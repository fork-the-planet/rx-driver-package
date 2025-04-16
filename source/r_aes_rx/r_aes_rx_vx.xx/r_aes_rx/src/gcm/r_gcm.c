/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         r_gcm.c
 * @brief        This module provides GCM mode.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "r_gcm.h"

/* ---------------------------------------------------------------------
 Prerequisites of this program:
 1.The data which uses this data structure(BIT_STRING) must be specified
 with multiple of 8 bits.
 2.Plain text(P), Chiper text(C), Additional Authenticated Data(AAD),
 Authentication tag(Tag), Initialize vector(IV), Key(K), are
 use this data structure.
 3.If these parameter has no 128bit alignment, user has to align 128bit
 with 0 padding to LSB.
 4.One block of this structure(BIT_STRING) is 128 bit.
 5.The definitions of these symbols are come from below.
 NIST Special Publication 800-38D :
 "4.1 Definitions and Abbreviations"
 -----------------------------------------------------------------------*/

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#define BLOCK_SIZE  (GCM_BLOCK_SIZE)
#define BYTE_SIZE   (8)
#define MAX_BIT     (BLOCK_SIZE * BYTE_SIZE)    /* GCM specifies 128 bits as data block. */

#if defined(_USE_ASM_VER)
    #if defined(__RX)
/* for 32-bit CPU */
        #define MUL_SIZE    (uint32_t)
        #define MUL_TIMES   (4)
    #else
/* for 16-bit CPU */
        #define MUL_SIZE    (uint16_t)
        #define MUL_TIMES   (8)
    #endif /* defined __RX */
#endif

#define GCM_STEP_ENC_1_2        (0x1001)
#define GCM_STEP_ENC_3          (0x1002)
#define GCM_STEP_ENC_3_LOOP     (0x1003)
#define GCM_STEP_ENC_4          (0x1004)
#define GCM_STEP_ENC_5          (0x1005)
#define GCM_STEP_ENC_5_LOOP     (0x1006)
#define GCM_STEP_ENC_6_7        (0x1007)

#define GCM_STEP_DEC_1_2_3      (0x2001)
#define GCM_STEP_DEC_4          (0x2002)
#define GCM_STEP_DEC_4_LOOP     (0x2003)
#define GCM_STEP_DEC_5          (0x2004)
#define GCM_STEP_DEC_6          (0x2005)
#define GCM_STEP_DEC_6_LOOP     (0x2006)
#define GCM_STEP_DEC_7_8        (0x2007)

#define GCM_STEP_COMPLETE       (0x4F4B)

#define GCM_NEXT_STEP(a,b,m1,m2)    if(a==b){a=m1;}else{a=m2;}

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef struct _bit_string
{
    /* bin[0] bin[1] bin[2] ...
     0x11   0x22   0x33   ...
     0x11223344556677   ...
     <-msb--------lsb->
     case (len == 128) */
    union
    {
        uint32_t l[BLOCK_SIZE / sizeof(uint32_t)];
        uint16_t w[BLOCK_SIZE / sizeof(uint16_t)];
        uint8_t  b[BLOCK_SIZE];
    } string;
    uint32_t len; /* shows number of bits. (shall be multiple of 8) */
} BIT_STRING;

typedef struct
{
    /* control */
    uint16_t   step;
    uint16_t   dummy1; /* for align */
    uint32_t   step_sub;
    int32_t    ret_val;
    /* arg */
    uint8_t    near *in;
    uint8_t    near *out;
    uint32_t   data_len;
    uint8_t    near *key;
    uint8_t    near *atag;
    uint32_t   atag_len;
    uint8_t    near *iv;
    uint32_t   iv_len;
    uint8_t    near *aad;
    uint32_t   aad_len;
    uint32_t   div_len;
    /* temp */
    BIT_STRING h_block;
    BIT_STRING j0;
    BIT_STRING s;
    BIT_STRING vu;
    BIT_STRING icb;
} gcm_work_t;

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
#if defined(_USE_ASM_VER)
extern void mul_body(MUL_SIZE bits, BIT_STRING near *v, BIT_STRING near *z);
extern natural_int_t xor(BIT_STRING near *src, BIT_STRING near *dst);
#endif

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
#if !defined(_USE_ASM_VER)
static natural_int_t right_shift_bit (BIT_STRING near *src);
static natural_int_t xor (BIT_STRING near *src, BIT_STRING near *dst);
#endif

static natural_int_t concat (BIT_STRING near *src_left, BIT_STRING near *src_right, BIT_STRING near *dst);
static natural_int_t msb (BIT_STRING near *src, BIT_STRING near *dst, natural_int_t num);
static natural_int_t lsb (BIT_STRING near *src, BIT_STRING near *dst, natural_int_t num);
static uint32_t get_int (BIT_STRING near *src);
static natural_int_t set_int (uint32_t src, BIT_STRING near *dst, natural_int_t int_base);
static natural_int_t inc (BIT_STRING near *x_src, BIT_STRING near *x_dst, natural_int_t s);
static natural_int_t mul (BIT_STRING near *src, BIT_STRING near *dst);
static natural_int_t xor_arg3 (BIT_STRING near *src1, BIT_STRING near *src2, BIT_STRING near *dst);
static natural_int_t ghash_arg2 (uint8_t near *src1, uint8_t near *src2, BIT_STRING near *dst, uint32_t len1,
        uint32_t len2, BIT_STRING near *h_block);
static natural_int_t ghash_arg3 (uint8_t near *src1, uint8_t near *src2, uint8_t near *src3, BIT_STRING near *dst,
        uint32_t len1, uint32_t len2, uint32_t len3, BIT_STRING near *h_block);
static natural_int_t gctr (BIT_STRING near *icb, uint8_t near *plain, uint8_t near *cipher, uint8_t near *key,
        uint32_t len);
static void ghash (uint8_t near *src, BIT_STRING near *dst, BIT_STRING near *h_block, uint32_t len);

#define CEIL(v,base) (((v)+(base)-1)/(base))
#define GET_LSB(x)  ((x).string.b[BLOCK_SIZE-1])
#define GET_BIT(dst, i) (((dst)->string.b[(i)>>3]) & (0x80 >> ((i)&7)))

