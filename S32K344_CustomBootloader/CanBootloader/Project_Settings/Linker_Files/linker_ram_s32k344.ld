/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 4.0.0
*   Build Version        : S32K3_RTD_4_0_0_P19_D2403_ASR_REL_4_7_REV_0000_20240315
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/*
* Target device: This linker is demo and it is using for device S32K344 only. It is not part of the production code deliverables.
* Target core: ARM cortex M7
* Linker need to align with MPU default setup in system.c
*/

/*
* GCC Linker Command File:
* 0x00000000    0x0000FFFF  65536   ITCM
* 0x20000000    0x2001FFFF  131072  DTCM
* 0x20400000    0x20427FFF  163840  SRAM_0
* 0x20428000    0x20443FFF  114688  SRAM_1  Actually only initialize 112 kB instead of 160 kB in RM, 48kB is blocked by fimrware
*/
HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x00002000;

ENTRY(Reset_Handler)

MEMORY
{
    int_itcm                : ORIGIN = 0x00000000, LENGTH = 0x00010000    /* 64KB */
    int_dtcm                : ORIGIN = 0x20000000, LENGTH = 0x0001F000    /* 124KB */
    int_stack_dtcm          : ORIGIN = 0x2001F000, LENGTH = 0x00001000    /* 4KB */
    int_sram                : ORIGIN = 0x20400000, LENGTH = 0x00030000    /* 192KB */
    int_sram_no_cacheable   : ORIGIN = 0x20430000, LENGTH = 0x0000FF00    /* 64KB, needs to include int_sram_results  */
    int_sram_results        : ORIGIN = 0x2043FF00, LENGTH = 0x00000100
    int_sram_shareable      : ORIGIN = 0x20440000, LENGTH = 0x00004000    /* 16KB */
    ram_rsvd2               : ORIGIN = 0x20444000, LENGTH = 0             /* End of SRAM */
}

