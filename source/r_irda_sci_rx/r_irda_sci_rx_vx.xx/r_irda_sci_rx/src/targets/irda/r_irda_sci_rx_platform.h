/*
* Copyright (C) 2014-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 01.12.2014 1.00     First Release
*              : 27.01.2015 1.01     Chage symbol name of Arguments 
*                                    None change proceedures.
*              : 20.03.2025 1.03     Changed the disclaimer in program sources
*******************************************************************************/
/*******************************************************************************
* System Name  : interface file for IrDA fit module.
* File Name    : r_irda_sci_rx_platform.h
* Version      : 1.03
* Device       : RX
* Abstract     : 
* Tool-Chain   : Renesas RXC Toolchain v3.07.00
* OS           : not use
* H/W Platform : RSKRX113
* Description  : Functions for using IrDA on RX devices. 
* Limitation   : none
*******************************************************************************/
/* Guards against multiple inclusion */
#ifndef IRDA_SCI_PLATFORM_H

/*******************************************************************************
  Macro definitions
*******************************************************************************/
#define IRDA_SCI_PLATFORM_H

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
/* Include specifics for chosen MCU.  */
#if defined(BSP_MCU_RX113)
    #include "./rx113/r_irda_sci_rx113_private.h"
#else
    #error "This MCU is not supported by the current r_irda_sci_rx module."
#endif


#endif /* IRDA_SCI_PLATFORM_H */

/* End of File */
