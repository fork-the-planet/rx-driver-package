/*
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_rsip_key_injection.c
* Description  : Interface definition for the r_rsip_key_injection RSIP module.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.10.2024 1.00     First Release.
*         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
*         :                     Revised key management specification
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_public.h"
#include "r_rsip_private.h"
#include "r_rsip_wrapper.h"
#include "r_rsip_protected_rx_if.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if RSIP_CFG_AES_128_ENABLE
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_AES_128                           RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_AES_128
#else
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_AES_128                           NULL
#endif
#if RSIP_CFG_AES_256_ENABLE
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_AES_256                           RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_AES_256
#else
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_AES_256                           NULL
#endif

#if RSIP_CFG_ECC_SECP256R1_ENABLE
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256R1_PUBLIC\
              RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_SECP256R1_PUBLIC
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256R1_PRIVATE\
              RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_SECP256R1_PRIVATE
#else
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256R1_PUBLIC              NULL
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256R1_PRIVATE             NULL
#endif
#if RSIP_CFG_ECC_BRAINPOOLP256R1_ENABLE
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PUBLIC\
            RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PUBLIC
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PRIVATE\
            RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PRIVATE
#else
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PUBLIC        NULL
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PRIVATE       NULL
#endif
#if RSIP_CFG_ECC_SECP256K1_ENABLE
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256K1_PUBLIC\
            RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_SECP256K1_PUBLIC
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256K1_PRIVATE\
            RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_ECC_SECP256K1_PRIVATE
#else
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256K1_PUBLIC              NULL
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256K1_PRIVATE             NULL
#endif

#if RSIP_CFG_HMAC_SHA224_ENABLE
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_HMAC_SHA224                       RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_HMAC_SHA224
#else
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_HMAC_SHA224                       NULL
#endif
#if RSIP_CFG_HMAC_SHA256_ENABLE
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_HMAC_SHA256                       RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_HMAC_SHA256
#else
 #define RSIP_PRV_FUNC_INIT_KEY_WRAP_HMAC_SHA256                       NULL
#endif

#define RSIP_PRV_FUNC_INIT_KEY_WRAP_KUK                                RSIP_PRV_FUNC_NAME_INIT_KEY_WRAP_KUK

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Initial key wrap */
typedef rsip_ret_t (* rsip_func_initial_key_wrap_t)(const uint32_t InData_SessionKey[],
                                                    const uint32_t InData_IV[],
                                                    const uint32_t InData_InstData[],
                                                    uint32_t OutData_KeyIndex[]);

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

static rsip_func_initial_key_wrap_t     select_func_initial_key_wrap(rsip_key_type_extend_t key_type_ext);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static const rsip_func_initial_key_wrap_t gsp_func_initial_key_wrap_aes[RSIP_PRV_KEY_SUBTYPE_AES_NUM] =
{
    [RSIP_PRV_KEY_SUBTYPE_AES_128] = RSIP_PRV_FUNC_INIT_KEY_WRAP_AES_128,
    [RSIP_PRV_KEY_SUBTYPE_AES_256] = RSIP_PRV_FUNC_INIT_KEY_WRAP_AES_256
};

static const rsip_func_initial_key_wrap_t gsp_func_initial_key_wrap_ecc_pub[RSIP_PRV_KEY_SUBTYPE_ECC_NUM] =
{
    [RSIP_PRV_KEY_SUBTYPE_ECC_SECP256R1] = RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256R1_PUBLIC,
    [RSIP_PRV_KEY_SUBTYPE_ECC_SECP256K1] = RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256K1_PUBLIC,
    [RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP256R1] = RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PUBLIC
};

static const rsip_func_initial_key_wrap_t gsp_func_initial_key_wrap_ecc_priv[RSIP_PRV_KEY_SUBTYPE_ECC_NUM] =
{
    [RSIP_PRV_KEY_SUBTYPE_ECC_SECP256R1] = RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256R1_PRIVATE,
    [RSIP_PRV_KEY_SUBTYPE_ECC_SECP256K1] = RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_SECP256K1_PRIVATE,
    [RSIP_PRV_KEY_SUBTYPE_ECC_BRAINPOOLP256R1] = RSIP_PRV_FUNC_INIT_KEY_WRAP_ECC_BRAINPOOLP256R1_PRIVATE
};

static const rsip_func_initial_key_wrap_t gsp_func_initial_key_wrap_hmac[RSIP_PRV_KEY_SUBTYPE_HMAC_NUM] =
{
    [RSIP_PRV_KEY_SUBTYPE_HMAC_SHA224] = RSIP_PRV_FUNC_INIT_KEY_WRAP_HMAC_SHA224,
    [RSIP_PRV_KEY_SUBTYPE_HMAC_SHA256] = RSIP_PRV_FUNC_INIT_KEY_WRAP_HMAC_SHA256
};

