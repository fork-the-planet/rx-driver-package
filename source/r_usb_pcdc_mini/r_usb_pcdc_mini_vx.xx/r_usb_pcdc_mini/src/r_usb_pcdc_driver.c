/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/******************************************************************************
 * File Name    : r_usb_pcdc_driver.c
 * Description  : USB PCDC Driver code
 ******************************************************************************/
/*******************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 01.09.2014 1.00     First Release
 *         : 30.11.2018 1.10     Supporting Smart Configurator
 *         : 30.06.2020 1.20     Added support for RTOS.
 *         : 20.03.2025 1.31     Changed the disclaimer.
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_mini_if.h"
#include "r_usb_pcdc_mini_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_pcdc.h"
#include "r_usb_bitdefine.h"

#ifdef USB_CFG_PCDC_USE

/******************************************************************************
 Macro definitions
 ******************************************************************************/
extern uint16_t g_usb_pstd_is_connected; /* Peri CDC application enable */

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
  * Function Name: usb_pcdc_read_complete
  * Description  : CallBack Function
  * Arguments    : usb_utr_t   *p_mess  : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 * Return Value : none
 ******************************************************************************/
void usb_pcdc_read_complete (usb_putr_t *p_mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    if ( USB_TRUE == g_usb_pstd_is_connected)
    {
        /* Set Receive data length */
        ctrl.size = 0;
        ctrl.pipe = p_mess->keyword;    /* Pipe number setting */

        if (USB_CFG_PCDC_BULK_OUT == ctrl.pipe)
        {
            ctrl.type = USB_PCDC; /* CDC Data class  */
        }
        else
        {
            ctrl.type = USB_PCDC2; /* CDC Data class  */
        }

        switch (p_mess->status)
        {
            case USB_DATA_OK :
                ctrl.size = p_mess->read_req_len - p_mess->tranlen;
                ctrl.status = USB_SUCCESS;
            break;
            case USB_DATA_SHT :
                ctrl.size = p_mess->read_req_len - p_mess->tranlen;
                ctrl.status = USB_ERR_SHORT;
            break;
            case USB_DATA_OVR :
                ctrl.status = USB_ERR_OVER;
            break;
            case USB_DATA_ERR :
            default :
                ctrl.status = USB_ERR_NG;
            break;
        }
#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
        ctrl.p_data = (void *)p_mess->task_id;
#endif /* (BSP_CFG_RTOS_USED != 0) */
        usb_cstd_set_event(USB_STS_READ_COMPLETE, &ctrl);
    }
} /* End of function usb_pcdc_read_complete() */

/******************************************************************************
  * Function Name: usb_pcdc_write_complete
  * Description  : CallBack Function
  * Arguments    : usb_utr_t   *p_mess  : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 * Return Value : none
 ******************************************************************************/
void usb_pcdc_write_complete (usb_putr_t *p_mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    if ( USB_TRUE == g_usb_pstd_is_connected)
    {
        ctrl.size = 0;
        ctrl.pipe = p_mess->keyword; /* Pipe number setting */
        if (USB_CFG_PCDC_BULK_IN == ctrl.pipe)
        {
            ctrl.type = USB_PCDC; /* CDC Data class  */
        }

        /* USB_CFG_PCDC_INT_IN */
        else if (USB_CFG_PCDC_INT_IN == ctrl.pipe)
        {
            ctrl.type = USB_PCDCC; /* CDC Control class  */
        }
        else if (USB_CFG_PCDC_BULK_IN2 == ctrl.pipe)
        {
            ctrl.type = USB_PCDC2; /* CDC Data class  */
        }
        /* USB_CFG_PCDC_INT_IN2 */
        else
        {
            ctrl.type = USB_PCDCC2; /* CDC Control class  */
        }
        if (USB_DATA_NONE == p_mess->status)
        {
            ctrl.status = USB_SUCCESS;
        }
        else
        {
            ctrl.status = USB_ERR_NG;
        }
#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
        ctrl.p_data = (void *)p_mess->task_id;
#endif /* (BSP_CFG_RTOS_USED != 0) */
        usb_cstd_set_event(USB_STS_WRITE_COMPLETE, &ctrl);
    }
} /* End of function usb_pcdc_write_complete() */

#endif                                 /* USB_CFG_PCDC_USE */

/******************************************************************************
 End  Of File
 ******************************************************************************/
