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

void r_rsip_func510(const uint32_t ARG1[], const uint32_t ARG2[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    RSIP.REG_0094H.WORD = 0x00003427U;
    RSIP.REG_0094H.WORD = 0x00000800U;
    RSIP.REG_0014H.WORD = 0x000000c7U;
    RSIP.REG_009CH.WORD = 0x80010080U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = ARG1[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0094H.WORD = 0x38000c84U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00260000U;
    r_rsip_func100(0xb0ea8bb0U, 0xd0dea9cbU, 0xca9dcee2U, 0xd61c643bU);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        RSIP.REG_0014H.WORD = 0x000003c1U;
        RSIP.REG_00D0H.WORD = 0x08000105U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = ARG2[0];
        RSIP.REG_002CH.WORD = ARG2[1];
        RSIP.REG_002CH.WORD = ARG2[2];
        RSIP.REG_002CH.WORD = ARG2[3];
        RSIP.REG_0094H.WORD = 0x0000b460U;
        RSIP.REG_0094H.WORD = 0x00000010U;
        RSIP.REG_009CH.WORD = 0x80840003U;
        RSIP.REG_0000H.WORD = 0x03410011U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        r_rsip_func101(0xabe9a225U, 0x73286278U, 0xf9b612ebU, 0x40ffecebU);
    }
    else
    {
        RSIP.REG_0014H.WORD = 0x000000c7U;
        RSIP.REG_009CH.WORD = 0x800100c0U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = ARG2[0];
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0014H.WORD = 0x000000a7U;
        RSIP.REG_009CH.WORD = 0x800100e0U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x0000f510U);
        RSIP.REG_0024H.WORD = 0x00000000U;
        r_rsip_func101(0xc762856fU, 0xca687744U, 0x006c4a94U, 0xac96e69aU);
        r_rsip_func043();
        RSIP.REG_0094H.WORD = 0x0000b4c0U;
        RSIP.REG_0094H.WORD = 0x0199e556U;
        RSIP.REG_0014H.WORD = 0x000000a7U;
        RSIP.REG_009CH.WORD = 0x800100e0U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x0000f510U);
        RSIP.REG_0024H.WORD = 0x00000000U;
        r_rsip_func101(0x53db1c02U, 0xf2338550U, 0x9995221fU, 0xb010d746U);
        r_rsip_func044();
        RSIP.REG_0014H.WORD = 0x000003c1U;
        RSIP.REG_00D4H.WORD = 0x40000000U;
        RSIP.REG_00D0H.WORD = 0xf7009d05U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = ARG2[1];
        RSIP.REG_002CH.WORD = ARG2[2];
        RSIP.REG_002CH.WORD = ARG2[3];
        RSIP.REG_002CH.WORD = ARG2[4];
        RSIP.REG_0094H.WORD = 0x0000b460U;
        RSIP.REG_0094H.WORD = 0x00000010U;
        RSIP.REG_009CH.WORD = 0x80840003U;
        RSIP.REG_0000H.WORD = 0x03410011U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        RSIP.REG_0014H.WORD = 0x000003c1U;
        RSIP.REG_00D4H.WORD = 0x40000000U;
        RSIP.REG_00D0H.WORD = 0x07008d05U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = ARG2[5];
        RSIP.REG_002CH.WORD = ARG2[6];
        RSIP.REG_002CH.WORD = ARG2[7];
        RSIP.REG_002CH.WORD = ARG2[8];
        RSIP.REG_00D0H.WORD = 0x9c100005U;
        RSIP.REG_0000H.WORD = 0x00410011U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        r_rsip_func100(0xc88a0583U, 0xef8f5ecbU, 0xb0224d90U, 0x514f5a86U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            RSIP.REG_0094H.WORD = 0x00002c00U;
            r_rsip_func101(0xd20df855U, 0xf472ffe4U, 0xa776e1feU, 0xec1d7906U);
        }
        r_rsip_func101(0x096d3581U, 0x42cda368U, 0x72387fc4U, 0x024dcf65U);
    }
    RSIP.REG_0094H.WORD = 0x000034e1U;
    RSIP.REG_0094H.WORD = 0x00007c07U;
    RSIP.REG_0040H.WORD = 0x00602000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
}
