/*
* Copyright (c) 2023(2024,2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/********************************************************************************/
/*                                                                              */
/* Device     : RX/RX200/RX261                                                  */
/* File Name  : iodefine.h                                                      */
/* Abstract   : Definition of I/O Register.                                     */
/* History    : V0.40  (2023-07-25)  [Hardware Manual Revision : 0.40]          */
/*            : V0.40A (2023-09-05)  [Hardware Manual Revision : 0.40]          */
/*            : V0.40B (2023-10-16)  [Hardware Manual Revision : 0.40]          */
/*            : V0.50  (2023-11-22)  [Hardware Manual Revision : 0.50]          */
/*            : V0.50A (2023-12-05)  [Hardware Manual Revision : 0.50]          */
/*            : V0.50B (2023-12-21)  [Hardware Manual Revision : 0.50]          */
/*            : V0.50C (2024-01-19)  [Hardware Manual Revision : 0.50]          */
/*            : V0.50D (2024-03-14)  [Hardware Manual Revision : 0.50]          */
/*            : V0.50E (2024-03-21)  [Hardware Manual Revision : 0.50]          */
/*            : V0.50F (2024-04-08)  [Hardware Manual Revision : 0.50]          */
/*            : V1.00  (2024-05-10)  [Hardware Manual Revision : 1.00]          */
/*            : V1.00A (2025-02-14)  [Hardware Manual Revision : 1.00]          */
/* Note       : This is a typical example.                                      */
/*                                                                              */
/********************************************************************************/
/*                                                                              */
/*  DESCRIPTION : Definition of ICU Register                                    */
/*  CPU TYPE    : RX261                                                         */
/*                                                                              */
/*  Usage : IR,DTCER,IER,IPR of ICU Register                                    */
/*     The following IR, DTCE, IEN, IPR macro functions simplify usage.         */
/*     The bit access operation is "Bit_Name(interrupt source,name)".           */
/*     A part of the name can be omitted.                                       */
/*     for example :                                                            */
/*       IR(BSC,BUSERR) = 0;     expands to :                                   */
/*         ICU.IR[16].BIT.IR = 0;                                               */
/*                                                                              */
/*       DTCE(ICU,IRQ0) = 1;     expands to :                                   */
/*         ICU.DTCER[64].BIT.DTCE = 1;                                          */
/*                                                                              */
/*       IEN(CMT0,CMI0) = 1;     expands to :                                   */
/*         ICU.IER[0x03].BIT.IEN4 = 1;                                          */
/*                                                                              */
/*       IPR(RSCI0,ERI) = 3;     expands to :                                   */
/*       IPR(RSCI0,   ) = 3;     // RSCI0 uses single IPR for all sources.      */
/*         ICU.IPR[214].BIT.IPR = 3;                                            */
/*                                                                              */
/*  Usage : #pragma interrupt Function_Identifier(vect=**)                      */
/*     The number of vector is "(interrupt source, name)".                      */
/*     for example :                                                            */
/*       #pragma interrupt INT_IRQ0(vect=VECT(ICU,IRQ0))          expands to :  */
/*         #pragma interrupt INT_IRQ0(vect=64)                                  */
/*       #pragma interrupt INT_CMT0_CMI0(vect=VECT(CMT0,CMI0))    expands to :  */
/*         #pragma interrupt INT_CMT0_CMI0(vect=28)                             */
/*                                                                              */
/*  Usage : MSTPCRA,MSTPCRB,MSTPCRC of SYSTEM Register                          */
/*     The bit access operation is "MSTP(name)".                                */
/*     The name that can be used is a macro name defined with "iodefine.h".     */
/*     for example :                                                            */
/*       MSTP(TMR2) = 0;    // TMR2,TMR3,TMR23                    expands to :  */
/*         SYSTEM.MSTPCRA.BIT.MSTPA4  = 0;                                      */
/*       MSTP(CMT3) = 0;    // CMT2,CMT3                          expands to :  */
/*         SYSTEM.MSTPCRA.BIT.MSTPA14 = 0;                                      */
/*                                                                              */
/*                                                                              */
/********************************************************************************/
#ifndef __RX261IODEFINE_HEADER__
#define __RX261IODEFINE_HEADER__

#define	IEN_BSC_BUSERR		IEN0
#define	IEN_RAM_RAMERR		IEN2
#define	IEN_FCU_FRDYI		IEN7
#define	IEN_ICU_SWINT		IEN3
#define	IEN_CMT0_CMI0		IEN4
#define	IEN_CMT1_CMI1		IEN5
#define	IEN_CMT2_CMI2		IEN6
#define	IEN_CMT3_CMI3		IEN7
#define	IEN_CAC_FERRF		IEN0
#define	IEN_CAC_MENDF		IEN1
#define	IEN_CAC_OVFF		IEN2
#define	IEN_USB0_D0FIFO0	IEN4
#define	IEN_USB0_D1FIFO0	IEN5
#define	IEN_USB0_USBI0		IEN6
#define	IEN_POEG_POEGGAI	IEN0
#define	IEN_POEG_POEGGBI	IEN1
#define	IEN_POEG_POEGGCI	IEN2
#define	IEN_POEG_POEGGDI	IEN3
#define	IEN_RSPI0_SPEI0		IEN4
#define	IEN_RSPI0_SPRI0		IEN5
#define	IEN_RSPI0_SPTI0		IEN6
#define	IEN_RSPI0_SPII0		IEN7
#define	IEN_DOC_DOPCF		IEN1
#define	IEN_CMPB_CMPB0		IEN2
#define	IEN_CMPB_CMPB1		IEN3
#define	IEN_CTSU_CTSUWR		IEN4
#define	IEN_CTSU_CTSURD		IEN5
#define	IEN_CTSU_CTSUFN		IEN6
#define	IEN_RTC_CUP			IEN7
#define	IEN_ICU_IRQ0		IEN0
#define	IEN_ICU_IRQ1		IEN1
#define	IEN_ICU_IRQ2		IEN2
#define	IEN_ICU_IRQ3		IEN3
#define	IEN_ICU_IRQ4		IEN4
#define	IEN_ICU_IRQ5		IEN5
#define	IEN_ICU_IRQ6		IEN6
#define	IEN_ICU_IRQ7		IEN7
#define	IEN_ELC_ELSR8I		IEN0
#define	IEN_SYSTEM_SNZI		IEN1
#define	IEN_LVD_LVD1		IEN0
#define	IEN_LVD_LVD2		IEN1
#define	IEN_USB0_USBR0		IEN2
#define	IEN_RTC_ALM			IEN4
#define	IEN_RTC_PRD			IEN5
#define	IEN_REMC0_REMCI0	IEN6
#define	IEN_S12AD_S12ADI0	IEN6
#define	IEN_S12AD_GBADI		IEN7
#define	IEN_ELC_ELSR18I		IEN2
#define	IEN_ELC_ELSR19I		IEN3
#define	IEN_GPTW0_GTCIA0	IEN4
#define	IEN_GPTW0_GTCIB0	IEN5
#define	IEN_GPTW0_GTCIC0	IEN6
#define	IEN_GPTW0_GTCID0	IEN7
#define	IEN_GPTW0_GTCIE0	IEN0
#define	IEN_GPTW0_GTCIF0	IEN1
#define	IEN_GPTW0_GTCIV0	IEN2
#define	IEN_GPTW0_GTCIU0	IEN3
#define	IEN_GPTW1_GTCIA1	IEN4
#define	IEN_GPTW1_GTCIB1	IEN5
#define	IEN_GPTW1_GTCIC1	IEN6
#define	IEN_GPTW1_GTCID1	IEN7
#define	IEN_GPTW1_GTCIE1	IEN0
#define	IEN_GPTW1_GTCIF1	IEN1
#define	IEN_GPTW1_GTCIV1	IEN2
#define	IEN_GPTW1_GTCIU1	IEN3
#define	IEN_GPTW2_GTCIA2	IEN4
#define	IEN_GPTW2_GTCIB2	IEN5
#define	IEN_GPTW2_GTCIC2	IEN6
#define	IEN_GPTW2_GTCID2	IEN7
#define	IEN_GPTW2_GTCIE2	IEN0
#define	IEN_GPTW2_GTCIF2	IEN1
#define	IEN_GPTW2_GTCIV2	IEN2
#define	IEN_GPTW2_GTCIU2	IEN3
#define	IEN_GPTW3_GTCIA3	IEN4
#define	IEN_GPTW3_GTCIB3	IEN5
#define	IEN_GPTW3_GTCIC3	IEN6
#define	IEN_GPTW3_GTCID3	IEN7
#define	IEN_GPTW3_GTCIE3	IEN0
#define	IEN_GPTW3_GTCIF3	IEN1
#define	IEN_GPTW3_GTCIV3	IEN2
#define	IEN_GPTW3_GTCIU3	IEN3
#define	IEN_GPTW4_GTCIA4	IEN4
#define	IEN_GPTW4_GTCIB4	IEN5
#define	IEN_GPTW4_GTCIC4	IEN6
#define	IEN_GPTW4_GTCID4	IEN7
#define	IEN_GPTW4_GTCIE4	IEN0
#define	IEN_GPTW4_GTCIF4	IEN1
#define	IEN_GPTW4_GTCIV4	IEN2
#define	IEN_GPTW4_GTCIU4	IEN3
#define	IEN_GPTW5_GTCIA5	IEN4
#define	IEN_GPTW5_GTCIB5	IEN5
#define	IEN_GPTW5_GTCIC5	IEN6
#define	IEN_GPTW5_GTCID5	IEN7
#define	IEN_GPTW5_GTCIE5	IEN0
#define	IEN_GPTW5_GTCIF5	IEN1
#define	IEN_GPTW5_GTCIV5	IEN2
#define	IEN_GPTW5_GTCIU5	IEN3
#define	IEN_GPTW6_GTCIA6	IEN4
#define	IEN_GPTW6_GTCIB6	IEN5
#define	IEN_GPTW6_GTCIC6	IEN6
#define	IEN_GPTW6_GTCID6	IEN7
#define	IEN_GPTW6_GTCIE6	IEN0
#define	IEN_GPTW6_GTCIF6	IEN1
#define	IEN_GPTW6_GTCIV6	IEN2
#define	IEN_GPTW6_GTCIU6	IEN3
#define	IEN_GPTW7_GTCIA7	IEN4
#define	IEN_GPTW7_GTCIB7	IEN5
#define	IEN_GPTW7_GTCIC7	IEN6
#define	IEN_GPTW7_GTCID7	IEN7
#define	IEN_GPTW7_GTCIE7	IEN0
#define	IEN_GPTW7_GTCIF7	IEN1
#define	IEN_GPTW7_GTCIV7	IEN2
#define	IEN_GPTW7_GTCIU7	IEN3
#define	IEN_TMR0_CMIA0		IEN6
#define	IEN_TMR0_CMIB0		IEN7
#define	IEN_TMR0_OVI0		IEN0
#define	IEN_TMR1_CMIA1		IEN1
#define	IEN_TMR1_CMIB1		IEN2
#define	IEN_TMR1_OVI1		IEN3
#define	IEN_TMR2_CMIA2		IEN4
#define	IEN_TMR2_CMIB2		IEN5
#define	IEN_TMR2_OVI2		IEN6
#define	IEN_TMR3_CMIA3		IEN7
#define	IEN_TMR3_CMIB3		IEN0
#define	IEN_TMR3_OVI3		IEN1
#define	IEN_CANFD_RFRI		IEN2
#define	IEN_CANFD_GLEI		IEN3
#define	IEN_CANFD_RMRI		IEN4
#define	IEN_CANFD_RFDREQ0	IEN5
#define	IEN_CANFD_RFDREQ1	IEN6
#define	IEN_CANFD_EC1EI		IEN7
#define	IEN_CANFD_EC2EI		IEN0
#define	IEN_CANFD_ECOVI		IEN1
#define	IEN_CANFD0_CHTI		IEN2
#define	IEN_CANFD0_CHEI		IEN3
#define	IEN_CANFD0_CFRI		IEN4
#define	IEN_CANFD0_CFDREQ0	IEN5
#define	IEN_DMAC_DMAC0I		IEN6
#define	IEN_DMAC_DMAC1I		IEN7
#define	IEN_DMAC_DMAC2I		IEN0
#define	IEN_DMAC_DMAC3I		IEN1
#define	IEN_RSIP_PROC_BUSY	IEN2
#define	IEN_RSIP_ROMOK		IEN3
#define	IEN_RSIP_LONG_PLG	IEN4
#define	IEN_RSIP_TEST_BUSY	IEN5
#define	IEN_RSIP_WRRDY0		IEN6
#define	IEN_RSIP_WRRDY2		IEN7
#define	IEN_RSIP_RDRDY0		IEN0
#define	IEN_RSIP_INTEGRATE_RDRDY	IEN1
#define	IEN_RSIP_INTEGRATE_WRRDY	IEN2
#define	IEN_RSIP_ECCERR		IEN3
#define	IEN_RSCI9_BFD		IEN4
#define	IEN_RSCI9_AED		IEN5
#define	IEN_RSCI0_ERI		IEN6
#define	IEN_RSCI0_RXI		IEN7
#define	IEN_RSCI0_TXI		IEN0
#define	IEN_RSCI0_TEI		IEN1
#define	IEN_SCI1_ERI1		IEN2
#define	IEN_SCI1_RXI1		IEN3
#define	IEN_SCI1_TXI1		IEN4
#define	IEN_SCI1_TEI1		IEN5
#define	IEN_SCI5_ERI5		IEN6
#define	IEN_SCI5_RXI5		IEN7
#define	IEN_SCI5_TXI5		IEN0
#define	IEN_SCI5_TEI5		IEN1
#define	IEN_SCI6_ERI6		IEN2
#define	IEN_SCI6_RXI6		IEN3
#define	IEN_SCI6_TXI6		IEN4
#define	IEN_SCI6_TEI6		IEN5
#define	IEN_RSCI8_ERI		IEN6
#define	IEN_RSCI8_RXI		IEN7
#define	IEN_RSCI8_TXI		IEN0
#define	IEN_RSCI8_TEI		IEN1
#define	IEN_RSCI9_ERI		IEN2
#define	IEN_RSCI9_RXI		IEN3
#define	IEN_RSCI9_TXI		IEN4
#define	IEN_RSCI9_TEI		IEN5
#define	IEN_SCI12_ERI12		IEN6
#define	IEN_SCI12_RXI12		IEN7
#define	IEN_SCI12_TXI12		IEN0
#define	IEN_SCI12_TEI12		IEN1
#define	IEN_SCI12_SCIX0		IEN2
#define	IEN_SCI12_SCIX1		IEN3
#define	IEN_SCI12_SCIX2		IEN4
#define	IEN_SCI12_SCIX3		IEN5
#define	IEN_RIIC0_EEI0		IEN6
#define	IEN_RIIC0_RXI0		IEN7
#define	IEN_RIIC0_TXI0		IEN0
#define	IEN_RIIC0_TEI0		IEN1
#define	IEN_LPT_LPTCMI1		IEN7

#define	VECT_BSC_BUSERR		16
#define	VECT_RAM_RAMERR		18
#define	VECT_FCU_FRDYI		23
#define	VECT_ICU_SWINT		27
#define	VECT_CMT0_CMI0		28
#define	VECT_CMT1_CMI1		29
#define	VECT_CMT2_CMI2		30
#define	VECT_CMT3_CMI3		31
#define	VECT_CAC_FERRF		32
#define	VECT_CAC_MENDF		33
#define	VECT_CAC_OVFF		34
#define	VECT_USB0_D0FIFO0	36
#define	VECT_USB0_D1FIFO0	37
#define	VECT_USB0_USBI0		38
#define	VECT_POEG_POEGGAI	40
#define	VECT_POEG_POEGGBI	41
#define	VECT_POEG_POEGGCI	42
#define	VECT_POEG_POEGGDI	43
#define	VECT_RSPI0_SPEI0	44
#define	VECT_RSPI0_SPRI0	45
#define	VECT_RSPI0_SPTI0	46
#define	VECT_RSPI0_SPII0	47
#define	VECT_DOC_DOPCF		57
#define	VECT_CMPB_CMPB0		58
#define	VECT_CMPB_CMPB1		59
#define	VECT_CTSU_CTSUWR	60
#define	VECT_CTSU_CTSURD	61
#define	VECT_CTSU_CTSUFN	62
#define	VECT_RTC_CUP		63
#define	VECT_ICU_IRQ0		64
#define	VECT_ICU_IRQ1		65
#define	VECT_ICU_IRQ2		66
#define	VECT_ICU_IRQ3		67
#define	VECT_ICU_IRQ4		68
#define	VECT_ICU_IRQ5		69
#define	VECT_ICU_IRQ6		70
#define	VECT_ICU_IRQ7		71
#define	VECT_ELC_ELSR8I		80
#define	VECT_SYSTEM_SNZI	81
#define	VECT_LVD_LVD1		88
#define	VECT_LVD_LVD2		89
#define	VECT_USB0_USBR0		90
#define	VECT_RTC_ALM		92
#define	VECT_RTC_PRD		93
#define	VECT_REMC0_REMCI0	94
#define	VECT_S12AD_S12ADI0	102
#define	VECT_S12AD_GBADI	103
#define	VECT_ELC_ELSR18I	106
#define	VECT_ELC_ELSR19I	107
#define	VECT_GPTW0_GTCIA0	108
#define	VECT_GPTW0_GTCIB0	109
#define	VECT_GPTW0_GTCIC0	110
#define	VECT_GPTW0_GTCID0	111
#define	VECT_GPTW0_GTCIE0	112
#define	VECT_GPTW0_GTCIF0	113
#define	VECT_GPTW0_GTCIV0	114
#define	VECT_GPTW0_GTCIU0	115
#define	VECT_GPTW1_GTCIA1	116
#define	VECT_GPTW1_GTCIB1	117
#define	VECT_GPTW1_GTCIC1	118
#define	VECT_GPTW1_GTCID1	119
#define	VECT_GPTW1_GTCIE1	120
#define	VECT_GPTW1_GTCIF1	121
#define	VECT_GPTW1_GTCIV1	122
#define	VECT_GPTW1_GTCIU1	123
#define	VECT_GPTW2_GTCIA2	124
#define	VECT_GPTW2_GTCIB2	125
#define	VECT_GPTW2_GTCIC2	126
#define	VECT_GPTW2_GTCID2	127
#define	VECT_GPTW2_GTCIE2	128
#define	VECT_GPTW2_GTCIF2	129
#define	VECT_GPTW2_GTCIV2	130
#define	VECT_GPTW2_GTCIU2	131
#define	VECT_GPTW3_GTCIA3	132
#define	VECT_GPTW3_GTCIB3	133
#define	VECT_GPTW3_GTCIC3	134
#define	VECT_GPTW3_GTCID3	135
#define	VECT_GPTW3_GTCIE3	136
#define	VECT_GPTW3_GTCIF3	137
#define	VECT_GPTW3_GTCIV3	138
#define	VECT_GPTW3_GTCIU3	139
#define	VECT_GPTW4_GTCIA4	140
#define	VECT_GPTW4_GTCIB4	141
#define	VECT_GPTW4_GTCIC4	142
#define	VECT_GPTW4_GTCID4	143
#define	VECT_GPTW4_GTCIE4	144
#define	VECT_GPTW4_GTCIF4	145
#define	VECT_GPTW4_GTCIV4	146
#define	VECT_GPTW4_GTCIU4	147
#define	VECT_GPTW5_GTCIA5	148
#define	VECT_GPTW5_GTCIB5	149
#define	VECT_GPTW5_GTCIC5	150
#define	VECT_GPTW5_GTCID5	151
#define	VECT_GPTW5_GTCIE5	152
#define	VECT_GPTW5_GTCIF5	153
#define	VECT_GPTW5_GTCIV5	154
#define	VECT_GPTW5_GTCIU5	155
#define	VECT_GPTW6_GTCIA6	156
#define	VECT_GPTW6_GTCIB6	157
#define	VECT_GPTW6_GTCIC6	158
#define	VECT_GPTW6_GTCID6	159
#define	VECT_GPTW6_GTCIE6	160
#define	VECT_GPTW6_GTCIF6	161
#define	VECT_GPTW6_GTCIV6	162
#define	VECT_GPTW6_GTCIU6	163
#define	VECT_GPTW7_GTCIA7	164
#define	VECT_GPTW7_GTCIB7	165
#define	VECT_GPTW7_GTCIC7	166
#define	VECT_GPTW7_GTCID7	167
#define	VECT_GPTW7_GTCIE7	168
#define	VECT_GPTW7_GTCIF7	169
#define	VECT_GPTW7_GTCIV7	170
#define	VECT_GPTW7_GTCIU7	171
#define	VECT_TMR0_CMIA0		174
#define	VECT_TMR0_CMIB0		175
#define	VECT_TMR0_OVI0		176
#define	VECT_TMR1_CMIA1		177
#define	VECT_TMR1_CMIB1		178
#define	VECT_TMR1_OVI1		179
#define	VECT_TMR2_CMIA2		180
#define	VECT_TMR2_CMIB2		181
#define	VECT_TMR2_OVI2		182
#define	VECT_TMR3_CMIA3		183
#define	VECT_TMR3_CMIB3		184
#define	VECT_TMR3_OVI3		185
#define	VECT_CANFD_RFRI		186
#define	VECT_CANFD_GLEI		187
#define	VECT_CANFD_RMRI		188
#define	VECT_CANFD_RFDREQ0	189
#define	VECT_CANFD_RFDREQ1	190
#define	VECT_CANFD_EC1EI	191
#define	VECT_CANFD_EC2EI	192
#define	VECT_CANFD_ECOVI	193
#define	VECT_CANFD0_CHTI	194
#define	VECT_CANFD0_CHEI	195
#define	VECT_CANFD0_CFRI	196
#define	VECT_CANFD0_CFDREQ0	197
#define	VECT_DMAC_DMAC0I	198
#define	VECT_DMAC_DMAC1I	199
#define	VECT_DMAC_DMAC2I	200
#define	VECT_DMAC_DMAC3I	201
#define	VECT_RSIP_PROC_BUSY	202
#define	VECT_RSIP_ROMOK		203
#define	VECT_RSIP_LONG_PLG	204
#define	VECT_RSIP_TEST_BUSY	205
#define	VECT_RSIP_WRRDY0	206
#define	VECT_RSIP_WRRDY2	207
#define	VECT_RSIP_RDRDY0	208
#define	VECT_RSIP_INTEGRATE_RDRDY	209
#define	VECT_RSIP_INTEGRATE_WRRDY	210
#define	VECT_RSIP_ECCERR	211
#define	VECT_RSCI9_BFD		212
#define	VECT_RSCI9_AED		213
#define	VECT_RSCI0_ERI		214
#define	VECT_RSCI0_RXI		215
#define	VECT_RSCI0_TXI		216
#define	VECT_RSCI0_TEI		217
#define	VECT_SCI1_ERI1		218
#define	VECT_SCI1_RXI1		219
#define	VECT_SCI1_TXI1		220
#define	VECT_SCI1_TEI1		221
#define	VECT_SCI5_ERI5		222
#define	VECT_SCI5_RXI5		223
#define	VECT_SCI5_TXI5		224
#define	VECT_SCI5_TEI5		225
#define	VECT_SCI6_ERI6		226
#define	VECT_SCI6_RXI6		227
#define	VECT_SCI6_TXI6		228
#define	VECT_SCI6_TEI6		229
#define	VECT_RSCI8_ERI		230
#define	VECT_RSCI8_RXI		231
#define	VECT_RSCI8_TXI		232
#define	VECT_RSCI8_TEI		233
#define	VECT_RSCI9_ERI		234
#define	VECT_RSCI9_RXI		235
#define	VECT_RSCI9_TXI		236
#define	VECT_RSCI9_TEI		237
#define	VECT_SCI12_ERI12	238
#define	VECT_SCI12_RXI12	239
#define	VECT_SCI12_TXI12	240
#define	VECT_SCI12_TEI12	241
#define	VECT_SCI12_SCIX0	242
#define	VECT_SCI12_SCIX1	243
#define	VECT_SCI12_SCIX2	244
#define	VECT_SCI12_SCIX3	245
#define	VECT_RIIC0_EEI0		246
#define	VECT_RIIC0_RXI0		247
#define	VECT_RIIC0_TXI0		248
#define	VECT_RIIC0_TEI0		249
#define	VECT_LPT_LPTCMI1	255

#define	MSTP_DMAC	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DMAC0	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DMAC1	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DMAC2	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DMAC3	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DTC	SYSTEM.MSTPCRA.BIT.MSTPA28
#define	MSTP_DA		SYSTEM.MSTPCRA.BIT.MSTPA19
#define	MSTP_S12AD	SYSTEM.MSTPCRA.BIT.MSTPA17
#define	MSTP_CMT0	SYSTEM.MSTPCRA.BIT.MSTPA15
#define	MSTP_CMT1	SYSTEM.MSTPCRA.BIT.MSTPA15
#define	MSTP_CMT2	SYSTEM.MSTPCRA.BIT.MSTPA14
#define	MSTP_CMT3	SYSTEM.MSTPCRA.BIT.MSTPA14
#define	MSTP_GPTW	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_GPTW0	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_GPTW1	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_GPTW2	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_GPTW3	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_GPTW4	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_GPTW5	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_GPTW6	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_GPTW7	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_POEG	SYSTEM.MSTPCRA.BIT.MSTPA7
#define	MSTP_TMR0	SYSTEM.MSTPCRA.BIT.MSTPA5
#define	MSTP_TMR1	SYSTEM.MSTPCRA.BIT.MSTPA5
#define	MSTP_TMR01	SYSTEM.MSTPCRA.BIT.MSTPA5
#define	MSTP_TMR2	SYSTEM.MSTPCRA.BIT.MSTPA4
#define	MSTP_TMR3	SYSTEM.MSTPCRA.BIT.MSTPA4
#define	MSTP_TMR23	SYSTEM.MSTPCRA.BIT.MSTPA4
#define	MSTP_RSCI0	SYSTEM.MSTPCRB.BIT.MSTPB31
#define	MSTP_SCI1	SYSTEM.MSTPCRB.BIT.MSTPB30
#define	MSTP_SCI5	SYSTEM.MSTPCRB.BIT.MSTPB26
#define	MSTP_SCI6	SYSTEM.MSTPCRB.BIT.MSTPB25
#define	MSTP_CRC	SYSTEM.MSTPCRB.BIT.MSTPB23
#define	MSTP_RIIC0	SYSTEM.MSTPCRB.BIT.MSTPB21
#define	MSTP_USB0	SYSTEM.MSTPCRB.BIT.MSTPB19
#define	MSTP_RSPI0	SYSTEM.MSTPCRB.BIT.MSTPB17
#define	MSTP_CMPB	SYSTEM.MSTPCRB.BIT.MSTPB10
#define	MSTP_ELC	SYSTEM.MSTPCRB.BIT.MSTPB9
#define	MSTP_DOC	SYSTEM.MSTPCRB.BIT.MSTPB6
#define	MSTP_SCI12	SYSTEM.MSTPCRB.BIT.MSTPB4
#define	MSTP_REMC0	SYSTEM.MSTPCRC.BIT.MSTPC29
#define	MSTP_RSCI8	SYSTEM.MSTPCRC.BIT.MSTPC27
#define	MSTP_RSCI9	SYSTEM.MSTPCRC.BIT.MSTPC26
#define	MSTP_CAC	SYSTEM.MSTPCRC.BIT.MSTPC19
#define	MSTP_RAM	SYSTEM.MSTPCRC.BIT.MSTPC0
#define	MSTP_RSIP	SYSTEM.MSTPCRD.BIT.MSTPD31
#define	MSTP_CTSU	SYSTEM.MSTPCRD.BIT.MSTPD10
#define	MSTP_CANFD0	SYSTEM.MSTPCRD.BIT.MSTPD9

#define	__IR( x )		ICU.IR[ IR ## x ].BIT.IR
#define	 _IR( x )		__IR( x )
#define	  IR( x , y )	_IR( _ ## x ## _ ## y )
#define	__DTCE( x )		ICU.DTCER[ DTCE ## x ].BIT.DTCE
#define	 _DTCE( x )		__DTCE( x )
#define	  DTCE( x , y )	_DTCE( _ ## x ## _ ## y )
#define	__IEN( x )		ICU.IER[ IER ## x ].BIT.IEN ## x
#define	 _IEN( x )		__IEN( x )
#define	  IEN( x , y )	_IEN( _ ## x ## _ ## y )
#define	__IPR( x )		ICU.IPR[ IPR ## x ].BIT.IPR
#define	 _IPR( x )		__IPR( x )
#define	  IPR( x , y )	_IPR( _ ## x ## _ ## y )
#define	__VECT( x )		VECT ## x
#define	 _VECT( x )		__VECT( x )
#define	  VECT( x , y )	_VECT( _ ## x ## _ ## y )
#define	__MSTP( x )		MSTP ## x
#define	 _MSTP( x )		__MSTP( x )
#define	  MSTP( x )		_MSTP( _ ## x )

