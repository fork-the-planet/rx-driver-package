/*
 * Copyright (c) 2015 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 27.06.2015 1.00     First Release
 *         : 15.05.2017 1.01     Add AES-CMAC
 *         : 30.09.2017 1.03     Add Init/Update/Final API and SHA, RSA
 *         : 28.02.2018 1.04     Change Init/Update/Final API for RX231, add TLS function and 
 *         :                     return values change FIT rules.
 *         : 30.04.2018 1.05     Add TDES, MD5 and RSAES-PKCS1-v1_5 API
 *         : 28.09.2018 1.06     Add RSA Key Generation, AES, TDES, RSA Key update features, RX66T support
 *         : 28.12.2018 1.07     Add RX72T support
 *         : 30.09.2019 1.08     Added support for GCC and IAR compiler, ECC API, RX23W and RX72M
 *         : 31.03.2020 1.09     Added support for AES-CCM, HMAC key generation, ECDH, Key Wrap API, RX66N and RX72N
 *         : 30.06.2020 1.10     Added support for ARC4, ECC(P-384) API
 *         : 30.09.2020 1.11     Added support for DH, ECDHE P-512r1 API, and generalization of KDF.
 *         :                     Added support for Key wrap API with TSIP-Lite.
 *         : 30.06.2021 1.12     Added support for RX23W chip version D
 *         : 31.08.2021 1.13     Added support for RX671
 *         : 22.10.2021 1.14     Added support for TLS1.3
 *         : 31.03.2022 1.15     Added support for TLS1.3(RX72M_RX72N_RX66N)
 *         : 15.09.2022 1.16     Added support for RSA 3k/4k and updated support for TLS1.3
 *         : 20.01.2023 1.17     Added support for TLS1.3 server
 *         : 24.05.2023 1.18     Added support for RX26T
 *         : 30.11.2023 1.19     Update example of Secure Bootloader / Firmware Update
 *         : 28.02.2024 1.20     Applied software workaround of AES-CCM decryption
 *         : 28.06.2024 1.21     Added support for TLS1.2 server
 *         : 10.04.2025 1.22     Added support for RSAES-OAEP, SSH
 *         :                     Updated Firmware Update API
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "../r_tsip_rx_private.h"

#if TSIP_TLS == 1
/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Imported global variables and functions (from other files)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private global variables and functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: R_TSIP_TlsEncryptPreMasterSecretSub
*******************************************************************************************************************/ /**
* @details       RX72M RSA2048 Encryption with Public Key
* @param[in]     InData_PubKey
* @param[in]     InData_PreMasterSecret
* @param[out]    OutData_PreMasterSecret
* @retval        TSIP_SUCCESS
* @retval        TSIP_ERR_FAIL
* @retval        TSIP_ERR_RESOURCE_CONFLICT
* @note          None
*/
e_tsip_err_t R_TSIP_TlsEncryptPreMasterSecretSub(uint32_t *InData_PubKey, uint32_t *InData_PreMasterSecret, uint32_t *OutData_PreMasterSecret)
{
    int32_t iLoop = 0u, jLoop = 0u, kLoop = 0u, oLoop1 = 0u, oLoop2 = 0u, iLoop2 = 0u;
    uint32_t KEY_ADR = 0u, OFS_ADR = 0u;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)iLoop2;
    (void)oLoop1;
    (void)oLoop2;
    (void)KEY_ADR;
    (void)OFS_ADR;
    #if TSIP_MULTI_THREADING == 1
    TSIP_MULTI_THREADING_LOCK_FUNCTION();
    #endif /* TSIP_MULTI_THREADING == 1 */
    if (0x0u != (TSIP.REG_1BCH.WORD & 0x1fu))
    {
        #if TSIP_MULTI_THREADING == 1
        TSIP_MULTI_THREADING_UNLOCK_FUNCTION();
        #endif /* TSIP_MULTI_THREADING == 1 */
        return TSIP_ERR_RESOURCE_CONFLICT;
    }
    TSIP.REG_84H.WORD = 0x0000e201u;
    TSIP.REG_108H.WORD = 0x00000000u;
    TSIP.REG_C4H.WORD = 0x200e1a0du;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_RAM[16+0 + 0];
    TSIP.REG_100H.WORD = S_RAM[16+0 + 1];
    TSIP.REG_100H.WORD = S_RAM[16+0 + 2];
    TSIP.REG_100H.WORD = S_RAM[16+0 + 3];
    TSIP.REG_104H.WORD = 0x00000368u;
    TSIP.REG_E0H.WORD = 0x80040000u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = InData_PubKey[0];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = InData_PubKey[1];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = InData_PubKey[2];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = InData_PubKey[3];
    TSIP.REG_ECH.WORD = 0x00000bdeu;
    TSIP.REG_ECH.WORD = 0x000037e0u;
    TSIP.REG_ECH.WORD = 0x00008fe0u;
    TSIP.REG_ECH.WORD = 0xff000000u;
    TSIP.REG_ECH.WORD = 0x38008be0u;
    TSIP.REG_ECH.WORD = 0x05000000u;
    TSIP.REG_ECH.WORD = 0x1000d3c0u;
    TSIP.REG_ECH.WORD = 0x3800d817u;
    TSIP.REG_ECH.WORD = 0x2000d3c1u;
    TSIP.REG_ECH.WORD = 0x000037e0u;
    TSIP.REG_ECH.WORD = 0x00008fe0u;
    TSIP.REG_ECH.WORD = 0x0000ff00u;
    TSIP.REG_ECH.WORD = 0x38008be0u;
    TSIP.REG_ECH.WORD = 0x00000100u;
    TSIP.REG_ECH.WORD = 0x1000d3c2u;
    TSIP.REG_ECH.WORD = 0x38008bc0u;
    TSIP.REG_ECH.WORD = 0x00000007u;
    TSIP.REG_E0H.WORD = 0x00000080u;
    TSIP.REG_1CH.WORD = 0x00A60000u;
    RX72M_RX72N_RX66N_func100(change_endian_long(0xd20093feu), change_endian_long(0x3b5f119au), change_endian_long(0x6f2e7584u), change_endian_long(0x4c2737b5u));
    TSIP.REG_1CH.WORD = 0x00400000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    if (1u == (TSIP.REG_1CH.BIT.B22))
    {
        RX72M_RX72N_RX66N_func102(change_endian_long(0x6c3b1fe3u), change_endian_long(0x99958a93u), change_endian_long(0x4f20047cu), change_endian_long(0xbe764594u));
        TSIP.REG_1BCH.WORD = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_18H.BIT.B12)
        {
            /* waiting */
        }
        #if TSIP_MULTI_THREADING == 1
        TSIP_MULTI_THREADING_UNLOCK_FUNCTION();
        #endif /* TSIP_MULTI_THREADING == 1 */
        return TSIP_ERR_FAIL;
    }
    else
    {
        TSIP.REG_104H.WORD = 0x00000362u;
        TSIP.REG_C4H.WORD = 0x00082b8du;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_PreMasterSecret[0];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[1];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[2];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[3];
        TSIP.REG_C4H.WORD = 0x400c0b0cu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = change_endian_long(0x0954569cu);
        TSIP.REG_104H.WORD = 0x00000b62u;
        TSIP.REG_D0H.WORD = 0x00000200u;
        TSIP.REG_C4H.WORD = 0x02f087bfu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_PreMasterSecret[4];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[5];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[6];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[7];
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_PreMasterSecret[8];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[9];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[10];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[11];
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_PreMasterSecret[12];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[13];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[14];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[15];
        TSIP.REG_ECH.WORD = 0x0000b480u;
        TSIP.REG_ECH.WORD = 0x00000070u;
        TSIP.REG_E0H.WORD = 0x808c0004u;
        TSIP.REG_00H.WORD = 0x00008233u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_104H.WORD = 0x00000362u;
        TSIP.REG_C4H.WORD = 0x000007bdu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_PreMasterSecret[16];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[17];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[18];
        TSIP.REG_100H.WORD = InData_PreMasterSecret[19];
        TSIP.REG_C4H.WORD = 0x00900c45u;
        TSIP.REG_00H.WORD = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        RX72M_RX72N_RX66N_func100(change_endian_long(0xc1ac81bcu), change_endian_long(0xdca6b482u), change_endian_long(0xe31230acu), change_endian_long(0xa34fd1fau));
        TSIP.REG_1CH.WORD = 0x00400000u;
        TSIP.REG_1D0H.WORD = 0x00000000u;
        if (1u == (TSIP.REG_1CH.BIT.B22))
        {
            RX72M_RX72N_RX66N_func102(change_endian_long(0x3b0a5023u), change_endian_long(0x26720df0u), change_endian_long(0xf8e82dc6u), change_endian_long(0x74cc62e0u));
            TSIP.REG_1BCH.WORD = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_18H.BIT.B12)
            {
                /* waiting */
            }
            #if TSIP_MULTI_THREADING == 1
            TSIP_MULTI_THREADING_UNLOCK_FUNCTION();
            #endif /* TSIP_MULTI_THREADING == 1 */
            return TSIP_ERR_FAIL;
        }
        else
        {
            TSIP.REG_C4H.WORD = 0x00082b8du;
            TSIP.REG_E0H.WORD = 0x81040000u;
            TSIP.REG_00H.WORD = 0x00002813u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_28H.WORD = 0x00bf0001u;
            RX72M_RX72N_RX66N_func100(change_endian_long(0xd4c43249u), change_endian_long(0x9027e4cbu), change_endian_long(0x09750b51u), change_endian_long(0x7be73e98u));
            RX72M_RX72N_RX66N_func103();
            TSIP.REG_104H.WORD = 0x00000052u;
            TSIP.REG_C4H.WORD = 0x01000c84u;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_104H.BIT.B31)
            {
                /* waiting */
            }
            TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
            TSIP.REG_E0H.WORD = 0x80010000u;
            TSIP.REG_00H.WORD = 0x00008207u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_00H.WORD = 0x0000020fu;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_ECH.WORD = 0x00008c00u;
            TSIP.REG_ECH.WORD = 0x0000ffffu;
            TSIP.REG_ECH.WORD = 0x00009000u;
            TSIP.REG_ECH.WORD = 0x00028080u;
            TSIP.REG_E0H.WORD = 0x81010000u;
            TSIP.REG_00H.WORD = 0x00003807u;
            TSIP.REG_2CH.WORD = 0x00000010u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_ECH.WORD = 0x0000b480u;
            TSIP.REG_ECH.WORD = 0x01020408u;
            TSIP.REG_ECH.WORD = 0x0000b4a0u;
            TSIP.REG_ECH.WORD = 0x10204080u;
            TSIP.REG_ECH.WORD = 0x0000b4c0u;
            TSIP.REG_ECH.WORD = 0x80200802u;
            TSIP.REG_ECH.WORD = 0x0000b4e0u;
            TSIP.REG_ECH.WORD = 0x40100401u;
            TSIP.REG_ECH.WORD = 0x00000bdeu;
            for (iLoop = 0; iLoop < 12; iLoop = iLoop + 1)
            {
                RX72M_RX72N_RX66N_func100(change_endian_long(0x1bc71572u), change_endian_long(0x9ec01372u), change_endian_long(0x343bf1a1u), change_endian_long(0x0981fce2u));
                RX72M_RX72N_RX66N_func103();
                TSIP.REG_104H.WORD = 0x00000052u;
                TSIP.REG_C4H.WORD = 0x01000c84u;
                /* WAIT_LOOP */
                while (1u != TSIP.REG_104H.BIT.B31)
                {
                    /* waiting */
                }
                TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
                TSIP.REG_E0H.WORD = 0x80040000u;
                TSIP.REG_00H.WORD = 0x00008213u;
                /* WAIT_LOOP */
                while (0u != TSIP.REG_00H.BIT.B25)
                {
                    /* waiting */
                }
                TSIP.REG_1CH.WORD = 0x00001800u;
                TSIP.REG_ECH.WORD = 0x00001004u;
                TSIP.REG_ECH.WORD = 0x00001025u;
                TSIP.REG_ECH.WORD = 0x00001046u;
                TSIP.REG_ECH.WORD = 0x00001067u;
                TSIP.REG_E0H.WORD = 0x81040000u;
                TSIP.REG_00H.WORD = 0x00003813u;
                /* WAIT_LOOP */
                while (0u != TSIP.REG_00H.BIT.B25)
                {
                    /* waiting */
                }
                TSIP.REG_1CH.WORD = 0x00001800u;
                TSIP.REG_ECH.WORD = 0x00002fc0u;
                RX72M_RX72N_RX66N_func101(change_endian_long(0x1e0c212cu), change_endian_long(0xde10b1b9u), change_endian_long(0x34664436u), change_endian_long(0xf49389b9u));
            }
            TSIP.REG_ECH.WORD = 0x0000b7e0u;
            TSIP.REG_ECH.WORD = 0x0000000Cu;
            TSIP.REG_ECH.WORD = 0x38000bdfu;
            TSIP.REG_E0H.WORD = 0x00000080u;
            TSIP.REG_1CH.WORD = 0x00A60000u;
            TSIP.REG_1CH.WORD = 0x00402000u;
            RX72M_RX72N_RX66N_func100(change_endian_long(0xbeafbf7cu), change_endian_long(0x8adae56bu), change_endian_long(0xf877babeu), change_endian_long(0xd3394e82u));
            RX72M_RX72N_RX66N_func103();
            TSIP.REG_104H.WORD = 0x00000052u;
            TSIP.REG_C4H.WORD = 0x01000c84u;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_104H.BIT.B31)
            {
                /* waiting */
            }
            TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
            TSIP.REG_E0H.WORD = 0x80030000u;
            TSIP.REG_00H.WORD = 0x0000820fu;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_00H.WORD = 0x00000207u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_ECH.WORD = 0x00001004u;
            TSIP.REG_ECH.WORD = 0x00001025u;
            TSIP.REG_ECH.WORD = 0x00001046u;
            TSIP.REG_E0H.WORD = 0x80010140u;
            TSIP.REG_104H.WORD = 0x00000058u;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_104H.BIT.B31)
            {
                /* waiting */
            }
            TSIP.REG_100H.WORD = change_endian_long(0xffffff00u);
            TSIP.REG_ECH.WORD = 0x00000c4au;
            TSIP.REG_E0H.WORD = 0x81030000u;
            TSIP.REG_00H.WORD = 0x0000380fu;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_ECH.WORD = 0x0000b420u;
            TSIP.REG_ECH.WORD = 0x00000070u;
            TSIP.REG_E0H.WORD = 0x818c0001u;
            TSIP.REG_00H.WORD = 0x00003833u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_104H.WORD = 0x00008362u;
            TSIP.REG_D0H.WORD = 0x00001f00u;
            TSIP.REG_C4H.WORD = 0x42f087bfu;
            TSIP.REG_00H.WORD = 0x00013203u;
            TSIP.REG_2CH.WORD = 0x00000014u;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1u != TSIP.REG_104H.BIT.B31)
                {
                    /* waiting */
                }
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+4 + 0];
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+4 + 1];
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+4 + 2];
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+4 + 3];
            }
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_00H.WORD = 0x00013203u;
            TSIP.REG_2CH.WORD = 0x00000012u;
            for (iLoop = 0; iLoop < 64; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1u != TSIP.REG_104H.BIT.B31)
                {
                    /* waiting */
                }
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+68 + 0];
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+68 + 1];
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+68 + 2];
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+68 + 3];
            }
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_C4H.WORD = 0x40f007bdu;
            for (iLoop = 0; iLoop < 4; iLoop = iLoop + 4)
            {
                /* WAIT_LOOP */
                while (1u != TSIP.REG_104H.BIT.B31)
                {
                    /* waiting */
                }
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+132 + 0];
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+132 + 1];
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+132 + 2];
                TSIP.REG_100H.WORD = InData_PubKey[iLoop+132 + 3];
            }
            TSIP.REG_E0H.WORD = 0x800100a0u;
            TSIP.REG_00H.WORD = 0x00008207u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_00H.WORD = 0x0000020fu;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_104H.WORD = 0x00000362u;
            TSIP.REG_C4H.WORD = 0x400007bdu;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_104H.BIT.B31)
            {
                /* waiting */
            }
            TSIP.REG_100H.WORD = InData_PubKey[136];
            TSIP.REG_100H.WORD = InData_PubKey[137];
            TSIP.REG_100H.WORD = InData_PubKey[138];
            TSIP.REG_100H.WORD = InData_PubKey[139];
            TSIP.REG_C4H.WORD = 0x00900c45u;
            TSIP.REG_00H.WORD = 0x00002213u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            RX72M_RX72N_RX66N_func100(change_endian_long(0x594a195du), change_endian_long(0xfd980dc6u), change_endian_long(0xd4cb9a26u), change_endian_long(0xff32bc3fu));
            TSIP.REG_1CH.WORD = 0x00400000u;
            TSIP.REG_1D0H.WORD = 0x00000000u;
            if (1u == (TSIP.REG_1CH.BIT.B22))
            {
                RX72M_RX72N_RX66N_func102(change_endian_long(0x04bf49c5u), change_endian_long(0xac896157u), change_endian_long(0xbbaf1c58u), change_endian_long(0x85522b8bu));
                TSIP.REG_1BCH.WORD = 0x00000040u;
                /* WAIT_LOOP */
                while (0u != TSIP.REG_18H.BIT.B12)
                {
                    /* waiting */
                }
                #if TSIP_MULTI_THREADING == 1
                TSIP_MULTI_THREADING_UNLOCK_FUNCTION();
                #endif /* TSIP_MULTI_THREADING == 1 */
                return TSIP_ERR_FAIL;
            }
            else
            {
                RX72M_RX72N_RX66N_func100(change_endian_long(0x6b4c15fbu), change_endian_long(0x51c4cc72u), change_endian_long(0x1b11c5bcu), change_endian_long(0x7faae0eau));
                TSIP.REG_18H.WORD = 0x00000004u;
                TSIP.REG_34H.WORD = 0x00000000u;
                TSIP.REG_38H.WORD = 0x00000338u;
                TSIP.REG_E0H.WORD = 0x810100a0u;
                TSIP.REG_00H.WORD = 0x00003807u;
                /* WAIT_LOOP */
                while (0u != TSIP.REG_00H.BIT.B25)
                {
                    /* waiting */
                }
                TSIP.REG_1CH.WORD = 0x00001800u;
                /* WAIT_LOOP */
                while (0u != TSIP.REG_18H.BIT.B10)
                {
                    /* waiting */
                }
                TSIP.REG_18H.WORD = 0x00000000u;
                TSIP.REG_28H.WORD = 0x00bf0001u;
                RX72M_RX72N_RX66N_func100(change_endian_long(0x8fbab374u), change_endian_long(0x85e830e6u), change_endian_long(0xe717e503u), change_endian_long(0x113103a5u));
                TSIP.REG_2CH.WORD = 0x00000020u;
                TSIP.REG_04H.WORD = 0x00000302u;
                /* WAIT_LOOP */
                while (1u != TSIP.REG_04H.BIT.B30)
                {
                    /* waiting */
                }
                OutData_PreMasterSecret[0] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[1] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[2] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[3] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[4] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[5] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[6] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[7] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[8] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[9] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[10] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[11] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[12] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[13] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[14] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[15] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[16] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[17] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[18] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[19] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[20] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[21] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[22] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[23] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[24] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[25] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[26] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[27] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[28] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[29] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[30] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[31] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[32] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[33] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[34] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[35] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[36] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[37] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[38] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[39] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[40] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[41] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[42] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[43] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[44] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[45] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[46] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[47] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[48] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[49] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[50] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[51] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[52] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[53] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[54] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[55] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[56] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[57] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[58] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[59] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[60] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[61] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[62] = TSIP.REG_100H.WORD;
                OutData_PreMasterSecret[63] = TSIP.REG_100H.WORD;
                RX72M_RX72N_RX66N_func102(change_endian_long(0x38cd72ccu), change_endian_long(0x931bd838u), change_endian_long(0x801fea22u), change_endian_long(0x8fc1e99au));
                TSIP.REG_1BCH.WORD = 0x00000040u;
                /* WAIT_LOOP */
                while (0u != TSIP.REG_18H.BIT.B12)
                {
                    /* waiting */
                }
                #if TSIP_MULTI_THREADING == 1
                TSIP_MULTI_THREADING_UNLOCK_FUNCTION();
                #endif /* TSIP_MULTI_THREADING == 1 */
                return TSIP_SUCCESS;
            }
        }
    }
}
/**********************************************************************************************************************
 End of function ./input_dir/RX72M/RX72M_pe2.prc
 *********************************************************************************************************************/
#endif /* #if TSIP_TLS == 1 */
