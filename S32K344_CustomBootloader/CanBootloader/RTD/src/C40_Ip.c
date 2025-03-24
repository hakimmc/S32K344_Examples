/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : C40
*   Dependencies         : None
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
 * @file       C40_Ip.c
 *
 * @addtogroup C40_IP
 * implements  C40_Ip.c_Artifact
 *
 * @{
 */

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "C40_Ip.h"

#if (STD_ON == C40_IP_SYNCRONIZE_CACHE)
#include "Cache_Ip.h"
#endif

#if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
#define USER_MODE_REG_PROT_ENABLED      STD_ON
#include "RegLockMacros.h"
#endif

#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
#include "OsIf.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define C40_IP_VENDOR_ID_C                    43
#define C40_IP_AR_RELEASE_MAJOR_VERSION_C     4
#define C40_IP_AR_RELEASE_MINOR_VERSION_C     7
#define C40_IP_AR_RELEASE_REVISION_VERSION_C  0
#define C40_IP_SW_MAJOR_VERSION_C             3
#define C40_IP_SW_MINOR_VERSION_C             0
#define C40_IP_SW_PATCH_VERSION_C             0


/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#if 0
/* Check if current file and C40_Ip header file are of the same vendor */
#if (C40_IP_VENDOR_ID_C != C40_IP_VENDOR_ID_H)
    #error "C40_Ip.c and C40_Ip.h have different vendor ids"
#endif
/* Check if current file and C40_Ip header file are of the same Autosar version */
#if ((C40_IP_AR_RELEASE_MAJOR_VERSION_C    != C40_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (C40_IP_AR_RELEASE_MINOR_VERSION_C    != C40_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (C40_IP_AR_RELEASE_REVISION_VERSION_C != C40_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of C40_Ip.c and C40_Ip.h are different"
#endif
/* Check if current file and C40_Ip header file are of the same Software version */
#if ((C40_IP_SW_MAJOR_VERSION_C != C40_IP_SW_MAJOR_VERSION_H) || \
     (C40_IP_SW_MINOR_VERSION_C != C40_IP_SW_MINOR_VERSION_H) || \
     (C40_IP_SW_PATCH_VERSION_C != C40_IP_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of C40_Ip.c and C40_Ip.h are different"
#endif

#if (STD_ON == C40_IP_SYNCRONIZE_CACHE)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
        /* Check if current file and Cache_Ip header file are of the same Autosar version */
        #if ((C40_IP_AR_RELEASE_MAJOR_VERSION_C != CACHE_IP_AR_RELEASE_MAJOR_VERSION) || \
             (C40_IP_AR_RELEASE_MINOR_VERSION_C != CACHE_IP_AR_RELEASE_MINOR_VERSION) \
            )
            #error "Autosar Version Numbers of C40_Ip.c and Cache_Ip.h are different"
        #endif
    #endif
#endif /* C40_IP_SYNCRONIZE_CACHE */

#if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
        /* Check if current file and RegLockMacros.h header file are of the same Autosar version */
        #if ((C40_IP_AR_RELEASE_MAJOR_VERSION_C != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
             (C40_IP_AR_RELEASE_MINOR_VERSION_C != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION) \
            )
            #error "Autosar Version Numbers of C40_Ip.c and RegLockMacros.h are different"
        #endif
        /* Check if current file and Mcal.h header file are of the same Autosar version */
        #if ((C40_IP_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
             (C40_IP_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
            )
            #error "Autosar Version Numbers of C40_Ip.c and Mcal.h are different"
        #endif
    #endif
#endif /* #if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT) */

#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
        /* Check if current file and OsIf.h header file are of the same Autosar version */
        #if ((C40_IP_AR_RELEASE_MAJOR_VERSION_C != OSIF_AR_RELEASE_MAJOR_VERSION) || \
             (C40_IP_AR_RELEASE_MINOR_VERSION_C != OSIF_AR_RELEASE_MINOR_VERSION) \
            )
            #error "AutoSar Version Numbers of C40_Ip.c and OsIf.h are different"
        #endif
    #endif
#endif
#endif

/*==================================================================================================
                                   LOCAL MACROS
==================================================================================================*/
/* Mask of failed address regions: A0-A5
   If the region is not present, the bit field is locked to 0
 */
#define FLASH_REGION_0_MASK                         (FLASH_ADR_A0_MASK << 0U)
#define FLASH_REGION_1_MASK                         (FLASH_ADR_A0_MASK << 1U)
#define FLASH_REGION_2_MASK                         (FLASH_ADR_A0_MASK << 2U)
#define FLASH_REGION_3_MASK                         (FLASH_ADR_A0_MASK << 3U)
#define FLASH_REGION_4_MASK                         (FLASH_ADR_A0_MASK << 4U)
#define FLASH_REGION_5_MASK                         (FLASH_ADR_A0_MASK << 5U)

#define FLASH_FAILED_ADDRESS_REGION_MASK            (FLASH_REGION_0_MASK  | \
                                                     FLASH_REGION_1_MASK  | \
                                                     FLASH_REGION_2_MASK  | \
                                                     FLASH_REGION_3_MASK  | \
                                                     FLASH_REGION_4_MASK  | \
                                                     FLASH_REGION_5_MASK)


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define MEM_43_INFLS_START_SEC_CODE
#include "Mem_43_InFls_MemMap.h"

static inline uint8 C40_Ip_ReadData8(uint32 Address);
static inline uint32 C40_Ip_ReadData32(uint32 Address);
static inline uint16 C40_Ip_ReadData16(uint32 Address);

static uint32 C40_Ip_ReadData(uint32 ReadAddress,
                              uint8 *DesAddressPtr,
                              uint32 SizeLeft
                             );

static C40_Ip_StatusType C40_Ip_ReadCheckInputParams(uint32 Length,
                                                     const uint8 *DestAddressPtr
                                                    );

static C40_Ip_StatusType C40_Ip_ClearPreviousRead(uint32 ReadAddress);

static C40_Ip_StatusType C40_Ip_CheckReadCompareStatus(uint32 ReadAddress,
                                                       boolean CompareResult
                                                      );

static void C40_Ip_ProgramVerify(uint32 Address,
                                 const uint8 *Data,
                                 uint32 Size
                                );

static void C40_Ip_EraseVerify(uint32 Address,
                               uint32 Size
                              );

static uint32 C40_Ip_CompareData(uint32 ReadAddress,
                                 uint32 DataAddress,
                                 uint32 SizeLeft,
                                 boolean *CompareResult
                                );

static uint32 C40_Ip_CompareBlank(uint32 ReadAddress,
                                  uint32 SizeLeft,
                                  boolean *CompareResult
                                 );

static C40_Ip_StatusType C40_Ip_UTestCheckBusy(void);
static void C40_Ip_UTestCheckBreakpoint(C40_Ip_FlashBreakPointsType BreakPoints);

static inline C40_Ip_StatusType C40_Ip_ArrayIntegrityResumeSuspended(void);
static inline C40_Ip_StatusType C40_Ip_ArrayIntegrityResumeBroken(void);

static C40_Ip_FlashBlocksNumberType C40_Ip_GetCodeBlockNumber(uint32 TargetAddress);

static uint32 C40_Ip_GetSectorID(C40_Ip_VirtualSectorsType VirtualSector);

static uint32 C40_Ip_GetBaseAddressOfSector(C40_Ip_VirtualSectorsType VirtualSectors);

static C40_Ip_StatusType C40_Ip_CheckUserTestStatusExecution(const C40_Ip_MisrType *MisrExpectedValues,
                                                             C40_Ip_UtestStateType *OpStatus
                                                            );

static C40_Ip_StatusType C40_Ip_CheckLockDomainID(C40_Ip_VirtualSectorsType VirtualSector,
                                                  uint8 DomainIdValue
                                                 );
/* Trusted Function */
void C40_Ip_CheckLockDomainID_CheckRegister(C40_Ip_VirtualSectorsType VirtualSector,
                                            uint32 *CheckRegister,
                                            uint32 *TempLockMasterRegister
                                           );

static boolean C40_Ip_CheckSelecBlock(uint32 SelectBlock);
static void C40_Ip_SetSeedMisr(const C40_Ip_MisrType *MisrSeedValues);

void C40_Ip_DataErrorSuppression(void);
#if (STD_ON == FLS_BLOCK_4_PIPE_SELECTABLE)
void C40_Ip_Block4PipeSelect(void);
#endif


#if ( (C40_ECC_CHECK == STD_ON) || (C40_ECC_CHECK_BY_AUTOSAR_OS == STD_ON) )
static C40_Ip_StatusType C40_Ip_InvalidPrefetchBuff(uint32 StartAddress);
static C40_Ip_StatusType C40_Ip_EccTest(uint32 ReadAddress);
/* Trusted Function */
uint32 C40_Ip_GetPflashDataErrorSuppressionStatus(void);
#endif

#if (STD_ON == C40_MAIN_INTERFACE_ENABLED)
static inline void C40_Ip_ClearAllErrorFlagsMainInterface(void);

static C40_Ip_StatusType C40_Ip_InitMainInterface(void);

static C40_Ip_StatusType C40_Ip_MainInterfaceAbort(void);

static C40_Ip_StatusType C40_Ip_MainInterfaceHVJobStatus(void);

static inline C40_Ip_StatusType C40_Ip_MainInterfaceSectorErasePreCheck(C40_Ip_VirtualSectorsType VirtualSector);

static inline C40_Ip_StatusType C40_Ip_MainInterfaceWritePreCheck(uint32 LogicalAddress,
                                                                  uint32 Length,
                                                                  const uint8 *SourceAddressPtr
                                                                 );

static void C40_Ip_ClearInterlockWrite(void);

static C40_Ip_StatusType C40_Ip_MainInterfaceWriteJobAddress(uint32 PhysicalAddress,
                                                             uint8 DomainIdValue
                                                            );

void C40_Ip_MainInterfaceWriteLogicalAddress(uint32 Address);

static void C40_Ip_MainInterfaceFillDataBuff(uint32 LocationWriteDataRegs,
                                             const uint8 *DataPtr,
                                             uint32 Size
                                            );
#endif


#if (STD_ON == C40_SECTOR_SET_LOCK_API)
void C40_Ip_SetLockProtect(C40_Ip_VirtualSectorsType VirtualSector);
#endif

uint32 C40_Ip_GetLockProtect(C40_Ip_VirtualSectorsType VirtualSector);
void C40_Ip_ClearLockProtect(C40_Ip_VirtualSectorsType VirtualSector);

#if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
void C40_Ip_SetUserAccessAllowed(void);
#endif

static inline void C40_Ip_FlashAccessCalloutStart(void);
static inline void C40_Ip_FlashAccessCalloutFinish(void);

#if (STD_ON == C40_IP_SYNCRONIZE_CACHE)
static inline void C40_Ip_SynchronizeCache(uint32 Address,
                                           uint32 Length
                                          );
#endif

static inline boolean C40_Ip_ValidCodeAddress(uint32 Address);

static inline boolean C40_Ip_ValidDataAddress(uint32 Address);

static inline boolean C40_Ip_ValidUTestAddress(uint32 Address);

static inline boolean C40_Ip_ValidAddress(uint32 Address);

static inline boolean C40_Ip_ValidRangeAddress(uint32 StartAddress,
                                               uint32 Length
                                              );

#define MEM_43_INFLS_STOP_SEC_CODE
#include "Mem_43_InFls_MemMap.h"


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#define MEM_43_INFLS_START_SEC_VAR_CLEARED_32
#include "Mem_43_InFls_MemMap.h"

#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
uint32 C40_Ip_u32ElapsedTicks;
uint32 C40_Ip_u32TimeoutTicks;
uint32 C40_Ip_u32CurrentTicks;
#endif

#if ((STD_ON == C40_PROGRAM_VERIFICATION_ENABLED) || (STD_ON == C40_IP_SYNCRONIZE_CACHE))
static uint32 C40_Ip_u32ProgrammedAddress;
static uint32 C40_Ip_u32ProgrammedLength;
#endif
#if (STD_ON == C40_PROGRAM_VERIFICATION_ENABLED)
static const uint8 *C40_Ip_pProgrammedData;
#endif

#if ((STD_ON == C40_ERASE_VERIFICATION_ENABLED) || (STD_ON == C40_IP_SYNCRONIZE_CACHE))
static uint32 C40_Ip_u32ErasedSectorAddress;
#endif

static uint32 C40_Ip_u32SectorId;
static uint32 C40_Ip_u32BitPosition;

#if ( (C40_ECC_CHECK == STD_ON) || (C40_ECC_CHECK_BY_AUTOSAR_OS == STD_ON) )
/* Save the most recent memory access address for ECC handling */
static volatile uint32 C40_Ip_u32ReadAddress;
#endif

static uint32 C40_Ip_u32LogicalAddressCheckFail;

#define MEM_43_INFLS_STOP_SEC_VAR_CLEARED_32
#include "Mem_43_InFls_MemMap.h"


#define MEM_43_INFLS_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mem_43_InFls_MemMap.h"

#if ( (C40_ECC_CHECK == STD_ON) || (C40_ECC_CHECK_BY_AUTOSAR_OS == STD_ON) )
static volatile C40_Ip_StatusType C40_Ip_eReadStatus = STATUS_C40_IP_ERROR;
#else
static C40_Ip_StatusType C40_Ip_eReadStatus = STATUS_C40_IP_ERROR;
#endif

#define MEM_43_INFLS_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mem_43_InFls_MemMap.h"

#define MEM_43_INFLS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mem_43_InFls_MemMap.h"

static C40_Ip_UtestStateType C40_Ip_eOpStatus;

/**
 * @brief Pointer to current flash module configuration set
 */
static const C40_ConfigType * C40_Ip_pConfigPtr;

#define MEM_43_INFLS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Mem_43_InFls_MemMap.h"

#define MEM_43_INFLS_START_SEC_VAR_INIT_BOOLEAN
#include "Mem_43_InFls_MemMap.h"

static boolean C40_Ip_bAsync = TRUE;

#define MEM_43_INFLS_STOP_SEC_VAR_INIT_BOOLEAN
#include "Mem_43_InFls_MemMap.h"


#define MEM_43_INFLS_START_SEC_CONST_UNSPECIFIED
#include "Mem_43_InFls_MemMap.h"

/* Base address for FLASH instance */
FLASH_Type * const C40_Ip_pFlashBaseAddress = IP_FLASH;

/* Base address for PFLASH instance */
static PFLASH_Type * const C40_Ip_pPFlashBaseAddress = IP_PFLASH;

#define MEM_43_INFLS_STOP_SEC_CONST_UNSPECIFIED
#include "Mem_43_InFls_MemMap.h"


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MEM_43_INFLS_START_SEC_CODE
#include "Mem_43_InFls_MemMap.h"

/**
 * Function Name    C40_Ip_Init
 * Description      This function will initialize c40 module and clear all error flags.
 *
 * @implements      C40_Ip_Init_Activity
 */
C40_Ip_StatusType C40_Ip_Init(const C40_ConfigType * InitConfig)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_ERROR;

    C40_IP_DEV_ASSERT(InitConfig != NULL_PTR );

