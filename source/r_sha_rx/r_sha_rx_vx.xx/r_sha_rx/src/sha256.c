/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         sha256.c
 * @brief        The code of calculation processing for SHA-256
 **********************************************************************************************************************/
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include "r_sha.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#if defined(__SUPPORT_SHA256__)

    #if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__) /* RL78 support only for LITTLE */
        #define _LIT
    #endif

    #if defined(_LIT) || defined(__LIT) /*  Define "LITTLE_ENDIAN" directly in case of these are not defined */
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

/* ---- SHA-256 ---- */
    #define ROTR(x,n)  (((x)>>(n))^((x)<<(32-(n))))
    #define SFTR(x,n)  ((x)>>(n))
    #define CH(x,y,z)  (((x)&(y))^(~(x)&(z)))
    #define MAJ(x,y,z) (((x)&(y))^((x)&(z))^((y)&(z)))
    #define SIGB0(x)   (ROTR((x),2)^ROTR((x),13)^ROTR((x),22))
    #define SIGB1(x)   (ROTR((x),6)^ROTR((x),11)^ROTR((x),25))
    #define SIGS0(x)   (ROTR((x),7)^ROTR((x),18)^SFTR((x),3))
    #define SIGS1(x)   (ROTR((x),17)^ROTR((x),19)^SFTR((x),10))
    #define LOAD4B(x)  ((uint32_t)*((x)+3)^(uint32_t)*((x)+2)<<8^(uint32_t)*((x)+1)<<16^(uint32_t)*((x)+0)<<24)
    #define ROUND1(a,b,c,d,e,f,g,h,n){\
W[n] = LOAD4B( mdat+(n)*4 );\
h = h + SIGB1(e) + CH(e,f,g) + K[n] + W[n];\
d = d + h;\
h = h + SIGB0(a) + MAJ(a,b,c);\
}
    #define ROUND2(a,b,c,d,e,f,g,h,n) {\
W[n&15] = SIGS1(W[(n-2)&15]) + W[(n-7)&15] + SIGS0(W[(n-15)&15]) + W[(n-16)&15];\
h = h + SIGB1(e) + CH(e,f,g) + K[n] + W[n&15];\
d = d + h;\
h = h + SIGB0(a) + MAJ(a,b,c);\
}

static const uint32_t far K[64] =
{ 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98,
        0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
        0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8,
        0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
        0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
        0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
        0xc67178f2 };

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
 * Declaration  : void R_Sha256_Hash (uint8_t near *mdat, uint8_t near *hdat, uint16_t block, void *work)
 * Function Name: R_Sha256_Hash
 * Description  : Secure hash algorithms based on SHA-256 specification to computing a condensed representation of
 * electronic data (message)
 * Arguments    : mdat Input data pointer.
 *                hdat Output destination of the hash value, a 32-byte area is required.
 *                block Number of blocks of input data, where block > 0.
 *                work Work area pointer.
 * Return Value : none.
 **********************************************************************************************************************/
