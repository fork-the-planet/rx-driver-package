/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_bitdefine.h
 * Version      : 1.44
 * Description  : USB signal control code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 01.03.2025 1.44 Change Disclaimer.
 ***********************************************************************************************************************/
#ifndef R_USB_BITDEFINE_H
#define R_USB_BITDEFINE_H

/*****************************************************************************
 Structure Types
 ******************************************************************************/

/* USB0 & USBHS Register definition */

/* System Configuration Control Register */
#define USB_SCKE                (0x0400u)   /* b10: USB clock enable */
#define USB_CNEN                (0x0100u)   /* b8: Single end receiver */
#define USB_HSE                 (0x0080u)   /* b7: Hi-speed enable */
#define USB_DCFM                (0x0040u)   /* b6: Function select */
#define USB_DRPD                (0x0020u)   /* b5: D+/D- pull down control */
#define USB_DPRPU               (0x0010u)   /* b4: D+ pull up control */
#define USB_DMRPU               (0x0008u)   /* b3: D- pull up control *//* For low speed */
#define USB_USBE                (0x0001u)   /* b0: USB module enable */

/* CPU Bus Wait Register */
#define USB_BWAIT               (0x000Fu)   /* b3-0: Bus wait bit */
#define USB_BWAIT_15            (0x000Fu)   /* 15 wait (access cycle 17) */
#define USB_BWAIT_14            (0x000Eu)   /* 14 wait (access cycle 16) */
#define USB_BWAIT_13            (0x000Du)   /* 13 wait (access cycle 15) */
#define USB_BWAIT_12            (0x000Cu)   /* 12 wait (access cycle 14) */
#define USB_BWAIT_11            (0x000Bu)   /* 11 wait (access cycle 13) */
#define USB_BWAIT_10            (0x000Au)   /* 10 wait (access cycle 12) */
#define USB_BWAIT_9             (0x0009u)   /*  9 wait (access cycle 11) */
#define USB_BWAIT_8             (0x0008u)   /*  8 wait (access cycle 10) */
#define USB_BWAIT_7             (0x0007u)   /*  7 wait (access cycle  9) */
#define USB_BWAIT_6             (0x0006u)   /*  6 wait (access cycle  8) */
#define USB_BWAIT_5             (0x0005u)   /*  5 wait (access cycle  7) */
#define USB_BWAIT_4             (0x0004u)   /*  4 wait (access cycle  6) */
#define USB_BWAIT_3             (0x0003u)   /*  3 wait (access cycle  5) */
#define USB_BWAIT_2             (0x0002u)   /*  2 wait (access cycle  4) */
#define USB_BWAIT_1             (0x0001u)   /*  1 wait (access cycle  3) */
#define USB_BWAIT_0             (0x0000u)   /*  0 wait (access cycle  2) */

/* System Configuration Status Register */
#define USB_OVCMON              (0xC000u)   /* b15-14: Over-current monitor */
#define USB_OVCBIT              (0x8000u)   /* b15-14: Over-current bit */
#define USB_HTACT               (0x0040u)   /* b6: USB Host Sequencer Status Monitor */
#define USB_SOFEA               (0x0020u)   /* b5: SOF monitor */
#define USB_IDMON               (0x0004u)   /* b2: ID-pin monitor */
#define USB_LNST                (0x0003u)   /* b1-0: D+, D- line status */
#define USB_SE1                 (0x0003u)   /* SE1 */
#define USB_FS_KSTS             (0x0002u)   /* Full-Speed K State */
#define USB_FS_JSTS             (0x0001u)   /* Full-Speed J State */
#define USB_LS_JSTS             (0x0002u)   /* Low-Speed J State */
#define USB_LS_KSTS             (0x0001u)   /* Low-Speed K State */
#define USB_SE0                 (0x0000u)   /* SE0 */

/* PLL Status Register */
#define USB_PLLLOCK             (0x0001u)

