/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************************************************//**
 * @ingroup RENESAS_SECURITY_INTERFACES
 * @defgroup RSIP_CM_API_Summary RSIP Interface
 * @brief Interface for Renesas Secure IP (RSIP) functions.
 *
 * @section RSIP_CM_API_Summary Summary
 * The RSIP interface provides RSIP functionality.
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_RSIP_CM_RX_HEADER_FILE
#define R_RSIP_CM_RX_HEADER_FILE

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_bsp/platform.h"
#include "r_rsip_cm_rx_config.h"
#include "r_sce_if.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif
#if (defined BSP_MCU_RX231 || defined BSP_MCU_RX23W || \
    defined BSP_MCU_RX261) && (BSP_CFG_MCU_PART_VERSION == 0xB) /* B */
#elif (defined BSP_MCU_RX66T || defined BSP_MCU_RX72T) && ((BSP_CFG_MCU_PART_FUNCTION == 0xE /* E */) || \
    (BSP_CFG_MCU_PART_FUNCTION == 0xF /* F */) || (BSP_CFG_MCU_PART_FUNCTION == 0x10 /* G */))
#elif (defined BSP_MCU_RX65N || defined BSP_MCU_RX651) && (BSP_CFG_MCU_PART_ENCRYPTION_INCLUDED == true)
#elif (defined BSP_MCU_RX72M || defined BSP_MCU_RX72N || defined BSP_MCU_RX66N) && \
    (BSP_CFG_MCU_PART_FUNCTION == 0x11 /* H */)
#else
    #error "Your MCU does not support SCE functions. Please confirm BSP_MCU_xxx macro in r_bsp_config.h."
#endif  /* defined BSP_MCU_RX231 || defined BSP_MCU_RX23W && BSP_CFG_MCU_PART_VERSION == 0xB */

/* For AES operation. */
#define R_RSIP_CM_AES256_KEY_INDEX_WORD_SIZE             (13U)

/* For HMAC operation. */
#define R_RSIP_CM_HMAC_SHA256_KEY_INDEX_WORD_SIZE        (13U)

/* For ECC operation. */
#define R_RSIP_CM_ECCP256_PUBLIC_KEY_INDEX_WORD_SIZE     (16U)
#define R_RSIP_CM_ECCP256_PRIVATE_KEY_INDEX_WORD_SIZE    (13U)

#define R_RSIP_CM_VERSION_MAJOR                          (1U)
#define R_RSIP_CM_VERSION_MINOR                          (0U)

/**********************************************************************************************************************
 * Global Typedef definitions
 *********************************************************************************************************************/
/** Key injection type. */
typedef enum e_rsip_key_injection_type
{
    RSIP_KEY_INJECTION_TYPE_ENCRYPTED = 0, ///< Input encrypted user key
    RSIP_KEY_INJECTION_TYPE_PLAIN     = 1, ///< Input plain user key
} rsip_key_injection_type_t;

/** AES128/256 wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_aes_wrapped_key
{
    uint32_t type;                                        ///< Key type
    uint32_t value[R_RSIP_CM_AES256_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_aes_wrapped_key_t;

/** ECC 256 public wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_ecc_public_wrapped_key
{
    uint32_t type;                                                ///< Key type
    uint32_t value[R_RSIP_CM_ECCP256_PUBLIC_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_ecc_public_wrapped_key_t;

/** ECC 256 private wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_ecc_private_wrapped_key
{
    uint32_t type;                                                 ///< Key type
    uint32_t value[R_RSIP_CM_ECCP256_PRIVATE_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_ecc_private_wrapped_key_t;

/** HMAC 256 wrapped key data structure. DO NOT MODIFY. */
typedef struct rsip_hmac_sha_wrapped_key
{
    uint32_t type;                                             ///< Key type
    uint32_t value[R_RSIP_CM_HMAC_SHA256_KEY_INDEX_WORD_SIZE]; ///< Wrapped key value
} rsip_hmac_sha_wrapped_key_t;

/** Functions API. */
typedef struct st_rsip_key_injection_api
{
    /**
     * Returns the version of this module.
     *
     * @param[in,out]  none.
     */
    uint32_t (* getversion)(void);

    /** This API outputs 128-bit AES wrapped key.
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
     * it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           128-bit AES wrapped key
    */
    fsp_err_t (* AES128_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key,
                                        rsip_aes_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit AES wrapped key.
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
     *                                                     it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit AES wrapped key
     */
    fsp_err_t (* AES256_InitialKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const p_wrapped_user_factory_programming_key,
                                        uint8_t const * const p_initial_vector,
                                        uint8_t const * const p_user_key,
                                        rsip_aes_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit ECC wrapped private key.
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
     *                                                     it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_secp256r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                uint8_t const * const p_wrapped_user_factory_programming_key,
                                                uint8_t const * const p_initial_vector,
                                                uint8_t const * const p_user_key,
                                                rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit ECC wrapped private key.
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
     *                                                     it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_secp256k1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                uint8_t const * const p_wrapped_user_factory_programming_key,
                                                uint8_t const * const p_initial_vector,
                                                uint8_t const * const p_user_key,
                                                rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

    /** This API outputs 256-bit brainpool ECC wrapped private key.
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
     *                                                     it must be encrypted and have MAC appended.
     * @param[out] p_wrapped_key                           256-bit ECC wrapped private key
     */
    fsp_err_t (* ECC_brainpoolP256r1_InitialPrivateKeyWrap)(rsip_key_injection_type_t const key_injection_type,
                                                uint8_t const * const p_wrapped_user_factory_programming_key,
                                                uint8_t const * const p_initial_vector,
                                                uint8_t const * const p_user_key,
                                                rsip_ecc_private_wrapped_key_t * const p_wrapped_key);
} rsip_key_injection_api_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif  /* R_RSIP_CM_RX_HEADER_FILE */

