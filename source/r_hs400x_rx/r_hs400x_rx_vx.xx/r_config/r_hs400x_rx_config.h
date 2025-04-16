/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2021 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/* Guards against multiple inclusion */
#ifndef R_HS400X_CONFIG_H
#define R_HS400X_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/* Setting to 0 does not include parameter checking */
#define RM_HS400X_CFG_PARAM_CHECKING_ENABLE             (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY NUMBER OF DEVICES */
#define RM_HS400X_CFG_DEVICE_NUM_MAX                    (1) /* Number of HS400x Sensors */

/* SPECIFY DATA TYPE */
#define RM_HS400X_CFG_MEASUREMENT_TYPE                  (2) /* Getting measurement type of HS400x Sensors */

/* SPECIFY DATA TYPE */
#define RM_HS400X_CFG_DATA_BOTH_HUMIDITY_TEMPERATURE    (1) /* Getting data type of HS400x Sensors */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOP DEVICE0 */
#define RM_HS400X_CFG_DEVICE0_COMMS_INSTANCE            (g_comms_i2c_device0)

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 0 */
#define RM_HS400X_CFG_DEVICE0_CALLBACK                  (hs400x_user_i2c_callback0) /* Enable user callback for HS400x Sensor Device0 */

/* SPECIFY TEMPERATURE RESOLUTION FOR DEVICE 0 */
#define RM_HS400X_CFG_DEVICE0_TEMPERATURE_RESOLUTION            (RM_HS400X_TEMPERATURE_RESOLUTION_8BIT)

/* SPECIFY HUMIDITY RESOLUTION FOR DEVICE 0 */
#define RM_HS400X_CFG_DEVICE0_HUMIDITY_RESOLUTION               (RM_HS400X_HUMIDITY_RESOLUTION_8BIT)

/* SPECIFY PERIODIC MEASUREMENT FREQUENCY FOR DEVICE 0 */
#define RM_HS400X_CFG_DEVICE0_PERIODIC_MEASUREMENT_FREQUENCY    (RM_HS400X_PERIODIC_MEASUREMENT_FREQUENCY_1HZ)

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOP DEVICE1 */
#define RM_HS400X_CFG_DEVICE1_COMMS_INSTANCE            (g_comms_i2c_device1)

/* SPECIFY CALLBACK FUNCTION NAME FOR DEVICE 1 */
#define RM_HS400X_CFG_DEVICE1_CALLBACK                  (hs400x_user_i2c_callback1) /* Enable user callback for HS400x Sensor Device1 */

/* SPECIFY TEMPERATURE RESOLUTION FOR DEVICE 1 */
#define RM_HS400X_CFG_DEVICE1_TEMPERATURE_RESOLUTION            (RM_HS400X_TEMPERATURE_RESOLUTION_8BIT)

/* SPECIFY HUMIDITY RESOLUTION FOR DEVICE 1 */
#define RM_HS400X_CFG_DEVICE1_HUMIDITY_RESOLUTION               (RM_HS400X_HUMIDITY_RESOLUTION_8BIT)

/* SPECIFY PERIODIC MEASUREMENT FREQUENCY FOR DEVICE 1 */
#define RM_HS400X_CFG_DEVICE1_PERIODIC_MEASUREMENT_FREQUENCY    (RM_HS400X_PERIODIC_MEASUREMENT_FREQUENCY_1HZ)

#endif  /* R_HS400X_CONFIG_H */
