/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         aesEcb.h
 * @brief        API function for AES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include "r_aes.h"
#include "r_aesSbox.h"
#include "r_aes_development.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

#ifdef _WIN32
    #include <stdlib.h>
    #define RotL32(a,n) _rotl(a,n)
#else
    #define RotL32(a,n) (((a)<<(n))^((a)>>(32-(n))))
#endif /* _WIN32 */

/*
 Two types of libraries are available:
 (Type1) ROM size is bigger, but execution performance is good
 (Type2) ROM size is smaller, but execution performance is not so good
 In RX, (Type1) is default, and in RL78, (Type2) is only supported.
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
#endif /* defined __COMPILE_EMPHASIS_SPEED__ && defined __COMPILE_EMPHASIS_SIZE__ */

/* Stadard version: 12K bytes ROM */

#if defined(__COMPILE_EMPHASIS_SIZE__)
/* 9K bytes ROM size down */
    #define   SM0(z)    (_SM0[z])
    #define   SM1(z)    ( ((_SM0[z]>>24)&0x000000FF) | ((_SM0[z]<< 8)&0xFFFFFF00) )
    #define   SM2(z)    ( ((_SM0[z]>>16)&0x0000FFFF) | ((_SM0[z]<<16)&0xFFFF0000) )
    #define   SM3(z)    ( ((_SM0[z]>> 8)&0x00FFFFFF) | ((_SM0[z]<<24)&0xFF000000) )
    #define  ISM0(z)    (_ISM0[z])
    #define  ISM1(z)    ( ((_ISM0[z]>>24)&0x000000FF) | ((_ISM0[z]<< 8)&0xFFFFFF00) )
    #define  ISM2(z)    ( ((_ISM0[z]>>16)&0x0000FFFF) | ((_ISM0[z]<<16)&0xFFFF0000) )
    #define  ISM3(z)    ( ((_ISM0[z]>> 8)&0x00FFFFFF) | ((_ISM0[z]<<24)&0xFF000000) )
    #define   IM0(z)    (_IM0[z])
    #define   IM1(z)    ( ((_IM0[z]>>24)&0x000000FF) | ((_IM0[z]<< 8)&0xFFFFFF00) )
    #define   IM2(z)    ( ((_IM0[z]>>16)&0x0000FFFF) | ((_IM0[z]<<16)&0xFFFF0000) )
    #define   IM3(z)    ( ((_IM0[z]>> 8)&0x00FFFFFF) | ((_IM0[z]<<24)&0xFF000000) )

#else
    #define   SM0(z)  _SM0[z]
    #define   SM1(z)  _SM1[z]
    #define   SM2(z)  _SM2[z]
    #define   SM3(z)  _SM3[z]
    #define  ISM0(z)  _ISM0[z]
    #define  ISM1(z)  _ISM1[z]
    #define  ISM2(z)  _ISM2[z]
    #define  ISM3(z)  _ISM3[z]
    #define   IM0(z)  _IM0[z]
    #define   IM1(z)  _IM1[z]
    #define   IM2(z)  _IM2[z]
    #define   IM3(z)  _IM3[z]
#endif /* defined__COMPILE_EMPHASIS_SIZE__ */

#if defined(__COMPILE_EMPHASIS_SPEED__)

/* 8K bytes ROM size up */
    #define    S0(z)  _S0[z]
    #define    S1(z)  _S1[z]
    #define    S2(z)  _S2[z]
    #define    S3(z)  _S3[z]
    #define   IS0(z)  _IS0[z]
    #define   IS1(z)  _IS1[z]
    #define   IS2(z)  _IS2[z]
    #define   IS3(z)  _IS3[z]
#else
    #define    S0(z)  (SM3(z)&0x000000ff)
    #define    S1(z)  (SM0(z)&0x0000ff00)
    #define    S2(z)  (SM0(z)&0x00ff0000)
    #define    S3(z)  (SM1(z)&0xff000000)
    #define   IS0(z)  ((ISM0(z)^ISM3(z)^ISM2(z)^ISM1(z))&0x000000ff)
    #define   IS1(z)  ((ISM1(z)^ISM0(z)^ISM3(z)^ISM2(z))&0x0000ff00)
    #define   IS2(z)  ((ISM2(z)^ISM1(z)^ISM0(z)^ISM3(z))&0x00ff0000)
    #define   IS3(z)  ((ISM3(z)^ISM2(z)^ISM1(z)^ISM0(z))&0xff000000)
