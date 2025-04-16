/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         shaif.h
 * @brief        The code of calculation processing for MD5/SHA-1/SHA-256/SHA-384/SHA-512
 **********************************************************************************************************************/
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "r_sha.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)  /* RL78 support only for LITTLE */
    #define _LIT
#endif

    #if defined(_LIT) || defined(__LIT) /*  Define "LITTLE_ENDIAN" directly in case of these are not defined */
        #ifndef LITTLE_ENDIAN_Compiler
            #define LITTLE_ENDIAN_Compiler
        #endif
    #endif

#if defined(MD5)
    #define FUNC_HASH(n)    R_##Md##n##_Hash
#else
    #define FUNC_HASH(n)    R_##Sha##n##_Hash
#endif /* defined(MD5) */
#define HASH(n) FUNC_HASH(n)

/* core function */
extern void R_Sha1_Hash (uint8_t near *, uint8_t near *, uint16_t, void *);
extern void R_Sha256_Hash (uint8_t near *, uint8_t near *, uint16_t, void *);
extern void R_Sha384_Hash (uint8_t near *, uint8_t near *, uint16_t, void *);
extern void R_Sha512_Hash (uint8_t near *, uint8_t near *, uint16_t, void *);
extern void R_Md5_Hash (uint8_t near *, uint8_t near *, uint16_t);

/* SHA1: Block Size= 512, Word Size=32, MD Size=160 [bit] */
#define SHA1_MD8_LEN        (20)
#define SHA1_MD32_LEN       (5)
#define SHA1_BLOCK8_LEN     (64)
#define SHA1_BLOCK32_LEN    (16)

/* SHA256: Block Size= 512, Word Size=32, MD Size=256 [bit] */
#define SHA256_MD8_LEN      (32)
#define SHA256_MD32_LEN     (8)
#define SHA256_BLOCK8_LEN   (64)
#define SHA256_BLOCK32_LEN  (16)
/* SHA384: Block Size= 1024, Word Size=64, MD Size=384 [bit] */
#define SHA384_MD8_LEN      (48)
#define SHA384_MD32_LEN     (12)
#define SHA384_MD64_LEN     (6)
#define SHA384_BLOCK8_LEN   (128)
#define SHA384_BLOCK32_LEN  (32)
#define SHA384_BLOCK64_LEN  (16)
/* SHA512: Block Size= 1024, Word Size=64, MD Size=512 [bit] */
#define SHA512_MD8_LEN      (64)
#define SHA512_MD32_LEN     (16)
#define SHA512_MD64_LEN     (8)
#define SHA512_BLOCK8_LEN   (128)
#define SHA512_BLOCK32_LEN  (32)
#define SHA512_BLOCK64_LEN  (16)

#if defined(MD5)
    #define MD_SIZE             5
    #define HASH_DIGEST         R_Md5_HashDigest
    #define SHA_MD8_LEN         MD5_MD8_LEN
    #define SHA_MD32_LEN        MD5_MD32_LEN
    #define SHA_BLOCK8_LEN      MD5_BLOCK8_LEN
    #define SHA_BLOCK32_LEN     MD5_BLOCK32_LEN
#elif defined(SHA1)
    #define MD_SIZE             1
    #define HASH_DIGEST         R_Sha1_HashDigest
    #define SHA_MD8_LEN         SHA1_MD8_LEN
    #define SHA_MD32_LEN        SHA1_MD32_LEN
    #define SHA_BLOCK8_LEN      SHA1_BLOCK8_LEN
    #define SHA_BLOCK32_LEN     SHA1_BLOCK32_LEN
#elif defined(SHA256)
    #define MD_SIZE             256
    #define HASH_DIGEST         R_Sha256_HashDigest
    #define SHA_MD8_LEN         SHA256_MD8_LEN
    #define SHA_MD32_LEN        SHA256_MD32_LEN
    #define SHA_BLOCK8_LEN      SHA256_BLOCK8_LEN
    #define SHA_BLOCK32_LEN     SHA256_BLOCK32_LEN
#elif defined(SHA384)
    #define MD_SIZE             512
    #define HASH_DIGEST         R_Sha384_HashDigest
/* SHA384 uses SHA512 inside, so set to SHA512 */
    #define SHA_MD8_LEN         SHA512_MD8_LEN
    #define SHA_MD32_LEN        SHA512_MD32_LEN
    #define SHA_MD64_LEN        SHA512_MD64_LEN
    #define SHA_BLOCK8_LEN      SHA512_BLOCK8_LEN
    #define SHA_BLOCK32_LEN     SHA512_BLOCK32_LEN
