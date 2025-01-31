/**
 * @file main.c
 * @brief RTD AUTOSAR 4.7 Ana Modülü
 * @details Bu dosya RTD AUTOSAR 4.7 projesinin ana modülünü içerir.
 *
 * @author hakimmc
 * @date 2025-01-31
 */

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

/** @brief UART RX Buffer */
uint8_t rxbuff[5];
uint8_t MagicWORD[5] = {'!','O','T','T','O'};
uint8_t counter;
uint8_t boot_state = 0;

#define clockConfig &Clock_Ip_aClockConfig[0]

/** @brief GPIO Tanımlamaları */
Siul2_Dio_Ip_GpioType* GPIOC_L = PTC_L_HALF;
Siul2_Dio_Ip_GpioType* GPIOC_H = PTC_H_HALF;
Siul2_Dio_Ip_GpioType* GPIOA_L = PTA_L_HALF;
Siul2_Dio_Ip_GpioType* GPIOA_H = PTA_H_HALF;

Siul2_Dio_Ip_PinsChannelType GREEN_LED = 1<<1;
Siul2_Dio_Ip_PinsChannelType RED_LED   = 1<<5;

#define MAIN_PRIORITY ( tskIDLE_PRIORITY + 2 )
SemaphoreHandle_t sem;

/** @brief ISR Fonksiyonları */
void PIT0_IRQn_Handler(void) { __asm("NOP"); }
void LPUART1_IRQn_Handler(void) { __asm("NOP"); }
void PitNotification(void) { __asm("NOP"); }

/** @brief Fonksiyon Tanımlamaları */
uint8_t CRC_Calculator(uint8_t* input,uint8_t max_len);
uint8_t WriteToFlash(uint8_t* input, uint8_t max_len);
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint8_t Length, uint8_t MASTER_ID);
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len);

/** @brief UART Mesajları */
#define ErrorMessage "!ERR"
#define NextMessage "!NXT"
#define FLS_MASTER_ID 0U
#define FLS_BUF_SIZE 16U
uint32_t APP_ADDR_START = 0x00600000;
#define FLS_SECTOR_TEST C40_CODE_ARRAY_0_BLOCK_2_S256
uint32_t FLS_LAST_SECTOR = C40_CODE_ARRAY_0_BLOCK_2_S256;
uint8_t* ExampleData;
uint32_t WriteIndex = 0;

/**
 * @brief Ana fonksiyon
 * @return Program dönüş değeri
 */
