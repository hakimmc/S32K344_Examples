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
*   @file       Clock_Ip_Frequency.c
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

#if (defined(CLOCK_IP_GET_FREQUENCY_API) && (CLOCK_IP_GET_FREQUENCY_API == STD_ON))


/*==================================================================================================
*                                     SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_FREQUENCY_VENDOR_ID_C                      43
#define CLOCK_IP_FREQUENCY_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_FREQUENCY_AR_RELEASE_MINOR_VERSION_C       4
#define CLOCK_IP_FREQUENCY_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_FREQUENCY_SW_MAJOR_VERSION_C               2
#define CLOCK_IP_FREQUENCY_SW_MINOR_VERSION_C               0
#define CLOCK_IP_FREQUENCY_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Frequency.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_FREQUENCY_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Frequency.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Frequency.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_FREQUENCY_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Frequency.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Frequency.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_FREQUENCY_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_FREQUENCY_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Frequency.c and Clock_Ip_Private.h are different"
#endif
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

typedef struct{

    Clock_Ip_NameType Name;
    uint32 Frequency;

}extSignalFreq;

typedef uint32 (*getFreqType)(void);

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

#define CLOCK_IP_SELECTOR_SOURCE_NO  64U
#define CLOCK_IP_SELECTOR_SOURCE_PRODUCER_NO 9U
#define CLOCK_IP_RTC_SELECTOR_SOURCE_NO  4U
#define CLOCK_IP_FIRC_DIV_SEL_VALS_NO  4U

#if (!defined(CLOCK_IP_DERIVATIVE_001))
#define CLOCK_IP_EXT_SIGNALS_NO      2U
#else
#define CLOCK_IP_EXT_SIGNALS_NO      1U
#endif

#define CLOCK_IP_MUL_BY_16384        14U
#define CLOCK_IP_MUL_BY_2048         11U
#define CLOCK_IP_DISABLED            0U
#define CLOCK_IP_ENABLED             0xFFFFFFFFU

#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
#define CLOCK_IP_EMAC_MII_REF_CLK_INDEX_ENTRY       0U
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
#define CLOCK_IP_EMAC_MII_RMII_TX_INDEX_ENTRY       1U
#endif

#define CLOCK_IP_PLL_FREQ                        2000000000U
#define CLOCK_IP_PLL_CHECKSUM                    4147U
/*==================================================================================================
*                                    GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

uint32 Clock_Ip_Get_RTC_CLK_Frequency_TrustedCall(void);
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static uint32 Clock_Ip_Get_Zero_Frequency(void);
static uint32 Clock_Ip_Get_FIRC_CLK_Frequency(void);
static uint32 Clock_Ip_Get_FIRC_STANDBY_CLK_Frequency(void);
static uint32 Clock_Ip_Get_SIRC_CLK_Frequency(void);
static uint32 Clock_Ip_Get_SIRC_STANDBY_CLK_Frequency(void);
static uint32 Clock_Ip_Get_FXOSC_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
static uint32 Clock_Ip_Get_SXOSC_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_PLL_CLK_Frequency(void);
static uint32 Clock_Ip_Get_FIRC_POSTDIV_CLK_Frequency(void);
static uint32 Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency(void);
static uint32 Clock_Ip_Get_PLL_PHI0_Frequency(void);
static uint32 Clock_Ip_Get_PLL_PHI1_Frequency(void);
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
static uint32 Clock_Ip_Get_emac_mii_rx_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
static uint32 Clock_Ip_Get_emac_mii_rmii_tx_Frequency(void);
#endif
static uint32 Clock_Ip_Get_SCS_CLK_Frequency(void);
static uint32 Clock_Ip_Get_CORE_CLK_Frequency(void);
static uint32 Clock_Ip_Get_AIPS_PLAT_CLK_Frequency(void);
static uint32 Clock_Ip_Get_AIPS_SLOW_CLK_Frequency(void);
static uint32 Clock_Ip_Get_HSE_CLK_Frequency(void);
static uint32 Clock_Ip_Get_DCM_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_LBIST_CLK)
static uint32 Clock_Ip_Get_LBIST_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
static uint32 Clock_Ip_Get_QSPI_MEM_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
static uint32 Clock_Ip_Get_CM7_CORE_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_CLKOUT_RUN_CLK_Frequency(void);
static uint32 Clock_Ip_Get_ADC0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_ADC1_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_ADC2_CLK)
static uint32 Clock_Ip_Get_ADC2_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_BCTU0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_CLKOUT_STANDBY_CLK_Frequency(void);
static uint32 Clock_Ip_Get_CMP0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_CMP1_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_CMP2_CLK)
static uint32 Clock_Ip_Get_CMP2_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_CRC0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_DCM_CLK_Frequency(void);
static uint32 Clock_Ip_Get_DMAMUX0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_DMAMUX1_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD1_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD2_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD3_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD4_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD5_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD6_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD7_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD8_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD9_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD10_CLK_Frequency(void);
static uint32 Clock_Ip_Get_EDMA0_TCD11_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD12_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD13_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD14_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD15_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD16_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD17_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD18_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD19_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD20_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD21_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD22_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD23_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD24_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD25_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD26_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD27_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD28_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD29_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD30_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
static uint32 Clock_Ip_Get_EDMA0_TCD31_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
static uint32 Clock_Ip_Get_EIM_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
static uint32 Clock_Ip_Get_EMAC_RX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
static uint32 Clock_Ip_Get_EMAC0_RX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
static uint32 Clock_Ip_Get_EMAC_TS_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
static uint32 Clock_Ip_Get_EMAC0_TS_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
static uint32 Clock_Ip_Get_EMAC_TX_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
static uint32 Clock_Ip_Get_EMAC0_TX_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_EMIOS0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
static uint32 Clock_Ip_Get_EMIOS1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
static uint32 Clock_Ip_Get_EMIOS2_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_ERM0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_FLEXCANA_CLK_Frequency(void);
static uint32 Clock_Ip_Get_FLEXCAN0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_FLEXCAN1_CLK_Frequency(void);
static uint32 Clock_Ip_Get_FLEXCAN2_CLK_Frequency(void);
static uint32 Clock_Ip_Get_FLEXCANB_CLK_Frequency(void);
static uint32 Clock_Ip_Get_FLEXCAN3_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
static uint32 Clock_Ip_Get_FLEXCAN4_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
static uint32 Clock_Ip_Get_FLEXCAN5_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_FLEXIO0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_I3C0_CLK)
static uint32 Clock_Ip_Get_I3C0_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_INTM_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LCU0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LCU1_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LPI2C0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LPI2C1_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LPSPI0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LPSPI1_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LPSPI2_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LPSPI3_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
static uint32 Clock_Ip_Get_LPSPI4_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
static uint32 Clock_Ip_Get_LPSPI5_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_LPUART0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LPUART1_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LPUART2_CLK_Frequency(void);
static uint32 Clock_Ip_Get_LPUART3_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
static uint32 Clock_Ip_Get_LPUART4_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
static uint32 Clock_Ip_Get_LPUART5_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
static uint32 Clock_Ip_Get_LPUART6_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
static uint32 Clock_Ip_Get_LPUART7_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
static uint32 Clock_Ip_Get_LPUART8_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
static uint32 Clock_Ip_Get_LPUART9_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
static uint32 Clock_Ip_Get_LPUART10_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
static uint32 Clock_Ip_Get_LPUART11_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
static uint32 Clock_Ip_Get_LPUART12_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
static uint32 Clock_Ip_Get_LPUART13_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
static uint32 Clock_Ip_Get_LPUART14_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
static uint32 Clock_Ip_Get_LPUART15_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_MSCM_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_MUA_CLK)
static uint32 Clock_Ip_Get_MUA_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_MUB_CLK)
static uint32 Clock_Ip_Get_MUB_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_PIT0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_PIT1_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_PIT2_CLK)
static uint32 Clock_Ip_Get_PIT2_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
static uint32 Clock_Ip_Get_QSPI0_RAM_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
static uint32 Clock_Ip_Get_QSPI_SFCK_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
static uint32 Clock_Ip_Get_QSPI_2XSFIF_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI0_SFCK_CLK)
static uint32 Clock_Ip_Get_QSPI0_SFCK_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
static uint32 Clock_Ip_Get_QSPI0_TX_MEM_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_RTC_CLK_Frequency(void);
static uint32 Clock_Ip_Get_RTC0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_SAI0_CLK)
static uint32 Clock_Ip_Get_SAI0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
static uint32 Clock_Ip_Get_SAI1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
static uint32 Clock_Ip_Get_SEMA42_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_SIUL0_CLK_Frequency(void);
static uint32 Clock_Ip_Get_AIPS_SLOW_CLK_Frequency(void);
static uint32 Clock_Ip_Get_STMA_CLK_Frequency(void);
static uint32 Clock_Ip_Get_STM0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_STMB_CLK)
static uint32 Clock_Ip_Get_STMB_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
static uint32 Clock_Ip_Get_STM1_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_SWT0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_SWT1_CLK)
static uint32 Clock_Ip_Get_SWT1_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_0_CLK)
static uint32 Clock_Ip_Get_TCM_CM7_0_CLK_Frequency(void);
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_1_CLK)
static uint32 Clock_Ip_Get_TCM_CM7_1_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_TEMPSENSE_CLK_Frequency(void);
static uint32 Clock_Ip_Get_TRACE_CLK_Frequency(void);
static uint32 Clock_Ip_Get_TRGMUX0_CLK_Frequency(void);
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
static uint32 Clock_Ip_Get_TSENSE0_CLK_Frequency(void);
#endif
static uint32 Clock_Ip_Get_WKPU0_CLK_Frequency(void);


static uint32 Clock_Ip_PLL_VCO(const PLL_Type *Base);


/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

static const uint32 Clock_Ip_u32EnableClock[2U] = {CLOCK_IP_DISABLED,CLOCK_IP_ENABLED};
static const uint32 Clock_Ip_u32EnableDivider[2U] = {CLOCK_IP_DISABLED,CLOCK_IP_ENABLED};
static const uint32 Clock_Ip_u32EnableGate[2U] = {CLOCK_IP_DISABLED,CLOCK_IP_ENABLED};

static const getFreqType Clock_Ip_apfTableProducerClkSrc[CLOCK_IP_SELECTOR_SOURCE_PRODUCER_NO] =
{
    Clock_Ip_Get_FIRC_POSTDIV_CLK_Frequency,      /* clock name for 0  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 1  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 2  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 3  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 4  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 5  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 6  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 7  hardware value */
    Clock_Ip_Get_PLL_PHI0_Frequency,              /* clock name for 8  hardware value */
};

