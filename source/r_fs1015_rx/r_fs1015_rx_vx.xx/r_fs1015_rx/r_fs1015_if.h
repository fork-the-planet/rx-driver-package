/*
* Copyright (c) 2021 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

#ifndef R_FS1015_IF_H_
#define R_FS1015_IF_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_fs1015.h"
#include "r_fs1015_rx_config.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if (1 <= RM_FS1015_CFG_DEVICE_NUM_MAX)
extern const rm_fsxxxx_instance_t g_fs1015_sensor0;
#endif
#if (2 <= RM_FS1015_CFG_DEVICE_NUM_MAX)
extern const rm_fsxxxx_instance_t g_fs1015_sensor1;
#endif

#endif /* R_FS1015_IF_H_ */
