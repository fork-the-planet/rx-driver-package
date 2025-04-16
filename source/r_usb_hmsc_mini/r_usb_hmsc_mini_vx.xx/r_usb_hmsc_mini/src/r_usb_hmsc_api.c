/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_hmsc_api.c
 * Description  : USB Host MSC Driver API
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 01.09.2014 1.00    First Release
 *         : 01.06.2015 1.01    Added RX231.
 *         : 29.12.2015 1.02    Minor Update.
 *         : 30.11.2018 1.10    Supporting Smart Configurator
 *         : 30.06.2020 1.20    Added support for RTOS.
 *         : 20.03.2025 1.31    Changed the disclaimer.
************************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
************************************************************************************************************************/

#include "r_usb_hmsc_mini_if.h"
#include "r_usb_cstd_rtos.h"

/**********************************************************************************************************************
 Macro definitions
************************************************************************************************************************/

/**********************************************************************************************************************
 Typedef definitions
************************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
************************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables (to be accessed by other files)
************************************************************************************************************************/

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
/***********************************************************************************************************************
 * Function Name   : R_USB_HmscStrgCmd
 *******************************************************************************************************************//**
 * @brief  Issues a Mass Storage command
 * @param[in, out] p_buf         Pointer to data area
 * @param[in]      command     Mass storage command
 * @retval     USB_SUCCESS     Successfully completed
 * @retval     USB_ERR_PARA    Parameter error
 * @retval     USB_ERR_NG      Other error
 * @details The Mass Storage command assigned to the argument (command) is issued to the MSC device that is specifed 
 * by the members (address and module) in the argument (p_ctrl).
 * @note The argument (p_ctrl) is not supported when using RX100/RX200 series MCU.
 */
usb_err_t   R_USB_HmscStrgCmd(uint8_t *p_buf, uint16_t command)
{
    usb_info_t  info;
    usb_utr_t   utr;
    uint16_t    ret;
    usb_ctrl_t  ctrl;

    R_USB_GetInformation(&info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    ret = usb_hmsc_strg_user_command(command, p_buf);
#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_PAR == ret)
    {
        return USB_ERR_PARA;
    }
#endif /* #if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    if (USB_OK != ret)
    {
        if (USB_HMSC_CSW_ERR == utr.result)
        {
            ctrl.status  = USB_CSW_FAIL;
            ctrl.pipe    = utr.keyword;  /* Pipe number setting */
            ctrl.size = 0;
#if (BSP_CFG_RTOS_USED == 1)                /* FreeRTOS */
            ctrl.p_data = (void *)xTaskGetCurrentTaskHandle();
#endif /* (BSP_CFG_RTOS_USED == 1) */
            usb_cstd_set_event(USB_STS_MSC_CMD_COMPLETE, &ctrl); /* Set Event(USB receive complete)  */
            return USB_SUCCESS;
        }
        else
        {
            return USB_ERR_NG;
        }
    }

    else
    {
        ctrl.pipe    = utr.keyword;  /* Pipe number setting */
        ctrl.size = 0;

        switch (utr.result)
        {
            case USB_HMSC_OK:
                ctrl.size    = utr.tranlen;
                ctrl.status  = USB_CSW_SUCCESS;
            break;

            case USB_HMSC_CSW_ERR:
                ctrl.status  = USB_CSW_FAIL;
            break;

            case USB_HMSC_CSW_PHASE_ERR:
                ctrl.status  = USB_CSW_PHASE;
            break;

            default:
                ctrl.status  = USB_CSW_FAIL;
            break;
        }
#if (BSP_CFG_RTOS_USED == 1)             /* FreeRTOS */
        ctrl.p_data = (void *)xTaskGetCurrentTaskHandle();
#endif /* (BSP_CFG_RTOS_USED == 1) */
        usb_cstd_set_event(USB_STS_MSC_CMD_COMPLETE, &ctrl); /* Set Event(USB receive complete)  */
    }

    return USB_SUCCESS;
}
/**********************************************************************************************************************
 End of function R_USB_HmscStrgCmd
************************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name   : R_USB_HmscGetSem
 *******************************************************************************************************************//**
 * @brief      Gets a semaphore (Only RTOS)
 * @details    Gets a specific semaphore which is used in HMSC driver.
 * @note This API is not supported when using RX100/RX200 series MCU.
 */
void     R_USB_HmscGetSem(void)
{
    rtos_get_semaphore (&g_rtos_usb_hmsc_sem_id, RTOS_FOREVER);
}
/**********************************************************************************************************************
 End of function R_USB_HmscGetSem
************************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name   : R_USB_HmscRelSem
 *******************************************************************************************************************//**
 * @brief      Releases a semaphore (Only RTOS)
 * @details    Releases a specific semaphore which is used in HMSC driver.
 * @note This API is not supported when using RX100/RX200 series MCU.
 */
void     R_USB_HmscRelSem(void)
{
    rtos_release_semaphore (&g_rtos_usb_hmsc_sem_id);
}
/**********************************************************************************************************************
 End of function R_USB_HmscRelSem
************************************************************************************************************************/

#else /* BSP_CFG_RTOS_USED != 0 */
/**********************************************************************************************************************
Function Name   : R_USB_HmscStrgCmd
Description     : Processing for MassStorage(ATAPI) command.
Arguments       : uint8_t       *p_buf  : Pointer to the buffer area to store the transfer data
                : uint16_t      command : ATAPI command
Return value    : usb_err_t error code  : USB_SUCCESS,USB_ERR_NG etc.
************************************************************************************************************************/
usb_err_t   R_USB_HmscStrgCmd (uint8_t *p_buf, uint16_t command)
{
    usb_info_t  info;
    uint16_t    ret;

    R_USB_GetInformation (&info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    ret = usb_hmsc_strg_user_command (command, p_buf, usb_hmsc_strg_cmd_complete);
#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_PAR == ret)
    {
        return USB_ERR_PARA;
    }
#endif /* #if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    if (USB_OK != ret)
    {
        return USB_ERR_NG;
    }

    return USB_SUCCESS;
}
/**********************************************************************************************************************
 End of function R_USB_HmscStrgCmd
************************************************************************************************************************/

#endif /* BSP_CFG_RTOS_USED != 0 */

/**********************************************************************************************************************
 End  Of File
************************************************************************************************************************/
