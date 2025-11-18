/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_ble_api.h"
#include "r_ble_gtl.h"
#include "r_ble_gtl_security.h"
#include <stdlib.h>


/***********************************************************************************************************************
 * GLobal variables
 **********************************************************************************************************************/

/* Pairing Keys storage, Default values for Just Works, Peripheral-Role*/
st_ble_gap_pairing_param_t ble_pairing_param_local =
{
    .iocap          = BLE_GAP_IOCAP_NOINPUT_NOOUTPUT,
    .mitm           = BLE_GAP_SEC_MITM_BEST_EFFORT,
    .bonding        = BLE_GAP_BONDING,
    .max_key_size   = BLE_GAP_LTK_SIZE,
    .min_key_size   = BLE_GAP_LTK_SIZE,

    .loc_key_dist   = BLE_GAP_KEY_DIST_ENCKEY,
    .rem_key_dist   = BLE_GAP_KEY_DIST_IDKEY,

    .key_notf       = BLE_GAP_SC_KEY_PRESS_NTF_NOT_SPRT,
    .sec_conn_only  = BLE_GAP_SC_BEST_EFFORT
};

/* Default values, will be replaced when generate new keys */
st_ble_gap_key_dist_t       pair_key_dist_local;
st_ble_gap_key_dist_t       pair_key_dist_tmp;


/* Bonding info for remote devices */
sec_ble_gap_bond_info_t bond_info_loc[BLE_ABS_CFG_NUMBER_BONDING_LOC];

/* Creat a LUT for connected devices */
r_ble_gtl_conn_lut_t r_ble_gtl_conn_lut[BLE_SEC_LUT_SIZE];

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
static void r_ble_gtl_sec_store_ltk_keys(uint8_t *data);

/***********************************************************************************************************************
 * Public Functions Implementation.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Return the local key distribution variable.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_loc_key_dist(void)
{
    return ble_pairing_param_local.loc_key_dist;
}

/***********************************************************************************************************************
 * Return the bonding variable.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_bond_var(void)
{
    return ble_pairing_param_local.bonding;
}

/***********************************************************************************************************************
 * Return the security connection variable.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_sec_conn_var(void)
{
    return ble_pairing_param_local.sec_conn_only;
}

/***********************************************************************************************************************
 * Execute gtl custom command (0xA001) to generate a random number. This number will be used for local security keys.
 *
 * @retval BLE_SUCCESS          Command executed succesfully .
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_sec_gen_pairing_keys(void)
{
    ble_status_t status;
    r_ble_gtl_app_gen_rand_rsp_t extdata;
    uint8_t rand_size = BLE_GAP_LTK_SIZE + BLE_GAP_EDIV_SIZE + BLE_GAP_RAND_64_BIT_SIZE + BLE_GAP_IRK_SIZE + BLE_GAP_ID_ADDR_SIZE + BLE_GAP_CSRK_SIZE;

    status = r_ble_gtl_app_get_rand_cust(rand_size, &extdata);

    r_ble_gtl_sec_store_ltk_keys((uint8_t *)&extdata.rand);

    return status;
}

/*******************************************************************************************************************//**
 *  Store to local variable EDIV,RN,LTK,CSRK keys previously generated.
 *
 * @param[in]  size             Size of random number.
 * @param[in]  data             The random number generated.
 **********************************************************************************************************************/
static void r_ble_gtl_sec_store_ltk_keys(uint8_t *data)
{
        memcpy(&pair_key_dist_local.enc_info, data, BLE_GAP_LTK_SIZE);
        data  = data + BLE_GAP_LTK_SIZE;
        memcpy(&pair_key_dist_local.mid_info, data, BLE_GAP_EDIV_SIZE + BLE_GAP_RAND_64_BIT_SIZE);
        data  = data + BLE_GAP_EDIV_SIZE + BLE_GAP_RAND_64_BIT_SIZE + BLE_GAP_IRK_SIZE + BLE_GAP_ID_ADDR_SIZE;
        memcpy(&pair_key_dist_local.sign_info, data, BLE_GAP_CSRK_SIZE);
}