/***********************************************************************************************************************
 * Declaration  : int32_t R_gcm_enc (uint8_t near *plain, uint8_t near *cipher, uint32_t data_len, uint8_t near *key,
 * uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len)
 * Function Name: R_gcm_enc
 * Description  : The R_gcm_enc() function encrypts the plaintext at a specified address (the 1st argument"plain") by
 * using the key (the 4th argument"key") and the initialize vector (the 7th argument"iv") and the additional
 * authentication data (the 9th argument"aad"). Encrypted data will output on the 2nd argument"cipher". Authentication
 * Tag data will output to the 5th argument"atag". Lengths to encrypt are specified 3rd argument"data_len".
 * Arguments    : plain Plain text area (data_len bytes).
 *                cipher Cipher text area (data_len bytes).
 *                data_len Plain text length (0 - any bytes).
 *                key Key area (16 byte).
 *                atag Authentication tag (atag_len bytes).
 *                atag_len Authentication tag length (1 - 16 bytes).
 *                iv Initialize vector area (iv_len bytes).
 *                iv_len Initialize vector length (1 - any bytes).
 *                aad Aad area (aad_len bytes).
 *                aad_len Aad length ((0 - any bytes).
 * Return Value : 0 Normal termination.
 *                -1 Abnormal termination (atag_len=0, iv_len=0).
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_gcm_enc
 **************************************************************************//**
 * @brief GCM Encryption Function.
 * @param[in] plain Plain text area (data_len bytes).
 * @param[out] cipher Cipher text area (data_len bytes).
 * @param[in] data_len Plain text length (0 - any bytes).
 * @param[in] key Key area (16 byte).
 * @param[out] atag Authentication tag (atag_len bytes).
 * @param[in] atag_len Authentication tag length (1 - 16 bytes).
 * @param[in] iv Initialize vector area (iv_len bytes).
 * @param[in] iv_len Initialize vector length (1 - any bytes).
 * @param[in] aad Aad area (aad_len bytes).
 * @param[in] aad_len Aad length (0 - any bytes).
 * @retval 0 Normal termination.
 * @retval -1 Abnormal termination (atag_len=0, iv_len=0).
 * @details The R_gcm_enc() function encrypts the plaintext at a specified
 * address (the 1st argument"plain") by using the key (the 4th argument"key")
 * and the initialize vector (the 7th argument"iv") and the additional
 * authentication data (the 9th argument"aad"). Encrypted data will output on
 * the 2nd argument "cipher". Authentication Tag data will output to the 5th
 * argument"atag". Lengths to encrypt are specified 3rd argument"data_len".
 * @note When input data, plain and aad are not aligned 16byte, the padding
 * process is executed in this function. The key size depends on block cipher
 * algorithm. When an invalid pointer (ex. Null pointer) or odd address is passed as a
 * parameter, the functions behavior is undefined. When data_len = 0, this
 * function does not use plain and cipher. This case, output authentication tag
 * is called as GMAC value. When aad_len = 0, this function does not use aad.
 * It is possible to allocate plain text area and cipher text area in same
 * address. (If these areas are not completely overlap, the function behavior is
 * not defined).
 */
int32_t R_gcm_enc (uint8_t near *plain, uint8_t near *cipher, uint32_t data_len, uint8_t near *key, uint8_t near *atag,
        uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len)
{
    BIT_STRING h_block;
    BIT_STRING j0;
    BIT_STRING icb;
    BIT_STRING s;
    BIT_STRING v;
    BIT_STRING u;
    BIT_STRING vu;
    BIT_STRING tmp1;
    BIT_STRING tmp2;

    volatile memset_t memset_func = &memset;

    if ((atag_len == 0) || (iv_len == 0))
    {
        return GCM_NG;
    }

    j0.len = 128;

    /* step1 : make H */
    memset(h_block.string.b, 0, BLOCK_SIZE);
    R_gcm_encrypt_plain_block((uint8_t near *) h_block.string.b, key);

    /* step2 : make a block, j0 */
    if ((iv_len * BYTE_SIZE) == 96)
    {
        memset(j0.string.b, 0, BLOCK_SIZE);
        memcpy(j0.string.b, iv, 96 / 8);
        j0.string.b[BLOCK_SIZE - 1] = 0x01;
    }
    else
    {
        memset( &tmp1, 0, sizeof(BIT_STRING));
        set_int(iv_len * BYTE_SIZE, (BIT_STRING near *) &tmp1, 32);
        ghash_arg2(iv, (uint8_t near *) tmp1.string.b, (BIT_STRING near *) &j0, iv_len, BLOCK_SIZE,
                (BIT_STRING near *) &h_block);
    }

    /* step3 : make C */
    inc((BIT_STRING near *) &j0, (BIT_STRING near *) &icb, 32);
    gctr((BIT_STRING near *) &icb, plain, cipher, key, data_len);

    /* step4 : set block length */
    memset( &v, 0, sizeof(BIT_STRING));
    memset( &u, 0, sizeof(BIT_STRING));
    set_int((aad_len * BYTE_SIZE), (BIT_STRING near *) &v, 32);
    set_int((data_len * BYTE_SIZE), (BIT_STRING near *) &u, 32);
    v.len = 64;
    u.len = 64;
    concat((BIT_STRING near *) &v, (BIT_STRING near *) &u, (BIT_STRING near *) &vu);

    /* step5 : make a block, S */
    ghash_arg3(aad, cipher, (uint8_t near *) vu.string.b, (BIT_STRING near *) &s, aad_len, data_len, BLOCK_SIZE,
            (BIT_STRING near *) &h_block);

    /* step6 : make a authentication TAG, T */
    gctr((BIT_STRING near *) &j0, (uint8_t near *) s.string.b, (uint8_t near *) tmp1.string.b, key, BLOCK_SIZE);
    tmp1.len = 128;
    memcpy( &tmp2, &tmp1, sizeof(BIT_STRING));
    msb((BIT_STRING near *) &tmp1, (BIT_STRING near *) &tmp2, (natural_int_t) (atag_len * BYTE_SIZE));
    memcpy(atag, (const void near *)(tmp2.string.b + (BLOCK_SIZE - atag_len)), (size_t )atag_len);

    /* step7 : return */
    memset_func( &h_block, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &j0, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &icb, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &s, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &v, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &u, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &vu, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &tmp1, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &tmp2, 0, sizeof(BIT_STRING)); /* clear temporary */

    return GCM_OK;
} /* End of function R_gcm_enc() */

