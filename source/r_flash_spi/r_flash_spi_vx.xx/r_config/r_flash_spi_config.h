/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_flash_spi_config.h
* Version      : 3.51
* Description  : FLASH SPI driver configuration header file
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 23.07.2014 2.21    Created
*              : 29.05.2015 2.32    Revised functions of same as Ver.2.32 of EEPROM SPI FIT module.
*              : 21.12.2018 3.00    Change flash drive interface to Memory Access Driver Interface
*              : 30.06.2022 3.10    Added macros to specify the ports used for SS#.
*              : 16.03.2023 3.20    Added support for AT25QF641B-SHB.
*              : 15.11.2023 3.40    Added support for MX25U6432F.
*              : 15.03.2025 3.51    Updated disclaimer.
***********************************************************************************************************************/
#ifndef __FLASH_SPI_CONFIG_H__
#define __FLASH_SPI_CONFIG_H__

/*===============================================================================================
(1) Common setting
================================================================================================*/
/************************************************************************************************
ENABLE CHECKING OF THE WEL BIT.
*************************************************************************************************/
/* Define the check of WEL bit after WREN command issue. */
/* 0 : Not check WEL bit. */
/* 1 : Check WEL bit. */
#define FLASH_SPI_CFG_WEL_CHK   (1)

/************************************************************************************************
ENABLE DEBUGGING INFORMATION
*************************************************************************************************/
/* Define using Firmware Integration Technology (FIT) for RX family MCU,
   Stores error log information using LONGQ module of FIT. */
/* 0 : Not use LONGQ module of FIT. */
/* 1 : Use FIT LONGQ of FIT. Please obtain FIT LONGQ module separately. */
#define FLASH_SPI_CFG_LONGQ_ENABLE  (0)

/************************************************************************************************
ENABLE GPIO MODULE AND MPC MODULE OF FIT FOR RX FAMILY MCU
*************************************************************************************************/
/* When perform terminal setting with GPIO and MPC module of FIT, please validate the definition. */
/* 0 : Not use GPIO  module and MPC  module of FIT. */
/* 1 : Use GPIO  module and MPC  module of FIT. */
#define FLASH_SPI_CFG_USE_GPIO_MPC_FIT  (0)


/*===============================================================================================
(2) Setting of depending on Device No.
================================================================================================*/
/************************************************************************************************
SPECIFY DEVICES TO INCLUDE SOFTWARE SUPPORT
*************************************************************************************************/
/* If these are defined, then the code for the specified device is valid.
   If the #define which device is not supported on the code is uncommented,
   then the compile error occurs. */
/* 0 : Not use Device No. */
/* 1 : Use Device No. */
#define FLASH_SPI_CFG_DEV0_INCLUDED     (1)         /* Device 0 Included                        */
#define FLASH_SPI_CFG_DEV1_INCLUDED     (0)         /* Device 1 Included                        */


/************************************************************************************************
 SELECT THE FLASHM MEMORY TYPE
*************************************************************************************************/
/* Setting to 1 configures the flash memory such that code is included.
   Please set 1 for one device No. */
/* 0 : Not use the flash memory. */
/* 1 : Use the flash memory. */
#define FLASH_SPI_CFG_DEV0_MX25L    (1)             /* Device 0 Macronix MX25L                  */
#define FLASH_SPI_CFG_DEV0_MX66L    (0)             /* Device 0 Macronix MX66L                  */
#define FLASH_SPI_CFG_DEV0_MX25R    (0)             /* Device 0 Macronix MX25R                  */
#define FLASH_SPI_CFG_DEV0_AT25QF   (0)             /* Device 0 Adesto AT25Q                    */
#define FLASH_SPI_CFG_DEV0_MX25U    (0)             /* Device 0 Macronix MX25U                  */

#define FLASH_SPI_CFG_DEV1_MX25L    (0)             /* Device 1 Macronix MX25L                  */
#define FLASH_SPI_CFG_DEV1_MX66L    (0)             /* Device 1 Macronix MX66L                  */
#define FLASH_SPI_CFG_DEV1_MX25R    (0)             /* Device 1 Macronix MX25R                  */
#define FLASH_SPI_CFG_DEV1_AT25QF   (0)             /* Device 1 Adesto AT25Q                    */
#define FLASH_SPI_CFG_DEV1_MX25U    (0)             /* Device 1 Macronix MX25U                  */

