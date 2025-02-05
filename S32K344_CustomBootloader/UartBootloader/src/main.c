#include "Clock_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "Lpuart_Uart_Ip.h"
#include "S32K344.h"
#include "Lpuart_Uart_Ip_Irq.h"
#include "IntCtrl_Ip.h"
#include "Pit_Ip.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "C40_Ip.h"

uint8_t rxbuff[9];
uint8_t MagicWORD[5] = {'!','O','T','T','O'};
uint8_t SkipWORD[9] = {'!','S','K','I','P','J','U','M','P'};
uint8_t dummy[9] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0',};
uint8_t freebyte[9] = {0,0,0,0,0,0,0,0,0};
uint8_t counter;
uint8_t boot_state = 0;

#define clockConfig &Clock_Ip_aClockConfig[0]

Siul2_Dio_Ip_GpioType* GPIOC_L = PTC_L_HALF;
Siul2_Dio_Ip_GpioType* GPIOC_H = PTC_H_HALF;
Siul2_Dio_Ip_GpioType* GPIOA_L = PTA_L_HALF;
Siul2_Dio_Ip_GpioType* GPIOA_H = PTA_H_HALF;

Siul2_Dio_Ip_PinsChannelType GREEN_LED = 1<<1;
Siul2_Dio_Ip_PinsChannelType RED_LED   = 1<<5;

#define MAIN_PRIORITY ( tskIDLE_PRIORITY + 2 )
SemaphoreHandle_t sem;

void PIT0_IRQn_Handler(void) { __asm("NOP"); }
void LPUART1_IRQn_Handler(void) { __asm("NOP"); }
void PitNotification(void) { __asm("NOP"); }

uint8_t CRC_Calculator(uint8_t* input,uint8_t max_len);
uint8_t WriteToFlash(uint8_t* input, uint8_t max_len);
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint32 Length, uint8_t MASTER_ID);
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len);
void JumpToApplication( unsigned int userSP,  unsigned int userStartup);
void __DISABLE_PER(void);

#define ReadyMessage "!RDY"
#define ErrorMessage "!ERR"
#define NextMessage "!NXT"
#define StartMessage "!STR"
#define FLS_MASTER_ID 0U
#define FLS_BUF_SIZE 8
uint32_t APP_ADDR_START = 0x00600000;
uint32_t UNLOCKED_LAST_SECTOR = 0;
uint32_t ERASED_LAST_SECTOR = 0;
uint8_t FlashData[8] = {0,0,0,0,0,0,0,0};
uint32_t WriteIndex = 0;


int main(void) {
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    Lpuart_Uart_Ip_Init(LPUART_UART_IP_INSTANCE_USING_1, &Lpuart_Uart_Ip_xHwConfigPB_1);
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    C40_Ip_Init(NULL_PTR);
    IntCtrl_Ip_Init(&IntCtrlConfig_0);
    OsIf_Init(NULL_PTR);

    UNLOCKED_LAST_SECTOR = C40_Ip_GetSectorNumberFromAddress(APP_ADDR_START);
    ERASED_LAST_SECTOR = UNLOCKED_LAST_SECTOR-1;

    IntCtrl_Ip_InstallHandler(LPUART1_IRQn, LPUART_UART_IP_1_IRQHandler, NULL_PTR);
    IntCtrl_Ip_EnableIrq(LPUART1_IRQn);

    Siul2_Dio_Ip_TogglePins(GPIOA_H, RED_LED);
    Lpuart_Uart_Ip_AsyncReceive(LPUART_UART_IP_INSTANCE_USING_1, rxbuff, 5);

	Lpuart_Uart_Ip_SyncSend(LPUART_UART_IP_INSTANCE_USING_1, (uint8_t*) ReadyMessage, 4, 0xFFFF);

	for (;;) {
		Siul2_Dio_Ip_TogglePins(GPIOC_L, GREEN_LED);
		for(int delay = 0; delay < 0xFF; delay++);
		Siul2_Dio_Ip_TogglePins(GPIOA_H, RED_LED);
		for(int delay = 0; delay < 0xFF; delay++);
	}
}



void UartRxCallback(const uint8 HwInstance, const Lpuart_Uart_Ip_EventType Event, void *UserData) {
    IntCtrl_Ip_DisableIrq(LPUART1_IRQn);
    (void) HwInstance;
    (void) Event;
    (void) UserData;
    if(!Comparator(rxbuff, dummy, 5))
    {
		if (boot_state) {
			if (Comparator(rxbuff, MagicWORD, 5)) {
				boot_state = 0;
				__DISABLE_PER();
				JumpToApplication(*((uint32_t*)APP_ADDR_START), *((uint32_t*)(APP_ADDR_START + 4)));
			} else{
				if (CRC_Calculator(rxbuff, 8) == rxbuff[8]) {
					for(int indx = 0; indx < 8; indx++){
						FlashData[indx] = rxbuff[indx];
					}
					FlashWrite(APP_ADDR_START+WriteIndex, FlashData, FLS_BUF_SIZE, FLS_MASTER_ID);
					Lpuart_Uart_Ip_SyncSend(LPUART_UART_IP_INSTANCE_USING_1, (uint8_t*) NextMessage, 4, 0xFFFF);
					WriteIndex += (FLS_BUF_SIZE);
				}
				else if(Comparator(rxbuff,SkipWORD,9)){
					for(int indx = 0; indx < 8; indx++){
						FlashData[indx] = freebyte[indx];
					}
					FlashWrite(APP_ADDR_START+WriteIndex, FlashData, FLS_BUF_SIZE, FLS_MASTER_ID);
					Lpuart_Uart_Ip_SyncSend(LPUART_UART_IP_INSTANCE_USING_1, (uint8_t*) NextMessage, 4, 0xFFFF);
					WriteIndex += (FLS_BUF_SIZE);
				}
			}

		} else {
			if (Comparator(rxbuff, MagicWORD, 5)) {
				boot_state = 1;
				Lpuart_Uart_Ip_SyncSend(LPUART_UART_IP_INSTANCE_USING_1, (uint8_t*) StartMessage, 4, 0xFFFF);
			}
		}
    }
		memset(rxbuff,'\0',9);
		Lpuart_Uart_Ip_AsyncReceive(LPUART_UART_IP_INSTANCE_USING_1, rxbuff, 9);
		IntCtrl_Ip_EnableIrq(LPUART1_IRQn);
}

uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        if (source[i] != target[i]) {
            return 0;
        }
    }
    return 1;
}

uint8_t CRC_Calculator(uint8_t* input,uint8_t max_len)
{
	uint32_t SummOfBytes = 0;
	for(int i=0;i<max_len;i++){
		SummOfBytes += input[i];
	}
	return ((uint8_t)(SummOfBytes%255));
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

void __DISABLE_PER(void)
{
	IntCtrl_Ip_DisableIrq(LPUART1_IRQn);
	Lpuart_Uart_Ip_Deinit(LPUART_UART_IP_INSTANCE_USING_1);
}

void JumpToApplication( unsigned int userSP,  unsigned int userStartup)
{
	/* Check if Entry address is erased and return if erased */
	if(userSP == 0xFFFFFFFF){
		return;
	}

	/* Set up stack pointer */
	__asm("msr msp, r0");
	__asm("msr psp, r0");

	/* Relocate vector table */
	S32_SCB->VTOR = (uint32_t)APP_ADDR_START;

	/* Jump to application PC (r1) */
	__asm("mov pc, r1");
}

