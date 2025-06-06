
/**
 *  \file MS_trn_api.h
 *
 *  \brief This file defines the Mesh Transport Application Interface - includes
 *  Data Structures and Methods.
 */

/*
 *  Copyright (C) 2017. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_MS_TRN_API_
#define _H_MS_TRN_API_


/* --------------------------------------------- Header File Inclusion */
/* Lower Transport Layer */
#include "MS_ltrn_api.h"

/* --------------------------------------------- Global Definitions */

/**
 * \defgroup trn_module Transport Layer (TRN)
 * \ingroup mesh_core_block
 * \{
 *  \brief This section describes the interfaces & APIs offered by the EtherMind
 *  Mesh Transport (TRN) module to the Application and other upper
 *  layers of the stack.
 */

/**
 * \defgroup trn_defines Defines
 * \{
 * \brief This section describes the various Defines in EtherMind
 * Mesh Transport Layer.
 */

/**
 * \defgroup trn_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * Mesh Transport Layer.
 */

/**
 * \name Tranport Layer Control Message Opcodes
 *       RFU Values: 0x0B - 0x7F
 * \{
 */

/**
 * Sent by a Low Power node to its Friend node to request any messages
 * that it has cached for the Low Power node
 */
#define MS_TRN_CTRL_OPCODE_FRND_POLL                    0x01

/**
 * Sent by a Friend node to a Low Power node to inform it about cache
 * and/or security updates
 */
#define MS_TRN_CTRL_OPCODE_FRND_UPDATE                  0x02

/** Broadcast by a Low Power node to start to find a friend */
#define MS_TRN_CTRL_OPCODE_FRND_REQ                     0x03

/** Sent by a Friend node to a Low Power node to offer to become its friend */
#define MS_TRN_CTRL_OPCODE_FRND_OFFER                   0x04

/**
 * Sent to a Friend node to inform a previous friend of a Low Power node
 * about the removal of a friendship
 */
#define MS_TRN_CTRL_OPCODE_FRND_CLEAR                   0x05

/**
 * Sent from a previous friend to Friend node to confirm that a prior friend
 * relationship has been removed
 */
#define MS_TRN_CTRL_OPCODE_FRND_CLEAR_CNF               0x06

/**
 * Sent to a Friend node to add one or more addresses
 * to the Friend Subscription List
 */
#define MS_TRN_CTRL_OPCODE_FRND_SUBSCRN_LIST_ADD        0x07

/**
 * Sent to a Friend node to remove one or more addresses
 * from the Friend Subscription List
 */
#define MS_TRN_CTRL_OPCODE_FRND_SUBSCRN_LIST_REMOVE     0x08

/** Sent by a Friend node to confirm Friend Subscription List updates */
#define MS_TRN_CTRL_OPCODE_FRND_SUBSCRN_LIST_CNF        0x09

/** Sent by a node to let other nodes determine topology of a Subnet */
#define MS_TRN_CTRL_OPCODE_HEARTBEAT                    0x0A

/** \} */

/**
 * \name Parameter defines for Friendship Opcodes
 * <b>Friend Update Flags</b>
 *
 * | <b>Bit 0</b> | Key Refresh Flag
 * |--------------|-----------------
 * |  <b>0</b>    | Not-In-Phase2
 * |  <b>1</b>    | In-Phase2
 *
 * | <b>Bit 1</b> |   IV Update Flag
 * |--------------|-----------------
 * |  <b>0</b>    | Normal operation
 * |  <b>1</b>    | IV Update active
 *
 * \{
 */
/** Friend Update Key Refresh Flag Bit Position */
#define MS_FRNDUPD_FLAG_KEYREF_BIT                      0
/** Friend Update Key Refresh Not-In-Phase2 */
#define MS_FRNDUPD_FLAG_KEYREF_NOTINPHASE_2             0x00
/** Friend Update Key Refresh In-Phase2 */
#define MS_FRNDUPD_FLAG_KEYREF_INPHASE_2                0x01

