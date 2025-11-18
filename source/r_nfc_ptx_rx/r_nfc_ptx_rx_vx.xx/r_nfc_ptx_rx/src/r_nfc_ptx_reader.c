/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_nfc_ptx_reader.c
 * Description  : API functions definition for PTX.
 *********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_nfc_ptx_common.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define NFC_PTX_ZERO                (0)
#define NFC_PTX_SHUTDOWN_TEMP       (223U)

/* ASCII conversion from string of "NFC" */
#define NFC_PTX_OPEN                (0x4e4643ULL)  //It stands for "NFC"
#define NFC_PTX_CLOSED              (0)

/* Default timeout-values for for RAW-protocols (e.g. T2T, T3T, ...) and standard-protocols (ISO-/NFC-DEP) */
#define NFC_PTX_TIMEOUT_RAW         (200U)   // Application-timeout for raw-protocols
#define NFC_PTX_TIMEOUT_PROTOCOL    (50000U) // Application-timeout for standard-protocols

/***********************************************************************************************************************
 * Extern variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Static Globals
 **********************************************************************************************************************/


/* Only perform calibration once per power cycle */
static bool g_start_temperature_sensor_calibration = true;

/***********************************************************************************************************************
 * Local function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public Functions Implementation
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  Initializes the NFC IoT Reader.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_cfg                Pointer to NFC IoT Reader configuration structure.
 *
 * @retval NFC_SUCCESS              Function completed successfully.
 * @retval NFC_ERR_ASSERTION        Assertion error occurred.
 * @retval NFC_ERR_INVALID_DATA     NFC SDK initialization data was incomplete.
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_Open(nfc_reader_ptx_ctrl_t * const 				p_ctrl,
							     nfc_reader_ptx_cfg_t const * const      	p_cfg)
{
	/* Do parameter checking */
#if (1 == NFC_CFG_PARAM_CHECKING_ENABLED)
	FSP_ERROR_RETURN(NULL != p_ctrl, NFC_ERR_ASSERTION);
	FSP_ERROR_RETURN(NULL != p_cfg, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NFC_PTX_OPEN != p_ctrl->open, NFC_ERR_ALREADY_OPEN);