static const getFreqType Clock_Ip_apfFreqTableClkSrc[CLOCK_IP_SELECTOR_SOURCE_NO] =
{
    Clock_Ip_Get_FIRC_POSTDIV_CLK_Frequency,      /* clock name for 0  hardware value */
    Clock_Ip_Get_SIRC_CLK_Frequency,              /* clock name for 1  hardware value */
    Clock_Ip_Get_FXOSC_CLK_Frequency,             /* clock name for 2  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 3  hardware value */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    Clock_Ip_Get_SXOSC_CLK_Frequency,             /* clock name for 4  hardware value */
#else
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 4 hardware value */
#endif
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 5  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 6  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 7  hardware value */
    Clock_Ip_Get_PLL_PHI0_Frequency,              /* clock name for 8  hardware value */
    Clock_Ip_Get_PLL_PHI1_Frequency,              /* clock name for 9  hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 10 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 11 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 12 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 13 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 14 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 15 hardware value */
    Clock_Ip_Get_CORE_CLK_Frequency,              /* clock name for 16 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 17 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 18 hardware value */
    Clock_Ip_Get_HSE_CLK_Frequency,               /* clock name for 19 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 20 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 21 hardware value */
    Clock_Ip_Get_AIPS_PLAT_CLK_Frequency,         /* clock name for 22 hardware value */
    Clock_Ip_Get_AIPS_SLOW_CLK_Frequency,         /* clock name for 23 hardware value */
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
    Clock_Ip_Get_emac_mii_rmii_tx_Frequency,      /* clock name for 24 hardware value */
#else
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 24 hardware value */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
    Clock_Ip_Get_emac_mii_rx_Frequency,           /* clock name for 25 hardware value */
#else
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 25 hardware value */
#endif
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 26 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 27 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 28 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 29 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 30 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 31 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 32 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 33 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 34 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 35 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 36 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 37 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 38 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 39 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 40 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 41 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 42 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 43 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 44 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 45 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 46 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 47 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 48 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 49 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 50 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 51 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 52 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 53 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 54 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 55 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 56 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 57 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 58 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 59 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 60 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 61 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 62 hardware value */
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 63 hardware value */
};

static const getFreqType Clock_Ip_apfFreqTableRtcClkSrc[CLOCK_IP_RTC_SELECTOR_SOURCE_NO] =
{
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    Clock_Ip_Get_SXOSC_CLK_Frequency,             /* clock name for 0  hardware value */
#else
    Clock_Ip_Get_Zero_Frequency,                  /* clock name for 0 hardware value */
#endif
    Clock_Ip_Get_SIRC_CLK_Frequency,              /* clock name for 1  hardware value */
    Clock_Ip_Get_FIRC_POSTDIV_CLK_Frequency,      /* clock name for 2  hardware value */
    Clock_Ip_Get_FXOSC_CLK_Frequency,             /* clock name for 3  hardware value */
};

