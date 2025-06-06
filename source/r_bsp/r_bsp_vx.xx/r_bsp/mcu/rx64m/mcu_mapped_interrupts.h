/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : mcu_mapped_interrupts.c
* Description  : This module maps Interrupt A & B interrupts. Which interrupts are mapped depends on the macros in
*                r_bsp_interrupt_config.h.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 10.01.2014 1.00     First Release
*         : 15.05.2017 1.10     Changed the name of the following macro definition, because there was a mistake
*                               in the name of macro definition.
*                                (XXX = BSP_MAPPED_INT_CFG_B_VECT, BSP_MAPPED_INT_CFG_A_VECT, BSP_PRV_INT_B_NUM,
*                                       BSP_PRV_INT_A_NUM, IR, DTCE, IER, IPR ,IEN, VECT)
*                               - From XXX_TPU0_TGI0V to XXX_TPU0_TCI0V.
*                               - From XXX_TPU1_TGI1V to XXX_TPU1_TCI1V.
*                               - From XXX_TPU1_TGI1U to XXX_TPU1_TCI1U.
*                               - From XXX_TPU2_TGI2V to XXX_TPU2_TCI2V.
*                               - From XXX_TPU2_TGI2U to XXX_TPU2_TCI2U.
*                               - From XXX_TPU3_TGI3V to XXX_TPU3_TCI3V.
*                               - From XXX_TPU4_TGI4V to XXX_TPU4_TCI4V.
*                               - From XXX_TPU4_TGI4U to XXX_TPU4_TCI4U.
*                               - From XXX_TPU5_TGI5V to XXX_TPU5_TCI5V.
*                               - From XXX_TPU5_TGI5U to XXX_TPU5_TCI5U.
*                               - From XXX_MTU0_TGIV0 to XXX_MTU0_TCIV0.
*                               - From XXX_MTU1_TGIV1 to XXX_MTU1_TCIV1.
*                               - From XXX_MTU1_TGIU1 to XXX_MTU1_TCIU1.
*                               - From XXX_MTU2_TGIV2 to XXX_MTU2_TCIV2.
*                               - From XXX_MTU2_TGIU2 to XXX_MTU2_TCIU2.
*                               - From XXX_MTU3_TGIV3 to XXX_MTU3_TCIV3.
*                               - From XXX_MTU4_TGIV4 to XXX_MTU4_TCIV4.
*                               - From XXX_MTU6_TGIV6 to XXX_MTU6_TCIV6.
*                               - From XXX_MTU7_TGIV7 to XXX_MTU7_TCIV7.
*                               - From XXX_MTU8_TGIV8 to XXX_MTU8_TCIV8.
*                               Removed the following macro definition.
*                                - BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIU8
*         : 28.02.2019 1.11     Fixed coding style.
*         : 26.02.2025 1.12     Changed the disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Multiple inclusion prevention macro */
#ifndef MCU_MAPPED_INTERRUPTS_H
#define MCU_MAPPED_INTERRUPTS_H

/* The following macros define the number for each interrupt request source as it pertains to being an Interrupt B or
 * Interrupt A interrupt. These values are used when setting the interrupt select registers (i.e. SLIBXRn, SLIBrn, and
 * SLIARn).
 */
/* Available Interrupt B Sources. */
#define BSP_PRV_INT_B_NUM_CMT2_CMI2                                       1
#define BSP_PRV_INT_B_NUM_CMT3_CMI3                                       2
#define BSP_PRV_INT_B_NUM_TMR0_CMIA0                                      3
#define BSP_PRV_INT_B_NUM_TMR0_CMIB0                                      4
#define BSP_PRV_INT_B_NUM_TMR0_OVI0                                       5
#define BSP_PRV_INT_B_NUM_TMR1_CMIA1                                      6
#define BSP_PRV_INT_B_NUM_TMR1_CMIB1                                      7
#define BSP_PRV_INT_B_NUM_TMR1_OVI1                                       8
#define BSP_PRV_INT_B_NUM_TMR2_CMIA2                                      9
#define BSP_PRV_INT_B_NUM_TMR2_CMIB2                                      10
#define BSP_PRV_INT_B_NUM_TMR2_OVI2                                       11
#define BSP_PRV_INT_B_NUM_TMR3_CMIA3                                      12
#define BSP_PRV_INT_B_NUM_TMR3_CMIB3                                      13
#define BSP_PRV_INT_B_NUM_TMR3_OVI3                                       14
#define BSP_PRV_INT_B_NUM_TPU0_TGI0A                                      15
#define BSP_PRV_INT_B_NUM_TPU0_TGI0B                                      16
#define BSP_PRV_INT_B_NUM_TPU0_TGI0C                                      17
#define BSP_PRV_INT_B_NUM_TPU0_TGI0D                                      18
#define BSP_PRV_INT_B_NUM_TPU0_TCI0V                                      19
#define BSP_PRV_INT_B_NUM_TPU1_TGI1A                                      20
#define BSP_PRV_INT_B_NUM_TPU1_TGI1B                                      21
#define BSP_PRV_INT_B_NUM_TPU1_TCI1V                                      22
#define BSP_PRV_INT_B_NUM_TPU1_TCI1U                                      23
#define BSP_PRV_INT_B_NUM_TPU2_TGI2A                                      24
#define BSP_PRV_INT_B_NUM_TPU2_TGI2B                                      25
#define BSP_PRV_INT_B_NUM_TPU2_TCI2V                                      26
#define BSP_PRV_INT_B_NUM_TPU2_TCI2U                                      27
#define BSP_PRV_INT_B_NUM_TPU3_TGI3A                                      28
#define BSP_PRV_INT_B_NUM_TPU3_TGI3B                                      29
#define BSP_PRV_INT_B_NUM_TPU3_TGI3C                                      30
#define BSP_PRV_INT_B_NUM_TPU3_TGI3D                                      31
#define BSP_PRV_INT_B_NUM_TPU3_TCI3V                                      32
#define BSP_PRV_INT_B_NUM_TPU4_TGI4A                                      33
#define BSP_PRV_INT_B_NUM_TPU4_TGI4B                                      34
#define BSP_PRV_INT_B_NUM_TPU4_TCI4V                                      35
#define BSP_PRV_INT_B_NUM_TPU4_TCI4U                                      36
#define BSP_PRV_INT_B_NUM_TPU5_TGI5A                                      37
#define BSP_PRV_INT_B_NUM_TPU5_TGI5B                                      38
#define BSP_PRV_INT_B_NUM_TPU5_TCI5V                                      39
#define BSP_PRV_INT_B_NUM_TPU5_TCI5U                                      40
#define BSP_PRV_INT_B_NUM_CMTW0_IC0I0                                     41
#define BSP_PRV_INT_B_NUM_CMTW0_IC1I0                                     42
#define BSP_PRV_INT_B_NUM_CMTW0_OC0I0                                     43
#define BSP_PRV_INT_B_NUM_CMTW0_OC1I0                                     44
#define BSP_PRV_INT_B_NUM_CMTW1_IC0I1                                     45
#define BSP_PRV_INT_B_NUM_CMTW1_IC1I1                                     46
#define BSP_PRV_INT_B_NUM_CMTW1_OC0I1                                     47
#define BSP_PRV_INT_B_NUM_CMTW1_OC1I1                                     48
#define BSP_PRV_INT_B_NUM_RTC_CUP                                         49
#define BSP_PRV_INT_B_NUM_CAN0_RXF0                                       50
#define BSP_PRV_INT_B_NUM_CAN0_TXF0                                       51
#define BSP_PRV_INT_B_NUM_CAN0_RXM0                                       52
#define BSP_PRV_INT_B_NUM_CAN0_TXM0                                       53
#define BSP_PRV_INT_B_NUM_CAN1_RXF1                                       54
#define BSP_PRV_INT_B_NUM_CAN1_TXF1                                       55
#define BSP_PRV_INT_B_NUM_CAN1_RXM1                                       56
#define BSP_PRV_INT_B_NUM_CAN1_TXM1                                       57
#define BSP_PRV_INT_B_NUM_CAN2_RXF2                                       58
#define BSP_PRV_INT_B_NUM_CAN2_TXF2                                       59
#define BSP_PRV_INT_B_NUM_CAN2_RXM2                                       60
#define BSP_PRV_INT_B_NUM_CAN2_TXM2                                       61
#define BSP_PRV_INT_B_NUM_USB0_USBI0                                      62
#define BSP_PRV_INT_B_NUM_S12ADC0_S12ADI0                                 64
#define BSP_PRV_INT_B_NUM_S12ADC0_S12GBADI0                               65
#define BSP_PRV_INT_B_NUM_S12ADC1_S12ADI1                                 68
#define BSP_PRV_INT_B_NUM_S12ADC1_S12GBADI1                               69
#define BSP_PRV_INT_B_NUM_DES_DESEND                                      73
#define BSP_PRV_INT_B_NUM_SHA_SHADEND                                     74
#define BSP_PRV_INT_B_NUM_SHA_SHAEND                                      75
#define BSP_PRV_INT_B_NUM_RNG_RNGEND                                      76
#define BSP_PRV_INT_B_NUM_ELC_ELSR18I                                     79
#define BSP_PRV_INT_B_NUM_ELC_ELSR19I                                     80

