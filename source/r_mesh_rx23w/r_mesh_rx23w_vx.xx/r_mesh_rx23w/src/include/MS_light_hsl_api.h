/**
 * \file MS_light_hsl_api.h
 *
 * \brief This file defines the Mesh Light HSL Model Application Interface
 * - includes Data Structures and Methods for both Server and Client.
 */

/*
 * Copyright (C) 2017. Mindtree Ltd.
 * All rights reserved.
 */

#ifndef _H_MS_LIGHT_HSL_API_
#define _H_MS_LIGHT_HSL_API_


/* --------------------------------------------- Header File Inclusion */
#include "MS_access_api.h"


/* --------------------------------------------- Global Definitions */
/**
 * \defgroup light_hsl_module Light HSL Model (LIGHT_HSL)
 * \ingroup lighting_models
 * \{
 *  \brief This section describes the interfaces & APIs offered by the EtherMind
 *  Mesh Light HSL Model (LIGHT_HSL) module to the Application.
 */

/* --------------------------------------------- Data Types/ Structures */
/**
 *  \defgroup light_hsl_cb Application Callback
 *  \{
 *  \brief This section describes the Notification Callback Interfaces offered
 *  to the application by EtherMind Mesh Light HSL Model Layer.
 */

/**
 * Light HSL Server application Asynchronous Notification Callback.
 *
 * Light HSL Server calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] msg_raw       Uninterpreted/raw received message.
 * \param [in] req_type      Requested message type.
 * \param [in] state_params  Model specific state parameters.
 * \param [in] ext_params    Additional parameters.
 */
typedef API_RESULT (* MS_LIGHT_HSL_SERVER_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
            MS_ACCESS_MODEL_REQ_MSG_RAW        * msg_raw,
            MS_ACCESS_MODEL_REQ_MSG_T          * req_type,
            MS_ACCESS_MODEL_STATE_PARAMS       * state_params,
            MS_ACCESS_MODEL_EXT_PARAMS         * ext_params

        ) DECL_REENTRANT;

#ifdef MS_MODEL_SERVER_EXTENDED_INTERFACE
/**
 * Light HSL Setup Server application Asynchronous Notification Callback.
 *
 * Light HSL setup Server calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] msg_raw       Uninterpreted/raw received message.
 * \param [in] req_type      Requested message type.
 * \param [in] state_params  Model specific state parameters.
 * \param [in] ext_params    Additional parameters.
 */
typedef API_RESULT (* MS_LIGHT_HSL_SETUP_SERVER_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
            MS_ACCESS_MODEL_REQ_MSG_RAW        * msg_raw,
            MS_ACCESS_MODEL_REQ_MSG_T          * req_type,
            MS_ACCESS_MODEL_STATE_PARAMS       * state_params,
            MS_ACCESS_MODEL_EXT_PARAMS         * ext_params

        ) DECL_REENTRANT;
#endif /* MS_MODEL_SERVER_EXTENDED_INTERFACE */

/**
 * Light HSL Hue Server application Asynchronous Notification Callback.
 *
 * Light HSL Hue Server calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] msg_raw       Uninterpreted/raw received message.
 * \param [in] req_type      Requested message type.
 * \param [in] state_params  Model specific state parameters.
 * \param [in] ext_params    Additional parameters.
 */
typedef API_RESULT (* MS_LIGHT_HSL_HUE_SERVER_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
            MS_ACCESS_MODEL_REQ_MSG_RAW        * msg_raw,
            MS_ACCESS_MODEL_REQ_MSG_T          * req_type,
            MS_ACCESS_MODEL_STATE_PARAMS       * state_params,
            MS_ACCESS_MODEL_EXT_PARAMS         * ext_params

        ) DECL_REENTRANT;

/**
 * Light HSL Saturation Server application Asynchronous Notification Callback.
 *
 * Light HSL Saturation Server calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] msg_raw       Uninterpreted/raw received message.
 * \param [in] req_type      Requested message type.
 * \param [in] state_params  Model specific state parameters.
 * \param [in] ext_params    Additional parameters.
 */
typedef API_RESULT (* MS_LIGHT_HSL_SATURATION_SERVER_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
            MS_ACCESS_MODEL_REQ_MSG_RAW        * msg_raw,
            MS_ACCESS_MODEL_REQ_MSG_T          * req_type,
            MS_ACCESS_MODEL_STATE_PARAMS       * state_params,
            MS_ACCESS_MODEL_EXT_PARAMS         * ext_params

        ) DECL_REENTRANT;

