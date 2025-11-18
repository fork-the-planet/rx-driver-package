/*
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
/**********************************************************************************************************************
 * File Name    : flash_map.c
 * Version      : 1.0
 * Description  : This module implements functions used to control the flash area.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *           30.06.2025 1.01    Added support for RX66N, RX72M and RX671
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdbool.h>
#include <string.h>
#include "flash_map_backend/flash_map_backend.h"
#include "bootutil/bootutil_log.h"
#include "bootutil_priv.h"
#include "sysflash/sysflash.h"
#include "mcu/all/fsp_common_api.h"

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
/* Definitions for different flash implementation. */
#define RM_MCUBOOT_PORT_INTERNAL_FLASH_BLOCK_ALIGN    (FLASH_CF_MIN_PGM_SIZE)

/* Write buffering is not required in overwrite only mode
 * (It is needed for overwrite only fast). */
#if defined(MCUBOOT_OVERWRITE_ONLY) && !defined(MCUBOOT_OVERWRITE_ONLY_FAST)
#define RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE         (0)
#else
#define RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE         (1)
#endif

/* Definition of an address that changes the size of the block to be erased. */
#if (FLASH_TYPE == FLASH_TYPE_1)
#define MCUBOOT_REGION0_SIZE (uint32_t)(FLASH_CF_BLOCK_END)
#define MEDIUM_BLOCK_SIZE    (FLASH_CF_BLOCK_SIZE)
#define SMALL_BLOCK_SIZE     (0)
#elif (FLASH_TYPE == FLASH_TYPE_4)
#if (RM_MCUBOOT_DUAL_BANK_ENABLED == 1)
#define MCUBOOT_REGION0_SIZE (uint32_t)(FLASH_CF_LO_BANK_SMALL_BLOCK_ADDR)
#elif  (RM_MCUBOOT_DUAL_BANK_ENABLED == 0)
#define MCUBOOT_REGION0_SIZE (uint32_t)(FLASH_CF_BLOCK_7)
#endif /* RM_MCUBOOT_DUAL_BANK_ENABLED */
#define MEDIUM_BLOCK_SIZE    (FLASH_CF_MEDIUM_BLOCK_SIZE)
#define SMALL_BLOCK_SIZE     (FLASH_CF_SMALL_BLOCK_SIZE)
#else
#error "MCU Group name must be defined."
#endif

#if RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE

/* This macro is used to index into gp_flush_buffer_lookup[]
 * lookup table to determine the appropriate flush buffer to use.
 * The logic works based on the MSB values of FLASH_DEVICE_INTERNAL_FLASH
 * and FLASH_DEVICE_EXTERNAL_FLASH being 0 and 1 respectively.
 */
#define RM_MCUBOOT_PORT_FLUSH_LOOKUP(x)    ((x) >> 7U)

uint32_t   g_rm_mcuboot_port_flash_write_ram[RM_MCUBOOT_PORT_INTERNAL_FLASH_BLOCK_ALIGN / sizeof(uint32_t)];
uint32_t * gp_write_buffer  = g_rm_mcuboot_port_flash_write_ram;

static rm_mcuboot_port_flush_buffer_t g_internal_flash_flush_buffer =
{
    .current_block = UINT32_MAX,
};

static rm_mcuboot_port_flush_buffer_t * gp_flush_buffer_lookup[2] =
{
    &g_internal_flash_flush_buffer,
};
#endif /* RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE */

/* Flash device name must be specified by target */

static const struct flash_area flash_map[] =
{
    {
        .fa_id        = FLASH_AREA_0_ID,
        .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
        .fa_off       = FLASH_AREA_0_OFFSET,
        .fa_size      = FLASH_AREA_0_SIZE,
    },
    {
        .fa_id = FLASH_AREA_2_ID,
        .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
        .fa_off  = FLASH_AREA_2_OFFSET,
        .fa_size = FLASH_AREA_2_SIZE,
    },

#if !defined(MCUBOOT_OVERWRITE_ONLY) && !defined(MCUBOOT_DIRECT_XIP)

    /* Scratch region is only used in swap mode. */
    {
        .fa_id        = FLASH_AREA_SCRATCH_ID,
        .fa_device_id = FLASH_DEVICE_INTERNAL_FLASH,
        .fa_off       = FLASH_AREA_SCRATCH_OFFSET,
        .fa_size      = FLASH_AREA_SCRATCH_SIZE,
    },
#endif
};

