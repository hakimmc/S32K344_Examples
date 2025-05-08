#include "bl_config.h"

int main(void)
{
	config = (MyConfig_t*)0x500000;
    WriteIndex = 0;

    Clock_Ip_Init(&Clock_Ip_aClockConfig[0]);
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
    C40_Ip_Init(NULL_PTR);
    IntCtrl_Ip_EnableIrq(FlexCAN0_1_IRQn);
    IntCtrl_Ip_InstallHandler(FlexCAN0_1_IRQn, CAN0_ORED_0_31_MB_IRQHandler, NULL_PTR);
    tx_info.is_polling = FALSE;
    rx_info.is_polling = FALSE;
    setupCan();
    UNLOCKED_LAST_SECTOR = C40_Ip_GetSectorNumberFromAddress(APP_ADDR_START);
	ERASED_LAST_SECTOR = UNLOCKED_LAST_SECTOR-1;

	FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, TX_BOOT_ID + config->system_id, HelloFromBoot);
	FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDW, &rxData, FALSE);
    while(!JumpState && !BootState)
    {
    	delay_ms(5000 + (config->boot_timeout*1000), &BootState);
    	JumpState = 1;
    	while(BootState);
    }    IntCtrl_Ip_DisableIrq(FlexCAN0_1_IRQn);
    FlexCAN_Ip_SetStopMode(INST_FLEXCAN_0);
    FlexCAN_Ip_Deinit(INST_FLEXCAN_0);
    JumpToUserApplication();
}
