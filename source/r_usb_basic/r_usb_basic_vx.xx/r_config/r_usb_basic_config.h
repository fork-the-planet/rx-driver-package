/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_basic_config_reference.h
 * Version      : 1.44
 * Description  : USB User definition
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 31.08.2015 1.00    First Release
 *         : 01.03.2025 1.44    Change Disclaimer.
 ***********************************************************************************************************************/

#ifndef R_USB_BASIC_CONFIG_H
#define R_USB_BASIC_CONFIG_H

/******************************************************************************/
/** Common Settings in USB Host/USB Peripheral Mode                           */
/******************************************************************************/

/** [USB operating mode setting]
 *  USB_CFG_HOST        : USB Host mode.
 *  USB_CFG_PERI        : USB Peri mode.
 */
#define USB_CFG_MODE                (USB_CFG_HOST)

/** [Argument check setting]
 *  USB_CFG_ENABLE      :Checks arguments.
 *  USB_CFG_DISABLE     :Does not check arguments.
 */
#define USB_CFG_PARAM_CHECKING      (USB_CFG_ENABLE)

/** [Device class setting]
 *  #define USB_CFG_HCDC_USE : Host Communication Device Class
 *  #define USB_CFG_HHID_USE : Host Human Interface Device Class
 *  #define USB_CFG_HMSC_USE : Host Mass Storage Class
 *  #define USB_CFG_HVND_USE : Host VENDER Class
 *  #define USB_CFG_PCDC_USE : Peripheral Communication Device Class
 *  #define USB_CFG_PHID_USE : Peripheral Human Interface Device Class
 *  #define USB_CFG_PMSC_USE : Peripheral Mass Storage Class
 *  #define USB_CFG_PVND_USE : Peripheral VENDER Class
 *  #define USB_CFG_PCDC_2COM_USE : Peripheral Composite device(CDC VCOM 2Port)
 *  #define USB_CFG_PCDC_PHID_USE : Peripheral Composite device(CDC + HID)
 *  #define USB_CFG_PCDC_PMSC_USE : Peripheral Composite device(CDC + MSC)
 *  #define USB_CFG_PHID_PMSC_USE : Peripheral Composite device(HID + MSC)
 * */
#define USB_CFG_HCDC_USE /* USB_CFG_DEVICE_CLASS */


/**  [DTC use setting]
 * USB_CFG_ENABLE       : Uses DTC
 * USB_CFG_DISABLE      : Does not use DTC
 */
#define USB_CFG_DTC              (USB_CFG_DISABLE)

/**  [DMA use setting]
 * USB_CFG_ENABLE       : Uses DMA
 * USB_CFG_DISABLE      : Does not use DMA
 */
#define USB_CFG_DMA              (USB_CFG_DISABLE)

/** [DMA Channel setting(USB0 module Send transfer)]
 * USB_CFG_CH0          : Uses DMAC0
 * USB_CFG_CH1          : Uses DMAC1
 * USB_CFG_CH2          : Uses DMAC2
 * USB_CFG_CH3          : Uses DMAC3
 * USB_CFG_CH7          : Uses DMAC7
 */
#define USB_CFG_USB0_DMA_TX     (USB_CFG_CH0)

/** [DMA Channel setting(USB0 module Receive transfer)]
 * USB_CFG_CH0          : Uses DMAC0
 * USB_CFG_CH1          : Uses DMAC1
 * USB_CFG_CH2          : Uses DMAC2
 * USB_CFG_CH3          : Uses DMAC3
 * USB_CFG_CH7          : Uses DMAC7
 */
#define USB_CFG_USB0_DMA_RX     (USB_CFG_CH1)

/** [DMA Channel setting(USB1 module Send transfer)]
 * USB_CFG_CH0          : Uses DMAC0
 * USB_CFG_CH1          : Uses DMAC1
 * USB_CFG_CH2          : Uses DMAC2
 * USB_CFG_CH3          : Uses DMAC3
 * USB_CFG_CH7          : Uses DMAC7
 */
#define USB_CFG_USB1_DMA_TX     (USB_CFG_CH2)

/** [DMA Channel setting(USB1 module Receive transfer)]
 * USB_CFG_CH0          : Uses DMAC0
 * USB_CFG_CH1          : Uses DMAC1
 * USB_CFG_CH2          : Uses DMAC2
 * USB_CFG_CH3          : Uses DMAC3
 * USB_CFG_CH7          : Uses DMAC7
 */
#define USB_CFG_USB1_DMA_RX     (USB_CFG_CH3)

/** [Setting Battery Charging (BC) function]
 * USB_CFG_ENABLE       : Uses BC function.
 * USB_CFG_DISABLE      : Does not use BC function.
 */
#define USB_CFG_BC                  (USB_CFG_DISABLE)

/** [PLL clock frequency setting]
 * USB_CFG_24MHZ        : Set to 24MHz
 * USB_CFG_20MHZ        : Set to 20MHz
 * USB_CFG_OTHER        : Set to other than 24/20MHz
 */
#define USB_CFG_CLKSEL              (USB_CFG_24MHZ)

