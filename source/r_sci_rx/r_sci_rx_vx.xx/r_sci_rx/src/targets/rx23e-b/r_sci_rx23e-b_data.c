/***********************************************************************************************************************
* Copyright (c) 2023 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_sci_rx23e-b_data.c
* Description  : Functions for using SCI on the RX23E-B device.
***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           29.05.2023 1.00    First Release.
*           15.03.2025 5.41    Updated disclaimer
***********************************************************************************************************************/

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "platform.h"

#include "r_sci_rx23e-b_private.h"

/*****************************************************************************
Typedef definitions
******************************************************************************/

/*****************************************************************************
Macro definitions
******************************************************************************/

/*****************************************************************************
Private global variables and functions
******************************************************************************/

/* BAUD DIVISOR INFO */

#if (SCI_CFG_ASYNC_INCLUDED)
/*
 * Asynchronous
 * BRR = (PCLK/(divisor * baud)) - 1
 * when: bgdm,abcs=11, divisor = 16*pow(2,2n-1)
 *       bgdm,abcs=01, divisor = 32*pow(2,2n-1)
 *       bgdm,abcs=10, divisor = 32*pow(2,2n-1)
 *       bgdm,abcs=00, divisor = 64*pow(2,2n-1)
 */
const baud_divisor_t async_baud[NUM_DIVISORS_ASYNC]=
{
    /* divisor result, bgdm, abcs, n */
    {8,    1, 1, 0},
    {16,   1, 0, 0},
    {32,   0, 0, 0},
    {64,   1, 0, 1},
    {128,  0, 0, 1},
    {256,  1, 0, 2},
    {512,  0, 0, 2},
    {1024, 1, 0, 3},
    {2048, 0, 0, 3}
};
#endif

#if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
/* Synchronous and Simple SPI */
/* BRR = (PCLK/(divisor * baud)) - 1 */
/* abcs=0, bdgm=0, divisor = 8*pow(2,2n-1) */

const baud_divisor_t sync_baud[NUM_DIVISORS_SYNC]=
{
    /* divisor result, abcs, bgdm, n */
    {4,   0, 0, 0},
    {16,  0, 0, 1},
    {64,  0, 0, 2},
    {256, 0, 0, 3}
};
#endif

/* CHANNEL MEMORY ALLOCATIONS */

#if SCI_CFG_CH0_INCLUDED

/* rom info */
const sci_ch_rom_t  ch0_rom = {(volatile struct st_sci12 R_BSP_EVENACCESS_SFR *)&SCI0,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRB.LONG, BIT31_MASK,
                                &ICU.IPR[IPR_SCI0_RXI0].BYTE,
                                &ICU.IR[IR_SCI0_RXI0].BYTE,
                                &ICU.IR[IR_SCI0_TXI0].BYTE,
                                &ICU.IR[IR_SCI0_TEI0].BYTE,
                                &ICU.IR[IR_SCI0_ERI0].BYTE,
                                &ICU.IER[IER_SCI0_RXI0].BYTE,
                                &ICU.IER[IER_SCI0_TXI0].BYTE,
                                &ICU.IER[IER_SCI0_TEI0].BYTE,
                                &ICU.IER[IER_SCI0_ERI0].BYTE,
                                SCI_BIT6, SCI_BIT7, SCI_BIT0, SCI_BIT1
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                , SCI_CFG_CH0_TX_DTC_DMACA_ENABLE
                                , SCI_CFG_CH0_RX_DTC_DMACA_ENABLE
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x01) || (RX_DTC_DMACA_ENABLE & 0x01))
                                , DTCE_SCI0_TXI0
                                , DTCE_SCI0_RXI0
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x02) || (RX_DTC_DMACA_ENABLE & 0x02))
                                , IR_SCI0_TXI0
                                , IR_SCI0_RXI0
                                , (uint8_t)SCI_CFG_CH0_TX_DMACA_CH_NUM
                                , (uint8_t)SCI_CFG_CH0_RX_DMACA_CH_NUM
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                /* Casting to uint8_t type is valid */
                                , (uint8_t)SCI_CH0
                                #endif
                                };
                                
/* channel control block */
sci_ch_ctrl_t   ch0_ctrl = {&ch0_rom                         
                            , SCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKB_HZ
                            #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                            , true, 0, 0, 0, 0, 0
                            #endif
                            };
#endif /* End of SCI_CFG_CH0_INCLUDED */


#if SCI_CFG_CH1_INCLUDED

