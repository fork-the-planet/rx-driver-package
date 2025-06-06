/***********************************************************************************************************************
* Copyright (c) 2022 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_lpc_rx26t_if.h
 * Description  : Definitions used by the r_lpc_rx26t.c module.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 15.08.2022 1.00    First Release
 *         : 15.03.2025 2.51    Updated disclaimer.
 ***********************************************************************************************************************/

#ifndef R_LPC_RX26T_IF_H
    #define R_LPC_RX26T_IF_H

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
/* Invalid function */
#define LPC_INVALID_OPERATING_MODE

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/
typedef enum lpc_low_power_mode
{
    LPC_LP_SLEEP,
    LPC_LP_ALL_MODULE_STOP,
    LPC_LP_SW_STANDBY,
    LPC_LP_INVALID_MODE
}lpc_low_power_mode_t;

/* LPC Sleep Mode Return Clock Switching Sources*/
typedef enum lpc_clock_switch
{
    LPC_HOCO = 0x01,
    LPC_MAIN_OSC = 0x02,
}lpc_clock_switch_t;

/***********************************************************************************************************************
 Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
#endif /* R_LPC_RX26T_IF_H */
