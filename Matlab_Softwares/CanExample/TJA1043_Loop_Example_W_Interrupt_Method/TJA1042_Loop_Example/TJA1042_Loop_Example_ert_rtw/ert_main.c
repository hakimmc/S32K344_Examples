/*
 * File: ert_main.c
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
#include "MW_target_hardware_resources.h"

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

  TJA1042_Loop_Example_step();

  /* Get model outputs here */
  OverrunFlag--;
}

volatile boolean_T stopRequested;
volatile boolean_T runModel;
int main(int argc, char **argv)
{
  float modelBaseRate = 0.2;
  float systemClock = 160;

  /* Initialize variables */
  stopRequested = false;
  runModel = false;
  (void)argc;
  (void)argv;
  (void)systemClock;

  /* Board init */
  board_init();
  ;
  rtmSetErrorStatus(TJA1042_Loop_Example_M, 0);
  TJA1042_Loop_Example_initialize();
  s32k3_trigger_config(modelBaseRate);
  runModel =
    rtmGetErrorStatus(TJA1042_Loop_Example_M) == (NULL);
  while (runModel) {
    stopRequested = !(
                      rtmGetErrorStatus(TJA1042_Loop_Example_M) == (NULL));
    runModel = !(stopRequested);
  }

  /* Terminate model */
  TJA1042_Loop_Example_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
