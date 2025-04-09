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
/**
*   @file       Clock_Ip_Specific.c
*   @version    2.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Ip Driver
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


#include "Clock_Ip_Private.h"

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
    #include "RegLockMacros.h"
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_DATA_VENDOR_ID_C                      43
#define CLOCK_IP_DATA_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_DATA_AR_RELEASE_MINOR_VERSION_C       4
#define CLOCK_IP_DATA_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_DATA_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_DATA_SW_MINOR_VERSION_C               0
#define CLOCK_IP_DATA_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Data.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_DATA_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Data.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Data.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_DATA_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_DATA_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_DATA_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Data.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Data.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_DATA_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_DATA_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_DATA_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Data.c and Clock_Ip_Private.h are different"
#endif

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if Clock_Ip_Data.c file and RegLockMacros.h file are of the same Autosar version */
    #if ((CLOCK_IP_DATA_AR_RELEASE_MAJOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
        (CLOCK_IP_DATA_AR_RELEASE_MINOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Clock_Ip_Data.c and RegLockMacros.h are different"
    #endif
    #endif
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

#if defined(CLOCK_IP_DERIVATIVE_001)

#define CLOCK_IP_NO_CALLBACK                   0U
#define CLOCK_IP_SWMUX_DIV                     1U
#define CLOCK_IP_FAST_XOSC_CMU                 1U
#define CLOCK_IP_FIRCOSC                       1U
#define CLOCK_IP_PLL_MOD                       1U
#define CLOCK_IP_GATE                          1U
#define CLOCK_IP_HWMUX_DIV                     2U
#define CLOCK_IP_SIRCOSC                       2U
#define CLOCK_IP_SLOW_XOSC                     2U
#define CLOCK_IP_PLL_POSTDIV                   3U
#define CLOCK_IP_HWMUX_PCFS                    3U
#define CLOCK_IP_PCFS_PLL_OUT                  4U
#define CLOCK_IP_RTC_SEL                       4U
#define CLOCK_IP_PLL_OUT                       5U
#define CLOCK_IP_DIV_TRIGGER_CMU               6U
#define CLOCK_IP_DIV_TRIGGER                   7U
#define CLOCK_IP_FIRC_POSTDIV                  8U

#define CLOCK_IP_SCS_EXTENSION             0U
#define CLOCK_IP_CORE_EXTENSION            1U
#define CLOCK_IP_AIPS_PLAT_EXTENSION       2U
#define CLOCK_IP_AIPS_SLOW_EXTENSION       3U
#define CLOCK_IP_HSE_EXTENSION             4U
#define CLOCK_IP_DCM_EXTENSION             5U
#define CLOCK_IP_RUN_EXTENSION             6U
#define CLOCK_IP_CLKOUT_STANDBY_EXTENSION  7U
#define CLOCK_IP_FLEXCANA_EXTENSION        8U
#define CLOCK_IP_FLEXCANB_EXTENSION        9U
#define CLOCK_IP_STMA_EXTENSION            10U
#define CLOCK_IP_TRACE_EXTENSION           11U

#define CLOCK_IP_FXOSC_INSTANCE            0U
#define CLOCK_IP_SXOSC_INSTANCE            1U

#define CLOCK_IP_CGM0_INSTANCE             0U

#define CLOCK_IP_CMU_FC_0_INSTANCE         0U
#define CLOCK_IP_CMU_FC_3_INSTANCE         3U
#define CLOCK_IP_CMU_FC_4_INSTANCE         4U
#define CLOCK_IP_CMU_FC_5_INSTANCE         5U

#define CLOCK_IP_DIV_0_INDEX               0U
#define CLOCK_IP_DIV_1_INDEX               1U
#define CLOCK_IP_DIV_2_INDEX               2U
#define CLOCK_IP_DIV_3_INDEX               3U
#define CLOCK_IP_DIV_4_INDEX               4U
#define CLOCK_IP_DIV_5_INDEX               5U

#define CLOCK_IP_PCFS_7_INDEX              7U

#define CLOCK_IP_PRT0_COL1_REQ40_INDEX      0U
#define CLOCK_IP_PRT0_COL1_REQ41_INDEX      1U
#define CLOCK_IP_PRT0_COL1_REQ33_INDEX      2U
#define CLOCK_IP_PRT1_COL2_REQ92_INDEX      3U
#define CLOCK_IP_PRT1_COL2_REQ93_INDEX      4U
#define CLOCK_IP_PRT1_COL3_REQ96_INDEX      5U
#define CLOCK_IP_PRT1_COL1_REQ32_INDEX      6U
#define CLOCK_IP_PRT1_COL1_REQ33_INDEX      7U
#define CLOCK_IP_PRT1_COL0_REQ3_INDEX      8U
#define CLOCK_IP_PRT1_COL0_REQ4_INDEX      9U
#define CLOCK_IP_PRT1_COL0_REQ5_INDEX      10U
#define CLOCK_IP_PRT1_COL0_REQ6_INDEX      11U
#define CLOCK_IP_PRT1_COL0_REQ7_INDEX      12U
#define CLOCK_IP_PRT1_COL0_REQ8_INDEX      13U
#define CLOCK_IP_PRT1_COL0_REQ9_INDEX      14U
#define CLOCK_IP_PRT1_COL0_REQ10_INDEX      15U
#define CLOCK_IP_PRT1_COL0_REQ11_INDEX      16U
#define CLOCK_IP_PRT1_COL0_REQ12_INDEX      17U
#define CLOCK_IP_PRT1_COL0_REQ13_INDEX      18U
#define CLOCK_IP_PRT1_COL0_REQ14_INDEX      19U
#define CLOCK_IP_PRT1_COL0_REQ15_INDEX      20U
#define CLOCK_IP_PRT1_COL0_REQ22_INDEX      21U
#define CLOCK_IP_PRT0_COL1_REQ34_INDEX      22U
#define CLOCK_IP_PRT0_COL1_REQ35_INDEX      23U
#define CLOCK_IP_PRT1_COL0_REQ23_INDEX      24U
#define CLOCK_IP_PRT1_COL2_REQ65_INDEX      25U
#define CLOCK_IP_PRT1_COL2_REQ66_INDEX      26U
#define CLOCK_IP_PRT1_COL2_REQ67_INDEX      27U
#define CLOCK_IP_PRT1_COL2_REQ68_INDEX      28U
#define CLOCK_IP_PRT1_COL2_REQ69_INDEX      29U
#define CLOCK_IP_PRT1_COL2_REQ70_INDEX      30U
#define CLOCK_IP_PRT1_COL2_REQ73_INDEX      31U
#define CLOCK_IP_PRT0_COL1_REQ48_INDEX      32U
#define CLOCK_IP_PRT1_COL0_REQ31_INDEX      33U
#define CLOCK_IP_PRT0_COL1_REQ38_INDEX      34U
#define CLOCK_IP_PRT0_COL1_REQ39_INDEX      35U
#define CLOCK_IP_PRT1_COL2_REQ84_INDEX      36U
#define CLOCK_IP_PRT1_COL2_REQ85_INDEX      37U
#define CLOCK_IP_PRT1_COL2_REQ86_INDEX      38U
#define CLOCK_IP_PRT1_COL2_REQ87_INDEX      39U
#define CLOCK_IP_PRT1_COL2_REQ88_INDEX      40U
#define CLOCK_IP_PRT1_COL2_REQ89_INDEX      41U
#define CLOCK_IP_PRT1_COL2_REQ74_INDEX      42U
#define CLOCK_IP_PRT1_COL2_REQ75_INDEX      43U
#define CLOCK_IP_PRT1_COL2_REQ76_INDEX      44U
#define CLOCK_IP_PRT1_COL2_REQ77_INDEX      45U
#define CLOCK_IP_PRT1_COL2_REQ78_INDEX      46U
#define CLOCK_IP_PRT1_COL2_REQ79_INDEX      47U
#define CLOCK_IP_PRT1_COL2_REQ80_INDEX      48U
#define CLOCK_IP_PRT1_COL2_REQ81_INDEX      49U
#define CLOCK_IP_PRT1_COL0_REQ24_INDEX      50U
#define CLOCK_IP_PRT0_COL1_REQ44_INDEX      51U
#define CLOCK_IP_PRT0_COL1_REQ45_INDEX      52U
#define CLOCK_IP_PRT1_COL1_REQ34_INDEX      53U
#define CLOCK_IP_PRT1_COL1_REQ42_INDEX      54U
#define CLOCK_IP_PRT1_COL0_REQ29_INDEX      55U
#define CLOCK_IP_PRT1_COL0_REQ28_INDEX      56U
#define CLOCK_IP_PRT1_COL2_REQ95_INDEX      57U
#define CLOCK_IP_PRT0_COL1_REQ32_INDEX      58U
#define CLOCK_IP_PRT1_COL1_REQ49_INDEX      59U
#define CLOCK_IP_PRT1_COL1_REQ45_INDEX      60U


#define CLOCK_IP_PARTITION_0_INDEX         0U
#define CLOCK_IP_PARTITION_1_INDEX         1U
#define CLOCK_IP_COLLECTION_0_INDEX        0U
#define CLOCK_IP_COLLECTION_1_INDEX        1U
#define CLOCK_IP_COLLECTION_2_INDEX        2U
#define CLOCK_IP_COLLECTION_3_INDEX        3U

#define CLOCK_IP_SEL_0_INDEX      0U
#define CLOCK_IP_SEL_1_INDEX      1U
#define CLOCK_IP_SEL_3_INDEX      2U
#define CLOCK_IP_SEL_4_INDEX      3U
#define CLOCK_IP_SEL_5_INDEX      4U
#define CLOCK_IP_SEL_6_INDEX      5U
#define CLOCK_IP_SEL_11_INDEX     6U

#elif defined(CLOCK_IP_DERIVATIVE_002)

#define CLOCK_IP_NO_CALLBACK                   0U
#define CLOCK_IP_SWMUX_DIV                     1U
#define CLOCK_IP_FAST_XOSC_CMU                 1U
#define CLOCK_IP_FIRCOSC                       1U
#define CLOCK_IP_PLL_MOD                       1U
#define CLOCK_IP_GATE                          1U
#define CLOCK_IP_HWMUX_DIV                     2U
#define CLOCK_IP_SIRCOSC                       2U
#define CLOCK_IP_SLOW_XOSC                     2U
#define CLOCK_IP_PLL_POSTDIV                   3U
#define CLOCK_IP_HWMUX_PCFS                    3U
#define CLOCK_IP_PCFS_PLL_OUT                  4U
#define CLOCK_IP_RTC_SEL                       4U
#define CLOCK_IP_PLL_OUT                       5U
#define CLOCK_IP_DIV_TRIGGER_CMU               6U
#define CLOCK_IP_DIV_TRIGGER                   7U
#define CLOCK_IP_FIRC_POSTDIV                  8U

#define CLOCK_IP_SCS_EXTENSION             0U
#define CLOCK_IP_CORE_EXTENSION            1U
#define CLOCK_IP_AIPS_PLAT_EXTENSION       2U
#define CLOCK_IP_AIPS_SLOW_EXTENSION       3U
#define CLOCK_IP_HSE_EXTENSION             4U
#define CLOCK_IP_DCM_EXTENSION             5U
#define CLOCK_IP_LBIST_EXTENSION           6U
#define CLOCK_IP_QSPI_MEM_EXTENSION        7U
#define CLOCK_IP_RUN_EXTENSION             8U
#define CLOCK_IP_CLKOUT_STANDBY_EXTENSION  9U
#define CLOCK_IP_EMAC_RX_EXTENSION         10U
#define CLOCK_IP_EMAC_TS_EXTENSION         11U
#define CLOCK_IP_EMAC_TX_EXTENSION         12U
#define CLOCK_IP_FLEXCANA_EXTENSION        13U
#define CLOCK_IP_FLEXCANB_EXTENSION        14U
#define CLOCK_IP_QSPI_SFCK_EXTENSION       15U
#define CLOCK_IP_STMA_EXTENSION            16U
#define CLOCK_IP_TRACE_EXTENSION           17U

#define CLOCK_IP_FXOSC_INSTANCE            0U
#define CLOCK_IP_SXOSC_INSTANCE            1U

#define CLOCK_IP_CGM0_INSTANCE             0U

#define CLOCK_IP_CMU_FC_0_INSTANCE         0U
#define CLOCK_IP_CMU_FC_3_INSTANCE         3U
#define CLOCK_IP_CMU_FC_4_INSTANCE         4U
#define CLOCK_IP_CMU_FC_5_INSTANCE         5U

#define CLOCK_IP_DIV_0_INDEX               0U
#define CLOCK_IP_DIV_1_INDEX               1U
#define CLOCK_IP_DIV_2_INDEX               2U
#define CLOCK_IP_DIV_3_INDEX               3U
#define CLOCK_IP_DIV_4_INDEX               4U
#define CLOCK_IP_DIV_5_INDEX               5U
#define CLOCK_IP_DIV_6_INDEX               6U

#define CLOCK_IP_PCFS_7_INDEX              7U

#define CLOCK_IP_PRT0_COL1_REQ40_INDEX      0U
#define CLOCK_IP_PRT0_COL1_REQ41_INDEX      1U
#define CLOCK_IP_PRT0_COL1_REQ42_INDEX      2U
#define CLOCK_IP_PRT0_COL1_REQ33_INDEX      3U
#define CLOCK_IP_PRT1_COL2_REQ92_INDEX      4U
#define CLOCK_IP_PRT1_COL2_REQ93_INDEX      5U
#define CLOCK_IP_PRT2_COL1_REQ58_INDEX      6U
#define CLOCK_IP_PRT1_COL3_REQ96_INDEX      7U
#define CLOCK_IP_PRT1_COL1_REQ32_INDEX      8U
#define CLOCK_IP_PRT1_COL1_REQ33_INDEX      9U
#define CLOCK_IP_PRT1_COL0_REQ3_INDEX      10U
#define CLOCK_IP_PRT1_COL0_REQ4_INDEX      11U
#define CLOCK_IP_PRT1_COL0_REQ5_INDEX      12U
#define CLOCK_IP_PRT1_COL0_REQ6_INDEX      13U
#define CLOCK_IP_PRT1_COL0_REQ7_INDEX      14U
#define CLOCK_IP_PRT1_COL0_REQ8_INDEX      15U
#define CLOCK_IP_PRT1_COL0_REQ9_INDEX      16U
#define CLOCK_IP_PRT1_COL0_REQ10_INDEX      17U
#define CLOCK_IP_PRT1_COL0_REQ11_INDEX      18U
#define CLOCK_IP_PRT1_COL0_REQ12_INDEX      19U
#define CLOCK_IP_PRT1_COL0_REQ13_INDEX      20U
#define CLOCK_IP_PRT1_COL0_REQ14_INDEX      21U
#define CLOCK_IP_PRT1_COL0_REQ15_INDEX      22U
#define CLOCK_IP_PRT2_COL0_REQ4_INDEX      23U
#define CLOCK_IP_PRT2_COL0_REQ5_INDEX      24U
#define CLOCK_IP_PRT2_COL0_REQ6_INDEX      25U
#define CLOCK_IP_PRT2_COL0_REQ7_INDEX      26U
#define CLOCK_IP_PRT2_COL0_REQ8_INDEX      27U
#define CLOCK_IP_PRT2_COL0_REQ9_INDEX      28U
#define CLOCK_IP_PRT2_COL0_REQ10_INDEX      29U
#define CLOCK_IP_PRT2_COL0_REQ11_INDEX      30U
#define CLOCK_IP_PRT2_COL0_REQ12_INDEX      31U
#define CLOCK_IP_PRT2_COL0_REQ13_INDEX      32U
#define CLOCK_IP_PRT2_COL0_REQ14_INDEX      33U
#define CLOCK_IP_PRT2_COL0_REQ15_INDEX      34U
#define CLOCK_IP_PRT2_COL0_REQ16_INDEX      35U
#define CLOCK_IP_PRT2_COL0_REQ17_INDEX      36U
#define CLOCK_IP_PRT2_COL0_REQ18_INDEX      37U
#define CLOCK_IP_PRT2_COL0_REQ19_INDEX      38U
#define CLOCK_IP_PRT2_COL0_REQ20_INDEX      39U
#define CLOCK_IP_PRT2_COL0_REQ21_INDEX      40U
#define CLOCK_IP_PRT2_COL0_REQ22_INDEX      41U
#define CLOCK_IP_PRT2_COL0_REQ23_INDEX      42U
#define CLOCK_IP_PRT1_COL0_REQ22_INDEX      43U
#define CLOCK_IP_PRT2_COL1_REQ32_INDEX      44U
#define CLOCK_IP_PRT0_COL1_REQ34_INDEX      45U
#define CLOCK_IP_PRT0_COL1_REQ35_INDEX      46U
#define CLOCK_IP_PRT0_COL1_REQ36_INDEX      47U
#define CLOCK_IP_PRT1_COL0_REQ23_INDEX      48U
#define CLOCK_IP_PRT1_COL2_REQ65_INDEX      49U
#define CLOCK_IP_PRT1_COL2_REQ66_INDEX      50U
#define CLOCK_IP_PRT1_COL2_REQ67_INDEX      51U
#define CLOCK_IP_PRT1_COL2_REQ68_INDEX      52U
#define CLOCK_IP_PRT1_COL2_REQ69_INDEX      53U
#define CLOCK_IP_PRT1_COL2_REQ70_INDEX      54U
#define CLOCK_IP_PRT1_COL2_REQ73_INDEX      55U
#define CLOCK_IP_PRT1_COL0_REQ31_INDEX      56U
#define CLOCK_IP_PRT0_COL1_REQ38_INDEX      57U
#define CLOCK_IP_PRT0_COL1_REQ39_INDEX      58U
#define CLOCK_IP_PRT1_COL2_REQ84_INDEX      59U
#define CLOCK_IP_PRT1_COL2_REQ85_INDEX      60U
#define CLOCK_IP_PRT1_COL2_REQ86_INDEX      61U
#define CLOCK_IP_PRT1_COL2_REQ87_INDEX      62U
#define CLOCK_IP_PRT1_COL2_REQ88_INDEX      63U
#define CLOCK_IP_PRT1_COL2_REQ89_INDEX      64U
#define CLOCK_IP_PRT2_COL1_REQ47_INDEX      65U
#define CLOCK_IP_PRT2_COL1_REQ48_INDEX      66U
#define CLOCK_IP_PRT1_COL2_REQ74_INDEX      67U
#define CLOCK_IP_PRT1_COL2_REQ75_INDEX      68U
#define CLOCK_IP_PRT1_COL2_REQ76_INDEX      69U
#define CLOCK_IP_PRT1_COL2_REQ77_INDEX      70U
#define CLOCK_IP_PRT1_COL2_REQ78_INDEX      71U
#define CLOCK_IP_PRT1_COL2_REQ79_INDEX      72U
#define CLOCK_IP_PRT1_COL2_REQ80_INDEX      73U
#define CLOCK_IP_PRT1_COL2_REQ81_INDEX      74U
#define CLOCK_IP_PRT2_COL1_REQ35_INDEX      75U
#define CLOCK_IP_PRT2_COL1_REQ36_INDEX      76U
#define CLOCK_IP_PRT2_COL1_REQ37_INDEX      77U
#define CLOCK_IP_PRT2_COL1_REQ38_INDEX      78U
#define CLOCK_IP_PRT2_COL1_REQ39_INDEX      79U
#define CLOCK_IP_PRT2_COL1_REQ40_INDEX      80U
#define CLOCK_IP_PRT2_COL1_REQ41_INDEX      81U
#define CLOCK_IP_PRT2_COL1_REQ42_INDEX      82U
#define CLOCK_IP_PRT1_COL0_REQ24_INDEX      83U
#define CLOCK_IP_PRT0_COL1_REQ44_INDEX      84U
#define CLOCK_IP_PRT0_COL1_REQ45_INDEX      85U
#define CLOCK_IP_PRT1_COL1_REQ63_INDEX      86U
#define CLOCK_IP_PRT2_COL1_REQ51_INDEX      87U
#define CLOCK_IP_PRT1_COL1_REQ34_INDEX      88U
#define CLOCK_IP_PRT1_COL2_REQ91_INDEX      89U
#define CLOCK_IP_PRT2_COL1_REQ55_INDEX      90U
#define CLOCK_IP_PRT2_COL0_REQ24_INDEX      91U
#define CLOCK_IP_PRT1_COL1_REQ42_INDEX      92U
#define CLOCK_IP_PRT1_COL0_REQ29_INDEX      93U
#define CLOCK_IP_PRT1_COL0_REQ28_INDEX      94U
#define CLOCK_IP_PRT2_COL1_REQ62_INDEX      95U
#define CLOCK_IP_PRT1_COL2_REQ95_INDEX      96U
#define CLOCK_IP_PRT0_COL1_REQ32_INDEX      97U
#define CLOCK_IP_PRT1_COL1_REQ49_INDEX      98U
#define CLOCK_IP_PRT1_COL1_REQ45_INDEX      99U


#define CLOCK_IP_PARTITION_0_INDEX         0U
#define CLOCK_IP_PARTITION_1_INDEX         1U
#define CLOCK_IP_PARTITION_2_INDEX         2U
#define CLOCK_IP_COLLECTION_0_INDEX        0U
#define CLOCK_IP_COLLECTION_1_INDEX        1U
#define CLOCK_IP_COLLECTION_2_INDEX        2U
#define CLOCK_IP_COLLECTION_3_INDEX        3U

#define CLOCK_IP_SEL_0_INDEX      0U
#define CLOCK_IP_SEL_1_INDEX      1U
#define CLOCK_IP_SEL_2_INDEX      2U
#define CLOCK_IP_SEL_3_INDEX      3U
#define CLOCK_IP_SEL_4_INDEX      4U
#define CLOCK_IP_SEL_5_INDEX      5U
#define CLOCK_IP_SEL_6_INDEX      6U
#define CLOCK_IP_SEL_7_INDEX      7U
#define CLOCK_IP_SEL_8_INDEX      8U
#define CLOCK_IP_SEL_9_INDEX      9U
#define CLOCK_IP_SEL_10_INDEX     10U
#define CLOCK_IP_SEL_11_INDEX     11U

#elif defined(CLOCK_IP_DERIVATIVE_003)

#define CLOCK_IP_NO_CALLBACK                   0U
#define CLOCK_IP_SWMUX_DIV                     1U
#define CLOCK_IP_FAST_XOSC_CMU                 1U
#define CLOCK_IP_FIRCOSC                       1U
#define CLOCK_IP_PLL_MOD                       1U
#define CLOCK_IP_GATE                          1U
#define CLOCK_IP_HWMUX_DIV                     2U
#define CLOCK_IP_SIRCOSC                       2U
#define CLOCK_IP_SLOW_XOSC                     2U
#define CLOCK_IP_PLL_POSTDIV                   3U
#define CLOCK_IP_HWMUX_PCFS                    3U
#define CLOCK_IP_PCFS_PLL_OUT                  4U
#define CLOCK_IP_RTC_SEL                       4U
#define CLOCK_IP_PLL_OUT                       5U
#define CLOCK_IP_DIV_TRIGGER_CMU               6U
#define CLOCK_IP_DIV_TRIGGER                   7U
#define CLOCK_IP_FIRC_POSTDIV                  8U

#define CLOCK_IP_SCS_EXTENSION             0U
#define CLOCK_IP_CORE_EXTENSION            1U
#define CLOCK_IP_AIPS_PLAT_EXTENSION       2U
#define CLOCK_IP_AIPS_SLOW_EXTENSION       3U
#define CLOCK_IP_HSE_EXTENSION             4U
#define CLOCK_IP_DCM_EXTENSION             5U
#define CLOCK_IP_LBIST_EXTENSION           6U
#define CLOCK_IP_QSPI_MEM_EXTENSION        7U
#define CLOCK_IP_RUN_EXTENSION             8U
#define CLOCK_IP_CLKOUT_STANDBY_EXTENSION  9U
#define CLOCK_IP_EMAC_RX_EXTENSION         10U
#define CLOCK_IP_EMAC_TS_EXTENSION         11U
#define CLOCK_IP_EMAC_TX_EXTENSION         12U
#define CLOCK_IP_FLEXCANA_EXTENSION        13U
#define CLOCK_IP_FLEXCANB_EXTENSION        14U
#define CLOCK_IP_QSPI_SFCK_EXTENSION       15U
#define CLOCK_IP_STMA_EXTENSION            16U
#define CLOCK_IP_STMB_EXTENSION            17U
#define CLOCK_IP_TRACE_EXTENSION           18U

#define CLOCK_IP_FXOSC_INSTANCE            0U
#define CLOCK_IP_SXOSC_INSTANCE            1U

#define CLOCK_IP_CGM0_INSTANCE             0U

#define CLOCK_IP_CMU_FC_0_INSTANCE         0U
#define CLOCK_IP_CMU_FC_3_INSTANCE         3U
#define CLOCK_IP_CMU_FC_4_INSTANCE         4U
#define CLOCK_IP_CMU_FC_5_INSTANCE         5U

#define CLOCK_IP_DIV_0_INDEX               0U
#define CLOCK_IP_DIV_1_INDEX               1U
#define CLOCK_IP_DIV_2_INDEX               2U
#define CLOCK_IP_DIV_3_INDEX               3U
#define CLOCK_IP_DIV_4_INDEX               4U
#define CLOCK_IP_DIV_5_INDEX               5U
#define CLOCK_IP_DIV_6_INDEX               6U

#define CLOCK_IP_PCFS_7_INDEX              7U

#define CLOCK_IP_PRT0_COL1_REQ40_INDEX      0U
#define CLOCK_IP_PRT0_COL1_REQ41_INDEX      1U
#define CLOCK_IP_PRT0_COL1_REQ42_INDEX      2U
#define CLOCK_IP_PRT0_COL1_REQ33_INDEX      3U
#define CLOCK_IP_PRT1_COL2_REQ92_INDEX      4U
#define CLOCK_IP_PRT1_COL2_REQ93_INDEX      5U
#define CLOCK_IP_PRT2_COL1_REQ58_INDEX      6U
#define CLOCK_IP_PRT1_COL3_REQ96_INDEX      7U
#define CLOCK_IP_PRT1_COL1_REQ32_INDEX      8U
#define CLOCK_IP_PRT1_COL1_REQ33_INDEX      9U
#define CLOCK_IP_PRT1_COL0_REQ3_INDEX      10U
#define CLOCK_IP_PRT1_COL0_REQ4_INDEX      11U
#define CLOCK_IP_PRT1_COL0_REQ5_INDEX      12U
#define CLOCK_IP_PRT1_COL0_REQ6_INDEX      13U
#define CLOCK_IP_PRT1_COL0_REQ7_INDEX      14U
#define CLOCK_IP_PRT1_COL0_REQ8_INDEX      15U
#define CLOCK_IP_PRT1_COL0_REQ9_INDEX      16U
#define CLOCK_IP_PRT1_COL0_REQ10_INDEX      17U
#define CLOCK_IP_PRT1_COL0_REQ11_INDEX      18U
#define CLOCK_IP_PRT1_COL0_REQ12_INDEX      19U
#define CLOCK_IP_PRT1_COL0_REQ13_INDEX      20U
#define CLOCK_IP_PRT1_COL0_REQ14_INDEX      21U
#define CLOCK_IP_PRT1_COL0_REQ15_INDEX      22U
#define CLOCK_IP_PRT2_COL0_REQ4_INDEX      23U
#define CLOCK_IP_PRT2_COL0_REQ5_INDEX      24U
#define CLOCK_IP_PRT2_COL0_REQ6_INDEX      25U
#define CLOCK_IP_PRT2_COL0_REQ7_INDEX      26U
#define CLOCK_IP_PRT2_COL0_REQ8_INDEX      27U
#define CLOCK_IP_PRT2_COL0_REQ9_INDEX      28U
#define CLOCK_IP_PRT2_COL0_REQ10_INDEX      29U
#define CLOCK_IP_PRT2_COL0_REQ11_INDEX      30U
#define CLOCK_IP_PRT2_COL0_REQ12_INDEX      31U
#define CLOCK_IP_PRT2_COL0_REQ13_INDEX      32U
#define CLOCK_IP_PRT2_COL0_REQ14_INDEX      33U
#define CLOCK_IP_PRT2_COL0_REQ15_INDEX      34U
#define CLOCK_IP_PRT2_COL0_REQ16_INDEX      35U
#define CLOCK_IP_PRT2_COL0_REQ17_INDEX      36U
#define CLOCK_IP_PRT2_COL0_REQ18_INDEX      37U
#define CLOCK_IP_PRT2_COL0_REQ19_INDEX      38U
#define CLOCK_IP_PRT2_COL0_REQ20_INDEX      39U
#define CLOCK_IP_PRT2_COL0_REQ21_INDEX      40U
#define CLOCK_IP_PRT2_COL0_REQ22_INDEX      41U
#define CLOCK_IP_PRT2_COL0_REQ23_INDEX      42U
#define CLOCK_IP_PRT1_COL0_REQ22_INDEX      43U
#define CLOCK_IP_PRT2_COL1_REQ32_INDEX      44U
#define CLOCK_IP_PRT0_COL1_REQ34_INDEX      45U
#define CLOCK_IP_PRT0_COL1_REQ35_INDEX      46U
#define CLOCK_IP_PRT0_COL1_REQ36_INDEX      47U
#define CLOCK_IP_PRT1_COL0_REQ23_INDEX      48U
#define CLOCK_IP_PRT1_COL2_REQ65_INDEX      49U
#define CLOCK_IP_PRT1_COL2_REQ66_INDEX      50U
#define CLOCK_IP_PRT1_COL2_REQ67_INDEX      51U
#define CLOCK_IP_PRT1_COL2_REQ68_INDEX      52U
#define CLOCK_IP_PRT1_COL2_REQ69_INDEX      53U
#define CLOCK_IP_PRT1_COL2_REQ70_INDEX      54U
#define CLOCK_IP_PRT1_COL2_REQ73_INDEX      55U
#define CLOCK_IP_PRT1_COL0_REQ31_INDEX      56U
#define CLOCK_IP_PRT0_COL1_REQ38_INDEX      57U
#define CLOCK_IP_PRT0_COL1_REQ39_INDEX      58U
#define CLOCK_IP_PRT1_COL2_REQ84_INDEX      59U
#define CLOCK_IP_PRT1_COL2_REQ85_INDEX      60U
#define CLOCK_IP_PRT1_COL2_REQ86_INDEX      61U
#define CLOCK_IP_PRT1_COL2_REQ87_INDEX      62U
#define CLOCK_IP_PRT1_COL2_REQ88_INDEX      63U
#define CLOCK_IP_PRT1_COL2_REQ89_INDEX      64U
#define CLOCK_IP_PRT2_COL1_REQ47_INDEX      65U
#define CLOCK_IP_PRT2_COL1_REQ48_INDEX      66U
#define CLOCK_IP_PRT1_COL2_REQ74_INDEX      67U
#define CLOCK_IP_PRT1_COL2_REQ75_INDEX      68U
#define CLOCK_IP_PRT1_COL2_REQ76_INDEX      69U
#define CLOCK_IP_PRT1_COL2_REQ77_INDEX      70U
#define CLOCK_IP_PRT1_COL2_REQ78_INDEX      71U
#define CLOCK_IP_PRT1_COL2_REQ79_INDEX      72U
#define CLOCK_IP_PRT1_COL2_REQ80_INDEX      73U
#define CLOCK_IP_PRT1_COL2_REQ81_INDEX      74U
#define CLOCK_IP_PRT2_COL1_REQ35_INDEX      75U
#define CLOCK_IP_PRT2_COL1_REQ36_INDEX      76U
#define CLOCK_IP_PRT2_COL1_REQ37_INDEX      77U
#define CLOCK_IP_PRT2_COL1_REQ38_INDEX      78U
#define CLOCK_IP_PRT2_COL1_REQ39_INDEX      79U
#define CLOCK_IP_PRT2_COL1_REQ40_INDEX      80U
#define CLOCK_IP_PRT2_COL1_REQ41_INDEX      81U
#define CLOCK_IP_PRT2_COL1_REQ42_INDEX      82U
#define CLOCK_IP_PRT1_COL0_REQ24_INDEX      83U
#define CLOCK_IP_PRT0_COL1_REQ46_INDEX      84U
#define CLOCK_IP_PRT0_COL1_REQ47_INDEX      85U
#define CLOCK_IP_PRT0_COL1_REQ44_INDEX      86U
#define CLOCK_IP_PRT0_COL1_REQ45_INDEX      87U
#define CLOCK_IP_PRT1_COL1_REQ63_INDEX      88U
#define CLOCK_IP_PRT2_COL1_REQ51_INDEX      89U
#define CLOCK_IP_PRT1_COL1_REQ34_INDEX      90U
#define CLOCK_IP_PRT1_COL2_REQ91_INDEX      91U
#define CLOCK_IP_PRT2_COL1_REQ55_INDEX      92U
#define CLOCK_IP_PRT2_COL0_REQ24_INDEX      93U
#define CLOCK_IP_PRT1_COL1_REQ42_INDEX      94U
#define CLOCK_IP_PRT1_COL0_REQ29_INDEX      95U
#define CLOCK_IP_PRT2_COL0_REQ29_INDEX      96U
#define CLOCK_IP_PRT1_COL0_REQ28_INDEX      97U
#define CLOCK_IP_PRT2_COL0_REQ27_INDEX      98U
#define CLOCK_IP_PRT2_COL1_REQ62_INDEX      99U
#define CLOCK_IP_PRT2_COL1_REQ63_INDEX      100U
#define CLOCK_IP_PRT1_COL2_REQ95_INDEX      101U
#define CLOCK_IP_PRT0_COL1_REQ32_INDEX      102U
#define CLOCK_IP_PRT1_COL1_REQ49_INDEX      103U
#define CLOCK_IP_PRT1_COL1_REQ45_INDEX      104U


#define CLOCK_IP_PARTITION_0_INDEX         0U
#define CLOCK_IP_PARTITION_1_INDEX         1U
#define CLOCK_IP_PARTITION_2_INDEX         2U
#define CLOCK_IP_COLLECTION_0_INDEX        0U
#define CLOCK_IP_COLLECTION_1_INDEX        1U
#define CLOCK_IP_COLLECTION_2_INDEX        2U
#define CLOCK_IP_COLLECTION_3_INDEX        3U

#define CLOCK_IP_SEL_0_INDEX      0U
#define CLOCK_IP_SEL_1_INDEX      1U
#define CLOCK_IP_SEL_2_INDEX      2U
#define CLOCK_IP_SEL_3_INDEX      3U
#define CLOCK_IP_SEL_4_INDEX      4U
#define CLOCK_IP_SEL_5_INDEX      5U
#define CLOCK_IP_SEL_6_INDEX      6U
#define CLOCK_IP_SEL_7_INDEX      7U
#define CLOCK_IP_SEL_8_INDEX      8U
#define CLOCK_IP_SEL_9_INDEX      9U
#define CLOCK_IP_SEL_10_INDEX     10U
#define CLOCK_IP_SEL_11_INDEX     11U

#elif defined(CLOCK_IP_DERIVATIVE_004)

#define CLOCK_IP_NO_CALLBACK                   0U
#define CLOCK_IP_SWMUX_DIV                     1U
#define CLOCK_IP_FAST_XOSC_CMU                 1U
#define CLOCK_IP_FIRCOSC                       1U
#define CLOCK_IP_PLL_MOD                       1U
#define CLOCK_IP_GATE                          1U
#define CLOCK_IP_HWMUX_DIV                     2U
#define CLOCK_IP_SIRCOSC                       2U
#define CLOCK_IP_SLOW_XOSC                     2U
#define CLOCK_IP_PLL_POSTDIV                   3U
#define CLOCK_IP_HWMUX_PCFS                    3U
#define CLOCK_IP_PCFS_PLL_OUT                  4U
#define CLOCK_IP_RTC_SEL                       4U
#define CLOCK_IP_PLL_OUT                       5U
#define CLOCK_IP_DIV_TRIGGER_CMU               6U
#define CLOCK_IP_DIV_TRIGGER                   7U
#define CLOCK_IP_FIRC_POSTDIV                  8U

#define CLOCK_IP_SCS_EXTENSION             0U
#define CLOCK_IP_CORE_EXTENSION            1U
#define CLOCK_IP_AIPS_PLAT_EXTENSION       2U
#define CLOCK_IP_AIPS_SLOW_EXTENSION       3U
#define CLOCK_IP_HSE_EXTENSION             4U
#define CLOCK_IP_DCM_EXTENSION             5U
#define CLOCK_IP_LBIST_EXTENSION           6U
#define CLOCK_IP_QSPI_MEM_EXTENSION        7U
#define CLOCK_IP_RUN_EXTENSION             8U
#define CLOCK_IP_CLKOUT_STANDBY_EXTENSION  9U
#define CLOCK_IP_EMAC_RX_EXTENSION         10U
#define CLOCK_IP_EMAC_TS_EXTENSION         11U
#define CLOCK_IP_EMAC_TX_EXTENSION         12U
#define CLOCK_IP_FLEXCANA_EXTENSION        13U
#define CLOCK_IP_FLEXCANB_EXTENSION        14U
#define CLOCK_IP_QSPI_SFCK_EXTENSION       15U
#define CLOCK_IP_STMA_EXTENSION            16U
#define CLOCK_IP_STMB_EXTENSION            17U
#define CLOCK_IP_TRACE_EXTENSION           18U

#define CLOCK_IP_FXOSC_INSTANCE            0U
#define CLOCK_IP_SXOSC_INSTANCE            1U

#define CLOCK_IP_CGM0_INSTANCE             0U

#define CLOCK_IP_CMU_FC_0_INSTANCE         0U
#define CLOCK_IP_CMU_FC_3_INSTANCE         3U
#define CLOCK_IP_CMU_FC_4_INSTANCE         4U
#define CLOCK_IP_CMU_FC_5_INSTANCE         5U

#define CLOCK_IP_DIV_0_INDEX               0U
#define CLOCK_IP_DIV_1_INDEX               1U
#define CLOCK_IP_DIV_2_INDEX               2U
#define CLOCK_IP_DIV_3_INDEX               3U
#define CLOCK_IP_DIV_4_INDEX               4U
#define CLOCK_IP_DIV_5_INDEX               5U
#define CLOCK_IP_DIV_6_INDEX               6U

#define CLOCK_IP_PCFS_7_INDEX              7U

#define CLOCK_IP_PRT0_COL1_REQ40_INDEX        0U
#define CLOCK_IP_PRT0_COL1_REQ41_INDEX        1U
#define CLOCK_IP_PRT0_COL1_REQ33_INDEX        2U
#define CLOCK_IP_PRT1_COL2_REQ92_INDEX        3U
#define CLOCK_IP_PRT1_COL2_REQ93_INDEX        4U
#define CLOCK_IP_PRT1_COL3_REQ96_INDEX        5U
#define CLOCK_IP_PRT1_COL1_REQ32_INDEX        6U
#define CLOCK_IP_PRT1_COL1_REQ33_INDEX        7U
#define CLOCK_IP_PRT1_COL0_REQ3_INDEX        8U
#define CLOCK_IP_PRT1_COL0_REQ4_INDEX        9U
#define CLOCK_IP_PRT1_COL0_REQ5_INDEX        10U
#define CLOCK_IP_PRT1_COL0_REQ6_INDEX        11U
#define CLOCK_IP_PRT1_COL0_REQ7_INDEX        12U
#define CLOCK_IP_PRT1_COL0_REQ8_INDEX        13U
#define CLOCK_IP_PRT1_COL0_REQ9_INDEX        14U
#define CLOCK_IP_PRT1_COL0_REQ10_INDEX        15U
#define CLOCK_IP_PRT1_COL0_REQ11_INDEX        16U
#define CLOCK_IP_PRT1_COL0_REQ12_INDEX        17U
#define CLOCK_IP_PRT1_COL0_REQ13_INDEX        18U
#define CLOCK_IP_PRT1_COL0_REQ14_INDEX        19U
#define CLOCK_IP_PRT1_COL0_REQ15_INDEX        20U
#define CLOCK_IP_PRT2_COL0_REQ4_INDEX        21U
#define CLOCK_IP_PRT2_COL0_REQ5_INDEX        22U
#define CLOCK_IP_PRT2_COL0_REQ6_INDEX        23U
#define CLOCK_IP_PRT2_COL0_REQ7_INDEX        24U
#define CLOCK_IP_PRT2_COL0_REQ8_INDEX        25U
#define CLOCK_IP_PRT2_COL0_REQ9_INDEX        26U
#define CLOCK_IP_PRT2_COL0_REQ10_INDEX        27U
#define CLOCK_IP_PRT2_COL0_REQ11_INDEX        28U
#define CLOCK_IP_PRT2_COL0_REQ12_INDEX        29U
#define CLOCK_IP_PRT2_COL0_REQ13_INDEX        30U
#define CLOCK_IP_PRT2_COL0_REQ14_INDEX        31U
#define CLOCK_IP_PRT2_COL0_REQ15_INDEX        32U
#define CLOCK_IP_PRT2_COL0_REQ16_INDEX        33U
#define CLOCK_IP_PRT2_COL0_REQ17_INDEX        34U
#define CLOCK_IP_PRT2_COL0_REQ18_INDEX        35U
#define CLOCK_IP_PRT2_COL0_REQ19_INDEX        36U
#define CLOCK_IP_PRT2_COL0_REQ20_INDEX        37U
#define CLOCK_IP_PRT2_COL0_REQ21_INDEX        38U
#define CLOCK_IP_PRT2_COL0_REQ22_INDEX        39U
#define CLOCK_IP_PRT2_COL0_REQ23_INDEX        40U
#define CLOCK_IP_PRT1_COL0_REQ22_INDEX        41U
#define CLOCK_IP_PRT2_COL1_REQ32_INDEX        42U
#define CLOCK_IP_PRT0_COL1_REQ34_INDEX        43U
#define CLOCK_IP_PRT0_COL1_REQ35_INDEX        44U
#define CLOCK_IP_PRT1_COL0_REQ23_INDEX        45U
#define CLOCK_IP_PRT1_COL2_REQ65_INDEX        46U
#define CLOCK_IP_PRT1_COL2_REQ66_INDEX        47U
#define CLOCK_IP_PRT1_COL2_REQ67_INDEX        48U
#define CLOCK_IP_PRT1_COL2_REQ68_INDEX        49U
#define CLOCK_IP_PRT1_COL2_REQ73_INDEX        50U
#define CLOCK_IP_PRT0_COL1_REQ48_INDEX        51U
#define CLOCK_IP_PRT1_COL0_REQ31_INDEX        52U
#define CLOCK_IP_PRT0_COL1_REQ38_INDEX        53U
#define CLOCK_IP_PRT0_COL1_REQ39_INDEX        54U
#define CLOCK_IP_PRT1_COL2_REQ84_INDEX        55U
#define CLOCK_IP_PRT1_COL2_REQ85_INDEX        56U
#define CLOCK_IP_PRT1_COL2_REQ86_INDEX        57U
#define CLOCK_IP_PRT1_COL2_REQ87_INDEX        58U
#define CLOCK_IP_PRT1_COL2_REQ88_INDEX        59U
#define CLOCK_IP_PRT1_COL2_REQ89_INDEX        60U
#define CLOCK_IP_PRT1_COL2_REQ74_INDEX        61U
#define CLOCK_IP_PRT1_COL2_REQ75_INDEX        62U
#define CLOCK_IP_PRT1_COL2_REQ76_INDEX        63U
#define CLOCK_IP_PRT1_COL2_REQ77_INDEX        64U
#define CLOCK_IP_PRT1_COL0_REQ24_INDEX        65U
#define CLOCK_IP_PRT0_COL1_REQ44_INDEX        66U
#define CLOCK_IP_PRT0_COL1_REQ45_INDEX        67U
#define CLOCK_IP_PRT1_COL1_REQ63_INDEX        68U
#define CLOCK_IP_PRT2_COL1_REQ51_INDEX        69U
#define CLOCK_IP_PRT1_COL1_REQ34_INDEX        70U
#define CLOCK_IP_PRT1_COL2_REQ91_INDEX        71U
#define CLOCK_IP_PRT2_COL1_REQ55_INDEX        72U
#define CLOCK_IP_PRT2_COL0_REQ24_INDEX        73U
#define CLOCK_IP_PRT1_COL1_REQ42_INDEX        74U
#define CLOCK_IP_PRT1_COL0_REQ29_INDEX        75U
#define CLOCK_IP_PRT2_COL0_REQ29_INDEX        76U
#define CLOCK_IP_PRT1_COL0_REQ28_INDEX        77U
#define CLOCK_IP_PRT2_COL1_REQ62_INDEX        78U
#define CLOCK_IP_PRT1_COL2_REQ95_INDEX        79U
#define CLOCK_IP_PRT0_COL1_REQ32_INDEX        80U
#define CLOCK_IP_PRT1_COL1_REQ49_INDEX        81U
#define CLOCK_IP_PRT1_COL1_REQ45_INDEX        82U



#define CLOCK_IP_PARTITION_0_INDEX         0U
#define CLOCK_IP_PARTITION_1_INDEX         1U
#define CLOCK_IP_PARTITION_2_INDEX         2U
#define CLOCK_IP_COLLECTION_0_INDEX        0U
#define CLOCK_IP_COLLECTION_1_INDEX        1U
#define CLOCK_IP_COLLECTION_2_INDEX        2U
#define CLOCK_IP_COLLECTION_3_INDEX        3U

#define CLOCK_IP_SEL_0_INDEX      0U
#define CLOCK_IP_SEL_1_INDEX      1U
#define CLOCK_IP_SEL_2_INDEX      2U
#define CLOCK_IP_SEL_3_INDEX      3U
#define CLOCK_IP_SEL_4_INDEX      4U
#define CLOCK_IP_SEL_5_INDEX      5U
#define CLOCK_IP_SEL_6_INDEX      6U
#define CLOCK_IP_SEL_7_INDEX      7U
#define CLOCK_IP_SEL_8_INDEX      8U
#define CLOCK_IP_SEL_9_INDEX      9U
#define CLOCK_IP_SEL_10_INDEX     10U
#define CLOCK_IP_SEL_11_INDEX     11U

#elif defined(CLOCK_IP_DERIVATIVE_005)

#define CLOCK_IP_NO_CALLBACK                   0U
#define CLOCK_IP_SWMUX_DIV                     1U
#define CLOCK_IP_FAST_XOSC_CMU                 1U
#define CLOCK_IP_FIRCOSC                       1U
#define CLOCK_IP_PLL_MOD                       1U
#define CLOCK_IP_GATE                          1U
#define CLOCK_IP_HWMUX_DIV                     2U
#define CLOCK_IP_SIRCOSC                       2U
#define CLOCK_IP_SLOW_XOSC                     2U
#define CLOCK_IP_PLL_POSTDIV                   3U
#define CLOCK_IP_HWMUX_PCFS                    3U
#define CLOCK_IP_PCFS_PLL_OUT                  4U
#define CLOCK_IP_RTC_SEL                       4U
#define CLOCK_IP_PLL_OUT                       5U
#define CLOCK_IP_DIV_TRIGGER_CMU               6U
#define CLOCK_IP_DIV_TRIGGER                   7U
#define CLOCK_IP_FIRC_POSTDIV                  8U

#define CLOCK_IP_SCS_EXTENSION             0U
#define CLOCK_IP_CORE_EXTENSION            1U
#define CLOCK_IP_AIPS_PLAT_EXTENSION       2U
#define CLOCK_IP_AIPS_SLOW_EXTENSION       3U
#define CLOCK_IP_HSE_EXTENSION             4U
#define CLOCK_IP_DCM_EXTENSION             5U
#define CLOCK_IP_LBIST_EXTENSION           6U
#define CLOCK_IP_QSPI_MEM_EXTENSION        7U
#define CLOCK_IP_RUN_EXTENSION             8U
#define CLOCK_IP_CLKOUT_STANDBY_EXTENSION  9U
#define CLOCK_IP_EMAC_RX_EXTENSION         10U
#define CLOCK_IP_EMAC_TS_EXTENSION         11U
#define CLOCK_IP_EMAC_TX_EXTENSION         12U
#define CLOCK_IP_FLEXCANA_EXTENSION        13U
#define CLOCK_IP_FLEXCANB_EXTENSION        14U
#define CLOCK_IP_QSPI_SFCK_EXTENSION       15U
#define CLOCK_IP_STMA_EXTENSION            16U
#define CLOCK_IP_STMB_EXTENSION            17U
#define CLOCK_IP_TRACE_EXTENSION           18U

#define CLOCK_IP_FXOSC_INSTANCE            0U
#define CLOCK_IP_SXOSC_INSTANCE            1U

#define CLOCK_IP_CGM0_INSTANCE             0U

#define CLOCK_IP_CMU_FC_0_INSTANCE         0U
#define CLOCK_IP_CMU_FC_3_INSTANCE         3U
#define CLOCK_IP_CMU_FC_4_INSTANCE         4U
#define CLOCK_IP_CMU_FC_5_INSTANCE         5U

#define CLOCK_IP_DIV_0_INDEX               0U
#define CLOCK_IP_DIV_1_INDEX               1U
#define CLOCK_IP_DIV_2_INDEX               2U
#define CLOCK_IP_DIV_3_INDEX               3U
#define CLOCK_IP_DIV_4_INDEX               4U
#define CLOCK_IP_DIV_5_INDEX               5U
#define CLOCK_IP_DIV_6_INDEX               6U

#define CLOCK_IP_PCFS_7_INDEX              7U

#define CLOCK_IP_PRT0_COL1_REQ40_INDEX      0U
#define CLOCK_IP_PRT0_COL1_REQ41_INDEX      1U
#define CLOCK_IP_PRT0_COL1_REQ42_INDEX      2U
#define CLOCK_IP_PRT0_COL1_REQ33_INDEX      3U
#define CLOCK_IP_PRT1_COL2_REQ92_INDEX      4U
#define CLOCK_IP_PRT1_COL2_REQ93_INDEX      5U
#define CLOCK_IP_PRT2_COL1_REQ58_INDEX      6U
#define CLOCK_IP_PRT1_COL3_REQ96_INDEX      7U
#define CLOCK_IP_PRT1_COL1_REQ32_INDEX      8U
#define CLOCK_IP_PRT1_COL1_REQ33_INDEX      9U
#define CLOCK_IP_PRT1_COL0_REQ3_INDEX      10U
#define CLOCK_IP_PRT1_COL0_REQ4_INDEX      11U
#define CLOCK_IP_PRT1_COL0_REQ5_INDEX      12U
#define CLOCK_IP_PRT1_COL0_REQ6_INDEX      13U
#define CLOCK_IP_PRT1_COL0_REQ7_INDEX      14U
#define CLOCK_IP_PRT1_COL0_REQ8_INDEX      15U
#define CLOCK_IP_PRT1_COL0_REQ9_INDEX      16U
#define CLOCK_IP_PRT1_COL0_REQ10_INDEX      17U
#define CLOCK_IP_PRT1_COL0_REQ11_INDEX      18U
#define CLOCK_IP_PRT1_COL0_REQ12_INDEX      19U
#define CLOCK_IP_PRT1_COL0_REQ13_INDEX      20U
#define CLOCK_IP_PRT1_COL0_REQ14_INDEX      21U
#define CLOCK_IP_PRT1_COL0_REQ15_INDEX      22U
#define CLOCK_IP_PRT2_COL0_REQ4_INDEX      23U
#define CLOCK_IP_PRT2_COL0_REQ5_INDEX      24U
#define CLOCK_IP_PRT2_COL0_REQ6_INDEX      25U
#define CLOCK_IP_PRT2_COL0_REQ7_INDEX      26U
#define CLOCK_IP_PRT2_COL0_REQ8_INDEX      27U
#define CLOCK_IP_PRT2_COL0_REQ9_INDEX      28U
#define CLOCK_IP_PRT2_COL0_REQ10_INDEX      29U
#define CLOCK_IP_PRT2_COL0_REQ11_INDEX      30U
#define CLOCK_IP_PRT2_COL0_REQ12_INDEX      31U
#define CLOCK_IP_PRT2_COL0_REQ13_INDEX      32U
#define CLOCK_IP_PRT2_COL0_REQ14_INDEX      33U
#define CLOCK_IP_PRT2_COL0_REQ15_INDEX      34U
#define CLOCK_IP_PRT2_COL0_REQ16_INDEX      35U
#define CLOCK_IP_PRT2_COL0_REQ17_INDEX      36U
#define CLOCK_IP_PRT2_COL0_REQ18_INDEX      37U
#define CLOCK_IP_PRT2_COL0_REQ19_INDEX      38U
#define CLOCK_IP_PRT2_COL0_REQ20_INDEX      39U
#define CLOCK_IP_PRT2_COL0_REQ21_INDEX      40U
#define CLOCK_IP_PRT2_COL0_REQ22_INDEX      41U
#define CLOCK_IP_PRT2_COL0_REQ23_INDEX      42U
#define CLOCK_IP_PRT1_COL0_REQ22_INDEX      43U
#define CLOCK_IP_PRT2_COL1_REQ32_INDEX      44U
#define CLOCK_IP_PRT0_COL1_REQ34_INDEX      45U
#define CLOCK_IP_PRT0_COL1_REQ35_INDEX      46U
#define CLOCK_IP_PRT0_COL1_REQ36_INDEX      47U
#define CLOCK_IP_PRT1_COL0_REQ23_INDEX      48U
#define CLOCK_IP_PRT1_COL2_REQ65_INDEX      49U
#define CLOCK_IP_PRT1_COL2_REQ66_INDEX      50U
#define CLOCK_IP_PRT1_COL2_REQ67_INDEX      51U
#define CLOCK_IP_PRT1_COL2_REQ68_INDEX      52U
#define CLOCK_IP_PRT1_COL2_REQ69_INDEX      53U
#define CLOCK_IP_PRT1_COL2_REQ70_INDEX      54U
#define CLOCK_IP_PRT1_COL2_REQ73_INDEX      55U
#define CLOCK_IP_PRT1_COL0_REQ31_INDEX      56U
#define CLOCK_IP_PRT0_COL1_REQ38_INDEX      57U
#define CLOCK_IP_PRT0_COL1_REQ39_INDEX      58U
#define CLOCK_IP_PRT1_COL2_REQ84_INDEX      59U
#define CLOCK_IP_PRT1_COL2_REQ85_INDEX      60U
#define CLOCK_IP_PRT1_COL2_REQ86_INDEX      61U
#define CLOCK_IP_PRT1_COL2_REQ87_INDEX      62U
#define CLOCK_IP_PRT1_COL2_REQ88_INDEX      63U
#define CLOCK_IP_PRT1_COL2_REQ89_INDEX      64U
#define CLOCK_IP_PRT2_COL1_REQ47_INDEX      65U
#define CLOCK_IP_PRT2_COL1_REQ48_INDEX      66U
#define CLOCK_IP_PRT1_COL2_REQ74_INDEX      67U
#define CLOCK_IP_PRT1_COL2_REQ75_INDEX      68U
#define CLOCK_IP_PRT1_COL2_REQ76_INDEX      69U
#define CLOCK_IP_PRT1_COL2_REQ77_INDEX      70U
#define CLOCK_IP_PRT1_COL2_REQ78_INDEX      71U
#define CLOCK_IP_PRT1_COL2_REQ79_INDEX      72U
#define CLOCK_IP_PRT1_COL2_REQ80_INDEX      73U
#define CLOCK_IP_PRT1_COL2_REQ81_INDEX      74U
#define CLOCK_IP_PRT2_COL1_REQ35_INDEX      75U
#define CLOCK_IP_PRT2_COL1_REQ36_INDEX      76U
#define CLOCK_IP_PRT2_COL1_REQ37_INDEX      77U
#define CLOCK_IP_PRT2_COL1_REQ38_INDEX      78U
#define CLOCK_IP_PRT2_COL1_REQ39_INDEX      79U
#define CLOCK_IP_PRT2_COL1_REQ40_INDEX      80U
#define CLOCK_IP_PRT2_COL1_REQ41_INDEX      81U
#define CLOCK_IP_PRT2_COL1_REQ42_INDEX      82U
#define CLOCK_IP_PRT1_COL0_REQ24_INDEX      83U
#define CLOCK_IP_PRT0_COL1_REQ44_INDEX      84U
#define CLOCK_IP_PRT0_COL1_REQ45_INDEX      85U
#define CLOCK_IP_PRT1_COL1_REQ63_INDEX      86U
#define CLOCK_IP_PRT2_COL1_REQ51_INDEX      87U
#define CLOCK_IP_PRT1_COL1_REQ34_INDEX      88U
#define CLOCK_IP_PRT1_COL2_REQ91_INDEX      89U
#define CLOCK_IP_PRT2_COL1_REQ55_INDEX      90U
#define CLOCK_IP_PRT2_COL0_REQ24_INDEX      91U
#define CLOCK_IP_PRT1_COL1_REQ42_INDEX      92U
#define CLOCK_IP_PRT1_COL0_REQ29_INDEX      93U
#define CLOCK_IP_PRT2_COL0_REQ29_INDEX      94U
#define CLOCK_IP_PRT1_COL0_REQ28_INDEX      95U
#define CLOCK_IP_PRT2_COL1_REQ62_INDEX      96U
#define CLOCK_IP_PRT1_COL2_REQ95_INDEX      97U
#define CLOCK_IP_PRT0_COL1_REQ32_INDEX      98U
#define CLOCK_IP_PRT1_COL1_REQ49_INDEX      99U
#define CLOCK_IP_PRT1_COL1_REQ45_INDEX      100U


#define CLOCK_IP_PARTITION_0_INDEX         0U
#define CLOCK_IP_PARTITION_1_INDEX         1U
#define CLOCK_IP_PARTITION_2_INDEX         2U
#define CLOCK_IP_COLLECTION_0_INDEX        0U
#define CLOCK_IP_COLLECTION_1_INDEX        1U
#define CLOCK_IP_COLLECTION_2_INDEX        2U
#define CLOCK_IP_COLLECTION_3_INDEX        3U

#define CLOCK_IP_SEL_0_INDEX      0U
#define CLOCK_IP_SEL_1_INDEX      1U
#define CLOCK_IP_SEL_2_INDEX      2U
#define CLOCK_IP_SEL_3_INDEX      3U
#define CLOCK_IP_SEL_4_INDEX      4U
#define CLOCK_IP_SEL_5_INDEX      5U
#define CLOCK_IP_SEL_6_INDEX      6U
#define CLOCK_IP_SEL_7_INDEX      7U
#define CLOCK_IP_SEL_8_INDEX      8U
#define CLOCK_IP_SEL_9_INDEX      9U
#define CLOCK_IP_SEL_10_INDEX     10U
#define CLOCK_IP_SEL_11_INDEX     11U

#elif defined(CLOCK_IP_DERIVATIVE_006)

#define CLOCK_IP_NO_CALLBACK                   0U
#define CLOCK_IP_SWMUX_DIV                     1U
#define CLOCK_IP_FAST_XOSC_CMU                 1U
#define CLOCK_IP_FIRCOSC                       1U
#define CLOCK_IP_PLL_MOD                       1U
#define CLOCK_IP_GATE                          1U
#define CLOCK_IP_HWMUX_DIV                     2U
#define CLOCK_IP_SIRCOSC                       2U
#define CLOCK_IP_SLOW_XOSC                     2U
#define CLOCK_IP_PLL_POSTDIV                   3U
#define CLOCK_IP_HWMUX_PCFS                    3U
#define CLOCK_IP_PCFS_PLL_OUT                  4U
#define CLOCK_IP_RTC_SEL                       4U
#define CLOCK_IP_PLL_OUT                       5U
#define CLOCK_IP_DIV_TRIGGER_CMU               6U
#define CLOCK_IP_DIV_TRIGGER                   7U
#define CLOCK_IP_FIRC_POSTDIV                  8U

#define CLOCK_IP_SCS_EXTENSION             0U
#define CLOCK_IP_CORE_EXTENSION            1U
#define CLOCK_IP_AIPS_PLAT_EXTENSION       2U
#define CLOCK_IP_AIPS_SLOW_EXTENSION       3U
#define CLOCK_IP_HSE_EXTENSION             4U
#define CLOCK_IP_DCM_EXTENSION             5U
#define CLOCK_IP_LBIST_EXTENSION           6U
#define CLOCK_IP_QSPI_MEM_EXTENSION        7U
#define CLOCK_IP_CM7_CORE_EXTENSION        8U
#define CLOCK_IP_RUN_EXTENSION             9U
#define CLOCK_IP_CLKOUT_STANDBY_EXTENSION  10U
#define CLOCK_IP_EMAC_RX_EXTENSION         11U
#define CLOCK_IP_EMAC_TS_EXTENSION         12U
#define CLOCK_IP_EMAC_TX_EXTENSION         13U
#define CLOCK_IP_EMAC_TX_RMII_EXTENSION    14U
#define CLOCK_IP_FLEXCANA_EXTENSION        15U
#define CLOCK_IP_FLEXCANB_EXTENSION        16U
#define CLOCK_IP_QSPI_2XSFIF_EXTENSION     17U
#define CLOCK_IP_QSPI_SFCK_EXTENSION       18U
#define CLOCK_IP_STMA_EXTENSION            19U
#define CLOCK_IP_STMB_EXTENSION            20U
#define CLOCK_IP_STMC_EXTENSION            21U
#define CLOCK_IP_TRACE_EXTENSION           22U
#define CLOCK_IP_LFAST_REF_EXTENSION       23U
#define CLOCK_IP_SWG_EXTENSION             24U

#define CLOCK_IP_FXOSC_INSTANCE            0U
#define CLOCK_IP_SXOSC_INSTANCE            1U

#define CLOCK_IP_CGM0_INSTANCE             0U

#define CLOCK_IP_CMU_FC_0_INSTANCE         0U
#define CLOCK_IP_CMU_FC_3_INSTANCE         3U
#define CLOCK_IP_CMU_FC_4_INSTANCE         4U
#define CLOCK_IP_CMU_FC_5_INSTANCE         5U
#define CLOCK_IP_CMU_FC_6_INSTANCE         6U

#define CLOCK_IP_DIV_0_INDEX               0U
#define CLOCK_IP_DIV_1_INDEX               1U
#define CLOCK_IP_DIV_2_INDEX               2U
#define CLOCK_IP_DIV_3_INDEX               3U
#define CLOCK_IP_DIV_4_INDEX               4U
#define CLOCK_IP_DIV_5_INDEX               5U
#define CLOCK_IP_DIV_6_INDEX               6U
#define CLOCK_IP_DIV_7_INDEX               7U

#define CLOCK_IP_PCFS_7_INDEX              7U

#define CLOCK_IP_PRT0_COL1_REQ40_INDEX        0U
#define CLOCK_IP_PRT0_COL1_REQ41_INDEX        1U
#define CLOCK_IP_PRT0_COL1_REQ42_INDEX        2U
#define CLOCK_IP_PRT3_COL1_REQ61_INDEX        3U
#define CLOCK_IP_PRT3_COL1_REQ62_INDEX        4U
#define CLOCK_IP_PRT3_COL1_REQ63_INDEX        5U
#define CLOCK_IP_PRT3_COL2_REQ64_INDEX        6U
#define CLOCK_IP_PRT0_COL1_REQ33_INDEX        7U
#define CLOCK_IP_PRT1_COL2_REQ92_INDEX        8U
#define CLOCK_IP_PRT1_COL2_REQ93_INDEX        9U
#define CLOCK_IP_PRT1_COL3_REQ96_INDEX        10U
#define CLOCK_IP_PRT1_COL1_REQ32_INDEX        11U
#define CLOCK_IP_PRT1_COL1_REQ33_INDEX        12U
#define CLOCK_IP_PRT1_COL0_REQ3_INDEX        13U
#define CLOCK_IP_PRT1_COL0_REQ4_INDEX        14U
#define CLOCK_IP_PRT1_COL0_REQ5_INDEX        15U
#define CLOCK_IP_PRT1_COL0_REQ6_INDEX        16U
#define CLOCK_IP_PRT1_COL0_REQ7_INDEX        17U
#define CLOCK_IP_PRT1_COL0_REQ8_INDEX        18U
#define CLOCK_IP_PRT1_COL0_REQ9_INDEX        19U
#define CLOCK_IP_PRT1_COL0_REQ10_INDEX        20U
#define CLOCK_IP_PRT1_COL0_REQ11_INDEX        21U
#define CLOCK_IP_PRT1_COL0_REQ12_INDEX        22U
#define CLOCK_IP_PRT1_COL0_REQ13_INDEX        23U
#define CLOCK_IP_PRT1_COL0_REQ14_INDEX        24U
#define CLOCK_IP_PRT1_COL0_REQ15_INDEX        25U
#define CLOCK_IP_PRT2_COL0_REQ4_INDEX        26U
#define CLOCK_IP_PRT2_COL0_REQ5_INDEX        27U
#define CLOCK_IP_PRT2_COL0_REQ6_INDEX        28U
#define CLOCK_IP_PRT2_COL0_REQ7_INDEX        29U
#define CLOCK_IP_PRT2_COL0_REQ8_INDEX        30U
#define CLOCK_IP_PRT2_COL0_REQ9_INDEX        31U
#define CLOCK_IP_PRT2_COL0_REQ10_INDEX        32U
#define CLOCK_IP_PRT2_COL0_REQ11_INDEX        33U
#define CLOCK_IP_PRT2_COL0_REQ12_INDEX        34U
#define CLOCK_IP_PRT2_COL0_REQ13_INDEX        35U
#define CLOCK_IP_PRT2_COL0_REQ14_INDEX        36U
#define CLOCK_IP_PRT2_COL0_REQ15_INDEX        37U
#define CLOCK_IP_PRT2_COL0_REQ16_INDEX        38U
#define CLOCK_IP_PRT2_COL0_REQ17_INDEX        39U
#define CLOCK_IP_PRT2_COL0_REQ18_INDEX        40U
#define CLOCK_IP_PRT2_COL0_REQ19_INDEX        41U
#define CLOCK_IP_PRT2_COL0_REQ20_INDEX        42U
#define CLOCK_IP_PRT2_COL0_REQ21_INDEX        43U
#define CLOCK_IP_PRT2_COL0_REQ22_INDEX        44U
#define CLOCK_IP_PRT2_COL0_REQ23_INDEX        45U
#define CLOCK_IP_PRT2_COL2_REQ67_INDEX        46U
#define CLOCK_IP_PRT2_COL2_REQ68_INDEX        47U
#define CLOCK_IP_PRT2_COL2_REQ69_INDEX      48U
#define CLOCK_IP_PRT2_COL1_REQ32_INDEX        49U
#define CLOCK_IP_PRT0_COL1_REQ34_INDEX        50U
#define CLOCK_IP_PRT1_COL0_REQ23_INDEX        51U
#define CLOCK_IP_PRT0_COL0_REQ3_INDEX        52U
#define CLOCK_IP_PRT1_COL2_REQ65_INDEX        53U
#define CLOCK_IP_PRT1_COL2_REQ66_INDEX        54U
#define CLOCK_IP_PRT1_COL2_REQ67_INDEX        55U
#define CLOCK_IP_PRT1_COL2_REQ68_INDEX        56U
#define CLOCK_IP_PRT1_COL2_REQ69_INDEX        57U
#define CLOCK_IP_PRT1_COL2_REQ70_INDEX        58U
#define CLOCK_IP_PRT1_COL2_REQ73_INDEX        59U
#define CLOCK_IP_PRT0_COL1_REQ48_INDEX        60U
#define CLOCK_IP_PRT0_COL1_REQ49_INDEX        61U
#define CLOCK_IP_PRT1_COL0_REQ31_INDEX        62U
#define CLOCK_IP_PRT0_COL1_REQ38_INDEX        63U
#define CLOCK_IP_PRT0_COL1_REQ39_INDEX        64U
#define CLOCK_IP_PRT1_COL2_REQ84_INDEX        65U
#define CLOCK_IP_PRT1_COL2_REQ85_INDEX        66U
#define CLOCK_IP_PRT1_COL2_REQ86_INDEX        67U
#define CLOCK_IP_PRT1_COL2_REQ87_INDEX        68U
#define CLOCK_IP_PRT1_COL2_REQ88_INDEX        69U
#define CLOCK_IP_PRT1_COL2_REQ89_INDEX        70U
#define CLOCK_IP_PRT2_COL1_REQ47_INDEX        71U
#define CLOCK_IP_PRT2_COL1_REQ48_INDEX        72U
#define CLOCK_IP_PRT1_COL2_REQ74_INDEX        73U
#define CLOCK_IP_PRT1_COL2_REQ75_INDEX        74U
#define CLOCK_IP_PRT1_COL2_REQ76_INDEX        75U
#define CLOCK_IP_PRT1_COL2_REQ77_INDEX        76U
#define CLOCK_IP_PRT1_COL0_REQ24_INDEX        77U
#define CLOCK_IP_PRT0_COL1_REQ44_INDEX        78U
#define CLOCK_IP_PRT0_COL1_REQ45_INDEX        79U
#define CLOCK_IP_PRT1_COL1_REQ63_INDEX        80U
#define CLOCK_IP_PRT2_COL1_REQ51_INDEX        81U
#define CLOCK_IP_PRT1_COL1_REQ34_INDEX        82U
#define CLOCK_IP_PRT2_COL0_REQ24_INDEX        83U
#define CLOCK_IP_PRT1_COL1_REQ42_INDEX        84U
#define CLOCK_IP_PRT1_COL0_REQ29_INDEX        85U
#define CLOCK_IP_PRT2_COL0_REQ29_INDEX        86U
#define CLOCK_IP_PRT2_COL0_REQ30_INDEX      87U
#define CLOCK_IP_PRT1_COL0_REQ28_INDEX        88U
#define CLOCK_IP_PRT2_COL1_REQ62_INDEX        89U
#define CLOCK_IP_PRT1_COL2_REQ95_INDEX        90U
#define CLOCK_IP_PRT0_COL1_REQ32_INDEX        91U
#define CLOCK_IP_PRT1_COL1_REQ45_INDEX        92U




#define CLOCK_IP_PARTITION_0_INDEX         0U
#define CLOCK_IP_PARTITION_1_INDEX         1U
#define CLOCK_IP_PARTITION_2_INDEX         2U
#define CLOCK_IP_PARTITION_3_INDEX         3U
#define CLOCK_IP_COLLECTION_0_INDEX        0U
#define CLOCK_IP_COLLECTION_1_INDEX        1U
#define CLOCK_IP_COLLECTION_2_INDEX        2U
#define CLOCK_IP_COLLECTION_3_INDEX        3U

#define CLOCK_IP_SEL_0_INDEX      0U
#define CLOCK_IP_SEL_1_INDEX      1U
#define CLOCK_IP_SEL_2_INDEX      2U
#define CLOCK_IP_SEL_3_INDEX      3U
#define CLOCK_IP_SEL_4_INDEX      4U
#define CLOCK_IP_SEL_5_INDEX      5U
#define CLOCK_IP_SEL_6_INDEX      6U
#define CLOCK_IP_SEL_7_INDEX      7U
#define CLOCK_IP_SEL_8_INDEX      8U
#define CLOCK_IP_SEL_9_INDEX      9U
#define CLOCK_IP_SEL_10_INDEX     10U
#define CLOCK_IP_SEL_11_INDEX     11U
#define CLOCK_IP_SEL_12_INDEX     12U
#define CLOCK_IP_SEL_13_INDEX     13U
#define CLOCK_IP_SEL_14_INDEX     14U
#define CLOCK_IP_SEL_15_INDEX     15U
#define CLOCK_IP_SEL_16_INDEX     16U


#elif defined(CLOCK_IP_DERIVATIVE_007)

#define CLOCK_IP_NO_CALLBACK                   0U
#define CLOCK_IP_SWMUX_DIV                     1U
#define CLOCK_IP_FAST_XOSC_CMU                 1U
#define CLOCK_IP_FIRCOSC                       1U
#define CLOCK_IP_PLL_MOD                       1U
#define CLOCK_IP_GATE                          1U
#define CLOCK_IP_HWMUX_DIV                     2U
#define CLOCK_IP_SIRCOSC                       2U
#define CLOCK_IP_SLOW_XOSC                     2U
#define CLOCK_IP_PLL_POSTDIV                   3U
#define CLOCK_IP_HWMUX_PCFS                    3U
#define CLOCK_IP_PCFS_PLL_OUT                  4U
#define CLOCK_IP_RTC_SEL                       4U
#define CLOCK_IP_PLL_OUT                       5U
#define CLOCK_IP_DIV_TRIGGER_CMU               6U
#define CLOCK_IP_DIV_TRIGGER                   7U
#define CLOCK_IP_FIRC_POSTDIV                  8U

#define CLOCK_IP_SCS_EXTENSION             0U
#define CLOCK_IP_CORE_EXTENSION            1U
#define CLOCK_IP_AIPS_PLAT_EXTENSION       2U
#define CLOCK_IP_AIPS_SLOW_EXTENSION       3U
#define CLOCK_IP_HSE_EXTENSION             4U
#define CLOCK_IP_DCM_EXTENSION             5U
#define CLOCK_IP_LBIST_EXTENSION           6U
#define CLOCK_IP_QSPI_MEM_EXTENSION        7U
#define CLOCK_IP_RUN_EXTENSION             8U
#define CLOCK_IP_CLKOUT_STANDBY_EXTENSION  9U
#define CLOCK_IP_EMAC_RX_EXTENSION         10U
#define CLOCK_IP_EMAC_TS_EXTENSION         11U
#define CLOCK_IP_EMAC_TX_EXTENSION         12U
#define CLOCK_IP_FLEXCANA_EXTENSION        13U
#define CLOCK_IP_FLEXCANB_EXTENSION        14U
#define CLOCK_IP_QSPI_SFCK_EXTENSION       15U
#define CLOCK_IP_STMA_EXTENSION            16U
#define CLOCK_IP_STMB_EXTENSION            17U
#define CLOCK_IP_TRACE_EXTENSION           18U

#define CLOCK_IP_FXOSC_INSTANCE            0U
#define CLOCK_IP_SXOSC_INSTANCE            1U

#define CLOCK_IP_CGM0_INSTANCE             0U

#define CLOCK_IP_CMU_FC_0_INSTANCE         0U
#define CLOCK_IP_CMU_FC_3_INSTANCE         3U
#define CLOCK_IP_CMU_FC_4_INSTANCE         4U
#define CLOCK_IP_CMU_FC_5_INSTANCE         5U

#define CLOCK_IP_DIV_0_INDEX               0U
#define CLOCK_IP_DIV_1_INDEX               1U
#define CLOCK_IP_DIV_2_INDEX               2U
#define CLOCK_IP_DIV_3_INDEX               3U
#define CLOCK_IP_DIV_4_INDEX               4U
#define CLOCK_IP_DIV_5_INDEX               5U
#define CLOCK_IP_DIV_6_INDEX               6U

#define CLOCK_IP_PCFS_7_INDEX              7U

#define CLOCK_IP_PRT0_COL1_REQ40_INDEX    0U
#define CLOCK_IP_PRT0_COL1_REQ41_INDEX    1U
#define CLOCK_IP_PRT0_COL1_REQ33_INDEX    2U
#define CLOCK_IP_PRT1_COL2_REQ92_INDEX    3U
#define CLOCK_IP_PRT1_COL2_REQ93_INDEX    4U
#define CLOCK_IP_PRT1_COL3_REQ96_INDEX    5U
#define CLOCK_IP_PRT1_COL1_REQ32_INDEX    6U
#define CLOCK_IP_PRT1_COL1_REQ33_INDEX    7U
#define CLOCK_IP_PRT1_COL0_REQ3_INDEX   8U
#define CLOCK_IP_PRT1_COL0_REQ4_INDEX   9U
#define CLOCK_IP_PRT1_COL0_REQ5_INDEX   10U
#define CLOCK_IP_PRT1_COL0_REQ6_INDEX   11U
#define CLOCK_IP_PRT1_COL0_REQ7_INDEX   12U
#define CLOCK_IP_PRT1_COL0_REQ8_INDEX   13U
#define CLOCK_IP_PRT1_COL0_REQ9_INDEX   14U
#define CLOCK_IP_PRT1_COL0_REQ10_INDEX    15U
#define CLOCK_IP_PRT1_COL0_REQ11_INDEX    16U
#define CLOCK_IP_PRT1_COL0_REQ12_INDEX    17U
#define CLOCK_IP_PRT1_COL0_REQ13_INDEX    18U
#define CLOCK_IP_PRT1_COL0_REQ14_INDEX    19U
#define CLOCK_IP_PRT1_COL0_REQ15_INDEX    20U
#define CLOCK_IP_PRT2_COL0_REQ4_INDEX   21U
#define CLOCK_IP_PRT2_COL0_REQ5_INDEX   22U
#define CLOCK_IP_PRT2_COL0_REQ6_INDEX   23U
#define CLOCK_IP_PRT2_COL0_REQ7_INDEX   24U
#define CLOCK_IP_PRT2_COL0_REQ8_INDEX   25U
#define CLOCK_IP_PRT2_COL0_REQ9_INDEX   26U
#define CLOCK_IP_PRT2_COL0_REQ10_INDEX    27U
#define CLOCK_IP_PRT2_COL0_REQ11_INDEX    28U
#define CLOCK_IP_PRT2_COL0_REQ12_INDEX    29U
#define CLOCK_IP_PRT2_COL0_REQ13_INDEX    30U
#define CLOCK_IP_PRT2_COL0_REQ14_INDEX    31U
#define CLOCK_IP_PRT2_COL0_REQ15_INDEX    32U
#define CLOCK_IP_PRT2_COL0_REQ16_INDEX    33U
#define CLOCK_IP_PRT2_COL0_REQ17_INDEX    34U
#define CLOCK_IP_PRT2_COL0_REQ18_INDEX    35U
#define CLOCK_IP_PRT2_COL0_REQ19_INDEX    36U
#define CLOCK_IP_PRT2_COL0_REQ20_INDEX    37U
#define CLOCK_IP_PRT2_COL0_REQ21_INDEX    38U
#define CLOCK_IP_PRT2_COL0_REQ22_INDEX    39U
#define CLOCK_IP_PRT2_COL0_REQ23_INDEX    40U
#define CLOCK_IP_PRT1_COL0_REQ22_INDEX    41U
#define CLOCK_IP_PRT2_COL1_REQ32_INDEX    42U
#define CLOCK_IP_PRT0_COL1_REQ34_INDEX    43U
#define CLOCK_IP_PRT0_COL1_REQ35_INDEX    44U
#define CLOCK_IP_PRT1_COL0_REQ23_INDEX    45U
#define CLOCK_IP_PRT1_COL2_REQ65_INDEX    46U
#define CLOCK_IP_PRT1_COL2_REQ66_INDEX    47U
#define CLOCK_IP_PRT1_COL2_REQ67_INDEX    48U
#define CLOCK_IP_PRT1_COL2_REQ68_INDEX    49U
#define CLOCK_IP_PRT1_COL2_REQ73_INDEX    50U
#define CLOCK_IP_PRT0_COL1_REQ48_INDEX    51U
#define CLOCK_IP_PRT1_COL0_REQ31_INDEX    52U
#define CLOCK_IP_PRT0_COL1_REQ38_INDEX    53U
#define CLOCK_IP_PRT0_COL1_REQ39_INDEX    54U
#define CLOCK_IP_PRT1_COL2_REQ84_INDEX    55U
#define CLOCK_IP_PRT1_COL2_REQ85_INDEX    56U
#define CLOCK_IP_PRT1_COL2_REQ86_INDEX    57U
#define CLOCK_IP_PRT1_COL2_REQ87_INDEX    58U
#define CLOCK_IP_PRT1_COL2_REQ88_INDEX    59U
#define CLOCK_IP_PRT1_COL2_REQ89_INDEX    60U
#define CLOCK_IP_PRT1_COL2_REQ74_INDEX    61U
#define CLOCK_IP_PRT1_COL2_REQ75_INDEX    62U
#define CLOCK_IP_PRT1_COL2_REQ76_INDEX    63U
#define CLOCK_IP_PRT1_COL2_REQ77_INDEX    64U
#define CLOCK_IP_PRT1_COL0_REQ24_INDEX    65U
#define CLOCK_IP_PRT0_COL1_REQ44_INDEX    66U
#define CLOCK_IP_PRT0_COL1_REQ45_INDEX    67U
#define CLOCK_IP_PRT1_COL1_REQ63_INDEX    68U
#define CLOCK_IP_PRT2_COL1_REQ51_INDEX    69U
#define CLOCK_IP_PRT1_COL1_REQ34_INDEX    70U
#define CLOCK_IP_PRT1_COL2_REQ91_INDEX    71U
#define CLOCK_IP_PRT2_COL1_REQ55_INDEX    72U
#define CLOCK_IP_PRT2_COL0_REQ24_INDEX    73U
#define CLOCK_IP_PRT1_COL1_REQ42_INDEX    74U
#define CLOCK_IP_PRT1_COL0_REQ29_INDEX    75U
#define CLOCK_IP_PRT2_COL0_REQ29_INDEX    76U
#define CLOCK_IP_PRT1_COL0_REQ28_INDEX    77U
#define CLOCK_IP_PRT2_COL0_REQ27_INDEX    78U
#define CLOCK_IP_PRT2_COL1_REQ62_INDEX    79U
#define CLOCK_IP_PRT1_COL2_REQ95_INDEX    80U
#define CLOCK_IP_PRT0_COL1_REQ32_INDEX    81U
#define CLOCK_IP_PRT1_COL1_REQ49_INDEX    82U
#define CLOCK_IP_PRT1_COL1_REQ45_INDEX    83U



#define CLOCK_IP_PARTITION_0_INDEX         0U
#define CLOCK_IP_PARTITION_1_INDEX         1U
#define CLOCK_IP_PARTITION_2_INDEX         2U
#define CLOCK_IP_COLLECTION_0_INDEX        0U
#define CLOCK_IP_COLLECTION_1_INDEX        1U
#define CLOCK_IP_COLLECTION_2_INDEX        2U
#define CLOCK_IP_COLLECTION_3_INDEX        3U

#define CLOCK_IP_SEL_0_INDEX      0U
#define CLOCK_IP_SEL_1_INDEX      1U
#define CLOCK_IP_SEL_2_INDEX      2U
#define CLOCK_IP_SEL_3_INDEX      3U
#define CLOCK_IP_SEL_4_INDEX      4U
#define CLOCK_IP_SEL_5_INDEX      5U
#define CLOCK_IP_SEL_6_INDEX      6U
#define CLOCK_IP_SEL_7_INDEX      7U
#define CLOCK_IP_SEL_8_INDEX      8U
#define CLOCK_IP_SEL_9_INDEX      9U
#define CLOCK_IP_SEL_10_INDEX     10U
#define CLOCK_IP_SEL_11_INDEX     11U

#endif

#define PRTN0_COFB0_STAT_ADDRESS     (uint32)(IP_MC_ME_BASE + 0x110U)
#define PRTN0_COFB0_CLKEN_ADDRESS    (uint32)(IP_MC_ME_BASE + 0x130U)

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/* Clock start constant section data */
#define MCU_START_SEC_CONST_8

#include "Mcu_MemMap.h"

const uint8 Clock_Ip_au8DividerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_SWMUX_DIV */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_HWMUX_DIV */
    CLOCK_IP_PLL_PLLDV_ODIV2_OUTPUT,                            /* CLOCK_IP_PLL_POSTDIV */
    CLOCK_IP_PLL_PLL0DIV_DE_DIV_OUTPUT,                         /* CLOCK_IP_PCFS_PLL_OUT */
    CLOCK_IP_PLL_PLL0DIV_DE_DIV_OUTPUT,                         /* CLOCK_IP_PLL_OUT */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_DIV_TRIGGER_CMU */
    CLOCK_IP_CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* CLOCK_IP_DIV_TRIGGER */
    CLOCK_IP_FIRC_DIV_SEL_HSEb_CONFIG_REG_GPR,                  /* CLOCK_IP_FIRC_POSTDIV */
};
const uint8 Clock_Ip_au8DividerTriggerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT,            /* CLOCK_IP_DIV_TRIGGER_CMU */
    CLOCK_IP_CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT,            /* CLOCK_IP_DIV_TRIGGER */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8XoscCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_FXOSC_OSCON_BYP_EOCV_GM_SEL,                       /* CLOCK_IP_FAST_XOSC_CMU */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    CLOCK_IP_SXOSC_OSCON_EOCV,                                  /* CLOCK_IP_SLOW_XOSC */
