/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_cdataio.c
 * Version      : 1.44
 * Description  : USB Host and Peripheral low level data I/O code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Move "g_usb_pcdc_serialstate_table[]" from "PCDC API file". and Change Function Name 
 *                           "pcdc_read_complete"->"usb_pcdc_read_complete"
 *                           "pcdc_write_complete"->"usb_pcdc_write_complete"
 *                           "phid_read_complete"->"usb_phid_read_complete"
 *                           "phid_write_complete"->"usb_phid_write_complete"
 *                           "pvndr_read_complete"->"usb_pvnd_read_complete"
 *                           "pnvdr_write_complete"->"usb_pnvdr_write_complete"
 *                           "hcdc_read_complete"->"usb_hcdc_read_complete"
 *                           "hcdc_write_complete"->"usb_hcdc_write_complete"
 *                           "hhid_read_complete"->"usb_hhid_read_complete"
 *                           "hhid_write_complete"->"usb_hhid_write_complete"
 *                           "hvndr_read_complete"->"usb_hvnd_read_complete"
 *                           "hnvdr_write_complete"->"usb_hnvdr_write_complete"
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 16.11.2018 1.24 Supporting RTOS Thread safe
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 30.04.2020 1.31 RX671 is added
 *         : 30.06.2022 1.40 USBX PCDC is supported
 *         : 30.10.2022 1.41 USBX HMSC is supported.
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

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
#include "r_rtos_abstract.h"
#endif /* (BSP_CFG_RTOS_USED != 0) */

#if defined(USB_CFG_HCDC_USE)
#include "r_usb_hcdc_config.h"
#endif /* defined(USB_CFG_HCDC_USE) */

#if defined(USB_CFG_HHID_USE)
#include "r_usb_hhid_config.h"
#endif /* defined(USB_CFG_HHID_USE) */

#if defined(USB_CFG_PCDC_USE)
#include "r_usb_pcdc_if.h"
#endif /* defined(USB_CFG_PCDC_USE) */

#if defined(USB_CFG_PMSC_USE)
#include "r_usb_pmsc_if.h"
#endif /* defined(USB_CFG_PMSC_USE) */

#if defined(USB_CFG_PHID_USE)
#include "r_usb_phid_if.h"
#endif /* defined(USB_CFG_PHID_USE) */

#if defined(USB_CFG_HMSC_USE)
#if (BSP_CFG_RTOS_USED != 5)	/* Azure RTOS */
#include "r_usb_hmsc.h"
#endif /* BSP_CFG_RTOS_USED != 5 */
#endif /* defined(USB_CFG_HMSC_USE) */

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
#include "r_usb_dmac.h"
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

