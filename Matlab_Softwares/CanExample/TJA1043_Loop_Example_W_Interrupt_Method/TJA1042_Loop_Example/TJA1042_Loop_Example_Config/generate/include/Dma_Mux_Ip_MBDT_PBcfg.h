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

#ifndef DMA_MUX_IP_MBDT_PBCFG_H
#define DMA_MUX_IP_MBDT_PBCFG_H

/**
*   @file Dma_Mux_Ip_MBDT_PBcfg.h
*
*   @addtogroup DMA_MUX_IP DMA_MUX IPV Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RM_DMA_MUX_IP_MBDT_PBCFG_VENDOR_ID                    43
#define RM_DMA_MUX_IP_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION     4
#define RM_DMA_MUX_IP_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION     7
#define RM_DMA_MUX_IP_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION  0
#define RM_DMA_MUX_IP_MBDT_PBCFG_SW_MAJOR_VERSION             5
#define RM_DMA_MUX_IP_MBDT_PBCFG_SW_MINOR_VERSION             0
#define RM_DMA_MUX_IP_MBDT_PBCFG_SW_PATCH_VERSION             0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/** @brief    Declaration of the configuration structure for Dma Mux Ip */
#define DMA_MUX_CONFIG_MBDT_PB \
    extern const Dma_Mux_Ip_ConfigType Dma_Mux_Config_MBDT;

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* DMA_MUX_IP_MBDT_PBCFG_H */

