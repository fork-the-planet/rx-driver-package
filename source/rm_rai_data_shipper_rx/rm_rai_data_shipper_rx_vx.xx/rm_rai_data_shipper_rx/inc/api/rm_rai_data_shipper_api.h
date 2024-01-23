/***********************************************************************************************************************
 * Copyright [2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef RM_RAI_DATA_SHIPPER_API_H
#define RM_RAI_DATA_SHIPPER_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_INTERFACES
 * @defgroup RM_RAI_DATA_SHIPPER_API Data Shipper Interface
 * @brief Interface for RAI Data Shipper
 *
 * @section RM_RAI_DATA_SHIPPER_API_SUMMARY Summary
 * The rai data shipper interface provides multiple communication methods.
 *
 * Implemented by:
 * - @ref RM_RAI_DATA_SHIPPER
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#if   defined(__CCRX__) || defined(__ICCRX__)   || defined(__RX__)
 #include "platform.h"
 #include "rm_rai_data_shipper_r_crc_api_complement.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include <stddef.h>
 #include <stdbool.h>
 #include "r_cg_macrodriver.h"
 #include "r_fsp_error.h"
#else
/* Includes board and MCU related header files. */
 #include "bsp_api.h"
 #include "r_crc_api.h"
#endif

#include "rm_rai_data_collector_api.h"
#include "rm_comms_uart_api.h"

#if   defined(__CCRX__) || defined(__ICCRX__)   || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Callback function parameter structure */
typedef struct st_rai_data_shipper_callback_args
{
    rm_comms_uart_event_t result;           ///< Whether data is sent successfully or not
    void const     * p_context;        ///< Pointer to the user-provided context
} rai_data_shipper_callback_args_t;

/** Data Shipper write funciton parameter structure */
typedef struct st_rai_data_shipper_write_params
{
    uint16_t  events;                                   ///< Events
    uint16_t  diagnostic_data_len;                      ///< Diagnostic data length
    uint8_t * p_diagnostic_data;                        ///< Pointer to diagnostic data
    rai_data_collector_callback_args_t * p_sensor_data; ///< Pointer to sensor data info
} rai_data_shipper_write_params_t;

/** RAI Data Shipper general configuration  */
typedef struct st_rai_data_shipper_cfg
{
    uint8_t divider;                                                ///< Send data on every (divider + 1) requests in case the interface bandwidth is not sufficient

    crc_instance_t const      * p_crc;                              ///< Pointer to CRC instance
    rm_comms_uart_instance_t const * p_comms;                       ///< Pointer to COMMS_UART API instance

    void const * p_context;                                         ///< Pointer to the user-provided context
    void (* p_callback)(rai_data_shipper_callback_args_t * p_args); ///< Pointer to the callback function on data sent or error
} rai_data_shipper_cfg_t;

/** Data Shipper control block.  Allocate an instance specific control block to pass into the Data Shipper API calls.
 * @par Implemented as
 * - @ref rai_data_shipper_instance_ctrl_t
 */
typedef void rai_data_shipper_ctrl_t;

/** RAI Data Shipper interface API. */
typedef struct st_rai_data_shipper_api
{
    /** Initialize Data Shipper module instance.
     * @par Implemented as
     * - @ref RM_RAI_DATA_SHIPPER_Open()
     *
     * @note To reopen after calling this function, call @ref rai_data_shipper_api_t::close first.
     * @param[in]  p_ctrl  Pointer to control handle structure
     * @param[in]  p_cfg   Pointer to configuration structure
     */
    fsp_err_t (* open)(rai_data_shipper_ctrl_t * const p_ctrl, rai_data_shipper_cfg_t const * const p_cfg);

    /** Read data.
     * @par Implemented as
     * - @ref RM_RAI_DATA_SHIPPER_Read()
     *
     * @param[in]  p_ctrl   Pointer to control structure.
     * @param[in]  p_buf    Pointer to the location to store read data.
     * @param[in]  buf_len  Number of bytes to read.
     */
    fsp_err_t (* read)(rai_data_shipper_ctrl_t * const p_api_ctrl, void * const p_buf, uint32_t * const buf_len);

    /** Write data.
     * @par Implemented as
     * - @ref RM_RAI_DATA_SHIPPER_Write()
     *
     * @param[in]  p_ctrl           Pointer to control structure.
     * @param[in]  write_params     Pointer to write parameters structure
     */
    fsp_err_t (* write)(rai_data_shipper_ctrl_t * const         p_api_ctrl,
                        rai_data_shipper_write_params_t const * p_write_params);

    /** Close the specified Data Shipper module instance.
     * @par Implemented as
     * - @ref RM_RAI_DATA_SHIPPER_Close()
     *
     * @param[in]  p_ctrl   Pointer to control handle structure
     */
    fsp_err_t (* close)(rai_data_shipper_ctrl_t * const p_ctrl);
} rai_data_shipper_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rai_data_shipper_instance
{
    rai_data_shipper_ctrl_t      * p_ctrl; ///< Pointer to the control structure for this instance
    rai_data_shipper_cfg_t const * p_cfg;  ///< Pointer to the configuration structure for this instance
    rai_data_shipper_api_t const * p_api;  ///< Pointer to the API structure for this instance
} rai_data_shipper_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup RM_RAI_DATA_SHIPPER_API)
 **********************************************************************************************************************/

#if   defined(__CCRX__) || defined(__ICCRX__)   || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif
