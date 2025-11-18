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

rsip_ret_t r_rsip_pef(const uint32_t InData_Msg1[], const uint32_t InData_Msg1Length[], const uint32_t InData_EncMsg[], const uint32_t InData_EncMsgLength[], const uint32_t InData_Msg2[], const uint32_t InData_Msg2Length[], uint32_t OutData_KDFInfo[])
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
    RSIP.REG_0070H.WORD = 0x00ef0001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    RSIP.REG_0014H.WORD = 0x000002c7U;
    RSIP.REG_009CH.WORD = 0x80030060U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_Msg1Length[0];
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_EncMsgLength[0];
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_Msg2Length[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0094H.WORD = 0x38008c80U;
    RSIP.REG_0094H.WORD = 0xffffffdfU;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00A60000U;
    RSIP.REG_0094H.WORD = 0x3420a8a0U;
    RSIP.REG_0094H.WORD = 0x00000009U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00260000U;
    RSIP.REG_0094H.WORD = 0x00000800U;
    RSIP.REG_0094H.WORD = 0x00002403U;
    RSIP.REG_0094H.WORD = 0x00002404U;
    RSIP.REG_0094H.WORD = 0x00002405U;
    RSIP.REG_0094H.WORD = 0x38008c00U;
    RSIP.REG_0094H.WORD = 0x0000003fU;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00A60000U;
    r_rsip_func100(0xa658c5a9U, 0xa071dfa5U, 0xc4a44101U, 0x636f10b8U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0x319b06a8U, 0x4a66080aU, 0xda4a8aacU, 0x906dabbeU);
        RSIP.REG_006CH.WORD = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0020H.BIT.B12)
        {
            /* waiting */
        }
        return RSIP_RET_FAIL;
    }
    else
    {
        RSIP.REG_0094H.WORD = 0x00000821U;
        RSIP.REG_0094H.WORD = 0x00003405U;
        RSIP.REG_0094H.WORD = 0x38000c84U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00A60000U;
        r_rsip_func100(0x34f6b6ddU, 0xaee58bc6U, 0x9bc0803cU, 0x23d6ebb5U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            RSIP.REG_0014H.WORD = 0x000000c7U;
            RSIP.REG_009CH.WORD = 0x800100c0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_EncMsg[0];
            RSIP.REG_0024H.WORD = 0x00000000U;
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x0000ef01U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0xc06f37e6U, 0x9f382d28U, 0xcd79f37aU, 0xe60aaba1U);
            r_rsip_func043();
            RSIP.REG_0094H.WORD = 0x0000b4c0U;
            RSIP.REG_0094H.WORD = 0x01799093U;
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x0000ef01U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x4f501f9bU, 0x3ed1cc77U, 0x6eac0086U, 0x7cc2e74aU);
            r_rsip_func044();
            RSIP.REG_0014H.WORD = 0x000007c1U;
            RSIP.REG_00D4H.WORD = 0x40000100U;
            RSIP.REG_00D0H.WORD = 0xf7009d07U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_EncMsg[1];
            RSIP.REG_002CH.WORD = InData_EncMsg[2];
            RSIP.REG_002CH.WORD = InData_EncMsg[3];
            RSIP.REG_002CH.WORD = InData_EncMsg[4];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_EncMsg[5];
            RSIP.REG_002CH.WORD = InData_EncMsg[6];
            RSIP.REG_002CH.WORD = InData_EncMsg[7];
            RSIP.REG_002CH.WORD = InData_EncMsg[8];
            RSIP.REG_00B0H.WORD = 0x00001404U;
            RSIP.REG_0000H.WORD = 0x00c10021U;
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
            RSIP.REG_002CH.WORD = InData_EncMsg[9];
            RSIP.REG_002CH.WORD = InData_EncMsg[10];
            RSIP.REG_002CH.WORD = InData_EncMsg[11];
            RSIP.REG_002CH.WORD = InData_EncMsg[12];
            RSIP.REG_00D0H.WORD = 0x9c100005U;
            RSIP.REG_0000H.WORD = 0x00410011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0xeaadc10dU, 0x0d9ab026U, 0x2d8d6625U, 0x9a48a354U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                RSIP.REG_0094H.WORD = 0x00002c20U;
                r_rsip_func101(0x8b7c511aU, 0x3955a113U, 0xab640492U, 0xcbcbd46fU);
            }
            r_rsip_func101(0xf3566e80U, 0x8a7665e9U, 0x3b1e9cfdU, 0xfab84b1fU);
        }
        RSIP.REG_0094H.WORD = 0x38000c21U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00A60000U;
        r_rsip_func100(0x3c7a7c54U, 0x4873dc31U, 0x232e775aU, 0xa6e81530U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0xd8b29ce9U, 0xd704c44cU, 0x1ccd5e5fU, 0x7cf87944U);
            RSIP.REG_006CH.WORD = 0x00000040U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0020H.BIT.B12)
            {
                /* waiting */
            }
            return RSIP_RET_FAIL;
        }
        else
        {
            RSIP.REG_00F4H.WORD = 0x00000010U;
            RSIP.REG_0014H.WORD = 0x000007a4U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x6a09e667U);
            RSIP.REG_002CH.WORD = bswap_32big(0xbb67ae85U);
            RSIP.REG_002CH.WORD = bswap_32big(0x3c6ef372U);
            RSIP.REG_002CH.WORD = bswap_32big(0xa54ff53aU);
            RSIP.REG_002CH.WORD = bswap_32big(0x510e527fU);
            RSIP.REG_002CH.WORD = bswap_32big(0x9b05688cU);
            RSIP.REG_002CH.WORD = bswap_32big(0x1f83d9abU);
            RSIP.REG_002CH.WORD = bswap_32big(0x5be0cd19U);
            RSIP.REG_00F4H.WORD = 0x00000011U;
            RSIP.REG_0094H.WORD = 0x00000821U;
            RSIP.REG_0094H.WORD = 0x00003c01U;
            RSIP.REG_0094H.WORD = 0x38000c63U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00A60000U;
            r_rsip_func100(0x76cc0c25U, 0x5982c393U, 0x5d756f29U, 0x25ce0532U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func100(0x31fb1f1cU, 0xf61a6397U, 0x88c429a2U, 0x105f6019U);
                RSIP.REG_0094H.WORD = 0x00000800U;
                RSIP.REG_0094H.WORD = 0x00003443U;
                RSIP.REG_0094H.WORD = 0x0000a440U;
                RSIP.REG_0094H.WORD = 0x00000003U;
                RSIP.REG_0094H.WORD = 0x00026842U;
                RSIP.REG_009CH.WORD = 0x81010040U;
                RSIP.REG_0008H.WORD = 0x00005006U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0008H.BIT.B30)
                {
                    /* waiting */
                }
                S_RAM[0] = bswap_32big(RSIP.REG_002CH.WORD);
                RSIP.REG_0094H.WORD = 0x000008a5U;
                RSIP.REG_0094H.WORD = 0x000008c6U;
                for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                {
                    RSIP.REG_0014H.WORD = 0x000000c7U;
                    RSIP.REG_009CH.WORD = 0x80010020U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = InData_Msg1[iLoop + 0];
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    RSIP.REG_0094H.WORD = 0x000008e7U;
                    for (jLoop = 0; jLoop < 4 ; jLoop = jLoop + 1)
                    {
                        RSIP.REG_0094H.WORD = 0x01886c01U;
                        RSIP.REG_0094H.WORD = 0x00086c21U;
                        RSIP.REG_0094H.WORD = 0x342028a3U;
                        RSIP.REG_009CH.WORD = 0x00000080U;
                        RSIP.REG_0040H.WORD = 0x00260000U;
                        r_rsip_func100(0x6ae05b23U, 0x866a55c4U, 0xd86962e6U, 0x3b3fb5c8U);
                        RSIP.REG_0040H.WORD = 0x00400000U;
                        RSIP.REG_0024H.WORD = 0x00000000U;
                        if (1U == (RSIP.REG_0040H.BIT.B22))
                        {
                            RSIP.REG_009CH.WORD = 0x81010000U;
                            RSIP.REG_0000H.WORD = 0x1009000dU;
                            /* WAIT_LOOP */
                            while (0U != RSIP.REG_0004H.BIT.B30)
                            {
                                /* waiting */
                            }
                            RSIP.REG_0040H.WORD = 0x00001800U;
                            RSIP.REG_0000H.WORD = 0x11490005U;
                            /* WAIT_LOOP */
                            while (0U != RSIP.REG_0004H.BIT.B30)
                            {
                                /* waiting */
                            }
                            RSIP.REG_0040H.WORD = 0x00001800U;
                            RSIP.REG_0094H.WORD = 0x00002ca0U;
                            r_rsip_func101(0xf6d5ac47U, 0x049dc908U, 0x1c7e28eeU, 0x3ad80315U);
                        }
                        RSIP.REG_0094H.WORD = 0x00002ce0U;
                        r_rsip_func101(0xa06df116U, 0xe16a9179U, 0x5f1d1de8U, 0x82cc4f56U);
                    }
                    RSIP.REG_0094H.WORD = 0x380088e0U;
                    RSIP.REG_0094H.WORD = 0x00000004U;
                    RSIP.REG_009CH.WORD = 0x00000080U;
                    RSIP.REG_0040H.WORD = 0x00260000U;
                    RSIP.REG_0040H.WORD = 0x00402000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    RSIP.REG_0094H.WORD = 0x00002cc0U;
                    r_rsip_func101(0x206d8c79U, 0xe0ba7275U, 0x0ccccceaU, 0xaf9919fbU);
                }
                RSIP.REG_0094H.WORD = 0x380008c2U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                RSIP.REG_0040H.WORD = 0x00402000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                r_rsip_func101(0x8e28a04eU, 0xcf72c4faU, 0x19f7d763U, 0x35f04fffU);
            }
            RSIP.REG_0094H.WORD = 0x38000c84U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00A60000U;
            r_rsip_func100(0x574e4993U, 0xacf6921aU, 0xbc1e353bU, 0x1adf9fceU);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                RSIP.REG_00B0H.WORD = 0x00001804U;
                RSIP.REG_0000H.WORD = 0x11430081U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                r_rsip_func101(0x95e61187U, 0xbcb9b454U, 0xb9db1918U, 0x1b4eb763U);
            }
            RSIP.REG_0094H.WORD = 0x00000821U;
            RSIP.REG_0094H.WORD = 0x00003861U;
            r_rsip_func100(0xe5c7c5b0U, 0xe8906fa6U, 0x0e0680cdU, 0x862b3eaaU);
            RSIP.REG_0094H.WORD = 0x00000800U;
            RSIP.REG_0094H.WORD = 0x00003443U;
            RSIP.REG_0094H.WORD = 0x0000a440U;
            RSIP.REG_0094H.WORD = 0x00000003U;
            RSIP.REG_0094H.WORD = 0x00026842U;
            RSIP.REG_009CH.WORD = 0x81010040U;
            RSIP.REG_0008H.WORD = 0x00005006U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0008H.BIT.B30)
            {
                /* waiting */
            }
            S_RAM[0] = bswap_32big(RSIP.REG_002CH.WORD);
            RSIP.REG_0094H.WORD = 0x000008a5U;
            RSIP.REG_0094H.WORD = 0x000008c6U;
            for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                RSIP.REG_0014H.WORD = 0x000000c7U;
                RSIP.REG_009CH.WORD = 0x80010020U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0014H.BIT.B31)
                {
                    /* waiting */
                }
                RSIP.REG_002CH.WORD = InData_Msg2[iLoop + 0];
                RSIP.REG_0024H.WORD = 0x00000000U;
                RSIP.REG_0094H.WORD = 0x000008e7U;
                for (jLoop = 0; jLoop < 4 ; jLoop = jLoop + 1)
                {
                    RSIP.REG_0094H.WORD = 0x01886c01U;
                    RSIP.REG_0094H.WORD = 0x00086c21U;
                    RSIP.REG_0094H.WORD = 0x342028a3U;
                    RSIP.REG_009CH.WORD = 0x00000080U;
                    RSIP.REG_0040H.WORD = 0x00260000U;
                    r_rsip_func100(0x10c6acd8U, 0x4de1ed32U, 0x4094d9f9U, 0x746e2d84U);
                    RSIP.REG_0040H.WORD = 0x00400000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    if (1U == (RSIP.REG_0040H.BIT.B22))
                    {
                        RSIP.REG_009CH.WORD = 0x81010000U;
                        RSIP.REG_0000H.WORD = 0x1009000dU;
                        /* WAIT_LOOP */
                        while (0U != RSIP.REG_0004H.BIT.B30)
                        {
                            /* waiting */
                        }
                        RSIP.REG_0040H.WORD = 0x00001800U;
                        RSIP.REG_0000H.WORD = 0x11490005U;
                        /* WAIT_LOOP */
                        while (0U != RSIP.REG_0004H.BIT.B30)
                        {
                            /* waiting */
                        }
                        RSIP.REG_0040H.WORD = 0x00001800U;
                        RSIP.REG_0094H.WORD = 0x00002ca0U;
                        r_rsip_func101(0x8c425362U, 0xcbf50632U, 0x4f1036e5U, 0x3f05f5d6U);
                    }
                    RSIP.REG_0094H.WORD = 0x00002ce0U;
                    r_rsip_func101(0x5079e2fcU, 0x8277ced0U, 0x551dca5cU, 0x46026b17U);
                }
                RSIP.REG_0094H.WORD = 0x380088e0U;
                RSIP.REG_0094H.WORD = 0x00000004U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                RSIP.REG_0040H.WORD = 0x00402000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                RSIP.REG_0094H.WORD = 0x00002cc0U;
                r_rsip_func101(0xa8ab82c6U, 0x3696a416U, 0xa539d78dU, 0x36e868faU);
            }
            RSIP.REG_0094H.WORD = 0x380008c2U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00260000U;
            RSIP.REG_0040H.WORD = 0x00402000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_00F8H.BIT.B2)
            {
                /* waiting */
            }
            RSIP.REG_00F4H.WORD = 0x00000100U;
            RSIP.REG_0040H.WORD = 0x00001600U;
            RSIP.REG_00F4H.WORD = 0x00000020U;
            r_rsip_func100(0xc9d864a1U, 0x93fcd3c5U, 0x383272c9U, 0xdd23cc05U);
            r_rsip_func103();
            RSIP.REG_0014H.WORD = 0x000000a1U;
            RSIP.REG_00D0H.WORD = 0x0c200104U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            RSIP.REG_009CH.WORD = 0x80010000U;
            RSIP.REG_0000H.WORD = 0x03410005U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_0000H.WORD = 0x0001000dU;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_0094H.WORD = 0x000034c0U;
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x0000ef02U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x09bc9721U, 0xb6bb3d17U, 0xd08e919dU, 0xbedb690bU);
            r_rsip_func043();
            RSIP.REG_0094H.WORD = 0x0000b4c0U;
            RSIP.REG_0094H.WORD = 0x01799093U;
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x0000ef02U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0xb45d43efU, 0xa9e8f77cU, 0x86c21e76U, 0x697f9df0U);
            r_rsip_func044();
            r_rsip_func100(0xc92fab64U, 0x19816850U, 0x906d1b6eU, 0x2221a04eU);
            RSIP.REG_0014H.WORD = 0x000000a1U;
            RSIP.REG_00D0H.WORD = 0x08000044U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            RSIP.REG_0014H.WORD = 0x000000a1U;
            RSIP.REG_00D0H.WORD = 0x08000054U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            RSIP.REG_00D4H.WORD = 0x40000100U;
            RSIP.REG_00D0H.WORD = 0xe7009d07U;
            RSIP.REG_0000H.WORD = 0x00450021U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_0008H.WORD = 0x00001022U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0008H.BIT.B30)
            {
                /* waiting */
            }
            OutData_KDFInfo[1] = RSIP.REG_002CH.WORD;
            OutData_KDFInfo[2] = RSIP.REG_002CH.WORD;
            OutData_KDFInfo[3] = RSIP.REG_002CH.WORD;
            OutData_KDFInfo[4] = RSIP.REG_002CH.WORD;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0008H.BIT.B30)
            {
                /* waiting */
            }
            OutData_KDFInfo[5] = RSIP.REG_002CH.WORD;
            OutData_KDFInfo[6] = RSIP.REG_002CH.WORD;
            OutData_KDFInfo[7] = RSIP.REG_002CH.WORD;
            OutData_KDFInfo[8] = RSIP.REG_002CH.WORD;
            r_rsip_func100(0x582a2d22U, 0x4acdfdfcU, 0x87e66ac7U, 0x319ae78fU);
            RSIP.REG_0014H.WORD = 0x000000a1U;
            RSIP.REG_00D0H.WORD = 0x0c000104U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            RSIP.REG_00D4H.WORD = 0x40000000U;
            RSIP.REG_00D0H.WORD = 0x09108105U;
            RSIP.REG_0000H.WORD = 0x00410011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            RSIP.REG_0008H.WORD = 0x00001012U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0008H.BIT.B30)
            {
                /* waiting */
            }
            OutData_KDFInfo[9] = RSIP.REG_002CH.WORD;
            OutData_KDFInfo[10] = RSIP.REG_002CH.WORD;
            OutData_KDFInfo[11] = RSIP.REG_002CH.WORD;
            OutData_KDFInfo[12] = RSIP.REG_002CH.WORD;
            r_rsip_func100(0x2bf38fadU, 0x2f8ecbecU, 0xad208cf4U, 0x70da03dfU);
            RSIP.REG_009CH.WORD = 0x81010000U;
            RSIP.REG_0008H.WORD = 0x00005006U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0008H.BIT.B30)
            {
                /* waiting */
            }
            OutData_KDFInfo[0] = RSIP.REG_002CH.WORD;
            r_rsip_func102(0xead615c6U, 0x7826c62aU, 0xadf6816aU, 0x0f17c98cU);
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
