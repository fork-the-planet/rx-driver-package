/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2020 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/* Guards against multiple inclusion */
#ifndef R_HS300X_CONFIG_H
#define R_HS300X_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/* Setting to 0 does not include parameter checking */
#define RM_HS300X_CFG_PARAM_CHECKING_ENABLE             (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY NUMBER OF DEVICES */
#define RM_HS300X_CFG_DEVICE_NUM_MAX                    (1) /* Number of HS300x Sensors */

/* SPECIFY DATA TYPE */
#define RM_HS300X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE    (1) /* Getting data type of HS300x Sensors */

/* SPECIFY PROGRAMMING MODE ON/OFF */
#define RM_HS300X_CFG_PROGRAMMING_MODE                  (0) /* Enable to enter the programming mode for HS300x Sensor */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOP DEVICE0 */
#define RM_HS300X_CFG_DEVICE0_COMMS_INSTANCE            (g_comms_i2c_device0)

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 0 */
#define RM_HS300X_CFG_DEVICE0_CALLBACK                  (hs300x_user_callback0) /* Enable user callback for HS300x Sensor Device0 */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOP DEVICE1 */
#define RM_HS300X_CFG_DEVICE1_COMMS_INSTANCE            (g_comms_i2c_device1)

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 1 */
#define RM_HS300X_CFG_DEVICE1_CALLBACK                  (hs300x_user_callback1) /* Enable user callback for HS300x Sensor Device0 */

#endif  /* R_HS300X_CONFIG_H */
