/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_hreg_abs.c
 * Description  : Call USB Host register access function 
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 31.11.2018 1.10 Supporting Smart Configurator
 *         : 31.05.2019 1.11 Added support for GNUC and ICCRX.
 *         : 30.06.2019 1.12 RX23W is added.
 *         : 30.06.2020 1.20 Added support for RTOS.
 *         : 30.04.2024 1.30 Added support for RX261.
 *         : 20.03.2025 1.31 Changed the disclaimer.
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_basic_mini_if.h"

#if (BSP_CFG_RTOS_USED == 0)    /* Non-OS */

#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"
#include "r_usb_dmac.h"

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
/******************************************************************************
Function Name   : usb_hstd_check_interrupt_source
Description     : USB interrupt Handler
Argument        : usb_strct_t  *p_inttype         : Interrupt type
                : usb_strct_t  *p_bitsts          : Interrupt status
Return          : none
******************************************************************************/
void usb_hstd_check_interrupt_source(usb_strct_t *p_inttype, uint16_t *p_bitsts)
{
    reg_access_t    intsts0;
    reg_access_t    intsts1;
    reg_access_t    brdysts;
    reg_access_t    nrdysts;
    reg_access_t    bempsts;
    reg_access_t    intenb0;
    reg_access_t    intenb1;
    reg_access_t    brdyenb;
    reg_access_t    nrdyenb;
    reg_access_t    bempenb;
    intstsbit_t     ists_u;
    intsts1bit_t    ists1_w;
    reg_access_t    bsts_d;
    reg_access_t    nsts_d;
    reg_access_t    ests_d;
    uint16_t    stat;
    usb_strct_t key;

    /* Interrupt Control & Status Register Save */
    intsts0.word.w = USB0.INTSTS0.WORD;
    intsts1.word.w = USB0.INTSTS1.WORD;
    brdysts.word.w = USB0.BRDYSTS.WORD;
    nrdysts.word.w = USB0.NRDYSTS.WORD;
    bempsts.word.w = USB0.BEMPSTS.WORD;
    intenb0.word.w = USB0.INTENB0.WORD;
    intenb1.word.w = USB0.INTENB1.WORD;
    brdyenb.word.w = USB0.BRDYENB.WORD;
    nrdyenb.word.w = USB0.NRDYENB.WORD;
    bempenb.word.w = USB0.BEMPENB.WORD;

    /* Interrupt status get */
    ists_u.byte.b       = (uint8_t)(intsts0.word.byte.up & intenb0.word.byte.up);
    ists1_w.word.w      = (uint16_t)(intsts1.word.w & intenb1.word.w);
    bsts_d.word.w       = (uint16_t)(brdysts.word.w & brdyenb.word.w);
    nsts_d.word.w       = (uint16_t)(nrdysts.word.w & nrdyenb.word.w);
    ests_d.word.w       = (uint16_t)(bempsts.word.w & bempenb.word.w);

    key     = USB_INT_UNKNOWN;
    stat    = 0;

    /***** Setup transaction processing *****/
    if (0 != ists1_w.word.bit.sack)                 /***** Setup ACK *****/
    {
        usb_hstd_setup_disable();
        key     = USB_INT_SACK;
    }
    else if (0 != ists1_w.word.bit.sign)            /***** Setup Ignore *****/
    {
        usb_hstd_setup_disable();
        key     = USB_INT_SIGN;
    }

    /***** PIPE0-MAX_PIPE_NO data processing *****/
    else if (0 != ists_u.byte.bit.brdy)             /***** EP0-7 BRDY *****/
    {
        stat    = bsts_d.word.w;
        USB0.BRDYSTS.WORD = (uint16_t) ((~stat) & USB_BRDYSTS_MASK);
        key     = USB_INT_BRDY;
    }
    else if (0 != ists_u.byte.bit.bemp)             /***** EP0-7 BEMP *****/
    {
        stat    = ests_d.word.w;
        USB0.BEMPSTS.WORD = (uint16_t) ((~stat) & USB_BEMPSTS_MASK);
        key     = USB_INT_BEMP;
    }
    else if (0 != ists_u.byte.bit.nrdy)             /***** EP0-7 NRDY *****/
    {
        stat    = nsts_d.word.w;
        USB0.NRDYSTS.WORD = (uint16_t) ((~stat) & USB_NRDYSTS_MASK);
        key     = USB_INT_NRDY;
    }

    /***** Port0 signal processing *****/
    else if (0 != ists1_w.word.bit.ovrcr)           /***** OVER CURRENT *****/
    {
        hw_usb_hclear_sts_ovrcr();
        key     = USB_INT_OVRCR0;
    }
    else if (0 != ists1_w.word.bit.attch)           /***** ATTCH INT *****/
    {
        /* DTCH  interrupt disable */
        usb_hstd_bus_int_disable();
        key     = USB_INT_ATTCH0;
    }
    else if (0 != ists1_w.word.bit.eoferr)          /***** EOFERR INT *****/
    {
        /* EOFERR Clear */
        USB0.INTSTS1.WORD = (uint16_t) ((~USB_EOFERR) & USB_INTSTS1_MASK);
        key     = USB_INT_EOFERR0;
    }
    else if (0 != ists1_w.word.bit.bchg)            /***** BCHG INT *****/
    {
        /* BCHG  interrupt disable */
        usb_hstd_bchg_disable();
        key     = USB_INT_BCHG0;
    }
    else if (0 != ists1_w.word.bit.dtch)            /***** DETACH INT *****/
    {
        /* DTCH  interrupt disable */
        usb_hstd_bus_int_disable();
        key     = USB_INT_DTCH0;
    }
#if USB_CFG_BC == USB_CFG_ENABLE
    else if (0 != ists1_w.word.bit.pddetint)        /***** PDDETINT INT *****/
    {
        USB0.INTSTS1.WORD = (uint16_t) ((~USB_PDDETINT) & USB_INTSTS1_MASK);
        key = USB_INT_PDDETINT0;
    }
#endif

    /***** VBUS/SOF signal processing *****/
    else if (0 != ists_u.byte.bit.vbint)            /***** VBUS change *****/
    {
        USB0.INTSTS0.WORD = (uint16_t) ~USB_VBINT;
        key = USB_INT_VBINT;
    }
    else if (0 != ists_u.byte.bit.sofr)             /***** SOFR change *****/
    {
        /* SOFR Clear */
        USB0.INTSTS0.WORD = (uint16_t) ~USB_SOFR;
        key = USB_INT_SOFR;
    }
    else
    {
        /* no processing */
    }
    *p_bitsts     = stat;
    *p_inttype    = key;
}
/******************************************************************************
 End of function usb_hstd_check_interrupt_source
 ******************************************************************************/

