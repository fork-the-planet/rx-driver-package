/***********************************************************************************************************************
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_sci_rx64m.h
* Description  : Functions for using SCI on the RX64M device.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           05.04.2016 1.00    Initial Release.
*           20.05.2019 3.00    Added support for GNUC and ICCRX.
*           25.08.2020 3.60    Added feature using DTC/DMAC in SCI transfer.
*           31.03.2021 3.80    Updated macro definition enable and disable TXI, RXI, ERI, TEI.
*           31.03.2022 4.40    Added receive flag when using DTC/DMAC.
*                              Updated channel variables in struct st_sci_ch_rom.
*           15.03.2025 5.41    Updated disclaimer
***********************************************************************************************************************/

#ifndef SCI_RX64M_H
#define SCI_RX64M_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "../../r_sci_rx_private.h"

#if (SCI_CFG_ASYNC_INCLUDED)
#include "r_byteq_if.h"
#endif

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* SCI channel include Check */
#if (SCI_CFG_CH8_INCLUDED  != 0) || (SCI_CFG_CH9_INCLUDED  != 0) || \
    (SCI_CFG_CH10_INCLUDED != 0) || (SCI_CFG_CH11_INCLUDED != 0)
    #error "ERROR - Unsupported channel chosen in r_sci_config.h"
#endif

/* Mask of all active channels */
#define SCI_CFG_CH_INCLUDED_MASK ((SCI_CFG_CH0_INCLUDED << 0)   |   \
                                  (SCI_CFG_CH1_INCLUDED << 1)   |   \
                                  (SCI_CFG_CH2_INCLUDED << 2)   |   \
                                  (SCI_CFG_CH3_INCLUDED << 3)   |   \
                                  (SCI_CFG_CH4_INCLUDED << 4)   |   \
                                  (SCI_CFG_CH5_INCLUDED << 5)   |   \
                                  (SCI_CFG_CH6_INCLUDED << 6)   |   \
                                  (SCI_CFG_CH7_INCLUDED << 7)   |   \
                                  (SCI_CFG_CH12_INCLUDED << 12))

/* SCI SCR register masks */
#define SCI_SCR_TEI_MASK    (0x80U)     /* transmit interrupt enable */
#define SCI_SCR_REI_MASK    (0x40U)     /* receive interrupt enable */
#define SCI_SCR_TE_MASK     (0x20U)     /* transmitter enable */
#define SCI_SCR_RE_MASK     (0x10U)     /* receiver enable */
#define SCI_EN_XCVR_MASK    (SCI_SCR_RE_MASK | SCI_SCR_TE_MASK | SCI_SCR_REI_MASK | SCI_SCR_TEI_MASK)

/* SCI SSR register receiver error masks */
#define SCI_SSR_ORER_MASK         (0x20U)     /* overflow error */
#define SCI_SSR_FER_MASK          (0x10U)     /* framing error */
#define SCI_SSR_PER_MASK          (0x08U)     /* parity err */
#define SCI_RCVR_ERR_MASK         (SCI_SSR_ORER_MASK | SCI_SSR_FER_MASK | SCI_SSR_PER_MASK)
#define SCI_SSR_CLR_MASK          (0xC0U)     /* SSR register cleare mask (11000000b) */

/* Macros to enable and disable ICU interrupts */
#define ENABLE_RXI_INT      (R_BSP_BIT_SET(hdl->rom->icu_rxi, hdl->rom->rxi_bit_num))
#define DISABLE_RXI_INT     (R_BSP_BIT_CLEAR(hdl->rom->icu_rxi, hdl->rom->rxi_bit_num))
#define ENABLE_TXI_INT      (R_BSP_BIT_SET(hdl->rom->icu_txi, hdl->rom->txi_bit_num))
#define DISABLE_TXI_INT     (R_BSP_BIT_CLEAR(hdl->rom->icu_txi, hdl->rom->txi_bit_num))

#define ENABLE_ERI_INT      (R_BSP_BIT_SET((uint8_t*)(hdl->rom->icu_grp) + (hdl->rom->eri_bit_num >> 3), hdl->rom->eri_bit_num & 7))
#define DISABLE_ERI_INT     (R_BSP_BIT_CLEAR((uint8_t*)(hdl->rom->icu_grp) + (hdl->rom->eri_bit_num >> 3), hdl->rom->eri_bit_num & 7))
#define ENABLE_TEI_INT      (R_BSP_BIT_SET((uint8_t*)(hdl->rom->icu_grp) + (hdl->rom->tei_bit_num >> 3), hdl->rom->tei_bit_num & 7))
#define DISABLE_TEI_INT     (R_BSP_BIT_CLEAR((uint8_t*)(hdl->rom->icu_grp) + (hdl->rom->tei_bit_num >> 3), hdl->rom->tei_bit_num & 7))


/*****************************************************************************
Typedef definitions
******************************************************************************/

