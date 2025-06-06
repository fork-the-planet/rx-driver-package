/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_phid.h
 * Version      : 1.44
 * Description  : USB Peripheral HID header file
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 30.09.2015 1.11 First Release
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Deleted functions and variables.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

#ifndef R_USB_PHID_H
#define R_USB_PHID_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define     USB_EP_B_DESCRIPTORTYPE     (1u)                /* Descriptor type */

/*****************************************************************************
 Exported global variables
 ******************************************************************************/
/* variables */
extern void usb_set_event (usb_status_t event, usb_ctrl_t *ctrl);

/*****************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/


#endif  /* #ifndef R_USB_PHID_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
