/***********************************************************************************************************************
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_rsci_iic_rx_if.h
 * Description  : Functions for using RSCI_IIC on RX devices. 
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 30.10.2025 1.00     First Release
 *         : 30.03.2026 1.01     Included spdx file in the package.
 *                               Fixed warnings in GCC.
 **********************************************************************************************************************/
/* Guards against multiple inclusion */
#ifndef RSCI_IIC_IF_H
    #define RSCI_IIC_IF_H

R_BSP_PRAGMA_UNPACK

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

/* Version Number of API. */
    #define RSCI_IIC_VERSION_MAJOR  (1)
    #define RSCI_IIC_VERSION_MINOR  (01)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef uint8_t rsci_iic_ch_dev_status_t;
typedef uint8_t rsci_iic_ctrl_ptn_t;

typedef enum /* RSCI_IIC API error codes */
{
    RSCI_IIC_SUCCESS = 0U,
    RSCI_IIC_ERR_LOCK_FUNC,                  /* chan still running in another mode */
    RSCI_IIC_ERR_INVALID_CHAN,               /* non-existent channel number */
    RSCI_IIC_ERR_INVALID_ARG,
    RSCI_IIC_ERR_NO_INIT,
    RSCI_IIC_ERR_BUS_BUSY,
    RSCI_IIC_ERR_OTHER
} rsci_iic_return_t;

/*----------------------------------------------------------------------------*/
/*   Define rsci_iic information structure type.                               */
/*----------------------------------------------------------------------------*/
/*----- Callback function type. -----*/
typedef void (* rsci_iic_callback)(void); /* Callback function type */

/*----- Structure type. -----*/
/* RSCI_IIC Information structure. */
typedef struct
{
    uint8_t                 rsv2; /* reserved */
    uint8_t                 rsv1; /* reserved */
    rsci_iic_ch_dev_status_t dev_sts; /* Device status flag */
    uint8_t                 ch_no; /* Channel No. */
    rsci_iic_callback        callbackfunc; /* Callback function */
    uint32_t                cnt2nd; /* 2nd Data Counter */
    uint32_t                cnt1st; /* 1st Data Counter */
    uint8_t               * p_data2nd; /* Pointer for 2nd Data buffer */
    uint8_t               * p_data1st; /* Pointer for 1st Data buffer */
    uint8_t               * p_slv_adr; /* Pointer for Slave address buffer */
} rsci_iic_info_t;

/*----------------------------------------------------------------------------*/
/*   Define rsci_iic status structure type.                                    */
/*----------------------------------------------------------------------------*/
typedef union
{
    uint32_t                LONG;
    R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_6
    (
        uint32_t rsv :27, /* reserve */
        uint32_t SCLI :1, /* SSCL Pin Level */
        uint32_t SDAI :1, /* SSDA Pin Level */
        uint32_t NACK :1, /* NACK detection flag */
        uint32_t TRS :1, /* Send mode / Receive mode flag */
        uint32_t BSY :1 /* Bus status flag */
    ) BIT;
} rsci_iic_mcu_status_t;

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/
extern volatile rsci_iic_ch_dev_status_t g_rsci_iic_ChStatus[]; /* Channel state flag */

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
/* IIC Driver API functions */

/******************************************************************************
 * Function Name: R_RSCI_IIC_Open
 * Description  : .
 * Arguments    : p_rsci_iic_info
 * Return Value : .
 *****************************************************************************/
rsci_iic_return_t R_RSCI_IIC_Open (rsci_iic_info_t * p_rsci_iic_info);

/******************************************************************************
 * Function Name: R_RSCI_IIC_MasterSend
 * Description  : .
 * Arguments    : p_rsci_iic_info
 * Return Value : .
 *****************************************************************************/
rsci_iic_return_t R_RSCI_IIC_MasterSend (rsci_iic_info_t * p_rsci_iic_info);

/******************************************************************************
 * Function Name: R_RSCI_IIC_MasterReceive
 * Description  : .
 * Arguments    : p_rsci_iic_info
 * Return Value : .
 *****************************************************************************/
rsci_iic_return_t R_RSCI_IIC_MasterReceive (rsci_iic_info_t * p_rsci_iic_info);

/******************************************************************************
 * Function Name: R_RSCI_IIC_GetStatus
 * Description  : .
 * Arguments    : p_rsci_iic_info
 *              : p_rsci_iic_status
 * Return Value : .
 *****************************************************************************/
rsci_iic_return_t R_RSCI_IIC_GetStatus (rsci_iic_info_t * p_rsci_iic_info, rsci_iic_mcu_status_t * p_rsci_iic_status);

/******************************************************************************
 * Function Name: R_RSCI_IIC_Control
 * Description  : .
 * Arguments    : p_rsci_iic_info
 *              : ctrl_ptn
 * Return Value : .
 *****************************************************************************/
rsci_iic_return_t R_RSCI_IIC_Control (rsci_iic_info_t * p_rsci_iic_info, rsci_iic_ctrl_ptn_t ctrl_ptn);

/******************************************************************************
 * Function Name: R_RSCI_IIC_Close
 * Description  : .
 * Arguments    : p_rsci_iic_info
 * Return Value : .
 *****************************************************************************/
rsci_iic_return_t R_RSCI_IIC_Close (rsci_iic_info_t * p_rsci_iic_info);

/******************************************************************************
 * Function Name: R_RSCI_IIC_GetVersion
 * Description  : .
 * Return Value : .
 *****************************************************************************/
uint32_t          R_RSCI_IIC_GetVersion (void);

R_BSP_PRAGMA_PACKOPTION

#endif /* RSCI_IIC_IF_H */
