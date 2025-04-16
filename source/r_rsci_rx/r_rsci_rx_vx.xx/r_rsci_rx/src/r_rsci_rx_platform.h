/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_rsci_rx_platform.h
* Description  : Functions for using RSCI on the RX devices.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           31.03.2021 1.00    Initial Release
*                              Supported for RX671.
*           31.03.2022 2.10    Supported for RX660.
*           15.08.2022 2.30    Supported for RX26T.
*           28.06.2024 2.60    Supported for RX260, RX261.
*           15.03.2025 2.71    Updated disclaimer
************************************************************************************************************************/

#ifndef RSCI_RX_PLATFORM_H
#define RSCI_RX_PLATFORM_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_rsci_rx_if.h"

#if defined(BSP_MCU_RX671)
#include "./targets/rx671/r_rsci_rx671_private.h"  /* RX671 */
#elif defined(BSP_MCU_RX660)
#include "./targets/rx660/r_rsci_rx660_private.h"  /* RX660 */
#elif defined(BSP_MCU_RX26T)
#include "./targets/rx26t/r_rsci_rx26t_private.h"  /* RX26T */
#elif defined(BSP_MCU_RX260)
#include "./targets/rx260/r_rsci_rx260_private.h"  /* RX260 */
#elif defined(BSP_MCU_RX261)
#include "./targets/rx261/r_rsci_rx261_private.h"  /* RX261 */
#else
#error "ERROR - r_rsci_rxXXX_private.h not included."
#endif

#endif /* RSCI_RX_PLATFORM_H */

