/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_nfc_ptx_data.c
 * Description  : Data definitions for PTX NFC driver.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdint.h>
#include "r_nfc_ptx_common.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef R_NFC_PTX_DATA_H_
#define R_NFC_PTX_DATA_H_

#if (SCI_CFG_SSPI_INCLUDED == 1)
extern const sci_sync_sspi_t s_spi_cfg;
extern const st_gpio_conf_t s_spi_ss_cfg;
#endif

extern const st_irq_conf_t s_ext_irq_cfg;

extern const st_timer_cfg_t s_app_timer_cfg;

extern const st_timer_cfg_t s_timer_cfg;

#endif
