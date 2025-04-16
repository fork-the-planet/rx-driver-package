/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_phid_if.h
 * Version      : 1.44
 * Description  : Interface file for USB Peripheral HID class API for RX
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 30.09.2015 1.11 First Release
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Deleted typedef struct"usb_request_t" and typedef"USB_CB_TRN_t".
 *                           Deleted export global functions.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

#ifndef USB_PHID_IF_H
#define USB_PHID_IF_H

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
/* User specific options for Flash API */
#include "r_usb_phid_config.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define USB_PHID_ECHO_MODE          (0)           /*  Peripheral HID Application echo mode */
#define USB_PHID_KEYBOARD_MODE      (1)           /* Peripheral HID Application keyboard mode */
#define USB_PHID_MOUSE_MODE         (2)           /* Peripheral HID Application mouse mode */

/*----- HID Mouse Class Request Defines --------*/
/* HID Class Request codes */
#define USB_GET_REPORT                  (0x0100u)
#define USB_GET_IDLE                    (0x0200u)
#define USB_GET_PROTOCOL                (0x0300u)
#define USB_SET_IDLE                    (0x0A00u)
#define USB_SET_REPORT                  (0x0900u)
#define USB_SET_PROTOCOL                (0x0B00u)

/* PHID reception message type definition */
#define USB_GET_REPORT_DESCRIPTOR       (0x2200u)
#define USB_GET_HID_DESCRIPTOR          (0x2100u)

/* ----- DESCRIPTOR Types ----- */
#define USB_DT_TYPE_GETREPORT           ((uint8_t)0x01)   /* Report Type Input */
#define USB_DT_TYPE_SETREPORT           ((uint8_t)0x02)   /* Report Type Output */
#define USB_DT_TYPE_HIDDESCRIPTOR       ((uint8_t)0x21)   /* HID descriptor type */
#define USB_DT_TYPE_RPTDESCRIPTOR       ((uint8_t)0x22)   /* Report descriptor type */

/* ----- Subclass Codes ----- */
#define USB_IFSUB_NOBOOT                ((uint8_t)0x00)   /* No Subclass */
#define USB_IFSUB_BOOT                  ((uint8_t)0x01)   /* Boot Interface Subclass */

/* ----- Protocol Codes ----- */
#define USB_IFPRO_NONE                  ((uint8_t)0x00)   /* Demonstration */
#define USB_IFPRO_KBD                   ((uint8_t)0x01)   /* Keyboard */
#define USB_IFPRO_MSE                   ((uint8_t)0x02)   /* Mouse */

/* Peripheral HID Max Packet Size */
#define USB_PHID_MXPS_KBD               (8u)
#define USB_PHID_MXPS_MSE               (3u)
#define USB_PHID_MXPS_ECHO              (64u)

#endif /* USB_PHID_IF_H */

/***********************************************************************************************************************
End  Of File
***********************************************************************************************************************/