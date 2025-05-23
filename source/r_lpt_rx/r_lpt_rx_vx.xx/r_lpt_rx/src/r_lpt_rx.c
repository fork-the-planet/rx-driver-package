/**********************************************************************************************************************
* Copyright (c) 2016 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_lpt_rx.c
 * Version      : 5.01
 * Description  : Functions for using Low Power Timer
 **********************************************************************************************************************
 * History : DD.MM.YYYY Version Description  
 *         : 01.03.2016 1.00    First Release
 *         : 01.07.2016 1.10    Added support for RX130,RX230,RX231
 *         :                    Lock release then lpt_open() error occurred
 *         : 04.08.2016 1.11    Added command LPT_CMD_COUNT_RESET to R_LPT_Control()
 *         : 04.22.2019 1.23    Delete inline definition of GetVersion function
 *         : 10.06.2020 2.00    Added support for RX23W
 *                              Modified comment of API function to Doxygen style.
 *         : 25.09.2020 2.01    Added support for RX140
 *         : 31.03.2021 3.00    Added function R_LPT_InitChan, R_LPT_SetCMT, R_LPT_FinalChan, R_LPT_InitPWM
 *                              Added command LPT_CMD_PWM_START and LPT_CMD_PWM_STOP to R_LPT_Control()
 *         : 31.01.2022 3.01    Fixed R_LPT_Open function
 *         : 31.07.2024 5.00    Added support for RX260, RX261
 *         : 20.03.2025 5.01    Changed the disclaimer in program sources.
 *********************************************************************************************************************/
/**********************************************************************************************************************
  Includes <System Includes> , "Project Includes"
**********************************************************************************************************************/
/* Access to peripherals and board defines. */
#include "platform.h"

/* Defines for LPT support */
#include "r_lpt_rx_if.h"

/* Include specifics for chosen MCU. */
#include "r_lpt_rx_private.h"

/**********************************************************************************************************************
 * Function Name: R_LPT_Open
 *****************************************************************************************************************/ /**
 * @brief The function initializes the LPT FIT module. This function must be called before calling any other API        
 *        functions.
 * @param[in] lpt_period
 *            LPT cycle (unit: microsecond)
 * @retval    LPT_SUCCESS: Processing completed successfully.
 * @retval    LPT_ERR_LOCK_FUNC: Operating. LPT has been used.
 * @retval    LPT_ERR_INVALID_ARG: Argument has an invalid value.
 * @details   The initialization is performed to start LPT operation and then the LPT cycle specified with the argument
 *            is set.\n
 *            Operations included in the initialization are as follows:
 *            \li Enables exiting software standby mode using the LPT.
 *            \li Sets the LPT clock source and the division ratio.
 *            \li Sets the LPT cycle.
 *            \li Provides the LPT clock.
 *            \li Resets the LPT.
 * @note      Call this function while the LPT clock source oscillation is stabilized.\n
 *            When the sub-clock oscillator is selected as the LPT clock source, the LPT cycle must be specified from
 *            92 to 64000488. But if using device that supported "no clock division", the LPT cycle must be specified
 *            from 46 to 64000488.\n When the IWDT-dedicated on-chip oscillator is selected as the LPT clock source,
 *            the LPT cycle must be specified from 200 to 139811199. But if using device that supported
 *            "no clock division", the LPT cycle must be specified from 100 to 139811199.\n
 *            When the LOCO oscillator is selected as the LPT clock source, the LPT cycle must be
 *            specified from 2 to 2097167.\n
 *            When the IWDT-dedicated on-chip oscillator is selected as the LPT clock source, set the OFS0.IWDTSLCSTP
 *            bit to 0 (counting stop is disabled) in IWDT auto-start mode, and set the IWDTCSTPR.SLCSTP bit to 0
 *            (counting stop is disabled) in other modes.\n
 *            When the LOCO clock is selected as the LPT clock source , set the LFOCR.LOFXIN bit to 1.
 *            (counting stop is disabled) in other modes.\n
 *            MCU executes the program after MCU waits for the stability time for Main Clock Oscillator Wait Control
 *            Register (SMOSCWTCR) when MCU is resumed from software standby mode.
 *            Set snooze mode before calling this function when using snooze mode.
 *            If wakeup from software standby mode using low-power timer is enabled, disable entry snooze mode setting.

 */
