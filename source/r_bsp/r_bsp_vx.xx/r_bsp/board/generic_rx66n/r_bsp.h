/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_bsp.h
* H/W Platform : GENERIC_RX66N
* Description  : Has the header files that should be included for this platform.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 08.10.2019 1.00     First Release
*         : 23.04.2021 1.01     Added the include of fsp_common_api.h and r_fsp_error.h.
*         : 30.11.2021 1.02     Modified the include file.
*         : 26.02.2025 1.03     Changed the disclaimer.
***********************************************************************************************************************/

/* Make sure that no other platforms have already been defined. Do not touch this! */
#ifdef  PLATFORM_DEFINED
#error  "Error - Multiple platforms defined in platform.h!"
#else
#define PLATFORM_DEFINED
#endif

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************************************
INCLUDE APPROPRIATE MCU AND BOARD FILES
***********************************************************************************************************************/
#include    "r_bsp_config.h"
#include    "mcu/all/r_bsp_common.h"
#include    "mcu/all/r_rx_compiler.h"

#include    "r_bsp_interrupt_config.h"

#include    "mcu/all/lowlvl.h"
#include    "mcu/all/lowsrc.h"
#include    "mcu/all/r_bsp_mcu_startup.h"

#if defined(__CCRX__)
#include    "mcu/rx66n/register_access/ccrx/iodefine.h"
#elif defined(__GNUC__)
#include    "mcu/rx66n/register_access/gnuc/iodefine.h"
#elif defined(__ICCRX__)
#include    "mcu/rx66n/register_access/iccrx/iodefine.h"
#endif /* defined(__CCRX__), defined(__GNUC__), defined(__ICCRX__) */
#include    "mcu/rx66n/r_bsp_cpu.h"
#include    "mcu/rx66n/r_bsp_locking.h"
#include    "mcu/rx66n/mcu_clocks.h"
#include    "mcu/rx66n/mcu_info.h"
#include    "mcu/rx66n/mcu_init.h"
#include    "mcu/rx66n/mcu_interrupts.h"
#include    "mcu/rx66n/mcu_locks.h"
#include    "mcu/rx66n/mcu_mapped_interrupts_private.h"
#include    "mcu/rx66n/mcu_mapped_interrupts.h"
#include    "mcu/rx66n/vecttbl.h"

#include    "board/generic_rx66n/hwsetup.h"

#include    "mcu/all/r_bsp_interrupts.h"
#include    "mcu/all/r_bsp_software_interrupt.h"
#include    "mcu/all/r_rx_intrinsic_functions.h"
#include    "mcu/all/r_rtos.h"

#include    "mcu/all/fsp_common_api.h"
#include    "mcu/all/r_fsp_error.h"

#ifdef __cplusplus
}
#endif

#ifndef BSP_BOARD_GENERIC_RX66N
#define BSP_BOARD_GENERIC_RX66N

#endif /* BSP_BOARD_GENERIC_RX66N */