/******************************************************************************
 Macro definitions
 ******************************************************************************/

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
/* Pipe number of USB Host transfer.(Read pipe/Write pipe) */
static const uint8_t g_usb_pipe_host[] =
{
        /* READ pipe *//* WRITE pipe */
        /* IN pipe *//* OUT pipe */
  #if defined(USB_CFG_HCDC_USE)
        USB_CFG_HCDC_BULK_IN, USB_CFG_HCDC_BULK_OUT,    /* HCDC: Address 1 */
        USB_CFG_HCDC_BULK_IN, USB_CFG_HCDC_BULK_OUT,    /* HCDC: Address 2 using Hub */
        USB_CFG_HCDC_BULK_IN2, USB_CFG_HCDC_BULK_OUT2,  /* HCDC: Address 3 using Hub */
        USB_NULL, USB_NULL,
        USB_CFG_HCDC_INT_IN, USB_NULL,                  /* HCDCC: Address 1 */
        USB_CFG_HCDC_INT_IN, USB_NULL,                  /* HCDCC: Address 2 using Hub */
        USB_CFG_HCDC_INT_IN2, USB_NULL,                 /* HCDCC: Address 3 using Hub */
        USB_NULL, USB_NULL,
  #else   /* defined(USB_CFG_HCDC_USE) */
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
  #endif  /* defined(USB_CFG_HCDC_USE) */

  #if defined(USB_CFG_HHID_USE)
        USB_CFG_HHID_INT_IN, USB_CFG_HHID_INT_OUT,      /* HCDC: Address 1 */
        USB_CFG_HHID_INT_IN, USB_CFG_HHID_INT_OUT,      /* HCDC: Address 2 using Hub */
        USB_CFG_HHID_INT_IN2, USB_NULL,                 /* HCDC: Address 3 using Hub */
        USB_CFG_HHID_INT_IN3, USB_NULL,                 /* HCDC: Address 4 using Hub */
  #else   /* defined(USB_CFG_HHID_USE) */
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
  #endif  /* defined(USB_CFG_HHID_USE) */
};
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
static const uint8_t g_usb_pipe_peri[] =
{
    /* OUT pipe */          /* IN pipe */
  #if defined(USB_CFG_PCDC_USE)
    USB_CFG_PCDC_BULK_OUT,  USB_CFG_PCDC_BULK_IN,       /* USB_PCDC */
    USB_NULL,               USB_CFG_PCDC_INT_IN,        /* USB_PCDCC */
   #if defined(USB_CFG_PCDC_2COM_USE)
    USB_CFG_PCDC_BULK_OUT2, USB_CFG_PCDC_BULK_IN2,      /* USB_PCDC2 */
    USB_NULL,               USB_CFG_PCDC_INT_IN2,       /* USB_PCDCC2 */
   #else  /* defined(USB_CFG_PCDC_2COM_USE) */
    USB_NULL,               USB_NULL,
    USB_NULL,               USB_NULL,
   #endif /* defined(USB_CFG_PCDC_2COM_USE) */
  #else   /* defined(USB_CFG_PCDC_USE) */
    USB_NULL,               USB_NULL,
    USB_NULL,               USB_NULL,
    USB_NULL,               USB_NULL,
    USB_NULL,               USB_NULL,
  #endif  /* defined(USB_CFG_PCDC_USE) */

  #if defined(USB_CFG_PHID_USE)
    USB_CFG_PHID_INT_OUT,   USB_CFG_PHID_INT_IN,        /* USB_PHID */
  #else   /* defined(USB_CFG_PHID_USE) */
    USB_NULL,               USB_NULL,
  #endif  /* defined(USB_CFG_PHID_USE) */
};
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
/* USB data transfer */
/* PIPEn Buffer counter */
uint32_t g_usb_pstd_data_cnt[USB_MAX_PIPE_NO + 1u];

/* PIPEn Buffer pointer(8bit) */
uint8_t *gp_usb_pstd_data[USB_MAX_PIPE_NO + 1u];

/* Message pipe */
usb_utr_t *g_p_usb_pstd_pipe[USB_MAX_PIPE_NO + 1u];

#endif  /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */


/* Callback function of USB Read/USB Write */
void (*g_usb_callback[]) (usb_utr_t *, uint16_t, uint16_t) =
{
    /* PCDC, PCDCC */
#if defined(USB_CFG_PCDC_USE)
 #if (BSP_CFG_RTOS_USED == 5)    /* Azure RTOS */
        USB_NULL, USB_NULL,                              /* USB_PCDC  (0) */
        USB_NULL, USB_NULL,                              /* USB_PCDCC (1) */
        USB_NULL, USB_NULL,                              /* USB_PCDC2  (2) */
        USB_NULL, USB_NULL,                              /* USB_PCDCC2 (3) */
 #else  /* #if (BSP_CFG_RTOS_USED == 5) */
        usb_pcdc_read_complete, usb_pcdc_write_complete, /* USB_PCDC  (0) */
        USB_NULL, usb_pcdc_write_complete, /* USB_PCDCC (1) */
        usb_pcdc_read_complete, usb_pcdc_write_complete, /* USB_PCDC  (2) */
        USB_NULL, usb_pcdc_write_complete, /* USB_PCDCC (3) */
 #endif /* #if (BSP_CFG_RTOS_USED == 5) */
#else
        USB_NULL, USB_NULL, /* USB_PCDC  (0) */
        USB_NULL, USB_NULL, /* USB_PCDCC (1) */
        USB_NULL, USB_NULL, /* USB_PCDC  (2) */
        USB_NULL, USB_NULL, /* USB_PCDCC (3) */
#endif

        /* PHID */
#if defined(USB_CFG_PHID_USE)
 #if (BSP_CFG_RTOS_USED != 5)   /* Other than Azure RTOS */
        usb_phid_read_complete, usb_phid_write_complete, /* USB_PHID (4) */
 #else  /* (BSP_CFG_RTOS_USED != 5) */
        USB_NULL, USB_NULL, /* USB_PHID  (4) */
 #endif /* (BSP_CFG_RTOS_USED != 5) */
#else
        USB_NULL, USB_NULL, /* USB_PHID (4) */
#endif

        /* PVND */
        USB_NULL, USB_NULL, /* USB_PVND  (5) */

        USB_NULL, USB_NULL, /* USB_PCDC_PHID(dummy 6) */
        USB_NULL, USB_NULL, /* USB_PCDC_PMSC(dummy 7) */
        USB_NULL, USB_NULL, /* USB_PHID_PMSC(dummy 8) */

        /* HCDC, HCDCC */
#if defined(USB_CFG_HCDC_USE)
 #if (BSP_CFG_RTOS_USED == 5)   /* Azure RTOS */
        USB_NULL, USB_NULL, /* USB_HCDC  (9) */
        USB_NULL, USB_NULL, /* USB_HCDCC (10) */
 #else  /* (BSP_CFG_RTOS_USED == 5) */
        usb_hcdc_read_complete, usb_hcdc_write_complete, /* USB_HCDC  (9) */
        usb_hcdc_read_complete, USB_NULL, /* USB_HCDCC (10) */
 #endif /* (BSP_CFG_RTOS_USED == 5) */
#else
        USB_NULL, USB_NULL, /* USB_HCDC  (9) */
        USB_NULL, USB_NULL, /* USB_HCDCC (10) */
#endif

        /* HHID */
#if defined(USB_CFG_HHID_USE)
        usb_hhid_read_complete, usb_hhid_write_complete, /* USB_HHID  (11) */
#else
        USB_NULL, USB_NULL, /* USB_HHID  (11) */
#endif

        /* HVND */
        USB_NULL, USB_NULL, /* USB_HVND  (12) */

        /* HMSC */
        USB_NULL, USB_NULL, /* USB_HMSC  (13) */

        /* PMSC */
        USB_NULL, USB_NULL, /* USB_PMSC  (14) */
}; /* const void (g_usb_callback[])(usb_utr_t *, uint16_t, uint16_t) */


