/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_cm_key_injection.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/* Key update. */
#define R_RSIP_CM_INSTALL_KEY_RING_INDEX    (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/* Key Inst Data Size. */
typedef enum e_rsip_word_size_oem_key_inst_data
{
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES128                          = 8U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES256                          = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PUBLIC_KEY        = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PRIVATE_KEY       = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PUBLIC_KEY  = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PRIVATE_KEY = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PUBLIC_KEY        = 20U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PRIVATE_KEY       = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA224                     = 12U,
    RSIP_WORD_SIZE_OEM_KEY_INST_DATA_HMAC_SHA256                     = 12U,
} e_rsip_word_size_oem_key_inst_data_t;

/* OEM Command */
typedef enum e_rsip_oem_cmd
{
    RSIP_OEM_CMD_INVALID                     = 0U,
    RSIP_OEM_CMD_AES128                      = 5U,
    RSIP_OEM_CMD_AES256                      = 7U,
    RSIP_OEM_CMD_ECC_SECP256R1_PUBLIC        = 22U,
    RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE       = 23U,
    RSIP_OEM_CMD_HMAC_SHA224                 = 26U,
    RSIP_OEM_CMD_HMAC_SHA256                 = 27U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PUBLIC  = 28U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PRIVATE = 29U,
    RSIP_OEM_CMD_ECC_SECP256K1_PUBLIC        = 34U,
    RSIP_OEM_CMD_ECC_SECP256K1_PRIVATE       = 35U,
} rsip_oem_cmd_t;

/* Key types */
typedef enum e_rsip_key_type
{
    RSIP_KEY_TYPE_INVALID,                      ///< Invalid key
    RSIP_KEY_TYPE_AES_128,                      ///< AES-128
    RSIP_KEY_TYPE_AES_192,                      ///< AES-192
    RSIP_KEY_TYPE_AES_256,                      ///< AES-256
    RSIP_KEY_TYPE_AES_128_XTS,                  ///< AES-128 XTS
    RSIP_KEY_TYPE_AES_256_XTS,                  ///< AES-256 XTS
    RSIP_KEY_TYPE_RSA_2048_PUBLIC,              ///< RSA-2048 public key
    RSIP_KEY_TYPE_RSA_2048_PRIVATE,             ///< RSA-2048 private key
    RSIP_KEY_TYPE_RSA_3072_PUBLIC,              ///< RSA-2048 public key
    RSIP_KEY_TYPE_RSA_3072_PRIVATE,             ///< RSA-2048 private key
    RSIP_KEY_TYPE_RSA_4096_PUBLIC,              ///< RSA-2048 public key
    RSIP_KEY_TYPE_RSA_4096_PRIVATE,             ///< RSA-2048 private key
    RSIP_KEY_TYPE_ECC_SECP256R1_PUBLIC,         ///< secp256r1 public key (also known as NIST P-256, prime256v1)
    RSIP_KEY_TYPE_ECC_SECP256R1_PRIVATE,        ///< secp256r1 private key (also known as NIST P-256, prime256v1)
    RSIP_KEY_TYPE_ECC_SECP384R1_PUBLIC,         ///< secp384r1 public key (also known as NIST P-384, prime384v1)
    RSIP_KEY_TYPE_ECC_SECP384R1_PRIVATE,        ///< secp384r1 private key (also known as NIST P-384, prime384v1)
    RSIP_KEY_TYPE_ECC_SECP521R1_PUBLIC,         ///< secp521r1 public key (also known as NIST P-521, prime521v1)
    RSIP_KEY_TYPE_ECC_SECP521R1_PRIVATE,        ///< secp521r1 private key (also known as NIST P-521, prime521v1)
    RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PUBLIC,   ///< brainpool256r1 public key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PRIVATE,  ///< brainpool256r1 private key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PUBLIC,   ///< brainpool256r1 public key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP384R1_PRIVATE,  ///< brainpool256r1 private key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PUBLIC,   ///< brainpool256r1 public key
    RSIP_KEY_TYPE_ECC_BRAINPOOLP512R1_PRIVATE,  ///< brainpool256r1 private key
    RSIP_KEY_TYPE_ECC_SECP256K1_PUBLIC,         ///< secp256k1 public key
    RSIP_KEY_TYPE_ECC_SECP256K1_PRIVATE,        ///< secp256k1 private key
    RSIP_KEY_TYPE_ECC_ED25519_PUBLIC,           ///< Ed25519 public key
    RSIP_KEY_TYPE_ECC_ED25519_PRIVATE,          ///< Ed25519 private key
    RSIP_KEY_TYPE_HMAC_SHA224,                  ///< hmac sha 224
    RSIP_KEY_TYPE_HMAC_SHA256,                  ///< hmac sha 256
    RSIP_KEY_TYPE_HMAC_SHA384,                  ///< hmac sha 384
    RSIP_KEY_TYPE_HMAC_SHA512,                  ///< hmac sha 512
    RSIP_KEY_TYPE_HMAC_SHA512_224,              ///< hmac sha 512/224
    RSIP_KEY_TYPE_HMAC_SHA512_256,              ///< hmac sha 512/256
    RSIP_KEY_TYPE_MAKE_ENUM_LONG = 0xFFFFFFFFUL // Make this enum 32-bit data
} rsip_key_type_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
const rsip_key_injection_api_t g_rsip_key_injection_on_rsip =
{
    .getversion                                = R_RSIP_CM_GetVersion,
    .AES128_InitialKeyWrap                     = R_RSIP_CM_AES128_InitialKeyWrap,
    .AES256_InitialKeyWrap                     = R_RSIP_CM_AES256_InitialKeyWrap,
    .ECC_secp256r1_InitialPrivateKeyWrap       = R_RSIP_CM_ECC_secp256r1_InitialPrivateKeyWrap,
    .ECC_secp256k1_InitialPrivateKeyWrap       = R_RSIP_CM_ECC_secp256k1_InitialPrivateKeyWrap,
    .ECC_brainpoolP256r1_InitialPrivateKeyWrap = R_RSIP_CM_ECC_brainpoolP256r1_InitialPrivateKeyWrap,
};