#else
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
#endif
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8IrcoscCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_FIRC_STDBY_ENABLE,                                 /* CLOCK_IP_FIRCOSC */
    CLOCK_IP_SIRC_STDBY_ENABLE,                                 /* CLOCK_IP_SIRCOSC */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8GateCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_MC_ME_PARTITION_COFB_ENABLE_REQUEST,               /* CLOCK_IP_GATE */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8FractionalDividerCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8PllCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_PLL_RDIV_MFI_MFN_ODIV2_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE,/* CLOCK_IP_PLL_MOD */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8SelectorCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_CSC_CSS_CS_GRIP,                             /* CLOCK_IP_SWMUX_DIV */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* CLOCK_IP_HWMUX_DIV */
    CLOCK_IP_CGM_X_CSC_CSS_CLK_SW_RAMPDOWN_RAMPUP_SWIP,         /* CLOCK_IP_HWMUX_PCFS */
    CLOCK_IP_RTC_RTCC_CLKSELECT,                                /* CLOCK_IP_RTC_SEL */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8PcfsCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS,                    /* CLOCK_IP_PCFS_PLL_OUT */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};
const uint8 Clock_Ip_au8CmuCallbackIndex[CLOCK_IP_ALL_CALLBACKS_COUNT] = {
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_FAST_XOSC_CMU */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CLOCK_IP_DIV_TRIGGER_CMU */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
    CLOCK_IP_NO_CALLBACK,                                       /* No callback */
};




