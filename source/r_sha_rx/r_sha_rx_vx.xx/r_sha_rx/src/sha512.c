/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         sha512.c
 * @brief        The code of calculation processing for SHA-384/SHA-512
 **********************************************************************************************************************/
/* 
 This SHA-384 / SHA-512 are based on FIPS PUB 180-4
 
 FEDERAL INFORMATION PROCESSING STANDARDS PUBLICATION
 Secure Hash Standard (SHS)
 */
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_sha.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#if defined(__SUPPORT_SHA384__) || defined(__SUPPORT_SHA512__)

    #include <stdio.h>
    #include <stdint.h>
    #include <string.h>

    #if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__) /* RL78 support only for LITTLE */
        #define _LIT
    #endif /* defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__) */

    #if defined(_LIT) || defined(__LIT) /* Define "LITTLE_ENDIAN" directly in case of these are not defined */
        #ifndef LITTLE_ENDIAN_Compiler
            #define LITTLE_ENDIAN_Compiler
        #endif
    #endif

    #if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)
/* RL78 not support */
    #else
        #include "r_sha_config.h"

        #if ( SHA_CFG_BUILD_OPTION == 0 )
            #define __COMPILE_EMPHASIS_SPEED__
        #elif  ( SHA_CFG_BUILD_OPTION == 1 )
            #define __COMPILE_EMPHASIS_SIZE__
        #endif
    #endif /* defined__RL78__ || defined__ICCRL78__ || defined__CCRL__ */

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
    #endif /* defined(__COMPILE_EMPHASIS_SPEED__) && defined(__COMPILE_EMPHASIS_SIZE__) */

/*
 3.2 Operations on Words
 The operations are applied to w-bit words
 SHA-384, SHA-512, SHA-512/224 and SHA-512/256 operate on 64-bit words (w=64).
 */
    #define W_BIT    (64)

/*
 4.1.3 SHA-384, SHA-512, SHA-512/224 and SHA-512/256 Functions

 Ch(x, y, z) = (x & y) ^ (~x & z)
 Maj(x, y, z) = (x & y) ^ (x & z) ^ (y & z)
 Sigma0_512(x) = ROTR 28(x) ^ ROTR 34(x) ^ ROTR 39(x)
 Sigma1_512(x) = ROTR 14(x) ^ ROTR 18(x) ^ ROTR 41(x)
 sigma0_512(x) = ROTR  1(x) ^ ROTR  8(x) ^ SHR  7(x)
 sigma1_512(x) = ROTR 19(x) ^ ROTR 61(x) ^ SHR  6(x) 
 */
    #if defined(__COMPILE_EMPHASIS_SIZE__)
static uint64_t Ch (uint64_t x, uint64_t y, uint64_t z)
{
    return (z) ^ ((x) & ((y) ^ (z)));
}

static uint64_t Maj (uint64_t x, uint64_t y, uint64_t z)
{
    return ((x) & (y)) | ((z) & ((x) | (y)));
}

/*
 The rotate right (circular right shift) operation ROTR n(x), 
 where x is a w-bit word and n is an integer with 0 =< n < w
 */
static uint64_t ROTR (uint64_t x, uint64_t n)
{
    return ((x) >> (n)) | ((x) << (W_BIT - (n)));
}

    #else /* __COMPILE_EMPHASIS_SPEED__ */

        #define Ch(x, y, z) ((z) ^ ((x) & ((y) ^ (z))))
        #define Maj(x, y, z)    (((x) & (y)) | ((z) & ((x) | (y))))
        #define ROTR(x, n)  (((x) >> (n)) | ((x) << (W_BIT - (n))))
    #endif /* defined(__COMPILE_EMPHASIS_SIZE__) */

    #define Sigma0_512(x)       (ROTR((x),28) ^ ROTR((x),34) ^ ROTR((x),39))
    #define Sigma1_512(x)       (ROTR((x),14) ^ ROTR((x),18) ^ ROTR((x),41))
    #define sigma0_512(x)       (ROTR((x), 1) ^ ROTR((x), 8) ^ ((x) >> 7))
    #define sigma1_512(x)       (ROTR((x),19) ^ ROTR((x),61) ^ ((x) >> 6))

/*
 4.2.3 SHA-384, SHA-512, SHA-512/224 and SHA-512/256 Constants
 SHA-384, SHA-512, SHA-512/224 and SHA-512/256 use the same sequence of
 eighty constant 64-bit word
 */
static const uint64_t far sha_384_512_K[80] =
{ 0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL, 0x3956c25bf348b538ULL,
        0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 0xd807aa98a3030242ULL,
        0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL, 0x72be5d74f27b896fULL,
        0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL, 0xe49b69c19ef14ad2ULL,
        0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL, 0x2de92c6f592b0275ULL,
        0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL, 0x983e5152ee66dfabULL,
        0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL, 0xc6e00bf33da88fc2ULL,
        0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 0x27b70a8546d22ffcULL,
        0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL, 0x650a73548baf63deULL,
        0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL, 0xa2bfe8a14cf10364ULL,
        0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 0xd192e819d6ef5218ULL,
        0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL, 0x19a4c116b8d2d0c8ULL,
        0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL, 0x391c0cb3c5c95a63ULL,
        0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL, 0x748f82ee5defb2fcULL,
        0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL, 0x90befffa23631e28ULL,
        0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL, 0xca273eceea26619cULL,
        0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL, 0x06f067aa72176fbaULL,
        0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL, 0x28db77f523047d84ULL,
        0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL, 0x4cc5d4becb3e42b6ULL,
        0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL, };

