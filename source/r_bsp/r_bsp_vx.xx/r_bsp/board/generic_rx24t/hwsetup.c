/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : hwsetup.c
* Device(s)    : RX
* H/W Platform : GENERIC_RX24T
* Description  : Defines the initialization routines used each time the MCU is restarted.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 01.11.2017 2.00     First Release
*         : 31.10.2018 2.01     Added the initialization function for Smart Configurator.
*         : 28.02.2019 2.02     Fixed coding style.
*                               Added the following function.
*                               - rom_cache_function_set
*         : 21.11.2023 2.03     Added compile switch of BSP_CFG_BOOTLOADER_PROJECT.
*         : 26.02.2025 2.04     Changed the disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* I/O Register and board definitions */
#include "platform.h"
#if BSP_CFG_CONFIGURATOR_SELECT == 1
#include "r_cg_macrodriver.h"
#endif

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_DISABLE == 0
/* ROM cache configuration function declaration */
#if BSP_CFG_ROM_CACHE_ENABLE == 1
static void rom_cache_function_set(void);
#endif /* BSP_CFG_ROM_CACHE_ENABLE == 1 */
#endif /* BSP_CFG_STARTUP_DISABLE == 0 */

#if BSP_CFG_BOOTLOADER_PROJECT == 0
/* Disable the following functions in the bootloader project. */
/* MCU I/O port configuration function declaration */
static void output_ports_configure(void);

/* Interrupt configuration function declaration */
static void interrupts_configure(void);
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

/* MCU peripheral module configuration function declaration */
static void peripheral_modules_enable(void);


/***********************************************************************************************************************
* Function name: hardware_setup
* Description  : Contains setup functions called at device restart
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
void hardware_setup(void)
{
/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_DISABLE == 0
#if BSP_CFG_ROM_CACHE_ENABLE == 1
    /* Initialize ROM cache function */
    rom_cache_function_set();
#endif /* BSP_CFG_ROM_CACHE_ENABLE == 1 */
#endif /* BSP_CFG_STARTUP_DISABLE == 0 */

#if BSP_CFG_BOOTLOADER_PROJECT == 0
    /* Disable the following functions in the bootloader project. */
    output_ports_configure();
    interrupts_configure();
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */
    peripheral_modules_enable();
    bsp_non_existent_port_init();
} /* End of function hardware_setup() */

/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_DISABLE == 0
#if BSP_CFG_ROM_CACHE_ENABLE == 1
/***********************************************************************************************************************
* Function name: rom_cache_function_set
* Description  : Configures the rom cache function.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void rom_cache_function_set (void)
{
    /* Invalidates the contents of the ROM cache. */
    FLASH.ROMCIV.WORD = 0x0001;
    /* WAIT_LOOP */
    while (FLASH.ROMCIV.WORD != 0x0000)
    {
        /* wait for bit to set */
    }

    /* Enables the ROM cache. */
    FLASH.ROMCE.WORD = 0x0001;
    /* WAIT_LOOP */
    while (FLASH.ROMCE.WORD != 0x0001)
    {
        /* wait for bit to set */
    }
} /* End of function rom_cache_function_set() */
#endif /* BSP_CFG_ROM_CACHE_ENABLE == 1 */
#endif /* BSP_CFG_STARTUP_DISABLE == 0 */

#if BSP_CFG_BOOTLOADER_PROJECT == 0
/* Disable the following functions in the bootloader project. */
/***********************************************************************************************************************
* Function name: output_ports_configure
* Description  : Configures the port and pin direction settings, and sets the pin outputs to a safe level.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void output_ports_configure(void)
{
    /* Add code here to setup additional output ports */
    R_BSP_NOP();
} /* End of function output_ports_configure() */

/***********************************************************************************************************************
* Function name: interrupts_configure
* Description  : Configures interrupts used
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void interrupts_configure(void)
{
    /* Add code here to setup additional interrupts */
    R_BSP_NOP();
} /* End of function interrupts_configure() */
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

/***********************************************************************************************************************
* Function name: peripheral_modules_enable
* Description  : Enables and configures peripheral devices on the MCU
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void peripheral_modules_enable(void)
{
    /* Add code here to enable peripherals used by the application */
#if BSP_CFG_CONFIGURATOR_SELECT == 1
    /* Smart Configurator initialization function */
    R_Systeminit();
#endif
} /* End of function peripheral_modules_enable() */

