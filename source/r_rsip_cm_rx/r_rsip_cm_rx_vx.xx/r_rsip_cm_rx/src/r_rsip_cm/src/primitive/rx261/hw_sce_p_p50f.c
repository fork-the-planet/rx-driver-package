/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes256EncryptDecryptFinalSub (void)
{
    if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
    {
        HW_SCE_p_func101(0x3aaa9bd4U, 0xb757a38cU, 0x9135f59dU, 0xb688ef9eU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
    {
        HW_SCE_p_func101(0x5cc9d15eU, 0x1909aa7aU, 0xb2ca13cfU, 0x2145b5baU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
    {
        HW_SCE_p_func101(0xf6d53d90U, 0x0b79dc2cU, 0xdb95966fU, 0x4dda2098U);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
    {
        HW_SCE_p_func101(0x2a11cc87U, 0xcc906a91U, 0xfb09cc48U, 0x604e365cU);
    }
    else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
    {
        HW_SCE_p_func101(0x8f7de187U, 0x73b6d5ebU, 0x84e85193U, 0x0acb193fU);
    }

    HW_SCE_p_func102(0xd3dcf824U, 0xe8470483U, 0xa5008275U, 0xb1b0c6faU);
    WR1_PROG(REG_006CH, 0x00000040U);
    WAIT_STS(REG_0020H, 12, 0);

    return FSP_SUCCESS;
}
