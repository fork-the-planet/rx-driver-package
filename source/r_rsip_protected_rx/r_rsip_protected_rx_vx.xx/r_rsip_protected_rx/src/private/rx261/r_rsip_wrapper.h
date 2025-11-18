/*
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_rsip_wrapper.h
* Description  : RSIP function wrapper header file.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.10.2024 1.00     First Release.
*         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
*         :                     Revised key management specification
***********************************************************************************************************************/
#ifndef R_RSIP_WRAPPER_H
#define R_RSIP_WRAPPER_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_primitive.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RSIP_DUMMY_LC                   (0x00000002)

#define RSIP_PRV_PKI_HASH_TYPE_SHA1                                     (0U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA224                                   (0U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA256                                   (1U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA384                                   (4U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA512                                   (5U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA512_224                               (2U)
#define RSIP_PRV_PKI_HASH_TYPE_SHA512_256                               (3U)

/* Primitive function names */
#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_128                         r_rsip_p07
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_128                         r_rsip_wrapper_p6f_aes128
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_AES_128                        r_rsip_p6e_aes128

#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_128                  r_rsip_wrapper_p47i_aes128ecb_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_128                  r_rsip_wrapper_p47i_aes128ecb_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_128                  r_rsip_wrapper_p47i_aes128cbc_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_128                  r_rsip_wrapper_p47i_aes128cbc_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_128_WRAPPED_IV       r_rsip_wrapper_p47i_aes128cbc_encrypt_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_128_WRAPPED_IV       r_rsip_wrapper_p47i_aes128cbc_decrypt_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_128                      r_rsip_wrapper_p47i_aes128ctr_crypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_128                        r_rsip_p47u
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_128                         r_rsip_p47f

#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_128                         r_rsip_wrapper_p29i_aes128gcm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_128_WRAPPED_IV              r_rsip_wrapper_p29i_aes128gcm_encrypt_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_128                   r_rsip_p29a
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_128            r_rsip_p29t
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_128                       r_rsip_p29u
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_128                        r_rsip_p29f
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_128                         r_rsip_wrapper_p32i_aes128gcm_decrypt
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_128_WRAPPED_IV              r_rsip_wrapper_p32i_aes128gcm_decrypt_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_128                   r_rsip_p32a
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_128            r_rsip_p32t
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_128                       r_rsip_p32u
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_128                        r_rsip_p32f

#define RSIP_PRV_FUNC_NAME_GHASH_COMPUTE                                r_rsip_p21

#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_INIT_128                         r_rsip_wrapper_p95i_aes128ccm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_UPDATE_128                       r_rsip_p95u
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_FINAL_128                        r_rsip_wrapper_p95f_aes128ccm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_INIT_128                         r_rsip_wrapper_p98i_aes128ccm_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_UPDATE_128                       r_rsip_p98u
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_FINAL_128                        r_rsip_wrapper_p98f_aes128ccm_decrypt

#define RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_128                            r_rsip_wrapper_p41i_aes128mac
#define RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_128                          r_rsip_p41u
#define RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_128                  r_rsip_wrapper_p41f_aes128mac_generate
#define RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_128                    r_rsip_wrapper_p41f_aes128mac_verify

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_AES_256                         r_rsip_p08
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_AES_256                         r_rsip_wrapper_p6f_aes256
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_AES_256                        r_rsip_p6e_aes256

#define RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_WRAP                     r_rsip_wrapper_p8f_aes128
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_128_KEY_UNWRAP                   r_rsip_wrapper_p90_aes128
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_WRAP                     r_rsip_wrapper_p8f_aes256
#define RSIP_PRV_FUNC_NAME_RFC3394_AES_256_KEY_UNWRAP                   r_rsip_wrapper_p90_aes256
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_128                        NULL
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_1_AES_128                        NULL

#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_ENC_256                  r_rsip_wrapper_p50i_aes256ecb_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_ECB_DEC_256                  r_rsip_wrapper_p50i_aes256ecb_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_256                  r_rsip_wrapper_p50i_aes256cbc_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_256                  r_rsip_wrapper_p50i_aes256cbc_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_ENC_256_WRAPPED_IV       r_rsip_wrapper_p50i_aes256cbc_encrypt_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CBC_DEC_256_WRAPPED_IV       r_rsip_wrapper_p50i_aes256cbc_decrypt_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_INIT_CTR_256                      r_rsip_wrapper_p50i_aes256ctr_crypt
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_UPDATE_256                        r_rsip_p50u
#define RSIP_PRV_FUNC_NAME_AES_CIPHER_FINAL_256                         r_rsip_p50f
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_0_AES_256                        NULL
#define RSIP_PRV_FUNC_NAME_OTF_CHANNEL_1_AES_256                        NULL