static const getFreqType Clock_Ip_apfFreqTable[CLOCK_IP_NAMES_NO] =
{
    Clock_Ip_Get_Zero_Frequency,                           /* CLOCK_IS_OFF               */
    Clock_Ip_Get_FIRC_CLK_Frequency,                       /* FIRC_CLK                   */
    Clock_Ip_Get_FIRC_STANDBY_CLK_Frequency,               /* FIRC_STANDBY_CLK clock     */
    Clock_Ip_Get_SIRC_CLK_Frequency,                       /* SIRC_CLK                   */
    Clock_Ip_Get_SIRC_STANDBY_CLK_Frequency,               /* SIRC_STANDBY_CLK clock     */
    Clock_Ip_Get_FXOSC_CLK_Frequency,                      /* FXOSC_CLK                  */
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
    Clock_Ip_Get_SXOSC_CLK_Frequency,                      /* SXOSC_CLK                  */
#endif
    Clock_Ip_Get_PLL_CLK_Frequency,                        /* PLL_CLK clock              */
    Clock_Ip_Get_FIRC_POSTDIV_CLK_Frequency,               /* FIRC_POSTDIV_CLK clock     */
    Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency,                /* PLL_POSTDIV_CLK clock      */
    Clock_Ip_Get_PLL_PHI0_Frequency,                       /* PLL_PHI0 clock             */
    Clock_Ip_Get_PLL_PHI1_Frequency,                       /* PLL_PHI1 clock             */
#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
    Clock_Ip_Get_emac_mii_rx_Frequency,                    /* emac_mii_rx clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
    Clock_Ip_Get_emac_mii_rmii_tx_Frequency,               /* emac_mii_rmii_tx clock     */
#endif
    Clock_Ip_Get_SCS_CLK_Frequency,                        /* SCS_CLK clock              */
    Clock_Ip_Get_CORE_CLK_Frequency,                       /* CORE_CLK clock             */
    Clock_Ip_Get_AIPS_PLAT_CLK_Frequency,                  /* AIPS_PLAT_CLK clock        */
    Clock_Ip_Get_AIPS_SLOW_CLK_Frequency,                  /* AIPS_SLOW_CLK clock        */
    Clock_Ip_Get_HSE_CLK_Frequency,                        /* HSE_CLK clock              */
    Clock_Ip_Get_DCM_CLK_Frequency,                        /* DCM_CLK clock              */
#if defined(CLOCK_IP_HAS_LBIST_CLK)
    Clock_Ip_Get_LBIST_CLK_Frequency,                      /* LBIST_CLK clock            */
#endif
#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
    Clock_Ip_Get_QSPI_MEM_CLK_Frequency,                   /* QSPI_MEM_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
    Clock_Ip_Get_CM7_CORE_CLK_Frequency,                   /* CM7_CORE_CLK clock         */
#endif
    Clock_Ip_Get_CLKOUT_RUN_CLK_Frequency,                 /* CLKOUT_RUN_CLK clock         */
    NULL_PTR,                                     /* THE_LAST_PRODUCER_CLK      */
    Clock_Ip_Get_ADC0_CLK_Frequency,                       /* ADC0_CLK clock             */
    Clock_Ip_Get_ADC1_CLK_Frequency,                       /* ADC1_CLK clock             */
#if defined(CLOCK_IP_HAS_ADC2_CLK)
    Clock_Ip_Get_ADC2_CLK_Frequency,                       /* ADC2_CLK clock             */
#endif
    Clock_Ip_Get_BCTU0_CLK_Frequency,                      /* BCTU0_CLK clock            */
    Clock_Ip_Get_CLKOUT_STANDBY_CLK_Frequency,             /* CLKOUT_STANDBY_CLK clock   */
    Clock_Ip_Get_CMP0_CLK_Frequency,                       /* CMP0_CLK clock             */
    Clock_Ip_Get_CMP1_CLK_Frequency,                       /* CMP1_CLK clock             */
#if defined(CLOCK_IP_HAS_CMP2_CLK)
    Clock_Ip_Get_CMP2_CLK_Frequency,                       /* CMP2_CLK clock             */
#endif
    Clock_Ip_Get_CRC0_CLK_Frequency,                       /* CRC0_CLK clock             */
    Clock_Ip_Get_DCM_CLK_Frequency,                        /* DCM0_CLK clock             */
    Clock_Ip_Get_DMAMUX0_CLK_Frequency,                    /* DMAMUX0_CLK clock          */
    Clock_Ip_Get_DMAMUX1_CLK_Frequency,                    /* DMAMUX1_CLK clock          */
    Clock_Ip_Get_EDMA0_CLK_Frequency,                      /* EDMA0_CLK clock            */
    Clock_Ip_Get_EDMA0_TCD0_CLK_Frequency,                 /* EDMA0_TCD0_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD1_CLK_Frequency,                 /* EDMA0_TCD1_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD2_CLK_Frequency,                 /* EDMA0_TCD2_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD3_CLK_Frequency,                 /* EDMA0_TCD3_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD4_CLK_Frequency,                 /* EDMA0_TCD4_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD5_CLK_Frequency,                 /* EDMA0_TCD5_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD6_CLK_Frequency,                 /* EDMA0_TCD6_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD7_CLK_Frequency,                 /* EDMA0_TCD7_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD8_CLK_Frequency,                 /* EDMA0_TCD8_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD9_CLK_Frequency,                 /* EDMA0_TCD9_CLK clock       */
    Clock_Ip_Get_EDMA0_TCD10_CLK_Frequency,                /* EDMA0_TCD10_CLK clock      */
    Clock_Ip_Get_EDMA0_TCD11_CLK_Frequency,                /* EDMA0_TCD11_CLK clock      */
#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
    Clock_Ip_Get_EDMA0_TCD12_CLK_Frequency,                /* EDMA0_TCD12_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
    Clock_Ip_Get_EDMA0_TCD13_CLK_Frequency,                /* EDMA0_TCD13_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
    Clock_Ip_Get_EDMA0_TCD14_CLK_Frequency,                /* EDMA0_TCD14_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
    Clock_Ip_Get_EDMA0_TCD15_CLK_Frequency,                /* EDMA0_TCD15_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
    Clock_Ip_Get_EDMA0_TCD16_CLK_Frequency,                /* EDMA0_TCD16_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
    Clock_Ip_Get_EDMA0_TCD17_CLK_Frequency,                /* EDMA0_TCD17_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
    Clock_Ip_Get_EDMA0_TCD18_CLK_Frequency,                /* EDMA0_TCD18_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
    Clock_Ip_Get_EDMA0_TCD19_CLK_Frequency,                /* EDMA0_TCD19_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
    Clock_Ip_Get_EDMA0_TCD20_CLK_Frequency,                /* EDMA0_TCD20_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
    Clock_Ip_Get_EDMA0_TCD21_CLK_Frequency,                /* EDMA0_TCD21_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
    Clock_Ip_Get_EDMA0_TCD22_CLK_Frequency,                /* EDMA0_TCD22_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
    Clock_Ip_Get_EDMA0_TCD23_CLK_Frequency,                /* EDMA0_TCD23_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
    Clock_Ip_Get_EDMA0_TCD24_CLK_Frequency,                /* EDMA0_TCD24_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
    Clock_Ip_Get_EDMA0_TCD25_CLK_Frequency,                /* EDMA0_TCD25_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
    Clock_Ip_Get_EDMA0_TCD26_CLK_Frequency,                /* EDMA0_TCD26_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
    Clock_Ip_Get_EDMA0_TCD27_CLK_Frequency,                /* EDMA0_TCD27_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
    Clock_Ip_Get_EDMA0_TCD28_CLK_Frequency,                /* EDMA0_TCD28_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
    Clock_Ip_Get_EDMA0_TCD29_CLK_Frequency,                /* EDMA0_TCD29_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
    Clock_Ip_Get_EDMA0_TCD30_CLK_Frequency,                /* EDMA0_TCD30_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
    Clock_Ip_Get_EDMA0_TCD31_CLK_Frequency,                /* EDMA0_TCD31_CLK clock      */
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
    Clock_Ip_Get_EIM_CLK_Frequency,                        /* EIM_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
    Clock_Ip_Get_EMAC_RX_CLK_Frequency,                    /* EMAC_RX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
    Clock_Ip_Get_EMAC0_RX_CLK_Frequency,                   /* EMAC0_RX_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
    Clock_Ip_Get_EMAC_TS_CLK_Frequency,                    /* EMAC_TS_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
    Clock_Ip_Get_EMAC0_TS_CLK_Frequency,                   /* EMAC0_TS_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
    Clock_Ip_Get_EMAC_TX_CLK_Frequency,                    /* EMAC_TX_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
    Clock_Ip_Get_EMAC0_TX_CLK_Frequency,                   /* EMAC0_TX_CLK clock         */
#endif
    Clock_Ip_Get_EMIOS0_CLK_Frequency,                     /* EMIOS0_CLK clock           */
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
    Clock_Ip_Get_EMIOS1_CLK_Frequency,                     /* EMIOS1_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
    Clock_Ip_Get_EMIOS2_CLK_Frequency,                     /* EMIOS2_CLK clock           */
#endif
    Clock_Ip_Get_ERM0_CLK_Frequency,                       /* ERM0_CLK clock             */
    Clock_Ip_Get_AIPS_SLOW_CLK_Frequency,                  /* FLASH0_CLK clock           */
    Clock_Ip_Get_FLEXCANA_CLK_Frequency,                   /* FLEXCANA_CLK clock         */
    Clock_Ip_Get_FLEXCAN0_CLK_Frequency,                   /* FLEXCAN0_CLK clock         */
    Clock_Ip_Get_FLEXCAN1_CLK_Frequency,                   /* FLEXCAN1_CLK clock         */
    Clock_Ip_Get_FLEXCAN2_CLK_Frequency,                   /* FLEXCAN2_CLK clock         */
    Clock_Ip_Get_FLEXCANB_CLK_Frequency,                   /* FLEXCANB_CLK clock         */
    Clock_Ip_Get_FLEXCAN3_CLK_Frequency,                   /* FLEXCAN3_CLK clock         */
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
    Clock_Ip_Get_FLEXCAN4_CLK_Frequency,                   /* FLEXCAN4_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
    Clock_Ip_Get_FLEXCAN5_CLK_Frequency,                   /* FLEXCAN5_CLK clock         */
#endif
    Clock_Ip_Get_FLEXIO0_CLK_Frequency,                    /* FLEXIO0_CLK clock          */
#if defined(CLOCK_IP_HAS_I3C0_CLK)
    Clock_Ip_Get_I3C0_CLK_Frequency,                       /* I3C0_CLK clock             */
#endif
    Clock_Ip_Get_INTM_CLK_Frequency,                       /* INTM_CLK clock             */
    Clock_Ip_Get_LCU0_CLK_Frequency,                       /* LCU0_CLK clock             */
    Clock_Ip_Get_LCU1_CLK_Frequency,                       /* LCU1_CLK clock             */
    Clock_Ip_Get_LPI2C0_CLK_Frequency,                     /* LPI2C0_CLK clock           */
    Clock_Ip_Get_LPI2C1_CLK_Frequency,                     /* LPI2C1_CLK clock           */
    Clock_Ip_Get_LPSPI0_CLK_Frequency,                     /* LPSPI0_CLK clock           */
    Clock_Ip_Get_LPSPI1_CLK_Frequency,                     /* LPSPI1_CLK clock           */
    Clock_Ip_Get_LPSPI2_CLK_Frequency,                     /* LPSPI2_CLK clock           */
    Clock_Ip_Get_LPSPI3_CLK_Frequency,                     /* LPSPI3_CLK clock           */
#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
    Clock_Ip_Get_LPSPI4_CLK_Frequency,                     /* LPSPI4_CLK clock           */
#endif
#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
    Clock_Ip_Get_LPSPI5_CLK_Frequency,                     /* LPSPI5_CLK clock           */
#endif
    Clock_Ip_Get_LPUART0_CLK_Frequency,                    /* LPUART0_CLK clock          */
    Clock_Ip_Get_LPUART1_CLK_Frequency,                    /* LPUART1_CLK clock          */
    Clock_Ip_Get_LPUART2_CLK_Frequency,                    /* LPUART2_CLK clock          */
    Clock_Ip_Get_LPUART3_CLK_Frequency,                    /* LPUART3_CLK clock          */
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
    Clock_Ip_Get_LPUART4_CLK_Frequency,                    /* LPUART4_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
    Clock_Ip_Get_LPUART5_CLK_Frequency,                    /* LPUART5_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
    Clock_Ip_Get_LPUART6_CLK_Frequency,                    /* LPUART6_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
    Clock_Ip_Get_LPUART7_CLK_Frequency,                    /* LPUART7_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
    Clock_Ip_Get_LPUART8_CLK_Frequency,                    /* LPUART8_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART9_CLK)
    Clock_Ip_Get_LPUART9_CLK_Frequency,                    /* LPUART9_CLK clock          */
#endif
#if defined(CLOCK_IP_HAS_LPUART10_CLK)
    Clock_Ip_Get_LPUART10_CLK_Frequency,                   /* LPUART10_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART11_CLK)
    Clock_Ip_Get_LPUART11_CLK_Frequency,                   /* LPUART11_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART12_CLK)
    Clock_Ip_Get_LPUART12_CLK_Frequency,                   /* LPUART12_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART13_CLK)
    Clock_Ip_Get_LPUART13_CLK_Frequency,                   /* LPUART13_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART14_CLK)
    Clock_Ip_Get_LPUART14_CLK_Frequency,                   /* LPUART14_CLK clock         */
#endif
#if defined(CLOCK_IP_HAS_LPUART15_CLK)
    Clock_Ip_Get_LPUART15_CLK_Frequency,                   /* LPUART15_CLK clock         */
#endif
    Clock_Ip_Get_MSCM_CLK_Frequency,                       /* MSCM_CLK clock             */
#if defined(CLOCK_IP_HAS_MUA_CLK)
    Clock_Ip_Get_MUA_CLK_Frequency,                        /* MUA_CLK clock              */
#endif
#if defined(CLOCK_IP_HAS_MUB_CLK)
    Clock_Ip_Get_MUB_CLK_Frequency,                        /* MUB_CLK clock              */
#endif
    Clock_Ip_Get_PIT0_CLK_Frequency,                       /* PIT0_CLK clock             */
    Clock_Ip_Get_PIT1_CLK_Frequency,                       /* PIT1_CLK clock             */
#if defined(CLOCK_IP_HAS_PIT2_CLK)
    Clock_Ip_Get_PIT2_CLK_Frequency,                       /* PIT2_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
    Clock_Ip_Get_QSPI0_RAM_CLK_Frequency,                  /* QSPI0_RAM_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
    Clock_Ip_Get_QSPI_SFCK_CLK_Frequency,                  /* QSPI_SFCK_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
    Clock_Ip_Get_QSPI_2XSFIF_CLK_Frequency,                  /* QSPI_2XSFIF_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_SFCK_CLK)
    Clock_Ip_Get_QSPI0_SFCK_CLK_Frequency,                 /* QSPI0_SFCK_CLK clock       */
#endif
#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
    Clock_Ip_Get_QSPI0_TX_MEM_CLK_Frequency,               /* QSPI0_TX_MEM_CLK clock     */
#endif
    Clock_Ip_Get_RTC_CLK_Frequency,                        /* RTC_CLK clock              */
    Clock_Ip_Get_RTC0_CLK_Frequency,                       /* RTC0_CLK clock             */
#if defined(CLOCK_IP_HAS_SAI0_CLK)
    Clock_Ip_Get_SAI0_CLK_Frequency,                       /* SAI0_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SAI1_CLK)
    Clock_Ip_Get_SAI1_CLK_Frequency,                       /* SAI1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_SEMA42_CLK)
    Clock_Ip_Get_SEMA42_CLK_Frequency,                     /* SEMA42_CLK clock           */
#endif
    Clock_Ip_Get_SIUL0_CLK_Frequency,                      /* SIUL0_CLK clock            */
    Clock_Ip_Get_AIPS_SLOW_CLK_Frequency,                  /* STCU0_CLK clock            */
    Clock_Ip_Get_STMA_CLK_Frequency,                       /* STMA_CLK clock             */
    Clock_Ip_Get_STM0_CLK_Frequency,                       /* STM0_CLK clock             */
#if defined(CLOCK_IP_HAS_STMB_CLK)
    Clock_Ip_Get_STMB_CLK_Frequency,                       /* STMB_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_STM1_CLK)
    Clock_Ip_Get_STM1_CLK_Frequency,                       /* STM1_CLK clock             */
#endif
    Clock_Ip_Get_SWT0_CLK_Frequency,                       /* SWT0_CLK clock             */
#if defined(CLOCK_IP_HAS_SWT1_CLK)
    Clock_Ip_Get_SWT1_CLK_Frequency,                       /* SWT1_CLK clock             */
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_0_CLK)
    Clock_Ip_Get_TCM_CM7_0_CLK_Frequency,                  /* TCM_CM7_0_CLK clock        */
