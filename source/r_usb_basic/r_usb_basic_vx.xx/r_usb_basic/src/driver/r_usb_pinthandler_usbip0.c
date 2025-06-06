/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_pinthandler_usbip0.c
 * Version      : 1.44
 * Description  : USB Peripheral interrupt handler code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
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

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
#include "r_rtos_abstract.h"
#include "r_usb_cstd_rtos.h"
#endif /* (BSP_CFG_RTOS_USED != 0) */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
usb_int_t g_usb_pstd_usb_int;

/******************************************************************************
 Renesas Abstracted common Interrupt handler functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_usb_handler
 Description     : USB interrupt routine. Analyze which USB interrupt occurred
                 : and send message to PCD task.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_usb_handler (void)
{
#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
    usb_utr_t       *p;
    rtos_err_t      ret;
    
    ret = rtos_get_fixed_memory_isr(&g_rtos_usb_mpf_id, (void **)&p);
    if (RTOS_ERROR == ret)
    {
        return; /* Error */
    }

    usb_pstd_interrupt_clock();

    /* Push Interrupt info */
    usb_pstd_interrupt_handler(&p->keyword, &p->status);
    p->msginfo = USB_MSG_PCD_INT;

    ret = rtos_send_mailbox_isr (&g_rtos_usb_pcd_mbx_id, (void *)p);
    if (RTOS_SUCCESS != ret)
    {
        USB_PRINTF1("### lib_UsbHandler DEF2 isnd_msg error (%ld)\n", err);
    }

#endif /*(BSP_CFG_RTOS_USED != 0)*/

#if (BSP_CFG_RTOS_USED == 0)        /* Non-OS */
    usb_pstd_interrupt_clock();
    usb_pstd_interrupt_handler(&g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.wp].type,
            &g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.wp].status);

    /* Write count up */
    g_usb_pstd_usb_int.wp = ((g_usb_pstd_usb_int.wp + 1) % USB_INT_BUFSIZE);

#endif /*(BSP_CFG_RTOS_USED == 0)*/
}
/******************************************************************************
 End of function usb_pstd_usb_handler
 ******************************************************************************/
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 End  Of File
 ******************************************************************************/