#define	BSC		(*(volatile struct st_bsc    __evenaccess *)0x81300)
#define	CAC		(*(volatile struct st_cac    __evenaccess *)0x8B000)
#define	CANFD	(*(volatile struct st_canfd  __evenaccess *)0xA8014)
#define	CANFD0	(*(volatile struct st_canfd0 __evenaccess *)0xA8000)
#define	CMPB	(*(volatile struct st_cmpb   __evenaccess *)0x8C580)
#define	CMT		(*(volatile struct st_cmt    __evenaccess *)0x88000)
#define	CMT0	(*(volatile struct st_cmt0   __evenaccess *)0x88002)
#define	CMT1	(*(volatile struct st_cmt0   __evenaccess *)0x88008)
#define	CMT2	(*(volatile struct st_cmt0   __evenaccess *)0x88012)
#define	CMT3	(*(volatile struct st_cmt0   __evenaccess *)0x88018)
#define	CRC		(*(volatile struct st_crc    __evenaccess *)0x88280)
#define	CTSU	(*(volatile struct st_ctsu   __evenaccess *)0xA0700)
#define	DA		(*(volatile struct st_da     __evenaccess *)0x880C0)
#define	DMAC	(*(volatile struct st_dmac   __evenaccess *)0x82200)
#define	DMAC0	(*(volatile struct st_dmac0  __evenaccess *)0x82000)
#define	DMAC1	(*(volatile struct st_dmac1  __evenaccess *)0x82040)
#define	DMAC2	(*(volatile struct st_dmac1  __evenaccess *)0x82080)
#define	DMAC3	(*(volatile struct st_dmac1  __evenaccess *)0x820C0)
#define	DOC		(*(volatile struct st_doc    __evenaccess *)0x8B080)
#define	DTC		(*(volatile struct st_dtc    __evenaccess *)0x82400)
#define	ELC		(*(volatile struct st_elc    __evenaccess *)0x8B100)
#define	FLASH	(*(volatile struct st_flash  __evenaccess *)0x7FC090)
#define	GPTW	(*(volatile struct st_gptw   __evenaccess *)0xC2B00)
#define	GPTW0	(*(volatile struct st_gptw0  __evenaccess *)0xC2000)
#define	GPTW1	(*(volatile struct st_gptw1  __evenaccess *)0xC2100)
#define	GPTW2	(*(volatile struct st_gptw1  __evenaccess *)0xC2200)
#define	GPTW3	(*(volatile struct st_gptw3  __evenaccess *)0xC2300)
#define	GPTW4	(*(volatile struct st_gptw3  __evenaccess *)0xC2400)
#define	GPTW5	(*(volatile struct st_gptw3  __evenaccess *)0xC2500)
#define	GPTW6	(*(volatile struct st_gptw6  __evenaccess *)0xC2600)
#define	GPTW7	(*(volatile struct st_gptw6  __evenaccess *)0xC2700)
#define	ICU		(*(volatile struct st_icu    __evenaccess *)0x87000)
#define	IWDT	(*(volatile struct st_iwdt   __evenaccess *)0x88030)
#define	LPT		(*(volatile struct st_lpt    __evenaccess *)0x800B0)
#define	MPC		(*(volatile struct st_mpc    __evenaccess *)0x8C11F)
#define	MPU		(*(volatile struct st_mpu    __evenaccess *)0x86400)
#define	OFSM	(*(volatile struct st_ofsm   __evenaccess *)0xFFFFFF80)
#define	POEG	(*(volatile struct st_poeg   __evenaccess *)0x9E000)
#define	PORT	(*(volatile struct st_port   __evenaccess *)0x8C120)
#define	PORT0	(*(volatile struct st_port0  __evenaccess *)0x8C000)
#define	PORT1	(*(volatile struct st_port1  __evenaccess *)0x8C001)
#define	PORT2	(*(volatile struct st_port2  __evenaccess *)0x8C002)
#define	PORT3	(*(volatile struct st_port3  __evenaccess *)0x8C003)
#define	PORT4	(*(volatile struct st_port4  __evenaccess *)0x8C004)
#define	PORT5	(*(volatile struct st_port5  __evenaccess *)0x8C005)
#define	PORTA	(*(volatile struct st_porta  __evenaccess *)0x8C00A)
#define	PORTB	(*(volatile struct st_portb  __evenaccess *)0x8C00B)
#define	PORTC	(*(volatile struct st_portc  __evenaccess *)0x8C00C)
#define	PORTD	(*(volatile struct st_portd  __evenaccess *)0x8C00D)
#define	PORTE	(*(volatile struct st_porte  __evenaccess *)0x8C00E)
#define	PORTG	(*(volatile struct st_portg  __evenaccess *)0x8C010)
#define	PORTH	(*(volatile struct st_porth  __evenaccess *)0x8C011)
#define	PORTJ	(*(volatile struct st_portj  __evenaccess *)0x8C012)
#define	RAM		(*(volatile struct st_ram    __evenaccess *)0x81200)
#define	REMC0	(*(volatile struct st_remc   __evenaccess *)0xA0B00)
#define	RIIC0	(*(volatile struct st_riic   __evenaccess *)0x88300)
#define	RSCI0	(*(volatile struct st_rsci0  __evenaccess *)0xA1000)
#define	RSCI8	(*(volatile struct st_rsci0  __evenaccess *)0xA1400)
#define	RSCI9	(*(volatile struct st_rsci9  __evenaccess *)0xA1480)
#define	RSPI0	(*(volatile struct st_rspi   __evenaccess *)0x88380)
#define	RTC		(*(volatile struct st_rtc    __evenaccess *)0x8C400)
#define	RTCB	(*(volatile struct st_rtcb   __evenaccess *)0x8C402)
#define	S12AD	(*(volatile struct st_s12ad  __evenaccess *)0x89000)
#define	SCI1	(*(volatile struct st_sci1   __evenaccess *)0x8A020)
#define	SCI5	(*(volatile struct st_sci1   __evenaccess *)0x8A0A0)
#define	SCI6	(*(volatile struct st_sci1   __evenaccess *)0x8A0C0)
#define	SCI12	(*(volatile struct st_sci12  __evenaccess *)0x8B300)
#define	SMCI1	(*(volatile struct st_smci   __evenaccess *)0x8A020)
#define	SMCI5	(*(volatile struct st_smci   __evenaccess *)0x8A0A0)
#define	SMCI6	(*(volatile struct st_smci   __evenaccess *)0x8A0C0)
#define	SMCI12	(*(volatile struct st_smci   __evenaccess *)0x8B300)
#define	SYSTEM	(*(volatile struct st_system __evenaccess *)0x80000)
#define	TEMPS	(*(volatile struct st_temps  __evenaccess *)0x7FC228)
#define	TMR0	(*(volatile struct st_tmr0   __evenaccess *)0x88200)
#define	TMR1	(*(volatile struct st_tmr1   __evenaccess *)0x88201)
#define	TMR2	(*(volatile struct st_tmr0   __evenaccess *)0x88210)
#define	TMR3	(*(volatile struct st_tmr1   __evenaccess *)0x88211)
#define	TMR01	(*(volatile struct st_tmr01  __evenaccess *)0x88204)
#define	TMR23	(*(volatile struct st_tmr01  __evenaccess *)0x88214)
#define	USB0	(*(volatile struct st_usb    __evenaccess *)0xA0000)
#define	WDT		(*(volatile struct st_wdt    __evenaccess *)0x88020)

typedef enum enum_ir {
IR_BSC_BUSERR=16,IR_RAM_RAMERR=18,
IR_FCU_FRDYI=23,
IR_ICU_SWINT=27,
IR_CMT0_CMI0,IR_CMT1_CMI1,
IR_CMT2_CMI2,IR_CMT3_CMI3,
IR_CAC_FERRF,IR_CAC_MENDF,IR_CAC_OVFF,
IR_USB0_D0FIFO0=36,IR_USB0_D1FIFO0,IR_USB0_USBI0,
IR_POEG_POEGGAI=40,IR_POEG_POEGGBI,IR_POEG_POEGGCI,IR_POEG_POEGGDI,
IR_RSPI0_SPEI0,IR_RSPI0_SPRI0,IR_RSPI0_SPTI0,IR_RSPI0_SPII0,
IR_DOC_DOPCF=57,
IR_CMPB_CMPB0,IR_CMPB_CMPB1,
IR_CTSU_CTSUWR,IR_CTSU_CTSURD,IR_CTSU_CTSUFN,
IR_RTC_CUP,
IR_ICU_IRQ0,IR_ICU_IRQ1,IR_ICU_IRQ2,IR_ICU_IRQ3,IR_ICU_IRQ4,IR_ICU_IRQ5,IR_ICU_IRQ6,IR_ICU_IRQ7,
IR_ELC_ELSR8I=80,
IR_SYSTEM_SNZI,
IR_LVD_LVD1=88,IR_LVD_LVD2,
IR_USB0_USBR0,
IR_RTC_ALM=92,IR_RTC_PRD,
IR_REMC0_REMCI0,
IR_S12AD_S12ADI0=102,IR_S12AD_GBADI,
IR_ELC_ELSR18I=106,IR_ELC_ELSR19I,
IR_GPTW0_GTCIA0,IR_GPTW0_GTCIB0,IR_GPTW0_GTCIC0,IR_GPTW0_GTCID0,IR_GPTW0_GTCIE0,IR_GPTW0_GTCIF0,IR_GPTW0_GTCIV0,IR_GPTW0_GTCIU0,
IR_GPTW1_GTCIA1,IR_GPTW1_GTCIB1,IR_GPTW1_GTCIC1,IR_GPTW1_GTCID1,IR_GPTW1_GTCIE1,IR_GPTW1_GTCIF1,IR_GPTW1_GTCIV1,IR_GPTW1_GTCIU1,
IR_GPTW2_GTCIA2,IR_GPTW2_GTCIB2,IR_GPTW2_GTCIC2,IR_GPTW2_GTCID2,IR_GPTW2_GTCIE2,IR_GPTW2_GTCIF2,IR_GPTW2_GTCIV2,IR_GPTW2_GTCIU2,
IR_GPTW3_GTCIA3,IR_GPTW3_GTCIB3,IR_GPTW3_GTCIC3,IR_GPTW3_GTCID3,IR_GPTW3_GTCIE3,IR_GPTW3_GTCIF3,IR_GPTW3_GTCIV3,IR_GPTW3_GTCIU3,
IR_GPTW4_GTCIA4,IR_GPTW4_GTCIB4,IR_GPTW4_GTCIC4,IR_GPTW4_GTCID4,IR_GPTW4_GTCIE4,IR_GPTW4_GTCIF4,IR_GPTW4_GTCIV4,IR_GPTW4_GTCIU4,
IR_GPTW5_GTCIA5,IR_GPTW5_GTCIB5,IR_GPTW5_GTCIC5,IR_GPTW5_GTCID5,IR_GPTW5_GTCIE5,IR_GPTW5_GTCIF5,IR_GPTW5_GTCIV5,IR_GPTW5_GTCIU5,
IR_GPTW6_GTCIA6,IR_GPTW6_GTCIB6,IR_GPTW6_GTCIC6,IR_GPTW6_GTCID6,IR_GPTW6_GTCIE6,IR_GPTW6_GTCIF6,IR_GPTW6_GTCIV6,IR_GPTW6_GTCIU6,
IR_GPTW7_GTCIA7,IR_GPTW7_GTCIB7,IR_GPTW7_GTCIC7,IR_GPTW7_GTCID7,IR_GPTW7_GTCIE7,IR_GPTW7_GTCIF7,IR_GPTW7_GTCIV7,IR_GPTW7_GTCIU7,
IR_TMR0_CMIA0=174,IR_TMR0_CMIB0,IR_TMR0_OVI0,
IR_TMR1_CMIA1,IR_TMR1_CMIB1,IR_TMR1_OVI1,
IR_TMR2_CMIA2,IR_TMR2_CMIB2,IR_TMR2_OVI2,
IR_TMR3_CMIA3,IR_TMR3_CMIB3,IR_TMR3_OVI3,
IR_CANFD_RFRI,IR_CANFD_GLEI,IR_CANFD_RMRI,IR_CANFD_RFDREQ0,IR_CANFD_RFDREQ1,IR_CANFD_EC1EI,IR_CANFD_EC2EI,IR_CANFD_ECOVI,
IR_CANFD0_CHTI,IR_CANFD0_CHEI,IR_CANFD0_CFRI,IR_CANFD0_CFDREQ0,
IR_DMAC_DMAC0I,IR_DMAC_DMAC1I,IR_DMAC_DMAC2I,IR_DMAC_DMAC3I,
IR_RSIP_PROC_BUSY,IR_RSIP_ROMOK,IR_RSIP_LONG_PLG,IR_RSIP_TEST_BUSY,IR_RSIP_WRRDY0,
IR_RSIP_WRRDY2,IR_RSIP_RDRDY0,IR_RSIP_INTEGRATE_RDRDY,IR_RSIP_INTEGRATE_WRRDY,IR_RSIP_ECCERR,
IR_RSCI9_BFD,IR_RSCI9_AED,
IR_RSCI0_ERI,IR_RSCI0_RXI,IR_RSCI0_TXI,IR_RSCI0_TEI,
IR_SCI1_ERI1,IR_SCI1_RXI1,IR_SCI1_TXI1,IR_SCI1_TEI1,
IR_SCI5_ERI5,IR_SCI5_RXI5,IR_SCI5_TXI5,IR_SCI5_TEI5,
IR_SCI6_ERI6,IR_SCI6_RXI6,IR_SCI6_TXI6,IR_SCI6_TEI6,
IR_RSCI8_ERI,IR_RSCI8_RXI,IR_RSCI8_TXI,IR_RSCI8_TEI,
IR_RSCI9_ERI,IR_RSCI9_RXI,IR_RSCI9_TXI,IR_RSCI9_TEI,
IR_SCI12_ERI12,IR_SCI12_RXI12,IR_SCI12_TXI12,IR_SCI12_TEI12,IR_SCI12_SCIX0,IR_SCI12_SCIX1,IR_SCI12_SCIX2,IR_SCI12_SCIX3,
IR_RIIC0_EEI0,IR_RIIC0_RXI0,IR_RIIC0_TXI0,IR_RIIC0_TEI0,
IR_LPT_LPTCMI1=255
} enum_ir_t;

typedef enum enum_dtce {
DTCE_ICU_SWINT=27,
DTCE_CMT0_CMI0,DTCE_CMT1_CMI1,
DTCE_CMT2_CMI2,DTCE_CMT3_CMI3,
DTCE_USB0_D0FIFO0=36,DTCE_USB0_D1FIFO0,
DTCE_RSPI0_SPRI0=45,DTCE_RSPI0_SPTI0,
DTCE_CMPB_CMPB0=58,DTCE_CMPB_CMPB1,
DTCE_CTSU_CTSUWR,DTCE_CTSU_CTSURD,
DTCE_ICU_IRQ0=64,DTCE_ICU_IRQ1,DTCE_ICU_IRQ2,DTCE_ICU_IRQ3,DTCE_ICU_IRQ4,DTCE_ICU_IRQ5,DTCE_ICU_IRQ6,DTCE_ICU_IRQ7,
DTCE_S12AD_S12ADI0=102,DTCE_S12AD_GBADI,
DTCE_ELC_ELSR18I=106,DTCE_ELC_ELSR19I,
DTCE_GPTW0_GTCIA0,DTCE_GPTW0_GTCIB0,DTCE_GPTW0_GTCIC0,DTCE_GPTW0_GTCID0,DTCE_GPTW0_GTCIE0,DTCE_GPTW0_GTCIF0,DTCE_GPTW0_GTCIV0,DTCE_GPTW0_GTCIU0,
DTCE_GPTW1_GTCIA1,DTCE_GPTW1_GTCIB1,DTCE_GPTW1_GTCIC1,DTCE_GPTW1_GTCID1,DTCE_GPTW1_GTCIE1,DTCE_GPTW1_GTCIF1,DTCE_GPTW1_GTCIV1,DTCE_GPTW1_GTCIU1,
DTCE_GPTW2_GTCIA2,DTCE_GPTW2_GTCIB2,DTCE_GPTW2_GTCIC2,DTCE_GPTW2_GTCID2,DTCE_GPTW2_GTCIE2,DTCE_GPTW2_GTCIF2,DTCE_GPTW2_GTCIV2,DTCE_GPTW2_GTCIU2,
DTCE_GPTW3_GTCIA3,DTCE_GPTW3_GTCIB3,DTCE_GPTW3_GTCIC3,DTCE_GPTW3_GTCID3,DTCE_GPTW3_GTCIE3,DTCE_GPTW3_GTCIF3,DTCE_GPTW3_GTCIV3,DTCE_GPTW3_GTCIU3,
DTCE_GPTW4_GTCIA4,DTCE_GPTW4_GTCIB4,DTCE_GPTW4_GTCIC4,DTCE_GPTW4_GTCID4,DTCE_GPTW4_GTCIE4,DTCE_GPTW4_GTCIF4,DTCE_GPTW4_GTCIV4,DTCE_GPTW4_GTCIU4,
DTCE_GPTW5_GTCIA5,DTCE_GPTW5_GTCIB5,DTCE_GPTW5_GTCIC5,DTCE_GPTW5_GTCID5,DTCE_GPTW5_GTCIE5,DTCE_GPTW5_GTCIF5,DTCE_GPTW5_GTCIV5,DTCE_GPTW5_GTCIU5,
DTCE_GPTW6_GTCIA6,DTCE_GPTW6_GTCIB6,DTCE_GPTW6_GTCIC6,DTCE_GPTW6_GTCID6,DTCE_GPTW6_GTCIE6,DTCE_GPTW6_GTCIF6,DTCE_GPTW6_GTCIV6,DTCE_GPTW6_GTCIU6,
DTCE_GPTW7_GTCIA7,DTCE_GPTW7_GTCIB7,DTCE_GPTW7_GTCIC7,DTCE_GPTW7_GTCID7,DTCE_GPTW7_GTCIE7,DTCE_GPTW7_GTCIF7,DTCE_GPTW7_GTCIV7,DTCE_GPTW7_GTCIU7,
DTCE_TMR0_CMIA0=174,DTCE_TMR0_CMIB0,
DTCE_TMR1_CMIA1=177,DTCE_TMR1_CMIB1,
DTCE_TMR2_CMIA2=180,DTCE_TMR2_CMIB2,
DTCE_TMR3_CMIA3=183,DTCE_TMR3_CMIB3,
DTCE_CANFD_RFDREQ0=189,DTCE_CANFD_RFDREQ1,
DTCE_CANFD0_CFDREQ0=197,
DTCE_DMAC_DMAC0I,DTCE_DMAC_DMAC1I,DTCE_DMAC_DMAC2I,DTCE_DMAC_DMAC3I,
DTCE_RSIP_WRRDY0=206,DTCE_RSIP_WRRDY2,DTCE_RSIP_RDRDY0,DTCE_RSIP_INTEGRATE_RDRDY,DTCE_RSIP_INTEGRATE_WRRDY,
DTCE_RSCI9_AED=213,
DTCE_RSCI0_RXI=215,DTCE_RSCI0_TXI,
DTCE_SCI1_RXI1=219,DTCE_SCI1_TXI1,
DTCE_SCI5_RXI5=223,DTCE_SCI5_TXI5,
DTCE_SCI6_RXI6=227,DTCE_SCI6_TXI6,
DTCE_RSCI8_RXI=231,DTCE_RSCI8_TXI,
DTCE_RSCI9_RXI=235,DTCE_RSCI9_TXI,
DTCE_SCI12_RXI12=239,DTCE_SCI12_TXI12,
DTCE_RIIC0_RXI0=247,DTCE_RIIC0_TXI0,
DTCE_LPT_LPTCMI1=255
} enum_dtce_t;

typedef enum enum_ier {
IER_BSC_BUSERR=0x02,
IER_RAM_RAMERR=0x02,
IER_FCU_FRDYI=0x02,
IER_ICU_SWINT=0x03,
IER_CMT0_CMI0=0x03,IER_CMT1_CMI1=0x03,
IER_CMT2_CMI2=0x03,IER_CMT3_CMI3=0x03,
IER_CAC_FERRF=0x04,IER_CAC_MENDF=0x04,IER_CAC_OVFF=0x04,
IER_USB0_D0FIFO0=0x04,IER_USB0_D1FIFO0=0x04,IER_USB0_USBI0=0x04,
IER_POEG_POEGGAI=0x05,IER_POEG_POEGGBI=0x05,IER_POEG_POEGGCI=0x05,IER_POEG_POEGGDI=0x05,
IER_RSPI0_SPEI0=0x05,IER_RSPI0_SPRI0=0x05,IER_RSPI0_SPTI0=0x05,IER_RSPI0_SPII0=0x05,
IER_DOC_DOPCF=0x07,
IER_CMPB_CMPB0=0x07,IER_CMPB_CMPB1=0x07,
IER_CTSU_CTSUWR=0x07,IER_CTSU_CTSURD=0x07,IER_CTSU_CTSUFN=0x07,
IER_RTC_CUP=0x07,
IER_ICU_IRQ0=0x08,IER_ICU_IRQ1=0x08,IER_ICU_IRQ2=0x08,IER_ICU_IRQ3=0x08,IER_ICU_IRQ4=0x08,IER_ICU_IRQ5=0x08,IER_ICU_IRQ6=0x08,IER_ICU_IRQ7=0x08,
IER_ELC_ELSR8I=0x0A,
IER_SYSTEM_SNZI=0x0A,
IER_LVD_LVD1=0x0B,IER_LVD_LVD2=0x0B,
IER_USB0_USBR0=0x0B,
IER_RTC_ALM=0x0B,IER_RTC_PRD=0x0B,
IER_REMC0_REMCI0=0x0B,
IER_S12AD_S12ADI0=0x0C,IER_S12AD_GBADI=0x0C,
IER_ELC_ELSR18I=0x0D,IER_ELC_ELSR19I=0x0D,
IER_GPTW0_GTCIA0=0x0D,IER_GPTW0_GTCIB0=0x0D,IER_GPTW0_GTCIC0=0x0D,IER_GPTW0_GTCID0=0x0D,IER_GPTW0_GTCIE0=0x0E,IER_GPTW0_GTCIF0=0x0E,IER_GPTW0_GTCIV0=0x0E,IER_GPTW0_GTCIU0=0x0E,
IER_GPTW1_GTCIA1=0x0E,IER_GPTW1_GTCIB1=0x0E,IER_GPTW1_GTCIC1=0x0E,IER_GPTW1_GTCID1=0x0E,IER_GPTW1_GTCIE1=0x0F,IER_GPTW1_GTCIF1=0x0F,IER_GPTW1_GTCIV1=0x0F,IER_GPTW1_GTCIU1=0x0F,
IER_GPTW2_GTCIA2=0x0F,IER_GPTW2_GTCIB2=0x0F,IER_GPTW2_GTCIC2=0x0F,IER_GPTW2_GTCID2=0x0F,IER_GPTW2_GTCIE2=0x10,IER_GPTW2_GTCIF2=0x10,IER_GPTW2_GTCIV2=0x10,IER_GPTW2_GTCIU2=0x10,
IER_GPTW3_GTCIA3=0x10,IER_GPTW3_GTCIB3=0x10,IER_GPTW3_GTCIC3=0x10,IER_GPTW3_GTCID3=0x10,IER_GPTW3_GTCIE3=0x11,IER_GPTW3_GTCIF3=0x11,IER_GPTW3_GTCIV3=0x11,IER_GPTW3_GTCIU3=0x11,
IER_GPTW4_GTCIA4=0x11,IER_GPTW4_GTCIB4=0x11,IER_GPTW4_GTCIC4=0x11,IER_GPTW4_GTCID4=0x11,IER_GPTW4_GTCIE4=0x12,IER_GPTW4_GTCIF4=0x12,IER_GPTW4_GTCIV4=0x12,IER_GPTW4_GTCIU4=0x12,
IER_GPTW5_GTCIA5=0x12,IER_GPTW5_GTCIB5=0x12,IER_GPTW5_GTCIC5=0x12,IER_GPTW5_GTCID5=0x12,IER_GPTW5_GTCIE5=0x13,IER_GPTW5_GTCIF5=0x13,IER_GPTW5_GTCIV5=0x13,IER_GPTW5_GTCIU5=0x13,
IER_GPTW6_GTCIA6=0x13,IER_GPTW6_GTCIB6=0x13,IER_GPTW6_GTCIC6=0x13,IER_GPTW6_GTCID6=0x13,IER_GPTW6_GTCIE6=0x14,IER_GPTW6_GTCIF6=0x14,IER_GPTW6_GTCIV6=0x14,IER_GPTW6_GTCIU6=0x14,
IER_GPTW7_GTCIA7=0x14,IER_GPTW7_GTCIB7=0x14,IER_GPTW7_GTCIC7=0x14,IER_GPTW7_GTCID7=0x14,IER_GPTW7_GTCIE7=0x15,IER_GPTW7_GTCIF7=0x15,IER_GPTW7_GTCIV7=0x15,IER_GPTW7_GTCIU7=0x15,
IER_TMR0_CMIA0=0x15,IER_TMR0_CMIB0=0x15,IER_TMR0_OVI0=0x16,
IER_TMR1_CMIA1=0x16,IER_TMR1_CMIB1=0x16,IER_TMR1_OVI1=0x16,
IER_TMR2_CMIA2=0x16,IER_TMR2_CMIB2=0x16,IER_TMR2_OVI2=0x16,
IER_TMR3_CMIA3=0x16,IER_TMR3_CMIB3=0x17,IER_TMR3_OVI3=0x17,
IER_CANFD_RFRI=0x17,IER_CANFD_GLEI=0x17,IER_CANFD_RMRI=0x17,IER_CANFD_RFDREQ0=0x17,IER_CANFD_RFDREQ1=0x17,IER_CANFD_EC1EI=0x17,IER_CANFD_EC2EI=0x18,IER_CANFD_ECOVI=0x18,
IER_CANFD0_CHTI=0x18,IER_CANFD0_CHEI=0x18,IER_CANFD0_CFRI=0x18,IER_CANFD0_CFDREQ0=0x18,
IER_DMAC_DMAC0I=0x18,IER_DMAC_DMAC1I=0x18,IER_DMAC_DMAC2I=0x19,IER_DMAC_DMAC3I=0x19,
IER_RSIP_PROC_BUSY=0x19,IER_RSIP_ROMOK=0x19,IER_RSIP_LONG_PLG=0x19,IER_RSIP_TEST_BUSY=0x19,IER_RSIP_WRRDY0=0x19,
IER_RSIP_WRRDY2=0x19,IER_RSIP_RDRDY0=0x1A,IER_RSIP_INTEGRATE_RDRDY=0x1A,IER_RSIP_INTEGRATE_WRRDY=0x1A,IER_RSIP_ECCERR=0x1A,
IER_RSCI9_BFD=0x1A,IER_RSCI9_AED=0x1A,
IER_RSCI0_ERI=0x1A,IER_RSCI0_RXI=0x1A,IER_RSCI0_TXI=0x1B,IER_RSCI0_TEI=0x1B,
IER_SCI1_ERI1=0x1B,IER_SCI1_RXI1=0x1B,IER_SCI1_TXI1=0x1B,IER_SCI1_TEI1=0x1B,
IER_SCI5_ERI5=0x1B,IER_SCI5_RXI5=0x1B,IER_SCI5_TXI5=0x1C,IER_SCI5_TEI5=0x1C,
IER_SCI6_ERI6=0x1C,IER_SCI6_RXI6=0x1C,IER_SCI6_TXI6=0x1C,IER_SCI6_TEI6=0x1C,
IER_RSCI8_ERI=0x1C,IER_RSCI8_RXI=0x1C,IER_RSCI8_TXI=0x1D,IER_RSCI8_TEI=0x1D,
IER_RSCI9_ERI=0x1D,IER_RSCI9_RXI=0x1D,IER_RSCI9_TXI=0x1D,IER_RSCI9_TEI=0x1D,
IER_SCI12_ERI12=0x1D,IER_SCI12_RXI12=0x1D,IER_SCI12_TXI12=0x1E,IER_SCI12_TEI12=0x1E,IER_SCI12_SCIX0=0x1E,IER_SCI12_SCIX1=0x1E,IER_SCI12_SCIX2=0x1E,IER_SCI12_SCIX3=0x1E,
IER_RIIC0_EEI0=0x1E,IER_RIIC0_RXI0=0x1E,IER_RIIC0_TXI0=0x1F,IER_RIIC0_TEI0=0x1F,
IER_LPT_LPTCMI1=0x1F
} enum_ier_t;

typedef enum enum_ipr {
IPR_BSC_BUSERR=0,
IPR_RAM_RAMERR=0,
IPR_FCU_FRDYI=2,
IPR_ICU_SWINT=3,
IPR_CMT0_CMI0=4,IPR_CMT1_CMI1=5,
IPR_CMT2_CMI2=6,IPR_CMT3_CMI3=7,
IPR_CAC_FERRF=32,IPR_CAC_MENDF=33,IPR_CAC_OVFF=34,
IPR_USB0_D0FIFO0=36,IPR_USB0_D1FIFO0=37,IPR_USB0_USBI0=38,
IPR_POEG_POEGGAI=40,IPR_POEG_POEGGBI=41,IPR_POEG_POEGGCI=42,IPR_POEG_POEGGDI=43,
IPR_RSPI0_SPEI0=44,IPR_RSPI0_SPRI0=44,IPR_RSPI0_SPTI0=44,IPR_RSPI0_SPII0=44,
IPR_DOC_DOPCF=57,
IPR_CMPB_CMPB0=58,IPR_CMPB_CMPB1=59,
IPR_CTSU_CTSUWR=60,IPR_CTSU_CTSURD=60,IPR_CTSU_CTSUFN=60,
IPR_RTC_CUP=63,
IPR_ICU_IRQ0=64,IPR_ICU_IRQ1=65,IPR_ICU_IRQ2=66,IPR_ICU_IRQ3=67,IPR_ICU_IRQ4=68,IPR_ICU_IRQ5=69,IPR_ICU_IRQ6=70,IPR_ICU_IRQ7=71,
IPR_ELC_ELSR8I=80,
IPR_SYSTEM_SNZI=81,
IPR_LVD_LVD1=88,IPR_LVD_LVD2=89,
IPR_USB0_USBR0=90,
IPR_RTC_ALM=92,IPR_RTC_PRD=93,
IPR_REMC0_REMCI0=94,
IPR_S12AD_S12ADI0=102,IPR_S12AD_GBADI=103,
IPR_ELC_ELSR18I=106,IPR_ELC_ELSR19I=107,
IPR_GPTW0_GTCIA0=108,IPR_GPTW0_GTCIB0=108,IPR_GPTW0_GTCIC0=110,IPR_GPTW0_GTCID0=110,IPR_GPTW0_GTCIE0=110,IPR_GPTW0_GTCIF0=110,IPR_GPTW0_GTCIV0=114,IPR_GPTW0_GTCIU0=114,
IPR_GPTW1_GTCIA1=116,IPR_GPTW1_GTCIB1=116,IPR_GPTW1_GTCIC1=118,IPR_GPTW1_GTCID1=118,IPR_GPTW1_GTCIE1=118,IPR_GPTW1_GTCIF1=118,IPR_GPTW1_GTCIV1=122,IPR_GPTW1_GTCIU1=122,
IPR_GPTW2_GTCIA2=124,IPR_GPTW2_GTCIB2=124,IPR_GPTW2_GTCIC2=126,IPR_GPTW2_GTCID2=126,IPR_GPTW2_GTCIE2=126,IPR_GPTW2_GTCIF2=126,IPR_GPTW2_GTCIV2=130,IPR_GPTW2_GTCIU2=130,
IPR_GPTW3_GTCIA3=132,IPR_GPTW3_GTCIB3=132,IPR_GPTW3_GTCIC3=134,IPR_GPTW3_GTCID3=134,IPR_GPTW3_GTCIE3=134,IPR_GPTW3_GTCIF3=134,IPR_GPTW3_GTCIV3=138,IPR_GPTW3_GTCIU3=138,
IPR_GPTW4_GTCIA4=140,IPR_GPTW4_GTCIB4=140,IPR_GPTW4_GTCIC4=142,IPR_GPTW4_GTCID4=142,IPR_GPTW4_GTCIE4=142,IPR_GPTW4_GTCIF4=142,IPR_GPTW4_GTCIV4=146,IPR_GPTW4_GTCIU4=146,
IPR_GPTW5_GTCIA5=148,IPR_GPTW5_GTCIB5=148,IPR_GPTW5_GTCIC5=150,IPR_GPTW5_GTCID5=150,IPR_GPTW5_GTCIE5=150,IPR_GPTW5_GTCIF5=150,IPR_GPTW5_GTCIV5=154,IPR_GPTW5_GTCIU5=154,
IPR_GPTW6_GTCIA6=156,IPR_GPTW6_GTCIB6=156,IPR_GPTW6_GTCIC6=158,IPR_GPTW6_GTCID6=158,IPR_GPTW6_GTCIE6=158,IPR_GPTW6_GTCIF6=158,IPR_GPTW6_GTCIV6=162,IPR_GPTW6_GTCIU6=162,
IPR_GPTW7_GTCIA7=164,IPR_GPTW7_GTCIB7=164,IPR_GPTW7_GTCIC7=166,IPR_GPTW7_GTCID7=166,IPR_GPTW7_GTCIE7=166,IPR_GPTW7_GTCIF7=166,IPR_GPTW7_GTCIV7=170,IPR_GPTW7_GTCIU7=170,
IPR_TMR0_CMIA0=174,IPR_TMR0_CMIB0=174,IPR_TMR0_OVI0=174,
IPR_TMR1_CMIA1=177,IPR_TMR1_CMIB1=177,IPR_TMR1_OVI1=177,
IPR_TMR2_CMIA2=180,IPR_TMR2_CMIB2=180,IPR_TMR2_OVI2=180,
IPR_TMR3_CMIA3=183,IPR_TMR3_CMIB3=183,IPR_TMR3_OVI3=183,
IPR_CANFD_RFRI=186,IPR_CANFD_GLEI=187,IPR_CANFD_RMRI=188,IPR_CANFD_RFDREQ0=189,IPR_CANFD_RFDREQ1=190,IPR_CANFD_EC1EI=191,IPR_CANFD_EC2EI=192,IPR_CANFD_ECOVI=193,
IPR_CANFD0_CHTI=194,IPR_CANFD0_CHEI=195,IPR_CANFD0_CFRI=196,IPR_CANFD0_CFDREQ0=197,
IPR_DMAC_DMAC0I=198,IPR_DMAC_DMAC1I=199,IPR_DMAC_DMAC2I=200,IPR_DMAC_DMAC3I=201,
IPR_RSIP_PROC_BUSY=202,IPR_RSIP_ROMOK=203,IPR_RSIP_LONG_PLG=204,IPR_RSIP_TEST_BUSY=205,IPR_RSIP_WRRDY0=206,
IPR_RSIP_WRRDY2=207,IPR_RSIP_RDRDY0=208,IPR_RSIP_INTEGRATE_RDRDY=209,IPR_RSIP_INTEGRATE_WRRDY=210,IPR_RSIP_ECCERR=211,
IPR_RSCI9_BFD=212,IPR_RSCI9_AED=213,
IPR_RSCI0_ERI=214,IPR_RSCI0_RXI=214,IPR_RSCI0_TXI=214,IPR_RSCI0_TEI=214,
IPR_SCI1_ERI1=218,IPR_SCI1_RXI1=218,IPR_SCI1_TXI1=218,IPR_SCI1_TEI1=218,
IPR_SCI5_ERI5=222,IPR_SCI5_RXI5=222,IPR_SCI5_TXI5=222,IPR_SCI5_TEI5=222,
IPR_SCI6_ERI6=226,IPR_SCI6_RXI6=226,IPR_SCI6_TXI6=226,IPR_SCI6_TEI6=226,
IPR_RSCI8_ERI=230,IPR_RSCI8_RXI=230,IPR_RSCI8_TXI=230,IPR_RSCI8_TEI=230,
IPR_RSCI9_ERI=234,IPR_RSCI9_RXI=234,IPR_RSCI9_TXI=234,IPR_RSCI9_TEI=234,
IPR_SCI12_ERI12=238,IPR_SCI12_RXI12=238,IPR_SCI12_TXI12=238,IPR_SCI12_TEI12=238,IPR_SCI12_SCIX0=242,IPR_SCI12_SCIX1=243,IPR_SCI12_SCIX2=244,IPR_SCI12_SCIX3=245,
IPR_RIIC0_EEI0=246,IPR_RIIC0_RXI0=247,IPR_RIIC0_TXI0=248,IPR_RIIC0_TEI0=249,
IPR_LPT_LPTCMI1=255,
IPR_FCU_=2,
IPR_DOC_=57,
IPR_CTSU_=60,
IPR_SYSTEM_=81,
IPR_REMC0_=94,
IPR_TMR0_=174,
IPR_TMR1_=177,
IPR_TMR2_=180,
IPR_TMR3_=183,
IPR_RSCI0_=214,
IPR_SCI1_=218,
IPR_SCI5_=222,
IPR_SCI6_=226,
IPR_RSCI8_=230,
IPR_LPT_=255
} enum_ipr_t;

