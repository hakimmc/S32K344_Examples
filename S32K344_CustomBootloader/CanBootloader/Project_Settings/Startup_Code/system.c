/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 2.0.0
*   Build Version        : S32K3_RTD_2_0_0_D2203_ASR_REL_4_4_REV_0000_20220331
*
*   (c) Copyright 2020 - 2022 NXP Semiconductors
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

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Platform_Types.h"
#include "Mcal.h"
#include "system.h"
#include "core_specific.h"

#ifdef S32K344
    #include "S32K344_SCB.h"
    #include "S32K344_MPU.h"
    #include "S32K344_MSCM.h"
#endif
#if defined (S32K342) || defined (S32K341)
    #include "S32K342_SCB.h"
    #include "S32K342_MPU.h"
    #include "S32K342_MSCM.h"
#endif
#ifdef S32K324
    #include "S32K324_SCB.h"
    #include "S32K324_MPU.h"
    #include "S32K324_MSCM.h"
#endif 
#ifdef S32K314
    #include "S32K314_SCB.h"
    #include "S32K314_MPU.h"
    #include "S32K314_MSCM.h"
#endif
#ifdef S32K312
    #include "S32K312_SCB.h"
    #include "S32K312_MPU.h"
    #include "S32K312_MSCM.h"
#endif
#ifdef S32K322
    #include "S32K322_SCB.h"
    #include "S32K322_MPU.h"
    #include "S32K322_MSCM.h"
#endif
/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

extern  uint32 __INT_ITCM_START[];
extern  uint32 __ROM_CODE_START[];
extern  uint32 __ROM_DATA_START[];
extern  uint32 __INT_DTCM_START[];
extern  uint32 __INT_SRAM_START[];
extern  uint32 __RAM_NO_CACHEABLE_START[];
extern  uint32 __RAM_SHAREABLE_START[];
extern  uint32 __RAM_CACHEABLE_SIZE[];
extern  uint32 __RAM_NO_CACHEABLE_SIZE[];
extern  uint32 __RAM_SHAREABLE_SIZE[];
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define CM7_0  (0UL)
#define CM7_1  (1UL)

#define SVC_GoToSupervisor()      ASM_KEYWORD("svc 0x0")
#define SVC_GoToUser()            ASM_KEYWORD("svc 0x1")

#define S32_SCB_CPACR_CPx_MASK(CpNum)             (0x3U << S32_SCB_CPACR_CPx_SHIFT(CpNum))
#define S32_SCB_CPACR_CPx_SHIFT(CpNum)            (2U*((uint32)CpNum))
#define S32_SCB_CPACR_CPx(CpNum, x)               (((uint32)(((uint32)(x))<<S32_SCB_CPACR_CPx_SHIFT((CpNum))))&S32_SCB_CPACR_CPx_MASK((CpNum)))

/* MPU setting */
#ifndef MULTIPLE_IMAGE
/* Single ELF for one or all cores */
/* Number of entries in the memory tables */
#if defined (S32K344) || defined (S32K342) || defined (S32K324) || defined (S32K314) || defined (S32K322) || defined (S32K341)
#define CPU_MPU_MEMORY_COUNT (15U)

/*
  Region  Description       Start       End           Size[KB]  Type              Inner Cache Policy    Outer Cache Policy    Shareable    Executable    Privileged Access    Unprivileged Access
--------  -------------     ----------  ----------  ----------  ----------------  --------------------  --------------------  -----------  ------------  -------------------  ---------------------
       0  Whole memory map  0x0         0xFFFFFFFF     4194304  Strongly Ordered  None                  None                  Yes          No            No Access            No Access
       1  ITCM              0x0         0xFFFF              64  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           No Access
       2  Program Flash     0x400000    0x7FFFFF          4096  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read-Only            Read-Only
       3  Data Flash        0x10000000  0x1003FFFF         256  Normal            Write-Back/Allocate   Write-Back/Allocate   No           No            Read-Only            Read-Only
       4  DTCM              0x20000000  0x2001FFFF         128  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           No Access
       5  SRAM + STACK      0x20400000  0x2043FFFF         256  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       6  SRAM NC           0x20430000  0x2043FFFF          64  Normal            None                  None                  Yes          No            Read/Write           Read/Write
       7  SRAM SHARED       0x20440000  0x20443FFF          16  Normal            None                  None                  Yes          No            Read/Write           Read/Write
       8  AIPS_0            0x40000000  0x401FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
       9  AIPS_1            0x40200000  0x403FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      10  AIPS_2            0x40400000  0x405FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      11  QSPI Rx           0x67000000  0x670003FF           1  Device            None                  None                  Yes          No            Read/Write           Read/Write
      12  QSPI AHB          0x68000000  0x6FFFFFFF      131072  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
      13  PPB               0xE0000000  0xE00FFFFF        1024  Strongly Ordered  None                  None                  Yes          No            Read/Write           Read/Write
*/

 volatile   uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x0UL};
 volatile   uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x0UL};

