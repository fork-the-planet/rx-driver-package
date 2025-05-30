/*
* Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name: r_ble_cli.h
 * Description : Command Line Interface Library.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @file
 * @defgroup cli Command Line Interface Library
 * @{
 * @ingroup app_lib
 * @brief Command Line Interface Library.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <stdint.h>
#include <string.h>
#include "r_ble_rx23w_if.h"
#include "console/r_ble_console.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#ifndef R_BLE_CLI_H
#define R_BLE_CLI_H

/** @defgroup cli_macro Macros 
 *  @{
 *  @brief Macro definition
 */

/*******************************************************************************************************************//**
 * @brief Maximum characters in a line
 **********************************************************************************************************************/
#define BLE_CLI_LINE_LEN          (80)

/*******************************************************************************************************************//**
 * @brief Number of history command.
 **********************************************************************************************************************/
#define BLE_CLI_NUM_OF_HISTORY    (8)

/*******************************************************************************************************************//**
 * @brief Number of sections in a line 
 **********************************************************************************************************************/
#define BLE_CLI_NUM_OF_COMPLEMENT (10)
/*@}*/

/** @defgroup cli_callback Callbacks
 *  @{
 *  @brief Callback definition
 */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Command execution handler.
 **********************************************************************************************************************/
typedef void (*ble_cli_exec_cb_t)(int argc, char *p_argv[]);

/*******************************************************************************************************************//**
 * @brief Command abort handler.
 **********************************************************************************************************************/
typedef void (*ble_cli_abort_cb_t)(void);
/*@}*/

/** @defgroup cli_struct Structures 
 *  @{
 *  @brief Structure definition
 */

/*******************************************************************************************************************//**
 * @brief Command parameters.
 **********************************************************************************************************************/
typedef struct st_ble_cli_cmd_t
{
    const char                            *p_name;      /**< Command name. */
    const char                            *p_help;      /**< Command help message. */
    const struct st_ble_cli_cmd_t * const *p_cmds;      /**< Sub commands. */
    uint16_t                              num_of_cmds;  /**< Number of sub commands */
    ble_cli_exec_cb_t                     exec;         /**< Command execution handler. */
    ble_cli_abort_cb_t                    abort;        /**< Command abort handler. */
} st_ble_cli_cmd_t;
/*@}*/

/** @defgroup cli_func Functions
 *  @{
 *  @brief Function definition
 */

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Initialize CLI library.
 * @return BLE_SUCCESS, otherwise an error code
 **********************************************************************************************************************/
ble_status_t R_BLE_CLI_Init(void);

/*******************************************************************************************************************//**
 * @brief Terminate CLI library.
 * @return BLE_SUCCESS, otherwise an error code
 **********************************************************************************************************************/
ble_status_t R_BLE_CLI_Terminate(void);

/*******************************************************************************************************************//**
 * @brief Register top level commands.
 * @param[in] p_cmds      Commands
 * @param[in] num_of_cmds Number of commands
 * @return BLE_SUCCESS, otherwise an error code
 **********************************************************************************************************************/
ble_status_t R_BLE_CLI_RegisterCmds(const st_ble_cli_cmd_t * const p_cmds[], uint16_t num_of_cmds);

/*******************************************************************************************************************//**
 * @brief Register CLI event callback for RTOS task wakeup.
 * @param[in] cb        callback pointer
 * @return BLE_SUCCESS, otherwise an error code
 **********************************************************************************************************************/
ble_status_t R_BLE_CLI_RegisterEventCb(ble_cli_event_cb_t cb);

/*******************************************************************************************************************//**
 * @brief Process input characters from the user.
 * @details This function process the input characters.
 **********************************************************************************************************************/
void R_BLE_CLI_Process(void);

/*******************************************************************************************************************//**
 * @brief Process input characters from the user with return value.
 * @details This function process the input characters.
 **********************************************************************************************************************/
bool R_BLE_CLI_Process_With_Retval(void);

/*******************************************************************************************************************//**
 * @brief Print with format like printf.
 * @details This function print with format.
 **********************************************************************************************************************/
#if (BLE_CFG_CMD_LINE_EN == 1)
#define R_BLE_CLI_Printf console_putsf
#else /* (BLE_CFG_CMD_LINE_EN == 1) */
#define R_BLE_CLI_Printf   /* null macro */
#endif /* (BLE_CFG_CMD_LINE_EN == 1) */

/*******************************************************************************************************************//**
 * @brief Inform the completion of abortable command.
 **********************************************************************************************************************/
void R_BLE_CLI_SetCmdComp(void);


/*******************************************************************************************************************//**
 * @brief Print unrecognized operands message.
 * @details This function print unrecognized operands message.\n
 *          message format:  "<latest command line>: unrecognized operands\n"
 **********************************************************************************************************************/
void R_BLE_CLI_PrintUnrecognized(void);

/*******************************************************************************************************************//**
 * @brief Print command error message.
 * @details This function print command error message.\n
 *          message format: "command error. result : <ret>\n"
 * @param[in] ret  Result code to print in the error message.
 **********************************************************************************************************************/
void R_BLE_CLI_PrintError(ble_status_t ret);
/*@}*/

#endif /* R_BLE_CLI_H */

/*@}*/
