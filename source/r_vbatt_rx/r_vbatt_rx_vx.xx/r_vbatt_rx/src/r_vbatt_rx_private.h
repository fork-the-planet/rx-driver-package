/***********************************************************************************************************************
* Copyright (c) 2015 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 30.06.2015 1.00     First Release
*              : 20.05.2019 1.03     Added macro
*              : 31.03.2021 2.00     Added support for RX671
*                                    Removed the sub-folder vbatt
*              : 15.03.2025 2.31     Updated disclaimer.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_vbatt_rx_private.h
* Description  : Functions for using Battery Backup Function on RX devices. 
*******************************************************************************/
#ifndef R_VBATT_RX_PRIVATE_H
#define R_VBATT_RX_PRIVATE_H

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_vbatt_rx_if.h"
#include "r_vbatt_rx_config.h"


/*******************************************************************************
Macro definitions
*******************************************************************************/
#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

#if (defined(BSP_CFG_VBATT_ENABLE) && (1 != BSP_CFG_VBATT_ENABLE))
    #error "ERROR - BSP_CFG_VBATT_ENABLE - Parameter error in bsp configures file."
#endif

/*----------------------------------------------------------------------------*/
/*  Parameter check of Configuration Options                                  */
/*----------------------------------------------------------------------------*/
#if ((0 != VBATT_CFG_PARAM_CHECKING_ENABLE) && (1 != VBATT_CFG_PARAM_CHECKING_ENABLE))
    #error "ERROR - VBATT_CFG_PARAM_CHECKING_ENABLE - Parameter error in configures file."
#endif

#ifdef GROUP_VBATT
#if ((0 > VBATT_CFG_DETECT_FUNCTION) || (3 < VBATT_CFG_DETECT_FUNCTION))
    #error "ERROR - VBATT_CFG_DETECT_FUNCTION - Parameter error in configures file."
#endif
#endif
#if ((1 > VBATT_CFG_INT_PRIORITY) || (15 < VBATT_CFG_INT_PRIORITY))
    #error "ERROR - VBATT_CFG_INT_PRIORITY - Parameter error in configures file."
#endif

/*----------------------------------------------------------------------------*/
/*  Define                                                                    */
/*----------------------------------------------------------------------------*/
/* Define bool type */
#define VBATT_TRUE                      ((bool)(0x01))      /* True                                 */
#define VBATT_FALSE                     ((bool)(0x00))      /* False                                */

/* Define enable/disable */
#define VBATT_ENABLE                    ((uint8_t)(1))      /* Enable                               */
#define VBATT_DISABLE                   ((uint8_t)(0))      /* Disable                              */

/* Define battery backup power voltage drop detection */
#define VBATT_VOLTAGE_DROP_DETECTED     ((uint8_t)(1))  /* Battery backup power voltage drop detected  */
#define VBATT_VOLTAGE_DROP_NOT_DETECTED ((uint8_t)(0))  /* Battery backup power voltage drop not detected */


/*******************************************************************************
Typedef definitions
*******************************************************************************/
/*----------------------------------------------------------------------------*/
/*  Define Battery Backup Function information structure type.                */
/*----------------------------------------------------------------------------*/
/* API Mode. */
typedef enum
{
#ifdef GROUP_VBATT
    VBATT_MODE_NONE = 0U,                   /* Non-communication mode                               */
    VBATT_MODE_OPEN,                        /* Open mode                                            */
    VBATT_MODE_CONTROL,                     /* Control mode                                         */
    VBATT_MODE_GETSTATUS                    /* Get status mode                                      */
#endif
#ifdef GROUP_VBATTB
    VBATT_TAMPER_MODE_NONE = 0U,             /* Non-communication mode                               */
    VBATT_TAMPER_MODE_OPEN,                  /* Open mode                                            */
    VBATT_TAMPER_MODE_CONTROL,               /* Control mode                                         */
    VBATT_TAMPER_MODE_GETSTATUS              /* Get status mode                                      */
#endif
} vbatt_api_mode_t;


/*******************************************************************************
Private global variables and functions
*******************************************************************************/
/*----------------------------------------------------------------------------*/
/*  Interrupt Function                                                        */
/*----------------------------------------------------------------------------*/
extern void r_vbatt_isr_processing(void);
#ifdef GROUP_VBATT
extern void r_vbatt_nmi_isr_processing(void);
#endif

#endif /* R_VBATT_RX_PRIVATE_H */

/* End of File */

