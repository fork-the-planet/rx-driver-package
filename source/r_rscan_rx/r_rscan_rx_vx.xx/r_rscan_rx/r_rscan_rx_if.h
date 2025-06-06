/***********************************************************************************************************************
* Copyright (c) 2015 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_rscan_rx_if.h
* Description  : This module provides the interface file to be included by the user when using the RSCAN driver module.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           22.03.2015 1.00    Initial Release
*           12.09.2016 1.10    Added support for RX230, RX24T-512, and RX24U
*                              Added CAN_RSK_20MHZ_XTAL_500KBPS_xxx equates.
*           06.12.2018 1.20    Fixed big endian bug. Added __evenaccess to private structure and union definitions.
*           01.02.2019 1.21    Changed Minor version to 1.21.
*           20.05.2019 2.00    Add support for GNUC and ICCRX.
*           28.05.2019 2.10    Added support for RX23W.
*           15.10.2019 2.20    Added support for RX23E-A
*                              Fixed warning in IAR
*           31.03.2020 2.21    Changed Minor version to 2.21.
*           30.06.2020 2.30    Changed Minor version to 2.30.
*           30.10.2020 2.31    Changed Minor version to 2.31.
*           13.09.2021 2.32    Changed Minor version to 2.32.
*           11.11.2021 2.40    Added support for RX140 (products with 128-Kbyte or larger ROM).
*           30.06.2022 2.41    Changed the default value of CAN clock source to PCLK.
*           29.07.2022 2.50    Updated demo projects
*                              Fixed RXMBX enum error
*           21.03.2023 2.60    Added new demo project
*           29.05.2023 2.70    Added support for RX23E-B.
*                              Fixed fifo threshold enum error.
*                              Updated according to GSCE Code Checker 6.50.
*           17.11.2023 2.80    Added CAN_ERR_TIME_OUT return to while loop in R_CAN_Open, R_CAN_Control, and
*                              R_CAN_SendMsg function.
*                              Added WAIT_LOOP comments.
*           06.09.2024 2.90    Added support Nested Interrupt.
*                              Added description of supported RX231.
*                              Modified code to support only RX24T chip version B.
*                              Removed support for RX230.
*           15.03.2025 2.91    Updated disclaimer.
***********************************************************************************************************************/

#ifndef CAN_INTERFACE_HEADER_FILE
#define CAN_INTERFACE_HEADER_FILE

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

#if ((BSP_MCU_RX24T == 1) && (BSP_RAM_SIZE_BYTES < 32768))
    #error  "ERROR - Only RX24T Version B Products support RSCAN Module."
#endif

/* Version Number of API. */
#define CAN_VERSION_MAJOR           (2)
#define CAN_VERSION_MINOR           (91)

/* Channel numbers */
#define CAN_CH0                     (0)

/* R_CAN_GetStatus() Masks */

/* CAN_STAT_CH_TXMBX_SENT, CAN_STAT_CH_TXMBX_ABORTED */
#define CAN_MASK_TXMBX_0            (0x0001)
#define CAN_MASK_TXMBX_1            (0x0002)
#define CAN_MASK_TXMBX_2            (0x0004)
#define CAN_MASK_TXMBX_3            (0x0008)

/* CAN_STAT_RXMBX_FULL */
#define CAN_MASK_RXMBX_0            (0x0001)
#define CAN_MASK_RXMBX_1            (0x0002)
#define CAN_MASK_RXMBX_2            (0x0004)
#define CAN_MASK_RXMBX_3            (0x0008)

/* CAN_STAT_FIFO_EMPTY, CAN_STAT_FIFO_THRESHOLD, CAN_STAT_FIFO_OVFL */
#define CAN_MASK_RXFIFO_0           (0x00000001)
#define CAN_MASK_RXFIFO_1           (0x00000002)
#define CAN_MASK_TXFIFO             (0x00000100)
#define CAN_MASK_HIST_FIFO          (0x00800000)

/* CAN_STAT_GLOBAL_ERR */
#define CAN_MASK_ERR_DLC            (0x0001)
#define CAN_MASK_ERR_RX_OVFL        (0x0002)
#define CAN_MASK_ERR_HIST_OVFL      (0x0004)
#define CAN_MASK_ERR_FIFO_OVFL      (0x0006)

