/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"

fsp_err_t HW_SCE_LoadHukSub (const uint32_t InData_LC[])
{
    if (RD1_MASK(REG_006CH, 0x00000017U) != 0)
    {
        return FSP_ERR_CRYPTO_SCE_RESOURCE_CONFLICT;
    }

    WR1_PROG(REG_0070H, 0x00400001U);
    WR1_PROG(REG_004CH, 0x00000000U);

    HW_SCE_p_func048(InData_LC);

    WR1_PROG(REG_0094H, 0x3420a800U);
    WR1_PROG(REG_0094H, 0x00000009U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    HW_SCE_p_func100(0x56b2f686U, 0x65c531d8U, 0x6316e9a3U, 0x7e311a45U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        HW_SCE_p_func102(0x8d7e8408U, 0xccf9de38U, 0x26c28a80U, 0x9f372384U);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_ERR_CRYPTO_SCE_FAIL;
    }
    else
    {
        WR1_PROG(REG_0014H, 0x000003a1U);
        WR1_PROG(REG_00D0H, 0x0a0700f5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_PROG(REG_002CH, change_endian_long(0x1812f4dcU), change_endian_long(0x82d61a46U),
                 change_endian_long(0xe6752383U), change_endian_long(0xab0bdbb3U));

        HW_SCE_p_func100(0xa8b2e233U, 0x3410e7d6U, 0xf1a36ec3U, 0x5c889990U);
        WR1_PROG(REG_00D0H, 0x4a470044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_00D0H, 0x0e470484U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x01a5da45U));

        HW_SCE_p_func100(0xb08ec877U, 0x747a76b7U, 0x59c2b07bU, 0xe7b91a0aU);
        WR1_PROG(REG_00D0H, 0x4a470044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_00D0H, 0x0e470494U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x02a5da45U));

        WR1_PROG(REG_0014H, 0x000003a1U);
        WR1_PROG(REG_00D0H, 0x0a0700f5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR4_PROG(REG_002CH, change_endian_long(0xb068951eU), change_endian_long(0xc59ca899U),
                 change_endian_long(0xbb7f581cU), change_endian_long(0xc1127d55U));

        HW_SCE_p_func100(0x3951cfb2U, 0x9cc90b10U, 0x48dc3d50U, 0x310fde59U);
        WR1_PROG(REG_00D4H, 0x40000100U);
        WR1_PROG(REG_00D0H, 0xf7009d05U);
        WR1_PROG(REG_00D8H, 0x20000000U);
        WR1_PROG(REG_0000H, 0x00480011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0xf7008d05U);
        WR1_PROG(REG_00D8H, 0x20000010U);
        WR1_PROG(REG_0000H, 0x00480011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00A0H, 0x00010000U);

        WR1_PROG(REG_00B0H, 0x0000140eU);
        WR1_PROG(REG_0000H, 0x00c10021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x07008d05U);
        WR1_PROG(REG_00D8H, 0x20000020U);
        WR1_PROG(REG_0000H, 0x00480011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_00D0H, 0x8c100005U);
        WR1_PROG(REG_0000H, 0x00410011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x0000180eU);
        WR1_PROG(REG_00D0H, 0x08000085U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func100(0x7bbaae3fU, 0x09fe85a2U, 0xc06fb7bfU, 0xf43c3524U);
        WR1_PROG(REG_00D0H, 0x08000095U);
        WR1_PROG(REG_0000H, 0x00430011U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00A0H, 0x00010000U);

        WR1_PROG(REG_00B0H, 0x00000492U);
        WR1_PROG(REG_0000H, 0x00c00005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);
        WR1_PROG(REG_009CH, 0x81010000U);
        WR1_PROG(REG_0000H, 0x00c90005U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0014H, 0x000002a1U);
        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x4a008044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0e008104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x01d65991U));

        WR1_PROG(REG_00D4H, 0x40000000U);
        WR1_PROG(REG_00D0H, 0x0e008104U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x02d65991U));

        WR1_PROG(REG_00B0H, 0x00001498U);
        WR1_PROG(REG_0000H, 0x00c10021U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        HW_SCE_p_func100(0x60eb9b86U, 0xf4aa33bdU, 0xe03212a0U, 0x73bfadadU);
        WR1_PROG(REG_00D0H, 0x4a470044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_00D0H, 0x0e4704c4U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x01417d25U));

        WR1_PROG(REG_00D0H, 0x4a040044U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000000U));

        WR1_PROG(REG_00D0H, 0x0e040504U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0xc4406986U));

        WR1_PROG(REG_00B0H, 0x00000493U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_00B0H, 0x00000494U);
        WR1_PROG(REG_0000H, 0x00c10009U);
        WAIT_STS(REG_0004H, 30, 0);
        WR1_PROG(REG_0040H, 0x00001800U);

        WR1_PROG(REG_0078H, 0x00000202U);

        HW_SCE_p_func102(0x21a657feU, 0xabcf9e62U, 0xca25fda0U, 0x04ff1dbfU);
        WR1_PROG(REG_006CH, 0x00000040U);
        WAIT_STS(REG_0020H, 12, 0);

        return FSP_SUCCESS;
    }
}
