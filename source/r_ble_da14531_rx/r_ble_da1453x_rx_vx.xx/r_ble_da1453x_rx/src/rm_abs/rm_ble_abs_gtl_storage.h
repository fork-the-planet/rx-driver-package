/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_BLE_ABS_GTL_STORAGE_H
#define RM_BLE_ABS_GTL_STORAGE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ble_gtl_security.h"
#include <stdint.h>
#include <stdlib.h>
#include "r_ble_api.h"
#include "r_datfrx_rx_config.h"
#include "r_flash_dm_rx_if.h"
#if BSP_CFG_RTOS_USED == 1
#include "FreeRTOS.h"
#include "task.h"
#endif
#ifdef ENABLE_STORAGE
 #include "r_flash_rx.h"
 #include "r_ble_da1453x_config.h"
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum _datfrx_status
{
    DATFRX_IDLE,
    DATFRX_RUN_FORMAT,
    DATFRX_SUCCESS_INIT,
    DATFRX_FINISH_FORMAT,
    DATFRX_FINISH_WRITE,
    DATFRX_FINISH_ERASE,
    DATFRX_FINISH_RECLAIM,
    DATFRX_ERR
} e_datfrx_status_t;

/* Security data management information */
typedef struct rm_ble_abs_gtl_strg_mng_info
{
    uint32_t magic_num;
    uint8_t  bond_cnt;
    uint8_t  padding[3];
} rm_ble_abs_gtl_strg_mng_info_t;

/* Local device security data */
typedef struct rm_ble_abs_gtl_strg_sec_data
{
    uint8_t           loc_irk[BLE_GAP_IRK_SIZE];
    uint8_t           loc_csrk[BLE_GAP_CSRK_SIZE];
    st_ble_dev_addr_t loc_ident_addr;
    uint8_t           padding[1];      // Padding for alignment to ensure proper memory layout
} rm_ble_abs_gtl_strg_sec_data_t;

/***********************************************************************************************************************
 * Boot structure for BLE ABS GTL storage
 **********************************************************************************************************************/
typedef struct rm_ble_abs_gtl_strg_boot
{
    rm_ble_abs_gtl_strg_mng_info_t sec_data_mng_info; // Security data management information
    rm_ble_abs_gtl_strg_sec_data_t loc_dev_sec_data;  // Local device security data
} rm_ble_abs_gtl_strg_boot;

static volatile uint32_t g_proc_flag = DATFRX_IDLE;

#if(FLASH_TYPE == FLASH_TYPE_1)
static uint32_t gs_flash_dm_work[140/sizeof(uint32_t)];
#else
static uint32_t gs_flash_dm_work[(261 + (FLASH_DM_CFG_DF_DATA_NUM * 2))/sizeof(uint32_t)+1];
#endif
#define TEST_BUFF_NUM (256)
static uint8_t gs_test_w_buff[TEST_BUFF_NUM];
static uint8_t gs_test_r_buff[TEST_BUFF_NUM];

static st_flash_dm_info_t g_flash_dm_info;
static volatile uint32_t g_loop_cnt = 0;

#define LOOP_CNT (FLASH_DM_CFG_DF_DATA_NUM)

/* Please set the maximum data size. */

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define REF_DATA_IDX                        (FLASH_DM_CFG_DF_DATA_NUM - 1)     // Reference data index
#define DEFAULT_ID                          (65535U)
#define REF_DATA_SIZE                       (48U)
#define BLE_ABS_SECURE_DATA_MAGIC_NUMBER    (0x12345678)
#define ZERO_VALUE                          (0x00)
#define BOND_DATA_SINGLE                    sizeof(sec_ble_gap_bond_info_t)
/*Maximum size for bond data*/
#define BOND_DATA_TL_SIZE                   (BLE_ABS_CFG_NUMBER_BONDING * BOND_DATA_SINGLE) 

/***********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_init(uint8_t * num_of_entries);
fsp_err_t rm_ble_abs_gtl_read_bond_data(uint8_t num_of_entries, uint8_t ** addr, uint16_t * data_size);
fsp_err_t rm_ble_abs_gtl_storage_write_bond_data(uint8_t idx, uint8_t * data_addr, uint16_t data_size);
fsp_err_t rm_ble_abs_gtl_storage_update_bond_num(uint8_t act_num_bond);
fsp_err_t rm_ble_abs_gtl_storage_rel_buf(uint8_t * p_sec_data);
fsp_err_t rm_ble_abs_gtl_storage_format_operation(void);
fsp_err_t rm_ble_abs_gtl_storage_refresh_operation(void);

#ifdef ENABLE_STORAGE
void ucb_function(void* error_code);
#endif
fsp_err_t rm_ble_abs_gtl_storage_rem_all_bond_data(void);
fsp_err_t rm_ble_abs_gtl_storage_rem_specific_bond_data(uint8_t idx);
fsp_err_t rm_ble_abs_gtl_storage_get_addr(st_ble_dev_addr_t * bd_address);
fsp_err_t rm_ble_abs_gtl_storage_set_addr(st_ble_dev_addr_t * bd_address);
fsp_err_t wr_timeout(uint8_t delay_ms);
fsp_err_t rm_ble_abs_gtl_storage_upd_crypto_key(uint8_t * key, uint8_t key_size);
static void test_data_set(uint8_t * p_buf, uint32_t cnt, uint32_t inc);

#endif                                 // End of include guard
