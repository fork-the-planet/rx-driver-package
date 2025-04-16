/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx671.c
* Description  : Data for r_gpio_rx driver specific to RX671.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 07.04.2021 1.00    First Release
*         : 15.03.2025 5.11    Updated disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

#if defined(BSP_MCU_RX671)

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
 *       pin checking is filtered by the enumerated port_pin list for that package as defined in r_gpio_rx671.h.
 */

#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
const uint8_t g_gpio_open_drain_n_support[GPIO_INFO_NUM_PORTS] =
{
    0xAF,     //PORT0   P00 to P03, P05,P07
    0xFC,     //PORT1   P12 to P17
    0xFF,     //PORT2   P20 to P27
    0xDF,     //PORT3   P30 to P34, P36, P37
    0xFF,     //PORT4   P40 to P47
    0x7F,     //PORT5   P50 to P56
    0xFF,     //PORT6   P60 to P67
    0xFF,     //PORT7   P70 to P77
    0xCF,     //PORT8   P80 to P83, P86,P87
    0x0F,     //PORT9   P90 to P93
    0xFF,     //PORTA   PA0 to PA7
    0xFF,     //PORTB   PB0 to PB7
    0xFF,     //PORTC   PC0 to PC7
    0xFF,     //PORTD   PD0 to PD7
    0xFF,     //PORTE   PE0 to PE7
    0x20,     //PORTF   PF5
    0x00,     //PORTG   None
    0x06,     //PORTH   PH1, PH2
    0x28,     //PORTJ   PJ3, PJ5
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
    0x00,     //PORTB   None
    0x00,     //PORTC   None
    0x00,     //PORTD   None
    0x02,     //PORTE   E1
    0x00,     //PORTF   None
    0x00,     //PORTG   None
    0x00,     //PORTH   None
    0x00,     //PORTJ   None
};

const uint8_t g_gpio_pull_up_support[GPIO_INFO_NUM_PORTS] =
{
    0xAF,     //PORT0   P00 to P03, P05, P07
    0xFC,     //PORT1   P12 to P17
    0xFF,     //PORT2   P20 to P27
    0xDF,     //PORT3   P30 to P34, P36, P37
    0xFF,     //PORT4   P40 to P47
    0x7F,     //PORT5   P50 to P56
    0xFF,     //PORT6   P60 to P67
    0xFF,     //PORT7   P70 to P77
    0xCF,     //PORT8   P80 to P83, P86, P87
    0x0F,     //PORT9   P90 to P93
    0xFF,     //PORTA   PA0 to PA7
    0xFF,     //PORTB   PB0 to PB7
    0xFF,     //PORTC   PC0 to PC7
    0xFF,     //PORTD   PD0 to PD7
    0xFF,     //PORTE   PE0 to PE7
    0x20,     //PORTF   PF5
    0x00,     //PORTG   None
    0x06,     //PORTH   PH1, PH2
    0x28,     //PORTJ   PJ3, PJ5
};

const uint8_t g_gpio_dscr_support[GPIO_INFO_NUM_PORTS] =
{
    0x07,     //PORT0   P00 to P02
    0x1C,     //PORT1   P12 to P14
    0x80,     //PORT2   P27
    0x00,     //PORT3   None
    0x00,     //PORT4   None
    0x77,     //PORT5   P50 to P52, P54 to P56
    0x00,     //PORT6   None
    0xF4,     //PORT7   P72, P74 to P77
    0x0F,     //PORT8   P80 to P83
    0x0F,     //PORT9   P90 to P93
    0xFF,     //PORTA   PA0 to PA7
    0xFF,     //PORTB   PB0 to PB7
    0xFF,     //PORTC   PC0 to PC7
    0xFF,     //PORTD   PD0 to PD7
    0xFF,     //PORTE   PE0 to PE7
    0x00,     //PORTF   None
    0x00,     //PORTG   None
    0x06,     //PORTH   PH1, PH2
    0x00,     //PORTJ   None
};

const uint8_t g_gpio_dscr2_support[GPIO_INFO_NUM_PORTS] =
{
    0x07,     //PORT0   P00 to P02
    0x9C,     //PORT1   P12 to P14, P17
    0x8F,     //PORT2   P20 to P23, P27
    0x03,     //PORT3   P30, P31
    0x00,     //PORT4   None
    0x7F,     //PORT5   P50 to P56
    0x00,     //PORT6   None
    0xFD,     //PORT7   P70, P72 to P77
    0xCF,     //PORT8   P80 to P83, P86, P87
    0x0F,     //PORT9   P90 to P93
    0xFF,     //PORTA   PA0 to PA7
    0xFF,     //PORTB   PB0 to PB7
    0xFF,     //PORTC   PC0 to PC7
    0xFF,     //PORTD   PD0 to PD7
    0xFF,     //PORTE   PE0 to PE7
    0x00,     //PORTF   None
    0x00,     //PORTG   None
    0x06,     //PORTH   PH1, PH2
    0x00,     //PORTJ   None
};

#endif /* GPIO_CFG_PARAM_CHECKING_ENABLE */

#endif /* BSP_MCU_RX671 */

