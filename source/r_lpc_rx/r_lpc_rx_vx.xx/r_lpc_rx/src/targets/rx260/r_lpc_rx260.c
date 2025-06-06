/***********************************************************************************************************************
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*********************************************************************************************************************
 * File Name    : r_lpc_rx260.c
 * Description  : Implementation of the LPC module for the RX260
 **********************************************************************************************************************/
/*********************************************************************************************************************
 * History : DD.MM.YYYY Version Description           
 *         : 28.06.2024 1.00    First Release
 *         : 01.11.2024 2.50    Moved the restrictions of PLL, PLL2 and main clock oscillator in middle-speed operation 
 *                              mode and middle-speed operation mode 2 to lpc_freq_range_check() and 
 *                              lpc_lowpower_activate_check() functions for RX260, RX261.
 *         : 15.03.2025 2.51    Updated disclaimer.
 **********************************************************************************************************************/

/*********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

#if defined(BSP_MCU_RX260)

/* Public interface header file for this package. */
#include "r_lpc_rx_if.h"
#include "r_lpc_rx_private.h"
#include "r_lpc_rx260_private.h"

/********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/

/********************************************************************************************************************
 Private global variables and functions
 *********************************************************************************************************************/
/* See cgc_init_local_data() for the initialization of these arrays */

static lpc_snooze_callback_set_t psnooze_release_callback;  //Snooze interrupt callback function

#if (LPC_CFG_PARAM_CHECKING_ENABLE == 1)
static uint32_t clock_frequency[6];    // Clock source frequencies used by lpc_clockhzget()
static uint32_t hoco_frequency[4];     // Possible HOCO frequencies; Indices 1&2&3 are not used for the RX260.

static uint32_t  lpc_clockhzget (lpc_system_clocks_t clock);
static lpc_err_t lpc_freq_range_check (lpc_operating_mode_t e_mode);
static lpc_err_t lpc_lowpower_activate_check (void);
#endif /* LPC_CFG_PARAM_CHECKING_ENABLE */

/********************************************************************************************************************
 * Function Name: lpc_operating_mode_set
 * Description  : This function will configure the MCU for the specified operating mode. In any of the operating
 *                modes, the CPU is running, but the maximum clock frequencies are limited based on the mode.
 *                The supported modes are listed in the lpc_operating_mode_t enum. The modes with the
 *                lower operating frequencies use regulator switches to reduce current draw. It is imperative
 *                that when switching to a higher clock frequency, the mode is changed first to support that
 *                frequency.
 * Arguments    : e_mode - Operating Mode
 *                    LPC_OP_HIGH_SPEED
 *                    LPC_OP_MIDDLE_SPEED
 *                    LPC_OP_MIDDLE_SPEED_2
 *                    LPC_OP_LOW_SPEED
 * Return Value : LPC_SUCCESS -
 *                LPC_ERR_CLOCK_EXCEEDED -
 *                    Clock exceeds the limit of current operating mode
 *                LPC_ERR_P_E_MODE -
 *                    The operation mode can't be changed in P/E mode.
 ********************************************************************************************************************/
