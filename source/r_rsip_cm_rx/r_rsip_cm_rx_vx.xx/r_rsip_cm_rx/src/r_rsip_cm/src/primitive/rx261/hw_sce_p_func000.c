/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_p_func000 (const uint32_t ARG1[], const uint32_t ARG2)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x00020064U);

    for (iLoop = 0U; iLoop < ARG2; iLoop = iLoop + 16U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR16_ADDR(REG_002CH, &ARG1[iLoop]);
    }

    WAIT_STS(REG_00F8H, 2, 0);

    WR1_PROG(REG_0014H, 0x00000000U);

    WR1_PROG(REG_0040H, 0x00001600U);
}