/**********************************************************************************************************************
 *  Helper function to return security requirements
 * @retval uint8_t  Security requirements.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_security_req(void)
{
    uint8_t ret_val;

    /* Case of LP Just Works */
    if (ble_pairing_param_local.iocap == BLE_GAP_IOCAP_NOINPUT_NOOUTPUT)
    {
        ret_val = GAP_SEC1_NOAUTH_PAIR_ENC;
    }
    /* Case of LP Passkey */
    else if ((ble_pairing_param_local.mitm == BLE_GAP_SEC_MITM_STRICT) &&
                                                    (ble_pairing_param_local.sec_conn_only == BLE_GAP_SC_BEST_EFFORT))
    {
        ret_val = GAP_SEC1_AUTH_PAIR_ENC;
    }
    /* Case of Secure Connections */
    else if (ble_pairing_param_local.sec_conn_only == BLE_GAP_SC_STRICT)
    {
        ret_val = GAP_SEC1_SEC_PAIR_ENC;
    }
    else
    {
        ret_val = GAP_NO_SEC;
    }
    return ret_val;
}

/*******************************************************************************************************************//**
 *  Helper function to return pointer on ediv data.
 **********************************************************************************************************************/
uint16_t r_ble_gtl_sec_get_ediv_value(void)
{
    uint16_t val = (uint16_t)pair_key_dist_local.mid_info[1] + (uint16_t)(pair_key_dist_local.mid_info[0] << 8);
    return val;
}

/*******************************************************************************************************************//**
 *  Helper function to return pointer on random num data.
 **********************************************************************************************************************/
uint8_t * r_ble_gtl_sec_get_rand_value(void)
{
    uint8_t *ptr = &pair_key_dist_local.mid_info[2];
    return ptr;
}

/*******************************************************************************************************************//**
 *  Helper function to return pointer on ltk data.
 **********************************************************************************************************************/
uint8_t * r_ble_gtl_sec_get_ltk_value(void)
{
    uint8_t *ptr = &pair_key_dist_local.enc_info[0];
    return ptr;
}

/*******************************************************************************************************************//**
 *  Helper function to return pointer on csrk data.
 **********************************************************************************************************************/
uint8_t * r_ble_gtl_sec_get_csrk_value(void)
{
    uint8_t *ptr = &pair_key_dist_local.sign_info[0];
    return ptr;
}

/*******************************************************************************************************************//**
 *  Helper function to return pointer on ltk data
 * @param[in]  conn_handle      Connection handle.
 * @param[in]  ediv_in          ediv received from remote.
 * @param[in]  rand_in          random number received from remote.
 * @retval bool                 Result after comparing the received ediv & rand with local storage.
 **********************************************************************************************************************/
bool r_ble_gtl_sec_encryption_req_resp (uint16_t conn_handle, uint16_t ediv_in, uint8_t * rand_in)
{
    bool res = false;
    uint16_t stored_ediv;
    uint8_t stored_rn[BLE_GAP_RAND_64_BIT_SIZE];
    uint8_t input_rn[BLE_GAP_RAND_64_BIT_SIZE];
    uint8_t bond_index = r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, conn_handle, 0);

    stored_ediv = (uint16_t)(bond_info_loc[bond_index].p_keys.p_keys_info.mid_info[0]<<8) + (bond_info_loc[bond_index].p_keys.p_keys_info.mid_info[1]);

    memcpy(stored_rn,  &bond_info_loc[bond_index].p_keys.p_keys_info.mid_info[2], BLE_GAP_RAND_64_BIT_SIZE);
    memcpy(input_rn,  rand_in, BLE_GAP_RAND_64_BIT_SIZE);

    if (stored_ediv == ediv_in)  /* Valid EDIV*/
    {
        if (memcmp(stored_rn, input_rn, BLE_GAP_RAND_64_BIT_SIZE) == 0) /* Valid RAND*/
        {
            res = true;
        }
        else
        {
            res = false; /* Invalid RAND*/
        }
    }
    else    /* Invalid EDIV*/
    {
        res = false;
    }
    return res;
}