lpc_err_t lpc_operating_mode_set(lpc_operating_mode_t e_mode)
{
#if (LPC_CFG_PARAM_CHECKING_ENABLE == 1)
    lpc_err_t err;

    /* Check FENTRY0(b0) and FENTRYD(b7) */
    if (0x0000 != (FLASH.FENTRYR.WORD & 0x0081))
    {
        return LPC_ERR_P_E_MODE;
    }

    err = lpc_freq_range_check(e_mode);
    if (LPC_SUCCESS != err)
    {
        return err;
    }
#endif

    switch (e_mode)
    {
        case LPC_OP_HIGH_SPEED:

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.SOPCCR.BIT.SOPCMTSF)
            {
                /* do not modify SOPCCR if a transition is ongoing */
            }
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.SOPCCR.BIT.SOPCM = 0x0;   // Set to High Speed/Medium Speed/Medium Speed2 Mode
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.SOPCCR.BIT.SOPCMTSF)
            {
                /* wait till transition is complete */
            }

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.OPCCR.BIT.OPCMTSF)
            {
                /* do not modify OPCCR if a transition is ongoing */
            }
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.OPCCR.BIT.OPCM = 0x0;     // Set to High Speed Mode
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.OPCCR.BIT.OPCMTSF)
            {
                /* wait till transition is complete */
            }
            break;
    
        case LPC_OP_MIDDLE_SPEED:

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.SOPCCR.BIT.SOPCMTSF)
            {
                /* do not modify SOPCCR if a transition is ongoing */
            }
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.SOPCCR.BIT.SOPCM = 0x0;   // Set to High Speed/Medium Speed/Medium Speed2 Mode
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.SOPCCR.BIT.SOPCMTSF)
            {
                /* wait till transition is complete */
            }

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.OPCCR.BIT.OPCMTSF)
            {
                /* do not modify OPCCR if a transition is ongoing */
            }
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.OPCCR.BIT.OPCM = 0x02;  // Set to Medium Speed Mode
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.OPCCR.BIT.OPCMTSF)
            {
                /* wait till transition is complete */
            }
            break;

        case LPC_OP_MIDDLE_SPEED_2:

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.SOPCCR.BIT.SOPCMTSF)
            {
                /* do not modify SOPCCR if a transition is ongoing */
            }
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.SOPCCR.BIT.SOPCM = 0x0;   // Set to High Speed/Medium Speed/Medium Speed2 Mode
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.SOPCCR.BIT.SOPCMTSF)
            {
                /* wait till transition is complete */
            }

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.OPCCR.BIT.OPCMTSF)
            {
                /* do not modify OPCCR if a transition is ongoing */
            }
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.OPCCR.BIT.OPCM = 0x04;  // Set to Medium Speed2 Mode
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.OPCCR.BIT.OPCMTSF)
            {
                /* wait till transition is complete */
            }
            break;

        case LPC_OP_LOW_SPEED:

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.SOPCCR.BIT.SOPCMTSF)
            {
                /* do not modify SOPCCR if a transition is ongoing */
            }
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.SOPCCR.BIT.SOPCM = 0x1;   // Set to Low Speed Mode
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

            /* WAIT_LOOP */
            while (LPC_TRANSITION_ONGOING == SYSTEM.SOPCCR.BIT.SOPCMTSF)
            {
                /* wait till transition is complete */
            }
            break;
        
        default:

            /* nothing here */
            break;
    }
    return LPC_SUCCESS;

}
/*********************************************************************************************************************
 End of function lpc_operating_mode_set
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Function Name: lpc_low_power_mode_configure
 * Description  : This function will configure the MCU for the specified Low Power Mode. In the Low Power Mode,
 *                the CPU is turned OFF and peripherals may be on or off depending on the mode. The supported
 *                low power modes are listed in the enum lpc_low_power_mode_t
 * Arguments    : e_mode - Low Power Mode
 *                    LPC_LP_SLEEP:
 *                    LPC_LP_DEEP_SLEEP:
 *                    LPC_LP_SW_STANDBY:
 *
 * Return Value : LPC_SUCCESS -
 ********************************************************************************************************************/
lpc_err_t lpc_low_power_mode_configure(lpc_low_power_mode_t e_mode)
{
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6) 
    bsp_int_ctrl_t int_ctrl;
#endif

    switch (e_mode)
    {
        case LPC_LP_SLEEP:
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.SBYCR.BIT.SSBY = 0;      /* Move to Sleep on R_BSP_WAIT();DSLPE also needs to be cleared */
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6) 
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif
            SYSTEM.MSTPCRC.BIT.DSLPE = 0;   /* Move to Sleep on R_BSP_WAIT() */
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6) 
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
            break;
        
        case LPC_LP_DEEP_SLEEP:
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.SBYCR.BIT.SSBY = 0;      /* Move to DeepSleep on R_BSP_WAIT(). DSLPE also needs to be set */
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6) 
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif
            SYSTEM.MSTPCRC.BIT.DSLPE = 1;   /* Move to DeepSleep on R_BSP_WAIT() */
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6) 
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
            break;

        case LPC_LP_SW_STANDBY:
            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
            SYSTEM.SBYCR.BIT.SSBY = 1;      /* Move to Sw Stby on R_BSP_WAIT() */
            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
            break;
    
        default:

            /* nothing here */
            break;
    }

    return LPC_SUCCESS;
}
/*********************************************************************************************************************
 End of function lpc_low_power_mode_configure
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Function Name: lpc_lowpower_activate
 * Description  : This function will activate the pre-configured low power mode. The R_BSP_WAIT() function re-enables
 *                interrupts.
 * Arguments    : void (*pcallback)(void* pdata)-
 *                Call back function to configure any un-configured interrupt that can be used to wake up from the low
 *                power mode. This can be a FIT_NO_FUNC if the interrupt(s) are already configured.
 *
 * Return Value : LPC_SUCCESS - Function will return only on waking up from low power mode.
 *                LPC_ERR_OSC_STOP_ENABLED -
 *                    The Software Standby Mode cannot be activated if oscillation stop detection is enabled.
 *                LPC_ERR_CLOCK_EXCEEDED -
 *                    Clock exceeds the limit of current operating mode
 *                LPC_ERR_ILL_CLOCK_SOURCE -
 *                    The Sleep Mode Return Clock Switch is only supported if the clock source at the time of
 *                    entry to sleep mode is allowed clock.
 *                LPC_ERR_ILL_MAIN_CLK_FREQ -
 *                    If the return mode is Medium Speed Mode and Main Osc is the return clock, then 
 *                    the system clock frequency limit over.
 *                LPC_ERR_DEEP_SLEEP_STATUS
 *                    The condition to go to a deep sleep mode isn't met.
 *                LPC_ERR_ILLEGAL
 *                    Other than those above.
 ********************************************************************************************************************/
