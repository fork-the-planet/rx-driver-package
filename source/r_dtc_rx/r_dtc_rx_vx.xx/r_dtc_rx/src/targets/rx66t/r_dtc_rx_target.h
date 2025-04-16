/***********************************************************************************************************************
* Copyright (c) 2018 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target.h
* Description  : Functions for using DTC on RX66T.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 28.09.2018 2.10    First Release for RX66T.
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
#if defined(BSP_MCU_RX66T)
#define DTC_NUM_INTERRUPT_SRC       (129)
#endif /* defined(BSP_MCU_RX66T) */

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

