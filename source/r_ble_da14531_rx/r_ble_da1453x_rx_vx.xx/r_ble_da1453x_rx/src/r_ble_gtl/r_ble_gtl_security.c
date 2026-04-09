/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes
 *********************************************************************************************************************/
#include "r_ble_api.h"
#include "r_ble_gtl.h"
#include "r_ble_gtl_security.h"
#include <stdlib.h>


/**********************************************************************************************************************
 * GLobal variables
 *********************************************************************************************************************/

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

/**********************************************************************************************************************
 * Private global variables and functions
 *********************************************************************************************************************/
static void r_ble_gtl_sec_store_ltk_keys(uint8_t *data);
static void r_ble_gtl_sec_defrag_db (void);
static uint8_t r_ble_gtl_sec_ret_addr_db_idx(uint8_t *remote_addr);

/**********************************************************************************************************************
 * Public Functions Implementation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Return the local key distribution variable.
 *********************************************************************************************************************/
uint8_t r_ble_gtl_sec_loc_key_dist(void)
{
    return ble_pairing_param_local.loc_key_dist;
}

/**********************************************************************************************************************
 * Return the bonding variable.
 *********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_bond_var(void)
{
    return ble_pairing_param_local.bonding;
}

/**********************************************************************************************************************
 * Return the security connection variable.
 *********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_sec_conn_var(void)
{
    return ble_pairing_param_local.sec_conn_only;
}

/**********************************************************************************************************************
 * Execute gtl custom command (0xA001) to generate a random number. This number will be used for local security keys.
 *
 * @retval BLE_SUCCESS          Command executed succesfully .
 *********************************************************************************************************************/
ble_status_t r_ble_gtl_sec_gen_pairing_keys(void)
{
    ble_status_t status;
    r_ble_gtl_app_gen_rand_rsp_t extdata;
    uint8_t rand_size = BLE_GAP_LTK_SIZE + BLE_GAP_EDIV_SIZE + BLE_GAP_RAND_64_BIT_SIZE + BLE_GAP_IRK_SIZE + 
                                                                    BLE_GAP_ID_ADDR_SIZE + BLE_GAP_CSRK_SIZE;

    status = r_ble_gtl_app_get_rand_cust(rand_size, &extdata);

    r_ble_gtl_sec_store_ltk_keys((uint8_t *)&extdata.rand);

    return status;
}

/******************************************************************************************************************//**
 *  Store to local variable EDIV,RN,LTK,CSRK keys previously generated.
 *
 * @param[in]  size             Size of random number.
 * @param[in]  data             The random number generated.
 *********************************************************************************************************************/
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
 *********************************************************************************************************************/
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

/******************************************************************************************************************//**
 *  Helper function to return pointer on ediv data.
 *********************************************************************************************************************/
uint16_t r_ble_gtl_sec_get_ediv_value(void)
{
    uint16_t val = (uint16_t)pair_key_dist_local.mid_info[1] + (uint16_t)(pair_key_dist_local.mid_info[0] << 8);
    return val;
}

/******************************************************************************************************************//**
 *  Helper function to return pointer on random num data.
 *********************************************************************************************************************/
uint8_t * r_ble_gtl_sec_get_rand_value(void)
{
    uint8_t *ptr = &pair_key_dist_local.mid_info[2];
    return ptr;
}

/******************************************************************************************************************//**
 *  Helper function to return pointer on ltk data.
 *********************************************************************************************************************/
uint8_t * r_ble_gtl_sec_get_ltk_value(void)
{
    uint8_t *ptr = &pair_key_dist_local.enc_info[0];
    return ptr;
}

/******************************************************************************************************************//**
 *  Helper function to return pointer on csrk data.
 *********************************************************************************************************************/
uint8_t * r_ble_gtl_sec_get_csrk_value(void)
{
    uint8_t *ptr = &pair_key_dist_local.sign_info[0];
    return ptr;
}

/******************************************************************************************************************//**
 *  Helper function to return pointer on ltk data
 * @param[in]  conn_handle      Connection handle.
 * @param[in]  ediv_in          ediv received from remote.
 * @param[in]  rand_in          random number received from remote.
 * @retval bool                 Result after comparing the received ediv & rand with local storage.
 *********************************************************************************************************************/
