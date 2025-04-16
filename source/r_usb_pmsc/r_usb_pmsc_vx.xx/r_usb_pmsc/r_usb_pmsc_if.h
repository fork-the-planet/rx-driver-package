/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_pmsc_if.h
 * Version      : 1.44
 * Description  : Interface file for USB vendor class API for RX
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Delete no use functions prototype.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/
#ifndef USB_PMSC_IF_H
#define USB_PMSC_IF_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
/* Used to get which MCU is currently being used. */
/* User specific options for Flash API */
#include "r_usb_basic_config.h"
#include "r_usb_pmsc_config.h"

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/

/* MSC Class Request code define. */
#define USB_MASS_STORAGE_RESET          (0xFF00)    /* Mass storage reset request */
#define USB_GET_MAX_LUN                 (0xFE00)    /* Get max logical unit number */

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

#endif  /* USB_PMSC_IF_H */

/***********************************************************************************************************************
End  Of File
***********************************************************************************************************************/