#endif
#if defined(CLOCK_IP_HAS_TCM_CM7_1_CLK)
    Clock_Ip_Get_TCM_CM7_1_CLK_Frequency,                  /* TCM_CM7_1_CLK clock        */
#endif
    Clock_Ip_Get_TEMPSENSE_CLK_Frequency,                  /* TEMPSENSE_CLK clock        */
    Clock_Ip_Get_TRACE_CLK_Frequency,                      /* TRACE_CLK clock            */
    Clock_Ip_Get_TRGMUX0_CLK_Frequency,                    /* TRGMUX0_CLK clock          */
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
    Clock_Ip_Get_TSENSE0_CLK_Frequency,                    /* TSENSE0_CLK clock          */
#endif
    Clock_Ip_Get_WKPU0_CLK_Frequency,                      /* WKPU0_CLK clock            */
};


/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

#if (!defined(CLOCK_IP_DERIVATIVE_001))
static extSignalFreq Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_EXT_SIGNALS_NO] =  {{EMAC_MII_RX_CLK,0U},{EMAC_MII_RMII_TX_CLK,0U}};
#else
static extSignalFreq Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_EXT_SIGNALS_NO] =  {{RESERVED_CLK,0U}};
#endif


/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"


#define MCU_START_SEC_VAR_INIT_32
#include "Mcu_MemMap.h"

static uint32 Clock_Ip_u32PllChecksum = CLOCK_IP_PLL_CHECKSUM;
static uint32 Clock_Ip_u32PllFreq = CLOCK_IP_PLL_FREQ;
/* External oscillators */
static uint32 Clock_Ip_u32Fxosc = CLOCK_IP_DEFAULT_FXOSC_FREQUENCY;

#if defined(CLOCK_IP_HAS_SXOSC_CLK)
static uint32 Clock_Ip_u32Sxosc = CLOCK_IP_DEFAULT_SXOSC_FREQUENCY;
#endif

#define MCU_STOP_SEC_VAR_INIT_32
#include "Mcu_MemMap.h"

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/* Return zero frequency */
static uint32 Clock_Ip_Get_Zero_Frequency(void)
{

    return 0U;
}

/* Return FIRC_CLK frequency */
static uint32 Clock_Ip_Get_FIRC_CLK_Frequency(void)
{

    return Clock_Ip_Get_FIRC_POSTDIV_CLK_Frequency();
}

/* Return FIRC_STANDBY_CLK frequency */
static uint32 Clock_Ip_Get_FIRC_STANDBY_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_FIRC_POSTDIV_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableClock[((IP_FIRC->STDBY_ENABLE & FIRC_STDBY_ENABLE_STDBY_EN_MASK) >> FIRC_STDBY_ENABLE_STDBY_EN_SHIFT)];                                     /*  clock enable/disable */
    return Frequency;
}

/* Return SIRC_CLK frequency */
static uint32 Clock_Ip_Get_SIRC_CLK_Frequency(void)
{

    return CLOCK_IP_SIRC_FREQUENCY;
}

/* Return SIRC_STANDBY_CLK frequency */
static uint32 Clock_Ip_Get_SIRC_STANDBY_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_SIRC_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableClock[((IP_SIRC->MISCELLANEOUS_IN & SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK) >> SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_SHIFT)];              /*  clock enable/disable */
    return Frequency;
}

/* Return FXOSC_CLK frequency */
static uint32 Clock_Ip_Get_FXOSC_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_u32Fxosc;
    if(((IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK53_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK53_SHIFT) != 0U)
    {
        Frequency &= Clock_Ip_u32EnableClock[((IP_FXOSC->CTRL & FXOSC_CTRL_OSCON_MASK) >> FXOSC_CTRL_OSCON_SHIFT)];                                              /*  clock enable/disable */
    }
    else
    {
        Frequency = 0U;
    }

    return Frequency;
}
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
/* Return SXOSC_CLK frequency */
static uint32 Clock_Ip_Get_SXOSC_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_u32Sxosc;
    if(((IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK51_SHIFT) != 0U)
    {
        Frequency &= Clock_Ip_u32EnableClock[((IP_SXOSC->SXOSC_CTRL & SXOSC_SXOSC_CTRL_OSCON_MASK) >> SXOSC_SXOSC_CTRL_OSCON_SHIFT)];                                    /*  clock enable/disable */
    }
    else
    {
        Frequency = 0U;
    }

    return Frequency;
}
#endif
/* Return PLL_CLK frequency */
static uint32 Clock_Ip_Get_PLL_CLK_Frequency(void)
{
    uint32 Frequency;
    uint32 PLLDivider;
    uint32 PLLFractionalDivider;

    if(((IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK56_SHIFT) != 0U)
    {
        PLLDivider = IP_PLL->PLLDV;
        PLLFractionalDivider = IP_PLL->PLLFD;
        if (Clock_Ip_u32PllChecksum != (PLLDivider ^ PLLFractionalDivider))
        {
            Clock_Ip_u32PllChecksum = (PLLDivider ^ PLLFractionalDivider);
            Clock_Ip_u32PllFreq = Clock_Ip_PLL_VCO(IP_PLL);
        }
        Frequency = ((((IP_PLL->PLLSR & PLL_PLLSR_LOCK_MASK) >> PLL_PLLSR_LOCK_SHIFT) != 0U) ? Clock_Ip_u32PllFreq : 0U);
    }
    else
    {
        Frequency = 0U;
    }
    return Frequency;
}

/* Return FIRC_POSTDIV_CLK frequency */
static uint32 Clock_Ip_Get_FIRC_POSTDIV_CLK_Frequency(void)
{
    uint32 Frequency = CLOCK_IP_FIRC_FREQUENCY;
    uint32 Divider = (IP_CONFIGURATION_GPR->CONFIG_REG_GPR & CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_MASK) >> CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_SHIFT;
    uint32 DividerValue;
    
    static const uint32 Clock_Ip_apfTableDividerValue[CLOCK_IP_FIRC_DIV_SEL_VALS_NO] =
    {
        2U,                  /* Divider value for 0  hardware value */
        2U,                  /* Divider value for 1  hardware value */
        16U,                 /* Divider value for 2  hardware value */
        1U,                  /* Divider value for 3  hardware value */
    };
    
    DividerValue = Clock_Ip_apfTableDividerValue[Divider];
    Frequency = (DividerValue != 0U) ? (Frequency / DividerValue) : 0U;
    return Frequency;
}

/* Return PLL_POSTDIV_CLK frequency */
static uint32 Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_PLL_CLK_Frequency();
    uint32 DividerValue = (IP_PLL->PLLDV & PLL_PLLDV_ODIV2_MASK) >> PLL_PLLDV_ODIV2_SHIFT;
    Frequency = (DividerValue != 0U) ? (Frequency / DividerValue) : 0U;
    return Frequency;
}