bool r_ble_gtl_sec_encryption_req_resp (uint16_t conn_handle, uint16_t ediv_in, uint8_t * rand_in)
{
    bool res = false;
    uint16_t stored_ediv;
    uint8_t stored_rn[BLE_GAP_RAND_64_BIT_SIZE];
    uint8_t input_rn[BLE_GAP_RAND_64_BIT_SIZE];
    uint8_t bond_index = r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, conn_handle, 0);
    uint8_t tmp_ltk[BLE_GAP_LTK_SIZE] = {0};

    /* Handle SC */
    if(ediv_in == 0 || rand_in == NULL)
    {
        memset(tmp_ltk, 0x00, BLE_GAP_LTK_SIZE);
        if (memcmp(&tmp_ltk, &bond_info_loc[bond_index].p_keys.p_keys_info.enc_info, 
                                                                BLE_GAP_LTK_SIZE) == 0) /* Empty LTK*/
        {
            res = false;
        }
        else
        {
            res = true;
        }
        return res;
    }

    /* Handle Legacy pairing */
    stored_ediv = (uint16_t)(bond_info_loc[bond_index].p_keys.p_keys_info.mid_info[0]<<8) 
                          + (bond_info_loc[bond_index].p_keys.p_keys_info.mid_info[1]);

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

/*********************************************************************************************************************
 *  Helper function to return pointer on bonding DB elements
 * @param[in]  idx              Index of the DB element.
 * @retval sec_ble_gap_bond_info_t * Pointer to the DB element.
 *********************************************************************************************************************/
sec_ble_gap_bond_info_t * r_ble_gtl_sec_get_rem_bond_data(uint8_t idx)
{
    sec_ble_gap_bond_info_t *ptr = &bond_info_loc[idx];
    return ptr;
}

/*********************************************************************************************************************
 *  Helper function to return index of available - free DB 
 *********************************************************************************************************************/
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

/*********************************************************************************************************************
 *  Helper function to resolve random addr
 * @param[in]   remote_addr      Random address to resolve.
 * @param[out]  addr_solved_rsp   Pointer to resolved address.
 * @retval      uint8_t           Index of the resolved addr in DB.
 *********************************************************************************************************************/
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
            memcpy(&irks[avail_irks * BLE_GAP_IRK_SIZE], &bond_info_loc[i].p_keys.p_keys_info.id_info, 
                                                                                    BLE_GAP_IRK_SIZE);
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
/*********************************************************************************************************************
 *  Helper function to locate static addr in db
 * @param[in]   remote_addr      Static address to locate.
 * @retval      uint8_t           Index of the static addr in DB.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_ret_addr_db_idx(uint8_t *remote_addr)
{
    uint8_t index_found = INVALID_IDX;

    // Return index from DB, static check
    for (uint8_t i = 0; i < BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
    {
        if (memcmp(remote_addr, &bond_info_loc[i].p_addr.addr, BLE_BD_ADDR_LEN) == 0)
        {
            return i;
        }
    }

    // Return index from DB, random check
    for (uint8_t i = 0; i < BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
    {
        if(memcmp(remote_addr, &bond_info_loc[i].p_keys.p_keys_info.id_addr_info[1], BLE_BD_ADDR_LEN) == 0)
        {
            return i;
        }
    }

    return index_found;
}

/*********************************************************************************************************************
 *  Helper function for LUT, support multiple connections as well
 * @param[in]  action           Action to be performed.
 * @param[in]  in_addr          Address to be added or updated.
 * @param[in]  conn_handle      Connection handle.
 * @param[in]  role             Role of the device.
 * @retval     uint8_t          Index of the DB element.
 *********************************************************************************************************************/
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
                    memcpy(r_ble_gtl_conn_lut[conn_handle].addr, &bond_info_loc[i].p_addr.addr, BLE_BD_ADDR_LEN);
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
                    if ((bond_info_loc[temp_index].p_auth_info.bonding == ZERO_VAL) 
                        || (bond_info_loc[temp_index].p_auth_info.bonding == EMPTY_VAL))
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

/*********************************************************************************************************************
 *  Helper function to return auth value from auth_info struct
 * @param[in]  db_index          Index of the DB element.
 * @retval     uint8_t           Auth value.
 *********************************************************************************************************************/
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

