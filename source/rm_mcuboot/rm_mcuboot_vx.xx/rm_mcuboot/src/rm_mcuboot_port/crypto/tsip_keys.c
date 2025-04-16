/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : tsip_keys.c
 * Version      : 1.0
 * Description  : This module implements Wrapped Key for the two keys described below.
 *                    1. Public key used for signature verification
 *                    2. Key encryption key used to encrypt the image encryption key
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "bootutil/sign_key.h"
#include "mcuboot_config/mcuboot_config.h"
#include "tsip_keys.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

#if defined(MCUBOOT_USE_TSIP)
#if (RM_MCUBOOT_CFG_DER_PUB_USER_KEY_ENABLE == 0)
const struct bootutil_key bootutil_keys[] = {
    {
        .key = NULL,
        .len = NULL,
    },
};
const int bootutil_key_cnt = 0;
#endif

#if defined (MCUBOOT_SIGN_RSA)
#define HAVE_KEYS
#if (MCUBOOT_SIGN_RSA_LEN == 2048)
const unsigned int g_pub_key_len_bytes = MCUBOOT_TSIP_RSA_PUB_KEY_LEN;
#endif /* MCUBOOT_SIGN_RSA_LEN == 2048 */

#elif defined(MCUBOOT_SIGN_EC256)
#define HAVE_KEYS
const unsigned int g_pub_key_len_bytes = MCUBOOT_TSIP_ECC_PUB_KEY_LEN;
#endif

#if defined (HAVE_KEYS)
const struct bootutil_key g_bootutil_keys_wrapped[] =
{
    {
        .key = (uint8_t *)RM_MCUBOOT_CFG_VERIFY_KEY_ADDRESS,
        .len = &g_pub_key_len_bytes,
    }
};
#endif /* HAVE_KEYS */


#if defined(MCUBOOT_ENCRYPT_KW)
const unsigned int enc_key_len = MCUBOOT_TSIP_KEY_WRAP_KEY_LEN;

const struct bootutil_key bootutil_enc_key = {
    .key = (uint8_t *)RM_MCUBOOT_CFG_ENCRYPT_KEY_ADDRESS,
    .len = &enc_key_len,
};
#endif /* MCUBOOT_ENCRYPT_KW */

#endif /* MCUBOOT_USE_TSIP */
