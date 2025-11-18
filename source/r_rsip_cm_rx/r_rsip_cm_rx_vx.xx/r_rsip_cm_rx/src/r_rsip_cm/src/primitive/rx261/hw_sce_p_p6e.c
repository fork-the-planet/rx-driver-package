/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_GenerateOemKeyIndexSub (const uint32_t InData_KeyType[],
                                         const uint32_t InData_Cmd[],
                                         const uint32_t InData_SharedKeyIndex[],
                                         const uint32_t InData_SessionKey[],
                                         const uint32_t InData_IV[],
                                         const uint32_t InData_InstData[],
                                         uint32_t OutData_KeyIndex[])
{
    uint32_t OFS_ADR = 0U;

    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x006e0001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    HW_SCE_p_func048(InData_KeyType);

    WR1_PROG(REG_0094H, 0x38000c00U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00260000U);

    HW_SCE_p_func100(0x0de60e2eU, 0xd9cbc028U, 0x6d08bcf9U, 0x91847a36U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func049(InData_Cmd);

        WR1_PROG(REG_0014H, 0x000000c7U);
        WR1_PROG(REG_009CH, 0x80010020U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(InData_SharedKeyIndex[0]));
        WR1_PROG(REG_0024H, 0x00000000U);

        WR1_PROG(REG_0094H, 0x0000b440U);
        WR1_PROG(REG_0094H, 0x2C8003A0U);

        WR1_PROG(REG_0094H, 0x000034a4U);

        WR1_PROG(REG_0094H, 0x38008880U);
        WR1_PROG(REG_0094H, 0x00000023U);
        WR1_PROG(REG_0094H, 0x1000b480U);
        WR1_PROG(REG_0094H, 0x00000005U);

        HW_SCE_p_func056();

        WR1_PROG(REG_0094H, 0x3420a820U);
        WR1_PROG(REG_0094H, 0x00000010U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00A60000U);

        HW_SCE_p_func100(0xe50071a3U, 0x47b7dd31U, 0x9e989796U, 0x6c9bbf5bU);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func102(0x41e0d747U, 0x68aae311U, 0x8ba0e7b5U, 0xdab0bcbfU);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_0094H, 0x00003485U);

            WR1_PROG(REG_0014H, 0x000001a1U);
            WR1_PROG(REG_00D0H, 0x07330c04U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_00D0H, 0x07330d04U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_009CH, 0x80010000U);
            WR1_PROG(REG_0000H, 0x03410005U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);
            WR1_PROG(REG_0000H, 0x0001000dU);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_0014H, 0x000001a1U);
            WR1_PROG(REG_00D0H, 0x07330d04U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_00D0H, 0x06330104U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

            WR1_PROG(REG_00B0H, 0x00001404U);
            WR1_PROG(REG_0000H, 0x00c10021U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            OFS_ADR = InData_SharedKeyIndex[0] << 3;

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x0000006eU));
            WR1_PROG(REG_0024H, 0x00000000U);

            HW_SCE_p_func101(0x6a5fa47cU, 0x3fc57cdeU, 0x8b4b9105U, 0xb1785d74U);
            HW_SCE_p_func058(InData_SessionKey, OFS_ADR);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x0000006eU));
            WR1_PROG(REG_0024H, 0x00000000U);

            HW_SCE_p_func101(0xfee1d7dcU, 0x6e35e226U, 0x64ab57dbU, 0x64b6603aU);
            HW_SCE_p_func057(InData_IV, InData_InstData, OutData_KeyIndex);

            HW_SCE_p_func100(0x0c004e39U, 0x9eb4a634U, 0x66e8d765U, 0xe2cd7e59U);
            WR1_PROG(REG_00B0H, 0x00001804U);

            WR1_PROG(REG_00D0H, 0x080000b5U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            WR1_PROG(REG_00D0H, 0x08000075U);
            WR1_PROG(REG_0000H, 0x00430011U);
            WAIT_STS(REG_0004H, 30, 0);
            WR1_PROG(REG_0040H, 0x00001800U);

            HW_SCE_p_func100(0x9872015dU, 0xd799a614U, 0x76387235U, 0xc352d26bU);
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                HW_SCE_p_func102(0xb66faf73U, 0x09fe0d5dU, 0x454a624aU, 0x826a8fb0U);
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return FSP_ERR_CRYPTO_SCE_FAIL;
            }
            else
            {
                HW_SCE_p_func100(0xf903ffa9U, 0x4a7ce815U, 0x0ed5cfc1U, 0x296b8c98U);
                WR1_PROG(REG_009CH, 0x81010000U);
                WR1_PROG(REG_0008H, 0x00005006U);
                WAIT_STS(REG_0008H, 30, 1);
                RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

                HW_SCE_p_func102(0x378cf83fU, 0xd972f132U, 0xcb8a5efaU, 0x9ce99c1aU);
                WR1_PROG(REG_006CH, 0x00000040U);
                WAIT_STS(REG_0020H, 12, 0);

                return FSP_SUCCESS;
            }
        }
    }
    else
    {
        HW_SCE_p_func049(InData_Cmd);

        WR1_PROG(REG_0094H, 0x0000b440U);
        WR1_PROG(REG_0094H, 0x2C8003A0U);

        WR1_PROG(REG_0094H, 0x000034a4U);

        WR1_PROG(REG_0094H, 0x38008880U);
        WR1_PROG(REG_0094H, 0x00000023U);
        WR1_PROG(REG_0094H, 0x1000b480U);
        WR1_PROG(REG_0094H, 0x00000005U);

        HW_SCE_p_func056();

        HW_SCE_p_func100(0xcbeb0daeU, 0x49603825U, 0x4bbc4617U, 0xe113d2b6U);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func102(0x1dfd5883U, 0x585ef9fcU, 0xa5441a8cU, 0xe7145164U);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_ERR_CRYPTO_SCE_FAIL;
        }
        else
        {
            WR1_PROG(REG_0094H, 0x00003485U);

            WR1_PROG(REG_0014H, 0x000000a7U);
            WR1_PROG(REG_009CH, 0x800100e0U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x0000006eU));
            WR1_PROG(REG_0024H, 0x00000000U);

            HW_SCE_p_func101(0x1e51007bU, 0xf2c8379fU, 0x82dcb25aU, 0x51986c30U);
            HW_SCE_p_func093(InData_InstData, OutData_KeyIndex);

            HW_SCE_p_func100(0x40495942U, 0x87921405U, 0x59993826U, 0x08120704U);
            WR1_PROG(REG_009CH, 0x81010000U);
            WR1_PROG(REG_0008H, 0x00005006U);
            WAIT_STS(REG_0008H, 30, 1);
            RD1_ADDR(REG_002CH, &OutData_KeyIndex[0]);

            HW_SCE_p_func102(0x5af19f25U, 0x86d14394U, 0x7b8475d5U, 0x22f8d256U);
            WR1_PROG(REG_006CH, 0x00000040U);
            WAIT_STS(REG_0020H, 12, 0);

            return FSP_SUCCESS;
        }
    }
}
