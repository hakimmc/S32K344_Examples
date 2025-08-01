/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : FLEXIO
*   Dependencies         : 
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef CDD_UART_CFG_H
#define CDD_UART_CFG_H

/**
*   @file
*
*   @defgroup uart_driver UART Driver
*   @addtogroup  uart_driver UART Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"


#include "CDD_Uart_MBDT_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define UART_CFG_VENDOR_ID                    43
#define UART_CFG_AR_RELEASE_MAJOR_VERSION     4
#define UART_CFG_AR_RELEASE_MINOR_VERSION     7
#define UART_CFG_AR_RELEASE_REVISION_VERSION  0
#define UART_CFG_SW_MAJOR_VERSION             5
#define UART_CFG_SW_MINOR_VERSION             0
#define UART_CFG_SW_PATCH_VERSION             0
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Uart_MBDT_PBcfg.h */
#if (UART_CFG_VENDOR_ID != UART_MBDT_PBCFG_VENDOR_ID)
    #error "CDD_Uart_Cfg.h and Uart_MBDT_PBcfg.h have different vendor ids"
#endif
#if ((UART_CFG_AR_RELEASE_MAJOR_VERSION    != UART_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (UART_CFG_AR_RELEASE_MINOR_VERSION    != UART_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (UART_CFG_AR_RELEASE_REVISION_VERSION != UART_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of CDD_Uart_Cfg.h and Uart_MBDT_PBcfg.h are different"
#endif
#if ((UART_CFG_SW_MAJOR_VERSION != UART_MBDT_PBCFG_SW_MAJOR_VERSION) || \
     (UART_CFG_SW_MINOR_VERSION != UART_MBDT_PBCFG_SW_MINOR_VERSION) || \
     (UART_CFG_SW_PATCH_VERSION != UART_MBDT_PBCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of CDD_Uart_Cfg.h and Uart_MBDT_PBcfg.h are different"
#endif
    
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((UART_CFG_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (UART_CFG_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AUTOSAR Version Numbers of CDD_Uart_Cfg.h and Mcal.h are different"
    #endif
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define UART_CONFIG_EXT \
    UART_CONFIG_MBDT_PB \
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* CDD_UART_CFG_H */