/* Return PLL_PHI0_CLK frequency */
static uint32 Clock_Ip_Get_PLL_PHI0_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableDivider[((IP_PLL->PLLODIV[0U] & PLL_PLLODIV_DE_MASK) >> PLL_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (((IP_PLL->PLLODIV[0U] & PLL_PLLODIV_DIV_MASK) >> PLL_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}

/* Return PLL_PHI1_CLK frequency */
static uint32 Clock_Ip_Get_PLL_PHI1_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_PLL_POSTDIV_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableDivider[((IP_PLL->PLLODIV[1U] & PLL_PLLODIV_DE_MASK) >> PLL_PLLODIV_DE_SHIFT)];                                    /*  Divider enable/disable */
    Frequency /= (((IP_PLL->PLLODIV[1U] & PLL_PLLODIV_DIV_MASK) >> PLL_PLLODIV_DIV_SHIFT) + 1U);                                          /*  Apply divider value */
    return Frequency;
}

#if defined(CLOCK_IP_HAS_EMAC_MII_RX_CLK)
/* Return EMAC_MII_RX_CLK frequency */
static uint32 Clock_Ip_Get_emac_mii_rx_Frequency(void)
{

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_EMAC_MII_REF_CLK_INDEX_ENTRY].Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EMAC_MII_RMII_TX_CLK)
/* Return EMAC_MII_RMII_TX_CLK frequency */
static uint32 Clock_Ip_Get_emac_mii_rmii_tx_Frequency(void)
{

    return Clock_Ip_axExtSignalFreqEntries[CLOCK_IP_EMAC_MII_RMII_TX_INDEX_ENTRY].Frequency;
}
#endif

/* Return SCS_CLK frequency */
static uint32 Clock_Ip_Get_SCS_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfTableProducerClkSrc[((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    return Frequency;
}

/* Return CORE_CLK frequency */
static uint32 Clock_Ip_Get_CORE_CLK_Frequency(void)
{
    uint32 Frequency;
    Frequency  = Clock_Ip_apfTableProducerClkSrc[((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_0_DC_0 & MC_CGM_MUX_0_DC_0_DE_MASK) >> MC_CGM_MUX_0_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_0_DC_0 & MC_CGM_MUX_0_DC_0_DIV_MASK) >> MC_CGM_MUX_0_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

/* Return AIPS_PLAT_CLK frequency */
static uint32 Clock_Ip_Get_AIPS_PLAT_CLK_Frequency(void)
{
    uint32 Frequency;
    Frequency  = Clock_Ip_apfTableProducerClkSrc[((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_0_DC_1 & MC_CGM_MUX_0_DC_1_DE_MASK) >> MC_CGM_MUX_0_DC_1_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_0_DC_1 & MC_CGM_MUX_0_DC_1_DIV_MASK) >> MC_CGM_MUX_0_DC_1_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

/* Return AIPS_SLOW_CLK frequency */
static uint32 Clock_Ip_Get_AIPS_SLOW_CLK_Frequency(void)
{
    uint32 Frequency;
    Frequency  = Clock_Ip_apfTableProducerClkSrc[((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_0_DC_2 & MC_CGM_MUX_0_DC_2_DE_MASK) >> MC_CGM_MUX_0_DC_2_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_0_DC_2 & MC_CGM_MUX_0_DC_2_DIV_MASK) >> MC_CGM_MUX_0_DC_2_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

/* Return FIRC_CLK frequency */
static uint32 Clock_Ip_Get_HSE_CLK_Frequency(void)
{
    uint32 Frequency;
    Frequency  = Clock_Ip_apfTableProducerClkSrc[((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_0_DC_3 & MC_CGM_MUX_0_DC_3_DE_MASK) >> MC_CGM_MUX_0_DC_3_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_0_DC_3 & MC_CGM_MUX_0_DC_3_DIV_MASK) >> MC_CGM_MUX_0_DC_3_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

/* Return DCM_CLK frequency */
static uint32 Clock_Ip_Get_DCM_CLK_Frequency(void)
{
    uint32 Frequency;
    Frequency  = Clock_Ip_apfTableProducerClkSrc[((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_0_DC_4 & MC_CGM_MUX_0_DC_4_DE_MASK) >> MC_CGM_MUX_0_DC_4_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_0_DC_4 & MC_CGM_MUX_0_DC_4_DIV_MASK) >> MC_CGM_MUX_0_DC_4_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

#if defined(CLOCK_IP_HAS_LBIST_CLK)
/* Return LBIST_CLK frequency */
static uint32 Clock_Ip_Get_LBIST_CLK_Frequency(void)
{
    uint32 Frequency;
    Frequency  = Clock_Ip_apfTableProducerClkSrc[((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_0_DC_5 & MC_CGM_MUX_0_DC_5_DE_MASK) >> MC_CGM_MUX_0_DC_5_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_0_DC_5 & MC_CGM_MUX_0_DC_5_DIV_MASK) >> MC_CGM_MUX_0_DC_5_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_QSPI_MEM_CLK)
/* Return QSPI_MEM_CLK frequency */
static uint32 Clock_Ip_Get_QSPI_MEM_CLK_Frequency(void)
{
    uint32 Frequency;
    Frequency  = Clock_Ip_apfTableProducerClkSrc[((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_0_DC_6 & MC_CGM_MUX_0_DC_6_DE_MASK) >> MC_CGM_MUX_0_DC_6_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_0_DC_6 & MC_CGM_MUX_0_DC_6_DIV_MASK) >> MC_CGM_MUX_0_DC_6_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_CM7_CORE_CLK)
/* Return CM7_CORE_CLK frequency */
static uint32 Clock_Ip_Get_CM7_CORE_CLK_Frequency(void)
{
    uint32 Frequency;
    Frequency  = Clock_Ip_apfTableProducerClkSrc[((IP_MC_CGM->MUX_0_CSS & MC_CGM_MUX_0_CSS_SELSTAT_MASK) >> MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_0_DC_7 & MC_CGM_MUX_0_DC_7_DE_MASK) >> MC_CGM_MUX_0_DC_7_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_0_DC_6 & MC_CGM_MUX_0_DC_7_DIV_MASK) >> MC_CGM_MUX_0_DC_7_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}
#endif

/* Return CLKOUT_RUN_CLK frequency */
static uint32 Clock_Ip_Get_CLKOUT_RUN_CLK_Frequency(void)
{
    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_6_CSS & MC_CGM_MUX_6_CSS_SELSTAT_MASK) >> MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_6_DC_0 & MC_CGM_MUX_6_DC_0_DE_MASK) >> MC_CGM_MUX_6_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_6_DC_0 & MC_CGM_MUX_6_DC_0_DIV_MASK) >> MC_CGM_MUX_6_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

/* Return ADC0_CLK frequency */
static uint32 Clock_Ip_Get_ADC0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK40_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK40_SHIFT];
    return Frequency;
}

/* Return ADC1_CLK frequency */
static uint32 Clock_Ip_Get_ADC1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK41_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK41_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_ADC2_CLK)
/* Return ADC2_CLK frequency */
static uint32 Clock_Ip_Get_ADC2_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK42_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK42_SHIFT];
    return Frequency;
}
#endif

/* Return BCTU0_CLK frequency */
static uint32 Clock_Ip_Get_BCTU0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}

/* Return DMAMUX0_CLK frequency */
static uint32 Clock_Ip_Get_DMAMUX0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}

/* Return DMAMUX1_CLK frequency */
static uint32 Clock_Ip_Get_DMAMUX1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK33_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK33_SHIFT];
    return Frequency;
}

/* Return EDMA0_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK3_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK3_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD0_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK4_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK4_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD1_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK5_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK5_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD2_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD2_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK6_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK6_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD3_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD3_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK7_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK7_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD4_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD4_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK8_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK8_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD5_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD5_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK9_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK9_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD6_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD6_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK10_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK10_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD7_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD7_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK11_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK11_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD8_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD8_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK12_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK12_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD9_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD9_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK13_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK13_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD10_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD10_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK14_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK14_SHIFT];
    return Frequency;
}

/* Return EDMA0_TCD11_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD11_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK15_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK15_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_EDMA0_TCD12_CLK)
/* Return EDMA0_TCD12_CLKs frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD12_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK4_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK4_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD13_CLK)
/* Return EDMA0_TCD13_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD13_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK5_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK5_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD14_CLK)
/* Return EDMA0_TCD14_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD14_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK6_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK6_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD15_CLK)
/* Return EDMA0_TCD15_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD15_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK7_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK7_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD16_CLK)
/* Return EDMA0_TCD16_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD16_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK8_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK8_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD17_CLK)
/* Return EDMA0_TCD17_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD17_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK9_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK9_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD18_CLK)
/* Return EDMA0_TCD18_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD18_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK10_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK10_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD19_CLK)
/* Return EDMA0_TCD19_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD19_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK11_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK11_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD20_CLK)
/* Return EDMA0_TCD20_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD20_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK12_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK12_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD21_CLK)
/* Return EDMA0_TCD21_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD21_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK13_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK13_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EDMA0_TCD22_CLK)
/* Return EDMA0_TCD22_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD22_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK14_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK14_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD23_CLK)
/* Return EDMA0_TCD23_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD23_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK15_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK15_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD24_CLK)
/* Return EDMA0_TCD24_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD24_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK16_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK16_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD25_CLK)
/* Return EDMA0_TCD25_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD25_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK17_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK17_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD26_CLK)
/* Return EDMA0_TCD26_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD26_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK18_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK18_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD27_CLK)
/* Return EDMA0_TCD27 frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD27_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK19_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK19_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD28_CLK)
/* Return EDMA0_TCD28_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD28_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK20_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK20_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD29_CLK)
/* Return EDMA0_TCD29_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD29_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK21_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK21_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD30_CLK)
/* Return EDMA0_TCD30_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD30_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK22_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK22_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EDMA0_TCD31_CLK)
/* Return EDMA0_TCD31_CLK frequency */
static uint32 Clock_Ip_Get_EDMA0_TCD31_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK23_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK23_SHIFT];
    return Frequency;
}
#endif

/* Return EMIOS0_CLK frequency */
static uint32 Clock_Ip_Get_EMIOS0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK34_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_EMIOS1_CLK)
/* Return EMIOS1_CLK frequency */
static uint32 Clock_Ip_Get_EMIOS1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK35_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK35_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EMIOS2_CLK)
/* Return EMIOS2_CLK frequency */
static uint32 Clock_Ip_Get_EMIOS2_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK36_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK36_SHIFT];
    return Frequency;
}
#endif

