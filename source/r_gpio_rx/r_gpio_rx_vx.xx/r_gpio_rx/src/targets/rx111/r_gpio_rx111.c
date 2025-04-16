/***********************************************************************************************************************
* Copyright (c) 2013 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx111.c
* Description  : Data for r_gpio_rx driver specific to RX111.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 17.07.2013 1.00    First Release
*         : 18.02.2014 1.10    Updated bitmasks
*         : 15.01.2021 3.70    Removed PH7 for RX111.
*         : 15.03.2025 5.11    Updated disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

#if defined(BSP_MCU_RX111)

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
 */
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
const uint8_t g_gpio_open_drain_n_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0xF0,     //PORT1   P14, P15, P16, P17
    0xC0,     //PORT2   P26, P27
    0x07,     //PORT3   P30 to P32
    0x00,     //PORT4   None
    0x00,     //PORT5   None
    0x00,     //PORT6
    0x00,     //PORT7
    0x00,     //PORT8
    0x00,     //PORT9
    0x5B,     //PORTA   PA0, PA1, PA3, PA4, PA6
    0xEB,     //PORTB   PB0, PB1, PB3, PB5 to PB7
    0xFF,     //PORTC   PC0 to PC7
    0x00,     //PORTD
    0xFF,     //PORTE   PE0 to PE7
    0x00,     //PORTF
    0x00,     //PORTG
    0x00,     //PORTH
    0x00,     //PORTJ   None
};

const uint8_t g_gpio_open_drain_p_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,     //PORT0   None
    0x10,     //PORT1   P14
    0x00,     //PORT2   None
    0x00,     //PORT3   None
    0x00,     //PORT4   None
    0x00,     //PORT5   None
    0x00,     //PORT6
    0x00,     //PORT7
    0x00,     //PORT8
    0x00,     //PORT9
    0x00,     //PORTA   None
    0x00,     //PORTB   None
    0x00,     //PORTC   None
    0x00,     //PORTD
    0x02,     //PORTE   PE1
    0x00,     //PORTF
    0x00,     //PORTG
    0x00,     //PORTH
    0x00,     //PORTJ   None
};

const uint8_t g_gpio_pull_up_support[GPIO_INFO_NUM_PORTS] =
{
    0x28,     //PORT0   P03, P05
    0xF0,     //PORT1   P14, P15, P16, P17
    0xC0,     //PORT2   P26, P27
    0x07,     //PORT3   P30 to P32
    0x00,     //PORT4   None
    0x30,     //PORT5   P54, P55
    0x00,     //PORT6
    0x00,     //PORT7
    0x00,     //PORT8
    0x00,     //PORT9
    0x5B,     //PORTA   PA0, PA1, PA3, PA4, PA6
    0xEB,     //PORTB   PB0, PB1, PB3, PB5 to PB7
    0xFF,     //PORTC   PC0 to PC7
    0x00,     //PORTD
    0xFF,     //PORTE   PE0 to PE7
    0x00,     //PORTF
    0x00,     //PORTG
    0x00,     //PORTH
    0x00,     //PORTJ   None
};
#endif

#endif

