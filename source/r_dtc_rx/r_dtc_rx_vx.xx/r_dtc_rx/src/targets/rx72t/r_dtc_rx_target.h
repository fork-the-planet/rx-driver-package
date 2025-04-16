/***********************************************************************************************************************
* Copyright (c) 2019 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target.h
* Description  : Functions for using DTC on RX72T.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.02.2019 2.20    First Release for RX72T.
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
/* The number of activation sources */
#if defined(BSP_MCU_RX72T)
#define DTC_NUM_INTERRUPT_SRC       (129)
#endif /* defined(BSP_MCU_RX72T) */

/* Size of DTC Vector table (in byte units) */
#define DTC_VECTOR_TABLE_SIZE_BYTES (0x400 + 0x400)

/* Definition of num of DMAC channel. */
#define DMAC_NUM_CHANNELS           (8)

/* DTC IP Version */
#define DTC_IP                      (DTC_IP_VER_DTCa)

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


#endif /* DTC_RX_TARGET_H */

/* End of File */

