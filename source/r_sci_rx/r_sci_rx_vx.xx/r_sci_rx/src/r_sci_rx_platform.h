/***********************************************************************************************************************
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_sci_rx_platform.h
* Description  : Functions for using SCI on the RX devices.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           01.10.2016 1.80    Initial Release. (The remake of the r01an1815ju0170 to the base.)
*           19.12.2016 1.90    Added RX24U support
*           28.09.2018 2.10    Added RX66T support
*           01.02.2019 2.20    Added RX72T, RX65N-64pin support
*           28.06.2019 3.10    Added RX23W support
*           15.08.2019 3.20    Added RX72M support
*           25.11.2019 3.30    Added support RX13T.
*                              Removed support for Generation 1 devices.
*           30.12.2019 3.40    Added support RX66N, RX72N.
*           31.03.2020 3.50    Added support RX23E-A.
*           31.03.2021 3.80    Added support for RX671.
*           15.04.2021 3.90    Added support for RX140.
*           31.03.2022 4.40    Added support for RX660.
*           31.03.2023 4.80    Added support for RX26T.
*                              Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*           29.05.2023 4.90    Added support for RX23E-B.
*           28.06.2024 5.30    Added support for RX260, RX261.
*           15.03.2025 5.41    Updated disclaimer
***********************************************************************************************************************/

#ifndef SCI_RX_PLATFORM_H
#define SCI_RX_PLATFORM_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_sci_rx_if.h"

#if defined(BSP_MCU_RX110) 
#include "./targets/rx110/r_sci_rx110_private.h"  /* RX110 */
#elif defined(BSP_MCU_RX111)
#include "./targets/rx111/r_sci_rx111_private.h"  /* RX111 */
#elif defined(BSP_MCU_RX113)
#include "./targets/rx113/r_sci_rx113_private.h"  /* RX113 */
#elif defined(BSP_MCU_RX130)
#include "./targets/rx130/r_sci_rx130_private.h"  /* RX130 */
#elif defined(BSP_MCU_RX13T)
#include "./targets/rx13t/r_sci_rx13t_private.h"  /* RX13T */
#elif defined(BSP_MCU_RX140)
#include "./targets/rx140/r_sci_rx140_private.h"  /* RX140 */
#elif defined(BSP_MCU_RX230)
#include "./targets/rx230/r_sci_rx230_private.h"  /* RX230 */
#elif defined(BSP_MCU_RX231)
#include "./targets/rx231/r_sci_rx231_private.h"  /* RX231 */
#elif defined(BSP_MCU_RX23E_A)
#include "./targets/rx23e-a/r_sci_rx23e-a_private.h"  /* RX23E-A */
#elif defined(BSP_MCU_RX23E_B)
#include "./targets/rx23e-b/r_sci_rx23e-b_private.h"  /* RX23E-B */
#elif defined(BSP_MCU_RX23T)
#include "./targets/rx23t/r_sci_rx23t_private.h"  /* RX23T */
#elif defined(BSP_MCU_RX23W)
#include "./targets/rx23w/r_sci_rx23w_private.h"  /* RX23W */
#elif defined(BSP_MCU_RX24T)
#include "./targets/rx24t/r_sci_rx24t_private.h"  /* RX24T */
#elif defined(BSP_MCU_RX24U)
#include "./targets/rx24u/r_sci_rx24u_private.h"  /* RX24U */
#elif defined(BSP_MCU_RX260)
#include "./targets/rx260/r_sci_rx260_private.h"  /* RX260 */
#elif defined(BSP_MCU_RX261)
#include "./targets/rx261/r_sci_rx261_private.h"  /* RX261 */
#elif defined(BSP_MCU_RX26T)
#include "./targets/rx26t/r_sci_rx26t_private.h"  /* RX26T */
#elif defined(BSP_MCU_RX64M)
#include "./targets/rx64m/r_sci_rx64m_private.h"  /* RX64M */
#elif defined(BSP_MCU_RX65N)
#include "./targets/rx65n/r_sci_rx65n_private.h"  /* RX65N */
#elif defined(BSP_MCU_RX66T)
#include "./targets/rx66t/r_sci_rx66t_private.h"  /* RX66T */
#elif defined(BSP_MCU_RX66N)
#include "./targets/rx66n/r_sci_rx66n_private.h"  /* RX66N */
#elif defined(BSP_MCU_RX671)
#include "./targets/rx671/r_sci_rx671_private.h"  /* RX671 */
#elif defined(BSP_MCU_RX660)
#include "./targets/rx660/r_sci_rx660_private.h"  /* RX660 */
#elif defined(BSP_MCU_RX71M)
#include "./targets/rx71m/r_sci_rx71m_private.h"  /* RX71M */
#elif defined(BSP_MCU_RX72T)
#include "./targets/rx72t/r_sci_rx72t_private.h"  /* RX72T */
#elif defined(BSP_MCU_RX72M)
#include "./targets/rx72m/r_sci_rx72m_private.h"  /* RX72M */
#elif defined(BSP_MCU_RX72N)
#include "./targets/rx72n/r_sci_rx72n_private.h"  /* RX72N */
#else
#error "ERROR - r_sci_rxXXX_private.h not included."
#endif

#endif /* SCI_RX_PLATFORM_H */

