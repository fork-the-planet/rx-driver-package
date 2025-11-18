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

void r_rsip_func001(void)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_00D0H.WORD = 0x08000045U;
    RSIP.REG_00B0H.WORD = 0x00001804U;
    RSIP.REG_0000H.WORD = 0x00430011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_00D0H.WORD = 0x08000055U;
    RSIP.REG_0000H.WORD = 0x00430011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0000H.WORD = 0x01410041U;
    RSIP.REG_0014H.WORD = 0x00000fa1U;
    RSIP.REG_00D0H.WORD = 0x0c000105U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_00D0H.WORD = 0x0c100105U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_00D4H.WORD = 0x00000100U;
    RSIP.REG_00D0H.WORD = 0x08008107U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    RSIP.REG_002CH.WORD = bswap_32big(0x36363636U);
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
}
