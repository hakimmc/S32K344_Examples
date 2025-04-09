/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : S32K3XX
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 2.0.0
*   Build Version        : S32K3_RTD_2_0_0_D2203_ASR_REL_4_4_REV_0000_20220331
*
*   (c) Copyright 2020 - 2021 NXP Semiconductors
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

/**
*   @file      Siul2_Port_Ip_Cfg.h
*
*   @addtogroup Port_CFG
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
#include "Siul2_Port_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SIUL2_PORT_IP_VENDOR_ID_CFG_C                       43
#define SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_C        4
#define SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_C        4
#define SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_C     0
#define SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_C                2
#define SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_C                0
#define SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_C                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are of the same vendor */
#if (SIUL2_PORT_IP_VENDOR_ID_CFG_C != SIUL2_PORT_IP_VENDOR_ID_CFG_H)
    #error "Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h have different vendor ids"
#endif
/* Check if Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are of the same Autosar version */
#if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_C    != SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
    (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_C    != SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H) || \
    (SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_C != SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H) \
    )
    #error "AutoSar Version Numbers of Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are different"
#endif
/* Check if Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are of the same Software version */
#if ((SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_C != SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_H) || \
    (SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_C != SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_H) || \
    (SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_C != SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_H)    \
    )
    #error "Software Version Numbers of Siul2_Port_Ip_Cfg.c and Siul2_Port_Ip_Cfg.h are different"
#endif

/*==================================================================================================
                             LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                             LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                            LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                           LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                           GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                           GLOBAL VARIABLES
==================================================================================================*/

/* clang-format off */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0}
- pin_list:
  - {pin_num: M15, peripheral: FlexCAN_0, signal: rxd, pin_signal: PTA6}
  - {pin_num: M16, peripheral: FlexCAN_0, signal: txd, pin_signal: PTA7}
  - {pin_num: N16, peripheral: SIUL2, signal: 'gpio, 93', pin_signal: PTC29, direction: INPUT}
  - {pin_num: N17, peripheral: SIUL2, signal: 'gpio, 94', pin_signal: PTC30, direction: OUTPUT}
  - {pin_num: U17, peripheral: SIUL2, signal: 'gpio, 204', pin_signal: PTG12, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*! @brief Array of pin configuration structures */
const Siul2_Port_Ip_PinSettingsConfig g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0] =
{
    {
        .base                        = IP_SIUL2,
        .pinPortIdx                  = 6u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .inputFilter                 = PORT_INPUT_FILTER_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .pullKeep                    = PORT_PULL_KEEP_DISABLED,
        .invert                      = PORT_INVERT_DISABLED,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .adcInterleaves              = { MUX_MODE_NOT_AVAILABLE, MUX_MODE_NOT_AVAILABLE },
        .inputMuxReg                 = {
                                         0u
                                       },
        .inputMux                    = { 
                                         PORT_INPUT_MUX_ALT2,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
    },
    {
        .base                        = IP_SIUL2,
        .pinPortIdx                  = 7u,
        .mux                         = PORT_MUX_ALT4,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .inputFilter                 = PORT_INPUT_FILTER_DISABLED,
        .driveStrength               = PORT_DRIVE_STRENTGTH_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .pullKeep                    = PORT_PULL_KEEP_DISABLED,
        .invert                      = PORT_INVERT_DISABLED,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .adcInterleaves              = { MUX_MODE_NOT_AVAILABLE, MUX_MODE_NOT_AVAILABLE },
    },
    {
        .base                        = IP_SIUL2,
        .pinPortIdx                  = 93u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .inputFilter                 = PORT_INPUT_FILTER_DISABLED,
        .driveStrength               = PORT_DRIVE_STRENTGTH_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .pullKeep                    = PORT_PULL_KEEP_DISABLED,
        .invert                      = PORT_INVERT_DISABLED,
        .inputBuffer                 = PORT_INPUT_BUFFER_ENABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_DISABLED,
        .adcInterleaves              = { MUX_MODE_NOT_AVAILABLE, MUX_MODE_NOT_AVAILABLE },
        .inputMux                    = {
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT,
                                         PORT_INPUT_MUX_NO_INIT
                                       },
    },
    {
        .base                        = IP_SIUL2,
        .pinPortIdx                  = 94u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .inputFilter                 = PORT_INPUT_FILTER_DISABLED,
        .driveStrength               = PORT_DRIVE_STRENTGTH_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .pullKeep                    = PORT_PULL_KEEP_DISABLED,
        .invert                      = PORT_INVERT_DISABLED,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .adcInterleaves              = { MUX_MODE_NOT_AVAILABLE, MUX_MODE_NOT_AVAILABLE },
        .initValue                   = 0u
    },
    {
        .base                        = IP_SIUL2,
        .pinPortIdx                  = 204u,
        .mux                         = PORT_MUX_AS_GPIO,
        .safeMode                    = PORT_SAFE_MODE_DISABLED,
        .inputFilter                 = PORT_INPUT_FILTER_DISABLED,
        .pullConfig                  = PORT_INTERNAL_PULL_NOT_ENABLED,
        .pullKeep                    = PORT_PULL_KEEP_DISABLED,
        .invert                      = PORT_INVERT_DISABLED,
        .inputBuffer                 = PORT_INPUT_BUFFER_DISABLED,
        .outputBuffer                = PORT_OUTPUT_BUFFER_ENABLED,
        .adcInterleaves              = { MUX_MODE_NOT_AVAILABLE, MUX_MODE_NOT_AVAILABLE },
        .initValue                   = 0u
    },
};

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Port_MemMap.h"

/*==================================================================================================
                                      LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                           LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                           GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

