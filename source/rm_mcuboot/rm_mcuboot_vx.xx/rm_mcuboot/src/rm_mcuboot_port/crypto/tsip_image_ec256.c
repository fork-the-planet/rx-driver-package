/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2016-2019 JUUL Labs
 * Copyright (c) 2017 Linaro LTD
 *
 * Original license:
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
/**********************************************************************************************************************
 * File Name    : tsip_image_ec256.c
 * Version      : 1.0
 * Description  : This module implements some of the functions used for ECDSA signature verification.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *           30.06.2025 1.01    Added support for RX66N, RX72M and RX671
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <string.h>

#include "mcuboot_config/mcuboot_config.h"
#include "tsip_keys.h"

#if defined (MCUBOOT_SIGN_EC256)
#if defined (MCUBOOT_USE_TSIP)
#include "mbedtls/build_info.h"
#include "bootutil/sign_key.h"

#include "mbedtls/oid.h"
#include "mbedtls/asn1.h"
#include "bootutil_priv.h"

/**
 * Declaring these like this adds NULL termination.
 */
/* Read public key information from ASN1 format. */
static const uint8_t ec_pubkey_oid[] = MBEDTLS_OID_EC_ALG_UNRESTRICTED;
/* Read the elliptic curve information from ASN1 format. */
static const uint8_t ec_secp256r1_oid[] = MBEDTLS_OID_EC_GRP_SECP256R1;

/**********************************************************************************************************************
* Function Name: bootutil_ecdsa_verify
* Description  : Executes ECDSA signature verification with a key length of 256 bits.
* Arguments    : bootutil_ecdsa_context_t * p_ctx -
*                    Context used for signature verification
*                const uint8_t * p_pk -
*                    Pointer to public key
*                const uint8_t * p_hash -
*                    Pointer to hash value
*                const uint8_t * p_sig -
*                    Pointer to signature
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
static inline int32_t bootutil_ecdsa_verify (bootutil_ecdsa_context_t * p_ctx, const uint8_t * p_pk,
                                                const uint8_t * p_hash, const uint8_t * p_sig)
{
    (void) p_ctx;
    e_tsip_err_t tsip_err = TSIP_SUCCESS;
    tsip_ecdsa_byte_data_t local_sig;
    tsip_ecdsa_byte_data_t local_hash;
    tsip_ecc_public_key_index_t ecc_public_key_installed;

    /* Set to data type used by TSIP. The other fields are not used by the driver. */

    local_sig.pdata       = (uint8_t *) p_sig;
    local_sig.data_length = BOOTUTIL_CRYPTO_ECDSA_P256_SIGNATURE_SIZE_BYTES;

    local_hash.data_length = BOOTUTIL_CRYPTO_SHA256_DIGEST_SIZE_BYTES;
    local_hash.data_type   = 1; // 1 indicates that the data is a hash; 0 indicates that the data is to be hashed
    local_hash.pdata       = (uint8_t *) p_hash;

    memcpy((uint8_t *) &ecc_public_key_installed.value, (uint8_t *) p_pk, sizeof(ecc_public_key_installed.value));

    ecc_public_key_installed.type = TSIP_KEY_INDEX_TYPE_ECC_P256_PUBLIC;

    tsip_err = R_TSIP_EcdsaP256SignatureVerification(&local_sig, &local_hash, &ecc_public_key_installed);

    if (tsip_err != TSIP_SUCCESS)
    {
        return -1;
    }

    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_ecdsa_verify (bootutil_ecdsa_context_t * p_ctx, const uint8_t * p_pk,
                                                const uint8_t * p_hash, const uint8_t * p_sig)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_import_key
