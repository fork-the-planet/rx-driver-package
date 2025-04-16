/***********************************************************************************************************************
* Copyright (c) 2013 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_rtc_rx_config.h
* Description  : Configures the Real Time Clock (RTC) package for RX MCUs.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           09.09.2013 1.00    First release.
*           16.04.2014 2.00    Updated for new API.
*           03.09.2014 2.10    Added support for RX64M
*           03.12.2014 2.20    Added support for RX113
*           26.01.2015 2.30    Added support for RX71M
*           06.07.2015 2.40    Added support for RX231
*           01.03.2016 2.41    Added support for RX130
*                              Added support for RX230
*                              Added the option of RTC_CFG_DRIVE_CAPACITY_MD for sub-clock drive capacity.
*           01.10.2016 2.50    Added support for RX65N
*           31.07.2017 2.70    Added support for RX65N-2MB and RX130-512KB.
*                              Removed support for RX210 and RX63N/631.
*           20.09.2017 2.71    Fixed issue that an incorrect time is read out when a carry of the RTC counter occurs
*                              while reading the current time.
*                              Fixed issue that count stop occurred at warm start.
*                              - There is no change in this file.
*           30.07.2019 2.77    Added support for RX72M.
*           22.11.2019 2.78    Added support for RX66N.
*                              Added support for RX72N.
*           30.06.2021 2.81    Added support for RX671.
*           31.07.2021 2.82    Added support for RX140.
*           31.12.2021 2.83    Added support for RX660.
*           28.06.2024 3.00    Added support for RX260, RX261.
*           15.03.2025 3.01    Updated disclaimer.
***********************************************************************************************************************/

#ifndef R_RTC_RX_CONFIG_H
#define R_RTC_RX_CONFIG_H

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
 * Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting
 * Setting to 1 includes parameter checking; 0 compiles out parameter checking
 */
#define RTC_CFG_PARAM_CHECKING_ENABLE   (BSP_CFG_PARAM_CHECKING_ENABLE)


/* SPECIFY IF WANT TO CALCULATE DAY OF YEAR FOR R_RTC_Read(); 1-yes, 0=no (compiles out code) */
#define RTC_CFG_CALCULATE_YDAY          (0)


/* SPECIFY SUB-CLOCK OSCILLATOR DRIVE CAPACITY ON RX11x, RX130, RX23x, RX64M or RX71M, RX65N, RX671, RX72M, RX66N, RX72N 
 * uncomment appropriate level: standard, low, middle, or high
 * Devices with invalid settings: RX140, RX660, RX260, RX261
 */

/* Supported by the RX11x, RX130, RX23x, RX64M or RX71M, RX65N, RX671, RX72M, RX66N, RX72N */
#define RTC_CFG_DRIVE_CAPACITY_STD

/* Supported by the RX11x, RX130, RX23x, RX64M or RX71M, RX65N, RX671, RX72M, RX66N, RX72N */
//#define RTC_CFG_DRIVE_CAPACITY_LO

/* Supported by the RX11x only */
//#define RTC_CFG_DRIVE_CAPACITY_MD
//#define RTC_CFG_DRIVE_CAPACITY_HI


#endif /* R_RTC_RX_CONFIG_H */
