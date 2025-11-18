/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_SoftwareResetSub (void)
{
    WR1_PROG(REG_000CH, 0x00000000U);
    WR1_PROG(REG_0024H, 0x00000000U);
    WR1_PROG(REG_0024H, 0x00000000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