/** Friend Update IV Update Flag Bit Position */
#define MS_FRNDUPD_FLAG_IVUPDATE_BIT                    1
/** Friend Update IV Update Normal Operation */
#define MS_FRNDUPD_FLAG_IVUPDATE_NORMAL                 0x00
/** Friend Update IV Update Active */
#define MS_FRNDUPD_FLAG_IVUPDATE_ACTIVE                 0x01
/** \} */

/**
 * \name Friend Update More Data
 * \{
 */
/** Friend Update Data Queue Empty */
#define MS_FRNDUPD_MD_QUEUE_EMPTY                       0x00
/** Friend Update Data Queue Not Empty */
#define MS_FRNDUPD_MD_QUEUE_NOTEMPTY                    0x01
/** \} */

/**
 * \name Friend Request Criteria
 * \{
 */
/** Friend Request RSSI Factor Offset */
#define MS_FRNDREQ_RSSIFACTOR_OFFSET                    5
/** Friend Request RSSI Factor Mask */
#define MS_FRNDREQ_RSSIFACTOR_MASK                      0x60
/** Friend Request RSSI Factor 1 */
#define MS_FRNDREQ_RSSIFACTOR_1                         0x00
/** Friend Request RSSI Factor 1.5 */
#define MS_FRNDREQ_RSSIFACTOR_1_5                       0x01
/** Friend Request RSSI Factor 2 */
#define MS_FRNDREQ_RSSIFACTOR_2                         0x02
/** Friend Request RSSI Factor 2.5 */
#define MS_FRNDREQ_RSSIFACTOR_2_5                       0x03

/** Friend Request Receive Window Factor Offset */
#define MS_FRNDREQ_RCVWINFACTOR_OFFSET                  3
/** Friend Request Receive Window Factor Mask */
#define MS_FRNDREQ_RCVWINFACTOR_MASK                    0x18
/** Friend Request Receive Window Factor 1 */
#define MS_FRNDREQ_RCVWINFACTOR_1                       0x00
/** Friend Request Receive Window Factor 1.5 */
#define MS_FRNDREQ_RCVWINFACTOR_1_5                     0x01
/** Friend Request Receive Window Factor 2 */
#define MS_FRNDREQ_RCVWINFACTOR_2                       0x02
/** Friend Request Receive Window Factor 2.5 */
#define MS_FRNDREQ_RCVWINFACTOR_2_5                     0x03

/** Friend Request Minimum Queue Size Log Offset */
#define MS_FRNDREQ_MINQSIZELOG_OFFSET                   0
/** Friend Request Minimum Queue Size Log Mask */
#define MS_FRNDREQ_MINQSIZELOG_MASK                     0x07
/** Friend Request Minimum Queue Size Invalid/Prohibited */
#define MS_FRNDREQ_MINQSIZE_INVALID                     0x00
/** Friend Request Minimum Queue Size 2 */
#define MS_FRNDREQ_MINQSIZE_2                           0x01
/** Friend Request Minimum Queue Size 4 */
#define MS_FRNDREQ_MINQSIZE_4                           0x02
/** Friend Request Minimum Queue Size 8 */
#define MS_FRNDREQ_MINQSIZE_8                           0x03
/** Friend Request Minimum Queue Size 16 */
#define MS_FRNDREQ_MINQSIZE_16                          0x04
/** Friend Request Minimum Queue Size 32 */
#define MS_FRNDREQ_MINQSIZE_32                          0x05
/** Friend Request Minimum Queue Size 64 */
#define MS_FRNDREQ_MINQSIZE_64                          0x06
/** Friend Request Minimum Queue Size 128 */
#define MS_FRNDREQ_MINQSIZE_128                         0x07
/** \} */

/**
 * \name Heartbeat features
 * \{
 */
