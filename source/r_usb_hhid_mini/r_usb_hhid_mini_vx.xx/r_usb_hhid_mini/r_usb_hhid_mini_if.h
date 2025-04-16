/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_hhid_mini_if.h
 * Description  : Interface file for USB Host HID class API for RX
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 01.09.2014 1.00    First Release
 *         : 01.06.2015 1.01    Added RX231.
 *         : 30.11.2018 1.10    Supporting Smart Configurator
 *         : 30.06.2020 1.20    Added support for RTOS.
 *         : 20.03.2025 1.31    Changed the disclaimer.
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_hhid_mini_config.h"

#ifndef USB_HHID_MINI_IF_H
#define USB_HHID_MINI_IF_H

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
#define USB_HID_OTHER                       (0x00)
#define USB_HID_KEYBOARD                    (0x01)   /* Keyboard */
#define USB_HID_MOUSE                       (0x02)   /* Mouse */

#define USB_IN                              (0u)
#define USB_OUT                             (1u)

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
usb_err_t       R_USB_HhidGetType (uint8_t *p_type);
usb_err_t       R_USB_HhidGetMxps(uint16_t *p_mxps, uint8_t dir);

#endif /* USB_HHID_MINI_IF_H */

/***********************************************************************************************************************
End  Of File
***********************************************************************************************************************/
