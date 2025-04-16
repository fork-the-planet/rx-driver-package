/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : tsip_ecdsa_p256.h
 * Version      : 1.0
 * Description  : This module implements some of the functions used for ECDSA signature verification.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <string.h>
#include "r_tsip_rx_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef BOOTUTIL_CRYPTO_TSIP_ECDSA_P256_H
#define BOOTUTIL_CRYPTO_TSIP_ECDSA_P256_H

#define BOOTUTIL_CRYPTO_ECDSA_P256_SIGNATURE_SIZE_BYTES         (64U)

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/
typedef uintptr_t bootutil_ecdsa_context_t;

/**********************************************************************************************************************
* Function Name: bootutil_ecdsa_init
* Description  : Prepare ECDSA signature verification with key length of 256 bits.
* Arguments    : bootutil_ecdsa_context_t * p_ctx -
*                    Pointer to the context used for signature verification
* Return Value : none
**********************************************************************************************************************/
static inline void bootutil_ecdsa_init (bootutil_ecdsa_context_t * p_ctx)
{
    /* Do nothing. */
    (void) p_ctx;
}
/**********************************************************************************************************************
* End of function bootutil_ecdsa_init (bootutil_ecdsa_context_t * p_ctx)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_ecdsa_drop
* Description  : Release resources for ECDSA signature verification with key length 256 bits.
* Arguments    : bootutil_ecdsa_context_t * p_ctx -
*                    Pointer to the context used for signature verification
* Return Value : none
**********************************************************************************************************************/
static inline void bootutil_ecdsa_drop (bootutil_ecdsa_context_t * p_ctx)
{
    /* Do nothing. */
    (void) p_ctx;
}
/**********************************************************************************************************************
* End of function bootutil_ecdsa_drop (bootutil_ecdsa_context_t * p_ctx)
**********************************************************************************************************************/

#endif /* BOOTUTIL_CRYPTO_TSIP_ECDSA_P256_H */
