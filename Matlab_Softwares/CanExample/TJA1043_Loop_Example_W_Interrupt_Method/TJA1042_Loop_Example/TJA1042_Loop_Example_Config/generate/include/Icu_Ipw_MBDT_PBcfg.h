/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : Emios Siul2 Wkpu LpCmp
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

#ifndef ICU_IPW_MBDT_PBCFG_H
#define ICU_IPW_MBDT_PBCFG_H

/**
 *   @file           Icu_Ipw_MBDT_PBcfg.h
 *   @version        5.0.0
 *
 *   @brief          AUTOSAR Icu  - Icu driver configuration header file.
 *   @details        Contains the information that will be exported by the module, as requested by Autosar.
 *   @internal
 *   @addtogroup     icu_ipw
 *   @{
 */

#ifdef __cplusplus
extern "C"{
#endif

 /*==================================================================================================
 *                                         INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define ICU_IPW_MBDT_PBCFG_VENDOR_ID                    43
#define ICU_IPW_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION     4
#define ICU_IPW_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION     7
#define ICU_IPW_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION  0
#define ICU_IPW_MBDT_PBCFG_SW_MAJOR_VERSION             5
#define ICU_IPW_MBDT_PBCFG_SW_MINOR_VERSION             0
#define ICU_IPW_MBDT_PBCFG_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
 *                                       CONSTANTS
 *================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ICU_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Icu_MemMap.h"

extern const Icu_Ipw_ChannelConfigType Icu_Ipw_IpChannelConfig_PB_MBDT[4U];
extern const Icu_Ipw_IpConfigType Icu_Ipw_IpConfig_PB_MBDT[3U];

#define ICU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Icu_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* ICU_IPW_MBDT_PBCFG_H */

