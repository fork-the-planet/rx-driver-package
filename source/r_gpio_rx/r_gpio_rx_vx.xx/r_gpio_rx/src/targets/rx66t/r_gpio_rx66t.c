/***********************************************************************************************************************
* Copyright (c) 2018 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx66t.c
* Description  : Data for r_gpio_rx driver specific to RX66T.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 28.09.2018 1.00    First Release
*         : 15.03.2025 5.11    Updated disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

#if defined(BSP_MCU_RX66T)

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
 *       pin checking is filtered by the enumerated port_pin list for that package as defined in r_gpio_rx66t.h.
 */
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
const uint8_t g_gpio_open_drain_n_support[GPIO_INFO_NUM_PORTS] =
{
    0x03,    // P0: P00, P01
    0xFF,    // P1: P10 to P17
    0xFF,    // P2: P20 to P27
    0xFF,    // P3: P30 to P37
    0x88,    // P4: P43, P47
    0x3F,    // P5: P50 to P55
    0x3F,    // P6: P60 to P65
    0x7F,    // P7: P70 to P76
    0x07,    // P8: P80 to P82
    0x7F,    // P9: P90 to P96
    0xFF,    // PA: PA0 to PA7
    0xFF,    // PB: PB0 to PB7
    0x7F,    // PC: PC0 to PC6
    0xFF,    // PD: PD0 to PD7
    0x7B,    // PE: PE0, PE1, PE3 to PE6
    0x0F,    // PF: PF0 to PF3
    0x07,    // PG: PG0 to PG2
    0xEE,    // PH: PH1 to PH3, PH5 to PH7
    0x00,    // PJ: -
    0x07,    // PK: PK0 to PK2
};

const uint8_t g_gpio_open_drain_p_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,    // P0: -
    0x00,    // P1: -
    0x00,    // P2: -
    0x00,    // P3: -
    0x00,    // P4: -
    0x00,    // P5: -
    0x00,    // P6: -
    0x00,    // P7: -
    0x00,    // P8: -
    0x00,    // P9: -
    0x00,    // PA: -
    0x00,    // PB: -
    0x00,    // PC: -
    0x00,    // PD: -
    0x00,    // PE: -
    0x00,    // PF: -
    0x00,    // PG: -
    0x00,    // PH: -
    0x00,    // PJ: -
    0x00,    // PK: -
};

const uint8_t g_gpio_pull_up_support[GPIO_INFO_NUM_PORTS] =
{
    0x03,    // P0: P00, P01
    0xFF,    // P1: P10 to P17
    0xFF,    // P2: P20 to P27
    0xFF,    // P3: P30 to P37
    0x88,    // P4: P43, P47
    0x3F,    // P5: P50 to P55
    0x3F,    // P6: P60 to P65
    0x7F,    // P7: P70 to P76
    0x07,    // P8: P80 to P82
    0x7F,    // P9: P90 to P96
    0xFF,    // PA: PA0 to PA7
    0xFF,    // PB: PB0 to PB7
    0x7F,    // PC: PC0 to PC6
    0xFF,    // PD: PD0 to PD7
    0x7B,    // PE: PE0, PE1, PE3 to PE6
    0x0F,    // PF: PF0 to PF3
    0x07,    // PG: PG0 to PG2
    0xEE,    // PH: PH1 to PH3, PH5 to PH7
    0x00,    // PJ: -
    0x07,    // PK: PK0 to PK2
};

const uint8_t g_gpio_dscr_support[GPIO_INFO_NUM_PORTS] =
{
    0x03,    // P0: P00, P01
    0xFF,    // P1: P10 to P17
    0xFF,    // P2: P20 to P27
    0x3F,    // P3: P30 to P35
    0x00,    // P4: -
    0x00,    // P5: -
    0x00,    // P6: -
    0x7F,    // P7: P70 to P76
    0x07,    // P8: P80 to P82
    0x7F,    // P9: P90 to P96
    0xFF,    // PA: PA0 to PA7
    0xFF,    // PB: PB0 to PB7
    0x7F,    // PC: PC0 to PC6
    0xFF,    // PD: PD0 to PD7
    0x7B,    // PE: PE0, PE1, PE3 to PE6
    0x0F,    // PF: PF0 to PF3
    0x07,    // PG: PG0 to PG2
    0x00,    // PH: -
    0x00,    // PJ: -
    0x07,    // PK: PK0 to PK2
};

const uint8_t g_gpio_dscr2_support[GPIO_INFO_NUM_PORTS] =
{
    0x00,    // P0: -
    0x00,    // P1: -
    0x00,    // P2: -
    0x00,    // P3: -
    0x00,    // P4: -
    0x00,    // P5: -
    0x00,    // P6: -
    0x7E,    // P7: P71 to P76
    0x02,    // P8: P81
    0x3F,    // P9: P90 to P95
    0x00,    // PA: -
    0x20,    // PB: PB5
    0x00,    // PC: -
    0x08,    // PD: PD3
    0x00,    // PE: -
    0x00,    // PF: -
    0x00,    // PG: -
    0x00,    // PH: -
    0x00,    // PJ: -
    0x00,    // PK: -
};

#endif /* GPIO_CFG_PARAM_CHECKING_ENABLE */

#endif /* BSP_MCU_RX66T */

