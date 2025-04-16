/***********************************************************************************************************************
 * Copyright (c) 2016 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_elc_rx_platform.h
 * Version      : 4.01
 * Description  : Functions for using Event Link Controller module
 ************************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           01.07.2016 1.0     Initial Release
 *           12.09.2016 1.10    Added support for RX65N
 *           16.06.2017 1.20    Added support for RX65N(2MB), RX130(512KB)
 *           10.06.2020 2.00    Added support for RX23W
 *           10.12.2020 2.01    Added support for RX140
 *           31.05.2023 3.00    Added support for RX23E-B
 *           31.07.2024 4.00    Added support for RX260, RX261
 *           20.03.2025 4.01    Changed the disclaimer in program sources.
***********************************************************************************************************************/
#ifndef ELC_RX_PLATFORM_H
    #define ELC_RX_PLATFORM_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
    #include "platform.h"
    #if defined(BSP_MCU_RX113)
        #include "./targets/rx113/r_elc_rx113_private.h"  /* RX113 */
    #endif
    #if defined(BSP_MCU_RX130)
        #include "./targets/rx130/r_elc_rx130_private.h"  /* RX130 */
    #endif
    #if defined(BSP_MCU_RX140)
        #include "./targets/rx140/r_elc_rx140_private.h"  /* RX140 */
    #endif
    #if defined(BSP_MCU_RX230)
        #include "./targets/rx230/r_elc_rx230_private.h"  /* RX230 */
    #endif
    #if defined(BSP_MCU_RX231)
        #include "./targets/rx231/r_elc_rx231_private.h"  /* RX231 */
    #endif
    #if defined(BSP_MCU_RX23W)
        #include "./targets/rx23w/r_elc_rx23w_private.h"  /* RX23W */
    #endif
    #if defined(BSP_MCU_RX23E_B)
        #include "./targets/rx23e-b/r_elc_rx23e-b_private.h"  /* RX23E-B */
    #endif
    #if defined(BSP_MCU_RX260)
        #include "./targets/rx260/r_elc_rx260_private.h"  /* RX260 */
    #endif
    #if defined(BSP_MCU_RX261)
        #include "./targets/rx261/r_elc_rx261_private.h"  /* RX261 */
    #endif
    #if defined(BSP_MCU_RX65N)
        #include "./targets/rx65n/r_elc_rx65n_private.h"  /* RX65N */
    #endif

#endif /* ELC_RX_PLATFORM_H */
/***********************************************************************************************************************
 * End of File
 ***********************************************************************************************************************/
