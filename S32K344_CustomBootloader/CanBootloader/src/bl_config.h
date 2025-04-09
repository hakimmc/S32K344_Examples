/*
 * bl_config.h
 *
 *  Created on: 25 Mar 2025
 *      Author: hakimmc
 */

#ifndef BL_CONFIG_H_
#define BL_CONFIG_H_

#pragma once

#include "FlexCAN_Ip.h"
#include <machine/_default_types.h>
#include "C40_Ip.h"
#include "Clock_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"

/* ENUM SETUP */

typedef enum{
	NONE,
	CONFIG,
	APPLICATION
}BootMode_Enum;

typedef enum{
	CAN,
	UART
}BootType;

typedef enum{
	K125,
	K250,
	K500,
	K1000
}CAN_BAUD;

typedef enum{
	B9600,
	B115200
}UART_BAUD;

typedef enum
{
	TimeOut,
	Condition_Occured
}DelayState;

/* STRUCT SETUP */

#pragma pack(push, 1)

typedef struct
{
    // DATE (Unix timestamp)
    uint32_t unix_timestamp;            // 0x00 - 0x03

    // SYSTEM ID ve SW VERSION
    uint8_t system_id;                  // 0x04
    uint8_t sw_version_major;           // 0x05
    uint8_t sw_version_minor;           // 0x06
    uint8_t sw_version_bugfix;          // 0x07

    // BOOT SETTINGS
    BootType boot_mode:1;             // 0x08
    uint8_t boot_timeout:7;             // 0x08

    // CAN SETTINGS
    CAN_BAUD can1_baud:2;              // 0x09
    CAN_BAUD can2_baud:2;              // 0x09
    CAN_BAUD can3_baud:2;              // 0x09
    CAN_BAUD can4_baud:2;              // 0x09
    // UART + PRINTF DEBUG + COMPANY NUM
    UART_BAUD uart_baud:1;     // 0x0A
    uint8_t printf_debug:1;     // 0x0A
    uint8_t company_num:6;     // 0x0A
    // USERNAME NUM
    uint8_t username_num;                  // 0x0B

    // BMS SETTINGS
    uint8_t cell_capacity;             // 0x0C
    uint8_t series_count;              // 0x0D
    uint8_t parallel_count;            // 0x0E
    uint8_t daisychain_count;          // 0x0F

    // CELL SETTINGS (voltage thresholds)
    uint16_t max_cell_voltage;         // 0x10 - 0x11
    uint16_t min_cell_voltage;         // 0x12 - 0x13
    uint16_t temp_sensor_b;            // 0x14 - 0x15

    // DEFAULTS
    uint8_t default_soc;               // 0x16
    uint8_t default_soh;               // 0x17
    uint8_t max_temp;                  // 0x18
    uint8_t min_temp;                  // 0x19
    uint8_t temp_sensor_count;         // 0x1A
    uint8_t padding1;                  // 0x1B (0xFF)

    // MAC ADDRESS
    uint8_t mac_address[6];            // 0x1C - 0x21

    // Padding
    uint8_t padding2[6];                // 0x22 - 0x27

    char signature[8];                 // 0x28 - 0x2F → "!CFGEOC;"

} MyConfig_t;

extern MyConfig_t* config;

#pragma pack(pop)

/* CAN SETUP */

#define RX_MB_IDW 2U
#define RX_MB_IDX 1U
#define TX_MB_IDX 0U
#define RX_BOOT_WAKE_ID 0x5165U
#define RX_BOOT_ID 0x5166U
#define TX_BOOT_ID 0x5166U
#define BOOT_CCITT_KEY 0xCEFA

extern uint8_t HelloFromBoot[8];
extern uint8_t startWORD[8];
extern uint8_t jumpWORD[8];
extern uint8_t skipWORD[8];
extern uint8_t APP_MagicWORD[8];
extern uint8_t CFG_MagicWORD[8];

extern volatile uint8_t BootState;
extern volatile uint8_t JumpState;
extern BootMode_Enum BootMode;

extern Flexcan_Ip_DataInfoType rx_info;
extern Flexcan_Ip_DataInfoType tx_info;

extern uint8_t readCanIndx;
extern uint32_t systemdate;
extern uint8_t systemid;

extern Flexcan_Ip_MsgBuffType rxData;

void setupCan( void );

/* FLASH SETUP */

#define REVERSE_ENDIAN_32(x) ( \
    (((x) >> 24) & 0x000000FF) | \
    (((x) >> 8)  & 0x0000FF00) | \
    (((x) << 8)  & 0x00FF0000) | \
    (((x) << 24) & 0xFF000000) )

#define FLS_MASTER_ID 0U
#define FLS_BUF_SIZE 8

extern uint32_t CFG_ADDR_START;
extern uint32_t APP_ADDR_START;
extern uint32_t UNLOCKED_LAST_SECTOR;
extern uint32_t ERASED_LAST_SECTOR;
extern volatile uint32_t WriteIndex;
extern uint8_t FlashData[8];
extern uint8_t JumpToAppFromCfgData[8];
extern volatile uint8_t BoolOfJumpToAppCfg;

void flexcan0_Callback(uint8 instance, Flexcan_Ip_EventType eventType, uint32 buffIdx, const Flexcan_Ip_StateType *flexcanState);
uint16_t CalculateCRC(uint8_t *data, uint32_t Length);
uint8_t WriteToFlash(uint8_t* input, uint8_t max_len);
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint32 Length, uint8_t MASTER_ID);
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len);
DelayState __attribute__((optimize("O0"))) delay_ms(uint32_t ms, volatile uint8_t *condition);
void JumpToUserApplication( void );

#endif /* BL_CONFIG_H_ */