#endif

    p_ctrl->p_cfg = p_cfg;

    /* Define IoT Reader parameters */
    ptxIoTRd_InitPars_t            nfc_reader_init_params;
    ptxIoTRd_TempSense_Params_t    nfc_reader_temp_sensor;
    ptxIoTRd_ComInterface_Params_t nfc_reader_interface;

    /* Set all initial values to 0 */
    memset(&nfc_reader_init_params, NFC_PTX_ZERO, sizeof(ptxIoTRd_InitPars_t));
    memset(&nfc_reader_temp_sensor, NFC_PTX_ZERO, sizeof(ptxIoTRd_TempSense_Params_t));
    memset(&nfc_reader_interface, NFC_PTX_ZERO, sizeof(ptxIoTRd_ComInterface_Params_t));

    /* Check if temperature calibration was performed yet */
    if (true == g_start_temperature_sensor_calibration)
    {
        /* Calibration required. Set ambient temperature and expected shutdown temperature threshold. */
        nfc_reader_temp_sensor.Calibrate = 1;
        nfc_reader_temp_sensor.Tambient  = NFC_CFG_TEMP_SENSOR_AMBIENT;
        nfc_reader_temp_sensor.Tshutdown = NFC_CFG_TEMP_SENSOR_SHUTDOWN;

        /* Calibration will take place now. Doesn't need to be done anymore if Open is successful. */
        g_start_temperature_sensor_calibration = false;
    }
    else
    {
        /* Calibration not needed, it has already been done. Provide compensated threshold temperature word. */
        nfc_reader_temp_sensor.Tshutdown = NFC_PTX_SHUTDOWN_TEMP;
    }

    /* Initial parameters for temperature sensor are ready. */
    nfc_reader_init_params.TemperatureSensor = &nfc_reader_temp_sensor;
    nfc_reader_init_params.ComInterface      = &nfc_reader_interface;

    /* Initiate IoT-Reader System. */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxIoTRd_Init(p_cfg->iot_reader_context, &nfc_reader_init_params),
    				 NFC_ERR_INVALID_DATA);

    p_ctrl->open       = NFC_PTX_OPEN;
    p_ctrl->state_flag = NFC_PTX_IDLE;

    return NFC_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Initiates discovery of NFC tags.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 *
 * @retval NFC_SUCCESS              Function completed successfully.
 * @retval NFC_ERR_ASSERTION        Assertion error occurred.
 * @retval NFC_ERR_NOT_OPEN         Module is not opened yet.
 * @retval NFC_ERR_INVALID_STATE    NFC module is not in the idle state.
 * @retval NFC_ERR_INVALID_DATA     NFC Discovery parameters were invalid or discovery was not started.
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_StartDiscovery(nfc_reader_ptx_ctrl_t * const p_ctrl)
{
    /* Do parameter checking */
#if (1 == NFC_CFG_PARAM_CHECKING_ENABLED)
	FSP_ERROR_RETURN(NULL != p_ctrl, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NFC_PTX_OPEN == p_ctrl->open, NFC_ERR_NOT_OPEN);

    /* Check device is idle before initiating discovery */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_PTX_IDLE, NFC_ERR_INVALID_STATE);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* RF-Discover configuration */
    ptxIoTRd_DiscConfig_t nfc_reader_disc_config;
    memset(&nfc_reader_disc_config, NFC_PTX_ZERO, sizeof(ptxIoTRd_DiscConfig_t));

    nfc_reader_disc_config.PollTypeA            = NFC_CFG_POLL_TYPE_A;
    nfc_reader_disc_config.PollTypeB            = NFC_CFG_POLL_TYPE_B;
    nfc_reader_disc_config.PollTypeF212         = NFC_CFG_POLL_TYPE_F;
    nfc_reader_disc_config.PollTypeV            = NFC_CFG_POLL_TYPE_V;
    nfc_reader_disc_config.IdleTime             = NFC_CFG_IDLE_TIME_MS;
    nfc_reader_disc_config.PollTypeADeviceLimit = NFC_CFG_DEVICE_LIMIT;
    nfc_reader_disc_config.PollTypeBDeviceLimit = NFC_CFG_DEVICE_LIMIT;
    nfc_reader_disc_config.PollTypeVDeviceLimit = NFC_CFG_DEVICE_LIMIT;
    nfc_reader_disc_config.PollTypeFDeviceLimit = NFC_CFG_DEVICE_LIMIT;

    /* Check that at least one poll type option was selected (e.g. Type-A) */
    FSP_ERROR_RETURN(
        nfc_reader_disc_config.PollTypeA || nfc_reader_disc_config.PollTypeB || nfc_reader_disc_config.PollTypeF212 || nfc_reader_disc_config.PollTypeV,
        NFC_ERR_INVALID_DATA);

    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxIoTRd_Initiate_Discovery(p_cfg->iot_reader_context, &nfc_reader_disc_config),
                     NFC_ERR_INVALID_DATA);

    p_ctrl->state_flag = NFC_PTX_POLLING;

    return NFC_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Gets the status information on the provided status identifier (system, discovery, etc.).
 *  Used during polling to confirm a card was discovered.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  status_type          Status identifier for target info.
 * @param[in]  p_status             Pointer to location to store NFC chip status flag.
 *
 * @retval NFC_SUCCESS              Function completed successfully.
 * @retval NFC_ERR_ASSERTION        Assertion error occurred.
 * @retval NFC_ERR_NOT_OPEN         Module is not opened yet.
 * @retval NFC_ERR_INVALID_STATE    NFC module is not in the polling state.
 * @retval NFC_ERR_INVALID_ARGUMENT Invalid input parameters to NFC Status function.
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_GetStatus(nfc_reader_ptx_ctrl_t * const 		  p_ctrl,
                                       ptxIoTRd_StatusType_t                  status_type,
                                       uint8_t * const                        p_status)
{
    /* Do parameter checking */
#if (1 == NFC_CFG_PARAM_CHECKING_ENABLED)
    FSP_ERROR_RETURN(NULL != p_ctrl, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NULL != p_status, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NFC_PTX_OPEN == p_ctrl->open, NFC_ERR_NOT_OPEN);
#endif

    if (StatusType_Discover == status_type)
    {
        /* Check device is polling before checking for discovery */
        FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_PTX_POLLING, NFC_ERR_INVALID_STATE);
    }

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxIoTRd_Get_Status_Info(p_cfg->iot_reader_context, status_type, p_status),
                     NFC_ERR_INVALID_ARGUMENT);

    /* Confirm results if discovery status is being checked */
    if (StatusType_Discover == status_type)
    {
        switch (*p_status)
        {
            case RF_DISCOVER_STATUS_NO_CARD:
            {
                /* If there is no card, do nothing */
                break;
            }

            case RF_DISCOVER_STATUS_CARD_ACTIVE:
            {
                /* If a single card was discovered, set state to Activated */
                p_ctrl->state_flag = NFC_PTX_ACTIVATED;
                break;
            }

            case RF_DISCOVER_STATUS_DISCOVER_RUNNING:
            {
                /* Wait for discovery to finish */
                break;
            }

            case RF_DISCOVER_STATUS_DISCOVER_DONE:
            {
                /* If multiple cards were detected, set to Discovered */
                p_ctrl->state_flag = NFC_PTX_DISCOVERED;
                break;
            }

            default:
            {
                return NFC_ERR_INVALID_STATE;
                break;
            }
        }
    }

    return NFC_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Gets the internal card registry.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  pp_card_registry     Pointer to card registry for discovered cards.
 *
 * @retval NFC_SUCCESS              Function completed successfully.
 * @retval NFC_ERR_ASSERTION        Assertion error occurred.
 * @retval NFC_ERR_INVALID_ARGUMENT Invalid input parameters to NFC registry function.
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_GetCardRegistry(nfc_reader_ptx_ctrl_t * const p_ctrl,
                                            ptxIoTRd_CardRegistry_t       ** pp_card_registry)
{
    /* Do parameter checking */
#if (1 == NFC_CFG_PARAM_CHECKING_ENABLED)
    FSP_ERROR_RETURN(NULL != p_ctrl, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NULL != pp_card_registry, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NFC_PTX_OPEN == p_ctrl->open, NFC_ERR_NOT_OPEN);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Get reference to the internal card registry */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxIoTRd_Get_Card_Registry(p_cfg->iot_reader_context, pp_card_registry),
                     NFC_ERR_INVALID_ARGUMENT);

    return NFC_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Gets the details of the discovered card and connects to it.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_card_params        Parameters of the card to be activated.
 * @param[in]  protocol             The NFC protocol of the card to be activated.
 *
 * @retval NFC_SUCCESS              Function completed successfully.
 * @retval NFC_ERR_ASSERTION        Assertion error occurred.
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_ActivateCard(nfc_reader_ptx_ctrl_t * const p_ctrl,
                                          ptxIoTRd_CardParams_t * const          p_card_params,
                                          ptxIoTRd_CardProtocol_t                protocol)
{
#if (1 == NFC_CFG_PARAM_CHECKING_ENABLED)
    FSP_ERROR_RETURN(NULL != p_ctrl, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NULL != p_card_params, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NFC_PTX_OPEN == p_ctrl->open, NFC_ERR_NOT_OPEN);

    /* Check device is polling before checking for discovery */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_PTX_DISCOVERED, NFC_ERR_INVALID_STATE);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Activate the card that was discovered */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxIoTRd_Activate_Card(p_cfg->iot_reader_context, p_card_params, protocol),
                     NFC_ERR_INVALID_ARGUMENT);

    /* Update state flag to Activated if successful */
    p_ctrl->state_flag = NFC_PTX_ACTIVATED;

    return NFC_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Sends and receives data to/from the activated card.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  p_data_info          Pointer to the NFC TX/RX data.
 *
 * @retval NFC_SUCCESS              Function completed successfully.
 * @retval NFC_ERR_ASSERTION        Assertion error occurred.
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_DataExchange(nfc_reader_ptx_ctrl_t * const 			p_ctrl,
                                         nfc_reader_ptx_data_info_t * const     p_data_info)
{
#if (1 == NFC_CFG_PARAM_CHECKING_ENABLED)
    FSP_ERROR_RETURN(NULL != p_ctrl, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NULL != p_data_info, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NFC_PTX_OPEN == p_ctrl->open, NFC_ERR_NOT_OPEN);

    /* Check device is activated before exchanging data */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_PTX_ACTIVATED, NFC_ERR_INVALID_STATE);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Activate the card that was discovered */
    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxIoTRd_Data_Exchange(p_cfg->iot_reader_context, p_data_info->p_tx_buf, p_data_info->tx_length,
                                            p_data_info->p_rx_buf, &p_data_info->rx_length, NFC_PTX_TIMEOUT_RAW),
                     NFC_ERR_INVALID_ARGUMENT);

    return NFC_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Deactivates the activated card to return to the desired state (idle, discovery, etc.).
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 * @param[in]  return_state         Expectation for end state of NFC state machine.
 *
 * @retval NFC_SUCCESS              Function completed successfully.
 * @retval NFC_ERR_ASSERTION        Assertion error occurred.
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_ReaderDeactivation(nfc_reader_ptx_ctrl_t * const 		  p_ctrl,
                                               nfc_reader_ptx_return_state_t          return_state)
{
#if (1 == NFC_CFG_PARAM_CHECKING_ENABLED)
	FSP_ERROR_RETURN(NULL != p_ctrl, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NFC_PTX_OPEN == p_ctrl->open, NFC_ERR_NOT_OPEN);

    /* Check device is active before deactivation */
    FSP_ERROR_RETURN(p_ctrl->state_flag == NFC_PTX_ACTIVATED, NFC_ERR_INVALID_STATE);
#endif
    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Deactivate the activated card */
    FSP_ERROR_RETURN(ptxStatus_Success ==
                     ptxIoTRd_Reader_Deactivation(p_cfg->iot_reader_context, (uint8_t) return_state),
                     NFC_ERR_INVALID_ARGUMENT);

    /* Change the state depending on expected return state */
    switch (return_state)
    {
        case NFC_PTX_RETURN_IDLE:
        {
            /* Set the state flag to idle */
            p_ctrl->state_flag = NFC_PTX_IDLE;
            break;
        }

        case NFC_PTX_RETURN_DISCOVER:
        {
            /* Set the state flag to discover */
            p_ctrl->state_flag = NFC_PTX_POLLING;
            break;
        }

        case NFC_PTX_RETURN_SLEEP:
        {
            /* Handled internally by IoT Reader */
            break;
        }

        case NFC_PTX_RETURN_NO_RF_RESET:
        {
            /* Handled internally by IoT Reader */
            break;
        }

        default:
        {
            return NFC_ERR_INVALID_STATE;
            break;
        }
    }

    return NFC_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Trigger software reset if there is no response from NFC.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 *
 * @retval NFC_SUCCESS              Function completed successfully.
 * @retval NFC_ERR_ASSERTION        Assertion error occurred.
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_SWReset(nfc_reader_ptx_ctrl_t * const p_ctrl)
{
#if (1 == NFC_CFG_PARAM_CHECKING_ENABLED)
	FSP_ERROR_RETURN(NULL != p_ctrl, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NFC_PTX_OPEN == p_ctrl->open, NFC_ERR_NOT_OPEN);
#endif
    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Trigger software reset */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxIoTRd_SWReset(p_cfg->iot_reader_context),
                     NFC_ERR_INVALID_ARGUMENT);
    return NFC_SUCCESS;
}

