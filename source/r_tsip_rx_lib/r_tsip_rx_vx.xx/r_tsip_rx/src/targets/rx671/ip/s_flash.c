/*
 * Copyright (c) 2015 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : s_flash.c
 * Version      : 1.22
 * Description  : Key information file.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 31.03.2020 1.09     First Release
 *         : 30.06.2020 1.10     Added support for ARC4, ECC(P-384) API
 *         : 30.09.2020 1.11     Added support for DH, ECDHE P-512r1 API, and generalization of KDF.
 *         :                     Added support for Key wrap API with TSIP-Lite.
 *         : 30.06.2021 1.12     Added support for RX23W chip version D
 *         : 31.08.2021 1.13     Added support for RX671
 *         : 10.04.2025 1.22     Added support for RSAES-OAEP, SSH
 *         :                     Updated Firmware Update API
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_tsip_rx_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
TSIP_SEC_C_SECURE_BOOT
uint32_t const S_FLASH[] =
{
#if defined __LIT
    0x58b94f05, 0x69118037, 0x1e0d60b0, 0xf2444885,
    0x267cc7b3, 0x58e3d8f1, 0x4da88280, 0x993fda62,
    0xd9e6038c, 0x44beac5d, 0x1142b8b0, 0xc525ff20,
    0x1f410b8b, 0xde783f14, 0xf4f7ca28, 0xdc7ec3da,
    0x462b9584, 0x24fc88a3, 0x357166dc, 0x174fe261,
    0x20cf755e, 0x57ea9a43, 0x92aebce9, 0x71b97ab4,
    0xecf4377f, 0xafca6fe7, 0x8c14ece9, 0x83805ca6,
    0xe28fed5d, 0x971c1e15, 0xf5a98f8d, 0x23948457,
    0xd3bf47ff, 0x168e5ef5, 0xdfb6b9a8, 0x9c7421d2,
    0x00c2d6aa, 0xb4ff7f05, 0x9a519f1f, 0x6f951885,
    0xd0d01d13, 0xbc94376e, 0x7b85e4af, 0x91e82368,
    0x1ad406ef, 0x16ded719, 0xe5ef1293, 0x83a88493,
    0x5cc11f6d, 0x05ac5dff, 0x70438588, 0x0c700f74,
    0x3b531b1c, 0x3e19b9a4, 0x86576b31, 0x3388ebab,
    0x4aac5f57, 0x86cf7194, 0xd6e0fd98, 0xa5b15e7f,
    0x92673eaf, 0x19b82afd, 0xdeb547c7, 0x64d80e44,
    0xba78b5d8, 0x031ad197, 0x2dc576ef, 0xf347128a,
    0x7cad96f4, 0xf123c38b, 0xca5f1eed, 0xb8168c29,
    0xdf95c2ab, 0x000dc1ca, 0xb37613c3, 0xe90a8e38,
    0x7e0dc6e6, 0xf1a75761, 0xf7b50aee, 0xbcd2d243,
    0xf37c1929, 0x5bf7d8b9, 0xc8204c35, 0x8dca796f,
    0xee249122, 0x6df40b2e, 0x60aa5edf, 0x27a51289,
    0xcfff8b2a, 0x6c376ef9, 0xe63dd6f7, 0x93baf48a,
    0x7b5ed2a7, 0xeea3435e, 0xe7512d6e, 0xa42e5269,
    0xba60ab2d, 0x0d30afd2, 0x9ba8f1e7, 0xbb7b67cf,
    0x92e20f43, 0x6fc07c88, 0xe4076014, 0x58edef86,
    0xf8159b75, 0x4e20bf3a, 0xc84b8e40, 0x06f40659,
    0xafe12f56, 0xb3fc85c9, 0x2717d76a, 0x911d269e,
    0x48306892, 0xb40a7811, 0x8bdeed7c, 0xfa023756,
    0x408c847f, 0x10786790, 0xe608eb62, 0x3a47d62b,
    0xb7f5bec2, 0xd7899bb6, 0xe26dbcb9, 0x952ad7af,
    0xeba9329a, 0xe28b083d, 0x809da34d, 0x072c725f,
#else   /* defined __LIT */
    0x054fb958, 0x37801169, 0xb0600d1e, 0x854844f2,
    0xb3c77c26, 0xf1d8e358, 0x8082a84d, 0x62da3f99,
    0x8c03e6d9, 0x5dacbe44, 0xb0b84211, 0x20ff25c5,
    0x8b0b411f, 0x143f78de, 0x28caf7f4, 0xdac37edc,
    0x84952b46, 0xa388fc24, 0xdc667135, 0x61e24f17,
    0x5e75cf20, 0x439aea57, 0xe9bcae92, 0xb47ab971,
    0x7f37f4ec, 0xe76fcaaf, 0xe9ec148c, 0xa65c8083,
    0x5ded8fe2, 0x151e1c97, 0x8d8fa9f5, 0x57849423,
    0xff47bfd3, 0xf55e8e16, 0xa8b9b6df, 0xd221749c,
    0xaad6c200, 0x057fffb4, 0x1f9f519a, 0x8518956f,
    0x131dd0d0, 0x6e3794bc, 0xafe4857b, 0x6823e891,
    0xef06d41a, 0x19d7de16, 0x9312efe5, 0x9384a883,
    0x6d1fc15c, 0xff5dac05, 0x88854370, 0x740f700c,
    0x1c1b533b, 0xa4b9193e, 0x316b5786, 0xabeb8833,
    0x575fac4a, 0x9471cf86, 0x98fde0d6, 0x7f5eb1a5,
    0xaf3e6792, 0xfd2ab819, 0xc747b5de, 0x440ed864,
    0xd8b578ba, 0x97d11a03, 0xef76c52d, 0x8a1247f3,
    0xf496ad7c, 0x8bc323f1, 0xed1e5fca, 0x298c16b8,
    0xabc295df, 0xcac10d00, 0xc31376b3, 0x388e0ae9,
    0xe6c60d7e, 0x6157a7f1, 0xee0ab5f7, 0x43d2d2bc,
    0x29197cf3, 0xb9d8f75b, 0x354c20c8, 0x6f79ca8d,
    0x229124ee, 0x2e0bf46d, 0xdf5eaa60, 0x8912a527,
    0x2a8bffcf, 0xf96e376c, 0xf7d63de6, 0x8af4ba93,
    0xa7d25e7b, 0x5e43a3ee, 0x6e2d51e7, 0x69522ea4,
    0x2dab60ba, 0xd2af300d, 0xe7f1a89b, 0xcf677bbb,
    0x430fe292, 0x887cc06f, 0x146007e4, 0x86efed58,
    0x759b15f8, 0x3abf204e, 0x408e4bc8, 0x5906f406,
    0x562fe1af, 0xc985fcb3, 0x6ad71727, 0x9e261d91,
    0x92683048, 0x11780ab4, 0x7cedde8b, 0x563702fa,
    0x7f848c40, 0x90677810, 0x62eb08e6, 0x2bd6473a,
    0xc2bef5b7, 0xb69b89d7, 0xb9bc6de2, 0xafd72a95,
    0x9a32a9eb, 0x3d088be2, 0x4da39d80, 0x5f722c07,
