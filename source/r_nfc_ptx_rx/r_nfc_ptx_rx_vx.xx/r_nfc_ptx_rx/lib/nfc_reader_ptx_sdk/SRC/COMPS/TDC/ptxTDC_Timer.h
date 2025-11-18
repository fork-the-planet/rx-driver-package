/** \file
    /*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
    /* /* ---------------------------------------------------------------

    Project     : PTX1K
    Module      : Transparent Data Channel (TDC) Timer Support API
    File        : ptxTDC_Timer.h

    Description : Platform dependent Timer API used by TDC Component.
                  Implements Stop-Watch functionality. 
*/

/**
 * \addtogroup grp_ptx_api_tdc_timer Transparent Data Channel (TDC) Timer API
 *
 * @{
 */

#ifndef APIS_PTX_TDC_TIMER_H_
#define APIS_PTX_TDC_TIMER_H_

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */

#include <stdint.h>
#include "ptxStatus.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */

/*
 * ####################################################################################################################
 * TYPES
 * ####################################################################################################################
 */

/**
 * \brief TDC Timer: Component Structure.
 */
typedef struct ptxTDC_Timer_Status
{
    uint8_t     IsElapsed;      /**< Status Info whether Timer elapsed or is still running. */
    uint32_t    ElapsedTime;    /**< Elapsed Time given in ms. */

} ptxTDC_Timer_Status_t;

/**
 * \brief Initializes and starts the TDC timer for a given duration.
 *
 * \param[in]   ms  Milliseconds until the timer elapses.
 *
 * \return Status, indicating whether the operation was successful. See \ref ptxStatus_t.
 */
ptxStatus_t ptxTDC_Timer_Start(uint32_t ms);

/**
 * \brief Retrieves status information from the timer.
 *
 * \param[in,out]   timerStatus Pointer to \ref ptxTDC_Timer_Status_t.
 *
 * \return Status, indicating whether the operation was successful. See \ref ptxStatus_t.
 */
ptxStatus_t ptxTDC_Timer_Status(ptxTDC_Timer_Status_t *timerStatus);

/**
 * \brief Stops and deinitializes the TDC timer.
 *
 * \return Status, indicating whether the operation was successful. See \ref ptxStatus_t.
 */
ptxStatus_t ptxTDC_Timer_Stop();

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* Guard */