/**
 * Light HSL Client application Asynchronous Notification Callback.
 *
 * Light HSL Client calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] opcode        Opcode.
 * \param [in] data_param    Data associated with the event if any or NULL.
 * \param [in] data_len      Size of the event data. 0 if event data is NULL.
 */
typedef API_RESULT (* MS_LIGHT_HSL_CLIENT_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT * ctx,
            UINT32                   opcode,
            UCHAR                  * data_param,
            UINT16                   data_len
        ) DECL_REENTRANT;
/** \} */

/**
 * \defgroup light_hsl_defines Defines
 * \{
 * \brief This section describes the various Defines in EtherMind
 * Mesh Light HSL Model Layer.
 */

/**
 *  \defgroup light_hsl_structures Structures
 *  \{
 *  \brief This section describes the various Data-Types and Structures in
 *  EtherMind Light HSL Model Layer.
 */

/**
 * Light HSL Set message parameters.
 */
typedef struct MS_light_hsl_set_struct
{
    /** The target value of the Light HSL Lightness state */
    UINT16 hsl_lightness;

    /** The target value of the Light HSL Hue state */
    UINT16 hsl_hue;

    /** The target value of the Light HSL Saturation state */
    UINT16 hsl_saturation;

    /** Transaction Identifier */
    UCHAR  tid;

    /**
     * Transition Time is a 1-octet value that consists of two fields:
     * - a 2-bit bit field representing the step resolution
     * - a 6-bit bit field representing the number of transition steps.
     *
     * Field                      | Size (bits) | Description
     * ---------------------------|-------------|----------------
     * Transition Number of Steps | 6           | The number of Steps
     * Transition Step Resolution | 2           | The resolution of the Default Transition
     *                                          | Number of Steps field
     */
    UCHAR  transition_time;

    /** Message execution delay in 5 milliseconds steps */
    UCHAR  delay;

    /** Flag: To represent if optional Transaction time and Delay fields are valid */
    UCHAR optional_fields_present;

} MS_LIGHT_HSL_SET_STRUCT;

/**
 * Light HSL Status message parameters.
 */
typedef struct MS_light_hsl_status_struct
{
    /** The present value of the Light HSL Lightness state */
    UINT16 hsl_lightness;

    /** The present value of the Light HSL Hue state */
    UINT16 hsl_hue;

    /** The present value of the Light HSL Saturation state */
    UINT16 hsl_saturation;

    /**
     * Remaining Time is a 1-octet value that consists of two fields:
     * - a 2-bit bit field representing the step resolution
     * - a 6-bit bit field representing the number of transition steps.
     *
     * Field                      | Size (bits) | Description
     * ---------------------------|-------------|----------------
     * Transition Number of Steps | 6           | The number of Steps
     * Transition Step Resolution | 2           | The resolution of the Default Transition
     *                                          | Number of Steps field
     */
    UCHAR  remaining_time;

    /** Flag: To represent if optional field Remaining Time is valid */
    UCHAR optional_fields_present;

} MS_LIGHT_HSL_STATUS_STRUCT;

/**
 * Light HSL Target Status message parameters.
 */
typedef struct MS_light_hsl_target_status_struct
{
    /** The target value of the Light HSL Lightness state */
    UINT16 hsl_lightness_target;

    /** The target value of the Light HSL Hue state */
    UINT16 hsl_hue_target;

    /** The target Light HSL Saturation state */
    UINT16 hsl_saturation_target;

    /**
     * Remaining Time is a 1-octet value that consists of two fields:
     * - a 2-bit bit field representing the step resolution
     * - a 6-bit bit field representing the number of transition steps.
     *
     * Field                      | Size (bits) | Description
     * ---------------------------|-------------|----------------
     * Transition Number of Steps | 6           | The number of Steps
     * Transition Step Resolution | 2           | The resolution of the Default Transition
     *                                          | Number of Steps field
     */
    UCHAR  remaining_time;

    /** Flag: To represent if optional field Remaining Time is valid */
    UCHAR optional_fields_present;

} MS_LIGHT_HSL_TARGET_STATUS_STRUCT;

/**
 * Light HSL Default Set message parameters.
 */
