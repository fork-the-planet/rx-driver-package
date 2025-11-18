/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_Aes256CmacUpdateSub (const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x00020061U);
    WR1_PROG(REG_00D4H, 0x40000000U);
    WR1_PROG(REG_00D0H, 0x0e008406U);

    for (iLoop = 0U; iLoop < MAX_CNT; iLoop = iLoop + 4U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[iLoop]);
    }

    HW_SCE_p_func205();

    HW_SCE_p_func101(0xf5aaa719U, 0xdb4857f2U, 0x490f4bb1U, 0xec4cb2bcU);
}