/* Return LCU0_CLK frequency */
static uint32 Clock_Ip_Get_LCU0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK38_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK38_SHIFT];
    return Frequency;
}

/* Return LCU1_CLK frequency */
static uint32 Clock_Ip_Get_LCU1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK39_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK39_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_TCM_CM7_0_CLK)
/* Return TCM_CM7_0_CLK frequency */
static uint32 Clock_Ip_Get_TCM_CM7_0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK62_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK62_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_TCM_CM7_1_CLK)
/* Return TCM_CM7_1_CLK frequency */
static uint32 Clock_Ip_Get_TCM_CM7_1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK63_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK63_SHIFT];
    return Frequency;
}
#endif

/* Return TEMPSENSE_CLK frequency */
static uint32 Clock_Ip_Get_TEMPSENSE_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_CORE_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK95_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK95_SHIFT];
    return Frequency;
}

/* Return CMP0_CLK frequency */
static uint32 Clock_Ip_Get_CMP0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK92_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK92_SHIFT];
    return Frequency;
}

/* Return CMP1_CLK frequency */
static uint32 Clock_Ip_Get_CMP1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK93_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK93_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_CMP2_CLK)
/* Return CMP2_CLK frequency */
static uint32 Clock_Ip_Get_CMP2_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK58_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK58_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_EIM_CLK)
/* Return EIM_CLK frequency */
static uint32 Clock_Ip_Get_EIM_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK22_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK22_SHIFT];
    return Frequency;
}
#endif
/* Return ERM0_CLK frequency */
static uint32 Clock_Ip_Get_ERM0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK23_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK23_SHIFT];
    return Frequency;
}

/* Return LPI2C0_CLK frequency */
static uint32 Clock_Ip_Get_LPI2C0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK84_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK84_SHIFT];
    return Frequency;
}

/* Return LPI2C1_CLK frequency */
static uint32 Clock_Ip_Get_LPI2C1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK85_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK85_SHIFT];
    return Frequency;
}

/* Return LPSPI0_CLK frequency */
static uint32 Clock_Ip_Get_LPSPI0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK86_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK86_SHIFT];
    return Frequency;
}

/* Return LPSPI1_CLK frequency */
static uint32 Clock_Ip_Get_LPSPI1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK87_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK87_SHIFT];
    return Frequency;
}

/* Return LPSPI2_CLK frequency */
static uint32 Clock_Ip_Get_LPSPI2_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK88_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK88_SHIFT];
    return Frequency;
}

/* Return LPSPI3_CLK frequency */
static uint32 Clock_Ip_Get_LPSPI3_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK89_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK89_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_LPSPI4_CLK)
/* Return LPSPI4_CLK frequency */
static uint32 Clock_Ip_Get_LPSPI4_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK47_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK47_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_LPSPI5_CLK)
/* Return LPSPI5_CLK frequency */
static uint32 Clock_Ip_Get_LPSPI5_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK48_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK48_SHIFT];
    return Frequency;
}
#endif

/* Return LPUART0_CLK frequency */
static uint32 Clock_Ip_Get_LPUART0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK74_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK74_SHIFT];
    return Frequency;
}

/* Return LPUART1_CLK frequency */
static uint32 Clock_Ip_Get_LPUART1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK75_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK75_SHIFT];
    return Frequency;
}

/* Return LPUART2_CLK frequency */
static uint32 Clock_Ip_Get_LPUART2_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK76_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK76_SHIFT];
    return Frequency;
}

/* Return LPUART3_CLK frequency */
static uint32 Clock_Ip_Get_LPUART3_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK77_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK77_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_LPUART4_CLK)
/* Return LPUART4_CLK frequency */
static uint32 Clock_Ip_Get_LPUART4_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK78_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK78_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART5_CLK)
/* Return LPUART5_CLK frequency */
static uint32 Clock_Ip_Get_LPUART5_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK79_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK79_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART6_CLK)
/* Return LPUART6_CLK frequency */
static uint32 Clock_Ip_Get_LPUART6_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK80_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK80_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART7_CLK)
/* Return LPUART7_CLK frequency */
static uint32 Clock_Ip_Get_LPUART7_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK81_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK81_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_LPUART8_CLK)
/* Return LPUART8_CLK frequency */
static uint32 Clock_Ip_Get_LPUART8_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK35_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK35_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_LPUART9_CLK)
/* Return LPUART9_CLK frequency */
static uint32 Clock_Ip_Get_LPUART9_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK36_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK36_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_LPUART10_CLK)
/* Return LPUART10_CLK frequency */
static uint32 Clock_Ip_Get_LPUART10_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK37_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK37_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_LPUART11_CLK)
/* Return LPUART11_CLK frequency */
static uint32 Clock_Ip_Get_LPUART11_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK38_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK38_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_LPUART12_CLK)
/* Return LPUART12_CLK frequency */
static uint32 Clock_Ip_Get_LPUART12_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK39_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK39_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_LPUART13_CLK)
/* Return LPUART13_CLK frequency */
static uint32 Clock_Ip_Get_LPUART13_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK40_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK40_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_LPUART14_CLK)
/* Return LPUART14_CLK frequency */
static uint32 Clock_Ip_Get_LPUART14_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK41_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK41_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_LPUART15_CLK)
/* Return LPUART15_CLK frequency */
static uint32 Clock_Ip_Get_LPUART15_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK42_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK42_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_MUA_CLK)
/* Return MUA_CLK frequency */
static uint32 Clock_Ip_Get_MUA_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK46_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK46_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_MUB_CLK)
/* Return MUB_CLK frequency */
static uint32 Clock_Ip_Get_MUB_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK47_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK47_SHIFT];
    return Frequency;
}
#endif

/* Return PIT0_CLK frequency */
static uint32 Clock_Ip_Get_PIT0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK44_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK44_SHIFT];
    return Frequency;
}

