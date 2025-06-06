/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : sqnsl.c
 * Description  : Function to execute the AT command (SQNSL).
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
 * Function Name  @fn            atc_sqnsl
 ************************************************************************************************/
e_cellular_err_t atc_sqnsl(st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no,
                            const uint8_t ip_version, const uint16_t port)
{
    uint8_t          ip_type                               = 1;
    uint8_t          str[3][10]                            = {0};
    const uint8_t *  p_command_arg[CELLULAR_MAX_ARG_COUNT] = {0};
    e_cellular_err_t ret                                   = CELLULAR_SUCCESS;

    if (CELLULAR_PROTOCOL_IPV4 != ip_version)
    {
        ip_type = 2;
    }

    sprintf((char *)str[0], "%d", socket_no);    // (&uint8_t[])->(char *)
    sprintf((char *)str[1], "%d", ip_type);      // (&uint8_t[])->(char *)
    sprintf((char *)str[2], "%d", port);         // (&uint8_t[])->(char *)

    p_command_arg[0] = str[0];
    p_command_arg[1] = str[1];
    p_command_arg[2] = str[2];

    atc_generate(p_ctrl->sci_ctrl.atc_buff, gp_at_command[ATC_LISTENING_SOCKET], p_command_arg);

    ret = cellular_execute_at_command(p_ctrl, p_ctrl->sci_ctrl.atc_timeout, ATC_RETURN_OK, ATC_LISTENING_SOCKET);

    return ret;
}
/**********************************************************************************************************************
 * End of function atc_sqnsl
 *********************************************************************************************************************/