/** Heartbeat feature bit-mask for Relay Feature */
#define MS_HEARTBEAT_FEATURE_RELAY                      (1 << 0)
/** Heartbeat feature bit-mask for Proxy Feature */
#define MS_HEARTBEAT_FEATURE_PROXY                      (1 << 1)
/** Heartbeat feature bit-mask for Friend Feature */
#define MS_HEARTBEAT_FEATURE_FRIEND                     (1 << 2)
/** Heartbeat feature bit-mask for Lowpower Node Feature */
#define MS_HEARTBEAT_FEATURE_LOWPOWER                   (1 << 3)
/** \} */

/**
 * \name Specification Defined Friendship Constants
 * \{
 */
/** Minimum Delay time in milliseconds for Friend-Offer */
#define MS_MIN_FRNDOFFER_DELAY                          100 /* ms */
/** Initial Poll Timeout in milliseconds */
#define MS_TRN_INITIAL_FRNDPOLL_TIMEOUT                 1000 /* ms */
/** \} */

/** \} */

/**
 *  \defgroup trn_events Events
 *  \{
 *  \brief This section lists the Asynchronous Events notified to Application
 *  by EtherMind Mesh Transport Layer.
 */
/**
 * \name Friendship Procedure Events
 * \{
 */
/** Friendship Setup Confirmation Event */
#define MS_TRN_FRIEND_SETUP_CNF                         0x00
/** Friendship Subscriptionlist Confirmation Event */
#define MS_TRN_FRIEND_SUBSCRNLIST_CNF                   0x01
/** Friendship Clear Confirmation Event */
#define MS_TRN_FRIEND_CLEAR_CNF                         0x02
/** Friendship Termination Indication Event */
#define MS_TRN_FRIEND_TERMINATE_IND                     0x03
/** \} */

/** \} */

/** \} */

/* --------------------------------------------- Data Types/ Structures */

/**
 *  \defgroup trn_cb Application Callback
 *  \{
 *  \brief This section describes the Notification Callback Interfaces offered
 *  to the application by EtherMind Mesh Transport Layer.
 */
/**
 * Transport Application Asynchronous Notification Callback.
 *
 * Transport calls the registered callback to indicate events occurred to the
 * application.
 *
 * \param brr_type          Bearer Type.
 * \param net_hdr           Network Header.
 * \param subnet_handle     Associated Subnet Handle.
 * \param appkey_handle     Associated AppKey Handle.
 * \param data_param        Data associated with the event if any or NULL.
 * \param data_len          Size of the event data. 0 if event data is NULL.
 */
typedef void (*TRN_NTF_CB)
        (
            MS_NET_HEADER     * net_hdr,
            MS_SUBNET_HANDLE    subnet_handle,
            MS_APPKEY_HANDLE    appkey_handle,
            UCHAR             * data_param,
            UINT16              data_len
        ) DECL_REENTRANT;

/**
 * Transport Application Friendship Asynchronous Notification Callback.
 *
 * Transport calls the registered callback to indicate the status of friendship
 * setup procedure to the application
 *
 * \param subnet_handle     Associated Subnet Handle.
 * \param event_type        Friendship event. \ref trn_events
 * \param status            Result of the procedure.
 */
typedef void (*TRN_FRND_CB)
        (
            MS_SUBNET_HANDLE   subnet_handle,
            UCHAR              event_type,
            UINT16             status
        ) DECL_REENTRANT;

/** \} */

/**
 *  \addtogroup trn_defines Defines
 *  \{
 */

/**
 *  \defgroup trn_structures Structures
 *  \{
 *  \brief This section describes the various Data-Types and Structures in
 *  EtherMind Mesh Transport Layer.
 */

/** Transport Control Packet Opcode Type */
typedef UCHAR   MS_TRN_CTRL_PKT_OPCODE;

/** Friend Data Structure */
typedef struct _MS_TRN_FRIEND_ENTRY
{
    /** Friend Sequence Number - 7 bit value */
    UINT8        fsn;

    /** Low Power Node Address */
    MS_NET_ADDR  addr;

    /** Number of Elements in LPN */
    UINT8        num_elements;

    /** Previous Friend Address */
    MS_NET_ADDR  prev_faddr;

} MS_TRN_FRIEND_ENTRY;

