/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*******************************************************************************
* File Name    : r_usb_hcdc_mini_config_reference.h
* Version      : 1.31
* Description  : Definition of user macro
*******************************************************************************/
/*******************************************************************************
 * History   : DD.MM.YYYY Version Description
 *           : 01.09.2014 1.00    First Release
 *           : 01.06.2015 1.01    Added RX231.
 *           : 30.11.2018 1.10    Supporting Smart Configurator
 *           : 31.05.2019 1.11    Added support for GNUC and ICCRX.
 *           : 20.03.2025 1.31    Changed the disclaimer.
 *******************************************************************************/

#ifndef R_USB_HCDC_MINI_CONFIG_H
#define R_USB_HCDC_MINI_CONFIG_H

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Select CDC Interface class]
 * USB_CFG_VEN         : CDC Device Vendor class
 * USB_CFG_CDC         : CDC Device CDC class(CDC-Data & CDC-Control)
 */
#define USB_CFG_HCDC_IFCLS       USB_CFG_CDC

/** [Setting pipe to be used]
 * USB_CFG_HCDC_BULK_IN   : Pipe number (USB_PIPE1 to USB_PIPE5)  1st Device CDC Data class Bulk In Pipe
 * USB_CFG_HCDC_BULK_OUT  : Pipe number (USB_PIPE1 to USB_PIPE5)  1st Device CDC Data class Bulk Out Pipe
 * USB_CFG_HCDC_INT_IN    : Pipe number (USB_PIPE6 to USB_PIPE9)  1st Device CDC Data class Interrupt In Pipe
 */
#define USB_CFG_HCDC_BULK_IN        (USB_PIPE1)
#define USB_CFG_HCDC_BULK_OUT       (USB_PIPE2)
#define USB_CFG_HCDC_INT_IN         (USB_PIPE6)

#endif  /* R_USB_HCDC_MINI_CONFIG_H */
/******************************************************************************
End of file
******************************************************************************/
