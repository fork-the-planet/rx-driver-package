/***********************************************************************************************************************
* Copyright (c) 2019 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_lvd_rx72t.h
* Description  : When a target product is selected, as for this header, it is done include.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 01.02.2019 1.00     First Release
*              : 12.12.2022 1.10     Update default register value of voltage level
*              : 30.01.2024 1.20     Changed LVD circuit enable wait value
*                                    Changed ICU group from LVD_GROUP_INT_ICUB to LVD_GROUP_INT_ICUC
*              : 15.03.2025 4.81     Updated disclaimer.
***********************************************************************************************************************/
#ifndef LVD_RX72T_HEADER_FILE
#define LVD_RX72T_HEADER_FILE

/***********************************************************************************************************************
Includes <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Used for configuring the LVD module */
#include "r_lvd_rx_config.h"

/* Private header file for this package. */
#include "r_lvd_rx_private.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* Group: LVD setup group */
#define LVD_GROUP_SETUP                         (LVD_GROUP_SETUP_LVDA_2)

/* Group: ICU group */
#define LVD_GROUP_INT                           (LVD_GROUP_INT_ICUC)

/* Support: Maskable interrupt */
#define LVD_SUPPORT_MI_CH1                      (LVD_ENABLE)
#define LVD_SUPPORT_MI_CH2                      (LVD_ENABLE)

/* Support: None-maskable interrupt */
#define LVD_SUPPORT_NMI_CH1                     (LVD_ENABLE)
#define LVD_SUPPORT_NMI_CH2                     (LVD_ENABLE)

/* Support: CMPA pin */
#define LVD_SUPPORT_CMPA_CH1                    (LVD_DISABLE)
#define LVD_SUPPORT_CMPA_CH2                    (LVD_DISABLE)

/* Support: Digital filter */
#define LVD_SUPPORT_DFILTER_CH1                 (LVD_ENABLE)
#define LVD_SUPPORT_DFILTER_CH2                 (LVD_ENABLE)

/* Value: Max priority of maskable interrupt */
#define LVD_MAX_MI_PRIO                         (15)

/* Default value: Default register value of voltage level */
#define LVD_VOLTAGE_LEVEL_DEFAULT_VALUE_CH1     (6)
#define LVD_VOLTAGE_LEVEL_DEFAULT_VALUE_CH2     (6)

/* Convert: Voltage level: Setting value -> register value */
#if (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_1 == 457)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH1         (4)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_1 == 447)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH1         (5)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_1 == 432)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH1         (6)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_1 == 293)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH1         (10)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_1 == 288)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH1         (11)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_1 == LVD_DEFAULT_VALUE)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH1         (LVD_VOLTAGE_LEVEL_DEFAULT_VALUE_CH1)
#else
    #define LVD_VOLTAGE_LEVEL_VALUE_CH1         (LVD_INVALID_VALUE)
#endif

#if (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_2 == 457)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH2         (4)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_2 == 447)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH2         (5)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_2 == 432)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH2         (6)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_2 == 293)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH2         (10)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_2 == 288)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH2         (11)
#elif (LVD_CFG_VOLTAGE_LEVEL_CHANNEL_2 == LVD_DEFAULT_VALUE)
    #define LVD_VOLTAGE_LEVEL_VALUE_CH2         (LVD_VOLTAGE_LEVEL_DEFAULT_VALUE_CH2)
#else
    #define LVD_VOLTAGE_LEVEL_VALUE_CH2         (LVD_INVALID_VALUE)
#endif


/* Default value: Default setting value of the sampling clock */
#define LVD_DFILTER_DIV_DEFAULT_CH1             (2)
#define LVD_DFILTER_DIV_DEFAULT_CH2             (2)

/* Default value: Default register value of the sampling clock */
#define LVD_DFILTER_DIV_DEFAULT_VALUE_CH1       (0)
#define LVD_DFILTER_DIV_DEFAULT_VALUE_CH2       (0)

/* Convert: Sampling clock: Setting value -> register value */
#if (LVD_CFG_SAMPLING_CLOCK_CHANNEL_1 == 2)
    #define LVD_DFILTER_DIV_VALUE_CH1           (0)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_1 == 4)
    #define LVD_DFILTER_DIV_VALUE_CH1           (1)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_1 == 8)
    #define LVD_DFILTER_DIV_VALUE_CH1           (2)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_1 == 16)
    #define LVD_DFILTER_DIV_VALUE_CH1           (3)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_1 == LVD_DEFAULT_VALUE)
    #define LVD_DFILTER_DIV_VALUE_CH1           (LVD_DFILTER_DIV_DEFAULT_VALUE_CH1)
#else
    #define LVD_DFILTER_DIV_VALUE_CH1           (LVD_INVALID_VALUE)
#endif

#if (LVD_CFG_SAMPLING_CLOCK_CHANNEL_2 == 2)
    #define LVD_DFILTER_DIV_VALUE_CH2           (0)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_2 == 4)
    #define LVD_DFILTER_DIV_VALUE_CH2           (1)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_2 == 8)
    #define LVD_DFILTER_DIV_VALUE_CH2           (2)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_2 == 16)
    #define LVD_DFILTER_DIV_VALUE_CH2           (3)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_2 == LVD_DEFAULT_VALUE)
    #define LVD_DFILTER_DIV_VALUE_CH2           (LVD_DFILTER_DIV_DEFAULT_VALUE_CH2)
#else
    #define LVD_DFILTER_DIV_VALUE_CH2           (LVD_INVALID_VALUE)
#endif

/* Value: Wait for enable digital filter. (LOCO cycle) */
#if (LVD_DFILTER_DIV_VALUE_CH1 == LVD_INVALID_VALUE)
    #define LVD_DELAY_DFILTER_ENABLE_LOCO_CH1   (0)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_1 == LVD_DEFAULT_VALUE)
    #define LVD_DELAY_DFILTER_ENABLE_LOCO_CH1   ((2 * LVD_DFILTER_DIV_DEFAULT_CH1) + 3)
#else
    #define LVD_DELAY_DFILTER_ENABLE_LOCO_CH1   ((2 * LVD_CFG_SAMPLING_CLOCK_CHANNEL_1) + 3)
#endif

#if (LVD_DFILTER_DIV_VALUE_CH2 == LVD_INVALID_VALUE)
    #define LVD_DELAY_DFILTER_ENABLE_LOCO_CH2   (0)
#elif (LVD_CFG_SAMPLING_CLOCK_CHANNEL_2 == LVD_DEFAULT_VALUE)
    #define LVD_DELAY_DFILTER_ENABLE_LOCO_CH2   ((2 * LVD_DFILTER_DIV_DEFAULT_CH2) + 3)
#else
    #define LVD_DELAY_DFILTER_ENABLE_LOCO_CH2   ((2 * LVD_CFG_SAMPLING_CLOCK_CHANNEL_2) + 3)
#endif


/* Value: Wait for enable LVD circuit. (micro sec) */
#define LVD_DELAY_CIRCUIT_ENABLE_USEC           (20)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/


#endif/* LVD_RX72T_HEADER_FILE */

/* End of File */

