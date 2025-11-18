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

rsip_ret_t r_rsip_peei(const uint32_t InData_CurveType[], const uint32_t InData_KeyIndex[], const uint32_t InData_MsgDgst[], const uint32_t InData_Signature[], const uint32_t InData_DomainParam[])
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
    RSIP.REG_0070H.WORD = 0x00ee0001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    RSIP.REG_00A0H.WORD = 0x00010000U;
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
    RSIP.REG_0094H.WORD = 0x00000002U;
    RSIP.REG_0094H.WORD = 0x2000b400U;
    RSIP.REG_0094H.WORD = 0x00000001U;
    RSIP.REG_00A0H.WORD = 0x20010000U;
    RSIP.REG_0014H.WORD = 0x00000fc5U;
    RSIP.REG_00B0H.WORD = 0x00001469U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_Signature[0];
    RSIP.REG_002CH.WORD = InData_Signature[1];
    RSIP.REG_002CH.WORD = InData_Signature[2];
    RSIP.REG_002CH.WORD = InData_Signature[3];
    RSIP.REG_002CH.WORD = InData_Signature[4];
    RSIP.REG_002CH.WORD = InData_Signature[5];
    RSIP.REG_002CH.WORD = InData_Signature[6];
    RSIP.REG_002CH.WORD = InData_Signature[7];
    RSIP.REG_00B0H.WORD = 0x0000146eU;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_Signature[8];
    RSIP.REG_002CH.WORD = InData_Signature[9];
    RSIP.REG_002CH.WORD = InData_Signature[10];
    RSIP.REG_002CH.WORD = InData_Signature[11];
    RSIP.REG_002CH.WORD = InData_Signature[12];
    RSIP.REG_002CH.WORD = InData_Signature[13];
    RSIP.REG_002CH.WORD = InData_Signature[14];
    RSIP.REG_002CH.WORD = InData_Signature[15];
    RSIP.REG_0014H.WORD = 0x000007c5U;
    RSIP.REG_00B0H.WORD = 0x0000147eU;
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
    RSIP.REG_0094H.WORD = 0x00003420U;
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
    RSIP.REG_002CH.WORD = bswap_32big(0x0000ee01U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0xee85e099U, 0x9dd1838fU, 0xc965cbd1U, 0x2682f71fU);
    r_rsip_func043();
    r_rsip_func075();
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x0000ee01U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x4983ba23U, 0x65962f9eU, 0x1c03fddeU, 0x09aa6689U);
    r_rsip_func044();
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x08000044U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x08000054U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_0014H.WORD = 0x00000fc1U;
    RSIP.REG_00D4H.WORD = 0x40000300U;
    RSIP.REG_00D0H.WORD = 0xe8008107U;
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
    RSIP.REG_00B0H.WORD = 0x0000347aU;
    RSIP.REG_0000H.WORD = 0x00c10021U;
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
    RSIP.REG_002CH.WORD = InData_KeyIndex[9];
    RSIP.REG_002CH.WORD = InData_KeyIndex[10];
    RSIP.REG_002CH.WORD = InData_KeyIndex[11];
    RSIP.REG_002CH.WORD = InData_KeyIndex[12];
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_KeyIndex[13];
    RSIP.REG_002CH.WORD = InData_KeyIndex[14];
    RSIP.REG_002CH.WORD = InData_KeyIndex[15];
    RSIP.REG_002CH.WORD = InData_KeyIndex[16];
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
    RSIP.REG_002CH.WORD = InData_KeyIndex[17];
    RSIP.REG_002CH.WORD = InData_KeyIndex[18];
    RSIP.REG_002CH.WORD = InData_KeyIndex[19];
    RSIP.REG_002CH.WORD = InData_KeyIndex[20];
    RSIP.REG_00D0H.WORD = 0x9c100005U;
    RSIP.REG_0000H.WORD = 0x00410011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    r_rsip_func100(0x3293d624U, 0x3eb46f0fU, 0x3b60ffb7U, 0x5ebf3d08U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0xe052d9c3U, 0x5dd8f657U, 0xe9613096U, 0x0d1503ccU);
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
        RSIP.REG_002CH.WORD = bswap_32big(0x000000eeU);
        RSIP.REG_0024H.WORD = 0x00000000U;
        r_rsip_func101(0xd3000d71U, 0x34b4e938U, 0x2bb26dbaU, 0x0453cc0aU);
        r_rsip_func073(InData_DomainParam);
        r_rsip_func100(0x9a598332U, 0x0ad847a2U, 0x1235eaeaU, 0x881e3eb0U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0xd7342e68U, 0xf4dd15c4U, 0xa78654eeU, 0x8f818d3fU);
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
            r_rsip_func101(0x630de691U, 0x26433936U, 0x70c025a7U, 0x28e38074U);
            return RSIP_RET_PASS;
        }
    }
}
