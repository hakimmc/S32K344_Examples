/**
 * @file C_Flash.h
 * @brief Must be init this library header file.
 * @details This file including many functions about Flash read/writing.
 *
 * @author hakimmc
 * @date 2025-01-31
 */

/* STANDARD LIBRARIES */
#include <stdint.h>
#include <stdlib.h>

/* GENERATED LIBRARIES */
#include "C40_Ip.h"

/* FUNCTION HEADERS */
uint8_t CRC_Calculator(uint8_t* input,uint8_t max_len);
uint8_t FlashWrite(uint32_t Addr, uint8_t* Data, uint8_t Length, uint8_t MASTER_ID);