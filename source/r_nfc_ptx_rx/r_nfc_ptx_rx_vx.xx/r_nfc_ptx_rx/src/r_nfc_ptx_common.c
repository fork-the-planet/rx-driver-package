/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_nfc_ptx_common.c
 * Description  : Common definition for PTX.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_nfc_ptx_data.h"
#include "r_nfc_ptx_common.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

#define TMR_MSEC_TO_SEC	(1000)

/**********************************************************************************************************************
 Structure definitions
 *********************************************************************************************************************/

static const st_sci_conf_t s_sci_cfg[] =
{
#if SCI_CFG_CH0_INCLUDED == 1
    {SCI_CH0 , R_SCI_PinSet_SCI0  ,SCI_CFG_CH0_TX_BUFSIZ  ,SCI_CFG_CH0_RX_BUFSIZ  },
#endif
#if SCI_CFG_CH1_INCLUDED == 1
    {SCI_CH1 , R_SCI_PinSet_SCI1  ,SCI_CFG_CH1_TX_BUFSIZ  ,SCI_CFG_CH1_RX_BUFSIZ  },
#endif
#if SCI_CFG_CH2_INCLUDED == 1
    {SCI_CH2 , R_SCI_PinSet_SCI2  ,SCI_CFG_CH2_TX_BUFSIZ  ,SCI_CFG_CH2_RX_BUFSIZ  },
#endif
#if SCI_CFG_CH3_INCLUDED == 1
    {SCI_CH3 , R_SCI_PinSet_SCI3  ,SCI_CFG_CH3_TX_BUFSIZ  ,SCI_CFG_CH3_RX_BUFSIZ  },
#endif
#if defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL)
    {SCI_NUM_CH, NULL ,0 ,0 }
#else
#if SCI_CFG_CH4_INCLUDED == 1
    {SCI_CH4 , R_SCI_PinSet_SCI4  ,SCI_CFG_CH4_TX_BUFSIZ  ,SCI_CFG_CH4_RX_BUFSIZ  },
#endif
#if SCI_CFG_CH5_INCLUDED == 1
    {SCI_CH5 , R_SCI_PinSet_SCI5  ,SCI_CFG_CH5_TX_BUFSIZ  ,SCI_CFG_CH5_RX_BUFSIZ  },
#endif
#if SCI_CFG_CH6_INCLUDED == 1
    {SCI_CH6 , R_SCI_PinSet_SCI6  ,SCI_CFG_CH6_TX_BUFSIZ  ,SCI_CFG_CH6_RX_BUFSIZ  },
#endif
#if SCI_CFG_CH7_INCLUDED == 1
    {SCI_CH7 , R_SCI_PinSet_SCI7  ,SCI_CFG_CH7_TX_BUFSIZ  ,SCI_CFG_CH7_RX_BUFSIZ  },
#endif
#if SCI_CFG_CH8_INCLUDED == 1
    {SCI_CH8 , R_SCI_PinSet_SCI8  ,SCI_CFG_CH8_TX_BUFSIZ  ,SCI_CFG_CH8_RX_BUFSIZ  },
#endif
#if SCI_CFG_CH9_INCLUDED == 1
    {SCI_CH9 , R_SCI_PinSet_SCI9  ,SCI_CFG_CH9_TX_BUFSIZ  ,SCI_CFG_CH9_RX_BUFSIZ  },
#endif
#if SCI_CFG_CH10_INCLUDED == 1
    {SCI_CH10, R_SCI_PinSet_SCI10 ,SCI_CFG_CH10_TX_BUFSIZ ,SCI_CFG_CH10_RX_BUFSIZ },
#endif
#if SCI_CFG_CH11_INCLUDED == 1
    {SCI_CH11, R_SCI_PinSet_SCI11 ,SCI_CFG_CH11_TX_BUFSIZ ,SCI_CFG_CH11_RX_BUFSIZ },
#endif
#if SCI_CFG_CH12_INCLUDED == 1
    {SCI_CH12, R_SCI_PinSet_SCI12 ,SCI_CFG_CH12_TX_BUFSIZ ,SCI_CFG_CH12_RX_BUFSIZ },
#endif
    {SCI_NUM_CH, NULL ,0 ,0 }
#endif
};

/**********************************************************************************************************************
 Extern function definitions
 *********************************************************************************************************************/
extern void R_ICU_PinSet(void);

/**********************************************************************************************************************
 Local function definitions
 *********************************************************************************************************************/
static st_sci_conf_t *get_port_config(void);

/**********************************************************************************************************************
 Global function definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: get_port_config
 * Description  : get port configuration table pointer.
 * Arguments    : none
 * Return Value : SUCCESS : SCI configuration table(st_sci_conf_t) pointer by port.
 *                FAIL    : NULL
 *********************************************************************************************************************/