/***********************************************************************************************************************
 * Declaration  : int32_t R_gcm_dec (uint8_t near *cipher, uint8_t near *plain, uint32_t data_len, uint8_t near *key,
 * uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len)
 * Function Name: R_gcm_dec
 * Description  : The R_gcm_dec() function decrypts and verifies the ciphertext at a specified address (the 1st argument
 * "cipher") by using the key (the 4th argument"key") and the authentication tag (the 5th argument"atag") and the
 * initialize vector (the 7th argument"iv") and the additional authentication data (the 9th argument"aad"). If result of
 * verification is OK, this function outputs plaintext to the 2nd argument "plain". If result of verification is NG,
 * this function outputs 0 to"plain". Lengths to decrypt are specified 3rd argument"data_len".
 * Arguments    : cipher Cipher text area (data_len bytes).
 *                plain Plain text area (data_len bytes).
 *                data_len Plain text length (0 - any bytes).
 *                key Key area (16 byte).
 *                atag Authentication tag (atag_len bytes).
 *                atag_len Authentication tag length (1 - 16 bytes).
 *                iv Initialize vector area (iv_len bytes).
 *                iv_len Initialize vector length (1 - any bytes).
 *                aad Aad area (aad_len bytes).
 *                aad_len Aad length ((0 - any bytes).
 * Return Value : 0 Successful authentication.
 *                -1 Failure authentication or illegal termination (atag_len=0, iv_len=0).
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_gcm_dec
 **************************************************************************//**
 * @brief GCM Decryption Function.
 * @param[in] cipher Cipher text area (data_len bytes).
 * @param[out] plain Plain text area (data_len bytes).
 * @param[in] data_len Plain text length (0 - any bytes).
 * @param[in] key Key area (16 byte).
 * @param[in] atag Authentication tag (atag_len bytes).
 * @param[in] atag_len Authentication tag length (1 - 16 bytes).
 * @param[in] iv Initialize vector area (iv_len bytes).
 * @param[in] iv_len Initialize vector length (1 - any bytes).
 * @param[in] aad Aad area (aad_len bytes).
 * @param[in] aad_len Aad length ((0 - any bytes).
 * @retval 0 Successful authentication.
 * @retval -1 Failure authentication or illegal termination (atag_len=0,
 * iv_len=0).
 * @details The R_gcm_dec() function decrypts and verifies the ciphertext at a
 * specified address (the 1st argument "cipher") by using the key (the 4th
 * argument"key") and the authentication tag (the 5th argument"atag") and the
 * initialize vector (the 7th argument"iv") and the additional authentication
 * data (the 9th argument"aad"). If result of verification is OK, this function
 * outputs plaintext to the 2nd argument "plain". If result of verification is
 * NG, this function outputs 0 to"plain". Lengths to decrypt are specified 3rd
 * argument"data_len".
 * @note When input data, plain and aad are not aligned 16byte, the padding
 * process is executed in this function. The key size depends on block cipher
 * algorithm. When an invalid pointer (ex. Null pointer) or odd address is passed as a
 * parameter, the functions behavior is undefined. When data_len = 0, this
 * function does not use plain and cipher. This case, input authentication tag
 * would be verified as GMAC value. When aad_len = 0, this function does not use
 * aad. It is possible to allocate plain text area and cipher text area in same
 * address. (If these areas are not completely overlap, the function behavior is
 * not defined).
 */
int32_t R_gcm_dec (uint8_t near *cipher, uint8_t near *plain, uint32_t data_len, uint8_t near *key, uint8_t near *atag,
        uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len)
{
    BIT_STRING h_block;
    BIT_STRING j0;
    BIT_STRING icb;
    BIT_STRING s;
    BIT_STRING v;
    BIT_STRING u;
    BIT_STRING vu;
    BIT_STRING tmp1;
    BIT_STRING tmp2;
    natural_int_t result;

    volatile memset_t memset_func = &memset;

    /* step1 : check error (this program do not check any arguments) */
    if ((atag_len == 0) || (iv_len == 0))
    {
        return GCM_NG;
    }

    j0.len = 128;

    /* step2 : make H */
    memset(h_block.string.b, 0, BLOCK_SIZE);
    R_gcm_encrypt_plain_block((uint8_t near *) h_block.string.b, key);

    /* step3 : make a block, j0 */
    if ((iv_len * BYTE_SIZE) == 96)
    {
        memset(j0.string.b, 0, BLOCK_SIZE);
        memcpy(j0.string.b, iv, 96 / 8);
        j0.string.b[BLOCK_SIZE - 1] = 0x01;
    }
    else
    {
        memset( &tmp1, 0, sizeof(BIT_STRING));
        set_int(iv_len * BYTE_SIZE, (BIT_STRING near *) &tmp1, 32);
        ghash_arg2(iv, (uint8_t near *) tmp1.string.b, (BIT_STRING near *) &j0, iv_len, BLOCK_SIZE,
                (BIT_STRING near *) &h_block);
    }

    /* Order is changed in order to overwrite "plain" at "cipher". */
    /* step5 -> step6 -> step 4 */

    /* step5 : set block length */
    memset( &v, 0, sizeof(BIT_STRING));
    memset( &u, 0, sizeof(BIT_STRING));
    set_int((aad_len * BYTE_SIZE), (BIT_STRING near *) &v, 32);
    set_int((data_len * BYTE_SIZE), (BIT_STRING near *) &u, 32);
    v.len = 64;
    u.len = 64;
    concat((BIT_STRING near *) &v, (BIT_STRING near *) &u, (BIT_STRING near *) &vu);

    /* step6 : make a block, S */
    ghash_arg3(aad, cipher, (uint8_t near *) vu.string.b, (BIT_STRING near *) &s, aad_len, data_len, BLOCK_SIZE,
            (BIT_STRING near *) &h_block);

    /* step4 : make P */
    inc((BIT_STRING near *) &j0, (BIT_STRING near *) &icb, 32);
    gctr((BIT_STRING near *) &icb, cipher, plain, key, data_len);

    /* step7 : make a authentication TAG, T */
    gctr((BIT_STRING near *) &j0, (uint8_t near *) s.string.b, (uint8_t near *) tmp1.string.b, key, BLOCK_SIZE);
    tmp1.len = 128;
    memcpy( &tmp2, &tmp1, sizeof(BIT_STRING));
    msb((BIT_STRING near *) &tmp1, (BIT_STRING near *) &tmp2, (natural_int_t) (atag_len * BYTE_SIZE));

    /* step8 : check authentication tag */
    if ( !memcmp((const void near *) (tmp2.string.b + (BLOCK_SIZE - atag_len)), (const void near *) atag,
            (size_t) atag_len))
    {
        result = GCM_OK;
    }
    else
    {
        result = GCM_NG;
        memset(plain, 0, (size_t )data_len);
    }
    memset_func( &h_block, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &j0, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &icb, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &s, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &v, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &u, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &vu, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &tmp1, 0, sizeof(BIT_STRING)); /* clear temporary */
    memset_func( &tmp2, 0, sizeof(BIT_STRING)); /* clear temporary */

    return result;
} /* End of function R_gcm_dec() */

/***********************************************************************************************************************
 * Declaration  : natural_int_t concat (BIT_STRING near *src_left, BIT_STRING near *src_right, BIT_STRING near *dst)
 * Function Name: concat
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t concat (BIT_STRING near *src_left, BIT_STRING near *src_right, BIT_STRING near *dst)
{
    natural_int_t index_src_left;
    natural_int_t index_src_right;
    natural_int_t len;
    natural_int_t len2;
    uint8_t near *s;
    uint8_t near *d;

    if ((src_left->len + src_right->len) > MAX_BIT)
    {
        return -1;
    }

    if ((src_left->len % 8) || (src_right->len % 8))
    {
        return -1;
    }

    memset(dst, 0, sizeof(BIT_STRING));

    dst->len = src_left->len + src_right->len;

    len = (natural_int_t) (src_right->len / 8);
    len2 = (natural_int_t) (src_left->len / 8);
    s = &(src_left->string.b[BLOCK_SIZE - len2]);
    d = &(dst->string.b[(BLOCK_SIZE - len) - len2]);
    for (index_src_left = len2; index_src_left; --index_src_left)
    {
        *d++ = *s++;
    }
    s = &(src_right->string.b[BLOCK_SIZE - len]);
    for (index_src_right = len; index_src_right; --index_src_right)
    {
        *d++ = *s++;
    }
    return 0;
} /* End of function concat() */

