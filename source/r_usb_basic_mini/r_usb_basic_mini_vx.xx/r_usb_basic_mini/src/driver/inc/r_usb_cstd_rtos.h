/*
* Copyright (c) 2020(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*******************************************************************************
* File Name    : r_usb_cstd_rtos.h
* Version      : 1.31
* Description  : Create tasks, mailboxes, memory pool for USB in freeRTOS.
******************************************************************************/
/*****************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 30.06.2020 1.20     First Release
*         : 20.03.2025 1.31     Changed the disclaimer.
******************************************************************************/

#ifndef R_USB_RTOS_H
#define R_USB_RTOS_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_usb_basic_mini_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"

#if BSP_CFG_RTOS_USED == 4      /* Renesas RI600V4 & RI600PX */
#include "kernel.h"
#include "kernel_id.h"
#endif /* BSP_CFG_RTOS_USED == 4 */

#if defined(USB_CFG_HMSC_USE)
#include "r_usb_hmsc_mini_if.h"
#endif /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_HCDC_USE)
#include "r_usb_hcdc.h"
#endif /* defined(USB_CFG_HCDC_USE) */

#if defined(USB_CFG_HHID_USE)
#include "r_usb_hhid.h"
#endif /* defined(USB_CFG_HHID_USE) */

#if BSP_CFG_RTOS_USED != 0      /* Use RTOS */
/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define QUEUE_SIZE              (16)

#if BSP_CFG_RTOS_USED == 1      /* FreeRTOS */
/** USB task's priority **/
#define HCD_TSK_PRI             (11)
#define MGR_TSK_PRI             (10)
#define PCD_TSK_PRI             (11)
#define PMSC_TSK_PRI            (8)
#define HCDC_TSK_PRI            (8)
#define HHID_TSK_PRI            (8)

#define usb_rtos_err_t          rtos_err_t
#define UsbRtos_Success         RTOS_SUCCESS

#elif BSP_CFG_RTOS_USED == 2    /* SEGGER embOS */
/** USB task's priority **/
#elif BSP_CFG_RTOS_USED == 3    /* Micrium MicroC/OS */
/** USB task's priority **/

/** USB mailbox's pointer to a message queue control block**/

/** USB mailbox's pointer to the name of the message queue **/

/** USB mailbox's specifies the size of each message in the queue.
 * Message size range from 1 32-bit word to 16 32-bit words.
 * Valid message size options are defined as follows **/

/** USB mailbox's starting address of the message queue **/

/** USB mailbox's total number of bytes available for the message queue **/

#elif BSP_CFG_RTOS_USED == 4    /* Renesas RI600V4 & RI600PX */
/** USB task's priority **/
#define HCD_TSK_PRI             (1)
#define MGR_TSK_PRI             (2)
#define PCD_TSK_PRI             (1)
#define PMSC_TSK_PRI            (4)
#define HCDC_TSK_PRI            (4)
#define HHID_TSK_PRI            (4)
#else
#endif  /* BSP_CFG_RTOS_USED == 1 */

/** USB task stack size in words **/
#define HCD_STACK_SIZE          (512)
#define MGR_STACK_SIZE          (512)
#define PCD_STACK_SIZE          (512)
#define PMSC_STACK_SIZE         (512)
#define HCDC_STACK_SIZE         (512)
#define HHID_STACK_SIZE         (512)

/** USB task stack size in words **/
#define STACK_SIZE              (512)

#define NUM_OF_BLOCK            (16u)
#define NUM_OF_MBX              (16u)
#define NUM_OF_TASK             (7)

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

extern  rtos_mbx_id_t   g_rtos_usb_hcd_mbx_id;
extern  rtos_mbx_id_t   g_rtos_usb_hcd_sub_mbx_id;
extern  rtos_mbx_id_t   g_rtos_usb_mgr_mbx_id;
extern  rtos_mbx_id_t   g_rtos_usb_cls_mbx_id;
extern  rtos_mbx_id_t   g_rtos_usb_hmsc_mbx_id;
extern  rtos_mbx_id_t   g_rtos_usb_hmsc_req_mbx_id;
extern  rtos_mbx_id_t   g_rtos_usb_hhid_mbx_id;

extern  rtos_mbx_id_t   g_rtos_usb_pcd_mbx_id;
extern  rtos_mbx_id_t   g_rtos_usb_pcd_sub_mbx_id;

extern  rtos_mbx_id_t   g_rtos_usb_pmsc_mbx_id;

extern  rtos_sem_id_t   g_rtos_usb_hmsc_sem_id;

extern  rtos_mem_id_t   g_rtos_usb_mpf_id;

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
rtos_err_t usb_rtos_configuration(void);
rtos_err_t usb_rtos_unconfiguration(void);
#endif /* BSP_CFG_RTOS_USED != 0 */
#endif /* R_USB_RTOS_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/


