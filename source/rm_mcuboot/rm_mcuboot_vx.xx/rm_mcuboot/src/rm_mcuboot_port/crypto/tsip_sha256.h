/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : tsip_sha256.h
 * Version      : 1.0
 * Description  : This module implements functions used for hash value calculation.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdint.h>
#include "r_tsip_rx_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

#ifndef BOOTUTIL_CRYPTO_TSIP_SHA256_H
#define BOOTUTIL_CRYPTO_TSIP_SHA256_H

#define BOOTUTIL_CRYPTO_SHA256_DIGEST_SIZE_BYTES  (32)

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/
typedef struct tsip_sha_md5_handle bootutil_sha_context;

/**********************************************************************************************************************
* Function Name: bootutil_sha_init
* Description  : Prepare for hash value calculation.
* Arguments    : bootutil_sha_context * p_ctx -
*                    Pointer to the context used in hash value operations
* Return Value : none
**********************************************************************************************************************/
static inline void bootutil_sha_init (bootutil_sha_context * p_ctx)
{
    R_TSIP_Sha256Init(p_ctx);
}
/**********************************************************************************************************************
* End of function bootutil_sha_init (bootutil_sha_context * p_ctx)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_sha_drop
* Description  : Release resources for hash value calculation.
* Arguments    : bootutil_sha_context * p_ctx -
*                    Pointer to the context used in hash value operations
* Return Value : none
**********************************************************************************************************************/
static inline void bootutil_sha_drop (bootutil_sha_context * p_ctx)
{
    /* Do nothing. */
    (void) p_ctx;
}
/**********************************************************************************************************************
* End of function bootutil_sha_drop (bootutil_sha_context * p_ctx)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_sha_update
* Description  : Perform hash value calculation.
* Arguments    : bootutil_sha_context * p_ctx -
*                    Pointer to the context used in hash value operations
*                const void * p_data -
*                    Pointer to data to be operated on
*                uint32_t data_len -
*                    Data length
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
static inline int32_t bootutil_sha_update (bootutil_sha_context * p_ctx, const void * p_data, uint32_t data_len)
{
    e_tsip_err_t tsip_err = TSIP_SUCCESS;

    tsip_err = R_TSIP_Sha256Update(p_ctx, (uint8_t *) p_data, data_len);
    if (tsip_err != TSIP_SUCCESS)
    {
        return -1;
    }

    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_sha_update (bootutil_sha_context * p_ctx, const void * p_data, uint32_t data_len)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_sha_finish
* Description  : Write out the result of hash value operation.
* Arguments    : bootutil_sha_context * p_ctx -
*                    Pointer to the context used in hash value operations
*                uint8_t * p_output -
*                    Pointer to operation result
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
static inline int32_t bootutil_sha_finish (bootutil_sha_context * p_ctx, uint8_t * p_output)
{
    e_tsip_err_t tsip_err = TSIP_SUCCESS;
    uint32_t  digest_length = 0;

    tsip_err = R_TSIP_Sha256Final(p_ctx, p_output, &digest_length);
    if (tsip_err != TSIP_SUCCESS)
    {
        return -1;
    }

    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_sha_update (bootutil_sha_context * p_ctx, uint8_t * p_output)
**********************************************************************************************************************/

#endif /* BOOTUTIL_CRYPTO_TSIP_SHA256_H */
