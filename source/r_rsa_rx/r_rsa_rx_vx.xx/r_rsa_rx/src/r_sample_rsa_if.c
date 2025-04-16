/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * File Name    : r_sample_rsa_if.c
 * Description  : Sample program of User Definition Functions.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stdint.h>
#include <string.h>
#include "r_rsa.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#define USE_SHA_LIB         (0)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
#if USE_SHA_LIB
    #include "r_sha.h"
#else
static const uint8_t Sha1_HashDigest[20] =
{   0xDD, 0x57, 0x83, 0xBC, 0xF1, 0xE9, 0x00, 0x2B, 0xC0, 0x0A, 0xD5, 0xB8, 0x3A, 0x95, 0xED, 0x6E, 0x4E, 0xBB,
    0x4A, 0xD5 };

static const uint8_t Sha256_HashDigest[32] =
{   0x66, 0x84, 0x0D, 0xDA, 0x15, 0x4E, 0x8A, 0x11, 0x3C, 0x31, 0xDD, 0x0A, 0xD3, 0x2F, 0x7F, 0x3A, 0x36, 0x6A, 0x80,
    0xE8, 0x13, 0x69, 0x79, 0xD8, 0xF5, 0xA1, 0x01, 0xD3, 0xD2, 0x9D, 0x6F, 0x72 };
#if !(defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__))
static const uint8_t Sha384_HashDigest[48] =
{   0x9B, 0x11, 0x0B, 0xBC, 0x74, 0x1B, 0xB6, 0x6A, 0xC0, 0x9E, 0xD8, 0xE0, 0x66, 0xE3, 0x48, 0x99, 0x0C, 0x5D, 0xBD,
        0xB7, 0x40, 0x6A, 0x2B, 0xDF, 0x8D, 0x77, 0x16, 0x73, 0x64, 0x82, 0x0E, 0x06, 0xB5, 0xC7, 0x8B, 0x53, 0xF8,
        0x20, 0x15, 0xa7, 0x88, 0x77, 0x86, 0x62, 0x83, 0x74, 0xE6, 0xAE };
#endif
#endif  /* defined USE_SHA_LIB */

/***********************************************************************************************************************
 * Function Name: R_rsa_if_hash
 * Description  : Sample program of R_rsa_if_hash().
 * Arguments    : p_mes Start address of message.
 *                p_hash Hash calculation result storage address.
 *                mes_len Valid byte count of message.
 *                hash_type Hash type.
 * Return Value : 0 Hash calculation successful.
 *                Other than 0 Hash calculation failed.
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_rsa_if_hash
 **************************************************************************//**
 * @brief Calculate Hash.
 * @param[in] p_mes Start address of message.
 * @param[out] p_hash Hash calculation result storage address.
 * @param[in] mes_len Valid byte count of message
 * @param[in] hash_type Hash type.
 * @retval 0 Hash calculation successful.
 * @retval Other than 0 Hash calculation failed.
 * @details This function must be implemented in order to run 
 * R_rsa_signature_generate() and R_rsa_signature_verify(). The hash is
 * calculated for the number of bytes of data specified by the argument mes_len,
 * starting from the address specified by the argument p_mes. The hash method is
 * specified by the argument hash. The calculation result should be stored at
 * the address specified by the argument p_hash. The calculation result and the
 * size of the stored calculation result differ depending on the hash method.
 * @note none.
 */
#if !(defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__))
int16_t R_rsa_if_hash (uint8_t *p_mes, uint8_t *p_hash, uint16_t mes_len, uint8_t hash_type)
#else
int16_t R_rsa_if_hash (uint8_t near *p_mes, uint8_t near *p_hash, uint16_t mes_len, uint8_t hash_type)
#endif /* !(defined__RL78__ || defined__ICCRL78__ || defined__CCRL__) */
{
#if USE_SHA_LIB
    R_sha_handle sha_work;
#endif /* defined USE_SHA_LIB */

    switch (hash_type)
    {
        case RSA_HASH_SHA1:
#if USE_SHA_LIB
            if (R_Sha1_HashDigest(p_mes, p_hash, mes_len, (R_SHA_INIT | R_SHA_FINISH),
                    (void *) &sha_work) != R_PROCESS_COMPLETE)
            {
                return -1;
            }
#else
            memcpy(p_hash, Sha1_HashDigest, 20); /* Preliminary */
#endif /* defined USE_SHA_LIB */
        break;
        case RSA_HASH_SHA256:
#if USE_SHA_LIB
            if (R_Sha256_HashDigest(p_mes, p_hash, mes_len, (R_SHA_INIT | R_SHA_FINISH),
                    (void *) &sha_work) != R_PROCESS_COMPLETE)
            {
                return -1;
            }
#else
            memcpy(p_hash, Sha256_HashDigest, 32); /* Preliminary */
#endif /* defined USE_SHA_LIB */
        break;
#if !(defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__))
        case RSA_HASH_SHA384:
#if USE_SHA_LIB

            if (R_Sha384_HashDigest(p_mes, p_hash, mes_len, (R_SHA_INIT | R_SHA_FINISH),
                    (void *) &sha_work) != R_PROCESS_COMPLETE)
            {
                return -1;
            }
#else
            memcpy(p_hash, Sha384_HashDigest, 48); /* Preliminary */
#endif /* defined USE_SHA_LIB */
        break;
#endif
        case RSA_HASH_MD2:
        case RSA_HASH_MD5:
        case RSA_HASH_SHA512:
        default:
            return -1;
    }
    return 0;
} /* End of function R_rsa_if_hash() */

