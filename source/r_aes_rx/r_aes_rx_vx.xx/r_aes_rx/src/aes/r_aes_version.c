/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         r_aes_version.c
 * @brief        Middleware version information definition
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_stdint.h"
#include "r_mw_version.h"
#include "platform.h"
/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#define __COMPLIER_VER_UNDEFINED__ (0xFFFFFFFF)
/* version define */
#define __AES_VERSION__ "1.08"

#if defined(__GNUC__)
    #define __RENESAS_VERSION__  (__GNUC__* 0x1000000 + __GNUC_MINOR__* 0x10000 + __GNUC_PATCHLEVEL__)
#elif defined(__ICCRX__)
    #define __RENESAS_VERSION__  __VER__
#endif

#if (defined (__RX) && defined (__BIG))
    #define __TARGET_CPU__ "RX BIG endian"
    #define __COMPILER_VER__ (__RENESAS_VERSION__)
#elif (defined (__RX) && defined (__LIT))
    #define __TARGET_CPU__ "RX LITTLE endian"
    #define __COMPILER_VER__ (__RENESAS_VERSION__)
#elif (defined (_SH4A) && defined(_BIG))
    #define __TARGET_CPU__ "SH-4A BIG endian"
    #define __COMPILER_VER__ (__RENESAS_VERSION__)
#elif (defined (_SH4A) && defined(_LIT))
    #define __TARGET_CPU__ "SH-4A LITTLE endian"
    #define __COMPILER_VER__ (__RENESAS_VERSION__)
#elif defined (_SH2AFPU)
    #define __TARGET_CPU__ "SH2A-FPU"
    #define __COMPILER_VER__ (__RENESAS_VERSION__)
#elif defined (_SH2A)
    #define __TARGET_CPU__ "SH-2A"
    #define __COMPILER_VER__ (__RENESAS_VERSION__)
#elif (defined (_SH2) && defined(_BIG))
    #define __TARGET_CPU__ "SH-2 BIG endian"
    #define __COMPILER_VER__ (__RENESAS_VERSION__)
#elif (defined (_SH2) && defined(_LIT))
    #define __TARGET_CPU__ "SH-2 LITTLE endian"
    #define __COMPILER_VER__ (__RENESAS_VERSION__)
#elif defined (__v850) && (__v850e2v3)
    #define __TARGET_CPU__ "V850E2V3"
    #define __COMPILER_VER__   (__COMPLIER_VER_UNDEFINED__)
#elif defined (__v850) && (__v850e2)
    #define __TARGET_CPU__ "V850E2"
    #define __COMPILER_VER__   (__COMPLIER_VER_UNDEFINED__)
#elif defined (__v850) && (__v850e)
    #define __TARGET_CPU__ "V850E"
    #define __COMPILER_VER__   (__COMPLIER_VER_UNDEFINED__)
#elif defined (__v850)
    #define __TARGET_CPU__ "V850"
    #define __COMPILER_VER__   (__COMPLIER_VER_UNDEFINED__)
#elif defined (__K0__)
    #define __TARGET_CPU__ "78K0"
    #define __COMPILER_VER__   (__COMPLIER_VER_UNDEFINED__)
#elif defined (__CCRL__)
    #if defined (__RL78_SMALL__)
        #define __MEMORY_MODEL__ "SMALL"
    #elif defined (__RL78_MEDIUM__)
        #define __MEMORY_MODEL__ "MEDIUM"
    #else
        #error "Undefined memory model."
    #endif /* defined__RL78_SMALL__ */
    #if defined (__RL78_S1__)
        #define __CORE_NAME__ "S1" /* RL78/G10 */
    #elif defined (__RL78_S2__)
        #define __CORE_NAME__ "S2" /* RL78/G12 RL78/G13 */
    #elif defined (__RL78_S3__)
        #define __CORE_NAME__ "S3" /* RL78/G14 */
    #else
        #error "Undefined CPU Core."
    #endif /* defined__RL78_S1__ */
    #define __TARGET_CPU__ "RL78 (CCRL, "__CORE_NAME__", "__MEMORY_MODEL__")"
    #define __COMPILER_VER__   (__RENESAS_VERSION__)
