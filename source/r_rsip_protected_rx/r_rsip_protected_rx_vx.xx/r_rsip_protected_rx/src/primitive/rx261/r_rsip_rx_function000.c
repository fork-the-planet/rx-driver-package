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

void r_rsip_func000(const uint32_t InData_PaddedMsg[], uint32_t MAX_CNT)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_0014H.WORD = 0x00020064U;
    for (iLoop = 0; iLoop < MAX_CNT; iLoop = iLoop + 16)
    {
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 0];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 1];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 2];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 3];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 4];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 5];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 6];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 7];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 8];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 9];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 10];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 11];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 12];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 13];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 14];
        RSIP.REG_002CH.WORD = InData_PaddedMsg[iLoop + 15];
    }
    /* WAIT_LOOP */
    while (0U != RSIP.REG_00F8H.BIT.B2)
    {
        /* waiting */
    }
    RSIP.REG_0014H.WORD = 0x00000000U;
    RSIP.REG_0040H.WORD = 0x00001600U;
}
