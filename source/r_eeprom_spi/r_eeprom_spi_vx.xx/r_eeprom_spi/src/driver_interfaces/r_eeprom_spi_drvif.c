/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/************************************************************************************************
* System Name  : EEPROM driver software
* File Name    : r_eeprom_spi_drvif.c
* Version      : 3.21
* Device       : -
* Abstract     : IO I/F module
* Tool-Chain   : -
* OS           : not use
* H/W Platform : -
* Description  : SPI Renesas EEPROM I/O file
* Limitation   : none
*************************************************************************************************/
/************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 28.11.2014 2.30    Revised functions of same as Ver.2.30 of other middleware.
*              : 30.01.2015 2.31    Added RX71M.
*              : 22.12.2018 3.00    Added RX72T.  Change eeprom drive interface to Memory Access Driver Interface
*              : 30.06.2022 3.10    Fixed issues of wrong conditional expression in the if statement.
*              : 15.03.2025 3.21    Updated disclaimer.
*************************************************************************************************/


/************************************************************************************************
Includes <System Includes> , "Project Includes"
*************************************************************************************************/
#include "r_eeprom_spi_if.h"                      /* EEPROM driver I/F definitions                 */
#include "r_eeprom_spi_config.h"                  /* EEPROM driver Configuration definitions       */
#include "r_memdrv_rx_if.h"                       /* MEMORY driver I/F definitions                 */
#include "../r_eeprom_spi_private.h"              /* EEPROM driver Private module definitions      */


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
* Function Name: r_eeprom_spi_drvif_open
* Description  : Initializes I/O driver.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_open(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;
    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Open(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_open_tx_data
* Description  : Initializes I/O driver for writing data.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_open_tx_data(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;
    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Open(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_open_rx_data
* Description  : Initializes I/O driver for reading data.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_open_rx_data(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;
    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Open(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_close
* Description  : Resets I/O driver.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_close(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;
    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Close(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_close_tx_data
* Description  : Resets I/O driver for writing data.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_close_tx_data(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;
    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Close(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_close_rx_data
* Description  : Resets I/O driver for reading data.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_close_rx_data(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;
    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Close(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_disable
* Description  : Disables I/O driver.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_disable(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;

    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Disable(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_enable
* Description  : Enables I/O driver.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_enable(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;
    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Enable(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_enable_tx_data
* Description  : Enables I/O driver for writing data.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_enable_tx_data(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt = 0;
    memdrv_info.p_data = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_EnableTxData(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_enable_rx_data
* Description  : Enables I/O driver for reading data.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_enable_rx_data(uint8_t devno)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = 0;
    memdrv_info.p_data  = NULL;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_EnableRxData(devno,&memdrv_info);

    if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_tx
* Description  : Transmits data for command and status register.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
*              : uint32_t        txcnt                      ;   Number of bytes to be write
*              : uint8_t       * p_data                     ;   Write data storage buffer pointer
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_HARD                        ;   Hardware error
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_tx(uint8_t devno, uint32_t txcnt, uint8_t * p_data)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = txcnt;
    memdrv_info.p_data  = p_data;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Tx(devno,&memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return EEPROM_SPI_ERR_HARD;
    }
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_tx_data
* Description  : Transmits data using the single mode.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
*              : uint32_t        txcnt                      ;   Number of bytes to be write
*              : uint8_t       * p_data                     ;   Write data storage buffer pointer
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_HARD                        ;   Hardware error
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_tx_data(uint8_t devno, uint32_t txcnt, uint8_t * p_data)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = txcnt;
    memdrv_info.p_data  = p_data;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_TxData(devno,&memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return EEPROM_SPI_ERR_HARD;
    }
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_rx
* Description  : Receives data for status register and Read ID.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
*              : uint32_t        rxcnt                      ;   Number of bytes to be read
*              : uint8_t       * p_data                     ;   Read data storage buffer pointer
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_HARD                        ;   Hardware error
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_rx(uint8_t devno, uint32_t rxcnt, uint8_t * p_data)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = rxcnt;
    memdrv_info.p_data  = p_data;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_Rx(devno,&memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return EEPROM_SPI_ERR_HARD;
    }
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_rx_data
* Description  : Receives data using the single mode.
* Arguments    : uint8_t         devno                      ;   Device No. (EEPROM_SPI_DEVn)
*              : uint32_t        rxcnt                      ;   Number of bytes to be read
*              : uint8_t       * p_data                     ;   Read data storage buffer pointer
* Return Value : EEPROM_SPI_SUCCESS                         ;   Successful operation
*              : EEPROM_SPI_ERR_HARD                        ;   Hardware error
*              : EEPROM_SPI_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_rx_data(uint8_t devno, uint32_t rxcnt, uint8_t * p_data)
{
    memdrv_err_t ret_drv = MEMDRV_SUCCESS;
    st_memdrv_info_t  memdrv_info;

    memdrv_info.cnt     = rxcnt;
    memdrv_info.p_data  = p_data;
    memdrv_info.io_mode = MEMDRV_MODE_SINGLE;

    ret_drv = R_MEMDRV_RxData(devno,&memdrv_info);

    if (MEMDRV_ERR_HARD == ret_drv)
    {
        return EEPROM_SPI_ERR_HARD;
    }
    else if (MEMDRV_SUCCESS > ret_drv)
    {
        return EEPROM_SPI_ERR_OTHER;
    }
    return EEPROM_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_1ms_interval
* Description  : 1ms Interval Timer call function for driver interface.
* Arguments    : None
* Return Value : None
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
void r_eeprom_spi_drvif_1ms_interval(void)
{
    R_MEMDRV_1msInterval();
    return;
}


/************************************************************************************************
* Function Name: r_eeprom_spi_drvif_set_loghdladdress
* Description  : Sets handler address for driver interface.
* Arguments    : uint32_t           user_long_que       ;   Handler address
* Return Value : EEPROM_SPI_SUCCESS                     ;   Successful operation
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
eeprom_status_t r_eeprom_spi_drvif_set_loghdladdress(uint32_t user_long_que)
{
    R_MEMDRV_SetLogHdlAddress(user_long_que);
    return EEPROM_SPI_SUCCESS;
}


/* End of File */