/* Return PIT1_CLK frequency */
static uint32 Clock_Ip_Get_PIT1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK45_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK45_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_PIT2_CLK)
/* Return PIT2_CLK frequency */
static uint32 Clock_Ip_Get_PIT2_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK63_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK63_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_SAI0_CLK)
/* Return SAI0_CLK frequency */
static uint32 Clock_Ip_Get_SAI0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK91_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK91_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_SAI1_CLK)
/* Return SAI1_CLK frequency */
static uint32 Clock_Ip_Get_SAI1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK55_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK55_SHIFT];
    return Frequency;
}
#endif

/* Return TRGMUX0_CLK frequency */
static uint32 Clock_Ip_Get_TRGMUX0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_TSENSE0_CLK)
/* Return TSENSE0_CLK frequency */
static uint32 Clock_Ip_Get_TSENSE0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK49_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK49_SHIFT];
    return Frequency;
}
#endif
/* Return WKPU0_CLK frequency */
static uint32 Clock_Ip_Get_WKPU0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK45_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK45_SHIFT];
    return Frequency;
}

/* Return CRC0_CLK frequency */
static uint32 Clock_Ip_Get_CRC0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB3_STAT & MC_ME_PRTN1_COFB3_STAT_BLOCK96_MASK) >> MC_ME_PRTN1_COFB3_STAT_BLOCK96_SHIFT];
    return Frequency;
}

/* Return FLEXIO0_CLK frequency */
static uint32 Clock_Ip_Get_FLEXIO0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK73_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK73_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_I3C0_CLK)
/* Return I3C0_CLK frequency */
static uint32 Clock_Ip_Get_I3C0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN0_COFB1_STAT & MC_ME_PRTN0_COFB1_STAT_BLOCK48_MASK) >> MC_ME_PRTN0_COFB1_STAT_BLOCK48_SHIFT];
    return Frequency;
}
#endif

/* Return INTM_CLK frequency */
static uint32 Clock_Ip_Get_INTM_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK31_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK31_SHIFT];
    return Frequency;
}

/* Return MSCM_CLK frequency */
static uint32 Clock_Ip_Get_MSCM_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK24_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK24_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_SEMA42_CLK)
/* Return SEMA42_CLK frequency */
static uint32 Clock_Ip_Get_SEMA42_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK24_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK24_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_QSPI0_RAM_CLK)
/* Return QSPI0_RAM_CLK frequency */
static uint32 Clock_Ip_Get_QSPI0_RAM_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK51_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_QSPI0_TX_MEM_CLK)
/* Return QSPI0_TX_MEM_CLK frequency */
static uint32 Clock_Ip_Get_QSPI0_TX_MEM_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK51_SHIFT];
    return Frequency;
}
#endif

/* Return SIUL0_CLK frequency */
static uint32 Clock_Ip_Get_SIUL0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK42_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK42_SHIFT];
    return Frequency;
}

/* Return SWT0_CLK frequency */
static uint32 Clock_Ip_Get_SWT0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_SLOW_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK28_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK28_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_SWT1_CLK)
/* Return SWT1_CLK frequency */
static uint32 Clock_Ip_Get_SWT1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_AIPS_PLAT_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK27_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK27_SHIFT];
    return Frequency;
}
#endif

/* Return CLKOUT_STANDBY_CLK frequency */
static uint32 Clock_Ip_Get_CLKOUT_STANDBY_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_5_CSS & MC_CGM_MUX_5_CSS_SELSTAT_MASK) >> MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_5_DC_0 & MC_CGM_MUX_5_DC_0_DE_MASK) >> MC_CGM_MUX_5_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_5_DC_0 & MC_CGM_MUX_5_DC_0_DIV_MASK) >> MC_CGM_MUX_5_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

#if defined(CLOCK_IP_HAS_EMAC_RX_CLK)
/* Return EMAC_RX_CLK frequency */
static uint32 Clock_Ip_Get_EMAC_RX_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_7_CSS & MC_CGM_MUX_7_CSS_SELSTAT_MASK) >> MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DE_MASK) >> MC_CGM_MUX_7_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_7_DC_0 & MC_CGM_MUX_7_DC_0_DIV_MASK) >> MC_CGM_MUX_7_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EMAC0_RX_CLK)
/* Return EMAC0_RX_CLK frequency */
static uint32 Clock_Ip_Get_EMAC0_RX_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_EMAC_RX_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EMAC_TS_CLK)
/* Return EMAC_TS_CLK frequency */
static uint32 Clock_Ip_Get_EMAC_TS_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_9_CSS & MC_CGM_MUX_9_CSS_SELSTAT_MASK) >> MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_9_DC_0 & MC_CGM_MUX_9_DC_0_DE_MASK) >> MC_CGM_MUX_9_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_9_DC_0 & MC_CGM_MUX_9_DC_0_DIV_MASK) >> MC_CGM_MUX_9_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EMAC0_TS_CLK)
/* Return EMAC0_TS_CLK frequency */
static uint32 Clock_Ip_Get_EMAC0_TS_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_EMAC_TS_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EMAC_TX_CLK)
/* Return EMAC_TX_CLK frequency */
static uint32 Clock_Ip_Get_EMAC_TX_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_8_CSS & MC_CGM_MUX_8_CSS_SELSTAT_MASK) >> MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_8_DC_0 & MC_CGM_MUX_8_DC_0_DE_MASK) >> MC_CGM_MUX_8_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_8_DC_0 & MC_CGM_MUX_8_DC_0_DIV_MASK) >> MC_CGM_MUX_8_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_EMAC0_TX_CLK)
/* Return EMAC0_TX_CLK frequency */
static uint32 Clock_Ip_Get_EMAC0_TX_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_EMAC_TX_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK32_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK32_SHIFT];
    return Frequency;
}
#endif

/* Return FLEXCANA_CLK frequency */
static uint32 Clock_Ip_Get_FLEXCANA_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_3_CSS & MC_CGM_MUX_3_CSS_SELSTAT_MASK) >> MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_3_DC_0 & MC_CGM_MUX_3_DC_0_DE_MASK) >> MC_CGM_MUX_3_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_3_DC_0 & MC_CGM_MUX_3_DC_0_DIV_MASK) >> MC_CGM_MUX_3_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN0_CLK frequency */
static uint32 Clock_Ip_Get_FLEXCAN0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_FLEXCANA_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK65_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK65_SHIFT];
    return Frequency;
}

/* Return FLEXCAN1_CLK frequency */
static uint32 Clock_Ip_Get_FLEXCAN1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_FLEXCANA_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK66_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK66_SHIFT];
    return Frequency;
}

/* Return FLEXCAN2_CLK frequency */
static uint32 Clock_Ip_Get_FLEXCAN2_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_FLEXCANA_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK67_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK67_SHIFT];
    return Frequency;
}

/* Return FLEXCANB_CLK frequency */
static uint32 Clock_Ip_Get_FLEXCANB_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_4_CSS & MC_CGM_MUX_4_CSS_SELSTAT_MASK) >> MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DE_MASK) >> MC_CGM_MUX_4_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_4_DC_0 & MC_CGM_MUX_4_DC_0_DIV_MASK) >> MC_CGM_MUX_4_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

/* Return FLEXCAN3_CLK frequency */
static uint32 Clock_Ip_Get_FLEXCAN3_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_FLEXCANB_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK68_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK68_SHIFT];
    return Frequency;
}
#if defined(CLOCK_IP_HAS_FLEXCAN4_CLK)
/* Return FLEXCAN4_CLK frequency */
static uint32 Clock_Ip_Get_FLEXCAN4_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_FLEXCANB_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK69_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK69_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_FLEXCAN5_CLK)
/* Return FLEXCAN5_CLK frequency */
static uint32 Clock_Ip_Get_FLEXCAN5_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_FLEXCANB_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB2_STAT & MC_ME_PRTN1_COFB2_STAT_BLOCK70_MASK) >> MC_ME_PRTN1_COFB2_STAT_BLOCK70_SHIFT];
    return Frequency;
}
#endif
#if defined(CLOCK_IP_HAS_QSPI_SFCK_CLK)
/* Return QSPI_SFCK_CLK frequency */
static uint32 Clock_Ip_Get_QSPI_SFCK_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_10_CSS & MC_CGM_MUX_10_CSS_SELSTAT_MASK) >> MC_CGM_MUX_10_CSS_SELSTAT_SHIFT)]();   /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_10_DC_0 & MC_CGM_MUX_10_DC_0_DE_MASK) >> MC_CGM_MUX_10_DC_0_DE_SHIFT)];                        /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_10_DC_0 & MC_CGM_MUX_10_DC_0_DIV_MASK) >> MC_CGM_MUX_10_DC_0_DIV_SHIFT) + 1U);                              /*  Apply divider value */
#ifdef CLOCK_IP_DERIVATIVE_006
    Frequency /= (2U);