lpc_err_t lpc_lowpower_activate(lpc_callback_set_t pcallback)
{
#if (LPC_CFG_PARAM_CHECKING_ENABLE == 1)
    lpc_err_t err;

    err = lpc_lowpower_activate_check();
    
    if (LPC_SUCCESS != err)
    {
        return err;
    }
#endif

    R_BSP_InterruptsDisable(); /* Clear the I bit to disable interrupts */
    if ((NULL != pcallback) && (FIT_NO_FUNC != pcallback)) /* If call-back is valid */
    {
        pcallback(FIT_NO_PTR); /* Call call-back to configure wake-up interrupt source */
    }
    else
    {
        R_BSP_NOP();
        R_BSP_NOP();
        R_BSP_NOP();
        R_BSP_NOP();
        R_BSP_NOP(); /* Read last written IO register to make sure it is complete */
        R_BSP_NOP(); /* or wait for 4-5 cycles till any prior write is complete */
    }

    R_BSP_WAIT();                         /* Enter Low Power mode */
    return LPC_SUCCESS;
}
/*********************************************************************************************************************
 End of function lpc_lowpower_activate
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Function Name: lpc_return_clock_switch
 * Description  : This function will configure the return clock switching parameter that allows the clock source to
 *                be switched on returning from Sleep Mode to either the HOCO, LOCO or Main Clock. 
 * Arguments    : lpc_clock_switch_t e_clock_source -
 *                  Specify the clock source to switch to.
 *                bool enable
 *                  Enable/disable the Return clock Source switching function.
 * Return Value : LPC_SUCCESS
 *********************************************************************************************************************/
lpc_err_t lpc_return_clock_switch(lpc_clock_switch_t e_clock_source, bool enable)
{
    if (true == enable)
    {
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
        SYSTEM.RSTCKCR.BYTE = (uint8_t) ((LPC_CLOCK_SWITCH_ENABLE << 7) | e_clock_source);
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
    }
    else
    {
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);
        SYSTEM.RSTCKCR.BYTE = LPC_CLOCK_SWITCH_DISABLE;
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
    }
    
    return LPC_SUCCESS;
}
/*********************************************************************************************************************
 End of function lpc_return_clock_switch
 ********************************************************************************************************************/

/********************************************************************************************************************
 * Function Name: lpc_snooze_mode_configure
 * Description  : This function configures the conditions for entering the snooze mode, returning to the software standby mode
 *                or releasing from the snooze mode.
 * Arguments    : snooze_mode -
 *                   snooze_mode  The snooze_mode  for all supported MCUs are specified in enum \e lpc_snooze_mode_t.
 * Return Value : LPC_SUCCESS -
 *                LPC_ERR_ILLEGAL -
 ********************************************************************************************************************/
lpc_err_t lpc_snooze_mode_configure(lpc_snooze_mode_t * snooze_mode)
{
#if (LPC_CFG_PARAM_CHECKING_ENABLE == 1)
    if (NULL == snooze_mode)
    {
        return LPC_ERR_ILLEGAL;
    }
#endif

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

    SYSTEM.SNZCR.WORD  = snooze_mode->snooze_operation;
    SYSTEM.SNZCR2.WORD = snooze_mode->snooze_release;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

    /*Set snooze release interrupt*/
    if (LPC_SNZ_RESET == snooze_mode->snooze_release)
    {
        R_BSP_InterruptRequestDisable(VECT(SYSTEM, SNZI));
        IPR(SYSTEM,SNZI)         = 0;
        IR(SYSTEM,SNZI)          = 0;
        psnooze_release_callback = FIT_NO_FUNC;
    }
    else
    {
        psnooze_release_callback = snooze_mode->snooze_interrupt.pcallback;
        IR(SYSTEM,SNZI)          = 0;
        IPR(SYSTEM,SNZI)         = snooze_mode->snooze_interrupt.priority;
        R_BSP_InterruptRequestEnable(VECT(SYSTEM, SNZI));
    }

    return LPC_SUCCESS;
}
/*********************************************************************************************************************
 End of function lpc_snooze_mode_configure
 ********************************************************************************************************************/


