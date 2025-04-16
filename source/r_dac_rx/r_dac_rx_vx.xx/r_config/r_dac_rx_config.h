/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name     : r_dac_rx_config.h
* Description   : Configures the DAC driver
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           31.03.2014 2.00    New API
*           28.09.2018 3.20    Updated follow GSCE coding rules 5.0
*           15.03.2025 5.31    Updated disclaimer.
***********************************************************************************************************************/
#ifndef DAC_CONFIG_H
#define DAC_CONFIG_H

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking; 0 compiles out parameter checking */
#define DAC_CFG_PARAM_CHECKING_ENABLE   (BSP_CFG_PARAM_CHECKING_ENABLE)


#endif /* DAC_CONFIG_H */