lpt_err_t R_LPT_Open(uint32_t const lpt_period)
{
    lpt_err_t   err = LPT_SUCCESS;
    bool        chk;

    /*  ---- LPT HARDWARE LOCK ---- */
    chk = r_lpt_mcu_hardware_lock();

    if (false == chk)
    {
        /* Lock has already been acquired by another task. Needs to try again later. */
        return LPT_ERR_LOCK_FUNC;
    }
    else
    {
        err = lpt_open(lpt_period);

        if (LPT_SUCCESS != err)
        {
            r_lpt_mcu_hardware_unlock();
        }
    }
    return (err);
}
/*********************************************************************************************************************
 * End of function R_LPT_Open()
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_LPT_Close
 *****************************************************************************************************************/ /**
 * @brief This function performs processing to stop the LPT.
 * @retval    LPT_SUCCESS: Processing completed successfully.
 * @details   The following operations are performed to stop the LPT.
 *            \li Stops the LPT.
 *            \li Resets the LPT if the LPT clock is provided.
 *            \li Stops the LPT clock.
 *            \li Resets the value of LPT compare match 0.
 *            \li Resets the LPT cycle.
 *            \li Resets low-power timer control register 1.
 *            \li Disables exiting software standby mode using the LPT.
 * @note      Configure the LPT settings in the R_LPT_Open function first, wait one or more cycles of the LPT clock
 *            source, and then call this function.
 */
lpt_err_t R_LPT_Close(void)
{
    /* Calls the API function. */
    lpt_close();

    /* ---- Release hardware locks for the LPT. ---- */
    r_lpt_mcu_hardware_unlock();

    return (LPT_SUCCESS);
}
/**********************************************************************************************************************
 * End of function R_LPT_Close()
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_LPT_Control
 *****************************************************************************************************************/ /**
 * @brief This function performs processing to start, stop, or reset LPT count and start and stop PWM output.
 * @param[in] cmd
 *            Command to be executed (see 2.9, Parameters in the application note).
 * @retval    LPT_SUCCESS: Processing completed successfully.
 * @retval    LPT_ERR_INVALID_ARG: Argument has an invalid value.
 * @retval    LPT_ERR_CONDITION_NOT_MET: Condition not met.
 * @details   This API function controls start/stop of LPT count and start and stop of PWM output.\n
 *            The counter reset command (LPT_CMD_COUNT_RESET) must be executed while LPT count stops. If
 *            LPT_CMD_COUNT_RESET is executed during counting, LPT_ERR_CONDITION_NOT_MET is returned.
 *            The PWM start/stop command (LPT_CMD_PWM_START/LPT_CMD_PWM_STOP) must be executed while LPT count stops.
 *            If LPT_CMD_PWM_START or LPT_CMD_PWM_STOP is executed during counting,
 *            LPT_ERR_CONDITION_NOT_MET is returned. The LPT cycle and compare match 1 cycle must be equal
 *            when executing the PWM start command. If the values of LPT cycle and compare match 1 cycle are not equal,
 *            LPT_ERR_CONDITION_NOT_MET is returned. LPT_CMD_PWM_START and LPT_CMD_PWM_STOP command can only execute
 *            on some device. If LPT_CMD_PWM_START or LPT_CMD_PWM_STOP is executed on unsupported device,
 *            LPT_ERR_INVALID_ARG is returned.
 * @note      Call this function after the LPT have been configured in the R_LPT_Open and R_LPT_InitChan function.
 */
