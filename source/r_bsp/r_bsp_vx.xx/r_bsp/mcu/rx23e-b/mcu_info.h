/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : mcu_info.h
* Device(s)    : RX23E-B
* Description  : Information about the MCU.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 10.03.2023 1.00     First Release
*         : 26.02.2025 1.01     Changed the disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Gets MCU configuration information. */
#include "r_bsp_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Multiple inclusion prevention macro */
#ifndef MCU_INFO
#define MCU_INFO

/* MCU CPU Version */
#define BSP_MCU_CPU_VERSION    (2)

/* CPU cycles. Known number of RXv2 CPU cycles required to execute the delay_wait() loop */
#define CPU_CYCLES_PER_LOOP    (4)

/* MCU Series. */
#define BSP_MCU_SERIES_RX200   (1)

/* This macro means that this MCU is part of the RX23x collection of MCUs (i.e. RX23E-B). */
#define BSP_MCU_RX23_ALL       (1)

/* MCU Group name. */
#define BSP_MCU_RX23E_B        (1)

/* Package. */
#if   BSP_CFG_MCU_PART_PACKAGE == 0x0
    #define BSP_PACKAGE_LFQFP100    (1)
    #define BSP_PACKAGE_PINS        (100)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x1
    #define BSP_PACKAGE_TFBGA100    (1)
    #define BSP_PACKAGE_PINS        (100)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x2
    #define BSP_PACKAGE_LFQFP64     (1)
    #define BSP_PACKAGE_PINS        (64)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x6
    #define BSP_PACKAGE_LFQFP48     (1)
    #define BSP_PACKAGE_PINS        (48)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x7
    #define BSP_PACKAGE_LFQFP80     (1)
    #define BSP_PACKAGE_PINS        (80)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x8
    #define BSP_PACKAGE_HWQFN40     (1)
    #define BSP_PACKAGE_PINS        (40)
#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

/* Memory size of your MCU. */
#if   BSP_CFG_MCU_PART_MEMORY_SIZE == 0x5
    #define BSP_ROM_SIZE_BYTES              (131072)
    #define BSP_RAM_SIZE_BYTES              (32768)
    #define BSP_DATA_FLASH_SIZE_BYTES       (8192)
#elif BSP_CFG_MCU_PART_MEMORY_SIZE == 0x6
    #define BSP_ROM_SIZE_BYTES              (262144)
    #define BSP_RAM_SIZE_BYTES              (32768)
    #define BSP_DATA_FLASH_SIZE_BYTES       (8192)
#else
    #error "ERROR - BSP_CFG_MCU_PART_MEMORY_SIZE - Unknown memory size chosen in r_bsp_config.h"
#endif

/* These macros define clock speeds for fixed speed clocks. */
#define BSP_LOCO_HZ                 (4000000)
#define BSP_SUB_CLOCK_HZ            (32768)
#define BSP_ILOCO_HZ                (15000)
#define BSP_HOCO_HZ                 (32000000)

/* Clock source select (CKSEL).
   0 = Low Speed On-Chip Oscillator  (LOCO)
   1 = High Speed On-Chip Oscillator (HOCO)
   2 = Main Clock Oscillator
   3 = Sub-Clock Oscillator
   4 = PLL Circuit
*/ 
#if   BSP_CFG_CLOCK_SOURCE == 0
    #define BSP_SELECTED_CLOCK_HZ   (BSP_LOCO_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 1
    #define BSP_SELECTED_CLOCK_HZ   (BSP_HOCO_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 2
    #define BSP_SELECTED_CLOCK_HZ   (BSP_CFG_XTAL_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 3
    #define BSP_SELECTED_CLOCK_HZ   (BSP_SUB_CLOCK_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 4
    #define BSP_SELECTED_CLOCK_HZ   ((BSP_CFG_XTAL_HZ/BSP_CFG_PLL_DIV) * BSP_CFG_PLL_MUL)
#else
    #error "ERROR - BSP_CFG_CLOCK_SOURCE - Unknown clock source chosen in r_bsp_config.h"
#endif

/* SSI clock speed in Hz */
#define BSP_SSISCK_HZ               (BSP_CFG_XTAL_HZ)

/* LCD clock speed in Hz */
#if   BSP_CFG_LCD_CLOCK_SOURCE == 0
    #define BSP_LCDSRCCLK_HZ        (BSP_LOCO_HZ)
