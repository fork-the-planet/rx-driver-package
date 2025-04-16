/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 01.12.2014 1.00    First Release
*              : 21.01.2015 1.01    Added support USB Mini Firmware
*              : 22.06.2015 1.02    Added support MCU RX231.
*              : 01.04.2016 1.03    Updated the xml file.
*              : 29.06.2018 1.04    Modified SDHI to SDMEM.
*              : 08.08.2019 2.00    Added support for FreeRTOS and Renesas uITRON (RI600V4).
*                                   Added support for GNUC and ICCRX.
*              : 10.06.2020 2.10    Added API function "flash_1ms_interval".
*                                   Added support FLASH SPI Firmware
*                                   Added support MMCIF Firmware
*              : 15.12.2023 2.40    Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*              : 08.05.2024 2.50    Added support SPI mode SD card.
*              : 15.03.2025 2.61    Updated disclaimer.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_tfat_drv_rx_if_dev.h
* Description  : TFAT driver Interface on RX devices.
***********************************************************************************************************************/
#ifndef _R_TFAT_DRIVER_RX_IF_DEV_H_
#define _R_TFAT_DRIVER_RX_IF_DEV_H_

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_tfat_driver_rx_config.h"
#include "diskio.h"
#include "ff.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/


/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/
#if (TFAT_USB_DRIVE_NUM > 0)
DSTATUS usb_disk_initialize(uint8_t pdrv);
DRESULT usb_disk_read(uint8_t pdrv, uint8_t* buff,
                        uint32_t sector, uint32_t count);
DRESULT usb_disk_write(uint8_t pdrv, const uint8_t* buff,
                        uint32_t sector, uint32_t count);
DRESULT usb_disk_ioctl(uint8_t pdrv, uint8_t cmd, void* buff);
DSTATUS usb_disk_status(uint8_t pdrv);
#endif /* (TFAT_USB_DRIVE_NUM > 0) */

#if (TFAT_USB_MINI_DRIVE_NUM > 0)
DSTATUS usb_mini_disk_initialize(uint8_t drive);
DRESULT usb_mini_disk_read(uint8_t drive, uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT usb_mini_disk_write(uint8_t drive, const uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT usb_mini_disk_ioctl(uint8_t drive, uint8_t command, void* buffer);
DSTATUS usb_mini_disk_status(uint8_t drive);
#endif /* (TFAT_USB_MINI_DRIVE_NUM > 0) */

#if (TFAT_SDMEM_DRIVE_NUM > 0)
DSTATUS sdmem_disk_initialize(uint8_t drive);
DRESULT sdmem_disk_read(uint8_t drive, uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT sdmem_disk_write(uint8_t drive, const uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT sdmem_disk_ioctl(uint8_t drive, uint8_t command, void* buffer);
DSTATUS sdmem_disk_status(uint8_t drive);
#endif /* (TFAT_SDMEM_DRIVE_NUM > 0) */

#if (TFAT_SPI_SDMEM_DRIVE_NUM > 0)
DSTATUS spi_sdmem_disk_initialize(uint8_t drive);
DRESULT spi_sdmem_disk_read(uint8_t drive, uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT spi_sdmem_disk_write(uint8_t drive, const uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT spi_sdmem_disk_ioctl(uint8_t drive, uint8_t command, void* buffer);
DSTATUS spi_sdmem_disk_status(uint8_t drive);
#endif /* (TFAT_SPI_SDMEM_DRIVE_NUM > 0) */

#if (TFAT_MMC_DRIVE_NUM > 0)
DSTATUS mmcif_disk_initialize(uint8_t drive);
DRESULT mmcif_disk_read(uint8_t drive, uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT mmcif_disk_write(uint8_t drive, const uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT mmcif_disk_ioctl(uint8_t drive, uint8_t command, void* buffer);
DSTATUS mmcif_disk_status(uint8_t drive);
#endif /* (TFAT_MMC_DRIVE_NUM > 0) */

#if (TFAT_SERIAL_FLASH_DRIVE_NUM > 0)
DSTATUS flash_spi_disk_initialize(uint8_t drive);
DRESULT flash_spi_disk_read(uint8_t drive, uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT flash_spi_disk_write(uint8_t drive, const uint8_t* buffer,
                        uint32_t sector_number, uint32_t sector_count);
DRESULT flash_spi_disk_ioctl(uint8_t drive, uint8_t command, void* buffer);
DSTATUS flash_spi_disk_status(uint8_t drive);
void flash_spi_1ms_interval(void);
#endif /* (TFAT_SERIAL_FLASH_DRIVE_NUM > 0) */

#endif    /* _R_TFAT_DRIVER_RX_IF_DEV_H_ */

/* End of File */
