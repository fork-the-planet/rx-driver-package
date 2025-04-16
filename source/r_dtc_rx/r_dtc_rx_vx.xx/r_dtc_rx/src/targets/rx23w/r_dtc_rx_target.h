/***********************************************************************************************************************
* Copyright (c) 2019 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target.h
* Description  : Functions for using DTC on RX23W devices. 
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 28.06.2019 1.00    Initial revision
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
#define DTC_NUM_INTERRUPT_SRC       (89)
/* Size of DTC Vector table (in byte units) */
#define DTC_VECTOR_TABLE_SIZE_BYTES (0x3E8 + 0x400)
/* Definition of num of DMAC channel. */
#define DMAC_NUM_CHANNELS           (4)
/* DTC IP Version */
#define DTC_IP                      (DTC_IP_VER_DTCa)

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


#endif /* DTC_RX_TARGET_H */

/* End of File */