#endif /* defined__COMPILE_EMPHASIS_SPEED__ */

#define Sub(x)       (S0(x&0xff)^S1(x>>8&0xff)^S2(x>>16&0xff)^S3(x>>24))
#define RotSub(x)    (S3(x&0xff)^S0(x>>8&0xff)^S1(x>>16&0xff)^S2(x>>24))
#define InvMixCol(x) (IM0((x)&0xff)^IM1(((x)>>8)&0xff)^IM2(((x)>>16)&0xff)^IM3((x)>>24))

#if defined(__COMPILE_EMPHASIS_SIZE__) /* program size will be down */

/***********************************************************************************************************************
 * Declaration  : void AddRoundKey(uint32_t *s, uint32_t *n)
 * Function Name: AddRoundKey
 * Description  : none.
 * Arguments    : none.
 * Return Value : none.
 **********************************************************************************************************************/
static void AddRoundKey (uint32_t *s, uint32_t *n)
{
    s[0] ^= n[0];
    s[1] ^= n[1];
    s[2] ^= n[2];
    s[3] ^= n[3];
} /* End of function AddRoundKey() */

/***********************************************************************************************************************
 * Declaration  : void SubShiftMix(uint32_t *s, uint32_t *t)
 * Function Name: SubShiftMix
 * Description  : none.
 * Arguments    : none.
 * Return Value : none.
 **********************************************************************************************************************/
static void SubShiftMix (uint32_t *s, uint32_t *t)
{
    t[0] = SM0(s[0] & 0xff) ^ SM1(s[1] >> 8 & 0xff) ^ SM2(s[2] >> 16 & 0xff) ^ SM3(s[3] >> 24);
    t[1] = SM0(s[1] & 0xff) ^ SM1(s[2] >> 8 & 0xff) ^ SM2(s[3] >> 16 & 0xff) ^ SM3(s[0] >> 24);
    t[2] = SM0(s[2] & 0xff) ^ SM1(s[3] >> 8 & 0xff) ^ SM2(s[0] >> 16 & 0xff) ^ SM3(s[1] >> 24);
    t[3] = SM0(s[3] & 0xff) ^ SM1(s[0] >> 8 & 0xff) ^ SM2(s[1] >> 16 & 0xff) ^ SM3(s[2] >> 24);
} /* End of function SubShiftMix() */

/***********************************************************************************************************************
 * Declaration  : void SubShift(uint32_t *s, uint32_t *t)
 * Function Name: SubShift
 * Description  : none.
 * Arguments    : none.
 * Return Value : none.
 **********************************************************************************************************************/
static void SubShift (uint32_t *s, uint32_t *t)
{
    t[0] = S0(s[0] & 0xff) ^ S1(s[1] >> 8 & 0xff) ^ S2(s[2] >> 16 & 0xff) ^ S3(s[3] >> 24);
    t[1] = S0(s[1] & 0xff) ^ S1(s[2] >> 8 & 0xff) ^ S2(s[3] >> 16 & 0xff) ^ S3(s[0] >> 24);
    t[2] = S0(s[2] & 0xff) ^ S1(s[3] >> 8 & 0xff) ^ S2(s[0] >> 16 & 0xff) ^ S3(s[1] >> 24);
    t[3] = S0(s[3] & 0xff) ^ S1(s[0] >> 8 & 0xff) ^ S2(s[1] >> 16 & 0xff) ^ S3(s[2] >> 24);
} /* End of function SubShift() */

/***********************************************************************************************************************
 * Declaration  : void InvSubShiftMix(uint32_t *s, uint32_t *t)
 * Function Name: InvSubShiftMix
 * Description  : none.
 * Arguments    : none.
 * Return Value : none.
 **********************************************************************************************************************/
