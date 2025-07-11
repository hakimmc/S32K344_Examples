/**
*   @file    Spi_PBcfg.c
*   @implements Spi_PBcfg.c_Artifact
*   @version 5.0.0
*
*   @brief   AUTOSAR Spi - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup SPI_DRIVER_CONFIGURATION Spi Driver Configuration
*   @{
*/
/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : LPSPI
*   Dependencies         : 
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

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Spi.h"
#include "Spi_Ipw_MBDT_PBcfg.h"

#if (SPI_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif

/*==================================================================================================
*                                    SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SPI_MBDT_VENDOR_ID_PBCFG_C                        43
#define SPI_MBDT_AR_RELEASE_MAJOR_VERSION_PBCFG_C         4
#define SPI_MBDT_AR_RELEASE_MINOR_VERSION_PBCFG_C         7

#define SPI_MBDT_AR_RELEASE_REVISION_VERSION_PBCFG_C      0
#define SPI_MBDT_SW_MAJOR_VERSION_PBCFG_C                 5
#define SPI_MBDT_SW_MINOR_VERSION_PBCFG_C                 0
#define SPI_MBDT_SW_PATCH_VERSION_PBCFG_C                 0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and SPI header file are of the same vendor */
#if (SPI_MBDT_VENDOR_ID_PBCFG_C != SPI_VENDOR_ID)
    #error "Spi_PBCfg.c and Spi.h have different vendor ids"
#endif
/* Check if current file and SPI header file are of the same Autosar version */
#if ((SPI_MBDT_AR_RELEASE_MAJOR_VERSION_PBCFG_C    != SPI_AR_RELEASE_MAJOR_VERSION) || \
     (SPI_MBDT_AR_RELEASE_MINOR_VERSION_PBCFG_C    != SPI_AR_RELEASE_MINOR_VERSION) || \
     (SPI_MBDT_AR_RELEASE_REVISION_VERSION_PBCFG_C != SPI_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Spi_PBCfg.c and Spi.h are different"
#endif
/* Check if current file and SPI header file are of the same Software version */
#if ((SPI_MBDT_SW_MAJOR_VERSION_PBCFG_C != SPI_SW_MAJOR_VERSION) || \
     (SPI_MBDT_SW_MINOR_VERSION_PBCFG_C != SPI_SW_MINOR_VERSION) || \
     (SPI_MBDT_SW_PATCH_VERSION_PBCFG_C != SPI_SW_PATCH_VERSION))
    #error "Software Version Numbers of Spi_PBCfg.c and Spi.h are different"
#endif

/* Check if current file and SPI header file are of the same vendor */
#if (SPI_MBDT_VENDOR_ID_PBCFG_C != SPI_IPW_VENDOR_ID_MBDT_PBCFG_H)
    #error "Spi_PBCfg.c and Spi_Ipw_PBCfg.h have different vendor ids"
#endif
/* Check if current file and SPI header file are of the same Autosar version */
#if ((SPI_MBDT_AR_RELEASE_MAJOR_VERSION_PBCFG_C    != SPI_IPW_AR_RELEASE_MAJOR_VERSION_MBDT_PBCFG_H) || \
     (SPI_MBDT_AR_RELEASE_MINOR_VERSION_PBCFG_C    != SPI_IPW_AR_RELEASE_MINOR_VERSION_MBDT_PBCFG_H) || \
     (SPI_MBDT_AR_RELEASE_REVISION_VERSION_PBCFG_C != SPI_IPW_AR_RELEASE_REVISION_VERSION_MBDT_PBCFG_H ))
    #error "AutoSar Version Numbers of Spi_PBCfg.c and Spi_Ipw_PBCfg.h are different"
#endif
/* Check if current file and SPI header file are of the same Software version */
#if ((SPI_MBDT_SW_MAJOR_VERSION_PBCFG_C != SPI_IPW_SW_MAJOR_VERSION_MBDT_PBCFG_H) || \
     (SPI_MBDT_SW_MINOR_VERSION_PBCFG_C != SPI_IPW_SW_MINOR_VERSION_MBDT_PBCFG_H) || \
     (SPI_MBDT_SW_PATCH_VERSION_PBCFG_C != SPI_IPW_SW_PATCH_VERSION_MBDT_PBCFG_H))
    #error "Software Version Numbers of Spi_PBCfg.c and Spi_Ipw_PBCfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if (SPI_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/* Check if current file and Dem.h file are of the same Autosar version */
#if ((SPI_MBDT_AR_RELEASE_MAJOR_VERSION_PBCFG_C    != DEM_AR_RELEASE_MAJOR_VERSION) || \
     (SPI_MBDT_AR_RELEASE_MINOR_VERSION_PBCFG_C    != DEM_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Spi_PBCfg.c and Dem.h are different"
#endif
#endif
#endif

/*==================================================================================================
*                         LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/*==================================================================================================
*                                  LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL FUNCTIONS
==================================================================================================*/
#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

/* List Of Notification Functions */
/* Job start/end Notifications */
extern void MBDT_SPI_end_job0_callback(void); /* End Notification for Job SpiJob_0 */
/* Sequence End Notifications */
extern void MBDT_SPI_end_sequence1_callback(void); /* End Notification for Sequence SpiSequence_1 */

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"
/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2)))
    #define SPI_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#else
    #define SPI_START_SEC_VAR_CLEARED_UNSPECIFIED
