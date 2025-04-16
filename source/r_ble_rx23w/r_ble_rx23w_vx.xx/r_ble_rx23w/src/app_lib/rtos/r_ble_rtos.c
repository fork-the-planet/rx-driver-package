/*
* Copyright (c) 2020-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * File Name    : r_ble_rtos.c
 * Description  : BLE Task functions for FreeRTOS. 
 **********************************************************************************************************************/

/***********************************************************************************************************************
  Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_ble_rtos.h"

#if (BSP_CFG_RTOS_USED == 1)

#include "FreeRTOS.h"
#include "task.h"

/***********************************************************************************************************************
Export global variables
***********************************************************************************************************************/
TaskHandle_t g_ble_task_hdl;

/***********************************************************************************************************************
* Function Name: R_BLE_RTOS_WakeTask
* Description  : Wake up the ble task from other task.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void R_BLE_RTOS_WakeTask(void)
{
    xTaskNotifyGive(g_ble_task_hdl);
    taskYIELD();
}

/***********************************************************************************************************************
* Function Name: R_BLE_RTOS_WakeTaskFromIsr
* Description  : Wake up the ble task from ISR.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void R_BLE_RTOS_WakeTaskFromIsr(void)
{
    BaseType_t xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;
    if (g_ble_task_hdl != NULL)
    {
        vTaskNotifyGiveFromISR(g_ble_task_hdl, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

#endif /* (BSP_CFG_RTOS_USED == 1) */
