/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_gpio_rx64m.h
* Description  : Specifics for the r_gpio_rx driver for the RX64M.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 22.05.2014 1.00    First Release
*         : 02.04.2015 1.10    Added definitions for P20 and P21 for 144, 145 pin package.  Corrected comments.
*         :                    Removed definitions for P10, P11 for 144, 145 pin package. Corrected comments.
*         :                    Added DSCR support
*         : 03.06.2015 1.11    Fixed an error in the definition for GPIO_PRV_BASE_ADDR_DSCR.
*         : 24.04.2015 1.12    Added the compiler directive: "#if defined(BSP_MCU_RX64M)"
*         : 07.04.2023 2.00    Removed define PIN MASK is not provided.
*         : 15.03.2025 5.11    Updated disclaimer.
***********************************************************************************************************************/
#ifndef GPIO_RX64M
#define GPIO_RX64M

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"
#if defined(BSP_MCU_RX64M)  //Prevents the compiler from finding multiple definitions of constant in this file.

/* Configuration for this package. */
#include "r_gpio_rx_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* General information about number of ports and pins on this device. */
#define GPIO_INFO_NUM_PORTS                 (19)    /* Includes PORTH for proper indexing */

#if   ((BSP_PACKAGE_PINS == 176) || (BSP_PACKAGE_PINS == 177))
    #define GPIO_INFO_NUM_PINS              (128)
#elif ((BSP_PACKAGE_PINS == 144) || (BSP_PACKAGE_PINS == 145))
    #define GPIO_INFO_NUM_PINS              (112)
#elif (BSP_PACKAGE_PINS == 100)
    #define GPIO_INFO_NUM_PINS              (79)
#else
    #error "r_gpio_rx does not have information about this RX64M package. Please update r_gpio_rx64m.h"
#endif

/* For testing we will allocate virtual IO ports. */
#if !defined(GPIO_TESTING)
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
#endif

#define GPIO_DSCR_IS_SUPPORTED    //High-drive is supported for the RX64M

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
#if ((BSP_PACKAGE_PINS == 177) || (BSP_PACKAGE_PINS == 176))
/* This enumerator has each available GPIO port on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_0 = 0x0000,
    GPIO_PORT_1 = 0x0100,
    GPIO_PORT_2 = 0x0200,
    GPIO_PORT_3 = 0x0300,
    GPIO_PORT_4 = 0x0400,
    GPIO_PORT_5 = 0x0500,
    GPIO_PORT_6 = 0x0600,
    GPIO_PORT_7 = 0x0700,
    GPIO_PORT_8 = 0x0800,
    GPIO_PORT_9 = 0x0900,
    GPIO_PORT_A = 0x0A00,
    GPIO_PORT_B = 0x0B00,
    GPIO_PORT_C = 0x0C00,
    GPIO_PORT_D = 0x0D00,
    GPIO_PORT_E = 0x0E00,
    GPIO_PORT_F = 0x0F00,
    GPIO_PORT_G = 0x1000,
    GPIO_PORT_J = 0x1200,
} gpio_port_t;

/* This enumerator has a bit mask for each available GPIO pin for the given port on this MCU. */
typedef enum
{
    GPIO_PORT0_PIN_MASK = 0xAF,    /* Available pins: P00 to P03, P05, P07 */
    GPIO_PORT1_PIN_MASK = 0xFF,    /* Available pins: P10 to P17           */
    GPIO_PORT2_PIN_MASK = 0xFF,    /* Available pins: P20 to P27           */
    GPIO_PORT3_PIN_MASK = 0xFF,    /* Available pins: P30 to P37           */
    GPIO_PORT4_PIN_MASK = 0xFF,    /* Available pins: P40 to P47           */
    GPIO_PORT5_PIN_MASK = 0x0F,    /* Available pins: P50 to P53           */
    GPIO_PORT6_PIN_MASK = 0xFF,    /* Available pins: P60 to P67           */
    GPIO_PORT7_PIN_MASK = 0xFF,    /* Available pins: P70 to P77           */
    GPIO_PORT8_PIN_MASK = 0xCF,    /* Available pins: P80 to P83, P86, P87 */
    GPIO_PORT9_PIN_MASK = 0xFF,    /* Available pins: P90 to P97           */
    GPIO_PORTA_PIN_MASK = 0xFF,    /* Available pins: PA0 to PA7           */
    GPIO_PORTB_PIN_MASK = 0xFF,    /* Available pins: PB0 to PB7           */
    GPIO_PORTC_PIN_MASK = 0xFF,    /* Available pins: PC0 to PC7           */
    GPIO_PORTD_PIN_MASK = 0xFF,    /* Available pins: PD0 to PD7           */
    GPIO_PORTE_PIN_MASK = 0xFF,    /* Available pins: PE0 to PE7           */
    GPIO_PORTF_PIN_MASK = 0x3F,    /* Available pins: PF0 to PF5           */
    GPIO_PORTG_PIN_MASK = 0xFF,    /* Available pins: PG0 to PG7           */
    GPIO_PORTJ_PIN_MASK = 0x28,    /* Available pins: PJ3, PJ5             */
} gpio_pin_bit_mask_t;

