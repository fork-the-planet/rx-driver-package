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
* Function Name: R_TSIP_SelfCheck2Sub
*******************************************************************************************************************/ /**
* @details       RX26T initialization2
* @retval        TSIP_SUCCESS
* @retval        TSIP_ERR_RESOURCE_CONFLICT
* @retval        TSIP_ERR_RETRY
* @note          None
*/
e_tsip_err_t R_TSIP_SelfCheck2Sub(void)
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
    if (0x0u != (TSIP.REG_1BCH.WORD & 0x1fu))
    {
        return TSIP_ERR_RESOURCE_CONFLICT;
    }
    TSIP.REG_84H.WORD = 0x00000201u;
    TSIP.REG_108H.WORD = 0x00000000u;
    TSIP.REG_ECH.WORD = 0x3000a800u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_ECH.WORD = 0x00000003u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_ECH.WORD = 0x00010020u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_ECH.WORD = 0x00000800u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_ECH.WORD = 0x00000080u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    RX26T_function001(0x6b880613u, 0x20b7397cu, 0x52eb4790u, 0xe3e07794u);
    TSIP.REG_ECH.WORD = 0x00007c00u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_1CH.WORD = 0x00600000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    if (0x00000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x00000008u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x0000005Cu;
        RX26T_function002(0xea2665d8u, 0xa24e4b5du, 0x569b136au, 0x3fc1be10u);
    }
    else if (0x01000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x00000008u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x0000005eu;
        RX26T_function002(0x8f46d031u, 0x9e4a8601u, 0x94b6188cu, 0xd1b6c768u);
    }
    else if (0x02000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x00000008u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x0000005du;
        RX26T_function002(0x4cfb1165u, 0x5b010dfdu, 0xf69fa135u, 0x98d5975eu);
    }
    TSIP.REG_A4H.WORD = 0x00040804u;
    TSIP.REG_E0H.WORD = 0x81010000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_00H.WORD = 0x00001807u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    R_TSIP_SelfCheck2SubSub();

    /* WAIT_LOOP */
    while (0u != TSIP.REG_64H.BIT.B11)
    {
        /* waiting */
    }
    TSIP.REG_104H.WORD = 0x00000051u;
    TSIP.REG_A4H.WORD = 0x00000684u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = 0x00000000u;
    TSIP.REG_E0H.WORD = 0x80010000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_00H.WORD = 0x00008107u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_00H.WORD = 0x0000010fu;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_ECH.WORD = 0x00002c00u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    RX26T_function001(0xb40a4132u, 0x473f68e3u, 0x3212048eu, 0xa4b946a7u);
    TSIP.REG_1CH.WORD = 0x00400000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    if (1u == (TSIP.REG_1CH.BIT.B22))
    {
        RX26T_function003(0x64c94fcbu, 0x7e3dc66du, 0xaf4a2921u, 0xd863114au);
        TSIP.REG_1BCH.WORD = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_18H.BIT.B12)
        {
            /* waiting */
        }
        return TSIP_ERR_RETRY;
    }
    else
    {
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x0000001cu;
        TSIP.REG_104H.WORD = 0x00000051u;
        TSIP.REG_A4H.WORD = 0x00200684u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_E0H.WORD = 0x80040000u;
        TSIP.REG_1D0H.WORD = 0x00000000u;
        TSIP.REG_00H.WORD = 0x00008113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_A4H.WORD = 0xc0200c9du;
        TSIP.REG_00H.WORD = 0x00001413u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x00000000u;
        TSIP.REG_E0H.WORD = 0x80040080u;
        TSIP.REG_1D0H.WORD = 0x00000000u;
        TSIP.REG_00H.WORD = 0x00008113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        RX26T_function001(0x0d5379d3u, 0x57e64bf3u, 0x8194340eu, 0x6f91e5dau);
        TSIP.REG_104H.WORD = 0x00000051u;
        TSIP.REG_A4H.WORD = 0x000b0804u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_104H.WORD = 0x00000351u;
        TSIP.REG_A4H.WORD = 0x00010805u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_100H.WORD = 0x00000001u;
        RX26T_function001(0x5d5c1855u, 0x95c4716cu, 0x49cdfae8u, 0xbb856015u);
        TSIP.REG_B0H.WORD = 0x00000100u;
        TSIP.REG_A4H.WORD = 0x0020b6bfu;
        TSIP.REG_E0H.WORD = 0x81080000u;
        TSIP.REG_1D0H.WORD = 0x00000000u;
        TSIP.REG_00H.WORD = 0x00001823u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_A4H.WORD = 0x000b0805u;
        TSIP.REG_00H.WORD = 0x00001113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_A4H.WORD = 0x00010805u;
        TSIP.REG_00H.WORD = 0x00001113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        RX26T_function001(0xe97e35f3u, 0x902135adu, 0x8fb5c906u, 0x0d2ae44fu);
        TSIP.REG_104H.WORD = 0x00000251u;
        TSIP.REG_A4H.WORD = 0x0020363cu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_A4H.WORD = 0x002036bcu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_A4H.WORD = 0x002036bcu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_A4H.WORD = 0x00060805u;
        TSIP.REG_00H.WORD = 0x00001113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_104H.WORD = 0x00000151u;
        TSIP.REG_A4H.WORD = 0x0021340cu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_A4H.WORD = 0x000b0805u;
        TSIP.REG_00H.WORD = 0x00001113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_A4H.WORD = 0x01000684u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        RX26T_function001(0x02d907b8u, 0x0d02be0au, 0x92e2101fu, 0x614d1c69u);
        TSIP.REG_A4H.WORD = 0x000d0805u;
        TSIP.REG_00H.WORD = 0x00001113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        RX26T_function001(0xf916eac3u, 0x077a6fa7u, 0x1ed81e32u, 0x3279e540u);
        TSIP.REG_104H.WORD = 0x00000251u;
        TSIP.REG_A4H.WORD = 0x0020363cu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_A4H.WORD = 0x002036bcu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_A4H.WORD = 0x002036bcu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_A4H.WORD = 0x00060805u;
        TSIP.REG_00H.WORD = 0x00001113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_104H.WORD = 0x00000151u;
        TSIP.REG_A4H.WORD = 0x0021340cu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        TSIP.REG_A4H.WORD = 0x000b0805u;
        TSIP.REG_00H.WORD = 0x00001113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_A4H.WORD = 0x01000684u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = 0x00000000u;
        RX26T_function001(0x1cfd32bbu, 0x91f12e99u, 0xc508c22cu, 0x924f62bau);
        TSIP.REG_04H.WORD = 0x00000113u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_04H.BIT.B30)
        {
            /* waiting */
        }
        S_RAM[4+0 + 0] = change_endian_long(TSIP.REG_100H.WORD);
        S_RAM[4+0 + 1] = change_endian_long(TSIP.REG_100H.WORD);
        S_RAM[4+0 + 2] = change_endian_long(TSIP.REG_100H.WORD);
        S_RAM[4+0 + 3] = change_endian_long(TSIP.REG_100H.WORD);
        TSIP.REG_13CH.WORD = 0x00000202u;
        RX26T_function003(0x6842b270u, 0xfce4fc88u, 0x135cade7u, 0x512ab8e8u);
        TSIP.REG_1BCH.WORD = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_18H.BIT.B12)
        {
            /* waiting */
        }
        return TSIP_SUCCESS;
    }
}
/**********************************************************************************************************************
 End of function ./input_dir/RX26T/RX26T_p02.prc
 *********************************************************************************************************************/
TSIP_SEC_DEFAULT
