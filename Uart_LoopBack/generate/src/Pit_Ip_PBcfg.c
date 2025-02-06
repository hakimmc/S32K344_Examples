/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : Stm_Pit_Rtc_Emios
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 3.0.0
* Build Version : S32K3_RTD_3_0_0_D2303_ASR_REL_4_7_REV_0000_20230331
*
* Copyright 2020 - 2023 NXP Semiconductors
*
* NXP Confidential. This software is owned or controlled by NXP and may only be
* used strictly in accordance with the applicable license terms. By expressly
* accepting such terms or by downloading, installing, activating and/or otherwise
* using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms. If you do not agree to be
* bound by the applicable license terms, then you may not retain, install,
* activate or otherwise use the software.
==================================================================================================*/
/**
 *   @file          Pit_Ip_PBcfg.c
 *
 *   @addtogroup    pit_ip Pit IPL
 *
 *   @{
 */

/*==================================================================================================
 *                              GENERATION MACRO DEFINTION
 *================================================================================================*/



/*==================================================================================================*/
#ifdef __cplusplus
extern "C"{
#endif

 /*==================================================================================================
 *                                         INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *================================================================================================*/
#include "Pit_Ip_PBcfg.h"

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *================================================================================================*/
#define PIT_IP_VENDOR_ID_PBCFG_C                    43
#define PIT_IP_AR_RELEASE_MAJOR_VERSION_PBCFG_C     4
#define PIT_IP_AR_RELEASE_MINOR_VERSION_PBCFG_C     7
#define PIT_IP_AR_RELEASE_REVISION_VERSION_PBCFG_C  0
#define PIT_IP_SW_MAJOR_VERSION_PBCFG_C             3
#define PIT_IP_SW_MINOR_VERSION_PBCFG_C             0
#define PIT_IP_SW_PATCH_VERSION_PBCFG_C             0
/*==================================================================================================
 *                                      FILE VERSION CHECKS
 *================================================================================================*/
#if (PIT_IP_VENDOR_ID_PBCFG_C != PIT_IP_VENDOR_ID_PBCFG_H)
    #error "Pit_Ip_PBcfg.c and Pit_Ip_PBcfg.h have different vendor ids"
#endif
/* Check if this header file and header file are of the same Autosar version */
#if ((PIT_IP_AR_RELEASE_MAJOR_VERSION_PBCFG_C != PIT_IP_AR_RELEASE_MAJOR_VERSION_PBCFG_H) || \
     (PIT_IP_AR_RELEASE_MINOR_VERSION_PBCFG_C != PIT_IP_AR_RELEASE_MINOR_VERSION_PBCFG_H) || \
     (PIT_IP_AR_RELEASE_REVISION_VERSION_PBCFG_C != PIT_IP_AR_RELEASE_REVISION_VERSION_PBCFG_H) \
    )
    #error "AutoSar Version Numbers of Pit_Ip_PBcfg.c and Pit_Ip_PBcfg.h are different"
#endif
/* Check if this header file and header file are of the same Software version */
#if ((PIT_IP_SW_MAJOR_VERSION_PBCFG_C != PIT_IP_SW_MAJOR_VERSION_PBCFG_H) || \
     (PIT_IP_SW_MINOR_VERSION_PBCFG_C != PIT_IP_SW_MINOR_VERSION_PBCFG_H) || \
     (PIT_IP_SW_PATCH_VERSION_PBCFG_C != PIT_IP_SW_PATCH_VERSION_PBCFG_H) \
    )
    #error "Software Version Numbers of Pit_Ip_PBcfg.c and Pit_Ip_PBcfg.h are different"
#endif
/*================================================================================================*/

/*==================================================================================================
 *                                       GLOBAL VARIABLES
 *================================================================================================*/
#define GPT_START_SEC_CODE
#include "Gpt_MemMap.h"
extern void PitNotification(uint8 channel); 
#define GPT_STOP_SEC_CODE
#include "Gpt_MemMap.h"

/*==================================================================================================
 *                                       GLOBAL CONSTANTS
 *================================================================================================*/
#define GPT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"


const Pit_Ip_InstanceConfigType PIT_0_InitConfig_PB =
{
    /** @brief PIT Standard Timer */
#if(defined (PIT_IP_MDIS_BIT_EXISTS) && (PIT_IP_MDIS_BIT_EXISTS == STD_ON))
    (boolean)(TRUE), /* Enable standard timer */
#endif
#if(defined (PIT_IP_RTI_USED) && (PIT_IP_RTI_USED == STD_ON))
    (boolean)(FALSE), /* Disable real time interrupt timer */
#endif
    /** @brief PIT Debug Mode */
    (boolean)(FALSE) /* Enable/Disable Freeze Bit */
}; 

const Pit_Ip_ChannelConfigType PIT_0_ChannelConfig_PB[1U] =
{
    /**@brief PitChannel_0 */ 
    {
        /** @brief PIT Channel Id */
        0U,
        /** @brief PIT Enable Interrupt */
        (boolean)(TRUE),
        /** @brief PIT callback name */
        &PitNotification,
        /** @brief PIT callbackparam  */
        (uint8)0U,
        /** @brief PIT channel mode  */
        PIT_IP_CH_MODE_CONTINUOUS
    }
};
#define GPT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"

/*==================================================================================================
 *                                       GLOBAL FUNCTIONS
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL VARIABLES
 *================================================================================================*/

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL MACROS
 *================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 *================================================================================================*/

/*==================================================================================================
 *                                       LOCAL FUNCTIONS
 *================================================================================================*/

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 *================================================================================================*/

#ifdef __cplusplus
}
#endif /* PIT_IP_PBCFG_C */

/** @} */

