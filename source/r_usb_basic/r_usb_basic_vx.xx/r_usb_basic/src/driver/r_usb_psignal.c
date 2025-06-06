/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_psignal.c
 * Version      : 1.44
 * Description  : USB Peripheral signal control code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 30.06.2022 1.40 USBX PCDC is supported.
 *         : 30.09.2023 1.42 USBX HCDC is supported.
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

#if (BSP_CFG_RTOS_USED == 5)
 #include "ux_api.h"
 #include "ux_system.h"
 #include "ux_utility.h"
 #include "ux_device_stack.h"
#endif  /* (BSP_CFG_RTOS_USED == 5) */


#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if USB_CFG_BC == USB_CFG_ENABLE
extern uint16_t        g_usb_bc_detect;

#endif  /* USB_CFG_BC == USB_CFG_ENABLE */

/******************************************************************************
 Renesas Abstracted Peripheral signal control functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_bus_reset
 Description     : A USB bus reset was issued by the host. Execute relevant pro-
                 : cessing.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_bus_reset (void)
{
    uint16_t connect_info;

    /* Bus Reset */
    usb_pstd_busreset_function();

    /* Memory clear */
    usb_pstd_clr_mem();
    connect_info = usb_cstd_port_speed(USB_NULL);

 #if (BSP_CFG_RTOS_USED == 5)   /* Azure RTOS */
    switch (connect_info)
    {
        case USB_HSCONNECT:
        {
            _ux_system_slave->ux_system_slave_speed = (uint32_t) UX_HIGH_SPEED_DEVICE;
            break;
        }

        case USB_FSCONNECT:
        {
            _ux_system_slave->ux_system_slave_speed = (uint32_t) UX_FULL_SPEED_DEVICE;
            break;
        }

        case USB_LSCONNECT:
        {
            _ux_system_slave->ux_system_slave_speed = (uint32_t) UX_LOW_SPEED_DEVICE;
            break;
        }

        default:
        {
            break;
        }
    }
 #endif                                /* #if (BSP_CFG_RTOS_USED == 5) */

    /* Callback */
    if (USB_NULL != g_usb_pstd_driver.devdefault)
    {
#if USB_CFG_BC == USB_CFG_ENABLE
        (*g_usb_pstd_driver.devdefault)(USB_NULL, connect_info, g_usb_bc_detect);
#else   /* USB_CFG_BC == USB_CFG_ENABLE */
        (*g_usb_pstd_driver.devdefault)(USB_NULL, connect_info, USB_NULL);
#endif  /* USB_CFG_BC == USB_CFG_ENABLE */

#if (BSP_CFG_RTOS_USED == 5)   /* Azure RTOS */
        usb_peri_usbx_initialize_complete();
#endif     /* #if (BSP_CFG_RTOS_USED == 5) */
    }

    /* DCP configuration register  (0x5C) */
    hw_usb_write_dcpcfg(USB_NULL, 0);

    /* DCP maxpacket size register (0x5E) */
    hw_usb_write_dcpmxps(USB_NULL, g_usb_pstd_driver.p_devicetbl[USB_DEV_MAX_PKT_SIZE]);
}
/******************************************************************************
 End of function usb_pstd_bus_reset
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_attach_process
 Description     : USB attach setting.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_attach_process (void)
{
    usb_cpu_delay_xms((uint16_t) 10);
#if USB_CFG_BC == USB_CFG_ENABLE
    usb_pstd_bc_detect_process();

#endif  /* USB_CFG_BC == USB_CFG_ENABLE */
    hw_usb_pset_dprpu();

}
/******************************************************************************
 End of function usb_pstd_attach_process
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_detach_process
 Description     : Initialize USB registers for detaching, and call the callback
                 : function that completes the detach.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_detach_process (void)
{
    uint16_t i;

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    hw_usb_clear_cnen(USB_NULL);
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
    /* Pull-up disable */
    hw_usb_pclear_dprpu();

    /* Configuration number */
    g_usb_pstd_config_num = 0;

    /* Remote wakeup enable flag */
    g_usb_pstd_remote_wakeup = USB_FALSE;

    /* WAIT_LOOP */
    for (i = USB_MIN_PIPE_NO; i < (USB_MAXPIPE_NUM +1); i++)
    {
        if (USB_TRUE == g_usb_pipe_table[USB_CFG_USE_USBIP][i].use_flag)
        {
            usb_pstd_forced_termination(i, (uint16_t) USB_DATA_STOP);
            usb_cstd_clr_pipe_cnfg(USB_NULL, i);
#if (BSP_CFG_RTOS_USED == 5)    /* Azure RTOS */
            g_usb_peri_usbx_is_detach[i] = USB_YES;
            rtos_release_semaphore(&g_usb_peri_usbx_sem[i]);
            rtos_delete_semaphore(&g_usb_peri_usbx_sem[i]);
#endif  /* #if (BSP_CFG_RTOS_USED == 5) */
        }
    }

    /* Callback */
    if (USB_NULL != g_usb_pstd_driver.devdetach)
    {
        (*g_usb_pstd_driver.devdetach)(USB_NULL, USB_POWERED, USB_NULL);
    }
}
/******************************************************************************
 End of function usb_pstd_detach_process
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_suspend_process
 Description     : Perform a USB peripheral suspend.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_suspend_process (void)
{
    uint16_t intsts0;
    uint16_t buf;

    /* Resume interrupt enable */
    hw_usb_pset_enb_rsme();

    intsts0 = hw_usb_read_intsts();
    buf = hw_usb_read_syssts(USB_NULL);
    if (((uint16_t) 0 != (intsts0 & USB_DS_SUSP)) && (USB_FS_JSTS == (buf & USB_LNST)))
    {
        /* Suspend */
        usb_pstd_stop_clock();
        usb_pstd_suspend_function();

        /* Callback */
        if (USB_NULL != g_usb_pstd_driver.devsuspend)
        {
            (*g_usb_pstd_driver.devsuspend)(USB_NULL, g_usb_pstd_remote_wakeup, USB_NULL);
        }
    }

    /* --- SUSPEND -> RESUME --- */
    else
    {
        /* RESM status clear */
        hw_usb_pclear_sts_resm();

        /* RESM interrupt disable */
        hw_usb_pclear_enb_rsme();
    }
}
/******************************************************************************
 End of function usb_pstd_suspend_process
 ******************************************************************************/
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 End  Of File
 ******************************************************************************/