/* Device State Control Register */
#define USB_HNPBTOA             (0x0800u)   /* b11: Host negotiation protocol (BtoA) */
#define USB_EXICEN              (0x0400u)   /* b10: EXICEN output terminal control */
#define USB_VBUSEN              (0x0200u)   /* b9: VBUS output terminal control */
#define USB_WKUP                (0x0100u)   /* b8: Remote wakeup */
#define USB_RWUPE               (0x0080u)   /* b7: Remote wakeup sense */
#define USB_USBRST              (0x0040u)   /* b6: USB reset enable */
#define USB_RESUME              (0x0020u)   /* b5: Resume enable */
#define USB_UACT                (0x0010u)   /* b4: USB bus enable */
#define USB_RHST                (0x0007u)   /* b2-0: Reset handshake status */
#define USB_HSPROC              (0x0004u)   /* HS handshake processing */
#define USB_HSMODE              (0x0003u)   /* Hi-Speed mode */
#define USB_FSMODE              (0x0002u)   /* Full-Speed mode */
#define USB_LSMODE              (0x0001u)   /* Low-Speed mode */
#define USB_UNDECID             (0x0000u)   /* Undecided */

/* Test Mode Register */
#define USB_UTST                (0x000Fu)   /* b3-0: Test mode */
#define USB_H_TST_F_EN          (0x000Du)   /* HOST TEST FORCE ENABLE */
#define USB_H_TST_PACKET        (0x000Cu)   /* HOST TEST Packet */
#define USB_H_TST_SE0_NAK       (0x000Bu)   /* HOST TEST SE0 NAK */
#define USB_H_TST_K             (0x000Au)   /* HOST TEST K */
#define USB_H_TST_J             (0x0009u)   /* HOST TEST J */
#define USB_H_TST_NORMAL        (0x0000u)   /* HOST Normal Mode */
#define USB_P_TST_PACKET        (0x0004u)   /* PERI TEST Packet */
#define USB_P_TST_SE0_NAK       (0x0003u)   /* PERI TEST SE0 NAK */
#define USB_P_TST_K             (0x0002u)   /* PERI TEST K */
#define USB_P_TST_J             (0x0001u)   /* PERI TEST J */
#define USB_P_TST_NORMAL        (0x0000u)   /* PERI Normal Mode */

/* CFIFO/DxFIFO Port Select Register */
#define USB_RCNT                (0x8000u)   /* b15: Read count mode */
#define USB_REW                 (0x4000u)   /* b14: Buffer rewind */
#define USB_DCLRM               (0x2000u)   /* b13: Automatic buffer clear mode */
#define USB_DREQE               (0x1000u)   /* b12: DREQ output enable */
#define USB_MBW                 (0x0C00u)   /* b10: Maximum bit width for FIFO access */
#define USB_MBW_32              (0x0800u)   /* FIFO access : 32bit */
#define USB_MBW_16              (0x0400u)   /* FIFO access : 16bit */
#define USB_MBW_8               (0x0000u)   /* FIFO access : 8bit */
#define USB_BIGEND              (0x0100u)   /* b8: Big endian mode */
#define USB_FIFO_BIG            (0x0100u)   /* Big endian */
#define USB_FIFO_LITTLE         (0x0000u)   /* Little endian */
#define USB_ISEL                (0x0020u)   /* b5: DCP FIFO port direction select */
#define USB_CURPIPE             (0x000Fu)   /* b2-0: PIPE select */

/* CFIFO/DxFIFO Port Control Register */
#define USB_BVAL                (0x8000u)   /* b15: Buffer valid flag */
#define USB_BCLR                (0x4000u)   /* b14: Buffer clear */
#define USB_FRDY                (0x2000u)   /* b13: FIFO ready */
#define USB_DTLN                (0x0FFFu)   /* b11-0: FIFO data length */

/* Interrupt Enable Register 0 */
#define USB_VBSE                (0x8000u)   /* b15: VBUS interrupt */
#define USB_RSME                (0x4000u)   /* b14: Resume interrupt */
#define USB_SOFE                (0x2000u)   /* b13: Frame update interrupt */
#define USB_DVSE                (0x1000u)   /* b12: Device state transition interrupt */
#define USB_CTRE                (0x0800u)   /* b11: Control transfer stage transition interrupt */
#define USB_BEMPE               (0x0400u)   /* b10: Buffer empty interrupt */
#define USB_NRDYE               (0x0200u)   /* b9: Buffer notready interrupt */
#define USB_BRDYE               (0x0100u)   /* b8: Buffer ready interrupt */