#elif BSP_CFG_LCD_CLOCK_SOURCE == 1
    #define BSP_LCDSRCCLK_HZ        (BSP_HOCO_HZ)
#elif BSP_CFG_LCD_CLOCK_SOURCE == 2
    #define BSP_LCDSRCCLK_HZ        (BSP_CFG_XTAL_HZ)
#elif BSP_CFG_LCD_CLOCK_SOURCE == 3
    #define BSP_LCDSRCCLK_HZ        (BSP_SUB_CLOCK_HZ)
#elif BSP_CFG_LCD_CLOCK_SOURCE == 4
    #define BSP_LCDSRCCLK_HZ        (15000)                                     /* IWDTCLK frequency */
#endif

/* LPT clock speed in Hz */
#if   BSP_CFG_LPT_CLOCK_SOURCE == 0
    #define BSP_LPTSRCCLK_HZ        (BSP_SUB_CLOCK_HZ)
#elif BSP_CFG_LPT_CLOCK_SOURCE == 1
    #define BSP_LPTSRCCLK_HZ        (BSP_ILOCO_HZ)                              /* IWDTCLK typical frequency */
#elif BSP_CFG_LPT_CLOCK_SOURCE == 2
    /* LPT none used */
#else
    #error "ERROR - BSP_CFG_LPT_CLOCK_SOURCE - Unknown lpt clock source chosen in r_bsp_config.h"
#endif

/* CAN clock speed in Hz */
#define BSP_CANCLK_HZ               (BSP_CFG_XTAL_HZ)

/* System clock speed in Hz. */
#define BSP_ICLK_HZ                 (BSP_SELECTED_CLOCK_HZ / BSP_CFG_ICK_DIV)
/* Peripheral Module Clock A speed in Hz. */
#define BSP_PCLKA_HZ                (BSP_SELECTED_CLOCK_HZ / BSP_CFG_PCKA_DIV)
/* Peripheral Module Clock B speed in Hz. */
#define BSP_PCLKB_HZ                (BSP_SELECTED_CLOCK_HZ / BSP_CFG_PCKB_DIV)
/* Peripheral Module Clock C speed in Hz. */
#define BSP_PCLKC_HZ                (BSP_SELECTED_CLOCK_HZ / BSP_CFG_PCKC_DIV)
/* Peripheral Module Clock D speed in Hz. */
#define BSP_PCLKD_HZ                (BSP_SELECTED_CLOCK_HZ / BSP_CFG_PCKD_DIV)
/* FlashIF clock speed in Hz. */
#define BSP_FCLK_HZ                 (BSP_SELECTED_CLOCK_HZ / BSP_CFG_FCK_DIV)

/* Null argument definitions. */
#define FIT_NO_FUNC                 ((void (*)(void *))0x10000000)  /* Reserved space on RX */
#define FIT_NO_PTR                  ((void *)0x10000000)            /* Reserved space on RX */

/* Mininum and maximum IPL levels available for this MCU. */
#define BSP_MCU_IPL_MAX             (0xF)
#define BSP_MCU_IPL_MIN             (0)

/* Maximum frequency on Middle-speed operating mode. */
#define BSP_MIDDLE_SPEED_MAX_FREQUENCY      (12000000)

/* MCU functions */
#define BSP_MCU_REGISTER_WRITE_PROTECTION
#define BSP_MCU_RCPC_PRC0
#define BSP_MCU_RCPC_PRC1
#define BSP_MCU_RCPC_PRC2
#define BSP_MCU_RCPC_PRC3
#define BSP_MCU_FLOATING_POINT
#define BSP_MCU_EXCEPTION_TABLE
#define BSP_MCU_EXCEP_SUPERVISOR_INST_ISR
#define BSP_MCU_EXCEP_ACCESS_ISR
#define BSP_MCU_EXCEP_UNDEFINED_INST_ISR
#define BSP_MCU_EXCEP_FLOATING_POINT_ISR
#define BSP_MCU_NON_MASKABLE_ISR
#define BSP_MCU_UNDEFINED_INTERRUPT_SOURCE_ISR
#define BSP_MCU_BUS_ERROR_ISR

#define BSP_MCU_NMI_EXC_NMI_PIN
#define BSP_MCU_NMI_OSC_STOP_DETECT
#define BSP_MCU_NMI_IWDT_ERROR
#define BSP_MCU_NMI_LVD1
#define BSP_MCU_NMI_LVD2

#endif /* MCU_INFO */