static st_sci_conf_t *get_port_config(void)
{
    uint8_t i = 0;
    st_sci_conf_t * p_tbl = NULL;

    /* Set table pointer */
    for (i = 0;; i++ )
    {
        if (SCI_NUM_CH == s_sci_cfg[i].ch)
        {
            break;
        }
        if (NFC_CFG_SCI_CHANNEL == s_sci_cfg[i].ch)
        {
            p_tbl = (st_sci_conf_t *)&s_sci_cfg[i];
            break;
        }
    }
    return p_tbl;
}
/**********************************************************************************************************************
 * End of function get_port_config
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 * Function Name: uart_port_open
 * Description  : Open serial port.
 * Arguments    : p_cb  - Callback function of SCI interrupts
 * Return Value : E_OK    success
 *                E_FAIL  failed
 *********************************************************************************************************************/
sci_err_t port_open(sci_hdl_t *p_handle, void (* const p_cb)(void *p_args))
{
	st_sci_tbl_t * p_port = NULL;
    st_sci_conf_t * p_cfg = get_port_config();

    if (NULL == p_cfg)
    {
        return SCI_ERR_BAD_CHAN;
    }

    /* Port settings */
    p_cfg->func();

    memset(&p_port->sci_hdl , 0, sizeof(sci_hdl_t));
#if (SCI_CFG_SSPI_INCLUDED == 1) //SCI SSPI mode
    p_port->sci_config.sspi.spi_mode     = s_spi_cfg.spi_mode;
    p_port->sci_config.sspi.bit_rate     = s_spi_cfg.bit_rate;
    p_port->sci_config.sspi.msb_first    = s_spi_cfg.msb_first;
    p_port->sci_config.sspi.invert_data  = s_spi_cfg.invert_data;
    p_port->sci_config.sspi.int_priority = s_spi_cfg.int_priority;
    if (SCI_SUCCESS != R_SCI_Open(p_cfg->ch, SCI_MODE_SSPI, &p_port->sci_config, p_cb, p_handle))
    {
        return SCI_ERR_BAD_CHAN;
    }
    return SCI_SUCCESS;
#endif
}
/**********************************************************************************************************************
 * End of function port_open
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 * Function Name: port_send
 * Description  : Send data to the port.
 * Arguments    : hdl   - Handle to the SCI port
 *                p_src  - Pointer to the source data buffer
 *                length - Length of the data to send
 * Return Value : E_OK    success
 *                E_FAIL  failed
 *********************************************************************************************************************/
 sci_err_t port_send(sci_hdl_t const hdl, uint8_t *p_src, uint32_t length)
 {
    sci_err_t r_status = SCI_SUCCESS;

    if (NULL == p_src || 0 == length)
    {
        return SCI_ERR_INVALID_ARG;
    }

    r_status = R_SCI_Send(hdl, p_src, length);
    if (SCI_SUCCESS != r_status)
    {
        return r_status;
    }

    return SCI_SUCCESS;
 }

 /**********************************************************************************************************************
 * End of function port_send
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: port_receive
 * Description  : Receive data from the port.
 * Arguments    : hdl   - Handle to the SCI port
 *                p_dst  - Pointer to the destination data buffer
 *                length - Length of the data to receive
 * Return Value : E_OK    success
 *                E_FAIL  failed
 *********************************************************************************************************************/
 sci_err_t port_receive(sci_hdl_t const hdl, uint8_t *p_dst, uint32_t length)
 {
    sci_err_t r_status = SCI_SUCCESS;

    if (NULL == p_dst || 0 == length)
    {
        return SCI_ERR_INVALID_ARG;
    }

    r_status = R_SCI_Receive(hdl, p_dst, length);
    if (SCI_SUCCESS != r_status)
    {
        return r_status;
    }

    return SCI_SUCCESS;
}

/**********************************************************************************************************************
 * End of function port_receive
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 * Function Name: port_close
 * Description  : Close the port.
 * Arguments    : hdl   - Handle to the SCI port
 * Return Value : E_OK    success
 *                E_FAIL  failed
 *********************************************************************************************************************/
sci_err_t port_close(sci_hdl_t const hdl)
{
    sci_err_t r_status = SCI_SUCCESS;

    if (NULL == hdl)
    {
        return SCI_ERR_INVALID_ARG;
    }

    r_status = R_SCI_Close(hdl);
    if (SCI_SUCCESS != r_status)
    {
        return r_status;
    }

    return SCI_SUCCESS;
}
/**********************************************************************************************************************
 * End of function port_close
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ext_irq_open
 * Description  : Open external interrupt.
 * Arguments    : phandle  - Pointer to the IRQ handle
 *                p_callback - Pointer to the callback function
 * Return Value : E_OK    success
 *                E_FAIL  failed
 *********************************************************************************************************************/
irq_err_t ext_irq_open(irq_handle_t *phandle, void (* const p_callback)(void *p_args))
{
    irq_err_t r_status = IRQ_SUCCESS;

    /* Initialize GPIO for external interrupt */
    R_ICU_PinSet();

    irq_number_t irq_number = s_ext_irq_cfg.irq_num;

    irq_trigger_t trigger = s_ext_irq_cfg.trigger;

    irq_prio_t priority = (irq_prio_t)s_ext_irq_cfg.priority;

    r_status = R_IRQ_Open(irq_number, trigger, priority, phandle, p_callback);

    return r_status;
}
/**********************************************************************************************************************
 * End of function ext_irq_open
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ext_irq_enable
 * Description  : Enable or disable external interrupt.
 * Arguments    : hdl    - Handle to the IRQ
 *                enable - true to enable, false to disable
 * Return Value : E_OK    success
 *                E_FAIL  failed
 *********************************************************************************************************************/