/***********************************************************************************************************************
 * Declaration  : natural_int_t msb (BIT_STRING near *src, BIT_STRING near *dst, natural_int_t num)
 * Function Name: msb
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t msb (BIT_STRING near *src, BIT_STRING near *dst, natural_int_t num)
{
    natural_int_t src_index;
    natural_int_t dst_index;

    if ((num % 8) || (num > MAX_BIT))
    {
        return -1;
    }

    if (src->len > MAX_BIT)
    {
        return -1;
    }

    memset(dst, 0, sizeof(BIT_STRING));

    dst->len = num;

    for (src_index = (natural_int_t) ((MAX_BIT - src->len) / 8), dst_index = ((MAX_BIT - num) / 8);
            dst_index < BLOCK_SIZE; src_index++, dst_index++)
    {
        dst->string.b[dst_index] = src->string.b[src_index];
    }

    return 0;
} /* End of function msb() */

/***********************************************************************************************************************
 * Declaration  : natural_int_t lsb (BIT_STRING near *src, BIT_STRING near *dst, natural_int_t num)
 * Function Name: lsb
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t lsb (BIT_STRING near *src, BIT_STRING near *dst, natural_int_t num)
{
    natural_int_t start;

    if ((num % 8) || (num > MAX_BIT))
    {
        return -1;
    }

    if (src->len > MAX_BIT)
    {
        return -1;
    }

    dst->len = num;
    start = (MAX_BIT - num) >> 3;

    memset( &(dst->string.b[0]), 0, start);

    memcpy( &(dst->string.b[start]), &(src->string.b[start]), BLOCK_SIZE - start);

    return 0;
} /* End of function lsb() */

/***********************************************************************************************************************
 * Declaration  : uint32_t get_int (BIT_STRING near *src)
 * Function Name: get_int
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static uint32_t get_int (BIT_STRING near *src)
{
    natural_int_t i;
    int32_t tmp = 0;

    if (src->len > (MAX_BIT / 2))
    {
        return 0xffffffff;
    }

    for (i = 0; i < 4; i++)
    {
        tmp += ((long) src->string.b[(BLOCK_SIZE - i) - 1] << (i * 8));
    }
    return tmp;
} /* End of function get_int() */

/***********************************************************************************************************************
 * Declaration  : natural_int_t set_int (uint32_t src, BIT_STRING near *dst, natural_int_t int_base)
 * Function Name: set_int
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t set_int (uint32_t src, BIT_STRING near *dst, natural_int_t int_base)
{
    memset(dst, 0, sizeof(BIT_STRING));

    if ((int_base != 8) && (int_base != 16) && (int_base != 24) && (int_base != 32))
    {
        return -1;
    }

    dst->len = int_base;

    if (int_base >= 32)
    {
        dst->string.b[(BLOCK_SIZE - 3) - 1] = (uint8_t) ((src & 0xff000000) >> 24);
    }
    if (int_base >= 24)
    {
        dst->string.b[(BLOCK_SIZE - 2) - 1] = (uint8_t) ((src & 0x00ff0000) >> 16);
    }
    if (int_base >= 16)
    {
        dst->string.b[(BLOCK_SIZE - 1) - 1] = (uint8_t) ((src & 0x0000ff00) >> 8);
    }
    if (int_base >= 8)
    {
        dst->string.b[(BLOCK_SIZE - 0) - 1] = (uint8_t) ((src & 0x000000ff) >> 0);
    }

    return 0;
} /* End of function set_int() */

/***********************************************************************************************************************
 * Declaration  : natural_int_t inc (BIT_STRING near *x_src, BIT_STRING near *x_dst, natural_int_t s)
 * Function Name: inc
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t inc (BIT_STRING near *x_src, BIT_STRING near *x_dst, natural_int_t s)
{
    BIT_STRING tmp1;
    BIT_STRING tmp2;
    uint32_t int_tmp;

    if ((s % 8) || (s > MAX_BIT))
    {
        return -1;
    }

    if (x_src->len > MAX_BIT)
    {
        return -1;
    }

    msb(x_src, (BIT_STRING near *) &tmp1, (natural_int_t) (x_src->len - s));
    lsb(x_src, (BIT_STRING near *) &tmp2, s);

    /* spec : incs(X)=MSBlen(X)-s(X) || [int(LSBs(X))+1 mod 2s]s */
    /* "s" is always specified the value = 32. And it is not necessary to take a mod. */
    int_tmp = get_int((BIT_STRING near *) &tmp2) + 1;
    set_int(int_tmp, (BIT_STRING near *) &tmp2, s);

    concat((BIT_STRING near *) &tmp1, (BIT_STRING near *) &tmp2, x_dst);

    return 0;
} /* End of function inc() */

/***********************************************************************************************************************
 * Declaration  : natural_int_t mul (BIT_STRING near *src, BIT_STRING near *dst)
 * Function Name: mul
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t mul (BIT_STRING near *src, BIT_STRING near *dst)
{
    BIT_STRING z;
    BIT_STRING v;
    natural_int_t i;

    memset( &z, 0, sizeof(BIT_STRING));
    memcpy( &v, src, sizeof(BIT_STRING));

#if defined(_USE_ASM_VER)
    {
        MUL_SIZE near *p;

        p = (MUL_SIZE near *)(&(dst->string.l[0]));
        for (i = MUL_TIMES; i; --i)
        {
            mul_body(*p++, (BIT_STRING near *)&v, (BIT_STRING near *)&z);
        }
    }
#else   /* for C version */
    for (i = 0; i < MAX_BIT; i++)
    {
        /* calculate Zi+1 */
        if (GET_BIT(dst, i))
        {
            xor( &v, &z);
        }
        /* calculate Vi+1 */
        if (GET_LSB(v) & 0x01)
        {
            right_shift_bit( &v);
            v.string.b[0] ^= 0xe1;
        }
        else
        {
            right_shift_bit( &v);
        }
    }
#endif /* defined _USE_ASM_VER */
    memcpy(dst, &z, sizeof(BIT_STRING));
    dst->len = 128;
    return 0;
} /* End of function mul() */

#if !defined(_USE_ASM_VER)
/***********************************************************************************************************************
 * Declaration  : natural_int_t xor (BIT_STRING near *src1, BIT_STRING near *src2)
 * Function Name: xor
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t xor (BIT_STRING near *src1, BIT_STRING near *src2)
{
    natural_uint_t near *src1_ptr;
    natural_uint_t near *src2_ptr;

    src1_ptr = (natural_uint_t near *) src1->string.w; /* object is holds the even alignment */
    src2_ptr = (natural_uint_t near *) src2->string.w; /* object is holds the even alignment */

    /* repeat xor at BLOCK_SIZE/sizeof(int) times.
     (not to use loop because of speed optimize) */
    if (sizeof(int) == 4)
    {
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
    }
    else if (sizeof(int) == 2)
    {
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;

        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
        *src2_ptr = ( *src1_ptr) ^ ( *src2_ptr);
        src1_ptr++;
        src2_ptr++;
    }
    else
    {
        /* not supported */
        return -1;
    }
    return 0;
} /* End of function xor() */
#endif /* !defined_USE_ASM_VER */