#pragma bit_order left
#pragma unpack

typedef struct st_bsc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char STSCLR:1;
		} BIT;
	} BERCLR;
	char           wk0[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char TOEN:1;
			unsigned char IGAEN:1;
		} BIT;
	} BEREN;
	char           wk1[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char MST:3;
			unsigned char :2;
			unsigned char TO:1;
			unsigned char IA:1;
		} BIT;
	} BERSR1;
	char           wk2[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short ADDR:13;
			unsigned short :3;
		} BIT;
	} BERSR2;
	char           wk3[4];
	union {
		unsigned short WORD;
		struct {
			unsigned short :4;
			unsigned short BPFB:2;
			unsigned short BPHB:2;
			unsigned short BPGB:2;
			unsigned short BPIB:2;
			unsigned short BPRO:2;
			unsigned short BPRA:2;
		} BIT;
	} BUSPRI;
} st_bsc_t;

typedef struct st_cac {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CFME:1;
		} BIT;
	} CACR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char EDGES:2;
			unsigned char TCSS:2;
			unsigned char FMCS:3;
			unsigned char CACREFE:1;
		} BIT;
	} CACR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DFS:2;
			unsigned char RCDS:2;
			unsigned char RSCS:3;
			unsigned char RPS:1;
		} BIT;
	} CACR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char OVFFCL:1;
			unsigned char MENDFCL:1;
			unsigned char FERRFCL:1;
			unsigned char :1;
			unsigned char OVFIE:1;
			unsigned char MENDIE:1;
			unsigned char FERRIE:1;
		} BIT;
	} CAICR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char OVFF:1;
			unsigned char MENDF:1;
			unsigned char FERRF:1;
		} BIT;
	} CASTR;
	char           wk0[1];
	unsigned short CAULVR;
	unsigned short CALLVR;
	unsigned short CACNTBR;
} st_cac_t;

typedef struct st_canfd {
	union {
		unsigned long LONG;
		struct {
			unsigned long ITP:16;
			unsigned long :3;
			unsigned long TSCS:1;
			unsigned long TSP:4;
			unsigned long :2;
			unsigned long OMRC:1;
			unsigned long DLLCS:1;
			unsigned long MME:1;
			unsigned long DRE:1;
			unsigned long DCE:1;
			unsigned long TPRI:1;
		} BIT;
	} GCFG;
	union {
		unsigned long LONG;
		struct {
			unsigned long :15;
			unsigned long TSCR:1;
			unsigned long :4;
			unsigned long POIE:1;
			unsigned long THLIE:1;
			unsigned long MLIE:1;
			unsigned long DEIE:1;
			unsigned long :5;
			unsigned long SLPRQ:1;
			unsigned long MDC:2;
		} BIT;
	} GCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long RAMST:1;
			unsigned long SLPST:1;
			unsigned long HLTST:1;
			unsigned long RSTST:1;
		} BIT;
	} GSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :15;
			unsigned long EEDF0:1;
			unsigned long :12;
			unsigned long PODF:1;
			unsigned long THLDF:1;
			unsigned long MLDF:1;
			unsigned long DEDF:1;
		} BIT;
	} GESR;
	unsigned long  TSCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :23;
			unsigned long AFLWE:1;
			unsigned long :7;
			unsigned long PAGE:1;
		} BIT;
	} AFCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :10;
			unsigned long RN0:6;
			unsigned long :16;
		} BIT;
	} AFCFG;
	union {
		unsigned long LONG;
		struct {
			unsigned long :21;
			unsigned long PLS:3;
			unsigned long :2;
			unsigned long NMB:6;
		} BIT;
	} RMCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long NDF:32;
		} BIT;
	} RMNDR;
	union {
		unsigned long LONG;
		struct {
			unsigned long RMIE31:1;
			unsigned long RMIE30:1;
			unsigned long RMIE29:1;
			unsigned long RMIE28:1;
			unsigned long RMIE27:1;
			unsigned long RMIE26:1;
			unsigned long RMIE25:1;
			unsigned long RMIE24:1;
			unsigned long RMIE23:1;
			unsigned long RMIE22:1;
			unsigned long RMIE21:1;
			unsigned long RMIE20:1;
			unsigned long RMIE19:1;
			unsigned long RMIE18:1;
			unsigned long RMIE17:1;
			unsigned long RMIE16:1;
			unsigned long RMIE15:1;
			unsigned long RMIE14:1;
			unsigned long RMIE13:1;
			unsigned long RMIE12:1;
			unsigned long RMIE11:1;
			unsigned long RMIE10:1;
			unsigned long RMIE9:1;
			unsigned long RMIE8:1;
			unsigned long RMIE7:1;
			unsigned long RMIE6:1;
			unsigned long RMIE5:1;
			unsigned long RMIE4:1;
			unsigned long RMIE3:1;
			unsigned long RMIE2:1;
			unsigned long RMIE1:1;
			unsigned long RMIE0:1;
		} BIT;
	} RMIER;
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long RFITH:3;
			unsigned long RFIM:1;
			unsigned long :1;
			unsigned long FDS:3;
			unsigned long :1;
			unsigned long PLS:3;
			unsigned long :2;
			unsigned long RFIE:1;
			unsigned long RFE:1;
		} BIT;
	} RFCR[2];
	union {
		unsigned long LONG;
		struct {
			unsigned long :18;
			unsigned long FLVL:6;
			unsigned long :4;
			unsigned long RFIF:1;
			unsigned long LOST:1;
			unsigned long FULL:1;
			unsigned long EMPTY:1;
		} BIT;
	} RFSR[2];
	unsigned long  RFPCR[2];
	union {
		unsigned long LONG;
		struct {
			unsigned long TINT:8;
			unsigned long FDS:3;
			unsigned long :3;
			unsigned long LTM:2;
			unsigned long CFITH:3;
			unsigned long CFIM:1;
			unsigned long ITR:1;
			unsigned long ITCS:1;
			unsigned long :1;
			unsigned long MODE:1;
			unsigned long :1;
			unsigned long PLS:3;
			unsigned long :1;
			unsigned long CFTIE:1;
			unsigned long CFRIE:1;
			unsigned long CFE:1;
		} BIT;
	} CFCR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :18;
			unsigned long FLVL:6;
			unsigned long :3;
			unsigned long CFTIF:1;
			unsigned long CFRIF:1;
			unsigned long LOST:1;
			unsigned long FULL:1;
			unsigned long EMPTY:1;
		} BIT;
	} CFSR0;
	unsigned long  CFPCR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :23;
			unsigned long CFEMP0:1;
			unsigned long :6;
			unsigned long RFEMP1:1;
			unsigned long RFEMP0:1;
		} BIT;
	} FESR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :23;
			unsigned long CFFUL0:1;
			unsigned long :6;
			unsigned long RFFUL1:1;
			unsigned long RFFUL0:1;
		} BIT;
	} FFSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :23;
			unsigned long CFML0:1;
			unsigned long :6;
			unsigned long RFML1:1;
			unsigned long RFML0:1;
		} BIT;
	} FMLSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :30;
			unsigned long RFIF1:1;
			unsigned long RFIF0:1;
		} BIT;
	} RFISR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char ONESHOT:1;
			unsigned char TARQ:1;
			unsigned char TXRQ:1;
		} BIT;
	} TMCR[4];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char TARQS:1;
			unsigned char TXRQS:1;
			unsigned char TXRF:2;
			unsigned char TXSF:1;
		} BIT;
	} TMSR[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long TXRQS3:1;
			unsigned long TXRQS2:1;
			unsigned long TXRQS1:1;
			unsigned long TXRQS0:1;
		} BIT;
	} TMTRSR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long TARQS3:1;
			unsigned long TARQS2:1;
			unsigned long TARQS1:1;
			unsigned long TARQS0:1;
		} BIT;
	} TMARSR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long TXCF3:1;
			unsigned long TXCF2:1;
			unsigned long TXCF1:1;
			unsigned long TXCF0:1;
		} BIT;
	} TMTCSR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long TAF3:1;
			unsigned long TAF2:1;
			unsigned long TAF1:1;
			unsigned long TAF0:1;
		} BIT;
	} TMTASR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long TMIE3:1;
			unsigned long TMIE2:1;
			unsigned long TMIE1:1;
			unsigned long TMIE0:1;
		} BIT;
	} TMIER0;
	char           wk0[24];
	union {
		unsigned long LONG;
		struct {
			unsigned long :27;
			unsigned long THIF0:1;
			unsigned long CFTIF0:1;
			unsigned long TQIF0:1;
			unsigned long TAIF0:1;
			unsigned long TSIF0:1;
		} BIT;
	} TISR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :12;
			unsigned long RTPS:4;
			unsigned long :16;
		} BIT;
	} GTMCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :29;
			unsigned long RTME:1;
			unsigned long :2;
		} BIT;
	} GTMER;
	union {
		unsigned long LONG;
		struct {
			unsigned long :22;
			unsigned long TSCPS:2;
			unsigned long :7;
			unsigned long PXEDIS:1;
		} BIT;
	} GFDCFG;
	char           wk1[4];
	unsigned long  GTMLKR;
	char           wk2[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long :27;
			unsigned long IGES:5;
		} BIT;
	} AFIGSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long KEY:8;
			unsigned long :7;
			unsigned long IGEE:1;
		} BIT;
	} AFIGER;
	union {
		unsigned long LONG;
		struct {
			unsigned long :23;
			unsigned long CFDTE0:1;
			unsigned long :6;
			unsigned long RFDTE1:1;
			unsigned long RFDTE0:1;
		} BIT;
	} DTCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :23;
			unsigned long CFDTS0:1;
			unsigned long :6;
			unsigned long RFDTS1:1;
			unsigned long RFDTS0:1;
		} BIT;
	} DTSR;
	char           wk3[8];
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long KEY:8;
			unsigned long :7;
			unsigned long SRST:1;
		} BIT;
	} GRCR;
	char           wk4[68];
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long LPC:1;
				unsigned long ID:29;
			} BIT;
		} IDR;
		union {
			unsigned long LONG;
			struct {
				unsigned long IDEM:1;
				unsigned long RTRM:1;
				unsigned long IFL1:1;
				unsigned long IDM:29;
			} BIT;
		} MASK;
		union {
			unsigned long LONG;
			struct {
				unsigned long PTR:16;
				unsigned long DMBE:1;
				unsigned long :2;
				unsigned long DMB:5;
				unsigned long IFL0:1;
				unsigned long :3;
				unsigned long DLC:4;
			} BIT;
		} PTR0;
		union {
			unsigned long LONG;
			struct {
				unsigned long :23;
				unsigned long CF0E:1;
				unsigned long :6;
				unsigned long RF1E:1;
				unsigned long RF0E:1;
			} BIT;
		} PTR1;
	} AFL[16];
	char           wk5[96];
	unsigned long  RTPAR[64];
	char           wk6[416];
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RFB[2];
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long THENT:1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} CFB[1];
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long THENT:1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :28;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} TMB[4];
	char           wk7[492];
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB0;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB1;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB2;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB3;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB4;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB5;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB6;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB7;
	char           wk8[416];
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB8;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB9;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB10;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB11;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB12;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB13;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB14;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB15;
	char           wk9[416];
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB16;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB17;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB18;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB19;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB20;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB21;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB22;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB23;
	char           wk10[416];
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB24;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB25;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB26;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB27;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB28;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB29;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB30;
	struct {
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long IDE:1;
				unsigned long RTR:1;
				unsigned long :1;
				unsigned long ID:29;
			} BIT;
		} HF0;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long DLC:4;
				unsigned long :12;
				unsigned long TS:16;
			} BIT;
		} HF1;
		union {
			unsigned long LONG;
			struct {
				unsigned short L;
				unsigned short H;
			} WORD;
			struct {
				unsigned char LL;
				unsigned char LH;
				unsigned char HL;
				unsigned char HH;
			} BYTE;
			struct {
				unsigned long PTR:16;
				unsigned long :6;
				unsigned long IFL:2;
				unsigned long :5;
				unsigned long FDF:1;
				unsigned long BRS:1;
				unsigned long ESI:1;
			} BIT;
		} HF2;
		union {
			unsigned long DF[16];
			unsigned char DATA[64];
		};
	} RMB31;
	char           wk11[276608];
	union {
		unsigned long LONG;
		struct {
			unsigned long :14;
			unsigned long EC2EAS:1;
			unsigned long EC1EAS:1;
			unsigned long ECEDWC:2;
			unsigned long :2;
			unsigned long ECOVF:1;
			unsigned long EC2EC:1;
			unsigned long EC1EC:1;
			unsigned long :2;
			unsigned long ECEDE:1;
			unsigned long EC1ECD:1;
			unsigned long EC2EIE:1;
			unsigned long EC1EIE:1;
			unsigned long EC2EF:1;
			unsigned long EC1EF:1;
			unsigned long ECEF:1;
		} BIT;
	} ECCSR;
	union {
		unsigned short WORD;
		struct {
			unsigned short ECTMWC:2;
			unsigned short :6;
			unsigned short ECTME:1;
			unsigned short :5;
			unsigned short ECDIS:1;
			unsigned short :1;
		} BIT;
	} ECTMR;
	char           wk12[6];
	unsigned long  ECTDR;
	unsigned long  ECEAR;
} st_canfd_t;

typedef struct st_canfd0 {
	union {
		unsigned long LONG;
		struct {
			unsigned long TSEG2:7;
			unsigned long TSEG1:8;
			unsigned long SJW:7;
			unsigned long BRP:10;
		} BIT;
	} NBCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long ROME:1;
			unsigned long BFT:1;
			unsigned long :3;
			unsigned long CTMS:2;
			unsigned long CTME:1;
			unsigned long EDM:1;
			unsigned long BOM:2;
			unsigned long :1;
			unsigned long TDCVIE:1;
			unsigned long SCOVIE:1;
			unsigned long ECOVIE:1;
			unsigned long TAIE:1;
			unsigned long ALIE:1;
			unsigned long BLIE:1;
			unsigned long OLIE:1;
			unsigned long BORIE:1;
			unsigned long BOEIE:1;
			unsigned long EPIE:1;
			unsigned long EWIE:1;
			unsigned long BEIE:1;
			unsigned long :4;
			unsigned long RTBO:1;
			unsigned long SLPRQ:1;
			unsigned long MDC:2;
		} BIT;
	} CHCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long TEC:8;
			unsigned long REC:8;
			unsigned long :7;
			unsigned long RESI:1;
			unsigned long CRDY:1;
			unsigned long RECST:1;
			unsigned long TRMST:1;
			unsigned long BOST:1;
			unsigned long EPST:1;
			unsigned long SLPST:1;
			unsigned long HLTST:1;
			unsigned long RSTST:1;
		} BIT;
	} CHSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long CRC15:15;
			unsigned long :1;
			unsigned long ADEDF:1;
			unsigned long B0EDF:1;
			unsigned long B1EDF:1;
			unsigned long CEDF:1;
			unsigned long AEDF:1;
			unsigned long FEDF:1;
			unsigned long SEDF:1;
			unsigned long ALDF:1;
			unsigned long BLDF:1;
			unsigned long OLDF:1;
			unsigned long BORDF:1;
			unsigned long BOEDF:1;
			unsigned long EPDF:1;
			unsigned long EWDF:1;
			unsigned long BEDF:1;
		} BIT;
	} CHESR;
	char           wk0[124];
	union {
		unsigned long LONG;
		struct {
			unsigned long :22;
			unsigned long QDS:2;
			unsigned long TQIM:1;
			unsigned long :1;
			unsigned long TQIE:1;
			unsigned long :4;
			unsigned long TQE:1;
		} BIT;
	} TQCR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :21;
			unsigned long FLVL:3;
			unsigned long :5;
			unsigned long TQIF:1;
			unsigned long FULL:1;
			unsigned long EMPTY:1;
		} BIT;
	} TQSR0;
	unsigned long  TQPCR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :21;
			unsigned long THRC:1;
			unsigned long THIM:1;
			unsigned long THIE:1;
			unsigned long :7;
			unsigned long THE:1;
		} BIT;
	} THCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :20;
			unsigned long FLVL:4;
			unsigned long :4;
			unsigned long THIF:1;
			unsigned long LOST:1;
			unsigned long FULL:1;
			unsigned long EMPTY:1;
		} BIT;
	} THSR;
	unsigned long  THPCR;
	char           wk1[92];
	union {
		unsigned long LONG;
		struct {
			unsigned long :4;
			unsigned long SJW:4;
			unsigned long :4;
			unsigned long TSEG2:4;
			unsigned long :3;
			unsigned long TSEG1:5;
			unsigned long BRP:8;
		} BIT;
	} DBCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long CLOE:1;
			unsigned long REFE:1;
			unsigned long FDOE:1;
			unsigned long :4;
			unsigned long TDCO:8;
			unsigned long :5;
			unsigned long TESI:1;
			unsigned long TDCE:1;
			unsigned long SSPC:1;
			unsigned long :5;
			unsigned long ECC:3;
		} BIT;
	} FDCFG;
	union {
		unsigned long LONG;
		struct {
			unsigned long :30;
			unsigned long SCCL:1;
			unsigned long ECCL:1;
		} BIT;
	} FDCTR;
	union {
		unsigned long LONG;
		struct {
			unsigned long SC:8;
			unsigned long EC:8;
			unsigned long TDCV:1;
			unsigned long :5;
			unsigned long SCOV:1;
			unsigned long ECOV:1;
			unsigned long TDCR:8;
		} BIT;
	} FDSTS;
	union {
		unsigned long LONG;
		struct {
			unsigned long :4;
			unsigned long SBC:4;
			unsigned long :3;
			unsigned long CRC21:21;
		} BIT;
	} FDCRC;
	char           wk2[1580];
	union {
		unsigned long LONG;
		struct {
			unsigned long TS:16;
			unsigned long :11;
			unsigned long BN:2;
			unsigned long BT:3;
		} BIT;
	} THACR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :14;
			unsigned long IFL:2;
			unsigned long PTR:16;
		} BIT;
	} THACR1;
} st_canfd0_t;

typedef struct st_cmpb {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CPB1INI:1;
			unsigned char :3;
			unsigned char CPB0INI:1;
		} BIT;
	} CPBCNT1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CPB1WCP:1;
			unsigned char :3;
			unsigned char CPB0WCP:1;
		} BIT;
	} CPBCNT2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CPB1OUT:1;
			unsigned char :3;
			unsigned char CPB0OUT:1;
			unsigned char :3;
		} BIT;
	} CPBFLG;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char CPB1INTPL:1;
			unsigned char CPB1INTEG:1;
			unsigned char CPB1INTEN:1;
			unsigned char :1;
			unsigned char CPB0INTPL:1;
			unsigned char CPB0INTEG:1;
			unsigned char CPB0INTEN:1;
		} BIT;
	} CPBINT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CPB1F:2;
			unsigned char :1;
			unsigned char CPB1FEN:1;
			unsigned char CPB0F:2;
			unsigned char :1;
			unsigned char CPB0FEN:1;
		} BIT;
	} CPBF;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CPBSPDMD:1;
		} BIT;
	} CPBMD;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CPB1VRF:1;
			unsigned char :3;
			unsigned char CPB0VRF:1;
		} BIT;
	} CPBREF;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char CPB1OP:1;
			unsigned char CPB1OE:1;
			unsigned char :2;
			unsigned char CPB0OP:1;
			unsigned char CPB0OE:1;
		} BIT;
	} CPBOCR;
} st_cmpb_t;

typedef struct st_cmt {
	union {
		unsigned short WORD;
		struct {
			unsigned short :14;
			unsigned short STR1:1;
			unsigned short STR0:1;
		} BIT;
	} CMSTR0;
	char           wk0[14];
	union {
		unsigned short WORD;
		struct {
			unsigned short :14;
			unsigned short STR3:1;
			unsigned short STR2:1;
		} BIT;
	} CMSTR1;
} st_cmt_t;

typedef struct st_cmt0 {
	union {
		unsigned short WORD;
		struct {
			unsigned short :9;
			unsigned short CMIE:1;
			unsigned short :4;
			unsigned short CKS:2;
		} BIT;
	} CMCR;
	unsigned short CMCNT;
	unsigned short CMCOR;
} st_cmt0_t;

typedef struct st_crc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char DORCLR:1;
			unsigned char :4;
			unsigned char LMS:1;
			unsigned char GPS:2;
		} BIT;
	} CRCCR;
	unsigned char  CRCDIR;
	unsigned short CRCDOR;
} st_crc_t;

typedef struct st_ctsu {
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long :31;
			unsigned long CTADCS:1;
		} BIT;
	} CTSUADCC;
	char           wk0[508];
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long DCBACK:1;
			unsigned long DCMODE:1;
			unsigned long STCLK:6;
			unsigned long PCSEL:1;
			unsigned long SDPSEL:1;
			unsigned long POSEL:2;
			unsigned long LOAD:2;
			unsigned long ATUNE2:1;
			unsigned long :1;
			unsigned long MD1:1;
			unsigned long MD0:1;
			unsigned long CLK:2;
			unsigned long ATUNE1:1;
			unsigned long ATUNE0:1;
			unsigned long CSW:1;
			unsigned long PON:1;
			unsigned long TXVSEL:2;
			unsigned long PUMPON:1;
			unsigned long INIT:1;
			unsigned long :1;
			unsigned long SNZ:1;
			unsigned long CAP:1;
			unsigned long STRT:1;
		} BIT;
	} CTSUCRA;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long :2;
			unsigned long SSCNT:2;
			unsigned long :1;
			unsigned long SSMOD:3;
			unsigned long :8;
			unsigned long SST:8;
			unsigned long PROFF:1;
			unsigned long SOFF:1;
			unsigned long PRMODE:2;
			unsigned long PRRATIO:4;
		} BIT;
	} CTSUCRB;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long :12;
			unsigned long MCA3:1;
			unsigned long MCA2:1;
			unsigned long MCA1:1;
			unsigned long MCA0:1;
			unsigned long :2;
			unsigned long MCH1:6;
			unsigned long :2;
			unsigned long MCH0:6;
		} BIT;
	} CTSUMCH;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long CHAC31:1;
			unsigned long CHAC30:1;
			unsigned long CHAC29:1;
			unsigned long CHAC28:1;
			unsigned long CHAC27:1;
			unsigned long CHAC26:1;
			unsigned long CHAC25:1;
			unsigned long CHAC24:1;
			unsigned long CHAC23:1;
			unsigned long CHAC22:1;
			unsigned long CHAC21:1;
			unsigned long CHAC20:1;
			unsigned long CHAC19:1;
			unsigned long CHAC18:1;
			unsigned long CHAC17:1;
			unsigned long CHAC16:1;
			unsigned long CHAC15:1;
			unsigned long CHAC14:1;
			unsigned long CHAC13:1;
			unsigned long CHAC12:1;
			unsigned long CHAC11:1;
			unsigned long CHAC10:1;
			unsigned long CHAC9:1;
			unsigned long CHAC8:1;
			unsigned long CHAC7:1;
			unsigned long CHAC6:1;
			unsigned long CHAC5:1;
			unsigned long CHAC4:1;
			unsigned long CHAC3:1;
			unsigned long CHAC2:1;
			unsigned long CHAC1:1;
			unsigned long CHAC0:1;
		} BIT;
	} CTSUCHACA;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long :28;
			unsigned long CHAC35:1;
			unsigned long CHAC34:1;
			unsigned long CHAC33:1;
			unsigned long CHAC32:1;
		} BIT;
	} CTSUCHACB;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long CHTRC31:1;
			unsigned long CHTRC30:1;
			unsigned long CHTRC29:1;
			unsigned long CHTRC28:1;
			unsigned long CHTRC27:1;
			unsigned long CHTRC26:1;
			unsigned long CHTRC25:1;
			unsigned long CHTRC24:1;
			unsigned long CHTRC23:1;
			unsigned long CHTRC22:1;
			unsigned long CHTRC21:1;
			unsigned long CHTRC20:1;
			unsigned long CHTRC19:1;
			unsigned long CHTRC18:1;
			unsigned long CHTRC17:1;
			unsigned long CHTRC16:1;
			unsigned long CHTRC15:1;
			unsigned long CHTRC14:1;
			unsigned long CHTRC13:1;
			unsigned long CHTRC12:1;
			unsigned long CHTRC11:1;
			unsigned long CHTRC10:1;
			unsigned long CHTRC9:1;
			unsigned long CHTRC8:1;
			unsigned long CHTRC7:1;
			unsigned long CHTRC6:1;
			unsigned long CHTRC5:1;
			unsigned long CHTRC4:1;
			unsigned long CHTRC3:1;
			unsigned long CHTRC2:1;
			unsigned long CHTRC1:1;
			unsigned long CHTRC0:1;
		} BIT;
	} CTSUCHTRCA;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long :28;
			unsigned long CHTRC35:1;
			unsigned long CHTRC34:1;
			unsigned long CHTRC33:1;
			unsigned long CHTRC32:1;
		} BIT;
	} CTSUCHTRCB;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long :16;
			unsigned long PS:1;
			unsigned long UCOVF:1;
			unsigned long SCOVF:1;
			unsigned long DTSR:1;
			unsigned long :1;
			unsigned long STC:3;
			unsigned long ICOMP0:1;
			unsigned long ICOMP1:1;
			unsigned long ICOMPRST:1;
			unsigned long :3;
			unsigned long MFC:2;
		} BIT;
	} CTSUSR;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long SDPA:8;
			unsigned long SSDIV:4;
			unsigned long :2;
			unsigned long SNUM:8;
			unsigned long SO:10;
		} BIT;
	} CTSUSO;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long UC:16;
			unsigned long SC:16;
		} BIT;
	} CTSUSCNT;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long TXREV:1;
			unsigned long CCOCALIB:1;
			unsigned long CCOCLK:1;
			unsigned long DACCLK:1;
			unsigned long SUCARRY:1;
			unsigned long SUMSEL:1;
			unsigned long DACCARRY:1;
			unsigned long DACMSEL:1;
			unsigned long :11;
			unsigned long IOCSEL:1;
			unsigned long DCOFF:1;
			unsigned long :1;
			unsigned long IOC:1;
			unsigned long CNTRDSEL:1;
			unsigned long TSOC:1;
			unsigned long SUCLKEN:1;
			unsigned long CLKSEL:2;
			unsigned long DRV:1;
			unsigned long TSOD:1;
			unsigned long :2;
		} BIT;
	} CTSUCALIB;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long SUMULTI1:8;
			unsigned long SUADJ1:8;
			unsigned long SUMULTI0:8;
			unsigned long SUADJ0:8;
		} BIT;
	} CTSUSUCLKA;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long SUMULTI3:8;
			unsigned long SUADJ3:8;
			unsigned long SUMULTI2:8;
			unsigned long SUADJ2:8;
		} BIT;
	} CTSUSUCLKB;
	char           wk1[12];
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long :12;
			unsigned long SCACTB:4;
			unsigned long :7;
			unsigned long AJFEN:1;
			unsigned long :2;
			unsigned long MTUCFEN:1;
			unsigned long DTCLESS:1;
			unsigned long :1;
			unsigned long MAJIRIMD:1;
			unsigned long MCACFEN:1;
			unsigned long CCOCFEN:1;
		} BIT;
	} CTSUOPT;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long SCNTACCOUNT:16;
			unsigned long SCNTACCOEFF:16;
		} BIT;
	} CTSUSCNTACT;
	char           wk2[4];
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long OFFSETCOEFF1:16;
			unsigned long :6;
			unsigned long SO1:10;
		} BIT;
	} CTSUMCACT1;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long OFFSETCOEFF2:16;
			unsigned long :6;
			unsigned long SO2:10;
		} BIT;
	} CTSUMCACT2;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long OFFSETCOEFF3:16;
			unsigned long :6;
			unsigned long SO3:10;
		} BIT;
	} CTSUMCACT3;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long AJBMAT:4;
			unsigned long AJMMAT:4;
			unsigned long :2;
			unsigned long JC:2;
			unsigned long :3;
			unsigned long BLINI:1;
			unsigned long THOT:8;
			unsigned long TLOT:8;
		} BIT;
	} CTSUAJCR;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long AJTHH:16;
			unsigned long AJTHL:16;
		} BIT;
	} CTSUAJTHR;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long AJMMAR:27;
			unsigned long :1;
			unsigned long AJMMATI:4;
		} BIT;
	} CTSUAJMMAR;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long AJBLACT:32;
		} BIT;
	} CTSUAJBLACT;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long AJBLAR:16;
			unsigned long AJBLAC:16;
		} BIT;
	} CTSUAJBLAR;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned long :16;
			unsigned long SJCCR:8;
			unsigned long :3;
			unsigned long FJR:1;
			unsigned long TJR3:1;
			unsigned long TJR2:1;
			unsigned long TJR1:1;
			unsigned long TJR0:1;
		} BIT;
	} CTSUAJRR;
	char           wk3[7715380];
	union {
		unsigned long LONG;
		struct {
			unsigned long TRESULT4:8;
			unsigned long SUADJD:8;
			unsigned long DACTRIM:8;
			unsigned long RTRIM:8;
		} BIT;
	} CTSUTRIMA;
	union {
		unsigned long LONG;
		struct {
			unsigned long TRESULT3:8;
			unsigned long TRESULT2:8;
			unsigned long TRESULT1:8;
			unsigned long TRESULT0:8;
		} BIT;
	} CTSUTRIMB;
} st_ctsu_t;

typedef struct st_da {
	unsigned short DADR0;
	unsigned short DADR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAOE1:1;
			unsigned char DAOE0:1;
			unsigned char :6;
		} BIT;
	} DACR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DPSEL:1;
			unsigned char :7;
		} BIT;
	} DADPR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAADST:1;
			unsigned char :7;
		} BIT;
	} DAADSCR;
} st_da_t;

