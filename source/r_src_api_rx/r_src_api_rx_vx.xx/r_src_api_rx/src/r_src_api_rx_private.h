/*
* Copyright (c) 2014 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/******************************************************************************
* File Name    : r_src_api_rx_private.h
* Version      : 1.15
* Device       : RX64M, RX71M
* Tool-Chain   : RX Family C Compiler
* Description  : SRC for the RX64M
*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.07.2014 1.00    First Release
*         : 05.09.2014 1.10    Second Release, no code modification on this file.
*         : 11.12.2014 1.11    RX71M support added.
*         : 20.05.2019 1.13    Added macro
*         : 20.03.2025 1.15    Changed the disclaimer.
*                               
******************************************************************************/

#ifndef SRC_API_RX_PRIVATE_H_
#define SRC_API_RX_PRIVATE_H_

/******************************************************************************
    Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Get r_bsp info. */
#include "platform.h"
#include "r_src_api_rx_config.h"

/******************************************************************************
    Macro definitions
******************************************************************************/
#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

/******************************************************************************
Typedef definitions
******************************************************************************/
/* Input data empty interrupt configuration (for SRCIDCTRL.IEN) */
typedef enum {
    SRC_IEN_OFF = 0,   /* Disable interrupt */
    SRC_IEN_ON  = 1,   /* Enable interrupt */
} src_ien_t;

/* Output data empty interrupt configuration (for SRCODCTRL.OEN) */
typedef enum {
    SRC_OEN_OFF = 0,   /* Disable interrupt */
    SRC_OEN_ON  = 1,   /* Enable interrupt */
} src_oen_t;

/* Channel swap of output data (for SRCODCTRL.OCH) */
typedef enum {
    SRC_OCH_OFF = 0,   /* same order of input data */
    SRC_OCH_ON  = 1,   /* reverse order of input data */
} src_och_t;

/* Condition when IINT frag to be set (for SRCIDCTRL.IFTRG) */
typedef enum {
    SRC_IFTG_0  = 0,   /* Set flag when number of data in FIFO is 0 or less */
    SRC_IFTG_2  = 1,   /* Set flag when number of data in FIFO is 2 or less */
    SRC_IFTG_4  = 2,   /* Set flag when number of data in FIFO is 4 or less */
    SRC_IFTG_6  = 3,   /* Set flag when number of data in FIFO is 6 or less */
} src_iftg_t;

/* Condition when OINT frag to be set (for SRCODCTRL.OFTRG) */
typedef enum {
    SRC_OFTG_1  = 0,   /* Set flag when number of data in FIFO is 1 or larger */
    SRC_OFTG_4  = 1,   /* Set flag when number of data in FIFO is 4 or larger */
    SRC_OFTG_8  = 2,   /* Set flag when number of data in FIFO is 8 or larger */
    SRC_OFTG_12 = 3,   /* Set flag when number of data in FIFO is 12 or larger */
} src_oftg_t;

/* Switch for internal work memory clear (for SRCCTRL.CL) */
typedef enum {
/*  SRC_CL_OFF = 0, *//* "0" should not be written to CL */
    SRC_CL_ON  = 1,   /* Clear internal work memory */
} src_cl_t;

/* Switch for flash (for SRCCTRL.FL) */
typedef enum {
/*  SRC_FL_OFF = 0, *//* "0" should not be written to FL */
    SRC_FL_ON  = 1,   /* Execute flush  */
} src_fl_t;

/* Switch for over write interrupt enable (for SRCCTRL.OVEN) */
typedef enum {
    SRC_OVEN_OFF = 0,   /* Disble overwrite interrupt */
    SRC_OVEN_ON  = 1,   /* Enable overwrite interrupt */
} src_oven_t;

/* Switch for under flow interrupt enable (for SRCCTRL.UDEN) */
typedef enum {
    SRC_UDEN_OFF = 0,   /* Disble underflow interrupt */
    SRC_UDEN_ON  = 1,   /* Enable underflow interrupt */
} src_uden_t;

