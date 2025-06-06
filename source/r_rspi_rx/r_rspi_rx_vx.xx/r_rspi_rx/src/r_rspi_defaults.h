/***********************************************************************************************************************
* Copyright (c) 2013 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_rspi_defaults.h
* Description  : Definition of default settings used for the RSPI driver
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 25.10.2013 1.00     First Release
*         : 30.09.2016 1.50     Added #define RSPI_SPDCR2_DEF.
*         : 31.07.2017 1.70     Supported RX65N-2MB, RX130-512KB.
*         : 30.06.2021 3.01     Supported RX671.
*                               Fixed bug. Set the RSPCK auto-stop function enable bit(SPCR2.SCKASE) to ensure RSPI can 
*                               communication normally when it is in high speed reception.
*         : 31.12.2021 3.04     Supported RX660.
*         : 31.03.2023 3.10     Added support for RX26T.
*                               Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*         : 15.03.2025 3.51     Updated disclaimer.
***********************************************************************************************************************/
#ifndef R_RSPI_DEFS_H
#define R_RSPI_DEFS_H

/***********************************************************************************************************************
* Default RSPI register settings section. One set of defaults provided for all channels.
* Make sure to understand the operation of these registers if making changes.
***********************************************************************************************************************/
/* RSPI Control Register (SPCR) */
#define RSPI_SPCR_SPMS_DEF     (0x00) /* 0: SPI mode operation (4-wire). Uses RSPI generated slave select. */
#define RSPI_SPCR_TXMD_DEF     (0x00) /* 0: Full-duplex synchronous serial communications. */
#define RSPI_SPCR_MODFEN_DEF   (0x00) /* 0: Mode fault error detection disabled. */
#define RSPI_SPCR_MSTR_DEF     (0x08) /* 1: Master mode. */
#define RSPI_SPCR_SPEIE_DEF    (0x00) /* 0: Error Interrupt disabled. */
#define RSPI_SPCR_SPTIE_DEF    (0x00) /* 0: Transmit Interrupt disabled */
#define RSPI_SPCR_SPE_DEF      (0x00) /* 0: RSPI operation disabled. */
#define RSPI_SPCR_SPRIE_DEF    (0x00) /* 0: Receive Interrupt disabled. */

#define RSPI_SPCR_DEF   (RSPI_SPCR_SPMS_DEF | RSPI_SPCR_TXMD_DEF  | RSPI_SPCR_MODFEN_DEF\
                        | RSPI_SPCR_MSTR_DEF| RSPI_SPCR_SPEIE_DEF | RSPI_SPCR_SPTIE_DEF \
                        | RSPI_SPCR_SPE_DEF | RSPI_SPCR_SPRIE_DEF )

/*RSPI Slave Select Polarity Register (SSLP) */
#define RSPI_SSLP_SSL0P_DEF    (0x00) /* 0 = active low. 1 = active high. */
#define RSPI_SSLP_SSL1P_DEF    (0x00)
#define RSPI_SSLP_SSL2P_DEF    (0x00)
#define RSPI_SSLP_SSL3P_DEF    (0x00)

#define RSPI_SSLP_DEF   (RSPI_SSLP_SSL0P_DEF | RSPI_SSLP_SSL1P_DEF | RSPI_SSLP_SSL2P_DEF\
                        |RSPI_SSLP_SSL3P_DEF )

/* RSPI Pin Control Register (SPPCR) */
#define RSPI_SPPCR_SPLP_DEF  (0x00) /* 0: Normal mode. 1: Loop-back mode (reversed transmit data = receive data) */
#define RSPI_SPPCR_SPLP2_DEF (0x00) /* 0: Normal mode. 1: Loop-back mode (transmit data = receive data) */
#define RSPI_SPPCR_MOIFV_DEF (0x00) /* 0: MOSI pin idles low. 1: MOSI pin idles high. */
#define RSPI_SPPCR_MOIFE_DEF (0x00) /* 0: MOSI pin idles at final previous data. 1: MOSI pin idles at MOIFV. */

#define RSPI_SPPCR_DEF  (RSPI_SPPCR_SPLP_DEF  | RSPI_SPPCR_SPLP2_DEF | RSPI_SPPCR_MOIFV_DEF\
                        |RSPI_SPPCR_MOIFE_DEF )

/* RSPI Sequence Control Register (SPSCR) */
#define RSPI_SPSCR_DEF  (0x00)

/* RSPI Bit Rate Register (SPBR) */
#define RSPI_SPBR_DEF         (0x01)  /* 0x00: Maximum bit rate setting. */

/* RSPI Data Control Register (SPDCR) */
#define RSPI_SPDCR_SPFC_DEF   (0x00)  /* 0: Transfer 1 frame at a time */
#define RSPI_SPDCR_SPRDTD_DEF (0x00)  /* 0: read SPDR values from the RX buffer. */
#define RSPI_SPDCR_SPLW_DEF   (0x20)  /* 1: SPDR is accessed in longwords (32 bits) */
#define RSPI_SPDCR_DEF        (RSPI_SPDCR_SPFC_DEF | RSPI_SPDCR_SPRDTD_DEF | RSPI_SPDCR_SPLW_DEF)

