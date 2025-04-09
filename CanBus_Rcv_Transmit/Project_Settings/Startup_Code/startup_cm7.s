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

#ifdef MULTIPLE_IMAGE
	#define RAM_DATA_INIT_ON_ALL_CORES
#endif

/* If this is a secodary core, it shall wait for the MSCM clock to be initialized */
#if defined(CORE1)
	#define NO_MSCM_CLOCK_INIT
#endif

#define MAIN_CORE 0
#define MCME_CTL_KEY    0x402DC000
#define MCME_PRTN1_PUPD 0x402DC304
#define MCME_PRTN1_STAT 0x402DC308
#define MCME_PRTN1_COFB0_CLKEN 0x402DC330
#define MCME_PRTN1_COFB0_STAT 0x402DC310
#define MCME_MSCM_REQ (1 << 24)
#define MCME_KEY 0x5AF0
#define MCME_INV_KEY 0xA50F
#define CM7_ITCMCR 0xE000EF90
#define CM7_DTCMCR 0xE000EF94

#define SBAF_BOOT_MARKER   (0x5AA55AA5)
#define CM7_0_ENABLE_SHIFT (0)
#define CM7_1_ENABLE_SHIFT (1)

#define CM7_0_ENABLE            (1)
#ifndef CM7_1_ENABLE
	#define CM7_1_ENABLE            (0)
#endif
#define CM7_0_VTOR_ADDR         (__CORE0_VTOR)
#define CM7_1_VTOR_ADDR         (__CORE1_VTOR)
#define XRDC_CONFIG_ADDR        (0)
#define LF_CONFIG_ADDR          (0)

    .syntax unified
    .arch armv7-m
/* Table for copying and zeroing */
/* Copy table:
  - Table entries count
    - entry one ram start
    - entry one rom start
    - entry one rom end
    ...
    - entry n ram start
    - entry n rom start
    - entry n rom end
  Zero Table:
    - Table entries count
      - entry one ram start
      - entry one ram end
*/
.section ".init_table", "a"
  .long 4
  .long __RAM_CACHEABLE_START
  .long __ROM_CACHEABLE_START
  .long __ROM_CACHEABLE_END
  .long __RAM_NO_CACHEABLE_START
  .long __ROM_NO_CACHEABLE_START
  .long __ROM_NO_CACHEABLE_END
  .long __RAM_SHAREABLE_START
  .long __ROM_SHAREABLE_START
  .long __ROM_SHAREABLE_END
  .long __RAM_INTERRUPT_START
  .long __ROM_INTERRUPT_START
  .long __ROM_INTERRUPT_END  
.section ".zero_table", "a"
  .long 3
  .long __BSS_SRAM_SH_START
  .long __BSS_SRAM_SH_END
  .long __BSS_SRAM_NC_START
  .long __BSS_SRAM_NC_END
  .long __BSS_SRAM_START
  .long __BSS_SRAM_END

.globl RESET_CATCH_CORE
.globl _core_loop
.section ".core_loop","ax"
.thumb

_core_loop:
    nop
    nop
    nop
    nop
    b _core_loop

.section ".boot_header","ax"
  .long SBAF_BOOT_MARKER /* IVT marker */
  .long (CM7_0_ENABLE << CM7_0_ENABLE_SHIFT) | (CM7_1_ENABLE << CM7_1_ENABLE_SHIFT) /* Boot configuration word */
  .long 0 /* Reserved */
  .long CM7_0_VTOR_ADDR /* CM7_0 Start address */
  .long 0 /* Reserved */
  .long CM7_1_VTOR_ADDR /* CM7_1 Start address */
  .long 0 /* Reserved */
  .long 0 /* Reserved */
  .long XRDC_CONFIG_ADDR /* XRDC configuration pointer */
  .long LF_CONFIG_ADDR /* Lifecycle configuration pointer */
  .long 0 /* Reserved */

