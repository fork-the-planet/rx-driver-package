/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */

#include "ptxPLAT_TIMER.h"
#include <string.h>

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */

//static uint32_t channel = s_timer_cfg.channel;
//static cmt_priority_t priority = st_timer_cfg.priority;

#define PTX_PLAT_TIMER_DIVIDER    (1000)

#define TMR_MSEC_TO_SEC	(1000)

#define TMR_CLK_DIVIDER (8)

/**
 * Timer Context.
 */
ptxPlatTimer_t timer_ctx;
void ptxPLAT_TIMER_IsrCallback(void *p_args);
static volatile uint32_t counter = 0;


/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */

ptxStatus_t ptxPLAT_TIMER_GetInitializedTimer(ptxPlatTimer_t **timer)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != timer)
    {
        /**
         * Initialization of the TIMER Context
         */

        memset(&timer_ctx, 0, sizeof(ptxPlatTimer_t));
		timer_ctx.Freq = 0;
		timer_ctx.TimerChannel = s_timer_cfg.channel;
		*timer = &timer_ctx;
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TIMER_Start (ptxPlatTimer_t         * timer,
                                 uint32_t                 ms,
                                 uint8_t                  isBlock,
                                 pptxPlat_TimerCallBack_t fnISRCb,
                                 void                   * ISRCxt)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != timer) && (ms > 0) && ((0 == isBlock) || (1U == isBlock)))
    {
        /** Clear IsElpased state */
        timer->IsElapsed = 0;

        /** Stop Timer, first. Then, set period. Finally, start timer counter. */
        bool r_status = timer_stop(timer->TimerChannel);

        if (true == r_status)
        {
            timer->ISRCallBack = fnISRCb;
            timer->ISRCxt = ISRCxt;

            uint32_t const CMT_RX_MAX_TIMER_TICKS = 10000;

            uint32_t const min_freq_pwr = ((uint32_t)BSP_PCLKB_HZ) / TMR_CLK_DIVIDER / CMT_RX_MAX_TIMER_TICKS / BSP_CFG_PCKB_DIV;

            if(ms >= TMR_MSEC_TO_SEC)
            {
             		timer->Freq = min_freq_pwr;
             		counter = (ms / TMR_MSEC_TO_SEC) * timer->Freq;
            }
            else
            {
             		timer->Freq = TMR_MSEC_TO_SEC / ms;
             		counter = 0;
            }

            r_status = timer_init(timer->Freq, ptxPLAT_TIMER_IsrCallback, timer->TimerChannel, s_timer_cfg.priority);

            if(true == r_status)
            {
                timer->TimerState = Timer_InUse;
                if (1u == isBlock)
                {
                    /**
                     * WFI until Timer is elapsed. Suitable for Pause() functionality.
                     */
                    while(0 == timer->IsElapsed)
                    {
                    		R_BSP_WAIT();
                    		R_BSP_NOP();
                    }
                }
            }
        }

        if(true != r_status)
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TIMER_IsElapsed(ptxPlatTimer_t *timer, uint8_t *isElapsed)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != timer) && (NULL != isElapsed))
    {
        *isElapsed = timer->IsElapsed;

        if (0 != *isElapsed)
        {
            status = ptxPLAT_TIMER_Stop(timer);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TIMER_Stop(ptxPlatTimer_t *timer)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != timer)
    {
    	bool r_status = timer_stop(timer_ctx.TimerChannel);

    		if(true == r_status)
        {
            timer->IsElapsed  = 0;
            timer->TimerState = Timer_Free;
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_TIMER_Deinit(ptxPlatTimer_t *timer)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != timer)
    {
        /** Timer driver API close stops the timer, disables interrupts and performs other cleanup. */
    	bool r_status = timer_stop(timer_ctx.TimerChannel);

        if(true == r_status)
        {
            memset(&timer_ctx, 0, sizeof(ptxPlatTimer_t));
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

/*
 * ####################################################################################################################
 * INTERNAL FUNCTIONS
 * ####################################################################################################################
 */
void ptxPLAT_TIMER_IsrCallback(void *p_args)
{
    /**
//     * PERIODIC_MODE is used for timer operation:
//     *      -interrupt flags are cleared in ISR routine
//     *      -timer counter is not automatically stopped (unless a Callback-routine is used), as this periodic mechanism is
//     *       is used to prevent a potential race condition between checking the "IsElapsed"-flag and the WFI-instruction in "ptxPLAT_TIMER_Start".
//     */
//	/* Check if the counter has reached its limit; otherwise, continue counting */
	if(0 == counter)
	{
		timer_ctx.IsElapsed = 1U;

		/*Let's call back if defined. */
		if (NULL != timer_ctx.ISRCallBack)
		{
			timer_stop(timer_ctx.TimerChannel);

			if (NULL != timer_ctx.ISRCxt)
			{
				timer_ctx.ISRCallBack(timer_ctx.ISRCxt);
			}
		}
	}
	else
	{
		counter--;
	}
    (void) p_args;
}
