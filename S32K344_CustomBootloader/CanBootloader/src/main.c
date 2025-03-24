/*!
** Copyright 2019 NXP
** @file main.c
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including necessary configuration files. */
#include "Mcal.h"
#include "Clock_Ip.h"
#include "FlexCAN_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "C40_Ip.h"

uint8_t boot_state = 0;
uint32_t CRC_Calculator(uint8_t* input,uint8_t max_len);
uint8_t WriteToFlash(uint8_t* input, uint8_t max_len);
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint32 Length, uint8_t MASTER_ID);
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len);
void JumpToUserApplication(void);

#define FLS_MASTER_ID 0U
#define FLS_BUF_SIZE 8
uint32_t APP_ADDR_START = 0x00500000;//0x00600000;
uint32_t UNLOCKED_LAST_SECTOR = 0;
uint32_t ERASED_LAST_SECTOR = 0;
uint8_t FlashData[8] = {1,2,3,4,5,6,7,8};
uint32_t WriteIndex = 0;

#define MSG_ID 0xC0FFEEu
#define RX_MB_IDX 1U
#define TX_MB_IDX 0U
volatile int exit_code = 0;
/* User includes */
uint8 dummyData[8] = {1,2,3,4,5,6,7,8};
Flexcan_Ip_MsgBuffType rxData;

Flexcan_Ip_DataInfoType rx_info = {
            .msg_id_type = FLEXCAN_MSG_ID_EXT,
            .data_length = 8u,
            .is_polling = FALSE,
            .is_remote = FALSE
    };

Flexcan_Ip_DataInfoType tx_info = {
		.msg_id_type = FLEXCAN_MSG_ID_EXT,
		.data_length = 8u,
		.is_polling = FALSE,
		.is_remote = FALSE
	};

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
extern void CAN0_ORED_0_31_MB_IRQHandler(void);


void flexcan0_Callback(uint8 instance, Flexcan_Ip_EventType eventType, uint32 buffIdx,
		const Flexcan_Ip_StateType *flexcanState)
{
	(void)flexcanState;
	(void)instance;
	(void)buffIdx;

	switch(eventType)
	{
	case FLEXCAN_EVENT_RX_COMPLETE:

		FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
		FlashWrite(APP_ADDR_START+WriteIndex, FlashData, FLS_BUF_SIZE, FLS_MASTER_ID);
		FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, MSG_ID, (uint8 *)&rxData);
		WriteIndex+=8;
		break;
	case FLEXCAN_EVENT_RXFIFO_COMPLETE:
		break;
	case FLEXCAN_EVENT_TX_COMPLETE:



		break;
	default:
		break;
	}
}

static void setupCan( void )
{
	Siul2_Dio_Ip_WritePin(CAN0_EN_PORT, CAN0_EN_PIN, 1U);
	Siul2_Dio_Ip_WritePin(CAN0_STB_PORT, CAN0_STB_PIN, 1U);
	FlexCAN_Ip_Init(INST_FLEXCAN_0, &FlexCAN_State0, &FlexCAN_Config0);
    FlexCAN_Ip_ConfigRxMb(INST_FLEXCAN_0, RX_MB_IDX, &rx_info, 0xFACE);
	FlexCAN_Ip_SetStartMode(INST_FLEXCAN_0);
}


int main(void)
{
	/* Write your code here */
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    C40_Ip_Init(NULL_PTR);

    IntCtrl_Ip_EnableIrq(FlexCAN0_1_IRQn);
    IntCtrl_Ip_EnableIrq(FlexCAN0_0_IRQn);
    IntCtrl_Ip_InstallHandler(FlexCAN0_1_IRQn, CAN0_ORED_0_31_MB_IRQHandler, NULL_PTR);
    IntCtrl_Ip_InstallHandler(FlexCAN0_0_IRQn, CAN0_ORED_0_31_MB_IRQHandler, NULL_PTR);

    tx_info.is_polling = FALSE;
    rx_info.is_polling = FALSE;
    setupCan();

    UNLOCKED_LAST_SECTOR = C40_Ip_GetSectorNumberFromAddress(APP_ADDR_START);
	ERASED_LAST_SECTOR = UNLOCKED_LAST_SECTOR-1;

    FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, MSG_ID, (uint8 *)&dummyData);
	FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
    while(1)
    {

    }

    FlexCAN_Ip_SetStopMode(INST_FLEXCAN_0);
    FlexCAN_Ip_Deinit(INST_FLEXCAN_0);
    return 0;
}


uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        if (source[i] != target[i]) {
            return 0;
        }
    }
    return 1;
}

uint32_t CRC_Calculator(uint8_t* input,uint8_t max_len)
{
	uint32_t SummOfBytes = 0;
	for(int i=0;i<max_len;i++){
		SummOfBytes += input[i];
	}
	return ((uint32_t)(SummOfBytes%255));
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

typedef void (*AppAddr)(void);
AppAddr JumpAppAddr = NULL;
void JumpToUserApplication(void)
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
