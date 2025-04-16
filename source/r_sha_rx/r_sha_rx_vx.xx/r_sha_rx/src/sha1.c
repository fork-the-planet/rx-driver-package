/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         sha1.c
 * @brief        The code of calculation processing for SHA-1
 **********************************************************************************************************************/
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include "r_sha.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#if defined(__SUPPORT_SHA1__)

    #if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__) /* RL78 support only for LITTLE */
        #define _LIT
    #endif /* defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__) */

    #if defined(_LIT) || defined(__LIT) /*  Define "LITTLE_ENDIAN" directly in case of these are not defined */
        #ifndef LITTLE_ENDIAN_Compiler
            #define LITTLE_ENDIAN_Compiler
        #endif
    #endif

/*
 The words of the second 5-word buffer are labeled H0, H1, H2, H3, H4.
 The words of the 80-word sequence are labeled W0, W1, ... , W79.
 A single word buffer TEMP is also employed.
 */
/*
 The above assumes that the sequence W0, ... , W79 is implemented as an array of eighty 32-bit words.
 This is efficient from the standpoint of minimization of execution time, since the addresses of Wt-3, ... , Wt-16
 in step (b) are easily computed. If space is at a premium, an alternative is to regard { Wt } as a circular queue,
 which may be implemented using an array of sixteen 32-bit words W[0], ... W[15].
 In this case, in hex let MASK = 0000000F. Then processing of Mi is as follows:
 */

    #define WORDS               (16)
    #define FIVE_WORD_BUFFER    (5)

/* circular left shift operation S(x, n) */
    #define S(x,n) (((x)<<(n))^((x)>>(32-(n)))) /* left rotate shift by n bits */
    #define S1(x) (S((x),1))
    #define S5(x) (S((x),5))
    #define S30(x) (S((x),30))

/*
 A sequence of constant words K0, K1, ... , K79 is used in the SHA-1. In hex these are given by
 Kt = 5A827999 (0 <= t <= 19)
 Kt = 6ED9EBA1 (20 <= t <= 39)
 Kt = 8F1BBCDC (40 <= t <= 59)
 Kt = CA62C1D6 (60 <= t <= 79).
 */
    #define K0_19        (0x5A827999)
    #define K20_39       (0x6ED9EBA1)
    #define K40_59       (0x8F1BBCDC)
    #define K60_79       (0xCA62C1D6)

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
/***********************************************************************************************************************
 * Declaration  : void R_Sha1_Hash (uint8_t near *mdat, uint8_t near *hdat, uint16_t block, void *work)
 * Function Name: R_Sha1_Hash
 * Description  : Secure hash algorithms based on SHA-1 specification to computing a condensed representation of
 * electronic data (message).
 * Arguments    : mdat Input data pointer.
 *                hdat Output destination of the hash value, a 20-byte area is required.
 *                block Nnumber of blocks of input data, where block > 0.
 *                work Work area pointer.
 * Return Value : none.
 **********************************************************************************************************************/
void R_Sha1_Hash (uint8_t near *mdat, uint8_t near *hdat, uint16_t block, void *work /* not used */)
{
    uint32_t A;
    uint32_t B;
    uint32_t C;
    uint32_t D;
    uint32_t E;
    uint32_t TEMP;
    uint32_t H[FIVE_WORD_BUFFER];
    uint32_t W[WORDS];
    uint32_t s;
    uint32_t t;

    volatile memset_t memset_func = &memset;

    for (s = 0; s < FIVE_WORD_BUFFER; ++s)
    {
        H[s] = ((uint32_t) hdat[(s * 4) + 0] << 24) ^ ((uint32_t) hdat[(s * 4) + 1] << 16)
                ^ ((uint32_t) hdat[(s * 4) + 2] << 8) ^ ((uint32_t) hdat[(s * 4) + 3]);
    }

    while (block != 0)
    {

        for (t = 0; t < WORDS; ++t)
        {
            W[t] = ((uint32_t) mdat[(t * 4) + 0] << 24) ^ ((uint32_t) mdat[(t * 4) + 1] << 16)
                    ^ ((uint32_t) mdat[(t * 4) + 2] << 8) ^ ((uint32_t) mdat[(t * 4) + 3]);
        }

        A = H[0];
        B = H[1];
        C = H[2];
        D = H[3];
        E = H[4];

        for (t = 0; t < 80; ++t)
        {

            s = t & 0xf;

            if (t >= 16)
            {
                W[s] ^= (W[(s + 13) & 0xf] ^ W[(s + 8) & 0xf] ^ W[(s + 2) & 0xf]);
                W[s] = S1(W[s]);
            }

            if (t <= 19)
            {
                TEMP = S5(A) + ((B & C) | (( ~B) & D)) + E + W[s] + K0_19;
            }
            else if (t <= 39)
            {
                TEMP = S5(A) + (B ^ C ^ D) + E + W[s] + K20_39;
            }
            else if (t <= 59)
            {
                TEMP = S5(A) + ((B & C) | (B & D) | (C & D)) + E + W[s] + K40_59;
            }
            else
            {
                TEMP = S5(A) + (B ^ C ^ D) + E + W[s] + K60_79;
            }

            E = D;
            D = C;
            C = S30(B);
            B = A;
            A = TEMP;
        }

        H[0] += A;
        H[1] += B;
        H[2] += C;
        H[3] += D;
        H[4] += E;

        mdat += 64;
        --block;
    }

    for (s = 0; s < FIVE_WORD_BUFFER; ++s)
    {
        hdat[(s * 4) + 0] = (uint8_t) (H[s] >> 24);
        hdat[(s * 4) + 1] = (uint8_t) ((H[s] >> 16) & 0xff);
        hdat[(s * 4) + 2] = (uint8_t) ((H[s] >> 8) & 0xff);
        hdat[(s * 4) + 3] = (uint8_t) (H[s] & 0xff);
    }
    /* clear local variables */
    A = 0;
    B = 0;
    C = 0;
    D = 0;
    E = 0;
    TEMP = 0;
    memset_func(H, 0, FIVE_WORD_BUFFER * sizeof(uint32_t));
    memset_func(W, 0, WORDS * sizeof(uint32_t));
    s = 0;
    t = 0;
} /* End of function R_Sha1_Hash() */

#endif /* defined__SUPPORT_SHA1__ */
