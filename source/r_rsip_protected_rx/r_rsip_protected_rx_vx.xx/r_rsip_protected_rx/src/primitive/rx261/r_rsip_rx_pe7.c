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

rsip_ret_t r_rsip_pe7(const uint32_t InData_KDFInfo[], const uint32_t InData_KDFInfo_Count[], const uint32_t InData_OutDataType[], const uint32_t InData_OutDataLocation[], uint32_t OutData_KeyIndex[], uint32_t OutData_EncIV[])
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
    RSIP.REG_0070H.WORD = 0x00e70001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    RSIP.REG_0014H.WORD = 0x000001c7U;
    RSIP.REG_009CH.WORD = 0x800200a0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_KDFInfo_Count[0];
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_OutDataType[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0094H.WORD = 0x38000ca5U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00260000U;
    RSIP.REG_0094H.WORD = 0x0000b400U;
    RSIP.REG_0094H.WORD = 0x08000000U;
    RSIP.REG_0094H.WORD = 0x34202805U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00260000U;
    RSIP.REG_0094H.WORD = 0x0000b400U;
    RSIP.REG_0094H.WORD = 0x00000002U;
    RSIP.REG_0094H.WORD = 0x34202806U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00260000U;
    r_rsip_func100(0x55fa0eedU, 0xf0c6523cU, 0x74ed9fbaU, 0x2bfd9f41U);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0x1f37f458U, 0x4fcd7356U, 0x2f28b12eU, 0xd8dd8cc5U);
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
        r_rsip_func100(0xdfd19a37U, 0x77cb755fU, 0x4fe863f7U, 0xd7db6a9fU);
        RSIP.REG_0094H.WORD = 0x00007c06U;
        RSIP.REG_0040H.WORD = 0x00600000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (0x00000000U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x80010080U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x0000000fU);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0xaebd8ccdU, 0xf6bfd4eeU, 0x36472390U, 0x4a2203d2U);
        }
        else if (0x00000001U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x80010080U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x0000001fU);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x765b9e0eU, 0x14bbaff7U, 0xdccd96a1U, 0x2956719cU);
        }
        else if (0x00000002U == (RSIP.REG_0044H.WORD & 0xffffffffU))
        {
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x80010080U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x0000000fU);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x292da8e4U, 0x1ab3a5beU, 0xa7a7ae25U, 0x997ccf32U);
        }
        RSIP.REG_0094H.WORD = 0x0000b4e0U;
        RSIP.REG_0094H.WORD = 0x00000010U;
        RSIP.REG_0094H.WORD = 0x00003cc7U;
        RSIP.REG_0014H.WORD = 0x000000c7U;
        RSIP.REG_009CH.WORD = 0x80010020U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_OutDataLocation[0];
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0094H.WORD = 0x00003405U;
        RSIP.REG_0094H.WORD = 0x00056c00U;
        RSIP.REG_0094H.WORD = 0x00003000U;
        RSIP.REG_0094H.WORD = 0x00002481U;
        RSIP.REG_0094H.WORD = 0x34202804U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00260000U;
        RSIP.REG_0094H.WORD = 0x34202824U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00A60000U;
        r_rsip_func100(0x878c7e43U, 0xf8201b49U, 0xd51ffc21U, 0x1930f112U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0x58609fe4U, 0x6711e1f4U, 0x6ad16ac1U, 0x357d63a0U);
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
            RSIP.REG_0094H.WORD = 0x000008c6U;
            RSIP.REG_0094H.WORD = 0x00000800U;
            RSIP.REG_0094H.WORD = 0x00000842U;
            RSIP.REG_0094H.WORD = 0x00000863U;
            r_rsip_func100(0xea541111U, 0x6a706c4bU, 0x680bea75U, 0x1259cbbeU);
            RSIP.REG_009CH.WORD = 0x810100a0U;
            RSIP.REG_0008H.WORD = 0x00005006U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0008H.BIT.B30)
            {
                /* waiting */
            }
            S_RAM[0] = bswap_32big(RSIP.REG_002CH.WORD);
            RSIP.REG_0094H.WORD = 0x0000b4e0U;
            RSIP.REG_0094H.WORD = 0x00000014U;
            RSIP.REG_0094H.WORD = 0x00003ca7U;
            for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
            {
                RSIP.REG_0094H.WORD = 0x34202880U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                RSIP.REG_0094H.WORD = 0x0000a400U;
                RSIP.REG_0094H.WORD = 0x0000001fU;
                RSIP.REG_0094H.WORD = 0x34202801U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                r_rsip_func100(0x5ef8265bU, 0x5752cfdaU, 0xaa63edcaU, 0x64947440U);
                RSIP.REG_0040H.WORD = 0x00400000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                if (1U == (RSIP.REG_0040H.BIT.B22))
                {
                    r_rsip_func101(0xfddd3c2aU, 0x4e6733d1U, 0xfd36d676U, 0x46d91526U);
                }
                else
                {
                    RSIP.REG_0094H.WORD = 0x0000b4e0U;
                    RSIP.REG_0094H.WORD = 0x00000018U;
                    RSIP.REG_0094H.WORD = 0x00003c47U;
                    RSIP.REG_0094H.WORD = 0x0000b4e0U;
                    RSIP.REG_0094H.WORD = 0x0000001cU;
                    RSIP.REG_0094H.WORD = 0x00003cc7U;
                    RSIP.REG_0014H.WORD = 0x000000c7U;
                    RSIP.REG_009CH.WORD = 0x800100c0U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 0];
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    RSIP.REG_0014H.WORD = 0x000000a7U;
                    RSIP.REG_009CH.WORD = 0x800100e0U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = bswap_32big(0x0000e701U);
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    r_rsip_func101(0xa6149172U, 0xcf162f8fU, 0x5328d02aU, 0x9ff2727bU);
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
                    RSIP.REG_002CH.WORD = bswap_32big(0x0000e701U);
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    r_rsip_func101(0x2cb62cfdU, 0xaac374e0U, 0xaa1f51e1U, 0x25a9c199U);
                    r_rsip_func044();
                    RSIP.REG_0094H.WORD = 0x38000c63U;
                    RSIP.REG_009CH.WORD = 0x00000080U;
                    RSIP.REG_0040H.WORD = 0x00260000U;
                    r_rsip_func100(0xfe317e48U, 0x934afa36U, 0x995cb39fU, 0x471f2aeeU);
                    RSIP.REG_0040H.WORD = 0x00400000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    if (1U == (RSIP.REG_0040H.BIT.B22))
                    {
                        RSIP.REG_00B0H.WORD = 0x00001404U;
                        r_rsip_func101(0xaa1165d9U, 0xbfc714faU, 0xa9da7200U, 0xba8c0999U);
                    }
                    else
                    {
                        RSIP.REG_00B0H.WORD = 0x00001408U;
                        r_rsip_func101(0xa30a7298U, 0xeb17fffbU, 0x27832d1fU, 0xa0043701U);
                    }
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
                    RSIP.REG_0014H.WORD = 0x000007c1U;
                    RSIP.REG_00D4H.WORD = 0x40000100U;
                    RSIP.REG_00D0H.WORD = 0xf7008d07U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 1];
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 2];
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 3];
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 4];
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 5];
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 6];
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 7];
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 8];
                    RSIP.REG_0000H.WORD = 0x00c10021U;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0004H.BIT.B30)
                    {
                        /* waiting */
                    }
                    RSIP.REG_0040H.WORD = 0x00001800U;
                    RSIP.REG_0094H.WORD = 0x00002c60U;
                    RSIP.REG_0094H.WORD = 0x0000b4e0U;
                    RSIP.REG_0094H.WORD = 0x00000018U;
                    RSIP.REG_0094H.WORD = 0x00003847U;
                    RSIP.REG_0094H.WORD = 0x0000b4e0U;
                    RSIP.REG_0094H.WORD = 0x0000001cU;
                    RSIP.REG_0094H.WORD = 0x000038c7U;
                    RSIP.REG_0014H.WORD = 0x000003c1U;
                    RSIP.REG_00D4H.WORD = 0x40000000U;
                    RSIP.REG_00D0H.WORD = 0x07008d05U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 9];
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 10];
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 11];
                    RSIP.REG_002CH.WORD = InData_KDFInfo[iLoop*13 + 12];
                    RSIP.REG_00D0H.WORD = 0x9c100005U;
                    RSIP.REG_0000H.WORD = 0x00410011U;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0004H.BIT.B30)
                    {
                        /* waiting */
                    }
                    RSIP.REG_0040H.WORD = 0x00001800U;
                    r_rsip_func100(0x596e7d1bU, 0xea428408U, 0xdd1e13afU, 0x904e9fa4U);
                    RSIP.REG_0040H.WORD = 0x00400000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    if (1U == (RSIP.REG_0040H.BIT.B22))
                    {
                        RSIP.REG_0094H.WORD = 0x0000d040U;
                        r_rsip_func101(0x08ae7dfeU, 0xcec07f3fU, 0x1db56b37U, 0x6cf472aeU);
                    }
                    else
                    {
                        r_rsip_func101(0x9da77702U, 0xcf7229baU, 0x0ed1bc76U, 0x98f53187U);
                    }
                }
                RSIP.REG_0094H.WORD = 0x00002c00U;
                RSIP.REG_0094H.WORD = 0x00002cc0U;
                r_rsip_func101(0xa5900824U, 0x9af3ad39U, 0x56462faeU, 0x61d67f1cU);
            }
            RSIP.REG_0094H.WORD = 0x0000b4e0U;
            RSIP.REG_0094H.WORD = 0x00000014U;
            RSIP.REG_0094H.WORD = 0x00003807U;
            RSIP.REG_0094H.WORD = 0x380008c0U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00260000U;
            RSIP.REG_0040H.WORD = 0x00402000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            RSIP.REG_0094H.WORD = 0x38000c42U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00A60000U;
            r_rsip_func100(0x97eef71eU, 0xdb154eeaU, 0x4252bd5eU, 0x2b26aef5U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0xa0ee2b89U, 0xa43fdaa5U, 0xf68a7587U, 0xf260f58dU);
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
                r_rsip_func100(0xb9c61164U, 0x85499717U, 0x5146d812U, 0x27c2ae52U);
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
                RSIP.REG_002CH.WORD = bswap_32big(0x0000e702U);
                RSIP.REG_0024H.WORD = 0x00000000U;
                r_rsip_func101(0x6a65a41aU, 0x2be03956U, 0xf8172730U, 0x4b89c34cU);
                r_rsip_func043();
                RSIP.REG_0094H.WORD = 0x0000b4e0U;
                RSIP.REG_0094H.WORD = 0x00000010U;
                RSIP.REG_0094H.WORD = 0x00003847U;
                r_rsip_func100(0x93971f8dU, 0xc290f582U, 0xad26477bU, 0x46c9e91cU);
                RSIP.REG_0094H.WORD = 0x00007c02U;
                RSIP.REG_0040H.WORD = 0x00600000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                if (0x00000000U == (RSIP.REG_0044H.WORD & 0xffffffffU))
                {
                    RSIP.REG_0094H.WORD = 0x0000b4c0U;
                    RSIP.REG_0094H.WORD = 0x00000005U;
                    r_rsip_func101(0x12eb169eU, 0x581b4461U, 0x0e97b3faU, 0x07e09bf0U);
                }
                else if (0x00000001U == (RSIP.REG_0044H.WORD & 0xffffffffU))
                {
                    RSIP.REG_0094H.WORD = 0x0000b4c0U;
                    RSIP.REG_0094H.WORD = 0x00000007U;
                    r_rsip_func101(0x361e844bU, 0x5fe340a2U, 0xae3cb713U, 0x59fe734aU);
                }
                else if (0x00000002U == (RSIP.REG_0044H.WORD & 0xffffffffU))
                {
                    RSIP.REG_0094H.WORD = 0x0000b4c0U;
                    RSIP.REG_0094H.WORD = 0x0199e556U;
                    r_rsip_func101(0x43ce6ef5U, 0x85b78dc3U, 0x5c88be68U, 0x653f2041U);
                }
                RSIP.REG_0014H.WORD = 0x000000a7U;
                RSIP.REG_009CH.WORD = 0x800100e0U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0014H.BIT.B31)
                {
                    /* waiting */
                }
                RSIP.REG_002CH.WORD = bswap_32big(0x0000e702U);
                RSIP.REG_0024H.WORD = 0x00000000U;
                r_rsip_func101(0xc0e257c5U, 0x478b5647U, 0xaf4eba90U, 0x081fa542U);
                r_rsip_func044();
                RSIP.REG_0094H.WORD = 0x00008c20U;
                RSIP.REG_0094H.WORD = 0x0000001fU;
                RSIP.REG_0094H.WORD = 0x000008e7U;
                RSIP.REG_0094H.WORD = 0x000008a5U;
                RSIP.REG_0094H.WORD = 0x38008860U;
                RSIP.REG_0094H.WORD = 0x00000001U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                r_rsip_func100(0xc7c600b1U, 0x4381528dU, 0x17781c86U, 0xd54b36dfU);
                RSIP.REG_0040H.WORD = 0x00400000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                if (1U == (RSIP.REG_0040H.BIT.B22))
                {
                    RSIP.REG_0094H.WORD = 0x0000b480U;
                    RSIP.REG_0094H.WORD = 0x00000020U;
                    RSIP.REG_00B0H.WORD = 0x00001804U;
                    r_rsip_func101(0xe8948dcdU, 0x57d82b9eU, 0xbb2750f3U, 0xbac4d9c4U);
                }
                else
                {
                    RSIP.REG_0094H.WORD = 0x0000b480U;
                    RSIP.REG_0094H.WORD = 0x00000040U;
                    RSIP.REG_00B0H.WORD = 0x00003808U;
                    r_rsip_func101(0xcafb931cU, 0x176137c6U, 0xd6b4827cU, 0xd31178e9U);
                }
                r_rsip_func100(0xd76a3755U, 0x16aed960U, 0xb3172a7aU, 0x996f0f5eU);
                RSIP.REG_009CH.WORD = 0x81010080U;
                RSIP.REG_0008H.WORD = 0x00005006U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0008H.BIT.B30)
                {
                    /* waiting */
                }
                S_RAM[0] = bswap_32big(RSIP.REG_002CH.WORD);
                for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                {
                    RSIP.REG_0094H.WORD = 0x342028a1U;
                    RSIP.REG_009CH.WORD = 0x00000080U;
                    RSIP.REG_0040H.WORD = 0x00260000U;
                    RSIP.REG_0094H.WORD = 0x3420a8e0U;
                    RSIP.REG_0094H.WORD = 0x00000020U;
                    RSIP.REG_009CH.WORD = 0x00000080U;
                    RSIP.REG_0040H.WORD = 0x00A60000U;
                    r_rsip_func100(0x0ac7e4f6U, 0x5cc2a2f0U, 0x3e24b977U, 0x23f902fbU);
                    RSIP.REG_0040H.WORD = 0x00400000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    if (1U == (RSIP.REG_0040H.BIT.B22))
                    {
                        RSIP.REG_0000H.WORD = 0x1000000dU;
                        /* WAIT_LOOP */
                        while (0U != RSIP.REG_0004H.BIT.B30)
                        {
                            /* waiting */
                        }
                        RSIP.REG_0040H.WORD = 0x00001800U;
                        RSIP.REG_0000H.WORD = 0x10030005U;
                        /* WAIT_LOOP */
                        while (0U != RSIP.REG_0004H.BIT.B30)
                        {
                            /* waiting */
                        }
                        RSIP.REG_0040H.WORD = 0x00001800U;
                        r_rsip_func101(0x857b68e8U, 0xe0c750a4U, 0x609201dfU, 0x493ddc65U);
                    }
                    else
                    {
                        RSIP.REG_009CH.WORD = 0x800100c0U;
                        RSIP.REG_0000H.WORD = 0x1340000dU;
                        /* WAIT_LOOP */
                        while (0U != RSIP.REG_0004H.BIT.B30)
                        {
                            /* waiting */
                        }
                        RSIP.REG_0040H.WORD = 0x00001800U;
                        RSIP.REG_0000H.WORD = 0x13430005U;
                        /* WAIT_LOOP */
                        while (0U != RSIP.REG_0004H.BIT.B30)
                        {
                            /* waiting */
                        }
                        RSIP.REG_0040H.WORD = 0x00001800U;
                        RSIP.REG_0094H.WORD = 0x02003cc7U;
                        RSIP.REG_0094H.WORD = 0x00002ce0U;
                        r_rsip_func101(0x86f6ad3aU, 0x5a0d70cfU, 0x0eb95d8dU, 0x564534deU);
                    }
                    RSIP.REG_0094H.WORD = 0x00002ca0U;
                    r_rsip_func101(0xfec3b738U, 0x15ab07a6U, 0x7ad7fb26U, 0xae13401aU);
                }
                RSIP.REG_0094H.WORD = 0x380008a4U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                RSIP.REG_0040H.WORD = 0x00402000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                RSIP.REG_0094H.WORD = 0x0000b4e0U;
                RSIP.REG_0094H.WORD = 0x00000000U;
                RSIP.REG_0094H.WORD = 0x3420a840U;
                RSIP.REG_0094H.WORD = 0x00000002U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                r_rsip_func100(0x72502ac0U, 0xeeda278eU, 0xbf40db5aU, 0x7f41fa91U);
                RSIP.REG_0040H.WORD = 0x00400000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                if (1U == (RSIP.REG_0040H.BIT.B22))
                {
                    RSIP.REG_0094H.WORD = 0x38000c42U;
                    RSIP.REG_009CH.WORD = 0x00000080U;
                    RSIP.REG_0040H.WORD = 0x00260000U;
                    r_rsip_func100(0x8243d23fU, 0xe17ab2feU, 0x8e54d187U, 0xd38030dbU);
                    RSIP.REG_0040H.WORD = 0x00400000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    if (1U == (RSIP.REG_0040H.BIT.B22))
                    {
                        r_rsip_func100(0x3240cfdfU, 0x593381cbU, 0xcfc29389U, 0x048a61a9U);
                        RSIP.REG_00D4H.WORD = 0x40000000U;
                        RSIP.REG_00D0H.WORD = 0xe7009d05U;
                        RSIP.REG_009CH.WORD = 0x81840007U;
                        RSIP.REG_0000H.WORD = 0x00490011U;
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
                        OutData_KeyIndex[1] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[2] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[3] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[4] = RSIP.REG_002CH.WORD;
                        r_rsip_func100(0x169292f6U, 0xb519e796U, 0xe78f9e09U, 0x03640100U);
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
                        OutData_KeyIndex[5] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[6] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[7] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[8] = RSIP.REG_002CH.WORD;
                        r_rsip_func101(0x14ac6a1bU, 0x284b28fbU, 0xcb4cb823U, 0xde3a3936U);
                    }
                    else
                    {
                        r_rsip_func100(0xbc61a5baU, 0xf7e209e0U, 0x394d90b5U, 0x39547f1cU);
                        RSIP.REG_00D4H.WORD = 0x40000100U;
                        RSIP.REG_00D0H.WORD = 0xe7009d07U;
                        RSIP.REG_009CH.WORD = 0x81880007U;
                        RSIP.REG_0000H.WORD = 0x00490021U;
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
                        OutData_KeyIndex[1] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[2] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[3] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[4] = RSIP.REG_002CH.WORD;
                        /* WAIT_LOOP */
                        while (1U != RSIP.REG_0008H.BIT.B30)
                        {
                            /* waiting */
                        }
                        OutData_KeyIndex[5] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[6] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[7] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[8] = RSIP.REG_002CH.WORD;
                        r_rsip_func100(0xa780b39cU, 0x2394ac42U, 0xcc808d54U, 0x10dd15b0U);
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
                        OutData_KeyIndex[9] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[10] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[11] = RSIP.REG_002CH.WORD;
                        OutData_KeyIndex[12] = RSIP.REG_002CH.WORD;
                        r_rsip_func101(0x8e9952d2U, 0xe14bb23fU, 0x0a256f10U, 0xb92ce4cbU);
                    }
                    r_rsip_func100(0xe6bbc4c9U, 0x25c5787dU, 0xa1c12a69U, 0x5e5e4d62U);
                    RSIP.REG_009CH.WORD = 0x81010000U;
                    RSIP.REG_0008H.WORD = 0x00005006U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0008H.BIT.B30)
                    {
                        /* waiting */
                    }
                    OutData_KeyIndex[0] = RSIP.REG_002CH.WORD;
                    r_rsip_func102(0x58b0f6d0U, 0x35d61c8dU, 0x4a3ae1e5U, 0x11f9f8f1U);
                    RSIP.REG_006CH.WORD = 0x00000040U;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0020H.BIT.B12)
                    {
                        /* waiting */
                    }
                    return RSIP_RET_PASS;
                }
                else
                {
                    r_rsip_func100(0x31eee52eU, 0xf8414358U, 0xc46ee37dU, 0x95b6306cU);
                    RSIP.REG_00D4H.WORD = 0x40000000U;
                    RSIP.REG_00D0H.WORD = 0xe7009d05U;
                    RSIP.REG_009CH.WORD = 0x81840007U;
                    RSIP.REG_0000H.WORD = 0x00490011U;
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
                    OutData_EncIV[1] = RSIP.REG_002CH.WORD;
                    OutData_EncIV[2] = RSIP.REG_002CH.WORD;
                    OutData_EncIV[3] = RSIP.REG_002CH.WORD;
                    OutData_EncIV[4] = RSIP.REG_002CH.WORD;
                    r_rsip_func100(0x1a7d478dU, 0xa9f09dc1U, 0x07bc389eU, 0x6cc7c7a5U);
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
                    OutData_EncIV[5] = RSIP.REG_002CH.WORD;
                    OutData_EncIV[6] = RSIP.REG_002CH.WORD;
                    OutData_EncIV[7] = RSIP.REG_002CH.WORD;
                    OutData_EncIV[8] = RSIP.REG_002CH.WORD;
                    r_rsip_func100(0xa74ab8d0U, 0xb9dae7ebU, 0x21e30fdbU, 0x96497354U);
                    RSIP.REG_009CH.WORD = 0x81010000U;
                    RSIP.REG_0008H.WORD = 0x00005006U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0008H.BIT.B30)
                    {
                        /* waiting */
                    }
                    OutData_EncIV[0] = RSIP.REG_002CH.WORD;
                    r_rsip_func102(0xf42a0de8U, 0xae162b8fU, 0xf20032b6U, 0xc39515f0U);
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
    }
}
