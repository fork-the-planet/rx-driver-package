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

rsip_ret_t r_rsip_pdci(const uint32_t InData_KeyIndex[])
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
    RSIP.REG_0070H.WORD = 0x00dc0001U;
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
    RSIP.REG_002CH.WORD = bswap_32big(0x000000dcU);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0xb237392aU, 0xfd38624fU, 0x01ca809fU, 0x07350074U);
    r_rsip_func043();
    RSIP.REG_0094H.WORD = 0x0000b4c0U;
    RSIP.REG_0094H.WORD = 0x0000001aU;
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x000000dcU);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x20d6e4a1U, 0x62c10ec3U, 0xff946880U, 0x51461df9U);
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
    r_rsip_func100(0x82ff0b65U, 0xd34e005dU, 0x14a6db2dU, 0x6ccf1802U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0xe98c7918U, 0x68227e35U, 0xf6ecaabdU, 0x50b323c4U);
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
        RSIP.REG_00F4H.WORD = 0x00000010U;
        RSIP.REG_0014H.WORD = 0x000007a4U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0xc1059ed8U);
        RSIP.REG_002CH.WORD = bswap_32big(0x367cd507U);
        RSIP.REG_002CH.WORD = bswap_32big(0x3070dd17U);
        RSIP.REG_002CH.WORD = bswap_32big(0xf70e5939U);
        RSIP.REG_002CH.WORD = bswap_32big(0xffc00b31U);
        RSIP.REG_002CH.WORD = bswap_32big(0x68581511U);
        RSIP.REG_002CH.WORD = bswap_32big(0x64f98fa7U);
        RSIP.REG_002CH.WORD = bswap_32big(0xbefa4fa4U);
        RSIP.REG_00F4H.WORD = 0x00000011U;
        r_rsip_func001();
        r_rsip_func101(0x7a898ab7U, 0xffd61f84U, 0x2bfde1cdU, 0x29bbeddcU);
        return RSIP_RET_PASS;
    }
}
