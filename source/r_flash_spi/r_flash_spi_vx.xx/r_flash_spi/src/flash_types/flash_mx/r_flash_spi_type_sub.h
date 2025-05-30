/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_flash_spi_type_sub.h
* Version      : 3.51
* Description  : FLASH SPI driver memory type header file
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 23.07.2014 2.21    Created
*              : 29.05.2015 2.32    Revised functions of same as Ver.2.32 of EEPROM SPI FIT module.
*              : 31.12.2021 3.03    Added variable "read_after_write" "read_after_write_add" and
*                                   "read_after_write_data" for controlling SPI bus.
*              : 16.03.2023 3.20    Added support for QSPIX Memory Mapped Mode.
*              : 15.11.2023 3.40    Added support for MX25U6432F.
*                                   Added features Advanced sector protection supporting for MX66L1G45 and MX25U6432F.
*              : 15.03.2025 3.51    Updated disclaimer.
***********************************************************************************************************************/
#ifndef FLASH_SPI_TYPE_SUB_H
#define FLASH_SPI_TYPE_SUB_H


/************************************************************************************************
Includes <System Includes> , "Project Includes"
*************************************************************************************************/


/************************************************************************************************
Macro definitions
*************************************************************************************************/
/*-------- Definitions of Command size ---------*/
#define FLASH_SPI_MX_CMD_SIZE           (uint8_t)(1)    /* Command size(Byte)                       */
#define FLASH_SPI_MX_STSREG_SIZE        (uint32_t)(1)   /* Status register size(Byte)               */
#define FLASH_SPI_MX_SCURREG_SIZE       (uint32_t)(1)   /* Security register size (bytes)           */
#define FLASH_SPI_MX_LKREG_SIZE         (uint32_t)(2)   /* Lock register size (2 bytes)             */
#define FLASH_SPI_MX_SPBLKREG_SIZE      (uint32_t)(1)   /* SPB lock register size (1 byte)          */
#define FLASH_SPI_MX_SPBREG_SIZE        (uint32_t)(1)   /* SPB register size (1 byte)               */
#if   (FLASH_SPI_CFG_DEV0_MX25L == 1) || (FLASH_SPI_CFG_DEV0_MX66L == 1) || (FLASH_SPI_CFG_DEV0_MX25U == 1) || \
      (FLASH_SPI_CFG_DEV1_MX25L == 1) || (FLASH_SPI_CFG_DEV1_MX66L == 1) || (FLASH_SPI_CFG_DEV1_MX25U == 1)
#define FLASH_SPI_MX_CFGREG_SIZE        (uint32_t)(1)   /* Configuration register size (1 byte)     */
#define FLASH_SPI_MX_WSTSREG_SIZE       (uint32_t)(2)   /* Status register size (bytes) for Write   */
#elif (FLASH_SPI_CFG_DEV0_MX25R == 1) || (FLASH_SPI_CFG_DEV1_MX25R == 1)
#define FLASH_SPI_MX_CFGREG_SIZE        (uint32_t)(2)   /* Configuration register size (2 bytes)    */
#define FLASH_SPI_MX_WSTSREG_SIZE       (uint32_t)(3)   /* Status register size (bytes) for Write   */
#endif
#define FLASH_SPI_MX_IDDATA_SIZE        (uint32_t)(3)   /* ID data size (bytes)                     */
#define TRUE                            (bool)(true)    /* not close SPI bus cycle                  */
#define FALSE                           (bool)(false)   /* close SPI bus cycle                      */

/*-------- Definitions of device information ---------*/
/* ==== FLASH device 0 ==== */
#if (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_32M == 1)
#define FLASH_SPI_MX_DEV0_MEM_SIZE      (uint32_t)(4194304)     /* 4MByte (32Mbit)                      */
#define FLASH_SPI_MX_DEV0_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV0_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV0_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV0_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV0_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV0_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV0_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV0_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV0_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_32M == 1) */

