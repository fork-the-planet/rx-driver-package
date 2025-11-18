/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_OemKeyIndexValidationSub (const uint32_t InData_Cmd[], const uint32_t InData_KeyIndex[])
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00700001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    HW_SCE_p_func049(InData_Cmd);

    WR1_PROG(REG_0094H, 0x0000b440U);
    WR1_PROG(REG_0094H, 0x2C8003A0U);

    WR1_PROG(REG_0094H, 0x000034a4U);

    WR1_PROG(REG_0094H, 0x38008880U);
    WR1_PROG(REG_0094H, 0x00000023U);
    WR1_PROG(REG_0094H, 0x1000b480U);
    WR1_PROG(REG_0094H, 0x00000005U);

    HW_SCE_p_func056();

    HW_SCE_p_func100(0xd0af8bd0U, 0x60496bb7U, 0x3c19871dU, 0x4190e4daU);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0x0d1a6e48U, 0x106294f2U, 0x7088d17eU, 0x3407f5b3U);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003485U);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_KeyIndex[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000070U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0xc3364ea6U, 0x115fe37aU, 0x427d0aaaU, 0x099bec32U);
        HW_SCE_p_func043();

        WR1_PROG(REG_0094H, 0x000034c4U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000070U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0xa3d6e86eU, 0xa87df3ceU, 0xcec04841U, 0x0974fb19U);
        HW_SCE_p_func044();

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0xf7009c06U);

        for (iLoop = 0U; iLoop < (KEY_INDEX_SIZE - 5); iLoop = iLoop + 4U)
        {
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_KeyIndex[1 + iLoop]);
        }

        HW_SCE_p_func205();

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[1 + iLoop]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func100(0x92979d48U, 0xd9815e71U, 0x10ce7114U, 0xa2623084U);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func102(0x71983069U, 0xf4b6e19fU, 0xba5c7f85U, 0xb5daeedaU);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
        }
        else
        {
            HW_SCE_p_func102(0x377bab71U, 0xab136e9aU, 0x19ff52b0U, 0x21abeba3U);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
