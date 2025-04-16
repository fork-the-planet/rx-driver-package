/***********************************************************************************************************************
* Copyright (c) 2022 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

/***********************************************************************************************************************
 * File Name    : r_ri3c_rx_data.h
 * Description  : Renesas RX FIT RI3C driver's data header file.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 15.08.2022 1.00    First release
 *                              Supported for RX26T.
 *         : 15.03.2025 1.12    Updated disclaimer
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "r_ri3c_rx_if.h"

#ifndef RI3C_DATA_H
#define RI3C_DATA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if (BSP_MCU_RX26T)
extern ri3c_instance_t g_ri3c0;

extern ri3c_instance_ctrl_t g_ri3c0_ctrl;
extern ri3c_cfg_t           g_ri3c0_cfg;

#ifndef g_ri3c0_callback
/**********************************************************************************************************************
 * Function Name: g_ri3c0_callback
 * Description  : Callback function of RI3C FIT Module
 * Arguments    : ri3c_callback_args_t const *const p_args
 * Return Value : None
 *********************************************************************************************************************/
void g_ri3c0_callback (ri3c_callback_args_t const * const p_args);
#endif
#endif /* (BSP_MCU_RX26T) */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* RI3C_DATA_H */
