/*
* Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @file
 * @defgroup cmd_vs Vendor Specific Command Library
 * @{
 * @ingroup cli
 * @brief Vendor Specific Commands
 * @details This library provides CLI for Vendor Specific(VS). And exposes APIs used in the commands.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_ble_rx23w_if.h"
#include "cli/r_ble_cli.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#ifndef R_BLE_CMD_VS_H
#define R_BLE_CMD_VS_H

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
/** @defgroup cmd_vs_val Variables
 *  @{
 *  @brief Variable definition
 */

/** @brief VS command definition. */
extern const st_ble_cli_cmd_t g_vs_cmd;
/*@}*/

/** @defgroup cmd_vs_func Functions
 *  @{
 *  @brief Function definition
 */
/*******************************************************************************************************************//**
 * @brief VS event handler.
 * @details This function shall be called from VS callback registered by 
 *          @ref R_BLE_VS_Init or @ref R_BLE_ABS_Init function.
***********************************************************************************************************************/
void R_BLE_CMD_VsCb(uint16_t type, ble_status_t result, st_ble_vs_evt_data_t *data);
/*@}*/

#endif /* R_BLE_CMD_VS_H */

/** @} */
