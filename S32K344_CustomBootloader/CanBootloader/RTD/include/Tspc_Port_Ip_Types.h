/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 2.0.0
*   Build Version        : S32K3_RTD_2_0_0_D2203_ASR_REL_4_4_REV_0000_20220331
*
*   (c) Copyright 2020 - 2022 NXP Semiconductors
*   All Rights Reserved.
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef TSPC_PORT_IP_TYPES_H
#define TSPC_PORT_IP_TYPES_H

/**
*   @file    Tspc_Port_Ip_Types.h
*
*   @defgroup Tspc_IPL TSPC IPL
*   @{
*/

#if defined(__cplusplus)
extern "C" {
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "StandardTypes.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
 * @brief Parameters that shall be published within the driver header file and also in the
 *        module's description file
 */
#define TSPC_PORT_IP_TYPES_VENDOR_ID_H                     43
#define TSPC_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H      4
#define TSPC_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H      4
#define TSPC_PORT_IP_TYPES_AR_RELEASE_REVISION_VERSION_H   0
#define TSPC_PORT_IP_TYPES_SW_MAJOR_VERSION_H              2
#define TSPC_PORT_IP_TYPES_SW_MINOR_VERSION_H              0
#define TSPC_PORT_IP_TYPES_SW_PATCH_VERSION_H              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Tspc_Port_Ip_Types.h and StandardTypes.h are of the same version */
    #if ((TSPC_PORT_IP_TYPES_AR_RELEASE_MAJOR_VERSION_H != STD_AR_RELEASE_MAJOR_VERSION) || \
         (TSPC_PORT_IP_TYPES_AR_RELEASE_MINOR_VERSION_H != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Tspc_Port_Ip_Types.h and StandardTypes.h are different"
    #endif
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define TSPC_INVALID_GROUP_INDEX (0xFFFFU)

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct
{
    uint8                       obeGroupSelect;    /*!< obeGroup number */
    uint32                      obeGroupIndex;     /*!< obeGroupIndex number */
} Tspc_Port_Ip_ObeGroupConfig;
/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/


#if defined(__cplusplus)
}
#endif

/** @} */

#endif /* TSPC_PORT_IP_TYPES_H */
