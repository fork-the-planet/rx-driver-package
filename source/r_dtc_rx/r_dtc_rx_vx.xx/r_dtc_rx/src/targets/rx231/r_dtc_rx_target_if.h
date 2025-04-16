/***********************************************************************************************************************
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target_if.h
* Description  : Functions for using DTC on RX231 devices.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.09.2016 2.05    First Release
*         : 15.03.2025 4.51    Updated disclaimer.
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

