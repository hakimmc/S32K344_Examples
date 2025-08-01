/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPI2C
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
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may
*   only be used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file
*
*   @addtogroup I2C_DRIVER_CONFIGURATION I2c Driver Configurations
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif



/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "CDD_I2c_MBDT_PBcfg.h"
#include "CDD_I2c_Ipw_MBDT_PBcfg.h"

#if (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_I2C_MBDT_PBCFG_VENDOR_ID_C                     43
#define CDD_I2C_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define CDD_I2C_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION_C      7
#define CDD_I2C_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define CDD_I2C_MBDT_PBCFG_SW_MAJOR_VERSION_C              5
#define CDD_I2C_MBDT_PBCFG_SW_MINOR_VERSION_C              0
#define CDD_I2C_MBDT_PBCFG_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and CDD_I2c_MBDT_PBcfg.h file are of the same vendor */
#if (CDD_I2C_MBDT_PBCFG_VENDOR_ID_C != CDD_I2C_MBDT_PBCFG_VENDOR_ID)
    #error "CDD_I2c_MBDT_PBcfg.c and CDD_I2c_MBDT_PBcfg.h have different vendor ids"
#endif
/* Check if current file and CDD_I2c_MBDT_PBcfg.h file are of the same Autosar version */
#if ((CDD_I2C_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != CDD_I2C_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION_C    != CDD_I2C_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION_C != CDD_I2C_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of CDD_I2c_MBDT_PBcfg.c and CDD_I2c_MBDT_PBcfg.h are different"
#endif
/* Check if current file and CDD_I2c_MBDT_PBcfg.h file are of the same Software version */
#if ((CDD_I2C_MBDT_PBCFG_SW_MAJOR_VERSION_C != CDD_I2C_MBDT_PBCFG_SW_MAJOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_SW_MINOR_VERSION_C != CDD_I2C_MBDT_PBCFG_SW_MINOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_SW_PATCH_VERSION_C != CDD_I2C_MBDT_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of CDD_I2c_MBDT_PBcfg.c and CDD_I2c_MBDT_PBcfg.h are different"
#endif

/* Check if current file and CDD_I2c_Ipw_MBDT_PBcfg.h file are of the same vendor */
#if (CDD_I2C_MBDT_PBCFG_VENDOR_ID_C != CDD_I2C_IPW_MBDT_PBCFG_VENDOR_ID)
    #error "CDD_I2c_MBDT_PBcfg.c and CDD_I2c_Ipw_MBDT_PBcfg.h have different vendor ids"
#endif
/* Check if current file and CDD_I2c_Ipw_MBDT_PBcfg.h file are of the same Autosar version */
#if ((CDD_I2C_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != CDD_I2C_IPW_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION_C    != CDD_I2C_IPW_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION_C != CDD_I2C_IPW_MBDT_PBCFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of CDD_I2c_MBDT_PBcfg.c and CDD_I2c_Ipw_MBDT_PBcfg.h are different"
#endif
/* Check if current file and CDD_I2c_Ipw_MBDT_PBcfg.h file are of the same Software version */
#if ((CDD_I2C_MBDT_PBCFG_SW_MAJOR_VERSION_C != CDD_I2C_IPW_MBDT_PBCFG_SW_MAJOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_SW_MINOR_VERSION_C != CDD_I2C_IPW_MBDT_PBCFG_SW_MINOR_VERSION) || \
     (CDD_I2C_MBDT_PBCFG_SW_PATCH_VERSION_C != CDD_I2C_IPW_MBDT_PBCFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of CDD_I2c_MBDT_PBcfg.c and CDD_I2c_Ipw_MBDT_PBcfg.h are different"
#endif

/* Check if current file and DEM header file are of the same version */
#if (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
        /* Check if current file and Dem.h header file are of the same Autosar version */
        #if ((CDD_I2C_MBDT_PBCFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) ||  \
             (CDD_I2C_MBDT_PBCFG_AR_RELEASE_MINOR_VERSION_C  != DEM_AR_RELEASE_MINOR_VERSION))
            #error "AutoSar Version Numbers of CDD_I2c_MBDT_PBcfg.c and Dem.h are different"
        #endif
    #endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
#endif /* I2C_DISABLE_DEM_REPORT_ERROR_STATUS */

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
/**
* @brief          Paritition IDs.
* @details        Paritition IDs.
*
* @api
*/

#define I2C_START_SEC_CONFIG_DATA_UNSPECIFIED

#include "I2c_MemMap.h"

/**
* @brief        Definition of I2c hardware channel structure.
* @details      Configures the hardware peripheral of an I2c channel.
*               Configuration set by calling I2c_Init() API.
*/

static const I2c_HwUnitConfigType I2c_ChannelConfigPB_MBDT[2] =
{
    /* Start of I2c_ChannelConfig_MBDT[0] */
    {
        /* The hardware channel ID. */
        (I2c_HwUnitType) I2C_FLEXIO_0_CH_2_3,

        /* The Partition Id */
        (I2c_PartCoreType) I2C_SPURIOUS_PARTITION_ID,

        /* The master/slave mode of the channel. */
        (I2c_MasterSlaveModeType) I2C_MASTER_MODE,

        /* The hardware channel type */
        I2C_FLEXIO_CHANNEL,
        {
            NULL_PTR,
            &Flexio_I2cMasterChannel0_MBDT
        }
    }, /* end of I2c_ChannelConfig_MBDT[0]. */

    /* Start of I2c_ChannelConfig_MBDT[1] */
    {
        /* The hardware channel ID. */
        (I2c_HwUnitType) I2C_LPI2C_1,

        /* The Partition Id */
        (I2c_PartCoreType) I2C_SPURIOUS_PARTITION_ID,

        /* The master/slave mode of the channel. */
        (I2c_MasterSlaveModeType) I2C_SLAVE_MODE,

        /* The hardware channel type */
        I2C_LPI2C_CHANNEL,
        {
            &I2c_Ipw_ChannelConfig1_MBDT,
            NULL_PTR
        }
    } /* end of I2c_ChannelConfig_MBDT[1]. */
};

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/
/**
* @brief          Initialization data for the I2c driver.
* @details        A structure is provided to the I2c initialization routines for configuration.
*                 The configuration structure for spurious_partition.
*
*/
const I2c_ConfigType I2c_Config_MBDT =
{
    /* The Partition Id */
    (I2c_PartCoreType) I2C_SPURIOUS_PARTITION_ID,

#if (I2C_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    /* Pointer to DEM error reporting configurations. */
    &I2c_DemConfig,
#endif

    /* Pointer to I2c hardware unit configuration. */
    &I2c_ChannelConfigPB_MBDT
};



#define I2C_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* statements and comments before "#include"
*/
#include "I2c_MemMap.h"

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */


