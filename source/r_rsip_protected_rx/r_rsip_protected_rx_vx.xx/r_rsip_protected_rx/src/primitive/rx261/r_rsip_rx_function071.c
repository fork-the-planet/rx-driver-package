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

void r_rsip_func071(const uint32_t ARG1[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_0094H.WORD = 0x30003000U;
    RSIP.REG_0094H.WORD = 0x00050020U;
    RSIP.REG_0094H.WORD = 0x0000b420U;
    RSIP.REG_0094H.WORD = 0x017f9e4eU;
    RSIP.REG_0094H.WORD = 0x00030040U;
    RSIP.REG_0094H.WORD = 0x0000b420U;
    RSIP.REG_0094H.WORD = 0x01b24fdbU;
    RSIP.REG_0094H.WORD = 0x00070040U;
    RSIP.REG_0094H.WORD = 0x0000b420U;
    RSIP.REG_0094H.WORD = 0x01b2b66bU;
    RSIP.REG_0094H.WORD = 0x00000080U;
    RSIP.REG_00D0H.WORD = 0x300710c4U;
    RSIP.REG_009CH.WORD = 0x81010020U;
    RSIP.REG_0000H.WORD = 0x00490005U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_00A0H.WORD = 0x20010000U;
    RSIP.REG_00B0H.WORD = 0x00001419U;
    RSIP.REG_0014H.WORD = 0x00000fc1U;
    RSIP.REG_00D4H.WORD = 0x00000300U;
    RSIP.REG_00D0H.WORD = 0xf7049d07U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = ARG1[0];
    RSIP.REG_002CH.WORD = ARG1[1];
    RSIP.REG_002CH.WORD = ARG1[2];
    RSIP.REG_002CH.WORD = ARG1[3];
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = ARG1[4];
    RSIP.REG_002CH.WORD = ARG1[5];
    RSIP.REG_002CH.WORD = ARG1[6];
    RSIP.REG_002CH.WORD = ARG1[7];
    RSIP.REG_0000H.WORD = 0x00c10021U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_00B0H.WORD = 0x0000141eU;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = ARG1[8];
    RSIP.REG_002CH.WORD = ARG1[9];
    RSIP.REG_002CH.WORD = ARG1[10];
    RSIP.REG_002CH.WORD = ARG1[11];
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = ARG1[12];
    RSIP.REG_002CH.WORD = ARG1[13];
    RSIP.REG_002CH.WORD = ARG1[14];
    RSIP.REG_002CH.WORD = ARG1[15];
    RSIP.REG_0000H.WORD = 0x00c10021U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_00D0H.WORD = 0x07040d05U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = ARG1[16];
    RSIP.REG_002CH.WORD = ARG1[17];
    RSIP.REG_002CH.WORD = ARG1[18];
    RSIP.REG_002CH.WORD = ARG1[19];
    RSIP.REG_00D0H.WORD = 0x8c100005U;
    RSIP.REG_0000H.WORD = 0x00410011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
}
