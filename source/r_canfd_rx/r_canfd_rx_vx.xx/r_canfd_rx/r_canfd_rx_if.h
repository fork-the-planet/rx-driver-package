/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_canfd_rx_if.h
* Description  : The RX CANFD FIT API.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 22.11.2021 1.00    Initial Release
*                              Supported for RX660.
*         : 28.06.2022 1.10    Changed Minor version to 10.
*         : 06.01.2023 1.20    Changed Minor version to 20.
*         : 31.03.2023 1.30    Changed Minor version to 30.
*                              Supported for RX26T.
*         : 13.12.2023 1.31    Added WAIT_LOOP comments.
*         : 28.06.2024 1.40    Added support for RX261.
*                              Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*         : 15.03.2025 1.41    Updated disclaimer.
***********************************************************************************************************************/
#ifndef CAN_INTERFACE_HEADER_FILE
#define CAN_INTERFACE_HEADER_FILE 

/***********************************************************************************************************************
Includes   "Project Includes"
***********************************************************************************************************************/
#include <stdint.h>
#include "r_canfd.h"
#include "r_can_api.h"
#include "r_canfd_rx_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#if (R_BSP_VERSION_MAJOR < 7)
    #error "This module must use BSP module of Rev.7.00 or higher. Please use the BSP module of Rev.7.00 or higher."
#endif

/* Version Number of API. */
#define CANFD_RX_VERSION_MAJOR           (1)
#define CANFD_RX_VERSION_MINOR           (41)
/* The process of getting the version number is done through the macro below. The version number is encoded where the
   top 2 bytes are the major version number and the bottom 2 bytes are the minor version number. For example,
   Version 4.25 would be returned as 0x00040019. */
#define R_CANFD_GetVersion()  ((((uint32_t)CANFD_RX_VERSION_MAJOR) << 16) | (uint32_t)CANFD_RX_VERSION_MINOR)

/* A pointer to the CAN peripheral registers memory map structure. */
typedef volatile struct st_canfd0 R_BSP_EVENACCESS_SFR * canfd_ch_st_ptr;

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/**************************************************************************************************
Exported global variables
***************************************************************************************************/
/**************************************************************************************************
Exported global functions (to be accessed by other files)
***************************************************************************************************/

/** CANFD on CANFD Instance. */
extern const can_instance_t g_canfd0;

/** Access the CANFD instance using these structures when calling API functions directly (::p_api is not used). */
extern canfd_instance_ctrl_t g_canfd0_ctrl;
extern can_cfg_t             g_canfd0_cfg;
extern canfd_extended_cfg_t  g_canfd0_extended_cfg;
extern can_bit_timing_cfg_t  g_canfd0_bit_timing_cfg;
extern can_bit_timing_cfg_t  g_canfd0_data_timing_cfg;

/* Global configuration (referenced by all instances) */
extern canfd_global_cfg_t g_canfd_global_cfg;
#endif    /* CAN_INTERFACE_HEADER_FILE */
