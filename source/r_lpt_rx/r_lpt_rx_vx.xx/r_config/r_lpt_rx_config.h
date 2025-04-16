/***********************************************************************************************************************
* Copyright (c) 2016 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_lpt_rx_config.h
* Version      : 5.01
* Description  : Functions for using even link controller
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.03.2016 1.00    First Release
*         : 25.09.2020 2.01    Added support for RX140
*                              Added PWM output
*         : 31.05.2023 4.00    Added support for RX23E-B
*                              Change parameter check definition.
*         : 20.03.2025 5.01    Changed the disclaimer in program sources.
***********************************************************************************************************************/
#ifndef LPT_CONFIG_H
#define LPT_CONFIG_H

/*******************************************************************************
  Configuration Options
*******************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking; 0 compiles out parameter checking */
#define LPT_CFG_PARAM_CHECKING_ENABLE   (BSP_CFG_PARAM_CHECKING_ENABLE)

/* LPT (Low Power Timer) Clock source select (LPTCR1.LPCNTCKSEL)
   0 = Sub-clock oscillator
   1 = IWDT-dedicated on-chip oscillator
   2 = Low-speed on-chip oscillator
*/ 
#ifndef BSP_CFG_LPT_CLOCK_SOURCE
#define LPT_CFG_LPT_CLOCK_SOURCE    (0)
#endif

#endif /* LPT_CONFIG_H */
/***********************************************************************************************************************
 * End of File
 ***********************************************************************************************************************/
