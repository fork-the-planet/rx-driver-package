/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 ***********************************************************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <rm_ble_abs.h>
#include "r_ble_gtl.h"
#include "qe_ble_profile.h"
#include "r_ble_gtl_security.h"
#if BSP_CFG_RTOS_USED == 1
#include "FreeRTOS.h"
#include "semphr.h"
#include "event_groups.h"
#include "timers.h"

#elif BSP_CFG_RTOS_USED == 5
#include "tx_api.h"
#endif
#include "r_ble_gtl_image.h"
#include "r_ble_da1453x_config.h"
/* Variable to expose the device role */
#if (BLE_CFG_DEVICE_ROLE == R_BLE_GTL_CENTRAL_ROLE) // CENTRAL_ROLE
    uint8_t glob_dev_role = R_BLE_GTL_CENTRAL_ROLE;
#endif
#if (BLE_CFG_DEVICE_ROLE == R_BLE_GTL_PERIPHERAL_ROLE)
    uint8_t glob_dev_role = R_BLE_GTL_PERIPHERAL_ROLE;
#endif
#if (BLE_CFG_DEVICE_ROLE == R_BLE_GTL_ROLE_ALL)
    uint8_t glob_dev_role = R_BLE_GTL_ROLE_ALL;
#endif
#if (BLE_DA1453x_SLEEP_FLOW_CONTROL)
volatile uint8_t active_sleep_mode;
#endif

/***********************************************************************************************************************
 * Defines
 **********************************************************************************************************************/

#ifndef BLE_CFG_DEVICE_ROLE
#define BLE_CFG_DEVICE_ROLE                (0x0A)
#endif

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
 #define BLE_EVENT_PATTERN                      0x0A0A
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
 #define R_BLE_GTL_BYTE_POOL_LEN                0x800
#endif

#define R_BLE_GTL_RESET_PULSE_MS                200
#define R_BLE_GTL_ADV_DATA_LEN                  0x1F
#define R_BLE_GTL_MSG_DFLT_SCAN_TIMEOUT_MS      10000
#define R_BLE_GTL_SLEEP_WAKEUP_TOGGLE_MS        5

/* Internal event bit definitions*/
#define R_BLE_GTL_ADV_TIMER_EXPIRED_EVENT       0x00000001UL

/* Maximum length of device name in bytes (as defined by Bluetooth Core v4.2 / GAP) */
#define R_BLE_GTL_GAP_DEV_NAME_LEN_MAX          0xF8

#define R_BLE_GTL_MSG_LEN_MAX                   528
#define R_BLE_GTL_MSG_HDR_LEN                   8
#define R_BLE_GTL_MSG_INITIATOR                 0x05

#define R_BLE_GTL_MSG_TX_TIMEOUT_MS             5000
#define R_BLE_GTL_MSG_TX_BLOCK_TIMEOUT_MS       5000
#define R_BLE_GTL_MSG_RSP_TIMEOUT_MS            5000
#define R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS        5000

#define R_BLE_GTL_CB_EVT_QUEUE_LEN              32
#define R_BLE_GTL_MSG_QUEUE_LEN                 8

/* Application callback event types */
#define R_BLE_GTL_CB_EVT_TYPE_MASK              0xF000U
#define R_BLE_GTL_CB_EVT_TYPE_GAP               0x1000U
#define R_BLE_GTL_CB_EVT_TYPE_GATTS             0x3000U
#define R_BLE_GTL_CB_EVT_TYPE_GATTC             0x4000U
#define R_BLE_GTL_CB_EVT_TYPE_L2CAP             0x5000U
#define R_BLE_GTL_CB_EVT_TYPE_VS                0x8000U

/* GTL Task ID's */
#define R_BLE_GTL_TASK_ID_APP                   0x0004
#define R_BLE_GTL_TASK_ID_GATTM                 0x000B
#define R_BLE_GTL_TASK_ID_GATTC                 0x000C
#define R_BLE_GTL_TASK_ID_GAPM                  0x000D
#define R_BLE_GTL_TASK_ID_GAPC                  0x000E
#define R_BLE_GTL_TASK_ID_GTL                   0x0010
#define R_BLE_GTL_TASK_ID_AUX                   0x00A0

/* GTL GATTM Command ID's */
#define R_BLE_GTL_GATTM_ADD_SVC_REQ             0x0B00
#define R_BLE_GTL_GATTM_ADD_SVC_RSP             0x0B01
#define R_BLE_GTL_GATTM_ATT_GET_VALUE_REQ       0x0B0A
#define R_BLE_GTL_GATTM_ATT_GET_VALUE_RSP       0x0B0B
#define R_BLE_GTL_GATTM_ATT_SET_VALUE_REQ       0x0B0C
#define R_BLE_GTL_GATTM_ATT_SET_VALUE_RSP       0x0B0D

/* GTL GATTC Command ID's */
#define R_BLE_GTL_GATTC_CMP_EVT                 0x0C00
#define R_BLE_GTL_GATTC_EXC_MTU_CMD             0x0C01
#define R_BLE_GTL_GATTC_MTU_CHANGED_IND         0x0C02
#define R_BLE_GTL_GATTC_DISC_CMD                0x0C03
#define R_BLE_GTL_GATTC_DISC_SVC_IND            0x0C04
#define R_BLE_GTL_GATTC_DISC_SVC_INCL_IND       0x0C05
#define R_BLE_GTL_GATTC_DISC_CHAR_IND           0x0C06
#define R_BLE_GTL_GATTC_DISC_CHAR_DESC_IND      0x0C07
#define R_BLE_GTL_GATTC_READ_CMD                0x0C08
#define R_BLE_GTL_GATTC_READ_IND                0x0C09
#define R_BLE_GTL_GATTC_SEND_EVT_CMD            0x0C10
#define R_BLE_GTL_GATTC_WRITE_CMD               0x0C0A
#define R_BLE_GTL_GATTC_WRITE_EXECUTE_CMD       0x0C0B
#define R_BLE_GTL_GATTC_EVENT_IND               0x0C0C
#define R_BLE_GTL_GATTC_EVENT_REQ_IND           0x0C0D
#define R_BLE_GTL_GATTC_EVENT_CFM               0x0C0E
#define R_BLE_GTL_GATTC_SEND_SVC_CHANGED_CMD    0x0C11
#define R_BLE_GTL_GATTC_SVC_CHANGED_CFG_IND     0x0C12
#define R_BLE_GTL_GATTC_READ_REQ_IND            0x0C13
#define R_BLE_GTL_GATTC_READ_CFM                0x0C14
#define R_BLE_GTL_GATTC_WRITE_REQ_IND           0x0C15
#define R_BLE_GTL_GATTC_WRITE_CFM               0x0C16
#define R_BLE_GTL_GATTC_ATT_INFO_REQ_IND        0x0C17
#define R_BLE_GTL_GATTC_ATT_INFO_CFM            0x0C18

/* GTL GAPM Command ID's */
#define R_BLE_GTL_GAPM_CMP_EVT                  0x0D00
#define R_BLE_GTL_GAPM_DEVICE_READY_IND         0x0D01
#define R_BLE_GTL_GAPM_RESET_CMD                0x0D02
#define R_BLE_GTL_GAPM_CANCEL_CMD               0x0D03
#define R_BLE_GTL_GAPM_SET_DEV_CONFIG_CMD       0x0D04
#define R_BLE_GTL_GAPM_GET_DEV_INFO_CMD         0x0D06
#define R_BLE_GTL_GAPM_DEV_VERSION_IND          0x0D07
#define R_BLE_GTL_GAPM_DEV_BDADDR_IND           0x0D08
#define R_BLE_GTL_GAPM_WHITE_LIST_MGT_CMD       0x0D0B
#define R_BLE_GTL_GAPM_GEN_RAND_ADDR_CMD        0x0D16
#define R_BLE_GTL_GAPM_GEN_RAND_NB_CMD          0x0D19
#define R_BLE_GTL_GAPM_GEN_RAND_NB_IND          0x0D1A
#define R_BLE_GTL_GAPM_UNKNOWN_TASK_IND         0x0D1D
#define R_BLE_GTL_GAPM_START_ADVERTISE_CMD      0x0D0D
#define R_BLE_GTL_GAPM_START_SCAN_CMD           0x0D0F
#define R_BLE_GTL_GAPM_ADV_REPORT_IND           0x0D10
#define R_BLE_GTL_GAPM_START_CONNECTION_CMD     0x0D11
#define R_BLE_GTL_GAPM_RESOLV_ADDR_CMD          0x0D14
#define R_BLE_GTL_GAPM_ADDR_SOLVED_IND          0x0D15

/* GTL GAPC Command ID's */
#define R_BLE_GTL_GAPC_CMP_EVT                  0x0E00
#define R_BLE_GTL_GAPC_CONNECTION_REQ_IND       0x0E01
#define R_BLE_GTL_GAPC_CONNECTION_CFM           0x0E02
#define R_BLE_GTL_GAPC_DISCONNECT_IND           0x0E03
#define R_BLE_GTL_GAPC_DISCONNECT_CMD           0x0E04
#define R_BLE_GTL_GAPC_GET_INFO_CMD             0x0E05
#define R_BLE_GTL_GAPC_PEER_VERSION_IND         0x0E07
#define R_BLE_GTL_GAPC_PEER_FEATURES_IND        0x0E08
#define R_BLE_GTL_GAPC_CON_RSSI_IND             0x0E09
#define R_BLE_GTL_GAPC_GET_DEV_INFO_REQ_IND     0x0E0A
#define R_BLE_GTL_GAPC_GET_DEV_INFO_CFM         0x0E0B
#define R_BLE_GTL_GAPC_SET_DEV_INFO_REQ_IND     0x0E0C
#define R_BLE_GTL_GAPC_SET_DEV_INFO_CFM         0x0E0D
#define R_BLE_GTL_GAPC_PARAM_UPDATE_CMD         0x0E0E
#define R_BLE_GTL_GAPC_PARAM_UPDATE_REQ_IND     0x0E0F
#define R_BLE_GTL_GAPC_PARAM_UPDATE_CFM         0x0E10
#define R_BLE_GTL_GAPC_PARAM_UPDATED_IND        0x0E11

#define R_BLE_GTL_GAPC_BOND_CMD                 0x0E12
#define R_BLE_GTL_GAPC_BOND_REQ_IND             0x0E13
#define R_BLE_GTL_GAPC_BOND_CFM                 0x0E14
#define R_BLE_GTL_GAPC_BOND_IND                 0x0E15

#define R_BLE_GTL_GAPC_ENCRYPT_CMD              0x0E16
#define R_BLE_GTL_GAPC_ENCRYPT_REQ_IND          0x0E17
#define R_BLE_GTL_GAPC_ENCRYPT_CFM              0x0E18
#define R_BLE_GTL_GAPC_ENCRYPT_IND              0x0E19

#define R_BLE_GTL_GAPC_SECURITY_CMD             0x0E1A
#define R_BLE_GTL_GAPC_SECURITY_IND             0x0E1B

#define R_BLE_GTL_GAPC_CON_CHANNEL_MAP_IND      0x0E1D
#define R_BLE_GTL_GAPC_LECB_CONNECT_CMD         0x0E20
#define R_BLE_GTL_GAPC_LECB_ADD_CMD             0x0E24
#define R_BLE_GTL_GAPC_LECB_SEND_CMD            0x0E25
#define R_BLE_GTL_GAPC_LECB_DISCONNECT_CMD      0x0E26
#define R_BLE_GTL_GAPC_SET_LE_PKT_SIZE_CMD      0x0E2B
#define R_BLE_GTL_GAPC_LE_PKT_SIZE_IND          0x0E2C

/* GTL Auxiliary Command ID's */
#define R_BLE_GTL_GAPC_APP_RAND_REQ             0xA001
#define R_BLE_GTL_APP_GEN_RAND_RSP              0xA002
#define R_BLE_GTL_GET_FW_VERSION_REQ            0xA003
#define R_BLE_GTL_GET_FW_VERSION_RSP            0xA004
#define R_BLE_GTL_AUX_SET_TX_POWER_CMD          0xA005
#define R_BLE_GTL_AUX_SET_TX_POWER_CMP_EVT      0xA006
#define R_BLE_GTL_AUX_GET_TX_POWER_CMD          0xA007
#define R_BLE_GTL_AUX_GET_TX_POWER_RSP          0xA008
#define R_BLE_GTL_AUX_SET_SLEEP_MODE_CMD        0xA009
#define R_BLE_GTL_AUX_GET_SLEEP_MODE_CMD        0xA00A
#define R_BLE_GTL_AUX_SET_SLEEP_MODE_CFM        0xA00B
#define R_BLE_GTL_AUX_SET_BD_ADDRESS_CMD        0xA00C
#define R_BLE_GTL_AUX_SET_BD_ADDRESS_CFM        0xA00D


#define R_BLE_GTL_ADV_FLAG_FIELD_LEN            3
#define R_BLE_GTL_ADV_DATA_LEN_MAX              31
#define R_BLE_GTL_ADV_DATA_TYPE_FLAGS           0x01
#define R_BLE_GTL_SCAN_RSP_DATA_LEN_MAX         31
#define R_BLE_GTL_KEY_LEN                       0x10
#define R_BLE_GTL_GET_RAND_SIZE_MAX             8
#define R_BLE_GTL_DATA_LEN_TX_OCTETS_MAX        251
#define R_BLE_GTL_DATA_LEN_TX_TIME_MAX          2120
#define R_BLE_GTL_GAP_NON_DISCOVERABLE          0x00
#define R_BLE_GTL_GAP_GEN_DISCOVERABLE          0x01
#define R_BLE_GTL_GAP_LIM_DISCOVERABLE          0x02
#define R_BLE_GTL_GAP_BROADCASTER_MODE          0x03


/* Service permissions defined in QE profile */
#define R_BLE_GTL_QE_SVC_PRM_MSK                0xE0

#define R_BLE_GTL_QE_SVC_NO_SEC                 0x00
#define R_BLE_GTL_QE_SVC_UNAUTH_ENC             0x20
#define R_BLE_GTL_QE_SVC_AUTH_ENC               0x60
#define R_BLE_GTL_QE_SVC_SC_AUTH_ENC            0xA0

/* Attribute permissions defined in QE profile */
#define R_BLE_GTL_QE_ATT_PERM_READ              0x01
#define R_BLE_GTL_QE_ATT_PERM_WRITE             0x02

/* Attribute properties defined in QE profile */
#define R_BLE_GTL_QE_ATT_PROP_READ              0x02
#define R_BLE_GTL_QE_ATT_PROP_WRITE             0x08
#define R_BLE_GTL_QE_ATT_PROP_WRITE_NO_RESPONSE 0x04
#define R_BLE_GTL_QE_ATT_PROP_NOTIFY            0x10
#define R_BLE_GTL_QE_ATT_PROP_INDICATE          0x20

/* Attribute permissions defined in GTL message(s) */
#define R_BLE_GTL_ATT_PERM_READ_ENABLE          0x00000001UL
#define R_BLE_GTL_ATT_PERM_WRITE_ENABLE         0x00000008UL
#define R_BLE_GTL_ATT_PERM_INDICATE_ENABLE      0x00000040UL
#define R_BLE_GTL_ATT_PERM_NOIFY_ENABLE         0x00000200UL
#define R_BLE_GTL_ATT_PERM_WRITE_CMD_ACCEPTED   0x00008000UL
#define R_BLE_GTL_ATT_PERM_WRITE_REQ_ACCEPTED   0x00020000UL
#define R_BLE_GTL_ATT_PERM_UUID_LEN_128         0x00080000UL

#define R_BLE_GTL_SVC_GAP_UUID                  0x1800
#define R_BLE_GTL_SVC_GATT_UUID                 0x1801
#define R_BLE_GTL_ATT_PRIMARY_SVC_DECL          0x2800
#define R_BLE_GTL_ATT_SECONDARY_SVC_DECL        0x2801
#define R_BLE_GTL_CHAR_DECLARATION              0x2803
#define R_BLE_GTL_CHAR_USER_DESC                0x2901
#define R_BLE_GTL_CLIENT_CHAR_CONF              0x2902
#define R_BLE_GTL_SERVER_CHAR_CONF              0x2903
#define R_BLE_GTL_CHAR_DEVICE_NAME              0x2A00
#define R_BLE_GTL_CHAR_APPEARANCE               0x2A01
#define R_BLE_GTL_CHAR_PERIPH_PRIVACY_FLAG      0x2A02
#define R_BLE_GTL_CHAR_RECONNECTION_ADDRESS     0x2A03
#define R_BLE_GTL_CHAR_PERIPH_PREF_CONN_PARAMS  0x2A04
#define R_BLE_GTL_CHAR_SERVICE_CHANGED          0x2A05

#define R_BLE_GTL_CHAR_MIN_UUID					0x2A00
#define R_BLE_GTL_CHAR_MAX_UUID					0x2C19

/* Service permissions defined in GTL messages(s), can be or'd together */
#define R_BLE_GTL_SVC_PERM_ENABLE               (0x01 << 2)
#define R_BLE_GTL_SVC_PERM_UNAUTH               (0x02 << 2)
#define R_BLE_GTL_SVC_PERM_AUTH                 (0x03 << 2)
 
#define R_BLE_GTL_SVC_PERM_UUID_LEN_128         0x40
#define R_BLE_GTL_SVC_PERM_PRIMARY              0x80

#define R_BLE_GTL_RI_FLAG                       0x8000

/* The first two bits of a non-public (random) address must be binary ones */
#define R_BLE_GTL_PUBLIC_BD_ADDR_MASK           0xC0

#define R_BLE_GTL_MS_PER_SECOND                 1000UL
#define R_BLE_GTL_ADV_TIMER_TICKS_PER_SECOND    100UL

/* "RBLE" in ASCII. Used to determine if the control block is open. */
#define R_BLE_GTL_OPEN                          0x52424C45U
#define R_BLE_GTL_CLOSED                        0x00000000U

/* Mutex give/take defines */
#define R_BLE_GTL_MUTEX_TX                      (1UL << 0)
#define R_BLE_GTL_MUTEX_RX                      (1UL << 1)
#define R_BLE_GTL_MUTEX_TEI                     (1UL << 2)

/* UART boot protocol message types */
#define R_BLE_GTL_BOOT_STX                      0x02
#define R_BLE_GTL_BOOT_SOH                      0x01
#define R_BLE_GTL_BOOT_ACK                      0x06
#define R_BLE_GTL_BOOT_NACK                     0x15

/* Defines for host DB */
#define DB_NON_RI_INDEX                        0xFFFF
#define DB_INVALID_PARAM                       0xFFFE
#define DB_VALID_RI_INDEX                      0x0000


/* Directive macro invalid */
#if (2 == BLE_CFG_HOST_BOOT_MODE) && (DA14531_DEVICE == BLE_CFG_DA1453X_DEVICE)
    #error "Error! Invalid value for BLE_CFG_HOST_BOOT_MODE & BLE_CFG_DA1453X_DEVICE. \
                                                                    Please verify this macro in r_ble_da1453x_config.h"
#endif

/* Defines for scan parameters */
#define R_BLE_GTL_GAPM_STATIC_ADDR  0x00
#define R_BLE_GTL_GAP_GEN_DISCOVERY 0x00
#define R_BLE_GTL_GAP_LIM_DISCOVERY 0x01
#define R_BLE_GTL_GAP_OBSERVER_MODE 0x02

#define R_BLE_GTL_SCAN_ALLOW_ADV_ALL 0x00
#define R_BLE_SCAN_ALLOW_ADV_WLST    0x01

/* Defines for connection parameters */
#define R_BLE_GTL_MIN_CONNECTION_CE_LENGTH     0x0000
#define R_BLE_GTL_MAX_CONNECTION_CE_LENGTH     0xFFFF

/* Defines for whitelisting */
#define R_BLE_GTL_GAPM_GET_WLIST_SIZE       0x08
#define R_BLE_GTL_GAPM_ADD_DEV_IN_WLIST     0x09
#define R_BLE_GTL_GAPM_RMV_DEV_FRM_WLIST    0x0A
#define R_BLE_GTL_GAPM_CLEAR_WLIST          0x0B

/***********************************************************************************************************************
 * Enumerations
 **********************************************************************************************************************/
typedef enum e_r_ble_gtl_rx_msg_parser_state
{
    R_BLE_GTL_RX_MSG_PARSER_STATE_IDLE = 0,
    R_BLE_GTL_RX_MSG_PARSER_STATE_RX_HEADER,
    R_BLE_GTL_RX_MSG_PARSER_STATE_RX_PARAM
} r_ble_gtl_rx_msg_parser_state_t;

typedef enum e_r_ble_gtl_gapm_operation
{
    R_BLE_GTL_GAPM_OP_NONE = 0x00,
    R_BLE_GTL_GAPM_OP_RESET,
    R_BLE_GTL_GAPM_OP_CANCEL,
    R_BLE_GTL_GAPM_OP_SET_DEV_CONFIG,
    R_BLE_GTL_GAPM_OP_SET_CHANNEL_MAP,
    R_BLE_GTL_GAPM_OP_GET_DEV_VERSION,
    R_BLE_GTL_GAPM_OP_GET_DEV_BDADDR,
    R_BLE_GTL_GAPM_OP_GET_DEV_ADV_TX_POWER,
    R_BLE_GTL_GAPM_OP_GET_WLIST_SIZE,
    R_BLE_GTL_GAPM_OP_ADD_DEV_IN_WLIST,
    R_BLE_GTL_GAPM_OP_RMV_DEV_FRM_WLIST,
    R_BLE_GTL_GAPM_OP_CLEAR_WLIST,
    R_BLE_GTL_GAPM_OP_ADV_NON_CONN,
    R_BLE_GTL_GAPM_OP_ADV_UNDIRECT,
    R_BLE_GTL_GAPM_OP_ADV_DIRECT,
    R_BLE_GTL_GAPM_OP_ADV_DIRECT_LDC,
    R_BLE_GTL_GAPM_OP_UPDATE_ADVERTISE_DATA,
    R_BLE_GTL_GAPM_OP_SCAN_ACTIVE,
    R_BLE_GTL_GAPM_OP_SCAN_PASSIVE,
    R_BLE_GTL_GAPM_OP_CONNECTION_DIRECT,
    R_BLE_GTL_GAPM_OP_CONNECTION_AUTO,
    R_BLE_GTL_GAPM_OP_CONNECTION_SELECTIVE,
    R_BLE_GTL_GAPM_OP_CONNECTION_NAME_REQUEST,
    R_BLE_GTL_GAPM_OP_RESOLV_ADDR,
    R_BLE_GTL_GAPM_OP_GEN_RAND_ADDR,
    R_BLE_GTL_GAPM_OP_USE_ENC_BLOCK,
    R_BLE_GTL_GAPM_OP_GEN_RAND_NB,
    R_BLE_GTL_GAPM_OP_PROFILE_TASK_ADD,
    R_BLE_GTL_GAPM_OP_DBG_GET_MEM_INFO,
    R_BLE_GTL_GAPM_OP_PLF_RESET,
    R_BLE_GTL_GAPM_OP_SET_SUGGESTED_DFLT_LE_DATA_LEN,
    R_BLE_GTL_GAPM_OP_GET_SUGGESTED_DFLT_LE_DATA_LEN,
    R_BLE_GTL_GAPM_OP_GET_MAX_LE_DATA_LEN,
    R_BLE_GTL_GAPM_OP_GET_RAL_SIZE,
    R_BLE_GTL_GAPM_OP_GET_RAL_LOC_ADDR,
    R_BLE_GTL_GAPM_OP_GET_RAL_PEER_ADDR,
    R_BLE_GTL_GAPM_OP_ADD_DEV_IN_RAL,
    R_BLE_GTL_GAPM_OP_RMV_DEV_FRM_RAL,
    R_BLE_GTL_GAPM_OP_CLEAR_RAL,
    R_BLE_GTL_GAPM_OP_USE_P256_BLOCK,
    R_BLE_GTL_GAPM_OP_NETWORK_MODE_RAL,
    R_BLE_GTL_GAPM_OP_DEVICE_MODE_RAL,
    R_BLE_GTL_GAPM_OP_KEY_RENEW,
    R_BLE_GTL_GAPM_OP_GEN_P256_KEY = R_BLE_GTL_GAPM_OP_KEY_RENEW,
    R_BLE_GTL_GAPM_OP_LAST
} r_ble_gtl_gapm_operation_t;

typedef enum e_r_ble_gtl_gapc_operation
{
    R_BLE_GTL_GAPC_OP_NONE = 0x00,
    R_BLE_GTL_GAPC_OP_DISCONNECT,
    R_BLE_GTL_GAPC_OP_GET_PEER_NAME,
    R_BLE_GTL_GAPC_OP_GET_PEER_VERSION,
    R_BLE_GTL_GAPC_OP_GET_PEER_FEATURES,
    R_BLE_GTL_GAPC_OP_GET_PEER_APPEARANCE,
    R_BLE_GTL_GAPC_OP_GET_PEER_SLV_PREF_PARAMS,
    R_BLE_GTL_GAPC_OP_GET_CON_RSSI,
    R_BLE_GTL_GAPC_OP_GET_CON_CHANNEL_MAP,
    R_BLE_GTL_GAPC_OP_UPDATE_PARAMS,
    R_BLE_GTL_GAPC_OP_BOND,
    R_BLE_GTL_GAPC_OP_ENCRYPT,
    R_BLE_GTL_GAPC_OP_SECURITY_REQ,
    R_BLE_GTL_GAPC_OP_LE_CB_CREATE,
    R_BLE_GTL_GAPC_OP_LE_CB_DESTROY,
    R_BLE_GTL_GAPC_OP_LE_CB_CONNECTION,
    R_BLE_GTL_GAPC_OP_LE_CB_DISCONNECTION,
    R_BLE_GTL_GAPC_OP_LE_CB_ADDITION,
    R_BLE_GTL_GAPC_OP_GET_LE_PING_TO,
    R_BLE_GTL_GAPC_OP_SET_LE_PING_TO,
    R_BLE_GTL_GAPC_OP_SET_LE_PKT_SIZE,
    R_BLE_GTL_GAPC_OP_GET_PEER_CENTRAL_RPA,
    R_BLE_GTL_GAPC_OP_GET_PEER_RPA_ONLY,
    R_BLE_GTL_GAPC_OP_LE_CB_SEND,
} r_ble_gtl_gapc_operation_t;

typedef enum e_r_ble_gtl_gattc_operation
{
    R_BLE_GTL_GATTC_OP_NONE = 0x00,
    R_BLE_GTL_GATTC_OP_MTU_EXCH,
    R_BLE_GTL_GATTC_OP_DISC_ALL_SVC,
    R_BLE_GTL_GATTC_OP_DISC_BY_UUID_SVC,
    R_BLE_GTL_GATTC_OP_DISC_INCLUDED_SVC,
    R_BLE_GTL_GATTC_OP_DISC_ALL_CHAR,
    R_BLE_GTL_GATTC_OP_DISC_BY_UUID_CHAR,
    R_BLE_GTL_GATTC_OP_DISC_DESC_CHAR,
    R_BLE_GTL_GATTC_OP_READ,
    R_BLE_GTL_GATTC_OP_READ_LONG,
    R_BLE_GTL_GATTC_OP_READ_BY_UUID,
    R_BLE_GTL_GATTC_OP_READ_MULTIPLE,
    R_BLE_GTL_GATTC_OP_WRITE,
    R_BLE_GTL_GATTC_OP_WRITE_NO_RESPONSE,
    R_BLE_GTL_GATTC_OP_WRITE_SIGNED,
    R_BLE_GTL_GATTC_OP_EXEC_WRITE,
    R_BLE_GTL_GATTC_OP_REGISTER,
    R_BLE_GTL_GATTC_OP_UNREGISTER,
    R_BLE_GTL_GATTC_OP_NOTIFY,
    R_BLE_GTL_GATTC_OP_INDICATE,
    R_BLE_GTL_GATTC_OP_SVC_CHANGED
} r_ble_gtl_gattc_operation_t;

typedef enum e_r_ble_gtl_aux_operation
{
    R_BLE_GTL_AUX_OP_NONE      = 0x00,
    R_BLE_GTL_AUX_SET_TX_POWER = 0x06,
} r_ble_gtl_aux_operation_t;

typedef enum e_r_ble_gtl_host_error_code
{
  R_BLE_GTL_GAP_ERR_NO_ERROR              = 0x00,
  R_BLE_GTL_ATT_ERR_INVALID_HANDLE,
  R_BLE_GTL_ATT_ERR_READ_NOT_PERMITTED,
  R_BLE_GTL_ATT_ERR_REQUEST_NOT_SUPPORTED = 0x06,
  R_BLE_GTL_GAP_ERR_CANCELED              = 0x44,
  R_BLE_GTL_GAP_ERR_TIMEOUT               = 0x45,
  R_BLE_GTL_GAP_ERR_REJECTED              = 0x48,
  R_BLE_GTL_GAP_ERR_ANY                   = 0x7F
} r_ble_gtl_host_error_code_t;

typedef enum e_r_ble_gtl_gapc_device_info
{
    R_BLE_GTL_GAPC_DEV_NAME = 0x00,
    R_BLE_GTL_GAPC_DEV_APPEARANCE,
    R_BLE_GTL_GAPC_DEV_SLV_PREF_PARAMS,
    R_BLE_GTL_GAPC_DEV_CENTRAL_RPA,
    R_BLE_GTL_GAPC_DEV_RPA_ONLY,
} r_ble_gtl_gapc_device_info_t;

typedef enum e_r_ble_gtl_device_state
{
    R_BLE_GTL_DEV_STATE_IDLE = 0x00,
    R_BLE_GTL_DEV_STATE_CONNECTED,
    R_BLE_GTL_DEV_STATE_CONNECTING,
	R_BLE_GTL_DEV_STATE_ADVERTISING = 0x10
} r_ble_gtl_device_state_t;

/* Common GTL message parameters */
#pragma pack
typedef struct r_ble_gtl_bd_addr
{
    uint8_t                         addr[BLE_BD_ADDR_LEN];
} r_ble_gtl_bd_addr_t;

typedef struct r_ble_gtl_gap_bdaddr
{
    r_ble_gtl_bd_addr_t             addr;
    uint8_t                         type;
} r_ble_gtl_gap_bdaddr_t;

typedef struct r_ble_gtl_gap_device_name
{
    uint16_t                        length;
    uint8_t                         value[0];
} r_ble_gtl_gap_device_name_t;

typedef struct  r_ble_gtl_gap_slv_pref_params
{
    uint16_t                        con_intv_min;
    uint16_t                        con_intv_max;
    uint16_t                        slave_latency;
    uint16_t                        conn_timeout;
} r_ble_gtl_gap_slv_pref_params_t;

typedef struct r_ble_gtl_gap_sec_key
{
    uint8_t                         key[R_BLE_GTL_KEY_LEN];
} r_ble_gtl_gap_sec_key_t;

typedef union r_ble_gtl_uuid_value
{
    uint16_t                        uuid16;
    uint8_t                         uuid128[BLE_GATT_128_BIT_UUID_SIZE];
} r_ble_gtl_uuid_value_t;

/* Common GTL GAPM message parameters */
typedef struct  r_ble_gtl_adv_report
{
    uint8_t        evt_type;
    uint8_t        adv_addr_type;
    r_ble_gtl_bd_addr_t  adv_addr;
    uint8_t        data_len;
    uint8_t        data[R_BLE_GTL_ADV_DATA_LEN];
    int8_t         rssi;
} r_ble_gtl_adv_report_t;

typedef struct  r_ble_gtl_gapm_air_operation
{
    uint8_t  code;
    uint8_t  addr_src;
    uint16_t state;
} r_ble_gtl_gapm_air_operation_t;

typedef struct r_ble_gtl_gapm_adv_host
{
    uint8_t                         mode;
    uint8_t                         adv_filt_policy;
    uint8_t                         adv_data_len;
    uint8_t                         adv_data[R_BLE_GTL_ADV_DATA_LEN_MAX];
    uint8_t                         scan_rsp_data_len;
    uint8_t                         scan_rsp_data[R_BLE_GTL_SCAN_RSP_DATA_LEN_MAX];
    r_ble_gtl_gap_bdaddr_t          peer_info;
} r_ble_gtl_gapm_adv_host_t;

typedef union r_ble_gtl_gapm_adv_info
{
    r_ble_gtl_gapm_adv_host_t       host;
    r_ble_gtl_gap_bdaddr_t          direct;
} r_ble_gtl_gapm_adv_info_t;

typedef struct r_ble_gtl_gapm_air_op
{
    uint8_t                         code;
    uint8_t                         addr_src;
    uint16_t                        state;
} r_ble_gtl_gapm_air_op_t;

/* GTL message GAPM Commands */
typedef struct  r_ble_gtl_gapm_start_scan_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    r_ble_gtl_gapm_air_operation_t  op;
    uint16_t                        interval;
    uint16_t                        window;
    uint8_t                         mode;
    uint8_t                         filt_policy;
    uint8_t                         filter_duplic;
    uint8_t                         pad1;
}r_ble_gtl_gapm_start_scan_cmd_t;

typedef struct  r_ble_gtl_gapm_start_connection_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    r_ble_gtl_gapm_air_operation_t  op;
    uint16_t             scan_interval;
    uint16_t             scan_window;
    uint16_t             con_intv_min;
    uint16_t             con_intv_max;
    uint16_t             con_latency;
    uint16_t             superv_to;
    uint16_t             ce_len_min;
    uint16_t             ce_len_max;
    uint8_t              nb_peers;
    struct r_ble_gtl_gap_bdaddr   peers[0];
}r_ble_gtl_gapm_start_connection_cmd_t;

typedef struct r_ble_gtl_gapm_reset_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         op;
} r_ble_gtl_gapm_reset_cmd_t;

typedef struct r_ble_gtl_gapm_cancel_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         op;
} r_ble_gtl_gapm_cancel_cmd_t;

typedef struct r_ble_gtl_gapm_set_dev_config_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         role;
    uint16_t                        renew_dur;
    r_ble_gtl_bd_addr_t             addr;
    r_ble_gtl_gap_sec_key_t         irk;
    uint8_t                         addr_type;
    uint8_t                         att_cfg;
    uint16_t                        gap_start_hdl;
    uint16_t                        gatt_start_hdl;
    uint16_t                        max_mtu;
    uint16_t                        max_mps;
    uint16_t                        att_cfg_;
    uint16_t                        max_txoctets;
    uint16_t                        max_txtime;
    uint8_t                         priv1_2;
    uint8_t                         pad;
} r_ble_gtl_gapm_set_dev_config_cmd_t;

typedef struct r_ble_gtl_gapm_start_advertise_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    r_ble_gtl_gapm_air_op_t         op;
    uint16_t                        intv_min;
    uint16_t                        intv_max;
    uint8_t                         channel_map;
    r_ble_gtl_gapm_adv_info_t       info;
} r_ble_gtl_gapm_start_advertise_cmd_t;

typedef struct r_ble_gtl_gapm_gen_rand_nb_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
} r_ble_gtl_gapm_gen_rand_nb_cmd_t;

typedef struct r_ble_gtl_gapm_gen_rand_addr_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         type;
} r_ble_gtl_gapm_gen_rand_addr_cmd_t;

typedef struct r_ble_gtl_gapm_get_dev_info_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         op;
} r_ble_gtl_gapm_get_dev_info_cmd_t;

/* GTL message GAPM Responses */
typedef struct r_ble_gtl_gapm_cmp_evt
{
    uint8_t                         operation;
    uint8_t                         status;
} r_ble_gtl_gapm_cmp_evt_t;

typedef struct  r_ble_gtl_gapm_adv_report_ind
{
    struct r_ble_gtl_adv_report report;
} r_ble_gtl_gapm_adv_report_ind_t;

typedef struct r_ble_gtl_gapm_dev_version_ind
{
    uint8_t                         hci_ver;
    uint8_t                         lmp_ver;
    uint8_t                         host_ver;
    uint8_t                         padding;
    uint16_t                        hci_subver;
    uint16_t                        lmp_subver;
    uint16_t                        host_subver;
    uint16_t                        manuf_name;
} r_ble_gtl_gapm_dev_version_ind_t;

typedef struct r_ble_gtl_gapm_dev_bdaddr_ind
{
    r_ble_gtl_gap_bdaddr_t          addr;
} r_ble_gtl_gapm_dev_bdaddr_ind_t;

typedef struct r_ble_gtl_gapm_unknown_task_ind
{
    uint16_t                        msg_id;
    uint16_t                        task_id;
} r_ble_gtl_gapm_unknown_task_ind_t;

typedef struct r_ble_gtl_gapm_gen_rand_nb_ind
{
    uint8_t                         rand_nb[R_BLE_GTL_GET_RAND_SIZE_MAX];
} r_ble_gtl_gapm_gen_rand_nb_ind_t;

/* Common GTL GAPC message parameters */
typedef struct  r_ble_gtl_gapc_set_bd_address_cmd
{
    r_ble_gtl_msg_hdr_t hdr;
    st_ble_dev_addr_t addr;
} r_ble_gtl_gapc_set_bd_address_cmd_t;

typedef struct  r_ble_gtl_gapc_set_bd_address_cmp
{
    st_ble_dev_addr_t addr;
    uint8_t dummy;
} r_ble_gtl_gapc_set_bd_address_cmp_t;

typedef struct  r_ble_gtl_gapc_set_sleep_mode_cmd
{
    r_ble_gtl_msg_hdr_t hdr;
    uint8_t sleep_mode;
    uint8_t ram_retention;
    uint8_t pin_selection;
} r_ble_gtl_gapc_set_sleep_mode_cmd_t;

typedef struct  ble_gtl_gapc_set_sleep_mode_cmp
{
    uint8_t sleep_mode;
    uint8_t command_status;
} r_ble_gtl_gapc_set_sleep_mode_cmp_t;


typedef union r_ble_gtl_gapc_dev_info_val
{
    r_ble_gtl_gap_device_name_t     name;
    uint16_t                        appearance;
    r_ble_gtl_gap_slv_pref_params_t slv_pref_params;
} r_ble_gtl_gapc_dev_info_val_t;

/* GTL message GAPC Commands */
typedef struct r_ble_gtl_gapc_disconnect_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         op;
    uint8_t                         reason;
} r_ble_gtl_gapc_disconnect_cmd_t;

typedef struct r_ble_gtl_gapc_param_update_cmd_t
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         op;
    uint8_t                         pkt_id;
    uint16_t                        intv_min;
    uint16_t                        intv_max;
    uint16_t                        latency;
    uint16_t                        timeout;
    uint16_t                        ce_len_min;
    uint16_t                        ce_len_max;
} r_ble_gtl_gapc_param_update_cmd_t;

typedef struct r_ble_gtl_gapc_get_info_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         op;
} r_ble_gtl_gapc_get_info_cmd_t;

typedef struct r_ble_gtl_gapc_set_le_pkt_size_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         op;
    uint8_t                         padding;
    uint16_t                        max_tx_octets;
    uint16_t                        max_tx_time;
} r_ble_gtl_gapc_set_le_pkt_size_cmd_t;

typedef struct r_ble_gtl_gapc_get_dev_info_cfm
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         req;
    uint8_t                         padding;
    r_ble_gtl_gapc_dev_info_val_t   info;
} r_ble_gtl_gapc_get_dev_info_cfm_t;

typedef struct  r_ble_gtl_gapc_set_dev_info_cfm
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         req;
    uint8_t                         status;
} r_ble_gtl_gapc_set_dev_info_cfm_t;


typedef struct r_ble_gtl_gapc_connection_cfm
{
    r_ble_gtl_msg_hdr_t             hdr;
    r_ble_gtl_gap_sec_key_t         lcsrk;
    uint32_t                        lsign_counter;
    r_ble_gtl_gap_sec_key_t         rcsrk;
    uint32_t                        rsign_counter;
    uint8_t                         auth;
    uint8_t                         svc_changed_ind_enable;
    uint16_t                        pad;
} r_ble_gtl_gapc_connection_cfm_t;

typedef struct r_ble_gtl_gapc_param_update_cfm
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         accept;
    uint8_t                         padding;
    uint16_t                        ce_len_min;
    uint16_t                        ce_len_max;
} r_ble_gtl_gapc_param_update_cfm_t;

typedef struct r_ble_gtl_gapc_lecb_connect_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         pkt_id;
    uint16_t                        le_psm;
    uint16_t                        cid;
    uint16_t                        credit;
} r_ble_gtl_gapc_lecb_connect_cmd_t;

typedef struct r_ble_gtl_gapc_lecb_add_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         pkt_id;
    uint16_t                        le_psm;
    uint16_t                        credit;
} r_ble_gtl_gapc_lecb_add_cmd_t;

typedef struct r_ble_gtl_gapc_lecb_disconnect_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         pkt_id;
    uint16_t                        le_psm;
} r_ble_gtl_gapc_lecb_disconnect_cmd_t;

typedef struct r_ble_gtl_gapc_lecb_send_data_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         lcid;
    uint16_t                        data_len;
    uint8_t                         data[0];
} r_ble_gtl_gapc_lecb_send_data_cmd_t;

/* GTL message GAPC Responses */
typedef struct r_ble_gtl_gapc_connection_req_ind
{
    uint16_t                        conhdl;
    uint16_t                        con_interval;
    uint16_t                        con_latency;
    uint16_t                        sup_to;
    uint8_t                         clk_accuracy;
    uint8_t                         peer_addr_type;
    r_ble_gtl_bd_addr_t             peer_addr;
} r_ble_gtl_gapc_connection_req_ind_t;

typedef struct r_ble_gtl_gapc_disconnect_ind
{
    uint16_t                        conhdl;
    uint8_t                         reason;
} r_ble_gtl_gapc_disconnect_ind_t;

typedef struct r_ble_gtl_gapc_peer_version_ind
{
    uint16_t                        manuf_name;
    uint16_t                        lmp_subver;
    uint8_t                         lmp_ver;
    uint8_t                         padding;
} r_ble_gtl_gapc_peer_version_ind_t;

typedef struct r_ble_gtl_gapc_peer_features_ind
{
    uint8_t                         features[BLE_GAP_REM_FEATURE_SIZE];
} r_ble_gtl_gapc_peer_features_ind_t;

typedef struct r_ble_gtl_gapc_le_pkt_size_ind
{
    uint16_t                        max_tx_octets;
    uint16_t                        max_tx_time;
    uint16_t                        max_rx_octets;
    uint16_t                        max_rx_time;
} r_ble_gtl_gapc_le_pkt_size_ind_t;

typedef struct r_ble_gtl_gapc_con_rssi_ind
{
    uint8_t                         rssi;
} r_ble_gtl_gapc_con_rssi_ind_t;

typedef struct r_ble_gtl_gapc_con_channel_map_ind
{
    uint8_t                         map[BLE_GAP_CH_MAP_SIZE];
} r_ble_gtl_gapc_con_channel_map_ind_t;

typedef struct r_ble_gtl_gapc_param_update_ind
{
    uint16_t                        intv;
    uint16_t                        latency;
    uint16_t                        timeout;
} r_ble_gtl_gapc_param_update_ind_t;

typedef struct r_ble_gtl_gapc_param_update_req_ind
{
    uint16_t                        intv_min;
    uint16_t                        intv_max;
    uint16_t                        latency;
    uint16_t                        timeout;
} r_ble_gtl_gapc_param_update_req_ind_t;

typedef struct r_ble_gtl_gapc_get_dev_info_req_ind
{
    uint8_t                         operation;
} r_ble_gtl_gapc_get_dev_info_req_ind_t;

typedef struct  r_ble_gtl_gapc_set_dev_info_req_ind
{
    uint8_t                         req;
    uint8_t                         padding;
    uint16_t                        length;
    uint8_t                         value[0];
} r_ble_gtl_gapc_set_dev_info_req_ind_t;

/* Common GTL GATTC message parameters */

/* GTL message GATTC Commands */
typedef struct r_ble_gtl_gattc_exc_mtu_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         padding;
    uint16_t                        seq_nbr;
} r_ble_gtl_gattc_exc_mtu_cmd_t;

typedef struct r_ble_gtl_gattc_write_req_cfm
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint16_t                        handle;
    uint8_t                         status;
    uint8_t                         padding;
} r_ble_gtl_gattc_write_req_cfm_t;

typedef struct r_ble_gtl_gattc_read_req_cfm
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint16_t                        handle;
    uint16_t                        length;
    uint8_t                         status;
    uint8_t                         value[0];
} r_ble_gtl_gattc_read_cfm_t;

typedef struct  r_ble_gtl_gattc_att_info_cfm
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint16_t                        handle;
    uint16_t                        length;
    uint8_t                         status;
    uint8_t                         padding;
} r_ble_gtl_gattc_att_info_cfm_t;

typedef struct r_ble_gtl_gattc_read
{
    uint16_t                        att_hdl;
    uint16_t                        offset;
    uint16_t                        length;
} r_ble_gtl_gattc_read_t;

typedef struct r_ble_gtl_gattc_read_uuid
{
    uint16_t                        start_hdl;
    uint16_t                        end_hdl;
    uint8_t                         uuid_len;
    r_ble_gtl_uuid_value_t          uuid;
} r_ble_gtl_gattc_read_uuid_t;

typedef struct r_ble_gtl_gattc_read_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         number;
    uint16_t                        seq_nbr;
    r_ble_gtl_gattc_read_t          param;
} r_ble_gtl_gattc_read_cmd_t;

typedef struct r_ble_gtl_gattc_read_uuid_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         number;
    uint16_t                        seq_nbr;
    r_ble_gtl_gattc_read_uuid_t     param;
} r_ble_gtl_gattc_read_uuid_cmd_t;

typedef struct r_ble_gtl_read_multi_att
{
    uint16_t                        att_hdl;
    uint16_t                        length;
} r_ble_gtl_read_multi_att_t;

typedef struct r_ble_gtl_gattc_read_multi_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         number;
    uint16_t                        seq_nbr;
    r_ble_gtl_read_multi_att_t      att_list[0];
} r_ble_gtl_gattc_read_multi_cmd_t;

typedef struct r_ble_gtl_whitelist_devices
{
    uint8_t                         addr[BLE_BD_ADDR_LEN];
    uint8_t                         type;
} r_ble_gtl_whitelist_devices_t;

typedef struct r_ble_gtl_gattm_white_list_mgt_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         nb;
    r_ble_gtl_whitelist_devices_t   dev_list[0];
} r_ble_gtl_gattm_white_list_mgt_cmd_t;

typedef struct r_ble_gtl_gattc_write_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         auto_exec;
    uint16_t                        seq_nbr;
    uint16_t                        handle;
    uint16_t                        offset;
    uint16_t                        length;
    uint16_t                        cursor;
    uint8_t                         value[0];
} r_ble_gtl_gattc_write_cmd_t;

typedef struct r_ble_gtl_gattc_write_exeute_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         execute;
    uint16_t                        seq_nbr;
} r_ble_gtl_gattc_write_execute_cmd_t;

typedef struct r_ble_gtl_gattc_disc_uuid16_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         uuid_len;
    uint16_t                        seq_num;
    uint16_t                        start_hdl;
    uint16_t                        end_hdl;
    uint16_t                        uuid16;
} r_ble_gtl_gattc_disc_uuid16_cmd_t;

typedef struct r_ble_gtl_gattc_disc_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         uuid_len;
    uint16_t                        seq_num;
    uint16_t                        start_hdl;
    uint16_t                        end_hdl;
    r_ble_gtl_uuid_value_t          uuid;
} r_ble_gtl_gattc_disc_cmd_t;

typedef struct r_ble_gtl_gattc_send_evt_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         padding;
    uint16_t                        seq_num;
    uint16_t                        handle;
    uint16_t                        length;
    uint8_t                         value[0];
} r_ble_gtl_gattc_send_evt_cmd_t;

typedef struct r_ble_gtl_gattc_send_svc_changed_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
    uint8_t                         padding;
    uint16_t                        seq_num;
    uint16_t                        svc_shdl;
    uint16_t                        svc_ehdl;
} r_ble_gtl_gattc_send_svc_changed_cmd_t;

/* GTL message GATTC Event Indication (Notifications & Indications) */
typedef struct r_ble_gtl_gattc_event_ind
{
    uint8_t                         type;
    uint8_t                         padding;
    uint16_t                        length;
    uint16_t                        handle;
    uint8_t                         value[0];
} r_ble_gtl_gattc_event_ind_t;

/* GTL message GATTC Event Indication Confirmation (Indications Confirmation) */
typedef struct  r_ble_gtl_gattc_event_cfm
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint16_t                        handle;
} r_ble_gtl_gattc_event_cfm_t;

/* GTL message GATTC Service Changed Event Indication*/
typedef struct  r_ble_gtl_gattc_svc_changed_cfg_ind
{
    uint16_t                        ind_cfg;
} r_ble_gtl_gattc_svc_changed_cfg_ind_t;


/* GTL message GATTC Responses */
typedef struct r_ble_gtl_gattc_mtu_changed_ind
{
    uint16_t                        mtu;
    uint16_t                        sqn;
} r_ble_gtl_gattc_mtu_changed_ind_t;

typedef struct r_ble_gtl_gattc_read_req_ind
{
    uint16_t                        handle;
} r_ble_gtl_gattc_read_req_ind_t;

typedef struct r_ble_gtl_gattc_write_req_ind
{
    uint16_t                        handle;
    uint16_t                        offset;
    uint16_t                        length;
    uint8_t                         value[0];
} r_ble_gtl_gattc_write_req_ind_t;

typedef struct r_ble_gtl_gattc_disc_char_desc_ind
{
    uint16_t                        handle;
    uint8_t                         uuid_len;
    r_ble_gtl_uuid_value_t          uuid;
    uint8_t                         padding;
} r_ble_gtl_gattc_disc_char_desc_ind_t;

typedef struct r_ble_gtl_gattc_disc_svc_ind
{
    uint16_t                        start_hdl;
    uint16_t                        end_hdl;
    uint8_t                         uuid_len;
    r_ble_gtl_uuid_value_t          uuid;
    uint8_t                         padding;
} r_ble_gtl_gattc_disc_svc_ind_t;

typedef struct r_ble_gtl_gattc_disc_char_ind
{
    uint16_t                        att_hdl;
    uint16_t                        ptr_hdl;
    uint8_t                         properties;
    uint8_t                         uuid_len;
    r_ble_gtl_uuid_value_t          uuid;
} r_ble_gtl_gattc_disc_char_ind_t;

typedef struct r_ble_gtl_gattc_disc_svc_incl_ind
{
    uint16_t                        att_hdl;
    uint16_t                        start_hdl;
    uint16_t                        end_hdl;
    uint8_t                         uuid_len;
    r_ble_gtl_uuid_value_t          uuid;
    uint8_t			    pad;
} r_ble_gtl_gattc_disc_svc_incl_ind_t;

typedef struct r_ble_gtl_gattc_read_ind
{
    uint16_t                        handle;
    uint16_t                        offset;
    uint16_t                        length;
    uint8_t                         value[0];
} r_ble_gtl_gattc_read_ind_t;

typedef struct  r_ble_gtl_gattc_att_info_req_ind
{
    uint16_t                        handle;
} r_ble_gtl_gattc_att_info_req_t;

/* Common GTL GATTM message parameters */
typedef struct r_ble_gtl_gattm_att_desc
{
    uint8_t                         uuid[BLE_GATT_128_BIT_UUID_SIZE];
    uint32_t                        perm;
    uint16_t                        max_len;
    uint16_t                        padding;
} r_ble_gtl_gattm_att_desc_t;

/* GTL message GATTM Commands */
typedef struct r_ble_gtl_gattm_add_svc_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint16_t                        start_hdl;
    uint16_t                        task_id;
    uint8_t                         perm;
    uint8_t                         nb_att;
    uint8_t                         uuid[BLE_GATT_128_BIT_UUID_SIZE];
    uint16_t                        padding;
    uint8_t                         atts[0];
} r_ble_gtl_gattm_add_svc_cmd_t;

typedef struct r_ble_gtl_gattm_att_set_value_req
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint16_t                        handle;
    uint16_t                        length;
    uint8_t                         value[0];
} r_ble_gtl_gattm_att_set_value_req_t;

typedef struct r_ble_gtl_gattm_att_get_value_req
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint16_t                        handle;
} r_ble_gtl_gattm_att_get_value_req_t;

/* GTL message GATTM Responses */
typedef struct r_ble_gtl_gattm_att_set_value_rsp
{
    uint16_t                        handle;
    uint8_t                         status;
    uint8_t                         padding;
} r_ble_gtl_gattm_att_set_value_rsp_t;

typedef struct r_ble_gtl_gattm_att_get_value_rsp
{
    uint16_t                        handle;
    uint16_t                        length;
    uint8_t                         status;
    uint8_t                         value[0];
} r_ble_gtl_gattm_att_get_value_rsp_t;

typedef struct r_ble_gtl_gattm_add_svc_rsp
{
    uint16_t                        start_hdl;
    uint8_t                         status;
    uint8_t                         padding;
} r_ble_gtl_gattm_add_svc_rsp_t;

/* GTL message Auxiliary Commands */
typedef struct r_ble_gtl_aux_get_pwr_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    /* No parameters with this command */
} r_ble_gtl_aux_get_pwr_cmd_t;

typedef struct r_ble_gtl_aux_set_pwr_cmd
{
    r_ble_gtl_msg_hdr_t             hdr;
    uint8_t                         operation;
} r_ble_gtl_aux_set_pwr_cmd_t;

/* GTL message Auxiliary Responses */
typedef struct r_ble_gtl_aux_set_pwr_rsp
{
    uint8_t                         operation;
    uint8_t                         status;
} r_ble_gtl_aux_set_pwr_rsp_t;
#pragma unpack

/* Device data */
typedef struct r_ble_gtl_adv_data
{
    uint8_t                         data[R_BLE_GTL_ADV_DATA_LEN_MAX];
    uint8_t                         length;
} r_ble_gtl_adv_data_t;

typedef struct r_ble_gtl_scan_rsp_data
{
    uint8_t                         length;
    uint8_t                         data[R_BLE_GTL_SCAN_RSP_DATA_LEN_MAX];
} r_ble_gtl_scan_rsp_data_t;

typedef struct r_ble_gtl_adv_param
{
    st_ble_gap_adv_param_t          param;
    bool                            valid;
} r_ble_gtl_adv_param_t;

typedef struct r_ble_gtl_dev_params
{
    uint8_t                         dev_name[R_BLE_GTL_GAP_DEV_NAME_LEN_MAX];
    uint16_t                        dev_name_length;
    uint8_t                         adv_mode;
    uint16_t                        appearance;
    uint16_t                        mtu_size;
    int8_t                          att_hndl_offset;
    uint16_t                        start_hdl;
    uint16_t                        qe_att_hdl;
    r_ble_gtl_adv_param_t           adv_param;
    r_ble_gtl_adv_data_t            adv_data;
    r_ble_gtl_scan_rsp_data_t       scan_rsp_data;
    st_ble_dev_addr_t               dev_addr;
    r_ble_gtl_device_state_t        state;
    int16_t                         nof_active_connections;
    uint16_t                        l2cap_conn_hdl;
    r_ble_gtl_gap_slv_pref_params_t ppcp;
} r_ble_gtl_dev_params_t;

typedef union r_ble_gtl_cb_evt_data
{
    st_ble_evt_data_t               gap;
    st_ble_vs_evt_data_t            vs;
    st_ble_gatts_evt_data_t         gatts;
    st_ble_gattc_evt_data_t         gattc;
    st_ble_l2cap_cf_evt_data_t      l2cap;
} r_ble_gtl_cb_evt_data_t;

typedef struct r_ble_gtl_cb_evt
{
    uint16_t                        type;
    ble_status_t                    result;
    r_ble_gtl_cb_evt_data_t         data;
} r_ble_gtl_cb_evt_t;

typedef struct r_ble_gtl_uuid
{
    uint8_t                         length;
    r_ble_gtl_uuid_value_t          value;
} r_ble_gtl_uuid_t;

typedef struct r_ble_gtl_disc_events
{
    uint16_t                        evt_16;
    uint16_t                        evt_128;
    uint16_t                        evt_comp;
} r_ble_gtl_disc_events_t;

#if BSP_CFG_RTOS_USED == 0 /* Baremetal */
typedef struct r_ble_gtl_fifo
{
    uint8_t                      ** p_buffer;
    uint32_t                        size;
    uint32_t                        items;
    uint32_t                        head;
    uint32_t                        tail;
} r_ble_gtl_fifo_t;
#endif

#if (BLE_CFG_HOST_BOOT_MODE > 0)
#pragma pack
typedef struct r_ble_gtl_boot_header
{
    uint8_t                         soh;
    uint16_t                        length;
} r_ble_gtl_boot_header_t;
#pragma unpack
#endif

 

/***********************************************************************************************************************
 * Extern variables
 **********************************************************************************************************************/
extern ble_abs_instance_ctrl_t * gp_instance_ctrl;
#if (BLE_CFG_HOST_BOOT_MODE > 0)
extern st_sci_conf_t * s_port_cfg;
#endif

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
 extern EventGroupHandle_t       g_ble_event_group_handle;
#endif

/***********************************************************************************************************************
 * Static Private Variables
 **********************************************************************************************************************/
static uint8_t                        * p_rx_buf = NULL;
static uint16_t                         rx_msg_ix = 0;
static r_ble_gtl_rx_msg_parser_state_t  rx_gtl_msg_parser_state;
static r_ble_gtl_transport_api_t        g_transport_api;
static r_ble_gtl_dev_params_t           g_dev_params;
static ble_gap_app_cb_t                 g_gap_cb   = NULL;
static ble_vs_app_cb_t                  g_vs_cb    = NULL;
static ble_gatts_app_cb_t               g_gatts_cb = NULL;
static ble_gattc_app_cb_t               g_gattc_cb = NULL;
static ble_l2cap_cf_app_cb_t            g_l2cap_cb = NULL;

static uint16_t                         slv_pref_con_par_index   = 0;
static uint16_t                         service_changed_index    = 0;
static uint16_t                         device_name_index        = 0;
static uint16_t                         device_appearance_index  = 0;
static uint32_t                         g_gtl_open               = 0;

/* Buffers must be aligned to 32-bit boundary as messages contain 16 and 32-bit data types which can be 
   dereferenced via pointers */
#pragma pack
static uint8_t                          g_gtl_msg_buf_pool[R_BLE_GTL_MSG_QUEUE_LEN][R_BLE_GTL_MSG_LEN_MAX];
#pragma unpack
#if (BLE_CFG_HOST_BOOT_MODE > 0)
/* Set this flag when booting DA1453x from host. It informs UART receive interrupt handler that incoming bytes are not
   GTL messages and should instead be handled by boot loader function. */
static volatile bool                    g_booting = false;
/* When booting DA1453x from host MCU received bytes are stored in this variable and are processed by 
   the boot loader function */
static volatile uint8_t                 g_rx_boot_byte = 0;
#endif

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
static QueueHandle_t                    g_cb_evt_queue;
static QueueHandle_t                    g_pend_gtl_msg_queue;
static QueueHandle_t                    g_used_gtl_msg_queue;
static QueueHandle_t                    g_free_gtl_msg_queue;
static SemaphoreHandle_t                g_uart_tei_sem;
static SemaphoreHandle_t                g_tx_sem;
static SemaphoreHandle_t                g_rx_sem;
static TimerHandle_t                    g_adv_timer;
static EventGroupHandle_t               g_events;
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
static uint8_t                          g_cb_evt_queue_buff[sizeof(ULONG)*(TX_1_ULONG)*(R_BLE_GTL_CB_EVT_QUEUE_LEN)];
static TX_QUEUE                         g_cb_evt_queue;
static uint8_t                          g_pend_gtl_msg_queue_buff[sizeof(ULONG)*(TX_1_ULONG)*(R_BLE_GTL_MSG_QUEUE_LEN)];
static uint8_t                          g_used_gtl_msg_queue_buff[sizeof(ULONG)*(TX_1_ULONG)*(R_BLE_GTL_MSG_QUEUE_LEN)];
static uint8_t                          g_free_gtl_msg_queue_buff[sizeof(ULONG)*(TX_1_ULONG)*(R_BLE_GTL_MSG_QUEUE_LEN)];
static TX_QUEUE                         g_pend_gtl_msg_queue;
static TX_QUEUE                         g_used_gtl_msg_queue;
static TX_QUEUE                         g_free_gtl_msg_queue;
static TX_BYTE_POOL                     g_byte_pool;
#pragma pack
static uint8_t                          g_byte_pool_buff[R_BLE_GTL_BYTE_POOL_LEN];
#pragma unpack
static TX_SEMAPHORE                     g_uart_tei_sem;
static TX_SEMAPHORE                     g_tx_sem;
static TX_SEMAPHORE                     g_rx_sem;
static TX_TIMER                         g_adv_timer;
static TX_EVENT_FLAGS_GROUP             g_events;
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
static r_ble_gtl_cb_evt_t             * g_cb_evt_queue_buff[R_BLE_GTL_CB_EVT_QUEUE_LEN];
static r_ble_gtl_fifo_t                 g_cb_evt_queue;
static uint8_t                        * g_free_gtl_msg_buf[R_BLE_GTL_MSG_QUEUE_LEN];
static volatile r_ble_gtl_fifo_t        g_free_gtl_msg_queue;
static uint8_t                        * g_used_gtl_msg_buf[R_BLE_GTL_MSG_QUEUE_LEN];
static volatile r_ble_gtl_fifo_t        g_used_gtl_msg_queue;
static uint8_t                        * g_pend_gtl_msg_buf[R_BLE_GTL_MSG_QUEUE_LEN];
static r_ble_gtl_fifo_t                 g_pend_gtl_msg_queue;
static volatile bool                    g_uart_tei_sem;
#endif

/* Mapping of power level returned by DA1453x to actual power in dBm */
#if  (DA14531_DEVICE == BLE_CFG_DA1453X_DEVICE)
static const int8_t tx_pwr_lut[] =
{
   -127, /* 0  - Invalid */
    -19, /* 1  - RF_TX_PWR_LVL_MINUS_19d5 */
    -13, /* 2  - RF_TX_PWR_LVL_MINUS_13d5 */
    -10, /* 3  - RF_TX_PWR_LVL_MINUS_10d0 */
    -7,  /* 4  - RF_TX_PWR_LVL_MINUS_7d0 */
    -5,  /* 5  - RF_TX_PWR_LVL_MINUS_5d0 */
    -3,  /* 6  - RF_TX_PWR_LVL_MINUS_3d5 */
    -2,  /* 7  - RF_TX_PWR_LVL_MINUS_2d0 */
    -1,  /* 8  - RF_TX_PWR_LVL_MINUS_1d0 */
     0,  /* 9  - RF_TX_PWR_LVL_0d0 */
     1,  /* 10 - RF_TX_PWR_LVL_PLUS_1d0 */
     2,  /* 11 - RF_TX_PWR_LVL_PLUS_1d5 */
     3   /* 12 - RF_TX_PWR_LVL_PLUS_2d5 */
};
#elif  (DA14535_DEVICE == BLE_CFG_DA1453X_DEVICE)
static const int8_t tx_pwr_lut[] =
{
   -127, /* 0  - Invalid */
    -18, /* 1  - RF_TX_PWR_LVL_MINUS_18d0 */
    -12, /* 2  - RF_TX_PWR_LVL_MINUS_12d0 */
    -9,  /* 3  - RF_TX_PWR_LVL_MINUS_9d0 */
    -6,  /* 4  - RF_TX_PWR_LVL_MINUS_6d0 */
    -4,  /* 5  - RF_TX_PWR_LVL_MINUS_4d0 */
    -2,  /* 6  - RF_TX_PWR_LVL_MINUS_2d5 */
    -1,  /* 7  - RF_TX_PWR_LVL_MINUS_1d0 */
     0,  /* 8  - RF_TX_PWR_LVL_0d0 */
     1,  /* 9  - RF_TX_PWR_LVL_PLUS_1d5 */
     2,  /* 10 - RF_TX_PWR_LVL_PLUS_2d5 */
     3,  /* 11 - RF_TX_PWR_LVL_PLUS_3d0 */
     4   /* 12 - RF_TX_PWR_LVL_PLUS_4d0 */
};
#endif
/***********************************************************************************************************************
 * Local function prototypes
 **********************************************************************************************************************/
static bool                 r_ble_gtl_msg_queue_init(void);
static ble_status_t         r_ble_gtl_msg_queue_add(uint8_t ** p_rx_msg);
static bool                 r_ble_gtl_msg_queue_empty(void);
static void                 r_ble_gtl_msg_pend_queue_add(uint8_t ** p_rx_msg);
static bool                 r_ble_gtl_msg_pend_queue_empty(void);
static ble_status_t         r_ble_gtl_msg_receive(uint8_t ** p_msg, uint32_t timeout_ms);
static ble_status_t         r_ble_gtl_msg_pend_receive(uint8_t ** p_msg, uint32_t timeout_ms);
static ble_status_t         r_ble_gtl_msg_transmit(uint8_t * p_msg);
static r_ble_gtl_cb_evt_t * r_ble_gtl_msg_process(uint8_t * p_gtl_msg);
static uint8_t            * r_ble_gtl_msg_allocate(uint16_t id, uint16_t dest_id, uint16_t src_id, uint16_t len);
static uint8_t            * r_ble_gtl_msg_buffer_allocate_from_isr(uint16_t len);
static void                 r_ble_gtl_msg_buffer_free(uint8_t * p_msg);
static void                 r_ble_gtl_msg_buffer_free_from_isr(uint8_t * p_msg);
static uint8_t            * r_ble_gtl_msg_parse_rx_char(uint8_t rxd_byte);
static ble_status_t         r_ble_gtl_msg_wait_for_response(uint16_t rsp_msg_id, uint8_t * p_rsp_param, 
															uint32_t rsp_param_len, uint32_t timeout_ms);
static ble_status_t         r_ble_gtl_msg_wait_for_cmd_complete(uint16_t cmp_evt, uint8_t operation,
															uint8_t cmd_status, uint32_t timeout_ms);
static ble_status_t r_ble_check_completion_message(uint8_t * p_msg, uint8_t operation, uint16_t value_hdl);
static ble_status_t         r_ble_gtl_gapm_send_start_adv_cmd(void);
static ble_status_t         r_ble_gtl_gapm_send_reset_cmd(void);
static ble_status_t         r_ble_gtl_gapm_send_cancel_cmd(uint8_t operation);
static ble_status_t         r_ble_gtl_gapm_send_dev_config_cmd(void);
static ble_status_t         r_ble_gtl_gapm_send_get_dev_info_cmd(uint8_t operation);
static ble_status_t         r_ble_gtl_gapm_send_gen_rand_nb_cmd(void);
static ble_status_t         r_ble_gtl_gapm_get_get_dev_version(r_ble_gtl_gapm_dev_version_ind_t * p_version);
static ble_status_t         r_ble_gtl_gapm_get_bd_addr(r_ble_gtl_gapm_dev_bdaddr_ind_t * p_bd_addr);
static ble_status_t         r_ble_gtl_gapm_gen_rand_nb(r_ble_gtl_gapm_gen_rand_nb_ind_t * p_rand_nb);
static ble_status_t         r_ble_gtl_gapm_reset(void);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_handler(uint8_t * p_gtl_msg);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_connection_req_handler(uint16_t conn_hdl,
																 r_ble_gtl_gapc_connection_req_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_disconnect_ind_handler(uint16_t conn_hdl, 
																 r_ble_gtl_gapc_disconnect_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_le_pkt_size_ind_handler(uint16_t conn_hdl, 
																	r_ble_gtl_gapc_le_pkt_size_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_param_update_ind_handler(uint16_t conn_hdl, 
																	r_ble_gtl_gapc_param_update_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_get_dev_info_req_ind_handler(uint16_t conn_hdl, 
																	r_ble_gtl_gapc_get_dev_info_req_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_set_dev_info_req_ind_handler(uint16_t conn_hdl, 
																	r_ble_gtl_gapc_set_dev_info_req_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_parm_update_req_ind_handler(uint16_t conn_hdl, 
																	r_ble_gtl_gapc_param_update_req_ind_t * p_param);
static ble_status_t         r_ble_gtl_gapc_send_param_update_cmd(uint16_t conn_hdl, 
																st_ble_gap_conn_param_t * p_conn_updt_param);
static ble_status_t         r_ble_gtl_gapc_send_le_pkt_size_cmd(uint16_t conn_hdl, 
																uint16_t tx_octets, uint16_t tx_time);
static ble_status_t         r_ble_gtl_gapc_send_get_info_cmd(uint16_t conn_hdl, uint8_t operation);
static ble_status_t         r_ble_gtl_gapc_send_param_update_cfm(uint16_t conn_hdl, uint8_t accept);
static ble_status_t         r_ble_gtl_gapc_set_le_pkt_size(uint16_t conn_hdl, uint16_t tx_octets, uint16_t tx_time);
static ble_status_t         r_ble_gtl_gapc_get_peer_version(uint16_t conn_hdl, 
															r_ble_gtl_gapc_peer_version_ind_t * p_version);
static ble_status_t         r_ble_gtl_gapc_get_peer_features(uint16_t conn_hdl, 
															r_ble_gtl_gapc_peer_features_ind_t * p_features);
static ble_status_t         r_ble_gtl_gapc_get_con_rssi(uint16_t conn_hdl, 
														r_ble_gtl_gapc_con_rssi_ind_t * p_param);
static ble_status_t         r_ble_gtl_gapc_get_channel_map(uint16_t conn_hdl, 
														r_ble_gtl_gapc_con_channel_map_ind_t * p_param);
static ble_status_t         r_ble_gtl_gapc_disconnect(uint16_t conn_hdl, uint8_t reason);
static ble_status_t         r_ble_gtl_gapc_param_update(uint16_t conn_hdl, st_ble_gap_conn_param_t * p_conn_update_param,
                                                        r_ble_gtl_gapc_param_update_ind_t * p_param_update_ind);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_handler(uint8_t * p_gtl_msg);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_write_req_ind_handler(uint16_t conn_hdl, 
														r_ble_gtl_gattc_write_req_ind_t * p_param, bool local_db);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_read_req_ind_handler(uint16_t conn_hdl, r_ble_gtl_gattc_read_req_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_read_ccc_ind_handler(uint16_t conn_hdl, r_ble_gtl_gattc_read_req_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_mtu_changed_ind_handler(uint16_t conn_hdl, r_ble_gtl_gattc_mtu_changed_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_att_info_req_ind_handler(uint16_t conn_hdl, r_ble_gtl_gattc_att_info_req_t * p_param);
static ble_status_t         r_ble_gtl_gattc_send_write_cfm(uint16_t conn_hdl, uint8_t wr_status, uint16_t att_handle);
static ble_status_t         r_ble_gtl_gattc_send_disc_cmd(uint16_t conn_hdl, uint8_t operation, uint16_t seq_num, uint16_t start_hdl,
                                                          uint16_t end_hdl, r_ble_gtl_uuid_t * p_uuid);
static ble_status_t         r_ble_gtl_gattc_write(uint8_t operation, uint8_t auto_exec, uint16_t conn_hdl, uint16_t att_hdl,
                                                  uint8_t * p_value, uint16_t length, uint16_t offset);
static ble_status_t         r_ble_gtl_gattc_send_write_cmd(uint8_t operation, uint8_t auto_exec, uint16_t conn_hdl, uint16_t att_hdl,
                                                           uint8_t * p_value, uint16_t length, uint16_t offset);
static ble_status_t         r_ble_gtl_gattc_send_read_cfm(uint16_t conn_hdl, uint8_t rd_status, 
														uint16_t att_hdl, uint16_t value_len, uint8_t * p_value);
static ble_status_t         r_ble_gtl_gattc_send_write_execute_cmd(uint16_t conn_hdl, uint8_t execute);
static ble_status_t         r_ble_gtl_gattc_send_att_info_cfm(uint16_t conn_hdl, uint16_t att_hdl, 
														uint16_t value_len, uint8_t cmd_status);
static ble_status_t         r_ble_gtl_gattc_send_read_cmd(uint16_t conn_hdl, uint8_t operation, 
															uint16_t att_hdl, uint16_t offset, uint16_t length);
static ble_status_t         r_ble_gtl_gattc_send_read_by_uuid_cmd(uint16_t conn_hdl, uint16_t start_hdl, uint16_t end_hdl,
																 r_ble_gtl_uuid_t * p_uuid);
static ble_status_t         r_ble_gtl_gattc_send_read_multiple_cmd(uint16_t conn_hdl, uint8_t number,
																	uint16_t * p_hdl_list, uint16_t *p_length_list);
static ble_status_t         r_ble_gtl_gattc_send_write_execute(uint16_t conn_hdl, uint8_t execute);
static ble_status_t         r_ble_gtl_gattc_exch_mtu(uint16_t conn_hdl, uint16_t * p_mtu_rsp);
static ble_status_t         r_ble_gtl_gattc_send_exch_mtu_cmd(uint16_t conn_hdl);
static ble_status_t         r_ble_gtl_gattc_notify(uint16_t conn_hdl, uint16_t attr_hdl, uint8_t * p_value, uint16_t length);
static ble_status_t         r_ble_gtl_gattc_indicate(uint16_t conn_hdl, uint16_t attr_hdl, uint8_t * p_value, uint16_t length);
static ble_status_t         r_ble_gtl_gattc_discover(uint16_t conn_hdl, uint8_t operation, uint16_t start_hdl, uint16_t end_hdl,
                                                     r_ble_gtl_uuid_t * p_uuid, r_ble_gtl_disc_events_t * p_disc_evts);
static ble_status_t         r_ble_gtl_gattc_send_evt_cmd(uint8_t operation, uint16_t conn_hdl, uint16_t attr_hdl, 
														uint8_t * p_value, uint16_t length);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_event_ind_handler(uint16_t conn_hdl, r_ble_gtl_gattc_event_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_event_svc_changed_handler(uint16_t conn_hdl, r_ble_gtl_gattc_svc_changed_cfg_ind_t * p_param);
static ble_status_t         r_ble_gtl_gattc_handle_discovered_svc(uint16_t conn_hdl, r_ble_gtl_gattc_disc_svc_ind_t * p_disc_svc_ind,
																	r_ble_gtl_disc_events_t * p_disc_evts);
static ble_status_t         r_ble_gtl_gattc_handle_discovered_char(uint16_t conn_hdl, r_ble_gtl_gattc_disc_char_ind_t * p_disc_char_ind,
																	r_ble_gtl_disc_events_t * p_disc_evts);
static ble_status_t         r_ble_gtl_gattc_handle_discovered_char_desc(uint16_t conn_hdl, 
                                                                    r_ble_gtl_gattc_disc_char_desc_ind_t * p_disc_char_desc_ind,
																	r_ble_gtl_disc_events_t * p_disc_evts);
static ble_status_t         r_ble_gtl_gattc_handle_discovered_svc_incl(uint16_t conn_hdl, r_ble_gtl_gattc_disc_svc_incl_ind_t * p_disc_svc_incl_ind,
																		r_ble_gtl_disc_events_t * p_disc_evts);
static ble_status_t         r_ble_gtl_gattc_send_read_char_event( uint16_t conn_hdl, uint16_t type,  r_ble_gtl_gattc_read_ind_t * p_read_ind );
static ble_status_t         r_ble_gtl_gattc_send_service_changed(uint16_t conn_hdl, uint16_t start_handle, uint16_t end_handle);
static ble_status_t         r_ble_gtl_gattc_send_event_cfm(uint16_t conn_hdl, uint16_t attr_hdl);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapm_handler(uint8_t * p_gtl_msg);
static ble_status_t         r_ble_gtl_gattm_add_service(uint8_t perm, uint8_t nbr_att, r_ble_gtl_uuid_t * p_uuid,
                                                        r_ble_gtl_gattm_att_desc_t * p_att_descs, uint16_t * p_start_hdl);
static ble_status_t         r_ble_gtl_gattm_set_att_value(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value);
static ble_status_t         r_ble_gtl_gattm_set_att_value_int(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value);
static ble_status_t         r_ble_gtl_gattm_read_cfm_value(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value);
static ble_status_t         r_ble_gtl_gattm_get_att_value(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value);
static ble_status_t         r_ble_gtl_att_build_descriptor(r_ble_gtl_gattm_att_desc_t * p_att_desc, attribute_t * p_att, uint16_t nbr_atts);
static ble_status_t         r_ble_gtl_gap_get_char_value_by_uuid(uint16_t uuid, uint8_t * p_value, uint8_t len);
static ble_status_t         r_ble_gtl_gap_get_char_value_by_handle(uint16_t handle, uint8_t ** p_value, uint16_t * p_len);
static ble_status_t         r_ble_gtl_gap_stop_adv(uint8_t adv_hdl, uint8_t reason);
static ble_status_t         r_ble_gtl_aux_get_tx_power(int8_t * p_tx_pwr);
static ble_status_t         r_ble_gtl_aux_set_tx_power(uint8_t tx_pwr);
static ble_status_t         r_ble_gtl_aux_send_get_tx_power_cmd(void);
static ble_status_t         r_ble_gtl_aux_send_set_tx_power_cmd(uint8_t operation);
static ble_status_t         r_ble_gtl_aux_set_bd_address_cmd(st_ble_dev_addr_t * p_addr);
static ble_status_t         r_ble_gtl_aux_set_sleep_mode_cmd(uint8_t sleep_mode, uint8_t ram_retention, uint8_t pin_selection);
static void                 r_ble_gtl_cleanup_open(void);
static bool                 r_ble_gtl_cb_evt_queue_init(void);
static bool                 r_ble_gtl_cb_evt_queue_empty(void);
static ble_status_t         r_ble_gtl_cb_evt_queue_add(r_ble_gtl_cb_evt_t * p_evt);
static bool                 r_ble_gtl_cb_evt_queue_get(r_ble_gtl_cb_evt_t ** p_cb_evt);
static r_ble_gtl_cb_evt_t * r_ble_gtl_cb_evt_allocate(uint16_t type, ble_status_t result, uint16_t param_len);
static void                 r_ble_gtl_cb_evt_free(r_ble_gtl_cb_evt_t * p_evt);
static void                 r_ble_gtl_cb_evt_execute(r_ble_gtl_cb_evt_t * p_evt);
static void               * r_ble_gtl_malloc(uint32_t size);
static void                 r_ble_gtl_free(void * p_mem);
static void                 r_ble_gtl_delay(uint32_t ms);
static bool                 r_ble_gtl_mutex_init(void);
static bool                 r_ble_gtl_mutex_take(uint32_t mutex);
static bool                 r_ble_gtl_mutex_give(uint32_t mutex);
static void                 r_ble_gtl_hw_reset(void);
static ble_status_t         r_ble_gtl_transmit(uint8_t * p_data, uint32_t len);
static uint16_t             r_ble_gtl_is_characteristic_present(uint16_t service_uuid, uint16_t characteristic_uuid);


#if BSP_CFG_RTOS_USED == 1 || BSP_CFG_RTOS_USED == 5 /* ThreadX or FreeRTOS */
static ble_status_t         r_ble_gtl_adv_timer_start(uint16_t duration);
static ble_status_t         r_ble_gtl_adv_timer_stop(void);
static bool                 r_ble_gtl_adv_timer_expired(void);
static bool                 r_ble_gtl_event_init(void);
#endif
#if (BLE_CFG_HOST_BOOT_MODE > 0)
static ble_status_t         r_ble_gtl_transmit_image(uint8_t * p_data, uint32_t len);
static ble_status_t         r_ble_gtl_boot_load_image(void);
#endif
#if BSP_CFG_RTOS_USED == 0 /* Baremetal */
static bool                 r_ble_gtl_fifo_empty(r_ble_gtl_fifo_t * p_fifo);
static bool                 r_ble_gtl_fifo_full(r_ble_gtl_fifo_t * p_fifo);
static bool                 r_ble_gtl_fifo_put(r_ble_gtl_fifo_t * p_fifo, uint8_t ** p_data);
static bool                 r_ble_gtl_fifo_get(r_ble_gtl_fifo_t * p_fifo, uint8_t ** p_data, uint32_t timeout_ms);
static void                 r_ble_gtl_fifo_init(r_ble_gtl_fifo_t * p_fifo, uint8_t ** p_buf, uint32_t size);
#endif

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
static void                 r_ble_gtl_adv_timer_cb(TimerHandle_t xTimer);
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
static void                 r_ble_gtl_adv_timer_cb(ULONG context);
#endif
 
static uint16_t             r_ble_gtl_is_ri_index(uint16_t db_index);
static uint16_t             r_ble_gtl_is_ccc_ri_index(uint16_t db_index);
static uint16_t             r_ble_gtl_get_ri_value_with_db_index(uint16_t db_index, uint16_t ** p_value);
 
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_bond_req_ind_handler(uint16_t conn_hdl, r_ble_gtl_gapc_bond_req_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_bond_ind_handler(uint16_t conn_hdl, r_ble_gtl_gapc_bond_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_encrypt_req_ind_handler(uint16_t conn_hdl, r_ble_gtl_gapc_encrypt_req_ind_t * p_param);
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_encrypt_ind_handler(uint16_t conn_hdl, gapc_encrypt_ind_t *p_param);
static void                 r_ble_gtl_gapc_security_ind_handler(uint16_t conn_hdl, gapc_security_ind_t *p_param);

static uint8_t int_conn_addr[BLE_BD_ADDR_LEN] = {0x00,0x00,0x00,0x00,0x00,0x00}; // Inteded address for conn
extern st_ble_gap_pairing_param_t  ble_pairing_param_local;
extern st_ble_gap_key_dist_t       pair_key_dist_local;
extern st_ble_gap_key_dist_t       pair_key_dist_tmp;

/***********************************************************************************************************************
 * Public Functions Implementation
 **********************************************************************************************************************/
ble_status_t R_BLE_GTL_Open (r_ble_gtl_transport_api_t * p_api)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl->p_cfg, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_api, BLE_ERR_INVALID_ARG);
    FSP_ERROR_RETURN(R_BLE_GTL_CLOSED == g_gtl_open, BLE_ERR_ALREADY_INITIALIZED);
#endif

    int          ret;
    ble_status_t status;

    /* Initialize transport layer */
    g_transport_api = *(p_api);
    ret = g_transport_api.open(g_transport_api.p_context);
    if (0 != ret)
    {
        r_ble_gtl_cleanup_open();
    }

    FSP_ERROR_RETURN(0 == ret, BLE_ERR_UNSPECIFIED);

    /* Initialize GTL message receive buffer */
    bool rx_msgq_init = r_ble_gtl_msg_queue_init();
    if (false == rx_msgq_init)
    {
        r_ble_gtl_cleanup_open();
    }

    FSP_ERROR_RETURN(true == rx_msgq_init, BLE_ERR_MEM_ALLOC_FAILED);

    /* Initialize callback event queue */
    bool cb_evtq_init = r_ble_gtl_cb_evt_queue_init();
    if (false == cb_evtq_init)
    {
        r_ble_gtl_cleanup_open();
    }

    FSP_ERROR_RETURN(true == cb_evtq_init, BLE_ERR_MEM_ALLOC_FAILED);

    /* Initialize transmit mutex */
    bool mutex_init = r_ble_gtl_mutex_init();
    if (false == mutex_init)
    {
        r_ble_gtl_cleanup_open();
    }

    FSP_ERROR_RETURN(true == mutex_init, BLE_ERR_MEM_ALLOC_FAILED);

#if (BSP_CFG_RTOS_USED == 1) || (BSP_CFG_RTOS_USED == 5) /* ThreadX or FreeRTOS */
    /* Initialize event signalling mechanism */
    bool event_init = r_ble_gtl_event_init();
    if (false == event_init)
    {
        r_ble_gtl_cleanup_open();
    }

    FSP_ERROR_RETURN(true == event_init, BLE_ERR_MEM_ALLOC_FAILED);
#endif

    /* Reset GTL message parser state machine */
    rx_gtl_msg_parser_state = R_BLE_GTL_RX_MSG_PARSER_STATE_IDLE;

    /* Set device default parameters */
    g_dev_params.dev_addr.type = BLE_GAP_ADDR_PUBLIC;
    g_dev_params.mtu_size      = BLE_GATT_DEFAULT_MTU;
    g_dev_params.state         = R_BLE_GTL_DEV_STATE_IDLE;
    g_dev_params.nof_active_connections = 0;

#if (BLE_CFG_HOST_BOOT_MODE > 0)
    /* Load an image directly into the DA1453x device, once loaded the DA1453x will automatically start
       executing the image. NOTE: This does not re-program any flash connected to the DA1453x, it simply
       loads the image into the DA1453x internal RAM. If successful device will send the ready indication */
    status = r_ble_gtl_boot_load_image();
    FSP_ERROR_RETURN(BLE_SUCCESS == status, status);
#else
    /* Assume DA1453x has a flash memory connected that contains an image that we want to use.
       Perform hardware reset of DA1453x - this causes it to send the device ready indication */
    r_ble_gtl_hw_reset();
#endif

    /* Wait for device ready indication */
    status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPM_DEVICE_READY_IND,
                                             NULL,
                                             0,
                                             R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
    FSP_ERROR_RETURN(BLE_SUCCESS == status, status);

    g_gtl_open = R_BLE_GTL_OPEN;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GTL_Close (r_ble_gtl_transport_api_t * p_api)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    FSP_PARAMETER_NOT_USED(p_api);

    ble_status_t         status = BLE_SUCCESS;
    r_ble_gtl_cb_evt_t * p_cb_evt;

    /* Close transport layer first to prevent any news messages from being received */
    g_transport_api.close(g_transport_api.p_context);

    /* Removed any pending messages from the callback event queue */
    while (true == r_ble_gtl_cb_evt_queue_get(&p_cb_evt))
    {
        r_ble_gtl_cb_evt_free(p_cb_evt);
    }

    /* Invalidate advertising data so it is not re-used (has to be set again) */
    g_dev_params.adv_param.valid = false;

    /* Free memory allocated for queues etc. */
    r_ble_gtl_cleanup_open();

    g_dev_params.state = R_BLE_GTL_DEV_STATE_IDLE;
    g_dev_params.nof_active_connections = 0;
    gp_instance_ctrl->open = 0;
    g_gtl_open = R_BLE_GTL_CLOSED;

    return status;
}

ble_status_t R_BLE_GTL_Execute(void)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    r_ble_gtl_cb_evt_t * p_cb_evt = NULL;
    uint8_t            * p_msg    = NULL;
    ble_status_t         status   = BLE_ERR_NOT_YET_READY;
    uint8_t              max_pend_messages_process = 4;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        /* Check if any GTL messages have been received since last time we checked */
        status = r_ble_gtl_msg_receive(&p_msg, 0);
        if ((BLE_SUCCESS == status) && (NULL != p_msg))
        {
 
            p_cb_evt = r_ble_gtl_msg_process(p_msg);
            r_ble_gtl_msg_buffer_free(p_msg);
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    if (NULL != p_cb_evt)
    {
        /* Processing the message generated an event, pass that to the application via the registered callback */
        r_ble_gtl_cb_evt_execute(p_cb_evt);
        r_ble_gtl_cb_evt_free(p_cb_evt);
    }
 
    p_cb_evt = NULL;
  
    //Check for messages on pending queue (received while waiting for another message)
    status   = BLE_ERR_NOT_YET_READY;
    do
    {
        if (true == r_ble_gtl_mutex_take (R_BLE_GTL_MUTEX_RX))
        {
            status = r_ble_gtl_msg_pend_receive (&p_msg, 0);
            if ((BLE_SUCCESS == status) && (NULL != p_msg))
            {
                p_cb_evt = NULL;
                p_cb_evt = r_ble_gtl_msg_process (p_msg);
                r_ble_gtl_msg_buffer_free (p_msg);
                max_pend_messages_process--;

            }
            r_ble_gtl_mutex_give (R_BLE_GTL_MUTEX_RX);

            if (NULL != p_cb_evt)
            {
                // Processing the message generated an event, pass that to the application via the registered callback
                r_ble_gtl_cb_evt_execute (p_cb_evt);
                r_ble_gtl_cb_evt_free (p_cb_evt);
                p_cb_evt = NULL;
            }

        }
    }
    while ((BLE_SUCCESS == status) && (max_pend_messages_process > 0));

#if (BSP_CFG_RTOS_USED == 1) || (BSP_CFG_RTOS_USED == 5) /* ThreadX or FreeRTOS */
    /* Check if advertising timer has expired */
    if (true == r_ble_gtl_adv_timer_expired())
    {
        /* Reason of 0x02 means stopped via timer */
        (void)r_ble_gtl_gap_stop_adv(0, 0x02);
    }
#endif

    /* Check for any events generated as a result of an API call, rather than an incoming GTL message */
    if (true == r_ble_gtl_cb_evt_queue_get(&p_cb_evt))
    {
        r_ble_gtl_cb_evt_execute(p_cb_evt);
        r_ble_gtl_cb_evt_free(p_cb_evt);
    }

    return BLE_SUCCESS;
}

uint32_t R_BLE_GTL_IsTaskFree(void)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    uint32_t free = 1;

    if (false == r_ble_gtl_msg_queue_empty())
    {
        /* Incoming GTL messages pending */
        free = 0;
    }

    if (false == r_ble_gtl_msg_pend_queue_empty())
    {
        /* GTL messages pending (received while waiting for another message)*/
        free = 0;
    }

    if (false == r_ble_gtl_cb_evt_queue_empty())
    {
        /* Callback event(s) pending for the application */
        free = 0;
    }

    return free;
}

ble_status_t R_BLE_GTL_GAP_Init(ble_gap_app_cb_t gap_cb)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != gap_cb, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t         status;
    r_ble_gtl_cb_evt_t * p_cb_evt = NULL;
    #ifdef ENABLE_STORAGE
    st_ble_dev_addr_t    bd_address;
    uint8_t              empty_bd_address[BLE_BD_ADDR_LEN];
    #endif

    /* Callback used to pass GAP events to next higher layer */
    g_gap_cb = gap_cb;

    /* Perform a software reset */
    status = r_ble_gtl_gapm_send_reset_cmd();
    FSP_ERROR_RETURN(BLE_SUCCESS == status, status);

    /* Wait for reset complete indication */
    status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT,
                                                 R_BLE_GTL_GAPM_OP_RESET,
                                                 0,
                                                 R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
    FSP_ERROR_RETURN(BLE_SUCCESS == status, status);
    slv_pref_con_par_index = r_ble_gtl_is_characteristic_present(R_BLE_GTL_SVC_GAP_UUID, R_BLE_GTL_CHAR_PERIPH_PREF_CONN_PARAMS);
    service_changed_index = r_ble_gtl_is_characteristic_present(R_BLE_GTL_SVC_GATT_UUID, R_BLE_GTL_CHAR_SERVICE_CHANGED);

    device_name_index = r_ble_gtl_is_characteristic_present(R_BLE_GTL_SVC_GAP_UUID, R_BLE_GTL_CHAR_DEVICE_NAME);
    device_appearance_index = r_ble_gtl_is_characteristic_present(R_BLE_GTL_SVC_GAP_UUID, R_BLE_GTL_CHAR_APPEARANCE);

    /* Initialize BD Address. If the BD address is public then the command is invoked prior to configuration.
     * If the BD address is random it will included in configuration command.
     */

    #ifdef ENABLE_STORAGE
    memset(empty_bd_address, 0, BLE_BD_ADDR_LEN);

    status = R_BLE_GTL_VS_GetBdAddr_dflash(0, &bd_address);
    if((status == BLE_SUCCESS) && (memcmp(bd_address.addr, empty_bd_address, BLE_BD_ADDR_LEN) != 0))
    {
        R_BLE_VS_SetBdAddr(BLE_VS_ADDR_AREA_REG, &bd_address);
    };
    #endif

    /* Configure DA1453x device */
    status = r_ble_gtl_gapm_send_dev_config_cmd();
    FSP_ERROR_RETURN(BLE_SUCCESS == status, status);

    /* Wait for set configuration complete indication */
    status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT,
                                                 R_BLE_GTL_GAPM_OP_SET_DEV_CONFIG,
                                                 0,
                                                 R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
    FSP_ERROR_RETURN(BLE_SUCCESS == status, status);

    /* No parameters are passed with this event type */
    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_STACK_ON, status, 0);
    if (NULL != p_cb_evt)
    {
        status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_Terminate(void)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t         status;
    r_ble_gtl_cb_evt_t * p_cb_evt = NULL;

    status = r_ble_gtl_gapm_reset();
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_STACK_OFF, status, 0);
        if (NULL != p_cb_evt)
        {
            /* No parameters are passed with this event type */
            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_ConnParamUpdateCfm(uint16_t conn_hdl, uint16_t accept)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);
    FSP_PARAMETER_NOT_USED(accept);

    return BLE_ERR_UNSUPPORTED;
}

ble_status_t R_BLE_GTL_GAP_ConnParamUpdateReq(uint16_t conn_hdl, st_ble_gap_conn_param_t * p_conn_updt_param)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_conn_updt_param, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t                        status = BLE_ERR_MEM_ALLOC_FAILED;
    r_ble_gtl_cb_evt_t                * p_cb_evt;
    st_ble_gap_conn_upd_evt_t         * p_evt_param;
    r_ble_gtl_gapc_param_update_ind_t   param_update_ind;

    status = r_ble_gtl_gapc_param_update(conn_hdl, p_conn_updt_param, &param_update_ind);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_CONN_PARAM_UPD_COMP,
                                             BLE_SUCCESS,
                                             sizeof(st_ble_gap_conn_upd_evt_t));
        if (NULL != p_cb_evt)
        {
            p_evt_param               = p_cb_evt->data.gap.p_param;
            p_evt_param->conn_hdl     = conn_hdl;
            p_evt_param->conn_intv    = param_update_ind.intv;
            p_evt_param->conn_latency = param_update_ind.latency;
            p_evt_param->sup_to       = param_update_ind.timeout;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_SetDataLen(uint16_t conn_hdl, uint16_t tx_octets, uint16_t tx_time)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                status;
    r_ble_gtl_cb_evt_t        * p_cb_evt;
    st_ble_gap_conn_hdl_evt_t * p_evt_param;

    status = r_ble_gtl_gapc_set_le_pkt_size(conn_hdl, tx_octets, tx_time);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_SET_DATA_LEN_COMP,
                                             BLE_SUCCESS,
                                             sizeof(st_ble_gap_conn_hdl_evt_t));
        if (NULL != p_cb_evt)
        {
            p_evt_param = p_cb_evt->data.gap.p_param;
            p_evt_param->conn_hdl = conn_hdl;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_Disconnect(uint16_t conn_hdl, uint8_t reason)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t               status;
    r_ble_gtl_cb_evt_t       * p_cb_evt;
    st_ble_gap_disconn_evt_t * p_discon_param;

    status = r_ble_gtl_gapc_disconnect(conn_hdl, reason);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_DISCONN_IND, BLE_SUCCESS, sizeof(st_ble_gap_disconn_evt_t));

        if (NULL != p_cb_evt)
        {
            p_discon_param = p_cb_evt->data.gap.p_param;
            p_discon_param->conn_hdl = conn_hdl;
            p_discon_param->reason   = reason;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }

        g_dev_params.nof_active_connections -= 1;
        if (g_dev_params.nof_active_connections == 0)
        {
            g_dev_params.state &= (uint8_t) ~R_BLE_GTL_DEV_STATE_CONNECTED;
        }
    }

    return status;
}

static ble_status_t  r_ble_gtl_gapm_send_white_list_mgt_cmd(uint8_t op, st_ble_dev_addr_t * p_addr, uint8_t device_num)
{
    ble_status_t status = BLE_ERR_MEM_ALLOC_FAILED;
    r_ble_gtl_gattm_white_list_mgt_cmd_t * p_cmd;
    r_ble_gtl_cb_evt_t * p_cb_evt;
    st_ble_dev_addr_t * p_list = p_addr;
   
    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
         p_cmd = (r_ble_gtl_gattm_white_list_mgt_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_WHITE_LIST_MGT_CMD,
                                                                          R_BLE_GTL_TASK_ID_GAPM,
                                                                          R_BLE_GTL_TASK_ID_GTL,
                                                                          (uint16_t)(sizeof(r_ble_gtl_gattm_white_list_mgt_cmd_t) + (device_num * sizeof(r_ble_gtl_whitelist_devices_t))));
        if (NULL != p_cmd)
        {
            p_cmd->operation = op;
            p_cmd->nb = device_num;

            r_ble_gtl_whitelist_devices_t *p_dev = p_cmd->dev_list;
            for (uint8_t dev = 0; dev < device_num; dev++)
            {
                memcpy (p_dev->addr, p_list->addr, BLE_BD_ADDR_LEN);
                p_dev->type = p_list->type;
                p_list++;
                p_dev++;
            }
            status = r_ble_gtl_msg_transmit ((uint8_t*) p_cmd);

            if (status == BLE_SUCCESS)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT,
                                                             op,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);

                p_cb_evt = r_ble_gtl_cb_evt_allocate (BLE_GAP_EVENT_WHITE_LIST_CONF_COMP,
                                                      status,
                                                      sizeof(st_ble_gap_white_list_conf_evt_t));
                if (NULL != p_cb_evt)
                {
                    st_ble_gap_white_list_conf_evt_t *p_evt_param = p_cb_evt->data.gap.p_param;
                    p_evt_param->num = device_num;
                    p_evt_param->op_code = op;
                    status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
                }

            }

        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }
    return status;
}


ble_status_t R_BLE_GTL_GAP_ConfWhiteList (uint8_t op_code, st_ble_dev_addr_t * p_addr, uint8_t device_num)
{
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t status = BLE_SUCCESS;
    uint8_t op;

    if( p_addr==NULL )
    {
        if((op_code == BLE_GAP_LIST_ADD_DEV) || (op_code == BLE_GAP_LIST_REM_DEV))
        {
            status = BLE_ERR_INVALID_PTR;
            return status;
        }
    }

    if (device_num > BLE_GAP_WHITE_LIST_MAX_ENTRY)
    {
        status = BLE_ERR_LIMIT_EXCEEDED;
    }
    else
    {
        switch(op_code)
        {
            case BLE_GAP_LIST_ADD_DEV:
            {
                op = R_BLE_GTL_GAPM_ADD_DEV_IN_WLIST;
                break;
            }
            case BLE_GAP_LIST_REM_DEV:
            {
                op = R_BLE_GTL_GAPM_RMV_DEV_FRM_WLIST;
                break;
            }
            case BLE_GAP_LIST_CLR:
            {
                FSP_ERROR_RETURN(device_num == 0, BLE_ERR_INVALID_ARG);

                op = R_BLE_GTL_GAPM_CLEAR_WLIST;
                break;
            }
            default:
            {
                status = BLE_ERR_INVALID_ARG;
                break;
            }
        }
        if(status ==  BLE_SUCCESS)
        {
            status = r_ble_gtl_gapm_send_white_list_mgt_cmd(op, p_addr, device_num);
        }
    }
    return status;
}


ble_status_t R_BLE_GTL_GAP_GetVerInfo(void)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                       status;
    r_ble_gtl_cb_evt_t               * p_cb_evt;
    st_ble_gap_loc_dev_info_evt_t    * p_dev_info;
    r_ble_gtl_gapm_dev_version_ind_t   version;
    r_ble_gtl_gapm_dev_bdaddr_ind_t    bd_addr;

    status = r_ble_gtl_gapm_get_get_dev_version(&version);
    if (BLE_SUCCESS == status)
    {
        status = r_ble_gtl_gapm_get_bd_addr(&bd_addr);
        if (BLE_SUCCESS == status)
        {
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_LOC_VER_INFO, BLE_SUCCESS, 
                                                 sizeof(st_ble_gap_loc_dev_info_evt_t));

            if (NULL != p_cb_evt)
            {
                p_dev_info = p_cb_evt->data.gap.p_param;

                memcpy(p_dev_info->l_dev_addr.addr, bd_addr.addr.addr.addr, BLE_BD_ADDR_LEN);
                p_dev_info->l_dev_addr.type       = bd_addr.addr.type;
                p_dev_info->l_ver_num.subminor    = (uint8_t)((version.host_subver >> 8) & UINT8_MAX);
                p_dev_info->l_ver_num.minor       = (uint8_t)(version.host_subver & UINT8_MAX);
                p_dev_info->l_ver_num.major       = version.host_ver;
                p_dev_info->l_bt_info.hci_ver     = version.hci_ver;
                p_dev_info->l_bt_info.hci_rev     = version.hci_subver;
                p_dev_info->l_bt_info.lmp_ver     = version.lmp_ver;
                p_dev_info->l_bt_info.lmp_sub_ver = version.lmp_subver;
                p_dev_info->l_bt_info.mnf_name    = version.manuf_name;

                status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
            }
            else
            {
                status = BLE_ERR_MEM_ALLOC_FAILED;
            }
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_ReadRssi(uint16_t conn_hdl)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                    status;
    r_ble_gtl_cb_evt_t            * p_cb_evt;
    st_ble_gap_rd_rssi_evt_t      * p_evt_param;
    r_ble_gtl_gapc_con_rssi_ind_t   rssi_ind;

    status = r_ble_gtl_gapc_get_con_rssi(conn_hdl, &rssi_ind);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_RSSI_RD_COMP, BLE_SUCCESS, 
                                             sizeof(st_ble_gap_rd_rssi_evt_t));

        if (NULL != p_cb_evt)
        {
            p_evt_param = p_cb_evt->data.gap.p_param;
            p_evt_param->conn_hdl = conn_hdl;
            p_evt_param->rssi = (int8_t)rssi_ind.rssi;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_ReadChMap(uint16_t conn_hdl)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                           status;
    r_ble_gtl_cb_evt_t                   * p_cb_evt;
    st_ble_gap_rd_ch_map_evt_t           * p_evt_param;
    r_ble_gtl_gapc_con_channel_map_ind_t   chan_map_ind;

    status = r_ble_gtl_gapc_get_channel_map(conn_hdl, &chan_map_ind);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_CH_MAP_RD_COMP, BLE_SUCCESS, 
                                             sizeof(st_ble_gap_rd_ch_map_evt_t));

        if (NULL != p_cb_evt)
        {
            p_evt_param = p_cb_evt->data.gap.p_param;

            p_evt_param->conn_hdl = conn_hdl;
            memcpy(&p_evt_param->ch_map[0], &chan_map_ind.map[0], BLE_GAP_CH_MAP_SIZE);

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_SetAdvParam(st_ble_gap_adv_param_t * p_adv_param)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_adv_param, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t status = BLE_ERR_INVALID_ARG;

    /* DA1543x only supports one advertising instance */
    if (0 == p_adv_param->adv_hdl)
    {
        /* Store data for use later when R_BLE_GTL_GAP_StartAdv is called */
        memcpy(&g_dev_params.adv_param.param, p_adv_param, sizeof(st_ble_gap_adv_param_t));
        g_dev_params.adv_param.valid = true;
        status = BLE_SUCCESS;
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_SetAdvSresData(st_ble_gap_adv_data_t * p_adv_srsp_data)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_adv_srsp_data, BLE_ERR_INVALID_ARG);
#endif

    uint8_t      offset = 0;
    ble_status_t status = BLE_ERR_INVALID_ARG;

    /* DA1543x only supports one advertising instance */
    if (0 == p_adv_srsp_data->adv_hdl)
    {
        /* Store data for use later when R_BLE_GTL_GAP_StartAdv is called */
        if (BLE_GAP_ADV_DATA_MODE == p_adv_srsp_data->data_type)
        {
            if (R_BLE_GTL_ADV_DATA_LEN_MAX >= p_adv_srsp_data->data_length)
            {
                /* DA1453x automatically adds the flags field (first 3 bytes) to the advertising payload
                   so ignore it if it is present in the data we are passed */
                if (p_adv_srsp_data->p_data[1] == R_BLE_GTL_ADV_DATA_TYPE_FLAGS)
                {
                    offset = R_BLE_GTL_ADV_FLAG_FIELD_LEN;
                }
                memcpy(&g_dev_params.adv_data.data[0],
                       &p_adv_srsp_data->p_data[offset],
                       p_adv_srsp_data->data_length - offset);
                /* Extended advertising not supported so length can't exceed 31 bytes */
                g_dev_params.adv_data.length = (uint8_t)(p_adv_srsp_data->data_length - offset);
                status = BLE_SUCCESS;
            }
        }
        else if (BLE_GAP_SCAN_RSP_DATA_MODE == p_adv_srsp_data->data_type)
        {
            if (R_BLE_GTL_SCAN_RSP_DATA_LEN_MAX >= p_adv_srsp_data->data_length)
            {
                memcpy(&g_dev_params.scan_rsp_data.data[0], p_adv_srsp_data->p_data, p_adv_srsp_data->data_length);
                /* Extended advertising not supported so length can't exceed 31 bytes */
                g_dev_params.scan_rsp_data.length = (uint8_t)p_adv_srsp_data->data_length;
                status = BLE_SUCCESS;
            }
        }
        else
        {
            ; /* Do nothing, status is already set to BLE_ERR_INVALID_ARG if we get here */
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_StartAdv(uint8_t adv_hdl, uint16_t duration)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t               status   = BLE_ERR_INVALID_ARG;
    r_ble_gtl_cb_evt_t       * p_cb_evt = NULL;
    st_ble_gap_adv_set_evt_t * p_evt_param;

    /* DA1543x only supports one advertising instance */
    if (0 == adv_hdl)
    {
        if (true == g_dev_params.adv_param.valid)
        {
            status = BLE_SUCCESS;

            #if BSP_CFG_RTOS_USED == 0 /* Baremetal */
                if (0 < duration)
                {
                    /* Advertising duration not supported by baremetal, user can implement this
                       functionality in their application */
                    status = BLE_ERR_UNSUPPORTED;
                }
            #else /* FreeRTOS or ThreadX */
                if (0 < duration)
                {
                    status = r_ble_gtl_adv_timer_start(duration);
                }
            #endif

            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_gapm_send_start_adv_cmd();
                if (BLE_SUCCESS == status)
                {
                    g_dev_params.state = R_BLE_GTL_DEV_STATE_ADVERTISING;

                    /* No GTL message received in response to start advertising command */
                    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_ADV_ON, BLE_SUCCESS, 
                                                         sizeof(st_ble_gap_adv_set_evt_t));

                    if (NULL != p_cb_evt)
                    {
                        p_evt_param = p_cb_evt->data.gap.p_param;

                        p_cb_evt->data.gap.param_len = sizeof(st_ble_gap_adv_set_evt_t);
                        p_evt_param->adv_hdl = adv_hdl;

                        status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
                    }
                    else
                    {
                        status = BLE_ERR_MEM_ALLOC_FAILED;
                    }
                }
#if (BSP_CFG_RTOS_USED == 1) || (BSP_CFG_RTOS_USED == 5) /* ThreadX or FreeRTOS */
                else
                {
                    if (0 < duration)
                    {
                        r_ble_gtl_adv_timer_stop();
                    }
                }
#endif
            }
        }
        else
        {
            status = BLE_ERR_INVALID_STATE;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_StopAdv(uint8_t adv_hdl)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t status = BLE_ERR_INVALID_MODE;

    if (R_BLE_GTL_DEV_STATE_ADVERTISING & g_dev_params.state)
    {
        /* DA1543x only supports one advertising instance */
        if (0 == adv_hdl)
        {
            /* Reason of 0x01 means stopped via call to stop function */
            status = r_ble_gtl_gap_stop_adv(adv_hdl, 0x01);

            /* Advertising timer might be running... */
#if (BSP_CFG_RTOS_USED == 1) || (BSP_CFG_RTOS_USED == 5) /* ThreadX or FreeRTOS */
            r_ble_gtl_adv_timer_stop();
#endif
        }
        else
        {
            status = BLE_ERR_INVALID_ARG;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_GetRemainAdvBufSize(uint16_t * p_remain_adv_data_size, 
                                                    uint16_t * p_remain_perd_adv_data_size)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_remain_adv_data_size, BLE_ERR_INVALID_ARG);
    FSP_ERROR_RETURN(NULL != p_remain_perd_adv_data_size, BLE_ERR_INVALID_ARG);
#endif

    *p_remain_adv_data_size = R_BLE_GTL_ADV_DATA_LEN_MAX - g_dev_params.adv_data.length;

    /* Periodic advertising is not supported by the DA1453x */
    *p_remain_perd_adv_data_size = 0;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GTL_GAP_GetRemDevInfo(uint16_t conn_hdl)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                        status;
    r_ble_gtl_cb_evt_t                * p_cb_evt;
    st_ble_gap_dev_info_evt_t         * p_dev_info;
    r_ble_gtl_gapc_peer_version_ind_t   peer_version;
    r_ble_gtl_gapc_peer_features_ind_t  peer_features;

    status = r_ble_gtl_gapc_get_peer_version(conn_hdl, &peer_version);
    if (BLE_SUCCESS == status)
    {
        status = r_ble_gtl_gapc_get_peer_features(conn_hdl, &peer_features);
        if (BLE_SUCCESS == status)
        {
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_GET_REM_DEV_INFO, BLE_SUCCESS, 
                                                        sizeof(st_ble_gap_dev_info_evt_t));

            if (NULL != p_cb_evt)
            {
                p_dev_info = p_cb_evt->data.gap.p_param;

                memcpy(&p_dev_info->features[0], &peer_features.features[0], BLE_GAP_REM_FEATURE_SIZE);
                p_dev_info->company_id = peer_version.manuf_name;
                p_dev_info->subversion = peer_version.lmp_subver;
                p_dev_info->version    = peer_version.lmp_ver;
                p_dev_info->conn_hdl   = conn_hdl;
                p_dev_info->get_status = 0x06; /* Features and version are being returned */

                /* Address not being returned, it is available via connection indication callback */
                p_dev_info->addr.type = 0;
                memset(&p_dev_info->addr.addr[0], 0, BLE_BD_ADDR_LEN);

                status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
            }
            else
            {
                status = BLE_ERR_MEM_ALLOC_FAILED;
            }
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_SetPairingParams (st_ble_gap_pairing_param_t * p_pair_param)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE

    /* Check if param ptr is NULL*/
    FSP_ERROR_RETURN(NULL != p_pair_param, BLE_ERR_INVALID_PTR);

    /* IO capabilities of local device. */
    FSP_ERROR_RETURN(p_pair_param->iocap < BLE_GAP_IOCAP_KEYBOARD_DISPLAY, BLE_ERR_INVALID_DATA);

    /* MITM protection policy. */
    FSP_ERROR_RETURN((p_pair_param->mitm == BLE_GAP_SEC_MITM_STRICT) ||
                                            (p_pair_param->mitm == BLE_GAP_SEC_MITM_BEST_EFFORT), BLE_ERR_INVALID_DATA);

    /* Bonding policy. */
    FSP_ERROR_RETURN((p_pair_param->bonding == BLE_GAP_BONDING) || 
                                                 (p_pair_param->bonding == BLE_GAP_BONDING_NONE), BLE_ERR_INVALID_DATA);

    /* Maximum LTK size(in bytes). */
    FSP_ERROR_RETURN((p_pair_param->max_key_size > 7) &&
                                                (p_pair_param->max_key_size <= BLE_GAP_LTK_SIZE), BLE_ERR_INVALID_DATA);

    /* Minimum LTK size(in bytes). */
    FSP_ERROR_RETURN((p_pair_param->min_key_size > 7) &&
                                                (p_pair_param->min_key_size <= BLE_GAP_LTK_SIZE), BLE_ERR_INVALID_DATA);

    /* Determine whether to accept only Secure Connections or not. */
    FSP_ERROR_RETURN((p_pair_param->sec_conn_only == BLE_GAP_SC_STRICT) ||
                                         (p_pair_param->sec_conn_only == BLE_GAP_SC_BEST_EFFORT), BLE_ERR_INVALID_DATA);
#endif

    ble_pairing_param_local.iocap = p_pair_param->iocap;
    ble_pairing_param_local.mitm = p_pair_param->mitm;
    ble_pairing_param_local.bonding = p_pair_param->bonding;
    ble_pairing_param_local.max_key_size = p_pair_param->max_key_size;
    ble_pairing_param_local.min_key_size = p_pair_param->min_key_size;
    ble_pairing_param_local.loc_key_dist = p_pair_param->loc_key_dist;
    ble_pairing_param_local.rem_key_dist = p_pair_param->rem_key_dist;
    ble_pairing_param_local.sec_conn_only = p_pair_param->sec_conn_only;

    return BLE_SUCCESS;
}

static uint16_t r_ble_gtl_is_characteristic_present(uint16_t service_uuid, uint16_t characteristic_uuid)
{
    uint16_t ret_index = 0;
    attribute_t * p_srv;
    attribute_t * p_att;
    
    for(uint16_t index = 0; index<QE_ATTRIBUTE_HANDLE_PROFILE_END; index++)
    {
        p_srv = (attribute_t *)&qe_ble_profile[index];
        if (p_srv->value_length == 2)
        {
            uint16_t value = *(uint16_t*) p_srv->value;
            if (value == service_uuid)
            {
                for (uint16_t i = 0; i < p_srv->encapsulated_attributes - 1; i++)
                {
                    p_att = (attribute_t *)&qe_ble_profile[index + i + 1];
                    if(p_att->uuid_length == 2)
                    {
                        uint16_t uuid  = *(uint16_t*) p_att->uuid;
                        if (uuid == characteristic_uuid)
                        {
                            ret_index = (uint16_t)(index + i + 1);
                            
                            return ret_index;
                        }
                    }
                }
            }
        }
    }
    return ret_index;
}
ble_status_t R_BLE_GTL_GATTS_SetDbInst(st_ble_gatts_db_cfg_t * p_db_inst)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    FSP_PARAMETER_NOT_USED(p_db_inst);

    ble_status_t                 status       = BLE_SUCCESS;
    uint8_t                      svc_perms    = 0;
    uint16_t                     db_ix        = 0;
    uint16_t                     att_ix       = 0;
    uint16_t                     nbr_db_atts  = 0;
    uint16_t                     nbr_svc_atts = 0;
    r_ble_gtl_uuid_t             uuid;
    r_ble_gtl_gattm_att_desc_t * p_att_desc   = NULL;


    /* Store GAP service characteristic values so we can respond with them if requested 
       via R_BLE_GTL_GAPC_GET_DEV_INFO_REQ_IND command */
    r_ble_gtl_gap_get_char_value_by_uuid(R_BLE_GTL_CHAR_DEVICE_NAME, &g_dev_params.dev_name[0], R_BLE_GTL_GAP_DEV_NAME_LEN_MAX);
    g_dev_params.dev_name_length = (uint16_t)strlen((const char *)g_dev_params.dev_name);

    r_ble_gtl_gap_get_char_value_by_uuid(R_BLE_GTL_CHAR_APPEARANCE, (uint8_t *)&g_dev_params.appearance, sizeof(g_dev_params.appearance));
    r_ble_gtl_gap_get_char_value_by_uuid(R_BLE_GTL_CHAR_PERIPH_PREF_CONN_PARAMS, (uint8_t *)&g_dev_params.ppcp, sizeof(g_dev_params.ppcp));

    /* When a service is registered with the DA1453x it selects the starting handle, this may be different from
       the handle in the QE profile database. The offset between the two is captured in  when the
       first service is registered. */
    g_dev_params.att_hndl_offset = 0;

    /* First element in database contains profile description, all we need from this is the total number of 
    attributes in the database  */
    nbr_db_atts = qe_ble_profile[db_ix++].encapsulated_attributes;

    /* Add services/characteristics from the database created by the QE Tool */
    while ((db_ix < nbr_db_atts) && (BLE_SUCCESS == status))
    {
        attribute_t * p_qe_att = (attribute_t *)&qe_ble_profile[db_ix];

        /* Find next service declaration - will have pre-defined 16-bit UUID */
        if (QE_BLE_PROFILE_UUID_SIZE_ADOPTED == p_qe_att->uuid_length)
        {
            /* 16-bit UUID */
            uuid.length = BLE_GATT_16_BIT_UUID_SIZE;
            memcpy(&uuid.value, p_qe_att->uuid, BLE_GATT_16_BIT_UUID_SIZE);

            if ((R_BLE_GTL_ATT_PRIMARY_SVC_DECL   == uuid.value.uuid16) ||
                (R_BLE_GTL_ATT_SECONDARY_SVC_DECL == uuid.value.uuid16))
            {
                /* Found service declaration, set service permissions */
                svc_perms = R_BLE_GTL_SVC_PERM_ENABLE;
                if (R_BLE_GTL_ATT_PRIMARY_SVC_DECL == uuid.value.uuid16)
                {
                    svc_perms |= R_BLE_GTL_SVC_PERM_PRIMARY;
                }

                if (BLE_GATT_128_BIT_UUID_SIZE == p_qe_att->value_length)
                {
                    svc_perms |= R_BLE_GTL_SVC_PERM_UUID_LEN_128;
                }

                /* Get service UUID */
                if (BLE_GATT_16_BIT_UUID_SIZE == p_qe_att->value_length)
                {
                    memcpy(&uuid.value, p_qe_att->value, BLE_GATT_16_BIT_UUID_SIZE);
                    uuid.length = BLE_GATT_16_BIT_UUID_SIZE;
                }
                else if (BLE_GATT_128_BIT_UUID_SIZE == p_qe_att->value_length)
                {
                    memcpy(&uuid.value, p_qe_att->value, BLE_GATT_128_BIT_UUID_SIZE);
                    uuid.length = BLE_GATT_128_BIT_UUID_SIZE;
                }
                else
                {
                    /* Unsupported UUID length */
                    status = BLE_ERR_INVALID_DATA;
                    break;
                }
                
                 /* Service Security Permissions */
                uint8_t qe_perms = p_qe_att->permissions & R_BLE_GTL_QE_SVC_PRM_MSK;

                if (R_BLE_GTL_QE_SVC_UNAUTH_ENC == qe_perms)
                {
                    svc_perms |= R_BLE_GTL_SVC_PERM_UNAUTH;
                }
                else if(R_BLE_GTL_QE_SVC_AUTH_ENC == qe_perms)
                {
                    svc_perms |= R_BLE_GTL_SVC_PERM_AUTH;
                }
                else
                {
                    svc_perms |= R_BLE_GTL_SVC_PERM_ENABLE;
                }

                /* Ignore GAP and GATT services as these are automatically added by the DA1453x */
                if ((BLE_GATT_16_BIT_UUID_SIZE == uuid.length) &&
                   ((R_BLE_GTL_SVC_GAP_UUID == uuid.value.uuid16) || (R_BLE_GTL_SVC_GATT_UUID == uuid.value.uuid16)))
                {
                    db_ix += p_qe_att->encapsulated_attributes;
                    continue;
                }

                /* Number of attributes that describe this service, not including the service itself */
                nbr_svc_atts = qe_ble_profile[db_ix].encapsulated_attributes - 1;

                /* Build attribute descriptor list for this service */
                if (0 != nbr_svc_atts)
                {
                    p_att_desc = r_ble_gtl_malloc(sizeof(r_ble_gtl_gattm_att_desc_t) * nbr_svc_atts);
                    memset(p_att_desc, 0,sizeof(r_ble_gtl_gattm_att_desc_t) * nbr_svc_atts);

                    if (NULL != p_att_desc)
                    {
                        /* Build service attribute descriptor based on information in database */
                        status = r_ble_gtl_att_build_descriptor(&p_att_desc[0], &p_qe_att[1], nbr_svc_atts);

                        if (BLE_SUCCESS == status)
                        {
                            uint16_t start_handle = 0;
                            status = r_ble_gtl_gattm_add_service(svc_perms, (uint8_t)nbr_svc_atts,
                                                                 &uuid, p_att_desc, &start_handle);

                            /* Capture the starting handle of the first service registered */
                            if (0 == g_dev_params.att_hndl_offset)
                            {
                                g_dev_params.att_hndl_offset = ((int8_t)start_handle) - ((int8_t)p_qe_att->handle);
                                g_dev_params.start_hdl = start_handle;
                                g_dev_params.qe_att_hdl = p_qe_att->handle;
                            }

                            if (BLE_SUCCESS == status)
                            {
                                /* Set initial attribute values */
                                for (att_ix = 0; ((att_ix <= nbr_svc_atts) && (BLE_SUCCESS == status)); att_ix++)
                                {
                                    /* Do not attempt to write the DB if value is RI type */
                                    /* CCC's are always RI type */
                                    if ( DB_NON_RI_INDEX == r_ble_gtl_is_ri_index(att_ix+db_ix))
                                    {   
                                        uint16_t adopted_uuid  = *(uint16_t *) p_qe_att[att_ix].uuid;
                                        if (QE_BLE_PROFILE_UUID_SIZE_CUSTOM == p_qe_att[att_ix].uuid_length)
                                        {
                                          st_ble_gatt_value_t value;
                                          value.value_len = p_qe_att[att_ix].value_length;
                                          value.p_value   = p_qe_att[att_ix].value;

                                          status = r_ble_gtl_gattm_set_att_value(0, start_handle + att_ix, &value);

                                        }
                                        else if ((adopted_uuid > R_BLE_GTL_CHAR_MIN_UUID) &&
                                        		 (adopted_uuid > R_BLE_GTL_CHAR_MAX_UUID) &&
												 (p_qe_att[att_ix].uuid_length == QE_BLE_PROFILE_UUID_SIZE_ADOPTED))
                                        {
                                              st_ble_gatt_value_t value;
                                              value.value_len = p_qe_att[att_ix].value_length;
                                              value.p_value   = p_qe_att[att_ix].value;
                                              
                                              status = r_ble_gtl_gattm_set_att_value(0, start_handle + att_ix, &value);
                                        }
                                        else
                                        {
                                            /* Declaration */
                                        }
                                    }   
                                    else
                                    {
                                    	/* RI value, can also ve a declaration if marked as RI*/
                                    }
                                }
                                db_ix += p_qe_att->encapsulated_attributes;
                            }
                        }
                        r_ble_gtl_free(p_att_desc);
                    }
                }
            }
        }
    }

    return status;
}


ble_status_t R_BLE_GTL_GATT_GetMtu(uint16_t conn_hdl, uint16_t * p_mtu)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_mtu, BLE_ERR_INVALID_ARG);
#endif

    /* DA1453x only supported one connection at present */
    FSP_PARAMETER_NOT_USED(conn_hdl);

    *p_mtu = g_dev_params.mtu_size;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GTL_GATTS_RegisterCb(ble_gatts_app_cb_t cb, uint8_t priority)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != cb, BLE_ERR_INVALID_ARG);
#endif

    FSP_PARAMETER_NOT_USED(priority);

    /* Only supporting one callback at present */
    g_gatts_cb = cb;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GTL_GATTS_DeregisterCb(ble_gatts_app_cb_t cb)
{
    /* Only supporting one callback at present */
    FSP_PARAMETER_NOT_USED(cb);

    g_gatts_cb = NULL;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GTL_GATTS_Notification(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ntf_data)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_ntf_data, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t             status;
    r_ble_gtl_cb_evt_t     * p_cb_evt;
    st_ble_gatts_cfm_evt_t * p_cfm;

    status = r_ble_gtl_gattc_notify(conn_hdl,
                                    (uint16_t)(p_ntf_data->attr_hdl + g_dev_params.att_hndl_offset),
                                    p_ntf_data->value.p_value,
                                    p_ntf_data->value.value_len);

    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTS_EVENT_HDL_VAL_CNF, BLE_SUCCESS, sizeof(st_ble_gatts_cfm_evt_t));

        if (NULL != p_cb_evt)
        {
            p_cfm = p_cb_evt->data.gatts.p_param;
            p_cfm->attr_hdl = p_ntf_data->attr_hdl;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTS_Indication(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_ind_data)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_ind_data, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t             status;
    r_ble_gtl_cb_evt_t     * p_cb_evt;
    st_ble_gatts_cfm_evt_t * p_cfm;

    status = r_ble_gtl_gattc_indicate(conn_hdl,
                                     (uint16_t)(p_ind_data->attr_hdl + g_dev_params.att_hndl_offset),
                                     p_ind_data->value.p_value,
                                     p_ind_data->value.value_len);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTS_EVENT_HDL_VAL_CNF, BLE_SUCCESS, sizeof(st_ble_gatts_cfm_evt_t));

        if (NULL != p_cb_evt)
        {
            p_cfm = p_cb_evt->data.gatts.p_param;
            p_cfm->attr_hdl = p_ind_data->attr_hdl;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTS_ServiceChanged(uint16_t conn_hdl, uint16_t start_handle, uint16_t end_handle)
{
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t             status;

    status = r_ble_gtl_gattc_send_service_changed(conn_hdl, start_handle, end_handle);

    return status;
}


static bool r_ble_gtl_attribute_is_ri(uint16_t attr_hdl)
{
    bool status = false;
    if(qe_ble_profile[attr_hdl].notify_read == 1)
    {
        status = true;
    }
    
    return status;
}

static bool r_ble_gtl_ptr_attribute_is_ri(attribute_t * p_att)
{
    bool status = false;
    
    if(p_att->notify_read == 1)
    {
        return true;
    }
    
    return status;
}

ble_status_t R_BLE_GTL_GATTS_GetAttr(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_value, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t status = BLE_ERR_INVALID_ARG;

    if (0 <= ((int32_t)attr_hdl + g_dev_params.att_hndl_offset))
    {
        if(r_ble_gtl_is_ccc_ri_index(attr_hdl) == DB_VALID_RI_INDEX)
        {
            uint16_t *p_ccc_val = 0;
            r_ble_gtl_get_ri_value_with_db_index(attr_hdl, &p_ccc_val);
            if(p_ccc_val != NULL)
            {
                *( uint16_t *)p_value->p_value = *p_ccc_val;
                p_value->value_len = 2;
                status = BLE_SUCCESS;
            }
            else
            {
                status = BLE_ERR_INVALID_PTR;
            }
        }
        else if( r_ble_gtl_attribute_is_ri(attr_hdl))
        {
            memcpy(p_value->p_value, &qe_ble_profile[attr_hdl].value, qe_ble_profile[attr_hdl].value_length);
            status = BLE_SUCCESS;
        }
        else if( r_ble_gtl_attribute_is_ri(attr_hdl))
        {
            memcpy(p_value->p_value, &qe_ble_profile[attr_hdl].value, qe_ble_profile[attr_hdl].value_length);
        }
        else
        {
            status = r_ble_gtl_gattm_get_att_value(conn_hdl, 
                                    (uint16_t)((int32_t)attr_hdl + g_dev_params.att_hndl_offset), p_value);
        }
    }
    return status;
}

ble_status_t R_BLE_GTL_GATTS_ReadCfm(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_value, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t status;

    status = r_ble_gtl_gattm_read_cfm_value(conn_hdl, (uint16_t)(attr_hdl + g_dev_params.att_hndl_offset), p_value);

    return status;
}



ble_status_t R_BLE_GTL_GATTS_SetAttr(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_value, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t status = BLE_ERR_GATT_WRITE_NOT_PERMITTED;

    if(attr_hdl >= g_dev_params.qe_att_hdl)
    {
        status = r_ble_gtl_gattm_set_att_value(conn_hdl, (uint16_t)(attr_hdl + g_dev_params.att_hndl_offset), p_value);
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_RegisterCb(ble_gattc_app_cb_t cb, uint8_t priority)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != cb, BLE_ERR_INVALID_ARG);
#endif

    FSP_PARAMETER_NOT_USED(priority);

    /* Only supporting one callback at present */
    g_gattc_cb = cb;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GTL_GATTC_DeregisterCb(ble_gattc_app_cb_t cb)
{
    /* Only supporting one callback at present */
    FSP_PARAMETER_NOT_USED(cb);

    g_gattc_cb = NULL;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GTL_GATTC_ReqExMtu(uint16_t conn_hdl, uint16_t mtu)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    FSP_PARAMETER_NOT_USED(mtu);

    uint16_t                        rsp_mtu;
    ble_status_t                    status;
    r_ble_gtl_cb_evt_t            * p_cb_evt;
    st_ble_gattc_ex_mtu_rsp_evt_t * p_ex_mtu_rsp;

    status = r_ble_gtl_gattc_exch_mtu(conn_hdl, &rsp_mtu);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTC_EVENT_EX_MTU_RSP, BLE_SUCCESS, 
                                             sizeof(st_ble_gattc_ex_mtu_rsp_evt_t));
        if (NULL != p_cb_evt)
        {
            p_ex_mtu_rsp = p_cb_evt->data.gattc.p_param;
            p_ex_mtu_rsp->mtu = rsp_mtu;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_DiscAllPrimServ(uint16_t conn_hdl)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t            status;
    r_ble_gtl_disc_events_t disc_serv_events;

    disc_serv_events.evt_16   = BLE_GATTC_EVENT_PRIM_SERV_16_DISC_IND;
    disc_serv_events.evt_128  = BLE_GATTC_EVENT_PRIM_SERV_128_DISC_IND;
    disc_serv_events.evt_comp = BLE_GATTC_EVENT_ALL_PRIM_SERV_DISC_COMP;

    status = r_ble_gtl_gattc_discover(conn_hdl, R_BLE_GTL_GATTC_OP_DISC_ALL_SVC, 0x0001, 
                                                UINT16_MAX, NULL, &disc_serv_events);

    return status;
}

ble_status_t R_BLE_GTL_GATTC_DiscPrimServ(uint16_t conn_hdl, uint8_t * p_uuid, uint8_t uuid_type)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_uuid, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t            status = BLE_SUCCESS;
    r_ble_gtl_disc_events_t disc_serv_events;
    r_ble_gtl_uuid_t        uuid;

    if (BLE_GATT_16_BIT_UUID_FORMAT == uuid_type)
    {
        uuid.length = BLE_GATT_16_BIT_UUID_SIZE;
    }
    else if (BLE_GATT_128_BIT_UUID_FORMAT == uuid_type)
    {
        uuid.length = BLE_GATT_128_BIT_UUID_SIZE;
    }
    else
    {
        status = BLE_ERR_INVALID_ARG;
    }

    if (BLE_SUCCESS == status)
    {
        memcpy(&uuid.value, p_uuid, uuid.length);

        disc_serv_events.evt_16   = BLE_GATTC_EVENT_PRIM_SERV_16_DISC_IND;
        disc_serv_events.evt_128  = BLE_GATTC_EVENT_PRIM_SERV_128_DISC_IND;
        disc_serv_events.evt_comp = BLE_GATTC_EVENT_PRIM_SERV_DISC_COMP;

        status = r_ble_gtl_gattc_discover(conn_hdl, R_BLE_GTL_GATTC_OP_DISC_BY_UUID_SVC, 0x0001, 
                                                    UINT16_MAX, &uuid, &disc_serv_events);
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_DiscIncServ(uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_range, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t            status;
    r_ble_gtl_disc_events_t disc_serv_events;

    disc_serv_events.evt_16   = BLE_GATTC_EVENT_INC_SERV_16_DISC_IND;
    disc_serv_events.evt_128  = BLE_GATTC_EVENT_INC_SERV_128_DISC_IND;
    disc_serv_events.evt_comp = BLE_GATTC_EVENT_INC_SERV_DISC_COMP;

    status = r_ble_gtl_gattc_discover(conn_hdl, R_BLE_GTL_GATTC_OP_DISC_INCLUDED_SVC, p_range->start_hdl, 
                                                        p_range->end_hdl, NULL, &disc_serv_events);

    return status;
}

ble_status_t R_BLE_GTL_GATTC_DiscAllChar(uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_range, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t            status;
    r_ble_gtl_disc_events_t disc_serv_events;

    disc_serv_events.evt_16   = BLE_GATTC_EVENT_CHAR_16_DISC_IND;
    disc_serv_events.evt_128  = BLE_GATTC_EVENT_CHAR_128_DISC_IND;
    disc_serv_events.evt_comp = BLE_GATTC_EVENT_ALL_CHAR_DISC_COMP;

    status = r_ble_gtl_gattc_discover(conn_hdl, R_BLE_GTL_GATTC_OP_DISC_ALL_CHAR,
                                      p_range->start_hdl, p_range->end_hdl, NULL, &disc_serv_events);

    return status;
}

ble_status_t R_BLE_GTL_GATTC_DiscCharByUuid(uint16_t                  conn_hdl,
                                            uint8_t                 * p_uuid,
                                            uint8_t                   uuid_type,
                                            st_ble_gatt_hdl_range_t * p_range)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_uuid, BLE_ERR_INVALID_ARG);
    FSP_ERROR_RETURN(NULL != p_range, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t            status = BLE_SUCCESS;
    r_ble_gtl_disc_events_t disc_serv_events;
    r_ble_gtl_uuid_t        uuid;

    if (BLE_GATT_16_BIT_UUID_FORMAT == uuid_type)
    {
        uuid.length = BLE_GATT_16_BIT_UUID_SIZE;
    }
    else if (BLE_GATT_128_BIT_UUID_FORMAT == uuid_type)
    {
        uuid.length = BLE_GATT_128_BIT_UUID_SIZE;
    }
    else
    {
        status = BLE_ERR_INVALID_ARG;
    }

    if (BLE_SUCCESS == status)
    {
        memcpy(&uuid.value, p_uuid, uuid.length);

        disc_serv_events.evt_16   = BLE_GATTC_EVENT_CHAR_16_DISC_IND;
        disc_serv_events.evt_128  = BLE_GATTC_EVENT_CHAR_128_DISC_IND;
        disc_serv_events.evt_comp = BLE_GATTC_EVENT_CHAR_DISC_COMP;

        status = r_ble_gtl_gattc_discover(conn_hdl, R_BLE_GTL_GATTC_OP_DISC_BY_UUID_CHAR,
                                          p_range->start_hdl, p_range->end_hdl, &uuid, &disc_serv_events);
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_DiscAllCharDesc (uint16_t conn_hdl, st_ble_gatt_hdl_range_t * p_range)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_range, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t            status;
    r_ble_gtl_disc_events_t disc_serv_events;

    disc_serv_events.evt_16   = BLE_GATTC_EVENT_CHAR_DESC_16_DISC_IND;
    disc_serv_events.evt_128  = BLE_GATTC_EVENT_CHAR_DESC_128_DISC_IND;
    disc_serv_events.evt_comp = BLE_GATTC_EVENT_ALL_CHAR_DESC_DISC_COMP;

    status = r_ble_gtl_gattc_discover(conn_hdl, R_BLE_GTL_GATTC_OP_DISC_DESC_CHAR, p_range->start_hdl, 
                                                        p_range->end_hdl, NULL, &disc_serv_events);
    return status;
}

static ble_status_t r_ble_check_completion_message(uint8_t * p_msg, uint8_t operation, uint16_t value_hdl)
{
    r_ble_gtl_gapm_cmp_evt_t  *  p_param;
    ble_status_t                 status = BLE_ERR_NOT_FOUND;
    r_ble_gtl_cb_evt_t         * p_cb_evt;
    st_ble_gattc_err_rsp_evt_t * p_gattc_err;

    /* If there is a permission issue, the READ_IND will not come but the completion message */
    if (R_BLE_GTL_GATTC_CMP_EVT == ((r_ble_gtl_msg_hdr_t*) p_msg)->msg_id)
    {
        p_param = (r_ble_gtl_gapm_cmp_evt_t*) &p_msg[sizeof(r_ble_gtl_msg_hdr_t)];
        if (p_param->operation == operation)
        {
            /* CMPT EVENT. READ FAILED */
            status = p_param->status | BLE_ERR_GROUP_GATT;

        }
    }

    if (status != BLE_ERR_NOT_FOUND)
    {
        /* A read error is detected */
        p_cb_evt = r_ble_gtl_cb_evt_allocate (BLE_GATTC_EVENT_ERROR_RSP, status,
                                              sizeof(st_ble_gattc_err_rsp_evt_t));
        if (NULL != p_cb_evt)
        {
            p_gattc_err = p_cb_evt->data.gattc.p_param;
            p_gattc_err->attr_hdl = value_hdl;
            p_gattc_err->op_code = operation;
            p_gattc_err->rsp_code = status;
            r_ble_gtl_cb_evt_queue_add (p_cb_evt);

        }
        else
        {

        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_ReadChar(uint16_t conn_hdl, uint16_t value_hdl)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                 status = BLE_ERR_ALREADY_IN_PROGRESS;
    ble_status_t                 cmp_status;
    bool                         complete = false;
    uint8_t                    * p_msg;
    r_ble_gtl_gattc_read_ind_t * p_read_ind;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        /* Length of 0 means read all */
        status = r_ble_gtl_gattc_send_read_cmd(conn_hdl, R_BLE_GTL_GATTC_OP_READ, value_hdl, 0, 0);

        while ((BLE_SUCCESS == status) && (false == complete))
        {
            status = r_ble_gtl_msg_receive(&p_msg, R_BLE_GTL_MSG_RSP_TIMEOUT_MS);

            if (BLE_SUCCESS == status)
            {
                cmp_status = r_ble_check_completion_message(p_msg, R_BLE_GTL_GATTC_OP_READ, value_hdl);
                if(cmp_status != BLE_ERR_NOT_FOUND)
                {
                    /* Error detected, send a message and return */
                    r_ble_gtl_msg_buffer_free (p_msg);
                    status = cmp_status;
                    complete = true;

                }

            }

            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete (R_BLE_GTL_GATTC_CMP_EVT, R_BLE_GTL_GATTC_OP_READ,
                                                              R_BLE_GTL_GAP_ERR_NO_ERROR  ,
                                                              R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);

                if (R_BLE_GTL_GATTC_READ_IND == ((r_ble_gtl_msg_hdr_t *)p_msg)->msg_id)
                {
                    p_read_ind = (r_ble_gtl_gattc_read_ind_t *)&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];

                    status = r_ble_gtl_gattc_send_read_char_event (conn_hdl, BLE_GATTC_EVENT_CHAR_READ_RSP, p_read_ind);

                    if (status != BLE_SUCCESS)
                    {
                        r_ble_gtl_msg_buffer_free (p_msg);
                        r_ble_gtl_mutex_give (R_BLE_GTL_MUTEX_RX);
                        return status;
                    }

                    complete = true;
                    r_ble_gtl_msg_buffer_free(p_msg);

                }
                else
                {
                    /* Message received but not what we expected, queue for processing next time 
                       BLE execute is called */
                    r_ble_gtl_msg_pend_queue_add(&p_msg);
                }
            }
        }

        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_ReadCharUsingUuid(uint16_t                  conn_hdl,
                                               uint8_t                 * p_uuid,
                                               uint8_t                   uuid_type,
                                               st_ble_gatt_hdl_range_t * p_range)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_uuid, BLE_ERR_INVALID_ARG);
    FSP_ERROR_RETURN(NULL != p_range, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t                 status = BLE_ERR_ALREADY_IN_PROGRESS;
    ble_status_t                 cmp_status;
    bool                         complete = false;
    uint8_t                    * p_msg;
    r_ble_gtl_gattc_read_ind_t * p_read_ind;
    r_ble_gtl_uuid_t             uuid;

    if (BLE_GATT_16_BIT_UUID_FORMAT == uuid_type)
    {
        uuid.length = BLE_GATT_16_BIT_UUID_SIZE;
    }
    else if (BLE_GATT_128_BIT_UUID_FORMAT == uuid_type)
    {
        uuid.length = BLE_GATT_128_BIT_UUID_SIZE;
    }
    else
    {
        //uuid.length = 0;
        status = BLE_ERR_INVALID_ARG;
    }

    if (status != BLE_ERR_INVALID_ARG)
    {
        memcpy(&uuid.value, p_uuid, uuid.length);

        if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
        {
            status = r_ble_gtl_gattc_send_read_by_uuid_cmd(conn_hdl, p_range->start_hdl, p_range->end_hdl, &uuid);

            while ((BLE_SUCCESS == status) && (false == complete))
            {
                status = r_ble_gtl_msg_receive (&p_msg, R_BLE_GTL_MSG_RSP_TIMEOUT_MS);

                if (BLE_SUCCESS == status)
                {
                    cmp_status = r_ble_check_completion_message (p_msg, R_BLE_GTL_GATTC_OP_READ, p_range->start_hdl);
                    if (cmp_status != BLE_ERR_NOT_FOUND)
                    {
                        /* Error detected, send a message and return */
                        r_ble_gtl_msg_buffer_free (p_msg);
                        status = cmp_status;
                        complete = true;
                    }
                }

                if (BLE_SUCCESS == status)
                {
                    status = r_ble_gtl_msg_wait_for_cmd_complete (R_BLE_GTL_GATTC_CMP_EVT,
                                                                  R_BLE_GTL_GATTC_OP_READ_BY_UUID,
                                                                  R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                                  R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
                    if (R_BLE_GTL_GATTC_READ_IND == ((r_ble_gtl_msg_hdr_t *)p_msg)->msg_id)
                    {
                        p_read_ind = (r_ble_gtl_gattc_read_ind_t *)&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];

                        status = r_ble_gtl_gattc_send_read_char_event (conn_hdl, BLE_GATTC_EVENT_CHAR_READ_BY_UUID_RSP,
                                                                       p_read_ind);

                        if (status != BLE_SUCCESS)
                        {
                            r_ble_gtl_msg_buffer_free (p_msg);
                            r_ble_gtl_mutex_give (R_BLE_GTL_MUTEX_RX);
                            return status;
                        }

                        r_ble_gtl_msg_buffer_free(p_msg);
                        complete = true;
                    }
                    else
                    {
                        /* Message received but not what we expected, queue for processing next time 
                           BLE execute is called */
                        r_ble_gtl_msg_pend_queue_add(&p_msg);
                    }
                }
            }

            r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
        }
        else
        {
            status = BLE_ERR_ALREADY_IN_PROGRESS;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_ReadLongChar(uint16_t conn_hdl, uint16_t value_hdl, uint16_t offset, uint16_t length)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                 status = BLE_ERR_ALREADY_IN_PROGRESS;
    ble_status_t                 cmp_status;
    bool                         complete = false;
    uint8_t                    * p_msg;
    r_ble_gtl_gattc_read_ind_t * p_read_ind;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        /* Length of 0 means read all */
        status = r_ble_gtl_gattc_send_read_cmd(conn_hdl, R_BLE_GTL_GATTC_OP_READ_LONG, value_hdl, offset, length);

        while ((BLE_SUCCESS == status) && (false == complete))
        {
            status = r_ble_gtl_msg_receive(&p_msg, R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                cmp_status = r_ble_check_completion_message (p_msg, R_BLE_GTL_GATTC_OP_READ, value_hdl);
                if (cmp_status != BLE_ERR_NOT_FOUND)
                {
                    /* Error detected, send a message and return */
                    r_ble_gtl_msg_buffer_free (p_msg);
                    status = cmp_status;
                    complete = true;
                }
            }

            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GATTC_CMP_EVT,
                                                             R_BLE_GTL_GATTC_OP_READ_LONG,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
                if (R_BLE_GTL_GATTC_READ_IND == ((r_ble_gtl_msg_hdr_t *)p_msg)->msg_id)
                {
                    p_read_ind = (r_ble_gtl_gattc_read_ind_t *)&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];
                    status = r_ble_gtl_gattc_send_read_char_event(conn_hdl, BLE_GATTC_EVENT_CHAR_PART_READ_RSP, p_read_ind);

                    if (status != BLE_SUCCESS)
                    {
                        r_ble_gtl_msg_buffer_free (p_msg);
                        r_ble_gtl_mutex_give (R_BLE_GTL_MUTEX_RX);
                        return status;
                    }

                    complete = true;
                    r_ble_gtl_msg_buffer_free(p_msg);
                }
                else
                {
                    /* Message received but not what we expected, queue for processing next time 
                       BLE execute is called */
                    r_ble_gtl_msg_pend_queue_add(&p_msg);
                }
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

static ble_status_t r_ble_gtl_gattc_send_read_char_event( uint16_t conn_hdl, uint16_t type,  r_ble_gtl_gattc_read_ind_t * p_read_ind )
{
    ble_status_t status = BLE_ERR_MEM_ALLOC_FAILED;
    r_ble_gtl_cb_evt_t *p_cb_evt;
    st_ble_gattc_rd_char_evt_t * p_rd_char = NULL;

    p_cb_evt = r_ble_gtl_cb_evt_allocate (type, BLE_SUCCESS, sizeof(st_ble_gattc_rd_char_evt_t));
    p_rd_char = p_cb_evt->data.gattc.p_param;
    p_rd_char->read_data.value.p_value = NULL;
    
    if (NULL != p_cb_evt)
    {
        if (0 < p_read_ind->length)
        {
            uint8_t *pdata = r_ble_gtl_malloc (p_read_ind->length);
            if (NULL != pdata)
            {
                p_cb_evt->data.gattc.conn_hdl = conn_hdl;
                p_rd_char = p_cb_evt->data.gattc.p_param;
                p_rd_char->read_data.attr_hdl = p_read_ind->handle;
                p_rd_char->read_data.value.value_len = p_read_ind->length;
                p_rd_char->read_data.value.p_value = pdata;
                memcpy (p_rd_char->read_data.value.p_value, p_read_ind->value, p_read_ind->length);
                status = r_ble_gtl_cb_evt_queue_add (p_cb_evt);
            }
            else
            {
                r_ble_gtl_cb_evt_free (p_cb_evt);
                //r_ble_gtl_msg_buffer_free (p_msg);
                //r_ble_gtl_mutex_give (R_BLE_GTL_MUTEX_RX);
                return BLE_ERR_INVALID_PTR;
            }
        }
        else
        {
            r_ble_gtl_cb_evt_free (p_cb_evt);
            status = BLE_ERR_INVALID_DATA;
        }
    }

    return status;
}
ble_status_t R_BLE_GTL_GATTC_ReadMultiChar(uint16_t conn_hdl, st_ble_gattc_rd_multi_req_param_t * p_list)
{

#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_list, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t                 status = BLE_ERR_ALREADY_IN_PROGRESS;
    ble_status_t                 cmp_status;
    bool                         complete = false;
    uint8_t                    * p_msg;
    r_ble_gtl_gattc_read_ind_t * p_read_ind;
    uint16_t list_count = p_list->list_count;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        /* Length of 0 means read all */
        status = r_ble_gtl_gattc_send_read_multiple_cmd(conn_hdl, (uint8_t)p_list->list_count, p_list->p_hdl_list, p_list->p_len_list);

        while ((BLE_SUCCESS == status) && (false == complete))
        {
            status = r_ble_gtl_msg_receive(&p_msg, R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                cmp_status = r_ble_check_completion_message (p_msg, R_BLE_GTL_GATTC_OP_READ,  p_list->p_hdl_list[0]);
                if (cmp_status != BLE_ERR_NOT_FOUND)
                {
                    /* Error detected, send a message and return */
                    r_ble_gtl_msg_buffer_free (p_msg);
                    status = cmp_status;
                    complete = true;
                }
            }

            list_count--;

            if (BLE_SUCCESS == status)
            {
                if(list_count == 0)
                {
                    status = r_ble_gtl_msg_wait_for_cmd_complete (R_BLE_GTL_GATTC_CMP_EVT,
                                                                  R_BLE_GTL_GATTC_OP_READ_MULTIPLE,
                                                                  R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                                  R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);

                }

                if (R_BLE_GTL_GATTC_READ_IND == ((r_ble_gtl_msg_hdr_t *) p_msg)->msg_id)
                {
                    p_read_ind = (r_ble_gtl_gattc_read_ind_t *) &p_msg[sizeof(r_ble_gtl_msg_hdr_t)];
                    status = r_ble_gtl_gattc_send_read_char_event (conn_hdl, BLE_GATTC_EVENT_MULTI_CHAR_READ_RSP,
                                                                   p_read_ind);

                    if(status != BLE_SUCCESS)
                    {
                        r_ble_gtl_msg_buffer_free (p_msg);
                        r_ble_gtl_mutex_give (R_BLE_GTL_MUTEX_RX);
                        return status;
                    }

                    r_ble_gtl_msg_buffer_free (p_msg);
                    if(list_count == 0)
                    {
                        complete = true;
                    }
                }
                else
                {
                    /* Message received but not what we expected, queue for processing next time 
                       BLE execute is called */
                    r_ble_gtl_msg_pend_queue_add(&p_msg);
                }
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_WriteCharWithoutRsp(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_write_data, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t status;
    r_ble_gtl_cb_evt_t * p_cb_evt;
    st_ble_gattc_wr_char_without_rsp_evt_t * p_wr_wor_evt;

    status = r_ble_gtl_gattc_write (R_BLE_GTL_GATTC_OP_WRITE_NO_RESPONSE,
                                    1, /* Automatically execute the write */
                                    conn_hdl,
                                    p_write_data->attr_hdl,
                                    p_write_data->value.p_value,
                                    p_write_data->value.value_len,
                                    0);

    p_cb_evt = r_ble_gtl_cb_evt_allocate (BLE_GATTC_EVENT_CHAR_WRITE_WITHOUT_RSP, status,
                                          sizeof(st_ble_gattc_wr_char_without_rsp_evt_t));
    if (NULL != p_cb_evt)
    {
        p_cb_evt->data.gattc.conn_hdl = conn_hdl;
        p_cb_evt->data.gattc.param_len =  sizeof(st_ble_gattc_wr_char_without_rsp_evt_t);
        p_wr_wor_evt = p_cb_evt->data.gattc.p_param;
        p_wr_wor_evt->value_hdl = p_write_data->attr_hdl;

        status = r_ble_gtl_cb_evt_queue_add (p_cb_evt);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_SignedWriteChar(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_write_data, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t status;

    status = r_ble_gtl_gattc_write(R_BLE_GTL_GATTC_OP_WRITE_SIGNED,
                                   1, /* Automatically execute the write */
                                   conn_hdl,
                                   p_write_data->attr_hdl,
                                   p_write_data->value.p_value,
                                   p_write_data->value.value_len,
                                   0);

    return status;
}

ble_status_t R_BLE_GTL_GATTC_WriteChar(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_write_data, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t                 status;
    r_ble_gtl_cb_evt_t         * p_cb_evt;
    st_ble_gattc_wr_char_evt_t * p_wr_char;

    status = r_ble_gtl_gattc_write(R_BLE_GTL_GATTC_OP_WRITE,
                                   1, /* Automatically execute the write */
                                   conn_hdl,
                                   p_write_data->attr_hdl,
                                   p_write_data->value.p_value,
                                   p_write_data->value.value_len,
                                   0);
   
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTC_EVENT_CHAR_WRITE_RSP, ((BLE_SUCCESS == status)?BLE_SUCCESS:(BLE_ERR_GROUP_GATT | status)), sizeof(st_ble_gattc_wr_char_evt_t));

        if (NULL != p_cb_evt)
        {
            p_wr_char = p_cb_evt->data.gattc.p_param;
            p_wr_char->value_hdl = p_write_data->attr_hdl;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_WriteLongChar(uint16_t conn_hdl, st_ble_gatt_hdl_value_pair_t * p_write_data, 
                                                                        uint16_t offset)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_write_data, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t                      status;
    r_ble_gtl_cb_evt_t              * p_cb_evt;
    st_ble_gattc_char_part_wr_evt_t * p_char_part_wr;

    status = r_ble_gtl_gattc_write(R_BLE_GTL_GATTC_OP_WRITE,
                                   0, /* Do not automatically execute the write */
                                   conn_hdl,
                                   p_write_data->attr_hdl,
                                   p_write_data->value.p_value,
                                   p_write_data->value.value_len,
                                   offset);
    
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTC_EVENT_LONG_CHAR_WRITE_COMP, ((BLE_SUCCESS == status)?BLE_SUCCESS:(BLE_ERR_GROUP_GATT | status)), sizeof(st_ble_gattc_char_part_wr_evt_t));

        if (NULL != p_cb_evt)
        {
            p_char_part_wr = p_cb_evt->data.gattc.p_param;

            p_char_part_wr->offset              = offset;
            p_char_part_wr->write_data.attr_hdl = p_write_data->attr_hdl;
            p_char_part_wr->write_data.value.value_len =  p_write_data->value.value_len;
            p_char_part_wr->write_data.value.p_value = 0;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_ReliableWrites (uint16_t                                   conn_hdl,
                                             st_ble_gattc_reliable_writes_char_pair_t * p_char_pair,
                                             uint8_t                                    pair_num,
                                             uint8_t                                    auto_flag)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(NULL != p_char_pair, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t         status = BLE_ERR_INVALID_ARG;
    uint8_t              pair   = 0;
    r_ble_gtl_cb_evt_t * p_cb_evt;

    if (0 < pair_num)
    {
        do
        {
            status = r_ble_gtl_gattc_write(R_BLE_GTL_GATTC_OP_WRITE,
                                           auto_flag,
                                           conn_hdl,
                                           p_char_pair[pair].write_data.attr_hdl,
                                           p_char_pair[pair].write_data.value.p_value,
                                           p_char_pair[pair].write_data.value.value_len,
                                           p_char_pair[pair].offset);
            pair++;
        }
        while ((pair < pair_num) && (BLE_SUCCESS == status));
        {
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTC_EVENT_RELIABLE_WRITES_TX_COMP, BLE_SUCCESS, 0);

            if (NULL != p_cb_evt)
            {
                status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
            }
            else
            {
                status = BLE_ERR_MEM_ALLOC_FAILED;
            }
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_GATTC_ExecWrite(uint16_t conn_hdl, uint8_t exe_flag)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                              status;
    r_ble_gtl_cb_evt_t                      * p_cb_evt;
    st_ble_gattc_reliable_writes_comp_evt_t * p_writes_comp;

    status = r_ble_gtl_gattc_send_write_execute(conn_hdl, exe_flag);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTC_EVENT_EXECUTE_WRITE_COMP, BLE_SUCCESS, sizeof(st_ble_gattc_reliable_writes_comp_evt_t));

        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_writes_comp = p_cb_evt->data.gattc.p_param;
            p_writes_comp->exe_flag = exe_flag;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_VS_Init(ble_vs_app_cb_t vs_cb)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != vs_cb, BLE_ERR_INVALID_ARG);
#endif

    g_vs_cb = vs_cb;

    return BLE_SUCCESS;
}

ble_status_t R_BLE_GTL_VS_GetBdAddr(uint8_t addr_type)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    /* All address types returned by same command */
    FSP_PARAMETER_NOT_USED(addr_type);

    ble_status_t                       status   = BLE_ERR_MEM_ALLOC_FAILED;
    r_ble_gtl_cb_evt_t               * p_cb_evt = NULL;
    st_ble_vs_get_bd_addr_comp_evt_t * p_bd_addr_evt;
    r_ble_gtl_gapm_dev_bdaddr_ind_t    bd_addr;

    status = r_ble_gtl_gapm_get_bd_addr(&bd_addr);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_VS_EVENT_GET_ADDR_COMP, BLE_SUCCESS, 
                                                sizeof(st_ble_vs_get_bd_addr_comp_evt_t));
        if (NULL != p_cb_evt)
        {
            p_bd_addr_evt = p_cb_evt->data.vs.p_param;
            p_bd_addr_evt->area = BLE_VS_ADDR_AREA_REG;
            /* Address type enumeration in GTL message matches BLE API address type enumeration */
            p_bd_addr_evt->addr.type = bd_addr.addr.type;
            memcpy(&p_bd_addr_evt->addr.addr[0], &bd_addr.addr.addr.addr[0], BLE_BD_ADDR_LEN);

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

#ifdef ENABLE_STORAGE
ble_status_t R_BLE_GTL_VS_GetBdAddr_dflash(uint8_t addr_type, st_ble_dev_addr_t * p_addr)
{
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN != gp_instance_ctrl->open, BLE_ERR_INVALID_STATE);
#endif

    /* All address types returned by same command */
    FSP_PARAMETER_NOT_USED(addr_type);

    ble_status_t                       status   = BLE_ERR_NOT_FOUND;
    r_ble_gtl_cb_evt_t               * p_cb_evt = NULL;
    st_ble_vs_get_bd_addr_comp_evt_t * p_bd_addr_evt;
    st_ble_dev_addr_t                  bd_addr;
    fsp_err_t                          fsp_status;
      
    fsp_status = r_ble_gtl_storage_read_bd(&bd_addr);

    if (FSP_SUCCESS == fsp_status)
    {
        p_addr->type = bd_addr.type;
        memcpy(&p_addr->addr[0], &bd_addr.addr[0], BLE_BD_ADDR_LEN);
        memcpy(gp_instance_ctrl->loc_bd_addr.addr, &bd_addr.addr[0], BLE_BD_ADDR_LEN);
    }
 
    if (FSP_SUCCESS == fsp_status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_VS_EVENT_GET_ADDR_COMP, BLE_SUCCESS, sizeof(st_ble_vs_get_bd_addr_comp_evt_t));
        if (NULL != p_cb_evt)
        {
            p_bd_addr_evt = p_cb_evt->data.vs.p_param;
            p_bd_addr_evt->area = BLE_VS_ADDR_AREA_DATA_FLASH;
            /* Address type enumeration in GTL message matches BLE API address type enumeration */
            p_bd_addr_evt->addr.type = bd_addr.type;
            memcpy(&p_bd_addr_evt->addr.addr[0], &bd_addr.addr[0], BLE_BD_ADDR_LEN);

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }
    return status;
}
#endif
ble_status_t R_BLE_GTL_VS_SetBdAddr(st_ble_dev_addr_t * p_addr)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != p_addr, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t status = BLE_ERR_INVALID_ARG;

    /* This command should be invoked prior to r_ble_gtl_gapm_send_dev_config_cmd(). */
    if (BLE_GAP_ADDR_RAND == p_addr->type)
    {
        g_dev_params.dev_addr.type = p_addr->type;
        memcpy(&g_dev_params.dev_addr.addr[0], &p_addr->addr[0], BLE_BD_ADDR_LEN);
        status = BLE_SUCCESS;
    }
    else if(BLE_GAP_ADDR_PUBLIC == p_addr->type)
    {
        status = r_ble_gtl_aux_set_bd_address_cmd(p_addr);
    }
    else
    {

    }
    return status;
}

#ifdef ENABLE_STORAGE
ble_status_t R_BLE_GTL_VS_SetBdAddr_dflash(st_ble_dev_addr_t * p_addr)
{
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != p_addr, BLE_ERR_INVALID_ARG);
#endif
    ble_status_t status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_storage_write_bd(*p_addr);
    return status;
}
#endif
ble_status_t R_BLE_GTL_VS_GetRand(uint8_t rand_size)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                       status   = BLE_ERR_INVALID_ARG;
    r_ble_gtl_cb_evt_t               * p_cb_evt = NULL;
    st_ble_vs_get_rand_comp_evt_t    * p_rand_nb_evt;
    r_ble_gtl_gapm_gen_rand_nb_ind_t   rand_nb;

    if (R_BLE_GTL_GET_RAND_SIZE_MAX >= rand_size)
    {
        status = r_ble_gtl_gapm_gen_rand_nb(&rand_nb);
        if (BLE_SUCCESS == status)
        {
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_VS_EVENT_GET_RAND, BLE_SUCCESS, rand_size);
            if (NULL != p_cb_evt)
            {
                p_rand_nb_evt = p_cb_evt->data.vs.p_param;

                p_rand_nb_evt->rand_size = rand_size;
                memcpy(p_rand_nb_evt->p_rand, rand_nb.rand_nb, rand_size);

                status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
            }
            else
            {
                status = BLE_ERR_MEM_ALLOC_FAILED;
            }
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_VS_GetTxPower(uint16_t conn_hdl)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    /* Same power level used for all connections */
    FSP_PARAMETER_NOT_USED(conn_hdl);

    ble_status_t                       status;
    r_ble_gtl_cb_evt_t               * p_cb_evt = NULL;
    st_ble_vs_get_tx_pwr_comp_evt_t  * p_tx_power_evt;
    int8_t                             tx_power;

    status = r_ble_gtl_aux_get_tx_power(&tx_power);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_VS_EVENT_GET_TX_POWER, BLE_SUCCESS,
                                             sizeof(st_ble_vs_get_tx_pwr_comp_evt_t));
        if (NULL != p_cb_evt)
        {
            p_tx_power_evt = p_cb_evt->data.vs.p_param;

            p_tx_power_evt->conn_hdl    = 0;
            p_tx_power_evt->max_tx_pwr  = tx_pwr_lut[sizeof(tx_pwr_lut) - 1];
            p_tx_power_evt->curr_tx_pwr = tx_power;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

ble_status_t R_BLE_GTL_VS_SetTxPower (uint16_t conn_hdl, uint8_t tx_power)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    /* Same power level used for all connections */
    FSP_PARAMETER_NOT_USED(conn_hdl);

    ble_status_t                      status = BLE_ERR_INVALID_ARG;;
    r_ble_gtl_cb_evt_t              * p_cb_evt = NULL;
    st_ble_vs_set_tx_pwr_comp_evt_t * p_tx_power_evt;
    int8_t                            tx_power_dbm;

    if ((BLE_VS_TX_POWER_HIGH == tx_power) ||
        (BLE_VS_TX_POWER_MID == tx_power) ||
        (BLE_VS_TX_POWER_LOW == tx_power))
    {
        status = r_ble_gtl_aux_set_tx_power(tx_power);
        if (BLE_SUCCESS == status)
        {
            /* Read back power in dBm so we can pass back to user */
            status = r_ble_gtl_aux_get_tx_power(&tx_power_dbm);
            if (BLE_SUCCESS == status)
            {
                p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_VS_EVENT_SET_TX_POWER, BLE_SUCCESS,
                                                     sizeof(st_ble_vs_set_tx_pwr_comp_evt_t));
                if (NULL != p_cb_evt)
                {
                    p_tx_power_evt = p_cb_evt->data.vs.p_param;

                    p_tx_power_evt->conn_hdl    = 0;
                    p_tx_power_evt->curr_tx_pwr = tx_power_dbm;

                    status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
                }
                else
                {
                    status = BLE_ERR_MEM_ALLOC_FAILED;
                }
            }
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Handle interrupt from UART. Name of function name is displayed in e2 Studio configurator but is locked and can't
 *  be changed.
 *
 * @param[in]  p_args    Pointer to callabck arguments which includes received data etc.
 *
 **********************************************************************************************************************/
#if defined (BLE_CFG_TRANSPORT_INTERFACE_UART)
void R_BLE_GTL_UartCallback (void * pArgs)
{
    uint8_t * p_rx_msg  = NULL;
    uint8_t   data_byte;
    sci_cb_args_t * p_args = (sci_cb_args_t *) pArgs;

    switch (p_args->event)
    {
        case SCI_EVT_RX_CHAR:
        {
            g_transport_api.read(g_transport_api.p_context, &data_byte, 1);
#if (BLE_CFG_HOST_BOOT_MODE > 0)
            if (false == g_booting)
            {
#endif
                p_rx_msg = r_ble_gtl_msg_parse_rx_char(data_byte);
                if (NULL != p_rx_msg)
                {
                    /* Message received, queue for processing by R_BLE_Execute */
                    if (BLE_SUCCESS != r_ble_gtl_msg_queue_add(&p_rx_msg))
                    {
                        /* Unable to queue message, just discard */
                        r_ble_gtl_msg_buffer_free_from_isr(p_rx_msg);
                    }
                }
#if (BLE_CFG_HOST_BOOT_MODE > 0)
            }
            else
            {
                /* In process of booting DA1453x so store received byte for processing
                by image loading function. OK to overwrite previously received data,
                we are only interested in the last received byte. */
                g_rx_boot_byte = data_byte;
            }
#endif
            break;
        }

        case SCI_EVT_TEI:
        {
            (void)r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_TEI);
            break;
        }

        default:
        {
            break;
        }
    }
}
#elif defined (RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_SPI)
    /* Placeholder - SPI support will be added in a future release */
#endif


ble_status_t R_BLE_GTL_VS_SetSleepMode(uint8_t sleep_mode, uint8_t ram_retention, uint8_t pin_selection)
{
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif
    ble_status_t status = BLE_ERR_INVALID_ARG;

    status = r_ble_gtl_aux_set_sleep_mode_cmd(sleep_mode, ram_retention, pin_selection);
    if (BLE_SUCCESS == status)
    {
        #if (BLE_DA1453x_SLEEP_FLOW_CONTROL)
        active_sleep_mode = sleep_mode;
        #endif

    }

    return status;
}



/***********************************************************************************************************************
 * Local Functions definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Get the value of an RI type attribute from a local database
 *
 * @param[in]  db_index         Index in the database
 * @param[out] p_value          Pointer to the value of the attribue.
 *
 * @retval DB_VALID_RI_INDEX       The indexed attribute had been found in the database. *value holds its value.
 * @retval DB_NON_RI_INDEX     The indexed attribute had not been found in the database. *value remains unchanged.
 **********************************************************************************************************************/
static uint16_t r_ble_gtl_get_ri_value_with_db_index(uint16_t db_index, uint16_t ** p_value)
{
    uint16_t status = DB_NON_RI_INDEX;
    r_ble_gtl_uuid_t             uuid;
    attribute_t *p_attribute = (attribute_t *)&qe_ble_profile[db_index];

    if( p_attribute->notify_read == 1 )
    {
        status = DB_VALID_RI_INDEX;
    }
    else if (p_attribute->uuid_length == BLE_GATT_16_BIT_UUID_SIZE)
    {
        memcpy(&uuid.value, p_attribute->uuid, BLE_GATT_16_BIT_UUID_SIZE);
        if (uuid.value.uuid16 == R_BLE_GTL_CLIENT_CHAR_CONF)
        {
            status = DB_VALID_RI_INDEX;
        }
    }
    else
    {
    }    

    if (status == DB_VALID_RI_INDEX)
    {
        *p_value = (uint16_t *)&p_attribute->value[0];
    }
 
    return status;
}

/*******************************************************************************************************************//**
 *  Checks if the database index holds an RI type attribute.
 *
 * @param[in]  db_index         Index in the database
 *
 * @retval DB_VALID_RI_INDEX       The indexed attribute had been found in the database.
 * @retval DB_NON_RI_INDEX     The indexed attribute had not been found in the database.
 **********************************************************************************************************************/
static uint16_t r_ble_gtl_is_ri_index(uint16_t db_index)
{
    uint16_t status = DB_NON_RI_INDEX;
    r_ble_gtl_uuid_t             uuid;

    attribute_t *p_attribute = ( attribute_t *)&qe_ble_profile[db_index];


    if( p_attribute->notify_read == 1 )
    {
        status = DB_VALID_RI_INDEX;
    }
    else if (p_attribute->uuid_length == BLE_GATT_16_BIT_UUID_SIZE)
    {
        memcpy(&uuid.value, p_attribute->uuid, BLE_GATT_16_BIT_UUID_SIZE);
        if (uuid.value.uuid16 == R_BLE_GTL_CLIENT_CHAR_CONF)
        {
            status = DB_VALID_RI_INDEX;
        }
    }
    else
    {
    }
 
    return status;
}

/*******************************************************************************************************************//**
 *  Checks if the database index holds an CCC type attribute (notification or indication).
 *
 * @param[in]  db_index         Index in the database
 *
 * @retval DB_VALID_RI_INDEX       The indexed attribute had been found in the database.
 * @retval DB_NON_RI_INDEX     The indexed attribute had not been found in the database.
 **********************************************************************************************************************/
static uint16_t r_ble_gtl_is_ccc_ri_index(uint16_t db_index)
{
    uint16_t status = DB_NON_RI_INDEX;
    r_ble_gtl_uuid_t             uuid;

    attribute_t *p_attribute =  (attribute_t *)&qe_ble_profile[db_index];

    if (p_attribute->uuid_length == BLE_GATT_16_BIT_UUID_SIZE)
    {
        memcpy(&uuid.value, p_attribute->uuid, BLE_GATT_16_BIT_UUID_SIZE);
        if (uuid.value.uuid16 == R_BLE_GTL_CLIENT_CHAR_CONF)
        {
            status = DB_VALID_RI_INDEX;
        }
    }

    return status;
}



/*******************************************************************************************************************//**
 * Sets the value of an RI type attribute in the local database.
 *
 * @param[in]  db_index         Index in the database
 * @param[out] value            The value of the attribue.
 *
 * @retval DB_VALID_RI_INDEX       The indexed attribute had been found in the database. Successful write.
 * @retval DB_NON_RI_INDEX     The indexed attribute had not been found in the database. Unsuccessful write.
 **********************************************************************************************************************/
static uint16_t r_ble_gtl_set_ri_value_with_db_index(uint16_t db_index, uint16_t *p_value, uint16_t length )
{
    uint16_t status = DB_INVALID_PARAM;

    attribute_t *p_att =  (attribute_t *)&qe_ble_profile[db_index];
    if (length == p_att->value_length)
    {
        memcpy( &qe_ble_profile[db_index].value[0], p_value, length);
        status = DB_VALID_RI_INDEX;
    }
 
    return status;
}
 
/*******************************************************************************************************************//**
 *  Process incoming GTL messages received via transport layer. Messages might generated a callback event.
 *
 * @param[in]  p_gtl_msg        Pointer to buffer containing received GTL message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_msg_process(uint8_t * p_gtl_msg)
{
    r_ble_gtl_msg_hdr_t * p_gtl_msg_hdr = (r_ble_gtl_msg_hdr_t *)p_gtl_msg;
    r_ble_gtl_cb_evt_t  * p_cb_evt      = NULL;

    if (R_BLE_GTL_TASK_ID_GTL == p_gtl_msg_hdr->dest_id)
    {
        uint16_t src_id = p_gtl_msg_hdr->src_id & R_BLE_GTL_SRC_ID_MASK;

        switch (src_id)
        {

            case R_BLE_GTL_TASK_ID_GAPM:
            {
                p_cb_evt = r_ble_gtl_gapm_handler(p_gtl_msg);
                break;
            }

            case R_BLE_GTL_TASK_ID_GAPC:
            {
                p_cb_evt = r_ble_gtl_gapc_handler(p_gtl_msg);
                break;
            }

            case R_BLE_GTL_TASK_ID_GATTC:
            {
                p_cb_evt = r_ble_gtl_gattc_handler(p_gtl_msg);
                break;
            }

            default:
            {
                /* Unknown message, do nothing */
                break;
            }
        }
    }

    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle received GAP client messages. Messages might generated a callback event.
 *
 * @param[in]  p_gtl_msg        Pointer to buffer containing received GAP client message (including header)
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_handler(uint8_t * p_gtl_msg)
{
    uint16_t              conn_hdl      = 0x0000;
    r_ble_gtl_cb_evt_t  * p_cb_evt      = NULL;
    r_ble_gtl_msg_hdr_t * p_gtl_msg_hdr = (r_ble_gtl_msg_hdr_t *)p_gtl_msg;

    /* Connection handle is part of the source ID - it only has 8-bit range but is stored as uint16_t to be 
    consistent with the R_BLE API */
    conn_hdl = p_gtl_msg_hdr->src_id >> 8;

    switch (p_gtl_msg_hdr->msg_id)
    {
        case R_BLE_GTL_GAPC_CONNECTION_REQ_IND:
        {
            r_ble_gtl_gapc_connection_req_ind_t * p_param = 
                                    (r_ble_gtl_gapc_connection_req_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_connection_req_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GAPC_DISCONNECT_IND:
        {
            r_ble_gtl_gapc_disconnect_ind_t * p_param = 
                                    (r_ble_gtl_gapc_disconnect_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_disconnect_ind_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GAPC_LE_PKT_SIZE_IND:
        {
            r_ble_gtl_gapc_le_pkt_size_ind_t * p_param = 
                                    (r_ble_gtl_gapc_le_pkt_size_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_le_pkt_size_ind_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GAPC_PARAM_UPDATED_IND:
        {
            r_ble_gtl_gapc_param_update_ind_t * p_param = 
                                    (r_ble_gtl_gapc_param_update_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_param_update_ind_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GAPC_GET_DEV_INFO_REQ_IND:
        {
            r_ble_gtl_gapc_get_dev_info_req_ind_t * p_param = 
                                    (r_ble_gtl_gapc_get_dev_info_req_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_get_dev_info_req_ind_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GAPC_SET_DEV_INFO_REQ_IND:
        {
             r_ble_gtl_gapc_set_dev_info_req_ind_t * p_param = (r_ble_gtl_gapc_set_dev_info_req_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
             p_cb_evt = r_ble_gtl_gapc_set_dev_info_req_ind_handler(conn_hdl, p_param);
             break;
        }

        case R_BLE_GTL_GAPC_PARAM_UPDATE_REQ_IND:
        {
            r_ble_gtl_gapc_param_update_req_ind_t * p_param = 
                                    (r_ble_gtl_gapc_param_update_req_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_parm_update_req_ind_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GAPC_BOND_REQ_IND:
        {        
            r_ble_gtl_gapc_bond_req_ind_t * p_param = 
                                            (r_ble_gtl_gapc_bond_req_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_bond_req_ind_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GAPC_BOND_IND:
        {
            r_ble_gtl_gapc_bond_ind_t * p_param = (r_ble_gtl_gapc_bond_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_bond_ind_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GAPC_ENCRYPT_REQ_IND:
        {
            r_ble_gtl_gapc_encrypt_req_ind_t * p_param = 
                                           (r_ble_gtl_gapc_encrypt_req_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_encrypt_req_ind_handler(conn_hdl, p_param);
            break;
        }
        case R_BLE_GTL_GAPC_ENCRYPT_IND:
        {
            gapc_encrypt_ind_t * p_param = (gapc_encrypt_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapc_encrypt_ind_handler(conn_hdl, p_param);
            break;
        }
        case R_BLE_GTL_GAPC_SECURITY_IND:
        {
            gapc_security_ind_t * p_param = (gapc_security_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            r_ble_gtl_gapc_security_ind_handler(conn_hdl, p_param);
            break;
        }

        default:
        {
            /* Unknown message, do nothing */
            break;
        }
    }

    return p_cb_evt;
}
/*******************************************************************************************************************//**
 *  Handle GATT client write request indication message for RI attributes.

 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GATT client write request indication message
 *
 * @retval NULL                 No callback event generated by message processing
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_write_req_ind_handler(uint16_t conn_hdl,
									 r_ble_gtl_gattc_write_req_ind_t * p_param, bool local_db)
{
    ble_status_t                   status;
    r_ble_gtl_cb_evt_t           * p_cb_evt = NULL;
    st_ble_gatts_write_rsp_evt_t * p_write_rsp_evt;
    st_ble_gatts_db_access_evt_t * p_db_access_evt;
    st_ble_gatt_value_t            value;

    status = r_ble_gtl_gattc_send_write_cfm(conn_hdl, R_BLE_GTL_GAP_ERR_NO_ERROR, p_param->handle);

    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTS_EVENT_WRITE_RSP_COMP, status, sizeof(st_ble_gatts_write_rsp_evt_t));
    if (NULL != p_cb_evt)
    {
        p_cb_evt->data.gatts.conn_hdl  = conn_hdl;

        p_write_rsp_evt = p_cb_evt->data.gatts.p_param;
        p_write_rsp_evt->attr_hdl = (uint16_t)(p_param->handle - g_dev_params.att_hndl_offset);

        r_ble_gtl_cb_evt_queue_add(p_cb_evt);
    }

    /* Update the attribute database with the value written */
    if ( local_db)
    {
        r_ble_gtl_set_ri_value_with_db_index((uint16_t)(p_param->handle - g_dev_params.att_hndl_offset) ,  (uint16_t *)p_param->value, p_param->length);
    }
    else
    {
        /* Update the attribute database with the value written */
        value.value_len = p_param->length;
        value.p_value   = p_param->value;
        status = r_ble_gtl_gattm_set_att_value_int(0, p_param->handle, &value);
    }

    /* Send the application callback */
    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTS_EVENT_DB_ACCESS_IND, status, p_param->length);
    if (NULL != p_cb_evt)
    {
         p_cb_evt->data.gatts.conn_hdl  = conn_hdl;

         p_db_access_evt = p_cb_evt->data.gatts.p_param;
         p_db_access_evt->p_handle->conn_hdl        = conn_hdl;
         p_db_access_evt->p_params->attr_hdl        = (uint16_t)(p_param->handle - g_dev_params.att_hndl_offset);
         //p_db_access_evt->p_params->db_op           = BLE_GATTS_OP_CHAR_PEER_WRITE_REQ;

         attribute_t *p_attribute = (attribute_t *)&qe_ble_profile[p_db_access_evt->p_params->attr_hdl];

         uint8_t db_op = BLE_GATTS_OP_CHAR_PEER_WRITE_REQ;
         r_ble_gtl_uuid_t             uuid;

         if (p_attribute->uuid_length == BLE_GATT_16_BIT_UUID_SIZE)
         {
             uuid.length = BLE_GATT_16_BIT_UUID_SIZE;
             memcpy(&uuid.value, p_attribute->uuid, BLE_GATT_16_BIT_UUID_SIZE);

             if (uuid.value.uuid16 == R_BLE_GTL_CLIENT_CHAR_CONF)
             {
                 db_op           = BLE_GATTS_OP_CHAR_PEER_CLI_CNFG_WRITE_REQ;
             }
             else if(uuid.value.uuid16 == R_BLE_GTL_SERVER_CHAR_CONF)
             {
                 db_op           = BLE_GATTS_OP_CHAR_PEER_SER_CNFG_WRITE_REQ;
             }
             else
             {
             }
         }
         else
         {
         }

         p_db_access_evt->p_params->db_op           = db_op;;
         p_db_access_evt->p_params->value.value_len = p_param->length;
         memcpy(p_db_access_evt->p_params->value.p_value, p_param->value, p_param->length);
    }

     return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle GATT client read request indication message. 
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GATT client read request indication message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_read_req_ind_handler(uint16_t conn_hdl, r_ble_gtl_gattc_read_req_ind_t * p_param)
{
    uint8_t status = R_BLE_GTL_ATT_ERR_REQUEST_NOT_SUPPORTED;
    uint8_t *p_value = NULL;
    uint16_t value_len = 0;
    uint16_t att_index = (uint16_t) ((int32_t) p_param->handle - g_dev_params.att_hndl_offset);
    r_ble_gtl_cb_evt_t *p_cb_evt = NULL;
    st_ble_gatts_db_access_evt_t *p_db_access_evt;
    uint16_t *p_ccc_val = 0;

  
    /* All characteristic values are stored in the DA1453x, except for client configuration characteristics that are RI type*/
    if ( DB_VALID_RI_INDEX == r_ble_gtl_get_ri_value_with_db_index (att_index, &p_ccc_val))
    {
        status = R_BLE_GTL_GAP_ERR_NO_ERROR;
        p_cb_evt = r_ble_gtl_cb_evt_allocate (BLE_GATTS_EVENT_DB_ACCESS_IND, status, sizeof(p_param->handle));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gatts.conn_hdl = conn_hdl;
            p_db_access_evt = p_cb_evt->data.gatts.p_param;
            p_db_access_evt->p_handle->conn_hdl = conn_hdl;
            p_db_access_evt->p_params->attr_hdl = (uint16_t) (p_param->handle - g_dev_params.att_hndl_offset);

            attribute_t *p_attribute = (attribute_t *)&qe_ble_profile[p_db_access_evt->p_params->attr_hdl];
            r_ble_gtl_uuid_t uuid;

            uint8_t db_op = BLE_GATTS_OP_CHAR_PEER_READ_REQ;

            if (p_attribute->uuid_length == BLE_GATT_16_BIT_UUID_SIZE)
            {
                uuid.length = BLE_GATT_16_BIT_UUID_SIZE;
                memcpy (&uuid.value, p_attribute->uuid, BLE_GATT_16_BIT_UUID_SIZE);

                if (uuid.value.uuid16 == R_BLE_GTL_CLIENT_CHAR_CONF)
                {
                    db_op = BLE_GATTS_OP_CHAR_PEER_CLI_CNFG_READ_REQ;
                }
                else if (uuid.value.uuid16 == R_BLE_GTL_SERVER_CHAR_CONF)
                {
                    db_op = BLE_GATTS_OP_CHAR_PEER_SER_CNFG_READ_REQ;
                }
                else
                {
                }
            }
            else
            {
            }
            p_db_access_evt->p_params->db_op = db_op;
        }
    }
    else if (BLE_SUCCESS == r_ble_gtl_gap_get_char_value_by_handle (att_index, &p_value, &value_len))
    {
        status = R_BLE_GTL_GAP_ERR_NO_ERROR;
        (void) r_ble_gtl_gattc_send_read_cfm (conn_hdl, status, p_param->handle, value_len, p_value);
    }
    else
    {
        status = R_BLE_GTL_ATT_ERR_INVALID_HANDLE;
        p_cb_evt = r_ble_gtl_cb_evt_allocate (BLE_GATTS_EVENT_DB_ACCESS_IND, status, sizeof(p_param->handle));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gatts.conn_hdl = conn_hdl;
            p_db_access_evt = p_cb_evt->data.gatts.p_param;
            p_db_access_evt->p_handle->conn_hdl = conn_hdl;
            p_db_access_evt->p_params->attr_hdl = (uint16_t) (p_param->handle - g_dev_params.att_hndl_offset);
        }
    }

    return p_cb_evt;
}
/*******************************************************************************************************************//**
 *  Handle GATT client handles read indication request for a Client Characteristic Configuration. These values are always
 *  stored in RA CPU database.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GATT client read request indication message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 ********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_read_ccc_ind_handler(uint16_t conn_hdl, r_ble_gtl_gattc_read_req_ind_t * p_param)
{
    uint8_t status = R_BLE_GTL_ATT_ERR_REQUEST_NOT_SUPPORTED;
    uint8_t *p_value = NULL;
    uint16_t value_len = 0;
    uint16_t att_index = (uint16_t) ((int32_t) p_param->handle - g_dev_params.att_hndl_offset);
    r_ble_gtl_cb_evt_t *p_cb_evt = NULL;
    st_ble_gatts_db_access_evt_t *p_db_access_evt;
   
    /* All characteristic values are stored in the DA1453x, except for client configuration characteristics that are RI type*/
    p_cb_evt = r_ble_gtl_cb_evt_allocate (BLE_GATTS_EVENT_DB_ACCESS_IND, status, sizeof(p_param->handle));
    if (NULL != p_cb_evt)
    {
        p_cb_evt->data.gatts.conn_hdl = conn_hdl;
        p_db_access_evt = p_cb_evt->data.gatts.p_param;
        p_db_access_evt->p_handle->conn_hdl = conn_hdl;
        p_db_access_evt->p_params->attr_hdl = (uint16_t) (p_param->handle - g_dev_params.att_hndl_offset);
       
        p_db_access_evt->p_params->db_op = BLE_GATTS_OP_CHAR_PEER_CLI_CNFG_READ_REQ;

        if (BLE_SUCCESS == r_ble_gtl_gap_get_char_value_by_handle (att_index, &p_value, &value_len))
        {
            status = R_BLE_GTL_GAP_ERR_NO_ERROR;
            (void) r_ble_gtl_gattc_send_read_cfm (conn_hdl, status, p_param->handle, value_len, p_value);
        }
    }

    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle received GATT client messages. Messages might generated a callback event.
 *
 * @param[in]  p_gtl_msg        Pointer to buffer containing received GATT client message (including header)
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_handler(uint8_t * p_gtl_msg)
{
    uint16_t              conn_hdl      = 0x0000;
    r_ble_gtl_cb_evt_t  * p_cb_evt      = NULL;
    r_ble_gtl_msg_hdr_t * p_gtl_msg_hdr = (r_ble_gtl_msg_hdr_t *)p_gtl_msg;

    /* Connection handle is part of the source ID - it only has 8-bit range but is stored as uint16_t to be consistent with the R_BLE API */
    conn_hdl = p_gtl_msg_hdr->src_id >> 8;

    switch (p_gtl_msg_hdr->msg_id)
    {
        case R_BLE_GTL_GATTC_EVENT_REQ_IND:
        case R_BLE_GTL_GATTC_EVENT_IND:
        {
            r_ble_gtl_gattc_event_ind_t * p_param = (r_ble_gtl_gattc_event_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];

            p_cb_evt = r_ble_gtl_gattc_event_ind_handler(conn_hdl, p_param);
            break;
        }
        case R_BLE_GTL_GATTC_WRITE_REQ_IND:
        {

            r_ble_gtl_gattc_write_req_ind_t * p_param = 
                                        (r_ble_gtl_gattc_write_req_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];

            /* If the atttibute is RI type, then it should not be accessed via
			 DA1453x database but through host database */
            uint16_t db_index= (uint16_t)(p_param->handle - g_dev_params.att_hndl_offset);
            if (r_ble_gtl_is_ri_index(db_index) == DB_VALID_RI_INDEX)
            {
                p_cb_evt = r_ble_gtl_gattc_write_req_ind_handler(conn_hdl, p_param, 1);
            }
            else
            {
                p_cb_evt = r_ble_gtl_gattc_write_req_ind_handler(conn_hdl, p_param, 0);
            }

            break;
        }

        case R_BLE_GTL_GATTC_READ_REQ_IND:
        {
            r_ble_gtl_gattc_read_req_ind_t * p_param = (r_ble_gtl_gattc_read_req_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];

            uint16_t db_index= (uint16_t)(p_param->handle - g_dev_params.att_hndl_offset);
            /* If the user has not mark the CCC as notify_read, the CCC will be handled automatically */
            /* CCC attributes for DA1453x are always RI type */
            if ((r_ble_gtl_is_ccc_ri_index(db_index) == DB_VALID_RI_INDEX) && (r_ble_gtl_attribute_is_ri(db_index)==false))
            {
                p_cb_evt = r_ble_gtl_gattc_read_ccc_ind_handler(conn_hdl, p_param);
            }
            else
            {
                p_cb_evt = r_ble_gtl_gattc_read_req_ind_handler(conn_hdl, p_param);
            }
            break;
        }

        case R_BLE_GTL_GATTC_MTU_CHANGED_IND:
        {
            r_ble_gtl_gattc_mtu_changed_ind_t * p_param = 
                                    (r_ble_gtl_gattc_mtu_changed_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gattc_mtu_changed_ind_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GATTC_ATT_INFO_REQ_IND:
        {
            r_ble_gtl_gattc_att_info_req_t * p_param = (r_ble_gtl_gattc_att_info_req_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gattc_att_info_req_ind_handler(conn_hdl, p_param);
            break;
        }

        case R_BLE_GTL_GATTC_SVC_CHANGED_CFG_IND:
        {
            r_ble_gtl_gattc_svc_changed_cfg_ind_t * p_param = (r_ble_gtl_gattc_svc_changed_cfg_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gattc_event_svc_changed_handler(conn_hdl, p_param);
            break;

        }

        default:
        {
            /* Unknown message, do nothing */
            break;
        }
    }

    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle GAPC connection request message. Messages might generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client connection request message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_connection_req_handler(uint16_t conn_hdl, 
                                                r_ble_gtl_gapc_connection_req_ind_t * p_param)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);

    ble_status_t                      status;
    uint8_t                           operation;
    r_ble_gtl_cb_evt_t              * p_cb_evt = NULL;
    r_ble_gtl_cb_evt_t              * p_cb_evt_ind = NULL;

    /*
     * With the reception of the GAPC_CONNECTION_REQ_INDs the connection procedure begins and the advertising of the
     * peripheral stops. Thus, GAPM_CMP_EVT with an operation of GAPM_CONNECTION_DIRECT is sent from  the BLE App to
     * the GTL Host on the central’s side and GAPM_CMP_EVT with an operation of GAPM_ADV_UNDIRECT is sent from the
     * BLE App to the GTL Host on the peripheral’s side.
     */

    if (g_dev_params.state & R_BLE_GTL_DEV_STATE_ADVERTISING)
    {
        operation = R_BLE_GTL_GAPM_OP_ADV_UNDIRECT;
    }
    else if (g_dev_params.state & R_BLE_GTL_DEV_STATE_CONNECTING)
    {
        operation = R_BLE_GTL_GAPM_OP_CONNECTION_AUTO;
    }
    else
    {
        return p_cb_evt;
    }
 
    status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT,
                                                 operation,
                                                 0,
                                                 R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
                                                 
    if (operation == R_BLE_GTL_GAPM_OP_ADV_UNDIRECT)
    {
       if (status == R_BLE_GTL_GAP_ERR_NO_ERROR)
       {
           p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_ADV_OFF, BLE_SUCCESS, 0);
       }
       else
       {
           p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_ADV_OFF, BLE_ERR_UNSPECIFIED, 0);
       }
       g_dev_params.state &=  (uint8_t)~R_BLE_GTL_DEV_STATE_ADVERTISING;
    }
    else if (operation == R_BLE_GTL_GAPM_OP_CONNECTION_AUTO)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_CREATE_CONN_COMP, status, 0);
    }
    else
    {
    }
 
    if (BLE_SUCCESS == status)
    {
        g_dev_params.state &= (uint8_t)~R_BLE_GTL_DEV_STATE_CONNECTING;
        g_dev_params.state |= R_BLE_GTL_DEV_STATE_CONNECTED;
        g_dev_params.nof_active_connections += 1;

        if (BLE_SUCCESS == status)
        {
            p_cb_evt_ind = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_CONN_IND, BLE_SUCCESS, sizeof(st_ble_gap_conn_evt_t));

            if (NULL != p_cb_evt_ind)
            {
                st_ble_gap_conn_evt_t *p_conn_param = p_cb_evt_ind->data.gap.p_param;
                /* Role is not provided in this GTL message */

                if(memcmp(&p_param->peer_addr, &int_conn_addr[0], BLE_BD_ADDR_LEN) == 0)
                {
                    p_conn_param->role = R_BLE_GTL_CENTRAL_ROLE; // MASTER
                }
                else
                {
                    p_conn_param->role = R_BLE_GTL_PERIPHERAL_ROLE; // SLAVE
                }
                memset(int_conn_addr, 0x00, BLE_BD_ADDR_LEN);

                /* Remote_rpa needs to be updated TODO*/
                    p_conn_param->clk_acc = p_param->clk_accuracy;
                    p_conn_param->conn_hdl = p_param->conhdl;
                    p_conn_param->conn_latency = p_param->con_latency;
                    p_conn_param->conn_intv = p_param->con_interval;
                    p_conn_param->sup_to = p_param->sup_to;
                    p_conn_param->remote_addr_type = p_param->peer_addr_type;
                    memcpy(&p_conn_param->remote_addr[0], &p_param->peer_addr.addr[0], BLE_BD_ADDR_LEN);
                }
            }
        }
    if((NULL != p_cb_evt_ind) && (NULL != p_cb_evt))
    {
        r_ble_gtl_cb_evt_queue_add(p_cb_evt_ind);
        return p_cb_evt;
    }
    if(p_cb_evt_ind != 0)
    {
        return p_cb_evt_ind;
    }
     
    return p_cb_evt;
}

/*********************************************************************************************************************
 *  Send the GAPC_CONNECTION_CFM (0x0E02) cmd following a CONNECTION_REQ_IND event.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  auth_par                 Current Auth value to be send.
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_connection_cfm_cmd(uint16_t conn_hdl, uint8_t auth_par)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;
    r_ble_gtl_gapc_connection_cfm_t *p_cfm;

    p_cfm = (r_ble_gtl_gapc_connection_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_CONNECTION_CFM,
                                                                      R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                      R_BLE_GTL_TASK_ID_GTL,
                                                                      sizeof(r_ble_gtl_gapc_connection_cfm_t));

    if (NULL != p_cfm)
    {
        // auth_temp = (uint8_t)((ble_pairing_param_local.bonding << 0) | (ble_pairing_param_local.mitm << 2) | (ble_pairing_param_local.sec_conn_only << 3));
        p_cfm->auth = auth_par;
        status = r_ble_gtl_msg_transmit((uint8_t *)p_cfm);
    }
    return status;
}
/*******************************************************************************************************************//**
 *  Handle GAPC disconnect request message. Messages might generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client disconnect message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_disconnect_ind_handler(uint16_t conn_hdl, 
                                                                r_ble_gtl_gapc_disconnect_ind_t * p_param)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);

    r_ble_gtl_cb_evt_t * p_cb_evt = NULL;
    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_DISCONN_IND, BLE_SUCCESS, sizeof(st_ble_gap_disconn_evt_t));

    if (NULL != p_cb_evt)
    {
        st_ble_gap_disconn_evt_t * p_discon_param = p_cb_evt->data.gap.p_param;
        p_discon_param->conn_hdl = p_param->conhdl;
        p_discon_param->reason   = p_param->reason;
    }

    g_dev_params.nof_active_connections -= 1;
    if ( g_dev_params.nof_active_connections == 0)
    {
        g_dev_params.state &= (uint8_t)~R_BLE_GTL_DEV_STATE_CONNECTED;
    }

    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle GAPC LE packet size indication message. Messages might generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client LE packet size indication message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_le_pkt_size_ind_handler(uint16_t conn_hdl, 
                                                                r_ble_gtl_gapc_le_pkt_size_ind_t * p_param)
{
    r_ble_gtl_cb_evt_t * p_cb_evt = NULL;

    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_DATA_LEN_CHG, BLE_SUCCESS, 
                                        sizeof(st_ble_gap_data_len_chg_evt_t));

    if (NULL != p_cb_evt)
    {
        st_ble_gap_data_len_chg_evt_t * p_len_chg_param = p_cb_evt->data.gap.p_param;

        p_len_chg_param->conn_hdl  = conn_hdl;
        p_len_chg_param->tx_octets = p_param->max_tx_octets;
        p_len_chg_param->tx_time   = p_param->max_tx_time;
        p_len_chg_param->rx_octets = p_param->max_rx_octets;
        p_len_chg_param->rx_time   = p_param->max_rx_time;
    }

    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle GAPC connection parameter update message. Messages might generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client connection parameter update message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_param_update_ind_handler(uint16_t conn_hdl, 
                                                                r_ble_gtl_gapc_param_update_ind_t * p_param)
{
    r_ble_gtl_cb_evt_t * p_cb_evt = NULL;

    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_CONN_PARAM_UPD_COMP, BLE_SUCCESS, 
                                                    sizeof(st_ble_gap_conn_upd_evt_t));

    if (NULL != p_cb_evt)
    {
        st_ble_gap_conn_upd_evt_t * p_update_param = p_cb_evt->data.gap.p_param;

        p_update_param->conn_hdl     = conn_hdl;
        p_update_param->conn_intv    = p_param->intv;
        p_update_param->conn_latency = p_param->latency;
        p_update_param->sup_to       = p_param->timeout;
    }

    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle GAPC device information request message. Message does not generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client device information request message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_get_dev_info_req_ind_handler(uint16_t conn_hdl, 
                                                                        r_ble_gtl_gapc_get_dev_info_req_ind_t * p_param)
{
    switch (p_param->operation)
    {
        case R_BLE_GTL_GAPC_DEV_NAME:
        {
            r_ble_gtl_gapc_get_dev_info_cfm_t * p_cmd;

            p_cmd = (r_ble_gtl_gapc_get_dev_info_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_GET_DEV_INFO_CFM,
                                                                R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                R_BLE_GTL_TASK_ID_GTL,
                                                                                sizeof (r_ble_gtl_gapc_get_dev_info_cfm_t) + g_dev_params.dev_name_length);
            if (NULL != p_cmd)
            {
                p_cmd->req = p_param->operation;
                p_cmd->info.name.length = g_dev_params.dev_name_length;
                memcpy(p_cmd->info.name.value, g_dev_params.dev_name, p_cmd->info.name.length);
                p_cmd->hdr.param_length = sizeof(p_cmd->req) + sizeof(p_cmd->padding) 
                                            + sizeof(p_cmd->info.name.length) + p_cmd->info.name.length;

                (void)r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            }

            break;
        }

        case R_BLE_GTL_GAPC_DEV_APPEARANCE:
        {
            r_ble_gtl_gapc_get_dev_info_cfm_t * p_cmd;

            p_cmd = (r_ble_gtl_gapc_get_dev_info_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_GET_DEV_INFO_CFM,
                                                                    R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof (r_ble_gtl_gapc_get_dev_info_cfm_t));
            if (NULL != p_cmd)
            {
                p_cmd->req = p_param->operation;
                p_cmd->info.appearance = g_dev_params.appearance;
                p_cmd->hdr.param_length = sizeof(p_cmd->req) + sizeof(p_cmd->padding) + sizeof(p_cmd->info.appearance);

                (void)r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            }

            break;
        }

        case R_BLE_GTL_GAPC_DEV_SLV_PREF_PARAMS:
        {
            r_ble_gtl_gapc_get_dev_info_cfm_t * p_cmd;

            p_cmd = (r_ble_gtl_gapc_get_dev_info_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_GET_DEV_INFO_CFM,
                                                                               R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                               R_BLE_GTL_TASK_ID_GTL,
                                                                               sizeof (r_ble_gtl_gapc_get_dev_info_cfm_t));
            if (NULL != p_cmd)
            {
                p_cmd->req = p_param->operation;
                p_cmd->hdr.param_length = sizeof(p_cmd->req) + sizeof(p_cmd->padding) + sizeof(r_ble_gtl_gap_slv_pref_params_t);

                p_cmd->info.slv_pref_params.con_intv_max = g_dev_params.ppcp.con_intv_max;
                p_cmd->info.slv_pref_params.con_intv_min = g_dev_params.ppcp.con_intv_min;
                p_cmd->info.slv_pref_params.conn_timeout = g_dev_params.ppcp.conn_timeout;
                p_cmd->info.slv_pref_params.slave_latency = g_dev_params.ppcp.slave_latency;

                (void)r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            }
            /* Place holder for future functionality */
            break;
        }

        case R_BLE_GTL_GAPC_DEV_CENTRAL_RPA:
        {
            /* Place holder for future functionality */
            break;
        }

        case R_BLE_GTL_GAPC_DEV_RPA_ONLY:
        {
            /* Place holder for future functionality */
            break;
        }

        default:
        {
            /* Unknown operation - do nothing */
            break;
        }
    }

    return NULL;
}

/*******************************************************************************************************************//**
 *  Handle GAPC device information requestindication  message. Message does not generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client device information set message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_set_dev_info_req_ind_handler(uint16_t conn_hdl, r_ble_gtl_gapc_set_dev_info_req_ind_t * p_param)
{
    r_ble_gtl_gapc_set_dev_info_cfm_t *p_cmd;
    uint8_t status = R_BLE_GTL_GAP_ERR_REJECTED;
    switch (p_param->req)
    {
        case R_BLE_GTL_GAPC_DEV_NAME:
        {
            if(p_param->length <= R_BLE_GTL_GAP_DEV_NAME_LEN_MAX)
            {
                memcpy(g_dev_params.dev_name, p_param->value, p_param->length);
                g_dev_params.dev_name_length = p_param->length;
                status = R_BLE_GTL_GAP_ERR_NO_ERROR;
            }

            break;
        }
        case R_BLE_GTL_GAPC_DEV_APPEARANCE:
        {
            if(p_param->length <=2)
            {
                g_dev_params.appearance = *(uint16_t *)p_param->value;
                status = R_BLE_GTL_GAP_ERR_NO_ERROR;
            }
            break;
        }
    }

    p_cmd = (r_ble_gtl_gapc_set_dev_info_cfm_t*) r_ble_gtl_msg_allocate (R_BLE_GTL_GAPC_SET_DEV_INFO_CFM,
                                                                         R_BLE_GTL_TASK_ID_GAPC + (uint16_t) (conn_hdl << 8),
                                                                         R_BLE_GTL_TASK_ID_GTL,
                                                                         sizeof(r_ble_gtl_gapc_set_dev_info_cfm_t));
    if (NULL != p_cmd)
    {
        p_cmd->req = p_param->req;
        p_cmd->status = status;

        (void) r_ble_gtl_msg_transmit ((uint8_t*) p_cmd);
    }

    return NULL;
}

/*******************************************************************************************************************//**
 *  Handle GAPC connection parameter indication message. Message does not generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client connection parameter indication message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_parm_update_req_ind_handler(uint16_t conn_hdl, 
                                                                    r_ble_gtl_gapc_param_update_req_ind_t * p_param)
{
    FSP_PARAMETER_NOT_USED(p_param);

    /* Accept parameters */
    (void)r_ble_gtl_gapc_send_param_update_cfm(conn_hdl, 0x01);

    return NULL;
}

/*******************************************************************************************************************//**
 *  Handles the recepcion of GATTC message SVC CHANGED
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GATTC event message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static  r_ble_gtl_cb_evt_t *  r_ble_gtl_gattc_event_svc_changed_handler(uint16_t conn_hdl, r_ble_gtl_gattc_svc_changed_cfg_ind_t * p_param)
{
    uint16_t type = BLE_GATTC_EVENT_HDL_VAL_SVC_CHNG;
    st_ble_gattc_svc_chng_evt_t *p_evt_svc_chng_param;
    r_ble_gtl_cb_evt_t     * p_cb_evt    = NULL;
    p_cb_evt = r_ble_gtl_cb_evt_allocate (type, BLE_SUCCESS, sizeof(st_ble_gattc_svc_chng_evt_t));

    if (NULL != p_cb_evt)
    {
        p_cb_evt->data.gattc.conn_hdl = conn_hdl;
        p_evt_svc_chng_param = p_cb_evt->data.gattc.p_param;
        p_evt_svc_chng_param->ind_cfg = p_param->ind_cfg;
    }

    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handles the reception of GATTC message NOTIFY/INDICATE
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GATTC event message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static  r_ble_gtl_cb_evt_t *  r_ble_gtl_gattc_event_ind_handler(uint16_t conn_hdl, r_ble_gtl_gattc_event_ind_t * p_param)
{
    uint16_t                 type        = BLE_GATTC_EVENT_ERROR_RSP;
    st_ble_gattc_ntf_evt_t * p_evt_ntf_param;
    st_ble_gattc_ind_evt_t * p_evt_ind_param;
    r_ble_gtl_cb_evt_t     * p_cb_evt    = NULL;
    uint8_t                * p_evt_data  = NULL;

    if( p_param->type == R_BLE_GTL_GATTC_OP_NOTIFY)
    {
        type = BLE_GATTC_EVENT_HDL_VAL_NTF;

        p_cb_evt = r_ble_gtl_cb_evt_allocate (type, BLE_SUCCESS, sizeof(st_ble_gattc_ntf_evt_t));

        p_evt_data = r_ble_gtl_malloc (p_param->length);

        if ((NULL != p_cb_evt) && (NULL != p_evt_data))
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_evt_ntf_param = p_cb_evt->data.gattc.p_param;
            p_evt_ntf_param->data.attr_hdl = p_param->handle;
            p_evt_ntf_param->data.value.p_value = p_evt_data;
            p_evt_ntf_param->data.value.value_len = p_param->length;
            memcpy (p_evt_data, p_param->value, p_param->length);
        }
        else
        {
            r_ble_gtl_free (p_evt_data);
            r_ble_gtl_cb_evt_free (p_cb_evt);
        }
    }
    else if( p_param->type== R_BLE_GTL_GATTC_OP_INDICATE )
    {
        r_ble_gtl_gattc_send_event_cfm(conn_hdl, p_param->handle);

        type = BLE_GATTC_EVENT_HDL_VAL_IND;
        p_cb_evt = r_ble_gtl_cb_evt_allocate(type, BLE_SUCCESS, sizeof(st_ble_gattc_ind_evt_t));

        p_evt_data    = r_ble_gtl_malloc(p_param->length);

        if ((NULL != p_cb_evt) && (NULL != p_evt_data))
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_evt_ind_param = p_cb_evt->data.gattc.p_param;
            p_evt_ind_param->data.attr_hdl = p_param->handle;
            p_evt_ind_param->data.value.p_value = p_evt_data;
            p_evt_ind_param->data.value.value_len = p_param->length;
            memcpy (p_evt_data, p_param->value, p_param->length);

        }
        else
        {
            r_ble_gtl_free(p_evt_data);
            r_ble_gtl_cb_evt_free(p_cb_evt);
        }
    }
    else
    {
        return NULL;
    }

    return p_cb_evt;
}


/*******************************************************************************************************************//**
 *  Handle GATT client MTU changed indication message. Message does not generate callback events.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GATT client MTU changed indication message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_mtu_changed_ind_handler(uint16_t conn_hdl, 
                                                                    r_ble_gtl_gattc_mtu_changed_ind_t * p_param)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);

    g_dev_params.mtu_size = p_param->mtu;

    /* This message is just consumed internally, no callback event generated for the application */
    return NULL;
}

/*******************************************************************************************************************//**
 *  Handle GATT client REQUEST ATT INFO indication message.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GATT information message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gattc_att_info_req_ind_handler(uint16_t conn_hdl, r_ble_gtl_gattc_att_info_req_t * p_param)
{
    r_ble_gtl_cb_evt_t *p_cb_evt = NULL;
    st_ble_gattc_att_info_req_ind_evt_t *p_att_info = NULL;
    ble_status_t status;

    uint16_t index = p_param->handle - (uint16_t)g_dev_params.att_hndl_offset;

    status = r_ble_gtl_gattc_send_att_info_cfm(conn_hdl, p_param->handle, qe_ble_profile[index].value_length, 0);

    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GATTC_EVENT_ATT_INFO_REQ_IND, status, sizeof(st_ble_gattc_att_info_req_ind_evt_t));

    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate (BLE_GATTC_EVENT_ATT_INFO_REQ_IND, status,
                                              sizeof(st_ble_gattc_att_info_req_ind_evt_t));

        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_att_info = (st_ble_gattc_att_info_req_ind_evt_t*) p_cb_evt->data.gattc.p_param;
            p_att_info->value_hdl = p_param->handle;
        }
    }

    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Request DA14xxx device generates a random number
 *
 * @param[in]  p_rand_nb                Pointer to structure in which generated number should be stored.
 *
 * @retval BLE_SUCCESS                  Random number generated.
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Module is busy processing another request.
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_gen_rand_nb(r_ble_gtl_gapm_gen_rand_nb_ind_t * p_rand_nb)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapm_send_gen_rand_nb_cmd();
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPM_GEN_RAND_NB_IND,
                                                     (uint8_t *)p_rand_nb,
                                                     sizeof(r_ble_gtl_gapm_gen_rand_nb_ind_t),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT,
                                                             R_BLE_GTL_GAPM_OP_GEN_RAND_NB,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Read Bluetooth Device Address from DA14xxx
 *
 * @param[in]  p_bd_addr                Pointer to data structure in which BD address should be written once read.
 *
 * @retval BLE_SUCCESS                  BD address successfully read from DA14xxx.
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Module is busy processing another request.
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_get_bd_addr(r_ble_gtl_gapm_dev_bdaddr_ind_t * p_bd_addr)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapm_send_get_dev_info_cmd(R_BLE_GTL_GAPM_OP_GET_DEV_BDADDR);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPM_DEV_BDADDR_IND,
                                                     (uint8_t *)p_bd_addr,
                                                     sizeof(r_ble_gtl_gapm_dev_bdaddr_ind_t),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT,
                                                             R_BLE_GTL_GAPM_OP_GET_DEV_BDADDR,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Read device version information from DA14xxx.
 *
 * @param[in]  p_version                Pointer to data structure into which version information should be written.
 *
 * @retval BLE_SUCCESS                  Version information successfully read from DA14xxx.
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Module is busy processing another request.
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_get_get_dev_version(r_ble_gtl_gapm_dev_version_ind_t * p_version)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapm_send_get_dev_info_cmd(R_BLE_GTL_GAPM_OP_GET_DEV_VERSION);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPM_DEV_VERSION_IND,
                                                     (uint8_t *)p_version,
                                                     sizeof(r_ble_gtl_gapm_dev_version_ind_t),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT,
                                                             R_BLE_GTL_GAPM_OP_GET_DEV_VERSION,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Perform a software reset of the DA14xxx.
 *
 * @retval BLE_SUCCESS                  Reset successful.
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Module is busy processing another request.
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_reset(void)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapm_send_reset_cmd();
        if (BLE_SUCCESS == status)
        {
            /* Wait for reset complete indication */
            status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT, R_BLE_GTL_GAPM_OP_RESET, 
                                                                    0, R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send start advertising command to the DA14xxx. Advertising parameters are configured via calls to
 *  R_BLE_GTL_GAP_SetAdvParam and R_BLE_GTL_GAP_SetAdvSresData functions.
 *
 * @retval BLE_SUCCESS                  Advertising started
 * @retval BLE_ERR_INVALID_ARG          Advertising parameters invalid
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_send_start_adv_cmd(void)
{
    ble_status_t                           status;
    r_ble_gtl_gapm_start_advertise_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gapm_start_advertise_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_START_ADVERTISE_CMD,
                                                                    R_BLE_GTL_TASK_ID_GAPM,
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof (r_ble_gtl_gapm_start_advertise_cmd_t));
    if (NULL != p_cmd)
    {
        status = BLE_SUCCESS;

        p_cmd->info.host.mode = R_BLE_GTL_GAP_GEN_DISCOVERABLE;

        /* Convert advertising packet type */
        if (BLE_GAP_LEGACY_PROP_ADV_NONCONN_IND == g_dev_params.adv_param.param.adv_prop_type)
        {
            p_cmd->op.code = R_BLE_GTL_GAPM_OP_ADV_NON_CONN;
        }
        else if (BLE_GAP_LEGACY_PROP_ADV_IND == g_dev_params.adv_param.param.adv_prop_type)
        {
            p_cmd->op.code = R_BLE_GTL_GAPM_OP_ADV_UNDIRECT;
        }
        else if (BLE_GAP_LEGACY_PROP_ADV_HDC_DIRECT_IND == g_dev_params.adv_param.param.adv_prop_type)
        {
            p_cmd->op.code = R_BLE_GTL_GAPM_OP_ADV_DIRECT;
        }
        else if (BLE_GAP_LEGACY_PROP_ADV_DIRECT_IND == g_dev_params.adv_param.param.adv_prop_type)
        {
            p_cmd->op.code = R_BLE_GTL_GAPM_OP_ADV_DIRECT_LDC;
        }
        else
        {
            r_ble_gtl_free(p_cmd);
            status = BLE_ERR_INVALID_ARG;
        }

        if (BLE_SUCCESS == status)
        {
            /* Mode is required when calling advertising stop so store here for possible use in future */
            g_dev_params.adv_mode              = p_cmd->op.code;

            p_cmd->intv_min                    = (uint16_t)g_dev_params.adv_param.param.adv_intv_min;
            p_cmd->intv_max                    = (uint16_t)g_dev_params.adv_param.param.adv_intv_max;
            p_cmd->channel_map                 = g_dev_params.adv_param.param.adv_ch_map;
            p_cmd->info.host.adv_filt_policy   = g_dev_params.adv_param.param.filter_policy;
            p_cmd->info.host.adv_data_len      = g_dev_params.adv_data.length;
            p_cmd->info.host.scan_rsp_data_len = g_dev_params.scan_rsp_data.length;

            /* Add advertising payload data */
            if (0 < g_dev_params.adv_data.length)
            {
                memcpy(&p_cmd->info.host.adv_data[0], &g_dev_params.adv_data.data[0], g_dev_params.adv_data.length);
            }

            /* Add scan response data */
            if (0 < g_dev_params.scan_rsp_data.length)
            {
                memcpy(&p_cmd->info.host.scan_rsp_data[0], &g_dev_params.scan_rsp_data.data[0], 
                                                                g_dev_params.scan_rsp_data.length);
            }

            status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
        }
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send get device information command to the DA14xxx.
 *
 * @param[in]  operation                Type of information to read (R_BLE_GTL_GAPM_OP_GET_DEV_VERSION or
 *                                      R_BLE_GTL_GAPM_OP_GET_DEV_BDADDR)
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_send_get_dev_info_cmd(uint8_t operation)
{
    ble_status_t                        status;
    r_ble_gtl_gapm_get_dev_info_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gapm_get_dev_info_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_GET_DEV_INFO_CMD,
                                                                        R_BLE_GTL_TASK_ID_GAPM,
                                                                        R_BLE_GTL_TASK_ID_GTL,
                                                                        sizeof(r_ble_gtl_gapm_get_dev_info_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->op = operation;
        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send reset command to the DA14xxx.
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_send_reset_cmd(void)
{
    ble_status_t                 status = BLE_ERR_MEM_ALLOC_FAILED;
    r_ble_gtl_gapm_reset_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gapm_reset_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_RESET_CMD,
                                                                 R_BLE_GTL_TASK_ID_GAPM,
                                                                 R_BLE_GTL_TASK_ID_GTL,
                                                                 sizeof(r_ble_gtl_gapm_reset_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->op = R_BLE_GTL_GAPM_OP_RESET;
        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send cancel operation command to the DA14xxx.
 *
 * @param[in]  operation                Operation to be cancelled
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_send_cancel_cmd(uint8_t operation)
{
    ble_status_t                  status = BLE_ERR_ALREADY_IN_PROGRESS;
    r_ble_gtl_gapm_cancel_cmd_t * p_cmd;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        p_cmd = (r_ble_gtl_gapm_cancel_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_CANCEL_CMD,
                                                                      R_BLE_GTL_TASK_ID_GAPM,
                                                                      R_BLE_GTL_TASK_ID_GTL,
                                                                      sizeof (r_ble_gtl_gapm_cancel_cmd_t));
        if (NULL != p_cmd)
        {
            p_cmd->op = R_BLE_GTL_GAPM_OP_CANCEL;
            status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);

            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT,
                                                             operation,
                                                             R_BLE_GTL_GAP_ERR_CANCELED,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
            }
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }

        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send generate random number command to the DA14xxx.
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_send_gen_rand_nb_cmd(void)
{
    ble_status_t                       status = BLE_ERR_MEM_ALLOC_FAILED;
    r_ble_gtl_gapm_gen_rand_nb_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gapm_gen_rand_nb_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_GEN_RAND_NB_CMD,
                                                                       R_BLE_GTL_TASK_ID_GAPM,
                                                                       R_BLE_GTL_TASK_ID_GTL,
                                                                       sizeof(r_ble_gtl_gapm_gen_rand_nb_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->operation = R_BLE_GTL_GAPM_OP_GEN_RAND_NB;

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }

    return status;
}

#define R_BLE_GTL_ATT_CFG_GAPM_NAME_PERM_WRITE_DISABLE 0x00
#define R_BLE_GTL_ATT_CFG_GAPM_NAME_PERM_WRITE_ENABLE  0x01

#define R_BLE_GTL_ATT_CFG_GAPM_APP_PERM_WRITE_DISABLE 0x00
#define R_BLE_GTL_ATT_CFG_GAPM_APP_PERM_WRITE_ENABLE  0x04

#define R_BLE_GTL_ATT_CFG_GAPM_SLV_PREF_CON_PAR_PRESENT  0x10
#define R_BLE_GTL_ATT_CFG_GAPM_SERVICE_CHANGED_PRESENT  0x20


#define ENABLE_ALL_FLAGS (R_BLE_GTL_ATT_CFG_GAPM_NAME_PERM_WRITE_ENABLE | R_BLE_GTL_ATT_CFG_GAPM_APP_PERM_WRITE_ENABLE)
/*******************************************************************************************************************//**
 *  Send configure device command to the DA14xxx. Configuration information is taken from a global data structure.
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_send_dev_config_cmd(void)
{
    ble_status_t                          status = BLE_ERR_MEM_ALLOC_FAILED;
    r_ble_gtl_gapm_set_dev_config_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gapm_set_dev_config_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_SET_DEV_CONFIG_CMD,
                                                                          R_BLE_GTL_TASK_ID_GAPM,
                                                                          R_BLE_GTL_TASK_ID_GTL,
                                                                          sizeof(r_ble_gtl_gapm_set_dev_config_cmd_t));
    if (NULL != p_cmd)
    {
        status = BLE_SUCCESS;

        p_cmd->operation      = R_BLE_GTL_GAPM_OP_SET_DEV_CONFIG;
        p_cmd->max_mtu        = g_dev_params.mtu_size;
        p_cmd->max_txoctets   = R_BLE_GTL_DATA_LEN_TX_OCTETS_MAX;
        p_cmd->max_txtime     = R_BLE_GTL_DATA_LEN_TX_TIME_MAX;
        p_cmd->gap_start_hdl  = 0x0000; /* Let DA1453X selects its own handles */
        p_cmd->gatt_start_hdl = 0x0000;
        p_cmd->att_cfg_       = 0x0000; /* Not used, must be set to zero */
        p_cmd->max_mtu        = BLE_ABS_CFG_GATT_MTU_SIZE;
        p_cmd->max_mps        = 0;
        p_cmd->role           = BLE_CFG_DEVICE_ROLE;
        p_cmd->att_cfg        = 0x00;
        //p_cmd->att_cfg        = 0x20; //0x00; /* Don't allow writes to device name or appearance */
        //p_cmd->att_cfg         = ENABLE_ALL_FLAGS;


        if (slv_pref_con_par_index > 0)
        {
            p_cmd->att_cfg |= R_BLE_GTL_ATT_CFG_GAPM_SLV_PREF_CON_PAR_PRESENT;
        }

        if (service_changed_index > 0)
        {
            p_cmd->att_cfg |= R_BLE_GTL_ATT_CFG_GAPM_SERVICE_CHANGED_PRESENT;
        }

        if(device_name_index > 0)
        {
            if(qe_ble_profile[device_name_index].permissions & 0x2)
            {
                p_cmd->att_cfg |= R_BLE_GTL_ATT_CFG_GAPM_NAME_PERM_WRITE_ENABLE;
            }
        }

        if(device_appearance_index > 0)
        {
            if(qe_ble_profile[device_appearance_index].permissions & 0x2)
            {
                p_cmd->att_cfg |= R_BLE_GTL_ATT_CFG_GAPM_APP_PERM_WRITE_ENABLE;
            }
        }

        /* Privacy features not used at present */
        p_cmd->renew_dur      = 0;
        p_cmd->priv1_2        = 0x00;
        memset(&p_cmd->irk.key[0], 0, R_BLE_GTL_KEY_LEN);

        p_cmd->addr_type = g_dev_params.dev_addr.type;
        if (BLE_GAP_ADDR_RAND == p_cmd->addr_type)
        {
            memcpy(&p_cmd->addr.addr[0], &g_dev_params.dev_addr.addr[0], BLE_BD_ADDR_LEN);
            /* The first two bits of a non-public (random) address must be binary ones */
            p_cmd->addr.addr[5] |= R_BLE_GTL_PUBLIC_BD_ADDR_MASK;

        }
        else if (BLE_GAP_ADDR_PUBLIC == p_cmd->addr_type)
        {
            /* If address type is public then the module will use the public BD
               address that has been programmed into it during manufacture. */
            ;
        }
        else
        {
            /* Unsupported address type */
            r_ble_gtl_free(p_cmd);
            status = BLE_ERR_INVALID_ARG;
        }

        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Get version information from peer device.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  p_version                Pointer to data structure into which peer version information should be written.
 *
 * @retval BLE_SUCCESS                  Version information read successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_get_peer_version(uint16_t conn_hdl, r_ble_gtl_gapc_peer_version_ind_t * p_version)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapc_send_get_info_cmd(conn_hdl, R_BLE_GTL_GAPC_OP_GET_PEER_VERSION);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPC_PEER_VERSION_IND,
                                                     (uint8_t *)p_version,
                                                     sizeof(r_ble_gtl_gapc_peer_version_ind_t),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPC_CMP_EVT,
                                                             R_BLE_GTL_GAPC_OP_GET_PEER_VERSION,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Get features supported by peer device.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  p_features               Pointer to data structure into which peer features should be written.
 *
 * @retval BLE_SUCCESS                  Feature information read successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_get_peer_features(uint16_t conn_hdl, r_ble_gtl_gapc_peer_features_ind_t * p_features)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapc_send_get_info_cmd(conn_hdl, R_BLE_GTL_GAPC_OP_GET_PEER_FEATURES);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPC_PEER_FEATURES_IND,
                                                     (uint8_t *)p_features,
                                                     sizeof(r_ble_gtl_gapc_peer_features_ind_t),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPC_CMP_EVT,
                                                             R_BLE_GTL_GAPC_OP_GET_PEER_FEATURES,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Get connection received signal strength indiciation (RSSI)
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  p_param                  Pointer to data structure into which RSSI information should be written.
 *
 * @retval BLE_SUCCESS                  RSSI read successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_get_con_rssi(uint16_t conn_hdl, r_ble_gtl_gapc_con_rssi_ind_t * p_param)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapc_send_get_info_cmd(conn_hdl, R_BLE_GTL_GAPC_OP_GET_CON_RSSI);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPC_CON_RSSI_IND,
                                                     (uint8_t *)p_param,
                                                     sizeof(r_ble_gtl_gapc_con_rssi_ind_t),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPC_CMP_EVT,
                                                             R_BLE_GTL_GAPC_OP_GET_CON_RSSI,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Get map of used/unused channels
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  p_param                  Pointer to data structure into which channel map should be written.
 *
 * @retval BLE_SUCCESS                  Channel map read successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_get_channel_map(uint16_t conn_hdl, r_ble_gtl_gapc_con_channel_map_ind_t * p_param)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapc_send_get_info_cmd(conn_hdl, R_BLE_GTL_GAPC_OP_GET_CON_CHANNEL_MAP);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPC_CON_CHANNEL_MAP_IND,
                                                     (uint8_t *)p_param,
                                                     sizeof(r_ble_gtl_gapc_con_channel_map_ind_t),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPC_CMP_EVT,
                                                             R_BLE_GTL_GAPC_OP_GET_CON_CHANNEL_MAP,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Set packet size parameters, may generated a callback event.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  tx_octets                Number of octets that can be transmitted
 * @param[in]  tx_time                  Maximum transmit time for tx_octets
 *
 * @retval BLE_SUCCESS                  Packet size set successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_set_le_pkt_size(uint16_t conn_hdl, uint16_t tx_octets, uint16_t tx_time)
{
    ble_status_t   status   = BLE_ERR_ALREADY_IN_PROGRESS;
    uint8_t      * p_msg    = NULL;
    bool           complete = false;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapc_send_le_pkt_size_cmd(conn_hdl, tx_octets, tx_time);
        if (BLE_SUCCESS == status)
        {
            do
            {
                status = r_ble_gtl_msg_receive(&p_msg, R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
                if (BLE_SUCCESS == status)
                {
                    uint16_t msg_id = ((r_ble_gtl_msg_hdr_t *)p_msg)->msg_id;

                    if (R_BLE_GTL_GAPC_LE_PKT_SIZE_IND == msg_id)
                    {
                        /* Parameters are not passed back to the caller */
                        r_ble_gtl_msg_buffer_free(p_msg);
                    }
                    else if (R_BLE_GTL_GAPC_CMP_EVT == msg_id)
                    {
                        r_ble_gtl_gapm_cmp_evt_t * p_cmp_param = 
                                                (r_ble_gtl_gapm_cmp_evt_t *)&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];
                        if ((R_BLE_GTL_GAPC_OP_SET_LE_PKT_SIZE != p_cmp_param->operation) ||
                            (R_BLE_GTL_GAP_ERR_NO_ERROR != p_cmp_param->status))
                        {
                            status = BLE_ERR_UNSUPPORTED;
                        }
                        complete = true;
                        r_ble_gtl_msg_buffer_free(p_msg);
                    }
                    else
                    {
                        /* Message received but not what we expected, queue for processing 
                        next time BLE execute is called */
                        r_ble_gtl_msg_pend_queue_add(&p_msg);
                    }
                }
            }
            while ((false == complete) && (BLE_SUCCESS == status));
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Update connection parameters.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  p_conn_update_param      Pointer to new connection parameters
 * @param[in]  p_param_update_ind       Pointer to response
 *
 * @retval BLE_SUCCESS                  Packet size set successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_param_update(uint16_t conn_hdl, st_ble_gap_conn_param_t * p_conn_update_param, 
                                                r_ble_gtl_gapc_param_update_ind_t * p_param_update_ind)
{
    ble_status_t                        status   = BLE_ERR_MEM_ALLOC_FAILED;
    uint8_t                           * p_msg    = NULL;
    bool                                complete = false;
    r_ble_gtl_gapc_param_update_ind_t * p_ind_param;
    r_ble_gtl_gapm_cmp_evt_t          * p_cmp_param;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gapc_send_param_update_cmd(conn_hdl, p_conn_update_param);
        if (BLE_SUCCESS == status)
        {
            do
            {
                status = r_ble_gtl_msg_receive(&p_msg, R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
                if (BLE_SUCCESS == status)
                {
                    uint16_t msg_id = ((r_ble_gtl_msg_hdr_t *)p_msg)->msg_id;

                    if (R_BLE_GTL_GAPC_PARAM_UPDATED_IND == msg_id)
                    {
                        p_ind_param = (r_ble_gtl_gapc_param_update_ind_t *)&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];
                        p_param_update_ind->intv     = p_ind_param->intv;
                        p_param_update_ind->latency  = p_ind_param->latency;
                        p_param_update_ind->timeout  = p_ind_param->timeout;
                        complete = true;

                        r_ble_gtl_msg_buffer_free(p_msg);
                    }
                    else if (R_BLE_GTL_GAPC_CMP_EVT == msg_id)
                    {
                        p_cmp_param = (r_ble_gtl_gapm_cmp_evt_t *)&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];
                        if ((R_BLE_GTL_GAPC_OP_UPDATE_PARAMS != p_cmp_param->operation) ||
                            (R_BLE_GTL_GAP_ERR_NO_ERROR != p_cmp_param->status))
                        {
                            status = BLE_ERR_HC_UNACCEPTEBALE_CONN_INTERVAL;
                        }
                        r_ble_gtl_msg_buffer_free(p_msg);
                    }
                    else
                    {
                        /* Message received but not what we expected, queue for processing next time 
                        BLE execute is called */
                        r_ble_gtl_msg_pend_queue_add(&p_msg);
                    }
                }
            }
            while ((false == complete) && (BLE_SUCCESS == status));
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Disconnect from central device
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  reason                   Reason for disconnection
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_disconnect(uint16_t conn_hdl, uint8_t reason)
{
    ble_status_t                      status = BLE_ERR_ALREADY_IN_PROGRESS;
    r_ble_gtl_gapc_disconnect_cmd_t * p_cmd;
    r_ble_gtl_gapc_disconnect_ind_t   disconn_ind;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        p_cmd = (r_ble_gtl_gapc_disconnect_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_DISCONNECT_CMD,
                                                                R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                R_BLE_GTL_TASK_ID_GTL,
                                                                sizeof (r_ble_gtl_gapc_disconnect_cmd_t));
        if (NULL != p_cmd)
        {
            p_cmd->op     = R_BLE_GTL_GAPC_OP_DISCONNECT;
            p_cmd->reason = reason;

            status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPC_DISCONNECT_IND,
                                                         (uint8_t *)&disconn_ind,
                                                         sizeof(r_ble_gtl_gapc_disconnect_ind_t),
                                                         R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            }
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send connection parameter update command to the DA14xxx.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.

 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_send_param_update_cmd(uint16_t conn_hdl, st_ble_gap_conn_param_t * p_conn_updt_param)
{
    ble_status_t                        status;
    r_ble_gtl_gapc_param_update_cmd_t * p_cmd = NULL;

    p_cmd = (r_ble_gtl_gapc_param_update_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_PARAM_UPDATE_CMD,
                                                                R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                R_BLE_GTL_TASK_ID_GTL,
                                                                sizeof (r_ble_gtl_gapc_param_update_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->op         = R_BLE_GTL_GAPC_OP_UPDATE_PARAMS;
        p_cmd->pkt_id     = 0; /* Unused, always set to zero */
        p_cmd->intv_min   = p_conn_updt_param->conn_intv_min;
        p_cmd->intv_max   = p_conn_updt_param->conn_intv_max;
        p_cmd->latency    = p_conn_updt_param->conn_latency;
        p_cmd->timeout    = p_conn_updt_param->sup_to;
        p_cmd->ce_len_min = p_conn_updt_param->min_ce_length;
        p_cmd->ce_len_max = p_conn_updt_param->max_ce_length;

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}


/*******************************************************************************************************************//**
 *  Send connection parameter update confirmation command to the DA14xxx.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  accept                   Accept (1) or Reject (0) connection parameters
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_send_param_update_cfm(uint16_t conn_hdl, uint8_t accept)
{
    ble_status_t                        status;
    r_ble_gtl_gapc_param_update_cfm_t * p_cmd;

    p_cmd = (r_ble_gtl_gapc_param_update_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_PARAM_UPDATE_CFM,
                                                                R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                R_BLE_GTL_TASK_ID_GTL,
                                                                sizeof (r_ble_gtl_gapc_param_update_cfm_t));
    if (NULL != p_cmd)
    {
        p_cmd->accept     = accept;
        p_cmd->ce_len_min = 0x0000;
        p_cmd->ce_len_min = UINT16_MAX;
        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send set packet size command to the DA14xxx.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  tx_octets                Number of octets that can be transmitted
 * @param[in]  tx_time                  Maximum transmit time for tx_octets
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_send_le_pkt_size_cmd(uint16_t conn_hdl, uint16_t tx_octets, uint16_t tx_time)
{
    ble_status_t                           status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_gapc_set_le_pkt_size_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gapc_set_le_pkt_size_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_SET_LE_PKT_SIZE_CMD,
                                                                R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                R_BLE_GTL_TASK_ID_GTL,
                                                                sizeof (r_ble_gtl_gapc_set_le_pkt_size_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->op = R_BLE_GTL_GAPC_OP_SET_LE_PKT_SIZE;
        p_cmd->max_tx_octets = tx_octets;
        p_cmd->max_tx_time = tx_time;

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send get device information command to the DA14xxx.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  operation                Type of information to read
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_send_get_info_cmd(uint16_t conn_hdl, uint8_t operation)
{
    ble_status_t                    status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_gapc_get_info_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gapc_get_info_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_GET_INFO_CMD,
                                                                R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                R_BLE_GTL_TASK_ID_GTL,
                                                                sizeof (r_ble_gtl_gapc_get_info_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->op = operation;

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Add GATT service based on supplied parameters
 *
 * @param[in]  perm                     Service permissions
 * @param[in]  nbr_att                  Number of service attributes
 * @param[in]  p_uuid                   Pointer to service UUID (can be 16-bit or 128-bit)
 * @param[in]  p_att_descs              Pointer to table of descriptors for each attribute
 * @param[in]  p_start_hdl              Pointer into which start handle (generated by DA14xxx device) should be written
 *
 * @retval BLE_SUCCESS                  Service added successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_gattm_add_service(uint8_t perm, uint8_t nbr_att, r_ble_gtl_uuid_t * p_uuid, 
                                         r_ble_gtl_gattm_att_desc_t * p_att_descs, uint16_t * p_start_hdl)
{
    ble_status_t                    status = BLE_ERR_ALREADY_IN_PROGRESS;
    r_ble_gtl_gattm_add_svc_cmd_t * p_cmd;
    r_ble_gtl_gattm_add_svc_rsp_t   add_svc_rsp;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        p_cmd = (r_ble_gtl_gattm_add_svc_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTM_ADD_SVC_REQ,
                R_BLE_GTL_TASK_ID_GATTM,
                R_BLE_GTL_TASK_ID_GTL,
                (uint16_t)(sizeof(r_ble_gtl_gattm_add_svc_cmd_t) + (nbr_att * sizeof(r_ble_gtl_gattm_att_desc_t))));
        if (NULL != p_cmd)
        {
            p_cmd->start_hdl = 0x0000; /* Let the DA1453x automatically assign start handle */
            p_cmd->task_id   = R_BLE_GTL_TASK_ID_GTL;
            p_cmd->perm      = perm;
            p_cmd->nb_att    = nbr_att;
            memset(&p_cmd->uuid[0], 0, BLE_GATT_128_BIT_UUID_SIZE);
            memcpy(&p_cmd->uuid[0], &p_uuid->value, p_uuid->length);
            memcpy(&p_cmd->atts, p_att_descs, nbr_att * sizeof(r_ble_gtl_gattm_att_desc_t));

            status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GATTM_ADD_SVC_RSP,
                                                         (uint8_t *)&add_svc_rsp,
                                                         sizeof(r_ble_gtl_gattm_add_svc_rsp_t),
                                                         R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
                if (BLE_SUCCESS == status)
                {
                    if (R_BLE_GTL_GAP_ERR_NO_ERROR == add_svc_rsp.status)
                    {
                        /* Return allocated handle as this will be required for GATT operations on this service */
                        *p_start_hdl = add_svc_rsp.start_hdl;
                    }
                    else
                    {
                        status = BLE_ERR_GATT_REQUEST_NOT_SUPPORTED;
                    }
                }
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Read an attribute value from DA14xxx database
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  attr_hdl                 Handle of attribute to be read
 * @param[in]  p_value                  Pointer to data structure into which read value should be written
 *
 * @retval BLE_SUCCESS                  Value read successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattm_get_att_value(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);

    ble_status_t                          status = BLE_ERR_ALREADY_IN_PROGRESS;
    r_ble_gtl_gattm_att_get_value_req_t * p_cmd;
    r_ble_gtl_gattm_att_get_value_rsp_t * p_rsp;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        p_cmd = (r_ble_gtl_gattm_att_get_value_req_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTM_ATT_GET_VALUE_REQ,
                                                                    R_BLE_GTL_TASK_ID_GATTM,
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof (r_ble_gtl_gattm_att_get_value_req_t));
        if (NULL != p_cmd)
        {
            p_cmd->handle = attr_hdl;

            status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            if (BLE_SUCCESS == status)
            {
                p_rsp = r_ble_gtl_malloc(sizeof(r_ble_gtl_gattm_att_get_value_rsp_t) + p_value->value_len);

                status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GATTM_ATT_GET_VALUE_RSP,
                                                    (uint8_t *)p_rsp,
                                                    sizeof(r_ble_gtl_gattm_att_get_value_rsp_t) + p_value->value_len,
                                                    R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
                if (BLE_SUCCESS == status)
                {
                    if (R_BLE_GTL_GAP_ERR_NO_ERROR == p_rsp->status)
                    {
                        memcpy(p_value->p_value, p_rsp->value, p_value->value_len);
                    }
                    else
                    {
                        status = BLE_ERR_GATT_READ_NOT_PERMITTED;
                    }
                }

                r_ble_gtl_free(p_rsp);
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Write an attribute value from DA14xxx database
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  attr_hdl                 Handle of attribute to be read
 * @param[in]  p_value                  Pointer to data structure containing value to write
 *
 * @retval BLE_SUCCESS                  Value written successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattm_set_att_value(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gattm_set_att_value_int(conn_hdl, attr_hdl, p_value);

        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Provide an RI vaule after GATTC_READ_REQ_IND
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  attr_hdl                 Handle of attribute to be read
 * @param[in]  p_value                  Pointer to data structure containing value to write
 *
 * @retval BLE_SUCCESS                  Value written successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattm_read_cfm_value(uint16_t conn_hdl, uint16_t attr_hdl, st_ble_gatt_value_t * p_value)
{
    uint8_t status = R_BLE_GTL_GAP_ERR_NO_ERROR;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        
         (void)r_ble_gtl_gattc_send_read_cfm(conn_hdl, status, attr_hdl, p_value->value_len, p_value->p_value);

        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}


/*******************************************************************************************************************//**
 *  Write an attribute value from DA14xxx database
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  attr_hdl                 Handle of attribute to be read
 * @param[in]  p_value                  Pointer to data structure containing value to write
 *
 * @retval BLE_SUCCESS                  Value written successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattm_set_att_value_int(uint16_t conn_hdl, uint16_t attr_hdl, 
                                                      st_ble_gatt_value_t * p_value)
{
    FSP_PARAMETER_NOT_USED(conn_hdl);

    ble_status_t                          status = BLE_ERR_MEM_ALLOC_FAILED;
    r_ble_gtl_gattm_att_set_value_req_t * p_cmd;
    r_ble_gtl_gattm_att_set_value_rsp_t   rsp;

    p_cmd = (r_ble_gtl_gattm_att_set_value_req_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTM_ATT_SET_VALUE_REQ,
                                                R_BLE_GTL_TASK_ID_GATTM,
                                                R_BLE_GTL_TASK_ID_GTL,
                                                sizeof (r_ble_gtl_gattm_att_set_value_req_t) + p_value->value_len);
    if (NULL != p_cmd)
    {
        p_cmd->handle = attr_hdl;
        p_cmd->length = p_value->value_len;
        memcpy(p_cmd->value, p_value->p_value, p_value->value_len);

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GATTM_ATT_SET_VALUE_RSP,
                                                     (uint8_t *)&rsp,
                                                     sizeof(r_ble_gtl_gattm_att_set_value_rsp_t),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                if (0 != rsp.status)
                {
                    status = BLE_ERR_GATT_WRITE_NOT_PERMITTED;
                }
            }
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Write value to peer device attribute
 *
 * @param[in]  operation                Type of write operation
 * @param[in]  conn_hdl                 Handle of connection on which request should be made
 * @param[in]  att_hdl                  Handle of attribute to write
 * @param[in]  p_value                  Pointer to value to be written
 * @param[in]  length                   Length of value to be written
 * @param[in]  offset                   Offset (within value) to be written
 *
 * @retval BLE_SUCCESS                  Value written successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_write(uint8_t operation, uint8_t auto_exec, uint16_t conn_hdl, uint16_t att_hdl,
                                          uint8_t * p_value, uint16_t length, uint16_t offset)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gattc_send_write_cmd(operation, auto_exec, conn_hdl, att_hdl, p_value, length, offset);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GATTC_CMP_EVT,
                                                         operation,
                                                         R_BLE_GTL_GAP_ERR_ANY,
                                                         R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Exchange MTU with peer device.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made
 * @param[in]  p_mtu_rsp                Pointer into which new MTU is written

 * @retval BLE_SUCCESS                  Value written successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_exch_mtu(uint16_t conn_hdl, uint16_t * p_mtu_rsp)
{
    ble_status_t                      status = BLE_ERR_ALREADY_IN_PROGRESS;
    r_ble_gtl_gattc_mtu_changed_ind_t mtu_changed_ind;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gattc_send_exch_mtu_cmd(conn_hdl);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GATTC_MTU_CHANGED_IND,
                                                     (uint8_t *)&mtu_changed_ind,
                                                     sizeof(r_ble_gtl_gattc_mtu_changed_ind_t),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);

            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GATTC_CMP_EVT,
                                                             R_BLE_GTL_GATTC_OP_MTU_EXCH,
                                                             R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                             R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
                if (BLE_SUCCESS == status)
                {
                    *p_mtu_rsp = mtu_changed_ind.mtu;
                }
            }
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send execute write request to peer device
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made
 * @param[in]  execute                  Execute (1) or cancel (0) the write operation

 * @retval BLE_SUCCESS                  Value written successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_write_execute(uint16_t conn_hdl, uint8_t execute)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gattc_send_write_execute_cmd(conn_hdl, execute);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GATTC_CMP_EVT,
                                                         R_BLE_GTL_GATTC_OP_EXEC_WRITE,
                                                         R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                         R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Notify client of change to attribute value.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made
 * @param[in]  attr_hdl                 Handle of attribute
 * @param[in]  p_value                  Pointer to value that has changed
 * @param[in]  length                   Length of value
 *
 * @retval BLE_SUCCESS                  Notify successful
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_notify(uint16_t conn_hdl, uint16_t attr_hdl, uint8_t * p_value, uint16_t length)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gattc_send_evt_cmd(R_BLE_GTL_GATTC_OP_NOTIFY, conn_hdl, attr_hdl, p_value, length);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GATTC_CMP_EVT,
                                                         R_BLE_GTL_GATTC_OP_NOTIFY,
                                                         R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                         R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

static ble_status_t r_ble_gtl_gattc_send_service_changed(uint16_t conn_hdl, uint16_t start_handle, uint16_t end_handle)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        r_ble_gtl_gattc_send_svc_changed_cmd_t * p_cmd;

        p_cmd = (r_ble_gtl_gattc_send_svc_changed_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_SEND_SVC_CHANGED_CMD,
                                                                                 R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                                                 R_BLE_GTL_TASK_ID_GTL,
                                                                                 sizeof (r_ble_gtl_gattc_send_svc_changed_cmd_t));
        if (NULL != p_cmd)
        {
           p_cmd->operation = R_BLE_GTL_GATTC_OP_SVC_CHANGED;
           p_cmd->seq_num   = 0x0000;
           p_cmd->svc_shdl = start_handle;
           p_cmd->svc_ehdl = end_handle;
           status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
        }
        else
        {
           status = BLE_ERR_MEM_ALLOC_FAILED;
        }

        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}


/*******************************************************************************************************************//**
 *  Indicate to client a change to attribute value.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made
 * @param[in]  attr_hdl                 Handle of attribute
 * @param[in]  p_value                  Pointer to value that has changed
 * @param[in]  length                   Length of value
 *
 * @retval BLE_SUCCESS                  Indicate successful
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_indicate(uint16_t conn_hdl, uint16_t attr_hdl, uint8_t * p_value, uint16_t length)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gattc_send_evt_cmd(R_BLE_GTL_GATTC_OP_INDICATE, conn_hdl, attr_hdl, p_value, length);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GATTC_CMP_EVT,
                                                         R_BLE_GTL_GATTC_OP_INDICATE,
                                                         R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                         R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Dsicover peer services/characteristics
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made
 * @param[in]  operation                Type of discovery to perform
 * @param[in]  start_hdl                Start discovery at this attribute handle
 * @param[in]  end_hdl                  End discovery at this attribute handle
 * @param[in]  p_uuid                   Pointer to service UUID
 * @param[in]  p_disc_evts              Type of events to generate when services are discovered
 *
 * @retval BLE_SUCCESS                  Discovery successful
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as command already in progress
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_discover(uint16_t conn_hdl, uint8_t operation, uint16_t start_hdl, uint16_t end_hdl,
                                             r_ble_gtl_uuid_t * p_uuid, r_ble_gtl_disc_events_t * p_disc_evts)
{
    uint8_t                         * p_msg    = NULL;
    bool                              complete = false;
    ble_status_t                      status   = BLE_ERR_ALREADY_IN_PROGRESS;
    r_ble_gtl_gattc_disc_svc_ind_t  * p_disc_svc_ind;
    r_ble_gtl_gattc_disc_char_ind_t * p_disc_char_ind;
    r_ble_gtl_gattc_disc_char_desc_ind_t * p_disc_desc_ind;
    r_ble_gtl_gattc_disc_svc_incl_ind_t *p_disc_svc_incl_ind;
    r_ble_gtl_cb_evt_t              * p_cb_evt;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_gattc_send_disc_cmd(conn_hdl, operation, 0x000, start_hdl, end_hdl, p_uuid);
        if (BLE_SUCCESS == status)
        {
            do
            {
                status = r_ble_gtl_msg_receive(&p_msg, R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
                if (BLE_SUCCESS == status)
                {
                    uint16_t msg_id = ((r_ble_gtl_msg_hdr_t *)p_msg)->msg_id;

                    if (R_BLE_GTL_GATTC_DISC_SVC_IND == msg_id)
                    {
                        p_disc_svc_ind = (r_ble_gtl_gattc_disc_svc_ind_t * )&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];

                        status = r_ble_gtl_gattc_handle_discovered_svc(conn_hdl, p_disc_svc_ind, p_disc_evts);

                        r_ble_gtl_msg_buffer_free(p_msg);
                    }
                    else if (R_BLE_GTL_GATTC_DISC_CHAR_IND == msg_id)
                    {
                        p_disc_char_ind = (r_ble_gtl_gattc_disc_char_ind_t * )&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];

                        status = r_ble_gtl_gattc_handle_discovered_char(conn_hdl, p_disc_char_ind, p_disc_evts);

                        r_ble_gtl_msg_buffer_free(p_msg);
                    }
                    else if (R_BLE_GTL_GATTC_DISC_CHAR_DESC_IND == msg_id)
                    {
                        p_disc_desc_ind = (r_ble_gtl_gattc_disc_char_desc_ind_t * )&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];
                        status = r_ble_gtl_gattc_handle_discovered_char_desc(conn_hdl, p_disc_desc_ind, p_disc_evts);
                        r_ble_gtl_msg_buffer_free(p_msg);
                    }
                    else if (R_BLE_GTL_GATTC_DISC_SVC_INCL_IND == msg_id)
                    {
                           p_disc_svc_incl_ind = (r_ble_gtl_gattc_disc_svc_incl_ind_t * )&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];
                           status = r_ble_gtl_gattc_handle_discovered_svc_incl(conn_hdl, p_disc_svc_incl_ind, p_disc_evts);
                           r_ble_gtl_msg_buffer_free(p_msg);
                    }
                    else if (R_BLE_GTL_GATTC_CMP_EVT == msg_id)
                    {
                        p_cb_evt = r_ble_gtl_cb_evt_allocate(p_disc_evts->evt_comp, BLE_SUCCESS, 
                                                                sizeof(st_ble_gattc_evt_data_t));
                        if (NULL != p_cb_evt)
                        {
                            p_cb_evt->data.gattc.conn_hdl=conn_hdl;
                            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
                        }
                        else
                        {
                            status = BLE_ERR_MEM_ALLOC_FAILED;
                        }

                        r_ble_gtl_msg_buffer_free(p_msg);
                        complete = true;
                    }
                    else
                    {
                        /* Message received but not what we expected, queue for processing next time 
                        BLE execute is called */
                        r_ble_gtl_msg_pend_queue_add(&p_msg);
                    }
                }
            }
            while ((false == complete) && (BLE_SUCCESS == status));
        }

        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Handle discovered service
 *
 * @param[in]  p_disc_svc_ind           Discovered service inidication
 * @param[in]  p_disc_evts              Type of events to generate when services are discovered
 *
 * @retval BLE_SUCCESS                  Service discovered and queued.
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Unable to queue discovered service.
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_handle_discovered_svc(uint16_t conn_hdl, r_ble_gtl_gattc_disc_svc_ind_t * p_disc_svc_ind, r_ble_gtl_disc_events_t * p_disc_evts)
{
    ble_status_t                  status;
    st_ble_gattc_serv_16_evt_t  * p_serv_16;
    st_ble_gattc_serv_128_evt_t * p_serv_128;
    r_ble_gtl_cb_evt_t          * p_cb_evt;

    if (p_disc_svc_ind->uuid_len == BLE_GATT_16_BIT_UUID_SIZE)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(p_disc_evts->evt_16, BLE_SUCCESS, sizeof(st_ble_gattc_serv_16_evt_t));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;

            p_serv_16 = p_cb_evt->data.gattc.p_param;
            p_serv_16->uuid_16         = p_disc_svc_ind->uuid.uuid16;
            p_serv_16->range.start_hdl = p_disc_svc_ind->start_hdl;
            p_serv_16->range.end_hdl   = p_disc_svc_ind->end_hdl;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }
    else
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(p_disc_evts->evt_128, BLE_SUCCESS, sizeof(st_ble_gattc_serv_128_evt_t));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;

            p_serv_128 = p_cb_evt->data.gattc.p_param;

            memcpy(p_serv_128->uuid_128, p_disc_svc_ind->uuid.uuid128, BLE_GATT_128_BIT_UUID_SIZE);
            p_serv_128->range.start_hdl = p_disc_svc_ind->start_hdl;
            p_serv_128->range.end_hdl   = p_disc_svc_ind->end_hdl;

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}


/*******************************************************************************************************************//**
 *  Handle discovered characteristic descriptor
 *
 * @param[in]  p_disc_char_desc_ind     Discovered service inidication
 * @param[in]  p_disc_evts              Type of events to generate when services are discovered
 *
 * @retval BLE_SUCCESS                  Characteristic discovered and queued.
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Unable to queue discovered characteristic.
 **********************************************************************************************************************/
static  ble_status_t r_ble_gtl_gattc_handle_discovered_char_desc(uint16_t conn_hdl, r_ble_gtl_gattc_disc_char_desc_ind_t * p_disc_char_desc_ind, r_ble_gtl_disc_events_t * p_disc_evts)
{
    ble_status_t                  status;
    st_ble_gattc_char_desc_16_evt_t  * p_char_16;
    st_ble_gattc_char_desc_128_evt_t * p_char_128;
    r_ble_gtl_cb_evt_t          * p_cb_evt;

    if (p_disc_char_desc_ind->uuid_len == BLE_GATT_16_BIT_UUID_SIZE)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(p_disc_evts->evt_16, BLE_SUCCESS, sizeof(st_ble_gattc_char_desc_16_evt_t));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_char_16 = p_cb_evt->data.gattc.p_param;
            p_char_16->uuid_16   = p_disc_char_desc_ind->uuid.uuid16;
            p_char_16->desc_hdl  = p_disc_char_desc_ind->handle;
            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }
    else
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(p_disc_evts->evt_128, BLE_SUCCESS, sizeof(st_ble_gattc_char_desc_128_evt_t));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_char_128 = p_cb_evt->data.gattc.p_param;
            memcpy(p_char_128->uuid_128, p_disc_char_desc_ind->uuid.uuid128, BLE_GATT_128_BIT_UUID_SIZE);
            p_char_128->desc_hdl  = p_disc_char_desc_ind->handle;
            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Handle discovered included service
 *
 * @param[in]  p_disc_char_desc_ind     Discovered service inidication
 * @param[in]  p_disc_evts              Type of events to generate when services are discovered
 *
 * @retval BLE_SUCCESS                  Characteristic discovered and queued.
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Unable to queue discovered characteristic.
 **********************************************************************************************************************/

static  ble_status_t r_ble_gtl_gattc_handle_discovered_svc_incl(uint16_t conn_hdl, r_ble_gtl_gattc_disc_svc_incl_ind_t * p_disc_svc_incl_ind, r_ble_gtl_disc_events_t * p_disc_evts)
{
    ble_status_t                  status;
    st_ble_gattc_inc_serv_16_evt_t  * p_char_16;
    st_ble_gattc_inc_serv_128_evt_t * p_char_128;
    r_ble_gtl_cb_evt_t          * p_cb_evt;

    if (p_disc_svc_incl_ind->uuid_len == BLE_GATT_16_BIT_UUID_SIZE)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(p_disc_evts->evt_16, BLE_SUCCESS, sizeof(st_ble_gattc_inc_serv_16_evt_t));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_char_16 = p_cb_evt->data.gattc.p_param;

            p_char_16->decl_hdl = p_disc_svc_incl_ind->att_hdl;
            p_char_16->service.uuid_16 =  p_disc_svc_incl_ind->uuid.uuid16;
            p_char_16->service.range.start_hdl =  p_disc_svc_incl_ind->start_hdl;
            p_char_16->service.range.end_hdl =  p_disc_svc_incl_ind->end_hdl;
            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }
    else
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(p_disc_evts->evt_128, BLE_SUCCESS, sizeof(st_ble_gattc_inc_serv_128_evt_t));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_char_128 = p_cb_evt->data.gattc.p_param;

            memcpy(p_char_128->service.uuid_128, p_disc_svc_incl_ind->uuid.uuid128, BLE_GATT_128_BIT_UUID_SIZE);
            p_char_128->service.range.start_hdl =  p_disc_svc_incl_ind->start_hdl;
            p_char_128->service.range.end_hdl =  p_disc_svc_incl_ind->end_hdl;
            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Handle discovered characteristic
 *
 * @param[in]  p_disc_svc_ind           Discovered service inidication
 * @param[in]  p_disc_evts              Type of events to generate when services are discovered
 *
 * @retval BLE_SUCCESS                  Characteristic discovered and queued.
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Unable to queue discovered characteristic.
 **********************************************************************************************************************/
static  ble_status_t r_ble_gtl_gattc_handle_discovered_char(uint16_t conn_hdl, r_ble_gtl_gattc_disc_char_ind_t * p_disc_char_ind, r_ble_gtl_disc_events_t * p_disc_evts)
{
    ble_status_t                  status;
    st_ble_gattc_char_16_evt_t  * p_char_16;
    st_ble_gattc_char_128_evt_t * p_char_128;
    r_ble_gtl_cb_evt_t          * p_cb_evt;

    if (p_disc_char_ind->uuid_len == BLE_GATT_16_BIT_UUID_SIZE)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(p_disc_evts->evt_16, BLE_SUCCESS, sizeof(st_ble_gattc_char_16_evt_t));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_char_16 = p_cb_evt->data.gattc.p_param;
            p_char_16->uuid_16   = p_disc_char_ind->uuid.uuid16;
            p_char_16->cproperty = p_disc_char_ind->properties;
            p_char_16->decl_hdl  = p_disc_char_ind->att_hdl;
            p_char_16->value_hdl = p_disc_char_ind->ptr_hdl;
            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }
    else
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(p_disc_evts->evt_128, BLE_SUCCESS, sizeof(st_ble_gattc_char_128_evt_t));
        if (NULL != p_cb_evt)
        {
            p_cb_evt->data.gattc.conn_hdl = conn_hdl;
            p_char_128 = p_cb_evt->data.gattc.p_param;
            memcpy(p_char_128->uuid_128, p_disc_char_ind->uuid.uuid128, BLE_GATT_128_BIT_UUID_SIZE);
            p_char_128->cproperty = p_disc_char_ind->properties;
            p_char_128->decl_hdl  = p_disc_char_ind->att_hdl;
            p_char_128->value_hdl = p_disc_char_ind->ptr_hdl;
            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send write client attribute command to the DA14xxx.
 *
 * @param[in]  operation                Type of write operation
 * @param[in]  conn_hdl                 Handle of connection on which request should be made
 * @param[in]  att_hdl                  Handle of attribute to write
 * @param[in]  p_value                  Pointer to value to be written
 * @param[in]  length                   Length of value to be written
 * @param[in]  offset                   Offset (within value) to be written
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_write_cmd(uint8_t operation, uint8_t auto_exec, uint16_t conn_hdl, 
                                                uint16_t att_hdl, uint8_t * p_value, uint16_t length, uint16_t offset)
{
    ble_status_t                  status;
    r_ble_gtl_gattc_write_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_write_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_WRITE_CMD,
                                                                  R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                                  R_BLE_GTL_TASK_ID_GTL,
                                                                  sizeof (r_ble_gtl_gattc_write_cmd_t) + length);
    if (NULL != p_cmd)
    {
        p_cmd->operation = operation;
        p_cmd->auto_exec = auto_exec;
        p_cmd->seq_nbr   = 0x0000;
        p_cmd->handle    = att_hdl;
        p_cmd->offset    = offset;
        p_cmd->length    = length;
        p_cmd->cursor    = 0x0000;
        memcpy(p_cmd->value, p_value, length);

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send read client attribute command to the DA14xxx
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  value_hdl                Handle of attribute to be read
 * @param[in]  p_value                  Pointer to data structure into which read value should be written
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_read_cmd(uint16_t conn_hdl, uint8_t operation, uint16_t att_hdl, 
                                                  uint16_t offset, uint16_t length)
{
    ble_status_t                 status;
    r_ble_gtl_gattc_read_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_read_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_READ_CMD,
                                                                 R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                                 R_BLE_GTL_TASK_ID_GTL,
                                                                 sizeof (r_ble_gtl_gattc_read_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->operation = operation;
        p_cmd->seq_nbr   = 0x0000;
        p_cmd->number    = 0x00; /* Not used for this operation */
        p_cmd->param.att_hdl = att_hdl - (uint16_t)g_dev_params.att_hndl_offset;
        p_cmd->param.offset  = offset;
        p_cmd->param.length  = length;

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send read client attribute command to the DA14xxx
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  value_hdl                Handle of attribute to be read
 * @param[in]  p_value                  Pointer to data structure into which read value should be written
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_read_by_uuid_cmd(uint16_t conn_hdl, uint16_t start_hdl, 
                                                          uint16_t end_hdl, r_ble_gtl_uuid_t * p_uuid)
{
    ble_status_t                 status;
    r_ble_gtl_gattc_read_uuid_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_read_uuid_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_READ_CMD,
                                                              R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                              R_BLE_GTL_TASK_ID_GTL,
                                                              sizeof (r_ble_gtl_gattc_read_uuid_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->operation = R_BLE_GTL_GATTC_OP_READ_BY_UUID;
        p_cmd->seq_nbr   = 0x0000;
        p_cmd->number    = 0x00; /* Not used for this operation */
        p_cmd->param.start_hdl = start_hdl;
        p_cmd->param.end_hdl   = end_hdl;
        p_cmd->param.uuid_len  = p_uuid->length;
        memcpy(&p_cmd->param.uuid, &p_uuid->value, p_uuid->length);

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send read client multiple attributes command to the DA14xxx
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  number                   Number of attributes to be read
 * @param[in]  value_hdl                Start handle of attributes to be read
 * @param[in]  length                   Length of attribute handle
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_read_multiple_cmd(uint16_t conn_hdl, uint8_t number, uint16_t * p_hdl_list, uint16_t * p_length_list)
{
    ble_status_t                       status;
    r_ble_gtl_gattc_read_multi_cmd_t * p_cmd;
    uint16_t                           hdl;

    p_cmd = (r_ble_gtl_gattc_read_multi_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_READ_CMD,
                                                                       R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                                       R_BLE_GTL_TASK_ID_GTL,
                                                                       (uint16_t)(sizeof(r_ble_gtl_gattc_read_multi_cmd_t) + 
                                                                                 (sizeof (uint32_t) * number)));
    if (NULL != p_cmd)
    {
        p_cmd->operation = R_BLE_GTL_GATTC_OP_READ_MULTIPLE;
        p_cmd->number    = number;
        p_cmd->seq_nbr   = 0x0000;

        for (hdl = 0; hdl < number; hdl++)
        {
            p_cmd->att_list[hdl].att_hdl = p_hdl_list[hdl];
            if (p_length_list!=NULL)
            {
                p_cmd->att_list[hdl].length = p_length_list[hdl];
            }
            else
            {
                p_cmd->att_list[hdl].length = 0;
            }

        }

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send MTU exchange command to the DA14xxx
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_exch_mtu_cmd(uint16_t conn_hdl)
{
    ble_status_t                    status;
    r_ble_gtl_gattc_exc_mtu_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_exc_mtu_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_EXC_MTU_CMD,
                                                            R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                            R_BLE_GTL_TASK_ID_GTL,
                                                            sizeof (r_ble_gtl_gattc_exc_mtu_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->operation = R_BLE_GTL_GATTC_OP_MTU_EXCH;
        p_cmd->seq_nbr   = 0x0000;

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}


static ble_status_t r_ble_gtl_gattc_send_att_info_cfm(uint16_t conn_hdl, uint16_t att_hdl, uint16_t value_len, uint8_t cmd_status)
{
    ble_status_t                 status;
    r_ble_gtl_gattc_att_info_cfm_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_att_info_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_ATT_INFO_CFM,
                                                                 R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                                 R_BLE_GTL_TASK_ID_GTL,
                                                                 sizeof (r_ble_gtl_gattc_att_info_cfm_t));
    if (NULL != p_cmd)
    {
         p_cmd->handle = att_hdl;
         p_cmd->length = value_len;
         p_cmd->status = cmd_status;

         status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
         status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}
/*******************************************************************************************************************//**
 *  Send client read confirm command to the DA14xxx
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  rd_status                Status of read request
 * @param[in]  att_hdl                  Handle of attribute that was read
 * @param[in]  value_len                Length of data value read
 * @param[in]  p_value                  Pointer to attribute value
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_read_cfm(uint16_t conn_hdl, uint8_t rd_status, uint16_t att_hdl, 
                                                  uint16_t value_len, uint8_t * p_value)
{
    ble_status_t                 status;
    r_ble_gtl_gattc_read_cfm_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_read_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_READ_CFM,
                                                        R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                        R_BLE_GTL_TASK_ID_GTL,
                                                        /* Command ends with a single padding byte (of any value) */
                                                        sizeof (r_ble_gtl_gattc_read_cfm_t) + value_len + 1);
    if (NULL != p_cmd)
    {
        p_cmd->handle = att_hdl;
        p_cmd->length = value_len;
        p_cmd->status = rd_status;
        if (NULL != p_value)
        {
            memcpy(p_cmd->value, p_value, value_len);
        }

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send write confirm command to the DA14xxx
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  wr_status                Status of write request
 * @param[in]  att_handle               Handle of attribute written
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_write_cfm(uint16_t conn_hdl, uint8_t wr_status, uint16_t att_handle)
{
    ble_status_t                      status;
    r_ble_gtl_gattc_write_req_cfm_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_write_req_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_WRITE_CFM,
                                                            R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                            R_BLE_GTL_TASK_ID_GTL,
                                                            sizeof (r_ble_gtl_gattc_write_req_cfm_t));
    if (NULL != p_cmd)
    {
        p_cmd->status = wr_status;
        p_cmd->handle = att_handle;
        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send write event confirmation command to the DA14xxx (Indications Only)
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  wr_status                Status of write request
 * @param[in]  att_handle               Handle of attribute written
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_event_cfm(uint16_t conn_hdl, uint16_t attr_hdl)
{
    ble_status_t status;
    r_ble_gtl_gattc_event_cfm_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_event_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_EVENT_CFM,
                                                                  R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                                  R_BLE_GTL_TASK_ID_GTL,
                                                                  sizeof (r_ble_gtl_gattc_event_cfm_t));
    if (NULL != p_cmd)
    {
        p_cmd->handle = attr_hdl;
        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send write confirm command to the DA14xxx
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  operation                Type of discovery operation
 * @param[in]  uuid_len                 Length of UUID
 * @param[in]  seq_num                  Sequence number for operation
 * @param[in]  start_hdl                Start attribute handle
 * @param[in]  end_hdl                  End attribute handle
 * @param[in]  p_uuid                   Pointer to UUID to be discovered
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_disc_cmd(uint16_t conn_hdl, uint8_t operation, uint16_t seq_num, 
                                                  uint16_t start_hdl, uint16_t end_hdl, r_ble_gtl_uuid_t * p_uuid)
{
    ble_status_t status;
    r_ble_gtl_gattc_disc_cmd_t *p_cmd;
    uint16_t param_len;

    if ((operation == R_BLE_GTL_GATTC_OP_DISC_ALL_SVC)||
        (operation == R_BLE_GTL_GATTC_OP_DISC_ALL_CHAR)||
        (operation == R_BLE_GTL_GATTC_OP_DISC_DESC_CHAR)||
        (operation == R_BLE_GTL_GATTC_OP_DISC_INCLUDED_SVC))
    {
        param_len =  sizeof (r_ble_gtl_gattc_disc_uuid16_cmd_t) ;
    }
    else
    {
        param_len =  sizeof (r_ble_gtl_gattc_disc_cmd_t);
    }
    p_cmd = (r_ble_gtl_gattc_disc_cmd_t*) r_ble_gtl_msg_allocate (R_BLE_GTL_GATTC_DISC_CMD,
                                                                  R_BLE_GTL_TASK_ID_GATTC + (uint16_t) (conn_hdl << 8),
                                                                  R_BLE_GTL_TASK_ID_GTL,
                                                                  param_len);

    if (NULL != p_cmd)
    {
        p_cmd->operation = operation;
        p_cmd->seq_num   = seq_num;
        p_cmd->start_hdl = start_hdl;
        p_cmd->end_hdl = end_hdl;

        if ((operation == R_BLE_GTL_GATTC_OP_DISC_ALL_SVC)||
            (operation == R_BLE_GTL_GATTC_OP_DISC_ALL_CHAR)||
            (operation == R_BLE_GTL_GATTC_OP_DISC_DESC_CHAR)||
            (operation == R_BLE_GTL_GATTC_OP_DISC_INCLUDED_SVC))
        {
            p_cmd->uuid_len = 0x02;
        }
        if (NULL != p_uuid)
        {
            p_cmd->uuid_len = p_uuid->length;
            memcpy(&p_cmd->uuid, &p_uuid->value, p_cmd->uuid_len);
        }

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send write confirm command to the DA14xxx
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  operation                Type of event
 * @param[in]  attr_hdl                 Attribute handle associated with event
 * @param[in]  p_value                  Pointer to value associated with event
 * @param[in]  length                   Length of value
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_evt_cmd(uint8_t operation, uint16_t conn_hdl, uint16_t attr_hdl, 
                                                 uint8_t * p_value, uint16_t length)
{
    ble_status_t                     status;
    r_ble_gtl_gattc_send_evt_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_send_evt_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_SEND_EVT_CMD,
                                                            R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                            R_BLE_GTL_TASK_ID_GTL,
                                                            sizeof (r_ble_gtl_gattc_send_evt_cmd_t) + length);
    if (NULL != p_cmd)
    {
        p_cmd->operation = operation;
        p_cmd->seq_num   = 0x0000;
        p_cmd->handle    = attr_hdl;
        p_cmd->length    = length;
        memcpy(p_cmd->value, p_value, length);

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send execute write command to the DA14xxx
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made (not used)
 * @param[in]  execute                  Execute (1) or cancel (0) the operation
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gattc_send_write_execute_cmd(uint16_t conn_hdl, uint8_t execute)
{
    ble_status_t                          status;
    r_ble_gtl_gattc_write_execute_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gattc_write_execute_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GATTC_WRITE_EXECUTE_CMD,
                                                                R_BLE_GTL_TASK_ID_GATTC + (uint16_t)(conn_hdl << 8),
                                                                R_BLE_GTL_TASK_ID_GTL,
                                                                sizeof (r_ble_gtl_gattc_write_execute_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->operation = R_BLE_GTL_GATTC_OP_EXEC_WRITE;
        p_cmd->execute   = execute;
        p_cmd->seq_nbr   = 0x0000;

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Stop advertising
 *
 * @param[in]  adv_hdl                  Advertising handle
 * @param[in]  reason                   Reason for stopping (0x01 due to stop function, 0x02 due to timer expiration)
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gap_stop_adv(uint8_t adv_hdl, uint8_t reason)
{
    ble_status_t               status;
    r_ble_gtl_cb_evt_t       * p_cb_evt;
    st_ble_gap_adv_off_evt_t * p_evt_param;

    status = r_ble_gtl_gapm_send_cancel_cmd(g_dev_params.adv_mode);
    if (BLE_SUCCESS == status)
    {
        p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_ADV_OFF, BLE_SUCCESS, sizeof(st_ble_gap_adv_off_evt_t));

        if (NULL != p_cb_evt)
        {
            p_evt_param = p_cb_evt->data.gap.p_param;

            p_cb_evt->data.gap.param_len = sizeof(st_ble_gap_adv_off_evt_t);
            p_evt_param->adv_hdl               = adv_hdl;
            p_evt_param->reason                = reason;
            p_evt_param->conn_hdl              = 0;       /* Field not used */
            p_evt_param->num_comp_ext_adv_evts = 0;       /* Extended advertising is not supported by the DA1453x */

            status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }

        g_dev_params.state &= (uint8_t)~R_BLE_GTL_DEV_STATE_ADVERTISING;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Read characteristic value from attribute database by handle.
 *
 * @param[in]  handle           Attribute handle
 * @param[in]  p_value          Pointer into which attribute value pointer should be written
 * @param[in]  p_len            Pointer into which attribute length should be written
 *
 * @retval BLE_SUCCESS          Attribute read successfully
 * @retval BLE_ERR_NOT_FOUND    Attribute not found
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gap_get_char_value_by_handle(uint16_t handle, uint8_t ** p_value, uint16_t * p_len)
{
    ble_status_t status = BLE_ERR_NOT_FOUND;
    uint32_t     att_ix;

    for (att_ix = 0; att_ix < QE_ATTRIBUTE_HANDLE_PROFILE_END; att_ix++)
    {
        attribute_t * p_att = (attribute_t *)&qe_ble_profile[att_ix];
        if (p_att->handle == handle)
        {
            *p_len   = p_att->value_length;
            *p_value = p_att->value;
            status = BLE_SUCCESS;
            break;
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Read characteristic value from attribute database by UUID.
 *
 * @param[in]  uuid             UUID (16-bit) of attribute
 * @param[in]  p_value          Pointer into which attribute value should be written
 * @param[in]  p_len            Maximum length of value
 *
 * @retval BLE_SUCCESS          Attribute read successfully
 * @retval BLE_ERR_NOT_FOUND    Attribute not found
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gap_get_char_value_by_uuid(uint16_t uuid, uint8_t * p_value, uint8_t len)
{
    ble_status_t status = BLE_ERR_NOT_FOUND;
    uint32_t     att_ix;
    uint32_t     i;

    for (att_ix = 0; att_ix < QE_ATTRIBUTE_HANDLE_PROFILE_END; att_ix++)
    {
        attribute_t * p_att = (attribute_t *)&qe_ble_profile[att_ix];

        if (BLE_GATT_16_BIT_UUID_SIZE == p_att->uuid_length)
        {
            /* Check if this is the start of a primary service section */
            if (R_BLE_GTL_ATT_PRIMARY_SVC_DECL == *((uint16_t *)p_att->uuid))
            {
                /* Check if it is the GAP service */
                if (R_BLE_GTL_SVC_GAP_UUID == *((uint16_t *)p_att->value))
                {
                    /* GAP service found, now check for characteristic value */
                    for (i = 0; i < p_att->encapsulated_attributes; i++)
                    {
                        attribute_t * p_gap_svc_att = (attribute_t *)&qe_ble_profile[att_ix + i];

                        if (BLE_GATT_16_BIT_UUID_SIZE == p_gap_svc_att->uuid_length)
                        {
                            if (*((uint16_t *)p_gap_svc_att->uuid) == uuid)
                            {
                                if (p_gap_svc_att->value_length <= len)
                                {
                                    /* Device name characteristic value found */
                                    memcpy(p_value, p_gap_svc_att->value, p_gap_svc_att->value_length);
                                    /* Break out of outer loop */
                                    att_ix = QE_ATTRIBUTE_HANDLE_PROFILE_END;
                                    status = BLE_SUCCESS;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Read transmit power level and convert into units of dBm.
 *
 * @param[in]  p_tx_pwr         Pointer into which power level value should be written
 *
 * @retval BLE_SUCCESS          Power level read successfully
 * @retval BLE_ERR_INVALID_DATA Invalid power level returned
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_aux_get_tx_power(int8_t * p_tx_pwr)
{
    uint8_t      tx_power_level;
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_aux_send_get_tx_power_cmd();
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_AUX_GET_TX_POWER_RSP,
                                                     &tx_power_level,
                                                     sizeof(tx_power_level),
                                                     R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
            if (BLE_SUCCESS == status)
            {
                /* Convert response into dBm */
                if ((sizeof(tx_pwr_lut) > tx_power_level) && (0 < tx_power_level))
                {
                    *p_tx_pwr = tx_pwr_lut[tx_power_level];
                }
                else
                {
                    status =  BLE_ERR_INVALID_DATA;
                }
            }

        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Set transmit power level.
 *
 * @param[in] tx_pwr                   Power level value
 *
 * @retval BLE_SUCCESS                 Power level set successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS Busy with another command
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_aux_set_tx_power(uint8_t tx_pwr)
{
    ble_status_t status = BLE_ERR_ALREADY_IN_PROGRESS;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
    {
        status = r_ble_gtl_aux_send_set_tx_power_cmd(tx_pwr);
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_AUX_SET_TX_POWER_CMP_EVT,
                                                         R_BLE_GTL_AUX_SET_TX_POWER,
                                                         R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                         R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS);
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send get transmit power command to the DA14xxx
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_aux_send_get_tx_power_cmd(void)
{
    ble_status_t   status;
    uint8_t      * p_cmd;

    p_cmd = r_ble_gtl_msg_allocate(R_BLE_GTL_AUX_GET_TX_POWER_CMD,
                                   R_BLE_GTL_TASK_ID_AUX,
                                   R_BLE_GTL_TASK_ID_GTL,
                                   sizeof(r_ble_gtl_aux_get_pwr_cmd_t));
    if (NULL != p_cmd)
    {
        status = r_ble_gtl_msg_transmit(p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send set transmit power command to the DA14xxx
 *
 * @param[in] operation                 Power level value
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_aux_send_set_tx_power_cmd(uint8_t operation)
{
    ble_status_t                  status;
    r_ble_gtl_aux_set_pwr_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_aux_set_pwr_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_AUX_SET_TX_POWER_CMD,
                                                                  R_BLE_GTL_TASK_ID_AUX,
                                                                  R_BLE_GTL_TASK_ID_GTL,
                                                                  sizeof(r_ble_gtl_aux_set_pwr_cmd_t));
    if (NULL != p_cmd)
    {
        p_cmd->operation = operation;

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/**********************************************************************************************************************
 *  Parse received GTL message byte. Once complete message is received it is queued for processing by the R_BLE_Execute
 *  function (which is called periodically by the users application).
 *
 * @param[in]  byte     Single byte of a GTL message.
 *
 * @retval NULL         No message received
 * @retval uint8_t *    Pointer to buffer containing received message
 **********************************************************************************************************************/
static uint8_t * r_ble_gtl_msg_parse_rx_char(uint8_t rxd_byte)
{
     uint8_t * p_rx_msg = NULL;

     switch (rx_gtl_msg_parser_state)
     {
         case R_BLE_GTL_RX_MSG_PARSER_STATE_IDLE:
         {
             if (R_BLE_GTL_MSG_INITIATOR == rxd_byte)
             {
                 /* Get buffer to store message, don't know how long it will be so assume the worst case... */
                 p_rx_buf = r_ble_gtl_msg_buffer_allocate_from_isr(R_BLE_GTL_MSG_LEN_MAX);
                 if (NULL != p_rx_buf)
                 {
                     rx_msg_ix = 0;
                     rx_gtl_msg_parser_state = R_BLE_GTL_RX_MSG_PARSER_STATE_RX_HEADER;
                 }
             }
             break;
         }

         case R_BLE_GTL_RX_MSG_PARSER_STATE_RX_HEADER:
         {
             p_rx_buf[rx_msg_ix] = rxd_byte;
             rx_msg_ix++;

             if (R_BLE_GTL_MSG_HDR_LEN == rx_msg_ix)
             {
                 r_ble_gtl_msg_hdr_t * p_msg_hdr = (r_ble_gtl_msg_hdr_t *)p_rx_buf;

                 /* Header reception complete */
                 if (0 == p_msg_hdr->param_length)
                 {
                     /* No parameters, message reception complete */
                     p_rx_msg = p_rx_buf;

                     /* Reset state so next message can be received */
                     rx_gtl_msg_parser_state = R_BLE_GTL_RX_MSG_PARSER_STATE_IDLE;
                 }
                 else
                 {
                     /* Receive parameters */
                     rx_gtl_msg_parser_state = R_BLE_GTL_RX_MSG_PARSER_STATE_RX_PARAM;
                 }
             }
             break;
         }

         case R_BLE_GTL_RX_MSG_PARSER_STATE_RX_PARAM:
         {
             if (rx_msg_ix < R_BLE_GTL_MSG_LEN_MAX)
             {
                 r_ble_gtl_msg_hdr_t * p_msg_hdr = (r_ble_gtl_msg_hdr_t *)p_rx_buf;

                 p_rx_buf[rx_msg_ix] = rxd_byte;
                 rx_msg_ix++;

                 if (rx_msg_ix == (p_msg_hdr->param_length + R_BLE_GTL_MSG_HDR_LEN))
                 {
                     /* message reception complete */
                     p_rx_msg = p_rx_buf;

                     /* Reset state so next message can be received */
                     rx_gtl_msg_parser_state = R_BLE_GTL_RX_MSG_PARSER_STATE_IDLE;
                 }
             }
             else
             {
                 /* Number of received bytes has exceeded maximum expected message length,
                    just discard the message... */
                 r_ble_gtl_msg_buffer_free_from_isr(p_rx_buf);
                 rx_gtl_msg_parser_state = R_BLE_GTL_RX_MSG_PARSER_STATE_IDLE;
             }
             break;
         }

         default:
         {
             /* Invalid state, should never get here...*/
             break;
         }
     }

     return p_rx_msg;
}

/*******************************************************************************************************************//**
 *  Wait for a response following transmission of a GTL message
 *
 * @param[in]  rsp_msg_id       Message ID of expected response
 * @param[in]  p_rsp_param      Pointer into which parameters should be written if expected response received
 * @param[in]  rsp_param_len    Length of expected response parameters
 * @param[in]  timeout_ms       Time to wait for response (in milliseconds)
 *
 * @retval BLE_SUCCESS          Expected response recevied
 * @retval BLE_ERR_NOT_FOUND    Expected response not recevied
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_msg_wait_for_response(uint16_t rsp_msg_id, uint8_t * p_rsp_param, 
                                                uint32_t rsp_param_len, uint32_t timeout_ms)
{
    ble_status_t   status;
    bool           received = false;
    uint8_t      * p_msg = NULL;

    do
    {
        status = r_ble_gtl_msg_receive(&p_msg, timeout_ms);
        if (BLE_SUCCESS == status)
        {
            if (((r_ble_gtl_msg_hdr_t *)p_msg)->msg_id == rsp_msg_id)
            {
                if ((NULL != p_rsp_param) && (0 != rsp_param_len))
                {
                    memcpy(p_rsp_param, &p_msg[sizeof(r_ble_gtl_msg_hdr_t)], rsp_param_len);
                }
                r_ble_gtl_msg_buffer_free(p_msg);
                received = true;
            }
            else
            {
                /* Message received but not what we expected, queue for processing next time BLE execute is called */
                r_ble_gtl_msg_pend_queue_add(&p_msg);
            }
        }
    }
    while ((BLE_ERR_NOT_FOUND != status) && (false == received));

    return status;
}

/*******************************************************************************************************************//**
 *  Wait for a command complete response following transmission of a GTL message
 *
 * @param[in]  cmp_evt          Event ID of expected response
 * @param[in]  operation        Operation expected in command complete response
 * @param[in]  cmd_status       Command status expected in command complete response
 * @param[in]  timeout_ms       Time to wait for response (in milliseconds)
 *
 * @retval BLE_SUCCESS          Expected response recevied
 * @retval BLE_ERR_NOT_FOUND    Expected response not recevied
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_msg_wait_for_cmd_complete(uint16_t cmp_evt, uint8_t operation, 
                                                uint8_t cmd_status, uint32_t timeout_ms)
{
    ble_status_t               status;
    bool                       received = false;
    uint8_t                  * p_msg = NULL;
    r_ble_gtl_gapm_cmp_evt_t * p_param;

    do
    {
        status = r_ble_gtl_msg_receive(&p_msg, timeout_ms);
        if (BLE_SUCCESS == status)
        {
            if (cmp_evt == ((r_ble_gtl_msg_hdr_t *)p_msg)->msg_id)
            {

                p_param = (r_ble_gtl_gapm_cmp_evt_t *)&p_msg[sizeof(r_ble_gtl_msg_hdr_t)];
                if ((p_param->operation == operation) && (p_param->status == cmd_status))
                {
                    status = BLE_SUCCESS;
                }
                else if ((p_param->operation == operation) && (cmd_status == R_BLE_GTL_GAP_ERR_ANY))
                {
                    /* Here we detect a possible error */
                    status = p_param->status;
                }
                else
                {
                    status = BLE_ERR_NOT_FOUND;
                }
                r_ble_gtl_msg_buffer_free(p_msg);
                received = true;
            }
            else
            {
                /* Message received but not what we expected, queue for processing next time BLE execute is called */
                r_ble_gtl_msg_pend_queue_add(&p_msg);
            }
        }
    }
    while ((BLE_ERR_NOT_FOUND != status) && (false == received));

    return status;
}

/*******************************************************************************************************************//**
 *  Deassert the RTS signal. Development feature.
 *
 **********************************************************************************************************************/
#if (BLE_DA1453x_SLEEP_FLOW_CONTROL)
void r_ble_gtl_rts_flow_off( void )
{

    R_BSP_PinAccessEnable ();

    R_BSP_PinWrite (BSP_IO_PORT_04_PIN_12, BSP_IO_LEVEL_HIGH);

    R_BSP_PinAccessDisable ();
}
#endif

/*******************************************************************************************************************//**
 *  Assert the RTS signal. Development feature.
 *
 **********************************************************************************************************************/
 #if (BLE_DA1453x_SLEEP_FLOW_CONTROL)
void r_ble_gtl_rts_flow_on( void )
{

    R_BSP_PinAccessEnable ();

    R_BSP_PinWrite (BSP_IO_PORT_04_PIN_12, BSP_IO_LEVEL_LOW);

    R_BSP_PinAccessDisable ();
}
#endif 

/*******************************************************************************************************************//**
 *  Transmit a GTL message of the appropriate transport layer.
 *
 * @param[in]  p_msg                    Pointer to message to be transmitted
 *
 * @retval BLE_SUCCESS                  Message transmitted successfully
 * @retval BLE_ERR_ALREADY_IN_PROGRESS  Unable to obtain mutex as transmission already in progress
 * @retval BLE_ERR_UNSPECIFIED          Transport layer failed to transmit message
 **********************************************************************************************************************/
 
static ble_status_t r_ble_gtl_msg_transmit(uint8_t * p_msg)
{
#if BLE_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != p_msg, BLE_ERR_INVALID_ARG);
#endif

    ble_status_t          status        = BLE_ERR_ALREADY_IN_PROGRESS;
    r_ble_gtl_msg_hdr_t * p_gtl_msg_hdr = (r_ble_gtl_msg_hdr_t *)p_msg;
    uint8_t               initiator     = R_BLE_GTL_MSG_INITIATOR;

    if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_TX))
    {
        
        #if (BLE_DA1453x_SLEEP_FLOW_CONTROL)
        if (active_sleep_mode > 0)
        {
            r_ble_gtl_rts_flow_off();
            vTaskDelay(pdMS_TO_TICKS(R_BLE_GTL_SLEEP_WAKEUP_TOGGLE_MS));
            r_ble_gtl_rts_flow_on();
        }
        #endif 
 
        /* First transmit the initiator byte, then the message */
        status = r_ble_gtl_transmit(&initiator, sizeof(initiator));
        if (BLE_SUCCESS == status)
        {
            status = r_ble_gtl_transmit(p_msg, p_gtl_msg_hdr->param_length + sizeof(r_ble_gtl_msg_hdr_t));
        }
        r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_TX);
    }

    r_ble_gtl_free(p_msg);

    return status;
}

/*******************************************************************************************************************//**
 *  Allocate memory for transmission of a GTL message and build the header with supplied parameters.
 *
 * @param[in]  id       Message ID (type)
 * @param[in]  dest_id  Destination task ID
 * @param[in]  src_id   Source task ID
 * @param[in]  len      Length of message (including parameters) in bytes
 *
 * @retval NULL         Unable to allocate memory for the message
 * @retval Address      Pointer to memory containing the message
 **********************************************************************************************************************/
static uint8_t * r_ble_gtl_msg_allocate(uint16_t id, uint16_t dest_id, uint16_t src_id, uint16_t len)
{
    uint8_t             * p_msg;
    r_ble_gtl_msg_hdr_t * p_msg_hdr;

    p_msg = (uint8_t *)r_ble_gtl_malloc(len);

    if (NULL != p_msg)
    {
        p_msg_hdr = (r_ble_gtl_msg_hdr_t *)p_msg;

        /* Build message header */
        p_msg_hdr->msg_id       = id;
        p_msg_hdr->dest_id      = dest_id;
        p_msg_hdr->src_id       = src_id;
        p_msg_hdr->param_length = (uint16_t)(len - sizeof(r_ble_gtl_msg_hdr_t));

        /* Some commands can have zero parameters */
        if (0 != p_msg_hdr->param_length)
        {
            memset(&p_msg[sizeof(r_ble_gtl_msg_hdr_t)], 0, p_msg_hdr->param_length);
        }
    }

    return p_msg;
}

/*******************************************************************************************************************//**
 *  Execute callback assocaited with an callback event.
 *
 * @param[in]  p_evt    Pointer containing callback event data.
 *
 **********************************************************************************************************************/
static void r_ble_gtl_cb_evt_execute(r_ble_gtl_cb_evt_t * p_evt)
{
    if (NULL != p_evt)
    {
        switch(p_evt->type & R_BLE_GTL_CB_EVT_TYPE_MASK)
        {
            case R_BLE_GTL_CB_EVT_TYPE_GAP:
            {
                if (NULL != g_gap_cb)
                {
                    g_gap_cb(p_evt->type, p_evt->result, &p_evt->data.gap);
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_GATTS:
            {
                if (NULL != g_gatts_cb)
                {
                    g_gatts_cb(p_evt->type, p_evt->result, &p_evt->data.gatts);
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_GATTC:
            {
                if (NULL != g_gattc_cb)
                {
                    g_gattc_cb(p_evt->type, p_evt->result, &p_evt->data.gattc);
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_L2CAP:
            {
                if (NULL != g_l2cap_cb)
                {
                    g_l2cap_cb(p_evt->type, p_evt->result, &p_evt->data.l2cap);
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_VS:
            {
                if (NULL != g_vs_cb)
                {
                    g_vs_cb(p_evt->type, p_evt->result, &p_evt->data.vs);
                }
                break;
            }

            default:
            {
                /* Unknown event type, do nothing. */
                break;
            }
        }
    }
}

/*******************************************************************************************************************//**
 *  Allocated memory for a callback event
 *
 * @param[in]  type             Type of callback event (helps determine amount of memory to allocate)
 * @param[in]  result           Result status code to embed into the callback event
 * @param[in]  param_len        Length of parameters assocaited with the event
 *
 * @retval NULL                 Unable to allocate required memory
 * @retval r_ble_gtl_cb_evt_t * Pointer to allocated memory
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_cb_evt_allocate(uint16_t type, ble_status_t result, uint16_t param_len)
{
    r_ble_gtl_cb_evt_t * p_evt_cb = NULL;
    bool allocated                = false;

    p_evt_cb = r_ble_gtl_malloc(sizeof(r_ble_gtl_cb_evt_t));
    if (NULL != p_evt_cb)
    {
        /* Allocate memory for event parameters */
        switch (type & R_BLE_GTL_CB_EVT_TYPE_MASK)
        {
            case R_BLE_GTL_CB_EVT_TYPE_L2CAP:
            {
                p_evt_cb->data.l2cap.p_param = r_ble_gtl_malloc(param_len);
                if ( NULL != p_evt_cb->data.l2cap.p_param)
                {
                    allocated = true;
                }
                else
                {
                    p_evt_cb->data.gap.p_param = NULL;
                    allocated = false; 
                }
                if (true == allocated)
                {
                    p_evt_cb->type                  = type;
                    p_evt_cb->result                = result;
                    p_evt_cb->data.l2cap.param_len  = param_len;
                }
                else
                {
                    r_ble_gtl_free(p_evt_cb);
                    p_evt_cb = NULL;
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_GAP:
            {
                if (0 != param_len)
                {
                    p_evt_cb->data.gap.p_param = r_ble_gtl_malloc(param_len);
                    if (NULL != p_evt_cb->data.gap.p_param)
                    {
                        allocated = true;
                    }

                }
                else
                {
                    p_evt_cb->data.gap.p_param = NULL;
                    allocated = true;
                }

                if (true == allocated)
                {
                    p_evt_cb->type               = type;
                    p_evt_cb->result             = result;
                    p_evt_cb->data.gap.param_len = param_len;
                }
                else
                {
                    r_ble_gtl_free(p_evt_cb);
                    p_evt_cb = NULL;
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_GATTS:
            {
                if (BLE_GATTS_EVENT_DB_ACCESS_IND == type)
                {
                    st_ble_gatts_db_access_evt_t * p_db_access_param;

                    p_evt_cb->data.gatts.p_param = r_ble_gtl_malloc(sizeof(st_ble_gatts_db_access_evt_t));
                    if (NULL != p_evt_cb->data.gatts.p_param)
                    {
                        p_db_access_param = (st_ble_gatts_db_access_evt_t *)p_evt_cb->data.gatts.p_param;

                        p_db_access_param->p_handle = r_ble_gtl_malloc(sizeof(st_ble_gatts_db_conn_hdl_t));
                        if (NULL != p_db_access_param->p_handle)
                        {
                            p_db_access_param->p_params = r_ble_gtl_malloc(sizeof(st_ble_gatts_db_params_t));
                            if (NULL != p_db_access_param->p_params)
                            {
                                p_db_access_param->p_params->value.p_value = r_ble_gtl_malloc(param_len);
                                if (NULL != p_db_access_param->p_params->value.p_value)
                                {
                                    allocated = true;
                                }
                            }
                        }
                    }
                    if (true == allocated)
                    {
                        p_evt_cb->type                 = type;
                        p_evt_cb->result               = result;
                        p_evt_cb->data.gatts.param_len = param_len;
                    }
                    else
                    {
                        if (NULL != p_evt_cb->data.gatts.p_param)
                        {
                            if (NULL != p_db_access_param->p_handle)
                            {
                                r_ble_gtl_free(p_db_access_param->p_handle);
                            }
                            if (NULL != p_db_access_param->p_params)
                            {
                                if (NULL != p_db_access_param->p_params->value.p_value)
                                {
                                    r_ble_gtl_free(p_db_access_param->p_params->value.p_value);
                                }
                                r_ble_gtl_free(p_db_access_param->p_params);
                            }
                            r_ble_gtl_free(p_evt_cb->data.gatts.p_param);
                        }
                        r_ble_gtl_free(p_evt_cb);
                        p_evt_cb = NULL;
                    }
                }
                else
                {
                    if (0 != param_len)
                    {
                        p_evt_cb->data.gatts.p_param = r_ble_gtl_malloc(param_len);
                        if (NULL != p_evt_cb->data.gatts.p_param)
                        {
                            allocated = true;
                        }
                    }
                    else
                    {
                        p_evt_cb->data.gatts.p_param = NULL;
                        allocated = true;
                    }

                    if (true == allocated)
                    {
                        p_evt_cb->type                 = type;
                        p_evt_cb->result               = result;
                        p_evt_cb->data.gatts.param_len = param_len;
                    }
                    else
                    {
                        r_ble_gtl_free(p_evt_cb);
                        p_evt_cb = NULL;
                    }
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_GATTC:
            {
                if (0 != param_len)
                {
                    p_evt_cb->data.gattc.p_param = r_ble_gtl_malloc(param_len);
                    if (NULL != p_evt_cb->data.gattc.p_param)
                    {
                        allocated = true;
                    }
                }
                else
                {
                    p_evt_cb->data.gattc.p_param = NULL;
                    allocated = true;
                }

                if (true == allocated)
                {
                    p_evt_cb->type                 = type;
                    p_evt_cb->result               = result;
                    p_evt_cb->data.gattc.param_len = param_len;
                }
                else
                {
                    r_ble_gtl_free(p_evt_cb);
                    p_evt_cb = NULL;
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_VS:
            {
                if (BLE_VS_EVENT_GET_RAND == type)
                {
                    st_ble_vs_get_rand_comp_evt_t * p_rand_comp;

                    p_evt_cb->data.vs.p_param = r_ble_gtl_malloc(sizeof(st_ble_vs_get_rand_comp_evt_t));
                    if (NULL != p_evt_cb->data.vs.p_param)
                    {
                        p_rand_comp = (st_ble_vs_get_rand_comp_evt_t *)p_evt_cb->data.vs.p_param;

                        p_rand_comp->p_rand = r_ble_gtl_malloc(sizeof(param_len));
                        if (NULL != p_rand_comp->p_rand)
                        {
                            allocated = true;
                        }
                    }
                    if (true == allocated)
                    {
                        p_evt_cb->type              = type;
                        p_evt_cb->result            = result;
                        p_evt_cb->data.vs.param_len = param_len;
                    }
                    else
                    {
                        if (NULL != p_evt_cb->data.vs.p_param)
                        {
                            if (NULL != p_rand_comp->p_rand)
                            {
                                r_ble_gtl_free(p_rand_comp->p_rand);
                            }
                            r_ble_gtl_free(p_evt_cb->data.vs.p_param);
                        }

                        r_ble_gtl_free(p_evt_cb);
                        p_evt_cb = NULL;
                    }
                }
                else
                {
                    if (0 != param_len)
                    {
                        p_evt_cb->data.vs.p_param = r_ble_gtl_malloc(param_len);
                        if (NULL != p_evt_cb->data.vs.p_param)
                        {
                            allocated = true;
                        }
                    }
                    else
                    {
                        p_evt_cb->data.vs.p_param = NULL;
                        allocated = true;
                    }

                    if (true == allocated)
                    {
                        p_evt_cb->type              = type;
                        p_evt_cb->result            = result;
                        p_evt_cb->data.vs.param_len = param_len;
                    }
                    else
                    {
                        r_ble_gtl_free(p_evt_cb);
                        p_evt_cb = NULL;
                    }
                }
                break;
            }

            default:
            {
                /* Unknown event type, do nothing. */
                break;
            }
        }
    }

    return p_evt_cb;
}

/*******************************************************************************************************************//**
 *  Free memory allocated for a callback event
 *
 * @param[in]  p_evt        Pointer to callback event memory to be freed
 *
 **********************************************************************************************************************/
static void r_ble_gtl_cb_evt_free(r_ble_gtl_cb_evt_t * p_evt)
{
    if (NULL != p_evt)
    {
        /* Free any memory allocated for event parameters */
        switch(p_evt->type & R_BLE_GTL_CB_EVT_TYPE_MASK)
        {
            case R_BLE_GTL_CB_EVT_TYPE_GAP:
            {
                if (NULL != p_evt->data.gap.p_param)
                {
                    if (BLE_GAP_EVENT_ADV_REPT_IND == p_evt->type)
                    {
                        st_ble_gap_adv_rept_evt_t * p_gapm_adv_report_ind_param = p_evt->data.gap.p_param;
                        r_ble_gtl_free( p_gapm_adv_report_ind_param->param.p_adv_rpt->p_addr);
                        r_ble_gtl_free( p_gapm_adv_report_ind_param->param.p_adv_rpt->p_data );
                        r_ble_gtl_free( p_gapm_adv_report_ind_param->param.p_adv_rpt);
                    }
                    r_ble_gtl_free(p_evt->data.gap.p_param);
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_GATTS:
            {
                if (NULL != p_evt->data.gatts.p_param)
                {
                    if (BLE_GATTS_EVENT_DB_ACCESS_IND == p_evt->type)
                    {
                        st_ble_gatts_db_access_evt_t * p_db_access_param;
                        p_db_access_param = (st_ble_gatts_db_access_evt_t *)p_evt->data.gatts.p_param;

                        r_ble_gtl_free(p_db_access_param->p_params->value.p_value);
                        r_ble_gtl_free(p_db_access_param->p_params);
                        r_ble_gtl_free(p_db_access_param->p_handle);
                    }

                    r_ble_gtl_free(p_evt->data.gatts.p_param);
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_GATTC:
            {
                if (NULL != p_evt->data.gattc.p_param)
                {
                    bool free_evt_data = false;

                    switch(p_evt->type)
                    {
                        case BLE_GATTC_EVENT_HDL_VAL_NTF:
                        case BLE_GATTC_EVENT_HDL_VAL_IND:
                     
                        case BLE_GATTC_EVENT_CHAR_READ_BY_UUID_RSP:
                        case BLE_GATTC_EVENT_CHAR_READ_RSP:
                
                        case BLE_GATTC_EVENT_CHAR_PART_READ_RSP:
                        case BLE_GATTC_EVENT_MULTI_CHAR_READ_RSP:

                    
                        {
                            free_evt_data = true;
                        }
                        break;
                        default:
                            break;

                    }

                    if (free_evt_data == true)
                    {
                        st_ble_gattc_ntf_evt_t * p_evt_param = (st_ble_gattc_ntf_evt_t *)p_evt->data.gattc.p_param;
                        r_ble_gtl_free(p_evt_param->data.value.p_value);
                    }
                    r_ble_gtl_free(p_evt->data.gattc.p_param);
                }
                break;
            }

            case R_BLE_GTL_CB_EVT_TYPE_VS:
            {
                if (NULL != p_evt->data.vs.p_param)
                {
                    /* Some events have additional memory allocated when created, free this first */
                    if (BLE_VS_EVENT_GET_RAND == p_evt->type)
                    {
                        st_ble_vs_get_rand_comp_evt_t * p_rand_comp;

                        p_rand_comp = (st_ble_vs_get_rand_comp_evt_t *)p_evt->data.vs.p_param;
                        if (NULL != p_rand_comp->p_rand)
                        {
                            r_ble_gtl_free(p_rand_comp->p_rand);
                        }
                    }
                    r_ble_gtl_free(p_evt->data.vs.p_param);
                }
                break;
            }

            default:
            {
                /* Unknown event type, do nothing. */
                break;
            }
        }

        r_ble_gtl_free(p_evt);
    }
}

/*******************************************************************************************************************//**
 *  Build an GTL attribute descriptor based on QE attribute descriptor
 *
 * @param[in]  p_att_desc   Pointer to GTL descriptor being built
 * @param[in]  p_att        Pointer to QE descriptor used as source
 * @param[in]  nbr_atts     Number of attributes
 *
 * @retval BLE_SUCCESS      Descriptor built successfully
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_att_build_descriptor(r_ble_gtl_gattm_att_desc_t * p_att_desc, 
                                                   attribute_t * p_att, uint16_t nbr_atts)
{
    uint16_t att_ix   = 0;
    uint32_t att_perm = 0;
    bool is_value_declaration = false;

    for (att_ix = 0; att_ix < nbr_atts; att_ix++)
    {
        /* First add the UUID */
        memset(&p_att_desc->uuid[0], 0, BLE_GATT_128_BIT_UUID_SIZE);
        memcpy(&p_att_desc->uuid[0], p_att->uuid, p_att->uuid_length);

        /* Convert permissions from QE Tool generated type to GTL type */
        p_att_desc->perm = 0;
        if (is_value_declaration == false)
        {
            if (p_att->permissions & R_BLE_GTL_QE_ATT_PERM_READ)
            {
                att_perm |= R_BLE_GTL_ATT_PERM_READ_ENABLE;
            }

            if (BLE_GATT_128_BIT_UUID_SIZE == p_att->uuid_length)
            {
                att_perm |= R_BLE_GTL_ATT_PERM_UUID_LEN_128;
            }

            if (p_att->permissions & R_BLE_GTL_QE_ATT_PERM_WRITE)
            {
                att_perm |= R_BLE_GTL_ATT_PERM_WRITE_ENABLE;
                att_perm |= R_BLE_GTL_ATT_PERM_WRITE_REQ_ACCEPTED;
            }
        }
        else
        {
            if (BLE_GATT_128_BIT_UUID_SIZE == p_att->uuid_length)
            {
                att_perm |= R_BLE_GTL_ATT_PERM_UUID_LEN_128;
            }
            if (p_att->permissions & R_BLE_GTL_QE_ATT_PERM_READ)
            {
                att_perm |= R_BLE_GTL_ATT_PERM_READ_ENABLE;
            }
            is_value_declaration = false;
        }
        p_att_desc->perm = att_perm;

        /* Enabling the RI */
        if (r_ble_gtl_ptr_attribute_is_ri(p_att))
        {
            p_att_desc->max_len = p_att->value_length | R_BLE_GTL_RI_FLAG;
        }    
        else
        {
            p_att_desc->max_len = p_att->value_length;
        }

        /* If this is was a characteristic declaration then additional permissions such as
           notify etc. are stored in value field. Extract these and then apply them to the
           value which is always next in the list */
        att_perm = 0;
        if (BLE_GATT_16_BIT_UUID_SIZE == p_att->uuid_length)
        {
            uint16_t uuid;
            memcpy(&uuid, p_att->uuid, BLE_GATT_16_BIT_UUID_SIZE);

            if (R_BLE_GTL_CHAR_DECLARATION == uuid)
            {
                if (0 < p_att->value_length)
                {
                    if (p_att->value[0] & R_BLE_GTL_QE_ATT_PROP_INDICATE)
                    {
                        att_perm |= R_BLE_GTL_ATT_PERM_INDICATE_ENABLE;
                    }

                    if (p_att->value[0] & R_BLE_GTL_QE_ATT_PROP_NOTIFY)
                    {
                        att_perm |= R_BLE_GTL_ATT_PERM_NOIFY_ENABLE;
                    }

                    if (p_att->value[0] & R_BLE_GTL_QE_ATT_PROP_WRITE_NO_RESPONSE)
                    {
                        att_perm |= R_BLE_GTL_ATT_PERM_WRITE_ENABLE;
                        att_perm |= R_BLE_GTL_ATT_PERM_WRITE_CMD_ACCEPTED;
                    }

                    if (p_att->value[0] & R_BLE_GTL_QE_ATT_PROP_WRITE)
                    {
                        att_perm |= R_BLE_GTL_ATT_PERM_WRITE_ENABLE;
                        att_perm |= R_BLE_GTL_ATT_PERM_WRITE_REQ_ACCEPTED;
                    }


                    is_value_declaration = true;
                    /*
                     r_ble_gtl_gattm_att_desc_t *p_att_desc_value = p_att_desc + 1;
                     p_att_desc_value->perm = att_perm;
                     */
                }
            }
        }
        p_att_desc++;
        p_att++;
    }

    return BLE_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Free any memory allocated by calling the R_BLE_GTL_Open function.
 **********************************************************************************************************************/
static void r_ble_gtl_cleanup_open(void)
{
#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (NULL != g_tx_sem)
    {
        vSemaphoreDelete(g_tx_sem);
        g_tx_sem = NULL;
    }

    if (NULL != g_rx_sem)
    {
        vSemaphoreDelete(g_rx_sem);
        g_rx_sem = NULL;
    }

    if (NULL != g_uart_tei_sem)
    {
        vSemaphoreDelete(g_uart_tei_sem);
        g_uart_tei_sem = NULL;
    }

    if (NULL != g_cb_evt_queue)
    {
        vQueueDelete(g_cb_evt_queue);
        g_cb_evt_queue = NULL;
    }

    if (NULL != g_used_gtl_msg_queue)
    {
        vQueueDelete(g_used_gtl_msg_queue);
        g_used_gtl_msg_queue = NULL;
    }

    if (NULL != g_free_gtl_msg_queue)
    {
        vQueueDelete(g_free_gtl_msg_queue);
        g_free_gtl_msg_queue = NULL;
    }

    if (NULL != g_pend_gtl_msg_queue)
    {
        vQueueDelete(g_pend_gtl_msg_queue);
        g_pend_gtl_msg_queue = NULL;
    }

    if (NULL != g_adv_timer)
    {
        r_ble_gtl_adv_timer_stop();
    }

    if (NULL != g_events)
    {
        vEventGroupDelete(g_events);
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    tx_semaphore_delete(&g_tx_sem);
    tx_semaphore_delete(&g_rx_sem);
    tx_semaphore_delete(&g_uart_tei_sem);

    tx_queue_delete(&g_cb_evt_queue);
    tx_queue_delete(&g_used_gtl_msg_queue);
    tx_queue_delete(&g_free_gtl_msg_queue);
    tx_queue_delete(&g_pend_gtl_msg_queue);

    r_ble_gtl_adv_timer_stop();

    tx_byte_pool_delete(&g_byte_pool);

    tx_event_flags_delete(&g_events);
#endif
}

/*******************************************************************************************************************//**
 *  Allocate a GTL message buffer - safe to call from within an ISR
 *
 * @param[in]  len          Length of buffer required
 *
 **********************************************************************************************************************/
static uint8_t * r_ble_gtl_msg_buffer_allocate_from_isr(uint16_t len)
{
    uint8_t * p_buff = NULL;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    FSP_PARAMETER_NOT_USED(len);
    if (pdFALSE == xQueueReceiveFromISR(g_free_gtl_msg_queue, &p_buff, NULL))
    {
        p_buff = NULL;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    FSP_PARAMETER_NOT_USED(len);
    if (TX_SUCCESS != tx_queue_receive(&g_free_gtl_msg_queue, &p_buff, TX_NO_WAIT))
    {
        p_buff = NULL;
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    FSP_PARAMETER_NOT_USED(len);
    /* Statically allocated buffers are all the same length. Deliberately
     * ignoring return value, caller should check for NULL pointer. */
    (void)r_ble_gtl_fifo_get((r_ble_gtl_fifo_t *)&g_free_gtl_msg_queue, &p_buff, 0);
#endif

    return p_buff;
}

/*******************************************************************************************************************//**
 *  Free previously allocated GTL message buffer
 *
 * @param[in]  p_msg        Pointer to message buffer to be freed
 *
 **********************************************************************************************************************/
static void r_ble_gtl_msg_buffer_free(uint8_t * p_msg)
{
#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    xQueueSend(g_free_gtl_msg_queue, &p_msg, 0);
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    tx_queue_send(&g_free_gtl_msg_queue, &p_msg, TX_NO_WAIT);
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    (void)r_ble_gtl_fifo_put((r_ble_gtl_fifo_t *)&g_free_gtl_msg_queue, &p_msg);
#endif
}

/*******************************************************************************************************************//**
 *  Free previously allocated GTL message buffer - safe to be called from an ISR
 *
 * @param[in]  p_msg        Pointer to message buffer to be freed
 *
 **********************************************************************************************************************/
static void r_ble_gtl_msg_buffer_free_from_isr(uint8_t * p_msg)
{
#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    BaseType_t xHigherPriorityTaskWoken;
    xQueueSendFromISR(g_free_gtl_msg_queue, &p_msg, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    tx_queue_send(&g_free_gtl_msg_queue, &p_msg, TX_NO_WAIT);
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    (void)r_ble_gtl_fifo_put((r_ble_gtl_fifo_t *)&g_free_gtl_msg_queue, &p_msg);
#endif
}

/*******************************************************************************************************************//**
 *  Receive GTL message by checking incoming messge queue
 *
 * @param[in]  p_msg            Pointer into which message buffer pointer is stored if message is received
 * @param[in]  timeout_ms       Maximum time to wait (in milliseconds)
 *
 * @retval BLE_SUCCESS          Message received
 * @retval BLE_ERR_RSP_TIMEOUT  Timeout while waiting for message to be received
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_msg_receive(uint8_t ** p_msg, uint32_t timeout_ms)
{
    ble_status_t status = BLE_ERR_NOT_FOUND;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (pdTRUE == xQueueReceive(g_used_gtl_msg_queue, p_msg, timeout_ms * portTICK_PERIOD_MS))
    {
        status = BLE_SUCCESS;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (TX_SUCCESS == tx_queue_receive(&g_used_gtl_msg_queue, p_msg, 
                                        (timeout_ms * TX_TIMER_TICKS_PER_SECOND) / R_BLE_GTL_MS_PER_SECOND))
    {
        status = BLE_SUCCESS;
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    if (true == r_ble_gtl_fifo_get((r_ble_gtl_fifo_t *)&g_used_gtl_msg_queue, p_msg, timeout_ms))
    {
        status = BLE_SUCCESS;
    }
#endif

    return status;
}

/*******************************************************************************************************************//**
 *  Receive GTL message by checking pending messge queue
 *
 * @param[in]  p_msg            Pointer into which message buffer pointer is stored if message is received
 * @param[in]  timeout_ms       Maximum time to wait (in milliseconds)
 *
 * @retval BLE_SUCCESS          Message received
 * @retval BLE_ERR_RSP_TIMEOUT  Timeout while waiting for message to be received
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_msg_pend_receive(uint8_t ** p_msg, uint32_t timeout_ms)
{
    ble_status_t status = BLE_ERR_NOT_FOUND;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (pdTRUE == xQueueReceive(g_pend_gtl_msg_queue, p_msg, timeout_ms * portTICK_PERIOD_MS))
    {
        status = BLE_SUCCESS;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (TX_SUCCESS == tx_queue_receive(&g_pend_gtl_msg_queue, p_msg, 
                                        (timeout_ms * TX_TIMER_TICKS_PER_SECOND) / R_BLE_GTL_MS_PER_SECOND))
    {
        status = BLE_SUCCESS;
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    if (true == r_ble_gtl_fifo_get(&g_pend_gtl_msg_queue, p_msg, timeout_ms))
    {
        status = BLE_SUCCESS;
    }
#endif

    return status;
}

/*******************************************************************************************************************//**
 *  Initialize GTL messages queue(s)
 *
 * @retval true     Queue initialized successfully
 * @retval false    Queue initialized failed
 **********************************************************************************************************************/
static bool r_ble_gtl_msg_queue_init(void)
{
    bool init = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    uint8_t i;
    /* Initialize queues containing (pointers to) buffers used to store incoming GTL messages */
    g_used_gtl_msg_queue = xQueueCreate(R_BLE_GTL_MSG_QUEUE_LEN, sizeof(uint8_t *));
    if (NULL != g_used_gtl_msg_queue)
    {
        g_pend_gtl_msg_queue = xQueueCreate(R_BLE_GTL_MSG_QUEUE_LEN, sizeof(uint8_t *));
        if (NULL != g_pend_gtl_msg_queue)
        {
            g_free_gtl_msg_queue = xQueueCreate(R_BLE_GTL_MSG_QUEUE_LEN, sizeof(uint8_t *));
            if (NULL != g_free_gtl_msg_queue)
            {
                /* Fill free queue with (pointers to) buffers */
                for (i = 0; i < R_BLE_GTL_MSG_QUEUE_LEN; i++)
                {
                    uint8_t * p_buf = &g_gtl_msg_buf_pool[i][0];
                    (void)xQueueSend(g_free_gtl_msg_queue, &p_buf, 0);
                }

                init = true;
            }
        }
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    uint8_t i;
    UINT    status;

    /* Initialize queues containing (pointers to) buffers used to store incoming GTL messages */
    status = tx_queue_create(&g_used_gtl_msg_queue, "GTL_USED", TX_1_ULONG, &g_used_gtl_msg_queue_buff[0], 
                                        sizeof(ULONG) * (TX_1_ULONG) * (R_BLE_GTL_MSG_QUEUE_LEN));
    if (TX_SUCCESS == status)
    {
        status = tx_queue_create(&g_pend_gtl_msg_queue, "GTL_USED", TX_1_ULONG, &g_pend_gtl_msg_queue_buff[0], 
                                        sizeof(ULONG) * (TX_1_ULONG) * (R_BLE_GTL_MSG_QUEUE_LEN));
        if (TX_SUCCESS == status)
        {
            status = tx_queue_create(&g_free_gtl_msg_queue, "GTL_USED", TX_1_ULONG, &g_free_gtl_msg_queue_buff[0], 
                                        sizeof(ULONG) * (TX_1_ULONG) * (R_BLE_GTL_MSG_QUEUE_LEN));
            if (TX_SUCCESS == status)
            {
                /* Fill free queue with (pointers to) buffers */
                for (i = 0; i < R_BLE_GTL_MSG_QUEUE_LEN; i++)
                {
                    uint8_t * p_buf = &g_gtl_msg_buf_pool[i][0];
                    (void)tx_queue_send(&g_free_gtl_msg_queue, &p_buf, TX_NO_WAIT);
                }

                /* Create byte pool (heap) used when building messages for transmission */
                status = tx_byte_pool_create(&g_byte_pool, "GTL_HEAP", &g_byte_pool_buff[0], R_BLE_GTL_BYTE_POOL_LEN);
                if (TX_SUCCESS == status)
                {
                    init = true;
                }
            }
        }
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    uint8_t i;

    /* Initialize queues containing (pointers to) buffers used to store incoming GTL messages */
    r_ble_gtl_fifo_init((r_ble_gtl_fifo_t *)&g_used_gtl_msg_queue, g_used_gtl_msg_buf, R_BLE_GTL_MSG_QUEUE_LEN);
    r_ble_gtl_fifo_init((r_ble_gtl_fifo_t *)&g_free_gtl_msg_queue, g_free_gtl_msg_buf, R_BLE_GTL_MSG_QUEUE_LEN);
    r_ble_gtl_fifo_init(&g_pend_gtl_msg_queue, g_pend_gtl_msg_buf, R_BLE_GTL_MSG_QUEUE_LEN);


    /* Fill free queue with (pointers to) buffers */
    init = true;
    for (i = 0; (i < R_BLE_GTL_MSG_QUEUE_LEN) && (true == init); i++)
    {
        uint8_t * p_buf = &g_gtl_msg_buf_pool[i][0];
        init = r_ble_gtl_fifo_put((r_ble_gtl_fifo_t *)&g_free_gtl_msg_queue, &p_buf);
    }
#endif

    return init;
}

/*******************************************************************************************************************//**
 *  Add GTL message to received queue
 *
 * @param[in]  p_rx_msg     Pointer to buffer containing received message
 *
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_msg_queue_add(uint8_t ** p_rx_msg)
{
    ble_status_t status = BLE_ERR_MEM_ALLOC_FAILED;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    BaseType_t xHigherPriorityTaskWoken;

    if (pdTRUE == xQueueSendFromISR(g_used_gtl_msg_queue, p_rx_msg, &xHigherPriorityTaskWoken))
    {
        xEventGroupSetBitsFromISR(g_ble_event_group_handle, BLE_EVENT_PATTERN, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        status = BLE_SUCCESS;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (TX_SUCCESS == tx_queue_send(&g_used_gtl_msg_queue, p_rx_msg, TX_NO_WAIT))
    {
        status = BLE_SUCCESS;
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    if (true == r_ble_gtl_fifo_put((r_ble_gtl_fifo_t *)&g_used_gtl_msg_queue, p_rx_msg))
    {
        status = BLE_SUCCESS;
    }
#endif

    return status;
}

/*******************************************************************************************************************//**
 *  Check if the received message queue is empty.
 *
 * @retval true          Queue is empty
 * @retval false         Queue is not empty
 **********************************************************************************************************************/
static bool r_ble_gtl_msg_queue_empty(void)
{
    bool result = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (0 == uxQueueMessagesWaiting(g_used_gtl_msg_queue))
    {
        result = true;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    CHAR      * p_name;
    ULONG       enqueued;
    ULONG       available_storage;
    TX_THREAD * p_first_suspended;
    ULONG       suspended_count;
    TX_QUEUE  * p_next_queue;
    UINT        status;

    status = tx_queue_info_get(&g_used_gtl_msg_queue,
                               &p_name,
                               &enqueued,
                               &available_storage,
                               &p_first_suspended,
                               &suspended_count,
                               &p_next_queue);

    if (TX_SUCCESS == status)
    {
        if (0 == enqueued)
        {
            result = true;
        }
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    result = r_ble_gtl_fifo_empty((r_ble_gtl_fifo_t *)&g_used_gtl_msg_queue);
#endif

    return result;
}

/*******************************************************************************************************************//**
 *  Add a message to the pending queue.
 *
 * @param[in]  p_rx_msg     Pointer to buffer containing message.
 *
 **********************************************************************************************************************/
static void r_ble_gtl_msg_pend_queue_add(uint8_t ** p_rx_msg)
{
#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (pdTRUE != xQueueSend(g_pend_gtl_msg_queue, p_rx_msg, 0))
    {
        /* Unable to queue message, just discard */
        r_ble_gtl_msg_buffer_free(*p_rx_msg);
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (TX_SUCCESS != tx_queue_send(&g_pend_gtl_msg_queue, p_rx_msg, TX_NO_WAIT))
    {
        /* Unable to queue message, just discard */
        r_ble_gtl_msg_buffer_free(*p_rx_msg);
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    r_ble_gtl_fifo_put(&g_pend_gtl_msg_queue, p_rx_msg);
#endif
}

/*******************************************************************************************************************//**
 *  Check if the pending message queue is empty.
 *
 * @retval true          Queue is empty
 * @retval false         Queue is not empty
 **********************************************************************************************************************/
static bool r_ble_gtl_msg_pend_queue_empty(void)
{
    bool result = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (0 == uxQueueMessagesWaiting(g_pend_gtl_msg_queue))
    {
        result = true;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    CHAR      * p_name;
    ULONG       enqueued;
    ULONG       available_storage;
    TX_THREAD * p_first_suspended;
    ULONG       suspended_count;
    TX_QUEUE  * p_next_queue;
    UINT        status;

    status = tx_queue_info_get(&g_pend_gtl_msg_queue,
                               &p_name,
                               &enqueued,
                               &available_storage,
                               &p_first_suspended,
                               &suspended_count,
                               &p_next_queue);

    if (TX_SUCCESS == status)
    {
        if (0 == enqueued)
        {
            result = true;
        }
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    result = r_ble_gtl_fifo_empty(&g_pend_gtl_msg_queue);
#endif

    return result;
}

/*******************************************************************************************************************//**
 *  Initialize the callback event queue.
 *
 * @retval true         Initialization successful.
 * @retval false        Initialization failed.
 **********************************************************************************************************************/
static bool r_ble_gtl_cb_evt_queue_init(void)
{
    bool init = true;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    g_cb_evt_queue = xQueueCreate(R_BLE_GTL_CB_EVT_QUEUE_LEN, sizeof(r_ble_gtl_cb_evt_t *));
    if (NULL == g_cb_evt_queue)
    {
        init = false;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    UINT    status;
    status = tx_queue_create(&g_cb_evt_queue, "GTL_CB_EVT", TX_1_ULONG, &g_cb_evt_queue_buff[0], 
                                    sizeof(ULONG) * (TX_1_ULONG) * (R_BLE_GTL_CB_EVT_QUEUE_LEN));
    if (TX_SUCCESS != status)
    {
        init = false;
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    /* Initialize queue containing (pointers to) buffers used to store callback events */
    r_ble_gtl_fifo_init(&g_cb_evt_queue, (uint8_t **)g_cb_evt_queue_buff, R_BLE_GTL_CB_EVT_QUEUE_LEN);
#endif

    return init;
}

/*******************************************************************************************************************//**
 *  Remove an item from the callback event queue.
 *
 * @param[in]  p_cb_evt     Pointer to callback event removed from queue
 * @retval true             Item removed from the queue
 * @retval false            No item removed from queue (because it is empty)
 **********************************************************************************************************************/
static bool r_ble_gtl_cb_evt_queue_get(r_ble_gtl_cb_evt_t ** p_cb_evt)
{
    bool result = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (0 < uxQueueMessagesWaiting(g_cb_evt_queue))
    {
        if (pdTRUE == xQueueReceive(g_cb_evt_queue, p_cb_evt, 0))
        {
            result = true;
        }
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (TX_SUCCESS == tx_queue_receive(&g_cb_evt_queue, p_cb_evt, TX_NO_WAIT))
    {
        result = true;
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    result = r_ble_gtl_fifo_get(&g_cb_evt_queue, (uint8_t **)p_cb_evt, 0);
#endif

    return result;
}

/*******************************************************************************************************************//**
 *  Add an entry to the callback event queue.
 *
 * @param[in]  p_evt                    Pointer to the event to be added
 * @retval BLE_SUCCESS                  Event successfully added to the queue.
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficent memory to add item to queue.
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_cb_evt_queue_add(r_ble_gtl_cb_evt_t * p_evt)
{
    ble_status_t status;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    /* FreeRTOS based implementation */
    if (pdTRUE == xQueueSend(g_cb_evt_queue, &p_evt, 0))
    {
        xEventGroupSetBits(g_ble_event_group_handle, BLE_EVENT_PATTERN);
        status = BLE_SUCCESS;
    }
    else
    {
        /* Failed to add event to queue, free memory storing event data */
        r_ble_gtl_cb_evt_free(p_evt);
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (TX_SUCCESS == tx_queue_send(&g_cb_evt_queue, &p_evt, TX_NO_WAIT))
    {
        status = BLE_SUCCESS;
    }
    else
    {
        /* Failed to add event to queue, free memory storing event data */
        r_ble_gtl_cb_evt_free(p_evt);
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    if (true == r_ble_gtl_fifo_put(&g_cb_evt_queue, (uint8_t **)&p_evt))
    {
        status = BLE_SUCCESS;
    }
    else
    {
        /* Failed to add event to queue, free memory storing event data */
        r_ble_gtl_cb_evt_free(p_evt);
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }
#endif

    return status;
}

/*******************************************************************************************************************//**
 *  Check if callback event queue is emtpy
 *
 * @retval true          Queue is empty
 * @retval false         Queue is not empty
 **********************************************************************************************************************/
static bool r_ble_gtl_cb_evt_queue_empty(void)
{
    bool result = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (0 == uxQueueMessagesWaiting(g_cb_evt_queue))
    {
        result = true;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    CHAR      * p_name;
    ULONG       enqueued;
    ULONG       available_storage;
    TX_THREAD * p_first_suspended;
    ULONG       suspended_count;
    TX_QUEUE  * p_next_queue;
    UINT        status;

    status = tx_queue_info_get(&g_cb_evt_queue,
                               &p_name,
                               &enqueued,
                               &available_storage,
                               &p_first_suspended,
                               &suspended_count,
                               &p_next_queue);

    if (TX_SUCCESS == status)
    {
        if (0 == enqueued)
        {
            result = true;
        }
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    result = r_ble_gtl_fifo_empty(&g_cb_evt_queue);
#endif

    return result;
}

/*******************************************************************************************************************//**
 *  Generate a blocking delay.
 *
 * @param[in]  ms       Length of delay in milliseconds
 **********************************************************************************************************************/
static void r_ble_gtl_delay(uint32_t ms)
{
#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    vTaskDelay(pdMS_TO_TICKS(ms));
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    tx_thread_sleep((ms * TX_TIMER_TICKS_PER_SECOND) / R_BLE_GTL_MS_PER_SECOND);
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    R_BSP_SoftwareDelay(ms, BSP_DELAY_MILLISECS);
#endif
}

/*******************************************************************************************************************//**
 *  Wrappper for memory allocate function.
 *
 * @param[in]  size     Size of memory to be allocated (in bytes)
 * @retval NULL         Memory not allocated
 * @retval Address      Address of memory allocated
 **********************************************************************************************************************/
static void * r_ble_gtl_malloc(uint32_t size)
{
#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    return pvPortMalloc(size);
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    UINT    status;
    UCHAR * p_mem;

    status = tx_byte_allocate(&g_byte_pool, (VOID **)&p_mem, size, TX_NO_WAIT);
    if (TX_SUCCESS != status)
    {
        p_mem = NULL;
    }

    return p_mem;
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    void *p_mem = NULL;
    p_mem = malloc(size);
    memset(p_mem, 0, size);
    return p_mem;
#endif
}

/*******************************************************************************************************************//**
 *  Wrapper for free memory allocation function.
 *
 * @param[in]  p_mem    Pointer to memory to be freed
 **********************************************************************************************************************/
static void r_ble_gtl_free(void * p_mem)
{
#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    vPortFree(p_mem);
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    tx_byte_release(p_mem);
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    free(p_mem);
#endif
}

/*******************************************************************************************************************//**
 *  Initialize mutexe(s)
 *
 * @param[in]  mutex     Bitmask respresenting mutex(es) to be initialized
 **********************************************************************************************************************/
static bool r_ble_gtl_mutex_init(void)
{
    bool status = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (NULL != g_tx_sem)
    {
        vSemaphoreDelete(g_tx_sem);
    }

    g_tx_sem = xSemaphoreCreateMutex();
    if (NULL != g_tx_sem)
    {
        if (NULL != g_rx_sem)
        {
            vSemaphoreDelete(g_rx_sem);
        }

        g_rx_sem = xSemaphoreCreateMutex();
        if (NULL != g_rx_sem)
        {
            g_uart_tei_sem = xSemaphoreCreateBinary();
            if (NULL != g_uart_tei_sem)
            {
                xSemaphoreTake(g_uart_tei_sem, 0);
                status = true;
            }
        }
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    UINT result;

    result = tx_semaphore_create(&g_tx_sem, "GTL_TX_SEM", 1);
    if (TX_SUCCESS == result)
    {
        result = tx_semaphore_create(&g_rx_sem, "GTL_RX_SEM", 1);
        if (TX_SUCCESS == result)
        {
            result = tx_semaphore_create(&g_uart_tei_sem, "GTL_TEI_SEM", 1);
            if (TX_SUCCESS == result)
            {
                result = tx_semaphore_get(&g_uart_tei_sem, TX_NO_WAIT);
                if (TX_SUCCESS == result)
                {
                    status = true;
                }
            }
        }
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    g_uart_tei_sem = false;
    status = true;
#endif

    return status;
}

/*******************************************************************************************************************//**
 *  Take one of the previously created mutexes.
 *
 * @param[in]  mutex    Bitmask representing which mutex(es) to take.
 *
 * @retval true         Mutex(es) taken successfully
 * @retval false        Taking one (or more) mutex failed
 **********************************************************************************************************************/
static bool r_ble_gtl_mutex_take(uint32_t mutex)
{
    bool status = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (0 != (mutex & R_BLE_GTL_MUTEX_TX))
    {
        if (pdTRUE == xSemaphoreTake(g_tx_sem, R_BLE_GTL_MSG_TX_BLOCK_TIMEOUT_MS))
        {
            mutex &= ~R_BLE_GTL_MUTEX_TX;
        }
    }

    if (0 != (mutex & R_BLE_GTL_MUTEX_RX))
    {
        if (pdTRUE == xSemaphoreTake(g_rx_sem, R_BLE_GTL_MSG_TX_BLOCK_TIMEOUT_MS))
        {
            mutex &= ~R_BLE_GTL_MUTEX_RX;
        }
    }

    if (0 != (mutex & R_BLE_GTL_MUTEX_TEI))
    {
        if (pdTRUE == xSemaphoreTake(g_uart_tei_sem, pdMS_TO_TICKS(R_BLE_GTL_MSG_TX_TIMEOUT_MS)))
        {
            mutex &= ~R_BLE_GTL_MUTEX_TEI;
        }
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (0 != (mutex & R_BLE_GTL_MUTEX_TX))
    {
        if (TX_SUCCESS == tx_semaphore_get(&g_tx_sem, 
                            (R_BLE_GTL_MSG_TX_BLOCK_TIMEOUT_MS * TX_TIMER_TICKS_PER_SECOND) / R_BLE_GTL_MS_PER_SECOND))
        {
            mutex &= ~R_BLE_GTL_MUTEX_TX;
        }
    }

    if (0 != (mutex & R_BLE_GTL_MUTEX_RX))
    {
        if (TX_SUCCESS == tx_semaphore_get(&g_rx_sem, 
                            (R_BLE_GTL_MSG_TX_BLOCK_TIMEOUT_MS * TX_TIMER_TICKS_PER_SECOND) / R_BLE_GTL_MS_PER_SECOND))
        {
            mutex &= ~R_BLE_GTL_MUTEX_RX;
        }
    }

    if (0 != (mutex & R_BLE_GTL_MUTEX_TEI))
    {
        if (TX_SUCCESS == tx_semaphore_get(&g_uart_tei_sem, 
                            (R_BLE_GTL_MSG_TX_TIMEOUT_MS * TX_TIMER_TICKS_PER_SECOND) / R_BLE_GTL_MS_PER_SECOND))
        {
            mutex &= ~R_BLE_GTL_MUTEX_TEI;
        }
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    if (0 != (mutex & R_BLE_GTL_MUTEX_TEI))
    {
        uint32_t timeout_ms = R_BLE_GTL_MSG_TX_TIMEOUT_MS;

        do
        {
            if (false == g_uart_tei_sem)
            {
                if (0 < timeout_ms)
                {
                    r_ble_gtl_delay(1);
                }
            }
            else
            {
                mutex = 0;
                g_uart_tei_sem = false;
                break;
            }
        }
        while (0 < timeout_ms);
    }
    else
    {
        mutex = 0;
    }
#endif

    if (0 == mutex)
    {
        status = true;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Give one of the previously created mutexes.
 *
 * @param[in]  mutex    Bitmask representing which mutex(es) to give.
 *
 * @retval true         Mutex(es) taken successfully
 * @retval false        Giving one (or more) mutex failed
 **********************************************************************************************************************/
static bool r_ble_gtl_mutex_give(uint32_t mutex)
{
    bool status = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (0 != (mutex & R_BLE_GTL_MUTEX_TX))
    {
        if (pdTRUE == xSemaphoreGive(g_tx_sem))
        {
            mutex &= ~R_BLE_GTL_MUTEX_TX;
        }
    }

    if (0 != (mutex & R_BLE_GTL_MUTEX_RX))
    {
        if (pdTRUE == xSemaphoreGive(g_rx_sem))
        {
            mutex &= ~R_BLE_GTL_MUTEX_RX;
        }
    }

    if (0 != (mutex & R_BLE_GTL_MUTEX_TEI))
    {
        if (pdTRUE == xSemaphoreGiveFromISR(g_uart_tei_sem, &xHigherPriorityTaskWoken))
        {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            mutex &= ~R_BLE_GTL_MUTEX_TEI;
        }
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (0 != (mutex & R_BLE_GTL_MUTEX_TX))
    {
        if (TX_SUCCESS == tx_semaphore_put(&g_tx_sem))
        {
            mutex &= ~R_BLE_GTL_MUTEX_TX;
        }
    }

    if (0 != (mutex & R_BLE_GTL_MUTEX_RX))
    {
        if (TX_SUCCESS == tx_semaphore_put(&g_rx_sem))
        {
            mutex &= ~R_BLE_GTL_MUTEX_RX;
        }
    }

    if (0 != (mutex & R_BLE_GTL_MUTEX_TEI))
    {
        if (TX_SUCCESS == tx_semaphore_put(&g_uart_tei_sem))
        {
            mutex &= ~R_BLE_GTL_MUTEX_TEI;
        }
    }
#elif BSP_CFG_RTOS_USED == 0 /* Baremetal */
    if (0 != (mutex & R_BLE_GTL_MUTEX_TEI))
    {
        g_uart_tei_sem = true;
    }
    mutex = 0;
#endif

    if (0 == mutex)
    {
        status = true;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Perform hardware reset of DA1453x device
 *
 * @param[in]  reset_pin    GPIO to be used to reset external DA1453x device
 *
 **********************************************************************************************************************/
static void r_ble_gtl_hw_reset(void)
{
#if (0 == BLE_CFG_RESET_POLARITY)
    /* Generate an active low reset */
    BLE_SCK_DDR(BLE_CFG_SCK_PORT, BLE_CFG_SCK_PIN) = 1;
    BLE_SCK_DR(BLE_CFG_SCK_PORT, BLE_CFG_SCK_PIN) = 0;
    BLE_RESET_DDR(BLE_CFG_RESET_PORT, BLE_CFG_RESET_PIN) = 1;
    BLE_RESET_DR(BLE_CFG_RESET_PORT, BLE_CFG_RESET_PIN) = 0;
    r_ble_gtl_delay(R_BLE_GTL_RESET_PULSE_MS);
    BLE_RESET_DR(BLE_CFG_RESET_PORT, BLE_CFG_RESET_PIN) = 1;
#else
	/* Generate an active high reset */
    BLE_SCK_DDR(BLE_CFG_SCK_PORT, BLE_CFG_SCK_PIN) = 1;
    BLE_SCK_DR(BLE_CFG_SCK_PORT, BLE_CFG_SCK_PIN) = 0;
    BLE_RESET_DDR(BLE_CFG_RESET_PORT, BLE_CFG_RESET_PIN) = 0;
    BLE_RESET_DR(BLE_CFG_RESET_PORT, BLE_CFG_RESET_PIN) = 1;
    r_ble_gtl_delay(R_BLE_GTL_RESET_PULSE_MS);
    BLE_RESET_DR(BLE_CFG_RESET_PORT, BLE_CFG_RESET_PIN) = 0;
#endif
#if (2 == BLE_CFG_HOST_BOOT_MODE) && (DA14531_DEVICE == BLE_CFG_DA1453X_DEVICE)
/* Restore Reset-Rx pin initial status back to Input */
/* Configure pins. */
    BLE_RESET_DDR(BLE_CFG_RESET_PORT, BLE_CFG_RESET_PIN) = 1;
#if (0 == BLE_CFG_RESET_POLARITY)
    BLE_RESET_DR(BLE_CFG_RESET_PORT, BLE_CFG_RESET_PIN) = 1;
#else
    BLE_RESET_DR(BLE_CFG_RESET_PORT, BLE_CFG_RESET_PIN) = 0;
#endif
#endif
}

/*******************************************************************************************************************//**
 *  Transmit a sequence of bytes via the appropriate transport layer.
 *
 * @param[in]  p_data                   Pointer to data to be transmitted
 * @param[in]  len                      Number of bytes to be transmitted
 *
 * @retval BLE_SUCCESS                  Message transmitted successfully
 * @retval BLE_ERR_UNSPECIFIED          Transport layer failed to transmit message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_transmit(uint8_t * p_data, uint32_t len)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;

    if (0 == g_transport_api.write(g_transport_api.p_context, p_data, len))
    {
        /* Wait for transmit to complete */
        if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_TEI))
        {
            status = BLE_SUCCESS;
        }
    }

    return status;
}

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
/*******************************************************************************************************************//**
 *  Callback that is called when advertising timer expires
 *
 * @param[in]  xTimer       Timer handle
 *
 **********************************************************************************************************************/
static void r_ble_gtl_adv_timer_cb(TimerHandle_t xTimer)
{
    FSP_PARAMETER_NOT_USED(xTimer);

    /* We poll for this event when R_BLE_GTL_Execute is called */
    xEventGroupSetBits(g_events, R_BLE_GTL_ADV_TIMER_EXPIRED_EVENT);

    /* Setting this event causes app_main to call R_BLE_GTL_Execute */
    xEventGroupSetBits(g_ble_event_group_handle, BLE_EVENT_PATTERN);
}
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
/*******************************************************************************************************************//**
 *  Callback that is called when advertising timer expires
 *
 * @param[in]  context      Input to passed to function when timer expires.
 *
 **********************************************************************************************************************/
static void r_ble_gtl_adv_timer_cb(ULONG context)
{
    FSP_PARAMETER_NOT_USED(context);

    tx_event_flags_set(&g_events, R_BLE_GTL_ADV_TIMER_EXPIRED_EVENT, TX_OR);
}
#endif

#if (BSP_CFG_RTOS_USED == 5) || (BSP_CFG_RTOS_USED == 1) /* ThreadX or FreeRTOS */
/*******************************************************************************************************************//**
 *  Start advertising timer, upon expiring advertising will be stopped
 *
 * @param[in]  duration                 Timer duration in milliseconds
 *
 * @retval BLE_SUCCESS                  Timer successfully started
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficent memory to add item to queue
 * @retval BLE_ERR_UNSPECIFIED          Unable to start timer
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_adv_timer_start(uint16_t duration)
{
    ble_status_t status;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    /* Duration parameter has units of 10ms, timer uses units of ticks */
    TickType_t ticks = ((TickType_t)duration * (TickType_t)10) * portTICK_PERIOD_MS;
    g_adv_timer = xTimerCreate("AdvTimer", ticks, pdFALSE, (void *)0, r_ble_gtl_adv_timer_cb);
    if (NULL != g_adv_timer)
    {
        if (pdPASS == xTimerStart(g_adv_timer, 0))
        {
            /* Timer started! */
            status = BLE_SUCCESS;
        }
        else
        {
            /* Unable to start timer */
            xTimerDelete(g_adv_timer, 0);
            g_adv_timer = NULL;
            status = BLE_ERR_UNSPECIFIED;
        }
    }
    else
    {
        /* Unable to create timer */
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    /* Duration parameter has units of 10ms, timer uses units of ticks */
    ULONG ticks = ((ULONG)duration * TX_TIMER_TICKS_PER_SECOND) / R_BLE_GTL_ADV_TIMER_TICKS_PER_SECOND;

    if (TX_SUCCESS == tx_timer_create(&g_adv_timer, "GTL_ADV_TMR", r_ble_gtl_adv_timer_cb, 0, ticks, 
                                        0, TX_AUTO_ACTIVATE))
    {
        /* Timer started! */
        status = BLE_SUCCESS;
    }
    else
    {
        /* Unable to start timer */
        status = BLE_ERR_UNSPECIFIED;
    }
#endif

    return status;
}

/*******************************************************************************************************************//**
 *  Stop advertising timer
 *
 * @retval BLE_SUCCESS                  Timer successfully stopped
 * @retval BLE_ERR_INVALID_STATE        Timer invalid (not created or started)
 * @retval BLE_ERR_UNSPECIFIED          Unable to stop timer
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_adv_timer_stop(void)
{
    ble_status_t status;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    if (NULL != g_adv_timer)
    {
        if (pdTRUE == xTimerIsTimerActive(g_adv_timer))
        {
            if (pdTRUE == xTimerStop(g_adv_timer, 0))
            {
                /* Timer stopped! */
                status = BLE_SUCCESS;
            }
            else
            {
                /* Unable to stop timer */
                status = BLE_ERR_UNSPECIFIED;
            }
        }
        else
        {
            /* Timer not running */
            status = BLE_ERR_INVALID_STATE;
        }
        xTimerDelete(g_adv_timer, 0);
        g_adv_timer = NULL;
    }
    else
    {
        /* Timer not created */
        status = BLE_ERR_INVALID_STATE;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (TX_SUCCESS == tx_timer_deactivate(&g_adv_timer))
    {
        /* Timer stopped! */
        status = BLE_SUCCESS;
    }
    else
    {
        /* Unable to stop timer */
        status = BLE_ERR_UNSPECIFIED;
    }
    tx_timer_delete(&g_adv_timer);
#endif

    return status;
}

/*******************************************************************************************************************//**
 *  Check if advertising timer has expired
 *
 * @retval true             Expired.
 * @retval false            Not expired.
 **********************************************************************************************************************/
static bool r_ble_gtl_adv_timer_expired(void)
{
    bool expired = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
     EventBits_t events_bits = xEventGroupGetBits(g_events);

     if (R_BLE_GTL_ADV_TIMER_EXPIRED_EVENT & events_bits)
     {
         xEventGroupClearBits(g_events, R_BLE_GTL_ADV_TIMER_EXPIRED_EVENT);
         expired = true;
     }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    ULONG actual_events;
    if (TX_SUCCESS == tx_event_flags_get(&g_events, R_BLE_GTL_ADV_TIMER_EXPIRED_EVENT, TX_OR_CLEAR, 
                                                    &actual_events, TX_NO_WAIT))
    {
        expired = true;
    }
#endif

    return expired;
}
/*******************************************************************************************************************//**
 *  Initialize event signalling mechanism
 *
 * @retval true             Initialization successful.
 * @retval false            Initialization failed.
 **********************************************************************************************************************/
static bool r_ble_gtl_event_init(void)
{
    bool init = false;

#if BSP_CFG_RTOS_USED == 1 /* FreeRTOS */
    g_events = xEventGroupCreate();
    if (NULL != g_events)
    {
        init = true;
    }
#elif BSP_CFG_RTOS_USED == 5 /* ThreadX */
    if (TX_SUCCESS == tx_event_flags_create(&g_events, "EVENTS"))
    {
        init = true;
    }
#endif

    return init;
}
#endif
#if (BLE_CFG_HOST_BOOT_MODE > 0)
/*******************************************************************************************************************//**
 *  Transmit image to DA1453x.
 *
 * @retval BLE_SUCCESS            Image transmitted successfully.
 * @retval BLE_ERR_INVALID_CHAN   The handle does not indicate a SCI channel
 * @retval BLE_ERR_UNSPECIFIED    Transport layer failed to transmit image
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_transmit_image(uint8_t * p_data, uint32_t len)
{
	ble_status_t status = BLE_SUCCESS;
	uint32_t index = 0;
	uint32_t send_length = 0;

	while ((index < len) && (status == BLE_SUCCESS))
	{
		if ((len - index) > s_port_cfg->tx_size)
		{
			send_length = s_port_cfg->tx_size;
		}
		else
		{
			send_length = len - index;
		}

		if (BLE_SUCCESS != r_ble_gtl_transmit(&p_data[index], send_length))
		{
			status = BLE_ERR_UNSPECIFIED;
			break;
		}
		index += send_length;
	}

    return status;
}

/*******************************************************************************************************************//**
 *  Load an image into the DA1453x. DA1453x will automatically start executing the image once loading is complete.
 *
 * @retval BLE_SUCCESS           Image loading successful.
 * @retval BLE_ERR_UNSPECIFIED   Image loading failed.
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_boot_load_image(void)
{
    ble_status_t      status  = BLE_ERR_UNSPECIFIED;
    uint8_t           rx_crc  = 0;
    volatile uint32_t timeout = 1000;

    /* Inform UART ISR how to handle received data */
    g_booting = true;

    /* Reset DA1453x */
    r_ble_gtl_hw_reset();

    /* Wait for DA1453x bootloader to transmit STX */
    while ((R_BLE_GTL_BOOT_STX != g_rx_boot_byte) && timeout)
    {
        r_ble_gtl_delay(10);
        timeout -= 10;
    }

    if (R_BLE_GTL_BOOT_STX == g_rx_boot_byte)
    {
        r_ble_gtl_boot_header_t header;

        header.soh    = R_BLE_GTL_BOOT_SOH;
        header.length = r_ble_gtl_image_get_len();

        /* Send header information (SOH and image length in bytes) */
        if (BLE_SUCCESS == r_ble_gtl_transmit((uint8_t *)&header, sizeof(r_ble_gtl_boot_header_t)))
        {
            /* Give DA1453x time to transmit response */
            r_ble_gtl_delay(10);
            if (R_BLE_GTL_BOOT_ACK == g_rx_boot_byte)
            {
                /* Transmit image to DA1453x */
                if (BLE_SUCCESS == r_ble_gtl_transmit_image((uint8_t *)r_ble_gtl_image_get(), 
                                                    r_ble_gtl_image_get_len()))
                {
                    /* Wait for CRC from DA1453x */
                    r_ble_gtl_delay(10);

                    /* Check CRC */
                    rx_crc = g_rx_boot_byte;
                    if (rx_crc == r_ble_gtl_image_get_crc())
                    {
                        uint8_t ack = R_BLE_GTL_BOOT_ACK;
                        if (BLE_SUCCESS == r_ble_gtl_transmit(&ack, sizeof(ack)))
                        {
                            status = BLE_SUCCESS;
                        }
                    }
                }
            }
        }
    }

    g_booting = false;

    return status;
}
#endif
#if BSP_CFG_RTOS_USED == 0 /* Baremetal */
/*******************************************************************************************************************//**
 *  Initialize FIFO
 *
 * @param[in]  p_fifo   Pointer to FIFO to be initialized
 * @param[in]  p_buf    Pointer to buffer that FIFO can use as storage
 * @param[in]  size     Length of buffer storage
 *
 **********************************************************************************************************************/
static void r_ble_gtl_fifo_init(r_ble_gtl_fifo_t * p_fifo, uint8_t ** p_buf, uint32_t size)
{
    p_fifo->p_buffer = p_buf;
    p_fifo->size     = size;
    p_fifo->head     = 0;
    p_fifo->tail     = 0;
    p_fifo->items    = 0;
}

/*******************************************************************************************************************//**
 *  Check if FIFO is empty
 *
 * @param[in]  p_fifo   Pointer to FIFO to be checked
 *
 * @retval true         FIFO empty
 * @retval false        FIFO not empty
 **********************************************************************************************************************/
static bool r_ble_gtl_fifo_empty(r_ble_gtl_fifo_t * p_fifo)
{
    return (p_fifo->items == 0);
}

/*******************************************************************************************************************//**
 *  Check if FIFO is full
 *
 * @param[in]  p_fifo   Pointer to FIFO to be checked
 *
 * @retval true         FIFO full
 * @retval false        FIFO not full
 **********************************************************************************************************************/
static bool r_ble_gtl_fifo_full(r_ble_gtl_fifo_t * p_fifo)
{
    return (p_fifo->items == p_fifo->size);
}

/*******************************************************************************************************************//**
 *  Add item to the FIFO
 *
 * @param[in]  p_fifo   Pointer to FIFO
 * @param[in]  p_data   Pointer to buffer pointer that is to be added
 *
 * @retval true         Added
 * @retval false        Not added
 **********************************************************************************************************************/
static bool r_ble_gtl_fifo_put(r_ble_gtl_fifo_t * p_fifo, uint8_t ** p_data)
{
    bool added = false;

    /* FIFO put function is called from within interrupt and main loop, therefore critical section required */
    if (r_ble_gtl_fifo_full(p_fifo) == 0)
    {
        p_fifo->p_buffer[p_fifo->head] = *p_data;

        if (++p_fifo->head >= p_fifo->size)
        {
            p_fifo->head = 0;
        }
        p_fifo->items++;

        added = true;
    }

    return added;
}

/*******************************************************************************************************************//**
 *  Remove item from the FIFO
 *
 * @param[in]  p_fifo   Pointer to FIFO
 * @param[in]  p_data   Pointer to buffer pointer that is to be used by the removed item
 *
 * @retval true         Removed
 * @retval false        Not removed
 **********************************************************************************************************************/
static bool r_ble_gtl_fifo_get(r_ble_gtl_fifo_t * p_fifo, uint8_t ** p_data, uint32_t timeout_ms)
{
    bool removed = false;

    do
    {
        if (false == r_ble_gtl_fifo_empty(p_fifo))
        {
            /* FIFO get function is called from within uart receive interrupt and main loop, therefore critical
               section required */
            *p_data = p_fifo->p_buffer[p_fifo->tail];

            if (++p_fifo->tail >= p_fifo->size)
            {
                p_fifo->tail = 0;
            }
            p_fifo->items--;

            removed = true;
        }
        else
        {
            if (0 < timeout_ms)
            {
                r_ble_gtl_delay(1);
                timeout_ms--;
            }
        }
    }
    while ((0 < timeout_ms) && (false == removed));

    return removed;
}
#endif

/*******************************************************************************************************************//**
 *  Handle GAPC_BOND_REQ_IND 0x0E13 indication message. Messages might generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client connection request message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_bond_req_ind_handler(uint16_t conn_hdl, 
                                                                r_ble_gtl_gapc_bond_req_ind_t *p_param)
{
    r_ble_gtl_cb_evt_t      * p_cb_evt = NULL;

    switch (p_param->request)
    {
        case R_BLE_GTL_GAPC_PAIRING_REQ:
        {
            st_ble_gap_pairing_req_evt_t *p_gapc_bond_req_ind_param;
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_PAIRING_REQ, BLE_SUCCESS, 
                                                 sizeof(st_ble_gap_pairing_req_evt_t));

            if (NULL != p_cb_evt)
            {
                p_gapc_bond_req_ind_param = p_cb_evt->data.gap.p_param;
                p_gapc_bond_req_ind_param->conn_hdl = conn_hdl;

                p_gapc_bond_req_ind_param->auth_info.bonding = p_param->data.auth_req & R_BLE_GTL_GAP_AUTH_BOND;
                if (p_param->data.auth_req & R_BLE_GTL_GAP_AUTH_SEC)
                {
                    p_gapc_bond_req_ind_param->auth_info.pair_mode = 0x02;
                }
                else
                {
                    p_gapc_bond_req_ind_param->auth_info.pair_mode = 0x01;
                }

                if(p_param->data.auth_req & R_BLE_GTL_GAP_AUTH_MITM)
                {
                    p_gapc_bond_req_ind_param->auth_info.security = 0x02;
                }
                else
                {
                    p_gapc_bond_req_ind_param->auth_info.security = 0x01;
                }
                p_gapc_bond_req_ind_param->auth_info.ekey_size = R_BLE_GTL_GAP_SEC_KEY_LEN;
            }
            break;
        }
        
        case R_BLE_GTL_GAPC_LTK_EXCH:
        {
            st_ble_gap_conn_hdl_evt_t *p_key_exch_param;
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_EX_KEY_REQ, BLE_SUCCESS, sizeof(st_ble_gap_conn_hdl_evt_t));
            if (NULL != p_cb_evt)
            {
                p_key_exch_param = p_cb_evt->data.gap.p_param;
                p_key_exch_param->conn_hdl = conn_hdl + (uint16_t)(R_BLE_GTL_GAPC_LTK_EXCH << 8);
            }
            break;
        }

        case R_BLE_GTL_GAPC_CSRK_EXCH:
        {
            st_ble_gap_conn_hdl_evt_t *p_key_exch_param;
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_EX_KEY_REQ, BLE_SUCCESS, sizeof(st_ble_gap_conn_hdl_evt_t));
            if (NULL != p_cb_evt)
            {
                p_key_exch_param = p_cb_evt->data.gap.p_param;
                p_key_exch_param->conn_hdl = conn_hdl + (uint16_t)(R_BLE_GTL_GAPC_CSRK_EXCH << 8);
            }
            break;
        }
        
        case R_BLE_GTL_GAPC_TK_EXCH:
        {
            switch (p_param->data.tk_type)
            {

            case GAP_TK_OOB:
            {
                break;
            }

            case GAP_TK_DISPLAY:
            {
                st_ble_gap_passkey_display_evt_t *passkey_display_evt_param;
                p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_PASSKEY_DISPLAY_REQ, BLE_SUCCESS, sizeof(st_ble_gap_passkey_display_evt_t));
                if (NULL != p_cb_evt)
                {
                    passkey_display_evt_param = p_cb_evt->data.gap.p_param;
                    passkey_display_evt_param->conn_hdl = conn_hdl;
                }
                break;
            }

            case GAP_TK_KEY_ENTRY:
            {
                st_ble_gap_conn_hdl_evt_t *tk_key_entry_evt_param;
                p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_PASSKEY_ENTRY_REQ, BLE_SUCCESS, sizeof(st_ble_gap_conn_hdl_evt_t));
                if (NULL != p_cb_evt)
                {
                    tk_key_entry_evt_param = p_cb_evt->data.gap.p_param;
                    tk_key_entry_evt_param->conn_hdl = conn_hdl;
                }
                break;
            }

            case GAP_TK_KEY_CONFIRM:
            {
                /* Secure Connections*/
                st_ble_gap_num_comp_evt_t *num_comp_evt_param;
                p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_NUM_COMP_REQ, BLE_SUCCESS, sizeof(st_ble_gap_num_comp_evt_t));

                if (NULL != p_cb_evt)
                {
                    num_comp_evt_param = p_cb_evt->data.gap.p_param;
                    num_comp_evt_param->conn_hdl = conn_hdl;
                    num_comp_evt_param->numeric = (((uint32_t)p_param->tk.key[3] << 24) |
                                                   ((uint32_t)p_param->tk.key[2] << 16) |
                                                   ((uint32_t)p_param->tk.key[1] << 8) |
                                                   ((uint32_t)p_param->tk.key[0])) %
                                                  MOD_OF_TK;
                }
                break;
            }
            }
            break;
        }
        default:
        {
            /* Should not reach this point */
            break;
        }
    } // switch
    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle GAPC_BOND_CFM confirmation message.
 *
 * @param[in]  conn_hdl         Connection Handle on which message will be send
 * @param[in]  bond             Bond event type
 * @param[in]  accept           Accert or reject pairing request
 * @retval     ble_status_t
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_send_gapc_bond_cfm(uint16_t conn_hdl, r_ble_gtl_gapc_bond_t bond, bool accept, uint32_t passkey)
{
    ble_status_t status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_gapc_bond_cfm_t *p_cmd;

    uint8_t bond_index = r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, conn_hdl, 0);
    sec_ble_gap_bond_info_t *bond_info_loc_tmp = {0};
    bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(bond_index);

    switch (bond)
    {
        case R_BLE_GTL_GAPC_PAIRING_RSP:
        {
            p_cmd = (r_ble_gtl_gapc_bond_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_BOND_CFM,
                                                                    R_BLE_GTL_TASK_ID_GAPC +(uint16_t)(conn_hdl << 8),
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof(r_ble_gtl_gapc_bond_cfm_t));
            if (NULL != p_cmd)
            {
                p_cmd->request = (uint8_t)bond;

                /* GTL for DA1453X has inverted logic for the accept parameter */
                if (accept)
                {
                    p_cmd->accept = 0x00; /* BLE_GAP_PAIRING_REJECT(0x01) */
                }
                else
                {
                    p_cmd->accept = 0x01; /* BLE_GAP_PAIRING_ACCEPT(0x00) */
                }

                p_cmd->data.pairing_feat.iocap = ble_pairing_param_local.iocap;
                /* OOB is not supported*/
                p_cmd->data.pairing_feat.oob = BLE_GAP_OOB_DATA_NOT_PRESENT;
                p_cmd->data.pairing_feat.auth = (uint8_t)((ble_pairing_param_local.bonding << 0)
                        | (ble_pairing_param_local.mitm << 2)
                        | (ble_pairing_param_local.sec_conn_only <<3 ));
                p_cmd->data.pairing_feat.key_size = ble_pairing_param_local.max_key_size;

                // Need to distinguish these because GLT translates Initiator & Responder, Central & Peripheral
                p_cmd->data.pairing_feat.ikey_dist = ble_pairing_param_local.loc_key_dist;
                p_cmd->data.pairing_feat.rkey_dist = ble_pairing_param_local.rem_key_dist;
                    
                p_cmd->data.pairing_feat.sec_req = r_ble_gtl_sec_get_security_req();

                status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            }
        }
        break;

        case R_BLE_GTL_GAPC_TK_EXCH:
        {
            p_cmd = (r_ble_gtl_gapc_bond_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_BOND_CFM,
                                                                    R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof(r_ble_gtl_gapc_bond_cfm_t));

            if (NULL != p_cmd)
            {
                p_cmd->request = R_BLE_GTL_GAPC_TK_EXCH;
                /* GTL for DA1453X has inverted logic for the accept parameter */
                if (accept)
                {
                    p_cmd->accept = 0x00; /* BLE_GAP_PAIRING_REJECT(0x01) */
                }
                else
                {
                    p_cmd->accept = 0x01; /* BLE_GAP_PAIRING_ACCEPT(0x00) */
                }

                p_cmd->data.tk.key[0] = (uint8_t)passkey;
                p_cmd->data.tk.key[1] = (uint8_t)(passkey >> 8);
                p_cmd->data.tk.key[2] = (uint8_t)(passkey >> 16);
                p_cmd->data.tk.key[3] = (uint8_t)(passkey >> 24);

                status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            }
        }
        break;

        case R_BLE_GTL_GAPC_CSRK_EXCH:
        {
            /* Place holder for future functionality. Add the csrk cntr */
            p_cmd = (r_ble_gtl_gapc_bond_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_BOND_CFM,
                                                                        R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                        R_BLE_GTL_TASK_ID_GTL,
                                                                        sizeof(r_ble_gtl_gapc_bond_cfm_t));
            if (NULL != p_cmd)
            {
                p_cmd->request = (uint8_t)bond;
                p_cmd->accept = 0x01;
                memcpy(p_cmd->data.csrk.key, (const void *)r_ble_gtl_sec_get_csrk_value(), BLE_GAP_CSRK_SIZE);

                status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            }
        }
        break;

        case R_BLE_GTL_GAPC_LTK_EXCH:
        {
            /* Peripheral must provide the LTK to Central */
            p_cmd = (r_ble_gtl_gapc_bond_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_BOND_CFM,
                                                                    R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof(r_ble_gtl_gapc_bond_cfm_t));
            if (NULL != p_cmd)
            {
                /* GTL for DA1453x has inverted logic for the accept parameter */
                p_cmd->request = (uint8_t)bond; /*(Exchange LTK)*/
                p_cmd->accept = 0x01;           /*Accepted*/
                p_cmd->data.ltk.ediv = r_ble_gtl_sec_get_ediv_value();
                p_cmd->data.ltk.key_size = BLE_GAP_LTK_SIZE;
                memcpy(p_cmd->data.ltk.ltkey, (const void *)r_ble_gtl_sec_get_ltk_value(), BLE_GAP_LTK_SIZE);
                memcpy(p_cmd->data.ltk.nb, (const void *)r_ble_gtl_sec_get_rand_value(), BLE_GAP_RAND_64_BIT_SIZE);
                
                if (r_ble_gtl_sec_get_dev_role(conn_hdl) == R_BLE_GTL_PERIPHERAL_ROLE)
                {
                    //  This is needed when in Peripheral role only.Copy these to DB for future use
                    bond_info_loc_tmp->p_keys.p_keys_info.mid_info[0] = (uint8_t)(p_cmd->data.ltk.ediv >> 8);
                    bond_info_loc_tmp->p_keys.p_keys_info.mid_info[1] = (uint8_t)(p_cmd->data.ltk.ediv);
                    memcpy(&bond_info_loc_tmp->p_keys.p_keys_info.mid_info[2], (const void *)r_ble_gtl_sec_get_rand_value(), BLE_GAP_RAND_64_BIT_SIZE);
                    memcpy(bond_info_loc_tmp->p_keys.p_keys_info.enc_info, (const void *)r_ble_gtl_sec_get_ltk_value(), BLE_GAP_LTK_SIZE);                
                }
                status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
            }
            break;
        }       

        default:
        {
            status = BLE_ERR_UNSPECIFIED;
            break;
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Handle GAPC_BOND_IND indication message (0x0E15). Messages might generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client connection request message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/ 
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_bond_ind_handler(uint16_t conn_hdl, r_ble_gtl_gapc_bond_ind_t * p_param)
{
    r_ble_gtl_cb_evt_t *p_cb_evt = NULL;

    switch (p_param->info)
    {
        case R_BLE_GTL_GAPC_LTK_EXCH:
        {
            /* Secure connections, Central shares LTK */
            st_ble_gap_peer_key_info_evt_t *p_gapc_bond_ind_param;

            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_PEER_KEY_INFO, BLE_SUCCESS, sizeof(st_ble_gap_peer_key_info_evt_t));
            if (NULL != p_cb_evt)
            {
                /* Save the LTK to a temp variable*/
                memcpy(pair_key_dist_tmp.enc_info, p_param->data.ltk.ltkey, BLE_GAP_LTK_SIZE);
                p_gapc_bond_ind_param = p_cb_evt->data.gap.p_param;
                p_gapc_bond_ind_param->conn_hdl = conn_hdl;

                pair_key_dist_tmp.mid_info[0] = (uint8_t)(p_param->data.ltk.ediv >> 8);
                pair_key_dist_tmp.mid_info[1] = (uint8_t)(p_param->data.ltk.ediv);
                memcpy(&pair_key_dist_tmp.mid_info[2], p_param->data.ltk.nb, BLE_GAP_RAND_64_BIT_SIZE);

                /* Distributed keys and negotiated LTK size */
                p_gapc_bond_ind_param->key_ex_param.keys = (1 << 0); // Bit 0. Type of key, LTK is distributed in Secure Connections
                p_gapc_bond_ind_param->key_ex_param.ekey_size = BLE_GAP_LTK_SIZE;

                p_gapc_bond_ind_param->key_ex_param.p_keys_info = &pair_key_dist_tmp;
            }
            break;
        }

        case R_BLE_GTL_GAPC_IRK_EXCH:
        {
            /* Save IRK key received from remote to DB */
            memcpy(pair_key_dist_tmp.id_info, p_param->data.irk.key, BLE_GAP_IRK_SIZE);
            /* The type & Addr is public type because it is resolved in this step, even if initialy was random */
            pair_key_dist_tmp.id_addr_info[0] = p_param->data.irk.addr.type;
            memcpy(&pair_key_dist_tmp.id_addr_info[1], &p_param->data.irk.addr, BLE_BD_ADDR_LEN);

            /* Notify application */
            st_ble_gap_peer_key_info_evt_t *p_gapc_bond_ind_param;
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_PEER_KEY_INFO, BLE_SUCCESS,
                                                 sizeof(st_ble_gap_peer_key_info_evt_t));
            if (NULL != p_cb_evt)
            {
                p_gapc_bond_ind_param = p_cb_evt->data.gap.p_param;
                p_gapc_bond_ind_param->conn_hdl = conn_hdl;
                p_gapc_bond_ind_param->key_ex_param.keys = (1 << 1); // Bit 1. Type of key, IRK and Identity Address Information

                p_gapc_bond_ind_param->key_ex_param.p_keys_info = &pair_key_dist_tmp;
                p_gapc_bond_ind_param->bd_addr.type = pair_key_dist_tmp.id_addr_info[0]; // Addr type
                memcpy(p_gapc_bond_ind_param->bd_addr.addr, &pair_key_dist_tmp.id_addr_info[1], BLE_BD_ADDR_LEN);
            }
            break;
        }

        case R_BLE_GTL_GAPC_CSRK_EXCH:
        {
            /* Save CSRK key received from remote to DB */
            memcpy(pair_key_dist_tmp.sign_info, p_param->data.csrk.key, BLE_GAP_CSRK_SIZE);

            /* Notify application */
            st_ble_gap_peer_key_info_evt_t *p_gapc_bond_ind_param;
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_PEER_KEY_INFO, BLE_SUCCESS, sizeof(st_ble_gap_peer_key_info_evt_t));
            if (NULL != p_cb_evt)
            {
                p_gapc_bond_ind_param = p_cb_evt->data.gap.p_param;
                p_gapc_bond_ind_param->conn_hdl = conn_hdl;
                p_gapc_bond_ind_param->key_ex_param.keys = (1 << 2); // Bit 2. Type of key, IRK and Identity Address Information
                p_gapc_bond_ind_param->key_ex_param.p_keys_info = &pair_key_dist_tmp;
            }
            break;
        }

        case R_BLE_GTL_GAPC_PAIRING_SUCCEED:
        {
            st_ble_gap_pairing_info_evt_t *p_gapc_bond_ind_param;
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_PAIRING_COMP, BLE_SUCCESS,
                                                 sizeof(st_ble_gap_pairing_info_evt_t));

            if (NULL != p_cb_evt)
            {
                p_gapc_bond_ind_param = p_cb_evt->data.gap.p_param;
                p_gapc_bond_ind_param->conn_hdl = conn_hdl;

                if(p_param->data.auth & 0x04) // Check Authentication param, MITM
                {
                	p_gapc_bond_ind_param->auth_info.security = 0x02;  // Authenticated pairing
                }
                else
                {
                	p_gapc_bond_ind_param->auth_info.security = 0x01;  // Unauthenticated pairing
                }

                if(p_param->data.auth & 0x08) // Check Secure Connections param
                {
                    p_gapc_bond_ind_param->auth_info.pair_mode = 0x02; // The remote device requests Secure Connections.
                }
                else
                {
                    p_gapc_bond_ind_param->auth_info.pair_mode = 0x01; // The remote device requests Legacy pairing..
                }

                if(p_param->data.auth & 0x01) // Check Bonding param
                {
                    p_gapc_bond_ind_param->auth_info.bonding = 0x01;   // The remote device stores the Bonding information
                }
                else{
                    p_gapc_bond_ind_param->auth_info.bonding = 0x00;   // The remote device does not store the Bonding information.
                }

                p_gapc_bond_ind_param->auth_info.ekey_size = R_BLE_GTL_ATT_SEC_ENC_KEY_SIZE;
                // This info is not provided by GTL here.
                memset(p_gapc_bond_ind_param->bd_addr.addr, 0x00, BLE_BD_ADDR_LEN);
                p_gapc_bond_ind_param->bd_addr.type = 0x00;
            }

            break;
        }

        case R_BLE_GTL_GAPC_PAIRING_FAILED:
        {
            st_ble_gap_pairing_info_evt_t *p_gapc_bond_ind_param;
            p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_PAIRING_COMP, p_param->data.reason,
                                                 sizeof(st_ble_gap_pairing_info_evt_t));

            if (NULL != p_cb_evt)
            {
                p_gapc_bond_ind_param = p_cb_evt->data.gap.p_param;
                p_gapc_bond_ind_param->conn_hdl = conn_hdl;
            }
            break;
        }

        default:
        {
            // Should not reach this point
            break;
        }
    } // switch
    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle R_BLE_GTL_GAPC_ENCRYPT_REQ_IND indication message.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client connection request message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_encrypt_req_ind_handler(uint16_t conn_hdl, 
                                                                   r_ble_gtl_gapc_encrypt_req_ind_t *p_param)
{
    r_ble_gtl_cb_evt_t *p_cb_evt = NULL;

    st_ble_gap_ltk_req_evt_t *p_gapc_bond_req_ind_param;
    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_LTK_REQ, BLE_SUCCESS, sizeof(st_ble_gap_ltk_req_evt_t));

    if (NULL != p_cb_evt)
    {
        p_gapc_bond_req_ind_param = p_cb_evt->data.gap.p_param;
        p_gapc_bond_req_ind_param->conn_hdl = conn_hdl;
        /* Add security params*/
        p_gapc_bond_req_ind_param->ediv = p_param->ediv;

        p_gapc_bond_req_ind_param->p_peer_rand = (uint8_t*)&p_param->rand_nb;
    }
    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Handle GAPC_ENCRYPT_CFM indication message.
 *
 * @param[in]   conn_hdl         Connection Handle on which message will be send
 * @param[in]   found            Indicate if ltk is found or not
 *
 * @retval      ble_status_t
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_send_gapc_encrypt_cfm(uint16_t conn_hdl, bool found)
{
    ble_status_t status;
    r_ble_gtl_gapc_encrypt_cfm_t *p_enc_cfm;
    r_ble_gtl_gapc_connection_cfm_t *p_conn_cfm;

    uint8_t bond_index =  r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, conn_hdl, 0);
    sec_ble_gap_bond_info_t *bond_info_loc_tmp = {0};
    bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(bond_index);

    /* Allocate msg to respond to the LTK request */
    p_enc_cfm = (r_ble_gtl_gapc_encrypt_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_ENCRYPT_CFM,
                                                                    R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof(r_ble_gtl_gapc_encrypt_cfm_t));
    if (found == BLE_GAP_LTK_REQ_ACCEPT)
    {
        /* Sending the GAPC_ENCRYPT_CFM message ACCEPT*/
        p_enc_cfm->found = 0x01; // Found
        memcpy(p_enc_cfm->ltk.key, bond_info_loc_tmp->p_keys.p_keys_info.enc_info, BLE_GAP_LTK_SIZE);
        p_enc_cfm->key_size = BLE_GAP_LTK_SIZE;
        status = r_ble_gtl_msg_transmit((uint8_t *)p_enc_cfm);

        /* Security Establishment, only if LTK was found. Apply this step only in Legacy Pairing case. */
        p_conn_cfm = (r_ble_gtl_gapc_connection_cfm_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_CONNECTION_CFM,
                                                                    R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof(r_ble_gtl_gapc_connection_cfm_t));
        if (NULL != p_conn_cfm)
        {
            /* Use initial pairing params to set this response */
            p_conn_cfm->auth = (uint8_t)((ble_pairing_param_local.bonding << 0)
                    | (ble_pairing_param_local.mitm << 2)
                    | (ble_pairing_param_local.sec_conn_only << 3));
            status = r_ble_gtl_msg_transmit((uint8_t *)p_conn_cfm);
        }
    }
    else
    {
        /* Sending the GAPC_ENCRYPT_CFM message REJECT*/
        /* This action (REJECT) will force Central to delete Bond data of this device*/
        p_enc_cfm->found = 0x00; // NOT found
        memset(p_enc_cfm->ltk.key, 0x00, BLE_GAP_LTK_SIZE);
        p_enc_cfm->key_size = BLE_GAP_LTK_SIZE;
        status = r_ble_gtl_msg_transmit((uint8_t *)p_enc_cfm);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Notify that local device has replied to the LTK request from the remote device, BLE_GAP_EVENT_LTK_RSP_COMP
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client connection request message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_gapc_ltk_rsp_comp(uint16_t conn_hdl, bool found)
{
    ble_status_t status = BLE_SUCCESS;
    r_ble_gtl_cb_evt_t *p_cb_evt = NULL;
    
    st_ble_gap_ltk_rsp_evt_t *p_evt_param;
    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_LTK_RSP_COMP, BLE_SUCCESS, sizeof(st_ble_gap_ltk_rsp_evt_t));

     if (NULL != p_cb_evt)
    {
        p_evt_param = p_cb_evt->data.gap.p_param;
        p_evt_param->conn_hdl = conn_hdl;
        if(found){
            /* 0x00     | Local device replied with the stored LTK. */
            p_evt_param->response = 0x00; 
        }
        else{
            /* 0x01     | Local device rejected the LTK request, because the LTK was not found.*/
            p_evt_param->response = 0x01; 
        }
        status = r_ble_gtl_cb_evt_queue_add(p_cb_evt);
    }
    return status;   
}

/*******************************************************************************************************************//**
 *  Handle R_BLE_GTL_GAPC_ENCRYPT_IND indication message. Messages might generated a callback event.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client connection request message
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapc_encrypt_ind_handler(uint16_t conn_hdl, gapc_encrypt_ind_t *p_param)
{
    r_ble_gtl_cb_evt_t *p_cb_evt = NULL;

    st_ble_gap_enc_chg_evt_t *p_gapc_enc_ind_param;
    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_ENC_CHG, BLE_SUCCESS, sizeof(st_ble_gap_enc_chg_evt_t));

    if (NULL != p_cb_evt)
    {
        p_gapc_enc_ind_param = p_cb_evt->data.gap.p_param;
        p_gapc_enc_ind_param->conn_hdl = conn_hdl;
        p_gapc_enc_ind_param->enc_status = 0x01; /* Reaching this point, assume encryption is enabled*/
    }
    FSP_PARAMETER_NOT_USED(p_param);
    return p_cb_evt;
}

/*******************************************************************************************************************//**
 *  Request a random number using custom APP_GEN_RAND_REQ, 0xA001
 *
 * @param[in]  size             Size of the random number
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_app_get_rand_cust(uint8_t rand_size, r_ble_gtl_app_gen_rand_rsp_t *data)
{
    ble_status_t status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_app_gen_rand_req_t *p_rand_cmd;
    r_ble_gtl_app_gen_rand_rsp_t p_rand_rsp;

    if (R_BLE_GTL_DATA_LEN_TX_OCTETS_MAX >= rand_size)
    {
        if (true == r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX))
        {
            p_rand_cmd = (r_ble_gtl_app_gen_rand_req_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_APP_RAND_REQ,
                                                                                R_BLE_GTL_TASK_ID_AUX,
                                                                                R_BLE_GTL_TASK_ID_GTL,
                                                                                sizeof(r_ble_gtl_app_gen_rand_req_t));
            if (NULL != p_rand_cmd)
            {
                p_rand_cmd->rand_size = rand_size;
                status = r_ble_gtl_msg_transmit((uint8_t *)p_rand_cmd);
            }

            if (BLE_SUCCESS == status)
            {
                status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_APP_GEN_RAND_RSP,
                                                         (uint8_t *)&p_rand_rsp,
                                                         sizeof(r_ble_gtl_app_gen_rand_rsp_t),
                                                         R_BLE_GTL_MSG_RSP_TIMEOUT_MS/20);
                if (BLE_SUCCESS == status)
                {
                    memcpy(data, &p_rand_rsp, sizeof(r_ble_gtl_app_gen_rand_rsp_t));
                }
            }
            r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX);
        }
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Initiate a security request procedure
 * 
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @retval     ble_status_t
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_security_cmd(uint16_t conn_hdl)
{
    ble_status_t status = BLE_ERR_INVALID_ARG;
    gapc_security_cmd_t *p_sec_cmd;

    p_sec_cmd = (gapc_security_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_SECURITY_CMD,
                                                              R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                              R_BLE_GTL_TASK_ID_GTL,
                                                              sizeof(gapc_security_cmd_t));
    if (NULL != p_sec_cmd)
    {
        p_sec_cmd->operation = GAPC_SECURITY_REQ;
        p_sec_cmd->auth = (uint8_t)((ble_pairing_param_local.bonding << 0)
                | (ble_pairing_param_local.mitm << 2)
                | (ble_pairing_param_local.sec_conn_only << 3));
        status = r_ble_gtl_msg_transmit((uint8_t *)p_sec_cmd);
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Handle R_BLE_GTL_GAPC_SECURITY_IND indication message (0x0E1B). Device can receive this as Central role.
 *
 * @param[in]  conn_hdl         Handle of connection on which message was received
 * @param[in]  p_param          Pointer to buffer containing received GAP client connection request message
 *
 * @retval NULL                 No callback event generated by message processing
 **********************************************************************************************************************/
static void r_ble_gtl_gapc_security_ind_handler(uint16_t conn_hdl, gapc_security_ind_t *p_param)
{
    FSP_PARAMETER_NOT_USED(p_param);
    sec_ble_gap_bond_info_t *bond_info_loc_tmp = {0};

    uint8_t bond_index = r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, conn_hdl, 0);
    if (INVALID_IDX != bond_index)
    {
        bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(bond_index);
        if (bond_info_loc_tmp->p_auth_info.bonding == 0x00)
        {
            // No bonding available, initiate pairing.
            r_ble_gtl_send_bond_cmd(conn_hdl);
        }
        else
        {
            // Bonding available, encryption should be handled upon connection establishment. Not here.
        }
    }
}

/*******************************************************************************************************************//**
 *  Send start connection command (R_BLE_GTL_GAPM_START_CONNECTION_CMD) to DA145xx device.
 *
 * @param[in]  p_param          Pointer to connection parameters
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_send_start_connection_cmd(st_ble_gap_create_conn_param_t * p_param)
{
    ble_status_t  status;
    r_ble_gtl_gapm_start_connection_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gapm_start_connection_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_START_CONNECTION_CMD,
                                                                           R_BLE_GTL_TASK_ID_GAPM,
                                                                           R_BLE_GTL_TASK_ID_GTL,
                                                                           sizeof (r_ble_gtl_gapm_start_connection_cmd_t) +
                                                                           sizeof(struct r_ble_gtl_gap_bdaddr) * 1);
    if (NULL != p_cmd)
    {
        p_cmd->op.code = R_BLE_GTL_GAPM_OP_CONNECTION_AUTO; // If used scannnig preceeds and this takes time.
        // p_cmd->op.code = R_BLE_GTL_GAPM_OP_CONNECTION_DIRECT; // Shorter execution
        p_cmd->op.addr_src = R_BLE_GTL_GAPM_STATIC_ADDR;
        p_cmd->op.state = 0x00;
        p_cmd->scan_interval = p_param->p_conn_param_1M->scan_intv;
        p_cmd->scan_window = p_param->p_conn_param_1M->scan_window;
        p_cmd->con_intv_min = p_param->p_conn_param_1M->p_conn_param->conn_intv_min;
        p_cmd->con_intv_max = p_param->p_conn_param_1M->p_conn_param->conn_intv_max;
        p_cmd->con_latency =  p_param->p_conn_param_1M->p_conn_param->conn_latency;
        p_cmd->superv_to = p_param->p_conn_param_1M->p_conn_param->sup_to;
        p_cmd->ce_len_min = R_BLE_GTL_MIN_CONNECTION_CE_LENGTH;//p_param->p_conn_param_1M->p_conn_param->min_ce_length;
        p_cmd->ce_len_max = R_BLE_GTL_MAX_CONNECTION_CE_LENGTH;//p_param->p_conn_param_1M->p_conn_param->max_ce_length;
        p_cmd->nb_peers = 1;
        memcpy(p_cmd->peers[0].addr.addr, p_param->remote_bd_addr, sizeof(r_ble_gtl_bd_addr_t));
        p_cmd->peers[0].type = p_param->remote_bd_addr_type;
        /* Use this info on conn ind */
        memcpy(&int_conn_addr[0], p_param->remote_bd_addr, sizeof(r_ble_gtl_bd_addr_t));
        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;
}

/*******************************************************************************************************************//**
 *  Send start scanning command (R_BLE_GTL_GAPM_START_SCAN_CMD) to DA145xx device.
 *
 * @param[in]  p_scan_param          Pointer to scan parameters
 * @param[in]  p_scan_enable         Pointer to scan filter parameters
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapm_send_scan_start_cmd(st_ble_gap_scan_param_t * p_scan_param, st_ble_gap_scan_on_t * p_scan_enable)
{
    ble_status_t                      status;
    r_ble_gtl_gapm_start_scan_cmd_t * p_cmd;

    p_cmd = (r_ble_gtl_gapm_start_scan_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_START_SCAN_CMD,
                                                                      R_BLE_GTL_TASK_ID_GAPM,
                                                                      R_BLE_GTL_TASK_ID_GTL,
                                                                      sizeof (r_ble_gtl_gapm_start_scan_cmd_t));
    if (NULL != p_cmd)
    {
        if (p_scan_param->p_phy_param_1M->scan_type == BLE_GAP_SCAN_ACTIVE)
        {
            p_cmd->op.code = R_BLE_GTL_GAPM_OP_SCAN_ACTIVE;
        }
        else
        {
            p_cmd->op.code = R_BLE_GTL_GAPM_OP_SCAN_PASSIVE;
        }
        p_cmd->op.addr_src = R_BLE_GTL_GAPM_STATIC_ADDR;
        p_cmd->op.state = 0x0000;
        p_cmd->interval = p_scan_param->p_phy_param_1M->scan_intv;
        p_cmd->window = p_scan_param->p_phy_param_1M->scan_window;
        p_cmd->mode = R_BLE_GTL_GAP_GEN_DISCOVERY;
        p_cmd->filt_policy = R_BLE_GTL_SCAN_ALLOW_ADV_ALL;
        p_cmd->filter_duplic = p_scan_enable->filter_dups ;
        p_cmd->pad1 = 0;

        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);

    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }

    return status;

}


ble_status_t R_BLE_GTL_GAP_CreateConn(st_ble_gap_create_conn_param_t * p_param)
{
    ble_status_t                      status   = BLE_SUCCESS;

    status = r_ble_gtl_gapm_send_start_connection_cmd(p_param);

    if (BLE_SUCCESS == status)
    {
        g_dev_params.state |=  R_BLE_GTL_DEV_STATE_CONNECTING;
    }
    else
    {
    
    }

    return status;
}

ble_status_t R_BLE_GTL_GAP_CancelConn(void)
{
    ble_status_t                      status   = BLE_SUCCESS;

    status = r_ble_gtl_gapm_send_cancel_cmd((uint8_t)R_BLE_GTL_GAPM_OP_CONNECTION_AUTO);

    if (BLE_SUCCESS == status)
    {
        g_dev_params.state &= (uint8_t)~R_BLE_GTL_DEV_STATE_CONNECTING;

        /* No parameters are passed with this event type */
        r_ble_gtl_cb_evt_t * p_cb_evt = r_ble_gtl_cb_evt_allocate (BLE_GAP_EVENT_CONN_CANCEL_COMP, status, 0);
        if (NULL != p_cb_evt)
        {
            status = r_ble_gtl_cb_evt_queue_add (p_cb_evt);
        }
        else
        {
            status = BLE_ERR_MEM_ALLOC_FAILED;
        }
    }
    else
    {
       
    }

    return status;
}


ble_status_t R_BLE_GTL_GAP_StartScan(st_ble_gap_scan_param_t * p_scan_param, st_ble_gap_scan_on_t * p_scan_enable)
{
#if BLE_ABS_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(NULL != gp_instance_ctrl, BLE_ERR_INVALID_STATE);
    FSP_ERROR_RETURN(R_BLE_GTL_OPEN == g_gtl_open, BLE_ERR_INVALID_STATE);
#endif

    ble_status_t                      status   = BLE_SUCCESS;
    status = r_ble_gtl_gapm_send_scan_start_cmd(p_scan_param, p_scan_enable);

    if (status == BLE_SUCCESS)
    {
          r_ble_gtl_cb_evt_t * p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_SCAN_ON, BLE_SUCCESS, 0);
          if (NULL != p_cb_evt)
          {
              r_ble_gtl_cb_evt_queue_add(p_cb_evt);
          }
    }


    return status;
}

/*******************************************************************************************************************//**
 *  Handles the advertise report received by the DA145xx GTL host.
 *
 * @param[in]  p_param  Pointer to contents of the advertise report.
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapm_adv_report_ind_handler(r_ble_gtl_gapm_adv_report_ind_t * p_param)
{
    r_ble_gtl_cb_evt_t          * p_cb_evt = NULL;
    st_ble_gap_adv_rept_evt_t   * p_gapm_adv_report_ind_param;

    p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_ADV_REPT_IND , BLE_SUCCESS, sizeof(st_ble_gap_adv_rept_evt_t));

    if ((NULL != p_cb_evt))
    {

        st_ble_gap_adv_rept_t * p_advertise_report = r_ble_gtl_malloc(sizeof(st_ble_gap_adv_rept_t));
        uint8_t * p_adv_address = r_ble_gtl_malloc(BLE_BD_ADDR_LEN);
        uint8_t * p_adv_data    = r_ble_gtl_malloc(R_BLE_GTL_ADV_DATA_LEN);

        if ((NULL != p_adv_address) && (NULL != p_adv_data) && (NULL != p_advertise_report))
        {

            p_gapm_adv_report_ind_param = p_cb_evt->data.gap.p_param;
            p_gapm_adv_report_ind_param->param.p_adv_rpt = p_advertise_report;

            p_gapm_adv_report_ind_param->adv_rpt_type = 0x00;  /* Advertising  Report */
            p_gapm_adv_report_ind_param->param.p_adv_rpt->num = 1; /* Always 1 message received*/
            p_gapm_adv_report_ind_param->param.p_adv_rpt->adv_type = p_param->report.evt_type; /* Connectable/Non-connectable, Directed/undirected */
            p_gapm_adv_report_ind_param->param.p_adv_rpt->addr_type = p_param->report.adv_addr_type; /* Public or Random */
            memcpy(p_adv_address, p_param->report.adv_addr.addr, BLE_BD_ADDR_LEN);
            p_gapm_adv_report_ind_param->param.p_adv_rpt->p_addr = p_adv_address;
            p_gapm_adv_report_ind_param->param.p_adv_rpt->len = p_param->report.data_len;
            p_gapm_adv_report_ind_param->param.p_adv_rpt->rssi = p_param->report.rssi;

            memset(p_adv_data, 0, R_BLE_GTL_ADV_DATA_LEN);
            memcpy(p_adv_data, p_param->report.data, p_param->report.data_len);
            p_gapm_adv_report_ind_param->param.p_adv_rpt->p_data = p_adv_data;
        }
        else
        {
            r_ble_gtl_free(p_advertise_report);
            r_ble_gtl_free(p_adv_address);
            r_ble_gtl_free(p_adv_data);
            r_ble_gtl_cb_evt_free(p_cb_evt);
        }

    }

    return p_cb_evt;
}

/*******************************************************************************************************************//**
 * Handles the GAPM messages received by the DA145xx GTL host.
 *
 * @param[in]  p_gtl_msg        Pointer to buffer containing received GTL/GAP message (including header)
 *
 * @retval NULL                 No callback event generated by message processing
 * @retval r_ble_gtl_cb_evt_t * Pointer to callback event generated as a result of processing the message.
 **********************************************************************************************************************/
static r_ble_gtl_cb_evt_t * r_ble_gtl_gapm_handler(uint8_t * p_gtl_msg)
{
    r_ble_gtl_cb_evt_t  * p_cb_evt      = NULL;
    r_ble_gtl_msg_hdr_t * p_gtl_msg_hdr = (r_ble_gtl_msg_hdr_t *)p_gtl_msg;

    switch (p_gtl_msg_hdr->msg_id)
    {
        case R_BLE_GTL_GAPM_ADV_REPORT_IND:
        {
            r_ble_gtl_gapm_adv_report_ind_t * p_adv_report_param = (r_ble_gtl_gapm_adv_report_ind_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            p_cb_evt = r_ble_gtl_gapm_adv_report_ind_handler(p_adv_report_param);
            break;
        }    
        case R_BLE_GTL_GAPM_CMP_EVT:
        {
            r_ble_gtl_gapm_cmp_evt_t * p_cmp_evt_param = (r_ble_gtl_gapm_cmp_evt_t *)&p_gtl_msg[sizeof(r_ble_gtl_msg_hdr_t)];
            if ((p_cmp_evt_param->operation == R_BLE_GTL_GAPM_OP_SCAN_PASSIVE) && (p_cmp_evt_param->status == R_BLE_GTL_GAP_ERR_TIMEOUT))
            {
                p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_SCAN_OFF, BLE_SUCCESS, 0);
            }
            else if (p_cmp_evt_param->operation == R_BLE_GTL_GAPM_OP_CONNECTION_AUTO)
            {
                uint8_t status = BLE_SUCCESS;
                if (p_cmp_evt_param->status != BLE_SUCCESS)
                {
                   status = BLE_ERR_INVALID_OPERATION; 
                }
                p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_CREATE_CONN_COMP, status, 0);
            }
            else
            {
            }

            break;
        }
        default:
        {
            /* Unknown message, do nothing */
            break;
        }
    }

    return p_cb_evt;
}

ble_status_t R_BLE_GTL_GAP_StopScan( void )
{
    ble_status_t status = r_ble_gtl_gapm_send_cancel_cmd((uint8_t)R_BLE_GTL_GAPM_OP_SCAN_PASSIVE);
    if (status == BLE_SUCCESS)
    {
        r_ble_gtl_cb_evt_t * p_cb_evt = r_ble_gtl_cb_evt_allocate(BLE_GAP_EVENT_SCAN_OFF, BLE_SUCCESS, 0);
        if (NULL != p_cb_evt)
        {
            r_ble_gtl_cb_evt_queue_add(p_cb_evt);
        }
    }

    return status;
}


// CENTRAL_ROLE
/***********************************************************************************************************************
 *  Initiate a pairing when device has the Central role request procedure
 * 
 * @param[in]  conn_hdl         Handle of connection
 * @retval BLE_SUCCESS          Command transmitted successfully
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_send_bond_cmd(uint16_t conn_hdl)
{
    ble_status_t status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_gapc_bond_cmd_t *p_bond_cmd;

    p_bond_cmd = (r_ble_gtl_gapc_bond_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_BOND_CMD,
                                                                    R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof(r_ble_gtl_gapc_bond_cmd_t));
    if (NULL != p_bond_cmd)
    {
        p_bond_cmd->operation = GAPC_BOND_CMD;
        p_bond_cmd->pairing.iocap = ble_pairing_param_local.iocap;
        p_bond_cmd->pairing.oob = BLE_GAP_OOB_DATA_NOT_PRESENT;
        p_bond_cmd->pairing.auth = (uint8_t)((ble_pairing_param_local.bonding << 0) | (ble_pairing_param_local.mitm << 2) | (ble_pairing_param_local.sec_conn_only <<3 ));
        p_bond_cmd->pairing.key_size = ble_pairing_param_local.max_key_size;

        /* Since this is Central role these are set in normal order */
        p_bond_cmd->pairing.ikey_dist = ble_pairing_param_local.loc_key_dist;
        p_bond_cmd->pairing.rkey_dist = ble_pairing_param_local.rem_key_dist;
        p_bond_cmd->pairing.sec_req = r_ble_gtl_sec_get_security_req();

		status = r_ble_gtl_msg_transmit((uint8_t *)p_bond_cmd);
    }

    return status;
}

/***********************************************************************************************************************
 *  Initiate a encryption when device has the Central role
 * 
 * @param[in]  conn_hdl         Handle of connection
 * @retval BLE_SUCCESS          Command transmitted successfully
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_send_enc_cmd(uint16_t conn_hdl)
{
    ble_status_t status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_gapc_encrypt_cmd_t *p_enc_cmd;

    uint8_t bond_index = r_ble_gtl_sec_lut_table_info(GET_ENTRY, NULL, conn_hdl, 0);
    sec_ble_gap_bond_info_t *bond_info_loc_tmp = {0};
    bond_info_loc_tmp = r_ble_gtl_sec_get_rem_bond_data(bond_index);

    p_enc_cmd = (r_ble_gtl_gapc_encrypt_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPC_ENCRYPT_CMD,
                                                                    R_BLE_GTL_TASK_ID_GAPC + (uint16_t)(conn_hdl << 8),
                                                                    R_BLE_GTL_TASK_ID_GTL,
                                                                    sizeof(r_ble_gtl_gapc_encrypt_cmd_t));
    if (NULL != p_enc_cmd)
    {
        p_enc_cmd->operation = GAPC_ENCRYPT;
        p_enc_cmd->ltk.key_size = BLE_GAP_LTK_SIZE;
        /// EDIV
        p_enc_cmd->ltk.ediv = (uint16_t)(bond_info_loc_tmp->p_keys.p_keys_info.mid_info[1]) + (uint16_t)(bond_info_loc_tmp->p_keys.p_keys_info.mid_info[0] << 8);
        /// LTK
        memcpy(&p_enc_cmd->ltk.ltkey, bond_info_loc_tmp->p_keys.p_keys_info.enc_info, BLE_GAP_LTK_SIZE);
        /// RAND
        memcpy(&p_enc_cmd->ltk.nb, &bond_info_loc_tmp->p_keys.p_keys_info.mid_info[2], BLE_GAP_RAND_64_BIT_SIZE);
        status = r_ble_gtl_msg_transmit((uint8_t *)p_enc_cmd);
    }
    return status;
}
// CENTRAL_ROLE



/*********************************************************************************************************************
 *  Send Random Address Resolution to the DA14xxx.
 *
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  operation                Type of information to read
 *
 * @retval BLE_SUCCESS                  Command transmitted successfully
 * @retval BLE_ERR_MEM_ALLOC_FAILED     Insufficient memory to create command message
 **********************************************************************************************************************/
static ble_status_t r_ble_gtl_gapc_send_resolv_addr_cmd(uint16_t conn_hdl,
                                                        uint8_t *peer_addr,
                                                        uint8_t num_of_rec,
                                                        uint8_t *irks)
{
    ble_status_t status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_gapm_resolv_addr_cmd_t *p_cmd;
    FSP_PARAMETER_NOT_USED(conn_hdl);

    p_cmd = (r_ble_gtl_gapm_resolv_addr_cmd_t *)r_ble_gtl_msg_allocate(R_BLE_GTL_GAPM_RESOLV_ADDR_CMD,
                                                                       R_BLE_GTL_TASK_ID_GAPM,
                                                                       R_BLE_GTL_TASK_ID_GTL,
                                                                       sizeof(r_ble_gtl_gapm_resolv_addr_cmd_t) + (uint16_t)(num_of_rec* BLE_GAP_IRK_SIZE) );
    if (NULL != p_cmd)
    {
        p_cmd->operation = 0x17; // operation = GAPM_RESOLV_ADDR
        p_cmd->nb_key = num_of_rec;
        memcpy(p_cmd->addr, peer_addr, BLE_GAP_ID_ADDR_SIZE - 1);
        memcpy(p_cmd->irk, irks, num_of_rec * BLE_GAP_IRK_SIZE);
        status = r_ble_gtl_msg_transmit((uint8_t *)p_cmd);
    }
    else
    {
        status = BLE_ERR_MEM_ALLOC_FAILED;
    }
    return status;
}
/**********************************************************************************************************************
 *  Resolve address from connected event
 * @param[in]  conn_hdl                 Handle of connection on which request should be made.
 * @param[in]  peer_addr                Peer's address
 * @param[in]  num_of_rec               Number of IRKs
 * @param[in]  irks                     IRKs
 * @param[out] addr_solved_rsp          Address resolved response
 * @retval BLE_SUCCESS          Command transmitted successfully
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_resolve_address_from_connected_evt_cmd(uint16_t conn_hdl,
                                                              uint8_t *peer_addr,
                                                              uint8_t num_of_rec,
                                                              uint8_t *irks,
                                                              r_ble_gtl_gapm_addr_solved_ind_t *addr_solved_rsp)
{
    ble_status_t status = BLE_ERR_UNSPECIFIED;
    r_ble_gtl_gapm_addr_solved_ind_t addr_solved_rsp_tmp;

    /* Check if peer's address is resolvable,case of Static Random Address */
    if ((peer_addr[5] & RAND_STATIC_ADDR) != RAND_RSLV_ADDR)
    {
        return status;
    }

    /* Send the Command, ignore mutex use since we are already inside a receive routine from r_ble_gtl_gapc_connection_req_handler */

    r_ble_gtl_mutex_take(R_BLE_GTL_MUTEX_RX);
    status = r_ble_gtl_gapc_send_resolv_addr_cmd(conn_hdl, peer_addr, num_of_rec, irks);
    if (BLE_SUCCESS == status)
    {
        /* Wait for cmd response */
        status = r_ble_gtl_msg_wait_for_response(R_BLE_GTL_GAPM_ADDR_SOLVED_IND,
                                                 (uint8_t *)&addr_solved_rsp_tmp,
                                                 sizeof(r_ble_gtl_gapm_addr_solved_ind_t),
                                                 R_BLE_GTL_MSG_RSP_TIMEOUT_MS/20);
        if (BLE_SUCCESS == status)
        {
            /* Wait for cmd complete status */
            status = r_ble_gtl_msg_wait_for_cmd_complete(R_BLE_GTL_GAPM_CMP_EVT,
                                                         R_BLE_GTL_GAPM_OP_RESOLV_ADDR,
                                                         R_BLE_GTL_GAP_ERR_NO_ERROR,
                                                         R_BLE_GTL_MSG_CMD_CMP_TIMEOUT_MS/20);
            if (BLE_SUCCESS == status)
            {
                *addr_solved_rsp = addr_solved_rsp_tmp;
            }
        }
    }
    r_ble_gtl_mutex_give(R_BLE_GTL_MUTEX_RX); // release from R_BLE_GTL_Execute
    return status;
}

/**********************************************************************************************************************
 * Set public BD address command
 * @param[in]  p_addr           Public type of BD address
 *
 * @retval BLE_SUCCESS          Command transmitted successfully
 **********************************************************************************************************************/
 ble_status_t r_ble_gtl_aux_set_bd_address_cmd(st_ble_dev_addr_t * p_addr)
{
    ble_status_t status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_gapc_set_bd_address_cmd_t *p_set_addr_cmd;
    r_ble_gtl_gapc_set_bd_address_cmp_t addr_rsp;

    p_set_addr_cmd = (r_ble_gtl_gapc_set_bd_address_cmd_t*) r_ble_gtl_msg_allocate (R_BLE_GTL_AUX_SET_BD_ADDRESS_CMD,
    R_BLE_GTL_TASK_ID_AUX,
                                                                          R_BLE_GTL_TASK_ID_GTL,
                                                                          sizeof(r_ble_gtl_gapc_set_bd_address_cmd_t));
    if (NULL != p_set_addr_cmd)
    {
        memcpy ((void*) &p_set_addr_cmd->addr, p_addr, sizeof(st_ble_dev_addr_t));

        status = r_ble_gtl_msg_transmit ((uint8_t*) p_set_addr_cmd);

        if (BLE_SUCCESS == status)
        {

            status = r_ble_gtl_msg_wait_for_response (R_BLE_GTL_AUX_SET_BD_ADDRESS_CFM, (uint8_t*) &addr_rsp,
                                                      sizeof(r_ble_gtl_gapc_set_bd_address_cmp_t),
                                                      R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
        }
    }

    return status;
}

/**********************************************************************************************************************
 * Set DA1453x in any of the three sleep modes
 * @param[in] sleep_mode  set BLE_VS_SLEEP_OFF, BLE_VS_EXTENDED_SLEEP, BLE_VS_DEEP_SLEEP or BLE_VS_HIBERNATION
 * @param[in] ram_retention retain RAM during Deep Sleep or Hibernation. Set BLE_VS_RAM_POWER_ON or BLE_VS_RAM_POWER_OFF
 * @param[in] pin_selection Set 0-11 for port 0(P00..P011). Used only for deep sleep/hibernation modes  
 *
 * @retval BLE_SUCCESS          Command transmitted successfully
 **********************************************************************************************************************/
ble_status_t r_ble_gtl_aux_set_sleep_mode_cmd(uint8_t sleep_mode, uint8_t ram_retention, uint8_t pin_selection)
{
    ble_status_t status = BLE_ERR_INVALID_ARG;
    r_ble_gtl_gapc_set_sleep_mode_cmd_t *p_set_sleep_mode_cmd;
    r_ble_gtl_gapc_set_sleep_mode_cmp_t sleep_rsp;

    p_set_sleep_mode_cmd = (r_ble_gtl_gapc_set_sleep_mode_cmd_t *) r_ble_gtl_msg_allocate (R_BLE_GTL_AUX_SET_SLEEP_MODE_CMD,
                                                                                R_BLE_GTL_TASK_ID_AUX,
                                                                                R_BLE_GTL_TASK_ID_GTL,
                                                                                sizeof(r_ble_gtl_gapc_set_sleep_mode_cmd_t));
    if (NULL != p_set_sleep_mode_cmd)
    {
        p_set_sleep_mode_cmd->pin_selection = pin_selection;
        p_set_sleep_mode_cmd->ram_retention = ram_retention;
        p_set_sleep_mode_cmd->sleep_mode = sleep_mode;

        status = r_ble_gtl_msg_transmit ((uint8_t*) p_set_sleep_mode_cmd);

        if (BLE_SUCCESS == status)
        {

            status = r_ble_gtl_msg_wait_for_response (R_BLE_GTL_AUX_SET_SLEEP_MODE_CFM, (uint8_t*) &sleep_rsp,
                                                      sizeof(r_ble_gtl_gapc_set_sleep_mode_cmp_t),
                                                      R_BLE_GTL_MSG_RSP_TIMEOUT_MS);
        }
    }

    return status;
}