/** Transport Friend Poll Message */
typedef struct _MS_TRN_FRND_POLL_PARAM
{
    /**
     *  Friend Sequence Number used to acknowledge receipt of
     *  previous messages from the Friend node to the Low Power node.
     */
    UINT8 fsn;

} MS_TRN_FRND_POLL_PARAM;

/** Transport Friend Update Message */
typedef struct _MS_TRN_FRND_UPDATE_PARAM
{
    /** Contains the IV Update Flag and the Key Refresh Flag */
    UINT8 flags;

    /** The current IV Index value known by the Friend node */
    UINT32 ivi;

    /**
     * Availability of data in friend queue
     *
     * Value | Description
     * ------|------------
     *  0    | Friend Queue is empty
     *  1    | Friend Queue is not empty
     */
    UCHAR md;

} MS_TRN_FRND_UPDATE_PARAM;

/** Transport Friend Request Message */
typedef struct _MS_TRN_FRND_REQ_PARAM
{
    /**
     * The criteria that a Friend node should support
     * in order to participate in friendship negotiation
     */
    UCHAR criteria;

    /** Receive delay requested by the Low Power node */
    UCHAR rx_delay;

    /** Poll timeout requested by the Low Power node */
    UINT32 poll_to;

    /** Previous Friend's unicast address */
    UINT16 prev_addr;

    /** Number of Elements in the Low Power node */
    UCHAR num_elem;

    /** Number of Friend Request messages that the Low Power node has sent */
    UINT16 lpn_counter;

} MS_TRN_FRND_REQ_PARAM;

/** Transport Friend Offer Message */
typedef struct _MS_TRN_FRND_OFFER_PARAM
{
    /** Receive Window value supported by the Friend node */
    UINT8 rx_window;

    /** Queue Size available on the Friend node */
    UINT8 queue_size;

    /**
     * Size of the Subscription List that can be supported
     * by a Friend node for a Low Power node
     */
    UINT8 sublist_size;

    /** RSSI measured by the Friend node */
    UINT8 rssi;

    /** Number of Friend Offer messages that the Friend node has sent */
    UINT16 frnd_counter;

} MS_TRN_FRND_OFFER_PARAM;

/** Transport Friend Clear Message */
typedef struct _MS_TRN_FRND_CLEAR_PARAM
{
    /** The unicast address of the Low Power node being removed */
    UINT16 lpn_addr;

    /** Value of the LPNCounter of new relationship */
    UINT16 lpn_counter;

} MS_TRN_FRND_CLEAR_PARAM;

/** Transport Friend Clear Confirm Message */
typedef struct _MS_TRN_FRND_CLEAR_CNF_PARAM
{
    /** The unicast address of the Low Power node being removed */
    UINT16 lpn_addr;

    /** Value of the LPNCounter of corresponding Friend Clear message */
    UINT16 lpn_counter;

} MS_TRN_FRND_CLEAR_CNF_PARAM;

/** Transport Friend Subscription List Add/Remove Message */
typedef struct _MS_TRN_FRND_MANAGE_PARAM
{
    /** The number for identifying a transaction */
    UINT8 txn_num;

    /**
     * List of group addresses and virtual addresses where N is
     * the number of group addresses and virtual addresses in this message.
     *
     * Address octet stream packed in big-endian format.
     */
    void * addr_list;

    /**
     * Number of Addresses in the list
     *
     * Note: Number of addresses is half of the octets in the addr_list field.
     */
    UINT16   num_addr;

    /** Opcode - Add/Delete */
    UINT8    opcode;

} MS_TRN_FRND_MANAGE_PARAM;

