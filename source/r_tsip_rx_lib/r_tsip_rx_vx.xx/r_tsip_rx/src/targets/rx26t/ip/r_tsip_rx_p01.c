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
* @details       RX26T TSIP Selftest Function1
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
    TSIP.REG_1D0H.WORD = 0x00000000u;
    R_TSIP_SelfCheck1SubSub();

    TSIP.REG_138H.WORD = 0xf597806Au;
    TSIP.REG_F0H.WORD = 0x00000000u;
    TSIP.REG_04H.WORD = 0x00000001u;
    if (0x0u != (TSIP.REG_1BCH.WORD & 0x1fu))
    {
        return TSIP_ERR_RESOURCE_CONFLICT;
    }
    TSIP.REG_80H.WORD = 0x00000001u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_64H.BIT.B11)
    {
        /* waiting */
    }
    TSIP.REG_64H.WORD = 0x00000008u;
    TSIP.REG_84H.WORD = 0x00010101u;
    TSIP.REG_13CH.WORD = 0x00000F00u;
    TSIP.REG_88H.WORD = 0x00008002u;
    TSIP.REG_104H.WORD = 0x00000351u;
    RX26T_function002(0x694e3801u, 0x37ef9bf1u, 0x089d7e8fu, 0x2fbaabc4u);
    TSIP.REG_88H.WORD = 0x00000000u;
    TSIP.REG_104H.WORD = 0x00000351u;
    TSIP.REG_A4H.WORD = 0x400f380du;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = 0x57a61dd7u;
    TSIP.REG_100H.WORD = 0xfb5c9169u;
    TSIP.REG_100H.WORD = 0xa359dffau;
    TSIP.REG_100H.WORD = 0xf83e7c40u;
    RX26T_function002(0x7fb15105u, 0x00848949u, 0x0f420424u, 0xac916425u);
    RX26T_function001(0xb5839ab1u, 0x8aae0044u, 0x0f3c47beu, 0xb35d913eu);
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
        RX26T_function003(0x7b6bb7a6u, 0x8c72d5ceu, 0x31a7f304u, 0x265a09e6u);
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
 End of function ./input_dir/RX26T/RX26T_p01.prc
 *********************************************************************************************************************/
TSIP_SEC_DEFAULT
