/***********************************************************************************************************************
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx65n.c
* Description  : Data for r_gpio_rx driver specific to RX65N.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.10.2016 1.00    First Release
*         : 21.07.2017 2.30    Updated for RX65N-2MB.
*         : 01.02.2019 2.50    Updated for RX65N-64pin.
*         : 07.04.2023 3.00    Updated for RX65N (with products with 1 Mbyte of code flash memory or less)
*                                for the g_gpio_dscr_support and g_gpio_dscr2_support structures.
*         : 15.03.2025 5.11    Updated disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

#if defined(BSP_MCU_RX65N)

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
 *       pin checking is filtered by the enumerated port_pin list for that package as defined in r_gpio_rx65N.h.
 */
#if (GPIO_CFG_PARAM_CHECKING_ENABLE == 1)
const uint8_t g_gpio_open_drain_n_support[GPIO_INFO_NUM_PORTS] =
{
    0xAF,    // P0: P00 to P03, P05, P07
    0xFF,    // P1: P10 to P17
    0xFF,    // P2: P20 to P27
    0xDF,    // P3: P30 to P34, P36, P37
    0xFF,    // P4: P40 to P47
    0xFF,    // P5: P50 to P57
    0xFF,    // P6: P60 to P67
    0xFF,    // P7: P70 to P77
    0xFF,    // P8: P80 to P87
    0xFF,    // P9: P90 to P97
    0xFF,    // PA: PA0 to PA7
    0xFF,    // PB: PB0 to PB7
    0xFF,    // PC: PC0 to PC7
    0xFF,    // PD: PD0 to PD7
    0xFF,    // PE: PE0 to PE7
    0x3F,    // PF: PF0 to PF5
    0xFF,    // PG: PG0 to PG7
    0x00,    // PH: -
    0x2F,    // PJ: PJ0 to PJ3, PJ5
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
    0x02,    // PE: PE1
    0x00,    // PF: -
    0x00,    // PG: -
    0x00,    // PH: -
    0x00,    // PJ: -
};

const uint8_t g_gpio_pull_up_support[GPIO_INFO_NUM_PORTS] =
{
    0xAF,    // P0: P00 to P03, P05, P07
    0xFF,    // P1: P10 to P17
    0xFF,    // P2: P20 to P27
    0xDF,    // P3: P30 to P34, P36, P37
    0xFF,    // P4: P40 to P47
    0xFF,    // P5: P50 to P57
    0xFF,    // P6: P60 to P67
    0xFF,    // P7: P70 to P77
    0xFF,    // P8: P80 to P87
    0xFF,    // P9: P90 to P97
    0xFF,    // PA: PA0 to PA7
    0xFF,    // PB: PB0 to PB7
    0xFF,    // PC: PC0 to PC7
    0xFF,    // PD: PD0 to PD7
    0xFF,    // PE: PE0 to PE7
    0x3F,    // PF: PF0 to PF5
    0xFF,    // PG: PG0 to PG7
    0x00,    // PH: -
    0x2F,    // PJ: PJ0 to PJ3, PJ5
};
#if (BSP_CFG_MCU_PART_MEMORY_SIZE == 0xC) || (BSP_CFG_MCU_PART_MEMORY_SIZE == 0xE)
/* Products with at least 1.5 Mbytes of code flash memory */
const uint8_t g_gpio_dscr_support[GPIO_INFO_NUM_PORTS] =
{
    0x07,    // P0: P00 to P02
    0x1E,    // P1: P11 to P14
    0x80,    // P2: P27
    0x00,    // P3: -
    0x00,    // P4: -
    0xF7,    // P5: P50 to P52, P54 to P57
    0x00,    // P6: -
    0xF4,    // P7: P72, P74 to P77
    0x3F,    // P8: P80 to P85
    0xFF,    // P9: P90 to P97
    0xFF,    // PA: PA0 to PA7
    0xFF,    // PB: PB0 to PB7
    0xFF,    // PC: PC0 to PC7
    0xFF,    // PD: PD0 to PD7
    0xFF,    // PE: PE0 to PE7
    0x00,    // PF: -
    0x03,    // PG: PG0 to PG1
    0x00,    // PH: -
    0x07,    // PJ: PJ0 to PJ2
};

const uint8_t g_gpio_dscr2_support[GPIO_INFO_NUM_PORTS] =
{
    0x07,    // P0: P00 to P02
    0x9E,    // P1: P11 to P14, P17
    0x8F,    // P2: P20 to P23, P27
    0x03,    // P3: P30 to P31
    0x00,    // P4: -
    0xFF,    // P5: P50 to P57
    0x00,    // P6: -
    0xFD,    // P7: P70, P72 to P77
    0xBF,    // P8: P80 to P85, P87
    0xFF,    // P9: P90 to P97
    0xFF,    // PA: PA0 to PA7
    0xFF,    // PB: PB0 to PB7
    0xFF,    // PC: PC0 to PC7
    0xFF,    // PD: PD0 to PD7
    0xFF,    // PE: PE0 to PE7
    0x00,    // PF: -
    0xFF,    // PG: PG0 to PG7
    0x00,    // PH: -
    0x07,    // PJ: PJ0 to PJ2
};
#else
/* Products with 1 Mbyte of code flash memory or less */
const uint8_t g_gpio_dscr_support[GPIO_INFO_NUM_PORTS] =
{
    0x07,    // P0: P00 to P02
    0x00,    // P1: -
    0x80,    // P2: P27
    0x00,    // P3: -
    0x00,    // P4: -
    0x47,    // P5: P50 to P52, P56
    0x00,    // P6: -
    0x00,    // P7: -
    0x00,    // P8: -
    0x0F,    // P9: P90 to P93
    0xFF,    // PA: PA0 to PA7
    0xFF,    // PB: PB0 to PB7
    0xFF,    // PC: PC0 to PC7
    0xFF,    // PD: PD0 to PD7
    0xFF,    // PE: PE0 to PE7
    0x00,    // PF: -
    0x00,    // PG: -
    0x00,    // PH: -
    0x00,    // PJ: -
};

const uint8_t g_gpio_dscr2_support[GPIO_INFO_NUM_PORTS] =
{
    0x07,    // P0: P00 to P02
    0x00,    // P1: -
    0x80,    // P2: P27
    0x03,    // P3: P30 to P31
    0x00,    // P4: -
    0x7F,    // P5: P50 to P56
    0x00,    // P6: -
    0xF9,    // P7: P70, P73 to P77
    0x0F,    // P8: P80 to P83
    0x0F,    // P9: P90 to P93
    0xFF,    // PA: PA0 to PA7
    0xFF,    // PB: PB0 to PB7
    0xFF,    // PC: PC0 to PC7
    0xFF,    // PD: PD0 to PD7
    0xFF,    // PE: PE0 to PE7
    0x00,    // PF: -
    0x00,    // PG: -
    0x00,    // PH: -
    0x00,    // PJ: -
};
#endif


#endif

#endif

