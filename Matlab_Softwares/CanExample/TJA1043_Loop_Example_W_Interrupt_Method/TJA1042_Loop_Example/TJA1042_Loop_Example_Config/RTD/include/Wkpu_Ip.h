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

#ifndef WKPU_IP_H
#define WKPU_IP_H

/**
 *     @file
 *
 *     @addtogroup wkpu_icu_ip WKPU IPL
 *     @{
 */

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                          INCLUDE FILES
==================================================================================================*/
#include "Wkpu_Ip_Cfg.h"

#if (STD_ON == WKPU_IP_USED)
    #if (defined (WKPU_IP_ENABLE_USER_MODE_SUPPORT))
        #if (STD_ON == WKPU_IP_ENABLE_USER_MODE_SUPPORT)
            #include "Reg_eSys.h"
        #endif
    #endif
#endif /* WKPU_IP_USED */
/*==================================================================================================
*                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define WKPU_IP_VENDOR_ID                      43
#define WKPU_IP_AR_RELEASE_MAJOR_VERSION       4
#define WKPU_IP_AR_RELEASE_MINOR_VERSION       7
#define WKPU_IP_AR_RELEASE_REVISION_VERSION    0
#define WKPU_IP_SW_MAJOR_VERSION               5
#define WKPU_IP_SW_MINOR_VERSION               0
#define WKPU_IP_SW_PATCH_VERSION               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ICU header file are of the same vendor */
#if (WKPU_IP_VENDOR_ID != WKPU_IP_CFG_VENDOR_ID)
    #error "Wkpu_Ip.h and Wkpu_Ip_Cfg.h have different vendor IDs"
#endif
/* Check if source file and ICU header file are of the same AutoSar version */
#if ((WKPU_IP_AR_RELEASE_MAJOR_VERSION  != WKPU_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (WKPU_IP_AR_RELEASE_MINOR_VERSION  != WKPU_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (WKPU_IP_AR_RELEASE_REVISION_VERSION   != WKPU_IP_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Wkpu_Ip.h and Wkpu_Ip_Cfg.h are different"
#endif
/* Check if source file and ICU header file are of the same Software version */
#if ((WKPU_IP_SW_MAJOR_VERSION  != WKPU_IP_CFG_SW_MAJOR_VERSION) || \
     (WKPU_IP_SW_MINOR_VERSION  != WKPU_IP_CFG_SW_MINOR_VERSION) || \
     (WKPU_IP_SW_PATCH_VERSION  != WKPU_IP_CFG_SW_PATCH_VERSION))
#error "Software Version Numbers of Wkpu_Ip.h and Wkpu_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if (STD_ON == WKPU_IP_USED)
        #if (defined (WKPU_IP_ENABLE_USER_MODE_SUPPORT))
            #if (STD_ON == WKPU_IP_ENABLE_USER_MODE_SUPPORT)
            /* Check if header file and Reg_eSys.h file are of the same Autosar version */
                #if ((WKPU_IP_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
                    (WKPU_IP_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION))
                    #error "AutoSar Version Numbers of Ftm_Icu_Ip.h and Reg_eSys.h are different"
                #endif
            #endif
        #endif
    #endif /* WKPU_IP_USED */
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        DEFINES AND MACROS
==================================================================================================*/
#if (STD_ON == WKPU_IP_USED)

#if (defined WKPU_CONFIG_EXT)
#define ICU_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Icu_MemMap.h"

/* Macro used to import WKPU generated configurations. */
WKPU_CONFIG_EXT

#define ICU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Icu_MemMap.h"
#endif
/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#if (WKPU_IP_NO_CACHE_USED == STD_ON)
    #define ICU_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#else
    #define ICU_START_SEC_VAR_CLEARED_UNSPECIFIED
#endif
#include "Icu_MemMap.h"

/* Table of initialized WKPU channels */
extern Wkpu_Ip_State Wkpu_Ip_u32ChState[WKPU_IP_NUM_OF_CHANNELS_USED];

#if (WKPU_IP_NO_CACHE_USED == STD_ON)
    #define ICU_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#else
    #define ICU_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#endif
#include "Icu_MemMap.h"

#if (WKPU_IP_NO_CACHE_USED == STD_ON)
    #define ICU_START_SEC_VAR_INIT_8_NO_CACHEABLE
#else
    #define ICU_START_SEC_VAR_INIT_8
#endif
#include "Icu_MemMap.h"

/* This array stores the positions in the Wkpu_Ip_u32ChState array of the configured Wkpu channels. */
extern uint8 Wkpu_Ip_IndexInChState[WKPU_IP_NUM_OF_CHANNELS];

