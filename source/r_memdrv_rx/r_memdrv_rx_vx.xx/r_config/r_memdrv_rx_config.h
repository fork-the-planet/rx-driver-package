/***********************************************************************************************************************
* Copyright (c) 2018 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_memdrv_rx_config.h
* Version      : 1.31
* Description  : Memory driver configuration header file
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 15.12.2018 1.00    Initial Release
*              : 16.03.2023 1.05    Added support for RSCI and QSPIX Memory Mapped Mode.
*              : 15.03.2025 1.31    Updated disclaimer.
***********************************************************************************************************************/
#ifndef MEMDRV_CONFIG_H
#define MEMDRV_CONFIG_H

/************************************************************************************************
SPECIFY DEVICES TO INCLUDE SOFTWARE SUPPORT
*************************************************************************************************/
/* If these are defined, then the code for the specified device is valid.
   If the #define which device is not supported on the code is uncommented,
   then the compile error occurs. */
/* 0 : Not use Device No. */
/* 1 : Use Device No. */
#define MEMDRV_CFG_DEV0_INCLUDED  (1)             /* Device 0 Included                        */
#define MEMDRV_CFG_DEV1_INCLUDED  (0)             /* Device 1 Included                        */

/************************************************************************************************
DATA TRANSFER MODE
*************************************************************************************************/
/*  Please set one macro definition. */
/*      MEMDRV_TRNS_CPU   */
/*      MEMDRV_TRNS_DMAC  : RX DMACA FIT module   */
/*      MEMDRV_TRNS_DTC   : RX DTC FIT module     */
#define MEMDRV_CFG_DEV0_MODE_TRNS         (MEMDRV_TRNS_CPU)
#define MEMDRV_CFG_DEV1_MODE_TRNS         (MEMDRV_TRNS_CPU)

/************************************************************************************************
DEVICE DRIVER
*************************************************************************************************/
/*  Please set one macro definition. */
/*      MEMDRV_DRVR_RX_FIT_RSPI           : RX RSPI FIT module  */
/*      MEMDRV_DRVR_RX_FIT_QSPI_SMSTR     : RX QSPI Single Master FIT module  */
/*      MEMDRV_DRVR_RX_FIT_SCI_SPI        : RX SCI as SPI FIT module  */
/*      MEMDRV_DRVR_RX_FIT_QSPIX_IAM      : RX QSPIX FIT module(Indirect access mode)  */
/*      MEMDRV_DRVR_RX_FIT_QSPIX_MMM      : RX QSPIX FIT module(Memory mapped mode)  */
/*      MEMDRV_DRVR_RX_FIT_RSCI_SPI       : RX RSCI as SPI FIT module  */
#define MEMDRV_CFG_DEV0_MODE_DRVR         (MEMDRV_DRVR_RX_FIT_RSPI)
#define MEMDRV_CFG_DEV1_MODE_DRVR         (MEMDRV_DRVR_RX_FIT_RSPI)

/************************************************************************************************
DEVICE DRIVER CHANEL NUMBER
*************************************************************************************************/
/*  Please set one macro definition. */
/*      MEMDRV_DRVR_CH0 - MEMDRV_DRVR_CH15  */
#define MEMDRV_CFG_DEV0_MODE_DRVR_CH      (MEMDRV_DRVR_CH0)
#define MEMDRV_CFG_DEV1_MODE_DRVR_CH      (MEMDRV_DRVR_CH0)

/************************************************************************************************
DEVICE TYPE
*************************************************************************************************/
/*  Please set one macro definition. */
/* 0 : NOR FLASH or EEPROM. */
/* 1 : NAND FLASH. */
#define MEMDRV_CFG_DEV0_TYPE              (0)
#define MEMDRV_CFG_DEV1_TYPE              (0)
/************************************************************************************************
TRANSFER RATE
*************************************************************************************************/
/* Define the transfer rate for using MCU driver interface.
   Necessary to set command transmission, data transmission and data reception.
        e.g. (1) The transfer rate is RSPI Bit Rate Register (SPBR) for using RX RSPI driver.
        e.g. (2) The transfer rate is QSPI Bit Rate Register (SPBR) for using RX QSPI driver. */

#define MEMDRV_CFG_DEV0_BR                ((uint32_t)(1000000))
                                        /* Device 0 Transfer rate for command transmission.     */
#define MEMDRV_CFG_DEV0_BR_WRITE_DATA     ((uint32_t)(1000000))
                                        /* Device 0 Transfer rate for data transmission.        */
#define MEMDRV_CFG_DEV0_BR_READ_DATA      ((uint32_t)(1000000))
                                        /* Device 0 Transfer rate for data reception.           */

#define MEMDRV_CFG_DEV1_BR                ((uint32_t)(1000000))
                                        /* Device 1 Transfer rate for command transmission.     */
#define MEMDRV_CFG_DEV1_BR_WRITE_DATA     ((uint32_t)(1000000))
                                        /* Device 1 Transfer rate for data transmission.        */
#define MEMDRV_CFG_DEV1_BR_READ_DATA      ((uint32_t)(1000000))
                                        /* Device 1 Transfer rate for data reception.           */

/************************************************************************************************
DMAC ONLY : CHANNEL NUMBER OF FIT DMAC FOR RX
*************************************************************************************************/
/* Set channel No. of RX FIT DMAC driver for transmission and reception. */
#define MEMDRV_CFG_DEV0_DMAC_CH_NO_Tx     (0) /* Device 0 DMAC for transmission & reception   */
#define MEMDRV_CFG_DEV0_DMAC_CH_NO_Rx     (1) /* Device 0 DMAC for reception                  */
#define MEMDRV_CFG_DEV1_DMAC_CH_NO_Tx     (2) /* Device 1 DMAC for transmission & reception   */
#define MEMDRV_CFG_DEV1_DMAC_CH_NO_Rx     (3) /* Device 1 DMAC for reception                  */

/************************************************************************************************
DMAC ONLY : PRIORITY LEVEL OF FIT DMAC FOR RX
*************************************************************************************************/
/* Set interrupt priority level of RX FIT DMAC driver for transmission and reception. */
#define MEMDRV_CFG_DEV0_DMAC_INT_PRL_Tx   (10)
                            /* Device 0 Interrupt priority level for RX FIT DMAC transmission.  */
#define MEMDRV_CFG_DEV0_DMAC_INT_PRL_Rx   (10)
                            /* Device 0 Interrupt priority level for RX FIT DMAC reception.     */
#define MEMDRV_CFG_DEV1_DMAC_INT_PRL_Tx   (10)
                            /* Device 1 Interrupt priority level for RX FIT DMAC transmission.  */
#define MEMDRV_CFG_DEV1_DMAC_INT_PRL_Rx   (10)
                            /* Device 1 Interrupt priority level for RX FIT DMAC reception.     */

/************************************************************************************************
SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
*************************************************************************************************/
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting
   Setting to 1 includes parameter checking; 0 compiles out parameter checking */
#define MEMDRV_CFG_PARAM_CHECKING_ENABLE  (BSP_CFG_PARAM_CHECKING_ENABLE)

/************************************************************************************************
ENABLE DEBUGGING INFORMATION
*************************************************************************************************/
/* Define using Firmware Integration Technology (FIT) for RX family MCU,
   Stores error log information using LONGQ module of FIT. */
/* 0 : Not use LONGQ module of FIT. */
/* 1 : Use FIT LONGQ of FIT. Please obtain FIT LONGQ module separately. */
#define MEMDRV_CFG_LONGQ_ENABLE   (0)

#endif /* __MEMDRV_CONFIG_H__ */

/* End of File */