void R_Sha256_Hash (uint8_t near *mdat, uint8_t near *hdat, uint16_t block, void *work)
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    uint32_t *W;
    uint32_t *Z;
    #if defined(__COMPILE_EMPHASIS_SIZE__)
    uint32_t t1;
    uint32_t t2;
    uint32_t i;
    #endif

    volatile memset_t memset_func = &memset;

    W = (uint32_t *) work;
    Z = W + 16;

    #ifdef LITTLE_ENDIAN_Compiler  /* Little Endian */
    Z[0] = LOAD4B(hdat + 0);
    Z[1] = LOAD4B(hdat + 4);
    Z[2] = LOAD4B(hdat + 8);
    Z[3] = LOAD4B(hdat + 12);
    Z[4] = LOAD4B(hdat + 16);
    Z[5] = LOAD4B(hdat + 20);
    Z[6] = LOAD4B(hdat + 24);
    Z[7] = LOAD4B(hdat + 28);
    #else  /* Big Endian */
    Z[0] = ((uint32_t *) hdat)[0];
    Z[1] = ((uint32_t *) hdat)[1];
    Z[2] = ((uint32_t *) hdat)[2];
    Z[3] = ((uint32_t *) hdat)[3];
    Z[4] = ((uint32_t *) hdat)[4];
    Z[5] = ((uint32_t *) hdat)[5];
    Z[6] = ((uint32_t *) hdat)[6];
    Z[7] = ((uint32_t *) hdat)[7];
    #endif /* Little Endian */

    while (block != 0)
    {

        a = Z[0];
        b = Z[1];
        c = Z[2];
        d = Z[3];
        e = Z[4];
        f = Z[5];
        g = Z[6];
        h = Z[7];

    #if defined(__COMPILE_EMPHASIS_SIZE__)
        for(i=0; i<16; i++)
        {
            W[i]=LOAD4B(mdat+i*4);
            t1=(uint32_t)K[i];
            t1=h+SIGB1(e)+K[i]+W[i];
            t1=h+SIGB1(e)+CH(e,f,g)+K[i]+W[i];
            t2=SIGB0(a)+MAJ(a,b,c);
            h=g;
            g=f;
            f=e;
            e=d+t1;
            d=c;
            c=b;
            b=a;
            a=t1+t2;
        }

        for(i=16; i<64; i++)
        {
            W[i&15]=SIGS1(W[(i-2)&15])+W[(i-7)&15]+SIGS0(W[(i-15)&15])+W[(i-16)&15];
            t1=h+SIGB1(e)+CH(e, f, g)+K[i]+W[i&15];
            t2=SIGB0(a)+MAJ(a, b, c);
            h=g;
            g=f;
            f=e;
            e=d+t1;
            d=c;
            c=b;
            b=a;
            a=t1+t2;
        }
    #elif defined(__COMPILE_EMPHASIS_SPEED__)
        ROUND1(a, b, c, d, e, f, g, h, 0);
        ROUND1(h, a, b, c, d, e, f, g, 1);
        ROUND1(g, h, a, b, c, d, e, f, 2);
        ROUND1(f, g, h, a, b, c, d, e, 3);
        ROUND1(e, f, g, h, a, b, c, d, 4);
        ROUND1(d, e, f, g, h, a, b, c, 5);
        ROUND1(c, d, e, f, g, h, a, b, 6);
        ROUND1(b, c, d, e, f, g, h, a, 7);
        ROUND1(a, b, c, d, e, f, g, h, 8);
        ROUND1(h, a, b, c, d, e, f, g, 9);
        ROUND1(g, h, a, b, c, d, e, f, 10);
        ROUND1(f, g, h, a, b, c, d, e, 11);
        ROUND1(e, f, g, h, a, b, c, d, 12);
        ROUND1(d, e, f, g, h, a, b, c, 13);
        ROUND1(c, d, e, f, g, h, a, b, 14);
        ROUND1(b, c, d, e, f, g, h, a, 15);

        ROUND2(a, b, c, d, e, f, g, h, 16);
        ROUND2(h, a, b, c, d, e, f, g, 17);
        ROUND2(g, h, a, b, c, d, e, f, 18);
        ROUND2(f, g, h, a, b, c, d, e, 19);
        ROUND2(e, f, g, h, a, b, c, d, 20);
        ROUND2(d, e, f, g, h, a, b, c, 21);
        ROUND2(c, d, e, f, g, h, a, b, 22);
        ROUND2(b, c, d, e, f, g, h, a, 23);
        ROUND2(a, b, c, d, e, f, g, h, 24);
        ROUND2(h, a, b, c, d, e, f, g, 25);
        ROUND2(g, h, a, b, c, d, e, f, 26);
        ROUND2(f, g, h, a, b, c, d, e, 27);
        ROUND2(e, f, g, h, a, b, c, d, 28);
        ROUND2(d, e, f, g, h, a, b, c, 29);
        ROUND2(c, d, e, f, g, h, a, b, 30);
        ROUND2(b, c, d, e, f, g, h, a, 31);

        ROUND2(a, b, c, d, e, f, g, h, 32);
        ROUND2(h, a, b, c, d, e, f, g, 33);
        ROUND2(g, h, a, b, c, d, e, f, 34);
        ROUND2(f, g, h, a, b, c, d, e, 35);
        ROUND2(e, f, g, h, a, b, c, d, 36);
        ROUND2(d, e, f, g, h, a, b, c, 37);
        ROUND2(c, d, e, f, g, h, a, b, 38);
        ROUND2(b, c, d, e, f, g, h, a, 39);
        ROUND2(a, b, c, d, e, f, g, h, 40);
        ROUND2(h, a, b, c, d, e, f, g, 41);
        ROUND2(g, h, a, b, c, d, e, f, 42);
        ROUND2(f, g, h, a, b, c, d, e, 43);
        ROUND2(e, f, g, h, a, b, c, d, 44);
        ROUND2(d, e, f, g, h, a, b, c, 45);
        ROUND2(c, d, e, f, g, h, a, b, 46);
        ROUND2(b, c, d, e, f, g, h, a, 47);

        ROUND2(a, b, c, d, e, f, g, h, 48);
        ROUND2(h, a, b, c, d, e, f, g, 49);
        ROUND2(g, h, a, b, c, d, e, f, 50);
        ROUND2(f, g, h, a, b, c, d, e, 51);
        ROUND2(e, f, g, h, a, b, c, d, 52);
        ROUND2(d, e, f, g, h, a, b, c, 53);
        ROUND2(c, d, e, f, g, h, a, b, 54);
        ROUND2(b, c, d, e, f, g, h, a, 55);
        ROUND2(a, b, c, d, e, f, g, h, 56);
        ROUND2(h, a, b, c, d, e, f, g, 57);
        ROUND2(g, h, a, b, c, d, e, f, 58);
        ROUND2(f, g, h, a, b, c, d, e, 59);
        ROUND2(e, f, g, h, a, b, c, d, 60);
        ROUND2(d, e, f, g, h, a, b, c, 61);
        ROUND2(c, d, e, f, g, h, a, b, 62);
        ROUND2(b, c, d, e, f, g, h, a, 63);
    #endif /* defined__COMPILE_EMPHASIS_SIZE__ */

        Z[0] += a;
        Z[1] += b;
        Z[2] += c;
        Z[3] += d;
        Z[4] += e;
        Z[5] += f;
        Z[6] += g;
        Z[7] += h;

        mdat += 64;
        block--;
    }

    #ifdef LITTLE_ENDIAN_Compiler  /* Little endian */
    {
        uint32_t i;

        for (i = 0; i < 8; i++)
        {
            hdat[(i * 4) + 0] = (uint8_t) (Z[i] >> 24);
            hdat[(i * 4) + 1] = (uint8_t) ((Z[i] >> 16) & 0xff);
            hdat[(i * 4) + 2] = (uint8_t) ((Z[i] >> 8) & 0xff);
            hdat[(i * 4) + 3] = (uint8_t) (Z[i] & 0xff);
        }
        i = 0;
    }
    #else  /* Big Endian */
    ((uint32_t *) hdat)[0] = Z[0];
    ((uint32_t *) hdat)[1] = Z[1];
    ((uint32_t *) hdat)[2] = Z[2];
    ((uint32_t *) hdat)[3] = Z[3];
    ((uint32_t *) hdat)[4] = Z[4];
    ((uint32_t *) hdat)[5] = Z[5];
    ((uint32_t *) hdat)[6] = Z[6];
    ((uint32_t *) hdat)[7] = Z[7];
    #endif /* define LITTLE_ENDIAN */

    /* erase data for safety */
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
    g = 0;
    h = 0;
    memset_func(work, 0, 4 * (16 + 8));
    #if defined(__COMPILE_EMPHASIS_SIZE__)
    t1 = 0;
    t2 = 0;
    i = 0;
    #endif
} /* End of function R_Sha256_Hash() */

#endif  /* defined__SUPPORT_SHA256__ */
