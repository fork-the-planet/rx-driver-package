/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : mcu_info.h
* Device(s)    : RX71M
* Description  : Information about the MCU.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 26.09.2014 1.00     First Release
*         : 15.05.2017 1.10     Changed the name of the following macro definition, because there was a mistake
*                               in the name of macro definition.
*                               - BSP_PACKAGE_LFQFP176 - Changed package type from LQFP to LFQFP.
*                               - BSP_PACKAGE_LFQFP144 - Changed package type from LQFP to LFQFP.
*                               - BSP_PACKAGE_LFQFP100 - Changed package type from LQFP to LFQFP.
*                               Changed the value of the following macro definition.
*                               - BSP_CFG_MCU_PART_PACKAGE - Changed the value from 0x6 to 0xA.
*         : 28.02.2019 2.00     Added macro definition of MCU functions.
*                               Added the following macro definition.
*                               - BSP_MCU_CPU_VERSION
*                               - CPU_CYCLES_PER_LOOP
*                               - BSP_MCU_MEMWAIT_FREQ_THRESHOLD
*                               Fixed coding style.
*                               Added the error check of BSP_CFG_CLOCK_SOURCE.
*                               Added the following enumeration constant.
*                               - BSP_MCU_GROUP_INTERRUPT_BE0
*         : 30.11.2021 2.01     Deleted the compile switch for BSP_CFG_MCU_PART_SERIES and BSP_CFG_MCU_PART_GROUP.
*         : 22.04.2022 2.02     Added version check of smart configurator.
*         : 27.11.2024 2.03     Added version check of smart configurator.
*         : 26.02.2025 2.04     Changed the disclaimer.
*                               Fixed comment about BSP_CFG_CONFIGURATOR_VERSION.
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

#if BSP_CFG_CONFIGURATOR_VERSION < 2120
    /* The following macros are updated to invalid value by Smart configurator if you are using Smart Configurator for 
       RX V2.11.0 (equivalent to e2 studio 2021-10) or earlier version.
       - BSP_CFG_MCU_PART_GROUP, BSP_CFG_MCU_PART_SERIES
       The following macros are not updated by Smart configurator if you are using Smart Configurator for RX V2.11.0 
       (equivalent to e2 studio 2021-10) or earlier version.
       - BSP_CFG_MAIN_CLOCK_OSCILLATE_ENABLE, BSP_CFG_SUB_CLOCK_OSCILLATE_ENABLE, BSP_CFG_HOCO_OSCILLATE_ENABLE, 
         BSP_CFG_LOCO_OSCILLATE_ENABLE, BSP_CFG_IWDT_CLOCK_OSCILLATE_ENABLE, BSP_CFG_CPLUSPLUS
       Please update Smart configurator to Smart Configurator for RX V2.12.0 (equivalent to e2 studio 2022-01) or 
       later version.
     */
    #error "To use this version of BSP, you need to upgrade Smart configurator. Please upgrade Smart configurator. If you don't use Smart Configurator, please change value of BSP_CFG_CONFIGURATOR_VERSION in r_bsp_config.h."
#endif

#if BSP_CFG_CONFIGURATOR_VERSION < 2240
    /* If you are using a version earlier than Smart Configurator for RX V2.23.0 (equivalent to e2 studio 2024-10), 
       the program may enter an infinite loop in the initial settings depending on the conditions used. For details, 
       see the related Tool News (R20TS1052).
       Please update Smart configurator to Smart Configurator for RX V2.24.0 (equivalent to e2 studio 2025-01) or 
       later version.
     */
    #error "To use this version of BSP, you need to upgrade Smart configurator. Please upgrade Smart configurator. If you don't use Smart Configurator, please change value of BSP_CFG_CONFIGURATOR_VERSION in r_bsp_config.h."
#endif

/* MCU CPU Version */
#define BSP_MCU_CPU_VERSION    (2)

/* CPU cycles. Known number of RXv2 CPU cycles required to execute the delay_wait() loop */
#define CPU_CYCLES_PER_LOOP    (4)

/* MCU Series. */
#define BSP_MCU_SERIES_RX700   (1)

/* This macro means that this MCU is part of the RX64x collection of MCUs (i.e. RX64M). */
#define BSP_MCU_RX71_ALL       (1)

/* MCU Group name. */
#define BSP_MCU_RX71M          (1)

