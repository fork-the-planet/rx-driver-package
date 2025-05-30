/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : mcu_clocks.c
* Description  : Contains clock specific routines
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 01.02.2016 1.00     First Release
*         : 30.09.2016 1.01     Added the setting of High Speed On-Chip Oscillator (HOCO).
*         : 28.02.2019 2.00     Added clock setup.
*                               Fixed cast of get_iclk_freq_hz function.
*                               Deleted the rom cache setting.
*                               (The rom cache setting moved to the hardware setup file (hwsetup.c).)
*                               Fixed coding style.
*                               Renamed following macro definitions.
*                               - BSP_PRV_CKSEL_LOCO
*                               - BSP_PRV_CKSEL_HOCO
*                               - BSP_PRV_CKSEL_MAIN_OSC
*                               - BSP_PRV_CKSEL_PLL
*                               - BSP_PRV_NORMALIZE_X10
*                               Deleted the error check of BSP_CFG_CLOCK_SOURCE in the clock_source_select function.
*         : 17.12.2019 2.01     Deleted the unused variables of clock_source_select function.
*         : 30.11.2021 3.00     Added the following macro definition.
*                               - BSP_PRV_PLL_CLK_OPERATING
*                               Changed compile switch of clock settings by the following new macro definitions.
*                               - BSP_CFG_MAIN_CLOCK_OSCILLATE_ENABLE
*                               - BSP_CFG_HOCO_OSCILLATE_ENABLE
*                               - BSP_CFG_LOCO_OSCILLATE_ENABLE
*                               - BSP_PRV_PLL_CLK_OPERATING
*                               Added the setting of the IWDT-Dedicated On-Chip Oscillator in operating_frequency_set 
*                               function.
*                               Added comments for when use simulator.
*                               Added version check of smart configurator.
*         : 22.04.2022 3.01     Deleted version check of smart configurator.
*         : 21.11.2023 3.02     Added compile switch of BSP_CFG_BOOTLOADER_PROJECT.
*                               Added the bsp_mcu_clock_reset_bootloader function.
*                               Changed MOFCR setting timing.
*         : 26.02.2025 3.03     Changed the disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define BSP_PRV_CKSEL_LOCO            (0x0)
#define BSP_PRV_CKSEL_HOCO            (0x1)
#define BSP_PRV_CKSEL_MAIN_OSC        (0x2)
#define BSP_PRV_CKSEL_PLL             (0x4)

#define BSP_PRV_NORMALIZE_X10  (10)   /* used to avoid floating point arithmetic */

/* This macro runs or stops the PLL circuit.
   If the following conditions are satisfied, PLL circuit will operate.
   1. System clock source is PLL circuit.
 */
#if (BSP_CFG_CLOCK_SOURCE == 4)
    #define BSP_PRV_PLL_CLK_OPERATING    (1)    /* PLL circuit is operating. */
#else /* PLL is not used as clock source. */
    #define BSP_PRV_PLL_CLK_OPERATING    (0)    /* PLL circuit is stopped. */
#endif

#if BSP_CFG_BOOTLOADER_PROJECT == 1
/* Enable the following macro definitions in the bootloader project. */
#define BSP_PRV_SCKCR_RESET_VALUE        (0x33033303)
#define BSP_PRV_SCKCR3_RESET_VALUE       (0x0000)
#define BSP_PRV_MEMWAIT_RESET_VALUE      (0x00)
#define BSP_PRV_PLLCR_RESET_VALUE        (0x0f00)
#define BSP_PRV_PLLCR2_RESET_VALUE       (0x01)
#define BSP_PRV_MOSCCR_RESET_VALUE       (0x01)
#define BSP_PRV_MOSCWTCR_RESET_VALUE     (0x04)
#define BSP_PRV_MOFCR_RESET_VALUE        (0x00)
#define BSP_PRV_OPCCR_RESET_VALUE        (0x02)
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 1 */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_DISABLE == 0
static void operating_frequency_set(void);
static void clock_source_select(void);
#endif /* BSP_CFG_STARTUP_DISABLE == 0 */