static void InvSubShiftMix (uint32_t *s, uint32_t *t)
{
    t[0] = ISM0(s[0] & 0xff) ^ ISM1(s[3] >> 8 & 0xff) ^ ISM2(s[2] >> 16 & 0xff) ^ ISM3(s[1] >> 24);
    t[1] = ISM0(s[1] & 0xff) ^ ISM1(s[0] >> 8 & 0xff) ^ ISM2(s[3] >> 16 & 0xff) ^ ISM3(s[2] >> 24);
    t[2] = ISM0(s[2] & 0xff) ^ ISM1(s[1] >> 8 & 0xff) ^ ISM2(s[0] >> 16 & 0xff) ^ ISM3(s[3] >> 24);
    t[3] = ISM0(s[3] & 0xff) ^ ISM1(s[2] >> 8 & 0xff) ^ ISM2(s[1] >> 16 & 0xff) ^ ISM3(s[0] >> 24);
} /* End of function InvSubShiftMix() */

/***********************************************************************************************************************
 * Declaration  : void InvSubShift(uint32_t *s, uint32_t *t)
 * Function Name: InvSubShift
 * Description  : none.
 * Arguments    : none.
 * Return Value : none.
 **********************************************************************************************************************/
static void InvSubShift (uint32_t *s, uint32_t *t)
{
    t[0] = IS0(s[0] & 0xff) ^ IS1(s[3] >> 8 & 0xff) ^ IS2(s[2] >> 16 & 0xff) ^ IS3(s[1] >> 24);
    t[1] = IS0(s[1] & 0xff) ^ IS1(s[0] >> 8 & 0xff) ^ IS2(s[3] >> 16 & 0xff) ^ IS3(s[2] >> 24);
    t[2] = IS0(s[2] & 0xff) ^ IS1(s[1] >> 8 & 0xff) ^ IS2(s[0] >> 16 & 0xff) ^ IS3(s[3] >> 24);
    t[3] = IS0(s[3] & 0xff) ^ IS1(s[2] >> 8 & 0xff) ^ IS2(s[1] >> 16 & 0xff) ^ IS3(s[0] >> 24);
} /* End of function InvSubShift() */

/***********************************************************************************************************************
 * Declaration  : uint32_t Load32(uint8_t *x)
 * Function Name: Load32
 * Description  : none.
 * Arguments    : none.
 * Return Value : none.
 **********************************************************************************************************************/
static uint32_t Load32 (uint8_t *x)
{
    return ((uint32_t)*(x + 0) ^ ((uint32_t)*(x + 1) << 8) ^ ((uint32_t)*(x + 2) << 16) ^ ((uint32_t)*(x + 3) << 24));
} /* End of function Load32() */

/***********************************************************************************************************************
 * Declaration  : void Store32(uint32_t a, uint8_t *b)
 * Function Name: Store32
 * Description  : none.
 * Arguments    : none.
 * Return Value : none.
 **********************************************************************************************************************/
