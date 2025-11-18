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

rsip_ret_t r_rsip_p20(uint32_t OutData_Text[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    if (0x0U != (RSIP.REG_006CH.WORD & 0x17U))
    {
        return RSIP_RET_RESOURCE_CONFLICT;
    }
    RSIP.REG_0070H.WORD = 0x00200002U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    r_rsip_func100(0x80521d5dU, 0x21c2b073U, 0x79d384a4U, 0xd947bd49U);
    r_rsip_func103();
    r_rsip_func100(0x1275d60bU, 0x5b4a8e94U, 0xb152d30dU, 0x64d46a47U);
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x0c200104U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_0008H.WORD = 0x00001012U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0008H.BIT.B30)
    {
        /* waiting */
    }
    OutData_Text[0] = RSIP.REG_002CH.WORD;
    OutData_Text[1] = RSIP.REG_002CH.WORD;
    OutData_Text[2] = RSIP.REG_002CH.WORD;
    OutData_Text[3] = RSIP.REG_002CH.WORD;
    r_rsip_func102(0x492a50eeU, 0xe52f677fU, 0xd8dbf88dU, 0xf95f3cbaU);
    RSIP.REG_006CH.WORD = 0x00000040U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0020H.BIT.B12)
    {
        /* waiting */
    }
    return RSIP_RET_PASS;
}
