/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 31.03.2021 1.00     First Release
*              : 16.03.2023 1.40     Added r_qspix_read_memory_map() function
*              : 15.03.2025 1.42     Updated disclaimer
*******************************************************************************/
/*******************************************************************************
* File Name    : r_qspix_rx671_private.h
* Description  : Functions for using QSPIX on RX devices.
*******************************************************************************/
#ifndef R_QSPIX_RX671_PRIVATE_H
#define R_QSPIX_RX671_PRIVATE_H

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
/* Access to peripherals and board defines. */
#include "platform.h"
#include "r_qspix_rx_if.h"
#ifdef BSP_MCU_RX671


/*******************************************************************************
Macro definitions
*******************************************************************************/

/*----------------------------------------------------------------------------*/
/*   Define                                                                   */
/*----------------------------------------------------------------------------*/
/* Define maximum number of BANK */
#define QSPIX_MAXIMUM_BANK (63)

/*******************************************************************************
Private global variables and functions
*******************************************************************************/
/*----------------------------------------------------------------------------*/
/*   Function For Target MCU                                                  */
/*----------------------------------------------------------------------------*/
extern qspix_err_t r_qspix_parameter_channel_check(uint8_t channel);
extern qspix_err_t r_qspix_parameter_check(uint8_t channel, qspix_cfg_t * p_cfg);
extern qspix_err_t r_qspix_enable(uint8_t channel, qspix_cfg_t * p_cfg);
extern qspix_err_t r_qspix_control(uint8_t channel, qspix_cfg_t * p_cfg);
extern qspix_err_t r_qspix_disable(uint8_t channel);

extern qspix_err_t r_qspix_xip(uint8_t channel, uint8_t mode, bool action);
extern qspix_err_t r_qspix_get_status(qspix_cmd_t cmd, uint8_t *return_status);
extern qspix_err_t r_qspix_read_indirect(uint8_t channel,
                                  uint8_t *p_des_addr,
                                  uint32_t bytes);
extern qspix_err_t r_qspix_read_memory_map(uint8_t channel,
                                    uint8_t *p_des_addr,
                                    uint32_t p_addr,
                                    qspix_protocol_t protocol_ext,
                                    qspix_address_size_t addr_size,
                                    uint32_t bytes);
extern qspix_err_t r_qspix_write_indirect(uint8_t channel,
                                   uint8_t *p_src_addr,
                                   uint32_t bytes,
                                   bool read_after_write);
extern qspix_err_t r_qspix_set_spi_protocol(uint8_t channel, qspix_protocol_t protocol);
extern qspix_err_t r_qspix_bankset(uint8_t channel, uint8_t bank);
#endif /* BSP_MCU_RX671 */
#endif /* R_QSPIX_RX671_PRIVATE_H */
/* End of File */