#if defined(USB_CFG_PCDC_USE)

/* Abstract Control Model Notification - SerialState */
uint8_t g_usb_pcdc_serialstate_table[USB_CDC_SETUP_TBL_BSIZE] =
{
    0xA1,       /* bmRequestType */
    0x20,       /* bNotification:SERIAL_STATE */
    0x00, 0x00, /* wValue:Zero */
    0x00, 0x00, /* wIndex:Interface */
    0x02, 0x00, /* wLength:2 */
    0x00, 0x00, /* Data:UART State bitmap */
};

#endif /* defined(USB_CFG_PCDC_USE) */

usb_pipe_table_t    g_usb_pipe_table[USB_NUM_USBIP][USB_MAXPIPE_NUM+1];
uint16_t            g_usb_cstd_bemp_skip[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1u];

/******************************************************************************
 Renesas Abstracted common data I/O functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_debug_hook
 Description     : Debug hook
 Arguments       : uint16_t error_code          : error code
 Return value    : none
 ******************************************************************************/
void usb_cstd_debug_hook (uint16_t error_code)
{
    /* WAIT_LOOP */
    while (1)
    {
        /* Non */
    }
} /* End of function usb_cstd_debug_hook() */

/******************************************************************************
 Function Name   : usb_ctrl_read
 Description     : Receive process for Control transfer
 Arguments       : usb_ctrl_t *p_ctrl: Control structure for USB API.
                 : uint8_t *buf      : transfer data address
                 : uint32_t size     : transfer length
 Return value    : usb_er_t          : USB_SUCCESS(USB_OK) / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_ctrl_read (usb_ctrl_t *p_ctrl, uint8_t *buf, uint32_t size)
{
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_er_t err;
    usb_utr_t   *p_tran_data;
#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
    usb_utr_t   tran_data;
#endif /* BSP_CFG_RTOS_USED != 0 */

    if (USB_HOST == g_usb_usbmode)
    {
#if (BSP_CFG_RTOS_USED != 0)                 /* Use RTOS */
        p_tran_data = (usb_utr_t *)&tran_data;
#else  /* BSP_CFG_RTOS_USED != 0 */
        p_tran_data = (usb_utr_t *)&g_usb_hdata[p_ctrl->module][USB_PIPE0];
#endif /* BSP_CFG_RTOS_USED != 0 */

        p_tran_data->read_req_len = size;   /* Save Read Request Length */
        p_tran_data->keyword = USB_PIPE0;   /* Pipe No */
        p_tran_data->p_tranadr = buf;       /* Data address */
        p_tran_data->tranlen = size;        /* Data Size */

        /* Callback function */
        p_tran_data->complete = usb_class_request_complete;
        g_usb_ctrl_request[p_ctrl->module][p_ctrl->address].address = p_ctrl->address;
        g_usb_ctrl_request[p_ctrl->module][p_ctrl->address].setup = p_ctrl->setup;

        /* Setup message address set */
        p_tran_data->p_setup =
                (uint16_t *) &g_usb_ctrl_request[p_ctrl->module][p_ctrl->address];
        p_tran_data->segment = USB_TRAN_END;
        p_tran_data->ip = p_ctrl->module;
        p_tran_data->ipp = usb_hstd_get_usb_ip_adr((uint8_t) p_ctrl->module);
        err = usb_hstd_transfer_start(p_tran_data);

        return err;
    }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    if (USB_PERI == g_usb_usbmode)
    {
        if (USB_ON == g_usb_pstd_pipe0_request)
        {
            return USB_QOVR;
        }
        g_usb_pstd_std_request = USB_YES;
        usb_pstd_ctrl_write(size, buf);
    }
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    return USB_SUCCESS;
} /* End of function usb_ctrl_read() */