/***********************************************************************************************************************
* Function Name: get_iclk_freq_hz
* Description  : Return the current ICLK frequency in Hz. Called by R_BSP_GetIClkFreqHz().
*                The system clock source can be changed at any time via SYSTEM.SCKCR3.BIT.CKSEL, so in order to
*                determine the ICLK frequency we need to first find the current system clock source and then,
*                in some cases where the clock source can be configured for multiple frequencies, calculate the
*                frequency at which it is currently running.
* Arguments    : None
* Return Value : uint32_t - the iclk frequency in Hz
***********************************************************************************************************************/
uint32_t get_iclk_freq_hz(void)
{
    uint32_t sys_clock_src_freq;
    uint32_t pll_multiplier;
    uint32_t pll_source_freq;
    uint32_t hoco_frequency[4] = {32000000, 0, 0, 64000000};

    /* Casting is valid because it matches the type to the retern value. */
    uint8_t  cksel = (uint8_t)SYSTEM.SCKCR3.BIT.CKSEL;

    switch (cksel)
    {
        case BSP_PRV_CKSEL_LOCO:
            sys_clock_src_freq = BSP_LOCO_HZ;
            break;

        case BSP_PRV_CKSEL_HOCO:
            sys_clock_src_freq = BSP_HOCO_HZ;
            break;

        case BSP_PRV_CKSEL_MAIN_OSC:
            sys_clock_src_freq = BSP_CFG_XTAL_HZ;
            break;

        case BSP_PRV_CKSEL_PLL:

            /* The RX24T have two possible sources for the PLL */

            /* Casting is valid because it matches the type to the retern value. */
            pll_multiplier = ((((uint32_t)(SYSTEM.PLLCR.BIT.STC + 1)) * BSP_PRV_NORMALIZE_X10) / 2);

            /* Default to the MAIN OSC as the PLL source */
            pll_source_freq = BSP_CFG_XTAL_HZ;

            /* If 1 then the HOCO is the PLL source */
            if (0x1 == SYSTEM.PLLCR.BIT.PLLSRCSEL)
            {
                /* Set HOCO frequency. */
                pll_source_freq = hoco_frequency[SYSTEM.HOCOCR2.BIT.HCFRQ];
            }

            /* Casting is valid because it matches the type to the retern value. */
            sys_clock_src_freq = ((pll_source_freq / (((uint32_t)(1 << SYSTEM.PLLCR.BIT.PLIDIV)) * BSP_PRV_NORMALIZE_X10)) * pll_multiplier);
            break;

        default:

            /* Should never arrive here. Use the Main OSC freq as a default... */
            sys_clock_src_freq = BSP_CFG_XTAL_HZ;
            break;
    }

    /* Finally, divide the system clock source frequency by the currently set ICLK divider to get the ICLK frequency */
    return (sys_clock_src_freq / (uint32_t)(1 << SYSTEM.SCKCR.BIT.ICK));
} /* End of function get_iclk_freq_hz() */

/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_DISABLE == 0

/***********************************************************************************************************************
* Function name: mcu_clock_setup
* Description  : Contains clock functions called at device restart.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
void mcu_clock_setup(void)
{
    /* Switch to high-speed operation */
    operating_frequency_set();
} /* End of function mcu_clock_setup() */

/***********************************************************************************************************************
* Function name: operating_frequency_set
* Description  : Configures the clock settings for each of the device clocks
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void operating_frequency_set (void)
{
    /* Used for constructing value to write to SCKCR, and SCKCR3 registers. */
    uint32_t tmp_clock = 0;

    /* Protect off. */
    SYSTEM.PRCR.WORD = 0xA50F;

    /* Select the clock based upon user's choice. */
    clock_source_select();

    /* Figure out setting for FCK bits. */
#if   BSP_CFG_FCK_DIV == 1
    /* Do nothing since FCK bits should be 0. */
#elif BSP_CFG_FCK_DIV == 2
    tmp_clock |= 0x10000000;
#elif BSP_CFG_FCK_DIV == 4
    tmp_clock |= 0x20000000;
#elif BSP_CFG_FCK_DIV == 8
    tmp_clock |= 0x30000000;
