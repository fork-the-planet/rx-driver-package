/*
 * Copyright (C) 2024 - 2025 Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef RM_COMMS_USB_PCDC_API_COMPLEMENT_H
#define RM_COMMS_USB_PCDC_API_COMPLEMENT_H
/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define USB_PCDC_BASIC                        (0)
#define USB_PCDC_BASIC_MINI                   (1)

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_smc_entry.h"
#include "platform.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "rm_comms_usb_pcdc_rx_config.h"
#else
 #include "rm_comms_usb_pcdc_cfg.h"
#endif

#if COMMS_USB_PCDC_DEVICE_USED == USB_PCDC_BASIC
 #include "r_usb_basic_if.h"
#elif COMMS_USB_PCDC_DEVICE_USED == USB_PCDC_BASIC_MINI
 #include "r_usb_basic_mini_if.h"
#else
#endif

#if BSP_CFG_RTOS == 0
 #include "r_cmt_rx_if.h"
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if BSP_CFG_RTOS == 0
/* CMT Driver Instance */
typedef struct st_cmt_instance
{
    uint32_t const          freqency_hz;            ///< Frequency [Hz]
    uint32_t const          channel;                ///< Channel
    cmt_priority_t const    priority;               ///< Desired priority level of timer interrupt
    void (* callback)       (void * pdata);         ///< Callback function
} cmt_instance_t;
#endif

/* This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_usb_instance
{
    usb_ctrl_t * p_ctrl;          ///< Pointer to the control structure for this instance
    usb_cfg_t  * p_cfg;           ///< Pointer to the configuration structure for this instance
} usb_instance_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

#endif /* RM_COMMS_USB_PCDC_API_COMPLEMENT_H */