#if (WKPU_IP_NO_CACHE_USED == STD_ON)
    #define ICU_STOP_SEC_VAR_INIT_8_NO_CACHEABLE
#else
    #define ICU_STOP_SEC_VAR_INIT_8
#endif
#include "Icu_MemMap.h"

#define ICU_START_SEC_CONST_UNSPECIFIED
#include "Icu_MemMap.h"

extern WKPU_Type * const Wkpu_Ip_apxBase[];

#define ICU_STOP_SEC_CONST_UNSPECIFIED
#include "Icu_MemMap.h"
/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/
#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"

#ifdef WKPU_IP_SUPPORT_INTERRUPT_REQUEST

/**
 * @brief      Enable the interrupt request and wakeup generation.
 * @details    This function setup generation of interrupt and wakeup generation.
 *
 * @param[in]  instance  Hardware instance of WKPU used. 
 * @param[in]  hwChannel Hardware channel of WKPU used.
 * @return     void
 */
void Wkpu_Ip_EnableInterrupt(uint8 instance, uint8 hwChannel);

/**
 * @brief      ICU driver function that disables the interrupt of a WKPU channel.
 * @details    This function disables WKPU Channel Interrupt.
 *
 * @param[in]  instance  Hardware instance of WKPU used. 
 * @param[in]  hwChannel Hardware channel of WKPU used.
 * @return     void
 */
void Wkpu_Ip_DisableInterrupt(uint8 instance, uint8 hwChannel);

/**
 * @brief      Icu driver function that initializes WKPU channels.
 * @details    This function:
 *              - Sets Interrupt Filter Enable Register
 *              - Sets Wakeup/Interrupt Pull-up Enable Register
 *              - Sets Activation Condition
 *
 * @param[in]  instance  Hardware instance of WKPU used. 
 * @param[in]  userConfig - Pointer to array of with channels configuration.
 * @return     void
 */
Wkpu_Ip_StatusType Wkpu_Ip_Init(uint8 instance, const Wkpu_Ip_IrqConfigType* userConfig);

/**
 * @brief      ICU driver function that resets WKPU configuration.
 * @details    This function:
 *              - Disables IRQ Interrupt
 *              - Clears Wakeup/Interrupt Filter Enable Register
 *              - Clears Wakeup/Interrupt Pull-up Enable Register
 *              - Clears edge event enable registers
 *              - Clear Interrupt Filter Enable Register
 *
 * @param[in]  instance Hardware instance of WKPU used. 
 * @return     void
 */
Wkpu_Ip_StatusType Wkpu_Ip_DeInit(uint8 instance);

/**
 * @brief      ICU driver function that sets activation condition of WKPU channel.
 * @details    This function enables the requested activation condition(rising, falling or both edges)
 *             for corresponding WKPU channels.
 *
 * @param[in]  instance  Hardware instance of WKPU used. 
 * @param[in]  hwChannel Hardware channel of WKPU used.
 * @param[in]  edge      Edge type for activation.
 * @return     void
 */
void Wkpu_Ip_SetActivationCondition(uint8 instance, uint8 hwChannel, Wkpu_Ip_EdgeType edge);

/**
 * @brief      ICU driver function that gets the input state of WKPU channel.
 * @details    This function:
 *             - Checks if interrupt flags for corresponding WKPU channel is set then
 *             it clears the interrupt flag and returns the value as TRUE.
 *
 * @param[in]  instance  Hardware instance of WKPU used. 
 * @param[in]  hwChannel Hardware channel of WKPU used.
 * @return     boolean
 *              - TRUE - if channel is active
 *              - FALSE - If channel is in idle
 */
boolean Wkpu_Ip_GetInputState(uint8 instance, uint8 hwChannel);

/**
 * @brief      Driver function Enable Notification for timestamp.
 */
void Wkpu_Ip_EnableNotification(uint8 hwChannel);

/**
 * @brief      Driver function Disable Notification for timestamp.
 */
void Wkpu_Ip_DisableNotification(uint8 hwChannel);

#endif /* WKPU_IP_SUPPORT_INTERRUPT_REQUEST */

#if (defined (WKPU_IP_NMI_API) && (STD_ON == WKPU_IP_NMI_API))
Wkpu_Ip_StatusType Wkpu_Ip_InitNMI(uint8 instance, const Wkpu_Ip_IrqConfigType* userConfig);
Wkpu_Ip_StatusType Wkpu_Ip_DeinitNMI(uint8 instance);
#endif

#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#endif /* WKPU_IP_USED */

#ifdef __cplusplus
}
#endif

/** @} */

#endif  /* WKPU_IP_H */
