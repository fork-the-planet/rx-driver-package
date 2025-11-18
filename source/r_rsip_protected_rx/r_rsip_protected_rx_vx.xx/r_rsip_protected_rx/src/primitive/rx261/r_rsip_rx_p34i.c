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

rsip_ret_t r_rsip_p34i(const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
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
    RSIP.REG_0070H.WORD = 0x00340001U;
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
    RSIP.REG_002CH.WORD = bswap_32big(0x00000034U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x4d6f1a61U, 0x2606545fU, 0xa7eaefcdU, 0xf7d8a233U);
    r_rsip_func043();
    RSIP.REG_0094H.WORD = 0x0000b4c0U;
    RSIP.REG_0094H.WORD = 0x00000007U;
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000034U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x5d2d752dU, 0x88cfb101U, 0x1088e4ebU, 0xde8f1672U);
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
    RSIP.REG_00B0H.WORD = 0x00001404U;
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
    r_rsip_func100(0x462a75a1U, 0xc30f2142U, 0x287dac88U, 0x0b581a97U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0xc8c35523U, 0xb824bb0fU, 0x8adaf83fU, 0xf1562515U);
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
        RSIP.REG_0014H.WORD = 0x000000a7U;
        RSIP.REG_009CH.WORD = 0x800100e0U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x00000034U);
        RSIP.REG_0024H.WORD = 0x00000000U;
        r_rsip_func101(0x365f9ff0U, 0x1a98827eU, 0x75935a0bU, 0xa3cf1f37U);
        r_rsip_func510(InData_IVType, InData_IV);
        RSIP.REG_0094H.WORD = 0x38000c00U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00A60000U;
        r_rsip_func100(0x174018c5U, 0x905cbe53U, 0x8d68da1aU, 0xadd39f9aU);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0xa5b4bbc8U, 0x0e16d051U, 0x086c8e95U, 0x15e64c2bU);
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
            r_rsip_func100(0x8e78d79bU, 0xea09a13eU, 0xa46d6502U, 0xc07e92a3U);
            RSIP.REG_00D0H.WORD = 0x08000085U;
            RSIP.REG_00B0H.WORD = 0x00001804U;
            RSIP.REG_0000H.WORD = 0x00430011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0xbe6f0c1bU, 0xbb047288U, 0x070b5832U, 0x16eb54deU);
            RSIP.REG_00D0H.WORD = 0x08000095U;
            RSIP.REG_0000H.WORD = 0x00430011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0x8712f7d9U, 0x77c64db8U, 0xa8cf6e62U, 0xb0963b32U);
            RSIP.REG_0014H.WORD = 0x000000a1U;
            RSIP.REG_00D0H.WORD = 0x08000054U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            RSIP.REG_0014H.WORD = 0x000000a1U;
            RSIP.REG_00D4H.WORD = 0x40000000U;
            RSIP.REG_00D0H.WORD = 0x0a0080a4U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            r_rsip_func101(0x942f1845U, 0xa5006d49U, 0xc5d51ae3U, 0xb68c387eU);
            return RSIP_RET_PASS;
        }
    }
}
