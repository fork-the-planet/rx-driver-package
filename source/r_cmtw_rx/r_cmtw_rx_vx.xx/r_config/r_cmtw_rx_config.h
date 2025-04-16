/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_cmtw_rx_config.h
* Description  : Configures the r_cmtw_rx code.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 29.08.2014 1.00    First GSCE Release.
*         : 01.02.2019 1.40    Supported RX65N-64pin.
*                              Corrected interrupt priority level macro names.
*         : 28.06.2024 2.90    Added support Nested Interrupt.  
*         : 15.03.2025 2.91    Updated disclaimer.
***********************************************************************************************************************/
#ifndef CMTW_RX_CONFIG_H
#define CMTW_RX_CONFIG_H

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/
/* Parameter checking configuration */
#define CMTW_CFG_PARAM_CHECKING_ENABLE      (BSP_CFG_PARAM_CHECKING_ENABLE)

/* Acquire lock configuration */
#define CMTW_CGF_REQUIRE_LOCK               (1)

/* Enable the CMTW channels used */
#define CMTW_CFG_USE_CH0                    (1)
#define CMTW_CFG_USE_CH1                    (1)

/* Interrupt level configuration for CMTW timers */
#define CMTW_CFG_IPR_CM_CH0                 (3)
#define CMTW_CFG_IPR_OC0_CH0                (3)
#define CMTW_CFG_IPR_OC1_CH0                (3)
#define CMTW_CFG_IPR_IC0_CH0                (3)
#define CMTW_CFG_IPR_IC1_CH0                (3)
#define CMTW_CFG_IPR_CM_CH1                 (3)
#define CMTW_CFG_IPR_OC0_CH1                (3)
#define CMTW_CFG_IPR_OC1_CH1                (3)
#define CMTW_CFG_IPR_IC0_CH1                (3)
#define CMTW_CFG_IPR_IC1_CH1                (3)

/* Enable CMTW Nested Interrupt */
/* 0 : Disable nested interrupt.*/
/* 1 : Enable nested interrupt.*/
/* (default value = 0)*/
#define CMTW_CFG_EN_NESTED_INT              (0)

#endif /* CMTW_RX_CONFIG_H */

