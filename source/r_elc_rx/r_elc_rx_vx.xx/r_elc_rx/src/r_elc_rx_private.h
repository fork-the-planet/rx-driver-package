/***********************************************************************************************************************
* Copyright (c) 2016 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_elc_rx_private.h
 * Version      : 4.01
 * Description  : Functions for using Event Link Controller module
 ************************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           01.07.2016 1.0     Initial Release
 *           16.06.2017 1.20    Added support for RX65N(2MB), RX130(512KB)
 *           20.03.2025 4.01    Changed the disclaimer in program sources.
***********************************************************************************************************************/
#ifndef R_ELC_RX_PRIVATE_H
    #define R_ELC_RX_PRIVATE_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "r_elc_rx_if.h"

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
#define ELC_IPR_MAX         (15)

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/
typedef enum
{
    ELC_MODULE_STOP_RELEASE = 0, 
    ELC_MODULE_STOP_TRANSITION = 1
} elc_module_stop_t;

/***********************************************************************************************************************
 Public Functions
 ***********************************************************************************************************************/
void elc_module_control (elc_module_stop_t select);
void elc_open_init_register (void);
void elc_set_eventlink_setting (elc_event_signal_t * const p_elc_event_signal, elc_link_module_t * const p_elc_module);
void elc_control_cmd_event_clear (const elc_module_t clear_select);
void elc_control_cmd_soft_trigger (void);
void elc_start_all_eventlink (void);
void elc_stop_all_eventlink (void);
void elc_control_cmd_write_pdbf (const elc_portbuffer_t portbuffer_select, const uint8_t value);
uint8_t elc_control_cmd_read_pdbf (const elc_portbuffer_t portbuffer_select);
elc_err_t elc_check_validate_module (const elc_module_t link_module);
elc_err_t elc_set_err_check_um_note (elc_event_signal_t * const p_elc_event_signal,
elc_link_module_t * const p_elc_peripheral_module);

#endif /* R_ELC_RX_PRIVATE_H */
/***********************************************************************************************************************
 * End of File
 ***********************************************************************************************************************/
