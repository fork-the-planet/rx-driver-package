/***********************************************************************************************************************
* Copyright (c) 2019 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx13t.c
* Description  : Data for r_gpio_rx driver specific to RX13T.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 25.11.2019 1.00    First Release
*         : 15.03.2025 5.11    Updated disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

#if defined(BSP_MCU_RX13T)

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
 *       pin checking is filtered by the enumerated port_pin list for that package as defined in r_gpio_rx13t.h.
 */

#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
const uint8_t g_gpio_open_drain_n_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0x03,     //PORT1   P10 to P11
    0x1C,     //PORT2   P22, P23, P24
    0xC0,     //PORT3   P36, P37
    0x00,     //PORT4   None
    0x00,     //PORT5   None
    0x00,     //PORT6   None
    0x7F,     //PORT7   P70 to P76
    0x00,     //PORT8   None
    0x18,     //PORT9   P93, P94
    0x0C,     //PORTA   PA2, PA3
    0xFF,     //PORTB   PB0 to PB7
    0x00,     //PORTC   None
    0x78,     //PORTD   PD3 to PD6
    0x00,     //PORTE   None
    0x00,     //PORTF   None
    0x00,     //PORTG   None
    0x00,     //PORTH   None
    0x00,     //PORTJ   None
};

const uint8_t g_gpio_open_drain_p_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0x00,     //PORT1   None
    0x00,     //PORT2   None
    0x00,     //PORT3   None
    0x00,     //PORT4   None
    0x00,     //PORT5   None
    0x00,     //PORT6   None
    0x00,     //PORT7   None
    0x00,     //PORT8   None
    0x00,     //PORT9   None
    0x00,     //PORTA   None
    0x01,     //PORTB   PB0
    0x00,     //PORTC   None
    0x00,     //PORTD   None
    0x00,     //PORTE   None
    0x00,     //PORTF   None
    0x00,     //PORTG   None
    0x00,     //PORTH   None
    0x00,     //PORTJ   None
};

const uint8_t g_gpio_pull_up_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0x03,     //PORT1   P10 to P11
    0x1C,     //PORT2   P22, P23, P24
    0xC0,     //PORT3   P36, P37
    0xFF,     //PORT4   P40 to P47
    0x00,     //PORT5   None
    0x00,     //PORT6   None
    0x7F,     //PORT7   P70 to P76
    0x00,     //PORT8   None
    0x18,     //PORT9   P93, P94
    0x0C,     //PORTA   PA2, PA3
    0xFF,     //PORTB   PB0 to PB7
    0x00,     //PORTC   None
    0x78,     //PORTD   PD3 to PD6
    0x00,     //PORTE   None
    0x00,     //PORTF   None
    0x00,     //PORTG   None
    0x00,     //PORTH   None
    0x00,     //PORTJ   None
};

const uint8_t g_gpio_dscr_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0x03,     //PORT1   P10 to P11
    0x1C,     //PORT2   P22, P23, P24
    0x00,     //PORT3   None
    0x00,     //PORT4   None
    0x00,     //PORT5   None
    0x00,     //PORT6   None
    0x7F,     //PORT7   P70 to P76
    0x00,     //PORT8   None
    0x18,     //PORT9   P93, P94
    0x0C,     //PORTA   PA2, PA3
    0xFF,     //PORTB   PB0 to PB7
    0x00,     //PORTC   None
    0x78,     //PORTD   PD3 to PD6
    0x00,     //PORTE   None
    0x00,     //PORTF   None
    0x00,     //PORTG   None
    0x00,     //PORTH   None
    0x00,     //PORTJ   None
};

#endif

#endif

