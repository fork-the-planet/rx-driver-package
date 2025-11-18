/** \file
    /*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
    /* ---------------------------------------------------------------

    Project     : PTX1K
    Module      : Transparent Data Channel (TDC) Timer Support API
    File        : ptxTDC_Timer.c

    Description : Platform dependent Timer API used by TDC Component.
                  Implements Stop-Watch functionality. 
*/

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */
#include "ptxTDC_Timer.h"
#include "ptxPERIPH_APPTIMER.h"

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */

/*
 * ####################################################################################################################
 * INTERNAL FUNCTIONS / HELPERS
 * ####################################################################################################################
 */

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */

ptxStatus_t ptxTDC_Timer_Start(uint32_t ms)
{
    ptxStatus_t status;

    status = ptxPERIPH_APPTIMER_Start(ms);
    
    return status;
}

ptxStatus_t ptxTDC_Timer_Status(ptxTDC_Timer_Status_t *timerStatus)
{
    ptxStatus_t status = ptxStatus_Success;
    
    if (NULL != timerStatus)
    {
        TimerStatus_t app_timer_status = {0};

        status = ptxPERIPH_APPTIMER_Status(&app_timer_status);

        /* Map Elapsed-Status */
        if (ptxStatus_Success == status)
        {
            timerStatus->IsElapsed = app_timer_status.IsElapsed;
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_TDC, ptxStatus_InvalidParameter);
    }
    
    return status;
}

ptxStatus_t ptxTDC_Timer_Stop()
{
    ptxStatus_t status;

    status = ptxPERIPH_APPTIMER_Stop();

    return status;
}

