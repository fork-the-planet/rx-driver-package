/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* System Name  : FLASH SPI driver software
* File Name    : r_flash_spi_drvif.c
* Version      : 3.51
* Device       : -
* Abstract     : IO I/F module
* Tool-Chain   : -
* OS           : not use
* H/W Platform : -
* Description  : SPI FLASH I/O file
* Limitation   : none
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 23.07.2014 2.21     Created
*              : 29.05.2015 2.32     Revised functions of same as Ver.2.32 of EEPROM SPI FIT module.
*              : 21.12.2018 3.00     Change flash drive interface to Memory Access Driver Interface
*              : 31.12.2021 3.03     Added variable "read_after_write" "read_after_write_add" and
*                                    "read_after_write_data" for controlling SPI bus.
*              : 30.06.2022 3.10     Fixed issues of wrong conditional expression in the if statement.
*              : 16.03.2023 3.20     Added the QSPIX Memory Mapped Mode.
*              : 15.11.2023 3.40     Updated according to GSCE Code Checker 6.50.
*              : 15.03.2025 3.51     Updated disclaimer.
***********************************************************************************************************************/


/************************************************************************************************
Includes <System Includes> , "Project Includes"
*************************************************************************************************/
#include "r_flash_spi_if.h"                      /* FLASH driver I/F definitions                 */
#include "r_flash_spi_config.h"                  /* FLASH driver Configuration definitions       */
#include "r_memdrv_rx_if.h"                      /* MEMORY driver I/F definitions                */
#include "../r_flash_spi_private.h"              /* FLASH driver Private module definitions      */


/************************************************************************************************
Macro definitions
*************************************************************************************************/


/************************************************************************************************
Typedef definitions
*************************************************************************************************/


/************************************************************************************************
Exported global variables (to be accessed by other files)
*************************************************************************************************/


