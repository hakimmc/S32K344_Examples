#include "bl_config.h"

/**
 * @brief Main entry point for the bootloader.
 *
 * This function initializes clocks, CAN peripherals, IRQ handlers, and memory interfaces.
 * It sends a "Hello from Bootloader" message, waits for incoming commands or timeout,
 * and then either enters the bootloader or jumps to the user application.
 *
 * @return Always 0 (not used).
 */
int main(void)
{
    /* Load configuration struct from fixed memory address */
	config = (MyConfig_t*)0x500000;
    WriteIndex = 0;

    /* Initialize clock system */
    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);

    /* Initialize pin multiplexing */
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

    /* Initialize flash memory interface */
    C40_Ip_Init(NULL_PTR);

    /* Configure CAN interrupt */
    IntCtrl_Ip_EnableIrq(FlexCAN0_1_IRQn);
    IntCtrl_Ip_InstallHandler(FlexCAN0_1_IRQn, CAN0_ORED_0_31_MB_IRQHandler, NULL_PTR);

    /* Set polling mode for TX and RX buffers */
    tx_info.is_polling = FALSE;
    rx_info.is_polling = FALSE;

    /* Setup CAN peripheral configuration */
    setupCan();

    /* Determine flash sector locations for unlocking/erasing */
    UNLOCKED_LAST_SECTOR = C40_Ip_GetSectorNumberFromAddress(APP_ADDR_START);
	ERASED_LAST_SECTOR = UNLOCKED_LAST_SECTOR - 1;

    /* Send initial "Hello from Bootloader" message */
	FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, TX_BOOT_ID + config->system_id, HelloFromBoot);

    /* Start listening for wake-up or boot messages */
	FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDW, &rxData, FALSE);

    /**
     * Wait for either a boot command (BootState) or timeout.
     * If timeout expires without command, JumpState is triggered to launch application.
     */
    while (!JumpState && !BootState)
    {
    	delay_ms(5000 + (config->boot_timeout * 1000), &BootState);
    	JumpState = 1;

    	/* If boot command arrives during delay, wait until boot completes */
    	while (BootState);
    }

    /* Cleanup CAN and disable interrupt before jumping to user app */
    IntCtrl_Ip_DisableIrq(FlexCAN0_1_IRQn);
    FlexCAN_Ip_SetStopMode(INST_FLEXCAN_0);
    FlexCAN_Ip_Deinit(INST_FLEXCAN_0);

    /* Jump to main application */
    JumpToUserApplication();

    return 0;
}