#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_256                         r_rsip_wrapper_p34i_aes256gcm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_INIT_256_WRAPPED_IV              r_rsip_wrapper_p34i_aes256gcm_encrypt_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_AAD_256                   r_rsip_p34a
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_TRANSITION_256            r_rsip_p34t
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_UPDATE_256                       r_rsip_p34u
#define RSIP_PRV_FUNC_NAME_AES_GCM_ENC_FINAL_256                        r_rsip_p34f
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_256                         r_rsip_wrapper_p36i_aes256gcm_decrypt
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_INIT_256_WRAPPED_IV              r_rsip_wrapper_p36i_aes256gcm_decrypt_wrapped_iv
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_AAD_256                   r_rsip_p36a
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_TRANSITION_256            r_rsip_p36t
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_UPDATE_256                       r_rsip_p36u
#define RSIP_PRV_FUNC_NAME_AES_GCM_DEC_FINAL_256                        r_rsip_p36f

#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_INIT_256                         r_rsip_wrapper_pa1i_aes256ccm_encrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_UPDATE_256                       r_rsip_pa1u
#define RSIP_PRV_FUNC_NAME_AES_CCM_ENC_FINAL_256                        r_rsip_pa1f
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_INIT_256                         r_rsip_wrapper_pa4i_aes256ccm_decrypt
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_UPDATE_256                       r_rsip_pa4u
#define RSIP_PRV_FUNC_NAME_AES_CCM_DEC_FINAL_256                        r_rsip_pa4f

#define RSIP_PRV_FUNC_NAME_AES_CMAC_INIT_256                            r_rsip_wrapper_p44i_aes256mac
#define RSIP_PRV_FUNC_NAME_AES_CMAC_UPDATE_256                          r_rsip_p44u
#define RSIP_PRV_FUNC_NAME_AES_CMAC_GENERATE_FINAL_256                  r_rsip_wrapper_p44f_aes256mac_generate
#define RSIP_PRV_FUNC_NAME_AES_CMAC_VERIFY_FINAL_256                    r_rsip_wrapper_p44f_aes256mac_verify

// #define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_XTS_AES_128                  r_rsip_wrapper_p6f_aes128xts
// #define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_XTS_AES_256                  r_rsip_wrapper_p6f_aes256xts
#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP256R1              r_rsip_wrapper_pf4_secp256r1
#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_BRAINPOOLP256R1        r_rsip_wrapper_pf4_brainpoolp256r1
#define RSIP_PRV_FUNC_NAME_KEY_PAIR_GENERATE_ECC_SECP256K1              r_rsip_wrapper_pf4_secp256k1

#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PUBLIC            r_rsip_wrapper_p6f_secp256r1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256R1_PRIVATE           r_rsip_wrapper_p6f_secp256r1_priv
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_BRAINPOOLP256R1_PUBLIC      r_rsip_wrapper_p6f_brainpoolp256r1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_BRAINPOOLP256R1_PRIVATE     r_rsip_wrapper_p6f_brainpoolp256r1_priv
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256K1_PUBLIC            r_rsip_wrapper_p6f_secp256k1_pub
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_ECC_SECP256K1_PRIVATE           r_rsip_wrapper_p6f_secp256k1_priv
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_SECP256R1_PUBLIC           r_rsip_p6e_secp256r1_pub
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_SECP256R1_PRIVATE          r_rsip_p6e_secp256r1_priv
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PUBLIC     r_rsip_p6e_brainpool256r1_pub
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PRIVATE    r_rsip_p6e_brainpool256r1_priv
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_SECP256K1_PUBLIC           r_rsip_p6e_eccsecp256k1_public
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_SECP256K1_PRIVATE          r_rsip_p6e_secp256k1_priv