.globl VTABLE
.section ".startup","ax"
.thumb
/************************************************************************/
/* Autosar synopsis of startup code (See MCU Specification):            */
/*                                                                      */
/*   Before the MCU driver can be initialized, a basic initialization   */
/*   of the MCU has to be executed. This MCU specific initialization is */
/*   typically executed in a start-up code. The start-up code of the    */
/*   MCU shall be executed after power up and any kind of micro-        */
/*   controller reset. It shall perform very basic and microcontroller  */
/*   specific start-up initialization and shall be kept short, because  */
/*   the MCU clock and PLL is not yet initialized. The start-up code    */
/*   shall cover MCU specific initialization, which is not part of      */
/*   other MCU services or other MCAL drivers. The following steps      */
/*   summarizes basic functionality which shall be included in the      */
/*   start-up code. They are listed for guidance, because some          */
/*   functionality might not be supported. No code will be found in     */
/*   case.                                                              */
/************************************************************************/
.set VTOR_REG, 0xE000ED08
.thumb 
.thumb_func
.globl Reset_Handler
.globl _start
_start:
Reset_Handler:
/*****************************************************/
/* Skip normal entry point as nothing is initialized */
/*****************************************************/
 cpsid i
 mov   r0, #0
 mov   r1, #0
 mov   r2, #0
 mov   r3, #0
 mov   r4, #0
 mov   r5, #0
 mov   r6, #0
 mov   r7, #0

#ifndef NO_MSCM_CLOCK_INIT
InitMSCMClock:
  /* If the MSCM clock is enabled, skip this sequence */
  ldr r0, =MCME_PRTN1_COFB0_STAT
  ldr r1, [r0]
  ldr r2, =MCME_MSCM_REQ
  and r1, r1, r2
  cmp r1, 0
  bne SetVTOR

  /* Enable clock in PRTN1 */
  ldr r0, =MCME_PRTN1_COFB0_CLKEN
  ldr r1, [r0]
  ldr r2, =MCME_MSCM_REQ
  orr r1, r2
  str r1, [r0]

  /* Set PUPD field */
  ldr r0, =MCME_PRTN1_PUPD
  ldr r1, [r0]
  ldr r2, =1
  orr r1, r2 
  str r1, [r0]

  /* Trigger update */
  ldr r0, =MCME_CTL_KEY
  ldr r1, =MCME_KEY
  str r1, [r0]
  ldr r1, =MCME_INV_KEY
  str r1, [r0]
#endif
/* Check MSCM clock in PRTN1 */
WaitForClock:
  ldr r0, =MCME_PRTN1_COFB0_STAT
  ldr r1, [r0]
  ldr r2, =MCME_MSCM_REQ
  and r1, r1, r2
  cmp r1, 0
  beq WaitForClock

/*******************************************************************/
/* NXP Guidance 1 - Init registers to avoid lock-step issues */
/* N/A                                                             */
/*******************************************************************/

/*******************************************************************/
/* NXP Guidance 2 - MMU Initialization for CPU               */
/*  TLB0 - PbridgeB                                                */
/*  TLB1 - Internal Flash                                          */
/*  TLB2 - External SRAM                                           */
/*  TLB3 - Internal SRAM                                           */
/*  TLB4 - PbridgeA                                                */
/*******************************************************************/

/******************************************************************/
/* Autosar Guidance 1 - The start-up code shall initialize the    */
/* base addresses for interrupt and trap vector tables. These base*/
/* addresses are provided as configuration parameters or          */
/* linker/locator setting.                                        */
/******************************************************************/

SetVTOR:
/* relocate vector table to RAM */
ldr  r0, =VTOR_REG
ldr  r1, =__RAM_INTERRUPT_START
str  r1,[r0]

/******************************************************************/
/* Autosar Guidance 2 - The start-up code shall initialize the    */
/* interrupt stack pointer, if an interrupt stack is              */
/* supported by the MCU. The interrupt stack pointer base address */
/* and the stack size are provided as configuration parameter or  */
/* linker/locator setting.                                        */
/*                                                                */
/******************************************************************/