static const rsip_func_initial_key_wrap_t gsp_func_initial_key_wrap_misc[RSIP_PRV_KEY_SUBTYPE_MISC_NUM] =
{
    [RSIP_PRV_KEY_SUBTYPE_MISC_KUK] = RSIP_PRV_FUNC_INIT_KEY_WRAP_KUK
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup RSIP_PROTECTED
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Decrypts an encrypted user key with User Factory Programming Key (UFPK)
 * and wrap it with the Hardware Unique Key (HUK).
 *
 * @par State transition
 * This API can only be executed in **STATE_MAIN**, and does not cause any state transitions.
 *
 * @param[in,out] p_ctrl                                 Pointer to control block.
 * @param[in]     p_wrapped_user_factory_programming_key Wrapped User Factory Programming Key (W-UFPK).
 *                                                       The length is 32 bytes.
 * @param[in]     p_initial_vector                       Initialization vector when generating encrypted_key.
 *                                                       The length is 16 bytes.
 * @param[in]     p_encrypted_key                        Encrypted user key. The length depends on the key type.
 * @param[in,out] p_wrapped_key                          Pointer to destination of wrapped key.
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
fsp_err_t R_RSIP_InitialKeyWrap(rsip_ctrl_t * const         p_ctrl,
                                void const * const          p_wrapped_user_factory_programming_key,
                                void const * const          p_initial_vector,
                                void const * const          p_encrypted_key,
                                rsip_wrapped_key_t * const  p_wrapped_key)

{
    rsip_instance_ctrl_t * p_instance_ctrl = (rsip_instance_ctrl_t *) p_ctrl;

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_wrapped_user_factory_programming_key);
    FSP_ASSERT(p_initial_vector);
    FSP_ASSERT(p_encrypted_key);
    FSP_ASSERT(p_wrapped_key);
    FSP_ASSERT(p_wrapped_key->p_value);
    FSP_ERROR_RETURN(RSIP_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    rsip_key_type_extend_t       key_type_ext = r_rsip_key_type_parse(p_wrapped_key->type); // Parse key type
    rsip_func_initial_key_wrap_t p_func       = select_func_initial_key_wrap(key_type_ext); // Set function

#if RSIP_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(p_func, FSP_ERR_NOT_ENABLED);
#endif

    /* Check state */
    FSP_ERROR_RETURN(RSIP_STATE_MAIN == p_instance_ctrl->state, FSP_ERR_INVALID_STATE);

    /* Call primitive (cast to match the argument type with the primitive function) */
    rsip_ret_t rsip_ret = p_func((uint32_t const *) p_wrapped_user_factory_programming_key,
                                (uint32_t const *) p_initial_vector,
                                (uint32_t const *) p_encrypted_key,
                                (uint32_t *) p_wrapped_key->p_value);

    /* Check error */
    fsp_err_t err = FSP_ERR_CRYPTO_RSIP_FATAL;
    switch (rsip_ret)
    {
        case RSIP_RET_PASS:
        {
            err = FSP_SUCCESS;
            break;
        }

        case RSIP_RET_RESOURCE_CONFLICT:
        {
            err = FSP_ERR_CRYPTO_RSIP_RESOURCE_CONFLICT;
            break;
        }

        case RSIP_RET_FAIL:
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
 * @} (end addtogroup RSIP_PROTECTED)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Select primitive function of initial key wrapping from key type.
 *
 * @param[in] key_type_ext Extended key type.
 *
 * @return Pointer to function.
 ***********************************************************************************************************************/
static rsip_func_initial_key_wrap_t select_func_initial_key_wrap(rsip_key_type_extend_t key_type_ext)
{
    rsip_func_initial_key_wrap_t ret = NULL;

    switch (key_type_ext.alg)
    {
        case RSIP_PRV_ALG_AES:
        {
            ret = gsp_func_initial_key_wrap_aes[key_type_ext.subtype];
            break;
        }
        case RSIP_PRV_ALG_ECC_PUBLIC:
        {
            ret = gsp_func_initial_key_wrap_ecc_pub[key_type_ext.subtype];
            break;
        }

        case RSIP_PRV_ALG_ECC_PRIVATE:
        {
            ret = gsp_func_initial_key_wrap_ecc_priv[key_type_ext.subtype];
            break;
        }

        case RSIP_PRV_ALG_HMAC:
        {
            ret = gsp_func_initial_key_wrap_hmac[key_type_ext.subtype];
            break;
        }

        case RSIP_PRV_ALG_MISC:
        {
            ret = gsp_func_initial_key_wrap_misc[key_type_ext.subtype];
            break;
        }

        default:
        {
            /* Do nothing */
        }
    }

    return ret;
}