#elif BSP_CFG_FCK_DIV == 16
    tmp_clock |= 0x40000000;
#elif BSP_CFG_FCK_DIV == 32
    tmp_clock |= 0x50000000;
#elif BSP_CFG_FCK_DIV == 64
    tmp_clock |= 0x60000000;
#else
    #error "Error! Invalid setting for BSP_CFG_FCK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for ICK bits. */
#if   BSP_CFG_ICK_DIV == 1
    /* Do nothing since ICK bits should be 0. */
#elif BSP_CFG_ICK_DIV == 2
    tmp_clock |= 0x01000000;
#elif BSP_CFG_ICK_DIV == 4
    tmp_clock |= 0x02000000;
#elif BSP_CFG_ICK_DIV == 8
    tmp_clock |= 0x03000000;
#elif BSP_CFG_ICK_DIV == 16
    tmp_clock |= 0x04000000;
#elif BSP_CFG_ICK_DIV == 32
    tmp_clock |= 0x05000000;
#elif BSP_CFG_ICK_DIV == 64
    tmp_clock |= 0x06000000;
#else
    #error "Error! Invalid setting for BSP_CFG_ICK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for PCKA bits. */
#if   BSP_CFG_PCKA_DIV == 1
    /* Do nothing since PCKA bits should be 0. */
#elif BSP_CFG_PCKA_DIV == 2
    tmp_clock |= 0x00001000;
#elif BSP_CFG_PCKA_DIV == 4
    tmp_clock |= 0x00002000;
#elif BSP_CFG_PCKA_DIV == 8
    tmp_clock |= 0x00003000;
#elif BSP_CFG_PCKA_DIV == 16
    tmp_clock |= 0x00004000;
#elif BSP_CFG_PCKA_DIV == 32
    tmp_clock |= 0x00005000;
#elif BSP_CFG_PCKA_DIV == 64
    tmp_clock |= 0x00006000;
#else
    #error "Error! Invalid setting for BSP_CFG_PCKA_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for PCKB bits. */
#if   BSP_CFG_PCKB_DIV == 1
    /* Do nothing since PCKB bits should be 0. */
#elif BSP_CFG_PCKB_DIV == 2
    tmp_clock |= 0x00010100;
#elif BSP_CFG_PCKB_DIV == 4
    tmp_clock |= 0x00020200;
#elif BSP_CFG_PCKB_DIV == 8
    tmp_clock |= 0x00030300;
#elif BSP_CFG_PCKB_DIV == 16
    tmp_clock |= 0x00040400;
#elif BSP_CFG_PCKB_DIV == 32
    tmp_clock |= 0x00050500;
#elif BSP_CFG_PCKB_DIV == 64
    tmp_clock |= 0x00060600;
#else
    #error "Error! Invalid setting for BSP_CFG_PCKB_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for PCKD bits. */
#if   BSP_CFG_PCKD_DIV == 1
    /* Do nothing since PCKD bits should be 0. */
#elif BSP_CFG_PCKD_DIV == 2
    tmp_clock |= 0x00000001;
#elif BSP_CFG_PCKD_DIV == 4
    tmp_clock |= 0x00000002;
#elif BSP_CFG_PCKD_DIV == 8
    tmp_clock |= 0x00000003;
#elif BSP_CFG_PCKD_DIV == 16
    tmp_clock |= 0x00000004;
#elif BSP_CFG_PCKD_DIV == 32
    tmp_clock |= 0x00000005;
#elif BSP_CFG_PCKD_DIV == 64
    tmp_clock |= 0x00000006;
#else
    #error "Error! Invalid setting for BSP_CFG_PCKD_DIV in r_bsp_config.h"