#elif defined (S32K312) 
#define CPU_MPU_MEMORY_COUNT (15U)

/*
  Region  Description       Start       End           Size[KB]  Type              Inner Cache Policy    Outer Cache Policy    Shareable    Executable    Privileged Access    Unprivileged Access
--------  -------------     ----------  ----------  ----------  ----------------  --------------------  --------------------  -----------  ------------  -------------------  ---------------------
       0  Whole memory map  0x0         0xFFFFFFFF     4194304  Strongly Ordered  None                  None                  Yes          No            No Access            No Access
       1  ITCM              0x0         0xFFFF              64  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           No Access
       2  Program Flash     0x400000    0x7FFFFF          4096  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read-Only            Read-Only
       3  Data Flash        0x10000000  0x1003FFFF         256  Normal            Write-Back/Allocate   Write-Back/Allocate   No           No            Read-Only            Read-Only
       4  DTCM              0x20000000  0x2001FFFF         128  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           No Access
       5  SRAM + STACK      0x20400000  0x2043FFFF         256  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       6  SRAM NC           0x20430000  0x2043FFFF          64  Normal            None                  None                  Yes          No            Read/Write           Read/Write
       7  SRAM SHARED       0x20440000  0x20443FFF          16  Normal            None                  None                  Yes          No            Read/Write           Read/Write
       8  AIPS_0            0x40000000  0x401FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
       9  AIPS_1            0x40200000  0x403FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      10  AIPS_2            0x40400000  0x405FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      11  QSPI Rx           0x67000000  0x670003FF           1  Device            None                  None                  Yes          No            Read/Write           Read/Write
      12  QSPI AHB          0x68000000  0x6FFFFFFF      131072  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
      13  PPB               0xE0000000  0xE00FFFFF        1024  Strongly Ordered  None                  None                  Yes          No            Read/Write           Read/Write
*/

 volatile   uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x0UL};
 volatile   uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x0UL};
#endif
#else
#if defined(CORE0)
/* Multiple core approach */
/* Number of entries in the memory tables */
#define CPU_MPU_MEMORY_COUNT (15U)

/*
  Region  Description       Start       End           Size[KB]  Type              Inner Cache Policy    Outer Cache Policy    Shareable    Executable    Privileged Access    Unprivileged Access
--------  -------------     ----------  ----------  ----------  ----------------  --------------------  --------------------  -----------  ------------  -------------------  ---------------------
       0  Whole memory map  0x0         0xFFFFFFFF     4194304  Strongly Ordered  None                  None                  Yes          No            No Access            No Access
       1  ITCM              0x0         0xFFFF              64  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           No Access
       2  Program Flash     0x400000    0x5FFFFF          2048  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read-Only            Read-Only
       3  Data Flash        0x10000000  0x1003FFFF         256  Normal            Write-Back/Allocate   Write-Back/Allocate   No           No            Read-Only            Read-Only
       4  DTCM              0x20000000  0x2001FFFF         128  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           No Access
       5  SRAM + STACK      0x20400000  0x2040FFFF          64  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       6  SRAM + STACK      0x20410000  0x20417FFF          32  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       7  SRAM NC           0x20418000  0x2041FFFF          32  Normal            None                  None                  Yes          No            Read/Write           Read/Write
       8  SRAM SHARED       0x20420000  0x20428000          32  Normal            None                  None                  Yes          No            Read/Write           Read/Write
       9  AIPS_0            0x40000000  0x401FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      10  AIPS_1            0x40200000  0x403FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      11  AIPS_2            0x40400000  0x405FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      12  QSPI Rx           0x67000000  0x670003FF           1  Device            None                  None                  Yes          No            Read/Write           Read/Write
      13  QSPI AHB          0x68000000  0x6FFFFFFF      131072  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
      14  PPB               0xE0000000  0xE00FFFFF        1024  Strongly Ordered  None                  None                  Yes          No            Read/Write           Read/Write
*/

 volatile   uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x0UL};
 volatile   uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x0UL};
