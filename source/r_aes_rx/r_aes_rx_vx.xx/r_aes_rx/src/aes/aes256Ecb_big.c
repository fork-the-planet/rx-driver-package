/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         aes256Ecb_big.c
 * @brief        Define option for API function
 **********************************************************************************************************************/
/*
 There 3 options to build AES library
 - the length of key: KEY_LENGTH    128/192/256
 - operation mode:    ECB_MODE/CBC_MODE
 - code size :        __COMPILE_EMPHASIS_SPEED__/__COMPILE_EMPHASIS_SIZE__
 */
#include "r_aes.h"

#if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)
    /* RL78 not support */
#else
    #include "r_aes_config.h"

    #if ( AES_CFG_BUILD_OPTION == 0 )

        #if defined(__SUPPORT_AES256__)

            #define KEY_LENGTH 256
            #define ECB_MODE
            #define __COMPILE_EMPHASIS_SPEED__

            #include "r_aesEcb.h"

        #endif /* defined__SUPPORT_AES256__ */

    #endif
#endif /* defined__RL78__ || defined__ICCRL78__ || defined__CCRL__ */