typedef enum
{
    GPIO_PORT_0_PIN_0 = 0x0000,
    GPIO_PORT_0_PIN_1 = 0x0001,
    GPIO_PORT_0_PIN_2 = 0x0002,
    GPIO_PORT_0_PIN_3 = 0x0003,
    GPIO_PORT_0_PIN_5 = 0x0005,
    GPIO_PORT_0_PIN_7 = 0x0007,
    GPIO_PORT_1_PIN_0 = 0x0100,
    GPIO_PORT_1_PIN_1 = 0x0101,
    GPIO_PORT_1_PIN_2 = 0x0102,
    GPIO_PORT_1_PIN_3 = 0x0103,
    GPIO_PORT_1_PIN_4 = 0x0104,
    GPIO_PORT_1_PIN_5 = 0x0105,
    GPIO_PORT_1_PIN_6 = 0x0106,
    GPIO_PORT_1_PIN_7 = 0x0107,
    GPIO_PORT_2_PIN_0 = 0x0200,
    GPIO_PORT_2_PIN_1 = 0x0201,
    GPIO_PORT_2_PIN_2 = 0x0202,
    GPIO_PORT_2_PIN_3 = 0x0203,
    GPIO_PORT_2_PIN_4 = 0x0204,
    GPIO_PORT_2_PIN_5 = 0x0205,
    GPIO_PORT_2_PIN_6 = 0x0206,
    GPIO_PORT_2_PIN_7 = 0x0207,
    GPIO_PORT_3_PIN_0 = 0x0300,
    GPIO_PORT_3_PIN_1 = 0x0301,
    GPIO_PORT_3_PIN_2 = 0x0302,
    GPIO_PORT_3_PIN_3 = 0x0303,
    GPIO_PORT_3_PIN_4 = 0x0304,
    GPIO_PORT_3_PIN_5 = 0x0305,
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
    GPIO_PORT_5_PIN_0 = 0x0500,
    GPIO_PORT_5_PIN_1 = 0x0501,
    GPIO_PORT_5_PIN_2 = 0x0502,
    GPIO_PORT_5_PIN_3 = 0x0503,
    GPIO_PORT_6_PIN_0 = 0x0600,
    GPIO_PORT_6_PIN_1 = 0x0601,
    GPIO_PORT_6_PIN_2 = 0x0602,
    GPIO_PORT_6_PIN_3 = 0x0603,
    GPIO_PORT_6_PIN_4 = 0x0604,
    GPIO_PORT_6_PIN_5 = 0x0605,
    GPIO_PORT_6_PIN_6 = 0x0606,
    GPIO_PORT_6_PIN_7 = 0x0607,
    GPIO_PORT_7_PIN_0 = 0x0700,
    GPIO_PORT_7_PIN_1 = 0x0701,
    GPIO_PORT_7_PIN_2 = 0x0702,
    GPIO_PORT_7_PIN_3 = 0x0703,
    GPIO_PORT_7_PIN_4 = 0x0704,
    GPIO_PORT_7_PIN_5 = 0x0705,
    GPIO_PORT_7_PIN_6 = 0x0706,
    GPIO_PORT_7_PIN_7 = 0x0707,
    GPIO_PORT_8_PIN_0 = 0x0800,
    GPIO_PORT_8_PIN_1 = 0x0801,
    GPIO_PORT_8_PIN_2 = 0x0802,
    GPIO_PORT_8_PIN_3 = 0x0803,
    GPIO_PORT_8_PIN_6 = 0x0806,
    GPIO_PORT_8_PIN_7 = 0x0807,
    GPIO_PORT_9_PIN_0 = 0x0900,
    GPIO_PORT_9_PIN_1 = 0x0901,
    GPIO_PORT_9_PIN_2 = 0x0902,
    GPIO_PORT_9_PIN_3 = 0x0903,
    GPIO_PORT_9_PIN_4 = 0x0904,
    GPIO_PORT_9_PIN_5 = 0x0905,
    GPIO_PORT_9_PIN_6 = 0x0906,
    GPIO_PORT_9_PIN_7 = 0x0907,
    GPIO_PORT_A_PIN_0 = 0x0A00,
    GPIO_PORT_A_PIN_1 = 0x0A01,
    GPIO_PORT_A_PIN_2 = 0x0A02,
    GPIO_PORT_A_PIN_3 = 0x0A03,
    GPIO_PORT_A_PIN_4 = 0x0A04,
    GPIO_PORT_A_PIN_5 = 0x0A05,
    GPIO_PORT_A_PIN_6 = 0x0A06,
    GPIO_PORT_A_PIN_7 = 0x0A07,
    GPIO_PORT_B_PIN_0 = 0x0B00,
    GPIO_PORT_B_PIN_1 = 0x0B01,
    GPIO_PORT_B_PIN_2 = 0x0B02,
    GPIO_PORT_B_PIN_3 = 0x0B03,
    GPIO_PORT_B_PIN_4 = 0x0B04,
    GPIO_PORT_B_PIN_5 = 0x0B05,
    GPIO_PORT_B_PIN_6 = 0x0B06,
    GPIO_PORT_B_PIN_7 = 0x0B07,
    GPIO_PORT_C_PIN_0 = 0x0C00,
    GPIO_PORT_C_PIN_1 = 0x0C01,
    GPIO_PORT_C_PIN_2 = 0x0C02,
    GPIO_PORT_C_PIN_3 = 0x0C03,
    GPIO_PORT_C_PIN_4 = 0x0C04,
    GPIO_PORT_C_PIN_5 = 0x0C05,
    GPIO_PORT_C_PIN_6 = 0x0C06,
    GPIO_PORT_C_PIN_7 = 0x0C07,
    GPIO_PORT_D_PIN_0 = 0x0D00,
    GPIO_PORT_D_PIN_1 = 0x0D01,
    GPIO_PORT_D_PIN_2 = 0x0D02,
    GPIO_PORT_D_PIN_3 = 0x0D03,
    GPIO_PORT_D_PIN_4 = 0x0D04,
    GPIO_PORT_D_PIN_5 = 0x0D05,
    GPIO_PORT_D_PIN_6 = 0x0D06,
    GPIO_PORT_D_PIN_7 = 0x0D07,
    GPIO_PORT_E_PIN_0 = 0x0E00,
    GPIO_PORT_E_PIN_1 = 0x0E01,
    GPIO_PORT_E_PIN_2 = 0x0E02,
    GPIO_PORT_E_PIN_3 = 0x0E03,
    GPIO_PORT_E_PIN_4 = 0x0E04,
    GPIO_PORT_E_PIN_5 = 0x0E05,
    GPIO_PORT_E_PIN_6 = 0x0E06,
    GPIO_PORT_E_PIN_7 = 0x0E07,
    GPIO_PORT_F_PIN_0 = 0x0F00,
    GPIO_PORT_F_PIN_1 = 0x0F01,
    GPIO_PORT_F_PIN_2 = 0x0F02,
    GPIO_PORT_F_PIN_3 = 0x0F03,
    GPIO_PORT_F_PIN_4 = 0x0F04,
    GPIO_PORT_F_PIN_5 = 0x0F05,
    GPIO_PORT_G_PIN_0 = 0x1000,
    GPIO_PORT_G_PIN_1 = 0x1001,
    GPIO_PORT_G_PIN_2 = 0x1002,
    GPIO_PORT_G_PIN_3 = 0x1003,
    GPIO_PORT_G_PIN_4 = 0x1004,
    GPIO_PORT_G_PIN_5 = 0x1005,
    GPIO_PORT_G_PIN_6 = 0x1006,
    GPIO_PORT_G_PIN_7 = 0x1007,
    GPIO_PORT_J_PIN_3 = 0x1203,
    GPIO_PORT_J_PIN_5 = 0x1205,
} gpio_port_pin_t;

