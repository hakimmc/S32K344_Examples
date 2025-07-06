/*
 * File: TJA1042_Loop_Example.c
 *
 * Code generated for Simulink model 'TJA1042_Loop_Example'.
 *
 * Model version                   : 1.0
 * Simulink Coder version          : 24.1 (R2024a) 19-Nov-2023
 * MBDT for S32K3 Series Version  :  Version 1.6.0 (R2021a-R2024b) 27-Jan-2025
 * C/C++ source code generated on  : Sun Jul  6 17:24:43 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TJA1042_Loop_Example.h"
#include "rtwtypes.h"
#include "TJA1042_Loop_Example_private.h"
#include <math.h>
#include "rt_nonfinite.h"

/* Named constants for Chart: '<S3>/Chart' */
#define TJA1042_Loop_Example_IN_A      ((uint8_T)1U)
#define TJA1042_Loop_Example_IN_A1     ((uint8_T)2U)
#define TJA1042_Loop_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

/* Block signals (default storage) */
B_TJA1042_Loop_Example_T TJA1042_Loop_Example_B;

/* Block states (default storage) */
DW_TJA1042_Loop_Example_T TJA1042_Loop_Example_DW;

/* Real-time model */
static RT_MODEL_TJA1042_Loop_Example_T TJA1042_Loop_Example_M_;
RT_MODEL_TJA1042_Loop_Example_T *const TJA1042_Loop_Example_M =
  &TJA1042_Loop_Example_M_;
void CanIf_TxConfirmation (PduIdType CanTxPduId)
{
  TJA1042_Loop_Example_B.Hardware_Interrupt_Handler_o2 = CanTxPduId;

#ifdef FMSTR_TX_HWOBJ

  uint8_t fmstrResult = 0u;
  fmstrResult = FMSTR_CanIsr(0u, 0u, 0u, NULL_PTR, CanTxPduId);
  if (fmstrResult) {
    return;
  }

#endif

  /* Output and update for function-call system: '<Root>/Triggered Subsystem' */
  {
    boolean_T rtb_A;

    /* S-Function (s32k3_dio): '<S3>/Dio_WriteChannel' */
    Dio_WriteChannel(DioConf_DioChannel_RGBLED0_BLUE,
                     TJA1042_Loop_Example_B.DataTypeConversion_k);

    /* Chart: '<S3>/Chart' */
    if (TJA1042_Loop_Example_DW.is_active_c1_TJA1042_Loop_Examp == 0U) {
      TJA1042_Loop_Example_DW.is_active_c1_TJA1042_Loop_Examp = 1U;
      rtb_A = true;
      TJA1042_Loop_Example_DW.is_c1_TJA1042_Loop_Example =
        TJA1042_Loop_Example_IN_A;
    } else if (TJA1042_Loop_Example_DW.is_c1_TJA1042_Loop_Example ==
               TJA1042_Loop_Example_IN_A) {
      rtb_A = false;
      TJA1042_Loop_Example_DW.is_c1_TJA1042_Loop_Example =
        TJA1042_Loop_Example_IN_A1;
    } else {
      /* case IN_A1: */
      rtb_A = true;
      TJA1042_Loop_Example_DW.is_c1_TJA1042_Loop_Example =
        TJA1042_Loop_Example_IN_A;
    }

    /* End of Chart: '<S3>/Chart' */

    /* DataTypeConversion: '<S3>/Data Type Conversion' */
    TJA1042_Loop_Example_B.DataTypeConversion_k = rtb_A;
  }
}