/* Interrupt Enable Register 1 */
#define USB_OVRCRE              (0x8000u)   /* b15: Over-current interrupt */
#define USB_BCHGE               (0x4000u)   /* b14: USB bus change interrupt */
#define USB_DTCHE               (0x1000u)   /* b12: Detach sense interrupt */
#define USB_ATTCHE              (0x0800u)   /* b11: Attach sense interrupt */
#define USB_L1RSMENDE           (0x0200u)   /* b9: L1 resume completion interrupt */
#define USB_LPMENDE             (0x0100u)   /* b8: LPM transaction completion interrupt */
#define USB_EOFERRE             (0x0040u)   /* b6: EOF error interrupt */
#define USB_SIGNE               (0x0020u)   /* b5: SETUP IGNORE interrupt */
#define USB_SACKE               (0x0010u)   /* b4: SETUP ACK interrupt */
#define USB_PDDETINTE           (0x0001u)   /* b0: PDDET detection interrupt */

/* BRDY Interrupt Enable/Status Register */
#define USB_BRDY9               (0x0200u)   /* b9: PIPE9 */
#define USB_BRDY8               (0x0100u)   /* b8: PIPE8 */
#define USB_BRDY7               (0x0080u)   /* b7: PIPE7 */
#define USB_BRDY6               (0x0040u)   /* b6: PIPE6 */
#define USB_BRDY5               (0x0020u)   /* b5: PIPE5 */
#define USB_BRDY4               (0x0010u)   /* b4: PIPE4 */
#define USB_BRDY3               (0x0008u)   /* b3: PIPE3 */
#define USB_BRDY2               (0x0004u)   /* b2: PIPE2 */
#define USB_BRDY1               (0x0002u)   /* b1: PIPE1 */
#define USB_BRDY0               (0x0001u)   /* b1: PIPE0 */

/* NRDY Interrupt Enable/Status Register */
#define USB_NRDY9               (0x0200u)   /* b9: PIPE9 */
#define USB_NRDY8               (0x0100u)   /* b8: PIPE8 */
#define USB_NRDY7               (0x0080u)   /* b7: PIPE7 */
#define USB_NRDY6               (0x0040u)   /* b6: PIPE6 */
#define USB_NRDY5               (0x0020u)   /* b5: PIPE5 */
#define USB_NRDY4               (0x0010u)   /* b4: PIPE4 */
#define USB_NRDY3               (0x0008u)   /* b3: PIPE3 */
#define USB_NRDY2               (0x0004u)   /* b2: PIPE2 */
#define USB_NRDY1               (0x0002u)   /* b1: PIPE1 */
#define USB_NRDY0               (0x0001u)   /* b1: PIPE0 */

/* BEMP Interrupt Enable/Status Register */
#define USB_BEMP9               (0x0200u)   /* b9: PIPE9 */
#define USB_BEMP8               (0x0100u)   /* b8: PIPE8 */
#define USB_BEMP7               (0x0080u)   /* b7: PIPE7 */
#define USB_BEMP6               (0x0040u)   /* b6: PIPE6 */
#define USB_BEMP5               (0x0020u)   /* b5: PIPE5 */
#define USB_BEMP4               (0x0010u)   /* b4: PIPE4 */
#define USB_BEMP3               (0x0008u)   /* b3: PIPE3 */
#define USB_BEMP2               (0x0004u)   /* b2: PIPE2 */
#define USB_BEMP1               (0x0002u)   /* b1: PIPE1 */
#define USB_BEMP0               (0x0001u)   /* b0: PIPE0 */

