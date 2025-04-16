/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_riichs_rx_pin_config.h
 * Description  : Pin configures the RIICHS drivers
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 30.06.2021 1.00     First Release
 *         : 15.03.2025 1.21     Updated disclaimer
 **********************************************************************************************************************/
/* Guards against multiple inclusion */
#ifndef RIICHS_PIN_CONFIG_H
    #define RIICHS_PIN_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/
/*------------------------------------------------------------------------------*/
/*   Set using port as riic port                                                */
/*------------------------------------------------------------------------------*/
/* Set using port as riic port.                                                                 */
/* If you want to include the port configuration process(RIICHS_CFG_PORT_SET_PROCESSING is "1"),  */
/* please choose which ports to use for the SCL/SDA of RIICHS with the following setting.         */
/* Select the port group and pin used by setting
 "R_RIICHS_CFG_RIICHSx_SCLx_PORT (select from port group 0 to K)"
 and "R_RIICHS_CFG_RIICHSx_SCLx_BIT (select from pin number 0 to 7)"
 and "R_RIICHS_CFG_RIICHSx_SDAx_PORT (select from port group 0 to K)"
 and "R_RIICHS_CFG_RIICHSx_SDAx_BIT (select from pin number 0 to 7)",
 respectively. */

/* Select the ports (SCL0 and SDA0) to use in RIICHS0 */
    #define R_RIICHS_CFG_RIICHS0_SCL0_PORT   '1'     /* Port Number */
    #define R_RIICHS_CFG_RIICHS0_SCL0_BIT    '2'     /* Bit Number  */

    #define R_RIICHS_CFG_RIICHS0_SDA0_PORT   '1'     /* Port Number */
    #define R_RIICHS_CFG_RIICHS0_SDA0_BIT    '3'     /* Bit Number  */

#endif /* RIICHS_PIN_CONFIG_H */

