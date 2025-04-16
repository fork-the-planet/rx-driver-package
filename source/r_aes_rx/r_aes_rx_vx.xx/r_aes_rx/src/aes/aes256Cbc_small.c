/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         aes256Cbc_small.c
 * @brief        Define option for API function
 **********************************************************************************************************************/
/*
 There is 1 option to build this AES library
 - code size :        __COMPILE_EMPHASIS_SPEED__/__COMPILE_EMPHASIS_SIZE__
 */

#if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)
    #define __COMPILE_EMPHASIS_SIZE__

    #include "aes256.h"
#else
    #include "r_aes_config.h"

    #if ( AES_CFG_BUILD_OPTION == 1 )

        #define __COMPILE_EMPHASIS_SIZE__

        #include "aes256.h"

    #endif
#endif /* defined__RL78__ || defined__ICCRL78__ || defined__CCRL__ */