/* Package. */
#if   BSP_CFG_MCU_PART_PACKAGE == 0x0
    #define BSP_PACKAGE_LFQFP176    (1)
    #define BSP_PACKAGE_PINS        (176)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x1
    #define BSP_PACKAGE_LFBGA176    (1)
    #define BSP_PACKAGE_PINS        (176)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x2
    #define BSP_PACKAGE_TFLGA177    (1)
    #define BSP_PACKAGE_PINS        (177)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x3
    #define BSP_PACKAGE_LFQFP144    (1)
    #define BSP_PACKAGE_PINS        (144)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x4
    #define BSP_PACKAGE_TFLGA145    (1)
    #define BSP_PACKAGE_PINS        (145)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x5
    #define BSP_PACKAGE_LFQFP100    (1)
    #define BSP_PACKAGE_PINS        (100)
#elif BSP_CFG_MCU_PART_PACKAGE == 0xA
    #define BSP_PACKAGE_TFLGA100    (1)
    #define BSP_PACKAGE_PINS        (100)
#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

/* Memory size of your MCU. */
#if   BSP_CFG_MCU_PART_MEMORY_SIZE == 0xF
    #define BSP_ROM_SIZE_BYTES              (2097152)
    #define BSP_RAM_SIZE_BYTES              (524288)
    #define BSP_DATA_FLASH_SIZE_BYTES       (65536)
#elif BSP_CFG_MCU_PART_MEMORY_SIZE == 0x10
    #define BSP_ROM_SIZE_BYTES              (2621440)
    #define BSP_RAM_SIZE_BYTES              (524288)
    #define BSP_DATA_FLASH_SIZE_BYTES       (65536)
#elif BSP_CFG_MCU_PART_MEMORY_SIZE == 0x13
    #define BSP_ROM_SIZE_BYTES              (3145728)
    #define BSP_RAM_SIZE_BYTES              (524288)
    #define BSP_DATA_FLASH_SIZE_BYTES       (65536)
#elif BSP_CFG_MCU_PART_MEMORY_SIZE == 0x15
    #define BSP_ROM_SIZE_BYTES              (4194304)
    #define BSP_RAM_SIZE_BYTES              (524288)
    #define BSP_DATA_FLASH_SIZE_BYTES       (65536)
#else
    #error "ERROR - BSP_CFG_MCU_PART_MEMORY_SIZE - Unknown memory size chosen in r_bsp_config.h"
#endif

/* These macros define clock speeds for fixed speed clocks. */
#define BSP_LOCO_HZ                         (240000)
#define BSP_SUB_CLOCK_HZ                    (32768)

/* Define frequency of HOCO. */
#if   BSP_CFG_HOCO_FREQUENCY == 0
    #define BSP_HOCO_HZ                     (16000000)
#elif BSP_CFG_HOCO_FREQUENCY == 1
    #define BSP_HOCO_HZ                     (18000000)
#elif BSP_CFG_HOCO_FREQUENCY == 2
    #define BSP_HOCO_HZ                     (20000000)
#else
    #error "ERROR - Invalid HOCO frequency chosen in r_bsp_config.h! Set valid value for BSP_CFG_HOCO_FREQUENCY."
#endif

/* Clock source select (CKSEL).
   0 = Low Speed On-Chip Oscillator  (LOCO)
   1 = High Speed On-Chip Oscillator (HOCO)
   2 = Main Clock Oscillator
   3 = Sub-Clock Oscillator
   4 = PLL Circuit
*/ 
#if   BSP_CFG_CLOCK_SOURCE == 0
    #define BSP_SELECTED_CLOCK_HZ       (BSP_LOCO_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 1
    #define BSP_SELECTED_CLOCK_HZ       (BSP_HOCO_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 2
    #define BSP_SELECTED_CLOCK_HZ       (BSP_CFG_XTAL_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 3
    #define BSP_SELECTED_CLOCK_HZ       (BSP_SUB_CLOCK_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 4
    #if   BSP_CFG_PLL_SRC == 0
        #define BSP_SELECTED_CLOCK_HZ   ((BSP_CFG_XTAL_HZ/BSP_CFG_PLL_DIV) * BSP_CFG_PLL_MUL)
    #elif BSP_CFG_PLL_SRC == 1
        #define BSP_SELECTED_CLOCK_HZ   ((BSP_HOCO_HZ/BSP_CFG_PLL_DIV) * BSP_CFG_PLL_MUL)
    #else
        #error "ERROR - Valid PLL clock source must be chosen in r_bsp_config.h using BSP_CFG_PLL_SRC macro."
    #endif
