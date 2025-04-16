/*
* Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @file
 * @defgroup cmd_sys System Command Library
 * @{
 * @ingroup cli
 * @brief GAP Commands
 * @details This library provides CLI for System. And exposes APIs used in the commands.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_ble_rx23w_if.h"
#include "cli/r_ble_cli.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#ifndef R_BLE_CMD_SYS_H
#define R_BLE_CMD_SYS_H

/** @defgroup cmd_sys_val Variables
 *  @{
 *  @brief Variable definition
 */
/** @brief SYS command definition. */
extern const st_ble_cli_cmd_t g_sys_cmd;

/** @brief ble reset command callback. */
extern ble_event_cb_t g_ble_host_reset_cb;

/** @brief ble command definition. */
extern const st_ble_cli_cmd_t g_ble_cmd;
/*@}*/

/** @defgroup cmd_sys_func Functions
 *  @{
 *  @brief Function definition
 */
/*******************************************************************************************************************//**
 * @brief Register a callback for "ble reset" command.
 * @details
 * This function registers a callback which initializes the upper layer after the "ble reset" command.
 * @param[in] reset_cb A callback to be registered. 
 * @retval  none
***********************************************************************************************************************/
void R_BLE_CMD_SetResetCb(ble_event_cb_t reset_cb);
/*@}*/

#endif /* R_BLE_CMD_SYS_H */
/** @} */