static flash_err_t flash_on_chip_flush (const struct flash_area * p_area);

static const struct flash_area * prv_lookup_flash_area(int32_t id);

static const uint32_t flash_map_entry_num = (sizeof(flash_map)) / sizeof(struct flash_area);

static bool g_internal_flash_driver_open = false;

/**********************************************************************************************************************
* Function Name: flash_area_open
* Description  : Opens the area for use. id is one of the `fa_id`s
* Arguments    : uint8_t id -
*                     Flash area ID
*                const struct flash_area ** pp_area -
*                     Pointer to pointer to flash area information.
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
int32_t flash_area_open (uint8_t id, const struct flash_area ** pp_area)
{
    flash_err_t err;

    /* Open the flash driver if it hasn't been opened yet. */
    if (!g_internal_flash_driver_open)
    {
        err = R_FLASH_Open();
        if (FLASH_SUCCESS != err)
        {
            return -1;
        }

#if RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE
        g_internal_flash_flush_buffer.p_flush_buffer = g_rm_mcuboot_port_flash_write_ram;
#endif

        g_internal_flash_driver_open = true;
    }

    BOOT_LOG_DBG("area %d", id);

    /* Copy the area's information to the provided pointer. */
    *pp_area = prv_lookup_flash_area(id);
    assert(NULL != *pp_area);

    /* Success. */
    return 0;
}
/**********************************************************************************************************************
* End of function flash_area_open (uint8_t id, const struct flash_area ** pp_area)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_driver_init
* Description  : Initialize all flash driver.
* Arguments    : none
* Return Value : 0
**********************************************************************************************************************/
int32_t flash_area_driver_init (void)
{
    /* Do nothing. */
    return 0;
}
/**********************************************************************************************************************
* End of function flash_area_driver_init (void)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_close
* Description  : Closes the area for use.
* Arguments    : const struct flash_area * p_area -
*                    Pointer to flash area information.
* Return Value : none
**********************************************************************************************************************/
void flash_area_close (const struct flash_area * p_area)
{
    (void)p_area;

    /* Nothing to do.
     * All flash modules are closed before entering the application image. */
}
/**********************************************************************************************************************
* End of function flash_area_close (const struct flash_area * p_area)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_read
* Description  : Reads `len` bytes of flash memory at `off` to the buffer at `dst`
* Arguments    : const struct flash_area * p_area -
*                    Pointer to flash area information
*                uint32_t off -
*                    Offset indicating the location of the data to read
*                void * p_dst -
*                    Pointer to buffer for reading
*                uint32_t len -
*                    Length of data to read
* Return Value : 0 - Success
**********************************************************************************************************************/
int32_t flash_area_read (const struct flash_area * p_area, uint32_t off, void * p_dst, uint32_t len)
{
#if RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE

    /* If any buffered writes have not yet been written,
     * write them before reading. */
    flash_err_t ret = flash_on_chip_flush(p_area);
    assert(FLASH_SUCCESS == ret);
    (void)ret;
#endif

    /* Internal flash is memory mapped. Just read with memcpy. */
    BOOT_LOG_DBG("read area=%d, off=%#x, len=%#x",
                (uint32_t) p_area->fa_id, (uint32_t) off, (uint32_t) len);

    memcpy(p_dst, (void *) (p_area->fa_off + off), len);

    return 0;
}
/**********************************************************************************************************************
* End of function flash_area_read (const struct flash_area * p_area, uint32_t off, void * p_dst, uint32_t len)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_on_chip_flush
* Description  : Flushes internal flash buffer.
* Arguments    : const struct flash_area * p_area -
*                    Pointer to flash area information.
* Return Value : FLASH_SUCCESS - Success
*                err - Failure
**********************************************************************************************************************/
static flash_err_t flash_on_chip_flush (const struct flash_area * p_area)
{
#if RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE
    flash_err_t err = FLASH_ERR_FAILURE;
    rm_mcuboot_port_flush_buffer_t * p_area_flush_buffer =
        gp_flush_buffer_lookup[RM_MCUBOOT_PORT_FLUSH_LOOKUP(p_area->fa_device_id)];

    /* If the write buffer has data, write it. */
    if (UINT32_MAX != p_area_flush_buffer->current_block)
    {
        BOOT_LOG_DBG("write flush ram buffer, addr=%#x, len=%#x",
                    (uint32_t) p_area_flush_buffer->current_block,
                    (uint32_t) RM_MCUBOOT_PORT_INTERNAL_FLASH_BLOCK_ALIGN);

        R_BSP_InterruptsDisable();
        if (FLASH_DEVICE_INTERNAL_FLASH == p_area->fa_device_id)
        {
            err = R_FLASH_Write((uint32_t) p_area_flush_buffer->p_flush_buffer,
                                    p_area_flush_buffer->current_block,
                                    RM_MCUBOOT_PORT_INTERNAL_FLASH_BLOCK_ALIGN);
        }
        else
        {
            /* do nothing */;
        }

        p_area_flush_buffer->current_block = UINT32_MAX;
        R_BSP_InterruptsEnable();

        return err;
    }
#else
    (void)p_area;
#endif /* RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE */
    return FLASH_SUCCESS;
}
/**********************************************************************************************************************
* End of function flash_on_chip_flush (const struct flash_area * p_area)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_write
* Description  : Writes `len` bytes of flash memory at `off` from the buffer at `p_src`
* Arguments    : const struct flash_area * p_area -
*                    Pointer to flash area information.
*                uint32_t off -
*                    Offset indicating where to write the data.
*                const void * p_src -
*                    Pointer to the buffer that holds the data to write
*                uint32_t len -
*                    Length of data to write
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
int32_t flash_area_write (const struct flash_area * p_area, uint32_t off, const void * p_src, uint32_t len)
{
    flash_err_t err = FLASH_SUCCESS;

#if RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE
    rm_mcuboot_port_flush_buffer_t * p_area_flush_buffer =
        gp_flush_buffer_lookup[RM_MCUBOOT_PORT_FLUSH_LOOKUP(p_area->fa_device_id)];
    uint32_t write_align_size = RM_MCUBOOT_PORT_INTERNAL_FLASH_BLOCK_ALIGN;

    if (FLASH_DEVICE_INTERNAL_FLASH == p_area->fa_device_id)
    {
        gp_write_buffer   = g_rm_mcuboot_port_flash_write_ram;
        write_align_size = RM_MCUBOOT_PORT_INTERNAL_FLASH_BLOCK_ALIGN;
    }
    else
    {
        /* Not supported */
        return -1;
    }

    /* If the write length is less than the minimum write size, buffer it.
     * MCUboot always writes from an address with the required alignment
     * when the length is a multiple of the required alignment,
     * so we are only checkinglen here. */
    if ((len % write_align_size) != 0)
    {
        /* Ensure all writes meet minimum alignment. */
        uint32_t aligned_address = (uint32_t) ((p_area->fa_off + off) & (uint32_t) ~(write_align_size - 1));
        uint32_t offset = (p_area->fa_off + off) % write_align_size;
        if (p_area_flush_buffer->current_block != aligned_address)
        {
            /* If the requested write block is different from the data in the buffer, flush the buffer before
             * buffering a new write block. */
            err = flash_on_chip_flush(p_area);
            memset(gp_write_buffer, UINT8_MAX, write_align_size);
            p_area_flush_buffer->current_block = aligned_address;
        }
        else
        {
            /* If the requested write block is the same as
             * the last requested write block, copy data into the
             * write buffer. */
        }

        memcpy(gp_write_buffer + (offset / sizeof(uint32_t)), p_src, len);
        BOOT_LOG_DBG("write buffer=%d, off=%#x, len=%#x",
                        (uint32_t) p_area->fa_id,
                        (uint32_t) off,
                        (uint32_t) len);
    }
    else
