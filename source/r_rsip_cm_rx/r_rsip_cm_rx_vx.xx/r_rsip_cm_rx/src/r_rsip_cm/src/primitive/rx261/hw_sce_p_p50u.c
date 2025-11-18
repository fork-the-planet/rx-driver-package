/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_Aes256EncryptDecryptUpdateSub (const uint32_t InData_Text[],
                                           uint32_t OutData_Text[],
                                           const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0x74904c22U, 0x5f2aa74dU, 0x27befa25U, 0xa7baae82U);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0a008106U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0xf4af051eU, 0xbc45970bU, 0x6793d2b9U, 0x00a8ff20U);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0a00810eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0x016be914U, 0x28e1122bU, 0xcceea67eU, 0x6e259d1bU);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0e008506U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0x0fdd2facU, 0x76990000U, 0x3016e2b1U, 0x48747f22U);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0900890eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0xeea9e2b7U, 0x781a6821U, 0xb0639404U, 0x58f85ab9U);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d06U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }

    WAIT_STS(REG_0014H, 31, 1);
    WR4_ADDR(REG_002CH, &InData_Text[0]);
    for (iLoop = 4; iLoop < MAX_CNT; iLoop = iLoop + 4U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[iLoop]);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_Text[iLoop - 4]);
    }

    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_Text[MAX_CNT - 4]);

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x2ac2946bU, 0xebc32164U, 0x92501c88U, 0xfd10387fU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xd5845b35U, 0xf599b230U, 0x3c7d97d2U, 0x9ea74c64U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x6f998cf7U, 0xb8de6fdbU, 0x77bfff1dU, 0xc09fa08dU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x02072da7U, 0xb0dd7547U, 0x508cba68U, 0x4ebea53bU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xb21afd74U, 0x524a02feU, 0x31294914U, 0x80c44f52U);
    }
}