/* Clock features mapping */
const uint8 Clock_Ip_au8ClockFeatures[CLOCK_IP_NAMES_NO][CLOCK_IP_FEATURES_NO] =
/*   \
**********************************************************************************************************************************************************************************************************************************************************************************************  \
************************************     **********************       ***********************   E   ****************************       *************       *******************       ******************       ***************************       *****************       **********************  \
************************************  I  **********************   C   ***********************   X   ****************************       *************   S   *******************   D   ******************       ***************************       *****************       **********************  \
************************************  N  **********************   A   ***********************   T   ****************************   P   *************   E   *******************   I   ******************   G   ***************************   P   *****************       **********************  \
************************************  S  **********************   L   ***********************   E   ****************************   O   *************   L   *******************   V   ******************   A   ***************************   C   *****************   C   **********************  \
************************************  T  **********************   L   ***********************   N   ****************************   W   *************   E   *******************   I   ******************   T   ***************************   F   *****************   M   **********************  \
************************************  A  **********************   B   ***********************   S   ****************************   E   *************   C   *******************   D   ******************   E   ***************************   S   *****************   U   **********************  \
************************************  N  **********************   A   ***********************   I   ****************************   R   *************   T   *******************   E   ******************       ***************************       *****************       **********************  \
************************************  C  **********************   C   ***********************   O   ****************************       *************   O   *******************   R   ******************       ***************************       *****************       **********************  \
************************************  E  **********************   K   ***********************   N   ****************************       *************   R   *******************       ******************       ***************************       *****************       **********************  \
************************************     **********************       ***********************       ****************************       *************       *******************       ******************       ***************************       *****************       **********************  \
***********************************************************************************************************************************************************************************************************************************************************************************************/\
{ \
/*   CLOCK_IS_OFF clock         */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   CLOCK_IS_OFF               */ 
/*   FIRC_CLK clock             */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   FIRC_CLK clock             */
/*   FIRC_STANDBY_CLK clock     */ {0U,                       CLOCK_IP_FIRCOSC,                0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   FIRC_STANDBY_CLK clock     */
/*   SIRC_CLK clock             */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   SIRC_CLK clock             */
/*   SIRC_STANDBY_CLK clock     */ {0U,                       CLOCK_IP_SIRCOSC,                0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   SIRC_STANDBY_CLK clock     */
/*   FXOSC_CLK clock            */ {CLOCK_IP_FXOSC_INSTANCE,  CLOCK_IP_FAST_XOSC_CMU,          0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     CLOCK_IP_CMU_FC_0_INSTANCE},  /*   FXOSC_CLK clock            */
#if defined(CLOCK_IP_HAS_SXOSC_CLK) 
/*   SXOSC_CLK clock            */ {CLOCK_IP_SXOSC_INSTANCE,  CLOCK_IP_SLOW_XOSC,              0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   SXOSC_CLK clock            */
#endif
/*   PLL_CLK clock              */ {0U,                       CLOCK_IP_PLL_MOD,                0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   PLL_CLK clock              */
/*   FIRC_POSTDIV_CLK clock     */ {0U,                       CLOCK_IP_FIRC_POSTDIV,           0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   FIRC_POSTDIV_CLK clock     */
/*   PLL_POSTDIV_CLK clock      */ {0U,                       CLOCK_IP_PLL_POSTDIV,            0U,                                 0U,                 0U,                      CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   PLL_POSTDIV_CLK clock      */
/*   PLL_PHI0 clock             */ {0U,                       CLOCK_IP_PCFS_PLL_OUT,           0U,                                 0U,                 0U,                      CLOCK_IP_DIV_0_INDEX,   0U,                               CLOCK_IP_PCFS_7_INDEX,  0U},                          /*   PLL_PHI0 clock             */
/*   PLL_PHI1 clock             */ {0U,                       CLOCK_IP_PLL_OUT,                0U,                                 0U,                 0U,                      CLOCK_IP_DIV_1_INDEX,   0U,                               0U,                     0U},                          /*   PLL_PHI1 clock             */
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK) 
/*   emac_mii_rx clock          */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   emac_mii_rx clock          */
#endif  
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)  
/*   emac_mii_rmii_tx clock     */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   emac_mii_rmii_tx clock     */
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK) 
/*   lfast_ref_ext clock        */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   lfast_ref_ext clock          */
#endif  
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)  
/*   swg_pad clock              */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   swg_pad clock     */
#endif    
/*   SCS_CLK clock              */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_PCFS,             CLOCK_IP_SCS_EXTENSION,             0U,                 CLOCK_IP_SEL_0_INDEX,    0U,                     0U,                               0U,                     0U},                          /*   SCS_CLK clock              */
/*   CORE_CLK clock             */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_DIV_TRIGGER_CMU,        CLOCK_IP_CORE_EXTENSION,            0U,                 CLOCK_IP_SEL_0_INDEX,    CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     CLOCK_IP_CMU_FC_3_INSTANCE},  /*   CORE_CLK clock             */
/*   AIPS_PLAT_CLK clock        */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_DIV_TRIGGER_CMU,        CLOCK_IP_AIPS_PLAT_EXTENSION,       0U,                 CLOCK_IP_SEL_0_INDEX,    CLOCK_IP_DIV_1_INDEX,   0U,                               0U,                     CLOCK_IP_CMU_FC_4_INSTANCE},  /*   AIPS_PLAT_CLK clock        */
/*   AIPS_SLOW_CLK clock        */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_DIV_TRIGGER,            CLOCK_IP_AIPS_SLOW_EXTENSION,       0U,                 CLOCK_IP_SEL_0_INDEX,    CLOCK_IP_DIV_2_INDEX,   0U,                               0U,                     0U},                          /*   AIPS_SLOW_CLK clock        */
/*   HSE_CLK clock              */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_DIV_TRIGGER_CMU,        CLOCK_IP_HSE_EXTENSION,             0U,                 CLOCK_IP_SEL_0_INDEX,    CLOCK_IP_DIV_3_INDEX,   0U,                               0U,                     CLOCK_IP_CMU_FC_5_INSTANCE},  /*   HSE_CLK clock              */
/*   DCM_CLK clock              */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_DIV_TRIGGER,            CLOCK_IP_DCM_EXTENSION,             0U,                 CLOCK_IP_SEL_0_INDEX,    CLOCK_IP_DIV_4_INDEX,   0U,                               0U,                     0U},                          /*   DCM_CLK clock              */
#if defined(CLOCK_IP_HAS_LBIST_CLK) 
/*   LBIST_CLK clock            */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_DIV_TRIGGER,            CLOCK_IP_LBIST_EXTENSION,           0U,                 CLOCK_IP_SEL_0_INDEX,    CLOCK_IP_DIV_5_INDEX,   0U,                               0U,                     0U},                          /*   LBIST_CLK clock            */
#endif  
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)  
/*   QSPI_MEM_CLK clock         */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_DIV_TRIGGER,            CLOCK_IP_QSPI_MEM_EXTENSION,        0U,                 CLOCK_IP_SEL_0_INDEX,    CLOCK_IP_DIV_6_INDEX,   0U,                               0U,                     0U},                          /*   QSPI_MEM_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)  
/*   CM7_CORE_CLK clock         */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_DIV_TRIGGER,            CLOCK_IP_CM7_CORE_EXTENSION,        0U,                 CLOCK_IP_SEL_0_INDEX,    CLOCK_IP_DIV_7_INDEX,   0U,                               0U,                     CLOCK_IP_CMU_FC_6_INSTANCE},   /*   CM7_CORE_CLK clock         */
#endif
/*   CLKOUT_RUN_CLK clock       */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_SWMUX_DIV,              CLOCK_IP_RUN_EXTENSION,             0U,                 CLOCK_IP_SEL_6_INDEX,    CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   CLKOUT_RUN_CLK clock       */
/*   THE_LAST_PRODUCER_CLK      */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   THE_LAST_PRODUCER_CLK      */
/*   ADC0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ40_INDEX,   0U,                     0U},                          /*   ADC0_CLK clock             */
/*   ADC1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ41_INDEX,   0U,                     0U},                          /*   ADC1_CLK clock             */
#if defined(CLOCK_IP_HAS_ADC2_CLK)  
/*   ADC2_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ42_INDEX,   0U,                     0U},                          /*   ADC2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)  
/*   ADC3_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT3_COL1_REQ61_INDEX,   0U,                     0U},                          /*   ADC3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)  
/*   ADC4_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT3_COL1_REQ62_INDEX,   0U,                     0U},                          /*   ADC4_CLK clock             */
#endif 
#if defined(CLOCK_IP_HAS_ADC5_CLK)  
/*   ADC5_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT3_COL1_REQ63_INDEX,   0U,                     0U},                          /*   ADC5_CLK clock             */
#endif 
#if defined(CLOCK_IP_HAS_ADC6_CLK)  
/*   ADC6_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT3_COL2_REQ64_INDEX,   0U,                     0U},                          /*   ADC6_CLK clock             */
#endif 
/*   BCTU0_CLK clock            */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ33_INDEX,   0U,                     0U},                          /*   BCTU0_CLK clock            */
/*   CLKOUT_STANDBY_CLK clock   */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_SWMUX_DIV,              CLOCK_IP_CLKOUT_STANDBY_EXTENSION,  0U,                 CLOCK_IP_SEL_5_INDEX,    CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   CLKOUT_STANDBY_CLK clock   */
/*   CMP0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ92_INDEX,   0U,                     0U},                          /*   CMP0_CLK clock             */
/*   CMP1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ93_INDEX,   0U,                     0U},                          /*   CMP1_CLK clock             */
#if defined(CLOCK_IP_HAS_CMP2_CLK)  
/*   CMP2_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ58_INDEX,   0U,                     0U},                          /*   CMP2_CLK clock             */
#endif  
/*   CRC0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL3_REQ96_INDEX,   0U,                     0U},                          /*   CRC0_CLK clock             */
/*   DCM0_CLK clock             */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   DCM0_CLK clock             */
/*   DMAMUX0_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL1_REQ32_INDEX,   0U,                     0U},                          /*   DMAMUX0_CLK clock          */
/*   DMAMUX1_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL1_REQ33_INDEX,   0U,                     0U},                          /*   DMAMUX1_CLK clock          */
/*   EDMA0_CLK clock            */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ3_INDEX,    0U,                     0U},                          /*   EDMA0_CLK clock            */
/*   EDMA0_TCD0_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ4_INDEX,    0U,                     0U},                          /*   EDMA0_TCD0_CLK clock       */
/*   EDMA0_TCD1_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ5_INDEX,    0U,                     0U},                          /*   EDMA0_TCD1_CLK clock       */
/*   EDMA0_TCD2_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ6_INDEX,    0U,                     0U},                          /*   EDMA0_TCD2_CLK clock       */
/*   EDMA0_TCD3_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ7_INDEX,    0U,                     0U},                          /*   EDMA0_TCD3_CLK clock       */
/*   EDMA0_TCD4_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ8_INDEX,    0U,                     0U},                          /*   EDMA0_TCD4_CLK clock       */
/*   EDMA0_TCD5_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ9_INDEX,    0U,                     0U},                          /*   EDMA0_TCD5_CLK clock       */
/*   EDMA0_TCD6_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ10_INDEX,   0U,                     0U},                          /*   EDMA0_TCD6_CLK clock       */
/*   EDMA0_TCD7_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ11_INDEX,   0U,                     0U},                          /*   EDMA0_TCD7_CLK clock       */
/*   EDMA0_TCD8_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ12_INDEX,   0U,                     0U},                          /*   EDMA0_TCD8_CLK clock       */
/*   EDMA0_TCD9_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ13_INDEX,   0U,                     0U},                          /*   EDMA0_TCD9_CLK clock       */
/*   EDMA0_TCD10_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ14_INDEX,   0U,                     0U},                          /*   EDMA0_TCD10_CLK clock      */
/*   EDMA0_TCD11_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ15_INDEX,   0U,                     0U},                          /*   EDMA0_TCD11_CLK clock      */
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK) 
/*   EDMA0_TCD12_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ4_INDEX,    0U,                     0U},                          /*   EDMA0_TCD12_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK) 
/*   EDMA0_TCD13_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ5_INDEX,    0U,                     0U},                          /*   EDMA0_TCD13_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK) 
/*   EDMA0_TCD14_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ6_INDEX,    0U,                     0U},                          /*   EDMA0_TCD14_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK) 
/*   EDMA0_TCD15_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ7_INDEX,    0U,                     0U},                          /*   EDMA0_TCD15_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK) 
/*   EDMA0_TCD16_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ8_INDEX,    0U,                     0U},                          /*   EDMA0_TCD16_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK) 
/*   EDMA0_TCD17_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ9_INDEX,    0U,                     0U},                          /*   EDMA0_TCD17_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK) 
/*   EDMA0_TCD18_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ10_INDEX,   0U,                     0U},                          /*   EDMA0_TCD18_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK) 
/*   EDMA0_TCD19_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ11_INDEX,   0U,                     0U},                          /*   EDMA0_TCD19_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK) 
/*   EDMA0_TCD20_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ12_INDEX,   0U,                     0U},                          /*   EDMA0_TCD20_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK) 
/*   EDMA0_TCD21_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ13_INDEX,   0U,                     0U},                          /*   EDMA0_TCD21_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK) 
/*   EDMA0_TCD22_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ14_INDEX,   0U,                     0U},                          /*   EDMA0_TCD22_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK) 
/*   EDMA0_TCD23_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ15_INDEX,   0U,                     0U},                          /*   EDMA0_TCD23_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK) 
/*   EDMA0_TCD24_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ16_INDEX,   0U,                     0U},                          /*   EDMA0_TCD24_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK) 
/*   EDMA0_TCD25_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ17_INDEX,   0U,                     0U},                          /*   EDMA0_TCD25_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK) 
/*   EDMA0_TCD26_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ18_INDEX,   0U,                     0U},                          /*   EDMA0_TCD26_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK) 
/*   EDMA0_TCD27_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ19_INDEX,   0U,                     0U},                          /*   EDMA0_TCD27_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK) 
/*   EDMA0_TCD28_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ20_INDEX,   0U,                     0U},                          /*   EDMA0_TCD28_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK) 
/*   EDMA0_TCD29_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ21_INDEX,   0U,                     0U},                          /*   EDMA0_TCD29_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK) 
/*   EDMA0_TCD30_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ22_INDEX,   0U,                     0U},                          /*   EDMA0_TCD30_CLK clock      */
#endif  
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK) 
/*   EDMA0_TCD31_CLK clock      */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ23_INDEX,   0U,                     0U},                          /*   EDMA0_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)  
/*   EIM_CLK clock              */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ22_INDEX,   0U,                     0U},                          /*   EIM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)  
/*   EIM0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL2_REQ67_INDEX,   0U,                     0U},                          /*   EIM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)  
/*   EIM1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL2_REQ68_INDEX,   0U,                     0U},                          /*   EIM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)  
/*   EIM2_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL2_REQ69_INDEX,   0U,                     0U},                          /*   EIM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK) 
/*   EMAC_RX_CLK clock          */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_EMAC_RX_EXTENSION,         0U,                 CLOCK_IP_SEL_7_INDEX,    0U,                     0U,                               0U,                     0U},                          /*   EMAC_RX_CLK clock          */
#endif  
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)  
/*   EMAC0_RX_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ32_INDEX,   0U,                     0U},                          /*   EMAC0_RX_CLK clock         */
#endif  
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK) 
/*   EMAC_TS_CLK clock          */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_EMAC_TS_EXTENSION,         0U,                 CLOCK_IP_SEL_9_INDEX,    0U,                     0U,                               0U,                     0U},                          /*   EMAC_TS_CLK clock          */
#endif  
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)  
/*   EMAC0_TS_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ32_INDEX,   0U,                     0U},                          /*   EMAC0_TS_CLK clock         */
#endif  
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK) 
/*   EMAC_TX_CLK clock          */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_EMAC_TX_EXTENSION,         0U,                 CLOCK_IP_SEL_8_INDEX,    0U,                     0U,                               0U,                     0U},                          /*   EMAC_TX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK) 
/*   EMAC_TX_RMII_CLK clock     */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_EMAC_TX_RMII_EXTENSION,    0U,                 CLOCK_IP_SEL_12_INDEX,    CLOCK_IP_DIV_0_INDEX,  0U,                               0U,                     0U},                          /*   EMAC_TX_RMII_CLK clock          */
#endif  
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)  
/*   EMAC0_TX_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ32_INDEX,   0U,                     0U},                          /*   EMAC0_TX_CLK clock         */
#endif  
/*   EMIOS0_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ34_INDEX,   0U,                     0U},                          /*   EMIOS0_CLK clock           */
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
/*   EMIOS1_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ35_INDEX,   0U,                     0U},                          /*   EMIOS1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)  
/*   EMIOS2_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ36_INDEX,   0U,                     0U},                          /*   EMIOS2_CLK clock           */
#endif  
/*   ERM0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ23_INDEX,   0U,                     0U},                          /*   ERM0_CLK clock             */
#if defined(CLOCK_IP_HAS_ERM1_CLK) 
/*   ERM1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL0_REQ3_INDEX,   0U,                     0U},                          /*   ERM1_CLK clock             */
#endif
/*   FLASH0_CLK clock           */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   FLASH0_CLK clock           */
/*   FLEXCANA_CLK clock         */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_FLEXCANA_EXTENSION,        0U,                 CLOCK_IP_SEL_3_INDEX,    0U,                     0U,                               0U,                     0U},                          /*   FLEXCANA_CLK clock         */
/*   FLEXCAN0_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ65_INDEX,   0U,                     0U},                          /*   FLEXCAN0_CLK clock         */
/*   FLEXCAN1_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ66_INDEX,   0U,                     0U},                          /*   FLEXCAN1_CLK clock         */
/*   FLEXCAN2_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ67_INDEX,   0U,                     0U},                          /*   FLEXCAN2_CLK clock         */
/*   FLEXCANB_CLK clock         */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_FLEXCANB_EXTENSION,        0U,                 CLOCK_IP_SEL_4_INDEX,    0U,                     0U,                               0U,                     0U},                          /*   FLEXCANB_CLK clock         */
/*   FLEXCAN3_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ68_INDEX,   0U,                     0U},                          /*   FLEXCAN3_CLK clock         */
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK) 
/*   FLEXCAN4_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ69_INDEX,   0U,                     0U},                          /*   FLEXCAN4_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK) 
/*   FLEXCAN5_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ70_INDEX,   0U,                     0U},                          /*   FLEXCAN5_CLK clock         */
#endif
/*   FLEXIO0_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ73_INDEX,   0U,                     0U},                          /*   FLEXIO0_CLK clock          */
#if defined(CLOCK_IP_HAS_I3C0_CLK)  
/*   I3C0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ48_INDEX,   0U,                     0U},                          /*   I3C0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_I3C1_CLK)  
/*   I3C1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ49_INDEX,   0U,                     0U},                          /*   I3C1_CLK clock             */
#endif  
/*   INTM_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ31_INDEX,   0U,                     0U},                          /*   INTM_CLK clock             */
/*   LCU0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ38_INDEX,   0U,                     0U},                          /*   LCU0_CLK clock             */
/*   LCU1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ39_INDEX,   0U,                     0U},                          /*   LCU1_CLK clock             */
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK) 
/*   LFAST_REF_CLK clock        */ {CLOCK_IP_CGM0_INSTANCE,  CLOCK_IP_HWMUX_DIV,               CLOCK_IP_LFAST_REF_EXTENSION,       0U,                 CLOCK_IP_SEL_15_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   LFAST_REF_CLK clock             */
#endif
/*   LPI2C0_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ84_INDEX,   0U,                     0U},                          /*   LPI2C0_CLK clock           */
/*   LPI2C1_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ85_INDEX,   0U,                     0U},                          /*   LPI2C1_CLK clock           */
/*   LPSPI0_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ86_INDEX,   0U,                     0U},                          /*   LPSPI0_CLK clock           */
/*   LPSPI1_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ87_INDEX,   0U,                     0U},                          /*   LPSPI1_CLK clock           */
/*   LPSPI2_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ88_INDEX,   0U,                     0U},                          /*   LPSPI2_CLK clock           */
/*   LPSPI3_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ89_INDEX,   0U,                     0U},                          /*   LPSPI3_CLK clock           */
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)  
/*   LPSPI4_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ47_INDEX,   0U,                     0U},                          /*   LPSPI4_CLK clock           */
#endif  
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)  
/*   LPSPI5_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ48_INDEX,   0U,                     0U},                          /*   LPSPI5_CLK clock           */
#endif  
/*   LPUART0_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ74_INDEX,   0U,                     0U},                          /*   LPUART0_CLK clock          */
/*   LPUART1_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ75_INDEX,   0U,                     0U},                          /*   LPUART1_CLK clock          */
/*   LPUART2_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ76_INDEX,   0U,                     0U},                          /*   LPUART2_CLK clock          */
/*   LPUART3_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ77_INDEX,   0U,                     0U},                          /*   LPUART3_CLK clock          */
#if defined(CLOCK_IP_HAS_LPUART4_CLK) 
/*   LPUART4_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ78_INDEX,   0U,                     0U},                          /*   LPUART4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK) 
/*   LPUART5_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ79_INDEX,   0U,                     0U},                          /*   LPUART5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK) 
/*   LPUART6_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ80_INDEX,   0U,                     0U},                          /*   LPUART6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK) 
/*   LPUART7_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ81_INDEX,   0U,                     0U},                          /*   LPUART7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK) 
/*   LPUART8_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ35_INDEX,   0U,                     0U},                          /*   LPUART8_CLK clock          */
#endif  
#if defined(CLOCK_IP_HAS_LPUART9_CLK) 
/*   LPUART9_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ36_INDEX,   0U,                     0U},                          /*   LPUART9_CLK clock          */
#endif  
#if defined(CLOCK_IP_HAS_LPUART10_CLK)  
/*   LPUART10_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ37_INDEX,   0U,                     0U},                          /*   LPUART10_CLK clock         */
#endif  
#if defined(CLOCK_IP_HAS_LPUART11_CLK)  
/*   LPUART11_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ38_INDEX,   0U,                     0U},                          /*   LPUART11_CLK clock         */
#endif  
#if defined(CLOCK_IP_HAS_LPUART12_CLK)  
/*   LPUART12_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ39_INDEX,   0U,                     0U},                          /*   LPUART12_CLK clock         */
#endif  
#if defined(CLOCK_IP_HAS_LPUART13_CLK)  
/*   LPUART13_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ40_INDEX,   0U,                     0U},                          /*   LPUART13_CLK clock         */
#endif  
#if defined(CLOCK_IP_HAS_LPUART14_CLK)  
/*   LPUART14_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ41_INDEX,   0U,                     0U},                          /*   LPUART14_CLK clock         */
#endif  
#if defined(CLOCK_IP_HAS_LPUART15_CLK)  
/*   LPUART15_CLK clock         */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ42_INDEX,   0U,                     0U},                          /*   LPUART15_CLK clock         */
#endif  
/*   MSCM_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ24_INDEX,   0U,                     0U},                          /*   MSCM_CLK clock             */
#if defined(CLOCK_IP_HAS_MUA_CLK) 
/*   MUA_CLK clock              */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ46_INDEX,   0U,                     0U},                          /*   MUA_CLK clock              */
#endif  
#if defined(CLOCK_IP_HAS_MUB_CLK) 
/*   MUB_CLK clock              */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ47_INDEX,   0U,                     0U},                          /*   MUB_CLK clock              */
#endif  
/*   PIT0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ44_INDEX,   0U,                     0U},                          /*   PIT0_CLK clock             */
/*   PIT1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ45_INDEX,   0U,                     0U},                          /*   PIT1_CLK clock             */
#if defined(CLOCK_IP_HAS_PIT2_CLK)  
/*   PIT2_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL1_REQ63_INDEX,   0U,                     0U},                          /*   PIT2_CLK clock             */
#endif  
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK) 
/*   QSPI0_RAM_CLK clock        */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ51_INDEX,   0U,                     0U},                          /*   QSPI0_RAM_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK) 
/*   QSPI_2XSFIF_CLK clock      */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_QSPI_2XSFIF_EXTENSION,     0U,                 CLOCK_IP_SEL_10_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   QSPI_2XSFIF_CLK clock        */
#endif 
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK) 
/*   QSPI_SFCK_CLK clock        */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_QSPI_SFCK_EXTENSION,       0U,                 CLOCK_IP_SEL_10_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   QSPI_SFCK_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_SFCK_CLK)  
/*   QSPI0_SFCK_CLK clock       */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ51_INDEX,   0U,                     0U},                          /*   QSPI0_SFCK_CLK clock       */
#endif  
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)  
/*   QSPI0_TX_MEM_CLK clock     */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ51_INDEX,   0U,                     0U},                          /*   QSPI0_TX_MEM_CLK clock     */
#endif  
/*   RTC_CLK clock              */ {0U,                       CLOCK_IP_RTC_SEL,                0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   RTC_CLK clock              */
/*   RTC0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL1_REQ34_INDEX,   0U,                     0U},                          /*   RTC0_CLK clock             */
#if defined(CLOCK_IP_HAS_SAI0_CLK)  
/*   SAI0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ91_INDEX,   0U,                     0U},                          /*   SAI0_CLK clock             */
#endif  
#if defined(CLOCK_IP_HAS_SAI1_CLK)  
/*   SAI1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ55_INDEX,   0U,                     0U},                          /*   SAI1_CLK clock             */
#endif  
#if defined(CLOCK_IP_HAS_SEMA42_CLK)  
/*   SEMA42_CLK clock           */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ24_INDEX,   0U,                     0U},                          /*   SEMA42_CLK clock           */
#endif  
/*   SIUL0_CLK clock            */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL1_REQ42_INDEX,   0U,                     0U},                          /*   SIUL0_CLK clock            */
/*   STCU0_CLK clock            */ {0U,                       CLOCK_IP_NO_CALLBACK,            0U,                                 0U,                 0U,                      0U,                     0U,                               0U,                     0U},                          /*   STCU0_CLK clock            */
/*   STMA_CLK clock             */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_STMA_EXTENSION,            0U,                 CLOCK_IP_SEL_1_INDEX,    0U,                     0U,                               0U,                     0U},                          /*   STMA_CLK clock             */
/*   STM0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ29_INDEX,   0U,                     0U},                          /*   STM0_CLK clock             */
#if defined(CLOCK_IP_HAS_STMB_CLK)  
/*   STMB_CLK clock             */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_STMB_EXTENSION,            0U,                 CLOCK_IP_SEL_2_INDEX,    CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   STMB_CLK clock             */
#endif  
#if defined(CLOCK_IP_HAS_STM1_CLK)  
/*   STM1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ29_INDEX,   0U,                     0U},                          /*   STM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)  
/*   STMC_CLK clock             */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_STMC_EXTENSION,            0U,                 CLOCK_IP_SEL_13_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   STMC_CLK clock             */
#endif  
#if defined(CLOCK_IP_HAS_STM2_CLK)  
/*   STM2_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ30_INDEX,   0U,                     0U},                          /*   STM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)  
/*   SWG_CLK clock             */  {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_HWMUX_DIV,              CLOCK_IP_SWG_EXTENSION,             0U,                 CLOCK_IP_SEL_16_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   SWG_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)  
/*   SWG0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT3_COL1_REQ50_INDEX,   0U,                     0U},                          /*   SWG0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)  
/*   SWG1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT3_COL1_REQ51_INDEX,   0U,                     0U},                          /*   SWG1_CLK clock             */
#endif
/*   SWT0_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL0_REQ28_INDEX,   0U,                     0U},                          /*   SWT0_CLK clock             */
#if defined(CLOCK_IP_HAS_SWT1_CLK)  
/*   SWT1_CLK clock             */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL0_REQ27_INDEX,   0U,                     0U},                          /*   SWT1_CLK clock             */
#endif  
#if defined(CLOCK_IP_HAS_TCM_CM7_0_CLK) 
/*   TCM_CM7_0_CLK clock        */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ62_INDEX,   0U,                     0U},                          /*   TCM_CM7_0_CLK clock        */
#endif  
#if defined(CLOCK_IP_HAS_TCM_CM7_1_CLK) 
/*   TCM_CM7_1_CLK clock        */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT2_COL1_REQ63_INDEX,   0U,                     0U},                          /*   TCM_CM7_1_CLK clock        */
#endif  
/*   TEMPSENSE_CLK clock        */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL2_REQ95_INDEX,   0U,                     0U},                          /*   TEMPSENSE_CLK clock        */
/*   TRACE_CLK clock            */ {CLOCK_IP_CGM0_INSTANCE,   CLOCK_IP_SWMUX_DIV,              CLOCK_IP_TRACE_EXTENSION,           0U,                 CLOCK_IP_SEL_11_INDEX,   CLOCK_IP_DIV_0_INDEX,   0U,                               0U,                     0U},                          /*   TRACE_CLK clock            */
/*   TRGMUX0_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT0_COL1_REQ32_INDEX,   0U,                     0U},                          /*   TRGMUX0_CLK clock          */
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
/*   TSENSE0_CLK clock          */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL1_REQ49_INDEX,   0U,                     0U},                          /*   TSENSE0_CLK clock          */
#endif
/*   WKPU0_CLK clock            */ {0U,                       CLOCK_IP_GATE,                   0U,                                 0U,                 0U,                      0U,                     CLOCK_IP_PRT1_COL1_REQ45_INDEX,   0U,                     0U},                          /*   WKPU0_CLK clock            */
};


