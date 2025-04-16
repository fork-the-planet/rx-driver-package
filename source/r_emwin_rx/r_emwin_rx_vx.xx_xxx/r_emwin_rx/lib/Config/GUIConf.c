/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : GUIConf.c
 * Version      : 1.21
 * Description  : GUI runtime configuration.
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
 *         : 31.01.2024 6.34.g.1.00    Update emWin library to v6.34g.
 *         : 20.03.2025 6.34.g.1.21    Changed the disclaimer.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdint.h>
#include "GUI.h"
#if (GUI_SUPPORT_TOUCH == 1)
#include "PIDConf.h"
#endif

#include "r_emwin_rx_config.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: GUI_X_Config
 * Description  : Called during the initialization process in order to set up the available memory for the GUI.
 * Arguments    : .
 * Return Value : .
 *********************************************************************************************************************/
void GUI_X_Config(void)
{
    /* 32 bit aligned memory area */
    static uint32_t s_a_memory[EMWIN_GUI_NUM_BYTES / 4];

    /* Assign memory to emWin */
    GUI_ALLOC_AssignMemory(s_a_memory, EMWIN_GUI_NUM_BYTES);

    /* Create and select default font */
    GUI_SetDefaultFont(&GUI_Font6x8);

#if (GUI_SUPPORT_TOUCH == 1)
    /* Set PID init function */
    GUI_PID_SetInitFunc(PID_X_Init);
#endif
}
/**********************************************************************************************************************
 End of function GUI_X_Config
 *********************************************************************************************************************/
