/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
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
*   @file    Tspc_Port_Ip.c
*
*   @addtogroup Tspc_IPL
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
#include "Tspc_Port_Ip.h"
#include "SchM_Port.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
* @brief Parameters that shall be published within the driver header file and also in the
* module's description file
*/
#define TSPC_PORT_IP_VENDOR_ID_C                     43
#define TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_C      4
#define TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_C      7
#define TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_C   0
#define TSPC_PORT_IP_SW_MAJOR_VERSION_C              3
#define TSPC_PORT_IP_SW_MINOR_VERSION_C              0
#define TSPC_PORT_IP_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if the files Tspc_Port_Ip.c and Tspc_Port_Ip.h are of the same version */
#if (TSPC_PORT_IP_VENDOR_ID_C != TSPC_PORT_IP_VENDOR_ID_H)
    #error "Tspc_Port_Ip.c and Tspc_Port_Ip.h have different vendor ids"
#endif
/* Check if Tspc_Port_Ip.c and Tspc_Port_Ip.h are of the same Autosar version */
#if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_C    != TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_C    != TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_C != TSPC_PORT_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Tspc_Port_Ip.c and Tspc_Port_Ip.h are different"
#endif
/* Check if Tspc_Port_Ip.c and Tspc_Port_Ip.h are of the same Software version */
#if ((TSPC_PORT_IP_SW_MAJOR_VERSION_C != TSPC_PORT_IP_SW_MAJOR_VERSION_H) || \
     (TSPC_PORT_IP_SW_MINOR_VERSION_C != TSPC_PORT_IP_SW_MINOR_VERSION_H) || \
     (TSPC_PORT_IP_SW_PATCH_VERSION_C != TSPC_PORT_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Tspc_Port_Ip.c and Tspc_Port_Ip.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Tspc_Port_Ip.c and SchM_Port.h are of the same AutoSar version */
    #if ((TSPC_PORT_IP_AR_RELEASE_MAJOR_VERSION_C != SCHM_PORT_AR_RELEASE_MAJOR_VERSION) || \
         (TSPC_PORT_IP_AR_RELEASE_MINOR_VERSION_C != SCHM_PORT_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Tspc_Port_Ip.c and SchM_Port.h are different"
    #endif
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

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
#ifdef FEATURE_SIUL2_PORT_IP_HAS_TOUCH_SENSING
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : Tspc_Port_Ip_EnableObeGroup
 * Description   : This function shall enable the specified group whose pads
 * are participating in simultaneous transition.
 *
 * @implements Tspc_Port_Ip_EnableObeGroup_Activity
 ******************************************************************************/
void Tspc_Port_Ip_EnableObeGroup(uint8 group)
{
    TSPC_Type * tspcBase = (TSPC_Type *)IP_TSPC_BASE;

    TSPC_PORT_DEV_ASSERT((boolean)((group < 3) && (group != 0)));

    /* Enter critical region */
    SchM_Enter_Port_PORT_EXCLUSIVE_AREA_09();
    if (1U == group)
    {
        tspcBase->GRP_EN |= TSPC_GRP_EN_GRP1_EN(1);
    }
    else
    {
        tspcBase->GRP_EN |= TSPC_GRP_EN_GRP2_EN(1);
    }
    /* Exit critical region */
    SchM_Exit_Port_PORT_EXCLUSIVE_AREA_09();

}

/*FUNCTION**********************************************************************
 *
 * Function Name : Tspc_Port_Ip_ConfigureObeGroup
 * Description   : This function shall configure which channels participate in the OBE group.
 *                 It enables the specified group whose pads are participating in simultaneous transition.
 *
 * @implements Tspc_Port_Ip_ConfigureObeGroup_Activity
 ******************************************************************************/
void Tspc_Port_Ip_ConfigureObeGroup(uint32 cfgCount,
                                    const Tspc_Port_Ip_ObeGroupConfig config[])
{
    TSPC_PORT_DEV_ASSERT((boolean)(config != NULL_PTR));

    TSPC_Type * tspcBase = (TSPC_Type *)IP_TSPC_BASE;
    uint32 i;
    uint8 groupConfig = 0U;

    for (i = 0U; i < cfgCount; i++)
    {
        /* check dev_assert to make sure the group within in range */
        TSPC_PORT_DEV_ASSERT((boolean)(config[i].obeGroupSelect < 3U));
        groupConfig |= config[i].obeGroupSelect;
    }

    /* Enter critical region */
    SchM_Enter_Port_PORT_EXCLUSIVE_AREA_10();

    /* disable the group which will be configured the OBE */
    tspcBase->GRP_EN &= ~((uint32)groupConfig);

    for (i = 0U; i < cfgCount; i++)
    {
        /* Write touch sense configuration */
        if (0U != config[i].obeGroupSelect)
        {
            if (TSPC_INVALID_GROUP_INDEX != config[i].obeGroupIndex)
            {
                if (config[i].obeGroupIndex > 31U)
                {
                    tspcBase->GROUP[(config[i].obeGroupSelect) - 1U].GRP_OBE2 |= (uint32)((uint32)1 << ((config[i].obeGroupIndex) - 32U));
                }
                else
                {
                    tspcBase->GROUP[(config[i].obeGroupSelect) - 1U].GRP_OBE1 |= (uint32)((uint32)1 << (config[i].obeGroupIndex));
                }
            }
        }
    }

    /* re-enable the group which will be configured the OBE */
    tspcBase->GRP_EN |= (uint32)groupConfig;

    /* Exit critical region */
    SchM_Exit_Port_PORT_EXCLUSIVE_AREA_10();

}

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#endif /* FEATURE_SIUL2_PORT_IP_HAS_TOUCH_SENSING */

#ifdef __cplusplus
}
#endif

/** @} */