static void Store32 (uint32_t a, uint8_t *b)
{
    *(b + 0) = (uint8_t) (a & 0xff);
    *(b + 1) = (uint8_t)((a >> 8) & 0xff);
    *(b + 2) = (uint8_t)((a >> 16) & 0xff);
    *(b + 3) = (uint8_t) (a >> 24);
}
#else /* defined__COMPILE_EMPHASIS_SIZE__) */
    #define AddRoundKey(s,n) (s[0]^=*(n+0),s[1]^=*(n+1),s[2]^=*(n+2),s[3]^=*(n+3))

    #define SubShiftMix(s,t){\
    t[0] = SM0(s[0]&0xff)^SM1(s[1]>>8&0xff)^SM2(s[2]>>16&0xff)^SM3(s[3]>>24);\
    t[1] = SM0(s[1]&0xff)^SM1(s[2]>>8&0xff)^SM2(s[3]>>16&0xff)^SM3(s[0]>>24);\
    t[2] = SM0(s[2]&0xff)^SM1(s[3]>>8&0xff)^SM2(s[0]>>16&0xff)^SM3(s[1]>>24);\
    t[3] = SM0(s[3]&0xff)^SM1(s[0]>>8&0xff)^SM2(s[1]>>16&0xff)^SM3(s[2]>>24);\
}
    #define SubShift(s,t){\
    t[0] = S0(s[0]&0xff)^S1(s[1]>>8&0xff)^S2(s[2]>>16&0xff)^S3(s[3]>>24);\
    t[1] = S0(s[1]&0xff)^S1(s[2]>>8&0xff)^S2(s[3]>>16&0xff)^S3(s[0]>>24);\
    t[2] = S0(s[2]&0xff)^S1(s[3]>>8&0xff)^S2(s[0]>>16&0xff)^S3(s[1]>>24);\
    t[3] = S0(s[3]&0xff)^S1(s[0]>>8&0xff)^S2(s[1]>>16&0xff)^S3(s[2]>>24);\
}
    #define InvSubShiftMix(s,t){\
    t[0] = ISM0(s[0]&0xff)^ISM1(s[3]>>8&0xff)^ISM2(s[2]>>16&0xff)^ISM3(s[1]>>24);\
    t[1] = ISM0(s[1]&0xff)^ISM1(s[0]>>8&0xff)^ISM2(s[3]>>16&0xff)^ISM3(s[2]>>24);\
    t[2] = ISM0(s[2]&0xff)^ISM1(s[1]>>8&0xff)^ISM2(s[0]>>16&0xff)^ISM3(s[3]>>24);\
    t[3] = ISM0(s[3]&0xff)^ISM1(s[2]>>8&0xff)^ISM2(s[1]>>16&0xff)^ISM3(s[0]>>24);\
}
    #define InvSubShift(s,t){\
    t[0] = IS0(s[0]&0xff)^IS1(s[3]>>8&0xff)^IS2(s[2]>>16&0xff)^IS3(s[1]>>24);\
    t[1] = IS0(s[1]&0xff)^IS1(s[0]>>8&0xff)^IS2(s[3]>>16&0xff)^IS3(s[2]>>24);\
    t[2] = IS0(s[2]&0xff)^IS1(s[1]>>8&0xff)^IS2(s[0]>>16&0xff)^IS3(s[3]>>24);\
    t[3] = IS0(s[3]&0xff)^IS1(s[2]>>8&0xff)^IS2(s[1]>>16&0xff)^IS3(s[0]>>24);\
}
    #define Load32( x ) ((uint32_t)*(x+0)^(uint32_t)*(x+1)<<8^(uint32_t)*(x+2)<<16^(uint32_t)*(x+3)<<24)
    #define Store32( a, b ){\
    *(b+0) = (uint8_t)(a & 0xff);  *(b+1) = (uint8_t)(a >> 8 & 0xff);\
    *(b+2) = (uint8_t)(a >> 16  & 0xff); *(b+3) = (uint8_t)(a >> 24);\
} /* End of function Store32() */
#endif /* defined__COMPILE_EMPHASIS_SIZE__) */


/* Key Scheduling for 128-bit Key */
/***********************************************************************************************************************
 * Declaration  : void AES_KEY(KEY_LENGTH) (uint8_t *key, uint32_t *ekey)
 * Function Name: R_Aes_128_Keysch/R_Aes_192_Keysch/R_Aes_256_Keysch
 * Description  : The R_Aes_128_Keysch()/R_Aes_192_Keysch()/R_Aes_256_Keysch() function executes the key schedule of
 * AES. The R_Aes_128_Keysch/R_Aes_192_Keysch/R_Aes_256_Keysch function expands the given key specified by the first
 * argument "key" and writes the expanded key to an "ekey". Because 176/208/240 bytes memory area is required to store
 * the expansion key, "ekey" has to point to the memory area of at least 176/208/240 bytes.
 * Arguments    : key Key data area (16/24/32 byte).
 *                ekey Expanded key area (176/208/240 byte).
 * Return Value : none.
 **********************************************************************************************************************/
