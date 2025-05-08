/*
 * can_callback.c
 *
 *  Created on: 25 Mar 2025
 *      Author: hakimmc
 */

#include "bl_config.h"

/**
 * @brief FlexCAN0 interrupt callback function.
 * @param instance CAN instance
 * @param eventType Event type
 * @param buffIdx Buffer index
 * @param flexcanState Pointer to CAN state
 */
void flexcan0_Callback(uint8 instance, Flexcan_Ip_EventType eventType, uint32 buffIdx, const Flexcan_Ip_StateType *flexcanState)
{
	(void)flexcanState;
	(void)instance;

	switch (eventType)
	{
		case FLEXCAN_EVENT_RX_COMPLETE:
			switch (buffIdx)
			{
				case RX_MB_IDW: // Wakeup message
					if (Comparator(rxData.data, ReadConfig_TX, 7))
					{
						if (rxData.data[7] == 0) {
							BootState = 1;
						} else __asm("NOP");
						ReportConfig(config, rxData.data[7]);
						return;
					}
					if (Comparator(rxData.data, BootStartWord_TX, 8))
					{
						BootState = 1;
						FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, TX_BOOT_ID + config->system_id, BootStartWord_RX);
						FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDW, &rxData, FALSE);
						return;
					}
					BootMode = Comparator(rxData.data, APP_MagicWORD, 4)?
							APPLICATION:(Comparator(rxData.data, CFG_MagicWORD, 4)?
							CONFIG:
							NONE
					);
					if (BootMode != NONE)
					{
						FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, TX_BOOT_ID + config->system_id, ModestartWORD);
						FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
					}
					else
					{
						BootState = 0;
						JumpState = 1;
					}
					break;
				case RX_MB_IDX: // Bootloader message
					if (BootState)
					{
						if (Comparator(rxData.data, jumpWORD, 8))
						{
							BootState = 0;
							JumpState = 1;
							break;
						}
						if (CalculateCRC(rxData.data, 6) != (uint16_t)((rxData.data[6]*256) + rxData.data[7])){ break; }

						if (!rxData.data[1])
						{
							for (int fi = 0; fi < 4; fi++)
							{
								FlashData[fi] = rxData.data[2+fi];
							}
						}
						else
						{
							for (int fi = 0; fi < 4; fi++)
							{
								FlashData[fi+4] = rxData.data[2+fi];
							}

							if (BootMode == APPLICATION && !BoolOfJumpToAppCfg)
							{
								//*(uint64_t*)((uint8_t*)&check_config + WriteIndex) = *(uint64_t*)FlashData;
								if(WriteIndex == 0 || WriteIndex == 8)
								{
									switch (WriteIndex)
									{
										case 0:
//#ifdef SwLastDateControl_Enable & SwVersionControl_Enable
											if(	!CheckSwDate(*(uint32_t*)FlashData) && !CheckSwVersion(FlashData[5], FlashData[6], FlashData[7]))
											{
												BootState = 0;
												JumpState = 1;
												return;
											}
//#endif
											break;
										case 8:
											if(!CheckMacAddr(FlashData))
											{
												BootState = 0;
												JumpState = 1;
												return;
											}
											break;
									}
								}
								if (Comparator(FlashData, JumpToAppFromCfgData, 8))
								{
									WriteIndex = 0x2000 - 8;
									BoolOfJumpToAppCfg = 1;
								}
							}
							FlashWrite(CFG_ADDR_START + WriteIndex, FlashData, FLS_BUF_SIZE, FLS_MASTER_ID);
							WriteIndex += 8;
						}

						FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, RX_BOOT_ID + config->system_id, skipWORD);
						FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
					}
					break;
			}
			break;
		default:
			break;
	}
}

uint8_t by[8];

void ReportConfig(MyConfig_t* Config, uint8_t ConfigIndex)
{
	FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, TX_BOOT_ID + config->system_id, (uint8*)(((uint64*)Config) + ConfigIndex));
	FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDW, &rxData, FALSE);
}