/*******************************************************************************************************************//**
 *  Closes the FSP NFC module and resets all variables.
 *
 * @param[in]  p_ctrl               Pointer to NFC IoT Reader control structure.
 *
 * @retval NFC_SUCCESS              Function completed successfully.
 * @retval NFC_ERR_ASSERTION        Assertion error occurred.
 * @retval NFC_ERR_NOT_OPEN         Close being called before the module is Open.
 **********************************************************************************************************************/
nfc_err_t R_NFC_PTX_Close (nfc_reader_ptx_ctrl_t * const p_ctrl)
{
#if (1 == NFC_CFG_PARAM_CHECKING_ENABLED)
	FSP_ERROR_RETURN(NULL != p_ctrl, NFC_ERR_ASSERTION);
    FSP_ERROR_RETURN(NFC_PTX_OPEN == p_ctrl->open, NFC_ERR_NOT_OPEN);
#endif

    nfc_reader_ptx_cfg_t const * p_cfg = p_ctrl->p_cfg;

    /* Reset values to initial state */
    p_ctrl->open       = NFC_PTX_CLOSED;
    p_ctrl->state_flag = NFC_PTX_IDLE;

    /* Deinit reader */
    FSP_ERROR_RETURN(ptxStatus_Success == ptxIoTRd_Deinit(p_cfg->iot_reader_context),
                     NFC_ERR_INVALID_ARGUMENT);
    return NFC_SUCCESS;
}



