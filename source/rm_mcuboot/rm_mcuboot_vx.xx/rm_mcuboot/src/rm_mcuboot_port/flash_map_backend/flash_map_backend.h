/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2015 Runtime Inc
 * Copyright (c) 2020 Embedded Planet
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**********************************************************************************************************************
 * File Name    : flash_map_backend.h
 * Version      : 1.0
 * Description  : This is a private header file used internally by MCUboot and the porting section.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *********************************************************************************************************************/

/**
 *
 * Provides abstraction of flash regions for type of use.
 * I.e. dude where's my image?
 *
 * System will contain a map which contains flash areas. Every
 * region will contain flash identifier, offset within flash and length.
 *
 * 1. This system map could be in a file within filesystem (Initializer
 * must know/figure out where the filesystem is at).
 * 2. Map could be at fixed location for project (compiled to code)
 * 3. Map could be at specific place in flash (put in place at mfg time).
 *
 * Note that the map you use must be valid for BSP it's for,
 * match the linker scripts when platform executes from flash,
 * and match the target offset specified in download script.
 */

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <inttypes.h>

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
#ifndef FLASH_MAP_BACKEND_H
#define FLASH_MAP_BACKEND_H

/**
 * @brief Structure describing an area on a flash device.
 *
 * Multiple flash devices may be available in the system, each of
 * which may have its own areas. For this reason, flash areas track
 * which flash device they are part of.
 */
struct flash_area
{
    /** This flash area's ID; unique in the system. */
    uint8_t  fa_id;

    /** ID of the flash device this area is a part of. */
    uint8_t  fa_device_id;

    uint16_t pad16;

    /** This area's offset, relative to the beginning of its flash
     *  device's storage.
     */
    uint32_t fa_off;

    /**
     * This area's size, in bytes.
     */
    uint32_t fa_size;
};

/**********************************************************************************************************************
* Function Name: flash_area_get_id
* Description  : Gets the flash area ID from the flash area information.
* Arguments    : const struct flash_area * p_fa -
*                    Pointer to flash area information.
* Return Value : p_fa->fa_id -
*                    Flash area's ID
**********************************************************************************************************************/
static inline uint8_t flash_area_get_id (const struct flash_area * p_fa)
{
    return p_fa->fa_id;
}
/**********************************************************************************************************************
* End of function flash_area_get_id (const struct flash_area * p_fa)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_get_device_id
* Description  : Gets the flash device ID from the flash area information.
* Arguments    : const struct flash_area * p_fa -
*                    Pointer to flash area information.
* Return Value : p_fa->fa_device_id -
*                    Flash device id
**********************************************************************************************************************/
static inline uint8_t flash_area_get_device_id (const struct flash_area * p_fa)
{
    return p_fa->fa_device_id;
}
/**********************************************************************************************************************
* End of function flash_area_get_device_id (const struct flash_area * p_fa)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_get_off
* Description  : Get the offset from the flash area information.
* Arguments    : const struct flash_area * p_fa -
*                    Pointer to flash area information.
* Return Value : p_fa->fa_off -
*                    Flash area offset
**********************************************************************************************************************/
static inline uint32_t flash_area_get_off (const struct flash_area * p_fa)
{
    return p_fa->fa_off;
}
/**********************************************************************************************************************
* End of function flash_area_get_off (const struct flash_area * p_fa)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_get_size
* Description  : Gets the size from the flash area information.
* Arguments    : const struct flash_area * p_fa -
*                    Pointer to flash area information.
* Return Value : p_fa->fa_size -
*                    Flash area size
**********************************************************************************************************************/
static inline uint32_t flash_area_get_size (const struct flash_area * p_fa)
{
    return p_fa->fa_size;
}
/**********************************************************************************************************************
* End of function flash_area_get_size (const struct flash_area * p_fa)
**********************************************************************************************************************/

/**
 * @brief Structure describing a sector within a flash area.
 *
 * Each sector has an offset relative to the start of its flash area
 * (NOT relative to the start of its flash device), and a size. A
 * flash area may contain sectors with different sizes.
 */
struct flash_sector
{
    /**
     * Offset of this sector, from the start of its flash area (not device).
     */
    uint32_t fs_off;

    /**
     * Size of this sector, in bytes.
     */
    uint32_t fs_size;
};

/**********************************************************************************************************************
* Function Name: flash_sector_get_off
* Description  : Get the offset of a sector within the flash area.
* Arguments    : const struct flash_sector * p_fs -
*                    Pointer to flash sector information.
* Return Value : p_fs->fs_off -
*                    Offset of sector within flash area
**********************************************************************************************************************/
static inline uint32_t flash_sector_get_off (const struct flash_sector * p_fs)
{
    return p_fs->fs_off;
}
/**********************************************************************************************************************
* End of function flash_sector_get_off (const struct flash_area * p_fs)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_sector_get_size
* Description  : Get the size of a sector within the flash area.
* Arguments    : const struct flash_sector * p_fs -
*                    Pointer to flash sector information.
* Return Value : p_fs->fs_size -
*                    Size of sectors within flash area
**********************************************************************************************************************/
static inline uint32_t flash_sector_get_size (const struct flash_sector * p_fs)
{
    return p_fs->fs_size;
}
/**********************************************************************************************************************
* End of function flash_sector_get_size (const struct flash_area * p_fs)
**********************************************************************************************************************/

int32_t flash_area_driver_init(void);

int32_t  flash_area_open (uint8_t id, const struct flash_area ** pp_area);

void flash_area_close (const struct flash_area * p_area);

int32_t flash_area_read (const struct flash_area * p_area, uint32_t off, void * p_dst, uint32_t len);

int32_t flash_area_write (const struct flash_area * p_area, uint32_t off, const void * p_src, uint32_t len);

int32_t flash_area_erase (const struct flash_area * p_area, uint32_t off, uint32_t len);

uint32_t flash_area_align (const struct flash_area * p_area);

uint8_t flash_area_erased_val (const struct flash_area * p_area);

int32_t flash_area_get_sectors (int32_t fa_id, uint32_t * p_count, struct flash_sector * p_sectors);

int32_t flash_area_id_from_image_slot (int32_t slot);

int32_t flash_area_id_from_multi_image_slot (int32_t image_index, int32_t slot);

int32_t flash_area_id_to_image_slot (uint32_t area_id);

int32_t flash_area_id_to_multi_image_slot (int32_t image_index, int32_t area_id);

int32_t rm_mcuboot_cleanup (void);

int32_t flash_on_chip_cleanup (void);

typedef struct rm_mcuboot_port_flush_buffer
{
    uint32_t   current_block;
    uint32_t * p_flush_buffer;
} rm_mcuboot_port_flush_buffer_t;

#endif /* FLASH_MAP_BACKEND_H */
