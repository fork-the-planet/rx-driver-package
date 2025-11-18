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
#include "r_rsip_sub_func.h"

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

void r_rsip_func073(const uint32_t ARG1[])
{
    int32_t iLoop = 0U, jLoop = 0U, kLoop = 0U, oLoop = 0U;
    uint32_t OFS_ADR = 0U;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)oLoop;
    (void)OFS_ADR;
    r_rsip_func070(ARG1);
    RSIP.REG_00A0H.WORD = 0x20010000U;
    RSIP.REG_00B8H.WORD = 0x0000000aU;
    RSIP.REG_00A4H.WORD = 0x04040010U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    r_rsip_func073_sub002(0x0000141eU, 0x00c0001dU);
    RSIP.REG_0014H.WORD = 0x000000a5U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
    r_rsip_func073_sub001(0x001e000aU, 0x00140000U, 0x0404000aU);
    r_rsip_func073_sub001(0x00690014U, 0x00190000U, 0x0404000aU);
    RSIP.REG_0040H.WORD = 0x00210000U;
    r_rsip_func073_sub001(0x001e0069U, 0x00190000U, 0x0404000aU);
    RSIP.REG_0040H.WORD = 0x00210000U;
    r_rsip_func073_sub001(0x006e0014U, 0x00190000U, 0x0404000aU);
    RSIP.REG_0040H.WORD = 0x00210000U;
    r_rsip_func073_sub001(0x001e006eU, 0x00190000U, 0x0404000aU);
    RSIP.REG_0040H.WORD = 0x00210000U;
    r_rsip_func100(0x7ac0587dU, 0x6075522aU, 0xef89dda1U, 0xd94e952fU);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        RSIP.REG_0094H.WORD = 0x00000800U;
        r_rsip_func101(0x2fa51911U, 0x63e5eaeaU, 0x6a633c5aU, 0x9193a074U);
    }
    else
    {
        r_rsip_func100(0x5b936a00U, 0xaac05c83U, 0xcd004503U, 0x20a393d3U);
        r_rsip_func073_sub001(0x001e0014U, 0x00190000U, 0x0404000aU);
        RSIP.REG_00B4H.WORD = 0x0019006eU;
        RSIP.REG_00B8H.WORD = 0x000f000aU;
        RSIP.REG_00A4H.WORD = 0x04040000U;
        RSIP.REG_0008H.WORD = 0x00020000U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        RSIP.REG_0040H.WORD = 0x00000d00U;
        r_rsip_func073_sub001(0x005a000fU, 0x0014000aU, 0x04040002U);
        r_rsip_func073_sub002(0x00001423U, 0x00c00021U);
        r_rsip_func073_sub001(0x0023007eU, 0x000f0000U, 0x04040009U);
        r_rsip_func073_sub001(0x0014000fU, 0x000f000aU, 0x04040002U);
        r_rsip_func073_sub001(0x00140069U, 0x0032000aU, 0x04040002U);
        RSIP.REG_00B8H.WORD = 0x00000005U;
        RSIP.REG_00A4H.WORD = 0x04040010U;
        RSIP.REG_00A0H.WORD = 0x20010001U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_00A8H.BIT.B0)
        {
            /* waiting */
        }
        RSIP.REG_00ACH.WORD = 0x00000001U;
        r_rsip_func073_sub001(0x00230069U, 0x000a0000U, 0x04040009U);
        r_rsip_func073_sub001(0x00370076U, 0x004b0005U, 0x04040002U);
        r_rsip_func073_sub001(0x0037007aU, 0x00500005U, 0x04040002U);
        r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
        RSIP.REG_0014H.WORD = 0x000000a5U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
        r_rsip_func073_sub001(0x00140037U, 0x00550005U, 0x04040002U);
        r_rsip_func073_sub001(0x0023005fU, 0x00280000U, 0x04040009U);
        r_rsip_func073_sub001(0x00230005U, 0x002d0000U, 0x04040009U);
        r_rsip_func073_sub002(0x00000415U, 0x00c00009U);
        r_rsip_func073_sub002(0x0000041aU, 0x00c00009U);
        r_rsip_func071(ARG1);
        r_rsip_func073_sub001(0x00230019U, 0x005a0000U, 0x04040009U);
        r_rsip_func073_sub001(0x0023001eU, 0x005f0000U, 0x04040009U);
        r_rsip_func073_sub001(0x00230055U, 0x00640000U, 0x04040009U);
        r_rsip_func073_sub001(0x004b005aU, 0x00140000U, 0x0404000aU);
        RSIP.REG_0040H.WORD = 0x00210000U;
        r_rsip_func073_sub001(0x005a004bU, 0x00140000U, 0x0404000aU);
        RSIP.REG_0040H.WORD = 0x00210000U;
        r_rsip_func073_sub001(0x0050005fU, 0x00140000U, 0x0404000aU);
        RSIP.REG_0040H.WORD = 0x00210000U;
        r_rsip_func073_sub001(0x005f0050U, 0x00140000U, 0x0404000aU);
        RSIP.REG_0040H.WORD = 0x00210000U;
        r_rsip_func100(0x2374ebeaU, 0xca2653aeU, 0x0986f925U, 0x8c6a75daU);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func073_sub001(0x00550064U, 0x00730005U, 0x04040013U);
            RSIP.REG_0040H.WORD = 0x00000d00U;
            r_rsip_func101(0x54a15c77U, 0x4bca8315U, 0x3624074aU, 0x4dc9f021U);
        }
        else
        {
            r_rsip_func073_sub001(0x00000064U, 0x0073002dU, 0x04040014U);
            RSIP.REG_0040H.WORD = 0x00000d00U;
            r_rsip_func101(0x3e9e06efU, 0x5f3850bbU, 0x900de5c3U, 0xead4abf5U);
        }
        r_rsip_func073_sub001(0x0023000fU, 0x00370000U, 0x04040009U);
        r_rsip_func073_sub001(0x00190019U, 0x00190000U, 0x0404000aU);
        r_rsip_func073_sub001(0x001e001eU, 0x001e0000U, 0x0404000aU);
        r_rsip_func073_sub001(0x00230023U, 0x00230000U, 0x0404000aU);
        RSIP.REG_0094H.WORD = 0x00000800U;
        for (iLoop = 0; iLoop < 2; iLoop = iLoop + 1)
        {
            RSIP.REG_0094H.WORD = 0x000008a5U;
            RSIP.REG_0094H.WORD = 0x38000c00U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00260000U;
            r_rsip_func100(0xe0262596U, 0xebd6e7d7U, 0xce5a0a1dU, 0x72134269U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func073_sub003(0x00000834U);
                RSIP.REG_0094H.WORD = 0x0000a4a0U;
                RSIP.REG_0094H.WORD = 0x00000008U;
                r_rsip_func073_sub003(0x00000835U);
                RSIP.REG_0094H.WORD = 0x0000a4a0U;
                RSIP.REG_0094H.WORD = 0x00000008U;
                r_rsip_func073_sub003(0x0000082fU);
                RSIP.REG_0094H.WORD = 0x0000a4a0U;
                RSIP.REG_0094H.WORD = 0x00000008U;
                r_rsip_func073_sub003(0x00000830U);
                r_rsip_func101(0x3844a0baU, 0x8544acf0U, 0x9408f56bU, 0xe22cce87U);
            }
            else
            {
                r_rsip_func073_sub003(0x00000836U);
                RSIP.REG_0094H.WORD = 0x0000a4a0U;
                RSIP.REG_0094H.WORD = 0x00000008U;
                r_rsip_func073_sub003(0x00000837U);
                RSIP.REG_0094H.WORD = 0x0000a4a0U;
                RSIP.REG_0094H.WORD = 0x00000008U;
                r_rsip_func073_sub003(0x00000831U);
                RSIP.REG_0094H.WORD = 0x0000a4a0U;
                RSIP.REG_0094H.WORD = 0x00000008U;
                r_rsip_func073_sub003(0x00000832U);
                r_rsip_func101(0x703a2d19U, 0x91eb7a1bU, 0xdc66074aU, 0x7e8a3361U);
            }
            RSIP.REG_0094H.WORD = 0x00000821U;
            for (jLoop = 0; jLoop < 4; jLoop = jLoop + 1)
            {
                RSIP.REG_0094H.WORD = 0x000034a1U;
                RSIP.REG_0094H.WORD = 0x00026ca5U;
                RSIP.REG_0094H.WORD = 0x00003865U;
                RSIP.REG_0094H.WORD = 0x0000a4a0U;
                RSIP.REG_0094H.WORD = 0x00000010U;
                RSIP.REG_0094H.WORD = 0x00003885U;
                RSIP.REG_0094H.WORD = 0x00000842U;
                for (kLoop = 0; kLoop < 32; kLoop = kLoop + 1)
                {
                    RSIP.REG_0094H.WORD = 0x000008a5U;
                    RSIP.REG_0094H.WORD = 0x01816ca3U;
                    RSIP.REG_0094H.WORD = 0x01816ca4U;
                    RSIP.REG_0094H.WORD = 0x00016c63U;
                    RSIP.REG_0094H.WORD = 0x00016c84U;
                    r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
                    RSIP.REG_0014H.WORD = 0x000000a5U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
                    r_rsip_func073_sub001(0x00140019U, 0x000f0000U, 0x0404000aU);
                    RSIP.REG_0040H.WORD = 0x00a10000U;
                    r_rsip_func073_sub001(0x00140023U, 0x000f0000U, 0x0404000aU);
                    RSIP.REG_0040H.WORD = 0x00a10000U;
                    r_rsip_func100(0x57dc3b0cU, 0x351d8141U, 0x319fdd43U, 0xd155baecU);
                    RSIP.REG_0040H.WORD = 0x00400000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    if (1U == (RSIP.REG_0040H.BIT.B22))
                    {
                        r_rsip_func073_sub001(0x00000023U, 0x0023002dU, 0x04040014U);
                        RSIP.REG_0040H.WORD = 0x00000d00U;
                        r_rsip_func101(0xe57cc178U, 0x3faa92afU, 0x916102ffU, 0x5a44e8e5U);
                    }
                    else
                    {
                        r_rsip_func101(0x5ab5b764U, 0x68c61a52U, 0xc889f563U, 0x06c19fc1U);
                    }
                    RSIP.REG_0094H.WORD = 0x38000ca5U;
                    RSIP.REG_009CH.WORD = 0x00000080U;
                    RSIP.REG_0040H.WORD = 0x00A60000U;
                    r_rsip_func100(0x8725f026U, 0xc0d4a86bU, 0x7c6dd55dU, 0x3514fbc9U);
                    RSIP.REG_0040H.WORD = 0x00400000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    if (1U == (RSIP.REG_0040H.BIT.B22))
                    {
                        r_rsip_func100(0xa16824f0U, 0xf5d8ad23U, 0x2e42fd05U, 0x6f8f7bd0U);
                        r_rsip_func073_sub002(0x00001414U, 0x00c00021U);
                        RSIP.REG_0094H.WORD = 0x00007c05U;
                        RSIP.REG_0040H.WORD = 0x00600000U;
                        RSIP.REG_0024H.WORD = 0x00000000U;
                        if (0x00000001U == (RSIP.REG_0044H.WORD & 0xffffffffU))
                        {
                            r_rsip_func073_sub001(0x0014004bU, 0x003c0000U, 0x04040009U);
                            r_rsip_func073_sub001(0x00140050U, 0x00410000U, 0x04040009U);
                            r_rsip_func073_sub001(0x00140055U, 0x00460000U, 0x04040009U);
                            r_rsip_func101(0x1223dd93U, 0x5d994e65U, 0x79a8e037U, 0x6f08564dU);
                        }
                        else if (0x00000002U == (RSIP.REG_0044H.WORD & 0xffffffffU))
                        {
                            r_rsip_func073_sub001(0x0014005aU, 0x003c0000U, 0x04040009U);
                            r_rsip_func073_sub001(0x0014005fU, 0x00410000U, 0x04040009U);
                            r_rsip_func073_sub001(0x00140064U, 0x00460000U, 0x04040009U);
                            r_rsip_func101(0xd3c559deU, 0xe0270a14U, 0xe0d7592fU, 0xca0ddcaeU);
                        }
                        else if (0x00000003U == (RSIP.REG_0044H.WORD & 0xffffffffU))
                        {
                            r_rsip_func073_sub001(0x00140069U, 0x003c0000U, 0x04040009U);
                            r_rsip_func073_sub001(0x0014006eU, 0x00410000U, 0x04040009U);
                            r_rsip_func073_sub001(0x00140073U, 0x00460000U, 0x04040009U);
                            r_rsip_func101(0xb689239dU, 0xd00045c9U, 0x3867b5abU, 0x2aa1147fU);
                        }
                        r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
                        RSIP.REG_0014H.WORD = 0x000000a5U;
                        /* WAIT_LOOP */
                        while (1U != RSIP.REG_0014H.BIT.B31)
                        {
                            /* waiting */
                        }
                        RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
                        r_rsip_func073_sub001(0x00140019U, 0x000f0000U, 0x0404000aU);
                        RSIP.REG_0040H.WORD = 0x00a10000U;
                        r_rsip_func073_sub001(0x00140023U, 0x000f0000U, 0x0404000aU);
                        RSIP.REG_0040H.WORD = 0x00a10000U;
                        r_rsip_func100(0x91c71aa9U, 0xf59a96d3U, 0x9b4156f9U, 0x03c7f5e3U);
                        RSIP.REG_0040H.WORD = 0x00400000U;
                        RSIP.REG_0024H.WORD = 0x00000000U;
                        if (1U == (RSIP.REG_0040H.BIT.B22))
                        {
                            r_rsip_func073_sub001(0x0014003cU, 0x000f0000U, 0x0404000aU);
                            RSIP.REG_0040H.WORD = 0x00a10000U;
                            r_rsip_func073_sub001(0x00140046U, 0x000f0000U, 0x0404000aU);
                            RSIP.REG_0040H.WORD = 0x00a10000U;
                            r_rsip_func100(0xbf88f894U, 0x4be0d849U, 0x79e5b438U, 0x1135ad24U);
                            RSIP.REG_0040H.WORD = 0x00400000U;
                            RSIP.REG_0024H.WORD = 0x00000000U;
                            if (1U == (RSIP.REG_0040H.BIT.B22))
                            {
                                r_rsip_func073_sub001(0x003c0019U, 0x000f0000U, 0x0404000aU);
                                RSIP.REG_0040H.WORD = 0x00210000U;
                                r_rsip_func073_sub001(0x0019003cU, 0x000f0000U, 0x0404000aU);
                                RSIP.REG_0040H.WORD = 0x00210000U;
                                r_rsip_func073_sub001(0x0041001eU, 0x000f0000U, 0x0404000aU);
                                RSIP.REG_0040H.WORD = 0x00210000U;
                                r_rsip_func073_sub001(0x001e0041U, 0x000f0000U, 0x0404000aU);
                                RSIP.REG_0040H.WORD = 0x00210000U;
                                r_rsip_func073_sub001(0x00460023U, 0x000f0000U, 0x0404000aU);
                                RSIP.REG_0040H.WORD = 0x00210000U;
                                r_rsip_func073_sub001(0x00230046U, 0x000f0000U, 0x0404000aU);
                                RSIP.REG_0040H.WORD = 0x00210000U;
                                r_rsip_func100(0xa41545d8U, 0x2a735aa4U, 0x7d8eb40bU, 0xe2e2c52bU);
                                RSIP.REG_0040H.WORD = 0x00400000U;
                                RSIP.REG_0024H.WORD = 0x00000000U;
                                if (1U == (RSIP.REG_0040H.BIT.B22))
                                {
                                    r_rsip_func073_sub001(0x00460023U, 0x00230005U, 0x04040013U);
                                    RSIP.REG_0040H.WORD = 0x00000d00U;
                                    r_rsip_func101(0x645af7d5U, 0xb699660fU, 0x1b4618b2U, 0xdefcd33aU);
                                }
                                else
                                {
                                    r_rsip_func073_sub001(0x00000023U, 0x0023002dU, 0x04040014U);
                                    RSIP.REG_0040H.WORD = 0x00000d00U;
                                    r_rsip_func101(0xf7035200U, 0x9af7e491U, 0x005e1b3fU, 0x00263252U);
                                }
                            }
                            else
                            {
                                r_rsip_func101(0xee7c0289U, 0x821c27ddU, 0x1ab662b4U, 0xf3d94d63U);
                            }
                        }
                        else
                        {
                            r_rsip_func073_sub002(0x00001414U, 0x00c00021U);
                            r_rsip_func073_sub001(0x0014003cU, 0x00190000U, 0x04040009U);
                            r_rsip_func073_sub001(0x00140041U, 0x001e0000U, 0x04040009U);
                            r_rsip_func073_sub001(0x00140046U, 0x00230000U, 0x04040009U);
                            r_rsip_func101(0xee6b7feaU, 0x2c6f7566U, 0xc5b4d482U, 0xb0902552U);
                        }
                    }
                    else
                    {
                        r_rsip_func101(0x1a135c7cU, 0x8905be2bU, 0xd1d66250U, 0xb6bca453U);
                    }
                    RSIP.REG_0094H.WORD = 0x00002c40U;
                    r_rsip_func101(0x626ecb0bU, 0x12e61bc6U, 0x100f1023U, 0x9f066464U);
                }
                RSIP.REG_0094H.WORD = 0x38008840U;
                RSIP.REG_0094H.WORD = 0x00000020U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                RSIP.REG_0040H.WORD = 0x00402000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                RSIP.REG_0094H.WORD = 0x00002c20U;
                r_rsip_func101(0x481fb7d3U, 0xb1c2594aU, 0x5e9b1dd9U, 0x055abe1cU);
            }
            RSIP.REG_0094H.WORD = 0x38008820U;
            RSIP.REG_0094H.WORD = 0x00000004U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00260000U;
            RSIP.REG_0040H.WORD = 0x00402000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            RSIP.REG_0094H.WORD = 0x00002c00U;
            r_rsip_func101(0x76cfc671U, 0xa4260128U, 0x570c8d00U, 0x752f580dU);
        }
        RSIP.REG_0094H.WORD = 0x38008800U;
        RSIP.REG_0094H.WORD = 0x00000002U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00260000U;
        RSIP.REG_0040H.WORD = 0x00402000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        r_rsip_func073_sub002(0x00001414U, 0x00c00021U);
        r_rsip_func073_sub001(0x0014000aU, 0x00690000U, 0x04040009U);
        r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
        RSIP.REG_0014H.WORD = 0x000000a5U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x00000001U);
        r_rsip_func073_sub001(0x00140023U, 0x002d0000U, 0x0404000aU);
        RSIP.REG_0040H.WORD = 0x00210000U;
        r_rsip_func100(0x052e8275U, 0x34a15ec7U, 0x18434e89U, 0x9cf8bf29U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            RSIP.REG_0094H.WORD = 0x00000800U;
            r_rsip_func101(0x4625ec81U, 0x1a2e2615U, 0xc016e306U, 0xcad776a6U);
        }
        else
        {
            r_rsip_func100(0x9ddfcb36U, 0xb1de4bf0U, 0x17a6e8b8U, 0xdaec720cU);
            r_rsip_func073_sub001(0x00140023U, 0x00280005U, 0x04040002U);
            r_rsip_func073_sub002(0x00001414U, 0x00c0001dU);
            RSIP.REG_0014H.WORD = 0x000000a5U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000002U);
            r_rsip_func073_sub001(0x00140005U, 0x000f0000U, 0x0404000aU);
            RSIP.REG_00B4H.WORD = 0x000f0028U;
            RSIP.REG_00B8H.WORD = 0x00140005U;
            RSIP.REG_00A4H.WORD = 0x04040000U;
            RSIP.REG_0008H.WORD = 0x00020000U;
            RSIP.REG_00A0H.WORD = 0x20010001U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_00A8H.BIT.B0)
            {
                /* waiting */
            }
            RSIP.REG_00ACH.WORD = 0x00000001U;
            RSIP.REG_0040H.WORD = 0x00000d00U;
            r_rsip_func073_sub001(0x00140019U, 0x00280005U, 0x04040002U);
            r_rsip_func073_sub001(0x00690028U, 0x00190000U, 0x0404000aU);
            RSIP.REG_0040H.WORD = 0x00210000U;
            r_rsip_func073_sub001(0x00280069U, 0x00190000U, 0x0404000aU);
            RSIP.REG_0040H.WORD = 0x00210000U;
            r_rsip_func100(0xbde95c34U, 0xbba81e06U, 0xefc26d4dU, 0x80700687U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                RSIP.REG_0094H.WORD = 0x00000800U;
                r_rsip_func101(0xf60a8844U, 0x85da504dU, 0xf02db763U, 0x264dfdd5U);
            }
            else
            {
                RSIP.REG_0094H.WORD = 0x0000b400U;
                RSIP.REG_0094H.WORD = 0x3070de88U;
                r_rsip_func101(0x15c6a3c1U, 0xc2874755U, 0x48888a40U, 0xd222e803U);
            }
        }
    }
    RSIP.REG_0094H.WORD = 0x38008800U;
    RSIP.REG_0094H.WORD = 0x3070de88U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00A60000U;
    RSIP.REG_0094H.WORD = 0x00007c07U;
    RSIP.REG_0040H.WORD = 0x00602000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
}