#if (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_64M == 1)
#define FLASH_SPI_MX_DEV0_MEM_SIZE      (uint32_t)(8388608)     /* 8MByte (64Mbit)                      */
#define FLASH_SPI_MX_DEV0_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV0_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV0_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV0_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV0_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV0_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV0_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV0_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV0_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_64M == 1) */

#if (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_128M == 1)
#define FLASH_SPI_MX_DEV0_MEM_SIZE      (uint32_t)(16777216)    /* 16MByte (128Mbit)                    */
#define FLASH_SPI_MX_DEV0_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV0_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV0_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV0_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV0_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV0_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV0_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV0_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV0_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_128M == 1) */

#if (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_256M == 1)
#define FLASH_SPI_MX_DEV0_MEM_SIZE      (uint32_t)(33554432)    /* 32MByte (256Mbit)                    */
#define FLASH_SPI_MX_DEV0_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV0_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV0_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV0_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV0_ADDR_SIZE     FLASH_SPI_ADDR_4BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV0_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV0_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV0_ADDR_MODE     FLASH_SPI_MODE_4BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV0_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_256M == 1) */

#if (FLASH_SPI_CFG_DEV0_MX66L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_512M == 1)
#define FLASH_SPI_MX_DEV0_MEM_SIZE      (uint32_t)(67108864)    /* 64MByte (512Mbit)                    */
#define FLASH_SPI_MX_DEV0_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV0_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV0_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV0_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV0_ADDR_SIZE     FLASH_SPI_ADDR_4BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV0_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV0_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV0_ADDR_MODE     FLASH_SPI_MODE_4BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV0_TYPE             FLASH_SPI_TYPE_MX66L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV0_MX66L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_512M == 1) */

#if (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_512M == 1)
#define FLASH_SPI_MX_DEV0_MEM_SIZE      (uint32_t)(67108864)    /* 64MByte (512Mbit)                    */
#define FLASH_SPI_MX_DEV0_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV0_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV0_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV0_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV0_ADDR_SIZE     FLASH_SPI_ADDR_4BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV0_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV0_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV0_ADDR_MODE     FLASH_SPI_MODE_4BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV0_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_512M == 1) */

#if (FLASH_SPI_CFG_DEV0_MX66L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_1G == 1)
#define FLASH_SPI_MX_DEV0_MEM_SIZE      (uint32_t)(134217728)   /* 128MByte (1Gbit)                     */
#define FLASH_SPI_MX_DEV0_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV0_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV0_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV0_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV0_ADDR_SIZE     FLASH_SPI_ADDR_4BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV0_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV0_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV0_ADDR_MODE     FLASH_SPI_MODE_4BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV0_TYPE             FLASH_SPI_TYPE_MX66L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV0_MX66L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_1G == 1) */

#if (FLASH_SPI_CFG_DEV0_MX25R == 1) && (FLASH_SPI_CFG_DEV0_SIZE_64M == 1)
#define FLASH_SPI_MX_DEV0_MEM_SIZE      (uint32_t)(8388608)     /* 8MByte (64Mbit)                      */
#define FLASH_SPI_MX_DEV0_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV0_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV0_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV0_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV0_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV0_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV0_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV0_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV0_TYPE             FLASH_SPI_TYPE_MX25R    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV0_MX25L == 1) && (FLASH_SPI_CFG_DEV0_SIZE_64M == 1) */

#if (FLASH_SPI_CFG_DEV0_MX25U == 1) && (FLASH_SPI_CFG_DEV0_SIZE_64M == 1)
#define FLASH_SPI_MX_DEV0_MEM_SIZE      (uint32_t)(8388608)     /* 8MByte (64Mbit)                      */
#define FLASH_SPI_MX_DEV0_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV0_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV0_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV0_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV0_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV0_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV0_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV0_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV0_TYPE             FLASH_SPI_TYPE_MX25U    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV0_MX25U == 1) && (FLASH_SPI_CFG_DEV0_SIZE_64M == 1) */