#if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
    /* Enable user mode support */
    OsIf_Trusted_Call(C40_Ip_SetUserAccessAllowed);
#endif /* STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT */

/**  Single-bit and multi-bit ECC events on data flash memory accesses are suppressed Or not */
#if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
    OsIf_Trusted_Call(C40_Ip_DataErrorSuppression);
#else
    C40_Ip_DataErrorSuppression();
#endif /* STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT */

#if (STD_ON == FLS_BLOCK_4_PIPE_SELECTABLE)
/* Selects the active pipe for flash memory block 4 access */
#if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
    OsIf_Trusted_Call(C40_Ip_Block4PipeSelect);
#else
    C40_Ip_Block4PipeSelect();
#endif /* STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT */
#endif /* #if (STD_ON == FLS_BLOCK_4_PIPE_SELECTABLE) */

#if (STD_ON == C40_MAIN_INTERFACE_ENABLED)
    /** Init with Main interface **/
    ReturnCode = C40_Ip_InitMainInterface();
#endif

    C40_Ip_pConfigPtr = InitConfig;
    return ReturnCode;
}

#if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
/**
* @brief        Enable user mode support to access c40asf and PFLASH registers
*
* @details      Set UAA bit in FLASH_REG_PROT_GCR to allow user access locked registers in c40asf and PFLASH module
*
* @param[in]    none
* @retval       none
*
* @pre          The user mode is enabled
*
*/
void C40_Ip_SetUserAccessAllowed(void)
{
#if (STD_ON == C40_MAIN_INTERFACE_ENABLED)
    /* Set UAA bit in REG_PROT register of FLASH controlled */
    SET_USER_ACCESS_ALLOWED(IP_FLASH_BASE, C40_MAIN_INTERFACE_REG_PROT_SIZE);
#endif
}
#endif /* STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT */

/**
 * Function Name    C40_Ip_DataErrorSuppression
 * Description      Single-bit and multi-bit ECC events on data flash memory accesses are suppressed or not
 */
void C40_Ip_DataErrorSuppression(void)
{
#if (STD_ON == C40_DATA_FLASH_ERROR_SUPPRESSION)
    /* 1b - Single-bit and multi-bit ECC events on data flash memory accesses are suppressed */
    C40_Ip_pPFlashBaseAddress->PFCR4 |= PFLASH_PFCR4_DERR_SUP_MASK;
#else
    /* 0b - Reports ECC events on data flash memory accesses */
    C40_Ip_pPFlashBaseAddress->PFCR4 &= ~PFLASH_PFCR4_DERR_SUP_MASK;
#endif /* #if (STD_ON == C40_DATA_FLASH_ERROR_SUPPRESSION) */
}

#if (STD_ON == FLS_BLOCK_4_PIPE_SELECTABLE)
/**
 * Function Name    C40_Ip_Block4PipeSelect
 * Description      Selects the active pipe for flash memory block 4 access
 */
void C40_Ip_Block4PipeSelect(void)
{
    /* Clear BLK4_PS bitfield */
    C40_Ip_pPFlashBaseAddress->PFCR4 &= ~PFLASH_PFCR4_BLK4_PS_MASK;
    /* Selects the active pipe */
    C40_Ip_pPFlashBaseAddress->PFCR4 |= PFLASH_PFCR4_BLK4_PS(C40_BLOCK4_PIPE_SELECT);
}
#endif /* #if (STD_ON == FLS_BLOCK_4_PIPE_SELECTABLE) */

/**
 * Function Name    C40_Ip_Abort
 * Description      Abort a program or erase operation
 *
 * @implements      C40_Ip_Abort_Activity
 */
C40_Ip_StatusType C40_Ip_Abort(void)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_ERROR;
#if (STD_ON == C40_MAIN_INTERFACE_ENABLED)
    /** Abort Main interface jobs **/
    ReturnCode = C40_Ip_MainInterfaceAbort();
#endif

    return ReturnCode;
}


/**
 * @brief       Check status after memory accessing of Read/Compare operations
 *
 * @return      the status of the most recent memory access
 * @retval      STATUS_C40_IP_ERROR     Hardware errors or ECC happened or there was a compare error
 * @retval      STATUS_C40_IP_SUCCESS   Everything was ok
 */
static C40_Ip_StatusType C40_Ip_CheckReadCompareStatus(uint32 ReadAddress,
                                                       boolean CompareResult
                                                      )
{
    #if ( (C40_ECC_CHECK == STD_OFF) && (C40_ECC_CHECK_BY_AUTOSAR_OS == STD_OFF) )
    (void)ReadAddress;
    #endif
    C40_Ip_StatusType Status = STATUS_C40_IP_ERROR;
    uint32 ErrorFlags;

    /* Check everything in order of priority: hardware > ECC > DATA Syndrome > compare */

    /* Step 1: Check for hardware errors */
    ErrorFlags = C40_Ip_pFlashBaseAddress->MCRS & (FLASH_MCRS_AEE_MASK |
                                            FLASH_MCRS_EEE_MASK |
                                            FLASH_MCRS_RVE_MASK |
                                            FLASH_MCRS_RRE_MASK |
                                            FLASH_MCRS_RWE_MASK);

    if (0U != ErrorFlags)
    {
        /* Clear all error flags: write 1 to clear */
        C40_Ip_pFlashBaseAddress->MCRS &= ErrorFlags;
        /* Hardware errors: change read status to error state */
        C40_Ip_eReadStatus = STATUS_C40_IP_ERROR;
    }
#if ( (C40_ECC_CHECK == STD_ON) || (C40_ECC_CHECK_BY_AUTOSAR_OS == STD_ON) )
    /* Step 2: Checking if eec happened */
    else if (STATUS_C40_IP_ERROR == C40_Ip_eReadStatus)
    {
        /* ECC happened in the DsiHandler: keep the current status */
    }

    /* Step 3: Checking DERR_SUP bit to decide ECC on data flash occurred or not */
    else if (STATUS_C40_IP_SUCCESS != C40_Ip_EccTest(ReadAddress))
    {
        C40_Ip_eReadStatus = STATUS_C40_IP_ERROR;
    }
#endif
    /* Step 4: Check for compare error */
    else if ((boolean)TRUE != CompareResult)
    {
        /* Compare error: update read status */
        C40_Ip_eReadStatus = STATUS_C40_IP_ERROR_PROGRAM_VERIFY;
    }
    else
    {
        /* Everything was ok */
        Status = STATUS_C40_IP_SUCCESS;
    }

    return Status;
}


#if (STD_ON == C40_IP_SYNCRONIZE_CACHE)
static inline void C40_Ip_SynchronizeCache(uint32 Address,
                                           uint32 Length
                                          )
{
    /* Invalidate cache */
    (void)Cache_Ip_InvalidateByAddr(CACHE_IP_CORE, CACHE_IP_DATA, Address, Length);
}
#endif


/**
 * Function Name    C40_Ip_ReadData32
 * Description      Reads 4 bytes from the specified address
 */
static inline uint32 C40_Ip_ReadData32(uint32 Address)
{
    return (*((uint32 *)Address));
}


/**
 * Function Name    C40_Ip_ReadData16
 * Description      Reads 2 bytes from the specified address
 */
static inline uint16 C40_Ip_ReadData16(uint32 Address)
{
    return (*((uint16 *)Address));
}


/**
 * Function Name    C40_Ip_ReadData8
 * Description      Reads 1 byte from the specified address
 */
static inline uint8 C40_Ip_ReadData8(uint32 Address)
{
    return (*((uint8 *)Address));
}

/**
 * Function Name    C40_Ip_SetSeedMisr
 * Description      Set the seed values of the MISR in UMx registers
 */
static void C40_Ip_SetSeedMisr(const C40_Ip_MisrType *MisrSeedValues)
{
    uint8 Counter;

    if (NULL_PTR == MisrSeedValues)
    {
        for (Counter = 0U; Counter < FLASH_UM_COUNT; Counter++)
        {
            C40_Ip_pFlashBaseAddress->UM[Counter] = 0U;
        }
        C40_Ip_pFlashBaseAddress->UM9 = 0U;
    }
    else
    {
        for (Counter = 0U; Counter < FLASH_UM_COUNT; Counter++)
        {
            C40_Ip_pFlashBaseAddress->UM[Counter] = MisrSeedValues->arrMISRValue[Counter];
        }
        C40_Ip_pFlashBaseAddress->UM9 = MisrSeedValues->arrMISRValue[9];
    }
}

/**
 * Function Name    C40_Ip_ReadData
 * Description      Accesses the flash to read data to user buffer
 */
static uint32 C40_Ip_ReadData(uint32 ReadAddress,
                              uint8 *DesAddressPtr,
                              uint32 SizeLeft
                             )
{
    uint32 ReadSize;
    uint32 DesAddress = (uint32)DesAddressPtr;
    /* Combine two addresses for faster alignment checking */
    uint32 CombinedAddress = ReadAddress | DesAddress;

    /* Both the lowest two bits are zero: 4 bytes aligned */
    if ( (0UL == (CombinedAddress & 0x03UL)) && (SizeLeft >= FLS_SIZE_4BYTE) )
    {
        /* 4 bytes operation */
        ReadSize = FLS_SIZE_4BYTE;
        *((uint32 *)DesAddress) = C40_Ip_ReadData32(ReadAddress);
    }
    /* Both the lowest one bit are zero: 2 bytes aligned */
    else if ( (0UL == (CombinedAddress & 0x01UL)) && (SizeLeft >= FLS_SIZE_2BYTE) )
    {
        /* 2 bytes operation */
        ReadSize = FLS_SIZE_2BYTE;
        *((uint16 *)DesAddress) = C40_Ip_ReadData16(ReadAddress);
    }
    else
    {
        /* 1 byte operation */
        ReadSize = FLS_SIZE_1BYTE;
        *DesAddressPtr = C40_Ip_ReadData8(ReadAddress);  /* Using uint8 directly to avoid pointer casting */
    }

    return ReadSize;
}


/**
 * Function Name    C40_Ip_ReadCheckInputParams
 * Description      Checks the input parameters for C40_Ip_Read
 */
static C40_Ip_StatusType C40_Ip_ReadCheckInputParams(uint32 Length,
                                                     const uint8 *DestAddressPtr
                                                    )
{
    C40_Ip_StatusType Status = STATUS_C40_IP_ERROR_INPUT_PARAM;

    /* Check 1: The user buffer pointer cannot be a null pointer */
    if (NULL_PTR == DestAddressPtr)
    {
        /* Wrong input parameters */
    }
    /* Check 2: The read length must be greater than zero */
    else if (0UL == Length)
    {
        /* Wrong input parameters */
    }
    else
    {
        /* Reaching here means that everything is ok */
        Status = STATUS_C40_IP_SUCCESS;
    }

    return Status;
}


/**
 * Function Name    C40_Ip_ClearPreviousRead
 * Description      Prepare before accessing to the flash memory
 *                  Clear all hardware flags and invalidate the prefetch buffer in ECC check is enabled
 */
static C40_Ip_StatusType C40_Ip_ClearPreviousRead(uint32 ReadAddress)
{
    C40_Ip_StatusType Status = STATUS_C40_IP_SUCCESS;

    /* Clear all the error flags */
    #if (STD_ON == C40_MAIN_INTERFACE_ENABLED)
    C40_Ip_ClearAllErrorFlagsMainInterface();
    #endif

#if ( (STD_ON == C40_ECC_CHECK) || (STD_ON == C40_ECC_CHECK_BY_AUTOSAR_OS) )
    /* Save the current memory access address for ECC handling */
    C40_Ip_u32ReadAddress = ReadAddress;

    /* Invalidate prefect buffer before reading to make sure ecc will occur all times */
    Status = C40_Ip_InvalidPrefetchBuff(ReadAddress);
    if (STATUS_C40_IP_SUCCESS != Status)
    {
        /* Save the read status */
        C40_Ip_eReadStatus = Status;
    }
#else
    (void)ReadAddress;
#endif

    return Status;
}


/**
 * Function Name    C40_Ip_Read
 * Description      This function fills data to DestAddressPtr with data from the specified address
 *
 * @implements      C40_Ip_Read_Activity
 */
C40_Ip_StatusType C40_Ip_Read(uint32 LogicalAddress,
                              uint32 Length,
                              uint8 *DestAddressPtr
                             )
{
    uint32 ReadAddress = LogicalAddress;
    uint8 *DesAddressPtr = DestAddressPtr;
    uint32 SizeLeft = Length;
    uint32 ReadSize;
    C40_Ip_StatusType Status;

    C40_IP_DEV_ASSERT(Length > 0UL);
    C40_IP_DEV_ASSERT(DestAddressPtr != NULL_PTR);
    C40_IP_DEV_ASSERT( C40_Ip_ValidRangeAddress(LogicalAddress, Length) );

    /* Checking before reading */
    C40_Ip_eReadStatus = C40_Ip_ReadCheckInputParams(Length, DestAddressPtr);

    /* Everything is ready for a new read operation */
    if (STATUS_C40_IP_SUCCESS == C40_Ip_eReadStatus)
    {
        /* Change to busy state */
        C40_Ip_eReadStatus = STATUS_C40_IP_BUSY;

        /* Invalidate cache */
        #if (STD_ON == C40_IP_SYNCRONIZE_CACHE)
        C40_Ip_SynchronizeCache(ReadAddress, SizeLeft);
        #endif

        /* Start read operation */
        do
        {
            /* Prepare before access to the flash memory */
            Status = C40_Ip_ClearPreviousRead(ReadAddress);

            if (STATUS_C40_IP_SUCCESS == Status)
            {
                /* Start flash access */
                C40_Ip_FlashAccessCalloutStart();

                /* Access the flash to read data to user buffer */
                ReadSize = C40_Ip_ReadData(ReadAddress, DesAddressPtr, SizeLeft);

                /* Finish flash access */
                C40_Ip_FlashAccessCalloutFinish();

                /* Check for hardware errors or ECC happened */
                Status = C40_Ip_CheckReadCompareStatus(ReadAddress, TRUE);
            }

            if (STATUS_C40_IP_SUCCESS != Status)
            {
                break;
            }

            /* Move to the next data */
            ReadAddress  += ReadSize;
            DesAddressPtr = &DesAddressPtr[ReadSize];
            SizeLeft     -= ReadSize;
        }
        while (0UL < SizeLeft);

        /* Checking if working was successful: the requested bytes were copied and no errors happened */
        if (0UL == SizeLeft)
        {
            /* Mark as success */
            C40_Ip_eReadStatus = STATUS_C40_IP_SUCCESS;
        }
    }

    return C40_Ip_eReadStatus;
}


#if ( (C40_ECC_CHECK == STD_ON) || (C40_ECC_CHECK_BY_AUTOSAR_OS == STD_ON) )
/**
 * Function Name    C40_Ip_EccTest
 * Description      Checking DERR_SUP bit to decide ecc on data flash occurred or not
 */
static C40_Ip_StatusType C40_Ip_EccTest(uint32 ReadAddress)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_ERROR;
    uint32 ReadECCValue;
    uint32 ErrorFlags;

    /* Check for errors */
    ErrorFlags = C40_Ip_pFlashBaseAddress->MCRS;
    /* If ECC flag was set and in Data sectors */
    if (( 0U != (ErrorFlags & FLASH_MCRS_EER_MASK)) && ((uint32)C40_DATA_BASE_ADDRESS <= ReadAddress) && (ReadAddress <= (uint32)C40_DATA_END_ADDRESS))
    {
        /* If DERR_SUP was set and Single-bit and multi-bit ECC events on data flash memory accesses are suppressed */
        #if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
        if (0U != OsIf_Trusted_Call_Return(C40_Ip_GetPflashDataErrorSuppressionStatus))
        #else
        if (0U != C40_Ip_GetPflashDataErrorSuppressionStatus())
        #endif
        {
            /* Read opcode to decide the exact ecc area */
            ReadECCValue = *(volatile uint32 *)(ReadAddress - ((uint32)ReadAddress % 4U));
            /* Checking if ecc or not */
            if (C40_ECC_VALUE == ReadECCValue)
            {
                ReturnCode = STATUS_C40_IP_ERROR;
            }
            else
            {
                ReturnCode = STATUS_C40_IP_SUCCESS;
            }
        }
        else
        {
            ReturnCode = STATUS_C40_IP_SUCCESS;
        }
        /* Clear ecc flag */
        C40_Ip_pFlashBaseAddress->MCRS &= FLASH_MCRS_EER_MASK;
    }
    else
    {
        ReturnCode = STATUS_C40_IP_SUCCESS;
    }

    return ReturnCode;
}


/**
 * Function Name    C40_Ip_GetPflashDataErrorSuppressionStatus
 * Description      Read DERR_SUP bit to get the data error suppression status
 */
uint32 C40_Ip_GetPflashDataErrorSuppressionStatus(void)
{
    /* Get the data error suppression status */
    return (C40_Ip_pPFlashBaseAddress->PFCR4 & PFLASH_PFCR4_DERR_SUP_MASK);
}
#endif /* (C40_ECC_CHECK == STD_ON) || (C40_ECC_CHECK_BY_AUTOSAR_OS == STD_ON) */


#if (STD_ON == C40_SECTOR_SET_LOCK_API)
/**
 * Function Name    C40_Ip_SetLock
 * Description      Locks the selected sector for the requesting core if possible
 *
 * @implements      C40_Ip_SetLock_Activity
 */
C40_Ip_StatusType C40_Ip_SetLock(C40_Ip_VirtualSectorsType VirtualSector,
                                 uint8 DomainIdValue
                                )
{
    C40_Ip_StatusType ReturnCode;

    C40_IP_DEV_ASSERT((uint32)VirtualSector <= FLS_MAX_VIRTUAL_SECTOR);

    ReturnCode = C40_Ip_GetLock(VirtualSector);

    if (STATUS_C40_IP_ERROR == ReturnCode)
    {
        /* Return immediately if encountered an error */
    }
    else if (STATUS_C40_IP_SECTOR_PROTECTED == ReturnCode)
    {
        /* This sector has been already locked */
        ReturnCode = STATUS_C40_IP_SUCCESS;
    }
    else
    {
        /* Check the lock Domain Id */
        ReturnCode = C40_Ip_CheckLockDomainID(VirtualSector, DomainIdValue);
        if (STATUS_C40_IP_SUCCESS == ReturnCode)
        {
            #if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
            OsIf_Trusted_Call1param(C40_Ip_SetLockProtect, VirtualSector);
            #else
            C40_Ip_SetLockProtect(VirtualSector);
            #endif
        }
    }

    return ReturnCode;
}


void C40_Ip_SetLockProtect(C40_Ip_VirtualSectorsType VirtualSector)
{
    uint32 SectorIndex;
    uint32 BlockCount;
    uint32 SectorPosition;

    /* All checks passed - set lock bit */
    if ((uint32)VirtualSector < FLS_MAX_DATA_SECTOR)
    {
        /* Sector is in the Data Block _ Block 4 for K3x4, _ Block 2 for K3x2 */
        C40_Ip_pPFlashBaseAddress->PFCBLK_SPELOCK[FLS_DATA_PFCBLK_ORDER] |= C40_Ip_u32BitPosition;
    }
    else if (FLS_MAX_VIRTUAL_SECTOR == (uint32)VirtualSector)
    {
        /* Sector is in Utest */
        C40_Ip_pPFlashBaseAddress->PFCBLKU_SPELOCK[0] |= C40_Ip_u32BitPosition;
    }
    else
    {
        SectorIndex    = (uint32)VirtualSector - FLS_MAX_DATA_SECTOR;
        /* divide by 128: each block 1MB has 128 sectors */
        /* divide by 256: each block 2MB has 256 sectors */
        BlockCount     = SectorIndex / FLS_NO_OF_SECTOR_PER_BLOCK;
        SectorPosition = SectorIndex & (FLS_NO_OF_SECTOR_PER_BLOCK - 1U);  /* the position sectors 8KB per block */

        /* For 1 MB blocks, the first 768KB (96 sectors 8KB) is protected with super sector granularity */
        /* For 2 MB blocks, the first 1972KB (224 sectors 8KB) is protected with super sector granularity */
        if (SectorPosition < (FLS_NO_OF_SUPPER_SECTOR_PER_BLOCK * 8U))
        {
            /* Sector is in the Super Sector zone */
            C40_Ip_pPFlashBaseAddress->PFCBLK_SSPELOCK[BlockCount] |= C40_Ip_u32BitPosition;
        }
        else
        {
            /* Sector is in the 8KB Sector zone */
            C40_Ip_pPFlashBaseAddress->PFCBLK_SPELOCK[BlockCount] |= C40_Ip_u32BitPosition;
        }
    }
}
#endif /* STD_ON == C40_SECTOR_SET_LOCK_API */


/**
 * Function Name    C40_Ip_GetLock
 * Description      Returns the locking status of the selected sector
 *
 * @implements      C40_Ip_GetLock_Activity
 */
C40_Ip_StatusType C40_Ip_GetLock(C40_Ip_VirtualSectorsType VirtualSector)
{
    C40_Ip_StatusType ReturnCode;
    uint32 CheckRegister;

    C40_IP_DEV_ASSERT((uint32)VirtualSector <= FLS_MAX_VIRTUAL_SECTOR);

    /* Sector is out of range */
    if ((uint32)VirtualSector > FLS_MAX_VIRTUAL_SECTOR)
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    else
    {
        #if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
        CheckRegister = OsIf_Trusted_Call_Return1param(C40_Ip_GetLockProtect, VirtualSector);
        #else
        CheckRegister = C40_Ip_GetLockProtect(VirtualSector);
        #endif

        /* Place the checking here to prevent HIS_CCM */
        /* Check the register's value */
        if (0U == CheckRegister)
        {
            ReturnCode = STATUS_C40_IP_SECTOR_UNPROTECTED;
        }
        else
        {
            ReturnCode = STATUS_C40_IP_SECTOR_PROTECTED;
        }
    }

    return ReturnCode;
}


uint32 C40_Ip_GetLockProtect(C40_Ip_VirtualSectorsType VirtualSector)
{
    uint32 SectorIndex;
    uint32 BlockCount;
    uint32 SectorPosition;
    uint32 CheckRegister;

    C40_Ip_u32SectorId = C40_Ip_GetSectorID(VirtualSector);
    C40_Ip_u32BitPosition = (uint32) 1U << C40_Ip_u32SectorId;

    /* Sector is in the Data Block _ Block 4 for K3x4, _ Block 2 for K3x2 */
    if ((uint32)VirtualSector < FLS_MAX_DATA_SECTOR)
    {
        CheckRegister = C40_Ip_pPFlashBaseAddress->PFCBLK_SPELOCK[FLS_DATA_PFCBLK_ORDER];
    }
    /* Sector is in Utest*/
    else if (FLS_MAX_VIRTUAL_SECTOR == (uint32)VirtualSector)
    {
        CheckRegister = C40_Ip_pPFlashBaseAddress->PFCBLKU_SPELOCK[0];
    }
    else
    {
        SectorIndex    = (uint32)VirtualSector - FLS_MAX_DATA_SECTOR;
        /* divide by 128: each block 1MB has 128 sectors */
        /* divide by 256: each block 2MB has 256 sectors */
        BlockCount     = SectorIndex / FLS_NO_OF_SECTOR_PER_BLOCK;
        SectorPosition = SectorIndex & (FLS_NO_OF_SECTOR_PER_BLOCK - 1U);  /* the position sectors 8KB per block */

        /* For 1 MB blocks, the first 768KB (96 sectors 8KB) is protected with super sector granularity */
        /* For 2 MB blocks, the first 1972KB (224 sectors 8KB) is protected with super sector granularity */
        if (SectorPosition < (FLS_NO_OF_SUPPER_SECTOR_PER_BLOCK * 8U))
        {
            /* Sector is in the Super Sector zone */
            CheckRegister = C40_Ip_pPFlashBaseAddress->PFCBLK_SSPELOCK[BlockCount];
        }
        else
        {
            /* Sector is in the 8KB Sector zone */
            CheckRegister = C40_Ip_pPFlashBaseAddress->PFCBLK_SPELOCK[BlockCount];
        }
    }

    return (CheckRegister & C40_Ip_u32BitPosition);
}

/**
 * Function Name    C40_Ip_ClearLock
 * Description      Unlocks the selected sector for the requesting core if possible
 *
 * @implements      C40_Ip_ClearLock_Activity
 */
C40_Ip_StatusType C40_Ip_ClearLock(C40_Ip_VirtualSectorsType VirtualSector,
                                   uint8 DomainIdValue
                                  )
{
    C40_Ip_StatusType ReturnCode;

    C40_IP_DEV_ASSERT((uint32)VirtualSector <= FLS_MAX_VIRTUAL_SECTOR);

    ReturnCode = C40_Ip_GetLock(VirtualSector);
    if (STATUS_C40_IP_ERROR == ReturnCode)
    {
        /* Return immediately if encountered an error */
    }
    else if (STATUS_C40_IP_SECTOR_UNPROTECTED == ReturnCode)
    {
        /* This sector has been already unlocked */
        ReturnCode = STATUS_C40_IP_SUCCESS;
    }
    else
    {
        /* Check the lock Domain Id */
        ReturnCode = C40_Ip_CheckLockDomainID(VirtualSector, DomainIdValue);
        if (STATUS_C40_IP_SUCCESS == ReturnCode)
        {
            #if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
            OsIf_Trusted_Call1param(C40_Ip_ClearLockProtect, VirtualSector);
            #else
            C40_Ip_ClearLockProtect(VirtualSector);
            #endif
        }
    }

    return ReturnCode;
}

/**
 * Function Name    C40_Ip_ClearLockProtect
 * Description      Unlocks the selected sector for the requesting core if possible
 */
void C40_Ip_ClearLockProtect(C40_Ip_VirtualSectorsType VirtualSector)
{
    uint32 SectorIndex;
    uint32 BlockCount;
    uint32 SectorPosition;

    /* All checks passed - set lock bit */
    if ((uint32)VirtualSector < FLS_MAX_DATA_SECTOR)
    {
        /* Sector is in the Data Block _ Block 4 for K3x4, _ Block 2 for K3x2 */
        C40_Ip_pPFlashBaseAddress->PFCBLK_SPELOCK[FLS_DATA_PFCBLK_ORDER] &= ~C40_Ip_u32BitPosition;
    }
    else if (FLS_MAX_VIRTUAL_SECTOR == (uint32)VirtualSector)
    {
        /* Sector is in Utest */
        C40_Ip_pPFlashBaseAddress->PFCBLKU_SPELOCK[0] &= ~C40_Ip_u32BitPosition;
    }
    else
    {
        SectorIndex    = (uint32)VirtualSector - FLS_MAX_DATA_SECTOR;
        /* divide by 128: each block 1MB has 128 sectors */
        /* divide by 256: each block 2MB has 256 sectors */
        BlockCount     = SectorIndex / FLS_NO_OF_SECTOR_PER_BLOCK;
        SectorPosition = SectorIndex & (FLS_NO_OF_SECTOR_PER_BLOCK - 1U);  /* the position sectors 8KB per block */

        /* For 1 MB blocks, the first 768KB (96 sectors 8KB) is protected with super sector granularity */
        /* For 2 MB blocks, the first 1972KB (224 sectors 8KB) is protected with super sector granularity */
        if (SectorPosition < (FLS_NO_OF_SUPPER_SECTOR_PER_BLOCK * 8U))
        {
            /* Sector is in the Super Sector zone */
            C40_Ip_pPFlashBaseAddress->PFCBLK_SSPELOCK[BlockCount] &= ~C40_Ip_u32BitPosition;
        }
        else
        {
            /* Sector is in the 8KB Sector zone */
            C40_Ip_pPFlashBaseAddress->PFCBLK_SPELOCK[BlockCount] &= ~C40_Ip_u32BitPosition;
        }
    }
}


/**
 * Function Name    C40_Ip_Compare
 * Description      Checks that there is the desired data at the specified address
 *
 * @implements      C40_Ip_Compare_Activity
 */
C40_Ip_StatusType C40_Ip_Compare(uint32 LogicalAddress,
                                 uint32 Length,
                                 const uint8 *SourceAddressPtr
                                )
{
    C40_IP_DEV_ASSERT(Length > 0UL);
    C40_IP_DEV_ASSERT( C40_Ip_ValidRangeAddress(LogicalAddress, Length) );

    /* Check the input parameter */
    if (0U == Length)
    {
        /* Wrong input parameter */
        C40_Ip_eReadStatus = STATUS_C40_IP_ERROR_INPUT_PARAM;
    }
    else
    {
        /* Change to busy state */
        C40_Ip_eReadStatus = STATUS_C40_IP_BUSY;

        /* Invalidate cache */
        #if (STD_ON == C40_IP_SYNCRONIZE_CACHE)
        C40_Ip_SynchronizeCache(LogicalAddress, Length);
        #endif

        /* Choose the type of comparison */
        if (NULL_PTR != SourceAddressPtr)
        {
            /* Verify the written data */
            C40_Ip_ProgramVerify(LogicalAddress, SourceAddressPtr, Length);
        }
        else
        {
            /* Blank check */
            C40_Ip_EraseVerify(LogicalAddress, Length);
        }
    }

    return C40_Ip_eReadStatus;
}

/**
 * @brief   Verifies data written in memory flash
 */
static uint32 C40_Ip_CompareData(uint32 ReadAddress,
                                 uint32 DataAddress,
                                 uint32 SizeLeft,
                                 boolean *CompareResult
                                )
{
    uint32 ReadSize;

    /* Combine two addresses for faster alignment checking */
    uint32 CombinedAddress = ReadAddress | DataAddress;

    /* Both the lowest two bits are zero: 4 bytes aligned */
    if ( (0UL == (CombinedAddress & 0x03UL)) && (SizeLeft >= FLS_SIZE_4BYTE) )
    {
        /* 4 bytes operation */
        ReadSize = FLS_SIZE_4BYTE;
        *CompareResult = ( C40_Ip_ReadData32(ReadAddress) == C40_Ip_ReadData32(DataAddress) );
    }
    /* Both the lowest one bit are zero: 2 bytes aligned */
    else if ( (0UL == (CombinedAddress & 0x01UL)) && (SizeLeft >= FLS_SIZE_2BYTE) )
    {
        /* 2 bytes operation */
        ReadSize = FLS_SIZE_2BYTE;
        *CompareResult = ( C40_Ip_ReadData16(ReadAddress) == C40_Ip_ReadData16(DataAddress) );
    }
    else
    {
        /* 1 byte operation */
        ReadSize = FLS_SIZE_1BYTE;
        *CompareResult = ( C40_Ip_ReadData8(ReadAddress) == C40_Ip_ReadData8(DataAddress) );
    }

    return ReadSize;
}


