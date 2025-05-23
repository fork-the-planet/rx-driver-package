/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_flash_spi_if.h
* Version      : 3.51
* Description  : FLASH SPI driver interface header file
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 23.07.2014 2.21    Created
*              : 29.05.2015 2.32    Revised functions of same as Ver.2.32 of EEPROM SPI FIT module.
*              : 24.12.2015 2.33    Added RX130, RX23T and RX24T.
*              : 31.07.2017 2.34    Modified Application note.
*              : 21.12.2018 3.00    Change flash drive interface to Memory Access Driver Interface
*              : 20.05.2019 3.01    Added support for GNUC and ICCRX.
*                                   Fixed coding style.
*              : 10.12.2020 3.02    Changed version to 3.02.
*              : 31.12.2021 3.03    Changed version to 3.03.
*              : 30.06.2022 3.10    Added macros to specify the ports used for SS#.
*              : 16.03.2023 3.20    Added support for AT25QF641B-SHB with Indirect Access Mode of QSPIX
*                                   Added support for RSCI and QSPIX Memory Mapped Mode
*                                   Removed the processing related to other unsupported flash devices.
*              : 15.06.2023 3.30    Updated and added new demo project.
*              : 15.11.2023 3.40    Added support for reading across multiple banks in QSPIX
*                                   Memory Mapped Mode.
*                                   Updated according to GSCE Code Checker 6.50.
*                                   Added support for MX25U6432F.
*                                   Added features Advanced sector protection supporting for MX66L1G45 and MX25U6432F.
*              : 20.12.2024 3.50    Updated the parameter checking of the Read Data operation.
*                                   Modified comment of API function to Doxygen style.
*                                   Added dependency modules to the options in MDF file.
*                                   Updated demo projects.
*              : 15.03.2025 3.51    Updated disclaimer.
***********************************************************************************************************************/
#ifndef FLASH_SPI_IF_H
#define FLASH_SPI_IF_H

/************************************************************************************************
Includes <System Includes> , "Project Includes"
*************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"


/************************************************************************************************
Macro definitions
*************************************************************************************************/
#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

/* Define using Firmware Integration Technology (FIT) for RX family MCU. */
#define FLASH_SPI_CFG_USE_FIT

/* Driver version */
#define FLASH_SPI_VERSION_MAJOR       (3)
#define FLASH_SPI_VERSION_MINOR       (51)


/*--------------- Define no. of slots ----------------*/
#define FLASH_SPI_DEV0                (0)                   /* Device 0                             */
#define FLASH_SPI_DEV1                (1)                   /* Device 1                             */

/* Define address size */
#define FLASH_SPI_ADDR_4BYTES         ((uint8_t)(4))
#define FLASH_SPI_ADDR_3BYTES         ((uint8_t)(3))


/************************************************************************************************
Typedef definitions
*************************************************************************************************/
/* Enumeration for return values */
typedef enum e_flash_status
{
    FLASH_SPI_SUCCESS_BUSY    = 1,     /* Successful operation (EERPOM is busy)         */
    FLASH_SPI_SUCCESS         = 0,     /* Successful operation                          */
    FLASH_SPI_ERR_PARAM       = -1,    /* Parameter error                               */
    FLASH_SPI_ERR_HARD        = -2,    /* Hardware error                                */
    FLASH_SPI_ERR_WP          = -4,    /* Write-protection error                        */
    FLASH_SPI_ERR_TIMEOUT     = -6,    /* Time out error                                */
    FLASH_SPI_ERR_OTHER       = -7,    /* Other error                                   */
    FLASH_SPI_ERR_WP_ADVANCED = -8     /* Advanced write-protection error               */
} flash_spi_status_t;

typedef enum e_flash_spi_erase_mode
{
    FLASH_SPI_MODE_C_ERASE = 1,
    FLASH_SPI_MODE_B_ERASE,
    FLASH_SPI_MODE_D_ERASE,
    FLASH_SPI_MODE_B4K_ERASE,
    FLASH_SPI_MODE_B32K_ERASE,
    FLASH_SPI_MODE_B64K_ERASE,
    FLASH_SPI_MODE_SCUR_ERASE,
    FLASH_SPI_MODE_S_ERASE,
    FLASH_SPI_MODE_SS_ERASE,
    FLASH_SPI_MODE_P_ERASE
} flash_spi_erase_mode_t;