/* SOF Pin Configuration Register */
#define USB_TRNENSEL            (0x0100u)   /* b8: Select transaction enable period */
#define USB_BRDYM               (0x0040u)   /* b6: BRDY clear timing */
#define USB_INTL                (0x0020u)   /* b5: Interrupt sense select */
#define USB_EDGESTS             (0x0010u)   /* b4:  */
#define USB_SOFMODE             (0x000Cu)   /* b3-2: SOF pin select */
#define USB_SOF_125US           (0x0008u)   /* SOF 125us Frame Signal */
#define USB_SOF_1MS             (0x0004u)   /* SOF 1ms Frame Signal */
#define USB_SOF_DISABLE         (0x0000u)   /* SOF Disable */

#define USB_HSEB                (0x8000u)   /* b15: CL only mode bit */

#define USB_REPSTART            (0x0800u)   /* b11: Terminator adjustment forcible starting bit */
#define USB_REPSEL              (0x0300u)   /* b9-8: Terminator adjustment cycle setting */
#define USB_REPSEL_128          (0x0300u)   /* 128 sec */
#define USB_REPSEL_64           (0x0200u)   /* 64 sec */
#define USB_REPSEL_16           (0x0100u)   /* 16 sec */
#define USB_REPSEL_NONE         (0x0000u)   /* - */
#define USB_CLKSEL              (0x0030u)   /* b5-4: System clock setting */
#define USB_CLKSEL_24           (0x0030u)   /* 24MHz */
#define USB_CLKSEL_20           (0x0020u)   /* 20MHz */
#define USB_CLKSEL_48           (0x0010u)   /* 48MHz */
#define USB_CLKSEL_30           (0x0000u)   /* 30MHz */
#define USB_CDPEN               (0x0008u)   /* b3: Charging downstream port enable */
#define USB_PLLRESET            (0x0002u)   /* b1: PLL reset control */
#define USB_DIRPD               (0x0001u)   /* b0: Power down control */

/* Interrupt Status Register 0 */
#define USB_VBINT               (0x8000u)   /* b15: VBUS interrupt */
#define USB_RESM                (0x4000u)   /* b14: Resume interrupt */
#define USB_SOFR                (0x2000u)   /* b13: SOF update interrupt */
#define USB_DVST                (0x1000u)   /* b12: Device state transition interrupt */
#define USB_CTRT                (0x0800u)   /* b11: Control transfer stage transition interrupt */
#define USB_BEMP                (0x0400u)   /* b10: Buffer empty interrupt */
#define USB_NRDY                (0x0200u)   /* b9: Buffer notready interrupt */
#define USB_BRDY                (0x0100u)   /* b8: Buffer ready interrupt */
#define USB_VBSTS               (0x0080u)   /* b7: VBUS input port */
#define USB_DVSQ                (0x0070u)   /* b6-4: Device state */
#define USB_DS_SPD_CNFG         (0x0070u)   /* Suspend Configured */
#define USB_DS_SPD_ADDR         (0x0060u)   /* Suspend Address */
#define USB_DS_SPD_DFLT         (0x0050u)   /* Suspend Default */
#define USB_DS_SPD_POWR         (0x0040u)   /* Suspend Powered */
#define USB_DS_SUSP             (0x0040u)   /* Suspend */
#define USB_DS_CNFG             (0x0030u)   /* Configured */
#define USB_DS_ADDS             (0x0020u)   /* Address */
#define USB_DS_DFLT             (0x0010u)   /* Default */
#define USB_DS_POWR             (0x0000u)   /* Powered */
#define USB_DVSQS               (0x0030u)   /* b5-4: Device state */
#define USB_VALID               (0x0008u)   /* b3: Setup packet detect flag */
#define USB_CTSQ                (0x0007u)   /* b2-0: Control transfer stage */
#define USB_CS_SQER             (0x0006u)   /* Sequence error */
#define USB_CS_WRND             (0x0005u)   /* Ctrl write nodata status stage */
#define USB_CS_WRSS             (0x0004u)   /* Ctrl write status stage */
#define USB_CS_WRDS             (0x0003u)   /* Ctrl write data stage */
#define USB_CS_RDSS             (0x0002u)   /* Ctrl read status stage */
#define USB_CS_RDDS             (0x0001u)   /* Ctrl read data stage */
#define USB_CS_IDST             (0x0000u)   /* Idle or setup stage */