/* CAN_STAT_CH_ERROR */
#define CAN_MASK_ERR_PROTOCOL       (0x0001)
#define CAN_MASK_ERR_WARNING        (0x0002)
#define CAN_MASK_ERR_PASSIVE        (0x0004)
#define CAN_MASK_ERR_BUS_OFF_ENTRY  (0x0008)
#define CAN_MASK_ERR_BUS_OFF_EXIT   (0x0010)
#define CAN_MASK_ERR_OVERLOAD       (0x0020)
#define CAN_MASK_ERR_DOMINANT_LOCK  (0x0040)
#define CAN_MASK_ERR_ARB_LOST       (0x0080)
#define CAN_MASK_ERR_STUFF          (0x0100)
#define CAN_MASK_ERR_FORM           (0x0200)
#define CAN_MASK_ERR_ACK            (0x0400)
#define CAN_MASK_ERR_CRC            (0x0800)
#define CAN_MASK_ERR_RECESSIVE_BIT  (0x1000)
#define CAN_MASK_ERR_DOMINANT_BIT   (0x2000)
#define CAN_MASK_ERR_ACK_DELIMITER  (0x4000)

#define TRUE        (1)
#define FALSE       (0)
#define CAN_UNUSED  (0)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Mailbox and FIFO box IDs */
#define CAN_FLG_TXMBX           (0x80000000)
#define CAN_FLG_RXMBX           (0x40000000)
#define CAN_FLG_FIFO            (0x20000000)

typedef enum e_can_box
{
    CAN_BOX_NONE              = 0,  /* unused parameter value */

    CAN_BOX_TXMBX_0           = (CAN_FLG_TXMBX | 0),
    CAN_BOX_TXMBX_1           = (CAN_FLG_TXMBX | 1),
    CAN_BOX_TXMBX_2           = (CAN_FLG_TXMBX | 2),
    CAN_BOX_TXMBX_3           = (CAN_FLG_TXMBX | 3),

    CAN_BOX_RXMBX_0           = (CAN_FLG_RXMBX | 0),
    CAN_BOX_RXMBX_1           = (CAN_FLG_RXMBX | 1),
    CAN_BOX_RXMBX_2           = (CAN_FLG_RXMBX | 2),
    CAN_BOX_RXMBX_3           = (CAN_FLG_RXMBX | 3),

    CAN_BOX_RXFIFO_0          = (CAN_FLG_FIFO | CAN_MASK_RXFIFO_0),
    CAN_BOX_RXFIFO_1          = (CAN_FLG_FIFO | CAN_MASK_RXFIFO_1),

    CAN_BOX_TXFIFO            = (CAN_FLG_FIFO | CAN_MASK_TXFIFO),
    CAN_BOX_HIST_FIFO         = (CAN_FLG_FIFO | CAN_MASK_HIST_FIFO)
} can_box_t;

/* Callback Function Events */
typedef enum e_can_cb_evt           /* callback function events */
{
    /* Main Callback Events */
    CAN_EVT_RXFIFO_THRESHOLD,       /* RX FIFO threshold */
    CAN_EVT_GLOBAL_ERR,             /* RX or History FIFO overflow, or DLC error */

    /* Channel Callback Events */
    CAN_EVT_TRANSMIT,               /* mbx tx complete or aborted, tx or history FIFO threshold */
    CAN_EVT_CHANNEL_ERR,
} can_cb_evt_t;

/* API Error Codes */
typedef enum e_can_err          // CAN API error codes
{
    CAN_SUCCESS=0,
    CAN_ERR_OPENED,             // Call to Open already made
    CAN_ERR_NOT_OPENED,         // Call to Open not yet made
    CAN_ERR_INIT_DONE,          // Call to InitChan already made for specified channel
    CAN_ERR_CH_NO_INIT,         // Channel not initialized
    CAN_ERR_INVALID_ARG,        // Invalid argument passed to function
    CAN_ERR_MISSING_CALLBACK,   // Callback function not provided and interrupts requested
    CAN_ERR_MAX_RULES,          // 16 rules already present
    CAN_ERR_BOX_FULL,           // Transmit mailbox or FIFO is full
    CAN_ERR_BOX_EMPTY,          // Receive mailbox or FIFO is full
    CAN_ERR_ILLEGAL_MODE,       // Not in proper mode for request
    CAN_ERR_TIME_OUT            // Time Out error
} can_err_t;

/* R_CAN_Open() */
typedef enum e_can_timestamp_src
{
    CAN_TIMESTAMP_SRC_HALF_PCLK = 0,
    CAN_TIMESTAMP_SRC_CANMCLK   = 1,    // obtained from EXTAL pin
    CAN_TIMESTAMP_SRC_END_ENUM
} can_timestamp_src_t;

