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

/***********************************************************************************************************************
* Function Name: R_TSIP_GenerateAes256RandomKeyIndexSub
*******************************************************************************************************************/ /**
* @details       RX231HU Create 256bit AES Key
* @param[out]    OutData_KeyIndex
* @retval        TSIP_SUCCESS
* @retval        TSIP_ERR_RESOURCE_CONFLICT
* @note          None
*/
e_tsip_err_t R_TSIP_GenerateAes256RandomKeyIndexSub(uint32_t *OutData_KeyIndex)
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
    TSIP.REG_84H.WORD = 0x00000701u;
    TSIP.REG_108H.WORD = 0x00000000u;
    RX231_RX23W_function001(change_endian_long(0x613e065cu), change_endian_long(0x544d38d1u), change_endian_long(0x0bd572f7u), change_endian_long(0xc2e24bcfu));
    TSIP.REG_104H.WORD = 0x00000251u;
    TSIP.REG_A4H.WORD = 0x0020363cu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_A4H.WORD = 0x002036bcu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_A4H.WORD = 0x002036bcu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
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
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
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
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    RX231_RX23W_function001(change_endian_long(0x6bd67e05u), change_endian_long(0x1f235b01u), change_endian_long(0xa3b6bb12u), change_endian_long(0x32b4863eu));
    TSIP.REG_E0H.WORD = 0x80040000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_00H.WORD = 0x00008113u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_E0H.WORD = 0x81040000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_04H.WORD = 0x00000612u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[0] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[1] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[2] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[3] = TSIP.REG_100H.WORD;
    TSIP.REG_A4H.WORD = 0x600c3a0du;
    TSIP.REG_E0H.WORD = 0x81040000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_00H.WORD = 0x00001813u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_A4H.WORD = 0x400c0a0cu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x213f32e4u);
    RX231_RX23W_function001(change_endian_long(0xc9636bbfu), change_endian_long(0xcc203fdfu), change_endian_long(0xceed79b9u), change_endian_long(0x9d65d499u));
    TSIP.REG_104H.WORD = 0x00000251u;
    TSIP.REG_A4H.WORD = 0x0020363cu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_A4H.WORD = 0x002036bcu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_A4H.WORD = 0x002036bcu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
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
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
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
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    RX231_RX23W_function001(change_endian_long(0x02277094u), change_endian_long(0x28ba21fcu), change_endian_long(0x654e1323u), change_endian_long(0x476434d5u));
    TSIP.REG_E0H.WORD = 0x80080000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_00H.WORD = 0x00008113u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_104H.WORD = 0x00000251u;
    TSIP.REG_A4H.WORD = 0x0020363cu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_A4H.WORD = 0x002036bcu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_A4H.WORD = 0x002036bcu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
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
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
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
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_00H.WORD = 0x00008113u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    RX231_RX23W_function001(change_endian_long(0x69a90eb7u), change_endian_long(0x28a76b72u), change_endian_long(0x98563a2eu), change_endian_long(0xe73b6f31u));
    TSIP.REG_B0H.WORD = 0x00000100u;
    TSIP.REG_A4H.WORD = 0x42e486bfu;
    TSIP.REG_E0H.WORD = 0x81080000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    TSIP.REG_00H.WORD = 0x00001823u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_104H.WORD = 0x00000351u;
    TSIP.REG_A4H.WORD = 0x400009cdu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_100H.WORD = change_endian_long(0x00000002u);
    TSIP.REG_04H.WORD = 0x00000133u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[4] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[5] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[6] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[7] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[8] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[9] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[10] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[11] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[12] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[13] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[14] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[15] = TSIP.REG_100H.WORD;
    RX231_RX23W_function003(change_endian_long(0x4a739455u), change_endian_long(0xdba98bd1u), change_endian_long(0x2c484061u), change_endian_long(0x4bd3ab80u));
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
/**********************************************************************************************************************
 End of function ./input_dir/RX231HU/RX231HU_p07.prc
 *********************************************************************************************************************/