typedef struct MS_light_hsl_default_set_struct
{
    /** The value of the Light Lightness Default state */
    UINT16 lightness;

    /** The value of the Light HSL Hue Default state */
    UINT16 hue;

    /** The value of the Light HSL Saturation Default state */
    UINT16 saturation;

} MS_LIGHT_HSL_DEFAULT_SET_STRUCT;

/**
 * Light HSL Default Status message parameters.
 */
typedef struct MS_light_hsl_default_status_struct
{
    /** The value of the Light Lightness Default state */
    UINT16 lightness;

    /** The value of the Light HSL Hue Default state */
    UINT16 hue;

    /** The value of the Light HSL Saturation Default state */
    UINT16 saturation;

} MS_LIGHT_HSL_DEFAULT_STATUS_STRUCT;

/**
 * Light HSL Range Set message parameters.
 */
typedef struct MS_light_hsl_range_set_struct
{
    /** The value of the Hue Range Min field of the Light HSL Hue Range state */
    UINT16 hue_range_min;

    /** The value of the Hue Range Max field of the Light HSL Hue Range state */
    UINT16 hue_range_max;

    /** The value of the Saturation Range Min field of the Light HSL Saturation Range state */
    UINT16 saturation_range_min;

    /** The value of the Saturation Range Max field of the Light HSL Saturation Range state */
    UINT16 saturation_range_max;

} MS_LIGHT_HSL_RANGE_SET_STRUCT;

/**
 * Light HSL Range Status message parameters.
 */
typedef struct MS_light_hsl_range_status_struct
{
    /** Status Code for the requesting message. */
    UCHAR  status_code;

    /** The value of the Hue Range Min field of the Light HSL Hue Range state */
    UINT16 hue_range_min;

    /** The value of the Hue Range Max field of the Light HSL Hue Range state */
    UINT16 hue_range_max;

    /** The value of the Saturation Range Min field of the Light HSL Saturation Range state */
    UINT16 saturation_range_min;

    /** The value of the Saturation Range Max field of the Light HSL Saturation Range state */
    UINT16 saturation_range_max;

} MS_LIGHT_HSL_RANGE_STATUS_STRUCT;

/**
 * Light HSL Hue Set message parameters.
 */
typedef struct MS_light_hsl_hue_set_struct
{
    /** The target value of the Light HSL Hue state. */
    UINT16 hue;

    /** Transaction Identifier */
    UCHAR  tid;

    /**
     * Transition Time is a 1-octet value that consists of two fields:
     * - a 2-bit bit field representing the step resolution
     * - a 6-bit bit field representing the number of transition steps.
     *
     * Field                      | Size (bits) | Description
     * ---------------------------|-------------|----------------
     * Transition Number of Steps | 6           | The number of Steps
     * Transition Step Resolution | 2           | The resolution of the Default Transition
     *                                          | Number of Steps field
     */
    UCHAR  transition_time;

    /** Message execution delay in 5 milliseconds steps */
    UCHAR  delay;

    /** Flag: To represent if optional Transaction time and Delay fields are valid */
    UCHAR optional_fields_present;

} MS_LIGHT_HSL_HUE_SET_STRUCT;

/**
 * Light HSL Hue Status message parameters.
 */
typedef struct MS_light_hsl_hue_status_struct
{
    /** The present value of the Light HSL Hue state */
    UINT16 present_hue;

    /** The target value of the Light HSL Hue state (Optional) */
    UINT16 target_hue;

    /**
     * Remaining Time is a 1-octet value that consists of two fields:
     * - a 2-bit bit field representing the step resolution
     * - a 6-bit bit field representing the number of transition steps.
     *
     * Field                      | Size (bits) | Description
     * ---------------------------|-------------|----------------
     * Transition Number of Steps | 6           | The number of Steps
     * Transition Step Resolution | 2           | The resolution of the Default Transition
     *                                          | Number of Steps field
     */
    UCHAR  remaining_time;

    /** Flag: To represent if optional fields Target Hue and Remaining Time are valid */
    UCHAR optional_fields_present;

} MS_LIGHT_HSL_HUE_STATUS_STRUCT;

/**
 * Light HSL Saturation Set message parameters.
 */
