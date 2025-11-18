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

rsip_ret_t r_rsip_pdcf(const uint32_t InData_Cmd[], const uint32_t InData_MAC[], const uint32_t InData_length[], uint32_t OutData_MAC[])
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
    RSIP.REG_002CH.WORD = bswap_32big(0xc1059ed8U);
    RSIP.REG_002CH.WORD = bswap_32big(0x367cd507U);
    RSIP.REG_002CH.WORD = bswap_32big(0x3070dd17U);
    RSIP.REG_002CH.WORD = bswap_32big(0xf70e5939U);
    RSIP.REG_002CH.WORD = bswap_32big(0xffc00b31U);
    RSIP.REG_002CH.WORD = bswap_32big(0x68581511U);
    RSIP.REG_002CH.WORD = bswap_32big(0x64f98fa7U);
    RSIP.REG_002CH.WORD = bswap_32big(0xbefa4fa4U);
    RSIP.REG_00F4H.WORD = 0x00000011U;
    r_rsip_func002();
    RSIP.REG_00B0H.WORD = 0x00001804U;
    RSIP.REG_0000H.WORD = 0x0143001dU;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0000H.WORD = 0x00030005U;
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
    RSIP.REG_0000H.WORD = 0x01400019U;
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
    RSIP.REG_002CH.WORD = bswap_32big(0x000002E0U);
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
    r_rsip_func100(0x1c339fe4U, 0xeacde36aU, 0x40d8c6e9U, 0x804a8db8U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func100(0x4ee25af6U, 0xd0bf8ac6U, 0x5e6466d7U, 0x8b464109U);
        RSIP.REG_00F4H.WORD = 0x00000020U;
        RSIP.REG_0008H.WORD = 0x0000401eU;
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
        RSIP.REG_0000H.WORD = 0x00050005U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        r_rsip_func102(0xafe8a978U, 0x242153c0U, 0x19a4269eU, 0x91e8310fU);
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
        RSIP.REG_0094H.WORD = 0x0000001dU;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00A60000U;
        r_rsip_func100(0x0bc8e9e2U, 0x1d2c1632U, 0x9b40fe00U, 0xe0e6a813U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0x1bc1f6e2U, 0x333f08baU, 0xf560fadbU, 0x2a8ffb09U);
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
            RSIP.REG_009CH.WORD = 0x80870002U;
            RSIP.REG_00F4H.WORD = 0x00000020U;
            RSIP.REG_0000H.WORD = 0x0345001dU;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_0000H.WORD = 0x00050005U;
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
            RSIP.REG_0014H.WORD = 0x000006c1U;
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
            RSIP.REG_0014H.WORD = 0x000000a1U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            r_rsip_func100(0x621b65c1U, 0x8ad8b301U, 0x12459e3eU, 0x281210b5U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0x3827c0aaU, 0x1d7baafdU, 0x2dbae6b5U, 0xe3e59a9bU);
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
                r_rsip_func102(0x915d163eU, 0xa80e4fa3U, 0xcf6cadf9U, 0xbbb69e22U);
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
