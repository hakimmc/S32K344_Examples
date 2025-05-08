/*
 * bl_config.c
 *
 *  Created on: 9 Mar 2025
 *      Author: hakimmc
 */

#include "bl_config.h"

uint8_t HelloFromBoot[8] = {'C','R','7','>','L','M','1','0'};
uint8_t ModestartWORD[8] = {'!','O','T','T','O','S','T','R'};
uint8_t jumpWORD[8]  = {'!','O','T','T','O','J','M','P'};
uint8_t skipWORD[8]  = {'!','O','T','T','O','N','X','T'};
uint8_t APP_MagicWORD[8] = {'!','A','P','P','D','A','T','E'};
uint8_t CFG_MagicWORD[8] = {'!','C','F','G','D','A','T','E'};
uint8_t BootStartWord_TX[8] = {'!','B','O','O','T','S','T','T'};
uint8_t BootStartWord_RX[8] = {'!','B','O','O','T','S','T','D'};
uint8_t ReadConfig_TX[8] = {'R','E','A','D','C','F','G',';'};
uint8_t ReadConfig_RX[8] = {'!','C','F','G','W','R','G','T'};

volatile uint8_t BootState = 0;
volatile uint8_t JumpState = 0;
BootMode_Enum BootMode = APPLICATION;
uint32_t CFG_ADDR_START = 0x00500000;
uint32_t APP_ADDR_START = 0x00502000;
uint32_t UNLOCKED_LAST_SECTOR = 0;
uint32_t ERASED_LAST_SECTOR = 0;
volatile uint32_t WriteIndex = 0;
uint8_t FlashData[8] = {1,2,3,4,5,6,7,8};
uint8_t JumpToAppFromCfgData[8] = {'!','C','F','G','E','O','C',';'};
volatile uint8_t BoolOfJumpToAppCfg = 0;
uint8_t readCanIndx = 0;

Flexcan_Ip_MsgBuffType rxData;

Flexcan_Ip_DataInfoType rx_info =
{
		.msg_id_type = FLEXCAN_MSG_ID_EXT,
		.data_length = 8u,
		.is_polling = FALSE,
		.is_remote = FALSE
};

Flexcan_Ip_DataInfoType tx_info =
{
	.msg_id_type = FLEXCAN_MSG_ID_EXT,
	.data_length = 8u,
	.is_polling = FALSE,
	.is_remote = FALSE
};

MyConfig_t* config;

void setupCan( void )
{
	Siul2_Dio_Ip_WritePin(CAN0_EN_PORT, CAN0_EN_PIN, 1U);
	Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 1U);
	FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX, &rx_info, RX_BOOT_ID + config->system_id);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDW, &rx_info, RX_BOOT_WAKE_ID + config->system_id);
	FlexCAN_Ip_SetStartMode(INST_FLEXCAN_0);
}

DelayState __attribute__((optimize("O0"))) delay_ms(uint32_t ms, volatile uint8_t *condition)
{
    volatile uint32_t i, j;//2 cycle
    for (i = 0; i < ms; i++)
    {
        //for (j = 0; j < 40000; j++)removed for perfect timing with 160mhz clock : loop using 8 cycle; 8 x 40000 = 320.000 => 320.000 / 160.000.000 = 0.002S => 2mS
		//																			2mS is too much max loop value replaced with 20000 for 1 mS;
        for (j = 0; j < 14545; j++)
		{
            //__asm("NOP"); removed for perfect timing 160mhz clock; if i use nop asm block i will be used 9 cycle;
			if(*condition) break;
        }
		if(*condition) break;
    }
	return *condition;
}

uint16_t CalculateCRC(uint8_t *data, uint32_t Length)
{
    const uint16_t poly = 0x1021; // 0x1021 = 4129 (CRC-CCITT poly)
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

uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint32 Length, uint8_t MASTER_ID)
{
	C40_Ip_StatusType c40Status;


	/* Flash Lock */
	if(UNLOCKED_LAST_SECTOR < (uint32_t)C40_Ip_GetSectorNumberFromAddress(Addr))
	{
		while(STATUS_C40_IP_SECTOR_PROTECTED != C40_Ip_GetLock(C40_Ip_GetSectorNumberFromAddress(Addr))){
			C40_Ip_SetLock(UNLOCKED_LAST_SECTOR, FLS_MASTER_ID);
		}
		UNLOCKED_LAST_SECTOR = C40_Ip_GetSectorNumberFromAddress(Addr);
	}

	/* Flash Unlock */
	if (STATUS_C40_IP_SECTOR_PROTECTED == C40_Ip_GetLock(C40_Ip_GetSectorNumberFromAddress(Addr)))
	{
		while(STATUS_C40_IP_SECTOR_UNPROTECTED != C40_Ip_GetLock(C40_Ip_GetSectorNumberFromAddress(Addr))){
			C40_Ip_ClearLock(C40_Ip_GetSectorNumberFromAddress(Addr), FLS_MASTER_ID);
		}
	}

	/* Erase Flash */
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

	/* Write Flash */
    C40_Ip_MainInterfaceWrite(Addr, Length, Data, MASTER_ID);
    /* Check Last Status */
    do
	{
		c40Status = C40_Ip_MainInterfaceWriteStatus();
	}
    while (STATUS_C40_IP_SUCCESS != c40Status);
    return (c40Status==STATUS_C40_IP_SUCCESS?1:0);
}

uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++) {
        if (source[i] != target[i]) {
            return 0;
        }
    }
    return 1;
}

typedef void (*AppAddr)(void);
AppAddr JumpAppAddr = NULL;
void JumpToUserApplication( void )
{
	uint32 func = *(uint32 volatile *)(APP_ADDR_START+ 0xC);
	func = *(uint32 volatile *)(((uint32)func) + 0x4);
	func = ((((uint32)func) & 0xFFFFFFFEU) | 1u); // with "|1u" code worked
	(* (void (*) (void)) func)();
}

#ifdef SwVersionControl_Enable
/**
 * @brief Check if software version matches expected version.
 *
 * @param SwVersion Expected software version
 * @return 1 if match, 0 otherwise
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
 * @brief Check if software date matches expected date.
 *
 * @param Date Expected date
 * @return 1 if match, 0 otherwise
 */
uint8_t CheckSwDate(uint32_t Date)
{
	return (Date >= config->unix_timestamp || config->unix_timestamp == 4294967295);
}
#endif

#ifdef SwMacAddressControl_Enable
/**
 * @brief Check if software mac adress expected mac address.
 *
 * @param Mac Mac address
 * @return 1 if match, 0 otherwise
 */
uint8_t CheckMacAddr(uint8_t Mac[8])
{
	for(int indx = 1; indx<7;indx++)
	{
		if(Mac[indx] == config->mac_address[indx-1] || config->mac_address[indx-1] == 0xFF)	continue;
		else return 0;
	}
	return 1;
}
#endif

