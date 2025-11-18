/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes128CcmEncryptFinalSub (const uint32_t InData_Text[],
                                           uint32_t OutData_Text[],
                                           uint32_t OutData_MAC[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0094H, 0x00003404U);

    WR1_PROG(REG_0094H, 0x00008c00U);
    WR1_PROG(REG_0094H, 0x0000000fU);

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0x00000000U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    HW_SCE_p_func100(0x10d71b50U, 0x855faaa5U, 0xcb1c2155U, 0x32ea0a69U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D0H, 0xe7000d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[0]);

        WR1_PROG(REG_0094H, 0x00000821U);
        WR1_PROG(REG_009CH, 0x80840001U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x00000821U);

        WR1_PROG(REG_0094H, 0x000008a5U);

        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_0094H, 0x3c0028a0U);
            WR1_PROG(REG_0094H, 0x12003c25U);
            WR1_PROG(REG_0094H, 0x00002ca0U);
        }

        HW_SCE_p_func100(0x3165227cU, 0x28f6acd9U, 0xa9ebf541U, 0x7841bdbdU);
        WR1_PROG(REG_0094H, 0x00000821U);
        WR1_PROG(REG_009CH, 0x81840001U);
        WR1_PROG(REG_0008H, 0x00005012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[0]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[1]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[2]);
        WAIT_STS(REG_0008H, 30, 1);
        RD1_ADDR(REG_002CH, &OutData_Text[3]);

        HW_SCE_p_func101(0xbc0afb76U, 0x1a6db0ccU, 0x18c61d16U, 0xc6a92584U);
    }
    else
    {
        HW_SCE_p_func101(0x087963ccU, 0x439cad8dU, 0x865f97fcU, 0x14d89a00U);
    }

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

    HW_SCE_p_func100(0xefb22ad8U, 0xda97c8dcU, 0x81148bc0U, 0xae480291U);
    WR1_PROG(REG_00D0H, 0x09100105U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_MAC[0]);

    HW_SCE_p_func102(0x1c97c0aaU, 0x0c12992dU, 0x2c4b4854U, 0x6caf70f8U);
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return FSP_SUCCESS;
}
