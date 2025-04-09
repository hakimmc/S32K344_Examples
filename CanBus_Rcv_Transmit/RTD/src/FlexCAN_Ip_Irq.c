/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : FLEXCAN
*   Dependencies         : 
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
 *  @file FlexCAN_Ip_Irq.c
 *
 *  @brief FlexCAN Interrupts
 *
 *  @addtogroup FlexCAN
 *  @{
 */

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "FlexCAN_Ip_Irq.h"
#include "FlexCAN_Ip_HwAccess.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXCAN_IP_IRQ_VENDOR_ID_C                      43
#define FLEXCAN_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define FLEXCAN_IP_IRQ_AR_RELEASE_MINOR_VERSION_C       4
#define FLEXCAN_IP_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define FLEXCAN_IP_IRQ_SW_MAJOR_VERSION_C               2
#define FLEXCAN_IP_IRQ_SW_MINOR_VERSION_C               0
#define FLEXCAN_IP_IRQ_SW_PATCH_VERSION_C               0
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and FlexCAN_Ip_Irq header file are of the same vendor */
#if (FLEXCAN_IP_IRQ_VENDOR_ID_C != FLEXCAN_IP_IRQ_VENDOR_ID_H)
    #error "FlexCAN_Ip_Irq.c and FlexCAN_Ip_Irq.h have different vendor ids"
#endif
/* Check if current file and FlexCAN_Ip_Irq header file are of the same Autosar version */
#if ((FLEXCAN_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != FLEXCAN_IP_IRQ_AR_RELEASE_MAJOR_VERSION_H) || \
     (FLEXCAN_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != FLEXCAN_IP_IRQ_AR_RELEASE_MINOR_VERSION_H) || \
     (FLEXCAN_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != FLEXCAN_IP_IRQ_AR_RELEASE_REVISION_VERSION_H))
    #error "AutoSar Version Numbers of FlexCAN_Ip_Irq.c and FlexCAN_Ip_Irq.h are different"
#endif
/* Check if current file and FlexCAN_Ip_Irq header file are of the same Software version */
#if ((FLEXCAN_IP_IRQ_SW_MAJOR_VERSION_C != FLEXCAN_IP_IRQ_SW_MAJOR_VERSION_H) || \
     (FLEXCAN_IP_IRQ_SW_MINOR_VERSION_C != FLEXCAN_IP_IRQ_SW_MINOR_VERSION_H) || \
     (FLEXCAN_IP_IRQ_SW_PATCH_VERSION_C != FLEXCAN_IP_IRQ_SW_PATCH_VERSION_H))
    #error "Software Version Numbers of FlexCAN_Ip_Irq.c and FlexCAN_Ip_Irq.h are different"
#endif

/* Check if current file and FlexCAN_Ip_HwAccess header file are of the same vendor */
#if (FLEXCAN_IP_IRQ_VENDOR_ID_C != FLEXCAN_IP_HWACCESS_VENDOR_ID_H)
    #error "FlexCAN_Ip_Irq.c and FlexCAN_Ip_HwAccess.h have different vendor ids"
#endif
/* Check if current file and FlexCAN_Ip_HwAccess header file are of the same Autosar version */
#if ((FLEXCAN_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != FLEXCAN_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION_H) || \
     (FLEXCAN_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != FLEXCAN_IP_HWACCESS_AR_RELEASE_MINOR_VERSION_H) || \
     (FLEXCAN_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != FLEXCAN_IP_HWACCESS_AR_RELEASE_REVISION_VERSION_H))
    #error "AutoSar Version Numbers of FlexCAN_Ip_Irq.c and FlexCAN_Ip_HwAccess.h are different"
#endif
/* Check if current file and FlexCAN_Ip_HwAccess header file are of the same Software version */
#if ((FLEXCAN_IP_IRQ_SW_MAJOR_VERSION_C != FLEXCAN_IP_HWACCESS_SW_MAJOR_VERSION_H) || \
     (FLEXCAN_IP_IRQ_SW_MINOR_VERSION_C != FLEXCAN_IP_HWACCESS_SW_MINOR_VERSION_H) || \
     (FLEXCAN_IP_IRQ_SW_PATCH_VERSION_C != FLEXCAN_IP_HWACCESS_SW_PATCH_VERSION_H))
    #error "Software Version Numbers of FlexCAN_Ip_Irq.c and FlexCAN_Ip_HwAccess.h are different"
#endif
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define CAN_START_SEC_CODE
#include "Can_MemMap.h"

ISR(CAN0_ORED_IRQHandler);

ISR(CAN0_ORED_0_31_MB_IRQHandler);

ISR(CAN0_ORED_32_63_MB_IRQHandler);

#if (FLEXCAN_IP_FEATURE_MBDSR_COUNT > 2U)
ISR(CAN0_ORED_64_95_MB_IRQHandler);
#endif /* (FLEXCAN_IP_FEATURE_MBDSR_COUNT > 2U) */

#if (FLEXCAN_INSTANCE_COUNT > 1U)
ISR(CAN1_ORED_IRQHandler);

ISR(CAN1_ORED_0_31_MB_IRQHandler);

ISR(CAN1_ORED_32_63_MB_IRQHandler);

#endif /* (FLEXCAN_INSTANCE_COUNT > 1U) */

#if (FLEXCAN_INSTANCE_COUNT > 2U)
ISR(CAN2_ORED_IRQHandler);

ISR(CAN2_ORED_0_31_MB_IRQHandler);

