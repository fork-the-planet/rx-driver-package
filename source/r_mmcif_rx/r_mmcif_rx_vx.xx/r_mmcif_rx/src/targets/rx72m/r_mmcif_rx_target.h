/***********************************************************************************************************************
* Copyright (c) 2019 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

/**********************************************************************************************************************
* File Name    : r_mmcif_rx_target.h
* Description  : Interface file for MMC API for RX
***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 30.07.2019 1.06    First Release
*              : 29.11.2024 1.20    Updated file description.
*              : 15.03.2025 1.21    Updated disclaimer.
**********************************************************************************************************************/

#ifndef _MMC_RX_TARGET_H
#define _MMC_RX_TARGET_H

/**********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
**********************************************************************************************************************/

/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/
/* ---- Definition of group interrupt source register. ---- */
#define MMC_CH0_INT_CDETIO          (0x00000040u)   /* MMC channel 0 card detection interrupt                       */
#define MMC_CH0_INT_ERRIO           (0x00000080u)   /* MMC channel 0 error interrupt                                */
#define MMC_CH0_INT_ACCIO           (0x00000100u)   /* MMC channel 0 access interrupt                               */

#define MMC_CH1_INT_CDETIO          (0x00000040u)   /* MMC channel 1 card detection interrupt                       */
#define MMC_CH1_INT_ERRIO           (0x00000080u)   /* MMC channel 1 error interrupt                                */
#define MMC_CH1_INT_ACCIO           (0x00000100u)   /* MMC channel 1 access interrupt                               */


/**********************************************************************************************************************
Exported global functions (to be accessed by other files)
**********************************************************************************************************************/


#endif /* _MMC_RX_TARGET_H */

