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

rsip_ret_t r_rsip_p47i(const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[], const uint32_t InData_IVType[], const uint32_t InData_IV[])
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
    RSIP.REG_0070H.WORD = 0x00470001U;
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
    RSIP.REG_002CH.WORD = bswap_32big(0x00000047U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x7da06dfeU, 0x6c29f852U, 0x01fc07f6U, 0x611cf98aU);
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
    RSIP.REG_002CH.WORD = bswap_32big(0x00000047U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0xb9bb82efU, 0xb3069824U, 0x43686fafU, 0x3143f568U);
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
    r_rsip_func100(0xa1f3f259U, 0x0457e44cU, 0x4885796eU, 0xcef0a059U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0xaa9aff26U, 0x36d42817U, 0xcd56c692U, 0x49319853U);
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
        r_rsip_func100(0x1d8dfd62U, 0xc20ab216U, 0xfbb3e6b5U, 0x1992223eU);
        RSIP.REG_0094H.WORD = 0x00007c04U;
        RSIP.REG_0040H.WORD = 0x00600000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (0x00000000U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            r_rsip_func100(0x33fb22d9U, 0x43ba39d6U, 0x07eb08d9U, 0x66f1f86fU);
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
            r_rsip_func101(0x2710f869U, 0x43e7127dU, 0x7d3b7f71U, 0x7863c6d2U);
        }
        else if (0x00000001U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            r_rsip_func100(0x9839dfa1U, 0x42f0175aU, 0xe7b6bb53U, 0x362e7244U);
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
            r_rsip_func101(0xfe5b3f1aU, 0x1bcefd84U, 0xf91d6b36U, 0x1665b40cU);
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
            RSIP.REG_002CH.WORD = bswap_32big(0x00004701U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x593f41dbU, 0xdee11500U, 0x2e1c93e4U, 0xeb5f31d6U);
            r_rsip_func510(InData_IVType, InData_IV);
            RSIP.REG_0094H.WORD = 0x38000c00U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00A60000U;
            r_rsip_func100(0xbf58a789U, 0x3843f53dU, 0xde882d40U, 0x2d72655cU);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0x8ca28188U, 0x068a66cbU, 0x7fc043c2U, 0x3e2d6961U);
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
                r_rsip_func100(0x9cea1addU, 0x27295506U, 0x54ffd65cU, 0x2b48c648U);
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
                r_rsip_func101(0x07892b8dU, 0xfe8db6c7U, 0x8b27f7c6U, 0x8b52b1c0U);
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
            RSIP.REG_002CH.WORD = bswap_32big(0x00004702U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0xb8787149U, 0xf6f03082U, 0xe8034e0eU, 0x1a6ad8eaU);
            r_rsip_func510(InData_IVType, InData_IV);
            RSIP.REG_0094H.WORD = 0x38000c00U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00A60000U;
            r_rsip_func100(0x1a94bfdaU, 0xd74aeadfU, 0xf054a33dU, 0x2c16c12cU);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0x619e6624U, 0xa8c1d930U, 0xd65e614eU, 0xfd5cd115U);
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
                r_rsip_func100(0x7ee4a0bdU, 0x1bcd7b61U, 0x4c05a76fU, 0x8ba970a4U);
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
                r_rsip_func101(0xd013faa1U, 0xce75efdcU, 0xd3d149c7U, 0xae033193U);
            }
        }
        else if (0x00000004U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            r_rsip_func100(0x31385888U, 0x37450cf0U, 0x0e4fe2e2U, 0xc777d8f9U);
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
            r_rsip_func101(0x3ebb8753U, 0x33c72b66U, 0x6399cef0U, 0xbd6a9f4aU);
        }
        else
        {
        }
        return RSIP_RET_PASS;
    }
}