/* rom info */
const sci_ch_rom_t  ch1_rom = {(volatile struct st_sci12 R_BSP_EVENACCESS_SFR *)&SCI1,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRB.LONG, BIT30_MASK,
                                &ICU.IPR[IPR_SCI1_RXI1].BYTE,
                                &ICU.IR[IR_SCI1_RXI1].BYTE,
                                &ICU.IR[IR_SCI1_TXI1].BYTE,
                                &ICU.IR[IR_SCI1_TEI1].BYTE,
                                &ICU.IR[IR_SCI1_ERI1].BYTE,
                                &ICU.IER[IER_SCI1_RXI1].BYTE,
                                &ICU.IER[IER_SCI1_TXI1].BYTE,
                                &ICU.IER[IER_SCI1_TEI1].BYTE,
                                &ICU.IER[IER_SCI1_ERI1].BYTE,
                                SCI_BIT2, SCI_BIT3, SCI_BIT4, SCI_BIT5
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                , SCI_CFG_CH1_TX_DTC_DMACA_ENABLE
                                , SCI_CFG_CH1_RX_DTC_DMACA_ENABLE
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x01) || (RX_DTC_DMACA_ENABLE & 0x01))
                                , DTCE_SCI1_TXI1
                                , DTCE_SCI1_RXI1
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x02) || (RX_DTC_DMACA_ENABLE & 0x02))
                                , IR_SCI1_TXI1
                                , IR_SCI1_RXI1
                                , (uint8_t)SCI_CFG_CH1_TX_DMACA_CH_NUM
                                , (uint8_t)SCI_CFG_CH1_RX_DMACA_CH_NUM
                                #endif
                                #if (TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE)
                                /* Casting to uint8_t type is valid */
                                , (uint8_t)SCI_CH1
                                #endif
                                };
                                
/* channel control block */
sci_ch_ctrl_t   ch1_ctrl = {&ch1_rom                        
                            , SCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKB_HZ
                            #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                            , true, 0, 0, 0, 0, 0
                            #endif
                            };
#endif /* End of SCI_CFG_CH1_INCLUDED */


#if SCI_CFG_CH5_INCLUDED

/* rom info */
const sci_ch_rom_t  ch5_rom = {(volatile struct st_sci12 R_BSP_EVENACCESS_SFR *)&SCI5,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRB.LONG, BIT26_MASK,
                                &ICU.IPR[IPR_SCI5_RXI5].BYTE,
                                &ICU.IR[IR_SCI5_RXI5].BYTE,
                                &ICU.IR[IR_SCI5_TXI5].BYTE,
                                &ICU.IR[IR_SCI5_TEI5].BYTE,
                                &ICU.IR[IR_SCI5_ERI5].BYTE,
                                &ICU.IER[IER_SCI5_RXI5].BYTE,
                                &ICU.IER[IER_SCI5_TXI5].BYTE,
                                &ICU.IER[IER_SCI5_TEI5].BYTE,
                                &ICU.IER[IER_SCI5_ERI5].BYTE,
                                SCI_BIT6, SCI_BIT7, SCI_BIT0, SCI_BIT1
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                , SCI_CFG_CH5_TX_DTC_DMACA_ENABLE
                                , SCI_CFG_CH5_RX_DTC_DMACA_ENABLE
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x01) || (RX_DTC_DMACA_ENABLE & 0x01))
                                , DTCE_SCI5_TXI5
                                , DTCE_SCI5_RXI5
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x02) || (RX_DTC_DMACA_ENABLE & 0x02))
                                , IR_SCI5_TXI5
                                , IR_SCI5_RXI5
                                , (uint8_t)SCI_CFG_CH5_TX_DMACA_CH_NUM
                                , (uint8_t)SCI_CFG_CH5_RX_DMACA_CH_NUM
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                /* Casting to uint8_t type is valid */
                                , (uint8_t)SCI_CH5
                                #endif
                                };
                                
/* channel control block */
sci_ch_ctrl_t   ch5_ctrl = {&ch5_rom
                            , SCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKB_HZ
                            #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                            , true, 0, 0, 0, 0, 0
                            #endif
                            };
#endif /* End of SCI_CFG_CH5_INCLUDED */


#if SCI_CFG_CH6_INCLUDED

