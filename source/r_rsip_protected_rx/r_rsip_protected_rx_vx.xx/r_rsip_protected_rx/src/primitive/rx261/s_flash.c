/*
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : s_flash.c
* Description  : Key information file.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.10.2024 1.00     First Release.
*         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
*         :                     Revised key management specification
***********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_rsip_primitive.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

uint32_t const S_FLASH[] =
{
    BSWAP_32BIG_C(0x598b520f), BSWAP_32BIG_C(0x4cc4e88a), BSWAP_32BIG_C(0x56f1fb63), BSWAP_32BIG_C(0x6260146f),
    BSWAP_32BIG_C(0x829fc2bd), BSWAP_32BIG_C(0xeae42a22), BSWAP_32BIG_C(0x5ab77087), BSWAP_32BIG_C(0xd630d4a5),
    BSWAP_32BIG_C(0xcec7387b), BSWAP_32BIG_C(0x18a3f229), BSWAP_32BIG_C(0xad92ba93), BSWAP_32BIG_C(0x77f60115),
    BSWAP_32BIG_C(0x9e834698), BSWAP_32BIG_C(0x05a4b4fc), BSWAP_32BIG_C(0x15229d00), BSWAP_32BIG_C(0x29af942b),
    BSWAP_32BIG_C(0xf4ee104a), BSWAP_32BIG_C(0x2ed0baeb), BSWAP_32BIG_C(0x14529324), BSWAP_32BIG_C(0x963c3a01),
    BSWAP_32BIG_C(0xafc16504), BSWAP_32BIG_C(0xb293e328), BSWAP_32BIG_C(0x28e19822), BSWAP_32BIG_C(0xbeb155f2),
    BSWAP_32BIG_C(0xc1918e3c), BSWAP_32BIG_C(0xeabf2682), BSWAP_32BIG_C(0x19e49ed4), BSWAP_32BIG_C(0x8e42fbca),
    BSWAP_32BIG_C(0x1408616e), BSWAP_32BIG_C(0xebef4d0a), BSWAP_32BIG_C(0x5559b070), BSWAP_32BIG_C(0xf31ee20c),
    BSWAP_32BIG_C(0x8a70c196), BSWAP_32BIG_C(0x3975a772), BSWAP_32BIG_C(0x0cf5839b), BSWAP_32BIG_C(0x65d78f83),
    BSWAP_32BIG_C(0x80112674), BSWAP_32BIG_C(0xcc80e96a), BSWAP_32BIG_C(0xb5c5a0c0), BSWAP_32BIG_C(0xb05fdae6),
    BSWAP_32BIG_C(0x371500ee), BSWAP_32BIG_C(0x40ddb8c4), BSWAP_32BIG_C(0xe5105077), BSWAP_32BIG_C(0xb7fd4eda),
    BSWAP_32BIG_C(0x7b16b4cf), BSWAP_32BIG_C(0x1549a130), BSWAP_32BIG_C(0x18059c65), BSWAP_32BIG_C(0x87f720b0),
    BSWAP_32BIG_C(0xf0d80162), BSWAP_32BIG_C(0x9f967f56), BSWAP_32BIG_C(0x6281e2fd), BSWAP_32BIG_C(0x3d7f5d1b),
    BSWAP_32BIG_C(0x49f16258), BSWAP_32BIG_C(0x1495ce2e), BSWAP_32BIG_C(0xde4d034a), BSWAP_32BIG_C(0x2fbdaad3),
    BSWAP_32BIG_C(0xa13196ad), BSWAP_32BIG_C(0x39271586), BSWAP_32BIG_C(0x72d6f3d5), BSWAP_32BIG_C(0xc5537a70),
    BSWAP_32BIG_C(0xcb1fef6f), BSWAP_32BIG_C(0xa169f250), BSWAP_32BIG_C(0x49fdaf45), BSWAP_32BIG_C(0x48d992f4),
    BSWAP_32BIG_C(0xcf2d3f4b), BSWAP_32BIG_C(0x4afb8084), BSWAP_32BIG_C(0x25a55044), BSWAP_32BIG_C(0xe7f5f0f5),
    BSWAP_32BIG_C(0xcb3a1225), BSWAP_32BIG_C(0xc3b907db), BSWAP_32BIG_C(0x6e5075d3), BSWAP_32BIG_C(0x9b05fd6f),
    BSWAP_32BIG_C(0xb446b895), BSWAP_32BIG_C(0x22dab125), BSWAP_32BIG_C(0x4053ec4d), BSWAP_32BIG_C(0xe847ecf2),
    BSWAP_32BIG_C(0x226a13f2), BSWAP_32BIG_C(0xced05159), BSWAP_32BIG_C(0x61e33bc2), BSWAP_32BIG_C(0x902d326d),
    BSWAP_32BIG_C(0x8c97fac9), BSWAP_32BIG_C(0x3dc24a87), BSWAP_32BIG_C(0x28b177ce), BSWAP_32BIG_C(0x7f330dbb),
    BSWAP_32BIG_C(0x48bd9277), BSWAP_32BIG_C(0x3ca20ea5), BSWAP_32BIG_C(0x4f493828), BSWAP_32BIG_C(0x53b0b9dd),
    BSWAP_32BIG_C(0x91873ea7), BSWAP_32BIG_C(0x9c30a704), BSWAP_32BIG_C(0x0511e053), BSWAP_32BIG_C(0x5f9067a9),
    BSWAP_32BIG_C(0x746acc8d), BSWAP_32BIG_C(0x7f45c1a6), BSWAP_32BIG_C(0x20c0f4ab), BSWAP_32BIG_C(0x60344cc7),
    BSWAP_32BIG_C(0xf5d2e261), BSWAP_32BIG_C(0xecd45b7c), BSWAP_32BIG_C(0x29b668e6), BSWAP_32BIG_C(0x0677687d),
    BSWAP_32BIG_C(0x487af40a), BSWAP_32BIG_C(0xb7e70fa7), BSWAP_32BIG_C(0x062fd9fe), BSWAP_32BIG_C(0x4aeff2bb),
    BSWAP_32BIG_C(0x81739e2a), BSWAP_32BIG_C(0xeeab3688), BSWAP_32BIG_C(0x6ecacb5c), BSWAP_32BIG_C(0x8f94392d),
    BSWAP_32BIG_C(0xddde7935), BSWAP_32BIG_C(0x8c46dd38), BSWAP_32BIG_C(0xddefdb31), BSWAP_32BIG_C(0x98c38ab7),
    BSWAP_32BIG_C(0xe830f8d3), BSWAP_32BIG_C(0xd804b2ce), BSWAP_32BIG_C(0x825699e2), BSWAP_32BIG_C(0x2258975a),
    BSWAP_32BIG_C(0x47dfb4e6), BSWAP_32BIG_C(0xd795582c), BSWAP_32BIG_C(0xf1b4edc0), BSWAP_32BIG_C(0x05551baf),
    BSWAP_32BIG_C(0x005b2b00), BSWAP_32BIG_C(0xc0e01b11), BSWAP_32BIG_C(0xbdcf1b2e), BSWAP_32BIG_C(0x501d0da4),
    BSWAP_32BIG_C(0x094e7e00), BSWAP_32BIG_C(0x2fec710b), BSWAP_32BIG_C(0x9a92cdbd), BSWAP_32BIG_C(0x35bbbebf),
};
