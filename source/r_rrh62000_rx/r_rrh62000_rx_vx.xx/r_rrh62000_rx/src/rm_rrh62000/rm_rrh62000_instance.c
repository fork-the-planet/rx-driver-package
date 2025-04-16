/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
 #include "r_comms_i2c_if.h"
 #include "r_rrh62000_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/
extern void rm_rrh62000_comms_i2c_callback (rm_comms_callback_args_t * p_args);
/* RRH62000 Device0 */
#if (1 <= RM_RRH62000_CFG_DEVICE_NUM_MAX)
void rm_rrh62000_callback0(rm_comms_callback_args_t * p_args);
void RM_RRH62000_CFG_DEVICE0_COMMS_I2C_CALLBACK(rm_air_sensor_callback_args_t * p_args);
#endif

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
/* RRH62000 Device0 */
#if (1 <= RM_RRH62000_CFG_DEVICE_NUM_MAX)
rm_rrh62000_instance_ctrl_t g_rrh62000_sensor0_ctrl;
rm_rrh62000_extended_cfg_t g_rrh62000_sensor0_extended_cfg =
{
    .moving_average = RM_RRH62000_CFG_DEVICE0_MOVING_AVERAGE,
    .fan_speed      = RM_RRH62000_CFG_DEVICE0_FAN_SPEED,
};
const rm_air_sensor_cfg_t g_rrh62000_sensor0_cfg =
{
    .p_comms_instance = &(RM_RRH62000_CFG_DEVICE0_COMMS_INSTANCE),
    .p_comms_callback = (void (*)(rm_air_sensor_callback_args_t *))RM_RRH62000_CFG_DEVICE0_COMMS_I2C_CALLBACK,
    .p_context        = NULL,
    .p_extend         = (void *)&g_rrh62000_sensor0_extended_cfg,
};

const rm_air_sensor_instance_t g_rrh62000_sensor0 =
{
    .p_ctrl = &g_rrh62000_sensor0_ctrl,
    .p_cfg  = &g_rrh62000_sensor0_cfg,
    .p_api  = &g_air_sensor_on_rrh62000,
};

void rm_rrh62000_callback0(rm_comms_callback_args_t * p_args)
{
    p_args->p_context = (void *)&g_rrh62000_sensor0_ctrl;
    rm_rrh62000_comms_i2c_callback(p_args);
}

#endif