/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_p_func206 (void)
{
    WR1_PROG(REG_0008H, 0x00000000U);
    WR1_PROG(REG_0014H, 0x00000000U);
    WAIT_STS(REG_00C8H, 6, 0);
    WR1_PROG(REG_0040H, 0x00000400U);
    WR1_PROG(REG_0040H, 0x00000600U);
    WR1_PROG(REG_0040H, 0x00000500U);
    WR1_PROG(REG_00D0H, 0x00000000U);
}
