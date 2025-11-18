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

rsip_ret_t r_rsip_p23u(const uint32_t InData_UpProgram[], uint32_t MAX_CNT, uint32_t OutData_Program[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    for (iLoop = 0; iLoop < MAX_CNT; iLoop = iLoop + 4)
    {
        r_rsip_func100(0xc5905e76U, 0x2ef46928U, 0xf3e28899U, 0x0021f6b8U);
        RSIP.REG_0014H.WORD = 0x000003c1U;
        RSIP.REG_00D0H.WORD = 0xd922090dU;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_UpProgram[iLoop + 0];
        RSIP.REG_002CH.WORD = InData_UpProgram[iLoop + 1];
        RSIP.REG_002CH.WORD = InData_UpProgram[iLoop + 2];
        RSIP.REG_002CH.WORD = InData_UpProgram[iLoop + 3];
        RSIP.REG_00D4H.WORD = 0x40000000U;
        RSIP.REG_00D0H.WORD = 0xe8008105U;
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
        OutData_Program[iLoop] = RSIP.REG_002CH.WORD;
        OutData_Program[iLoop + 1] = RSIP.REG_002CH.WORD;
        OutData_Program[iLoop + 2] = RSIP.REG_002CH.WORD;
        OutData_Program[iLoop + 3] = RSIP.REG_002CH.WORD;
        r_rsip_func101(0x6cfbd000U, 0x063767b6U, 0x84c83a1cU, 0x447ebe78U);
    }
    return RSIP_RET_PASS;
}
