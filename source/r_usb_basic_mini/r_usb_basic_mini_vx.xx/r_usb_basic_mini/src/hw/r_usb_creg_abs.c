/*
* Copyright (c) 2018(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_creg_abs.c
 * Description  : Call USB register access function
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 30.11.2018 1.00 First Release
 *         : 31.05.2019 1.11 Added support for GNUC and ICCRX.
 *         : 30.06.2020 1.20 Added support for RTOS.
 *         : 20.03.2025 1.31 Changed the disclaimer.
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_mini_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"
#include "r_usb_dmac.h"

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
#include "r_usb_cstd_rtos.h"
#endif /* (BSP_CFG_RTOS_USED != 0) */

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_get_maxpacket_size
 Description     : Fetch MaxPacketSize of the specified pipe.
 Arguments       : uint16_t pipe  : Pipe number.
 Return value    : uint16_t MaxPacketSize
 ******************************************************************************/
uint16_t usb_cstd_get_maxpacket_size (uint16_t pipe)
{
    uint16_t size;
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL; /* Error */
    }

    if (USB_PIPE0 == pipe)
    {
        buffer = hw_usb_read_dcpmaxp();

    /* Max Packet Size */
        size = (uint16_t) (buffer & USB_DCP_MXPS);
    }
    else
    {
        /* Pipe select */
        hw_usb_write_pipesel(pipe);

        buffer = hw_usb_read_pipemaxp();

        /* Max Packet Size */
        size = (uint16_t) (buffer & USB_PIPE_MXPS);
    }

    return size;
}
/******************************************************************************
 End of function usb_cstd_get_maxpacket_size
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_set_pipe_config
 Description     : Initialization of registers associated with specified pipe.
 Arguments       : uint16_t pipe     : Pipe Number
 Return value    : none
 ******************************************************************************/
void usb_cstd_set_pipe_config (uint16_t pipe)
{
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint16_t    useport = USB_CUSE;
#endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
        if (USB_NULL != gp_usb_pstd_pipe[pipe])
        {
            rtos_release_fixed_memory(&g_rtos_usb_mpf_id, (void *)gp_usb_pstd_pipe[pipe]);
        }

#endif  /* (BSP_CFG_RTOS_USED != 0) */

    gp_usb_pstd_pipe[pipe] = (usb_putr_t *)USB_NULL;
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
    if (USB_NULL != gp_usb_hstd_pipe[pipe])
    {
        rtos_release_fixed_memory(&g_rtos_usb_mpf_id, (void *)gp_usb_hstd_pipe[pipe]);
    }

    gp_usb_hstd_pipe[pipe] = (usb_utr_t*) USB_NULL;
#else   /* (BSP_CFG_RTOS_USED != 0) */
    g_usb_hstd_current_pipe   = pipe;
    gp_usb_hstd_pipe[pipe] = (usb_hutr_t*)USB_NULL;
#endif  /* (BSP_CFG_RTOS_USED != 0) */
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    /* Interrupt Disable */
    /* Ready         Int Disable */
    hw_usb_clear_brdyenb(pipe);

    /* NotReady      Int Disable */
    hw_usb_clear_nrdyenb(pipe);

    /* Empty/SizeErr Int Disable */
    hw_usb_clear_bempenb(pipe);

    /* PID=NAK & clear STALL */
    usb_cstd_clr_stall(pipe);

    /* PIPE Configuration */
    hw_usb_write_pipesel(pipe);

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    useport = usb_cstd_pipe_to_fport(pipe);
    if ((USB_D0USE == useport) || (USB_D1USE == useport))
    {
        g_usb_cstd_pipe_tbl[pipe].pipe_cfg |= USB_BFREON;
    }
#endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    hw_usb_write_pipecfg(g_usb_cstd_pipe_tbl[pipe].pipe_cfg);
    hw_usb_write_pipemaxp(g_usb_cstd_pipe_tbl[pipe].pipe_maxp);
#if (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST
    if (USB_HOST == g_usb_cstd_usb_mode)
    {
        hw_usb_write_pipeperi(g_usb_cstd_pipe_tbl[pipe].pipe_peri);
    }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    /* FIFO buffer initialized */
    hw_usb_write_pipesel(USB_PIPE0);

    /* SQCLR */
    hw_usb_set_sqclr(pipe);

    /* ACLRM */
    usb_cstd_do_aclrm(pipe);

    /* Interrupt status clear */
    /* Ready         Int Clear */
    hw_usb_clear_sts_brdy(pipe);

    /* NotReady      Int Clear */
    hw_usb_clear_status_nrdy(pipe);

    /* Empty/SizeErr Int Clear */
    hw_usb_clear_status_bemp(pipe);
}
/******************************************************************************
 End of function usb_cstd_set_pipe_config
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_clr_pipe_config
 Description     : Clear specified pipe configuration register.
 Arguments       : uint16_t pipe_no  : pipe number
 Return value    : none
 ******************************************************************************/