/* Available Interrupt A Sources. */
#define BSP_PRV_INT_A_NUM_MTU0_TGIA0                                      1
#define BSP_PRV_INT_A_NUM_MTU0_TGIB0                                      2
#define BSP_PRV_INT_A_NUM_MTU0_TGIC0                                      3
#define BSP_PRV_INT_A_NUM_MTU0_TGID0                                      4
#define BSP_PRV_INT_A_NUM_MTU0_TCIV0                                      5
#define BSP_PRV_INT_A_NUM_MTU0_TGIE0                                      6
#define BSP_PRV_INT_A_NUM_MTU0_TGIF0                                      7
#define BSP_PRV_INT_A_NUM_MTU1_TGIA1                                      8
#define BSP_PRV_INT_A_NUM_MTU1_TGIB1                                      9
#define BSP_PRV_INT_A_NUM_MTU1_TCIV1                                      10
#define BSP_PRV_INT_A_NUM_MTU1_TCIU1                                      11
#define BSP_PRV_INT_A_NUM_MTU2_TGIA2                                      12
#define BSP_PRV_INT_A_NUM_MTU2_TGIB2                                      13
#define BSP_PRV_INT_A_NUM_MTU2_TCIV2                                      14
#define BSP_PRV_INT_A_NUM_MTU2_TCIU2                                      15
#define BSP_PRV_INT_A_NUM_MTU3_TGIA3                                      16
#define BSP_PRV_INT_A_NUM_MTU3_TGIB3                                      17
#define BSP_PRV_INT_A_NUM_MTU3_TGIC3                                      18
#define BSP_PRV_INT_A_NUM_MTU3_TGID3                                      19
#define BSP_PRV_INT_A_NUM_MTU3_TCIV3                                      20
#define BSP_PRV_INT_A_NUM_MTU4_TGIA4                                      21
#define BSP_PRV_INT_A_NUM_MTU4_TGIB4                                      22
#define BSP_PRV_INT_A_NUM_MTU4_TGIC4                                      23
#define BSP_PRV_INT_A_NUM_MTU4_TGID4                                      24
#define BSP_PRV_INT_A_NUM_MTU4_TCIV4                                      25
#define BSP_PRV_INT_A_NUM_MTU5_TGIU5                                      27
#define BSP_PRV_INT_A_NUM_MTU5_TGIV5                                      28
#define BSP_PRV_INT_A_NUM_MTU5_TGIW5                                      29
#define BSP_PRV_INT_A_NUM_MTU6_TGIA6                                      30
#define BSP_PRV_INT_A_NUM_MTU6_TGIB6                                      31
#define BSP_PRV_INT_A_NUM_MTU6_TGIC6                                      32
#define BSP_PRV_INT_A_NUM_MTU6_TGID6                                      33
#define BSP_PRV_INT_A_NUM_MTU6_TCIV6                                      34
#define BSP_PRV_INT_A_NUM_MTU7_TGIA7                                      35
#define BSP_PRV_INT_A_NUM_MTU7_TGIB7                                      36
#define BSP_PRV_INT_A_NUM_MTU7_TGIC7                                      37
#define BSP_PRV_INT_A_NUM_MTU7_TGID7                                      38
#define BSP_PRV_INT_A_NUM_MTU7_TCIV7                                      39
#define BSP_PRV_INT_A_NUM_MTU8_TGIA8                                      41
#define BSP_PRV_INT_A_NUM_MTU8_TGIB8                                      42
#define BSP_PRV_INT_A_NUM_MTU8_TGIC8                                      43
#define BSP_PRV_INT_A_NUM_MTU8_TGID8                                      44
#define BSP_PRV_INT_A_NUM_MTU8_TCIV8                                      45
#define BSP_PRV_INT_A_NUM_GPT0_GTCIA0                                     46
#define BSP_PRV_INT_A_NUM_GPT0_GTCIB0                                     47
#define BSP_PRV_INT_A_NUM_GPT0_GTCIC0                                     48
#define BSP_PRV_INT_A_NUM_GPT0_GTCID0                                     49
#define BSP_PRV_INT_A_NUM_GPT0_GDTE0                                      50
#define BSP_PRV_INT_A_NUM_GPT0_GTCIE0                                     51
#define BSP_PRV_INT_A_NUM_GPT0_GTCIF0                                     52
#define BSP_PRV_INT_A_NUM_GPT0_GTCIV0                                     53
#define BSP_PRV_INT_A_NUM_GPT0_GTCIU0                                     54
#define BSP_PRV_INT_A_NUM_GPTA_ETGIN                                      55
#define BSP_PRV_INT_A_NUM_GPTA_ETGIP                                      56
#define BSP_PRV_INT_A_NUM_GPT1_GTCIA1                                     57
#define BSP_PRV_INT_A_NUM_GPT1_GTCIB1                                     58
#define BSP_PRV_INT_A_NUM_GPT1_GTCIC1                                     59
#define BSP_PRV_INT_A_NUM_GPT1_GTCID1                                     60
#define BSP_PRV_INT_A_NUM_GPT1_GDTE1                                      61
#define BSP_PRV_INT_A_NUM_GPT1_GTCIE1                                     62
#define BSP_PRV_INT_A_NUM_GPT1_GTCIF1                                     63
#define BSP_PRV_INT_A_NUM_GPT1_GTCIV1                                     64
#define BSP_PRV_INT_A_NUM_GPT1_GTCIU1                                     65
#define BSP_PRV_INT_A_NUM_GPT2_GTCIA2                                     66
#define BSP_PRV_INT_A_NUM_GPT2_GTCIB2                                     67
#define BSP_PRV_INT_A_NUM_GPT2_GTCIC2                                     68
#define BSP_PRV_INT_A_NUM_GPT2_GTCID2                                     69
#define BSP_PRV_INT_A_NUM_GPT2_GDTE2                                      70
#define BSP_PRV_INT_A_NUM_GPT2_GTCIE2                                     71
#define BSP_PRV_INT_A_NUM_GPT2_GTCIF2                                     72
#define BSP_PRV_INT_A_NUM_GPT2_GTCIV2                                     73
#define BSP_PRV_INT_A_NUM_GPT2_GTCIU2                                     74
#define BSP_PRV_INT_A_NUM_GPT3_GTCIA3                                     75
#define BSP_PRV_INT_A_NUM_GPT3_GTCIB3                                     76
#define BSP_PRV_INT_A_NUM_GPT3_GTCIC3                                     77
#define BSP_PRV_INT_A_NUM_GPT3_GTCID3                                     78
#define BSP_PRV_INT_A_NUM_GPT3_GDTE3                                      79
#define BSP_PRV_INT_A_NUM_GPT3_GTCIE3                                     80
#define BSP_PRV_INT_A_NUM_GPT3_GTCIF3                                     81
#define BSP_PRV_INT_A_NUM_GPT3_GTCIV3                                     82
#define BSP_PRV_INT_A_NUM_GPT3_GTCIU3                                     83
#define BSP_PRV_INT_A_NUM_EPTPC_IPLS                                      84
#define BSP_PRV_INT_A_NUM_AES_AESRDY                                      86
#define BSP_PRV_INT_A_NUM_AES_AESEND                                      88

/* The appropriate macros will now be defined based on the vector selections made by the user.
 * These are the same macros that are defined for constant-mapped interrupts (vectors 0-127). This means that the
 * code can define, setup, and use mapped interrupts the same as would be done for constant-mapped interrupts.
 */
