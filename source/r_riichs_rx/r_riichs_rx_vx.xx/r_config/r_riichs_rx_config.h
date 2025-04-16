/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_riichs_rx_config.h
 * Description  : Configures the RIICHS drivers
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 30.06.2021 1.00     First Release
 *         : 15.03.2025 1.21     Updated disclaimer
 **********************************************************************************************************************/
/* Guards against multiple inclusion */
#ifndef RIICHS_CONFIG_H
    #define RIICHS_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/
/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking; 0 compiles out parameter checking */
    #define RIICHS_CFG_PARAM_CHECKING_ENABLE  (1)

/* SPECIFY CHANNELS TO INCLUDE SOFTWARE SUPPORT FOR 1=included, 0=not */
/* mcu supported channels */
/*  RX671: ch0 */

    #define RIICHS_CFG_CH0_INCLUDED           (1)

/* Setting to */
/* 1: includes riichs port setting processing */
/* 0: compiles out riichs port setting processing */
    #define RIICHS_CFG_PORT_SET_PROCESSING    (1)

#endif /* RIICHS_CONFIG_H */