void usb_cstd_clr_pipe_config (uint16_t pipe_no)
{
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint16_t    buf;
#endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
        if (USB_NULL != gp_usb_pstd_pipe[pipe_no])
        {
            rtos_release_fixed_memory(&g_rtos_usb_mpf_id, (void *)gp_usb_pstd_pipe[pipe_no]);
        }

#endif  /* (BSP_CFG_RTOS_USED != 0) */

    gp_usb_pstd_pipe[pipe_no] = (usb_putr_t *)USB_NULL;

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
    if (USB_NULL != gp_usb_hstd_pipe[pipe_no])
    {
        rtos_release_fixed_memory(&g_rtos_usb_mpf_id, (void *)gp_usb_hstd_pipe[pipe_no]);
    }

    gp_usb_hstd_pipe[pipe_no] = (usb_utr_t*) USB_NULL;
#else   /* (BSP_CFG_RTOS_USED != 0) */
    gp_usb_hstd_pipe[pipe_no] = (usb_hutr_t*)USB_NULL;
#endif  /* (BSP_CFG_RTOS_USED != 0) */

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    /* PID=NAK & clear STALL */
    usb_cstd_clr_stall(pipe_no);

    /* Interrupt Disable */
    /* Ready         Int Disable */
    hw_usb_clear_brdyenb(pipe_no);

    /* NotReady      Int Disable */
    hw_usb_clear_nrdyenb(pipe_no);

    /* Empty/SizeErr Int Disable */
    hw_usb_clear_bempenb(pipe_no);

    /* PIPE Configuration */
    usb_cstd_chg_curpipe(USB_PIPE0, USB_CUSE, USB_NULL);

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    /* Clear D0FIFO-port */
    buf = hw_usb_read_fifosel(USB_D0USE);
    if ((buf & USB_CURPIPE) == pipe_no )
    {
        usb_cstd_dma_stop(USB_D0USE);

        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(USB_PIPE0, USB_D0USE, USB_NULL);

    }

    /* Clear D1FIFO-port */
    buf = hw_usb_read_fifosel(USB_D1USE);
    if ((buf & USB_CURPIPE) == pipe_no )
    {
        usb_cstd_dma_stop(USB_D1USE);

        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(USB_PIPE0, USB_D1USE, USB_NULL);
    }

#endif /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    hw_usb_write_pipesel(pipe_no);
    hw_usb_write_pipecfg(0);

    hw_usb_write_pipemaxp(0);
    hw_usb_write_pipeperi(0);
    hw_usb_write_pipesel(USB_PIPE0);

    /* FIFO buffer DATA-PID initialized */
    /* SQCLR */
    hw_usb_set_sqclr(pipe_no);

    /* ACLRM */
    usb_cstd_do_aclrm(pipe_no);

    usb_cstd_clr_transaction(pipe_no);

    /* Interrupt status clear */
    /* Ready         Int Clear */
    hw_usb_clear_sts_brdy(pipe_no);

    /* NotReady      Int Clear */
    hw_usb_clear_status_nrdy(pipe_no);

    /* Empty/SizeErr Int Clear */
    hw_usb_clear_status_bemp(pipe_no);
}
/******************************************************************************
 End of function usb_cstd_clr_pipe_config
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_set_nak
 Description     : Set up to NAK the specified pipe.
 Arguments       : uint16_t pipe     : Pipe Number
 Return value    : none
 ******************************************************************************/
void usb_cstd_set_nak (uint16_t pipe)
{
    uint16_t buf;
    uint16_t n;

    /* Set NAK */
    hw_usb_clear_pid(pipe, (uint16_t) USB_PID_BUF);

    /* The state of PBUSY continues while transmitting the packet when it is a detach. */
    /* 1ms comes off when leaving because the packet duration might not exceed 1ms.  */
    /* Whether it is PBUSY release or 1ms passage can be judged. */
    /* WAIT_LOOP */
    for (n = 0; n < 0xFFFFu; ++n)
    {
        /* PIPE control reg read */
        buf = hw_usb_read_pipectr(pipe);
        if (0 == (uint16_t) (buf & USB_PBUSY))
        {
            n = 0xFFFEu;
        }
    }
}
/******************************************************************************
 End of function usb_cstd_set_nak
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_is_set_frdy
 Description     : Changes the specified FIFO port by the specified pipe.
 Arguments       : uint16_t pipe     : Pipe Number
                 : uint16_t fifosel  : FIFO select
                 : uint16_t isel     : ISEL bit status
 Return value    : FRDY status
 ******************************************************************************/