#if (LPC_CFG_PARAM_CHECKING_ENABLE == 1)
/*********************************************************************************************************************
 * Function Name: lpc_freq_range_check
 * Description  : This function will check clock frequency.
 * Arguments    : e_mode - Operating Mode
 *                    LPC_OP_HIGH_SPEED
 *                    LPC_OP_MIDDLE_SPEED
 *                    LPC_OP_MIDDLE_SPEED_2
 *                    LPC_OP_LOW_SPEED
 * Return Value : LPC_SUCCESS -
 *                LPC_ERR_CLOCK_EXCEEDED -
 *                    If the current system clocks dividers are higher than those supported by the e_mode operating mode.
 ********************************************************************************************************************/
static lpc_err_t lpc_freq_range_check(lpc_operating_mode_t e_mode)
{
    uint32_t iclk_freq;
    uint32_t fclk_freq;
    uint32_t pclka_freq;
    uint32_t pclkb_freq;
    uint32_t pclkd_freq;

    /* Clock source frequencies. The HOCO and PLL values need to be calculated by
     * R_CGC_ClockHzGet() before they are valid. These map to enum cgc_clocks_t */
    clock_frequency[0] = BSP_LOCO_HZ;      // LOCO
    clock_frequency[1] = BSP_HOCO_HZ;      // HOCO
    clock_frequency[2] = BSP_CFG_XTAL_HZ;  // MAIN
    clock_frequency[3] = BSP_SUB_CLOCK_HZ; // SUBCLK
    clock_frequency[4] = 0;                // PLL
    clock_frequency[5] = 15000;            // IWDT - 15 kHz

    hoco_frequency[0] = BSP_HOCO_HZ;

    hoco_frequency[1] = 0;        // not used
    hoco_frequency[2] = 0;        // not used
    hoco_frequency[3] = 0;        // not used

    iclk_freq  = lpc_clockhzget(LPC_ICLK);
    fclk_freq  = lpc_clockhzget(LPC_FCLK);
    pclka_freq = lpc_clockhzget(LPC_PCLKA);
    pclkd_freq = lpc_clockhzget(LPC_PCLKD);
    pclkb_freq = lpc_clockhzget(LPC_PCLKB);

    switch (e_mode)
    {
        case LPC_OP_HIGH_SPEED:
#if (BSP_CFG_MCU_VCC_MV > 2399)
            /* Check if clock speeds are within limits */
            if (((((iclk_freq > LPC_MAX_ICLK_HIGH_SPEED_FREQ_HZ)
                || (fclk_freq > LPC_MAX_FCLK_HIGH_SPEED_FREQ_HZ))
                || (pclka_freq > LPC_MAX_PCLKA_HIGH_SPEED_FREQ_HZ))
                || (pclkd_freq > LPC_MAX_PCLKD_HIGH_SPEED_FREQ_HZ))
                || (pclkb_freq > LPC_MAX_PCLKB_HIGH_SPEED_FREQ_HZ))
            {
                return LPC_ERR_CLOCK_EXCEEDED;
            }
#elif (BSP_CFG_MCU_VCC_MV > 1799)
            /* Check if clock speeds are within limits */
            /* RSIP enable */
            if (0 == SYSTEM.MSTPCRD.BIT.MSTPD31)
            {
                if (((((iclk_freq > LPC_MAX_RSIP_ENABLE_HIGH_SPEED_FREQ_HZ)
                    || (fclk_freq > LPC_MAX_RSIP_ENABLE_HIGH_SPEED_FREQ_HZ))
                    || (pclka_freq > LPC_MAX_RSIP_ENABLE_HIGH_SPEED_FREQ_HZ))
                    || (pclkd_freq > LPC_MAX_RSIP_ENABLE_HIGH_SPEED_FREQ_HZ))
                    || (pclkb_freq > LPC_MAX_RSIP_ENABLE_HIGH_SPEED_FREQ_HZ))
                {
                    return LPC_ERR_CLOCK_EXCEEDED;
                }
            }
            /* RSIP disable */
            else
            {
                if (((((iclk_freq > LPC_MAX_ICLK_HIGH_SPEED_FREQ_HZ)
                    || (fclk_freq > LPC_MAX_FCLK_HIGH_SPEED_FREQ_HZ))
                    || (pclka_freq > LPC_MAX_PCLKA_HIGH_SPEED_FREQ_HZ))
                    || (pclkd_freq > LPC_MAX_PCLKD_HIGH_SPEED_FREQ_HZ))
                    || (pclkb_freq > LPC_MAX_PCLKB_HIGH_SPEED_FREQ_HZ))
                {
                    return LPC_ERR_CLOCK_EXCEEDED;
                }
            }
#endif
            break;
    
        case LPC_OP_MIDDLE_SPEED:
#if (BSP_CFG_MCU_VCC_MV <= 1799)
            /* Check if PLL/PLL2 is running */
            if ((LPC_CLOCK_ACTIVE == SYSTEM.PLLCR2.BYTE) || \
                (LPC_CLOCK_ACTIVE == SYSTEM.PLL2CR2.BYTE))
            {
                return LPC_ERR_CLOCK_EXCEEDED;
            }
#endif

#if ((BSP_CFG_MCU_VCC_MV > 2399) || (BSP_CFG_MCU_VCC_MV <= 1799))
            /* Check if clock speeds are within limits */
            if (((((iclk_freq > LPC_MAX_ICLK_MID_SPEED_FREQ_HZ)
                || (fclk_freq > LPC_MAX_FCLK_MID_SPEED_FREQ_HZ))
                || (pclka_freq > LPC_MAX_PCLKA_MID_SPEED_FREQ_HZ))
                || (pclkd_freq > LPC_MAX_PCLKD_MID_SPEED_FREQ_HZ))
                || (pclkb_freq > LPC_MAX_PCLKB_MID_SPEED_FREQ_HZ))
            {
                return LPC_ERR_CLOCK_EXCEEDED;
            }
#elif (BSP_CFG_MCU_VCC_MV > 1799)
            /* Check if clock speeds are within limits */
            /* RSIP enable */
            if (0 == SYSTEM.MSTPCRD.BIT.MSTPD31)
            {
                if (((((iclk_freq > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ)
                    || (fclk_freq > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ))
                    || (pclka_freq > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ))
                    || (pclkd_freq > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ))
                    || (pclkb_freq > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ))
                {
                    return LPC_ERR_CLOCK_EXCEEDED;
                }
            }
            /* RSIP disable */
            else
            {
                if (((((iclk_freq > LPC_MAX_ICLK_MID_SPEED_FREQ_HZ)
                    || (fclk_freq > LPC_MAX_FCLK_MID_SPEED_FREQ_HZ))
                    || (pclka_freq > LPC_MAX_PCLKA_MID_SPEED_FREQ_HZ))
                    || (pclkd_freq > LPC_MAX_PCLKD_MID_SPEED_FREQ_HZ))
                    || (pclkb_freq > LPC_MAX_PCLKB_MID_SPEED_FREQ_HZ))
                {
                    return LPC_ERR_CLOCK_EXCEEDED;
                }
            }
#endif
            break;

        case LPC_OP_MIDDLE_SPEED_2:
#if (BSP_CFG_MCU_VCC_MV <= 1799)
            /* Check if PLL/PLL2 is running */
            if ((LPC_CLOCK_ACTIVE == SYSTEM.PLLCR2.BYTE) || \
                (LPC_CLOCK_ACTIVE == SYSTEM.PLL2CR2.BYTE))
            {
                return LPC_ERR_CLOCK_EXCEEDED;
            }
#endif

            /* Check if main clock oscillator as the clock source */
            if (LPC_CKSEL_MAIN_OSC == SYSTEM.SCKCR3.BIT.CKSEL)
            {
                return LPC_ERR_CLOCK_EXCEEDED;
            }

            /* Check if clock speeds are within limits */
            if (((((iclk_freq > LPC_MAX_ICLK_MID_SPEED2_FREQ_HZ)
                || (fclk_freq > LPC_MAX_FCLK_MID_SPEED2_FREQ_HZ))
                || (pclka_freq > LPC_MAX_PCLKA_MID_SPEED2_FREQ_HZ))
                || (pclkd_freq > LPC_MAX_PCLKD_MID_SPEED2_FREQ_HZ))
                || (pclkb_freq > LPC_MAX_PCLKB_MID_SPEED2_FREQ_HZ))
            {
                return LPC_ERR_CLOCK_EXCEEDED;
            }
            break;

        case LPC_OP_LOW_SPEED:

            /* Check if clock speeds are within limits */
            if (((((iclk_freq > LPC_MAX_ICLK_LOW_SPEED_FREQ_HZ)
                || (fclk_freq > LPC_MAX_FCLK_LOW_SPEED_FREQ_HZ))
                || (pclka_freq > LPC_MAX_PCLKA_LOW_SPEED_FREQ_HZ))
                || (pclkd_freq > LPC_MAX_PCLKD_LOW_SPEED_FREQ_HZ))
                || (pclkb_freq > LPC_MAX_PCLKB_LOW_SPEED_FREQ_HZ))
            {
                return LPC_ERR_CLOCK_EXCEEDED;
            }
    
            if ((((LPC_CLOCK_ACTIVE == SYSTEM.LOCOCR.BYTE)   /* Check if LOCO is running */
                || (LPC_CLOCK_ACTIVE == SYSTEM.HOCOCR.BYTE)) /* Check if HOCO is running */
                || (LPC_CLOCK_ACTIVE == SYSTEM.MOSCCR.BYTE)) /* Check if Main Osc is running */
                || (LPC_CLOCK_ACTIVE == SYSTEM.PLLCR2.BYTE)) /* Check if PLL is running */
            {
                return LPC_ERR_CLOCK_EXCEEDED;
            }
            break;
        
        default:

            /* nothing here */
            break;
    }

    return LPC_SUCCESS;
}
/*********************************************************************************************************************
 End of function lpc_freq_range_check
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Function Name: lpc_clockhzget
 * Description  : This function will return the requested internal clock frequency in Hz
 * Arguments    : lpc_system_clocks_t clock -
 *                    Specifies the internal clock whose frequency will be returned in Hz .
 *
 * Return Value : uint32_t frequency - clock  frequency in hz
 ********************************************************************************************************************/