typedef struct MS_light_hsl_saturation_set_struct
{
    /** The target value of the Light HSL Saturation state. */
    UINT16 saturation;

    /** Transaction Identifier */
    UCHAR  tid;

    /**
     * Transition Time is a 1-octet value that consists of two fields:
     * - a 2-bit bit field representing the step resolution
     * - a 6-bit bit field representing the number of transition steps.
     *
     * Field                      | Size (bits) | Description
     * ---------------------------|-------------|----------------
     * Transition Number of Steps | 6           | The number of Steps
     * Transition Step Resolution | 2           | The resolution of the Default Transition
     *                                          | Number of Steps field
     */
    UCHAR  transition_time;

    /** Message execution delay in 5 milliseconds steps */
    UCHAR  delay;

    /** Flag: To represent if optional Transaction time and Delay fields are valid */
    UCHAR optional_fields_present;

} MS_LIGHT_HSL_SATURATION_SET_STRUCT;

/**
 * Light HSL Saturation Status message parameters.
 */
typedef struct MS_light_hsl_saturation_status_struct
{
    /** The present value of the Light HSL Saturation state. */
    UINT16 present_saturation;

    /** The target value of the Light HSL Saturation state. (Optional) */
    UINT16 target_saturation;

    /**
     * Remaining Time is a 1-octet value that consists of two fields:
     * - a 2-bit bit field representing the step resolution
     * - a 6-bit bit field representing the number of transition steps.
     *
     * Field                      | Size (bits) | Description
     * ---------------------------|-------------|----------------
     * Transition Number of Steps | 6           | The number of Steps
     * Transition Step Resolution | 2           | The resolution of the Default Transition
     *                                          | Number of Steps field
     */
    UCHAR  remaining_time;

    /** Flag: To represent if optional fields Target Saturation and Remaining Time are valid */
    UCHAR optional_fields_present;

} MS_LIGHT_HSL_SATURATION_STATUS_STRUCT;

/** \} */

/** \} */

/* --------------------------------------------- Function */
/**
 * \defgroup light_hsl_api_defs API Definitions
 * \{
 * \brief This section describes the various APIs exposed by
 * EtherMind Mesh Light HSL Model Layer to the Application.
 */

/**
 * \defgroup light_hsl_ser_api_defs Light HSL Server API Definitions
 * \{
 * \brief This section describes the EtherMind Mesh Light HSL Server
 * Model APIs.
 */

/**
 * \name Light HSL Server Interfaces
 * \{
 */

#ifndef MS_MODEL_SERVER_EXTENDED_INTERFACE
/**
 *  \brief API to initialize Light_HSL Server model
 *
 *  \par Description
 *  This is to initialize Light_HSL Server model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] hsl_model_handle
 *                   Model identifier associated with the Light HSL model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in, out] hsl_setup_model_handle
 *                   Model identifier associated with the Light HSL Setup model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] hsl_appl_cb    Application Callback to be used by the Light_HSL Server.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_server_init
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE    element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * hsl_model_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * hsl_setup_model_handle,
               /* IN */    MS_LIGHT_HSL_SERVER_CB      hsl_appl_cb
           );
#else /* MS_MODEL_SERVER_EXTENDED_INTERFACE */
/**
 *  \brief API to initialize Light_HSL Server model
 *
 *  \par Description
 *  This is to initialize Light_HSL Server model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] hsl_model_handle
 *                   Model identifier associated with the Light HSL model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in, out] hsl_setup_model_handle
 *                   Model identifier associated with the Light HSL Setup model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] hsl_appl_cb    Application Callback to be used by the Light_HSL Server.
 *
 *  \param [in] hsl_setup_appl_cb    Application Callback to be used by the Light_HSL_Setup Server.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_server_init_ext
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE       element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE       * hsl_model_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE       * hsl_setup_model_handle,
               /* IN */    MS_LIGHT_HSL_SERVER_CB         hsl_appl_cb,
               /* IN */    MS_LIGHT_HSL_SETUP_SERVER_CB   hsl_setup_appl_cb
           );
#endif /* MS_MODEL_SERVER_EXTENDED_INTERFACE */

/**
 *  \brief API to initialize Light_HSL_Hue Server model
 *
 *  \par Description
 *  This is to initialize Light_HSL_Hue Server model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] model_handle
 *                   Model identifier associated with the model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] appl_cb    Application Callback to be used by the Light_HSL_Hue Server.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_hue_server_init
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE    element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * model_handle,
               /* IN */    MS_LIGHT_HSL_HUE_SERVER_CB appl_cb
           );

