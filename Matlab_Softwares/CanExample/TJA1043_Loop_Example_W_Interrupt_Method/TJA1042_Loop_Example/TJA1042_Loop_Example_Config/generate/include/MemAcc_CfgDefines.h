/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : none
*   Dependencies         : MemAcc
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

#ifndef MEMACC_CFG_DEFINES_H
#define MEMACC_CFG_DEFINES_H

/**
*   @file MemAcc_CfgDefines.h
*
*   @addtogroup MEMACC
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MEMACC_VENDOR_ID_CFG_DEFINES                      43
#define MEMACC_AR_RELEASE_MAJOR_VERSION_CFG_DEFINES       4
#define MEMACC_AR_RELEASE_MINOR_VERSION_CFG_DEFINES       7
#define MEMACC_AR_RELEASE_REVISION_VERSION_CFG_DEFINES    0
#define MEMACC_SW_MAJOR_VERSION_CFG_DEFINES               5
#define MEMACC_SW_MINOR_VERSION_CFG_DEFINES               0
#define MEMACC_SW_PATCH_VERSION_CFG_DEFINES               0


/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/* Pre-processor switch to enable and disable development error detection */
#define MEMACC_DEV_ERROR_DETECT                        (STD_OFF)

/* Pre-processor switch to define if the Mem driver functions are called using the Mem function pointer table API */
#define MEMACC_USE_MEM_FUNCPTR_TABLE                   (STD_OFF)

/* Pre-processor switch to enable/disable the function MemAcc_Compare() */
#define MEMACC_COMPARE_API                             (STD_OFF)

/* OsIf counter type used in timeout detection for MemAcc operations */
#define MEMACC_TIMEOUT_TYPE                            (OSIF_COUNTER_DUMMY)

/* Define support for 32 or 64Bit address type */
#define MEMACC_ADDRESSTYPE                             uint32
#define MEMACC_LENGTHTYPE                              uint32

/*Mem drivers hardware ID list*/
#define MEMACC_MEM_43_INFLS_DRIVER_ID                         (0U)

/* Number of hardware resources which are provided by Mem drivers */
#define MEMACC_MEM_HW_RESOURCE_COUNT                   (1U)

/* The unique numeric identifiers for each hardware resource */
#define  MEMACC_MEM_43_INFLS_MEMINSTANCE_0_ID                          (0U)

/* Enable multicore core synchronization feature. */
#define MEMACC_MULTICORE_TYPE_1_ENABLED                (STD_OFF)

/* Pre-processor switch to enable and disable multicore function from the driver */
#define MEMACC_MULTICORE_TYPE_3_ENABLED                (STD_OFF)
/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* MEMACC_CFG_DEFINES_H */

