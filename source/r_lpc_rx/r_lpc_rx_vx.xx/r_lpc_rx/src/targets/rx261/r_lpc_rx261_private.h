/***********************************************************************************************************************
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_lpc_rx261_private.h
 * Description  : Definitions used by the r_lpc_rx261.c module.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description           
 *         : 28.06.2024 1.00    First Release
 *         : 15.03.2025 2.51    Updated disclaimer.
 ***********************************************************************************************************************/

#ifndef R_LPC_RX261_PRIVATE_H
    #define R_LPC_RX261_PRIVATE_H

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
/* Internally used definitions */
    #define LPC_TRANSITION_ONGOING    (1)
    #define LPC_TRANSITION_COMPLETE   (0)

    #define LPC_OSC_STOP_ENABLED      (1)

    #define LPC_SUB_CLOCK             (0x0300)

    #define LPC_CLOCK_SWITCH_ENABLE   (0x01)
    #define LPC_CLOCK_SWITCH_DISABLE  (0x00)

    #define LPC_CLOCK_INACTIVE        (0x01)
    #define LPC_CLOCK_ACTIVE          (0x00)


    #if (BSP_CFG_MCU_VCC_MV > 2399)
        #define LPC_MAX_ICLK_HIGH_SPEED_FREQ_HZ               (64000000)
        #define LPC_MAX_FCLK_HIGH_SPEED_FREQ_HZ               (64000000)
        #define LPC_MAX_PCLKA_HIGH_SPEED_FREQ_HZ              (64000000)
        #define LPC_MAX_PCLKB_HIGH_SPEED_FREQ_HZ              (32000000)
        #define LPC_MAX_PCLKD_HIGH_SPEED_FREQ_HZ              (64000000)

        #define LPC_MAX_ICLK_MID_SPEED_FREQ_HZ                (24000000)
        #define LPC_MAX_FCLK_MID_SPEED_FREQ_HZ                (24000000)
        #define LPC_MAX_PCLKA_MID_SPEED_FREQ_HZ               (24000000)
        #define LPC_MAX_PCLKB_MID_SPEED_FREQ_HZ               (24000000)
        #define LPC_MAX_PCLKD_MID_SPEED_FREQ_HZ               (24000000)

        #define LPC_MAX_ICLK_MID_SPEED2_FREQ_HZ               (1000000)
        #define LPC_MAX_FCLK_MID_SPEED2_FREQ_HZ               (1000000)
        #define LPC_MAX_PCLKA_MID_SPEED2_FREQ_HZ              (1000000)
        #define LPC_MAX_PCLKB_MID_SPEED2_FREQ_HZ              (1000000)
        #define LPC_MAX_PCLKD_MID_SPEED2_FREQ_HZ              (1000000)

        #define LPC_MAX_ICLK_LOW_SPEED_FREQ_HZ                (32768)
        #define LPC_MAX_FCLK_LOW_SPEED_FREQ_HZ                (32768)
        #define LPC_MAX_PCLKA_LOW_SPEED_FREQ_HZ               (32768)
        #define LPC_MAX_PCLKB_LOW_SPEED_FREQ_HZ               (32768)
        #define LPC_MAX_PCLKD_LOW_SPEED_FREQ_HZ               (32768)

    #elif  (BSP_CFG_MCU_VCC_MV > 1799)
        #define LPC_MAX_ICLK_HIGH_SPEED_FREQ_HZ               (48000000)
        #define LPC_MAX_FCLK_HIGH_SPEED_FREQ_HZ               (48000000)
        #define LPC_MAX_PCLKA_HIGH_SPEED_FREQ_HZ              (48000000)
        #define LPC_MAX_PCLKB_HIGH_SPEED_FREQ_HZ              (32000000)
        #define LPC_MAX_PCLKD_HIGH_SPEED_FREQ_HZ              (48000000)
        #define LPC_MAX_RSIP_ENABLE_HIGH_SPEED_FREQ_HZ        (16000000)

        #define LPC_MAX_ICLK_MID_SPEED_FREQ_HZ                (24000000)
        #define LPC_MAX_FCLK_MID_SPEED_FREQ_HZ                (24000000)
        #define LPC_MAX_PCLKA_MID_SPEED_FREQ_HZ               (24000000)
        #define LPC_MAX_PCLKB_MID_SPEED_FREQ_HZ               (24000000)
        #define LPC_MAX_PCLKD_MID_SPEED_FREQ_HZ               (24000000)
        #define LPC_MAX_RSIP_ENABLE_MID_SPEED_FREQ_HZ         (16000000)

        #define LPC_MAX_ICLK_MID_SPEED2_FREQ_HZ               (1000000)
        #define LPC_MAX_FCLK_MID_SPEED2_FREQ_HZ               (1000000)
        #define LPC_MAX_PCLKA_MID_SPEED2_FREQ_HZ              (1000000)
        #define LPC_MAX_PCLKB_MID_SPEED2_FREQ_HZ              (1000000)
        #define LPC_MAX_PCLKD_MID_SPEED2_FREQ_HZ              (1000000)

        #define LPC_MAX_ICLK_LOW_SPEED_FREQ_HZ                (32768)
        #define LPC_MAX_FCLK_LOW_SPEED_FREQ_HZ                (32768)
        #define LPC_MAX_PCLKA_LOW_SPEED_FREQ_HZ               (32768)
        #define LPC_MAX_PCLKB_LOW_SPEED_FREQ_HZ               (32768)
        #define LPC_MAX_PCLKD_LOW_SPEED_FREQ_HZ               (32768)

    #elif  (BSP_CFG_MCU_VCC_MV > 1599)
        #define LPC_MAX_ICLK_MID_SPEED_FREQ_HZ                (4000000)
        #define LPC_MAX_FCLK_MID_SPEED_FREQ_HZ                (4000000)
        #define LPC_MAX_PCLKA_MID_SPEED_FREQ_HZ               (4000000)
        #define LPC_MAX_PCLKB_MID_SPEED_FREQ_HZ               (4000000)
        #define LPC_MAX_PCLKD_MID_SPEED_FREQ_HZ               (4000000)

        #define LPC_MAX_ICLK_MID_SPEED2_FREQ_HZ               (1000000)
        #define LPC_MAX_FCLK_MID_SPEED2_FREQ_HZ               (1000000)
        #define LPC_MAX_PCLKA_MID_SPEED2_FREQ_HZ              (1000000)
        #define LPC_MAX_PCLKB_MID_SPEED2_FREQ_HZ              (1000000)
        #define LPC_MAX_PCLKD_MID_SPEED2_FREQ_HZ              (1000000)

        #define LPC_MAX_ICLK_LOW_SPEED_FREQ_HZ                (32768)
        #define LPC_MAX_FCLK_LOW_SPEED_FREQ_HZ                (32768)
        #define LPC_MAX_PCLKA_LOW_SPEED_FREQ_HZ               (32768)
        #define LPC_MAX_PCLKB_LOW_SPEED_FREQ_HZ               (32768)
        #define LPC_MAX_PCLKD_LOW_SPEED_FREQ_HZ               (32768)
    #endif

    #define LPC_MEDIUM_SPD                                    (0x02)
    #define LPC_MEDIUM_SPD_2                                  (0x04)
    #define LPC_HIGH_SPD                                      (0x00)

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
#endif /* R_LPC_RX261_PRIVATE_H */
