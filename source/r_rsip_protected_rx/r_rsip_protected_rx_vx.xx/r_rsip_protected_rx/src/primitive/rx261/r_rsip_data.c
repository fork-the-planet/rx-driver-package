/*
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_rsip_data.c
 * Version      : 2.00
 * Description  : DomainParam data information file.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 15.10.2024 1.00     First Release.
 *         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
 *         :                     Revised key management specification
 *********************************************************************************************************************/

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

uint32_t S_RAM[RSIP_PRV_WORD_SIZE_S_RAM];
uint32_t const * S_INST2;
uint32_t INST_DATA_SIZE;

uint32_t const DomainParam_NIST_P256[] =
{
    BSWAP_32BIG_C(0x8f0da443), BSWAP_32BIG_C(0x914cbf02), BSWAP_32BIG_C(0x303997c8), BSWAP_32BIG_C(0x969aaf18),
    BSWAP_32BIG_C(0xb0dca52f), BSWAP_32BIG_C(0xc2a04522), BSWAP_32BIG_C(0x9404cf9a), BSWAP_32BIG_C(0xde850246),
    BSWAP_32BIG_C(0xe027863d), BSWAP_32BIG_C(0xe1669751), BSWAP_32BIG_C(0x05b20b64), BSWAP_32BIG_C(0x208fc58f),
    BSWAP_32BIG_C(0x9a652c40), BSWAP_32BIG_C(0x794ac9d8), BSWAP_32BIG_C(0xa832f746), BSWAP_32BIG_C(0x2e6f360c),
    BSWAP_32BIG_C(0xe75dadf1), BSWAP_32BIG_C(0x5737ec8e), BSWAP_32BIG_C(0xf9a7fe4c), BSWAP_32BIG_C(0x35932bd8),
    BSWAP_32BIG_C(0x01b44349), BSWAP_32BIG_C(0x075f7723), BSWAP_32BIG_C(0x57711751), BSWAP_32BIG_C(0xb967f0f8),
    BSWAP_32BIG_C(0x126bcc05), BSWAP_32BIG_C(0x73ce1cfc), BSWAP_32BIG_C(0x4f47f1c3), BSWAP_32BIG_C(0x7922a4a0),
    BSWAP_32BIG_C(0x4455b2d2), BSWAP_32BIG_C(0x7f9de42e), BSWAP_32BIG_C(0x6b1e756a), BSWAP_32BIG_C(0x5e08eadc),
    BSWAP_32BIG_C(0xd2b103bf), BSWAP_32BIG_C(0x6c335fc9), BSWAP_32BIG_C(0x1afb1895), BSWAP_32BIG_C(0xc4733935),
    BSWAP_32BIG_C(0x4cb0ba7f), BSWAP_32BIG_C(0xf5a8191a), BSWAP_32BIG_C(0x9f116bed), BSWAP_32BIG_C(0x6c870f68),
    BSWAP_32BIG_C(0x2ac8ce42), BSWAP_32BIG_C(0xb65de50c), BSWAP_32BIG_C(0xb874409f), BSWAP_32BIG_C(0x8216e57c),
    BSWAP_32BIG_C(0x14c0a1a4), BSWAP_32BIG_C(0x12f84f73), BSWAP_32BIG_C(0x4395e787), BSWAP_32BIG_C(0x3c2faff3),
    BSWAP_32BIG_C(0x48843417), BSWAP_32BIG_C(0xd11e8c64), BSWAP_32BIG_C(0x30f7692a), BSWAP_32BIG_C(0xd92782c0),
    BSWAP_32BIG_C(0x81566388), BSWAP_32BIG_C(0xb748d2ea), BSWAP_32BIG_C(0xc3c3ea80), BSWAP_32BIG_C(0x57ba8f2a),
    BSWAP_32BIG_C(0x7d65828b), BSWAP_32BIG_C(0x4a2ff618), BSWAP_32BIG_C(0x7f7e5ffa), BSWAP_32BIG_C(0x4f8e4559),
    BSWAP_32BIG_C(0x0b7579d8), BSWAP_32BIG_C(0xfbbef790), BSWAP_32BIG_C(0x8e80e84a), BSWAP_32BIG_C(0x7bc1b618),
    BSWAP_32BIG_C(0x9a2cf683), BSWAP_32BIG_C(0x9f5ee1bb), BSWAP_32BIG_C(0x06be7b17), BSWAP_32BIG_C(0x70a3d16a),
    BSWAP_32BIG_C(0x7b07a979), BSWAP_32BIG_C(0xc97e1b21), BSWAP_32BIG_C(0xee0e3ec7), BSWAP_32BIG_C(0xdf1f84fc),
};