#endif /* ((SPI_DMA_USED == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) ||
        (SPI_LEVEL_DELIVERED == SPI_LEVEL2))) */
#include "Spi_MemMap.h"

/* Buffers Descriptors for EB Channels and Allocate Buffers for IB Channels */
static Spi_BufferDescriptorType Spi_Buffer_MBDT_SpiChannel_0;
static Spi_DataBufferType Spi_BufferTX_MBDT_SpiChannel_1[1];
static Spi_DataBufferType Spi_BufferRX_MBDT_SpiChannel_1[1];

#if ((SPI_DMA_USED == STD_ON) && \
    ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2)))
    #define SPI_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#else
    #define SPI_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#endif /* ((SPI_DMA_USED == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) ||
        (SPI_LEVEL_DELIVERED == SPI_LEVEL2))) */
#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

/* Buffers Descriptors for IB Channels */
/*  Buffers Descriptors for IB Channel SpiChannel_1 */
static Spi_BufferDescriptorType Spi_Buffer_MBDT_SpiChannel_1 =
{
    (const uint8*)NULL_PTR,
    Spi_BufferTX_MBDT_SpiChannel_1,  /* BufferTX */
    Spi_BufferRX_MBDT_SpiChannel_1   /* BufferRX */
};

#define SPI_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Spi_MemMap.h"
/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
#define SPI_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Spi_MemMap.h"

/* Channel Configuration */
/* Channel Configuration for SpiChannel_0 */
static const Spi_ChannelConfigType Spi_ChannelConfig_SpiChannel_0_MBDT =
{
        EB,  /* BufferType IB or EB */
        8U,   /* Frame size */
        (boolean)FALSE, /* Bit order, 1:LSB, 0: MSB */
        (boolean)FALSE, /* Byte Swap */
#ifdef SPI_HALF_DUPLEX_MODE_SUPPORT
  #if (STD_ON == SPI_HALF_DUPLEX_MODE_SUPPORT)
            SPI_FULL_DUPLEX,
              #endif
#endif

        (uint32)1U,  /* DefaultTransmitValue (configured) */
        1000U, /* length of buffer */
        &Spi_Buffer_MBDT_SpiChannel_0, /* BufferDescriptor */
        (uint32)SPI_SPURIOUS_USER_ID_U32,  /* User Id */
};
/* Channel Configuration for SpiChannel_1 */
static const Spi_ChannelConfigType Spi_ChannelConfig_SpiChannel_1_MBDT =
{
        IB,  /* BufferType IB or EB */
        8U,   /* Frame size */
        (boolean)FALSE, /* Bit order, 1:LSB, 0: MSB */
        (boolean)FALSE, /* Byte Swap */
#ifdef SPI_HALF_DUPLEX_MODE_SUPPORT
  #if (STD_ON == SPI_HALF_DUPLEX_MODE_SUPPORT)
            SPI_FULL_DUPLEX,
              #endif
#endif

        (uint32)1U,  /* DefaultTransmitValue (configured) */
        1U, /* length of buffer */
        &Spi_Buffer_MBDT_SpiChannel_1, /* BufferDescriptor */
        (uint32)SPI_SPURIOUS_USER_ID_U32,  /* User Id */
};
/* Spi_aChannelConfigList_MBDT Channel Configuration */
static const Spi_ChannelsCfgType Spi_aChannelConfigList_MBDT[2] =
{
    /* SpiChannel_0 */
    {
        &Spi_ChannelConfig_SpiChannel_0_MBDT
    },
    /* SpiChannel_1 */
    {
        &Spi_ChannelConfig_SpiChannel_1_MBDT
    }
};

/* Channel Assignment of Jobs */
/* SpiJob_0 */
static const Spi_ChannelType Spi_SpiJob_0_ChannelAssignment_MBDT[1] =
{
    SpiConf_SpiChannel_SpiChannel_0
};
/* SpiJob_1 */
static const Spi_ChannelType Spi_SpiJob_1_ChannelAssignment_MBDT[1] =
{
    SpiConf_SpiChannel_SpiChannel_1
};

