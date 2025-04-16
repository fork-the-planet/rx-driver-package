/*
* Copyright (c) 2021 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

#ifndef R_FS3000_IF_H_
#define R_FS3000_IF_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_fs3000.h"
#include "r_fs3000_rx_config.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if (1 <= RM_FS3000_CFG_DEVICE_NUM_MAX)
extern const rm_fsxxxx_instance_t g_fs3000_sensor0;
#endif
#if (2 <= RM_FS3000_CFG_DEVICE_NUM_MAX)
extern const rm_fsxxxx_instance_t g_fs3000_sensor1;
#endif

#endif /* R_FS3000_IF_H_ */
