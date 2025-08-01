/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : Emios Flexio FlexPwm eTpu
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

/**
*   @file Flexio_Pwm_Ip.c
*
*   @addtogroup flexio_pwm_ip FlexIO Pwm IPL
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
#include "Flexio_Pwm_Ip.h"
#include "Flexio_Pwm_Ip_HwAccess.h"
#if (FLEXIO_PWM_IP_USED_MCL == STD_ON)
#include "Flexio_Mcl_Ip_HwAccess.h"
#endif
#include "SchM_Pwm.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_PWM_IP_VENDOR_ID_C                      43
#define FLEXIO_PWM_IP_AR_RELEASE_MAJOR_VERSION_C       4
#define FLEXIO_PWM_IP_AR_RELEASE_MINOR_VERSION_C       7
#define FLEXIO_PWM_IP_AR_RELEASE_REVISION_VERSION_C    0
#define FLEXIO_PWM_IP_SW_MAJOR_VERSION_C               5
#define FLEXIO_PWM_IP_SW_MINOR_VERSION_C               0
#define FLEXIO_PWM_IP_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if (FLEXIO_PWM_IP_USED_MCL == STD_ON)
    /* Check if source file and Flexio_Mcl_Ip_HwAccess.h are of the same AUTOSAR version */
    #if ((FLEXIO_PWM_IP_AR_RELEASE_MAJOR_VERSION_C != FLEXIO_IP_HW_ACCESS_AR_RELEASE_MAJOR_VERSION) || \
         (FLEXIO_PWM_IP_AR_RELEASE_MINOR_VERSION_C != FLEXIO_IP_HW_ACCESS_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Flexio_Pwm_Ip_Types.h and Flexio_Mcl_Ip_HwAccess.h are different"
    #endif
#endif

    /* Check if source file and SchM_Pwm.h are of the same AUTOSAR version */
    #if ((FLEXIO_PWM_IP_AR_RELEASE_MAJOR_VERSION_C != SCHM_PWM_AR_RELEASE_MAJOR_VERSION) || \
         (FLEXIO_PWM_IP_AR_RELEASE_MINOR_VERSION_C != SCHM_PWM_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR version numbers of Flexio_Pwm_Ip.c and SchM_Pwm.h are different."
    #endif
#endif

/* Check if source file and Flexio_Pwm_Ip.h file are of the same vendor */
#if (FLEXIO_PWM_IP_VENDOR_ID_C != FLEXIO_PWM_IP_VENDOR_ID)
    #error "Vendor IDs of Flexio_Pwm_Ip.c and Flexio_Pwm_Ip.h are different."
#endif

/* Check if source file and Flexio_Pwm_Ip.h file are of the same AUTOSAR version */
#if ((FLEXIO_PWM_IP_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_PWM_IP_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_PWM_IP_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_PWM_IP_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_PWM_IP_AR_RELEASE_REVISION_VERSION_C != FLEXIO_PWM_IP_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR version numbers of Flexio_Pwm_Ip.c and Flexio_Pwm_Ip.h are different."
#endif

/* Check if source file and Flexio_Pwm_Ip.h file are of the same Software version */
#if ((FLEXIO_PWM_IP_SW_MAJOR_VERSION_C != FLEXIO_PWM_IP_SW_MAJOR_VERSION)  || \
     (FLEXIO_PWM_IP_SW_MINOR_VERSION_C != FLEXIO_PWM_IP_SW_MINOR_VERSION)  || \
     (FLEXIO_PWM_IP_SW_PATCH_VERSION_C != FLEXIO_PWM_IP_SW_PATCH_VERSION))
    #error "Software version numbers of Flexio_Pwm_Ip.c and Flexio_Pwm_Ip.h are different."
#endif

/* Check if source file and Flexio_Pwm_Ip_HwAccess.h file are of the same vendor */
#if (FLEXIO_PWM_IP_VENDOR_ID_C != FLEXIO_PWM_IP_HWACCESS_VENDOR_ID)
    #error "Vendor IDs of Flexio_Pwm_Ip.c and Flexio_Pwm_Ip_HwAccess.h are different."
#endif

/* Check if source file and Flexio_Pwm_Ip_HwAccess.h file are of the same AUTOSAR version */
#if ((FLEXIO_PWM_IP_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_PWM_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_PWM_IP_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_PWM_IP_HWACCESS_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_PWM_IP_AR_RELEASE_REVISION_VERSION_C != FLEXIO_PWM_IP_HWACCESS_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR version numbers of Flexio_Pwm_Ip.c and Flexio_Pwm_Ip_HwAccess.h are different."
#endif

/* Check if source file and Flexio_Pwm_Ip_HwAccess.h file are of the same Software version */
#if ((FLEXIO_PWM_IP_SW_MAJOR_VERSION_C != FLEXIO_PWM_IP_HWACCESS_SW_MAJOR_VERSION)  || \
     (FLEXIO_PWM_IP_SW_MINOR_VERSION_C != FLEXIO_PWM_IP_HWACCESS_SW_MINOR_VERSION)  || \
     (FLEXIO_PWM_IP_SW_PATCH_VERSION_C != FLEXIO_PWM_IP_HWACCESS_SW_PATCH_VERSION))
    #error "Software version numbers of Flexio_Pwm_Ip.c and Flexio_Pwm_Ip_HwAccess.h are different."
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/
#if (FLEXIO_PWM_IP_USED == STD_ON)
#define PWM_START_SEC_CONST_UNSPECIFIED
#include "Pwm_MemMap.h"

