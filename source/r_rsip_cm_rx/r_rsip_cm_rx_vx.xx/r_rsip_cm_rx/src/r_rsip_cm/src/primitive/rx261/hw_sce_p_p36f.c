/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes256GcmDecryptFinalSub (const uint32_t InData_Text[],
                                           const uint32_t InData_TextLen[],
                                           const uint32_t InData_DataALen[],
                                           const uint32_t InData_DataT[],
                                           const uint32_t InData_DataTLen[],
                                           uint32_t OutData_Text[])
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

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x800100a0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_DataTLen[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x380088a0U);
    WR1_PROG(REG_0094H, 0x00000000U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    WR1_PROG(REG_0094H, 0x0000b420U);
    WR1_PROG(REG_0094H, 0x00000010U);
    WR1_PROG(REG_0094H, 0x34202825U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    HW_SCE_p_func100(0x450785e7U, 0x8ef9b3f6U, 0x9ae51d2cU, 0xae9b0b8aU);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0xe9433243U, 0xaa89d1b4U, 0xd8eeacdaU, 0x09b8fafdU);
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

        HW_SCE_p_func100(0xbd1da77bU, 0xb6e544f4U, 0x9d63f1a0U, 0xd586dd83U);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func100(0x1490bae5U, 0x26d7cd28U, 0x31034614U, 0xe8da2ba2U);
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D4H, 0x40008020U);
            WR1_PROG(REG_00D0H, 0x20008d05U);
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

            WR1_PROG(REG_0094H, 0x00000821U);
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

            HW_SCE_p_func101(0x0dbe4926U, 0x19adf3d5U, 0x455289ceU, 0x28e35867U);
        }

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

        WR1_PROG(REG_0094H, 0x00000821U);
        WR1_PROG(REG_009CH, 0x80840001U);
        WR1_PROG(REG_0000H, 0x03410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0094H, 0x00000884U);
        for (iLoop = 0U; iLoop < 16U; iLoop++)
        {
            WR1_PROG(REG_0094H, 0x3c002825U);
            WR1_PROG(REG_0094H, 0x12003c81U);
            WR1_PROG(REG_0094H, 0x00002c20U);
        }

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D0H, 0x08000055U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_DataT[0]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0094H, 0x00000821U);
        WR1_PROG(REG_009CH, 0x81840001U);
        WR1_PROG(REG_0000H, 0x00490011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func100(0xba3801b9U, 0xf8abcac1U, 0x7f28461aU, 0x617d3c95U);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func102(0xb9b1d64bU, 0x95afdd9fU, 0x354fac11U, 0xcf354bccU);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_AUTHENTICATION;
        }
        else
        {
            HW_SCE_p_func102(0x7aa100d8U, 0x58659cd6U, 0xc3316b16U, 0x9e4480d1U);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