/* Switch for activate SRC peripheral (for SRCCTRL.SRCEN) */
typedef enum {
    SRC_SRCEN_OFF = 0,   /* Inactivate SRC peripheral */
    SRC_SRCEN_ON  = 1,   /* Activate SRC peripheral */
} src_srcen_t;

/* Switch for conversion finish interrupt enable (for SRCCTRL.CEEN) */
typedef enum {
    SRC_CEEN_OFF = 0,   /* Disble conversion finish interrupt */
    SRC_CEEN_ON  = 1,   /* Enable conversion finish interrupt */
} src_ceen_t;

/* Switch for coefficient write enable/disable  (for SRCCTRL.FICRAE) */
typedef enum {
    SRC_FICRAE_WR_DISABLE = 0,    /* Disable write */
    SRC_FICRAE_WR_ENABLE  = 1,    /* Eable write   */
} src_ficrae_t;

/******************************************************************************
    Error checking for user configuration
******************************************************************************/
/*************************************************/
/*   Checking shared MCU resource configuration  */
/*************************************************/
/*
     No shared MCU resource is used 
*/

/*************************************************/
/*    Checking configuration for SRC main body   */
/*************************************************/
/* Macro definition for user parameter ranges */
#define SRC_IEN_MIN   (0)   /* SRC_IEN_OFF */
#define SRC_IEN_MAX   (1)   /* SRC_IEN_ON  */
#define SRC_OEN_MIN   (0)   /* SRC_OEN_OFF */
#define SRC_OEN_MAX   (1)   /* SRC_OEN_ON  */
#define SRC_OCH_MIN   (0)   /* SRC_OCH_OFF */
#define SRC_OCH_MAX   (1)   /* SRC_OCH_ON  */
#define SRC_IFTG_MIN  (0)   /* SRC_IFTG_0  */
#define SRC_IFTG_MAX  (3)   /* SRC_IFTG_6  */
#define SRC_OFTG_MIN  (0)   /* SRC_OFTG_1  */
#define SRC_OFTG_MAX  (3)   /* SRC_OFTG_12 */

/* SRC_IEN configuration check */
#if ( (SRC_IEN > SRC_IEN_MAX) || (SRC_IEN < SRC_IEN_MIN) )
    #error "the value for macro SRC_IEN must be (0) or (1)"
#endif

/* SRC_OEN configuration check */
#if ( (SRC_OEN > SRC_OEN_MAX) || (SRC_OEN < SRC_OEN_MIN) )
    #error "the value for macro SRC_OEN must be (0) or (1)"
#endif

/* SRC_IED configuration check */
#if ( (SRC_IED > SRC_IED_MAX) || (SRC_IED < SRC_IED_MIN) )
    #error "the value for macro SRC_IED must be (0) or (1)"
#endif

/* SRC_OED configuration check */
#if ( (SRC_OED > SRC_OED_MAX) || (SRC_OED < SRC_OED_OFF) )
    #error "the value for macro SRC_OED must be (0) or (1)"
#endif

/* SRC_OCH configuration check */
#if ( (SRC_OCH > SRC_OCH_MAX) || (SRC_OCH < SRC_OCH_MIN) )
    #error "the value for macro SRC_OCH must be (0) or (1)"
#endif

/* Following instruction, it shows mis-judgement. 02.Dec.2013 */
#if ( (SRC_IFTG > SRC_IFTG_MAX) || (SRC_IFTG < SRC_IFTG_MIN) )
    #error "the value for macro SRC_IFTG must range from (0) to (3)"
#endif

/* Following instruction, it shows mis-judgement. 02.Dec.2013 */
#if ( (SRC_OFTG > SRC_OFTG_MAX) || (SRC_OFTG < SRC_OFTG_MIN) )
    #error "the value for macro SRC_OFTG must range from (0) to (3)"
#endif

#endif /* SRC_API_RX_PRIVATE_H_ */

