/**
 * @file bl_config.h
 * @brief Bootloader configuration header file.
 *
 * @date 25 Mar 2025
 * @author hakimmc
 */

#ifndef BL_CONFIG_H__
#define BL_CONFIG_H__

#include "FlexCAN_Ip.h"
#include <machine/_default_types.h>
#include "C40_Ip.h"
#include "Clock_Ip.h"
#include "IntCtrl_Ip.h"
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"

/** @brief Enable software version control feature */
//#define SwVersionControl_Enable

/** @brief Enable software last date control feature */
//#define SwLastDateControl_Enable

/** @brief Enable software mac address control feature */
//#define SwMacAddressControl_Enable

/** @defgroup ENUMS Enumerations
 *  @{
 */

/**
 * @brief Boot mode selection
 */
typedef enum {
    NONE,       /**< No boot action */
    CONFIG,     /**< Configuration mode */
    APPLICATION /**< Application mode */
} BootMode_Enum;

/**
 * @brief Boot communication type
 */
typedef enum {
    CAN,    /**< CAN communication */
    UART    /**< UART communication */
} BootType;

/**
 * @brief CAN baud rate selection
 */
typedef enum {
    K125,   /**< 125 kbps */
    K250,   /**< 250 kbps */
    K500,   /**< 500 kbps */
    K1000   /**< 1000 kbps */
} CAN_BAUD;

/**
 * @brief UART baud rate selection
 */
typedef enum {
    B9600,      /**< 9600 bps */
    B115200     /**< 115200 bps */
} UART_BAUD;

/**
 * @brief Delay state definition
 */
typedef enum {
    TimeOut,            /**< Timeout occurred */
    Condition_Occured   /**< Condition occurred */
} DelayState;

/** @} */ // end of ENUMS

/* STRUCT SETUP */

#pragma pack(push, 1)

/**
 * @brief Configuration data structure
 */
typedef struct
{
    uint32_t unix_timestamp;          /**< Date in Unix timestamp format (0x00 - 0x03) */

    uint8_t system_id;                /**< System ID (0x04) */
    uint8_t sw_version_major;         /**< Software version major (0x05) */
    uint8_t sw_version_minor;         /**< Software version minor (0x06) */
    uint8_t sw_version_bugfix;        /**< Software version bugfix (0x07) */

    uint8_t padding1;                  /**< Padding byte (0x1B) */
    uint8_t mac_address[6];             /**< MAC address (0x1C - 0x21) */
    uint8_t padding2;                  /**< Padding byte (0x1B) */

    BootType boot_mode : 1;            /**< Boot mode selection (0x08) */
    uint8_t boot_timeout : 7;          /**< Boot timeout value (0x08) */
    CAN_BAUD can1_baud : 2;            /**< CAN1 baud rate (0x09) */
    CAN_BAUD can2_baud : 2;            /**< CAN2 baud rate (0x09) */
    CAN_BAUD can3_baud : 2;            /**< CAN3 baud rate (0x09) */
    CAN_BAUD can4_baud : 2;            /**< CAN4 baud rate (0x09) */
    UART_BAUD uart_baud : 1;           /**< UART baud rate (0x0A) */
    uint8_t printf_debug : 1;          /**< Enable printf debug (0x0A) */
    uint8_t company_num : 6;           /**< Company number (0x0A) */
    uint8_t username_num;              /**< Username number (0x0B) */
    uint8_t cell_capacity;             /**< Cell capacity (0x0C) */
    uint8_t series_count;              /**< Number of cells in series (0x0D) */
    uint8_t parallel_count;            /**< Number of cells in parallel (0x0E) */
    uint8_t daisychain_count;          /**< Daisychain count (0x0F) */

    uint16_t max_cell_voltage;         /**< Maximum cell voltage (0x10 - 0x11) */
    uint16_t min_cell_voltage;         /**< Minimum cell voltage (0x12 - 0x13) */
    uint16_t temp_sensor_b;            /**< Temperature sensor B value (0x14 - 0x15) */
    uint8_t default_soc;               /**< Default SOC (0x16) */
    uint8_t default_soh;               /**< Default SOH (0x17) */

    uint8_t max_temp;                  /**< Maximum temperature (0x18) */
    uint8_t min_temp;                  /**< Minimum temperature (0x19) */
    uint8_t temp_sensor_count;         /**< Number of temperature sensors (0x1A) */
    uint8_t padding3[5];                /**< Additional padding (0x22 - 0x27) */
    char signature[8];                 /**< Configuration signature "!CFGEOC;" (0x28 - 0x2F) */

} MyConfig_t;

