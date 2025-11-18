/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
#ifndef R_RSIP_CM_RX_CONFIG_HEADER_FILE
#define R_RSIP_CM_RX_CONFIG_HEADER_FILE

#define BSP_FEATURE_RSIP_RSIP_E11A_SUPPORTED                (1)

/*** rm_psa_crypto module configurations **/
#define PSA_CRYPTO_CFG_PLAINTEXT_KEY_SUPPORT                (0x01)
#define PSA_CRYPTO_CFG_WRAPPED_KEY_SUPPORT                  (0x02)

#define PSA_CRYPTO_CFG_WRAPPED_AND_PLAINTEXT_KEY_SUPPORT    ((PSA_CRYPTO_CFG_PLAINTEXT_KEY_SUPPORT) | \
                                                            (PSA_CRYPTO_CFG_WRAPPED_KEY_SUPPORT))
/*** rm_psa_crypto module wrapped key configurations **/
#define PSA_CRYPTO_IS_WRAPPED_SUPPORT_REQUIRED(type)        ((type) & PSA_CRYPTO_CFG_WRAPPED_KEY_SUPPORT)
/*** rm_psa_crypto module plaintext key configurations **/
#define PSA_CRYPTO_IS_PLAINTEXT_SUPPORT_REQUIRED(type)      ((type) & PSA_CRYPTO_CFG_PLAINTEXT_KEY_SUPPORT)

#define PSA_CRYPTO_CFG_AES_FORMAT                           (3)
#define PSA_CRYPTO_CFG_ECC_FORMAT                           (3)
/*** end-rm_psa_crypto module configurations **/

#endif /* R_RSIP_RX_CONFIG_HEADER_FILE */
