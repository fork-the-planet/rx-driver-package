/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : mcuboot_config.h
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
#include "rm_mcuboot_config.h"

#include "bootutil/crypto/common.h"
#include "r_flash_rx_if.h"

#if (RM_MCUBOOT_CFG_SELECT_SECURE_IP == 1)
#include "r_rsip_protected_rx_if.h"
#if (RM_MCUBOOT_CFG_SIGN == 1)
#include "rsip_ecdsa_p256.h"
#endif /* RM_MCUBOOT_CFG_SIGN */
#include "rsip_sha256.h"
#else
#include "r_tsip_rx_if.h"
#if (RM_MCUBOOT_CFG_SIGN == 1)
#include "tsip_ecdsa_p256.h"
#endif /* RM_MCUBOOT_CFG_SIGN */
#include "tsip_sha256.h"
#endif /* RM_MCUBOOT_CFG_SELECT_SECURE_IP */

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef MCUBOOT_CONFIG_H
#define MCUBOOT_CONFIG_H

/** Upgrade mode */
#if (RM_MCUBOOT_CFG_UPGRADE_MODE == 0)
/** Define the following macro to enable Overwrite Only mode processing. */
#define MCUBOOT_OVERWRITE_ONLY
#elif (RM_MCUBOOT_CFG_UPGRADE_MODE == 1)
/** Define the following macro to enable Overwrite Only Fast mode processing. */
#define MCUBOOT_OVERWRITE_ONLY
#define MCUBOOT_OVERWRITE_ONLY_FAST
#elif (RM_MCUBOOT_CFG_UPGRADE_MODE == 2)
/** Define nothing. */
#elif (RM_MCUBOOT_CFG_UPGRADE_MODE == 3)
/** Define the following macro to enable Direct XIP mode processing. */
#define MCUBOOT_DIRECT_XIP
#endif /* RM_MCUBOOT_CFG_UPGRADE_MODE */

/** Define the following macro to enable the processing required for TSIP. */
#if (RM_MCUBOOT_CFG_SELECT_SECURE_IP == 1)
#define MCUBOOT_USE_RSIP
#else
#define MCUBOOT_USE_TSIP
#endif

/** Define the following macro to avoid build errors. */
#define MCUBOOT_USE_USER_DEFINED_CRYPTO_STACK

/** Signature verification format
 *  If signature verification is not performed, no macros are defined.*/
#if (RM_MCUBOOT_CFG_SIGN == 1)
/** Define the following macro to enable signature verification processing by ECDSA. */
#define MCUBOOT_SIGN_EC256
#elif (RM_MCUBOOT_CFG_SIGN == 2)
/** Define the following macro to enable signature verification processing by RSA. */
#define MCUBOOT_SIGN_RSA
/** RSA key length */
#define MCUBOOT_SIGN_RSA_LEN (2048)
#endif /* RM_MCUBOOT_CFG_SIGN */

/** Validate primary slot */
#if (RM_MCUBOOT_CFG_VALIDATE_PRIMARY_SLOT == 1)
/** Define the following macro to enable the processing required for primary slot validation. */
#define MCUBOOT_VALIDATE_PRIMARY_SLOT
#endif /* RM_MCUBOOT_CFG_VALIDATE_PRIMARY_SLOT */

/** Downgrade Prevention */
#if ((defined(MCUBOOT_OVERWRITE_ONLY)) && (RM_MCUBOOT_CFG_DOWNGRADE_PREVENTION == 1))
/** Define the following macro to enable the processing required for downgrade prevention. */
#define MCUBOOT_DOWNGRADE_PREVENTION
#endif /* RM_MCUBOOT_CFG_DOWNGRADE_PREVENTION */

/** To get information about sectors within an area, define the following macro. */
#define MCUBOOT_USE_FLASH_AREA_GET_SECTORS

/** Number of images in primary and secondary areas.
 *  RX does not allow multiple images to fit into one slot. */
#define MCUBOOT_IMAGE_NUMBER (1)

