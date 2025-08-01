/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
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

#ifndef XRDC_IP_CFG_H
#define XRDC_IP_CFG_H

/**
*   @file Xrdc_Ip_Cfg.h
*
*   @addtogroup XRDC_IP XRDC IPV Driver
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"

#include "Xrdc_Ip_MBDT_PBcfg.h"
#include "Xrdc_Ip_Types.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RM_XRDC_IP_CFG_VENDOR_ID                    43
#define RM_XRDC_IP_CFG_AR_RELEASE_MAJOR_VERSION     4
#define RM_XRDC_IP_CFG_AR_RELEASE_MINOR_VERSION     7
#define RM_XRDC_IP_CFG_AR_RELEASE_REVISION_VERSION  0
#define RM_XRDC_IP_CFG_SW_MAJOR_VERSION             5
#define RM_XRDC_IP_CFG_SW_MINOR_VERSION             0
#define RM_XRDC_IP_CFG_SW_PATCH_VERSION             0

/*==================================================================================================
*                                   FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Xrdc_Ip_MBDT_PBcfg.h */
#if (RM_XRDC_IP_CFG_VENDOR_ID != RM_XRDC_IP_PBCFG_MBDT_VENDOR_ID)
    #error "Xrdc_Ip_Cfg.h and Xrdc_Ip_MBDT_PBcfg.h have different vendor ids"
#endif
#if ((RM_XRDC_IP_CFG_AR_RELEASE_MAJOR_VERSION    != RM_XRDC_IP_PBCFG_MBDT_AR_RELEASE_MAJOR_VERSION) || \
     (RM_XRDC_IP_CFG_AR_RELEASE_MINOR_VERSION    != RM_XRDC_IP_PBCFG_MBDT_AR_RELEASE_MINOR_VERSION) || \
     (RM_XRDC_IP_CFG_AR_RELEASE_REVISION_VERSION != RM_XRDC_IP_PBCFG_MBDT_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Xrdc_Ip_Cfg.h and Xrdc_Ip_MBDT_PBcfg.h are different"
#endif
#if ((RM_XRDC_IP_CFG_SW_MAJOR_VERSION != RM_XRDC_IP_PBCFG_MBDT_SW_MAJOR_VERSION) || \
     (RM_XRDC_IP_CFG_SW_MINOR_VERSION != RM_XRDC_IP_PBCFG_MBDT_SW_MINOR_VERSION) || \
     (RM_XRDC_IP_CFG_SW_PATCH_VERSION != RM_XRDC_IP_PBCFG_MBDT_SW_PATCH_VERSION))
    #error "Software Version Numbers of Xrdc_Ip_Cfg.h and Xrdc_Ip_MBDT_PBcfg.h are different"
#endif


#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((RM_XRDC_IP_CFG_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (RM_XRDC_IP_CFG_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Xrdc_Ip_Cfg.h and Mcal.h are different"
    #endif
#endif

/* Checks against Xrdc_Ip_Types.h */
#if (RM_XRDC_IP_CFG_VENDOR_ID != RM_XRDC_IP_TYPES_VENDOR_ID)
    #error "Xrdc_Ip_Cfg.h and Xrdc_Ip_Types.h have different vendor ids"
#endif
#if ((RM_XRDC_IP_CFG_AR_RELEASE_MAJOR_VERSION    != RM_XRDC_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (RM_XRDC_IP_CFG_AR_RELEASE_MINOR_VERSION    != RM_XRDC_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (RM_XRDC_IP_CFG_AR_RELEASE_REVISION_VERSION != RM_XRDC_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Xrdc_Ip_Cfg.h and Xrdc_Ip_Types.h are different"
#endif
#if ((RM_XRDC_IP_CFG_SW_MAJOR_VERSION != RM_XRDC_IP_TYPES_SW_MAJOR_VERSION) || \
     (RM_XRDC_IP_CFG_SW_MINOR_VERSION != RM_XRDC_IP_TYPES_SW_MINOR_VERSION) || \
     (RM_XRDC_IP_CFG_SW_PATCH_VERSION != RM_XRDC_IP_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Xrdc_Ip_Cfg.h and Xrdc_Ip_Types.h are different"
#endif

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
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
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif /* __cplusplus */

/** @} */

#endif /* XRDC_IP_CFG_H */