/******************************************************************************
 Function Name   : usb_ctrl_write
 Description     : Send process for Control transfer
 Arguments       : usb_ctrl_t *p_ctrl: Control structure for USB API.
                 : uint8_t *buf      : transfer data address
                 : uint32_t size     : transfer length
 Return value    : usb_er_t          : USB_SUCCESS(USB_OK) / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_ctrl_write (usb_ctrl_t *p_ctrl, uint8_t *buf, uint32_t size)
{
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_er_t err;
    usb_utr_t   *p_tran_data;
#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
    usb_utr_t   tran_data;
#endif /* BSP_CFG_RTOS_USED != 0 */

    if (USB_HOST == g_usb_usbmode)
    {
#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
        p_tran_data = (usb_utr_t *)&tran_data;
#else  /* (BSP_CFG_RTOS_USED != 0) */
        p_tran_data = (usb_utr_t *)&g_usb_hdata[p_ctrl->module][USB_PIPE0];
#endif /* (BSP_CFG_RTOS_USED != 0) */

        p_tran_data->read_req_len = size;   /* Save Read Request Length */

        p_tran_data->keyword = USB_PIPE0;   /* Pipe No */
        p_tran_data->p_tranadr = buf;       /* Data address */
        p_tran_data->tranlen = size;        /* Data Size */

        /* Callback function */
        p_tran_data->complete = usb_class_request_complete;
        g_usb_ctrl_request[p_ctrl->module][p_ctrl->address].address = p_ctrl->address;
        g_usb_ctrl_request[p_ctrl->module][p_ctrl->address].setup = p_ctrl->setup;

        /* Setup message address set */
        p_tran_data->p_setup =
                (uint16_t *) &g_usb_ctrl_request[p_ctrl->module][p_ctrl->address];
        p_tran_data->segment = USB_TRAN_END;
        p_tran_data->ip = p_ctrl->module;
        p_tran_data->ipp = usb_hstd_get_usb_ip_adr((uint8_t) p_ctrl->module);
        err = usb_hstd_transfer_start(p_tran_data);
        return err;
    }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    usb_ctrl_t ctrl;
#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
    rtos_current_task_id_t  task_id;
#endif /* (BSP_CFG_RTOS_USED != 0) */

    if (USB_PERI == g_usb_usbmode)
    {
        if ((USB_NULL == buf) && (USB_NULL == size))
        {
            if (USB_ACK == p_ctrl->status)
            {
                usb_cstd_set_buf(USB_NULL, (uint16_t) USB_PIPE0);   /* Set BUF */
            }
            else /* USB_STALL */
            {
                usb_pstd_set_stall_pipe0();
            }
            
            ctrl.setup  = p_ctrl->setup;    /* Save setup data. */
            ctrl.module = USB_CFG_USE_USBIP;
            ctrl.size   = 0;
            ctrl.status = USB_ACK;
            ctrl.type   = USB_REQUEST;
#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
            rtos_get_task_id(&task_id);

            ctrl.p_data = (void *)task_id;
#endif /* (BSP_CFG_RTOS_USED != 0) */
            usb_set_event(USB_STS_REQUEST_COMPLETE, &ctrl);

        }
        else
        {
            if (USB_ON == g_usb_pstd_pipe0_request)
            {
                return USB_QOVR;
            }
            g_usb_pstd_std_request = USB_YES;
            usb_pstd_ctrl_read(size, buf);
        }
    }
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    return USB_SUCCESS;
} /* End of function usb_ctrl_write() */