/** @brief Array with base addresses for Flexio instances available on platform */
Flexio_Pwm_Ip_HwAddrType * const Flexio_Pwm_Ip_aBasePtr[FLEXIO_PWM_IP_INSTANCE_COUNT] = IP_FLEXIO_BASE_PTRS;

#define PWM_STOP_SEC_CONST_UNSPECIFIED
#include "Pwm_MemMap.h"

#if (FLEXIO_PWM_IP_NO_CACHE_NEEDED == STD_ON)
    #define PWM_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#else
    #define PWM_START_SEC_VAR_CLEARED_UNSPECIFIED
#endif
#include "Pwm_MemMap.h"

/** @brief Array with pointers to user cfg structs*/
const Flexio_Pwm_Ip_ChannelConfigType * Flexio_Pwm_Ip_aState[FLEXIO_PWM_IP_CHANNEL_COUNT];

#if (FLEXIO_PWM_IP_NO_CACHE_NEEDED == STD_ON)
    #define PWM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#else
    #define PWM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#endif
#include "Pwm_MemMap.h"

#if (FLEXIO_PWM_IP_NO_CACHE_NEEDED == STD_ON)
    #define PWM_START_SEC_VAR_CLEARED_8_NO_CACHEABLE
#else
    #define PWM_START_SEC_VAR_CLEARED_8
#endif
#include "Pwm_MemMap.h"

/** @brief Interrupt enable masks for used timers */
volatile uint8 Flexio_Pwm_Ip_u8TimerIrqMask;

#if (FLEXIO_PWM_IP_NO_CACHE_NEEDED == STD_ON)
    #define PWM_STOP_SEC_VAR_CLEARED_8_NO_CACHEABLE
#else
    #define PWM_STOP_SEC_VAR_CLEARED_8
#endif
#include "Pwm_MemMap.h"
#if (FLEXIO_PWM_IP_NO_CACHE_NEEDED == STD_ON)
    #define PWM_START_SEC_VAR_CLEARED_32_NO_CACHEABLE
#else
    #define PWM_START_SEC_VAR_CLEARED_32
#endif
#include "Pwm_MemMap.h"

#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
/** @brief Interrupt enable masks for used pins */
volatile uint32 Flexio_Pwm_Ip_u32PinIrqMask;
#endif

#if (FLEXIO_PWM_IP_NO_CACHE_NEEDED == STD_ON)
    #define PWM_STOP_SEC_VAR_CLEARED_32_NO_CACHEABLE
#else
    #define PWM_STOP_SEC_VAR_CLEARED_32
#endif
#include "Pwm_MemMap.h"
/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
#define PWM_START_SEC_CODE
#include "Pwm_MemMap.h"
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Pwm_Ip_PinOverrideNeeded
 * Description   : Configure the pin override value based on channel polarity
 * and duty cycle case 0% or 100%. Returns true if pin overide was enabled, false
 * otherwise.
 *END**************************************************************************/