#elif ((BSP_PACKAGE_PINS == 145) || (BSP_PACKAGE_PINS == 144))
/* This enumerator has each available GPIO port on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_0 = 0x0000,
    GPIO_PORT_1 = 0x0100,
    GPIO_PORT_2 = 0x0200,
    GPIO_PORT_3 = 0x0300,
    GPIO_PORT_4 = 0x0400,
    GPIO_PORT_5 = 0x0500,
    GPIO_PORT_6 = 0x0600,
    GPIO_PORT_7 = 0x0700,
    GPIO_PORT_8 = 0x0800,
    GPIO_PORT_9 = 0x0900,
    GPIO_PORT_A = 0x0A00,
    GPIO_PORT_B = 0x0B00,
    GPIO_PORT_C = 0x0C00,
    GPIO_PORT_D = 0x0D00,
    GPIO_PORT_E = 0x0E00,
    GPIO_PORT_F = 0x0F00,
    GPIO_PORT_J = 0x1200,
} gpio_port_t;

/* This enumerator has a bit mask for each available GPIO pin for the given port on this MCU. */
typedef enum
{
    GPIO_PORT0_PIN_MASK = 0xAF,    /* Available pins: P00 to P03, P05, P07 */
    GPIO_PORT1_PIN_MASK = 0xFC,    /* Available pins: P12 to P17           */
    GPIO_PORT2_PIN_MASK = 0xFF,    /* Available pins: P20 to P27           */
    GPIO_PORT3_PIN_MASK = 0xFF,    /* Available pins: P30 to P37           */
    GPIO_PORT4_PIN_MASK = 0xFF,    /* Available pins: P40 to P47           */
    GPIO_PORT5_PIN_MASK = 0x7F,    /* Available pins: P50 to P56           */
    GPIO_PORT6_PIN_MASK = 0xFF,    /* Available pins: P60 to P67           */
    GPIO_PORT7_PIN_MASK = 0xFF,    /* Available pins: P70 to P77           */
    GPIO_PORT8_PIN_MASK = 0xCF,    /* Available pins: P80 to P83, P86, P87 */
    GPIO_PORT9_PIN_MASK = 0x0F,    /* Available pins: P90 to P93           */
    GPIO_PORTA_PIN_MASK = 0xFF,    /* Available pins: PA0 to PA7           */
    GPIO_PORTB_PIN_MASK = 0xFF,    /* Available pins: PB0 to PB7           */
    GPIO_PORTC_PIN_MASK = 0xFF,    /* Available pins: PC0 to PC7           */
    GPIO_PORTD_PIN_MASK = 0xFF,    /* Available pins: PD0 to PD7           */
    GPIO_PORTE_PIN_MASK = 0xFF,    /* Available pins: PE0 to PE7           */
    GPIO_PORTF_PIN_MASK = 0x20,    /* Available pins: PF5                  */
    GPIO_PORTJ_PIN_MASK = 0x28,    /* Available pins: PJ3, PJ5             */
} gpio_pin_bit_mask_t;

