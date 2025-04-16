/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_pmsc_config.h
 * Version      : 1.44
 * Description  : USB Peripheral MSC configuration
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 31.05.2019 1.26 Added support for GNUC and ICCRX.
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

#ifndef R_USB_PMSC_CONFIG_H
#define R_USB_PMSC_CONFIG_H

/*****************************************************************************
 Macro definitions (USER DEFINE)
 ******************************************************************************/
/** [Setting pipe to be used]
 * USB_CFG_PMSC_BULK_IN     : Pipe number (USB_PIPE1 to USB_PIPE5)  MSC Bulk In Pipe
 * USB_CFG_PMSC_BULK_OUT    : Pipe number (USB_PIPE1 to USB_PIPE5)  MSC Bulk Out Pipe
 */
#define USB_CFG_PMSC_BULK_IN        (USB_PIPE1)
#define USB_CFG_PMSC_BULK_OUT       (USB_PIPE2)

/* Vendor Information in INQUIRY Data Format */
/* Note : Be sure to specify 8 bytes of data in double quotation marks. */
#define USB_CFG_PMSC_VENDOR             ("Vendor  ")

/* Product Identification in INQUIRY Data Format */
/* Note : Be sure to specify 16 bytes of data in double quotation marks. */
#define USB_CFG_PMSC_PRODUCT            ("Mass Storage    ")

/* Product Revision Level in INQUIRY Data Format */
/* Note : Be sure to specify 4 bytes of data in double quotation marks. */
#define USB_CFG_PMSC_REVISION           ("1.00")

/* Number of data blocks transferred at one time (512 * N) */
#define USB_CFG_PMSC_TRANS_COUNT        (8)


#endif  /* R_USB_PMSC_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