#elif defined(CORE1)
/* Multiple core approach */
/* Number of entries in the memory tables */
#define CPU_MPU_MEMORY_COUNT (15U)

/*
  Region  Description       Start       End           Size[KB]  Type              Inner Cache Policy    Outer Cache Policy    Shareable    Executable    Privileged Access    Unprivileged Access
--------  -------------     ----------  ----------  ----------  ----------------  --------------------  --------------------  -----------  ------------  -------------------  ---------------------
       0  Whole memory map  0x0         0xFFFFFFFF     4194304  Strongly Ordered  None                  None                  Yes          No            No Access            No Access
       1  ITCM              0x0         0xFFFF              64  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           No Access
       2  Program Flash     0x600000    0x7FFFFF          2048  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read-Only            Read-Only
       3  Data Flash        0x10000000  0x1003FFFF         256  Normal            Write-Back/Allocate   Write-Back/Allocate   No           No            Read-Only            Read-Only
       4  DTCM              0x20000000  0x2001FFFF         128  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           No Access
       5  SRAM + STACK      0x20428000  0x2042FFFF          32  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       6  SRAM + STACK      0x20430000  0x20437FFF          32  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       7  SRAM + STACK      0x20438000  0x2043FFFF          32  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       8  SRAM NC           0x20440000  0x20443FFF          16  Normal            None                  None                  Yes          No            Read/Write           Read/Write
       9  SRAM SHARED       0x20420000  0x20428000          32  Normal            None                  None                  Yes          No            Read/Write           Read/Write
      10  AIPS_0            0x40000000  0x401FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      11  AIPS_1            0x40200000  0x403FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      12  AIPS_2            0x40400000  0x405FFFFF        2048  Device            None                  None                  Yes          No            Read/Write           Read/Write
      13  QSPI Rx           0x67000000  0x670003FF           1  Device            None                  None                  Yes          No            Read/Write           Read/Write
      14  QSPI AHB          0x68000000  0x6FFFFFFF      131072  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
      15  PPB               0xE0000000  0xE00FFFFF        1024  Strongly Ordered  None                  None                  Yes          No            Read/Write           Read/Write
*/

 volatile   uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x0UL};
 volatile   uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x0UL};
#endif
#endif

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================-
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
#define PLATFORM_START_SEC_VAR_CLEARED_32
#include "Platform_MemMap.h"

/* Allocate a global variable which will be overwritten by the debugger if attached(in CMM), to catch the core after reset. */
uint32 RESET_CATCH_CORE;

#define PLATFORM_STOP_SEC_VAR_CLEARED_32
#include "Platform_MemMap.h"
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"

/*================================================================================================*/
/* 
 * @brief Initializes the caches on the platform based on build options. This requires the MPU areas to be configured and enabled before calling this routine.
 * @param: None
 * 
 * @return: None
 */
static INLINE void sys_m7_cache_init(void);
/* 
 * @brief Disables any previously configured and initialized cache, please make sure MPU is enabled before calling these apis
 * @param: None
 * 
 * @return: None
 */
static INLINE void sys_m7_cache_disable(void);
/* 
 * @brief Performs a cache clean operation over the configured caches. 
 * @param: None
 * 
 * @return: None
 */
static INLINE void sys_m7_cache_clean(void);


#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
LOCAL_INLINE void Direct_GoToUser(void);
#endif
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
LOCAL_INLINE void Direct_GoToUser(void)
{
    ASM_KEYWORD("push {r0}");
    ASM_KEYWORD("ldr r0, =0x1");
    ASM_KEYWORD("msr CONTROL, r0");
    ASM_KEYWORD("pop {r0}");
}
#endif
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT  
    extern uint32 startup_getControlRegisterValue(void);
    extern uint32 startup_getAipsRegisterValue(void);
    extern void Suspend_Interrupts(void);
    extern void Resume_Interrupts(void);