/******************************************************************************
Function Name   : usb_hstd_interrupt_handler
 Description     : USB interrupt routine. Analyze which USB interrupt occurred 
                 : and send message to HCD task.
Arguments       : none
Return value    : none
******************************************************************************/
void usb_hstd_interrupt_handler(void)
{
    usb_intinfo_t       *p_utr;

    p_utr = &g_usb_hstd_int_msg[g_usb_hstd_int_msg_cnt];
    usb_hstd_check_interrupt_source(&p_utr->inttype, &p_utr->bitsts);
    if (USB_OK != USB_ISND_MSG(USB_HCD_MBX, (usb_msg_t*)p_utr))
    {
        USB_DEBUG_HOOK(USB_DEBUG_HOOK_HOST | USB_DEBUG_HOOK_CODE4);
    }

    /* Renewal Message count */
    g_usb_hstd_int_msg_cnt++;
    if (USB_INTMSGMAX == g_usb_hstd_int_msg_cnt)
    {
        g_usb_hstd_int_msg_cnt  = 0;
    }
}
/******************************************************************************
 End of function usb_hstd_interrupt_handler
 ******************************************************************************/


/******************************************************************************
Function Name   : usb_hstd_detach_process
 Description     : Handles the require processing when USB device is detached
                 : (Data transfer forcibly termination processing to the connected USB Device,
                 : the clock supply stop setting and the USB interrupt dissable setteing etc)
Arguments       : none
Return value    : none
******************************************************************************/
void usb_hstd_detach_process(void)
{
    usb_addr_t addr;

    /* OVRCR, ATTCH, DTCH, BCHG interrupt disable */
    usb_hstd_bus_int_disable();

    /* WAIT_LOOP */
    for (g_usb_hcd_devaddr = USB_DEVICE_0; g_usb_hcd_devaddr <= USB_MAXDEVADDR; g_usb_hcd_devaddr++ )
    {
        if (USB_NOCONNECT != usb_hstd_devaddr_to_speed())
        {
            if (USB_IDLEST != g_usb_hstd_ctsq)
            {
                /* Control Read/Write End */
                usb_hstd_setup_disable();
                usb_hstd_control_end(USB_DATA_DTCH);
            }
            /* WAIT_LOOP */
            for (g_usb_hstd_current_pipe = USB_MIN_PIPE_NO; 
                                            g_usb_hstd_current_pipe <= USB_MAX_PIPE_NO; g_usb_hstd_current_pipe++ )
            {
                /* Not control transfer */
                addr = usb_hstd_pipe_to_addr();
                if (g_usb_hcd_devaddr == addr)
                {
                    /* Agreement device address */
                    if (usb_cstd_get_pid(g_usb_hstd_current_pipe) == USB_PID_BUF )
                    {
                        /* End of data transfer (IN/OUT) */
                        usb_hstd_forced_termination(USB_DATA_DTCH);
                    }
                    usb_cstd_clr_pipe_config(g_usb_hstd_current_pipe);
                }
            }
            usb_hstd_set_devaddx_register(USB_NOCONNECT);
        }
    }

    /* Decide USB Line state (ATTACH) */
    if (USB_LNST_ATTACH == usb_hstd_check_attach())
    {
        usb_hstd_status_notification(USB_RTP_DETACH, (usb_strct_t)g_usb_hstd_hcd_port);
        usb_hstd_attach_control();
    }
    else
    {
        usb_hstd_detach_control();
    }
}
/******************************************************************************
 End of function usb_hstd_detach_process
 ******************************************************************************/

