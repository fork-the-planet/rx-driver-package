/*
* Copyright (c) 2020 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/*******************************************************************************************************************//**
 * @addtogroup RM_FS2012
 * @{
 **********************************************************************************************************************/

#ifndef RM_FS2012_H
#define RM_FS2012_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_fsxxxx_api.h"

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "r_fs2012_rx_config.h"
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
 #include "r_fs2012_rl_config.h"
#else
 #include "rm_fs2012_cfg.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER
#endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** FS2012 Control Block */
typedef struct rm_fs2012_instance_ctrl
{
    uint32_t                    open;                 ///< Open flag
    rm_fsxxxx_cfg_t const     * p_cfg;                ///< Pointer to FS2012 Configuration
    rm_comms_instance_t const * p_comms_i2c_instance; ///< Pointer of I2C Communications Middleware instance structure
    void const                * p_context;            ///< Pointer to the user-provided context

    /* Pointer to callback and optional working memory */
    void (* p_callback)(rm_fsxxxx_callback_args_t * p_args);
} rm_fs2012_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern rm_fsxxxx_api_t const g_fsxxxx_on_fs2012;

/** @endcond */

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t RM_FS2012_Open(rm_fsxxxx_ctrl_t * const p_api_ctrl, rm_fsxxxx_cfg_t const * const p_cfg);
fsp_err_t RM_FS2012_Close(rm_fsxxxx_ctrl_t * const p_api_ctrl);
fsp_err_t RM_FS2012_Read(rm_fsxxxx_ctrl_t * const p_api_ctrl, rm_fsxxxx_raw_data_t * const p_raw_data);
fsp_err_t RM_FS2012_DataCalculate(rm_fsxxxx_ctrl_t * const     p_api_ctrl,
                                  rm_fsxxxx_raw_data_t * const p_raw_data,
                                  rm_fsxxxx_data_t * const     p_fs2012_data);

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
#else

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_FOOTER
#endif

#endif                                 /* RM_FS2012_H_*/

/*******************************************************************************************************************//**
 * @} (end addtogroup RM_FS2012)
 **********************************************************************************************************************/