/**
 * @brief   Verifies data written in memory flash
 */
static void C40_Ip_ProgramVerify(uint32 Address,
                                 const uint8 *Data,
                                 uint32 Size
                                )
{
    uint32 ReadAddress = Address;
    uint32 DataAddress = (uint32)Data;
    uint32 SizeLeft = Size;
    uint32 ReadSize;
    C40_Ip_StatusType Status;
    boolean CompareResult;

    /* Start compare operation */
    do
    {
        /* Prepare before access to the flash memory */
        Status = C40_Ip_ClearPreviousRead(ReadAddress);

        if (STATUS_C40_IP_SUCCESS == Status)
        {
            /* Start flash access */
            C40_Ip_FlashAccessCalloutStart();

            /* Access the flash to compare data */
            ReadSize = C40_Ip_CompareData(ReadAddress, DataAddress, SizeLeft, &CompareResult);

            /* Finish flash access */
            C40_Ip_FlashAccessCalloutFinish();

            /* Check for hardware errors or ECC happend or compare error */
            Status = C40_Ip_CheckReadCompareStatus(ReadAddress, CompareResult);
        }

        if (STATUS_C40_IP_SUCCESS != Status)
        {
            break;
        }

        /* Move to next data */
        ReadAddress += ReadSize;
        DataAddress += ReadSize;
        SizeLeft    -= ReadSize;
    }
    while (0UL < SizeLeft);

    /* Checking if working is successful: the requested bytes were compared and no errors happend */
    if (0UL == SizeLeft)
    {
        /* Mark as success */
        C40_Ip_eReadStatus = STATUS_C40_IP_SUCCESS;
    }
}


/**
 * @brief   Verifies that an area in memory flash is in erased state
 */
static uint32 C40_Ip_CompareBlank(uint32 ReadAddress,
                                  uint32 SizeLeft,
                                  boolean *CompareResult
                                 )
{
    uint32 ReadSize;

    /* The lowest two bits are zero: 4 bytes aligned */
    if ( (0UL == (ReadAddress & 0x03UL)) && (SizeLeft >= FLS_SIZE_4BYTE) )
    {
        /* 4 bytes operation */
        ReadSize = FLS_SIZE_4BYTE;
        *CompareResult = ( C40_ERASED_VALUE_32 == C40_Ip_ReadData32(ReadAddress) );
    }
    /* The lowest one bit are zero: 2 bytes aligned */
    else if ( (0UL == (ReadAddress & 0x01UL)) && (SizeLeft >= FLS_SIZE_2BYTE) )
    {
        /* 2 bytes operation */
        ReadSize = FLS_SIZE_2BYTE;
        *CompareResult = ( C40_ERASED_VALUE_16 == C40_Ip_ReadData16(ReadAddress) );
    }
    else
    {
        /* 1 byte operation */
        ReadSize = FLS_SIZE_1BYTE;
        *CompareResult = ( C40_ERASED_VALUE_8 == C40_Ip_ReadData8(ReadAddress) );
    }

    return ReadSize;
}


/**
 * @brief   Verifies that an area in memory flash is in erased state
 */
static void C40_Ip_EraseVerify(uint32 Address,
                               uint32 Size
                              )
{
    uint32 ReadAddress = Address;
    uint32 SizeLeft = Size;
    uint32 ReadSize;
    C40_Ip_StatusType Status;
    boolean CompareResult;

    /* Start compare operation */
    do
    {
        /* Prepare before access to the flash memory */
        Status = C40_Ip_ClearPreviousRead(ReadAddress);

        if (STATUS_C40_IP_SUCCESS == Status)
        {
            /* Start flash access */
            C40_Ip_FlashAccessCalloutStart();

            /* Access the flash to compare data */
            ReadSize = C40_Ip_CompareBlank(ReadAddress, SizeLeft, &CompareResult);

            /* Finish flash access */
            C40_Ip_FlashAccessCalloutFinish();

            /* Check for hardware errors or ECC happend or compare error */
            Status = C40_Ip_CheckReadCompareStatus(ReadAddress, CompareResult);
        }

        if (STATUS_C40_IP_SUCCESS != Status)
        {
            break;
        }

        /* Move to next data */
        ReadAddress += ReadSize;
        SizeLeft    -= ReadSize;
    }
    while (0UL < SizeLeft);

    /* Checking if working is successful: the requested bytes were compared and no errors happend */
    if (0UL == SizeLeft)
    {
        /* Mark as success */
        C40_Ip_eReadStatus = STATUS_C40_IP_SUCCESS;
    }
}


#if (STD_ON == C40_MAIN_INTERFACE_ENABLED)
/**
 * Function Name : C40_Ip_MainInterfaceWriteLogicalAddress
 * Description   : Write the program erase address using logical address registers located in the Platform Flash Controller
 */
void C40_Ip_MainInterfaceWriteLogicalAddress(uint32 Address)
{
    /* Write the program/erase address */
    C40_Ip_pPFlashBaseAddress->PFCPGM_PEADR_L = Address;
}


/**
 * Function Name    C40_Ip_MainInterfaceWriteJobAddress
 * Description      Write the address in the PEADR register
 */
static C40_Ip_StatusType C40_Ip_MainInterfaceWriteJobAddress(uint32 PhysicalAddress,
                                                             uint8 DomainIdValue
                                                            )
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;
    uint8 ActualDomainIDs;

    /* Write the address in the PEADR register */
    do
    {
        #if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
        OsIf_Trusted_Call1param(C40_Ip_MainInterfaceWriteLogicalAddress, PhysicalAddress);
        #else
        C40_Ip_MainInterfaceWriteLogicalAddress(PhysicalAddress);
        #endif

        ActualDomainIDs = (uint8)((C40_Ip_pFlashBaseAddress->MCR & FLASH_MCR_PEID_MASK) >> FLASH_MCR_PEID_SHIFT);

        #if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
        C40_Ip_u32ElapsedTicks += OsIf_GetElapsed(&C40_Ip_u32CurrentTicks, (OsIf_CounterType)C40_TIMEOUT_TYPE);
        if (C40_Ip_u32ElapsedTicks >= C40_Ip_u32TimeoutTicks)
        {
            /* Errors Timeout because wait for the Done bit long time*/
            ReturnCode = STATUS_C40_IP_ERROR_TIMEOUT;
            break;
        }
        #endif
    }
    while (ActualDomainIDs != DomainIdValue);

    return ReturnCode;
}


/**
 * Function Name    C40_Ip_InitMainInterface
 * Description      Initializes the C40 module with main interface
 */
static C40_Ip_StatusType C40_Ip_InitMainInterface(void)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_ERROR;

    ReturnCode = C40_Ip_MainInterfaceAbort();

    /* Disable watchdog interrupt */
    C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_WDIE_MASK;
    /* No interrupt request will be generated when the DONE flag is set*/
    C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_PECIE_MASK;

    C40_Ip_ClearAllErrorFlagsMainInterface();

    return ReturnCode;
}

/**
 * Function Name    C40_Ip_MainInterfaceAbort
 * Description      Abort a program or erase operation with main interface
 */
static C40_Ip_StatusType C40_Ip_MainInterfaceAbort(void)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;

#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
    /* Prepare timeout counter */
    C40_Ip_u32ElapsedTicks = 0UL;
    C40_Ip_u32TimeoutTicks = OsIf_MicrosToTicks(C40_ABORT_TIMEOUT, (OsIf_CounterType)C40_TIMEOUT_TYPE);
    C40_Ip_u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)C40_TIMEOUT_TYPE);
#endif

    /* Disable HV to finalize/abort the operation */
    C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_EHV_MASK;
    MCAL_FAULT_INJECTION_POINT(C40_IP_FMEA_MAIN_INTERFACE_ABORT_INJECT_ERROR);
    while (0U == (C40_Ip_pFlashBaseAddress->MCRS & FLASH_MCRS_DONE_MASK))
    {
#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
        C40_Ip_u32ElapsedTicks += OsIf_GetElapsed(&C40_Ip_u32CurrentTicks, (OsIf_CounterType)C40_TIMEOUT_TYPE);
        if (C40_Ip_u32ElapsedTicks >= C40_Ip_u32TimeoutTicks)
        {
            /* Errors Timeout because wait for the Done bit long time*/
            ReturnCode = STATUS_C40_IP_ERROR_TIMEOUT;
            break;
        }
#endif
    }
    /* Clear ERS and PGM bits */
    C40_Ip_pFlashBaseAddress->MCR &= ~(FLASH_MCR_PGM_MASK|FLASH_MCR_ESS_MASK|FLASH_MCR_ERS_MASK);

    return ReturnCode;
}

/**
 * Function Name    C40_Ip_ClearAllErrorFlagsMainInterface
 * Description      Clear all error flags with main interface
 */
static inline void C40_Ip_ClearAllErrorFlagsMainInterface(void)
{
    /** Clear all error flags for main interface */
    C40_Ip_pFlashBaseAddress->MCRS &= FLASH_MCRS_EER_MASK |  \
                               FLASH_MCRS_SBC_MASK |  \
                               FLASH_MCRS_AEE_MASK |  \
                               FLASH_MCRS_EEE_MASK |  \
                               FLASH_MCRS_RVE_MASK |  \
                               FLASH_MCRS_RRE_MASK |  \
                               FLASH_MCRS_RWE_MASK |  \
                               FLASH_MCRS_PES_MASK |  \
                               FLASH_MCRS_PEP_MASK;
}


/**
 * Function Name    C40_Ip_MainInterfaceSectorErasePreCheck
 * Description      Verify the parameters, EHV, UTest and the selected sector are ready to perform the erase job
 */
static inline C40_Ip_StatusType C40_Ip_MainInterfaceSectorErasePreCheck(C40_Ip_VirtualSectorsType VirtualSector)
{
    C40_Ip_StatusType ReturnCode;

    /* Check length and u32offet should align with C40_SECTOR_SIZE */
    if (VirtualSector > C40_UTEST_ARRAY_0_S000)
    {
        /* Wrong input parameters*/
        ReturnCode = STATUS_C40_IP_ERROR_INPUT_PARAM;
    }
    /* Verify that there is no other job in progress */
    else if (0UL != (C40_Ip_pFlashBaseAddress->MCR & (FLASH_MCR_ERS_MASK | FLASH_MCR_PGM_MASK)))
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    /* Verify that UTest is not enabled */
    else if (0UL != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_UTE_MASK))
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    /* Check the lock bit */
    else if (STATUS_C40_IP_SECTOR_UNPROTECTED != C40_Ip_GetLock(VirtualSector))
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    else
    {
        /* Reaching here means that everything is ok */
        ReturnCode = STATUS_C40_IP_SUCCESS;
    }

    return ReturnCode;
}


/**
 * Function Name    C40_Ip_MainInterfaceSectorErase
 * Description      Accepts an erase job over one of the sectors through the main interface if possible
 *
 * @implements      C40_Ip_MainInterfaceSectorErase_Activity
 */
C40_Ip_StatusType C40_Ip_MainInterfaceSectorErase(C40_Ip_VirtualSectorsType VirtualSector,
                                                  uint8 DomainIdValue
                                                 )
{
    C40_Ip_StatusType ReturnCode;
    uint32 LogicalAddress;

    C40_IP_DEV_ASSERT((uint32)VirtualSector <= FLS_MAX_VIRTUAL_SECTOR);

#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
    /* Prepare timeout counter */
    C40_Ip_u32ElapsedTicks = 0UL;
    C40_Ip_u32TimeoutTicks = OsIf_MicrosToTicks(((boolean)FALSE == C40_Ip_bAsync)?C40_SYNC_ERASE_TIMEOUT:C40_ASYNC_ERASE_TIMEOUT, (OsIf_CounterType)C40_TIMEOUT_TYPE);
    C40_Ip_u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)C40_TIMEOUT_TYPE);
#endif

    /* Checking before start a new erase operation */
    ReturnCode = C40_Ip_MainInterfaceSectorErasePreCheck(VirtualSector);

    if (STATUS_C40_IP_SUCCESS == ReturnCode)
    {
        /* Fault Injection point: lock sector to test MSCR_PEP bit */
        MCAL_FAULT_INJECTION_POINT(FLS_FIP_LOCK_INTSECTOR_C40SECTORERASE);

        /* Clear all the error flags */
        C40_Ip_ClearAllErrorFlagsMainInterface();

        /* Address of the sector to be erased */
        LogicalAddress = C40_Ip_GetBaseAddressOfSector(VirtualSector);

        #if ((C40_ERASE_VERIFICATION_ENABLED == STD_ON) || (STD_ON == C40_IP_SYNCRONIZE_CACHE))
        /* Prepare address for the blank check */
        C40_Ip_u32ErasedSectorAddress = LogicalAddress;
        #endif

        /* Write the address to be erased */
        ReturnCode = C40_Ip_MainInterfaceWriteJobAddress(LogicalAddress, DomainIdValue);
        if (STATUS_C40_IP_ERROR_TIMEOUT == ReturnCode)
        {
            /* In case of timeout, create a dummy write to clear the PEADR register */
            C40_Ip_ClearInterlockWrite();
        }
    }

    if (STATUS_C40_IP_SUCCESS == ReturnCode)
    {
        /* One and only one ADATA register must also be written. This is referred to as an erase interlock write.*/
        C40_Ip_pFlashBaseAddress->DATA[0] = 0xFFFFFFFFU;
        /* Setup erase operation */
        C40_Ip_pFlashBaseAddress->MCR |= FLASH_MCR_ERS_MASK;
        /* Flash memory erase will be on a sector */
        C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_ESS_MASK;
        /* if Async is true */
        if (TRUE == C40_Ip_bAsync)
        {
            /* Start flash access */
            C40_Ip_FlashAccessCalloutStart();
            /* start internal erase/program sequence */
            C40_Ip_pFlashBaseAddress->MCR |= FLASH_MCR_EHV_MASK;
        }
    }

    return ReturnCode;
}

/**
 * Function Name    C40_Ip_MainInterfaceSectorEraseStatus
 * Description      Checks the status of the hardware erase started by the C40_Ip_MainInterfaceSectorErase function.
 *
 * @implements      C40_Ip_MainInterfaceSectorEraseStatus_Activity
 */