/* Interrupt Status Register 1 */
#define USB_OVRCR               (0x8000u)   /* b15: Over-current interrupt */
#define USB_BCHG                (0x4000u)   /* b14: USB bus change interrupt */
#define USB_DTCH                (0x1000u)   /* b12: Detach sense interrupt */
#define USB_ATTCH               (0x0800u)   /* b11: Attach sense interrupt */
#define USB_L1RSMEND            (0x0200u)   /* b9: L1 resume completion interrupt */
#define USB_LPMEND              (0x0100u)   /* b8: LPM transaction completion interrupt */
#define USB_EOFERR              (0x0040u)   /* b6: EOF-error interrupt */
#define USB_SIGN                (0x0020u)   /* b5: Setup ignore interrupt */
#define USB_SACK                (0x0010u)   /* b4: Setup ack interrupt */
#define USB_PDDETINT            (0x0001u)   /* b0: PDDET detection interrupt */

/* Frame Number Register */
#define USB_OVRN                (0x8000u)   /* b15: Overrun error */
#define USB_CRCE                (0x4000u)   /* b14: Received data error */
#define USB_FRNM                (0x07FFu)   /* b10-0: Frame number */

/* Device State Change Register */ /* For USB0 */
#define USB_DVCHG               (0x8000u)   /* b15: Device state change */

/* Micro Frame Number Register */ /* For USBHS */
#define USB_UFRNM               (0x0007u)   /* b2-0: Micro frame number */

/* USB Address / Low Power Status Recovery Register */
#define USB_STSRECOV            (0x0F00u)   /* b11-8: Status Recovery */
#define USB_USBADDR_MASK        (0x007Fu)   /* b6-0: USB address */

/* USB Request Type Register */
#define USB_BMREQUESTTYPE       (0x00FFu)   /* b7-0: USB_BMREQUESTTYPE */
#define USB_BMREQUESTTYPEDIR    (0x0080u)   /* b7  : Data transfer direction */
#define USB_BMREQUESTTYPETYPE   (0x0060u)   /* b6-5: Type */
#define USB_BMREQUESTTYPERECIP  (0x001Fu)   /* b4-0: Recipient */

/* USB Request Value Register */
#define USB_WVALUE              (0xFFFFu)   /* b15-0: wValue */
#define USB_DT_TYPE             (0xFF00u)
#define USB_GET_DT_TYPE(v)      (((v) & USB_DT_TYPE) >> 8)
#define USB_DT_INDEX            (0x00FFu)
#define USB_CONF_NUM            (0x00FFu)
#define USB_ALT_SET             (0x00FFu)

/* USB Request Index Register */
#define USB_WINDEX              (0xFFFFu)   /* b15-0: wIndex */
#define USB_TEST_SELECT         (0xFF00u)   /* b15-b8: Test Mode Selectors */
#define USB_TEST_J              (0x0100u)   /* Test_J */
#define USB_TEST_K              (0x0200u)   /* Test_K */
#define USB_TEST_SE0_NAK        (0x0300u)   /* Test_SE0_NAK */
#define USB_TEST_PACKET         (0x0400u)   /* Test_Packet */
#define USB_TEST_FORCE_ENABLE   (0x0500u)   /* Test_Force_Enable */
#define USB_TEST_STSelectors    (0x0600u)   /* Standard test selectors */
#define USB_TEST_RESERVED       (0x4000u)   /* Reserved */
#define USB_TEST_VSTMODES       (0xC000u)   /* VendorSpecific test modes */
#define USB_EP_DIR              (0x0080u)   /* b7: Endpoint Direction */
#define USB_EP_DIR_IN           (0x0080u)
#define USB_EP_DIR_OUT          (0x0000u)

/* USB Request Length Register */
#define USB_WLENGTH             (0xFFFFu)   /* b15-0: wLength */

