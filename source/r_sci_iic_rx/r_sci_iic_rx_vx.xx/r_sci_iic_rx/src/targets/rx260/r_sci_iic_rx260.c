/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
 * No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
 * applicable laws, including copyright laws. 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO 
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the 
 * following link:
 * http://www.renesas.com/disclaimer 
 *
 * Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_sci_iic_rx260.c
 * Description  : Functions for using SCI_IIC on RX devices. 
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 28.06.2024 1.00     First Release
 **********************************************************************************************************************/
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
/* Access to peripherals and board defines. */
#include "platform.h"

#ifdef BSP_MCU_RX260
/* Defines for SCI_IIC support */
    #include "r_sci_iic_rx_pin_config.h"
    #include "r_sci_iic_rx_private.h"
    #include "r_sci_iic_rx260_private.h"
    #include "r_sci_iic_rx_if.h"
    #include "r_sci_iic_rx_config.h"

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
/*----------------------------------------------------------------------------*/
/*   Defines specific information for each SCI IIC channel.                   */
/*----------------------------------------------------------------------------*/
    #if SCI_IIC_CFG_CH1_INCLUDED
/* rom info */
const sci_iic_ch_rom_t g_sci_iic_ch1_rom =
{
    BSP_LOCK_SCI1,
    (sci_regs_t)&SCI1, /* Cast to sci_regs_t */
    (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRB.LONG, BIT30_MASK, /* Cast to R_BSP_EVENACCESS_SFR */
    &ICU.IPR[IPR_SCI1_TXI1].BYTE,
    &ICU.IR[IR_SCI1_TXI1].BYTE,
    &ICU.IR[IR_SCI1_TEI1].BYTE, BIT0_MASK,
    &ICU.IER[IER_SCI1_TXI1].BYTE, BIT4_MASK,
    &ICU.IER[IER_SCI1_TEI1].BYTE, BIT5_MASK,
    SCI_IIC_CFG_CH1_INT_PRIORITY,
    SCI_IIC_CFG_CH1_SSCL_GP,
    SCI_IIC_CFG_CH1_SSCL_PIN,
    SCI_IIC_MPC_SSCL1_ENABLE,
    SCI_IIC_CFG_CH1_SSDA_GP,
    SCI_IIC_CFG_CH1_SSDA_PIN,
    SCI_IIC_MPC_SSDA1_ENABLE,
    SCI_IIC_CFG_CH1_SSDA_DELAY_SELECT,
    SCI_IIC_CFG_CH1_BITRATE_BPS,
    SCI_IIC_CFG_CH1_DIGITAL_FILTER,
    SCI_IIC_CFG_CH1_FILTER_CLOCK
};

/* channel control block */
sci_iic_ch_ctrl_t g_sci_iic_ch1_ctrl =
{
    &g_sci_iic_ch1_rom,
    SCI_IIC_EV_INIT,
    SCI_IIC_MODE_NONE,
    SCI_IIC_STS_NO_INIT,
    SCI_IIC_STS_NO_INIT,
    (uint8_t)INT_ZERO, /* Cast to uint8_t */
    (sci_iic_info_t *)NULL
};
    #endif /* endif SCI_IIC_CFG_CH1_INCLUDED */

    #if SCI_IIC_CFG_CH5_INCLUDED
/* rom info */
const sci_iic_ch_rom_t g_sci_iic_ch5_rom =
{
    BSP_LOCK_SCI5,
    (sci_regs_t)&SCI5, /* Cast to sci_regs_t */
    (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRB.LONG, BIT26_MASK, /* Cast to R_BSP_EVENACCESS_SFR */
    &ICU.IPR[IPR_SCI5_TXI5].BYTE,
    &ICU.IR[IR_SCI5_TXI5].BYTE,
    &ICU.IR[IR_SCI5_TEI5].BYTE, BIT0_MASK,
    &ICU.IER[IER_SCI5_TXI5].BYTE, BIT0_MASK,
    &ICU.IER[IER_SCI5_TEI5].BYTE, BIT1_MASK,
    SCI_IIC_CFG_CH5_INT_PRIORITY,
    SCI_IIC_CFG_CH5_SSCL_GP,
    SCI_IIC_CFG_CH5_SSCL_PIN,
    SCI_IIC_MPC_SSCL5_ENABLE,
    SCI_IIC_CFG_CH5_SSDA_GP,
    SCI_IIC_CFG_CH5_SSDA_PIN,
    SCI_IIC_MPC_SSDA5_ENABLE,
    SCI_IIC_CFG_CH5_SSDA_DELAY_SELECT,
    SCI_IIC_CFG_CH5_BITRATE_BPS,
    SCI_IIC_CFG_CH5_DIGITAL_FILTER,
    SCI_IIC_CFG_CH5_FILTER_CLOCK
};

/* channel control block */
sci_iic_ch_ctrl_t g_sci_iic_ch5_ctrl =
{
    &g_sci_iic_ch5_rom,
    SCI_IIC_EV_INIT,
    SCI_IIC_MODE_NONE,
    SCI_IIC_STS_NO_INIT,
    SCI_IIC_STS_NO_INIT,
    (uint8_t)INT_ZERO, /* Cast to uint8_t */
    (sci_iic_info_t *)NULL
};
    #endif /* endif SCI_IIC_CFG_CH5_INCLUDED */

    #if SCI_IIC_CFG_CH6_INCLUDED
/* rom info */
const sci_iic_ch_rom_t g_sci_iic_ch6_rom =
{
    BSP_LOCK_SCI6,
    (sci_regs_t)&SCI6, /* Cast to sci_regs_t */
    (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRB.LONG, BIT25_MASK, /* Cast to R_BSP_EVENACCESS_SFR */
    &ICU.IPR[IPR_SCI6_TXI6].BYTE,
    &ICU.IR[IR_SCI6_TXI6].BYTE,
    &ICU.IR[IR_SCI6_TEI6].BYTE, BIT0_MASK,
    &ICU.IER[IER_SCI6_TXI6].BYTE, BIT4_MASK,
    &ICU.IER[IER_SCI6_TEI6].BYTE, BIT5_MASK,
    SCI_IIC_CFG_CH6_INT_PRIORITY,
    SCI_IIC_CFG_CH6_SSCL_GP,
    SCI_IIC_CFG_CH6_SSCL_PIN,
    SCI_IIC_MPC_SSCL6_ENABLE,
    SCI_IIC_CFG_CH6_SSDA_GP,
    SCI_IIC_CFG_CH6_SSDA_PIN,
    SCI_IIC_MPC_SSDA6_ENABLE,
    SCI_IIC_CFG_CH6_SSDA_DELAY_SELECT,
    SCI_IIC_CFG_CH6_BITRATE_BPS,
    SCI_IIC_CFG_CH6_DIGITAL_FILTER,
    SCI_IIC_CFG_CH6_FILTER_CLOCK
};

/* channel control block */
sci_iic_ch_ctrl_t g_sci_iic_ch6_ctrl =
{
    &g_sci_iic_ch6_rom,
    SCI_IIC_EV_INIT,
    SCI_IIC_MODE_NONE,
    SCI_IIC_STS_NO_INIT,
    SCI_IIC_STS_NO_INIT,
    (uint8_t)INT_ZERO, /* Cast to uint8_t */
    (sci_iic_info_t *)NULL
};
    #endif /* endif SCI_IIC_CFG_CH6_INCLUDED */

    #if SCI_IIC_CFG_CH12_INCLUDED
/* rom info */
const sci_iic_ch_rom_t g_sci_iic_ch12_rom =
{
    BSP_LOCK_SCI12,
    (sci_regs_t)&SCI12, /* Cast to sci_regs_t */
    (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRB.LONG, BIT4_MASK, /* Cast to R_BSP_EVENACCESS_SFR */
    &ICU.IPR[IPR_SCI12_TXI12].BYTE,
    &ICU.IR[IR_SCI12_TXI12].BYTE,
    &ICU.IR[IR_SCI12_TEI12].BYTE, BIT0_MASK,
    &ICU.IER[IER_SCI12_TXI12].BYTE, BIT0_MASK,
    &ICU.IER[IER_SCI12_TEI12].BYTE, BIT1_MASK,
    SCI_IIC_CFG_CH12_INT_PRIORITY,
    SCI_IIC_CFG_CH12_SSCL_GP,
    SCI_IIC_CFG_CH12_SSCL_PIN,
    SCI_IIC_MPC_SSCL12_ENABLE,
    SCI_IIC_CFG_CH12_SSDA_GP,
    SCI_IIC_CFG_CH12_SSDA_PIN,
    SCI_IIC_MPC_SSDA12_ENABLE,
    SCI_IIC_CFG_CH12_SSDA_DELAY_SELECT,
    SCI_IIC_CFG_CH12_BITRATE_BPS,
    SCI_IIC_CFG_CH12_DIGITAL_FILTER,
    SCI_IIC_CFG_CH12_FILTER_CLOCK
};

/* channel control block */
sci_iic_ch_ctrl_t g_sci_iic_ch12_ctrl =
{
    &g_sci_iic_ch12_rom,
    SCI_IIC_EV_INIT,
    SCI_IIC_MODE_NONE,
    SCI_IIC_STS_NO_INIT,
    SCI_IIC_STS_NO_INIT,
    (uint8_t)INT_ZERO, /* Cast to uint8_t */
    (sci_iic_info_t *)NULL
};
    #endif /* endif SCI_IIC_CFG_CH12_INCLUDED */

/*----------------------------------------------------------------------------*/
/*   Array for start addresses of information for each SCI IIC channel        */
/*----------------------------------------------------------------------------*/
const sci_iic_hdl_t g_sci_iic_handles[SCI_IIC_NUM_CH_MAX] =
{
    NULL,
    #if SCI_IIC_CFG_CH1_INCLUDED
    &g_sci_iic_ch1_ctrl,
    #else
    NULL,
    #endif
    NULL,
    NULL,
    NULL,
    #if SCI_IIC_CFG_CH5_INCLUDED
    &g_sci_iic_ch5_ctrl,
    #else
    NULL,
    #endif
    #if SCI_IIC_CFG_CH6_INCLUDED
    &g_sci_iic_ch6_ctrl,
    #else
    NULL,
    #endif
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    #if SCI_IIC_CFG_CH12_INCLUDED
    &g_sci_iic_ch12_ctrl
    #else
    NULL
    #endif
};

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
static void sci_iic_set_frequency (sci_iic_info_t * p_sci_iic_info);
static void sci_iic_clear_ir_flag (sci_iic_info_t * p_sci_iic_info);

/***********************************************************************************************************************
 * Function Name: r_sci_iic_check_arguments
 * Description  : check to parameter.
 * Arguments    : sci_iic_info_t * p_sci_iic_info    ; IIC Information
 *              ; sci_iic_api_mode_t called_api      ; Internal Mode
 * Return Value : none
 **********************************************************************************************************************/
sci_iic_return_t r_sci_iic_check_arguments(sci_iic_info_t * p_sci_iic_info, sci_iic_api_mode_t called_api)
{

    if (NULL == p_sci_iic_info)
    {
        return SCI_IIC_ERR_INVALID_ARG;
    }

    if (SCI_IIC_MODE_RECEIVE == called_api)
    {

        if (((NULL == p_sci_iic_info->p_slv_adr) || (NULL == p_sci_iic_info->p_data2nd))
                || ((uint32_t)NULL == p_sci_iic_info->cnt2nd))
        {
            return SCI_IIC_ERR_INVALID_ARG;
        }

    }

    if ((SCI_IIC_MODE_SEND == called_api) || (SCI_IIC_MODE_RECEIVE == called_api))
    {

        if (NULL == p_sci_iic_info->callbackfunc)
        {
            return SCI_IIC_ERR_INVALID_ARG;
        }

    }

    if (((((((((((SCI_IIC_NUM_CH0 == p_sci_iic_info->ch_no) || (SCI_IIC_NUM_CH2 == p_sci_iic_info->ch_no))
            || (SCI_IIC_NUM_CH3 == p_sci_iic_info->ch_no)) || (SCI_IIC_NUM_CH4 == p_sci_iic_info->ch_no))
            || (SCI_IIC_NUM_CH7 == p_sci_iic_info->ch_no)) || (SCI_IIC_NUM_CH8 == p_sci_iic_info->ch_no))
            || (SCI_IIC_NUM_CH9 == p_sci_iic_info->ch_no)) || (SCI_IIC_NUM_CH10 == p_sci_iic_info->ch_no))
            || (SCI_IIC_NUM_CH11 == p_sci_iic_info->ch_no)))
            || (SCI_IIC_NUM_CH12 < p_sci_iic_info->ch_no))
    {
        return SCI_IIC_ERR_INVALID_CHAN;
    }

    return SCI_IIC_SUCCESS;
} /* End of function r_sci_iic_check_arguments() */

/***********************************************************************************************************************
 * Function Name: r_sci_iic_power_on
 * Description  : Turns on power to a SCI_IIC channel.
 * Arguments    : channel -
 *                    Which channel to use.
 * Return Value : none
 **********************************************************************************************************************/
void r_sci_iic_power_on(uint8_t channel)
{
    R_BSP_VOLATILE_EVENACCESS const sci_iic_ch_rom_t * p_rom = g_sci_iic_handles[channel]->prom;

    uint32_t mstp;
    uint32_t stop_mask;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
#endif

    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif

    /* Enable selected SCI_IIC Channel. */
    /* Bring module out of stop state. */
    mstp            = (*p_rom->pmstp);
    stop_mask       = p_rom->stop_mask;
    (*p_rom->pmstp) = mstp & (~stop_mask);

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
} /* End of function r_sci_iic_power_on() */

/***********************************************************************************************************************
 * Function Name: r_sci_iic_power_off
 * Description  : Turns off power to a SCI_IIC channel.
 * Arguments    : channel -
 *                    Which channel to use.
 * Return Value : none
 **********************************************************************************************************************/
void r_sci_iic_power_off(uint8_t channel)
{
    R_BSP_VOLATILE_EVENACCESS const sci_iic_ch_rom_t * p_rom = g_sci_iic_handles[channel]->prom;
    
    uint32_t mstp;
    uint32_t stop_mask;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
#endif

    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif

    /* Disable selected SCI_IIC Channel. */
    /* Put module in stop state. */
    mstp            = (*p_rom->pmstp);
    stop_mask       = p_rom->stop_mask;
    (*p_rom->pmstp) = mstp | stop_mask;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
} /* End of function r_sci_iic_power_off() */

/***********************************************************************************************************************
 * Function Name: r_sci_iic_io_open
 * Description  : Open Port Processing
 *                Sets ports to input mode. Ports input pull-up becomes "Off".
 * Arguments    : uint8_t port_gr      ;   port group
 *                uint8_t pin_num      ;   pin number
 * Return Value : None
 **********************************************************************************************************************/
void r_sci_iic_io_open(uint8_t port_gr, uint8_t pin_num)
{

    R_BSP_VOLATILE_EVENACCESS uint8_t * const p_pcr = \
            (uint8_t *)((uint32_t)SCI_IIC_PRV_PCR_BASE_REG+(uint32_t)port_gr);/* Get p_pcr */

    R_BSP_VOLATILE_EVENACCESS uint8_t * const p_pdr = \
            (uint8_t *)((uint32_t)SCI_IIC_PRV_PDR_BASE_REG+(uint32_t)port_gr);/* Get p_pdr */

    R_BSP_VOLATILE_EVENACCESS uint8_t * const p_odr0 = \
            (uint8_t *)((uint32_t)SCI_IIC_PRV_ODR0_BASE_REG+(uint32_t)(port_gr*2));/* Get p_odr0 */

    R_BSP_VOLATILE_EVENACCESS uint8_t * const p_odr1 = \
            (uint8_t *)((uint32_t)SCI_IIC_PRV_ODR1_BASE_REG+(uint32_t)(port_gr*2));/* Get p_odr1 */

    R_BSP_VOLATILE_EVENACCESS uint8_t * const p_dscr = \
            (uint8_t *)((uint32_t)SCI_IIC_PRV_DSCR_BASE_REG+(uint32_t)port_gr);/* Get p_dscr */

    /* Sets the port register */
    (*p_dscr) |= (1U<<pin_num); /* drive capacity control : High-drive output */
    (*p_pcr)  &= (~(1U<<pin_num)); /* input pull-up resister : off */
    (*p_pdr)  &= (~(1U<<pin_num)); /* input mode */

    /* Set N-channel open-drain output */
    if (pin_num <= 3)
    {
        (*p_odr0) |= (0x01 << (2*pin_num));
    }
    else
    {
        (*p_odr1) |= (0x01 << (2*(pin_num&0x03)));
    }

    /* dummy read */
    if (*p_odr1)
    {
        R_BSP_NOP();
    }
} /* End of function r_sci_iic_io_open() */

/***********************************************************************************************************************
 * Function Name: r_sci_iic_init_io_register
 * Description  : Initializes SCI_IIC register.
 * Arguments    : sci_iic_info_t * p_sci_iic_info     ;   IIC Information
 * Return Value : None
 **********************************************************************************************************************/
void r_sci_iic_init_io_register(sci_iic_info_t * p_sci_iic_info)
{
    sci_regs_t pregs = g_sci_iic_handles[p_sci_iic_info->ch_no]->prom->regs;

    R_BSP_VOLATILE_EVENACCESS const sci_iic_ch_rom_t * p_rom = g_sci_iic_handles[p_sci_iic_info->ch_no]->prom;

    /* Sets SCLn and SDAn to non-driven state. */
    /* SCR - Serial Control Register 
     b5     TE - Transmit Enable - Serial transmission is enabled. */
    pregs->SCR.BYTE = SCI_IIC_SCR_INIT;

    if (SCI_IIC_NUM_CH12 != p_sci_iic_info->ch_no)
    {
        /* SPTR - Serial Port Register 
         b7     TTADJ - Transmit Signal Transition Timing Adjustment.
         b6     RTADJ - Receive Data Sampling Timing Adjustment.
         b5     TINV - Transmitter Output Invert.
         b4     RINV - Receiver Input Invert.
         b3     Reserved - These bits are read as 0.
         b2     SPB2IO - Serial Port Break I/O.
         b1     SPB2DT - Serial Port Break Data.
         b0     RXDMON - RXD Line Monitoring Flag.   */
        pregs->SPTR.BYTE = SCI_IIC_SPTR_INIT;
    }

    /* Sets a transfer clock. */
    /* Includes I/O register read operation at the end of the following function. */
    sci_iic_set_frequency(p_sci_iic_info);

    /* SEMR - Serial Extended Mode Register
     b5    Digital Noise Filter Function Enable -
     Noise cancellation function for the SSCLn and SSDAn input signals enabled. */
    pregs->SEMR.BIT.NFEN = p_rom->df_sel;

    /* SNFR - Noise Filter Setting Register
     b7;b3   Reserved - These bits are read as 0.
     b2:b0   NFCS - The clock signal divided by 1 is used with the noise filter.
     b0      IICM  - Simple I2C Mode Select - Serial Interface Mode */
    pregs->SNFR.BIT.NFCS = p_rom->df_clk;

    /* Resets all SCI_IIC registers and the internal status. */
    /* SIMR1 - I2C Mode Register 1
     b7;b3   IICDL - SSDA Delay Output Select
     b2:b1   Reserved - These bits are read as 0.
     b0      IICM  - Simple I2C Mode Select - Serial Interface Mode */
    pregs->SIMR1.BIT.IICM = 0; /* Do not use Simple IIC mode. */

    /* SIMR1 - I2C Mode Register 1
     b7:b3  IICDL - SSDA Delay Output Select - 2 to 3 cycles */
    pregs->SIMR1.BIT.IICDL = p_rom->ssda_delay;

    /* SIMR2 - I2C Mode Register 2
     b5      IICACKT - ACK Transmission Data - NACK transmission and reception of ACK/NACK */
    pregs->SIMR2.BIT.IICACKT = SCI_IIC_NACK_TRANS;

    /* SIMR2 - I2C Mode Register 2
     b1      IICCSC - Clock Synchronization - Enable Clock Synchronization */
    pregs->SIMR2.BIT.IICCSC = SCI_IIC_SYNCHRO;

    /* SIMR2 - I2C Mode Register 2
     b0      IICINTM - I2C Interrupt Mode Select - Use reception and transmission interrupts. */
    pregs->SIMR2.BIT.IICINTM = SCI_IIC_RCV_TRS_INTERRUPT;

    /* SISR - I2C Status Register
     b0      IICACKR - ACK Reception Data Flag - ACK received */
    pregs->SISR.BIT.IICACKR = SCI_IIC_ACK_RCV;

    /* SPMR - SPI Mode Register
     b7      CKPH   - Clock Phase Select - Clock is not delayed.
     b6      CKPOL  - Clock Polarity Select - Clock polarity is not inverted.
     b5      Reserved - These bits are read as 0.
     b4      MFF    - Mode Fault Flag - No mode-fault error.
     b3      Reserved - These bits are read as 0.
     b2      MSS - Master Slave Select - master mode.
     b1      CTSE - CTS Enable - CTS function is disabled (RTS output function is enabled).
     b0      SSE - SS Pin Function Enable - SS pin function is disabled. */
    pregs->SPMR.BYTE = 0x00;
} /* End of function r_sci_iic_init_io_register() */

/***********************************************************************************************************************
 * Function Name: r_sci_iic_clear_io_register
 * Description  : Reset SCI I/O register.
 * Arguments    : sci_iic_info_t * p_sci_iic_info     ;   IIC Information
 * Return Value : None
 **********************************************************************************************************************/
void r_sci_iic_clear_io_register(sci_iic_info_t * p_sci_iic_info)
{
    sci_regs_t pregs = g_sci_iic_handles[p_sci_iic_info->ch_no]->prom->regs;

    /* Initializes SCI I/O register */
    pregs->SCR.BYTE  = SCI_IIC_SCR_INIT;
    pregs->SMR.BYTE  = SCI_IIC_SMR_INIT;
    pregs->SCMR.BYTE = SCI_IIC_SCMR_INIT;

    if (SCI_IIC_NUM_CH12 != p_sci_iic_info->ch_no)
    {
        pregs->SPTR.BYTE = SCI_IIC_SPTR_INIT;
    }

    pregs->BRR        = SCI_IIC_BRR_INIT;
    pregs->SEMR.BYTE  = SCI_IIC_SEMR_INIT;
    pregs->SNFR.BYTE  = SCI_IIC_SNFR_INIT;
    pregs->SIMR1.BYTE = SCI_IIC_SIMR1_INIT;
    pregs->SIMR2.BYTE = SCI_IIC_SIMR2_INIT;
    pregs->SIMR3.BYTE = SCI_IIC_SIMR3_INIT;
    pregs->SISR.BYTE  = SCI_IIC_SISR_INIT;
    pregs->SPMR.BYTE  = SCI_IIC_SPMR_INIT;
} /* End of function r_sci_iic_clear_io_register() */

/***********************************************************************************************************************
 * Function Name: r_sci_iic_int_disable
 * Description  : Disables interrupt.
 *              : Sets interrupt source priority.
 *              : Clears interrupt request register.
 * Arguments    : sci_iic_info_t * p_sci_iic_info     ;   IIC Information
 * Return Value : None
 **********************************************************************************************************************/
void r_sci_iic_int_disable(sci_iic_info_t * p_sci_iic_info)
{
    R_BSP_VOLATILE_EVENACCESS const sci_iic_ch_rom_t * p_rom = g_sci_iic_handles[p_sci_iic_info->ch_no]->prom;
    uint8_t icu_txi;
    uint8_t txi_en_mask;
    uint8_t icu_tei;
    uint8_t tei_en_mask;
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
#endif

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif

    /* Disables interrupt. */
    /* Disables TXI interrupt request enable register. */
    icu_txi            = (*p_rom->picu_txi);
    txi_en_mask        = p_rom->txi_en_mask;
    (*p_rom->picu_txi) = icu_txi & (~txi_en_mask);

    /* Disables TEI interrupt request enable register. */
    icu_tei            = (*p_rom->picu_tei);
    tei_en_mask        = p_rom->tei_en_mask;
    (*p_rom->picu_tei) = icu_tei & (~tei_en_mask);

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

    /* Clears interrupt source priority. */
    (*p_rom->pipr) = 0; /* Clears TXI interrupt source priority register. */

    /* dummy read */
    if (*p_rom->pipr)
    {
        R_BSP_NOP();
    }

    /* Clears the interrupt request register. */
    /* Includes I/O register read operation at the end of the following function. */
    sci_iic_clear_ir_flag(p_sci_iic_info);
} /* End of function r_sci_iic_int_disable() */

/***********************************************************************************************************************
 * Function Name: r_sci_iic_int_enable
 * Description  : Clears interrupt request register.
 *              : Enables interrupt.
 * Arguments    : sci_iic_info_t * p_sci_iic_info     ;   IIC Information
 * Return Value : None
 **********************************************************************************************************************/
void r_sci_iic_int_enable(sci_iic_info_t * p_sci_iic_info)
{
    R_BSP_VOLATILE_EVENACCESS const sci_iic_ch_rom_t * p_rom = g_sci_iic_handles[p_sci_iic_info->ch_no]->prom;

    uint8_t icu_txi;
    uint8_t txi_en_mask;
    uint8_t icu_tei;
    uint8_t tei_en_mask;
    uint8_t ipr_set_val;
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
#endif

    /* Clears the interrupt request register. */
    sci_iic_clear_ir_flag(p_sci_iic_info);

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif

    /* Enables interrupt. */
    /* Enables TXI interrupt request enable register. */
    icu_txi            = (*p_rom->picu_txi);
    txi_en_mask        = p_rom->txi_en_mask;
    (*p_rom->picu_txi) = icu_txi | txi_en_mask;

    /* Enables TEI interrupt request enable register. */
    icu_tei            = (*p_rom->picu_tei);
    tei_en_mask        = p_rom->tei_en_mask;
    (*p_rom->picu_tei) = icu_tei | tei_en_mask;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

    /* Sets interrupt source priority. */
    ipr_set_val    = p_rom->ipr_set_val;
    (*p_rom->pipr) = ipr_set_val; /* Sets TXI interrupt source priority register. */

    /* dummy read */
    if (*p_rom->pipr)
    {
        R_BSP_NOP();
    }
} /* End of function r_sci_iic_int_enable() */

/***********************************************************************************************************************
 * Function Name: sci_iic_set_frequency
 * Description  : Set IIC Frequency Processing.
 *                Sets SMR,BRR registers.
 * Arguments    : sci_iic_info_t * p_sci_iic_info     ;   IIC Information
 * Return Value : None
 **********************************************************************************************************************/
static void sci_iic_set_frequency(sci_iic_info_t * p_sci_iic_info)
{
    volatile uint16_t brr_n     = 32U; /* default: 64*2^(2*0-1) = 32 */
    volatile uint8_t  cks_value = 0U; /* default: PCLK/1 */
    volatile uint32_t brr_value = 0U;

    uint16_t brr_n_tmp;
    uint8_t  cks_value_tmp;

    sci_regs_t pregs = g_sci_iic_handles[p_sci_iic_info->ch_no]->prom->regs;

    R_BSP_VOLATILE_EVENACCESS const sci_iic_ch_rom_t * p_rom = g_sci_iic_handles[p_sci_iic_info->ch_no]->prom;

    /*  ---- Calculation BRR ---- */
    /* Macro definition does not have the type of declaration. The cast for the calculation of the floating point, 
     has been cast in the double type. After that, it is cast to type long to fit on the left-hand side. 
     Calculation results are not affected by casting, it is no problem. */
    brr_n_tmp = brr_n;

    /* Cast to double */
    brr_value = (uint32_t)((double)((double)((double)BSP_PCLKB_HZ / (brr_n_tmp *(p_rom->bitrate)))) - 0.1);

    /* Set clock source */
    /* WAIT_LOOP */
    while (brr_value > 255)
    {
        /* Counter over 0xff */
        switch (brr_n)
        {
            case 32 :
                brr_n     = 128; /* 64*(2^(2*1-1)) */
                cks_value = 1; /* clock select: PCLK/4 */
                break;

            case 128 :
                brr_n     = 512; /* 64*(2^(2*2-1))  */
                cks_value = 2; /* clock select: PCLK/16 */
                break;

            case 512 :
                brr_n     = 2048; /* 64*(2^(2*3-1)) */
                cks_value = 3; /* clock select: PCLK/64 */
                break;

            default :

                /* nothing to do */
                break;
        }

        /*  ---- Calculation BRR ---- */
        /* Macro definition does not have the type of declaration. The cast for the calculation of the floating point, 
         has been cast in the double type. After that, it is cast to type long to fit on the left-hand side. 
         Calculation results are not affected by casting, it is no problem. */
        brr_n_tmp = brr_n;

        /* Cast to double */
        brr_value = (uint32_t) ((double)(((double)BSP_PCLKB_HZ / (brr_n_tmp *(p_rom->bitrate)))) - 0.1);

        /* When the clock source of the on-chip baud rate generator is PCLK/64 and when the value
         of brr_value is greater than 255. */
        if ((3 == cks_value) && (255 < brr_value))
        {
            brr_value = 255;
        }
    }

    cks_value_tmp    = cks_value;
    pregs->SMR.BYTE |= cks_value_tmp; /* Sets SMR */
    pregs->BRR       = brr_value; /* Sets BRR */
} /* End of function sci_iic_set_frequency() */

/***********************************************************************************************************************
 * Function Name: r_sci_iic_mpc_setting
 * Description  : Set SCI_IIC multi-function pin controller.
 * Arguments    : uint8_t port_gr      ;   port group
 *                uint8_t pin_num      ;   pin number
 *                uint8_t set_value    ;   value of pin function select setting
 * Return Value : None
 **********************************************************************************************************************/
void r_sci_iic_mpc_setting(uint8_t port_gr, uint8_t pin_num, uint8_t set_value)
{
    R_BSP_VOLATILE_EVENACCESS uint8_t * const p_pmr = \
            (uint8_t *)((uint32_t)SCI_IIC_PRV_PMR_BASE_REG+(uint32_t)port_gr); /* Get p_pmr */

    R_BSP_VOLATILE_EVENACCESS uint8_t * const p_pfs = \
            (uint8_t *)((uint32_t)SCI_IIC_PRV_PFS_BASE_REG+(uint32_t)((port_gr*8)+pin_num)); /* Get p_pfs */

    if ((*p_pfs) != set_value)
    {
        (*p_pmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */
        R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */
        (*p_pfs) = set_value; /* Pin function select to "SSCL/SSDA" or "Hi-Z" pin. */
        R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */

        /* Verifies "set_value" (setting value for the PFS register). */
        /* If "set_value" is a value other than 0 (default), sets the pin mode control bit to be used 
         as I/O port for peripheral functions. */
        if (SCI_IIC_MPC_SSCL_INIT != set_value)
        {
            (*p_pmr) |= (1U << pin_num); /* Uses as SCI_IIC (SSCL/SSDA). */
        }

        /* dummy read */
        if (*p_pmr)
        {
            R_BSP_NOP();
        }
    }
} /* End of function r_sci_iic_mpc_setting() */

/***********************************************************************************************************************
 * Function Name: sci_iic_clear_ir_flag
 * Description  : Clears Interrupt Request Flag Processing.
 *                Clears interrupt request register.
 * Arguments    : sci_iic_info_t * p_sci_iic_info     ;   IIC Information
 * Return Value : None
 **********************************************************************************************************************/
static void sci_iic_clear_ir_flag(sci_iic_info_t * p_sci_iic_info)
{
    sci_regs_t pregs = g_sci_iic_handles[p_sci_iic_info->ch_no]->prom->regs;

    R_BSP_VOLATILE_EVENACCESS const sci_iic_ch_rom_t * p_rom = g_sci_iic_handles[p_sci_iic_info->ch_no]->prom;

    /* Checks IR flag. */
    /* If IR flag is set, clears IR flag. */
    if (SCI_IIC_IR_SET == (*p_rom->pir_txi))
    {
        /* Initializes ICIER->SCR register. */
        pregs->SCR.BYTE = SCI_IIC_SCR_INIT;

        /* WAIT_LOOP */
        while (SCI_IIC_SCR_INIT != pregs->SCR.BYTE)
        {
            /* nothing to do */
            R_BSP_NOP();
        }

        /* Clears TXI1 interrupt request register. */
        (*p_rom->pir_txi) = SCI_IIC_IR_CLR;

        /* dummy read */
        if (*p_rom->pir_txi)
        {
            R_BSP_NOP();
        }

        /* Re-initializes SCI_IIC register because cleared ICCR1.ICE bit. */
        /* Includes I/O register read operation at the end of the following function. */
        r_sci_iic_init_io_register(p_sci_iic_info);
    }
} /* End of function sci_iic_clear_ir_flag() */

    #if SCI_IIC_CFG_CH1_INCLUDED
/***********************************************************************************************************************
 * Function Name: sci_iic_int_sci_iic1_txi_isr
 * Description  : Interrupt TXI handler for channel 1.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT (sci_iic_int_sci_iic1_txi_isr, VECT_SCI1_TXI1)
R_BSP_ATTRIB_STATIC_INTERRUPT void sci_iic_int_sci_iic1_txi_isr(void)
{
    r_sci_iic_txi_isr_processing(SCI_IIC_NUM_CH1);

    /* Calls advance function */
    r_sci_iic_advance(g_sci_iic_handles[SCI_IIC_NUM_CH1]->psci_iic_info_ch);
} /* End of function sci_iic_int_sci_iic1_txi_isr() */
    #endif

    #if SCI_IIC_CFG_CH5_INCLUDED
/***********************************************************************************************************************
 * Function Name: sci_iic_int_sci_iic5_txi_isr
 * Description  : Interrupt TXI handler for channel 5.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT (sci_iic_int_sci_iic5_txi_isr, VECT_SCI5_TXI5)
R_BSP_ATTRIB_STATIC_INTERRUPT void sci_iic_int_sci_iic5_txi_isr (void)
{
    r_sci_iic_txi_isr_processing(SCI_IIC_NUM_CH5);

    /* Calls advance function */
    r_sci_iic_advance(g_sci_iic_handles[SCI_IIC_NUM_CH5]->psci_iic_info_ch);
} /* End of function sci_iic_int_sci_iic5_txi_isr() */
    #endif

    #if SCI_IIC_CFG_CH6_INCLUDED
/***********************************************************************************************************************
 * Function Name: sci_iic_int_sci_iic6_txi_isr
 * Description  : Interrupt TXI handler for channel 6.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT (sci_iic_int_sci_iic6_txi_isr, VECT_SCI6_TXI6)
R_BSP_ATTRIB_STATIC_INTERRUPT void sci_iic_int_sci_iic6_txi_isr (void)
{
    r_sci_iic_txi_isr_processing(SCI_IIC_NUM_CH6);

    /* Calls advance function */
    r_sci_iic_advance(g_sci_iic_handles[SCI_IIC_NUM_CH6]->psci_iic_info_ch);
} /* End of function sci_iic_int_sci_iic6_txi_isr() */
    #endif

    #if SCI_IIC_CFG_CH12_INCLUDED
/***********************************************************************************************************************
 * Function Name: sci_iic_int_sci_iic12_txi_isr
 * Description  : Interrupt TXI handler for channel 12.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT (sci_iic_int_sci_iic12_txi_isr, VECT_SCI12_TXI12)
R_BSP_ATTRIB_STATIC_INTERRUPT void sci_iic_int_sci_iic12_txi_isr (void)
{
    r_sci_iic_txi_isr_processing(SCI_IIC_NUM_CH12);

    /* Calls advance function */
    r_sci_iic_advance(g_sci_iic_handles[SCI_IIC_NUM_CH12]->psci_iic_info_ch);
} /* End of function sci_iic_int_sci_iic12_txi_isr() */
    #endif

    #if SCI_IIC_CFG_CH1_INCLUDED
/***********************************************************************************************************************
 * Function Name: sci_iic_int_sci_iic1_tei_isr
 * Description  : Interrupt TEI handler for channel 1.
 *                Types of interrupt requests transfer error or event generation.
 *              : The event generations are arbitration-lost, NACK detection, timeout detection, 
 *              : start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT (sci_iic_int_sci_iic1_tei_isr, VECT_SCI1_TEI1)
R_BSP_ATTRIB_STATIC_INTERRUPT void sci_iic_int_sci_iic1_tei_isr (void)
{
    r_sci_iic_tei_isr_processing(SCI_IIC_NUM_CH1);

    /* Calls advance function */
    r_sci_iic_advance(g_sci_iic_handles[SCI_IIC_NUM_CH1]->psci_iic_info_ch);
} /* End of function sci_iic_int_sci_iic1_tei_isr() */
    #endif

    #if SCI_IIC_CFG_CH5_INCLUDED
