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
* Function Name: R_TSIP_SelfCheck1Sub
*******************************************************************************************************************/ /**
* @details       RX671 TSIP Initialization 1
* @retval        TSIP_SUCCESS
* @retval        TSIP_ERR_FAIL
* @retval        TSIP_ERR_RESOURCE_CONFLICT
* @note          None
*/
e_tsip_err_t R_TSIP_SelfCheck1Sub(void)
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
    R_TSIP_SelfCheck1SubSub();

    TSIP.REG_138H.WORD = 0xf597806Au;
    TSIP.REG_F0H.WORD = 0x00000000u;
    TSIP.REG_04H.WORD = 0x00000001u;
    TSIP.REG_10CH.WORD = 0x0000057bu;
    if (0x0u != (TSIP.REG_1BCH.WORD & 0x1fu))
    {
        return TSIP_ERR_RESOURCE_CONFLICT;
    }
    TSIP.REG_80H.WORD = 0x00000001u;
    TSIP.REG_28H.WORD = 0x00000001u;
    TSIP.REG_7CH.WORD = 0x00000001u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_64H.BIT.B11)
    {
        /* waiting */
    }
    TSIP.REG_64H.WORD = 0x00000008u;
    TSIP.REG_84H.WORD = 0x00010101u;
    TSIP.REG_13CH.WORD = 0x00000F00u;
    TSIP.REG_88H.WORD = 0x00008001u;
    TSIP.REG_104H.WORD = 0x00000352u;
    RX671_func101(0x196e4dfau, 0xff83c99eu, 0x31af3cdfu, 0x11449e07u);
    TSIP.REG_88H.WORD = 0x00000000u;
    TSIP.REG_104H.WORD = 0x00000352u;
    TSIP.REG_C4H.WORD = 0x000f3a0du;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = 0x87100519u;
    TSIP.REG_100H.WORD = 0x7a157131u;
    TSIP.REG_100H.WORD = 0x341e45bbu;
    TSIP.REG_100H.WORD = 0xbef0c2a1u;
    RX671_func101(0xcf713503u, 0xf2682921u, 0x968d7b7bu, 0xa02b3e45u);
    RX671_func100(0xa9f7bf06u, 0xa4393702u, 0xf1e4c877u, 0x09326e2fu);
    TSIP.REG_04H.WORD = 0x00001001u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    if (0u == (TSIP.REG_18H.BIT.B13))
    {
        TSIP.REG_1BCH.WORD = 0x00000020u;
        return TSIP_ERR_FAIL;
    }
    else
    {
        TSIP.REG_13CH.WORD = 0x00000201u;
        RX671_func102(0x7363fe55u, 0x7cca05e8u, 0x807b3273u, 0xccf7fac8u);
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
 End of function ./input_dir/RX671/RX671_p01.prc
 *********************************************************************************************************************/
TSIP_SEC_DEFAULT