/******************************************************************************
 Function Name   : usb_ctrl_stop
 Description     : Stop of USB Control transfer.
 Arguments       : usb_ctrl_t *p_ctrl: Control structure for USB API.
 Return value    : usb_er_t          : USB_OK / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_ctrl_stop (usb_ctrl_t *p_ctrl)
{
    usb_er_t err;
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t utr;
#endif

    if ((p_ctrl->type) > USB_PVND)
    {
        /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ip = p_ctrl->module;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
        err = usb_hstd_transfer_end(&utr, USB_PIPE0, (uint16_t) USB_DATA_STOP);
#endif
    }
    else
    {
        /* Peripheral only */
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        err = usb_pstd_transfer_end(USB_PIPE0);
#endif
    }
    return err;
} /* End of function usb_ctrl_stop() */

/******************************************************************************
 Function Name   : usb_data_read
 Description     : USB data read processing
 Arguments       : usb_ctrl_t *p_ctrl: Control structure for USB API.
                 : uint8_t *buf      : Transfer data address
                 : uint32_t size     : Transfer length
 Return value    : usb_er_t          : USB_OK / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_data_read (usb_ctrl_t *p_ctrl, uint8_t *buf, uint32_t size)
{
    uint8_t pipe;
    usb_er_t err;
    usb_utr_t   *p_tran_data;
#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
    usb_utr_t   tran_data;
#endif /* BSP_CFG_RTOS_USED != 0 */

    pipe = usb_get_usepipe(p_ctrl, USB_READ);

    if ((p_ctrl->type) > USB_PVND)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
        p_tran_data = (usb_utr_t *)&tran_data;
#else  /* BSP_CFG_RTOS_USED != 0 */
        p_tran_data = (usb_utr_t *)&g_usb_hdata[p_ctrl->module][pipe];
#endif /* BSP_CFG_RTOS_USED != 0 */

        p_tran_data->read_req_len = size;   /* Save Read Request Length */

        p_tran_data->keyword = pipe;        /* Pipe No */
        p_tran_data->p_tranadr = buf;       /* Data address */
        p_tran_data->tranlen = size;        /* Data Size */
        p_tran_data->complete = g_usb_callback[p_ctrl->type * 2]; /* Callback function */
        p_tran_data->segment = USB_TRAN_END;
        p_tran_data->ip = p_ctrl->module;
        p_tran_data->ipp = usb_hstd_get_usb_ip_adr((uint8_t) p_ctrl->module);
        err = usb_hstd_transfer_start(p_tran_data);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
        p_tran_data = (usb_utr_t *)&tran_data;
#else  /* BSP_CFG_RTOS_USED != 0 */
        p_tran_data = (usb_utr_t *)&g_usb_pdata[pipe];
#endif /* BSP_CFG_RTOS_USED != 0 */

        p_tran_data->read_req_len = size;   /* Save Read Request Length */

        p_tran_data->keyword = pipe;        /* Pipe No */
        p_tran_data->p_tranadr = buf;       /* Data address */
        p_tran_data->tranlen = size;        /* Data Size */
        p_tran_data->complete = (usb_cb_t)g_usb_callback[p_ctrl->type*2]; /* Callback function */
        err = usb_pstd_transfer_start(p_tran_data);
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }

    return err;
} /* End of function usb_data_read() */

/******************************************************************************
 Function Name   : usb_data_write
 Description     : USB data write processing
 Arguments       : usb_ctrl_t *p_ctrl: Control structure for USB API.
                 : uint8_t *buf      : Transfer data address
                 : uint32_t size     : Transfer length
 Return value    : usb_er_t          : USB_OK / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_data_write (usb_ctrl_t *p_ctrl, uint8_t *buf, uint32_t size)
{
    uint8_t pipe;
    usb_er_t err;
    usb_utr_t   *p_tran_data;
#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
    usb_utr_t   tran_data;
#endif /* BSP_CFG_RTOS_USED != 0 */

    pipe = usb_get_usepipe(p_ctrl, USB_WRITE);

    if ((p_ctrl->type) > USB_PVND)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)

#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
        p_tran_data = (usb_utr_t *)&tran_data;
#else  /* BSP_CFG_RTOS_USED != 0 */
        p_tran_data = (usb_utr_t *)&g_usb_hdata[p_ctrl->module][pipe];
