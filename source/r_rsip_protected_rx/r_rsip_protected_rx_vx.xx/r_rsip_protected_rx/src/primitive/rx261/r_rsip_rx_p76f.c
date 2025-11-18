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

rsip_ret_t r_rsip_p76f(const uint32_t InData_Cmd[], const uint32_t InData_MAC[], const uint32_t InData_length[], uint32_t OutData_MAC[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_00F4H.WORD = 0x00000100U;
    RSIP.REG_00F4H.WORD = 0x00000020U;
    RSIP.REG_00B0H.WORD = 0x00001404U;
    RSIP.REG_0000H.WORD = 0x00c50021U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_00F4H.WORD = 0x00000010U;
    RSIP.REG_0014H.WORD = 0x000007a4U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x6a09e667U);
    RSIP.REG_002CH.WORD = bswap_32big(0xbb67ae85U);
    RSIP.REG_002CH.WORD = bswap_32big(0x3c6ef372U);
    RSIP.REG_002CH.WORD = bswap_32big(0xa54ff53aU);
    RSIP.REG_002CH.WORD = bswap_32big(0x510e527fU);
    RSIP.REG_002CH.WORD = bswap_32big(0x9b05688cU);
    RSIP.REG_002CH.WORD = bswap_32big(0x1f83d9abU);
    RSIP.REG_002CH.WORD = bswap_32big(0x5be0cd19U);
    RSIP.REG_00F4H.WORD = 0x00000011U;
    r_rsip_func002();
    RSIP.REG_00B0H.WORD = 0x00001804U;
    RSIP.REG_0000H.WORD = 0x01430021U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0014H.WORD = 0x000000a4U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x80000000U);
    RSIP.REG_0000H.WORD = 0x01400015U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0014H.WORD = 0x000001a4U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_002CH.WORD = bswap_32big(0x00000300U);
    /* WAIT_LOOP */
    while (0U != RSIP.REG_00F8H.BIT.B2)
    {
        /* waiting */
    }
    RSIP.REG_00F4H.WORD = 0x00000100U;
    RSIP.REG_0040H.WORD = 0x00001600U;
    RSIP.REG_0014H.WORD = 0x000000c7U;
    RSIP.REG_009CH.WORD = 0x80010000U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_Cmd[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0094H.WORD = 0x38000c00U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00260000U;
    r_rsip_func100(0xaefb41cbU, 0x4db68d37U, 0x0463b6c9U, 0x6a007732U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func100(0x595d4404U, 0xfe107884U, 0xc436247fU, 0x984052dbU);
        RSIP.REG_00F4H.WORD = 0x00000020U;
        RSIP.REG_0008H.WORD = 0x00004022U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_MAC[0] = RSIP.REG_002CH.WORD;
        OutData_MAC[1] = RSIP.REG_002CH.WORD;
        OutData_MAC[2] = RSIP.REG_002CH.WORD;
        OutData_MAC[3] = RSIP.REG_002CH.WORD;
        OutData_MAC[4] = RSIP.REG_002CH.WORD;
        OutData_MAC[5] = RSIP.REG_002CH.WORD;
        OutData_MAC[6] = RSIP.REG_002CH.WORD;
        OutData_MAC[7] = RSIP.REG_002CH.WORD;
        r_rsip_func102(0xd19bf991U, 0xd3aa34b9U, 0xd680e1e3U, 0xc50be1bfU);
        RSIP.REG_006CH.WORD = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0020H.BIT.B12)
        {
            /* waiting */
        }
        return RSIP_RET_PASS;
    }
    else
    {
        RSIP.REG_0014H.WORD = 0x000000c7U;
        RSIP.REG_009CH.WORD = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_length[0];
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0094H.WORD = 0x3420a820U;
        RSIP.REG_0094H.WORD = 0x00000004U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00260000U;
        RSIP.REG_0094H.WORD = 0x3420a820U;
        RSIP.REG_0094H.WORD = 0x00000021U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00A60000U;
        r_rsip_func100(0xbeaee575U, 0x985bdc7eU, 0xa6c9eef3U, 0x81fa254dU);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0xa8007676U, 0xa6961e02U, 0xd38954abU, 0x3636ad5fU);
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
            RSIP.REG_0094H.WORD = 0x00000842U;
            RSIP.REG_009CH.WORD = 0x80880002U;
            RSIP.REG_00F4H.WORD = 0x00000020U;
            RSIP.REG_0000H.WORD = 0x03450021U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_0094H.WORD = 0x00000800U;
            for (iLoop = 0; iLoop < 32; iLoop = iLoop + 1)
            {
                RSIP.REG_0094H.WORD = 0x3c002841U;
                RSIP.REG_0094H.WORD = 0x12003c02U;
                RSIP.REG_0094H.WORD = 0x00002c40U;
            }
            RSIP.REG_00D0H.WORD = 0x08000045U;
            RSIP.REG_0094H.WORD = 0x00000842U;
            RSIP.REG_009CH.WORD = 0x81880002U;
            RSIP.REG_0000H.WORD = 0x00490011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_00D0H.WORD = 0x08000055U;
            RSIP.REG_0000H.WORD = 0x00490011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_0014H.WORD = 0x000007c1U;
            RSIP.REG_00D0H.WORD = 0x9c000005U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_MAC[0];
            RSIP.REG_002CH.WORD = InData_MAC[1];
            RSIP.REG_002CH.WORD = InData_MAC[2];
            RSIP.REG_002CH.WORD = InData_MAC[3];
            RSIP.REG_00D0H.WORD = 0x9c100005U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_MAC[4];
            RSIP.REG_002CH.WORD = InData_MAC[5];
            RSIP.REG_002CH.WORD = InData_MAC[6];
            RSIP.REG_002CH.WORD = InData_MAC[7];
            r_rsip_func100(0x7977a950U, 0xa4fbe30cU, 0x326d5347U, 0xc4d9f8f7U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0x000a2543U, 0xbbae4a48U, 0xf5e102e8U, 0x3562a418U);
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
                r_rsip_func102(0x06255719U, 0xf23e1cf5U, 0x6804ee7eU, 0xa2eb7037U);
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
