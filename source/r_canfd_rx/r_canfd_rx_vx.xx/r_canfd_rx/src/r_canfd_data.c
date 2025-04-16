/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_canfd_data.c
* Description  : Functions for using CANFD
***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           22.11.2021 1.00    Initial Release.
*           15.03.2025 1.41    Updated disclaimer.
***********************************************************************************************************************/
#include "r_canfd_rx_if.h"

#ifndef CANFD_PRV_GLOBAL_CFG
#define CANFD_PRV_GLOBAL_CFG
canfd_global_cfg_t g_canfd_global_cfg =
{ .global_interrupts = CANFD_CFG_GLOBAL_ERR_SOURCES, .global_config = (CANFD_CFG_TX_PRIORITY | CANFD_CFG_DLC_CHECK
        | ((1U == CANFD_CFG_CANFDCLK_SOURCE) ? R_CANFD_GCFG_DLLCS_Msk : 0U)
        | CANFD_CFG_FD_OVERFLOW),
  .rx_mb_config = (CANFD_CFG_RXMB_NUMBER | (CANFD_CFG_RXMB_SIZE << R_CANFD_RMCR_PLS_Pos)), .global_err_ipl =
          CANFD_CFG_GLOBAL_ERR_IPL,
  .rx_fifo_ipl = CANFD_CFG_RX_FIFO_IPL, .rx_fifo_config =
  { ((CANFD_CFG_RXFIFO0_INT_THRESHOLD << R_CANFD_RFCR_RFITH_Pos)
            | (CANFD_CFG_RXFIFO0_DEPTH << R_CANFD_RFCR_FDS_Pos)
            | (CANFD_CFG_RXFIFO0_PAYLOAD << R_CANFD_RFCR_PLS_Pos) | (CANFD_CFG_RXFIFO0_INT_MODE)
            | (CANFD_CFG_RXFIFO0_ENABLE)),
    ((CANFD_CFG_RXFIFO1_INT_THRESHOLD << R_CANFD_RFCR_RFITH_Pos)
            | (CANFD_CFG_RXFIFO1_DEPTH << R_CANFD_RFCR_FDS_Pos)
            | (CANFD_CFG_RXFIFO1_PAYLOAD << R_CANFD_RFCR_PLS_Pos) | (CANFD_CFG_RXFIFO1_INT_MODE)
            | (CANFD_CFG_RXFIFO1_ENABLE)), }, };
#endif

/* Config Nominal bit rate */
can_bit_timing_cfg_t g_canfd0_bit_timing_cfg =
{
.baud_rate_prescaler = CANFD0_BIT_TIMING_CFG_BRP,
  .time_segment_1 = CANFD0_BIT_TIMING_CFG_TSEG1, .time_segment_2 = CANFD0_BIT_TIMING_CFG_TSEG2, .synchronization_jump_width = CANFD0_BIT_TIMING_CFG_SJW };

/* Config data rate */
can_bit_timing_cfg_t g_canfd0_data_timing_cfg =
{
.baud_rate_prescaler = CANFD0_DATA_TIMING_CFG_BRP,
  .time_segment_1 = CANFD0_DATA_TIMING_CFG_TSEG1, .time_segment_2 = CANFD0_DATA_TIMING_CFG_TSEG2, .synchronization_jump_width = CANFD0_DATA_TIMING_CFG_SJW };

canfd_extended_cfg_t g_canfd0_extended_cfg =
{ .p_afl = NULL, .txmb_txi_enable = (CANFD0_EXTENDED_CFG_TXMB0_TXI_ENABLE
        | CANFD0_EXTENDED_CFG_TXMB1_TXI_ENABLE
        | CANFD0_EXTENDED_CFG_TXMB2_TXI_ENABLE
        | CANFD0_EXTENDED_CFG_TXMB3_TXI_ENABLE | 0ULL), .error_interrupts = (CANFD0_EXTENDED_CFG_WARNING_ERROR_INTERRUPTS
                | CANFD0_EXTENDED_CFG_PASSING_ERROR_INTERRUPTS
                | CANFD0_EXTENDED_CFG_BUS_OFF_ENTRY_ERROR_INTERRUPTS
                | CANFD0_EXTENDED_CFG_BUS_OFF_RECOVERY_ERROR_INTERRUPTS
                | CANFD0_EXTENDED_CFG_OVERLOAD_ERROR_INTERRUPTS | 0U),
  .p_data_timing = &g_canfd0_data_timing_cfg, .delay_compensation = CANFD0_EXTENDED_CFG_DELAY_COMPENSATION, .p_global_cfg = &g_canfd_global_cfg, };

canfd_instance_ctrl_t g_canfd0_ctrl;
can_cfg_t g_canfd0_cfg =
{ .channel = 0, .p_bit_timing = &g_canfd0_bit_timing_cfg, .p_callback = NULL, .p_extend =
          &g_canfd0_extended_cfg,
  .p_context = NULL, .ipl = CANFD0_CFG_IPL,
        };

/* Instance structure to use this module. */
const can_instance_t g_canfd0 =
{ .p_ctrl = &g_canfd0_ctrl, .p_cfg = &g_canfd0_cfg, .p_api = &g_canfd_on_canfd };