/*!
 * @brief Reset value of a software clock mux associated to a clock name
 */
const uint8 Clock_Ip_au8SoftwareMuxResetValue[CLOCK_IP_NAMES_NO] = {
/*   CLOCK_IS_OFF clock         */ 0U,  
/*   FIRC_CLK clock             */ 0U,  
/*   FIRC_STANDBY_CLK clock     */ 0U,  
/*   SIRC_CLK clock             */ 0U,  
/*   SIRC_STANDBY_CLK clock     */ 0U,  
/*   FXOSC_CLK clock            */ 0U,  
#if defined(CLOCK_IP_HAS_SXOSC_CLK) 
/*   SXOSC_CLK clock            */ 0U,  
#endif
/*   PLL_CLK clock              */ 0U,  
/*   FIRC_POSTDIV_CLK clock     */ 0U,
/*   PLL_POSTDIV_CLK clock      */ 0U,  
/*   PLL_PHI0 clock             */ 0U,  
/*   PLL_PHI1 clock             */ 0U,  
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
/*   emac_mii_rx clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
/*   emac_mii_rmii_tx clock     */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
/*   lfast_ref_ext clock        */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
/*   swg_pad clock              */ 0U,  
#endif
/*   SCS_CLK clock              */ 0U,  
/*   CORE_CLK clock             */ 0U,  
/*   AIPS_PLAT_CLK clock        */ 0U,  
/*   AIPS_SLOW_CLK clock        */ 0U,  
/*   HSE_CLK clock              */ 0U,  
/*   DCM_CLK clock              */ 0U,  
#if defined(CLOCK_IP_HAS_LBIST_CLK)
/*   LBIST_CLK clock            */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
/*   QSPI_MEM_CLK clock         */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
/*   CM7_CORE_CLK clock         */ 0U,  
#endif
/*   CLKOUT_RUN_CLK clock       */ 0U,  
/*   THE_LAST_PRODUCER_CLK      */ 0U,  
/*   ADC0_CLK clock             */ 0U,  
/*   ADC1_CLK clock             */ 0U,  
#if defined(CLOCK_IP_HAS_ADC2_CLK)
/*   ADC2_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
/*   ADC3_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
/*   ADC4_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
/*   ADC5_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
/*   ADC6_CLK clock             */ 0U,  
#endif
/*   BCTU0_CLK clock            */ 0U,  
/*   CLKOUT_STANDBY_CLK clock   */ 0U,  
/*   CMP0_CLK clock             */ 0U,  
/*   CMP1_CLK clock             */ 0U,  
#if defined(CLOCK_IP_HAS_CMP2_CLK)
/*   CMP2_CLK clock             */ 0U,  
#endif
/*   CRC0_CLK clock             */ 0U,  
/*   DCM0_CLK clock             */ 0U,  
/*   DMAMUX0_CLK clock          */ 0U,  
/*   DMAMUX1_CLK clock          */ 0U,  
/*   EDMA0_CLK clock            */ 0U,  
/*   EDMA0_TCD0_CLK clock       */ 0U,  
/*   EDMA0_TCD1_CLK clock       */ 0U,  
/*   EDMA0_TCD2_CLK clock       */ 0U,  
/*   EDMA0_TCD3_CLK clock       */ 0U,  
/*   EDMA0_TCD4_CLK clock       */ 0U,  
/*   EDMA0_TCD5_CLK clock       */ 0U,  
/*   EDMA0_TCD6_CLK clock       */ 0U,  
/*   EDMA0_TCD7_CLK clock       */ 0U,  
/*   EDMA0_TCD8_CLK clock       */ 0U,  
/*   EDMA0_TCD9_CLK clock       */ 0U,  
/*   EDMA0_TCD10_CLK clock      */ 0U,  
/*   EDMA0_TCD11_CLK clock      */ 0U,  
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
/*   EDMA0_TCD12_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
/*   EDMA0_TCD13_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
/*   EDMA0_TCD14_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
/*   EDMA0_TCD15_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
/*   EDMA0_TCD16_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
/*   EDMA0_TCD17_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
/*   EDMA0_TCD18_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
/*   EDMA0_TCD19_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
/*   EDMA0_TCD20_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
/*   EDMA0_TCD21_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
/*   EDMA0_TCD22_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
/*   EDMA0_TCD23_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
/*   EDMA0_TCD24_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
/*   EDMA0_TCD25_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
/*   EDMA0_TCD26_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
/*   EDMA0_TCD27_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
/*   EDMA0_TCD28_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
/*   EDMA0_TCD29_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
/*   EDMA0_TCD30_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
/*   EDMA0_TCD31_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
/*   EIM_CLK clock              */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
/*   EIM0_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
/*   EIM1_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
/*   EIM2_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
/*   EMAC_RX_CLK clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
/*   EMAC0_RX_CLK clock         */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
/*   EMAC_TS_CLK clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
/*   EMAC0_TS_CLK clock         */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
/*   EMAC_TX_CLK clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
/*   EMAC_TX_RMII_CLK clock     */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
/*   EMAC0_TX_CLK clock         */ 0U,  
#endif
/*   EMIOS0_CLK clock           */ 0U,  
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
/*   EMIOS1_CLK clock           */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
/*   EMIOS2_CLK clock           */ 0U,  
#endif
/*   ERM0_CLK clock             */ 0U,  
#if defined(CLOCK_IP_HAS_ERM1_CLK)
/*   ERM1_CLK clock             */ 0U,  
#endif
/*   FLASH0_CLK clock           */ 0U,  
/*   FLEXCANA_CLK clock         */ 0U,  
/*   FLEXCAN0_CLK clock         */ 0U,  
/*   FLEXCAN1_CLK clock         */ 0U,  
/*   FLEXCAN2_CLK clock         */ 0U,  
/*   FLEXCANB_CLK clock         */ 0U,  
/*   FLEXCAN3_CLK clock         */ 0U,  
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
/*   FLEXCAN4_CLK clock         */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
/*   FLEXCAN5_CLK clock         */ 0U,  
#endif
/*   FLEXIO0_CLK clock          */ 0U,  
#if defined(CLOCK_IP_HAS_I3C0_CLK)
/*   I3C0_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_I3C1_CLK)
/*   I3C1_CLK clock             */ 0U,  
#endif
/*   INTM_CLK clock             */ 0U,  
/*   LCU0_CLK clock             */ 0U,  
/*   LCU1_CLK clock             */ 0U,  
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
/*   LFAST_REF_CLK clock        */ 0U,  
#endif
/*   LPI2C0_CLK clock           */ 0U,  
/*   LPI2C1_CLK clock           */ 0U,  
/*   LPSPI0_CLK clock           */ 0U,  
/*   LPSPI1_CLK clock           */ 0U,  
/*   LPSPI2_CLK clock           */ 0U,  
/*   LPSPI3_CLK clock           */ 0U,  
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
/*   LPSPI4_CLK clock           */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
/*   LPSPI5_CLK clock           */ 0U,  
#endif
/*   LPUART0_CLK clock          */ 0U,  
/*   LPUART1_CLK clock          */ 0U,  
/*   LPUART2_CLK clock          */ 0U,  
/*   LPUART3_CLK clock          */ 0U,  
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
/*   LPUART4_CLK clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
/*   LPUART5_CLK clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
/*   LPUART6_CLK clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
/*   LPUART7_CLK clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
/*   LPUART8_CLK clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
/*   LPUART9_CLK clock          */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
/*   LPUART10_CLK clock         */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
/*   LPUART11_CLK clock         */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
/*   LPUART12_CLK clock         */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
/*   LPUART13_CLK clock         */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
/*   LPUART14_CLK clock         */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
/*   LPUART15_CLK clock         */ 0U,  
#endif
/*   MSCM_CLK clock             */ 0U,  
#if defined(CLOCK_IP_HAS_MUA_CLK)
/*   MUA_CLK clock              */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_MUB_CLK)
/*   MUB_CLK clock              */ 0U,  
#endif
/*   PIT0_CLK clock             */ 0U,  
/*   PIT1_CLK clock             */ 0U,  
#if defined(CLOCK_IP_HAS_PIT2_CLK)
/*   PIT2_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
/*   QSPI0_RAM_CLK clock        */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/*   QSPI_2XSFIF_CLK clock      */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
/*   QSPI_SFCK_CLK clock        */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_QSPI0_SFCK_CLK)
/*   QSPI0_SFCK_CLK clock       */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK) 
/*   QSPI0_TX_MEM_CLK clock     */ 0U,  
#endif
/*   RTC_CLK clock              */ 0U,  
/*   RTC0_CLK clock             */ 0U,  
#if defined(CLOCK_IP_HAS_SAI0_CLK)
/*   SAI0_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
/*   SAI1_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
/*   SEMA42_CLK clock           */ 0U,  
#endif
/*   SIUL0_CLK clock            */ 0U,  
/*   STCU0_CLK clock            */ 0U,  
/*   STMA_CLK clock             */ 0U,  
/*   STM0_CLK clock             */ 0U,  
#if defined(CLOCK_IP_HAS_STMB_CLK)
/*   STMB_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
/*   STM1_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
/*   STMC_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
/*   STM2_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)  
/*   SWG_CLK clock              */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
/*   SWG0_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
/*   SWG1_CLK clock             */ 0U,  
#endif
/*   SWT0_CLK clock             */ 0U,  
#if defined(CLOCK_IP_HAS_SWT1_CLK)
/*   SWT1_CLK clock             */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_0_CLK)
/*   TCM_CM7_0_CLK clock        */ 0U,  
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_1_CLK)
/*   TCM_CM7_1_CLK clock        */ 0U,  
#endif
/*   TEMPSENSE_CLK clock        */ 0U,  
/*   TRACE_CLK clock            */ 0U,  
/*   TRGMUX0_CLK clock          */ 0U,  
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
/*   TSENSE0_CLK clock          */ 0U,  
#endif
/*   WKPU0_CLK clock            */ 0U, 
};