/* Configuration of Jobs */
/* Job Configuration for SpiJob_0 */
static const Spi_JobConfigType Spi_JobConfig_SpiJob_0_MBDT =
{
        (Spi_ChannelType)1U, /* NumChannels field */
        Spi_SpiJob_0_ChannelAssignment_MBDT, /* List of Channels */
        &MBDT_SPI_end_job0_callback, /* End Notification */
        NULL_PTR, /* Start Notification */
        (sint8)0, /* Priority */
        (uint32)SPI_SPURIOUS_USER_ID_U32,    /* User Id */
        CSIB0, /* HWUnit index */
        SPI_SpiExternalDevice_0, /* External Device */
        &Spi_aExternalDeviceConfigList_MBDT[SPI_SpiExternalDevice_0] /* ExternalDeviceConfig - pointer to the external device configuration */
};
/* Job Configuration for SpiJob_1 */
static const Spi_JobConfigType Spi_JobConfig_SpiJob_1_MBDT =
{
        (Spi_ChannelType)1U, /* NumChannels field */
        Spi_SpiJob_1_ChannelAssignment_MBDT, /* List of Channels */
        NULL_PTR, /* End Notification */
        NULL_PTR, /* Start Notification */
        (sint8)0, /* Priority */
        (uint32)SPI_SPURIOUS_USER_ID_U32,    /* User Id */
        CSIB1, /* HWUnit index */
        SPI_SpiExternalDevice_1, /* External Device */
        &Spi_aExternalDeviceConfigList_MBDT[SPI_SpiExternalDevice_1] /* ExternalDeviceConfig - pointer to the external device configuration */
};
/* Spi_aJobConfigList_MBDT Job Configuration*/
static const Spi_JobsCfgType Spi_aJobConfigList_MBDT[2] =
{
    /* SpiJob_0 */
    {
        &Spi_JobConfig_SpiJob_0_MBDT
    },
    /* SpiJob_1 */
    {
        &Spi_JobConfig_SpiJob_1_MBDT
    }
};

/* Job Assignment of Sequences  */
/* SpiSequence_0 */
static const Spi_JobType Spi_SpiSequence_0_JobAssignment_MBDT[1] =
{
    SpiConf_SpiJob_SpiJob_0
};
/* SpiSequence_1 */
static const Spi_JobType Spi_SpiSequence_1_JobAssignment_MBDT[1] =
{
    SpiConf_SpiJob_SpiJob_1
};

/* Configuration of Sequences */
/* Sequence Configuration for SpiSequence_0 */
static const Spi_SequenceConfigType Spi_SequenceConfig_SpiSequence_0_MBDT =
{
        (Spi_JobType)1U,  /* Number of Job in Seq */
        (uint32)SPI_SPURIOUS_USER_ID_U32,
        Spi_SpiSequence_0_JobAssignment_MBDT, /* List of Jobs */
        NULL_PTR, /* End Notification */
        (uint8)FALSE  /* Interruptible */
        #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMAFASTTRANSFER_SUPPORT == STD_ON))
        , (boolean)FALSE /* Enable Dma fast transfer */
        #endif
        #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMA_CONT_MEM_TRANSFER_SUPPORT == STD_ON))
        ,(boolean)FALSE /* Enable ContMemTransferSequence */
        ,NULL_PTR
        #endif
};
/* Sequence Configuration for SpiSequence_1 */
static const Spi_SequenceConfigType Spi_SequenceConfig_SpiSequence_1_MBDT =
{
        (Spi_JobType)1U,  /* Number of Job in Seq */
        (uint32)SPI_SPURIOUS_USER_ID_U32,
        Spi_SpiSequence_1_JobAssignment_MBDT, /* List of Jobs */
        &MBDT_SPI_end_sequence1_callback, /* End Notification */
        (uint8)FALSE  /* Interruptible */
        #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMAFASTTRANSFER_SUPPORT == STD_ON))
        , (boolean)FALSE /* Enable Dma fast transfer */
        #endif
        #if ((SPI_DMA_USED == STD_ON) && (SPI_ENABLE_DMA_CONT_MEM_TRANSFER_SUPPORT == STD_ON))
        ,(boolean)FALSE /* Enable ContMemTransferSequence */
        ,NULL_PTR
        #endif
};
/* Spi_aSequenceConfigList_MBDT Sequence Configuration */
static const Spi_SeqsConfigType Spi_aSequenceConfigList_MBDT[2] =
{
    /* SpiSequence_0 */
    {
        &Spi_SequenceConfig_SpiSequence_0_MBDT
    },
    /* SpiSequence_1 */
    {
        &Spi_SequenceConfig_SpiSequence_1_MBDT
    }
};
/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/
/* Spi Configuration */
 const Spi_ConfigType Spi_Config_MBDT=
{
    2U,  /* MaxExternalDevice - number of external devices */
    1U, /* SpiMaxChannel - number of channels */
    1U, /* SpiMaxJob - number of jobs */
    1U, /* SpiMaxSequence - number of sequences */
    (uint32)SPI_SPURIOUS_USER_ID_U32,   /* SpiPartitionUse - used partition */
    Spi_aChannelConfigList_MBDT, /* ChannelConfig */
    Spi_aJobConfigList_MBDT, /* JobConfig */
    Spi_aSequenceConfigList_MBDT, /* SequenceConfig */
    Spi_aExternalDeviceConfigList_MBDT, /* ExternalDeviceConfig */
    Spi_aHwUnitConfigList_MBDT /* HWUnitConfig */
#if (SPI_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    ,{ (uint32)STD_OFF, (uint32)0U} /* SPI_E_HARDWARE_ERROR parameters*/
#endif /* SPI_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF */
};


#define SPI_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Spi_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */


