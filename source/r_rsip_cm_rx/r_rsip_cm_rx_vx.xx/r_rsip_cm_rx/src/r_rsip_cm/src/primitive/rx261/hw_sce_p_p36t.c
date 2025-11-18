/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_Aes256GcmDecryptUpdateTransitionSub (void)
{
    WR1_PROG(REG_00D0H, 0x08000045U);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000010U);
    WR1_PROG(REG_009CH, 0x81840001U);
    WR1_PROG(REG_0000H, 0x00490011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D4H, 0x40000020U);
    WR1_PROG(REG_00D0H, 0x07008c04U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x00000000U));
}