/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_8

#include "Mcu_MemMap.h"


/* Clock start constant section data */
#define MCU_START_SEC_CONST_16

#include "Mcu_MemMap.h"

/*!
 * @brief Converts a clock name to a selector entry hardware value
 */
const uint16 Clock_Ip_au16SelectorEntryHardwareValue[CLOCK_IP_PRODUCERS_NO] = {
        0U,     /*!< CLOCK_IS_OFF                           */
        0U,     /*!< FIRC_CLK_CLK clock source              */
        0U,     /*!< FIRC_STANDBY_CLK clock source          */
        1U,     /*!< SIRC_CLK_CLK clock source              */
        1U,     /*!< SIRC_STANDBY_CLK clock source          */
        2U,     /*!< FXOSC_CLK_CLK clock source             */
#if defined(CLOCK_IP_HAS_SXOSC_CLK) 
        4U,     /*!< SXOSC_CLK_CLK clock source             */
#endif
        0U,     /*!< PLL_VCO_CLK clock source               */
        0U,     /*!< FIRC_POSTDIV_CLK clock                 */
        0U,     /*!< PLL_POSTVDIV_CLK clock source          */
        8U,     /*!< PLL_PHI0_CLK clock source              */
        9U,     /*!< PLL_PHI1_CLK clock source              */
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
        25U,    /*!< emac_mii_rx_CLK external source        */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
        24U,    /*!< emac_mii_rmii_tx_CLK external source   */
#endif
        0U,     /*!< SCS_CLK common clock                   */
        16U,    /*!< CORE_CLK common clock                  */
        22U,    /*!< AIPS_PLAT_CLK common clock             */
        23U,    /*!< AIPS_SLOW_CLK common clock             */
        19U,    /*!< HSE_CLK common clock                   */
        0U,     /*!< DCM_CLK common clock                   */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
        0U,     /*!< LBIST_CLK common clock                 */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
        0U,     /*!< QSPI_MEM_CLK common clock              */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
        0U,     /*!< CM7_CORE_CLK common clock              */
#endif 
        0U,     /*!< CLKOUT_RUN_CLK common clock            */
};

