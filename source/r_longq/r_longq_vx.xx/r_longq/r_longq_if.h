/***********************************************************************************************************************
* Copyright (c) 2013 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_longq_if.h
* Description  : Functions for using 32-bit queues/circular buffers 
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.12.2013 1.00    Initial Release
*         : 21.07.2014 1.10    Removed BSP dependency for parameter checking
*         : 11.26.2014 1.20    Updated to include RX113 in the supported MCUs
*         : 01.23.2015 1.30    Updated to version 1.30 for RX71M release
*         : 03.04.2015 1.40    Updated to version 1.30 for RX71M release
*         : 30.09.2015 1.50    Added BSP dependency
*         : 29.01.2016 1.60    Updated version to 1.60 for correspondence to RX Family
*         : 01.06.2018 1.70    Updated version to 1.70
*         : 03.12.2018 1.71    Updated version to 1.71 for update of xml file.
*         : 07.02.2019 1.80    Updated version to 1.80.
*         : 10.06.2020 1.81    Updated version to 1.81.
*         : 30.11.2020 1.82    Updated version to 1.82 for e2studio 2020-10 support.
*         : 29.10.2021 1.90    Updated for queue protection.
*                              Updated for critical section protection.
*         : 30.11.2022 2.00    Updated and added new demo project.
*         : 15.03.2025 2.01    Updated disclaimer
***********************************************************************************************************************/

#ifndef LONGQ_IF_H
#define LONGQ_IF_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"
#include "r_longq_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Version Number of API. */
#define LONGQ_VERSION_MAJOR (2)
#define LONGQ_VERSION_MINOR (01)

#if ((LONGQ_CFG_CRITICAL_SECTION == 1)||(LONGQ_CFG_PROTECT_QUEUE == 1))
#if (BSP_CFG_RUN_IN_USER_MODE == 1)
    #error "Protect circular buffer must use in supervisor mode."
#endif
#endif

/*****************************************************************************
Typedef definitions
******************************************************************************/

typedef enum e_longq_err        // LONGQ API error codes
{
    LONGQ_SUCCESS = 0,
    LONGQ_ERR_NULL_PTR,         // received null ptr; missing required argument
    LONGQ_ERR_INVALID_ARG,      // argument is not valid for parameter
    LONGQ_ERR_MALLOC_FAIL,      // can't allocate memory for ctrl block; increase heap
    LONGQ_ERR_NO_MORE_CTRL_BLKS,  // no more control blocks, increase LONGQ_MAX_CTRL_BLKS
    LONGQ_ERR_QUEUE_FULL,       // queue full; cannot add another entry
    LONGQ_ERR_QUEUE_EMPTY       // queue empty; no data to fetch
} longq_err_t;


/* BYTE QUEUE HANDLE */

typedef struct st_longq_ctrl *  longq_hdl_t;


/*****************************************************************************
Public Functions
******************************************************************************/
longq_err_t R_LONGQ_Open(uint32_t * const       p_buf,
                         uint16_t const         size,
                         bool const             ignore_overflow,
                         longq_hdl_t * const    p_hdl);

longq_err_t R_LONGQ_Close(longq_hdl_t const hdl);

longq_err_t R_LONGQ_Put(longq_hdl_t const   hdl,
                        uint32_t const      datum);

longq_err_t R_LONGQ_Get(longq_hdl_t const   hdl,
                        uint32_t * const    p_datum);

longq_err_t R_LONGQ_Flush(longq_hdl_t const hdl);

longq_err_t R_LONGQ_Used(longq_hdl_t const  hdl,
                         uint16_t * const   p_cnt);

longq_err_t R_LONGQ_Unused(longq_hdl_t const    hdl,
                           uint16_t * const     p_cnt);

uint32_t R_LONGQ_GetVersion(void);


#endif /* LONGQ_IF_H */

