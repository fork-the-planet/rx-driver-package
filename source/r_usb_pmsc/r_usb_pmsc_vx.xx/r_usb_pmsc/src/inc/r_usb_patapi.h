/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_patapi.h
 * Version      : 1.44
 * Description  : USB APAPI Define Header
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 MEDIA_ADDRESS,USB_MEDIA_TYPE_PP is deleted.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 31.05.2019 1.26 Added support for GNUC and ICCRX.
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/

#ifndef R_USB_PATAPI_H
#define R_USB_PATAPI_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
/* Storage sector size */
#define USB_ATAPI_BLOCK_UNIT    (0x0200ul)

/* Operation when responding with a short packet to a command */
/*  0: Respond to 0x00 with CSW with setting PIPE to STALL
    1: Respond to 0x00 with CSW without setting PIPE to STALL
 */
#define USB_ATAPI_SHT_RESPONSE          1


/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/


/* ATAPI command */
typedef enum
{
    /*--- SFF-8070i command define ---*/
    USB_ATAPI_TEST_UNIT_READY       = 0x00u,
    USB_ATAPI_REQUEST_SENSE         = 0x03u,
    USB_ATAPI_FORMAT_UNIT           = 0x04u,
    USB_ATAPI_INQUIRY               = 0x12u,
    USB_ATAPI_MODE_SELECT6          = 0x15u,
    USB_ATAPI_MODE_SENSE6           = 0x1Au,
    USB_ATAPI_START_STOP_UNIT       = 0x1Bu,
    USB_ATAPI_PREVENT_ALLOW         = 0x1Eu,
    USB_ATAPI_READ_FORMAT_CAPACITY  = 0x23u,
    USB_ATAPI_READ_CAPACITY         = 0x25u,
    USB_ATAPI_READ10                = 0x28u,
    USB_ATAPI_WRITE10               = 0x2Au,
    USB_ATAPI_SEEK                  = 0x2Bu,
    USB_ATAPI_WRITE_AND_VERIFY      = 0x2Eu,
    USB_ATAPI_VERIFY10              = 0x2Fu,
    USB_ATAPI_MODE_SELECT10         = 0x55u,
    USB_ATAPI_MODE_SENSE10          = 0x5Au,
} usb_atapi_t;

/* ATAPI error code */
typedef enum
{
    USB_ATAPI_SUCCESS               = 0x11,

    /* Command receive events */
    USB_ATAPI_NO_DATA               = 0x21,
    USB_ATAPI_A_SND_DATA            = 0x22,
    USB_ATAPI_A_RCV_DATA            = 0x23,
    USB_ATAPI_SND_DATAS             = 0x24,
    USB_ATAPI_RCV_DATAS             = 0x25,
    USB_ATAPI_NOT_SUPPORT           = 0x26,

    /* Complete events */
    USB_ATAPI_CMD_CONTINUE          = 0x31,
    USB_ATAPI_CMD_COMPLETE          = 0x32,
    USB_ATAPI_CMD_FAILED            = 0x33,

    /* ATAPI Start events */
    USB_ATAPI_READY                 = 0x41,

    /* Respond error */
    USB_ATAPI_ERROR                 = 0x51,

    /*** ERR CODE ***/
    USB_ATAPI_ERR_CODE_SEPARATER    = 0x100,
    USB_ATAPI_ERR_INVAL             = 0x61

}usb_atapi_result_t;

/* ATAPI command size */
typedef enum
{
    USB_ATAPI_REQUEST_SENSE_SIZE            = 18,
    USB_ATAPI_INQUIRY_SIZE                  = 36,
    USB_ATAPI_READ_FORMAT_CAPACITY_SIZE     = 20,
    USB_ATAPI_READ_CAPACITY_SIZE            = 8,
    USB_ATAPI_MODE_SENSE10_MODE_PARAM_SIZE  = 8,
    USB_ATAPI_MODE_SENSE10_ERR_RCVR_P_SIZE  = 20,
    USB_ATAPI_MODE_SENSE10_CASHING_P_SIZE   = 20,
    USB_ATAPI_MODE_SENSE10_CAP_P_SIZE       = 20,
    USB_ATAPI_MODE_SENSE10_OP_CMD_SIZE      = 16,
    USB_ATAPI_MODE_SENSE10_ALL_P_SIZE       = 44,
    USB_ATAPI_MODE_SENSE10_P_CODE_ERR_SIZE  = 8,
    USB_ATAPI_DATA_SIZE_0                   = 0
} usb_atapi_command_size_t;

