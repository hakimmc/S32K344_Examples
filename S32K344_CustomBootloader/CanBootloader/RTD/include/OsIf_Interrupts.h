/*==================================================================================================
* Project : RTD AUTOSAR 4.4
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.4.0
* Autosar Revision : ASR_REL_4_4_REV_0000
* Autosar Conf.Variant :
* SW Version : 2.0.0
* Build Version : S32K3_RTD_2_0_0_D2203_ASR_REL_4_4_REV_0000_20220331
*
* (c) Copyright 2020 - 2022 NXP Semiconductors
* All Rights Reserved.
*
* NXP Confidential. This software is owned or controlled by NXP and may only be
* used strictly in accordance with the applicable license terms. By expressly
* accepting such terms or by downloading, installing, activating and/or otherwise
* using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms. If you do not agree to be
* bound by the applicable license terms, then you may not retain, install,
* activate or otherwise use the software.
==================================================================================================*/
#ifndef OSIF_INTERRUPTS_H
#define OSIF_INTERRUPTS_H

/**
*   @file
*
*   @addtogroup osif_drv
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
#include "OsIf_Cfg.h"

#if defined(USING_OS_ZEPHYR)
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_INTERRUPTS_VENDOR_ID                    43
#define OSIF_INTERRUPTS_AR_RELEASE_MAJOR_VERSION     4
#define OSIF_INTERRUPTS_AR_RELEASE_MINOR_VERSION     4
#define OSIF_INTERRUPTS_AR_RELEASE_REVISION_VERSION  0
#define OSIF_INTERRUPTS_SW_MAJOR_VERSION             2
#define OSIF_INTERRUPTS_SW_MINOR_VERSION             0
#define OSIF_INTERRUPTS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/
#define BASE_START_SEC_CODE
#include "Base_MemMap.h"

void OsIf_Interrupts_ResumeAllInterrupts(void);
void OsIf_Interrupts_SuspendAllInterrupts(void);

#define BASE_STOP_SEC_CODE
#include "Base_MemMap.h"

#endif /* defined(USING_OS_ZEPHYR) */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* OSIF_INTERRUPTS_H */