/******************************************************************************
Function Name   : usb_hstd_read_lnst
 Description     : Reads LNST register two times, checks whether these values
                 : are equal and returns the value of DVSTCTR register that correspond to
                 : the port specified by 2nd argument.
 Arguments       : uint16_t *buf     : Pointer to the buffer to store DVSTCTR register
Return value    : none
Note            : Please change for your SYSTEM
******************************************************************************/
void usb_hstd_read_lnst(uint16_t *p_buf)
{
    /* WAIT_LOOP */
    do
    {
        p_buf[0] = hw_usb_read_syssts();

        /* 30ms wait */
        usb_cpu_delay_xms((uint16_t)30);
        p_buf[1] = hw_usb_read_syssts();
        if ((p_buf[0] & USB_LNST) == (p_buf[1] & USB_LNST) )
        {
            /* 20ms wait */
            usb_cpu_delay_xms((uint16_t)20);
            p_buf[1] = hw_usb_read_syssts();
        }
    }
    while ((p_buf[0] & USB_LNST) != (p_buf[1] & USB_LNST) );
    p_buf[1] = hw_usb_read_dvstctr();
}
/******************************************************************************
 End of function usb_hstd_read_lnst
 ******************************************************************************/


/******************************************************************************
Function Name   : usb_hstd_attach_process
 Description     : Interrupt disable setting when USB Device is attached and
                 : handles the required interrupt disable setting etc when USB device
                 : is attached.
Arguments       : none
Return value    : none
Note            : Please change for your SYSTEM
******************************************************************************/
void usb_hstd_attach_process(void)
{

    /* OVRCR, ATTCH, DTCH, BCHG interrupt disable */
    usb_hstd_bus_int_disable();

    /* Decide USB Line state (ATTACH) */
    if (USB_LNST_DETACH == usb_hstd_check_attach())
    {
        usb_hstd_detach_control();
    }
    else
    {
        usb_hstd_attach_control();
    }
}
/******************************************************************************
 End of function usb_hstd_attach_process
 ******************************************************************************/


/******************************************************************************
Function Name   : usb_hstd_bus_reset
 Description     : Setting USB register when BUS Reset
Arguments       : none
Return value    : none
******************************************************************************/
void usb_hstd_bus_reset(void)
{
    /* Cautions!!!
     * The DTCH interrupt is detected during the recovery time after the SE0 drive ends.
     * Therefore, even if the DTCH interruption and the ATTCH interrupt are generated while driving SE0,
     * connected detection of the device cannot be done.
     * In this case, the sequence since the USB reset processing is continued
     * as generation of neither cutting nor the reconnection.
     */

    /* SE0 drivet & wait 50ms(reset signal), SOF output & wait 20ms(reset recovery) */
    hw_usb_rmw_dvstctr(USB_USBRST, (USB_USBRST | USB_UACT));
    usb_cpu_delay_xms((uint16_t)50);
    usb_hstd_set_uact();
    /* Wait 10ms or more (USB reset recovery) */
    hw_usb_write_dcpmxps((uint16_t) (USB_DEFPACKET + USB_DEVICE_0));
    usb_cpu_delay_xms((uint16_t)100);   /* 20msec->100msec Support Tera Byte Size Storage Device */
}
/******************************************************************************
 End of function usb_hstd_bus_reset
 ******************************************************************************/


/******************************************************************************
Function Name   : usb_hstd_resume_process
 Description     : Setting USB register when RESUME signal is detected
Arguments       : none
Return value    : none
******************************************************************************/
void usb_hstd_resume_process(void)
{
    /* RESUME signal output, wait 20ms, SOF output, wait 5ms */
    usb_hstd_bchg_disable();
    /* RESUME=1, RWUPE=0 */
    hw_usb_rmw_dvstctr(USB_RESUME, (USB_RESUME | USB_RWUPE));
    /* Wait */
    usb_cpu_delay_xms((uint16_t)20);

    /* USBRST=0, RESUME=0, UACT=1 */
    usb_hstd_set_uact();

    /* Wait */
    usb_cpu_delay_xms((uint16_t)5);
}
/******************************************************************************
 End of function usb_hstd_resume_process
 ******************************************************************************/