/*
 6.4.2 SHA-512 Hash Computation
 Prepare the message schedule
 0 =< t <= 15   Wi = Mi (message block,)
 16 =< t <= 79   Wi = sigma1_512(Wt-2) + Wt-7 + sigma0_512(Wt-15) + Wt-16
 */
    #if defined(__COMPILE_EMPHASIS_SIZE__)
static uint64_t LOAD64 (const uint8_t *input)
{
    uint64_t w;

    w = input[0] & 0xff;
    w <<= 8;
    w |= input[1] & 0xff;
    w <<= 8;
    w |= input[2] & 0xff;
    w <<= 8;
    w |= input[3] & 0xff;
    w <<= 8;
    w |= input[4] & 0xff;
    w <<= 8;
    w |= input[5] & 0xff;
    w <<= 8;
    w |= input[6] & 0xff;
    w <<= 8;
    w |= input[7] & 0xff;
    return (w);
}

static void MESSAGE_SCHEDULE_0_15 (uint64_t *word64, int n)
{
    word64[n] = sigma1_512(word64[n-2]) + word64[n - 7] + sigma0_512(word64[n - 15]) + word64[n - 16];
}

    #else /* __COMPILE_EMPHASIS_SPEED__ */

        #define LOAD64(x)                                                                               \
    (((uint64_t)*((x)+7))^(((uint64_t)*((x)+6))<<8)^(((uint64_t)*((x)+5))<<16)^(((uint64_t)*((x)+4))<<24)^ \
    (((uint64_t)*((x)+3))<<32)^(((uint64_t)*((x)+2))<<40)^(((uint64_t)*((x)+1))<<48)^(((uint64_t)*(x+0))<<56))

        #define MESSAGE_SCHEDULE_0_15(word64, n)                                                        \
    {                                                                                                   \
        word64[n] = sigma1_512(word64[n-2]) + word64[n-7] + sigma0_512(word64[n-15]) + word64[n-16];    \
    }

    #endif /* defined__COMPILE_EMPHASIS_SIZE__ */

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
/*
 3.1 Bit Strings and Integers

 - the most significant bit is stored in the left-most bit position.

 - For SHA-384, SHA-512, SHA-512/224 and SHA-512/256 each message block
 has 1024 bits, which are represented as a sequence of sixteen 64-bit words.
 */

/***********************************************************************************************************************
 * Declaration  : void R_Sha512_Hash(uint8_t near *mdat, uint8_t near *hdat, uint16_t block, void *work)
 * Function Name: R_Sha512_Hash
 * Description  : Secure hash algorithms based on SHA-512 specification to computing a condensed representation of
 * electronic data (message).
 * Arguments    : mdat Input data pointer.
 *                hdat Output destination of the hash value, a 64-byte area is required.
 *                block Number of blocks of input data, where block > 0.
 *                work Work area pointer.
 * Return Value : none.
 **********************************************************************************************************************/
