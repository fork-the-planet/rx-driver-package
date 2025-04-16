/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : tsip_aes_ctr.h
 * Version      : 1.0
 * Description  : This module implements functions used for image decoding processing.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <string.h>
#include "mcuboot_config/mcuboot_config.h"
#if(defined(MCUBOOT_USE_TSIP)) != 1
#error "One crypto backend must be defined: either TSIP or TINYCRYPT"
#endif
#if defined(MCUBOOT_USE_TSIP)
#include <string.h>
#include "r_tsip_rx_if.h"
#include "tsip_keys.h"
#endif
#include <stdint.h>

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef BOOTUTIL_CRYPTO_TSIP_AES_CTR_H
#define BOOTUTIL_CRYPTO_TSIP_AES_CTR_H


#if defined (MCUBOOT_USE_TSIP)
/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/
typedef struct
{
    tsip_aes_key_index_t* p_key_index;
}tsip_aes_context_t;

typedef tsip_aes_context_t bootutil_aes_ctr_context;

/**********************************************************************************************************************
* Function Name: bootutil_aes_ctr_init
* Description  : Prepare for image encryption/decryption processing.
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used to decrypt the encrypted image
* Return Value : none
**********************************************************************************************************************/
static inline void bootutil_aes_ctr_init(bootutil_aes_ctr_context *p_ctx)
{
    /* Do nothing. */
    (void)p_ctx;
}
/**********************************************************************************************************************
* End of function bootutil_aes_ctr_init(bootutil_aes_ctr_context *p_ctx)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_aes_ctr_drop
* Description  : Release resources for image encryption/decryption processing.
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used to decrypt the encrypted image
* Return Value : none
**********************************************************************************************************************/
static inline void bootutil_aes_ctr_drop(bootutil_aes_ctr_context *p_ctx)
{
    /* Do nothing. */
    (void)p_ctx;
}
/**********************************************************************************************************************
* End of function bootutil_aes_ctr_drop(bootutil_aes_ctr_context *p_ctx)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_aes_ctr_set_key
* Description  : Set the key index of the image encryption key.
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used to decrypt the encrypted image
*                const uint8_t *p_k -
*                    Pointer to the key index of the image encryption key
* Return Value : 0 - Success
**********************************************************************************************************************/
static inline int32_t bootutil_aes_ctr_set_key(bootutil_aes_ctr_context *p_ctx, const uint8_t *p_k)
{
    p_ctx->p_key_index = (tsip_aes_key_index_t *)p_k;
    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_aes_ctr_set_key(bootutil_aes_ctr_context *p_ctx, const uint8_t *p_k)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_aes_ctr_encrypt
* Description  : Encrypt the input sentence and output the result.
*                According to the TSIP specifications, the processing is equivalent to bootutil_aes_ctr_decrypt.
*                This function is called by MCUboot when decrypting an encrypted image.
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used to decrypt the encrypted image
*                uint8_t *p_counter -
*                    Pointer to counter
*                const uint8_t *p_m -
*                    Pointer to input statement data
*                uint32_t mlen -
*                    Input sentence data length
*                size_t blk_off -
*                    Block offset
*                uint8_t *p_c -
*                    Pointer to output statement data
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
static inline int32_t bootutil_aes_ctr_encrypt(bootutil_aes_ctr_context *p_ctx, uint8_t *p_counter, const uint8_t *p_m,
                                                uint32_t mlen, size_t blk_off, uint8_t *p_c)
{
    e_tsip_err_t rc = TSIP_ERR_FAIL;
    tsip_aes_handle_t handle;

    /* If blk_off is non-zero, TSIP does nothing. */
    if (blk_off != 0)
    {
        return -1;
    }
    rc = R_TSIP_Aes256CtrInit(&handle, p_ctx->p_key_index, p_counter);
    if (rc != TSIP_SUCCESS)
    {
        return -1;
    }
    rc = R_TSIP_Aes256CtrUpdate(&handle, (uint8_t *)p_m, p_c, mlen);
    if (rc != TSIP_SUCCESS)
    {
        return -1;
    }
    rc = R_TSIP_Aes256CtrFinal(&handle);
    if (rc != TSIP_SUCCESS)
    {
        return -1;
    }
    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_aes_ctr_encrypt(bootutil_aes_ctr_context *p_ctx, uint8_t *p_counter, const uint8_t *p_m,
*                                             uint32_t mlen, size_t blk_off, uint8_t *p_c)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_aes_ctr_decrypt
* Description  : Decrypt the input sentence and output the result.
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used to decrypt the encrypted image
*                uint8_t *p_counter -
*                    Pointer to counter
*                const uint8_t *p_c -
*                    Pointer to input statement data
*                uint32_t clen -
*                    Input sentence data length
*                size_t blk_off -
*                    Block offset
*                uint8_t *p_m -
*                    Pointer to output statement data
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
static inline int32_t bootutil_aes_ctr_decrypt(bootutil_aes_ctr_context *p_ctx, uint8_t *p_counter, const uint8_t *p_c,
                                                uint32_t clen, size_t blk_off, uint8_t *p_m)
{
    e_tsip_err_t rc = TSIP_ERR_FAIL;
    tsip_aes_handle_t handle;

    /* If blk_off is non-zero, TSIP does nothing. */
    if (blk_off != 0)
    {
        return -1;
    }
    rc = R_TSIP_Aes256CtrInit(&handle, p_ctx->p_key_index, p_counter);
    if (rc != TSIP_SUCCESS)
    {
        return -1;
    }
    rc = R_TSIP_Aes256CtrUpdate(&handle, (uint8_t *)p_c, p_m, clen);
    if (rc != TSIP_SUCCESS)
    {
        return -1;
    }
    rc = R_TSIP_Aes256CtrFinal(&handle);
    if (rc != TSIP_SUCCESS)
    {
        return -1;
    }
    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_aes_ctr_decrypt(bootutil_aes_ctr_context *p_ctx, uint8_t *p_counter, const uint8_t *p_c,
*                                                 uint32_t clen, size_t blk_off, uint8_t *p_m)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_aes_ctr_finish
* Description  : Prepare for .
* Arguments    : bootutil_aes_ctr_context *p_ctx -
*                    Pointer to the context used to decrypt the encrypted image
* Return Value : 0 - Success
**********************************************************************************************************************/
static inline int32_t bootutil_aes_ctr_finish(bootutil_aes_ctr_context *p_ctx)
{
    /* Do nothing. */
    (void)p_ctx;
    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_aes_ctr_finish(bootutil_aes_ctr_context *p_ctx)
**********************************************************************************************************************/

#endif /* MCUBOOT_USE_TSIP */
#endif /* BOOTUTIL_CRYPTO_TSIP_AES_CTR_H */