static boolean Flexio_Pwm_Ip_PinOverrideNeeded(uint8 InstanceId, uint8 Channel, uint16 Period, uint16 DutyCycle)
{
    boolean RetStatus = TRUE;
    Flexio_Pwm_Ip_StatusType Status = FLEXIO_PWM_IP_STATUS_SUCCESS;
    Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
    
    /* Check if duty is 0% or 100% to not create spikes on the output */
    if ((0U == DutyCycle) || (0U == Period))
    {
#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
        /* Case 0% duty cycle -> Ouput driven to Idle state */
        if (FLEXIO_PWM_IP_ACTIVE_HIGH == Flexio_Pwm_Ip_aState[Channel]->Polarity)
        {
#endif
            Status = Flexio_Pwm_Ip_ForceOuputLevel(InstanceId, Channel, FALSE);
#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
        }
        else
        {
            Status = Flexio_Pwm_Ip_ForceOuputLevel(InstanceId, Channel, TRUE);
        }
#endif
    }
    else if (DutyCycle == Period)
    {
#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
        /* Case 100% duty cycle -> Ouput driven to Active state */
        if (FLEXIO_PWM_IP_ACTIVE_HIGH == Flexio_Pwm_Ip_aState[Channel]->Polarity)
        {
#endif
            Status = Flexio_Pwm_Ip_ForceOuputLevel(InstanceId, Channel, TRUE);
#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
        }
        else
        {
            Status = Flexio_Pwm_Ip_ForceOuputLevel(InstanceId, Channel, FALSE);
        }
#endif
    }
    else
    {
        RetStatus = FALSE;
    }

    if(Period > 2U)
    {
        Flexio_Pwm_Ip_SetUpperValue(Base, Channel, 0U);        
        Flexio_Pwm_Ip_SetLowerValue(Base, Channel, (uint8)(Period - 2U));
    }
    else
    {
        Flexio_Pwm_Ip_SetUpperValue(Base, Channel, 0U);
        Flexio_Pwm_Ip_SetLowerValue(Base, Channel, 0U);
    }

    (void)Status;

    return RetStatus;
}
#endif /* (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON)) */
static inline void Flexio_Pwm_Ip_ResetTimerRegisters(uint8 InstanceId, uint8 Channel)
{
    Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
    const Flexio_Pwm_Ip_ChannelConfigType * const UserCfg = Flexio_Pwm_Ip_aState[Channel];
    
#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
    Flexio_Pwm_Ip_SetTimerPinPolarity(Base, UserCfg->TimerId, FLEXIO_PWM_IP_ACTIVE_HIGH);
#endif
    Flexio_Pwm_Ip_SetTimerPin(Base, UserCfg->TimerId, 0U);
    /* Disable the pin out for the selected timer */
    Flexio_Pwm_Ip_SetTimerPinOutput(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_PIN_OUTPUT_DISABLE);
    Flexio_Pwm_Ip_SetTimerInitMode(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_INIT_HIGH);
#if (defined(FLEXIO_PWM_IP_HAS_PRESCALER) && (FLEXIO_PWM_IP_HAS_PRESCALER == STD_ON))
    Flexio_Pwm_Ip_SetTimerPrescaler(Base, UserCfg->TimerId, FLEXIO_PWM_IP_CLK_DIV_1);
#endif
    Flexio_Pwm_Ip_SetUpperValue(Base, UserCfg->TimerId, 0U);
    Flexio_Pwm_Ip_SetLowerValue(Base, UserCfg->TimerId, 0U);
}

static inline void Flexio_Pwm_Ip_InitTimerPin(Flexio_Pwm_Ip_HwAddrType * const Base,
                                       const Flexio_Pwm_Ip_ChannelConfigType * const UserCfg)
{
    /* Enable the pin out for the selected timer */
    Flexio_Pwm_Ip_SetTimerPinOutput(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_PIN_OUTPUT_ENABLE);
    /* Select the pin that the selected timer will ouput the signal */
    Flexio_Pwm_Ip_SetTimerPin(Base, UserCfg->TimerId, UserCfg->PinId);
}

#define PWM_STOP_SEC_CODE
#include "Pwm_MemMap.h"

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#define PWM_START_SEC_CODE
#include "Pwm_MemMap.h"

/**
 *
 * Function Name : Flexio_Pwm_Ip_InitChannel
 * Description   : Initialize a flexio channel in pwm mode.
 * The function will initialize one timer and pin of the selected flexio channel in pwm
 * mode, with the configuration of the user. The interrupts will be disabled.
 *
 * @implements Flexio_Pwm_Ip_InitChannel_Activity
 */
