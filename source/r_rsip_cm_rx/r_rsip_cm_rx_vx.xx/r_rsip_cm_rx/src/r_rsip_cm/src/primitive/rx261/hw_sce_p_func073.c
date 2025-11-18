/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "hw_sce_rx_private.h"
#include "hw_sce_sub_func.h"

void HW_SCE_p_func073 (const uint32_t ARG1[])
{
    uint32_t iLoop = 0U;
    uint32_t jLoop = 0U;
    uint32_t kLoop = 0U;

    HW_SCE_p_func070(ARG1);

    WR1_PROG(REG_00A0H, 0x20010000U);

    WR1_PROG(REG_00B8H, 0x0000000aU);

    WR1_PROG(REG_00A4H, 0x04040010U);

    WR1_PROG(REG_00A0H, 0x20010001U);
    WAIT_STS(REG_00A8H, 0, 1);
    WR1_PROG(REG_00ACH, 0x00000001U);

    HW_SCE_p_func073_sub003(0x0000141eU, 0x00c0001dU);
    WR1_PROG(REG_0014H, 0x000000a5U);
    WAIT_STS(REG_0014H, 31, 1);
    WR1_PROG(REG_002CH, change_endian_long(0x00000001U));

    HW_SCE_p_func073_sub001(0x001e000aU, 0x00140000U, 0x0404000aU);
    HW_SCE_p_func073_sub001(0x00690014U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_0040H, 0x00210000U);

    HW_SCE_p_func073_sub001(0x001e0069U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_0040H, 0x00210000U);

    HW_SCE_p_func073_sub001(0x006e0014U, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_0040H, 0x00210000U);

    HW_SCE_p_func073_sub001(0x001e006eU, 0x00190000U, 0x0404000aU);

    WR1_PROG(REG_0040H, 0x00210000U);

    HW_SCE_p_func100(0x96707843U, 0xf0e8a3b4U, 0x99acd4a9U, 0x7c332f65U);
    WR1_PROG(REG_0040H, 0x00400000U);
    WR1_PROG(REG_0024H, 0x00000000U);

    if (CHCK_STS(REG_0040H, 22, 1))
    {
        WR1_PROG(REG_0094H, 0x00000800U);

        HW_SCE_p_func101(0x461edcd2U, 0xf49dffe3U, 0xc7ee28deU, 0x6b2e0349U);
    }
    else
    {
        HW_SCE_p_func100(0x7b19f51cU, 0x11d3d6f6U, 0xfcd9bae7U, 0xd70e7b9eU);

        HW_SCE_p_func073_sub001(0x001e0014U, 0x00190000U, 0x0404000aU);

        WR1_PROG(REG_00B4H, 0x0019006eU);
        WR1_PROG(REG_00B8H, 0x000f000aU);

        WR1_PROG(REG_00A4H, 0x04040000U);
        WR1_PROG(REG_0008H, 0x00020000U);
        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);
        WR1_PROG(REG_0040H, 0x00000d00U);

        HW_SCE_p_func073_sub001(0x005a000fU, 0x0014000aU, 0x04040002U);

        HW_SCE_p_func073_sub003(0x00001423U, 0x00c00021U);

        HW_SCE_p_func073_sub001(0x00230072U, 0x000f0000U, 0x04040009U);

        HW_SCE_p_func073_sub001(0x0014000fU, 0x000f000aU, 0x04040002U);

        HW_SCE_p_func073_sub001(0x00140069U, 0x0032000aU, 0x04040002U);

        WR1_PROG(REG_00B8H, 0x00000005U);

        WR1_PROG(REG_00A4H, 0x04040010U);

        WR1_PROG(REG_00A0H, 0x20010001U);
        WAIT_STS(REG_00A8H, 0, 1);
        WR1_PROG(REG_00ACH, 0x00000001U);

        HW_SCE_p_func073_sub001(0x00230069U, 0x000a0000U, 0x04040009U);

        HW_SCE_p_func073_sub001(0x00370076U, 0x004b0005U, 0x04040002U);

        HW_SCE_p_func073_sub001(0x0037007aU, 0x00500005U, 0x04040002U);

        HW_SCE_p_func073_sub003(0x00001414U, 0x00c0001dU);

        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000001U));

        HW_SCE_p_func073_sub001(0x00140037U, 0x00550005U, 0x04040002U);

        HW_SCE_p_func073_sub001(0x0023005fU, 0x00280000U, 0x04040009U);

        HW_SCE_p_func073_sub001(0x00230005U, 0x002d0000U, 0x04040009U);

        HW_SCE_p_func073_sub003(0x00000415U, 0x00c00009U);

        HW_SCE_p_func073_sub003(0x0000041aU, 0x00c00009U);

        HW_SCE_p_func071(ARG1);

        HW_SCE_p_func073_sub001(0x00230019U, 0x005a0000U, 0x04040009U);

        HW_SCE_p_func073_sub001(0x0023001eU, 0x005f0000U, 0x04040009U);

        HW_SCE_p_func073_sub001(0x00230055U, 0x00640000U, 0x04040009U);

        HW_SCE_p_func073_sub003(0x0000046fU, 0x00c00009U);

        HW_SCE_p_func073_sub001(0x004b005aU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        HW_SCE_p_func073_sub001(0x005a004bU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        HW_SCE_p_func073_sub001(0x0050005fU, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        HW_SCE_p_func073_sub001(0x005f0050U, 0x00140000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        HW_SCE_p_func100(0x81742749U, 0x678b86e7U, 0x224da4abU, 0x71fa78aeU);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            HW_SCE_p_func073_sub001(0x00550064U, 0x00730005U, 0x04040013U);

            WR1_PROG(REG_0040H, 0x00000d00U);

            HW_SCE_p_func101(0x4c2d21d4U, 0xe475db33U, 0x683ff184U, 0xedda1049U);
        }
        else
        {
            HW_SCE_p_func073_sub001(0x00000064U, 0x0073002dU, 0x04040014U);

            WR1_PROG(REG_0040H, 0x00000d00U);

            HW_SCE_p_func101(0xd495c2fcU, 0xa26bbe07U, 0xa4dc38ebU, 0x7372a4c5U);
        }

        HW_SCE_p_func073_sub001(0x0023000fU, 0x00370000U, 0x04040009U);

        HW_SCE_p_func073_sub001(0x00190019U, 0x00190000U, 0x0404000aU);

        HW_SCE_p_func073_sub001(0x001e001eU, 0x001e0000U, 0x0404000aU);

        HW_SCE_p_func073_sub001(0x00230023U, 0x00230000U, 0x0404000aU);

        WR1_PROG(REG_0094H, 0x00000800U);
        for (iLoop = 0U; iLoop < 2U; iLoop++)
        {
            WR1_PROG(REG_0094H, 0x000008a5U);

            WR1_PROG(REG_0094H, 0x38000c00U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);

            HW_SCE_p_func100(0x97a7743dU, 0x99736c8eU, 0x2a1e19e8U, 0x6142b08fU);
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                HW_SCE_p_func073_sub002(0x00000834U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                HW_SCE_p_func073_sub002(0x00000835U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                HW_SCE_p_func073_sub002(0x0000082fU);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                HW_SCE_p_func073_sub002(0x00000830U);

                HW_SCE_p_func101(0x18391f0aU, 0x9434f682U, 0x1d37c544U, 0x2eb285d9U);
            }
            else
            {
                HW_SCE_p_func073_sub002(0x00000836U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                HW_SCE_p_func073_sub002(0x00000837U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                HW_SCE_p_func073_sub002(0x00000831U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000008U);

                HW_SCE_p_func073_sub002(0x00000832U);

                HW_SCE_p_func101(0xa02ea37cU, 0x753b1906U, 0x8b02332bU, 0xf9b994d7U);
            }

            WR1_PROG(REG_0094H, 0x00000821U);

            for (jLoop = 0U; jLoop < 4; jLoop++)
            {
                WR1_PROG(REG_0094H, 0x000034a1U);

                WR1_PROG(REG_0094H, 0x00026ca5U);

                WR1_PROG(REG_0094H, 0x00003865U);

                WR1_PROG(REG_0094H, 0x0000a4a0U);
                WR1_PROG(REG_0094H, 0x00000010U);

                WR1_PROG(REG_0094H, 0x00003885U);

                WR1_PROG(REG_0094H, 0x00000842U);

                for (kLoop = 0U; kLoop < 32U; kLoop++)
                {
                    WR1_PROG(REG_0094H, 0x000008a5U);

                    WR1_PROG(REG_0094H, 0x01816ca3U);
                    WR1_PROG(REG_0094H, 0x01816ca4U);
                    WR1_PROG(REG_0094H, 0x00016c63U);
                    WR1_PROG(REG_0094H, 0x00016c84U);

                    WR1_PROG(REG_0094H, 0x38000ca5U);
                    WR1_PROG(REG_009CH, 0x00000080U);
                    WR1_PROG(REG_0040H, 0x00A60000U);

                    HW_SCE_p_func100(0x587bbb83U, 0x0022ea55U, 0x372910e8U, 0x252d8dd4U);
                    WR1_PROG(REG_0040H, 0x00400000U);
                    WR1_PROG(REG_0024H, 0x00000000U);

                    if (CHCK_STS(REG_0040H, 22, 1))
                    {
                        HW_SCE_p_func100(0x8789c53fU, 0xa4604616U, 0x276b43b3U, 0xe05d8418U);

                        HW_SCE_p_func073_sub003(0x00001414U, 0x00c00021U);

                        WR1_PROG(REG_0094H, 0x00007c05U);
                        WR1_PROG(REG_0040H, 0x00600000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000001U)
                        {
                            HW_SCE_p_func073_sub001(0x0014004bU, 0x003c0000U, 0x04040009U);

                            HW_SCE_p_func073_sub001(0x00140050U, 0x00410000U, 0x04040009U);

                            HW_SCE_p_func073_sub001(0x00140055U, 0x00460000U, 0x04040009U);

                            HW_SCE_p_func101(0xf9241590U, 0x0e3ed9faU, 0x7b5102e8U, 0x28220df2U);
                        }
                        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000002U)
                        {
                            HW_SCE_p_func073_sub001(0x0014005aU, 0x003c0000U, 0x04040009U);

                            HW_SCE_p_func073_sub001(0x0014005fU, 0x00410000U, 0x04040009U);

                            HW_SCE_p_func073_sub001(0x00140064U, 0x00460000U, 0x04040009U);

                            HW_SCE_p_func101(0xde6d47c4U, 0x036ba384U, 0x669ed9a3U, 0xb47ced65U);
                        }
                        else if (RD1_MASK(REG_0044H, 0xffffffffU) == 0x00000003U)
                        {
                            HW_SCE_p_func073_sub001(0x00140069U, 0x003c0000U, 0x04040009U);

                            HW_SCE_p_func073_sub001(0x0014006eU, 0x00410000U, 0x04040009U);

                            HW_SCE_p_func073_sub001(0x00140073U, 0x00460000U, 0x04040009U);

                            HW_SCE_p_func101(0xbafeaaacU, 0xac3a80cdU, 0xf44b0441U, 0x94da01fcU);
                        }

                        HW_SCE_p_func073_sub003(0x00001414U, 0x00c0001dU);

                        WR1_PROG(REG_0014H, 0x000000a5U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, change_endian_long(0x00000001U));

                        HW_SCE_p_func073_sub001(0x00140019U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        HW_SCE_p_func073_sub001(0x00140023U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        HW_SCE_p_func100(0xc8ff75bdU, 0x67f58e57U, 0x9b6b6986U, 0xabfcb44aU);
                        WR1_PROG(REG_0040H, 0x00400000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {                           
                            HW_SCE_p_func073_sub001(0x00000023U, 0x0023002dU, 0x04040014U);

                            WR1_PROG(REG_0040H, 0x00000d00U);

                            HW_SCE_p_func073_sub001(0x0014003cU, 0x000f0000U, 0x0404000aU);

                            WR1_PROG(REG_0040H, 0x00a10000U);

                            HW_SCE_p_func073_sub001(0x00140046U, 0x000f0000U, 0x0404000aU);

                            WR1_PROG(REG_0040H, 0x00a10000U);

                            HW_SCE_p_func100(0x4646ea6eU, 0x9000bdcfU, 0x6786791bU, 0x2a7d6b46U);
                            WR1_PROG(REG_0040H, 0x00400000U);
                            WR1_PROG(REG_0024H, 0x00000000U);

                            if (CHCK_STS(REG_0040H, 22, 1))
                            {
                                HW_SCE_p_func073_sub001(0x003c0019U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                HW_SCE_p_func073_sub001(0x0019003cU, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                HW_SCE_p_func073_sub001(0x0041001eU, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                HW_SCE_p_func073_sub001(0x001e0041U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                HW_SCE_p_func073_sub001(0x00460023U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                HW_SCE_p_func073_sub001(0x00230046U, 0x000f0000U, 0x0404000aU);

                                WR1_PROG(REG_0040H, 0x00210000U);

                                HW_SCE_p_func100(0xc61f3c33U, 0xfcb7c254U, 0xe84b2bacU, 0x333d4236U);
                                WR1_PROG(REG_0040H, 0x00400000U);
                                WR1_PROG(REG_0024H, 0x00000000U);

                                if (CHCK_STS(REG_0040H, 22, 1))
                                {
                                    HW_SCE_p_func073_sub001(0x00460023U, 0x00230005U, 0x04040013U);

                                    WR1_PROG(REG_0040H, 0x00000d00U);

                                    HW_SCE_p_func101(0xa67a402bU, 0xa733523aU, 0xc0d96ed4U, 0x7d9221f7U);
                                }
                                else
                                {
                                    HW_SCE_p_func073_sub001(0x00000023U, 0x0023002dU, 0x04040014U);

                                    WR1_PROG(REG_0040H, 0x00000d00U);

                                    HW_SCE_p_func101(0x20efed06U, 0x4ff03d6eU, 0x0218b88aU, 0x7a499288U);
                                }
                            }
                            else
                            {
                                HW_SCE_p_func101(0xd25d3ca3U, 0x251e100bU, 0x84599bc1U, 0x27b9ccd2U);
                            }
                        }
                        else
                        {
                            HW_SCE_p_func073_sub003(0x00001414U, 0x00c00021U);

                            HW_SCE_p_func073_sub001(0x0014003cU, 0x00190000U, 0x04040009U);

                            HW_SCE_p_func073_sub001(0x00140041U, 0x001e0000U, 0x04040009U);

                            HW_SCE_p_func073_sub001(0x00140046U, 0x00230000U, 0x04040009U);

                            HW_SCE_p_func101(0xdb780cc4U, 0x158f1fe3U, 0xe38fcabaU, 0x134eca37U);
                        }
                    }
                    else
                    {
                        HW_SCE_p_func073_sub003(0x00001414U, 0x00c0001dU);
                        WR1_PROG(REG_0014H, 0x000000a5U);
                        WAIT_STS(REG_0014H, 31, 1);
                        WR1_PROG(REG_002CH, change_endian_long(0x00000001U));

                        HW_SCE_p_func073_sub001(0x00140019U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        HW_SCE_p_func073_sub001(0x00140023U, 0x000f0000U, 0x0404000aU);

                        WR1_PROG(REG_0040H, 0x00a10000U);

                        HW_SCE_p_func100(0xf3fdcfe2U, 0x0585be02U, 0xdbec79f3U, 0x6f262f50U);
                        WR1_PROG(REG_0040H, 0x00400000U);
                        WR1_PROG(REG_0024H, 0x00000000U);

                        if (CHCK_STS(REG_0040H, 22, 1))
                        {
                            HW_SCE_p_func073_sub001(0x00000023U, 0x0023002dU, 0x04040014U);

                            WR1_PROG(REG_0040H, 0x00000d00U);

                            HW_SCE_p_func101(0xedf20355U, 0x73be5eb5U, 0x89b9faebU, 0x2a9543afU);
                        }
                        else
                        {
                            HW_SCE_p_func101(0x7e63e379U, 0x55aa9fe2U, 0xb25699f5U, 0x5a7cd6e5U);
                        }
                    }

                    WR1_PROG(REG_0094H, 0x00002c40U);
                    HW_SCE_p_func101(0x461b5f5fU, 0x67b0288fU, 0x705fa755U, 0x236afc80U);
                }

                WR1_PROG(REG_0094H, 0x38008840U);
                WR1_PROG(REG_0094H, 0x00000020U);
                WR1_PROG(REG_009CH, 0x00000080U);
                WR1_PROG(REG_0040H, 0x00260000U);

                WR1_PROG(REG_0040H, 0x00402000U);
                WR1_PROG(REG_0024H, 0x00000000U);

                WR1_PROG(REG_0094H, 0x00002c20U);

                HW_SCE_p_func101(0x8b659b51U, 0x90403728U, 0x1befae16U, 0x60de17f0U);
            }

            WR1_PROG(REG_0094H, 0x38008820U);
            WR1_PROG(REG_0094H, 0x00000004U);
            WR1_PROG(REG_009CH, 0x00000080U);
            WR1_PROG(REG_0040H, 0x00260000U);

            WR1_PROG(REG_0040H, 0x00402000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            WR1_PROG(REG_0094H, 0x00002c00U);

            HW_SCE_p_func101(0xa4f008abU, 0x4ebd8a80U, 0x0b27fd1aU, 0x59133c90U);
        }

        WR1_PROG(REG_0094H, 0x38008800U);
        WR1_PROG(REG_0094H, 0x00000002U);
        WR1_PROG(REG_009CH, 0x00000080U);
        WR1_PROG(REG_0040H, 0x00260000U);

        WR1_PROG(REG_0040H, 0x00402000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        HW_SCE_p_func073_sub003(0x00001414U, 0x00c00021U);

        HW_SCE_p_func073_sub001(0x0014000aU, 0x00690000U, 0x04040009U);

        HW_SCE_p_func073_sub003(0x00001414U, 0x00c0001dU);

        WR1_PROG(REG_0014H, 0x000000a5U);
        WAIT_STS(REG_0014H, 31, 1);
        WR1_PROG(REG_002CH, change_endian_long(0x00000001U));

        HW_SCE_p_func073_sub001(0x00140023U, 0x002d0000U, 0x0404000aU);

        WR1_PROG(REG_0040H, 0x00210000U);

        HW_SCE_p_func100(0xec821bfdU, 0x2c637115U, 0x8e8726dbU, 0x26e17208U);
        WR1_PROG(REG_0040H, 0x00400000U);
        WR1_PROG(REG_0024H, 0x00000000U);

        if (CHCK_STS(REG_0040H, 22, 1))
        {
            WR1_PROG(REG_0094H, 0x00000800U);

            HW_SCE_p_func101(0x845afecbU, 0x1e3cf8b3U, 0xa60bbf12U, 0x25eb4499U);
        }
        else
        {
            HW_SCE_p_func100(0x5543c832U, 0xaddf6c71U, 0x28946799U, 0xff20b5e1U);

            HW_SCE_p_func073_sub001(0x00140023U, 0x00280005U, 0x04040002U);

            HW_SCE_p_func073_sub003(0x00001414U, 0x00c0001dU);

            WR1_PROG(REG_0014H, 0x000000a5U);
            WAIT_STS(REG_0014H, 31, 1);
            WR1_PROG(REG_002CH, change_endian_long(0x00000002U));

            HW_SCE_p_func073_sub001(0x00140005U, 0x000f0000U, 0x0404000aU);

            WR1_PROG(REG_00B4H, 0x000f0028U);
            WR1_PROG(REG_00B8H, 0x00140005U);

            WR1_PROG(REG_00A4H, 0x04040000U);
            WR1_PROG(REG_0008H, 0x00020000U);
            WR1_PROG(REG_00A0H, 0x20010001U);
            WAIT_STS(REG_00A8H, 0, 1);
            WR1_PROG(REG_00ACH, 0x00000001U);
            WR1_PROG(REG_0040H, 0x00000d00U);

            HW_SCE_p_func073_sub001(0x00140019U, 0x00280005U, 0x04040002U);

            HW_SCE_p_func073_sub001(0x00690028U, 0x00190000U, 0x0404000aU);

            WR1_PROG(REG_0040H, 0x00210000U);

            HW_SCE_p_func073_sub001(0x00280069U, 0x00190000U, 0x0404000aU);

            WR1_PROG(REG_0040H, 0x00210000U);

            HW_SCE_p_func100(0x980a9850U, 0x1168a1b3U, 0x75c496c6U, 0x4908265bU);
            WR1_PROG(REG_0040H, 0x00400000U);
            WR1_PROG(REG_0024H, 0x00000000U);

            if (CHCK_STS(REG_0040H, 22, 1))
            {
                WR1_PROG(REG_0094H, 0x00000800U);

                HW_SCE_p_func101(0x64e43117U, 0x9024a6c6U, 0xcfeb8075U, 0x42f5f02eU);
            }
            else
            {
                WR1_PROG(REG_0094H, 0x0000b400U);
                WR1_PROG(REG_0094H, 0xfdec21a6U);

                HW_SCE_p_func101(0xcd2816fbU, 0x6aef2141U, 0xa979352bU, 0x0b3998b5U);
            }
        }
    }

    WR1_PROG(REG_0094H, 0x38008800U);
    WR1_PROG(REG_0094H, 0xfdec21a6U);
    WR1_PROG(REG_009CH, 0x00000080U);
    WR1_PROG(REG_0040H, 0x00A60000U);

    WR1_PROG(REG_0094H, 0x00007c07U);
    WR1_PROG(REG_0040H, 0x00602000U);
    WR1_PROG(REG_0024H, 0x00000000U);
}
