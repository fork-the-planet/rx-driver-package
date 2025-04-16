/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : LCDConf.h
 * Version      : 1.21
 * Description  : SEGGER internal standard configuration file.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version        Description
 *         : 31.07.2020 6.14.a.1.00    First Release
 *         : 04.09.2020 6.14.a.1.10    Update to adjust r_emwin_rx_config.h file.
 *         : 11.12.2020 6.14.g.1.20    Update to adjust emWin v6.14g. Modify multi-touch and timer function.
 *                                     Adjust GCC and IAR compilers.
 *         : 31.03.2021 6.14.g.1.30    Update to adjust the spec of Smart Configurator and QE for Display.
 *         : 29.12.2021 6.22.  1.00    Update emWin library to v6.22.
 *                                     Adjust configuration option with Smart Configurator.
 *         : 31.08.2022 6.26.c.1.00    Update emWin library to v6.26c.
 *         : 31.03.2023 6.32.a.1.00    Update emWin library to v6.32a.
 *                                     Added LCD_MIRROR definition. (Required for CLUT1)
 *         : 31.01.2024 6.34.g.1.00    Update emWin library to v6.34g.
 *         : 20.03.2025 6.34.g.1.21    Changed the disclaimer.
 *********************************************************************************************************************/
#ifndef LCDCONF_H
#define LCDCONF_H

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_emwin_rx_config.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
/* Check if the Dave2D engine can be used */
#if (EMWIN_BITS_PER_PIXEL > 8)
#define USE_DAVE2D  (EMWIN_USE_DRW2D)
#else
#define USE_DAVE2D  (0)
#endif

#define LCD_MIRROR  (1) /* Required for CLUT1 */

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#if (USE_DAVE2D == 1)
/**********************************************************************************************************************
 * Function Name: drw_int_isr
 * Description  : .
 * Arguments    : .
 * Return Value : .
 *********************************************************************************************************************/
extern void drw_int_isr (void);
#endif

#endif /* LCDCONF_H */
