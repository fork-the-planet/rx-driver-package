/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target_if.h
* Description  : Functions for using DTC on RX64M devices.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.09.2016 2.05    First Release
*******************************************************************************/
#ifndef DTC_RX_TARGET_IF_H
#define DTC_RX_TARGET_IF_H

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/

/*******************************************************************************
Macro definitions
*******************************************************************************/

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* Transfer data configuration */
typedef struct st_dtc_transfer_data_cfg {
    dtc_transfer_mode_t       transfer_mode;         /* DTC transfer mode */
    dtc_data_size_t           data_size;             /* Size of data */
    dtc_src_addr_mode_t       src_addr_mode;         /* Address mode of source */
    dtc_chain_transfer_t      chain_transfer_enable; /* Chain transfer is enabled or not. */
    dtc_chain_transfer_mode_t chain_transfer_mode;   /* How chain transfer is performed. */
    dtc_interrupt_t           response_interrupt;    /* How response interrupt is raised */
    dtc_repeat_block_side_t   repeat_block_side;     /* The side being repeat or block in */
                                                     /*  repeat / block transfer mode. */
    dtc_dest_addr_mode_t      dest_addr_mode;        /* Address mode of destination */
    uint32_t                  source_addr;           /* Start address of source */
    uint32_t                  dest_addr;             /* Start address of destination */
    uint32_t                  transfer_count;        /* Transfer count */
    uint16_t                  block_size;            /* Size of a block in block transfer mode */
    uint16_t                  rsv;                   /* Reserved */
} dtc_transfer_data_cfg_t;

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/


#endif /* DTC_RX_TARGET_IF_H */

/* End of File */