/* rom info */
const sci_ch_rom_t  ch6_rom = {(volatile struct st_sci12 R_BSP_EVENACCESS_SFR *)&SCI6,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRB.LONG, BIT25_MASK,
                                &ICU.IPR[IPR_SCI6_RXI6].BYTE,
                                &ICU.IR[IR_SCI6_RXI6].BYTE,
                                &ICU.IR[IR_SCI6_TXI6].BYTE,
                                &ICU.IR[IR_SCI6_TEI6].BYTE,
                                &ICU.IR[IR_SCI6_ERI6].BYTE,
                                &ICU.IER[IER_SCI6_RXI6].BYTE,
                                &ICU.IER[IER_SCI6_TXI6].BYTE,
                                &ICU.IER[IER_SCI6_TEI6].BYTE,
                                &ICU.IER[IER_SCI6_ERI6].BYTE,
                                SCI_BIT2, SCI_BIT3, SCI_BIT4, SCI_BIT5
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                , SCI_CFG_CH6_TX_DTC_DMACA_ENABLE
                                , SCI_CFG_CH6_RX_DTC_DMACA_ENABLE
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x01) || (RX_DTC_DMACA_ENABLE & 0x01))
                                , DTCE_SCI6_TXI6
                                , DTCE_SCI6_RXI6
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x02) || (RX_DTC_DMACA_ENABLE & 0x02))
                                , IR_SCI6_TXI6
                                , IR_SCI6_RXI6
                                , (uint8_t)SCI_CFG_CH6_TX_DMACA_CH_NUM
                                , (uint8_t)SCI_CFG_CH6_RX_DMACA_CH_NUM
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                /* Casting to uint8_t type is valid */
                                , (uint8_t)SCI_CH6
                                #endif
                                };
                                
/* channel control block */
sci_ch_ctrl_t   ch6_ctrl = {&ch6_rom
                            , SCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKB_HZ
                            #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                            , true, 0, 0, 0, 0, 0
                            #endif
                            };
#endif /* End of SCI_CFG_CH6_INCLUDED */


#if SCI_CFG_CH8_INCLUDED

/* rom info */
const sci_ch_rom_t  ch8_rom = {(volatile struct st_sci12 R_BSP_EVENACCESS_SFR *)&SCI8,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRC.LONG, BIT27_MASK,
                                &ICU.IPR[IPR_SCI8_RXI8].BYTE,
                                &ICU.IR[IR_SCI8_RXI8].BYTE,
                                &ICU.IR[IR_SCI8_TXI8].BYTE,
                                &ICU.IR[IR_SCI8_TEI8].BYTE,
                                &ICU.IR[IR_SCI8_ERI8].BYTE,
                                &ICU.IER[IER_SCI8_RXI8].BYTE,
                                &ICU.IER[IER_SCI8_TXI8].BYTE,
                                &ICU.IER[IER_SCI8_TEI8].BYTE,
                                &ICU.IER[IER_SCI8_ERI8].BYTE,
                                SCI_BIT6, SCI_BIT7, SCI_BIT0, SCI_BIT1
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                , SCI_CFG_CH8_TX_DTC_DMACA_ENABLE
                                , SCI_CFG_CH8_RX_DTC_DMACA_ENABLE
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x01) || (RX_DTC_DMACA_ENABLE & 0x01))
                                , DTCE_SCI8_TXI8
                                , DTCE_SCI8_RXI8
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x02) || (RX_DTC_DMACA_ENABLE & 0x02))
                                , IR_SCI8_TXI8
                                , IR_SCI8_RXI8
                                , (uint8_t)SCI_CFG_CH8_TX_DMACA_CH_NUM
                                , (uint8_t)SCI_CFG_CH8_RX_DMACA_CH_NUM
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                /* Casting to uint8_t type is valid */
                                , (uint8_t)SCI_CH8
                                #endif
                                };
                                
/* channel control block */
sci_ch_ctrl_t   ch8_ctrl = {&ch8_rom
                            , SCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKB_HZ
                            #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                            , true, 0, 0, 0, 0, 0
                            #endif
                            };
#endif /* End of SCI_CFG_CH8_INCLUDED */


#if SCI_CFG_CH9_INCLUDED

/* rom info */
const sci_ch_rom_t  ch9_rom = {(volatile struct st_sci12 R_BSP_EVENACCESS_SFR *)&SCI9,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRC.LONG, BIT26_MASK,
                                &ICU.IPR[IPR_SCI9_RXI9].BYTE,
                                &ICU.IR[IR_SCI9_RXI9].BYTE,
                                &ICU.IR[IR_SCI9_TXI9].BYTE,
                                &ICU.IR[IR_SCI9_TEI9].BYTE,
                                &ICU.IR[IR_SCI9_ERI9].BYTE,
                                &ICU.IER[IER_SCI9_RXI9].BYTE,
                                &ICU.IER[IER_SCI9_TXI9].BYTE,
                                &ICU.IER[IER_SCI9_TEI9].BYTE,
                                &ICU.IER[IER_SCI9_ERI9].BYTE,
                                SCI_BIT2, SCI_BIT3, SCI_BIT4, SCI_BIT5
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                , SCI_CFG_CH9_TX_DTC_DMACA_ENABLE
                                , SCI_CFG_CH9_RX_DTC_DMACA_ENABLE
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x01) || (RX_DTC_DMACA_ENABLE & 0x01))
                                , DTCE_SCI9_TXI9
                                , DTCE_SCI9_RXI9
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x02) || (RX_DTC_DMACA_ENABLE & 0x02))
                                , IR_SCI9_TXI9
                                , IR_SCI9_RXI9
                                , (uint8_t)SCI_CFG_CH9_TX_DMACA_CH_NUM
                                , (uint8_t)SCI_CFG_CH9_RX_DMACA_CH_NUM
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                /* Casting to uint8_t type is valid */
                                , (uint8_t)SCI_CH9
                                #endif
                                };
                                
