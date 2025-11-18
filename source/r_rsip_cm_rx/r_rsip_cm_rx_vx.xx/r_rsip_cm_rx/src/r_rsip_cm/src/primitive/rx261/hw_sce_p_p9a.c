/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Ecc256ScalarMultiplicationSub (const uint32_t InData_CurveType[],
                                                const uint32_t InData_KeyMode[],
                                                const uint32_t InData_KeyIndex[],
                                                const uint32_t InData_Key[],
                                                const uint32_t InData_PubKey[],
                                                const uint32_t InData_DomainParam[],
                                                uint32_t OutData_R[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x009a0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_00A0H, 0x20010000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_0094H, 0x2000b400U);
    WR1_PROG(REG_0094H, 0x00000002U);

    WR1_PROG(REG_0094H, 0x00003420U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyMode[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    HW_SCE_p_func100(0x99caff9dU, 0x1cfa0e0aU, 0x86995324U, 0x6f17b170U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);
    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x800100c0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, InData_KeyIndex[0]);
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x0000009aU));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0x074cd7ecU, 0x5580a0dbU, 0xc11a565cU, 0x9f7a77baU);
        HW_SCE_p_func043();

        HW_SCE_p_func074();

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x0000009aU));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0xf306cc35U, 0xb856927fU, 0x2af99731U, 0x28ac0f37U);
        HW_SCE_p_func044();

        WR1_PROG(REG_0014H, 0x000007c1U);
        WR1_PROG(REG_00D4H, 0x40000100U);
        WR1_PROG(REG_00D0H, 0xf7009d07U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_00B0H, 0x00001432U);
        WR1_PROG(REG_0000H, 0x00c10021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[9]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func101(0x61cd2cfdU, 0x62fa4ba9U, 0x3086e002U, 0x73891bfeU);
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000007c5U);
        WR1_PROG(REG_00B0H, 0x00001432U);
        WAIT_STS(REG_0014H, 31, 1);
        WR8_ADDR(REG_002CH, &InData_Key[0]);

        HW_SCE_p_func101(0x84509629U, 0x1a40216dU, 0x3bd813c1U, 0x631c0166U);
    }

    HW_SCE_p_func100(0xe90facb5U, 0x662c2c90U, 0x2c0579d2U, 0xe01e7ed8U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0xd494f9b4U, 0x840b4c4bU, 0xaaa607eaU, 0x8c79c128U);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        WR1_PROG(REG_0094H, 0x00003401U);

        HW_SCE_p_func070(InData_DomainParam);

        WR1_PROG(REG_00B8H, 0x00000005U);

        WR1_PROG(REG_00A4H, 0x04040010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0014H, 0x00000fc5U);
        WR1_PROG(REG_00B0H, 0x0000140fU);
        WAIT_STS(REG_0014H, 31, 1);
        WR8_ADDR(REG_002CH, &InData_PubKey[0]);

        WR1_PROG(REG_00B0H, 0x00001414U);
        WAIT_STS(REG_0014H, 31, 1);
        WR8_ADDR(REG_002CH, &InData_PubKey[8]);

        HW_SCE_p_func008();

        HW_SCE_p_func100(0x2df3d52cU, 0x83c71ebcU, 0xe1b3ae1aU, 0x7f9bfb03U);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func102(0x9b2ff321U, 0x9752ecb8U, 0x6f50f421U, 0xc0c48acfU);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x0000009aU));
            WR1_PROG(REG_0024H, 0x00000000U);

            HW_SCE_p_func101(0x32a30642U, 0x5dd9f8b1U, 0x2976de43U, 0x48514974U);
            HW_SCE_p_func088();

            HW_SCE_p_func100(0x6fd00b2fU, 0x525609acU, 0x2a08c3e8U, 0xf743252bU);
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                HW_SCE_p_func102(0xe19bbd21U, 0x4c31177fU, 0x3a1a0382U, 0xc2050938U);
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0xc389fa7aU, 0x96ce43cfU, 0x13171f0fU, 0xdaba2bf3U);
                WR1_PROG(REG_00B0H, 0x00001828U);
                WR1_PROG(REG_0008H, 0x00006022U);
                WAIT_STS(REG_0008H, 30, 1);
                RD8_ADDR(REG_002CH, &OutData_R[0]);

                HW_SCE_p_func100(0x9d589826U, 0x39eb0539U, 0x47bc48d5U, 0x20108220U);
                WR1_PROG(REG_00B0H, 0x0000182dU);
                WR1_PROG(REG_0008H, 0x00006022U);
                WAIT_STS(REG_0008H, 30, 1);
                RD8_ADDR(REG_002CH, &OutData_R[8]);

                HW_SCE_p_func102(0x9ebcb773U, 0xc68e1d7aU, 0xc13338d6U, 0xd927af1aU);
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
}
