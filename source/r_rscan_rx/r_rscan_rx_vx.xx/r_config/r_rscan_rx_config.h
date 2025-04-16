/***********************************************************************************************************************
* Copyright (c) 2015 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_rscan_rx_config.h
 * Description  : Configures the RSCAN driver module for the RX231/RX23W/RX23E-A/RX140 MCU
 ***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 22.03.2015 1.00    Initial Release
*         : 31.03.2020 2.21    Added support for RX23E-A
*         : 11.11.2021 2.40    Added support for RX140 (products with 128-Kbyte or larger ROM).
*         : 30.06.2022 2.41    Changed the default value of CAN clock source to PCLK.
*         : 06.09.2024 2.90    Added support Nested Interrupt.
*         : 15.03.2025 2.91    Updated disclaimer.
***********************************************************************************************************************/
#ifndef RSCAN_CONFIG_HEADER_FILE
#define RSCAN_CONFIG_HEADER_FILE


/***********************************************************************************************************************
 Configuration Options
 ***********************************************************************************************************************/
/*
 * SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
 * Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting
 * Setting to 1 includes parameter checking; 0 compiles out parameter checking
 */
#define CAN_CFG_PARAM_CHECKING_ENABLE   (BSP_CFG_PARAM_CHECKING_ENABLE)

/*
 * Setting for CAN clock source.
 * 0 = PCLKB/2
 * 1 = CANMCLK = EXTAL pin              // RSKRX231, RSKRX23W, RX23E-A, RX140
 */
#define CAN_CFG_CLOCK_SOURCE            (0)

/*
 * CAN Interrupt Priority
 */
#define CAN_CFG_INT_PRIORITY            (5)         /* 0-31 */

/*
 * Main Callback Interrupt Sources
 * 0 = disabled                                                                 GetStatusMask() Type
 * 1 = enabled                                      Callback Event              to identify interrupt source
 */
#define CAN_CFG_INT_RXFIFO_THRESHOLD        (1)     /* CAN_EVT_RXFIFO_THRESHOLD CAN_STAT_FIFO_THRESHOLD */
#define CAN_CFG_INT_DLC_ERR                 (0)     /* CAN_EVT_GLOBAL_ERR       CAN_STAT_GLOBAL_ERR */
#define CAN_CFG_INT_HIST_FIFO_OVFL          (1)     /* CAN_EVT_GLOBAL_ERR       CAN_STAT_GLOBAL_ERR, CAN_STAT_FIFO_OVFL */
/* for TX and RX FIFOs */
#define CAN_CFG_INT_FIFO_OVFL               (1)     /* CAN_EVT_GLOBAL_ERR       CAN_STAT_GLOBAL_ERR, CAN_STAT_FIFO_OVFL */

/*
 * Channel Callback Interrupt Sources
 * 0 = disabled                                                                 GetStatusMask() Type
 * 1 = enabled                                      Callback Event              to identify interrupt source
 */
#define CAN_CFG_INT_TXFIFO_THRESHOLD        (1)     /* CAN_EVT_TRANSMIT         CAN_STAT_FIFO_THRESHOLD */
#define CAN_CFG_INT_HIST_FIFO_THRESHOLD     (1)     /* CAN_EVT_TRANSMIT         CAN_STAT_FIFO_THRESHOLD */
#define CAN_CFG_INT_MBX_TX_COMPLETE         (0)     /* CAN_EVT_TRANSMIT         CAN_STAT_CH_TXMBX_SENT */
#define CAN_CFG_INT_MBX_TX_ABORTED          (0)     /* CAN_EVT_TRANSMIT         CAN_STAT_CH_TXMBX_ABORTED */
#define CAN_CFG_INT_BUS_ERROR               (0)     /* CAN_EVT_CHANNEL_ERR      CAN_STAT_CH_ERROR */
#define CAN_CFG_INT_ERR_WARNING             (0)     /* CAN_EVT_CHANNEL_ERR      CAN_STAT_CH_ERROR */
#define CAN_CFG_INT_ERR_PASSIVE             (1)     /* CAN_EVT_CHANNEL_ERR      CAN_STAT_CH_ERROR */
#define CAN_CFG_INT_BUS_OFF_ENTRY           (1)     /* CAN_EVT_CHANNEL_ERR      CAN_STAT_CH_ERROR */
#define CAN_CFG_INT_BUS_OFF_RECOVERY        (1)     /* CAN_EVT_CHANNEL_ERR      CAN_STAT_CH_ERROR */
#define CAN_CFG_INT_OVERLOAD_FRAME_TX       (0)     /* CAN_EVT_CHANNEL_ERR      CAN_STAT_CH_ERROR */
#define CAN_CFG_INT_BUS_LOCK                (0)     /* CAN_EVT_CHANNEL_ERR      CAN_STAT_CH_ERROR */
#define CAN_CFG_INT_ARB_LOST                (0)     /* CAN_EVT_CHANNEL_ERR      CAN_STAT_CH_ERROR */

/* 
 * Enable Nested Interrupt       
 * 0 = disable nested interrupt.
 * 1 = enable nested interrupt.
 * (default value = 0)
 */
#define CAN_CFG_EN_NESTED_INT               (0)

#endif /* RSCAN_CONFIG_HEADER_FILE */