static uint32_t lpc_clockhzget(lpc_system_clocks_t clock)
{
    uint32_t divisor;
    uint32_t pll_clk_src_freq;
    float    pll_multiplier;

    /* Determine the current HOCO frequency */
    clock_frequency[LPC_CKSEL_HOCO] = 0;
    if (LPC_CLOCK_ACTIVE == SYSTEM.HOCOCR.BIT.HCSTP)
    {
        /* Get the currently programmed HOCO frequency and update the clock_frequency[]
         * array in case it has changed. */
        clock_frequency[LPC_CKSEL_HOCO] = hoco_frequency[0];
    }

    /* Determine the current PLL frequency */
    clock_frequency[LPC_CKSEL_PLL] = 0;
    if (LPC_CLOCK_ACTIVE == SYSTEM.PLLCR2.BIT.PLLEN)
    {
        /*
         * Calculate the PLL clock frequency as follows:
         * - Determine the main oscillator's frequency
         * - Determine the programmed PLL input divider value from PLLCR.PLIDIV
         * - Determine the programmed PLL output multiplier from PLLCR.STC
         * - Calculate the PLL clock frequency as ((SRC_CLK_FREQ / PLL_DIV) * PLL_MUL)
         */
        pll_clk_src_freq = clock_frequency[LPC_CKSEL_MAIN_OSC];
        pll_multiplier   = (((float) SYSTEM.PLLCR.BIT.STC + 1.0f) / 2.0f);

        /* Finally, calculate the PLL clock frequency */
        clock_frequency[LPC_CKSEL_PLL] = (uint32_t) (((float) pll_clk_src_freq / (float) (1 << SYSTEM.PLLCR.BIT.PLIDIV))
                * pll_multiplier);
    }

    /* Retrieve the programmed divisor for the clock being queried */
    switch (clock)
    {
        case LPC_ICLK :
            divisor = (uint32_t) (1 << SYSTEM.SCKCR.BIT.ICK);
            break;
        case LPC_FCLK :
            divisor = (uint32_t) (1 << SYSTEM.SCKCR.BIT.FCK);
            break;
        case LPC_PCLKA :
            divisor = (uint32_t) (1 << SYSTEM.SCKCR.BIT.PCKA);
            break;
        case LPC_PCLKB :
            divisor = (uint32_t) (1 << SYSTEM.SCKCR.BIT.PCKB);
            break;
        case LPC_PCLKD :
            divisor = (uint32_t) (1 << SYSTEM.SCKCR.BIT.PCKD);
            break;
        default :
            divisor = (uint32_t) (1 << SYSTEM.SCKCR.BIT.ICK);    /* Forced select ICLK when invalid arg */
            break;
    }

    return (uint32_t) ((float) clock_frequency[SYSTEM.SCKCR3.BIT.CKSEL] / (float) divisor);
}
/*********************************************************************************************************************
 End of function lpc_clockhzget
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Function Name: lpc_lowpower_activate_check
 * Description  : This function will check if low power activate can be executed.
 * Arguments    : void 
 *
 * Return Value : LPC_SUCCESS - 
 *                LPC_ERR_OSC_STOP_ENABLED -
 *                    The Software Standby Mode cannot be activated if oscillation stop detection is enabled.
 *                LPC_ERR_ILL_CLOCK_SOURCE -
 *                    The Sleep Mode Return Clock Switch is only supported if the clock source at the time of
 *                    entry to sleep mode is the SubClock.
 *                    If the return mode is Medium Speed Mode, then HOCO cannot be used as the return clock.
 *                    If the return mode is Medium Speed Mode 2, then main clock cannot be used as the return clock.
 *                LPC_ERR_ILL_MAIN_CLK_FREQ -
 *                    If the return mode is Medium Speed Mode and Main Osc is the return clock, then 
 *                    the system clock frequency limit over.
 *                LPC_ERR_DEEP_SLEEP_STATUS
 *                    The condition to go to a deep sleep mode isn't met.
 *                LPC_ERR_ILLEGAL
 *                    Other than those above.
 ********************************************************************************************************************/
