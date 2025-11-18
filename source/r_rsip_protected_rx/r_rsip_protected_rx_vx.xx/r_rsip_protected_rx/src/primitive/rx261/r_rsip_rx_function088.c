/*
 * Copyright (c) 2015 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 15.10.2024 1.00     First Release.
 *         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
 *         :                     Revised key management specification
 *********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_rsip_primitive.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

void r_rsip_func088_r1(void)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    r_rsip_func100(0xa245e636U, 0x1c41e4b7U, 0xd3a4f021U, 0x987ddad0U);
    RSIP.REG_00A0H.WORD = 0x20010000U;
    r_rsip_func103();
    r_rsip_func100(0x8c621658U, 0x0ac5b536U, 0xf6c31910U, 0xcff8ec50U);
    RSIP.REG_00B0H.WORD = 0x0000140fU;
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x0c200104U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_0000H.WORD = 0x00c10011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    r_rsip_func103();
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x0c200104U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_0000H.WORD = 0x00c10011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_00B0H.WORD = 0x00001428U;
    RSIP.REG_0000H.WORD = 0x00c0001dU;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0014H.WORD = 0x000000a5U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
    RSIP.REG_00B0H.WORD = 0x0000142dU;
    RSIP.REG_0000H.WORD = 0x00c0001dU;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0014H.WORD = 0x000000a5U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000002U);
    RSIP.REG_00B4H.WORD = 0x002d000aU;
    RSIP.REG_00B8H.WORD = 0x00140000U;
    RSIP.REG_00A4H.WORD = 0x0404000aU;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B8H.WORD = 0x00000014U;
    RSIP.REG_00A4H.WORD = 0x04040010U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x0028000fU;
    RSIP.REG_00B8H.WORD = 0x00230014U;
    RSIP.REG_00A4H.WORD = 0x04040002U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x00280023U;
    RSIP.REG_00B8H.WORD = 0x00140000U;
    RSIP.REG_00A4H.WORD = 0x04040009U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x00140032U;
    RSIP.REG_00B8H.WORD = 0x000f000aU;
    RSIP.REG_00A4H.WORD = 0x04040005U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x0028000fU;
    RSIP.REG_00B8H.WORD = 0x002d0000U;
    RSIP.REG_00A4H.WORD = 0x0404000aU;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_0040H.WORD = 0x00210000U;
    r_rsip_func100(0x04e1528cU, 0xf4ddc3beU, 0xf67d73e4U, 0x886f9e7dU);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        RSIP.REG_0094H.WORD = 0x00000800U;
        r_rsip_func101(0xfbefbba5U, 0xd54dd946U, 0x7886de26U, 0x140fc8fcU);
    }
    else
    {
        r_rsip_func100(0x3a1ea2f7U, 0xfd2f27f2U, 0x383a6098U, 0xf67610e0U);
        RSIP.REG_00B8H.WORD = 0x00000005U;
        RSIP.REG_00A4H.WORD = 0x04040010U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_00B4H.WORD = 0x00280037U;
        RSIP.REG_00B8H.WORD = 0x00230005U;
        RSIP.REG_00A4H.WORD = 0x04040002U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_00B0H.WORD = 0x0000143cU;
        RSIP.REG_0000H.WORD = 0x00c00021U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        RSIP.REG_00B4H.WORD = 0x003c005fU;
        RSIP.REG_00B8H.WORD = 0x00280000U;
        RSIP.REG_00A4H.WORD = 0x04040009U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_00B4H.WORD = 0x003c0005U;
        RSIP.REG_00B8H.WORD = 0x002d0000U;
        RSIP.REG_00A4H.WORD = 0x04040009U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_00B4H.WORD = 0x000f0023U;
        RSIP.REG_00B8H.WORD = 0x0046002dU;
        RSIP.REG_00A4H.WORD = 0x04040015U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_0040H.WORD = 0x00000d00U;
        RSIP.REG_00B0H.WORD = 0x0000140fU;
        RSIP.REG_0000H.WORD = 0x00c0001dU;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        RSIP.REG_0014H.WORD = 0x000000a5U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
        RSIP.REG_00B4H.WORD = 0x000f0046U;
        RSIP.REG_00B8H.WORD = 0x004b0000U;
        RSIP.REG_00A4H.WORD = 0x0404000aU;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_0040H.WORD = 0x00210000U;
        r_rsip_func100(0x450e85a8U, 0x1a145f8bU, 0xa640ecb6U, 0xabb15022U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            RSIP.REG_0094H.WORD = 0x00000800U;
            r_rsip_func101(0x5952a829U, 0x216b74c2U, 0x968c4b00U, 0x1de2f978U);
        }
        else
        {
            r_rsip_func100(0xf961226fU, 0x19e5f5e2U, 0x0f91bd60U, 0x1496c828U);
            RSIP.REG_00B4H.WORD = 0x00140023U;
            RSIP.REG_00B8H.WORD = 0x0055002dU;
            RSIP.REG_00A4H.WORD = 0x04040015U;
            RSIP.REG_00A0H.WORD = 0x20010001U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_00A8H.BIT.B0)
            {
                /* waiting */
            }
            RSIP.REG_00ACH.WORD = 0x00000001U;
            RSIP.REG_0040H.WORD = 0x00000d00U;
            RSIP.REG_00B0H.WORD = 0x0000140fU;
            RSIP.REG_0000H.WORD = 0x00c0001dU;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_0014H.WORD = 0x000000a5U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
            RSIP.REG_00B4H.WORD = 0x000f0055U;
            RSIP.REG_00B8H.WORD = 0x00190000U;
            RSIP.REG_00A4H.WORD = 0x0404000aU;
            RSIP.REG_00A0H.WORD = 0x20010001U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_00A8H.BIT.B0)
            {
                /* waiting */
            }
            RSIP.REG_00ACH.WORD = 0x00000001U;
            RSIP.REG_0040H.WORD = 0x00210000U;
            r_rsip_func100(0xc3340552U, 0xf806c068U, 0x8189722bU, 0x06aa6c96U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                RSIP.REG_0094H.WORD = 0x00000800U;
                r_rsip_func101(0x5c11a819U, 0x63151a5bU, 0xc0f0a43eU, 0xd7aff548U);
            }
            else
            {
                r_rsip_func100(0x4c21f315U, 0x7f7827f8U, 0x8683e8aeU, 0x81a44442U);
                RSIP.REG_00B4H.WORD = 0x000f0055U;
                RSIP.REG_00B8H.WORD = 0x00230005U;
                RSIP.REG_00A4H.WORD = 0x04040002U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B0H.WORD = 0x00001414U;
                RSIP.REG_0000H.WORD = 0x00c0001dU;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                RSIP.REG_0014H.WORD = 0x000000a5U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0014H.BIT.B31)
                {
                    /* waiting */
                }
                RSIP.REG_002CH.WORD = bswap_32big(0x00000002U);
                RSIP.REG_00B4H.WORD = 0x00140005U;
                RSIP.REG_00B8H.WORD = 0x000f0000U;
                RSIP.REG_00A4H.WORD = 0x0404000aU;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B4H.WORD = 0x000f0023U;
                RSIP.REG_00B8H.WORD = 0x00140005U;
                RSIP.REG_00A4H.WORD = 0x04040000U;
                RSIP.REG_0008H.WORD = 0x00020000U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_0040H.WORD = 0x00000d00U;
                RSIP.REG_00B4H.WORD = 0x0014004bU;
                RSIP.REG_00B8H.WORD = 0x00190005U;
                RSIP.REG_00A4H.WORD = 0x04040002U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B4H.WORD = 0x00140050U;
                RSIP.REG_00B8H.WORD = 0x001e0005U;
                RSIP.REG_00A4H.WORD = 0x04040002U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B4H.WORD = 0x001e0005U;
                RSIP.REG_00B8H.WORD = 0x000f0000U;
                RSIP.REG_00A4H.WORD = 0x0404000aU;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B4H.WORD = 0x0037000fU;
                RSIP.REG_00B8H.WORD = 0x00500005U;
                RSIP.REG_00A4H.WORD = 0x04040002U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B4H.WORD = 0x00370019U;
                RSIP.REG_00B8H.WORD = 0x000f0005U;
                RSIP.REG_00A4H.WORD = 0x04040002U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B0H.WORD = 0x00001414U;
                RSIP.REG_0000H.WORD = 0x00c00021U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                RSIP.REG_00B4H.WORD = 0x0014000fU;
                RSIP.REG_00B8H.WORD = 0x004b0000U;
                RSIP.REG_00A4H.WORD = 0x04040009U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B0H.WORD = 0x0000142dU;
                RSIP.REG_0000H.WORD = 0x00c0001dU;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                RSIP.REG_0014H.WORD = 0x000000a5U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0014H.BIT.B31)
                {
                    /* waiting */
                }
                RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
                RSIP.REG_00B4H.WORD = 0x002d0037U;
                RSIP.REG_00B8H.WORD = 0x00550005U;
                RSIP.REG_00A4H.WORD = 0x04040002U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B4H.WORD = 0x00550046U;
                RSIP.REG_00B8H.WORD = 0x00230005U;
                RSIP.REG_00A4H.WORD = 0x04040013U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_0040H.WORD = 0x00000d00U;
                RSIP.REG_00B4H.WORD = 0x002d0023U;
                RSIP.REG_00B8H.WORD = 0x00280000U;
                RSIP.REG_00A4H.WORD = 0x0404000aU;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_0040H.WORD = 0x00210000U;
                r_rsip_func100(0x5948fc67U, 0x98a978f7U, 0xf72de54bU, 0xd9dae1a7U);
                RSIP.REG_0040H.WORD = 0x00400000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                if (1U == (RSIP.REG_0040H.BIT.B22))
                {
                    RSIP.REG_0094H.WORD = 0x00000800U;
                    r_rsip_func101(0xe50a1b94U, 0xf8fab026U, 0x5ebfd474U, 0x4d78711dU);
                }
                else
                {
                    r_rsip_func100(0xdf38fa57U, 0x0bf440b3U, 0x6d48d38bU, 0x76c4c565U);
                    RSIP.REG_00B4H.WORD = 0x002d0023U;
                    RSIP.REG_00B8H.WORD = 0x00280005U;
                    RSIP.REG_00A4H.WORD = 0x04040002U;
                    RSIP.REG_00A0H.WORD = 0x20010001U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_00A8H.BIT.B0)
                    {
                        /* waiting */
                    }
                    RSIP.REG_00ACH.WORD = 0x00000001U;
                    RSIP.REG_00B0H.WORD = 0x00001414U;
                    RSIP.REG_0000H.WORD = 0x00c0001dU;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0004H.BIT.B30)
                    {
                        /* waiting */
                    }
                    RSIP.REG_0040H.WORD = 0x00001800U;
                    RSIP.REG_0014H.WORD = 0x000000a5U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = bswap_32big(0x00000002U);
                    RSIP.REG_00B4H.WORD = 0x00140005U;
                    RSIP.REG_00B8H.WORD = 0x000f0000U;
                    RSIP.REG_00A4H.WORD = 0x0404000aU;
                    RSIP.REG_00A0H.WORD = 0x20010001U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_00A8H.BIT.B0)
                    {
                        /* waiting */
                    }
                    RSIP.REG_00ACH.WORD = 0x00000001U;
                    RSIP.REG_00B4H.WORD = 0x000f0028U;
                    RSIP.REG_00B8H.WORD = 0x00140005U;
                    RSIP.REG_00A4H.WORD = 0x04040000U;
                    RSIP.REG_0008H.WORD = 0x00020000U;
                    RSIP.REG_00A0H.WORD = 0x20010001U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_00A8H.BIT.B0)
                    {
                        /* waiting */
                    }
                    RSIP.REG_00ACH.WORD = 0x00000001U;
                    RSIP.REG_0040H.WORD = 0x00000d00U;
                    RSIP.REG_00B4H.WORD = 0x00140019U;
                    RSIP.REG_00B8H.WORD = 0x00280005U;
                    RSIP.REG_00A4H.WORD = 0x04040002U;
                    RSIP.REG_00A0H.WORD = 0x20010001U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_00A8H.BIT.B0)
                    {
                        /* waiting */
                    }
                    RSIP.REG_00ACH.WORD = 0x00000001U;
                    RSIP.REG_00B4H.WORD = 0x0014001eU;
                    RSIP.REG_00B8H.WORD = 0x002d0005U;
                    RSIP.REG_00A4H.WORD = 0x04040002U;
                    RSIP.REG_00A0H.WORD = 0x20010001U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_00A8H.BIT.B0)
                    {
                        /* waiting */
                    }
                    RSIP.REG_00ACH.WORD = 0x00000001U;
                    RSIP.REG_0094H.WORD = 0x0000b400U;
                    RSIP.REG_0094H.WORD = 0x618c5618U;
                    r_rsip_func101(0x7e6d0837U, 0x1b0eb9cdU, 0x8675c2f1U, 0x3443565eU);
                }
            }
        }
    }
    RSIP.REG_0094H.WORD = 0x38008800U;
    RSIP.REG_0094H.WORD = 0x618c5618U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00A60000U;
    RSIP.REG_0094H.WORD = 0x00007c07U;
    RSIP.REG_0040H.WORD = 0x00602000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
}
