/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         aes256.h
 * @brief        Define API function for AES-256
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_aes.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#if defined(__SUPPORT_AES256__)

    #undef KEY_LENGTH
    #define KEY_LENGTH 256

    #include <stdio.h>
    #include <string.h>
    #include "r_aes_development.h"
    #include "platform.h"
    #ifdef _WIN32
        #include <stdlib.h>
        #define RotL32(a,n) _rotl(a,n)
    #else
        #define RotL32(a,n) (((a)<<(n))^((a)>>(32-(n))))
    #endif /* _WIN32 */

    #if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__) /* RL78 support only for LITTLE */
        #define _LIT
    #endif

    #if defined(_LIT) || defined(__LIT) /* Define "LITTLE_ENDIAN" directly in case of these are not defined */
        #ifndef   LITTLE_ENDIAN_Compiler
            #define LITTLE_ENDIAN_Compiler
        #endif
    #endif

/*
 Two types of libraries are available:
 (Type1) ROM size is bigger, but execution performance is good
 (Type2) ROM size is smaller, but execution performance is not so good
 In RX, (Type1) is default, and in RL78, (Type2) is default.
 If you need another library, define as follows :
 (a) To change from (Type1) to (Type2), define the macro __COMPILE_EMPHASIS_SIZE__
 (b) To change from (Type2) to (Type1), define the macro __COMPILE_EMPHASIS_SPEED__
 */
    #if defined(__COMPILE_EMPHASIS_SPEED__) && defined(__COMPILE_EMPHASIS_SIZE__)
        #error "Need to select a compile option with  emphasis on either execution performance or code size"
    #elif defined(__COMPILE_EMPHASIS_SPEED__) || defined(__COMPILE_EMPHASIS_SIZE__)
/* a compile option is selected */
    #else
        #if __COMPILE_EMPHASIS_DEFAULT__ == __COMPILE_DEFAULT_EMPHASIS_SPEED__
            #define __COMPILE_EMPHASIS_SPEED__
        #elif __COMPILE_EMPHASIS_DEFAULT__ == __COMPILE_DEFAULT_EMPHASIS_SIZE__
            #define __COMPILE_EMPHASIS_SIZE__
        #endif
    #endif /* defined__COMPILE_EMPHASIS_SPEED__ && defined__COMPILE_EMPHASIS_SIZE__ */

    #if defined(__COMPILE_EMPHASIS_SIZE__) /* program size will be down */

/***********************************************************************************************************************
 * Declaration  : uint32_t Load32(uint8_t *x)
 * Function Name: Load32
 * Description  : none.
 * Arguments    : none.
 * Return Value : none.
 **********************************************************************************************************************/
static uint32_t Load32(uint8_t *x)
{
        #if defined(LITTLE_ENDIAN_Compiler)
    return((uint32_t)*(x + 0) ^ ((uint32_t)*(x + 1) << 8) ^ ((uint32_t)*(x + 2) << 16) ^ ((uint32_t)*(x + 3) << 24));
        #else
    return((uint32_t)*(x + 3) ^ ((uint32_t)*(x + 2)) << 8 ^ ((uint32_t)*(x + 1) << 16) ^ ((uint32_t)*(x + 0) << 24));
        #endif /* defined LITTLE_ENDIAN */
} /* End of function Load32() */

/***********************************************************************************************************************
 * Declaration  : Store32(uint32_t a, uint8_t *b)
 * Function Name: Store32
 * Description  : none.
 * Arguments    : none.
 * Return Value : none.
 **********************************************************************************************************************/
static void Store32(uint32_t a, uint8_t *b)
{
        #if defined(LITTLE_ENDIAN_Compiler)
    *(b + 0) = (uint8_t)(a & 0xff);
    *(b + 1) = (uint8_t)((a >> 8) & 0xff);
    *(b + 2) = (uint8_t)((a >> 16) & 0xff);
    *(b + 3) = (uint8_t)(a >> 24);
        #else
    *(b + 0) = (uint8_t)(a >> 24);
    *(b + 1) = (uint8_t)((a >> 16) & 0xff);
    *(b + 2) = (uint8_t)((a >> 8) & 0xff);
    *(b + 3) = (uint8_t)(a & 0xff);
        #endif /* defined LITTLE_ENDIAN */
} /* End of function Store32() */
    #else /* defined__COMPILE_EMPHASIS_SIZE__ */
        #if defined(LITTLE_ENDIAN_Compiler)
            #define Load32(x) ((uint32_t)*(x+0)^(uint32_t)*(x+1)<<8^(uint32_t)*(x+2)<<16^(uint32_t)*(x+3)<<24)
            #define Store32( a, b ){\
    *(b+0) = (uint8_t)(a & 0xff);  *(b+1) = (uint8_t)(a >> 8 & 0xff);\
    *(b+2) = (uint8_t)(a >> 16  & 0xff); *(b+3) = (uint8_t)(a >> 24);\
}
        #else
            #define Load32(x) ((uint32_t)*(x+3)^(uint32_t)*(x+2)<<8^(uint32_t)*(x+1)<<16^(uint32_t)*(x+0)<<24)
            #define Store32( a, b ){\
    *(b+0) = (uint8_t)(a >> 24);  *(b+1) = (uint8_t)(a >> 16 & 0xff);\
    *(b+2) = (uint8_t)(a >> 8  & 0xff); *(b+3) = (uint8_t)(a & 0xff);\
}
        #endif /* defined LITTLE_ENDIAN */
    #endif /* defined__COMPILE_EMPHASIS_SIZE__ */

/* Stadard version: 12K bytes ROM */

