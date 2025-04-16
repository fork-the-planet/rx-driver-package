/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*******************************************************************************
 * File Name    : r_usb_phid_mini_config.h
 * Description  : USB Peripheral HID configuration
 ******************************************************************************/
/*******************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 01.09.2014 1.00     First Release
 *         : 30.11.2018 1.10     Supporting Smart Configurator
 *         : 20.03.2025 1.31     Changed the disclaimer.
 ******************************************************************************/

#ifndef R_USB_PHID_MINI_CONFIG_H
#define R_USB_PHID_MINI_CONFIG_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Setting pipe to be used]
 * USB_CFG_PHID_INT_IN   : Pipe number (USB_PIPE6 to USB_PIPE9) 1st Device HID Interrupt In Pipe
 * USB_CFG_PHID_INT_OUT  : Pipe number (USB_PIPE6 to USB_PIPE9) 1st Device HID Interrupt Out Pipe
 * USB_CFG_PHID_INT_IN2  : Pipe number (USB_PIPE6 to USB_PIPE9) 2channel In Pipe
 * USB_CFG_PHID_INT_OUT2 : Pipe number (USB_PIPE6 to USB_PIPE9) 2channel Out Pipe
 */
#define USB_CFG_PHID_INT_IN               (USB_PIPE6)
#define USB_CFG_PHID_INT_OUT              (USB_PIPE7)
#define USB_CFG_PHID_INT_IN2              (USB_PIPE8)
#define USB_CFG_PHID_INT_OUT2             (USB_PIPE9)

#endif  /* R_USB_PHID_MINI_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