irq_err_t ext_irq_enable(irq_handle_t hdl, bool enable)
{
    irq_err_t r_status = IRQ_SUCCESS;

    if (NULL != hdl)
    {
        r_status = R_IRQ_InterruptEnable(hdl, (uint8_t*)enable);
    }
    else
    {
        r_status = IRQ_ERR_INVALID_PTR;
    }

    return r_status;
}
/**********************************************************************************************************************
 * End of function ext_irq_enable
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: read_interrupt_status
 * Description  : Read the status of the external interrupt.
 * Arguments    : None
 * Return Value : Status of the external interrupt enable bit
 *********************************************************************************************************************/
uint8_t read_interrupt_status(void)
{
    return NFC_IRQ_ENABLE_BIT;
}

irq_err_t ext_irq_read_input(irq_handle_t hdl, uint32_t *state)
{
    irq_err_t r_status = IRQ_SUCCESS;

    if (NULL != hdl)
    {
        r_status = R_IRQ_ReadInput(hdl, (uint8_t *)state);
    }
    else
    {
        r_status = IRQ_ERR_INVALID_PTR;
    }

    return r_status;
}
/**********************************************************************************************************************
 * End of function ext_irq_read_input
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: ext_irq_close
 * Description  : Close the external interrupt.
 * Arguments    : hdl - Handle to the IRQ
 * Return Value : E_OK    success
 *                E_FAIL  failed
 *********************************************************************************************************************/
irq_err_t ext_irq_close(irq_handle_t hdl)
{
    irq_err_t r_status = IRQ_SUCCESS;

    if (NULL != hdl)
    {
        r_status = R_IRQ_Close(hdl);
    }
    else
    {
        r_status = IRQ_ERR_INVALID_PTR;
    }

    return r_status;
}
/**********************************************************************************************************************
 * End of function ext_irq_close
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: write_pin
 * Description  : Write a value to a GPIO pin.
 * Arguments    : pin   - The GPIO pin to write to
 *                level - The value to write (high or low)
 * Return Value : None
 *********************************************************************************************************************/
void write_pin(gpio_port_pin_t pin, gpio_level_t level)
{
    R_GPIO_PinWrite(pin, level);
}
/**********************************************************************************************************************
 * End of function write_pin
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: read_pin
 * Description  : Read the value of a GPIO pin.
 * Arguments    : pin - The GPIO pin to read from
 * Return Value : The value of the GPIO pin (high or low)
 *********************************************************************************************************************/
gpio_level_t read_pin(gpio_port_pin_t pin)
{
    return R_GPIO_PinRead(pin);
}

int set_pin_direct(gpio_port_pin_t *pin, gpio_dir_t dir)
{
    if (NULL == pin)
    {
        return -1; // Error: null pointer
    }

    R_GPIO_PinDirectionSet(*pin, dir);
    return 0; // Success
}
/**********************************************************************************************************************
 * End of function read_pin
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: timer_init
 * Description  : Initialize the timer.
 * Arguments    : freq      - Frequency for the timer
 *                p_callback - Callback function to be called on timer expiration
 *                channel    - Timer channel to use
 *                priority   - Timer priority
 * Return Value : true if successful, false otherwise
 *********************************************************************************************************************/
bool timer_init(uint32_t freq, void(* p_callback)(void * pdata), uint32_t channel, cmt_priority_t priority)
{
    /* Initialize the timer */
    bool status = R_CMT_CreatePeriodicAssignChannelPriority(freq, p_callback, channel, priority);

    return status;
}
/**********************************************************************************************************************
 * End of function timer_init
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: timer_status
 * Description  : Get the current status of the timer.
 * Arguments    : channel   - Timer channel to check
 *                p_status  - Pointer to store the timer status (true if running, false if stopped)
 * Return Value : true if successful, false otherwise
 *********************************************************************************************************************/
bool timer_status(uint32_t channel, bool *p_status)
{
    if (NULL == p_status)
    {
        return false;
    }

    /* Get the current timer status */
    bool status = R_CMT_Control(channel, CMT_RX_CMD_IS_CHANNEL_COUNTING, (void *)p_status);

    return status;
}
/**********************************************************************************************************************
 * End of function timer_status
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: timer_stop
 * Description  : Stop the timer.
 * Arguments    : channel - Timer channel to stop
 * Return Value : true if successful, false otherwise
 *********************************************************************************************************************/
bool timer_stop(uint32_t channel)
{
    /* Stop the timer */
    bool status = R_CMT_Stop(channel);

    return status;
}
/**********************************************************************************************************************
 * End of function timer_stop
 *********************************************************************************************************************/