#endif

    /* b7 to b4 should be 0x0.
       b23 to b20 should be 0x0. */

    /* Set SCKCR register. */
    SYSTEM.SCKCR.LONG = tmp_clock;

    /* Dummy read and compare. cf."5. I/O Registers", "(2) Notes on writing to I/O registers" in User's manual.
       This is done to ensure that the register has been written before the next register access. The RX has a 
       pipeline architecture so the next instruction could be executed before the previous write had finished.
    */
    if(tmp_clock == SYSTEM.SCKCR.LONG)
    {
        R_BSP_NOP();
    }

    /* Choose clock source. Default for r_bsp_config.h is PLL. */
    tmp_clock = ((uint16_t)BSP_CFG_CLOCK_SOURCE) << 8;

    /* Casting is valid because it matches the type to the retern value. */
    SYSTEM.SCKCR3.WORD = (uint16_t)tmp_clock;

    /* Dummy read and compare. cf."5. I/O Registers", "(2) Notes on writing to I/O registers" in User's manual.
       This is done to ensure that the register has been written before the next register access. The RX has a 
       pipeline architecture so the next instruction could be executed before the previous write had finished.
    */
    if((uint16_t)tmp_clock == SYSTEM.SCKCR3.WORD)
    {
        R_BSP_NOP();
    }

#if BSP_CFG_BOOTLOADER_PROJECT == 0
/* Disable the following functions in the bootloader project. */
#if BSP_CFG_IWDT_CLOCK_OSCILLATE_ENABLE == 1
    /* IWDT clock is stopped after reset. Oscillate the IWDT. */
    SYSTEM.ILOCOCR.BIT.ILCSTP = 0;

    /* Wait processing for the IWDT clock oscillation stabilization (50us) */
    R_BSP_SoftwareDelay((uint32_t)50, BSP_DELAY_MICROSECS);
#endif

#if BSP_CFG_LOCO_OSCILLATE_ENABLE == 0
    /* We can now turn LOCO off since it is not going to be used. */
    SYSTEM.LOCOCR.BYTE = 0x01;

    /* Wait for five the LOCO cycles */
    /* 5 count of LOCO : (1000000/3440000)*5 = 1.453488us
       1.45 + 2 = 3.45us ("+2" is overhead cycle) */
    R_BSP_SoftwareDelay((uint32_t)4, BSP_DELAY_MICROSECS);
#endif
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

    /* Protect on. */
    SYSTEM.PRCR.WORD = 0xA500;
} /* End of function operating_frequency_set() */

/***********************************************************************************************************************
* Function name: clock_source_select
* Description  : Enables and disables clocks as chosen by the user.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void clock_source_select (void)
{
    /* Set to High-speed operating mode if ICLK is > 12MHz. */
    if( BSP_ICLK_HZ > BSP_MIDDLE_SPEED_MAX_FREQUENCY )
    {
        /* set to high-speed mode */
        SYSTEM.OPCCR.BYTE = 0x00;

        /* WAIT_LOOP */
        while(1 == SYSTEM.OPCCR.BIT.OPCMTSF)
        {
            /* Wait for transition to finish. */
            R_BSP_NOP();
        }
    }

    /* Set to memory wait if ICLK is > 64MHz. */
    if( BSP_ICLK_HZ > BSP_MCU_MEMWAIT_FREQ_THRESHOLD )
    {
        /* Use wait states */
        SYSTEM.MEMWAIT.BYTE = 0x02;

        /* WAIT_LOOP */
        while (0x02 != SYSTEM.MEMWAIT.BYTE)
        {
            /* wait for bit to set */
            R_BSP_NOP();
        }
    }
    /* Set to memory wait if ICLK is > 32MHz. */
    else if( BSP_ICLK_HZ > BSP_MEMORY_NO_WAIT_MAX_FREQUENCY )
    {
        /* Use wait states */
        SYSTEM.MEMWAIT.BYTE = 0x01;

        /* WAIT_LOOP */
        while (0x01 != SYSTEM.MEMWAIT.BYTE)
        {
            /* wait for bit to set */
            R_BSP_NOP();
        }
    }
    else
    {
        /* do nothing */
        R_BSP_NOP();
    }

    /* At this time the MCU is still running on the 4MHz LOCO. */

