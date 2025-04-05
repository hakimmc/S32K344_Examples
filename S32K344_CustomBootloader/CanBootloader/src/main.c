//#include "Mcal.h"
#include "Clock_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#include "bl_config.h"
#include "S32K344.h"

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

#define RX_MB_IDW 2U
#define RX_MB_IDX 1U
#define TX_MB_IDX 0U

#define RX_BOOT_WAKE_ID 0x5165U
#define RX_BOOT_ID 0x5166U
#define TX_BOOT_ID 0x5166U

#define BOOT_CCITT_KEY 0xCEFA

uint8_t readCanIndx = 0;

Flexcan_Ip_MsgBuffType rxData;

uint8_t startWORD[8] = {'!','O','T','T','O','S','T','R'};
uint8_t jumpWORD[8]  = {'!','O','T','T','O','J','M','P'};
uint8_t skipWORD[8]  = {'!','O','T','T','O','N','X','T'};

uint8_t APP_MagicWORD[8] = {'!','A','P','P','D','A','T','E'};
uint8_t CFG_MagicWORD[8] = {'!','C','F','G','D','A','T','E'};

volatile uint8_t BootState = 0;
volatile uint8_t JumpState = 0;
BootMode_Enum BootMode = APPLICATION;
#define FLS_MASTER_ID 0U
#define FLS_BUF_SIZE 8
uint32_t CFG_ADDR_START = 0x00450000;
uint32_t APP_ADDR_START = 0x00500000;
uint32_t UNLOCKED_LAST_SECTOR = 0;
uint32_t ERASED_LAST_SECTOR = 0;
uint32_t WriteIndex = 0;
uint8_t FlashData[8] = {1,2,3,4,5,6,7,8};

void setupCan( void )
{
	Siul2_Dio_Ip_WritePin(CAN0_EN_PORT, CAN0_EN_PIN, 1U);
	Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 1U);
	FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX, &rx_info, RX_BOOT_ID);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDW, &rx_info, RX_BOOT_WAKE_ID);
	FlexCAN_Ip_SetStartMode(INST_FLEXCAN_0);
}

uint8_t is_Timeout(uint32_t ms);
uint16_t CalculateCRC(uint8_t *data, uint32_t Length);
uint8_t WriteToFlash(uint8_t* input, uint8_t max_len);
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint32 Length, uint8_t MASTER_ID);
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len);
void __attribute__((optimize("O0"))) delay_ms(uint32_t ms, volatile uint8_t *condition);
void JumpToUserApplication( void );
void SysTick_Init(void);
void SysTick_Enable(void);
void SysTick_Disable(void);

int main(void)
{
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    C40_Ip_Init(NULL_PTR);

    IntCtrl_Ip_EnableIrq(FlexCAN0_1_IRQn);
    IntCtrl_Ip_InstallHandler(FlexCAN0_1_IRQn, CAN0_ORED_0_31_MB_IRQHandler, NULL_PTR);
    tx_info.is_polling = FALSE;
    rx_info.is_polling = FALSE;
    setupCan();
    SysTick_Init();
    UNLOCKED_LAST_SECTOR = C40_Ip_GetSectorNumberFromAddress(APP_ADDR_START);
	ERASED_LAST_SECTOR = UNLOCKED_LAST_SECTOR-1;

	FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, TX_BOOT_ID, startWORD);
	FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDW, &rxData, FALSE);
    while(!JumpState && !BootState)
    {
    	delay_ms(5000, BootState);
    	JumpState = 1;
    	while(BootState) __asm("NOP");
    }
    IntCtrl_Ip_DisableIrq(FlexCAN0_1_IRQn);
    FlexCAN_Ip_SetStopMode(INST_FLEXCAN_0);
    FlexCAN_Ip_Deinit(INST_FLEXCAN_0);
    JumpToUserApplication();
}

void SysTick_Init(void)
{
	S32_SysTick->RVR = 0xFFFFFFFul;
	S32_SysTick->CVR = 0ul;
	S32_SysTick->CSRr = 0u;
}