C40_Ip_StatusType C40_Ip_MainInterfaceSectorEraseStatus(void)
{
    C40_Ip_StatusType ReturnCode;

    ReturnCode = C40_Ip_MainInterfaceHVJobStatus();

    if (STATUS_C40_IP_BUSY != ReturnCode)
    {
        /* terminate erase operation */
        C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_EHV_MASK;
        /* Terminate erase operation */
        C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_ERS_MASK;

#if ( C40_ERASE_VERIFICATION_ENABLED == STD_ON )
        /* Verify blank check after erasing the data */
        if (STATUS_C40_IP_SUCCESS == ReturnCode)
        {
            /* Fault Injection point: write data to erased sector to make the Compare failed */
            MCAL_FAULT_INJECTION_POINT(FLS_FIP_C40_FAILED_VERIFICATION_ERASE);

            ReturnCode = C40_Ip_Compare(C40_Ip_u32ErasedSectorAddress, C40_SECTOR_SIZE, NULL_PTR);
            if (STATUS_C40_IP_SUCCESS != ReturnCode)
            {
                ReturnCode = STATUS_C40_IP_ERROR_BLANK_CHECK;
            }
        }
#else
    #if (C40_IP_SYNCRONIZE_CACHE == STD_ON)
        /* Invalidate cache */
        C40_Ip_SynchronizeCache(C40_Ip_u32ErasedSectorAddress, C40_SECTOR_SIZE);
    #endif
#endif
    }
    return ReturnCode;
}


/**
 * Function Name    C40_Ip_MainInterfaceWritePreCheck
 * Description      Verify the parameters, EHV, UTest and the selected sector are ready to perform the write job
 */
static inline C40_Ip_StatusType C40_Ip_MainInterfaceWritePreCheck(uint32 LogicalAddress,
                                                                  uint32 Length,
                                                                  const uint8 *SourceAddressPtr
                                                                 )
{
    C40_Ip_StatusType ReturnCode;
    C40_Ip_VirtualSectorsType VirtualSector;
    uint32 Offset;

    C40_IP_DEV_ASSERT( C40_Ip_ValidRangeAddress(LogicalAddress, Length) );

    /* Get sector number */
    VirtualSector = C40_Ip_GetSectorNumberFromAddress(LogicalAddress);

    /* Byte offset of a quad-page */
    Offset = LogicalAddress & (C40_DATA_SIZE_BYTES_U32 - 1U);

    /* Validates input parameters */
    if ( ((LogicalAddress & (C40_WRITE_DOUBLE_WORD - 1U)) != 0U ) ||    /* Must be aligned with 8-byte     */
         ((Length         & (C40_WRITE_DOUBLE_WORD - 1U)) != 0U ) ||    /* Must be aligned with 8-byte     */
         ((Length + Offset) > C40_DATA_SIZE_BYTES_U32)            ||    /* Must fall within a quad-page    */
         (0U == Length)                                           ||    /* Must not be zero                */
         (NULL_PTR == SourceAddressPtr)                                 /* Must not be NULL_PRT            */
       )
    {
        /* Wrong input parameters*/
        ReturnCode = STATUS_C40_IP_ERROR_INPUT_PARAM;
    }
    /* Verify that EHV may be set */
    else if (0UL != (C40_Ip_pFlashBaseAddress->MCR & (FLASH_MCR_ERS_MASK | FLASH_MCR_PGM_MASK)))
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    /* Verify that UTest is not enabled */
    else if (0UL != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_UTE_MASK))
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    /* Check lock bit of the first sector */
    else if (STATUS_C40_IP_SECTOR_UNPROTECTED != C40_Ip_GetLock(VirtualSector))
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    else
    {
        /* Reaching here means that everything is ok */
        ReturnCode = STATUS_C40_IP_SUCCESS;
    }

    return ReturnCode;
}


/**
 * Function Name    C40_Ip_MainInterfaceFillProgramBuffer
 * Description      Writes data into the memory array using the main interface
 */
static void C40_Ip_MainInterfaceFillDataBuff(uint32 LocationWriteDataRegs,
                                             const uint8 *DataPtr,
                                             uint32 Size
                                            )
{
    const uint32 *DataPtr32 = (const uint32 *)((uint32)DataPtr);
    const uint8  *DataPtr8  = DataPtr;
    uint32 DataIndex = LocationWriteDataRegs;
    uint32 SizeLeft = Size;
    volatile uint32 DataTemp32;  /* Prevent compiler optimization when working with unaligned addresses */

    /* Check user buffer alignment */
    if (((uint32)DataPtr & 0x3U) == 0U)
    {
        /* Process double-word at a time to speed things up */
        do
        {
            C40_Ip_pFlashBaseAddress->DATA[DataIndex + 0U] = DataPtr32[0U];
            C40_Ip_pFlashBaseAddress->DATA[DataIndex + 1U] = DataPtr32[1U];

            /* Move to the next double-word */
            DataPtr32  = &(DataPtr32[2U]);
            DataIndex += 2U;
            SizeLeft  -= 8U;
        }
        while (SizeLeft > 0U);
    }
    else
    {
        /* Process each byte one by one */
        do
        {
            DataTemp32  = (uint32)DataPtr8[0U] <<  0U;
            DataTemp32 |= (uint32)DataPtr8[1U] <<  8U;
            DataTemp32 |= (uint32)DataPtr8[2U] << 16U;
            DataTemp32 |= (uint32)DataPtr8[3U] << 24U;
            C40_Ip_pFlashBaseAddress->DATA[DataIndex + 0U] = DataTemp32;

            DataTemp32  = (uint32)DataPtr8[4U] <<  0U;
            DataTemp32 |= (uint32)DataPtr8[5U] <<  8U;
            DataTemp32 |= (uint32)DataPtr8[6U] << 16U;
            DataTemp32 |= (uint32)DataPtr8[7U] << 24U;
            C40_Ip_pFlashBaseAddress->DATA[DataIndex + 1U] = DataTemp32;

            /* Move to the next double-word */
            DataPtr8   = &(DataPtr8[8U]);
            DataIndex += 2U;
            SizeLeft  -= 8U;
        }
        while (SizeLeft > 0U);
    }
}


/**
 * Function Name    C40_Ip_ClearInterlockWrite
 * Description      Clear the interlock write by using a dummy write operation
 *                  to ensure no operations are in progress
 */
static void C40_Ip_ClearInterlockWrite(void)
{
    /* Write a dummy data */
    C40_Ip_pFlashBaseAddress->DATA[0] = 0x00U;
    /* Setup for a program operation to create the interlock write */
    C40_Ip_pFlashBaseAddress->MCR |= FLASH_MCR_PGM_MASK;

#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
    /* Prepare timeout counter */
    uint32 ElapsedTicks = 0UL;
    uint32 TimeoutTicks = OsIf_MicrosToTicks(C40_ABORT_TIMEOUT, (OsIf_CounterType)C40_TIMEOUT_TYPE);
    uint32 CurrentTicks = OsIf_GetCounter((OsIf_CounterType)C40_TIMEOUT_TYPE);
#endif

    /* Wait until interlock write finishes */
    while (0U == (C40_Ip_pFlashBaseAddress->MCR & FLASH_MCR_PGM_MASK))
    {
#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
        ElapsedTicks += OsIf_GetElapsed(&CurrentTicks, (OsIf_CounterType)C40_TIMEOUT_TYPE);
        if (ElapsedTicks >= TimeoutTicks)
        {
            break;
        }
#endif
    }

    /* Abort the program operation */
    C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_PGM_MASK;
}


/**
 * Function Name    C40_Ip_MainInterfaceWrite
 * Description      Writes data into the memory array using the main interface. Initiates the hardware write and then exits.
 *
 * @implements      C40_Ip_MainInterfaceWrite_Activity
 */
C40_Ip_StatusType C40_Ip_MainInterfaceWrite(uint32 LogicalAddress,
                                            uint32 Length,
                                            const uint8 *SourceAddressPtr,
                                            uint8 DomainIdValue
                                           )
{
    C40_Ip_StatusType ReturnCode;
    uint32 LocationWriteDataRegs;

    /* Store address to check failed operation */
    C40_Ip_u32LogicalAddressCheckFail = LogicalAddress % C40_DATA_SIZE_BYTES_U32;
    C40_Ip_eOpStatus = C40_IP_PGM_WRITE;

#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
    /* Prepare timeout counter */
    C40_Ip_u32ElapsedTicks = 0UL;
    C40_Ip_u32TimeoutTicks = OsIf_MicrosToTicks(((boolean)FALSE == C40_Ip_bAsync)?C40_SYNC_WRITE_TIMEOUT:C40_ASYNC_WRITE_TIMEOUT, (OsIf_CounterType)C40_TIMEOUT_TYPE);
    C40_Ip_u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)C40_TIMEOUT_TYPE);
#endif

    /* Checking before a new write operation */
    ReturnCode = C40_Ip_MainInterfaceWritePreCheck(LogicalAddress, Length, SourceAddressPtr);

#if ( C40_ERASE_VERIFICATION_ENABLED == STD_ON )
    if (STATUS_C40_IP_SUCCESS == ReturnCode)
    {
        /* Verify blank check before writing the data */
        ReturnCode = C40_Ip_Compare(LogicalAddress, Length, NULL_PTR);
        if (STATUS_C40_IP_SUCCESS != ReturnCode)
        {
            ReturnCode = STATUS_C40_IP_ERROR_BLANK_CHECK;
        }
    }
#endif

    if (STATUS_C40_IP_SUCCESS == ReturnCode)
    {
        /* Clear all the error flags */
        C40_Ip_ClearAllErrorFlagsMainInterface();
        /* Write the address to be programmed */
        ReturnCode = C40_Ip_MainInterfaceWriteJobAddress(LogicalAddress, DomainIdValue);
        if (STATUS_C40_IP_ERROR_TIMEOUT == ReturnCode)
        {
            /* In case of timeout, create a dummy write to clear the PEADR register */
            C40_Ip_ClearInterlockWrite();
        }
    }

    if (STATUS_C40_IP_SUCCESS == ReturnCode)
    {
        #if ((STD_ON == C40_PROGRAM_VERIFICATION_ENABLED) || (STD_ON == C40_IP_SYNCRONIZE_CACHE))
        C40_Ip_u32ProgrammedAddress = LogicalAddress;
        C40_Ip_u32ProgrammedLength = Length;
        #endif

        #if (STD_ON == C40_PROGRAM_VERIFICATION_ENABLED)
        C40_Ip_pProgrammedData = SourceAddressPtr;
        #endif

        /* The numerical order of Sector Offset Address based on (calculated by) PageSize in a block of write buffer size (128 bytes in case of main interface) */
        /*
        * Actual start location needs to be written to DATA registers (DATA[0], DATA[1] ..)
        * Ex: if LogicalAddress = 0 it means that data (of LogicalAddress 0->3) will be written starting from the DATA[0] register (save 4 byte data).
        *     if LogicalAddress = 4 it means that data (of LogicalAddress 4->7) will be written starting from the DATA[1] register (save 4 byte data).
        */
        /* Get the number of the starting registers pair. */
        LocationWriteDataRegs = (LogicalAddress & (C40_DATA_SIZE_BYTES_U32 - 1U)) >> 2U;

        /* Fill the data into hardware buffer */
        C40_Ip_MainInterfaceFillDataBuff(LocationWriteDataRegs, SourceAddressPtr, Length);

        /* Fault Injection point: make sequence error to test MSCR_PES bit */
        MCAL_FAULT_INJECTION_POINT(FLS_FIP_C40_MAIN_INTF_WRITE);

        /* Setup program operation */
        C40_Ip_pFlashBaseAddress->MCR |= FLASH_MCR_PGM_MASK;
        /* If Async is true */
        if (TRUE == C40_Ip_bAsync)
        {
            /* Start flash access */
            C40_Ip_FlashAccessCalloutStart();
            /* Start internal erase/program sequence */
            C40_Ip_pFlashBaseAddress->MCR |= FLASH_MCR_EHV_MASK;
        }
    }

    return ReturnCode;
}

/**
 * Function Name    C40_Ip_MainInterfaceWriteStatus
 * Description      Checks the status of the hardware program started by the C40_IP_MainInterfaceWrite function.
 *
 * @implements      C40_Ip_MainInterfaceWriteStatus_Activity
 */
C40_Ip_StatusType C40_Ip_MainInterfaceWriteStatus(void)
{
    C40_Ip_StatusType ReturnCode;

    ReturnCode = C40_Ip_MainInterfaceHVJobStatus();

    if (STATUS_C40_IP_BUSY != ReturnCode)
    {
        /* Terminate write operation */
        C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_EHV_MASK;
        /* Terminate write operation */
        C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_PGM_MASK;

#if ( C40_PROGRAM_VERIFICATION_ENABLED == STD_ON )
        /* Verify written data */
        if (STATUS_C40_IP_SUCCESS == ReturnCode)
        {
            /* Fault Injection point: write data to programmed sector to make the Compare failed */
            MCAL_FAULT_INJECTION_POINT(FLS_FIP_C40_FAILED_VERIFICATION_WRITE);

            ReturnCode = C40_Ip_Compare(C40_Ip_u32ProgrammedAddress, C40_Ip_u32ProgrammedLength, C40_Ip_pProgrammedData);
            if (STATUS_C40_IP_SUCCESS != ReturnCode)
            {
                ReturnCode = STATUS_C40_IP_ERROR_PROGRAM_VERIFY;
            }
        }
#else
        #if ( STD_ON == C40_IP_SYNCRONIZE_CACHE )
        /* Invalidate cache */
        C40_Ip_SynchronizeCache(C40_Ip_u32ProgrammedAddress, C40_Ip_u32ProgrammedLength);
        #endif
#endif
    }
    return ReturnCode;
}

/**
 * Function Name    C40_Ip_MainInterfaceHVJobStatus
 * Description      Get the status of job with main interface.
 */
static C40_Ip_StatusType C40_Ip_MainInterfaceHVJobStatus(void)
{
    C40_Ip_StatusType ReturnCode;
    uint32 ErrorFlags;

    if (0U == (C40_Ip_pFlashBaseAddress->MCRS & FLASH_MCRS_DONE_MASK))
    {
        ReturnCode = STATUS_C40_IP_BUSY;
#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
        C40_Ip_u32ElapsedTicks += OsIf_GetElapsed(&C40_Ip_u32CurrentTicks, (OsIf_CounterType)C40_TIMEOUT_TYPE);
        if (C40_Ip_u32ElapsedTicks >= C40_Ip_u32TimeoutTicks)
        {
            /* Errors Timeout because wait for the Done bit long time*/
            ReturnCode = STATUS_C40_IP_ERROR_TIMEOUT;
        }
#endif
    }
    else
    {
        ErrorFlags = C40_Ip_pFlashBaseAddress->MCRS & (FLASH_MCRS_PEG_MASK | FLASH_MCRS_PEP_MASK | FLASH_MCRS_PES_MASK);
        /* Program/Erase Good: only PEG = 1; both PEP and PES should be 0 */
        if (FLASH_MCRS_PEG_MASK == ErrorFlags)
        {
            ReturnCode = STATUS_C40_IP_SUCCESS;
        }
        else
        {
            ReturnCode = STATUS_C40_IP_ERROR;
        }
    }

    return ReturnCode;
}
#endif /* (STD_ON == C40_MAIN_INTERFACE_ENABLED) */


/**
 * Function Name    C40_Ip_GetSectorID
 * Description      Get sector ID base on Fls_VirtualSector
 */