void R_Sha512_Hash (uint8_t near *mdat, uint8_t near *hdat, uint16_t block, void *work)
{
    /*
     6.4 SHA-512
     The words of the message schedule are labeled W0, W1,..., W79.
     The eight working variables are labeled a, b, c, d, e, f, g, and h.
     The words of the hash value are labeled H0-H7
     SHA-512 also uses two temporary words, T1 and T2.
     */
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    uint64_t e;
    uint64_t f;
    uint64_t g;
    uint64_t h;
    uint64_t t1;
    uint64_t t2;
    uint64_t *W; /* message schedule (cf. 6.4.2) */
    uint64_t *H; /* words of the hash value */
    natural_int_t i;

    volatile memset_t memset_func = &memset;

    W = (uint64_t *) work;
    H = W + 80;

    #if defined(__COMPILE_EMPHASIS_SIZE__)
    for (i = 0; i < 8; i++)
    {
        H[i] = LOAD64((const uint8_t *) (hdat + (8 * i)));
    }
    #else /* defined__COMPILE_EMPHASIS_SPEED__ */
    H[0] = LOAD64(hdat + 8 * 0);
    H[1] = LOAD64(hdat + 8 * 1);
    H[2] = LOAD64(hdat + 8 * 2);
    H[3] = LOAD64(hdat + 8 * 3);
    H[4] = LOAD64(hdat + 8 * 4);
    H[5] = LOAD64(hdat + 8 * 5);
    H[6] = LOAD64(hdat + 8 * 6);
    H[7] = LOAD64(hdat + 8 * 7);
    #endif /* defined__COMPILE_EMPHASIS_SIZE__ */

    while (0 != block)
    {
        /* load the input */
    #if defined(__COMPILE_EMPHASIS_SIZE__)
        for (i = 0; i < 16; i++)
        {
            W[i] = LOAD64((const uint8_t *) (mdat + (8 * i)));
        }
    #else /* __COMPILE_EMPHASIS_SPEED__ */
        W[0] = LOAD64(mdat + 8 * 0);
        W[1] = LOAD64(mdat + 8 * 1);
        W[2] = LOAD64(mdat + 8 * 2);
        W[3] = LOAD64(mdat + 8 * 3);
        W[4] = LOAD64(mdat + 8 * 4);
        W[5] = LOAD64(mdat + 8 * 5);
        W[6] = LOAD64(mdat + 8 * 6);
        W[7] = LOAD64(mdat + 8 * 7);
        W[8] = LOAD64(mdat + 8 * 8);
        W[9] = LOAD64(mdat + 8 * 9);
        W[10] = LOAD64(mdat + 8 * 10);
        W[11] = LOAD64(mdat + 8 * 11);
        W[12] = LOAD64(mdat + 8 * 12);
        W[13] = LOAD64(mdat + 8 * 13);
        W[14] = LOAD64(mdat + 8 * 14);
        W[15] = LOAD64(mdat + 8 * 15);
    #endif /* defined(__COMPILE_EMPHASIS_SIZE__) */

        for (i = 16; i < 80; i++)
        {
            MESSAGE_SCHEDULE_0_15(W, i);
        }

        /* 
         6.4.2 SHA-512 Hash Computation
         2. Initialize the eight working variables, a, b, c, d, e, f, g, and h, with the (i-1)st hash value
         */
        a = H[0];
        b = H[1];
        c = H[2];
        d = H[3];
        e = H[4];
        f = H[5];
        g = H[6];
        h = H[7];

    #if defined(__COMPILE_EMPHASIS_SIZE__)
        for (i = 0; i < 80; i++)
        {
            t1 = h + Sigma1_512(e) + Ch(e, f, g) + sha_384_512_K[i] + W[i];
            t2 = Sigma0_512(a) + Maj(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }
    #else /* __COMPILE_EMPHASIS_SPEED__ */
        for (i = 0; i < 80; i += 8)
        {

        #define MESSAGE_SCHEDULE_16_79(x1, x2, x3, x4, x5, x6, x7, x8, idx)                 \
        {                                                                                   \
            t1 = x8 + Sigma1_512(x5) + Ch(x5, x6, x7) + sha_384_512_K[idx] + W[idx];        \
            t2 = Sigma0_512(x1) + Maj(x1, x2, x3);                                          \
            x4 += t1;                                                                       \
            x8 = t1 + t2;                                                                   \
        }

            MESSAGE_SCHEDULE_16_79(a, b, c, d, e, f, g, h, i)
            MESSAGE_SCHEDULE_16_79(h, a, b, c, d, e, f, g, i + 1)
            MESSAGE_SCHEDULE_16_79(g, h, a, b, c, d, e, f, i + 2)
            MESSAGE_SCHEDULE_16_79(f, g, h, a, b, c, d, e, i + 3)
            MESSAGE_SCHEDULE_16_79(e, f, g, h, a, b, c, d, i + 4)
            MESSAGE_SCHEDULE_16_79(d, e, f, g, h, a, b, c, i + 5)
            MESSAGE_SCHEDULE_16_79(c, d, e, f, g, h, a, b, i + 6)
            MESSAGE_SCHEDULE_16_79(b, c, d, e, f, g, h, a, i + 7)
        }
        #undef MESSAGE_SCHEDULE_16_79
    #endif /* defined__COMPILE_EMPHASIS_SIZE__ */

        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
        H[5] += f;
        H[6] += g;
        H[7] += h;
        mdat += 128;
        block--;
    }

    for (i = 0; i < 8; i++)
    {
        hdat[(i * 8) + 0] = (uint8_t) (H[i] >> 56);
        hdat[(i * 8) + 1] = (uint8_t) ((H[i] >> 48) & 0xff);
        hdat[(i * 8) + 2] = (uint8_t) ((H[i] >> 40) & 0xff);
        hdat[(i * 8) + 3] = (uint8_t) ((H[i] >> 32) & 0xff);
        hdat[(i * 8) + 4] = (uint8_t) ((H[i] >> 24) & 0xff);
        hdat[(i * 8) + 5] = (uint8_t) ((H[i] >> 16) & 0xff);
        hdat[(i * 8) + 6] = (uint8_t) ((H[i] >> 8) & 0xff);
        hdat[(i * 8) + 7] = (uint8_t) (H[i] & 0xff);
    }

    /* erase data for safety */
    a = b = c = d = e = f = g = h = t1 = t2 = 0;
    i = 0;
    memset_func(work, 0, 8 * (80 + 8));

    return;
} /* End of function R_Sha512_Hash() */

#endif /* defined__SUPPORT_SHA384__ || defined__SUPPORT_SHA512__ */

