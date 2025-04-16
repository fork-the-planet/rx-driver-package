/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/**********************************************************************************************************************
 * @file         rsa_api.c
 * @brief        RSA Library API source file.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include "r_rsa.h"
#include "mc_lib.h"
#include "rsa_internal_header.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
static int16_t make_rsapss_pkcs (R_RSA_BYTEDATA_t *p_mes, uint8_t *p_buff, uint16_t modn_len, uint8_t hash_type);
static int16_t valid_key_check (R_RSA_KEY_t *key);

/* HASH ObjectID */
/* MD2 */
const static uint8_t far hash_oid_md2[18] =
{ 0x30, 0x20, 0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x02, 0x05, 0x00, 0x04, 0x10 };
/* MD5 */
const static uint8_t far hash_oid_md5[18] =
{ 0x30, 0x20, 0x30, 0x0c, 0x06, 0x08, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x02, 0x05, 0x05, 0x00, 0x04, 0x10 };
/* SHA-1 */
const static uint8_t far hash_oid_sha1[15] =
{ 0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02, 0x1a, 0x05, 0x00, 0x04, 0x14 };
/* SHA-256 */
const static uint8_t far hash_oid_sha256[19] =
{ 0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20 };
/* SHA-384 */
const static uint8_t far hash_oid_sha384[19] =
{ 0x30, 0x41, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x02, 0x05, 0x00, 0x04, 0x30 };
/* SHA-512 */
const static uint8_t far hash_oid_sha512[19] =
{ 0x30, 0x51, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03, 0x05, 0x00, 0x04, 0x40 };

const static RSA_HASH_INFO_t far hash_info[RSA_HASH_TYPE_MAX] =
{
/* HASH ObjectID         , ObjectID Len           , hash size */
{ (uint8_t far *) hash_oid_md2, sizeof(hash_oid_md2), 16 },
{ (uint8_t far *) hash_oid_md5, sizeof(hash_oid_md5), 16 },
{ (uint8_t far *) hash_oid_sha1, sizeof(hash_oid_sha1), 20 },
{ (uint8_t far *) hash_oid_sha256, sizeof(hash_oid_sha256), 32 },
{ (uint8_t far *) hash_oid_sha384, sizeof(hash_oid_sha384), 48 },
{ (uint8_t far *) hash_oid_sha512, sizeof(hash_oid_sha512), 64 } };

/***********************************************************************************************************************
 Exported global function
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Declaration  : int16_t R_rsa_signature_generate_pkcs (R_RSA_BYTEDATA_t *p_mes, R_RSA_BYTEDATA_t *p_sig,
 *                R_RSA_KEY_t *p_key, uint8_t hash_type, R_RSA_WORK_t *p_wk)
 * Function Name: R_rsa_signature_generate_pkcs
 * Description  : Signature Generation (RSASSA-PKCS1-V1_5).
 * Arguments    : p_mes The message information to be signed.
 *              : p_sig Signature text storage destination information.
 *              : p_key Key information.
 *              : hash_type Hash method.
 *              : p_wk Work area.
 * Return Value : RSA_OK Normal end.
 *                RSA_PARAM_ERR  Parameter error end.
 *                RSA_USER_DEF_FUNC_ERR User definition function error end.
 *                RSA_SIG_GEN_NG Signature generation failed.
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_rsa_signature_generate_pkcs
 **************************************************************************//**
 * @brief Signature Generation (RSASSA-PKCS1-V1_5).
 * @param[in] p_mes The message information to be signed.
 * @param[in] p_key Key information.
 * @param[in] hash_type Hash method.
 * @param[in,out] p_sig Signature text storage destination information.
 * @param[in,out] p_wk Work area.
 * @retval RSA_OK Normal end.
 * @retval RSA_PARAM_ERR Parameter error end.
 * @retval RSA_USER_DEF_FUNC_ERR User definition function error end.
 * @retval RSA_SIG_GEN_NG Signature generation failed.
 * @details This API generates a signature according to RSASSA-PKCS1-V1_5.
 * @note none.
 */
