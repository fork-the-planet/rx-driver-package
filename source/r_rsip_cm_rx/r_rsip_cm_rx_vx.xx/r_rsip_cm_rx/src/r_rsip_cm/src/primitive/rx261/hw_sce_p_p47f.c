/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func101(0x1cd9a17eU, 0xf39159ecU, 0x91aab7baU, 0x619b6ebaU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func101(0x150caed4U, 0x9d345048U, 0xb3b06709U, 0x130bb29eU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func101(0x86b2591cU, 0x79a466eeU, 0xd0822e3eU, 0xcde3700bU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func101(0x676b6c52U, 0xf9e5e733U, 0x538d7be5U, 0xe8bf7bd2U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func101(0x2e2fb651U, 0x0d51249aU, 0xefa69cdbU, 0x7cb592c2U);
    }

    HW_SCE_p_func102(0x0de195a6U, 0xb7dfa51fU, 0xa537ecedU, 0x739df64aU);
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return FSP_SUCCESS;
}
