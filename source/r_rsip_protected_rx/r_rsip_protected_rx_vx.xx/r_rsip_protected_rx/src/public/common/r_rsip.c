/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_rsip.c
* Description  : Interface definition for the r_rsip RSIP module.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.10.2024 1.00     First Release.
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_protected_rx_if.h"
#include "r_rsip_public.h"
#include "r_rsip_private.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static rsip_func_key_generate_t       select_func_key_generate (rsip_key_type_t key_type);
static rsip_func_key_pair_generate_t  select_func_key_pair_generate (rsip_key_pair_type_t key_pair_type);
static rsip_func_encrypted_key_wrap_t select_func_encrypted_key_wrap (rsip_key_type_t key_type);
static uint32_t                       get_wrapped_key_size (rsip_key_type_t key_type);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static const uint32_t gs_ecc_param1_pos[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QX,
    [RSIP_KEY_ECC_SECP256K1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QX,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QX,
};

static const uint32_t gs_ecc_param1_len[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_SECP256K1]       = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
};

static const uint32_t gs_ecc_param2_pos[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QY,
    [RSIP_KEY_ECC_SECP256K1]       = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QY,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_CFG_BYTE_POS_WRAPPED_PUBLIC_KEY_ECC_256_QY,
};

static const uint32_t gs_ecc_param2_len[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1]       = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_SECP256K1]       = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_PRV_BYTE_SIZE_ECC_256_PARAM,
};

RSIP_SEC_C_SECURE_BOOT
static const uint32_t gs_wrapped_key_value_len_aes[RSIP_KEY_AES_NUM] =
{
    [RSIP_KEY_AES_128] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_AES_128,
    [RSIP_KEY_AES_256] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_AES_256,
};
RSIP_SEC_DEFAULT

static const uint32_t gs_wrapped_key_value_len_ecc_pub[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_ECC_SECP256R1_PUBLIC,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_ECC_BRAINPOOLP256R1_PUBLIC,
    [RSIP_KEY_ECC_SECP256K1] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_ECC_SECP256K1_PUBLIC,
};

static const uint32_t gs_wrapped_key_value_len_ecc_priv[RSIP_KEY_ECC_NUM] =
{
    [RSIP_KEY_ECC_SECP256R1] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_ECC_SECP256R1_PRIVATE,
    [RSIP_KEY_ECC_BRAINPOOLP256R1] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_ECC_BRAINPOOLP256R1_PRIVATE,
    [RSIP_KEY_ECC_SECP256K1] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_ECC_SECP256K1_PRIVATE,
};