int16_t R_rsa_signature_generate_pkcs (R_RSA_BYTEDATA_t *p_mes, R_RSA_BYTEDATA_t *p_sig, R_RSA_KEY_t *p_key,
        uint8_t hash_type, R_RSA_WORK_t *p_wk)
{
    RSA_WORK_INTERNAL_t *p_int_wk;
    int16_t api_ret;

    volatile memset_t memset_func = &memset;

    /* Checking arguments */
    if (0 != valid_key_check(p_key))
    {
        return RSA_PARAM_ERR;
    }

    if (RSA_HASH_TYPE_MAX <= hash_type)
    {
        /* Hash Type error */
        return RSA_PARAM_ERR;
    }

    if (p_key->key_n.len
            < (hash_info[hash_type].hash_oid_len + hash_info[hash_type].hash_len + RSA_RSASSA_PKCS_EM_MIN_LEN))
    {
        /* 9.2 EMSA-PKCS1-v1_5
         3. If emLen < tLen + 11, output "intended encoded message length too short" and stop. */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_mes)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_mes->p_adr)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_sig)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_sig->p_adr)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (p_sig->len < p_key->key_n.len)
    {
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_wk)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    /* Start processing */
    memset(p_wk, 0x00, sizeof(R_RSA_WORK_t));
    p_int_wk = (RSA_WORK_INTERNAL_t *) p_wk;

    /* RSASSA-PKCS1-v1_5 format creation */
    api_ret = make_rsapss_pkcs(p_mes, p_int_wk->format_buff[0], p_key->key_n.len, hash_type);
    if (RSA_OK != api_ret)
    {
        goto r_rsa_signature_generate_pkcs_finish;
    }

    p_int_wk->fbuff_bytedata[0].p_adr = p_int_wk->format_buff[0];
    p_int_wk->fbuff_bytedata[0].len = p_key->key_n.len;

    if (RSA_OK != R_rsa_mod_exp( &p_int_wk->fbuff_bytedata[0], p_sig, p_key, p_wk))
    {
        api_ret = RSA_SIG_GEN_NG;
        goto r_rsa_signature_generate_pkcs_finish;
    }

    api_ret = RSA_OK;

    /* End processing */
    r_rsa_signature_generate_pkcs_finish :
    {
        memset_func(p_wk, 0x00, sizeof(R_RSA_WORK_t));
        p_int_wk = 0;
    }
    return api_ret;

} /* End of function R_rsa_signature_generate_pkcs() */

/***********************************************************************************************************************
 * Declaration  : int16_t R_rsa_signature_verify_pkcs (R_RSA_BYTEDATA_t *p_sig, R_RSA_BYTEDATA_t *p_mes,
 *                R_RSA_KEY_t *p_key, uint8_t hash_type, R_RSA_WORK_t *p_wk)
 * Function Name: R_rsa_signature_verify_pkcs
 * Description  : Signature Verification (RSASSA-PKCS1-V1_5).
 * Arguments    : p_sig The signature information to be verified.
 *              : p_mes The message information to be verified.
 *              : p_key Key information.
 *              : hash_type Hash method.
 *              : p_wk Work area.
 * Return Value : RSA_OK Normal end.
 *                RSA_PARAM_ERR Parameter error end.
 *                RSA_USER_DEF_FUNC_ERR User definition function error end.
 *                RSA_SIG_VERIFY_NG Verification failed.
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_rsa_signature_verify_pkcs
 **************************************************************************//**
 * @brief Signature Generation (RSASSA-PKCS1-V1_5).
 * @param[in] p_sig The signature information to be verified.
 * @param[in] p_mes The message information to be verified.
 * @param[in] p_key Key information.
 * @param[in] hash_type Hash method.
 * @param[in,out] p_wk Work area.
 * @retval RSA_OK Normal end.
 * @retval RSA_PARAM_ERR Parameter error end.
 * @retval RSA_USER_DEF_FUNC_ERR User definition function error end.
 * @retval RSA_SIG_VERIFY_NG Verification failed.
 * @details This API verifies the signature according to RSASSA-PKCS1-V1_5.
 * @note none.
 */
