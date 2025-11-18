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

rsip_ret_t r_rsip_pdcs(uint32_t OutData_State[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_00F4H.WORD = 0x00000100U;
    r_rsip_func100(0xd0747b87U, 0x9be6c091U, 0x72b2154cU, 0xa0883d0bU);
    RSIP.REG_00F4H.WORD = 0x00000020U;
    RSIP.REG_0008H.WORD = 0x00004022U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0008H.BIT.B30)
    {
        /* waiting */
    }
    OutData_State[0] = RSIP.REG_002CH.WORD;
    OutData_State[1] = RSIP.REG_002CH.WORD;
    OutData_State[2] = RSIP.REG_002CH.WORD;
    OutData_State[3] = RSIP.REG_002CH.WORD;
    OutData_State[4] = RSIP.REG_002CH.WORD;
    OutData_State[5] = RSIP.REG_002CH.WORD;
    OutData_State[6] = RSIP.REG_002CH.WORD;
    OutData_State[7] = RSIP.REG_002CH.WORD;
    r_rsip_func102(0x4a87d0f8U, 0x29bcb32bU, 0x52b7f0d6U, 0x706913ddU);
    RSIP.REG_006CH.WORD = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0020H.BIT.B12)
    {
        /* waiting */
    }
    return RSIP_RET_PASS;
}