typedef struct st_dmac {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DMST:1;
		} BIT;
	} DMAST;
} st_dmac_t;

typedef struct st_dmac0 {
	void          *DMSAR;
	void          *DMDAR;
	unsigned long  DMCRA;
	unsigned short DMCRB;
	char           wk0[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short MD:2;
			unsigned short DTS:2;
			unsigned short :2;
			unsigned short SZ:2;
			unsigned short :6;
			unsigned short DCTG:2;
		} BIT;
	} DMTMD;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char DTIE:1;
			unsigned char ESIE:1;
			unsigned char RPTIE:1;
			unsigned char SARIE:1;
			unsigned char DARIE:1;
		} BIT;
	} DMINT;
	union {
		unsigned short WORD;
		struct {
			unsigned short SM:2;
			unsigned short :1;
			unsigned short SARA:5;
			unsigned short DM:2;
			unsigned short :1;
			unsigned short DARA:5;
		} BIT;
	} DMAMD;
	char           wk2[2];
	unsigned long  DMOFR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DTE:1;
		} BIT;
	} DMCNT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CLRS:1;
			unsigned char :3;
			unsigned char SWREQ:1;
		} BIT;
	} DMREQ;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ACT:1;
			unsigned char :2;
			unsigned char DTIF:1;
			unsigned char :3;
			unsigned char ESIF:1;
		} BIT;
	} DMSTS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DISEL:1;
		} BIT;
	} DMCSL;
} st_dmac0_t;

typedef struct st_dmac1 {
	void          *DMSAR;
	void          *DMDAR;
	unsigned long  DMCRA;
	unsigned short DMCRB;
	char           wk0[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short MD:2;
			unsigned short DTS:2;
			unsigned short :2;
			unsigned short SZ:2;
			unsigned short :6;
			unsigned short DCTG:2;
		} BIT;
	} DMTMD;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char DTIE:1;
			unsigned char ESIE:1;
			unsigned char RPTIE:1;
			unsigned char SARIE:1;
			unsigned char DARIE:1;
		} BIT;
	} DMINT;
	union {
		unsigned short WORD;
		struct {
			unsigned short SM:2;
			unsigned short :1;
			unsigned short SARA:5;
			unsigned short DM:2;
			unsigned short :1;
			unsigned short DARA:5;
		} BIT;
	} DMAMD;
	char           wk2[6];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DTE:1;
		} BIT;
	} DMCNT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char CLRS:1;
			unsigned char :3;
			unsigned char SWREQ:1;
		} BIT;
	} DMREQ;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ACT:1;
			unsigned char :2;
			unsigned char DTIF:1;
			unsigned char :3;
			unsigned char ESIF:1;
		} BIT;
	} DMSTS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DISEL:1;
		} BIT;
	} DMCSL;
} st_dmac1_t;

typedef struct st_doc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char DOPCFCL:1;
			unsigned char DOPCF:1;
			unsigned char DOPCIE:1;
			unsigned char :1;
			unsigned char DCSEL:1;
			unsigned char OMS:2;
		} BIT;
	} DOCR;
	char           wk0[1];
	unsigned short DODIR;
	unsigned short DODSR;
} st_doc_t;

typedef struct st_dtc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char RRS:1;
			unsigned char :4;
		} BIT;
	} DTCCR;
	char           wk0[3];
	void          *DTCVBR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char SHORT:1;
		} BIT;
	} DTCADMOD;
	char           wk1[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DTCST:1;
		} BIT;
	} DTCST;
	char           wk2[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short ACT:1;
			unsigned short :7;
			unsigned short VECN:8;
		} BIT;
	} DTCSTS;
	void          *DTCIBR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char SQTFRL:1;
		} BIT;
	} DTCOR;
	char           wk3[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short ESPSEL:1;
			unsigned short :7;
			unsigned short VECN:8;
		} BIT;
	} DTCSQE;
	unsigned long  DTCDISP;
} st_dtc_t;

typedef struct st_elc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELCON:1;
			unsigned char :7;
		} BIT;
	} ELCR;
	char           wk0[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR7;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR8;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR10;
	char           wk2[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR12;
	char           wk3[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR14;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR15;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR16;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR18;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR19;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR20;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR21;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR22;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR23;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR24;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR25;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR26;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR27;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR28;
	char           wk5[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char LPTMD:2;
			unsigned char CMT1MD:2;
			unsigned char :2;
		} BIT;
	} ELOPC;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char TMR2MD:2;
			unsigned char :2;
			unsigned char TMR0MD:2;
		} BIT;
	} ELOPD;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PGR7:1;
			unsigned char PGR6:1;
			unsigned char PGR5:1;
			unsigned char PGR4:1;
			unsigned char PGR3:1;
			unsigned char PGR2:1;
			unsigned char PGR1:1;
			unsigned char PGR0:1;
		} BIT;
	} PGR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PGR7:1;
			unsigned char PGR6:1;
			unsigned char PGR5:1;
			unsigned char PGR4:1;
			unsigned char PGR3:1;
			unsigned char PGR2:1;
			unsigned char PGR1:1;
			unsigned char PGR0:1;
		} BIT;
	} PGR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PGCO:3;
			unsigned char :1;
			unsigned char PGCOVE:1;
			unsigned char PGCI:2;
		} BIT;
	} PGC1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PGCO:3;
			unsigned char :1;
			unsigned char PGCOVE:1;
			unsigned char PGCI:2;
		} BIT;
	} PGC2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PDBF7:1;
			unsigned char PDBF6:1;
			unsigned char PDBF5:1;
			unsigned char PDBF4:1;
			unsigned char PDBF3:1;
			unsigned char PDBF2:1;
			unsigned char PDBF1:1;
			unsigned char PDBF0:1;
		} BIT;
	} PDBF1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PDBF7:1;
			unsigned char PDBF6:1;
			unsigned char PDBF5:1;
			unsigned char PDBF4:1;
			unsigned char PDBF3:1;
			unsigned char PDBF2:1;
			unsigned char PDBF1:1;
			unsigned char PDBF0:1;
		} BIT;
	} PDBF2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PSM:2;
			unsigned char PSP:2;
			unsigned char PSB:3;
		} BIT;
	} PEL0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PSM:2;
			unsigned char PSP:2;
			unsigned char PSB:3;
		} BIT;
	} PEL1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PSM:2;
			unsigned char PSP:2;
			unsigned char PSB:3;
		} BIT;
	} PEL2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char PSM:2;
			unsigned char PSP:2;
			unsigned char PSB:3;
		} BIT;
	} PEL3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char WI:1;
			unsigned char WE:1;
			unsigned char :5;
			unsigned char SEG:1;
		} BIT;
	} ELSEGR;
	char           wk6[24];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR48;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR49;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR50;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR51;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR52;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR53;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR54;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR55;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ELS:8;
		} BIT;
	} ELSR56;
} st_elc_t;

typedef struct st_flash {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DFLEN:1;
		} BIT;
	} DFLCTL;
	char           wk0[111];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char FMS1:1;
			unsigned char RPDIS:1;
			unsigned char :1;
			unsigned char FMS0:1;
			unsigned char :1;
		} BIT;
	} FPMCR;
	char           wk1[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char EXS:1;
		} BIT;
	} FASR;
	char           wk2[3];
	unsigned short FSARL;
	char           wk3[6];
	unsigned short FSARH;
	char           wk4[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char OPST:1;
			unsigned char STOP:1;
			unsigned char :2;
			unsigned char CMD:4;
		} BIT;
	} FCR;
	char           wk5[3];
	unsigned short FEARL;
	char           wk6[6];
	unsigned short FEARH;
	char           wk7[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char FRESET:1;
		} BIT;
	} FRESETR;
	char           wk8[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char EILGLERR:1;
			unsigned char ILGLERR:1;
			unsigned char BCERR:1;
			unsigned char :1;
			unsigned char PRGERR:1;
			unsigned char ERERR:1;
		} BIT;
	} FSTATR0;
	char           wk9[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char EXRDY:1;
			unsigned char FRDY:1;
			unsigned char :6;
		} BIT;
	} FSTATR1;
	char           wk10[3];
	unsigned short FWB0;
	char           wk11[6];
	unsigned short FWB1;
	char           wk12[6];
	unsigned short FWB2;
	char           wk13[2];
	unsigned short FWB3;
	char           wk14[58];
	unsigned char  FPR;
	char           wk15[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char PERR:1;
		} BIT;
	} FPSR;
	char           wk16[59];
	union {
		unsigned short WORD;
		struct {
			unsigned short :1;
			unsigned short AWPR:1;
			unsigned short :5;
			unsigned short SASMF:1;
			unsigned short :8;
		} BIT;
	} FSCMR;
	char           wk17[6];
	unsigned short FAWSMR;
	char           wk18[6];
	unsigned short FAWEMR;
	char           wk19[6];
	union {
		unsigned char BYTE;
		struct {
			unsigned char SAS:2;
			unsigned char PCKA:6;
		} BIT;
	} FISR;
	char           wk20[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char OPST:1;
			unsigned char :4;
			unsigned char CMD:3;
		} BIT;
	} FEXCR;
	char           wk21[3];
	unsigned short FEAML;
	char           wk22[6];
	unsigned short FEAMH;
	char           wk23[358];
	unsigned long  UIDR0;
	unsigned long  UIDR1;
	unsigned long  UIDR2;
	unsigned long  UIDR3;
	char           wk24[15440];
	union {
		unsigned short WORD;
		struct {
			unsigned short FEKEY:8;
			unsigned short FENTRYD:1;
			unsigned short :6;
			unsigned short FENTRY0:1;
		} BIT;
	} FENTRYR;
	char           wk25[14];
	union {
		unsigned short WORD;
		struct {
			unsigned short MEKEY:8;
			unsigned short :7;
			unsigned short MEMWAIT:1;
		} BIT;
	} MEMWAITR;
} st_flash_t;

typedef struct st_gptw {
	union {
		unsigned long LONG;
		struct {
			unsigned long NFCS:2;
			unsigned long NFEN:1;
			unsigned long :2;
			unsigned long GODF:1;
			unsigned long GRP:2;
			unsigned long :2;
			unsigned long ALIGN:1;
			unsigned long RV:1;
			unsigned long INV:1;
			unsigned long N:1;
			unsigned long P:1;
			unsigned long FB:1;
			unsigned long :7;
			unsigned long EN:1;
			unsigned long :1;
			unsigned long W:1;
			unsigned long V:1;
			unsigned long U:1;
			unsigned long :1;
			unsigned long WF:1;
			unsigned long VF:1;
			unsigned long UF:1;
		} BIT;
	} OPSCR;
} st_gptw_t;

typedef struct st_gptw0 {
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long PRKEY:8;
			unsigned long :3;
			unsigned long CMNWP:1;
			unsigned long CLRWP:1;
			unsigned long STPWP:1;
			unsigned long STRWP:1;
			unsigned long WP:1;
		} BIT;
	} GTWP;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CSTRT7:1;
			unsigned long CSTRT6:1;
			unsigned long CSTRT5:1;
			unsigned long CSTRT4:1;
			unsigned long CSTRT3:1;
			unsigned long CSTRT2:1;
			unsigned long CSTRT1:1;
			unsigned long CSTRT0:1;
		} BIT;
	} GTSTR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CSTOP7:1;
			unsigned long CSTOP6:1;
			unsigned long CSTOP5:1;
			unsigned long CSTOP4:1;
			unsigned long CSTOP3:1;
			unsigned long CSTOP2:1;
			unsigned long CSTOP1:1;
			unsigned long CSTOP0:1;
		} BIT;
	} GTSTP;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CCLR7:1;
			unsigned long CCLR6:1;
			unsigned long CCLR5:1;
			unsigned long CCLR4:1;
			unsigned long CCLR3:1;
			unsigned long CCLR2:1;
			unsigned long CCLR1:1;
			unsigned long CCLR0:1;
		} BIT;
	} GTCLR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CSTRT:1;
			unsigned long :7;
			unsigned long SSELCH:1;
			unsigned long SSELCG:1;
			unsigned long SSELCF:1;
			unsigned long SSELCE:1;
			unsigned long SSELCD:1;
			unsigned long SSELCC:1;
			unsigned long SSELCB:1;
			unsigned long SSELCA:1;
			unsigned long SSCBFAH:1;
			unsigned long SSCBFAL:1;
			unsigned long SSCBRAH:1;
			unsigned long SSCBRAL:1;
			unsigned long SSCAFBH:1;
			unsigned long SSCAFBL:1;
			unsigned long SSCARBH:1;
			unsigned long SSCARBL:1;
			unsigned long SSGTRGDF:1;
			unsigned long SSGTRGDR:1;
			unsigned long SSGTRGCF:1;
			unsigned long SSGTRGCR:1;
			unsigned long SSGTRGBF:1;
			unsigned long SSGTRGBR:1;
			unsigned long SSGTRGAF:1;
			unsigned long SSGTRGAR:1;
		} BIT;
	} GTSSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CSTOP:1;
			unsigned long :7;
			unsigned long PSELCH:1;
			unsigned long PSELCG:1;
			unsigned long PSELCF:1;
			unsigned long PSELCE:1;
			unsigned long PSELCD:1;
			unsigned long PSELCC:1;
			unsigned long PSELCB:1;
			unsigned long PSELCA:1;
			unsigned long PSCBFAH:1;
			unsigned long PSCBFAL:1;
			unsigned long PSCBRAH:1;
			unsigned long PSCBRAL:1;
			unsigned long PSCAFBH:1;
			unsigned long PSCAFBL:1;
			unsigned long PSCARBH:1;
			unsigned long PSCARBL:1;
			unsigned long PSGTRGDF:1;
			unsigned long PSGTRGDR:1;
			unsigned long PSGTRGCF:1;
			unsigned long PSGTRGCR:1;
			unsigned long PSGTRGBF:1;
			unsigned long PSGTRGBR:1;
			unsigned long PSGTRGAF:1;
			unsigned long PSGTRGAR:1;
		} BIT;
	} GTPSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CCLR:1;
			unsigned long :3;
			unsigned long CP1CCE:1;
			unsigned long CSCMSC:3;
			unsigned long CSELCH:1;
			unsigned long CSELCG:1;
			unsigned long CSELCF:1;
			unsigned long CSELCE:1;
			unsigned long CSELCD:1;
			unsigned long CSELCC:1;
			unsigned long CSELCB:1;
			unsigned long CSELCA:1;
			unsigned long CSCBFAH:1;
			unsigned long CSCBFAL:1;
			unsigned long CSCBRAH:1;
			unsigned long CSCBRAL:1;
			unsigned long CSCAFBH:1;
			unsigned long CSCAFBL:1;
			unsigned long CSCARBH:1;
			unsigned long CSCARBL:1;
			unsigned long CSGTRGDF:1;
			unsigned long CSGTRGDR:1;
			unsigned long CSGTRGCF:1;
			unsigned long CSGTRGCR:1;
			unsigned long CSGTRGBF:1;
			unsigned long CSGTRGBR:1;
			unsigned long CSGTRGAF:1;
			unsigned long CSGTRGAR:1;
		} BIT;
	} GTCSR;
	char           wk0[8];
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long ASOC:1;
			unsigned long ASELCH:1;
			unsigned long ASELCG:1;
			unsigned long ASELCF:1;
			unsigned long ASELCE:1;
			unsigned long ASELCD:1;
			unsigned long ASELCC:1;
			unsigned long ASELCB:1;
			unsigned long ASELCA:1;
			unsigned long ASCBFAH:1;
			unsigned long ASCBFAL:1;
			unsigned long ASCBRAH:1;
			unsigned long ASCBRAL:1;
			unsigned long ASCAFBH:1;
			unsigned long ASCAFBL:1;
			unsigned long ASCARBH:1;
			unsigned long ASCARBL:1;
			unsigned long ASGTRGDF:1;
			unsigned long ASGTRGDR:1;
			unsigned long ASGTRGCF:1;
			unsigned long ASGTRGCR:1;
			unsigned long ASGTRGBF:1;
			unsigned long ASGTRGBR:1;
			unsigned long ASGTRGAF:1;
			unsigned long ASGTRGAR:1;
		} BIT;
	} GTICASR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long BSOC:1;
			unsigned long BSELCH:1;
			unsigned long BSELCG:1;
			unsigned long BSELCF:1;
			unsigned long BSELCE:1;
			unsigned long BSELCD:1;
			unsigned long BSELCC:1;
			unsigned long BSELCB:1;
			unsigned long BSELCA:1;
			unsigned long BSCBFAH:1;
			unsigned long BSCBFAL:1;
			unsigned long BSCBRAH:1;
			unsigned long BSCBRAL:1;
			unsigned long BSCAFBH:1;
			unsigned long BSCAFBL:1;
			unsigned long BSCARBH:1;
			unsigned long BSCARBL:1;
			unsigned long BSGTRGDF:1;
			unsigned long BSGTRGDR:1;
			unsigned long BSGTRGCF:1;
			unsigned long BSGTRGCR:1;
			unsigned long BSGTRGBF:1;
			unsigned long BSGTRGBR:1;
			unsigned long BSGTRGAF:1;
			unsigned long BSGTRGAR:1;
		} BIT;
	} GTICBSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long CKEG:2;
			unsigned long TPCS:4;
			unsigned long :3;
			unsigned long MD:4;
			unsigned long SSCEN:1;
			unsigned long :3;
			unsigned long SSCGRP:2;
			unsigned long SCGTIOC:1;
			unsigned long ICDS:1;
			unsigned long :7;
			unsigned long CST:1;
		} BIT;
	} GTCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :4;
			unsigned long OBDTYR:1;
			unsigned long OBDTYF:1;
			unsigned long OBDTY:2;
			unsigned long :4;
			unsigned long OADTYR:1;
			unsigned long OADTYF:1;
			unsigned long OADTY:2;
			unsigned long :14;
			unsigned long UDF:1;
			unsigned long UD:1;
		} BIT;
	} GTUDDTYC;
	union {
		unsigned long LONG;
		struct {
			unsigned long NFCSB:2;
			unsigned long NFBEN:1;
			unsigned long :1;
			unsigned long OBEOCD:1;
			unsigned long OBDF:2;
			unsigned long OBE:1;
			unsigned long OBHLD:1;
			unsigned long OBDFLT:1;
			unsigned long :1;
			unsigned long GTIOB:5;
			unsigned long NFCSA:2;
			unsigned long NFAEN:1;
			unsigned long PSYE:1;
			unsigned long OAEOCD:1;
			unsigned long OADF:2;
			unsigned long OAE:1;
			unsigned long OAHLD:1;
			unsigned long OADFLT:1;
			unsigned long CPSCIR:1;
			unsigned long GTIOA:5;
		} BIT;
	} GTIOR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long GRPABL:1;
			unsigned long GRPABH:1;
			unsigned long :3;
			unsigned long GRP:2;
			unsigned long :4;
			unsigned long ADTRBDEN:1;
			unsigned long ADTRBUEN:1;
			unsigned long ADTRADEN:1;
			unsigned long ADTRAUEN:1;
			unsigned long SCFPU:1;
			unsigned long SCFPO:1;
			unsigned long SCFF:1;
			unsigned long SCFE:1;
			unsigned long SCFD:1;
			unsigned long SCFC:1;
			unsigned long SCFB:1;
			unsigned long SCFA:1;
			unsigned long GTINTPR:2;
			unsigned long GTINTF:1;
			unsigned long GTINTE:1;
			unsigned long GTINTD:1;
			unsigned long GTINTC:1;
			unsigned long GTINTB:1;
			unsigned long GTINTA:1;
		} BIT;
	} GTINTAD;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long OABLF:1;
			unsigned long OABHF:1;
			unsigned long :4;
			unsigned long ODF:1;
			unsigned long :4;
			unsigned long ADTRBDF:1;
			unsigned long ADTRBUF:1;
			unsigned long ADTRADF:1;
			unsigned long ADTRAUF:1;
			unsigned long TUCF:1;
			unsigned long :4;
			unsigned long ITCNT:3;
			unsigned long TCFPU:1;
			unsigned long TCFPO:1;
			unsigned long TCFF:1;
			unsigned long TCFE:1;
			unsigned long TCFD:1;
			unsigned long TCFC:1;
			unsigned long TCFB:1;
			unsigned long TCFA:1;
		} BIT;
	} GTST;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long ADTDB:1;
			unsigned long ADTTB:2;
			unsigned long :1;
			unsigned long ADTDA:1;
			unsigned long ADTTA:2;
			unsigned long :1;
			unsigned long CCRSWT:1;
			unsigned long PR:2;
			unsigned long CCRB:2;
			unsigned long CCRA:2;
			unsigned long :13;
			unsigned long BD:3;
		} BIT;
	} GTBER;
	union {
		unsigned long LONG;
		struct {
			unsigned long :17;
			unsigned long ADTBL:1;
			unsigned long :1;
			unsigned long ADTAL:1;
			unsigned long :1;
			unsigned long IVTT:3;
			unsigned long IVTC:2;
			unsigned long ITLF:1;
			unsigned long ITLE:1;
			unsigned long ITLD:1;
			unsigned long ITLC:1;
			unsigned long ITLB:1;
			unsigned long ITLA:1;
		} BIT;
	} GTITC;
	unsigned long  GTCNT;
	unsigned long  GTCCRA;
	unsigned long  GTCCRB;
	unsigned long  GTCCRC;
	unsigned long  GTCCRE;
	unsigned long  GTCCRD;
	unsigned long  GTCCRF;
	unsigned long  GTPR;
	unsigned long  GTPBR;
	unsigned long  GTPDBR;
	unsigned long  GTADTRA;
	unsigned long  GTADTBRA;
	unsigned long  GTADTDBRA;
	unsigned long  GTADTRB;
	unsigned long  GTADTBRB;
	unsigned long  GTADTDBRB;
	union {
		unsigned long LONG;
		struct {
			unsigned long :31;
			unsigned long TDE:1;
		} BIT;
	} GTDTCR;
	unsigned long  GTDVU;
	char           wk1[64];
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long SECSEL7:1;
			unsigned long SECSEL6:1;
			unsigned long SECSEL5:1;
			unsigned long SECSEL4:1;
			unsigned long SECSEL3:1;
			unsigned long SECSEL2:1;
			unsigned long SECSEL1:1;
			unsigned long SECSEL0:1;
		} BIT;
	} GTSECSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :6;
			unsigned long SSCD:1;
			unsigned long :7;
			unsigned long SSCE:1;
			unsigned long :6;
			unsigned long SBDAD:1;
			unsigned long SBDPD:1;
			unsigned long SBDCD:1;
			unsigned long :5;
			unsigned long SBDAE:1;
			unsigned long SBDPE:1;
			unsigned long SBDCE:1;
		} BIT;
	} GTSECR;
	char           wk2[20];
	union {
		unsigned long LONG;
		struct {
			unsigned long ICBGRP:2;
			unsigned long :5;
			unsigned long ICBCLK:1;
			unsigned long ICBFPU:1;
			unsigned long ICBFPO:1;
			unsigned long ICBFF:1;
			unsigned long ICBFE:1;
			unsigned long ICBFD:1;
			unsigned long ICBFC:1;
			unsigned long ICBFB:1;
			unsigned long ICBFA:1;
			unsigned long ICAGRP:2;
			unsigned long :5;
			unsigned long ICACLK:1;
			unsigned long ICAFPU:1;
			unsigned long ICAFPO:1;
			unsigned long ICAFF:1;
			unsigned long ICAFE:1;
			unsigned long ICAFD:1;
			unsigned long ICAFC:1;
			unsigned long ICAFB:1;
			unsigned long ICAFA:1;
		} BIT;
	} GTICCR;
} st_gptw0_t;

typedef struct st_gptw1 {
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long PRKEY:8;
			unsigned long :3;
			unsigned long CMNWP:1;
			unsigned long CLRWP:1;
			unsigned long STPWP:1;
			unsigned long STRWP:1;
			unsigned long WP:1;
		} BIT;
	} GTWP;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CSTRT7:1;
			unsigned long CSTRT6:1;
			unsigned long CSTRT5:1;
			unsigned long CSTRT4:1;
			unsigned long CSTRT3:1;
			unsigned long CSTRT2:1;
			unsigned long CSTRT1:1;
			unsigned long CSTRT0:1;
		} BIT;
	} GTSTR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CSTOP7:1;
			unsigned long CSTOP6:1;
			unsigned long CSTOP5:1;
			unsigned long CSTOP4:1;
			unsigned long CSTOP3:1;
			unsigned long CSTOP2:1;
			unsigned long CSTOP1:1;
			unsigned long CSTOP0:1;
		} BIT;
	} GTSTP;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CCLR7:1;
			unsigned long CCLR6:1;
			unsigned long CCLR5:1;
			unsigned long CCLR4:1;
			unsigned long CCLR3:1;
			unsigned long CCLR2:1;
			unsigned long CCLR1:1;
			unsigned long CCLR0:1;
		} BIT;
	} GTCLR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CSTRT:1;
			unsigned long :7;
			unsigned long SSELCH:1;
			unsigned long SSELCG:1;
			unsigned long SSELCF:1;
			unsigned long SSELCE:1;
			unsigned long SSELCD:1;
			unsigned long SSELCC:1;
			unsigned long SSELCB:1;
			unsigned long SSELCA:1;
			unsigned long SSCBFAH:1;
			unsigned long SSCBFAL:1;
			unsigned long SSCBRAH:1;
			unsigned long SSCBRAL:1;
			unsigned long SSCAFBH:1;
			unsigned long SSCAFBL:1;
			unsigned long SSCARBH:1;
			unsigned long SSCARBL:1;
			unsigned long SSGTRGDF:1;
			unsigned long SSGTRGDR:1;
			unsigned long SSGTRGCF:1;
			unsigned long SSGTRGCR:1;
			unsigned long SSGTRGBF:1;
			unsigned long SSGTRGBR:1;
			unsigned long SSGTRGAF:1;
			unsigned long SSGTRGAR:1;
		} BIT;
	} GTSSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CSTOP:1;
			unsigned long :7;
			unsigned long PSELCH:1;
			unsigned long PSELCG:1;
			unsigned long PSELCF:1;
			unsigned long PSELCE:1;
			unsigned long PSELCD:1;
			unsigned long PSELCC:1;
			unsigned long PSELCB:1;
			unsigned long PSELCA:1;
			unsigned long PSCBFAH:1;
			unsigned long PSCBFAL:1;
			unsigned long PSCBRAH:1;
			unsigned long PSCBRAL:1;
			unsigned long PSCAFBH:1;
			unsigned long PSCAFBL:1;
			unsigned long PSCARBH:1;
			unsigned long PSCARBL:1;
			unsigned long PSGTRGDF:1;
			unsigned long PSGTRGDR:1;
			unsigned long PSGTRGCF:1;
			unsigned long PSGTRGCR:1;
			unsigned long PSGTRGBF:1;
			unsigned long PSGTRGBR:1;
			unsigned long PSGTRGAF:1;
			unsigned long PSGTRGAR:1;
		} BIT;
	} GTPSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CCLR:1;
			unsigned long :3;
			unsigned long CP1CCE:1;
			unsigned long CSCMSC:3;
			unsigned long CSELCH:1;
			unsigned long CSELCG:1;
			unsigned long CSELCF:1;
			unsigned long CSELCE:1;
			unsigned long CSELCD:1;
			unsigned long CSELCC:1;
			unsigned long CSELCB:1;
			unsigned long CSELCA:1;
			unsigned long CSCBFAH:1;
			unsigned long CSCBFAL:1;
			unsigned long CSCBRAH:1;
			unsigned long CSCBRAL:1;
			unsigned long CSCAFBH:1;
			unsigned long CSCAFBL:1;
			unsigned long CSCARBH:1;
			unsigned long CSCARBL:1;
			unsigned long CSGTRGDF:1;
			unsigned long CSGTRGDR:1;
			unsigned long CSGTRGCF:1;
			unsigned long CSGTRGCR:1;
			unsigned long CSGTRGBF:1;
			unsigned long CSGTRGBR:1;
			unsigned long CSGTRGAF:1;
			unsigned long CSGTRGAR:1;
		} BIT;
	} GTCSR;
	char           wk0[8];
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long ASOC:1;
			unsigned long ASELCH:1;
			unsigned long ASELCG:1;
			unsigned long ASELCF:1;
			unsigned long ASELCE:1;
			unsigned long ASELCD:1;
			unsigned long ASELCC:1;
			unsigned long ASELCB:1;
			unsigned long ASELCA:1;
			unsigned long ASCBFAH:1;
			unsigned long ASCBFAL:1;
			unsigned long ASCBRAH:1;
			unsigned long ASCBRAL:1;
			unsigned long ASCAFBH:1;
			unsigned long ASCAFBL:1;
			unsigned long ASCARBH:1;
			unsigned long ASCARBL:1;
			unsigned long ASGTRGDF:1;
			unsigned long ASGTRGDR:1;
			unsigned long ASGTRGCF:1;
			unsigned long ASGTRGCR:1;
			unsigned long ASGTRGBF:1;
			unsigned long ASGTRGBR:1;
			unsigned long ASGTRGAF:1;
			unsigned long ASGTRGAR:1;
		} BIT;
	} GTICASR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long BSOC:1;
			unsigned long BSELCH:1;
			unsigned long BSELCG:1;
			unsigned long BSELCF:1;
			unsigned long BSELCE:1;
			unsigned long BSELCD:1;
			unsigned long BSELCC:1;
			unsigned long BSELCB:1;
			unsigned long BSELCA:1;
			unsigned long BSCBFAH:1;
			unsigned long BSCBFAL:1;
			unsigned long BSCBRAH:1;
			unsigned long BSCBRAL:1;
			unsigned long BSCAFBH:1;
			unsigned long BSCAFBL:1;
			unsigned long BSCARBH:1;
			unsigned long BSCARBL:1;
			unsigned long BSGTRGDF:1;
			unsigned long BSGTRGDR:1;
			unsigned long BSGTRGCF:1;
			unsigned long BSGTRGCR:1;
			unsigned long BSGTRGBF:1;
			unsigned long BSGTRGBR:1;
			unsigned long BSGTRGAF:1;
			unsigned long BSGTRGAR:1;
		} BIT;
	} GTICBSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long CKEG:2;
			unsigned long TPCS:4;
			unsigned long :3;
			unsigned long MD:4;
			unsigned long SSCEN:1;
			unsigned long :3;
			unsigned long SSCGRP:2;
			unsigned long SCGTIOC:1;
			unsigned long ICDS:1;
			unsigned long :7;
			unsigned long CST:1;
		} BIT;
	} GTCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :4;
			unsigned long OBDTYR:1;
			unsigned long OBDTYF:1;
			unsigned long OBDTY:2;
			unsigned long :4;
			unsigned long OADTYR:1;
			unsigned long OADTYF:1;
			unsigned long OADTY:2;
			unsigned long :14;
			unsigned long UDF:1;
			unsigned long UD:1;
		} BIT;
	} GTUDDTYC;
	union {
		unsigned long LONG;
		struct {
			unsigned long NFCSB:2;
			unsigned long NFBEN:1;
			unsigned long :1;
			unsigned long OBEOCD:1;
			unsigned long OBDF:2;
			unsigned long OBE:1;
			unsigned long OBHLD:1;
			unsigned long OBDFLT:1;
			unsigned long :1;
			unsigned long GTIOB:5;
			unsigned long NFCSA:2;
			unsigned long NFAEN:1;
			unsigned long :1;
			unsigned long OAEOCD:1;
			unsigned long OADF:2;
			unsigned long OAE:1;
			unsigned long OAHLD:1;
			unsigned long OADFLT:1;
			unsigned long CPSCIR:1;
			unsigned long GTIOA:5;
		} BIT;
	} GTIOR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long GRPABL:1;
			unsigned long GRPABH:1;
			unsigned long :3;
			unsigned long GRP:2;
			unsigned long :4;
			unsigned long ADTRBDEN:1;
			unsigned long ADTRBUEN:1;
			unsigned long ADTRADEN:1;
			unsigned long ADTRAUEN:1;
			unsigned long SCFPU:1;
			unsigned long SCFPO:1;
			unsigned long SCFF:1;
			unsigned long SCFE:1;
			unsigned long SCFD:1;
			unsigned long SCFC:1;
			unsigned long SCFB:1;
			unsigned long SCFA:1;
			unsigned long GTINTPR:2;
			unsigned long GTINTF:1;
			unsigned long GTINTE:1;
			unsigned long GTINTD:1;
			unsigned long GTINTC:1;
			unsigned long GTINTB:1;
			unsigned long GTINTA:1;
		} BIT;
	} GTINTAD;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long OABLF:1;
			unsigned long OABHF:1;
			unsigned long :4;
			unsigned long ODF:1;
			unsigned long :4;
			unsigned long ADTRBDF:1;
			unsigned long ADTRBUF:1;
			unsigned long ADTRADF:1;
			unsigned long ADTRAUF:1;
			unsigned long TUCF:1;
			unsigned long :4;
			unsigned long ITCNT:3;
			unsigned long TCFPU:1;
			unsigned long TCFPO:1;
			unsigned long TCFF:1;
			unsigned long TCFE:1;
			unsigned long TCFD:1;
			unsigned long TCFC:1;
			unsigned long TCFB:1;
			unsigned long TCFA:1;
		} BIT;
	} GTST;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long ADTDB:1;
			unsigned long ADTTB:2;
			unsigned long :1;
			unsigned long ADTDA:1;
			unsigned long ADTTA:2;
			unsigned long :1;
			unsigned long CCRSWT:1;
			unsigned long PR:2;
			unsigned long CCRB:2;
			unsigned long CCRA:2;
			unsigned long :13;
			unsigned long BD:3;
		} BIT;
	} GTBER;
	union {
		unsigned long LONG;
		struct {
			unsigned long :17;
			unsigned long ADTBL:1;
			unsigned long :1;
			unsigned long ADTAL:1;
			unsigned long :1;
			unsigned long IVTT:3;
			unsigned long IVTC:2;
			unsigned long ITLF:1;
			unsigned long ITLE:1;
			unsigned long ITLD:1;
			unsigned long ITLC:1;
			unsigned long ITLB:1;
			unsigned long ITLA:1;
		} BIT;
	} GTITC;
	unsigned long  GTCNT;
	unsigned long  GTCCRA;
	unsigned long  GTCCRB;
	unsigned long  GTCCRC;
	unsigned long  GTCCRE;
	unsigned long  GTCCRD;
	unsigned long  GTCCRF;
	unsigned long  GTPR;
	unsigned long  GTPBR;
	unsigned long  GTPDBR;
	unsigned long  GTADTRA;
	unsigned long  GTADTBRA;
	unsigned long  GTADTDBRA;
	unsigned long  GTADTRB;
	unsigned long  GTADTBRB;
	unsigned long  GTADTDBRB;
	union {
		unsigned long LONG;
		struct {
			unsigned long :31;
			unsigned long TDE:1;
		} BIT;
	} GTDTCR;
	unsigned long  GTDVU;
	char           wk1[64];
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long SECSEL7:1;
			unsigned long SECSEL6:1;
			unsigned long SECSEL5:1;
			unsigned long SECSEL4:1;
			unsigned long SECSEL3:1;
			unsigned long SECSEL2:1;
			unsigned long SECSEL1:1;
			unsigned long SECSEL0:1;
		} BIT;
	} GTSECSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :6;
			unsigned long SSCD:1;
			unsigned long :7;
			unsigned long SSCE:1;
			unsigned long :6;
			unsigned long SBDAD:1;
			unsigned long SBDPD:1;
			unsigned long SBDCD:1;
			unsigned long :5;
			unsigned long SBDAE:1;
			unsigned long SBDPE:1;
			unsigned long SBDCE:1;
		} BIT;
	} GTSECR;
	char           wk2[20];
	union {
		unsigned long LONG;
		struct {
			unsigned long ICBGRP:2;
			unsigned long :5;
			unsigned long ICBCLK:1;
			unsigned long ICBFPU:1;
			unsigned long ICBFPO:1;
			unsigned long ICBFF:1;
			unsigned long ICBFE:1;
			unsigned long ICBFD:1;
			unsigned long ICBFC:1;
			unsigned long ICBFB:1;
			unsigned long ICBFA:1;
			unsigned long ICAGRP:2;
			unsigned long :5;
			unsigned long ICACLK:1;
			unsigned long ICAFPU:1;
			unsigned long ICAFPO:1;
			unsigned long ICAFF:1;
			unsigned long ICAFE:1;
			unsigned long ICAFD:1;
			unsigned long ICAFC:1;
			unsigned long ICAFB:1;
			unsigned long ICAFA:1;
		} BIT;
	} GTICCR;
} st_gptw1_t;