static uint32 C40_Ip_GetSectorID(C40_Ip_VirtualSectorsType VirtualSector)
{
    uint32 SectorIndex;
    uint32 SectorPosition;


    if ((uint32)VirtualSector < FLS_MAX_DATA_SECTOR)
    {
        /* Sector is in the Data Block */
        C40_Ip_u32SectorId = (uint32)VirtualSector;
    }
    else if (FLS_MAX_VIRTUAL_SECTOR == (uint32)VirtualSector)
    {
        /* Sector is in Utest */
        C40_Ip_u32SectorId = (uint32)VirtualSector - FLS_MAX_VIRTUAL_SECTOR;
    }
    else
    {
        SectorIndex    = (uint32)VirtualSector - FLS_MAX_DATA_SECTOR;
        /* the position in a total of 128 sectors 8KB per 1MB block */
        /*                            256 sectors 8KB per 2MB block */
        SectorPosition = SectorIndex & (FLS_NO_OF_SECTOR_PER_BLOCK - 1U);

        /* For 1 MB blocks, the first 768KB (96 sectors 8KB) is protected with super sector granularity */
        /* For 2 MB blocks, the first 1972KB (224 sectors 8KB) is protected with super sector granularity */
        if (SectorPosition < (FLS_NO_OF_SUPPER_SECTOR_PER_BLOCK * 8U))
        {
            /* Sector is in the Super Sector zone: 1 Super Sector 64KB = 8 sectors 8KB */
            C40_Ip_u32SectorId = SectorPosition >> 3U;  /* divide by 8 */
        }
        else
        {
            /* Sector is in the 8KB Sector zone */
            C40_Ip_u32SectorId = SectorPosition - (FLS_NO_OF_SUPPER_SECTOR_PER_BLOCK * 8U);
        }
    }

    return C40_Ip_u32SectorId;
}

/**
 * Function Name    C40_Ip_CheckLockDomainID
 * Description      Check Domain ID base on Fls_VirtualSector
 */
static C40_Ip_StatusType C40_Ip_CheckLockDomainID(C40_Ip_VirtualSectorsType VirtualSector,
                                                  uint8 DomainIdValue
                                                 )
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;
    uint8 LockDomainIDValue = 0U;
    uint32 TempLockMasterRegister = 0U;
    uint32 ShiftValue = 0U;
    uint32 CheckRegister = 0U;

    if ((uint32)VirtualSector != FLS_MAX_VIRTUAL_SECTOR)
    {
        ShiftValue = (C40_Ip_u32SectorId - ((C40_Ip_u32SectorId/4U)*4U))*8U;
    }

    if ((uint32)VirtualSector <= FLS_MAX_VIRTUAL_SECTOR)
    {
#if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
        OsIf_Trusted_Call3params(C40_Ip_CheckLockDomainID_CheckRegister, VirtualSector, &CheckRegister, &TempLockMasterRegister);
#else
        C40_Ip_CheckLockDomainID_CheckRegister(VirtualSector, &CheckRegister, &TempLockMasterRegister);
#endif
    }

    /* Check register's value */
    if ( (0U != (CheckRegister & C40_Ip_u32BitPosition)) && (TempLockMasterRegister != 0U) )
    {
        LockDomainIDValue = (uint8)(((*(volatile uint32*)(TempLockMasterRegister)) >> ShiftValue) & 0xFFU);
        /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
        if (LockDomainIDValue != DomainIdValue)
        {
            /* Any effort to modify(1 to 0, or 0 to1) the lock bit by a master with different domain id will result transfer error.   */
            ReturnCode = STATUS_C40_IP_ERROR;
        }
        else
        {
            /* the lock bits can be modified because it same domain ID */
        }
    }
    else
    {
        /* Lock bits can be modified by any domain IDs if SETSLOCK bites are low */
    }

    return ReturnCode;
}

/**
 * Function Name    C40_Ip_GetBaseAddressOfSector
 * Description      Get baseAddress of sector
 */
static uint32 C40_Ip_GetBaseAddressOfSector(C40_Ip_VirtualSectorsType VirtualSectors)
{
    uint32 BaseAddressofSector;

    if ((uint32)VirtualSectors < FLS_MAX_DATA_SECTOR)
    {
        /* This sector is Data zone: Block 4*/
        BaseAddressofSector = C40_DATA_BASE_ADDRESS + ((uint32)VirtualSectors * C40_SECTOR_SIZE);
    }
    else if ((uint32)VirtualSectors < FLS_MAX_VIRTUAL_SECTOR)
    {
        BaseAddressofSector = C40_CODE_BASE_ADDRESS + (((uint32)VirtualSectors - FLS_MAX_DATA_SECTOR) * C40_SECTOR_SIZE);
    }
    else if (FLS_MAX_VIRTUAL_SECTOR == (uint32)VirtualSectors)
    {
        BaseAddressofSector = C40_UTEST_BASE_ADDRESS;
    }
    else
    {
        /* Configuration errors */
        BaseAddressofSector = FLS_INVALID_ADDR;
    }

    return BaseAddressofSector;
}

void C40_Ip_CheckLockDomainID_CheckRegister(C40_Ip_VirtualSectorsType VirtualSector,
                                            uint32 *CheckRegister,
                                            uint32 *TempLockMasterRegister
                                           )
{
    uint32 SectorIndex;
    uint32 BlockCount;
    uint32 SectorPosition;
    uint32 DomainStep;
    uint32 SectorStep = C40_Ip_u32SectorId & (uint32)(~0x03UL);

    if ((uint32)VirtualSector < FLS_MAX_DATA_SECTOR)
    {
        /* Sector is in the Data Block _ Block 4 for K3x4, _ Block 2 for K3x2 */
        *CheckRegister = C40_Ip_pPFlashBaseAddress->PFCBLK_SETSLOCK[FLS_DATA_PFCBLK_ORDER];
        *TempLockMasterRegister = PFLASH_PFCBLK_DATA_LOCKMASTER_S0_ADDR32 + SectorStep;
    }
    else if (FLS_MAX_VIRTUAL_SECTOR == (uint32)VirtualSector)
    {
        /* Sector is in Utest*/
        *CheckRegister = C40_Ip_pPFlashBaseAddress->PFCBLKU_SETSLOCK[0];
        *TempLockMasterRegister = PFLASH_PFCBLKU_LOCKMASTER_S_ADDR32;
    }
    else
    {
        SectorIndex    = (uint32)VirtualSector - FLS_MAX_DATA_SECTOR;
        /* divide by 128: each block 1MB has 128 sectors */
        /* divide by 256: each block 2MB has 256 sectors */
        BlockCount     = SectorIndex / FLS_NO_OF_SECTOR_PER_BLOCK;
        SectorPosition = SectorIndex & (FLS_NO_OF_SECTOR_PER_BLOCK - 1U);  /* the position sectors 8KB per block */

        /* For 1 MB blocks, the first 768KB (96 sectors 8KB) is protected with super sector granularity */
        /* For 2 MB blocks, the first 1972KB (224 sectors 8KB) is protected with super sector granularity */
        if (SectorPosition < (FLS_NO_OF_SUPPER_SECTOR_PER_BLOCK * 8U))
        {
            /* Sector is in the Super Sector zone */
            *CheckRegister = C40_Ip_pPFlashBaseAddress->PFCBLK_SSETSLOCK[BlockCount];

            DomainStep = BlockCount << 4U;  /* Lock Master Super Sector: the offset is 0x10 (multiply by 16) */
            *TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_SS0_ADDR32 + DomainStep + SectorStep;
        }
        else
        {
            /* Sector is in the 8KB Sector zone */
            *CheckRegister = C40_Ip_pPFlashBaseAddress->PFCBLK_SETSLOCK[BlockCount];

            DomainStep = BlockCount << 5U;  /* Lock Master Sector b: the offset is 0x20 (multiply by 32) */
            *TempLockMasterRegister = PFLASH_PFCBLK0_LOCKMASTER_S0_ADDR32 + DomainStep + SectorStep;
        }
    }
}

/**
 * Function Name    C40_Ip_GetSectorNumberFromAddress
 * Description      Get Sector number of sector from address.
 */
C40_Ip_VirtualSectorsType C40_Ip_GetSectorNumberFromAddress(uint32 TargetAddress)
{
    C40_Ip_VirtualSectorsType VirtualSectors;

    C40_IP_DEV_ASSERT( C40_Ip_ValidAddress(TargetAddress) );

    if      ((TargetAddress >= (uint32)FLS_UTEST_BLOCK_BASE_ADDR)  && (TargetAddress <= (uint32)FLS_UTEST_BLOCK_END_ADDR))
    {
        /* The address is from the Utest sector */
        VirtualSectors = C40_UTEST_ARRAY_0_S000;
    }
    else if ((TargetAddress >= (uint32)FLS_DATA_BLOCK_BASE_ADDR)   && (TargetAddress <= (uint32)FLS_DATA_BLOCK_END_ADDR))
    {
        /* The address is from the data sectors */
        VirtualSectors = (C40_Ip_VirtualSectorsType)(((uint32)TargetAddress - (uint32)FLS_DATA_BLOCK_BASE_ADDR) / C40_SECTOR_SIZE);
    }
    else if ((TargetAddress >= (uint32)FLS_CODE_BLOCK_0_BASE_ADDR) && (TargetAddress <= (uint32)FLS_CODE_BLOCK_END_ADDR))
    {
        /* The address is from the code sectors */
        VirtualSectors = (C40_Ip_VirtualSectorsType)((uint32)FLS_MAX_DATA_SECTOR + (((uint32)TargetAddress - (uint32)FLS_CODE_BLOCK_0_BASE_ADDR) / C40_SECTOR_SIZE));
    }
    else
    {
        /* Out of bounds address */
        VirtualSectors = C40_SECTOR_ERROR;
    }

    return VirtualSectors;
}

/**
 * Function Name    C40_Ip_GetCodeBlockNumber
 * Description      Get code block number from address.
 */
static C40_Ip_FlashBlocksNumberType C40_Ip_GetCodeBlockNumber(uint32 TargetAddress)
{
    C40_Ip_FlashBlocksNumberType BlockNumber = FLS_BLOCK_INVALID;

    if (TargetAddress <= (uint32)FLS_CODE_BLOCK_0_END_ADDR)
    {
        /* The address is in the code block 0 */
        BlockNumber = FLS_CODE_BLOCK_0;
    }
#ifdef FLS_CODE_BLOCK_1_END_ADDR
    else if (TargetAddress <= (uint32)FLS_CODE_BLOCK_1_END_ADDR)
    {
        /* The address is in the code block 1 */
        BlockNumber = FLS_CODE_BLOCK_1;
    }
#endif
#ifdef FLS_CODE_BLOCK_2_END_ADDR
    else if (TargetAddress <= (uint32)FLS_CODE_BLOCK_2_END_ADDR)
    {
        /* The address is in the code block 2 */
        BlockNumber = FLS_CODE_BLOCK_2;
    }
#endif
    else
    {
#ifdef FLS_CODE_BLOCK_3_END_ADDR
        /* The address is in the code block 3 */
        BlockNumber = FLS_CODE_BLOCK_3;
#endif
    }

    return BlockNumber;
}


/**
 * Function Name    C40_Ip_GetBlockNumberFromAddress
 * Description      Get block number from address.
 */
C40_Ip_FlashBlocksNumberType C40_Ip_GetBlockNumberFromAddress(uint32 TargetAddress)
{
    C40_Ip_FlashBlocksNumberType BlockNumber;

    if      ((TargetAddress >= (uint32)FLS_UTEST_BLOCK_BASE_ADDR)  && (TargetAddress <= (uint32)FLS_UTEST_BLOCK_END_ADDR))
    {
        /* The address is in the Utest block */
        BlockNumber = FLS_BLOCK_UTEST;
    }
    else if ((TargetAddress >= (uint32)FLS_DATA_BLOCK_BASE_ADDR)   && (TargetAddress <= (uint32)FLS_DATA_BLOCK_END_ADDR))
    {
        /* The address is in the data block */
        BlockNumber = FLS_DATA_BLOCK;
    }
    else if ((TargetAddress >= (uint32)FLS_CODE_BLOCK_0_BASE_ADDR) && (TargetAddress <= (uint32)FLS_CODE_BLOCK_END_ADDR))
    {
        /* The address is in the code block */
        BlockNumber = C40_Ip_GetCodeBlockNumber(TargetAddress);
    }
    else
    {
        /* Out of bounds address */
        BlockNumber = FLS_BLOCK_INVALID;
    }

    return BlockNumber;
}


/**
 * Function Name    C40_Ip_UTestCheckBusy
 * Description      Check if UTest is busy or not
 */
static C40_Ip_StatusType C40_Ip_UTestCheckBusy(void)
{
    uint32 WaitCounter = FLASH_USER_TEST_WAIT;  /* the loop count for the wait loop */
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;

    if (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AIE_MASK))
    {
        /* In case the previous check is broken, we allow to start a new check */
        if (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_NAIBP_MASK))
        {
            /* Clear all error bits  */
            C40_Ip_pFlashBaseAddress->MCRS &= FLASH_MCRS_EER_MASK|FLASH_MCRS_SBC_MASK|FLASH_MCRS_AEE_MASK|FLASH_MCRS_EEE_MASK|FLASH_MCRS_RVE_MASK|FLASH_MCRS_RRE_MASK|FLASH_MCRS_RWE_MASK;
            /* Clear bits Array Integrity Break Point */
            C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_NAIBP_MASK;
            /* abort to start next operation */
            C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_AIE_MASK;
            /* Wait the UT0_AID bit goes high */
            while ((0x0U == (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)) && (WaitCounter > 0U))
            {
                WaitCounter--;
            }
            /* Clear UT0_AIS, UT0_UTE */
            C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AIS_MASK;
            C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_UTE_MASK;
            if ((0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_NAIBP_MASK)) || (0x0U == (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)))
            {
                /* allow to start a new check was not successfully resumed */
                ReturnCode = STATUS_C40_IP_ERROR;
            }
        }
        else
        {
            ReturnCode = STATUS_C40_IP_BUSY;
        }
    }
    return ReturnCode;
}


/**
 * Function Name    C40_Ip_UTestCheckBreakpoint
 * Description      Switch the breakpoint if needed
 */
