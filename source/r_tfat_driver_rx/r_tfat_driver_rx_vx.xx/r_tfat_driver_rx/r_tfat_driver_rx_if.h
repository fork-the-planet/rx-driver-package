/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_tfat_driver_rx_if.h
* Description  : TFAT driver Interface.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 01.12.2014 1.00    First Release
*              : 05.01.2015 1.01    Added support USB Mini Firmware.
*              : 22.06.2015 1.02    Added support MCU RX231.
*              : 01.04.2016 1.03    Added support RX family.
*              : 29.06.2018 1.04    Modified SDHI to SDMEM.
*              : 08.08.2019 2.00    Added support for FreeRTOS and Renesas uITRON (RI600V4).
*                                   Added support for GNUC and ICCRX.
*              : 10.06.2020 2.10    Added support MMC Firmware and FLASH Firmware.
*              : 15.12.2023 2.40    Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*              : 08.05.2024 2.50    Added support SPI mode SD card.
*              : 30.09.2024 2.60    Changed the comment of API functions to the Doxygen style.
*              : 15.03.2025 2.61    Updated disclaimer.
***********************************************************************************************************************/
#ifndef _R_TFAT_DRIVER_RX_IF_H_
#define _R_TFAT_DRIVER_RX_IF_H_

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include "platform.h"
#include "ff.h"                  /* TFAT define */
#include "diskio.h"              /* TFAT define */

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* used memory define */
#define TFAT_CTRL_NONE          (0)
#define TFAT_CTRL_USB           (1)
#define TFAT_CTRL_SDMEM         (2)
#define TFAT_CTRL_MMC           (3)
#define TFAT_CTRL_USB_MINI      (4)
#define TFAT_CTRL_SERIAL_FLASH  (5)
#define TFAT_CTRL_SPI_SDMEM     (6)

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* Drive number define ("uint8_t drive") */
typedef enum
{
    TFAT_DRIVE_NUM_0 = 0x00,
    TFAT_DRIVE_NUM_1,
    TFAT_DRIVE_NUM_2,
    TFAT_DRIVE_NUM_3,
    TFAT_DRIVE_NUM_4,
    TFAT_DRIVE_NUM_5,
    TFAT_DRIVE_NUM_6,
    TFAT_DRIVE_NUM_7,
    TFAT_DRIVE_NUM_8,
    TFAT_DRIVE_NUM_9,
    TFAT_DRIVE_NUM_MAX,
}TFAT_DRV_NUM;

/*******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/
extern DRESULT drv_change_alloc(TFAT_DRV_NUM tfat_drv,
                                uint8_t dev_type,
                                uint8_t dev_drv_num);
void disk_1ms_interval (void);
#endif    /* _R_TFAT_DRIVER_RX_IF_H_ */

/*******************************************************************************
End  of file
*******************************************************************************/
