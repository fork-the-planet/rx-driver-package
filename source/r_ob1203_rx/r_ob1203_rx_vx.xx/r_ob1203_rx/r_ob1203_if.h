/*
* Copyright (c) 2021 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

#ifndef R_OB1203_IF_H_
#define R_OB1203_IF_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_ob1203.h"
#include "r_ob1203_rx_config.h"
#if RM_OB1203_CFG_IRQ_ENABLE
#include "r_irq_rx_if.h"
#include "r_irq_rx_pinset.h"
#endif

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/
/* IRQ */
#ifndef R_SENSOR_IRQ_DEFINE
#define R_SENSOR_IRQ_DEFINE
#if RM_OB1203_CFG_IRQ_ENABLE
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
 * Exported global functions
 *********************************************************************************************************************/
#if (1 <= RM_OB1203_CFG_DEVICE_NUM_MAX)
extern const rm_ob1203_instance_t          g_ob1203_sensor0;
extern       rm_ob1203_mode_extended_cfg_t g_ob1203_sensor0_extended_cfg;
#endif
#if (2 <= RM_OB1203_CFG_DEVICE_NUM_MAX)
extern const rm_ob1203_instance_t          g_ob1203_sensor1;
extern       rm_ob1203_mode_extended_cfg_t g_ob1203_sensor1_extended_cfg;
#endif

#endif /* R_OB1203_IF_H_ */
