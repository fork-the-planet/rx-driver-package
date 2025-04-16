/***********************************************************************************************************************
* Copyright (c) 2022 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_rsci_rx26t_data.c
* Description  : Functions for using RSCI on the RX26T device.
***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           15.08.2022 1.00    Initial Release
*           15.03.2025 2.71    Updated disclaimer
***********************************************************************************************************************/

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "platform.h"

#include "r_rsci_rx26t_private.h"

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

/* Asynchronous or Manchester */
/* BRR = (PCLK/(divisor * baud)) - 1 */
/* when abcs=0 & bgdm=0 & abcse =0, divisor = 64*pow(2,2n-1) */
/* when abcs=1 & bgdm=0 & abcse =0 OR abcs=0 & bgdm=1 & abcse =0, divisor = 32*pow(2,2n-1) */
/* when abcs=1 & bgdm=1 & abcse =0, divisor = 16*pow(2,2n-1) */
/* when abcs=(1 or 0) & bgdm= (1 or 0) & abcse =1, divisor = 12*pow(2,2n-1). */
/* In manchester mode, only ABCSE bit = 0 can be selected. */

#if (RSCI_CFG_ASYNC_INCLUDED || RSCI_CFG_MANC_INCLUDED)
/* NOTE: diff than RSCI async baud table, but should provide same results */
const baud_divisor_t rsci_async_baud[NUM_DIVISORS_ASYNC]=
{
    /* divisor result, abcs, bgdm, abcse, n */
    {6,    1, 1, 1, 0},
    {8,    1, 1, 0, 0},
    {16,   0, 1, 0, 0},
    {32,   0, 0, 0, 0},
    {64,   0, 1, 0, 1},
    {128,  0, 0, 0, 1},
    {256,  0, 1, 0, 2},
    {512,  0, 0, 0, 2},
    {1024, 0, 1, 0, 3},
    {2048, 0, 0, 0, 3}
};
#endif

/* Synchronous and Simple SPI */
/* BRR = (PCLK/(divisor * baud)) - 1 */
/* abcs=0, bdgm=0, divisor = 8*pow(2,2n-1) */

#if (RSCI_CFG_SSPI_INCLUDED || RSCI_CFG_SYNC_INCLUDED)
/* NOTE: Identical to RSCI sync baud table */
const baud_divisor_t rsci_sync_baud[NUM_DIVISORS_SYNC]=
{
    /* divisor result, abcs, bgdm, abcse, n */
    {4,   0, 0, 0, 0},
    {16,  0, 0, 0, 1},
    {64,  0, 0, 0, 2},
    {256, 0, 0, 0, 3}
};
#endif


/* CHANNEL MEMORY ALLOCATIONS */

#if RSCI_CFG_CH8_INCLUDED

/* rom info */
const rsci_ch_rom_t  g_rsci_ch8_rom = {(volatile struct st_rsci11 R_BSP_EVENACCESS_SFR *)&RSCI8,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR*)&SYSTEM.MSTPCRC.LONG, BIT27_MASK,
                                #if RSCI_CFG_TEI_INCLUDED
                                BSP_INT_SRC_BL1_RSCI8_TEI, rsci8_tei_isr,
                                #endif
                                BSP_INT_SRC_BL1_RSCI8_ERI, rsci8_eri_isr,
                                BIT24_MASK, BIT25_MASK,
                                &ICU.IPR[IPR_RSCI8_RXI].BYTE,
                                &ICU.IPR[IPR_RSCI8_TXI].BYTE,
                                &ICU.IR[IR_RSCI8_RXI].BYTE,
                                &ICU.IR[IR_RSCI8_TXI].BYTE,
                                &ICU.IER[IER_RSCI8_RXI].BYTE,
                                &ICU.IER[IER_RSCI8_TXI].BYTE,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR*)&ICU.GENBL1.LONG,
                                BIT4_MASK, BIT5_MASK,
                                (uint8_t)RSCI_CH8 /* Casting to uint8_t type is valid */
                                };

/* channel control block */
rsci_ch_ctrl_t   g_rsci_ch8_ctrl = {&g_rsci_ch8_rom, RSCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (RSCI_CFG_SSPI_INCLUDED || RSCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKB_HZ
                            #if RSCI_CFG_FIFO_INCLUDED
                            , false
                            , 0
                            , 0
                            , 0
                            , 0
                            #endif
                            #if RSCI_CFG_MANC_INCLUDED
                            , 0
                            , 0
                            , 0
                            , 0
                            , 0
                            , 0
                            #endif
                            };
#endif /* End of RSCI_CFG_CH8_INCLUDED */

#if RSCI_CFG_CH9_INCLUDED

/* rom info */
const rsci_ch_rom_t  g_rsci_ch9_rom = {(volatile struct st_rsci11 R_BSP_EVENACCESS_SFR *)&RSCI9,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR*)&SYSTEM.MSTPCRC.LONG, BIT26_MASK,
                                #if RSCI_CFG_TEI_INCLUDED
                                BSP_INT_SRC_BL1_RSCI9_TEI, rsci9_tei_isr,
                                #endif
                                BSP_INT_SRC_BL1_RSCI9_ERI, rsci9_eri_isr,
                                BIT26_MASK, BIT27_MASK,
                                &ICU.IPR[IPR_RSCI9_RXI].BYTE,
                                &ICU.IPR[IPR_RSCI9_TXI].BYTE,
                                &ICU.IR[IR_RSCI9_RXI].BYTE,
                                &ICU.IR[IR_RSCI9_TXI].BYTE,
                                &ICU.IER[IER_RSCI9_RXI].BYTE,
                                &ICU.IER[IER_RSCI9_TXI].BYTE,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR*)&ICU.GENBL1.LONG,
                                BIT6_MASK, BIT7_MASK,
                                (uint8_t)RSCI_CH9 /* Casting to uint8_t type is valid */
                                };

