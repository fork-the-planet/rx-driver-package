/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_GenerateRandomNumberSub (uint32_t OutData_Text[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00200002U);
    WR1_PROG(REG_004CH, 0x00000000U);

    HW_SCE_p_func100(0xfbf572c7U, 0x3d26c201U, 0x7dead592U, 0x13bb962cU);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0x920296fcU, 0x43043d66U, 0x791311dfU, 0x90baf03fU);
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

    WR1_PROG(REG_0008H, 0x00001012U);
    WAIT_STS(REG_0008H, 30, 1);
    RD4_ADDR(REG_002CH, &OutData_Text[0]);

    HW_SCE_p_func102(0x64ca4a52U, 0x07954962U, 0x1d3cf60eU, 0x1b2afad8U);

    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return FSP_SUCCESS;
}