int16_t R_rsa_signature_verify_pkcs (R_RSA_BYTEDATA_t *p_sig, R_RSA_BYTEDATA_t *p_mes, R_RSA_KEY_t *p_key,
        uint8_t hash_type, R_RSA_WORK_t *p_wk)
{
    RSA_WORK_INTERNAL_t *p_int_wk;
    int16_t api_ret;

    volatile memset_t memset_func = &memset;

    if (0 != valid_key_check(p_key))
    {
        return RSA_PARAM_ERR;
    }

    if (RSA_HASH_TYPE_MAX <= hash_type)
    {
        /* Hash Type error */
        return RSA_PARAM_ERR;
    }

    if (p_key->key_n.len
            < (hash_info[hash_type].hash_oid_len + hash_info[hash_type].hash_len + RSA_RSASSA_PKCS_EM_MIN_LEN))
    {
        /* 9.2 EMSA-PKCS1-v1_5
         3. If emLen < tLen + 11, output "intended encoded message length too short" and stop. */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_sig)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_sig->p_adr)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (p_sig->len != p_key->key_n.len)
    {
        /* 8.2.2 Signature verification operation
         1. Length checking: If the length of the signature S is not k octets, output "invalid signature" and stop. */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_mes)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_mes->p_adr)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_wk)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    /* Start processing */
    memset(p_wk, 0x00, sizeof(R_RSA_WORK_t));
    p_int_wk = (RSA_WORK_INTERNAL_t *) p_wk;

    p_int_wk->fbuff_bytedata[1].p_adr = p_int_wk->format_buff[1];
    p_int_wk->fbuff_bytedata[1].len = IO_DATA_BYTE_LENGTH;

    /* Execution of modular exponentiation */
    if (RSA_OK != R_rsa_mod_exp(p_sig, &p_int_wk->fbuff_bytedata[1], p_key, p_wk))
    {
        api_ret = RSA_SIG_VERIFY_NG;
        goto r_rsa_signature_verify_pkcs_finish;
    }

    /* Create encoded message for compare */
    api_ret = make_rsapss_pkcs(p_mes, p_int_wk->format_buff[0], p_key->key_n.len, hash_type);
    if (RSA_OK != api_ret)
    {
        goto r_rsa_signature_verify_pkcs_finish;
    }

    if (0 != memcmp(p_int_wk->format_buff[0], p_int_wk->format_buff[1], p_key->key_n.len))
    {
        api_ret = RSA_SIG_VERIFY_NG;
        goto r_rsa_signature_verify_pkcs_finish;
    }

    api_ret = RSA_OK;

    /* End processing */
    r_rsa_signature_verify_pkcs_finish :
    {
        memset_func(p_wk, 0x00, sizeof(R_RSA_WORK_t));
        p_int_wk = 0;
    }
    return api_ret;

} /* End of function R_rsa_signature_verify_pkcs() */

/***********************************************************************************************************************
 * Declaration  : int16_t R_rsa_mod_exp (R_RSA_BYTEDATA_t *p_input, R_RSA_BYTEDATA_t *p_output, R_RSA_KEY_t *p_key,
 *                R_RSA_WORK_t *p_wk)
 * Function Name: R_rsa_mod_exp
 * Description  : Modular exponentiation.
 * Arguments    : p_input Calculation information.
 *              : p_output Calculated data storage destination information.
 *              : p_key Exponent of modulus exponentiation ( e or d) and modulus (n) information.
 *              : p_wk Work area.
 * Return Value : RSA_OK Normal end.
 *                RSA_PARAM_ERR Parameter error end.
 *                RSA_MOD_EXP_NG Calculation failed.
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_rsa_mod_exp
 **************************************************************************//**
 * @brief Modular exponentiation.
 * @param[in] p_input Calculation information.
 * @param[in] p_key Exponent of modulus exponentiation ( e or d) and modulus (n) information.
 * @param[in,out] p_output Calculated data storage destination information.
 * @param[in,out] p_wk Work area.
 * @retval RSA_OK Normal end.
 * @retval RSA_PARAM_ERR Parameter error end.
 * @retval RSA_MOD_EXP_NG Calculation failed.
 * @details This API performs Modular exponentiation.
 * @note none.
 */
