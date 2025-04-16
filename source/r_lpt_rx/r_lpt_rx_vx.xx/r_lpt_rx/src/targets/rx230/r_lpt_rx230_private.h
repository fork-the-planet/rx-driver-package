/**********************************************************************************************************************
* Copyright (c) 2016 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_lpt_rx230_private.h
 * Version      : 5.01
 * Description  : Functions for using even link controller
 **********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 01.07.2016 1.00    First Release
 *         : 31.03.2021 3.00    Added error code if selected LOCO clock
 *         : 20.03.2025 5.01    Changed the disclaimer in program sources.
 *********************************************************************************************************************/

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_lpt_rx_config.h"

/*******************************************************************************
  Macro definitions
*******************************************************************************/
#ifndef LPT_RX230_PRIVATE_H
#define LPT_RX230_PRIVATE_H

#define LPT_CONV_US          (1000 * 1000)    /* Value converted to microseconds */
#define LPT_CALCSCALE_OFFSET (1000)           /* OFFSET value deal with clock source change to MHz */

/* Minimum cycle */
#define LPT_MIN_PERIOD      (0x00000001)    /* Minimum cycle */
/* Maximum cycle */
#define LPT_MAX_PERIOD      (0x0000FFFF)    /* Maximum cycle (shall not overflow with uint16_t) */

/* Common register setting */
#define LPT_LPTCR1_INIT     (0x01)           /* Initial value of LPTCR1 */
#define LPT_LPTCR2_INIT     (0x01)           /* Initial value of LPTCR2 */
#define LPT_LPTPRD_INIT     (0xFFFF)         /* Initial value of LPTPRD */
#define LPT_LPCMR0_INIT     (0xFFFF)         /* Initial value of LPCMR0 */
#define LPT_LPWUCR_INIT     (0x0000)         /* Initial value of LPWUCR */

/* Low-Power Timer Clock Division Ratio Select Data (do NOT change values) */
#define LPT_DIVISION_RATIO_2    (0x01U)
#define LPT_DIVISION_RATIO_4    (0x02U)
#define LPT_DIVISION_RATIO_8    (0x03U)
#define LPT_DIVISION_RATIO_16   (0x04U)
#define LPT_DIVISION_RATIO_32   (0x05U)

/*------------------------------------------------------------------------------
  Parameter check of Configuration Options
------------------------------------------------------------------------------*/
#ifdef BSP_CFG_LPT_CLOCK_SOURCE
    #define LPT_CLOCK_SOURCE    (BSP_CFG_LPT_CLOCK_SOURCE)
#else
    #define LPT_CLOCK_SOURCE    (LPT_CFG_LPT_CLOCK_SOURCE)
#endif

#if   (LPT_CLOCK_SOURCE == 0)
    #define LPT_LPTSRCCLK_HZ    (BSP_SUB_CLOCK_HZ)
    #define LPT_LPTSRCCLK_CYC   (31)                    /* 1cycle/Sub-clock(32.768kHz) */
#elif (LPT_CLOCK_SOURCE == 1)
    #define LPT_LPTSRCCLK_HZ    (15000)                 /* IWDTCLK frequency */
    #define LPT_LPTSRCCLK_CYC   (79)                    /* 1cycle/IWDTCLK(min:12.75kHz max:17.25kHz) */
#elif (LPT_CLOCK_SOURCE == 3)
    #error "ERROR - LPT_CLOCK_SOURCE - Unsupported LOCO lpt clock source chosen in r_lpt_rx230_private.h"
#else
    #error "ERROR - LPT_CFG_LPT_CLOCK_SOURCE - Unknown lpt clock source chosen in r_lpt_rx230_private.h"
#endif

#if   (2000000 < LPT_LPTSRCCLK_HZ)
    /* lpt_regval_calc() calculation result overflow when lpt clock source 2MHz greater. */
    #error "ERROR - LPT_LPTSRCCLK_HZ - 2MHz < lpt clock frequency in r_lpt_rx230_private.h"
#endif


#endif /* LPT_RX230_PRIVATE_H */

/**********************************************************************************************************************
 * End of File
 *********************************************************************************************************************/
