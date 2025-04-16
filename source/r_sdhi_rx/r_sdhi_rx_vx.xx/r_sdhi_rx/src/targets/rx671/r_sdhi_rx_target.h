/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

/**********************************************************************************************************************
* File Name    : r_sdhi_rx_target.h
* Device       : RX671
* Tool-Chain   : RX Family C Compiler
* H/W Platform : RSK board for RX671
* Description  : Interface file for SDHI API for RX
**********************************************************************************************************************/
/**********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 30.06.2021 2.07    First Release
*              : 15.03.2025 2.12    Updated disclaimer.
**********************************************************************************************************************/
#ifndef SDHI_RX_TARGET_H
#define SDHI_RX_TARGET_H

#if defined(BSP_MCU_RX671)

/**********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
**********************************************************************************************************************/

/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/
/* #define for SDHI grp int status flag bit & level */
#define SDHI_CH0_INT_CDETI         (0x00000008u)          /* SDHI channel 0 interrupt SDHICD   */
#define SDHI_CH0_INT_CACI          (0x00000010u)          /* SDHI channel 0 interrupt MEM_INT  */
#define SDHI_CH0_INT_SDACI         (0x00000020u)          /* SDHI channel 0 interrupt SDIO_INT */

#define SDHI_CH1_INT_CDETI         (0x00000008u)          /* SDHI channel 1 interrupt SDHICD   */
#define SDHI_CH1_INT_CACI          (0x00000010u)          /* SDHI channel 1 interrupt MEM_INT  */
#define SDHI_CH1_INT_SDACI         (0x00000020u)          /* SDHI channel 1 interrupt SDIO_INT */

/**********************************************************************************************************************
Exported global functions (to be accessed by other files)
**********************************************************************************************************************/

#endif /* SDHI_RX_TARGET_H */

#endif /* defined(BSP_MCU_RX671) */

