/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         r_aes_rx_if.h
 * @brief        AES Library header file.
 **********************************************************************************************************************/

#ifndef R_AES_RX_IF_H
    #define R_AES_RX_IF_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_stdint.h"


extern void R_Aes_128_Keysch (uint8_t near *key, uint32_t near *ekey);

extern void R_Aes_128_Cbcenc (uint8_t near *pdat , uint8_t near *cdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);
	
extern void R_Aes_128_Cbcdec (uint8_t near *cdat , uint8_t near *pdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);

extern void R_Aes_128_Ecbenc (uint8_t near *pdat, uint8_t near *cdat, uint32_t near *ekey, uint16_t block);

extern void R_Aes_128_Ecbdec (uint8_t near *cdat, uint8_t near *pdat, uint32_t near *ekey, uint16_t block);

extern void R_Aes_256_Keysch (uint8_t near *key, uint32_t near *ekey);

extern void R_Aes_256_Cbcenc (uint8_t near *pdat , uint8_t near *cdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);
	
extern void R_Aes_256_Cbcdec (uint8_t near *cdat, uint8_t near *pdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);

extern void R_Aes_256_Ecbenc (uint8_t near *pdat, uint8_t near *cdat, uint32_t near *ekey, uint16_t block);

extern void R_Aes_256_Ecbdec (uint8_t near *cdat, uint8_t near *pdat, uint32_t near *ekey, uint16_t block);

extern int32_t R_gcm_enc (uint8_t near *plain, uint8_t near *cipher, uint32_t data_len, uint8_t near *key, uint8_t near *atag,
        uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len);

extern int32_t R_gcm_dec (uint8_t near *cipher, uint8_t near *plain, uint32_t data_len, uint8_t near *key, uint8_t near *atag,
        uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len);

extern int32_t R_gcm_enc_start (uint8_t near *plain, uint8_t near *cipher, uint32_t data_len, uint8_t near *key,
        uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len,
        uint32_t div_block_num, uint32_t near *work);

extern int32_t R_gcm_dec_start (uint8_t near *cipher, uint8_t near *plain, uint32_t data_len, uint8_t near *key,
        uint8_t near *atag, uint32_t atag_len, uint8_t near *iv, uint32_t iv_len, uint8_t near *aad, uint32_t aad_len,
        uint32_t div_block_num, uint32_t near *work);

extern void R_clear_keyLength (void);

extern int32_t R_gcm_repeat (uint32_t near *work);

extern uint32_t R_set_keyLength (uint32_t n);	
#endif /* R_AES_RX_IF_H */
