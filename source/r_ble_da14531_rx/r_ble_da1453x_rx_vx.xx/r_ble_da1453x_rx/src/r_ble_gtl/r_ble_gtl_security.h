/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
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
#if(BLE_ABS_CFG_ENABLE_SECURE_DATA == 1)
#define ENABLE_STORAGE
#else
#undef ENABLE_STORAGE
#endif
#ifdef BLE_ABS_CFG_NUMBER_BONDING
#define BLE_ABS_CFG_NUMBER_BONDING_LOC      BLE_ABS_CFG_NUMBER_BONDING
#else
#define BLE_ABS_CFG_NUMBER_BONDING_LOC      3
#endif
/* This is fixed and DA14531 stack dependent */
#define BLE_SEC_LUT_SIZE                    3

#define NULL_TK_VAL 0x000000

#define GAPC_BOND_CMD                       0x0A    /// Start bonding procedure, Central
#define GAPC_ENCRYPT                        0x0B    /// Start encryption, Central
#define GAPC_SECURITY_REQ                   0x0C
#define MOD_OF_TK                           1000000UL

#define INVALID_IDX                         0xFF
#define EMPTY_VAL                           0xFF
#define ZERO_VAL                            0x00

/* Temporary Key Type */
typedef enum
{
    GAP_TK_OOB = 0x00, /* TK get from out of band method */
    GAP_TK_DISPLAY,    /* TK generated and shall be displayed by local device */
    GAP_TK_KEY_ENTRY,  /* TK shall be entered by user using device keyboard */
    GAP_TK_KEY_CONFIRM /* TK shall be displayed and confirmed */
} temp_key_type_t;

/* Bluetooth Address type */
typedef enum addr_types {
        PUBLIC_ADDRESS      = 0x00,    /**< Public Static Address */
        PRIVATE_ADDRESS     = 0x01,    /**< Private Random Address */
} addr_type_t;

/// Random Address type
typedef enum
{
    RAND_STATIC_ADDR = 0xC0,   /// Static random address           - 11 (MSB->LSB)
    RAND_NON_RSLV_ADDR = 0x00, /// Private non resolvable address  - 00 (MSB->LSB)
    RAND_RSLV_ADDR = 0x40,     /// Private resolvable address      - 01 (MSB->LSB)
    RAND_UNKNOWN_ADDR = 0x80,  /// Unknown address                 - 10 (MSB->LSB)
} rand_addr_type_t;
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
    uint8_t ikey_dist;  /// Initiator key distribution, the Central
    uint8_t rkey_dist;  /// Responder key distribution, the Peripheral
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
    uint8_t request ; /// Bond request type (@see gapc_bond)
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
    uint8_t padding;     /// Ignored. Any value is valid
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
    uint8_t rand[BLE_GAP_LTK_SIZE + BLE_GAP_EDIV_SIZE + BLE_GAP_RAND_64_BIT_SIZE + BLE_GAP_IRK_SIZE + BLE_GAP_ID_ADDR_SIZE + BLE_GAP_CSRK_SIZE];
} r_ble_gtl_app_gen_rand_rsp_t;

typedef struct gapc_security_cmd
{
    r_ble_gtl_msg_hdr_t hdr;
    uint8_t operation; /// GAPC_SECURITY_REQ: Start security request procedure
    uint8_t auth;      /// Authentication level
} gapc_security_cmd_t;

typedef struct gapc_security_ind
{    
    uint8_t auth;   /// Authentification level (@see gap_auth)
} gapc_security_ind_t;

/* CENTRAL_ROLE, Start Bonding command procedure */
typedef struct r_ble_gtl_gapc_bond_cmd 
{
    r_ble_gtl_msg_hdr_t hdr;    
    uint8_t operation;          /// GAP request type    
    gapc_pairing_t pairing;     /// Pairing information
}r_ble_gtl_gapc_bond_cmd_t;

/* CENTRAL_ROLE, Start Encryption command procedure */
typedef struct r_ble_gtl_gapc_encrypt_cmd
{
    r_ble_gtl_msg_hdr_t hdr;
    uint8_t operation;          /// - GAPC_ENCRYPT:  Start encryption procedure.    
    struct gapc_ltk ltk;        /// Long Term Key information
}r_ble_gtl_gapc_encrypt_cmd_t;

/** GAP security levels */
typedef enum {
        GAP_SEC_LEVEL_1         = 0x00, ///< No security
        GAP_SEC_LEVEL_2         = 0x01, ///< Unauthenticated pairing with encryption
        GAP_SEC_LEVEL_3         = 0x02, ///< Authenticated pairing with encryption
        GAP_SEC_LEVEL_4         = 0x03, ///< Authenticated LE Secure Connections pairing with
                                        ///< encryption using a 128-bit strength encryption key

} gap_sec_level_t;

/***********************************************************************************************************************
 * Random Address Resolution related structures. 
 * Keep compatibility with GTL protocol for the DA14xxx devices
 **********************************************************************************************************************/

