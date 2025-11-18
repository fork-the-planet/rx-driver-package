/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : rm_mcuboot_config.h
 * Version      : 1.0
 * Description  : This is a private header file used internally by MCUboot and the porting section.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *           30.06.2025 1.01    Added support for RX66N, RX72M and RX671
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

#ifndef RM_MCUBOOT_CONFIG_H
#define RM_MCUBOOT_CONFIG_H

/* Select MCUboot upgrade mode.
 *   0:Overwrite Only
 *   1:Overwrite Only Fast
 *   2:Swap
 *   3:Direct XIP
 */
#define RM_MCUBOOT_CFG_UPGRADE_MODE (0)

/* Set this to 1 to perform signature verification of the Primary image. */
#define RM_MCUBOOT_CFG_VALIDATE_PRIMARY_SLOT (1)

/* Set this to 1 to prevent downgrades when performing updates.
 * Can only be changed when the upgrade mode is set to overwrite only.
 */
#define RM_MCUBOOT_CFG_DOWNGRADE_PREVENTION (0)

/* Set this to 1 when using a user-defined watchdog feed. */
#define RM_MCUBOOT_CFG_WATCHDOG_FEED_ENABLED (0)

/* Register a user-defined watch dog function. */
#define RM_MCUBOOT_CFG_WATCHDOG_FEED_FUNCTION (my_watchdog_feed_function())

/* Setting the authentication method for signature verification.
 * If RM_MCUBOOT_CFG_VALIDATE_PRIMARY_SLOT is set to 1, perform primary image signature verification using the method
 * set here.
 *   0:No signature verification is performed.
 *   1:ECDSA P-256
 *   2:RSA 2048
 */
#define RM_MCUBOOT_CFG_SIGN (1)

/* Set the decryption function for encrypted images.
 * If an Upgrade Mode other than the Direct XIP method is set, this setting can be made.
 *   0:Encryption Disabled
 *   1:Key Wrap
 */
#define RM_MCUBOOT_CFG_APPLICATION_ENCRYPTION_SCHEME (0)

/* Set this to 0 to use the sample DER format public key data.
 * If authentication method for signature verification is not set, it cannot be changed.
 */
#define RM_MCUBOOT_CFG_DER_PUB_USER_KEY_ENABLE (0)

/* Set the address of the public key used for signature verification. */
#define RM_MCUBOOT_CFG_VERIFY_KEY_ADDRESS (NULL)

/* Set the address of the key encryption key used for image decryption. */
#define RM_MCUBOOT_CFG_ENCRYPT_KEY_ADDRESS (NULL)

/* Set the size of the area allocated to MCUboot. */
#define RM_MCUBOOT_CFG_MCUBOOT_AREA_SIZE (0x10000)

/* Set the size of the area allocated to the application image. */
#define RM_MCUBOOT_CFG_APPLICATION_AREA_SIZE (0xF8000)

/* Set the scratch area size.
 * This setting is required when Swap is specified in upgrade mode.
 * It is necessary to set an integral multiple of the flash sector size used as the scratch area.
 */
#define RM_MCUBOOT_CFG_SCRATCH_AREA_SIZE (0x0)

/* Log settings
 * Logs of the specified level are output from MCUboot.
 *   0:Off
 *   1:Error
 *   2:Warning
 *   3:Info
 *   4:Debug
 */
#define RM_MCUBOOT_CFG_LOG_LEVEL (0)

/* Setting the secure IP to use.
 * Set this depending on the secure IP module being added.
 *   0:TSIP
 *   1:RSIP
 */
#define RM_MCUBOOT_CFG_SELECT_SECURE_IP (0)

#endif/* RM_MCUBOOT_CONFIG_H */
