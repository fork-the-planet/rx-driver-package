#ifndef R_BLE_GTL_TYPEDEF_H_
#define R_BLE_GTL_TYPEDEF_H_

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
#define R_BLE_GTL_GAP_SEC_KEY_LEN               16
#define R_BLE_GTL_ATT_SEC_ENC_KEY_SIZE          16

/***********************************************************************************************************************
 * Enumerations
 **********************************************************************************************************************/
/*Bond event type.*/ 
typedef enum r_ble_gtl_gapc_bond
{
    R_BLE_GTL_GAPC_PAIRING_REQ,         /// Bond Pairing request
    R_BLE_GTL_GAPC_PAIRING_RSP,         /// Respond to Pairing request
    R_BLE_GTL_GAPC_PAIRING_SUCCEED,     /// Pairing Finished information
    R_BLE_GTL_GAPC_PAIRING_FAILED,      /// Pairing Failed information
    R_BLE_GTL_GAPC_TK_EXCH,             /// Used to retrieve pairing Temporary Key
    R_BLE_GTL_GAPC_IRK_EXCH,            /// Used for Identity Resolving Key exchange
    R_BLE_GTL_GAPC_CSRK_EXCH,           /// Used for Connection Signature Resolving Key exchange
    R_BLE_GTL_GAPC_LTK_EXCH,            /// Used for Long Term Key exchange
    R_BLE_GTL_GAPC_REPEATED_ATTEMPT     /// Bond Pairing request issue, Repeated attempt
}r_ble_gtl_gapc_bond_t;


/* Authentication mask */
typedef enum r_ble_gap_auth
{    
    R_BLE_GTL_GAP_AUTH_NONE     = 0,                /// No Flag set
    R_BLE_GTL_GAP_AUTH_BOND     = (1 << 0),         /// Bond authentication
    R_BLE_GTL_GAP_AUTH_MITM     = (1 << 2),         /// Man In the middle protection
    R_BLE_GTL_GAP_AUTH_SEC      = (1 << 3),         /// Secure Connections
    R_BLE_GTL_GAP_AUTH_KEY      = (1 << 4)          /// Keypress Notifications
} r_ble_gap_auth_t;


/* Security Defines */ 
typedef enum gap_sec_req
{
    GAP_NO_SEC = 0x00,              /// No security (no authentication and encryption)
    GAP_SEC1_NOAUTH_PAIR_ENC,       /// Unauthenticated pairing with encryption
    GAP_SEC1_AUTH_PAIR_ENC,         /// Authenticated pairing with encryption
    GAP_SEC2_NOAUTH_DATA_SGN,       /// Unauthenticated pairing with data signing
    GAP_SEC2_AUTH_DATA_SGN,         /// Authentication pairing with data signing
    GAP_SEC1_SEC_PAIR_ENC,          /// Authenticated LE Secure Connections pairing with encryption
    GAP_SEC_UNDEFINED               /// Unrecognized security
}gap_sec_req_t;

#endif /* R_BLE_GTL_TYPEDEF_H_ */