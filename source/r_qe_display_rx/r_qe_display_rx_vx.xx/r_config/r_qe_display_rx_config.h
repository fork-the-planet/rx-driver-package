/*
 * Copyright (c) 2024 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/***********************************************************************************************************************
 * File Name    : r_qe_display_rx_config.h
 * Version      : 1.11
 * Description  : Configuration header file of QE for Display module.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 19.07.2024 1.00     First Release
 *         : 20.03.2025 1.11     Changed the disclaimer.
 **********************************************************************************************************************/

#ifndef R_QE_DISPLAY_RX_CONFIG_H
#define R_QE_DISPLAY_RX_CONFIG_H

/***********************************************************************************************************************
 * Configuration Options
 **********************************************************************************************************************/


/* Select SCI channel number.
 * Setting range: 0 to 12
 */
#define QE_DISPLAY_CFG_UART_CH  (0)


/* Specify UART baud rate.
 * Set the baud rate to be the same as the QE for Display settings.
 * The maximum baud rate is device dependent.
 * Refer to the user's manual for device used.
 */
#define QE_DISPLAY_CFG_UART_BAUDRATE (115200)


/* Interrupt priority level of SCI interrupt.
 *  Setting range: 0 to 15
 */
#define QE_DISPLAY_CFG_UART_INTERRUPT_PRIORITY_LEVEL (5)


/* Select whether to send communication and adjustment error messages to the standard output
 * (normally the console of the development environment connected to the debugger).
 *  0 : No error message will be sent.
 *  1 : Sends an error message.
 */
#define QE_DISPLAY_CFG_DEBUG_PRINT_ENABLE (0)


#endif /* R_QE_DISPLAY_RX_CONFIG_H */

/* End of File */
