/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_canfd_rx_private.h
* Description  : Internal structures and definitions for the CANFD driver.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           22.11.2021 1.00    Initial Release
*           15.03.2025 1.41    Updated disclaimer.
***********************************************************************************************************************/

#ifndef CAN_PRIVATE_HEADER_FILE
#define CAN_PRIVATE_HEADER_FILE

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"
#include "r_canfd_rx_config.h"
#include "r_canfd_rx_if.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/******************************************************************************
 * ACCEPTANCE FILTER LIST CONFIGURATION DEFINITIONS
 ******************************************************************************/
/*
 * Adapted from iodefine.h
 */
typedef R_BSP_EVENACCESS struct st_canfd_afl
{
    union {
        unsigned long LONG;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_4 (
            unsigned long IDE:1,
            unsigned long RTR:1,
            unsigned long LPC:1,
            unsigned long ID:29
        ) BIT;
    } IDR;

    union {
        unsigned long LONG;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_4 (
            unsigned long IDEM:1,
            unsigned long RTRM:1,
            unsigned long IFL1:1,
            unsigned long IDM:29
        ) BIT;
    } MASK;

    union {
        unsigned long LONG;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_7 (
            unsigned long PTR:16,
            unsigned long DMBE:1,
            unsigned long :2,
            unsigned long DMB:5,
            unsigned long IFL0:1,
            unsigned long :3,
            unsigned long DLC:4
        ) BIT;
    } PTR0;

    union {
        unsigned long LONG;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_5 (
            unsigned long :23,
            unsigned long CF0E:1,
            unsigned long :6,
            unsigned long RF1E:1,
            unsigned long RF0E:1
        ) BIT;
    } PTR1;
} canfd_afl_t;

/******************************************************************************
 * ACCEPTANCE FILTER LIST CONFIGURATION DEFINITIONS
 ******************************************************************************/
/*
 * Adapted from iodefine.h
 */
typedef R_BSP_EVENACCESS struct st_canfd_rmb
{
    union {
        unsigned long LONG;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_4 (
            unsigned long IDE:1,
            unsigned long RTR:1,
            unsigned long :1,
            unsigned long ID:29
        ) BIT;
    } HF0;

    union {
        unsigned long LONG;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_3 (
            unsigned long DLC:4,
            unsigned long :12,
            unsigned long TS:16
        ) BIT;
    } HF1;

    union {
        unsigned long LONG;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_7 (
            unsigned long PTR:16,
            unsigned long :6,
            unsigned long IFL:2,
            unsigned long :5,
            unsigned long FDF:1,
            unsigned long BRS:1,
            unsigned long ESI:1
        ) BIT;
    } HF2;

    union {
        unsigned long DF[16];
        unsigned char DATA[64];
    } ;
} canfd_rmb_t;

#endif /* CANFD_PRIVATE_HEADER_FILE*/