#else
    #error "ERROR - BSP_CFG_CLOCK_SOURCE - Unknown clock source chosen in r_bsp_config.h"
#endif

/* System clock speed in Hz. */
#define BSP_ICLK_HZ                 (BSP_SELECTED_CLOCK_HZ / BSP_CFG_ICK_DIV)
/* Peripheral Module Clock A speed in Hz. Used for ETHERC and EDMAC. */
#define BSP_PCLKA_HZ                (BSP_SELECTED_CLOCK_HZ / BSP_CFG_PCKA_DIV)
/* Peripheral Module Clock B speed in Hz. */
#define BSP_PCLKB_HZ                (BSP_SELECTED_CLOCK_HZ / BSP_CFG_PCKB_DIV)
/* Peripheral Module Clock C speed in Hz. */
#define BSP_PCLKC_HZ                (BSP_SELECTED_CLOCK_HZ / BSP_CFG_PCKC_DIV)
/* Peripheral Module Clock D speed in Hz. */
#define BSP_PCLKD_HZ                (BSP_SELECTED_CLOCK_HZ / BSP_CFG_PCKD_DIV)
/* External bus clock speed in Hz. */
#define BSP_BCLK_HZ                 (BSP_SELECTED_CLOCK_HZ / BSP_CFG_BCK_DIV)
/* FlashIF clock speed in Hz. */
#define BSP_FCLK_HZ                 (BSP_SELECTED_CLOCK_HZ / BSP_CFG_FCK_DIV)
/* USB clock speed in Hz. */
#define BSP_UCLK_HZ                 (BSP_SELECTED_CLOCK_HZ / BSP_CFG_UCK_DIV)

/* Null argument definitions. */
#define FIT_NO_FUNC                 ((void (*)(void *))0x10000000)  /* Reserved space on RX */
#define FIT_NO_PTR                  ((void *)0x10000000)            /* Reserved space on RX */

/* Mininum and maximum IPL levels available for this MCU. */
#define BSP_MCU_IPL_MAX             (0xF)
#define BSP_MCU_IPL_MIN             (0)

/* Frequency threshold of Memory wait cycle setting. */
#define BSP_MCU_MEMWAIT_FREQ_THRESHOLD (120000000)        /* ICLK > 120MHz requires MEMWAIT register update */

/* MCU functions */
#define BSP_MCU_REGISTER_WRITE_PROTECTION
#define BSP_MCU_RCPC_PRC0
#define BSP_MCU_RCPC_PRC1
#define BSP_MCU_RCPC_PRC3
#define BSP_MCU_FLOATING_POINT
#define BSP_MCU_EXCEPTION_TABLE
#define BSP_MCU_GROUP_INTERRUPT
#define BSP_MCU_GROUP_INTERRUPT_BE0
#define BSP_MCU_GROUP_INTERRUPT_BL0
#define BSP_MCU_GROUP_INTERRUPT_BL1
#define BSP_MCU_GROUP_INTERRUPT_AL0
#define BSP_MCU_GROUP_INTERRUPT_AL1
#define BSP_MCU_SOFTWARE_CONFIGURABLE_INTERRUPT
#define BSP_MCU_EXCEP_SUPERVISOR_INST_ISR
#define BSP_MCU_EXCEP_ACCESS_ISR
#define BSP_MCU_EXCEP_UNDEFINED_INST_ISR
#define BSP_MCU_EXCEP_FLOATING_POINT_ISR
#define BSP_MCU_NON_MASKABLE_ISR
#define BSP_MCU_UNDEFINED_INTERRUPT_SOURCE_ISR
#define BSP_MCU_BUS_ERROR_ISR

#define BSP_MCU_NMI_EXC_NMI_PIN
#define BSP_MCU_NMI_OSC_STOP_DETECT
#define BSP_MCU_NMI_WDT_ERROR
#define BSP_MCU_NMI_IWDT_ERROR
#define BSP_MCU_NMI_LVD1
#define BSP_MCU_NMI_LVD2
#define BSP_MCU_NMI_ECCRAM

#endif /* MCU_INFO */

