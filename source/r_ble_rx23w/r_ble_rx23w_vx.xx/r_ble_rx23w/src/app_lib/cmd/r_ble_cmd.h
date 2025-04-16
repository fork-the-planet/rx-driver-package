/*
* Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include <string.h>
#include <stdlib.h>
#include "r_ble_rx23w_if.h"

#ifndef R_BLE_CMD_H
#define R_BLE_CMD_H

/*******************************************************************************************************************//**
 * @brief Parse comma separated hex values.
 * @param[in] p_str    Comma separated string.
 * @param[in] p_buffer uint8_t array to store values.
 * @param[in] p_length The length of values.
 **********************************************************************************************************************/
void R_BLE_CMD_ParseValues(char *p_str, uint8_t *p_buffer, uint16_t *p_length);

/*******************************************************************************************************************//**
 * @brief Print with format like printf.
 * @param[in] p_bufffer uint8_t array to print.
 * @param[in] length    The length of values.
 **********************************************************************************************************************/
void R_BLE_CMD_PrintValues(uint8_t *p_buffer, uint16_t length);

/*******************************************************************************************************************//**
 * @brief Parse bluetooth device address, the format is 00:11:22:33:44:55.
 * @param[in] p_str  uint8_t array to parse.
 * @param[in] p_addr uint8_t array to store address.
 **********************************************************************************************************************/
void R_BLE_CMD_ParseAddr(char *p_str, uint8_t *p_addr);

/*******************************************************************************************************************//**
 * @brief Print bluetooth device address, the format is 00:11:22:33:44:55.
 * @param[in] p_addr uint8_t array to print in bluetooth device address format.
 **********************************************************************************************************************/
void R_BLE_CMD_PrintAddr(uint8_t *p_addr);

#endif /* R_BLE_CMD_H */
