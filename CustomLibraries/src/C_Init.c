/**
 * @file C_Init.c
 * @brief Must be init this library source file.
 * @details This file including many functions about everything.
 *
 * @author hakimmc
 * @date 2025-01-31
 */

#include "C_Init.h"

/**
 * @brief Comparing 2 data functions
 * @param source Source data
 * @param target Target data
 * @param len Length of comparasion
 * @return Result of comparasion
 */
uint8_t Comparator(uint8_t* source, uint8_t* target, uint8_t len) 
{
    for (uint8_t i = 0; i < len; i++) 
    {
        if (source[i] != target[i]) return 0;
    }
    return 1;
}