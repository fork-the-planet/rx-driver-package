/*
* Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************
* File Name    : r_mesh_rx23w_if.h
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version  Description
*           30.09.2019  1.00    First Release.
*           29.11.2019  1.01    Added random-delay to ADV-Bearer transmission control.
*           30.09.2020  1.10    Updated Mesh API, Improved Network Layer operation, etc.
*           30.09.2021  1.20    Improved Provisioniong/Network/Transport Layer operation, etc.
*           23.12.2022  1.30    Improved Model Layer operation, etc.
*           31.03.2025  1.31    No update in Mesh stack.
*
* For details, refer to "Program Updates (MESH FIT Module)" in the application note of 
* RX23W Group Bluetooth Mesh FIT Module (R01AN4930).
*******************************************************************************/

#ifndef R_MESH_RX23W_IF_H
#define R_MESH_RX23W_IF_H

/*******************************************************************************
* Includes   <System Includes> , "Project Includes"
*******************************************************************************/
/* Mesh Stack headers */
#include "MS_access_api.h"
#include "MS_assigned_numbers.h"
#include "MS_brr_api.h"
#include "MS_common.h"
#include "MS_config_api.h"
#include "MS_error.h"
#include "MS_generic_battery_api.h"
#include "MS_generic_default_transition_time_api.h"
#include "MS_generic_level_api.h"
#include "MS_generic_location_api.h"
#include "MS_generic_onoff_api.h"
#include "MS_generic_power_level_api.h"
#include "MS_generic_power_onoff_api.h"
#include "MS_generic_property_api.h"
#include "MS_health_client_api.h"
#include "MS_health_server_api.h"
#include "MS_light_ctl_api.h"
#include "MS_light_hsl_api.h"
#include "MS_light_lc_api.h"
#include "MS_light_lightness_api.h"
#include "MS_light_xyl_api.h"
#include "MS_ltrn_api.h"
#include "MS_model_states.h"
#include "MS_net_api.h"
#include "MS_prov_api.h"
#include "MS_scene_api.h"
#include "MS_scheduler_api.h"
#include "MS_sensor_api.h"
#include "MS_time_api.h"
#include "MS_trn_api.h"
#include "MS_version.h"
#include "EM_os.h"
#include "EM_platform.h"
#include "EM_timer.h"
#include "MS_features.h"

/* Mesh Stack configurations */
#include "r_mesh_rx23w_config.h"

#endif /* R_MESH_RX23W_IF_H */
