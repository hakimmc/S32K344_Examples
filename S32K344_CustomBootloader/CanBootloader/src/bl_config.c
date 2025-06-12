/**
 * @file bl_config.c
 * @brief Bootloader configuration and flash utility functions.
 * @date 9 Mar 2025
 * @author hakimmc
 */

#include "bl_config.h"

/** @brief Bootloader startup message */
uint8_t HelloFromBoot[8] = {'C','R','7','>','L','M','1','0'};

/** @brief Mode start trigger word */
uint8_t ModestartWORD[8] = {'!','O','T','T','O','S','T','R'};

/** @brief Jump command word */
uint8_t jumpWORD[8]  = {'!','O','T','T','O','J','M','P'};

/** @brief Skip command word */
uint8_t skipWORD[8]  = {'!','O','T','T','O','N','X','T'};

/** @brief Application magic word */
uint8_t APP_MagicWORD[8] = {'!','A','P','P','D','A','T','E'};

/** @brief Configuration magic word */
uint8_t CFG_MagicWORD[8] = {'!','C','F','G','D','A','T','E'};

/** @brief Bootloader transmit word */
uint8_t BootStartWord_TX[8] = {'!','B','O','O','T','S','T','T'};

/** @brief Bootloader receive word */
uint8_t BootStartWord_RX[8] = {'!','B','O','O','T','S','T','D'};

/** @brief Configuration read transmit word */
uint8_t ReadConfig_TX[8] = {'R','E','A','D','C','F','G',';'};

/** @brief Configuration read response word */
uint8_t ReadConfig_RX[8] = {'!','C','F','G','W','R','G','T'};

/** @brief Bootloader state variable */
volatile uint8_t BootState = 0;

/** @brief Jump state variable */
volatile uint8_t JumpState = 0;

/** @brief Current boot mode */
BootMode_Enum BootMode = APPLICATION;

/** @brief Configuration flash start address */
uint32_t CFG_ADDR_START = 0x00500000;

/** @brief Application flash start address */
uint32_t APP_ADDR_START = 0x00502000;

/** @brief Last unlocked flash sector */
uint32_t UNLOCKED_LAST_SECTOR = 0;

/** @brief Last erased flash sector */
uint32_t ERASED_LAST_SECTOR = 0;

/** @brief Flash write index */
volatile uint32_t WriteIndex = 0;

/** @brief Dummy data to write to flash */
uint8_t FlashData[8] = {1,2,3,4,5,6,7,8};

/** @brief Data to signal jump from config */
uint8_t JumpToAppFromCfgData[8] = {'!','C','F','G','E','O','C',';'};

/** @brief Jump control flag */
volatile uint8_t BoolOfJumpToAppCfg = 0;

/** @brief CAN read buffer index */
uint8_t readCanIndx = 0;

/** @brief CAN receive buffer */
Flexcan_Ip_MsgBuffType rxData;

/** @brief CAN RX configuration */
Flexcan_Ip_DataInfoType rx_info =
{
	.msg_id_type = FLEXCAN_MSG_ID_EXT,
	.data_length = 8u,
	.is_polling = FALSE,
	.is_remote = FALSE
};

/** @brief CAN TX configuration */
Flexcan_Ip_DataInfoType tx_info =
{
	.msg_id_type = FLEXCAN_MSG_ID_EXT,
	.data_length = 8u,
	.is_polling = FALSE,
	.is_remote = FALSE
};

/** @brief Pointer to configuration structure */
MyConfig_t* config;

/**
 * @brief Initialize CAN interface and configure receive mailboxes.
 */
void setupCan(MyConfig_t* Conf)
{
	Siul2_Dio_Ip_WritePin(CAN0_EN_PORT, CAN0_EN_PIN, 1U);
	Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 1U);
	FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX, &rx_info, RX_BOOT_ID + Conf->system_id);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDW, &rx_info, RX_BOOT_WAKE_ID + Conf->system_id);
	FlexCAN_Ip_SetStartMode(INST_FLEXCAN_0);
}

/**
 * @brief Delay loop with condition-based break.
 *
 * @param ms Number of milliseconds to delay.
 * @param condition Pointer to condition variable to interrupt delay.
 * @return DelayState Final state of condition (0 or 1).
 */
DelayState __attribute__((optimize("O0"))) delay_ms(uint32_t ms, volatile uint8_t *condition)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 14545; j++)
        {
            if(*condition) break;
        }
		if(*condition) break;
    }
	return *condition;
}

/**
 * @brief Calculate CRC-CCITT checksum.
 *
 * @param data Pointer to data array.
 * @param Length Length of data array.
 * @return uint16_t Computed CRC value.
 */
uint16_t CalculateCRC(uint8_t *data, uint32_t Length)
{
    const uint16_t poly = 0x1021;
    uint16_t table[256];
    uint16_t initialValue = BOOT_CCITT_KEY;
    uint16_t temp, a;
    uint16_t crc = initialValue;

    for (int i = 0; i < 256; ++i)
    {
        temp = 0;
        a = (uint16_t)(i << 8);
        for (int j = 0; j < 8; ++j)
        {
            if (((temp ^ a) & 0x8000) != 0)
                temp = (uint16_t)((temp << 1) ^ poly);
            else
                temp <<= 1;
            a <<= 1;
        }
        table[i] = temp;
    }

    for (uint32_t i = 0; i < Length; ++i)
    {
        crc = (uint16_t)((crc << 8) ^ table[((crc >> 8) ^ data[i])]);
    }
    return crc;
}