#endif  /* defined __LIT */
};
TSIP_SEC_DEFAULT

uint32_t const DomainParam_NIST_P256[188] =
{
#if defined __LIT
    0x20e4cb18, 0xbf434391, 0x22360c8e, 0x1e9748ad,
    0x88d49b0a, 0x9120868b, 0xd5ab695f, 0x141ad242,
    0x3e9fa2b1, 0x43553b41, 0xf9fd7d40, 0x6706f2f4,
    0xd630fa1e, 0x017c3616, 0xea2cbb4b, 0xffb07f44,
    0xdde04222, 0x18503b6c, 0xc1111c0a, 0x7d9adb85,
    0x43e7f813, 0x31efac4d, 0x7fcd0ec6, 0x9f5d85ef,
    0x00b597bc, 0x52c87d90, 0xb32fa799, 0xc3f02237,
    0x4b7e6650, 0x60e1c755, 0x3af523cb, 0x62c72ebb,
    0x0187a4a6, 0x52d59159, 0x33352a32, 0x16ce80c4,
    0xc5ba46d0, 0x0e20a6b3, 0x8d5e5992, 0x59184672,
    0x6870d838, 0xa4bb55e0, 0x4d63a477, 0x78b9ff4d,
    0x11cf8003, 0x3950dc2e, 0x55e034b9, 0xf6222820,
    0x8ba0193b, 0x451c7f5a, 0x14a3d10b, 0xd9564310,
    0x61a4d5cb, 0x4c144106, 0xd07f5f2b, 0xff5e9c19,
    0x8822b1ac, 0x34d4f9e8, 0x2e1e24fb, 0x6c2759b9,
    0x098d58cb, 0x3b34c0df, 0x48b7236e, 0xf85753c3,
    0x541d3def, 0x31d6b471, 0x56a0695e, 0x3e025fe5,
    0x030d1f27, 0xfbf65db1, 0x167dc945, 0x51e67775,
    0x7ebf87b5, 0xabc224f0, 0x83bf0923, 0x09721b63,
    0x98ae30a7, 0xbc69b2a3, 0x5053c70c, 0xeb078cd7,
    0xee09bb7e, 0x2530b008, 0x9586d198, 0x2015cf52,
    0xe155f85f, 0x1fdbe234, 0xa70dd456, 0xd343cf05,
    0xbb07b529, 0x88698d4c, 0x823418ac, 0x28917029,
    0x280d13ce, 0xa402c75c, 0x5b0dab55, 0x6b58a68b,
    0x16d49aa1, 0xa810e66a, 0xbc9cda16, 0x86aae70a,
    0xbce4f045, 0x04c779d9, 0x787a17be, 0xd2c7948a,
    0x6b691b4e, 0x6d84aa0c, 0x91c0451b, 0x9b7569bf,
    0xb9c0c5bd, 0xa076784f, 0x592ab454, 0xf9b058a6,
    0x5057bed9, 0x76377037, 0xa94f160c, 0xcfeca80a,
    0xa5a1d661, 0x6ebfd54c, 0xc027da9c, 0x1fc37207,
    0x5d7c01d9, 0xc3eabf2c, 0x756ec29b, 0x22e16a7a,
    0x2b4adb71, 0x61a42e76, 0x9e909b8d, 0x9cf637a1,
    0x4477f8b0, 0x919170ec, 0x24f83f56, 0x0f58dea3,
    0x8044ac59, 0x81701e4b, 0xa5cc9dbb, 0xf22137c9,
    0x8a160d5f, 0x87a33ce0, 0xc96873b1, 0xeae49d0c,
    0x7082a7d1, 0xb218b9aa, 0x2fad4c3c, 0xc71f935a,
    0x8481fa04, 0x0a1193a1, 0x83eec80e, 0x848e2f4e,
    0xef14ec40, 0x3c3bba5b, 0xd8994144, 0x1aea5912,
    0x9635d1ed, 0x8cfb0df0, 0x38948acf, 0x89f6684e,
    0xb7183bd6, 0xaf3354f8, 0xa2a1806d, 0x3c292cba,
    0x6058c8ba, 0xb0f66db1, 0x13af3e2a, 0x5fdd6376,
    0x0db54567, 0xa4c86c02, 0x7006df77, 0xd9882241,
    0x5bbd612a, 0xbbe22d90, 0xb8f7e935, 0xc4aa7467,
    0x42349c31, 0x9db10be3, 0xf4746cbb, 0xe493e79d,
    0x09a7b737, 0x91484629, 0xb63c96d8, 0xf27b935a,
    0x7a419cba, 0x3f02bbcc, 0x3680217f, 0x01ab7c5d,
    0x63dfe5fa, 0xde5c8aff, 0x47c79cd0, 0xab236e2f
#else   /* defined __LIT */
    0x18cbe420, 0x914343bf, 0x8e0c3622, 0xad48971e,
    0x0a9bd488, 0x8b862091, 0x5f69abd5, 0x42d21a14,
    0xb1a29f3e, 0x413b5543, 0x407dfdf9, 0xf4f20667,
    0x1efa30d6, 0x16367c01, 0x4bbb2cea, 0x447fb0ff,
    0x2242e0dd, 0x6c3b5018, 0x0a1c11c1, 0x85db9a7d,
    0x13f8e743, 0x4dacef31, 0xc60ecd7f, 0xef855d9f,
    0xbc97b500, 0x907dc852, 0x99a72fb3, 0x3722f0c3,
    0x50667e4b, 0x55c7e160, 0xcb23f53a, 0xbb2ec762,
    0xa6a48701, 0x5991d552, 0x322a3533, 0xc480ce16,
    0xd046bac5, 0xb3a6200e, 0x92595e8d, 0x72461859,
    0x38d87068, 0xe055bba4, 0x77a4634d, 0x4dffb978,
    0x0380cf11, 0x2edc5039, 0xb934e055, 0x202822f6,
    0x3b19a08b, 0x5a7f1c45, 0x0bd1a314, 0x104356d9,
    0xcbd5a461, 0x0641144c, 0x2b5f7fd0, 0x199c5eff,
    0xacb12288, 0xe8f9d434, 0xfb241e2e, 0xb959276c,
    0xcb588d09, 0xdfc0343b, 0x6e23b748, 0xc35357f8,
    0xef3d1d54, 0x71b4d631, 0x5e69a056, 0xe55f023e,
    0x271f0d03, 0xb15df6fb, 0x45c97d16, 0x7577e651,
    0xb587bf7e, 0xf024c2ab, 0x2309bf83, 0x631b7209,
    0xa730ae98, 0xa3b269bc, 0x0cc75350, 0xd78c07eb,
    0x7ebb09ee, 0x08b03025, 0x98d18695, 0x52cf1520,
    0x5ff855e1, 0x34e2db1f, 0x56d40da7, 0x05cf43d3,
    0x29b507bb, 0x4c8d6988, 0xac183482, 0x29709128,
    0xce130d28, 0x5cc702a4, 0x55ab0d5b, 0x8ba6586b,
    0xa19ad416, 0x6ae610a8, 0x16da9cbc, 0x0ae7aa86,
    0x45f0e4bc, 0xd979c704, 0xbe177a78, 0x8a94c7d2,
    0x4e1b696b, 0x0caa846d, 0x1b45c091, 0xbf69759b,
    0xbdc5c0b9, 0x4f7876a0, 0x54b42a59, 0xa658b0f9,
    0xd9be5750, 0x37703776, 0x0c164fa9, 0x0aa8eccf,
    0x61d6a1a5, 0x4cd5bf6e, 0x9cda27c0, 0x0772c31f,
    0xd9017c5d, 0x2cbfeac3, 0x9bc26e75, 0x7a6ae122,
    0x71db4a2b, 0x762ea461, 0x8d9b909e, 0xa137f69c,
    0xb0f87744, 0xec709191, 0x563ff824, 0xa3de580f,
    0x59ac4480, 0x4b1e7081, 0xbb9dcca5, 0xc93721f2,
    0x5f0d168a, 0xe03ca387, 0xb17368c9, 0x0c9de4ea,
    0xd1a78270, 0xaab918b2, 0x3c4cad2f, 0x5a931fc7,
    0x04fa8184, 0xa193110a, 0x0ec8ee83, 0x4e2f8e84,
    0x40ec14ef, 0x5bba3b3c, 0x444199d8, 0x1259ea1a,
    0xedd13596, 0xf00dfb8c, 0xcf8a9438, 0x4e68f689,
    0xd63b18b7, 0xf85433af, 0x6d80a1a2, 0xba2c293c,
    0xbac85860, 0xb16df6b0, 0x2a3eaf13, 0x7663dd5f,
    0x6745b50d, 0x026cc8a4, 0x77df0670, 0x412288d9,
    0x2a61bd5b, 0x902de2bb, 0x35e9f7b8, 0x6774aac4,
    0x319c3442, 0xe30bb19d, 0xbb6c74f4, 0x9de793e4,
    0x37b7a709, 0x29464891, 0xd8963cb6, 0x5a937bf2,
    0xba9c417a, 0xccbb023f, 0x7f218036, 0x5d7cab01,
    0xfae5df63, 0xff8a5cde, 0xd09cc747, 0x2f6e23ab
#endif  /* defined __LIT */
};

