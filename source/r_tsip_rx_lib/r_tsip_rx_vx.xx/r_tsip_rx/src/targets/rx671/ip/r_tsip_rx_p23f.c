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

#if TSIP_FIRMWARE_UPDATE == 1
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
TSIP_SEC_P_SECURE_BOOT

/***********************************************************************************************************************
* Function Name: R_TSIP_GenerateFirmwareMacFinalSub
*******************************************************************************************************************/ /**
* @details       RX72M F/W update Final
* @param[in]     InData_UpProgram
* @param[in]     MAX_CNT
* @param[in]     InData_UpMAC
* @param[out]    OutData_Program
* @param[out]    OutData_MAC
* @retval        TSIP_SUCCESS
* @retval        TSIP_ERR_FAIL
* @note          None
*/
e_tsip_err_t R_TSIP_GenerateFirmwareMacFinalSub(uint32_t *InData_UpProgram, uint32_t *InData_UpMAC, uint32_t *OutData_Program, uint32_t *OutData_MAC, uint32_t MAX_CNT)
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
    RX671_func100(change_endian_long(0xff02017au), change_endian_long(0xefc2ba0cu), change_endian_long(0x18068c37u), change_endian_long(0x5083b117u));
    TSIP.REG_00H.WORD = 0x80002100u;
    TSIP.REG_104H.WORD = 0x000000b1u;
    TSIP.REG_A4H.WORD = 0x00d049a6u;
    TSIP.REG_C4H.WORD = 0x00f0088eu;
    TSIP.REG_04H.WORD = 0x0000c201u;
    iLoop = 0;
    if (MAX_CNT > 4)
    {
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 0];
        TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 1];
        TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 2];
        TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 3];
        for (iLoop = 4; iLoop < MAX_CNT-4; iLoop = iLoop + 4)
        {
            /* WAIT_LOOP */
            while (1u != TSIP.REG_104H.BIT.B31)
            {
                /* waiting */
            }
            TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 0];
            TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 1];
            TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 2];
            TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 3];
            /* WAIT_LOOP */
            while (1u != TSIP.REG_04H.BIT.B30)
            {
                /* waiting */
            }
            OutData_Program[iLoop-4 + 0] = TSIP.REG_100H.WORD;
            OutData_Program[iLoop-4 + 1] = TSIP.REG_100H.WORD;
            OutData_Program[iLoop-4 + 2] = TSIP.REG_100H.WORD;
            OutData_Program[iLoop-4 + 3] = TSIP.REG_100H.WORD;
        }
        /* WAIT_LOOP */
        while (1u != TSIP.REG_04H.BIT.B30)
        {
            /* waiting */
        }
        OutData_Program[iLoop-4 + 0] = TSIP.REG_100H.WORD;
        OutData_Program[iLoop-4 + 1] = TSIP.REG_100H.WORD;
        OutData_Program[iLoop-4 + 2] = TSIP.REG_100H.WORD;
        OutData_Program[iLoop-4 + 3] = TSIP.REG_100H.WORD;
    }
    RX671_func202();//DisableINTEGRATE_WRRDYBandINTEGRATE_RDRDYBinthisfunction.
    RX671_func100(change_endian_long(0xa5b4cdfau), change_endian_long(0x951991a6u), change_endian_long(0xd4add25fu), change_endian_long(0xa4d96a79u));
    TSIP.REG_104H.WORD = 0x00000361u;
    TSIP.REG_A4H.WORD = 0x00d049a5u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 0];
    TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 1];
    TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 2];
    TSIP.REG_100H.WORD = InData_UpProgram[iLoop + 3];
    TSIP.REG_E0H.WORD = 0x80040000u;
    TSIP.REG_00H.WORD = 0x00008113u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_E0H.WORD = 0x81040000u;
    TSIP.REG_04H.WORD = 0x00000613u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_Program[iLoop + 0] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_Program[iLoop+1 + 0] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_Program[iLoop+2 + 0] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_Program[iLoop+3 + 0] = TSIP.REG_100H.WORD;
    TSIP.REG_104H.WORD = 0x00000052u;
    TSIP.REG_C4H.WORD = 0x00400accu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_C4H.WORD = 0x00050c45u;
    TSIP.REG_00H.WORD = 0x00002213u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_C4H.WORD = 0x00050e5du;
    TSIP.REG_E0H.WORD = 0x81040000u;
    TSIP.REG_00H.WORD = 0x00002813u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_104H.WORD = 0x00000361u;
    TSIP.REG_A4H.WORD = 0x000049a5u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = InData_UpMAC[0];
    TSIP.REG_100H.WORD = InData_UpMAC[1];
    TSIP.REG_100H.WORD = InData_UpMAC[2];
    TSIP.REG_100H.WORD = InData_UpMAC[3];
    TSIP.REG_A4H.WORD = 0x00900c45u;
    TSIP.REG_00H.WORD = 0x00001113u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    RX671_func100(change_endian_long(0x25f34b19u), change_endian_long(0x2650631bu), change_endian_long(0x5c4996acu), change_endian_long(0x3128c7ebu));
    TSIP.REG_1CH.WORD = 0x00400000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    if (1u == (TSIP.REG_1CH.BIT.B22))
    {
        RX671_func102(change_endian_long(0x1a7225a3u), change_endian_long(0x4182647eu), change_endian_long(0x7d5a461cu), change_endian_long(0x01c37c1fu));
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
        RX671_func100(change_endian_long(0x60dda712u), change_endian_long(0xb0c69d4cu), change_endian_long(0x0118ebaeu), change_endian_long(0x0643def4u));
        TSIP.REG_104H.WORD = 0x00000052u;
        TSIP.REG_C4H.WORD = 0x00000cc4u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
        TSIP.REG_04H.WORD = 0x00000213u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_04H.BIT.B30)
        {
            /* waiting */
        }
        OutData_MAC[0] = TSIP.REG_100H.WORD;
        OutData_MAC[1] = TSIP.REG_100H.WORD;
        OutData_MAC[2] = TSIP.REG_100H.WORD;
        OutData_MAC[3] = TSIP.REG_100H.WORD;
        TSIP.REG_13CH.WORD = 0x000002ffu;
        RX671_func102(change_endian_long(0x661c8ee2u), change_endian_long(0x43de3c27u), change_endian_long(0x14f3dfbcu), change_endian_long(0xd2c79401u));
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
/**********************************************************************************************************************
 End of function ./input_dir/RX671/RX671_p23f.prc
 *********************************************************************************************************************/
#endif /* #if TSIP_FIRMWARE_UPDATE == 1 */
TSIP_SEC_DEFAULT
