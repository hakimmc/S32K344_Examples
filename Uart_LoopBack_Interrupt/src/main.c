/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : S32K3XX
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file main.c
*
*   @addtogroup main_module main module documentation
*   @{
*/

/* Including necessary configuration files. */
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

volatile int exit_code = 0;
/* User includes */
#define PIT_INST_0 0U
#define CH_0 0U
#define PIT_PERIOD 40000000

/* Uart Rx Buffer*/
uint8_t rxbuff[24];
uint8_t counter;

#define clockConfig &Clock_Ip_aClockConfig[0]

#define FXOSC_CLOCK_FREQ   16000000U


#define UART_DEMO_ENABLE 1

Siul2_Dio_Ip_GpioType* GPIOC_L = PTC_L_HALF;
Siul2_Dio_Ip_GpioType* GPIOC_H = PTC_H_HALF;
Siul2_Dio_Ip_GpioType* GPIOA_L = PTA_L_HALF;
Siul2_Dio_Ip_GpioType* GPIOA_H = PTA_H_HALF;

Siul2_Dio_Ip_PinsChannelType GREEN_LED = 1<<1;
Siul2_Dio_Ip_PinsChannelType RED_LED   = 1<<5; // 16+5 need to be in high register

#define MAIN_PRIORITY                ( tskIDLE_PRIORITY + 2 )
SemaphoreHandle_t sem;

void RED_LED_TASK ( void *pvParameters );
void GRN_LED_TASK ( void *pvParameters );
void UART_TASK ( void *pvParameters );

void PIT0_IRQn_Handler(void){
	counter = 0;
}

void LPUART1_IRQn_Handler(void){
	counter = 0;
}
void PitNotification(void){
	counter = 0;
}

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
    /* Write your code here */
	Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);

	Lpuart_Uart_Ip_Init(LPUART_UART_IP_INSTANCE_USING_1, &Lpuart_Uart_Ip_xHwConfigPB_1);

	Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

	IntCtrl_Ip_Init(&IntCtrlConfig_0);

	OsIf_Init(NULL_PTR);
	IntCtrl_Ip_InstallHandler(LPUART1_IRQn, LPUART_UART_IP_1_IRQHandler, NULL_PTR);
	IntCtrl_Ip_EnableIrq(LPUART1_IRQn);

	Siul2_Dio_Ip_TogglePins(GPIOA_H, RED_LED);
	Lpuart_Uart_Ip_AsyncReceive(LPUART_UART_IP_INSTANCE_USING_1, rxbuff, 24);

	vSemaphoreCreateBinary(sem);
	configASSERT(sem != NULL);
	xSemaphoreGive(sem);

	xTaskCreate(RED_LED_TASK, "RED LED TASK", configMINIMAL_STACK_SIZE, NULL, MAIN_PRIORITY, NULL);
	xTaskCreate(GRN_LED_TASK, "GREEN LED TASK", configMINIMAL_STACK_SIZE, NULL, MAIN_PRIORITY+1, NULL);
	xTaskCreate(UART_TASK, "UART TASK", configMINIMAL_STACK_SIZE, NULL, MAIN_PRIORITY+2, NULL);
	vTaskStartScheduler();

    for(;;);
}

void RED_LED_TASK ( void *pvParameters )
{
	BaseType_t operation_status;
	(void)pvParameters;

	for(;;)
	{
		vTaskDelay(pdMS_TO_TICKS(1));
		operation_status = xSemaphoreTake(sem, portMAX_DELAY);
		configASSERT(operation_status == pdPASS);

		/* App Start */
		Siul2_Dio_Ip_TogglePins(GPIOA_H, RED_LED);
		Siul2_Dio_Ip_TogglePins(GPIOC_L, GREEN_LED);
		vTaskDelay(pdMS_TO_TICKS(100));
		/* App Stop */

		operation_status = xSemaphoreGive(sem);
		configASSERT(operation_status == pdPASS);
	}
}

void GRN_LED_TASK ( void *pvParameters )
{
	BaseType_t operation_status;
	(void)pvParameters;

	for(;;)
	{
		vTaskDelay(pdMS_TO_TICKS(1));
        operation_status = xSemaphoreTake(sem, portMAX_DELAY);
		configASSERT(operation_status == pdPASS);/**/

		/* App Start */
		Siul2_Dio_Ip_TogglePins(GPIOC_L, GREEN_LED);
		Siul2_Dio_Ip_TogglePins(GPIOA_H, RED_LED);
		vTaskDelay(pdMS_TO_TICKS(100));
		/* App Stop */

        operation_status = xSemaphoreGive(sem);
		configASSERT(operation_status == pdPASS);/**/
	}
}

//#define UART_SEMAPHORE_CUSTOM

void UART_TASK ( void *pvParameters )
{
	(void)pvParameters;
	for(int i=0;i<24;i++){
		rxbuff[i] = '\0';
	}
	for(;;)
	{
		/* App Start */
		//Lpuart_Uart_Ip_SyncSend(LPUART_UART_IP_INSTANCE_USING_1, rxbuff, 24, portMAX_DELAY);
		vTaskDelay(pdMS_TO_TICKS(1000));
		/* App Stop */
	}
}

void UartRxCallback(const uint8 HwInstance, const Lpuart_Uart_Ip_EventType Event, void *UserData)
{
	IntCtrl_Ip_DisableIrq(LPUART1_IRQn);
	(void) HwInstance;
	(void) Event;
	(void) UserData;
	Lpuart_Uart_Ip_SyncSend(LPUART_UART_IP_INSTANCE_USING_1, rxbuff, 24, 0xFFFF);
	Lpuart_Uart_Ip_AsyncReceive(LPUART_UART_IP_INSTANCE_USING_1, rxbuff, 24);
	IntCtrl_Ip_EnableIrq(LPUART1_IRQn);
}

/** @} */
