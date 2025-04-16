/*
* Copyright (c) 2021 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
 #include "r_comms_i2c_if.h"
 #include "r_fs3000_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/
#if (1 <= RM_FS3000_CFG_DEVICE_NUM_MAX)
void rm_fs3000_callback0(rm_comms_callback_args_t * p_args);
void RM_FS3000_CFG_DEVICE0_CALLBACK(rm_fsxxxx_callback_args_t * p_args);
#endif
#if (2 <= RM_FS3000_CFG_DEVICE_NUM_MAX)
void rm_fs3000_callback1(rm_comms_callback_args_t * p_args);
void RM_FS3000_CFG_DEVICE1_CALLBACK(rm_fsxxxx_callback_args_t * p_args);
#endif

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
extern void rm_fs3000_callback (rm_comms_callback_args_t * p_args);
#if (1 <= RM_FS3000_CFG_DEVICE_NUM_MAX)
rm_fs3000_instance_ctrl_t g_fs3000_sensor0_ctrl;
const rm_fsxxxx_cfg_t g_fs3000_sensor0_cfg =
{
    .p_instance = &(RM_FS3000_CFG_DEVICE0_COMMS_INSTANCE),
    .p_callback = (void (*)(rm_fsxxxx_callback_args_t *))RM_FS3000_CFG_DEVICE0_CALLBACK,
    .p_context  = NULL,
};
const rm_fsxxxx_instance_t g_fs3000_sensor0 =
{
    .p_ctrl = &g_fs3000_sensor0_ctrl,
    .p_cfg  = &g_fs3000_sensor0_cfg,
    .p_api  = &g_fsxxxx_on_fs3000,
};
void rm_fs3000_callback0(rm_comms_callback_args_t * p_args)
{
    p_args->p_context = (void *)&g_fs3000_sensor0_ctrl;
    rm_fs3000_callback(p_args);
}
#endif
#if (2 <= RM_FS3000_CFG_DEVICE_NUM_MAX)
rm_fs3000_instance_ctrl_t g_fs3000_sensor1_ctrl;
const rm_fsxxxx_cfg_t g_fs3000_sensor1_cfg =
{
	.p_instance = &(RM_FS3000_CFG_DEVICE1_COMMS_INSTANCE),
    .p_callback = (void (*)(rm_fsxxxx_callback_args_t *))RM_FS3000_CFG_DEVICE1_CALLBACK,
    .p_context  = NULL,
};
const rm_fsxxxx_instance_t g_fs3000_sensor1 =
{
    .p_ctrl = &g_fs3000_sensor1_ctrl,
    .p_cfg  = &g_fs3000_sensor1_cfg,
    .p_api  = &g_fsxxxx_on_fs3000,
};
void rm_fs3000_callback1(rm_comms_callback_args_t * p_args)
{
    p_args->p_context = (void *)&g_fs3000_sensor1_ctrl;
    rm_fs3000_callback(p_args);
}
#endif
/**********************************************************************************************************************
 * End of function rm_hs3001_callback1
 *********************************************************************************************************************/


