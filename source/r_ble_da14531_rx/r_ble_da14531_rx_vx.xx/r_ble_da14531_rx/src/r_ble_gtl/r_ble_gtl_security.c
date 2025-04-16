/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
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
/* Pairing Keys storage*/
/* Default values for Just Works*/
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

st_ble_gap_key_dist_t       pair_key_dist_local;

/***********************************************************************************************************************
 * Public Functions Implementation.
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_loc_key_dist_var(void)
{
    return ble_pairing_param_local.loc_key_dist;
}

/*******************************************************************************************************************//**
 *  Execute gtl custom app command (0xA001) to DA1453x to generate a random number.
 *
 * @param[in]  size             Size of random number.
 *
 * @retval BLE_SUCCESS          Command executed succesfully .
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_sec_generate_and_store_ltk_keys_req(uint8_t size)
{
    ble_status_t status;
    status = r_ble_gtl_app_get_rand_cust(size);
    return status;
}

/*******************************************************************************************************************//**
 *  Store to local variable LTK keys previously generated.
 *
 * @param[in]  size             Size of random number.
 * @param[in]  data             The random number generated.
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_sec_generate_and_store_ltk_keys_resp(uint8_t res, uint8_t size, uint8_t *data)
{
    ble_status_t status;
    if (res == 0x00)
    {
        memcpy(&pair_key_dist_local, data, size);
        status = BLE_SUCCESS;
    }
    else
    {
        status = BLE_ERR_UNSPECIFIED;
    }
    return status;
}

/**********************************************************************************************************************
 *  Helper function to return security requirements
 **********************************************************************************************************************/
uint8_t get_security_requirements(void)
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
    else
    {
        ret_val = GAP_NO_SEC;
    }
    return ret_val;
}

/*******************************************************************************************************************//**
 *  Helper function to return pointer on ediv data.
 **********************************************************************************************************************/
uint16_t r_ble_gtl_sec_ret_ediv_value(void)
{
    uint16_t val = (uint16_t)pair_key_dist_local.mid_info[1] + (uint16_t)(pair_key_dist_local.mid_info[0] << 8);
    return val;
}

/*******************************************************************************************************************//**
 *  Helper function to return pointer on random num data.
 **********************************************************************************************************************/
uint8_t * r_ble_gtl_sec_ret_rand_value(void)
{
    uint8_t *ptr = &pair_key_dist_local.mid_info[2];
    return ptr;
}

/*******************************************************************************************************************//**
 *  Helper function to return pointer on ltk data.
 **********************************************************************************************************************/
uint8_t * r_ble_gtl_sec_ret_ltk_value(void)
{
    uint8_t *ptr = &pair_key_dist_local.enc_info[0];
    return ptr;
}

/*******************************************************************************************************************//**
 *  Helper function to return pointer on ltk data
 * @param[in]  ediv_in          ediv received from remote.
 * @param[in]  rand_in          random number received from remote.
 * @retval bool                 Result after comparing the received ediv & rand with local storage.
 **********************************************************************************************************************/
bool r_ble_gtl_sec_encryption_req_resp (uint16_t ediv_in, uint8_t * rand_in)
{
    uint16_t stored_ediv;
    uint8_t stored_rn[BLE_GAP_RAND_64_BIT_SIZE];
    uint8_t input_rn[BLE_GAP_RAND_64_BIT_SIZE];

    stored_ediv = (uint16_t)((pair_key_dist_local.mid_info[0])<<8) + (pair_key_dist_local.mid_info[1]);

    memcpy(stored_rn,  &pair_key_dist_local.mid_info[2], BLE_GAP_RAND_64_BIT_SIZE);
    memcpy(input_rn,  rand_in, BLE_GAP_RAND_64_BIT_SIZE);

    if (stored_ediv == ediv_in)  /* Valid EDIV*/
    {
        if (memcmp(stored_rn, input_rn, BLE_GAP_RAND_64_BIT_SIZE) == 0) /* Valid RAND*/
        {
            return true;
        }
    }
    else    /* Invalid EDIV*/
    {
        return false;
    }
    return false;
}