#endif
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_QSPI_2XSFIF_CLK)
/* Return QSPI_2XSFIF_CLK frequency */
static uint32 Clock_Ip_Get_QSPI_2XSFIF_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_10_CSS & MC_CGM_MUX_10_CSS_SELSTAT_MASK) >> MC_CGM_MUX_10_CSS_SELSTAT_SHIFT)]();   /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_10_DC_0 & MC_CGM_MUX_10_DC_0_DE_MASK) >> MC_CGM_MUX_10_DC_0_DE_SHIFT)];                        /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_10_DC_0 & MC_CGM_MUX_10_DC_0_DIV_MASK) >> MC_CGM_MUX_10_DC_0_DIV_SHIFT) + 1U);                              /*  Apply divider value */
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_QSPI0_SFCK_CLK)
/* Return QSPI0_SFCK_CLK frequency */
static uint32 Clock_Ip_Get_QSPI0_SFCK_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_QSPI_SFCK_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB1_STAT & MC_ME_PRTN2_COFB1_STAT_BLOCK51_MASK) >> MC_ME_PRTN2_COFB1_STAT_BLOCK51_SHIFT];
    return Frequency;
}
#endif

/* Return RTC_CLK frequency */
uint32 Clock_Ip_Get_RTC_CLK_Frequency_TrustedCall(void)
{
    uint32 Frequency;
    if(CLOCK_IP_ENABLED == Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK34_SHIFT])
    {
        Frequency = Clock_Ip_apfFreqTableRtcClkSrc[((IP_RTC->RTCC & RTC_RTCC_CLKSEL_MASK) >> RTC_RTCC_CLKSEL_SHIFT)]();      /*  Selector value */
    }
    else
    {
        Frequency = 0U;
    }
    return Frequency;
}

static uint32 Clock_Ip_Get_RTC_CLK_Frequency(void)
{
    uint32 Frequency;
#ifdef CLOCK_IP_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    Frequency = OsIf_Trusted_Call_Return(Clock_Ip_Get_RTC_CLK_Frequency_TrustedCall);
  #else
    Frequency = Clock_Ip_Get_RTC_CLK_Frequency_TrustedCall();
  #endif
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */
    return Frequency;
}

/* Return RTC0_CLK frequency */
static uint32 Clock_Ip_Get_RTC0_CLK_Frequency(void)
{
    uint32 Frequency = Clock_Ip_Get_RTC_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK34_MASK) >> MC_ME_PRTN1_COFB1_STAT_BLOCK34_SHIFT];
    return Frequency;
}

/* Return STMA_CLK frequency */
static uint32 Clock_Ip_Get_STMA_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_1_CSS & MC_CGM_MUX_1_CSS_SELSTAT_MASK) >> MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DE_MASK) >> MC_CGM_MUX_1_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_1_DC_0 & MC_CGM_MUX_1_DC_0_DIV_MASK) >> MC_CGM_MUX_1_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}

/* Return STM0_CLK frequency */
static uint32 Clock_Ip_Get_STM0_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_STMA_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN1_COFB0_STAT & MC_ME_PRTN1_COFB0_STAT_BLOCK29_MASK) >> MC_ME_PRTN1_COFB0_STAT_BLOCK29_SHIFT];
    return Frequency;
}

#if defined(CLOCK_IP_HAS_STMB_CLK)
/* Return STMB_CLK frequency */
static uint32 Clock_Ip_Get_STMB_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_2_CSS & MC_CGM_MUX_2_CSS_SELSTAT_MASK) >> MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)]();      /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DE_MASK) >> MC_CGM_MUX_2_DC_0_DE_SHIFT)];                           /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_2_DC_0 & MC_CGM_MUX_2_DC_0_DIV_MASK) >> MC_CGM_MUX_2_DC_0_DIV_SHIFT) + 1U);                                 /*  Apply divider value */
    return Frequency;
}
#endif

#if defined(CLOCK_IP_HAS_STM1_CLK)
/* Return STM1_CLK frequency */
static uint32 Clock_Ip_Get_STM1_CLK_Frequency(void)
{

    uint32 Frequency = Clock_Ip_Get_STMB_CLK_Frequency();
    Frequency &= Clock_Ip_u32EnableGate[(IP_MC_ME->PRTN2_COFB0_STAT & MC_ME_PRTN2_COFB0_STAT_BLOCK29_MASK) >> MC_ME_PRTN2_COFB0_STAT_BLOCK29_SHIFT];
    return Frequency;
}
#endif

/* Return TRACE_CLK frequency */
static uint32 Clock_Ip_Get_TRACE_CLK_Frequency(void)
{

    uint32 Frequency;
    Frequency  = Clock_Ip_apfFreqTableClkSrc[((IP_MC_CGM->MUX_11_CSS & MC_CGM_MUX_11_CSS_SELSTAT_MASK) >> MC_CGM_MUX_11_CSS_SELSTAT_SHIFT)]();   /*  Selector value */
    Frequency &= Clock_Ip_u32EnableDivider[((IP_MC_CGM->MUX_11_DC_0 & MC_CGM_MUX_11_DC_0_DE_MASK) >> MC_CGM_MUX_11_DC_0_DE_SHIFT)];                        /*  Divider enable/disable */
    Frequency /= (((IP_MC_CGM->MUX_11_DC_0 & MC_CGM_MUX_11_DC_0_DIV_MASK) >> MC_CGM_MUX_11_DC_0_DIV_SHIFT) + 1U);                              /*  Apply divider value */
    return Frequency;
}

/* Return PLL_VCO_CLK frequency */
static uint32 Clock_Ip_PLL_VCO(const PLL_Type *Base)
{
    uint32 Fin;
    uint32 Rdiv;
    uint32 Mfi;
    uint32 Mfn;
    uint32 Fout;
    uint32 Var1;
    uint32 Var2;
    uint32 Var3;
    uint32 Var4;
    uint32 Var5;
    Fin  = Clock_Ip_Get_FXOSC_CLK_Frequency();   /* input freq */
    Rdiv = ((Base->PLLDV & PLL_PLLDV_RDIV_MASK) >> PLL_PLLDV_RDIV_SHIFT);              /* Rdiv */
    Mfi  = ((Base->PLLDV & PLL_PLLDV_MFI_MASK) >> PLL_PLLDV_MFI_SHIFT);                /* Mfi */
    Mfn  = ((Base->PLLFD & PLL_PLLFD_MFN_MASK) >> PLL_PLLFD_MFN_SHIFT);                /* Mfn */


    Var1 = Mfi / Rdiv;                                      /* Mfi divided by Rdiv */
    Var2 = Mfi - (Var1 * Rdiv);                             /* Mfi minus Var1 multiplied by Rdiv */
    Var3 = (Rdiv << CLOCK_IP_MUL_BY_16384) + (Rdiv << CLOCK_IP_MUL_BY_2048);  /* Rdiv multiplied by 18432 */
    Var4 = Fin / Var3;                                      /* Fin divide by (Rdiv multiplied by 18432) */
    Var5 = Fin - (Var4 * Var3);                               /* Fin minus Var4 multiplied by (Rdiv mul 18432) */

    Fout = Var1 * Fin;                                      /* Var1 multipied by Fin */
    Fout += Fin / Rdiv * Var2;                              /* Fin divided by Rdiv and multiplied by Var2 */
    Fout += Var4 * Mfn;                                     /* Mfn multiplied by Var4 */
    Fout += Var5 * Mfn / Var3;                              /* Var5 multiplied by Mfn and divide by (Rdiv mul 18432) */

    return Fout;
}

/* Set frequency value for External Oscillator */
void Clock_Ip_SetExternalOscillatorFrequency(Clock_Ip_NameType ExtOscName, uint32 Frequency)
{
    switch(ExtOscName)
    {
        case FXOSC_CLK:
        {
            Clock_Ip_u32Fxosc = Frequency;
        }
        break;
#if defined(CLOCK_IP_HAS_SXOSC_CLK)
        case SXOSC_CLK:
        {
            Clock_Ip_u32Sxosc = Frequency;
        }
        break;
#endif
        default:
        {
            /* Invalid clock name */
        }
        break;
    }

}

/* Set frequency value for External Signal */
void Clock_Ip_SetExternalSignalFrequency(Clock_Ip_NameType SignalName, uint32 Frequency)
{
    uint32 Index;
    for (Index = 0U; Index < CLOCK_IP_EXT_SIGNALS_NO; Index++)
    {
        if (SignalName == Clock_Ip_axExtSignalFreqEntries[Index].Name)
        {
            Clock_Ip_axExtSignalFreqEntries[Index].Frequency = Frequency;
            break;
        }
    }
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

uint32 Clock_Ip_GetFreq(Clock_Ip_NameType ClockName)
{
    return Clock_Ip_apfFreqTable[ClockName]();
}

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#else
/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/* Set external frequency */
void Clock_Ip_SetExternalSignalFrequency(Clock_Ip_NameType SignalName, uint32 Frequency)
{
    (void)SignalName;
    (void)Frequency;
}

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#endif  /* #if (defined(CLOCK_IP_GET_FREQUENCY_API) && (CLOCK_IP_GET_FREQUENCY_API == STD_ON)) */

#ifdef __cplusplus
}
#endif

/** @} */
