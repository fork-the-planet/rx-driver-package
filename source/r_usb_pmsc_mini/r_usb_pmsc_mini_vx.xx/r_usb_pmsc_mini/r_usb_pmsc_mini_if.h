/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/******************************************************************************
 * File Name    : r_usb_pmsc_mini_if.h
 * Description  : Interface file for USB vendor class API for RX
 ******************************************************************************/
/******************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 01.09.2014 1.00     First Release
 *         : 01.06.2015 1.01     Added RX231.
 *         : 30.11.2018 1.10     Supporting Smart Configurator
 *         : 20.03.2025 1.31     Changed the disclaimer.
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

/* Used to get which MCU is currently being used. */
/* User specific options for Flash API */
#include "r_usb_basic_mini_config.h"
#include "r_usb_pmsc_mini_config.h"

#ifndef USB_PMSC_MINI_IF_H
#define USB_PMSC_MINI_IF_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/

/* MSC Class Request code define. */
#define USB_MASS_STORAGE_RESET          (0xFF00)    /* Mass storage reset request */
#define USB_GET_MAX_LUN                 (0xFE00)    /* Get max logical unit number */

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables
 ******************************************************************************/

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

#endif  /* USB_PMSC_MINI_IF_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/

