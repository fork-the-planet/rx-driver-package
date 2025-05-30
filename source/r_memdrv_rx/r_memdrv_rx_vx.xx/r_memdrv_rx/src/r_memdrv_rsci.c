/***********************************************************************************************************************
* Copyright (c) 2023 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* System Name  : MEMDRV software
* File Name    : r_memdrv_rsci.c
* Version      : 1.31
* Device       : -
* Abstract     : IO I/F module
* Tool-Chain   : -
* OS           : not use
* H/W Platform : -
* Description  : MEMDRV I/O file
* Limitation   : None
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 16.03.2023 1.00    Initial Release
*              : 15.03.2025 1.31    Updated disclaimer.
***********************************************************************************************************************/

/************************************************************************************************
Includes <System Includes> , "Project Includes"
*************************************************************************************************/
#include "r_memdrv_rx_if.h"                      /* MEMDRV driver I/F definitions                  */
#include "r_memdrv_rx_config.h"                  /* MEMDRV driver Configuration definitions        */
#include "./src/r_memdrv_rx_private.h"           /* MEMDRV driver Private module definitions       */

/* Check driver interface. */
#if ((MEMDRV_CFG_DEV0_INCLUDED == 1) && (MEMDRV_CFG_DEV0_MODE_DRVR == MEMDRV_DRVR_RX_FIT_RSCI_SPI)) || \
    ((MEMDRV_CFG_DEV1_INCLUDED == 1) && (MEMDRV_CFG_DEV1_MODE_DRVR == MEMDRV_DRVR_RX_FIT_RSCI_SPI))
#include "r_pinset.h"
/************************************************************************************************
Macro definitions
*************************************************************************************************/
#define RSCI_TIMER_CH_FLG                 (0)
#define RSCI_TIMER_CH_COUNT               (1)
#define RSCI_TIMER_CH_MAX_COUNT           (2)
#define RSCI_TIMER_MIN_TIME               (100)       /* 100ms */
#define RSCI_SECTOR_SIZE                  (512)       /* 1 sector size */
#define RSCI_EXCHG_MAX_COUNT              (65532)

#define RSCI_MAX_CHANNELS                 (RSCI_NUM_CH)
/************************************************************************************************
Typedef definitions
*************************************************************************************************/

/************************************************************************************************
Exported global variables (to be accessed by other files)
*************************************************************************************************/

/************************************************************************************************
Private global variables and functions
*************************************************************************************************/
static volatile bool  transfer_busy = false;
static rsci_hdl_t rsci_handle;
static volatile uint32_t memdrv_rsci_timer_cnt_out[RSCI_MAX_CHANNELS][RSCI_TIMER_CH_MAX_COUNT + 1];

static void                 r_memdrv_rsci_start_timer(uint8_t channel, uint32_t msec);
static memdrv_err_t         r_memdrv_rsci_check_timer(uint8_t channel);
static void                 r_memdrv_rsci_end_timer(uint8_t channel);
static memdrv_err_t         r_memdrv_rsci_wait(uint8_t channel, uint32_t size);
static void                 r_memdrv_rsci_callback(void *p_data);
static void                 rsci_init_ports(void);

/************************************************************************************************
* Function Name: r_memdrv_rsci_open
* Description  : Initializes I/O driver.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*              : MEMDRV_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_open(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    uint8_t channel = r_memdrv_get_drv_ch(devno);
    rsci_cfg_t config;
    
    if (MEMDRV_DEV0 == devno)
    {
        config.sspi.bit_rate = (uint32_t)MEMDRV_CFG_DEV0_BR;
    }
    else if (MEMDRV_DEV1 == devno)
    {
        config.sspi.bit_rate = (uint32_t)MEMDRV_CFG_DEV1_BR;
    }

    config.sspi.spi_mode = RSCI_SPI_MODE_3;
    config.sspi.msb_first = true;
    config.sspi.invert_data = false;
    config.sspi.int_priority = 4;
    
    rsci_init_ports();

    /* Casting to a uint8_t type is valid. */
    if (RSCI_SUCCESS != R_RSCI_Open(channel,
                                  RSCI_MODE_SSPI,
                                  &config,
                                  &r_memdrv_rsci_callback,
                                  &rsci_handle))
    {
        R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
        return MEMDRV_ERR_OTHER;
    }

    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_open() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_close