typedef enum e_flash_spi_poll_mode
{
    FLASH_SPI_MODE_REG_WRITE_POLL = 1,
    FLASH_SPI_MODE_PROG_POLL,
    FLASH_SPI_MODE_ERASE_POLL
} flash_spi_poll_mode_t;

typedef enum e_flash_spi_opmode
{
    FLASH_SPI_SINGLE = 0,           /* Single-SPI mode                          */
    FLASH_SPI_DUAL,                 /* Dual-SPI mode                            */
    FLASH_SPI_QUAD                  /* Quad-SPI mode                            */
} flash_spi_opmode_t;

typedef enum e_flash_spi_protect_mode
{
    FLASH_SPI_MODE_INDIVIDUAL_PROTECT = 1,
    FLASH_SPI_MODE_ALL_PROTECT
} flash_spi_protect_mode_t;

/* Flash memory information */
typedef struct
{
    uint32_t           addr;        /* Address to issue a command               */
    uint32_t           cnt;         /* Number of bytes to be read/written       */
    uint32_t           data_cnt;    /* Temporary counter or Number of bytes to be written in a page */
    uint8_t          * p_data;      /* Data storage buffer pointer              */
    flash_spi_opmode_t op_mode;     /* SPI operating mode; ignore it when using write/read data
                                       in a Security register page              */
} flash_spi_info_t;                 /* 20 bytes                                 */

/* Flash memory size information */
typedef struct
{
    uint32_t        mem_size;       /* Max memory size                          */
    uint32_t        wpag_size;      /* Write page size                          */
} flash_spi_mem_info_t;             /* 8 bytes                                  */

/* Flash memory erase information */
typedef struct
{
    uint32_t        addr;           /* Address to issue a command               */
    flash_spi_erase_mode_t  mode;   /* Mode of erase                            */
} flash_spi_erase_info_t;           /* 8 bytes                                  */

/* Flash memory register information */
typedef struct
{
    uint8_t         status;         /* Status register                           */
    uint8_t         config1;        /* Configuration or Configuration-1 register */
    uint8_t         config2;        /* Configuration-2 register                  */
    uint8_t         rsv[1];
} flash_spi_reg_info_t;             /* 4 bytes                                   */

/* Flash memory advanced sector protection information */
typedef struct
{
    uint32_t                 addr;                /* Address to issue a command   */
    flash_spi_protect_mode_t protect_mode;        /* Advanced protection mode     */
    bool                     lock_protect_enable; /* prevent further modification */
} flash_spi_protect_sector_info_t; 


/************************************************************************************************
Exported global variables
*************************************************************************************************/


/************************************************************************************************
Exported global functions (to be accessed by other files)
*************************************************************************************************/

/* ---- API for all flash memory  ---- */

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Open
 * Description  : .
 * Argument     : devno
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Open (uint8_t devno);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Close
 * Description  : .
 * Argument     : devno
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Close (uint8_t devno);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Status
 * Description  : .
 * Arguments    : devno
 *              : p_status
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Read_Status (uint8_t devno, uint8_t * p_status);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Set_Write_Protect
 * Description  : .
 * Arguments    : devno
 *              : wpsts
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Set_Write_Protect (uint8_t devno, uint8_t wpsts);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Di
 * Description  : .
 * Argument     : devno
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Write_Di (uint8_t devno);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Data
 * Description  : .
 * Arguments    : devno
 *              : p_flash_spi_info
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Read_Data (uint8_t devno, flash_spi_info_t * p_flash_spi_info);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Data_Page
 * Description  : .
 * Arguments    : devno
 *              : p_flash_spi_info
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Write_Data_Page (uint8_t devno, flash_spi_info_t * p_flash_spi_info);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Erase
 * Description  : .
 * Argument     : devno
 *              : p_flash_spi_erase_info
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Erase (uint8_t devno, flash_spi_erase_info_t * p_flash_spi_erase_info);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Polling
 * Description  : .
 * Arguments    : devno
 *              : mode
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Polling (uint8_t devno, flash_spi_poll_mode_t mode);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_ID
 * Description  : .
 * Arguments    : devno
 *              : p_data
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Read_ID (uint8_t devno, uint8_t * p_data);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_GetMemoryInfo
 * Description  : .
 * Arguments    : devno
 *              : p_flash_spi_mem_info
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_GetMemoryInfo (uint8_t devno, flash_spi_mem_info_t * p_flash_spi_mem_info);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_GetVersion
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
uint32_t           R_FLASH_SPI_GetVersion (void);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Set_LogHdlAddress
 * Description  : .
 * Argument     : user_long_que
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Set_LogHdlAddress (uint32_t user_long_que);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Log
 * Description  : .
 * Arguments    : flg
 *              : fid
 *              : line
 * Return Value : .
 *********************************************************************************************************************/