void AES_KEY(KEY_LENGTH) (uint8_t *key, uint32_t *ekey)
{
    natural_int_t i;

    ekey[0] = Load32(key + 0);
    ekey[1] = Load32(key + 4);
    ekey[2] = Load32(key + 8);
    ekey[3] = Load32(key + 12);
#if (KEY_LENGTH == 192) || (KEY_LENGTH == 256)
    ekey[4] = Load32(key + 16);
    ekey[5] = Load32(key + 20);
    #if KEY_LENGTH == 256
    ekey[6] = Load32(key + 24);
    ekey[7] = Load32(key + 28);
    #endif
#endif

#if KEY_LENGTH == 128
    for (i = 4; i < 44; i += 4)
    {
        ekey[i+0] = ekey[i-4] ^ RotSub(ekey[i-1]) ^ Rcon[i/4];
        ekey[i+1] = ekey[i-3] ^ ekey[i+0];
        ekey[i+2] = ekey[i-2] ^ ekey[i+1];
        ekey[i+3] = ekey[i-1] ^ ekey[i+2];
    }
#elif KEY_LENGTH == 192
    for (i = 6; i < 48; i += 6)
    {
        ekey[i+0] = ekey[i-6] ^ RotSub(ekey[i-1]) ^ Rcon[i/6];
        ekey[i+1] = ekey[i-5] ^ ekey[i+0];
        ekey[i+2] = ekey[i-4] ^ ekey[i+1];
        ekey[i+3] = ekey[i-3] ^ ekey[i+2];
        ekey[i+4] = ekey[i-2] ^ ekey[i+3];
        ekey[i+5] = ekey[i-1] ^ ekey[i+4];
    }
    ekey[48] = ekey[42] ^ RotSub(ekey[47]) ^ Rcon[8];
    ekey[49] = ekey[43] ^ ekey[48];
    ekey[50] = ekey[44] ^ ekey[49];
    ekey[51] = ekey[45] ^ ekey[50];
#elif  KEY_LENGTH == 256
    for (i = 8; i < 56; i += 8)
    {
        ekey[i+0] = ekey[i-8] ^ RotSub(ekey[i-1]) ^ Rcon[i/8];
        ekey[i+1] = ekey[i-7] ^ ekey[i+0];
        ekey[i+2] = ekey[i-6] ^ ekey[i+1];
        ekey[i+3] = ekey[i-5] ^ ekey[i+2];
        ekey[i+4] = ekey[i-4] ^ Sub(ekey[i+3]);
        ekey[i+5] = ekey[i-3] ^ ekey[i+4];
        ekey[i+6] = ekey[i-2] ^ ekey[i+5];
        ekey[i+7] = ekey[i-1] ^ ekey[i+6];
    }
    ekey[56] = ekey[48] ^ RotSub(ekey[55]) ^ Rcon[7];
    ekey[57] = ekey[49] ^ ekey[56];
    ekey[58] = ekey[50] ^ ekey[57];
    ekey[59] = ekey[51] ^ ekey[58];
#endif

    /* erase data for safety */
    i = 0;
} /* End of function AES_KEY(KEY_LENGTH)() */

/* Encryption for 128-bit */

#if defined (ECB_MODE)
/***********************************************************************************************************************
 * Declaration  : void AES_ECBENC(KEY_LENGTH)(uint8_t *pdat, uint8_t *cdat, uint32_t *ekey, uint16_t block)
 * Function Name: R_Aes_128_Ecbenc/R_Aes_192_Ecbenc/R_Aes_256_Ecbenc
 * Description  : The R_Aes_128_Ecbenc()/R_Aes_192_Ecbenc()/R_Aes_256_Ecbenc() function encrypts the plain text at a
 * specified address (the first argument "pdat") by using the expanded key (the third argument "ekey") in ECB mode and
 * outputs cipher text to a designated address (the second argument "cdat"). The amount specified by the number of
 * blocks (the forth argument "block" and each block is 16 byte in length) is encrypted.
 * Arguments    : pdat Plain text area (block * 16 byte).
 *                cdat Cipher text area (block * 16 byte).
 *                ekey Expanded key area (176/208/240 byte).
 *                block Number of encryption block (1 - any block).
 * Return Value : none.
 **********************************************************************************************************************/