#endif /*MCAL_ENABLE_USER_MODE_SUPPORT*/



/*================================================================================================*/
/**
* @brief    startup_go_to_user_mode
* @details  Function called from startup.s to switch to user mode if MCAL_ENABLE_USER_MODE_SUPPORT
*           is defined
*/
/*================================================================================================*/
void startup_go_to_user_mode(void);
void startup_go_to_user_mode(void)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    ASM_KEYWORD("svc 0x1");
#endif
}

/*================================================================================================*/
/**
* @brief   Default IRQ handler
* @details Infinite Loop
*/
/*================================================================================================*/
void default_interrupt_routine(void)
{
    while(TRUE){};
}

/*================================================================================================*/
/**
* @brief Sys_GoToSupervisor
* @details function used to enter to supervisor mode.
*           check if it's needed to switch to supervisor mode and make the switch.
*           Return 1 if switch was done
*/
/*================================================================================================*/

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
uint32 Sys_GoToSupervisor(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;
    uint32 u32SwitchToSupervisor;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    /* if core is already in supervisor mode for Thread mode, or running form Handler mode, there is no need to make the switch */
    if((0U == (u32ControlRegValue & 1u)) || (0u < (u32AipsRegValue & 0xFFu)))
    {
        u32SwitchToSupervisor = 0U;
    }
    else
    {
        u32SwitchToSupervisor = 1U;
        SVC_GoToSupervisor();
    }

    return u32SwitchToSupervisor;
}

/*================================================================================================*/
/**
* @brief Sys_GoToUser_Return
* @details function used to switch back to user mode for Thread mode, return a uint32 value passed as parameter
*/
/*================================================================================================*/
uint32 Sys_GoToUser_Return(uint32 u32SwitchToSupervisor, uint32 u32returnValue)
{
    if (1UL == u32SwitchToSupervisor)
    {
        Direct_GoToUser();
    }

    return u32returnValue;
}

uint32 Sys_GoToUser(void)
{
    Direct_GoToUser();
    return 0UL;
}
/*================================================================================================*/
/**
* @brief Sys_SuspendInterrupts
* @details Suspend Interrupts
*/
/*================================================================================================*/
void Sys_SuspendInterrupts(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    if((0U == (u32ControlRegValue & 1u)) || (0u < (u32AipsRegValue & 0xFFu)))
    {
        Suspend_Interrupts();
    }
    else
    {
        ASM_KEYWORD(" svc 0x3");
    }
}
/*================================================================================================*/
/**
* @brief Sys_ResumeInterrupts
* @details Resume Interrupts
*/
/*================================================================================================*/
void Sys_ResumeInterrupts(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    if((0U == (u32ControlRegValue & 1u)) || (0u < (u32AipsRegValue & 0xFFu)))
    {
        Resume_Interrupts();
    }
    else
    {
        ASM_KEYWORD(" svc 0x2");
    }
}
#endif
/*================================================================================================*/
/**
* @brief Sys_GetCoreID
* @details Function used to get the ID of the currently executing thread
*/
/*================================================================================================*/
#if !defined(USING_OS_AUTOSAROS)
uint8 Sys_GetCoreID(void)
{
    return (IP_MSCM->CPXNUM & MSCM_CPXNUM_CPN_MASK);
}
#endif

/*================================================================================================*/
/*
 * system initialization : system clock, interrupt router ...
 */


