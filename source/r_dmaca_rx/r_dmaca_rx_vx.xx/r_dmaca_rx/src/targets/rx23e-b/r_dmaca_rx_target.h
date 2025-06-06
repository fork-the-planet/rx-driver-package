/***********************************************************************************************************************
* Copyright (c) 2023 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dmaca_rx_target.h
* Description  : Functions for DMACA driver
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 29.05.2023 1.00    First Release for RX23E-B.
*                              Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*         : 15.03.2025 3.41    Updated disclaimer.
*******************************************************************************/
#ifndef DMACA_RX_TARGET_H
#define DMACA_RX_TARGET_H

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* Number of activation sources */
/* #define DMACA_NUM_INTERRUPT_SRC         (32) */

/* Maximum value of 16bit count value (normal transfer mode) */
#define DMACA_MAX_16BITS_COUNT_VAL_A    (65535)
/* Maximum value of 16bit count value (repeat or block transfer mode) */
#define DMACA_MAX_16BITS_COUNT_VAL_B    (65536)
/* Maximum value of 10bit count value */
#define DMACA_MAX_10BITS_COUNT_VAL      (1024)
/* Minimum of count value and block size */
#define DMACA_MIN_COUNT_VAL             (1)

/* Definition of number of DMACA channel */
#define DMACA_NUM_CHANNELS              (4)

/* DMACA source address must be in 0x00000000h to 0x0FFFFFFF and 0xF0000000 to 0xFFFFFFFF. */
#define DMACA_INVALID_SRC_ADDR_MASK     (0xf0000000u)
/* DMACA destination address must be in 0x00000000h to 0x0FFFFFFF and 0xF0000000 to 0xFFFFFFFF. */
#define DMACA_INVALID_DES_ADDR_MASK     (0xf0000000u)

/* DMACA channel0 offset address must be in 0x00000000h to 0x00FFFFFF and 0xFF000000 to 0xFFFFFFFF. */
#define DMAC0_INVALID_OFFSET_VALUE_MASK (0xff000000u)

/* DMACA lower bits of transfer count bit mask */
#define DMACA_INVALID_LOWER_BIT_MASK    (0x0000ffffu)

/* ---- DMACA register base address ---- */
#define DMACA_BASE_ADDR        ((uint32_t)&DMAC0)

/* DMACA ch4 Interrupt request bit mask */
#define DMACA_DMIS4_BIT_MASK   (0x10u)
/* DMACA ch5 Interrupt request bit mask */
#define DMACA_DMIS5_BIT_MASK   (0x20u)
/* DMACA ch6 Interrupt request bit mask */
#define DMACA_DMIS6_BIT_MASK   (0x40u)
/* DMACA ch7 Interrupt request bit mask */
#define DMACA_DMIS7_BIT_MASK   (0x80u)

/* ---- DMACA register address offset ---- */
/* DMA Source Address Register address offset */
#define DMACA_DMSAR_OFST   (0x00u)
/* DMA Destination Address Register address offset */
#define DMACA_DMDAR_OFST   (0x04u)
/* DMA Transfer Count Register address offset */
#define DMACA_DMCRA_OFST   (0x08u)
/* DMA Block Transfer Count Register address offset */
#define DMACA_DMCRB_OFST   (0x0Cu)
/* DMA Transfer Mode Register address offset */
#define DMACA_DMTMD_OFST   (0x10u)
/* DMA Interrupt Setting Register address offset */
#define DMACA_DMINT_OFST   (0x13u)
/* DMA Address Mode Register address offset */
#define DMACA_DMAMD_OFST   (0x14u)
/* DMA Offset Register address offset */
#define DMACA_DMOFR_OFST   (0x18u)
/* DMA Transfer Enable Register address offset */
#define DMACA_DMCNT_OFST   (0x1Cu)
/* DMA Software Start Register address offset */
#define DMACA_DMREQ_OFST   (0x1Du)
/* DMA Status Register address offset */
#define DMACA_DMSTS_OFST   (0x1Eu)
/* DMA Activation Source Flag Control Register address offset */
#define DMACA_DMCSL_OFST   (0x1Fu)
/* DMACA Module Activation Register address offset */
#define DMACA_DMAST_OFST   (0x200u)
/* DMAC74 Interrupt Status Monitor Register address offset */
#define DMACA_DMIST_OFST   (0x204u)


