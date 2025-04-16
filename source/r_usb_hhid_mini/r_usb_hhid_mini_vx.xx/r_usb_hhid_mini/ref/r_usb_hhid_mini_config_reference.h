/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_hhid_mini_config.h
 * Description  : USB Host HID User definition
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           : 01.09.2014 1.00    First Release
 *           : 30.11.2018 1.10    Supporting Smart Configurator
 *           : 20.03.2025 1.31    Changed the disclaimer
 ***********************************************************************************************************************/
#ifndef R_USB_HHID_MINI_CONFIG_H
#define R_USB_HHID_MINI_CONFIG_H

/*****************************************************************************
 Macro definitions (USER DEFINE)
 ******************************************************************************/
/** [Setting pipe to be used]
 * USB_CFG_HHID_INT_IN      : Pipe number (USB_PIPE6 to USB_PIPE9) 1st Device HID Interrupt In Pipe
 */
#define USB_CFG_HHID_INT_IN         (USB_PIPE6)

/** [Setting pipe to be used]
 * USB_CFG_HHID_INT_OUT     : Pipe number (USB_PIPE6 to USB_PIPE9) 1st Device HID Interrupt Out Pipe
 */
#define USB_CFG_HHID_INT_OUT        (USB_PIPE7)


#endif  /* R_USB_HHID_MINI_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