static void C40_Ip_UTestCheckBreakpoint(C40_Ip_FlashBreakPointsType BreakPoints)
{
    uint32 Temp;

    switch (BreakPoints)
    {
        case FLS_BREAKPOINTS_ON_DBD:
            Temp = C40_Ip_pFlashBaseAddress->MCRS;
            /* Clear bits MCR_EER, MCR_SBC (notes: write 1 to clear) */
            Temp &= ~(FLASH_MCRS_EER_MASK|FLASH_MCRS_SBC_MASK|FLASH_MCRS_AEE_MASK|FLASH_MCRS_EEE_MASK|FLASH_MCRS_RVE_MASK|FLASH_MCRS_RRE_MASK|FLASH_MCRS_RWE_MASK|FLASH_MCRS_PES_MASK|FLASH_MCRS_PEP_MASK);
            Temp |= (FLASH_MCRS_EER_MASK|FLASH_MCRS_SBC_MASK);
            C40_Ip_pFlashBaseAddress->MCRS = Temp;
            /* Set bit UT0_AIBPE */
            C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AIBPE_MASK;
            /* Clear SBCE bit if only double bit detection is selected */
            C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_SBCE_MASK;
            break;

        case FLS_BREAKPOINTS_ON_DBD_SBC:
            Temp = C40_Ip_pFlashBaseAddress->MCRS;
            /* Clear bits MCR_EER, MCR_SBC (notes: write 1 to clear) */
            Temp &= ~(FLASH_MCRS_EER_MASK|FLASH_MCRS_SBC_MASK|FLASH_MCRS_AEE_MASK|FLASH_MCRS_EEE_MASK|FLASH_MCRS_RVE_MASK|FLASH_MCRS_RRE_MASK|FLASH_MCRS_RWE_MASK|FLASH_MCRS_PES_MASK|FLASH_MCRS_PEP_MASK);
            Temp |= (FLASH_MCRS_EER_MASK|FLASH_MCRS_SBC_MASK);
            C40_Ip_pFlashBaseAddress->MCRS = Temp;
            /* Set bit UT0_AIBPE */
            C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AIBPE_MASK;
            /* Set bit UT0_SBCE */
            C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_SBCE_MASK;
            break;

        default:
            /* Clear AIBPE bit if no break */
            C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_AIBPE_MASK;
            /* Clear SBCE bit if only double bit detection is selected */
            C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_SBCE_MASK;
            break;
    }
}

/**
 * Function Name    C40_Ip_ArrayIntegrityCheck
 * Description      This function will check the array integrity of the flash via main interface.
 *                  The user specified address sequence is used for array integrity reads
 *                  and the operation is done on the specified blocks. The MISR values calculated
 *                  by the hardware is compared to the values passed by the user, if they are not
 *                  the same, then an error code is returned.
 *                  User should call C40_Ip_CheckUserTestStatus to check the on-going status of this function.
 *                  And once finish, it will do comparison between MISR values provided by user which
 *                  is currently stored in 'pMisrExpectedValues' and MISR values generated by hardware
 *                  and return an appropriate code according to this compared result.
 *
 * @implements      C40_Ip_ArrayIntegrityCheck_Activity
 */
C40_Ip_StatusType C40_Ip_ArrayIntegrityCheck(uint32 SelectBlock,
                                             C40_Ip_ArrayIntegritySequenceType AddressSequence,
                                             C40_Ip_FlashBreakPointsType BreakPoints,
                                             const C40_Ip_MisrType *MisrSeedValues,
                                             uint8 DomainIdValue
                                            )
{
    C40_Ip_StatusType ReturnCode;
    uint32 WaitCounter = FLASH_USER_TEST_WAIT;  /* the loop count for the wait loop for Done bit */

    /* Check if input parameters were correct or not */
    if ((boolean)FALSE == C40_Ip_CheckSelecBlock(SelectBlock))
    {
        /* Wrong input parameters*/
        ReturnCode = STATUS_C40_IP_ERROR_INPUT_PARAM;
    }
    else
    {
        /* There is an in-progress UTest operation */
        ReturnCode = C40_Ip_UTestCheckBusy();
    }

    if (STATUS_C40_IP_SUCCESS == ReturnCode)
    {
        /* Write password to UT0 register to enable test mode */
        C40_Ip_pFlashBaseAddress->UT0 = C40_USER_TEST_PASSWORD;
        if (0x0U == (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_UTE_MASK))
        {
            /* Did not enable the Utest mode yet*/
            ReturnCode = STATUS_C40_IP_ERROR;
        }
        else
        {
            #if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
            /* Prepare timeout counter */
            C40_Ip_u32ElapsedTicks = 0UL;
            C40_Ip_u32TimeoutTicks = OsIf_MicrosToTicks(C40_SYNC_WRITE_TIMEOUT, (OsIf_CounterType)C40_TIMEOUT_TYPE);
            C40_Ip_u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)C40_TIMEOUT_TYPE);
            #endif

            /* Select the block to receive the array integrity check by doing an interlock write to that block */
            /*
            * The block selected for array integrity check do not need to be unlocked.
            * Write to the sector or block address to be erased using logical address registers located in the Platform Flash Controller
            */
            ReturnCode = C40_Ip_MainInterfaceWriteJobAddress((uint32)SelectBlock, DomainIdValue);

            if (STATUS_C40_IP_SUCCESS == ReturnCode)
            {
                /* One and only one ADATA register must also be written. This is referred to as an interlock write.*/
                C40_Ip_pFlashBaseAddress->DATA[0] = FLASH_DATA_PDATA((uint32)0xFFFFFFFFU);
                /* Set the Address sequence to be used */
                if (FLS_SEQUENTIAL == AddressSequence)
                {
                   /* The logical sequence is used */
                    C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AIS_MASK;
                }
                else
                {
                    /* The proprietary sequence is used */
                    C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_AIS_MASK;
                }

                /* Check the breakpoint */
                C40_Ip_UTestCheckBreakpoint(BreakPoints);
                /* Set the seed values of the MISR in UMx registers */
                C40_Ip_SetSeedMisr(MisrSeedValues);
                /* Initiate the Array Integrity Check by writing 1 to UT0_AIE bit*/
                C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AIE_MASK;
                /* Return here, not wait until UT0_AID is set */
            }
            else
            {
                /* Write job address has been failed, create a dummy check to clear interlock and disable UTest mode */

                /* One and only one ADATA register must also be written. This is referred to as an interlock write.*/
                C40_Ip_pFlashBaseAddress->DATA[0] = FLASH_DATA_PDATA((uint32)0xFFFFFFFFU);

                /* Initiate the Array Integrity Check by writing 1 to UT0_AIE bit*/
                C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AIE_MASK;

                /* Abort the array integrity operation */
                C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_AIE_MASK;

                /* Wait the UT0_AID bit goes high */
                while ((0x0U == (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)) && (WaitCounter > 0U))
                {
                    WaitCounter--;
                }

                /* Disable UTest mode */
                C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_UTE_MASK;
            }
        }
    }
    return ReturnCode;
}

static boolean C40_Ip_CheckSelecBlock(uint32 SelectBlock)
{
    boolean ReturnCode = (boolean)TRUE;

    /* check if it is wrong input block */
    if (
         (FLS_CODE_BLOCK_0_BASE_ADDR == SelectBlock) ||
#ifdef FLS_CODE_BLOCK_1_BASE_ADDR
         (FLS_CODE_BLOCK_1_BASE_ADDR == SelectBlock) ||
#endif
#ifdef FLS_CODE_BLOCK_2_BASE_ADDR
         (FLS_CODE_BLOCK_2_BASE_ADDR == SelectBlock) ||
#endif
#ifdef FLS_CODE_BLOCK_3_BASE_ADDR
         (FLS_CODE_BLOCK_3_BASE_ADDR == SelectBlock) ||
#endif
         (FLS_DATA_BLOCK_BASE_ADDR   == SelectBlock) ||
         (FLS_UTEST_BLOCK_BASE_ADDR  == SelectBlock)
       )
    {
        /* Input parameter was correct */
    }
    else
    {
        /* Wrong input parameters*/
        ReturnCode = (boolean)FALSE;
    }

    return ReturnCode;
}

/**
 * Function Name    C40_Ip_CheckUserTestStatus
 * Description      This function will check the status array integrity check in user test mode.
 *
 * @implements      C40_Ip_CheckUserTestStatus_Activity
 */
C40_Ip_StatusType C40_Ip_CheckUserTestStatus(const C40_Ip_MisrType *MisrExpectedValues,
                                             C40_Ip_UtestStateType *TestResult
                                            )
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;

    C40_IP_DEV_ASSERT(NULL_PTR != MisrExpectedValues);
    C40_IP_DEV_ASSERT(NULL_PTR != TestResult);

    if ((NULL_PTR == MisrExpectedValues) || (NULL_PTR == TestResult))
    {
        ReturnCode = STATUS_C40_IP_ERROR_INPUT_PARAM;
    }
    else
    {
        *TestResult = C40_IP_OK;

        /* There must be an UTest operation */
        if (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AIE_MASK))
        {
            /* If DONE bit goes high */
            if (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK))
            {
                /* If the operation is suspended */
                if (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AISUS_MASK))
                {
                    *TestResult = C40_IP_USER_TEST_SUS;
                }
                else
                {
                    ReturnCode = C40_Ip_CheckUserTestStatusExecution(MisrExpectedValues, TestResult);
                }
            }
            else
            {
                /* DONE bit is still low means the operation is in-progress */
                ReturnCode = STATUS_C40_IP_BUSY;
            }
        }
        else
        {
            ReturnCode = STATUS_C40_IP_ERROR_TIMEOUT;
        }
    }

    return ReturnCode;
}

/**
 * Function Name    C40_Ip_CheckUserTestStatusExecution
 * Description      This function is used in the C40_Ip_CheckUserTestStatus which
 *                  will check the status array integrity check in user test mode.
 */
static C40_Ip_StatusType C40_Ip_CheckUserTestStatusExecution(const C40_Ip_MisrType *MisrExpectedValues,
                                                             C40_Ip_UtestStateType *OpStatus
                                                            )
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;
    *OpStatus = C40_IP_OK;
    uint32 Temp;
    uint8 Index;

    /* Compare the hardware calculated MISR to the user input */
    for (Index = 0x0U; Index < FLASH_UM_COUNT; Index++)
    {
        Temp = MisrExpectedValues->arrMISRValue[Index];
        if (C40_Ip_pFlashBaseAddress->UM[Index] != Temp)
        {
            ReturnCode = STATUS_C40_IP_ERROR;
            break;
        }
    }

    if ((uint32)(C40_Ip_pFlashBaseAddress->UM9 & FLASH_UM9_MISR_MASK) != MisrExpectedValues->arrMISRValue[9])
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }

    /* If the operation is broken */
    if (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_NAIBP_MASK))
    {
        *OpStatus = ((C40_Ip_pFlashBaseAddress->MCRS & FLASH_MCRS_SBC_MASK) != 0x0U) ? C40_IP_USER_TEST_BREAK_SBC : C40_IP_USER_TEST_BREAK_DBD;
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    else
    {
        /* Clear UT0_MRE, UT0_AIS, UT0_AIE, then UT0_UTE */
        C40_Ip_pFlashBaseAddress->UT0 &= ~(FLASH_UT0_AIS_MASK|FLASH_UT0_MRE_MASK);
        C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_AIE_MASK;
        C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_UTE_MASK;
    }
    return ReturnCode;
}

/**
 * Function Name    C40_Ip_ArrayIntegrityCheckSuspend
 * Description      This function will check if there is an on-going array integrity
 *                  check of the flash and suspend it via main interface.
 *
 * @implements      C40_Ip_ArrayIntegrityCheckSuspend_Activity
 */
C40_Ip_StatusType C40_Ip_ArrayIntegrityCheckSuspend(void)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;
    uint32 WaitCounter = FLASH_USER_TEST_WAIT;   /* the loop count for the wait loop */

    /* There must be an UTest operation is in-progress */
    if ((0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AIE_MASK)) && (0x0U == (C40_Ip_pFlashBaseAddress->UT0 & (FLASH_UT0_AISUS_MASK|FLASH_UT0_AID_MASK))))
    {
        /* Set bit UT0_AISUS */
        C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AISUS_MASK;
        /* Wait the UT0_AID bit goes high */
        while ((0x0U == (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)) && (WaitCounter > 0U))
        {
            WaitCounter--;
        }
        if ((0x0U == (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AISUS_MASK)) || (0x0U == (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)))
        {
            /* the ongoing array integrity check was not successfully suspended */
            ReturnCode = STATUS_C40_IP_ERROR;
        }
    }
    /* there is no suspended array integrity check */
    else
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    return ReturnCode;
}

static inline C40_Ip_StatusType C40_Ip_ArrayIntegrityResumeSuspended(void)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;
    uint32 WaitCounter = FLASH_USER_TEST_WAIT;

    /* Clear bit UT0_AISUS */
    C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_AISUS_MASK;
    /* Wait the UT0_AID bit goes low */
    while ((0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)) && (WaitCounter > 0U))
    {
        WaitCounter--;
    }

    if ((0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AISUS_MASK)) || (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)))
    {
        /* the ongoing array integrity check was not successfully resumed */
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    return ReturnCode;
}


static inline C40_Ip_StatusType C40_Ip_ArrayIntegrityResumeBroken(void)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;
    uint32 WaitCounter = FLASH_USER_TEST_WAIT;
    uint32 Temp;

    Temp = C40_Ip_pFlashBaseAddress->MCRS;
    /* Clear bits MCR_EER, MCR_SBC (notes: write 1 to clear) */
    Temp &= ~(FLASH_MCRS_EER_MASK|FLASH_MCRS_SBC_MASK|FLASH_MCRS_AEE_MASK|FLASH_MCRS_EEE_MASK|FLASH_MCRS_RVE_MASK|FLASH_MCRS_RRE_MASK|FLASH_MCRS_RWE_MASK|FLASH_MCRS_PES_MASK|FLASH_MCRS_PEP_MASK);
    Temp |=  (FLASH_MCRS_EER_MASK|FLASH_MCRS_SBC_MASK);
    C40_Ip_pFlashBaseAddress->MCRS = Temp;

    /* Clear UT0_NAIBP to resume the operation */
    C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_NAIBP_MASK;
    /* Wait the UT0_AID bit goes low */
    while ((0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)) && (WaitCounter > 0U))
    {
        WaitCounter--;
    }

    if ((0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_NAIBP_MASK)) || (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)))
    {
        /* the ongoing array integrity check was not successfully resumed */
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    return ReturnCode;
}

/**
 * Function Name    C40_Ip_ArrayIntegrityCheckResume
 * Description      This function will check if there is an on-going array integrity
 *                  check of the flash being suspended and resume it via main interface.
 *
 * @implements      C40_Ip_ArrayIntegrityCheckResume_Activity
 */
C40_Ip_StatusType C40_Ip_ArrayIntegrityCheckResume(void)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;

    /* There must be an UTest operation */
    if (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AIE_MASK))
    {
        /* The operation is in suspended state */
        if ((C40_Ip_pFlashBaseAddress->UT0 & (FLASH_UT0_AISUS_MASK | FLASH_UT0_AID_MASK)) == (FLASH_UT0_AISUS_MASK | FLASH_UT0_AID_MASK))
        {
            ReturnCode = C40_Ip_ArrayIntegrityResumeSuspended();
        }
            /* Resume operation is broken due to an error */
        else if (0x0U != (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_NAIBP_MASK))
        {
            ReturnCode = C40_Ip_ArrayIntegrityResumeBroken();
        }
        else
        {
            /* Do nothing */
        }
    }
    /* there is no resumed array integrity check */
    else
    {
        ReturnCode = STATUS_C40_IP_ERROR;
    }
    return ReturnCode;
}

/**
 * Function Name    C40_Ip_UserMarginReadCheck
 * Description      This function will check the user margin reads of the flash via main interface.
 *                  The user specified margin level is used for reads and the operation is done on the specified blocks.
 *                  The MISR values calculated by the hardware are compared to the values passed by the user,
 *                  if they are not the same, then an error code is returned.
 *                  User should call C40_Ip_CheckUserTestStatus to check the on-going status of this function.
 *                  And once finish, it will do comparison between MISR values provided by user
 *                  which are currently stored in 'pMisrExpectedValues,' and MISR values
 *                  generated by hardware and return an appropriate code according to this compared result.
 *
 * @implements      C40_Ip_UserMarginReadCheck_Activity
 */
