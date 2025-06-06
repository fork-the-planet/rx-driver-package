/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_reg_access.h
 * Description  : USB IP Register control code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 30.11.2018 1.10 Supporting Smart Configurator
 *         : 30.06.2020 1.20 Added support for RTOS.
 *         : 20.03.2025 1.31 Changed the disclaimer.
 ***********************************************************************************************************************/
#ifndef HW_USB_REG_ACCESS_H
#define HW_USB_REG_ACCESS_H

/******************************************************************************
 Macro definitions
 ******************************************************************************/
#define USB_BUFSIZE_BIT   (10u)
#define USB_SUSPEND_MODE  (1u)
#define USB_NORMAL_MODE   (0)

#define USB0_CFIFO8     (USB0.CFIFO.BYTE.L)
#define USB0_D0FIFO8    (USB0.D0FIFO.BYTE.L)
#define USB0_D1FIFO8    (USB0.D1FIFO.BYTE.L)
#define USB0_CFIFO16    (USB0.CFIFO.WORD)
#define USB0_D0FIFO16   (USB0.D0FIFO.WORD)
#define USB0_D1FIFO16   (USB0.D1FIFO.WORD)

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables
 ******************************************************************************/

/*******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
/****************/
/*  INITIARIZE  */
/****************/
void         hw_usb_hmodule_init(void);
void         hw_usb_pmodule_init( void );


/************/
/*  SYSCFG  */
/************/
uint16_t hw_usb_read_syscfg (void);
void hw_usb_clear_cnen(void);
void hw_usb_set_dcfm (void);
void hw_usb_clear_drpd (void);
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
void hw_usb_set_cnen(void);
void hw_usb_pset_dprpu (void);
void hw_usb_pclear_dprpu (void);
void hw_usb_pset_dmrpu (void);
void hw_usb_pclear_dmrpu (void);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/************/
/*  SYSSTS0 */
/************/
uint16_t hw_usb_read_syssts (void);

/**************/
/*  DVSTCTR0  */
/**************/
uint16_t hw_usb_read_dvstctr (void);
void hw_usb_rmw_dvstctr (uint16_t data, uint16_t width);
void hw_usb_clear_dvstctr (uint16_t data);
void hw_usb_set_vbout (void);
void hw_usb_clear_vbout (void);
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
void hw_usb_hset_rwupe (void);
void hw_usb_hclear_uact (void);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
void hw_usb_pset_wkup (void);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/***************************/
/*  CFIFO, D0FIFO, D1FIFO  */
/***************************/
uint16_t hw_usb_read_fifo16 (uint16_t pipemode);
void hw_usb_write_fifo16 (uint16_t pipemode, uint16_t data);
void hw_usb_write_fifo8 (uint16_t pipemode, uint8_t data);

/************************************/
/*  CFIFOSEL, D0FIFOSEL, D1FIFOSEL  */
/************************************/
uint16_t hw_usb_read_fifosel (uint16_t pipemode);
void hw_usb_rmw_fifosel (uint16_t pipemode, uint16_t data, uint16_t width);
void hw_usb_clear_dclrm (uint16_t pipemode);
void hw_usb_set_dreqe (uint16_t pipemode);
void hw_usb_clear_dreqe (uint16_t pipemode);
void hw_usb_set_mbw (uint16_t pipemode, uint16_t data);
void hw_usb_set_curpipe (uint16_t pipemode, uint16_t pipeno);

/**********************************/
/* CFIFOCTR, D0FIFOCTR, D1FIFOCTR */
/**********************************/
uint16_t hw_usb_read_fifoctr (uint16_t pipemode);
void hw_usb_set_bval (uint16_t pipemode);
void hw_usb_set_bclr (uint16_t pipemode);

/*************/
/*  INTENB0  */
/*************/
void hw_usb_set_intenb (uint16_t data);
void hw_usb_clear_enb_vbse (void);
void hw_usb_clear_enb_sofe (void);
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
void hw_usb_pset_enb_rsme (void);
void hw_usb_pclear_enb_rsme (void);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/*************/
/*  BRDYENB  */
/*************/
void hw_usb_set_brdyenb (uint16_t pipeno);
void hw_usb_clear_brdyenb (uint16_t pipeno);

/*************/
/*  NRDYENB  */
/*************/
void hw_usb_set_nrdyenb (uint16_t pipeno);
void hw_usb_clear_nrdyenb (uint16_t pipeno);

/*************/
/*  BEMPENB  */
/*************/
void hw_usb_set_bempenb (uint16_t pipeno);
void hw_usb_clear_bempenb (uint16_t pipeno);

/*************/
/*  SOFCFG   */
/*************/
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
void hw_usb_hset_trnensel (void);
void hw_usb_hclear_trnensel (void);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/*************/
/*  INTSTS0  */
/*************/
void hw_usb_clear_sts_sofr (void);
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
uint16_t hw_usb_read_intsts (void);
void hw_usb_pclear_sts_resm (void);
void hw_usb_pclear_sts_valid (void);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/************/
/* BRDYSTS  */
/************/
void hw_usb_clear_sts_brdy (uint16_t pipeno);