/***********************************************************************************************************************
 * Declaration  : natural_int_t xor_arg3 (BIT_STRING near *src1, BIT_STRING near *src2, BIT_STRING near *dst)
 * Function Name: xor_arg3
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t xor_arg3 (BIT_STRING near *src1, BIT_STRING near *src2, BIT_STRING near *dst)
{
    natural_uint_t near *src1_ptr;
    natural_uint_t near *src2_ptr;
    natural_uint_t near *dst_ptr;

    src1_ptr = (natural_uint_t near *)src1->string.w;
    src2_ptr = (natural_uint_t near *)src2->string.w;
    dst_ptr = (natural_uint_t near *)dst->string.w;

    /* repeat xor at BLOCK_SIZE/sizeof(int) times.
     (not to use loop because of speed optimize) */
    if (sizeof(int) == 4)
    {
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
    }
    else if (sizeof(int) == 2)
    {
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);

        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
        *dst_ptr++ = ( *src1_ptr++) ^ ( *src2_ptr++);
    }
    else
    {
        /* not supported */
        return -1;
    }
    return 0;
} /* End of function xor_arg3() */

#if !defined(_USE_ASM_VER)
/***********************************************************************************************************************
 * Declaration  : natural_int_t right_shift_bit (BIT_STRING near *src)
 * Function Name: right_shift_bit
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t right_shift_bit (BIT_STRING near *src)
{
    uint8_t byte;
    uint8_t tmp = 0;
    uint8_t near *p;

    tmp = 0;
    p = src->string.b;

    /* repeat shift at BLOCK_SIZE times.
     (not to use loop because of speed optimize) */
    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    byte = *p;
    *p++ = (byte >> 1) + tmp;
    tmp = byte << 7;

    return 0;
} /* End of function right_shift_bit() */
#endif /* !defined_USE_ASM_VER */

/***********************************************************************************************************************
 * Declaration  : natural_int_t ghash_arg2 (uint8_t near *src1, uint8_t near *src2, BIT_STRING near *dst, uint32_t len1,
 *                uint32_t len2, BIT_STRING near *h_block)
 * Function Name: ghash_arg2
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t ghash_arg2 (uint8_t near *src1, uint8_t near *src2, BIT_STRING near *dst, uint32_t len1,
        uint32_t len2, BIT_STRING near *h_block)
{
    memset(dst->string.b, 0, BLOCK_SIZE);
    dst->len = 128;
    ghash(src1, dst, h_block, len1);
    ghash(src2, dst, h_block, len2);

    return 0;
} /* End of function ghash_arg2() */

/***********************************************************************************************************************
 * Declaration  : natural_int_t ghash_arg3 (uint8_t near *src1, uint8_t near *src2, uint8_t near *src3,
 *                BIT_STRING near *dst, uint32_t len1, uint32_t len2, uint32_t len3, BIT_STRING near *h_block)
 * Function Name: ghash_arg3
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t ghash_arg3 (uint8_t near *src1, uint8_t near *src2, uint8_t near *src3, BIT_STRING near *dst,
        uint32_t len1, uint32_t len2, uint32_t len3, BIT_STRING near *h_block)
{
    memset(dst->string.b, 0, BLOCK_SIZE);
    dst->len = 128;
    ghash(src1, dst, h_block, len1);
    ghash(src2, dst, h_block, len2);
    ghash(src3, dst, h_block, len3);

    return 0;
} /* End of function ghash_arg3() */

/***********************************************************************************************************************
 * Declaration  : natural_int_t gctr (BIT_STRING near *icb, uint8_t near *plain, uint8_t near *cipher,
 *                uint8_t near *key, uint32_t len)
 * Function Name: gctr
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static natural_int_t gctr (BIT_STRING near *icb, uint8_t near *plain, uint8_t near *cipher, uint8_t near *key,
        uint32_t len)
{
    natural_int_t i;
    BIT_STRING cb;
    BIT_STRING x;
    BIT_STRING y;
    uint32_t block_num;
    size_t len_mod_block;

    block_num = len / BLOCK_SIZE;
    cb.len = 128;

    x.len = 128;
    for (i = 0; i < block_num; i++)
    {
        memcpy(cb.string.b, icb->string.b, BLOCK_SIZE);
        R_gcm_encrypt_plain_block((uint8_t near *) cb.string.b, key);
        memcpy(x.string.b, plain, BLOCK_SIZE);
        xor_arg3((BIT_STRING near *) &cb, (BIT_STRING near *) &x, (BIT_STRING near *) &y);
        memcpy(cipher, y.string.b, BLOCK_SIZE);

        inc(icb, icb, 32);
        plain += BLOCK_SIZE;
        cipher += BLOCK_SIZE;
    }
    /* padding */
    len_mod_block = (size_t) (len % BLOCK_SIZE);
    if (len_mod_block > 0)
    {
        memcpy(cb.string.b, icb->string.b, BLOCK_SIZE);
        R_gcm_encrypt_plain_block((uint8_t near *) cb.string.b, key);
        memcpy(x.string.b, plain, len_mod_block);
        xor_arg3((BIT_STRING near *) &cb, (BIT_STRING near *) &x, (BIT_STRING near *) &y);
        memcpy(cipher, y.string.b, len_mod_block);
    }

    return 0;
} /* End of function gctr() */

/***********************************************************************************************************************
 * Declaration  : int32_t R_gcm_enc_start (uint8_t near *plain, uint8_t near *cipher, uint32_t data_len,
 * uint8_t near *key, uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad,
 * uint32_t aad_len, uint32_t div_block_num, uint32_t near *work)
 * Function Name: R_gcm_enc_start
 * Description  : The R_gcm_enc_start() function encrypts the plaintext at a specified address (the 1st argument"plain")
 * by using the key (the 4th argument"key") and the initialize vector (the 7th argument"iv") and the additional
 * authentication data (the 9th argument"aad"). Encrypted data will output on the  2nd argument "cipher". Authentication
 * Tag data will output to the 5th argument"atag". Lengths to encrypt are  specified 3rd argument "data_len". This
 * function will recode each argument data to the 12th argument  "work". This function does not execute encryption. To
 * execute encryption, please call GCM Repeat Function repeatedly. GCM Repeat Function reads plaintext unit that
 * specified in 11th argument "div_block_num". The 1block size is 16 bytes.
 * Arguments    : plain Plain text area (data_len bytes).
 *                cipher Cipher text area (data_len bytes).
 *                data_len Plain text length (0 - any bytes).
 *                key Key area (16 byte).
 *                atag Authentication tag (atag_len bytes).
 *                atag_len Authentication tag length (1 - 16 bytes).
 *                iv Initialize vector area (iv_len bytes).
 *                iv_len Initialize vector length (1 - any bytes).
 *                aad Aad area (aad_len bytes).
 *                aad_len Aad length (0 - any bytes).
 *                div_block_num Divided block number (1 - any blocks).
 *                work Work area for  dividing process (requires 156 byte).
 * Return Value : positive value Normal termination. The times to call GCM Repeat Function for all block encryption
 * completion.
 *                -1 Abnormal termination ( atag_len=0, iv_len=0, div_block_num=0).
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_gcm_enc_start
 **************************************************************************//**
 * @brief GCM Encrypted Start Function.
 * @param[in] plain Plain text area (data_len bytes).
 * @param[out] cipher Cipher text area (data_len bytes).
 * @param[in] data_len Plain text length (0 - any bytes).
 * @param[in] key Key area (16 byte).
 * @param[out] atag Authentication tag (atag_len bytes).
 * @param[in] atag_len Authentication tag length (1 - 16 bytes).
 * @param[in] iv Initialize vector area (iv_len bytes).
 * @param[in] iv_len Initialize vector length (1 - any bytes).
 * @param[in] aad Aad area (aad_len bytes).
 * @param[in] aad_len Aad length (0 - any bytes).
 * @param[in] div_block_num Divided block number (1-any blocks).
 * @param[out] work Work area for  dividing process (requires 156 byte).
 * @retval pos itive value Normal termination. The times to call GCM Repeat
 * Function for all block encryption completion.
 * @retval -1 Abnormal termination ( atag_len=0, iv_len=0, div_block_num=0 )
 * @details The R_gcm_enc() function encrypts the plaintext at a specified
 * address (the 1st argument "plain" by using the key (the 4th argument "key")
 * and the initialize vector (the 7th argument "iv") and the additional
 * authentication data (the 9th argument "aad"). Encrypted data will output
 * on the 2nd argument "cipher". Authentication Tag data will output to the
 * 5th argument "atag". Lengths to encrypt are specified 3rd argument
 * "data_len". This function will recode each argument data to the 12th
 * argument "work". This function does not execute encryption. To execute
 * encryption, please call GCM Repea Function repeatedly.  GCM Repeat
 * Function reads plaintext unit that specified in 11th argument
 * "div_block_num". The 1block size is 16 bytes.
 * @note When input data, plain and aad are not aligned 16byte, the padding 
 * process is executed in this function. The key size depends on block cipher
 * algorithm. When an invalid pointer (ex. Null pointer) or odd address is passed
 * as a parameter, the functions behavior is undefined.When data_len = 0, this
 * function does not use plain and cipher. This case,output authentication tag
 * is called as GMAC value.When aad_len = 0, this function does not use aad.
 * It is possible to allocate plain text area and cipher text area in same
 * address.(If these areas are not completely overlap, the function behavior is
 * not defined.) The temporary data will store to work, please clear work area
 * after all data encryption.
 */