/******************************************************************/
/* Autosar Guidance 3 - The start-up code shall initialize the    */
/* user stack pointer. The user stack pointer base address and    */
/* the stack size are provided as configuration parameter or      */
/* linker/locator setting.                                        */
/******************************************************************/
/*GetCoreID*/
ldr  r0, =0x40260004
ldr  r1,[r0]

ldr  r0, =MAIN_CORE
cmp  r1,r0
beq	 SetCore0Stack
b SetCore1Stack

SetCore0Stack:
  /* set up stack; r13 SP*/
  ldr  r0, =__Stack_start_c0
  msr MSP, r0
  b DisableSWT0
  
SetCore1Stack:
  /* set up stack; r13 SP*/
  ldr  r0, =__Stack_start_c1
  msr MSP, r0
#ifdef RAM_DATA_INIT_ON_ALL_CORES
  b RamInit
#else
  b DTCM_Init /* SWT1 clock is disabled at startup */
#endif

/******************************************************************/
/* Autosar Guidance 4 - If the MCU supports context save          */
/* operation, the start-up code shall initialize the memory which */
/* is used for context save operation. The maximum amount of      */
/* consecutive context save operations is provided as             */
/* configuration parameter or linker/locator setting.             */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 5 - The start-up code shall ensure that the   */
/* MCU internal watchdog shall not be serviced until the watchdog */
/* is initialized from the MCAL watchdog driver. This can be      */
/* done for example by increasing the watchdog service time.      */
/*                                                                */
/******************************************************************/

/* Note from manual: For any operation to be performed on an SWT  */
/* instance, its respective core must be enabled.                 */
DisableSWT0:
  ldr  r0, =0x40270010
  ldr  r1, =0xC520
  str  r1, [r0]
  ldr  r1, =0xD928
  str  r1, [r0]
  ldr  r0, =0x40270000
  ldr  r1, =0xFF000040
  str  r1, [r0]
  b    RamInit
  
DisableSWT1:
  ldr  r0, =0x4046C010
  ldr  r1, =0xC520
  str  r1, [r0]
  ldr  r1, =0xD928
  str  r1, [r0]
  ldr  r0, =0x4046C000
  ldr  r1, =0xFF000040
  str  r1, [r0]
  b    RamInit

/******************************************************************/
/* Autosar Guidance 13 - The start-up code shall initialize a     */
/* minimum amount of RAM in order to allow proper execution of    */
/* the MCU driver services and the caller of these services.      */
/******************************************************************/
RamInit:
    /* Initialize SRAM ECC */
    ldr  r0, =__RAM_INIT
    cmp  r0, 0
    /* Skip if __SRAM_INIT is not set */
    beq SRAM_LOOP_END
    ldr r1, =__INT_SRAM_START
    ldr r2, =__INT_SRAM_END
    
    subs    r2, r1
    subs    r2, #1
    ble SRAM_LOOP_END

    movs    r0, 0
    movs    r3, 0
SRAM_LOOP:
    stm r1!, {r0,r3}
    subs r2, 8
    bge SRAM_LOOP
SRAM_LOOP_END:

DTCM_Init:
    /* Initialize DTCM ECC */
    ldr  r0, =__DTCM_INIT
    cmp  r0, 0
    /* Skip if __DTCM_INIT is not set */
    beq DTCM_LOOP_END
    /* Enable TCM */
    LDR r1, =CM7_DTCMCR
    LDR r0, [r1]
    LDR r2, =0x1
    ORR r0, r2
    STR r0, [r1]

    ldr r1, =__INT_DTCM_START
    ldr r2, =__INT_DTCM_END
    
    subs    r2, r1
    subs    r2, #1
    ble DTCM_LOOP_END

    movs    r0, 0
    movs    r3, 0
DTCM_LOOP:
    stm r1!, {r0,r3}
    subs r2, #8
    bge DTCM_LOOP
DTCM_LOOP_END:

