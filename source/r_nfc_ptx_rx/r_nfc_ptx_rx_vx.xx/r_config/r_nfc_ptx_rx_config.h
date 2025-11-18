/* Generated configuration header file - do not edit */
/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2025 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
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
#define NFC_CFG_IRQ_NUM                     5

/* SCI Channel for NFC communication
   Set this option to match the SCI port to be controlled.
 */
#define NFC_CFG_SCI_CHANNEL				    (5)

/* Config SS pin for SCI SSPI */
#define NFC_CFG_SCI_SSPI_SS_PORT	        C
#define NFC_CFG_SCI_SSPI_SS_PIN	            0

/* SCI host mode for NFC communication */
#define NFC_CFG_SCI_MODE                    0
/* SCI modes
    0: Simple SPI
*/

/* Config SCI SSPI bitrate */
#define NFC_CFG_SCI_SSPI_SPEED              (1000000)

/* Data transfer mode:
    0: LSB first transfer.
    1: MSB first transfer.
*/
#define NFC_SCI_SPI_MSB_FIRST               1


/* Config timer channel */
#define NFC_CFG_SLEEP_TIMER_CHANNEL             (0)

#define NFC_CFG_TDC_TIMER_CHANNEL               (1)

/* NFC polling type of tags selection */

#define NFC_CFG_POLL_TYPE_A         (1)

#define NFC_CFG_POLL_TYPE_B         (1)

#define NFC_CFG_POLL_TYPE_F         (1)

#define NFC_CFG_POLL_TYPE_V         (1)

/* Thermal shutdown threshold value */

#define NFC_CFG_TEMP_SENSOR_SHUTDOWN       (100)

/* Ambient temperature at which temperature sensor calibration takes place */

#define NFC_CFG_TEMP_SENSOR_AMBIENT        (25)

/* Max number of tags to discover */

#define NFC_CFG_DEVICE_LIMIT               (5) // Max number of tags to discover

/* Idle time between polling cycle */

#define NFC_CFG_IDLE_TIME_MS               (100) // Idle time between polling cycles in milliseconds


#endif /* R_NFC_PTX_RX_CONFIG_H_ */
