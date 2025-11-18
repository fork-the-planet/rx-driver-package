/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes256CmacInitSub (const uint32_t InData_KeyMode[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Key[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00440001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyMode[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    HW_SCE_p_func100(0xf63c5f5cU, 0xe49c0703U, 0x17f81cc0U, 0x762dcf32U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);
    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_KeyIndex[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000044U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0x9e7f6b89U, 0x5f8eeea7U, 0xce4dc5daU, 0x2078590fU);
        HW_SCE_p_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x00000007U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000044U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0xbc8d0d51U, 0xee9de65bU, 0xfdd5d547U, 0x313b84d1U);
        HW_SCE_p_func044();

        WR1_PROG(REG_0014H, 0x000007c1U);
        WR1_PROG(REG_00D4H, 0x40000100U);
        WR1_PROG(REG_00D0H, 0xf7009d07U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_00B0H, 0x00001404U);
        WR1_PROG(REG_0000H, 0x00c10021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func101(0xa986ab28U, 0x05e42baeU, 0x10ccf847U, 0x3d59420dU);
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000007c5U);
        WR1_PROG(REG_00B0H, 0x00001404U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Key[0]);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Key[4]);

        HW_SCE_p_func101(0xd5358f3aU, 0x619418edU, 0x5d86ed96U, 0x4beb6d11U);
    }

    HW_SCE_p_func100(0x2dcedd25U, 0x92f5a3f3U, 0x90bca635U, 0x53c815d5U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0x1b1b1ff4U, 0x12b1381dU, 0x7b9432ffU, 0x88c86012U);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x7e6c2bcfU, 0x574ef0c8U, 0x7127e38dU, 0x2c224b83U);
        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_00B0H, 0x00001804U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func100(0x042592bdU, 0x80a7205eU, 0x78c118edU, 0xcd78e4a4U);
        WR1_PROG(REG_00D0H, 0x08000095U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0xf798046eU, 0xe1cd7b9eU, 0xde9a7c8eU, 0x353c2d9dU);

        return FSP_SUCCESS;
    }
}