uint32_t const DomainParam_NIST_P224[188] =
{
#if defined __LIT
    0x598d5549, 0xe1107622, 0x905dcd70, 0x3fa69c67,
    0x751e4739, 0x5efe0a7e, 0xbaabe59e, 0xb29739fc,
    0x96d86330, 0xf0922696, 0x4019e042, 0xd46c8bbe,
    0x44f3c11f, 0x186d96ea, 0x445af5a6, 0x8c8f8b91,
    0xc3b45dd2, 0x0f968ca7, 0xd0146e76, 0x9d33f2a6,
    0x08d9497c, 0xd995b1a4, 0x6e9c0587, 0xd146f9f1,
    0xc19dad14, 0x15190351, 0x90d8ea20, 0x6595cdc1,
    0x87895786, 0x7f5cf3bd, 0xbe64c2e2, 0xc492a38a,
    0xe2117f38, 0x9b6c384b, 0xc244e721, 0x7f6184be,
    0x78dd18b1, 0xe04c2dff, 0x57fad69c, 0x9551a6be,
    0xf96a5251, 0xccf54735, 0xad5dd197, 0x4bbeb02f,
    0x476da342, 0x44efc120, 0x6988a297, 0xe2adf0b7,
    0x21063ccc, 0x53ad9226, 0xf55a1fb6, 0xe250d8ab,
    0xc8426bd0, 0x2a84e8ad, 0x0f8c17a2, 0x59a50cdf,
    0x79ddf9c9, 0xbf62bd22, 0x46999275, 0x1d3a1748,
    0x0b0a2fd5, 0x04b69fc2, 0xbe7c4e77, 0x50fb2984,
    0xe8066325, 0x9e8a3c74, 0x013495ab, 0x960053ef,
    0x22bd1c06, 0x0bf6ecad, 0x7f270718, 0x3828881d,
    0x25d91bd5, 0x0c37b847, 0xe28b2bb5, 0x94a62677,
    0xc74cfb3c, 0x59cc4c50, 0x687ab8cf, 0x18487f97,
    0xc15106cd, 0x0e50c396, 0xb851596d, 0x38f13669,
    0x94ccba7d, 0xad8dac8d, 0x3b4bae0b, 0xe53b4196,
    0x229542ee, 0x2bb6131a, 0xc6b849b8, 0xeec58ccf,
    0xba6d2a94, 0x3a5197c1, 0xde12b214, 0xd723748d,
    0x4b7f5581, 0x49676fbd, 0xd36106d7, 0x25dd6928,
    0x6e91578f, 0xe24549a5, 0x7c575b86, 0x1b1ea0a4,
    0x703788ed, 0x1eccf40e, 0x92a21628, 0xce7a25a4,
    0x977cd51e, 0xbd733bd8, 0xb7cbaeb4, 0x81275107,
    0x9c90f47f, 0xe31112bb, 0x5df9497b, 0xafefde0c,
    0x0b903650, 0x6f7d1831, 0x82831cd4, 0x64110a50,
    0x5a80ef62, 0xaaa336b5, 0x4b897291, 0xf8668554,
    0x467b02cf, 0xec441d23, 0xd61933f6, 0xb11fc49a,
    0x5f40519d, 0x9941b190, 0x3e677e4e, 0x9f24075b,
    0xebddf091, 0x9d21ff05, 0xc546b6b4, 0x0102252e,
    0xcbd9279b, 0x9e1fd1bf, 0x270e4af9, 0xd67910af,
    0x5ed663a8, 0x825c2248, 0x23ea7651, 0xa16dd66b,
    0x303dd122, 0x5c7a0728, 0x21256c93, 0x1a313229,
    0xf97f31dd, 0x7af71ac2, 0x40f1198a, 0x6ae0459d,
    0x766b6285, 0x4ba86e91, 0xb4bb190d, 0x56e2020f,
    0xe7b6dfa1, 0xc43564cd, 0xed587323, 0xfb035e9a,
    0xee2fd9cf, 0x4f526946, 0x50cc4677, 0xb54d4ed1,
    0x6eb8e850, 0x24ccd355, 0xfc64d0ef, 0xf23a332f,
    0xf68ba3f6, 0xd4e75de6, 0x4b5ba063, 0x44d00837,
    0xdcac2c87, 0x6ad4dff1, 0xb5350ccd, 0x0c11f983,
    0xa7236cfc, 0x69b03212, 0x7d035383, 0xacfc861e,
    0x6a541114, 0x5639df52, 0x2a43279e, 0x25e7deaf,
    0x08114db9, 0x4d54c8e8, 0xeb085c74, 0xce404724
#else   /* defined __LIT */
    0x49558d59, 0x227610e1, 0x70cd5d90, 0x679ca63f,
    0x39471e75, 0x7e0afe5e, 0x9ee5abba, 0xfc3997b2,
    0x3063d896, 0x962692f0, 0x42e01940, 0xbe8b6cd4,
    0x1fc1f344, 0xea966d18, 0xa6f55a44, 0x918b8f8c,
    0xd25db4c3, 0xa78c960f, 0x766e14d0, 0xa6f2339d,
    0x7c49d908, 0xa4b195d9, 0x87059c6e, 0xf1f946d1,
    0x14ad9dc1, 0x51031915, 0x20ead890, 0xc1cd9565,
    0x86578987, 0xbdf35c7f, 0xe2c264be, 0x8aa392c4,
    0x387f11e2, 0x4b386c9b, 0x21e744c2, 0xbe84617f,
    0xb118dd78, 0xff2d4ce0, 0x9cd6fa57, 0xbea65195,
    0x51526af9, 0x3547f5cc, 0x97d15dad, 0x2fb0be4b,
    0x42a36d47, 0x20c1ef44, 0x97a28869, 0xb7f0ade2,
    0xcc3c0621, 0x2692ad53, 0xb61f5af5, 0xabd850e2,
    0xd06b42c8, 0xade8842a, 0xa2178c0f, 0xdf0ca559,
    0xc9f9dd79, 0x22bd62bf, 0x75929946, 0x48173a1d,
    0xd52f0a0b, 0xc29fb604, 0x774e7cbe, 0x8429fb50,
    0x256306e8, 0x743c8a9e, 0xab953401, 0xef530096,
    0x061cbd22, 0xadecf60b, 0x1807277f, 0x1d882838,
    0xd51bd925, 0x47b8370c, 0xb52b8be2, 0x7726a694,
    0x3cfb4cc7, 0x504ccc59, 0xcfb87a68, 0x977f4818,
    0xcd0651c1, 0x96c3500e, 0x6d5951b8, 0x6936f138,
    0x7dbacc94, 0x8dac8dad, 0x0bae4b3b, 0x96413be5,
    0xee429522, 0x1a13b62b, 0xb849b8c6, 0xcf8cc5ee,
    0x942a6dba, 0xc197513a, 0x14b212de, 0x8d7423d7,
    0x81557f4b, 0xbd6f6749, 0xd70661d3, 0x2869dd25,
    0x8f57916e, 0xa54945e2, 0x865b577c, 0xa4a01e1b,
    0xed883770, 0x0ef4cc1e, 0x2816a292, 0xa4257ace,
    0x1ed57c97, 0xd83b73bd, 0xb4aecbb7, 0x07512781,
    0x7ff4909c, 0xbb1211e3, 0x7b49f95d, 0x0cdeefaf,
    0x5036900b, 0x31187d6f, 0xd41c8382, 0x500a1164,
    0x62ef805a, 0xb536a3aa, 0x9172894b, 0x548566f8,
    0xcf027b46, 0x231d44ec, 0xf63319d6, 0x9ac41fb1,
    0x9d51405f, 0x90b14199, 0x4e7e673e, 0x5b07249f,
    0x91f0ddeb, 0x05ff219d, 0xb4b646c5, 0x2e250201,
    0x9b27d9cb, 0xbfd11f9e, 0xf94a0e27, 0xaf1079d6,
    0xa863d65e, 0x48225c82, 0x5176ea23, 0x6bd66da1,
    0x22d13d30, 0x28077a5c, 0x936c2521, 0x2932311a,
    0xdd317ff9, 0xc21af77a, 0x8a19f140, 0x9d45e06a,
    0x85626b76, 0x916ea84b, 0x0d19bbb4, 0x0f02e256,
    0xa1dfb6e7, 0xcd6435c4, 0x237358ed, 0x9a5e03fb,
    0xcfd92fee, 0x4669524f, 0x7746cc50, 0xd14e4db5,
    0x50e8b86e, 0x55d3cc24, 0xefd064fc, 0x2f333af2,
    0xf6a38bf6, 0xe65de7d4, 0x63a05b4b, 0x3708d044,
    0x872cacdc, 0xf1dfd46a, 0xcd0c35b5, 0x83f9110c,
    0xfc6c23a7, 0x1232b069, 0x8353037d, 0x1e86fcac,
    0x1411546a, 0x52df3956, 0x9e27432a, 0xafdee725,
    0xb94d1108, 0xe8c8544d, 0x745c08eb, 0x244740ce
#endif  /* defined __LIT */
};

