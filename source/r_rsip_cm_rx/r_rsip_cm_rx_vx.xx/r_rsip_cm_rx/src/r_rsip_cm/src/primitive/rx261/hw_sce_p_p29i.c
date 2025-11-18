/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes128GcmEncryptInitSub (const uint32_t InData_KeyMode[],
                                          const uint32_t InData_KeyIndex[],
                                          const uint32_t InData_Key[],
                                          const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00290001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyMode[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    HW_SCE_p_func100(0xc53d4538U, 0x39eb9e7dU, 0x046726c2U, 0x4db23172U);
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
        WR1_PROG(REG_002CH, change_endian_long(0x00000029U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0x10d8273fU, 0x17b99cd4U, 0x1b47495cU, 0x83c821f1U);
        HW_SCE_p_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x00000005U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000029U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0x6a7aa66bU, 0x92e177f5U, 0x95ff1ae2U, 0x3ef27a2aU);
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

        HW_SCE_p_func101(0x0498de7aU, 0x20d17dbaU, 0xc00c2382U, 0x43fb5fe4U);
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

        HW_SCE_p_func101(0x46362570U, 0x82079c88U, 0x0d45722aU, 0x33d26d0fU);
    }

    HW_SCE_p_func100(0x6175cbf6U, 0x1fd0ea25U, 0x6eeba15bU, 0xc6e97f12U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0xf5be1c9aU, 0x7fd0a76dU, 0x447ac342U, 0x8b1fbc12U);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x6d1a43ffU, 0x5f295359U, 0x447aab5aU, 0xcb379434U);
        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_00B0H, 0x00000801U);
        WR1_PROG(REG_0000H, 0x00430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000802U);
        WR1_PROG(REG_0000H, 0x00430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func100(0xcb41db8dU, 0xf5cf1807U, 0x68d5bf89U, 0x72bdc16aU);
        WR1_PROG(REG_0014H, 0x000003c7U);
        WR1_PROG(REG_0094H, 0x0000b420U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x80840001U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IV[0]);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IV[1]);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IV[2]);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_IV[3]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x08000054U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0a0000a4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x309b4665U, 0xe7a5fda5U, 0xc816e18bU, 0x7b839d32U);

        return FSP_SUCCESS;
    }
}