/* Refer to r_usb_cdefusbip.h */
#define USB_TYPE                (0xC000u)   /* b15-14: Transfer type */
#define USB_BFRE                (0x0400u)   /* b10: Buffer ready interrupt mode select */

#define USB_DEVSEL              (0xF000u)   /* b15-14: Device address select */
#define USB_MAXP                (0x007Fu)   /* b6-0: Maxpacket size of default control pipe */
#define USB_MXPS                (0x07FFu)   /* b10-0: Maxpacket size */

#define USB_BSTS                (0x8000u)   /* b15: Buffer status */
#define USB_SUREQ               (0x4000u)   /* b14: Send USB request  */
#define USB_INBUFM              (0x4000u)   /* b14: IN buffer monitor (Only for PIPE1 to 5) */
#define USB_CSCLR               (0x2000u)   /* b13: c-split status clear */
#define USB_CSSTS               (0x1000u)   /* b12: c-split status */
#define USB_SUREQCLR            (0x0800u)   /* b11: stop setup request */
#define USB_ATREPM              (0x0400u)   /* b10: Auto repeat mode */
#define USB_ACLRM               (0x0200u)   /* b9: buffer auto clear mode */
#define USB_SQCLR               (0x0100u)   /* b8: Sequence bit clear */
#define USB_SQSET               (0x0080u)   /* b7: Sequence bit set */
#define USB_SQMON               (0x0040u)   /* b6: Sequence bit monitor */
#define USB_PBUSY               (0x0020u)   /* b5: pipe busy */
#define USB_PINGE               (0x0010u)   /* b4: ping enable */
#define USB_CCPL                (0x0004u)   /* b2: Enable control transfer complete */
#define USB_PID                 (0x0003u)   /* b1-0: Response PID */
#define USB_PID_STALL           (0x0002u)   /* STALL */
#define USB_PID_BUF             (0x0001u)   /* BUF */
#define USB_PID_NAK             (0x0000u)   /* NAK */

#define USB_PIPENM              (0x0007u)   /* b2-0: Pipe select */

/* Refer to r_usb_cdefusbip.h */
#define USB_BUFSIZE             (0x7C00u)   /* b14-10: Pipe buffer size */
#define USB_BUFNMB              (0x007Fu)   /* b6-0: Pipe buffer number */
#define USB_PIPE0BUF            (256u)
#define USB_PIPEXBUF            (64u)

#define USB_TRENB               (0x0200u)   /* b9: Transaction count enable */
#define USB_TRCLR               (0x0100u)   /* b8: Transaction count clear */
#define USB_TRNCNT              (0xFFFFu)   /* b15-0: Transaction counter */

#define USB_UPPHUB              (0x7800u)   /* b14-11: HUB register */
#define USB_HUBPORT             (0x0700u)   /* b10-8: HUB port */
#define USB_USBSPD              (0x00C0u)   /* b7-6: Device speed */

/********* USB0 Only ******************************************************************************/

/* PHY Crosspoint Adjustment Register */
/* PHYSLEW */
#define USB_SLEWF01             (0x0008u)   /* b3: Cross point adjustment bit 01 */
#define USB_SLEWF00             (0x0004u)   /* b2: Cross point adjustment bit 00 */
#define USB_SLEWR01             (0x0002u)   /* b1: Cross point adjustment bit 01 */
#define USB_SLEWR00             (0x0001u)   /* b0: Cross point adjustment bit 00 */

/* Deep Standby USB Transceiver Control/Terminal Monitor Register */
/* DPUSR0R */
#define USB_DVBSTS0             (0x00800000u)   /* b23: USB0 VBUS input */
#define USB_DOVCB0              (0x00200000u)   /* b21: USB0 OVRCURB input */
#define USB_DOVCA0              (0x00100000u)   /* b20: USB0 OVRCURA input */
#define USB_DM0                 (0x00200000u)   /* b17: USB0 D- input */
#define USB_DP0                 (0x00100000u)   /* b16: USB0 D+ input */
#define USB_FIXPHY0             (0x00000010u)   /* b4: USB0 transceiver output fixed bit  */
#define USB_DRPD0               (0x00000008u)   /* b3: D+/D- pull down resistor control bit */
#define USB_RPUE0               (0x00000002u)   /* b1: DP pull up resistor control bit */
#define USB_SRPC0               (0x00000001u)   /* b0: USB0 single end receiver control bit */