lpt_err_t R_LPT_Control(lpt_cmd_t const cmd)
{
    lpt_err_t   err = LPT_SUCCESS;

    /* Command control */
    switch (cmd)
    {

        /* start LPT count */
        case (LPT_CMD_START):
            lpt_start();
            break;

        /* stop LPT count */
        case (LPT_CMD_STOP):
            lpt_stop();
            break;

        /* reset LPT count */
        case (LPT_CMD_COUNT_RESET):
            err = lpt_count_reset();
            break;

/* PWM feature supported from LPTa */
#if (LPT_VERSION == 0x0061)
        /* start PWM output */
        case (LPT_CMD_PWM_START):
            err = lpt_pwm_start();
            break;

        /* stop PWM output */
        case (LPT_CMD_PWM_STOP):
            err = lpt_pwm_stop();
            break;
#endif /* (LPT_VERSION == 0x0061) */

        /* other */
        default:
            err = LPT_ERR_INVALID_ARG;
            break;
    }

    return err;
}
/**********************************************************************************************************************
 * End of function R_LPT_Control()
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_LPT_InitChan
 *****************************************************************************************************************/ /**
 * @brief This function enable compare match and sets the value of LPT compare match.
 * @param[in] chan
 *            Channel to initialize.
 *            cmt_period
 *            LPT Compare match timer (unit: microsecond)
 * @retval    LPT_SUCCESS: Processing completed successfully.
 * @retval    LPT_ERR_INVALID_ARG: Argument has an invalid value.
 * @retval    LPT_ERR_CONDITION_NOT_MET: Condition not met.
 * @retval    LPT_ERR_INVALID_CH: Selected channel is invalid.
 * @details   This API function performed to enable compare match and sets the value of LPT compare match
 *            with the argument.\n
 *            Set cmt_period to the value corresponding to the clock source. See the R_LPT_Open for more information.
 *            Set the value of cmt_period to a value less than or equal the LPT period.
 *            If the value of cmt_period is greater than the LPT period, LPT_ERR_INVALID_ARG is returned.
 *            This function must be called while LPT count stops.
 *            If this function is called during counting, LPT_ERR_CONDITION_NOT_MET is returned.
 *            If the PWM output is enabled and the selected channel is 1, set the compare match cycle 
 *            to the equal value as the LPT cycle. If the compare match cycle 1 is set to a value different from
 *            the LPT cycle when the PWM output is enabled, LPT_ERR_CONDITION_NOT_MET is returned.
 *            Channel 1 can only be selected on some devices. If channel 1 is selected on unsupported device,
 *            LPT_ERR_INVALID_CH is returned.
 *            Operations included in the initialization are as follows:
 *            \li Enables compare match for the selected channel.
 *            \li Sets the value of LPT compare match for the selected channel.
 * @note      None
 */
lpt_err_t R_LPT_InitChan(lpt_ch_t chan, uint32_t const cmt_period)
{
    lpt_err_t   err = LPT_SUCCESS;
    err = lpt_initchan(chan, cmt_period);

    return (err);
}
/**********************************************************************************************************************
 * End of function R_LPT_InitChan()
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_LPT_SetCMT
 *****************************************************************************************************************/ /**
 * @brief This function set the value of LPT compare match.
 * @param[in] chan
 *            Channel to initialize.
 *            cmt_period
 *            LPT Compare match timer (unit: microsecond)
 * @retval    LPT_SUCCESS: Processing completed successfully.
 * @retval    LPT_ERR_INVALID_ARG: Argument has an invalid value.
 * @retval    LPT_ERR_CONDITION_NOT_MET: Condition not met.
 * @retval    LPT_ERR_INVALID_CH: Selected channel is invalid.
 * @details   This API function performed to set the value of LPT compare match with the argument.\n
 *            Set cmt_period to the value corresponding to the clock source. See the R_LPT_Open for more information.
 *            Set the value of cmt_period to a value less than or equal the LPT period.
 *            If the value of cmt_period is greater than the LPT period, LPT_ERR_INVALID_ARG is returned.
 *            This function must be called while LPT count stops. If this function is called during counting,
 *            LPT_ERR_CONDITION_NOT_MET is returned. But if selected cannel 0 and PWM output is enable,
 *            this function could call.
 *            If the PWM output is enabled and the selected channel is 1, set the compare match cycle 
 *            to the equal value as the LPT cycle. If the compare match cycle 1 is set to a value different from
 *            the LPT cycle when the PWM output is enabled, LPT_ERR_CONDITION_NOT_MET is returned.
 *            Channel 1 can only be selected on some devices. If channel 1 is selected on an unsupported device,
 *            LPT_ERR_INVALID_CH is returned.
 * @note      None
 */
