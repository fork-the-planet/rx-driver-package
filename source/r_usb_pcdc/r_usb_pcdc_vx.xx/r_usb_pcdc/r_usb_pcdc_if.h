/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_pcdc_if.h
 * Version      : 1.44
 * Description  : Interface file for USB PCDC API
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Fix typedef struct "usb_serial_state_bitmap_t".
 *                           Deleted export variables and functions "g_cdc_trans_len","R_USB_PcdcSetInterface",
 *                           "R_USB_PcdcSendData","R_USB_PcdcReceiveData",
 *                           "R_USB_PcdcSerialStateNotification","R_USB_PcdcCtrltrans",
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 31.05.2019 1.26 Added support for GNUC and ICCRX.
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

#ifndef USB_PCDC_IF_H
#define USB_PCDC_IF_H

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_pcdc_config.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/
/* CDC Class Requests IDs*/
#define USB_PCDC_SET_LINE_CODING            (0x2000u)
#define USB_PCDC_GET_LINE_CODING            (0x2100u)
#define USB_PCDC_SET_CONTROL_LINE_STATE     (0x2200u)

/* setup packet table size (uint16_t * 5) */
#define     USB_CDC_SETUP_TBL_BSIZE             (10u)

/*******************************************************************************
 Typedef definitions
 *******************************************************************************/

R_BSP_PRAGMA_UNPACK
typedef struct
{
    union {
        uint16_t    WORD;
        /* CPU bit order rigth */
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_8(
            uint16_t brx_carrier  :1,   /* DCD signal */
            uint16_t btx_carrier  :1,   /* DSR signal */
            uint16_t bbreak       :1,   /* State of break detection mechanism of the device */
            uint16_t bring_signal :1,   /* State of ring signal detection of the device */
            uint16_t bframing     :1,   /* Framing error */
            uint16_t bparity      :1,   /* Parity error */
            uint16_t bover_run    :1,   /* Over Run error */
            uint16_t rsv          :9    /* Reserve */
        )BIT;
    };
} usb_serial_state_bitmap_t;
R_BSP_PRAGMA_PACKOPTION

/* Class Notification Serial State */
typedef union
{
    uint32_t                    word;
    usb_serial_state_bitmap_t   bit;
} usb_sci_serialstate_t;        /*USB_SCI_SerialState_t; */

typedef struct
{
    uint32_t dw_dte_rate;       /* Data terminal rate, in bits per second */
    uint8_t  b_char_format;     /* Stop bits */
    uint8_t  b_parity_type;     /* Parity */
    uint8_t  b_data_bits;       /* Data bits */
    uint8_t  rsv;               /* reserve */
} usb_pcdc_linecoding_t;        /* USB_PCDC_LineCoding_t; */

R_BSP_PRAGMA_UNPACK
typedef struct
{
    union {
        uint16_t    WORD;
        /* CPU bit order rigth */
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_3(
            uint16_t bdtr :1,       /* DTR */
            uint16_t brts :1,       /* RTS */
            uint16_t rsv  :14       /* Reserve */
        )BIT;
    };
} usb_pcdc_ctrllinestate_t;     /* USB_PCDC_ControlLineState_t; */
R_BSP_PRAGMA_PACKOPTION

#endif /* USB_PCDC_IF_H */

/***********************************************************************************************************************
End  Of File
***********************************************************************************************************************/