Flexio_Pwm_Ip_StatusType Flexio_Pwm_Ip_InitChannel(uint8 InstanceId, const Flexio_Pwm_Ip_ChannelConfigType * const UserCfg)
{
#if ((defined(FLEXIO_PWM_IP_DEV_ERROR_DETECT)) && (FLEXIO_PWM_IP_DEV_ERROR_DETECT == STD_ON))
    /* Check received parameters */
    DevAssert(NULL_PTR != UserCfg);
    DevAssert(FLEXIO_INSTANCE_COUNT > InstanceId);
    /* Check UserCfg period can be achieved with the selected duty cycle */
    DevAssert(UserCfg->Period >= UserCfg->DutyCycle);
    /* Driver uses pin override feature to generate the output signal with duty cycle 100% or 0%.
       Therefore, the pin's driven with value of PINOUTD , not controlled by timer configuration */
    DevAssert((FLEXIO_PWM_IP_TIMER_CMP_MAX_VALUE >= UserCfg->DutyCycle) || (UserCfg->Period == UserCfg->DutyCycle));
    DevAssert(FLEXIO_PWM_IP_TIMER_CMP_MAX_VALUE >= (uint16)(UserCfg->Period - UserCfg->DutyCycle));
#endif

    Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
    Flexio_Pwm_Ip_StatusType RetStatus = FLEXIO_PWM_IP_STATUS_SUCCESS;

    /* Save the user cfg pointer */
    Flexio_Pwm_Ip_aState[UserCfg->TimerId] = UserCfg;

    /* Make sure the timer is disabled */
    Flexio_Pwm_Ip_SetTimerMode(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_DISABLED);
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
    /* Do not touch PINOUTE/PINOUTD registers to prevent spike in case duty cycle 0%/100% and multivariants used or Flexio_Pwm_Ip_InitChannel
       called one more times. PINOUTE/PINOUTD registers will be configured in Flexio_Pwm_Ip_PinOverrideNeeded function */
    if ((0U != UserCfg->Period) && (0U != UserCfg->DutyCycle) && (UserCfg->Period != UserCfg->DutyCycle))
    {
        /* Reset the Pin configuration */
        Flexio_Pwm_Ip_ConfigurePinOverride(Base, UserCfg->PinId, FALSE);
        /* Reset the value driven on the corresponding pin */
        Flexio_Pwm_Ip_SetPinLevel(Base, UserCfg->PinId, FALSE);
    }
#endif
#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
    /* Configure the timer initial and clock source and control register */
    if (FLEXIO_PWM_IP_ACTIVE_HIGH == UserCfg->Polarity)
    {
#endif
        Flexio_Pwm_Ip_SetTimerInitMode(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_INIT_HIGH);

#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
    }
    else
    {
        Flexio_Pwm_Ip_SetTimerInitMode(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_INIT_LOW);
    }
#endif
#if (defined(FLEXIO_PWM_IP_HAS_PRESCALER) && (FLEXIO_PWM_IP_HAS_PRESCALER == STD_ON))
    Flexio_Pwm_Ip_SetTimerPrescaler(Base, UserCfg->TimerId, UserCfg->Prescaler);
#endif
#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
    Flexio_Pwm_Ip_SetTimerPinPolarity(Base, UserCfg->TimerId, FLEXIO_PWM_IP_ACTIVE_HIGH);
#endif
    /* Disable interrupts as per ASR requirements */
    RetStatus = Flexio_Pwm_Ip_UpdateInterruptMode(InstanceId, UserCfg->TimerId, FLEXIO_PWM_IP_IRQ_DISABLED);
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
    /* If not in 0% 100% duty case start the timer */
    if (Flexio_Pwm_Ip_PinOverrideNeeded(InstanceId, UserCfg->TimerId, UserCfg->Period, UserCfg->DutyCycle) == FALSE)
    {
#endif
        /* Configure the timer comparator with duty and period values */
        Flexio_Pwm_Ip_SetLowerValue(Base, UserCfg->TimerId, (uint8)(UserCfg->DutyCycle - 1U));
        Flexio_Pwm_Ip_SetUpperValue(Base, UserCfg->TimerId, (uint8)(UserCfg->Period - UserCfg->DutyCycle - 1U));

#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
        /* Transition and enable the timer in selected mode */
        if (FLEXIO_PWM_IP_ACTIVE_HIGH == UserCfg->Polarity)
        {
#endif

            Flexio_Pwm_Ip_SetTimerMode(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_PWM_HIGH);
#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
        }
        else
        {
            Flexio_Pwm_Ip_SetTimerMode(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_PWM_LOW);
        }
#endif
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
    }
#endif
    /* Configure timer pin */
    Flexio_Pwm_Ip_InitTimerPin(Base, UserCfg);

    return RetStatus;
}