int32_t R_gcm_enc_start (uint8_t near *plain, uint8_t near *cipher, uint32_t data_len, uint8_t near *key,
        uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len,
        uint32_t div_block_num, uint32_t near *work)
{
    gcm_work_t near *work_pt;

    if ((atag_len == 0) || (iv_len == 0) || (div_block_num == 0))
    {
        return GCM_NG;
    }
    work_pt = (gcm_work_t near *) work;

    work_pt->step = GCM_STEP_ENC_1_2;
    work_pt->in = plain;
    work_pt->out = cipher;
    work_pt->data_len = data_len;
    work_pt->key = key;
    work_pt->atag = atag;
    work_pt->atag_len = atag_len;
    work_pt->iv = iv;
    work_pt->iv_len = iv_len;
    work_pt->aad = aad;
    work_pt->aad_len = aad_len;
    work_pt->div_len = (div_block_num * BLOCK_SIZE);

    if (work_pt->data_len == 0)
    {
        work_pt->ret_val = 5;
    }
    else
    {
        work_pt->ret_val = 3 + (((work_pt->data_len + (work_pt->div_len - 1)) / work_pt->div_len) * 2);
    }
    return work_pt->ret_val;
} /* End of function R_gcm_enc_start() */

/***********************************************************************************************************************
 * Declaration  : int32_t R_gcm_dec_start (uint8_t near *cipher, uint8_t near *plain, uint32_t data_len,
 * uint8_t near *key, uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad,
 * uint32_t aad_len, uint32_t div_block_num, uint32_t near *work)
 * Function Name: R_gcm_dec_start
 * Description  : The R_gcm_dec_start() function decrypts and verifies the ciphertext at a specified address (the 1st
 * argument "cipher") by using the key (the 4th argument"key") and the authentication tag (the 5th argument"atag")
 * initialize vector (the 7th argument"iv") and the additional authentication data (the 9th and the argument"aad"). If
 * argument"aad"). If result of verification is OK, this function outputs plaintext to the 2nd argument "plain". If
 * result of verification is NG, this function outputs 0 to"plain". Lengths to decrypt are  specified 3rd argument
 * "data_len". This function will recode each argument data to the 12th argument"work". This function does not execute
 * decryption. To execute decryption, please call GCM Repeat Function repeatedly. GCM Repeat Function reads ciphertext
 * unit that specified in 11th argument"div_block_num". The block size is 16 bytes.
 * Arguments    : cipher Cipher text area (data_len bytes).
 *                plain Plain text area (data_len bytes).
 *                data_len Plain text length (0 - any bytes).
 *                key Key area (16 byte).
 *                atag Authentication tag (atag_len bytes).
 *                atag_len Authentication tag length (1 - 16 bytes).
 *                iv Initialize vector area (iv_len bytes).
 *                iv_len Initialize vector length (1 - any bytes).
 *                aad Aad area (aad_len bytes).
 *                aad_len Aad length (0 - any bytes).
 *                div_block_num Divided block number (1 - any blocks).
 *                work Work area for  dividing process (requires 156 byte).
 * Return Value : positive value Normal termination. The times to call GCM Repeat Function for all block encryption
 * completion.
 *                -1 Abnormal termination (atag_len=0, iv_len=0, div_block_num=0).
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_gcm_dec_start 
 **************************************************************************//**
 * @brief GCM Decryption Start Function.
 * @param[in] cipher Cipher text area (data_len bytes).
 * @param[out] plain Plain text area (data_len bytes).
 * @param[in] data_len Plain text length (0 - any bytes).
 * @param[in] key Key area (16 byte).
 * @param[in] atag Authentication tag	 (atag_len bytes).
 * @param[in] atag_len Authentication tag length (1 - 16 bytes).
 * @param[in] iv Initialize vector area (iv_len bytes).
 * @param[in] iv_len Initialize vector length (1 - any bytes).
 * @param[in] aad Aad area (aad_len bytes).
 * @param[in] aad_len Aad length (0 - any bytes).
 * @param[in] div_block_num Divided block number (1-any blocks).
 * @param[out] work Work area for  dividing process (requires 156 byte).
 * @retval positive value Normal termination. The times to call GCM Repeat
 * Function for all block encryption completion.
 * @retval -1 Abnormal termination ( atag_len=0, iv_len=0, div_block_num=0 )
 * @details The R_gcm_dec() function decrypts and verifies the ciphertext at a
 * specified address (the 1st argument "cipher") by using the key (the 4th
 * argument "key") and the authentication tag (the 5th argument "atag") and
 * the initialize vector (the 7th argument "iv") and the additional
 * authentication data (the 9th argument "aad"). If result of verification is
 * OK, this function outputs plaintext to the 2nd argument "plain". If result
 * of verification is NG, this function outputs 0 to "plain". Lengths to
 * decrypt are specified 3rd argument "data_len".This function will recode each
 * argument data to the 12th argument "work". This function does not execute
 * decryption. To execute decryption, please call GCM Repeat Function
 * repeatedly. GCM Repeat Function reads ciphertext unit that specified
 * in 11th argument "div_block_num". The block size is 16 bytes.
 * @note When input data, plain and aad are not aligned 16byte, the padding
 * process is executed in this function.The key size depends on block cipher 
 * algorithm.When an invalid pointer (ex. Null pointer) or odd address is passed 
 * as a parameter, the functions behavior is undefined.When data_len = 0, this 
 * function does not use plain and cipher. This case, input authentication tag
 * would be verified as GMAC value. When aad_len = 0, this function does not
 * use aad.It is possible to allocate plain text area and cipher text area in
 * same address.(If these areas are not completely overlap, the function
 * behavior is not defined.) The temporary data will store to work, please clear
 * work area after all data encryption.
 */
 int32_t R_gcm_dec_start (uint8_t near *cipher, uint8_t near *plain, uint32_t data_len, uint8_t near *key,
        uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len,
        uint32_t div_block_num, uint32_t near *work)
{
    gcm_work_t near *work_pt;

    if ((atag_len == 0) || (iv_len == 0) || (div_block_num == 0))
    {
        return GCM_NG;
    }
    work_pt = (gcm_work_t near *) work;

    work_pt->step = GCM_STEP_DEC_1_2_3;
    work_pt->in = cipher;
    work_pt->out = plain;
    work_pt->data_len = data_len;
    work_pt->key = key;
    work_pt->atag = atag;
    work_pt->atag_len = atag_len;
    work_pt->iv = iv;
    work_pt->iv_len = iv_len;
    work_pt->aad = aad;
    work_pt->aad_len = aad_len;
    work_pt->div_len = (div_block_num * BLOCK_SIZE);

    if (work_pt->data_len == 0)
    {
        work_pt->ret_val = 5;
    }
    else
    {
        work_pt->ret_val = 3 + (((work_pt->data_len + (work_pt->div_len - 1)) / work_pt->div_len) * 2);
    }
    return work_pt->ret_val;
} /* End of function R_gcm_dec_start() */