lpt_err_t R_LPT_SetCMT(lpt_ch_t chan, uint32_t const cmt_period)
{
    lpt_err_t   err = LPT_SUCCESS;
    err = lpt_setcmt(chan, cmt_period);

    return (err);
}
/**********************************************************************************************************************
 * End of function R_LPT_SetCMT()
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_LPT_FinalChan
 *****************************************************************************************************************/ /**
 * @brief This function finalizes compare match.
 * @param[in] chan
 *            Channel to finalize.
 * @retval    LPT_SUCCESS: Processing completed successfully.
 * @retval    LPT_ERR_CONDITION_NOT_MET: Condition not met.
 * @retval    LPT_ERR_INVALID_CH: Selected channel is invalid.
 * @details   This API function performed to finalize compare match selected channel.\n
 *            This function must be called while LPT count stops.
 *            If this function is called during counting, LPT_ERR_CONDITION_NOT_MET is returned.
 *            Channel 1 can only be selected on some devices. If channel 1 is selected on unsupported device,
 *            LPT_ERR_INVALID_CH is returned.
 * @note      None
 */
lpt_err_t R_LPT_FinalChan(lpt_ch_t chan)
{
    lpt_err_t   err = LPT_SUCCESS;
    err = lpt_finalchan(chan);

    return (err);
}
/**********************************************************************************************************************
 * End of function R_LPT_FinalChan()
 *********************************************************************************************************************/

/* PWM feature supported from LPTa */
#if (LPT_VERSION == 0x0061)
/**********************************************************************************************************************
 * Function Name: R_LPT_InitPWM
 *****************************************************************************************************************/ /**
 * @brief This function sets the PWM configuration.
 * @param[in] chan
 *            LPT channel.
 *
 *            p_config
 *            PWM configuration. (see enumeration below)
 * @code
typedef struct st_lpt_pwm_cfg                   LPT PWM output configuration.
{
    lpt_pwm_polarity_t output_polarity;         Output polarity select.
    lpt_pwm_level_t output_level;               Output Level select.
}lpt_pwm_cfg_t;
 * @endcode
 * @retval    LPT_SUCCESS: Processing completed successfully.
 * @retval    LPT_ERR_INVALID_ARG: Argument has an invalid value.
 * @retval    LPT_ERR_CONDITION_NOT_MET: Condition not met.
 * @retval    LPT_ERR_INVALID_CH: Selected channel is invalid.
 * @retval    LPT_ERR_NULL_PTR: p_config is NULL.
 * @details   This API function sets the PWM configuration. This function must be executed while LPT count stops.
 *            If this function is executed during counting, LPT_ERR_CONDITION_NOT_MET is returned.
 *            PWM function can only executed on channel 0. If this function is executed with channel 1 selected,
 *            LPT_ERR_INVALID_CH is returned.
 *            Set a valid value in the argument p_config. If this function is executed 
 *            with an invalid value in p_config, LPT_ERR_NULL_PTR is returned.
 * @note      None
 */
lpt_err_t R_LPT_InitPWM(lpt_ch_t chan, lpt_pwm_cfg_t * const p_config)
{
    lpt_err_t   err = LPT_SUCCESS;

    /* Check arguments */
#if LPT_CFG_PARAM_CHECKING_ENABLE
    /* Check argument p_config */
    if (NULL == p_config)
    {
        return LPT_ERR_NULL_PTR;
    }
#endif

    err = lpt_initpwm(chan, p_config);
    return (err);
}
/**********************************************************************************************************************
 * End of function R_LPT_InitPWM()
 *********************************************************************************************************************/
#endif /* (LPT_VERSION == 0x0061) */

/**********************************************************************************************************************
 * Function Name: R_LPT_GetVersion
 *****************************************************************************************************************/ /**
 * @brief This function returns the module version.
 * @return    Version number
 * @details   Returns the module version number. The version number is encoded where the top 2 bytes are the major
 *            version number and the bottom 2 bytes are the minor version number.
 * @note      None
 */
uint32_t  R_LPT_GetVersion(void)
{
    return ((LPT_VERSION_MAJOR << 16) | LPT_VERSION_MINOR);;
}
/**********************************************************************************************************************
 * End of function R_LPT_GetVersion()
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * End of File
 *********************************************************************************************************************/
