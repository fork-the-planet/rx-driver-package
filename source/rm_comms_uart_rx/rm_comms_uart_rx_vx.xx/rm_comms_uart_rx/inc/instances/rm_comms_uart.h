/*
* Copyright (c) 2020-2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*******************************************************************************************************************//**
 * @addtogroup RM_COMMS_UART
 * @{
 **********************************************************************************************************************/

#ifndef RM_COMMS_UART_H
#define RM_COMMS_UART_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_comms_uart_api.h"

#if   defined(__CCRX__) || defined(__ICCRX__)   || defined(__RX__)
 #include "rm_comms_uart_r_uart_api_complement.h"
 #include "rm_comms_uart_rx_config.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include "rm_comms_uart_rl_config.h"
#else
 #include "rm_comms_uart_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* UART bus configuration */
typedef struct st_rm_comms_uart_extended_cfg
{
#if BSP_CFG_RTOS
    void * const   p_tx_mutex;         ///< Lock device for writing.
    void * const   p_rx_mutex;         ///< Lock device for reading.
    uint32_t const mutex_timeout;      ///< Timeout for locking device.
    void * const   p_tx_semaphore;     ///< Block write operations. If this is NULL then operations will be non-blocking and require a callback.
    void * const   p_rx_semaphore;     ///< Block read operations. If this is NULL then operations will be non-blocking and require a callback.
#endif
    uart_instance_t const * p_uart;    ///< Pointer to UART instance.  for RA
    void const   * p_driver_instance;  ///< Pointer to UART HAL interface to be used in the framework for RX, RL78  
} rm_comms_uart_extended_cfg_t;

/** Communications middleware control structure. */
typedef struct st_rm_comms_uart_instance_ctrl
{
    uint32_t                             open;              ///< Open flag.
    rm_comms_uart_cfg_t const               * p_cfg;             ///< Middleware configuration.
    rm_comms_uart_extended_cfg_t const * p_extend;          ///< Pointer to extended configuration structure

    void (* p_callback)(rm_comms_uart_callback_args_t * p_args); ///< Pointer to callback that is called when a uart_event_t occurs.
    void const * p_context;                                 ///< Pointer to context passed into callback function
} rm_comms_uart_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

extern rm_comms_uart_api_t const g_comms_on_comms_uart;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_COMMS_UART_Open(rm_comms_uart_ctrl_t * const p_api_ctrl, rm_comms_uart_cfg_t const * const p_cfg);
fsp_err_t RM_COMMS_UART_Close(rm_comms_uart_ctrl_t * const p_api_ctrl);
fsp_err_t RM_COMMS_UART_Read(rm_comms_uart_ctrl_t * const p_api_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t RM_COMMS_UART_Write(rm_comms_uart_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint32_t const bytes);
fsp_err_t RM_COMMS_UART_WriteRead(rm_comms_uart_ctrl_t * const            p_api_ctrl,
                                  rm_comms_uart_write_read_params_t const write_read_params);
fsp_err_t RM_COMMS_UART_CallbackSet(rm_comms_uart_ctrl_t * const p_api_ctrl,
                                    void (                * p_callback)(rm_comms_uart_callback_args_t *),
                                    void const * const      p_context);

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_COMMS_UART_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_COMMS_UART)
 **********************************************************************************************************************/
