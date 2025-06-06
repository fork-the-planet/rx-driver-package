/*
* Copyright (C) 2017-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_flash_targets.h
* Description  : This is a private header file used internally by the FLASH module. It should not be modified or
*                included by the user in their application.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           02.08.2017 1.00    First Release
*           27.02.2018 1.10    Added RX66T
*           23.10.2018 1.20    Added RX72T
*           19.04.2019 4.00    Removed support for flash type 2.
*           07.06.2019 4.10    Added RX23W
*           19.07.2019 4.20    Added RX72M
*           09.09.2019 4.30    Added RX13T
*           27.09.2019 4.40    Added RX23E-A
*           18.11.2019 4.50    Added RX66N, and RX72N.
*           23.10.2020 4.70    Added RX671.
*           23.04.2021 4.80    Added RX140.
*           23.12.2021 4.90    Added RX660.
*           24.01.2023 5.00    Added RX26T.
*           28.02.2023 5.10    Added RX23E-B.
*           30.07.2024 5.20    Added RX260, and RX261.
*           20.03.2025 5.22    Changed the disclaimer in program sources
***********************************************************************************************************************/

#ifndef FLASH_TARGETS_HEADER_FILE
#define FLASH_TARGETS_HEADER_FILE

#include <stdbool.h>
#include "platform.h"       // provides variable types and BSP equates

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* WHEN BSP IS USED, MAP FLASH MCU_xxx EQUATES TO BSP EQUATES HERE */

#define MCU_CFG_PART_MEMORY_SIZE    BSP_CFG_MCU_PART_MEMORY_SIZE
#define MCU_ROM_SIZE_BYTES          BSP_ROM_SIZE_BYTES
#define MCU_RAM_SIZE_BYTES          BSP_RAM_SIZE_BYTES
#define MCU_DATA_FLASH_SIZE_BYTES   BSP_DATA_FLASH_SIZE_BYTES

#if   defined(BSP_MCU_RX111)
    #define MCU_RX111
    #define MCU_RX11_ALL
#elif defined(BSP_MCU_RX110)
    #define MCU_RX110
    #define MCU_RX11_ALL
#elif defined(BSP_MCU_RX113)
    #define MCU_RX113
    #define MCU_RX11_ALL
#elif defined(BSP_MCU_RX130)
    #define MCU_RX130
    #define MCU_RX13_ALL
#elif defined(BSP_MCU_RX13T)
    #define MCU_RX13T
    #define MCU_RX13_ALL
#elif defined(BSP_MCU_RX140)
    #define MCU_RX140
    #define MCU_RX14_ALL
#elif defined(BSP_MCU_RX231)
    #define MCU_RX231
    #define MCU_RX23_ALL
#elif defined(BSP_MCU_RX230)
    #define MCU_RX230
    #define MCU_RX23_ALL
#elif defined(BSP_MCU_RX23E_A)
    #define MCU_RX23E_A
    #define MCU_RX23_ALL
#elif defined(BSP_MCU_RX23E_B)
    #define MCU_RX23E_B
    #define MCU_RX23_ALL
#elif defined(BSP_MCU_RX23T)
    #define MCU_RX23T
    #define MCU_RX23_ALL
#elif defined(BSP_MCU_RX23W)
    #define MCU_RX23W
    #define MCU_RX23_ALL
#elif defined(BSP_MCU_RX24T)
    #define MCU_RX24T
    #define MCU_RX24_ALL
#elif defined(BSP_MCU_RX24U)
    #define MCU_RX24U
    #define MCU_RX24_ALL
#elif defined(BSP_MCU_RX260)
    #define MCU_RX260
#elif defined(BSP_MCU_RX261)
    #define MCU_RX261
#elif defined(BSP_MCU_RX26T)
    #define MCU_RX26T
#elif defined(BSP_MCU_RX64M)
    #define MCU_RX64M
    #define MCU_RX64_ALL
#elif defined(BSP_MCU_RX651) || defined(BSP_MCU_RX65N)
    #define MCU_RX651
    #define MCU_RX65N
    #define MCU_RX65_ALL
#elif defined(BSP_MCU_RX660)
    #define MCU_RX660
    #define MCU_RX66_ALL
#elif defined(BSP_MCU_RX66T)
    #define MCU_RX66T
    #define MCU_RX66_ALL
#elif defined(BSP_MCU_RX66N)
    #define MCU_RX66N
    #define MCU_RX66_ALL
#elif defined(BSP_MCU_RX671)
    #define MCU_RX671
    #define MCU_RX67_ALL
#elif defined(BSP_MCU_RX71M)
    #define MCU_RX71M
    #define MCU_RX71_ALL
#elif defined(BSP_MCU_RX72T)
    #define MCU_RX72T
    #define MCU_RX72_ALL
#elif defined(BSP_MCU_RX72M)
    #define MCU_RX72M
    #define MCU_RX72_ALL
#elif defined(BSP_MCU_RX72N)
    #define MCU_RX72N
    #define MCU_RX72_ALL
#else
    #error "!!! No 'targets' folder for this MCU Group !!!"
#endif

#define MCU_CFG_ICLK_HZ             BSP_ICLK_HZ
#define MCU_CFG_FCLK_HZ             BSP_FCLK_HZ



/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/


/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

#endif /* FLASH_TARGETS_HEADER_FILE */

/* end of file */
