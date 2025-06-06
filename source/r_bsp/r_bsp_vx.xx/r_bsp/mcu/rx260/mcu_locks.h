/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : mcu_locks.h
* Device(s)    : RX260
* Description  : This source file has 1 lock per MCU resource.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 31.05.2024 1.00     First Release
*         : 26.02.2025 1.01     Changed the disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Gets MCU configuration information. */
#include "r_bsp_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Multiple inclusion prevention macro */
#ifndef MCU_LOCKS_H
#define MCU_LOCKS_H

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* This enum defines all of the available hardware locks for this MCU. If you delete an entry out of this list then you
   will decrease the size of the locks array but will not be able to use that lock. For example, if your design is not
   using CAN at all then you can safely remove the BSP_LOCK_CAN# entries below. */
typedef enum
{
    BSP_LOCK_BSC = 0,
    BSP_LOCK_CAC,
    BSP_LOCK_CMPB,
    BSP_LOCK_CMT,
    BSP_LOCK_CMT0,
    BSP_LOCK_CMT1,
    BSP_LOCK_CMT2,
    BSP_LOCK_CMT3,
    BSP_LOCK_CRC,
    BSP_LOCK_CTSU,
    BSP_LOCK_DA,
    BSP_LOCK_DMAC,
    BSP_LOCK_DMAC0,
    BSP_LOCK_DMAC1,
    BSP_LOCK_DMAC2,
    BSP_LOCK_DMAC3,
    BSP_LOCK_DOC,
    BSP_LOCK_DTC,
    BSP_LOCK_ELC,
    BSP_LOCK_FLASH,
    BSP_LOCK_GPTW0,
    BSP_LOCK_GPTW1,
    BSP_LOCK_GPTW2,
    BSP_LOCK_GPTW3,
    BSP_LOCK_GPTW4,
    BSP_LOCK_GPTW5,
    BSP_LOCK_GPTW6,
    BSP_LOCK_GPTW7,
    BSP_LOCK_IRQ0,
    BSP_LOCK_IRQ1,
    BSP_LOCK_IRQ2,
    BSP_LOCK_IRQ3,
    BSP_LOCK_IRQ4,
    BSP_LOCK_IRQ5,
    BSP_LOCK_IRQ6,
    BSP_LOCK_IRQ7,
    BSP_LOCK_ICU,
    BSP_LOCK_IWDT,
    BSP_LOCK_LPT,
    BSP_LOCK_MPC,
    BSP_LOCK_MPU,
    BSP_LOCK_POEG,
    BSP_LOCK_RAM,
    BSP_LOCK_REMC0,
    BSP_LOCK_RIIC0,
    BSP_LOCK_RSCI0,
    BSP_LOCK_RSCI8,
    BSP_LOCK_RSCI9,
    BSP_LOCK_RSPI0,
    BSP_LOCK_RTC,
    BSP_LOCK_RTCB,
    BSP_LOCK_S12AD,
    BSP_LOCK_SCI1,
    BSP_LOCK_SCI5,
    BSP_LOCK_SCI6,
    BSP_LOCK_SCI12,
    BSP_LOCK_SYSTEM,
    BSP_LOCK_TEMPS,
    BSP_LOCK_TMR0,
    BSP_LOCK_TMR1,
    BSP_LOCK_TMR2,
    BSP_LOCK_TMR3,
    BSP_LOCK_TMR01,
    BSP_LOCK_TMR23,
    BSP_LOCK_WDT,
    BSP_LOCK_SWINT,
    BSP_NUM_LOCKS //This entry is not a valid lock. It is used for sizing g_bsp_Locks[] array below. Do not touch!
} mcu_lock_t;

typedef struct
{
    /* The actual lock. int32_t is used because this is what the xchg() instruction takes as parameters. */
    int32_t     lock;

    /* Could add a ID for locking and unlocking. In this could protect against any function being able to unlock. */
} bsp_lock_t;

/***********************************************************************************************************************
Error checking
***********************************************************************************************************************/
#if BSP_CFG_USER_LOCKING_ENABLED == 0
#undef  BSP_CFG_USER_LOCKING_TYPE
#define BSP_CFG_USER_LOCKING_TYPE       bsp_lock_t
#else
    #if !defined(BSP_CFG_USER_LOCKING_TYPE)
    #error "R_BSP ERROR - If you are using your own locking mechanism then you must define BSP_CFG_USER_LOCKING_TYPE in r_bsp_config.h."
    #endif
#endif

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
extern BSP_CFG_USER_LOCKING_TYPE g_bsp_Locks[];

#endif /* MCU_LOCKS_H */

