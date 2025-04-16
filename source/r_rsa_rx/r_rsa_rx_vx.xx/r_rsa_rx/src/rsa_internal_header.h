/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/**********************************************************************************************************************
 * @file         rsa_internal_header.h
 * @brief        RSA Library header file.
 **********************************************************************************************************************/

/* Include mc_lib.h before including this file */
#ifndef RSA_INTERNAL_HEADER_H
    #define RSA_INTERNAL_HEADER_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
    #include "r_rsa.h"
    #include "r_stdint.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* Define the maximum value of RSA_HASH_XXXXX in r_rsa.h + 1 */
    #define RSA_HASH_TYPE_MAX ((uint8_t)0x06)  /* MAX */

/* Null Pointer */
    #define RSA_NULL (0)

/* RSA encryption/ decryption  Minimum key size of RSAES-PKCS1_V1_5 */
    #define RSA_RSAES_PKCS_MIN_KEY_N_LEN (11)

/* RSA signature generation/ verification Minimum size of RSASSA-PKCS1_V1_5 encoded message excluding [T] */
    #define RSA_RSASSA_PKCS_EM_MIN_LEN (11)

    #if MC_BASE==16
        #define SDL_MEMORY_SIZE ((IO_DATA_BYTE_LENGTH*2)+2) /* 514 Bytes */
    #else
        #define SDL_MEMORY_SIZE ((IO_DATA_BYTE_LENGTH*2)+4) /* 516 Bytes */
    #endif /*  MC_BASE==16 */

typedef struct
{
    uint8_t sdl_memory[4][SDL_MEMORY_SIZE];
    MC_int mc_p; /* Law p */
    MC_int mc_a; /* Bottom a */
    MC_int mc_b; /* Power exponent b */
    MC_int mc_c; /* Calculation result c */
    R_RSA_BYTEDATA_t work2_bytedata;
    union
    {
        uint8_t work2[512]; /* For PKCS */
        uint8_t MC_memory[MC_MEMORY_NUM][MC_MEMORY_SIZE];
    };
} RSA_EXPONENTIAL_t;

typedef struct
{
    uint8_t           format_buff[2][IO_DATA_BYTE_LENGTH]; /* PKCS format data creation part */
    R_RSA_BYTEDATA_t  fbuff_bytedata[2]; /* R_RSA_BYTEDATA_t of format_buff */
    RSA_EXPONENTIAL_t expn; /* Area used for modular exponentiation */
} RSA_WORK_INTERNAL_t;

typedef struct
{
    uint8_t  far *p_hash_oid; /* Start address of DER encoded object ID (HashDigest) */
    uint16_t hash_oid_len; /* HashDigest byte length */
    uint16_t hash_len; /* Hash value byte length */
} RSA_HASH_INFO_t;


/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
#endif /* define RSA_INTERNAL_HEADER_H */
