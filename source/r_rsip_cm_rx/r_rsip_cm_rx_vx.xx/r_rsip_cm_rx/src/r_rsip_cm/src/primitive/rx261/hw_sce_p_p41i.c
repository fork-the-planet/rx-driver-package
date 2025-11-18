/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes128CmacInitSub (const uint32_t InData_KeyMode[],
                                    const uint32_t InData_KeyIndex[],
                                    const uint32_t InData_Key[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00410001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyMode[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    HW_SCE_p_func100(0xeaa6fc88U, 0x69899ac4U, 0x5e2d016bU, 0xfd7b6650U);
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
        WR1_PROG(REG_002CH, change_endian_long(0x00000041U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0x53536e56U, 0xf6699fa7U, 0x4cab328bU, 0xb3dac55cU);
        HW_SCE_p_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x00000005U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000041U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0xf43d33deU, 0x7dd90a24U, 0xc025f84dU, 0x0e8ffb56U);
        HW_SCE_p_func044();

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0xf7009d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);

        WR1_PROG(REG_00B0H, 0x00000401U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_00B0H, 0x00000402U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func101(0x8ad7d9b8U, 0xa5efa945U, 0xea7ca54cU, 0x2defd65cU);
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000003c5U);
        WR1_PROG(REG_00B0H, 0x00000401U);
        WAIT_STS(REG_0014H, 31, 1);
        WR2_ADDR(REG_002CH, &InData_Key[0]);
        WR1_PROG(REG_00B0H, 0x00000402U);
        WAIT_STS(REG_0014H, 31, 1);
        WR2_ADDR(REG_002CH, &InData_Key[2]);

        HW_SCE_p_func101(0x4fc73278U, 0x9f905708U, 0xa2f678f8U, 0x43ef6d41U);
    }

    HW_SCE_p_func100(0xb947b22cU, 0x5eaa1a29U, 0x4dd827aaU, 0x3711a4e1U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0xfac0580cU, 0x704ea397U, 0x473a8325U, 0x20355fe6U);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0xe0ab58baU, 0x1d11765fU, 0xce7c630eU, 0x5178f750U);
        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_00B0H, 0x00000801U);
        WR1_PROG(REG_0000H, 0x00430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000802U);
        WR1_PROG(REG_0000H, 0x00430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x6d295084U, 0xf81a07e0U, 0x5ba1d90eU, 0xa0b7ebddU);

        return FSP_SUCCESS;
    }
}