uint32_t const DomainParam_NIST_P192[188] =
{
#if defined __LIT
    0x6d3390f2, 0xae4b69b6, 0xec8e9f24, 0x2812b01b,
    0x33ac01aa, 0xc3210209, 0xbc0ea877, 0x5733502a,
    0x3ffc4b3a, 0xab82f285, 0x32899604, 0x90695a7f,
    0x77141163, 0x61f40bdd, 0xbf015e2d, 0x57e794e0,
    0xbbb1f827, 0x52a87ac8, 0x63042279, 0x1ab1414f,
    0xd7872242, 0x3c54b566, 0x42e6dacb, 0x02402d34,
    0x198fc04c, 0xee053607, 0x309d6f29, 0xcf61bdd7,
    0xdea78202, 0x0be384d5, 0x8bc87ad0, 0x171b20c4,
    0xf5a6e884, 0x5b62ff8c, 0x545ea4db, 0x9dffae7e,
    0x632daa8e, 0x33cf6f8a, 0xbcb3f422, 0x2487049b,
    0xc12e4fba, 0xb09ff428, 0xbea06543, 0xf9066448,
    0x07288181, 0xed5c70a3, 0xeae1c9d3, 0x61f83b7b,
    0x7adc0460, 0x2b3236de, 0xd38ef835, 0x4d9cddd8,
    0x2230e7dc, 0x3cf1007a, 0x25e1588a, 0x835a3a4c,
    0x105d0c0f, 0xe92b43c1, 0x4fd8b157, 0xc340aa07,
    0x63767c20, 0xa8bea897, 0x589f10a3, 0x46c25fa5,
    0x1efefea2, 0x7683f730, 0x13462ce3, 0x0873c1f2,
    0x40a9f721, 0x1cf392b1, 0x1718a5a0, 0xaf336dba,
    0x4ff8f107, 0xa15afb90, 0x3eefb3f0, 0x02bd2004,
    0x98c46328, 0x87e3714d, 0x39e05ff2, 0x53af827f,
    0x34013e68, 0x3aae7658, 0x4c9ebd60, 0xd4b1e73b,
    0x304fb266, 0x979d9108, 0x68ada753, 0x766a1971,
    0x69a9f846, 0xc3ae7b63, 0x2e6dbcfc, 0x344f18f5,
    0x8d1fea46, 0xc0889586, 0x057f7014, 0x066c89b2,
    0xaa7815c3, 0x77045c75, 0xe7314643, 0xa2fabff5,
    0x59764c60, 0xde8aead8, 0xa3a4ecdd, 0x4f7b0b4a,
    0x21822017, 0x2f27b3f7, 0xbb1cef1b, 0x48540861,
    0xfacae250, 0xb6664e48, 0x5d7f0a23, 0xb795e148,
    0x28fbdd82, 0x0faf6641, 0x7056e227, 0xb8887057,
    0xe63eb69e, 0xec6d4170, 0x477c95a8, 0xce801616,
    0x80540164, 0xe09176ba, 0xd816678a, 0x5799bfa4,
    0xde0aa564, 0x8a0519d3, 0xaa3ce294, 0x857f0746,
    0x85924519, 0xb5e045fd, 0x0eb7140a, 0xf21984e1,
    0x79a1094c, 0xc0b0c054, 0xf8b3b927, 0x721b1fb1,
    0x4017ee2f, 0x2057b831, 0x5f7a1a67, 0x3be7ae64,
    0xe860127b, 0x76176161, 0x31cea423, 0x1ec83727,
    0x398da319, 0x8d06ec14, 0xba6c5186, 0xf51c28bd,
    0xba2c9364, 0x79b6ff02, 0xfb554b1b, 0x0e8fbe25,
    0x91c659ee, 0x8810c42b, 0x53aa098a, 0xa8f8bbe4,
    0xb3dca23a, 0xd9b9c39e, 0x6eec1933, 0x3b44f606,
    0x0391a63b, 0x9d633472, 0xd9f1fdec, 0xfcb0da26,
    0xdb064f04, 0xac2aeccf, 0xd8b94499, 0xa21c649c,
    0xb2b7038b, 0x4544aa97, 0xa933dc96, 0x553aa7f0,
    0x685e20af, 0x6c4d344e, 0xcd04d4d2, 0x71b2d442,
    0x5bf0a016, 0x84fb3653, 0x50db47ee, 0xdad1ef15,
    0xe4143f4b, 0xf56674da, 0xcb089bfd, 0x49b18b34,
    0xbbfa8123, 0x4900b508, 0xa6e98b44, 0x06698d1e
#else   /* defined __LIT */
    0xf290336d, 0xb6694bae, 0x249f8eec, 0x1bb01228, 
    0xaa01ac33, 0x090221c3, 0x77a80ebc, 0x2a503357, 
    0x3a4bfc3f, 0x85f282ab, 0x04968932, 0x7f5a6990, 
    0x63111477, 0xdd0bf461, 0x2d5e01bf, 0xe094e757, 
    0x27f8b1bb, 0xc87aa852, 0x79220463, 0x4f41b11a, 
    0x422287d7, 0x66b5543c, 0xcbdae642, 0x342d4002, 
    0x4cc08f19, 0x073605ee, 0x296f9d30, 0xd7bd61cf, 
    0x0282a7de, 0xd584e30b, 0xd07ac88b, 0xc4201b17, 
    0x84e8a6f5, 0x8cff625b, 0xdba45e54, 0x7eaeff9d, 
    0x8eaa2d63, 0x8a6fcf33, 0x22f4b3bc, 0x9b048724, 
    0xba4f2ec1, 0x28f49fb0, 0x4365a0be, 0x486406f9, 
    0x81812807, 0xa3705ced, 0xd3c9e1ea, 0x7b3bf861, 
    0x6004dc7a, 0xde36322b, 0x35f88ed3, 0xd8dd9c4d, 
    0xdce73022, 0x7a00f13c, 0x8a58e125, 0x4c3a5a83, 
    0x0f0c5d10, 0xc1432be9, 0x57b1d84f, 0x07aa40c3, 
    0x207c7663, 0x97a8bea8, 0xa3109f58, 0xa55fc246, 
    0xa2fefe1e, 0x30f78376, 0xe32c4613, 0xf2c17308, 
    0x21f7a940, 0xb192f31c, 0xa0a51817, 0xba6d33af, 
    0x07f1f84f, 0x90fb5aa1, 0xf0b3ef3e, 0x0420bd02, 
    0x2863c498, 0x4d71e387, 0xf25fe039, 0x7f82af53, 
    0x683e0134, 0x5876ae3a, 0x60bd9e4c, 0x3be7b1d4, 
    0x66b24f30, 0x08919d97, 0x53a7ad68, 0x71196a76, 
    0x46f8a969, 0x637baec3, 0xfcbc6d2e, 0xf5184f34, 
    0x46ea1f8d, 0x869588c0, 0x14707f05, 0xb2896c06, 
    0xc31578aa, 0x755c0477, 0x434631e7, 0xf5bffaa2, 
    0x604c7659, 0xd8ea8ade, 0xddeca4a3, 0x4a0b7b4f, 
    0x17208221, 0xf7b3272f, 0x1bef1cbb, 0x61085448, 
    0x50e2cafa, 0x484e66b6, 0x230a7f5d, 0x48e195b7, 
    0x82ddfb28, 0x4166af0f, 0x27e25670, 0x577088b8, 
    0x9eb63ee6, 0x70416dec, 0xa8957c47, 0x161680ce, 
    0x64015480, 0xba7691e0, 0x8a6716d8, 0xa4bf9957, 
    0x64a50ade, 0xd319058a, 0x94e23caa, 0x46077f85, 
    0x19459285, 0xfd45e0b5, 0x0a14b70e, 0xe18419f2, 
    0x4c09a179, 0x54c0b0c0, 0x27b9b3f8, 0xb11f1b72, 
    0x2fee1740, 0x31b85720, 0x671a7a5f, 0x64aee73b, 
    0x7b1260e8, 0x61611776, 0x23a4ce31, 0x2737c81e, 
    0x19a38d39, 0x14ec068d, 0x86516cba, 0xbd281cf5, 
    0x64932cba, 0x02ffb679, 0x1b4b55fb, 0x25be8f0e, 
    0xee59c691, 0x2bc41088, 0x8a09aa53, 0xe4bbf8a8, 
    0x3aa2dcb3, 0x9ec3b9d9, 0x3319ec6e, 0x06f6443b, 
    0x3ba69103, 0x7234639d, 0xecfdf1d9, 0x26dab0fc, 
    0x044f06db, 0xcfec2aac, 0x9944b9d8, 0x9c641ca2, 
    0x8b03b7b2, 0x97aa4445, 0x96dc33a9, 0xf0a73a55, 
    0xaf205e68, 0x4e344d6c, 0xd2d404cd, 0x42d4b271, 
    0x16a0f05b, 0x5336fb84, 0xee47db50, 0x15efd1da, 
    0x4b3f14e4, 0xda7466f5, 0xfd9b08cb, 0x348bb149, 
    0x2381fabb, 0x08b50049, 0x448be9a6, 0x1e8d6906
#endif  /* defined __LIT */
};

