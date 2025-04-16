/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_phid_driver.c
 * Version      : 1.44
 * Description  : USB HID application code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 30.09.2015 1.11 First Release
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 phid_read_complete(),phid_write_complete is fixed.
 *         : 30.09.2017 1.22 Changed function names
 *                           "phid_write_complete"->"usb_phid_write_complete"
 *                           "phid_read_complete"->"usb_phid_read_complete"
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"
#include "r_usb_phid_if.h"
#include "r_usb_phid.h"

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/


/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 Renesas Abstracted USB Driver functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_phid_write_complete
 Description     : CallBack Function
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 Return          : none
 ******************************************************************************/
void usb_phid_write_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    ctrl.pipe   = mess->keyword;                      /* Pipe number setting */
    ctrl.type   = USB_PHID;                           /* PHID class  */
    ctrl.module = USB_CFG_USE_USBIP;
    ctrl.type   = USB_PHID;                           /* HID Data class  */
    if (USB_DATA_NONE == mess->status)
    {
        ctrl.status = USB_SUCCESS;
    }
    else
    {
        ctrl.status = USB_ERR_NG;
    }
#if (BSP_CFG_RTOS_USED == 1)                          /* FreeRTOS */
    ctrl.p_data = (void *)mess->task_id;
#endif /* (BSP_CFG_RTOS_USED == 1) */
    usb_set_event(USB_STS_WRITE_COMPLETE, &ctrl);
}
/******************************************************************************
 End of function usb_phid_write_complete
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_phid_read_complete
 Description     : CallBack Function
 Arguments       : usb_utr_t    *mess   : Pointer to usb_utr_t structure
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 Return          : none
 ******************************************************************************/
void usb_phid_read_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    /* Set Receive data length */
    ctrl.size = mess->read_req_len - mess->tranlen;

    ctrl.pipe   = mess->keyword;                    /* Pipe number setting */
    ctrl.module = USB_CFG_USE_USBIP;

    ctrl.type   = USB_PHID;                         /* Device class setting  */
    switch (mess->status)
    {
        case USB_DATA_OK :
            ctrl.status = USB_SUCCESS;
        break;
        case USB_DATA_SHT :
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
#if (BSP_CFG_RTOS_USED == 1)                         /* FreeRTOS */
    ctrl.p_data = (void *)mess->task_id;
#endif /* (BSP_CFG_RTOS_USED == 1) */
    usb_set_event(USB_STS_READ_COMPLETE, &ctrl);
}
/******************************************************************************
 End of function usb_phid_read_complete
 ******************************************************************************/


/******************************************************************************
 End  Of File
 ******************************************************************************/
