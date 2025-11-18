/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_EcdsaSignatureGenerateSub (const uint32_t InData_CurveType[],
                                            const uint32_t InData_KeyMode[],
                                            const uint32_t InData_KeyIndex[],
                                            const uint32_t InData_Key[],
                                            const uint32_t InData_MsgDgst[],
                                            const uint32_t InData_DomainParam[],
                                            uint32_t OutData_Signature[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00f00001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_CurveType[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000003U);
    WR1_PROG(REG_0094H, 0x2000b400U);
    WR1_PROG(REG_0094H, 0x00000002U);

    HW_SCE_p_func070(InData_DomainParam);

    HW_SCE_p_func100(0xcb637e7bU, 0xed317f9bU, 0xfcab126eU, 0xa08c6528U);

    WR1_PROG(REG_00B0H, 0x0000140fU);
    HW_SCE_p_func103();
    HW_SCE_p_func100(0xfb5af664U, 0x735a1e6cU, 0xfd13abbcU, 0x06602b54U);
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    HW_SCE_p_func103();
    WR1_PROG(REG_0014H, 0x000000a1U);
    WR1_PROG(REG_00D0H, 0x0c200104U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x00000000U));
    WR1_PROG(REG_0000H, 0x00c10011U);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);

    WR1_PROG(REG_00B0H, 0x00001428U);
    WR1_PROG(REG_0000H, 0x00c0001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x00000001U));

    WR1_PROG(REG_00B0H, 0x00001419U);
    WR1_PROG(REG_0000H, 0x00c0001dU);
    WAIT_STS(REG_0004H, 30, 0);
    WR1_PROG(REG_0040H, 0x00001800U);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x00000002U));

    WR1_PROG(REG_00B4H, 0x0019000aU);
    WR1_PROG(REG_00B8H, 0x00140000U);

    WR1_PROG(REG_00A4H, 0x0404000aU);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00A0H, 0x20010000U);
    WR1_PROG(REG_00B8H, 0x00000014U);

    WR1_PROG(REG_00A4H, 0x04040010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0028000fU);
    WR1_PROG(REG_00B8H, 0x002d0014U);

    WR1_PROG(REG_00A4H, 0x04040002U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    WR1_PROG(REG_00B4H, 0x0028002dU);
    WR1_PROG(REG_00B8H, 0x00320000U);

    WR1_PROG(REG_00A4H, 0x04040009U);
    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    HW_SCE_p_func071(InData_DomainParam);

    WR1_PROG(REG_0094H, 0x00003420U);

    WR1_PROG(REG_0014H, 0x000000a7U);
    WR1_PROG(REG_009CH, 0x800100e0U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x000000f0U));
    WR1_PROG(REG_0024H, 0x00000000U);

    HW_SCE_p_func101(0xccef9b37U, 0x1cc14b97U, 0x6e6d0b0dU, 0xde8f0f2eU);
    HW_SCE_p_func088();

    HW_SCE_p_func100(0x46cc920cU, 0x8d757839U, 0xea20df70U, 0x3de74732U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0x5ca928afU, 0x11df335aU, 0xa54a75b3U, 0x03421348U);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_00B8H, 0x0000000aU);

        WR1_PROG(REG_00A4H, 0x04040010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x005a0028U);
        WR1_PROG(REG_00B8H, 0x002d000aU);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0014H, 0x000000a5U);
        WR1_PROG(REG_00B0H, 0x0000140fU);
        WR1_PROG(REG_0000H, 0x00c0001dU);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000001U));

        WR1_PROG(REG_00B4H, 0x000f002dU);
        WR1_PROG(REG_00B8H, 0x0028000aU);

        WR1_PROG(REG_00A4H, 0x04040002U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_00B4H, 0x000f0028U);
        WR1_PROG(REG_00B8H, 0x00140000U);

        WR1_PROG(REG_00A4H, 0x0404000aU);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        WR1_PROG(REG_0040H, 0x00210000U);

        HW_SCE_p_func100(0x6e55cae9U, 0xed052bffU, 0x5c7e38b2U, 0x27fe77feU);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func102(0xc3e7bffdU, 0xa4a124c8U, 0xede3776bU, 0xe3b9611dU);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            HW_SCE_p_func100(0x4b24807aU, 0xe26814ccU, 0x60e3683bU, 0x27848a85U);
            WR1_PROG(REG_00B0H, 0x00001414U);
            WR1_PROG(REG_0000H, 0x00c0001dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0014H, 0x000000a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x00000002U));

            WR1_PROG(REG_00B4H, 0x0014000aU);
            WR1_PROG(REG_00B8H, 0x000f0000U);

            WR1_PROG(REG_00A4H, 0x0404000aU);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_00B4H, 0x000f0032U);
            WR1_PROG(REG_00B8H, 0x0014000aU);

            WR1_PROG(REG_00A4H, 0x04040000U);
            WR1_PROG(REG_0008H, 0x00020000U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            WR1_PROG(REG_00B4H, 0x005a0014U);
            WR1_PROG(REG_00B8H, 0x000f000aU);

            WR1_PROG(REG_00A4H, 0x04040002U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);

            WR1_PROG(REG_0014H, 0x000007c5U);
            WR1_PROG(REG_00B0H, 0x00001414U);
            WAIT_STS(REG_0014H, 31, 1);
            WR8_ADDR(REG_002CH, &InData_MsgDgst[0]);

            WR1_PROG(REG_0014H, 0x000000c7U);
            WR1_PROG(REG_009CH, 0x80010000U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, InData_KeyMode[0]);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);

            HW_SCE_p_func100(0x0717e5c9U, 0x2f47a6d4U, 0xa265fc94U, 0x6c66af99U);
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
                WR1_PROG(REG_002CH, change_endian_long(0x000000f0U));
                WR1_PROG(REG_0024H, 0x00000000U);

                HW_SCE_p_func101(0xf675bc96U, 0xfe7aaf6dU, 0xb710e2f0U, 0x1718fdfdU);
                HW_SCE_p_func043();

                HW_SCE_p_func074();

                WR1_PROG(REG_0014H, 0x000000a7U);
                WR1_PROG(REG_009CH, 0x800100e0U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, change_endian_long(0x000000f0U));
                WR1_PROG(REG_0024H, 0x00000000U);

                HW_SCE_p_func101(0x27bb3cf1U, 0xb14c489aU, 0xe0b8929cU, 0xd97b64c1U);
                HW_SCE_p_func044();

                WR1_PROG(REG_0014H, 0x000007c1U);
                WR1_PROG(REG_00D4H, 0x40000100U);
                WR1_PROG(REG_00D0H, 0xf7009d07U);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);
                WAIT_STS(REG_0014H, 31, 1);
                WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

                WR1_PROG(REG_00B0H, 0x0000141eU);
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

                HW_SCE_p_func101(0xf8853f44U, 0xbc857246U, 0xb2fee6b0U, 0xc7a51661U);
            }
            else
            {
                WR1_PROG(REG_0014H, 0x000007c5U);
                WR1_PROG(REG_00B0H, 0x0000141eU);
                WAIT_STS(REG_0014H, 31, 1);
                WR8_ADDR(REG_002CH, &InData_Key[0]);

                HW_SCE_p_func101(0x9e5bd6c8U, 0xa60bdff7U, 0xfaecb78eU, 0x48e1add2U);
            }

            HW_SCE_p_func100(0x40d38391U, 0x5ecd3e8fU, 0x4d23cdc2U, 0x1ef4bc27U);
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                HW_SCE_p_func102(0xa48be862U, 0xc27d9311U, 0xe0135168U, 0xf9650492U);
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
            }
            else
            {
                WR1_PROG(REG_00B4H, 0x005a001eU);
                WR1_PROG(REG_00B8H, 0x0019000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x00280019U);
                WR1_PROG(REG_00B8H, 0x001e000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x001e0014U);
                WR1_PROG(REG_00B8H, 0x0019000aU);

                WR1_PROG(REG_00A4H, 0x04040005U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B4H, 0x0019000fU);
                WR1_PROG(REG_00B8H, 0x001e000aU);

                WR1_PROG(REG_00A4H, 0x04040002U);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_00B0H, 0x0000140fU);
                WR1_PROG(REG_0000H, 0x00c0001dU);
                WAIT_STS(REG_0004H, 30, 0);
                WR1_PROG(REG_0040H, 0x00001800U);
                WR1_PROG(REG_0014H, 0x000000a5U);
                WAIT_STS(REG_0014H, 31, 1);
                WR1_PROG(REG_002CH, change_endian_long(0x00000001U));

                WR1_PROG(REG_00B4H, 0x000f001eU);
                WR1_PROG(REG_00B8H, 0x00140000U);

                WR1_PROG(REG_00A4H, 0x0404000aU);
                WR1_PROG(REG_00A0H, 0x20010001U);
                WAIT_STS(REG_00A8H, 0, 1);
                WR1_PROG(REG_00ACH, 0x00000001U);

                WR1_PROG(REG_0040H, 0x00210000U);

                HW_SCE_p_func100(0x6a8f2261U, 0xc9db9ceaU, 0x82f5bd8aU, 0x88afc05eU);
                WR1_PROG(REG_0040H, 0x00400000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                if (CHCK_STS(REG_0040H, 22, 1))
                {
                    HW_SCE_p_func102(0x98107b51U, 0x9d8778c1U, 0xcf5dd711U, 0x0ffe2679U);
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return FSP_ERR_CRYPTO_SCE_FAIL;
                }
                else
                {
                    HW_SCE_p_func100(0x6dca6c1dU, 0xe2ed078fU, 0x37443742U, 0x51b06ffeU);
                    WR1_PROG(REG_00B0H, 0x00001828U);
                    WR1_PROG(REG_0008H, 0x00006022U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD8_ADDR(REG_002CH, &OutData_Signature[0]);

                    HW_SCE_p_func100(0x1611ee98U, 0x0590ff48U, 0x2c565523U, 0x8f2abe0fU);
                    WR1_PROG(REG_00B0H, 0x0000181eU);
                    WR1_PROG(REG_0008H, 0x00006022U);
                    WAIT_STS(REG_0008H, 30, 1);
                    RD8_ADDR(REG_002CH, &OutData_Signature[8]);

                    HW_SCE_p_func102(0x935510d4U, 0x7b2ef5f1U, 0x4fa34cdfU, 0x99d720c4U);
                    WR1_PROG(REG_006CH, 0x00000040U);
                    WAIT_STS(REG_0020H, 12, 0);

                    return FSP_SUCCESS;
                }
            }
        }
    }
}