#endif /* RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE */
    {
        /* If the write is a multiple of minimum write size,
         * write it to flash. */
        BOOT_LOG_DBG("write area=%d, off=%#x, len=%#x",
                        (uint32_t) p_area->fa_id,
                        (uint32_t) off,
                        (uint32_t) len);

        uint32_t write_addr = p_area->fa_off + off;

        R_BSP_InterruptsDisable();

        if (FLASH_DEVICE_INTERNAL_FLASH == p_area->fa_device_id)
        {
            err = R_FLASH_Write((uint32_t) p_src, write_addr, len);
        }
        else /// If a flash driver other than the internal flash is used, added processing is performed.
        {
            /* do nothing */;
        }

        R_BSP_InterruptsEnable();
    }

    if (err != FLASH_SUCCESS)
    {
        return -1;
    }

    return 0;
}
/**********************************************************************************************************************
* End of function flash_area_write (const struct flash_area * p_area, uint32_t off, const void * p_src, uint32_t len)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_erase
* Description  : Erases `len` bytes of flash memory at `off`
* Arguments    : const struct flash_area * p_area -
*                    Pointer to flash area information.
*                uint32_t off -
*                    Offset indicating the location of the data to erase.
*                uint32_t len -
*                    Length of data to erase
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
int32_t flash_area_erase (const struct flash_area * p_area, uint32_t off, uint32_t len)
{
    /* No need to flush the write buffer here since it does not make sense
     * to write to a block just before erasing it. */

    BOOT_LOG_DBG("erase p_area=%d, off=%#x, len=%#x",
                (uint32_t) (p_area->fa_id), (uint32_t) off, (uint32_t) len);

    flash_err_t  err           = FLASH_SUCCESS;
    uint32_t  erase_address    = p_area->fa_off + off;
    uint32_t  sectors_to_erase = 0;
    uint32_t  sector_size = 0;

    /* Erase, accounting for block sizes. */
    if (FLASH_DEVICE_INTERNAL_FLASH == p_area->fa_device_id)
    {
        uint32_t deleted_len = 0;
        while (deleted_len < len)
        {
            if ((erase_address + deleted_len) < MCUBOOT_REGION0_SIZE)
            {
                sector_size = MEDIUM_BLOCK_SIZE;
            }
            else
            {
                sector_size = SMALL_BLOCK_SIZE;
            }

            sectors_to_erase++;
            deleted_len += sector_size;
        }

        R_BSP_InterruptsDisable();

        uint32_t tmp_erase_address = erase_address;

#if (FLASH_TYPE != FLASH_TYPE_1)
        /* Adjusting the address passed to the R_FLASH_Erase function in cases other than Flash Type 1. */
        tmp_erase_address = tmp_erase_address + (deleted_len - sector_size);
#endif

        err = R_FLASH_Erase((flash_block_address_t)tmp_erase_address, sectors_to_erase);
        R_BSP_InterruptsEnable();
        assert(FLASH_SUCCESS == err);
    }
    else
    {
        err = FLASH_ERR_UNSUPPORTED;
    }

    if (err != FLASH_SUCCESS)
    {
        return -1;
    }

    return 0;
}
/**********************************************************************************************************************
* End of function flash_area_erase (const struct flash_area * p_area, uint32_t off, uint32_t len)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_align
* Description  : Returns this `flash_area`s alignment
* Arguments    : const struct flash_area * p_area -
*                    Pointer to flash area information.
* Return Value : write_alignment -
*                    Flash area alignment
*                0 - Failure
**********************************************************************************************************************/
uint32_t flash_area_align (const struct flash_area * p_area)
{
    uint32_t write_alignment = 0U;
    if (FLASH_DEVICE_INTERNAL_FLASH == p_area->fa_device_id)
    {
        write_alignment = RM_MCUBOOT_PORT_INTERNAL_FLASH_BLOCK_ALIGN;
    }
    else
    {
        /* do nothing */;
    }

    return write_alignment;
}
/**********************************************************************************************************************
* End of function flash_area_align (const struct flash_area * p_area)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: prv_lookup_flash_area
* Description  : Returns the `flash_area` for a given `id`
* Arguments    : int32_t id -
*                    Flash area ID
* Return Value : p_area -
*                    Flash area information
*                NULL -
*                    Failure
**********************************************************************************************************************/
static const struct flash_area * prv_lookup_flash_area (int32_t id)
{
    for (uint32_t i = 0; i < flash_map_entry_num; i++)
    {
        const struct flash_area * p_area = &flash_map[i];
        if (id == p_area->fa_id)
        {
            return p_area;
        }
    }

    return NULL;
}
/**********************************************************************************************************************
* End of function prv_lookup_flash_area (uint32_t id)
**********************************************************************************************************************/

