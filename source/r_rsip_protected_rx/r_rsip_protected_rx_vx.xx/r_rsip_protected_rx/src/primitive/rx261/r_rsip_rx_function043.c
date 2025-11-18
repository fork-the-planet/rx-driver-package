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

void r_rsip_func043(void)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_00A0H.WORD = 0x00010000U;
    r_rsip_func100(0x6162f2e7U, 0x99276973U, 0xbfeaa50eU, 0x3845d1bcU);
    RSIP.REG_00B0H.WORD = 0x00001898U;
    RSIP.REG_00D0H.WORD = 0x08000085U;
    RSIP.REG_0000H.WORD = 0x00430011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    r_rsip_func100(0x65acddbdU, 0xd9c84621U, 0xefd0f228U, 0xf5da7567U);
    RSIP.REG_00D0H.WORD = 0x08000095U;
    RSIP.REG_0000H.WORD = 0x00430011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    r_rsip_func100(0x524d700bU, 0x32191befU, 0x457fdc49U, 0xc5b22cd6U);
    RSIP.REG_0094H.WORD = 0x000008a5U;
    RSIP.REG_00D0H.WORD = 0x080000c5U;
    RSIP.REG_00B0H.WORD = 0x00000893U;
    RSIP.REG_0000H.WORD = 0x00430009U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_00B0H.WORD = 0x00000894U;
    RSIP.REG_0000H.WORD = 0x00430009U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_00D0H.WORD = 0x0b040104U;
    RSIP.REG_009CH.WORD = 0x810100c0U;
    RSIP.REG_0000H.WORD = 0x00490005U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_009CH.WORD = 0x80840005U;
    RSIP.REG_0000H.WORD = 0x03410011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0094H.WORD = 0x00003845U;
    RSIP.REG_0094H.WORD = 0x00008c40U;
    RSIP.REG_0094H.WORD = 0x00ffffffU;
    RSIP.REG_0094H.WORD = 0x00009040U;
    RSIP.REG_0094H.WORD = 0x01000000U;
    RSIP.REG_0094H.WORD = 0x00003c45U;
    RSIP.REG_00D4H.WORD = 0x40000000U;
    RSIP.REG_00D0H.WORD = 0x30009105U;
    RSIP.REG_009CH.WORD = 0x81840005U;
    RSIP.REG_0000H.WORD = 0x00490011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    RSIP.REG_0094H.WORD = 0x00008c40U;
    RSIP.REG_0094H.WORD = 0x00ffffffU;
    RSIP.REG_0094H.WORD = 0x00009040U;
    RSIP.REG_0094H.WORD = 0x02000000U;
    RSIP.REG_0094H.WORD = 0x00003c45U;
    RSIP.REG_00D4H.WORD = 0x40000000U;
    RSIP.REG_00D0H.WORD = 0x30009045U;
    RSIP.REG_009CH.WORD = 0x81840005U;
    RSIP.REG_0000H.WORD = 0x00490011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    r_rsip_func100(0x0911c822U, 0x9dc007c7U, 0x50a93c0eU, 0x6d8a0f4cU);
    RSIP.REG_00D0H.WORD = 0x08000085U;
    RSIP.REG_0000H.WORD = 0x00410011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    r_rsip_func100(0x00738f57U, 0x82189ca3U, 0x21f84f35U, 0x4af72aabU);
    RSIP.REG_0014H.WORD = 0x000000a1U;
    RSIP.REG_00D0H.WORD = 0x0c000094U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
    RSIP.REG_0094H.WORD = 0x00007c07U;
    RSIP.REG_0040H.WORD = 0x00602000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
}
