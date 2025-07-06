/*
 * File: TJA1042_Loop_Example_data.c
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

/* Block parameters (default storage) */
P_TJA1042_Loop_Example_T TJA1042_Loop_Example_P = {
  /* Computed Parameter: DataStoreMemory5_InitialValue
   * Referenced by: '<Root>/Data Store Memory5'
   */
  {
    0U,                                /* vendorID */
    0U,                                /* moduleID */
    0U,                                /* sw_major_version */
    0U,                                /* sw_minor_version */
    0U                                 /* sw_patch_version */
  },

  /* Expression: 1
   * Referenced by: '<S1>/Constant'
   */
  1.0,

  /* Expression: funcParams
   * Referenced by: '<Root>/Hardware_Interrupt_Handler'
   */
  { 0, 0, 1, 5, 1 },

  /* Expression: funcParams
   * Referenced by: '<S3>/Dio_WriteChannel'
   */
  { 1U, 1U },

  /* Expression: funcParams
   * Referenced by: '<S1>/Dio_WriteChannel'
   */
  { 1U, 1U },

  /* Expression: funcParams
   * Referenced by: '<S2>/Can_SetControllerMode'
   */
  3U,

  /* Expression: funcParams
   * Referenced by: '<S2>/Can_GetControllerErrorState'
   */
  17U,

  /* Expression: funcParams
   * Referenced by: '<S2>/Can_GetControllerMode'
   */
  18U,

  /* Expression: funcParams
   * Referenced by: '<S2>/Can_DisableControllerInterrupts'
   */
  4U,

  /* Expression: funcParams
   * Referenced by: '<S5>/Dio_WriteChannel'
   */
  { 1U, 1U },

  /* Expression: funcParams
   * Referenced by: '<S5>/Dio_WriteChannel1'
   */
  { 1U, 1U },

  /* Expression: funcParams
   * Referenced by: '<S2>/Can_EnableControllerInterrupts'
   */
  0U,

  /* Expression: funcParams
   * Referenced by: '<S2>/Can_GetVersionInfo'
   */
  7U,

  /* Expression: funcParams
   * Referenced by: '<Root>/Can_Write'
   */
  6U,

  /* Computed Parameter: Constant5_Value
   * Referenced by: '<Root>/Constant5'
   */
  10U,

  /* Computed Parameter: DataStoreMemory2_InitialValue
   * Referenced by: '<Root>/Data Store Memory2'
   */
  0U,

  /* Computed Parameter: DataStoreMemory4_InitialValue
   * Referenced by: '<Root>/Data Store Memory4'
   */
  0U,

  /* Computed Parameter: Constant2_Value
   * Referenced by: '<Root>/Constant2'
   */
  0U,

  /* Computed Parameter: Constant_Value_p
   * Referenced by: '<S5>/Constant'
   */
  1U,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<S5>/Constant1'
   */
  1U,

  /* Computed Parameter: Constant1_Value_a
   * Referenced by: '<Root>/Constant1'
   */
  { 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U },

  /* Computed Parameter: DataStoreMemory_InitialValue
   * Referenced by: '<Root>/Data Store Memory'
   */
  0U,

  /* Computed Parameter: DataStoreMemory1_InitialValue
   * Referenced by: '<Root>/Data Store Memory1'
   */
  0U,

  /* Computed Parameter: DataStoreMemory3_InitialValue
   * Referenced by: '<Root>/Data Store Memory3'
   */
  0U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
