/*
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_rsip_err.h
* Description  : RSIP function return code header file.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.10.2024 1.00     First Release.
*         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
*         :                     Revised key management specification
***********************************************************************************************************************/

#ifndef R_RSIP_ERR_H
#define R_RSIP_ERR_H

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Return code of internal function */
typedef enum e_rsip_ret
{
    /* Success */
    RSIP_RET_PASS,

    /* Branching */
    RSIP_RET_PASS_0,
    RSIP_RET_PASS_1,

    /* Error */
    RSIP_RET_RESOURCE_CONFLICT,
    RSIP_RET_RETRY,
    RSIP_RET_FAIL,
    RSIP_RET_KEY_FAIL,
    RSIP_RET_PARAM_FAIL,
    RSIP_RET_VERIFICATION_FAIL,
    RSIP_RET_AUTH_FAIL,
    RSIP_RET_VERSION_MATCH,
    RSIP_RET_UNKNOWN
} rsip_ret_t;

#endif                                 /* R_RSIP_ERR_H */
