/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name     : r_usb_hcdc.h
 * Version       : 1.44
 * Description   : USB Host CDC Driver API declaration
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 "usb_hcdc_ClassRequest","usb_hcdc_serial_state_trans_complete" is deleted
 *                           "usb_hcdc_set_pipe_registration","usb_hcdc_class_check" is added.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 16.11.2018 1.24 Supporting BSP_CFG_RTOS_USED
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 30.09.2023 1.42 USBX HCDC is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/
#ifndef R_USB_HCDC_H
#define R_USB_HCDC_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/
/* CDC Transfer data size */
#define     USB_HCDC_EP_OFFSET_DATA         (0)       /* Ep Table Bulk Pipe offset */
#define     USB_HCDC_EP_OFFSET_CTL          (2)       /* Ep Table Int Pipe offset */

#define     USB_NOPIPE                      ((uint8_t)0xFF)

/* Host Sample Task */
#if (BSP_CFG_RTOS_USED == 0)                          /* Non-OS */
#define USB_HCDC_TSK        (USB_TID_6)               /* Task ID */
#define USB_HCDC_MBX        (USB_HCDC_TSK)            /* Mailbox ID */
#define USB_HCDC_MPL        (USB_HCDC_TSK)            /* Memorypool ID */
#else
#define USB_HCDC_TSK        (USB_TID_8)               /* Task ID */
#define USB_HCDC_MBX        (USB_HCDC_TSK)            /* Mailbox ID */
#define USB_HCDC_MPL        (USB_HCDC_TSK)            /* Memorypool ID */
#endif /* (BSP_CFG_RTOS_USED == 0) */
#define USB_MAX_CONNECT_DEVICE_NUM          (2u)    /* 1-2 */

/******************************************************************************
 Exported global variables
 ******************************************************************************/
extern uint8_t *g_p_usb_hcdc_device_table[];
extern uint8_t *g_p_usb_hcdc_config_table[];
extern uint8_t *g_p_usb_hcdc_interface_table[];
extern uint16_t g_usb_hcdc_speed[];
extern uint16_t g_usb_hcdc_devaddr[];
extern int16_t g_usb_hcdc_smpl_class_seq[];
extern uint16_t *g_p_usb_hcdc_pipe_table[];


extern void usb_hcdc_task (rtos_task_arg_t stacd);
extern void usb_hcdc_configured (usb_utr_t *ptr, uint16_t devadr, uint16_t data2);
extern void usb_hcdc_detach (usb_utr_t *ptr, uint16_t devadr, uint16_t data2);


extern usb_er_t usb_hcdc_set_pipe_registration (usb_utr_t *ptr, uint16_t dev_addr);
extern void usb_hcdc_class_check (usb_utr_t *ptr, uint16_t **table);

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/

void usb_hcdc_enumeration (usb_clsinfo_t *mess);
uint16_t usb_hcdc_pipe_info (usb_utr_t *ptr, uint8_t *table, uint16_t speed, uint16_t length);

#endif  /* R_USB_HCDC_H */
/******************************************************************************
 End Of File
 ******************************************************************************/