/* Resolve Address command */
typedef struct r_ble_gtl_gapm_resolv_addr_cmd
{
    r_ble_gtl_msg_hdr_t hdr;
    uint8_t operation;                      /// GAPM_RESOLV_ADDR: Resolve device address
    uint8_t nb_key;                         /// Number of provided IRK (sahlle be > 0)
    uint8_t addr[BLE_GAP_ID_ADDR_SIZE - 1]; /// Resolvable random address to solve, exclude the type element
    uint8_t irk[0];                         /// Array of IRK used for address resolution (MSB -> LSB)
} r_ble_gtl_gapm_resolv_addr_cmd_t;

/* Indicate that resolvable random address has been solved */ 
typedef struct r_ble_gtl_gapm_addr_solved_ind
{
    uint8_t addr[BLE_GAP_ID_ADDR_SIZE - 1];     /// Resolved random address to solve, exclude the type element
    uint8_t key[BLE_GAP_IRK_SIZE];              /// IRK that correctly solved the random address
}r_ble_gtl_gapm_addr_solved_ind_t;


typedef struct BLE_PACKED_OPTION
{
    uint8_t addr[BLE_BD_ADDR_LEN];
    uint8_t type;
} sec_ble_dev_addr_t;
typedef struct BLE_PACKED_OPTION
{
    uint8_t security;		// Unauthenticated (0x01) or Authenticated (0x02)
    uint8_t pair_mode;		// Legacy(0x01) or Secure Connections (0x02)
    uint8_t bonding;		// Stores (0x00) or not the Bonding information (0x01) 
    uint8_t ekey_size;
} sec_ble_gap_auth_info_t;
typedef struct BLE_PACKED_OPTION
{ 
    uint8_t enc_info[BLE_GAP_LTK_SIZE];
    uint8_t mid_info[BLE_GAP_EDIV_SIZE + BLE_GAP_RAND_64_BIT_SIZE];
    uint8_t id_info[BLE_GAP_IRK_SIZE];
    uint8_t id_addr_info[BLE_GAP_ID_ADDR_SIZE];
    uint8_t sign_info[BLE_GAP_CSRK_SIZE];
} sec_ble_gap_key_dist_t;
typedef struct BLE_PACKED_OPTION
{
    sec_ble_gap_key_dist_t p_keys_info;
    uint8_t keys;
    uint8_t ekey_size;
} sec_ble_gap_key_ex_param_t;
typedef struct BLE_PACKED_OPTION
{
    uint8_t bonded;
    sec_ble_dev_addr_t p_addr;
    sec_ble_gap_auth_info_t p_auth_info;
    sec_ble_gap_key_ex_param_t p_keys;
} sec_ble_gap_bond_info_t;

/* Connections LUT */
typedef enum
{
    ADD_ENTRY = 0x00,
    UPDATE_ENTRY,
    GET_ENTRY,
    DELETE_LUT_ENTRY,
    DELETE_DB_ENTRY
} lut_actions_t;
typedef struct r_ble_gtl_conn_LUT
{
    bool active;                        /* Is entry in use */
    uint16_t conn_hdl;                  /* Connection handle */
    uint8_t DB_index;                   /* Corresponding entry in bond_info DB */
    uint8_t addr[BLE_BD_ADDR_LEN];      /* Un-resv addr */
    uint8_t role;                       /* Device role */
} r_ble_gtl_conn_lut_t;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
uint8_t r_ble_gtl_sec_loc_key_dist(void);
uint8_t r_ble_gtl_sec_get_bond_var(void);
uint8_t r_ble_gtl_sec_get_sec_conn_var(void);
ble_status_t r_ble_gtl_sec_gen_pairing_keys(void);
bool r_ble_gtl_sec_encryption_req_resp(uint16_t conn_handle, uint16_t ediv_in, uint8_t *rand_in);
uint16_t r_ble_gtl_sec_get_ediv_value(void);
uint8_t *r_ble_gtl_sec_get_rand_value(void);
uint8_t *r_ble_gtl_sec_get_ltk_value(void);
uint8_t *r_ble_gtl_sec_get_csrk_value(void);
uint8_t r_ble_gtl_sec_get_security_req(void);
sec_ble_gap_bond_info_t *r_ble_gtl_sec_get_rem_bond_data(uint8_t idx);
uint8_t r_ble_gtl_sec_resolve_rand_addr(uint8_t *remote_addr, r_ble_gtl_gapm_addr_solved_ind_t *addr_solved_rsp);
uint8_t r_ble_gtl_sec_lut_table_info(lut_actions_t action, uint8_t *addr, uint16_t conn_handle, uint8_t role);
uint8_t r_ble_gtl_sec_find_static_addr(uint8_t *remote_addr);
uint8_t r_ble_gtl_sec_get_db_auth(uint8_t db_index);
uint8_t r_ble_gtl_sec_get_dev_role(uint16_t conn_handle);
uint8_t r_ble_gtl_sec_get_active_bond_entries(void);
void r_ble_gtl_sec_clear_ram_db(void);
fsp_err_t r_ble_gtl_sec_rem_all_bond_data(void);
fsp_err_t r_ble_gtl_sec_rem_specific_bond_data(ble_device_address_t *remote_addr);

#endif  /* R_BLE_GTL_SECURITY_H */
