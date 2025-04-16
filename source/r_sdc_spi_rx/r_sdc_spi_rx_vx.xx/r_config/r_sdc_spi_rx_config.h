/* Generated configuration header file - do not edit */
/**********************************************************************************************************************
* Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_sdc_spi_rx_config.h
 * Version      : 1.11
 * Description  : Configures the SPI mode SDC card driver.
  *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 28.12.2023 1.00     First Release
 *         : 20.03.2025 1.11     Changed the disclaimer in program sources.
 *********************************************************************************************************************/
#ifndef SDC_SPI_CONFIG_H
#define SDC_SPI_CONFIG_H

#define SDC_SPI_CFG_CH0_CD_ENABLE           (1)     /* CH0 CD pin use select */
#define SDC_SPI_CFG_CH0_CD_PORT             (0x00)  /* CH0 CD pin port number */
#define SDC_SPI_CFG_CH0_CD_BIT              (0)     /* CH0 CD pin port bit number */
#define SDC_SPI_CFG_CH0_CS_ENABLE           (1)     /* CH0 CS pin use select */
#define SDC_SPI_CFG_CH0_CS_PORT             (0x00)  /* CH0 CS pin port number */
#define SDC_SPI_CFG_CH0_CS_BIT              (0)     /* CH0 CS pin port bit number */
#define SDC_SPI_CFG_CH0_WP_ENABLE           (1)     /* CH0 WP pin use select */
#define SDC_SPI_CFG_CH0_WP_PORT             (0x00)  /* CH0 WP pin port number */
#define SDC_SPI_CFG_CH0_WP_BIT              (0)     /* CH0 WP pin port bit number */
#define SDC_SPI_CFG_CH1_CD_ENABLE           (1)     /* CH1 CD pin use select */
#define SDC_SPI_CFG_CH1_CD_PORT             (0x00)  /* CH1 CD pin port number */
#define SDC_SPI_CFG_CH1_CD_BIT              (0)     /* CH1 CD pin port bit number */
#define SDC_SPI_CFG_CH1_CS_ENABLE           (1)     /* CH1 CS pin use select */
#define SDC_SPI_CFG_CH1_CS_PORT             (0x00)  /* CH1 CS pin port bit number */
#define SDC_SPI_CFG_CH1_CS_BIT              (0)     /* CH1 CS pin port bit number */
#define SDC_SPI_CFG_CH1_WP_ENABLE           (1)     /* CH1 WP pin use select */
#define SDC_SPI_CFG_CH1_WP_PORT             (0x00)  /* CH1 WP pin port number */
#define SDC_SPI_CFG_CH1_WP_BIT              (0)     /* CH1 WP pin port bit number */
#define SDC_SPI_CFG_ERROR_LOG_ACQUISITION   (0)     /* Use Error log get select */
#define SDC_SPI_CFG_PARAM_CHECKING_ENABLE   (BSP_CFG_PARAM_CHECKING_ENABLE)
#define SDC_SPI_CFG_SBLK_NUM                (1)     /* Number of blocks accessed as single block */
#define SDC_SPI_CFG_USE_SC_CRC              (0)     /* Use CRC smart configration */
#endif /* SDC_SPI_CONFIG_H */
