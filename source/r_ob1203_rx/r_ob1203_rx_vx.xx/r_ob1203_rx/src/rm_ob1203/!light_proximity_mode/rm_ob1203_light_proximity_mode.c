/*
* Copyright (c) 2021 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
 

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "r_ob1203_if.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include "r_ob1203_if.h"
#else
 #define RM_OB1203_LIGHT_PROX_MODE_ENABLE    (1)
#endif

#if RM_OB1203_LIGHT_PROX_MODE_ENABLE
 #include "rm_ob1203.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/* Definitions of Timeout */
#define RM_OB1203_TIMEOUT                      (100)

/* Definitions of Command */
 #define RM_OB1203_COMMAND_MEASUREMENT_START    (0x01)
 #define RM_OB1203_COMMAND_INTERRUPT_ENABLE     (0x01)

/* Definitions of Register address */
 #define RM_OB1203_REG_ADDR_LS_CLEAR_DATA_0     (0x04) // LS Clear measurement data, LSB
 #define RM_OB1203_REG_ADDR_LS_GREEN_DATA_0     (0x07) // LS Green/LS measurement data, LSB
 #define RM_OB1203_REG_ADDR_LS_BLUE_DATA_0      (0x0A) // LS Blue measurement data, LSB
 #define RM_OB1203_REG_ADDR_LS_RED_DATA_0       (0x0D) // LS Red measurement data, LSB
 #define RM_OB1203_REG_ADDR_COMP_DATA_0         (0x10) // LS Comp measurement data, LSB
 #define RM_OB1203_REG_ADDR_LS_RES_PERIOD       (0x22) // LS resolution and measurement period setting
 #define RM_OB1203_REG_ADDR_LS_GAIN             (0x23) // LS analog gain range setting
 #define RM_OB1203_REG_ADDR_LS_THRES_UP_0       (0x24) // LS interrupt upper threshold, LSB
 #define RM_OB1203_REG_ADDR_PS_DATA_0           (0x02) // PS measurement data, LSB
 #define RM_OB1203_REG_ADDR_PS_LED_CURR_0       (0x17) // PS LED current, LSB
 #define RM_OB1203_REG_ADDR_PS_CAN_PULSES       (0x19) // PS analog cancellation level and pulse setting
 #define RM_OB1203_REG_ADDR_PS_PWIDTH_PERIOD    (0x1A) // PS pulse width and measurement period
 #define RM_OB1203_REG_ADDR_PS_CAN_DIG_0        (0x1B) // PS digital cancellation level setting, LSB
 #define RM_OB1203_REG_ADDR_PS_MOV_AVG_HYS      (0x1D) // PS moving average and hysteresis configuration
 #define RM_OB1203_REG_ADDR_PS_THRES_UP_0       (0x1E) // PS interrupt upper threshold, LSB

/* Definitions of Mask */
 #define RM_OB1203_MASK_PERSIST                 (0x0F)
 #define RM_OB1203_MASK_DATA                    (0x0F)
 #define RM_OB1203_MASK_LIGHT_THRESHOLD         (0x000FFFFF)
 #define RM_OB1203_MASK_LED_CURRENT             (0x03FF)
 #define RM_OB1203_MASK_8BITS                   (0xFF)
 #define RM_OB1203_MASK_HYSTERESIS              (0x7F)

/* Definitions of Calculation */
 #define RM_OB1203_MAX_NUM_LIGHT_SOURCE         (5)

/**********************************************************************************************************************
 * Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global functions
 *********************************************************************************************************************/
extern fsp_err_t rm_ob1203_read(rm_ob1203_ctrl_t * const p_api_ctrl, rm_comms_write_read_params_t write_read_params);
extern fsp_err_t rm_ob1203_write(rm_ob1203_ctrl_t * const p_api_ctrl, uint8_t * const p_src, uint8_t const bytes);
extern fsp_err_t rm_ob1203_main_ctrl_register_write(rm_ob1203_ctrl_t * const p_api_ctrl,
                                                    uint8_t const            main_ctrl_0,
                                                    uint8_t const            main_ctrl_1);