/* RSPI Clock Delay Register (SPCKD) */
#define RSPI_SPCKD_DEF   (0x00)

/* RSPI Slave Select Negation Delay Register (SSLND) */
#define RSPI_SSLND_DEF   (0x00)

/* RSPI Next-Access Delay Register (SPND) */
#define RSPI_SPND_DEF   (0x00)

/* RSPI Control Register 2 (SPCR2) */
#define RSPI_SPCR2_SPPE_DEF   (0x00)     /* 0: No parity */
#define RSPI_SPCR2_SPOE_DEF   (0x00)     /* 0: Even parity (ignored) */
#define RSPI_SPCR2_SPIIE_DEF  (0x00)     /* 0: Disable Idle interrupt */
#define RSPI_SPCR2_PTE_DEF    (0x00)     /* 0: Disable parity self diagnostic. */
#define RSPI_SPCR2_SCKASE_DEF (0x00)     /* 0: Disables the RSPCK auto-stop function */
#if (!defined(BSP_MCU_RX110) && !defined(BSP_MCU_RX111) && !defined(BSP_MCU_RX113))
    #define RSPI_SPCR2_SCKASE_ENABLE (0x10) /* 1: Enables the RSPCK auto-stop function */
#else
    #define RSPI_SPCR2_SCKASE_ENABLE (0x00)
#endif
#define RSPI_SPCR2_DEF          (RSPI_SPCR2_SPPE_DEF | RSPI_SPCR2_SPOE_DEF  | RSPI_SPCR2_SPIIE_DEF\
                                | RSPI_SPCR2_PTE_DEF | RSPI_SPCR2_SCKASE_DEF)
#define RSPI_SPCR2_HIGH_SPEED   (RSPI_SPCR2_SPPE_DEF | RSPI_SPCR2_SPOE_DEF  | RSPI_SPCR2_SPIIE_DEF\
                                | RSPI_SPCR2_PTE_DEF | RSPI_SPCR2_SCKASE_ENABLE)

/* RSPI Command Registers 0 to 7 (SPCMD0 to SPCMD7). One set of defaults supported */
#define RSPI_SPCMD_CPHA_DEF   (0x0000)  /* 0: Data sampling on odd edge, data variation on even edge. */
#define RSPI_SPCMD_CPOL_DEF   (0x0000)  /* 0: RSPCK is low when idle. */
#define RSPI_SPCMD_BRDV_DEF   (0x0000)  /* 0: Base bit-rate divisor = 1. */
#define RSPI_SPCMD_SSLA_DEF   (0x0000)  /* 0: Slave select 0. Will be controlled by application. */
#define RSPI_SPCMD_SSLKP_DEF  (0x0000)  /* 0: SSL signal negated at end of transfer. */
#define RSPI_SPCMD_SPB_DEF    (0x0400)  /* b11 to b8 SPB[3:0] 0100 to 0111 = 8 bits data length */
#define RSPI_SPCMD_LSBF_DEF   (0x0000)  /* 0: MSB first. */
#define RSPI_SPCMD_SPNDEN_DEF (0x0000)  /* 0: A next-access delay of 1 RSPCK + 2 PCLK. */
#define RSPI_SPCMD_SLNDEN_DEF (0x0000)  /* 0: An SSL negation delay of 1 RSPCK. */
#define RSPI_SPCMD_SCKDEN_DEF (0x0000)  /* 0: An RSPCK delay of 1 RSPCK. */

#define RSPI_SPCMD_DEF      (RSPI_SPCMD_CPHA_DEF  | RSPI_SPCMD_CPOL_DEF | RSPI_SPCMD_BRDV_DEF | RSPI_SPCMD_SSLA_DEF\
                            |RSPI_SPCMD_SSLKP_DEF | RSPI_SPCMD_SPB_DEF  | RSPI_SPCMD_LSBF_DEF | RSPI_SPCMD_SPNDEN_DEF\
                            |RSPI_SPCMD_SLNDEN_DEF| RSPI_SPCMD_SCKDEN_DEF )

/* RSPI Data Control Register 2 (SPDCR2) */
#define RSPI_SPDCR2_DEF       (0x00)

/* RSPI Control Register 3 (SPCR3) */
#define RSPI_SPCR3_RXMD_DEF    (0x00) /* 0: Full-duplex or transmit-only simplex
                                       *    communications (enables the transmitter) */
#define RSPI_SPCR3_SCKDDIS_DEF (0x00) /* 0: Does not insert delays between data bytes during burst transfer */
#define RSPI_SPCR3_SPCIE_DEF   (0x00) /* 0: Disables the generation of communication end interrupt requests */

#define RSPI_SPCR3_DEF         (RSPI_SPCR3_RXMD_DEF | RSPI_SPCR3_SCKDDIS_DEF | RSPI_SPCR3_SPCIE_DEF)

#endif /* R_RSPI_DEFS_H_ */
