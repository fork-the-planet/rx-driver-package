/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target.h
* Description  : Functions for using DTC on RX140 devices.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 15.04.2021 1.00    First Release
*         : 23.02.2022 4.00    Added interrupt vector "DTCE_RNG_RNGRDI" for RX140.
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
#define DTC_NUM_INTERRUPT_SRC       (67)

#if (DTC_ENABLE == DTC_CFG_USE_SEQUENCE_TRANSFER)
/* Size of DTC Vector table and DTC Index table (in byte units) */
#define DTC_VECTOR_TABLE_SIZE_BYTES (0x400 + 0x400 + 0x400)
#else
/* Size of DTC Vector table (in byte units) */
#define DTC_VECTOR_TABLE_SIZE_BYTES (0x400 + 0x400)
#endif /* (DTC_ENABLE == DTC_CFG_USE_SEQUENCE_TRANSFER) */

/* DTC IP Version */
#define DTC_IP                      (DTC_IP_VER_DTCb)

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


#endif /* DTC_RX_TARGET_H */

/* End of File */

