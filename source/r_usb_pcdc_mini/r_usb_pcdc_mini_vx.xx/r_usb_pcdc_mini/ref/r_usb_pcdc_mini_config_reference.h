/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/******************************************************************************
 * File Name    : r_usb_pcdc_mini_config.h
 * Description  : USB Peripheral CDC configuration
 ******************************************************************************/
/******************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 01.09.2014 1.00    First Release
 *         : 30.11.2018 1.10    Supporting Smart Configurator
 *         : 30.06.2020 1.20    Added support for RTOS.
 *         : 20.03.2025 1.31    Changed the disclaimer.
 ******************************************************************************/

#ifndef R_USB_PCDC_MINI_CONFIG_H
#define R_USB_PCDC_MINI_CONFIG_H

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/** [Setting pipe to be used]
 * USB_CFG_PCDC_BULK_IN   : Pipe number (USB_PIPE1 to USB_PIPE5)  1st VCOM CDC Data class Bulk In Pipe
 * USB_CFG_PCDC_BULK_OUT  : Pipe number (USB_PIPE1 to USB_PIPE5)  1st VCOM CDC Data class Bulk Out Pipe
 * USB_CFG_PCDC_INT_IN    : Pipe number (USB_PIPE6 to USB_PIPE9)  1st VCOM CDC Data class Interrupt In Pipe
 * USB_CFG_PCDC_BULK_IN2  : Pipe number (USB_PIPE1 to USB_PIPE5)  2nd VCOM CDC Data class Bulk In Pipe
 * USB_CFG_PCDC_BULK_OUT2 : Pipe number (USB_PIPE1 to USB_PIPE5)  2nd VCOM CDC Data class Bulk Out Pipe
 * USB_CFG_PCDC_INT_IN2   : Pipe number (USB_PIPE6 to USB_PIPE9)  2nd VCOM CDC Data class Interrupt In Pipe
 */
#define USB_CFG_PCDC_BULK_IN        (USB_PIPE1)
#define USB_CFG_PCDC_BULK_OUT       (USB_PIPE2)
#define USB_CFG_PCDC_INT_IN         (USB_PIPE6)
#define USB_CFG_PCDC_BULK_IN2       (USB_PIPE3)
#define USB_CFG_PCDC_BULK_OUT2      (USB_PIPE4)
#define USB_CFG_PCDC_INT_IN2        (USB_PIPE7)


#endif  /* R_USB_PCDC_MINI_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
