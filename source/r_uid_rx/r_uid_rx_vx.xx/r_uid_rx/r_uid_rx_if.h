/*******************************************************************************
* Copyright (c) 2014 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*******************************************************************************/
/*******************************************************************************
 * File Name    : r_uid_rx_if.h
 * Description  : This module provides the interface file to be included by the user
 *              : when using the Unique ID Read API.
 ******************************************************************************/
/*******************************************************************************
 * History : DD.MM.YYYY Version Description           
 *         : 01.12.2014 1.00    First Release
 *         : 01.12.2017 1.10    Added support for RX130
 *         : 20.05.2019 1.11    Updated version to 1.11
 *         : 31.07.2019 1.13    Added support for RX13T
 *         : 10.06.2020 1.14    Updated version to 1.14
 *         : 20.03.2025 1.15    Changed the disclaimer in program sources.
 ******************************************************************************/

#ifndef UID_INTERFACE_HEADER_FILE
#define UID_INTERFACE_HEADER_FILE

/*******************************************************************************
 Macro definitions
 ******************************************************************************/
/* Version Number of API. */
#define UID_RX_VERSION_MAJOR           (1)
#define UID_RX_VERSION_MINOR           (15)

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/* Flash API error codes */
typedef enum _uid_err {
    UID_SUCCESS = 0,           /* Operation success.  */
    UID_ERR_UNINITIALIZED,     /* Uninitialized.      */
    UID_ERR_LOCK_FUNC,         /* Function Locking.   */
    UID_ERR_FAILURE,           /* Operation failure.  */
} uid_err_t;

/*******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
uid_err_t R_UID_Open(void);
uid_err_t R_UID_Read(uint8_t *);
uint32_t R_UID_GetVersion(void);

#endif /* UID_INTERFACE_HEADER_FILE */

/* end of file */
