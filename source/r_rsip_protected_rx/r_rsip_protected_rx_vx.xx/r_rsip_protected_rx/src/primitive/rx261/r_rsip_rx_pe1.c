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

rsip_ret_t r_rsip_pe1(const uint32_t InData_Sel_KeyType[], const uint32_t InData_Certificate[], const uint32_t InData_CertificateLength[], const uint32_t InData_CertificatePubKey[], const uint32_t InData_EncCertificateInfo[], uint32_t OutData_KeyIndex[])
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
    RSIP.REG_0070H.WORD = 0x00e10001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    RSIP.REG_0014H.WORD = 0x000000c7U;
    RSIP.REG_009CH.WORD = 0x80010000U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_Sel_KeyType[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0094H.WORD = 0x3420a800U;
    RSIP.REG_0094H.WORD = 0x00000003U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00260000U;
    RSIP.REG_0094H.WORD = 0x38008800U;
    RSIP.REG_0094H.WORD = 0x00000004U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00260000U;
    RSIP.REG_0094H.WORD = 0x38008800U;
    RSIP.REG_0094H.WORD = 0x00000005U;
    RSIP.REG_009CH.WORD = 0x00000080U;
    RSIP.REG_0040H.WORD = 0x00260000U;
    r_rsip_func100(0x63c3047cU, 0x2a59d839U, 0x2a3611d8U, 0x482426cbU);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0x463515b9U, 0x8d7c4af7U, 0x3e61797dU, 0x406f7d98U);
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
        RSIP.REG_0094H.WORD = 0x3000a800U;
        RSIP.REG_0094H.WORD = 0x00000006U;
        RSIP.REG_0094H.WORD = 0x00010020U;
        RSIP.REG_0094H.WORD = 0x0000b400U;
        RSIP.REG_0094H.WORD = 0x00000006U;
        RSIP.REG_0094H.WORD = 0x00000080U;
        RSIP.REG_0094H.WORD = 0x0000b420U;
        RSIP.REG_0094H.WORD = 0x00000014U;
        RSIP.REG_0094H.WORD = 0x00003c01U;
        RSIP.REG_0014H.WORD = 0x000000c7U;
        RSIP.REG_009CH.WORD = 0x800100c0U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[0];
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0014H.WORD = 0x000000a7U;
        RSIP.REG_009CH.WORD = 0x800100e0U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x0000e101U);
        RSIP.REG_0024H.WORD = 0x00000000U;
        r_rsip_func101(0x6a9fe040U, 0xd560110dU, 0x93fb6ea3U, 0x6aa5fc07U);
        r_rsip_func043();
        RSIP.REG_0094H.WORD = 0x0000b4c0U;
        RSIP.REG_0094H.WORD = 0x010f6caaU;
        RSIP.REG_0014H.WORD = 0x000000a7U;
        RSIP.REG_009CH.WORD = 0x800100e0U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = bswap_32big(0x0000e101U);
        RSIP.REG_0024H.WORD = 0x00000000U;
        r_rsip_func101(0x38279f01U, 0x011212afU, 0x0abc7336U, 0x4affa82cU);
        r_rsip_func044();
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
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[1];
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[2];
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[3];
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[4];
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[5];
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[6];
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[7];
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[8];
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
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[9];
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[10];
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[11];
        RSIP.REG_002CH.WORD = InData_EncCertificateInfo[12];
        RSIP.REG_00D0H.WORD = 0x9c100005U;
        RSIP.REG_0000H.WORD = 0x00410011U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0004H.BIT.B30)
        {
            /* waiting */
        }
        RSIP.REG_0040H.WORD = 0x00001800U;
        r_rsip_func100(0x5f3b0d8eU, 0x00774c83U, 0xb308de03U, 0x0e233783U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0x30804396U, 0xb0bbe241U, 0x4815a64fU, 0x7c677ca8U);
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
            RSIP.REG_0014H.WORD = 0x000000c7U;
            RSIP.REG_009CH.WORD = 0x80010040U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_CertificateLength[0];
            RSIP.REG_0024H.WORD = 0x00000000U;
            RSIP.REG_0014H.WORD = 0x000003c7U;
            RSIP.REG_009CH.WORD = 0x80040060U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_CertificatePubKey[0];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_CertificatePubKey[1];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_CertificatePubKey[2];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_CertificatePubKey[3];
            RSIP.REG_0024H.WORD = 0x00000000U;
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
            RSIP.REG_0094H.WORD = 0x000008e7U;
            RSIP.REG_0094H.WORD = 0x0000b400U;
            RSIP.REG_0094H.WORD = 0x0000001fU;
            RSIP.REG_0094H.WORD = 0x0000b420U;
            RSIP.REG_0094H.WORD = 0x0000001fU;
            RSIP.REG_0094H.WORD = 0x3c0028a6U;
            RSIP.REG_0094H.WORD = 0x1000d0e0U;
            RSIP.REG_0094H.WORD = 0x00002425U;
            RSIP.REG_0094H.WORD = 0x08002826U;
            RSIP.REG_0094H.WORD = 0x2000d0e0U;
            RSIP.REG_0094H.WORD = 0x3c002864U;
            RSIP.REG_0094H.WORD = 0x1000d0e0U;
            RSIP.REG_0094H.WORD = 0x3c002885U;
            RSIP.REG_0094H.WORD = 0x1000d0e0U;
            RSIP.REG_0094H.WORD = 0x00002403U;
            RSIP.REG_0094H.WORD = 0x08002804U;
            RSIP.REG_0094H.WORD = 0x2000d0e0U;
            RSIP.REG_0094H.WORD = 0x3c0028c2U;
            RSIP.REG_0094H.WORD = 0x1000d0e0U;
            RSIP.REG_0094H.WORD = 0x38000ce7U;
            RSIP.REG_009CH.WORD = 0x00000080U;
            RSIP.REG_0040H.WORD = 0x00A60000U;
            r_rsip_func100(0x74fcc9d9U, 0xb1819ae1U, 0x0747821eU, 0x30d15b54U);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0x44f743e6U, 0x2b07f5e8U, 0x5b28a9e7U, 0xdf5b4ac4U);
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
                r_rsip_func100(0xb1250114U, 0x3f7f8dcaU, 0xa852de4cU, 0x822412bcU);
                RSIP.REG_0094H.WORD = 0x00003403U;
                RSIP.REG_0094H.WORD = 0x00046800U;
                RSIP.REG_0094H.WORD = 0x00026c00U;
                RSIP.REG_009CH.WORD = 0x81010000U;
                RSIP.REG_0008H.WORD = 0x00005006U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0008H.BIT.B30)
                {
                    /* waiting */
                }
                S_RAM[0] = bswap_32big(RSIP.REG_002CH.WORD);
                RSIP.REG_0094H.WORD = 0x00000821U;
                for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 4)
                {
                    RSIP.REG_0014H.WORD = 0x000003c4U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = InData_Certificate[iLoop + 0];
                    RSIP.REG_002CH.WORD = InData_Certificate[iLoop + 1];
                    RSIP.REG_002CH.WORD = InData_Certificate[iLoop + 2];
                    RSIP.REG_002CH.WORD = InData_Certificate[iLoop + 3];
                    RSIP.REG_0094H.WORD = 0x0000a420U;
                    RSIP.REG_0094H.WORD = 0x00000004U;
                    r_rsip_func101(0xff12f963U, 0x437ad436U, 0x726310c3U, 0xa98f0a86U);
                }
                r_rsip_func100(0xbef2094dU, 0xdfea6388U, 0xf88bbe80U, 0x05758853U);
                RSIP.REG_0094H.WORD = 0x38000801U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                RSIP.REG_0040H.WORD = 0x00402000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                RSIP.REG_00B0H.WORD = 0x0000340cU;
                RSIP.REG_0094H.WORD = 0x00003402U;
                RSIP.REG_0094H.WORD = 0x0000a400U;
                RSIP.REG_0094H.WORD = 0x00000003U;
                RSIP.REG_0094H.WORD = 0x00026800U;
                RSIP.REG_009CH.WORD = 0x81010000U;
                RSIP.REG_0008H.WORD = 0x00005006U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0008H.BIT.B30)
                {
                    /* waiting */
                }
                S_RAM[0] = bswap_32big(RSIP.REG_002CH.WORD);
                RSIP.REG_0094H.WORD = 0x000034e1U;
                RSIP.REG_0094H.WORD = 0x00026ce7U;
                RSIP.REG_0094H.WORD = 0x00003040U;
                RSIP.REG_0094H.WORD = 0x00000884U;
                RSIP.REG_0094H.WORD = 0x00003c04U;
                for (; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                {
                    RSIP.REG_0014H.WORD = 0x000000c7U;
                    RSIP.REG_009CH.WORD = 0x800100c0U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = InData_Certificate[iLoop + 0];
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    RSIP.REG_0094H.WORD = 0x0000b480U;
                    RSIP.REG_0094H.WORD = 0x00000004U;
                    RSIP.REG_0094H.WORD = 0x00003c24U;
                    RSIP.REG_0094H.WORD = 0x00000821U;
                    for (jLoop = 0; jLoop < 4; jLoop = jLoop + 1)
                    {
                        RSIP.REG_0094H.WORD = 0x00002c20U;
                        RSIP.REG_0094H.WORD = 0x01886c06U;
                        RSIP.REG_0094H.WORD = 0x00086cc6U;
                        RSIP.REG_0094H.WORD = 0x00003485U;
                        RSIP.REG_0094H.WORD = 0x0000a480U;
                        RSIP.REG_0094H.WORD = 0x0000001fU;
                        RSIP.REG_0094H.WORD = 0x3c0028e5U;
                        RSIP.REG_009CH.WORD = 0x00000080U;
                        RSIP.REG_0040H.WORD = 0x00260000U;
                        r_rsip_func100(0x9a41b75fU, 0xd91864bdU, 0x1635ddd4U, 0x824ca49dU);
                        RSIP.REG_0040H.WORD = 0x00400000U;
                        RSIP.REG_0024H.WORD = 0x00000000U;
                        if (1U == (RSIP.REG_0040H.BIT.B22))
                        {
                            RSIP.REG_0094H.WORD = 0x3c002887U;
                            RSIP.REG_009CH.WORD = 0x00000080U;
                            RSIP.REG_0040H.WORD = 0x00260000U;
                            r_rsip_func100(0xae094a8dU, 0xff7a72b6U, 0xb00767c1U, 0x06101a6aU);
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
                                RSIP.REG_0000H.WORD = 0x10c90005U;
                                /* WAIT_LOOP */
                                while (0U != RSIP.REG_0004H.BIT.B30)
                                {
                                    /* waiting */
                                }
                                RSIP.REG_0040H.WORD = 0x00001800U;
                                r_rsip_func101(0xaf5c9a59U, 0x7679ac40U, 0x43e0d930U, 0x4f432b53U);
                            }
                            r_rsip_func101(0x1595224eU, 0xb977fd96U, 0x5010af26U, 0x18093c52U);
                        }
                        RSIP.REG_0094H.WORD = 0x00003483U;
                        RSIP.REG_0094H.WORD = 0x0000a480U;
                        RSIP.REG_0094H.WORD = 0x0000001fU;
                        RSIP.REG_0094H.WORD = 0x3c0028e3U;
                        RSIP.REG_009CH.WORD = 0x00000080U;
                        RSIP.REG_0040H.WORD = 0x00260000U;
                        r_rsip_func100(0x92a49524U, 0x744b1983U, 0x39d47452U, 0x6a63f292U);
                        RSIP.REG_0040H.WORD = 0x00400000U;
                        RSIP.REG_0024H.WORD = 0x00000000U;
                        if (1U == (RSIP.REG_0040H.BIT.B22))
                        {
                            RSIP.REG_0094H.WORD = 0x3c002887U;
                            RSIP.REG_009CH.WORD = 0x00000080U;
                            RSIP.REG_0040H.WORD = 0x00260000U;
                            r_rsip_func100(0xd75f9bb6U, 0xf8ddbaefU, 0x93d97cf1U, 0xf2dc85e8U);
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
                                RSIP.REG_0000H.WORD = 0x10c90005U;
                                /* WAIT_LOOP */
                                while (0U != RSIP.REG_0004H.BIT.B30)
                                {
                                    /* waiting */
                                }
                                RSIP.REG_0040H.WORD = 0x00001800U;
                                r_rsip_func101(0xbd0afa29U, 0xaeacdb3fU, 0xdab01fc4U, 0x31bc428eU);
                            }
                            r_rsip_func101(0x6bde46abU, 0x29d5ba62U, 0x5c5494b0U, 0x5bb8b498U);
                        }
                        RSIP.REG_0094H.WORD = 0x3c002847U;
                        RSIP.REG_009CH.WORD = 0x00000080U;
                        RSIP.REG_0040H.WORD = 0x00260000U;
                        r_rsip_func100(0xdcfbe4a2U, 0xcbf191d8U, 0xda0a5d95U, 0x0b9e2a00U);
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
                            r_rsip_func101(0xa8b44fa6U, 0x7a184b4bU, 0xd8f63e14U, 0x0618d727U);
                        }
                        RSIP.REG_0094H.WORD = 0x00002ce0U;
                        r_rsip_func101(0x60f809cdU, 0xe557b707U, 0x4d5064d6U, 0xc3ee38e7U);
                    }
                    RSIP.REG_0094H.WORD = 0x38008820U;
                    RSIP.REG_0094H.WORD = 0x00000004U;
                    RSIP.REG_009CH.WORD = 0x00000080U;
                    RSIP.REG_0040H.WORD = 0x00260000U;
                    RSIP.REG_0040H.WORD = 0x00402000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    RSIP.REG_0094H.WORD = 0x0000b480U;
                    RSIP.REG_0094H.WORD = 0x00000004U;
                    RSIP.REG_0094H.WORD = 0x00003824U;
                    RSIP.REG_0094H.WORD = 0x00002c20U;
                    r_rsip_func101(0x5709e8d9U, 0x7ee6dd29U, 0x2d82bd11U, 0xdb04d73fU);
                }
                RSIP.REG_0094H.WORD = 0x00000884U;
                RSIP.REG_0094H.WORD = 0x00003804U;
                RSIP.REG_0094H.WORD = 0x38000801U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                RSIP.REG_0040H.WORD = 0x00402000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                RSIP.REG_0094H.WORD = 0x00002c40U;
                RSIP.REG_0094H.WORD = 0x0000b400U;
                RSIP.REG_0094H.WORD = 0x00000080U;
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
                RSIP.REG_0094H.WORD = 0x00003402U;
                RSIP.REG_0094H.WORD = 0x00002c00U;
                RSIP.REG_0094H.WORD = 0x00008c00U;
                RSIP.REG_0094H.WORD = 0x0000003fU;
                RSIP.REG_0094H.WORD = 0x0000b420U;
                RSIP.REG_0094H.WORD = 0x00000038U;
                RSIP.REG_0094H.WORD = 0x3c002820U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                r_rsip_func100(0xd4820addU, 0xe0602edcU, 0x693ee049U, 0xcfccae99U);
                RSIP.REG_0040H.WORD = 0x00400000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                if (1U == (RSIP.REG_0040H.BIT.B22))
                {
                    RSIP.REG_0094H.WORD = 0x00202820U;
                    r_rsip_func101(0x71f77d12U, 0x1c0238e0U, 0xa86ab335U, 0xbe60d08cU);
                }
                else
                {
                    RSIP.REG_0094H.WORD = 0x0000a420U;
                    RSIP.REG_0094H.WORD = 0x00000040U;
                    RSIP.REG_0094H.WORD = 0x00202820U;
                    r_rsip_func101(0xf1eb14faU, 0x10c26923U, 0xb9db8c4eU, 0x7ed1d5bbU);
                }
                r_rsip_func100(0xbd1b4c1fU, 0xf4cbfaceU, 0xd00edc1dU, 0xe22f9560U);
                RSIP.REG_009CH.WORD = 0x81010020U;
                RSIP.REG_0008H.WORD = 0x00005006U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0008H.BIT.B30)
                {
                    /* waiting */
                }
                S_RAM[0] = bswap_32big(RSIP.REG_002CH.WORD);
                RSIP.REG_0094H.WORD = 0x000008a5U;
                RSIP.REG_0094H.WORD = 0x00000800U;
                for (iLoop = 0; iLoop < S_RAM[0]; iLoop = iLoop + 1)
                {
                    RSIP.REG_009CH.WORD = 0x81010000U;
                    RSIP.REG_0000H.WORD = 0x11490005U;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0004H.BIT.B30)
                    {
                        /* waiting */
                    }
                    RSIP.REG_0040H.WORD = 0x00001800U;
                    RSIP.REG_0000H.WORD = 0x1009000dU;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0004H.BIT.B30)
                    {
                        /* waiting */
                    }
                    RSIP.REG_0040H.WORD = 0x00001800U;
                    RSIP.REG_0094H.WORD = 0x00002ca0U;
                    r_rsip_func101(0x9de88e87U, 0x7ccda0fbU, 0xab6f1da9U, 0xeaf9dbf7U);
                }
                RSIP.REG_0094H.WORD = 0x38000825U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                RSIP.REG_0040H.WORD = 0x00402000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                RSIP.REG_0094H.WORD = 0x00000821U;
                RSIP.REG_0094H.WORD = 0x01836c22U;
                RSIP.REG_0094H.WORD = 0x00036c42U;
                RSIP.REG_009CH.WORD = 0x81020020U;
                RSIP.REG_0000H.WORD = 0x01490009U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0004H.BIT.B30)
                {
                    /* waiting */
                }
                RSIP.REG_0040H.WORD = 0x00001800U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_00F8H.BIT.B2)
                {
                    /* waiting */
                }
                RSIP.REG_00F4H.WORD = 0x00000100U;
                RSIP.REG_0040H.WORD = 0x00001600U;
                RSIP.REG_00F4H.WORD = 0x00000020U;
                RSIP.REG_0094H.WORD = 0x000008a5U;
                RSIP.REG_0094H.WORD = 0x00000800U;
                RSIP.REG_00B0H.WORD = 0x00001804U;
                for (iLoop = 0; iLoop < 8; iLoop = iLoop + 1)
                {
                    RSIP.REG_009CH.WORD = 0x80010020U;
                    RSIP.REG_0000H.WORD = 0x03450005U;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0004H.BIT.B30)
                    {
                        /* waiting */
                    }
                    RSIP.REG_0040H.WORD = 0x00001800U;
                    RSIP.REG_009CH.WORD = 0x80010040U;
                    RSIP.REG_0000H.WORD = 0x03430005U;
                    /* WAIT_LOOP */
                    while (0U != RSIP.REG_0004H.BIT.B30)
                    {
                        /* waiting */
                    }
                    RSIP.REG_0040H.WORD = 0x00001800U;
                    RSIP.REG_0094H.WORD = 0x08002822U;
                    RSIP.REG_0094H.WORD = 0x2000d000U;
                    RSIP.REG_0094H.WORD = 0x00002ca0U;
                    r_rsip_func101(0x6d36ec2bU, 0xa9e8fdbdU, 0xabc4b87bU, 0x2e7c5246U);
                }
                RSIP.REG_0094H.WORD = 0x380088a0U;
                RSIP.REG_0094H.WORD = 0x00000008U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00260000U;
                RSIP.REG_0040H.WORD = 0x00402000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                RSIP.REG_0094H.WORD = 0x38000c00U;
                RSIP.REG_009CH.WORD = 0x00000080U;
                RSIP.REG_0040H.WORD = 0x00A60000U;
                r_rsip_func100(0x17d074fbU, 0xf7306457U, 0xfb916066U, 0x1ce0ca00U);
                RSIP.REG_0040H.WORD = 0x00400000U;
                RSIP.REG_0024H.WORD = 0x00000000U;
                if (1U == (RSIP.REG_0040H.BIT.B22))
                {
                    r_rsip_func102(0xf7d90ab8U, 0x1d261ad0U, 0xc744f82cU, 0x1b269d6cU);
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
                    r_rsip_func100(0xadcbac61U, 0x5763af2bU, 0x9149a5f4U, 0xf8429a86U);
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
                    RSIP.REG_002CH.WORD = bswap_32big(0x0000e102U);
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    r_rsip_func101(0xe3e80c3bU, 0x5d1e0279U, 0xf251d84eU, 0x272bf487U);
                    r_rsip_func043();
                    RSIP.REG_0094H.WORD = 0x0000b420U;
                    RSIP.REG_0094H.WORD = 0x00000014U;
                    RSIP.REG_0094H.WORD = 0x00003881U;
                    r_rsip_func100(0x303a5c12U, 0x606ad2a2U, 0x4f3b029eU, 0xe220f47dU);
                    RSIP.REG_0094H.WORD = 0x00007c04U;
                    RSIP.REG_0040H.WORD = 0x00600000U;
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    if (0x00000003U == (RSIP.REG_0044H.WORD & 0xffffffffU))
                    {
                        RSIP.REG_0094H.WORD = 0x0000b4c0U;
                        RSIP.REG_0094H.WORD = 0x00000016U;
                        r_rsip_func101(0x7e4a877eU, 0xd943e7f0U, 0xddd0222dU, 0x712e2f3fU);
                    }
                    else if (0x00000006U == (RSIP.REG_0044H.WORD & 0xffffffffU))
                    {
                        RSIP.REG_0094H.WORD = 0x0000b4c0U;
                        RSIP.REG_0094H.WORD = 0x0000001cU;
                        r_rsip_func101(0x0f41232dU, 0xc94db9f3U, 0xe5002f39U, 0xd3e4ba5cU);
                    }
                    RSIP.REG_0014H.WORD = 0x000000a7U;
                    RSIP.REG_009CH.WORD = 0x800100e0U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0014H.BIT.B31)
                    {
                        /* waiting */
                    }
                    RSIP.REG_002CH.WORD = bswap_32big(0x0000e102U);
                    RSIP.REG_0024H.WORD = 0x00000000U;
                    r_rsip_func101(0x90114721U, 0xae799596U, 0x99a6c980U, 0xb939cf86U);
                    r_rsip_func044();
                    r_rsip_func100(0x7cf27a89U, 0x3afd850eU, 0x502344dfU, 0x4f688f88U);
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
                    RSIP.REG_00D0H.WORD = 0xe8008107U;
                    RSIP.REG_00B0H.WORD = 0x00001808U;
                    RSIP.REG_0000H.WORD = 0x00430021U;
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
                    r_rsip_func100(0xf5c737c4U, 0xbe4aa84eU, 0x4fac81eeU, 0xa2178c55U);
                    RSIP.REG_00D4H.WORD = 0x40000100U;
                    RSIP.REG_00D0H.WORD = 0xe8008107U;
                    RSIP.REG_00B0H.WORD = 0x0000180cU;
                    RSIP.REG_0000H.WORD = 0x00430021U;
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
                    OutData_KeyIndex[9] = RSIP.REG_002CH.WORD;
                    OutData_KeyIndex[10] = RSIP.REG_002CH.WORD;
                    OutData_KeyIndex[11] = RSIP.REG_002CH.WORD;
                    OutData_KeyIndex[12] = RSIP.REG_002CH.WORD;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0008H.BIT.B30)
                    {
                        /* waiting */
                    }
                    OutData_KeyIndex[13] = RSIP.REG_002CH.WORD;
                    OutData_KeyIndex[14] = RSIP.REG_002CH.WORD;
                    OutData_KeyIndex[15] = RSIP.REG_002CH.WORD;
                    OutData_KeyIndex[16] = RSIP.REG_002CH.WORD;
                    r_rsip_func100(0x48b76ac2U, 0x1826891fU, 0x9be15113U, 0x301899feU);
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
                    OutData_KeyIndex[17] = RSIP.REG_002CH.WORD;
                    OutData_KeyIndex[18] = RSIP.REG_002CH.WORD;
                    OutData_KeyIndex[19] = RSIP.REG_002CH.WORD;
                    OutData_KeyIndex[20] = RSIP.REG_002CH.WORD;
                    r_rsip_func100(0xa3bf7da6U, 0x1f2ba4c7U, 0x36e60e29U, 0xe5c0e547U);
                    RSIP.REG_009CH.WORD = 0x81010000U;
                    RSIP.REG_0008H.WORD = 0x00005006U;
                    /* WAIT_LOOP */
                    while (1U != RSIP.REG_0008H.BIT.B30)
                    {
                        /* waiting */
                    }
                    OutData_KeyIndex[0] = RSIP.REG_002CH.WORD;
                    r_rsip_func102(0x17cd3018U, 0xa8e67ad7U, 0xb8cc292aU, 0x29788725U);
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