typedef enum e_can_timestamp_div
{
    CAN_TIMESTAMP_DIV_1     = 0,
    CAN_TIMESTAMP_DIV_2     = 1,
    CAN_TIMESTAMP_DIV_4     = 2,
    CAN_TIMESTAMP_DIV_8     = 3,
    CAN_TIMESTAMP_DIV_16    = 4,
    CAN_TIMESTAMP_DIV_32    = 5,
    CAN_TIMESTAMP_DIV_64    = 6,
    CAN_TIMESTAMP_DIV_128   = 7,
    CAN_TIMESTAMP_DIV_256   = 8,
    CAN_TIMESTAMP_DIV_512   = 9,
    CAN_TIMESTAMP_DIV_1024  = 10,
    CAN_TIMESTAMP_DIV_2048  = 11,
    CAN_TIMESTAMP_DIV_4096  = 12,
    CAN_TIMESTAMP_DIV_8192  = 13,
    CAN_TIMESTAMP_DIV_16384 = 14,
    CAN_TIMESTAMP_DIV_32768 = 15,
    CAN_TIMESTAMP_DIV_END_ENUM
} can_timestamp_div_t;

typedef struct st_can_cfg
{
    can_timestamp_src_t     timestamp_src;
    can_timestamp_div_t     timestamp_div;
} can_cfg_t;


/* R_CAN_InitChan() */
typedef struct st_can_bitrate
{
    uint16_t    prescaler;  // 1-1024
    uint8_t     tseg1;      // 4-16
    uint8_t     tseg2;      // 2-8
    uint8_t     sjw;        // 1-4
} can_bitrate_t;

/* Sample settings for 500kbps */
#define CAN_RSK_27MHZ_PCLKB_500KBPS_PRESCALER   (3)
#define CAN_RSK_27MHZ_PCLKB_500KBPS_TSEG1       (5)
#define CAN_RSK_27MHZ_PCLKB_500KBPS_TSEG2       (3)
#define CAN_RSK_27MHZ_PCLKB_500KBPS_SJW         (1)

#define CAN_RSK_32MHZ_PCLKB_500KBPS_PRESCALER   (2)
#define CAN_RSK_32MHZ_PCLKB_500KBPS_TSEG1       (11)
#define CAN_RSK_32MHZ_PCLKB_500KBPS_TSEG2       (4)
#define CAN_RSK_32MHZ_PCLKB_500KBPS_SJW         (4)

/* RSKRX231/RSKRX23W/RSKRX23E-A has an 8MHz XTAL clock alternate settings*/
#define CAN_RSK_8MHZ_XTAL_500KBPS_PRESCALER     (1)       /* 2 */
#define CAN_RSK_8MHZ_XTAL_500KBPS_TSEG1         (10)      /* 5 */
#define CAN_RSK_8MHZ_XTAL_500KBPS_TSEG2         (5)       /* 2 */
#define CAN_RSK_8MHZ_XTAL_500KBPS_SJW           (1)       /* 1 */

/* RSKRX24T and RSKRX24U have a 20MHz XTAL clock*/
#define CAN_RSK_20MHZ_XTAL_500KBPS_PRESCALER    (2)
#define CAN_RSK_20MHZ_XTAL_500KBPS_TSEG1        (15)
#define CAN_RSK_20MHZ_XTAL_500KBPS_TSEG2        (4)
#define CAN_RSK_20MHZ_XTAL_500KBPS_SJW          (1)

/* R_CAN_ConfigFIFO() */
typedef enum e_can_fifo_threshold       /* NOTE: History FIFO (8 deep) can only have a threshold of 1 or 6 */
{
    CAN_FIFO_THRESHOLD_1    = 1,        // every message
    CAN_FIFO_THRESHOLD_2    = 3,        // 4/8 of 4
    CAN_FIFO_THRESHOLD_3    = 5,        // 6/8 of 4
    CAN_FIFO_THRESHOLD_6    = 6,        // History FIFO Only!
    CAN_FIFO_THRESHOLD_FULL = 7,        // 8/8 of 4
    CAN_FIFO_THRESHOLD_END_ENUM
} can_fifo_threshold_t;

/* R_CAN_AddRxRule() */
typedef struct st_can_filter
{
    uint8_t     check_ide:1;
    uint8_t     ide;
    uint8_t     check_rtr:1;
    uint8_t     rtr;
    uint32_t    id;
    uint32_t    id_mask;
    uint8_t     min_dlc;
    uint16_t    label;          // 12-bit label
} can_filter_t;


/* R_CAN_SendMsg() */
typedef struct st_can_txmsg
{
    uint8_t     ide;
    uint8_t     rtr;
    uint32_t    id;
    uint8_t     dlc;
    uint8_t     data[8];
    bool        one_shot;       // no retries on error; txmbx only
    bool        log_history;    // true if want to log
    uint8_t     label;          // 8-bit label for History FIFO
} can_txmsg_t;

/* R_CAN_GetMsg() */
typedef struct st_can_rxmsg
{
    uint8_t     ide;
    uint8_t     rtr;
    uint32_t    id;
    uint8_t     dlc;
    uint8_t     data[8];
    uint16_t    label;          // 12-bit label from receive rule
    uint16_t    timestamp;
} can_rxmsg_t;

