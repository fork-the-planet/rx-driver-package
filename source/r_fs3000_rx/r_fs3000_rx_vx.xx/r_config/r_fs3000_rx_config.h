/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2021 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/* Guards against multiple inclusion */
#ifndef R_FS3000_CONFIG_H
#define R_FS3000_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/* Setting to 0 does not include parameter checking */
#define RM_FS3000_CFG_PARAM_CHECKING_ENABLE             (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY NUMBER OF DEVICES */
#define RM_FS3000_CFG_DEVICE_NUM_MAX                    (1) /* Number of FS3000 Sensors */

/* SPECIFY USING FS3000 device type */
#define RM_FS3000_CFG_DEVICE_TYPE                       (0) /* Select FS3000 device type */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOP DEVICE0 */
#define RM_FS3000_CFG_DEVICE0_COMMS_INSTANCE            (g_comms_i2c_device0)

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 0 */
#define RM_FS3000_CFG_DEVICE0_CALLBACK                  (fs3000_user_callback0) /* Enable user callback for FS3000 Sensor Device0 */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOR DEVICE1 */
#define RM_FS3000_CFG_DEVICE1_COMMS_INSTANCE            (g_comms_i2c_device1)

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 1 */
#define RM_FS3000_CFG_DEVICE1_CALLBACK                  (fs3000_user_callback1) /* Enable user callback for FS3000 Sensor Device0 */

#endif  /* R_FS3000_CONFIG_H */