/*!
 * @brief Converts a clock name to a RTC selector entry hardware value
 */
const uint16 Clock_Ip_au16SelectorEntryRtcHardwareValue[CLOCK_IP_PRODUCERS_NO] = {
        0U,     /*!< CLOCK_IS_OFF                           */
        2U,     /*!< FIRC_CLK clock source                  */
        0U,     /*!< FIRC_STANDBY_CLK clock source       NA */
        1U,     /*!< SIRC_CLK clock source                  */
        0U,     /*!< SIRC_STANDBY_CLK clock source       NA */
        3U,     /*!< FXOSC_CLK clock source                 */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)                         
        0U,     /*!< SXOSC_CLK clock source                 */
#endif
        0U,     /*!< PLL_VCO_CLK clock source            NA */
        0U,     /*!< FIRC_POSTDIV_CLK clock              NA */
        0U,     /*!< PLL_POSTVDIV_CLK clock source       NA */
        0U,     /*!< PLL_PHI0_CLK clock source           NA */
        0U,     /*!< PLL_PHI1_CLK clock source           NA */
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
        0U,     /*!< emac_mii_rx_CLK external source     NA */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
        0U,     /*!< emac_mii_rmii_tx_CLK external sourceNA */
#endif
        0U,     /*!< SCS_CLK common clock                NA */
        0U,     /*!< CORE_CLK common clock               NA */
        0U,     /*!< AIPS_PLAT_CLK common clock          NA */
        0U,     /*!< AIPS_SLOW_CLK common clock          NA */
        0U,     /*!< HSE_CLK common clock                NA */
        0U,     /*!< DCM_CLK common clock                NA */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
        0U,     /*!< LBIST_CLK common clock              NA */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
        0U,     /*!< QSPI_MEM_CLK common clock           NA */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
        0U,     /*!< CM7_CORE_CLK common clock           NA */