/*********************************************************************************************************************
 *  Helper function to return local device role for this connection
 * @param[in]  conn_handle          Connection handle.
 * @retval     uint8_t              Role of the device.
 *********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_dev_role(uint16_t conn_handle)
{
    return r_ble_gtl_conn_lut[conn_handle].role;
}

/*********************************************************************************************************************
 *  Helper function to return active bonding DB entries
 * @retval     uint8_t              Number of active bonding entries.
 *********************************************************************************************************************/
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

/*********************************************************************************************************************
 *  Helper function to Clear DB in RAM
 *********************************************************************************************************************/
void r_ble_gtl_sec_clear_ram_db(void)
{
    for (uint8_t i = 0; i < BLE_ABS_CFG_NUMBER_BONDING_LOC; i++)
    {
        memset(&bond_info_loc[i], EMPTY_VAL, sizeof(sec_ble_gap_bond_info_t));
    }
}

/*********************************************************************************************************************
 *  Helper function to delete all bond info
 * @retval     fsp_err_t            Status of the operation.
 **********************************************************************************************************************/
void  r_ble_gtl_sec_rem_all_bond_data(void)
{
    r_ble_gtl_sec_clear_ram_db();
}

/*********************************************************************************************************************
 *  Helper function to delete specific bond info
 * @param[in]  remote_addr          Address to be deleted.
 * @retval     fsp_err_t            Status of the operation.
 *********************************************************************************************************************/
fsp_err_t r_ble_gtl_sec_rem_specific_bond_data(ble_device_address_t *remote_addr, uint8_t *ret_idx)
{
    fsp_err_t status = FSP_ERR_NOT_FOUND;
    *ret_idx = ZERO_VAL;
    uint8_t bond_index = INVALID_IDX;

    bond_index = r_ble_gtl_sec_ret_addr_db_idx((uint8_t*)remote_addr);
    
    if (bond_index != INVALID_IDX)
    {
        memset(&bond_info_loc[bond_index], EMPTY_VAL, sizeof(sec_ble_gap_bond_info_t));
        *ret_idx = bond_index;
        r_ble_gtl_sec_defrag_db();
        status = FSP_SUCCESS;        
    }    
    return status;
}

/**********************************************************************************************************************
 *  Helper function to handle a remote device with a resolvable random address
 * @param[in]  p_gap_conn_evt_param  Pointer to the connection event parameters.
 **********************************************************************************************************************/
static void r_ble_gtl_sec_handle_rand_addr(st_ble_gap_conn_evt_t * p_gap_conn_evt_param)
{
    r_ble_gtl_gapm_addr_solved_ind_t addr_solved_rsp;
    sec_ble_gap_bond_info_t *bond_info_loc_tmp = {0};
    uint8_t auth_val = 0;
    uint8_t db_index = INVALID_IDX;

    // Look for available IRKs in DB & send resolve cmd
    db_index = r_ble_gtl_sec_resolve_rand_addr(p_gap_conn_evt_param->remote_addr, &addr_solved_rsp);
    // KNOWN address
    if (db_index != INVALID_IDX)
    {
        auth_val = r_ble_gtl_sec_get_db_auth(db_index);

        /* Send the GAPC_CONNECTION_CFM cmd*/
        r_ble_gtl_connection_cfm_cmd(p_gap_conn_evt_param->conn_hdl, auth_val);

        // Update LUT using the resolved address, maybe moved to different conn handle.
        bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(db_index);

        /* Update conn info in bond_info_loc*/
        memcpy(bond_info_loc_tmp->p_addr.addr, p_gap_conn_evt_param->remote_addr, BLE_BD_ADDR_LEN);
        bond_info_loc_tmp->p_addr.type = p_gap_conn_evt_param->remote_addr_type;

        r_ble_gtl_sec_lut_table_info(UPDATE_ENTRY, &bond_info_loc_tmp->p_keys.p_keys_info.id_addr_info[1], 
                                    p_gap_conn_evt_param->conn_hdl, p_gap_conn_evt_param->role);

        /* Automaticaly try encryption, since IRK availabe bonding data exist */        
        if (r_ble_gtl_sec_get_dev_role(p_gap_conn_evt_param->conn_hdl) == R_BLE_GTL_CENTRAL_ROLE)
        {
            r_ble_gtl_send_enc_cmd(p_gap_conn_evt_param->conn_hdl);
        }
        else                                                                                       
        {
            // PERIPHERAL_ROLE
            /* Expect the remote device -> Central to send the encryption command 
                                            and respond through GAPC_ENCRYPT_CFM handler */
        }
    }
    else
    {
        /* Send the GAPC_CONNECTION_CFM cmd*/
        r_ble_gtl_connection_cfm_cmd(p_gap_conn_evt_param->conn_hdl, auth_val);

        /* Generate and register keys */
        r_ble_gtl_sec_gen_pairing_keys();
        
        /* New record, new LUT */
        r_ble_gtl_sec_lut_table_info(ADD_ENTRY, p_gap_conn_evt_param->remote_addr, 
                                                p_gap_conn_evt_param->conn_hdl, p_gap_conn_evt_param->role);
        uint8_t bond_index = r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, p_gap_conn_evt_param->conn_hdl, 0);
        bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(bond_index);

        /* Add conn info in bond_info_loc*/
        memcpy(bond_info_loc_tmp->p_addr.addr, p_gap_conn_evt_param->remote_addr, BLE_BD_ADDR_LEN);
        bond_info_loc_tmp->p_addr.type = p_gap_conn_evt_param->remote_addr_type;
    }
}

