/***********************************************************************************************************************
* Copyright (c) 2013 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_private.h
* Description  : Definitions internal to long queue module
************************************************************************************************************************
* History : DD.MM.YYYY Version Description   
*         : 11.12.2013 1.0     Initial Release
*         : 30.09.2015 1.50    Added BSP dependency
*         : 15.03.2025 2.01    Updated disclaimer
***********************************************************************************************************************/

#ifndef LONGQ_PRIVATE_H
#define LONGQ_PRIVATE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/


/*****************************************************************************
Typedef definitions
******************************************************************************/

/* QUEUE CONTROL BLOCK */

typedef struct st_longq_ctrl    // Long Queue Control Block (for handle)
{
    uint32_t    *buffer;        // pointer to buffer
    uint16_t    size;           // buffer size
    uint16_t    count;          // number of entries in queue
    uint16_t    in_index;       // index used by Put function to add data
    uint16_t    out_index;      // index used by Get function to remove data
    bool        ignore_ovfl;    // store continuously if true. when false, generate error on queue full
} longq_ctrl_t;


#endif /* LONGQ_PRIVATE_H */