* Description  : Resets I/O driver.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*              : MEMDRV_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_close(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    if (RSCI_SUCCESS != R_RSCI_Close(rsci_handle))
    {
        R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
        return MEMDRV_ERR_OTHER;
    }
    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_close() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_disable
* Description  : Disables I/O driver.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_disable(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_disable() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_disable_tx_data
* Description  : Disables I/O driver for writing data.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_disable_tx_data(uint8_t devno,
                                          st_memdrv_info_t * p_memdrv_info)
{
    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_disable_tx_data() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_disable_rx_data
* Description  : Disables I/O driver for reading data.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_disable_rx_data(uint8_t devno,
                                          st_memdrv_info_t * p_memdrv_info)
{
    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_disable_rx_data() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_enable
* Description  : Enables I/O driver.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*              : MEMDRV_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_enable(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    rsci_baud_t baud;
    baud.pclk = BSP_PCLKA_HZ;
    baud.rate = MEMDRV_CFG_DEV0_BR;
    /* Casting to a uint32_t type is valid. */
    if (R_RSCI_Control(rsci_handle,RSCI_CMD_CHANGE_BAUD,(void *)&baud) != RSCI_SUCCESS)
    {
        R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
        return MEMDRV_ERR_OTHER;
    }
    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_enable() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_enable_tx_data
* Description  : Enables I/O driver for writing data.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*              : MEMDRV_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_enable_tx_data(uint8_t devno,
                                         st_memdrv_info_t * p_memdrv_info)
{
    rsci_baud_t baud;
    baud.pclk = BSP_PCLKA_HZ;
    baud.rate = MEMDRV_CFG_DEV0_BR_WRITE_DATA;
    /* Casting to a uint32_t type is valid. */
    if (R_RSCI_Control(rsci_handle,RSCI_CMD_CHANGE_BAUD,(void *)&baud) != RSCI_SUCCESS)
    {
        R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
        return MEMDRV_ERR_OTHER;
    }

    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_enable_tx_data() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_enable_rx_data
* Description  : Enables I/O driver for reading data.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*              : MEMDRV_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_enable_rx_data(uint8_t devno,
                                         st_memdrv_info_t * p_memdrv_info)
{
    rsci_baud_t baud;
    baud.pclk = BSP_PCLKA_HZ;
    baud.rate = MEMDRV_CFG_DEV0_BR_READ_DATA;
    /* Casting to a uint32_t type is valid. */
    if (R_RSCI_Control(rsci_handle, RSCI_CMD_CHANGE_BAUD, (void *)&baud) != RSCI_SUCCESS)
    {
        R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
        return MEMDRV_ERR_OTHER;
    }

    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_enable_rx_data() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_tx
* Description  : Transmits data for command and status register.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*              : MEMDRV_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_tx(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    rsci_err_t   ret_drv = RSCI_SUCCESS;
    uint8_t channel = r_memdrv_get_drv_ch(devno);

    transfer_busy = true;
    ret_drv = R_RSCI_Send(rsci_handle, p_memdrv_info->p_data, p_memdrv_info->cnt);
    if (RSCI_SUCCESS != ret_drv)
    {
        R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
        return MEMDRV_ERR_OTHER;
    }
    
    /* Wait for transmission completion. */
    if (0 > r_memdrv_rsci_wait(channel, p_memdrv_info->cnt))
    {
        /* ---- Disable rsci transmission. ---- */
        if (RSCI_SUCCESS != R_RSCI_Close(rsci_handle))
        {
            R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
            return MEMDRV_ERR_OTHER;
        }
    }
    
    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_tx() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_tx_data
* Description  : Transmits data using the single mode.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*              : MEMDRV_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_tx_data(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    rsci_err_t   ret_drv = RSCI_SUCCESS;
    uint8_t     channel = r_memdrv_get_drv_ch(devno);
    uint32_t    cnt     = p_memdrv_info->cnt;
    uint32_t    rem_txcnt = cnt / RSCI_EXCHG_MAX_COUNT;
    uint32_t    mod_txcnt = cnt % RSCI_EXCHG_MAX_COUNT;

    transfer_busy = true;
    /* Turn 32 digits into 16 digits */
    if (rem_txcnt >= 1)
    {
        /* WAIT_LOOP */
        while(rem_txcnt)
        {
            ret_drv = R_RSCI_Send(rsci_handle, p_memdrv_info->p_data, RSCI_EXCHG_MAX_COUNT);
            if (RSCI_SUCCESS != ret_drv)
            {
                return MEMDRV_ERR_OTHER;
            }
            p_memdrv_info->p_data = (uint8_t *)(p_memdrv_info->p_data + RSCI_EXCHG_MAX_COUNT);
            rem_txcnt--;
        }
        ret_drv = R_RSCI_Send(rsci_handle, p_memdrv_info->p_data, mod_txcnt);
    }
    else
    {
        ret_drv = R_RSCI_Send(rsci_handle, p_memdrv_info->p_data, cnt);
    }

    if (RSCI_SUCCESS != ret_drv)
    {
        R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
        return MEMDRV_ERR_OTHER;
    }
    
    /* Wait for transmission completion. */
    if (0 > r_memdrv_rsci_wait(channel, p_memdrv_info->cnt))
    {
        /* ---- Disable rsci transmission. ---- */
        if (RSCI_SUCCESS != R_RSCI_Close(rsci_handle))
        {
            R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
            return MEMDRV_ERR_OTHER;
        }
    }
    
    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_tx_data() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_rx
* Description  : Receives data for status register and Read ID.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*              : MEMDRV_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_rx(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    rsci_err_t   ret_drv = RSCI_SUCCESS;
    uint8_t channel = r_memdrv_get_drv_ch(devno);
    
    transfer_busy = true;
    ret_drv = R_RSCI_Receive(rsci_handle, p_memdrv_info->p_data, p_memdrv_info->cnt);
    if (RSCI_SUCCESS != ret_drv)
    {
        R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
        return MEMDRV_ERR_OTHER;
    }
    
    /* Wait for transmission completion. */
    if (0 > r_memdrv_rsci_wait(channel, p_memdrv_info->cnt))
    {
        /* ---- Disable rsci transmission. ---- */
        if (RSCI_SUCCESS != R_RSCI_Close(rsci_handle))
        {
            R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
            return MEMDRV_ERR_OTHER;
        }
    }
    
    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_rx() */

/************************************************************************************************
* Function Name: r_memdrv_rsci_rx_data
* Description  : Receives data using the single mode.
* Arguments    : uint8_t         devno                  ;   Device No. (MEMDRV_DEVn)
*              : st_memdrv_info_t * p_memdrv_info
*              :    uint32_t    cnt                     ;   Number of bytes
*              :    uint8_t   * p_data                  ;   Buffer pointer
*              :    uint8_t     io_mode                 ;   Single/Dual/Quad
*              :    uint8_t     rsv[3]                  ;   Reserved
* Return Value : MEMDRV_SUCCESS                         ;   Successful operation
*              : MEMDRV_ERR_OTHER                       ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
memdrv_err_t r_memdrv_rsci_rx_data(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    rsci_err_t   ret_drv = RSCI_SUCCESS;
    uint8_t     channel = r_memdrv_get_drv_ch(devno);
    uint32_t    cnt     = p_memdrv_info->cnt;
    uint32_t    rem_rxcnt = cnt / RSCI_EXCHG_MAX_COUNT;
    uint32_t    mod_rxcnt = cnt % RSCI_EXCHG_MAX_COUNT;
    
    transfer_busy = true;
    /* Turn 32 digits into 16 digits */
    if (rem_rxcnt >= 1)
    {
        /* WAIT_LOOP */
        while(rem_rxcnt)
        {
            ret_drv = R_RSCI_Receive(rsci_handle, p_memdrv_info->p_data, RSCI_EXCHG_MAX_COUNT);
            if (RSCI_SUCCESS != ret_drv)
            {
                return MEMDRV_ERR_OTHER;
            }
            p_memdrv_info->p_data = (uint8_t *)(p_memdrv_info->p_data + RSCI_EXCHG_MAX_COUNT);
            rem_rxcnt--;
        }
        ret_drv = R_RSCI_Receive(rsci_handle, p_memdrv_info->p_data, mod_rxcnt);
    }
    else
    {
        ret_drv = R_RSCI_Receive(rsci_handle, p_memdrv_info->p_data, cnt);
    }
    if (RSCI_SUCCESS != ret_drv)
    {
        R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
        return MEMDRV_ERR_OTHER;
    }

    /* Wait for transmission completion. */
    if (0 > r_memdrv_rsci_wait(channel, p_memdrv_info->cnt))
    {
        /* ---- Disable rsci transmission. ---- */
        if (RSCI_SUCCESS != R_RSCI_Close(rsci_handle))
        {
            R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
            return MEMDRV_ERR_OTHER;
        }
    }
    
    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_rx_data() */

/*******************************************************************************
* Function Name: r_memdrv_rsci_1ms_interval
* Description  : 1ms Interval Timer call function.
* Arguments    : none
* Return Value : MEMDRV_SUCCESS -
*                    Successful operation
*******************************************************************************/
memdrv_err_t r_memdrv_rsci_1ms_interval(void)
{
    uint8_t channel = 0;
    /* WAIT_LOOP */
    for (channel = 0; channel < RSCI_MAX_CHANNELS; channel++)
    {
        if (memdrv_rsci_timer_cnt_out[channel][RSCI_TIMER_CH_FLG] != 0)
        {
            memdrv_rsci_timer_cnt_out[channel][RSCI_TIMER_CH_COUNT]++;
        }
    }

    return MEMDRV_SUCCESS;
} /* End of function r_memdrv_rsci_1ms_interval() */

/*******************************************************************************
* Function Name: r_memdrv_rsci_start_timer
* Description  : Sets timer for checking timeout and start timer.
* Arguments    : channel -
*                    Which channel to use
*              : msec -
*                    timeout(msec order)
* Return Value : none
*******************************************************************************/
static void r_memdrv_rsci_start_timer(uint8_t channel, uint32_t msec)
{
    memdrv_rsci_timer_cnt_out[channel][RSCI_TIMER_CH_FLG] = 1;
    memdrv_rsci_timer_cnt_out[channel][RSCI_TIMER_CH_COUNT] = 0;
    memdrv_rsci_timer_cnt_out[channel][RSCI_TIMER_CH_MAX_COUNT] = (uint32_t)(msec);
} /* End of function r_memdrv_rsci_start_timer() */

/*******************************************************************************
* Function Name: r_memdrv_rsci_check_timer
* Description  : Checks timeout to set r_memdrv_rsci_start_timer function.
*              : If timeout,return MEMDRV_ERR_HARD. 
*              : In the case of others, return MEMDRV_SUCCESS.
* Arguments    : channel -
*                    Which channel to use
* Return Value : MEMDRV_SUCCESS -
*                    Successful operation
*                MEMDRV_ERR_HARD -
*                    Hardware error
*******************************************************************************/
static memdrv_err_t r_memdrv_rsci_check_timer(uint8_t channel)
{
    memdrv_err_t ret = MEMDRV_SUCCESS;
    uint32_t memdrv_rsci_timer_cnt_out1 = memdrv_rsci_timer_cnt_out[channel][RSCI_TIMER_CH_COUNT];
    uint32_t memdrv_rsci_timer_cnt_out2 = memdrv_rsci_timer_cnt_out[channel][RSCI_TIMER_CH_MAX_COUNT];

    /* ---- Check compare ---- */
    if (memdrv_rsci_timer_cnt_out1 >= memdrv_rsci_timer_cnt_out2)
    {
        ret = MEMDRV_ERR_HARD;
    }
    else
    {
        ret = MEMDRV_SUCCESS;
    }

    return ret;
} /* End of function r_memdrv_rsci_check_timer() */

/*******************************************************************************
* Function Name: r_memdrv_rsci_end_timer
* Description  : Stops timer to set r_memdrv_rsci_start_timer function.
* Arguments    : channel -
*                    Which channel to use
* Return Value : none
*******************************************************************************/
static void r_memdrv_rsci_end_timer(uint8_t channel)
{
    memdrv_rsci_timer_cnt_out[channel][RSCI_TIMER_CH_FLG] = 0;
} /* End of function r_memdrv_rsci_end_timer() */

/*******************************************************************************
* Function Name: r_memdrv_rsci_wait
* Description  : Waits for reception completion.
* Arguments    : channel -
*                    Which channel to use
*                size -
*                    Size of data
* Return Value : MEMDRV_SUCCESS -
*                    Successful operation
*                MEMDRV_ERR_HARD -
*                    Hardware error
*******************************************************************************/
static memdrv_err_t r_memdrv_rsci_wait(uint8_t channel, uint32_t size)
{
    memdrv_err_t    ret  = MEMDRV_SUCCESS;
    uint32_t               time = RSCI_TIMER_MIN_TIME;     // 100ms

    /* ---- Check DMAC/DTC transfer end.  --- */
    /* Timeout value depends on transfer size. 
       Minimum time is 100ms. When the data count exceeds 10 sectors (1 sector = 512 bytes),
       increase 10ms time for 1 sector increase.*/
    if ((RSCI_SECTOR_SIZE * 10) < size)
    {
        time = (time + (((size / RSCI_SECTOR_SIZE) - 10) * 10));
        if (0x0fffffff < time)
        {
            time = 0x0fffffff;
        }
    }

    /* Start timer. */
    r_memdrv_rsci_start_timer(channel, time);
    /* WAIT_LOOP */
    while (1)
    {
        /* Check timeout. */
        if (MEMDRV_ERR_HARD == r_memdrv_rsci_check_timer(channel))
        {
            ret = MEMDRV_ERR_HARD;
            break;
        }
        if (false == transfer_busy)
        {
            break;
        }
    }

    r_memdrv_rsci_end_timer(channel);

    return ret;
} /* End of function r_memdrv_rsci_wait() */

/*****************************************************************************
* Function Name: r_memdrv_rsci_callback
* Description  : This is an example of an rsci callback function.
* Arguments    : p_data - pointer to rsci event code data.
* Return Value : None
******************************************************************************/
static void r_memdrv_rsci_callback(void *p_data)
{
    transfer_busy = false;
} /* End of function r_memdrv_rsci_callback() */

/*****************************************************************************
* Function Name: rsci_init_ports
* Description  : This function initializes the port pins associated with
*                RSCI channel using the macros defined in iodefine.h.
* Arguments    : None
* Return Value : None
******************************************************************************/
static void rsci_init_ports(void)
{
#if (((MEMDRV_CFG_DEV0_INCLUDED == 1) && (MEMDRV_CFG_DEV0_MODE_DRVR & MEMDRV_DRVR_RX_FIT_RSCI_SPI) && \
      (MEMDRV_CFG_DEV0_MODE_DRVR_CH == MEMDRV_DRVR_CH8)) || ((MEMDRV_CFG_DEV1_INCLUDED == 1)      && \
      (MEMDRV_CFG_DEV1_MODE_DRVR & MEMDRV_DRVR_RX_FIT_RSCI_SPI) && (MEMDRV_CFG_DEV1_MODE_DRVR_CH == MEMDRV_DRVR_CH8)))
    R_RSCI_PinSet_RSCI8();
#endif
#if (((MEMDRV_CFG_DEV0_INCLUDED == 1) && (MEMDRV_CFG_DEV0_MODE_DRVR & MEMDRV_DRVR_RX_FIT_RSCI_SPI) && \
      (MEMDRV_CFG_DEV0_MODE_DRVR_CH == MEMDRV_DRVR_CH9)) || ((MEMDRV_CFG_DEV1_INCLUDED == 1)      && \
      (MEMDRV_CFG_DEV1_MODE_DRVR & MEMDRV_DRVR_RX_FIT_RSCI_SPI) && (MEMDRV_CFG_DEV1_MODE_DRVR_CH == MEMDRV_DRVR_CH9)))
    R_RSCI_PinSet_RSCI9();
#endif
#if (((MEMDRV_CFG_DEV0_INCLUDED == 1) && (MEMDRV_CFG_DEV0_MODE_DRVR & MEMDRV_DRVR_RX_FIT_RSCI_SPI) && \
      (MEMDRV_CFG_DEV0_MODE_DRVR_CH == MEMDRV_DRVR_CH10)) || ((MEMDRV_CFG_DEV1_INCLUDED == 1)     && \
      (MEMDRV_CFG_DEV1_MODE_DRVR & MEMDRV_DRVR_RX_FIT_RSCI_SPI) && (MEMDRV_CFG_DEV1_MODE_DRVR_CH == MEMDRV_DRVR_CH10)))
    R_RSCI_PinSet_RSCI10();
#endif
#if (((MEMDRV_CFG_DEV0_INCLUDED == 1) && (MEMDRV_CFG_DEV0_MODE_DRVR & MEMDRV_DRVR_RX_FIT_RSCI_SPI) && \
      (MEMDRV_CFG_DEV0_MODE_DRVR_CH == MEMDRV_DRVR_CH11)) || ((MEMDRV_CFG_DEV1_INCLUDED == 1)     && \
      (MEMDRV_CFG_DEV1_MODE_DRVR & MEMDRV_DRVR_RX_FIT_RSCI_SPI) && (MEMDRV_CFG_DEV1_MODE_DRVR_CH == MEMDRV_DRVR_CH11)))
    R_RSCI_PinSet_RSCI11();
#endif
} /* End of function rsci_init_ports() */

#else
memdrv_err_t r_memdrv_rsci_open(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_open() */
memdrv_err_t r_memdrv_rsci_close(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_close() */
memdrv_err_t r_memdrv_rsci_disable(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_disable() */
memdrv_err_t r_memdrv_rsci_disable_tx_data(uint8_t devno,
                                          st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_disable_tx_data() */
memdrv_err_t r_memdrv_rsci_disable_rx_data(uint8_t devno,
                                          st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_disable_rx_data() */
memdrv_err_t r_memdrv_rsci_enable(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_enable() */
memdrv_err_t r_memdrv_rsci_enable_tx_data(uint8_t devno,
                                         st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_enable_tx_data() */
memdrv_err_t r_memdrv_rsci_enable_rx_data(uint8_t devno,
                                         st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_enable_rx_data() */
memdrv_err_t r_memdrv_rsci_tx(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_tx() */
memdrv_err_t r_memdrv_rsci_tx_data(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_tx_data() */
memdrv_err_t r_memdrv_rsci_rx(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_rx() */
memdrv_err_t r_memdrv_rsci_rx_data(uint8_t devno, st_memdrv_info_t * p_memdrv_info)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_rx_data() */
memdrv_err_t r_memdrv_rsci_1ms_interval(void)
{
    R_MEMDRV_Log(MEMDRV_DEBUG_ERR_ID, (uint32_t)MEMDRV_ERR_SUB, __LINE__);
    return MEMDRV_ERR_OTHER;
} /* End of function r_memdrv_rsci_1ms_interval() */
#endif  /* ((MEMDRV_CFG_DEV0_INCLUDED == 1) && (MEMDRV_CFG_DEV0_MODE_DRVR == MEMDRV_DRVR_RX_FIT_RSCI_SPI)) || \
           ((MEMDRV_CFG_DEV1_INCLUDED == 1) && (MEMDRV_CFG_DEV1_MODE_DRVR == MEMDRV_DRVR_RX_FIT_RSCI_SPI)) */

/* End of File */
