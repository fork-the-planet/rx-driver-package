/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : GUIConf.h
 * Version      : 1.21
 * Description  : GUI compile time configuration.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version        Description
 *         : 31.07.2020 6.14.a.1.00    First Release
 *         : 04.09.2020 6.14.a.1.10    Update to adjust r_emwin_rx_config.h file.
 *         : 11.12.2020 6.14.g.1.20    Update to adjust emWin v6.14g. Modify multi-touch and timer function.
 *                                     Adjust GCC and IAR compilers.
 *         : 31.03.2021 6.14.g.1.30    Update to adjust the spec of Smart Configurator and QE for Display.
 *         : 29.12.2021 6.20.  1.00    Update emWin library to v6.22.
 *                                     Adjust configuration option with Smart Configurator.
 *         : 31.08.2022 6.26.c.1.00    Update emWin library to v6.26c.
 *         : 31.03.2023 6.32.a.1.00    Update emWin library to v6.32a.
 *         : 31.01.2024 6.34.g.1.00    Update emWin library to v6.34g.
 *         : 20.03.2025 6.34.g.1.21    Changed the disclaimer.
 *********************************************************************************************************************/
#ifndef GUICONF_H
#define GUICONF_H

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define GUI_OS                    (1)  /* Enable multitasking support */
#define GUI_SUPPORT_MEMDEV        (1)  /* Support for memory devices */
#define GUI_SUPPORT_MOUSE         (1)  /* Support a mouse */
#define GUI_SUPPORT_TOUCH         (1)  /* Support a touch screen */
#define GUI_WINSUPPORT            (1)  /* Enable window manager support */

#define GUI_NUM_LAYERS            (16) /* Maximum of available layer */
#define GUI_PID_BUFFER_SIZE       (10) /* Maximum number of PID events with the touch screen */

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#endif /* GUICONF_H */