typedef struct st_gptw3 {
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long PRKEY:8;
			unsigned long :3;
			unsigned long CMNWP:1;
			unsigned long CLRWP:1;
			unsigned long STPWP:1;
			unsigned long STRWP:1;
			unsigned long WP:1;
		} BIT;
	} GTWP;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CSTRT7:1;
			unsigned long CSTRT6:1;
			unsigned long CSTRT5:1;
			unsigned long CSTRT4:1;
			unsigned long CSTRT3:1;
			unsigned long CSTRT2:1;
			unsigned long CSTRT1:1;
			unsigned long CSTRT0:1;
		} BIT;
	} GTSTR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CSTOP7:1;
			unsigned long CSTOP6:1;
			unsigned long CSTOP5:1;
			unsigned long CSTOP4:1;
			unsigned long CSTOP3:1;
			unsigned long CSTOP2:1;
			unsigned long CSTOP1:1;
			unsigned long CSTOP0:1;
		} BIT;
	} GTSTP;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CCLR7:1;
			unsigned long CCLR6:1;
			unsigned long CCLR5:1;
			unsigned long CCLR4:1;
			unsigned long CCLR3:1;
			unsigned long CCLR2:1;
			unsigned long CCLR1:1;
			unsigned long CCLR0:1;
		} BIT;
	} GTCLR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CSTRT:1;
			unsigned long :7;
			unsigned long SSELCH:1;
			unsigned long SSELCG:1;
			unsigned long SSELCF:1;
			unsigned long SSELCE:1;
			unsigned long SSELCD:1;
			unsigned long SSELCC:1;
			unsigned long SSELCB:1;
			unsigned long SSELCA:1;
			unsigned long SSCBFAH:1;
			unsigned long SSCBFAL:1;
			unsigned long SSCBRAH:1;
			unsigned long SSCBRAL:1;
			unsigned long SSCAFBH:1;
			unsigned long SSCAFBL:1;
			unsigned long SSCARBH:1;
			unsigned long SSCARBL:1;
			unsigned long SSGTRGDF:1;
			unsigned long SSGTRGDR:1;
			unsigned long SSGTRGCF:1;
			unsigned long SSGTRGCR:1;
			unsigned long SSGTRGBF:1;
			unsigned long SSGTRGBR:1;
			unsigned long SSGTRGAF:1;
			unsigned long SSGTRGAR:1;
		} BIT;
	} GTSSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CSTOP:1;
			unsigned long :7;
			unsigned long PSELCH:1;
			unsigned long PSELCG:1;
			unsigned long PSELCF:1;
			unsigned long PSELCE:1;
			unsigned long PSELCD:1;
			unsigned long PSELCC:1;
			unsigned long PSELCB:1;
			unsigned long PSELCA:1;
			unsigned long PSCBFAH:1;
			unsigned long PSCBFAL:1;
			unsigned long PSCBRAH:1;
			unsigned long PSCBRAL:1;
			unsigned long PSCAFBH:1;
			unsigned long PSCAFBL:1;
			unsigned long PSCARBH:1;
			unsigned long PSCARBL:1;
			unsigned long PSGTRGDF:1;
			unsigned long PSGTRGDR:1;
			unsigned long PSGTRGCF:1;
			unsigned long PSGTRGCR:1;
			unsigned long PSGTRGBF:1;
			unsigned long PSGTRGBR:1;
			unsigned long PSGTRGAF:1;
			unsigned long PSGTRGAR:1;
		} BIT;
	} GTPSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CCLR:1;
			unsigned long :4;
			unsigned long CSCMSC:3;
			unsigned long CSELCH:1;
			unsigned long CSELCG:1;
			unsigned long CSELCF:1;
			unsigned long CSELCE:1;
			unsigned long CSELCD:1;
			unsigned long CSELCC:1;
			unsigned long CSELCB:1;
			unsigned long CSELCA:1;
			unsigned long CSCBFAH:1;
			unsigned long CSCBFAL:1;
			unsigned long CSCBRAH:1;
			unsigned long CSCBRAL:1;
			unsigned long CSCAFBH:1;
			unsigned long CSCAFBL:1;
			unsigned long CSCARBH:1;
			unsigned long CSCARBL:1;
			unsigned long CSGTRGDF:1;
			unsigned long CSGTRGDR:1;
			unsigned long CSGTRGCF:1;
			unsigned long CSGTRGCR:1;
			unsigned long CSGTRGBF:1;
			unsigned long CSGTRGBR:1;
			unsigned long CSGTRGAF:1;
			unsigned long CSGTRGAR:1;
		} BIT;
	} GTCSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :4;
			unsigned long USILVL:4;
			unsigned long USELCH:1;
			unsigned long USELCG:1;
			unsigned long USELCF:1;
			unsigned long USELCE:1;
			unsigned long USELCD:1;
			unsigned long USELCC:1;
			unsigned long USELCB:1;
			unsigned long USELCA:1;
			unsigned long USCBFAH:1;
			unsigned long USCBFAL:1;
			unsigned long USCBRAH:1;
			unsigned long USCBRAL:1;
			unsigned long USCAFBH:1;
			unsigned long USCAFBL:1;
			unsigned long USCARBH:1;
			unsigned long USCARBL:1;
			unsigned long USGTRGDF:1;
			unsigned long USGTRGDR:1;
			unsigned long USGTRGCF:1;
			unsigned long USGTRGCR:1;
			unsigned long USGTRGBF:1;
			unsigned long USGTRGBR:1;
			unsigned long USGTRGAF:1;
			unsigned long USGTRGAR:1;
		} BIT;
	} GTUPSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :4;
			unsigned long DSILVL:4;
			unsigned long DSELCH:1;
			unsigned long DSELCG:1;
			unsigned long DSELCF:1;
			unsigned long DSELCE:1;
			unsigned long DSELCD:1;
			unsigned long DSELCC:1;
			unsigned long DSELCB:1;
			unsigned long DSELCA:1;
			unsigned long DSCBFAH:1;
			unsigned long DSCBFAL:1;
			unsigned long DSCBRAH:1;
			unsigned long DSCBRAL:1;
			unsigned long DSCAFBH:1;
			unsigned long DSCAFBL:1;
			unsigned long DSCARBH:1;
			unsigned long DSCARBL:1;
			unsigned long DSGTRGDF:1;
			unsigned long DSGTRGDR:1;
			unsigned long DSGTRGCF:1;
			unsigned long DSGTRGCR:1;
			unsigned long DSGTRGBF:1;
			unsigned long DSGTRGBR:1;
			unsigned long DSGTRGAF:1;
			unsigned long DSGTRGAR:1;
		} BIT;
	} GTDNSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long ASOC:1;
			unsigned long ASELCH:1;
			unsigned long ASELCG:1;
			unsigned long ASELCF:1;
			unsigned long ASELCE:1;
			unsigned long ASELCD:1;
			unsigned long ASELCC:1;
			unsigned long ASELCB:1;
			unsigned long ASELCA:1;
			unsigned long ASCBFAH:1;
			unsigned long ASCBFAL:1;
			unsigned long ASCBRAH:1;
			unsigned long ASCBRAL:1;
			unsigned long ASCAFBH:1;
			unsigned long ASCAFBL:1;
			unsigned long ASCARBH:1;
			unsigned long ASCARBL:1;
			unsigned long ASGTRGDF:1;
			unsigned long ASGTRGDR:1;
			unsigned long ASGTRGCF:1;
			unsigned long ASGTRGCR:1;
			unsigned long ASGTRGBF:1;
			unsigned long ASGTRGBR:1;
			unsigned long ASGTRGAF:1;
			unsigned long ASGTRGAR:1;
		} BIT;
	} GTICASR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long BSOC:1;
			unsigned long BSELCH:1;
			unsigned long BSELCG:1;
			unsigned long BSELCF:1;
			unsigned long BSELCE:1;
			unsigned long BSELCD:1;
			unsigned long BSELCC:1;
			unsigned long BSELCB:1;
			unsigned long BSELCA:1;
			unsigned long BSCBFAH:1;
			unsigned long BSCBFAL:1;
			unsigned long BSCBRAH:1;
			unsigned long BSCBRAL:1;
			unsigned long BSCAFBH:1;
			unsigned long BSCAFBL:1;
			unsigned long BSCARBH:1;
			unsigned long BSCARBL:1;
			unsigned long BSGTRGDF:1;
			unsigned long BSGTRGDR:1;
			unsigned long BSGTRGCF:1;
			unsigned long BSGTRGCR:1;
			unsigned long BSGTRGBF:1;
			unsigned long BSGTRGBR:1;
			unsigned long BSGTRGAF:1;
			unsigned long BSGTRGAR:1;
		} BIT;
	} GTICBSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long CKEG:2;
			unsigned long TPCS:4;
			unsigned long :4;
			unsigned long MD:3;
			unsigned long SSCEN:1;
			unsigned long :3;
			unsigned long SSCGRP:2;
			unsigned long SCGTIOC:1;
			unsigned long ICDS:1;
			unsigned long :7;
			unsigned long CST:1;
		} BIT;
	} GTCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :4;
			unsigned long OBDTYR:1;
			unsigned long OBDTYF:1;
			unsigned long OBDTY:2;
			unsigned long :4;
			unsigned long OADTYR:1;
			unsigned long OADTYF:1;
			unsigned long OADTY:2;
			unsigned long :14;
			unsigned long UDF:1;
			unsigned long UD:1;
		} BIT;
	} GTUDDTYC;
	union {
		unsigned long LONG;
		struct {
			unsigned long NFCSB:2;
			unsigned long NFBEN:1;
			unsigned long :2;
			unsigned long OBDF:2;
			unsigned long OBE:1;
			unsigned long OBHLD:1;
			unsigned long OBDFLT:1;
			unsigned long :1;
			unsigned long GTIOB:5;
			unsigned long NFCSA:2;
			unsigned long NFAEN:1;
			unsigned long :2;
			unsigned long OADF:2;
			unsigned long OAE:1;
			unsigned long OAHLD:1;
			unsigned long OADFLT:1;
			unsigned long :1;
			unsigned long GTIOA:5;
		} BIT;
	} GTIOR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long GRPABL:1;
			unsigned long GRPABH:1;
			unsigned long :3;
			unsigned long GRP:2;
			unsigned long :8;
			unsigned long SCFPU:1;
			unsigned long SCFPO:1;
			unsigned long SCFF:1;
			unsigned long SCFE:1;
			unsigned long SCFD:1;
			unsigned long SCFC:1;
			unsigned long SCFB:1;
			unsigned long SCFA:1;
			unsigned long GTINTPR:2;
			unsigned long GTINTF:1;
			unsigned long GTINTE:1;
			unsigned long GTINTD:1;
			unsigned long GTINTC:1;
			unsigned long GTINTB:1;
			unsigned long GTINTA:1;
		} BIT;
	} GTINTAD;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long OABLF:1;
			unsigned long OABHF:1;
			unsigned long :4;
			unsigned long ODF:1;
			unsigned long :8;
			unsigned long TUCF:1;
			unsigned long :7;
			unsigned long TCFPU:1;
			unsigned long TCFPO:1;
			unsigned long TCFF:1;
			unsigned long TCFE:1;
			unsigned long TCFD:1;
			unsigned long TCFC:1;
			unsigned long TCFB:1;
			unsigned long TCFA:1;
		} BIT;
	} GTST;
	union {
		unsigned long LONG;
		struct {
			unsigned long :9;
			unsigned long CCRSWT:1;
			unsigned long :1;
			unsigned long PR:1;
			unsigned long CCRB:2;
			unsigned long CCRA:2;
			unsigned long :14;
			unsigned long BD:2;
		} BIT;
	} GTBER;
	char           wk0[4];
	unsigned long  GTCNT;
	unsigned long  GTCCRA;
	unsigned long  GTCCRB;
	unsigned long  GTCCRC;
	unsigned long  GTCCRE;
	unsigned long  GTCCRD;
	unsigned long  GTCCRF;
	unsigned long  GTPR;
	unsigned long  GTPBR;
	char           wk1[100];
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long SECSEL7:1;
			unsigned long SECSEL6:1;
			unsigned long SECSEL5:1;
			unsigned long SECSEL4:1;
			unsigned long SECSEL3:1;
			unsigned long SECSEL2:1;
			unsigned long SECSEL1:1;
			unsigned long SECSEL0:1;
		} BIT;
	} GTSECSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :6;
			unsigned long SSCD:1;
			unsigned long :7;
			unsigned long SSCE:1;
			unsigned long :7;
			unsigned long SBDPD:1;
			unsigned long SBDCD:1;
			unsigned long :6;
			unsigned long SBDPE:1;
			unsigned long SBDCE:1;
		} BIT;
	} GTSECR;
	char           wk2[20];
	union {
		unsigned long LONG;
		struct {
			unsigned long ICBGRP:2;
			unsigned long :5;
			unsigned long ICBCLK:1;
			unsigned long ICBFPU:1;
			unsigned long ICBFPO:1;
			unsigned long ICBFF:1;
			unsigned long ICBFE:1;
			unsigned long ICBFD:1;
			unsigned long ICBFC:1;
			unsigned long ICBFB:1;
			unsigned long ICBFA:1;
			unsigned long ICAGRP:2;
			unsigned long :5;
			unsigned long ICACLK:1;
			unsigned long ICAFPU:1;
			unsigned long ICAFPO:1;
			unsigned long ICAFF:1;
			unsigned long ICAFE:1;
			unsigned long ICAFD:1;
			unsigned long ICAFC:1;
			unsigned long ICAFB:1;
			unsigned long ICAFA:1;
		} BIT;
	} GTICCR;
} st_gptw3_t;

typedef struct st_gptw6 {
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long PRKEY:8;
			unsigned long :3;
			unsigned long CMNWP:1;
			unsigned long CLRWP:1;
			unsigned long STPWP:1;
			unsigned long STRWP:1;
			unsigned long WP:1;
		} BIT;
	} GTWP;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CSTRT7:1;
			unsigned long CSTRT6:1;
			unsigned long CSTRT5:1;
			unsigned long CSTRT4:1;
			unsigned long CSTRT3:1;
			unsigned long CSTRT2:1;
			unsigned long CSTRT1:1;
			unsigned long CSTRT0:1;
		} BIT;
	} GTSTR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CSTOP7:1;
			unsigned long CSTOP6:1;
			unsigned long CSTOP5:1;
			unsigned long CSTOP4:1;
			unsigned long CSTOP3:1;
			unsigned long CSTOP2:1;
			unsigned long CSTOP1:1;
			unsigned long CSTOP0:1;
		} BIT;
	} GTSTP;
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long CCLR7:1;
			unsigned long CCLR6:1;
			unsigned long CCLR5:1;
			unsigned long CCLR4:1;
			unsigned long CCLR3:1;
			unsigned long CCLR2:1;
			unsigned long CCLR1:1;
			unsigned long CCLR0:1;
		} BIT;
	} GTCLR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CSTRT:1;
			unsigned long :7;
			unsigned long SSELCH:1;
			unsigned long SSELCG:1;
			unsigned long SSELCF:1;
			unsigned long SSELCE:1;
			unsigned long SSELCD:1;
			unsigned long SSELCC:1;
			unsigned long SSELCB:1;
			unsigned long SSELCA:1;
			unsigned long SSCBFAH:1;
			unsigned long SSCBFAL:1;
			unsigned long SSCBRAH:1;
			unsigned long SSCBRAL:1;
			unsigned long SSCAFBH:1;
			unsigned long SSCAFBL:1;
			unsigned long SSCARBH:1;
			unsigned long SSCARBL:1;
			unsigned long SSGTRGDF:1;
			unsigned long SSGTRGDR:1;
			unsigned long SSGTRGCF:1;
			unsigned long SSGTRGCR:1;
			unsigned long SSGTRGBF:1;
			unsigned long SSGTRGBR:1;
			unsigned long SSGTRGAF:1;
			unsigned long SSGTRGAR:1;
		} BIT;
	} GTSSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CSTOP:1;
			unsigned long :7;
			unsigned long PSELCH:1;
			unsigned long PSELCG:1;
			unsigned long PSELCF:1;
			unsigned long PSELCE:1;
			unsigned long PSELCD:1;
			unsigned long PSELCC:1;
			unsigned long PSELCB:1;
			unsigned long PSELCA:1;
			unsigned long PSCBFAH:1;
			unsigned long PSCBFAL:1;
			unsigned long PSCBRAH:1;
			unsigned long PSCBRAL:1;
			unsigned long PSCAFBH:1;
			unsigned long PSCAFBL:1;
			unsigned long PSCARBH:1;
			unsigned long PSCARBL:1;
			unsigned long PSGTRGDF:1;
			unsigned long PSGTRGDR:1;
			unsigned long PSGTRGCF:1;
			unsigned long PSGTRGCR:1;
			unsigned long PSGTRGBF:1;
			unsigned long PSGTRGBR:1;
			unsigned long PSGTRGAF:1;
			unsigned long PSGTRGAR:1;
		} BIT;
	} GTPSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CCLR:1;
			unsigned long :4;
			unsigned long CSCMSC:3;
			unsigned long CSELCH:1;
			unsigned long CSELCG:1;
			unsigned long CSELCF:1;
			unsigned long CSELCE:1;
			unsigned long CSELCD:1;
			unsigned long CSELCC:1;
			unsigned long CSELCB:1;
			unsigned long CSELCA:1;
			unsigned long CSCBFAH:1;
			unsigned long CSCBFAL:1;
			unsigned long CSCBRAH:1;
			unsigned long CSCBRAL:1;
			unsigned long CSCAFBH:1;
			unsigned long CSCAFBL:1;
			unsigned long CSCARBH:1;
			unsigned long CSCARBL:1;
			unsigned long CSGTRGDF:1;
			unsigned long CSGTRGDR:1;
			unsigned long CSGTRGCF:1;
			unsigned long CSGTRGCR:1;
			unsigned long CSGTRGBF:1;
			unsigned long CSGTRGBR:1;
			unsigned long CSGTRGAF:1;
			unsigned long CSGTRGAR:1;
		} BIT;
	} GTCSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :8;
			unsigned long USELCH:1;
			unsigned long USELCG:1;
			unsigned long USELCF:1;
			unsigned long USELCE:1;
			unsigned long USELCD:1;
			unsigned long USELCC:1;
			unsigned long USELCB:1;
			unsigned long USELCA:1;
			unsigned long USCBFAH:1;
			unsigned long USCBFAL:1;
			unsigned long USCBRAH:1;
			unsigned long USCBRAL:1;
			unsigned long USCAFBH:1;
			unsigned long USCAFBL:1;
			unsigned long USCARBH:1;
			unsigned long USCARBL:1;
			unsigned long USGTRGDF:1;
			unsigned long USGTRGDR:1;
			unsigned long USGTRGCF:1;
			unsigned long USGTRGCR:1;
			unsigned long USGTRGBF:1;
			unsigned long USGTRGBR:1;
			unsigned long USGTRGAF:1;
			unsigned long USGTRGAR:1;
		} BIT;
	} GTUPSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :8;
			unsigned long DSELCH:1;
			unsigned long DSELCG:1;
			unsigned long DSELCF:1;
			unsigned long DSELCE:1;
			unsigned long DSELCD:1;
			unsigned long DSELCC:1;
			unsigned long DSELCB:1;
			unsigned long DSELCA:1;
			unsigned long DSCBFAH:1;
			unsigned long DSCBFAL:1;
			unsigned long DSCBRAH:1;
			unsigned long DSCBRAL:1;
			unsigned long DSCAFBH:1;
			unsigned long DSCAFBL:1;
			unsigned long DSCARBH:1;
			unsigned long DSCARBL:1;
			unsigned long DSGTRGDF:1;
			unsigned long DSGTRGDR:1;
			unsigned long DSGTRGCF:1;
			unsigned long DSGTRGCR:1;
			unsigned long DSGTRGBF:1;
			unsigned long DSGTRGBR:1;
			unsigned long DSGTRGAF:1;
			unsigned long DSGTRGAR:1;
		} BIT;
	} GTDNSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long ASOC:1;
			unsigned long ASELCH:1;
			unsigned long ASELCG:1;
			unsigned long ASELCF:1;
			unsigned long ASELCE:1;
			unsigned long ASELCD:1;
			unsigned long ASELCC:1;
			unsigned long ASELCB:1;
			unsigned long ASELCA:1;
			unsigned long ASCBFAH:1;
			unsigned long ASCBFAL:1;
			unsigned long ASCBRAH:1;
			unsigned long ASCBRAL:1;
			unsigned long ASCAFBH:1;
			unsigned long ASCAFBL:1;
			unsigned long ASCARBH:1;
			unsigned long ASCARBL:1;
			unsigned long ASGTRGDF:1;
			unsigned long ASGTRGDR:1;
			unsigned long ASGTRGCF:1;
			unsigned long ASGTRGCR:1;
			unsigned long ASGTRGBF:1;
			unsigned long ASGTRGBR:1;
			unsigned long ASGTRGAF:1;
			unsigned long ASGTRGAR:1;
		} BIT;
	} GTICASR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long BSOC:1;
			unsigned long BSELCH:1;
			unsigned long BSELCG:1;
			unsigned long BSELCF:1;
			unsigned long BSELCE:1;
			unsigned long BSELCD:1;
			unsigned long BSELCC:1;
			unsigned long BSELCB:1;
			unsigned long BSELCA:1;
			unsigned long BSCBFAH:1;
			unsigned long BSCBFAL:1;
			unsigned long BSCBRAH:1;
			unsigned long BSCBRAL:1;
			unsigned long BSCAFBH:1;
			unsigned long BSCAFBL:1;
			unsigned long BSCARBH:1;
			unsigned long BSCARBL:1;
			unsigned long BSGTRGDF:1;
			unsigned long BSGTRGDR:1;
			unsigned long BSGTRGCF:1;
			unsigned long BSGTRGCR:1;
			unsigned long BSGTRGBF:1;
			unsigned long BSGTRGBR:1;
			unsigned long BSGTRGAF:1;
			unsigned long BSGTRGAR:1;
		} BIT;
	} GTICBSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long CKEG:2;
			unsigned long TPCS:4;
			unsigned long :4;
			unsigned long MD:3;
			unsigned long SSCEN:1;
			unsigned long :3;
			unsigned long SSCGRP:2;
			unsigned long SCGTIOC:1;
			unsigned long ICDS:1;
			unsigned long :7;
			unsigned long CST:1;
		} BIT;
	} GTCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :4;
			unsigned long OBDTYR:1;
			unsigned long OBDTYF:1;
			unsigned long OBDTY:2;
			unsigned long :4;
			unsigned long OADTYR:1;
			unsigned long OADTYF:1;
			unsigned long OADTY:2;
			unsigned long :14;
			unsigned long UDF:1;
			unsigned long UD:1;
		} BIT;
	} GTUDDTYC;
	union {
		unsigned long LONG;
		struct {
			unsigned long NFCSB:2;
			unsigned long NFBEN:1;
			unsigned long :2;
			unsigned long OBDF:2;
			unsigned long OBE:1;
			unsigned long OBHLD:1;
			unsigned long OBDFLT:1;
			unsigned long :1;
			unsigned long GTIOB:5;
			unsigned long NFCSA:2;
			unsigned long NFAEN:1;
			unsigned long :2;
			unsigned long OADF:2;
			unsigned long OAE:1;
			unsigned long OAHLD:1;
			unsigned long OADFLT:1;
			unsigned long :1;
			unsigned long GTIOA:5;
		} BIT;
	} GTIOR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long GRPABL:1;
			unsigned long GRPABH:1;
			unsigned long :3;
			unsigned long GRP:2;
			unsigned long :8;
			unsigned long SCFPU:1;
			unsigned long SCFPO:1;
			unsigned long SCFF:1;
			unsigned long SCFE:1;
			unsigned long SCFD:1;
			unsigned long SCFC:1;
			unsigned long SCFB:1;
			unsigned long SCFA:1;
			unsigned long GTINTPR:2;
			unsigned long GTINTF:1;
			unsigned long GTINTE:1;
			unsigned long GTINTD:1;
			unsigned long GTINTC:1;
			unsigned long GTINTB:1;
			unsigned long GTINTA:1;
		} BIT;
	} GTINTAD;
	union {
		unsigned long LONG;
		struct {
			unsigned long :1;
			unsigned long OABLF:1;
			unsigned long OABHF:1;
			unsigned long :4;
			unsigned long ODF:1;
			unsigned long :8;
			unsigned long TUCF:1;
			unsigned long :7;
			unsigned long TCFPU:1;
			unsigned long TCFPO:1;
			unsigned long TCFF:1;
			unsigned long TCFE:1;
			unsigned long TCFD:1;
			unsigned long TCFC:1;
			unsigned long TCFB:1;
			unsigned long TCFA:1;
		} BIT;
	} GTST;
	union {
		unsigned long LONG;
		struct {
			unsigned long :9;
			unsigned long CCRSWT:1;
			unsigned long :1;
			unsigned long PR:1;
			unsigned long CCRB:2;
			unsigned long CCRA:2;
			unsigned long :14;
			unsigned long BD:2;
		} BIT;
	} GTBER;
	char           wk0[4];
	unsigned long  GTCNT;
	unsigned long  GTCCRA;
	unsigned long  GTCCRB;
	unsigned long  GTCCRC;
	unsigned long  GTCCRE;
	unsigned long  GTCCRD;
	unsigned long  GTCCRF;
	unsigned long  GTPR;
	unsigned long  GTPBR;
	char           wk1[100];
	union {
		unsigned long LONG;
		struct {
			unsigned long :24;
			unsigned long SECSEL7:1;
			unsigned long SECSEL6:1;
			unsigned long SECSEL5:1;
			unsigned long SECSEL4:1;
			unsigned long SECSEL3:1;
			unsigned long SECSEL2:1;
			unsigned long SECSEL1:1;
			unsigned long SECSEL0:1;
		} BIT;
	} GTSECSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :6;
			unsigned long SSCD:1;
			unsigned long :7;
			unsigned long SSCE:1;
			unsigned long :7;
			unsigned long SBDPD:1;
			unsigned long SBDCD:1;
			unsigned long :6;
			unsigned long SBDPE:1;
			unsigned long SBDCE:1;
		} BIT;
	} GTSECR;
	char           wk2[20];
	union {
		unsigned long LONG;
		struct {
			unsigned long ICBGRP:2;
			unsigned long :5;
			unsigned long ICBCLK:1;
			unsigned long ICBFPU:1;
			unsigned long ICBFPO:1;
			unsigned long ICBFF:1;
			unsigned long ICBFE:1;
			unsigned long ICBFD:1;
			unsigned long ICBFC:1;
			unsigned long ICBFB:1;
			unsigned long ICBFA:1;
			unsigned long ICAGRP:2;
			unsigned long :5;
			unsigned long ICACLK:1;
			unsigned long ICAFPU:1;
			unsigned long ICAFPO:1;
			unsigned long ICAFF:1;
			unsigned long ICAFE:1;
			unsigned long ICAFD:1;
			unsigned long ICAFC:1;
			unsigned long ICAFB:1;
			unsigned long ICAFA:1;
		} BIT;
	} GTICCR;
} st_gptw6_t;

