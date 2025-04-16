/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2020 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/* Guards against multiple inclusion */
#ifndef R_FS2012_CONFIG_H
#define R_FS2012_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/* Setting to 0 does not include parameter checking */
#define RM_FS2012_CFG_PARAM_CHECKING_ENABLE             (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY NUMBER OF DEVICES */
#define RM_FS2012_CFG_DEVICE_NUM_MAX                    (1) /* Number of FS2012 Sensors */

/* SPECIFY USING FS2012 device type */
#define RM_FS2012_CFG_DEVICE_TYPE                       (0) /* Select FS2012 device type */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOP DEVICE0 */
#define RM_FS2012_CFG_DEVICE0_COMMS_INSTANCE            (g_comms_i2c_device0)

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 0 */
#define RM_FS2012_CFG_DEVICE0_CALLBACK                  (fs2012_user_callback) /* Enable user callback for FS2012 Sensor Device0 */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOR DEVICE1 */
#define RM_FS2012_CFG_DEVICE1_COMMS_INSTANCE            (g_comms_i2c_device1)

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 1 */
#define RM_FS2012_CFG_DEVICE1_CALLBACK                  (fs2012_user_callback1) /* Enable user callback for FS2012 Sensor Device0 */

#endif  /* R_FS2012_CONFIG_H */
