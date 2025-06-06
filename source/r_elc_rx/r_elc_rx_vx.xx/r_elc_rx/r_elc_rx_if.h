/***********************************************************************************************************************
 * Copyright (c) 2016-2024  Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_elc_rx_if.h
 * Description  : Functions for using Event Link Controller Module 
 ************************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           01.07.2016 1.0     Initial Release
 *           12.09.2016 1.10    Added support for RX65N
 *           16.06.2017 1.20    Added support for RX65N(2MB), RX130(512KB)
 *           01.04.2019 1.21    Changed Minor version to 1.21.
 *           10.06.2020 2.00    Updated version to 2.00 for RX23W release
 *                              Added support for GNUC and ICCRX.
 *                              Fixed coding style.
 *           10.12.2020 2.01    Updated version to 2.01 for RX140 release
 *           31.05.2023 3.00    Added support for RX23E-B
 *           31.07.2024 4.00    Added support for RX260, RX261
 *           20.03.2025 4.01    Changed the disclaimer in program sources.
***********************************************************************************************************************/
#ifndef R_ELC_RX_IF_H
    #define R_ELC_RX_IF_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
    #include    <stdint.h>
    #include "./src/r_elc_rx_platform.h"

/******************************************************************************
 Macro definitions
 ******************************************************************************/
#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

/* Version Number of API. */
    #define ELC_RX_VERSION_MAJOR            (4)
    #define ELC_RX_VERSION_MINOR            (01)

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/
typedef enum
{
    ELC_SUCCESS, 
    ELC_ERR_LOCK_FUNC, 
    ELC_ERR_INVALID_ARG
} elc_err_t;

typedef struct elc_event_signal_s
{
    elc_eventlink_signal_t    event_signal;
    elc_port_trigger_select_t event_signal_input_port_edge;
    elc_single_port_select_t  event_signal_single_port;
    uint8_t                   event_signal_port_group_bit;
} elc_event_signal_t;

typedef struct elc_link_module_s
{
    elc_module_t                 link_module;
    elc_timer_operation_select_t link_module_timer_operation;
    elc_port_level_select_t      link_module_output_port_level;
    elc_single_port_select_t     link_module_single_port;
    uint8_t                      link_module_port_group_bit;
    elc_port_buffer_select_t     link_module_port_buffer;
    uint8_t                      link_module_interrupt_level;
    elc_interrupt_set_t          link_module_callbackfunc;
} elc_link_module_t;

typedef struct elc_pdbf_access_s
{
    elc_portbuffer_t             select_group;
    uint8_t                      value;
} elc_pdbf_access_t;

/***********************************************************************************************************************
 Public Functions
 ***********************************************************************************************************************/
elc_err_t R_ELC_Open (void);
elc_err_t R_ELC_Set (elc_event_signal_t * const p_elc_event_signal, elc_link_module_t * const p_elc_module);
elc_err_t R_ELC_Control (const elc_eventlink_cmd_t command, void *pdata);
elc_err_t R_ELC_Close (void);
uint32_t R_ELC_GetVersion (void);

#endif /* R_ELC_RX_IF_H */
/***********************************************************************************************************************
 * End of File
 ***********************************************************************************************************************/
