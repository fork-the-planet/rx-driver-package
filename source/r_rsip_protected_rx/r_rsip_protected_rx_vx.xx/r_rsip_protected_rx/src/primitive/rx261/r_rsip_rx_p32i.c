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

rsip_ret_t r_rsip_p32i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
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
    RSIP.REG_0070H.WORD = 0x00320001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
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
    RSIP.REG_002CH.WORD = bswap_32big(0x00003201U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x2a89281fU, 0x40371f5fU, 0x8f63423fU, 0xdb7ea7b0U);
    r_rsip_func043();
    RSIP.REG_0094H.WORD = 0x0000b4c0U;
    RSIP.REG_0094H.WORD = 0x00000005U;
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000032U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x921dc7f4U, 0x9d4c26b2U, 0x8a6a98dcU, 0xb82cb2b5U);
    r_rsip_func044();
    RSIP.REG_0014H.WORD = 0x000003c1U;
    RSIP.REG_00D4H.WORD = 0x40000000U;
    RSIP.REG_00D0H.WORD = 0xf7009d05U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_KeyIndex[1];
    RSIP.REG_002CH.WORD = InData_KeyIndex[2];
    RSIP.REG_002CH.WORD = InData_KeyIndex[3];
    RSIP.REG_002CH.WORD = InData_KeyIndex[4];
    RSIP.REG_00B0H.WORD = 0x00000401U;
    RSIP.REG_0000H.WORD = 0x00c10009U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_00B0H.WORD = 0x00000402U;
    RSIP.REG_0000H.WORD = 0x00c10009U;
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
    RSIP.REG_002CH.WORD = InData_KeyIndex[5];
    RSIP.REG_002CH.WORD = InData_KeyIndex[6];
    RSIP.REG_002CH.WORD = InData_KeyIndex[7];
    RSIP.REG_002CH.WORD = InData_KeyIndex[8];
    RSIP.REG_00D0H.WORD = 0x9c100005U;
    RSIP.REG_0000H.WORD = 0x00410011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    r_rsip_func100(0xf635cfa8U, 0xe7f9ab87U, 0x087a8a2bU, 0xd85731f6U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0x86044468U, 0x8cda35f8U, 0x06d1040cU, 0x7a988a9cU);
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
        RSIP.REG_0094H.WORD = 0x00000800U;
        RSIP.REG_0014H.WORD = 0x000000c7U;
        RSIP.REG_009CH.WORD = 0x80010080U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_IVType[0];
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0094H.WORD = 0x38000c84U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00260000U;
        r_rsip_func100(0xa46a5e14U, 0xdfde3d21U, 0xfee0dd37U, 0x308c306bU);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            RSIP.REG_0014H.WORD = 0x000003c7U;
            RSIP.REG_0094H.WORD = 0x0000b420U;
            RSIP.REG_0094H.WORD = 0x00000010U;
            RSIP.REG_009CH.WORD = 0x80840001U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_IV[0];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_IV[1];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_IV[2];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_IV[3];
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0xc3825c39U, 0xb2e46c16U, 0x55417adbU, 0xa4b8ec04U);
        }
        else
        {
            RSIP.REG_0014H.WORD = 0x000000c7U;
            RSIP.REG_009CH.WORD = 0x800100c0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_IV[0];
            RSIP.REG_0024H.WORD = 0x00000000U;
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00003202U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0xe7fd7934U, 0xa9fb5d2eU, 0x0ed0bc80U, 0x516165e3U);
            r_rsip_func043();
            RSIP.REG_0094H.WORD = 0x0000b4c0U;
            RSIP.REG_0094H.WORD = 0x0199e556U;
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000032U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x94e18642U, 0x6213eb80U, 0xf58051feU, 0xb96ae05fU);
            r_rsip_func044();
            RSIP.REG_0014H.WORD = 0x000003c1U;
            RSIP.REG_00D4H.WORD = 0x40000000U;
            RSIP.REG_00D0H.WORD = 0xf7009d05U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_IV[1];
            RSIP.REG_002CH.WORD = InData_IV[2];
            RSIP.REG_002CH.WORD = InData_IV[3];
            RSIP.REG_002CH.WORD = InData_IV[4];
            RSIP.REG_0094H.WORD = 0x0000b420U;
            RSIP.REG_0094H.WORD = 0x00000010U;
            RSIP.REG_009CH.WORD = 0x80840001U;
            RSIP.REG_0000H.WORD = 0x03410011U;
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
            RSIP.REG_002CH.WORD = InData_IV[5];
            RSIP.REG_002CH.WORD = InData_IV[6];
            RSIP.REG_002CH.WORD = InData_IV[7];
            RSIP.REG_002CH.WORD = InData_IV[8];
            RSIP.REG_00D0H.WORD = 0x9c100005U;
            RSIP.REG_0000H.WORD = 0x00410011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0xcdfc49b6U, 0x4687bf88U, 0x4a0d36c0U, 0x633cb008U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                RSIP.REG_0094H.WORD = 0x00002c00U;
                r_rsip_func101(0x0ba33eb7U, 0x04b6ae68U, 0xe72e7ea7U, 0x6a7b23b0U);
            }
            r_rsip_func101(0x6eee1d15U, 0x19b4fef9U, 0xaa408312U, 0x7524e570U);
        }
        RSIP.REG_0094H.WORD = 0x38000c00U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00A60000U;
        r_rsip_func100(0xe6f570ceU, 0x52c6cfc9U, 0xaea8b4cfU, 0xa97d952bU);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0x9bc9de29U, 0x70aba2adU, 0xbea265acU, 0xdc9ccd27U);
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
            r_rsip_func100(0x16c04939U, 0x9ecf76e7U, 0x486a495cU, 0x0774c276U);
            RSIP.REG_00D0H.WORD = 0x08000085U;
            RSIP.REG_00B0H.WORD = 0x00000801U;
            RSIP.REG_0000H.WORD = 0x00430009U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_00B0H.WORD = 0x00000802U;
            RSIP.REG_0000H.WORD = 0x00430009U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0xadd83956U, 0xcd82afdaU, 0x5ddf3fa7U, 0x33f09b6eU);
            RSIP.REG_0014H.WORD = 0x000000a1U;
            RSIP.REG_00D0H.WORD = 0x08000054U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            RSIP.REG_0014H.WORD = 0x000000a1U;
            RSIP.REG_00D0H.WORD = 0x0a0000a4U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            r_rsip_func101(0x8765cc0bU, 0xb6a88784U, 0xec42fc10U, 0x58ff579eU);
            return RSIP_RET_PASS;
        }
    }
}