#if defined (MCUBOOT_USE_FLASH_AREA_GET_SECTORS)

/**********************************************************************************************************************
* Function Name: flash_area_get_sectors
* Description  : Given flash area ID, return info about sectors within the area.
* Arguments    : uint32_t fa_id -
*                    Flash area ID
*                uint32_t * p_count -
*                    Pointer to sector number counter
*                struct flash_sector * p_sectors -
*                    Pointer to sector information
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
int32_t flash_area_get_sectors (int32_t fa_id, uint32_t * p_count, struct flash_sector * p_sectors)
{
    /* MCUBoot works only if both source and destination have the same
     * sector size. */
#if (FLASH_TYPE == FLASH_TYPE_4)
    const size_t p_sector_size = FLASH_CF_MEDIUM_BLOCK_SIZE;
#elif (FLASH_TYPE == FLASH_TYPE_1)
    const size_t p_sector_size = FLASH_CF_BLOCK_SIZE;
#else
    const size_t sector_size = BSP_FEATURE_FLASH_LP_CF_BLOCK_SIZE;
#endif
    int32_t retval = -1;
    const struct flash_area * fa = prv_lookup_flash_area(fa_id);
    if (NULL == fa)
    {
        return -1;
    }

    if (fa->fa_device_id == FLASH_DEVICE_INTERNAL_FLASH)
    {
        /* All sectors are treated as the same size for internal flash. */
        uint32_t total_count = 0;
        for (size_t off = 0; off < fa->fa_size; off += p_sector_size)
        {
            /* Note: Offset here is relative to flash area, not device */
            p_sectors[total_count].fs_off  = off;
            p_sectors[total_count].fs_size = p_sector_size;
            total_count++;
        }

        *p_count = total_count;
        retval = 0;
    }
    else
    {
        retval = -1;
    }

    return retval;
}
/**********************************************************************************************************************
* End of function flash_area_get_sectors (uint32_t fa_id, uint32_t * p_count, struct flash_sector * p_sectors)
**********************************************************************************************************************/

