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

void r_rsip_pa1u(const uint32_t InData_Text[], uint32_t OutData_Text[], uint32_t MAX_CNT)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    r_rsip_func100(0xa9c86d23U, 0x086cd766U, 0x232cff0aU, 0xc7446048U);
    RSIP.REG_0014H.WORD = 0x00020061U;
    RSIP.REG_00D4H.WORD = 0x40000000U;
    RSIP.REG_00D0H.WORD = 0xe7008d06U;
    RSIP.REG_0008H.WORD = 0x000c1000U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_Text[0];
    RSIP.REG_002CH.WORD = InData_Text[1];
    RSIP.REG_002CH.WORD = InData_Text[2];
    RSIP.REG_002CH.WORD = InData_Text[3];
    for (iLoop = 4; iLoop < MAX_CNT ; iLoop = iLoop + 4)
    {
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_Text[iLoop + 0];
        RSIP.REG_002CH.WORD = InData_Text[iLoop + 1];
        RSIP.REG_002CH.WORD = InData_Text[iLoop + 2];
        RSIP.REG_002CH.WORD = InData_Text[iLoop + 3];
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0008H.BIT.B30)
        {
            /* waiting */
        }
        OutData_Text[iLoop - 4] = RSIP.REG_002CH.WORD;
        OutData_Text[iLoop - 3] = RSIP.REG_002CH.WORD;
        OutData_Text[iLoop - 2] = RSIP.REG_002CH.WORD;
        OutData_Text[iLoop - 1] = RSIP.REG_002CH.WORD;
    }
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0008H.BIT.B30)
    {
        /* waiting */
    }
    OutData_Text[MAX_CNT - 4] = RSIP.REG_002CH.WORD;
    OutData_Text[MAX_CNT - 3] = RSIP.REG_002CH.WORD;
    OutData_Text[MAX_CNT - 2] = RSIP.REG_002CH.WORD;
    OutData_Text[MAX_CNT - 1] = RSIP.REG_002CH.WORD;
    r_rsip_func206();
    r_rsip_func101(0x273b7c8cU, 0x01f85e24U, 0x0c280302U, 0x966f4f9cU);
}