/************************************************************************************************
Private global variables and functions
*************************************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_open
* Description  : Initializes I/O driver.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_open(uint8_t devno)
{
    memdrv_err_t     ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t memdrv_info;

    memdrv_info.cnt     = 0;
    memdrv_info.p_data  = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Open(devno, &memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_open
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_open_tx_data
* Description  : Initializes I/O driver for writing data.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_open_tx_data(uint8_t devno)
{
    memdrv_err_t     ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t memdrv_info;

    memdrv_info.cnt     = 0;
    memdrv_info.p_data  = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Open(devno, &memdrv_info);

     if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_open_tx_data
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_open_rx_data
* Description  : Initializes I/O driver for reading data.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_open_rx_data(uint8_t devno)
{
    memdrv_err_t     ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t memdrv_info;

    memdrv_info.cnt     = 0;
    memdrv_info.p_data  = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Open(devno, &memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_open_rx_data
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_close
* Description  : Resets I/O driver.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_close(uint8_t devno)
{
    memdrv_err_t      ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt      = 0;
    memdrv_info.p_data   = NULL;
    memdrv_info.io_mode  = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Close(devno, &memdrv_info);

     if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_close
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_close_tx_data
* Description  : Resets I/O driver for writing data.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_close_tx_data(uint8_t devno)
{
    memdrv_err_t     ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t memdrv_info;

    memdrv_info.cnt     = 0;
    memdrv_info.p_data  = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Close(devno, &memdrv_info);

     if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_close_tx_data
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_close_rx_data
* Description  : Resets I/O driver for reading data.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_close_rx_data(uint8_t devno)
{
    memdrv_err_t     ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t memdrv_info;

    memdrv_info.cnt     = 0;
    memdrv_info.p_data  = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Close(devno, &memdrv_info);

     if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_close_rx_data
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_disable
* Description  : Disables I/O driver.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_disable(uint8_t devno)
{
    memdrv_err_t     ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t memdrv_info;

    memdrv_info.cnt     = 0;
    memdrv_info.p_data  = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Disable(devno, &memdrv_info);

     if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_disable
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_enable
* Description  : Enables I/O driver.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_enable(uint8_t devno)
{
    memdrv_err_t     ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t memdrv_info;

    memdrv_info.cnt     = 0;
    memdrv_info.p_data  = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Enable(devno, &memdrv_info);

     if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_enable
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_enable_tx_data
* Description  : Enables I/O driver for writing data.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_enable_tx_data(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;
    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_EnableTxData(devno, &memdrv_info);

     if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_enable_tx_data
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_enable_rx_data
* Description  : Enables I/O driver for reading data.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_enable_rx_data(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = 0;
    memdrv_info.p_data  = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_EnableRxData(devno, &memdrv_info);

     if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_enable_rx_data
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_tx
* Description  : Transmits data for command and status register.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
*              : uint32_t        txcnt                       ;   Number of bytes to be write
*              : uint8_t       * p_data                      ;   Write data storage buffer pointer
*              : bool            read_after_write            ;   Control SPI bus
*              : bool            read_in_memory_mapped       ;   Read access in memory-mapped mode
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_HARD                          ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_tx(uint8_t devno, uint32_t txcnt, uint8_t * p_data, bool read_after_write, bool read_in_memory_mapped)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = txcnt;
    memdrv_info.p_data  = p_data;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;
    memdrv_info.read_after_write = read_after_write;
    memdrv_info.read_in_memory_mapped = read_in_memory_mapped;

    ret_drv = R_MEMDRV_Tx(devno, &memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return FLASH_SPI_ERR_HARD;
    } 
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    else
    {
        /* Do nothing */
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_tx
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_tx_add
* Description  : Transmits data for address.
* Arguments    : uint8_t            devno                    ;   Device No. (FLASH_SPI_DEVn)
*              : uint32_t           txcnt                    ;   Number of bytes to be write
*              : uint8_t          * p_data                   ;   Write data storage buffer pointer
*              : flash_spi_opmode_t op_mode                  ;   SPI mode
*              : bool               read_after_write_add     ;   Whether or not to close SPI bus cycle
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_HARD                          ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_tx_add(uint8_t devno, uint32_t txcnt, uint8_t * p_data, flash_spi_opmode_t op_mode, bool read_after_write_add)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = txcnt;
    memdrv_info.p_data  = p_data;
    memdrv_info.read_after_write = read_after_write_add;

    switch (op_mode)
    {
        case FLASH_SPI_SINGLE:
            memdrv_info.io_mode = MEMDRV_MODE_SINGLE;
            break;
        case FLASH_SPI_DUAL:
            memdrv_info.io_mode = MEMDRV_MODE_DUAL;
            break;
        case FLASH_SPI_QUAD:
            memdrv_info.io_mode = MEMDRV_MODE_QUAD;
            break;
        default:
            memdrv_info.io_mode = MEMDRV_MODE_SINGLE;
            break;
    } 

    ret_drv = R_MEMDRV_TxData(devno, &memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return FLASH_SPI_ERR_HARD;
    } 
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    else
    {
        /* Do nothing */
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_tx_add
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_tx_data
* Description  : Transmits data using the single mode.
* Arguments    : uint8_t            devno                    ;   Device No. (FLASH_SPI_DEVn)
*              : uint32_t           txcnt                    ;   Number of bytes to be write
*              : uint8_t          * p_data                   ;   Write data storage buffer pointer
*              : flash_spi_opmode_t op_mode                  ;   SPI mode
*              : bool               read_after_write_data    ;   Whether or not to close SPI bus cycle
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_HARD                          ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_tx_data(uint8_t devno, uint32_t txcnt, uint8_t * p_data, flash_spi_opmode_t op_mode, bool read_after_write_data)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = txcnt;
    memdrv_info.p_data  = p_data;
    memdrv_info.read_after_write = read_after_write_data;

    switch (op_mode)
    {
        case FLASH_SPI_SINGLE:
            memdrv_info.io_mode = MEMDRV_MODE_SINGLE;
            break;
        case FLASH_SPI_DUAL:
            memdrv_info.io_mode = MEMDRV_MODE_DUAL;
            break;
        case FLASH_SPI_QUAD:
            memdrv_info.io_mode = MEMDRV_MODE_QUAD;
            break;
        default:
            memdrv_info.io_mode = MEMDRV_MODE_SINGLE;
            break;
    }

    ret_drv = R_MEMDRV_TxData(devno, &memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return FLASH_SPI_ERR_HARD;
    } 
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    else
    {
        /* Do nothing */
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_tx_data
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_rx
* Description  : Receives data for status register and Read ID.
* Arguments    : uint8_t         devno                       ;   Device No. (FLASH_SPI_DEVn)
*              : uint32_t        rxcnt                       ;   Number of bytes to be read
*              : uint8_t       * p_data                      ;   Read data storage buffer pointer
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_HARD                          ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_rx(uint8_t devno, uint32_t rxcnt, uint8_t * p_data)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = rxcnt;
    memdrv_info.p_data  = p_data;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Rx(devno, &memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return FLASH_SPI_ERR_HARD;
    } 
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    else
    {
        /* Do nothing */
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_rx
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_rx_add
* Description  : Receives data for address.
* Arguments    : uint8_t            devno                    ;   Device No. (FLASH_SPI_DEVn)
*              : uint32_t           rxcnt                    ;   Number of bytes to be read
*              : uint8_t          * p_data                   ;   Read data storage buffer pointer
*              : flash_spi_opmode_t op_mode                  ;   SPI mode
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_HARD                          ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_rx_add(uint8_t devno, uint32_t rxcnt, uint8_t * p_data, flash_spi_opmode_t op_mode)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = rxcnt;
    memdrv_info.p_data  = p_data;

    switch (op_mode)
    {
        case FLASH_SPI_SINGLE:
            memdrv_info.io_mode = MEMDRV_MODE_SINGLE;
            break;
        case FLASH_SPI_DUAL:
            memdrv_info.io_mode = MEMDRV_MODE_DUAL;
            break;
        case FLASH_SPI_QUAD:
            memdrv_info.io_mode = MEMDRV_MODE_QUAD;
            break;
        default:
            memdrv_info.io_mode = MEMDRV_MODE_SINGLE;
            break;
    }

    ret_drv = R_MEMDRV_RxData(devno, &memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return FLASH_SPI_ERR_HARD;
    } 
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    else
    {
        /* Do nothing */
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_rx_add
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_rx_data
* Description  : Receives data using the single mode.
* Arguments    : uint8_t            devno                    ;   Device No. (FLASH_SPI_DEVn)
*              : uint32_t           rxcnt                    ;   Number of bytes to be read
*              : uint8_t          * p_data                   ;   Read data storage buffer pointer
*              : uint32_t           p_addr                   ;   Read start address
*              : uint8_t            addr_size                ;   Address size
*              : flash_spi_opmode_t op_mode                  ;   SPI mode
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*              : FLASH_SPI_ERR_HARD                          ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                         ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_rx_data(uint8_t devno, uint32_t rxcnt, uint8_t * p_data, uint32_t p_addr, uint8_t addr_size, flash_spi_opmode_t op_mode)
{
    memdrv_err_t     ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t memdrv_info;

    memdrv_info.cnt     = rxcnt;
    memdrv_info.p_data  = p_data;
    memdrv_info.p_addr  = p_addr;

    switch (op_mode)
    {
        case FLASH_SPI_SINGLE:
            memdrv_info.io_mode = MEMDRV_MODE_SINGLE;
            break;
        case FLASH_SPI_DUAL:
            memdrv_info.io_mode = MEMDRV_MODE_DUAL;
            break;
        case FLASH_SPI_QUAD:
            memdrv_info.io_mode = MEMDRV_MODE_QUAD;
            break;
        default:
            memdrv_info.io_mode = MEMDRV_MODE_SINGLE;
            break;
    }

    switch (addr_size)
    {
        case FLASH_SPI_ADDR_4BYTES:
            memdrv_info.addr_size = MEMDRV_ADDR_4BYTES;
            break;
        case FLASH_SPI_ADDR_3BYTES:
            memdrv_info.addr_size = MEMDRV_ADDR_3BYTES;
            break;
        default:
            memdrv_info.addr_size = MEMDRV_ADDR_3BYTES;
            break;
    }

    ret_drv = R_MEMDRV_RxData(devno, &memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return FLASH_SPI_ERR_HARD;
    } 
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return FLASH_SPI_ERR_OTHER;
    }
    else
    {
        /* Do nothing */
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_rx_data
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_1ms_interval
* Description  : 1ms Interval Timer call function for driver interface.
* Arguments    : None
* Return Value : None
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
void r_flash_spi_drvif_1ms_interval(void)
{
    R_MEMDRV_1msInterval();
}
/******************************************************************************
 End of function r_flash_spi_drvif_1ms_interval
 *****************************************************************************/


/************************************************************************************************
* Function Name: r_flash_spi_drvif_set_loghdladdress
* Description  : Sets handler address for driver interface.
* Arguments    : uint32_t           user_long_que           ;   Handler address
* Return Value : FLASH_SPI_SUCCESS                           ;   Successful operation
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_drvif_set_loghdladdress(uint32_t user_long_que)
{
    R_MEMDRV_SetLogHdlAddress(user_long_que);
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_drvif_set_loghdladdress
 *****************************************************************************/


/* End of File */