#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP256R1                         r_rsip_wrapper_pf0_secp256r1
#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_BRAINPOOLP256R1                   r_rsip_wrapper_pf0_brainpoolp256r1
#define RSIP_PRV_FUNC_NAME_ECDSA_SIGN_SECP256K1                         r_rsip_wrapper_pf0_secp256k1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP256R1                       r_rsip_wrapper_pf1_secp256r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_BRAINPOOLP256R1                 r_rsip_wrapper_pf1_brainpoolp256r1
#define RSIP_PRV_FUNC_NAME_ECDSA_VERIFY_SECP256K1                       r_rsip_wrapper_pf1_secp256k1

#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA224                     r_rsip_p0a
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA224                     r_rsip_wrapper_p6f_hmacsha224
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_HMAC_SHA224                    r_rsip_p6e_hmacsha224
#define RSIP_PRV_FUNC_NAME_KEY_GENERATE_HMAC_SHA256                     r_rsip_p0b
#define RSIP_PRV_FUNC_NAME_ENC_KEY_WRAP_HMAC_SHA256                     r_rsip_wrapper_p6f_hmacsha256
#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_HMAC_SHA256                    r_rsip_p6e_hmacsha256
#define RSIP_PRV_FUNC_NAME_RANDOM_NUMBER_GENERATE                       r_rsip_p20

#define RSIP_PRV_FUNC_NAME_ECDH_WRAPPED_SECP256R1                       r_rsip_wrapper_pe2_wrapped
#define RSIP_PRV_FUNC_NAME_ECDH_PLAIN_SECP256R1                         r_rsip_wrapper_pe2_plain

#define RSIP_PRV_FUNC_NAME_PKI_ECDSA_VERIFY_INIT_SECP256R1              r_rsip_wrapper_peei
#define RSIP_PRV_FUNC_NAME_PKI_ECDSA_VERIFY_FINAL_SECP256R1             r_rsip_peef
#define RSIP_PRV_FUNC_NAME_PKI_CERT_KEY_IMPORT_ECC_SECP256R1            r_rsip_wrapper_pe1_secp256r1

#define RSIP_PRV_FUNC_NAME_KDF_SHA_ECDH_SECRET_MSG_WRAP_SHA256          r_rsip_pe3
#define RSIP_PRV_FUNC_NAME_KDF_SHA_DERIVED_KEY_IMPORT_SHA256_AES_128    r_rsip_wrapper_pe7_sha256_aes128
#define RSIP_PRV_FUNC_NAME_KDF_SHA_DERIVED_KEY_IMPORT_SHA256_AES_256    r_rsip_wrapper_pe7_sha256_aes256
#define RSIP_PRV_FUNC_NAME_KDF_SHA_DERIVED_IV_WRAP_SHA256_AES           r_rsip_wrapper_pe7_sha256_iv_aes

#define RSIP_PRV_FUNC_NAME_KDF_ECDH_SECRET_KEY_IMPORT_SHA256            NULL
#define RSIP_PRV_FUNC_NAME_KDF_ECDH_SECRET_MSG_WRAP_SHA256              NULL
#define RSIP_PRV_FUNC_NAME_KDF_MAC_KEY_IMPORT_SHA256                    NULL
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_KEY_IMPORT_SHA256_AES_128        NULL
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_KEY_IMPORT_SHA256_AES_256        NULL
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_KEY_IMPORT_SHA256_HMAC_SHA256    NULL
#define RSIP_PRV_FUNC_NAME_KDF_DERIVED_IV_WRAP_SHA256_AES               NULL

#define RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_KUK                            r_rsip_p6e_aes256_KUK

/* Key update inst data word */
#define RSIP_OEM_KEY_SIZE_DUMMY_INST_DATA_WORD                        (0)
#define RSIP_OEM_KEY_SIZE_AES128_INST_DATA_WORD                       (8)
#define RSIP_OEM_KEY_SIZE_AES256_INST_DATA_WORD                       (12)
#define RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD     (20)
#define RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD    (12)
#define RSIP_OEM_KEY_SIZE_HMAC_SHA256_KEY_INST_DATA_WORD              (12)

