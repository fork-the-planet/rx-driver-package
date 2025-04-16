/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_phid_config.h
 * Version      : 1.44
 * Description  : USB Peripheral HID configuration
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

#ifndef R_USB_PHID_CONFIG_H
#define R_USB_PHID_CONFIG_H

/*****************************************************************************
 Macro definitions (USER DEFINE)
 ******************************************************************************/
/** [Setting pipe to be used]
 * USB_CFG_PHID_INT_IN  : Pipe number (USB_PIPE6 to USB_PIPE9) HID Interrupt In Pipe
 * USB_CFG_PHID_INT_OUT : Pipe number (USB_PIPE6 to USB_PIPE9) HID Interrupt Out Pipe
 */
#define USB_CFG_PHID_INT_IN               (USB_PIPE6)
#define USB_CFG_PHID_INT_OUT              (USB_PIPE7)

#endif  /* __R_USB_PHID_CONFIG_H__ */
/******************************************************************************
 End  Of File
 ******************************************************************************/