typedef struct st_icu {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char IR:1;
		} BIT;
	} IR[256];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char DTCE:1;
		} BIT;
	} DTCER[256];
	union {
		unsigned char BYTE;
		struct {
			unsigned char IEN7:1;
			unsigned char IEN6:1;
			unsigned char IEN5:1;
			unsigned char IEN4:1;
			unsigned char IEN3:1;
			unsigned char IEN2:1;
			unsigned char IEN1:1;
			unsigned char IEN0:1;
		} BIT;
	} IER[32];
	char           wk0[192];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char SWINT:1;
		} BIT;
	} SWINTR;
	char           wk1[15];
	union {
		unsigned short WORD;
		struct {
			unsigned short FIEN:1;
			unsigned short :7;
			unsigned short FVCT:8;
		} BIT;
	} FIR;
	char           wk2[14];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char IPR:4;
		} BIT;
	} IPR[256];
	unsigned char  DMRSR0;
	char           wk3[3];
	unsigned char  DMRSR1;
	char           wk4[3];
	unsigned char  DMRSR2;
	char           wk5[3];
	unsigned char  DMRSR3;
	char           wk6[243];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char IRQMD:2;
			unsigned char :2;
		} BIT;
	} IRQCR[8];
	char           wk7[8];
	union {
		unsigned char BYTE;
		struct {
			unsigned char FLTEN7:1;
			unsigned char FLTEN6:1;
			unsigned char FLTEN5:1;
			unsigned char FLTEN4:1;
			unsigned char FLTEN3:1;
			unsigned char FLTEN2:1;
			unsigned char FLTEN1:1;
			unsigned char FLTEN0:1;
		} BIT;
	} IRQFLTE0;
	char           wk8[3];
	union {
		unsigned short WORD;
		struct {
			unsigned short FCLKSEL7:2;
			unsigned short FCLKSEL6:2;
			unsigned short FCLKSEL5:2;
			unsigned short FCLKSEL4:2;
			unsigned short FCLKSEL3:2;
			unsigned short FCLKSEL2:2;
			unsigned short FCLKSEL1:2;
			unsigned short FCLKSEL0:2;
		} BIT;
	} IRQFLTC0;
	char           wk9[106];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char RAMST:1;
			unsigned char LVD2ST:1;
			unsigned char LVD1ST:1;
			unsigned char IWDTST:1;
			unsigned char WDTST:1;
			unsigned char OSTST:1;
			unsigned char NMIST:1;
		} BIT;
	} NMISR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char RAMEN:1;
			unsigned char LVD2EN:1;
			unsigned char LVD1EN:1;
			unsigned char IWDTEN:1;
			unsigned char WDTEN:1;
			unsigned char OSTEN:1;
			unsigned char NMIEN:1;
		} BIT;
	} NMIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char LVD2CLR:1;
			unsigned char LVD1CLR:1;
			unsigned char IWDTCLR:1;
			unsigned char WDTCLR:1;
			unsigned char OSTCLR:1;
			unsigned char NMICLR:1;
		} BIT;
	} NMICLR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char NMIMD:1;
			unsigned char :3;
		} BIT;
	} NMICR;
	char           wk10[12];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char NFLTEN:1;
		} BIT;
	} NMIFLTE;
	char           wk11[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char NFCLKSEL:2;
		} BIT;
	} NMIFLTC;
} st_icu_t;

typedef struct st_iwdt {
	unsigned char  IWDTRR;
	char           wk0[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short RPSS:2;
			unsigned short :2;
			unsigned short RPES:2;
			unsigned short CKS:4;
			unsigned short :2;
			unsigned short TOPS:2;
		} BIT;
	} IWDTCR;
	union {
		unsigned short WORD;
		struct {
			unsigned short REFEF:1;
			unsigned short UNDFF:1;
			unsigned short CNTVAL:14;
		} BIT;
	} IWDTSR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RSTIRQS:1;
			unsigned char :7;
		} BIT;
	} IWDTRCR;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char SLCSTP:1;
			unsigned char :7;
		} BIT;
	} IWDTCSTPR;
} st_iwdt_t;

typedef struct st_lpt {
	union {
		unsigned char BYTE;
		struct {
			unsigned char LPCMRE1:1;
			unsigned char LPCMRE0:1;
			unsigned char :1;
			unsigned char LPCNTCKSEL:1;
			unsigned char LPCNTCKSEL2:1;
			unsigned char LPCNTPSSEL:3;
		} BIT;
	} LPTCR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PWME:1;
			unsigned char OLVL:1;
			unsigned char OPOL:1;
			unsigned char :4;
			unsigned char LPCNTSTP:1;
		} BIT;
	} LPTCR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char LPCNTRST:1;
			unsigned char LPCNTEN:1;
		} BIT;
	} LPTCR3;
	char           wk0[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short LPCNTPRD:16;
		} BIT;
	} LPTPRD;
	char           wk1[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short LPCMR0:16;
		} BIT;
	} LPCMR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short LPCMR1:16;
		} BIT;
	} LPCMR1;
	union {
		unsigned short WORD;
		struct {
			unsigned short LPWKUPEN:1;
			unsigned short :15;
		} BIT;
	} LPWUCR;
} st_lpt_t;

typedef struct st_mpc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B0WI:1;
			unsigned char PFSWE:1;
			unsigned char :6;
		} BIT;
	} PWPR;
	char           wk0[35];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P03PFS;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P05PFS;
	char           wk2[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P07PFS;
	char           wk3[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P12PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P13PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P14PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P15PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P16PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P17PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P20PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P21PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P22PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P23PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P24PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P25PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P26PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P27PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P30PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P31PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P32PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P33PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} P34PFS;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :6;
		} BIT;
	} P36PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :6;
		} BIT;
	} P37PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P40PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P41PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P42PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P43PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P44PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P45PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P46PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} P47PFS;
	char           wk5[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P51PFS;
	char           wk6[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P53PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P54PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} P55PFS;
	char           wk7[34];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PA3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PA4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PA7PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PB1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PB7PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PC7PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PD2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :6;
		} BIT;
	} PD3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :6;
		} BIT;
	} PD4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :6;
		} BIT;
	} PD5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :6;
		} BIT;
	} PD6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :6;
		} BIT;
	} PD7PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} PE0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} PE1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PE2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} PE3PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :2;
			unsigned char PSEL:5;
		} BIT;
	} PE4PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PE5PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :6;
		} BIT;
	} PE6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char ISEL:1;
			unsigned char :6;
		} BIT;
	} PE7PFS;
	char           wk8[16];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PH0PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PH1PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char ISEL:1;
			unsigned char :1;
			unsigned char PSEL:5;
		} BIT;
	} PH2PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PH3PFS;
	char           wk9[5];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PJ1PFS;
	char           wk10[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PSEL:5;
		} BIT;
	} PJ3PFS;
	char           wk11[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} PJ6PFS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ASEL:1;
			unsigned char :7;
		} BIT;
	} PJ7PFS;
} st_mpc_t;

typedef struct st_mpu {
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE0;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE0;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE1;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE1;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE2;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE2;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE3;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE3;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE4;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE4;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE5;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE5;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE6;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE6;
	union {
		unsigned long LONG;
		struct {
			unsigned long RSPN:28;
			unsigned long :4;
		} BIT;
	} RSPAGE7;
	union {
		unsigned long LONG;
		struct {
			unsigned long REPN:28;
			unsigned long UAC:3;
			unsigned long V:1;
		} BIT;
	} REPAGE7;
	char           wk0[192];
	union {
		unsigned long LONG;
		struct {
			unsigned long :31;
			unsigned long MPEN:1;
		} BIT;
	} MPEN;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long UBAC:3;
			unsigned long :1;
		} BIT;
	} MPBAC;
	union {
		unsigned long LONG;
		struct {
			unsigned long :31;
			unsigned long CLR:1;
		} BIT;
	} MPECLR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :29;
			unsigned long DRW:1;
			unsigned long DMPER:1;
			unsigned long IMPER:1;
		} BIT;
	} MPESTS;
	char           wk1[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long DEA:32;
		} BIT;
	} MPDEA;
	char           wk2[8];
	union {
		unsigned long LONG;
		struct {
			unsigned long SA:32;
		} BIT;
	} MPSA;
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short S:1;
		} BIT;
	} MPOPS;
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short INV:1;
		} BIT;
	} MPOPI;
	union {
		unsigned long LONG;
		struct {
			unsigned long :8;
			unsigned long HITI:8;
			unsigned long :12;
			unsigned long UHACI:3;
			unsigned long :1;
		} BIT;
	} MHITI;
	union {
		unsigned long LONG;
		struct {
			unsigned long :8;
			unsigned long HITD:8;
			unsigned long :12;
			unsigned long UHACD:3;
			unsigned long :1;
		} BIT;
	} MHITD;
} st_mpu_t;

typedef struct st_ofsm {
	union {
		unsigned long LONG;
		struct {
			unsigned long :29;
			unsigned long MDE:3;
		} BIT;
	} MDE;
	char           wk0[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long :18;
			unsigned long HOCOFRQ:2;
			unsigned long :3;
			unsigned long HOCOEN:1;
			unsigned long :3;
			unsigned long VDSEL2:1;
			unsigned long FASTSTUP:1;
			unsigned long LVDAS:1;
			unsigned long VDSEL:2;
		} BIT;
	} OFS1;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long WDTRSTIRQS:1;
			unsigned long WDTRPSS:2;
			unsigned long WDTRPES:2;
			unsigned long WDTCKS:4;
			unsigned long WDTTOPS:2;
			unsigned long WDTSTRT:1;
			unsigned long :2;
			unsigned long IWDTSLCSTP:1;
			unsigned long :1;
			unsigned long IWDTRSTIRQS:1;
			unsigned long IWDTRPSS:2;
			unsigned long IWDTRPES:2;
			unsigned long IWDTCKS:4;
			unsigned long IWDTTOPS:2;
			unsigned long IWDTSTRT:1;
			unsigned long :1;
		} BIT;
	} OFS0;
} st_ofsm_t;

typedef struct st_poeg {
	union {
		unsigned long LONG;
		struct {
			unsigned long NFCS:2;
			unsigned long NFEN:1;
			unsigned long INV:1;
			unsigned long :11;
			unsigned long ST:1;
			unsigned long :6;
			unsigned long CDRE1:1;
			unsigned long CDRE0:1;
			unsigned long :1;
			unsigned long OSTPE:1;
			unsigned long IOCE:1;
			unsigned long PIDE:1;
			unsigned long SSF:1;
			unsigned long OSTPF:1;
			unsigned long IOCF:1;
			unsigned long PIDF:1;
		} BIT;
	} POEGGA;
	char           wk0[252];
	union {
		unsigned long LONG;
		struct {
			unsigned long NFCS:2;
			unsigned long NFEN:1;
			unsigned long INV:1;
			unsigned long :11;
			unsigned long ST:1;
			unsigned long :6;
			unsigned long CDRE1:1;
			unsigned long CDRE0:1;
			unsigned long :1;
			unsigned long OSTPE:1;
			unsigned long IOCE:1;
			unsigned long PIDE:1;
			unsigned long SSF:1;
			unsigned long OSTPF:1;
			unsigned long IOCF:1;
			unsigned long PIDF:1;
		} BIT;
	} POEGGB;
	char           wk1[252];
	union {
		unsigned long LONG;
		struct {
			unsigned long NFCS:2;
			unsigned long NFEN:1;
			unsigned long INV:1;
			unsigned long :11;
			unsigned long ST:1;
			unsigned long :6;
			unsigned long CDRE1:1;
			unsigned long CDRE0:1;
			unsigned long :1;
			unsigned long OSTPE:1;
			unsigned long IOCE:1;
			unsigned long PIDE:1;
			unsigned long SSF:1;
			unsigned long OSTPF:1;
			unsigned long IOCF:1;
			unsigned long PIDF:1;
		} BIT;
	} POEGGC;
	char           wk2[252];
	union {
		unsigned long LONG;
		struct {
			unsigned long NFCS:2;
			unsigned long NFEN:1;
			unsigned long INV:1;
			unsigned long :11;
			unsigned long ST:1;
			unsigned long :6;
			unsigned long CDRE1:1;
			unsigned long CDRE0:1;
			unsigned long :1;
			unsigned long OSTPE:1;
			unsigned long IOCE:1;
			unsigned long PIDE:1;
			unsigned long SSF:1;
			unsigned long OSTPF:1;
			unsigned long IOCF:1;
			unsigned long PIDF:1;
		} BIT;
	} POEGGD;
} st_poeg_t;

typedef struct st_port {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char PSEL5:1;
			unsigned char :1;
			unsigned char PSEL3:1;
			unsigned char :1;
			unsigned char PSEL1:1;
			unsigned char PSEL0:1;
		} BIT;
	} PSRB;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PSEL7:1;
			unsigned char PSEL6:1;
			unsigned char :6;
		} BIT;
	} PSRA;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char WAIT:2;
		} BIT;
	} PRWCNTR;
} st_port_t;

typedef struct st_port0 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :1;
			unsigned char B5:1;
			unsigned char :1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PMR;
	char           wk3[95];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char :3;
		} BIT;
	} PCR;
} st_port0_t;

typedef struct st_port1 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PMR;
	char           wk3[32];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :4;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[61];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :2;
		} BIT;
	} PCR;
} st_port1_t;

typedef struct st_port2 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[33];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[60];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_port2_t;

typedef struct st_port3 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[34];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :3;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[59];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_port3_t;

typedef struct st_port4 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[95];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_port4_t;

typedef struct st_port5 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char :1;
			unsigned char B1:1;
			unsigned char :1;
		} BIT;
	} PMR;
	char           wk3[36];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[57];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_port5_t;

typedef struct st_porta {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[41];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[52];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_porta_t;

typedef struct st_portb {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[42];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[51];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_portb_t;

typedef struct st_portc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[43];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[50];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_portc_t;

typedef struct st_portd {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[44];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	char           wk4[50];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_portd_t;

typedef struct st_porte {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[45];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :1;
			unsigned char B4:1;
			unsigned char :1;
			unsigned char B2:1;
			unsigned char :1;
			unsigned char B0:1;
		} BIT;
	} ODR1;
	char           wk4[48];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char B5:1;
			unsigned char B4:1;
			unsigned char B3:1;
			unsigned char B2:1;
			unsigned char B1:1;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_porte_t;

typedef struct st_portg {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :7;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :7;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :7;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :7;
		} BIT;
	} PMR;
	char           wk3[48];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char B6:1;
			unsigned char :6;
		} BIT;
	} ODR1;
	char           wk4[46];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char :7;
		} BIT;
	} PCR;
} st_portg_t;

typedef struct st_porth {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :2;
			unsigned char B3:1;
			unsigned char :2;
			unsigned char B0:1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char :2;
			unsigned char B0:1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :2;
			unsigned char B3:1;
			unsigned char :2;
			unsigned char B0:1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char :2;
			unsigned char B0:1;
		} BIT;
	} PMR;
	char           wk3[95];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char B3:1;
			unsigned char :2;
			unsigned char B0:1;
		} BIT;
	} PCR;
} st_porth_t;

typedef struct st_portj {
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :2;
			unsigned char B3:1;
			unsigned char :1;
			unsigned char B1:1;
			unsigned char :1;
		} BIT;
	} PDR;
	char           wk0[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :2;
			unsigned char B3:1;
			unsigned char :1;
			unsigned char B1:1;
			unsigned char :1;
		} BIT;
	} PODR;
	char           wk1[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :2;
			unsigned char B3:1;
			unsigned char :1;
			unsigned char B1:1;
			unsigned char :1;
		} BIT;
	} PIDR;
	char           wk2[31];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :2;
			unsigned char B3:1;
			unsigned char :1;
			unsigned char B1:1;
			unsigned char :1;
		} BIT;
	} PMR;
	char           wk3[95];
	union {
		unsigned char BYTE;
		struct {
			unsigned char B7:1;
			unsigned char B6:1;
			unsigned char :2;
			unsigned char B3:1;
			unsigned char :1;
			unsigned char B1:1;
			unsigned char :1;
		} BIT;
	} PCR;
} st_portj_t;

typedef struct st_ram {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char RAMMODE:2;
		} BIT;
	} RAMMODE;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char RAMERR:1;
		} BIT;
	} RAMSTS;
	char           wk0[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char KW:7;
			unsigned char RAMPRCR:1;
		} BIT;
	} RAMPRCR;
	char           wk1[3];
	union {
		unsigned long LONG;
		struct {
			unsigned long :13;
			unsigned long READ:16;
			unsigned long :3;
		} BIT;
	} RAMECAD;
} st_ram_t;

typedef struct st_remc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char FILSEL:1;
			unsigned char :1;
			unsigned char EC:1;
			unsigned char INFLG:1;
			unsigned char FIL:1;
			unsigned char INV:1;
			unsigned char ENFLG:1;
		} BIT;
	} REMCON0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char INTMD:1;
			unsigned char CSRC:4;
			unsigned char EN:1;
			unsigned char TYP:2;
		} BIT;
	} REMCON1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SDFLG:1;
			unsigned char D1FLG:1;
			unsigned char D0FLG:1;
			unsigned char HDFLG:1;
			unsigned char BFULFLG:1;
			unsigned char DRFLG:1;
			unsigned char REFLG:1;
			unsigned char CPFLG:1;
		} BIT;
	} REMSTS;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SDINT:1;
			unsigned char :1;
			unsigned char DINT:1;
			unsigned char HDINT:1;
			unsigned char BFULINT:1;
			unsigned char DRINT:1;
			unsigned char REINT:1;
			unsigned char CPINT:1;
		} BIT;
	} REMINT;
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char CPN:4;
		} BIT;
	} REMCPC;
	union {
		unsigned short WORD;
		struct {
			unsigned short CPD:16;
		} BIT;
	} REMCPD;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short HDPMIN:11;
		} BIT;
	} HDPMIN;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short HDPMAX:11;
		} BIT;
	} HDPMAX;
	union {
		unsigned char BYTE;
		struct {
			unsigned char D0PMIN:8;
		} BIT;
	} D0PMIN;
	union {
		unsigned char BYTE;
		struct {
			unsigned char D0PMAX:8;
		} BIT;
	} D0PMAX;
	union {
		unsigned char BYTE;
		struct {
			unsigned char D1PMIN:8;
		} BIT;
	} D1PMIN;
	union {
		unsigned char BYTE;
		struct {
			unsigned char D1PMAX:8;
		} BIT;
	} D1PMAX;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short SDPMIN:11;
		} BIT;
	} SDPMIN;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short SDPMAX:11;
		} BIT;
	} SDPMAX;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short PE:11;
		} BIT;
	} REMPE;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char DNFSL:1;
			unsigned char LPCE:1;
		} BIT;
	} REMSTC;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char RBIT:7;
		} BIT;
	} REMRBIT;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAT0:8;
		} BIT;
	} REMDAT0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAT1:8;
		} BIT;
	} REMDAT1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAT2:8;
		} BIT;
	} REMDAT2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAT3:8;
		} BIT;
	} REMDAT3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAT4:8;
		} BIT;
	} REMDAT4;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAT5:8;
		} BIT;
	} REMDAT5;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAT6:8;
		} BIT;
	} REMDAT6;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DAT7:8;
		} BIT;
	} REMDAT7;
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short TIM:11;
		} BIT;
	} REMTIM;
} st_remc_t;

typedef struct st_riic {
	union {
		unsigned char BYTE;
		struct {
			unsigned char ICE:1;
			unsigned char IICRST:1;
			unsigned char CLO:1;
			unsigned char SOWP:1;
			unsigned char SCLO:1;
			unsigned char SDAO:1;
			unsigned char SCLI:1;
			unsigned char SDAI:1;
		} BIT;
	} ICCR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char BBSY:1;
			unsigned char MST:1;
			unsigned char TRS:1;
			unsigned char :1;
			unsigned char SP:1;
			unsigned char RS:1;
			unsigned char ST:1;
			unsigned char :1;
		} BIT;
	} ICCR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char MTWP:1;
			unsigned char CKS:3;
			unsigned char BCWP:1;
			unsigned char BC:3;
		} BIT;
	} ICMR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DLCS:1;
			unsigned char SDDL:3;
			unsigned char :1;
			unsigned char TMOH:1;
			unsigned char TMOL:1;
			unsigned char TMOS:1;
		} BIT;
	} ICMR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SMBS:1;
			unsigned char WAIT:1;
			unsigned char RDRFS:1;
			unsigned char ACKWP:1;
			unsigned char ACKBT:1;
			unsigned char ACKBR:1;
			unsigned char NF:2;
		} BIT;
	} ICMR3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char SCLE:1;
			unsigned char NFE:1;
			unsigned char NACKE:1;
			unsigned char SALE:1;
			unsigned char NALE:1;
			unsigned char MALE:1;
			unsigned char TMOE:1;
		} BIT;
	} ICFER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char HOAE:1;
			unsigned char :1;
			unsigned char DIDE:1;
			unsigned char :1;
			unsigned char GCAE:1;
			unsigned char SAR2E:1;
			unsigned char SAR1E:1;
			unsigned char SAR0E:1;
		} BIT;
	} ICSER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TIE:1;
			unsigned char TEIE:1;
			unsigned char RIE:1;
			unsigned char NAKIE:1;
			unsigned char SPIE:1;
			unsigned char STIE:1;
			unsigned char ALIE:1;
			unsigned char TMOIE:1;
		} BIT;
	} ICIER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char HOA:1;
			unsigned char :1;
			unsigned char DID:1;
			unsigned char :1;
			unsigned char GCA:1;
			unsigned char AAS2:1;
			unsigned char AAS1:1;
			unsigned char AAS0:1;
		} BIT;
	} ICSR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TDRE:1;
			unsigned char TEND:1;
			unsigned char RDRF:1;
			unsigned char NACKF:1;
			unsigned char STOP:1;
			unsigned char START:1;
			unsigned char AL:1;
			unsigned char TMOF:1;
		} BIT;
	} ICSR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SVA:7;
			unsigned char SVA0:1;
		} BIT;
	} SARL0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SVA:2;
			unsigned char FS:1;
		} BIT;
	} SARU0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SVA:7;
			unsigned char SVA0:1;
		} BIT;
	} SARL1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SVA:2;
			unsigned char FS:1;
		} BIT;
	} SARU1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SVA:7;
			unsigned char SVA0:1;
		} BIT;
	} SARL2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SVA:2;
			unsigned char FS:1;
		} BIT;
	} SARU2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char BRL:5;
		} BIT;
	} ICBRL;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char BRH:5;
		} BIT;
	} ICBRH;
	unsigned char  ICDRT;
	unsigned char  ICDRR;
} st_riic_t;

typedef struct st_rsci0 {
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned char LL;
			unsigned char LH;
			unsigned char HL;
			unsigned char HH;
		} BYTE;
		struct {
			unsigned long :3;
			unsigned long AFER:1;
			unsigned long APER:1;
			unsigned long :2;
			unsigned long ORER:1;
			unsigned long :14;
			unsigned long MPB:1;
			unsigned long RDAT:9;
		} BIT;
	} RDR;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned char LL;
			unsigned char LH;
			unsigned char HL;
			unsigned char HH;
		} BYTE;
		struct {
			unsigned long :19;
			unsigned long SYNC:1;
			unsigned long :2;
			unsigned long MPBT:1;
			unsigned long TDAT:9;
		} BIT;
	} TDR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long SSE:1;
			unsigned long :2;
			unsigned long TEIE:1;
			unsigned long TIE:1;
			unsigned long :3;
			unsigned long RIE:1;
			unsigned long :5;
			unsigned long IDSEL:1;
			unsigned long DCME:1;
			unsigned long MPIE:1;
			unsigned long :3;
			unsigned long TE:1;
			unsigned long :3;
			unsigned long RE:1;
		} BIT;
	} SCR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long NFEN:1;
			unsigned long :1;
			unsigned long NFCS:3;
			unsigned long :3;
			unsigned long HDSEL:1;
			unsigned long :3;
			unsigned long LOOP:1;
			unsigned long :2;
			unsigned long RINV:1;
			unsigned long TINV:1;
			unsigned long :2;
			unsigned long PM:1;
			unsigned long PE:1;
			unsigned long :2;
			unsigned long SPB2IO:1;
			unsigned long SPB2DT:1;
			unsigned long :2;
			unsigned long CRSEP:1;
			unsigned long CTSE:1;
		} BIT;
	} SCR1;
	union {
		unsigned long LONG;
		struct {
			unsigned long MDDR:8;
			unsigned long :2;
			unsigned long CKS:2;
			unsigned long :3;
			unsigned long BRME:1;
			unsigned long BRR:8;
			unsigned long :1;
			unsigned long ABCSE:1;
			unsigned long ABCS:1;
			unsigned long BGDM:1;
			unsigned long :1;
			unsigned long BCP:3;
		} BIT;
	} SCR2;
	union {
		unsigned long LONG;
		struct {
			unsigned long :2;
			unsigned long BLK:1;
			unsigned long GM:1;
			unsigned long :2;
			unsigned long CKE:2;
			unsigned long :2;
			unsigned long DEEN:1;
			unsigned long :1;
			unsigned long MP:1;
			unsigned long MOD:3;
			unsigned long RXDESEL:1;
			unsigned long STOP:1;
			unsigned long DINV:1;
			unsigned long DDIR:1;
			unsigned long :2;
			unsigned long CHR:2;
			unsigned long SYNDIS:1;
			unsigned long :5;
			unsigned long CPOL:1;
			unsigned long CPHA:1;
		} BIT;
	} SCR3;
	union {
		unsigned long LONG;
		struct {
			unsigned long TTMG:4;
			unsigned long RTMG:4;
			unsigned long :6;
			unsigned long TTADJ:1;
			unsigned long RTADJ:1;
			unsigned long :7;
			unsigned long CMPD:9;
		} BIT;
	} SCR4;
	char           wk0[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char LPS:1;
			unsigned char AOE:1;
			unsigned char :1;
			unsigned char HBSE:1;
		} BIT;
	} HBSCR;
	char           wk1[1];
	union {
		unsigned long LONG;
		struct {
			unsigned long :8;
			unsigned long IICSCLS:2;
			unsigned long IICSDAS:2;
			unsigned long :1;
			unsigned long IICSTPREQ:1;
			unsigned long IICRSTAREQ:1;
			unsigned long IICSTAREQ:1;
			unsigned long :2;
			unsigned long IICACKT:1;
			unsigned long :3;
			unsigned long IICCSC:1;
			unsigned long IICINTM:1;
			unsigned long :3;
			unsigned long IICDL:5;
		} BIT;
	} SIMR;
	char           wk2[12];
	union {
		unsigned long LONG;
		struct {
			unsigned long :11;
			unsigned long DEHLD:5;
			unsigned long :3;
			unsigned long DESU:5;
			unsigned long :7;
			unsigned long DELVL:1;
		} BIT;
	} DECR;
	char           wk3[20];
	union {
		unsigned long LONG;
		struct {
			unsigned long RDRF:1;
			unsigned long TEND:1;
			unsigned long TDRE:1;
			unsigned long AFER:1;
			unsigned long APER:1;
			unsigned long MFF:1;
			unsigned long :1;
			unsigned long ORER:1;
			unsigned long :5;
			unsigned long DFER:1;
			unsigned long DPER:1;
			unsigned long DCMF:1;
			unsigned long RXDMON:1;
			unsigned long :10;
			unsigned long ERS:1;
			unsigned long :4;
		} BIT;
	} SSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long IICSTIF:1;
			unsigned long :2;
			unsigned long IICACKR:1;
		} BIT;
	} SISR;
	char           wk4[24];
	union {
		unsigned long LONG;
		struct {
			unsigned long RDRFC:1;
			unsigned long :1;
			unsigned long TDREC:1;
			unsigned long AFERC:1;
			unsigned long APERC:1;
			unsigned long MFFC:1;
			unsigned long :1;
			unsigned long ORERC:1;
			unsigned long :5;
			unsigned long DFERC:1;
			unsigned long DPERC:1;
			unsigned long DCMFC:1;
			unsigned long :11;
			unsigned long ERSC:1;
			unsigned long :4;
		} BIT;
	} SSCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long IICSTIFC:1;
			unsigned long :3;
		} BIT;
	} SISCR;
} st_rsci0_t;

