/*
* Copyright (c) 2018(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_usb_dmac.h
* Description  : DMA Difinition for USB
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.11.2018 1.00    First Release
*         : 30.06.2020 1.20    Added support for RTOS.
*         : 20.03.2025 1.31    Changed the disclaimer.
***********************************************************************************************************************/

/*******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/


#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))

#ifndef R_USB_DMAC_H
#define R_USB_DMAC_H

/*******************************************************************************
 Macro definitions
 *******************************************************************************/
#define USB_DMA_USE_CH_MAX          (2)     /* MAX USE DMAC CH for USB */
#define USB_DMA_CH_PRI              (3)     /* DMACmI interrupt priority level for USB Pipe : DxFIFO->buff */
#define USB_DMA_CH2_PRI             (3)     /* DMACmI interrupt priority level for USB Pipe : buff->DxFIFO */

#define USB_BIT_MBW16            (1UL)                             /* Mod 2(2Byte=16Bit) */

/******************************************************************************
 Exported global functions (to be accessed by other files)
 ******************************************************************************/
extern uint32_t g_usb_cstd_dma_size[USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 buffer size */
extern uint16_t g_usb_cstd_dma_fifo[USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 FIFO buffer size */
extern uint16_t g_usb_cstd_dma_pipe[USB_DMA_USE_CH_MAX]; /* DMA0 and DMA1 pipe number */

void        usb_cstd_dma_driver(void);
uint16_t    usb_cstd_dma_get_crtb(uint16_t useport);
uint16_t    usb_cstd_dma_get_ir_vect(uint16_t useport);
void        usb_cstd_dma_clear_ir(uint16_t useport);
void        usb_cstd_dma_rcv_setting(uint32_t src_adr, uint16_t useport, uint32_t transfer_size);
void        usb_cstd_dma_send_setting(uint32_t src_adr, uint16_t useport, uint32_t transfer_size);
void        usb_cstd_dma_stop(uint16_t fifo_mode);
void        usb_cstd_dfifo_end(uint16_t useport);

uint8_t     usb_cstd_dma_ref_ch_no(uint16_t useport);
void        usb_cstd_dma_set_ch_no(uint16_t useport, uint8_t dma_ch_no);
void        usb_cstd_dma_send_continue(uint16_t useport);

void        usb_cstd_dma_rcv_start(uint16_t pipe, uint16_t useport);
void        usb_cstd_dma_send_start(uint16_t pipe, uint16_t useport);
void        usb_cstd_dma_send_restart(uint32_t src, uint32_t data_size, uint8_t pipe);
void        usb_cstd_dma_send_complete(uint16_t useport);

void        usb_cstd_d0fifo_cb (void);
void        usb_cstd_d1fifo_cb (void);

#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#endif /* R_USB_DMAC_H */
/******************************************************************************
End  Of File
******************************************************************************/
