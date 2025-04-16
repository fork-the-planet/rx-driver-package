/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         r_aes_development.h
 * @brief        AES Library header file.
 **********************************************************************************************************************/

#define FUNC_BIT_KEY(crypt,n)   R_##crypt##_##n##_Keysch
#define AES_KEY(n)  FUNC_BIT_KEY(Aes,n)

#define FUNC_BIT_ENC(crypt,n,mode)  R_##crypt##_##n##_##mode##enc
#define AES_ECBENC(n)   FUNC_BIT_ENC(Aes,n,Ecb)
#define AES_CBCENC(n)   FUNC_BIT_ENC(Aes,n,Cbc)
#define AES_OTFECBENC(n)    FUNC_BIT_ENC(Aes,n,OtfEcb)
#define AES_OTFCBCENC(n)    FUNC_BIT_ENC(Aes,n,OtfCbc)

#define FUNC_BIT_DEC(crypt,n,mode)  R_##crypt##_##n##_##mode##dec
#define AES_ECBDEC(n)   FUNC_BIT_DEC(Aes,n,Ecb)
#define AES_CBCDEC(n)   FUNC_BIT_DEC(Aes,n,Cbc)
#define AES_OTFECBDEC(n)    FUNC_BIT_DEC(Aes,n,OtfEcb)
#define AES_OTFCBCDEC(n)    FUNC_BIT_DEC(Aes,n,OtfCbc)
/*
 Define as follows and specify the length of key at compile time;

 void AES_KEY(KEY_LENGTH)(uint8_t *key,uint32_t *ekey)
 void AES_ECBENC(KEY_LENGTH)(uint8_t *pdat, uint8_t *cdat, uint32_t *ekey)
 void AES_CBCENC(KEY_LENGTH)(uint8_t *pdat, uint8_t *cdat, uint8_t *ivec, uint32_t *ekey)
 void AES_ECBDEC(KEY_LENGTH)(uint8_t *cdat, uint8_t *pdat, uint32_t *ekey)
 void AES_CBCDEC(KEY_LENGTH)(uint8_t *cdat, uint8_t *pdat, uint8_t *ivec, uint32_t *ekey)
 */