/* INQUIRY data format */
typedef enum
{
    USB_ATAPI_INQUIRY_VENDOR_SIZE   = 8,
    USB_ATAPI_INQUIRY_PRODUCT_SIZE  = 16,
    USB_ATAPI_INQUIRY_REVISION_SIZE = 4,
} usb_atapi_inquiry_data_format_size_t;

/* Callback Message format define. */
typedef struct
{
    uint32_t    ar_rst;
    uint32_t    ul_size;
} usb_pmsc_cbm_t;

/* Command Descriptor Block format define. */
R_BSP_PRAGMA_UNPACK
typedef struct
{
    union {
        uint8_t    BYTE;
        /* CPU bit order rigth */
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_2(
            uint8_t             b_lun      :3,  /* Logical Unit Number */
            uint8_t             b_reserved :5
        )BIT;
    };
} usb_pmsc_lun_t;
R_BSP_PRAGMA_PACKOPTION

typedef struct
{
    uint8_t             uc_opcode;
    usb_pmsc_lun_t      s_lun;
    uint8_t             uc_data;
} usb_pmsc_ptn0_t;

R_BSP_PRAGMA_UNPACK
typedef struct
{
    union {
        uint8_t    BYTE;
        /* CPU bit order rigth */
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_3(
            uint8_t             b_lun       :3, /* Logical Unit Number */
            uint8_t             b_reserved4 :4,
            uint8_t             b_immed     :1
        )BIT;
    };
} usb_pmsc_lun2_t;
R_BSP_PRAGMA_PACKOPTION

typedef struct
{
    uint8_t             uc_opcode;
    usb_pmsc_lun2_t     s_lun;
    uint8_t             uc_rsv2[2];
    uint8_t             uc_allocation;  /* Return Data Length */
    uint8_t             uc_rsv1[1];
    uint8_t             uc_rsv6[6];
} usb_pmsc_ptn12_t;

R_BSP_PRAGMA_UNPACK
typedef struct
{
    union {
        uint8_t    BYTE;
        /* CPU bit order rigth */
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_4(
            uint8_t             b_lun     :3,   /* Logical Unit Number */
            uint8_t             b_fmtdata :1,   /* Fmt Data */
            uint8_t             b_cmplist :1,   /* Cmp List */
            uint8_t             b_defect  :3    /* Defect List Fomat */
        )BIT;
    };
} usb_pmsc_lun3_t;
R_BSP_PRAGMA_PACKOPTION

typedef struct
{
    uint8_t             uc_opcode;
    usb_pmsc_lun3_t     s_lun;
    uint8_t             ul_lba0;        /* MSB */
    uint8_t             ul_lba1;
    uint8_t             ul_lba2;
    uint8_t             ul_lba3;        /* LSB */
    uint8_t             uc_rsv6[6];
} usb_pmsc_ptn378_t;

R_BSP_PRAGMA_UNPACK
typedef struct
{
    union {
        uint8_t    BYTE;
        /* CPU bit order rigth */
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_5(
            uint8_t             b_lun       :3, /* Logical Unit Number */
            uint8_t             b_1         :1,
            uint8_t             b_reserved2 :2,
            uint8_t             b_bytechk   :1,
            uint8_t             b_sp        :1
        )BIT;
    };
} usb_pmsc_s_s_lun4_t;
R_BSP_PRAGMA_PACKOPTION

typedef struct
{
    uint8_t             uc_opcode;
    usb_pmsc_s_s_lun4_t s_lun;
    uint8_t             ul_logical_block0; /* MSB */
    uint8_t             ul_logical_block1;
    uint8_t             ul_logical_block2;
    uint8_t             ul_logical_block3; /* LSB */
    uint8_t             uc_rsv1[1];
    uint8_t             us_length_hi;
    uint8_t             us_length_lo;
    uint8_t             uc_rsv3[3];
} usb_pmsc_ptn4569_t;


/* Command Descriptor Block format define. */
typedef union
{
    usb_pmsc_ptn0_t     s_usb_ptn0;
    usb_pmsc_ptn12_t    s_usb_ptn12;
    usb_pmsc_ptn378_t   s_usb_ptn378;
    usb_pmsc_ptn4569_t  s_usb_ptn4569;
} usb_pmsc_cdb_t;



/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
void    pmsc_atapi_analyze_cbwcb(uint8_t *cbwcb);
void    pmsc_atapi_command_processing(uint8_t *cbw, uint16_t status, usb_cb_t complete);
void    pmsc_atapi_init (void);

#endif  /* R_USB_PATAPI_H */
/***********************************************************************************************************************
 End Of File
 ***********************************************************************************************************************/
