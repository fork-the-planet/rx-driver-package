/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_sci_iic_rx110_private.h
 * Description  : Functions for using SCI_IIC on RX devices. 
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 22.09.2014 1.00     First Release
 *         : 15.11.2014 1.01     Add comment
 *         : 27.02.2015 1.60     Replaced the vector number with the macro defined in iodefine.h.
 *         : 01.10.2016 2.00     Fixed a program according to the Renesas coding rules.
 *         : 31.08.2017 2.20     Deleted definitions of PORT_PFS_OFFSET, PORT_ODR0_OFFSET, PORT_ODR1_OFFSET.
 *         : 20.05.2019 2.41     Added support for GNUC and ICCRX.
 *                               Fixed coding style.
 *         : 15.03.2025 2.81     Updated disclaimer
 **********************************************************************************************************************/
/* Guards against multiple inclusion */
#ifndef SCI_IIC_RX110_PRIVATE_H
    #define SCI_IIC_RX110_PRIVATE_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
/* Access to peripherals and board defines. */
    #include "platform.h"
    #ifdef BSP_MCU_RX110

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/*============================================================================*/
/*  Parameter check of Configuration Options                                  */
/*============================================================================*/
        #if (1 == SCI_IIC_CFG_CH0_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH0_INCLUDED - This channel is not supported by the current MCU."
        #endif

        #if (1 == SCI_IIC_CFG_CH2_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH2_INCLUDED - This channel is not supported by the current MCU."
        #endif

        #if (1 == SCI_IIC_CFG_CH3_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH3_INCLUDED - This channel is not supported by the current MCU."
        #endif

        #if (1 == SCI_IIC_CFG_CH4_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH4_INCLUDED - This channel is not supported by the current MCU."
        #endif

        #if (1 == SCI_IIC_CFG_CH6_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH6_INCLUDED - This channel is not supported by the current MCU."
        #endif

        #if (1 == SCI_IIC_CFG_CH7_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH7_INCLUDED - This channel is not supported by the current MCU."
        #endif

        #if (1 == SCI_IIC_CFG_CH8_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH8_INCLUDED - This channel is not supported by the current MCU."
        #endif

        #if (1 == SCI_IIC_CFG_CH9_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH9_INCLUDED - This channel is not supported by the current MCU."
        #endif

        #if (1 == SCI_IIC_CFG_CH10_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH10_INCLUDED - This channel is not supported by the current MCU."
        #endif

        #if (1 == SCI_IIC_CFG_CH11_INCLUDED)
            #error "ERROR - SCI_IIC_CFG_CH11_INCLUDED - This channel is not supported by the current MCU."
        #endif

/*----------------------------------------------------------------------------*/
/*   Define register setting.                                                 */
/*----------------------------------------------------------------------------*/
/* Sets to use multi-function pin controller. */
        #define SCI_IIC_MPC_SSDA_INIT       ((uint8_t)(0x00))   /* Pin function select to Hi-Z */
        #define SCI_IIC_MPC_SSCL_INIT       ((uint8_t)(0x00))   /* Pin function select to Hi-Z */

        #if SCI_IIC_CFG_CH1_INCLUDED
            #if ((SCI_IIC_CFG_CH1_SSDA_GP == PORTC_GR) && (SCI_IIC_CFG_CH1_SSDA_PIN == 7))
                #define SCI_IIC_MPC_SSDA1_ENABLE ((uint8_t)(0x0B))   /* Pin function select to SCI1 SSDA pin:b01011 */
            #else
                #define SCI_IIC_MPC_SSDA1_ENABLE ((uint8_t)(0x0A))   /* Pin function select to SCI1 SSDA pin:b01010 */
            #endif
            #if ((SCI_IIC_CFG_CH1_SSCL_GP == PORTC_GR) && (SCI_IIC_CFG_CH1_SSCL_PIN == 6))
                #define SCI_IIC_MPC_SSCL1_ENABLE ((uint8_t)(0x0B))   /* Pin function select to SCI1 SSCL pin:b01011 */
            #else
                #define SCI_IIC_MPC_SSCL1_ENABLE ((uint8_t)(0x0A))   /* Pin function select to SCI1 SSCL pin:b01010 */
            #endif
        #endif /* #ifdef SCI_IIC_CFG_CH1_INCLUDED */

        #if SCI_IIC_CFG_CH5_INCLUDED
            #define SCI_IIC_MPC_SSDA5_ENABLE    ((uint8_t)(0x0A))   /* Pin function select to SCI5 SSDA pin:b01010 */
            #define SCI_IIC_MPC_SSCL5_ENABLE    ((uint8_t)(0x0A))   /* Pin function select to SCI5 SSCL pin:b01010 */
        #endif /* #ifdef SCI_IIC_CFG_CH5_INCLUDED */

        #if SCI_IIC_CFG_CH12_INCLUDED
            #define SCI_IIC_MPC_SSDA12_ENABLE   ((uint8_t)(0x0C))   /* Pin function select to SCI12 SSDA pin:b01100 */
            #define SCI_IIC_MPC_SSCL12_ENABLE   ((uint8_t)(0x0C))   /* Pin function select to SCI12 SSCL pin:b01100 */
        #endif /* #ifdef SCI_IIC_CFG_CH12_INCLUDED */

/* Interrupt register setting */
        #define SCI_IIC_IR_CLR              ((uint8_t)(0x00))   /* Clears interrupt request register. */
        #define SCI_IIC_IR_SET              ((uint8_t)(0x01))   /* Sets interrupt request register. */