/***********************************************************************************************************************
 * Declaration  : int32_t R_gcm_repeat (uint32_t near *work)
 * Function Name: R_gcm_repeat
 * Description  : The R_gcm_repeat() function is the function that restarts the pending GCM processing. This function
 * returns the value that means remaining times for encryption/decryption completion. Please call this function until
 * this function returns 0.
 * Arguments    : work Work area for dividing process (requires 156 byte).
 * Return Value : positive value Normal termination. The times to call GCM Repeat Function for all block encryption
 * completion.
 *                0 Successful authentication and all encryption/decryption.
 *                -1 Failure authentication or illegal termination. (No call GCM Start Encryption/Decryption Function)
 **********************************************************************************************************************/
/******************************************************************************
 * Function Name: R_gcm_repeat
 **************************************************************************//**
 * @brief GCM Repeat Function.
 * @param[in,out] work Work area for dividing process (requires 156 byte).
 * @retval positive value Normal termination. The times to call GCM Repeat
 * Function for all block encryption completion.
 * @retval 0 Successful authentication and all encryption/decryption.
 * @retval -1 Failure authentication or illegal termination. (No call GCM Start
 * Encryption/Decryption Function) 
 * @details R_gcm_repeat() function is the function that restarts the pending
 * GCM processing. This function returns the value that means remaining times
 * for encryption/decryption completion. Please call this function until this
 * function returns 0.
 * @note none
 */
 int32_t R_gcm_repeat (uint32_t near *work)
{
    gcm_work_t near *work_pt;

    volatile memset_t memset_func = &memset;

    work_pt = (gcm_work_t near *) work;

    work_pt->ret_val--;
    switch (work_pt->step)
    {
        case GCM_STEP_ENC_1_2:
        case GCM_STEP_DEC_1_2_3:
            /* step1 : make H *//* step2 : make H */
            memset(work_pt->h_block.string.b, 0, BLOCK_SIZE);
            work_pt->h_block.len = 128;
            R_gcm_encrypt_plain_block(work_pt->h_block.string.b, work_pt->key);
            /* step2 : make a block, j0 *//* step3 : make a block, j0 */
            work_pt->j0.len = 128;
            if ((work_pt->iv_len * BYTE_SIZE) == 96)
            {
                memset(work_pt->j0.string.b, 0, BLOCK_SIZE);
                memcpy(work_pt->j0.string.b, work_pt->iv, 96 / 8);
                work_pt->j0.string.b[BLOCK_SIZE - 1] = 0x01;
            }
            else
            {
                BIT_STRING tmp1;

                memset( &tmp1, 0, sizeof(BIT_STRING));
                set_int(work_pt->iv_len * BYTE_SIZE, (BIT_STRING near *) &tmp1, 32);
                ghash_arg2(work_pt->iv, (uint8_t near *) tmp1.string.b, &work_pt->j0, work_pt->iv_len, BLOCK_SIZE,
                        &work_pt->h_block);
                memset_func( &tmp1, 0, sizeof(BIT_STRING)); /* clear temporary */
            }
            GCM_NEXT_STEP(work_pt->step, GCM_STEP_ENC_1_2, GCM_STEP_ENC_3, GCM_STEP_DEC_5);
        break;
        case GCM_STEP_ENC_3:
            /* step3 : make C */
        case GCM_STEP_DEC_4:
            /* step4 : make P */
            GCM_NEXT_STEP(work_pt->step, GCM_STEP_ENC_3, GCM_STEP_ENC_3_LOOP, GCM_STEP_DEC_4_LOOP);
            work_pt->step_sub = 0;
            inc( &work_pt->j0, &work_pt->icb, 32);
            /* not break */
        case GCM_STEP_ENC_3_LOOP:
        case GCM_STEP_DEC_4_LOOP:
        {
            uint32_t last;
            uint32_t add;

            last = work_pt->data_len - work_pt->step_sub;
            add = work_pt->step_sub;
            if (last > work_pt->div_len)
            {
                gctr( &work_pt->icb, (work_pt->in + add), (work_pt->out + add), work_pt->key, work_pt->div_len);
                work_pt->step_sub += work_pt->div_len;
                /* continue this step */
            }
            else
            {
                if (last > 0)
                {
                    gctr( &work_pt->icb, (work_pt->in + add), (work_pt->out + add), work_pt->key, last);
                    work_pt->step_sub += last;
                }
                GCM_NEXT_STEP(work_pt->step, GCM_STEP_ENC_3_LOOP, GCM_STEP_ENC_4, GCM_STEP_DEC_7_8);
                /* exit this step */
            }
        }
        break;
        case GCM_STEP_ENC_4:
        case GCM_STEP_DEC_5:
            /* step4 : set block length */
        {
            BIT_STRING v;
            BIT_STRING u;

            memset( &v, 0, sizeof(BIT_STRING));
            memset( &u, 0, sizeof(BIT_STRING));
            set_int((work_pt->aad_len * BYTE_SIZE), (BIT_STRING near *) &v, 32);
            set_int((work_pt->data_len * BYTE_SIZE), (BIT_STRING near *) &u, 32);
            v.len = 64;
            u.len = 64;
            concat((BIT_STRING near *) &v, (BIT_STRING near *) &u, &work_pt->vu);
            memset_func( &v, 0, sizeof(BIT_STRING)); /* clear temporary */
            memset_func( &u, 0, sizeof(BIT_STRING)); /* clear temporary */
        }
        GCM_NEXT_STEP(work_pt->step, GCM_STEP_ENC_4, GCM_STEP_ENC_5, GCM_STEP_DEC_6);
        break;
        case GCM_STEP_ENC_5:
            /* step5 : make a block, S */
            work_pt->step = GCM_STEP_ENC_5_LOOP;
            work_pt->step_sub = 0;
            memset( &work_pt->s, 0, BLOCK_SIZE);
            work_pt->s.len = 128;
            ghash(work_pt->aad, &work_pt->s, &work_pt->h_block, work_pt->aad_len);
            /* not break */
        case GCM_STEP_ENC_5_LOOP:
        {
            uint32_t last;
            uint32_t add;

            last = work_pt->data_len - work_pt->step_sub;
            add = work_pt->step_sub;
            if (last > work_pt->div_len)
            {
                ghash((work_pt->out + add), &work_pt->s, &work_pt->h_block, work_pt->div_len);
                work_pt->step_sub += work_pt->div_len;
                /* continue this step */
            }
            else
            {
                if (last > 0)
                {
                    ghash((work_pt->out + add), &work_pt->s, &work_pt->h_block, last);
                    work_pt->step_sub += last;
                }
                ghash(work_pt->vu.string.b, &work_pt->s, &work_pt->h_block, BLOCK_SIZE);
                work_pt->step = GCM_STEP_ENC_6_7;
                /* exit this step */
            }
        }
        break;
        case GCM_STEP_DEC_6:
            /* step6 : make a block, S */
            work_pt->step = GCM_STEP_DEC_6_LOOP;
            work_pt->step_sub = 0;
            memset( &work_pt->s, 0, BLOCK_SIZE);
            work_pt->s.len = 128;
            ghash(work_pt->aad, &work_pt->s, &work_pt->h_block, work_pt->aad_len);
            /* not break */
        case GCM_STEP_DEC_6_LOOP:
        {
            uint32_t last;
            uint32_t add;

            last = work_pt->data_len - work_pt->step_sub;
            add = work_pt->step_sub;
            if (last > work_pt->div_len)
            {
                ghash((work_pt->in + add), &work_pt->s, &work_pt->h_block, work_pt->div_len);
                work_pt->step_sub += work_pt->div_len;
                /* continue this step */
            }
            else
            {
                if (last > 0)
                {
                    ghash((work_pt->in + add), &work_pt->s, &work_pt->h_block, last);
                    work_pt->step_sub += last;
                }
                ghash(work_pt->vu.string.b, &work_pt->s, &work_pt->h_block, BLOCK_SIZE);
                work_pt->step = GCM_STEP_DEC_4;
                /* exit this step */
            }
        }
        break;
        case GCM_STEP_ENC_6_7:
            /* step6 : make a authentication TAG, T */
            /* step7 : return */
        {
            BIT_STRING tmp1;
            BIT_STRING tmp2;

            gctr( &work_pt->j0, work_pt->s.string.b, (uint8_t near *) tmp1.string.b, work_pt->key, BLOCK_SIZE);
            tmp1.len = 128;
            memcpy( &tmp2, &tmp1, sizeof(BIT_STRING));
            msb((BIT_STRING near *) &tmp1, (BIT_STRING near *) &tmp2,
                    (natural_int_t) ((work_pt->atag_len) * BYTE_SIZE));
            memcpy(work_pt->atag, (const void near *)(tmp2.string.b + (BLOCK_SIZE - (work_pt->atag_len))),
                    (size_t )(work_pt->atag_len));
            memset_func( &tmp1, 0, sizeof(BIT_STRING)); /* clear temporary */
            memset_func( &tmp2, 0, sizeof(BIT_STRING)); /* clear temporary */
        }
        work_pt->step = GCM_STEP_COMPLETE;
        break;
        case GCM_STEP_DEC_7_8:
        {
            BIT_STRING tmp1;
            BIT_STRING tmp2;

            /* step7 : make a authentication TAG, T */
            gctr( &work_pt->j0, work_pt->s.string.b, (uint8_t near *) tmp1.string.b, work_pt->key, BLOCK_SIZE);
            tmp1.len = 128;
            memcpy( &tmp2, &tmp1, sizeof(BIT_STRING));
            msb((BIT_STRING near *) &tmp1, (BIT_STRING near *) &tmp2,
                    (natural_int_t) ((work_pt->atag_len) * BYTE_SIZE));
            memset_func( &tmp1, 0, sizeof(BIT_STRING)); /* clear temporary */

            /* step8 : check authentication tag */
            if (memcmp((const void near *) (tmp2.string.b + (BLOCK_SIZE - (work_pt->atag_len))),
                    (const void near *) (work_pt->atag), (size_t) (work_pt->atag_len)))
            {
                memset(work_pt->out, 0, (size_t )(work_pt->data_len));
                memset_func( &tmp2, 0, sizeof(BIT_STRING)); /* clear temporary */
                work_pt->ret_val = GCM_NG;
                break;
            }
            memset_func( &tmp2, 0, sizeof(BIT_STRING)); /* clear temporary */
        }
        work_pt->step = GCM_STEP_COMPLETE;
        break;
        default:
            work_pt->ret_val = GCM_NG;
        break;
    }

    if (work_pt->step == GCM_STEP_COMPLETE)
    {
        /* complete but ret_val is not 0, ret_va <- GCM_NG. */
        if (work_pt->ret_val != 0)
        {
            work_pt->ret_val = GCM_NG;
        }
    }
    else
    {
        /* not complete, but ret_val is 0, ret_val <- GCM_NG. */
        if (work_pt->ret_val == 0)
        {
            work_pt->ret_val = GCM_NG;
        }
    }

    return work_pt->ret_val;
} /* End of function R_gcm_repeat() */

/***********************************************************************************************************************
 * Declaration  : void ghash (uint8_t near *src, BIT_STRING near *dst, BIT_STRING near *h_block, uint32_t len)
 * Function Name: ghash
 * Description  :
 * Arguments    :
 * Return Value :
 **********************************************************************************************************************/
static void ghash (uint8_t near *src, BIT_STRING near *dst, BIT_STRING near *h_block, uint32_t len)
{
    natural_int_t i;
    BIT_STRING x;
    uint32_t block_num;
    size_t len_mod_block;

    block_num = len / BLOCK_SIZE;
    x.len = 128;
    for (i = 0; i < block_num; i++)
    {
        memcpy(x.string.b, src, BLOCK_SIZE);
        src += BLOCK_SIZE;
        xor((BIT_STRING near *) &x, dst);
        mul(h_block, dst);
    }
    /* padding */
    len_mod_block = (size_t) (len % BLOCK_SIZE);
    if (len_mod_block > 0)
    {
        memset(x.string.b, 0, BLOCK_SIZE);
        memcpy(x.string.b, src, len_mod_block);
        xor((BIT_STRING near *) &x, dst);
        mul(h_block, dst);
    }
} /* End of function ghash() */
