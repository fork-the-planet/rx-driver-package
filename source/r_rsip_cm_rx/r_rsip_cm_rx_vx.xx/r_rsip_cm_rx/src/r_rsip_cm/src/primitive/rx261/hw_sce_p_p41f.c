/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes128CmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     uint32_t OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x4a000104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0xc477f7cdU, 0x0493bd80U, 0x0bf0f1e9U, 0x3e697e76U);
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x5a000104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x0ed37513U, 0xcaf8fbf0U, 0x911e3e06U, 0xe205b27aU);
    }

    WR1_PROG(REG_00D0H, 0x0c000045U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        HW_SCE_p_func100(0x597ab607U, 0xd3c8bdb1U, 0x959d42a8U, 0xd3540bceU);
        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D0H, 0x0e000505U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[0]);

        WR1_PROG(REG_0008H, 0x00001012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_DataT[0]);

        HW_SCE_p_func102(0x12a17691U, 0x0dd382e7U, 0x55921f28U, 0x64ce74f8U);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_SUCCESS;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010040U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_DataTLen[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x3420a840U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        WR1_PROG(REG_0094H, 0x0000b460U);
        WR1_PROG(REG_0094H, 0x00000080U);
        WR1_PROG(REG_0094H, 0x34202862U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        HW_SCE_p_func100(0xf19dbdfeU, 0xe95402c3U, 0x52cc9bbdU, 0xe27af844U);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func102(0xd38ab08aU, 0xfd230304U, 0x39eeadc3U, 0x50cdc1d2U);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x0e000505U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_Text[0]);

            WR1_PROG(REG_0094H, 0x00000821U);
            WR1_PROG(REG_009CH, 0x80840001U);
            WR1_PROG(REG_0000H, 0x03410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x000034e2U);
            WR1_PROG(REG_0094H, 0x000568e7U);
            WR1_PROG(REG_0094H, 0x00026ce7U);

            WR1_PROG(REG_0094H, 0x00003827U);

            WR1_PROG(REG_0094H, 0x0000b4c0U);
            WR1_PROG(REG_0094H, 0x00000020U);
            WR1_PROG(REG_0094H, 0x00003402U);
            WR1_PROG(REG_0094H, 0x00008c00U);
            WR1_PROG(REG_0094H, 0x0000001fU);
            WR1_PROG(REG_0094H, 0x000028c0U);
            WR1_PROG(REG_0094H, 0x00008cc0U);
            WR1_PROG(REG_0094H, 0x0000001fU);

            WR1_PROG(REG_0094H, 0x00004406U);

            WR1_PROG(REG_0094H, 0x00007421U);
            WR1_PROG(REG_0094H, 0x00007821U);

            WR1_PROG(REG_0094H, 0x00003c27U);

            WR1_PROG(REG_0094H, 0x000034c2U);
            WR1_PROG(REG_0094H, 0x0000a4c0U);
            WR1_PROG(REG_0094H, 0x0000001fU);
            WR1_PROG(REG_0094H, 0x000568c6U);

            WR1_PROG(REG_0094H, 0x000034e6U);
            WR1_PROG(REG_0094H, 0x00026ce7U);

            WR1_PROG(REG_0094H, 0x00000821U);

            for (iLoop = 0U; iLoop < 4; iLoop++)
            {
                WR1_PROG(REG_0094H, 0x3420a8e0U);
                WR1_PROG(REG_0094H, 0x0000000dU);
                WR1_PROG(REG_0094H, 0x10003c27U);

                WR1_PROG(REG_0094H, 0x1000a4e0U);
                WR1_PROG(REG_0094H, 0x00000004U);
            }

            WR1_PROG(REG_00D0H, 0x08000045U);
            WR1_PROG(REG_009CH, 0x81840001U);
            WR1_PROG(REG_0000H, 0x00490011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x9c000005U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_DataT[0]);

            HW_SCE_p_func100(0x64cd2ce2U, 0x86d778f4U, 0x8afe394bU, 0x2669e78bU);
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                HW_SCE_p_func102(0x06a0bad4U, 0x04f2b507U, 0xfdde17dfU, 0x40f2d35bU);
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
            }
            else
            {
                HW_SCE_p_func102(0xd66f435eU, 0xac3f6ab1U, 0x7bf1abb4U, 0xa7685eb9U);
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