/**********************************************************************************************************************
 *  Helper function to handle a remote device with a static address
 * @param[in]  p_gap_conn_evt_param  Pointer to the connection event parameters.
 **********************************************************************************************************************/
static void r_ble_gtl_sec_handle_static_addr(st_ble_gap_conn_evt_t * p_gap_conn_evt_param)
{
    sec_ble_gap_bond_info_t *bond_info_loc_tmp = {0};
    uint8_t auth_val = 0;
    uint8_t db_index = INVALID_IDX;

    db_index = r_ble_gtl_sec_ret_addr_db_idx(p_gap_conn_evt_param->remote_addr);
    // KNOWN address
    if (INVALID_IDX != db_index)
    {
        auth_val = r_ble_gtl_sec_get_db_auth(db_index);

        /* Send the GAPC_CONNECTION_CFM cmd*/
        r_ble_gtl_connection_cfm_cmd(p_gap_conn_evt_param->conn_hdl, auth_val);

        /* UPDATE conn handle if changed */
        r_ble_gtl_sec_lut_table_info(UPDATE_ENTRY, p_gap_conn_evt_param->remote_addr,
                                                   p_gap_conn_evt_param->conn_hdl, p_gap_conn_evt_param->role);

        /* Automaticaly try encryption, since bonding data exist */        
        if (r_ble_gtl_sec_get_dev_role(p_gap_conn_evt_param->conn_hdl) == R_BLE_GTL_CENTRAL_ROLE)
        {
            r_ble_gtl_send_enc_cmd(p_gap_conn_evt_param->conn_hdl);
        }
        else
        {
            // PERIPHERAL_ROLE
            /* Expect the remote device -> Central to send the encryption command 
                                            and respond through GAPC_ENCRYPT_CFM handler */
        }
    }
    else
    {
        /* Send the GAPC_CONNECTION_CFM cmd*/
        r_ble_gtl_connection_cfm_cmd(p_gap_conn_evt_param->conn_hdl, auth_val);
        /* Generate and register keys */
        r_ble_gtl_sec_gen_pairing_keys();

        /* New record, new LUT */
        db_index = r_ble_gtl_sec_lut_table_info(ADD_ENTRY, p_gap_conn_evt_param->remote_addr, 
                                                p_gap_conn_evt_param->conn_hdl, p_gap_conn_evt_param->role);

        /* Add address information to DB, case IRK data is not exchanged. This applies to STATIC address */
        bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(db_index);

        bond_info_loc_tmp->p_addr.type = p_gap_conn_evt_param->remote_addr_type;
        memcpy(bond_info_loc_tmp->p_addr.addr, p_gap_conn_evt_param->remote_addr, BLE_BD_ADDR_LEN);

        bond_info_loc_tmp->p_keys.p_keys_info.id_addr_info[0] = p_gap_conn_evt_param->remote_addr_type;
        memcpy(&bond_info_loc_tmp->p_keys.p_keys_info.id_addr_info[1],
                                   p_gap_conn_evt_param->remote_addr, BLE_BD_ADDR_LEN);
    }
}

/**********************************************************************************************************************
 *  Helper function to handle a remote device with a resolvable random address or static address
 * @param[in]  p_gap_conn_evt_param  Pointer to the connection event parameters.
 **********************************************************************************************************************/