/**
 *
 * Function Name : Flexio_Pwm_Ip_DeInitChannel
 * Description   :  Deinitialize a flexio channel.
 * The function will initialize one timer and pin of the selected flexio channel in pwm
 * mode, with the configuration of the user. The interrupts will be disabled.
 *
 * @implements Flexio_Pwm_Ip_DeInitChannel_Activity
 */
Flexio_Pwm_Ip_StatusType Flexio_Pwm_Ip_DeInitChannel(uint8 InstanceId, uint8 Channel)
{
#if ((defined(FLEXIO_PWM_IP_DEV_ERROR_DETECT)) && (FLEXIO_PWM_IP_DEV_ERROR_DETECT == STD_ON))
    /* Check received parameters */
    DevAssert(FLEXIO_PWM_IP_CHANNEL_COUNT > Channel);
    DevAssert(FLEXIO_INSTANCE_COUNT > InstanceId);
#endif

    Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
    const Flexio_Pwm_Ip_ChannelConfigType * const UserCfg = Flexio_Pwm_Ip_aState[Channel];
    Flexio_Pwm_Ip_StatusType RetStatus = FLEXIO_PWM_IP_STATUS_SUCCESS;

    /* Disable the timer */
    Flexio_Pwm_Ip_SetTimerMode(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_DISABLED);

    /* Clear flags for timer and pin */
    RetStatus = Flexio_Pwm_Ip_UpdateInterruptMode(InstanceId, Channel, FLEXIO_PWM_IP_IRQ_DISABLED);

    /* Reset the timer registers */
    Flexio_Pwm_Ip_ResetTimerRegisters(InstanceId, Channel);
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
#if (defined(FLEXIO_PWM_IP_AUTOSAR_MODE_IS_USED) && (STD_OFF == FLEXIO_PWM_IP_AUTOSAR_MODE_IS_USED))
    /* If this channel is working on ASR mode, do not touch PINOUTE/PINOUTD registers to prevent spike */
    /* Reset the Pin configuration */
    Flexio_Pwm_Ip_ConfigurePinOverride(Base, UserCfg->PinId, FALSE);

    Flexio_Pwm_Ip_SetPinLevel(Base, UserCfg->PinId, FALSE);
#endif
#endif
    return RetStatus;
}
#if (defined(FLEXIO_PWM_IP_HAS_PRESCALER) && (FLEXIO_PWM_IP_HAS_PRESCALER == STD_ON))
/**
 *
 * Function Name : Flexio_Pwm_Ip_UpdateClockPrescaler
 * Description   : Set clock prescaler for a flexio channel
 * The function will change the prescaller value for the selected flexio channel.
 *
 * @implements Flexio_Pwm_Ip_UpdateClockPrescaler_Activity
 */
Flexio_Pwm_Ip_StatusType Flexio_Pwm_Ip_UpdateClockPrescaler(uint8 InstanceId, uint8 Channel, Flexio_Pwm_Ip_ClockPrescalerType Prescaler)
{
#if ((defined(FLEXIO_PWM_IP_DEV_ERROR_DETECT)) && (FLEXIO_PWM_IP_DEV_ERROR_DETECT == STD_ON))
    /* Check received parameters */
    DevAssert(FLEXIO_PWM_IP_CHANNEL_COUNT > Channel);
    DevAssert(FLEXIO_INSTANCE_COUNT > InstanceId);
#endif

    Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
    const Flexio_Pwm_Ip_ChannelConfigType * const UserCfg = Flexio_Pwm_Ip_aState[Channel];

    SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_31();

    /* update timer configuration register */
    Flexio_Pwm_Ip_SetTimerPrescaler(Base, UserCfg->TimerId, Prescaler);

    SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_31();

    return FLEXIO_PWM_IP_STATUS_SUCCESS;
}
#endif /* (defined(FLEXIO_PWM_IP_HAS_PRESCALER) && (FLEXIO_PWM_IP_HAS_PRESCALER == STD_ON)) */
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
/**
 *
 * Function Name : Flexio_Pwm_Ip_ForceOuputLevel
 * Description   : Force the pin ouput to logic one or zero
 * The function will override the pin ouput of the selected flexio channel to the desired
 * logic level.
 *
 * @implements Flexio_Pwm_Ip_ForceOuputLevel_Activity
 */