void SystemInit(void)
{
    uint32 i;
    uint32 coreMask = 0UL;
    uint8 coreId = OsIf_GetCoreID();
#ifdef MPU_ENABLE
    uint8 index = 0U;
    uint8 regionNum = 0U;
#endif /* MPU_ENABLE */    
    switch(coreId)
    {
        case CM7_0:
            coreMask = (1UL << MSCM_IRSPRC_M7_0_SHIFT);
            break;
        case CM7_1:
#ifdef S32K324
            coreMask = (1UL << MSCM_IRSPRC_M7_1_SHIFT);
#endif
            break;
        default:
            coreMask = 0UL;
            break;
    }

    /* Configure MSCM to enable/disable interrupts routing to Core processor */
    for (i = 0; i < MSCM_IRSPRC_COUNT; i++) 
    {
        IP_MSCM->IRSPRC[i] |= coreMask;
    }
/**************************************************************************/
                      /* FPU ENABLE*/
/**************************************************************************/
#ifdef ENABLE_FPU
    /* Enable CP10 and CP11 coprocessors */
    S32_SCB->CPACR |= (S32_SCB_CPACR_CPx(10U, 3U) | S32_SCB_CPACR_CPx(11U, 3U)); 

    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif /* ENABLE_FPU */
/**************************************************************************/
                      /* MPU ENABLE*/
/**************************************************************************/  
#ifdef MPU_ENABLE
/**************************************************************************/
                      /* DEFAULT MEMORY ENABLE*/
/**************************************************************************/
    /* Init MPU table for memory layout*/
    /* Cover all memory on device as background set all memory as strong-order and no access*/
    rbar[0]=0x00000000UL;
    rasr[0]=0x1004003FUL;
    
    /* ITCM for cortex M7 if no set it as zero */
    rbar[1]=(uint32)__INT_ITCM_START;
    rasr[1]=0x0104001FUL;
    /*Program flash which would extract from linker symbol*/
    rbar[2]=(uint32)__ROM_CODE_START;
    rasr[2]=0x060B002BUL; 

    /*Data flash which would extract from linker symbol*/
    rbar[3]=(uint32)__ROM_DATA_START;
    rasr[3]=0x16050023UL;  /* Device, Non-cache, Share */
    
    /*DTCM for cortex m7 if no set it as zero*/
    rbar[4]=(uint32)__INT_DTCM_START;
    rasr[4]=0x01040021UL; 
    
    /*Ram unified section  + stack*/
#if !defined(S32K344) && !defined(S32K324)
    rbar[5]=(uint32)__INT_SRAM_START;
    rasr[5]=((uint32)0x030B0001UL)|(((uint32)__RAM_CACHEABLE_SIZE - 1) << 1);   
#else
    rbar[5]=(uint32)__INT_SRAM_START;
    /*disable subregion 7-8*/
    rasr[5]=((uint32)0x030B0001UL)|(((uint32)__RAM_CACHEABLE_SIZE - 1) << 1)|(1<<15)|(1<<14); 
#endif
    
    /*Ram non-cache section plus int result which is using for test report*/
    rbar[6]=(uint32)__RAM_NO_CACHEABLE_START;
    rasr[6]= ((uint32)0x130C0001UL)|(((uint32)__RAM_NO_CACHEABLE_SIZE - 1) << 1);

    /*Ram shareable section*/
    rbar[7]=(uint32)__RAM_SHAREABLE_START;
    rasr[7]=((uint32)0x130C0001UL)|(((uint32)__RAM_SHAREABLE_SIZE - 1) << 1);
    /* Additional configuration for peripheral device*/
    
    /*AIPS_0*/
    rbar[8]=0x40000000UL;
    rasr[8]=0x13050029UL; 
    
    /*AIPS_1*/
    rbar[9]=0x40200000UL;
    rasr[9]=0x13050029UL; 
    
    /*AIPS_2*/
    rbar[10]=0x40400000UL;
    rasr[10]=0x13050029UL; 
    
    /*QSPI Rx*/
    rbar[11]=0x67000000UL;
    rasr[11]=0x13050013UL; 
    
    /*QSPI AHB*/
    rbar[12]=0x68000000UL;
    rasr[12]=0x030B0035UL;
    
    /*QSPI AHB*/
    rbar[13]=0xE0000000UL;
    rasr[13]=0x13040027UL;
    
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");

    /*Checking if cache is enable before*/
    if (((((uint32)1U << (uint32)17U) & S32_SCB->CCR) != (uint32)0) || ((((uint32)1U << (uint32)16U) & S32_SCB->CCR) != (uint32)0))
    {
 /*synchronize cache before update mpu */
        sys_m7_cache_clean();
        sys_m7_cache_disable();
    }
    /* Set default memory regions */
    for (index = 0U; index < 15; index++)
    {
        if ((rasr[index]&(uint32)0x1) == (uint32)0x1)
        {
            S32_MPU->RNR  = regionNum;
            S32_MPU->RBAR = rbar[index];
            S32_MPU->RASR = rasr[index];
            regionNum++;
        }
    }

    /* Enable MPU */
    S32_MPU->CTRL |= S32_MPU_CTRL_ENABLE_MASK;

    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");

#endif /* MPU_ENABLE */
/**************************************************************************/
            /* ENABLE CACHE */
/**************************************************************************/
#if defined(D_CACHE_ENABLE) || defined(I_CACHE_ENABLE)
    sys_m7_cache_init();
#endif /*defined(D_CACHE_ENABLE) || defined(I_CACHE_ENABLE)*/    
}