void r_ble_gtl_sec_handle_conn_addr(st_ble_gap_conn_evt_t * p_gap_conn_evt_param)
{
    if (p_gap_conn_evt_param->remote_addr_type == BLE_GAP_ADDR_RAND) // RANDOM ADDRESS
    {
        r_ble_gtl_sec_handle_rand_addr(p_gap_conn_evt_param);
    }
    else if (p_gap_conn_evt_param->remote_addr_type == BLE_GAP_ADDR_PUBLIC) // STATIC ADDRESS
    {
        r_ble_gtl_sec_handle_static_addr(p_gap_conn_evt_param);
    }
    else
    {
        // Nothing to do, address type not supported.
    }
}

/**********************************************************************************************************************
 *  Helper function to handle the keys the remote device has distributed. These keys are stored in the RAM DB
 * @param[in]  p_peer_key          Pointer to the keys.
 **********************************************************************************************************************/
void r_ble_gtl_sec_recvremkeys(st_ble_gap_peer_key_info_evt_t *p_peer_key)
{

    uint8_t bond_index =  r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, p_peer_key->conn_hdl, 0);
    sec_ble_gap_bond_info_t *bond_info_loc_tmp = {0};
    bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(bond_index);


    bond_info_loc_tmp->p_keys.keys = bond_info_loc_tmp->p_keys.keys | p_peer_key->key_ex_param.keys;
    switch (p_peer_key->key_ex_param.keys)
    {
        case 1: // LTK
        {
            // Peripheral role. Save the LTK only in Secure Connections.
            if (r_ble_gtl_sec_get_sec_conn_var() == BLE_GAP_SC_STRICT)
            {
                memcpy(bond_info_loc_tmp->p_keys.p_keys_info.enc_info, 
                       p_peer_key->key_ex_param.p_keys_info->enc_info, BLE_GAP_LTK_SIZE);
            }
            // Central role, will receive and must store LTK + EDIV + RN in Legacy Pairing
            if ((r_ble_gtl_sec_get_dev_role(p_peer_key->conn_hdl) == R_BLE_GTL_CENTRAL_ROLE) &&
                (r_ble_gtl_sec_get_sec_conn_var() == BLE_GAP_SC_BEST_EFFORT))
            {
                memcpy(bond_info_loc_tmp->p_keys.p_keys_info.enc_info, 
                       p_peer_key->key_ex_param.p_keys_info->enc_info, BLE_GAP_LTK_SIZE);
                memcpy(bond_info_loc_tmp->p_keys.p_keys_info.mid_info, 
                       p_peer_key->key_ex_param.p_keys_info->mid_info, BLE_GAP_RAND_64_BIT_SIZE + BLE_GAP_EDIV_SIZE);
            }
        }
        break;

        case 2: // IRK
        {
            memcpy(bond_info_loc_tmp->p_keys.p_keys_info.id_info, 
                   p_peer_key->key_ex_param.p_keys_info->id_info, BLE_GAP_IRK_SIZE);
            /* Store Address here since BOND_IND is providing it. */
            if (p_peer_key->bd_addr.addr[5] != 0x00)
            {
                /* Save resolved remote address to Identity address */
                bond_info_loc_tmp->p_keys.p_keys_info.id_addr_info[0] = p_peer_key->bd_addr.type;
                memcpy(&bond_info_loc_tmp->p_keys.p_keys_info.id_addr_info[1],
                        p_peer_key->bd_addr.addr, BLE_BD_ADDR_LEN);
            }
        }
        break;
        
        case 4: // CSRK
        {
            memcpy(bond_info_loc_tmp->p_keys.p_keys_info.sign_info, 
                    p_peer_key->key_ex_param.p_keys_info->sign_info, BLE_GAP_CSRK_SIZE);
        }
        break;
    }

}

/**********************************************************************************************************************
 *  Helper function to clear DB on disconnection
 * @param[in]  conn_hdl           Connection handle.
 **********************************************************************************************************************/
void r_ble_gtl_sec_clear_db_on_disconn(uint16_t conn_hdl)
{
    /* Free DB entry if empty */
    r_ble_gtl_sec_lut_table_info(DELETE_DB_ENTRY, NULL, conn_hdl, 0);
    /* Free LUT entry */
    r_ble_gtl_sec_lut_table_info(DELETE_LUT_ENTRY, NULL, conn_hdl, 0);
}

