/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_ShaGenerateMessageDigestSub (const uint32_t InData_InitVal[],
                                              const uint32_t InData_PaddedMsg[],
                                              uint32_t OutData_MsgDigest[],
                                              const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_0068H, 0x00000016U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00720001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00F4H, 0x00000010U);

    WAIT_STS(REG_00F8H, 0, 1);

    WR1_PROG(REG_0014H, 0x000007c4U);
    WAIT_STS(REG_0014H, 31, 1);
    WR8_ADDR(REG_002CH, &InData_InitVal[0]);

    WR1_PROG(REG_00F4H, 0x00000011U);

    WAIT_STS(REG_00F8H, 0, 1);

    WR1_PROG(REG_0014H, 0x00000064U);
    for (iLoop = 0U; iLoop < MAX_CNT; iLoop = iLoop + 16U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR16_ADDR(REG_002CH, &InData_PaddedMsg[iLoop]);
    }

    WAIT_STS(REG_00F8H, 2, 0);

    WR1_PROG(REG_0014H, 0x00000000U);

    WR1_PROG(REG_00F4H, 0x00000100U);

    WR1_PROG(REG_00F4H, 0x00000020U);

    WAIT_STS(REG_00F8H, 1, 1);

    HW_SCE_p_func100(0x7af98838U, 0xf1e9f5feU, 0xb5668247U, 0x756c6419U);
    WR1_PROG(REG_0008H, 0x00004022U);
    WAIT_STS(REG_0008H, 30, 1);
    RD8_ADDR(REG_002CH, &OutData_MsgDigest[0]);

    HW_SCE_p_func102(0x6ca18432U, 0x10c727f4U, 0xefb2823fU, 0x51fcd4a2U);
    WR1_PROG(REG_0068H, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return FSP_SUCCESS;
}
