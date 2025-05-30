/*
* Copyright (c) 2020 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
 #include "r_comms_i2c_if.h"
 #include "r_hs300x_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/
#if (1 <= RM_HS300X_CFG_DEVICE_NUM_MAX)
void rm_hs300x_callback0(rm_comms_callback_args_t * p_args);
void RM_HS300X_CFG_DEVICE0_CALLBACK(rm_hs300x_callback_args_t * p_args);
#endif
#if (2 <= RM_HS300X_CFG_DEVICE_NUM_MAX)
void rm_hs300x_callback1(rm_comms_callback_args_t * p_args);
void RM_HS300X_CFG_DEVICE1_CALLBACK(rm_hs300x_callback_args_t * p_args);
#endif

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
extern void rm_hs300x_callback (rm_comms_callback_args_t * p_args);
#if (1 <= RM_HS300X_CFG_DEVICE_NUM_MAX)
rm_hs300x_instance_ctrl_t g_hs300x_sensor0_ctrl;
const rm_hs300x_cfg_t g_hs300x_sensor0_cfg =
{
    .p_instance = &(RM_HS300X_CFG_DEVICE0_COMMS_INSTANCE),
    .p_callback = (void (*)(rm_hs300x_callback_args_t *))RM_HS300X_CFG_DEVICE0_CALLBACK,
    .p_context  = NULL,
};
const rm_hs300x_instance_t g_hs300x_sensor0 =
{
    .p_ctrl = &g_hs300x_sensor0_ctrl,
    .p_cfg  = &g_hs300x_sensor0_cfg,
    .p_api  = &g_hs300x_on_hs300x,
};
void rm_hs300x_callback0(rm_comms_callback_args_t * p_args)
{
    p_args->p_context = (void *)&g_hs300x_sensor0_ctrl;
    rm_hs300x_callback(p_args);
}
#endif
#if (2 <= RM_HS300X_CFG_DEVICE_NUM_MAX)
const rm_hs300x_cfg_t g_hs300x_sensor1_cfg =
{
	.p_instance = &(RM_HS300X_CFG_DEVICE1_COMMS_INSTANCE),
    .p_callback = (void (*)(rm_hs300x_callback_args_t *))RM_HS300X_CFG_DEVICE1_CALLBACK,
    .p_context  = NULL,
};
rm_hs300x_instance_ctrl_t g_hs300x_sensor1_ctrl;
const rm_hs300x_instance_t g_hs300x_sensor1 =
{
    .p_ctrl = &g_hs300x_sensor1_ctrl,
    .p_cfg  = &g_hs300x_sensor1_cfg,
    .p_api  = &g_hs300x_on_hs300x,
};
void rm_hs300x_callback1(rm_comms_callback_args_t * p_args)
{
    p_args->p_context = (void *)&g_hs300x_sensor1_ctrl;
    rm_hs300x_callback(p_args);
}
#endif
/**********************************************************************************************************************
 * End of function rm_hs3001_callback1
 *********************************************************************************************************************/