void AES_ECBENC(KEY_LENGTH)(uint8_t *pdat, uint8_t *cdat, uint32_t *ekey, uint16_t block)
#elif defined(CBC_MODE)
/***********************************************************************************************************************
 * Declaration  : void AES_CBCENC(KEY_LENGTH)(uint8_t *pdat, uint8_t *cdat, uint8_t *ivec, uint32_t *ekey,
 * uint16_t block)
 * Function Name: R_Aes_128_Cbcenc/R_Aes_192_Cbcenc/R_Aes_256_Cbcenc
 * Description  : The R_Aes_128_Cbcenc()/R_Aes_192_Cbcenc()/R_Aes_256_Cbcenc() function encrypts the plain text at a
 * specified address (the first argument "pdat") by using the expanded key (the forth argument "ekey") with
 * initialization vector (the third argument "ivec") in CBC mode and outputs cipher text to a designated address
 * (the second argument "cdat"). The amount specified by the number of blocks (the fifth argument "block" and each block
 * is 16 byte in length) is encrypted. The "ivec" is used as 16-byte work area. When the block encryption has finished,
 * the last encrypted block data would be output to the "ivec".
 * Arguments    : cdat Cipher text area (block * 16 byte).
 *                pdat Plain text area (block * 16 byte).
 *                ivec Initialization vector area (16 byte).
 *                ekey Expanded key area (176/208/240 byte).
 *                block Number of encryption block (1 - any block).
 * Return Value : none.
 **********************************************************************************************************************/
void AES_CBCENC(KEY_LENGTH)(uint8_t *pdat, uint8_t *cdat, uint8_t *ivec, uint32_t *ekey, uint16_t block)
#else
    #error  "AES mode operation is not specified"
#endif /* defined ECB_MODE */
{
    uint32_t S[4], T[4];
    volatile memset_t memset_func = &memset;

#if defined(CBC_MODE)
    uint32_t buff[4];

    buff[0] = Load32(ivec + 0);
    buff[1] = Load32(ivec + 4);
    buff[2] = Load32(ivec + 8);
    buff[3] = Load32(ivec + 12);
#endif

    while (block != 0)
    {
        S[0] = Load32(pdat + 0);
        S[1] = Load32(pdat + 4);
        S[2] = Load32(pdat + 8);
        S[3] = Load32(pdat + 12);

#if defined(CBC_MODE)
        S[0] ^= buff[0];
        S[1] ^= buff[1];
        S[2] ^= buff[2];
        S[3] ^= buff[3];
#endif

        AddRoundKey(S, ekey + 0);

        SubShiftMix(S, T);
        AddRoundKey(T, ekey + 4);
        SubShiftMix(T, S);
        AddRoundKey(S, ekey + 8);
        SubShiftMix(S, T);
        AddRoundKey(T, ekey + 12);
        SubShiftMix(T, S);
        AddRoundKey(S, ekey + 16);
        SubShiftMix(S, T);
        AddRoundKey(T, ekey + 20);
        SubShiftMix(T, S);
        AddRoundKey(S, ekey + 24);
        SubShiftMix(S, T);
        AddRoundKey(T, ekey + 28);
        SubShiftMix(T, S);
        AddRoundKey(S, ekey + 32);
        SubShiftMix(S, T);
        AddRoundKey(T, ekey + 36);
#if KEY_LENGTH == 128
        SubShift(T, S);
        AddRoundKey(S, ekey + 40);
#elif KEY_LENGTH == 192
        SubShiftMix(T, S);
        AddRoundKey(S, ekey + 40);
        SubShiftMix(S, T);
        AddRoundKey(T, ekey + 44);
        SubShift(T, S);
        AddRoundKey(S, ekey + 48);
#elif KEY_LENGTH == 256
        SubShiftMix(T, S);
        AddRoundKey(S, ekey + 40);
        SubShiftMix(S, T);
        AddRoundKey(T, ekey + 44);
        SubShiftMix(T, S);
        AddRoundKey(S, ekey + 48);
        SubShiftMix(S, T);
        AddRoundKey(T, ekey + 52);
        SubShift(T, S);
        AddRoundKey(S, ekey + 56);
#endif

#if defined(CBC_MODE)
        buff[0] = S[0];
        buff[1] = S[1];
        buff[2] = S[2];
        buff[3] = S[3];
#endif

        Store32(S[0], cdat + 0);
        Store32(S[1], cdat + 4);
        Store32(S[2], cdat + 8);
        Store32(S[3], cdat + 12);

        pdat += 16;
        cdat += 16;
        block--;
    }
#if defined(CBC_MODE)
    Store32(buff[0], ivec + 0);
    Store32(buff[1], ivec + 4);
    Store32(buff[2], ivec + 8);
    Store32(buff[3], ivec + 12);
#endif
    /* erase data for safety */
    memset_func(S, 0, sizeof(S));
    memset_func(T, 0, sizeof(T));
#if defined(CBC_MODE)
    memset_func(buff, 0, sizeof(buff));
#endif
}/* End of function AES_CBCENC(KEY_LENGTH)() */

