/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_hhid_if.h
 * Version      : 1.44
 * Description  : Interface file for USB Host HID class API for RX
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Deleted functions
 *                           "R_USB_HhidTask"
 *                           "usb_hhid_class_check"
 *                           "usb_hhid_driver_start"
 *                           "R_USB_HhidDriverRelease"
 *                           "usb_hhid_set_pipe_registration"
 *                           "R_USB_HhidPipeTransfer"
 *                           "R_USB_HhidTransferEnd"
 *                           "R_USB_HhidClassRequest"
 *                           "R_usb_hhid_device_information"
 *                           "R_USB_HhidChangeDeviceState"
 *                           "R_USB_HhidGetReportLength"
 *                           "usb_hhid_get_hid_protocol"
 *                           "usb_hhid_get_pipetbl"
 *                           "R_USB_HhidGetType" is added.
 *         : 31.03.2018 1.23 Supporting Smart Configurator 
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

#ifndef USB_HHID_IF_H
#define USB_HHID_IF_H

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_hhid_config.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define USB_HHID_ECHO_MODE                  (0)   /* Host HID Application echo mode */
#define USB_HHID_MOUSE_KEYBOARD_MODE        (1)   /* Host HID Application mouse keyboard mode */

/* ----- HID Mouse Class Request Defines -------- */
/* HID Class Request IDs */
/* It is used by the classification judging of a class request. */
#define USB_HID_GET_REPORT                  (0x0100u)
#define USB_HID_GET_IDLE                    (0x0200u)
#define USB_HID_GET_PROTOCOL                (0x0300u)
#define USB_HID_SET_IDLE                    (0x0A00u)
#define USB_HID_SET_REPORT                  (0x0900u)
#define USB_HID_SET_PROTOCOL                (0x0B00u)
#define USB_HID_GET_HID_DESCRIPTOR          (0x2100u)
#define USB_HID_GET_REPORT_DESCRIPTOR       (0x2200u)
#define USB_HID_GET_PHYSICAL_DESCRIPTOR     (0x2300u)

/* ----- Protocol Codes ----- */
#define USB_HID_OTHER                       ((uint8_t)0x00)
#define USB_HID_KEYBOARD                    ((uint8_t)0x01)   /* Keyboard */
#define USB_HID_MOUSE                       ((uint8_t)0x02)   /* Mouse */

#define USB_IN                              (0u)
#define USB_OUT                             (1u)

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
usb_err_t       R_USB_HhidGetType (usb_ctrl_t *p_ctrl, uint8_t *p_type);
usb_err_t       R_USB_HhidGetMxps(usb_ctrl_t *p_ctrl, uint16_t *p_mxps, uint8_t dir);

#endif /* USB_VENDOR_IF_H */

/***********************************************************************************************************************
End  Of File
***********************************************************************************************************************/