/* ==== FLASH device 1 ==== */
#if (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_32M == 1)
#define FLASH_SPI_MX_DEV1_MEM_SIZE      (uint32_t)(4194304)     /* 4MByte (32Mbit)                      */
#define FLASH_SPI_MX_DEV1_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV1_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV1_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV1_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV1_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV1_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV1_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV1_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV1_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_32M == 1) */

#if (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_64M == 1)
#define FLASH_SPI_MX_DEV1_MEM_SIZE      (uint32_t)(8388608)     /* 8MByte (64Mbit)                      */
#define FLASH_SPI_MX_DEV1_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV1_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV1_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV1_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV1_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV1_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV1_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV1_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV1_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_64M == 1) */

#if (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_128M == 1)
#define FLASH_SPI_MX_DEV1_MEM_SIZE      (uint32_t)(16777216)    /* 16MByte (128Mbit)                    */
#define FLASH_SPI_MX_DEV1_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV1_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV1_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV1_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV1_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV1_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV1_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV1_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV1_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_128M == 1) */

#if (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_256M == 1)
#define FLASH_SPI_MX_DEV1_MEM_SIZE      (uint32_t)(33554432)    /* 32MByte (256Mbit)                    */
#define FLASH_SPI_MX_DEV1_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV1_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV1_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV1_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV1_ADDR_SIZE     FLASH_SPI_ADDR_4BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV1_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV1_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV1_ADDR_MODE     FLASH_SPI_MODE_4BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV1_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_256M == 1) */

#if (FLASH_SPI_CFG_DEV1_MX66L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_512M == 1)
#define FLASH_SPI_MX_DEV1_MEM_SIZE      (uint32_t)(67108864)    /* 64MByte (512Mbit)                    */
#define FLASH_SPI_MX_DEV1_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV1_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV1_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV1_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV1_ADDR_SIZE     FLASH_SPI_ADDR_4BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV1_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV1_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV1_ADDR_MODE     FLASH_SPI_MODE_4BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV1_TYPE             FLASH_SPI_TYPE_MX66L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV1_MX66L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_512M == 1) */

#if (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_512M == 1)
#define FLASH_SPI_MX_DEV1_MEM_SIZE      (uint32_t)(67108864)    /* 64MByte (512Mbit)                    */
#define FLASH_SPI_MX_DEV1_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV1_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV1_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV1_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV1_ADDR_SIZE     FLASH_SPI_ADDR_4BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV1_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV1_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV1_ADDR_MODE     FLASH_SPI_MODE_4BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV1_TYPE             FLASH_SPI_TYPE_MX25L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_512M == 1) */

#if (FLASH_SPI_CFG_DEV1_MX66L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_1G == 1)
#define FLASH_SPI_MX_DEV1_MEM_SIZE      (uint32_t)(134217728)   /* 128MByte (1Gbit)                     */
#define FLASH_SPI_MX_DEV1_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV1_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV1_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV1_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV1_ADDR_SIZE     FLASH_SPI_ADDR_4BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV1_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV1_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV1_ADDR_MODE     FLASH_SPI_MODE_4BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV1_TYPE             FLASH_SPI_TYPE_MX66L    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV1_MX66L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_1G == 1) */

#if (FLASH_SPI_CFG_DEV1_MX25R == 1) && (FLASH_SPI_CFG_DEV1_SIZE_64M == 1)
#define FLASH_SPI_MX_DEV1_MEM_SIZE      (uint32_t)(8388608)     /* 8MByte (64Mbit)                      */
#define FLASH_SPI_MX_DEV1_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV1_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV1_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV1_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV1_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV1_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV1_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV1_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV1_TYPE             FLASH_SPI_TYPE_MX25R    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV1_MX25L == 1) && (FLASH_SPI_CFG_DEV1_SIZE_64M == 1) */

