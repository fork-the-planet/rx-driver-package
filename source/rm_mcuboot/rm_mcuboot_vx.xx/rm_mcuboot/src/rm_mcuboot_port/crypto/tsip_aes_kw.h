/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : tsip_aes_kw.h
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

#if defined(MCUBOOT_USE_TSIP)
#include "r_tsip_rx_if.h"
#include "tsip_aes_ctr.h"
#include "tsip_keys.h"
#endif

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef BOOTUTIL_CRYPTO_TSIP_AES_KW_H
#define BOOTUTIL_CRYPTO_TSIP_AES_KW_H

#if(defined(MCUBOOT_USE_TSIP)) != 1
#error "One crypto backend must be defined: either TSIP or TINYCRYPT"
#endif

#if defined(MCUBOOT_USE_TSIP)

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/
typedef tsip_aes_context_t bootutil_aes_kw_context;

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
*                    Pointer to the key_index of the key encryption key
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
    p_ctx->p_key_index = (tsip_aes_key_index_t*)p_k;
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
    e_tsip_err_t rc = TSIP_ERR_FAIL;

    rc = R_TSIP_Aes256KeyUnwrap(p_ctx->p_key_index, R_TSIP_KEYWRAP_AES256, (uint32_t*)p_wrapped_key, (tsip_aes_key_index_t*)p_key);
    if (rc != TSIP_SUCCESS)
    {
        return -1;
    }

    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_aes_kw_unwrap(bootutil_aes_kw_context *p_ctx, const uint8_t *p_wrapped_key,
                                            uint32_t wrapped_key_len, uint8_t *p_key, uint32_t key_len)
**********************************************************************************************************************/
#endif /* MCUBOOT_USE_TSIP */

#endif /* BOOTUTIL_CRYPTO_TSIP_AES_KW_H */
