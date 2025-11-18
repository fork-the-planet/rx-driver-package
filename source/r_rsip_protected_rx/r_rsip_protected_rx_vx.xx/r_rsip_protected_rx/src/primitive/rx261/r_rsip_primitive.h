/*
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_rsip_primitive.h
* Description  : RSIP function primitive header file.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.10.2024 1.00     First Release.
*         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
*         :                     Revised key management specification
***********************************************************************************************************************/

#ifndef R_RSIP_PRIMITIVE_H
#define R_RSIP_PRIMITIVE_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>
#include "r_rsip_err.h"
#include "r_rsip_util.h"
#include "r_rsip_rx261_iodefine.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define RSIP_PRV_WORD_SIZE_S_INST2  (13U)
#define RSIP_PRV_WORD_SIZE_S_RAM    (1U)

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
extern uint32_t const DomainParam_NIST_P256[];
extern uint32_t const DomainParam_Brainpool_256r1[];
extern uint32_t const DomainParam_Koblitz_secp256k1[];
extern uint32_t const * S_INST2;
extern uint32_t const S_FLASH[];
extern uint32_t S_RAM[];
extern uint32_t INST_DATA_SIZE;
extern uint32_t KEY_INDEX_SIZE;
extern uint32_t WRAPPED_KEY_SIZE;

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
void r_rsip_func000 (const uint32_t InData_PaddedMsg[], uint32_t MAX_CNT);
void r_rsip_func001 (void);
void r_rsip_func002 (void);
void r_rsip_func008 (void);
void r_rsip_func030 (void);
void r_rsip_func040 (void);
void r_rsip_func043 (void);
void r_rsip_func044 (void);
void r_rsip_func048 (const uint32_t ARG1[]);
void r_rsip_func049 (const uint32_t ARG1[]);
void r_rsip_func056 (void);
void r_rsip_func057_r1 (const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3[], uint32_t INST_DATA_SIZE);
void r_rsip_func058 (const uint32_t ARG1[], uint32_t ARG2);
void r_rsip_func070 (const uint32_t ARG1[]);
void r_rsip_func071 (const uint32_t ARG1[]);
void r_rsip_func073 (const uint32_t ARG1[]);
void r_rsip_func074 (void);
void r_rsip_func075 (void);
void r_rsip_func081_r1 (void);
void r_rsip_func088_r1 (void);
void r_rsip_func100 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void r_rsip_func101 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void r_rsip_func102 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
void r_rsip_func103 (void);
void r_rsip_func205 (void);
void r_rsip_func206 (void);
void r_rsip_func407 (const uint32_t ARG1[]);
void r_rsip_func501 (const uint32_t ARG1[], const uint32_t ARG2[], uint32_t ARG3);
void r_rsip_func510 (const uint32_t ARG1[], const uint32_t ARG2[]);

/* Initialization */
void r_rsip_p00 (void);
rsip_ret_t r_rsip_p01 (void);
rsip_ret_t r_rsip_p02 (void);
rsip_ret_t r_rsip_p81 (void);
rsip_ret_t r_rsip_p82 (void);

/* OEM */
/* OEM Key Install*/
rsip_ret_t r_rsip_p6e (uint32_t InData_LC[], const uint32_t InData_Cmd[],
                        const uint32_t InData_SharedKeyIndex[], const uint32_t InData_SessionKey[],
                        const uint32_t InData_IV[], const uint32_t InData_InstData[],
                        uint32_t INST_DATA_SIZE, uint32_t OutData_KeyIndex[]);

/* OEM Key Validation*/
rsip_ret_t r_rsip_p70 (uint32_t InData_LC[], const uint32_t InData_Cmd[],
                        const uint32_t InData_KeyIndex[], uint32_t KEY_INDEX_SIZE);

/* OEM Key Update*/
rsip_ret_t r_rsip_p6f (uint32_t InData_LC[], const uint32_t InData_Cmd[],
                        const uint32_t InData_IV[], const uint32_t InData_InstData[],
                        uint32_t INST_DATA_SIZE, uint32_t OutData_KeyIndex[]);