extern fsp_err_t rm_ob1203_int_cfg_register_write(rm_ob1203_ctrl_t * const p_api_ctrl,
                                                  uint8_t const            int_cfg_0,
                                                  uint8_t const            int_cfg_1,
                                                  uint8_t const            int_pst);
extern fsp_err_t rm_ob1203_ppg_ps_gain_register_write(rm_ob1203_ctrl_t * const p_api_ctrl, uint8_t const ppg_ps_gain);
extern fsp_err_t rm_ob1203_ppg_ps_cfg_register_write(rm_ob1203_ctrl_t * const p_api_ctrl, uint8_t const ppg_ps_cfg);
extern fsp_err_t rm_ob1203_all_interrupt_bits_clear(rm_ob1203_ctrl_t * const p_api_ctrl);
extern fsp_err_t rm_ob1203_delay_ms(rm_ob1203_ctrl_t * const p_ctrl, uint32_t const delay_ms);

 #if BSP_CFG_RTOS
extern fsp_err_t rm_ob1203_os_semaphore_acquire(rm_ob1203_semaphore_t const * p_semaphore, uint32_t const timeout);

 #endif

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_open(rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_cfg_t const * const p_cfg);
static fsp_err_t rm_ob1203_light_prox_close(rm_ob1203_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_ob1203_light_prox_measurement_start(rm_ob1203_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_ob1203_light_prox_measurement_stop(rm_ob1203_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_ob1203_light_prox_light_read(rm_ob1203_ctrl_t * const     p_api_ctrl,
                                                 rm_ob1203_raw_data_t * const p_raw_data,
                                                 rm_ob1203_light_data_type_t  type);
static fsp_err_t rm_ob1203_light_prox_light_data_calculate(rm_ob1203_ctrl_t * const       p_api_ctrl,
                                                           rm_ob1203_raw_data_t * const   p_raw_data,
                                                           rm_ob1203_light_data_t * const p_ob1203_data);
static fsp_err_t rm_ob1203_light_prox_prox_read(rm_ob1203_ctrl_t * const     p_api_ctrl,
                                                rm_ob1203_raw_data_t * const p_raw_data);
static fsp_err_t rm_ob1203_light_prox_prox_data_calculate(rm_ob1203_ctrl_t * const      p_api_ctrl,
                                                          rm_ob1203_raw_data_t * const  p_raw_data,
                                                          rm_ob1203_prox_data_t * const p_ob1203_data);
static fsp_err_t rm_ob1203_light_prox_ppg_read(rm_ob1203_ctrl_t * const     p_api_ctrl,
                                               rm_ob1203_raw_data_t * const p_raw_data,
                                               uint8_t const                number_of_samples);
static fsp_err_t rm_ob1203_light_prox_ppg_data_calculate(rm_ob1203_ctrl_t * const     p_api_ctrl,
                                                         rm_ob1203_raw_data_t * const p_raw_data,
                                                         rm_ob1203_ppg_data_t * const p_ob1203_data);
static fsp_err_t rm_ob1203_light_prox_gain_set(rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_gain_t const gain);
static fsp_err_t rm_ob1203_light_prox_led_current_set(rm_ob1203_ctrl_t * const      p_api_ctrl,
                                                      rm_ob1203_led_current_t const led_current);
static fsp_err_t rm_ob1203_light_prox_device_interrupt_cfg_set(rm_ob1203_ctrl_t * const               p_api_ctrl,
                                                               rm_ob1203_device_interrupt_cfg_t const interrupt_cfg);
static fsp_err_t rm_ob1203_light_prox_fifo_info_get(rm_ob1203_ctrl_t * const      p_api_ctrl,
                                                    rm_ob1203_fifo_info_t * const p_fifo_info);
static fsp_err_t rm_ob1203_light_prox_device_status_get(rm_ob1203_ctrl_t * const          p_api_ctrl,
                                                        rm_ob1203_device_status_t * const p_status);

static fsp_err_t rm_ob1203_light_configuration(rm_ob1203_ctrl_t * const p_api_ctrl);
static fsp_err_t rm_ob1203_prox_configuration(rm_ob1203_ctrl_t * const p_api_ctrl);

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
rm_ob1203_api_t const g_ob1203_on_ob1203_light_proximity =
{
    .open                  = rm_ob1203_light_prox_open,
    .close                 = rm_ob1203_light_prox_close,
    .measurementStart      = rm_ob1203_light_prox_measurement_start,
    .measurementStop       = rm_ob1203_light_prox_measurement_stop,
    .lightRead             = rm_ob1203_light_prox_light_read,
    .lightDataCalculate    = rm_ob1203_light_prox_light_data_calculate,
    .proxRead              = rm_ob1203_light_prox_prox_read,
    .proxDataCalculate     = rm_ob1203_light_prox_prox_data_calculate,
    .ppgRead               = rm_ob1203_light_prox_ppg_read,
    .ppgDataCalculate      = rm_ob1203_light_prox_ppg_data_calculate,
    .gainSet               = rm_ob1203_light_prox_gain_set,
    .ledCurrentSet         = rm_ob1203_light_prox_led_current_set,
    .deviceInterruptCfgSet = rm_ob1203_light_prox_device_interrupt_cfg_set,
    .fifoInfoGet           = rm_ob1203_light_prox_fifo_info_get,
    .deviceStatusGet       = rm_ob1203_light_prox_device_status_get,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief Configures the OB1203 Light Proximity mode.
 *
 * @retval FSP_SUCCESS              OB1203 successfully configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_open (rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint8_t int_cfg_0 = 0x00;
    uint8_t int_cfg_1 = 0x00;
    uint8_t int_pst   = 0x00;

    FSP_PARAMETER_NOT_USED(p_cfg);

    /* Light mode configuration */
    err = rm_ob1203_light_configuration(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Proximity mode configuration */
    err = rm_ob1203_prox_configuration(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set device interrupt configurations */
    if (NULL != p_ctrl->p_irq_instance)
    {
        switch (p_ctrl->p_mode->mode_irq)
        {
            case RM_OB1203_OPERATION_MODE_LIGHT:
            {
                int_cfg_0 = (uint8_t) ((uint8_t) p_ctrl->p_mode->light_interrupt_source |
                                       (uint8_t) p_ctrl->p_mode->light_interrupt_type |
                                       RM_OB1203_COMMAND_INTERRUPT_ENABLE);
                int_cfg_1 = 0x00;
                int_pst   = (uint8_t) ((p_ctrl->p_mode->light_interrupt_persist & RM_OB1203_MASK_PERSIST) << 4);
                break;
            }

            case RM_OB1203_OPERATION_MODE_PROXIMITY:
            {
                int_cfg_0 = 0x00;
                int_cfg_1 =
                    (uint8_t) ((uint8_t) p_ctrl->p_mode->prox_interrupt_type | RM_OB1203_COMMAND_INTERRUPT_ENABLE);
                int_pst = (uint8_t) (p_ctrl->p_mode->prox_interrupt_persist & RM_OB1203_MASK_PERSIST);
                break;
            }

            default:
            {
                p_ctrl->p_mode->mode_irq = RM_OB1203_OPERATION_MODE_STANDBY;
                int_cfg_0                = 0x00;
                int_cfg_1                = 0x00;
                int_pst = 0x00;
                break;
            }
        }
    }
    else
    {
        p_ctrl->p_mode->mode_irq = RM_OB1203_OPERATION_MODE_STANDBY;
        int_cfg_0                = 0x00;
        int_cfg_1                = 0x00;
        int_pst = 0x00;
    }

    err = rm_ob1203_int_cfg_register_write(p_ctrl, int_cfg_0, int_cfg_1, int_pst);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_close (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Start periodic measurements in both Light mode and Proximity mode
 *
 * @retval FSP_SUCCESS              OB1203 successfully configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_measurement_start (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint8_t main_ctrl_0;
    uint8_t main_ctrl_1;

    /* Start measurement */
    main_ctrl_0 =
        (uint8_t) ((uint8_t) p_ctrl->p_mode->light_sleep | (uint8_t) p_ctrl->p_mode->light_sensor_mode |
                   RM_OB1203_COMMAND_MEASUREMENT_START);
    main_ctrl_1 = (uint8_t) ((uint8_t) p_ctrl->p_mode->prox_sleep | RM_OB1203_COMMAND_MEASUREMENT_START);
    err         = rm_ob1203_main_ctrl_register_write(p_ctrl, main_ctrl_0, main_ctrl_1);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Stop a periodic measurement
 *
 * @retval FSP_SUCCESS              OB1203 successfully configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_measurement_stop (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
#if (BSP_CFG_RTOS == 0) && (defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__))
    uint16_t counter = 0;
#endif

    if (RM_OB1203_OPERATION_MODE_STANDBY != p_ctrl->p_mode->mode_irq)
    {
        /* Clear interrupt bits after measurement stop */
        p_ctrl->interrupt_bits_clear = true;

#if (BSP_CFG_RTOS == 0) && (defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__))
        /* Clear flag */
        p_ctrl->rx_communication_finished = false;
#endif 
    }

    /* Stop measurement */
    err = rm_ob1203_main_ctrl_register_write(p_ctrl, 0x00, 0x00);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

 #if BSP_CFG_RTOS
    if (RM_OB1203_OPERATION_MODE_STANDBY != p_ctrl->p_mode->mode_irq)
    {
        /* Acquire a semaphore */
        err = rm_ob1203_os_semaphore_acquire(p_ctrl->p_semaphore, p_ctrl->p_cfg->semaphore_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Clear all interrupt bits */
        err = rm_ob1203_all_interrupt_bits_clear(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#else
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
    if (RM_OB1203_OPERATION_MODE_STANDBY != p_ctrl->p_mode->mode_irq)
    {
        /* Wait callback */
        while(false == p_ctrl->rx_communication_finished)
        {
            rm_ob1203_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_OB1203_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Clear all interrupt bits */
        err = rm_ob1203_all_interrupt_bits_clear(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif
 #endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Reads light ADC data from OB1203 device. If device interrupt is enabled, interrupt bits are cleared after data read.
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_light_read (rm_ob1203_ctrl_t * const     p_api_ctrl,
                                                  rm_ob1203_raw_data_t * const p_raw_data,
                                                  rm_ob1203_light_data_type_t  type)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint8_t reg_addr;
    uint8_t bytes = 0;
    rm_comms_write_read_params_t write_read_params;
#if (BSP_CFG_RTOS == 0) && (defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__))
    uint16_t counter = 0;
#endif

    /* Set light data type */
    p_ctrl->p_mode->light_data_type = type;

    /* Set bytes to read. */
    if (RM_OB1203_LIGHT_DATA_TYPE_ALL != type)
    {
        bytes = 3;
    }
    else
    {
        bytes = 3 * RM_OB1203_MAX_NUM_LIGHT_SOURCE;
    }

    /* Set register address */
    switch (type)
    {
        case RM_OB1203_LIGHT_DATA_TYPE_GREEN:
        {
            reg_addr = RM_OB1203_REG_ADDR_LS_GREEN_DATA_0;
            break;
        }

        case RM_OB1203_LIGHT_DATA_TYPE_BLUE:
        {
            reg_addr = RM_OB1203_REG_ADDR_LS_BLUE_DATA_0;
            break;
        }

        case RM_OB1203_LIGHT_DATA_TYPE_RED:
        {
            reg_addr = RM_OB1203_REG_ADDR_LS_RED_DATA_0;
            break;
        }

        case RM_OB1203_LIGHT_DATA_TYPE_COMP:
        {
            reg_addr = RM_OB1203_REG_ADDR_COMP_DATA_0;
            break;
        }

        case RM_OB1203_LIGHT_DATA_TYPE_ALL:
        case RM_OB1203_LIGHT_DATA_TYPE_CLEAR:
        default:
        {
            reg_addr = RM_OB1203_REG_ADDR_LS_CLEAR_DATA_0;
            break;
        }
    }

    if (RM_OB1203_OPERATION_MODE_LIGHT == p_ctrl->p_mode->mode_irq)
    {
        /* Clear interrupt bits after data read */
        p_ctrl->interrupt_bits_clear = true;

#if (BSP_CFG_RTOS == 0) && (defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__))
        /* Clear flag */
        p_ctrl->rx_communication_finished = false;
#endif     
    }

    /* Read light data. */
    p_ctrl->register_address     = reg_addr;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = (uint8_t *) p_raw_data;
    write_read_params.dest_bytes = bytes;
    err = rm_ob1203_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

 #if BSP_CFG_RTOS
    if (RM_OB1203_OPERATION_MODE_LIGHT == p_ctrl->p_mode->mode_irq)
    {
        /* Acquire a semaphore */
        err = rm_ob1203_os_semaphore_acquire(p_ctrl->p_semaphore, p_ctrl->p_cfg->semaphore_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Clear all interrupt bits */
        err = rm_ob1203_all_interrupt_bits_clear(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#else
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
    if (RM_OB1203_OPERATION_MODE_LIGHT == p_ctrl->p_mode->mode_irq)
    {
        /* Wait callback */
        while(false == p_ctrl->rx_communication_finished)
        {
            rm_ob1203_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_OB1203_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Clear all interrupt bits */
        err = rm_ob1203_all_interrupt_bits_clear(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif
 #endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Calculate light data from raw data.
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_light_data_calculate (rm_ob1203_ctrl_t * const       p_api_ctrl,
                                                            rm_ob1203_raw_data_t * const   p_raw_data,
                                                            rm_ob1203_light_data_t * const p_ob1203_data)
{
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint8_t    i;
    uint32_t * p_light_data;

    /* Set light data */
    switch (p_ctrl->p_mode->light_data_type)
    {
        case RM_OB1203_LIGHT_DATA_TYPE_GREEN:
        {
            p_light_data = &p_ob1203_data->green_data;
            break;
        }

        case RM_OB1203_LIGHT_DATA_TYPE_BLUE:
        {
            p_light_data = &p_ob1203_data->blue_data;
            break;
        }

        case RM_OB1203_LIGHT_DATA_TYPE_RED:
        {
            p_light_data = &p_ob1203_data->red_data;
            break;
        }

        case RM_OB1203_LIGHT_DATA_TYPE_COMP:
        {
            p_light_data = &p_ob1203_data->comp_data;
            break;
        }

        case RM_OB1203_LIGHT_DATA_TYPE_CLEAR:
        case RM_OB1203_LIGHT_DATA_TYPE_ALL:
        default:
        {
            p_light_data = &p_ob1203_data->clear_data;
            break;
        }
    }

    /* Calculate light data */
    for (i = 0; i < RM_OB1203_MAX_NUM_LIGHT_SOURCE; i++)
    {
        *p_light_data =
            (uint32_t) (((p_raw_data->adc_data[3 * i + 2] & RM_OB1203_MASK_DATA) << 16) +
                        (p_raw_data->adc_data[3 * i + 1] << 8) +
                        p_raw_data->adc_data[3 * i]);

        if (RM_OB1203_LIGHT_DATA_TYPE_ALL != p_ctrl->p_mode->light_data_type)
        {
            break;
        }

        p_light_data++;
    }

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Reads proximity ADC data from OB1203 device. If device interrupt is enabled, interrupt bits are cleared after data read.
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_prox_read (rm_ob1203_ctrl_t * const     p_api_ctrl,
                                                 rm_ob1203_raw_data_t * const p_raw_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t  * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    rm_comms_write_read_params_t write_read_params;
#if (BSP_CFG_RTOS == 0) && (defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__))
    uint16_t counter = 0;
#endif

    if (RM_OB1203_OPERATION_MODE_PROXIMITY == p_ctrl->p_mode->mode_irq)
    {
        /* Clear interrupt bits after data read */
        p_ctrl->interrupt_bits_clear = true;

#if (BSP_CFG_RTOS == 0) && (defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__))
        /* Clear flag */
        p_ctrl->rx_communication_finished = false;
#endif     
    }

    /* Read proximity data. */
    p_ctrl->register_address     = RM_OB1203_REG_ADDR_PS_DATA_0;
    write_read_params.p_src      = &p_ctrl->register_address;
    write_read_params.src_bytes  = 1;
    write_read_params.p_dest     = (uint8_t *) p_raw_data;
    write_read_params.dest_bytes = 2;
    err = rm_ob1203_read(p_ctrl, write_read_params);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

 #if BSP_CFG_RTOS
    if (RM_OB1203_OPERATION_MODE_PROXIMITY == p_ctrl->p_mode->mode_irq)
    {
        /* Acquire a semaphore */
        err = rm_ob1203_os_semaphore_acquire(p_ctrl->p_semaphore, p_ctrl->p_cfg->semaphore_timeout);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Clear all interrupt bits */
        err = rm_ob1203_all_interrupt_bits_clear(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#else
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
    if (RM_OB1203_OPERATION_MODE_PROXIMITY == p_ctrl->p_mode->mode_irq)
    {
        /* Wait callback */
        while(false == p_ctrl->rx_communication_finished)
        {
            rm_ob1203_delay_ms(p_ctrl, 1);
            counter++;
            FSP_ERROR_RETURN(RM_OB1203_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
        }

        /* Clear all interrupt bits */
        err = rm_ob1203_all_interrupt_bits_clear(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }
#endif
 #endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Calculate proximity data from raw data.
 *
 * @retval FSP_SUCCESS              Successfully results are read.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_prox_data_calculate (rm_ob1203_ctrl_t * const      p_api_ctrl,
                                                           rm_ob1203_raw_data_t * const  p_raw_data,
                                                           rm_ob1203_prox_data_t * const p_ob1203_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

    /* Calculate proximity data */
    p_ob1203_data->proximity_data = (uint16_t) ((p_raw_data->adc_data[1] << 8) + p_raw_data->adc_data[0]);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_ppg_read (rm_ob1203_ctrl_t * const     p_api_ctrl,
                                                rm_ob1203_raw_data_t * const p_raw_data,
                                                uint8_t const                number_of_samples)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(number_of_samples);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_ppg_data_calculate (rm_ob1203_ctrl_t * const     p_api_ctrl,
                                                          rm_ob1203_raw_data_t * const p_raw_data,
                                                          rm_ob1203_ppg_data_t * const p_ob1203_data)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_raw_data);
    FSP_PARAMETER_NOT_USED(p_ob1203_data);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Set gains for both Light and Proximity.
 *
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_gain_set (rm_ob1203_ctrl_t * const p_api_ctrl, rm_ob1203_gain_t const gain)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
#if (BSP_CFG_RTOS == 0) && (defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__))
    uint16_t counter = 0;
#endif

    /* Set flag */
    p_ctrl->prox_gain_update = true;

#if (BSP_CFG_RTOS == 0) && (defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__))
    /* Clear flag */
    p_ctrl->rx_communication_finished = false;
#endif  

    /* Set gain */
    p_ctrl->p_mode->light_gain    = gain.light;
    p_ctrl->p_mode->ppg_prox_gain = gain.ppg_prox;

    /* Set Light mode gain */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_LS_GAIN;
    p_ctrl->buf[1] = (uint8_t) p_ctrl->p_mode->light_gain;
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

 #if BSP_CFG_RTOS

    /* Acquire a semaphore */
    err = rm_ob1203_os_semaphore_acquire(p_ctrl->p_semaphore, p_ctrl->p_cfg->semaphore_timeout);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set Proximity mode gain */
    err = rm_ob1203_ppg_ps_gain_register_write(p_ctrl, (uint8_t) p_ctrl->p_mode->ppg_prox_gain);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#else
#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
    /* Wait callback */
    while(false == p_ctrl->rx_communication_finished)
    {
        rm_ob1203_delay_ms(p_ctrl, 1);
        counter++;
        FSP_ERROR_RETURN(RM_OB1203_TIMEOUT >= counter, FSP_ERR_TIMEOUT);
    }

    /* Set Proximity mode gain */
    err = rm_ob1203_ppg_ps_gain_register_write(p_ctrl, (uint8_t) p_ctrl->p_mode->ppg_prox_gain);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif
 #endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Set current for Proximity mode.
 *
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_led_current_set (rm_ob1203_ctrl_t * const      p_api_ctrl,
                                                       rm_ob1203_led_current_t const led_current)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint16_t current_tmp;

    /* Set LED current */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_PS_LED_CURR_0;
    if (RM_OB1203_LED_IR_FIRST_RED_SECOND == p_ctrl->p_mode->led_order)
    {
        p_ctrl->p_mode->prox_led_current = led_current.ir_led & RM_OB1203_MASK_LED_CURRENT;
    }
    else
    {
        p_ctrl->p_mode->prox_led_current = led_current.red_led & RM_OB1203_MASK_LED_CURRENT;
    }

    current_tmp    = p_ctrl->p_mode->prox_led_current;
    p_ctrl->buf[1] = (uint8_t) (current_tmp & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[2] = (uint8_t) (current_tmp >> 8);
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Set device interrupt configurations.
 *
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 * @retval FSP_ERR_INVALID_MODE     Invalid mode.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_device_interrupt_cfg_set (rm_ob1203_ctrl_t * const               p_api_ctrl,
                                                                rm_ob1203_device_interrupt_cfg_t const interrupt_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint8_t int_cfg_0 = 0x00;
    uint8_t int_cfg_1 = 0x00;
    uint8_t int_pst   = 0x00;

 #if RM_OB1203_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(((RM_OB1203_OPERATION_MODE_LIGHT == interrupt_cfg.light_prox_mode) ||
                      (RM_OB1203_OPERATION_MODE_PROXIMITY == interrupt_cfg.light_prox_mode)),
                     FSP_ERR_INVALID_MODE);
 #endif

    /* Set device interrupt configurations */
    if (RM_OB1203_OPERATION_MODE_LIGHT == interrupt_cfg.light_prox_mode)
    {
        p_ctrl->p_mode->mode_irq                = RM_OB1203_OPERATION_MODE_LIGHT;
        p_ctrl->p_mode->light_interrupt_source  = interrupt_cfg.light_source;
        p_ctrl->p_mode->light_interrupt_type    = interrupt_cfg.light_type;
        p_ctrl->p_mode->light_interrupt_persist = interrupt_cfg.persist;
        int_cfg_0 = (uint8_t) ((uint8_t) p_ctrl->p_mode->light_interrupt_source |
                               (uint8_t) p_ctrl->p_mode->light_interrupt_type |
                               RM_OB1203_COMMAND_INTERRUPT_ENABLE);
        int_cfg_1 = 0x00;
        int_pst   = (uint8_t) ((p_ctrl->p_mode->light_interrupt_persist & RM_OB1203_MASK_PERSIST) << 4);
    }
    else
    {
        p_ctrl->p_mode->mode_irq               = RM_OB1203_OPERATION_MODE_PROXIMITY;
        p_ctrl->p_mode->prox_interrupt_type    = interrupt_cfg.prox_type;
        p_ctrl->p_mode->prox_interrupt_persist = interrupt_cfg.persist;
        int_cfg_0 = 0x00;
        int_cfg_1 =
            (uint8_t) ((uint8_t) p_ctrl->p_mode->prox_interrupt_type | RM_OB1203_COMMAND_INTERRUPT_ENABLE);
        int_pst = (uint8_t) (p_ctrl->p_mode->prox_interrupt_persist & RM_OB1203_MASK_PERSIST);
    }

    err = rm_ob1203_int_cfg_register_write(p_ctrl, int_cfg_0, int_cfg_1, int_pst);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_fifo_info_get (rm_ob1203_ctrl_t * const      p_api_ctrl,
                                                     rm_ob1203_fifo_info_t * const p_fifo_info)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_fifo_info);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief  Unsupported API.
 *
 * @retval FSP_ERR_UNSUPPORTED                    Operation mode is not supported.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_prox_device_status_get (rm_ob1203_ctrl_t * const          p_api_ctrl,
                                                         rm_ob1203_device_status_t * const p_status)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_status);

    return FSP_ERR_UNSUPPORTED;
}

/*******************************************************************************************************************//**
 * @brief Configures the OB1203 Light mode.
 *
 * @retval FSP_SUCCESS              OB1203 successfully configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_light_configuration (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint32_t threshold_tmp;

    /* Set gain */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_LS_GAIN;
    p_ctrl->buf[1] = (uint8_t) p_ctrl->p_mode->light_gain;
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set resolution and measurement period */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_LS_RES_PERIOD;
    p_ctrl->buf[1] = (uint8_t) p_ctrl->p_mode->light_resolution_period;
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set thresholds */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_LS_THRES_UP_0;
    threshold_tmp  = p_ctrl->p_mode->light_upper_threshold & RM_OB1203_MASK_LIGHT_THRESHOLD;
    p_ctrl->buf[1] = (uint8_t) (threshold_tmp & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[2] = (uint8_t) ((threshold_tmp >> 8) & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[3] = (uint8_t) ((threshold_tmp >> 16) & RM_OB1203_MASK_8BITS);
    threshold_tmp  = p_ctrl->p_mode->light_lower_threshold & RM_OB1203_MASK_LIGHT_THRESHOLD;
    p_ctrl->buf[4] = (uint8_t) (threshold_tmp & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[5] = (uint8_t) ((threshold_tmp >> 8) & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[6] = (uint8_t) ((threshold_tmp >> 16) & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[7] = (uint8_t) p_ctrl->p_mode->light_variance_threshold;
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 8);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Configures the OB1203 Proximity mode.
 *
 * @retval FSP_SUCCESS              OB1203 successfully configured.
 * @retval FSP_ERR_TIMEOUT          Communication is timeout.
 * @retval FSP_ERR_ABORTED          Communication is aborted.
 **********************************************************************************************************************/
static fsp_err_t rm_ob1203_prox_configuration (rm_ob1203_ctrl_t * const p_api_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ob1203_instance_ctrl_t * p_ctrl = (rm_ob1203_instance_ctrl_t *) p_api_ctrl;
    uint16_t current_tmp;

    /* Set gain */
    err = rm_ob1203_ppg_ps_gain_register_write(p_ctrl, (uint8_t) p_ctrl->p_mode->ppg_prox_gain);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set LED current */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_PS_LED_CURR_0;
    current_tmp    = p_ctrl->p_mode->prox_led_current & RM_OB1203_MASK_LED_CURRENT;
    p_ctrl->buf[1] = (uint8_t) (current_tmp & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[2] = (uint8_t) (current_tmp >> 8);
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set LED order */
    err = rm_ob1203_ppg_ps_cfg_register_write(p_ctrl, (uint8_t) p_ctrl->p_mode->led_order);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set analog cancellation and the number of LED pulses */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_PS_CAN_PULSES;
    p_ctrl->buf[1] = (uint8_t) ((uint8_t) p_ctrl->p_mode->prox_ana_can | (uint8_t) p_ctrl->p_mode->prox_num_led_pulses);
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set digital cancellation */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_PS_CAN_DIG_0;
    p_ctrl->buf[1] = (uint8_t) (p_ctrl->p_mode->prox_dig_can & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[2] = (uint8_t) (p_ctrl->p_mode->prox_dig_can >> 8);
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 3);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set pulse width and measurement period */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_PS_PWIDTH_PERIOD;
    p_ctrl->buf[1] = (uint8_t) p_ctrl->p_mode->prox_width_period;
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set moving average and hysteresis */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_PS_MOV_AVG_HYS;
    p_ctrl->buf[1] =
        (uint8_t) ((uint8_t) p_ctrl->p_mode->prox_moving_average |
                   (uint8_t) (p_ctrl->p_mode->prox_hysteresis & RM_OB1203_MASK_HYSTERESIS));
    err = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 2);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set thresholds */
    p_ctrl->buf[0] = RM_OB1203_REG_ADDR_PS_THRES_UP_0;
    p_ctrl->buf[1] = (uint8_t) (p_ctrl->p_mode->prox_upper_threshold & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[2] = (uint8_t) (p_ctrl->p_mode->prox_upper_threshold >> 8);
    p_ctrl->buf[3] = (uint8_t) (p_ctrl->p_mode->prox_lower_threshold & RM_OB1203_MASK_8BITS);
    p_ctrl->buf[4] = (uint8_t) (p_ctrl->p_mode->prox_lower_threshold >> 8);
    err            = rm_ob1203_write(p_ctrl, &p_ctrl->buf[0], 5);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

#endif
