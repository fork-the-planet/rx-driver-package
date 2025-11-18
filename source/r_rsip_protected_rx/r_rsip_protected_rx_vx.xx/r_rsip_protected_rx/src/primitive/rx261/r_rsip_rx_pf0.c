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

rsip_ret_t r_rsip_pf0(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_DomainParam[], uint32_t OutData_Signature[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    if (0x0U != (RSIP.REG_006CH.WORD & 0x17U))
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    RSIP.REG_0070H.WORD = 0x00f00001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    RSIP.REG_0014H.WORD = 0x000000c7U;
    RSIP.REG_009CH.WORD = 0x80010000U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_CurveType[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0094H.WORD = 0x3420a800U;
    RSIP.REG_0094H.WORD = 0x00000003U;
    RSIP.REG_0094H.WORD = 0x2000b400U;
    RSIP.REG_0094H.WORD = 0x00000002U;
    r_rsip_func070(InData_DomainParam);
    r_rsip_func100(0xd54c7d25U, 0x49f922bdU, 0x103f9dc9U, 0x9aaf722eU);
    RSIP.REG_00B0H.WORD = 0x0000140fU;
    r_rsip_func103();
    r_rsip_func100(0xed562cf4U, 0x811a01e2U, 0x5f9b3c41U, 0xeb974316U);
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
    RSIP.REG_00B0H.WORD = 0x00001419U;
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
    RSIP.REG_00B4H.WORD = 0x0019000aU;
    RSIP.REG_00B8H.WORD = 0x00140000U;
    RSIP.REG_00A4H.WORD = 0x0404000aU;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00A0H.WORD = 0x20010000U;
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
    RSIP.REG_00B8H.WORD = 0x002d0014U;
    RSIP.REG_00A4H.WORD = 0x04040002U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x0028002dU;
    RSIP.REG_00B8H.WORD = 0x00320000U;
    RSIP.REG_00A4H.WORD = 0x04040009U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    r_rsip_func071(InData_DomainParam);
    RSIP.REG_0094H.WORD = 0x00003420U;
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x000000f0U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0xf698d71cU, 0x3b841503U, 0xa9bee387U, 0xf7d685a9U);
    r_rsip_func088_r1();
    r_rsip_func100(0xd4ee8ec9U, 0xcc492569U, 0x018d83c4U, 0x61e8a28aU);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0x68627610U, 0x2fbdeb94U, 0x75ab36aeU, 0x0e2ad324U);
        RSIP.REG_006CH.WORD = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0020H.BIT.B12)
        {
            /* waiting */
        }
        return RSIP_RET_FAIL;
    }
    else
    {
        RSIP.REG_00B8H.WORD = 0x0000000aU;
        RSIP.REG_00A4H.WORD = 0x04040010U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_00B4H.WORD = 0x005a0028U;
        RSIP.REG_00B8H.WORD = 0x002d000aU;
        RSIP.REG_00A4H.WORD = 0x04040002U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_0014H.WORD = 0x000000a5U;
        RSIP.REG_00B0H.WORD = 0x0000140fU;
        RSIP.REG_0000H.WORD = 0x00c0001dU;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
        RSIP.REG_00B4H.WORD = 0x000f002dU;
        RSIP.REG_00B8H.WORD = 0x0028000aU;
        RSIP.REG_00A4H.WORD = 0x04040002U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_00B4H.WORD = 0x000f0028U;
        RSIP.REG_00B8H.WORD = 0x00140000U;
        RSIP.REG_00A4H.WORD = 0x0404000aU;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_0040H.WORD = 0x00210000U;
        r_rsip_func100(0x0df125cfU, 0xad341cfbU, 0x85a63c28U, 0xb9b12c5eU);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0x0cc0ea76U, 0x48beee2fU, 0xad79a06fU, 0x1e69817fU);
            RSIP.REG_006CH.WORD = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0020H.BIT.B12)
            {
                /* waiting */
            }
            return RSIP_RET_FAIL;
        }
        else
        {
            r_rsip_func100(0x7522db5dU, 0xf835cfbfU, 0x9719e961U, 0xf8d9e851U);
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
            RSIP.REG_00B4H.WORD = 0x0014000aU;
            RSIP.REG_00B8H.WORD = 0x000f0000U;
            RSIP.REG_00A4H.WORD = 0x0404000aU;
            RSIP.REG_00A0H.WORD = 0x20010001U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_00A8H.BIT.B0)
            {
                /* waiting */
            }
            RSIP.REG_00ACH.WORD = 0x00000001U;
            RSIP.REG_00B4H.WORD = 0x000f0032U;
            RSIP.REG_00B8H.WORD = 0x0014000aU;
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
            RSIP.REG_00B4H.WORD = 0x005a0014U;
            RSIP.REG_00B8H.WORD = 0x000f000aU;
            RSIP.REG_00A4H.WORD = 0x04040002U;
            RSIP.REG_00A0H.WORD = 0x20010001U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_00A8H.BIT.B0)
            {
                /* waiting */
            }
            RSIP.REG_00ACH.WORD = 0x00000001U;
            RSIP.REG_0014H.WORD = 0x000007c5U;
            RSIP.REG_00B0H.WORD = 0x00001414U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_MsgDgst[0];
            RSIP.REG_002CH.WORD = InData_MsgDgst[1];
            RSIP.REG_002CH.WORD = InData_MsgDgst[2];
            RSIP.REG_002CH.WORD = InData_MsgDgst[3];
            RSIP.REG_002CH.WORD = InData_MsgDgst[4];
            RSIP.REG_002CH.WORD = InData_MsgDgst[5];
            RSIP.REG_002CH.WORD = InData_MsgDgst[6];
            RSIP.REG_002CH.WORD = InData_MsgDgst[7];
            RSIP.REG_0014H.WORD = 0x000000c7U;
            RSIP.REG_009CH.WORD = 0x800100c0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_KeyIndex[0];
            RSIP.REG_0024H.WORD = 0x00000000U;
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x000000f0U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x524c5e45U, 0x98ee6feeU, 0x9e1f792aU, 0x986f7835U);
            r_rsip_func043();
            r_rsip_func074();
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x000000f0U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x635739fcU, 0xea9bc791U, 0xe33c1936U, 0x7913fec5U);
            r_rsip_func044();
            RSIP.REG_0014H.WORD = 0x000007c1U;
            RSIP.REG_00D4H.WORD = 0x40000100U;
            RSIP.REG_00D0H.WORD = 0xf7009d07U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_KeyIndex[1];
            RSIP.REG_002CH.WORD = InData_KeyIndex[2];
            RSIP.REG_002CH.WORD = InData_KeyIndex[3];
            RSIP.REG_002CH.WORD = InData_KeyIndex[4];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_KeyIndex[5];
            RSIP.REG_002CH.WORD = InData_KeyIndex[6];
            RSIP.REG_002CH.WORD = InData_KeyIndex[7];
            RSIP.REG_002CH.WORD = InData_KeyIndex[8];
            RSIP.REG_00B0H.WORD = 0x0000141eU;
            RSIP.REG_0000H.WORD = 0x00c10021U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_0014H.WORD = 0x000003c1U;
            RSIP.REG_00D4H.WORD = 0x40000000U;
            RSIP.REG_00D0H.WORD = 0x07008d05U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_KeyIndex[9];
            RSIP.REG_002CH.WORD = InData_KeyIndex[10];
            RSIP.REG_002CH.WORD = InData_KeyIndex[11];
            RSIP.REG_002CH.WORD = InData_KeyIndex[12];
            RSIP.REG_00D0H.WORD = 0x9c100005U;
            RSIP.REG_0000H.WORD = 0x00410011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0x27cfad37U, 0xfca1381dU, 0x871d04fcU, 0x5e35f806U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0xbc24e908U, 0x0f70bb52U, 0x631fafccU, 0x73658d5cU);
                RSIP.REG_006CH.WORD = 0x00000040U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0020H.BIT.B12)
                {
                    /* waiting */
                }
                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                RSIP.REG_00B4H.WORD = 0x005a001eU;
                RSIP.REG_00B8H.WORD = 0x0019000aU;
                RSIP.REG_00A4H.WORD = 0x04040002U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B4H.WORD = 0x00280019U;
                RSIP.REG_00B8H.WORD = 0x001e000aU;
                RSIP.REG_00A4H.WORD = 0x04040002U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B4H.WORD = 0x001e0014U;
                RSIP.REG_00B8H.WORD = 0x0019000aU;
                RSIP.REG_00A4H.WORD = 0x04040005U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_00B4H.WORD = 0x0019000fU;
                RSIP.REG_00B8H.WORD = 0x001e000aU;
                RSIP.REG_00A4H.WORD = 0x04040002U;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
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
                RSIP.REG_00B4H.WORD = 0x000f001eU;
                RSIP.REG_00B8H.WORD = 0x00140000U;
                RSIP.REG_00A4H.WORD = 0x0404000aU;
                RSIP.REG_00A0H.WORD = 0x20010001U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_00A8H.BIT.B0)
                {
                    /* waiting */
                }
                RSIP.REG_00ACH.WORD = 0x00000001U;
                RSIP.REG_0040H.WORD = 0x00210000U;
                r_rsip_func100(0x3a4e10e1U, 0xffbfb278U, 0xfd0a7e5bU, 0x68478703U);
                RSIP.REG_0040H.WORD = 0x00400000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                if (1U == (RSIP.REG_0040H.BIT.B22))
                {
                    r_rsip_func102(0xcab598f5U, 0xf015e6f4U, 0xfb43ca20U, 0xb2d0ecc9U);
                    RSIP.REG_006CH.WORD = 0x00000040U;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0020H.BIT.B12)
                    {
                        /* waiting */
                    }
                    return RSIP_RET_FAIL;
                }
                else
                {
                    r_rsip_func100(0xcd00a4fdU, 0x44bd347dU, 0xd8906151U, 0x05476f25U);
                    RSIP.REG_00B0H.WORD = 0x00001828U;
                    RSIP.REG_0008H.WORD = 0x00006022U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0008H.BIT.B30)
                    {
                        /* waiting */
                    }
                    OutData_Signature[0] = RSIP.REG_002CH.WORD;
                    OutData_Signature[1] = RSIP.REG_002CH.WORD;
                    OutData_Signature[2] = RSIP.REG_002CH.WORD;
                    OutData_Signature[3] = RSIP.REG_002CH.WORD;
                    OutData_Signature[4] = RSIP.REG_002CH.WORD;
                    OutData_Signature[5] = RSIP.REG_002CH.WORD;
                    OutData_Signature[6] = RSIP.REG_002CH.WORD;
                    OutData_Signature[7] = RSIP.REG_002CH.WORD;
                    r_rsip_func100(0x25f9d547U, 0x4f8a0d2fU, 0x22f4f4e2U, 0x22a744dcU);
                    RSIP.REG_00B0H.WORD = 0x0000181eU;
                    RSIP.REG_0008H.WORD = 0x00006022U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0008H.BIT.B30)
                    {
                        /* waiting */
                    }
                    OutData_Signature[8] = RSIP.REG_002CH.WORD;
                    OutData_Signature[9] = RSIP.REG_002CH.WORD;
                    OutData_Signature[10] = RSIP.REG_002CH.WORD;
                    OutData_Signature[11] = RSIP.REG_002CH.WORD;
                    OutData_Signature[12] = RSIP.REG_002CH.WORD;
                    OutData_Signature[13] = RSIP.REG_002CH.WORD;
                    OutData_Signature[14] = RSIP.REG_002CH.WORD;
                    OutData_Signature[15] = RSIP.REG_002CH.WORD;
                    r_rsip_func102(0x4048dcd7U, 0x579d7e75U, 0x15f52448U, 0x14fdd03cU);
                    RSIP.REG_006CH.WORD = 0x00000040U;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0020H.BIT.B12)
                    {
                        /* waiting */
                    }
                    return RSIP_RET_PASS;
                }
            }
        }
    }
}
