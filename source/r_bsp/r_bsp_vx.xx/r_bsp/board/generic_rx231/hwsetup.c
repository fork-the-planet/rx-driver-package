/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : hwsetup.c
* Device(s)    : RX
* H/W Platform : GENERIC_RX231
* Description  : Defines the initialization routines used each time the MCU is restarted.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 01.11.2017 2.00     First Release
*         : 01.07.2018 2.01     Added the initialization function for Smart Configurator.
*         : 27.07.2018 2.02     Added the comment to while statement.
*         : 28.02.2019 3.00     Added support for GNUC and ICCRX.
*                               Fixed coding style.
*         : 21.11.2023 3.01     Added compile switch of BSP_CFG_BOOTLOADER_PROJECT.
*         : 26.02.2025 3.02     Changed the disclaimer.
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
#if BSP_CFG_BOOTLOADER_PROJECT == 0
/* Disable the following functions in the bootloader project. */
/* MCU I/O port configuration function declaration */
static void output_ports_configure(void);

/* Interrupt configuration function declaration */
static void interrupts_configure(void);
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

/* MCU peripheral module configuration function declaration */
static void peripheral_modules_enable(void);

/* Security initial configuration function declaration */
static void bsp_security_initial_configure(void);

/***********************************************************************************************************************
* Function name: hardware_setup
* Description  : Contains setup functions called at device restart
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
void hardware_setup(void)
{
    bsp_security_initial_configure();
#if BSP_CFG_BOOTLOADER_PROJECT == 0
    /* Disable the following functions in the bootloader project. */
    output_ports_configure();
    interrupts_configure();
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */
    peripheral_modules_enable();
    bsp_non_existent_port_init();
} /* End of function hardware_setup() */

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

/***********************************************************************************************************************
* Function name: bsp_security_initial_configure
* Description  : Configures the Security initial settings
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void bsp_security_initial_configure(void)
{
#if (BSP_CFG_MCU_PART_VERSION == 0xA) ||(BSP_CFG_MCU_PART_VERSION == 0xB)
    uint8_t  dummy;
    uint32_t tmp_mstp;

    /* Protect off. */
    SYSTEM.PRCR.WORD = 0xA502;

    /* Store the value of the MSTPCR. */
    tmp_mstp = MSTP(TSIP);

    /* Release from the module-stop state. */
    MSTP(TSIP) = 0;

    /* Wait PCLKB 3 clocks. */
    dummy = PORT1.PODR.BYTE;

    /* WAIT_LOOP */
    while (dummy != PORT1.PODR.BYTE)
    {
        /* dummy read. */
        R_BSP_NOP();
    }

    /* Restore the value of the MSTPCR. */
    MSTP(TSIP) = tmp_mstp;

    /* Protect on. */
    SYSTEM.PRCR.WORD = 0xA500;
#else
    /* Do nothing. */
#endif
} /* End of function bsp_security_initial_configure() */

