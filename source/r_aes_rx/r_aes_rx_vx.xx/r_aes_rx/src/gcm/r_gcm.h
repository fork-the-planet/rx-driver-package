/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         r_gcm.h
 * @brief        GCM Library header file.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_stdint.h"
#include "r_mw_version.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#ifndef R_GCM_H
    #define R_GCM_H

    #define GCM_OK              (0)
    #define GCM_NG              (-1)

    #define GCM_BLOCK_SIZE      (16)
    #define GCM_WORK_SIZE_L     (39) /* 39 lword (156 byte) */

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/


/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/
extern const mw_version_t far R_gcm_version;

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
/* interface function */
/* Function Name: R_gcm_enc */
/******************************************************************************************************************//**
 * @brief         GCM Encryption Function.
 * @warning       When input data, plain and aad are not aligned 16byte, the padding process is executed in this
 *                function. The key size depends on block cipher algorithmWhen an invalid pointer (ex. NULL) or odd
 *                address is passed as a parameter, the functions behavior is undefined. When data_len = 0, this
 *                function does not use plain and cipher. This case, output authentication tag is called as GMAC
 *                value. When aad_len = 0, this function does not use aad. It is possible to allocate plain text area
 *                and cipher text area in same address. (If these areas are not completely overlap, the function
 *                behavior is not defined.)
 * @retval        0 Normal termination.
 * @retval        -1 Abnormal termination (atag_len=0, iv_len=0).
 *********************************************************************************************************************/
int32_t R_gcm_enc (uint8_t near *plain, uint8_t near *cipher, uint32_t data_len, uint8_t near *key, uint8_t near *atag,
        uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len);

/* Function Name: R_gcm_dec */
/******************************************************************************************************************//**
 * @brief         GCM Decryption Function.
 * @warning       When input data, plain and aad are not aligned 16byte, the padding process is executed in this
 *                function. The key size depends on block cipher algorithm. When an invalid pointer (ex. NULL) or odd
 *                address is passed as a parameter, the functions behavior is undefined. When data_len = 0, this
 *                function does not use plain and cipher. This case, input authentication tag would be verified as GMAC
 *                value. When aad_len = 0, this function does not use aad. It is possible to allocate plain text area
 *                and cipher text area in same address. (If these areas are not completely overlap, the function
 *                behavior is not defined).
 * @retval        0 Successful authentication.
 * @retval        -1 Failure authentication or illegal termination (atag_len=0, iv_len=0).
 *********************************************************************************************************************/
int32_t R_gcm_dec (uint8_t near *cipher, uint8_t near *plain, uint32_t data_len, uint8_t near *key, uint8_t near *atag,
        uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len);

/* Function Name: R_gcm_enc_start */
/******************************************************************************************************************//**
 * @brief         GCM Start Encryption Function.
 * @warning       When input data, plain and aad are not aligned 16byte, the padding process is executed in this
 *                function. The key size depends on block cipher algorithm. When an invalid pointer (ex. NULL) or odd
 *                address is passed as a parameter, the functions behavior is undefined. When data_len = 0, this
 *                function does not use plain and cipher. This case, output authentication tag is called as GMAC value.
 *                When aad_len = 0, this function does not use aad. It is possible to allocate plain text area and
 *                cipher text area in same address. (If these areas are not completely overlap, the function behavior is
 *                not defined). The temporary data will store to work, please clear work area after all data encryption.
 * @retval        positive value Normal termination. The times to call GCM Repeat Function for all block encryption
 *                completion.
 * @retval        -1 Abnormal termination (atag_len=0, iv_len=0, div_block_num=0).
 *********************************************************************************************************************/
int32_t R_gcm_enc_start (uint8_t near *plain, uint8_t near *cipher, uint32_t data_len, uint8_t near *key,
        uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len,
        uint32_t div_block_num, uint32_t near *work);

/* Function Name: R_gcm_dec_start */
/******************************************************************************************************************//**
 * @brief         GCM Start Decryption Function.
 * @warning       When input data, plain and aad are not aligned 16byte, the padding process is executed in this
 *                function. The key size depends on block cipher algorithm. When an invalid pointer (ex. NULL) or odd
 *                address is passed as a parameter, the functions behavior is undefined. When data_len = 0, this
 *                function does not use plain and cipher. This case, input authentication tag would be verified as GMAC
 *                value. When aad_len = 0, this function does not use aad. It is possible to allocate plain text area
 *                and cipher text area in same address. (If these areas are not completely overlap, the function
 *                behavior is not defined). The temporary data will store to work, please clear work area after all data
 *                encryption.
 * @retval        positive value Normal termination. The times to call GCM Repeat Function for all block encryption
 *                completion.
 * @retval        -1 Abnormal termination (atag_len=0, iv_len=0, div_block_num=0).
 *********************************************************************************************************************/
int32_t R_gcm_dec_start (uint8_t near *cipher, uint8_t near *plain, uint32_t data_len, uint8_t near *key,
        uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len,
        uint32_t div_block_num, uint32_t near *work);

/* Function Name: R_gcm_repeat */
/******************************************************************************************************************//**
 * @brief         Restarts the pending GCM processing.
 * @warning       none.
 * @retval        positive value Normal termination. The times to call GCM Repeat Function for all block encryption
 *                completion.
 * @retval        0 Successful authentication and  all encryption/decryption.
 * @retval        -1 Failure authentication or illegal termination. (No call GCM Start Encryption/Decryption Function).
 *********************************************************************************************************************/
int32_t R_gcm_repeat (uint32_t near *work);

/* cipher driver function (user definition) */
/* Function Name: R_gcm_encrypt_plain_block */
/******************************************************************************************************************//**
 * @brief         Data Block Encryption Function for GCM.
 * @warning       This function is not needed for no GCM system. The key size depends on block cipher algorithm.
 * @retval        0 Normal termination.
 * @retval        -1 Abnormal termination.
 *********************************************************************************************************************/
int32_t R_gcm_encrypt_plain_block (uint8_t near *plain, uint8_t near *key);


/* Function Name: R_clear_keyLength */
/******************************************************************************************************************//**
 * @brief         Clear key length.
 * @warning       When an invalid pointer (ex. Null Pointer) is passed as a parameter, the functions behavior is
 *                undefined. It is possible to allocate plain text area and cipher text area in same address. (If these
 *                areas are not completely overlap, the function behavior is not defined).
 * @retval        none.
 *********************************************************************************************************************/
void R_clear_keyLength (void);

/* Function Name: R_set_keyLength  */
/******************************************************************************************************************//**
 * @brief         Set key length.
 * @warning       When an invalid pointer (ex. Null Pointer) is passed as a parameter, the functions behavior is
 *                undefined. It is possible to allocate plain text area and cipher text area in same address. (If these
 *                areas are not completely overlap, the function behavior is not defined).
 * @retval        none.
 *********************************************************************************************************************/
uint32_t R_set_keyLength (uint32_t n);
#endif /* R_GCM_H */