/* Decryption for 128-bit */

#if KEY_LENGTH == 128
    #define EKEY_NUM    (44)
#elif KEY_LENGTH == 192
    #define EKEY_NUM    (52)
#elif KEY_LENGTH == 256
    #define EKEY_NUM    (60)
#endif

#if defined (ECB_MODE)
/***********************************************************************************************************************
 * Declaration  : void AES_ECBDEC(KEY_LENGTH)(uint8_t *cdat, uint8_t *pdat, uint32_t *ekey, uint16_t block)
 * Function Name: R_Aes_128_Ecbdec/R_Aes_192_Ecbdec/R_Aes_256_Ecbdec
 * Description  : The R_Aes_128_Ecbdec()/R_Aes_192_Ecbdec()/R_Aes_256_Ecbdec() function decrypts the cipher text at a
 * specified address (the first argument "cpdat") by using the expanded key (the third argument "ekey") in ECB mode and
 * outputs plain text to a designated address (the second argument "pdat"). The amount specified by the number of blocks
 * (the forth argument "block" and each block is 16 byte in length) is encrypted.
 * Arguments    : cdat Cipher text area (block * 16 byte).
 *                pdat Plain text area (block * 16 byte).
 *                ekey Expanded key area (176/208/240 byte).
 *                block Number of encryption block (1 - any block).
 * Return Value : none.
 **********************************************************************************************************************/
void AES_ECBDEC(KEY_LENGTH)(uint8_t *cdat, uint8_t *pdat, uint32_t *ekey, uint16_t block)
#elif defined(CBC_MODE)
/***********************************************************************************************************************
 * Declaration  : void AES_CBCDEC(KEY_LENGTH)(uint8_t *cdat, uint8_t *pdat, uint8_t *ivec, uint32_t *ekey,
 * uint16_t block)
 * Function Name: R_Aes_128_Cbcdec/R_Aes_192_Cbcdec/R_Aes_256_Cbcdec
 * Description  : The R_Aes_128_Cbcdec()/R_Aes_192_Cbcdec()/R_Aes_256_Cbcdec() function decrypts the cipher text at a
 * specified address (the first argument "cdat") by using the expanded key (the forth argument "key") with
 * initialization vector (the third argument "ivec") in CBC mode and outputs plain text to a designated address (the
 * second argument "pdat"). The amount specified by the number of blocks (the fifth argument "block" and each block is
 * 16 byte in length) is encrypted. The "ivec" is used as 16-byte work area. When the block encryption has finished, the
 * last decrypted block data would be output to the "ivec".
 * Arguments    : cdat Cipher text area (block * 16 byte).
 *                pdat Plain text area (block * 16 byte).
 *                ivec Initialization vector area (16 byte).
 *                ekey Expanded key area (176/208/240 byte).
 *                block Number of encryption block (1 - any block).
 * Return Value : none
 **********************************************************************************************************************/
void AES_CBCDEC(KEY_LENGTH)(uint8_t *cdat, uint8_t *pdat, uint8_t *ivec, uint32_t *ekey, uint16_t block)
#else
    #error  "AES mode operation is not specified"
