/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : cellular_disconnect.c
 * Description  : Function to disconnect from the access point.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "cellular_private_api.h"
#include "cellular_freertos.h"
#include "at_command.h"

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

/*******************************************************************************
 * Function Name  @fn            cellular_disconnect
 ******************************************************************************/
e_cellular_err_t cellular_disconnect(st_cellular_ctrl_t * const p_ctrl)
{
    e_cellular_err_t           ret           = CELLULAR_SUCCESS;
    e_cellular_err_semaphore_t semaphore_ret = CELLULAR_SEMAPHORE_SUCCESS;

    semaphore_ret = cellular_take_semaphore(p_ctrl->at_semaphore);
    if (CELLULAR_SEMAPHORE_SUCCESS == semaphore_ret)
    {
        ret = atc_cfun(p_ctrl, CELLULAR_MODULE_OPERATING_LEVEL4);
        if (CELLULAR_SUCCESS == ret)
        {
            p_ctrl->system_state = CELLULAR_SYSTEM_OPEN;
        }
        cellular_give_semaphore(p_ctrl->at_semaphore);
    }
    else
    {
        ret = CELLULAR_ERR_OTHER_ATCOMMAND_RUNNING;
    }

    return ret;
}
/**********************************************************************************************************************
 * End of function cellular_disconnect
 *********************************************************************************************************************/
