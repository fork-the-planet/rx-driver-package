/*
* Copyright (c) 2018(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*******************************************************************************
 * File Name    : r_usb_hmsc_mini_config.h
 * Description  : USB Host MSC configuration
 ******************************************************************************/
/*******************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 30.11.2018 1.10 First Release
 *         : 20.03.2025 1.31 Changed the disclaimer.
 ******************************************************************************/

#ifndef R_USB_HMSC_MINI_CONFIG_H
#define R_USB_HMSC_MINI_CONFIG_H

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Setting pipe to be used]
 * USB_CFG_PMSC_BULK_IN     : Pipe number (USB_PIPE1 to USB_PIPE5)  MSC Bulk In Pipe
 * USB_CFG_PMSC_BULK_OUT    : Pipe number (USB_PIPE1 to USB_PIPE5)  MSC Bulk Out Pipe
 */
#define USB_CFG_HMSC_BULK_IN        (USB_PIPE1)
#define USB_CFG_HMSC_BULK_OUT       (USB_PIPE2)


#endif  /* R_USB_HMSC_MINI_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
