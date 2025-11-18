/*
 * Copyright (c) 2015 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 15.10.2024 1.00     First Release.
 *         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
 *         :                     Revised key management specification
 *********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_rsip_primitive.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

rsip_ret_t r_rsip_peef(uint32_t OutData_EncCertificateInfo[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    r_rsip_func100(0x0204567fU, 0xd7b6b870U, 0xcb8aba8aU, 0x3d17b6adU);
    r_rsip_func103();
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x0c200104U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_009CH.WORD = 0x80010000U;
    RSIP.REG_0000H.WORD = 0x03410005U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0000H.WORD = 0x0001000dU;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0094H.WORD = 0x000034c0U;
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x0000ee02U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0xcdd76889U, 0x13e440aeU, 0x4ac50352U, 0xa1b3b125U);
    r_rsip_func043();
    RSIP.REG_0094H.WORD = 0x0000b4c0U;
    RSIP.REG_0094H.WORD = 0x010f6caaU;
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x0000ee02U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x8546530eU, 0x435e5d00U, 0xa843d31fU, 0xbf41cf2eU);
    r_rsip_func044();
    r_rsip_func100(0xafd8b87eU, 0xf222a242U, 0x766557a5U, 0xb4d1433fU);
    RSIP.REG_00B0H.WORD = 0x0000187eU;
    RSIP.REG_00D4H.WORD = 0x40000100U;
    RSIP.REG_00D0H.WORD = 0xe7009d07U;
    RSIP.REG_0000H.WORD = 0x00430021U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0008H.WORD = 0x00001022U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0008H.BIT.B30)
    {
        /* waiting */
    }
    OutData_EncCertificateInfo[1] = RSIP.REG_002CH.WORD;
    OutData_EncCertificateInfo[2] = RSIP.REG_002CH.WORD;
    OutData_EncCertificateInfo[3] = RSIP.REG_002CH.WORD;
    OutData_EncCertificateInfo[4] = RSIP.REG_002CH.WORD;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0008H.BIT.B30)
    {
        /* waiting */
    }
    OutData_EncCertificateInfo[5] = RSIP.REG_002CH.WORD;
    OutData_EncCertificateInfo[6] = RSIP.REG_002CH.WORD;
    OutData_EncCertificateInfo[7] = RSIP.REG_002CH.WORD;
    OutData_EncCertificateInfo[8] = RSIP.REG_002CH.WORD;
    r_rsip_func100(0x9fe2eaf8U, 0xf86005b7U, 0xed4ceaa3U, 0x7f2dedb7U);
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x0c000104U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_00D4H.WORD = 0x40000000U;
    RSIP.REG_00D0H.WORD = 0x09108105U;
    RSIP.REG_0000H.WORD = 0x00410011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0008H.WORD = 0x00001012U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0008H.BIT.B30)
    {
        /* waiting */
    }
    OutData_EncCertificateInfo[9] = RSIP.REG_002CH.WORD;
    OutData_EncCertificateInfo[10] = RSIP.REG_002CH.WORD;
    OutData_EncCertificateInfo[11] = RSIP.REG_002CH.WORD;
    OutData_EncCertificateInfo[12] = RSIP.REG_002CH.WORD;
    r_rsip_func100(0x7126d0f2U, 0xef6fa6f9U, 0x3b506f5fU, 0xafc98a9fU);
    RSIP.REG_009CH.WORD = 0x81010000U;
    RSIP.REG_0008H.WORD = 0x00005006U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0008H.BIT.B30)
    {
        /* waiting */
    }
    OutData_EncCertificateInfo[0] = RSIP.REG_002CH.WORD;
    r_rsip_func102(0x0011dc78U, 0xa01cfb10U, 0xdf4a79b5U, 0xf7513404U);
    RSIP.REG_006CH.WORD = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0020H.BIT.B12)
    {
        /* waiting */
    }
    return RSIP_RET_PASS;
}