/* Wrap Key type and size word */
#define RSIP_KEY_INDEX_SIZE_AES128_WORD                       (9)
#define RSIP_WRAPPED_KEY_SIZE_AES128_WORD                     (6)
#define RSIP_KEY_INDEX_SIZE_AES256_WORD                       (13)
#define RSIP_WRAPPED_KEY_SIZE_AES256_WORD                     (10)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_rsip_ecc_curve_type
{
    RSIP_ECC_CURVE_TYPE_NIST,
    RSIP_ECC_CURVE_TYPE_Brainpool,
    RSIP_ECC_CURVE_TYPE_Koblitz
} rsip_ecc_type_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
rsip_ret_t r_rsip_wrapper_pf0_secp256r1 (const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf0_brainpoolp256r1 (const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf0_secp256k1 (const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf1_secp256r1 (const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf1_brainpoolp256r1 (const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf1_secp256k1 (const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[]);
rsip_ret_t r_rsip_wrapper_pf4_secp256r1 (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_pf4_brainpoolp256r1 (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_wrapper_pf4_secp256k1 (uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_p6e_aes128 (const uint32_t   InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_aes256 (const uint32_t   InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_secp256r1_pub (const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_secp256r1_priv (const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_brainpool256r1_pub (const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_brainpool256r1_priv (const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_eccsecp256k1_public (const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_secp256k1_priv (const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_hmacsha224 (const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_hmacsha256 (const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_p6e_aes256_KUK (const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_aes128 (const uint32_t InData_IV[],
                                    const uint32_t InData_InstData[],
                                    uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_aes256 (const uint32_t InData_IV[],
                                    const uint32_t InData_InstData[],
                                    uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp256r1_pub (const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp256r1_priv (const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_hmacsha224 (const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_hmacsha256 (const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_brainpoolp256r1_pub (const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_brainpoolp256r1_priv (const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp256k1_pub (const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p6f_secp256k1_priv (const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_p8f_aes128 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_WrappedKeyIndex[],
                                      uint32_t       OutData_Text[],
                                      uint32_t       KEY_INDEX_SIZE,
                                      uint32_t       WRAPPED_KEY_SIZE);
rsip_ret_t r_rsip_wrapper_p8f_aes256 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_WrappedKeyIndex[],
                                      uint32_t       OutData_Text[],
                                      uint32_t       KEY_INDEX_SIZE,
                                      uint32_t       WRAPPED_KEY_SIZE);
rsip_ret_t r_rsip_wrapper_p90_aes128 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_Text[],
                                      uint32_t       OutData_KeyIndex[],
                                      uint32_t       WRAPPED_KEY_SIZE,
                                      uint32_t       KEY_INDEX_SIZE);
rsip_ret_t r_rsip_wrapper_p90_aes256 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_Text[],
                                      uint32_t       OutData_KeyIndex[],
                                      uint32_t       WRAPPED_KEY_SIZE,
                                      uint32_t       KEY_INDEX_SIZE);

/* AES-ECB/CBC/CTR */
rsip_ret_t r_rsip_wrapper_p47i_aes128ecb_encrypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128ecb_decrypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_encrypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_encrypt_wrapped_iv (const uint32_t InData_KeyIndex[],
                                                            const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_decrypt_wrapped_iv (const uint32_t InData_KeyIndex[],
                                                            const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_decrypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p47i_aes128ctr_crypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256ecb_encrypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256ecb_decrypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_encrypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_encrypt_wrapped_iv (const uint32_t InData_KeyIndex[],
                                                            const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_decrypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_decrypt_wrapped_iv (const uint32_t InData_KeyIndex[],
                                                            const uint32_t InData_IV[]);
rsip_ret_t r_rsip_wrapper_p50i_aes256ctr_crypt (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[]);

/* AES-GCM */
rsip_ret_t r_rsip_wrapper_p29i_aes128gcm_encrypt (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p29i_aes128gcm_encrypt_wrapped_iv (const uint32_t * InData_KeyIndex,
                                                            const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p32i_aes128gcm_decrypt (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p32i_aes128gcm_decrypt_wrapped_iv (const uint32_t * InData_KeyIndex,
                                                            const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p34i_aes256gcm_encrypt (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p34i_aes256gcm_encrypt_wrapped_iv (const uint32_t * InData_KeyIndex,
                                                            const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p36i_aes256gcm_decrypt (const uint32_t * InData_KeyIndex, const uint32_t * InData_IV);
rsip_ret_t r_rsip_wrapper_p36i_aes256gcm_decrypt_wrapped_iv (const uint32_t * InData_KeyIndex,
                                                            const uint32_t * InData_IV);

/* AES-CCM */
rsip_ret_t r_rsip_wrapper_p95i_aes128ccm_encrypt (const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_TextLen,
                                                const uint32_t * InData_IV,
                                                const uint32_t * InData_Header,
                                                uint32_t         Header_Len);
rsip_ret_t r_rsip_wrapper_p95f_aes128ccm_encrypt (const uint32_t * InData_Text,
                                                const uint32_t * InData_TextLen,
                                                uint32_t       * OutData_Text,
                                                uint32_t       * OutData_MAC);
rsip_ret_t r_rsip_wrapper_p98i_aes128ccm_decrypt (const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_TextLen,
                                                const uint32_t * InData_MACLength,
                                                const uint32_t * InData_IV,
                                                const uint32_t * InData_Header,
                                                uint32_t         Header_Len);
rsip_ret_t r_rsip_wrapper_p98f_aes128ccm_decrypt (const uint32_t * InData_Text,
                                                const uint32_t * InData_TextLen,
                                                const uint32_t * InData_MAC,
                                                const uint32_t * InData_MACLength,
                                                uint32_t       * OutData_Text);

rsip_ret_t r_rsip_wrapper_pa1i_aes256ccm_encrypt (const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_TextLen,
                                                const uint32_t * InData_IV,
                                                const uint32_t * InData_Header,
                                                uint32_t         Header_Len);
rsip_ret_t r_rsip_wrapper_pa4i_aes256ccm_decrypt (const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_TextLen,
                                                const uint32_t * InData_MACLength,
                                                const uint32_t * InData_IV,
                                                const uint32_t * InData_Header,
                                                uint32_t         Header_Len);

/* AES-MAC */
rsip_ret_t r_rsip_wrapper_p41i_aes128mac (const uint32_t * InData_KeyIndex);
rsip_ret_t r_rsip_wrapper_p41f_aes128mac_generate (const uint32_t * InData_Text,
                                                    uint32_t       * OutData_DataT,
                                                    const uint32_t   all_msg_len);
rsip_ret_t r_rsip_wrapper_p41f_aes128mac_verify (const uint32_t * InData_Text,
                                                const uint32_t * InData_DataT,
                                                const uint32_t * InData_DataTLen,
                                                const uint32_t   all_msg_len);
rsip_ret_t r_rsip_wrapper_p44i_aes256mac (const uint32_t * InData_KeyIndex);
rsip_ret_t r_rsip_wrapper_p44f_aes256mac_generate (const uint32_t * InData_Text,
                                                    uint32_t       * OutData_DataT,
                                                    const uint32_t   all_msg_len);
rsip_ret_t r_rsip_wrapper_p44f_aes256mac_verify (const uint32_t * InData_Text,
                                                const uint32_t * InData_DataT,
                                                const uint32_t * InData_DataTLen,
                                                const uint32_t   all_msg_len);

/* ECDH */
rsip_ret_t r_rsip_wrapper_pe2_wrapped(const uint32_t InData_PubKey[],
                                      const uint32_t InData_KeyIndex[],
                                      uint32_t       OutData_EncSecret[]);

rsip_ret_t r_rsip_wrapper_pe2_plain(const uint32_t InData_PubKey[],
                                    const uint32_t InData_KeyIndex[],
                                    uint32_t       OutData_EncSecret[]);

/* PKI */
rsip_ret_t r_rsip_wrapper_peei(const uint32_t InData_KeyIndex[],
                               const uint32_t InData_MsgDgst[],
                               const uint32_t InData_Signature[]);

rsip_ret_t r_rsip_wrapper_pe1_secp256r1(const uint32_t InData_HashType[],
                                        const uint32_t InData_Certificate[],
                                        const uint32_t InData_CertificateLength[],
                                        const uint32_t InData_CertificatePubKey[],
                                        const uint32_t InData_EncCertificateInfo[],
                                        uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_aes128(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_aes256(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            uint32_t       OutData_KeyIndex[]);
rsip_ret_t r_rsip_wrapper_pe7_sha256_iv_aes(const uint32_t InData_KDFInfo[],
                                            const uint32_t InData_KDFInfo_Count[],
                                            const uint32_t InData_OutDataLocation[],
                                            const uint32_t InData_SeqNum[],
                                            uint32_t       OutData_EncIV[]);

/* FWUP */
rsip_ret_t r_rsip_fwup_start(void);

#endif                                 /* R_RSIP_WRAPPER_H */