uint32_t const DomainParam_Brainpool_256r1[] =
{
    BSWAP_32BIG_C(0x37c84908), BSWAP_32BIG_C(0x221daa49), BSWAP_32BIG_C(0x74a644b5), BSWAP_32BIG_C(0x973e9429),
    BSWAP_32BIG_C(0xbd3fadee), BSWAP_32BIG_C(0x762982d3), BSWAP_32BIG_C(0x6c9b9d28), BSWAP_32BIG_C(0x641314f6),
    BSWAP_32BIG_C(0x21bb14c6), BSWAP_32BIG_C(0xf31be15e), BSWAP_32BIG_C(0x9b706906), BSWAP_32BIG_C(0x210041c0),
    BSWAP_32BIG_C(0xd826e327), BSWAP_32BIG_C(0xb118d370), BSWAP_32BIG_C(0x7075f9d0), BSWAP_32BIG_C(0x32837602),
    BSWAP_32BIG_C(0xe963a917), BSWAP_32BIG_C(0x7775d863), BSWAP_32BIG_C(0x664fec12), BSWAP_32BIG_C(0x2f4f66fe),
    BSWAP_32BIG_C(0x27837c9f), BSWAP_32BIG_C(0xa7b8b8cb), BSWAP_32BIG_C(0x660f7ce3), BSWAP_32BIG_C(0xb54f3437),
    BSWAP_32BIG_C(0xea778abc), BSWAP_32BIG_C(0x260d6381), BSWAP_32BIG_C(0x8e7e938e), BSWAP_32BIG_C(0xe8ab8210),
    BSWAP_32BIG_C(0x8a577b24), BSWAP_32BIG_C(0x4b428639), BSWAP_32BIG_C(0xaf927c4c), BSWAP_32BIG_C(0x66e6f0f4),
    BSWAP_32BIG_C(0x586ee63a), BSWAP_32BIG_C(0x6d811862), BSWAP_32BIG_C(0xc4ac49f7), BSWAP_32BIG_C(0xa307bfea),
    BSWAP_32BIG_C(0x1fab608f), BSWAP_32BIG_C(0x14e079a4), BSWAP_32BIG_C(0x96197cf6), BSWAP_32BIG_C(0xe92beb58),
    BSWAP_32BIG_C(0xf8dd1805), BSWAP_32BIG_C(0xb6ec804b), BSWAP_32BIG_C(0xe24a01e0), BSWAP_32BIG_C(0x0308554a),
    BSWAP_32BIG_C(0x7a40ebe0), BSWAP_32BIG_C(0x882d5ef1), BSWAP_32BIG_C(0xf5c90126), BSWAP_32BIG_C(0x5c76c5a2),
    BSWAP_32BIG_C(0x0ec3df93), BSWAP_32BIG_C(0x7adf2887), BSWAP_32BIG_C(0xebfa9dd9), BSWAP_32BIG_C(0xcd03ccd9),
    BSWAP_32BIG_C(0x67f29ee5), BSWAP_32BIG_C(0x856f066d), BSWAP_32BIG_C(0xc40df71c), BSWAP_32BIG_C(0x75ed2fc2),
    BSWAP_32BIG_C(0xe13993b0), BSWAP_32BIG_C(0xc86a494d), BSWAP_32BIG_C(0x09dadbb8), BSWAP_32BIG_C(0xc753f37a),
    BSWAP_32BIG_C(0x6dc49275), BSWAP_32BIG_C(0x50db88ff), BSWAP_32BIG_C(0xe2bc58fc), BSWAP_32BIG_C(0xf3407381),
    BSWAP_32BIG_C(0x16590237), BSWAP_32BIG_C(0xcf2cb7d8), BSWAP_32BIG_C(0x8b490f14), BSWAP_32BIG_C(0x4205721f),
    BSWAP_32BIG_C(0x60d6f56d), BSWAP_32BIG_C(0x9571de00), BSWAP_32BIG_C(0x5dbc522e), BSWAP_32BIG_C(0x0470d2fe),
};

