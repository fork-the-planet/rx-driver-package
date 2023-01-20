/**
 * \file MS_time_api.h
 *
 * \brief This file defines the Mesh Time Model Application Interface
 * - includes Data Structures and Methods for both Server and Client.
 */

/*
 * Copyright (C) 2017. Mindtree Ltd.
 * All rights reserved.
 */

#ifndef _H_MS_TIME_API_
#define _H_MS_TIME_API_


/* --------------------------------------------- Header File Inclusion */
#include "MS_access_api.h"


/* --------------------------------------------- Global Definitions */
/**
 * \defgroup time_module Time Model (TIME)
 * \ingroup time_and_scenes_models
 * \{
 *  \brief This section describes the interfaces & APIs offered by the EtherMind
 *  Mesh Time Model (TIME) module to the Application.
 */

/* --------------------------------------------- Data Types/ Structures */
/**
 *  \defgroup time_cb Application Callback
 *  \{
 *  \brief This section describes the Notification Callback Interfaces offered
 *  to the application by EtherMind Mesh Time Model Layer.
 */

/**
 * Time Server application Asynchronous Notification Callback.
 *
 * Time Server calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] msg_raw       Uninterpreted/raw received message.
 * \param [in] req_type      Requested message type.
 * \param [in] state_params  Model specific state parameters.
 * \param [in] ext_params    Additional parameters.
 */
typedef API_RESULT (* MS_TIME_SERVER_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
            MS_ACCESS_MODEL_REQ_MSG_RAW        * msg_raw,
            MS_ACCESS_MODEL_REQ_MSG_T          * req_type,
            MS_ACCESS_MODEL_STATE_PARAMS       * state_params,
            MS_ACCESS_MODEL_EXT_PARAMS         * ext_params

        ) DECL_REENTRANT;

#ifdef MS_MODEL_SERVER_EXTENDED_INTERFACE
/**
 * Time Setup Server application Asynchronous Notification Callback.
 *
 * Time Setup Server calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] msg_raw       Uninterpreted/raw received message.
 * \param [in] req_type      Requested message type.
 * \param [in] state_params  Model specific state parameters.
 * \param [in] ext_params    Additional parameters.
 */
typedef API_RESULT (* MS_TIME_SETUP_SERVER_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT    * ctx,
            MS_ACCESS_MODEL_REQ_MSG_RAW        * msg_raw,
            MS_ACCESS_MODEL_REQ_MSG_T          * req_type,
            MS_ACCESS_MODEL_STATE_PARAMS       * state_params,
            MS_ACCESS_MODEL_EXT_PARAMS         * ext_params

        ) DECL_REENTRANT;
#endif /* MS_MODEL_SERVER_EXTENDED_INTERFACE */

/**
 * Time Client application Asynchronous Notification Callback.
 *
 * Time Client calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param [in] ctx           Context of the message received for a specific model instance.
 * \param [in] opcode        Opcode.
 * \param [in] data_param    Data associated with the event if any or NULL.
 * \param [in] data_len      Size of the event data. 0 if event data is NULL.
 */
typedef API_RESULT (* MS_TIME_CLIENT_CB)
        (
            MS_ACCESS_MODEL_REQ_MSG_CONTEXT * ctx,
            UINT32                   opcode,
            UCHAR                  * data_param,
            UINT16                   data_len
        ) DECL_REENTRANT;
/** \} */

/**
 * \defgroup time_defines Defines
 * \{
 * \brief This section describes the various Defines in EtherMind
 * Mesh Time Model Layer.
 */

/**
 *  \defgroup time_structures Structures
 *  \{
 *  \brief This section describes the various Data-Types and Structures in
 *  EtherMind Mesh Time Model Layer.
 */

/**
 * Time Set message parameters.
 */
