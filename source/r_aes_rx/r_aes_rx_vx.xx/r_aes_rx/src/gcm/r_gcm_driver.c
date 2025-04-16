/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * File Name    : r_gcm_driver.c
 * Description  : This is an example of GCM Driver which combined AES Library.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "r_gcm.h"
#include "r_aes.h"

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
static uint32_t keyLength;

/***********************************************************************************************************************
 * Declaration  : void R_clear_keyLength (void)
 * Function Name: R_clear_keyLength
 * Description  : Clear key length
 * Arguments    : none
 * Return Value : none
 **********************************************************************************************************************/
void R_clear_keyLength (void)
{
    keyLength = 0;
} /* End of function R_claer_keyLength() */

/***********************************************************************************************************************
 * Declaration  : uint32_t R_set_keyLength (uint32_t n)
 * Function Name: R_set_keyLength
 * Description  : Set key length
 * Arguments    : n Key length value
 * Return Value : Key length value
 **********************************************************************************************************************/
uint32_t R_set_keyLength (uint32_t n)
{
    keyLength = n;
    return (keyLength);
} /* End of function R_set_keyLength() */

/***********************************************************************************************************************
 * Declaration  : int32_t R_gcm_encrypt_plain_block (uint8_t near *plain, uint8_t near *key)
 * Function Name: R_gcm_encrypt_plain_block
 * Description  : GCM Driver 
 * Arguments    : plain Plain text/Cipher text area.
 *              : key Key data area.
 * Return Value : 0 Normal termination.
 *                -1 Abnormal termination
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_gcm_encrypt_plain_block
 **************************************************************************//**
 * @brief 128 bit Data Block Encryption Function for GCM.
 * @param[in,out] plain Plain text/Cipher text area.
 * @param[in] key Key data area.
 * @retval 0 Normal termination.
 * @retval -1 Abnormal termination
 * @details This function is user definition function. Please implement using
 * following specifications. The R_encrypt_plain_block() encrypts the 128bits
 * data specified the 1st argument "plain" and stores to the 1st argument.
 * The key data with 128 bit block encryption is specified in 2nd argument "key"
 * @note This function is not needed for no GCM system. The key size depends on
 * block cipher algorithm.
 */
int32_t R_gcm_encrypt_plain_block (uint8_t near *plain, uint8_t near *key)
{
    uint32_t ekey[AES_EKEY256_LEN];

    if (128 == keyLength)
    {
        R_Aes_128_Keysch(key, (uint32_t near *) ekey);
        R_Aes_128_Ecbenc(plain, plain, (uint32_t near *) ekey, 1);
    }
    else if (256 == keyLength)
    {
        R_Aes_256_Keysch(key, (uint32_t near *) ekey);
        R_Aes_256_Ecbenc(plain, plain, (uint32_t near *) ekey, 1);
    }
    else
    {
        /* none */
    }
    memset(ekey, 0, sizeof(ekey));

    return 0;
} /* End of function R_gcm_encrypt_plain_block() */