uint32_t           R_FLASH_SPI_Log (uint32_t flg, uint32_t fid, uint32_t line);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_1ms_Interval
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
void               R_FLASH_SPI_1ms_Interval (void);


/* ---- API for specific flash memory ---- */

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Configuration
 * Description  : .
 * Arguments    : devno
 *              : p_config
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Read_Configuration (uint8_t devno, uint8_t * p_config);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Configuration
 * Description  : .
 * Arguments    : devno
 *              : p_reg
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Write_Configuration (uint8_t devno, flash_spi_reg_info_t * p_reg);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Set_4byte_Address_Mode
 * Description  : .
 * Argument     : devno
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Set_4byte_Address_Mode (uint8_t devno);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Security
 * Description  : .
 * Arguments    : devno
 *              : p_scur
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Read_Security (uint8_t devno, uint8_t * p_scur);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Quad_Enable
 * Description  : .
 * Argument     : devno
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Quad_Enable (uint8_t devno);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Quad_Disable
 * Description  : .
 * Argument     : devno
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Quad_Disable (uint8_t devno);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Flag_Status
 * Description  : .
 * Arguments    : devno
 *              : p_status
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Read_Flag_Status (uint8_t devno, uint8_t * p_status);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Clear_Status
 * Description  : .
 * Argument     : devno
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Clear_Status (uint8_t devno);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Status
 * Description  : .
 * Arguments    : devno
 *              : p_reg
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Write_Status (uint8_t devno, uint8_t * p_reg);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Status2
 * Description  : .
 * Arguments    : devno
 *              : p_reg
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Write_Status2 (uint8_t devno, uint8_t * p_reg);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Status3
 * Description  : .
 * Arguments    : devno
 *              : p_reg
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Write_Status3 (uint8_t devno, uint8_t * p_reg);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Status2
 * Description  : .
 * Arguments    : devno
 *              : p_status
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Read_Status2 (uint8_t devno, uint8_t * p_status);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Status3
 * Description  : .
 * Arguments    : devno
 *              : p_status
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Read_Status3 (uint8_t devno, uint8_t * p_status);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Data_Security_Page
 * Description  : .
 * Arguments    : devno
 *              : p_flash_spi_info
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Read_Data_Security_Page (uint8_t devno, flash_spi_info_t * p_flash_spi_info);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Data_Security_Page
 * Description  : .
 * Arguments    : devno
 *              : p_flash_spi_info
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Write_Data_Security_Page (uint8_t devno, flash_spi_info_t * p_flash_spi_info);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_DeepPDown
 * Description  : .
 * Argument     : devno
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_DeepPDown (uint8_t devno);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_ReleaseDeepPDown
 * Description  : .
 * Arguments    : devno
 *              : p_data
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_ReleaseDeepPDown (uint8_t devno, uint8_t * p_data);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Set_Write_Protect_Advanced_Sector
 * Description  : .
 * Arguments    : devno
 *              : flash_spi_protect_sector_info
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Set_Write_Protect_Advanced_Sector (uint8_t devno, flash_spi_protect_sector_info_t * flash_spi_protect_sector_info);

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Erase_Write_Protect_Advanced_Sector
 * Description  : .
 * Arguments    : devno
 * Return Value : .
 *********************************************************************************************************************/
flash_spi_status_t R_FLASH_SPI_Erase_Write_Protect_Advanced_Sector (uint8_t devno);


#endif /* FLASH_SPI_IF_H */

/* End of File */
