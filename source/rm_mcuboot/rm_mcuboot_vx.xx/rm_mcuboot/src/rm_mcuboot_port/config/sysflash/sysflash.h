/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : sysflash.h
 * Version      : 1.0
 * Description  : This is a private header file used internally by MCUboot and the porting section.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *           30.06.2025 1.01    Added support for RX66N, RX72M and RX671
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "mcuboot_config/mcuboot_config.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef SYSFLASH_H
#define SYSFLASH_H

#define FLASH_DEVICE_INTERNAL_FLASH    (0x7F)
#define FLASH_DEVICE_EXTERNAL_FLASH    (0x80)

/** ID of bootloader in flash area */
#define FLASH_AREA_BOOTLOADER          (0)
/** ID of image 0 in flash area */
#define FLASH_AREA_IMAGE_0             (1)
/** ID of image 1 in flash area */
#define FLASH_AREA_IMAGE_1             (2)
/** ID of scratch area in flash area */
#define FLASH_AREA_IMAGE_SCRATCH       (3)
/** ID of image 2 in flash area */
#define FLASH_AREA_IMAGE_2             (5)
/** ID of image 3 in flash area */
#define FLASH_AREA_IMAGE_3             (6)

#if (MCUBOOT_IMAGE_NUMBER == 1)
/** Primary slot area ID  */
#define FLASH_AREA_IMAGE_PRIMARY(x)      (((x) == 0) ? FLASH_AREA_IMAGE_0 : FLASH_AREA_IMAGE_0)
/** Secondary slot area ID */
#define FLASH_AREA_IMAGE_SECONDARY(x)    (((x) == 0) ? FLASH_AREA_IMAGE_1 : FLASH_AREA_IMAGE_1)
#else
#warning "Image slot and flash area mapping is not defined"
#endif

#if (FLASH_TYPE == FLASH_TYPE_1)
/** Define the following macro to enable the processing required for linear mode. */
#define RM_MCUBOOT_DUAL_BANK_ENABLED    (0)
#else
#if (BSP_CFG_CODE_FLASH_BANK_MODE == 0)
/** Define the following macro to enable the processing required for dual bank mode. */
#define RM_MCUBOOT_DUAL_BANK_ENABLED    (1)
#endif
#endif

/** Offset of MCUboot in flash area */
#define FLASH_AREA_MCUBOOT_OFFSET     (uint32_t)(FLASH_CF_BLOCK_END - RM_MCUBOOT_PORT_CFG_MCUBOOT_SIZE + 1)

#if (MCUBOOT_IMAGE_NUMBER == 1)

/* Secure + Non-Secure image primary slot */
/** ID of primary image slot */
#define FLASH_AREA_0_ID        (FLASH_AREA_IMAGE_0)
/** Offset of primary image */
#define FLASH_AREA_0_OFFSET    (uint32_t)(FLASH_AREA_MCUBOOT_OFFSET - RM_MCUBOOT_PORT_CFG_PARTITION_SIZE)
/** Size of primary image */
#define FLASH_AREA_0_SIZE      (uint32_t)(RM_MCUBOOT_PORT_CFG_PARTITION_SIZE)

/* Secure + Non-secure secondary slot */
/** ID of primary image */
#define FLASH_AREA_2_ID        (FLASH_AREA_IMAGE_1)
/** Offset of secondary image */
#if (RM_MCUBOOT_DUAL_BANK_ENABLED)
#define FLASH_AREA_2_OFFSET    (uint32_t)(FLASH_CF_LO_BANK_HI_ADDR - RM_MCUBOOT_PORT_CFG_MCUBOOT_SIZE \
                                          - RM_MCUBOOT_PORT_CFG_PARTITION_SIZE + 1)
#else
#define FLASH_AREA_2_OFFSET    (uint32_t)(FLASH_AREA_0_OFFSET - RM_MCUBOOT_PORT_CFG_PARTITION_SIZE)
#endif /* RM_MCUBOOT_DUAL_BANK_ENABLED */
/** Size of secondary image */
#define FLASH_AREA_2_SIZE      (uint32_t)(RM_MCUBOOT_PORT_CFG_PARTITION_SIZE)

/* Swap space.  */
/** ID of scratch area */
#define FLASH_AREA_SCRATCH_ID         (FLASH_AREA_IMAGE_SCRATCH)
/** Offset of scratch area */
#define FLASH_AREA_SCRATCH_OFFSET     (uint32_t)(FLASH_AREA_2_OFFSET - RM_MCUBOOT_PORT_CFG_SCRATCH_SIZE)
/** Size of scratch area */
#define FLASH_AREA_SCRATCH_SIZE       (uint32_t)(RM_MCUBOOT_PORT_CFG_SCRATCH_SIZE)

#endif /* (MCUBOOT_IMAGE_NUMBER == 1) */

#endif /* SYSFLASH_H */
