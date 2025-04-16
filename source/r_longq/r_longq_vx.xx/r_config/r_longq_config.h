/***********************************************************************************************************************
* Copyright (c) 2013 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name     : r_longq_config.h
* Description   : Configures the 32-bit queue memory allocation
************************************************************************************************************************
* History : DD.MM.YYYY Version Description  
*         : 11.12.2013 1.00    Initial Release
*         : 21.07.2014 1.10    Removed BSP dependency for parameter checking
*         : 11.26.2014 1.20    Updated to include RX113 in the supported MCUs
*         : 30.09.2015 1.50    Added BSP dependency
*         : 01.06.2018 1.70    Changed the default value of the following macro definition.
*                               - LONGQ_CFG_MAX_CTRL_BLKS - Changed the default value from 2 to 32.
*         : 29.10.2021 1.90    Updated for queue protection.
*                              Updated for critical section protection.
*         : 15.03.2025 2.01    Updated disclaimer
***********************************************************************************************************************/
#ifndef LONGQ_CONFIG_H
#define LONGQ_CONFIG_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
   Available settings:
   BSP_CFG_PARAM_CHECKING_ENABLE:
       Utilizes the system default setting
   1:
       Includes parameter checking
   0:
       Compiles out parameter checking
*/
#define LONGQ_CFG_PARAM_CHECKING_ENABLE     (BSP_CFG_PARAM_CHECKING_ENABLE)

/* SPECIFY IF SHOULD USE MALLOC() TO ALLOCATE MEMORY FOR QUEUE CONTROL BLOCKS */
#define LONGQ_CFG_USE_HEAP_FOR_CTRL_BLKS    (0)

/* SPECIFY NUMBER OF STATIC QUEUE CONTROL BLOCKS TO SUPPORT */
/* valid only when LONGQ_USE_HEAP_FOR_CTRL_BLKS is set to 0 */
#define LONGQ_CFG_MAX_CTRL_BLKS             (32)

/* Selects to use disable interrupt to protect queue. */
#define LONGQ_CFG_PROTECT_QUEUE             (0)

/* Selects to use disable interrupt to protect critical section. */
#define LONGQ_CFG_CRITICAL_SECTION          (0)

#endif /* LONGQ_CONFIG_H */
