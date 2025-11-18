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

void r_rsip_func058(const uint32_t ARG1[], uint32_t ARG2)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    r_rsip_func100(0xcb81358eU, 0x081b2751U, 0xe64ae97cU, 0xd4dd9f6dU);
    RSIP.REG_00D0H.WORD = 0x4a070044U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_00D0H.WORD = 0x0e0704c4U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x01b16437U);
    r_rsip_func100(0xfc093198U, 0x8eaba8c6U, 0x688d5c7dU, 0xb996fdf8U);
    RSIP.REG_0094H.WORD = 0x00009020U;
    RSIP.REG_0094H.WORD = 0x01000000U;
    RSIP.REG_00D0H.WORD = 0x4a040044U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_00D0H.WORD = 0x0e0404c4U;
    RSIP.REG_009CH.WORD = 0x81010020U;
    RSIP.REG_0000H.WORD = 0x00490005U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    r_rsip_func100(0xecbed72aU, 0xf67665c8U, 0x62c35872U, 0x64abce4bU);
    RSIP.REG_00D0H.WORD = 0xf7041c85U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = S_FLASH[ARG2 + 0];
    RSIP.REG_002CH.WORD = S_FLASH[ARG2 + 1];
    RSIP.REG_002CH.WORD = S_FLASH[ARG2 + 2];
    RSIP.REG_002CH.WORD = S_FLASH[ARG2 + 3];
    r_rsip_func100(0xcb85f709U, 0xe00d6021U, 0x7db1ce37U, 0x3fcee2aaU);
    RSIP.REG_00D0H.WORD = 0x07040d05U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = S_FLASH[ARG2 + 4];
    RSIP.REG_002CH.WORD = S_FLASH[ARG2 + 5];
    RSIP.REG_002CH.WORD = S_FLASH[ARG2 + 6];
    RSIP.REG_002CH.WORD = S_FLASH[ARG2 + 7];
    RSIP.REG_00D0H.WORD = 0x8c100005U;
    RSIP.REG_0000H.WORD = 0x00410011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0014H.WORD = 0x000003c1U;
    RSIP.REG_00D0H.WORD = 0x0a0000adU;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = ARG1[0];
    RSIP.REG_002CH.WORD = ARG1[1];
    RSIP.REG_002CH.WORD = ARG1[2];
    RSIP.REG_002CH.WORD = ARG1[3];
    r_rsip_func100(0x331a5ba5U, 0x12d422d0U, 0x8a6a6143U, 0x9cf98b65U);
    RSIP.REG_0014H.WORD = 0x000003c1U;
    RSIP.REG_00D0H.WORD = 0x0a0000bdU;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = ARG1[4];
    RSIP.REG_002CH.WORD = ARG1[5];
    RSIP.REG_002CH.WORD = ARG1[6];
    RSIP.REG_002CH.WORD = ARG1[7];
    RSIP.REG_0094H.WORD = 0x00007c07U;
    RSIP.REG_0040H.WORD = 0x00602000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
}