#elif defined(SHA512)
    #define MD_SIZE             512
    #define HASH_DIGEST         R_Sha512_HashDigest
    #define SHA_MD8_LEN         SHA512_MD8_LEN
    #define SHA_MD32_LEN        SHA512_MD32_LEN
    #define SHA_MD64_LEN        SHA512_MD64_LEN
    #define SHA_BLOCK8_LEN      SHA512_BLOCK8_LEN
    #define SHA_BLOCK32_LEN     SHA512_BLOCK32_LEN
#else
    #error "None-support SHA"
#endif /* definedMD5 */

#if defined(SHA384) || defined(SHA512)
    #define MIN_PADDING_AREA  (16+1)    /* 128-bit for the number l and 8-bit for the end of message */
#else
    #define MIN_PADDING_AREA  (8+1)     /* 64-bit for the number l and 8-bit for the end of message */
#endif /* defined(SHA384) || defined(SHA512) */

#if defined(SHA512)
/*
 5.3.5 SHA-512
 For SHA-512, the initial hash value, H(0), shall consist of the following eight 64-bit words, in hex:
 H0 = 6a09e667f3bcc908
 H1 = bb67ae8584caa73b
 H2 = 3c6ef372fe94f82b
 H3 = a54ff53a5f1d36f1
 H4 = 510e527fade682d1
 H5 = 9b05688c2b3e6c1f
 H6 = 1f83d9abfb41bd6b
 H7 = 5be0cd19137e2179
 */
static const union
{
    uint8_t initValue[8*8];
    uint64_t dummy;
} far initialHahValues =
{
    {
        0x6a, 0x09, 0xe6, 0x67, 0xf3, 0xbc, 0xc9, 0x08,
        0xbb, 0x67, 0xae, 0x85, 0x84, 0xca, 0xa7, 0x3b,
        0x3c, 0x6e, 0xf3, 0x72, 0xfe, 0x94, 0xf8, 0x2b,
        0xa5, 0x4f, 0xf5, 0x3a, 0x5f, 0x1d, 0x36, 0xf1,
        0x51, 0x0e, 0x52, 0x7f, 0xad, 0xe6, 0x82, 0xd1,
        0x9b, 0x05, 0x68, 0x8c, 0x2b, 0x3e, 0x6c, 0x1f,
        0x1f, 0x83, 0xd9, 0xab, 0xfb, 0x41, 0xbd, 0x6b,
        0x5b, 0xe0, 0xcd, 0x19, 0x13, 0x7e, 0x21, 0x79,
    }
};
#elif defined(SHA384)
/*
 5.3.4 SHA-384
 For SHA-384, the initial hash value, H(0), shall consist of the following eight 64-bit words, in
 hex:
 H0 = cbbb9d5dc1059ed8
 H1 = 629a292a367cd507
 H2 = 9159015a3070dd17
 H3 = 152fecd8f70e5939
 H4 = 67332667ffc00b31
 H5 = 8eb44a8768581511
 H6 = db0c2e0d64f98fa7
 H7 = 47b5481dbefa4fa4
 */
static const union
{
    uint8_t initValue[8*8];
    uint64_t dummy;
} far initialHahValues =
{
    {
        0xcb, 0xbb, 0x9d, 0x5d, 0xc1, 0x05, 0x9e, 0xd8,
        0x62, 0x9a, 0x29, 0x2a, 0x36, 0x7c, 0xd5, 0x07,
        0x91, 0x59, 0x01, 0x5a, 0x30, 0x70, 0xdd, 0x17,
        0x15, 0x2f, 0xec, 0xd8, 0xf7, 0x0e, 0x59, 0x39,
        0x67, 0x33, 0x26, 0x67, 0xff, 0xc0, 0x0b, 0x31,
        0x8e, 0xb4, 0x4a, 0x87, 0x68, 0x58, 0x15, 0x11,
        0xdb, 0x0c, 0x2e, 0x0d, 0x64, 0xf9, 0x8f, 0xa7,
        0x47, 0xb5, 0x48, 0x1d, 0xbe, 0xfa, 0x4f, 0xa4,
    }
};
#endif /* definedSHA512 */