/** [CPU Bus Access Wait Select(CPU Bus Wait Register (BUSWAIT)BWAIT[3:0])]
 *  USB_CFG_BUSWAIT_0   : 2 access cycles  waits
 *  USB_CFG_BUSWAIT_1   : 3 access cycles  waits
 *  USB_CFG_BUSWAIT_2   : 4 access cycles  waits
 *  USB_CFG_BUSWAIT_3   : 5 access cycles  waits
 *  USB_CFG_BUSWAIT_4   : 6 access cycles  waits
 *  USB_CFG_BUSWAIT_5   : 7 access cycles  waits
 *  USB_CFG_BUSWAIT_6   : 8 access cycles  waits
 *  USB_CFG_BUSWAIT_7   : 9 access cycles  waits
 *  USB_CFG_BUSWAIT_8   : 10 access cycles waits
 *  USB_CFG_BUSWAIT_9   : 11 access cycles waits
 *  USB_CFG_BUSWAIT_10  : 12 access cycles waits
 *  USB_CFG_BUSWAIT_11  : 13 access cycles waits
 *  USB_CFG_BUSWAIT_12  : 14 access cycles waits
 *  USB_CFG_BUSWAIT_13  : 15 access cycles waits
 *  USB_CFG_BUSWAIT_14  : 16 access cycles waits
 *  USB_CFG_BUSWAIT_15  : 17 access cycles waits
 */
#define USB_CFG_BUSWAIT             (USB_CFG_BUSWAIT_7)

/* 
 * SET USB INTERRUPT PRIORITY; 
 *  1                   : lowest
 *  15                  : highest
 */
#define USB_CFG_INTERRUPT_PRIORITY  (3)

/******************************************************************************/
/** Settings in USB Host Mode                                                 */
/******************************************************************************/

/** [Setting power source IC for USB Host]
 * USB_CFG_HIGH         : High assert
 * USB_CFG_LOW          : Low assert
 */
#define USB_CFG_VBUS                (USB_CFG_HIGH)

/** [Setting USB port operation when using Battery Charging (BC) function]
 * USB_CFG_ENABLE       : DCP enabled.
 * USB_CFG_DISABLE      : DCP disabled.
 */
#define USB_CFG_DCP                 (USB_CFG_DISABLE)

/** [Setting whteher to use USB Hub]
 * USB_CFG_ENABLE       : Using USB Hub
 * USB_CFG_DISABLE      : Not using USB Hub
 */
#define USB_CFG_HUB                 (USB_CFG_ENABLE)

/** [Setting whther to use Type-C]
 * USB_CFG_ENABLE       : Using Type-C
 * USB_CFG_DISABLE      : Not using Type-C
 */
#define USB_CFG_TYPEC               (USB_CFG_DISABLE)

/** [Setting Compliance Test mode]
 * USB_CFG_ENABLE       : Compliance Test supported.
 * USB_CFG_DISABLE      : Compliance Test not supported.
 */
#define USB_CFG_COMPLIANCE          (USB_CFG_DISABLE)

/** [Setting a Targeted Peripheral List (TPL)]
 * USB_CFG_TPLCNT       : Number of the USB devices to be connected.
 * USB_CFG_TPL          : Set the VID and PID pairs for the USB device to be connected.
 * */
#define USB_CFG_TPLCNT              (1)
#define USB_CFG_TPL                 USB_NOVENDOR, USB_NOPRODUCT

/** [Setting a Targeted Peripheral List (TPL) for USB Hub]
 * USB_CFG_HUB_TPLCNT   : Set the number of the USB Hubs to be connected.
 * USB_CFG_HUB_TPL      : Setting VID and PID of the USB Hub.
 */
#define USB_CFG_HUB_TPLCNT          (1)
#define USB_CFG_HUB_TPL             USB_NOVENDOR, USB_NOPRODUCT

/** [Setting Hi-speed (HS) Electrical Test]
 * USB_CFG_ENABLE       : HS Electrical Test supported
 * USB_CFG_DISABLE      : HS Electrical Test not supported
 */
#define USB_CFG_ELECTRICAL          (USB_CFG_DISABLE)

/******************************************************************************/
/** Settings in USB Peripheral Mode                                           */
/******************************************************************************/
/** [USB module selection setting]
 *  USB_CFG_IP0         : Uses USB0 module
 *  USB_CFG_IP1         : Uses USB1 module
 */
#define USB_CFG_USE_USBIP           (USB_CFG_IP0)

/** [Setting whether to notify the application when receiving the request(SET_INTERFACE/SET_FEATURE/CLEAR_FEATURE)]
 * USB_CFG_ENABLE       : Notification
 * USB_CFG_DISABLE      : Not Notification
 */
#define USB_CFG_REQUEST             (USB_CFG_ENABLE)

/******************************************************************************/
/** OTHER DEFINITIONS SETTING                                                 */
/******************************************************************************/
/** [DBLB bit setting]
 * USB_CFG_DBLBON       : DBLB bit set.
 * USB_CFG_DBLBOFF      : DBLB bit cleared.
 */
#define USB_CFG_DBLB                (USB_CFG_DBLBON)

/** [CNTMD bit setting]
 * USB_CFG_CNTMDON      : CNTMD bit set.
 * USB_CFG_CNTMDOFF     : CNTMD bit cleared.
 */
#define USB_CFG_CNTMD               (USB_CFG_CNTMDOFF)

#endif  /* R_USB_BASIC_CONFIG_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/