Flexio_Pwm_Ip_StatusType Flexio_Pwm_Ip_ForceOuputLevel(uint8 InstanceId, uint8 Channel, boolean Level)
{
#if ((defined(FLEXIO_PWM_IP_DEV_ERROR_DETECT)) && (FLEXIO_PWM_IP_DEV_ERROR_DETECT == STD_ON))
    /* Check received parameters */
    DevAssert(FLEXIO_PWM_IP_CHANNEL_COUNT > Channel);
    DevAssert(FLEXIO_INSTANCE_COUNT > InstanceId);
#endif

    Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
    const Flexio_Pwm_Ip_ChannelConfigType * const UserCfg = Flexio_Pwm_Ip_aState[Channel];
    
    SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_32();

    /* enable pin override */
    Flexio_Pwm_Ip_SetPinLevel(Base, UserCfg->PinId, Level);
    Flexio_Pwm_Ip_ConfigurePinOverride(Base, UserCfg->PinId, TRUE);

#if (FLEXIO_PWM_IP_USED_MCL == STD_ON)
    /* Clear flags for timer and pin */
    Flexio_Mcl_Ip_ClearTimerStatus(Base, UserCfg->TimerId);
#endif
    Flexio_Pwm_Ip_ClearPinFlag(Base, UserCfg->PinId);

    /* Disable the timer */
    Flexio_Pwm_Ip_SetTimerMode(Base, UserCfg->TimerId, FLEXIO_PWM_IP_TIMER_DISABLED);

    SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_32();

    return FLEXIO_PWM_IP_STATUS_SUCCESS;
}
#endif /* (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON)) */
/**
 *
 * Function Name : Flexio_Pwm_Ip_UpdatePeriodDuty
 * Description   : Set a new value for duty cycle and period of the channel.
 * The function will update the selected flexio channel with the new values for the
 * duty cycle and period.
 *
 * @implements Flexio_Pwm_Ip_UpdatePeriodDuty_Activity
 */
Flexio_Pwm_Ip_StatusType Flexio_Pwm_Ip_UpdatePeriodDuty(uint8 InstanceId, uint8 Channel, uint16 Period, uint16 DutyCycle)
{
#if ((defined(FLEXIO_PWM_IP_DEV_ERROR_DETECT)) && (FLEXIO_PWM_IP_DEV_ERROR_DETECT == STD_ON))
    /* Check received parameters */
    DevAssert(FLEXIO_PWM_IP_CHANNEL_COUNT > Channel);
    DevAssert(FLEXIO_INSTANCE_COUNT > InstanceId);
    /* Check UserCfg period can be achieved with the selected duty cycle */
    DevAssert(Period >= DutyCycle);
    DevAssert(FLEXIO_PWM_IP_TIMER_CMP_MAX_VALUE >= DutyCycle);
    DevAssert(FLEXIO_PWM_IP_TIMER_CMP_MAX_VALUE >= (uint16)(Period - DutyCycle));
#endif

    Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
#if ((defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON)) || \
     (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON)))
    const Flexio_Pwm_Ip_ChannelConfigType * const UserCfg = Flexio_Pwm_Ip_aState[Channel];
#endif

    SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_33();

#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
        if (FLEXIO_PWM_IP_ACTIVE_HIGH == UserCfg->Polarity)
        {
#endif
            Flexio_Pwm_Ip_SetTimerInitMode(Base, Channel, FLEXIO_PWM_IP_TIMER_INIT_HIGH);
            Flexio_Pwm_Ip_SetTimerMode(Base, Channel, FLEXIO_PWM_IP_TIMER_PWM_HIGH);

#if (defined(FLEXIO_PWM_IP_HAS_LOW_MODE) && (FLEXIO_PWM_IP_HAS_LOW_MODE == STD_ON))
        }
        else
        {
            Flexio_Pwm_Ip_SetTimerInitMode(Base, Channel, FLEXIO_PWM_IP_TIMER_INIT_LOW);
            Flexio_Pwm_Ip_SetTimerMode(Base, Channel, FLEXIO_PWM_IP_TIMER_PWM_LOW);
        }
