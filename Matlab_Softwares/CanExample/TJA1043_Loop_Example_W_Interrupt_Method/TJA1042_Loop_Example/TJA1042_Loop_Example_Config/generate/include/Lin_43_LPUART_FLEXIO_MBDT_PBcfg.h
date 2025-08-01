/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPUART_FLEXIO
*   Dependencies         : none
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

#ifndef LIN_43_LPUART_FLEXIO_MBDT_PBCFG_H
#define LIN_43_LPUART_FLEXIO_MBDT_PBCFG_H

/**
*   @file
*
*   @defgroup lin_driver LIN Driver
*   @addtogroup  lin_driver LIN Driver
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Lin_43_LPUART_FLEXIO_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define LIN_43_LPUART_FLEXIO_MBDT_PBCFG_VENDOR_ID                     43
#define LIN_43_LPUART_FLEXIO_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION      4
#define LIN_43_LPUART_FLEXIO_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION      7
#define LIN_43_LPUART_FLEXIO_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION   0
#define LIN_43_LPUART_FLEXIO_MBDT_PBCFG_SW_MAJOR_VERSION              5
#define LIN_43_LPUART_FLEXIO_MBDT_PBCFG_SW_MINOR_VERSION              0
#define LIN_43_LPUART_FLEXIO_MBDT_PBCFG_SW_PATCH_VERSION              0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/* Checks against Lin_43_LPUART_FLEXIO_Types.h */
#if (LIN_43_LPUART_FLEXIO_MBDT_PBCFG_VENDOR_ID != LIN_43_LPUART_FLEXIO_TYPES_VENDOR_ID)
    #error "Lin_43_LPUART_FLEXIO_MBDT_PBcfg.h and Lin_43_LPUART_FLEXIO_Types.h have different vendor ids"
#endif
#if ((LIN_43_LPUART_FLEXIO_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION   != LIN_43_LPUART_FLEXIO_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION   != LIN_43_LPUART_FLEXIO_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION!= LIN_43_LPUART_FLEXIO_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Lin_43_LPUART_FLEXIO_MBDT_PBcfg.h and Lin_43_LPUART_FLEXIO_Types.h are different"
#endif
#if ((LIN_43_LPUART_FLEXIO_MBDT_PBCFG_SW_MAJOR_VERSION!= LIN_43_LPUART_FLEXIO_TYPES_SW_MAJOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_MBDT_PBCFG_SW_MINOR_VERSION!= LIN_43_LPUART_FLEXIO_TYPES_SW_MINOR_VERSION) || \
     (LIN_43_LPUART_FLEXIO_MBDT_PBCFG_SW_PATCH_VERSION!= LIN_43_LPUART_FLEXIO_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lin_43_LPUART_FLEXIO_MBDT_PBcfg.h and Lin_43_LPUART_FLEXIO_Types.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define LIN_43_LPUART_FLEXIO_CONFIG_MBDT_PB \
    extern const Lin_43_LPUART_FLEXIO_ConfigType Lin_43_LPUART_FLEXIO_xConfig_MBDT;
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

#endif  /* LIN_43_LPUART_FLEXIO_MBDT_PBCFG_H */