void SysTick_Enable(void)
{
	S32_SysTick->CSRr = S32_SysTick_CSR_TICKINT(1u) | S32_SysTick_CSR_ENABLE(1);
}

void SysTick_Disable(void)
{
	S32_SysTick->CSRr = 0ul;
}

typedef enum{
	TimeOut,
	Condition_Occured
}DelayState;

DelayState __attribute__((optimize("O0"))) delay_ms(uint32_t ms, volatile uint8_t *condition)
{
    volatile uint32_t i, j;	
    for (i = 0; i < ms; i++)
    {
        //for (j = 0; j < 40000; j++)removed for perfect timing with 160mhz clock : loop using 8 cycle; 8 x 40000 = 320.000 => 320.000 / 160.000.000 = 0.002S => 2mS
		//																			2mS is too much max loop value replaced with 20000 for 1 mS;
        for (j = 0; j < 20000; j++)
		{
            //__asm("NOP"); removed for perfect timing 160mhz clock; if i use nop asm block i will be used 9 cycle;
			if(*condition) break;
        }
		if(*condition) break;
    }
	return *condition;
}

uint8_t is_Timeout(uint32_t ms)
{
	S32_SysTick->RVR = 10000 * ms * 1000;
	SysTick_Enable();
    //uint32_t ticks = (160000000 / 1000) * ms; // 160 MHz
    //uint32_t start = S32_SysTick->CVR;
	//while (((start - S32_SysTick->CVR) & 0x00FFFFFF) < ticks);
	while (S32_SysTick->CVR != 0);
	SysTick_Disable();
    return 1;
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


extern void CAN0_ORED_0_31_MB_IRQHandler(void);

void flexcan0_Callback(uint8 instance, Flexcan_Ip_EventType eventType, uint32 buffIdx, const Flexcan_Ip_StateType *flexcanState)
{
	(void)flexcanState;
	(void)instance;
	/* Commented this block because the incoming buffIdx ignores itself via the void tag.
	(void)buffIdx;*/

	switch(eventType)
	{
		case FLEXCAN_EVENT_RX_COMPLETE:
			switch (buffIdx)
			{
				case RX_MB_IDW: // for wakeup
					if(Comparator(rxData.data, APP_MagicWORD, 4))
					{
						BootMode = APPLICATION;
					}
					else if(Comparator(rxData.data, CFG_MagicWORD, 4))
					{
						BootMode = CONFIG;
					}
					if(BootMode == APPLICATION  || BootMode == CONFIG)
					{
						BootState = 1;
						FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, TX_BOOT_ID, startWORD);
						FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
					}
					else
					{
						FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDW, &rxData, FALSE);
					}
					break;
				case RX_MB_IDX: // for boot
					if(BootState)
					{
						if(Comparator(rxData.data, jumpWORD, 8))
						{
							BootState = 0;
							JumpState = 1;
							break;
						}
						if(CalculateCRC(rxData.data, 6) != (uint16_t)((rxData.data[6]*256) + rxData.data[7])){ break;}
						if(!rxData.data[1])
						{
							for(int fi=0; fi<4; fi++)
							{
								FlashData[fi] = rxData.data[2+fi];
							}
						}
						else if(rxData.data[1])
						{
							for(int fi=0; fi<4; fi++)
							{
								FlashData[fi+4] = rxData.data[2+fi];
							}
							switch (BootMode)
							{
								case APPLICATION:
									FlashWrite(APP_ADDR_START+WriteIndex, FlashData, FLS_BUF_SIZE, FLS_MASTER_ID);
									WriteIndex+=8;
									break;
								case CONFIG:
									FlashWrite(CFG_ADDR_START+WriteIndex, FlashData, FLS_BUF_SIZE, FLS_MASTER_ID);
									WriteIndex+=8;
									break;
								default:
									break;
							}
						}

						FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, RX_BOOT_ID, skipWORD);
						//memset(rxData.data,'\0', 8);
						FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
					}
					break;
			}
			break;
		default:
			break;
	}
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


/* END main */
/*!
** @}
*/
