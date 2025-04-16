/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_hcdc_config.h
 * Version      : 1.44
 * Description  : USB Host CDC User definition
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

#ifndef R_USB_HCDC_CONFIG_H
#define R_USB_HCDC_CONFIG_H

/*****************************************************************************
 Macro definitions (USER DEFINE)
 ******************************************************************************/
/** [Setting connection of multiple CDC devices]
 * USB_CFG_ENABLE         : Multiple connection supported
 * USB_CFG_DISABLE        : Multiple connection not supported
 */
#define USB_CFG_HCDC_MULTI          (USB_CFG_ENABLE)
 
/** [Setting CDC class]
 * USB_CFG_CDC            : CDC class supported device
 * USB_CFG_VEN            : Vendor class device
 */
#define USB_CFG_HCDC_IFCLS          (USB_CFG_CDC)
 
/** [Setting pipe to be used]
 * USB_CFG_HCDC_BULK_IN   : Pipe number (USB_PIPE1 to USB_PIPE5)  1st Device CDC Data class Bulk In Pipe
 * USB_CFG_HCDC_BULK_OUT  : Pipe number (USB_PIPE1 to USB_PIPE5)  1st Device CDC Data class Bulk Out Pipe
 * USB_CFG_HCDC_INT_IN    : Pipe number (USB_PIPE6 to USB_PIPE9)  1st Device CDC Data class Interrupt In Pipe
 * USB_CFG_HCDC_BULK_IN2  : Pipe number (USB_PIPE1 to USB_PIPE5)  2nd Device CDC Data class Bulk In Pipe
 * USB_CFG_HCDC_BULK_OUT2 : Pipe number (USB_PIPE1 to USB_PIPE5)  2nd Device CDC Data class Bulk Out Pipe
 * USB_CFG_HCDC_INT_IN2   : Pipe number (USB_PIPE6 to USB_PIPE9)  2nd Device CDC Data class Interrupt In Pipe
 */
#define USB_CFG_HCDC_BULK_IN        (USB_PIPE1)
#define USB_CFG_HCDC_BULK_OUT       (USB_PIPE2)
#define USB_CFG_HCDC_INT_IN         (USB_PIPE6)
#define USB_CFG_HCDC_BULK_IN2       (USB_PIPE3)
#define USB_CFG_HCDC_BULK_OUT2      (USB_PIPE4)
#define USB_CFG_HCDC_INT_IN2        (USB_PIPE7)

#endif  /* R_USB_HCDC_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