int16_t R_rsa_mod_exp (R_RSA_BYTEDATA_t *p_input, R_RSA_BYTEDATA_t *p_output, R_RSA_KEY_t *p_key, R_RSA_WORK_t *p_wk)
{
    RSA_EXPONENTIAL_t *p_expn_wk;
    int16_t ret;
    int16_t api_ret;

    volatile memset_t memset_func = &memset;

    /* Checking arguments */
    if (0 != valid_key_check(p_key))
    {
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_input)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_input->p_adr)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (0 == p_input->len)
    {
        return RSA_PARAM_ERR;
    }

    if (p_key->key_n.len < p_input->len)
    {
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_output)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_output->p_adr)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    if (p_key->key_n.len > p_output->len)
    {
        return RSA_PARAM_ERR;
    }

    if (RSA_NULL == p_wk)
    {
        /* Null Pointer */
        return RSA_PARAM_ERR;
    }

    /* Start processing */
    p_expn_wk = &((RSA_WORK_INTERNAL_t *) p_wk)->expn;
    memset(p_expn_wk, 0x00, sizeof(RSA_EXPONENTIAL_t));

    p_expn_wk->work2_bytedata.p_adr = p_expn_wk->work2;
    p_expn_wk->work2_bytedata.len = IO_DATA_BYTE_LENGTH;

    p_expn_wk->mc_p.len = MC_INT_ARRAY_LENGTH;
    p_expn_wk->mc_p.val = (MC *) p_expn_wk->sdl_memory[0]; /* object is holds the even alignment */

    p_expn_wk->mc_a.len = MC_INT_ARRAY_LENGTH;
    p_expn_wk->mc_a.val = (MC *) p_expn_wk->sdl_memory[1]; /* object is holds the even alignment */

    p_expn_wk->mc_b.len = MC_INT_ARRAY_LENGTH;
    p_expn_wk->mc_b.val = (MC *) p_expn_wk->sdl_memory[2]; /* object is holds the even alignment */

    p_expn_wk->mc_c.len = MC_INT_ARRAY_LENGTH;
    p_expn_wk->mc_c.val = (MC *) p_expn_wk->sdl_memory[3]; /* object is holds the even alignment */

    /* Storing an array of one byte MC_int variable */
    ret = MC_byte2mc(p_key->key_n.p_adr, p_key->key_n.len, &p_expn_wk->mc_p);
    if (0 != ret)
    {
        api_ret = RSA_MOD_EXP_NG;
        goto r_rsa_mod_exp_finish;
    }

    ret = MC_byte2mc(p_input->p_adr, p_input->len, &p_expn_wk->mc_a);
    if (0 != ret)
    {
        api_ret = RSA_MOD_EXP_NG;
        goto r_rsa_mod_exp_finish;
    }

    ret = MC_byte2mc(p_key->key_ed.p_adr, p_key->key_ed.len, &p_expn_wk->mc_b);
    if (0 != ret)
    {
        api_ret = RSA_MOD_EXP_NG;
        goto r_rsa_mod_exp_finish;
    }

    if (0 >= MC_cmpl( &p_expn_wk->mc_a, &p_expn_wk->mc_p))
    {
        api_ret = RSA_MOD_EXP_NG;
        goto r_rsa_mod_exp_finish;
    }

    /* Modular exponentiation */
    ret = MC_powm( &p_expn_wk->mc_a, &p_expn_wk->mc_b, &p_expn_wk->mc_c, &p_expn_wk->mc_p,
            (uint8_t *) &p_expn_wk->MC_memory[0], (uint8_t *) &p_expn_wk->MC_memory[1]);
    if (0 != ret)
    {
        api_ret = RSA_MOD_EXP_NG;
        goto r_rsa_mod_exp_finish;
    }

    /* Output results are temporarily stored in the work */
    memset(p_expn_wk->work2_bytedata.p_adr, 0x00, p_expn_wk->work2_bytedata.len);
    ret = MC_mc2byte( &p_expn_wk->mc_c, p_expn_wk->work2_bytedata.p_adr, &p_expn_wk->work2_bytedata.len);
    if (0 != ret)
    {
        api_ret = RSA_MOD_EXP_NG;
        goto r_rsa_mod_exp_finish;
    }

    /* Output result =>  User memory */
    memcpy(p_output->p_adr, p_expn_wk->work2_bytedata.p_adr + (IO_DATA_BYTE_LENGTH - p_key->key_n.len),
            p_key->key_n.len);
    p_output->len = p_key->key_n.len;

    api_ret = RSA_OK;

    r_rsa_mod_exp_finish :
    {
        memset_func(p_expn_wk, 0x00, sizeof(RSA_EXPONENTIAL_t));
        p_expn_wk = 0;
        ret = 0;
    }
    return api_ret;

} /* End of function R_rsa_mod_exp() */

/***********************************************************************************************************************
 * Declaration  : int16_t valid_key_check (R_RSA_KEY_t *key)
 * Function Name: valid_key_check
 * Description  : Check if the key information is valid.
 * Arguments    : key Key information.
 * Return Value : 0  Normal end.
 *                -1 Parameter error end.
 **********************************************************************************************************************/