typedef enum
{
    GPIO_PORT_0_PIN_0 = 0x0000,
    GPIO_PORT_0_PIN_1 = 0x0001,
    GPIO_PORT_0_PIN_2 = 0x0002,
    GPIO_PORT_0_PIN_3 = 0x0003,
    GPIO_PORT_0_PIN_5 = 0x0005,
    GPIO_PORT_0_PIN_7 = 0x0007,
    GPIO_PORT_1_PIN_2 = 0x0102,
    GPIO_PORT_1_PIN_3 = 0x0103,
    GPIO_PORT_1_PIN_4 = 0x0104,
    GPIO_PORT_1_PIN_5 = 0x0105,
    GPIO_PORT_1_PIN_6 = 0x0106,
    GPIO_PORT_1_PIN_7 = 0x0107,
    GPIO_PORT_2_PIN_0 = 0x0200,
    GPIO_PORT_2_PIN_1 = 0x0201,
    GPIO_PORT_2_PIN_2 = 0x0202,
    GPIO_PORT_2_PIN_3 = 0x0203,
    GPIO_PORT_2_PIN_4 = 0x0204,
    GPIO_PORT_2_PIN_5 = 0x0205,
    GPIO_PORT_2_PIN_6 = 0x0206,
    GPIO_PORT_2_PIN_7 = 0x0207,
    GPIO_PORT_3_PIN_0 = 0x0300,
    GPIO_PORT_3_PIN_1 = 0x0301,
    GPIO_PORT_3_PIN_2 = 0x0302,
    GPIO_PORT_3_PIN_3 = 0x0303,
    GPIO_PORT_3_PIN_4 = 0x0304,
    GPIO_PORT_3_PIN_5 = 0x0305,
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
    GPIO_PORT_5_PIN_0 = 0x0500,
    GPIO_PORT_5_PIN_1 = 0x0501,
    GPIO_PORT_5_PIN_2 = 0x0502,
    GPIO_PORT_5_PIN_3 = 0x0503,
    GPIO_PORT_5_PIN_4 = 0x0504,
    GPIO_PORT_5_PIN_5 = 0x0505,
    GPIO_PORT_5_PIN_6 = 0x0506,
    GPIO_PORT_6_PIN_0 = 0x0600,
    GPIO_PORT_6_PIN_1 = 0x0601,
    GPIO_PORT_6_PIN_2 = 0x0602,
    GPIO_PORT_6_PIN_3 = 0x0603,
    GPIO_PORT_6_PIN_4 = 0x0604,
    GPIO_PORT_6_PIN_5 = 0x0605,
    GPIO_PORT_6_PIN_6 = 0x0606,
    GPIO_PORT_6_PIN_7 = 0x0607,
    GPIO_PORT_7_PIN_0 = 0x0700,
    GPIO_PORT_7_PIN_1 = 0x0701,
    GPIO_PORT_7_PIN_2 = 0x0702,
    GPIO_PORT_7_PIN_3 = 0x0703,
    GPIO_PORT_7_PIN_4 = 0x0704,
    GPIO_PORT_7_PIN_5 = 0x0705,
    GPIO_PORT_7_PIN_6 = 0x0706,
    GPIO_PORT_7_PIN_7 = 0x0707,
    GPIO_PORT_8_PIN_0 = 0x0800,
    GPIO_PORT_8_PIN_1 = 0x0801,
    GPIO_PORT_8_PIN_2 = 0x0802,
    GPIO_PORT_8_PIN_3 = 0x0803,
    GPIO_PORT_8_PIN_6 = 0x0806,
    GPIO_PORT_8_PIN_7 = 0x0807,
    GPIO_PORT_9_PIN_0 = 0x0900,
    GPIO_PORT_9_PIN_1 = 0x0901,
    GPIO_PORT_9_PIN_2 = 0x0902,
    GPIO_PORT_9_PIN_3 = 0x0903,
    GPIO_PORT_A_PIN_0 = 0x0A00,
    GPIO_PORT_A_PIN_1 = 0x0A01,
    GPIO_PORT_A_PIN_2 = 0x0A02,
    GPIO_PORT_A_PIN_3 = 0x0A03,
    GPIO_PORT_A_PIN_4 = 0x0A04,
    GPIO_PORT_A_PIN_5 = 0x0A05,
    GPIO_PORT_A_PIN_6 = 0x0A06,
    GPIO_PORT_A_PIN_7 = 0x0A07,
    GPIO_PORT_B_PIN_0 = 0x0B00,
    GPIO_PORT_B_PIN_1 = 0x0B01,
    GPIO_PORT_B_PIN_2 = 0x0B02,
    GPIO_PORT_B_PIN_3 = 0x0B03,
    GPIO_PORT_B_PIN_4 = 0x0B04,
    GPIO_PORT_B_PIN_5 = 0x0B05,
    GPIO_PORT_B_PIN_6 = 0x0B06,
    GPIO_PORT_B_PIN_7 = 0x0B07,
    GPIO_PORT_C_PIN_0 = 0x0C00,
    GPIO_PORT_C_PIN_1 = 0x0C01,
    GPIO_PORT_C_PIN_2 = 0x0C02,
    GPIO_PORT_C_PIN_3 = 0x0C03,
    GPIO_PORT_C_PIN_4 = 0x0C04,
    GPIO_PORT_C_PIN_5 = 0x0C05,
    GPIO_PORT_C_PIN_6 = 0x0C06,
    GPIO_PORT_C_PIN_7 = 0x0C07,
    GPIO_PORT_D_PIN_0 = 0x0D00,
    GPIO_PORT_D_PIN_1 = 0x0D01,
    GPIO_PORT_D_PIN_2 = 0x0D02,
    GPIO_PORT_D_PIN_3 = 0x0D03,
    GPIO_PORT_D_PIN_4 = 0x0D04,
    GPIO_PORT_D_PIN_5 = 0x0D05,
    GPIO_PORT_D_PIN_6 = 0x0D06,
    GPIO_PORT_D_PIN_7 = 0x0D07,
    GPIO_PORT_E_PIN_0 = 0x0E00,
    GPIO_PORT_E_PIN_1 = 0x0E01,
    GPIO_PORT_E_PIN_2 = 0x0E02,
    GPIO_PORT_E_PIN_3 = 0x0E03,
    GPIO_PORT_E_PIN_4 = 0x0E04,
    GPIO_PORT_E_PIN_5 = 0x0E05,
    GPIO_PORT_E_PIN_6 = 0x0E06,
    GPIO_PORT_E_PIN_7 = 0x0E07,
    GPIO_PORT_F_PIN_5 = 0x0F05,
    GPIO_PORT_J_PIN_3 = 0x1203,
    GPIO_PORT_J_PIN_5 = 0x1205,
} gpio_port_pin_t;