#if (FLASH_SPI_CFG_DEV1_MX25U == 1) && (FLASH_SPI_CFG_DEV1_SIZE_64M == 1)
#define FLASH_SPI_MX_DEV1_MEM_SIZE      (uint32_t)(8388608)     /* 8MByte (64Mbit)                      */
#define FLASH_SPI_MX_DEV1_SECT_ADDR     (uint32_t)(0xfffff000)  /* Sector address setting               */
#define FLASH_SPI_MX_DEV1_B32K_ADDR     (uint32_t)(0xffff8000)  /* 32KB Block address setting           */
#define FLASH_SPI_MX_DEV1_B64K_ADDR     (uint32_t)(0xffff0000)  /* 64KB Block address setting           */
#define FLASH_SPI_MX_DEV1_PAGE_SIZE     (uint32_t)(256)         /* Page size when writing               */
#define FLASH_SPI_MX_DEV1_ADDR_SIZE     FLASH_SPI_ADDR_3BYTES   /* Address size (bytes)                 */
#define FLASH_SPI_MX_DEV1_WP_WHOLE_MEM  (uint8_t)(0x0f)         /* Whole memory WP setting              */
#define FLASH_SPI_MX_DEV1_FULL_CHIP_ERASE   FLASH_SPI_MODE_C_ERASE
                                            /* Kind of full-chip erase command that the device supports */
#define FLASH_SPI_MX_DEV1_ADDR_MODE     FLASH_SPI_MODE_3BYTE    /* Addressability Mode                  */
#define FLASH_SPI_DEV1_TYPE             FLASH_SPI_TYPE_MX25U    /* Flash memory type                    */
#endif  /* (FLASH_SPI_CFG_DEV1_MX25U == 1) && (FLASH_SPI_CFG_DEV1_SIZE_64M == 1) */


/*------- Definitions of Status Register value -------*/
#define FLASH_SPI_MX_REG_SRWD           (uint8_t)(0x80)         /* Status Register Write Enable/Disable */
#define FLASH_SPI_MX_REG_QE             (uint8_t)(0x40)         /* Quad Enable Bit                      */
#define FLASH_SPI_MX_REG_BP3            (uint8_t)(0x20)         /* Block Protect Bit3                   */
#define FLASH_SPI_MX_REG_BP2            (uint8_t)(0x10)         /* Block Protect Bit2                   */
#define FLASH_SPI_MX_REG_BP1            (uint8_t)(0x08)         /* Block Protect Bit1                   */
#define FLASH_SPI_MX_REG_BP0            (uint8_t)(0x04)         /* Block Protect Bit0                   */
#define FLASH_SPI_MX_REG_WEL            (uint8_t)(0x02)         /* Write Enable Latch Bit               */
#define FLASH_SPI_MX_REG_WIP            (uint8_t)(0x01)         /* Write In Progress Bit                */
#define FLASH_SPI_MX_REG_MASK           (uint8_t)(0xfc)         /* Write status fixed data              */
#define FLASH_SPI_MX_REG_BPMASK         (uint8_t)(0x3c)         /* Block Protect Bit Mask               */

/*------- Definitions of Configuration Register value -------*/
#define FLASH_SPI_MX_CNFG_DC1           (uint8_t)(0x80)         /* Dummy Cycle 1                        */
#define FLASH_SPI_MX_CNFG_DC0           (uint8_t)(0x40)         /* Dummy Cycle 0                        */
#define FLASH_SPI_MX_CNFG_4BYTE         (uint8_t)(0x20)         /* 4 Byte Address Mode                  */
#define FLASH_SPI_MX_CNFG_PBE           (uint8_t)(0x10)         /* Preamble bit Enable                  */
#define FLASH_SPI_MX_CNFG_TB            (uint8_t)(0x08)         /* Top/Bottom                           */
#define FLASH_SPI_MX_CNFG_ODS2          (uint8_t)(0x04)         /* Output Driver Dtrength 2             */
#define FLASH_SPI_MX_CNFG_ODS1          (uint8_t)(0x02)         /* Output Driver Dtrength 1             */
#define FLASH_SPI_MX_CNFG_ODS0          (uint8_t)(0x01)         /* Output Driver Dtrength 0             */