/* Deep Standby USB Suspend/Resume Interrupt Register */
/* DPUSR1R */
#define USB_DVBINT0             (0x00800000u)   /* b23: USB0 VBUS monitor bit */
#define USB_DOVRCRB0            (0x00200000u)   /* b21: USB0 OVRCURB DM monitor bit */
#define USB_DOVRCRA0            (0x00100000u)   /* b20: USB0 OVRCURA DM monitor bit */
#define USB_DMINT0              (0x00020000u)   /* b17: USB0 DM monitor bit */
#define USB_DPINT0              (0x00010000u)   /* b16: USB0 DP monitor bit */
#define USB_DVBSE0              (0x00000080u)   /* b7: USB0 VBUS interrupt enable */
#define USB_DOVRCRBE0           (0x00000020u)   /* b5: USB0 OVRCURB interrupt enable */
#define USB_DOVRCRAE0           (0x00000010u)   /* b4: USB0 OVRCURA interrupt enable */
#define USB_DMINTE0             (0x00000002u)   /* b1: USB0 DM interrupt enable */
#define USB_DPINTE0             (0x00000001u)   /* b0: USB0 DP interrupt enable */

/**************************************************************************************************/

/********* USBHS Only *****************************************************************************/

/* Low Power Control Register */
/* LPCTRL */
#define USB_HWUPM               (0x0080u)   /* b7:  */

/* Low Power Status Register */
/* LPSTS */
#define USB_SUSPENDM            (0x4000u)   /* b14: UTMI SuspendM control */

/* PHY Single Access Read Data Register */
/* SPRDAT */
#define USB_PHYRDAT             (0x00FFu)   /* PHY read data bit */

/* Battery Charging Control Register */
/* BCCTRL */
#define USB_PDDETSTS            (0x0200u)   /* b9: PDDET status */
#define USB_CHGDETSTS           (0x0100u)   /* b8: CHGDET status */
#define USB_DCPMODE             (0x0020u)   /* b5: DCP mode  control */
#define USB_VDMSRCE             (0x0010u)   /* b4: VDMSRC control */
#define USB_IDPSINKE            (0x0008u)   /* b3: IDPSINK control */
#define USB_VDPSRCE             (0x0004u)   /* b2: VDPSRC control */
#define USB_IDMSINKE            (0x0002u)   /* b1: IDMSINK control */
#define USB_IDPSRCE             (0x0001u)   /* b0: IDPSRC control */

/* Function L1 Control Register 1 */
/* PL1CTRL1 */
#define USB_L1EXTMD             (0x4000u)   /* b14: PHY control mode */
#define USB_DVSQEX              (0x0080u)   /* b7: DVSQ extension bit */
#define USB_DVSQ                (0x0070u)   /* b6-4: Mirror of DVSQ */
#define USB_L1NEGOMD            (0x0008u)   /* b3: L1 response negotiation control */
#define USB_L1RESPMD            (0x0006u)   /* b2-1: L1 response mode */
#define USB_L1RESPEN            (0x0001u)   /* b0: L1 response enable */

/* Function L1 Control Register 2 */
/* PL1CTRL2 */
#define USB_HSRDMON             (0x0F00u)   /* b12: RWE monitor bit */
#define USB_RWEMON              (0x1000u)   /* b11-8: HIRD monitor bit */

/* Host L1 Control Register 1 */
/* HL1CTRL1 */
#define USB_L1STATUS            (0x0006u)   /* b2-1: L1 request completion state */
#define USB_L1REQ               (0x0001u)   /* b0: L1 changes request bit 
 */

