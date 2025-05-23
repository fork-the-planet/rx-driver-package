/*
* Copyright (C) 2014-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
* File Name    : r_flash_type1_if.h
* Description  : This module implements equates/declarations specific to Flash Type 1 MCUs
**********************************************************************************************************************/
/**********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*                02.18.2014 1.10    Support for RX110, RX111, RX113
*                12.01.2015 1.20    Updated for RX231
*                12.08.2016 2.00    Modified for BSPless flash.
*                17.11.2016 2.10    Added flash_stop() declaration.
*                                   Added FLASH_FREQ_xx and FLASH_FCU_INT_xxx #defines
*                05.10.2016 3.00    Merged functions common to other flash types into r_flash_group.c.
*                26.06.2020 4.60    Added FLASH_ACCESS_WINDOW_END_NEXT_REG_VALUE #define.
*                23.04.2021 4.80    Added RX140.
*                13.05.2022 4.90    Added support for Tool News R20TS0818.
*                24.01.2023 5.00    Modified FLASH_FREQ_HI.
*                30.07.2024 5.20    Added support for RX260 and RX261.
*                20.03.2025 5.22    Changed the disclaimer in program sources
**********************************************************************************************************************/

#ifndef R_FLASH_TYPE1_IF_H
#define R_FLASH_TYPE1_IF_H

#include "r_flash_rx_if.h"
#if (FLASH_TYPE == FLASH_TYPE_1)

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_flash_rx.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/*  operation definition (FEXCR Register setting)*/
#define FEXCR_STARTUP       (0x81)
#define FEXCR_AW            (0x82)
#define FEXCR_CLEAR         (0x00)

#define DEFAULT_AREA        (1)
#define DEFAULT_AREA_VALUE  (0xFFFF)
#define STARTUP_AREA_VALUE  (0xFEFF)

#define SASMF_ALTERNATE     (0)
#define SASMF_DEFAULT       (1)

#define FLASH_FREQ_LO           (1000000)
#if (FLASH_TYPE_VARIETY == FLASH_TYPE_VARIETY_A)
#if defined(MCU_RX140)
#define FLASH_FREQ_HI           (48000000)
#elif defined(MCU_RX260) || defined(MCU_RX261)
#define FLASH_FREQ_HI           (64000000)
#endif
#else
#define FLASH_FREQ_HI           (32000000)
#endif
#define FLASH_FCU_INT_ENABLE    // no FCU
#define FLASH_FCU_INT_DISABLE   // no FCU

#if (FLASH_TYPE_VARIETY == FLASH_TYPE_VARIETY_A)
#define FLASH_ACCESS_WINDOW_END_VALUE  (0x400)
#elif defined(MCU_RX23_ALL) || defined(MCU_RX24_ALL)
#define FLASH_ACCESS_WINDOW_END_VALUE (0x800)
#else
#define FLASH_ACCESS_WINDOW_END_VALUE (0x200)
#endif

/* Definition for function name compatibility */
#define R_CF_GetCurrentSwapState   flash_get_current_swap_state
#define R_CF_SetCurrentSwapState   flash_set_current_swap_state
#define R_CF_GetCurrentStartupArea flash_get_current_startup_area
#define R_CF_ToggleStartupArea     flash_toggle_startup_area
#define R_CF_GetAccessWindow       flash_get_access_window
#define R_CF_SetAccessWindow       flash_set_access_window

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/
uint8_t flash_get_current_swap_state(void);
void flash_set_current_swap_state(uint8_t value);
uint8_t flash_get_current_startup_area(void);
flash_err_t flash_toggle_startup_area(void);
flash_err_t flash_get_access_window(flash_access_window_config_t *pAccessInfo);
flash_err_t flash_set_access_window(flash_access_window_config_t *pAccessInfo);
flash_err_t flash_wait_exrdy(void);

#endif /* #if (FLASH_TYPE == FLASH_TYPE_1) */
#endif /* R_FLASH_TYPE1_IF_H */

/* end of file */
