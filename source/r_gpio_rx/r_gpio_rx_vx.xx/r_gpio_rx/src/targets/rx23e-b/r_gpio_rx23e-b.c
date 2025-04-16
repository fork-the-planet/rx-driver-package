/***********************************************************************************************************************
* Copyright (c) 2023 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx23e-b.c
* Description  : Data for r_gpio_rx driver specific to RX23E-B.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           29.05.2023 1.00    First Release
*           15.03.2025 5.11    Updated disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

#if defined(BSP_MCU_RX23E_B)

/* Public interface header file for this package. */
#include "r_gpio_rx_if.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* These arrays hold which pins have extra functionality. For example, not all pins have the option of enabling
 * open-drain N-channel output instead of the default CMOS output. Each entry in the array corresponds to a port.
 * Each bit in each entry corresponds to a pin on that port. If bit 3 of array entry [4] was set to 1 then that would
 * mean that PORT 4 PIN 3 supported the feature that array represented.
 *
 * These arrays are only used when GPIO_CFG_PARAM_CHECKING_ENABLE is set to 1 (checking enabled). If you know that
 * your code does not need to check the pins then you can set this macro to 0 and save a little execution time
 * and ROM space.
 *
 * Note: These arrays are defined for the largest package part. For smaller packages where some pins do not exist,
 *       pin checking is filtered by the enumerated port_pin list for that package as defined in r_gpio_rx23e-b.h.
 */

#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
const uint8_t g_gpio_open_drain_n_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0xFC,     //PORT1   P12 to P17
    0xFF,     //PORT2   P20 to P27
    0xC3,     //PORT3   P30, P31, P36, P37
    0x00,     //PORT4   None
    0x30,     //PORT5   P54, P55
    0xFF,     //PORT6   P60 to P67
    0x1F,     //PORT7   P70 to P74
    0x00,     //PORT8   None
    0x00,     //PORT9   None
    0x1F,     //PORTA   PA0 to PA4
    0x03,     //PORTB   PB0, PB1
    0xFF,     //PORTC   PC0 to PC7
    0x1F,     //PORTD   PD0 to PD4
    0x1F,     //PORTE   PE0 to PE4
};

const uint8_t g_gpio_open_drain_p_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0x80,     //PORT1   P17
    0x20,     //PORT2   P25
    0x00,     //PORT3   None
    0x00,     //PORT4   None
    0x00,     //PORT5   None
    0x00,     //PORT6   None
    0x00,     //PORT7   None
    0x00,     //PORT8   None
    0x00,     //PORT9   None
    0x00,     //PORTA   None
    0x00,     //PORTB   None
    0x00,     //PORTC   None
    0x00,     //PORTD   None
    0x00,     //PORTE   None
};

const uint8_t g_gpio_pull_up_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0xFC,     //PORT1   P12 to P17
    0xFF,     //PORT2   P20 to P27
    0xC3,     //PORT3   P30, P31, P36, P37
    0x00,     //PORT4   None
    0x30,     //PORT5   P54, P55
    0xFF,     //PORT6   P60 to P67
    0x1F,     //PORT7   P70 to P74
    0x00,     //PORT8   None
    0x00,     //PORT9   None
    0x1F,     //PORTA   PA0 to PA4
    0x03,     //PORTB   PB0, PB1
    0xFF,     //PORTC   PC0 to PC7
    0x1F,     //PORTD   PD0 to PD4
    0x1F,     //PORTE   PE0 to PE4
};

const uint8_t g_gpio_dscr_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0xFC,     //PORT1   P12 to P17
    0xFF,     //PORT2   P20 to P27
    0x03,     //PORT3   P30, P31
    0x00,     //PORT4   None
    0x30,     //PORT5   P54, P55
    0xFF,     //PORT6   P60 to P67
    0x1F,     //PORT7   P70 to P74
    0x00,     //PORT8   None
    0x00,     //PORT9   None
    0x1F,     //PORTA   PA0 to PA4
    0x03,     //PORTB   PB0, PB1
    0xFF,     //PORTC   PC0 to PC7
    0x1F,     //PORTD   PD0 to PD4
    0x1F,     //PORTE   PE0 to PE4
};

#endif /* GPIO_CFG_PARAM_CHECKING_ENABLE == 1 */
#endif /* definedBSP_MCU_RX23E_B */

