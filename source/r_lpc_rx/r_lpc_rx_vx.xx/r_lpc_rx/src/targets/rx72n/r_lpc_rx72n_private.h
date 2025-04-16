/***********************************************************************************************************************
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_lpc_rx72n_private.h
 * Description  : Definitions used by the r_lpc_rx72n.c module.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           10.06.2020 2.01    Added RX65N, RX66N, RX72M and RX72N.
 *           28.06.2024 2.10    Removed duplicate macros (LPC_CLOCK_ACTIVE and LPC_CLOCK_INACTIVE)
 *           15.03.2025 2.51    Updated disclaimer.
 ***********************************************************************************************************************/

#ifndef R_LPC_RX72N_PRIVATE_H
    #define R_LPC_RX72N_PRIVATE_H

/***********************************************************************************************************************
 Error checking for user defined macros
***********************************************************************************************************************/

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
/* Internally used definitions */
    #define LPC_TRANSITION_ONGOING (1)
    #define LPC_TRANSITION_COMPLETE (0)

    #define LPC_OSC_STOP_ENABLED (1)

    #define LPC_SUB_CLOCK (0x0300)
    #define LPC_LOCO      (0x0000)

    #define LPC_CLOCK_SWITCH_ENABLE (0x01)
    #define LPC_CLOCK_SWITCH_DISABLE (0x00)

    #define LPC_CLOCK_INACTIVE    (0x01)
    #define LPC_CLOCK_ACTIVE      (0x00)

    #define LPC_MAX_BCK_HIGH_SPEED_FREQ_HZ    (120000000)
    #define LPC_MAX_FCK_HIGH_SPEED_FREQ_HZ    ( 60000000)
    #define LPC_MAX_ICK_HIGH_SPEED_FREQ_HZ    (240000000)
    #define LPC_MAX_PCKA_HIGH_SPEED_FREQ_HZ   (120000000)
    #define LPC_MAX_PCKB_HIGH_SPEED_FREQ_HZ   ( 60000000)
    #define LPC_MAX_PCKC_HIGH_SPEED_FREQ_HZ   ( 60000000)
    #define LPC_MAX_PCKD_HIGH_SPEED_FREQ_HZ   ( 60000000)
    
    #define LPC_MAX_BCK_LOW1_SPEED_FREQ_HZ    (1000000)
    #define LPC_MAX_FCK_LOW1_SPEED_FREQ_HZ    (1000000)
    #define LPC_MAX_ICK_LOW1_SPEED_FREQ_HZ    (1000000)
    #define LPC_MAX_PCKA_LOW1_SPEED_FREQ_HZ   (1000000)
    #define LPC_MAX_PCKB_LOW1_SPEED_FREQ_HZ   (1000000)
    #define LPC_MAX_PCKC_LOW1_SPEED_FREQ_HZ   (1000000)
    #define LPC_MAX_PCKD_LOW1_SPEED_FREQ_HZ   (1000000)
    
    #define LPC_MAX_BCK_LOW2_SPEED_FREQ_HZ    (264000)
    #define LPC_MAX_FCK_LOW2_SPEED_FREQ_HZ    (264000)
    #define LPC_MAX_ICK_LOW2_SPEED_FREQ_HZ    (264000)
    #define LPC_MAX_PCKA_LOW2_SPEED_FREQ_HZ   (264000)
    #define LPC_MAX_PCKB_LOW2_SPEED_FREQ_HZ   (264000)
    #define LPC_MAX_PCKC_LOW2_SPEED_FREQ_HZ   (264000)
    #define LPC_MAX_PCKD_LOW2_SPEED_FREQ_HZ   (264000)

    #define LPC_MIN_BCK_LOW2_SPEED_FREQ_HZ    (1)
    #define LPC_MIN_FCK_LOW2_SPEED_FREQ_HZ    (32000)
    #define LPC_MIN_ICK_LOW2_SPEED_FREQ_HZ    (32000)
    #define LPC_MIN_PCKA_LOW2_SPEED_FREQ_HZ   (1)
    #define LPC_MIN_PCKB_LOW2_SPEED_FREQ_HZ   (1)
    #define LPC_MIN_PCKC_LOW2_SPEED_FREQ_HZ   (1)
    #define LPC_MIN_PCKD_LOW2_SPEED_FREQ_HZ   (1)

    #define LPC_MEDIUM_SPD (0x02)
    #define LPC_HIGH_SPD (0x00)
    
    #define LPC_ACS_CHK_MSTPCRA                 (0xFFFFFFCF)
    #define LPC_ACS_CHK_MSTPCRB                 (0xFFFFFFFF)
    #define LPC_ACS_CHK_MSTPCRC                 (0xFFFF0000)
    #define LPC_ACS_CHK_MSTPCRD                 (0xFFFFFFFF)
    
    #define LPC_OFS0_REG_VALUE                  (*(volatile uint32_t *)0xFE7F5D04)

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
#endif /* R_LPC_RX72N_PRIVATE_H */
