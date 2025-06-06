/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : sqnssendext.c
 * Description  : Function to execute the AT command (SQNSSENDEXT).
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "at_command.h"
#include "cellular_private_api.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

/*************************************************************************************************
 * Function Name  @fn            atc_sqnssendext
 ************************************************************************************************/
e_cellular_err_t atc_sqnssendext(st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no, const uint16_t length)
{
    uint8_t          str[2][10]                            = {0};
    const uint8_t *  p_command_arg[CELLULAR_MAX_ARG_COUNT] = {0};
    e_cellular_err_t ret                                   = CELLULAR_SUCCESS;

    sprintf((char *)str[0], "%d", socket_no);   // (uint8_t *)->(char *)
    sprintf((char *)str[1], "%d", length);      // (uint8_t *)->(char *)

    p_command_arg[0] = str[0];
    p_command_arg[1] = str[1];

    atc_generate(p_ctrl->sci_ctrl.atc_buff, gp_at_command[ATC_SEND_SOCKET], p_command_arg);

    ret = cellular_execute_at_command(p_ctrl, p_ctrl->sci_ctrl.atc_timeout, ATC_RETURN_OK_GO_SEND, ATC_SEND_SOCKET);

    return ret;
}
/**********************************************************************************************************************
 * End of function atc_sqnssendext
 *********************************************************************************************************************/
