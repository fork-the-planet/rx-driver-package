/***********************************************************************************************************************
* Copyright (c) 2015 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx23t.h
* Description  : Specifics for the r_gpio_rx driver for the RX23T.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.09.2015 1.00    First Release
*         : 07.04.2023 2.00    Added P36 and P37 for RX23T 64-pin, 52-pin, and 48-pin,
*                              Corrected the "Total of pins".
*         : 15.03.2025 5.11    Updated disclaimer.
***********************************************************************************************************************/
#ifndef GPIO_RX23T
#define GPIO_RX23T

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"
#if defined(BSP_MCU_RX23T)  //Prevents the compiler from finding multiple definitions of constant in this file.

/* Configuration for this package. */
#include "r_gpio_rx_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* General information about number of ports and pins on this device. */
#define GPIO_INFO_NUM_PORTS                 (15)    /* Includes PORTE for proper indexing */

#if (BSP_PACKAGE_PINS == 64)
    #define GPIO_INFO_NUM_PINS              (51)
#elif (BSP_PACKAGE_PINS == 52)
    #define GPIO_INFO_NUM_PINS              (42)
#elif (BSP_PACKAGE_PINS == 48)
    #define GPIO_INFO_NUM_PINS              (38)
#else
    #error "r_gpio_rx does not have information about this RX23T package. Please update r_gpio_rx23t.h"
#endif

/* Base registers used for offsets on output data registers. */
#define     GPIO_PRV_BASE_ADDR_OUTPUT           ((uint8_t volatile *)&PORT0.PODR.BYTE)
/* Base registers used for offsets on input data registers. */
#define     GPIO_PRV_BASE_ADDR_INPUT            ((uint8_t volatile *)&PORT0.PIDR.BYTE)
/* Base registers used for offsets on direction registers. */
#define     GPIO_PRV_BASE_ADDR_DIRECTION        ((uint8_t volatile *)&PORT0.PDR.BYTE)
/* Base registers used for offsets on mode registers. */
#define     GPIO_PRV_BASE_ADDR_MODE             ((uint8_t volatile *)&PORT0.PMR.BYTE)
/* Base registers used for offsets on output type registers. */
#define     GPIO_PRV_BASE_ADDR_OUT_TYPE         ((uint8_t volatile *)&PORT0.ODR0.BYTE)
/* Base registers used for offsets on pull-up registers. */
#define     GPIO_PRV_BASE_ADDR_PULL_UP          ((uint8_t volatile *)&PORT0.PCR.BYTE)
/* Base registers used for offsets on drive capacity control registers. */
#define     GPIO_PRV_BASE_ADDR_DSCR             ((uint8_t volatile *)&PORT0.DSCR.BYTE)

#define GPIO_DSCR_IS_SUPPORTED    //High-drive is supported for the RX23T

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
#if (BSP_PACKAGE_PINS == 64)
/* This enumerator has each available GPIO port on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_0 = 0x0000,
    GPIO_PORT_1 = 0x0100,
    GPIO_PORT_2 = 0x0200,
    GPIO_PORT_3 = 0x0300,
    GPIO_PORT_4 = 0x0400,
    GPIO_PORT_7 = 0x0700,
    GPIO_PORT_9 = 0x0900,
    GPIO_PORT_A = 0x0A00,
    GPIO_PORT_B = 0x0B00,
    GPIO_PORT_D = 0x0D00,
    GPIO_PORT_E = 0x0E00,
} gpio_port_t;

/* This enumerator has a bit mask for each available GPIO pin for the given port on this MCU. */
typedef enum
{
    GPIO_PORT0_PIN_MASK = 0x07,    /* Available pins: P00 to P02           */
    GPIO_PORT1_PIN_MASK = 0x03,    /* Available pins: P10, P11             */
    GPIO_PORT2_PIN_MASK = 0x1C,    /* Available pins: P22 to P24           */
    GPIO_PORT3_PIN_MASK = 0xCF,    /* Available pins: P30 to P33, P36, P37 */
    GPIO_PORT4_PIN_MASK = 0xFF,    /* Available pins: P40 to P47           */
    GPIO_PORT7_PIN_MASK = 0x7F,    /* Available pins: P70 to P76           */
    GPIO_PORT9_PIN_MASK = 0x1E,    /* Available pins: P91 to P94           */
    GPIO_PORTA_PIN_MASK = 0x3C,    /* Available pins: PA2 to PA5           */
    GPIO_PORTB_PIN_MASK = 0xFF,    /* Available pins: PB0 to PB7           */
    GPIO_PORTD_PIN_MASK = 0xF8,    /* Available pins: PD3 to PD7           */
    GPIO_PORTE_PIN_MASK = 0x04,    /* Available pins: PE2                  */
} gpio_pin_bit_mask_t;