/** Transport Friend Subscription List Confirm Message */
typedef struct _MS_TRN_FRND_SUBSCRN_LIST_CNF_PARAM
{
    /** The number for identifying a transaction */
    UINT8 txn_num;

} MS_TRN_FRND_SUBSCRN_LIST_CNF_PARAM;

/** Transport Heartbeat Message */
typedef struct _MS_TRN_HEARTBEAT_PARAM
{
    /** Initial TTL used when sending the message */
    UINT8 init_ttl;

    /** Bit field of currently active features of the node */
    UINT16 features;

} MS_TRN_HEARTBEAT_PARAM;

/** Low Power Node element information */
typedef struct _MS_TRN_FRNDSHIP_INFO
{
    /** Main subnet handle of the element */
    MS_SUBNET_HANDLE subnet_handle;

    /** Peer LPN/Friend Address */
    MS_NET_ADDR addr;

    /** Low Power Node Counter */
    UINT16 lpn_counter;

    /* TODO: Should be a global index? */
    /** Friend Counter */
    UINT16 frnd_counter;

} MS_TRN_FRNDSHIP_INFO;

/** Invalid LPN Handle */
#define LPN_HANDLE_INVALID              MESH_CFG_MAX_LPNS

/** Hearbeat Publication state */
typedef struct _MS_TRN_HEARTBEAT_PUBLICATION_INFO
{
    /**
     * Destination address for Heartbeat messages
     */
    MS_NET_ADDR daddr;

    /**
     * Count to control the number of periodic heartbeat
     * transport messages to be sent
     */
    UINT8 count_log;

    /**
     * Period to control the cadence of periodic heartbeat
     * transport messages
     */
    UINT8 period_log;

    /**
     * TTL value to be used when sending Heartbeat messages
     */
    UINT8 ttl;

    /**
     * Features that trigger sending Heartbeat messages when changed
     */
    UINT16 features;

    /**
     * Global NetKey index of the NetKey to be used to send Heartbeat messges
     */
    UINT16 netkey_index;

}MS_TRN_HEARTBEAT_PUBLICATION_INFO;

/** Heartbeat Subscription state */
typedef struct _MS_TRN_HEARTBEAT_SUBSCRIPTION_INFO
{
    /**
     * Source address for Heartbeat messages that a node shall process
     */
    MS_NET_ADDR saddr;

    /**
     * Destination address for Heartbeat messages
     */
    MS_NET_ADDR daddr;

    /**
     * Counter that tracks the number of periodic heartbeat transport message
     * received since receiving the most recent Config Heartbeat Subscription
     * Set message
     */
    UINT8 count_log;

    /**
     * Period that controls the period for processing periodical Heartbeat
     * transport control messages
     */
    UINT8 period_log;

    /**
     * Minimum hops value registered when receiving heartbeat messages since
     * receiving the most recent Config Heartbeat Subscription Set message
     */
    UINT16 min_hops;

    /**
     * Maximum hops value registered when receiving heartbeat messages since
     * receiving the most recent Config Heartbeat Subscription Set message
     */
    UINT16 max_hops;

}MS_TRN_HEARTBEAT_SUBSCRIPTION_INFO;

/** \} */

/** \} */

/* --------------------------------------------- Function */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup trn_api_defs API Definitions
 * \{
 * \brief This section describes the various APIs exposed by
 * EtherMind Mesh Transport Layer to the Application and other upper
 * layers of the stack.
 */

/**
 * \name Transport Interfaces
 * \{
 */

/**
 *  \brief Register Interface with Transport Layer
 *
 *  \par Description
 *  This routine registers interface with the Transport Layer.
 *  Transport Layer supports single Application, hence this rouine shall be called once.
 *
 *  \param [in] trn_cb
 *         Upper Layer Notification Callback for specific message type
 *
 *  \param [in] msg_type
 *         Message type (Control or Access) for which the callback to be called.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_register
           (
               /* IN */ TRN_NTF_CB        trn_cb,
               /* IN */ MS_TRN_MSG_TYPE   msg_type
           );


