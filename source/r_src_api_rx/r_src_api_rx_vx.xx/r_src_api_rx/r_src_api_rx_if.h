/*
* Copyright (c) 2014 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/******************************************************************************
* File Name    : r_src_api_rx_if.h
* Version      : 1.15
* Device       : RX64M, RX71M
* Tool-Chain   : RX Family C Compiler v3.07.00
*                GCC for Renesas RX 8.3.0.202411
*                IAR C/C++ Compiler for Renesas RX version 5.10.1
* Description  : Interface file for SRC API for RX
*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.07.2014 1.00    First Release
*         : 05.09.2014 1.10    Second Release
*                              'change SRC_API_VERSION_MINOR (00) to (10).
*         : 11.12.2014 1.11    RX71M support added.
*                              'change SRC_API_VERSION_MINOR (10) to (11).
*         : 01.02.2019 1.12    Changed Minor version to 1.12.
*         : 20.05.2019 1.13    Updated version to 1.13
*         : 10.06.2020 1.14    Updated version to 1.14
*         : 20.03.2025 1.15    Changed the disclaimer.
******************************************************************************/

#ifndef SRC_API_RX_H_
#define SRC_API_RX_H_

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Fixed-width integer and bool support. */
#include "platform.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/* Version Number of API. */
#define SRC_API_VERSION_MAJOR           (1)
#define SRC_API_VERSION_MINOR           (15)

/* Return Value of SRC API */
typedef enum
{
    SRC_SUCCESS    =  0,
    SRC_ERR_PARAM  = -1,
    SRC_ERR_UNLOCK = -2,
    SRC_ERR_LOCKED = -3,
    SRC_NOT_END    = -4,
    SRC_END        = -5,
} src_ret_t;

/* Sampling rate of output */
typedef enum
{
    SRC_OFS_44 = 0,        /* 44.1kHz  */
    SRC_OFS_48 = 1,        /* 48kHz    */
    SRC_OFS_32 = 2,        /* 32kHz    */
    SRC_OFS_8  = 4,        /* 8kHz     */
    SRC_OFS_16 = 5,        /* 16kHz    */
} src_ofs_t;

/* Sampling rate of input */ 
typedef enum
{
    SRC_IFS_8  = 0,        /* 8kHz     */
    SRC_IFS_11 = 1,        /* 11.02kHz */
    SRC_IFS_12 = 2,        /* 12kHz    */
    SRC_IFS_16 = 4,        /* 16kHz    */
    SRC_IFS_22 = 5,        /* 22.05kHz */
    SRC_IFS_24 = 6,        /* 24.0kHz  */
    SRC_IFS_32 = 8,        /* 32kHz    */
    SRC_IFS_44 = 9,        /* 44.1kHz  */
    SRC_IFS_48 = 10,       /* 48kHz    */
} src_ifs_t;

/* Input data endian configuration (for SRCIDCTRL.IED) */
typedef enum {
    SRC_IED_OFF = 0,   /* Endian of chip is the same as endian of input data  */
    SRC_IED_ON  = 1,   /* Endian of chip is not the sama as endian of input data */
} src_ied_t;

/* Output data endian configuration (for SRCODCTRL.OED) */
typedef enum {
    SRC_OED_OFF = 0,   /* Endian of chip is the same as endian of output data */
    SRC_OED_ON  = 1,   /* Endian of chip is not the sama as endian of output data */
} src_oed_t;

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/
src_ret_t R_SRC_Open( void );
src_ret_t R_SRC_Close( void );
src_ret_t R_SRC_Start( src_ifs_t fsi, src_ofs_t fso, src_ied_t ied, src_oed_t oed );
src_ret_t R_SRC_Stop( void );
int8_t    R_SRC_Write( uint16_t * buf, uint32_t samples);
int32_t   R_SRC_Read( uint16_t * buf, uint32_t samples);
src_ret_t R_SRC_CheckFlush( void );
uint32_t  R_SRC_GetVersion( void );

#endif /* SRC_API_RX_H_ */