typedef struct MS_time_struct
{
    /** The current TAI time in seconds */
    UCHAR  tai_seconds[5];

    /** The sub-second time in units of 1/256th second */
    UCHAR  subsecond;

    /** The estimated uncertainty in 10 millisecond steps */
    UCHAR  uncertainty;

    /** 0 = No Time Authority, 1 = Time Authority */
    UCHAR  time_authority;

    /** Current difference between TAI and UTC in seconds */
    UINT16 tai_utc_delta;

    /** The local time zone offset in 15-minute increments */
    UCHAR  time_zone_offset;

} MS_TIME_STRUCT;

/**
 * Time Zone Set message parameters.
 */
typedef struct MS_time_zone_set_struct
{
    /** Upcoming local time zone offset */
    UCHAR  time_zone_offset_new;

    /** TAI Seconds time of the upcoming Time Zone Offset change */
    UCHAR  tai_of_zone_change[5];

} MS_TIME_ZONE_SET_STRUCT;

/**
 * Time Zone Status message parameters.
 */
typedef struct MS_time_zone_status_struct
{
    /** Current local time zone offset */
    UCHAR  time_zone_offset_current;

    /** Upcoming local time zone offset */
    UCHAR  time_zone_offset_new;

    /** TAI Seconds time of the upcoming Time Zone Offset change */
    UCHAR  tai_of_zone_change[5];

} MS_TIME_ZONE_STATUS_STRUCT;

/**
 * TAI-UTC Delta Set message parameters.
 */
typedef struct MS_tai_utc_delta_set_struct
{
    /** Upcoming difference between TAI and UTC in seconds */
    UINT16 tai_utc_delta_new;

    /** Always 0b0. Other values are Prohibited. */
    UCHAR  padding;

    /** TAI Seconds time of the upcoming TAI-UTC Delta change */
    UCHAR  tai_of_delta_change[5];

} MS_TAI_UTC_DELTA_SET_STRUCT;

/**
 * TAI-UTC Delta Status message parameters.
 */
typedef struct MS_tai_utc_delta_status_struct
{
    /** Current difference between TAI and UTC in seconds */
    UINT16 tai_utc_delta_current;

    /** Always 0b0. Other values are Prohibited. */
    UCHAR  padding_1;

    /** Upcoming difference between TAI and UTC in seconds */
    UINT16 tai_utc_delta_new;

    /** Always 0b0. Other values are Prohibited. */
    UCHAR  padding_2;

    /** TAI Seconds time of the upcoming TAI-UTC Delta change */
    UCHAR  tai_of_delta_change[5];

} MS_TAI_UTC_DELTA_STATUS_STRUCT;

/**
 * Time Role Set/Status message parameters.
 */
typedef struct MS_time_role_struct
{
    /** The Time Role for the element */
    UCHAR  time_role;

} MS_TIME_ROLE_STRUCT;

/** \} */

/** \} */

/* --------------------------------------------- Function */
/**
 * \defgroup time_api_defs API Definitions
 * \brief This section describes the various APIs exposed by
 * EtherMind Mesh Time Model Layer to the Application and other upper
 * layers of the stack.
 * \{
 */

/**
 * \defgroup time_ser_api_defs Time Server API Definitions
 * \{
 * \brief This section describes the EtherMind Mesh Time Server Model APIs.
 */

/**
 * \name Timer Server Interfaces
 * \{
 */

#ifndef MS_MODEL_SERVER_EXTENDED_INTERFACE
/**
 *  \brief API to initialize Time Server model
 *
 *  \par Description
 *  This is to initialize Time Server model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] time_model_handle
 *                   Model identifier associated with the time model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in, out] time_setup_model_handle
 *                   Model identifier associated with the time setup model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] time_appl_cb    Application Callback to be used by the Time Server.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_time_server_init
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE    element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * time_model_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * time_setup_model_handle,
               /* IN */    MS_TIME_SERVER_CB           time_appl_cb
           );