typedef struct st_scif_fifo_ctrl
{
    uint8_t     *p_tx_buf;            /* user's buffer */
    uint8_t     *p_rx_buf;            /* user's buffer */
    uint16_t    tx_cnt;             /* bytes remaining to add to FIFO */
    uint16_t    rx_cnt;             /* bytes waiting to receive from FIFO */
#if (TX_DTC_DMACA_ENABLE) || (RX_DTC_DMACA_ENABLE)
    uint8_t     *p_tx_fraction_buf;
    uint8_t     *p_rx_fraction_buf;
    uint16_t    tx_fraction;
    uint16_t    rx_fraction;
#endif
    uint16_t    total_length;       /* used for DTC in txi_handler */
} sci_fifo_ctrl_t;

/* CHANNEL CONTROL BLOCK */

/* ROM INFO */

typedef struct st_sci_ch_rom    /* SCI ROM info for channel control block */
{
    volatile  struct st_sci12 R_BSP_EVENACCESS_SFR  *regs;  /* base ptr to ch registers */
    volatile  uint32_t R_BSP_EVENACCESS_SFR *mstp;          /* ptr to mstp register */
    uint32_t                        stop_mask;      /* mstp mask to disable ch */
#if SCI_CFG_TEI_INCLUDED
    bsp_int_src_t                   tei_vector;
    bsp_int_cb_t                    tei_isr;
#endif
    bsp_int_src_t                   eri_vector;
    bsp_int_cb_t                    eri_isr;
    uint32_t                        tei_bit_num;    /* ICU IR and IEN bit number */
    uint32_t                        eri_bit_num;    /* ICU IR and IEN bit number */
    volatile  uint8_t R_BSP_EVENACCESS_SFR  *ipr_rxi;       /* ptr to IPR register */
    volatile  uint8_t R_BSP_EVENACCESS_SFR  *ipr_txi;       /* ptr to IPR register */
    volatile  uint8_t R_BSP_EVENACCESS_SFR  *ir_rxi;        /* ptr to RXI IR register */
    volatile  uint8_t R_BSP_EVENACCESS_SFR  *ir_txi;        /* ptr to TXI IR register */

    /* 
    * DO NOT use the enable/disable interrupt bits in the SCR 
    * register. Pending interrupts can be lost that way.
    */
    volatile  uint8_t R_BSP_EVENACCESS_SFR  *icu_rxi;       /* ptr to ICU register */
    volatile  uint8_t R_BSP_EVENACCESS_SFR  *icu_txi;
    volatile  uint32_t R_BSP_EVENACCESS_SFR *icu_grp;
    uint8_t                         rxi_bit_num;    /* ICU enable/disable rxi bit number */
    uint8_t                         txi_bit_num;    /* ICU enable/disable txi bit number */
    /*
        * In case using DTC/DMAC
     */
#if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
    uint8_t                         dtc_dmaca_tx_enable;
    uint8_t                         dtc_dmaca_rx_enable;
#endif
#if ((TX_DTC_DMACA_ENABLE & 0x01) || (RX_DTC_DMACA_ENABLE & 0x01))
    dtc_activation_source_t         dtc_tx_act_src;
    dtc_activation_source_t         dtc_rx_act_src;
#endif
#if ((TX_DTC_DMACA_ENABLE & 0x02) || (RX_DTC_DMACA_ENABLE & 0x02))
    dmaca_activation_source_t       dmaca_tx_act_src;
    dmaca_activation_source_t       dmaca_rx_act_src;
    uint8_t                         dmaca_tx_channel;
    uint8_t                         dmaca_rx_channel;
#endif
#if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
    uint8_t                         chan;
#endif
} sci_ch_rom_t;


/* CHANNEL CONTROL BLOCK */

typedef struct st_sci_ch_ctrl       /* SCI channel control (for handle) */
{
    sci_ch_rom_t const *rom;        /* pointer to rom info */
    sci_mode_t      mode;           /* operational mode */
    uint32_t        baud_rate;      /* baud rate */
    void          (*callback)(void *p_args); /* function ptr for rcvr errs */
    union
    {
#if (SCI_CFG_ASYNC_INCLUDED)
        byteq_hdl_t     que;        /* async transmit queue handle */
#endif
        uint8_t         *buf;       /* sspi/sync tx buffer ptr */
    } u_tx_data;
    union
    {
#if (SCI_CFG_ASYNC_INCLUDED)
        byteq_hdl_t     que;        /* async receive queue handle */
#endif
        uint8_t         *buf;       /* sspi/sync rx buffer ptr */
    } u_rx_data;
    bool            tx_idle;        /* TDR is empty (async); TSR is empty (sync/sspi) */
#if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
    bool            save_rx_data;   /* save the data that is clocked in */
    uint16_t        tx_cnt;         /* number of bytes to transmit */
    uint16_t        rx_cnt;         /* number of bytes to receive */
    bool            tx_dummy;       /* transmit dummy byte, not buffer */
#endif
    uint32_t        pclk_speed;     /* saved peripheral clock speed for break generation */
#if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
    bool                            rx_idle;
    uint8_t                         qindex_app_tx;
    uint8_t                         qindex_int_tx;
    uint8_t                         qindex_app_rx;
    uint8_t                         qindex_int_rx;
    sci_fifo_ctrl_t                 queue[2];
#endif
} sci_ch_ctrl_t;


