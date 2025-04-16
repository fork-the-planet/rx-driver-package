/*
* Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "r_ble_rx23w_if.h"

#if (BLE_CFG_SOFT_TIMER_EN == 1) && (BLE_CFG_HCI_MODE_EN == 0) && (BSP_CFG_RTOS_USED == 0)

#include "r_cmt_rx_if.h"
#include "platform.h"

static const uint16_t gs_divider[4] = { 8, 32, 128, 512 };
static uint32_t gs_current_timeout_ms;
static uint32_t gs_elapsed_timeout_ms;
static uint32_t gs_cmt_hdl;

extern void process_timer_expire(void);
void pl_stop_timer(void);

static void timer_cb(void *p_data)
{
    process_timer_expire();
}

void pl_init_timer(void)
{
    gs_cmt_hdl = CMT_RX_NO_CHANNEL;
}

void pl_terminate_timer(void)
{
    pl_stop_timer();
}

void pl_start_timer(uint32_t timeout_ms)
{
    gs_current_timeout_ms = MIN(timeout_ms, 1000);
    gs_elapsed_timeout_ms = 0;

    uint32_t timeout_us = gs_current_timeout_ms * 1000;
    R_CMT_CreateOneShot(timeout_us, timer_cb, &gs_cmt_hdl);
}

void pl_stop_timer(void)
{
    gs_current_timeout_ms = 0;
    gs_elapsed_timeout_ms = 0;

    if (CMT_RX_NO_CHANNEL != gs_cmt_hdl)
    {
        R_CMT_Stop(gs_cmt_hdl);
        gs_cmt_hdl = CMT_RX_NO_CHANNEL;
    }
}

uint32_t pl_get_elapsed_time_ms(bool expired)
{
    uint32_t elapsed_time_from_prev_update_ms;
    uint32_t total_elapsed_timeout_ms;

    uint32_t ns_per_tick;
    uint16_t cmstr;
    uint16_t cmcnt;

    switch (gs_cmt_hdl)
    {
        case 0:
        {
            ns_per_tick = (1000000000 / (BSP_PCLKB_HZ / gs_divider[CMT0.CMCR.BIT.CKS]));
            cmstr       = CMT.CMSTR0.BIT.STR0;
            cmcnt       = CMT0.CMCNT;
        } break;

        case 1:
        {
            ns_per_tick = (1000000000 / (BSP_PCLKB_HZ / gs_divider[CMT1.CMCR.BIT.CKS]));
            cmstr       = CMT.CMSTR0.BIT.STR1;
            cmcnt       = CMT1.CMCNT;
        } break;

        case 2:
        {
            ns_per_tick = (1000000000 / (BSP_PCLKB_HZ / gs_divider[CMT2.CMCR.BIT.CKS]));
            cmstr       = CMT.CMSTR1.BIT.STR2;
            cmcnt       = CMT2.CMCNT;
        } break;

        case 3:
        {
            ns_per_tick = (1000000000 / (BSP_PCLKB_HZ / gs_divider[CMT3.CMCR.BIT.CKS]));
            cmstr       = CMT.CMSTR1.BIT.STR3;
            cmcnt       = CMT3.CMCNT;
        } break;

        default:
        {
            /* Currently all RX MCUs have either 2 or 4 CMT channels. */
            /* Refer to the CMT_RX_NUM_CHANNELS defined in r_cmt_rx.c */
            return 0;
        }
    }

    if (expired)
    {
        elapsed_time_from_prev_update_ms = gs_current_timeout_ms - gs_elapsed_timeout_ms;
        gs_elapsed_timeout_ms = gs_current_timeout_ms;
    }
    else if (cmstr)
    {
        total_elapsed_timeout_ms = (cmcnt * ns_per_tick) / 1000000;
        elapsed_time_from_prev_update_ms = total_elapsed_timeout_ms - gs_elapsed_timeout_ms;
        gs_elapsed_timeout_ms = total_elapsed_timeout_ms;
    }
    else if (0 == gs_current_timeout_ms)
    {
        elapsed_time_from_prev_update_ms = 0;
    }

    return elapsed_time_from_prev_update_ms;
}

#endif /* (BLE_CFG_SOFT_TIMER_EN == 1) && (BLE_CFG_HCI_MODE_EN == 0) && (BSP_CFG_RTOS_USED == 0) */
