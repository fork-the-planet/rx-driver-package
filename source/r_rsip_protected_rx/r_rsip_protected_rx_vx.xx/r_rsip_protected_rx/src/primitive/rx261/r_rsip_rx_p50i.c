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

rsip_ret_t r_rsip_p50i(const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
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
    RSIP.REG_0070H.WORD = 0x00500001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    RSIP.REG_0014H.WORD = 0x000000c7U;
    RSIP.REG_009CH.WORD = 0x80010080U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_Cmd[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0094H.WORD = 0x3000a880U;
    RSIP.REG_0094H.WORD = 0x00000004U;
    RSIP.REG_0094H.WORD = 0x00010020U;
    RSIP.REG_0094H.WORD = 0x0000b480U;
    RSIP.REG_0094H.WORD = 0x00000004U;
    RSIP.REG_0094H.WORD = 0x00000080U;
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
    RSIP.REG_002CH.WORD = bswap_32big(0x00000050U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x089c5887U, 0x486f3e61U, 0x79feb25aU, 0x99eb3dacU);
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
    RSIP.REG_002CH.WORD = bswap_32big(0x00000050U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x3552058cU, 0xec3ea681U, 0xafa58d80U, 0x162a9bbbU);
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
    r_rsip_func100(0xe0503836U, 0x0cd214a1U, 0x3080db10U, 0x8de5fcd4U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0xf9ff4dadU, 0xc2360c68U, 0xaf642f8bU, 0x3819aa34U);
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
        r_rsip_func100(0x10618b9eU, 0x668e5625U, 0x92337eceU, 0x65a5aa1eU);
        RSIP.REG_0094H.WORD = 0x00007c04U;
        RSIP.REG_0040H.WORD = 0x00600000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (0x00000000U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            r_rsip_func100(0xd33e94c6U, 0x0bf4fbb2U, 0x062c9500U, 0xc294452aU);
            RSIP.REG_00D0H.WORD = 0x08000085U;
            RSIP.REG_00B0H.WORD = 0x00001804U;
            RSIP.REG_0000H.WORD = 0x00430011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0x70bf7df3U, 0x92c42bf2U, 0x33c9e439U, 0xc1aeb438U);
            RSIP.REG_00D0H.WORD = 0x08000095U;
            RSIP.REG_0000H.WORD = 0x00430011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func101(0x293ed637U, 0xbce1b646U, 0xef3b6b5bU, 0xc27935fcU);
        }
        else if (0x00000001U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            r_rsip_func100(0x11c0befcU, 0x532009b0U, 0x597e7347U, 0x09020407U);
            RSIP.REG_00D0H.WORD = 0x08000085U;
            RSIP.REG_00B0H.WORD = 0x00001804U;
            RSIP.REG_0000H.WORD = 0x00430011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0x784eaa1eU, 0xce10ab09U, 0x27459243U, 0xfddde2c8U);
            RSIP.REG_00D0H.WORD = 0x08000095U;
            RSIP.REG_0000H.WORD = 0x00430011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func101(0xe8c514e1U, 0x8385a97eU, 0x6ea3598fU, 0x4c599425U);
        }
        else if (0x00000002U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00005001U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x10cc9b54U, 0x2888e8ceU, 0x9a2879b4U, 0x49ec4beaU);
            r_rsip_func510(InData_IVType, InData_IV);
            RSIP.REG_0094H.WORD = 0x38000c00U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00A60000U;
            r_rsip_func100(0x5ce195c8U, 0xe14ce81bU, 0x0a68b422U, 0x4e05c12eU);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0xa4e5786cU, 0x5d31fd4dU, 0x8143f054U, 0x3dec88e3U);
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
                RSIP.REG_00D0H.WORD = 0x08000045U;
                RSIP.REG_0094H.WORD = 0x0000b420U;
                RSIP.REG_0094H.WORD = 0x00000010U;
                RSIP.REG_009CH.WORD = 0x81840001U;
                RSIP.REG_0000H.WORD = 0x00490011U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                r_rsip_func100(0x7937ff1fU, 0x5fa2b5e9U, 0x7f335a5eU, 0xa482bef2U);
                RSIP.REG_00D0H.WORD = 0x08000085U;
                RSIP.REG_00B0H.WORD = 0x00001804U;
                RSIP.REG_0000H.WORD = 0x00430011U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                r_rsip_func100(0x39a9b3cfU, 0xdc78a23dU, 0x0ffe9508U, 0xb1ebbab9U);
                RSIP.REG_00D0H.WORD = 0x08000095U;
                RSIP.REG_0000H.WORD = 0x00430011U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                r_rsip_func101(0xfa2efe2aU, 0x70c4849fU, 0xd525ef09U, 0x279ffbccU);
            }
        }
        else if (0x00000003U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00005002U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x6d3f1c60U, 0xce24a069U, 0xb4f12b68U, 0x9ab726eaU);
            r_rsip_func510(InData_IVType, InData_IV);
            RSIP.REG_0094H.WORD = 0x38000c00U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00A60000U;
            r_rsip_func100(0x07e97392U, 0x69d5b25bU, 0xc7920cffU, 0x023f18d2U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0xdef5ff92U, 0x77256ebeU, 0x86925bc4U, 0x1c0740f2U);
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
                RSIP.REG_00D0H.WORD = 0x08000045U;
                RSIP.REG_0094H.WORD = 0x0000b420U;
                RSIP.REG_0094H.WORD = 0x00000010U;
                RSIP.REG_009CH.WORD = 0x81840001U;
                RSIP.REG_0000H.WORD = 0x00490011U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                r_rsip_func100(0x520ffd86U, 0xb2b63a87U, 0x15177fdfU, 0x4da561caU);
                RSIP.REG_00D0H.WORD = 0x08000085U;
                RSIP.REG_00B0H.WORD = 0x00001804U;
                RSIP.REG_0000H.WORD = 0x00430011U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                r_rsip_func100(0x4558708eU, 0x0d33f1eaU, 0xf99c840dU, 0x1a21570cU);
                RSIP.REG_00D0H.WORD = 0x08000095U;
                RSIP.REG_0000H.WORD = 0x00430011U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                r_rsip_func101(0x7bebf1b9U, 0x95b6c56dU, 0x4bd9c351U, 0x195256c0U);
            }
        }
        else if (0x00000004U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            r_rsip_func100(0x645562f8U, 0x8836054aU, 0x790e8faaU, 0x9e99b583U);
            RSIP.REG_0014H.WORD = 0x000003c1U;
            RSIP.REG_00D0H.WORD = 0x08000045U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_IV[0];
            RSIP.REG_002CH.WORD = InData_IV[1];
            RSIP.REG_002CH.WORD = InData_IV[2];
            RSIP.REG_002CH.WORD = InData_IV[3];
            RSIP.REG_00D0H.WORD = 0x08000085U;
            RSIP.REG_00B0H.WORD = 0x00001804U;
            RSIP.REG_0000H.WORD = 0x00430011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0x4ca966d6U, 0x704f4761U, 0x6aa1de68U, 0xee6309ccU);
            RSIP.REG_00D0H.WORD = 0x08000095U;
            RSIP.REG_0000H.WORD = 0x00430011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func101(0x11f925bfU, 0x9e98f6edU, 0xad3f97bdU, 0x453c64d4U);
        }
        else
        {
        }
        return RSIP_RET_PASS;
    }
}
