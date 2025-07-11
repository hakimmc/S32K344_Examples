/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : Stm_Pit_Rtc_Emios
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 5.0.0
* Build Version : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
* used strictly in accordance with the applicable license terms. By expressly
* accepting such terms or by downloading, installing, activating and/or otherwise
* using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms. If you do not agree to be
* bound by the applicable license terms, then you may not retain, install,
* activate or otherwise use the software.
==================================================================================================*/
/**
*   @file           Gpt_PBcfg.c
*
*   @addtogroup     gpt Gpt Driver
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
===================================================================================================*/
#include "Gpt.h"
#include "Gpt_Ipw_MBDT_PBcfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define GPT_VENDOR_ID_MBDT_PBCFG_C                      43
#define GPT_AR_RELEASE_MAJOR_VERSION_MBDT_PBCFG_C       4
#define GPT_AR_RELEASE_MINOR_VERSION_MBDT_PBCFG_C       7
#define GPT_AR_RELEASE_REVISION_VERSION_MBDT_PBCFG_C    0
#define GPT_SW_MAJOR_VERSION_MBDT_PBCFG_C               5
#define GPT_SW_MINOR_VERSION_MBDT_PBCFG_C               0
#define GPT_SW_PATCH_VERSION_MBDT_PBCFG_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if Gpt_PBcfg.c file and Gpt.h header file are of the same vendor */
#if (GPT_VENDOR_ID_MBDT_PBCFG_C != GPT_VENDOR_ID)
    #error "Gpt_MBDT_PBcfg.c and Gpt.h have different vendor ids"
#endif
/* Check if Gpt_PBcfg.c file and Gpt.h header file are of the same Autosar version */
#if ((GPT_AR_RELEASE_MAJOR_VERSION_MBDT_PBCFG_C != GPT_AR_RELEASE_MAJOR_VERSION) || \
     (GPT_AR_RELEASE_MINOR_VERSION_MBDT_PBCFG_C != GPT_AR_RELEASE_MINOR_VERSION) || \
     (GPT_AR_RELEASE_REVISION_VERSION_MBDT_PBCFG_C != GPT_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Gpt_MBDT_PBcfg.c and Gpt.h are different"
#endif
/* Check if Gpt_PBcfg.c file and Gpt.h header file are of the same Software version */
#if ((GPT_SW_MAJOR_VERSION_MBDT_PBCFG_C != GPT_SW_MAJOR_VERSION) || \
     (GPT_SW_MINOR_VERSION_MBDT_PBCFG_C != GPT_SW_MINOR_VERSION) || \
     (GPT_SW_PATCH_VERSION_MBDT_PBCFG_C != GPT_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Gpt_MBDT_PBcfg.c and Gpt.h are different"
#endif

#if (GPT_IPW_VENDOR_ID_MBDT_PBCFG_H != GPT_VENDOR_ID_MBDT_PBCFG_C)
    #error "Gpt_Ipw_MBDT_PBcfg.h and Gpt_MBDT_PBcfg.c have different vendor ids"
#endif
/* Check if the header files are of the same Autosar version */
#if ((GPT_IPW_AR_RELEASE_MAJOR_VERSION_MBDT_PBCFG_H != GPT_AR_RELEASE_MAJOR_VERSION_MBDT_PBCFG_C) || \
     (GPT_IPW_AR_RELEASE_MINOR_VERSION_MBDT_PBCFG_H != GPT_AR_RELEASE_MINOR_VERSION_MBDT_PBCFG_C) || \
     (GPT_IPW_AR_RELEASE_REVISION_VERSION_MBDT_PBCFG_H != GPT_AR_RELEASE_REVISION_VERSION_MBDT_PBCFG_C) \
    )
    #error "AutoSar Version Numbers of Gpt_Ipw_MBDT_PBcfg.h and Gpt_MBDT_PBcfg.c are different"
#endif
/* Check if the header files are of the same Software version */
#if ((GPT_IPW_SW_MAJOR_VERSION_MBDT_PBCFG_H != GPT_SW_MAJOR_VERSION_MBDT_PBCFG_C) || \
     (GPT_IPW_SW_MINOR_VERSION_MBDT_PBCFG_H != GPT_SW_MINOR_VERSION_MBDT_PBCFG_C) || \
     (GPT_IPW_SW_PATCH_VERSION_MBDT_PBCFG_H != GPT_SW_PATCH_VERSION_MBDT_PBCFG_C) \
    )
    #error "Software Version Numbers of Gpt_Ipw_MBDT_PBcfg.h and Gpt_MBDT_PBcfg.c are different"
