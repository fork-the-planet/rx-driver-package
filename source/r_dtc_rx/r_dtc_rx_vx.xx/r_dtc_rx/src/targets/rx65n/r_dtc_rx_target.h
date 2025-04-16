/***********************************************************************************************************************
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target.h
* Description  : Functions for using DTC on RX65N devices.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.09.2016 2.05    First Release
*         : 31.07.2017 2.08    Supported RX65N-2MB and RX130-512KB.
*         : 01.02.2019 2.20    Supported RX65N-64pin.
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
#if defined(BSP_MCU_RX65N_2MB)
#define DTC_NUM_INTERRUPT_SRC       (201)
#else
#define DTC_NUM_INTERRUPT_SRC       (199)
#endif /* defined(BSP_MCU_RX65N_2MB) */

#if (DTC_ENABLE == DTC_CFG_USE_SEQUENCE_TRANSFER)
/* Size of DTC Vector table and DTC Index table (in byte units) */
#define DTC_VECTOR_TABLE_SIZE_BYTES (0x400 + 0x400 + 0x400)
#else
/* Size of DTC Vector table (in byte units) */
#define DTC_VECTOR_TABLE_SIZE_BYTES (0x400 + 0x400)
#endif /* (DTC_ENABLE == DTC_CFG_USE_SEQUENCE_TRANSFER) */

/* Definition of num of DMAC channel. */
#define DMAC_NUM_CHANNELS           (8)

/* DTC IP Version */
#define DTC_IP                      (DTC_IP_VER_DTCb)

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


#endif /* DTC_RX_TARGET_H */

/* End of File */