/* Common register setting */
        #define SCI_IIC_SMR_INIT            ((uint8_t)(0x00))   /* Initializes SMR. */

        #define SCI_IIC_SCR_INIT            ((uint8_t)(0x00))   /* Initializes SCR. */
        #define SCI_IIC_SCR_ENABLE          ((uint8_t)(0xB4))   /* Enable bit:TEIE,TIE,TE,RE bit */
        #define SCI_IIC_SCR_TE_RE           ((uint8_t)(0x30))   /* Enable bit:TE,RE bit */

        #define SCI_IIC_SCMR_INIT           ((uint8_t)(0xF2))   /* Initializes SCMR. */

        #define SCI_IIC_BRR_INIT            ((uint8_t)(0xFF))   /* Initializes BRR. */

        #define SCI_IIC_SEMR_INIT           ((uint8_t)(0x00))   /* Initializes SEMR. */

        #define SCI_IIC_SNFR_INIT           ((uint8_t)(0x00))   /* Initializes SNFR. */

        #define SCI_IIC_SIMR1_INIT          ((uint8_t)(0x00))   /* Initializes SIMR1. */

        #define SCI_IIC_SIMR2_INIT          ((uint8_t)(0x00))   /* Initializes SIMR2. */

        #define SCI_IIC_SIMR3_INIT          ((uint8_t)(0x00))   /* Initializes SIMR3. */

        #define SCI_IIC_SISR_INIT           ((uint8_t)(0x00))   /* Initializes SISR. */

        #define SCI_IIC_SPMR_INIT           ((uint8_t)(0x00))   /* Initializes SPMR. */

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* define sci register type */
typedef volatile struct st_sci1 R_BSP_EVENACCESS_SFR * sci_regs_t;

/*----------------------------------------------------------------------------*/
/*   Define internal sci_iic information structure type.                      */
/*----------------------------------------------------------------------------*/
/* Specifies register addresses and bits associated with the SCI, module-stop, and ICU. */
typedef struct st_sci_iic_ch_rom /* SCI ROM info for channel control block */
{
    mcu_lock_t                       hd_lock; /* Hardware Lock number */
    sci_regs_t                       regs; /* base ptr to ch registers */
    volatile uint32_t R_BSP_EVENACCESS_SFR * pmstp; /* ptr to mstp register */
    uint32_t                         stop_mask; /* mstp mask to disable ch */
    volatile uint8_t R_BSP_EVENACCESS_SFR * pipr; /* ptr to IPR register */
    volatile uint8_t R_BSP_EVENACCESS_SFR * pir_txi; /* ptr to TXI IR register */
    volatile uint8_t R_BSP_EVENACCESS_SFR * pir_tei; /* ptr to TEI IR register */
    uint8_t                          tei_ir_mask; /* bit mask to enable/disable txi INT in ICU */
    volatile uint8_t R_BSP_EVENACCESS_SFR * picu_txi;
    uint8_t                          txi_en_mask; /* bit mask to enable/disable txi INT in ICU */
    volatile uint8_t R_BSP_EVENACCESS_SFR * picu_tei;
    uint8_t                          tei_en_mask; /* bit mask to enable/disable tei INT in ICU */
    uint8_t                          ipr_set_val;
    uint8_t                          sscl_port_gr;
    uint8_t                          sscl_port_pin;
    uint8_t                          sscl_en_val;
    uint8_t                          ssda_port_gr;
    uint8_t                          ssda_port_pin;
    uint8_t                          ssda_en_val;
    uint8_t                          ssda_delay;
    uint32_t                         bitrate;
    uint8_t                          df_sel;
    uint8_t                          df_clk;
} sci_iic_ch_rom_t;

/* CHANNEL CONTROL BLOCK */
typedef struct st_sci_iic_ch_ctrl /* SCI channel control (for handle) */
{
    const sci_iic_ch_rom_t * prom; /* pointer to rom info */
    sci_iic_api_event_t      api_event; /* Event flag pointer */
    sci_iic_api_mode_t       api_mode; /* Internal mode of control protocol */
    sci_iic_api_status_t     api_n_status; /* Internal Status of Now */
    sci_iic_api_status_t     api_b_status; /* Internal Status of Before */
    uint8_t                  mode; /* Check I2C condition */
    sci_iic_info_t         * psci_iic_info_ch; /* Channel 1 SCI driver information */
} sci_iic_ch_ctrl_t;

typedef sci_iic_ch_ctrl_t * sci_iic_hdl_t;

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/
extern const sci_iic_hdl_t g_sci_iic_handles[SCI_IIC_NUM_CH_MAX];

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
extern void r_sci_iic_power_on (uint8_t channel);
extern void r_sci_iic_power_off (uint8_t channel);
extern void r_sci_iic_io_open (uint8_t port_gr, uint8_t pin_num);
extern void r_sci_iic_init_io_register (sci_iic_info_t * p_sci_iic_info);
extern void r_sci_iic_clear_io_register (sci_iic_info_t * p_sci_iic_info);
extern void r_sci_iic_int_disable (sci_iic_info_t * p_sci_iic_info);
extern void r_sci_iic_int_enable (sci_iic_info_t * p_sci_iic_info);
extern void r_sci_iic_mpc_setting (uint8_t port_gr, uint8_t pin_num, uint8_t set_value);

    #endif /* BSP_MCU_RX110 */
#endif /* SCI_IIC_RX110_PRIVATE_H */