typedef struct
{
    uint32_t dummy;
    uint32_t length;
    union
    {
        uint8_t  md8[SHA512_MD8_LEN];
        uint32_t md32[SHA512_MD32_LEN];
#if defined(SHA384) || defined(SHA512)
    uint64_t md64[SHA512_MD64_LEN];
#endif
} hash;
#if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)
uint8_t buff[SHA256_BLOCK8_LEN];
uint32_t position;
uint32_t sha_work[16+8]; /* support SHA1 & SHA256 */
#else
uint8_t  buff[SHA512_BLOCK8_LEN];
uint32_t position;
uint64_t sha_work[80 + 8]; /* support SHA1 & SHA256 & SHA384 */
#endif /* defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__) */
} R_shaDomain;

int8_t
#if defined(MD5)
/***********************************************************************************************************************
 * Declaration  : R_Md5_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work)
 * Function Name: R_Md5_HashDigest
 * Description  : Secure hash algorithms based on MD5 specification to computing a condensed representation of
 * electronic data (message).
 * Arguments    : mdat Address of a input message.
 *                hdat Address of message digest.
 *                len Length of message (unit : byte).
 *                flag Control flag.
 *                work Address of work area.
 * Return Value : R_PROCESS_COMPLETE Normal end.
 *                R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 *                R_SHA_ERROR_FLAG Incorrect flag is specified.
 *                R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 **********************************************************************************************************************/
R_Md5_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work)
#elif defined(SHA1)
/***********************************************************************************************************************
 * Declaration  : R_Sha1_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work)
 * Function Name: R_Sha1_HashDigest
 * Description  : Secure hash algorithms based on SHA-1 specification to computing a condensed representation of
 * electronic data (message).
 * Arguments    : mdat Address of a input message.
 *                hdat Address of message digest.
 *                len Length of message (unit : byte).
 *                flag Control flag.
 *                work Address of work area.
 * Return Value : R_PROCESS_COMPLETE Normal end.
 *                R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 *                R_SHA_ERROR_FLAG Incorrect flag is specified.
 *                R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 **********************************************************************************************************************/
R_Sha1_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work)
#elif defined(SHA256)
/***********************************************************************************************************************
 * Declaration  : R_Sha256_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag,
 * void near *work)
 * Function Name: R_Sha256_HashDigest
 * Description  : Secure hash algorithms based on SHA-256 specification to computing a condensed representation of
 * electronic data (message).
 * Arguments    : mdat Address of a input message.
 *                hdat Address of message digest.
 *                len Length of message (unit : byte).
 *                flag Control flag.
 *                work Address of work area.
 * Return Value : R_PROCESS_COMPLETE Normal end.
 *                R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 *                R_SHA_ERROR_FLAG Incorrect flag is specified.
 *                R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 **********************************************************************************************************************/
R_Sha256_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work)
#elif defined(SHA384)
/***********************************************************************************************************************
 * Declaration  : R_Sha384_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag,
 * void near *work)
 * Function Name: R_Sha384_HashDigest
 * Description  : Secure hash algorithms based on SHA-384 specification to computing a condensed representation of
 * electronic data (message).
 * Arguments    : mdat Address of a input message.
 *                hdat Address of message digest.
 *                len Length of message (unit : byte).
 *                flag Control flag.
 *                work Address of work area.
 * Return Value : R_PROCESS_COMPLETE Normal end.
 *                R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 *                R_SHA_ERROR_FLAG Incorrect flag is specified.
 *                R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 **********************************************************************************************************************/
R_Sha384_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work)
#elif defined(SHA512)
/***********************************************************************************************************************
 * Declaration  : R_Sha512_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag,
 * void near *work)
 * Function Name: R_Sha512_HashDigest
 * Description  : Secure hash algorithms based on SHA-512 specification to computing a condensed representation of
 * electronic data (message).
 * Arguments    : mdat Address of a input message.
 *                hdat Address of message digest.
 *                len Length of message (unit : byte).
 *                flag Control flag.
 *                work Address of work area.
 * Return Value : R_PROCESS_COMPLETE Normal end.
 *                R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 *                R_SHA_ERROR_FLAG Incorrect flag is specified.
 *                R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 **********************************************************************************************************************/