/* channel control block */
sci_ch_ctrl_t   ch9_ctrl = {&ch9_rom
                            , SCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKB_HZ
                            #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                            , true, 0, 0, 0, 0, 0
                            #endif
                            };
#endif /* End of SCI_CFG_CH9_INCLUDED */


#if SCI_CFG_CH12_INCLUDED

/* rom info */
const sci_ch_rom_t  ch12_rom = {(volatile struct st_sci12 R_BSP_EVENACCESS_SFR *)&SCI12,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR *)&SYSTEM.MSTPCRB.LONG, BIT4_MASK,
                                &ICU.IPR[IPR_SCI12_RXI12].BYTE,
                                &ICU.IR[IR_SCI12_RXI12].BYTE,
                                &ICU.IR[IR_SCI12_TXI12].BYTE,
                                &ICU.IR[IR_SCI12_TEI12].BYTE,
                                &ICU.IR[IR_SCI12_ERI12].BYTE,
                                &ICU.IER[IER_SCI12_RXI12].BYTE,
                                &ICU.IER[IER_SCI12_TXI12].BYTE,
                                &ICU.IER[IER_SCI12_TEI12].BYTE,
                                &ICU.IER[IER_SCI12_ERI12].BYTE,
                                SCI_BIT6, SCI_BIT7, SCI_BIT0, SCI_BIT1
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                , SCI_CFG_CH12_TX_DTC_DMACA_ENABLE
                                , SCI_CFG_CH12_RX_DTC_DMACA_ENABLE
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x01) || (RX_DTC_DMACA_ENABLE & 0x01))
                                , DTCE_SCI12_TXI12
                                , DTCE_SCI12_RXI12
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE & 0x02) || (RX_DTC_DMACA_ENABLE & 0x02))
                                , IR_SCI12_TXI12
                                , IR_SCI12_RXI12
                                , (uint8_t)SCI_CFG_CH12_TX_DMACA_CH_NUM
                                , (uint8_t)SCI_CFG_CH12_RX_DMACA_CH_NUM
                                #endif
                                #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                                /* Casting to uint8_t type is valid */
                                , (uint8_t)SCI_CH12
                                #endif
                                };
                                
/* channel control block */
sci_ch_ctrl_t   ch12_ctrl = {&ch12_rom
                            , SCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (SCI_CFG_SSPI_INCLUDED || SCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKB_HZ
                            #if ((TX_DTC_DMACA_ENABLE || RX_DTC_DMACA_ENABLE))
                            , true, 0, 0, 0, 0, 0
                            #endif
                            };
#endif /* End of SCI_CFG_CH12_INCLUDED */


/* SCI HANDLE-ARRAY DECLARATION */

const sci_hdl_t g_handles[SCI_NUM_CH] =
{
#if SCI_CFG_CH0_INCLUDED
            &ch0_ctrl,
#else
            NULL,
#endif
#if SCI_CFG_CH1_INCLUDED
            &ch1_ctrl,
#else
            NULL,
#endif

            NULL,        /* ch2 */
            NULL,        /* ch3 */
            NULL,        /* ch4 */

#if SCI_CFG_CH5_INCLUDED
            &ch5_ctrl,
#else
            NULL,
#endif
#if SCI_CFG_CH6_INCLUDED
            &ch6_ctrl,
#else
            NULL,
#endif

            NULL,        /* ch7 */

#if SCI_CFG_CH8_INCLUDED
            &ch8_ctrl,
#else
            NULL,
#endif
#if SCI_CFG_CH9_INCLUDED
            &ch9_ctrl,
#else
            NULL,
#endif

            NULL,        /* ch10 */
            NULL,        /* ch11 */

#if SCI_CFG_CH12_INCLUDED
            &ch12_ctrl
#else
            NULL
#endif
};