/* HUK */
rsip_ret_t r_rsip_p2f (void);
rsip_ret_t r_rsip_p30 (uint32_t InData_LC[], uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p65 (const uint32_t InData_LC[]);
rsip_ret_t r_rsip_p40 (const uint32_t InData_LC[]);

/* Firmware Update*/
rsip_ret_t r_rsip_p22 (void);
rsip_ret_t r_rsip_p23i (const uint32_t InData_KeyIndex[], const uint32_t InData_SessionKey[],
                        const uint32_t InData_IV[]);
rsip_ret_t r_rsip_p23u (const uint32_t InData_UpProgram[], uint32_t MAX_CNT, uint32_t OutData_Program[]);
rsip_ret_t r_rsip_p23f (const uint32_t InData_UpProgram[], const uint32_t InData_UpMAC[], uint32_t MAX_CNT,
                        uint32_t OutData_Program[], uint32_t OutData_MAC[]);


/* Program Integrity Check */
rsip_ret_t r_rsip_p26i (void);
rsip_ret_t r_rsip_p26u (const uint32_t InData_Program[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p26f (const uint32_t InData_Program[], const uint32_t InData_MAC[], uint32_t MAX_CNT);

/* Key Generation */
rsip_ret_t r_rsip_p07 (uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p08 (uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_pf4 (const uint32_t InData_CurveType[], const uint32_t InData_DomainParam[],
                        uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[]);
rsip_ret_t r_rsip_p0a (uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_p0b (uint32_t OutData_KeyIndex[]);

/* Random Number Generation */
rsip_ret_t r_rsip_p20 (uint32_t OutData_Text[]);

/* SHA-224/256 Message Digest Generation */
rsip_ret_t r_rsip_p72 (const uint32_t InData_InitVal[], const uint32_t InData_PaddedMsg[],
                        const uint32_t MAX_CNT, uint32_t OutData_MsgDigest[]);

/* GHASH  Generation */
rsip_ret_t r_rsip_p21 (const uint32_t InData_HV[], const uint32_t InData_IV[],
                        const uint32_t InData_Text[], uint32_t OutData_DataT[],
                        uint32_t MAX_CNT);

/* Key  Wrap/Unwarp */
rsip_ret_t r_rsip_p8f (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[],
                            const uint32_t InData_WrappedKeyType[], const uint32_t InData_WrappedKeyIndex[],
                            uint32_t KEY_INDEX_SIZE, uint32_t OutData_Text[], uint32_t WRAPPED_KEY_SIZE);
rsip_ret_t r_rsip_p90 (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[],
                            const uint32_t InData_WrappedKeyType[], const uint32_t InData_Text[],
                            uint32_t KEY_INDEX_SIZE, uint32_t OutData_KeyIndex[], uint32_t WRAPPED_KEY_SIZE);

/* AES ECB/CBC/CTR*/
rsip_ret_t r_rsip_p47i (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[],
                        const uint32_t InData_IV[]);
void r_rsip_p47u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p47f (void);
rsip_ret_t r_rsip_p50i (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[],
                        const uint32_t InData_IV[]);
void r_rsip_p50u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p50f (void);

/* AES CCM*/
rsip_ret_t r_rsip_p95i (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[],
                        const uint32_t InData_Header[], uint32_t Header_Len);
void r_rsip_p95u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p95f (const uint32_t InData_Text[], const uint32_t InData_TextLen[],
                        uint32_t OutData_Text[], uint32_t OutData_MAC[]);
rsip_ret_t r_rsip_p98i (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[],
                        const uint32_t InData_Header[], uint32_t Header_Len);
void r_rsip_p98u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p98f (const uint32_t InData_Text[], const uint32_t InData_TextLen[],
                        const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_pa1i (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[],
                        const uint32_t InData_Header[], uint32_t Header_Len);
void r_rsip_pa1u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pa1f (const uint32_t InData_Text[], const uint32_t InData_TextLen[],
                        uint32_t OutData_Text[], uint32_t OutData_MAC[]);
rsip_ret_t r_rsip_pa4i (const uint32_t InData_KeyIndex[], const uint32_t InData_IV[],
                        const uint32_t InData_Header[], uint32_t Header_Len);
void r_rsip_pa4u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pa4f (const uint32_t InData_Text[], const uint32_t InData_TextLen[],
                        const uint32_t InData_MAC[], const uint32_t InData_MACLength[], uint32_t OutData_Text[]);

/* AES GCM*/
rsip_ret_t r_rsip_p29f (const uint32_t InData_Text[], const uint32_t InData_DataALen[],
                        const uint32_t InData_TextLen[], uint32_t OutData_Text[],
                        uint32_t OutData_DataT[]);
rsip_ret_t r_rsip_p29i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void r_rsip_p29a (const uint32_t InData_DataA[], uint32_t MAX_CNT);
void r_rsip_p29t (void);
void r_rsip_p29u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p32f (const uint32_t InData_Text[], const uint32_t InData_TextLen[],
                        const uint32_t InData_DataALen[], const uint32_t InData_DataT[],
                        const uint32_t InData_DataTLen[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p32i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void r_rsip_p32a (const uint32_t InData_DataA[], uint32_t MAX_CNT);
void r_rsip_p32t (void);
void r_rsip_p32u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p34f (const uint32_t InData_Text[], const uint32_t InData_DataALen[],
                        const uint32_t InData_TextLen[],uint32_t OutData_Text[],
                        uint32_t OutData_DataT[]);
rsip_ret_t r_rsip_p34i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void r_rsip_p34a (const uint32_t InData_DataA[], uint32_t MAX_CNT);
void r_rsip_p34t (void);
void r_rsip_p34u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p36f (const uint32_t InData_Text[], const uint32_t InData_TextLen[],
                        const uint32_t InData_DataALen[], const uint32_t InData_DataT[],
                        const uint32_t InData_DataTLen[], uint32_t OutData_Text[]);
rsip_ret_t r_rsip_p36i (const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[]);
void r_rsip_p36a (const uint32_t InData_DataA[], uint32_t MAX_CNT);
void r_rsip_p36t (void);
void r_rsip_p36u (const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT);

/* AES CMAC */
rsip_ret_t r_rsip_p41f (const uint32_t InData_Cmd[], const uint32_t InData_Text[],
                        const uint32_t InData_DataT[], const uint32_t InData_DataTLen[],
                        uint32_t OutData_DataT[]);
rsip_ret_t r_rsip_p41i (const uint32_t InData_KeyIndex[]);
void r_rsip_p41u (const uint32_t InData_Text[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p44f (const uint32_t InData_Cmd[], const uint32_t InData_Text[],
                        const uint32_t InData_DataT[], const uint32_t InData_DataTLen[],
                        uint32_t OutData_DataT[]);
rsip_ret_t r_rsip_p44i (const uint32_t InData_KeyIndex[]);
void r_rsip_p44u (const uint32_t InData_Text[], uint32_t MAX_CNT);

/* HMAC-SHA-224*/
rsip_ret_t r_rsip_pdci (const uint32_t InData_KeyIndex[]);
void r_rsip_pdcu (const uint32_t InData_Msg[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_pdcf (const uint32_t InData_Cmd[], const uint32_t InData_MAC[],
                        const uint32_t InData_length[], uint32_t OutData_MAC[]);
rsip_ret_t r_rsip_pdcs (uint32_t OutData_State[]);
rsip_ret_t r_rsip_pdcr (const uint32_t InData_KeyIndex[], const uint32_t InData_State[]);

/* HMAC-SHA-256*/
rsip_ret_t r_rsip_p76i (const uint32_t InData_KeyIndex[]);
void r_rsip_p76u (const uint32_t InData_Msg[], uint32_t MAX_CNT);
rsip_ret_t r_rsip_p76f (const uint32_t InData_Cmd[], const uint32_t InData_MAC[],
                        const uint32_t InData_length[], uint32_t OutData_MAC[]);
rsip_ret_t r_rsip_p76s (uint32_t OutData_State[]);
rsip_ret_t r_rsip_p76r (const uint32_t InData_KeyIndex[], const uint32_t InData_State[]);

/* ECDSA-256*/
rsip_ret_t r_rsip_pf0 (const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[],
                        const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[],
                        uint32_t OutData_Signature[]);
rsip_ret_t r_rsip_pf1 (const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[],
                        const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[],
                        const uint32_t InData_DomainParam[]);

/* PKI */
rsip_ret_t r_rsip_pe1 (const uint32_t InData_Sel_KeyType[], const uint32_t InData_Certificate[],
                        const uint32_t InData_CertificateLength[], const uint32_t InData_CertificatePubKey[],
                        const uint32_t InData_EncCertificateInfo[], uint32_t OutData_KeyIndex[]);
rsip_ret_t r_rsip_pe2 (const uint32_t InData_CurveType[], const uint32_t InData_PubKeyType[],
                        const uint32_t InData_PubKey[], const uint32_t InData_KeyIndex[],
                        const uint32_t InData_DomainParam[], uint32_t OutData_EncSecret[]);
rsip_ret_t r_rsip_peei (const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[],
                        const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[],
                        const uint32_t InData_DomainParam[]);
rsip_ret_t r_rsip_peef (uint32_t OutData_EncCertificateInfo[]);

/* KDF */
rsip_ret_t r_rsip_pe3 (const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[]);
rsip_ret_t r_rsip_pe7 (const uint32_t InData_KDFInfo[], const uint32_t InData_KDFInfo_Count[],
                        const uint32_t InData_OutDataType[], const uint32_t InData_OutDataLocation[],
                        uint32_t OutData_KeyIndex[], uint32_t OutData_EncIV[]);
rsip_ret_t r_rsip_pef(const uint32_t InData_Msg1[], const uint32_t InData_Msg1Length[], const uint32_t InData_EncMsg[],
                        const uint32_t InData_EncMsgLength[], const uint32_t InData_Msg2[],
                        const uint32_t InData_Msg2Length[], uint32_t OutData_KDFInfo[]);

#endif                                 /* R_RSIP_PRIMITIVE_H */
