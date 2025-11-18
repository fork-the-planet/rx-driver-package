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

rsip_ret_t r_rsip_p26f(const uint32_t InData_Program[], const uint32_t InData_MAC[], uint32_t MAX_CNT)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_0014H.WORD = 0x00020061U;
    RSIP.REG_00D4H.WORD = 0x40000000U;
    RSIP.REG_00D0H.WORD = 0x0e108456U;
    for (iLoop = 0; iLoop < MAX_CNT - 4; iLoop = iLoop + 4)
    {
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_Program[iLoop + 0];
        RSIP.REG_002CH.WORD = InData_Program[iLoop + 1];
        RSIP.REG_002CH.WORD = InData_Program[iLoop + 2];
        RSIP.REG_002CH.WORD = InData_Program[iLoop + 3];
    }
    r_rsip_func205();
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D4H.WORD = 0x40000000U;
    RSIP.REG_00D0H.WORD = 0x4a108104U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_00D0H.WORD = 0x0c100055U;
    RSIP.REG_0000H.WORD = 0x00410011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0014H.WORD = 0x000003c1U;
    RSIP.REG_00D4H.WORD = 0x40000000U;
    RSIP.REG_00D0H.WORD = 0x0e108455U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_Program[iLoop + 0];
    RSIP.REG_002CH.WORD = InData_Program[iLoop + 1];
    RSIP.REG_002CH.WORD = InData_Program[iLoop + 2];
    RSIP.REG_002CH.WORD = InData_Program[iLoop + 3];
    RSIP.REG_0014H.WORD = 0x000003c1U;
    RSIP.REG_00D0H.WORD = 0x9c100005U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_MAC[0];
    RSIP.REG_002CH.WORD = InData_MAC[1];
    RSIP.REG_002CH.WORD = InData_MAC[2];
    RSIP.REG_002CH.WORD = InData_MAC[3];
    r_rsip_func100(0xf4603914U, 0x8a8d194cU, 0x9ba210d2U, 0x6b740edbU);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        RSIP.REG_006CH.WORD = 0x00000020U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0020H.BIT.B12)
        {
            /* waiting */
        }
        return RSIP_RET_FAIL;
    }
    else
    {
        r_rsip_func102(0x9b59d5baU, 0x45a0f8daU, 0xca891d86U, 0xe88919a1U);
        RSIP.REG_006CH.WORD = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0020H.BIT.B12)
        {
            /* waiting */
        }
        return RSIP_RET_PASS;
    }
}
