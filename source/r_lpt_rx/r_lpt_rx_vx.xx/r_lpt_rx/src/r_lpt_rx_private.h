/**********************************************************************************************************************
* Copyright (c) 2016 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_lpt_rx_private.h
 * Version      : 5.01
 * Description  : Functions for using Low Power Timer
 **********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 01.03.2016 1.00    First Release
 *         : 01.07.2016 1.10    Added support for RX130,RX230,RX231
 *         : 04.08.2016 1.11    Added command LPT_CMD_COUNT_RESET to R_LPT_Control()
 *         : 10.06.2020 2.00    Added support for RX23W
 *         : 31.03.2021 3.00    Added function R_LPT_InitChan, R_LPT_SetCMT, R_LPT_FinalChan, R_LPT_InitPWM
 *                              Added command LPT_CMD_PWM_START and LPT_CMD_PWM_STOP to R_LPT_Control()
 *         : 31.05.2023 4.00    Change parameter check definition.
 *         : 31.07.2024 5.00    Added support for RX260, RX261
 *         : 20.03.2025 5.01    Changed the disclaimer in program sources.
*********************************************************************************************************************/

/*******************************************************************************
  Includes   <System Includes> , "Project Includes"
*******************************************************************************/
/* Defines for LPT support */
#include "r_lpt_rx_if.h"

/*******************************************************************************
  Macro definitions
*******************************************************************************/
#ifndef LPT_PRIVATE_H
#define LPT_PRIVATE_H

/*******************************************************************************
Private global variables and functions
*******************************************************************************/
/*****************************************************************************
* Function Name: r_lpt_mcu_hardware_lock
* Description  : Attempt to acquire the lock that has been sent in.
* Arguments    : none
* Return Value : true                   ; Successful operation
*              : false                  ; error operation
******************************************************************************/
bool r_lpt_mcu_hardware_lock (void);

/*****************************************************************************
* Function Name: r_lpt_mcu_hardware_unlock
* Description  : Release hold on lock.
* Arguments    : none
* Return Value : none
******************************************************************************/
void r_lpt_mcu_hardware_unlock (void);

/*****************************************************************************
* Function Name: lpt_open
* Description  : Initialization for using the LPT.
* Arguments    : period
* Return Value : LPT_SUCCESS
*                LPT_ERR_INVALID_ARG
******************************************************************************/
lpt_err_t lpt_open (uint32_t const period);

/*****************************************************************************
* Function Name: lpt_close
* Description  : Releases the LPT function.
* Arguments    : None
* Return Value : None
******************************************************************************/
void lpt_close (void);

/*****************************************************************************
* Function Name: lpt_start
* Description  : Starts the LPT.
* Arguments    : None
* Return Value : None
******************************************************************************/
void lpt_start (void);

/*****************************************************************************
* Function Name: lpt_stop
* Description  : Stops the LPT.
* Arguments    : None
* Return Value : None
******************************************************************************/
void lpt_stop (void);

/*****************************************************************************
* Function Name: lpt_count_reset
* Description  : Reset the LPT.
* Arguments    : None
* Return Value : LPT_SUCCESS
*                LPT_ERR_CONDITION_NOT_ERR
******************************************************************************/
lpt_err_t lpt_count_reset (void);

/* PWM feature supported from LPTa */
#if (LPT_VERSION == 0x0061)
/*****************************************************************************
* Function Name: lpt_pwm_start
* Description  : Starts the PWM output.
* Arguments    : None
* Return Value : LPT_SUCCESS
*                LPT_ERR_CONDITION_NOT_MET
******************************************************************************/
lpt_err_t lpt_pwm_start (void);

/*****************************************************************************
* Function Name: lpt_pwm_stop
* Description  : Stops the PWM output.
* Arguments    : None
* Return Value : LPT_SUCCESS
*                LPT_ERR_CONDITION_NOT_MET
******************************************************************************/
lpt_err_t lpt_pwm_stop (void);
#endif /* (LPT_VERSION == 0x0061) */

/*****************************************************************************
* Function Name: lpt_initchan
* Description  : Initialize the LPT configuration.
* Arguments    : chan
*                cmt_period
* Return Value : LPT_SUCCESS
*                LPT_ERR_INVALID_ARG
*                LPT_ERR_CONDITION_NOT_MET
*                LPT_ERR_INVALID_CH
******************************************************************************/
lpt_err_t lpt_initchan (lpt_ch_t chan, uint32_t const cmt_period);

/*****************************************************************************
* Function Name: lpt_setcmt
* Description  : Set the value of compare match 0 or 1.
* Arguments    : chan
*                cmt_period
* Return Value : LPT_SUCCESS
*                LPT_ERR_INVALID_ARG
*                LPT_ERR_CONDITION_NOT_MET
*                LPT_ERR_INVALID_CH
******************************************************************************/
lpt_err_t lpt_setcmt (lpt_ch_t chan, uint32_t const cmt_period);

/*****************************************************************************
* Function Name: lpt_finalchan
* Description  : Finalize the LPT configuration.
* Arguments    : chan
* Return Value : LPT_SUCCESS
*                LPT_ERR_INVALID_ARG
*                LPT_ERR_CONDITION_NOT_MET
*                LPT_ERR_INVALID_CH
******************************************************************************/
lpt_err_t lpt_finalchan (lpt_ch_t chan);

/* PWM feature supported from LPTa */
#if (LPT_VERSION == 0x0061)
/*****************************************************************************
* Function Name: lpt_initpwm
* Description  : Sets the PWM configuration.
* Arguments    : chan
*                p_config
* Return Value : LPT_SUCCESS
*                LPT_ERR_INVALID_CH
*                LPT_ERR_CONDITION_NOT_MET
******************************************************************************/
lpt_err_t lpt_initpwm (lpt_ch_t chan, lpt_pwm_cfg_t * const p_config);
#endif /* (LPT_VERSION == 0x0061) */

#endif /* LPT_PRIVATE_H */
/**********************************************************************************************************************
 * End of File
 *********************************************************************************************************************/
