/**
 * \file MS_generic_onoff_api.h
 *
 * \brief This file defines the Mesh Generic OnOff Model Application Interface
 * - includes Data Structures and Methods for both Server and Client.
 */

/*
 * Copyright (C) 2017. Mindtree Ltd.
 * All rights reserved.
 */

#ifndef _H_MS_GENERIC_ONOFF_API_
#define _H_MS_GENERIC_ONOFF_API_


/* --------------------------------------------- Header File Inclusion */
#include "MS_access_api.h"


/* --------------------------------------------- Global Definitions */
/**
 * \defgroup generic_onoff_module Generic OnOff Model (GENERIC_ONOFF)
 * \ingroup generics_models
 * \{
 *  \brief This section describes the interfaces & APIs offered by the EtherMind
 *  Mesh Generic OnOff Model (GENERIC_ONOFF) module to the Application.
 */

/* --------------------------------------------- Data Types/ Structures */
/**
 *  \defgroup generic_onoff_cb Application Callback
 *  \{
 *  \brief This section describes the Notification Callback Interfaces offered
 *  to the application by EtherMind Mesh Generic OnOff Model Layer.
 */

/**
 * Generic OnOff Server application Asynchronous Notification Callback.
 *
 * Generic OnOff Server calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] msg_raw       Uninterpreted/raw received message.
 * \param [in] req_type      Requested message type.
 * \param [in] state_params  Model specific state parameters.
 * \param [in] ext_params    Additional parameters.
 */
typedef API_RESULT (* MS_GENERIC_ONOFF_SERVER_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
            MS_ACCESS_MODEL_REQ_MSG_RAW        * msg_raw,
            MS_ACCESS_MODEL_REQ_MSG_T          * req_type,
            MS_ACCESS_MODEL_STATE_PARAMS       * state_params,
            MS_ACCESS_MODEL_EXT_PARAMS         * ext_params

        ) DECL_REENTRANT;

/**
 * Generic OnOff Client application Asynchronous Notification Callback.
 *
 * Generic OnOff Client calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] opcode        Opcode.
 * \param [in] data_param    Data associated with the event if any or NULL.
 * \param [in] data_len      Size of the event data. 0 if event data is NULL.
 */
typedef API_RESULT (* MS_GENERIC_ONOFF_CLIENT_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT * ctx,
            UINT32                            opcode,
            UCHAR                           * data_param,
            UINT16                            data_len
        ) DECL_REENTRANT;
/** \} */

/**
 * \defgroup generic_onoff_defines Defines
 * \{
 * \brief This section describes the various Defines in EtherMind
 * Mesh Generic OnOff Model Layer.
 */

/**
 *  \defgroup generic_onoff_structures Structures
 *  \{
 *  \brief This section describes the various Data-Types and Structures in
 *  EtherMind Mesh Generic OnOff Model Layer.
 */

/**
 *  Generic OnOff Set message parameters.
 */
typedef struct MS_generic_onoff_set_struct
{
    /** The target value of the Generic OnOff state */
    UCHAR  onoff;

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

} MS_GENERIC_ONOFF_SET_STRUCT;

/**
 * Generic OnOff Status message parameters.
 */
typedef struct MS_generic_onoff_status_struct
{
    /** The present value of the Generic OnOff state. */
    UCHAR  present_onoff;

    /** The target value of the Generic OnOff state */
    UCHAR  target_onoff;

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

    /** Flag: To represent if optional fields Target OnOff and Remaining Time are valid */
    UCHAR optional_fields_present;

} MS_GENERIC_ONOFF_STATUS_STRUCT;

/** \} */

/** \} */

/* --------------------------------------------- Function */
/**
 * \defgroup generic_onoff_api_defs API Definitions
 * \{
 * \brief This section describes the various APIs exposed by
 * EtherMind Mesh Generic OnOff Model Layer to the Application.
 */

/**
 * \defgroup generic_onoff_ser_api_defs Generic OnOff Server API Definitions
 * \{
 * \brief This section describes the EtherMind Mesh Generic OnOff Server
 * Model APIs.
 */

/**
 * \name Generic OnOff Server Interfaces
 * \{
 */

/**
 *  \brief API to initialize Generic_OnOff Server model
 *
 *  \par Description
 *  This is to initialize Generic_OnOff Server model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] model_handle
 *                   Model identifier associated with the model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] appl_cb    Application Callback to be used by the Generic_OnOff Server.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_generic_onoff_server_init
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE    element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * model_handle,
               /* IN */    MS_GENERIC_ONOFF_SERVER_CB appl_cb
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
API_RESULT MS_generic_onoff_server_state_update
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
 * \defgroup generic_onoff_cli_api_defs Generic OnOff Client API Definitions
 * \{
 * \brief This section describes the EtherMind Mesh Generic OnOff Client
 * Model APIs.
 */

/**
 * \name Generic OnOff Client Interfaces
 * \{
 */

/**
 *  \brief API to initialize Generic_OnOff Client model
 *
 *  \par Description
 *  This is to initialize Generic_OnOff Client model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] model_handle
 *                   Model identifier associated with the model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] appl_cb    Application Callback to be used by the Generic_OnOff Client.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_generic_onoff_client_init
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE    element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * model_handle,
               /* IN */    MS_GENERIC_ONOFF_CLIENT_CB appl_cb
           );

/**
 *  \brief API to get Generic_OnOff client model handle
 *
 *  \par Description
 *  This is to get the handle of Generic_OnOff client model.
 *
 *  \param [out] model_handle   Address of model handle to be filled/returned.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_generic_onoff_client_get_model_handle
           (
               /* OUT */ MS_ACCESS_MODEL_HANDLE  * model_handle
           );

/**
 *  \brief API to set Generic_OnOff client model handle
 *
 *  \par Description
 *  This is to set the handle of Generic_OnOff client model.
 *
 *  \param [in] model_handle   Model handle to be assigned.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_generic_onoff_client_set_model_handle
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
API_RESULT MS_generic_onoff_client_send_reliable_pdu
           (
               /* IN */ UINT32    req_opcode,
               /* IN */ void    * param,
               /* IN */ UINT32    rsp_opcode
           );
/** \} */

/** \} */

/** \} */

/**
 * \addtogroup generic_onoff_defines
 * \{
 */

/**
 * \defgroup generic_onoff_marcos Utility Macros
 * \{
 * \brief This section describes the various Utility Macros in EtherMind
 * Mesh Generic OnOff Model Layer.
 */

/**
 * \name Generic OnOff Client Macro
 * \{
 */

/**
 *  \brief API to get Generic OnOff state
 *
 *  \par Description
 *  The Generic OnOff Get is an acknowledged message used to get the Generic OnOff
 *  state of an element.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_generic_onoff_get() \
        MS_generic_onoff_client_send_reliable_pdu \
        (\
            MS_ACCESS_GENERIC_ONOFF_GET_OPCODE,\
            NULL,\
            MS_ACCESS_GENERIC_ONOFF_STATUS_OPCODE\
        )

/**
 *  \brief API to set Generic OnOff state
 *
 *  \par Description
 *  The Generic OnOff Set is an Acknowledged message used to set the Generic OnOff
 *  state of an element.
 *
 *  \param [in] param Generic OnOff Set message parameter \ref MS_GENERIC_ONOFF_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_generic_onoff_set(param) \
        MS_generic_onoff_client_send_reliable_pdu \
        (\
            MS_ACCESS_GENERIC_ONOFF_SET_OPCODE,\
            param,\
            MS_ACCESS_GENERIC_ONOFF_STATUS_OPCODE\
        )

/**
 *  \brief API to set Generic OnOff state unacknowledged
 *
 *  \par Description
 *  The Generic OnOff Set Unacknowledged is an unacknowledged message used to set the Generic OnOff
 *  state of an element.
 *
 *  \param [in] param Generic OnOff Set Unacknowledged message parameter \ref MS_GENERIC_ONOFF_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_generic_onoff_set_unacknowledged(param) \
        MS_generic_onoff_client_send_reliable_pdu \
        (\
            MS_ACCESS_GENERIC_ONOFF_SET_UNACKNOWLEDGED_OPCODE,\
            param,\
            0xFFFFFFFF\
        )
/** \} */

/** \} */

/** \} */

/** \} */

#endif /*_H_MS_GENERIC_ONOFF_API_ */