static const uint32_t gs_wrapped_key_value_len_hmac[RSIP_KEY_HMAC_NUM] =
{
    [RSIP_KEY_HMAC_SHA224] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_HMAC_SHA224,
    [RSIP_KEY_HMAC_SHA256] = RSIP_CFG_BYTE_SIZE_WRAPPED_KEY_VALUE_HMAC_SHA256,
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

const rsip_api_t g_rsip_on_rsip =
{
    .open                    = R_RSIP_Open,
    .close                   = R_RSIP_Close,
    .getversion              = R_RSIP_GetVersion,
    .randomNumberGenerate    = R_RSIP_RandomNumberGenerate,
    .keyGenerate             = R_RSIP_KeyGenerate,
    .keyPairGenerate         = R_RSIP_KeyPairGenerate,
    .encryptedKeyWrap        = R_RSIP_EncryptedKeyWrap,
    .rfc3394_KeyWrap         = R_RSIP_RFC3394_KeyWrap,
    .rfc3394_KeyUnwrap       = R_RSIP_RFC3394_KeyUnwrap,
    .injectedKeyImport       = R_RSIP_InjectedKeyImport,
    .publicKeyExport         = R_RSIP_PublicKeyExport,
    .initialKeyWrap          = R_RSIP_InitialKeyWrap,
    .initialKeyUpdateKeyWrap = R_RSIP_InitialKeyUpdateKeyWrap,
    .aesCipherInit           = R_RSIP_AES_Cipher_Init,
    .aesCipherUpdate         = R_RSIP_AES_Cipher_Update,
    .aesCipherFinish         = R_RSIP_AES_Cipher_Finish,
    .aesAeadInit             = R_RSIP_AES_AEAD_Init,
    .aesAeadLengthsSet       = R_RSIP_AES_AEAD_LengthsSet,
    .aesAeadAadUpdate        = R_RSIP_AES_AEAD_AADUpdate,
    .aesAeadUpdate           = R_RSIP_AES_AEAD_Update,
    .aesAeadFinish           = R_RSIP_AES_AEAD_Finish,
    .aesAeadVerify           = R_RSIP_AES_AEAD_Verify,
    .aesMacInit              = R_RSIP_AES_MAC_Init,
    .aesMacUpdate            = R_RSIP_AES_MAC_Update,
    .aesMacSignFinish        = R_RSIP_AES_MAC_SignFinish,
    .aesMacVerifyFinish      = R_RSIP_AES_MAC_VerifyFinish,
    .ecdsaSign               = R_RSIP_ECDSA_Sign,
    .ecdsaVerify             = R_RSIP_ECDSA_Verify,
    .shaInit                 = R_RSIP_SHA_Init,
    .shaUpdate               = R_RSIP_SHA_Update,
    .shaFinish               = R_RSIP_SHA_Finish,
    .hmacInit                = R_RSIP_HMAC_Init,
    .hmacUpdate              = R_RSIP_HMAC_Update,
    .hmacSignFinish          = R_RSIP_HMAC_SignFinish,
    .hmacVerifyFinish        = R_RSIP_HMAC_VerifyFinish
};

/*******************************************************************************************************************//**
 * @addtogroup RSIP_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

RSIP_SEC_P_SECURE_BOOT
/*******************************************************************************************************************//**
 * Enables use of Renesas Secure IP functionality.<br>
 * Implements @ref rsip_api_t::open.
 * 
 * \<Operational State><br>
 * This API can only be executed in the STATE_INITIAL,
 * and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal1"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_SUCCESS<td>STATE_MAIN</td>
 * <tr><td>Others<td>No change</td>
 * </table>
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_ALREADY_OPEN                  Module is already open.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Internal key value is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Hardware initialization is failed.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption or hardware fault is detected.
 *
 * @note  This version does not have an optional feature to disable TRNG initialization.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_Open(rsip_ctrl_t * const p_ctrl, rsip_cfg_t const * const p_cfg)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);
    FSP_ERROR_RETURN(RSIP_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    /* Set configuration */
    p_instance_ctrl->p_cfg = p_cfg;

    /* Device-specific sequence */
    rsip_err_t rsip_ret = r_rsip_open();

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            /* Reset handle */
            r_rsip_handle_reset(&p_instance_ctrl->handle);

            /* State transition */
            p_instance_ctrl->state = RSIP_STATE_MAIN;

            /* Set driver status to open */
            p_instance_ctrl->open = RSIP_OPEN;

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_ERR_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_ERR_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        /* Treat RETRY as FATAL */
        case RSIP_ERR_RETRY:
        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

RSIP_SEC_P_SECURE_BOOT
/*******************************************************************************************************************//**
 * Disables use of Renesas Secure IP functionality.<br>
 * Implements @ref rsip_api_t::close.
 *
 * \<Operational State><br>
 * This API can be executed in except STATE_INITIAL,
 * and the state after execution changes as follows depending on the return value.
 * <table>
 * <caption id="RetVal2"> </caption>
 * <tr><th>Return Value<th>State after execution</tr>
 * <tr><td>FSP_SUCCESS<td>STATE_INITIAL</td>
 * <tr><td>Others<td>No change</td>
 * </table>
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_Close(rsip_ctrl_t * const p_ctrl)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Device-specific sequence */
    rsip_err_t rsip_ret = r_rsip_close();

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            /* Set driver status to close */
            p_instance_ctrl->open = 0U;

            err = FSP_SUCCESS;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}