/**********************************************************************************************************************
 *  Helper function to support the key exchange process, replacing R_BLE_GAP_ReplyExKeyInfoReq()
 *  Local is requested to send the keys to remote device.
 * @param[in]  conn_hdl           Connection handle.
 **********************************************************************************************************************/
void r_ble_gtl_sec_ReplyExKeyInfoReq(uint16_t conn_hdl)
{
    ble_status_t status           = BLE_ERR_UNSUPPORTED;
    uint8_t      loc_key_dist_var = (uint8_t)(conn_hdl >> 8);

    /* Clear the top byte */
    conn_hdl = conn_hdl & R_BLE_GTL_SRC_ID_MASK;

    /* The command does not have the key as separate param, 
       for this reason the key is hidden in the first byte of conn_hdl */
    if (loc_key_dist_var == R_BLE_GTL_GAPC_LTK_EXCH)
    {
        status = r_ble_gtl_send_gapc_bond_cfm(conn_hdl, R_BLE_GTL_GAPC_LTK_EXCH, true, NULL_TK_VAL);
    }
    if (loc_key_dist_var == R_BLE_GTL_GAPC_IRK_EXCH)
    {
        status = r_ble_gtl_send_gapc_bond_cfm(conn_hdl, R_BLE_GTL_GAPC_IRK_EXCH, true, NULL_TK_VAL);
    }
    if (loc_key_dist_var == R_BLE_GTL_GAPC_CSRK_EXCH)
    {
        status = r_ble_gtl_send_gapc_bond_cfm(conn_hdl, R_BLE_GTL_GAPC_CSRK_EXCH, true, NULL_TK_VAL);
    }

    FSP_PARAMETER_NOT_USED(status);
}

/**********************************************************************************************************************
 *  Helper function to support the key exchange process, R_BLE_GAP_ReplyLtkReq()
 *  Local is requested to send the LTK to remote device. Encryption process.
 * @param[in]  p_ltk_req          Pointer to the LTK request parameters.
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_sec_ReplyLtkReq(uint16_t conn_hdl, uint16_t ediv, uint8_t * p_peer_rand, uint8_t response)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;
    FSP_PARAMETER_NOT_USED(response);

    if (r_ble_gtl_sec_get_sec_conn_var() != BLE_GAP_SC_STRICT)
    {
        /* Handle LEGACY PAIRING */
        bool comp_resp = r_ble_gtl_sec_encryption_req_resp(conn_hdl, ediv, p_peer_rand);

        if (comp_resp)
        {
            /* Values found in db */
            status = r_ble_gtl_send_gapc_encrypt_cfm(conn_hdl, BLE_GAP_LTK_REQ_ACCEPT);
        }
        else
        {
            /* Values NOT found in db */
            status = r_ble_gtl_send_gapc_encrypt_cfm(conn_hdl, BLE_GAP_LTK_REQ_DENY);
        }
        /* Notify the application */
        if (status == BLE_SUCCESS)
        {
            status = r_ble_gtl_gapc_ltk_rsp_comp(conn_hdl, comp_resp);
        }
    }
    else
    {
        /* Handle SECURE CONNECTIONS */
        status = r_ble_gtl_send_gapc_encrypt_cfm(conn_hdl, BLE_GAP_LTK_REQ_ACCEPT);
        if (status == BLE_SUCCESS)
        {
            status = r_ble_gtl_gapc_ltk_rsp_comp(conn_hdl, true);
        }
    }
    return status;
}

/**********************************************************************************************************************
 *  Helper function that acts upon the completion of the pairing process. BLE_GAP_EVENT_PAIRING_COMP
 * @param[in]  conn_hdl           Connection handle.
 **********************************************************************************************************************/
void r_ble_gtl_sec_pairing_complete(st_ble_gap_pairing_info_evt_t *p_param, 
                                    uint8_t *bond_idx, uint8_t *bond_size, uint8_t **bonded_addr)
{
    uint8_t bond_index = r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, p_param->conn_hdl, 0);
    sec_ble_gap_bond_info_t *bond_info_loc_tmp = {0};
    bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(bond_index);

    /* Save authentication info */
    bond_info_loc_tmp->p_auth_info.bonding = p_param->auth_info.bonding;
    bond_info_loc_tmp->p_auth_info.security = p_param->auth_info.security;
    bond_info_loc_tmp->p_auth_info.pair_mode = p_param->auth_info.pair_mode;
    bond_info_loc_tmp->p_auth_info.ekey_size = p_param->auth_info.ekey_size;

    bond_info_loc_tmp->bonded = bond_index + 1;
    *bond_idx = bond_index + 1; // Update the bond index
    *bond_size = sizeof(sec_ble_gap_bond_info_t);
    *bonded_addr = (uint8_t*)bond_info_loc_tmp;
}