#endif /* defined ECB_MODE */
{
    uint32_t S[4], T[4], EKEY[EKEY_NUM];
    volatile memset_t memset_func = &memset;

#if defined(CBC_MODE)
    uint32_t buff[4], buff2[4];
#endif
    natural_int_t i;

    EKEY[0] = ekey[0];
    EKEY[1] = ekey[1];
    EKEY[2] = ekey[2];
    EKEY[3] = ekey[3];
    for (i = 4; i < EKEY_NUM - 4; i++)
    {
        EKEY[i] = InvMixCol(ekey[i]);
    }
    EKEY[EKEY_NUM-4] = ekey[EKEY_NUM-4];
    EKEY[EKEY_NUM-3] = ekey[EKEY_NUM-3];
    EKEY[EKEY_NUM-2] = ekey[EKEY_NUM-2];
    EKEY[EKEY_NUM-1] = ekey[EKEY_NUM-1];

#if defined(CBC_MODE)
    buff[0] = Load32(ivec + 0);
    buff[1] = Load32(ivec + 4);
    buff[2] = Load32(ivec + 8);
    buff[3] = Load32(ivec + 12);
#endif

    while (block != 0)
    {
        S[0] = Load32(cdat + 0);
        S[1] = Load32(cdat + 4);
        S[2] = Load32(cdat + 8);
        S[3] = Load32(cdat + 12);

#if defined(CBC_MODE)
        buff2[0] = S[0];
        buff2[1] = S[1];
        buff2[2] = S[2];
        buff2[3] = S[3];
#endif

        AddRoundKey(S, EKEY + EKEY_NUM - 4);

#if KEY_LENGTH == 128
        /* Nothing to add */
#elif KEY_LENGTH == 192
        InvSubShiftMix(S, T);
        AddRoundKey(T, EKEY + 44);
        InvSubShiftMix(T, S);
        AddRoundKey(S, EKEY + 40);
#elif KEY_LENGTH == 256
        InvSubShiftMix(S, T);
        AddRoundKey(T, EKEY + 52);
        InvSubShiftMix(T, S);
        AddRoundKey(S, EKEY + 48);
        InvSubShiftMix(S, T);
        AddRoundKey(T, EKEY + 44);
        InvSubShiftMix(T, S);
        AddRoundKey(S, EKEY + 40);
#endif
        InvSubShiftMix(S, T);
        AddRoundKey(T, EKEY + 36);
        InvSubShiftMix(T, S);
        AddRoundKey(S, EKEY + 32);
        InvSubShiftMix(S, T);
        AddRoundKey(T, EKEY + 28);
        InvSubShiftMix(T, S);
        AddRoundKey(S, EKEY + 24);
        InvSubShiftMix(S, T);
        AddRoundKey(T, EKEY + 20);
        InvSubShiftMix(T, S);
        AddRoundKey(S, EKEY + 16);
        InvSubShiftMix(S, T);
        AddRoundKey(T, EKEY + 12);
        InvSubShiftMix(T, S);
        AddRoundKey(S, EKEY + 8);
        InvSubShiftMix(S, T);
        AddRoundKey(T, EKEY + 4);

        InvSubShift(T, S);
        AddRoundKey(S, EKEY + 0);

#if defined(CBC_MODE)
        S[0] ^= buff[0];
        S[1] ^= buff[1];
        S[2] ^= buff[2];
        S[3] ^= buff[3];

        buff[0] = buff2[0];
        buff[1] = buff2[1];
        buff[2] = buff2[2];
        buff[3] = buff2[3];
#endif

        Store32(S[0], pdat + 0);
        Store32(S[1], pdat + 4);
        Store32(S[2], pdat + 8);
        Store32(S[3], pdat + 12);

        pdat += 16;
        cdat += 16;
        block--;
    }
#if defined(CBC_MODE)
    Store32(buff[0], ivec + 0);
    Store32(buff[1], ivec + 4);
    Store32(buff[2], ivec + 8);
    Store32(buff[3], ivec + 12);
#endif

    /* erase data for safety */
    memset_func(S, 0, sizeof(S));
    memset_func(T, 0, sizeof(T));
    memset_func(EKEY, 0, sizeof(EKEY));
#if defined(CBC_MODE)
    memset_func(buff, 0, sizeof(buff));
    memset_func(buff2, 0, sizeof(buff2));
#endif
    i = 0;
} /* End of function AES_ECBDEC(KEY_LENGTH)() */
#undef EKEY_NUM