/*******************************************************************************************************************//**
 * @addtogroup RSIP_CM_KEY_INJECTION
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/
/*******************************************************************************************************************//**
 * Returns the version of this module. <br>
 * The version number is encoded such that the top two bytes are the
 * major version number and the bottom two bytes are the minor version number.
 * Implements @ref rsip_key_injection_api_t::getversion.
 *
 * \<Operational State><br>
 * This API can be executed in any state including STATE_INITIAL, and there are no state transitions.
 *
 * @retval        Version number
 **********************************************************************************************************************/
uint32_t R_RSIP_CM_GetVersion(void)
{
    return ((R_RSIP_CM_VERSION_MAJOR << 16u) | R_RSIP_CM_VERSION_MINOR);
}
/**********************************************************************************************************************
* End of function R_RSIP_CM_GetVersion
**********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief R_RSIP_CM_AES128_InitialKeyWrap This API generates 128-bit AES key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by
 *                                                     the Renesas Key Wrap Service.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain,
 *                                                     it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           128-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *
 * @note The pre-run state is RSIP CM Enabled State.
 *       After the function runs the state transitions to RSIP CM Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_CM_AES128_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const           p_wrapped_user_factory_programming_key,
                                        uint8_t const * const           p_initial_vector,
                                        uint8_t const * const           p_user_key,
                                        rsip_aes_wrapped_key_t * const  p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_AES128);
    uint32_t  in_data_shared_key_index = R_RSIP_CM_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES128;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES128 - 4;
    }

    /* Call primitive (cast to match the argument type with the primitive function) */
    error_code = HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                        &in_data_cmd,
                                        &in_data_shared_key_index,
                                        (uint32_t const *) p_wrapped_user_factory_programming_key,
                                        (uint32_t const *) p_initial_vector,
                                        (uint32_t const *) p_user_key,
                                        (uint32_t *) p_wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_AES_128;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}
/**********************************************************************************************************************
* End of function R_RSIP_CM_AES128_InitialKeyWrap
**********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This API generates 256-bit AES key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by
 *                                                     the Renesas Key Wrap Service.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain,
 *                                                     it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit AES wrapped key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *
 * @note The pre-run state is RSIP CM Enabled State.
 *       After the function runs the state transitions to RSIP CM Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_CM_AES256_InitialKeyWrap(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const           p_wrapped_user_factory_programming_key,
                                        uint8_t const * const           p_initial_vector,
                                        uint8_t const * const           p_user_key,
                                        rsip_aes_wrapped_key_t * const  p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_AES256);
    uint32_t  in_data_shared_key_index = R_RSIP_CM_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES256;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_AES256 - 4;
    }

    /* Call primitive (cast to match the argument type with the primitive function) */
    error_code = HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                        &in_data_cmd,
                                        &in_data_shared_key_index,
                                        (uint32_t const *) p_wrapped_user_factory_programming_key,
                                        (uint32_t const *) p_initial_vector,
                                        (uint32_t const *) p_user_key,
                                        (uint32_t *) p_wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_AES_256;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}
/**********************************************************************************************************************
* End of function R_RSIP_CM_AES256_InitialKeyWrap
**********************************************************************************************************************/

