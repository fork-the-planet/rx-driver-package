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

rsip_ret_t r_rsip_p95f(const uint32_t InData_Text[], const uint32_t InData_TextLen[], uint32_t OutData_Text[], uint32_t OutData_MAC[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_0014H.WORD = 0x000000c7U;
    RSIP.REG_009CH.WORD = 0x80010000U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_TextLen[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0094H.WORD = 0x00008c00U;
    RSIP.REG_0094H.WORD = 0x0000000fU;
    RSIP.REG_0094H.WORD = 0x38008800U;
    RSIP.REG_0094H.WORD = 0x00000000U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00A60000U;
    r_rsip_func100(0xd01fbf94U, 0x07dacdb2U, 0xc3e55da9U, 0x10c86c5eU);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        RSIP.REG_0014H.WORD = 0x000003c1U;
        RSIP.REG_00D0H.WORD = 0xe7000d05U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_Text[0];
        RSIP.REG_002CH.WORD = InData_Text[1];
        RSIP.REG_002CH.WORD = InData_Text[2];
        RSIP.REG_002CH.WORD = InData_Text[3];
        RSIP.REG_0094H.WORD = 0x00000821U;
        RSIP.REG_009CH.WORD = 0x80840001U;
        RSIP.REG_0000H.WORD = 0x03410011U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        RSIP.REG_0094H.WORD = 0x00000821U;
        RSIP.REG_0094H.WORD = 0x000008a5U;
        for (iLoop = 0; iLoop < 16; iLoop = iLoop + 1)
        {
            RSIP.REG_0094H.WORD = 0x3c0028a0U;
            RSIP.REG_0094H.WORD = 0x12003c25U;
            RSIP.REG_0094H.WORD = 0x00002ca0U;
        }
        r_rsip_func100(0xb8cdf669U, 0x6cf45fd7U, 0xda6e6a58U, 0x427cbf21U);
        RSIP.REG_0094H.WORD = 0x00000821U;
        RSIP.REG_009CH.WORD = 0x81840001U;
        RSIP.REG_0008H.WORD = 0x00005012U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_Text[0] = RSIP.REG_002CH.WORD;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_Text[1] = RSIP.REG_002CH.WORD;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_Text[2] = RSIP.REG_002CH.WORD;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_Text[3] = RSIP.REG_002CH.WORD;
        r_rsip_func101(0x32bdd9b4U, 0x5e42f64aU, 0x8c562062U, 0x035708eaU);
    }
    else
    {
        r_rsip_func101(0x248880e6U, 0xd444e12eU, 0xbb704e50U, 0xc1ba335dU);
    }
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x0c200104U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    r_rsip_func100(0xee73f22bU, 0xd0caafd3U, 0x92828575U, 0x0a8fbe2eU);
    RSIP.REG_00D0H.WORD = 0x09100105U;
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
    OutData_MAC[0] = RSIP.REG_002CH.WORD;
    OutData_MAC[1] = RSIP.REG_002CH.WORD;
    OutData_MAC[2] = RSIP.REG_002CH.WORD;
    OutData_MAC[3] = RSIP.REG_002CH.WORD;
    r_rsip_func102(0x35267fc0U, 0x9803fe19U, 0xca006485U, 0x4ebd545bU);
    RSIP.REG_006CH.WORD = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0020H.BIT.B12)
    {
        /* waiting */
    }
    return RSIP_RET_PASS;
}
