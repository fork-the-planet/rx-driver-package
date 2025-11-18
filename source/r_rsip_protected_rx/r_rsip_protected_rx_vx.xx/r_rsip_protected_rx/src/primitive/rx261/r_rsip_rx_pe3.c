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

rsip_ret_t r_rsip_pe3(const uint32_t InData_EncSecret[], uint32_t OutData_EncMsg[])
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
    RSIP.REG_0070H.WORD = 0x00e30001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x000000e3U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x82e82451U, 0xbb4bee72U, 0x43b2163fU, 0x88526cc1U);
    r_rsip_func407(InData_EncSecret);
    r_rsip_func100(0x9d3607b8U, 0x84725be6U, 0xa62c7a9cU, 0xcbb4e54dU);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0xa56d3bddU, 0xbe321ca7U, 0x4e81047aU, 0x5dd5dfe4U);
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
        r_rsip_func100(0x36d9df4dU, 0xe4740308U, 0xfceb81b7U, 0xba1f3ee3U);
        r_rsip_func103();
        RSIP.REG_0014H.WORD = 0x000000a1U;
        RSIP.REG_00D0H.WORD = 0x0c200104U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
        RSIP.REG_009CH.WORD = 0x80010000U;
        RSIP.REG_0000H.WORD = 0x03410005U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        RSIP.REG_0000H.WORD = 0x0001000dU;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        RSIP.REG_0094H.WORD = 0x000034c0U;
        RSIP.REG_0014H.WORD = 0x000000a7U;
        RSIP.REG_009CH.WORD = 0x800100e0U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x000000e3U);
        RSIP.REG_0024H.WORD = 0x00000000U;
        r_rsip_func101(0xe0a13455U, 0x23fb2c11U, 0x1b64a6ecU, 0x885eb0caU);
        r_rsip_func043();
        RSIP.REG_0094H.WORD = 0x0000b4c0U;
        RSIP.REG_0094H.WORD = 0x01799093U;
        RSIP.REG_0014H.WORD = 0x000000a7U;
        RSIP.REG_009CH.WORD = 0x800100e0U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x000000e3U);
        RSIP.REG_0024H.WORD = 0x00000000U;
        r_rsip_func101(0xda19e6deU, 0x066916ddU, 0x1a744355U, 0xef51467bU);
        r_rsip_func044();
        r_rsip_func100(0xb07b7c5eU, 0x3f305a1fU, 0x20be56a3U, 0x98f5a979U);
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
        RSIP.REG_00B0H.WORD = 0x00001804U;
        RSIP.REG_00D4H.WORD = 0x40000100U;
        RSIP.REG_00D0H.WORD = 0xe7008d07U;
        RSIP.REG_0000H.WORD = 0x00430021U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        RSIP.REG_0008H.WORD = 0x00001022U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_EncMsg[1] = RSIP.REG_002CH.WORD;
        OutData_EncMsg[2] = RSIP.REG_002CH.WORD;
        OutData_EncMsg[3] = RSIP.REG_002CH.WORD;
        OutData_EncMsg[4] = RSIP.REG_002CH.WORD;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_EncMsg[5] = RSIP.REG_002CH.WORD;
        OutData_EncMsg[6] = RSIP.REG_002CH.WORD;
        OutData_EncMsg[7] = RSIP.REG_002CH.WORD;
        OutData_EncMsg[8] = RSIP.REG_002CH.WORD;
        r_rsip_func100(0x4c357951U, 0x258e5d5fU, 0x1c490d71U, 0xec15a186U);
        RSIP.REG_0014H.WORD = 0x000000a1U;
        RSIP.REG_00D0H.WORD = 0x0c000104U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
        RSIP.REG_00D4H.WORD = 0x40000000U;
        RSIP.REG_00D0H.WORD = 0x09108105U;
        RSIP.REG_0000H.WORD = 0x00410011U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        RSIP.REG_0008H.WORD = 0x00001012U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_EncMsg[9] = RSIP.REG_002CH.WORD;
        OutData_EncMsg[10] = RSIP.REG_002CH.WORD;
        OutData_EncMsg[11] = RSIP.REG_002CH.WORD;
        OutData_EncMsg[12] = RSIP.REG_002CH.WORD;
        r_rsip_func100(0x71f556a0U, 0xc52e08b6U, 0x060531b3U, 0xb6621792U);
        RSIP.REG_009CH.WORD = 0x81010000U;
        RSIP.REG_0008H.WORD = 0x00005006U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_EncMsg[0] = RSIP.REG_002CH.WORD;
        r_rsip_func102(0xbec3392eU, 0xea20ee24U, 0x2758b6cdU, 0x62ff6a60U);
        RSIP.REG_006CH.WORD = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0020H.BIT.B12)
        {
            /* waiting */
        }
        return RSIP_RET_PASS;
    }
}