/***********************************************************************************************************************
 * Function Name: sci_iic_int_sci_iic5_tei_isr
 * Description  : Interrupt TEI handler for channel 5.
 *                Types of interrupt requests transfer error or event generation.
 *              : The event generations are arbitration-lost, NACK detection, timeout detection, 
 *              : start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT (sci_iic_int_sci_iic5_tei_isr, VECT_SCI5_TEI5)
R_BSP_ATTRIB_STATIC_INTERRUPT void sci_iic_int_sci_iic5_tei_isr (void)
{
    r_sci_iic_tei_isr_processing(SCI_IIC_NUM_CH5);

    /* Calls advance function */
    r_sci_iic_advance(g_sci_iic_handles[SCI_IIC_NUM_CH5]->psci_iic_info_ch);
} /* End of function sci_iic_int_sci_iic5_tei_isr() */
    #endif

    #if SCI_IIC_CFG_CH6_INCLUDED
/***********************************************************************************************************************
 * Function Name: sci_iic_int_sci_iic6_tei_isr
 * Description  : Interrupt TEI handler for channel 6.
 *                Types of interrupt requests transfer error or event generation.
 *              : The event generations are arbitration-lost, NACK detection, timeout detection, 
 *              : start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT (sci_iic_int_sci_iic6_tei_isr, VECT_SCI6_TEI6)
R_BSP_ATTRIB_STATIC_INTERRUPT void sci_iic_int_sci_iic6_tei_isr (void)
{
    r_sci_iic_tei_isr_processing(SCI_IIC_NUM_CH6);

    /* Calls advance function */
    r_sci_iic_advance(g_sci_iic_handles[SCI_IIC_NUM_CH6]->psci_iic_info_ch);
} /* End of function sci_iic_int_sci_iic6_tei_isr() */
    #endif

    #if SCI_IIC_CFG_CH12_INCLUDED
/***********************************************************************************************************************
 * Function Name: sci_iic_int_sci_iic12_tei_isr
 * Description  : Interrupt TEI handler for channel 12.
 *                Types of interrupt requests transfer error or event generation.
 *              : The event generations are arbitration-lost, NACK detection, timeout detection, 
 *              : start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT (sci_iic_int_sci_iic12_tei_isr, VECT_SCI12_TEI12)
R_BSP_ATTRIB_STATIC_INTERRUPT void sci_iic_int_sci_iic12_tei_isr (void)
{
    r_sci_iic_tei_isr_processing(SCI_IIC_NUM_CH12);

    /* Calls advance function */
    r_sci_iic_advance(g_sci_iic_handles[SCI_IIC_NUM_CH12]->psci_iic_info_ch);
} /* End of function sci_iic_int_sci_iic12_tei_isr() */
    #endif

#endif /* BSP_MCU_RX260 */