/**
 *  \brief API to send Access Layer PDUs
 *
 *  \par Description
 *  This routine sends Access Layer PDUs to peer device.
 *
 *  \param [in] src_addr
 *         Source Address
 *
 *  \param [in] dst_addr
 *         Destination Address
 *
 *  \param [in] label
 *         Lable UUID, representing Virtual Address of Destination
 *
 *  \param [in] subnet_handle
 *         Handle identifying the Subnet
 *
 *  \param [in] appkey_handle
 *         Handle identifying the AppKey to be used for Transport Layer encryption.
 *
 *  \param [in] ttl
 *         Time to Live
 *
 *  \param [in] param
 *         Transport parameter, based on the type and header
 *
 *  \param [in] reliable
 *         If requires lower transport Ack, set reliable as TRUE
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_send_access_pdu
           (
               /* IN */ MS_NET_ADDR              src_addr,
               /* IN */ MS_NET_ADDR              dst_addr,
               /* IN */ UINT8                  * label,
               /* IN */ MS_SUBNET_HANDLE         subnet_handle,
               /* IN */ MS_APPKEY_HANDLE         appkey_handle,
               /* IN */ UINT8                    ttl,
               /* IN */ void                   * param,
               /* IN */ UINT8                    reliable
           );

/**
 *  \brief API to send transport Control PDUs
 *
 *  \par Description
 *  This routine sends transport Control PDUs to peer device.
 *
 *  \param [in] src_addr
 *         Source Address
 *
 *  \param [in] dst_addr
 *         Destination Address
 *
 *  \param [in] subnet_handle
 *         Handle identifying the Subnet
 *
 *  \param [in] ttl
 *         Time to Live
 *
 *  \param [in] ctrl_opcode
 *         Control Packet Opcode.
 *
 *  \param [in] param
 *         Transport parameter, based on the type and header
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_send_control_pdu
           (
               /* IN */ MS_NET_ADDR              src_addr,
               /* IN */ MS_NET_ADDR              dst_addr,
               /* IN */ MS_SUBNET_HANDLE         subnet_handle,
               /* IN */ UINT8                    ttl,
               /* IN */ MS_TRN_CTRL_PKT_OPCODE   ctrl_opcode,
               /* IN */ void                   * param
           );

/** \} */

/**
 * \name Low Power Feature Functions
 * \{
 */
/**
 *  \brief API to setup Friendship.
 *
 *  \par Description
 *  This routine is used by the device acting as a low power node
 *  to setup a friendship procedure to any available friend nodes.
 *
 *  \param [in] subnet_handle
 *         The subnet to initiate the friendship procedure.
 *
 *  \param [in] criteria
 *         Friend criteria that is required. RSSI, Receive Window,
 *         MessageQueue size requirements can be established.
 *
 *  \param [in] rx_delay
 *         Receive delay in milliseconds that the LPN will wait before
 *         listening to response for any request.
 *
 *  \param [in] poll_timeout
 *         Timeout in units of 100 milliseconds after which the LPN will send Poll PDU
 *         to check for data from the friend.
 *
 *  \param [in] setup_timeout
 *         Timeout in milliseconds for which the Friend Establishment
 *         procedure is to be tried.
 *
 *  \param [in] cb
 *         Application Callback to notify the result of friendship procedures.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_lpn_setup_friendship
           (
               /* IN */ MS_SUBNET_HANDLE subnet_handle,
               /* IN */ UCHAR criteria,
               /* IN */ UCHAR rx_delay,
               /* IN */ UINT32 poll_timeout,
               /* IN */ UINT32 setup_timeout,
               /* IN */ TRN_FRND_CB cb
           );


