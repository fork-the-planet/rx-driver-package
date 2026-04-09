/*
* Copyright (c) 2018 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_ctsu_qe_config.h
 * Description  : Configures the QE CTSU API module.
 ***********************************************************************************************************************/
#ifndef CTSU_CONFIG_HEADER_FILE
#define CTSU_CONFIG_HEADER_FILE


/***********************************************************************************************************************
 Configuration Options
 ***********************************************************************************************************************/
/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
 * Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting
 * Setting to 1 includes parameter checking; 0 compiles out parameter checking
 */
#define CTSU_CFG_PARAM_CHECKING_ENABLE      (BSP_CFG_PARAM_CHECKING_ENABLE)

/* Data transfer of INTCTSUWR and INTCTSURD. To use DTC, set this to 1. */
#define CTSU_CFG_DTC_SUPPORT_ENABLE         (0)

/* Overall automatic judgement setting. To use, set this to 1. */
#define CTSU_CFG_AUTO_JUDGE_ENABLE          (0)

/* Interrupt priority level */
#define CTSU_CFG_INTCTSUWR_PRIORITY_LEVEL   (2)
#define CTSU_CFG_INTCTSURD_PRIORITY_LEVEL   (2)
#define CTSU_CFG_INTCTSUFN_PRIORITY_LEVEL   (2)

/* The following configurations are set according to the touch interface configuration,
 * so they are not set in Smart Configurator.
 * Set when using QE for Capacitive Touch. In that case, QE_TOUCH_CONFIGURATION is defined in the project,
 * the definition in r_ctsu_config.h is invalid, and instead it is defined in qe_touch_define.h.
 */

#ifndef QE_TOUCH_CONFIGURATION
 #if(TOUCH_CFG_SERIAL_TUNING_SUPPORT == 1)
 #define CTSU_CFG_NUM_SELF_ELEMENTS                   (35)
 #define CTSU_CFG_NUM_MUTUAL_ELEMENTS                 (255)
 #else
 #define CTSU_CFG_NUM_SELF_ELEMENTS                   (1)
 #define CTSU_CFG_NUM_MUTUAL_ELEMENTS                 (0)
 #endif
 #if (CTSU_CFG_AUTO_JUDGE_ENABLE == 1)
 #define CTSU_CFG_MAJORITY_MODE                       (2)
 #define CTSU_CFG_NUM_AUTOJUDGE_SELF_ELEMENTS         (1)
 #define CTSU_CFG_NUM_AUTOJUDGE_MUTUAL_ELEMENTS       (0)
 #define CTSU_CFG_AUTO_CORRECTION_ENABLE              (1)
 #else
 #define CTSU_CFG_MAJORITY_MODE                       (1)
 #define CTSU_CFG_NUM_AUTOJUDGE_SELF_ELEMENTS         (0)
 #define CTSU_CFG_NUM_AUTOJUDGE_MUTUAL_ELEMENTS       (0)
 #define CTSU_CFG_AUTO_CORRECTION_ENABLE              (0)
 #endif
#define CTSU_CFG_AUTO_MULTI_CLOCK_CORRECTION_ENABLE   (0)
#define CTSU_CFG_MULTIPLE_ELECTRODE_CONNECTION_ENABLE (0)
#define CTSU_CFG_LOW_VOLTAGE_MODE                     (0)
#define CTSU_CFG_PCLK_DIVISION                        (0)
#define CTSU_CFG_TSCAP_PORT                           (0xFFFF)
#define CTSU_CFG_VCC_MV                               (5000)
#define CTSU_CFG_DIAG_SUPPORT_ENABLE                  (0)
 #if defined(BSP_MCU_RX140) || defined(BSP_MCU_RX261) || defined(BSP_MCU_RX260)
  #if(TOUCH_CFG_SERIAL_TUNING_SUPPORT == 1)
  #define CTSU_CFG_NUM_SUMULTI                        (1)
  #else
  #define CTSU_CFG_NUM_SUMULTI                        (3)
  #endif
  #if defined(BSP_MCU_RX260) || defined(BSP_MCU_RX261)
  #define CTSU_CFG_SUMULTI0                         (0x2F)
  #define CTSU_CFG_SUMULTI1                         (0x28)
  #define CTSU_CFG_SUMULTI2                         (0x36)
  #else
  #define CTSU_CFG_SUMULTI0                         (0x3F)
  #define CTSU_CFG_SUMULTI1                         (0x36)
  #define CTSU_CFG_SUMULTI2                         (0x48)
  #endif
 #define CTSU_CFG_TEMP_CORRECTION_SUPPORT          (0)
 #define CTSU_CFG_TEMP_CORRECTION_TS               (0)
 #define CTSU_CFG_TEMP_CORRECTION_TIME             (0)
 #define CTSU_CFG_CALIB_RTRIM_SUPPORT              (0)
 #else
 #define CTSU_CFG_NUM_SUMULTI                      (1)
 #define CTSU_CFG_DIAG_DAC_TS                      (0)
 #endif
#endif

#endif /* TOUCH_CONFIG_HEADER_FILE */