#endif
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
/**
*
* @brief The callback functions defined by the user to be called as channel notifications
*/
extern void Gpt_PitNotification(void);
extern void MBDT_Step_Handler(void);

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/
#define GPT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"
/* Number of channels per variant without partitions */
#define GPT_CONF_CHANNELS_PB_MBDT    4U
#define GPT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"

#define GPT_START_SEC_CONST_UNSPECIFIED
#include "Gpt_MemMap.h"
#if(GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)

/*Predefined timer configuration structure.*/
static const Gpt_HwPredefChannelConfigType *const Gpt_pInitPredefTimerChannelPB_MBDT[GPT_HW_PREDEFTIMER_NUM]=
{
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR
};
#endif /*GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON*/

/*
*   @brief Translation LUT for Logical channel number to Partition Configuration indexed location
*/
static const uint8 u8GptChannelIdToIndexMap_MBDT[GPT_NUM_CONFIG] = 
{
    0, /* Logical Channel GptChannelConfiguration_0*/
    1, /* Logical Channel GptChannelConfiguration_1*/
    2, /* Logical Channel StepTimer*/
    3  /* Logical Channel ProfilerTimer*/
};

#define GPT_STOP_SEC_CONST_UNSPECIFIED
#include "Gpt_MemMap.h"

#define GPT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"
static const Gpt_ChannelConfigType Gpt_InitChannelPB_MBDT[GPT_CONF_CHANNELS_PB_MBDT] =
{
    {   /*GptChannelConfiguration_0 configuration data*/
        (boolean)FALSE, /* Wakeup capability */
        &Gpt_PitNotification, /* Channel notification */
#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
        (EcuM_WakeupSourceType)0U, /* Wakeup information */
#endif
        (Gpt_ValueType)(4294967295U), /* Maximum ticks value*/
        (GPT_CH_MODE_CONTINUOUS), /* Timer mode:continous/one-shot */
        &Gpt_Ipw_ChannelConfig_PB_MBDT[0U]
    }
,
    {   /*GptChannelConfiguration_1 configuration data*/
        (boolean)TRUE, /* Wakeup capability */
        NULL_PTR, /* Channel notification */
#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
        (EcuM_WakeupSourceType)((uint32)((uint32)1 << 0)), /* Wakeup information */
#endif
        (Gpt_ValueType)(4294967295U), /* Maximum ticks value*/
        (GPT_CH_MODE_ONESHOT), /* Timer mode:continous/one-shot */
        &Gpt_Ipw_ChannelConfig_PB_MBDT[1U]
    }
,
    {   /*StepTimer configuration data*/
        (boolean)FALSE, /* Wakeup capability */
        &MBDT_Step_Handler, /* Channel notification */
#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
        (EcuM_WakeupSourceType)0U, /* Wakeup information */
#endif
        (Gpt_ValueType)(4294967295U), /* Maximum ticks value*/
        (GPT_CH_MODE_CONTINUOUS), /* Timer mode:continous/one-shot */
        &Gpt_Ipw_ChannelConfig_PB_MBDT[2U]
    }
,
    {   /*ProfilerTimer configuration data*/
        (boolean)FALSE, /* Wakeup capability */
        NULL_PTR, /* Channel notification */
#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
        (EcuM_WakeupSourceType)0U, /* Wakeup information */
#endif
        (Gpt_ValueType)(4294967295U), /* Maximum ticks value*/
        (GPT_CH_MODE_CONTINUOUS), /* Timer mode:continous/one-shot */
        &Gpt_Ipw_ChannelConfig_PB_MBDT[3U]
    }
};

/**
* @brief        Gpt configuration type.
* @details      This is the type of the data structure including the configuration
*               set required for initializing the GPT driver.
*
*/
const Gpt_ConfigType Gpt_Config_MBDT =
{
    /** @brief Number of GPT channels (configured in tresos plugin builder)*/
    (Gpt_ChannelType)4U,
    /** @brief Pointer to the GPT channel configuration */
    &Gpt_InitChannelPB_MBDT,
    /** @brief Number of GPT instances (configured in tresos plugin builder)*/
    1U,
    /** @brief Pointer to the GPT instance configuration */
    &Gpt_Ipw_HwInstanceConfig_PB_MBDT,
#if(GPT_PREDEFTIMER_FUNCTIONALITY_API == STD_ON)
    /** @brief Pointer configuration of PredefTimer  */
    Gpt_pInitPredefTimerChannelPB_MBDT,
#endif
    /** @brief channel index in each partition map table*/
    &u8GptChannelIdToIndexMap_MBDT
};

#define GPT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Gpt_MemMap.h"

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
#endif /* GPT_PBCFG_C */
/** @} */