/* This enumerator has each available GPIO pin on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_0_PIN_0 = 0x0000,
    GPIO_PORT_0_PIN_1 = 0x0001,
    GPIO_PORT_0_PIN_2 = 0x0002,
    GPIO_PORT_1_PIN_0 = 0x0100,
    GPIO_PORT_1_PIN_1 = 0x0101,
    GPIO_PORT_2_PIN_2 = 0x0202,
    GPIO_PORT_2_PIN_3 = 0x0203,
    GPIO_PORT_2_PIN_4 = 0x0204,
    GPIO_PORT_3_PIN_0 = 0x0300,
    GPIO_PORT_3_PIN_1 = 0x0301,
    GPIO_PORT_3_PIN_2 = 0x0302,
    GPIO_PORT_3_PIN_3 = 0x0303,
    GPIO_PORT_3_PIN_6 = 0x0306,
    GPIO_PORT_3_PIN_7 = 0x0307,
    GPIO_PORT_4_PIN_0 = 0x0400,
    GPIO_PORT_4_PIN_1 = 0x0401,
    GPIO_PORT_4_PIN_2 = 0x0402,
    GPIO_PORT_4_PIN_3 = 0x0403,
    GPIO_PORT_4_PIN_4 = 0x0404,
    GPIO_PORT_4_PIN_5 = 0x0405,
    GPIO_PORT_4_PIN_6 = 0x0406,
    GPIO_PORT_4_PIN_7 = 0x0407,
    GPIO_PORT_7_PIN_0 = 0x0700,
    GPIO_PORT_7_PIN_1 = 0x0701,
    GPIO_PORT_7_PIN_2 = 0x0702,
    GPIO_PORT_7_PIN_3 = 0x0703,
    GPIO_PORT_7_PIN_4 = 0x0704,
    GPIO_PORT_7_PIN_5 = 0x0705,
    GPIO_PORT_7_PIN_6 = 0x0706,
    GPIO_PORT_9_PIN_1 = 0x0901,
    GPIO_PORT_9_PIN_2 = 0x0902,
    GPIO_PORT_9_PIN_3 = 0x0903,
    GPIO_PORT_9_PIN_4 = 0x0904,
    GPIO_PORT_A_PIN_2 = 0x0A02,
    GPIO_PORT_A_PIN_3 = 0x0A03,
    GPIO_PORT_A_PIN_4 = 0x0A04,
    GPIO_PORT_A_PIN_5 = 0x0A05,
    GPIO_PORT_B_PIN_0 = 0x0B00,
    GPIO_PORT_B_PIN_1 = 0x0B01,
    GPIO_PORT_B_PIN_2 = 0x0B02,
    GPIO_PORT_B_PIN_3 = 0x0B03,
    GPIO_PORT_B_PIN_4 = 0x0B04,
    GPIO_PORT_B_PIN_5 = 0x0B05,
    GPIO_PORT_B_PIN_6 = 0x0B06,
    GPIO_PORT_B_PIN_7 = 0x0B07,
    GPIO_PORT_D_PIN_3 = 0x0D03,
    GPIO_PORT_D_PIN_4 = 0x0D04,
    GPIO_PORT_D_PIN_5 = 0x0D05,
    GPIO_PORT_D_PIN_6 = 0x0D06,
    GPIO_PORT_D_PIN_7 = 0x0D07,
    GPIO_PORT_E_PIN_2 = 0x0E02,
} gpio_port_pin_t;

#elif (BSP_PACKAGE_PINS == 52)
/* This enumerator has each available GPIO port on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_0 = 0x0000,
    GPIO_PORT_1 = 0x0100,
    GPIO_PORT_2 = 0x0200,
    GPIO_PORT_3 = 0x0300,
    GPIO_PORT_4 = 0x0400,
    GPIO_PORT_7 = 0x0700,
    GPIO_PORT_9 = 0x0900,
    GPIO_PORT_A = 0x0A00,
    GPIO_PORT_B = 0x0B00,
    GPIO_PORT_D = 0x0D00,
    GPIO_PORT_E = 0x0E00,
} gpio_port_t;

/* This enumerator has a bit mask for each available GPIO pin for the given port on this MCU. */
typedef enum
{
    GPIO_PORT0_PIN_MASK = 0x04,    /* Available pins: P02           */
    GPIO_PORT1_PIN_MASK = 0x03,    /* Available pins: P10, P11      */
    GPIO_PORT2_PIN_MASK = 0x1C,    /* Available pins: P22 to P24    */
    GPIO_PORT3_PIN_MASK = 0xC8,    /* Available pins: P33, P36, P37 */
    GPIO_PORT4_PIN_MASK = 0xFF,    /* Available pins: P40 to P47    */
    GPIO_PORT7_PIN_MASK = 0x7F,    /* Available pins: P70 to P76    */
    GPIO_PORT9_PIN_MASK = 0x18,    /* Available pins: P93, P94      */
    GPIO_PORTA_PIN_MASK = 0x2C,    /* Available pins: PA2, PA3, PA5 */
    GPIO_PORTB_PIN_MASK = 0xFF,    /* Available pins: PB0 to PB7    */
    GPIO_PORTD_PIN_MASK = 0x78,    /* Available pins: PD3 to PD6    */
    GPIO_PORTE_PIN_MASK = 0x04,    /* Available pins: PE2           */
} gpio_pin_bit_mask_t;

