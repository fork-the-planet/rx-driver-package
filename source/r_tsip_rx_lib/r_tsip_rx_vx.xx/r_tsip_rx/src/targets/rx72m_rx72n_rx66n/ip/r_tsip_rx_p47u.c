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

#if TSIP_PRV_USE_AES_128 == 1
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
* Function Name: R_TSIP_Aes128EncryptDecryptUpdateSub
*******************************************************************************************************************/ /**
* @details       RX72M AES-128 Encryption/Decryption with ECB/CBC/CTR Mode Update
* @param[in]     InData_Text
* @param[in]     MAX_CNT
* @param[out]    OutData_Text
* @note          None
*/
void R_TSIP_Aes128EncryptDecryptUpdateSub(uint32_t *InData_Text, uint32_t *OutData_Text, uint32_t MAX_CNT)
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
    if (0x00000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        TSIP.REG_104H.WORD = 0x00000362u;
        RX72M_RX72N_RX66N_func100(change_endian_long(0x5d3f1e7au), change_endian_long(0x19861c5fu), change_endian_long(0x834b0d82u), change_endian_long(0x61016929u));
        TSIP.REG_104H.WORD = 0x000000b1u;
        TSIP.REG_A4H.WORD = 0x00000a86u;
        TSIP.REG_04H.WORD = 0x0000c100u;
    }
    else if (0x01000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        TSIP.REG_104H.WORD = 0x00000362u;
        RX72M_RX72N_RX66N_func100(change_endian_long(0xc27fa054u), change_endian_long(0xc09942dau), change_endian_long(0x6e57cc56u), change_endian_long(0x887c2df9u));
        TSIP.REG_104H.WORD = 0x000000b1u;
        TSIP.REG_A4H.WORD = 0x00004a86u;
        TSIP.REG_04H.WORD = 0x0000c100u;
    }
    else if (0x02000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        TSIP.REG_104H.WORD = 0x00000362u;
        RX72M_RX72N_RX66N_func100(change_endian_long(0x2e00e5edu), change_endian_long(0xb7166981u), change_endian_long(0xd78eb11cu), change_endian_long(0x8d73a061u));
        TSIP.REG_104H.WORD = 0x000000b1u;
        TSIP.REG_A4H.WORD = 0x00000e96u;
        TSIP.REG_04H.WORD = 0x0000c100u;
    }
    else if (0x03000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        TSIP.REG_104H.WORD = 0x00000362u;
        RX72M_RX72N_RX66N_func100(change_endian_long(0x11066197u), change_endian_long(0xc9a61312u), change_endian_long(0xca29fae1u), change_endian_long(0x4894c82eu));
        TSIP.REG_104H.WORD = 0x000000b1u;
        TSIP.REG_A4H.WORD = 0x000049a6u;
        TSIP.REG_04H.WORD = 0x0000c100u;
    }
    else if (0x04000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        TSIP.REG_104H.WORD = 0x00000362u;
        RX72M_RX72N_RX66N_func100(change_endian_long(0x28d8095fu), change_endian_long(0xc95e3aa2u), change_endian_long(0xbb7af886u), change_endian_long(0x38b1ad96u));
        TSIP.REG_104H.WORD = 0x000000b1u;
        TSIP.REG_A4H.WORD = 0x000007b6u;
        TSIP.REG_04H.WORD = 0x0000c100u;
    }
    if(MAX_CNT != 0)
    {
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_Text[0];
        TSIP.REG_100H.WORD = InData_Text[1];
        TSIP.REG_100H.WORD = InData_Text[2];
        TSIP.REG_100H.WORD = InData_Text[3];
        for (iLoop = 4; iLoop < MAX_CNT ; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1u != TSIP.REG_104H.BIT.B31)
            {
                /* waiting */
            }
            TSIP.REG_100H.WORD = InData_Text[iLoop + 0];
            TSIP.REG_100H.WORD = InData_Text[iLoop + 1];
            TSIP.REG_100H.WORD = InData_Text[iLoop + 2];
            TSIP.REG_100H.WORD = InData_Text[iLoop + 3];
            /* WAIT_LOOP */
            while (1u != TSIP.REG_04H.BIT.B30)
            {
                /* waiting */
            }
            OutData_Text[iLoop-4 + 0] = TSIP.REG_100H.WORD;
            OutData_Text[iLoop-4 + 1] = TSIP.REG_100H.WORD;
            OutData_Text[iLoop-4 + 2] = TSIP.REG_100H.WORD;
            OutData_Text[iLoop-4 + 3] = TSIP.REG_100H.WORD;
        }
        /* WAIT_LOOP */
        while (1u != TSIP.REG_04H.BIT.B30)
        {
            /* waiting */
        }
        OutData_Text[MAX_CNT-4 + 0] = TSIP.REG_100H.WORD;
        OutData_Text[MAX_CNT-4 + 1] = TSIP.REG_100H.WORD;
        OutData_Text[MAX_CNT-4 + 2] = TSIP.REG_100H.WORD;
        OutData_Text[MAX_CNT-4 + 3] = TSIP.REG_100H.WORD;
    }
    if (0x00000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX72M_RX72N_RX66N_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        RX72M_RX72N_RX66N_func101(change_endian_long(0x430cd022u), change_endian_long(0x754a8011u), change_endian_long(0x3d459c7du), change_endian_long(0x1911fe10u));
    }
    else if (0x01000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX72M_RX72N_RX66N_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        RX72M_RX72N_RX66N_func101(change_endian_long(0xaabf6858u), change_endian_long(0x5209b20du), change_endian_long(0xab7474c9u), change_endian_long(0x03321e5cu));
    }
    else if (0x02000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX72M_RX72N_RX66N_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        RX72M_RX72N_RX66N_func101(change_endian_long(0x6f9be2c0u), change_endian_long(0xc791d19cu), change_endian_long(0x76cb3c6du), change_endian_long(0x9e07b283u));
    }
    else if (0x03000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX72M_RX72N_RX66N_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        RX72M_RX72N_RX66N_func101(change_endian_long(0xc20b390au), change_endian_long(0x8d153b18u), change_endian_long(0x2908f747u), change_endian_long(0xcec60d8cu));
    }
    else if (0x04000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX72M_RX72N_RX66N_func206();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
        RX72M_RX72N_RX66N_func101(change_endian_long(0x4e868629u), change_endian_long(0x68456b71u), change_endian_long(0x9763dfa4u), change_endian_long(0x541b4ac2u));
    }
}
/**********************************************************************************************************************
 End of function ./input_dir/RX72M/RX72M_p47u_r1.prc
 *********************************************************************************************************************/
#endif /* #if TSIP_PRV_USE_AES_128 == 1 */