/************************************************************************************************
 SELECT THE FLASH MEMORY SIZE
*************************************************************************************************/
/* Setting to 1 configures the flash memory size.  Please set the one definition. */
/* 0 : Not use the flash memory. */
/* 1 : Use the flash memory. */
#define FLASH_SPI_CFG_DEV0_SIZE_512K      (0)       /* Device 0 512K-bit    (64K Bytes)         */
#define FLASH_SPI_CFG_DEV0_SIZE_1M        (0)       /* Device 0 1M-bit      (128K Bytes)        */
#define FLASH_SPI_CFG_DEV0_SIZE_2M        (0)       /* Device 0 2M-bit      (256K Bytes)        */
#define FLASH_SPI_CFG_DEV0_SIZE_4M        (0)       /* Device 0 4M-bit      (512K Bytes)        */
#define FLASH_SPI_CFG_DEV0_SIZE_16M       (0)       /* Device 0 16M-bit     (2M Bytes)          */
#define FLASH_SPI_CFG_DEV0_SIZE_32M       (0)       /* Device 0 32M-bit     (4M Bytes)          */
#define FLASH_SPI_CFG_DEV0_SIZE_64M       (1)       /* Device 0 64M-bit     (8M Bytes)          */
#define FLASH_SPI_CFG_DEV0_SIZE_128M      (0)       /* Device 0 128M-bit    (16M Bytes)         */
#define FLASH_SPI_CFG_DEV0_SIZE_256M      (0)       /* Device 0 256M-bit    (32M Bytes)         */
#define FLASH_SPI_CFG_DEV0_SIZE_512M      (0)       /* Device 0 512M-bit    (64M Bytes)         */
#define FLASH_SPI_CFG_DEV0_SIZE_1G        (0)       /* Device 0 1G-bit      (16M Bytes)         */

#define FLASH_SPI_CFG_DEV1_SIZE_512K      (0)       /* Device 1 512K-bit    (64K Bytes)         */
#define FLASH_SPI_CFG_DEV1_SIZE_1M        (0)       /* Device 1 1M-bit      (128K Bytes)        */
#define FLASH_SPI_CFG_DEV1_SIZE_2M        (0)       /* Device 1 2M-bit      (256K Bytes)        */
#define FLASH_SPI_CFG_DEV1_SIZE_4M        (0)       /* Device 1 4M-bit      (512K Bytes)        */
#define FLASH_SPI_CFG_DEV1_SIZE_16M       (0)       /* Device 1 16M-bit     (2M Bytes)          */
#define FLASH_SPI_CFG_DEV1_SIZE_32M       (0)       /* Device 1 32M-bit     (4M Bytes)          */
#define FLASH_SPI_CFG_DEV1_SIZE_64M       (0)       /* Device 1 64M-bit     (8M Bytes)          */
#define FLASH_SPI_CFG_DEV1_SIZE_128M      (0)       /* Device 1 128M-bit    (16M Bytes)         */
#define FLASH_SPI_CFG_DEV1_SIZE_256M      (0)       /* Device 1 256M-bit    (32M Bytes)         */
#define FLASH_SPI_CFG_DEV1_SIZE_512M      (0)       /* Device 1 512M-bit    (64M Bytes)         */
#define FLASH_SPI_CFG_DEV1_SIZE_1G        (0)       /* Device 1 1G-bit      (16M Bytes)         */

/************************************************************************************************
PIN ASSIGNMENT
*************************************************************************************************/
/* The macros to specify the ports used for SS#. 
   Default value 'X' is for reference only, If this default value is kept, then the code
   support for device port will be temporarily disabled until user assigns a value of port
   used for SS# according to a device. */
#define FLASH_SPI_CS_DEV0_CFG_PORTNO    ('X')         /* Device 0 Port Number : FLASH SS#    */
#define FLASH_SPI_CS_DEV0_CFG_BITNO     ('0')         /* Device 0 Bit Number  : FLASH SS#    */
#define FLASH_SPI_CS_DEV1_CFG_PORTNO    ('X')         /* Device 1 Port Number : FLASH SS#    */
#define FLASH_SPI_CS_DEV1_CFG_BITNO     ('0')         /* Device 1 Bit Number  : FLASH SS#    */
/************************************************************************************************
Includes <System Includes> , "Project Includes"
*************************************************************************************************/

#if (FLASH_SPI_CFG_LONGQ_ENABLE == 1)
#include "r_longq_if.h"
#endif

#if (FLASH_SPI_CFG_USE_GPIO_MPC_FIT == 1)
#include "r_gpio_rx_if.h"
#include "r_mpc_rx_if.h"
#endif



#endif /* __FLASH_SPI_CONFIG_H__ */

/* End of File */