#endif 
        0U,     /*!< CLKOUT_RUN_CLK common clock         NA */
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_16

#include "Mcu_MemMap.h"


/* Clock start constant section data */
#define MCU_START_SEC_CONST_32

#include "Mcu_MemMap.h"

#if (defined(CLOCK_IP_DEV_ERROR_DETECT))
#if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
/* Clock name types */
const uint32 Clock_Ip_au8ClockNameTypes[CLOCK_IP_NAMES_NO] =
{
/*   CLOCK_IS_OFF clock         */ 0U,                                                                                                                                                                                                                                                                                       /*   CLOCK_IS_OFF               */   
/*   FIRC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FIRC_CLK clock             */
/*   FIRC_STANDBY_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FIRC_STANDBY_CLK clock     */
/*   SIRC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SIRC_CLK clock             */
/*   SIRC_STANDBY_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SIRC_STANDBY_CLK clock     */
/*   FXOSC_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FXOSC_CLK clock            */
#if defined(CLOCK_IP_HAS_SXOSC_CLK) 
/*   SXOSC_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SXOSC_CLK clock            */
#endif
/*   PLL_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   PLL_CLK clock              */
/*   FIRC_POSTDIV_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FIRC_POSTDIV_CLK clock     */
/*   PLL_POSTDIV_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   PLL_POSTDIV_CLK clock      */
/*   PLL_PHI0 clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   PLL_PHI0 clock             */
/*   PLL_PHI1 clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   PLL_PHI1 clock             */
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
/*   emac_mii_rx clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   emac_mii_rx clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
/*   emac_mii_rmii_tx clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   emac_mii_rmii_tx clock     */
#endif
#if defined(CLOCK_IP_HAS_LFAST_REF_EXT_CLK)
/*   lfast_ref_ext clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   lfast_ref_ext clock     */
#endif
#if defined(CLOCK_IP_HAS_SWG_PAD_CLK)
/*   swg_pad clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   swg_pad clock     */
#endif
/*   SCS_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SCS_CLK clock              */
/*   CORE_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   CORE_CLK clock             */
/*   AIPS_PLAT_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   AIPS_PLAT_CLK clock        */
/*   AIPS_SLOW_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   AIPS_SLOW_CLK clock        */
/*   HSE_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   HSE_CLK clock              */
/*   DCM_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   DCM_CLK clock              */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
/*   LBIST_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LBIST_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
/*   QSPI_MEM_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   QSPI_MEM_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
/*   CM7_CORE_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   CM7_CORE_CLK clock         */
#endif
/*   CLKOUT_RUN_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   CLKOUT_RUN_CLK clock       */
/*   THE_LAST_PRODUCER_CLK      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   THE_LAST_PRODUCER_CLK      */
/*   ADC0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   ADC0_CLK clock             */
/*   ADC1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   ADC1_CLK clock             */
#if defined(CLOCK_IP_HAS_ADC2_CLK)
/*   ADC2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   ADC2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
/*   ADC3_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   ADC3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
/*   ADC4_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   ADC4_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
/*   ADC5_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   ADC5_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
/*   ADC6_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   ADC6_CLK clock             */
#endif
/*   BCTU0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   BCTU0_CLK clock            */
/*   CLKOUT_STANDBY_CLK clock   */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   CLKOUT_STANDBY_CLK clock   */
/*   CMP0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   CMP0_CLK clock             */
/*   CMP1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   CMP1_CLK clock             */
#if defined(CLOCK_IP_HAS_CMP2_CLK)
/*   CMP2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   CMP2_CLK clock             */
#endif
/*   CRC0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   CRC0_CLK clock             */
/*   DCM0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   DCM0_CLK clock             */
/*   DMAMUX0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   DMAMUX0_CLK clock          */
/*   DMAMUX1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   DMAMUX1_CLK clock          */
/*   EDMA0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_CLK clock            */
/*   EDMA0_TCD0_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD0_CLK clock       */
/*   EDMA0_TCD1_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD1_CLK clock       */
/*   EDMA0_TCD2_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD2_CLK clock       */
/*   EDMA0_TCD3_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD3_CLK clock       */
/*   EDMA0_TCD4_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD4_CLK clock       */
/*   EDMA0_TCD5_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD5_CLK clock       */
/*   EDMA0_TCD6_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD6_CLK clock       */
/*   EDMA0_TCD7_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD7_CLK clock       */
/*   EDMA0_TCD8_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD8_CLK clock       */
/*   EDMA0_TCD9_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD9_CLK clock       */
/*   EDMA0_TCD10_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD10_CLK clock      */
/*   EDMA0_TCD11_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD11_CLK clock      */
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
/*   EDMA0_TCD12_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD12_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
/*   EDMA0_TCD13_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD13_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
/*   EDMA0_TCD14_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD14_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
/*   EDMA0_TCD15_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD15_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
/*   EDMA0_TCD16_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD16_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
/*   EDMA0_TCD17_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD17_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
/*   EDMA0_TCD18_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD18_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
/*   EDMA0_TCD19_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD19_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
/*   EDMA0_TCD20_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD20_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
/*   EDMA0_TCD21_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD21_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
/*   EDMA0_TCD22_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD22_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
/*   EDMA0_TCD23_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD23_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
/*   EDMA0_TCD24_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD24_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
/*   EDMA0_TCD25_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD25_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
/*   EDMA0_TCD26_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD26_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
/*   EDMA0_TCD27_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD27_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
/*   EDMA0_TCD28_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD28_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
/*   EDMA0_TCD29_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD29_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
/*   EDMA0_TCD30_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD30_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
/*   EDMA0_TCD31_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EDMA0_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
/*   EIM_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EIM_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
/*   EIM0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EIM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
/*   EIM1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EIM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
/*   EIM2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EIM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
/*   EMAC_RX_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMAC_RX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
/*   EMAC0_RX_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMAC0_RX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
/*   EMAC_TS_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMAC_TS_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
/*   EMAC0_TS_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMAC0_TS_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
/*   EMAC_TX_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMAC_TX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
/*   EMAC_TX_RMII_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMAC_TX_RMII_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
/*   EMAC0_TX_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMAC0_TX_CLK clock         */
#endif
/*   EMIOS0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMIOS0_CLK clock           */
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
/*   EMIOS1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMIOS1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
/*   EMIOS2_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   EMIOS2_CLK clock           */
#endif
/*   ERM0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   ERM0_CLK clock             */
#if defined(CLOCK_IP_HAS_ERM1_CLK)
/*   ERM1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   ERM1_CLK clock             */
#endif
/*   FLASH0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLASH0_CLK clock           */
/*   FLEXCANA_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLEXCANA_CLK clock         */
/*   FLEXCAN0_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLEXCAN0_CLK clock         */
/*   FLEXCAN1_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLEXCAN1_CLK clock         */
/*   FLEXCAN2_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLEXCAN2_CLK clock         */
/*   FLEXCANB_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLEXCANB_CLK clock         */
/*   FLEXCAN3_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLEXCAN3_CLK clock         */
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
/*   FLEXCAN4_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLEXCAN4_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
/*   FLEXCAN5_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLEXCAN5_CLK clock         */
#endif
/*   FLEXIO0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   FLEXIO0_CLK clock          */
#if defined(CLOCK_IP_HAS_I3C0_CLK)
/*   I3C0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   I3C0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_I3C1_CLK)
/*   I3C1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   I3C1_CLK clock             */
#endif
/*   INTM_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   INTM_CLK clock             */
/*   LCU0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LCU0_CLK clock             */
/*   LCU1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LCU1_CLK clock             */
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
/*   LFAST_REF_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LFAST_REF_CLK clock        */
#endif
/*   LPI2C0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPI2C0_CLK clock           */
/*   LPI2C1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPI2C1_CLK clock           */
/*   LPSPI0_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPSPI0_CLK clock           */
/*   LPSPI1_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPSPI1_CLK clock           */
/*   LPSPI2_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPSPI2_CLK clock           */
/*   LPSPI3_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPSPI3_CLK clock           */
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
/*   LPSPI4_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPSPI4_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
/*   LPSPI5_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPSPI5_CLK clock           */
#endif
/*   LPUART0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART0_CLK clock          */
/*   LPUART1_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART1_CLK clock          */
/*   LPUART2_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART2_CLK clock          */
/*   LPUART3_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART3_CLK clock          */
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
/*   LPUART4_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
/*   LPUART5_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
/*   LPUART6_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
/*   LPUART7_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
/*   LPUART8_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART8_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
/*   LPUART9_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART9_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
/*   LPUART10_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART10_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
/*   LPUART11_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART11_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
/*   LPUART12_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART12_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
/*   LPUART13_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART13_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
/*   LPUART14_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART14_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
/*   LPUART15_CLK clock         */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   LPUART15_CLK clock         */
#endif
/*   MSCM_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   MSCM_CLK clock             */
#if defined(CLOCK_IP_HAS_MUA_CLK)
/*   MUA_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   MUA_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MUB_CLK)
/*   MUB_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   MUB_CLK clock              */
#endif
/*   PIT0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   PIT0_CLK clock             */
/*   PIT1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   PIT1_CLK clock             */
#if defined(CLOCK_IP_HAS_PIT2_CLK)
/*   PIT2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   PIT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
/*   QSPI0_RAM_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   QSPI0_RAM_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/*   QSPI_2XSFIF_CLK clock      */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   QSPI_2XSFIF_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
/*   QSPI_SFCK_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   QSPI_SFCK_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_SFCK_CLK)
/*   QSPI0_SFCK_CLK clock       */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   QSPI0_SFCK_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK) 
/*   QSPI0_TX_MEM_CLK clock     */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   QSPI0_TX_MEM_CLK clock     */
#endif
/*   RTC_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   RTC_CLK clock              */
/*   RTC0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   RTC0_CLK clock             */
#if defined(CLOCK_IP_HAS_SAI0_CLK)
/*   SAI0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SAI0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
/*   SAI1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SAI1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
/*   SEMA42_CLK clock           */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SEMA42_CLK clock           */
#endif
/*   SIUL0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SIUL0_CLK clock            */
/*   STCU0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   STCU0_CLK clock            */
/*   STMA_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   STMA_CLK clock             */
/*   STM0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   STM0_CLK clock             */
#if defined(CLOCK_IP_HAS_STMB_CLK)
/*   STMB_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   STMB_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
/*   STM1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   STM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
/*   STMC_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   STMB_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
/*   STM2_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   STM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)  
/*   SWG_CLK clock              */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SWG_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
/*   SWG0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SWG0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
/*   SWG1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SWG1_CLK clock             */
#endif
/*   SWT0_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SWT0_CLK clock             */
#if defined(CLOCK_IP_HAS_SWT1_CLK)
/*   SWT1_CLK clock             */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   SWT1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_0_CLK)
/*   TCM_CM7_0_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   TCM_CM7_0_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_1_CLK)
/*   TCM_CM7_1_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   TCM_CM7_1_CLK clock        */
#endif
/*   TEMPSENSE_CLK clock        */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   TEMPSENSE_CLK clock        */
/*   TRACE_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   TRACE_CLK clock            */
/*   TRGMUX0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   TRGMUX0_CLK clock          */
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
/*   TSENSE0_CLK clock          */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   TSENSE0_CLK clock          */
#endif
/*   WKPU0_CLK clock            */ (CLOCK_IP_IRCOSC_OBJECT | CLOCK_IP_XOSC_OBJECT | CLOCK_IP_PLL_OBJECT | CLOCK_IP_SELECTOR_OBJECT | CLOCK_IP_DIVIDER_OBJECT | CLOCK_IP_DIVIDER_TRIGGER_OBJECT | CLOCK_IP_FRAC_DIV_OBJECT | CLOCK_IP_EXT_SIG_OBJECT | CLOCK_IP_GATE_OBJECT | CLOCK_IP_PCFS_OBJECT | CLOCK_IP_CMU_OBJECT) ,   /*   WKPU0_CLK clock            */
};
#endif
#endif /* CLOCK_IP_DEV_ERROR_DETECT */

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_32
#include "Mcu_MemMap.h"


/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

Clock_Ip_CgmMuxType* const Clock_Ip_apxCgm[CLOCK_IP_MC_CGM_INSTANCES_COUNT][CLOCK_IP_MC_CGM_MUXS_COUNT] =
{
    {

     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_0_CSC) ),

     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_1_CSC) ),
#ifdef MC_CGM_MUX_2_CSC_SELCTL
     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_2_CSC) ),
#endif
     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_3_CSC) ),

     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_4_CSC) ),

     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_5_CSC) ),

     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_6_CSC) ),
#ifdef MC_CGM_MUX_7_CSC_SELCTL
     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_7_CSC) ),
#endif
#ifdef MC_CGM_MUX_8_CSC_SELCTL
     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_8_CSC) ),
#endif
#ifdef MC_CGM_MUX_9_CSC_SELCTL
     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_9_CSC) ),
#endif
#ifdef MC_CGM_MUX_10_CSC_SELCTL
     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_10_CSC) ),
#endif
     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_11_CSC) ),
#ifdef MC_CGM_MUX_15_CSC_SELCTL
     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_15_CSC) ),
#endif
#ifdef MC_CGM_MUX_16_CSC_SELCTL
     (Clock_Ip_CgmMuxType*)( &(IP_MC_CGM->MUX_16_CSC) ),
#endif
    },
};

volatile Clock_Ip_CgmPcfsType* const Clock_Ip_apxCgmPcfs[CLOCK_IP_MC_CGM_INSTANCES_COUNT] =
{
     (volatile Clock_Ip_CgmPcfsType*)( &(IP_MC_CGM->PCFS_SDUR) ),
};

Clock_Ip_ExtOSCType* const Clock_Ip_apxXosc[CLOCK_IP_XOSC_INSTANCES_ARRAY_SIZE] =
{
    (Clock_Ip_ExtOSCType*)IP_FXOSC,
#ifdef IP_SXOSC
    (Clock_Ip_ExtOSCType*)IP_SXOSC,
#endif
};

PLL_Type* const Clock_Ip_pxPll[CLOCK_IP_PLL_INSTANCES_ARRAY_SIZE] =
{
    (PLL_Type*)IP_PLL,
};

Clock_Ip_ClockMonitorType* const Clock_Ip_apxCmu[CLOCK_IP_CMU_INSTANCES_ARRAY_SIZE] =
{
    (Clock_Ip_ClockMonitorType*)IP_CMU_0,
    (Clock_Ip_ClockMonitorType*)IP_CMU_3,
    (Clock_Ip_ClockMonitorType*)IP_CMU_4,
    (Clock_Ip_ClockMonitorType*)IP_CMU_5,
#ifdef IP_CMU_6
    (Clock_Ip_ClockMonitorType*)IP_CMU_6,
#endif
};

Clock_Ip_NameType const Clock_Ip_aeCmuNames[CLOCK_IP_CMU_INSTANCES_ARRAY_SIZE] =
{
    FXOSC_CLK,
    CORE_CLK,
    AIPS_PLAT_CLK,
    HSE_CLK,
#ifdef CLOCK_IP_HAS_CM7_CORE_CLK
    CM7_CORE_CLK,
#endif
};

Clock_Ip_CmuInfoType const Clock_Ip_axCmuInfo[CLOCK_IP_CMU_INFO_SIZE] =  {

/* CLOCK_IP_CMU_FC_0_INSTANCE */
{
    FXOSC_CLK,                                       /* Name of the clock that supports cmu (clock monitor) */
    FIRC_CLK,                                        /* Name of the reference clock */
    AIPS_SLOW_CLK,                                   /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_0,                    /* Cmu instance */
},
/* Reserved cmu instance */
{
    RESERVED_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
    RESERVED_CLK,                                    /* Name of the reference clock */
    RESERVED_CLK,                                    /* Name of the bus clock */
    NULL_PTR,                                        /* Cmu instance */
},
/* Reserved cmu instance */
{
    RESERVED_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
    RESERVED_CLK,                                    /* Name of the reference clock */
    RESERVED_CLK,                                    /* Name of the bus clock */
    NULL_PTR,                                        /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_3_INSTANCE */
{
    CORE_CLK,                                        /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    AIPS_SLOW_CLK,                                   /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_3,                    /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_4_INSTANCE */
{
    AIPS_PLAT_CLK,                                   /* Name of the clock that supports cmu (clock monitor) */
    FIRC_CLK,                                       /* Name of the reference clock */
    AIPS_SLOW_CLK,                                   /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_4,                    /* Cmu instance */
},
/* CLOCK_IP_CMU_FC_5_INSTANCE */
{
    HSE_CLK,                                         /* Name of the clock that supports cmu (clock monitor) */
    FIRC_CLK,                                       /* Name of the reference clock */
    AIPS_SLOW_CLK,                                   /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_5,                    /* Cmu instance */
},
#ifdef CLOCK_IP_HAS_CM7_CORE_CLK
/* CLOCK_IP_CMU_FC_6_INSTANCE */
{
    CM7_CORE_CLK,                                         /* Name of the clock that supports cmu (clock monitor) */
    FXOSC_CLK,                                       /* Name of the reference clock */
    AIPS_SLOW_CLK,                                   /* Name of the bus clock */
    (Clock_Ip_ClockMonitorType*)IP_CMU_6,                    /* Cmu instance */
},
#endif
};

volatile Clock_Ip_McmePartitionSetType* const Clock_Ip_apxMcMeSetPartitions[CLOCK_IP_MC_ME_PARTITIONS_COUNT] =
{
     (volatile Clock_Ip_McmePartitionSetType*)(PRTN0_COFB0_CLKEN_ADDRESS),

     (volatile Clock_Ip_McmePartitionSetType*)( ((volatile uint8*)&(IP_MC_ME->PRTN1_COFB0_CLKEN)) ),
#ifndef CLOCK_IP_DERIVATIVE_001
     (volatile Clock_Ip_McmePartitionSetType*)( ((volatile uint8*)&(IP_MC_ME->PRTN2_COFB0_CLKEN)) ),
#endif
};

volatile const Clock_Ip_McmePartitionGetType* const Clock_Ip_apxMcMeGetPartitions[CLOCK_IP_MC_ME_PARTITIONS_COUNT] =
{
     (volatile const Clock_Ip_McmePartitionGetType*)(PRTN0_COFB0_STAT_ADDRESS),

     (volatile const Clock_Ip_McmePartitionGetType*)( ((volatile const uint8*)&(IP_MC_ME->PRTN1_COFB0_STAT)) ),
#ifndef CLOCK_IP_DERIVATIVE_001
     (volatile const Clock_Ip_McmePartitionGetType*)( ((volatile const uint8*)&(IP_MC_ME->PRTN2_COFB0_STAT)) ),
#endif
};

volatile Clock_Ip_McmePartitionTriggerType* const Clock_Ip_apxMcMeTriggerPartitions[CLOCK_IP_MC_ME_PARTITIONS_COUNT] =
{
     (volatile Clock_Ip_McmePartitionTriggerType*)( ((volatile uint8*)&(IP_MC_ME->PRTN0_PCONF)) ),

     (volatile Clock_Ip_McmePartitionTriggerType*)( ((volatile uint8*)&(IP_MC_ME->PRTN1_PCONF)) ),
#ifndef CLOCK_IP_DERIVATIVE_001
     (volatile Clock_Ip_McmePartitionTriggerType*)( ((volatile uint8*)&(IP_MC_ME->PRTN2_PCONF)) ),
#endif
};

const Clock_Ip_ClockNameSourceType Clock_Ip_aeSourceTypeClockName[CLOCK_IP_PRODUCERS_NO] = {
    UKNOWN_TYPE,                               /*!< CLOCK_IS_OFF                            */
    IRCOSC_TYPE,                               /*!< FIRC_CLK                                */
    IRCOSC_TYPE,                               /*!< FIRC_STANDBY_CLK clock source           */
    IRCOSC_TYPE,                               /*!< SIRC_CLK                                */
    IRCOSC_TYPE,                               /*!< SIRC_STANDBY_CLK clock source           */
    XOSC_TYPE,                                 /*!< FXOSC_CLK                               */
#if defined(CLOCK_IP_HAS_SXOSC_CLK) 
    XOSC_TYPE,                                 /*!< SXOSC_CLK                               */
#endif
    PLL_TYPE,                                  /*!< PLL_CLK                                 */
    IRCOSC_TYPE,                               /*!< FIRC_POSTDIV_CLK                        */
    PLL_TYPE,                                  /*!< PLL_POSTDIV_CLK                         */
    PLL_TYPE,                                  /*!< PLL_PHI0_CLK                            */
    PLL_TYPE,                                  /*!< PLL_PHI1_CLK                            */
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
    EXT_CLK_TYPE,                              /*!< EMAC_MII_RX_CLK                         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
    EXT_CLK_TYPE,                              /*!< EMAC_MII_RMII_TX_CLK                    */
#endif
    UKNOWN_TYPE,                               /*!< SCS_CLK                                 */
    UKNOWN_TYPE,                               /*!< CORE_CLK                                */
    UKNOWN_TYPE,                               /*!< AIPS_PLAT_CLK                           */
    UKNOWN_TYPE,                               /*!< AIPS_SLOW_CLK                           */
    UKNOWN_TYPE,                               /*!< HSE_CLK                                 */
    UKNOWN_TYPE,                               /*!< DCM_CLK                                 */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
    UKNOWN_TYPE,                               /*!< LBIST_CLK                               */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
    UKNOWN_TYPE,                               /*!< QSPI_MEM_CLK                            */
#endif
    UKNOWN_TYPE,                               /*!< CLKOUT_RUN_CLK                          */
};

const Clock_Ip_NameType Clock_Ip_aeHwPllName[CLOCK_IP_HARDWARE_PLL_ARRAY_SIZE] =
{
    PLL_CLK         /* PLL_CLK clock */
};

const Clock_Ip_NameType Clock_Ip_aeHwDfsName[CLOCK_IP_HARDWARE_DFS_ARRAY_SIZE] =
{
    RESERVED_CLK,              /* RESERVED_CLK Clock */
};

const Clock_Ip_ClockExtensionType Clock_Ip_axFeatureExtensions[CLOCK_IP_EXTENSIONS_SIZE] = {
    /* Selector value mask          Selector value shift            Divider value mask           Divider value shift  */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,  MC_CGM_MUX_0_CSC_SELCTL_SHIFT,  0U,                          0U},                           /*   CLOCK_IP_SCS_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,  MC_CGM_MUX_0_CSC_SELCTL_SHIFT,  MC_CGM_MUX_0_DC_0_DIV_MASK,  MC_CGM_MUX_0_DC_0_DIV_SHIFT},  /*   CLOCK_IP_CORE_EXTENSION*/
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,  MC_CGM_MUX_0_CSC_SELCTL_SHIFT,  MC_CGM_MUX_0_DC_1_DIV_MASK,  MC_CGM_MUX_0_DC_1_DIV_SHIFT},  /*   CLOCK_IP_AIPS_PLAT_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,  MC_CGM_MUX_0_CSC_SELCTL_SHIFT,  MC_CGM_MUX_0_DC_2_DIV_MASK,  MC_CGM_MUX_0_DC_2_DIV_SHIFT},  /*   CLOCK_IP_AIPS_SLOW_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,  MC_CGM_MUX_0_CSC_SELCTL_SHIFT,  MC_CGM_MUX_0_DC_3_DIV_MASK,  MC_CGM_MUX_0_DC_3_DIV_SHIFT},  /*   CLOCK_IP_HSE_EXTENSION */
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,  MC_CGM_MUX_0_CSC_SELCTL_SHIFT,  MC_CGM_MUX_0_DC_4_DIV_MASK,  MC_CGM_MUX_0_DC_4_DIV_SHIFT},  /*   CLOCK_IP_DCM_EXTENSION */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,  MC_CGM_MUX_0_CSC_SELCTL_SHIFT,  MC_CGM_MUX_0_DC_5_DIV_MASK,  MC_CGM_MUX_0_DC_5_DIV_SHIFT},  /*   CLOCK_IP_LBIST_EXTENSION */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,  MC_CGM_MUX_0_CSC_SELCTL_SHIFT,  MC_CGM_MUX_0_DC_6_DIV_MASK,  MC_CGM_MUX_0_DC_6_DIV_SHIFT},  /*   CLOCK_IP_QSPI_MEM_EXTENSION */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    {MC_CGM_MUX_0_CSC_SELCTL_MASK,  MC_CGM_MUX_0_CSC_SELCTL_SHIFT,  MC_CGM_MUX_0_DC_7_DIV_MASK,  MC_CGM_MUX_0_DC_7_DIV_SHIFT},  /*   CLOCK_IP_CM7_CORE_EXTENSION */
#endif
    {MC_CGM_MUX_6_CSC_SELCTL_MASK,  MC_CGM_MUX_6_CSC_SELCTL_SHIFT,  MC_CGM_MUX_6_DC_0_DIV_MASK,  MC_CGM_MUX_6_DC_0_DIV_SHIFT},  /*   CLOCK_IP_RUN_EXTENSION */
    {MC_CGM_MUX_5_CSC_SELCTL_MASK,  MC_CGM_MUX_5_CSC_SELCTL_SHIFT,  MC_CGM_MUX_5_DC_0_DIV_MASK,  MC_CGM_MUX_5_DC_0_DIV_SHIFT},  /*   CLOCK_IP_CLKOUT_STANDBY_EXTENSION*/
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
    {MC_CGM_MUX_7_CSC_SELCTL_MASK,  MC_CGM_MUX_7_CSC_SELCTL_SHIFT,  MC_CGM_MUX_7_DC_0_DIV_MASK,  MC_CGM_MUX_7_DC_0_DIV_SHIFT},  /*   CLOCK_IP_EMAC_RX_EXTENSION*/
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
    {MC_CGM_MUX_9_CSC_SELCTL_MASK,  MC_CGM_MUX_9_CSC_SELCTL_SHIFT,  MC_CGM_MUX_9_DC_0_DIV_MASK,  MC_CGM_MUX_9_DC_0_DIV_SHIFT},  /*   CLOCK_IP_EMAC_TS_EXTENSION */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
    {MC_CGM_MUX_8_CSC_SELCTL_MASK,  MC_CGM_MUX_8_CSC_SELCTL_SHIFT,  MC_CGM_MUX_8_DC_0_DIV_MASK,  MC_CGM_MUX_8_DC_0_DIV_SHIFT},  /*   CLOCK_IP_EMAC_TX_EXTENSION */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_RMII_CLK)
    {MC_CGM_MUX_12_CSC_SELCTL_MASK, MC_CGM_MUX_12_CSC_SELCTL_SHIFT, MC_CGM_MUX_12_DC_0_DIV_MASK, MC_CGM_MUX_12_DC_0_DIV_SHIFT}, /*   CLOCK_IP_EMAC_TX_RMII_EXTENSION */