static lpc_err_t lpc_lowpower_activate_check(void)
{
    uint8_t rstckcr_rstcksel;

#if (BSP_CFG_MCU_VCC_MV <= 1799)
    if ((LPC_MEDIUM_SPD == SYSTEM.OPCCR.BIT.OPCM) || \
        (LPC_MEDIUM_SPD_2 == SYSTEM.OPCCR.BIT.OPCM))
    {
        /* Check if PLL/PLL2 is running */
        if ((LPC_CLOCK_ACTIVE == SYSTEM.PLLCR2.BYTE) || \
            (LPC_CLOCK_ACTIVE == SYSTEM.PLL2CR2.BYTE))
        {
            return LPC_ERR_CLOCK_EXCEEDED;
        }
    }
#endif

    if (0x1 == SYSTEM.SBYCR.BIT.SSBY) /* check if entering software standby */
    {
        /* Check FENTRY0(b0) and FENTRYD(b7) */
        if (0x0000 != (FLASH.FENTRYR.WORD & 0x0081))
        {
            return LPC_ERR_ILLEGAL;         /* Cannot enter SW_Stanbay if P/E mode entry */
        }

        if (LPC_OSC_STOP_ENABLED == SYSTEM.OSTDCR.BIT.OSTDE)
        {
            return LPC_ERR_OSC_STOP_ENABLED;/* Cannot enter SW_Standby if Oscillation Stop is enabled */
        }
        
        if (((0 == SYSTEM.MSTPCRA.BIT.MSTPA28) 
            && ((1 == DTC.DTCST.BIT.DTCST) || (1 == DMAC.DMAST.BIT.DMST))) && (0 == SYSTEM.SNZCR.BIT.SNZDTCE))
        {
            return LPC_ERR_ILLEGAL;         /* Cannot enter SW_Stanbay if DMAC/DTC is enabled */
        }
    }

    /* Parameter check here to insure that if we are entering sleep mode with return clock switching
     * enabled then, only the Sub-clock is being used to enter sleep and if the return mode is Middle
     * Speed mode that the system clock will be less than limit
     */
    else if ((0x0 == SYSTEM.MSTPCRC.BIT.DSLPE) && /* Check if entering Sleep Mode */
            (LPC_CLOCK_SWITCH_ENABLE == SYSTEM.RSTCKCR.BIT.RSTCKEN)) /* If Return Clock Switching is enabled */
    {
        /* When entering sleep mode with return clock switching enabled, the system clock must be the sub-clock */
        if (LPC_SUB_CLOCK != SYSTEM.SCKCR3.WORD)
        {
            return LPC_ERR_ILL_CLOCK_SOURCE; /* Cannot enter Sleep if SubClock is not system clock */
        }

        if (LPC_MEDIUM_SPD == SYSTEM.OPCCR.BIT.OPCM) /* if return mode is medium speed mode */
        {
            rstckcr_rstcksel = (SYSTEM.RSTCKCR.BYTE & 0x07);
            switch (rstckcr_rstcksel)
            {
                case LPC_HOCO:  /* If HOCO is chosen as the return clock */

                    /* Exiting from sleep-mode to medium-speed mode with the HOCO selected is not permitted */
                    return LPC_ERR_ILL_CLOCK_SOURCE;
                    break;

                case LPC_MAIN_OSC:  /* If Main Clock is chosen as the return clock */
#if ((BSP_CFG_MCU_VCC_MV > 2399) || (BSP_CFG_MCU_VCC_MV <= 1799))
                    /* When exiting sleep-mode to medium-speed mode with the main clock oscillator selected,
                     * the system clock frequency does not exceed the limit */
                    if (((((((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.ICK) > LPC_MAX_ICLK_MID_SPEED_FREQ_HZ))
                        || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.FCK) > LPC_MAX_FCLK_MID_SPEED_FREQ_HZ))
                        || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.PCKA) > LPC_MAX_PCLKA_MID_SPEED_FREQ_HZ))
                        || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.PCKB) > LPC_MAX_PCLKB_MID_SPEED_FREQ_HZ))
                        || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.PCKD) > LPC_MAX_PCLKD_MID_SPEED_FREQ_HZ))
                    {
                        return LPC_ERR_ILL_MAIN_CLK_FREQ;
                    }