RSIP_SEC_DEFAULT

/*******************************************************************************************************************//**
 * Returns the version of this module. <br>
 * The version number is encoded such that the top two bytes are the
 * major version number and the bottom two bytes are the minor version number.
 * Implements @ref rsip_api_t::getversion.
 *
 * \<Operational State><br>
 * This API can be executed in any state including STATE_INITIAL, and there are no state transitions.
 *
 * @retval        Version number
 **********************************************************************************************************************/
uint32_t R_RSIP_GetVersion(void)
{
    return ((RSIP_VERSION_MAJOR << 16u) | RSIP_VERSION_MINOR);
}

/*******************************************************************************************************************//**
 * Generates a 128-bit random number.<br>
 * Implements @ref rsip_api_t::randomNumberGenerate.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RandomNumberGenerate(rsip_ctrl_t * const p_ctrl, uint8_t * const p_random)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_random);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    return r_rsip_random_number_generate(p_ctrl, p_random);
}

/*******************************************************************************************************************//**
 * Generate a wrapped symmetric key from a random number.
 * In this API, user key input is unnecessary.
 * By encrypting data using the wrapped key is output by this API, dead copying of data can be prevented.<br>
 * Implements @ref rsip_api_t::keyGenerate.
 *
 * \<Usage Precautions>
 * @arg Valid key types.
 *
 * <table>
 * <caption id="key_type"> </caption>
 * <tr><th>key_type<td>RSIP_KEY_TYPE_AES_128<br>
 * RSIP_KEY_TYPE_AES_256<br>
 * RSIP_KEY_TYPE_HMAC_SHA224<br>
 * RSIP_KEY_TYPE_HMAC_SHA256
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KeyGenerate(rsip_ctrl_t * const        p_ctrl,
                            rsip_key_type_t const      key_type,
                            rsip_wrapped_key_t * const p_wrapped_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Set primitive */
    rsip_func_key_generate_t p_func = select_func_key_generate(key_type);

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_err_t rsip_ret = p_func((uint32_t *) p_wrapped_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            p_wrapped_key->alg     = (uint8_t)r_rsip_key_type_to_alg(key_type);
            p_wrapped_key->subtype = r_rsip_key_type_to_subtype(key_type);

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_ERR_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Generate a wrapped asymmetric key pair from a random number. In this API, user key input is unnecessary.
 * By encrypting data using the wrapped key is output by this API, dead copying of data can be prevented.<br>
 * Implements @ref rsip_api_t::keyPairGenerate.
 *
 * \<Usage Precautions>
 * @arg Valid key pair types.
 *
 * <table>
 * <caption id="key_pair_type"> </caption>
 * <tr><th>key_pair_type<td>RSIP_KEY_PAIR_TYPE_ECC_SECP256R1<br>
 * RSIP_KEY_PAIR_TYPE_ECC_BRAINPOOLP256R1<br>
 * RSIP_KEY_PAIR_TYPE_ECC_SECP256K1
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_KeyPairGenerate(rsip_ctrl_t * const        p_ctrl,
                                rsip_key_pair_type_t const key_pair_type,
                                rsip_wrapped_key_t * const p_wrapped_public_key,
                                rsip_wrapped_key_t * const p_wrapped_private_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Set primitive */
    rsip_func_key_pair_generate_t p_func = select_func_key_pair_generate(key_pair_type);

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_wrapped_private_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_err_t rsip_ret = p_func((uint32_t *) p_wrapped_public_key->value, (uint32_t *) p_wrapped_private_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            p_wrapped_public_key->alg      = (uint8_t)r_rsip_key_pair_type_to_public_alg(key_pair_type);
            p_wrapped_public_key->subtype  = r_rsip_key_pair_type_to_subtype(key_pair_type);
            p_wrapped_private_key->alg     = (uint8_t)r_rsip_key_pair_type_to_private_alg(key_pair_type);
            p_wrapped_private_key->subtype = r_rsip_key_pair_type_to_subtype(key_pair_type);

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_ERR_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * Decrypt the encrypted user key with Key Update Key (KUK) and wrap it with the Hardware Unique Key (HUK).<br>
 * Implements @ref rsip_api_t::encryptedKeyWrap.
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_EncryptedKeyWrap(rsip_ctrl_t * const                   p_ctrl,
                                    rsip_key_update_key_t const * const p_key_update_key,
                                    uint8_t const * const               p_initial_vector,
                                    rsip_key_type_t const               key_type,
                                    uint8_t const * const               p_encrypted_key,
                                    rsip_wrapped_key_t * const          p_wrapped_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Set primitive */
    rsip_func_encrypted_key_wrap_t p_func = select_func_encrypted_key_wrap(key_type);

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_key_update_key);
    FSP_ASSERT(p_initial_vector);
    FSP_ASSERT(p_encrypted_key);
    FSP_ASSERT(p_wrapped_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Store KUK */
    r_rsip_kuk_set(p_key_update_key->value);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_err_t rsip_ret = p_func((uint32_t const *) p_initial_vector,
                                (uint32_t const *) p_encrypted_key,
                                (uint32_t *) p_wrapped_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            p_wrapped_key->alg     = (uint8_t)r_rsip_key_type_to_alg(key_type);
            p_wrapped_key->subtype = r_rsip_key_type_to_subtype(key_type);

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_ERR_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_ERR_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * This function provides Key Wrap algorithm compliant with RFC3394.
 * Using p_wrapped_kek to wrap p_wrapped_target_key, and output the result to p_rfc3394_wrapped_target_key.<br>
 * Implements @ref rsip_api_t::rfc3394_KeyWrap.
 *
 * \<Usage Precautions>
 * @arg Argument "p_wrapped_kek" only supports the following key type.
 * <table>
 * <caption id="KeyWrapType1"> </caption>
 * <tr><th>Key Type of p_wrapped_kek<th>Corresponding Parameter</tr>
 * <tr><td>AES-128<td>RSIP_KEY_TYPE_AES_128</td>
 * <tr><td>AES-256<td>RSIP_KEY_TYPE_AES_256</td>
 * </table>
 *
 * @arg Argument "p_wrapped_target_key" only supports the following key type.
 * <table>
 * <caption id="KeyWrapType2"> </caption>
 * <tr><th>Key Type of p_wrapped_target_key<th>Corresponding Parameter</tr>
 * <tr><td>AES-128<td>RSIP_KEY_TYPE_AES_128</td>
 * <tr><td>AES-256<td>RSIP_KEY_TYPE_AES_256</td>
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_INVALID_ARGUMENT              Input key type or mode is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RFC3394_KeyWrap(rsip_ctrl_t * const              p_ctrl,
                                    rsip_wrapped_key_t const * const p_wrapped_kek,
                                    rsip_wrapped_key_t const * const p_wrapped_target_key,
                                    uint8_t * const                  p_rfc3394_wrapped_target_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_kek);
    FSP_ASSERT(p_wrapped_target_key);
    FSP_ASSERT(p_rfc3394_wrapped_target_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_AES == p_wrapped_kek->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rfc3394_key_wrap[p_wrapped_kek->subtype], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_key_type_t key_type = (rsip_key_type_t)RSIP_PRV_KEY_TYPE(p_wrapped_target_key->alg,
                                p_wrapped_target_key->subtype);
    rsip_err_t rsip_ret =
            g_func.p_rfc3394_key_wrap[p_wrapped_kek->subtype]((const uint32_t *)    p_wrapped_kek->value,
                                                                                    key_type,
                                                            (const uint32_t *)      p_wrapped_target_key->value,
                                                            (uint32_t *)            p_rfc3394_wrapped_target_key);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            err = FSP_SUCCESS;
            break;
        }

        case RSIP_ERR_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        case RSIP_ERR_KEY_SET:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
            break;
        }

        case RSIP_ERR_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/*******************************************************************************************************************//**
 * This function provides Key Unwrap algorithm compliant with RFC3394.
 * Using p_wrapped_kek to unwrap p_rfc3394_wrapped_target_key, and output the result to p_wrapped_target_key.<br>
 * Implements @ref rsip_api_t::rfc3394_KeyUnwrap.
 *
 * \<Usage Precautions>
 * @arg Argument "p_wrapped_kek" only supports the following key type.
 * <table>
 * <caption id="KeyWrapType3"> </caption>
 * <tr><th>Key Type of p_wrapped_kek<th>Corresponding Parameter</tr>
 * <tr><td>AES-128<td>RSIP_KEY_TYPE_AES_128</td>
 * <tr><td>AES-256<td>RSIP_KEY_TYPE_AES_256</td>
 * </table>
 *
 * @arg Argument "key_type" represents the key type of p_rfc3394_wrapped_target_key,
 * and only supports the following key type.
 * <table>
 * <caption id="KeyWrapType4"> </caption>
 * <tr><th>Key Type of p_rfc3394_wrapped_target_key<th>Corresponding Parameter</tr>
 * <tr><td>AES-128<td>RSIP_KEY_TYPE_AES_128</td>
 * <tr><td>AES-256<td>RSIP_KEY_TYPE_AES_256</td>
 * </table>
 *
 * \<Operational State><br>
 * This API can only be executed in the STATE_MAIN, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_INVALID_ARGUMENT              Input key type or mode is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_RFC3394_KeyUnwrap(rsip_ctrl_t * const              p_ctrl,
                                    rsip_wrapped_key_t const * const p_wrapped_kek,
                                    rsip_key_type_t const            key_type,
                                    uint8_t const * const            p_rfc3394_wrapped_target_key,
                                    rsip_wrapped_key_t * const       p_wrapped_target_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_kek);
    FSP_ASSERT(p_rfc3394_wrapped_target_key);
    FSP_ASSERT(p_wrapped_target_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check key type */
    FSP_ERROR_RETURN(RSIP_ALG_AES == p_wrapped_kek->alg, FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL);

    /* Check configuration */
    FSP_ERROR_RETURN(g_func.p_rfc3394_key_unwrap[p_wrapped_kek->subtype], FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_err_t rsip_ret =
            g_func.p_rfc3394_key_unwrap[p_wrapped_kek->subtype]((const uint32_t *)      p_wrapped_kek->value,
                                                                                        key_type,
                                                                (const uint32_t *)      p_rfc3394_wrapped_target_key,
                                                                (uint32_t *)            p_wrapped_target_key->value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            p_wrapped_target_key->alg     = (uint8_t)r_rsip_key_type_to_alg(key_type);
            p_wrapped_target_key->subtype = r_rsip_key_type_to_subtype(key_type);

            err = FSP_SUCCESS;
            break;
        }

        case RSIP_ERR_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        case RSIP_ERR_KEY_SET:
        {
            err = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
            break;
        }

        case RSIP_ERR_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

RSIP_SEC_P_SECURE_BOOT
/*******************************************************************************************************************//**
 * This function provides the ability to construct structure data "rsip_wrapped_key_t" from injected key data.
 * The value of injected key is not validated in this API. Refer "Key Size Table" for supported key types.<br>
 * Implements @ref rsip_api_t::injectedKeyImport.
 *
 * \<Operational State><br>
 * This API can be executed in any state including STATE_INITIAL, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_UNSUPPORTED                   Selected key type is not supported.
 * @retval FSP_ERR_INVALID_SIZE                  Buffer length is too short.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_InjectedKeyImport(rsip_key_type_t const      key_type,
                                    uint8_t const * const      p_injected_key,
                                    rsip_wrapped_key_t * const p_wrapped_key,
                                    uint32_t const             wrapped_key_buffer_length)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_injected_key);
    FSP_ASSERT(p_wrapped_key);
#endif

    fsp_err_t err = FSP_ERR_UNSUPPORTED;
    uint32_t  len = get_wrapped_key_size(key_type);

    if (len == 0)
    {
        /* Unsupported key */
    }
    else if (RSIP_PRV_KEY_SIZE(len) > wrapped_key_buffer_length)
    {
        /* Buffer length must be equal or grater than actual wrapped key length */
        err = FSP_ERR_INVALID_SIZE;
    }
    else
    {
        p_wrapped_key->alg     = (uint8_t)r_rsip_key_type_to_alg(key_type);
        p_wrapped_key->subtype = r_rsip_key_type_to_subtype(key_type);
        memcpy(p_wrapped_key->value, p_injected_key, len);

        err = FSP_SUCCESS;
    }

    return err;
}
RSIP_SEC_DEFAULT
/*******************************************************************************************************************//**
 * Exports public key parameters from a wrapped key.<br>
 * Implements @ref rsip_api_t::publicKeyExport.
 *
 * \<Usage Precautions><br>
 * @arg The key type of p_wrapped_public_key must be RSIP_KEY_TYPE_ECC_xxx_PUBLIC
 * @arg For ECC public keys, raw_public_key has QX placed first and QY placed after that.
 * @arg The value location of each elements in public key is shown in below:
 * <table>
 * <caption id="EccBitLen"> </caption>
 * <tr><th>ECC bit length<th>QX location<th>QY location</tr>
 * <tr><td>256<td>0<td>32</td>
 * </table>
 *
 * \<Operational State><br>
 * This API can be executed in any state including STATE_INITIAL, and there are no state transitions.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL      Input key value is illegal.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_PublicKeyExport(rsip_wrapped_key_t const * const p_wrapped_public_key,
                                uint8_t * const                  p_raw_public_key)
{
#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_wrapped_public_key);
    FSP_ASSERT(p_raw_public_key);
#endif

    fsp_err_t err  = FSP_ERR_CRYPTO_RSIP_KEY_SET_FAIL;
    uint8_t * base = (uint8_t *)p_wrapped_public_key->value;
    uint32_t  param1_pos;
    uint32_t  param1_len;
    uint32_t  param2_pos;
    uint32_t  param2_len;

    switch (p_wrapped_public_key->alg)
    {
        case RSIP_ALG_ECC_PUBLIC:
        {
            param1_pos = gs_ecc_param1_pos[p_wrapped_public_key->subtype];
            param1_len = gs_ecc_param1_len[p_wrapped_public_key->subtype];
            param2_pos = gs_ecc_param2_pos[p_wrapped_public_key->subtype];
            param2_len = gs_ecc_param2_len[p_wrapped_public_key->subtype];
            err        = FSP_SUCCESS;
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    if (FSP_SUCCESS == err)
    {
        memcpy(p_raw_public_key, base + param1_pos, param1_len);
        memcpy(p_raw_public_key + param1_len, base + param2_pos, param2_len);
    }

    return err;
}

RSIP_SEC_P_SECURE_BOOT_ERASE
/*******************************************************************************************************************//**
 * Decrypts an encrypted user key with User Factory Programming Key (UFPK)
 * and wrap it with the Hardware Unique Key (HUK).
 * Implements @ref rsip_api_t::initialKeyWrap.
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @param[in,out] p_ctrl                                 Pointer to control block.
 * @param[in]     p_wrapped_user_factory_programming_key Wrapped User Factory Programming Key (W-UFPK).
 *                                                       The length is 32 bytes.
 * @param[in]     p_initial_vector                       Initialization vector when generating encrypted_key.
 *                                                       The length is 16 bytes.
 * @param[in]     key_type                               Inputs/Outputs key type.
 * @param[in]     p_encrypted_key                        Encrypted user key. The length depends on the key type.
 * @param[out]    p_injected_key                         Pointer to destination of injected key.
 *                                                       The length depends on the key type.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_NOT_ENABLED                   Input key type is disabled in this function by configuration.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_InitialKeyWrap(rsip_ctrl_t * const        p_ctrl,
                                rsip_wufpk_t const * const p_wrapped_user_factory_programming_key,
                                uint8_t const * const      p_initial_vector,
                                rsip_key_type_t const      key_type,
                                uint8_t const * const      p_encrypted_key,
                                uint8_t * const            p_injected_key)

{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Set primitive */
    rsip_func_initial_key_wrap_t p_func = select_func_initial_key_wrap(key_type);

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_user_factory_programming_key);
    FSP_ASSERT(p_initial_vector);
    FSP_ASSERT(p_encrypted_key);
    FSP_ASSERT(p_injected_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check if the key type is enabled on configuration */
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_err_t rsip_ret = p_func((uint32_t const *) p_wrapped_user_factory_programming_key,
                                (uint32_t const *) p_initial_vector,
                                (uint32_t const *) p_encrypted_key,
                                (uint32_t *) p_injected_key);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            err = FSP_SUCCESS;
            break;
        }

        case RSIP_ERR_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_ERR_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

RSIP_SEC_P_SECURE_BOOT_ERASE
/*******************************************************************************************************************//**
 * Decrypts an encrypted Key Update Key (KUK) with User Factory Programming Key (UFPK)
 * and wrap it with the Hardware Unique Key (HUK).
 *
 * Implements @ref rsip_api_t::initialKeyUpdateKeyWrap.
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @param[in,out] p_ctrl                                 Pointer to control block.
 * @param[in]     p_wrapped_user_factory_programming_key Wrapped User Factory Programming Key (W-UFPK).
 *                                                       The length is 32 bytes.
 * @param[in]     p_initial_vector                       Initialization vector when generating encrypted_key.
 *                                                       The length is 16 bytes.
 * @param[in]     p_encrypted_key                        Encrypted key update key.
 * @param[out]    p_injected_key                         Pointer to destination of injected key update key.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_ASSERTION                     A required parameter is NULL.
 * @retval FSP_ERR_NOT_OPEN                      Module is not open.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 * @retval FSP_ERR_CRYPTO_RSIP_FAIL              Input parameter is invalid.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_InitialKeyUpdateKeyWrap(rsip_ctrl_t * const           p_ctrl,
                                        rsip_wufpk_t const * const    p_wrapped_user_factory_programming_key,
                                        uint8_t const * const         p_initial_vector,
                                        uint8_t const * const         p_encrypted_key,
                                        rsip_key_update_key_t * const p_injected_key)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_user_factory_programming_key);
    FSP_ASSERT(p_initial_vector);
    FSP_ASSERT(p_encrypted_key);
    FSP_ASSERT(p_injected_key);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_err_t rsip_ret =
            g_func.p_initial_key_update_key_wrap_aes((uint32_t const *) p_wrapped_user_factory_programming_key,
                                                    (uint32_t const *) p_initial_vector,
                                                    (uint32_t const *) p_encrypted_key,
                                                    (uint32_t *) p_injected_key);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            err = FSP_SUCCESS;
            break;
        }

        case RSIP_ERR_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_ERR_FAIL:
        {
            err = FSP_ERR_CRYPTO_RSIP_FAIL;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}
RSIP_SEC_DEFAULT
/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_PROTECTED)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Generates a 128-bit random number.
 *
 * @param[in,out] p_ctrl   Pointer to control block.
 * @param[out]    p_random Pointer to destination of random number. The length is 16 bytes.
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @retval FSP_ERR_INVALID_STATE                 Internal state is illegal.
 *
 * @retval FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT A resource conflict occurred because a hardware resource required
 *                                               by the processing is in use by other processing.
 * @retval FSP_ERR_CRYPTO_RSIP_FATAL             Software corruption is detected.
 **********************************************************************************************************************/
fsp_err_t r_rsip_random_number_generate(rsip_ctrl_t * const p_ctrl, uint8_t * const p_random)
{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_err_t rsip_ret = g_func.p_rng((uint32_t *) p_random);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_SUCCESS:
        {
            err = FSP_SUCCESS;
            break;
        }

        case RSIP_ERR_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        default:
        {
            err = FSP_ERR_CRYPTO_RSIP_FATAL;
        }
    }

    return err;
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

static rsip_func_key_generate_t select_func_key_generate(rsip_key_type_t key_type)
{
    rsip_func_key_generate_t ret     = NULL;
    rsip_alg_t               alg     = r_rsip_key_type_to_alg(key_type);
    uint32_t                 subtype = r_rsip_key_type_to_subtype(key_type);

    switch (alg)
    {
        case RSIP_ALG_AES:
        {
            ret = g_func.p_key_generate_aes[subtype];
            break;
        }

        case RSIP_ALG_HMAC:
        {
            ret = g_func.p_key_generate_hmac[subtype];
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return ret;
}

static rsip_func_key_pair_generate_t select_func_key_pair_generate(rsip_key_pair_type_t key_pair_type)
{
    rsip_func_key_pair_generate_t ret = NULL;
    rsip_alg_t alg     = r_rsip_key_pair_type_to_public_alg(key_pair_type);
    uint32_t   subtype = r_rsip_key_pair_type_to_subtype(key_pair_type);

    switch (alg)
    {
        case RSIP_ALG_ECC_PUBLIC:
        {
            ret = g_func.p_key_pair_generate_ecc[subtype];
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return ret;
}

static rsip_func_encrypted_key_wrap_t select_func_encrypted_key_wrap(rsip_key_type_t key_type)
{
    rsip_func_encrypted_key_wrap_t ret = NULL;
    rsip_alg_t alg     = r_rsip_key_type_to_alg(key_type);
    uint32_t   subtype = r_rsip_key_type_to_subtype(key_type);

    switch (alg)
    {
        case RSIP_ALG_AES:
        {
            ret = g_func.p_encrypted_key_wrap_aes[subtype];
            break;
        }

        case RSIP_ALG_ECC_PUBLIC:
        {
            ret = g_func.p_encrypted_key_wrap_ecc_pub[subtype];
            break;
        }

        case RSIP_ALG_ECC_PRIVATE:
        {
            ret = g_func.p_encrypted_key_wrap_ecc_priv[subtype];
            break;
        }

        case RSIP_ALG_HMAC:
        {
            ret = g_func.p_encrypted_key_wrap_hmac[subtype];
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return ret;
}

RSIP_SEC_P_SECURE_BOOT
static uint32_t get_wrapped_key_size(rsip_key_type_t key_type)
{
    uint32_t   ret     = 0;
    rsip_alg_t alg     = r_rsip_key_type_to_alg(key_type);
    uint32_t   subtype = r_rsip_key_type_to_subtype(key_type);

    switch (alg)
    {
        case RSIP_ALG_AES:
        {
            ret = gs_wrapped_key_value_len_aes[subtype];
            break;
        }

        case RSIP_ALG_ECC_PUBLIC:
        {
            ret = gs_wrapped_key_value_len_ecc_pub[subtype];
            break;
        }

        case RSIP_ALG_ECC_PRIVATE:
        {
            ret = gs_wrapped_key_value_len_ecc_priv[subtype];
            break;
        }

        case RSIP_ALG_HMAC:
        {
            ret = gs_wrapped_key_value_len_hmac[subtype];
            break;
        }

        default:
        {
            /* Invalid key type */
        }
    }

    return ret;
}
RSIP_SEC_DEFAULT