static int16_t valid_key_check (R_RSA_KEY_t *key)
{
    if (RSA_NULL == key)
    {
        /* Null Address */
        return -1;
    }
    /* Key N length check */
    if (0 == key->key_n.len)
    {
        /* Key length is invalid */
        return -1;
    }
    if (IO_DATA_BYTE_LENGTH < key->key_n.len)
    {
        /* Key length is invalid */
        return -1;
    }

    /* Address check of key_n.p_adr */
    if (RSA_NULL == key->key_n.p_adr)
    {
        /* Null Address */
        return -1;
    }
    /* Check the value of the address pointed to by key_n.p_adr */
    if (0x00 == ( *key->key_n.p_adr))
    {
        /* Value is 0x00 */
        return -1;
    }

    /* Key EorD length check */
    if (0 == key->key_ed.len)
    {
        /* Key length is invalid */
        return -1;
    }
    if (IO_DATA_BYTE_LENGTH < key->key_ed.len)
    {
        /* Key length is invalid */
        return -1;
    }

    /* Address check of key_ed.p_adr */
    if (RSA_NULL == key->key_ed.p_adr)
    {
        /* null Address */
        return -1;
    }

    /* Check the value of the address pointed to by key_ed.p_adr */
    if (0x00 == ( *key->key_ed.p_adr))
    {
        /* value is 0x00 */
        return -1;
    }
    return 0;
} /* End of function valid_key_check() */

/***********************************************************************************************************************
 * Declaration  : int16_t make_rsapss_pkcs (R_RSA_BYTEDATA_t *p_mes, uint8_t *p_buff, uint16_t modn_len,
 *                uint8_t hash_type)
 * Function Name: make_rsapss_pkcs
 * Description  : RSAPSS_PKCS1_V1_5 Signature Generation.
 * Arguments    : p_mes The message information to be signed.
 *              : p_buff Storage location.
 *              : modn_len Effective number of bytes for modulus n (= length of encoded message).
 *              : hash_type Hash method.
 * Return Value : RSA_OK Normal end.
 *                RSA_USER_DEF_FUNC_ERR User definition function error end.
 **********************************************************************************************************************/
static int16_t make_rsapss_pkcs (R_RSA_BYTEDATA_t *p_mes, uint8_t *p_buff, uint16_t modn_len, uint8_t hash_type)
{
    uint8_t far *p_buff_f;
    uint16_t len;

    /* RSASSA-PKCS1-v1_5 format creation */

    /*       (1)   |  (2)   | (3)  |  (4)   | (5) ::      (5-1) | (5-2) */
    /* EM = [0x00] | [0x01] | [PS] | [0x00] | [T] ::  T = [OID] |  [H]  */

    /* (1) */
    *p_buff = 0x00;
    p_buff++;

    /* (2) */
    *p_buff = 0x01;
    p_buff++;

    /* (3) *//* "3" is (1)+(2)+(4) */
    memset(p_buff, 0xff, modn_len - (3 + hash_info[hash_type].hash_oid_len + hash_info[hash_type].hash_len));
    p_buff += (modn_len - (3 + hash_info[hash_type].hash_oid_len + hash_info[hash_type].hash_len));

    /* (4) */
    *p_buff = 0x00;
    p_buff++;
    /* (5-1) */
    for (len = hash_info[hash_type].hash_oid_len, p_buff_f = hash_info[hash_type].p_hash_oid; len > 0; --len)
    {
        *p_buff++ = *p_buff_f++;
    }
    /* (5-2) */
    if (0 != R_rsa_if_hash(p_mes->p_adr, p_buff, p_mes->len, hash_type))
    {
        return RSA_USER_DEF_FUNC_ERR;
    }

    /* Erase data for safety */
    p_buff_f = NULL;
    len = 0;

    return RSA_OK;

} /* End of function make_rsapss_pkcs() */

#if defined(_RSALIB_DEBUG_)
/***********************************************************************************************************************
 * Declaration  : uint32_t rsalib_worksize(void)
 * Function Name: rsalib_worksize.
 * Description  : Check work usage.
 * Arguments    : none.
 * Return Value : uint32_t Work usage.
 **********************************************************************************************************************/
uint32_t rsalib_worksize(void)
{
    return (uint32_t)sizeof(RSA_WORK_INTERNAL_t);
} /* End of function rsalib_worksize() */
#endif
