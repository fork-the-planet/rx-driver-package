/*
* Copyright (c) 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/* Guards against multiple inclusion */
#ifndef R_RRH46410_CONFIG_H
#define R_RRH46410_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/* Setting to 0 does not include parameter checking */
#define RM_RRH46410_CFG_PARAM_CHECKING_ENABLE             (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY NUMBER OF DEVICES */
#define RM_RRH46410_CFG_DEVICE_NUM_MAX                    (1) /* Number of RRH46410 Sensors */

/* SPECIFY OPERATION MODE FOR DEVICE0 */
#define RM_RRH46410_CFG_DEVICE0_OPERATION_MODE            (1) /* Set operation mode of RRH46410 Sensor device0 */
                                                            /*
                                                            1 : IAQ 2nd Gen.
                                                            2 : IAQ 2nd Gen. Ultra-Low Power
                                                            5 : PBAQ
                                                             */

/* SPECIFY USING COMMUNICATION LINE INSTANCE FOP DEVICE0 */
#define RM_RRH46410_CFG_DEVICE0_COMMS_INSTANCE            (g_comms_i2c_device0)

/* SPECIFY I2C CALLBACK FUNCTION NAME FOR DEVICE0 */
#define RM_RRH46410_CFG_DEVICE0_COMMS_I2C_CALLBACK        (rrh46410_user_i2c_callback0) /* Enable user I2C callback for RRH46410 Sensor Device0 */

/* SPECIFY IRQ ENABLED FOR DEVICE0 */
#define RM_RRH46410_CFG_DEVICE0_IRQ_ENABLE                (0)

/* SPECIFY IRQ CALLBACK FUNCTION NAME FOR DEVICE0 */
#define RM_RRH46410_CFG_DEVICE0_IRQ_CALLBACK              (rrh46410_user_irq_callback0) /* Enable user IRQ callback for RRH46410 Sensor Device0 */

/* SPECIFY IRQ NUMBER FOR DEVICE0 */
#define RM_RRH46410_CFG_DEVICE0_IRQ_NUMBER                (IRQ_NUM_13)

/* SPECIFY IRQ TRIGGER FOR DEVICE0 */
#define RM_RRH46410_CFG_DEVICE0_IRQ_TRIGGER               (IRQ_TRIG_RISING)

/* SPECIFY IRQ PRIORITY FOR DEVICE0 */
#define RM_RRH46410_CFG_DEVICE0_IRQ_PRIORITY              (IRQ_PRI_2)

#if RM_RRH46410_CFG_DEVICE0_IRQ_ENABLE
#define RM_RRH46410_CFG_IRQ_ENABLE (1)
#else
#define RM_RRH46410_CFG_IRQ_ENABLE (0)
#endif

 #endif  /* R_RRH46410_CONFIG_H */
