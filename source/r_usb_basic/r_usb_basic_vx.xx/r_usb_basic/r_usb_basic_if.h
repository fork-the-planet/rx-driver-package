/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_basic_if.h
 * Version      : 1.44
 * Description  : User macro define file
 *                This file is the macro definition header file which a user can operate.
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 USB Standard request Macro added. and Move Typedef definitions for "r_usb_typedef.h"
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 16.11.2018 1.24 Supporting RTOS Thread safe
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 30.06.2022 1.40 USBX PCDC is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/
#ifndef R_USB_BASIC_IF_H
#define R_USB_BASIC_IF_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "platform.h"
#include "r_usb_basic_define.h"
#include "r_usb_basic_config.h"
#include "r_rtos_abstract.h"

#if (BSP_CFG_RTOS_USED == 4)                    /* Renesas RI600V4 & RI600PX */
#include "itron.h"
#endif /* (BSP_CFG_RTOS_USED == 4) */

/******************************************************************************
 Macro definitions
 ******************************************************************************/
#if defined(USB_CFG_PCDC_2COM_USE)
#define USB_CFG_PCDC_USE /* USB_CFG_DEVICE_CLASS */
#endif /* defined(USB_CFG_PHID_USE) */

#if defined(USB_CFG_PCDC_PHID_USE)
#define USB_CFG_PCDC_USE /* USB_CFG_DEVICE_CLASS */
#define USB_CFG_PHID_USE /* USB_CFG_DEVICE_CLASS */
#endif /* defined(USB_CFG_PHID_USE) */

#if defined(USB_CFG_PCDC_PMSC_USE)
#define USB_CFG_PCDC_USE /* USB_CFG_DEVICE_CLASS */
#define USB_CFG_PMSC_USE /* USB_CFG_DEVICE_CLASS */
#endif /* defined(USB_CFG_PMSC_USE) */

#if defined(USB_CFG_PHID_PMSC_USE)
#define USB_CFG_PHID_USE /* USB_CFG_DEVICE_CLASS */
#define USB_CFG_PMSC_USE /* USB_CFG_DEVICE_CLASS */
#endif /* defined(USB_CFG_PMSC_USE) */

#if defined(USB_CFG_PMSC_REQUEST_USE)
#define USB_CFG_TESTREQUEST_USE /* USB_CFG_DEVICE_CLASS */
#define USB_CFG_PMSC_USE /* USB_CFG_DEVICE_CLASS */
#endif /* defined(USB_CFG_PMSC_REQUEST_USE) */

/* USB Request Type Register */
#define     USB_BREQUEST                        (0xFF00u)   /* b15-8 */

/* USB Standard request */
#define     USB_GET_STATUS                      (0x0000u)
#define     USB_CLEAR_FEATURE                   (0x0100u)
#define     USB_REQRESERVED                     (0x0200u)
#define     USB_SET_FEATURE                     (0x0300u)
#define     USB_REQRESERVED1                    (0x0400u)
#define     USB_SET_ADDRESS                     (0x0500u)
#define     USB_GET_DESCRIPTOR                  (0x0600u)
#define     USB_SET_DESCRIPTOR                  (0x0700u)
#define     USB_GET_CONFIGURATION               (0x0800u)
#define     USB_SET_CONFIGURATION               (0x0900u)
#define     USB_GET_INTERFACE                   (0x0A00u)
#define     USB_SET_INTERFACE                   (0x0B00u)
#define     USB_SYNCH_FRAME                     (0x0C00u)

/* USB_BMREQUESTTYPEDIR 0x0080u(b7) */
#define USB_HOST_TO_DEV                         (0x0000u)
#define USB_DEV_TO_HOST                         (0x0080u)

/* USB_BMREQUESTTYPETYPE    0x0060u(b6-5) */
#define USB_STANDARD                            (0x0000u)
#define USB_CLASS                               (0x0020u)
#define USB_VENDOR                              (0x0040u)

/* USB_BMREQUESTTYPERECIP   0x001Fu(b4-0) */
#define USB_DEVICE                              (0x0000u)
#define USB_INTERFACE                           (0x0001u)
#define USB_ENDPOINT                            (0x0002u)
#define USB_OTHER                               (0x0003u)

#define USB_NULL                                (0x0u)

#define USB_IP0                                 (0)         /* USB0 module */
#define USB_IP1                                 (1)         /* USB1 module */

