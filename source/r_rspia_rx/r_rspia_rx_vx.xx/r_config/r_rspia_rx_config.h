/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name     : r_rspia_rx_config.c
* Description   : Configures the RSPIA drivers
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 31.03.2021 1.00     First Release
*                               Supported for RX671.
*         : 30.06.2023 1.40     Supported for RX26T-256K.
*         : 15.12.2023 1.50     Changed the default value of TX/RX FIFO Threshold.
*         : 31.12.2024 1.60     Supported for Nested interrupt.
*         : 15.03.2025 1.61     Updated disclaimer.
***********************************************************************************************************************/
#ifndef RSPIA_CONFIG_HEADER_FILE
#define RSPIA_CONFIG_HEADER_FILE

#if ((BSP_MCU_RX26T == 1) && ((BSP_CFG_MCU_PART_MEMORY_SIZE == 0x8) || (BSP_CFG_MCU_PART_MEMORY_SIZE == 0xA)))
#error  "Error - RX26T Product with 48 Kbytes RAM not support RSPIA Module!"
#endif

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/
/* Checking of arguments passed to RSPIA API functions can be enable or disabled.
 * Disabling argument checking is provided for systems that absolutely require faster and smaller code.
 * By default the module is configured to use the setting of the system-wide BSP_CFG_PARAM_CHECKING_ENABLE macro.
 * This can be overridden for the local module by redefining RSPIA_CFG_PARAM_CHECKING_ENABLE.
 * To control parameter checking locally, set RSPIA_CFG_PARAM_CHECKING_ENABLE to 1 to enable it,
 * otherwise set to 0 skip checking.
 */
#define RSPIA_CFG_PARAM_CHECKING_ENABLE  (BSP_CFG_PARAM_CHECKING_ENABLE)

#define RSPIA_CFG_REQUIRE_LOCK (1)

/* Fixed data that is transmitted during receive-only operations. Change as needed. */
#define RSPIA_CFG_DUMMY_TX_DATA (0xFFFFFFFF)

/* Enable the RSPIA channels to use in this build. (0) = not used. (1) = used. */
#define RSPIA_CFG_USE_CH0  (1)

/* Set interrupt priority levels for each channel present.
 * Priority is shared by all interrupt sources in a channel.
 * Values must be in the range 0 (interrupt disabled) to 15 (highest)*/
#define RSPIA_CFG_CH0_IR_PRIORITY (3)

/* SET TX FIFO THRESHOLD; (RSPIA supported MCU ONLY) 0 lowest, 3 highest */
/* Set the same value for TX FIFO THRESHOLD and RX FIFO THRESHOLD. */
#define RSPIA_CFG_CH0_TX_FIFO_THRESH (1)

/* SET RX FIFO THRESHOLD; (RSPIA supported MCU ONLY) 0 lowest, 3 highest */
#define RSPIA_CFG_CH0_RX_FIFO_THRESH (1)

/* Specifies whether to include code for nested interrupt SPTI in channel 0 */
#define RSPIA_CFG_CH0_SPTI_EN_NESTED_INT (0)

/* Specifies whether to include code for nested interrupt SPRI in channel 0 */
#define RSPIA_CFG_CH0_SPRI_EN_NESTED_INT (0)

/* Specifies whether to include code for nested interrupt SPEI in channel 0 */
#define RSPIA_CFG_CH0_SPEI_EN_NESTED_INT (0)

/**********************************************************************************************************************/
#endif /* RSPIA_CONFIG_HEADER_FILE */