R_Sha512_HashDigest(uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work)
#endif
{
uint16_t i;
uint16_t n;
R_shaDomain near *d = (R_shaDomain near *)work;
uint8_t near *src;
uint8_t near *dst;

/* check input parameter */
if ((work == NULL) || (hdat == NULL))
{
    return R_SHA_ERROR_POINTER;
}
if (flag & R_SHA_NOPADDING)
{
    if (!(flag & R_SHA_FINISH))
    {
        return R_SHA_ERROR_FLAG;
    }
}
else
{
    if ((flag != R_SHA_ADD) && (flag != R_SHA_INIT) && (flag != R_SHA_FINISH) && (flag != (R_SHA_INIT | R_SHA_FINISH)))
    {
        return R_SHA_ERROR_FLAG;
    }
}
if ((len != 0) && (mdat == NULL))
{
    return R_SHA_ERROR_LENGTH;
}

if (flag & R_SHA_INIT)
{
    d->position = 0;
    d->length = 0;
    d->dummy = 0;
#if defined(MD5)
    #if defined(LITTLE_ENDIAN_Compiler)
    d->hash.md32[0] = 0x67452301UL;
    d->hash.md32[1] = 0xefcdab89UL;
    d->hash.md32[2] = 0x98badcfeUL;
    d->hash.md32[3] = 0x10325476UL;
    #else
    d->hash.md32[0] = 0x01234567UL;
    d->hash.md32[1] = 0x89abcdefUL;
    d->hash.md32[2] = 0xfedcba98UL;
    d->hash.md32[3] = 0x76543210UL;
    #endif /* definedMD5 */
#elif defined(SHA1)
    /*
     "7. COMPUTING THE MESSAGE DIGEST" says
     Before processing any blocks, the {Hj} are initialized as follows: in hex,
     H0 = 67452301
     H1 = EFCDAB89
     H2 = 98BADCFE
     H3 = 10325476
     H4 = C3D2E1F0.
     */
    #if defined(LITTLE_ENDIAN_Compiler)
    d->hash.md32[0] = 0x01234567UL;
    d->hash.md32[1] = 0x89abcdefUL;
    d->hash.md32[2] = 0xfedcba98UL;
    d->hash.md32[3] = 0x76543210UL;
    d->hash.md32[4] = 0xf0e1d2c3UL;
    #else
    d->hash.md32[0] = 0x67452301UL;
    d->hash.md32[1] = 0xefcdab89UL;
    d->hash.md32[2] = 0x98badcfeUL;
    d->hash.md32[3] = 0x10325476UL;
    d->hash.md32[4] = 0xc3d2e1f0UL;
    #endif /* definedLITTLE_ENDIAN */
#elif defined(SHA256)
    /*
     5.3.2 SHA-256
     For SHA-256, the initial hash value, H(0), shall consist of the following eight 32-bit words, in
     hex:
     H0 = 6a09e667
     H1 = bb67ae85
     H2 = 3c6ef372
     H3 = a54ff53a
     H4 = 510e527f
     H5 = 9b05688c
     H6 = 1f83d9ab
     H7 = 5be0cd19
     */

    #if defined(LITTLE_ENDIAN_Compiler)
    d->hash.md32[0] = 0x67e6096aUL;
    d->hash.md32[1] = 0x85ae67bbUL;
    d->hash.md32[2] = 0x72f36e3cUL;
    d->hash.md32[3] = 0x3af54fa5UL;
    d->hash.md32[4] = 0x7f520e51UL;
    d->hash.md32[5] = 0x8c68059bUL;
    d->hash.md32[6] = 0xabd9831fUL;
    d->hash.md32[7] = 0x19cde05bUL;
    #else
    d->hash.md32[0] = 0x6a09e667UL;
    d->hash.md32[1] = 0xbb67ae85UL;
    d->hash.md32[2] = 0x3c6ef372UL;
    d->hash.md32[3] = 0xa54ff53aUL;
    d->hash.md32[4] = 0x510e527fUL;
    d->hash.md32[5] = 0x9b05688cUL;
    d->hash.md32[6] = 0x1f83d9abUL;
    d->hash.md32[7] = 0x5be0cd19UL;
    #endif /* definedSHA256 */
#elif defined(SHA512) || defined(SHA384)
    memcpy(d->hash.md32, (void *)&initialHahValues, 64);
#endif
}

/* midway process */
d->length += len; /* update the total length of message */

if ((d->position + len) < SHA_BLOCK8_LEN) /* in case less than one block */
{
    for (i = 0, dst = &d->buff[d->position]; i < len; ++i)
    {
        *dst++ = *mdat++;
    }
    d->position += len;
    len = 0;
}
else /* in case at least one block */
{
    if (d->position != 0) /* buff is occupied */
    {
        for (i = (SHA_BLOCK8_LEN - (uint16_t)d->position), dst = &(d->buff[d->position]); i; --i)
        {
            *dst++ = *mdat++;
        }
        HASH(MD_SIZE)(d->buff, d->hash.md8, 1, (void *)(d->sha_work)); /* one block processed */
        len -= (SHA_BLOCK8_LEN - (uint16_t)d->position); /* update length */
    }

    n = len / SHA_BLOCK8_LEN; /* how many blocks to process */
    if (n > 0)
    {
        HASH(MD_SIZE)(mdat, d->hash.md8, n, (void *)(d->sha_work)); /* n block processed */
        mdat += (n * SHA_BLOCK8_LEN); /* update pointer */
        len -= (n * SHA_BLOCK8_LEN); /* update length */
    }

    for (i = len, dst = d->buff; i; --i)
    {
        *dst++ = *mdat++; /* move the rest to the buffer */
    }
    d->position = len;
}

/*********************/
/* finish flag check */
/*********************/
if (flag & R_SHA_FINISH) /* le dernier bloc qui a besoin de faire padding */
{
    /*
     "4. MESSAGE PADDING" says
     a. "1" is appended. Example: if the original message is "01010000", this is padded to
     "010100001".
     b. "0"s are appended. The number of "0"s will depend on the original length of the
     message. The last 64 bits of the last 512-bit block are reserved for the length l of the
     original message.
     c. Obtain the 2-word representation of l, the number of bits in the original message. If
     l < 2**32 then the first word is all zeroes. Append these two words to the padded message.
     */

    /* According a. */
    /*
     If (flag&4) == 1,
     then padding data is included in data and data size is n*SHA_BLOCK8_LEN.
     Therefore, Hash Function has called including padding data,
     so outputting digest is enough.
     */
    if (!(flag & R_SHA_NOPADDING))
    {
        d->buff[d->position] = 0x80;

        if ((SHA_BLOCK8_LEN - d->position) >= MIN_PADDING_AREA) /* another block unnecessary */
        {
            /* 4 comes from supporting only l < 2**32 case */
            for (i = ((uint16_t)d->position + 1); i < (SHA_BLOCK8_LEN - 4); ++i)
            {
                d->buff[i] = 0;
            }
        }
        else /* another block necessary */
        {

            for (i = ((uint16_t)d->position + 1); i < SHA_BLOCK8_LEN; ++i)
            {
                d->buff[i] = 0;
            }
            HASH(MD_SIZE)(d->buff, d->hash.md8, 1, (void *)(d->sha_work)); /* last but one */
            for (i = (SHA_BLOCK8_LEN - 4), dst = d->buff; i; --i)
            {
                *dst++ = 0;
            }
        }
#if defined(MD5)
        d->buff[SHA_BLOCK8_LEN-8] = (uint8_t)((d->length * 8) & 0xff);
        d->buff[SHA_BLOCK8_LEN-7] = (uint8_t)((d->length * 8) >> 8 & 0xff);
        d->buff[SHA_BLOCK8_LEN-6] = (uint8_t)((d->length * 8) >> 16 & 0xff);
        d->buff[SHA_BLOCK8_LEN-5] = (uint8_t)((d->length * 8) >> 24);
        d->buff[SHA_BLOCK8_LEN-4] = 0;
        d->buff[SHA_BLOCK8_LEN-3] = 0;
        d->buff[SHA_BLOCK8_LEN-2] = 0;
        d->buff[SHA_BLOCK8_LEN-1] = 0;
#else
        /* According 5.1, but support only l < 2**32 case */
        d->buff[SHA_BLOCK8_LEN-4] = (uint8_t)((d->length * 8) >> 24);
        d->buff[SHA_BLOCK8_LEN-3] = (uint8_t)(((d->length * 8) >> 16) & 0xff);
        d->buff[SHA_BLOCK8_LEN-2] = (uint8_t)(((d->length * 8) >> 8) & 0xff);
        d->buff[SHA_BLOCK8_LEN-1] = (uint8_t)((d->length * 8) & 0xff);
#endif /* definedMD5 */

        HASH(MD_SIZE)(d->buff, d->hash.md8, 1, (void *)(d->sha_work)); /* the final one */
    }

#if defined(SHA384)
    for (i = SHA384_MD8_LEN, src = d->hash.md8, dst = hdat; i; --i)
    {
        *dst++ = *src++; /* output digest */
    }
#else
    for (i = SHA_MD8_LEN, src = d->hash.md8, dst = hdat; i; --i)
    {
        *dst++ = *src++; /* output digest */
    }
#endif /* definedSHA384 */
}
return R_PROCESS_COMPLETE;
}