/* channel control block */
rsci_ch_ctrl_t   g_rsci_ch9_ctrl = {&g_rsci_ch9_rom, RSCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (RSCI_CFG_SSPI_INCLUDED || RSCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKB_HZ
                            #if RSCI_CFG_FIFO_INCLUDED
                            , false
                            , 0
                            , 0
                            , 0
                            , 0
                            #endif
                            #if RSCI_CFG_MANC_INCLUDED
                            , RSCI_CFG_CH9_RX_SEL_DECODING_POL
                            , RSCI_CFG_CH9_RX_PREFACE_LENGTH
                            , RSCI_CFG_CH9_RX_PREFACE_PATTERN
                            , RSCI_CFG_CH9_TX_SEL_ENCODING_POL
                            , RSCI_CFG_CH9_TX_PREFACE_LENGTH
                            , RSCI_CFG_CH9_TX_PREFACE_PATTERN
                            #endif
                            };
#endif /* End of RSCI_CFG_CH9_INCLUDED */


#if RSCI_CFG_CH11_INCLUDED

/* rom info */
const rsci_ch_rom_t  g_rsci_ch11_rom = {(volatile struct st_rsci11 R_BSP_EVENACCESS_SFR *)&RSCI11,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR*)&SYSTEM.MSTPCRC.LONG, BIT24_MASK,
                                #if RSCI_CFG_TEI_INCLUDED
                                BSP_INT_SRC_AL0_RSCI11_TEI, rsci11_tei_isr,
                                #endif
                                BSP_INT_SRC_AL0_RSCI11_ERI, rsci11_eri_isr,
                                BIT12_MASK, BIT13_MASK,
                                &ICU.IPR[IPR_RSCI11_RXI].BYTE,
                                &ICU.IPR[IPR_RSCI11_TXI].BYTE,
                                &ICU.IR[IR_RSCI11_RXI].BYTE,
                                &ICU.IR[IR_RSCI11_TXI].BYTE,
                                &ICU.IER[IER_RSCI11_RXI].BYTE,
                                &ICU.IER[IER_RSCI11_TXI].BYTE,
                                (volatile uint32_t R_BSP_EVENACCESS_SFR*)&ICU.GENAL0.LONG,
                                BIT2_MASK, BIT3_MASK,
                                (uint8_t)RSCI_CH11 /* Casting to uint8_t type is valid */
                                };

/* channel control block */
rsci_ch_ctrl_t   g_rsci_ch11_ctrl = {&g_rsci_ch11_rom, RSCI_MODE_OFF, 0, NULL, NULL, NULL, true
                            #if (RSCI_CFG_SSPI_INCLUDED || RSCI_CFG_SYNC_INCLUDED)
                            , true, 0, 0, false
                            #endif
                            , BSP_PCLKA_HZ
                            #if RSCI_CFG_FIFO_INCLUDED
                            , RSCI_CFG_CH11_FIFO_INCLUDED
                            , RSCI_CFG_CH11_RX_FIFO_THRESH
                            , RSCI_CFG_CH11_RX_FIFO_THRESH
                            , RSCI_CFG_CH11_TX_FIFO_THRESH
                            , RSCI_CFG_CH11_TX_FIFO_THRESH
                            #endif
                            #if RSCI_CFG_MANC_INCLUDED
                            , RSCI_CFG_CH11_RX_SEL_DECODING_POL
                            , RSCI_CFG_CH11_RX_PREFACE_LENGTH
                            , RSCI_CFG_CH11_RX_PREFACE_PATTERN
                            , RSCI_CFG_CH11_TX_SEL_ENCODING_POL
                            , RSCI_CFG_CH11_TX_PREFACE_LENGTH
                            , RSCI_CFG_CH11_TX_PREFACE_PATTERN
                            #endif
                            };
#endif /* End of RSCI_CFG_CH11_INCLUDED */



/* RSCI HANDLE-ARRAY DECLARATION */

const rsci_hdl_t g_rsci_handles[RSCI_NUM_CH] =
{
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
#if RSCI_CFG_CH8_INCLUDED
            &g_rsci_ch8_ctrl,
#else
            NULL,
#endif
#if RSCI_CFG_CH9_INCLUDED
            &g_rsci_ch9_ctrl,
#else
            NULL,
#endif
            NULL,
#if RSCI_CFG_CH11_INCLUDED
            &g_rsci_ch11_ctrl,
#else
            NULL,
#endif
};