ITCM_Init:
    /* Initialize ITCM ECC */
    ldr  r0, =__ITCM_INIT
    cmp  r0, 0
    /* Skip if __TCM_INIT is not set */
    beq ITCM_LOOP_END

    /* Enable TCM */
    LDR r1, =CM7_ITCMCR
    LDR r0, [r1]
    LDR r2, =0x1
    ORR r0, r2
    STR r0, [r1]

    ldr r1, =__INT_ITCM_START
    ldr r2, =__INT_ITCM_END
    
    subs    r2, r1
    subs    r2, #1
    ble ITCM_LOOP_END

    movs    r0, 0
    movs    r3, 0
ITCM_LOOP:
    stm r1!, {r0,r3}
    subs r2, #8
    bge ITCM_LOOP
ITCM_LOOP_END:

DebuggerHeldCoreLoop:
  ldr  r0, =RESET_CATCH_CORE
  ldr  r0, [r0]
  ldr  r1, =0x5A5A5A5A
  cmp  r0, r1
  beq	DebuggerHeldCoreLoop

/************************/
/* Erase ".bss Section" */
/************************/
_DATA_INIT:
#ifndef RAM_DATA_INIT_ON_ALL_CORES
    /* If this is the primary core, initialize data and bss */
    ldr  r0, =0x40260004
    ldr  r1,[r0]

    ldr  r0, =MAIN_CORE
    cmp  r1,r0
    beq	 _INIT_DATA_BSS
    b    __SYSTEM_INIT
#endif

_INIT_DATA_BSS:
  bl init_data_bss


/******************************************************************/
/* Autosar Guidance 6 - If the MCU supports cache memory for data */
/* and/or code, it shall be initialized and enabled in the        */
/* start-up code.                                                 */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 7 - The start-up code shall initialize MCU    */
/* specific features of internal memory like memory protection.   */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 8 - If external memory is used, the memory    */
/* shall be initialized in the start-up code. The start-up code   */
/* shall be prepared to support different memory configurations   */
/* depending on code location. Different configuration options    */
/* shall be taken into account for code execution from            */
/* external/internal memory.                                      */
/* N/A - external memory is not used                              */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 9 - The settings of the different memories    */
/* shall be provided to the start-up code as configuration        */
/* parameters.                                                    */
/* N/A - all memories are already configured                      */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 10 - In the start-up code a default           */
/* initialization of the MCU clock system shall be performed      */
/* including global clock prescalers.                             */
/******************************************************************/
__SYSTEM_INIT:
  bl SystemInit

/******************************************************************/
/* Autosar Guidance 5 - The start-up code shall ensure that the   */
/* MCU internal watchdog shall not be serviced until the watchdog */
/* is initialized from the MCAL watchdog driver. This can be      */
/* done for example by increasing the watchdog service time.      */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 11 - The start-up code shall enable           */
/* protection mechanisms for special function registers(SFR's),   */
/* if supported by the MCU.                                       */
/* N/A - will be handled by Autosar OS                            */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 12 - The start-up code shall initialize all   */
/* necessary write once registers or registers common to several  */
/* drivers where one write, rather than repeated writes, to the   */
/* register is required or highly desirable.                      */
/******************************************************************/

/*********************************/
/* Set the small ro data pointer */
/*********************************/


/*********************************/
/* Set the small rw data pointer */
/*********************************/

/******************************************************************/
/* Call Main Routine                                              */
/******************************************************************/
_MAIN:
  cpsie i
  bl startup_go_to_user_mode
  bl main

/******************************************************************/
/* Init runtime check data space                                  */
/******************************************************************/
.globl MCAL_LTB_TRACE_OFF
 MCAL_LTB_TRACE_OFF:
    nop

#ifdef CCOV_ENABLE
    /* code coverage is requested */
    bl ccov_main
#endif

    /*BKPT #1 - removed to avoid debug fault being escalated to hardfault when debugger is not attached or on VDK*/ /* last instruction for the debugger to dump results data */
.globl _end_of_eunit_test
_end_of_eunit_test:
    b .

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
.globl startup_getControlRegisterValue
startup_getControlRegisterValue:
mrs r0, CONTROL
bx r14

.globl startup_getAipsRegisterValue
startup_getAipsRegisterValue:
mrs r0, IPSR
bx r14
#endif

.align 4
.ltorg