/* This enumerator has each available GPIO pin on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_0_PIN_2 = 0x0002,
    GPIO_PORT_1_PIN_0 = 0x0100,
    GPIO_PORT_1_PIN_1 = 0x0101,
    GPIO_PORT_2_PIN_2 = 0x0202,
    GPIO_PORT_2_PIN_3 = 0x0203,
    GPIO_PORT_2_PIN_4 = 0x0204,
    GPIO_PORT_3_PIN_3 = 0x0303,
    GPIO_PORT_3_PIN_6 = 0x0306,
    GPIO_PORT_3_PIN_7 = 0x0307,
    GPIO_PORT_4_PIN_0 = 0x0400,
    GPIO_PORT_4_PIN_1 = 0x0401,
    GPIO_PORT_4_PIN_2 = 0x0402,
    GPIO_PORT_4_PIN_3 = 0x0403,
    GPIO_PORT_4_PIN_4 = 0x0404,
    GPIO_PORT_4_PIN_5 = 0x0405,
    GPIO_PORT_4_PIN_6 = 0x0406,
    GPIO_PORT_4_PIN_7 = 0x0407,
    GPIO_PORT_7_PIN_0 = 0x0700,
    GPIO_PORT_7_PIN_1 = 0x0701,
    GPIO_PORT_7_PIN_2 = 0x0702,
    GPIO_PORT_7_PIN_3 = 0x0703,
    GPIO_PORT_7_PIN_4 = 0x0704,
    GPIO_PORT_7_PIN_5 = 0x0705,
    GPIO_PORT_7_PIN_6 = 0x0706,
    GPIO_PORT_9_PIN_3 = 0x0903,
    GPIO_PORT_9_PIN_4 = 0x0904,
    GPIO_PORT_A_PIN_2 = 0x0A02,
    GPIO_PORT_A_PIN_3 = 0x0A03,
    GPIO_PORT_A_PIN_5 = 0x0A05,
    GPIO_PORT_B_PIN_0 = 0x0B00,
    GPIO_PORT_B_PIN_1 = 0x0B01,
    GPIO_PORT_B_PIN_2 = 0x0B02,
    GPIO_PORT_B_PIN_3 = 0x0B03,
    GPIO_PORT_B_PIN_4 = 0x0B04,
    GPIO_PORT_B_PIN_5 = 0x0B05,
    GPIO_PORT_B_PIN_6 = 0x0B06,
    GPIO_PORT_B_PIN_7 = 0x0B07,
    GPIO_PORT_D_PIN_3 = 0x0D03,
    GPIO_PORT_D_PIN_4 = 0x0D04,
    GPIO_PORT_D_PIN_5 = 0x0D05,
    GPIO_PORT_D_PIN_6 = 0x0D06,
    GPIO_PORT_E_PIN_2 = 0x0E02,
} gpio_port_pin_t;

#elif (BSP_PACKAGE_PINS == 48)
/* This enumerator has each available GPIO port on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_1 = 0x0100,
    GPIO_PORT_2 = 0x0200,
    GPIO_PORT_3 = 0x0300,
    GPIO_PORT_4 = 0x0400,
    GPIO_PORT_7 = 0x0700,
    GPIO_PORT_9 = 0x0900,
    GPIO_PORT_A = 0x0A00,
    GPIO_PORT_B = 0x0B00,
    GPIO_PORT_D = 0x0D00,
    GPIO_PORT_E = 0x0E00,
} gpio_port_t;

/* This enumerator has a bit mask for each available GPIO pin for the given port on this MCU. */
typedef enum
{
    GPIO_PORT1_PIN_MASK = 0x03,    /* Available pins: P10, P11   */
    GPIO_PORT2_PIN_MASK = 0x1C,    /* Available pins: P22 to P24 */
    GPIO_PORT3_PIN_MASK = 0xC0,    /* Available pins: P36, P37   */
    GPIO_PORT4_PIN_MASK = 0xFF,    /* Available pins: P40 to P47 */
    GPIO_PORT7_PIN_MASK = 0x7F,    /* Available pins: P70 to P76 */
    GPIO_PORT9_PIN_MASK = 0x18,    /* Available pins: P93, P94   */
    GPIO_PORTA_PIN_MASK = 0x0C,    /* Available pins: PA2, PA3   */
    GPIO_PORTB_PIN_MASK = 0x7F,    /* Available pins: PB0 to PB6 */
    GPIO_PORTD_PIN_MASK = 0x78,    /* Available pins: PD3 to PD6 */
    GPIO_PORTE_PIN_MASK = 0x04,    /* Available pins: PE2        */
} gpio_pin_bit_mask_t;