#endif /* BSP_CFG_RTOS_USED != 0 */

        p_tran_data->keyword = pipe;        /* Pipe No */
        p_tran_data->p_tranadr = buf;       /* Data address */
        p_tran_data->tranlen = size;        /* Data Size */
        p_tran_data->complete = g_usb_callback[(p_ctrl->type * 2) + 1]; /* Callback function */
        p_tran_data->segment = USB_TRAN_END;
        p_tran_data->ip = p_ctrl->module;
        p_tran_data->ipp = usb_hstd_get_usb_ip_adr((uint8_t) p_ctrl->module);
        err = usb_hstd_transfer_start(p_tran_data);
#endif
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

#if (BSP_CFG_RTOS_USED != 0)                /* Use RTOS */
        p_tran_data = (usb_utr_t *)&tran_data;
#else  /* BSP_CFG_RTOS_USED != 0 */
        p_tran_data = (usb_utr_t *)&g_usb_pdata[pipe];
#endif /* BSP_CFG_RTOS_USED != 0 */

  #if defined(USB_CFG_PCDC_USE)
        if (USB_CFG_PCDC_INT_IN != pipe)
        {
            p_tran_data->p_tranadr = buf;   /* Data address */
            p_tran_data->tranlen = size;    /* Data Size */
        }
        else
        {
            g_usb_pcdc_serialstate_table[8] = buf[0];
            g_usb_pcdc_serialstate_table[9] = buf[1];
            p_tran_data->p_tranadr = g_usb_pcdc_serialstate_table; /* Data address */
            p_tran_data->tranlen = 10;      /* Data Size */
        }

  #else   /* defined(USB_CFG_PCDC_USE) */
        p_tran_data->p_tranadr = buf;       /* Data address */
        p_tran_data->tranlen = size;        /* Data Size */
  #endif  /* defined(USB_CFG_PCDC_USE) */
        p_tran_data->keyword = pipe;        /* Pipe No */
        p_tran_data->complete = (usb_cb_t)g_usb_callback[(p_ctrl->type*2)+1]; /* Callback function */
        err = usb_pstd_transfer_start(p_tran_data);
#endif /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
    }

    return err;
} /* End of function usb_data_write() */

/******************************************************************************
 Function Name   : usb_data_stop
 Description     : USB data transfer stop processing
 Arguments       : usb_ctrl_t *p_ctrl: control structure for USB API.
                 : uint16_t type     : Read(0)/Write(1)
 Return value    : usb_er_t          : USB_OK / USB_ERROR.
 ******************************************************************************/
usb_er_t usb_data_stop (usb_ctrl_t *p_ctrl, uint16_t type)
{
    uint8_t pipe;
    usb_er_t err = USB_ERROR;
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    usb_utr_t utr;
#endif

    pipe = usb_get_usepipe(p_ctrl, type);

    if (USB_NULL == pipe)
    {
        return USB_ERROR;
    }

    if ((p_ctrl->type) > USB_PVND)
    {
        /* Host only */
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        utr.ip = p_ctrl->module;
        utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);
        err = usb_hstd_transfer_end(&utr, pipe, (uint16_t) USB_DATA_STOP);
#endif
    }
    else
    {
        /* Peripheral only */
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        err = usb_pstd_transfer_end(pipe);
#endif
    }
    return err;
} /* End of function usb_data_stop() */

/******************************************************************************
 Function Name   : usb_get_usepipe
 Description     : Get pipe number for USB Read/USB Write
 Arguments       : usb_ctrl_t *p_ctrl: Control structure for USB API.
                 : uint8_t dir       : Read(0)/Write(1)
 Return value    : Bitmap of Use pipe
 ******************************************************************************/
uint8_t usb_get_usepipe (usb_ctrl_t *p_ctrl, uint8_t dir)
{
    uint8_t pipe = USB_NULL;
    uint8_t idx;

    if ((p_ctrl->type) > USB_PVND)
    {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
        /* Host */
        idx = (((p_ctrl->type - USB_HCDC) * 8) + ((p_ctrl->address - 1) * 2)) + dir;
        pipe = g_usb_pipe_host[idx];
#endif
    }
    else
    {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
        /* Peripheral */
        idx = (p_ctrl->type * 2) + dir;
        pipe = g_usb_pipe_peri[idx];
#endif
    }
    return pipe;
} /* End of function usb_get_usepipe() */

/******************************************************************************
 End  Of File
 ******************************************************************************/