void r_ble_gtl_sec_pairing_failed(uint16_t conn_hdl)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    // Nothing to do here, just a placeholder for future use.
    // r_ble_gtl_sec_lut_table_info(DELETE_DB_ENTRY, NULL, conn_hdl, 0);
}

/**********************************************************************************************************************
 *  Helper function to push bond data to RAM
 * @param[in]  p_bond_addr       Pointer to the bond address.
 * @param[in]  bond_size         Size of the bond data.
 * @retval     fsp_err_t         Status of the operation.
 **********************************************************************************************************************/
fsp_err_t r_ble_gtl_sec_push_bond_data_to_ram (uint8_t *p_bond_addr, uint16_t bond_size)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t bond_mun = (uint8_t)(bond_size / sizeof(sec_ble_gap_bond_info_t));

    if (bond_mun < BLE_ABS_CFG_NUMBER_BONDING_LOC)
    {
        for(uint8_t i = 0; i < bond_mun; i++)
        {
            memcpy(&bond_info_loc[i], p_bond_addr, sizeof(sec_ble_gap_bond_info_t));
            p_bond_addr += sizeof(sec_ble_gap_bond_info_t);
        }
    }
    else
    {
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    return err;
}

/**********************************************************************************************************************
 *  Helper function to defragment the bonding DB before saving it to flash.
 *  This function will remove EMPTY entries and shift VALID entries to the front of the DB.
 * @retval     none
 **********************************************************************************************************************/
static void r_ble_gtl_sec_defrag_db (void)
{
    uint8_t bond_idx = ZERO_VAL;
    uint8_t mun_of_rep = BLE_ABS_CFG_NUMBER_BONDING_LOC - 1;
    bool is_empty = false;
    uint8_t tcpy = EMPTY_VAL;
    bool update_lut = false;

    do
    {
        // Found EMPTY
        if((bond_info_loc[bond_idx].bonded == EMPTY_VAL)&&(!is_empty))
        {
            is_empty = true;
            tcpy = bond_idx;
        }

        // Found VALID entry
        if((bond_info_loc[bond_idx].bonded != EMPTY_VAL)&&(bond_info_loc[bond_idx].bonded != ZERO_VAL)&&(is_empty))
        {
            memcpy(&bond_info_loc[tcpy], &bond_info_loc[bond_idx], sizeof(sec_ble_gap_bond_info_t));
            memset(&bond_info_loc[bond_idx], EMPTY_VAL, sizeof(sec_ble_gap_bond_info_t));
            bond_info_loc[tcpy].bonded = tcpy + 1;

            is_empty = false; 
            bond_idx = 0; // Reset bond_idx to start from the beginning
            mun_of_rep = BLE_ABS_CFG_NUMBER_BONDING_LOC;
        }
        bond_idx++;
    } while (ZERO_VAL < --mun_of_rep);

    // Update LUT with the new DB indexes
    for (uint8_t i = 0; i < BLE_SEC_LUT_SIZE; i++)
    {
        if (r_ble_gtl_conn_lut[i].active)
        {
            update_lut = true; // Assume we need to update the LUT
            for (uint8_t j = 0; j < BLE_ABS_CFG_NUMBER_BONDING_LOC; j++)
            {
                if (memcmp(r_ble_gtl_conn_lut[i].addr, bond_info_loc[j].p_addr.addr, BLE_BD_ADDR_LEN) == 0)
                {
                    r_ble_gtl_conn_lut[i].DB_index = j;
                    update_lut = false; // LUT already updated
                    break;
                }
            }
            // If we did not find the address in the DB, we need to assign a new db index in LUT
            if (update_lut)
            {
                r_ble_gtl_conn_lut[i].DB_index = r_ble_gtl_sec_return_free_DB();
                bond_info_loc[r_ble_gtl_conn_lut[i].DB_index].bonded = 0x00;
            }
        }
    }
}