int main(void) {
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    Lpuart_Uart_Ip_Init(LPUART_UART_IP_INSTANCE_USING_1, &Lpuart_Uart_Ip_xHwConfigPB_1);
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    C40_Ip_Init(NULL_PTR);
    IntCtrl_Ip_Init(&IntCtrlConfig_0);
    OsIf_Init(NULL_PTR);
    IntCtrl_Ip_InstallHandler(LPUART1_IRQn, LPUART_UART_IP_1_IRQHandler, NULL_PTR);
    IntCtrl_Ip_EnableIrq(LPUART1_IRQn);

    Siul2_Dio_Ip_TogglePins(GPIOA_H, RED_LED);
    Lpuart_Uart_Ip_AsyncReceive(LPUART_UART_IP_INSTANCE_USING_1, rxbuff, 5);

    for (;;) {
        Siul2_Dio_Ip_TogglePins(GPIOC_L, GREEN_LED);
        Siul2_Dio_Ip_TogglePins(GPIOA_H, RED_LED);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/**
 * @brief UART RX Callback fonksiyonu
 * @param HwInstance Donanım instance numarası
 * @param Event UART olay tipi
 * @param UserData Kullanıcı verisi
 */
void UartRxCallback(const uint8 HwInstance, const Lpuart_Uart_Ip_EventType Event, void *UserData) {
    IntCtrl_Ip_DisableIrq(LPUART1_IRQn);
    (void) HwInstance;
    (void) Event;
    (void) UserData;

    if (boot_state) {
    	if (Comparator(rxbuff, MagicWORD, 5)) {
    		boot_state = 0;
    	} else{
    		if (CRC_Calculator(rxbuff, 4) != rxbuff[4]) {
				Lpuart_Uart_Ip_SyncSend(LPUART_UART_IP_INSTANCE_USING_1, (uint8_t*) ErrorMessage, 4, 0xFFFF);
			} else {
				FlashWrite(APP_ADDR_START+WriteIndex, ExampleData, FLS_BUF_SIZE, FLS_MASTER_ID);
				Lpuart_Uart_Ip_SyncSend(LPUART_UART_IP_INSTANCE_USING_1, (uint8_t*) NextMessage, 4, 0xFFFF);
				WriteIndex += FLS_BUF_SIZE;
			}
    	}

    } else {
        if (Comparator(rxbuff, MagicWORD, 5)) {
            boot_state = 1;
        }
    }
    Lpuart_Uart_Ip_AsyncReceive(LPUART_UART_IP_INSTANCE_USING_1, rxbuff, 5);
    IntCtrl_Ip_EnableIrq(LPUART1_IRQn);
}

/**
 * @brief Verileri karşılaştıran fonksiyon
 * @param source Kaynak veri
 * @param target Hedef veri
 * @param len Karşılaştırma uzunluğu
 * @return Karşılaştırma sonucu
 */
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        if (source[i] != target[i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief CRC Hesaplama Fonksiyonu
 * @param input Giriş verisi
 * @param max_len Hesaba katma uzunluğu
 * @return CRC değeri
 */
uint8_t CRC_Calculator(uint8_t* input,uint8_t max_len)
{
	uint32_t SummOfBytes = 0;
	for(int i=0;i<max_len;i++){
		SummOfBytes += input[i];
	}
	return ((uint8_t)(SummOfBytes%255));
}

/**
 * @brief Flash'a data yazan fonksiyon
 * @param Addr Yazılacak adres verisi
 * @param Data Yazılacak veri
 * @param Length Yazma uzunluğu
 * @MASTER_ID MASTER ID
 * @return Yazma sonucu
 */
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint8_t Length, uint8_t MASTER_ID)
{
	C40_Ip_StatusType c40Status;
	/* Flash Unlock */
	if (STATUS_C40_IP_SECTOR_PROTECTED == C40_Ip_GetSectorNumberFromAddress(Addr))
	{
		C40_Ip_ClearLock(C40_Ip_GetSectorNumberFromAddress(Addr), FLS_MASTER_ID);
	}
	/* Erase Flash */
	do
	{
		c40Status = C40_Ip_MainInterfaceSectorEraseStatus();
	}
	while (STATUS_C40_IP_BUSY == c40Status);
	/* Write Flash */
    C40_Ip_MainInterfaceWrite(C40_Ip_GetSectorNumberFromAddress(Addr), Length, Data, MASTER_ID);
    /* Check Last Status */
    do
	{
		c40Status = C40_Ip_MainInterfaceWriteStatus();
	}
	while (STATUS_C40_IP_BUSY == c40Status);
    return (c40Status==STATUS_C40_IP_SUCCESS?1:0);
}

/**
 * @brief App atlama kodu
 */
static void JumpApplication(void)
{
  void (*app_reset_handler)(void) = (void*)(*((volatile uint32_t*) (APP_ADDR_START + 4U)));
  //  __set_MSP(*(volatile uint32_t*) APP_ADDR_START);
  /* Jump to application */
  /* Disable All Peripheral */
  /* !!!!!!!IMPORTANT!!!!!! */
__asm volatile ("MSR MSP, %0" : : "r" (*(volatile uint32_t*) APP_ADDR_START));
  /* Disable All Peripheral */
  app_reset_handler();    //call the app reset handler
}

/** @} */