SECTIONS
{
    .sram :
    {
        . = ALIGN(4);
        KEEP(*(.core_loop))
        . = ALIGN(4);
        *(.startup)
        . = ALIGN(4);
        *(.systeminit)
        . = ALIGN(4);
        *(.text.startup)
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
        *(.mcal_text)
        . = ALIGN(4);
        KEEP(*(.init))
        . = ALIGN(4);
        KEEP(*(.fini))
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        *(.mcal_const_cfg)
        . = ALIGN(4);
        *(.mcal_const)
        . = ALIGN(4);
        __init_table = .;
        KEEP(*(.init_table))
        . = ALIGN(4);
        __zero_table = .;
        KEEP(*(.zero_table))
        . = ALIGN(4);
        *(.acmcu_code_rom)
        . = ALIGN(4);
        *(.ramcode)
        . = ALIGN(4);
        *(.data)
        *(.data*)
        . = ALIGN(4);
        *(.mcal_data)
        . = ALIGN(16);
        __sram_bss_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(16);
        *(.mcal_bss)
        . = ALIGN(4);
        __sram_bss_end = .;
    } > int_sram

    /* heap section */
    .heap (NOLOAD):
    {
        . += ALIGN(4);
        _end = .;
        end = .;
        _heap_start = .;
        . += HEAP_SIZE;
        _heap_end = .;
    } > int_sram

    .acfls_code_rom :
    {
        __acfls_code_rom_start = .;
        . = ALIGN(0x4);
        *(.acfls_code_rom)
        __acfls_code_rom_end = .;
    } > int_sram

    .acfls_code_ram :
    {
        __acfls_code_ram_start = .;
        . += (__acfls_code_rom_end - __acfls_code_rom_start );
        __acfls_code_ram_end = .;
    } > int_sram

    .acmem_43_infls_code_rom :
    {
        __acmem_43_infls_code_rom_start = .;
        . = ALIGN(0x4);
        *(.acmem_43_infls_code_rom)
        __acmem_43_infls_code_rom_end = .;
    } > int_sram

    .acmem_43_infls_code_ram :
    {
        __acmem_43_infls_code_ram_start = .;
        . += (__acmem_43_infls_code_rom_end - __acmem_43_infls_code_rom_start );
        __acmem_43_infls_code_ram_end = .;
    } > int_sram

    . = ALIGN(4);
    __init_dtcm_data_start = .;

    .non_cacheable :
    {
        . = ALIGN(2048);
        __interrupts_init_start = .;
        KEEP(*(.intc_vector))
        . = ALIGN(4);
        __interrupts_init_end = .;
        . = ALIGN(16);
        __non_cacheable_bss_start = .;
        *(.mcal_bss_no_cacheable)
        . = ALIGN(4);
        __non_cacheable_bss_end = .;
        . = ALIGN(4);
        *(.mcal_data_no_cacheable)
        . = ALIGN(4);
        *(.mcal_const_no_cacheable)
        HSE_LOOP_ADDR = .;
        LONG(0x0);
    } > int_sram_no_cacheable

    .int_vector :
    {
        . = ALIGN(2048);
        __interrupts_ram_start = .;
        . += __interrupts_init_end - __interrupts_init_start;
        . = ALIGN(4);
        __interrupts_ram_end = .;
    } > int_dtcm

    .data_tcm_data : AT(__init_dtcm_data_start)
    {
        . = ALIGN(4);
        __dtcm_data_start__ = .;
        *(.dtcm_data*)
        . = ALIGN(4);
        __dtcm_data_end__ = .;
    } > int_dtcm

    __init_dtcm_data_end = __init_dtcm_data_start + (__dtcm_data_end__ - __dtcm_data_start__);

    .bss_tcm_data (NOLOAD) :
    {
        . = ALIGN(4);
        __dtcm_bss_start__ = .;
        *(.dtcm_bss*)
        . = ALIGN(4);
        __dtcm_bss_end__ = .;
    } > int_dtcm

    __init_itcm_code_start = __init_dtcm_data_end;

   .itcm_text : AT(__init_itcm_code_start)
    {
        . = ALIGN(4);
        __itcm_start__ = .;
        *(.itcm_text*)
        . = ALIGN(4);
        __itcm_end__ = .;
    } > int_itcm

    __init_itcm_code_end = __init_itcm_code_start + (__itcm_end__ - __itcm_start__);

    .int_results (NOLOAD):
    {
        . = ALIGN(4);
        KEEP(*(.int_results))
        . += 0x100;
    } > int_sram_results

    .shareable_ram :
    {
        . = ALIGN(16);
        __shareable_bss_start = .;
        KEEP(*(.mcal_shared_bss))
        . = ALIGN(4);
        __shareable_bss_end = .;
        . = ALIGN(16);
        KEEP(*(.mcal_shared_data))
    } > int_sram_shareable

    __Stack_dtcm_end        = ORIGIN(int_stack_dtcm);
    __Stack_dtcm_start      = ORIGIN(int_stack_dtcm) + LENGTH(int_stack_dtcm);

    __INT_SRAM_START         = ORIGIN(int_sram);
    __INT_SRAM_END           = ORIGIN(ram_rsvd2);

    __INT_ITCM_START         = ORIGIN(int_itcm);
    __INT_ITCM_END           = ORIGIN(int_itcm) + LENGTH(int_itcm);

    __INT_DTCM_START         = ORIGIN(int_dtcm);
    __INT_DTCM_END           = ORIGIN(int_dtcm) + LENGTH(int_dtcm) + LENGTH(int_stack_dtcm);

    __RAM_SHAREABLE_START    = ORIGIN(int_sram_shareable);
    __RAM_SHAREABLE_SIZE     = 0xE;  /* 16 kbyte in power of 2 */
    __ROM_SHAREABLE_START    = 0;
    __ROM_SHAREABLE_END      = 0;
    __RAM_NO_CACHEABLE_START = ORIGIN(int_sram_no_cacheable);
    __RAM_NO_CACHEABLE_SIZE  = 0x10;  /* 64kbyte in power of 2 */
    __ROM_NO_CACHEABLE_START = 0;
    __ROM_NO_CACHEABLE_END   = 0;
    __RAM_CACHEABLE_START    = ORIGIN(int_sram);
    __RAM_CACHEABLE_SIZE     = 0x12;  /* 256kbyte in power of 2 */
    __ROM_CACHEABLE_START    = 0;
    __ROM_CACHEABLE_END      = 0;
    __ROM_CODE_START         = 0x00400000;
    __ROM_DATA_START         = 0x10000000;

    __BSS_SRAM_START         = __sram_bss_start;
    __BSS_SRAM_END           = __sram_bss_end;
    __BSS_SRAM_SIZE          = __sram_bss_end - __sram_bss_start;

    __BSS_SRAM_NC_START      = __non_cacheable_bss_start;
    __BSS_SRAM_NC_SIZE       = __non_cacheable_bss_end - __non_cacheable_bss_start;
    __BSS_SRAM_NC_END        = __non_cacheable_bss_end;

    __BSS_SRAM_SH_START      = __shareable_bss_start;
    __BSS_SRAM_SH_SIZE       = __shareable_bss_end - __shareable_bss_start;
    __BSS_SRAM_SH_END        = __shareable_bss_end;

    __RAM_INTERRUPT_START    = __interrupts_ram_start;
    __INIT_INTERRUPT_START   = __interrupts_init_start;
    __INIT_INTERRUPT_END     = __interrupts_init_end;

    __RAM_ITCM_START         = __itcm_start__;
    __ROM_ITCM_START         = __init_itcm_code_start;
    __ROM_ITCM_END           = __init_itcm_code_end;

    __RAM_DTCM_DATA_START    = __dtcm_data_start__;
    __ROM_DTCM_DATA_START    = __init_dtcm_data_start;
    __ROM_DTCM_END           = __init_dtcm_data_end;

    __INIT_TABLE             = __init_table;
    __ZERO_TABLE             = __zero_table;

    __RAM_INIT               = 0;
    __ITCM_INIT              = 1;
    __DTCM_INIT              = 1;
   /* Discard boot header in RAM */
   /DISCARD/ : { *(.boot_header) }
    /* Fls module access code support */
    Fls_ACEraseRomStart         = __acfls_code_rom_start;
    Fls_ACEraseRomEnd           = __acfls_code_rom_end;
    Fls_ACEraseSize             = ((__acfls_code_rom_end - __acfls_code_rom_start)+3) / 4; /* Copy 4 bytes at a time*/

    Fls_ACWriteRomStart         = __acfls_code_rom_start;
    Fls_ACWriteRomEnd           = __acfls_code_rom_end;
    Fls_ACWriteSize             = ((__acfls_code_rom_end - __acfls_code_rom_start)+3) / 4; /* Copy 4 bytes at a time*/

    _ERASE_FUNC_ADDRESS_        = __acfls_code_ram_start;
    _WRITE_FUNC_ADDRESS_        = __acfls_code_ram_start;

    Mem_43_INFLS_ACEraseRomStart         = __acmem_43_infls_code_rom_start;
    Mem_43_INFLS_ACEraseRomEnd           = __acmem_43_infls_code_rom_end;
    Mem_43_INFLS_ACEraseSize             = ((__acmem_43_infls_code_rom_end - __acmem_43_infls_code_rom_start)+3) / 4; /* Copy 4 bytes at a time*/

    Mem_43_INFLS_ACWriteRomStart         = __acmem_43_infls_code_rom_start;
    Mem_43_INFLS_ACWriteRomEnd           = __acmem_43_infls_code_rom_end;
    Mem_43_INFLS_ACWriteSize             = ((__acmem_43_infls_code_rom_end - __acmem_43_infls_code_rom_start)+3) / 4; /* Copy 4 bytes at a time*/

    _MEM_43_INFLS_ERASE_FUNC_ADDRESS_    = __acmem_43_infls_code_ram_start;
    _MEM_43_INFLS_WRITE_FUNC_ADDRESS_    = __acmem_43_infls_code_ram_start;

    __ENTRY_VTABLE           = __INIT_INTERRUPT_START;
    __CORE0_VTOR             = __INIT_INTERRUPT_START;
    __CORE1_VTOR             = __INIT_INTERRUPT_START;
    __CORE2_VTOR             = __INIT_INTERRUPT_START;

    __INDEX_COPY_CORE2       = 3;    /* This symbol is used to initialize data of ITCM/DTCM for CORE2 */

}
