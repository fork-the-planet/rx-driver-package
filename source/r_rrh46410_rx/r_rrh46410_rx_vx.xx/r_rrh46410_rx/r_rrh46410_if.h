/*
* Copyright (c) 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

#ifndef R_RRH46410_IF_H_
#define R_RRH46410_IF_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_rrh46410.h"
#include "rm_zmod4xxx_api.h"
#if RM_RRH46410_CFG_IRQ_ENABLE
#include "r_irq_rx_if.h"
#include "r_irq_rx_pinset.h"
#endif

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/
/* IRQ */
#ifndef R_SENSOR_IRQ_DEFINE
#define R_SENSOR_IRQ_DEFINE
#if RM_RRH46410_CFG_IRQ_ENABLE
typedef struct st_external_irq_instance
{
    irq_number_t number;
    irq_trigger_t trigger;
    irq_prio_t priority;
    irq_handle_t * p_handle;
    void (* p_callback)(void *pargs);
} external_irq_instance_t;
#endif
typedef struct st_external_irq_callback_args
{
    void * p_context;
} external_irq_callback_args_t;
#endif /* R_SENSOR_IRQ_DEFINE */

 /**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
 #if (1 <= RM_RRH46410_CFG_DEVICE_NUM_MAX)
/* ZMOD4XXX on RRH46410 Sensor Instance. */
/** Access the RRH46410 Sensor instance using these structures when calling API functions directly (::p_api is not used). */
extern rm_rrh46410_instance_ctrl_t g_rrh46410_sensor0_ctrl;
extern const rm_zmod4xxx_cfg_t g_rrh46410_sensor0_cfg;
#endif

#endif /* R_RRH46410_IF_H_ */