#elif defined (__K0R__)
    #if defined (__RL78__)
        #if defined (__K0R_SMALL__)
            #define __MEMORY_MODEL__ "SMALL"
        #elif defined (__K0R_MEDIUM__)
            #define __MEMORY_MODEL__ "MEDIUM"
        #elif defined (__K0R_LARGE__)
            #define __MEMORY_MODEL__ "LARGE"
        #else
            #error "Undefined memory model."
        #endif /* defined__K0R_SMALL__ */
        #if defined (__RL78_1__)
            #define __CORE_NAME__ "S2" /* RL78/G12 RL78/G13 */
        #elif defined (__RL78_2__)
            #define __CORE_NAME__ "S3" /* RL78/G14 */
        #elif defined (__RL78_3__)
            #define __CORE_NAME__ "S1" /* RL78/G10 */
        #else
            #error "Undefined CPU Core."
        #endif /* defined__RL78_1__ */
        #define __TARGET_CPU__ "RL78 ("__CORE_NAME__", "__MEMORY_MODEL__")"
    #else
        #define __TARGET_CPU__ "78K0R"
    #endif /* defined__RL78__ */
    #define __COMPILER_VER__   (__COMPLIER_VER_UNDEFINED__)
#elif defined (__ICCRL78__)
    #if __CORE__==__RL78_0__
        #define __CORE_NAME__ "S1" /* RL78/G10 */
    #elif __CORE__==__RL78_1__
        #define __CORE_NAME__ "S2" /* RL78/G12 RL78/G13 */
    #elif __CORE__==__RL78_2__
        #define __CORE_NAME__ "S3" /* RL78/G14 */
    #else
        #error "Undefined CPU Core."
    #endif /* __CORE__==__RL78_0__ */
    #if __CODE_MODEL__==__CODE_MODEL_NEAR__
        #define __CODE_MODEL_NAME__ "code_model=near"
    #else
        #define __CODE_MODEL_NAME__ "code_model=far"
    #endif /* __CODE_MODEL__==__CODE_MODEL_NEAR__ */
    #if __DATA_MODEL__==__DATA_MODEL_NEAR__
        #define __DATA_MODEL_NAME__ "data_model=near"
    #else
        #define __DATA_MODEL_NAME__ "data_model=far"
    #endif /* __DATA_MODEL__==__DATA_MODEL_NEAR__ */
    #define __TARGET_CPU__ "RL78 (IAR, "__CORE_NAME__", "__CODE_MODEL_NAME__", "__DATA_MODEL_NAME__")"
    #define __COMPILER_VER__   (__VER__)
#elif defined (M16C) && defined(__R8C__)
    #define __TARGET_CPU__ "R8C"
    #ifdef __RENESAS_VERSION__
        #define __COMPILER_VER__ (__RENESAS_VERSION__)
    #else
        #define __COMPILER_VER__ (__COMPLIER_VER_UNDEFINED__)
    #endif /* __RENESAS_VERSION__ */
#elif defined (M16C) && !defined(__R8C__)
    #define __TARGET_CPU__ "M16C"
    #ifdef __RENESAS_VERSION__
        #define __COMPILER_VER__ (__RENESAS_VERSION__)
    #else
        #define __COMPILER_VER__ (__COMPLIER_VER_UNDEFINED__)
    #endif /* __RENESAS_VERSION__ */
#elif defined (M32C80)
    #define __TARGET_CPU__ "M32C/80"
    #define __COMPILER_VER__   (__COMPLIER_VER_UNDEFINED__)
#elif defined (R32C100)
    #define __TARGET_CPU__ "R32C/100"
    #define __COMPILER_VER__   (__COMPLIER_VER_UNDEFINED__)
#elif defined (__H8__) && defined(__2600A__)
    #define __TARGET_CPU__ "H8S/2600 Advanced mode"
    #define __COMPILER_VER__ (__RENESAS_VERSION__)
#elif defined (__arm__)
    #if defined (__TARGET_CPU_CORTEX_A9)
        #if defined (__BIG_ENDIAN)
            #define __TARGET_CPU__ "Cortex-A9 BIG endian"
        #else
            #define __TARGET_CPU__ "Cortex-A9 LITTLE endian"
        #endif /* __BIG_ENDIAN */
    #else
        #error "Undefined arm CPU."
    #endif /* __TARGET_CPU_CORTEX_A9 */
    #define __COMPILER_VER__ (__ARMCC_VERSION)
#else
    #error "None-support combination of CPU and endian"
#endif /* defined __RXV2 && defined __BIG */

/***********************************************************************************************************************
 Global variables
 **********************************************************************************************************************/
const mw_version_t far R_aes_version =
{
__COMPILER_VER__, "AES Library version "__AES_VERSION__" for "__TARGET_CPU__".("__DATE__", "__TIME__")\n" };
