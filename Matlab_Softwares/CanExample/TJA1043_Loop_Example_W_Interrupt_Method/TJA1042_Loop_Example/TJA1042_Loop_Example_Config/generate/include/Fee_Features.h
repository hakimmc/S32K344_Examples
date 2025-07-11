/*==================================================================================================
* Project              : RTD AUTOSAR 4.7
* Platform             : CORTEXM
* Peripheral           : none
* Dependencies         : MemAcc
*
* Autosar Version      : 4.7.0
* Autosar Revision     : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version           : 5.0.0
* Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly
* in accordance with the applicable license terms.  By expressly accepting
* such terms or by downloading, installing, activating and/or otherwise using
* the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to
* be bound by the applicable license terms, then you may not retain,
* install, activate or otherwise use the software.
*
==================================================================================================*/

#ifndef FEE_FEATURES_H
#define FEE_FEATURES_H

/**
*   @file
*
*   @addtogroup FEE
*   @{
*/
/*   @implements Fee_Features.h_Artifact*/
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

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define FEE_FEATURES_VENDOR_ID                    43
#define FEE_FEATURES_AR_RELEASE_MAJOR_VERSION     4
#define FEE_FEATURES_AR_RELEASE_MINOR_VERSION     7
#define FEE_FEATURES_AR_RELEASE_REVISION_VERSION  0
#define FEE_FEATURES_SW_MAJOR_VERSION             5
#define FEE_FEATURES_SW_MINOR_VERSION             0
#define FEE_FEATURES_SW_PATCH_VERSION             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/* This configuration enables the SubAddressArea retirement feature */
#define FEE_SUBADDRESSAREA_RETIREMENT                     (STD_OFF)

#if (FEE_SUBADDRESSAREA_RETIREMENT == STD_ON)
    /* The number of bytes in a cluster header, used to store the SubAddressAreas information */
    #define FEE_CLUSTER_HEADER_SUBADDRESSAREAINFO_SIZE    (8U)
    /* The number of attempts when erasing each SubAddressArea in the cluster in swap phase */
    #define FEE_SUBADDRESSAREA_ERASE_RETRIES              (3U)

    /* The number of attempts when erasing each SubAddressArea in the cluster in swap phase */
    #define FEE_NUMBER_OF_SUBADDRESSAREAS_TO_RECOVER      (0U)
#endif
#ifdef __cplusplus
}
#endif

/** @} */

#endif /* FEE_FEATURES_H */

