/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_nfc_ptx_if.h
 * Description  : API functions definition for PTX.
 *********************************************************************************************************************/
/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "platform.h"
#include "ptx_IOT_READER.h"
#include "r_nfc_ptx_rx_config.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef R_NFC_PTX_IF_H_
#define R_NFC_PTX_IF_H_

/**
 * @def NFC_VERSION_MAJOR
 * NFC Module Major Version.
 */
#define NFC_VERSION_MAJOR      (1)

/**
 * @def NFC_VERSION_MINOR
 * NFC Module Minor Version.
 */
#define NFC_VERSION_MINOR      (00)

/******************************************************************************************************************//**
 * @typedef e_nfc_err
 **********************************************************************************************************************/
typedef enum e_nfc_err
{
    NFC_SUCCESS = 0x0000,

    /* common error code */
	NFC_ERR_ASSERTION         	= 0x0001,
	NFC_ERR_INVALID_DATA        = 0x0002,
	NFC_ERR_NOT_OPEN	        = 0x0003,
	NFC_ERR_ALREADY_OPEN		= 0x0004,
	NFC_ERR_INVALID_STATE       = 0x0005,
	NFC_ERR_INVALID_ARGUMENT    = 0x0006
} nfc_err_t ;

/*******************************************************************************************************************//**
 **********************************************************************************************************************/

/** NFC state machine status */
typedef enum e_nfc_reader_ptx_state
{
    NFC_PTX_IDLE       = 0x01,  ///< Idle state before starting discovery
    NFC_PTX_POLLING    = 0x02,  ///< Polling state for discovering tags
    NFC_PTX_DISCOVERED = 0x03,  ///< Discovered state for tags that were found
    NFC_PTX_ACTIVATED  = 0x04,  ///< Activated state for activating a discovered tag
    NFC_PTX_ERROR_TEMP = 0x05, ///< Error state for temperature sensor
    NFC_PTX_ERROR_OVERCURRENT = 0x06, ///< Error state for overcurrent
    NFC_PTX_ERROR_RF   = 0x07, ///< Error state for RF error
} nfc_reader_ptx_state_t;

/** NFC de-activation return state */
typedef enum e_nfc_reader_ptx_return_state
{
    NFC_PTX_RETURN_IDLE               = PTX_IOTRD_RF_DEACTIVATION_TYPE_IDLE,               ///< Rf-Deactivation Type 0 - Turn off RF-field
    NFC_PTX_RETURN_DISCOVER           = PTX_IOTRD_RF_DEACTIVATION_TYPE_DISCOVER,           ///< Rf-Deactivation Type 1 - Restart RF-Discovery
    NFC_PTX_RETURN_SLEEP              = PTX_IOTRD_RF_DEACTIVATION_TYPE_SLEEP,              ///< Rf-Deactivation Type 2 - Put remote device to sleep
    NFC_PTX_RETURN_SLEEP_NON_BLOCKING = PTX_IOTRD_RF_DEACTIVATION_TYPE_SLEEP_NON_BLOCKING, ///< Rf-Deactivation Type 3 - Put remote device to sleep (non-blocking)
    NFC_PTX_RETURN_NO_RF_RESET        = PTX_IOTRD_RF_DEACTIVATION_TYPE_NO_RF_RESET,        ///< Rf-Deactivation Type 4 - Common RF Deactivate but no Field Reset
    NFC_PTX_RETURN_IDLE_PROTOCOL      = PTX_IOTRD_RF_DEACTIVATION_TYPE_IDLE_PROTOCOL,      ///< Rf-Deactivation Type 5 - Use protocol-specific Deactivation, IDLE afterwards
    NFC_PTX_RETURN_DISCOVER_PROTOCOL  = PTX_IOTRD_RF_DEACTIVATION_TYPE_DISCOVER_PROTOCOL,  ///< Rf-Deactivation Type 6 - Use protocol-specific Deactivation, RF-Discovery started afterwards
} nfc_reader_ptx_return_state_t;

/** NFC Configuration */
typedef struct st_nfc_reader_ptx_cfg
{
    bool    poll_type_a;                             ///< Flag to indicate enabling discovery for Type-A tags.
    bool    poll_type_b;                             ///< Flag to indicate enabling discovery for Type-B tags.
    bool    poll_type_f;                             ///< Flag to indicate enabling discovery for Type-F tags.
    bool    poll_type_v;                             ///< Flag to indicate enabling discovery for Type-V tags.
    uint8_t device_limit;                            ///< Defines the maximum number of devices that can be connected at once.

    uint32_t idle_time_ms;                           ///< RF-Discovery Loop. Idle time between polling cycles in milliseconds.
    uint8_t  temp_sensor_calibrate;                  ///< Flag to enable/disable temperature sensor calibration
    uint8_t  temp_sensor_shutdown;                   ///< Expected thermal shutdown threshold value.
    uint8_t  temp_sensor_ambient;                    ///< Ambient temperature at which temperature sensor calibration takes place.

    ptxIoTRd_t                * iot_reader_context;    ///< Instance of the NFC SDK IoT Reader main structure.
} nfc_reader_ptx_cfg_t;

/** NFC data exchange packet parameters */
typedef struct st_nfc_reader_ptx_data_info
{
    uint8_t * p_tx_buf;                ///< Pointer to buffer holding data to send.
    uint32_t  tx_length;               ///< Length of data to send.
    uint8_t * p_rx_buf;                ///< Pointer to buffer for data to receive.
    uint32_t  rx_length;               ///< Length of data to receive.
} nfc_reader_ptx_data_info_t;

typedef struct st_nfc_reader_ptx_ctrl
{
	uint32_t               		 open;        ///< Flag to indicate if NFC has been opened.
	nfc_reader_ptx_state_t 		 state_flag;  ///< Flag to track Idle/discovered/activated.

	nfc_reader_ptx_cfg_t const * p_cfg;
} nfc_reader_ptx_ctrl_t;



/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_Open(nfc_reader_ptx_ctrl_t * const 			 p_ctrl,
                                 nfc_reader_ptx_cfg_t const * const      p_cfg);
nfc_err_t R_NFC_PTX_StartDiscovery(nfc_reader_ptx_ctrl_t * const p_ctrl);
nfc_err_t R_NFC_PTX_GetStatus(nfc_reader_ptx_ctrl_t * const 	 p_ctrl,
                                      ptxIoTRd_StatusType_t              status_type,
                                      uint8_t * const                    p_status);
nfc_err_t R_NFC_PTX_GetCardRegistry(nfc_reader_ptx_ctrl_t * const p_ctrl,
                                            ptxIoTRd_CardRegistry_t             ** pp_card_registry);
nfc_err_t R_NFC_PTX_ActivateCard(nfc_reader_ptx_ctrl_t * const p_ctrl,
                                         ptxIoTRd_CardParams_t * const          p_card_params,
                                         ptxIoTRd_CardProtocol_t                protocol);
nfc_err_t R_NFC_PTX_DataExchange(nfc_reader_ptx_ctrl_t * const p_ctrl,
                                         nfc_reader_ptx_data_info_t * const     p_data_info);
nfc_err_t R_NFC_PTX_ReaderDeactivation(nfc_reader_ptx_ctrl_t * const p_ctrl,
                                               nfc_reader_ptx_return_state_t          return_state);
nfc_err_t R_NFC_PTX_SWReset(nfc_reader_ptx_ctrl_t * const p_ctrl);
nfc_err_t R_NFC_PTX_Close(nfc_reader_ptx_ctrl_t * const p_ctrl);

#endif /* R_NFC_PTX_IF_H_ */