/* Cache apis which are using for cache initilization, please make sure MPU is enable before calling these apis. Due to limitation of speculative access on cortex m7, MPU need to be initialized before enable cache. So if user specify -DDISABLE_MPUSTARTUP, cache will be disable in startup as well. If user want to enable cache again please call cache api after RM_init() or MPU_init() */

static INLINE void sys_m7_cache_init(void)
{     
#ifdef D_CACHE_ENABLE   
    uint32 ccsidr = 0U;
    uint32 sets = 0U;
    uint32 ways = 0U;

   
    /*init Data caches*/
    S32_SCB->CSSELR = 0U;                       /* select Level 1 data cache */
    ASM_KEYWORD("dsb");
    ccsidr = S32_SCB->CCSIDR;
    sets = (uint32)(CCSIDR_SETS(ccsidr));
    do {
      ways = (uint32)(CCSIDR_WAYS(ccsidr));
      do {
        S32_SCB->DCISW = (((sets << SCB_DCISW_SET_Pos) & SCB_DCISW_SET_Msk) |
                      ((ways << SCB_DCISW_WAY_Pos) & SCB_DCISW_WAY_Msk)  );  
        ASM_KEYWORD("dsb");
      } while (ways-- != 0U);
    } while(sets-- != 0U);
    ASM_KEYWORD("dsb");
    S32_SCB->CCR |=  (uint32)SCB_CCR_DC_Msk;  /* enable D-Cache */
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif /*D_CACHE_ENABLE*/

#ifdef I_CACHE_ENABLE  
    /*init Code caches*/
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    S32_SCB->ICIALLU = 0UL;                     /* invalidate I-Cache */
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    S32_SCB->CCR |=  (uint32)SCB_CCR_IC_Msk;  /* enable I-Cache */
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif /*I_CACHE_ENABLE*/

}


static INLINE void sys_m7_cache_disable(void)
{        
    sys_m7_cache_clean();
    S32_SCB->CCR &= ~((uint32)1U << 17U);
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    S32_SCB->CCR &= ~((uint32)1U << 16U);
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
}


static INLINE void sys_m7_cache_clean(void)
{  
#ifdef D_CACHE_ENABLE
    uint32 ccsidr = 0U;
    uint32 sets = 0U;
    uint32 ways = 0U;
    
    S32_SCB->CSSELR = 0U;                       /* select Level 1 data cache */
    ASM_KEYWORD("dsb");
    ccsidr = S32_SCB->CCSIDR;
    sets = (uint32)(CCSIDR_SETS(ccsidr));
    do {
      ways = (uint32)(CCSIDR_WAYS(ccsidr));
      do {
        S32_SCB->DCCISW = (((sets << 5) & (uint32)0x3FE0U) |
                      ((ways << 30) & (uint32)0xC0000000U)  );  
        ASM_KEYWORD("dsb");
      } while (ways-- != 0U);
    } while(sets-- != 0U);
    
    S32_SCB->CSSELR = (uint32)((S32_SCB->CSSELR) | 1U);
#endif /*D_CACHE_ENABLE*/

#ifdef I_CACHE_ENABLE      
    S32_SCB->ICIALLU = 0UL;
#endif /*I_CACHE_ENABLE*/    
    ASM_KEYWORD("dsb");
}


#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#ifdef __cplusplus
}
#endif