* Description  : Parse the public key used for signing.
* Arguments    : uint8_t **pp_cp -
*                    Pointer to pointer to public key data
*                uint8_t *p_end -
*                    Pointer to the end address of the public key
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
static int32_t bootutil_import_key(uint8_t **pp_cp, uint8_t *p_end)
{
    size_t len;
    mbedtls_asn1_buf alg;
    mbedtls_asn1_buf param;

    if (mbedtls_asn1_get_tag(pp_cp, p_end, &len,
        MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE))
    {
        return -1;
    }
    p_end = (*pp_cp) + len;

    /* ECParameters (RFC5480) */
    if (mbedtls_asn1_get_alg(pp_cp, p_end, &alg, &param))
    {
        return -1;
    }
    /* id-ecPublicKey (RFC5480) */
    if ((alg.len != ((sizeof(ec_pubkey_oid)) - 1)) ||
        memcmp(alg.p, ec_pubkey_oid, (sizeof(ec_pubkey_oid)) - 1))
    {
        return -1;
    }
    /* namedCurve (RFC5480) */
    if ((param.len != ((sizeof(ec_secp256r1_oid)) - 1)) ||
        memcmp(param.p, ec_secp256r1_oid, (sizeof(ec_secp256r1_oid)) - 1))
    {
        return -1;
    }
    /* ECPoint (RFC5480) */
    if (mbedtls_asn1_get_bitstring_null(pp_cp, p_end, &len))
    {
        return -1;
    }
    if (((*pp_cp) + len) != p_end)
    {
        return -1;
    }

    if (len != ((2 * NUM_ECC_BYTES) + (1)))
    {
        return -1;
    }
    /* Is uncompressed? */
    if ((*pp_cp[0]) != 0x04)
    {
        return -1;
    }

    (*pp_cp)++;

    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_import_key(uint8_t **pp_cp, uint8_t *p_end)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_read_bigint
* Description  : cp points to ASN1 string containing an integer.
*                Verify the tag, and that the length is 32 bytes.
* Arguments    : uint8_t i[NUM_ECC_BYTES] -
*                    Buffer that holds read signature data
*                uint8_t **pp_cp -
*                    Pointer to pointer to ASN1 string containing integer
*                uint8_t *p_end -
*                    Pointer to the end address of ASN1 string
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
static int32_t bootutil_read_bigint(uint8_t i[NUM_ECC_BYTES], uint8_t **pp_cp, uint8_t *p_end)
{
    size_t len;

    if (mbedtls_asn1_get_tag(pp_cp, p_end, &len, MBEDTLS_ASN1_INTEGER))
    {
        return -1;
    }

    if (len >= NUM_ECC_BYTES)
    {
        memcpy(i, ((*pp_cp) + len) - NUM_ECC_BYTES, NUM_ECC_BYTES);
    }
    else
    {
        memset(i, 0, NUM_ECC_BYTES - len);
        memcpy((i + (NUM_ECC_BYTES - len)), *pp_cp, len);
    }
    (*pp_cp) += len;
    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_read_bigint(uint8_t i[NUM_ECC_BYTES], uint8_t **pp_cp, uint8_t *p_end)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_decode_sig
* Description  : Read in signature. Signature has r and s encoded as integers.
* Arguments    : uint8_t signature[NUM_ECC_BYTES * 2] -
*                    Local signature data
*                uint8_t *p_cp
*                    Pointer to signature
*                uint8_t *p_end
*                    Pointer to the ending address of the signature
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
static int32_t bootutil_decode_sig(uint8_t signature[NUM_ECC_BYTES * 2], uint8_t *p_cp, uint8_t *p_end)
{
    int32_t rc;
    size_t len;

    rc = mbedtls_asn1_get_tag(&p_cp, p_end, &len,
        MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE);
    if (rc)
    {
        return -1;
    }
    if ((p_cp + len) > p_end)
    {
        return -1;
    }

    rc = bootutil_read_bigint(signature, &p_cp, p_end);
    if (rc)
    {
        return -1;
    }
    rc = bootutil_read_bigint(signature + NUM_ECC_BYTES, &p_cp, p_end);
    if (rc)
    {
        return -1;
    }
    return 0;
}
/**********************************************************************************************************************
* End of function bootutil_decode_sig(uint8_t signature[NUM_ECC_BYTES * 2], uint8_t *p_cp, uint8_t *p_end)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: bootutil_verify_sig
* Description  : Perform signature verification.
* Arguments    : uint8_t *p_hash -
*                    Pointer to hash value
*                uint32_t hlen -
*                    Hash value length
*                uint8_t *p_sig -
*                    Pointer to signature
*                size_t slen -
*                    Signature length
*                uint8_t key_id -
*                    Public key ID
* Return Value :  0 - Success
*                -1 - Failure
**********************************************************************************************************************/
fih_ret bootutil_verify_sig(uint8_t *p_hash, uint32_t hlen, uint8_t *p_sig, size_t slen, uint8_t key_id)
{
    int32_t rc;
    bootutil_ecdsa_context_t ctx;
    uint8_t *p_pubkey;
    uint8_t *p_end;

    uint8_t signature[2 * NUM_ECC_BYTES];
    tsip_ecc_public_key_index_t public_key_installed;

    /* If the DER format public key address is not set in the configuration, -1 is returned. */
    if ((bootutil_keys[key_id].key == NULL) || (bootutil_keys[key_id].len == NULL))
    {
        return -1;
    }
    p_pubkey = (uint8_t *)bootutil_keys[key_id].key;
    p_end = p_pubkey + (*bootutil_keys[key_id].len);

    rc = bootutil_import_key(&p_pubkey, p_end);
    if (rc)
    {
        return -1;
    }

    rc = bootutil_decode_sig(signature, p_sig, p_sig + slen);
    if (rc)
    {
        return -1;
    }

    /* The key_id passed to this function is for a key from bootutil_keys[] and
     * its hash has already been validated. Since the imgtool.py does not handle
     * the hash for the wrapped public key, we compare the public key portion of
     * the wrappedkey from bootutil_keys_wrapped[] with the key from
     * bootutil_keys[] and if both are the same, then we use the key from
     * bootutil_keys_wrapped[] to perform the verification using the protected
     * mode procedures. */
    /** Returns -1 if the wrapped public key address is not set in the configuration. */
    if(g_bootutil_keys_wrapped[key_id].key == NULL)
    {
        return -1;
    }
    memcpy((uint8_t *) &public_key_installed.value,
            (uint8_t *) g_bootutil_keys_wrapped[key_id].key,
            sizeof(public_key_installed.value));
    if (memcmp (&public_key_installed.value.key_q, p_pubkey, 2 * NUM_ECC_BYTES))
    {
        return -1;
    }

    /* This is simplified, as the hash length is also 32 bytes. */
    if (hlen != NUM_ECC_BYTES)
    {
        return -1;
    }

    bootutil_ecdsa_init(&ctx);

    rc = bootutil_ecdsa_verify(&ctx, (uint8_t *)&public_key_installed.value, p_hash, signature);
    bootutil_ecdsa_drop(&ctx);

    return rc;
}
/**********************************************************************************************************************
* End of function bootutil_verify_sig(uint8_t *p_hash, uint32_t hlen, uint8_t *p_sig, size_t slen, uint8_t key_id)
**********************************************************************************************************************/

#endif /* MCUBOOT_USE_TSIP */

#endif /* MCUBOOT_SIGN_EC256 */