/* Host L1 Control Register 2 */
/* HL1CTRL2 */
#define USB_BESL                (0x8000u)   /* b15: BESL & Alternate HIRD bit */
#define USB_L1RWE               (0x1000u)   /* b12: L1 RemoteWake enable for LPM tokens */
#define USB_HSRD                (0x0F00u)   /* b11-8: HIRD bit for LPM tokens */
#define USB_L1ADDR              (0x000Fu)   /* b3-0: DeviceAddress for LPM tokens */

/* PHY Timing Register 1 */
/* PHYTRIM1 */
#define USB_IMPOFFSET           (0x7000u)   /* b14-12: Terminator adjustment */
#define USB_HSIUP               (0x0F00u)   /* b11-8: Output level setup of HS  */
#define USB_PCOMPENB            (0x0080u)   /* b7: PVDD starting detection setup */
#define USB_DFALL               (0x000Cu)   /* b3-2: FS/LS falling output waveform compensation function setting */
#define USB_DRISE               (0x0003u)   /* b1-0: FS/LS standup output waveform compensation function setting */

/* PHY Timing Register 2 */
/* PHYTRIM2 */
#define USB_DIS                 (0x7000u)   /* b14-12: Disconnect disregard level setup */
#define USB_PDR                 (0x0300u)   /* b9-8: HS output compensation function setting */
#define USB_HSRXENMODE          (0x0080u)   /* b7: HS reception permission control mode setup */
#define USB_SQU                 (0x000Fu)   /* b3-0: Squelch disregard level setup */

/* Deep Standby USB Register */
/* DPUSR0R */
#define USB_DVBSTSHM            (0x00800000u)   /* b23: VBUS input */
#define USB_DOVCBHM             (0x00200000u)   /* b21: OVRCURB input */
#define USB_DOVCAHM             (0x00100000u)   /* b20: OVRCURA input */

/* DPUSR1R */
#define USB_DVBSTSH             (0x00800000u)   /* b23: Interruption factor return display of VBUS */
#define USB_DOVCBH              (0x00200000u)   /* b21: Interruption factor return display of OVRCURB  */
#define USB_DOVCAH              (0x00100000u)   /* b20: Interruption factor return display of OVRCURA  */
#define USB_DVBSTSHE            (0x00000080u)   /* b7 : VBUS interrupt enable */
#define USB_DOVCBHE             (0x00000020u)   /* b5 : OVRCURB interrupt enable */
#define USB_DOVCAHE             (0x00000010u)   /* b4 : OVRCURA interrupt enable */

/**************************************************************************************************/

/* DMAx Pin Configuration Register */
#define USB_DREQA               (0x4000u)   /* b14: Dreq active select */
#define USB_BURST               (0x2000u)   /* b13: Burst mode */
#define USB_DACKA               (0x0400u)   /* b10: Dack active select */
#define USB_DFORM               (0x0380u)   /* b9-7: DMA mode select */
#define USB_CPU_ADR_RD_WR       (0x0000u)   /* Address + RD/WR mode (CPU bus) */
#define USB_CPU_DACK_RD_WR      (0x0100u)   /* DACK + RD/WR (CPU bus) */
#define USB_CPU_DACK_ONLY       (0x0180u)   /* DACK only (CPU bus) */
#define USB_SPLIT_DACK_ONLY     (0x0200u)   /* DACK only (SPLIT bus) */
#define USB_DENDA               (0x0040u)   /* b6: Dend active select */
#define USB_PKTM                (0x0020u)   /* b5: Packet mode */
#define USB_DENDE               (0x0010u)   /* b4: Dend enable */
#define USB_OBUS                (0x0004u)   /* b2: OUTbus mode */

/* USB IO Register Reserved bit mask */
#define INTSTS1_MASK            (0xD870u)   /* INTSTS1 Reserved bit mask */
#define BRDYSTS_MASK            (0x03FFu)   /* BRDYSTS Reserved bit mask */
#define NRDYSTS_MASK            (0x03FFu)   /* NRDYSTS Reserved bit mask */
#define BEMPSTS_MASK            (0x03FFu)   /* BEMPSTS Reserved bit mask */

#endif /* R_USB_BITDEFINE_H */

/***********************************************************************************************************************
End  Of File
***********************************************************************************************************************/