/* Encryption for 256-bit */
/***********************************************************************************************************************
 * Declaration  : void AES_CBCENC(KEY_LENGTH) (uint8_t *pdat, uint8_t *cdat, uint8_t *ivec, uint32_t *ekey,
 * uint16_t block)
 * Function Name: R_Aes_256_Cbcenc
 * Description  : The R_Aes_256_Cbcenc function encrypts the plain text at a specified address (the first argument
 * "pdat") by using the expanded key (the forth argument "ekey") with initialization vector (the third argument
 * "ivec") in CBC mode and outputs cipher text to a designated address (the second argument "cdat"). The amount
 * specified by the number of blocks (the fifth argument "block" and each block is 16 byte in length) is encrypted.
 * The "ivec" is used as 16-byte work area. When the block encryption has finished, the last encrypted block data would
 *  be output to the "ivec".
 * Arguments    : pdat Plain text area (block * 16 byte).
 *                cdat Cipher text area (block * 16 byte).
 *                ivec Initialization vector area (16 byte).
 *                ekey Expanded key area (240 byte).
 *                block Number of encryption block (1 - any block).
 * Return Value : none.
 **********************************************************************************************************************/
void AES_CBCENC(KEY_LENGTH) (uint8_t *pdat, uint8_t *cdat, uint8_t *ivec, uint32_t *ekey, uint16_t block)
{
    uint32_t S[4];
    uint32_t buff[4];

    volatile memset_t memset_func = &memset;

    buff[0] = Load32(ivec + 0);
    buff[1] = Load32(ivec + 4);
    buff[2] = Load32(ivec + 8);
    buff[3] = Load32(ivec + 12);

    while (block != 0)
    {
        S[0] = Load32(pdat + 0);
        S[1] = Load32(pdat + 4);
        S[2] = Load32(pdat + 8);
        S[3] = Load32(pdat + 12);

        S[0] ^= buff[0];
        S[1] ^= buff[1];
        S[2] ^= buff[2];
        S[3] ^= buff[3];

        AES_ECBENC(KEY_LENGTH)((uint8_t *) S, cdat, ekey, 1);

        buff[0] = Load32(cdat + 0);
        buff[1] = Load32(cdat + 4);
        buff[2] = Load32(cdat + 8);
        buff[3] = Load32(cdat + 12);

        pdat += 16;
        cdat += 16;
        block--;
    }
    Store32(buff[0], ivec + 0);
    Store32(buff[1], ivec + 4);
    Store32(buff[2], ivec + 8);
    Store32(buff[3], ivec + 12);

    /* erase data for safety */
    memset_func( &S[0], 0, sizeof(S));
    memset_func( &buff[0], 0, sizeof(buff));

} /* End of function R_Aes_256_Cbcenc() */

/* Decryption for 256-bit */
/***********************************************************************************************************************
 * Declaration  : void AES_CBCDEC(KEY_LENGTH) (uint8_t *cdat, uint8_t *pdat, uint8_t *ivec, uint32_t *ekey,
 * uint16_t block)
 * Function Name: R_Aes_256_Cbcdec
 * Description  : R_Aes_256_Cbcdec() function decrypts the cipher text at a specified address (the first argument
 * "cdat") by using the expanded key (the forth argument "key") with initialization vector (the third argument "ivec")
 * in CBC mode and outputs plain text to a designated address (the second argument "pdat"). The amount specified by the
 * number of blocks (the fifth argument "block" and each block is 16 byte in length) is encrypted. The "ivec" is used
 * as 16-byte work area. When the block encryption has finished, the last decrypted block data would be output to the
 * "ivec".
 * Arguments    : cdat Cipher text area (block * 16 byte).
 *                ekey Expanded key area (240 byte).
 *                block Number of encryption block (1 - any block).
 *                pdat Plain text area (block * 16 byte).
 *                ivec Initialization vector area (16 byte).
 * Return Value : none.
 **********************************************************************************************************************/
void AES_CBCDEC(KEY_LENGTH) (uint8_t *cdat, uint8_t *pdat, uint8_t *ivec, uint32_t *ekey, uint16_t block)
{
    uint32_t S[4];
    uint32_t buff[4];
    uint32_t buff2[4];

    volatile memset_t memset_func = &memset;

    buff[0] = Load32(ivec + 0);
    buff[1] = Load32(ivec + 4);
    buff[2] = Load32(ivec + 8);
    buff[3] = Load32(ivec + 12);

    while (block != 0)
    {
        buff2[0] = Load32(cdat + 0);
        buff2[1] = Load32(cdat + 4);
        buff2[2] = Load32(cdat + 8);
        buff2[3] = Load32(cdat + 12);

        AES_ECBDEC(KEY_LENGTH)(cdat, pdat, ekey, 1);

        S[0] = Load32(pdat + 0);
        S[1] = Load32(pdat + 4);
        S[2] = Load32(pdat + 8);
        S[3] = Load32(pdat + 12);
        S[0] ^= buff[0];
        S[1] ^= buff[1];
        S[2] ^= buff[2];
        S[3] ^= buff[3];

        buff[0] = buff2[0];
        buff[1] = buff2[1];
        buff[2] = buff2[2];
        buff[3] = buff2[3];
        Store32(S[0], pdat + 0);
        Store32(S[1], pdat + 4);
        Store32(S[2], pdat + 8);
        Store32(S[3], pdat + 12);

        pdat += 16;
        cdat += 16;
        block--;
    }
    Store32(buff[0], ivec + 0);
    Store32(buff[1], ivec + 4);
    Store32(buff[2], ivec + 8);
    Store32(buff[3], ivec + 12);

    /* erase data for safety */
    memset_func( &S[0], 0, sizeof(S));
    memset_func( &buff[0], 0, sizeof(buff));
    memset_func( &buff2[0], 0, sizeof(buff2));
} /* defined__SUPPORT_AES256__ */

#endif /* defined__SUPPORT_AES256__ */
