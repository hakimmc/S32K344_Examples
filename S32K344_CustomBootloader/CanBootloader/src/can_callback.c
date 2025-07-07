/*
 * can_callback.c
 *
 *  Created on: 25 Mar 2025
 *      Author: hakimmc
 */

#include "bl_config.h"

/**
 * @brief Callback function for FlexCAN0 interrupts.
 *
 * This function is triggered when an event occurs on FlexCAN0. It handles:
 *  - Wake-up messages (RX_MB_IDW)
 *  - Bootloader data packets (RX_MB_IDX)
 *  - Validates incoming data
 *  - Controls boot state and mode transitions
 *  - Performs flash writes based on received packets
 *
 * @param instance FlexCAN instance index
 * @param eventType Type of the CAN event (e.g., RX_COMPLETE)
 * @param buffIdx Message buffer index that triggered the event
 * @param flexcanState Pointer to the FlexCAN state structure
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
				case RX_MB_IDW: /**< Wakeup message buffer */

					if (Comparator(rxData.data, jumpWORD, 8))
					{
						BootState = 0;
						JumpState = 1;
						break;
					}

					if (Comparator(rxData.data, ReadConfig_TX, 7))
					{
						if (rxData.data[7] == 0) {
							BootState = 1;
						} else {
							__asm("NOP");
						}
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

					/* Determine boot mode */
					BootMode = Comparator(rxData.data, APP_MagicWORD, 4) ?
					           APPLICATION :
					           (Comparator(rxData.data, CFG_MagicWORD, 4) ? CONFIG : NONE);

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

				case RX_MB_IDX: /**< Bootloader data transfer buffer */
					if (BootState)
					{
						if (Comparator(rxData.data, jumpWORD, 8))
						{
							BootState = 0;
							JumpState = 1;
							break;
						}

						/* Validate CRC before processing data */
						if (CalculateCRC(rxData.data, 6) != (uint16_t)((rxData.data[6] << 8) + rxData.data[7]))
						{
							break;
						}

						/* First half of data */
						if (!rxData.data[1])
						{
							for (int fi = 0; fi < 4; fi++)
							{
								FlashData[fi] = rxData.data[2 + fi];
							}
						}
						else /* Second half of data */
						{
							for (int fi = 0; fi < 4; fi++)
							{
								FlashData[fi + 4] = rxData.data[2 + fi];
							}

							if ((BootMode == APPLICATION || BootMode == CONFIG)  && !BoolOfJumpToAppCfg)
							{
								if (WriteIndex == 0 || WriteIndex == 8)
								{
									switch (WriteIndex)
									{
										case 0:
											#ifdef SwLastDateControl_Enable
											#ifdef SwVersionControl_Enable
											if (!CheckSwDate(*(uint32_t*)FlashData) && !CheckSwVersion(FlashData[5], FlashData[6], FlashData[7]))
											{
												BootState = 0;
												JumpState = 1;
												return;
											}
											#endif
											#endif
											break;

										case 8:
											#ifdef SwMacAddressControl_Enable
											if (!CheckMacAddr(FlashData))
											{
												BootState = 0;
												JumpState = 1;
												return;
											}
											#endif
											break;
									}
								}

								if (Comparator(FlashData, JumpToAppFromCfgData, 8))
								{
									WriteIndex = 0x2000 - 8;
									if(BootMode == CONFIG)
									{
										FlashWrite(CFG_ADDR_START + WriteIndex, FlashData, FLS_BUF_SIZE, FLS_MASTER_ID);
										BootState = 0;
										JumpState = 1;
										FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, RX_BOOT_ID + config->system_id, skipWORD);
									}
									BoolOfJumpToAppCfg = 1;
								}
							}

							/* Write 8 bytes to flash */
							if(BootState)
							{
#ifdef FAST_PROGRAM_ENABLE
								if(!Comparator(FlashData, ((uint8_t*)(CFG_ADDR_START + WriteIndex)), 8))
								{
#endif
									FlashWrite(CFG_ADDR_START + WriteIndex, FlashData, FLS_BUF_SIZE, FLS_MASTER_ID);
#ifdef FAST_PROGRAM_ENABLE
								}
#endif
								WriteIndex += 8;
							}
						}

						/* Acknowledge reception and prepare for next */
						if(BootState)
						{
							FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, RX_BOOT_ID + config->system_id, skipWORD);
							FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDX, &rxData, FALSE);
						}
					}
					break;
			}
			break;

		default:
			break;
	}
}

/**
 * @brief Sends a configuration block via CAN.
 *
 * This function sends an 8-byte block from the configuration structure based on the
 * specified index. Each block is aligned as 64-bit words in memory.
 *
 * @param Config Pointer to the current configuration structure
 * @param ConfigIndex Index of the 64-bit word to transmit (0-based)
 */
void ReportConfig(MyConfig_t* Config, uint8_t ConfigIndex)
{
	FlexCAN_Ip_Send(INST_FLEXCAN_0, TX_MB_IDX, &tx_info, TX_BOOT_ID + config->system_id, (uint8*)((uint64*)Config + ConfigIndex));
	FlexCAN_Ip_Receive(INST_FLEXCAN_0, RX_MB_IDW, &rxData, FALSE);
}
