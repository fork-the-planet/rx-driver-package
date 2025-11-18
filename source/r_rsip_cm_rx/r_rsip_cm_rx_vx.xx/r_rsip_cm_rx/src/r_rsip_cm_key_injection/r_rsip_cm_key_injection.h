/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RSIP_CM_KEY_INJECTION
 * @{
 **********************************************************************************************************************/

#ifndef R_RSIP_CM_KEY_INJECTION_H
#define R_RSIP_CM_KEY_INJECTION_H

#include "r_rsip_cm_rx_if.h"
#include "hw_sce_rx_private.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rsip_key_injection_api_t g_rsip_key_injection_on_rsip;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 *********************************************************************************************************************/
uint32_t R_RSIP_CM_GetVersion (void);

fsp_err_t R_RSIP_CM_AES128_InitialKeyWrap (rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const           p_wrapped_user_factory_programming_key,
                                        uint8_t const * const           p_initial_vector,
                                        uint8_t const * const           p_user_key,
                                        rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_CM_AES256_InitialKeyWrap (rsip_key_injection_type_t const key_injection_type,
                                        uint8_t const * const           p_wrapped_user_factory_programming_key,
                                        uint8_t const * const           p_initial_vector,
                                        uint8_t const * const           p_user_key,
                                        rsip_aes_wrapped_key_t * const  p_wrapped_key);

fsp_err_t R_RSIP_CM_ECC_secp256r1_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                        uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                        uint8_t const * const                  p_initial_vector,
                                        uint8_t const * const                  p_user_key,
                                        rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_CM_ECC_secp256k1_InitialPrivateKeyWrap (rsip_key_injection_type_t const        key_injection_type,
                                        uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                        uint8_t const * const                  p_initial_vector,
                                        uint8_t const * const                  p_user_key,
                                        rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

fsp_err_t R_RSIP_CM_ECC_brainpoolP256r1_InitialPrivateKeyWrap (rsip_key_injection_type_t const   key_injection_type,
                                        uint8_t const * const                  p_wrapped_user_factory_programming_key,
                                        uint8_t const * const                  p_initial_vector,
                                        uint8_t const * const                  p_user_key,
                                        rsip_ecc_private_wrapped_key_t * const p_wrapped_key);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif  /* R_RSIP_CM_KEY_INJECTION_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RSIP_CM_KEY_INJECTION)
 **********************************************************************************************************************/
