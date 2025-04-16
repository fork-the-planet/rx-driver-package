/*
* Copyright (c) 2014 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/******************************************************************************
* File Name    : r_src_api_rx_config.h
* Version      : 1.15
* Device       : RX64M, RX71M
* Description  : SRC programming for the RX family. This file has options to let
*                the user customize parts of the SRC API.
*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 31.07.2014 1.00    First release. 
*         : 04.09.2014 1.10    Second Release, no code modification on this file.
*         : 11.12.2014 1.11    RX71M support added.
*         : 20.03.2025 1.15    Changed the disclaimer.
*
******************************************************************************/

#ifndef SRC_API_CONFIG_H_
#define SRC_API_CONFIG_H_

/**************************************/
/*  Configuration to be set by users  */
/**************************************/

/* ---------------------------------------------------------- */
/* 
   Input data empty interrupt configuration (for SRCIDCTRL.IEN)
   'Disable interrupt     (0)
   'Enable interrupt      (1)
*/
#define SRC_IEN         (0)   /* select a value among alternatives above */

/* ---------------------------------------------------------- */
/* 
   Output data empty interrupt configuration (for SRCODCTRL.OEN)
   'Disable interrupt     (0)
   'Enable interrupt      (1)
*/
#define SRC_OEN         (0)   /* select a value among alternatives above */

/* ---------------------------------------------------------- */
/* 
   Channel swap of output data (for SRCODCTRL.OCH)
   'same order of input data     (0) 
   'reverse order of input data  (1) 
*/
#define SRC_OCH         (0)  /* select a value among alternatives above */

/* ---------------------------------------------------------- */
/* 
    Configure condition when IINT flag to be set (for SRCIDCTRL.IFTRG)
    'Set flag when number of data in FIFO is 0 or less    (0)
    'Set flag when number of data in FIFO is 2 or less    (1)
    'Set flag when number of data in FIFO is 4 or less    (2)
    'Set flag when number of data in FIFO is 6 or less    (3)
*/
#define SRC_IFTG        (3)  /* select a value among alternatives above */

/* ---------------------------------------------------------- */
/* 
    Configure condition when OINT frag to be set (for SRCODCTRL.OFTRG)
    'Set flag when number of data in FIFO is 1 or larger    (0)
    'Set flag when number of data in FIFO is 4 or larger    (1)
    'Set flag when number of data in FIFO is 8 or larger    (2)
    'Set flag when number of data in FIFO is 12 or larger   (3)
*/
#define SRC_OFTG        (3)  /* select a value among alternatives above */

/* ============================================================== */
/* ============================================================== */

#endif /* SRC_API_CONFIG_H_ */