extern MyConfig_t* config;
extern MyConfig_t* check_config;

#pragma pack(pop)

/* CAN SETUP */

/** @brief Receive mailbox ID word */
#define RX_MB_IDW 2U

/** @brief Receive mailbox index */
#define RX_MB_IDX 1U

/** @brief Transmit mailbox index */
#define TX_MB_IDX 0U

/** @brief Bootloader wake-up CAN ID */
#define RX_BOOT_WAKE_ID 0x5165U

/** @brief Bootloader receive CAN ID */
#define RX_BOOT_ID 0x5166U

/** @brief Bootloader transmit CAN ID */
#define TX_BOOT_ID 0x5166U

/** @brief CCITT Key for bootloader */
#define BOOT_CCITT_KEY 0xCEFA

extern uint8_t HelloFromBoot[8];
extern uint8_t ModestartWORD[8];
extern uint8_t jumpWORD[8];
extern uint8_t skipWORD[8];
extern uint8_t APP_MagicWORD[8];
extern uint8_t CFG_MagicWORD[8];
extern uint8_t BootStartWord_TX[8];
extern uint8_t BootStartWord_RX[8];
extern uint8_t ReadConfig_TX[8];
extern uint8_t ReadConfig_RX[8];

extern volatile uint8_t BootState;
extern volatile uint8_t JumpState;
extern BootMode_Enum BootMode;

extern Flexcan_Ip_DataInfoType rx_info;
extern Flexcan_Ip_DataInfoType tx_info;

extern uint8_t readCanIndx;
extern uint32_t systemdate;
extern uint8_t systemid;

extern Flexcan_Ip_MsgBuffType rxData;

/**
 * @brief Setup CAN communication parameters.
 */
void setupCan(MyConfig_t* Conf);

/** @brief Macro to reverse endianness of a 32-bit value */
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

/**
 * @brief Calculate CRC for the given data.
 *
 * @param data Pointer to the data buffer
 * @param Length Length of the data buffer
 * @return Calculated CRC value
 */
uint16_t CalculateCRC(uint8_t *data, uint32_t Length);

/**
 * @brief Write a buffer to flash memory.
 *
 * @param input Pointer to the input buffer
 * @param max_len Maximum length of the data
 * @return Operation result
 */
uint8_t WriteToFlash(uint8_t* input, uint8_t max_len);

/**
 * @brief Write data to a specific flash address.
 *
 * @param Addr Target address
 * @param Data Pointer to the data buffer
 * @param Length Length of the data
 * @param MASTER_ID Master ID for flash operation
 * @return Operation result
 */
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint32 Length, uint8_t MASTER_ID);

/**
 * @brief Compare two buffers.
 *
 * @param source Pointer to source buffer
 * @param target Pointer to target buffer
 * @param len Length to compare
 * @return 0 if match, otherwise mismatch
 */
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len);

/**
 * @brief Millisecond delay function with condition checking.
 *
 * @param ms Delay duration in milliseconds
 * @param condition Pointer to a condition variable
 * @return Delay state
 */
DelayState __attribute__((optimize("O0"))) delay_ms(uint32_t ms, volatile uint8_t *condition);

/**
 * @brief Jump to user application.
 */
void JumpToUserApplication(void);

/**
 * @brief Report Config to Gui
 */
void ReportConfig(MyConfig_t* Config, uint8_t ConfigIndex);

#ifdef SwVersionControl_Enable
/**
 * @brief Check if software version matches expected version.
 *
 * @param SwVersion Expected software version
 * @return 1 if match, 0 otherwise
 */
uint8_t CheckSwVersion(uint8_t MajorVersion, uint8_t MinorVersion, uint8_t PatchVersion);
#endif

#ifdef SwLastDateControl_Enable
/**
 * @brief Check if software date matches expected date.
 *
 * @param Date Expected date
 * @return 1 if match, 0 otherwise
 */
uint8_t CheckSwDate(uint32_t Date);
#endif

#ifdef SwMacAddressControl_Enable
/**
 * @brief Check if software date matches expected date.
 *
 * @param Date Expected date
 * @return 1 if match, 0 otherwise
 */
uint8_t CheckMacAddr(uint8_t Mac[8]);
#endif

#endif /* BL_CONFIG_H_ */