#endif /* MCUBOOT_USE_FLASH_AREA_GET_SECTORS */

/**********************************************************************************************************************
* Function Name: flash_area_id_from_multi_image_slot
* Description  : Returns the `fa_id` for slot, where slot is 0 (primary) or 1
*                (secondary). `image_index` (0 or 1) is the index of the image.
*                Image index is relevant only when multi-image support support
*                is enabled
* Arguments    : int32_t image_index -
*                    Image index
*                int32_t slot -
*                    Slot number
* Return Value :  0, 1 - Success
*                -1 - Failure
**********************************************************************************************************************/
int32_t flash_area_id_from_multi_image_slot (int32_t image_index, int32_t slot)
{
    switch (slot)
    {
        case 0:
        {
            return FLASH_AREA_IMAGE_PRIMARY(image_index);
        }

        case 1:
        {
            return FLASH_AREA_IMAGE_SECONDARY(image_index);
        }

#if MCUBOOT_SWAP_USING_SCRATCH
        case 2:
        {
            return FLASH_AREA_IMAGE_SCRATCH;
        }
#endif
        default:
        {
            /* do nothing */;
        }
    }

    return -1;                         /* flash_area_open will fail on that */
}
/**********************************************************************************************************************
* End of function flash_area_id_from_multi_image_slot (int32_t image_index, int32_t slot)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_id_to_multi_image_slot
* Description  : Returns the slot (0 for primary or 1 for secondary),
*                for the supplied `image_index` and `area_id`.
*                `area_id` is unique and is represented by `fa_id` in the
*                `flash_area` struct.
* Arguments    : int32_t image_index -
*                    Image index
*                int32_t area_id -
*                    Flash area ID
* Return Value :  0, 1 - Success
*                -1 - Failure
**********************************************************************************************************************/
int32_t flash_area_id_to_multi_image_slot (int32_t image_index, int32_t area_id)
{
    if (area_id == FLASH_AREA_IMAGE_PRIMARY(image_index))
    {
        return 0;
    }

    if (area_id == FLASH_AREA_IMAGE_SECONDARY(image_index))
    {
        return 1;
    }

    BOOT_LOG_ERR("invalid flash area ID");

    return -1;
}
/**********************************************************************************************************************
* End of function flash_area_id_to_multi_image_slot (int32_t image_index, int32_t area_id)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_erased_val
* Description  : What is value is read from erased flash bytes.
* Arguments    : const struct flash_area * p_area -
*                    Pointer to flash area information.
* Return Value : UINT8_MAX
**********************************************************************************************************************/
uint8_t flash_area_erased_val (const struct flash_area * p_area)
{
    (void) p_area;

    return UINT8_MAX;
}
/**********************************************************************************************************************
* End of function flash_area_erased_val (const struct flash_area * p_area)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: rm_mcuboot_cleanup
* Description  : Clean up internal flash driver.
* Arguments    : void
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
int32_t rm_mcuboot_cleanup (void)
{
    int32_t err = flash_on_chip_cleanup();
    if (FSP_SUCCESS != err)
    {
        return -1;
    }

    return 0U;
}
/**********************************************************************************************************************
* End of function rm_mcuboot_cleanup (void)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_on_chip_cleanup
* Description  : Close the flash driver.
* Arguments    : void
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
int32_t flash_on_chip_cleanup (void)
{
    if (g_internal_flash_driver_open)
    {
#if RM_MCUBOOT_PORT_BUFFERED_WRITE_ENABLE
        const struct flash_area * p_internal_flash_area
                                    = prv_lookup_flash_area(FLASH_AREA_0_ID);
        /* Flush the write buffer. */
        flash_err_t ret = flash_on_chip_flush(p_internal_flash_area);
        assert(FLASH_SUCCESS == ret);
        (void)ret;
#endif

        /* Close the flash driver. */
        flash_err_t err = R_FLASH_Close();
        if (FLASH_SUCCESS != err)
        {
            return -1;
        }

        g_internal_flash_driver_open = false;
    }

    return 0;
}
/**********************************************************************************************************************
* End of function flash_on_chip_cleanup (void)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: flash_area_id_from_image_slot
* Description  : Unused, required to link with AC6.
* Arguments    : int32_t slot -
*                    Slot number
* Return Value : -1
**********************************************************************************************************************/
int32_t flash_area_id_from_image_slot (int32_t slot)
{
    /* Do nothing. */
    (void)slot;
    return -1;
}
/**********************************************************************************************************************
* End of function flash_area_id_from_image_slot (int32_t slot)
**********************************************************************************************************************/
