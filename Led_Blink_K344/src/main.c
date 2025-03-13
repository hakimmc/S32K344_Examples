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


volatile uint8_t exit_code = 0;
volatile uint8_t status = 1;
/* User includes */

Siul2_Dio_Ip_GpioType* GPIOC_L = PTC_L_HALF;
Siul2_Dio_Ip_GpioType* GPIOC_H = PTC_H_HALF;
Siul2_Dio_Ip_GpioType* GPIOA_L = PTA_L_HALF;
Siul2_Dio_Ip_GpioType* GPIOA_H = PTA_H_HALF;

Siul2_Dio_Ip_PinsChannelType GREEN_LED = 1<<1;
Siul2_Dio_Ip_PinsChannelType RED_LED   = 1<<5; // 16+5 need to be in high register

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
    for(;;)
    {
    	switch (status) {
			case 1:
				Siul2_Dio_Ip_SetPins(GPIOC_L, GREEN_LED);
				Siul2_Dio_Ip_ClearPins(GPIOA_H, RED_LED);
				break;
			case 0:
				Siul2_Dio_Ip_ClearPins(GPIOC_L, GREEN_LED);
				Siul2_Dio_Ip_SetPins(GPIOA_H, RED_LED);
				break;
		}
    	/*SIUL2_DIO_IP_DEV_ASSERT(NULL_PTR != base);
		base->PGPDO |= Siul2_Dio_Ip_Rev_Bit_16(pins);*/
		status^=1;
		for(int i=0;i<0xFFFFFF;i++);
    }
}

/** @} */