/**********************************************************************************************************************
 *  Helper function to return pointer on bonding DB elements
 * @param[in]  idx              Index of the DB element.
 * @retval sec_ble_gap_bond_info_t * Pointer to the DB element.
 **********************************************************************************************************************/
sec_ble_gap_bond_info_t * r_ble_gtl_sec_get_rem_bond_data(uint8_t idx)
{
	sec_ble_gap_bond_info_t *ptr = &bond_info_loc[idx];
    return ptr;
}

/**********************************************************************************************************************
 *  Helper function to return index of available - free DB 
 **********************************************************************************************************************/
static uint8_t r_ble_gtl_sec_return_free_DB (void)
{
    for (uint8_t i = 0; i< BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
    {
        if (bond_info_loc[i].p_addr.type == EMPTY_VAL ) // Check addr Type of the distributed keys
        {
        	return i;
        }
    }
    return INVALID_IDX; // No free space
}

/**********************************************************************************************************************
 *  Helper function to resolve random addr
 * @param[in]   remote_addr      Random address to resolve.
 * @param[out]  addr_solved_rsp   Pointer to resolved address.
 * @retval      uint8_t           Index of the resolved addr in DB.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_resolve_rand_addr(uint8_t *remote_addr, r_ble_gtl_gapm_addr_solved_ind_t *addr_solved_rsp)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;
    uint8_t index_found = INVALID_IDX;
    uint8_t avail_irks = 0;
    uint8_t irks[BLE_GAP_IRK_SIZE * BLE_ABS_CFG_NUMBER_BONDING_LOC];

    // Fill the irks variable from DB
    for (uint8_t i = 0; i < BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
    {
        if (bond_info_loc[i].p_addr.type != EMPTY_VAL)
        {
            memcpy(&irks[avail_irks * BLE_GAP_IRK_SIZE], &bond_info_loc[i].p_keys.p_keys_info.id_info, BLE_GAP_IRK_SIZE);
            avail_irks++;
        }
    }

    // If found at least one available IRK record, send the command
    if (avail_irks)
    {
        status = r_ble_gtl_resolve_address_from_connected_evt_cmd(0, remote_addr, avail_irks, irks, addr_solved_rsp);
        if (BLE_SUCCESS == status)
        {
            // Return index from DB, compare irk keys
            for (uint8_t i = 0; i < BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
            {
                if (memcmp(&addr_solved_rsp->key, &bond_info_loc[i].p_keys.p_keys_info.id_info, BLE_GAP_IRK_SIZE) == 0)
                {
                    index_found = i;
                }
            }
        }
    }
    return index_found;
}

/**********************************************************************************************************************
 *  Helper function to locate static addr in db
 * @param[in]   remote_addr      Static address to locate.
 * @retval      uint8_t           Index of the static addr in DB.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_find_static_addr(uint8_t *remote_addr)
{
    uint8_t index_found = INVALID_IDX;

    // Return index from DB, compare irk keys
    for (uint8_t i = 0; i < BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
    {
        if (memcmp(remote_addr, &bond_info_loc[i].p_addr.addr, BLE_BD_ADDR_LEN) == 0)
        {
            index_found = i;
        }
    }

    return index_found;
}

/**********************************************************************************************************************
 *  Helper function for LUT, support multiple connections as well
 * @param[in]  action           Action to be performed.
 * @param[in]  in_addr          Address to be added or updated.
 * @param[in]  conn_handle      Connection handle.
 * @param[in]  role             Role of the device.
 * @retval     uint8_t          Index of the DB element.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_lut_table_info(lut_actions_t action, uint8_t *in_addr, uint16_t conn_handle, uint8_t role)
{
    uint8_t *temp_addr;
    uint8_t temp_index;
    switch (action)
    {
        case ADD_ENTRY:
        {
            for (uint8_t i = 0; i < BLE_SEC_LUT_SIZE; i++)
            {
                if (!r_ble_gtl_conn_lut[i].active)
                {
                    r_ble_gtl_conn_lut[i].conn_hdl = conn_handle;
                    temp_index = r_ble_gtl_sec_return_free_DB();
                    r_ble_gtl_conn_lut[i].DB_index  = temp_index;
                    r_ble_gtl_conn_lut[i].active = true;
                    r_ble_gtl_conn_lut[i].role = role;
                    memcpy(r_ble_gtl_conn_lut[i].addr, in_addr, BLE_BD_ADDR_LEN);
                    /* Clear Data */
                    memset(&bond_info_loc[temp_index], 0x00, sizeof(sec_ble_gap_bond_info_t));
                    memcpy(&bond_info_loc[temp_index].p_addr.addr, in_addr, BLE_BD_ADDR_LEN);
                    return temp_index;
                }
            }
            break;
        }
        case UPDATE_ENTRY:
        {
            for (uint8_t i = 0; i < BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
            {
                // Read the address from DB, inside keys info.
                temp_addr = &bond_info_loc[i].p_keys.p_keys_info.id_addr_info[1];
                if (memcmp(in_addr, temp_addr, BLE_BD_ADDR_LEN) == 0)
                {
                    r_ble_gtl_conn_lut[conn_handle].conn_hdl = conn_handle;
                    r_ble_gtl_conn_lut[conn_handle].DB_index = i;
                    r_ble_gtl_conn_lut[conn_handle].active = true;
                    r_ble_gtl_conn_lut[conn_handle].role = role;
                    memcpy(r_ble_gtl_conn_lut[conn_handle].addr, in_addr, BLE_BD_ADDR_LEN);
                    return i;
                }
            }
            break;
        }
        case GET_ENTRY:
        {
            for (uint8_t i = 0; i < BLE_SEC_LUT_SIZE; i++)
            {
                if ((r_ble_gtl_conn_lut[i].active == true) && (r_ble_gtl_conn_lut[i].conn_hdl == conn_handle))
                {
                    return r_ble_gtl_conn_lut[i].DB_index;
                }
            }
            break;
        }
        case DELETE_LUT_ENTRY:
        {
            for (uint8_t i = 0; i < BLE_SEC_LUT_SIZE; i++)
            {
                if (r_ble_gtl_conn_lut[i].conn_hdl == conn_handle)
                {
                    memset(&r_ble_gtl_conn_lut[i], ZERO_VAL, sizeof(r_ble_gtl_conn_lut_t));
                }
            }
            break;
        }
        case DELETE_DB_ENTRY:
        {
            for (uint8_t i = 0; i < BLE_SEC_LUT_SIZE; i++)
            {
                if (r_ble_gtl_conn_lut[i].conn_hdl == conn_handle)
                {
                    // Clean BD as , Check if keys available, else remove data.
                    temp_index = r_ble_gtl_conn_lut[i].DB_index;
                    if ((bond_info_loc[temp_index].p_auth_info.bonding == ZERO_VAL) || (bond_info_loc[temp_index].p_auth_info.bonding == EMPTY_VAL))
                    {
                        memset(&bond_info_loc[temp_index], EMPTY_VAL, sizeof(sec_ble_gap_bond_info_t));
                    }
                }
            }
            break;
        }
        default:
        {
            break;
        }
    }

    return INVALID_IDX;
}

