/***********************************************************************************************************************
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name     : r_wdt_rx_config.h
* Description   : Configures the WDT drivers
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           28.04.2016 1.00    First Release
*           15.03.2025 3.11    Updated disclaimer.
***********************************************************************************************************************/
#ifndef WDT_RX_CONFIG_H
#define WDT_RX_CONFIG_H

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING 
   Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting (default)
   Setting to 1 includes parameter checking; 0 compiles out parameter checking */
#define WDT_CFG_PARAM_CHECKING_ENABLE   (BSP_CFG_PARAM_CHECKING_ENABLE)


/* NOTE:
 * To have the WDT start automatically at powerup instead of using an Open() call,
 * change the BSP_CFG_OFS0_REG_VALUE mask to the desired settings in r_bsp_config.h.
 */


#endif /* WDT_RX_CONFIG_H */
