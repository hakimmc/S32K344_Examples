/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPI2C
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
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may
*   only be used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file
*
*   @addtogroup I2C_DRIVER_CONFIGURATION I2c Driver Configurations
*   @{
*/

#ifndef CDD_I2C_MBDT_PBCFG_H
#define CDD_I2C_MBDT_PBCFG_H

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
#include "CDD_I2c_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_I2C_MBDT_PBCFG_VENDOR_ID                    43
#define CDD_I2C_MBDT_PBCFG_MODULE_ID                    255
#define CDD_I2C_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION     4
#define CDD_I2C_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION     7
#define CDD_I2C_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION  0
#define CDD_I2C_MBDT_PBCFG_SW_MAJOR_VERSION             5
#define CDD_I2C_MBDT_PBCFG_SW_MINOR_VERSION             0
#define CDD_I2C_MBDT_PBCFG_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and CDD_I2c_Types.h header file are of the same vendor */
#if (CDD_I2C_MBDT_PBCFG_VENDOR_ID != CDD_I2C_TYPES_VENDOR_ID)
    #error "CDD_I2c_MBDT_PBcfg.h and CDD_I2c_Types.h have different vendor ids"
#endif
/* Check if current file and CDD_I2c_Types.h header file are of the same module */
#if (CDD_I2C_MBDT_PBCFG_MODULE_ID != CDD_I2C_TYPES_MODULE_ID)
    #error "CDD_I2c_MBDT_PBcfg.h and CDD_I2c_Types.h have different module ids"
#endif
/* Check if current file and CDD_I2c_Types.h header file are of the same Autosar version */
#if ((CDD_I2C_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION    != CDD_I2C_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION    != CDD_I2C_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION != CDD_I2C_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of CDD_I2c_MBDT_PBcfg.h and CDD_I2c_Types.h are different"
#endif
/* Check if current file and CDD_I2c_Types.h header file are of the same Software version */
#if ((CDD_I2C_MBDT_PBCFG_SW_MAJOR_VERSION != CDD_I2C_TYPES_SW_MAJOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_SW_MINOR_VERSION != CDD_I2C_TYPES_SW_MINOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_SW_PATCH_VERSION != CDD_I2C_TYPES_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of CDD_I2c_MBDT_PBcfg.h and CDD_I2c_Types.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
#define I2C_CONFIG_MBDT_PB \
extern const I2c_ConfigType I2c_Config_MBDT;

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* #ifndef CDD_I2C_MBDT_PBCFG_H */