/*******************************************************************************************************************//**
* This API generates 256-bit ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by
 *                                                     the Renesas Key Wrap Service.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain,
 *                                                     it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *
 * @note The pre-run state is RSIP CM Enabled State.
 *       After the function runs the state transitions to RSIP CM Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_CM_ECC_secp256r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                        uint8_t const * const    p_wrapped_user_factory_programming_key,
                                                        uint8_t const * const    p_initial_vector,
                                                        uint8_t const * const    p_user_key,
                                                        rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_CM_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256R1_PRIVATE_KEY - 4;
    }

    /* Call primitive (cast to match the argument type with the primitive function) */
    error_code = HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                        &in_data_cmd,
                                        &in_data_shared_key_index,
                                        (uint32_t const *) p_wrapped_user_factory_programming_key,
                                        (uint32_t const *) p_initial_vector,
                                        (uint32_t const *) p_user_key,
                                        (uint32_t *) p_wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_SECP256R1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}
/**********************************************************************************************************************
* End of function R_RSIP_CM_ECC_secp256r1_InitialPrivateKeyWrap
**********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This API generates 256-bit ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by
 *                                                     the Renesas Key Wrap Service.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain,
 *                                                     it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *
 * @note The pre-run state is RSIP CM Enabled State.
 *       After the function runs the state transitions to RSIP CM Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_CM_ECC_secp256k1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                        uint8_t const * const    p_wrapped_user_factory_programming_key,
                                                        uint8_t const * const    p_initial_vector,
                                                        uint8_t const * const    p_user_key,
                                                        rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_SECP256K1_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_CM_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_SECP256K1_PRIVATE_KEY - 4;
    }

    /* Call primitive (cast to match the argument type with the primitive function) */
    error_code = HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                        &in_data_cmd,
                                        &in_data_shared_key_index,
                                        (uint32_t const *) p_wrapped_user_factory_programming_key,
                                        (uint32_t const *) p_initial_vector,
                                        (uint32_t const *) p_user_key,
                                        (uint32_t *) p_wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_SECP256K1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}
/**********************************************************************************************************************
* End of function R_RSIP_CM_ECC_secp256k1_InitialPrivateKeyWrap
**********************************************************************************************************************/

/*******************************************************************************************************************//**
 * This API generates 256-bit brainpool ECC private key within the user routine.
 *
 * @param[in]  key_injection_type                      Selection key injection type when generating wrapped key
 * @param[in]  p_wrapped_user_factory_programming_key  Wrapped user factory programming key by
 *                                                     the Renesas Key Wrap Service.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_initial_vector                        Initialization vector when generating encrypted key.
 *                                                     When key injection type is plain,
 *                                                     this is not required and any value can be specified.
 * @param[in]  p_user_key                              User key. If key injection type is not plain,
 *                                                     it is encrypted and MAC appended
 * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
 *
 * @retval FSP_SUCCESS                           Normal termination.
 * @return If an error occurs, the return value will be as follows.
 *         * FSP_ERR_CRYPTO_SCE_FAIL               MAC anomaly detection.
 *         * FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT  Resource conflict.
 *
 * @note The pre-run state is RSIP CM Enabled State.
 *       After the function runs the state transitions to RSIP CM Enabled State.
 **********************************************************************************************************************/
fsp_err_t R_RSIP_CM_ECC_brainpoolP256r1_InitialPrivateKeyWrap(rsip_key_injection_type_t const        key_injection_type,
                                                        uint8_t const * const    p_wrapped_user_factory_programming_key,
                                                        uint8_t const * const    p_initial_vector,
                                                        uint8_t const * const    p_user_key,
                                                        rsip_ecc_private_wrapped_key_t * const p_wrapped_key)
{
    fsp_err_t error_code               = FSP_SUCCESS;
    uint32_t  in_data_key_type         = key_injection_type;
    uint32_t  in_data_cmd              = change_endian_long(RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PRIVATE);
    uint32_t  in_data_shared_key_index = R_RSIP_CM_INSTALL_KEY_RING_INDEX;

    if (RSIP_KEY_INJECTION_TYPE_ENCRYPTED == in_data_key_type)
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PRIVATE_KEY;
    }
    else
    {
        INST_DATA_SIZE = RSIP_WORD_SIZE_OEM_KEY_INST_DATA_ECC_BRAINPOOLP256R1_PRIVATE_KEY - 4;
    }

    /* Call primitive (cast to match the argument type with the primitive function) */
    error_code = HW_SCE_GenerateOemKeyIndexSub(&in_data_key_type,
                                        &in_data_cmd,
                                        &in_data_shared_key_index,
                                        (uint32_t const *) p_wrapped_user_factory_programming_key,
                                        (uint32_t const *) p_initial_vector,
                                        (uint32_t const *) p_user_key,
                                        (uint32_t *) p_wrapped_key->value);
    if (FSP_SUCCESS == error_code)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_ECC_BRAINPOOLP256R1_PRIVATE;
    }
    else
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_INVALID;
    }

    return error_code;
}
/**********************************************************************************************************************
* End of function R_RSIP_CM_ECC_brainpoolP256r1_InitialPrivateKeyWrap
**********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_CM_KEY_INJECTION)
 **********************************************************************************************************************/
