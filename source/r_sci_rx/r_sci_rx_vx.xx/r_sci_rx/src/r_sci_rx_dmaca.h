/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_sci_rx_dmaca.h
* Description  : 
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           25.08.2020 1.00    Initial Release
*           31.03.2023 4.80    Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*           29.05.2023 4.90    Fixed to comply with GSCE Coding Standards Rev.6.5.0.
***********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "platform.h"
#include "r_sci_rx_if.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/
/******************************************************************************
 * Function Name: sci_txfifo_dmaca_create
 * Description  : .
 * Arguments    : hdl
 *              : p_src
 *              : length
 * Return Value : .
 *****************************************************************************/
sci_err_t sci_txfifo_dmaca_create (sci_hdl_t const hdl, uint8_t *p_src, uint16_t const length);

/******************************************************************************
 * Function Name: sci_rxfifo_dmaca_create
 * Description  : .
 * Arguments    : hdl
 *              : p_dst
 *              : length
 * Return Value : .
 *****************************************************************************/
sci_err_t sci_rxfifo_dmaca_create (sci_hdl_t const hdl, uint8_t *p_dst, uint16_t const length);

/******************************************************************************
 * Function Name: sci_tx_dmaca_create
 * Description  : .
 * Arguments    : hdl
 *              : p_src
 *              : length
 * Return Value : .
 *****************************************************************************/
sci_err_t sci_tx_dmaca_create (sci_hdl_t const hdl, uint8_t *p_src, uint16_t const length);

/******************************************************************************
 * Function Name: sci_rx_dmaca_create
 * Description  : .
 * Arguments    : hdl
 *              : p_dst
 *              : length
 * Return Value : .
 *****************************************************************************/
sci_err_t sci_rx_dmaca_create (sci_hdl_t const hdl, uint8_t *p_dst, uint16_t const length);
