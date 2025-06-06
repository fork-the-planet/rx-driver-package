/*
* Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @file
 * @defgroup cmd_abs Abstraction API Command Library
 * @{
 * @ingroup cli
 * @brief ABS API Commands
 * @details This library provides CLI for Abstraction API. And exposes APIs used in the commands.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_ble_rx23w_if.h"
#include "cli/r_ble_cli.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#ifndef R_BLE_CMD_ABS_H
#define R_BLE_CMD_ABS_H


/** @defgroup cmd_abs_val Variables
 *  @{
 *  @brief Variable definition
 */
/** @brief ABS command definition. */
extern const st_ble_cli_cmd_t g_abs_cmd;
/*@}*/

/** @defgroup cmd_abs_func Functions
 *  @{
 *  @brief Function definition
 */
/*******************************************************************************************************************//**
 * @fn void R_BLE_CMD_AbsGapCb(uint16_t type, ble_status_t result, st_ble_evt_data_t *data)
 * @brief GAP event handler.
 * @details This function shall be called from GAP callback registered by 
 *          @ref R_BLE_GAP_Init or @ref R_BLE_ABS_Init function.
***********************************************************************************************************************/
void R_BLE_CMD_AbsGapCb(uint16_t type, ble_status_t result, st_ble_evt_data_t *data);
/*@}*/

#endif /* R_BLE_CMD_ABS_H */

/** @} */
