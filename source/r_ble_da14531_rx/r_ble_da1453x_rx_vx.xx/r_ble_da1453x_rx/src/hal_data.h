/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <string.h>
#include "platform.h"
#include "rm_ble_abs.h"
#include "rm_ble_abs_api.h"
#include "r_ble_da1453x_config.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef HAL_DATA_H_
#define HAL_DATA_H_

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/
/** Access the BLE_ABS instance using these structures when calling API functions directly (::p_api is not used). */
extern ble_abs_instance_ctrl_t g_ble_abs0_ctrl;
extern ble_abs_cfg_t g_ble_abs0_cfg;
extern const ble_abs_instance_t g_ble_abs0;
/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#ifndef gap_cb
void gap_cb(uint16_t type, ble_status_t result, st_ble_evt_data_t *p_data);
#endif

#ifndef vs_cb
void vs_cb(uint16_t type, ble_status_t result, st_ble_vs_evt_data_t *p_data);
#endif

#ifndef gs_abs_gatts_cb_param
extern ble_abs_gatt_server_callback_set_t gs_abs_gatts_cb_param[];
#else
ble_abs_gatt_server_callback_set_t gs_abs_gatts_cb_param[];
#endif

#ifndef gs_abs_gattc_cb_param
extern ble_abs_gatt_client_callback_set_t gs_abs_gattc_cb_param[];
#else
ble_abs_gatt_client_callback_set_t gs_abs_gattc_cb_param[];
#endif

#endif /* HAL_DATA_H_ */