uint32_t const DomainParam_NIST_P384[104] =
{
#if defined __LIT
    0x61acf0ce, 0x37a9f047, 0x756f6aca, 0x7d5fc0a1,
    0x14685494, 0x3842308e, 0x7dbda327, 0x1ad84f88,
    0x88607320, 0xc53acb3a, 0xaddf6165, 0x6b439b82,
    0x18f77f06, 0xdf1d5adc, 0x2eafd709, 0xd393966d,
    0x7849a4b1, 0x71a600eb, 0x1d1c5361, 0x992b0d42,
    0x599f30cf, 0xa7089748, 0x94a6634c, 0x64ee22e3,
    0x377837b4, 0x8fb7910b, 0x3c2fbcbc, 0xcecc8ad3,
    0x15f94a1a, 0xcaf9b239, 0xdc52e090, 0x56fa0675,
    0x3e4db609, 0x0cc7c5a4, 0x792c4db5, 0xf7987499,
    0x3c69709c, 0xbc8f194c, 0xce923037, 0x1c28d156,
    0x435ce2dc, 0xfa30dc68, 0xa5d27ab7, 0x26778ed7,
    0x8227ca70, 0x5e34fb01, 0xabb0bcfc, 0xab12d45b,
    0x8f292a6c, 0x666d5b0c, 0x323b6ca7, 0xbd7a63bf,
    0x1e510495, 0x63cd898d, 0x866085a3, 0x4d1a9db3,
    0x88ff1488, 0x63f17eaf, 0x9a5dea66, 0x6f7171ad,
    0x96e29ec5, 0x1f649263, 0x15ce6f4c, 0xf8eb501a,
    0xc88c45d6, 0x9518d7ea, 0x21dcba32, 0xe6f0af86,
    0x50231afd, 0x60120ab1, 0x8c0ce0b3, 0xb93ff854,
    0x55173062, 0xd75baa62, 0x45868469, 0x1aeaa77f,
    0xe639c12d, 0x3ed1996c, 0x455ae9c1, 0xfed18024,
    0x5ea4f08f, 0xdef80cb5, 0xdf9e3a88, 0x08344a4b,
    0x63729e29, 0x371e393e, 0x8b78123e, 0xeb5bd0fa,
    0x16791c94, 0xe3c6f145, 0xaf734ec5, 0x6dc16c82,
    0x11251681, 0xf8e2f7dd, 0x461df943, 0x7d54d9ea,
    0xce9cb1d5, 0x48c7e974, 0xdfa6c293, 0x6d68a3e6,
    0xc2dc036a, 0x8b5cd064, 0x63d6ab38, 0x4372b328
#else   /* defined __LIT */
    0xcef0ac61, 0x47f0a937, 0xca6a6f75, 0xa1c05f7d,
    0x94546814, 0x8e304238, 0x27a3bd7d, 0x884fd81a,
    0x20736088, 0x3acb3ac5, 0x6561dfad, 0x829b436b,
    0x067ff718, 0xdc5a1ddf, 0x09d7af2e, 0x6d9693d3,
    0xb1a44978, 0xeb00a671, 0x61531c1d, 0x420d2b99,
    0xcf309f59, 0x489708a7, 0x4c63a694, 0xe322ee64,
    0xb4377837, 0x0b91b78f, 0xbcbc2f3c, 0xd38accce,
    0x1a4af915, 0x39b2f9ca, 0x90e052dc, 0x7506fa56,
    0x09b64d3e, 0xa4c5c70c, 0xb54d2c79, 0x997498f7,
    0x9c70693c, 0x4c198fbc, 0x373092ce, 0x56d1281c,
    0xdce25c43, 0x68dc30fa, 0xb77ad2a5, 0xd78e7726,
    0x70ca2782, 0x01fb345e, 0xfcbcb0ab, 0x5bd412ab,
    0x6c2a298f, 0x0c5b6d66, 0xa76c3b32, 0xbf637abd,
    0x9504511e, 0x8d89cd63, 0xa3856086, 0xb39d1a4d,
    0x8814ff88, 0xaf7ef163, 0x66ea5d9a, 0xad71716f,
    0xc59ee296, 0x6392641f, 0x4c6fce15, 0x1a50ebf8,
    0xd6458cc8, 0xead71895, 0x32badc21, 0x86aff0e6,
    0xfd1a2350, 0xb10a1260, 0xb3e00c8c, 0x54f83fb9,
    0x62301755, 0x62aa5bd7, 0x69848645, 0x7fa7ea1a,
    0x2dc139e6, 0x6c99d13e, 0xc1e95a45, 0x2480d1fe,
    0x8ff0a45e, 0xb50cf8de, 0x883a9edf, 0x4b4a3408,
    0x299e7263, 0x3e391e37, 0x3e12788b, 0xfad05beb,
    0x941c7916, 0x45f1c6e3, 0xc54e73af, 0x826cc16d,
    0x81162511, 0xddf7e2f8, 0x43f91d46, 0xead9547d,
    0xd5b19cce, 0x74e9c748, 0x93c2a6df, 0xe6a3686d,
    0x6a03dcc2, 0x64d05c8b, 0x38abd663, 0x28b37243
#endif  /* defined __LIT */
};