uint32_t const DomainParam_Koblitz_secp256k1[] =
{
    BSWAP_32BIG_C(0x161a3329), BSWAP_32BIG_C(0x79d885af), BSWAP_32BIG_C(0x931a8fa1), BSWAP_32BIG_C(0x1aba764d),
    BSWAP_32BIG_C(0x618d8880), BSWAP_32BIG_C(0xe3c4921c), BSWAP_32BIG_C(0x92494aa8), BSWAP_32BIG_C(0x63c6d484),
    BSWAP_32BIG_C(0xade64611), BSWAP_32BIG_C(0x13d6980e), BSWAP_32BIG_C(0xf809b903), BSWAP_32BIG_C(0x45c84312),
    BSWAP_32BIG_C(0xf75c371a), BSWAP_32BIG_C(0x1ce38c3d), BSWAP_32BIG_C(0x7bd781e9), BSWAP_32BIG_C(0x5f35ba02),
    BSWAP_32BIG_C(0x2ec11001), BSWAP_32BIG_C(0xb0d7a4b6), BSWAP_32BIG_C(0xc5e98818), BSWAP_32BIG_C(0x760b1d1c),
    BSWAP_32BIG_C(0x431b4786), BSWAP_32BIG_C(0xc9fe62f6), BSWAP_32BIG_C(0x6b3fa7d3), BSWAP_32BIG_C(0x975b43b1),
    BSWAP_32BIG_C(0xf302e005), BSWAP_32BIG_C(0x6ec1c81c), BSWAP_32BIG_C(0xd666780c), BSWAP_32BIG_C(0x8a8b9b2c),
    BSWAP_32BIG_C(0x8fbdcbf2), BSWAP_32BIG_C(0xc86a43e4), BSWAP_32BIG_C(0xf12b3e2b), BSWAP_32BIG_C(0x2d1a6dd9),
    BSWAP_32BIG_C(0xe27bfd51), BSWAP_32BIG_C(0x7f3c0e2c), BSWAP_32BIG_C(0xd4621fb0), BSWAP_32BIG_C(0x4fd1efed),
    BSWAP_32BIG_C(0xc4d2213f), BSWAP_32BIG_C(0x687734aa), BSWAP_32BIG_C(0xabfd6c20), BSWAP_32BIG_C(0x730b5cca),
    BSWAP_32BIG_C(0x5fc409bb), BSWAP_32BIG_C(0x97f5a069), BSWAP_32BIG_C(0x2fda9ba2), BSWAP_32BIG_C(0x37843787),
    BSWAP_32BIG_C(0x7736fee9), BSWAP_32BIG_C(0x71ae96ed), BSWAP_32BIG_C(0x905dc6f0), BSWAP_32BIG_C(0x8834bc3c),
    BSWAP_32BIG_C(0x95143b11), BSWAP_32BIG_C(0xfbaba1c1), BSWAP_32BIG_C(0xff1f0e87), BSWAP_32BIG_C(0x4edd0d43),
    BSWAP_32BIG_C(0xd2774197), BSWAP_32BIG_C(0x2d8b5a5b), BSWAP_32BIG_C(0x3f988cb1), BSWAP_32BIG_C(0x0872d16a),
    BSWAP_32BIG_C(0x79fd8537), BSWAP_32BIG_C(0x5524de39), BSWAP_32BIG_C(0xcb06b339), BSWAP_32BIG_C(0x12bd2084),
    BSWAP_32BIG_C(0xaa393c73), BSWAP_32BIG_C(0x5af462bb), BSWAP_32BIG_C(0xa71ffda9), BSWAP_32BIG_C(0x01c3c14d),
    BSWAP_32BIG_C(0xceea4121), BSWAP_32BIG_C(0x6b0ee88c), BSWAP_32BIG_C(0x88154656), BSWAP_32BIG_C(0x9e63ae1f),
    BSWAP_32BIG_C(0x670564ba), BSWAP_32BIG_C(0xf90f3d82), BSWAP_32BIG_C(0x93a746c1), BSWAP_32BIG_C(0x0deeb748),
};

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
