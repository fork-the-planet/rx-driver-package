/*
* Copyright (C) 2024 - 2025 Renesas Electronics Corporation. All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/* Guards against multiple inclusion */
#ifndef R_COMMS_USB_PCDC_CONFIG_H
#define R_COMMS_USB_PCDC_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/
/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/* Setting to 0 does not include parameter checking */
#define RM_COMMS_USB_PCDC_CFG_PARAM_CHECKING_ENABLE (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY THE DEVICE LOCK OPERATION IN THE RTOS */
/* Setting to 1 enable a device lock operation */
/* Setting to 0 disable a device lock operation */
#define COMMS_USB_PCDC_CFG_RTOS_TX_MUTEX_SUPPORT_ENABLE         (0)

/* SPECIFY THE DEVICE LOCK OPERATION IN THE RTOS */
/* Setting to 1 enable a device lock operation */
/* Setting to 0 disable a device lock operation */
#define COMMS_USB_PCDC_CFG_RTOS_RX_MUTEX_SUPPORT_ENABLE         (0)

/* Timeout for recursive mutex operation in using RTOS. */
#define COMMS_USB_PCDC_CFG_MUTEX_TIMEOUT                        (0xFFFFFFFF)

/* SPECIFY BLOCKING OPERATION IN THE RTOS */
/* Setting to 1 enable blocking operation */
/* Setting to 0 disable blocking operation */
#define COMMS_USB_PCDC_CFG_RTOS_TX_SEMAPHORE_SUPPORT_ENABLE     (0)

/* SPECIFY BLOCKING OPERATION IN THE RTOS */
/* Setting to 1 enable blocking operation */
/* Setting to 0 disable blocking operation */
#define COMMS_USB_PCDC_CFG_RTOS_RX_SEMAPHORE_SUPPORT_ENABLE     (0)

/* Timeout for semaphore operation in using RTOS. */
#define COMMS_USB_PCDC_CFG_SEMAPHORE_TIMEOUT                    (0xFFFFFFFF)

/* Callback function */
#define COMMS_USB_PCDC_CFG_CALLBACK                             (rm_comms_usb_pcdc_user_callback)

/* Specify the timer channel. */
#define COMMS_USB_PCDC_CFG_TIMER_CHANNEL                        (1)

/* Specify the connection detection mode */
#define COMMS_USB_PCDC_CFG_CONNECT_DETECTION                    (1)

/* Specify the timer frequency (Hz). */
#define COMMS_USB_PCDC_CFG_TIMER_FREQUENCY                      (100)

/* Specify the timer priority level. */
#define COMMS_USB_PCDC_CFG_TIMER_PRIORITY                       (CMT_PRIORITY_14)

/* Specify the module used for Rm_comms */
#define COMMS_USB_PCDC_DEVICE_USED                              (USB_PCDC_BASIC)

#endif  /* R_COMMS_USB_PCDC_CONFIG_H */