/**
 * @brief Write data to flash memory with lock/unlock and erase management.
 *
 * @param Addr Target flash address.
 * @param Data Pointer to data buffer.
 * @param Length Length of data in bytes.
 * @param MASTER_ID Flash master ID.
 * @return uint8_t 1 on success, 0 on failure.
 */
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint32 Length, uint8_t MASTER_ID)
{
	C40_Ip_StatusType c40Status;

	if(UNLOCKED_LAST_SECTOR < (uint32_t)C40_Ip_GetSectorNumberFromAddress(Addr))
	{
		while(STATUS_C40_IP_SECTOR_PROTECTED != C40_Ip_GetLock(C40_Ip_GetSectorNumberFromAddress(Addr))){
			C40_Ip_SetLock(UNLOCKED_LAST_SECTOR, FLS_MASTER_ID);
		}
		UNLOCKED_LAST_SECTOR = C40_Ip_GetSectorNumberFromAddress(Addr);
	}

	if (STATUS_C40_IP_SECTOR_PROTECTED == C40_Ip_GetLock(C40_Ip_GetSectorNumberFromAddress(Addr)))
	{
		while(STATUS_C40_IP_SECTOR_UNPROTECTED != C40_Ip_GetLock(C40_Ip_GetSectorNumberFromAddress(Addr))){
			C40_Ip_ClearLock(C40_Ip_GetSectorNumberFromAddress(Addr), FLS_MASTER_ID);
		}
	}

	if(C40_Ip_GetSectorNumberFromAddress(Addr) != ERASED_LAST_SECTOR)
	{
	    C40_Ip_MainInterfaceSectorErase(C40_Ip_GetSectorNumberFromAddress(Addr), FLS_MASTER_ID);
		do
		{
			c40Status = C40_Ip_MainInterfaceSectorEraseStatus();
		}
		while (STATUS_C40_IP_SUCCESS != c40Status);
		ERASED_LAST_SECTOR = C40_Ip_GetSectorNumberFromAddress(Addr);
	}

    C40_Ip_MainInterfaceWrite(Addr, Length, Data, MASTER_ID);
    do
	{
		c40Status = C40_Ip_MainInterfaceWriteStatus();
	}
    while (STATUS_C40_IP_SUCCESS != c40Status);
    return (c40Status==STATUS_C40_IP_SUCCESS?1:0);
}

/**
 * @brief Compare two byte arrays.
 *
 * @param source Source data array.
 * @param target Target data array.
 * @param len Length to compare.
 * @return uint8_t 1 if equal, 0 otherwise.
 */
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++) {
        if (source[i] != target[i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Jump to user application.
 */
void JumpToUserApplication(void)
{
	uint32 func = *(uint32 volatile *)(APP_ADDR_START+ 0xC);
	func = *(uint32 volatile *)(((uint32)func) + 0x4);
	func = ((((uint32)func) & 0xFFFFFFFEU) | 1u);
	(* (void (*) (void)) func)();
}

#ifdef SwVersionControl_Enable
/**
 * @brief Check software version compatibility.
 *
 * @param MajorVersion Major version to check.
 * @param MinorVersion Minor version to check.
 * @param PatchVersion Patch (bugfix) version to check.
 * @return uint8_t 1 if compatible, 0 otherwise.
 */
uint8_t CheckSwVersion(uint8_t MajorVersion, uint8_t MinorVersion, uint8_t PatchVersion)
{
	if(MajorVersion >= config->sw_version_major || config->sw_version_major == 0xFF) return 1;
	if(MinorVersion >= config->sw_version_minor || config->sw_version_minor == 0xFF) return 1;
	if(PatchVersion >= config->sw_version_bugfix || config->sw_version_bugfix == 0xFF) return 1;
	return 0;
}
#endif

#ifdef SwLastDateControl_Enable
/**
 * @brief Check software build date compatibility.
 *
 * @param Date Software build date as UNIX timestamp.
 * @return uint8_t 1 if date is valid or newer, 0 otherwise.
 */
uint8_t CheckSwDate(uint32_t Date)
{
	return (Date >= config->unix_timestamp || config->unix_timestamp == 4294967295);
}
#endif

#ifdef SwMacAddressControl_Enable
/**
 * @brief Check if MAC address matches expected configuration.
 *
 * @param Mac Pointer to MAC address array (8 bytes).
 * @return uint8_t 1 if match or wildcard, 0 otherwise.
 */
uint8_t CheckMacAddr(uint8_t Mac[8])
{
	for(int indx = 1; indx < 7; indx++)
	{
		if(Mac[indx] == config->mac_address[indx-1] || config->mac_address[indx-1] == 0xFF)
			continue;
		else return 0;
	}
	return 1;
}
#endif
