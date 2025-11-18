/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_Aes128CmacUpdateSub (const uint32_t InData_Text[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x00020061U);
    WR1_PROG(REG_00D0H, 0x0e000406U);

    for (iLoop = 0U; iLoop < MAX_CNT; iLoop = iLoop + 4U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[iLoop]);
    }

    HW_SCE_p_func205();

    HW_SCE_p_func101(0xa8617a5dU, 0xf2c6dbceU, 0x93816ad0U, 0xf983430aU);
}
