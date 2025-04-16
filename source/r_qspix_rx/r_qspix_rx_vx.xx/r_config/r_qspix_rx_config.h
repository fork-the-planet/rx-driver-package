/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 31.03.2021 1.00     First Release
*              : 15.03.2025 1.42     Updated disclaimer
*******************************************************************************/
/*******************************************************************************
* File Name     : r_qspix_rx_config.h
* Description   : Configures the QSPIX drivers
*******************************************************************************/
#ifndef R_QSPIX_RX_CONFIG_H
#define R_QSPIX_RX_CONFIG_H

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/

/*******************************************************************************
Configuration Options
*******************************************************************************/
/* This setting selects whether to include parameter checking of arguments
   of API for QSPIX FIT module or not.
    When set to "1", API includes parameter checking.
    When set to "0", API doesn't include it.
   And, when the definition of "BSP_CFG_PARAM_CHECKING_ENABLE" is "0", API doesn't include it too.
*/
#define QSPIX_CFG_PARAM_CHECKING_ENABLE (BSP_CFG_PARAM_CHECKING_ENABLE)

/* Enable the QSPIX channels to use in this build. (0) = not used. (1) = used. */
#define QSPIX_CFG_USE_CH0  (1)

/*
* Enable or Disable ROM access error interrupt
*/
#define QSPIX_CFG_ERI_INCLUDED    (1)      /* 1=included, 0=not */

/* Set interrupt priority levels for each channel present.
 * Priority is shared by all interrupt sources in a channel.
 * Values must be in the range 0 (interrupt disabled) to 15 (highest)*/
#define QSPIX_CFG_ERI_IR_PRIORITY (3)

#endif /* R_QSPIX_RX_CONFIG_H */
