/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_pcdc_driver.c
 * Version      : 1.44
 * Description  : USB PCDC Driver code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Changed function name "pcdc_read_complete"->"usb_pcdc_read_complete"
 *                           "pcdc_write_complete"->"usb_pcdc_write_complete"
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 30.04.2021 1.31 RX671 is added and VCOM 2Port supported.
 *         : 30.06.2022 1.40 USBX PCDC is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_pcdc_if.h"
#include "r_usb_pcdc.h"
#include "r_usb_bitdefine.h"

#if (BSP_CFG_RTOS_USED != 5)    /* Other than Azure RTOS */

#if defined(USB_CFG_PCDC_USE)
/******************************************************************************
 Macro definitions
 ******************************************************************************/

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 Exported global variables
 ******************************************************************************/

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 Renesas Abstracted Peripheral Communications Devices Class Driver API functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pcdc_read_complete
 Description     : CallBack Function
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 Return          : none
 ******************************************************************************/
void usb_pcdc_read_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    if ( USB_TRUE == g_usb_peri_connected)
    {
        /* Set Receive data length */
        ctrl.size = 0;
        ctrl.pipe = mess->keyword;  /* Pipe number setting */

#if defined(USB_CFG_PCDC_2COM_USE)
        if (USB_CFG_PCDC_BULK_OUT == ctrl.pipe)
        {
            ctrl.type = USB_PCDC; /* CDC Data class  */
        }
        else
        {
            ctrl.type = USB_PCDC2; /* CDC Data class  */
        }
#else  /* defined(USB_CFG_PCDC_2COM_USE) */
        ctrl.type = USB_PCDC; /* CDC Data class  */
#endif /* defined(USB_CFG_PCDC_2COM_USE) */

        switch (mess->status)
        {
            case USB_DATA_OK :
                ctrl.size = mess->read_req_len - mess->tranlen;
                ctrl.status = USB_SUCCESS;
            break;
            case USB_DATA_SHT :
                ctrl.size = mess->read_req_len - mess->tranlen;
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
        ctrl.module = USB_CFG_USE_USBIP;
#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
        ctrl.p_data = (void *)mess->task_id;
#endif /* (BSP_CFG_RTOS_USED != 0) */
        usb_set_event(USB_STS_READ_COMPLETE, &ctrl);
    }
}
/******************************************************************************
 End of function usb_pcdc_read_complete
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pcdc_write_complete
 Description     : CallBack Function
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 Return          : none
 ******************************************************************************/
void usb_pcdc_write_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    if ( USB_TRUE == g_usb_peri_connected)
    {
        ctrl.pipe = mess->keyword; /* Pipe number setting */

#if defined(USB_CFG_PCDC_2COM_USE)
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
#else  /* defined(USB_CFG_PCDC_2COM_USE) */
        if (USB_CFG_PCDC_BULK_IN == ctrl.pipe)
        {
            ctrl.type = USB_PCDC; /* CDC Data class  */
        }
        /* USB_CFG_PCDC_INT_IN */
        else
        {
            ctrl.type = USB_PCDCC; /* CDC Control class  */
        }
#endif /* defined(USB_CFG_PCDC_2COM_USE) */

        if (USB_DATA_NONE == mess->status)
        {
            ctrl.status = USB_SUCCESS;
        }
        else
        {
            ctrl.status = USB_ERR_NG;
        }
        ctrl.module = USB_CFG_USE_USBIP;
#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
        ctrl.p_data = (void *)mess->task_id;
#endif /* (BSP_CFG_RTOS_USED != 0) */
        usb_set_event(USB_STS_WRITE_COMPLETE, &ctrl);
    }
}
/******************************************************************************
 End of function usb_pcdc_write_complete
 ******************************************************************************/
#endif /* defined(USB_CFG_PCDC_USE) */

#endif /* (BSP_CFG_RTOS_USED != 5) */
/******************************************************************************
 End  Of File
 ******************************************************************************/