/* USB pipe number */
#define USB_PIPE0                               (0x0u)
#define USB_PIPE1                               (0x1u)
#define USB_PIPE2                               (0x2u)
#define USB_PIPE3                               (0x3u)
#define USB_PIPE4                               (0x4u)
#define USB_PIPE5                               (0x5u)
#define USB_PIPE6                               (0x6u)
#define USB_PIPE7                               (0x7u)
#define USB_PIPE8                               (0x8u)
#define USB_PIPE9                               (0x9u)

#define USB_EP0                                 (0x0u)
#define USB_EP1                                 (0x1u)
#define USB_EP2                                 (0x2u)
#define USB_EP3                                 (0x3u)
#define USB_EP4                                 (0x4u)
#define USB_EP5                                 (0x5u)
#define USB_EP6                                 (0x6u)
#define USB_EP7                                 (0x7u)
#define USB_EP8                                 (0x8u)
#define USB_EP9                                 (0x9u)
#define USB_EP10                                (0xAu)
#define USB_EP11                                (0xBu)
#define USB_EP12                                (0xCu)
#define USB_EP13                                (0xDu)
#define USB_EP14                                (0xEu)
#define USB_EP15                                (0xFu)

/* Descriptor type  Define */
#define USB_DT_DEVICE                           (0x01u)   /* Configuration Descriptor */
#define USB_DT_CONFIGURATION                    (0x02u)   /* Configuration Descriptor */
#define USB_DT_STRING                           (0x03u)   /* Configuration Descriptor */
#define USB_DT_INTERFACE                        (0x04u)   /* Interface Descriptor */
#define USB_DT_ENDPOINT                         (0x05u)   /* Endpoint Descriptor */
#define USB_DT_DEVICE_QUALIFIER                 (0x06u)   /* Device Qualifier Descriptor */
#define USB_DT_OTHER_SPEED_CONF                 (0x07u)   /* Other Speed Configuration Descriptor */
#define USB_DT_INTERFACE_POWER                  (0x08u)   /* Interface Power Descriptor */
#define USB_DT_OTGDESCRIPTOR                    (0x09u)   /* OTG Descriptor */
#define USB_DT_HUBDESCRIPTOR                    (0x29u)   /* HUB descriptor */

/* Interface class Define */
#define USB_IFCLS_NOT                           (0x00u)   /* Un corresponding Class */
#define USB_IFCLS_AUD                           (0x01u)   /* Audio Class */
#define USB_IFCLS_CDC                           (0x02u)   /* CDC Class */
#define USB_IFCLS_CDCC                          (0x02u)   /* CDC-Control Class */
#define USB_IFCLS_HID                           (0x03u)   /* HID Class */
#define USB_IFCLS_PHY                           (0x05u)   /* Physical Class */
#define USB_IFCLS_IMG                           (0x06u)   /* Image Class */
#define USB_IFCLS_PRN                           (0x07u)   /* Printer Class */
#define USB_IFCLS_MAS                           (0x08u)   /* Mass Storage Class */
#define USB_IFCLS_HUB                           (0x09u)   /* HUB Class */
#define USB_IFCLS_CDCD                          (0x0Au)   /* CDC-Data Class */
#define USB_IFCLS_CHIP                          (0x0Bu)   /* Chip/Smart Card Class */
#define USB_IFCLS_CNT                           (0x0Cu)   /* Content-Security Class */
#define USB_IFCLS_VID                           (0x0Du)   /* Video Class */
#define USB_IFCLS_DIAG                          (0xDCu)   /* Diagnostic Device */
#define USB_IFCLS_WIRE                          (0xE0u)   /* Wireless Controller */
#define USB_IFCLS_APL                           (0xFEu)   /* Application-Specific */
#define USB_IFCLS_VEN                           (0xFFu)   /* Vendor-Specific Class */

/* Endpoint Descriptor  Define */
#define USB_EP_IN                               (0x80u)   /* In Endpoint */
#define USB_EP_OUT                              (0x00u)   /* Out Endpoint */
#define USB_EP_ISO                              (0x01u)   /* Isochronous Transfer */
#define USB_EP_BULK                             (0x02u)   /* Bulk Transfer */
#define USB_EP_INT                              (0x03u)   /* Interrupt Transfer */

/* Configuration descriptor bit define */
#define USB_CF_RESERVED                         (0x80u)   /* Reserved(set to 1) */
#define USB_CF_SELFP                            (0x40u)   /* Self Powered */
#define USB_CF_BUSP                             (0x00u)   /* Bus Powered */
#define USB_CF_RWUPON                           (0x20u)   /* Remote Wake up ON */
#define USB_CF_RWUPOFF                          (0x00u)   /* Remote Wake up OFF */

 /* Descriptor length Define */