#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMT2_CMI2)
#define IR_CMT2_CMI2        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMT2_CMI2)
#define DTCE_CMT2_CMI2      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMT2_CMI2)
#define IER_CMT2_CMI2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMT2_CMI2)
#define IPR_CMT2_CMI2       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMT2_CMI2)
#define IEN_CMT2_CMI2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMT2_CMI2)
#define VECT_CMT2_CMI2      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMT2_CMI2)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMT3_CMI3)
#define IR_CMT3_CMI3        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMT3_CMI3)
#define DTCE_CMT3_CMI3      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMT3_CMI3)
#define IER_CMT3_CMI3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMT3_CMI3)
#define IPR_CMT3_CMI3       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMT3_CMI3)
#define IEN_CMT3_CMI3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMT3_CMI3)
#define VECT_CMT3_CMI3      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMT3_CMI3)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0A)
#define IR_TPU0_TGI0A        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0A)
#define DTCE_TPU0_TGI0A      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0A)
#define IER_TPU0_TGI0A       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0A)
#define IPR_TPU0_TGI0A       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0A)
#define IEN_TPU0_TGI0A       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0A)
#define VECT_TPU0_TGI0A      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0A)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0B)
#define IR_TPU0_TGI0B        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0B)
#define DTCE_TPU0_TGI0B      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0B)
#define IER_TPU0_TGI0B       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0B)
#define IPR_TPU0_TGI0B       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0B)
#define IEN_TPU0_TGI0B       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0B)
#define VECT_TPU0_TGI0B      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0B)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0C)
#define IR_TPU0_TGI0C        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0C)
#define DTCE_TPU0_TGI0C      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0C)
#define IER_TPU0_TGI0C       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0C)
#define IPR_TPU0_TGI0C       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0C)
#define IEN_TPU0_TGI0C       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0C)
#define VECT_TPU0_TGI0C      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0C)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0D)
#define IR_TPU0_TGI0D        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0D)
#define DTCE_TPU0_TGI0D      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0D)
#define IER_TPU0_TGI0D       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0D)
#define IPR_TPU0_TGI0D       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0D)
#define IEN_TPU0_TGI0D       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0D)
#define VECT_TPU0_TGI0D      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TGI0D)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TCI0V)
#define IR_TPU0_TCI0V        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TCI0V)
#define DTCE_TPU0_TCI0V      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TCI0V)
#define IER_TPU0_TCI0V       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TCI0V)
#define IPR_TPU0_TCI0V       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TCI0V)
#define IEN_TPU0_TCI0V       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU0_TCI0V)
#define VECT_TPU0_TCI0V      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU0_TCI0V)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1B)
#define IR_TPU1_TGI1B        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1B)
#define DTCE_TPU1_TGI1B      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1B)
#define IER_TPU1_TGI1B       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1B)
#define IPR_TPU1_TGI1B       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1B)
#define IEN_TPU1_TGI1B       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1B)
#define VECT_TPU1_TGI1B      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1B)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1V)
#define IR_TPU1_TCI1V        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1V)
#define DTCE_TPU1_TCI1V      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1V)
#define IER_TPU1_TCI1V       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1V)
#define IPR_TPU1_TCI1V       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1V)
#define IEN_TPU1_TCI1V       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1V)
#define VECT_TPU1_TCI1V      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1V)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1U)
#define IR_TPU1_TCI1U        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1U)
#define DTCE_TPU1_TCI1U      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1U)
#define IER_TPU1_TCI1U       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1U)
#define IPR_TPU1_TCI1U       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1U)
#define IEN_TPU1_TCI1U       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1U)
#define VECT_TPU1_TCI1U      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TCI1U)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2A)
#define IR_TPU2_TGI2A        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2A)
#define DTCE_TPU2_TGI2A      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2A)
#define IER_TPU2_TGI2A       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2A)
#define IPR_TPU2_TGI2A       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2A)
#define IEN_TPU2_TGI2A       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2A)
#define VECT_TPU2_TGI2A      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2A)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2B)
#define IR_TPU2_TGI2B        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2B)
#define DTCE_TPU2_TGI2B      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2B)
#define IER_TPU2_TGI2B       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2B)
#define IPR_TPU2_TGI2B       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2B)
#define IEN_TPU2_TGI2B       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2B)
#define VECT_TPU2_TGI2B      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TGI2B)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2V)
#define IR_TPU2_TCI2V        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2V)
#define DTCE_TPU2_TCI2V      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2V)
#define IER_TPU2_TCI2V       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2V)
#define IPR_TPU2_TCI2V       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2V)
#define IEN_TPU2_TCI2V       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2V)
#define VECT_TPU2_TCI2V      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2V)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2U)
#define IR_TPU2_TCI2U        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2U)
#define DTCE_TPU2_TCI2U      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2U)
#define IER_TPU2_TCI2U       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2U)
#define IPR_TPU2_TCI2U       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2U)
#define IEN_TPU2_TCI2U       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2U)
#define VECT_TPU2_TCI2U      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU2_TCI2U)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3A)
#define IR_TPU3_TGI3A        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3A)
#define DTCE_TPU3_TGI3A      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3A)
#define IER_TPU3_TGI3A       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3A)
#define IPR_TPU3_TGI3A       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3A)
#define IEN_TPU3_TGI3A       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3A)
#define VECT_TPU3_TGI3A      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3A)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3B)
#define IR_TPU3_TGI3B        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3B)
#define DTCE_TPU3_TGI3B      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3B)
#define IER_TPU3_TGI3B       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3B)
#define IPR_TPU3_TGI3B       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3B)
#define IEN_TPU3_TGI3B       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3B)
#define VECT_TPU3_TGI3B      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3B)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1A)
#define IR_TPU1_TGI1A        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1A)
#define DTCE_TPU1_TGI1A      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1A)
#define IER_TPU1_TGI1A       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1A)
#define IPR_TPU1_TGI1A       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1A)
#define IEN_TPU1_TGI1A       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1A)
#define VECT_TPU1_TGI1A      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU1_TGI1A)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3C)
#define IR_TPU3_TGI3C        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3C)
#define DTCE_TPU3_TGI3C      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3C)
#define IER_TPU3_TGI3C       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3C)
#define IPR_TPU3_TGI3C       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3C)
#define IEN_TPU3_TGI3C       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3C)
#define VECT_TPU3_TGI3C      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3C)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIA0)
#define IR_TMR0_CMIA0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIA0)
#define DTCE_TMR0_CMIA0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIA0)
#define IER_TMR0_CMIA0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIA0)
#define IPR_TMR0_CMIA0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIA0)
#define IEN_TMR0_CMIA0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIA0)
#define VECT_TMR0_CMIA0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIA0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIB0)
#define IR_TMR0_CMIB0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIB0)
#define DTCE_TMR0_CMIB0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIB0)
#define IER_TMR0_CMIB0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIB0)
#define IPR_TMR0_CMIB0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIB0)
#define IEN_TMR0_CMIB0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIB0)
#define VECT_TMR0_CMIB0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_CMIB0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_OVI0)
#define IR_TMR0_OVI0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_OVI0)
#define DTCE_TMR0_OVI0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_OVI0)
#define IER_TMR0_OVI0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR0_OVI0)
#define IPR_TMR0_OVI0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_OVI0)
#define IEN_TMR0_OVI0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR0_OVI0)
#define VECT_TMR0_OVI0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR0_OVI0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIA1)
#define IR_TMR1_CMIA1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIA1)
#define DTCE_TMR1_CMIA1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIA1)
#define IER_TMR1_CMIA1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIA1)
#define IPR_TMR1_CMIA1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIA1)
#define IEN_TMR1_CMIA1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIA1)
#define VECT_TMR1_CMIA1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIA1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIB1)
#define IR_TMR1_CMIB1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIB1)
#define DTCE_TMR1_CMIB1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIB1)
#define IER_TMR1_CMIB1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIB1)
#define IPR_TMR1_CMIB1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIB1)
#define IEN_TMR1_CMIB1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIB1)
#define VECT_TMR1_CMIB1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_CMIB1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_OVI1)
#define IR_TMR1_OVI1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_OVI1)
#define DTCE_TMR1_OVI1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_OVI1)
#define IER_TMR1_OVI1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR1_OVI1)
#define IPR_TMR1_OVI1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_OVI1)
#define IEN_TMR1_OVI1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR1_OVI1)
#define VECT_TMR1_OVI1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR1_OVI1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIA2)
#define IR_TMR2_CMIA2        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIA2)
#define DTCE_TMR2_CMIA2      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIA2)
#define IER_TMR2_CMIA2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIA2)
#define IPR_TMR2_CMIA2       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIA2)
#define IEN_TMR2_CMIA2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIA2)
#define VECT_TMR2_CMIA2      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIA2)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIB2)
#define IR_TMR2_CMIB2        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIB2)
#define DTCE_TMR2_CMIB2      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIB2)
#define IER_TMR2_CMIB2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIB2)
#define IPR_TMR2_CMIB2       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIB2)
#define IEN_TMR2_CMIB2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIB2)
#define VECT_TMR2_CMIB2      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_CMIB2)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_OVI2)
#define IR_TMR2_OVI2        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_OVI2)
#define DTCE_TMR2_OVI2      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_OVI2)
#define IER_TMR2_OVI2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR2_OVI2)
#define IPR_TMR2_OVI2       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_OVI2)
#define IEN_TMR2_OVI2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR2_OVI2)
#define VECT_TMR2_OVI2      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR2_OVI2)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIA3)
#define IR_TMR3_CMIA3        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIA3)
#define DTCE_TMR3_CMIA3      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIA3)
#define IER_TMR3_CMIA3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIA3)
#define IPR_TMR3_CMIA3       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIA3)
#define IEN_TMR3_CMIA3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIA3)
#define VECT_TMR3_CMIA3      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIA3)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIB3)
#define IR_TMR3_CMIB3        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIB3)
#define DTCE_TMR3_CMIB3      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIB3)
#define IER_TMR3_CMIB3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIB3)
#define IPR_TMR3_CMIB3       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIB3)
#define IEN_TMR3_CMIB3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIB3)
#define VECT_TMR3_CMIB3      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_CMIB3)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_OVI3)
#define IR_TMR3_OVI3        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_OVI3)
#define DTCE_TMR3_OVI3      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_OVI3)
#define IER_TMR3_OVI3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TMR3_OVI3)
#define IPR_TMR3_OVI3       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_OVI3)
#define IEN_TMR3_OVI3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TMR3_OVI3)
#define VECT_TMR3_OVI3      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TMR3_OVI3)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3D)
#define IR_TPU3_TGI3D        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3D)
#define DTCE_TPU3_TGI3D      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3D)
#define IER_TPU3_TGI3D       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3D)
#define IPR_TPU3_TGI3D       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3D)
#define IEN_TPU3_TGI3D       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3D)
#define VECT_TPU3_TGI3D      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TGI3D)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TCI3V)
#define IR_TPU3_TCI3V        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TCI3V)
#define DTCE_TPU3_TCI3V      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TCI3V)
#define IER_TPU3_TCI3V       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TCI3V)
#define IPR_TPU3_TCI3V       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TCI3V)
#define IEN_TPU3_TCI3V       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU3_TCI3V)
#define VECT_TPU3_TCI3V      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU3_TCI3V)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4A)
#define IR_TPU4_TGI4A        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4A)
#define DTCE_TPU4_TGI4A      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4A)
#define IER_TPU4_TGI4A       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4A)
#define IPR_TPU4_TGI4A       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4A)
#define IEN_TPU4_TGI4A       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4A)
#define VECT_TPU4_TGI4A      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4A)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4B)
#define IR_TPU4_TGI4B        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4B)
#define DTCE_TPU4_TGI4B      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4B)
#define IER_TPU4_TGI4B       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4B)
#define IPR_TPU4_TGI4B       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4B)
#define IEN_TPU4_TGI4B       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4B)
#define VECT_TPU4_TGI4B      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TGI4B)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4V)
#define IR_TPU4_TCI4V        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4V)
#define DTCE_TPU4_TCI4V      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4V)
#define IER_TPU4_TCI4V       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4V)
#define IPR_TPU4_TCI4V       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4V)
#define IEN_TPU4_TCI4V       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4V)
#define VECT_TPU4_TCI4V      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4V)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4U)
#define IR_TPU4_TCI4U        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4U)
#define DTCE_TPU4_TCI4U      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4U)
#define IER_TPU4_TCI4U       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4U)
#define IPR_TPU4_TCI4U       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4U)
#define IEN_TPU4_TCI4U       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4U)
#define VECT_TPU4_TCI4U      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU4_TCI4U)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5A)
#define IR_TPU5_TGI5A        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5A)
#define DTCE_TPU5_TGI5A      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5A)
#define IER_TPU5_TGI5A       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5A)
#define IPR_TPU5_TGI5A       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5A)
#define IEN_TPU5_TGI5A       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5A)
#define VECT_TPU5_TGI5A      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5A)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5B)
#define IR_TPU5_TGI5B        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5B)
#define DTCE_TPU5_TGI5B      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5B)
#define IER_TPU5_TGI5B       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5B)
#define IPR_TPU5_TGI5B       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5B)
#define IEN_TPU5_TGI5B       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5B)
#define VECT_TPU5_TGI5B      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TGI5B)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5V)
#define IR_TPU5_TCI5V        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5V)
#define DTCE_TPU5_TCI5V      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5V)
#define IER_TPU5_TCI5V       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5V)
#define IPR_TPU5_TCI5V       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5V)
#define IEN_TPU5_TCI5V       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5V)
#define VECT_TPU5_TCI5V      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5V)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5U)
#define IR_TPU5_TCI5U        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5U)
#define DTCE_TPU5_TCI5U      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5U)
#define IER_TPU5_TCI5U       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5U)
#define IPR_TPU5_TCI5U       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5U)
#define IEN_TPU5_TCI5U       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5U)
#define VECT_TPU5_TCI5U      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_TPU5_TCI5U)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC0I0)
#define IR_CMTW0_IC0I0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC0I0)
#define DTCE_CMTW0_IC0I0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC0I0)
#define IER_CMTW0_IC0I0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC0I0)
#define IPR_CMTW0_IC0I0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC0I0)
#define IEN_CMTW0_IC0I0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC0I0)
#define VECT_CMTW0_IC0I0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC0I0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC1I0)
#define IR_CMTW0_IC1I0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC1I0)
#define DTCE_CMTW0_IC1I0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC1I0)
#define IER_CMTW0_IC1I0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC1I0)
#define IPR_CMTW0_IC1I0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC1I0)
#define IEN_CMTW0_IC1I0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC1I0)
#define VECT_CMTW0_IC1I0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_IC1I0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC0I0)
#define IR_CMTW0_OC0I0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC0I0)
#define DTCE_CMTW0_OC0I0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC0I0)
#define IER_CMTW0_OC0I0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC0I0)
#define IPR_CMTW0_OC0I0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC0I0)
#define IEN_CMTW0_OC0I0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC0I0)
#define VECT_CMTW0_OC0I0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC0I0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC1I0)
#define IR_CMTW0_OC1I0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC1I0)
#define DTCE_CMTW0_OC1I0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC1I0)
#define IER_CMTW0_OC1I0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC1I0)
#define IPR_CMTW0_OC1I0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC1I0)
#define IEN_CMTW0_OC1I0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC1I0)
#define VECT_CMTW0_OC1I0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW0_OC1I0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC0I1)
#define IR_CMTW1_IC0I1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC0I1)
#define DTCE_CMTW1_IC0I1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC0I1)
#define IER_CMTW1_IC0I1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC0I1)
#define IPR_CMTW1_IC0I1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC0I1)
#define IEN_CMTW1_IC0I1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC0I1)
#define VECT_CMTW1_IC0I1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC0I1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC1I1)
#define IR_CMTW1_IC1I1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC1I1)
#define DTCE_CMTW1_IC1I1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC1I1)
#define IER_CMTW1_IC1I1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC1I1)
#define IPR_CMTW1_IC1I1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC1I1)
#define IEN_CMTW1_IC1I1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC1I1)
#define VECT_CMTW1_IC1I1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_IC1I1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC0I1)
#define IR_CMTW1_OC0I1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC0I1)
#define DTCE_CMTW1_OC0I1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC0I1)
#define IER_CMTW1_OC0I1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC0I1)
#define IPR_CMTW1_OC0I1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC0I1)
#define IEN_CMTW1_OC0I1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC0I1)
#define VECT_CMTW1_OC0I1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC0I1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC1I1)
#define IR_CMTW1_OC1I1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC1I1)
#define DTCE_CMTW1_OC1I1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC1I1)
#define IER_CMTW1_OC1I1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC1I1)
#define IPR_CMTW1_OC1I1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC1I1)
#define IEN_CMTW1_OC1I1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC1I1)
#define VECT_CMTW1_OC1I1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CMTW1_OC1I1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_RTC_CUP)
#define IR_RTC_CUP        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_RTC_CUP)
#define DTCE_RTC_CUP      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_RTC_CUP)
#define IER_RTC_CUP       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_RTC_CUP)
#define IPR_RTC_CUP       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_RTC_CUP)
#define IEN_RTC_CUP       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_RTC_CUP)
#define VECT_RTC_CUP      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_RTC_CUP)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXF0)
#define IR_CAN0_RXF0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXF0)
#define DTCE_CAN0_RXF0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXF0)
#define IER_CAN0_RXF0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXF0)
#define IPR_CAN0_RXF0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXF0)
#define IEN_CAN0_RXF0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXF0)
#define VECT_CAN0_RXF0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXF0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXF0)
#define IR_CAN0_TXF0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXF0)
#define DTCE_CAN0_TXF0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXF0)
#define IER_CAN0_TXF0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXF0)
#define IPR_CAN0_TXF0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXF0)
#define IEN_CAN0_TXF0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXF0)
#define VECT_CAN0_TXF0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXF0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXM0)
#define IR_CAN0_RXM0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXM0)
#define DTCE_CAN0_RXM0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXM0)
#define IER_CAN0_RXM0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXM0)
#define IPR_CAN0_RXM0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXM0)
#define IEN_CAN0_RXM0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXM0)
#define VECT_CAN0_RXM0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_RXM0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXM0)
#define IR_CAN0_TXM0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXM0)
#define DTCE_CAN0_TXM0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXM0)
#define IER_CAN0_TXM0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXM0)
#define IPR_CAN0_TXM0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXM0)
#define IEN_CAN0_TXM0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXM0)
#define VECT_CAN0_TXM0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN0_TXM0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXF1)
#define IR_CAN1_RXF1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXF1)
#define DTCE_CAN1_RXF1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXF1)
#define IER_CAN1_RXF1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXF1)
#define IPR_CAN1_RXF1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXF1)
#define IEN_CAN1_RXF1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXF1)
#define VECT_CAN1_RXF1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXF1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXF1)
#define IR_CAN1_TXF1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXF1)
#define DTCE_CAN1_TXF1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXF1)
#define IER_CAN1_TXF1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXF1)
#define IPR_CAN1_TXF1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXF1)
#define IEN_CAN1_TXF1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXF1)
#define VECT_CAN1_TXF1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXF1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXM1)
#define IR_CAN1_RXM1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXM1)
#define DTCE_CAN1_RXM1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXM1)
#define IER_CAN1_RXM1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXM1)
#define IPR_CAN1_RXM1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXM1)
#define IEN_CAN1_RXM1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXM1)
#define VECT_CAN1_RXM1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_RXM1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXM1)
#define IR_CAN1_TXM1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXM1)
#define DTCE_CAN1_TXM1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXM1)
#define IER_CAN1_TXM1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXM1)
#define IPR_CAN1_TXM1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXM1)
#define IEN_CAN1_TXM1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXM1)
#define VECT_CAN1_TXM1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN1_TXM1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXF2)
#define IR_CAN2_RXF2        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXF2)
#define DTCE_CAN2_RXF2      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXF2)
#define IER_CAN2_RXF2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXF2)
#define IPR_CAN2_RXF2       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXF2)
#define IEN_CAN2_RXF2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXF2)
#define VECT_CAN2_RXF2      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXF2)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXF2)
#define IR_CAN2_TXF2        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXF2)
#define DTCE_CAN2_TXF2      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXF2)
#define IER_CAN2_TXF2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXF2)
#define IPR_CAN2_TXF2       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXF2)
#define IEN_CAN2_TXF2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXF2)
#define VECT_CAN2_TXF2      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXF2)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXM2)
#define IR_CAN2_RXM2        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXM2)
#define DTCE_CAN2_RXM2      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXM2)
#define IER_CAN2_RXM2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXM2)
#define IPR_CAN2_RXM2       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXM2)
#define IEN_CAN2_RXM2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXM2)
#define VECT_CAN2_RXM2      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_RXM2)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXM2)
#define IR_CAN2_TXM2        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXM2)
#define DTCE_CAN2_TXM2      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXM2)
#define IER_CAN2_TXM2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXM2)
#define IPR_CAN2_TXM2       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXM2)
#define IEN_CAN2_TXM2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXM2)
#define VECT_CAN2_TXM2      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_CAN2_TXM2)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_USB0_USBI0)
#define IR_USB0_USBI0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_USB0_USBI0)
#define DTCE_USB0_USBI0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_USB0_USBI0)
#define IER_USB0_USBI0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_USB0_USBI0)
#define IPR_USB0_USBI0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_USB0_USBI0)
#define IEN_USB0_USBI0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_USB0_USBI0)
#define VECT_USB0_USBI0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_USB0_USBI0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12ADI0)
#define IR_S12ADC0_S12ADI0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12ADI0)
#define DTCE_S12ADC0_S12ADI0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12ADI0)
#define IER_S12ADC0_S12ADI0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12ADI0)
#define IPR_S12ADC0_S12ADI0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12ADI0)
#define IEN_S12ADC0_S12ADI0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12ADI0)
#define VECT_S12ADC0_S12ADI0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12ADI0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12GBADI0)
#define IR_S12ADC0_S12GBADI0        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12GBADI0)
#define DTCE_S12ADC0_S12GBADI0      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12GBADI0)
#define IER_S12ADC0_S12GBADI0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12GBADI0)
#define IPR_S12ADC0_S12GBADI0       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12GBADI0)
#define IEN_S12ADC0_S12GBADI0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12GBADI0)
#define VECT_S12ADC0_S12GBADI0      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC0_S12GBADI0)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12ADI1)
#define IR_S12ADC1_S12ADI1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12ADI1)
#define DTCE_S12ADC1_S12ADI1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12ADI1)
#define IER_S12ADC1_S12ADI1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12ADI1)
#define IPR_S12ADC1_S12ADI1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12ADI1)
#define IEN_S12ADC1_S12ADI1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12ADI1)
#define VECT_S12ADC1_S12ADI1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12ADI1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12GBADI1)
#define IR_S12ADC1_S12GBADI1        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12GBADI1)
#define DTCE_S12ADC1_S12GBADI1      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12GBADI1)
#define IER_S12ADC1_S12GBADI1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12GBADI1)
#define IPR_S12ADC1_S12GBADI1       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12GBADI1)
#define IEN_S12ADC1_S12GBADI1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12GBADI1)
#define VECT_S12ADC1_S12GBADI1      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_S12ADC1_S12GBADI1)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_DES_DESEND)
#define IR_DES_DESEND        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_DES_DESEND)
#define DTCE_DES_DESEND      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_DES_DESEND)
#define IER_DES_DESEND       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_DES_DESEND)
#define IPR_DES_DESEND       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_DES_DESEND)
#define IEN_DES_DESEND       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_DES_DESEND)
#define VECT_DES_DESEND      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_DES_DESEND)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHADEND)
#define IR_SHA_SHADEND        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHADEND)
#define DTCE_SHA_SHADEND      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHADEND)
#define IER_SHA_SHADEND       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_SHA_SHADEND)
#define IPR_SHA_SHADEND       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHADEND)
#define IEN_SHA_SHADEND       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_SHA_SHADEND)
#define VECT_SHA_SHADEND      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHADEND)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHAEND)
#define IR_SHA_SHAEND        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHAEND)
#define DTCE_SHA_SHAEND      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHAEND)
#define IER_SHA_SHAEND       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_SHA_SHAEND)
#define IPR_SHA_SHAEND       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHAEND)
#define IEN_SHA_SHAEND       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_SHA_SHAEND)
#define VECT_SHA_SHAEND      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_SHA_SHAEND)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_RNG_RNGEND)
#define IR_RNG_RNGEND        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_RNG_RNGEND)
#define DTCE_RNG_RNGEND      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_RNG_RNGEND)
#define IER_RNG_RNGEND       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_RNG_RNGEND)
#define IPR_RNG_RNGEND       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_RNG_RNGEND)
#define IEN_RNG_RNGEND       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_RNG_RNGEND)
#define VECT_RNG_RNGEND      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_RNG_RNGEND)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR18I)
#define IR_ELC_ELSR18I        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR18I)
#define DTCE_ELC_ELSR18I      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR18I)
#define IER_ELC_ELSR18I       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR18I)
#define IPR_ELC_ELSR18I       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR18I)
#define IEN_ELC_ELSR18I       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR18I)
#define VECT_ELC_ELSR18I      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR18I)
#endif