/**
 *  \brief API to initialize Light_HSL_Saturation Server model
 *
 *  \par Description
 *  This is to initialize Light_HSL_Saturation Server model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] model_handle
 *                   Model identifier associated with the model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] appl_cb    Application Callback to be used by the Light_HSL_Saturation Server.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_saturation_server_init
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE    element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * model_handle,
               /* IN */    MS_LIGHT_HSL_SATURATION_SERVER_CB appl_cb
           );

/**
 *  \brief API to send reply or to update state change
 *
 *  \par Description
 *  This is to send reply for a request or to inform change in state.
 *
 * \param [in] ctx                     Context of the message.
 * \param [in] current_state_params    Model specific current state parameters.
 * \param [in] target_state_params     Model specific target state parameters (NULL: to be ignored).
 * \param [in] remaining_time          Time from current state to target state (0: to be ignored).
 * \param [in] ext_params              Additional parameters (NULL: to be ignored).
 * \param [in] reply                   If unicast response to be sent
 * \param [in] publish                 If state to be published
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#ifndef MS_MODEL_SERVER_EXTENDED_INTERFACE
API_RESULT MS_light_hsl_server_state_update
           (
               /* IN */ MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
               /* IN */ MS_ACCESS_MODEL_STATE_PARAMS       * current_state_params,
               /* IN */ MS_ACCESS_MODEL_STATE_PARAMS       * target_state_params,
               /* IN */ UINT16                               remaining_time,
               /* IN */ MS_ACCESS_MODEL_EXT_PARAMS         * ext_params,
               /* IN */ UCHAR                                reply,
               /* IN */ UCHAR                                publish
           );
#else /* MS_MODEL_SERVER_EXTENDED_INTERFACE */
API_RESULT MS_light_hsl_server_state_update_ext
           (
               /* IN */ MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
               /* IN */ MS_ACCESS_MODEL_STATE_PARAMS       * current_state_params,
               /* IN */ MS_ACCESS_MODEL_STATE_PARAMS       * target_state_params,
               /* IN */ UINT16                               remaining_time,
               /* IN */ MS_ACCESS_MODEL_EXT_PARAMS         * ext_params,
               /* IN */ UCHAR                                reply,
               /* IN */ UCHAR                                publish
           );
#endif /* MS_MODEL_SERVER_EXTENDED_INTERFACE */

/**
 *  \brief API to send reply or to update state change
 *
 *  \par Description
 *  This is to send reply for a request or to inform change in state.
 *
 * \param [in] ctx                     Context of the message.
 * \param [in] current_state_params    Model specific current state parameters.
 * \param [in] target_state_params     Model specific target state parameters (NULL: to be ignored).
 * \param [in] remaining_time          Time from current state to target state (0: to be ignored).
 * \param [in] ext_params              Additional parameters (NULL: to be ignored).
 * \param [in] reply                   If unicast response to be sent
 * \param [in] publish                 If state to be published
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_hue_server_state_update
           (
               /* IN */ MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
               /* IN */ MS_ACCESS_MODEL_STATE_PARAMS       * current_state_params,
               /* IN */ MS_ACCESS_MODEL_STATE_PARAMS       * target_state_params,
               /* IN */ UINT16                               remaining_time,
               /* IN */ MS_ACCESS_MODEL_EXT_PARAMS         * ext_params,
               /* IN */ UCHAR                                reply,
               /* IN */ UCHAR                                publish
           );

/**
 *  \brief API to send reply or to update state change
 *
 *  \par Description
 *  This is to send reply for a request or to inform change in state.
 *
 * \param [in] ctx                     Context of the message.
 * \param [in] current_state_params    Model specific current state parameters.
 * \param [in] target_state_params     Model specific target state parameters (NULL: to be ignored).
 * \param [in] remaining_time          Time from current state to target state (0: to be ignored).
 * \param [in] ext_params              Additional parameters (NULL: to be ignored).
 * \param [in] reply                   If unicast response to be sent
 * \param [in] publish                 If state to be published
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_saturation_server_state_update
           (
               /* IN */ MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
               /* IN */ MS_ACCESS_MODEL_STATE_PARAMS       * current_state_params,
               /* IN */ MS_ACCESS_MODEL_STATE_PARAMS       * target_state_params,
               /* IN */ UINT16                               remaining_time,
               /* IN */ MS_ACCESS_MODEL_EXT_PARAMS         * ext_params,
               /* IN */ UCHAR                                reply,
               /* IN */ UCHAR                                publish
           );
/** \} */

/** \} */

