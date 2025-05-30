/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : r_emwin_rx_pid_iic_if.c
 * Version      : 1.21
 * Description  : Functions of IIC touch interface.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version        Description
 *         : 31.07.2020 6.14.a.1.00    First Release
 *         : 04.09.2020 6.14.a.1.10    Update to adjust r_emwin_rx_config.h file.
 *         : 11.12.2020 6.14.g.1.20    Update to adjust emWin v6.14g. Modify multi-touch and timer function.
 *                                     Adjust GCC and IAR compilers.
 *         : 31.03.2021 6.14.g.1.30    Update to adjust the spec of Smart Configurator and QE for Display.
 *         : 29.12.2021 6.20.  1.00    Update emWin library to v6.22.
 *                                     Adjust configuration option with Smart Configurator.
 *         : 31.08.2022 6.26.c.1.00    Update emWin library to v6.26c.
 *                                     Added preprocessor code for code activation by selecting Touch interface.
 *         : 31.03.2023 6.32.a.1.00    Update emWin library to v6.32a.
 *         : 31.01.2024 6.34.g.1.00    Update emWin library to v6.34g.
 *         : 20.03.2025 6.34.g.1.21    Changed the disclaimer.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

#include "r_emwin_rx_if.h"

#if ((EMWIN_USE_TOUCH == 1) && (EMWIN_TOUCH_IF == TOUCH_IF_SCI_IIC))

#include "r_sci_iic_rx_if.h"
#include "r_emwin_rx_private.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private (static) variables and functions
 *********************************************************************************************************************/
static uint8_t s_a_buffer[TOUCH_DATA_BUFFER_SIZE] = {0};

static sci_iic_info_t s_iic_info;
static uint8_t s_iic_busy;


/**********************************************************************************************************************
 * Function Name: cb_sci_iic
 * Description  : .
 * Arguments    : .
 * Return Value : .
 *********************************************************************************************************************/
static void cb_sci_iic(void)
{
    sci_iic_mcu_status_t      iic_status;
    volatile sci_iic_return_t sci_iic_ret;
    volatile e_emwin_rx_err_t emwin_ret;

    sci_iic_ret = R_SCI_IIC_GetStatus(&s_iic_info, &iic_status);
    if ((SCI_IIC_SUCCESS == sci_iic_ret) && (1 == iic_status.BIT.NACK))
    {
        emwin_ret = r_emwin_rx_pidconf_cb(s_a_buffer, TOUCH_DATA_BUFFER_SIZE);
        if (EMWIN_RX_SUCCESS == emwin_ret)
        {
            s_iic_busy = 0;
        }
    }
}
/**********************************************************************************************************************
 * End of function cb_sci_iic
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: cb_timer_sci_iic
 * Description  : .
 * Arguments    : .
 * Return Value : .
 *********************************************************************************************************************/
static void cb_timer_sci_iic(cb_timer_arg_t arg)
{
    /* Read all touch points to clear the buffer on TC side */
    static uint8_t s_slave_addr_eeprom[] = { EMWIN_SLAVE_ADDRESS }; /* Slave address */
    static uint8_t s_access_addr1[]      = { 0x00 };                /* 1st data field */
    volatile sci_iic_return_t ret;

    if (s_iic_busy)
    {
        return;
    }

    /* Sets IIC Information */
    s_iic_info.p_slv_adr    = s_slave_addr_eeprom;
    s_iic_info.p_data1st    = s_access_addr1;
    s_iic_info.p_data2nd    = s_a_buffer;
    s_iic_info.dev_sts      = SCI_IIC_NO_INIT;
    s_iic_info.cnt1st       = sizeof(s_access_addr1);
    s_iic_info.cnt2nd       = sizeof(s_a_buffer);
    s_iic_info.callbackfunc = &cb_sci_iic;

    /* Start Master Receive */
    ret = R_SCI_IIC_MasterReceive(&s_iic_info);
    if (SCI_IIC_SUCCESS == ret)
    {
        s_iic_busy = 1;
    }
}
/**********************************************************************************************************************
 End of function cb_timer_sci_iic
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: r_emwin_rx_pid_open
 * Description  : .
 * Arguments    : .
 * Return Value : .
 *********************************************************************************************************************/
e_emwin_rx_err_t r_emwin_rx_pid_open(void)
{
    e_emwin_rx_err_t ret = EMWIN_RX_FAIL;

    e_emwin_rx_err_t timer_ret;
    sci_iic_return_t sci_ret;

    s_iic_info.ch_no = EMWIN_TOUCH_IF_NUMBER;

    sci_ret = R_SCI_IIC_Open(&s_iic_info);
    if (SCI_IIC_SUCCESS == sci_ret)
    {
        /* Casting emwin_rx_cb_timer pointer is used for callback function. */
        timer_ret = r_emwin_rx_guix_timer_create(20, (emwin_rx_cb_timer *)cb_timer_sci_iic);
        if (EMWIN_RX_SUCCESS == timer_ret)
        {
            ret = EMWIN_RX_SUCCESS;
        }
    }

    return ret;
}
/**********************************************************************************************************************
 End of function r_emwin_rx_pid_open
 *********************************************************************************************************************/
#endif /* (EMWIN_TOUCH_IF == TOUCH_IF_SCI_IIC) */