#elif (BSP_PACKAGE_PINS == 100)
/* This enumerator has each available GPIO port on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_0 = 0x0000,
    GPIO_PORT_1 = 0x0100,
    GPIO_PORT_2 = 0x0200,
    GPIO_PORT_3 = 0x0300,
    GPIO_PORT_4 = 0x0400,
    GPIO_PORT_5 = 0x0500,
    GPIO_PORT_A = 0x0A00,
    GPIO_PORT_B = 0x0B00,
    GPIO_PORT_C = 0x0C00,
    GPIO_PORT_D = 0x0D00,
    GPIO_PORT_E = 0x0E00,
    GPIO_PORT_J = 0x1200,
} gpio_port_t;

/* This enumerator has a bit mask for each available GPIO pin for the given port on this MCU. */
typedef enum
{
    GPIO_PORT0_PIN_MASK = 0xA0,    /* Available pins: P05, P07   */
    GPIO_PORT1_PIN_MASK = 0xFC,    /* Available pins: P12 to P17 */
    GPIO_PORT2_PIN_MASK = 0xFF,    /* Available pins: P20 to P27 */
    GPIO_PORT3_PIN_MASK = 0xFF,    /* Available pins: P30 to P37 */
    GPIO_PORT4_PIN_MASK = 0xFF,    /* Available pins: P40 to P47 */
    GPIO_PORT5_PIN_MASK = 0x3F,    /* Available pins: P50 to P55 */
    GPIO_PORTA_PIN_MASK = 0xFF,    /* Available pins: PA0 to PA7 */
    GPIO_PORTB_PIN_MASK = 0xFF,    /* Available pins: PB0 to PB7 */
    GPIO_PORTC_PIN_MASK = 0xFF,    /* Available pins: PC0 to PC7 */
    GPIO_PORTD_PIN_MASK = 0xFF,    /* Available pins: PD0 to PD7 */
    GPIO_PORTE_PIN_MASK = 0xFF,    /* Available pins: PE0 to PE7 */
    GPIO_PORTJ_PIN_MASK = 0x08,    /* Available pins: PJ3        */
} gpio_pin_bit_mask_t;