/**
 * \defgroup light_hsl_cli_api_defs Light HSL Client API Definitions
 * \{
 * \brief This section describes the EtherMind Mesh Light HSL Client
 * Model APIs.
 */

/**
 * \name Light HSL Client Interfaces
 * \{
 */

/**
 *  \brief API to initialize Light_HSL Client model
 *
 *  \par Description
 *  This is to initialize Light_HSL Client model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] model_handle
 *                   Model identifier associated with the model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] appl_cb    Application Callback to be used by the Light_HSL Client.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_client_init
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE    element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * model_handle,
               /* IN */    MS_LIGHT_HSL_CLIENT_CB appl_cb
           );

/**
 *  \brief API to get Light_HSL client model handle
 *
 *  \par Description
 *  This is to get the handle of Light_HSL client model.
 *
 *  \param [out] model_handle   Address of model handle to be filled/returned.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_client_get_model_handle
           (
               /* OUT */ MS_ACCESS_MODEL_HANDLE  * model_handle
           );

/**
 *  \brief API to set Light_HSL client model handle
 *
 *  \par Description
 *  This is to set the handle of Light_HSL client model.
 *
 *  \param [in] model_handle   Model handle to be assigned.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_client_set_model_handle
           (
               /* IN */ MS_ACCESS_MODEL_HANDLE  model_handle
           );

/**
 *  \brief API to send acknowledged commands
 *
 *  \par Description
 *  This is to initialize sending acknowledged commands.
 *
 *  \param [in] req_opcode    Request Opcode.
 *  \param [in] param         Parameter associated with Request Opcode.
 *  \param [in] rsp_opcode    Response Opcode.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_light_hsl_client_send_reliable_pdu
           (
               /* IN */ UINT32    req_opcode,
               /* IN */ void    * param,
               /* IN */ UINT32    rsp_opcode
           );
/** \} */

/** \} */

/** \} */

/**
 * \addtogroup light_hsl_defines
 * \{
 */

/**
 * \defgroup light_hsl_marcos Utility Macros
 * \{
 * \brief This section describes the various Utility Macros in EtherMind
 * Mesh Light HSL Model Layer.
 */

/**
 * \name Light HSL Client Macros
 * \{
 */

