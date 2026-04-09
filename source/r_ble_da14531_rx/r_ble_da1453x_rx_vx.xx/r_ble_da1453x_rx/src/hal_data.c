/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * File Name    : hal_data.c
 * Description  :
 *********************************************************************************************************************/
/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "hal_data.h"

ble_abs_instance_ctrl_t g_ble_abs0_ctrl;

static ble_abs_pairing_parameter_t gs_abs_pairing_param =
{ .io_capabilitie_local_device = BLE_CFG_IO_CAPABILITY,
  .mitm_protection_policy = BLE_CFG_MITM_PROTECTION,
  .secure_connection_only = BLE_CFG_SECURE_CONNECTIONS,
  .local_key_distribute = (uint8_t) (BLE_CFG_SECURITY_KEY_DIST | 0),
  .remote_key_distribute = (uint8_t) (BLE_CFG_SECURITY_KEY_DIST_PEER | 0),
  .maximum_key_size = BLE_CFG_MAX_LTK_SIZE, };

ble_abs_cfg_t g_ble_abs0_cfg =
{
    .gap_callback = gap_cb,
    .vendor_specific_callback = vs_cb,
    .p_pairing_parameter = &gs_abs_pairing_param,
    .p_gatt_server_callback_list = gs_abs_gatts_cb_param,
    .gatt_server_callback_list_number = 2,
    .p_gatt_client_callback_list = gs_abs_gattc_cb_param,
    .gatt_client_callback_list_number = 2,
    .p_callback = NULL,
    .p_context = (void*) NULL,
    .p_extend = NULL
};