uint32_t const DomainParam_Brainpool_512r1[136] =
{
#if defined __LIT
    0xb5842c10, 0x65fe8c4e, 0x7cab21b0, 0x7a8f20db,
    0x184573b6, 0x208d5b04, 0xc4afbfda, 0x7dbe0414,
    0x7377a035, 0xf4515323, 0xc9f5b9aa, 0xce67d115,
    0x98edc492, 0xb0fe899e, 0x954a0106, 0xd43aa662,
    0xd5309382, 0x26fe9d15, 0x3ed5f257, 0x994a78fd,
    0xbf2cd26f, 0x63ce1841, 0xa4cc96b1, 0x995c0e8c,
    0x793d5cf5, 0xbbe0fde6, 0x6d2f788f, 0x280b3846,
    0xdea57140, 0xd7d59ef1, 0xc7717978, 0xac864539,
    0xf41a4ebd, 0x5bcab9f9, 0x20a2af92, 0x01a27602,
    0x4afb2b4f, 0xb275f28d, 0x2fe0f140, 0x95e27329,
    0xdda1ede6, 0xc4854d44, 0x83871223, 0x3d55b94c,
    0x577b6a42, 0x8a3eefe8, 0x12ef453a, 0x468bf846,
    0x7bd0bd7d, 0x6a2ff2cf, 0xc7b2e032, 0x49c377fe,
    0x6db8706b, 0x79f4e6df, 0x8f2579f7, 0xacffe87c,
    0xaa870763, 0xaab560d8, 0x039525a1, 0x852454b9,
    0xa92139c8, 0xdf681994, 0xa606bbf2, 0x9d84829c,
    0x6cd22d11, 0x0fa6530a, 0x2f95960a, 0xaa35410d,
    0xf9a58f42, 0x8aad86f3, 0x76e4d19a, 0x5b910f78,
    0x02c7e29b, 0xc07b5a44, 0xfdc9415f, 0x3e3b0dac,
    0xd68d0204, 0xad494480, 0xb01f1a0b, 0xedf8b52a,
    0x4cad32a8, 0x41037234, 0x4ebeccdc, 0x8218d934,
    0x76909422, 0xbde33a57, 0x8001010e, 0x21c87ffe,
    0xf56d1fbb, 0x477442c8, 0x2ada83b0, 0x807c88c7,
    0x6febb8ce, 0x5dcd42fc, 0xc5860928, 0x45eb9b91,
    0x34c02bc0, 0x74e60793, 0xc3a41271, 0x3e86565f,
    0x32d7ef42, 0x74cfc3cc, 0xf7f210ad, 0x263b508a,
    0xe2bc996d, 0xfad9f44a, 0xba5171f2, 0x4d92fcf2,
    0xeda9ba85, 0x649cad7e, 0x2c395cc8, 0x8ca602f1,
    0xaab187f8, 0xe19cba64, 0x8d8b5812, 0xb81867a0,
    0x3c070edc, 0xef3db8b3, 0x8b682801, 0x128e8d3e,
    0x6c897311, 0xa347c97b, 0xce378ef4, 0x62c9f99f,
    0x4852fb0b, 0xcc8429da, 0x8a4c3881, 0x7d239970,
    0x5b7551e5, 0x3268f59f, 0xcd04da54, 0x495535ac,
    0xfe3f4b39, 0x343827af, 0x80bf3b3d, 0xb05c7a2e
#else   /* defined __LIT */
    0x102c84b5, 0x4e8cfe65, 0xb021ab7c, 0xdb208f7a,
    0xb6734518, 0x045b8d20, 0xdabfafc4, 0x1404be7d,
    0x35a07773, 0x235351f4, 0xaab9f5c9, 0x15d167ce,
    0x92c4ed98, 0x9e89feb0, 0x06014a95, 0x62a63ad4,
    0x829330d5, 0x159dfe26, 0x57f2d53e, 0xfd784a99,
    0x6fd22cbf, 0x4118ce63, 0xb196cca4, 0x8c0e5c99,
    0xf55c3d79, 0xe6fde0bb, 0x8f782f6d, 0x46380b28,
    0x4071a5de, 0xf19ed5d7, 0x787971c7, 0x394586ac,
    0xbd4e1af4, 0xf9b9ca5b, 0x92afa220, 0x0276a201,
    0x4f2bfb4a, 0x8df275b2, 0x40f1e02f, 0x2973e295,
    0xe6eda1dd, 0x444d85c4, 0x23128783, 0x4cb9553d,
    0x426a7b57, 0xe8ef3e8a, 0x3a45ef12, 0x46f88b46,
    0x7dbdd07b, 0xcff22f6a, 0x32e0b2c7, 0xfe77c349,
    0x6b70b86d, 0xdfe6f479, 0xf779258f, 0x7ce8ffac,
    0x630787aa, 0xd860b5aa, 0xa1259503, 0xb9542485,
    0xc83921a9, 0x941968df, 0xf2bb06a6, 0x9c82849d,
    0x112dd26c, 0x0a53a60f, 0x0a96952f, 0x0d4135aa,
    0x428fa5f9, 0xf386ad8a, 0x9ad1e476, 0x780f915b,
    0x9be2c702, 0x445a7bc0, 0x5f41c9fd, 0xac0d3b3e,
    0x04028dd6, 0x804449ad, 0x0b1a1fb0, 0x2ab5f8ed,
    0xa832ad4c, 0x34720341, 0xdcccbe4e, 0x34d91882,
    0x22949076, 0x573ae3bd, 0x0e010180, 0xfe7fc821,
    0xbb1f6df5, 0xc8427447, 0xb083da2a, 0xc7887c80,
    0xceb8eb6f, 0xfc42cd5d, 0x280986c5, 0x919beb45,
    0xc02bc034, 0x9307e674, 0x7112a4c3, 0x5f56863e,
    0x42efd732, 0xccc3cf74, 0xad10f2f7, 0x8a503b26,
    0x6d99bce2, 0x4af4d9fa, 0xf27151ba, 0xf2fc924d,
    0x85baa9ed, 0x7ead9c64, 0xc85c392c, 0xf102a68c,
    0xf887b1aa, 0x64ba9ce1, 0x12588b8d, 0xa06718b8,
    0xdc0e073c, 0xb3b83def, 0x0128688b, 0x3e8d8e12,
    0x1173896c, 0x7bc947a3, 0xf48e37ce, 0x9ff9c962,
    0x0bfb5248, 0xda2984cc, 0x81384c8a, 0x7099237d,
    0xe551755b, 0x9ff56832, 0x54da04cd, 0xac355549,
    0x394b3ffe, 0xaf273834, 0x3d3bbf80, 0x2e7a5cb0
#endif  /* defined __LIT */
};

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/

