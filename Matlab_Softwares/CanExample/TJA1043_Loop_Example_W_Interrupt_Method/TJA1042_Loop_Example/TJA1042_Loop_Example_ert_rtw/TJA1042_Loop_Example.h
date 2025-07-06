/*
 * File: TJA1042_Loop_Example.h
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

#ifndef TJA1042_Loop_Example_h_
#define TJA1042_Loop_Example_h_
#ifndef TJA1042_Loop_Example_COMMON_INCLUDES_
#define TJA1042_Loop_Example_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "Dio.h"
#include "Dio_Cfg.h"
#include "Can_43_FLEXCAN.h"
#include "SchM_Can_43_FLEXCAN.h"
#endif                               /* TJA1042_Loop_Example_COMMON_INCLUDES_ */

#include "TJA1042_Loop_Example_types.h"
#include "StandardTypes.h"
#include "rt_nonfinite.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  Std_VersionInfoType Can_GetVersionInfo;/* '<S2>/Can_GetVersionInfo' */
  uint32_T Can_GetControllerErrorState_o2;/* '<S2>/Can_GetControllerErrorState' */
  uint32_T Can_GetControllerMode_o2;   /* '<S2>/Can_GetControllerMode' */
  uint16_T Hardware_Interrupt_Handler_o2;/* '<Root>/Hardware_Interrupt_Handler' */
  uint8_T Can_Write;                   /* '<Root>/Can_Write' */
  uint8_T Can_SetControllerMode;       /* '<S2>/Can_SetControllerMode' */
  uint8_T Can_GetControllerErrorState_o1;/* '<S2>/Can_GetControllerErrorState' */
  uint8_T Can_GetControllerMode_o1;    /* '<S2>/Can_GetControllerMode' */
  uint8_T DataTypeConversion;          /* '<S1>/Data Type Conversion' */
  uint8_T DataTypeConversion_k;        /* '<S3>/Data Type Conversion' */
} B_TJA1042_Loop_Example_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c1_TJA1042_Loop_Examp;/* '<S3>/Chart' */
  uint8_T is_c1_TJA1042_Loop_Example;  /* '<S3>/Chart' */
} DW_TJA1042_Loop_Example_T;

/* Parameters (default storage) */
struct P_TJA1042_Loop_Example_T_ {
  Std_VersionInfoType DataStoreMemory5_InitialValue;
                            /* Computed Parameter: DataStoreMemory5_InitialValue
                             * Referenced by: '<Root>/Data Store Memory5'
                             */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S1>/Constant'
                                        */
  int32_T Hardware_Interrupt_Handler_P1[5];/* Expression: funcParams
                                            * Referenced by: '<Root>/Hardware_Interrupt_Handler'
                                            */
  uint32_T Dio_WriteChannel_P1[2];     /* Expression: funcParams
                                        * Referenced by: '<S3>/Dio_WriteChannel'
                                        */
  uint32_T Dio_WriteChannel_P1_b[2];   /* Expression: funcParams
                                        * Referenced by: '<S1>/Dio_WriteChannel'
                                        */
  uint32_T Can_SetControllerMode_P1;   /* Expression: funcParams
                                        * Referenced by: '<S2>/Can_SetControllerMode'
                                        */
  uint32_T Can_GetControllerErrorState_P1;/* Expression: funcParams
                                           * Referenced by: '<S2>/Can_GetControllerErrorState'
                                           */
  uint32_T Can_GetControllerMode_P1;   /* Expression: funcParams
                                        * Referenced by: '<S2>/Can_GetControllerMode'
                                        */
  uint32_T Can_DisableControllerInterrupts;/* Expression: funcParams
                                            * Referenced by: '<S2>/Can_DisableControllerInterrupts'
                                            */
  uint32_T Dio_WriteChannel_P1_b1[2];  /* Expression: funcParams
                                        * Referenced by: '<S5>/Dio_WriteChannel'
                                        */
  uint32_T Dio_WriteChannel1_P1[2];    /* Expression: funcParams
                                        * Referenced by: '<S5>/Dio_WriteChannel1'
                                        */
  uint32_T Can_EnableControllerInterrupts_;/* Expression: funcParams
                                            * Referenced by: '<S2>/Can_EnableControllerInterrupts'
                                            */
  uint32_T Can_GetVersionInfo_P1;      /* Expression: funcParams
                                        * Referenced by: '<S2>/Can_GetVersionInfo'
                                        */
  uint32_T Can_Write_P1;               /* Expression: funcParams
                                        * Referenced by: '<Root>/Can_Write'
                                        */
  uint32_T Constant5_Value;            /* Computed Parameter: Constant5_Value
                                        * Referenced by: '<Root>/Constant5'
                                        */
  uint32_T DataStoreMemory2_InitialValue;
                            /* Computed Parameter: DataStoreMemory2_InitialValue
                             * Referenced by: '<Root>/Data Store Memory2'
                             */
  uint32_T DataStoreMemory4_InitialValue;
                            /* Computed Parameter: DataStoreMemory4_InitialValue
                             * Referenced by: '<Root>/Data Store Memory4'
                             */
  uint16_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<Root>/Constant2'
                                        */
  uint8_T Constant_Value_p;            /* Computed Parameter: Constant_Value_p
                                        * Referenced by: '<S5>/Constant'
                                        */
  uint8_T Constant1_Value;             /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S5>/Constant1'
                                        */
  uint8_T Constant1_Value_a[8];        /* Computed Parameter: Constant1_Value_a
                                        * Referenced by: '<Root>/Constant1'
                                        */
  uint8_T DataStoreMemory_InitialValue;
                             /* Computed Parameter: DataStoreMemory_InitialValue
                              * Referenced by: '<Root>/Data Store Memory'
                              */
  uint8_T DataStoreMemory1_InitialValue;
                            /* Computed Parameter: DataStoreMemory1_InitialValue
                             * Referenced by: '<Root>/Data Store Memory1'
                             */
  uint8_T DataStoreMemory3_InitialValue;
                            /* Computed Parameter: DataStoreMemory3_InitialValue
                             * Referenced by: '<Root>/Data Store Memory3'
                             */
};

/* Real-time Model Data Structure */
struct tag_RTM_TJA1042_Loop_Example_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P_TJA1042_Loop_Example_T TJA1042_Loop_Example_P;

/* Block signals (default storage) */
extern B_TJA1042_Loop_Example_T TJA1042_Loop_Example_B;

/* Block states (default storage) */
extern DW_TJA1042_Loop_Example_T TJA1042_Loop_Example_DW;

/* Model entry point functions */
extern void TJA1042_Loop_Example_initialize(void);
extern void TJA1042_Loop_Example_step(void);
extern void TJA1042_Loop_Example_terminate(void);

/* Real-time Model object */
extern RT_MODEL_TJA1042_Loop_Example_T *const TJA1042_Loop_Example_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'TJA1042_Loop_Example'
 * '<S1>'   : 'TJA1042_Loop_Example/Error_Subsystem'
 * '<S2>'   : 'TJA1042_Loop_Example/Initialize Function'
 * '<S3>'   : 'TJA1042_Loop_Example/Triggered Subsystem'
 * '<S4>'   : 'TJA1042_Loop_Example/Initialize Function/CAN Transceiver Initialization'
 * '<S5>'   : 'TJA1042_Loop_Example/Initialize Function/CAN Transceiver Initialization/TJA1043'
 * '<S6>'   : 'TJA1042_Loop_Example/Triggered Subsystem/Chart'
 */
#endif                                 /* TJA1042_Loop_Example_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
