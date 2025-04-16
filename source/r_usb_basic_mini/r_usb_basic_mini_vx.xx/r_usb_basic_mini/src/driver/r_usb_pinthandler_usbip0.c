/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/******************************************************************************
 * File Name    : r_usb_pinthandler_usbip0.c
 * Description  : USB Peripheral interrupt handler code
 ******************************************************************************/
/*******************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00    First Release
 *         : 30.11.2018 1.10    Supporting Smart Configurator
 *         : 30.06.2020 1.20    Added support for RTOS.
 *         : 20.03.2025 1.31    Changed the disclaimer.
*******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_mini_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
#include "r_usb_cstd_rtos.h"
#endif /* (BSP_CFG_RTOS_USED != 0) */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
usb_int_t g_usb_pstd_usb_int;

/*******************************************************************************
 Private global variables and functions
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

    /* Push Interrupt info */
    usb_pstd_interrupt_handler(&p->keyword, &p->status);
    p->msginfo = USB_MSG_PCD_INT;

    rtos_send_mailbox_isr (&g_rtos_usb_pcd_mbx_id, (void *)p);

#else /*(BSP_CFG_RTOS_USED != 0)*/
    /* Push Interrupt info */
    usb_pstd_interrupt_handler(&g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.wp].type,
            &g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.wp].status);

    /* Write count up */
    g_usb_pstd_usb_int.wp = ((g_usb_pstd_usb_int.wp + 1) % USB_INT_BUFSIZE);

#endif /*(BSP_CFG_RTOS_USED != 0)*/
} /* End of function usb_pstd_usb_handler */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 End  Of File
 ******************************************************************************/