#endif
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
    /* If not in 0% 100% duty case configure the timer */
    if (Flexio_Pwm_Ip_PinOverrideNeeded(InstanceId, Channel, Period, DutyCycle) == FALSE)
    {
#endif
        /* Configure the timer comparator with duty and period values */
        Flexio_Pwm_Ip_SetLowerValue(Base, Channel, (uint8)(DutyCycle - 1U));
        Flexio_Pwm_Ip_SetUpperValue(Base, Channel, (uint8)(Period - DutyCycle - 1U));
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
        /* Disable pin override if active to support channels working in cases not 0% 100% */
        if (Flexio_Pwm_Ip_GetPinOverride(Base, UserCfg->PinId))
        {
            Flexio_Pwm_Ip_ConfigurePinOverride(Base, UserCfg->PinId, FALSE);
        }
    }
#endif
    SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_33();

    return FLEXIO_PWM_IP_STATUS_SUCCESS;
}

/**
 *
 * Function Name : Flexio_Pwm_Ip_GetOutputState
 * Description   : Get the logic level of the channel ouput.
 * The function will return the logic level that the selected flexio channel is driving on
 * on the output pin.
 *
 * @implements Flexio_Pwm_Ip_GetOutputState_Activity
 */
boolean Flexio_Pwm_Ip_GetOutputState(uint8 InstanceId, uint8 Channel)
{
#if ((defined(FLEXIO_PWM_IP_DEV_ERROR_DETECT)) && (FLEXIO_PWM_IP_DEV_ERROR_DETECT == STD_ON))
    /* Check received parameters */
    DevAssert(FLEXIO_PWM_IP_CHANNEL_COUNT > Channel);
    DevAssert(FLEXIO_INSTANCE_COUNT > InstanceId);
#endif

    const Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
    const Flexio_Pwm_Ip_ChannelConfigType * const UserCfg = Flexio_Pwm_Ip_aState[Channel];

    return Flexio_Pwm_Ip_GetPinState(Base, UserCfg->PinId);
}

/**
 *
 * Function Name : Flexio_Pwm_Ip_UpdateInterruptMode
 * Description   : Update the interrupt mode for a channel.
 * The function will set a new mode for the flag event response on the selected channel.
 *
 * @implements Flexio_Pwm_Ip_UpdateInterruptMode_Activity
 */
