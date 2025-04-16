/*
* Copyright (c) 2020-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef _MESH_SYSTEMTIME_
#define _MESH_SYSTEMTIME_

/*******************************************************************************
* Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "platform.h"
#include "r_ble_rx23w_config.h"

/*******************************************************************************
* Compilation Switches
*******************************************************************************/
#define SYSTEMTIME_EN                   (0)
#define SYSTEMTIME_STRING_EN            (1)

#if BLE_CFG_CMD_LINE_EN
#undef  SYSTEMTIME_EN
#define SYSTEMTIME_EN                   (1)
#endif /* BLE_CFG_CMD_LINE_EN */

#if SYSTEMTIME_EN

/*******************************************************************************
* Prototype declarations
*******************************************************************************/
/**
 *  \brief API to initialize System Time driver.
 *
 *  \par Description
 *  System Timer Driver uses two 8bit-Timers (TMR2 and TMR3) in 16bit Count Mode.
 *  Two timers clear the 16bit counter and interrupt occurs every 16,768[ms].
 *
 *  \return 0, if both TMR2 and TMR3 are available.
 *  1 or 2, if TMR2 or/and TMR3 is not available.
 *
 * \attention System Time driver assumes that PCLKB is 32MHz clock.
 */
uint8_t mesh_systemtime_init(void);

/**
 *  \brief API to check 8bit-Timers for System Time are active.
 *
 *  \return 1, if 8bit-Timers are counting.
 *  0, if 8bit-Timers stop.
 */
uint8_t mesh_systemtime_is_active(void);

/**
 *  \brief API to read Sytem Time.
 *
 *  \par Description
 *  System Time is 32bit-length and counted by millisecond step.
 *  That is why the sytem time wrap-around every 1193 hours.
 *
 * \return 32bit-length millisecond time
 */
uint32_t mesh_systemtime_read(void);

#if SYSTEMTIME_STRING_EN
/**
 *  \brief API to read Sytem Time String.
 *
 *  \par Description
 *  System Time String is represented in the following format:
 *   H:MM:SS.mmm, max 15characters followed by null character
 *     H: 0 to 1193 hours
 *     M: 0 to 59 minutes
 *     S: 0 to 50 seconds
 *     m: 0 to 999 milliseconds
 *
 * \return system time string
 */
char * mesh_systemtime_read_string(void);
#endif /* SYSTEMTIME_STRING_EN */

#endif /* SYSTEMTIME_EN */

#endif /* _MESH_SYSTEMTIME_ */