#elif (BSP_CFG_MCU_VCC_MV > 1799)
                    /* When exiting sleep-mode to medium-speed mode with the main clock oscillator selected,
                     * the system clock frequency does not exceed the limit */
                    /* RSIP enable */
                    if (0 == SYSTEM.MSTPCRD.BIT.MSTPD31)
                    {
                        if (((((((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.ICK) > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ))
                            || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.FCK) > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ))
                            || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.PCKA) > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ))
                            || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.PCKB) > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ))
                            || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.PCKD) > LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ))
                        {
                            return LPC_ERR_ILL_MAIN_CLK_FREQ;
                        }
                    }
                    /* RSIP disable */
                    else
                    {
                        if (((((((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.ICK) > LPC_MAX_ICLK_MID_SPEED_FREQ_HZ))
                            || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.FCK) > LPC_MAX_FCLK_MID_SPEED_FREQ_HZ))
                            || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.PCKA) > LPC_MAX_PCLKA_MID_SPEED_FREQ_HZ))
                            || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.PCKB) > LPC_MAX_PCLKB_MID_SPEED_FREQ_HZ))
                            || ((BSP_CFG_XTAL_HZ >> SYSTEM.SCKCR.BIT.PCKD) > LPC_MAX_PCLKD_MID_SPEED_FREQ_HZ))
                        {
                            return LPC_ERR_ILL_MAIN_CLK_FREQ;
                        }
                    }
