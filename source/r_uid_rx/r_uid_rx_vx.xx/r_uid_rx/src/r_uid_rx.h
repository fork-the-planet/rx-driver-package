/*******************************************************************************
* Copyright (c) 2014 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*******************************************************************************/
/*******************************************************************************
 * File Name    : r_uid_rx.h
 * Description  : This is a private header file used internally by the Unique ID Read API module.
 *              : It should not be modified or included by the user in their application.
 ******************************************************************************/
/*******************************************************************************
 * History : DD.MM.YYYY Version Description           
 *         : 01.12.2014 1.00    First Release
 *         : 20.05.2019 1.11    Added macro
 *         : 20.03.2025 1.15    Changed the disclaimer in program sources.
 ******************************************************************************/

#ifndef RX_UID_API_PRIVATE_HEADER_FILE
#define RX_UID_API_PRIVATE_HEADER_FILE


/*******************************************************************************
 Macro definitions
 ******************************************************************************/
#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

typedef enum {
    UID_UNINITIALIZED = 0,  /* Uninitialized */
    UID_READY               /* Unique ID Read Executable State */
} uid_status_t;


#endif /* RX_UID_API_PRIVATE_HEADER_FILE */

/* end of file */
