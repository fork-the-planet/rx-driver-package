/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : mcu_info.h
* Device(s)    : RX72T
* Description  : Information about the MCU.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version   Description
*         : 31.10.2018 1.00      First Release
*         : 28.02.2019 2.00      Added macro definition of MCU functions.
*                                Added the following macro definition.
*                                - CPU_CYCLES_PER_LOOP
*                                - BSP_MCU_MEMWAIT_FREQ_THRESHOLD
*                                - BSP_MCU_TRIGONOMETRIC
*                                Fixed coding style.
*                                Added the following enumeration constant.
*                                - BSP_MCU_GROUP_INTERRUPT_BE0
*         : 30.11.2021 2.01      Deleted the compile switch for BSP_CFG_MCU_PART_SERIES and BSP_CFG_MCU_PART_GROUP.
*         : 22.04.2022 2.02      Added version check of smart configurator.
*                                Added the following macro definitions.
*                                - BSP_MCU_VOLTAGE_LEVEL_SETTING_USB
*                                - BSP_MCU_VOLTAGE_LEVEL_SETTING_AD
*                                - BSP_MCU_VOLTAGE_LEVEL_SETTING_RIIC
*         : 28.02.2023 2.03      Added the following macro definitions.
*                                - BSP_MCU_TFU_VERSION
*         : 26.02.2025 2.04      Changed the disclaimer.
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
       - BSP_CFG_MAIN_CLOCK_OSCILLATE_ENABLE, BSP_CFG_HOCO_OSCILLATE_ENABLE, BSP_CFG_LOCO_OSCILLATE_ENABLE, 
         BSP_CFG_IWDT_CLOCK_OSCILLATE_ENABLE, BSP_CFG_CPLUSPLUS
       Please update Smart configurator to Smart Configurator for RX V2.14.0 (equivalent to e2 studio 2022-07) or 
       later version.
     */
    #error "To use this version of BSP, you need to upgrade Smart configurator. Please upgrade Smart configurator. If you don't use Smart Configurator, please change value of BSP_CFG_CONFIGURATOR_VERSION in r_bsp_config.h."
#endif

/* MCU CPU Version */
#define BSP_MCU_CPU_VERSION    (3)

/* CPU cycles. Known number of RXv3 CPU cycles required to execute the delay_wait() loop */
#define CPU_CYCLES_PER_LOOP    (3)

/* MCU Series. */
#define BSP_MCU_SERIES_RX700   (1)

/* This macro means that this MCU is part of the RX72x collection of MCUs (i.e. RX72T). */
#define BSP_MCU_RX72_ALL       (1)

/* MCU Group name. */
#define BSP_MCU_RX72T          (1)

/* Package. */
#if   BSP_CFG_MCU_PART_PACKAGE == 0x3
    #define BSP_PACKAGE_LFQFP144    (1)
    #define BSP_PACKAGE_PINS        (144)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x5
    #define BSP_PACKAGE_LFQFP100    (1)
    #define BSP_PACKAGE_PINS        (100)
#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

/* Memory size of your MCU. */
#if   BSP_CFG_MCU_PART_MEMORY_SIZE == 0x14
    #define BSP_ROM_SIZE_BYTES              (1048576)
    #define BSP_RAM_SIZE_BYTES              (131072)
    #define BSP_DATA_FLASH_SIZE_BYTES       (32768)
#elif BSP_CFG_MCU_PART_MEMORY_SIZE == 0xF
    #define BSP_ROM_SIZE_BYTES              (524288)
    #define BSP_RAM_SIZE_BYTES              (131072)
    #define BSP_DATA_FLASH_SIZE_BYTES       (32768)
#else
    #error "ERROR - BSP_CFG_MCU_PART_MEMORY_SIZE - Unknown memory size chosen in r_bsp_config.h"
#endif

/* Function. */
#if BSP_PACKAGE_PINS == 144
    #if (BSP_CFG_MCU_PART_FUNCTION == 0xC) || (BSP_CFG_MCU_PART_FUNCTION == 0x10)
    #else
        #error "ERROR - BSP_CFG_MCU_PART_FUNCTION - Invalid function code chosen in r_bsp_config.h"
    #endif
#endif /* BSP_PACKAGE_PINS == 144 */

/* These macros define clock speeds for fixed speed clocks. */
#define BSP_LOCO_HZ                         (240000)

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
   4 = PLL Circuit
*/ 
#if   BSP_CFG_CLOCK_SOURCE == 0
    #define BSP_SELECTED_CLOCK_HZ       (BSP_LOCO_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 1
    #define BSP_SELECTED_CLOCK_HZ       (BSP_HOCO_HZ)
#elif BSP_CFG_CLOCK_SOURCE == 2
    #define BSP_SELECTED_CLOCK_HZ       (BSP_CFG_XTAL_HZ)
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

/* MCU TFU Version */
#define BSP_MCU_TFU_VERSION    (1)

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
#define BSP_MCU_SOFTWARE_CONFIGURABLE_INTERRUPT
#define BSP_MCU_VOLTAGE_LEVEL_SETTING
#define BSP_MCU_VOLTAGE_LEVEL_SETTING_USB
#define BSP_MCU_VOLTAGE_LEVEL_SETTING_AD
#define BSP_MCU_VOLTAGE_LEVEL_SETTING_RIIC
#define BSP_MCU_EXCEP_SUPERVISOR_INST_ISR
#define BSP_MCU_EXCEP_ACCESS_ISR
#define BSP_MCU_EXCEP_UNDEFINED_INST_ISR
#define BSP_MCU_EXCEP_FLOATING_POINT_ISR
#define BSP_MCU_NON_MASKABLE_ISR
#define BSP_MCU_UNDEFINED_INTERRUPT_SOURCE_ISR
#define BSP_MCU_BUS_ERROR_ISR
#define BSP_MCU_TRIGONOMETRIC

#define BSP_MCU_NMI_EXC_NMI_PIN
#define BSP_MCU_NMI_OSC_STOP_DETECT
#define BSP_MCU_NMI_WDT_ERROR
#define BSP_MCU_NMI_IWDT_ERROR
#define BSP_MCU_NMI_LVD1
#define BSP_MCU_NMI_LVD2
#define BSP_MCU_NMI_RAM
#define BSP_MCU_NMI_RAM_ECCRAM

#endif /* MCU_INFO */

