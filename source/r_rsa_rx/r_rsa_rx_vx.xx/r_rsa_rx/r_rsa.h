/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/**********************************************************************************************************************
 * @file         r_rsa.h
 * @brief        RSA Library header file.
 **********************************************************************************************************************/
#ifndef R_RSA_H
    #define R_RSA_H
    
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_stdint.h"
#include "r_mw_version.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/* Return Value */
    #define RSA_OK                  (0)   /* Sucessful                     */
    #define RSA_PARAM_ERR           (-1)  /* Paramter Error                */
    #define RSA_USER_DEF_FUNC_ERR   (-2)  /* User definiton function Error */
    #define RSA_MOD_EXP_NG          (-3)  /* modulo exponnention API NG    */
    #define RSA_ENC_NG              (-4)  /* Encode API NG                 */
    #define RSA_DEC_NG              (-5)  /* Decode API NG                 */
    #define RSA_SIG_GEN_NG          (-6)  /* Signature genearate API NG    */
    #define RSA_SIG_VERIFY_NG       (-7)  /* Signature verify API NG       */

/* Hash type */
    #define RSA_HASH_MD2      ((uint8_t)0x00)  /* MD2               */
    #define RSA_HASH_MD5      ((uint8_t)0x01)  /* MD5               */
    #define RSA_HASH_SHA1     ((uint8_t)0x02)  /* SHA-1             */
    #define RSA_HASH_SHA256   ((uint8_t)0x03)  /* SHA-256           */
    #define RSA_HASH_SHA384   ((uint8_t)0x04)  /* SHA-384           */
    #define RSA_HASH_SHA512   ((uint8_t)0x05)  /* SHA-512           */

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef struct
{
    uint8_t  *p_adr;
    uint16_t len;
} R_RSA_BYTEDATA_t;

typedef struct
{
    uint32_t work[(3680 / sizeof(uint32_t))];
} R_RSA_WORK_t;

typedef struct
{
    R_RSA_BYTEDATA_t key_n;
    R_RSA_BYTEDATA_t key_ed;
} R_RSA_KEY_t;

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/
extern const mw_version_t far R_rsa_version;

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
/* API */
/* Function Name: R_rsa_mod_exp */
/******************************************************************************************************************//**
 * @brief         Modular exponentiation.
 * @warning       none.
 * @retval        RSA_OK Normal end.
 * @retval        RSA_PARAM_ERR Parameter error end.
 * @retval        RSA_MOD_EXP_NG Calculation failed.
 *********************************************************************************************************************/
int16_t R_rsa_mod_exp (R_RSA_BYTEDATA_t *p_input, R_RSA_BYTEDATA_t *p_output, R_RSA_KEY_t *p_key, R_RSA_WORK_t *p_wk);

/* Function Name: R_rsa_signature_generate_pkcs */
/******************************************************************************************************************//**
 * @brief         Signature Generation (RSASSA-PKCS1-V1_5).
 * @warning       none.
 * @retval        RSA_OK Normal end.
 * @retval        RSA_PARAM_ERR Parameter error end.
 * @retval        RSA_USER_DEF_FUNC_ERR User definition function error end.
 * @retval        RSA_SIG_GEN_NG Signature generation failed.
 *********************************************************************************************************************/
int16_t R_rsa_signature_generate_pkcs (R_RSA_BYTEDATA_t *p_mes, R_RSA_BYTEDATA_t *p_sig, R_RSA_KEY_t *p_key,
        uint8_t hash_type, R_RSA_WORK_t *p_wk);

/* Function Name: R_rsa_signature_verify_pkcs */
/******************************************************************************************************************//**
 * @brief         Signature Verification (RSASSA-PKCS1-V1_5).
 * @warning       none.
 * @retval        RSA_OK Normal end.
 * @retval        RSA_PARAM_ERR Parameter error end.
 * @retval        RSA_USER_DEF_FUNC_ERR User definition function error end.
 * @retval        RSA_SIG_VERIFY_NG Verification failed.
 *********************************************************************************************************************/
int16_t R_rsa_signature_verify_pkcs (R_RSA_BYTEDATA_t *p_sig, R_RSA_BYTEDATA_t *p_mes, R_RSA_KEY_t *p_key,
        uint8_t hash_type, R_RSA_WORK_t *p_wk);

/* User Definition Function */
/* Function Name: R_rsa_if_hash */
/******************************************************************************************************************//**
 * @brief         Calculate Hash.
 * @warning       none.
 * @retval        0 Hash calculation successful.
 * @retval        Other than 0 Hash calculation failed
 *********************************************************************************************************************/
int16_t R_rsa_if_hash (uint8_t *p_mes, uint8_t *p_hash, uint16_t mes_len, uint8_t hash_type);

#endif /* define R_RSA_H */