/**********************************************************************************************************************
 *  Helper function to return auth value from auth_info struct
 * @param[in]  db_index          Index of the DB element.
 * @retval     uint8_t           Auth value.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_db_auth(uint8_t db_index)
{
    uint8_t auth_ret = 0;

    if(bond_info_loc[db_index].p_auth_info.pair_mode == 0x02) // Secure Connections param
    {
        auth_ret |= 0x08;
    }
    if(bond_info_loc[db_index].p_auth_info.security == 0x02) // Check Authentication param, MITM
    {
        auth_ret |= 0x04;
    }
    if(bond_info_loc[db_index].p_auth_info.bonding == 0x01) // Check Bonding param
    {
        auth_ret |= 0x01;
    }

    return auth_ret;
}

/**********************************************************************************************************************
 *  Helper function to return local device role for this connection
 * @param[in]  conn_handle          Connection handle.
 * @retval     uint8_t              Role of the device.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_dev_role(uint16_t conn_handle)
{
    return r_ble_gtl_conn_lut[conn_handle].role;
}

/**********************************************************************************************************************
 *  Helper function to return active bonding DB entries
 * @retval     uint8_t              Number of active bonding entries.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_active_bond_entries(void)
{
    uint8_t active_bonding = 0;

    for (uint8_t i = 0; i < BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
    {
        if ((bond_info_loc[i].bonded != EMPTY_VAL) && (bond_info_loc[i].bonded != ZERO_VAL))
        {
            active_bonding++;
        }
    }

    return active_bonding;
}

/**********************************************************************************************************************
 *  Helper function to Clear DB in RAM
 **********************************************************************************************************************/
