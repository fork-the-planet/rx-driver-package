/*
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_BLE_GTL_SECURITY_H
#define R_BLE_GTL_SECURITY_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>
#include "rm_ble_abs_api.h"
#include "r_ble_gtl_typedef.h"
/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define NULL_TK_VAL 0x000000
#define GAPC_SECURITY_REQ   0x0C

/***********************************************************************************************************************
 * 
 * Security related structures. 
 * Keep compatibility with GTL protocol for the DA14xxx devices
 **********************************************************************************************************************/
/* GTL message header */
#pragma pack
typedef struct r_ble_gtl_msg_hdr
{
    uint16_t msg_id;
    uint16_t dest_id;
    uint16_t src_id;
    uint16_t param_length;
} r_ble_gtl_msg_hdr_t;
#pragma unpack

typedef struct gap_sec_key
{
    uint8_t key[BLE_GAP_LTK_SIZE];
} gap_sec_key_t;

/* Pairing parameters*/
typedef struct gapc_pairing
{
    uint8_t iocap;
    uint8_t oob;
    uint8_t auth;
    uint8_t key_size;
    uint8_t ikey_dist;
    uint8_t rkey_dist;
    uint8_t sec_req;
} gapc_pairing_t;

/* Long Term Key information */
#pragma pack
typedef struct gapc_ltk
{
    uint8_t ltkey[BLE_GAP_LTK_SIZE];
    uint16_t ediv;
    uint8_t nb[BLE_GAP_RAND_64_BIT_SIZE];
    uint8_t key_size;
} gapc_ltk_t;
#pragma unpack

/* Identity Resolving Key information */
typedef struct gapc_irk
{
    uint8_t key[BLE_GAP_IRK_SIZE]; /// Identity Resolving Key
    ble_device_address_t addr;
} gapc_irk_t;

/* Bonding requested by peer device indication message */
typedef struct r_ble_gtl_gapc_bond_req_ind
{
    uint8_t request; /// Bond request type (@see gapc_bond)
    union gapc_bond_req_data       /// Bond procedure requested information data
    {
        uint8_t auth_req; /// Authentication level (@see gap_auth) (if request = GAPC_PAIRING_REQ)
        uint8_t key_size; /// LTK Key Size (if request = GAPC_LTK_EXCH)
        uint8_t tk_type;  /// Device IO used to get TK: (if request = GAPC_TK_EXCH)
                          ///  - GAP_TK_OOB:       TK get from out of band method
                          ///  - GAP_TK_DISPLAY:   TK generated and shall be displayed by local device
                          ///  - GAP_TK_KEY_ENTRY: TK shall be entered by user using device keyboard
                          ///  - GAP_TK_KEY_CONFIRM: TK shall be displayed and confirmed
                                                                            ///(valid if RWBLE_SW_VERSION_MAJOR >= 8)
    } data;
    gap_sec_key_t tk;
} r_ble_gtl_gapc_bond_req_ind_t;

/* Confirm requested bond information */
#pragma pack
typedef struct r_ble_gtl_gapc_bond_cfm
{
    r_ble_gtl_msg_hdr_t hdr;
    uint8_t request;
    uint8_t accept;
    union gapc_bond_cfm_data
    {
        gapc_pairing_t pairing_feat;
        gapc_ltk_t ltk;
        gap_sec_key_t csrk;
        gap_sec_key_t tk;
    } data;
} r_ble_gtl_gapc_bond_cfm_t;
#pragma unpack

/* Bonding information indication message */
typedef struct r_ble_gtl_gapc_bond_ind
{
    uint8_t info;        /// Bond information type (@see gapc_bond)
    union gapc_bond_data /// Bond procedure information data
    {

        uint8_t auth;       /// Authentication information (@see gap_auth)
                            /// (if info = GAPC_PAIRING_SUCCEED)
        uint8_t reason;     /// Pairing failed reason  (if info = GAPC_PAIRING_FAILED)
        gapc_ltk_t ltk;     /// Long Term Key information (if info = GAPC_LTK_EXCH)
        gapc_irk_t irk;     /// Identity Resolving Key information (if info = GAPC_IRK_EXCH)
        gap_sec_key_t csrk; /// Connection Signature Resolving Key information (if info = GAPC_CSRK_EXCH)
    } data;
} r_ble_gtl_gapc_bond_ind_t;

/* Encryption requested by peer device indication message */
typedef struct r_ble_gtl_gapc_encrypt_req_ind
{
    uint16_t ediv;      /// Encryption Diversifier
    uint8_t rand_nb[8]; /// Random Number
} r_ble_gtl_gapc_encrypt_req_ind_t;

/* Encryption information indication message */
typedef struct gapc_encrypt_ind
{
    uint8_t auth; /// Authentication  level (@see gap_auth)
} gapc_encrypt_ind_t;

/* Confirm requested Encryption information */
typedef struct r_ble_gtl_gapc_encrypt_cfm
{
    r_ble_gtl_msg_hdr_t hdr;
    uint8_t found;     /// Indicate if a LTK has been found for the peer device
    gap_sec_key_t ltk; /// Long Term Key
    uint8_t key_size;  /// LTK Key Size
} r_ble_gtl_gapc_encrypt_cfm_t;

typedef struct r_ble_gtl_app_gen_rand_req
{
    r_ble_gtl_msg_hdr_t hdr;
    uint8_t rand_size;
} r_ble_gtl_app_gen_rand_req_t;

typedef struct r_ble_gtl_app_gen_rand_rsp
{
    uint8_t status;
    uint8_t rand_size;
    uint8_t rand[BLE_GAP_EDIV_SIZE + BLE_GAP_RAND_64_BIT_SIZE + BLE_GAP_LTK_SIZE];
} r_ble_gtl_app_gen_rand_rsp_t;

typedef struct gapc_security_cmd
{
    r_ble_gtl_msg_hdr_t hdr;
    uint8_t operation; /// GAPC_SECURITY_REQ: Start security request procedure
    uint8_t auth;      /// Authentication level
} gapc_security_cmd_t;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_get_loc_key_dist_var(void);
ble_status_t r_ble_gtl_sec_generate_and_store_ltk_keys_req(uint8_t size);
ble_status_t r_ble_gtl_sec_generate_and_store_ltk_keys_resp(uint8_t res, uint8_t size, uint8_t *data);
bool r_ble_gtl_sec_encryption_req_resp (uint16_t ediv_in, uint8_t * rand_in);
uint16_t r_ble_gtl_sec_ret_ediv_value(void);
uint8_t * r_ble_gtl_sec_ret_rand_value(void);
uint8_t * r_ble_gtl_sec_ret_ltk_value(void);
uint8_t get_security_requirements(void);

#endif  /* R_BLE_GTL_SECURITY_H */