#define USB_DD_BLENGTH                          (18u)     /* Device Descriptor Length */
#define USB_CD_BLENGTH                          (9u)      /* Configuration Descriptor Length */
#define USB_ID_BLENGTH                          (9u)      /* Interface Descriptor Length */
#define USB_ED_BLENGTH                          (7u)      /* Endpoint Descriptor Length */

/*****************************************************************************
 Typedef definitions
 ******************************************************************************/
typedef enum usb_err
{
    USB_SUCCESS = 0,            /* Successful */
    USB_ERR_PARA,               /* Invalid parameter */
    USB_ERR_BUSY,               /* API is busy now */
    USB_ERR_NOT_OPEN,           /* Device is not opened */
    USB_ERR_NOT_SUSPEND,        /* Device is not the suspend state */
    USB_ERR_OVER,               /* Received data size over */
    USB_ERR_SHORT,              /* Received data size short */
    USB_ERR_NG,                 /* Operation failed */
    USB_ERR_TMOUT,              /* Timeout */
} usb_err_t;

typedef struct usb_descriptor
{
    uint8_t *p_device;          /* Pointer to the device descriptor */
    uint8_t *p_config_f;        /* Pointer to the configuration descriptor for Full-speed */
    uint8_t *p_config_h;        /* Pointer to the configuration descriptor for Hi-speed */
    uint8_t *p_qualifier;       /* Pointer to the qualifier descriptor */
    uint8_t **p_string;         /* Pointer to the string descriptor table */
    uint8_t num_string;         /* Num entry String Descriptor */
} usb_descriptor_t;

typedef struct usb_cfg
{
    uint8_t             usb_mode;   /* USB_HOST/USB_PERI */
    uint8_t             usb_speed;  /* USB speed (USB_HS/USB_FS/USB_LS) */
    usb_descriptor_t    *p_usb_reg; /* Pointer to the usb_decriptor_t structure area */
} usb_cfg_t;

typedef struct usb_setup
{
    uint16_t        type;       /* USB standard/class request type */
    uint16_t        value;      /* Request value */
    uint16_t        index;      /* Request index */
    uint16_t        length;     /* Request length */
} usb_setup_t;

typedef struct usb_ctrl
{
#if (BSP_CFG_RTOS_USED == 4)    /* Renesas RI600V4 & RI600PX */
    T_MSG           msghead;    /* Message Header */
#endif /* (BSP_CFG_RTOS_USED == 4) */
    uint8_t         module;     /* USB module number (USB_IP0/USB_IP1) */
    uint8_t         address;    /* USB device address */
    uint8_t         pipe;       /* USB pipe number */
    uint8_t         type;       /* USB device class etc */
    uint8_t         status;     /* USB device state etc */
#if (BSP_CFG_RTOS_USED != 0)    /* Use RTOS */
    uint8_t         event;      /* USB event */
#endif /*(BSP_CFG_RTOS_USED != 0)*/
    uint32_t        size;       /* Read data size */
    usb_setup_t     setup;      /* usb_setup_t structure area */
#if (BSP_CFG_RTOS_USED != 0)    /* Use RTOS */
    void            *p_data;    /* Other information */
#endif /*(BSP_CFG_RTOS_USED != 0)*/
} usb_ctrl_t;

typedef struct usb_pipe
{
    uint8_t         ep;         /* Endpoint number */
    uint8_t         type;       /* Transfer type (USB_BULK/USB_INT etc) */
    uint16_t        mxps;       /* Max packet size */
} usb_pipe_t;

typedef struct usb_info
{
    uint8_t         type;       /* USB device class type */
    uint8_t         speed;      /* USB speed */
    uint8_t         status;     /* USB device status */
    uint8_t         port;       /* Battery charging information */
} usb_info_t;

typedef enum usb_ct_status
{
    USB_CT_ATTACH,              /* Device Attach Detection */
    USB_CT_DETACH,              /* Device Detach Detection */
    USB_CT_TPL,                 /* TPL device connect */
    USB_CT_NOTTPL,              /* Not TPL device connect */
    USB_CT_HUB,                 /* USB Hub connect */
    USB_CT_OVRC,                /* Over current */
    USB_CT_NORES,               /* Response Time out for Control Read Transfer */
    USB_CT_SETUP_ERR,           /* Setup Transaction Error */
} usb_ct_status_t;

typedef struct usb_compliance
{
    usb_ct_status_t status;     /* USB Status */
    uint16_t        vid;        /* Vendor ID  */
    uint16_t        pid;        /* Product ID */
} usb_compliance_t;