/* R_CAN_GetHistoryEntry() */
typedef struct st_can_history
{
    can_box_t   box_id;         // box which sent message
    uint8_t     label;          // associated 8-bit label
} can_history_t;

/* R_CAN_GetStatusMask() (masks defined at top of file) */
typedef enum e_can_stat
{
    CAN_STAT_FIFO_EMPTY,
    CAN_STAT_FIFO_THRESHOLD,
    CAN_STAT_FIFO_OVFL,         // bits reset after reading
    CAN_STAT_RXMBX_FULL,
    CAN_STAT_GLOBAL_ERR,        // DLC error bit is reset after reading
    CAN_STAT_CH_TXMBX_SENT,     // bits reset after reading
    CAN_STAT_CH_TXMBX_ABORTED,  // bits reset after reading
    CAN_STAT_CH_ERROR,          // bits reset after reading
    CAN_STAT_END_ENUM
} can_stat_t;


/* R_CAN_GetCountErr() */
typedef enum e_can_count
{
    CAN_COUNT_RX_ERR,
    CAN_COUNT_TX_ERR,
    CAN_COUNT_END_ENUM
} can_count_t;

/* R_CAN_Control() */
typedef enum e_can_cmd
{
    CAN_CMD_ABORT_TX,                       // argument: transmit mailbox id
    CAN_CMD_RESET_TIMESTAMP,
    CAN_CMD_SET_MODE_COMM,                  // start normal bus communications
    CAN_CMD_SET_MODE_TST_STANDARD,
    CAN_CMD_SET_MODE_TST_LISTEN,
    CAN_CMD_SET_MODE_TST_EXT_LOOPBACK,
    CAN_CMD_SET_MODE_TST_INT_LOOPBACK,
    CAN_CMD_END_ENUM
} can_cmd_t;

/*****************************************************************************
Public functions
******************************************************************************/
/******************************************************************************
* Function Name: R_CAN_Open
*******************************************************************************/
can_err_t R_CAN_Open(can_cfg_t  *p_cfg,
                     void       (* const p_callback)(can_cb_evt_t   event,
                                                     void           *p_args));

/******************************************************************************
* Function Name: R_CAN_InitChan
*******************************************************************************/
can_err_t R_CAN_InitChan(uint8_t        chan,
                         can_bitrate_t  *p_baud,
                         void           (* const p_chcallback)(uint8_t      chan,
                                                               can_cb_evt_t event,
                                                               void         *p_args));

/******************************************************************************
* Function Name: R_CAN_ConfigFIFO
*******************************************************************************/
can_err_t R_CAN_ConfigFIFO(can_box_t            fifo_id,
                           can_fifo_threshold_t threshold,
                           can_box_t            txmbx_id);

/******************************************************************************
* Function Name: R_CAN_AddRxRule
*******************************************************************************/
can_err_t R_CAN_AddRxRule(uint8_t       chan,
                          can_filter_t  *p_filter,
                          can_box_t     dst_box);

/******************************************************************************
* Function Name: R_CAN_Control
*******************************************************************************/
can_err_t R_CAN_Control(can_cmd_t   cmd,
                        uint32_t    arg1);

/******************************************************************************
* Function Name: R_CAN_SendMsg
*******************************************************************************/
can_err_t R_CAN_SendMsg(can_box_t   box_id,
                        can_txmsg_t *p_txmsg);

/******************************************************************************
* Function Name: R_CAN_GetMsg
*******************************************************************************/
can_err_t R_CAN_GetMsg(can_box_t    box_id,
                       can_rxmsg_t  *p_rxmsg);

/******************************************************************************
* Function Name: R_CAN_GetHistoryEntry
*******************************************************************************/
can_err_t R_CAN_GetHistoryEntry(can_box_t       box_id,
                                can_history_t   *p_entry);

/******************************************************************************
* Function Name: R_CAN_GetStatusMask
*******************************************************************************/
uint32_t  R_CAN_GetStatusMask(can_stat_t    stat_type,
                              uint8_t       chan,
                              can_err_t     *p_err);

/******************************************************************************
* Function Name: R_CAN_GetCountFIFO
*******************************************************************************/
uint32_t  R_CAN_GetCountFIFO(can_box_t  box_id,
                             can_err_t  *p_err);

/******************************************************************************
* Function Name: R_CAN_GetCountErr
*******************************************************************************/
uint32_t  R_CAN_GetCountErr(can_count_t  count_type,
                            uint8_t      chan,
                            can_err_t    *p_err);

/******************************************************************************
* Function Name: R_CAN_Close
*******************************************************************************/
void      R_CAN_Close(void);

/******************************************************************************
* Function Name: R_CAN_GetVersion
*******************************************************************************/
uint32_t  R_CAN_GetVersion(void);

#endif /* CAN_INTERFACE_HEADER_FILE*/
