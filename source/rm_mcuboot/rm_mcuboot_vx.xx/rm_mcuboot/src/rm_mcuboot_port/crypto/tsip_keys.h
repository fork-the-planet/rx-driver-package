/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : tsip_keys.h
 * Version      : 1.0
 * Description  : This is key header file used by the TSIP module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "mcuboot_config/mcuboot_config.h"
#include "bootutil/sign_key.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef TSIP_KEYS_H
#define TSIP_KEYS_H

/* Convert input bit data into byte units. */
#define RM_MCUBOOT_PORT_BITS_TO_BYTES(bits)    (((bits) + 7) / 8)

#if defined(MCUBOOT_USE_TSIP)
#if defined(MCUBOOT_SIGN_EC256)

/* NUM_ECC_BYTES is the size of the P256 private key.
 * 2 x NUM_ECC_BYTES is the size of the public key and the signature. */
#define NUM_ECC_BYTES (32U)

/* The size of the ECDSA public key index. */
#define MCUBOOT_TSIP_ECC_PUB_KEY_LEN (sizeof(tsip_ecc_public_key_index_t))

#elif defined(MCUBOOT_SIGN_RSA)
#if MCUBOOT_SIGN_RSA_LEN == 2048
/* The size of the RSA public key index. */
#define MCUBOOT_TSIP_RSA_PUB_KEY_LEN (sizeof(tsip_rsa2048_public_key_index_t))
#endif
#endif

#if defined(MCUBOOT_ENCRYPT_KW)
/* The size of the key wrap key index. */
#define MCUBOOT_TSIP_KEY_WRAP_KEY_LEN (sizeof(tsip_aes_key_index_t))
#endif

extern const struct bootutil_key g_bootutil_keys_wrapped[];
extern const struct bootutil_key bootutil_enc_key;
#endif /* MCUBOOT_USE_TSIP */

#endif /* TSIP_KEYS_H */
