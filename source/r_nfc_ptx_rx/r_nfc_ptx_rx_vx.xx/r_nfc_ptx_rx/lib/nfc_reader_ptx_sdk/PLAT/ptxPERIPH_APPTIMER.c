/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#include "ptxPERIPH_APPTIMER.h"

#define PTX_PLAT_TIMER_DIVIDER (1000)

#define TMR_MSEC_TO_SEC	(1000)

#define TMR_CLK_DIVIDER (8)

static volatile int counter = 0;

/*
 * ####################################################################################################################
 * INTERNAL FUNCTIONS / HELPERS
 * ####################################################################################################################
 */
void ptxPERIPH_APPTIMER_IsrCallback(void *p_args);

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */
ptxStatus_t ptxPERIPH_APPTIMER_Start(uint32_t ms)
{
    ptxStatus_t status = ptxStatus_Success;
    uint32_t freq;

    uint32_t const CMT_RX_MAX_TIMER_TICKS = 10000;

    uint32_t const min_freq_pwr = ((uint32_t)BSP_PCLKB_HZ) / TMR_CLK_DIVIDER / CMT_RX_MAX_TIMER_TICKS / BSP_CFG_PCKB_DIV;

    if(ms >= TMR_MSEC_TO_SEC)
    {
        freq = min_freq_pwr;
        counter = (ms / TMR_MSEC_TO_SEC) * freq;
    }
    else
    {
        freq = TMR_MSEC_TO_SEC / ms;
        counter = 0;
    }

    bool r_status = timer_init(freq, ptxPERIPH_APPTIMER_IsrCallback, s_app_timer_cfg.channel, s_app_timer_cfg.priority);

    if(true != r_status)
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
    }
    return status;
}

ptxStatus_t ptxPERIPH_APPTIMER_Status(TimerStatus_t *timerStatus)
{
	ptxStatus_t status = ptxStatus_Success;
	if(NULL != timerStatus)
	{
		bool isCounting = false;

        bool r_status = timer_status(s_app_timer_cfg.channel, &isCounting);

	    if(true == r_status)
	    {
	    		if(true == isCounting)
	    		{
                timerStatus->IsElapsed = 0u;
                //TODO: Get current timer counter
	    		}
	    		else
	    		{
                timerStatus->IsElapsed = 1u;
                timerStatus->ElapsedTime = 0u;
	    		}
	    }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
        }
    }

    return status;
}

ptxStatus_t ptxPERIPH_APPTIMER_Stop()
{
	ptxStatus_t status = ptxStatus_Success;
    bool r_status = timer_stop(s_app_timer_cfg.channel);
    if(true != r_status)
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
    }

    return status;
}

void ptxPERIPH_APPTIMER_IsrCallback(void *p_args)
{
	if(0 == counter)
	{
        timer_stop(s_app_timer_cfg.channel);
	}
	else
	{
		counter--;
	}
    (void)p_args;
}

