/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_SelfCheck1Sub (void)
{
    WR1_PROG(REG_008CH, 0x00000001U);

    WAIT_STS(REG_008CH, 1, 0);

    if (RD1_MASK(REG_0090H, 0xFFFFFFFFU) != 0x0009F7C3U)
    {
        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_000CH, 0x38c60eedU);
        WR1_PROG(REG_0024H, 0x00000000U);
        WR1_PROG(REG_0024H, 0x00000000U);
        WR1_PROG(REG_0048H, 0x00000000U);

        WR1_PROG(REG_0008H, 0x00000001U);
        WR1_PROG(REG_0010H, 0x00001601U);
        WR1_PROG(REG_0024H, 0x00000000U);
        WR1_PROG(REG_0024H, 0x00000000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
        {
            return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
        }

        WR1_PROG(REG_00C0H, 0x00000001U);
        WR1_PROG(REG_00E0H, 0x00000001U);
        WR1_PROG(REG_00F0H, 0x00000001U);

        WR1_PROG(REG_0070H, 0x00818001U);
        WR1_PROG(REG_0078H, 0x00000d00U);

        WR1_PROG(REG_00C4H, 0x00008004U);

        WR1_PROG(REG_0014H, 0x000003a1U);
        HW_SCE_p_func101(change_endian_long(0x0bba5221U), change_endian_long(0x25146762U),
                         change_endian_long(0x6e96356aU), change_endian_long(0x33468a16U));
        WR1_PROG(REG_00C4H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000003a1U);
        WR1_PROG(REG_00D0H, 0x0a0700f5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_PROG(REG_002CH, 0x4f663c12U, 0xd7a41a5dU, 0x7d9d5f07U, 0x3863ca31U);

        HW_SCE_p_func101(change_endian_long(0x28f72f0bU), change_endian_long(0xbe71c42bU),
                         change_endian_long(0xd7d0be43U), change_endian_long(0xb1ba802cU));

        HW_SCE_p_func100(change_endian_long(0x0ab49e02U), change_endian_long(0xb1441f77U),
                         change_endian_long(0x0ed9b912U), change_endian_long(0xee5665fbU));

        WR1_PROG(REG_0008H, 0x00020000U);

        if (CHCK_STS(REG_0020H, 13, 0))
        {
            WR1_PROG(REG_006CH, 0x00000020U);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_0038H, 0x000000F1U);

            WR1_PROG(REG_0078H, 0x00000220U);

            HW_SCE_p_func102(change_endian_long(0xd03e8458U), change_endian_long(0xda950502U),
                             change_endian_long(0xc7128abdU), change_endian_long(0x9ced6237U));
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