/**
 *  \brief API to get the Light HSL Lightness, Light HSL Hue, and Light HSL Saturation states of an element.
 *
 *  \par Description
 *  The Light HSL Get is an acknowledged message used to get the Light HSL Lightness, Light HSL Hue, and Light HSL Saturation states of an element.
 *  The response to the Light HSL Get message is a Light HSL Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_get() \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_GET_OPCODE,\
            NULL,\
            MS_ACCESS_LIGHT_HSL_STATUS_OPCODE\
        )

/**
 *  \brief API to set the Light HSL Lightness state, Light HSL Hue state, and the Light HSL Saturation state of an element.
 *
 *  \par Description
 *  The Light HSL Set Unacknowledged is an unacknowledged message used to set the Light HSL Lightness state, Light HSL Hue state,
 *  and the Light HSL Saturation state of an element.
 *
 *  \param [in] param Light HSL Set message parameter \ref MS_LIGHT_HSL_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_set(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_SET_OPCODE,\
            param,\
            MS_ACCESS_LIGHT_HSL_STATUS_OPCODE\
        )

/**
 *  \brief API to set the Light HSL Lightness state, Light HSL Hue state, and the Light HSL Saturation state of an element.
 *
 *  \par Description
 *  The Light HSL Set is an acknowledged message used to set the Light HSL Lightness state, Light HSL Hue state,
 *  and the Light HSL Saturation state of an element.
 *  The response to the Light HSL Set message is a Light HSL Status message.
 *
 *  \param [in] param Light HSL Set message parameter \ref MS_LIGHT_HSL_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_set_unacknowledged(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_SET_UNACKNOWLEDGED_OPCODE,\
            param,\
            0xFFFFFFFF\
        )

/**
 *  \brief API to get the target Light HSL Lightness, Light HSL Hue, and Light HSL Saturation states of an element.
 *
 *  \par Description
 *  Light HSL Target Get is an acknowledged message used to get the target Light HSL Lightness, Light HSL Hue,
 *  and Light HSL Saturation states of an element.
 *  The response to the Light HSL Target Get message is a Light HSL Target Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_target_get() \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_TARGET_GET_OPCODE,\
            NULL,\
            MS_ACCESS_LIGHT_HSL_TARGET_STATUS_OPCODE\
        )

/**
 *  \brief API to to get the Light Lightness Default, the Light HSL Hue Default, and Light HSL Saturation Default states of an element.
 *
 *  \par Description
 *  Light HSL Default Get is an acknowledged message used to get the Light Lightness Default, the Light HSL Hue Default,
 *  and Light HSL Saturation Default states of an element.
 *  The response to the Light HSL Default Get message is a Light HSL Default Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_default_get() \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_DEFAULT_GET_OPCODE,\
            NULL,\
            MS_ACCESS_LIGHT_HSL_DEFAULT_STATUS_OPCODE\
        )

/**
 *  \brief API to set the Light Lightness Default, the Light HSL Hue Default, and Light HSL Saturation Default states of an element.
 *
 *  \par Description
 *  Light HSL Default Set is an acknowledged message used to set the Light Lightness Default, the Light HSL Hue Default,
 *  and Light HSL Saturation Default states of an element.
 *  The response to the Light HSL Default Set message is a Light HSL Default Status message.
 *
 *  \param [in] param Light HSL Default Set message parameter \ref MS_LIGHT_HSL_DEFAULT_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_default_set(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_DEFAULT_SET_OPCODE,\
            param,\
            MS_ACCESS_LIGHT_HSL_DEFAULT_STATUS_OPCODE\
        )

/**
 *  \brief API to set the Light Lightness Default, the Light HSL Hue Default, and Light HSL Saturation Default states of an element.
 *
 *  \par Description
 *  Light HSL Default Set Unacknowledged is an unacknowledged message used to set the Light Lightness Default, the Light HSL Hue Default,
 *  and Light HSL Saturation Default states of an element.
 *
 *  \param [in] param Light HSL Default Set message parameter \ref MS_LIGHT_HSL_DEFAULT_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_default_set_unacknowledged(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_DEFAULT_SET_UNACKNOWLEDGED_OPCODE,\
            param,\
            0xFFFFFFFF\
        )

/**
 *  \brief API to get the Light HSL Hue Range and Light HSL Saturation Range states of an element.
 *
 *  \par Description
 *  The Light HSL Range Get is an acknowledged message used to get the Light HSL Hue Range and Light HSL Saturation Range states of an element.
 *  The response to the Light HSL Range Get message is a Light HSL Range Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_range_get() \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_RANGE_GET_OPCODE,\
            NULL,\
            MS_ACCESS_LIGHT_HSL_RANGE_STATUS_OPCODE\
        )

/**
 *  \brief API to set the Light HSL Hue Range and Light HSL Saturation Range states of an element.
 *
 *  \par Description
 *  Light HSL Range Set is an acknowledged message used to set the Light HSL Hue Range and Light HSL Saturation Range states of an element.
 *  The response to the Light HSL Range Set message is a Light HSL Range Status message.
 *
 *  \param [in] param Light HSL Range Set message parameter \ref MS_LIGHT_HSL_RANGE_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_range_set(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_RANGE_SET_OPCODE,\
            param,\
            MS_ACCESS_LIGHT_HSL_RANGE_STATUS_OPCODE\
        )

/**
 *  \brief API to set the Light HSL Hue Range and Light HSL Saturation Range states of an element.
 *
 *  \par Description
 *  Light HSL Range Set Unacknowledged is an unacknowledged message used to set the Light HSL Hue Range and Light HSL Saturation Range states of an element.
 *
 *  \param [in] param Light HSL Range Set message parameter \ref MS_LIGHT_HSL_RANGE_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_range_set_unacknowledged(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_RANGE_SET_UNACKNOWLEDGED_OPCODE,\
            param,\
            0xFFFFFFFF\
        )

/**
 *  \brief API to get the Light HSL Hue state of an element.
 *
 *  \par Description
 *  The Light HSL Hue Get is an acknowledged message used to get the Light HSL Hue state of an element.
 *  The response to the Light HSL Hue Get message is a Light HSL Hue Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_hue_get() \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_HUE_GET_OPCODE,\
            NULL,\
            MS_ACCESS_LIGHT_HSL_HUE_STATUS_OPCODE\
        )

/**
 *  \brief API to set the target Light HSL Hue state of an element.
 *
 *  \par Description
 *  The Light HSL Hue Set is an acknowledged message used to set the target Light HSL Hue state of an element.
 *  The response to the Light HSL Hue Set message is a Light HSL Hue Status message.
 *
 *  \param [in] param Light HSL Hue Set message parameter \ref MS_LIGHT_HSL_HUE_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_hue_set(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_HUE_SET_OPCODE,\
            param,\
            MS_ACCESS_LIGHT_HSL_HUE_STATUS_OPCODE\
        )

/**
 *  \brief API to set the target Light HSL Hue state of an element.
 *
 *  \par Description
 *  The Light HSL Hue Set Unacknowledged is an unacknowledged message used to
 *  set the target Light HSL Hue state of an element.
 *
 *  \param [in] param Light HSL Hue Set message parameter \ref MS_LIGHT_HSL_HUE_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_hue_set_unacknowledged(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_HUE_SET_UNACKNOWLEDGED_OPCODE,\
            param,\
            0xFFFFFFFF\
        )

/**
 *  \brief API to get the Light HSL Saturation state of an element.
 *
 *  \par Description
 *  The Light HSL Saturation Get is an acknowledged message used to get the Light HSL Saturation state of an element.
 *  The response to the Light HSL Saturation Get message is a Light HSL Saturation Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_saturation_get() \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_SATURATION_GET_OPCODE,\
            NULL,\
            MS_ACCESS_LIGHT_HSL_SATURATION_STATUS_OPCODE\
        )

/**
 *  \brief API to set the target Light HSL Saturation state of an element.
 *
 *  \par Description
 *  The Light HSL Saturation Set is an acknowledged message used to set the target Light HSL Saturation state of an element.
 *  The response to the Light HSL Saturation Set message is a Light HSL Saturation Status message.
 *
 *  \param [in] param Light HSL Saturation Set message parameter \ref MS_LIGHT_HSL_SATURATION_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_saturation_set(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_SATURATION_SET_OPCODE,\
            param,\
            MS_ACCESS_LIGHT_HSL_SATURATION_STATUS_OPCODE\
        )

/**
 *  \brief API to set the target Light HSL Saturation state of an element.
 *
 *  \par Description
 *  The Light HSL Saturation Set Unacknowledged is an unacknowledged message
 *  used to set the target Light HSL Saturation state of an element.
 *
 *  \param [in] param Light HSL Saturation Set message parameter \ref MS_LIGHT_HSL_SATURATION_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_saturation_set_unacknowledged(param) \
        MS_light_hsl_client_send_reliable_pdu \
        (\
            MS_ACCESS_LIGHT_HSL_SATURATION_SET_UNACKNOWLEDGED_OPCODE,\
            param,\
            0xFFFFFFFF\
        )
/** \} */