/* This enumerator has each available GPIO pin on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_1_PIN_0 = 0x0100,
    GPIO_PORT_1_PIN_1 = 0x0101,
    GPIO_PORT_2_PIN_2 = 0x0202,
    GPIO_PORT_2_PIN_3 = 0x0203,
    GPIO_PORT_2_PIN_4 = 0x0204,
    GPIO_PORT_3_PIN_6 = 0x0306,
    GPIO_PORT_3_PIN_7 = 0x0307,
    GPIO_PORT_4_PIN_0 = 0x0400,
    GPIO_PORT_4_PIN_1 = 0x0401,
    GPIO_PORT_4_PIN_2 = 0x0402,
    GPIO_PORT_4_PIN_3 = 0x0403,
    GPIO_PORT_4_PIN_4 = 0x0404,
    GPIO_PORT_4_PIN_5 = 0x0405,
    GPIO_PORT_4_PIN_6 = 0x0406,
    GPIO_PORT_4_PIN_7 = 0x0407,
    GPIO_PORT_7_PIN_0 = 0x0700,
    GPIO_PORT_7_PIN_1 = 0x0701,
    GPIO_PORT_7_PIN_2 = 0x0702,
    GPIO_PORT_7_PIN_3 = 0x0703,
    GPIO_PORT_7_PIN_4 = 0x0704,
    GPIO_PORT_7_PIN_5 = 0x0705,
    GPIO_PORT_7_PIN_6 = 0x0706,
    GPIO_PORT_9_PIN_3 = 0x0903,
    GPIO_PORT_9_PIN_4 = 0x0904,
    GPIO_PORT_A_PIN_2 = 0x0A02,
    GPIO_PORT_A_PIN_3 = 0x0A03,
    GPIO_PORT_B_PIN_0 = 0x0B00,
    GPIO_PORT_B_PIN_1 = 0x0B01,
    GPIO_PORT_B_PIN_2 = 0x0B02,
    GPIO_PORT_B_PIN_3 = 0x0B03,
    GPIO_PORT_B_PIN_4 = 0x0B04,
    GPIO_PORT_B_PIN_5 = 0x0B05,
    GPIO_PORT_B_PIN_6 = 0x0B06,
    GPIO_PORT_D_PIN_3 = 0x0D03,
    GPIO_PORT_D_PIN_4 = 0x0D04,
    GPIO_PORT_D_PIN_5 = 0x0D05,
    GPIO_PORT_D_PIN_6 = 0x0D06,
    GPIO_PORT_E_PIN_2 = 0x0E02,
} gpio_port_pin_t;
#endif

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

#endif /* BSP_MCU_RX23T */
#endif /* GPIO_RX23T */
