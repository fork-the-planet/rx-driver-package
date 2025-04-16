/*
* Copyright (c) 2020 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

#ifndef R_FS2012_IF_H_
#define R_FS2012_IF_H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_fs2012.h"
#include "r_fs2012_rx_config.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if (1 <= RM_FS2012_CFG_DEVICE_NUM_MAX)
extern const rm_fsxxxx_instance_t g_fs2012_sensor0;
#endif
#if (2 <= RM_FS2012_CFG_DEVICE_NUM_MAX)
extern const rm_fsxxxx_instance_t g_fs2012_sensor1;
#endif

#endif /* R_FS2012_IF_H_ */
