/***********************************************************************************************************************
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_lpc_rx231_private.h
 * Description  : Definitions used by the r_lpc_rx231.c module.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description           
 *           01.10.2016 1.00    First Release
 *           28.06.2024 1.10    Removed duplicate macros (LPC_CLOCK_ACTIVE and LPC_CLOCK_INACTIVE)
 *           15.03.2025 2.51    Updated disclaimer.
 ***********************************************************************************************************************/

#ifndef R_LPC_RX231_PRIVATE_H
    #define R_LPC_RX231_PRIVATE_H

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
/* Internally used definitions */
    #define LPC_TRANSITION_ONGOING (1)
    #define LPC_TRANSITION_COMPLETE (0)

    #define LPC_OSC_STOP_ENABLED (1)

    #define LPC_SUB_CLOCK (0x0300)

    #define LPC_CLOCK_SWITCH_ENABLE (0x01)
    #define LPC_CLOCK_SWITCH_DISABLE (0x00)

    #define LPC_CLOCK_INACTIVE    (0x01)
    #define LPC_CLOCK_ACTIVE      (0x00)

    #if (BSP_CFG_MCU_VCC_MV > 2699)
        #define LPC_MAX_ICK_HIGH_SPEED_FREQ_HZ2 (54000000)
        #define LPC_MAX_ICK_HIGH_SPEED_FREQ_HZ  (32000000)
        #define LPC_MAX_PCKA_HIGH_SPEED_FREQ_HZ (54000000)
        #define LPC_MAX_PCKB_HIGH_SPEED_FREQ_HZ (32000000)
        #define LPC_MAX_PCKD_HIGH_SPEED_FREQ_HZ (54000000)
        #define LPC_MAX_FCK_HIGH_SPEED_FREQ_HZ  (32000000)
        #define LPC_MAX_BCK_HIGH_SPEED_FREQ_HZ  (32000000)

        #define LPC_MAX_ICK_MID_SPEED_FREQ_HZ   (12000000)
        #define LPC_MAX_PCKA_MID_SPEED_FREQ_HZ  (12000000)
        #define LPC_MAX_PCKB_MID_SPEED_FREQ_HZ  (12000000)
        #define LPC_MAX_PCKD_MID_SPEED_FREQ_HZ  (12000000)
        #define LPC_MAX_FCK_MID_SPEED_FREQ_HZ   (12000000)
        #define LPC_MAX_BCK_MID_SPEED_FREQ_HZ   (12000000)

        #define LPC_MAX_ICK_LOW_SPEED_FREQ_HZ   (32768)
        #define LPC_MAX_PCKA_LOW_SPEED_FREQ_HZ  (32768)
        #define LPC_MAX_PCKB_LOW_SPEED_FREQ_HZ  (32768)
        #define LPC_MAX_PCKD_LOW_SPEED_FREQ_HZ  (32768)
        #define LPC_MAX_FCK_LOW_SPEED_FREQ_HZ   (32768)
        #define LPC_MAX_BCK_LOW_SPEED_FREQ_HZ   (32768)

    #elif (BSP_CFG_MCU_VCC_MV > 2399)
        #define LPC_MAX_ICK_HIGH_SPEED_FREQ_HZ2 (16000000)
        #define LPC_MAX_ICK_HIGH_SPEED_FREQ_HZ  (16000000)
        #define LPC_MAX_PCKA_HIGH_SPEED_FREQ_HZ (16000000)
        #define LPC_MAX_PCKB_HIGH_SPEED_FREQ_HZ (16000000)
        #define LPC_MAX_PCKD_HIGH_SPEED_FREQ_HZ (16000000)
        #define LPC_MAX_FCK_HIGH_SPEED_FREQ_HZ  (16000000)
        #define LPC_MAX_BCK_HIGH_SPEED_FREQ_HZ  (16000000)

        #define LPC_MAX_ICK_MID_SPEED_FREQ_HZ   (12000000)
        #define LPC_MAX_PCKA_MID_SPEED_FREQ_HZ  (12000000)
        #define LPC_MAX_PCKB_MID_SPEED_FREQ_HZ  (12000000)
        #define LPC_MAX_PCKD_MID_SPEED_FREQ_HZ  (12000000)
        #define LPC_MAX_FCK_MID_SPEED_FREQ_HZ   (12000000)
        #define LPC_MAX_BCK_MID_SPEED_FREQ_HZ   (12000000)

        #define LPC_MAX_ICK_LOW_SPEED_FREQ_HZ   (32768)
        #define LPC_MAX_PCKA_LOW_SPEED_FREQ_HZ  (32768)
        #define LPC_MAX_PCKB_LOW_SPEED_FREQ_HZ  (32768)
        #define LPC_MAX_PCKD_LOW_SPEED_FREQ_HZ  (32768)
        #define LPC_MAX_FCK_LOW_SPEED_FREQ_HZ   (32768)
        #define LPC_MAX_BCK_LOW_SPEED_FREQ_HZ   (32768)

    #elif (BSP_CFG_MCU_VCC_MV > 1799)
        #define LPC_MAX_ICK_HIGH_SPEED_FREQ_HZ2 (8000000)
        #define LPC_MAX_ICK_HIGH_SPEED_FREQ_HZ  (8000000)
        #define LPC_MAX_PCKA_HIGH_SPEED_FREQ_HZ (8000000)
        #define LPC_MAX_PCKB_HIGH_SPEED_FREQ_HZ (8000000)
        #define LPC_MAX_PCKD_HIGH_SPEED_FREQ_HZ (8000000)
        #define LPC_MAX_FCK_HIGH_SPEED_FREQ_HZ  (8000000)
        #define LPC_MAX_BCK_HIGH_SPEED_FREQ_HZ  (8000000)

        #define LPC_MAX_ICK_MID_SPEED_FREQ_HZ   (8000000)
        #define LPC_MAX_PCKA_MID_SPEED_FREQ_HZ  (8000000)
        #define LPC_MAX_PCKB_MID_SPEED_FREQ_HZ  (8000000)
        #define LPC_MAX_PCKD_MID_SPEED_FREQ_HZ  (8000000)
        #define LPC_MAX_FCK_MID_SPEED_FREQ_HZ   (8000000)
        #define LPC_MAX_BCK_MID_SPEED_FREQ_HZ   (8000000)

        #define LPC_MAX_ICK_LOW_SPEED_FREQ_HZ   (32768)
        #define LPC_MAX_PCKA_LOW_SPEED_FREQ_HZ  (32768)
        #define LPC_MAX_PCKB_LOW_SPEED_FREQ_HZ  (32768)
        #define LPC_MAX_PCKD_LOW_SPEED_FREQ_HZ  (32768)
        #define LPC_MAX_FCK_LOW_SPEED_FREQ_HZ   (32768)
        #define LPC_MAX_BCK_LOW_SPEED_FREQ_HZ   (32768)
    #endif

    #define LPC_MEDIUM_SPD (0x02)
    #define LPC_HIGH_SPD (0x00)

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
#endif /* R_LPC_RX231_PRIVATE_H */