/* USB speed type */
typedef enum usb_speed
{
    USB_LS = 0, USB_FS, USB_HS,
} usb_speed_t;

/* USB request result */
typedef enum usb_setup_status
{
    USB_ACK = 0, USB_STALL,
} usb_setup_status_t;

/* USB driver status */
typedef enum usb_status
{
    USB_STS_POWERED = 0,
    USB_STS_DEFAULT,
    USB_STS_ADDRESS,
    USB_STS_CONFIGURED,
    USB_STS_SUSPEND,
    USB_STS_RESUME,
    USB_STS_DETACH,
    USB_STS_REQUEST,
    USB_STS_REQUEST_COMPLETE,
    USB_STS_READ_COMPLETE,
    USB_STS_WRITE_COMPLETE,
    USB_STS_BC,
    USB_STS_OVERCURRENT,
    USB_STS_NOT_SUPPORT,
    USB_STS_NONE,
    USB_STS_MSC_CMD_COMPLETE,
} usb_status_t;

/* USB class type */
typedef enum usb_class
{
    USB_PCDC = 0, USB_PCDCC, USB_PCDC2, USB_PCDCC2, USB_PHID, USB_PVND,

    USB_PCDC_PHID, USB_PCDC_PMSC, USB_PHID_PMSC,

    USB_HCDC, USB_HCDCC, USB_HHID, USB_HVND,

    USB_HMSC, USB_PMSC, USB_REQUEST
} usb_class_t;

/* USB battery charging type */
typedef enum usb_bcport
{
    USB_SDP = 0, USB_CDP, USB_DCP,
} usb_bcport_t;

/* USB status */
typedef enum usb_onoff
{
    USB_OFF = 0, USB_ON,
} usb_onoff_t;

/* USB read / write type */
typedef enum usb_rw
{
    USB_READ = 0, USB_WRITE,
} usb_rw_t;

/* USB transfer type */
typedef enum usb_transfer
{
    USB_BULK = 0, USB_INT, USB_ISO,
} usb_transfer_t;
#if (BSP_CFG_RTOS_USED != 0)
typedef void (usb_callback_t)(usb_ctrl_t *, rtos_current_task_id_t, uint8_t);
#endif /* (BSP_CFG_RTOS_USED != 0) */

/******************************************************************************
 Export global functions
 ******************************************************************************/
usb_err_t       R_USB_Open (usb_ctrl_t *p_ctrl, usb_cfg_t *p_cfg);
usb_err_t       R_USB_Close (usb_ctrl_t *p_ctrl);
usb_err_t       R_USB_Read (usb_ctrl_t *p_ctrl, uint8_t *p_buf, uint32_t size);
usb_err_t       R_USB_Write (usb_ctrl_t *p_ctrl, uint8_t *p_buf, uint32_t size);
usb_err_t       R_USB_Stop (usb_ctrl_t *p_ctrl, uint16_t type);
usb_err_t       R_USB_Suspend (usb_ctrl_t *p_ctrl);
usb_err_t       R_USB_Resume (usb_ctrl_t *p_ctrl);
usb_err_t       R_USB_VbusSetting (usb_ctrl_t *p_ctrl, uint16_t state);
usb_err_t       R_USB_GetInformation (usb_ctrl_t *p_ctrl, usb_info_t *p_info);
usb_err_t       R_USB_PipeRead (usb_ctrl_t *p_ctrl, uint8_t *p_buf, uint32_t size);
usb_err_t       R_USB_PipeWrite (usb_ctrl_t *p_ctrl, uint8_t *p_buf, uint32_t size);
usb_err_t       R_USB_PipeStop (usb_ctrl_t *p_ctrl);
usb_err_t       R_USB_GetUsePipe (usb_ctrl_t *p_ctrl, uint16_t *p_pipe);
usb_err_t       R_USB_GetPipeInfo (usb_ctrl_t *p_ctrl, usb_pipe_t *p_info);
#if (BSP_CFG_RTOS_USED == 0)        /* Non-OS */
usb_status_t    R_USB_GetEvent (usb_ctrl_t *p_ctrl);
#endif /*(BSP_CFG_RTOS_USED == 0)*/
uint32_t        R_USB_GetVersion (void);
#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
void            R_USB_Callback (usb_callback_t *);
#endif /*(BSP_CFG_RTOS_USED == 0)*/
usb_err_t       R_USB_PullUp(uint8_t state);

#endif /* R_USB_BASIC_IF_H */

/***********************************************************************************************************************
End  Of File
***********************************************************************************************************************/