#if BSP_CFG_HOCO_OSCILLATE_ENABLE == 1
    /* HOCO is chosen. Start it operating if it is not already operating. */
    if (1 == SYSTEM.HOCOCR.BIT.HCSTP)
    {
        /* WAIT_LOOP */
        while (0 != SYSTEM.OSCOVFSR.BIT.HCOVF)
        {
            /* wait for bit to set */
            R_BSP_NOP();
        }

        /* Set HOCO frequency. */
        SYSTEM.HOCOCR2.BYTE = BSP_CFG_HOCO_FREQUENCY;

        /* Set the oscillation stabilization wait time of the HOCO. */
    #if BSP_CFG_HOCO_FREQUENCY == 0
        /* High-Speed On-Chip Oscillator Wait Time (HOCOWTCR).
           0x05(101b) = Wait time = 142 cycles
           When the HOCO frequency is 32MHz, settings other than above are prohibited.
        */
        SYSTEM.HOCOWTCR.BYTE = 0x05;
    #elif BSP_CFG_HOCO_FREQUENCY == 3
        /* High-Speed On-Chip Oscillator Wait Time (HOCOWTCR).
           0x06(110b) = Wait time = 270 cycles
           When the HOCO frequency is 64MHz, settings other than above are prohibited.
        */
        SYSTEM.HOCOWTCR.BYTE = 0x06;
    #else
        #error "Error! Invalid setting for BSP_CFG_HOCO_FREQUENCY in r_bsp_config.h"
    #endif

        /* Start HOCO operating. */
        SYSTEM.HOCOCR.BYTE = 0x00;

        /* WAIT_LOOP */
        while (0 == SYSTEM.OSCOVFSR.BIT.HCOVF)
        {
            /* Make sure clock has stabilized.
               If you use simulator, the flag is not set to 1, resulting in an infinite loop. */
            R_BSP_NOP();
        }
    }
#endif /* BSP_CFG_HOCO_OSCILLATE_ENABLE == 1 */

#if BSP_CFG_MAIN_CLOCK_OSCILLATE_ENABLE == 1
    /* Configure the main clock oscillator drive capability. */
    if (BSP_CFG_XTAL_HZ >= 10000000)
    {
        /* BSP_CFG_XTAL_HZ >= 10 MHz Uses 10MHz external oscillator */
        SYSTEM.MOFCR.BIT.MODRV21 = 1;
    }
    else
    {
        /* BSP_CFG_XTAL_HZ < 10 MHz */
        SYSTEM.MOFCR.BIT.MODRV21 = 0;
    }

    /* Set the oscillation source of the main clock oscillator. */
    SYSTEM.MOFCR.BIT.MOSEL = BSP_CFG_MAIN_CLOCK_SOURCE;

    #if   (BSP_CFG_MAIN_CLOCK_SOURCE == 0) /* Resonator */
        /* Set the oscillation stabilization wait time of the main clock oscillator. */
        SYSTEM.MOSCWTCR.BYTE = BSP_CFG_MOSC_WAIT_TIME;
    #elif (BSP_CFG_MAIN_CLOCK_SOURCE == 1) /* External oscillator input */
        SYSTEM.MOSCWTCR.BYTE = 0x00;
    #else
        #error "Error! Invalid setting for BSP_CFG_MAIN_CLOCK_SOURCE in r_bsp_config.h"
    #endif

    /* Set the main clock to operating. */
    SYSTEM.MOSCCR.BYTE = 0x00;

    /* WAIT_LOOP */
    while (1 != SYSTEM.OSCOVFSR.BIT.MOOVF)
    {
        /* wait for stabilization.
           If you use simulator, the flag is not set to 1, resulting in an infinite loop. */
        R_BSP_NOP();
    }
#endif /* BSP_CFG_MAIN_CLOCK_OSCILLATE_ENABLE == 1 */

#if BSP_PRV_PLL_CLK_OPERATING == 1

    /* Set PLL Input Divisor. */
    SYSTEM.PLLCR.BIT.PLIDIV = BSP_CFG_PLL_DIV >> 1;

    #if BSP_CFG_PLL_SRC == 0
    /* Clear PLL clock source if PLL clock source is Main clock. */
    SYSTEM.PLLCR.BIT.PLLSRCSEL = 0;
    #else
    /* Set PLL clock source if PLL clock source is HOCO clock. */
    SYSTEM.PLLCR.BIT.PLLSRCSEL = 1;
    #endif

    /* Set PLL Multiplier. */
    SYSTEM.PLLCR.BIT.STC = ((uint8_t)((float)BSP_CFG_PLL_MUL * 2.0)) - 1;

    /* Set the PLL to operating. */
    SYSTEM.PLLCR2.BYTE = 0x00;

    /* WAIT_LOOP */
    while (1 != SYSTEM.OSCOVFSR.BIT.PLOVF)
    {
        /* wait for stabilization.
           If you use simulator, the flag is not set to 1, resulting in an infinite loop. */
        R_BSP_NOP();
    }