/* BAUD DIVISOR INFO */

/* BRR = (PCLK/(divisor * baud)) - 1 */
/* when abcs=1, divisor = 32*pow(2,2n-1) */
/* when abcs=0, divisor = 64*pow(2,2n-1) */

typedef struct st_baud_divisor
{
    int16_t     divisor;    // clock divisor
    uint8_t     abcs;       // abcs value to get divisor
    uint8_t     bgdm;       // bdgm value to get divisor
    uint8_t     cks;        // cks  value to get divisor (cks = n)
} baud_divisor_t;

#define NUM_DIVISORS_ASYNC  (9)
#define NUM_DIVISORS_SYNC   (4)


/*****************************************************************************
Private global variables and functions
******************************************************************************/
#if (SCI_CFG_ASYNC_INCLUDED)
extern const baud_divisor_t async_baud[];
#endif
#if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
extern const baud_divisor_t sync_baud[];
#endif

#if SCI_CFG_TEI_INCLUDED
extern void sci0_tei0_isr(void *cb_args);
extern void sci1_tei1_isr(void *cb_args);
extern void sci2_tei2_isr(void *cb_args);
extern void sci3_tei3_isr(void *cb_args);
extern void sci4_tei4_isr(void *cb_args);
extern void sci5_tei5_isr(void *cb_args);
extern void sci6_tei6_isr(void *cb_args);
extern void sci7_tei7_isr(void *cb_args);
extern void sci12_tei12_isr(void *cb_args);
#endif

extern void sci0_eri0_isr(void *cb_args);
extern void sci1_eri1_isr(void *cb_args);
extern void sci2_eri2_isr(void *cb_args);
extern void sci3_eri3_isr(void *cb_args);
extern void sci4_eri4_isr(void *cb_args);
extern void sci5_eri5_isr(void *cb_args);
extern void sci6_eri6_isr(void *cb_args);
extern void sci7_eri7_isr(void *cb_args);
extern void sci12_eri12_isr(void *cb_args);

#if (SCI_CFG_CH0_INCLUDED)
extern const sci_ch_rom_t      ch0_rom;
extern sci_ch_ctrl_t           ch0_ctrl;
#endif

#if (SCI_CFG_CH1_INCLUDED)
extern const sci_ch_rom_t      ch1_rom;
extern sci_ch_ctrl_t           ch1_ctrl;
#endif

#if (SCI_CFG_CH2_INCLUDED)
extern const sci_ch_rom_t      ch2_rom;
extern sci_ch_ctrl_t           ch2_ctrl;
#endif

#if (SCI_CFG_CH3_INCLUDED)
extern const sci_ch_rom_t      ch3_rom;
extern sci_ch_ctrl_t           ch3_ctrl;
#endif

#if (SCI_CFG_CH4_INCLUDED)
extern const sci_ch_rom_t      ch4_rom;
extern sci_ch_ctrl_t           ch4_ctrl;
#endif

#if (SCI_CFG_CH5_INCLUDED)
extern const sci_ch_rom_t      ch5_rom;
extern sci_ch_ctrl_t           ch5_ctrl;
#endif

#if (SCI_CFG_CH6_INCLUDED)
extern const sci_ch_rom_t      ch6_rom;
extern sci_ch_ctrl_t           ch6_ctrl;
#endif

#if (SCI_CFG_CH7_INCLUDED)
extern const sci_ch_rom_t      ch7_rom;
extern sci_ch_ctrl_t           ch7_ctrl;
#endif

#if (SCI_CFG_CH12_INCLUDED)
extern const sci_ch_rom_t      ch12_rom;
extern sci_ch_ctrl_t           ch12_ctrl;
#endif

extern const sci_hdl_t g_sci_handles[];

extern void sci_init_register(sci_hdl_t const hdl);

#if (SCI_CFG_ASYNC_INCLUDED)
extern sci_err_t sci_async_cmds(sci_hdl_t const hdl,
                         sci_cmd_t const cmd,
                         void            *p_args);
#endif

#if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
extern sci_err_t sci_sync_cmds(sci_hdl_t const hdl,
                        sci_cmd_t const cmd,
                        void            *p_args);
#endif

extern sci_err_t sci_mcu_param_check(uint8_t const chan);

extern int32_t sci_init_bit_rate(sci_hdl_t const    hdl,
                          uint32_t const     pclk,
                          uint32_t const     baud);

extern void sci_initialize_ints(sci_hdl_t const hdl,
                                uint8_t const   priority);

extern void sci_disable_ints(sci_hdl_t const hdl);

#endif /* SCI_RX64M_H */

