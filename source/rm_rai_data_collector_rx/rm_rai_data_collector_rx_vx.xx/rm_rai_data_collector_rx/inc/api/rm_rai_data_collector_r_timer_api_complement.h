/*
* Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_RAI_DATA_COLLECTER_R_TIMER_API_COMPLEMENT_H
#define RM_RAI_DATA_COLLECTER_R_TIMER_API_COMPLEMENT_H


/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_cmt_rx_if.h"
/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#ifndef TIMER_INSTANCE
#define TIMER_INSTANCE
/* RX Driver Instance */
typedef struct st_timer_instance
{
    uint32_t const          freqency_hz;            ///< Frequency [Hz]
    uint32_t const          channel;                ///< Channel
    cmt_priority_t const    priority;
    void (* callback)       (void * pdata);         ///< Callback function
} timer_instance_t;
#endif

#endif
