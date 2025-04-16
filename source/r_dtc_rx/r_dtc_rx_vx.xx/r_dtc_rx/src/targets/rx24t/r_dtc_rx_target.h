/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target.h
* Description  : Functions for using DTC on RX24T devices. 
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 17.03.2014 1.00    Initial revision
*         : 17.07.2014 2.00    Second  revision
*         : 12.11.2014 2.01    Added RX113.
*         : 30.01.2015 2.02    Added RX71M.
*         : 13.04.2015 2.03    Added RX231 and RX230.
*         : 24.12.2015 2.04    Added RX130, RX23T and RX24T.
*         : 30.09.2016 2.05    Changed "DTC_RX_TSRGET" to "DTC_RX_TARGET".
*         :                    Added DTC IP Version.
*         : 31.03.2017 2.07    Added RX24T-512KB.
*         : 15.03.2025 4.51    Updated disclaimer.
*******************************************************************************/
#ifndef DTC_RX_TARGET_H
#define DTC_RX_TARGET_H

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* The number of activation sources and size of DTC Vector table (in byte units) */
#if (BSP_CFG_MCU_PART_MEMORY_SIZE == 0xB) || \
    (BSP_CFG_MCU_PART_MEMORY_SIZE == 0xC) || \
    (BSP_CFG_MCU_PART_MEMORY_SIZE == 0xE)
/* RX24T-512KB */
#define DTC_NUM_INTERRUPT_SRC       (124)
#define DTC_VECTOR_TABLE_SIZE_BYTES (0x3F8 + 0x400)
#else
/* RX24T-256KB */
#define DTC_NUM_INTERRUPT_SRC       (85)
#define DTC_VECTOR_TABLE_SIZE_BYTES (0x3E8 + 0x400)
#endif

/* DTC IP Version */
#define DTC_IP                      (DTC_IP_VER_DTCa)

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


#endif /* DTC_RX_TARGET_H */

/* End of File */