#endif
    {MC_CGM_MUX_3_CSC_SELCTL_MASK,  MC_CGM_MUX_3_CSC_SELCTL_SHIFT,  MC_CGM_MUX_3_DC_0_DIV_MASK,  MC_CGM_MUX_3_DC_0_DIV_SHIFT},  /*   CLOCK_IP_FLEXCANA_EXTENSION */
    {MC_CGM_MUX_4_CSC_SELCTL_MASK,  MC_CGM_MUX_4_CSC_SELCTL_SHIFT,  MC_CGM_MUX_4_DC_0_DIV_MASK,  MC_CGM_MUX_4_DC_0_DIV_SHIFT},  /*   CLOCK_IP_FLEXCANB_EXTENSION */
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
    {MC_CGM_MUX_10_CSC_SELCTL_MASK, MC_CGM_MUX_10_CSC_SELCTL_SHIFT, MC_CGM_MUX_10_DC_0_DIV_MASK, MC_CGM_MUX_10_DC_0_DIV_SHIFT}, /*   CLOCK_IP_QSPI_2XSFIF_EXTENSION */
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
    {MC_CGM_MUX_10_CSC_SELCTL_MASK, MC_CGM_MUX_10_CSC_SELCTL_SHIFT, MC_CGM_MUX_10_DC_0_DIV_MASK, MC_CGM_MUX_10_DC_0_DIV_SHIFT}, /*   CLOCK_IP_QSPI_SFCK_EXTENSION */
#endif
    {MC_CGM_MUX_1_CSC_SELCTL_MASK,  MC_CGM_MUX_1_CSC_SELCTL_SHIFT,  MC_CGM_MUX_1_DC_0_DIV_MASK,  MC_CGM_MUX_1_DC_0_DIV_SHIFT},  /*   CLOCK_IP_STMA_EXTENSION */
#if defined(CLOCK_IP_HAS_STMB_CLK)
    {MC_CGM_MUX_2_CSC_SELCTL_MASK,  MC_CGM_MUX_2_CSC_SELCTL_SHIFT,  MC_CGM_MUX_2_DC_0_DIV_MASK,  MC_CGM_MUX_2_DC_0_DIV_SHIFT},  /*   CLOCK_IP_STMB_EXTENSION */
#endif
#if defined(CLOCK_IP_HAS_STMC_CLK)
    {MC_CGM_MUX_13_CSC_SELCTL_MASK, MC_CGM_MUX_13_CSC_SELCTL_SHIFT, MC_CGM_MUX_13_DC_0_DIV_MASK, MC_CGM_MUX_13_DC_0_DIV_SHIFT}, /*   CLOCK_IP_STMC_EXTENSION */
#endif
    {MC_CGM_MUX_11_CSC_SELCTL_MASK, MC_CGM_MUX_11_CSC_SELCTL_SHIFT, MC_CGM_MUX_11_DC_0_DIV_MASK, MC_CGM_MUX_11_DC_0_DIV_SHIFT}, /*   CLOCK_IP_TRACE_EXTENSION */
#if defined(CLOCK_IP_HAS_LFAST_REF_CLK)
    {MC_CGM_MUX_15_CSC_SELCTL_MASK, MC_CGM_MUX_15_CSC_SELCTL_SHIFT, MC_CGM_MUX_15_DC_0_DIV_MASK, MC_CGM_MUX_15_DC_0_DIV_SHIFT}, /*   CLOCK_IP_LFAST_REF_EXTENSION */
#endif
#if defined(CLOCK_IP_HAS_SWG_CLK)
    {MC_CGM_MUX_16_CSC_SELCTL_MASK, MC_CGM_MUX_16_CSC_SELCTL_SHIFT, MC_CGM_MUX_16_DC_0_DIV_MASK, MC_CGM_MUX_16_DC_0_DIV_SHIFT}, /*   CLOCK_IP_SWG_EXTENSION */
#endif
};


Clock_Ip_GateInfoType const Clock_Ip_axGateInfo[CLOCK_IP_GATE_INFO_SIZE] =  {
    /* Partition value index            Selector value index            Request value shift                    Request value mask  */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ40_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ40_MASK},      /*   ADC0_CLK clock             */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ41_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ41_MASK},      /*   ADC1_CLK clock             */
#if defined(CLOCK_IP_HAS_ADC2_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ42_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ42_MASK},      /*   ADC2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC3_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN3_COFB1_CLKEN_REQ61_SHIFT,   MC_ME_PRTN3_COFB1_CLKEN_REQ61_MASK},      /*   ADC3_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC4_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN3_COFB1_CLKEN_REQ62_SHIFT,   MC_ME_PRTN3_COFB1_CLKEN_REQ62_MASK},      /*   ADC4_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC5_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN3_COFB1_CLKEN_REQ63_SHIFT,   MC_ME_PRTN3_COFB1_CLKEN_REQ63_MASK},      /*   ADC5_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_ADC6_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN3_COFB2_CLKEN_REQ64_SHIFT,   MC_ME_PRTN3_COFB2_CLKEN_REQ64_MASK},      /*   ADC6_CLK clock             */
#endif
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ33_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ33_MASK},      /*   BCTU0_CLK clock            */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ92_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ92_MASK},      /*   CMP0_CLK clock             */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ93_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ93_MASK},      /*   CMP1_CLK clock             */
#if defined(CLOCK_IP_HAS_CMP2_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ58_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ58_MASK},      /*   CMP2_CLK clock             */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_3_INDEX,    MC_ME_PRTN1_COFB3_CLKEN_REQ96_SHIFT,   MC_ME_PRTN1_COFB3_CLKEN_REQ96_MASK},      /*   CRC0_CLK clock             */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN1_COFB1_CLKEN_REQ32_SHIFT,   MC_ME_PRTN1_COFB1_CLKEN_REQ32_MASK},      /*   DMAMUX0_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN1_COFB1_CLKEN_REQ33_SHIFT,   MC_ME_PRTN1_COFB1_CLKEN_REQ33_MASK},      /*   DMAMUX1_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ3_SHIFT,    MC_ME_PRTN1_COFB0_CLKEN_REQ3_MASK},       /*   EDMA0_CLK clock            */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ4_SHIFT,    MC_ME_PRTN1_COFB0_CLKEN_REQ4_MASK},       /*   EDMA0_TCD0_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ5_SHIFT,    MC_ME_PRTN1_COFB0_CLKEN_REQ5_MASK},       /*   EDMA0_TCD1_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ6_SHIFT,    MC_ME_PRTN1_COFB0_CLKEN_REQ6_MASK},       /*   EDMA0_TCD2_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ7_SHIFT,    MC_ME_PRTN1_COFB0_CLKEN_REQ7_MASK},       /*   EDMA0_TCD3_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ8_SHIFT,    MC_ME_PRTN1_COFB0_CLKEN_REQ8_MASK},       /*   EDMA0_TCD4_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ9_SHIFT,    MC_ME_PRTN1_COFB0_CLKEN_REQ9_MASK},       /*   EDMA0_TCD5_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ10_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ10_MASK},      /*   EDMA0_TCD6_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ11_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ11_MASK},      /*   EDMA0_TCD7_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ12_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ12_MASK},      /*   EDMA0_TCD8_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ13_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ13_MASK},      /*   EDMA0_TCD9_CLK clock       */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ14_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ14_MASK},      /*   EDMA0_TCD10_CLK clock      */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ15_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ15_MASK},      /*   EDMA0_TCD11_CLK clock      */
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ4_SHIFT,    MC_ME_PRTN2_COFB0_CLKEN_REQ4_MASK},       /*   EDMA0_TCD12_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ5_SHIFT,    MC_ME_PRTN2_COFB0_CLKEN_REQ5_MASK},       /*   EDMA0_TCD13_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ6_SHIFT,    MC_ME_PRTN2_COFB0_CLKEN_REQ6_MASK},       /*   EDMA0_TCD14_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ7_SHIFT,    MC_ME_PRTN2_COFB0_CLKEN_REQ7_MASK},       /*   EDMA0_TCD15_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ8_SHIFT,    MC_ME_PRTN2_COFB0_CLKEN_REQ8_MASK},       /*   EDMA0_TCD16_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ9_SHIFT,    MC_ME_PRTN2_COFB0_CLKEN_REQ9_MASK},       /*   EDMA0_TCD17_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ10_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ10_MASK},      /*   EDMA0_TCD18_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ11_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ11_MASK},      /*   EDMA0_TCD19_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ12_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ12_MASK},      /*   EDMA0_TCD20_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ13_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ13_MASK},      /*   EDMA0_TCD21_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ14_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ14_MASK},      /*   EDMA0_TCD22_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ15_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ15_MASK},      /*   EDMA0_TCD23_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ16_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ16_MASK},      /*   EDMA0_TCD24_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ17_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ17_MASK},      /*   EDMA0_TCD25_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ18_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ18_MASK},      /*   EDMA0_TCD26_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ19_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ19_MASK},      /*   EDMA0_TCD27_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ20_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ20_MASK},      /*   EDMA0_TCD28_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ21_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ21_MASK},      /*   EDMA0_TCD29_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ22_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ22_MASK},      /*   EDMA0_TCD30_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ23_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ23_MASK},      /*   EDMA0_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)  
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ22_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ22_MASK},      /*   EIM_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM0_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN2_COFB2_CLKEN_REQ67_SHIFT,   MC_ME_PRTN2_COFB2_CLKEN_REQ67_MASK},      /*   EIM0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN2_COFB2_CLKEN_REQ68_SHIFT,   MC_ME_PRTN2_COFB2_CLKEN_REQ68_MASK},      /*   EIM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EIM2_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN2_COFB2_CLKEN_REQ69_SHIFT,   MC_ME_PRTN2_COFB2_CLKEN_REQ69_MASK},      /*   EIM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ32_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ32_MASK},      /*   EMAC0_RX_CLK clock         */
#endif
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ34_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ34_MASK},      /*   EMIOS0_CLK clock           */
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ35_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ35_MASK},      /*   EMIOS1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ36_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ36_MASK},      /*   EMIOS2_CLK clock           */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ23_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ23_MASK},      /*   ERM0_CLK clock             */
#if defined(CLOCK_IP_HAS_ERM1_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN0_COFB0_CLKEN_REQ3_SHIFT,    MC_ME_PRTN0_COFB0_CLKEN_REQ3_MASK},       /*   ERM0_CLK clock             */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ65_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ65_MASK},      /*   FLEXCAN0_CLK clock         */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ66_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ66_MASK},      /*   FLEXCAN1_CLK clock         */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ67_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ67_MASK},      /*   FLEXCAN2_CLK clock         */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ68_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ68_MASK},      /*   FLEXCAN3_CLK clock         */
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ69_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ69_MASK},      /*   FLEXCAN4_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ70_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ70_MASK},      /*   FLEXCAN5_CLK clock         */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ73_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ73_MASK},      /*   FLEXIO0_CLK clock          */
#if defined(CLOCK_IP_HAS_I3C0_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ48_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ48_MASK},      /*   I3C0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_I3C1_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ49_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ49_MASK},      /*   I3C0_CLK clock             */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ31_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ31_MASK},      /*   INTM_CLK clock             */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ38_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ38_MASK},      /*   LCU0_CLK clock             */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ39_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ39_MASK},      /*   LCU1_CLK clock             */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ84_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ84_MASK},      /*   LPI2C0_CLK clock           */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ85_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ85_MASK},      /*   LPI2C1_CLK clock           */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ86_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ86_MASK},      /*   LPSPI0_CLK clock           */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ87_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ87_MASK},      /*   LPSPI1_CLK clock           */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ88_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ88_MASK},      /*   LPSPI2_CLK clock           */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ89_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ89_MASK},      /*   LPSPI3_CLK clock           */
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ47_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ47_MASK},      /*   LPSPI4_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ48_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ48_MASK},      /*   LPSPI5_CLK clock           */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ74_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ74_MASK},      /*   LPUART0_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ75_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ75_MASK},      /*   LPUART1_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ76_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ76_MASK},      /*   LPUART2_CLK clock          */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ77_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ77_MASK},      /*   LPUART3_CLK clock          */
#if defined(CLOCK_IP_HAS_LPUART4_CLK) 
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ78_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ78_MASK},      /*   LPUART4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK) 
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ79_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ79_MASK},      /*   LPUART5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK) 
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ80_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ80_MASK},      /*   LPUART6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK) 
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ81_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ81_MASK},      /*   LPUART7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ35_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ35_MASK},      /*   LPUART8_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ36_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ36_MASK},      /*   LPUART9_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ37_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ37_MASK},      /*   LPUART10_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ38_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ38_MASK},      /*   LPUART11_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ39_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ39_MASK},      /*   LPUART12_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ40_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ40_MASK},      /*   LPUART13_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ41_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ41_MASK},      /*   LPUART14_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ42_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ42_MASK},      /*   LPUART15_CLK clock         */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ24_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ24_MASK},      /*   MSCM_CLK clock             */
#if defined(CLOCK_IP_HAS_MUA_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ46_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ46_MASK},      /*   MUA_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MUB_CLK)
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ47_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ47_MASK},      /*   MUB_CLK clock              */
#endif
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ44_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ44_MASK},      /*   PIT0_CLK clock             */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ45_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ45_MASK},      /*   PIT1_CLK clock             */
#if defined(CLOCK_IP_HAS_PIT2_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN1_COFB1_CLKEN_REQ63_SHIFT,   MC_ME_PRTN1_COFB1_CLKEN_REQ63_MASK},      /*   PIT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ51_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ51_MASK},      /*   QSPI0_RAM_CLK clock        */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN1_COFB1_CLKEN_REQ34_SHIFT,   MC_ME_PRTN1_COFB1_CLKEN_REQ34_MASK},      /*   RTC0_CLK clock             */
#if defined(CLOCK_IP_HAS_SAI0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ91_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ91_MASK},      /*   SAI0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ55_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ55_MASK},      /*   SAI1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ24_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ24_MASK},      /*   SEMA42_CLK clock           */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN1_COFB1_CLKEN_REQ42_SHIFT,   MC_ME_PRTN1_COFB1_CLKEN_REQ42_MASK},      /*   SIUL0_CLK clock            */
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ29_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ29_MASK},      /*   STM0_CLK clock             */
#if defined(CLOCK_IP_HAS_STM1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ29_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ29_MASK},      /*   STM1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM2_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ29_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ29_MASK},      /*   STM2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG0_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN3_COFB1_CLKEN_REQ50_SHIFT,   MC_ME_PRTN3_COFB1_CLKEN_REQ50_MASK},      /*   SWG0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SWG1_CLK)
    {CLOCK_IP_PARTITION_3_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN3_COFB1_CLKEN_REQ51_SHIFT,   MC_ME_PRTN3_COFB1_CLKEN_REQ51_MASK},      /*   SWG1_CLK clock             */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN1_COFB0_CLKEN_REQ28_SHIFT,   MC_ME_PRTN1_COFB0_CLKEN_REQ28_MASK},      /*   SWT0_CLK clock             */
#if defined(CLOCK_IP_HAS_SWT1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_0_INDEX,    MC_ME_PRTN2_COFB0_CLKEN_REQ27_SHIFT,   MC_ME_PRTN2_COFB0_CLKEN_REQ27_MASK},      /*   SWT1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_0_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ62_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ62_MASK},      /*   TCM_CM7_0_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_1_CLK)
    {CLOCK_IP_PARTITION_2_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN2_COFB1_CLKEN_REQ63_SHIFT,   MC_ME_PRTN2_COFB1_CLKEN_REQ63_MASK},      /*   TCM_CM7_1_CLK clock        */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_2_INDEX,    MC_ME_PRTN1_COFB2_CLKEN_REQ95_SHIFT,   MC_ME_PRTN1_COFB2_CLKEN_REQ95_MASK},      /*   TEMPSENSE_CLK clock        */
    {CLOCK_IP_PARTITION_0_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN0_COFB1_CLKEN_REQ32_SHIFT,   MC_ME_PRTN0_COFB1_CLKEN_REQ32_MASK},      /*   TRGMUX0_CLK clock          */
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN1_COFB1_CLKEN_REQ49_SHIFT,   MC_ME_PRTN1_COFB1_CLKEN_REQ49_MASK},      /*   TSENSE0_CLK clock          */
#endif
    {CLOCK_IP_PARTITION_1_INDEX,       CLOCK_IP_COLLECTION_1_INDEX,    MC_ME_PRTN1_COFB1_CLKEN_REQ45_SHIFT,   MC_ME_PRTN1_COFB1_CLKEN_REQ45_MASK},      /*   WKPU0_CLK clock            */
};



/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/




#ifdef __cplusplus
}
#endif

/** @} */

