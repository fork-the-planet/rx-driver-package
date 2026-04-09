/*
* Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_rai_data_shipper.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

fsp_err_t rm_rai_data_shipper_crc_open       (rai_data_shipper_ctrl_t          * const p_api_ctrl);
fsp_err_t rm_rai_data_shipper_crc_close      (rai_data_shipper_ctrl_t          * const p_api_ctrl);
fsp_err_t rm_rai_data_shipper_crc_calculate  (rai_data_shipper_ctrl_t          * const p_api_ctrl,
                                              crc_input_t                      * const p_crc_input, 
                                              uint32_t                         *       calculatedValue);
fsp_err_t rm_rai_data_shipper_crc_initialize (rai_data_shipper_ctrl_t          * const p_api_ctrl);

/*******************************************************************************************************************//**
 * Open CRC module.
 *
 * @retval FSP_SUCCESS                  Successfully configured.
 * @retval FSP_ERR_UNSUPPORTED          CRC is unsupported.
 ***********************************************************************************************************************/
fsp_err_t rm_rai_data_shipper_crc_open(rai_data_shipper_ctrl_t * const p_api_ctrl)
{
#if RM_RAI_DATA_SHIPPER_CFG_CRC_ENABLE
    return FSP_SUCCESS;
#else
    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Close CRC module.
 *
 * @retval FSP_SUCCESS                  Successfully configured.
 * @retval FSP_ERR_UNSUPPORTED          CRC is unsupported.
 ***********************************************************************************************************************/
fsp_err_t rm_rai_data_shipper_crc_close(rai_data_shipper_ctrl_t * const p_api_ctrl)
{
#if RM_RAI_DATA_SHIPPER_CFG_CRC_ENABLE
    return FSP_SUCCESS;
#else
    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Calculation for CRC.
 *
 * @retval FSP_SUCCESS                  Successfully configured.
 * @retval FSP_ERR_UNSUPPORTED          CRC is unsupported.
 ***********************************************************************************************************************/
fsp_err_t rm_rai_data_shipper_crc_calculate  (rai_data_shipper_ctrl_t          * const p_api_ctrl,
                                              crc_input_t                      * const p_crc_input, 
                                              uint32_t                         *       calculatedValue)
{
#if RM_RAI_DATA_SHIPPER_CFG_CRC_ENABLE
    int16_t     i;
    uint8_t    *p;
    rai_data_shipper_instance_ctrl_t * p_ctrl = (rai_data_shipper_instance_ctrl_t *) p_api_ctrl;

    /* Input values */
    p = (uint8_t *)p_crc_input->p_input_buffer;
    for(i = 0; i < p_crc_input->num_bytes; ++i)
    {
        p_ctrl->p_cfg->p_crc->p_api->inputData(*p);
        ++p;
    }

    /* Get calcualted value */
    p_ctrl->p_cfg->p_crc->p_api->getResult(calculatedValue);

    return FSP_SUCCESS;
#else
    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Initialize for CRC.
 *
 * @retval FSP_SUCCESS                  Successfully configured.
 * @retval FSP_ERR_UNSUPPORTED          CRC is unsupported.
 ***********************************************************************************************************************/
fsp_err_t rm_rai_data_shipper_crc_initialize (rai_data_shipper_ctrl_t          * const p_api_ctrl)
{
#if RM_RAI_DATA_SHIPPER_CFG_CRC_ENABLE
    rai_data_shipper_instance_ctrl_t * p_ctrl = (rai_data_shipper_instance_ctrl_t *) p_api_ctrl;

    /* Initialize */
    p_ctrl->p_cfg->p_crc->p_api->setCrc8();

    return FSP_SUCCESS;
#else
    return FSP_ERR_UNSUPPORTED;
#endif
}