#else /* MS_MODEL_SERVER_EXTENDED_INTERFACE */
/**
 *  \brief API to initialize Time Server model
 *
 *  \par Description
 *  This is to initialize Time Server model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] time_model_handle
 *                   Model identifier associated with the time model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in, out] time_setup_model_handle
 *                   Model identifier associated with the time setup model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] time_appl_cb    Application Callback to be used by the Time Server.

 *
 *  \param [in] time_setup_appl_cb    Application Callback to be used by the Time Setup Server.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_time_server_init_ext
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE      element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE      * time_model_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE      * time_setup_model_handle,
               /* IN */    MS_TIME_SERVER_CB             time_appl_cb,
               /* IN */    MS_TIME_SETUP_SERVER_CB       time_setup_appl_cb
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
#ifndef MS_MODEL_SERVER_EXTENDED_INTERFACE
API_RESULT MS_time_server_state_update
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
API_RESULT MS_time_server_state_update_ext
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

/** \} */

/** \} */

/**
 * \defgroup time_cli_api_defs Time Client API Definitions
 * \{
 * \brief This section describes the EtherMind Mesh Time Client Model APIs.
 */

/**
 * \name Timer Client Interfaces
 * \{
 */

/**
 *  \brief API to initialize Time Client model
 *
 *  \par Description
 *  This is to initialize Time Client model and to register with Access layer.
 *
 *  \param [in] element_handle
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] model_handle
 *                   Model identifier associated with the model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] appl_cb    Application Callback to be used by the Time Client.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_time_client_init
           (
               /* IN */    MS_ACCESS_ELEMENT_HANDLE    element_handle,
               /* INOUT */ MS_ACCESS_MODEL_HANDLE    * model_handle,
               /* IN */    MS_TIME_CLIENT_CB appl_cb
           );

/**
 *  \brief API to get Time client model handle
 *
 *  \par Description
 *  This is to get the handle of Time client model.
 *
 *  \param [out] model_handle   Address of model handle to be filled/returned.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_time_client_get_model_handle
           (
               /* OUT */ MS_ACCESS_MODEL_HANDLE  * model_handle
           );

/**
 *  \brief API to set Time client model handle
 *
 *  \par Description
 *  This is to set the handle of Time client model.
 *
 *  \param [in] model_handle   Model handle to be assigned.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_time_client_set_model_handle
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
API_RESULT MS_time_client_send_reliable_pdu
           (
               /* IN */ UINT32    req_opcode,
               /* IN */ void    * param,
               /* IN */ UINT32    rsp_opcode
           );
/** \} */

/** \} */

/** \} */

/**
 * \addtogroup time_defines
 * \{
 */

/**
 * \defgroup time_marcos Utility Macros
 * \{
 * \brief This section describes the various Utility Macros in EtherMind
 * Mesh Time Model Layer.
 */

/**
 * \name Time Client Macros
 * \{
 */