ISR(CAN2_ORED_32_63_MB_IRQHandler);
#endif /* (FLEXCAN_INSTANCE_COUNT > 2U) */

#if (FLEXCAN_INSTANCE_COUNT > 3U)
ISR(CAN3_ORED_IRQHandler);

ISR(CAN3_ORED_0_31_MB_IRQHandler);

#endif /* (FLEXCAN_INSTANCE_COUNT > 3U) */

#if (FLEXCAN_INSTANCE_COUNT > 4U)
ISR(CAN4_ORED_IRQHandler);

ISR(CAN4_ORED_0_31_MB_IRQHandler);

#endif /* (FLEXCAN_INSTANCE_COUNT > 4U) */

#if (FLEXCAN_INSTANCE_COUNT > 5U)
ISR(CAN5_ORED_IRQHandler);

ISR(CAN5_ORED_0_31_MB_IRQHandler);

#endif /* (FLEXCAN_INSTANCE_COUNT > 5U) */

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/* Implementation of CAN0 handler named in startup code for processing of Errors and Bus Off reporting. */
ISR(CAN0_ORED_IRQHandler)
{
    FlexCAN_Busoff_Error_IRQHandler(0U);
}

/* Implementation of CAN0 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 0-31. */
ISR(CAN0_ORED_0_31_MB_IRQHandler)
{
    FlexCAN_IRQHandler(0U, 0U, 31U, TRUE);
}

/* Implementation of CAN0 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 32-63. */
ISR(CAN0_ORED_32_63_MB_IRQHandler)
{
    FlexCAN_IRQHandler(0U, 32U, 63U, FALSE);
}

#if (FLEXCAN_IP_FEATURE_MBDSR_COUNT > 2U)
/* Implementation of CAN0 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 64-95. */
ISR(CAN0_ORED_64_95_MB_IRQHandler)
{
    FlexCAN_IRQHandler(0U, 64U, 95U, FALSE);
}
#endif /* #if (FLEXCAN_IP_FEATURE_MBDSR_COUNT > 2U) */

#if (FLEXCAN_INSTANCE_COUNT > 1U)
/* Implementation of CAN1 handler named in startup code for processing of Errors and Bus Off reporting. */
ISR(CAN1_ORED_IRQHandler)
{
    FlexCAN_Busoff_Error_IRQHandler(1U);
}

/* Implementation of CAN1 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 0-31. */
ISR(CAN1_ORED_0_31_MB_IRQHandler)
{
    FlexCAN_IRQHandler(1U, 0U, 31U, FALSE);
}

/* Implementation of CAN1 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 32-63. */
ISR(CAN1_ORED_32_63_MB_IRQHandler)
{
    FlexCAN_IRQHandler(1U, 32U, 63U, FALSE);
}

#endif /* (FLEXCAN_INSTANCE_COUNT > 1U) */

#if (FLEXCAN_INSTANCE_COUNT > 2U)
/* Implementation of CAN2 handler named in startup code for processing of Errors and Bus Off reporting. */
ISR(CAN2_ORED_IRQHandler)
{
    FlexCAN_Busoff_Error_IRQHandler(2U);
}

/* Implementation of CAN2 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 0-31. */
ISR(CAN2_ORED_0_31_MB_IRQHandler)
{
    FlexCAN_IRQHandler(2U, 0U, 31U, FALSE);
}

/* Implementation of CAN2 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 32-63. */
ISR(CAN2_ORED_32_63_MB_IRQHandler)
{
    FlexCAN_IRQHandler(2U, 32U, 63U, FALSE);
}

#endif /* (FLEXCAN_INSTANCE_COUNT > 2U) */

#if (FLEXCAN_INSTANCE_COUNT > 3U)
/* Implementation of CAN3 handler named in startup code for processing of Errors and Bus Off reporting. */
ISR(CAN3_ORED_IRQHandler)
{
    FlexCAN_Busoff_Error_IRQHandler(3U);
}

/* Implementation of CAN3 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 0-31. */
ISR(CAN3_ORED_0_31_MB_IRQHandler)
{
    FlexCAN_IRQHandler(3U, 0U, 31U, FALSE);
}

#endif /* (FLEXCAN_INSTANCE_COUNT > 3U) */

#if (FLEXCAN_INSTANCE_COUNT > 4U)

/* Implementation of CAN4 handler named in startup code for processing of Errors and Bus Off reporting. */
ISR(CAN4_ORED_IRQHandler)
{
    FlexCAN_Busoff_Error_IRQHandler(4U);
}

/* Implementation of CAN4 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 0-31. */
ISR(CAN4_ORED_0_31_MB_IRQHandler)
{
    FlexCAN_IRQHandler(4U, 0U, 31U, FALSE);
}

#endif /* (FLEXCAN_INSTANCE_COUNT > 4U) */

#if (FLEXCAN_INSTANCE_COUNT > 5U)

/* Implementation of CAN5 handler named in startup code for processing of Errors and Bus Off reporting. */
ISR(CAN5_ORED_IRQHandler)
{
    FlexCAN_Busoff_Error_IRQHandler(5U);
}

/* Implementation of CAN5 IRQ handler for interrupts indicating a successful
transmission or reception for Message Buffers 0-31. */
ISR(CAN5_ORED_0_31_MB_IRQHandler)
{
    FlexCAN_IRQHandler(5U, 0U, 31U, FALSE);
}

#endif /* (FLEXCAN_INSTANCE_COUNT > 5U) */

#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

/** @} */