void r_ble_gtl_sec_clear_ram_db(void)
{
    for (uint8_t i = 0; i < BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
    {
        memset(&bond_info_loc[i], EMPTY_VAL, sizeof(sec_ble_gap_bond_info_t));
    }
}

/**********************************************************************************************************************
 *  Helper function to delete all bond info
 * @retval     fsp_err_t            Status of the operation.
 **********************************************************************************************************************/
fsp_err_t r_ble_gtl_sec_rem_all_bond_data(void)
{
    fsp_err_t err = FSP_SUCCESS;
     
    r_ble_gtl_sec_clear_ram_db();
#ifdef ENABLE_STORAGE
    r_ble_sec_data_mng_info_t sec_data_mng_info;
    memcpy(&sec_data_mng_info, (void *)BLE_ABS_SECURE_DATA_BLOCK_BASE, sizeof(r_ble_sec_data_mng_info_t));
    sec_data_mng_info.bond_cnt = 0;
    err = r_ble_gtl_storage_write_mng_info(&sec_data_mng_info);
    err = r_ble_gtl_storage_delete_bond_data(BLE_ABS_SECURE_REMOTE_INFO_BASE, BLE_ABS_SECURE_DATA_NUM_OF_BLOCKS - 1);
#endif
    return err;
}

/**********************************************************************************************************************
 *  Helper function to delete specific bond info
 * @param[in]  remote_addr          Address to be deleted.
 * @retval     fsp_err_t            Status of the operation.
 **********************************************************************************************************************/
fsp_err_t r_ble_gtl_sec_rem_specific_bond_data(ble_device_address_t *remote_addr)
{
    fsp_err_t status = FSP_ERR_NOT_FOUND;

    uint8_t bond_index = r_ble_gtl_sec_find_static_addr(remote_addr->addr);
    if (bond_index != INVALID_IDX)
    {
        // Clear RAM
        memset(&bond_info_loc[bond_index], EMPTY_VAL, sizeof(sec_ble_gap_bond_info_t));
        status = FSP_SUCCESS;
#ifdef ENABLE_STORAGE
        // Clear Flash
        uint32_t mem_offset = 0;
        mem_offset = FLASH_HP_DF_BLOCK_1 + BOND_DATA_BLOCK_SIZE * bond_index;
        status = r_ble_gtl_storage_delete_bond_data(mem_offset, BOND_DATA_BLOCK_SIZE / BLOCK_SIZE);

        // Update Magic number
        r_ble_gtl_storage_write_bond_data();
#endif
    }

    return status;
}

