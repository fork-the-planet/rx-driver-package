/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes256GcmEncryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           uint32_t OutData_Text[],
                                           uint32_t OutData_DataT[])
{
    uint32_t iLoop = 0U;

    WR1_PROG(REG_0014H, 0x000001c7U);
    WR1_PROG(REG_009CH, 0x80020040U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_TextLen[0]);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_TextLen[1]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x0000b400U);
    WR1_PROG(REG_0094H, 0x0000007FU);
    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0xFFFFFF00U);
    WR1_PROG(REG_0094H, 0x0c002823U);
    WR1_PROG(REG_0094H, 0x04a02802U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    HW_SCE_p_func100(0x132090c7U, 0xcb358daeU, 0x2b3c6790U, 0x036e09cfU);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0xb98abfbfU, 0x8d955d4cU, 0xd2a9a8c7U, 0x3d677d0aU);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003403U);
        WR1_PROG(REG_0094H, 0x00036800U);

        WR1_PROG(REG_0094H, 0x08008c00U);
        WR1_PROG(REG_0094H, 0x0000000fU);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        HW_SCE_p_func100(0x3e78ffadU, 0xd1e65a47U, 0xb32019e3U, 0x52a4ab82U);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func100(0x818d8201U, 0x1303bad8U, 0x5f02cc55U, 0x440bff9dU);
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40000020U);
            WR1_PROG(REG_00D0H, 0x07008d05U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_Text[0]);

            WR1_PROG(REG_0094H, 0x00000821U);
            WR1_PROG(REG_009CH, 0x80840001U);
            WR1_PROG(REG_0000H, 0x03410011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0094H, 0x00000884U);
            for (iLoop = 0U; iLoop < 16U; iLoop++)
            {
                WR1_PROG(REG_0094H, 0x3c002820U);
                WR1_PROG(REG_0094H, 0x12003c81U);
                WR1_PROG(REG_0094H, 0x00002c20U);
            }

            WR1_PROG(REG_00D4H, 0x00008000U);
            WR1_PROG(REG_00D0H, 0x0e128455U);
            WR1_PROG(REG_0094H, 0x00000821U);
            WR1_PROG(REG_009CH, 0x81840001U);
            WR1_PROG(REG_0000H, 0x00490011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WAIT_STS(REG_00C8H, 6, 0);
            WR1_PROG(REG_0040H, 0x00000400U);
            WR1_PROG(REG_0040H, 0x00000500U);

            WR1_PROG(REG_009CH, 0x81840001U);
            WR1_PROG(REG_0008H, 0x00005012U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[0]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[1]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[2]);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_Text[3]);

            HW_SCE_p_func101(0xa31fdeb8U, 0x38384c51U, 0xdce3e653U, 0xe14efc95U);
        }

        HW_SCE_p_func100(0xd6f53be8U, 0x2904d6c2U, 0x95b7e3f2U, 0xc0d1318bU);
        WR1_PROG(REG_0014H, 0x000001c1U);
        WR1_PROG(REG_00D4H, 0x00008000U);
        WR1_PROG(REG_00D0H, 0x0e128455U);
        WAIT_STS(REG_0014H, 31, 1);
        WR2_ADDR(REG_002CH, &InData_DataALen[0]);

        WR1_PROG(REG_009CH, 0x81020040U);
        WR1_PROG(REG_0000H, 0x00490009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D0H, 0x08000045U);
        WR1_PROG(REG_0094H, 0x0000b420U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x81840001U);
        WR1_PROG(REG_0000H, 0x00490011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000000a1U);
        WR1_PROG(REG_00D0H, 0x0c100104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_00D4H, 0x40000020U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0008H, 0x00001012U);
        WAIT_STS(REG_0008H, 30, 1);
        RD4_ADDR(REG_002CH, &OutData_DataT[0]);

        HW_SCE_p_func102(0xf21fb59fU, 0x96d1d0a4U, 0xe9616b5eU, 0x560157adU);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_SUCCESS;
    }
}