typedef struct st_rsci9 {
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned char LL;
			unsigned char LH;
			unsigned char HL;
			unsigned char HH;
		} BYTE;
		struct {
			unsigned long :3;
			unsigned long AFER:1;
			unsigned long APER:1;
			unsigned long :2;
			unsigned long ORER:1;
			unsigned long :14;
			unsigned long MPB:1;
			unsigned long RDAT:9;
		} BIT;
	} RDR;
	union {
		unsigned long LONG;
		struct {
			unsigned short L;
			unsigned short H;
		} WORD;
		struct {
			unsigned char LL;
			unsigned char LH;
			unsigned char HL;
			unsigned char HH;
		} BYTE;
		struct {
			unsigned long :19;
			unsigned long SYNC:1;
			unsigned long :2;
			unsigned long MPBT:1;
			unsigned long TDAT:9;
		} BIT;
	} TDR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :7;
			unsigned long SSE:1;
			unsigned long :2;
			unsigned long TEIE:1;
			unsigned long TIE:1;
			unsigned long :3;
			unsigned long RIE:1;
			unsigned long :5;
			unsigned long IDSEL:1;
			unsigned long DCME:1;
			unsigned long MPIE:1;
			unsigned long :3;
			unsigned long TE:1;
			unsigned long :3;
			unsigned long RE:1;
		} BIT;
	} SCR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long NFEN:1;
			unsigned long :1;
			unsigned long NFCS:3;
			unsigned long :3;
			unsigned long HDSEL:1;
			unsigned long :3;
			unsigned long LOOP:1;
			unsigned long :2;
			unsigned long RINV:1;
			unsigned long TINV:1;
			unsigned long :2;
			unsigned long PM:1;
			unsigned long PE:1;
			unsigned long :2;
			unsigned long SPB2IO:1;
			unsigned long SPB2DT:1;
			unsigned long :2;
			unsigned long CRSEP:1;
			unsigned long CTSE:1;
		} BIT;
	} SCR1;
	union {
		unsigned long LONG;
		struct {
			unsigned long MDDR:8;
			unsigned long :2;
			unsigned long CKS:2;
			unsigned long :3;
			unsigned long BRME:1;
			unsigned long BRR:8;
			unsigned long :1;
			unsigned long ABCSE:1;
			unsigned long ABCS:1;
			unsigned long BGDM:1;
			unsigned long :1;
			unsigned long BCP:3;
		} BIT;
	} SCR2;
	union {
		unsigned long LONG;
		struct {
			unsigned long :2;
			unsigned long BLK:1;
			unsigned long GM:1;
			unsigned long :2;
			unsigned long CKE:2;
			unsigned long :2;
			unsigned long DEEN:1;
			unsigned long :1;
			unsigned long MP:1;
			unsigned long MOD:3;
			unsigned long RXDESEL:1;
			unsigned long STOP:1;
			unsigned long DINV:1;
			unsigned long DDIR:1;
			unsigned long :2;
			unsigned long CHR:2;
			unsigned long SYNDIS:1;
			unsigned long :5;
			unsigned long CPOL:1;
			unsigned long CPHA:1;
		} BIT;
	} SCR3;
	union {
		unsigned long LONG;
		struct {
			unsigned long TTMG:4;
			unsigned long RTMG:4;
			unsigned long :6;
			unsigned long TTADJ:1;
			unsigned long RTADJ:1;
			unsigned long :7;
			unsigned long CMPD:9;
		} BIT;
	} SCR4;
	char           wk0[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char LPS:1;
			unsigned char AOE:1;
			unsigned char :1;
			unsigned char HBSE:1;
		} BIT;
	} HBSCR;
	char           wk1[1];
	union {
		unsigned long LONG;
		struct {
			unsigned long :8;
			unsigned long IICSCLS:2;
			unsigned long IICSDAS:2;
			unsigned long :1;
			unsigned long IICSTPREQ:1;
			unsigned long IICRSTAREQ:1;
			unsigned long IICSTAREQ:1;
			unsigned long :2;
			unsigned long IICACKT:1;
			unsigned long :3;
			unsigned long IICCSC:1;
			unsigned long IICINTM:1;
			unsigned long :3;
			unsigned long IICDL:5;
		} BIT;
	} SIMR;
	char           wk2[8];
	union {
		unsigned long LONG;
		struct {
			unsigned long :5;
			unsigned long SBERIE:1;
			unsigned long SYERIE:1;
			unsigned long PFERIE:1;
			unsigned long :2;
			unsigned long RPPAT:2;
			unsigned long RPLEN:4;
			unsigned long :2;
			unsigned long TPPAT:2;
			unsigned long TPLEN:4;
			unsigned long :1;
			unsigned long SBLEN:1;
			unsigned long SYNCE:1;
			unsigned long SBPTN:1;
			unsigned long :1;
			unsigned long SADJE:1;
			unsigned long ENCS:1;
			unsigned long DECS:1;
		} BIT;
	} MMCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :11;
			unsigned long DEHLD:5;
			unsigned long :3;
			unsigned long DESU:5;
			unsigned long :7;
			unsigned long DELVL:1;
		} BIT;
	} DECR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :6;
			unsigned long BCCS:2;
			unsigned long :1;
			unsigned long AEDIE:1;
			unsigned long COFIE:1;
			unsigned long BFDIE:1;
			unsigned long :2;
			unsigned long BCDIE:1;
			unsigned long BFOIE:1;
			unsigned long PIBS:3;
			unsigned long PIBE:1;
			unsigned long CF1DS:2;
			unsigned long CF0RE:1;
			unsigned long BFE:1;
			unsigned long :6;
			unsigned long TCSS:2;
		} BIT;
	} XCR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long CF1CE:8;
			unsigned long SCF1D:8;
			unsigned long PCF1D:8;
			unsigned long :2;
			unsigned long BRME:1;
			unsigned long SDST:1;
			unsigned long :3;
			unsigned long TCST:1;
		} BIT;
	} XCR1;
	union {
		unsigned long LONG;
		struct {
			unsigned long BFLW:16;
			unsigned long CF0CE:8;
			unsigned long CF0D:8;
		} BIT;
	} XCR2;
	char           wk3[8];
	union {
		unsigned long LONG;
		struct {
			unsigned long RDRF:1;
			unsigned long TEND:1;
			unsigned long TDRE:1;
			unsigned long AFER:1;
			unsigned long APER:1;
			unsigned long MFF:1;
			unsigned long :1;
			unsigned long ORER:1;
			unsigned long :5;
			unsigned long DFER:1;
			unsigned long DPER:1;
			unsigned long DCMF:1;
			unsigned long RXDMON:1;
			unsigned long :10;
			unsigned long ERS:1;
			unsigned long :4;
		} BIT;
	} SSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long IICSTIF:1;
			unsigned long :2;
			unsigned long IICACKR:1;
		} BIT;
	} SISR;
	char           wk4[8];
	union {
		unsigned long LONG;
		struct {
			unsigned long :25;
			unsigned long RSYNC:1;
			unsigned long :1;
			unsigned long MCER:1;
			unsigned long :1;
			unsigned long SBER:1;
			unsigned long SYER:1;
			unsigned long PFER:1;
		} BIT;
	} MMSR;
	union {
		unsigned long LONG;
		struct {
			unsigned long CF1RD:8;
			unsigned long CF0RD:8;
			unsigned long AEDF:1;
			unsigned long COF:1;
			unsigned long PIBDF:1;
			unsigned long CF1MF:1;
			unsigned long CF0MF:1;
			unsigned long BFDF:1;
			unsigned long BCDF:1;
			unsigned long BFOF:1;
			unsigned long :6;
			unsigned long RXDSF:1;
			unsigned long SFSF:1;
		} BIT;
	} XSR0;
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long CCV:16;
		} BIT;
	} XSR1;
	char           wk5[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long RDRFC:1;
			unsigned long :1;
			unsigned long TDREC:1;
			unsigned long AFERC:1;
			unsigned long APERC:1;
			unsigned long MFFC:1;
			unsigned long :1;
			unsigned long ORERC:1;
			unsigned long :5;
			unsigned long DFERC:1;
			unsigned long DPERC:1;
			unsigned long DCMFC:1;
			unsigned long :11;
			unsigned long ERSC:1;
			unsigned long :4;
		} BIT;
	} SSCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :28;
			unsigned long IICSTIFC:1;
			unsigned long :3;
		} BIT;
	} SISCR;
	char           wk6[4];
	union {
		unsigned long LONG;
		struct {
			unsigned long :27;
			unsigned long MCERC:1;
			unsigned long :1;
			unsigned long SBERC:1;
			unsigned long SYERC:1;
			unsigned long PFERC:1;
		} BIT;
	} MMSCR;
	union {
		unsigned long LONG;
		struct {
			unsigned long :16;
			unsigned long AEDCL:1;
			unsigned long COFC:1;
			unsigned long PIBDCL:1;
			unsigned long CF1MCL:1;
			unsigned long CF0MCL:1;
			unsigned long BFDCL:1;
			unsigned long BCDCL:1;
			unsigned long BFOC:1;
			unsigned long :8;
		} BIT;
	} XSCR;
} st_rsci9_t;

typedef struct st_rspi {
	union {
		unsigned char BYTE;
		struct {
			unsigned char SPRIE:1;
			unsigned char SPE:1;
			unsigned char SPTIE:1;
			unsigned char SPEIE:1;
			unsigned char MSTR:1;
			unsigned char MODFEN:1;
			unsigned char TXMD:1;
			unsigned char SPMS:1;
		} BIT;
	} SPCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char SSL3P:1;
			unsigned char SSL2P:1;
			unsigned char SSL1P:1;
			unsigned char SSL0P:1;
		} BIT;
	} SSLP;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char MOIFE:1;
			unsigned char MOIFV:1;
			unsigned char :2;
			unsigned char SPLP2:1;
			unsigned char SPLP:1;
		} BIT;
	} SPPCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char SPRF:1;
			unsigned char :1;
			unsigned char SPTEF:1;
			unsigned char UDRF:1;
			unsigned char PERF:1;
			unsigned char MODF:1;
			unsigned char IDLNF:1;
			unsigned char OVRF:1;
		} BIT;
	} SPSR;
	union {
		unsigned long LONG;
		struct {
			unsigned short H;
		} WORD;
		struct {
			unsigned char HH;
		} BYTE;
	} SPDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SPSLN:3;
		} BIT;
	} SPSCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char SPECM:3;
			unsigned char :1;
			unsigned char SPCP:3;
		} BIT;
	} SPSSR;
	unsigned char  SPBR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char SPBYT:1;
			unsigned char SPLW:1;
			unsigned char SPRDTD:1;
			unsigned char :2;
			unsigned char SPFC:2;
		} BIT;
	} SPDCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SCKDL:3;
		} BIT;
	} SPCKD;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SLNDL:3;
		} BIT;
	} SSLND;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SPNDL:3;
		} BIT;
	} SPND;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char SCKASE:1;
			unsigned char PTE:1;
			unsigned char SPIIE:1;
			unsigned char SPOE:1;
			unsigned char SPPE:1;
		} BIT;
	} SPCR2;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD0;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD1;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD2;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD3;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD4;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD5;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD6;
	union {
		unsigned short WORD;
		struct {
			unsigned short SCKDEN:1;
			unsigned short SLNDEN:1;
			unsigned short SPNDEN:1;
			unsigned short LSBF:1;
			unsigned short SPB:4;
			unsigned short SSLKP:1;
			unsigned short SSLA:3;
			unsigned short BRDV:2;
			unsigned short CPOL:1;
			unsigned short CPHA:1;
		} BIT;
	} SPCMD7;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char BYSW:1;
		} BIT;
	} SPDCR2;
} st_rspi_t;

typedef struct st_rtc {
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char F1HZ:1;
			unsigned char F2HZ:1;
			unsigned char F4HZ:1;
			unsigned char F8HZ:1;
			unsigned char F16HZ:1;
			unsigned char F32HZ:1;
			unsigned char F64HZ:1;
		} BIT;
	} R64CNT;
	char           wk0[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECCNT;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNT:8;
			} BIT;
		} BCNT0;
	};
	char           wk1[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINCNT;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNT:8;
			} BIT;
		} BCNT1;
	};
	char           wk2[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRCNT;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNT:8;
			} BIT;
		} BCNT2;
	};
	char           wk3[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :5;
				unsigned char DAYW:3;
			} BIT;
		} RWKCNT;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNT:8;
			} BIT;
		} BCNT3;
	};
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char DATE10:2;
			unsigned char DATE1:4;
		} BIT;
	} RDAYCNT;
	char           wk5[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MON10:1;
			unsigned char MON1:4;
		} BIT;
	} RMONCNT;
	char           wk6[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short YR10:4;
			unsigned short YR1:4;
		} BIT;
	} RYRCNT;
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECAR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTAR:8;
			} BIT;
		} BCNT0AR;
	};
	char           wk7[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINAR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTAR:8;
			} BIT;
		} BCNT1AR;
	};
	char           wk8[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRAR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTAR:8;
			} BIT;
		} BCNT2AR;
	};
	char           wk9[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char :4;
				unsigned char DAYW:3;
			} BIT;
		} RWKAR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTAR:8;
			} BIT;
		} BCNT3AR;
	};
	char           wk10[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char :1;
				unsigned char DATE10:2;
				unsigned char DATE1:4;
			} BIT;
		} RDAYAR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:8;
			} BIT;
		} BCNT0AER;
	};
	char           wk11[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char :2;
				unsigned char MON10:1;
				unsigned char MON1:4;
			} BIT;
		} RMONAR;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:8;
			} BIT;
		} BCNT1AER;
	};
	char           wk12[1];
	union {
		union {
			unsigned short WORD;
			struct {
				unsigned short :8;
				unsigned short YR10:4;
				unsigned short YR1:4;
			} BIT;
		} RYRAR;
		union {
			unsigned short WORD;
			struct {
				unsigned short :8;
				unsigned short ENB:8;
			} BIT;
		} BCNT2AER;
	};
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:1;
				unsigned char :7;
			} BIT;
		} RYRAREN;
		union {
			unsigned char BYTE;
			struct {
				unsigned char ENB:8;
			} BIT;
		} BCNT3AER;
	};
	char           wk13[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char PES:4;
			unsigned char RTCOS:1;
			unsigned char PIE:1;
			unsigned char CIE:1;
			unsigned char AIE:1;
		} BIT;
	} RCR1;
	char           wk14[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CNTMD:1;
			unsigned char HR24:1;
			unsigned char AADJP:1;
			unsigned char AADJE:1;
			unsigned char RTCOE:1;
			unsigned char ADJ30:1;
			unsigned char RESET:1;
			unsigned char START:1;
		} BIT;
	} RCR2;
	char           wk15[9];
	union {
		unsigned char BYTE;
		struct {
			unsigned char PMADJ:2;
			unsigned char ADJ:6;
		} BIT;
	} RADJ;
	char           wk16[17];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCEN:1;
			unsigned char :1;
			unsigned char TCNF:2;
			unsigned char :1;
			unsigned char TCST:1;
			unsigned char TCCT:2;
		} BIT;
	} RTCCR0;
	char           wk17[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCEN:1;
			unsigned char :1;
			unsigned char TCNF:2;
			unsigned char :1;
			unsigned char TCST:1;
			unsigned char TCCT:2;
		} BIT;
	} RTCCR1;
	char           wk18[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TCEN:1;
			unsigned char :1;
			unsigned char TCNF:2;
			unsigned char :1;
			unsigned char TCST:1;
			unsigned char TCCT:2;
		} BIT;
	} RTCCR2;
	char           wk19[13];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECCP0;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP0:8;
			} BIT;
		} BCNT0CP0;
	};
	char           wk20[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINCP0;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP0:8;
			} BIT;
		} BCNT1CP0;
	};
	char           wk21[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRCP0;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP0:8;
			} BIT;
		} BCNT2CP0;
	};
	char           wk22[3];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :2;
				unsigned char DATE10:2;
				unsigned char DATE1:4;
			} BIT;
		} RDAYCP0;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP0:8;
			} BIT;
		} BCNT3CP0;
	};
	char           wk23[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MON10:1;
			unsigned char MON1:4;
		} BIT;
	} RMONCP0;
	char           wk24[5];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECCP1;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP1:8;
			} BIT;
		} BCNT0CP1;
	};
	char           wk25[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINCP1;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP1:8;
			} BIT;
		} BCNT1CP1;
	};
	char           wk26[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRCP1;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP1:8;
			} BIT;
		} BCNT2CP1;
	};
	char           wk27[3];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :2;
				unsigned char DATE10:2;
				unsigned char DATE1:4;
			} BIT;
		} RDAYCP1;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP1:8;
			} BIT;
		} BCNT3CP1;
	};
	char           wk28[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MON10:1;
			unsigned char MON1:4;
		} BIT;
	} RMONCP1;
	char           wk29[5];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char SEC10:3;
				unsigned char SEC1:4;
			} BIT;
		} RSECCP2;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP2:8;
			} BIT;
		} BCNT0CP2;
	};
	char           wk30[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char MIN10:3;
				unsigned char MIN1:4;
			} BIT;
		} RMINCP2;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP2:8;
			} BIT;
		} BCNT1CP2;
	};
	char           wk31[1];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :1;
				unsigned char PM:1;
				unsigned char HR10:2;
				unsigned char HR1:4;
			} BIT;
		} RHRCP2;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP2:8;
			} BIT;
		} BCNT2CP2;
	};
	char           wk32[3];
	union {
		union {
			unsigned char BYTE;
			struct {
				unsigned char :2;
				unsigned char DATE10:2;
				unsigned char DATE1:4;
			} BIT;
		} RDAYCP2;
		union {
			unsigned char BYTE;
			struct {
				unsigned char BCNTCP2:8;
			} BIT;
		} BCNT3CP2;
	};
	char           wk33[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MON10:1;
			unsigned char MON1:4;
		} BIT;
	} RMONCP2;
} st_rtc_t;

typedef struct st_rtcb {
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNT:8;
		} BIT;
	} BCNT0;
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNT:8;
		} BIT;
	} BCNT1;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNT:8;
		} BIT;
	} BCNT2;
	char           wk2[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNT:8;
		} BIT;
	} BCNT3;
	char           wk3[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTAR:8;
		} BIT;
	} BCNT0AR;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTAR:8;
		} BIT;
	} BCNT1AR;
	char           wk5[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTAR:8;
		} BIT;
	} BCNT2AR;
	char           wk6[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTAR:8;
		} BIT;
	} BCNT3AR;
	char           wk7[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ENB:8;
		} BIT;
	} BCNT0AER;
	char           wk8[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ENB:8;
		} BIT;
	} BCNT1AER;
	char           wk9[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short ENB:8;
		} BIT;
	} BCNT2AER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char ENB:8;
		} BIT;
	} BCNT3AER;
	char           wk10[51];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP0:8;
		} BIT;
	} BCNT0CP0;
	char           wk11[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP0:8;
		} BIT;
	} BCNT1CP0;
	char           wk12[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP0:8;
		} BIT;
	} BCNT2CP0;
	char           wk13[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP0:8;
		} BIT;
	} BCNT3CP0;
	char           wk14[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP1:8;
		} BIT;
	} BCNT0CP1;
	char           wk15[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP1:8;
		} BIT;
	} BCNT1CP1;
	char           wk16[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP1:8;
		} BIT;
	} BCNT2CP1;
	char           wk17[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP1:8;
		} BIT;
	} BCNT3CP1;
	char           wk18[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP2:8;
		} BIT;
	} BCNT0CP2;
	char           wk19[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP2:8;
		} BIT;
	} BCNT1CP2;
	char           wk20[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP2:8;
		} BIT;
	} BCNT2CP2;
	char           wk21[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCNTCP2:8;
		} BIT;
	} BCNT3CP2;
} st_rtcb_t;

typedef struct st_s12ad {
	union {
		unsigned short WORD;
		struct {
			unsigned short ADST:1;
			unsigned short ADCS:2;
			unsigned short ADIE:1;
			unsigned short :1;
			unsigned short ADHSC:1;
			unsigned short TRGE:1;
			unsigned short EXTRG:1;
			unsigned short DBLE:1;
			unsigned short GBADIE:1;
			unsigned short :1;
			unsigned short DBLANS:5;
		} BIT;
	} ADCSR;
	char           wk0[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :7;
			unsigned short ANSA008:1;
			unsigned short ANSA007:1;
			unsigned short ANSA006:1;
			unsigned short ANSA005:1;
			unsigned short ANSA004:1;
			unsigned short ANSA003:1;
			unsigned short ANSA002:1;
			unsigned short ANSA001:1;
			unsigned short ANSA000:1;
		} BIT;
	} ADANSA0;
	union {
		unsigned short WORD;
		struct {
			unsigned short ANSA115:1;
			unsigned short ANSA114:1;
			unsigned short ANSA113:1;
			unsigned short ANSA112:1;
			unsigned short ANSA111:1;
			unsigned short ANSA110:1;
			unsigned short ANSA109:1;
			unsigned short ANSA108:1;
			unsigned short ANSA107:1;
			unsigned short ANSA106:1;
			unsigned short ANSA105:1;
			unsigned short ANSA104:1;
			unsigned short ANSA103:1;
			unsigned short ANSA102:1;
			unsigned short ANSA101:1;
			unsigned short ANSA100:1;
		} BIT;
	} ADANSA1;
	union {
		unsigned short WORD;
		struct {
			unsigned short :7;
			unsigned short ADS008:1;
			unsigned short ADS007:1;
			unsigned short ADS006:1;
			unsigned short ADS005:1;
			unsigned short ADS004:1;
			unsigned short ADS003:1;
			unsigned short ADS002:1;
			unsigned short ADS001:1;
			unsigned short ADS000:1;
		} BIT;
	} ADADS0;
	union {
		unsigned short WORD;
		struct {
			unsigned short ADS115:1;
			unsigned short ADS114:1;
			unsigned short ADS113:1;
			unsigned short ADS112:1;
			unsigned short ADS111:1;
			unsigned short ADS110:1;
			unsigned short ADS109:1;
			unsigned short ADS108:1;
			unsigned short ADS107:1;
			unsigned short ADS106:1;
			unsigned short ADS105:1;
			unsigned short ADS104:1;
			unsigned short ADS103:1;
			unsigned short ADS102:1;
			unsigned short ADS101:1;
			unsigned short ADS100:1;
		} BIT;
	} ADADS1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char AVEE:1;
			unsigned char :4;
			unsigned char ADC:3;
		} BIT;
	} ADADC;
	char           wk1[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short ADRFMT:1;
			unsigned short :3;
			unsigned short DIAGM:1;
			unsigned short DIAGLD:1;
			unsigned short DIAGVAL:2;
			unsigned short :2;
			unsigned short ACE:1;
			unsigned short :5;
		} BIT;
	} ADCER;
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short TRSA:6;
			unsigned short :2;
			unsigned short TRSB:6;
		} BIT;
	} ADSTRGR;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short OCSA:1;
			unsigned short TSSA:1;
			unsigned short :6;
			unsigned short OCSAD:1;
			unsigned short TSSAD:1;
		} BIT;
	} ADEXICR;
	union {
		unsigned short WORD;
		struct {
			unsigned short :7;
			unsigned short ANSB008:1;
			unsigned short ANSB007:1;
			unsigned short ANSB006:1;
			unsigned short ANSB005:1;
			unsigned short ANSB004:1;
			unsigned short ANSB003:1;
			unsigned short ANSB002:1;
			unsigned short ANSB001:1;
			unsigned short ANSB000:1;
		} BIT;
	} ADANSB0;
	union {
		unsigned short WORD;
		struct {
			unsigned short ANSB115:1;
			unsigned short ANSB114:1;
			unsigned short ANSB113:1;
			unsigned short ANSB112:1;
			unsigned short ANSB111:1;
			unsigned short ANSB110:1;
			unsigned short ANSB109:1;
			unsigned short ANSB108:1;
			unsigned short ANSB107:1;
			unsigned short ANSB106:1;
			unsigned short ANSB105:1;
			unsigned short ANSB104:1;
			unsigned short ANSB103:1;
			unsigned short ANSB102:1;
			unsigned short ANSB101:1;
			unsigned short ANSB100:1;
		} BIT;
	} ADANSB1;
	unsigned short ADDBLDR;
	unsigned short ADTSDR;
	unsigned short ADOCDR;
	union {
		unsigned short WORD;
		union {
			struct {
				unsigned short DIAGST:2;
				unsigned short :2;
				unsigned short AD:12;
			} RIGHT;
			struct {
				unsigned short AD:12;
				unsigned short :2;
				unsigned short DIAGST:2;
			} LEFT;
		} BIT;
	} ADRD;
	unsigned short ADDR0;
	unsigned short ADDR1;
	unsigned short ADDR2;
	unsigned short ADDR3;
	unsigned short ADDR4;
	unsigned short ADDR5;
	unsigned short ADDR6;
	unsigned short ADDR7;
	unsigned short ADDR8;
	char           wk2[14];
	unsigned short ADDR16;
	unsigned short ADDR17;
	unsigned short ADDR18;
	unsigned short ADDR19;
	unsigned short ADDR20;
	unsigned short ADDR21;
	unsigned short ADDR22;
	unsigned short ADDR23;
	unsigned short ADDR24;
	unsigned short ADDR25;
	unsigned short ADDR26;
	unsigned short ADDR27;
	unsigned short ADDR28;
	unsigned short ADDR29;
	unsigned short ADDR30;
	unsigned short ADDR31;
	char           wk3[26];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char ADNDIS:5;
		} BIT;
	} ADDISCR;
	char           wk4[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char ELCC:2;
		} BIT;
	} ADELCCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char CCS:1;
			unsigned char :1;
		} BIT;
	} ADCCR;
	char           wk5[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short GBRP:1;
			unsigned short :13;
			unsigned short GBRSCN:1;
			unsigned short PGS:1;
		} BIT;
	} ADGSPCR;
	char           wk6[8];
	union {
		unsigned char BYTE;
		struct {
			unsigned char ADSLP:1;
			unsigned char :2;
			unsigned char LVSEL:1;
			unsigned char :2;
			unsigned char HVSEL:2;
		} BIT;
	} ADHVREFCNT;
	char           wk7[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char MONCMPB:1;
			unsigned char MONCMPA:1;
			unsigned char :3;
			unsigned char MONCOMB:1;
		} BIT;
	} ADWINMON;
	char           wk8[3];
	union {
		unsigned short WORD;
		struct {
			unsigned short :1;
			unsigned short WCMPE:1;
			unsigned short :2;
			unsigned short CMPAE:1;
			unsigned short :1;
			unsigned short CMPBE:1;
			unsigned short :7;
			unsigned short CMPAB:2;
		} BIT;
	} ADCMPCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char CMPOCA:1;
			unsigned char CMPTSA:1;
		} BIT;
	} ADCMPANSER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char CMPLOCA:1;
			unsigned char CMPLTSA:1;
		} BIT;
	} ADCMPLER;
	union {
		unsigned short WORD;
		struct {
			unsigned short :7;
			unsigned short CMPCHA008:1;
			unsigned short CMPCHA007:1;
			unsigned short CMPCHA006:1;
			unsigned short CMPCHA005:1;
			unsigned short CMPCHA004:1;
			unsigned short CMPCHA003:1;
			unsigned short CMPCHA002:1;
			unsigned short CMPCHA001:1;
			unsigned short CMPCHA000:1;
		} BIT;
	} ADCMPANSR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CMPCHA115:1;
			unsigned short CMPCHA114:1;
			unsigned short CMPCHA113:1;
			unsigned short CMPCHA112:1;
			unsigned short CMPCHA111:1;
			unsigned short CMPCHA110:1;
			unsigned short CMPCHA109:1;
			unsigned short CMPCHA108:1;
			unsigned short CMPCHA107:1;
			unsigned short CMPCHA106:1;
			unsigned short CMPCHA105:1;
			unsigned short CMPCHA104:1;
			unsigned short CMPCHA103:1;
			unsigned short CMPCHA102:1;
			unsigned short CMPCHA101:1;
			unsigned short CMPCHA100:1;
		} BIT;
	} ADCMPANSR1;
	union {
		unsigned short WORD;
		struct {
			unsigned short :7;
			unsigned short CMPLCHA008:1;
			unsigned short CMPLCHA007:1;
			unsigned short CMPLCHA006:1;
			unsigned short CMPLCHA005:1;
			unsigned short CMPLCHA004:1;
			unsigned short CMPLCHA003:1;
			unsigned short CMPLCHA002:1;
			unsigned short CMPLCHA001:1;
			unsigned short CMPLCHA000:1;
		} BIT;
	} ADCMPLR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CMPLCHA115:1;
			unsigned short CMPLCHA114:1;
			unsigned short CMPLCHA113:1;
			unsigned short CMPLCHA112:1;
			unsigned short CMPLCHA111:1;
			unsigned short CMPLCHA110:1;
			unsigned short CMPLCHA109:1;
			unsigned short CMPLCHA108:1;
			unsigned short CMPLCHA107:1;
			unsigned short CMPLCHA106:1;
			unsigned short CMPLCHA105:1;
			unsigned short CMPLCHA104:1;
			unsigned short CMPLCHA103:1;
			unsigned short CMPLCHA102:1;
			unsigned short CMPLCHA101:1;
			unsigned short CMPLCHA100:1;
		} BIT;
	} ADCMPLR1;
	unsigned short ADCMPDR0;
	unsigned short ADCMPDR1;
	union {
		unsigned short WORD;
		struct {
			unsigned short :7;
			unsigned short CMPSTCHA008:1;
			unsigned short CMPSTCHA007:1;
			unsigned short CMPSTCHA006:1;
			unsigned short CMPSTCHA005:1;
			unsigned short CMPSTCHA004:1;
			unsigned short CMPSTCHA003:1;
			unsigned short CMPSTCHA002:1;
			unsigned short CMPSTCHA001:1;
			unsigned short CMPSTCHA000:1;
		} BIT;
	} ADCMPSR0;
	union {
		unsigned short WORD;
		struct {
			unsigned short CMPSTCHA115:1;
			unsigned short CMPSTCHA114:1;
			unsigned short CMPSTCHA113:1;
			unsigned short CMPSTCHA112:1;
			unsigned short CMPSTCHA111:1;
			unsigned short CMPSTCHA110:1;
			unsigned short CMPSTCHA109:1;
			unsigned short CMPSTCHA108:1;
			unsigned short CMPSTCHA107:1;
			unsigned short CMPSTCHA106:1;
			unsigned short CMPSTCHA105:1;
			unsigned short CMPSTCHA104:1;
			unsigned short CMPSTCHA103:1;
			unsigned short CMPSTCHA102:1;
			unsigned short CMPSTCHA101:1;
			unsigned short CMPSTCHA100:1;
		} BIT;
	} ADCMPSR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char CMPSTOCA:1;
			unsigned char CMPSTTSA:1;
		} BIT;
	} ADCMPSER;
	char           wk9[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CMPLB:1;
			unsigned char :1;
			unsigned char CMPCHB:6;
		} BIT;
	} ADCMPBNSR;
	char           wk10[1];
	unsigned short ADWINLLB;
	unsigned short ADWINULB;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CMPSTB:1;
		} BIT;
	} ADCMPBSR;
	char           wk11[3];
	unsigned short ADBUF0;
	unsigned short ADBUF1;
	unsigned short ADBUF2;
	unsigned short ADBUF3;
	unsigned short ADBUF4;
	unsigned short ADBUF5;
	unsigned short ADBUF6;
	unsigned short ADBUF7;
	unsigned short ADBUF8;
	unsigned short ADBUF9;
	unsigned short ADBUF10;
	unsigned short ADBUF11;
	unsigned short ADBUF12;
	unsigned short ADBUF13;
	unsigned short ADBUF14;
	unsigned short ADBUF15;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char BUFEN:1;
		} BIT;
	} ADBUFEN;
	char           wk12[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char PTROVF:1;
			unsigned char BUFPTR:4;
		} BIT;
	} ADBUFPTR;
	char           wk13[10];
	unsigned char  ADSSTRL;
	unsigned char  ADSSTRT;
	unsigned char  ADSSTRO;
	unsigned char  ADSSTR0;
	unsigned char  ADSSTR1;
	unsigned char  ADSSTR2;
	unsigned char  ADSSTR3;
	unsigned char  ADSSTR4;
	unsigned char  ADSSTR5;
	unsigned char  ADSSTR6;
	unsigned char  ADSSTR7;
	unsigned char  ADSSTR8;
} st_s12ad_t;

typedef struct st_sci1 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CM:1;
			unsigned char CHR:1;
			unsigned char PE:1;
			unsigned char PM:1;
			unsigned char STOP:1;
			unsigned char MP:1;
			unsigned char CKS:2;
		} BIT;
	} SMR;
	unsigned char  BRR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TIE:1;
			unsigned char RIE:1;
			unsigned char TE:1;
			unsigned char RE:1;
			unsigned char MPIE:1;
			unsigned char TEIE:1;
			unsigned char CKE:2;
		} BIT;
	} SCR;
	unsigned char  TDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TDRE:1;
			unsigned char RDRF:1;
			unsigned char ORER:1;
			unsigned char FER:1;
			unsigned char PER:1;
			unsigned char TEND:1;
			unsigned char MPB:1;
			unsigned char MPBT:1;
		} BIT;
	} SSR;
	unsigned char  RDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCP2:1;
			unsigned char :2;
			unsigned char CHR1:1;
			unsigned char SDIR:1;
			unsigned char SINV:1;
			unsigned char :1;
			unsigned char SMIF:1;
		} BIT;
	} SCMR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RXDESEL:1;
			unsigned char BGDM:1;
			unsigned char NFEN:1;
			unsigned char ABCS:1;
			unsigned char ABCSE:1;
			unsigned char BRME:1;
			unsigned char ITE:1;
			unsigned char ACS0:1;
		} BIT;
	} SEMR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char NFCS:3;
		} BIT;
	} SNFR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IICDL:5;
			unsigned char :2;
			unsigned char IICM:1;
		} BIT;
	} SIMR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char IICACKT:1;
			unsigned char :3;
			unsigned char IICCSC:1;
			unsigned char IICINTM:1;
		} BIT;
	} SIMR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IICSCLS:2;
			unsigned char IICSDAS:2;
			unsigned char IICSTIF:1;
			unsigned char IICSTPREQ:1;
			unsigned char IICRSTAREQ:1;
			unsigned char IICSTAREQ:1;
		} BIT;
	} SIMR3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char IICACKR:1;
		} BIT;
	} SISR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CKPH:1;
			unsigned char CKPOL:1;
			unsigned char :1;
			unsigned char MFF:1;
			unsigned char :1;
			unsigned char MSS:1;
			unsigned char CTSE:1;
			unsigned char SSE:1;
		} BIT;
	} SPMR;
	union {
		unsigned short WORD;
		struct {
			unsigned char TDRH;
			unsigned char TDRL;
		} BYTE;
	} TDRHL;
	union {
		unsigned short WORD;
		struct {
			unsigned char RDRH;
			unsigned char RDRL;
		} BYTE;
	} RDRHL;
	unsigned char  MDDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char DCME:1;
			unsigned char IDSEL:1;
			unsigned char :1;
			unsigned char DFER:1;
			unsigned char DPER:1;
			unsigned char :2;
			unsigned char DCMF:1;
		} BIT;
	} DCCR;
	char           wk0[6];
	union {
		unsigned short WORD;
		struct {
			unsigned char H;
			unsigned char L;
		} BYTE;
		struct {
			unsigned short :7;
			unsigned short CMPD:9;
		} BIT;
	} CDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTADJ:1;
			unsigned char RTADJ:1;
			unsigned char TINV:1;
			unsigned char RINV:1;
			unsigned char :1;
			unsigned char SPB2IO:1;
			unsigned char SPB2DT:1;
			unsigned char RXDMON:1;
		} BIT;
	} SPTR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TTMG:4;
			unsigned char RTMG:4;
		} BIT;
	} TMGR;
} st_sci1_t;