/******************************************************************************
Function Name   : usb_hstd_forced_termination
Description     : End of data transfer (IN/OUT)
Arguments       : uint16_t status       ; Transfer status type
Return value    : none
Note            : In the case of timeout status, it does not call back.
******************************************************************************/
void usb_hstd_forced_termination(uint16_t status)
{
    uint16_t    pipe = g_usb_hstd_current_pipe;
    uint16_t    buffer;

    /* PID = NAK */
    /* Set NAK */
    usb_cstd_set_nak(pipe);

    /* Disable Interrupt */
    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(pipe);

    /* Disable Not Ready Interrupt */
    hw_usb_clear_nrdyenb(pipe);

    /* Disable Empty Interrupt */
    hw_usb_clear_bempenb(pipe);

    usb_cstd_clr_transaction(pipe);

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    /* Clear D0FIFO-port */
    buffer = hw_usb_read_fifosel(USB_D0USE);
    if ((buffer & USB_CURPIPE) == pipe )
    {
        /* Stop DMA,FIFO access */
        usb_cstd_dma_stop(USB_D0USE);

        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(USB_PIPE0, USB_D0USE, USB_NULL);
    }

    /* Clear D1FIFO-port */
    buffer = hw_usb_read_fifosel(USB_D1USE);
    if ((buffer & USB_CURPIPE) == pipe )
    {
        /* Stop DMA,FIFO access */
        usb_cstd_dma_stop(USB_D1USE);

        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(USB_PIPE0, USB_D1USE, USB_NULL);
    }
#endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    /* Clear CFIFO-port */
    buffer = hw_usb_read_fifosel(USB_CUSE);
    if ((buffer & USB_CURPIPE) == pipe )
    {
        /* FIFO buffer SPLIT transaction initialized */
        usb_cstd_chg_curpipe(USB_PIPE0, USB_CUSE, USB_NULL);
    }

    /* Do Aclr */
    usb_cstd_do_aclrm(pipe);

    /* Call Back */
    if (USB_NULL != gp_usb_hstd_pipe[pipe])
    {
        /* Transfer information set */
        gp_usb_hstd_pipe[pipe]->tranlen    = g_usb_hstd_data_cnt[pipe];
        gp_usb_hstd_pipe[pipe]->status     = (usb_strct_t)status;
        if (USB_NULL != gp_usb_hstd_pipe[pipe]->complete)
        {
            (gp_usb_hstd_pipe[pipe]->complete)(gp_usb_hstd_pipe[pipe]);
        }

        /* Evacuation pointer */
        gp_usb_hstd_pipe[pipe]    = (usb_hutr_t*)USB_NULL;
    }
}
/******************************************************************************
 End of function usb_hstd_forced_termination
 ******************************************************************************/


/******************************************************************************
Function Name   : usb_hstd_get_devaddx_register
Description     : Get device address configuration register from device address
Arguments       : none
Return value    : uint16_t                  : configuration register
******************************************************************************/
uint16_t usb_hstd_get_devaddx_register(void)
{
    R_BSP_VOLATILE_EVENACCESS uint16_t *p_reg;
    uint16_t return_value;

    if (g_usb_hcd_devaddr > USB_MAXDEVADDR)
    {
        return_value = USB_ERROR;
    }
    else
    {
        p_reg = (uint16_t *) &(USB0.DEVADD0) + g_usb_hcd_devaddr;
        return_value = *p_reg;
    }

    return return_value;
}   /* End of function usb_hstd_get_devaddx_register() */


/******************************************************************************
Function Name   : usb_hstd_set_devaddx_register
Description     : Set device speed
Arguments       : uint8_t    usbspd     : device speed
Return value    : none
******************************************************************************/
void usb_hstd_set_devaddx_register(uint8_t usbspd)
{
    R_BSP_VOLATILE_EVENACCESS uint16_t *p_reg;
    uint16_t    data;

    if (USB_FSCONNECT == usbspd)
    {
        data    = (uint16_t)(USB_FULLSPEED);
    }
    else if (USB_LSCONNECT == usbspd)
    {
        data    = (uint16_t)(USB_LOWSPEED);
    }
    else                                      /* else if (usbspd == USB_NOCONNECT) */
    {
        data    = (uint16_t)(USB_NOTUSED);    /* RTPT is set to port0 when unused. */
    }

    p_reg = (uint16_t *) &(USB0.DEVADD0) + g_usb_hcd_devaddr;

    (*p_reg) &= (~USB_USBSPD);
    (*p_reg) |= data;
}
/******************************************************************************
 End of function usb_hstd_set_devaddx_register
 ******************************************************************************/

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
#endif /*(BSP_CFG_RTOS_USED == 0)*/
/******************************************************************************
 End of file
 ******************************************************************************/