Flexio_Pwm_Ip_StatusType Flexio_Pwm_Ip_UpdateInterruptMode(uint8 InstanceId, uint8 Channel, Flexio_Pwm_Ip_InterruptType IrqMode)
{
#if ((defined(FLEXIO_PWM_IP_DEV_ERROR_DETECT)) && (FLEXIO_PWM_IP_DEV_ERROR_DETECT == STD_ON))
    /* Check received parameters */
    DevAssert(FLEXIO_PWM_IP_CHANNEL_COUNT > Channel);
    DevAssert(FLEXIO_INSTANCE_COUNT > InstanceId);
#endif

#if ((defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON)) || (FLEXIO_PWM_IP_USED_MCL == STD_ON))
    Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
#endif
    const Flexio_Pwm_Ip_ChannelConfigType * const UserCfg = Flexio_Pwm_Ip_aState[Channel];
    Flexio_Pwm_Ip_StatusType RetStatus = FLEXIO_PWM_IP_STATUS_SUCCESS;

    SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_34();

#if (FLEXIO_PWM_IP_USED_MCL == STD_ON)
    /* Clear Flags and irq mask for pin and timer */
    Flexio_Mcl_Ip_ClearTimerStatus(Base, UserCfg->TimerId);
#endif
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
    Flexio_Pwm_Ip_ClearPinFlag(Base, UserCfg->PinId);
#endif
#if (FLEXIO_PWM_IP_USED_MCL == STD_ON)
    /* Stop all Irq for this channel for case FLEXIO_PWM_IP_IRQ_DISABLED */
    Flexio_Mcl_Ip_SetTimerInterrupt(Base, (1U << UserCfg->TimerId), FALSE);
#endif
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
    Flexio_Pwm_Ip_ConfigurePinRisingEdge(Base, UserCfg->PinId, FALSE);
    Flexio_Pwm_Ip_ConfigurePinFallingEdge(Base, UserCfg->PinId, FALSE);
    Flexio_Pwm_Ip_ConfigurePinIrq(Base, UserCfg->PinId, FALSE);
    
    /* Configure interrupt for rising/falling edges of pin */
    if ((FLEXIO_PWM_IP_IRQ_ON_RISING_EDGE == IrqMode)
        || (FLEXIO_PWM_IP_IRQ_ON_BOTH_EDGES == IrqMode))
    {
        Flexio_Pwm_Ip_ConfigurePinRisingEdge(Base, UserCfg->PinId, TRUE);
        if ((UserCfg->IplCallback.CbFunction != NULL_PTR) || (UserCfg->HldCallback.CbFunction != NULL_PTR))
        {
            Flexio_Pwm_Ip_ConfigurePinIrq(Base, UserCfg->PinId, TRUE);
            Flexio_Pwm_Ip_u32PinIrqMask = Flexio_Pwm_Ip_u32PinIrqMask | (uint32)((uint32)1U << UserCfg->PinId);
        }
    }
    if ((FLEXIO_PWM_IP_IRQ_ON_FALLING_EDGE == IrqMode)
        || (FLEXIO_PWM_IP_IRQ_ON_BOTH_EDGES == IrqMode))
    {
        Flexio_Pwm_Ip_ConfigurePinFallingEdge(Base, UserCfg->PinId, TRUE);
        if ((UserCfg->IplCallback.CbFunction != NULL_PTR) || (UserCfg->HldCallback.CbFunction != NULL_PTR))
        {
            Flexio_Pwm_Ip_ConfigurePinIrq(Base, UserCfg->PinId, TRUE);
            Flexio_Pwm_Ip_u32PinIrqMask = Flexio_Pwm_Ip_u32PinIrqMask | (uint32)((uint32)1U << UserCfg->PinId);
        }
    }
#endif
    if (FLEXIO_PWM_IP_IRQ_ON_PERIOD_END == IrqMode)
    {
#if (FLEXIO_PWM_IP_USED_MCL == STD_ON)
        Flexio_Mcl_Ip_SetTimerInterrupt(Base, (1U << UserCfg->TimerId), TRUE);
#endif
        Flexio_Pwm_Ip_u8TimerIrqMask = Flexio_Pwm_Ip_u8TimerIrqMask | (uint8)((uint8)1U << UserCfg->TimerId);
    }
    else if (FLEXIO_PWM_IP_IRQ_DISABLED == IrqMode)
    {
        Flexio_Pwm_Ip_u8TimerIrqMask = Flexio_Pwm_Ip_u8TimerIrqMask & ~((uint8)0x01U << UserCfg->TimerId);
#if (defined(FLEXIO_PWM_IP_HAS_PIN_OVERRIDE) && (FLEXIO_PWM_IP_HAS_PIN_OVERRIDE == STD_ON))
        Flexio_Pwm_Ip_u32PinIrqMask = Flexio_Pwm_Ip_u32PinIrqMask & ~((uint32)1U << UserCfg->PinId);
#endif
    }
    else
    {
        /* Do Nothing */
    }

    SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_34();

    return RetStatus;
}

 /**
 *
 * Function Name : Flexio_Pwm_Ip_GetPeriod
 * Description   : Getting the period for a channel.
 * The function will get the period on the selected channel.
 *
 * @implements Flexio_Pwm_Ip_GetPeriod_Activity
 */
uint16 Flexio_Pwm_Ip_GetPeriod(uint8 InstanceId, uint8 Channel)
{
#if ((defined(FLEXIO_PWM_IP_DEV_ERROR_DETECT)) && (FLEXIO_PWM_IP_DEV_ERROR_DETECT == STD_ON))
    /* Check received parameters */
    DevAssert(FLEXIO_PWM_IP_CHANNEL_COUNT > Channel);
    DevAssert(FLEXIO_INSTANCE_COUNT > InstanceId);
#endif

    const Flexio_Pwm_Ip_HwAddrType * const Base = Flexio_Pwm_Ip_aBasePtr[InstanceId];
    /* Getting the period for a channel. */
    uint16 Period = (uint16)Flexio_Pwm_Ip_GetUpperValue(Base, Channel) + (uint16)Flexio_Pwm_Ip_GetLowerValue(Base, Channel) + (uint16)2U;
    
    return Period;
}

#define PWM_STOP_SEC_CODE
#include "Pwm_MemMap.h"

#endif /* FLEXIO_PWM_IP_USED == STD_ON */
#ifdef __cplusplus
}
#endif

/** @} */
