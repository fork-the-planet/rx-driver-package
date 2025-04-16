/***********************************************************************************************************************
* Copyright (c) 2015 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 30.06.2015 1.00     First Release
*              : 30.06.2019 1.04     Added support for RX23W
*              : 31.03.2021 2.00     Added support for RX671
*                                    Removed the sub-folder vbatt
*              : 15.03.2025 2.31     Updated disclaimer.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_vbatt_rx_platform.h
* Description  : Functions for using Battery Backup Function on RX devices. 
*******************************************************************************/
#ifndef R_VBATT_RX_PLATFORM_H
#define R_VBATT_RX_PLATFORM_H

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Include specifics for chosen MCU.  */
#if defined(BSP_MCU_RX231)
    #include "./targets/rx231/r_vbatt_rx231_private.h"
#elif defined(BSP_MCU_RX230)
    #include "./targets/rx230/r_vbatt_rx230_private.h"
#elif defined(BSP_MCU_RX23W)
    #include "./targets/rx23w/r_vbatt_rx23w_private.h"
#elif defined(BSP_MCU_RX671)
    #include "./targets/rx671/r_vbatt_rx671_private.h"
#else
    #error "This MCU is not supported by the current r_vbatt_rx module."
#endif


#endif /* R_VBATT_RX_PLATFORM_H */

/* End of File */

