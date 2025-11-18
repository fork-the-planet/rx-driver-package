/** \file
    /*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
    /* ---------------------------------------------------------------

    Project     : PTX1K
    Module      : NSC
    File        : ptxNSC_CE.h

    Description :
*/

#ifndef COMPS_NSC_NSC_CE_PTXNSC_CE_H_
#define COMPS_NSC_NSC_CE_PTXNSC_CE_H_

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */
#include "ptxStatus.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */

/*
 * Forward declaration
 */
struct ptxNSC;

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */

/**
 * \brief Function used to set up Routing Table for HCE application. All protocols and technologies go to Host.
 *
 * \param[in]   nscCtx              Pointer to an initialized instance of the NSC.
 *
 * \return Status, indicating whether the operation was successful. See ptxStatus_t.
 *
 */
ptxStatus_t ptxNSC_Set_Listen_RoutingTable_HCE ( struct ptxNSC *nscCtx );

#ifdef __cplusplus
}
#endif

#endif /* Guard */