uint16_t usb_cstd_is_set_frdy (uint16_t pipe, uint16_t fifosel, uint16_t isel)
{
    uint16_t read_reg;
    uint16_t i;

    /* Changes the FIFO port by the pipe. */
    usb_cstd_chg_curpipe(pipe, fifosel, isel);

    /* WAIT_LOOP */
    for (i = 0; i < 4000; i++)
    {
        read_reg = hw_usb_read_fifoctr(fifosel);

        if (USB_FRDY == (uint16_t) (read_reg & USB_FRDY))
        {
            return (read_reg);
        }

        /* Caution!!!
         * Depending on the external bus speed of CPU, you may need to wait
         * for 100ns here.
         * For details, please look at the data sheet.   */
        /***** The example of reference. *****/
        read_reg = hw_usb_read_syscfg();
        read_reg = hw_usb_read_syssts();

        /*************************************/
    }
    return (USB_FIFOERROR);
}
/******************************************************************************
 End of function usb_cstd_is_set_frdy
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_chg_curpipe
 Description     : Switch FIFO and pipe number.
 Arguments       : uint16_t pipe     : Pipe number.
                 : uint16_t fifosel  : FIFO selected (CPU, D0, D1..)
                 : uint16_t isel     : CFIFO Port Access Direction.(Pipe1 to 9:Set to 0)
 Return value    : none
 ******************************************************************************/
void usb_cstd_chg_curpipe (uint16_t pipe, uint16_t fifosel, uint16_t isel)
{
    uint16_t reg_fifosel;

    /* Select FIFO */
    switch (fifosel)
    {
        /* CFIFO use */
        case USB_CUSE :
            /* CURPIPE=pipeX */
            hw_usb_rmw_fifosel(USB_CUSE, ((USB_RCNT | isel) | pipe), ((USB_RCNT | USB_ISEL) | USB_CURPIPE));
            /* WAIT_LOOP */
            do
            {
                reg_fifosel = hw_usb_read_fifosel(USB_CUSE);
            }
            while ((reg_fifosel & (uint16_t) (USB_ISEL | USB_CURPIPE)) != (uint16_t) (isel | pipe));
        break;

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        /* D0FIFO  */
        case USB_D0USE:
        /* D1FIFO  */
        case USB_D1USE:
            /* CURPIPE=pipeX */
            hw_usb_set_curpipe (fifosel, USB_PIPE0);
            /* WAIT_LOOP */
            do
            {
                reg_fifosel = hw_usb_read_fifosel(fifosel);
            }
            while ((reg_fifosel & (uint16_t)(USB_CURPIPE)) != USB_PIPE0 );

            hw_usb_set_curpipe (fifosel, pipe);

            /* WAIT_LOOP */
            do
            {
                reg_fifosel = hw_usb_read_fifosel(fifosel);
            }
            while ((uint16_t)(reg_fifosel & USB_CURPIPE) != pipe);
        break;

#endif    /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        default :
        break;
    }
}
/******************************************************************************
 End of function usb_cstd_chg_curpipe
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_set_transaction
 Description     : Set specified Pipe Transaction Counter Register.
 Arguments       : uint16_t pipe   : Pipe number
                 : uint16_t trncnt   : Transaction counter
 Return value    : none
 ******************************************************************************/
void usb_cstd_set_transaction (uint16_t pipe, uint16_t trncnt)
{
    hw_usb_set_trclr(pipe);
    hw_usb_write_pipetrn(pipe, trncnt);
    hw_usb_set_trenb(pipe);
}
/******************************************************************************
 End of function usb_cstd_set_transaction
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_clr_transaction
 Description     : Clear specified Pipe Transaction Counter Register.
 Arguments       : uint16_t pipe   : Pipe Number
 Return value    : none
 ******************************************************************************/
void usb_cstd_clr_transaction (uint16_t pipe)
{
    hw_usb_clear_trenb(pipe);
    hw_usb_set_trclr(pipe);
}
/******************************************************************************
 End of function usb_cstd_clr_transaction
 ******************************************************************************/

/******************************************************************************
 End of file
 ******************************************************************************/