/**
 *  \brief API to terminate friendship.
 *
 *  \par Description
 *  This routine is used by the device acting as a low power node
 *  terminate friendship with an active Friend node.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_lpn_clear_friendship(void);


/**
 *  \brief API to manage friend subscription list.
 *
 *  \par Description
 *  This routine is used by the device acting as a low power node
 *  add/remove addresses to/from the friends subscription list.
 *
 *  \param [in] action
 *         Will be one of MS_TRN_CTRL_OPCODE_FRND_SUBSCRN_LIST_ADD or
 *         MS_TRN_CTRL_OPCODE_FRND_SUBSCRN_LIST_REMOVE
 *
 *  \param [in] addr_list
 *         Pointer to the packed list of addresses to be managed.
 *
 *  \param [in] count
 *         Number of addresses given.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_lpn_manage_subscription
           (
               UCHAR         action,
               UINT16       * addr_list,
               UINT16        count
           );

/**
 *  \brief To trigger Friend Poll from application
 *
 *  \par Description
 *  This routine enables the application to trigger a Friend Poll even before
 *  the expiry of an active poll period configured during the friendship
 *  establishment.
 *  The poll period will get reset at this point.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_lpn_poll (void);
/** \} */

/**
 * \name Friend Feature Functions
 * \{
 */
/**
 *  \brief To check if address matches with any of the LPN
 *
 *  \par Description
 *  This routine checks if destination address in a received packet matches
 *  with any of the known element address of LPN.
 *
 *  \param [in]  addr           Unicast Address to search
 *  \param [out] lpn_handle     LPN Handle on match
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_is_valid_lpn_element_address
           (
               /* IN */  MS_NET_ADDR     addr,
               /* OUT */ LPN_HANDLE    * lpn_handle
           );

/**
 *  \brief To check if valid subscription address of an LPN to receive a packet
 *
 *  \par Description
 *  This routine checks if destination address in a received packet matches
 *  with any of the known subscription address of an LPN.
 *
 *  \param [in]  addr          Address to search
 *  \param [out] lpn_handle    Pointer to an LPN Handle, which will be filled
 *                             if match found
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_is_valid_lpn_subscription_address
           (
               /* IN */  MS_NET_ADDR     addr,
               /* OUT */ LPN_HANDLE    * lpn_handle
           );

/**
 *  \brief To get Poll Timeout of an LPN
 *
 *  \par Description
 *  This routine checks if LPN address is valid and then returns
 *  Poll Timeout configured for the LPN.
 *
 *  \param [in]  lpn_addr        LPN Address to search
 *  \param [out] poll_timeout    Memory where poll timeout of the LPN to be filled
 *                               (if match found)
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_get_lpn_polltimeout
           (
               /* IN */  MS_NET_ADDR    lpn_addr,
               /* OUT */ UINT32       * poll_timeout
           );

/**
 *  \brief To get the LPN node information
 *
 *  \par Description
 *  This routine fetches the node information of the LPN element at the
 *  given index
 *
 *  \param [in]  role          Local friendship role
 *  \param [in]  lpn_index     Index of the LPN element
 *  \param [out] node          Pointer to copy the information
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_get_frndship_info
           (
               UINT8 role,
               UINT16 lpn_index,
               MS_TRN_FRNDSHIP_INFO * node
           );

/**
 *  \brief To add the security update information
 *
 *  \par Description
 *  This routine updates the security state of the network to all the active
 *  LPN elements. This will be forwarded to the elements when it polls for the
 *  next packet available.
 *
 *  \param [in] subnet_handle    Handle to identity the network.
 *  \param [in] flag             Flag indicating the Key Refresh and IV Update state.
 *  \param [in] ivindex          Current IV Index of the network.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_lpn_register_security_update
           (
               /* IN */ MS_SUBNET_HANDLE    subnet_handle,
               /* IN */ UCHAR               flag,
               /* IN */ UINT32              ivindex
           );

/**
 *  \brief To clear information related to all LPNs
 *
 *  \par Description
 *  This routine clears information related to all LPNs.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_clear_all_lpn
           (
               void
           );
/** \} */

/**
 * \name Heartbeat Functions
 * \{
 */