/*------- Definitions of Secure Register value -------*/
#define FLASH_SPI_MX_SCUR_E_FAIL        (uint8_t)(0x40)         /* Erase Failed                         */
#define FLASH_SPI_MX_SCUR_P_FAIL        (uint8_t)(0x20)         /* Program Failed                       */
#define FLASH_SPI_MX_SCUR_WPSEL         (uint8_t)(0x80)         /* Write Protection Selection bit       */

/*------- Definitions of Lock Register value -------*/
#define FLASH_SPI_MX_LKR_SPBE          (uint8_t)(0xfd)         /* Solid Protection Mode Lock Bit        */
#define FLASH_SPI_MX_LKR_SPBLKDN       (uint8_t)(0xbf)         /* SPB Lock Down Bit                     */

/*------- Definitions of SPB Lock Register value -------*/
#define FLASH_SPI_MX_SPBLKR_SPBLK      (uint8_t)(0x00)         /* SPB Lock Bit                          */


/************************************************************************************************
Typedef definitions
*************************************************************************************************/


/************************************************************************************************
Exported global variables
*************************************************************************************************/


/************************************************************************************************
Exported global functions (to be accessed by other files)
*************************************************************************************************/
/* r_flash_spi_sub.c */
void               r_flash_spi_mx_init_port(uint8_t devno);
void               r_flash_spi_mx_reset_port(uint8_t devno);
flash_spi_status_t r_flash_spi_mx_write_di(uint8_t devno);
flash_spi_status_t r_flash_spi_mx_read_stsreg(uint8_t devno, uint8_t * p_status);
flash_spi_status_t r_flash_spi_mx_read_configreg(uint8_t devno, uint8_t * p_config);
flash_spi_status_t r_flash_spi_mx_read_scurreg(uint8_t devno, uint8_t * p_scur);
flash_spi_status_t r_flash_spi_mx_set_write_protect(uint8_t devno, uint8_t wpsts, bool read_after_write);
flash_spi_status_t r_flash_spi_mx_write_configuration(uint8_t devno, flash_spi_reg_info_t * p_reg, bool read_after_write);
flash_spi_status_t r_flash_spi_mx_quad_enable(uint8_t devno, bool read_after_write);
flash_spi_status_t r_flash_spi_mx_quad_disable(uint8_t devno, bool read_after_write);
flash_spi_status_t r_flash_spi_mx_read(uint8_t devno, flash_spi_info_t * p_flash_spi_info);
flash_spi_status_t r_flash_spi_mx_write_page(uint8_t devno, flash_spi_info_t  * p_flash_spi_info, bool read_after_write_add, bool read_after_write_data);
flash_spi_status_t r_flash_spi_mx_erase(uint8_t devno, flash_spi_erase_info_t * p_flash_spi_erase_info);
flash_spi_status_t r_flash_spi_mx_rdid(uint8_t devno, uint8_t * p_data);
flash_spi_status_t r_flash_spi_mx_polling(uint8_t devno, flash_spi_poll_mode_t mode);
flash_spi_status_t r_flash_spi_mx_enter_4addr(uint8_t devno);
flash_spi_status_t r_flash_spi_mx_get_memory_info(uint8_t devno, flash_spi_mem_info_t * p_flash_spi_mem_info);
flash_spi_status_t r_flash_spi_mx_check_cnt(uint8_t devno, flash_spi_info_t  * p_flash_spi_info);
uint32_t           r_flash_spi_mx_page_calc(uint8_t devno, flash_spi_info_t  * p_flash_spi_info);
flash_spi_status_t r_flash_spi_mx_set_write_protect_advanced_sector(uint8_t devno, flash_spi_protect_sector_info_t * flash_spi_protect_sector_info);
flash_spi_status_t r_flash_spi_mx_erase_write_protect_advanced_sector(uint8_t devno);


#endif /* FLASH_SPI_TYPE_SUB_H */

/* End of File */
