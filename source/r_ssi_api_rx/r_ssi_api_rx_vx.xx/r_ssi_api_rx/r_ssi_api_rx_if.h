/*
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/******************************************************************************
* File Name    : r_ssi_api_rx_if.h
* Version      : 2.04
* Tool-Chain   : RX Family C Compiler
*                GCC for Renesas RX
*                IAR C/C++ Compiler for Renesas RX
* Description  : SSI driver module file for RX MCUs.
*******************************************************************************
* History : DD.MM.YYYY  Version   Description
*         : 01.08.2014   1.00      First release.
*         : 03.12.2014   1.10      Add flag access functions.
*         : 11.12.2014   1.11      RX71M support added.
*         : 28.04.2015   1.20      RX113, RX231, RX230 support added.
*         : 07.04.2017   1.21      Version number updated.
*         : 01.02.2019   1.22      Changed Minor version to 1.22.
*         : 20.05.2019   1.23      Added support for the GCC and IAR compiler.
*         : 20.06.2019   1.24      RX23W support added.
*         : 25.06.2019   2.00      SSIE support added.
*         : 31.10.2019   2.01      Version number updated.
*         : 30.06.2020   2.02      Version number updated.
*         : 30.06.2021   2.03      RX671 support added.
*         : 20.03.2025   2.04      Changed the disclaimer.
*
******************************************************************************/
#ifndef SSI_API_RX_H_
#define SSI_API_RX_H_

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Fixed-width integer and bool support. */
#include "platform.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/* Version Number of API. */
#define SSI_API_VERSION_MAJOR           (2)
#define SSI_API_VERSION_MINOR           (04)

/******************************************************************************
Typedef definitions
******************************************************************************/
/* Channel Number of SSI */
typedef enum {
    SSI_CH0 = 0,
#if (defined(SSI1) || defined(SSIE1))
    SSI_CH1 = 1, /* activates when using MCU with SSI1 or SSIE1 */
#endif
} ssi_ch_t;

/* Setting Value of Mute On/Off */
typedef enum {
    SSI_MUTE_ON  = 0,
    SSI_MUTE_OFF = 1,
} ssi_mute_t;

/* Return Value of SSI API */
typedef enum {
    SSI_SUCCESS     = 0,
    SSI_FLAG_CLR    = 0,
    SSI_FLAG_SET    = 1,
    SSI_ERR_PARAM   = -1,
    SSI_ERR_CHANNEL = -2,
    SSI_ERR_EXCEPT  = -3,
} ssi_ret_t;

/******************************************************************************
Exported global variables
******************************************************************************/
/* No global variable definited */

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/
ssi_ret_t R_SSI_Open ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_Start ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_Stop ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_Close ( const ssi_ch_t Channel );
int8_t R_SSI_Write ( const ssi_ch_t Channel, const void * pBuf, const uint8_t Samples );
int8_t R_SSI_Read ( const ssi_ch_t Channel, void * pBuf, const uint8_t Samples );
ssi_ret_t R_SSI_Mute ( const ssi_ch_t Channel, const ssi_mute_t OnOff );
uint32_t R_SSI_GetVersion( void );
ssi_ret_t R_SSI_GetFlagTxUnderFlow ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_GetFlagTxOverFlow ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_GetFlagRxUnderFlow ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_GetFlagRxOverFlow ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_ClearFlagTxUnderFlow ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_ClearFlagTxOverFlow ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_ClearFlagRxUnderFlow ( const ssi_ch_t Channel );
ssi_ret_t R_SSI_ClearFlagRxOverFlow ( const ssi_ch_t Channel );

#endif /* SSI_API_RX_H_ */

