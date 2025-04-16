/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2017-2018 Linaro LTD
 * Copyright (c) 2017-2019 JUUL Labs
 * Copyright (c) 2020 Arm Limited
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
 * File Name    : tsip_image_rsa.c
 * Version      : 1.0
 * Description  : This module implements functions used for RSA signature verification.
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

#include "tsip_keys.h"
#if defined (MCUBOOT_SIGN_RSA)
#if defined (MCUBOOT_USE_TSIP)
#include "bootutil/sign_key.h"

#include "bootutil_priv.h"
#include "bootutil/fault_injection_hardening.h"

/**********************************************************************************************************************
* Function Name: tsip_bootutil_cmp_rsasig
* Description  : Validate an RSA signature, using RSA-PSS.
* Arguments    : uint8_t * p_pub_key -
*                    Pointer to public key
*                uint8_t * p_hash -
*                    Pointer to hash value
*                uint32_t hlen -
*                    Hash value length
*                uint8_t * p_sig -
*                    Pointer to signature
* Return Value : FIH_SUCCESS -
*                    Success
*                FIH_FAILURE -
*                    Failure
**********************************************************************************************************************/
static fih_int tsip_bootutil_cmp_rsasig(uint8_t * p_pub_key, uint8_t * p_hash, uint32_t hlen, uint8_t * p_sig)
{
    e_tsip_err_t tsip_err = TSIP_SUCCESS;
    tsip_rsa_byte_data_t local_sig;
    tsip_rsa_byte_data_t local_hash;
    tsip_rsa2048_public_key_index_t rsa_public_key_installed;

    /* Set to data type used by TSIP. The other fields are not used by the driver. */

    local_sig.pdata = p_sig;
    local_sig.data_length = RM_MCUBOOT_PORT_BITS_TO_BYTES(MCUBOOT_SIGN_RSA_LEN);

    local_hash.data_length = hlen;
    local_hash.data_type = 1; // 1 indicates that the data is a hash; 0 indicates that the data is to be hashed
    local_hash.pdata = p_hash;

    rsa_public_key_installed.type = TSIP_KEY_INDEX_TYPE_RSA2048_PUBLIC;
    memcpy((uint8_t *) &rsa_public_key_installed.value, p_pub_key, sizeof(rsa_public_key_installed.value));

    tsip_err = R_TSIP_RsassaPss2048SignatureVerification(&local_sig, &local_hash, &rsa_public_key_installed,
                                                            R_TSIP_RSA_HASH_SHA256);

    if (tsip_err != TSIP_SUCCESS)
    {
        return FIH_FAILURE;
    }

    return FIH_SUCCESS;
}
/**********************************************************************************************************************
* End of function
**********************************************************************************************************************/


/**********************************************************************************************************************
* Function Name: bootutil_verify_sig
* Description  : Execute RSA signature verification.
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
* Return Value : FIH_SUCCESS -
*                    Success
*                FIH_FAILURE -
*                    Failure
**********************************************************************************************************************/
fih_int bootutil_verify_sig(uint8_t * p_hash, uint32_t hlen, uint8_t * p_sig, size_t slen,
                    uint8_t key_id)
{
    fih_int fih_rc = FIH_FAILURE;
    uint8_t * p_pubkey;

    if (slen != RM_MCUBOOT_PORT_BITS_TO_BYTES(MCUBOOT_SIGN_RSA_LEN))
    {
        goto out;
    }

    /** Returns -1 if the wrapped public key address is not set in the configuration. */
    if(g_bootutil_keys_wrapped[key_id].key == NULL)
    {
        return -1;
    }
    p_pubkey = (uint8_t *) g_bootutil_keys_wrapped[key_id].key;
    FIH_CALL(tsip_bootutil_cmp_rsasig, fih_rc, p_pubkey, p_hash, hlen, p_sig);

out:
    FIH_RET(fih_rc);
}
/**********************************************************************************************************************
* End of function
**********************************************************************************************************************/

#endif /* MCUBOOT_USE_TSIP */
#endif /* MCUBOOT_SIGN_RSA */
