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

rsip_ret_t r_rsip_p81(void)
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_008CH.WORD = 0x00000001U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_008CH.BIT.B1)
    {
        /* waiting */
    }
    if (0x0009F7C3U != (RSIP.REG_0090H.WORD & 0xFFFFFFFFU))
    {
        return RSIP_RET_FAIL;
    }
    else
    {
        RSIP.REG_000CH.WORD = 0x38c60eedU;
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0048H.WORD = 0x00000000U;
        RSIP.REG_0008H.WORD = 0x00000001U;
        RSIP.REG_0010H.WORD = 0x00001401U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (0x0U != (RSIP.REG_006CH.WORD & 0x17U))
        {
            return RSIP_RET_RESOURCE_CONFLICT;
        }
        RSIP.REG_00C0H.WORD = 0x00000001U;
        RSIP.REG_00E0H.WORD = 0x00000001U;
        RSIP.REG_00F0H.WORD = 0x00000001U;
        RSIP.REG_0070H.WORD = 0x00818001U;
        RSIP.REG_0078H.WORD = 0x00000d00U;
        RSIP.REG_00C4H.WORD = 0x00008002U;
        RSIP.REG_0014H.WORD = 0x000003a1U;
        r_rsip_func101(bswap_32big(0x5270f37cU), bswap_32big(0xbf2be020U), bswap_32big(0x46e2055dU), bswap_32big(0xadd4e6b8U));
        RSIP.REG_00C4H.WORD = 0x00000000U;
        RSIP.REG_0014H.WORD = 0x000003a1U;
        RSIP.REG_00D0H.WORD = 0x0a0700f5U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = 0x17bb05e0U;
        RSIP.REG_002CH.WORD = 0xd5ce4a63U;
        RSIP.REG_002CH.WORD = 0x184fb60aU;
        RSIP.REG_002CH.WORD = 0x27996c70U;
        r_rsip_func101(bswap_32big(0x73480c17U), bswap_32big(0xcfcc7dffU), bswap_32big(0xc32e1111U), bswap_32big(0x00ba8bd2U));
        r_rsip_func100(bswap_32big(0x11121160U), bswap_32big(0xba2b9f28U), bswap_32big(0x552cc303U), bswap_32big(0x5e0aa2c8U));
        RSIP.REG_0008H.WORD = 0x00020000U;
        if (0U == (RSIP.REG_0020H.BIT.B13))
        {
            RSIP.REG_006CH.WORD = 0x00000020U;
            return RSIP_RET_FAIL;
        }
        else
        {
            RSIP.REG_0038H.WORD = 0x000000F1U;
            RSIP.REG_0078H.WORD = 0x00000220U;
            r_rsip_func102(bswap_32big(0x7b0b8ac1U), bswap_32big(0x16fffecfU), bswap_32big(0xfc1af76fU), bswap_32big(0x70d1397aU));
            RSIP.REG_006CH.WORD = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0020H.BIT.B12)
            {
                /* waiting */
            }
            return RSIP_RET_PASS;
        }
    }
}