/** Log level */
#if (RM_MCUBOOT_CFG_LOG_LEVEL == 0)
/** Define the following macro to disable log output processing. */
#define MCUBOOT_LOG_LEVEL    (MCUBOOT_LOG_LEVEL_OFF)
#define MCUBOOT_HAVE_LOGGING (0)
#elif (RM_MCUBOOT_CFG_LOG_LEVEL == 1)
/** Define the following macro to enable the process of outputting error logs. */
#define MCUBOOT_LOG_LEVEL    (MCUBOOT_LOG_LEVEL_ERROR)
#define MCUBOOT_HAVE_LOGGING (1)
#elif (RM_MCUBOOT_CFG_LOG_LEVEL == 2)
/** Define the following macro to enable the process of outputting warning logs. */
#define MCUBOOT_LOG_LEVEL    (MCUBOOT_LOG_LEVEL_WARNING)
#define MCUBOOT_HAVE_LOGGING (1)
#elif (RM_MCUBOOT_CFG_LOG_LEVEL == 3)
/** Define the following macro to enable the process of outputting information logs. */
#define MCUBOOT_LOG_LEVEL    (MCUBOOT_LOG_LEVEL_INFO)
#define MCUBOOT_HAVE_LOGGING (1)
#elif (RM_MCUBOOT_CFG_LOG_LEVEL == 4)
/** Define the following macro to enable the process of outputting debug logs. */
#define MCUBOOT_LOG_LEVEL    (MCUBOOT_LOG_LEVEL_DEBUG)
#define MCUBOOT_HAVE_LOGGING (1)
#endif /* RM_MCUBOOT_CFG_LOG_LEVEL */

/** Encryption scheme */
#if (RM_MCUBOOT_CFG_APPLICATION_ENCRYPTION_SCHEME == 1)
/** Define the following macro to enable the process of image encryption. */
#define MCUBOOT_ENC_IMAGES
#define MCUBOOT_ENCRYPT_KW
#define MCUBOOT_AES_256
#endif /* RM_MCUBOOT_CFG_APPLICATION_ENCRYPTION_SCHEME */

/** Watchdog feed */
#if (RM_MCUBOOT_CFG_WATCHDOG_FEED_ENABLED == 0)
#define MCUBOOT_WATCHDOG_FEED()
#elif (RM_MCUBOOT_CFG_WATCHDOG_FEED_ENABLED == 1)
#define MCUBOOT_WATCHDOG_FEED() RM_MCUBOOT_CFG_WATCHDOG_FEED_FUNCTION
#endif /* RM_MCUBOOT_CFG_WATCHDOG_FEED_ENABLED */

/** MCUboot area size */
#define RM_MCUBOOT_PORT_CFG_MCUBOOT_SIZE (RM_MCUBOOT_CFG_MCUBOOT_AREA_SIZE)

/** Application image size */
#define RM_MCUBOOT_PORT_CFG_PARTITION_SIZE (RM_MCUBOOT_CFG_APPLICATION_AREA_SIZE)

/** Scratch area size */
#if (RM_MCUBOOT_CFG_UPGRADE_MODE == 2)
#define RM_MCUBOOT_PORT_CFG_SCRATCH_SIZE (RM_MCUBOOT_CFG_SCRATCH_AREA_SIZE)
#else
#define RM_MCUBOOT_PORT_CFG_SCRATCH_SIZE (0x0)
#endif

/** Image area sector size */
#if (FLASH_TYPE == FLASH_TYPE_1)
#define FLASH_AREA_IMAGE_SECTOR_SIZE    (FLASH_CF_BLOCK_SIZE)
#else
#define FLASH_AREA_IMAGE_SECTOR_SIZE    (FLASH_CF_MEDIUM_BLOCK_SIZE)
#endif
/** Maximum alignment value */
#define MCUBOOT_BOOT_MAX_ALIGN          (FLASH_CF_MIN_PGM_SIZE)

#if (MCUBOOT_IMAGE_NUMBER == 1)
/** Maximum sector size */
#define RM_MCUBOOT_LARGEST_SECTOR       (RM_MCUBOOT_PORT_CFG_PARTITION_SIZE)

/** Maximum number of image sectors supported by the bootloader. */
#define MCUBOOT_MAX_IMG_SECTORS    ((RM_MCUBOOT_LARGEST_SECTOR) / \
                                    FLASH_AREA_IMAGE_SECTOR_SIZE)
#endif /* MCUBOOT_IMAGE_NUMBER */

#if defined(MCUBOOT_USE_RSIP)
extern rsip_instance_ctrl_t g_rsip_ctrl;
extern rsip_cfg_t g_rsip_cfg;
#endif

#if (RM_MCUBOOT_CFG_WATCHDOG_FEED_ENABLED == 1)
void RM_MCUBOOT_CFG_WATCHDOG_FEED_FUNCTION(void);
#endif /* RM_MCUBOOT_CFG_WATCHDOG_FEED_ENABLED */

#endif /* MCUBOOT_CONFIG_H */