C40_Ip_StatusType C40_Ip_UserMarginReadCheck(uint32 SelectBlock,
                                             C40_Ip_FlashBreakPointsType BreakPoints,
                                             C40_Ip_MarginOptionType MarginLevel,
                                             const C40_Ip_MisrType *MisrSeedValues,
                                             uint8 DomainIdValue
                                            )
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;
    uint32 WaitCounter = FLASH_USER_TEST_WAIT;  /* the loop count for the wait loop for Done bit */

    /* Check if input parameters were correct or not */
    if ((boolean)FALSE == C40_Ip_CheckSelecBlock(SelectBlock))
    {
        /* Wrong input parameters*/
        ReturnCode = STATUS_C40_IP_ERROR_INPUT_PARAM;
    }
    else
    {
        /* There is an in-progress UTest operation */
        ReturnCode = C40_Ip_UTestCheckBusy();
    }


    if (STATUS_C40_IP_SUCCESS == ReturnCode)
    {
        /* Write password to UT0 register to enable test mode */
        C40_Ip_pFlashBaseAddress->UT0 = C40_USER_TEST_PASSWORD;
        if (0x0U == (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_UTE_MASK))
        {
            /* Did not enable the Utest mode yet*/
            ReturnCode = STATUS_C40_IP_ERROR;
        }
        else
        {
            #if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
            /* Prepare timeout counter */
            C40_Ip_u32ElapsedTicks = 0UL;
            C40_Ip_u32TimeoutTicks = OsIf_MicrosToTicks(C40_SYNC_WRITE_TIMEOUT, (OsIf_CounterType)C40_TIMEOUT_TYPE);
            C40_Ip_u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)C40_TIMEOUT_TYPE);
            #endif

            /* Select the block to receive the array integrity check by doing an interlock write to that block */
            /*
            * The block selected for array integrity check do not need to be unlocked.
            * Write to the sector or block address to be erased using logical address registers located in the Platform Flash Controller
            */
            ReturnCode = C40_Ip_MainInterfaceWriteJobAddress((uint32)SelectBlock, DomainIdValue);

            if (STATUS_C40_IP_SUCCESS == ReturnCode)
            {
                /* One and only one ADATA register must also be written. This is referred to as an interlock write.*/
                C40_Ip_pFlashBaseAddress->DATA[0] = FLASH_DATA_PDATA((uint32)0xFFFFFFFFU);
                /* Set the Address sequence to be used: linear sequence */
                C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AIS_MASK;

                /* Check breakpoint */
                C40_Ip_UTestCheckBreakpoint(BreakPoints);

                /* Set UT0_MRE to enable User Margin Read */
                C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_MRE_MASK;
                /* Set the Margin level to be used */
                if (C40_MARGIN_LEVEL_ERASE == MarginLevel)
                {
                    /* The erased level is used */
                    C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_MRV_MASK;
                }
                else
                {
                    /* The programmed level is used */
                    C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_MRV_MASK;
                }
                /* Set the seed values of the MISR in UMx registers */
                C40_Ip_SetSeedMisr(MisrSeedValues);
                /* Initiate the Array Integrity Check by writing 1 to UT0_AIE bit*/
                C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AIE_MASK;
                /* Return here, not wait until UT0_AID is set */
            }
            else
            {
                /* Write job address has been failed, create a dummy check to clear interlock and disable UTest mode */

                /* One and only one ADATA register must also be written. This is referred to as an interlock write.*/
                C40_Ip_pFlashBaseAddress->DATA[0] = FLASH_DATA_PDATA((uint32)0xFFFFFFFFU);

                /* Initiate the Array Integrity Check by writing 1 to UT0_AIE bit*/
                C40_Ip_pFlashBaseAddress->UT0 |= FLASH_UT0_AIE_MASK;

                /* Abort the array integrity operation */
                C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_AIE_MASK;

                /* Wait the UT0_AID bit goes high */
                while ((0x0U == (C40_Ip_pFlashBaseAddress->UT0 & FLASH_UT0_AID_MASK)) && (WaitCounter > 0U))
                {
                    WaitCounter--;
                }

                /* Disable UTest mode */
                C40_Ip_pFlashBaseAddress->UT0 &= ~FLASH_UT0_UTE_MASK;
            }
        }
    }
    return ReturnCode;
}

/**
 * Function Name    C40_Ip_GetFailedAddress
 * Description      This function will get the failing address in the event of ECC event error,
 *                  Single Bit Correction, as well as providing the address of a failure
 *                  that may have raised in a program/erase operation.
 *                  The address captured is from main array space or UTest array space.
 *
 * @implements     C40_Ip_GetFailedAddress_Activity
 */
uint32 C40_Ip_GetFailedAddress(void)
{
    uint32 Addr = FLS_INVALID_ADDR;
    uint32 CapturedRegion;
    uint32 AddrOffset;
    const uint32 ADRValue = C40_Ip_pFlashBaseAddress->ADR;

    /* get offset value */
    AddrOffset = (ADRValue & FLASH_ADR_ADDR_MASK) >> FLASH_ADR_ADDR_SHIFT;  /* double-word address that selects 64 bits */
    AddrOffset <<= 3;                                                       /* convert to byte address */
    if (C40_IP_PGM_WRITE == C40_Ip_eOpStatus)
    {
        AddrOffset += C40_Ip_u32LogicalAddressCheckFail;                    /* add the programmed address */
    }

    /* get region block error */
    CapturedRegion = ADRValue & FLASH_FAILED_ADDRESS_REGION_MASK;

    /* Select the memory address space */
    if ( (ADRValue & FLASH_ADR_SAD_MASK) != 0U )
    {
        /* Address captured or to be accessed is from the UTest NVM array space*/
        if ( (ADRValue & FLASH_REGION_0_MASK) != 0U )
        {
            Addr = FLS_UTEST_BLOCK_BASE_ADDR;
        }
    }
    else
    {
        /* Address captured or to be accessed is from the main array space */
        switch (CapturedRegion)
        {
            case FLASH_REGION_0_MASK:
                Addr = FLASH_REGION_0_ADDR + AddrOffset;
                break;

            case FLASH_REGION_1_MASK:
                Addr = FLASH_REGION_1_ADDR + AddrOffset;
                break;

            case FLASH_REGION_2_MASK:
                Addr = FLASH_REGION_2_ADDR + AddrOffset;
                break;

            case FLASH_REGION_3_MASK:
                Addr = FLASH_REGION_3_ADDR + AddrOffset;
                break;

            case FLASH_REGION_4_MASK:
                Addr = FLASH_REGION_4_ADDR + AddrOffset;
                break;

            case FLASH_REGION_5_MASK:
                Addr = FLASH_REGION_5_ADDR + AddrOffset;
                break;

            default:
                /* Do nothing */
                break;
        }
    }

    return Addr;
}

#if ( (C40_ECC_CHECK == STD_ON) || (C40_ECC_CHECK_BY_AUTOSAR_OS == STD_ON) )
/**
 * @brief    Low level data storage exception handler.
 *
 * @details  This function will be marked current pending job as failed, processing may continue or skipping the causing instruction.
 *
 * @return   Fls_CompHandlerReturnType
 * @retval   FLS_HANDLED_SKIP The data storage exception was caused by currently pending flash read or compare job
 * @retval   FLS_UNHANDLED    The data storage exception was NOT caused by currently pending flash read or compare job
 */
Fls_CompHandlerReturnType C40_Ip_DsiHandler(const Fls_ExceptionDetailsType *pExceptionDetailsPtr)
{
    Fls_CompHandlerReturnType RetVal = FLS_UNHANDLED;
    C40_Ip_StatusType ReadStatus = C40_Ip_eReadStatus;
    uint32 ReadAddress = C40_Ip_u32ReadAddress;

    C40_IP_DEV_ASSERT(pExceptionDetailsPtr != NULL_PTR);

    /*  Check whether there is
        [1] pending read, compare, erase or write job,
        [2] exception syndrome register indicates DSI reason, and
        [3] data_pt matches address currently accessed by pending flash read or flash compare job */
    if ( ( STATUS_C40_IP_BUSY == ReadStatus )
        &&
        (C40_DSI_EXC_SYNDROME == (pExceptionDetailsPtr->syndrome_u32 & C40_DSI_EXC_SYNDROME))
        &&
        (pExceptionDetailsPtr->data_pt == ReadAddress )
      )
    {
        C40_Ip_eReadStatus = STATUS_C40_IP_ERROR;
        RetVal = FLS_HANDLED_SKIP;
    }
    else
    {
        /* FLS_UNHANDLED */
    }

    return RetVal;
}


/**
 * Function Name    C40_Ip_InvalidPrefetchBuff
 * Description      Invalidate prefect buff to make sure that ecc will occur all times when read ecc area
 */
static C40_Ip_StatusType C40_Ip_InvalidPrefetchBuff(uint32 StartAddress)
{
    C40_Ip_StatusType ReturnCode = STATUS_C40_IP_SUCCESS;

    /* Write the logical address */
#if (STD_ON == C40_IP_ENABLE_USER_MODE_SUPPORT)
    OsIf_Trusted_Call1param(C40_Ip_MainInterfaceWriteLogicalAddress, StartAddress);
#else
    C40_Ip_MainInterfaceWriteLogicalAddress(StartAddress);
#endif

    /* Write a dummy data */
    C40_Ip_pFlashBaseAddress->DATA[0] = 0x00U;
    /* Setup for a program operation to create the interlock write */
    C40_Ip_pFlashBaseAddress->MCR |= FLASH_MCR_PGM_MASK;

#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
    /* Prepare timeout counter */
    C40_Ip_u32ElapsedTicks = 0UL;
    C40_Ip_u32TimeoutTicks = OsIf_MicrosToTicks(C40_ABORT_TIMEOUT, (OsIf_CounterType)C40_TIMEOUT_TYPE);
    C40_Ip_u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)C40_TIMEOUT_TYPE);
#endif

    MCAL_FAULT_INJECTION_POINT(C40_IP_FMEA_INVALID_PREFETCH_BUFF_INJECT_ERROR);
    /* Wait until interlock write finishes */
    while (0U == (C40_Ip_pFlashBaseAddress->MCR & FLASH_MCR_PGM_MASK))
    {
#if (STD_ON == C40_TIMEOUT_SUPERVISION_ENABLED)
        C40_Ip_u32ElapsedTicks += OsIf_GetElapsed(&C40_Ip_u32CurrentTicks, (OsIf_CounterType)C40_TIMEOUT_TYPE);
        if (C40_Ip_u32ElapsedTicks >= C40_Ip_u32TimeoutTicks)
        {
            ReturnCode = STATUS_C40_IP_ERROR_TIMEOUT;
            break;
        }
#endif
    }

    /* Abort the program operation */
    C40_Ip_pFlashBaseAddress->MCR &= ~FLASH_MCR_PGM_MASK;

    return ReturnCode;
}
#endif /* (C40_ECC_CHECK == STD_ON) || (C40_ECC_CHECK_BY_AUTOSAR_OS == STD_ON) */

/**
 * Function Name    C40_Ip_GetAsyncMode
 * Description      set synch/Asynch at IP layer base on the bAynch of HLD
 */
void C40_Ip_SetAsyncMode(const boolean Async)
{
    C40_Ip_bAsync = Async;
}


/**
 * Function Name    C40_Ip_FlashAccessCalloutStart
 * Description      Call the callout function if it was configured
 */
static inline void C40_Ip_FlashAccessCalloutStart(void)
{
    if (NULL_PTR != C40_Ip_pConfigPtr->startFlashAccessNotifPtr)
    {
        C40_Ip_pConfigPtr->startFlashAccessNotifPtr();
    }
}


/**
 * Function Name    C40_Ip_FlashAccessCalloutFinish
 * Description      Call the callout function if it was configured
 */
static inline void C40_Ip_FlashAccessCalloutFinish(void)
{
    if (NULL_PTR != C40_Ip_pConfigPtr->finishedFlashAccessNotifPtr)
    {
        C40_Ip_pConfigPtr->finishedFlashAccessNotifPtr();
    }
}

/**
 * Function Name    C40_Ip_ValidCodeAddress
 * Description      Checks the address is a valid Code flash address
 */
static inline boolean C40_Ip_ValidCodeAddress(uint32 Address)
{
    /* Check if it is within the program flash address space or not */
    return ( (FLS_CODE_BLOCK_0_BASE_ADDR <= (Address)) && ((Address) <= FLS_CODE_BLOCK_END_ADDR) );
}

/**
 * Function Name    C40_Ip_ValidDataAddress
 * Description      Checks the address is a valid Data flash address
 */
static inline boolean C40_Ip_ValidDataAddress(uint32 Address)
{
    /* Check if it is within the data flash address space or not */
    return ( (FLS_DATA_BLOCK_BASE_ADDR <= (Address)) && ((Address) <= FLS_DATA_BLOCK_END_ADDR) );
}

/**
 * Function Name    C40_Ip_ValidUTestAddress
 * Description      Checks the address is a valid UTest address
 */
static inline boolean C40_Ip_ValidUTestAddress(uint32 Address)
{
    /* Check if it is within the UTest address space or not */
    return ( (FLS_UTEST_BLOCK_BASE_ADDR <= (Address)) && ((Address) <= FLS_UTEST_BLOCK_END_ADDR) );
}

/**
 * Function Name    C40_Ip_ValidAddress
 * Description      Checks the address is a valid UTest address
 */
static inline boolean C40_Ip_ValidAddress(uint32 Address)
{
    /* Check if it is within the program flash or data flash or UTest space or not */
    return ( C40_Ip_ValidCodeAddress(Address) || C40_Ip_ValidDataAddress(Address) || C40_Ip_ValidUTestAddress(Address) );
}

/**
 * Function Name    C40_Ip_ValidRangeAddress
 * Description      Checks both start and end address are within the Program or Data or UTest flash space,
 *                  using before Read/Compare/Write operations
 */
static inline boolean C40_Ip_ValidRangeAddress(uint32 StartAddress,
                                               uint32 Length
                                              )
{
    boolean RetVal;
    uint32 EndAddress = StartAddress + Length - 1UL;

    /* The start and end address must be within the program flash or data flash or UTest space */
    if (C40_Ip_ValidCodeAddress(StartAddress) && C40_Ip_ValidCodeAddress(EndAddress))
    {
        RetVal = (boolean)TRUE;
    }
    else if (C40_Ip_ValidDataAddress(StartAddress) && C40_Ip_ValidDataAddress(EndAddress))
    {
        RetVal = (boolean)TRUE;
    }
    else if (C40_Ip_ValidUTestAddress(StartAddress) && C40_Ip_ValidUTestAddress(EndAddress))
    {
        RetVal = (boolean)TRUE;
    }
    else
    {
        /* Invalid memory range */
        RetVal = (boolean)FALSE;
    }

    return RetVal;
}


#define MEM_43_INFLS_STOP_SEC_CODE
#include "Mem_43_InFls_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
