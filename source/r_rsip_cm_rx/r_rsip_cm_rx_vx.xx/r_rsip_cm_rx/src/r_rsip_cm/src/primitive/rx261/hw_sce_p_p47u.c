/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_Aes128EncryptDecryptUpdateSub (const uint32_t InData_Text[],
                                           uint32_t OutData_Text[],
                                           const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0x72caf890U, 0x2a12ed4fU, 0xaadd8fe5U, 0x7553020dU);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x0a000106U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0x576a9b8eU, 0x9e44176cU, 0x3b1cc8a3U, 0xa22d03c0U);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x0a00010eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0x251084afU, 0x8ef85229U, 0xb9eb711fU, 0xd2b37f41U);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x0e000506U);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0x4b86c57dU, 0x388fc163U, 0x49f75d34U, 0xf4c7ac35U);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x0900090eU);
        WR1_PROG(REG_0008H, 0x000c1000U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        WR1_PROG(REG_0014H, 0x000003c1U);
        HW_SCE_p_func100(0x69d93daeU, 0xba185ff4U, 0x434603f2U, 0xc56870cbU);

        WR1_PROG(REG_0014H, 0x00020061U);
        WR1_PROG(REG_00D0H, 0x07000d06U);
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

        HW_SCE_p_func101(0xe3af2808U, 0xaf0aadebU, 0xbf08eb07U, 0x5750904eU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x3f146167U, 0xd9e3cf7eU, 0x628ae97fU, 0xdf20c462U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x7108804bU, 0x27d848acU, 0x74803e54U, 0xf35c3754U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0x5c8ddaa4U, 0xfcfd75ddU, 0x365acf28U, 0xbc50dea4U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func206();

        HW_SCE_p_func101(0xaee1fbe6U, 0x89e0ece7U, 0x6f39d52fU, 0xf061ee77U);
    }
}
