/**********************************************************************************************************************
* Copyright (c) 2016 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * File Name    : r_lpt_rx_platform.h
 * Version      : 5.01
 * Description  : Functions for using Low Power Timer
 **********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 01.03.2016 1.00    First Release
 *         : 01.07.2016 1.10    Added support for RX130,RX230,RX231
 *         : 10.06.2020 2.00    Added support for RX23W
 *         : 25.09.2020 2.01    Added support for RX140
 *         : 31.05.2023 4.00    Added support for RX23E-B
 *         : 31.07.2024 5.00    Added support for RX261,RX260
 *         : 20.03.2025 5.01    Changed the disclaimer in program sources.
 *********************************************************************************************************************/

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
/* Include specifics for chosen MCU.  */
#if defined(BSP_MCU_RX113)
    #include "./targets/rx113/r_lpt_rx113_private.h"
#elif defined(BSP_MCU_RX130)
    #include "./targets/rx130/r_lpt_rx130_private.h"
#elif defined(BSP_MCU_RX140)
    #include "./targets/rx140/r_lpt_rx140_private.h"
#elif defined(BSP_MCU_RX230)
    #include "./targets/rx230/r_lpt_rx230_private.h"
#elif defined(BSP_MCU_RX231)
    #include "./targets/rx231/r_lpt_rx231_private.h"
#elif defined(BSP_MCU_RX23W)
    #include "./targets/rx23w/r_lpt_rx23w_private.h"
#elif defined(BSP_MCU_RX23E_B)
    #include "./targets/rx23e-b/r_lpt_rx23e-b_private.h"
#elif defined(BSP_MCU_RX260)
    #include "./targets/rx260/r_lpt_rx260_private.h"
#elif defined(BSP_MCU_RX261)
    #include "./targets/rx261/r_lpt_rx261_private.h"
#else
    #error "This MCU is not supported by the current r_lpt_rx module."
#endif

/*******************************************************************************
  Macro definitions
*******************************************************************************/
#ifndef LPT_PLATFORM_H
#define LPT_PLATFORM_H

#endif /* LPT_PLATFORM_H */
/**********************************************************************************************************************
 * End of File
 *********************************************************************************************************************/
