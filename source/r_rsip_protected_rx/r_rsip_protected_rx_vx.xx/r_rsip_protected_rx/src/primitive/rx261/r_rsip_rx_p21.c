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

rsip_ret_t r_rsip_p21(const uint32_t InData_HV[], const uint32_t InData_IV[], const uint32_t InData_Text[], uint32_t OutData_DataT[], uint32_t MAX_CNT)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    if (0x0U != (RSIP.REG_0068H.WORD & 0x16U))
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    RSIP.REG_0070H.WORD = 0x00210001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    r_rsip_func100(0xcde6b73fU, 0x65775821U, 0xfb6857bcU, 0x1e2f6470U);
    RSIP.REG_0014H.WORD = 0x000003c1U;
    RSIP.REG_00D0H.WORD = 0x080000a5U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_HV[0];
    RSIP.REG_002CH.WORD = InData_HV[1];
    RSIP.REG_002CH.WORD = InData_HV[2];
    RSIP.REG_002CH.WORD = InData_HV[3];
    RSIP.REG_0014H.WORD = 0x000003c1U;
    RSIP.REG_00D0H.WORD = 0x08000055U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_IV[0];
    RSIP.REG_002CH.WORD = InData_IV[1];
    RSIP.REG_002CH.WORD = InData_IV[2];
    RSIP.REG_002CH.WORD = InData_IV[3];
    RSIP.REG_0014H.WORD = 0x00020061U;
    RSIP.REG_00D4H.WORD = 0x00008000U;
    RSIP.REG_00D0H.WORD = 0x0e128456U;
    for (iLoop = 0; iLoop < MAX_CNT ; iLoop = iLoop + 4)
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
    }
    r_rsip_func205();
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x0c100104U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    r_rsip_func100(0x620d608aU, 0x5714cbf8U, 0xe0253079U, 0x6f4639ccU);
    RSIP.REG_0008H.WORD = 0x00001012U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0008H.BIT.B30)
    {
        /* waiting */
    }
    OutData_DataT[0] = RSIP.REG_002CH.WORD;
    OutData_DataT[1] = RSIP.REG_002CH.WORD;
    OutData_DataT[2] = RSIP.REG_002CH.WORD;
    OutData_DataT[3] = RSIP.REG_002CH.WORD;
    r_rsip_func102(0x3f05a4e7U, 0x416c71e8U, 0x4d1c2e34U, 0x8c8cfbaaU);
    RSIP.REG_0068H.WORD = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0020H.BIT.B12)
    {
        /* waiting */
    }
    return RSIP_RET_PASS;
}