#ifdef MS_MODEL_SERVER_EXTENDED_INTERFACE

/**
 * \name Light HSL Server and Light HSL setup Server Macros
 * \{
 */

/**
 *  \brief API to initialize Light_HSL Server model
 *
 *  \par Description
 *  This is to initialize Light_HSL Server model and to register with Access layer.
 *
 *  \param [in] eh
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] mh
 *                   Model identifier associated with the Light HSL model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in, out] smh
 *                   Model identifier associated with the Light HSL Setup model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] cb    Application Callback to be used by the Light_HSL Server.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_server_init(eh,mh,smh,cb) \
        MS_light_hsl_server_init_ext \
        (\
            (eh),\
            (mh),\
            (smh),\
            (cb),\
            (cb)\
        )

/**
 *  \brief API to send reply or to update state change
 *
 *  \par Description
 *  This is to send reply for a request or to inform change in state.
 *
 * \param [in] c   Context of the message.
 * \param [in] cs  Model specific current state parameters.
 * \param [in] ts  Model specific target state parameters (NULL: to be ignored).
 * \param [in] rt  Time from current state to target state (0: to be ignored).
 * \param [in] ex  Additional parameters (NULL: to be ignored).
 * \param [in] r   If unicast response to be sent
 * \param [in] p   If state to be published
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_light_hsl_server_state_update(c,cs,ts,rt,ex,r,p) \
        MS_light_hsl_server_state_update_ext \
        (\
            (c),\
            (cs),\
            (ts),\
            (rt),\
            (ex),\
            (r),\
            (p)\
        )

/** \} */

#endif /* MS_MODEL_SERVER_EXTENDED_INTERFACE */

/** \} */

/** \} */

/** \} */

#endif /*_H_MS_LIGHT_HSL_API_ */