#endif
                    break;
                default:

                    /* nothing here */
                    break;
            }
        }
        else if (LPC_MEDIUM_SPD_2 == SYSTEM.OPCCR.BIT.OPCM) /* if return mode is medium speed mode2 */
        {
            rstckcr_rstcksel = (SYSTEM.RSTCKCR.BYTE & 0x07);
            switch (rstckcr_rstcksel)
            {
                case LPC_HOCO:  /* If HOCO is chosen as the return clock */

                    /* Exiting from sleep-mode to medium-speed mode 2 with the HOCO selected is not permitted */
                    return LPC_ERR_ILL_CLOCK_SOURCE;
                    break;

                case LPC_MAIN_OSC:  /* If Main Clock is chosen as the return clock */

                    /* Exiting from sleep-mode to medium-speed mode 2 with the main clock selected is not permitted */
                    return LPC_ERR_ILL_CLOCK_SOURCE;
                    break;
                default:

                    /* nothing here */
                    break;
            }
        }
        else
        {
            /* nothing here */
        }
    }
    else if (0x1 == SYSTEM.MSTPCRC.BIT.DSLPE)
    {
        /* Check FENTRY0(b0) and FENTRYD(b7) */
        if (0x0000 != (FLASH.FENTRYR.WORD & 0x0081))
        {
            return LPC_ERR_ILLEGAL;             /* Cannot enter Deep Sleep if P/E mode entry */
        }
        
        if (0 == SYSTEM.MSTPCRA.BIT.MSTPA28)
        {
            return LPC_ERR_DEEP_SLEEP_STATUS;   /* Cannot enter Deep Sleep if DTC is enabled */
        }
    }
    else
    {
        /* nothing here */
    }

    return LPC_SUCCESS;
}
/*********************************************************************************************************************
 End of function lpc_lowpower_activate_check
 ********************************************************************************************************************/

#endif /* LPC_CFG_PARAM_CHECKING_ENABLE */

/*********************************************************************************************************************
 * Function Name: lpc_snooze_release_isr
 * Description  :  snooze Interrupt
 * Arguments    : void
 ********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT (lpc_snooze_release_isr, VECT(SYSTEM, SNZI))
R_BSP_ATTRIB_STATIC_INTERRUPT void lpc_snooze_release_isr(void)
{
    if ((NULL != psnooze_release_callback) && (FIT_NO_FUNC != psnooze_release_callback))
    {
        psnooze_release_callback (FIT_NO_PTR);
    }
}
/*********************************************************************************************************************
 End of function lpc_snooze_release_isr
 ********************************************************************************************************************/


#endif /* BSP_MCU_RX260 */


/***********************************************************************************************************************
 * End of File
 ***********************************************************************************************************************/