/**
 *  \brief To set the Heartbeat publication data
 *
 *  \par Description
 *  This routine configures the Heartbeat publication information
 *
 *  \param [out] info    Heartbeat Publication information data as
 *                       in \ref MS_TRN_HEARTBEAT_PUBLICATION_INFO
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_set_heartbeat_publication
           (
               /* INOUT */ MS_TRN_HEARTBEAT_PUBLICATION_INFO * info
           );

/**
 *  \brief To get the Heartbeat publication data
 *
 *  \par Description
 *  This routine retrieves the Heartbeat publication information
 *
 *  \param [out] info    Heartbeat Publication information data as
 *                       in \ref MS_TRN_HEARTBEAT_PUBLICATION_INFO
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_get_heartbeat_publication
           (
               /* OUT */ MS_TRN_HEARTBEAT_PUBLICATION_INFO * info
           );


/**
 *  \brief To set the Heartbeat subscription data
 *
 *  \par Description
 *  This routine configures the Heartbeat subscription information
 *
 *  \param [in, out] info    Heartbeat Subscription information data as
 *                           in \ref MS_TRN_HEARTBEAT_SUBSCRIPTION_INFO
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_set_heartbeat_subscription
           (
               /* INOUT */ MS_TRN_HEARTBEAT_SUBSCRIPTION_INFO * info
           );

/**
 *  \brief To get the Heartbeat subscription data
 *
 *  \par Description
 *  This routine retrieves the Heartbeat subscription information
 *
 *  \param [out] info    Heartbeat Subscription information data as
 *                       in \ref MS_TRN_HEARTBEAT_SUBSCRIPTION_INFO
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_get_heartbeat_subscription
           (
               /* OUT */ MS_TRN_HEARTBEAT_SUBSCRIPTION_INFO * info
           );

/**
 *  \brief To trigger Heartbeat send on change in feature
 *
 *  \par Description
 *  This routine triggers the Heartbeat send on change in state of supported
 *  features.
 *
 *  \param [in] change_in_feature_bit    Bit mask of the changed feature field
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
API_RESULT MS_trn_trigger_heartbeat (/* IN */ UINT8 change_in_feature_bit);

/** \} */

/** \} */

/**
 *  \addtogroup trn_defines Defines
 *  \{
 */

/**
 * \defgroup trn_marcos Utility Macros
 * \{
 * \brief This section describes the various Utility Macros in EtherMind
 * Mesh Transport Layer.
 */

/**
 * \name LPN Macros
 * \{
 */
/**
 *  \brief API to add to friend subscription list.
 *
 *  \par Description
 *  This routine is used by the device acting as a low power node
 *  add addresses to the friends subscription list.
 *
 *  \param [in] addr_list
 *         Pointer to the list of addresses to be managed.
 *
 *  \param [in] count
 *         Number of addresses given.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_trn_lpn_subscrn_list_add(addr_list, count)\
        MS_trn_lpn_manage_subscription\
        (\
            MS_TRN_CTRL_OPCODE_FRND_SUBSCRN_LIST_ADD,\
            (addr_list),\
            (count)\
        );

/**
 *  \brief API to remove from friend subscription list.
 *
 *  \par Description
 *  This routine is used by the device acting as a low power node
 *  remove addresses from the friends subscription list.
 *
 *  \param [in] addr_list
 *         Pointer to the list of addresses to be managed.
 *
 *  \param [in] count
 *         Number of addresses given.
 *
 *  \return API_SUCCESS or an error code indicating reason for failure
 */
#define MS_trn_lpn_subscrn_list_remove(addr_list, count)\
        MS_trn_lpn_manage_subscription\
        (\
            MS_TRN_CTRL_OPCODE_FRND_SUBSCRN_LIST_REMOVE,\
            (addr_list),\
            (count)\
        );
/** \} */

/** \} */

/** \} */

#ifdef __cplusplus
};
#endif

/** \} */

#endif /* _H_MS_TRN_API_ */

