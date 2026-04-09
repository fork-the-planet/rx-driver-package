/*
* Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_RAI_DATA_COLLECTER_R_TRANSFER_API_COMPLEMENT_H
#define RM_RAI_DATA_COLLECTER_R_TRANSFER_API_COMPLEMENT_H


/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_dtc_rx_if.h"

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef dtc_transfer_data_cfg_t transfer_info_t;

#ifndef TRANSFER_INSTANCE
#define TRANSFER_INSTANCE
/* RX Driver Instance */
typedef struct st_transfer_instance
{
    dtc_activation_source_t     act_source;             ///< Activation source 
    dtc_transfer_data_t         * p_transfer_data;      ///< Pointer to the transfer data structure
    dtc_transfer_data_cfg_t     * p_data_cfg;           ///< Pointer to the data configuration structure
    uint32_t                    chain_transfer_nr;      ///< Number of chain transfer.
} transfer_instance_t;
#endif

#endif
