/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_GhashSub (const uint32_t InData_HV[],
                           const uint32_t InData_IV[],
                           const uint32_t InData_Text[],
                           uint32_t OutData_DataT[],
                           const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_0068H, 0x00000016U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00210001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    HW_SCE_p_func100(0xe9495273U, 0x775eabc9U, 0xa20b91a2U, 0xb305910fU);
    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D0H, 0x080000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_HV[0]);
    WR1_PROG(REG_0014H, 0x000003c1U);
    WR1_PROG(REG_00D0H, 0x08000055U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_IV[0]);

    WR1_PROG(REG_0014H, 0x00020061U);
    WR1_PROG(REG_00D4H, 0x00008000U);
    WR1_PROG(REG_00D0H, 0x0e128456U);

    for (iLoop = 0U; iLoop < MAX_CNT; iLoop = iLoop + 4U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[iLoop]);
    }

    HW_SCE_p_func205();

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c100104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

    HW_SCE_p_func100(0xde03dc63U, 0xe3429580U, 0x58fa471aU, 0xe6cf8b00U);
    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_DataT[0]);

    HW_SCE_p_func102(0x36eddaa7U, 0x6329edefU, 0xda7fcdf9U, 0x7ef92013U);
    WR1_PROG(REG_0068H, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return FSP_SUCCESS;
}
