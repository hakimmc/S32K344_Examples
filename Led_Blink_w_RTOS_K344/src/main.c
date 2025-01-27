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

volatile int exit_code = 0;
/* User includes */
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

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
    /* Write your code here */
	Clock_Ip_Init(Clock_Ip_aClockConfig);
	Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

	Siul2_Dio_Ip_TogglePins(GPIOA_H, RED_LED);

	vSemaphoreCreateBinary(sem);
	configASSERT(sem != NULL);
	/*xSemaphoreTake(sem, 0);*/
	xSemaphoreGive(sem);

	xTaskCreate(RED_LED_TASK, "RED LED TASK", configMINIMAL_STACK_SIZE, NULL, MAIN_PRIORITY, NULL);
	xTaskCreate(GRN_LED_TASK, "GREEN LED TASK", configMINIMAL_STACK_SIZE, NULL, MAIN_PRIORITY+1, NULL);
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

/** @} */
