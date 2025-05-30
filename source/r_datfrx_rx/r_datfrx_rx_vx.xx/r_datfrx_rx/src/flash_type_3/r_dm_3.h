/*
* Copyright (c) 2018(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/************************************************************************************************
* File Name    : r_dm_3.h
* Version      : 2.31
* Description  : DATFRX interface header file
*************************************************************************************************/
/************************************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 28.09.2018 2.00     First Release
*              : 20.03.2025 2.31     Changed the disclaimer.
*************************************************************************************************/

/************************************************************************************************
Includes <System Includes> , "Project Includes"
*************************************************************************************************/
#include "r_datfrx_rx_config.h"               /* DATFRX Configuration definitions    */
#include "r_flash_rx_if.h"                    /* FLASH module                        */
#include "r_flash_dm_rx_if.h"                 /* DATFRX I/F definitions              */
#include "r_flash_dm_private.h"               /* DATFRX Private module definitions   */

/************************************************************************************************
Macro definitions
*************************************************************************************************/
#ifndef R_DM_3_H
#define R_DM_3_H

#if(FLASH_TYPE == FLASH_TYPE_3)

#include "r_dispatch_2.h"
#include "r_datf_crc.h"

/************************************************************************************************
Global Typedef definitions
*************************************************************************************************/

/************************************************************************************************
Exported global variables
*************************************************************************************************/

/************************************************************************************************
Exported global functions (to be accessed by other files)
*************************************************************************************************/

#endif /* (FLASH_TYPE == FLASH_TYPE_3) */

#endif /* R_DM_3_H */

/* End of File */
