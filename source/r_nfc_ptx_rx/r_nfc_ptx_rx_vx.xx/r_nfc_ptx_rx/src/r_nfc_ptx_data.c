/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_nfc_ptx_data.c
 * Description  : Data definitions for PTX NFC driver.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_nfc_ptx_data.h"
#include "r_cmt_rx_config.h"

/**********************************************************************************************************************
 Macro definitions
*********************************************************************************************************************/

/* SSPI Configuration */
#if (SCI_CFG_SSPI_INCLUDED == 1)
const sci_sync_sspi_t s_spi_cfg =
{
	.spi_mode = SCI_SPI_MODE_0,
	.bit_rate = NFC_CFG_SCI_SSPI_SPEED,
	.msb_first = NFC_SCI_SPI_MSB_FIRST,
	.invert_data = 0,
	.int_priority = (uint8_t)SCI_CFG_ERI_TEI_PRIORITY
};
const st_gpio_conf_t s_spi_ss_cfg =
{
    .pin = NFC_SCI_SPI_SS_PIN,
    .level = GPIO_LEVEL_LOW,
    .dir = GPIO_DIRECTION_OUTPUT
};
#endif

/* External IRQ Configuration */
irq_handle_t ptx_plat_irq_handle;

const st_irq_conf_t s_ext_irq_cfg =
{
    .pin        = NFC_EXT_IRQ_PIN,
    .irq_num    = NFC_IRQ_NUM,
    .trigger    = IRQ_TRIG_RISING,
    .priority   = IRQ_PRI_3,
    .handle     = &ptx_plat_irq_handle
};

/* Application Timer Configuration */
const st_timer_cfg_t s_app_timer_cfg =
{
    .channel = NFC_CFG_TDC_TIMER_CHANNEL,
    .priority = (cmt_priority_t)CMT_RX_CFG_IPR
};

/* Timer Configuration */
const st_timer_cfg_t s_timer_cfg =
{
    .channel = NFC_CFG_SLEEP_TIMER_CHANNEL,
    .priority = (cmt_priority_t)CMT_RX_CFG_IPR
};
