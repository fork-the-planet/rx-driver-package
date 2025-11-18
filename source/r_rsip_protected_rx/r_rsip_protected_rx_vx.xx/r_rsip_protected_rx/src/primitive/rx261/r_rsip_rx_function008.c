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

void r_rsip_func008(void)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_00B4H.WORD = 0x0037000fU;
    RSIP.REG_00B8H.WORD = 0x00190005U;
    RSIP.REG_00A4H.WORD = 0x04040002U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x00370014U;
    RSIP.REG_00B8H.WORD = 0x001e0005U;
    RSIP.REG_00A4H.WORD = 0x04040002U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x00190019U;
    RSIP.REG_00B8H.WORD = 0x000f0005U;
    RSIP.REG_00A4H.WORD = 0x04040002U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x005f000fU;
    RSIP.REG_00B8H.WORD = 0x00140005U;
    RSIP.REG_00A4H.WORD = 0x04040005U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x00190014U;
    RSIP.REG_00B8H.WORD = 0x000f0005U;
    RSIP.REG_00A4H.WORD = 0x04040002U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x0064000fU;
    RSIP.REG_00B8H.WORD = 0x00140005U;
    RSIP.REG_00A4H.WORD = 0x04040005U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x001e001eU;
    RSIP.REG_00B8H.WORD = 0x000f0005U;
    RSIP.REG_00A4H.WORD = 0x04040002U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_00B4H.WORD = 0x0014000fU;
    RSIP.REG_00B8H.WORD = 0x00230000U;
    RSIP.REG_00A4H.WORD = 0x0404000aU;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_0040H.WORD = 0x00210000U;
    RSIP.REG_00B4H.WORD = 0x000f0014U;
    RSIP.REG_00B8H.WORD = 0x00230000U;
    RSIP.REG_00A4H.WORD = 0x0404000aU;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_0040H.WORD = 0x00210000U;
}
