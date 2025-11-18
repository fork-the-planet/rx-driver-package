/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : rsip_aes_kw.h
 * Version      : 1.0
 * Description  : This module implements functions used for key wrap processing.
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

#if defined(MCUBOOT_USE_RSIP)
#include "r_rsip_protected_rx_if.h"
#include "rsip_aes_ctr.h"
#include "rsip_keys.h"
#endif

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef BOOTUTIL_CRYPTO_RSIP_AES_KW_H
#define BOOTUTIL_CRYPTO_RSIP_AES_KW_H

#if(defined(MCUBOOT_USE_RSIP)) != 1
#error "One crypto backend must be defined: either RSIP or TINYCRYPT"
#endif

#if defined(MCUBOOT_USE_RSIP)

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/
typedef rsip_aes_context_t bootutil_aes_kw_context;

/**********************************************************************************************************************
* Function Name: bootutil_aes_kw_init
* Description  : Initialize key wrap processing.
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used in key wrap processing
* Return Value : none
**********************************************************************************************************************/
static inline void bootutil_aes_kw_init(bootutil_aes_kw_context *p_ctx)
{
    /* Do nothing. */
    (void)p_ctx;
}
/**********************************************************************************************************************
* End of function bootutil_aes_kw_init(bootutil_aes_kw_context *p_ctx)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_aes_kw_drop
* Description  : Release resources for key wrap processing.
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used in key wrap processing
* Return Value : none
**********************************************************************************************************************/
static inline void bootutil_aes_kw_drop(bootutil_aes_kw_context *p_ctx)
{
    /* Do nothing. */
    (void)p_ctx;
}
/**********************************************************************************************************************
* End of function bootutil_aes_kw_drop(bootutil_aes_kw_context *p_ctx)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_aes_kw_set_unwrap_key
* Description  : Set the key encryption key.
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used in key wrap processing
*                const uint8_t *p_k -
*                    Pointer to the Wrapped Key of the key encryption key
*                uint32_t klen -
*                    Key encryption key size
* Return Value : 0 - Success
**********************************************************************************************************************/
static inline int32_t bootutil_aes_kw_set_unwrap_key(bootutil_aes_kw_context *p_ctx, const uint8_t *p_k, uint32_t klen)
{
    (void)klen;
    /** If the key wrap key address is not set, -1 is returned. */
    if (p_k == NULL)
    {
        return -1;
    }
    p_ctx->p_key = (rsip_wrapped_key_t*)p_k;
    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_aes_kw_set_unwrap_key(bootutil_aes_kw_context *p_ctx, const uint8_t *p_k, uint32_t klen)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_aes_kw_unwrap
* Description  : Decrypts the encrypted image encryption key.
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used in key wrap processing
*                const uint8_t *p_wrapped_key -
*                    Pointer to encrypted image encryption key data
*                uint32_t wrapped_key_len -
*                    Size of encrypted image encryption key data
*                uint8_t *p_key -
*                    Pointer to the key index of the image encryption key
*                uint32_t key_len -
*                    Image encryption key size
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
static inline int32_t bootutil_aes_kw_unwrap(bootutil_aes_kw_context *p_ctx, const uint8_t *p_wrapped_key,
                                            uint32_t wrapped_key_len, uint8_t *p_key, uint32_t key_len)
{
    (void)wrapped_key_len;
    (void)key_len;
    fsp_err_t err = FSP_ERR_ASSERTION;

    err = R_RSIP_RFC3394_KeyUnwrap(&g_rsip_ctrl, p_ctx->p_key, RSIP_KEY_TYPE_AES_256, (uint8_t*)p_wrapped_key, (rsip_wrapped_key_t*)p_key);
    if (FSP_SUCCESS != err)
    {
        return -1;
    }

    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_aes_kw_unwrap(bootutil_aes_kw_context *p_ctx, const uint8_t *p_wrapped_key,
                                            uint32_t wrapped_key_len, uint8_t *p_key, uint32_t key_len)
**********************************************************************************************************************/
#endif /* MCUBOOT_USE_RSIP */

#endif /* BOOTUTIL_CRYPTO_RSIP_AES_KW_H */
