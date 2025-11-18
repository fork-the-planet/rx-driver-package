/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes256CmacFinalSub (const uint32_t InData_Cmd[],
                                     const uint32_t InData_Text[],
                                     const uint32_t InData_DataT[],
                                     const uint32_t InData_DataTLen[],
                                     uint32_t OutData_DataT[])
{
    uint32_t iLoop = 0U;

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000002U))
    {
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x4a008104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0x4241ff7eU, 0xe87d2756U, 0xa0568626U, 0x228de019U);
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x5a008104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        HW_SCE_p_func101(0xddb22cc1U, 0x0a841604U, 0xba6d0854U, 0xa71d252fU);
    }

    WR1_PROG(REG_00D0H, 0x0c000045U);
    WR1_PROG(REG_0000H, 0x00410011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    if ((InData_Cmd[0] == 0x00000000U) || (InData_Cmd[0] == 0x00000001U))
    {
        HW_SCE_p_func100(0x41a41340U, 0x0b43061fU, 0xad434ad4U, 0xbf4b10d9U);
        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0e008505U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_Text[0]);

        WR1_PROG(REG_0008H, 0x00001012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_DataT[0]);

        HW_SCE_p_func102(0x88b883a7U, 0x59b6221eU, 0x31547bd9U, 0xe2a41d37U);
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

        HW_SCE_p_func100(0x49d4ebfeU, 0x82fbaa44U, 0x1137782fU, 0xfdbc933cU);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func102(0x027698eaU, 0x790bb9f3U, 0x2edeeb41U, 0x1fa0e383U);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000000U);
            WR1_PROG(REG_00D0H, 0x0e008505U);
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

            HW_SCE_p_func100(0x004e7c74U, 0xe6601c8fU, 0x2099aeeaU, 0x30aaed9dU);
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                HW_SCE_p_func102(0x5b6965c2U, 0x66448187U, 0x97241c92U, 0x37e6269cU);
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
            }
            else
            {
                HW_SCE_p_func102(0x7283c31bU, 0x893a0d41U, 0x95c3fc51U, 0xa61eeeb0U);
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
