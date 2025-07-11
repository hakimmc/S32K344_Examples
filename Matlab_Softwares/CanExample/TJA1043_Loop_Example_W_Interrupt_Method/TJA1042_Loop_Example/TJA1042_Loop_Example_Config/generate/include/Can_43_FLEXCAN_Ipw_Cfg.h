/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : FLEXCAN
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

#ifndef CAN_43_FLEXCAN_IPW_CFG_H
#define CAN_43_FLEXCAN_IPW_CFG_H

/**
*   @file
*
*   @addtogroup CAN_DRIVER_CONFIGURATION Can Driver Configurations
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
#include "Std_Types.h"
#include "FlexCAN_Ip_Cfg.h"
#include "Can_43_FLEXCAN_Ipw_MBDT_PBcfg.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CAN_43_FLEXCAN_IPW_CFG_VENDOR_ID                    43
#define CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_MAJOR_VERSION     4
#define CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_MINOR_VERSION     7
#define CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_REVISION_VERSION  0
#define CAN_43_FLEXCAN_IPW_CFG_SW_MAJOR_VERSION             5
#define CAN_43_FLEXCAN_IPW_CFG_SW_MINOR_VERSION             0
#define CAN_43_FLEXCAN_IPW_CFG_SW_PATCH_VERSION             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Checks against FlexCAN_Ip_Cfg.h */
#if (CAN_43_FLEXCAN_IPW_CFG_VENDOR_ID != FLEXCAN_IP_CFG_VENDOR_ID_H)
    #error "Can_43_FLEXCAN_Ipw_Cfg.h and FlexCAN_Ip_Cfg.h have different vendor ids"
#endif
#if ((CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_MAJOR_VERSION    != FLEXCAN_IP_CFG_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_MINOR_VERSION    != FLEXCAN_IP_CFG_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_REVISION_VERSION != FLEXCAN_IP_CFG_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Can_43_FLEXCAN_Ipw_Cfg.h and FlexCAN_Ip_Cfg.h are different"
#endif
#if ((CAN_43_FLEXCAN_IPW_CFG_SW_MAJOR_VERSION != FLEXCAN_IP_CFG_SW_MAJOR_VERSION_H) || \
     (CAN_43_FLEXCAN_IPW_CFG_SW_MINOR_VERSION != FLEXCAN_IP_CFG_SW_MINOR_VERSION_H) || \
     (CAN_43_FLEXCAN_IPW_CFG_SW_PATCH_VERSION != FLEXCAN_IP_CFG_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Can_43_FLEXCAN_Ipw_Cfg.h and FlexCAN_Ip_Cfg.h are different"
#endif
/* Checks against Can_43_FLEXCAN_Ipw_MBDT_PBcfg.h */
#if (CAN_43_FLEXCAN_IPW_CFG_VENDOR_ID != CAN_43_FLEXCAN_VENDOR_ID_MBDT_IPW_PBCFG_H)
    #error "Can_43_FLEXCAN_Ipw_Cfg.h and Can_43_FLEXCAN_Ipw_MBDT_PBcfg.h have different vendor ids"
#endif
#if ((CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_MAJOR_VERSION    != CAN_43_FLEXCAN_AR_RELEASE_MAJOR_VERSION_MBDT_IPW_PBCFG_H) || \
     (CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_MINOR_VERSION    != CAN_43_FLEXCAN_AR_RELEASE_MINOR_VERSION_MBDT_IPW_PBCFG_H) || \
     (CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_REVISION_VERSION != CAN_43_FLEXCAN_AR_RELEASE_REVISION_VERSION_MBDT_IPW_PBCFG_H) \
    )
    #error "AutoSar Version Numbers of Can_43_FLEXCAN_Ipw_Cfg.h and Can_43_FLEXCAN_Ipw_MBDT_PBcfg.h are different"
#endif
#if ((CAN_43_FLEXCAN_IPW_CFG_SW_MAJOR_VERSION != CAN_43_FLEXCAN_SW_MAJOR_VERSION_MBDT_IPW_PBCFG_H) || \
     (CAN_43_FLEXCAN_IPW_CFG_SW_MINOR_VERSION != CAN_43_FLEXCAN_SW_MINOR_VERSION_MBDT_IPW_PBCFG_H) || \
     (CAN_43_FLEXCAN_IPW_CFG_SW_PATCH_VERSION != CAN_43_FLEXCAN_SW_PATCH_VERSION_MBDT_IPW_PBCFG_H) \
    )
    #error "Software Version Numbers of Can_43_FLEXCAN_Ipw_Cfg.h and Can_43_FLEXCAN_Ipw_MBDT_PBcfg.h are different"
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Std_Types.h */
    #if ((CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_MAJOR_VERSION    != STD_AR_RELEASE_MAJOR_VERSION) || \
         (CAN_43_FLEXCAN_IPW_CFG_AR_RELEASE_MINOR_VERSION    != STD_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Can_43_FLEXCAN_Ipw_Cfg.h and Std_Types.h are different"
    #endif
#endif
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define CAN_43_FLEXCAN_USE_FLEXCAN_IP                     (STD_ON)
#define CAN_43_FLEXCAN_USE_CANEXCEL_IP                    (STD_OFF)
#define CAN_43_FLEXCAN_MB_INTERRUPT_SUPPORT               (STD_ON)
#define CAN_43_FLEXCAN_ERROR_INTERRUPT_SUPPORT            FLEXCAN_IP_ERROR_INTERRUPT_SUPPORT
#define CAN_43_FLEXCAN_BUSOFF_INTERRUPT_SUPPORT           FLEXCAN_IP_BUSOFF_INTERRUPT_SUPPORT
#define CAN_43_FLEXCAN_FEATURE_HAS_DMA_ENABLE             (STD_OFF)
#define CAN_43_FLEXCAN_FEATURE_HAS_PRETENDED_NETWORKING   (STD_OFF) 
#define CAN_43_FLEXCAN_FEATURE_HAS_ENHANCED_RX_FIFO       FLEXCAN_IP_FEATURE_HAS_ENHANCED_RX_FIFO
#define CAN_43_FLEXCAN_MB_ENHANCED_RXFIFO                 FLEXCAN_IP_MB_ENHANCED_RXFIFO
#define CAN_43_FLEXCAN_FEATURE_HAS_FD                     FLEXCAN_IP_FEATURE_HAS_FD

#define CAN_43_FLEXCAN_IPW_EXT \
CAN_43_FLEXCAN_IPW_CONFIG_MBDT_PB 
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
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* CAN_IPW_CFG_H */

