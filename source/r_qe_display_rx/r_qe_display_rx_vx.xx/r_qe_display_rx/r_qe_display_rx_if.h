/*
 * Copyright (c) 2024 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/***********************************************************************************************************************
 * File Name    : r_qe_display_rx_if.h
 * Version      : 1.11
 * Description  : Interface header file for QE for Display FIT module.
 ***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 19.07.2024 1.00    Initial Release
 *         : 20.09.2024 1.10    Updated version.
 *         : 20.03.2025 1.11    Changed the disclaimer.
 **********************************************************************************************************************/

#ifndef R_QE_DISPLAY_RX_IF_H
#define R_QE_DISPLAY_RX_IF_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "platform.h"
#include "r_qe_display_rx_config.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* Version Number of API. */
#define QE_DISPLAY_VERSION_MAJOR (1)
#define QE_DISPLAY_VERSION_MINOR (11)


/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

typedef enum e_qe_display_err
{
    QE_DISPLAY_SUCCESS = 0,
    QE_DISPLAY_ERR_NOT_OPEN,
    QE_DISPLAY_ERR_ALREADY_OPENED,
    QE_DISPLAY_ERR_LCD_CONFIG,
    QE_DISPLAY_ERR_LCD_OTHER,
    QE_DISPLAY_ERR_UART_CONFIG,
    QE_DISPLAY_ERR_UART_OTHER
} qe_display_err_t;


/***********************************************************************************************************************
 Public Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_QE_DISPLAY_Open
 *******************************************************************************************************************//**
 * @brief This function initializes GLCDC and serial communication with QE for Display. This function must be called
 * before calling any other API functions.
 * @param None.
 * @retval QE_DISPLAY_SUCCESS            Processing has been completed successfully.
 * @retval QE_DISPLAY_ERR_ALREADY_OPENED The module was already opened.
 * @retval QE_DISPLAY_ERR_LCD_CONFIG     LCD setting error.
 * @retval QE_DISPLAY_ERR_UART_CONFIG    Serial communication setting error.
 * @details Executing this function initializes GLCDC and serial communication with QE Display.
 * @note 1. If you want to make adjustments based on images designed with the emWin FIT module
 *        and Aeropoint GUI FIT module, please initialize them before executing this function.
 * @note 2. When using DMAC/DTC with the SCI FIT module, the initialization functions
 *        (R_DMAC_Init function, R_DTC_Open function) of the DMAC and DTC FIT module are not executed
 *        within this module.
 *        Therefore, execute these initialization functions (R_DMAC_Init function, R_DTC_Open function)
 *        before executing this function.
 **********************************************************************************************************************/
qe_display_err_t R_QE_DISPLAY_Open (void);


/***********************************************************************************************************************
 * Function Name: R_QE_DISPLAY_Exec
 *******************************************************************************************************************//**
 * @brief This function executes GLCDC adjustment processing and error processing based on the data received
 * from QE for Display.
 * @param None.
 * @retval QE_DISPLAY_SUCCESS            Processing has been completed successfully.
 * @retval QE_DISPLAY_ERR_NOT_OPEN       R_QE_DISPLAY_Open function has not been executed.
 * @retval QE_DISPLAY_ERR_LCD_OTHER      Other LCD errors.
 * @retval QE_DISPLAY_ERR_UART_OTHER     Other serial communication errors.
 * @details Executes GLCDC adjustment processing. Make sure that this function is executed repeatedly
 * in the main routine.
 * @note None.
 **********************************************************************************************************************/
qe_display_err_t R_QE_DISPLAY_Exec (void);


/***********************************************************************************************************************
 * Function Name: R_QE_DISPLAY_GetVersion
 *******************************************************************************************************************//**
 * @brief This function returns the current version of this API.
 * @param None.
 * @return Version of this API.
 * @details This function will return the version of the currently running API. The version number is encoded where the
 * top 2 bytes are the major version number and the bottom 2 bytes are the minor version number.
 * For example, Version 4.25 would be returned as 0x00040019.
 * @note None.
 **********************************************************************************************************************/
uint32_t R_QE_DISPLAY_GetVersion (void);


#endif /* R_QE_DISPLAY_RX_IF_H */

/* End of File */
