/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/* Guards against multiple inclusion */
#ifndef R_RRH62000_CONFIG_H
#define R_RRH62000_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/* Setting to 0 does not include parameter checking */
#define RM_RRH62000_CFG_PARAM_CHECKING_ENABLE             (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY NUMBER OF DEVICES */
#define RM_RRH62000_CFG_DEVICE_NUM_MAX                    (1) /* Number of RRH62000 Sensors */

/* SPECIFY MOVING AVERAGE NUMBER FOR DEVICE0 */
#define RM_RRH62000_CFG_DEVICE0_MOVING_AVERAGE            (10) /* Set number of moving average for RRH62000 Sensor Device0 */

/* SPECIFY FAN SPEED CONTROL FOR DEVICE0 */
#define RM_RRH62000_CFG_DEVICE0_FAN_SPEED                 (86) /* Set fan speed control for RRH62000 Sensor Device0 */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOR DEVICE0 */
#define RM_RRH62000_CFG_DEVICE0_COMMS_INSTANCE            (g_comms_i2c_device0)

/* SPECIFY I2C CALLBACK FUNCTION NAME FOR DEVICE0 */
#define RM_RRH62000_CFG_DEVICE0_COMMS_I2C_CALLBACK        (rrh62000_user_i2c_callback0) /* Enable user I2C callback for RRH62000 Sensor Device0 */

 #endif  /* R_RRH62000_CONFIG_H */