typedef enum
{
    GPIO_PORT_0_PIN_5 = 0x0005,
    GPIO_PORT_0_PIN_7 = 0x0007,
    GPIO_PORT_1_PIN_2 = 0x0102,
    GPIO_PORT_1_PIN_3 = 0x0103,
    GPIO_PORT_1_PIN_4 = 0x0104,
    GPIO_PORT_1_PIN_5 = 0x0105,
    GPIO_PORT_1_PIN_6 = 0x0106,
    GPIO_PORT_1_PIN_7 = 0x0107,
    GPIO_PORT_2_PIN_0 = 0x0200,
    GPIO_PORT_2_PIN_1 = 0x0201,
    GPIO_PORT_2_PIN_2 = 0x0202,
    GPIO_PORT_2_PIN_3 = 0x0203,
    GPIO_PORT_2_PIN_4 = 0x0204,
    GPIO_PORT_2_PIN_5 = 0x0205,
    GPIO_PORT_2_PIN_6 = 0x0206,
    GPIO_PORT_2_PIN_7 = 0x0207,
    GPIO_PORT_3_PIN_0 = 0x0300,
    GPIO_PORT_3_PIN_1 = 0x0301,
    GPIO_PORT_3_PIN_2 = 0x0302,
    GPIO_PORT_3_PIN_3 = 0x0303,
    GPIO_PORT_3_PIN_4 = 0x0304,
    GPIO_PORT_3_PIN_5 = 0x0305,
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
    GPIO_PORT_5_PIN_0 = 0x0500,
    GPIO_PORT_5_PIN_1 = 0x0501,
    GPIO_PORT_5_PIN_2 = 0x0502,
    GPIO_PORT_5_PIN_3 = 0x0503,
    GPIO_PORT_5_PIN_4 = 0x0504,
    GPIO_PORT_5_PIN_5 = 0x0505,
    GPIO_PORT_A_PIN_0 = 0x0A00,
    GPIO_PORT_A_PIN_1 = 0x0A01,
    GPIO_PORT_A_PIN_2 = 0x0A02,
    GPIO_PORT_A_PIN_3 = 0x0A03,
    GPIO_PORT_A_PIN_4 = 0x0A04,
    GPIO_PORT_A_PIN_5 = 0x0A05,
    GPIO_PORT_A_PIN_6 = 0x0A06,
    GPIO_PORT_A_PIN_7 = 0x0A07,
    GPIO_PORT_B_PIN_0 = 0x0B00,
    GPIO_PORT_B_PIN_1 = 0x0B01,
    GPIO_PORT_B_PIN_2 = 0x0B02,
    GPIO_PORT_B_PIN_3 = 0x0B03,
    GPIO_PORT_B_PIN_4 = 0x0B04,
    GPIO_PORT_B_PIN_5 = 0x0B05,
    GPIO_PORT_B_PIN_6 = 0x0B06,
    GPIO_PORT_B_PIN_7 = 0x0B07,
    GPIO_PORT_C_PIN_0 = 0x0C00,
    GPIO_PORT_C_PIN_1 = 0x0C01,
    GPIO_PORT_C_PIN_2 = 0x0C02,
    GPIO_PORT_C_PIN_3 = 0x0C03,
    GPIO_PORT_C_PIN_4 = 0x0C04,
    GPIO_PORT_C_PIN_5 = 0x0C05,
    GPIO_PORT_C_PIN_6 = 0x0C06,
    GPIO_PORT_C_PIN_7 = 0x0C07,
    GPIO_PORT_D_PIN_0 = 0x0D00,
    GPIO_PORT_D_PIN_1 = 0x0D01,
    GPIO_PORT_D_PIN_2 = 0x0D02,
    GPIO_PORT_D_PIN_3 = 0x0D03,
    GPIO_PORT_D_PIN_4 = 0x0D04,
    GPIO_PORT_D_PIN_5 = 0x0D05,
    GPIO_PORT_D_PIN_6 = 0x0D06,
    GPIO_PORT_D_PIN_7 = 0x0D07,
    GPIO_PORT_E_PIN_0 = 0x0E00,
    GPIO_PORT_E_PIN_1 = 0x0E01,
    GPIO_PORT_E_PIN_2 = 0x0E02,
    GPIO_PORT_E_PIN_3 = 0x0E03,
    GPIO_PORT_E_PIN_4 = 0x0E04,
    GPIO_PORT_E_PIN_5 = 0x0E05,
    GPIO_PORT_E_PIN_6 = 0x0E06,
    GPIO_PORT_E_PIN_7 = 0x0E07,
    GPIO_PORT_J_PIN_3 = 0x1203,
} gpio_port_pin_t;
#endif


/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

#endif /* BSP_MCU_RX64M */
#endif /* GPIO_RX64M */