/* ---- Registers and bits for ICU ---- */
/* DMACA Activation Request Select Register */
#define ICU_DMRSR(dmaca_channel)       (*g_icu_dmrsr[(dmaca_channel)])

/* ---- Registers and bits for DMACA ---- */
/* DMA Source Address Register */
#define DMACA_DMSAR(dmaca_channel)     (*(volatile void R_BSP_EVENACCESS_SFR   **)(DMACA_BASE_ADDR + DMACA_DMSAR_OFST \
    + (0x40 * (dmaca_channel))))
/* DMA Destination Address Register */
#define DMACA_DMDAR(dmaca_channel)     (*(volatile void R_BSP_EVENACCESS_SFR   **)(DMACA_BASE_ADDR + DMACA_DMDAR_OFST \
    + (0x40 * (dmaca_channel))))
/* DMA Transfer Count Register */
#define DMACA_DMCRA(dmaca_channel)     (*(volatile uint32_t R_BSP_EVENACCESS_SFR *)(DMACA_BASE_ADDR + DMACA_DMCRA_OFST \
                                                                                + (0x40 * (dmaca_channel))))
/* DMA Block Transfer Count Register */
#define DMACA_DMCRB(dmaca_channel)     (*(volatile uint16_t R_BSP_EVENACCESS_SFR *)(DMACA_BASE_ADDR + DMACA_DMCRB_OFST \
                                                                                + (0x40 * (dmaca_channel))))
/* DMA Transfer Mode Register */
#define DMACA_DMTMD(dmaca_channel)     (*(volatile uint16_t R_BSP_EVENACCESS_SFR *)(DMACA_BASE_ADDR + DMACA_DMTMD_OFST \
                                                                                + (0x40 * (dmaca_channel))))
/* DMA Interrupt Setting Register */
#define DMACA_DMINT(dmaca_channel)     (*(volatile uint8_t R_BSP_EVENACCESS_SFR  *)(DMACA_BASE_ADDR + DMACA_DMINT_OFST \
                                                                                + (0x40 * (dmaca_channel))))
/* DMA Address Mode Register */
#define DMACA_DMAMD(dmaca_channel)     (*(volatile uint16_t R_BSP_EVENACCESS_SFR *)(DMACA_BASE_ADDR + DMACA_DMAMD_OFST \
                                                                                + (0x40 * (dmaca_channel))))
/* DMA Offset Register (only for DMACA channe0)*/
#define DMACA_DMOFR                       (*(volatile uint32_t R_BSP_EVENACCESS_SFR *)(DMACA_BASE_ADDR + DMACA_DMOFR_OFST))
/* DMA Transfer Enable Register */
#define DMACA_DMCNT(dmaca_channel)     (*(volatile uint8_t R_BSP_EVENACCESS_SFR  *)(DMACA_BASE_ADDR + DMACA_DMCNT_OFST \
                                                                                + (0x40 * (dmaca_channel))))
/* DMA Software Start Register */
#define DMACA_DMREQ(dmaca_channel)     (*(volatile uint8_t R_BSP_EVENACCESS_SFR  *)(DMACA_BASE_ADDR + DMACA_DMREQ_OFST \
                                                                                + (0x40 * (dmaca_channel))))
/* DMA Status Register */
#define DMACA_DMSTS(dmaca_channel)     (*(volatile uint8_t R_BSP_EVENACCESS_SFR  *)(DMACA_BASE_ADDR + DMACA_DMSTS_OFST \
                                                                                + (0x40 * (dmaca_channel))))
/* DMA Activation Source Flag Control Register */
#define DMACA_DMCSL(dmaca_channel)     (*(volatile uint8_t R_BSP_EVENACCESS_SFR  *)(DMACA_BASE_ADDR + DMACA_DMCSL_OFST \
                                                                                + (0x40 * (dmaca_channel))))
/* DMACA Module Activation Register (for DMACA All channel) */
#define DMACA_DMAST                       (*(volatile uint8_t R_BSP_EVENACCESS_SFR  *)(DMACA_BASE_ADDR + DMACA_DMAST_OFST))



#endif /* DMACA_RX_TARGET_H */

/* End of File */