#endif

    /* LOCO is saved for last since it is what is running by default out of reset. This means you do not want to turn
       it off until another clock has been enabled and is ready to use. */
#if BSP_CFG_LOCO_OSCILLATE_ENABLE == 1
    /* LOCO is chosen. This is the default out of reset. */
#else
    /* LOCO is not chosen but it cannot be turned off yet since it is still being used. */
#endif
} /* End of function clock_source_select() */

#if BSP_CFG_BOOTLOADER_PROJECT == 1
/***********************************************************************************************************************
* Function name: bsp_mcu_clock_reset_bootloader
* Description  : Returns the MCU clock settings to the reset state. The system clock returns to LOCO. PLL circuit will 
*                stop. Main clock will stop.
* Arguments    : none
* Return value : none
* Note         : Enable this functions in the bootloader project. This function for bootloader only. 
***********************************************************************************************************************/
void bsp_mcu_clock_reset_bootloader (void)
{
    /* Protect off. */
    SYSTEM.PRCR.WORD = 0xA503;

    /* Is not Clock source LOCO? */
    if(BSP_PRV_SCKCR3_RESET_VALUE != SYSTEM.SCKCR3.WORD)
    {
        /* Reset clock source. Change to LOCO. */
        SYSTEM.SCKCR3.WORD = BSP_PRV_SCKCR3_RESET_VALUE;

        /* Dummy read and compare. cf."5. I/O Registers", "(2) Notes on writing to I/O registers" in User's manual.
           This is done to ensure that the register has been written before the next register access. The RX has a
           pipeline architecture so the next instruction could be executed before the previous write had finished.
        */
        if(BSP_PRV_SCKCR3_RESET_VALUE == SYSTEM.SCKCR3.WORD)
        {
            R_BSP_NOP();
        }
    }

    /* Is not SCKCR reset value? */
    if(BSP_PRV_SCKCR_RESET_VALUE != SYSTEM.SCKCR.LONG)
    {
        /* Reset SCKCR register. */
        SYSTEM.SCKCR.LONG = BSP_PRV_SCKCR_RESET_VALUE;

        /* Dummy read and compare. cf."5. I/O Registers", "(2) Notes on writing to I/O registers" in User's manual.
           This is done to ensure that the register has been written before the next register access. The RX has a
           pipeline architecture so the next instruction could be executed before the previous write had finished.
        */
        if(BSP_PRV_SCKCR_RESET_VALUE == SYSTEM.SCKCR.LONG)
        {
            R_BSP_NOP();
        }
    }

    /* Is not MEMWAIT reset value? */
    if(BSP_PRV_MEMWAIT_RESET_VALUE != SYSTEM.MEMWAIT.BYTE)
    {
        /* Reset Memory Wait Cycle */
        SYSTEM.MEMWAIT.BYTE = BSP_PRV_MEMWAIT_RESET_VALUE;

        /* WAIT_LOOP */
        while (BSP_PRV_MEMWAIT_RESET_VALUE != SYSTEM.MEMWAIT.BYTE)
        {
            /* wait for bit to set */
            R_BSP_NOP();
        }
    }

#if BSP_PRV_PLL_CLK_OPERATING == 1
    /* PLL operating? */
    if(BSP_PRV_PLLCR2_RESET_VALUE != SYSTEM.PLLCR2.BYTE)
    {
        /* Stop PLL. */
        SYSTEM.PLLCR2.BYTE = BSP_PRV_PLLCR2_RESET_VALUE;

        /* WAIT_LOOP */
        while(1 == SYSTEM.OSCOVFSR.BIT.PLOVF)
        {
            /* The delay period needed is to make sure that the PLL has stabilized.
               If you use simulator, the flag is not set to 1, resulting in an infinite loop. */
            R_BSP_NOP();
        }
    }

    /* Is not PLLCR reset value? */
    if(BSP_PRV_PLLCR_RESET_VALUE != SYSTEM.PLLCR.WORD)
    {
        /* Reset PLL. */
        SYSTEM.PLLCR.WORD = BSP_PRV_PLLCR_RESET_VALUE;
    }
#endif /* BSP_PRV_PLL_CLK_OPERATING == 1 */

#if BSP_CFG_MAIN_CLOCK_OSCILLATE_ENABLE == 1
    /* main clock operating? */
    if(BSP_PRV_MOSCCR_RESET_VALUE != SYSTEM.MOSCCR.BYTE)
    {
        /* Stop the main clock. */
        SYSTEM.MOSCCR.BYTE = BSP_PRV_MOSCCR_RESET_VALUE;

        /* Dummy read and compare. cf."5. I/O Registers", "(2) Notes on writing to I/O registers" in User's manual.
           This is done to ensure that the register has been written before the next register access. The RX has a
           pipeline architecture so the next instruction could be executed before the previous write had finished.
        */
        if(BSP_PRV_MOSCCR_RESET_VALUE == SYSTEM.MOSCCR.BYTE)
        {
            R_BSP_NOP();
        }

        /* WAIT_LOOP */
        while(1 == SYSTEM.OSCOVFSR.BIT.MOOVF)
        {
            /* The delay period needed is to make sure that the Main clock has stabilized.
               If you use simulator, the flag is not set to 1, resulting in an infinite loop. */
            R_BSP_NOP();
        }
    }

    /* Is not MOSCWTCR reset value? */
    if(BSP_PRV_MOSCWTCR_RESET_VALUE != SYSTEM.MOSCWTCR.BYTE)
    {
        /* Reset MOSCWTCR */
        SYSTEM.MOSCWTCR.BYTE = BSP_PRV_MOSCWTCR_RESET_VALUE;

        /* Dummy read and compare. cf."5. I/O Registers", "(2) Notes on writing to I/O registers" in User's manual.
           This is done to ensure that the register has been written before the next register access. The RX has a
           pipeline architecture so the next instruction could be executed before the previous write had finished.
        */
        if(BSP_PRV_MOSCWTCR_RESET_VALUE == SYSTEM.MOSCWTCR.BYTE)
        {
            R_BSP_NOP();
        }
    }

    /* Is not MOFCR reset value? */
    if(BSP_PRV_MOFCR_RESET_VALUE != SYSTEM.MOFCR.BYTE)
    {
        /* Reset MOFCR */
        SYSTEM.MOFCR.BYTE = BSP_PRV_MOFCR_RESET_VALUE;

        /* Dummy read and compare. cf."5. I/O Registers", "(2) Notes on writing to I/O registers" in User's manual.
           This is done to ensure that the register has been written before the next register access. The RX has a
           pipeline architecture so the next instruction could be executed before the previous write had finished.
        */
        if(BSP_PRV_MOFCR_RESET_VALUE == SYSTEM.MOFCR.BYTE)
        {
            R_BSP_NOP();
        }
    }
#endif /* BSP_CFG_MAIN_CLOCK_OSCILLATE_ENABLE == 1 */

    /* Initialization of other clock-related registers. */
    /* Is not OPCCR reset value? */
    if(BSP_PRV_OPCCR_RESET_VALUE != SYSTEM.OPCCR.BYTE)
    {
        /* Reset OPCCR register. */
        SYSTEM.OPCCR.BYTE = BSP_PRV_OPCCR_RESET_VALUE;

        /* WAIT_LOOP */
        while(1 == SYSTEM.OPCCR.BIT.OPCMTSF)
        {
            /* Wait for transition to finish. */
            R_BSP_NOP();
        }
     }

    /* Protect on. */
    SYSTEM.PRCR.WORD = 0xA500;
} /* End of function bsp_mcu_clock_reset_bootloader() */
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 1 */

#endif /* BSP_CFG_STARTUP_DISABLE == 0 */

