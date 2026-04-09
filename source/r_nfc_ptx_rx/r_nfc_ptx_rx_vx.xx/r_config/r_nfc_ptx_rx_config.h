/* Generated configuration header file - do not edit */
/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_nfc_ptx_rx_config.h
 * Description  : PTX NFC driver Configuration.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef R_NFC_PTX_RX_CONFIG_H_
#define R_NFC_PTX_RX_CONFIG_H_

/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking; 0 compiles out parameter checking */
#define NFC_CFG_PARAM_CHECKING_ENABLED	BSP_CFG_PARAM_CHECKING_ENABLE


/* External interrupt pin for NFC communication */
#define NFC_CFG_EXT_IRQ_PORT	                D
#define NFC_CFG_EXT_IRQ_PIN		                5

/* IRQ source according to external interrupt pin */
#define NFC_CFG_IRQ_NUM                         5

/* SCI Channel for NFC communication
   Set this option to match the SCI port to be controlled.
 */
#define NFC_CFG_SCI_CHANNEL                      (5)

/* Config SS pin for SCI SSPI */
#define NFC_CFG_SCI_SSPI_SS_PORT	             C
#define NFC_CFG_SCI_SSPI_SS_PIN	                 0

/* SCI host mode for NFC communication */
#define NFC_CFG_SCI_MODE                         0
/* SCI modes
    0: Simple SPI
*/

/* Config SCI SSPI bitrate */
#define NFC_CFG_SCI_SSPI_SPEED                 (1000000)

/* Data transfer mode:
    0: LSB first transfer.
    1: MSB first transfer.
*/
#define NFC_SCI_SPI_MSB_FIRST                   1


/* Config timer channel */
#define NFC_CFG_SLEEP_TIMER_CHANNEL             (0)

#define NFC_CFG_TDC_TIMER_CHANNEL               (1)

/* Add-ons configuration */
#define NFC_CFG_NDEF_SUPPORT                    (1)

#define NFC_CFG_NATIVE_TAG_SUPPORT              (1)


#if (NFC_CFG_NDEF_SUPPORT == 1)
#define NFC_CFG_NDEF_WORK_BUF_SIZE              (256)
#else
#define NFC_CFG_NDEF_WORK_BUF_SIZE              (1)
#endif

/* Configure discovery mode
    Polling modes
    0: Regular Polling (default)
    1: Low-power Card Detection (LPCD)
    2 - 255: LPCD with every n-th cycle as Regular Polling
*/

#define NFC_CFG_DISCOVER_MODE                    (0)


/* NFC polling type of tags selection */

#define NFC_CFG_POLL_TYPE_A                      (1)

#define NFC_CFG_POLL_TYPE_B                      (1)

#define NFC_CFG_POLL_TYPE_F                      (1)

#define NFC_CFG_POLL_TYPE_V                      (1)

/* Thermal shutdown threshold value */

#define NFC_CFG_TEMP_SENSOR_SHUTDOWN             (100)

/* Ambient temperature at which temperature sensor calibration takes place */

#define NFC_CFG_TEMP_SENSOR_AMBIENT              (25)

/* Max number of tags to discover */

#define NFC_CFG_DEVICE_LIMIT                     (5) // Max number of tags to discover

/* Idle time between polling cycle */

#define NFC_CFG_IDLE_TIME_MS                     (100) // Idle time between polling cycles in milliseconds


#endif /* R_NFC_PTX_RX_CONFIG_H_ */