/************/
/* NRDYSTS  */
/************/
void hw_usb_clear_status_nrdy (uint16_t pipeno);

/************/
/* BEMPSTS  */
/************/
void hw_usb_clear_status_bemp (uint16_t pipeno);

/************/
/* FRMNUM   */
/************/
uint16_t hw_usb_read_frmnum (void);

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
/************/
/* USBREQ   */
/************/
void hw_usb_hwrite_usbreq (uint16_t data);

/************/
/* USBVAL   */
/************/
void hw_usb_hset_usbval (uint16_t data);

/************/
/* USBINDX  */
/************/
void hw_usb_hset_usbindx (uint16_t data);

/************/
/* USBLENG  */
/************/
void hw_usb_hset_usbleng (uint16_t data);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
/************/
/* USBREQ   */
/************/
uint16_t hw_usb_read_usbreq (void);

/************/
/* USBVAL   */
/************/
uint16_t hw_usb_read_usbval (void);

/************/
/* USBINDX  */
/************/
uint16_t hw_usb_read_usbindx (void);

/************/
/* USBLENG  */
/************/
uint16_t hw_usb_read_usbleng (void);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/************/
/* DCPCFG   */
/************/
void hw_usb_write_dcpcfg (uint16_t data);

/************/
/* DCPMAXP  */
/************/
uint16_t hw_usb_read_dcpmaxp (void);
void hw_usb_write_dcpmxps (uint16_t data);

/************/
/* DCPCTR   */
/************/
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
void hw_usb_hwrite_dcpctr (uint16_t data);
void hw_usb_hset_sureq (void);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
uint16_t hw_usb_read_dcpctr (void);
void hw_usb_pset_ccpl (void);

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/************/
/* PIPESEL  */
/************/
void hw_usb_write_pipesel (uint16_t data);

/************/
/* PIPECFG  */
/************/
uint16_t hw_usb_read_pipecfg (void);
void hw_usb_write_pipecfg (uint16_t data);

/************/
/* PIPEMAXP */
/************/
uint16_t hw_usb_read_pipemaxp (void);
void hw_usb_write_pipemaxp (uint16_t data);

/************/
/* PIPEPERI */
/************/
void hw_usb_write_pipeperi (uint16_t data);

/********************/
/* DCPCTR, PIPEnCTR */
/********************/
uint16_t hw_usb_read_pipectr (uint16_t pipeno);
void hw_usb_set_aclrm (uint16_t pipeno);
void hw_usb_clear_aclrm (uint16_t pipeno);
void hw_usb_set_sqclr (uint16_t pipeno);
void hw_usb_set_sqset (uint16_t pipeno);
void hw_usb_set_pid (uint16_t pipeno, uint16_t data);
void hw_usb_clear_pid (uint16_t pipeno, uint16_t data);

/************/
/* PIPEnTRE */
/************/
void hw_usb_set_trenb (uint16_t pipeno);
void hw_usb_clear_trenb (uint16_t pipeno);
void hw_usb_set_trclr (uint16_t pipeno);

/************/
/* PIPEnTRN */
/************/
void hw_usb_write_pipetrn (uint16_t pipeno, uint16_t data);

/************/
/* BCCTRL   */
/************/
void hw_usb_set_bcctrl (uint16_t data);
void hw_usb_clear_bcctrl (uint16_t data);
uint16_t hw_usb_read_bcctrl (void);
void hw_usb_set_vdmsrce (void);
void hw_usb_clear_vdmsrce (void);
void hw_usb_set_idpsinke (void);
void hw_usb_clear_idpsinke (void);
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
void hw_usb_hset_dcpmode (void);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

void hw_usb_set_vdcen(void);
void hw_usb_set_vddusbe(void);
void hw_usb_set_batchge(void);
void hw_usb_clear_batchge(void);

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
/*************/
/*  INTENB1  */
/*************/
void hw_usb_hclear_enb_ovrcre (void);
void hw_usb_hset_enb_bchge (void);
void hw_usb_hclear_enb_bchge (void);
void hw_usb_hset_enb_dtche (void);
void hw_usb_hclear_enb_dtche (void);
void hw_usb_hclear_enb_attche (void);
void hw_usb_hset_enb_signe (void);
void hw_usb_hset_enb_sacke (void);
void hw_usb_hset_enb_pddetinte (void);

/*************/
/*  INTSTS1  */
/*************/
void hw_usb_hclear_sts_ovrcr (void);
void hw_usb_hclear_sts_bchg (void);
void hw_usb_hclear_sts_dtch (void);
void hw_usb_hclear_sts_attch (void);
void hw_usb_hclear_sts_sign (void);
void hw_usb_hclear_sts_sack (void);
void hw_usb_hclear_sts_pddetint (void);

/************/
/* DEVADDn  */
/************/
uint16_t hw_usb_hread_devadd (uint16_t devadr);
void hw_usb_hset_usbspd (uint16_t devadr, uint8_t data);

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

#endif /* HW_USB_REG_ACCESS_H */
/******************************************************************************
 End of file
 ******************************************************************************/
