/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_p_func101 (uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4)
{
    WR1_PROG(REG_00D0H, 0x0a0701e5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR4_PROG(REG_002CH, change_endian_long(ARG1), change_endian_long(ARG2), change_endian_long(
                 ARG3), change_endian_long(ARG4));
    WAIT_STS(REG_00C8H, 17, 0);
}