#if BSP_PRV_VALID_MAP_INT(B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR19I)
#define IR_ELC_ELSR19I        BSP_PRV_IR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR19I)
#define DTCE_ELC_ELSR19I      BSP_PRV_DTCE(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR19I)
#define IER_ELC_ELSR19I       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR19I)
#define IPR_ELC_ELSR19I       BSP_PRV_IPR(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR19I)
#define IEN_ELC_ELSR19I       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR19I)
#define VECT_ELC_ELSR19I      BSP_PRV_VECT(BSP_PRV_B, BSP_MAPPED_INT_CFG_B_VECT_ELC_ELSR19I)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIA1)
#define IR_MTU1_TGIA1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIA1)
#define DTCE_MTU1_TGIA1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIA1)
#define IER_MTU1_TGIA1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIA1)
#define IPR_MTU1_TGIA1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIA1)
#define IEN_MTU1_TGIA1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIA1)
#define VECT_MTU1_TGIA1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIA1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIA0)
#define IR_MTU0_TGIA0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIA0)
#define DTCE_MTU0_TGIA0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIA0)
#define IER_MTU0_TGIA0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIA0)
#define IPR_MTU0_TGIA0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIA0)
#define IEN_MTU0_TGIA0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIA0)
#define VECT_MTU0_TGIA0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIA0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIB0)
#define IR_MTU0_TGIB0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIB0)
#define DTCE_MTU0_TGIB0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIB0)
#define IER_MTU0_TGIB0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIB0)
#define IPR_MTU0_TGIB0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIB0)
#define IEN_MTU0_TGIB0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIB0)
#define VECT_MTU0_TGIB0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIB0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIC0)
#define IR_MTU0_TGIC0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIC0)
#define DTCE_MTU0_TGIC0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIC0)
#define IER_MTU0_TGIC0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIC0)
#define IPR_MTU0_TGIC0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIC0)
#define IEN_MTU0_TGIC0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIC0)
#define VECT_MTU0_TGIC0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIC0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGID0)
#define IR_MTU0_TGID0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGID0)
#define DTCE_MTU0_TGID0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGID0)
#define IER_MTU0_TGID0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGID0)
#define IPR_MTU0_TGID0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGID0)
#define IEN_MTU0_TGID0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGID0)
#define VECT_MTU0_TGID0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGID0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TCIV0)
#define IR_MTU0_TCIV0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TCIV0)
#define DTCE_MTU0_TCIV0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TCIV0)
#define IER_MTU0_TCIV0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TCIV0)
#define IPR_MTU0_TCIV0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TCIV0)
#define IEN_MTU0_TCIV0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TCIV0)
#define VECT_MTU0_TCIV0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TCIV0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIE0)
#define IR_MTU0_TGIE0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIE0)
#define DTCE_MTU0_TGIE0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIE0)
#define IER_MTU0_TGIE0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIE0)
#define IPR_MTU0_TGIE0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIE0)
#define IEN_MTU0_TGIE0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIE0)
#define VECT_MTU0_TGIE0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIE0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIF0)
#define IR_MTU0_TGIF0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIF0)
#define DTCE_MTU0_TGIF0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIF0)
#define IER_MTU0_TGIF0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIF0)
#define IPR_MTU0_TGIF0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIF0)
#define IEN_MTU0_TGIF0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIF0)
#define VECT_MTU0_TGIF0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU0_TGIF0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIB1)
#define IR_MTU1_TGIB1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIB1)
#define DTCE_MTU1_TGIB1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIB1)
#define IER_MTU1_TGIB1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIB1)
#define IPR_MTU1_TGIB1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIB1)
#define IEN_MTU1_TGIB1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIB1)
#define VECT_MTU1_TGIB1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TGIB1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIV1)
#define IR_MTU1_TCIV1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIV1)
#define DTCE_MTU1_TCIV1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIV1)
#define IER_MTU1_TCIV1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIV1)
#define IPR_MTU1_TCIV1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIV1)
#define IEN_MTU1_TCIV1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIV1)
#define VECT_MTU1_TCIV1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIV1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIU1)
#define IR_MTU1_TCIU1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIU1)
#define DTCE_MTU1_TCIU1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIU1)
#define IER_MTU1_TCIU1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIU1)
#define IPR_MTU1_TCIU1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIU1)
#define IEN_MTU1_TCIU1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIU1)
#define VECT_MTU1_TCIU1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU1_TCIU1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIA2)
#define IR_MTU2_TGIA2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIA2)
#define DTCE_MTU2_TGIA2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIA2)
#define IER_MTU2_TGIA2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIA2)
#define IPR_MTU2_TGIA2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIA2)
#define IEN_MTU2_TGIA2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIA2)
#define VECT_MTU2_TGIA2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIA2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIB2)
#define IR_MTU2_TGIB2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIB2)
#define DTCE_MTU2_TGIB2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIB2)
#define IER_MTU2_TGIB2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIB2)
#define IPR_MTU2_TGIB2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIB2)
#define IEN_MTU2_TGIB2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIB2)
#define VECT_MTU2_TGIB2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TGIB2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIV2)
#define IR_MTU2_TCIV2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIV2)
#define DTCE_MTU2_TCIV2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIV2)
#define IER_MTU2_TCIV2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIV2)
#define IPR_MTU2_TCIV2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIV2)
#define IEN_MTU2_TCIV2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIV2)
#define VECT_MTU2_TCIV2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIV2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIU2)
#define IR_MTU2_TCIU2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIU2)
#define DTCE_MTU2_TCIU2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIU2)
#define IER_MTU2_TCIU2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIU2)
#define IPR_MTU2_TCIU2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIU2)
#define IEN_MTU2_TCIU2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIU2)
#define VECT_MTU2_TCIU2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU2_TCIU2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIA3)
#define IR_MTU3_TGIA3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIA3)
#define DTCE_MTU3_TGIA3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIA3)
#define IER_MTU3_TGIA3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIA3)
#define IPR_MTU3_TGIA3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIA3)
#define IEN_MTU3_TGIA3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIA3)
#define VECT_MTU3_TGIA3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIA3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIB3)
#define IR_MTU3_TGIB3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIB3)
#define DTCE_MTU3_TGIB3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIB3)
#define IER_MTU3_TGIB3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIB3)
#define IPR_MTU3_TGIB3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIB3)
#define IEN_MTU3_TGIB3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIB3)
#define VECT_MTU3_TGIB3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIB3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIC3)
#define IR_MTU3_TGIC3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIC3)
#define DTCE_MTU3_TGIC3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIC3)
#define IER_MTU3_TGIC3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIC3)
#define IPR_MTU3_TGIC3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIC3)
#define IEN_MTU3_TGIC3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIC3)
#define VECT_MTU3_TGIC3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGIC3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGID3)
#define IR_MTU3_TGID3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGID3)
#define DTCE_MTU3_TGID3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGID3)
#define IER_MTU3_TGID3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGID3)
#define IPR_MTU3_TGID3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGID3)
#define IEN_MTU3_TGID3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGID3)
#define VECT_MTU3_TGID3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TGID3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TCIV3)
#define IR_MTU3_TCIV3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TCIV3)
#define DTCE_MTU3_TCIV3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TCIV3)
#define IER_MTU3_TCIV3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TCIV3)
#define IPR_MTU3_TCIV3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TCIV3)
#define IEN_MTU3_TCIV3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU3_TCIV3)
#define VECT_MTU3_TCIV3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU3_TCIV3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIA4)
#define IR_MTU4_TGIA4        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIA4)
#define DTCE_MTU4_TGIA4      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIA4)
#define IER_MTU4_TGIA4       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIA4)
#define IPR_MTU4_TGIA4       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIA4)
#define IEN_MTU4_TGIA4       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIA4)
#define VECT_MTU4_TGIA4      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIA4)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIB4)
#define IR_MTU4_TGIB4        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIB4)
#define DTCE_MTU4_TGIB4      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIB4)
#define IER_MTU4_TGIB4       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIB4)
#define IPR_MTU4_TGIB4       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIB4)
#define IEN_MTU4_TGIB4       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIB4)
#define VECT_MTU4_TGIB4      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIB4)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIC4)
#define IR_MTU4_TGIC4        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIC4)
#define DTCE_MTU4_TGIC4      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIC4)
#define IER_MTU4_TGIC4       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIC4)
#define IPR_MTU4_TGIC4       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIC4)
#define IEN_MTU4_TGIC4       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIC4)
#define VECT_MTU4_TGIC4      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGIC4)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGID4)
#define IR_MTU4_TGID4        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGID4)
#define DTCE_MTU4_TGID4      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGID4)
#define IER_MTU4_TGID4       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGID4)
#define IPR_MTU4_TGID4       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGID4)
#define IEN_MTU4_TGID4       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGID4)
#define VECT_MTU4_TGID4      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TGID4)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TCIV4)
#define IR_MTU4_TCIV4        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TCIV4)
#define DTCE_MTU4_TCIV4      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TCIV4)
#define IER_MTU4_TCIV4       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TCIV4)
#define IPR_MTU4_TCIV4       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TCIV4)
#define IEN_MTU4_TCIV4       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU4_TCIV4)
#define VECT_MTU4_TCIV4      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU4_TCIV4)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIU5)
#define IR_MTU5_TGIU5        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIU5)
#define DTCE_MTU5_TGIU5      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIU5)
#define IER_MTU5_TGIU5       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIU5)
#define IPR_MTU5_TGIU5       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIU5)
#define IEN_MTU5_TGIU5       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIU5)
#define VECT_MTU5_TGIU5      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIU5)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIV5)
#define IR_MTU5_TGIV5        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIV5)
#define DTCE_MTU5_TGIV5      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIV5)
#define IER_MTU5_TGIV5       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIV5)
#define IPR_MTU5_TGIV5       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIV5)
#define IEN_MTU5_TGIV5       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIV5)
#define VECT_MTU5_TGIV5      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIV5)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIW5)
#define IR_MTU5_TGIW5        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIW5)
#define DTCE_MTU5_TGIW5      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIW5)
#define IER_MTU5_TGIW5       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIW5)
#define IPR_MTU5_TGIW5       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIW5)
#define IEN_MTU5_TGIW5       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIW5)
#define VECT_MTU5_TGIW5      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU5_TGIW5)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIA6)
#define IR_MTU6_TGIA6        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIA6)
#define DTCE_MTU6_TGIA6      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIA6)
#define IER_MTU6_TGIA6       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIA6)
#define IPR_MTU6_TGIA6       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIA6)
#define IEN_MTU6_TGIA6       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIA6)
#define VECT_MTU6_TGIA6      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIA6)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIB6)
#define IR_MTU6_TGIB6        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIB6)
#define DTCE_MTU6_TGIB6      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIB6)
#define IER_MTU6_TGIB6       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIB6)
#define IPR_MTU6_TGIB6       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIB6)
#define IEN_MTU6_TGIB6       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIB6)
#define VECT_MTU6_TGIB6      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIB6)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIC6)
#define IR_MTU6_TGIC6        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIC6)
#define DTCE_MTU6_TGIC6      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIC6)
#define IER_MTU6_TGIC6       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIC6)
#define IPR_MTU6_TGIC6       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIC6)
#define IEN_MTU6_TGIC6       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIC6)
#define VECT_MTU6_TGIC6      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGIC6)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGID6)
#define IR_MTU6_TGID6        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGID6)
#define DTCE_MTU6_TGID6      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGID6)
#define IER_MTU6_TGID6       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGID6)
#define IPR_MTU6_TGID6       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGID6)
#define IEN_MTU6_TGID6       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGID6)
#define VECT_MTU6_TGID6      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TGID6)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TCIV6)
#define IR_MTU6_TCIV6        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TCIV6)
#define DTCE_MTU6_TCIV6      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TCIV6)
#define IER_MTU6_TCIV6       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TCIV6)
#define IPR_MTU6_TCIV6       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TCIV6)
#define IEN_MTU6_TCIV6       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU6_TCIV6)
#define VECT_MTU6_TCIV6      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU6_TCIV6)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIA7)
#define IR_MTU7_TGIA7        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIA7)
#define DTCE_MTU7_TGIA7      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIA7)
#define IER_MTU7_TGIA7       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIA7)
#define IPR_MTU7_TGIA7       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIA7)
#define IEN_MTU7_TGIA7       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIA7)
#define VECT_MTU7_TGIA7      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIA7)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIB7)
#define IR_MTU7_TGIB7        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIB7)
#define DTCE_MTU7_TGIB7      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIB7)
#define IER_MTU7_TGIB7       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIB7)
#define IPR_MTU7_TGIB7       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIB7)
#define IEN_MTU7_TGIB7       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIB7)
#define VECT_MTU7_TGIB7      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIB7)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIC7)
#define IR_MTU7_TGIC7        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIC7)
#define DTCE_MTU7_TGIC7      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIC7)
#define IER_MTU7_TGIC7       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIC7)
#define IPR_MTU7_TGIC7       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIC7)
#define IEN_MTU7_TGIC7       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIC7)
#define VECT_MTU7_TGIC7      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGIC7)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGID7)
#define IR_MTU7_TGID7        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGID7)
#define DTCE_MTU7_TGID7      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGID7)
#define IER_MTU7_TGID7       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGID7)
#define IPR_MTU7_TGID7       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGID7)
#define IEN_MTU7_TGID7       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGID7)
#define VECT_MTU7_TGID7      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TGID7)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TCIV7)
#define IR_MTU7_TCIV7        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TCIV7)
#define DTCE_MTU7_TCIV7      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TCIV7)
#define IER_MTU7_TCIV7       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TCIV7)
#define IPR_MTU7_TCIV7       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TCIV7)
#define IEN_MTU7_TCIV7       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU7_TCIV7)
#define VECT_MTU7_TCIV7      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU7_TCIV7)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIA8)
#define IR_MTU8_TGIA8        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIA8)
#define DTCE_MTU8_TGIA8      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIA8)
#define IER_MTU8_TGIA8       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIA8)
#define IPR_MTU8_TGIA8       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIA8)
#define IEN_MTU8_TGIA8       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIA8)
#define VECT_MTU8_TGIA8      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIA8)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIB8)
#define IR_MTU8_TGIB8        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIB8)
#define DTCE_MTU8_TGIB8      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIB8)
#define IER_MTU8_TGIB8       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIB8)
#define IPR_MTU8_TGIB8       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIB8)
#define IEN_MTU8_TGIB8       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIB8)
#define VECT_MTU8_TGIB8      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIB8)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIC8)
#define IR_MTU8_TGIC8        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIC8)
#define DTCE_MTU8_TGIC8      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIC8)
#define IER_MTU8_TGIC8       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIC8)
#define IPR_MTU8_TGIC8       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIC8)
#define IEN_MTU8_TGIC8       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIC8)
#define VECT_MTU8_TGIC8      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGIC8)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGID8)
#define IR_MTU8_TGID8        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGID8)
#define DTCE_MTU8_TGID8      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGID8)
#define IER_MTU8_TGID8       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGID8)
#define IPR_MTU8_TGID8       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGID8)
#define IEN_MTU8_TGID8       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGID8)
#define VECT_MTU8_TGID8      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TGID8)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TCIV8)
#define IR_MTU8_TCIV8        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TCIV8)
#define DTCE_MTU8_TCIV8      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TCIV8)
#define IER_MTU8_TCIV8       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TCIV8)
#define IPR_MTU8_TCIV8       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TCIV8)
#define IEN_MTU8_TCIV8       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_MTU8_TCIV8)
#define VECT_MTU8_TCIV8      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_MTU8_TCIV8)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_EPTPC_IPLS)
#define IR_EPTPC_IPLS        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_EPTPC_IPLS)
#define DTCE_EPTPC_IPLS      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_EPTPC_IPLS)
#define IER_EPTPC_IPLS       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_EPTPC_IPLS)
#define IPR_EPTPC_IPLS       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_EPTPC_IPLS)
#define IEN_EPTPC_IPLS       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_EPTPC_IPLS)
#define VECT_EPTPC_IPLS      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_EPTPC_IPLS)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESRDY)
#define IR_AES_AESRDY        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESRDY)
#define DTCE_AES_AESRDY      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESRDY)
#define IER_AES_AESRDY       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_AES_AESRDY)
#define IPR_AES_AESRDY       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESRDY)
#define IEN_AES_AESRDY       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_AES_AESRDY)
#define VECT_AES_AESRDY      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESRDY)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESEND)
#define IR_AES_AESEND        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESEND)
#define DTCE_AES_AESEND      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESEND)
#define IER_AES_AESEND       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_AES_AESEND)
#define IPR_AES_AESEND       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESEND)
#define IEN_AES_AESEND       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_AES_AESEND)
#define VECT_AES_AESEND      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_AES_AESEND)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIA0)
#define IR_GPT0_GTCIA0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIA0)
#define DTCE_GPT0_GTCIA0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIA0)
#define IER_GPT0_GTCIA0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIA0)
#define IPR_GPT0_GTCIA0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIA0)
#define IEN_GPT0_GTCIA0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIA0)
#define VECT_GPT0_GTCIA0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIA0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIB0)
#define IR_GPT0_GTCIB0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIB0)
#define DTCE_GPT0_GTCIB0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIB0)
#define IER_GPT0_GTCIB0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIB0)
#define IPR_GPT0_GTCIB0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIB0)
#define IEN_GPT0_GTCIB0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIB0)
#define VECT_GPT0_GTCIB0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIB0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIC0)
#define IR_GPT0_GTCIC0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIC0)
#define DTCE_GPT0_GTCIC0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIC0)
#define IER_GPT0_GTCIC0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIC0)
#define IPR_GPT0_GTCIC0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIC0)
#define IEN_GPT0_GTCIC0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIC0)
#define VECT_GPT0_GTCIC0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIC0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCID0)
#define IR_GPT0_GTCID0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCID0)
#define DTCE_GPT0_GTCID0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCID0)
#define IER_GPT0_GTCID0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCID0)
#define IPR_GPT0_GTCID0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCID0)
#define IEN_GPT0_GTCID0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCID0)
#define VECT_GPT0_GTCID0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCID0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GDTE0)
#define IR_GPT0_GDTE0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GDTE0)
#define DTCE_GPT0_GDTE0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GDTE0)
#define IER_GPT0_GDTE0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GDTE0)
#define IPR_GPT0_GDTE0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GDTE0)
#define IEN_GPT0_GDTE0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GDTE0)
#define VECT_GPT0_GDTE0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GDTE0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIE0)
#define IR_GPT0_GTCIE0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIE0)
#define DTCE_GPT0_GTCIE0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIE0)
#define IER_GPT0_GTCIE0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIE0)
#define IPR_GPT0_GTCIE0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIE0)
#define IEN_GPT0_GTCIE0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIE0)
#define VECT_GPT0_GTCIE0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIE0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIF0)
#define IR_GPT0_GTCIF0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIF0)
#define DTCE_GPT0_GTCIF0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIF0)
#define IER_GPT0_GTCIF0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIF0)
#define IPR_GPT0_GTCIF0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIF0)
#define IEN_GPT0_GTCIF0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIF0)
#define VECT_GPT0_GTCIF0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIF0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIV0)
#define IR_GPT0_GTCIV0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIV0)
#define DTCE_GPT0_GTCIV0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIV0)
#define IER_GPT0_GTCIV0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIV0)
#define IPR_GPT0_GTCIV0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIV0)
#define IEN_GPT0_GTCIV0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIV0)
#define VECT_GPT0_GTCIV0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIV0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIU0)
#define IR_GPT0_GTCIU0        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIU0)
#define DTCE_GPT0_GTCIU0      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIU0)
#define IER_GPT0_GTCIU0       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIU0)
#define IPR_GPT0_GTCIU0       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIU0)
#define IEN_GPT0_GTCIU0       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIU0)
#define VECT_GPT0_GTCIU0      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT0_GTCIU0)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIN)
#define IR_GPTA_ETGIN        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIN)
#define DTCE_GPTA_ETGIN      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIN)
#define IER_GPTA_ETGIN       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIN)
#define IPR_GPTA_ETGIN       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIN)
#define IEN_GPTA_ETGIN       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIN)
#define VECT_GPTA_ETGIN      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIN)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIP)
#define IR_GPTA_ETGIP        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIP)
#define DTCE_GPTA_ETGIP      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIP)
#define IER_GPTA_ETGIP       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIP)
#define IPR_GPTA_ETGIP       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIP)
#define IEN_GPTA_ETGIP       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIP)
#define VECT_GPTA_ETGIP      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPTA_ETGIP)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIA1)
#define IR_GPT1_GTCIA1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIA1)
#define DTCE_GPT1_GTCIA1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIA1)
#define IER_GPT1_GTCIA1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIA1)
#define IPR_GPT1_GTCIA1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIA1)
#define IEN_GPT1_GTCIA1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIA1)
#define VECT_GPT1_GTCIA1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIA1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIB1)
#define IR_GPT1_GTCIB1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIB1)
#define DTCE_GPT1_GTCIB1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIB1)
#define IER_GPT1_GTCIB1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIB1)
#define IPR_GPT1_GTCIB1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIB1)
#define IEN_GPT1_GTCIB1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIB1)
#define VECT_GPT1_GTCIB1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIB1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIC1)
#define IR_GPT1_GTCIC1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIC1)
#define DTCE_GPT1_GTCIC1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIC1)
#define IER_GPT1_GTCIC1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIC1)
#define IPR_GPT1_GTCIC1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIC1)
#define IEN_GPT1_GTCIC1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIC1)
#define VECT_GPT1_GTCIC1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIC1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCID1)
#define IR_GPT1_GTCID1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCID1)
#define DTCE_GPT1_GTCID1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCID1)
#define IER_GPT1_GTCID1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCID1)
#define IPR_GPT1_GTCID1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCID1)
#define IEN_GPT1_GTCID1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCID1)
#define VECT_GPT1_GTCID1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCID1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GDTE1)
#define IR_GPT1_GDTE1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GDTE1)
#define DTCE_GPT1_GDTE1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GDTE1)
#define IER_GPT1_GDTE1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GDTE1)
#define IPR_GPT1_GDTE1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GDTE1)
#define IEN_GPT1_GDTE1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GDTE1)
#define VECT_GPT1_GDTE1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GDTE1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIE1)
#define IR_GPT1_GTCIE1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIE1)
#define DTCE_GPT1_GTCIE1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIE1)
#define IER_GPT1_GTCIE1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIE1)
#define IPR_GPT1_GTCIE1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIE1)
#define IEN_GPT1_GTCIE1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIE1)
#define VECT_GPT1_GTCIE1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIE1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIF1)
#define IR_GPT1_GTCIF1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIF1)
#define DTCE_GPT1_GTCIF1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIF1)
#define IER_GPT1_GTCIF1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIF1)
#define IPR_GPT1_GTCIF1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIF1)
#define IEN_GPT1_GTCIF1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIF1)
#define VECT_GPT1_GTCIF1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIF1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIV1)
#define IR_GPT1_GTCIV1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIV1)
#define DTCE_GPT1_GTCIV1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIV1)
#define IER_GPT1_GTCIV1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIV1)
#define IPR_GPT1_GTCIV1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIV1)
#define IEN_GPT1_GTCIV1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIV1)
#define VECT_GPT1_GTCIV1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIV1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIU1)
#define IR_GPT1_GTCIU1        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIU1)
#define DTCE_GPT1_GTCIU1      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIU1)
#define IER_GPT1_GTCIU1       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIU1)
#define IPR_GPT1_GTCIU1       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIU1)
#define IEN_GPT1_GTCIU1       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIU1)
#define VECT_GPT1_GTCIU1      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT1_GTCIU1)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIA2)
#define IR_GPT2_GTCIA2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIA2)
#define DTCE_GPT2_GTCIA2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIA2)
#define IER_GPT2_GTCIA2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIA2)
#define IPR_GPT2_GTCIA2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIA2)
#define IEN_GPT2_GTCIA2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIA2)
#define VECT_GPT2_GTCIA2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIA2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIB2)
#define IR_GPT2_GTCIB2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIB2)
#define DTCE_GPT2_GTCIB2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIB2)
#define IER_GPT2_GTCIB2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIB2)
#define IPR_GPT2_GTCIB2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIB2)
#define IEN_GPT2_GTCIB2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIB2)
#define VECT_GPT2_GTCIB2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIB2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIC2)
#define IR_GPT2_GTCIC2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIC2)
#define DTCE_GPT2_GTCIC2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIC2)
#define IER_GPT2_GTCIC2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIC2)
#define IPR_GPT2_GTCIC2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIC2)
#define IEN_GPT2_GTCIC2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIC2)
#define VECT_GPT2_GTCIC2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIC2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCID2)
#define IR_GPT2_GTCID2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCID2)
#define DTCE_GPT2_GTCID2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCID2)
#define IER_GPT2_GTCID2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCID2)
#define IPR_GPT2_GTCID2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCID2)
#define IEN_GPT2_GTCID2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCID2)
#define VECT_GPT2_GTCID2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCID2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GDTE2)
#define IR_GPT2_GDTE2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GDTE2)
#define DTCE_GPT2_GDTE2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GDTE2)
#define IER_GPT2_GDTE2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GDTE2)
#define IPR_GPT2_GDTE2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GDTE2)
#define IEN_GPT2_GDTE2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GDTE2)
#define VECT_GPT2_GDTE2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GDTE2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIE2)
#define IR_GPT2_GTCIE2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIE2)
#define DTCE_GPT2_GTCIE2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIE2)
#define IER_GPT2_GTCIE2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIE2)
#define IPR_GPT2_GTCIE2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIE2)
#define IEN_GPT2_GTCIE2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIE2)
#define VECT_GPT2_GTCIE2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIE2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIF2)
#define IR_GPT2_GTCIF2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIF2)
#define DTCE_GPT2_GTCIF2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIF2)
#define IER_GPT2_GTCIF2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIF2)
#define IPR_GPT2_GTCIF2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIF2)
#define IEN_GPT2_GTCIF2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIF2)
#define VECT_GPT2_GTCIF2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIF2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIV2)
#define IR_GPT2_GTCIV2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIV2)
#define DTCE_GPT2_GTCIV2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIV2)
#define IER_GPT2_GTCIV2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIV2)
#define IPR_GPT2_GTCIV2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIV2)
#define IEN_GPT2_GTCIV2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIV2)
#define VECT_GPT2_GTCIV2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIV2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIU2)
#define IR_GPT2_GTCIU2        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIU2)
#define DTCE_GPT2_GTCIU2      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIU2)
#define IER_GPT2_GTCIU2       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIU2)
#define IPR_GPT2_GTCIU2       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIU2)
#define IEN_GPT2_GTCIU2       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIU2)
#define VECT_GPT2_GTCIU2      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT2_GTCIU2)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIA3)
#define IR_GPT3_GTCIA3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIA3)
#define DTCE_GPT3_GTCIA3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIA3)
#define IER_GPT3_GTCIA3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIA3)
#define IPR_GPT3_GTCIA3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIA3)
#define IEN_GPT3_GTCIA3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIA3)
#define VECT_GPT3_GTCIA3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIA3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIB3)
#define IR_GPT3_GTCIB3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIB3)
#define DTCE_GPT3_GTCIB3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIB3)
#define IER_GPT3_GTCIB3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIB3)
#define IPR_GPT3_GTCIB3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIB3)
#define IEN_GPT3_GTCIB3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIB3)
#define VECT_GPT3_GTCIB3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIB3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIC3)
#define IR_GPT3_GTCIC3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIC3)
#define DTCE_GPT3_GTCIC3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIC3)
#define IER_GPT3_GTCIC3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIC3)
#define IPR_GPT3_GTCIC3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIC3)
#define IEN_GPT3_GTCIC3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIC3)
#define VECT_GPT3_GTCIC3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIC3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCID3)
#define IR_GPT3_GTCID3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCID3)
#define DTCE_GPT3_GTCID3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCID3)
#define IER_GPT3_GTCID3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCID3)
#define IPR_GPT3_GTCID3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCID3)
#define IEN_GPT3_GTCID3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCID3)
#define VECT_GPT3_GTCID3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCID3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GDTE3)
#define IR_GPT3_GDTE3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GDTE3)
#define DTCE_GPT3_GDTE3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GDTE3)
#define IER_GPT3_GDTE3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GDTE3)
#define IPR_GPT3_GDTE3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GDTE3)
#define IEN_GPT3_GDTE3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GDTE3)
#define VECT_GPT3_GDTE3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GDTE3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIE3)
#define IR_GPT3_GTCIE3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIE3)
#define DTCE_GPT3_GTCIE3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIE3)
#define IER_GPT3_GTCIE3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIE3)
#define IPR_GPT3_GTCIE3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIE3)
#define IEN_GPT3_GTCIE3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIE3)
#define VECT_GPT3_GTCIE3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIE3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIF3)
#define IR_GPT3_GTCIF3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIF3)
#define DTCE_GPT3_GTCIF3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIF3)
#define IER_GPT3_GTCIF3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIF3)
#define IPR_GPT3_GTCIF3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIF3)
#define IEN_GPT3_GTCIF3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIF3)
#define VECT_GPT3_GTCIF3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIF3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIV3)
#define IR_GPT3_GTCIV3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIV3)
#define DTCE_GPT3_GTCIV3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIV3)
#define IER_GPT3_GTCIV3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIV3)
#define IPR_GPT3_GTCIV3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIV3)
#define IEN_GPT3_GTCIV3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIV3)
#define VECT_GPT3_GTCIV3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIV3)
#endif

#if BSP_PRV_VALID_MAP_INT(A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIU3)
#define IR_GPT3_GTCIU3        BSP_PRV_IR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIU3)
#define DTCE_GPT3_GTCIU3      BSP_PRV_DTCE(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIU3)
#define IER_GPT3_GTCIU3       BSP_PRIV_CALC_IER_REG(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIU3)
#define IPR_GPT3_GTCIU3       BSP_PRV_IPR(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIU3)
#define IEN_GPT3_GTCIU3       BSP_PRV_IEN(BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIU3)
#define VECT_GPT3_GTCIU3      BSP_PRV_VECT(BSP_PRV_A, BSP_MAPPED_INT_CFG_A_VECT_GPT3_GTCIU3)
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
void bsp_mapped_interrupt_open(void); //r_bsp internal function. DO NOT CALL.

#endif /* MCU_MAPPED_INTERRUPTS_H */