typedef struct st_sci12 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CM:1;
			unsigned char CHR:1;
			unsigned char PE:1;
			unsigned char PM:1;
			unsigned char STOP:1;
			unsigned char MP:1;
			unsigned char CKS:2;
		} BIT;
	} SMR;
	unsigned char  BRR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TIE:1;
			unsigned char RIE:1;
			unsigned char TE:1;
			unsigned char RE:1;
			unsigned char MPIE:1;
			unsigned char TEIE:1;
			unsigned char CKE:2;
		} BIT;
	} SCR;
	unsigned char  TDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char TDRE:1;
			unsigned char RDRF:1;
			unsigned char ORER:1;
			unsigned char FER:1;
			unsigned char PER:1;
			unsigned char TEND:1;
			unsigned char MPB:1;
			unsigned char MPBT:1;
		} BIT;
	} SSR;
	unsigned char  RDR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCP2:1;
			unsigned char :2;
			unsigned char CHR1:1;
			unsigned char SDIR:1;
			unsigned char SINV:1;
			unsigned char :1;
			unsigned char SMIF:1;
		} BIT;
	} SCMR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RXDESEL:1;
			unsigned char BGDM:1;
			unsigned char NFEN:1;
			unsigned char ABCS:1;
			unsigned char :1;
			unsigned char BRME:1;
			unsigned char :1;
			unsigned char ACS0:1;
		} BIT;
	} SEMR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char NFCS:3;
		} BIT;
	} SNFR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IICDL:5;
			unsigned char :2;
			unsigned char IICM:1;
		} BIT;
	} SIMR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char IICACKT:1;
			unsigned char :3;
			unsigned char IICCSC:1;
			unsigned char IICINTM:1;
		} BIT;
	} SIMR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char IICSCLS:2;
			unsigned char IICSDAS:2;
			unsigned char IICSTIF:1;
			unsigned char IICSTPREQ:1;
			unsigned char IICRSTAREQ:1;
			unsigned char IICSTAREQ:1;
		} BIT;
	} SIMR3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char IICACKR:1;
		} BIT;
	} SISR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CKPH:1;
			unsigned char CKPOL:1;
			unsigned char :1;
			unsigned char MFF:1;
			unsigned char :1;
			unsigned char MSS:1;
			unsigned char CTSE:1;
			unsigned char SSE:1;
		} BIT;
	} SPMR;
	union {
		unsigned short WORD;
		struct {
			unsigned char TDRH;
			unsigned char TDRL;
		} BYTE;
	} TDRHL;
	union {
		unsigned short WORD;
		struct {
			unsigned char RDRH;
			unsigned char RDRL;
		} BYTE;
	} RDRHL;
	unsigned char  MDDR;
	char           wk0[13];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char ESME:1;
		} BIT;
	} ESMER;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char BRME:1;
			unsigned char RXDSF:1;
			unsigned char SFSF:1;
			unsigned char :1;
		} BIT;
	} CR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char PIBS:3;
			unsigned char PIBE:1;
			unsigned char CF1DS:2;
			unsigned char CF0RE:1;
			unsigned char BFE:1;
		} BIT;
	} CR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RTS:2;
			unsigned char BCCS:2;
			unsigned char :1;
			unsigned char DFCS:3;
		} BIT;
	} CR2;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char SDST:1;
		} BIT;
	} CR3;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char SHARPS:1;
			unsigned char :2;
			unsigned char RXDXPS:1;
			unsigned char TXDXPS:1;
		} BIT;
	} PCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char AEDIE:1;
			unsigned char BCDIE:1;
			unsigned char PIBDIE:1;
			unsigned char CF1MIE:1;
			unsigned char CF0MIE:1;
			unsigned char BFDIE:1;
		} BIT;
	} ICR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char AEDF:1;
			unsigned char BCDF:1;
			unsigned char PIBDF:1;
			unsigned char CF1MF:1;
			unsigned char CF0MF:1;
			unsigned char BFDF:1;
		} BIT;
	} STR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char AEDCL:1;
			unsigned char BCDCL:1;
			unsigned char PIBDCL:1;
			unsigned char CF1MCL:1;
			unsigned char CF0MCL:1;
			unsigned char BFDCL:1;
		} BIT;
	} STCR;
	unsigned char  CF0DR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CF0CE7:1;
			unsigned char CF0CE6:1;
			unsigned char CF0CE5:1;
			unsigned char CF0CE4:1;
			unsigned char CF0CE3:1;
			unsigned char CF0CE2:1;
			unsigned char CF0CE1:1;
			unsigned char CF0CE0:1;
		} BIT;
	} CF0CR;
	unsigned char  CF0RR;
	unsigned char  PCF1DR;
	unsigned char  SCF1DR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char CF1CE7:1;
			unsigned char CF1CE6:1;
			unsigned char CF1CE5:1;
			unsigned char CF1CE4:1;
			unsigned char CF1CE3:1;
			unsigned char CF1CE2:1;
			unsigned char CF1CE1:1;
			unsigned char CF1CE0:1;
		} BIT;
	} CF1CR;
	unsigned char  CF1RR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char TCST:1;
		} BIT;
	} TCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char TCSS:3;
			unsigned char TWRC:1;
			unsigned char :1;
			unsigned char TOMS:2;
		} BIT;
	} TMR;
	unsigned char  TPRE;
	unsigned char  TCNT;
} st_sci12_t;

typedef struct st_smci {
	union {
		unsigned char BYTE;
		struct {
			unsigned char GM:1;
			unsigned char BLK:1;
			unsigned char PE:1;
			unsigned char PM:1;
			unsigned char BCP:2;
			unsigned char CKS:2;
		} BIT;
	} SMR;
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TIE:1;
			unsigned char RIE:1;
			unsigned char TE:1;
			unsigned char RE:1;
			unsigned char MPIE:1;
			unsigned char TEIE:1;
			unsigned char CKE:2;
		} BIT;
	} SCR;
	char           wk1[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TDRE:1;
			unsigned char RDRF:1;
			unsigned char ORER:1;
			unsigned char ERS:1;
			unsigned char PER:1;
			unsigned char TEND:1;
			unsigned char MPB:1;
			unsigned char MPBT:1;
		} BIT;
	} SSR;
	char           wk2[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char BCP2:1;
			unsigned char :2;
			unsigned char CHR1:1;
			unsigned char SDIR:1;
			unsigned char SINV:1;
			unsigned char :1;
			unsigned char SMIF:1;
		} BIT;
	} SCMR;
} st_smci_t;

typedef struct st_system {
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short MD:1;
		} BIT;
	} MDMONR;
	char           wk0[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short :15;
			unsigned short RAME:1;
		} BIT;
	} SYSCR1;
	char           wk1[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short SSBY:1;
			unsigned short :15;
		} BIT;
	} SBYCR;
	char           wk2[2];
	union {
		unsigned long LONG;
		struct {
			unsigned long :3;
			unsigned long MSTPA28:1;
			unsigned long :8;
			unsigned long MSTPA19:1;
			unsigned long :1;
			unsigned long MSTPA17:1;
			unsigned long :1;
			unsigned long MSTPA15:1;
			unsigned long MSTPA14:1;
			unsigned long :6;
			unsigned long MSTPA7:1;
			unsigned long :1;
			unsigned long MSTPA5:1;
			unsigned long MSTPA4:1;
			unsigned long :4;
		} BIT;
	} MSTPCRA;
	union {
		unsigned long LONG;
		struct {
			unsigned long MSTPB31:1;
			unsigned long MSTPB30:1;
			unsigned long :3;
			unsigned long MSTPB26:1;
			unsigned long MSTPB25:1;
			unsigned long :1;
			unsigned long MSTPB23:1;
			unsigned long :1;
			unsigned long MSTPB21:1;
			unsigned long :1;
			unsigned long MSTPB19:1;
			unsigned long :1;
			unsigned long MSTPB17:1;
			unsigned long :6;
			unsigned long MSTPB10:1;
			unsigned long MSTPB9:1;
			unsigned long :2;
			unsigned long MSTPB6:1;
			unsigned long :1;
			unsigned long MSTPB4:1;
			unsigned long :4;
		} BIT;
	} MSTPCRB;
	union {
		unsigned long LONG;
		struct {
			unsigned long DSLPE:1;
			unsigned long :1;
			unsigned long MSTPC29:1;
			unsigned long :1;
			unsigned long MSTPC27:1;
			unsigned long MSTPC26:1;
			unsigned long :6;
			unsigned long MSTPC19:1;
			unsigned long :18;
			unsigned long MSTPC0:1;
		} BIT;
	} MSTPCRC;
	union {
		unsigned long LONG;
		struct {
			unsigned long MSTPD31:1;
			unsigned long :20;
			unsigned long MSTPD10:1;
			unsigned long MSTPD9:1;
			unsigned long :9;
		} BIT;
	} MSTPCRD;
	union {
		unsigned long LONG;
		struct {
			unsigned long FCK:4;
			unsigned long ICK:4;
			unsigned long :8;
			unsigned long PCKA:4;
			unsigned long PCKB:4;
			unsigned long :4;
			unsigned long PCKD:4;
		} BIT;
	} SCKCR;
	char           wk3[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short CKSEL:3;
			unsigned short :8;
		} BIT;
	} SCKCR3;
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short STC:6;
			unsigned short :6;
			unsigned short PLIDIV:2;
		} BIT;
	} PLLCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char PLLEN:1;
		} BIT;
	} PLLCR2;
	char           wk4[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short STC:6;
			unsigned short :6;
			unsigned short PLIDIV:2;
		} BIT;
	} PLL2CR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char PLL2EN:1;
		} BIT;
	} PLL2CR2;
	char           wk5[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char MOSTP:1;
		} BIT;
	} MOSCCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char SOSTP:1;
		} BIT;
	} SOSCCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char LCSTP:1;
		} BIT;
	} LOCOCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char ILCSTP:1;
		} BIT;
	} ILOCOCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char HCSTP:1;
		} BIT;
	} HOCOCR;
	char           wk6[5];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char PL2OVF:1;
			unsigned char :1;
			unsigned char HCOVF:1;
			unsigned char PLOVF:1;
			unsigned char :1;
			unsigned char MOOVF:1;
		} BIT;
	} OSCOVFSR;
	char           wk7[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short CKOSTP:1;
			unsigned short CKODIV:3;
			unsigned short CKOSEL:4;
			unsigned short :8;
		} BIT;
	} CKOCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char OSTDE:1;
			unsigned char :6;
			unsigned char OSTDIE:1;
		} BIT;
	} OSTDCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char OSTDF:1;
		} BIT;
	} OSTDSR;
	char           wk8[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char LOFXIN:1;
		} BIT;
	} LOFCR;
	char           wk9[29];
	union {
		unsigned char BYTE;
		struct {
			unsigned char LOCOTRD2:8;
		} BIT;
	} LOCOTRR2;
	char           wk10[2];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char ILOCOTRD:5;
		} BIT;
	} ILOCOTRR;
	char           wk11[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char HOCOTRD:6;
		} BIT;
	} HOCOTRR0;
	char           wk12[5];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char CANFDCKDIV:3;
		} BIT;
	} CANFDCKDIVCR;
	char           wk13[5];
	union {
		unsigned char BYTE;
		struct {
			unsigned char USBCKSRDY:1;
			unsigned char USBCKSREQ:1;
			unsigned char :3;
			unsigned char USBCKSEL:3;
		} BIT;
	} USBCKCR;
	char           wk14[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char CANFDCKSRDY:1;
			unsigned char CANFDCKSREQ:1;
			unsigned char :3;
			unsigned char CANFDCKSEL:3;
		} BIT;
	} CANFDCKCR;
	char           wk15[12];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char SOSEL:1;
			unsigned char :4;
			unsigned char SODRV:2;
		} BIT;
	} SOMCR;
	char           wk16[27];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char PSA3:1;
			unsigned char PSA2:1;
			unsigned char PSA1:1;
			unsigned char PSA0:1;
		} BIT;
	} RPSCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char OPCMTSF:1;
			unsigned char :1;
			unsigned char OPCM:3;
		} BIT;
	} OPCCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RSTCKEN:1;
			unsigned char :4;
			unsigned char RSTCKSEL:3;
		} BIT;
	} RSTCKCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char MSTS:5;
		} BIT;
	} MOSCWTCR;
	char           wk17[7];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :3;
			unsigned char SOPCMTSF:1;
			unsigned char :3;
			unsigned char SOPCM:1;
		} BIT;
	} SOPCCR;
	char           wk18[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :3;
			unsigned short ADE3:1;
			unsigned short :1;
			unsigned short ADE2:1;
			unsigned short CTSUFNE:2;
			unsigned short ADE:2;
			unsigned short LPTCM1E:2;
			unsigned short SCIRXE:2;
			unsigned short :1;
			unsigned short SCIERE:1;
		} BIT;
	} SNZCR2;
	union {
		unsigned short WORD;
		struct {
			unsigned short SNZDTCE:1;
			unsigned short :1;
			unsigned short ADCSNZ3SEL:2;
			unsigned short ADCSNZ2SEL:2;
			unsigned short REMCSNZSEL:2;
			unsigned short CTSUSNZSEL:2;
			unsigned short ADCSNZSEL:2;
			unsigned short LPTSNZSEL:2;
			unsigned short SCISNZSEL:2;
		} BIT;
	} SNZCR;
	char           wk19[16];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char SWRF:1;
			unsigned char WDTRF:1;
			unsigned char IWDTRF:1;
		} BIT;
	} RSTSR2;
	char           wk20[1];
	unsigned short SWRR;
	char           wk21[28];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char LVD1IRQSEL:1;
			unsigned char LVD1IDTSEL:2;
		} BIT;
	} LVD1CR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char LVD1MON:1;
			unsigned char LVD1DET:1;
		} BIT;
	} LVD1SR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :5;
			unsigned char LVD2IRQSEL:1;
			unsigned char LVD2IDTSEL:2;
		} BIT;
	} LVD2CR1;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :6;
			unsigned char LVD2MON:1;
			unsigned char LVD2DET:1;
		} BIT;
	} LVD2SR;
	char           wk22[794];
	union {
		unsigned short WORD;
		struct {
			unsigned short PRKEY:8;
			unsigned short :4;
			unsigned short PRC3:1;
			unsigned short PRC2:1;
			unsigned short PRC1:1;
			unsigned short PRC0:1;
		} BIT;
	} PRCR;
	char           wk23[48784];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char LVD2RF:1;
			unsigned char LVD1RF:1;
			unsigned char LVD0RF:1;
			unsigned char PORF:1;
		} BIT;
	} RSTSR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char CWSF:1;
		} BIT;
	} RSTSR1;
	char           wk24[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char MOSEL:1;
			unsigned char MODRV21:1;
			unsigned char :5;
		} BIT;
	} MOFCR;
	char           wk25[3];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :1;
			unsigned char LVD2E:1;
			unsigned char LVD1E:1;
			unsigned char :1;
			unsigned char EXVCCINP2:1;
			unsigned char :3;
		} BIT;
	} LVCMPCR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char :2;
			unsigned char LVD2LVL:2;
			unsigned char LVD1LVL:4;
		} BIT;
	} LVDLVLR;
	char           wk26[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char LVD1RN:1;
			unsigned char LVD1RI:1;
			unsigned char :3;
			unsigned char LVD1CMPE:1;
			unsigned char :1;
			unsigned char LVD1RIE:1;
		} BIT;
	} LVD1CR0;
	union {
		unsigned char BYTE;
		struct {
			unsigned char LVD2RN:1;
			unsigned char LVD2RI:1;
			unsigned char :3;
			unsigned char LVD2CMPE:1;
			unsigned char :1;
			unsigned char LVD2RIE:1;
		} BIT;
	} LVD2CR0;
} st_system_t;

typedef struct st_temps {
	unsigned short TSCDR;
} st_temps_t;

typedef struct st_tmr0 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CMIEB:1;
			unsigned char CMIEA:1;
			unsigned char OVIE:1;
			unsigned char CCLR:2;
			unsigned char :3;
		} BIT;
	} TCR;
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char OSB:2;
			unsigned char OSA:2;
		} BIT;
	} TCSR;
	char           wk1[1];
	unsigned char  TCORA;
	char           wk2[1];
	unsigned char  TCORB;
	char           wk3[1];
	unsigned char  TCNT;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TMRIS:1;
			unsigned char :2;
			unsigned char CSS:2;
			unsigned char CKS:3;
		} BIT;
	} TCCR;
	char           wk5[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :7;
			unsigned char TCS:1;
		} BIT;
	} TCSTR;
} st_tmr0_t;

typedef struct st_tmr1 {
	union {
		unsigned char BYTE;
		struct {
			unsigned char CMIEB:1;
			unsigned char CMIEA:1;
			unsigned char OVIE:1;
			unsigned char CCLR:2;
			unsigned char :3;
		} BIT;
	} TCR;
	char           wk0[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char :4;
			unsigned char OSB:2;
			unsigned char OSA:2;
		} BIT;
	} TCSR;
	char           wk1[1];
	unsigned char  TCORA;
	char           wk2[1];
	unsigned char  TCORB;
	char           wk3[1];
	unsigned char  TCNT;
	char           wk4[1];
	union {
		unsigned char BYTE;
		struct {
			unsigned char TMRIS:1;
			unsigned char :2;
			unsigned char CSS:2;
			unsigned char CKS:3;
		} BIT;
	} TCCR;
} st_tmr1_t;

typedef struct st_tmr01 {
	unsigned short TCORA;
	unsigned short TCORB;
	unsigned short TCNT;
	unsigned short TCCR;
} st_tmr01_t;

typedef struct st_usb {
	union {
		unsigned short WORD;
		struct {
			unsigned short :5;
			unsigned short SCKE:1;
			unsigned short :3;
			unsigned short DCFM:1;
			unsigned short DRPD:1;
			unsigned short DPRPU:1;
			unsigned short :3;
			unsigned short USBE:1;
		} BIT;
	} SYSCFG;
	char           wk0[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short OVCMON:2;
			unsigned short :7;
			unsigned short HTACT:1;
			unsigned short :3;
			unsigned short IDMON:1;
			unsigned short LNST:2;
		} BIT;
	} SYSSTS0;
	char           wk1[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :4;
			unsigned short HNPBTOA:1;
			unsigned short EXICEN:1;
			unsigned short VBUSEN:1;
			unsigned short WKUP:1;
			unsigned short RWUPE:1;
			unsigned short USBRST:1;
			unsigned short RESUME:1;
			unsigned short UACT:1;
			unsigned short :1;
			unsigned short RHST:3;
		} BIT;
	} DVSTCTR0;
	char           wk2[10];
	union {
		unsigned short WORD;
		struct {
			unsigned char L;
			unsigned char H;
		} BYTE;
	} CFIFO;
	char           wk3[2];
	union {
		unsigned short WORD;
		struct {
			unsigned char L;
			unsigned char H;
		} BYTE;
	} D0FIFO;
	char           wk4[2];
	union {
		unsigned short WORD;
		struct {
			unsigned char L;
			unsigned char H;
		} BYTE;
	} D1FIFO;
	char           wk5[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short RCNT:1;
			unsigned short REW:1;
			unsigned short :3;
			unsigned short MBW:1;
			unsigned short :1;
			unsigned short BIGEND:1;
			unsigned short :2;
			unsigned short ISEL:1;
			unsigned short :1;
			unsigned short CURPIPE:4;
		} BIT;
	} CFIFOSEL;
	union {
		unsigned short WORD;
		struct {
			unsigned short BVAL:1;
			unsigned short BCLR:1;
			unsigned short FRDY:1;
			unsigned short :4;
			unsigned short DTLN:9;
		} BIT;
	} CFIFOCTR;
	char           wk6[4];
	union {
		unsigned short WORD;
		struct {
			unsigned short RCNT:1;
			unsigned short REW:1;
			unsigned short DCLRM:1;
			unsigned short DREQE:1;
			unsigned short :1;
			unsigned short MBW:1;
			unsigned short :1;
			unsigned short BIGEND:1;
			unsigned short :4;
			unsigned short CURPIPE:4;
		} BIT;
	} D0FIFOSEL;
	union {
		unsigned short WORD;
		struct {
			unsigned short BVAL:1;
			unsigned short BCLR:1;
			unsigned short FRDY:1;
			unsigned short :4;
			unsigned short DTLN:9;
		} BIT;
	} D0FIFOCTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short RCNT:1;
			unsigned short REW:1;
			unsigned short DCLRM:1;
			unsigned short DREQE:1;
			unsigned short :1;
			unsigned short MBW:1;
			unsigned short :1;
			unsigned short BIGEND:1;
			unsigned short :4;
			unsigned short CURPIPE:4;
		} BIT;
	} D1FIFOSEL;
	union {
		unsigned short WORD;
		struct {
			unsigned short BVAL:1;
			unsigned short BCLR:1;
			unsigned short FRDY:1;
			unsigned short :4;
			unsigned short DTLN:9;
		} BIT;
	} D1FIFOCTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short VBSE:1;
			unsigned short RSME:1;
			unsigned short SOFE:1;
			unsigned short DVSE:1;
			unsigned short CTRE:1;
			unsigned short BEMPE:1;
			unsigned short NRDYE:1;
			unsigned short BRDYE:1;
			unsigned short :8;
		} BIT;
	} INTENB0;
	union {
		unsigned short WORD;
		struct {
			unsigned short OVRCRE:1;
			unsigned short BCHGE:1;
			unsigned short :1;
			unsigned short DTCHE:1;
			unsigned short ATTCHE:1;
			unsigned short :4;
			unsigned short EOFERRE:1;
			unsigned short SIGNE:1;
			unsigned short SACKE:1;
			unsigned short :4;
		} BIT;
	} INTENB1;
	char           wk7[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PIPE9BRDYE:1;
			unsigned short PIPE8BRDYE:1;
			unsigned short PIPE7BRDYE:1;
			unsigned short PIPE6BRDYE:1;
			unsigned short PIPE5BRDYE:1;
			unsigned short PIPE4BRDYE:1;
			unsigned short PIPE3BRDYE:1;
			unsigned short PIPE2BRDYE:1;
			unsigned short PIPE1BRDYE:1;
			unsigned short PIPE0BRDYE:1;
		} BIT;
	} BRDYENB;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PIPE9NRDYE:1;
			unsigned short PIPE8NRDYE:1;
			unsigned short PIPE7NRDYE:1;
			unsigned short PIPE6NRDYE:1;
			unsigned short PIPE5NRDYE:1;
			unsigned short PIPE4NRDYE:1;
			unsigned short PIPE3NRDYE:1;
			unsigned short PIPE2NRDYE:1;
			unsigned short PIPE1NRDYE:1;
			unsigned short PIPE0NRDYE:1;
		} BIT;
	} NRDYENB;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PIPE9BEMPE:1;
			unsigned short PIPE8BEMPE:1;
			unsigned short PIPE7BEMPE:1;
			unsigned short PIPE6BEMPE:1;
			unsigned short PIPE5BEMPE:1;
			unsigned short PIPE4BEMPE:1;
			unsigned short PIPE3BEMPE:1;
			unsigned short PIPE2BEMPE:1;
			unsigned short PIPE1BEMPE:1;
			unsigned short PIPE0BEMPE:1;
		} BIT;
	} BEMPENB;
	union {
		unsigned short WORD;
		struct {
			unsigned short :7;
			unsigned short TRNENSEL:1;
			unsigned short :1;
			unsigned short BRDYM:1;
			unsigned short :1;
			unsigned short EDGESTS:1;
			unsigned short :4;
		} BIT;
	} SOFCFG;
	char           wk8[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short VBINT:1;
			unsigned short RESM:1;
			unsigned short SOFR:1;
			unsigned short DVST:1;
			unsigned short CTRT:1;
			unsigned short BEMP:1;
			unsigned short NRDY:1;
			unsigned short BRDY:1;
			unsigned short VBSTS:1;
			unsigned short DVSQ:3;
			unsigned short VALID:1;
			unsigned short CTSQ:3;
		} BIT;
	} INTSTS0;
	union {
		unsigned short WORD;
		struct {
			unsigned short OVRCR:1;
			unsigned short BCHG:1;
			unsigned short :1;
			unsigned short DTCH:1;
			unsigned short ATTCH:1;
			unsigned short :4;
			unsigned short EOFERR:1;
			unsigned short SIGN:1;
			unsigned short SACK:1;
			unsigned short :4;
		} BIT;
	} INTSTS1;
	char           wk9[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PIPE9BRDY:1;
			unsigned short PIPE8BRDY:1;
			unsigned short PIPE7BRDY:1;
			unsigned short PIPE6BRDY:1;
			unsigned short PIPE5BRDY:1;
			unsigned short PIPE4BRDY:1;
			unsigned short PIPE3BRDY:1;
			unsigned short PIPE2BRDY:1;
			unsigned short PIPE1BRDY:1;
			unsigned short PIPE0BRDY:1;
		} BIT;
	} BRDYSTS;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PIPE9NRDY:1;
			unsigned short PIPE8NRDY:1;
			unsigned short PIPE7NRDY:1;
			unsigned short PIPE6NRDY:1;
			unsigned short PIPE5NRDY:1;
			unsigned short PIPE4NRDY:1;
			unsigned short PIPE3NRDY:1;
			unsigned short PIPE2NRDY:1;
			unsigned short PIPE1NRDY:1;
			unsigned short PIPE0NRDY:1;
		} BIT;
	} NRDYSTS;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short PIPE9BEMP:1;
			unsigned short PIPE8BEMP:1;
			unsigned short PIPE7BEMP:1;
			unsigned short PIPE6BEMP:1;
			unsigned short PIPE5BEMP:1;
			unsigned short PIPE4BEMP:1;
			unsigned short PIPE3BEMP:1;
			unsigned short PIPE2BEMP:1;
			unsigned short PIPE1BEMP:1;
			unsigned short PIPE0BEMP:1;
		} BIT;
	} BEMPSTS;
	union {
		unsigned short WORD;
		struct {
			unsigned short OVRN:1;
			unsigned short CRCE:1;
			unsigned short :3;
			unsigned short FRNM:11;
		} BIT;
	} FRMNUM;
	char           wk10[6];
	union {
		unsigned short WORD;
		struct {
			unsigned short BREQUEST:8;
			unsigned short BMREQUESTTYPE:8;
		} BIT;
	} USBREQ;
	unsigned short USBVAL;
	unsigned short USBINDX;
	unsigned short USBLENG;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short SHTNAK:1;
			unsigned short :2;
			unsigned short DIR:1;
			unsigned short :4;
		} BIT;
	} DCPCFG;
	union {
		unsigned short WORD;
		struct {
			unsigned short DEVSEL:4;
			unsigned short :5;
			unsigned short MXPS:7;
		} BIT;
	} DCPMAXP;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short SUREQ:1;
			unsigned short :2;
			unsigned short SUREQCLR:1;
			unsigned short :2;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :2;
			unsigned short CCPL:1;
			unsigned short PID:2;
		} BIT;
	} DCPCTR;
	char           wk11[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short :12;
			unsigned short PIPESEL:4;
		} BIT;
	} PIPESEL;
	char           wk12[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short TYPE:2;
			unsigned short :3;
			unsigned short BFRE:1;
			unsigned short DBLB:1;
			unsigned short :1;
			unsigned short SHTNAK:1;
			unsigned short :2;
			unsigned short DIR:1;
			unsigned short EPNUM:4;
		} BIT;
	} PIPECFG;
	char           wk13[2];
	union {
		unsigned short WORD;
		struct {
			unsigned short DEVSEL:4;
			unsigned short :3;
			unsigned short MXPS:9;
		} BIT;
	} PIPEMAXP;
	union {
		unsigned short WORD;
		struct {
			unsigned short :3;
			unsigned short IFIS:1;
			unsigned short :9;
			unsigned short IITV:3;
		} BIT;
	} PIPEPERI;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short INBUFM:1;
			unsigned short :3;
			unsigned short ATREPM:1;
			unsigned short ACLRM:1;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :3;
			unsigned short PID:2;
		} BIT;
	} PIPE1CTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short INBUFM:1;
			unsigned short :3;
			unsigned short ATREPM:1;
			unsigned short ACLRM:1;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :3;
			unsigned short PID:2;
		} BIT;
	} PIPE2CTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short INBUFM:1;
			unsigned short :3;
			unsigned short ATREPM:1;
			unsigned short ACLRM:1;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :3;
			unsigned short PID:2;
		} BIT;
	} PIPE3CTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short INBUFM:1;
			unsigned short :3;
			unsigned short ATREPM:1;
			unsigned short ACLRM:1;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :3;
			unsigned short PID:2;
		} BIT;
	} PIPE4CTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short INBUFM:1;
			unsigned short :3;
			unsigned short ATREPM:1;
			unsigned short ACLRM:1;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :3;
			unsigned short PID:2;
		} BIT;
	} PIPE5CTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short :5;
			unsigned short ACLRM:1;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :3;
			unsigned short PID:2;
		} BIT;
	} PIPE6CTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short :5;
			unsigned short ACLRM:1;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :3;
			unsigned short PID:2;
		} BIT;
	} PIPE7CTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short :5;
			unsigned short ACLRM:1;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :3;
			unsigned short PID:2;
		} BIT;
	} PIPE8CTR;
	union {
		unsigned short WORD;
		struct {
			unsigned short BSTS:1;
			unsigned short :5;
			unsigned short ACLRM:1;
			unsigned short SQCLR:1;
			unsigned short SQSET:1;
			unsigned short SQMON:1;
			unsigned short PBUSY:1;
			unsigned short :3;
			unsigned short PID:2;
		} BIT;
	} PIPE9CTR;
	char           wk14[14];
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short TRENB:1;
			unsigned short TRCLR:1;
			unsigned short :8;
		} BIT;
	} PIPE1TRE;
	unsigned short PIPE1TRN;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short TRENB:1;
			unsigned short TRCLR:1;
			unsigned short :8;
		} BIT;
	} PIPE2TRE;
	unsigned short PIPE2TRN;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short TRENB:1;
			unsigned short TRCLR:1;
			unsigned short :8;
		} BIT;
	} PIPE3TRE;
	unsigned short PIPE3TRN;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short TRENB:1;
			unsigned short TRCLR:1;
			unsigned short :8;
		} BIT;
	} PIPE4TRE;
	unsigned short PIPE4TRN;
	union {
		unsigned short WORD;
		struct {
			unsigned short :6;
			unsigned short TRENB:1;
			unsigned short TRCLR:1;
			unsigned short :8;
		} BIT;
	} PIPE5TRE;
	unsigned short PIPE5TRN;
	char           wk15[44];
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short USBSPD:2;
			unsigned short :6;
		} BIT;
	} DEVADD0;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short USBSPD:2;
			unsigned short :6;
		} BIT;
	} DEVADD1;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short USBSPD:2;
			unsigned short :6;
		} BIT;
	} DEVADD2;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short USBSPD:2;
			unsigned short :6;
		} BIT;
	} DEVADD3;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short USBSPD:2;
			unsigned short :6;
		} BIT;
	} DEVADD4;
	union {
		unsigned short WORD;
		struct {
			unsigned short :8;
			unsigned short USBSPD:2;
			unsigned short :6;
		} BIT;
	} DEVADD5;
} st_usb_t;

typedef struct st_wdt {
	unsigned char  WDTRR;
	char           wk0[1];
	union {
		unsigned short WORD;
		struct {
			unsigned short :2;
			unsigned short RPSS:2;
			unsigned short :2;
			unsigned short RPES:2;
			unsigned short CKS:4;
			unsigned short :2;
			unsigned short TOPS:2;
		} BIT;
	} WDTCR;
	union {
		unsigned short WORD;
		struct {
			unsigned short REFEF:1;
			unsigned short UNDFF:1;
			unsigned short CNTVAL:14;
		} BIT;
	} WDTSR;
	union {
		unsigned char BYTE;
		struct {
			unsigned char RSTIRQS:1;
			unsigned char :7;
		} BIT;
	} WDTRCR;
} st_wdt_t;

#pragma bit_order
#pragma packoption

#endif
