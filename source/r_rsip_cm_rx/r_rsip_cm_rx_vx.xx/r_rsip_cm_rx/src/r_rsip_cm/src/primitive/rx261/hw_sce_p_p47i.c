/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_Aes128EncryptDecryptInitSub (const uint32_t InData_KeyMode[],
                                              const uint32_t InData_Cmd[],
                                              const uint32_t InData_KeyIndex[],
                                              const uint32_t InData_Key[],
                                              const uint32_t InData_IV[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00470001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010080U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_Cmd[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x3000a880U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_0094H, 0x00010020U);
    WR1_PROG(REG_0094H, 0x0000b480U);
    WR1_PROG(REG_0094H, 0x00000004U);
    WR1_PROG(REG_0094H, 0x00000080U);

    WR1_PROG(REG_0014H, 0x000000c7U);
    WR1_PROG(REG_009CH, 0x80010000U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, InData_KeyMode[0]);
    WR1_PROG(REG_0024H, 0x00000000U);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    HW_SCE_p_func100(0x85ee8c98U, 0xbe55b6c6U, 0xd766d974U, 0xf0ec77beU);
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
        WR1_PROG(REG_002CH, change_endian_long(0x00000047U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0x08e2bd68U, 0xdf5c411aU, 0x2653a347U, 0x26e1f6e9U);
        HW_SCE_p_func043();

        WR1_PROG(REG_0094H, 0x0000b4c0U);
        WR1_PROG(REG_0094H, 0x00000005U);

        WR1_PROG(REG_0014H, 0x000000a7U);
        WR1_PROG(REG_009CH, 0x800100e0U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000047U));
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func101(0x25b110c9U, 0x389df13cU, 0x67a7d16fU, 0x1fccf8daU);
        HW_SCE_p_func044();

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0xf7009d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[1]);

        WR1_PROG(REG_00B0H, 0x00000401U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_00B0H, 0x00000402U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000003c1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_ADDR(REG_002CH, &InData_KeyIndex[5]);

        WR1_PROG(REG_00D0H, 0x9c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func101(0x79c5e2fdU, 0xcc0553caU, 0x4c31ed74U, 0xe0fd5c15U);
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000003c5U);
        WR1_PROG(REG_00B0H, 0x00000401U);
        WAIT_STS(REG_0014H, 31, 1);
        WR2_ADDR(REG_002CH, &InData_Key[0]);
        WR1_PROG(REG_00B0H, 0x00000402U);
        WAIT_STS(REG_0014H, 31, 1);
        WR2_ADDR(REG_002CH, &InData_Key[2]);

        HW_SCE_p_func101(0x2429dd3dU, 0xfcce9d5bU, 0x14bc5f25U, 0xc696a4d2U);
    }

    HW_SCE_p_func100(0x4a892cf4U, 0x00914ee8U, 0x65403d52U, 0xc6d702f9U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0x00e4a381U, 0x0813b7ebU, 0x458cb88dU, 0xda5c5bcbU);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL;
    }
    else
    {
        HW_SCE_p_func100(0x24e5c3fdU, 0x43f61aa6U, 0x37e46c1eU, 0x1f9ebce1U);

        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_00B0H, 0x00000801U);
        WR1_PROG(REG_0000H, 0x00430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000802U);
        WR1_PROG(REG_0000H, 0x00430009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func100(0xc403c582U, 0x861790b3U, 0xa60bea87U, 0x31cb3ad5U);
        WR1_PROG(REG_0094H, 0x00007c04U);
        WR1_PROG(REG_0040H, 0x00600000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000000U)
        {
            HW_SCE_p_func101(0x79688938U, 0x9a20d086U, 0x4c0ab1c9U, 0xdbd1f43aU);
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
        {
            HW_SCE_p_func101(0xb7438cb5U, 0x9cf1f91cU, 0x842e61b0U, 0xc7825dd3U);
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            HW_SCE_p_func101(0x7c1f52aaU, 0x10efba87U, 0x823e00d0U, 0x37fc0cc6U);
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            HW_SCE_p_func101(0x47634ac4U, 0xd3df2a94U, 0x7ca0ccf6U, 0x25b62169U);
        }
        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000004U)
        {
            WR1_PROG(REG_0014H, 0x000003c1U);
            WR1_PROG(REG_00D0H, 0x08000045U);
            WAIT_STS(REG_0014H, 31, 1);
            WR4_ADDR(REG_002CH, &InData_IV[0]);

            HW_SCE_p_func101(0x94d83b71U, 0xa0f6849cU, 0x18f722bdU, 0xa1a3c1a2U);
        }
        else
        {
        }

        return FSP_SUCCESS;
    }
}
