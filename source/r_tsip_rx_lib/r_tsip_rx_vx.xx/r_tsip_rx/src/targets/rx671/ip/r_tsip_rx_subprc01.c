/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED  AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2015-2024 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
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
* Function Name: R_TSIP_SelfCheck1SubSub
*******************************************************************************************************************/ /**
* @details       RX671 TSIP selftest subprocedure 01
* @note          None
*/
void R_TSIP_SelfCheck1SubSub(void)
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
    TSIP.REG_138H.WORD = 0xf597806Au;
    TSIP.REG_10CH.WORD = 0x00010001u;
    TSIP.REG_10H.WORD = 0x01234567u;
    TSIP.REG_7CH.WORD = 0x00000001u;
    TSIP.REG_78H.WORD = 0x00008007u;
    TSIP.REG_134H.WORD = 0x76543210u;
    RX671_func054(change_endian_long(0x00003008u), change_endian_long(0x00003018u));
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B31)
    {
        /* waiting */
    }
    RX671_func050(change_endian_long(0x00010001u));
    /* WAIT_LOOP */
    while (0u != TSIP.REG_64H.BIT.B11)
    {
        /* waiting */
    }
    TSIP.REG_64H.WORD = 0x00000008u;
    TSIP.REG_68H.WORD = 0x00000417u;
    TSIP.REG_6CH.WORD = 0xabcdef01u;
    RX671_func054(change_endian_long(0x10003008u), change_endian_long(0x10003018u));
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B31)
    {
        /* waiting */
    }
    RX671_func050(change_endian_long(0x00000001u));
    TSIP.REG_28H.WORD = 0x00000001u;
    TSIP.REG_3CH.WORD = 0x00010173u;
    TSIP.REG_4CH.WORD = 0x23456789u;
    TSIP.REG_80H.WORD = 0x00000001u;
    TSIP.REG_8CH.WORD = 0x000080BBu;
    TSIP.REG_94H.WORD = 0xabcdef01u;
    TSIP.REG_7CH.WORD = 0x00000001u;
    TSIP.REG_78H.WORD = 0x0000011fu;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_64H.BIT.B11)
    {
        /* waiting */
    }
    TSIP.REG_64H.WORD = 0x00000008u;
    TSIP.REG_68H.WORD = 0x00000017u;
    RX671_func054(change_endian_long(0x72f01007u), change_endian_long(0x72f01017u));
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B31)
    {
        /* waiting */
    }
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        RX671_func050(change_endian_long(0x00000001u));
        RX671_func054(change_endian_long(0x72f03007u), change_endian_long(0x72f03017u));
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B31)
        {
            /* waiting */
        }
    }
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        RX671_func050(change_endian_long(0x00000001u));
        TSIP.REG_28H.WORD = 0x00000001u;
        TSIP.REG_80H.WORD = 0x00000001u;
        TSIP.REG_7CH.WORD = 0x00000001u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x00000008u;
        RX671_func054(change_endian_long(0x72f03007u), change_endian_long(0x72f03017u));
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B31)
        {
            /* waiting */
        }
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        RX671_func050(change_endian_long(0x00000001u));
        TSIP.REG_28H.WORD = 0x00000001u;
        TSIP.REG_3CH.WORD = 0x00010173u;
        TSIP.REG_80H.WORD = 0x00000001u;
        TSIP.REG_B0H.WORD = 0x40000010u;
        TSIP.REG_D0H.WORD = 0x40000010u;
        TSIP.REG_A4H.WORD = 0x00008000u;
        TSIP.REG_C4H.WORD = 0x00008000u;
        TSIP.REG_8CH.WORD = 0x0000888Bu;
        TSIP.REG_7CH.WORD = 0x00000001u;
        TSIP.REG_78H.WORD = 0x00000007u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_64H.BIT.B11)
        {
            /* waiting */
        }
        TSIP.REG_64H.WORD = 0x00000008u;
        TSIP.REG_68H.WORD = 0x00000017u;
        RX671_func054(change_endian_long(0x7af03007u), change_endian_long(0x7af03017u));
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B31)
        {
            /* waiting */
        }
    }
    RX671_func051();
    TSIP.REG_28H.WORD = 0x00000001u;
    TSIP.REG_3CH.WORD = 0x00810173u;
    RX671_func054(change_endian_long(0x00003008u), change_endian_long(0x00003018u));
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B31)
    {
        /* waiting */
    }
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        RX671_func052(change_endian_long(0x00810173u));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        RX671_func052(change_endian_long(0x0080197fu));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        RX671_func052(change_endian_long(0x00fe017bu));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        RX671_func052(change_endian_long(0x00af091Fu));
    }
    RX671_func053(change_endian_long(0x000380BBu));
    for(iLoop = 0; iLoop < 6; iLoop = iLoop + 1)
    {
        RX671_func053(change_endian_long(0x000380BBu));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        RX671_func053(change_endian_long(0x000191BBu));
    }
    for(iLoop = 0; iLoop < 3; iLoop = iLoop + 1)
    {
        RX671_func053(change_endian_long(0x000185B7u));
    }
}
/**********************************************************************************************************************
 End of function ./input_dir/RX671/RX671_subprc01.prc
 *********************************************************************************************************************/
TSIP_SEC_DEFAULT