/**
 *  \brief API to get the Time state of neighbor nodes.
 *
 *  \par Description
 *  Time Get is a message used to get the Time state of neighbor nodes.
 *  The response to the Time Get message is a Time Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_time_get() \
        MS_time_client_send_reliable_pdu \
        (\
            MS_ACCESS_TIME_GET_OPCODE,\
            NULL,\
            MS_ACCESS_TIME_STATUS_OPCODE\
        )

/**
 *  \brief API to set the Time state of an element.
 *
 *  \par Description
 *  Time Set is an acknowledged message used to set the Time state of an element.
 *  The response to the Time Set message is a Time Status message.
 *
 *  \param [in] param Time Set message parameter \ref MS_TIME_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_time_set(param) \
        MS_time_client_send_reliable_pdu \
        (\
            MS_ACCESS_TIME_SET_OPCODE,\
            param,\
            MS_ACCESS_TIME_STATUS_OPCODE\
        )

/**
 *  \brief API to get the Time Zone Offset Current state.
 *
 *  \par Description
 *  Time Zone Get is an acknowledged message used to get the Time Zone Offset Current state,
 *  the Time Zone Offset New state , and the TAI of Zone Change state.
 *  The response to the Time Zone Get message is a Time Zone Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_time_zone_get() \
        MS_time_client_send_reliable_pdu \
        (\
            MS_ACCESS_TIME_ZONE_GET_OPCODE,\
            NULL,\
            MS_ACCESS_TIME_ZONE_STATUS_OPCODE\
        )

/**
 *  \brief API to set the Time Zone Offset New state.
 *
 *  \par Description
 *  Time Zone Set is an acknowledged message used to set the Time Zone Offset New state and the TAI of Zone Change state.
 *
 *  \param [in] param Time Zone Set message parameter \ref MS_TIME_ZONE_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_time_zone_set(param) \
        MS_time_client_send_reliable_pdu \
        (\
            MS_ACCESS_TIME_ZONE_SET_OPCODE,\
            param,\
            MS_ACCESS_TIME_ZONE_STATUS_OPCODE\
        )

/**
 *  \brief API to get the TAI-UTC Delta Current state, the TAI-UTC Delta New state, and the TAI of Delta Change state.
 *
 *  \par Description
 *  TAI-UTC Delta Get is an acknowledged message used to get the TAI-UTC Delta Current state,
 *  the TAI-UTC Delta New state, and the TAI of Delta Change state.
 *  The response to the TAI-UTC Delta Get message is a TAI-UTC Delta Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_tai_utc_delta_get() \
        MS_time_client_send_reliable_pdu \
        (\
            MS_ACCESS_TAI_UTC_DELTA_GET_OPCODE,\
            NULL,\
            MS_ACCESS_TAI_UTC_DELTA_STATUS_OPCODE\
        )

/**
 *  \brief API to set the TAI-UTC Delta New state and the TAI of Delta Change state.
 *
 *  \par Description
 *  TAI-UTC Delta Set is an acknowledged message used to set the TAI-UTC Delta New state and the TAI of Delta Change state.
 *
 *  \param [in] param TAI-UTC Delta Set message parameter \ref MS_TAI_UTC_DELTA_SET_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_tai_utc_delta_set(param) \
        MS_time_client_send_reliable_pdu \
        (\
            MS_ACCESS_TAI_UTC_DELTA_SET_OPCODE,\
            param,\
            MS_ACCESS_TAI_UTC_DELTA_STATUS_OPCODE\
        )

/**
 *  \brief API to get the Time Role state of an element.
 *
 *  \par Description
 *  Time Role Get is an acknowledged message used to get the Time Role state of an element.
 *  The response to the Time Role Get message is a Time Role Status message.
 *  There are no parameters for this message.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_time_role_get() \
        MS_time_client_send_reliable_pdu \
        (\
            MS_ACCESS_TIME_ROLE_GET_OPCODE,\
            NULL,\
            MS_ACCESS_TIME_ROLE_STATUS_OPCODE\
        )

/**
 *  \brief API to set the Time Role state of an element.
 *
 *  \par Description
 *  Time Role Set is an acknowledged message used to set the Time Role state of an element.
 *  The response to the Time Role Set message is a Time Role Status message.
 *
 *  \param [in] param Time Role Set message parameter \ref MS_TIME_ROLE_STRUCT
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_time_role_set(param) \
        MS_time_client_send_reliable_pdu \
        (\
            MS_ACCESS_TIME_ROLE_SET_OPCODE,\
            param,\
            MS_ACCESS_TIME_ROLE_STATUS_OPCODE\
        )
/** \} */

#ifdef MS_MODEL_SERVER_EXTENDED_INTERFACE

/**
 * \name Time Server and Time setup Server Macros
 * \{
 */

/**
 *  \brief API to initialize Time Server model
 *
 *  \par Description
 *  This is to initialize Time Server model and to register with Access layer.
 *
 *  \param [in] eh
 *              Element identifier to be associated with the model instance.
 *
 *  \param [in, out] mh
 *                   Model identifier associated with the time model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in, out] smh
 *                   Model identifier associated with the time setup model instance on successful initialization.
 *                   After power cycle of an already provisioned node, the model handle will have
 *                   valid value and the same will be reused for registration.
 *
 *  \param [in] cb   Application Callback to be used by the Time Server.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_time_server_init(eh,mh,smh,cb) \
        MS_time_server_init_ext \
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
#define MS_time_server_state_update(c,cs,ts,rt,ex,r,p) \
        MS_time_server_state_update_ext \
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

#endif /*_H_MS_TIME_API_ */