/* Model step function */
void TJA1042_Loop_Example_step(void)
{
  real_T tmp;

  /* S-Function (s32k3_can): '<Root>/Can_Write' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant5'
   */
  {
    Can_PduType pduInfo;
    pduInfo.id = TJA1042_Loop_Example_P.Constant5_Value;
    pduInfo.swPduHandle = TJA1042_Loop_Example_P.Constant2_Value;
    pduInfo.length = 8;
    pduInfo.sdu = &TJA1042_Loop_Example_P.Constant1_Value_a[0];
    TJA1042_Loop_Example_B.Can_Write = Can_43_FLEXCAN_Write
      (Can_43_FLEXCANConf_CanHardwareObject_CanHardwareObject_Can0_Tx_Interrupt,
       &pduInfo);
  }

  /* If: '<Root>/If1' */
  if (TJA1042_Loop_Example_B.Can_Write != 0) {
    /* Outputs for IfAction SubSystem: '<Root>/Error_Subsystem' incorporates:
     *  ActionPort: '<S1>/Action Port'
     */
    /* S-Function (s32k3_dio): '<S1>/Dio_WriteChannel' */
    Dio_WriteChannel(DioConf_DioChannel_RGBLED0_RED,
                     TJA1042_Loop_Example_B.DataTypeConversion);

    /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
     *  Constant: '<S1>/Constant'
     */
    tmp = floor(TJA1042_Loop_Example_P.Constant_Value);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 256.0);
    }

    /* DataTypeConversion: '<S1>/Data Type Conversion' */
    TJA1042_Loop_Example_B.DataTypeConversion = (uint8_T)(tmp < 0.0 ? (int32_T)
      (uint8_T)-(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp);

    /* End of Outputs for SubSystem: '<Root>/Error_Subsystem' */
  }

  /* End of If: '<Root>/If1' */
}

/* Model initialize function */
void TJA1042_Loop_Example_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Outputs for Atomic SubSystem: '<Root>/Initialize Function' */
  /* S-Function (s32k3_can): '<S2>/Can_SetControllerMode' */
  TJA1042_Loop_Example_B.Can_SetControllerMode =
    Can_43_FLEXCAN_SetControllerMode
    (Can_43_FLEXCANConf_CanController_CanController_0, CAN_CS_STARTED);

  /* S-Function (s32k3_can): '<S2>/Can_GetControllerErrorState' */
  TJA1042_Loop_Example_B.Can_GetControllerErrorState_o1 =
    Can_43_FLEXCAN_GetControllerErrorState
    (Can_43_FLEXCANConf_CanController_CanController_0,
     &TJA1042_Loop_Example_B.Can_GetControllerErrorState_o2);

  /* S-Function (s32k3_can): '<S2>/Can_GetControllerMode' */
  TJA1042_Loop_Example_B.Can_GetControllerMode_o1 =
    Can_43_FLEXCAN_GetControllerMode
    (Can_43_FLEXCANConf_CanController_CanController_0,
     &TJA1042_Loop_Example_B.Can_GetControllerMode_o2);

  /* S-Function (s32k3_can): '<S2>/Can_DisableControllerInterrupts' */
  Can_43_FLEXCAN_DisableControllerInterrupts
    (Can_43_FLEXCANConf_CanController_CanController_0);

  /* S-Function (s32k3_dio): '<S5>/Dio_WriteChannel' incorporates:
   *  Constant: '<S5>/Constant'
   */
  Dio_WriteChannel(DioConf_DioChannel_CAN0_EN_NXP,
                   TJA1042_Loop_Example_P.Constant_Value_p);

  /* S-Function (s32k3_dio): '<S5>/Dio_WriteChannel1' incorporates:
   *  Constant: '<S5>/Constant1'
   */
  Dio_WriteChannel(DioConf_DioChannel_CAN0_STB_NXP,
                   TJA1042_Loop_Example_P.Constant1_Value);

  /* S-Function (s32k3_can): '<S2>/Can_EnableControllerInterrupts' */
  Can_43_FLEXCAN_EnableControllerInterrupts
    (Can_43_FLEXCANConf_CanController_CanController_0);

  /* S-Function (s32k3_can): '<S2>/Can_GetVersionInfo' */
  Can_43_FLEXCAN_GetVersionInfo(&TJA1042_Loop_Example_B.Can_GetVersionInfo);

  /* End of Outputs for SubSystem: '<Root>/Initialize Function' */
}

/* Model terminate function */
void TJA1042_Loop_Example_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
