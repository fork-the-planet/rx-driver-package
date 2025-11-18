/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

void HW_SCE_Aes256GcmEncryptUpdateAADSub (const uint32_t InData_DataA[], const uint32_t MAX_CNT)
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x00020061U);
    WR1_PROG(REG_00D4H, 0x00008000U);
    WR1_PROG(REG_00D0H, 0x0e128456U);

    for (iLoop = 0U; iLoop < MAX_CNT; iLoop = iLoop + 4U)
    {
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_DataA[iLoop]);
    }

    HW_SCE_p_func205();

    HW_SCE_p_func101(0xede84400U, 0xaa741f70U, 0x5b8f5cf2U, 0x6bb578fcU);
}
