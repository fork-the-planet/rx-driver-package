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

rsip_ret_t r_rsip_pe2(const uint32_t InData_CurveType[], const uint32_t InData_PubKeyType[], const uint32_t InData_PubKey[], const uint32_t InData_KeyIndex[], const uint32_t InData_DomainParam[], uint32_t OutData_EncSecret[])
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
    RSIP.REG_0070H.WORD = 0x00e20001U;
    RSIP.REG_004CH.WORD = 0x00000000U;
    RSIP.REG_00A0H.WORD = 0x00010000U;
    RSIP.REG_0014H.WORD = 0x000000c7U;
    RSIP.REG_009CH.WORD = 0x80010000U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_CurveType[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0094H.WORD = 0x3420a800U;
    RSIP.REG_0094H.WORD = 0x00000002U;
    RSIP.REG_0094H.WORD = 0x2000b400U;
    RSIP.REG_0094H.WORD = 0x00000001U;
    r_rsip_func070(InData_DomainParam);
    RSIP.REG_0094H.WORD = 0x00003420U;
    RSIP.REG_00B8H.WORD = 0x00000005U;
    RSIP.REG_00A4H.WORD = 0x04040010U;
    RSIP.REG_00A0H.WORD = 0x20010001U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_00A8H.BIT.B0)
    {
        /* waiting */
    }
    RSIP.REG_00ACH.WORD = 0x00000001U;
    RSIP.REG_0014H.WORD = 0x000000c7U;
    RSIP.REG_009CH.WORD = 0x800100c0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_KeyIndex[0];
    RSIP.REG_0024H.WORD = 0x00000000U;
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x0000e201U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0xd37e87f4U, 0xe42208e8U, 0x3fcc7eeaU, 0xf9074dd7U);
    r_rsip_func043();
    r_rsip_func074();
    RSIP.REG_0014H.WORD = 0x000000a7U;
    RSIP.REG_009CH.WORD = 0x800100e0U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = bswap_32big(0x0000e201U);
    RSIP.REG_0024H.WORD = 0x00000000U;
    r_rsip_func101(0x724f4927U, 0xdba21e7aU, 0xae453211U, 0x7b172ca3U);
    r_rsip_func044();
    RSIP.REG_0014H.WORD = 0x000007c1U;
    RSIP.REG_00D4H.WORD = 0x40000100U;
    RSIP.REG_00D0H.WORD = 0xf7009d07U;
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_KeyIndex[1];
    RSIP.REG_002CH.WORD = InData_KeyIndex[2];
    RSIP.REG_002CH.WORD = InData_KeyIndex[3];
    RSIP.REG_002CH.WORD = InData_KeyIndex[4];
    /* WAIT_LOOP */
    while (1U != RSIP.REG_0014H.BIT.B31)
    {
        /* waiting */
    }
    RSIP.REG_002CH.WORD = InData_KeyIndex[5];
    RSIP.REG_002CH.WORD = InData_KeyIndex[6];
    RSIP.REG_002CH.WORD = InData_KeyIndex[7];
    RSIP.REG_002CH.WORD = InData_KeyIndex[8];
    RSIP.REG_00B0H.WORD = 0x00001432U;
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
    RSIP.REG_002CH.WORD = InData_KeyIndex[9];
    RSIP.REG_002CH.WORD = InData_KeyIndex[10];
    RSIP.REG_002CH.WORD = InData_KeyIndex[11];
    RSIP.REG_002CH.WORD = InData_KeyIndex[12];
    RSIP.REG_00D0H.WORD = 0x9c100005U;
    RSIP.REG_0000H.WORD = 0x00410011U;
    /* WAIT_LOOP */
    while (0U != RSIP.REG_0004H.BIT.B30)
    {
        /* waiting */
    }
    RSIP.REG_0040H.WORD = 0x00001800U;
    r_rsip_func100(0x9821c2f9U, 0x10ae7f27U, 0xae72a4b3U, 0x855aeb0dU);
    RSIP.REG_0040H.WORD = 0x00400000U;
    RSIP.REG_0024H.WORD = 0x00000000U;
    if (1U == (RSIP.REG_0040H.BIT.B22))
    {
        r_rsip_func102(0x6ee64eebU, 0xb0d39d41U, 0x33e176a6U, 0xcb2130c6U);
        RSIP.REG_006CH.WORD = 0x00000040U;
        /* WAIT_LOOP */
        while (0U != RSIP.REG_0020H.BIT.B12)
        {
            /* waiting */
        }
        return RSIP_RET_KEY_FAIL;
    }
    else
    {
        RSIP.REG_0014H.WORD = 0x000000c7U;
        RSIP.REG_009CH.WORD = 0x80010060U;
        /* WAIT_LOOP */
        while (1U != RSIP.REG_0014H.BIT.B31)
        {
            /* waiting */
        }
        RSIP.REG_002CH.WORD = InData_PubKeyType[0];
        RSIP.REG_0024H.WORD = 0x00000000U;
        RSIP.REG_0094H.WORD = 0x38000c63U;
        RSIP.REG_009CH.WORD = 0x00000080U;
        RSIP.REG_0040H.WORD = 0x00260000U;
        r_rsip_func100(0x9b03a9f7U, 0xace83ee7U, 0xabb08582U, 0x1d0e43e2U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            RSIP.REG_0014H.WORD = 0x00000fc5U;
            RSIP.REG_00B0H.WORD = 0x0000140fU;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_PubKey[0];
            RSIP.REG_002CH.WORD = InData_PubKey[1];
            RSIP.REG_002CH.WORD = InData_PubKey[2];
            RSIP.REG_002CH.WORD = InData_PubKey[3];
            RSIP.REG_002CH.WORD = InData_PubKey[4];
            RSIP.REG_002CH.WORD = InData_PubKey[5];
            RSIP.REG_002CH.WORD = InData_PubKey[6];
            RSIP.REG_002CH.WORD = InData_PubKey[7];
            RSIP.REG_00B0H.WORD = 0x00001414U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_PubKey[8];
            RSIP.REG_002CH.WORD = InData_PubKey[9];
            RSIP.REG_002CH.WORD = InData_PubKey[10];
            RSIP.REG_002CH.WORD = InData_PubKey[11];
            RSIP.REG_002CH.WORD = InData_PubKey[12];
            RSIP.REG_002CH.WORD = InData_PubKey[13];
            RSIP.REG_002CH.WORD = InData_PubKey[14];
            RSIP.REG_002CH.WORD = InData_PubKey[15];
            r_rsip_func101(0x6152f82dU, 0xd072b9f0U, 0x00d00865U, 0x4f2f2fdaU);
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
            RSIP.REG_002CH.WORD = InData_PubKey[0];
            RSIP.REG_0024H.WORD = 0x00000000U;
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x0000e202U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x7d2c84e8U, 0xd3ee52bcU, 0x6d1108d0U, 0xd71b12acU);
            r_rsip_func043();
            r_rsip_func075();
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x0000e202U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x12ec7f0eU, 0xa60fedf6U, 0x070fda81U, 0x9764ff7aU);
            r_rsip_func044();
            RSIP.REG_0014H.WORD = 0x000000a1U;
            RSIP.REG_00D0H.WORD = 0x08000044U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x00000000U);
            RSIP.REG_0014H.WORD = 0x00000fc1U;
            RSIP.REG_00D4H.WORD = 0x40000300U;
            RSIP.REG_00D0H.WORD = 0xe8009107U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_PubKey[1];
            RSIP.REG_002CH.WORD = InData_PubKey[2];
            RSIP.REG_002CH.WORD = InData_PubKey[3];
            RSIP.REG_002CH.WORD = InData_PubKey[4];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_PubKey[5];
            RSIP.REG_002CH.WORD = InData_PubKey[6];
            RSIP.REG_002CH.WORD = InData_PubKey[7];
            RSIP.REG_002CH.WORD = InData_PubKey[8];
            RSIP.REG_00B0H.WORD = 0x0000140fU;
            RSIP.REG_0000H.WORD = 0x00c10021U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_PubKey[9];
            RSIP.REG_002CH.WORD = InData_PubKey[10];
            RSIP.REG_002CH.WORD = InData_PubKey[11];
            RSIP.REG_002CH.WORD = InData_PubKey[12];
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = InData_PubKey[13];
            RSIP.REG_002CH.WORD = InData_PubKey[14];
            RSIP.REG_002CH.WORD = InData_PubKey[15];
            RSIP.REG_002CH.WORD = InData_PubKey[16];
            RSIP.REG_00B0H.WORD = 0x00001414U;
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
            RSIP.REG_002CH.WORD = InData_PubKey[17];
            RSIP.REG_002CH.WORD = InData_PubKey[18];
            RSIP.REG_002CH.WORD = InData_PubKey[19];
            RSIP.REG_002CH.WORD = InData_PubKey[20];
            RSIP.REG_00D0H.WORD = 0x9c100005U;
            RSIP.REG_0000H.WORD = 0x00410011U;
            /* WAIT_LOOP */
            while (0U != RSIP.REG_0004H.BIT.B30)
            {
                /* waiting */
            }
            RSIP.REG_0040H.WORD = 0x00001800U;
            r_rsip_func100(0xe1d90893U, 0xf70d5a5dU, 0x3f1bcb9fU, 0x5eebf75aU);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0x18ebe4c6U, 0x8ae58456U, 0x6bfe17afU, 0xbdd170a4U);
                RSIP.REG_006CH.WORD = 0x00000040U;
                /* WAIT_LOOP */
                while (0U != RSIP.REG_0020H.BIT.B12)
                {
                    /* waiting */
                }
                return RSIP_RET_KEY_FAIL;
            }
            else
            {
                r_rsip_func101(0x9ca8eab3U, 0x313a6f9fU, 0xd4fc06d5U, 0xdaf05080U);
            }
        }
        r_rsip_func008();
        r_rsip_func100(0x67446e67U, 0x32ffa6e4U, 0x5b91ec14U, 0x9cc29331U);
        RSIP.REG_0040H.WORD = 0x00400000U;
        RSIP.REG_0024H.WORD = 0x00000000U;
        if (1U == (RSIP.REG_0040H.BIT.B22))
        {
            r_rsip_func102(0xb9960e7bU, 0xacfe3463U, 0x64d07a1dU, 0x3cc64f1fU);
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
            RSIP.REG_0014H.WORD = 0x000000a7U;
            RSIP.REG_009CH.WORD = 0x800100e0U;
            /* WAIT_LOOP */
            while (1U != RSIP.REG_0014H.BIT.B31)
            {
                /* waiting */
            }
            RSIP.REG_002CH.WORD = bswap_32big(0x000000e2U);
            RSIP.REG_0024H.WORD = 0x00000000U;
            r_rsip_func101(0x96cf917bU, 0x2611674bU, 0xb910774bU, 0xffdcaaf7U);
            r_rsip_func088_r1();
            r_rsip_func100(0x6b085188U, 0x50177953U, 0x05829dbcU, 0x280b61faU);
            RSIP.REG_0040H.WORD = 0x00400000U;
            RSIP.REG_0024H.WORD = 0x00000000U;
            if (1U == (RSIP.REG_0040H.BIT.B22))
            {
                r_rsip_func102(0x2395de3dU, 0x0c7bce64U, 0x02afd10eU, 0xd7af2e93U);
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
                r_rsip_func100(0x633f20c5U, 0x7ef453e5U, 0x57abced7U, 0xdcf3a8ceU);
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
                RSIP.REG_002CH.WORD = bswap_32big(0x0000e203U);
                RSIP.REG_0024H.WORD = 0x00000000U;
                r_rsip_func101(0x979bbcbfU, 0xe6787521U, 0x6b71b3b0U, 0x3abe9d4aU);
                r_rsip_func043();
                RSIP.REG_0094H.WORD = 0x0000b4c0U;
                RSIP.REG_0094H.WORD = 0x015c5d71U;
                RSIP.REG_0014H.WORD = 0x000000a7U;
                RSIP.REG_009CH.WORD = 0x800100e0U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0014H.BIT.B31)
                {
                    /* waiting */
                }
                RSIP.REG_002CH.WORD = bswap_32big(0x0000e203U);
                RSIP.REG_0024H.WORD = 0x00000000U;
                r_rsip_func101(0x98323906U, 0x60065e04U, 0x0f513316U, 0x1439f558U);
                r_rsip_func044();
                r_rsip_func100(0x34178001U, 0xc4bac395U, 0xdd33c0c6U, 0x6be23dbeU);
                RSIP.REG_00B0H.WORD = 0x00001828U;
                RSIP.REG_00D4H.WORD = 0x40000100U;
                RSIP.REG_00D0H.WORD = 0xe7009d07U;
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
                OutData_EncSecret[1] = RSIP.REG_002CH.WORD;
                OutData_EncSecret[2] = RSIP.REG_002CH.WORD;
                OutData_EncSecret[3] = RSIP.REG_002CH.WORD;
                OutData_EncSecret[4] = RSIP.REG_002CH.WORD;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0008H.BIT.B30)
                {
                    /* waiting */
                }
                OutData_EncSecret[5] = RSIP.REG_002CH.WORD;
                OutData_EncSecret[6] = RSIP.REG_002CH.WORD;
                OutData_EncSecret[7] = RSIP.REG_002CH.WORD;
                OutData_EncSecret[8] = RSIP.REG_002CH.WORD;
                r_rsip_func100(0x622caa06U, 0x546d4cc5U, 0xad77e782U, 0xe5f493a4U);
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
                OutData_EncSecret[9] = RSIP.REG_002CH.WORD;
                OutData_EncSecret[10] = RSIP.REG_002CH.WORD;
                OutData_EncSecret[11] = RSIP.REG_002CH.WORD;
                OutData_EncSecret[12] = RSIP.REG_002CH.WORD;
                r_rsip_func100(0x1d11e5d2U, 0xe9c2019eU, 0x1c6a64c9U, 0x4099afbbU);
                RSIP.REG_009CH.WORD = 0x81010000U;
                RSIP.REG_0008H.WORD = 0x00005006U;
                /* WAIT_LOOP */
                while (1U != RSIP.REG_0008H.BIT.B30)
                {
                    /* waiting */
                }
                OutData_EncSecret[0] = RSIP.REG_002CH.WORD;
                r_rsip_func102(0xa485c58cU, 0x112a75daU, 0x2cd531cdU, 0xd7dff738U);
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
