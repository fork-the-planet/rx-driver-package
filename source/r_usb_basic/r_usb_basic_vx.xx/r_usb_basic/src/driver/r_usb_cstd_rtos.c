/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*******************************************************************************
* File Name    : r_usb_cstd_rtos.c
* Version      : 1.44
* Description  : Create tasks, mailboxes, memory pool for USB in freeRTOS.
******************************************************************************/
/*****************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.06.2016 1.00     First Release
*         : 16.11.2018 1.24     Supporting RTOS Thread safe
*         : 01.03.2020 1.30     RX72N/RX66N is added and uITRON is supported.
*         : 30.06.2022 1.40     USBX PCDC is supported.
*         : 30.10.2022 1.41     USBX HMSC is supported.
*         : 30.09.2023 1.42     USBX HCDC is supported.
*         : 01.03.2025 1.44     Change Disclaimer.
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
#include "r_rtos_abstract.h"
#include "r_usb_cstd_rtos.h"
#if (BSP_CFG_RTOS_USED == 4)        /* Renesas RI600V4 & RI600PX */
#include "kernel_id.h"
#endif /* (BSP_CFG_RTOS_USED == 4) */
#endif /* (BSP_CFG_RTOS_USED != 0) */

#if (BSP_CFG_RTOS_USED != 0)        /* Use RTOS */
/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/

/******************************************************************************
 Exported global variables (to be accessed by other files)
 *****************************************************************************/
rtos_mem_id_t       g_rtos_usb_mpf_id;
 #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static  rtos_task_id_t  g_rtos_usb_hcd_task_id;
static  rtos_task_id_t  g_rtos_usb_mgr_task_id;

#if (USB_CFG_HUB == USB_CFG_ENABLE)
static  rtos_task_id_t  g_rtos_usb_hub_task_id;
rtos_mbx_id_t       g_rtos_usb_hub_mbx_id;
#endif  /* USB_CFG_HUB == USB_CFG_ENABLE */

rtos_mbx_id_t       g_rtos_usb_hcd_mbx_id;
rtos_mbx_id_t       g_rtos_usb_hcd_sub_mbx_id;
rtos_mbx_id_t       g_rtos_usb_hcd_sub_addr_mbx_id;
rtos_mbx_id_t       g_rtos_usb_mgr_mbx_id;
rtos_mbx_id_t       g_rtos_usb_cls_mbx_id;

  #if defined(USB_CFG_HMSC_USE)
rtos_mbx_id_t       g_rtos_usb_hmsc_mbx_id;
rtos_mbx_id_t       g_rtos_usb_hmsc_req_mbx_id;
rtos_sem_id_t       g_rtos_usb_hmsc_sem_id;
  #endif /* defined(USB_CFG_HMSC_USE) */

  #if defined(USB_CFG_HHID_USE)
rtos_mbx_id_t       g_rtos_usb_hhid_mbx_id;
  #endif /* defined(USB_CFG_HHID_USE) */

 #endif  /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

 #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
static  rtos_task_id_t      g_rtos_usb_pcd_task_id;

rtos_mbx_id_t       g_rtos_usb_pcd_mbx_id;
rtos_mbx_id_t       g_rtos_usb_pcd_sub_mbx_id;
  #if defined(USB_CFG_PMSC_USE)
static  rtos_task_id_t      g_rtos_usb_pmsc_task_id;
rtos_mbx_id_t               g_rtos_usb_pmsc_mbx_id;
  #endif /* defined(USB_CFG_PMSC_USE) */

 #endif /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

 #if (BSP_CFG_RTOS_USED != 4)    /* Excluding Renesas RI600V4 & RI600PX */
  #if (BSP_CFG_RTOS_USED == 5)    /* Azure RTOS */
static uint8_t      g_usb_rtos_fixed_memblk[((sizeof(usb_utr_t) + sizeof(void *)) * NUM_OF_BLOCK)];
   #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
static uint8_t      g_rtos_usb_pcd_mbx[sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE)];
static uint8_t      g_rtos_usb_pcd_sub_mbx[sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE)];
static uint8_t      g_rtos_usb_pcd_stack[PCD_STACK_SIZE];
   #endif /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */
   #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
static uint8_t      g_rtos_usb_hcd_mbx[sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE)];
static uint8_t      g_rtos_usb_mgr_mbx[sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE)];
static uint8_t      g_rtos_usb_hcd_sub_mbx[sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE)];
static uint8_t      g_rtos_usb_hcd_sub_addr_mbx[sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE)];
static uint8_t      g_rtos_usb_cls_mbx[sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE)];
static uint8_t      g_rtos_usb_hcd_stack[HCD_STACK_SIZE];
static uint8_t      g_rtos_usb_mgr_stack[MGR_STACK_SIZE];
   #endif /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

  #else  /* (BSP_CFG_RTOS_USED == 5) */
static usb_utr_t    g_usb_rtos_fixed_memblk[NUM_OF_BLOCK];
  #endif /* (BSP_CFG_RTOS_USED == 5) */
 #endif /* (BSP_CFG_RTOS_USED != 4) */

/******************************************************************************
* Function Name: usb_rtos_configuration
* Description  : Create mailboxes, memory pool using for the created tasks
*                in usb system.
* Arguments    : None
* Return Value : USB_RTOS_SUCCESS -
*                   Successful.
*                UsbRtos_Err_Init_Mbx -
*                   Failed in mailbox allocation.
*                UsbRtos_Err_Init_Mpl -
*                   Failed in memory pool allocation.
******************************************************************************/
rtos_err_t usb_rtos_configuration(void)
{
    rtos_err_t ret      = RTOS_SUCCESS;
 #if (BSP_CFG_RTOS_USED != 4)         /* Excluding Renesas RI600V4 & RI600PX */
    rtos_mpf_info_t     mpf_info;
    rtos_task_info_t    task_info;
    rtos_mbx_info_t     mbx_info;
 #endif /* (BSP_CFG_RTOS_USED != 4) */

 #if     (BSP_CFG_RTOS_USED == 1)    /* FreeRTOS */
    /* Fix Memory Pool Creation */
    mpf_info.p_mempool      = (void *)g_usb_rtos_fixed_memblk;
    mpf_info.block_number   = NUM_OF_BLOCK;
    mpf_info.block_size     = sizeof(usb_utr_t);
    rtos_create_fixed_memory(&g_rtos_usb_mpf_id, &mpf_info);

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    /* Mailbox Creation*/
    mbx_info.length         = QUEUE_SIZE;
    rtos_create_mailbox(&g_rtos_usb_hcd_mbx_id, &mbx_info);             /* For HCD */
    rtos_create_mailbox(&g_rtos_usb_hcd_sub_mbx_id, &mbx_info);         /* For HCD Sub */
    rtos_create_mailbox(&g_rtos_usb_hcd_sub_addr_mbx_id, &mbx_info);    /* For HCD Sub ADDR */
    rtos_create_mailbox(&g_rtos_usb_mgr_mbx_id, &mbx_info);             /* For MGR */
   #if (USB_CFG_HUB == USB_CFG_ENABLE)
    rtos_create_mailbox(&g_rtos_usb_hub_mbx_id, &mbx_info);             /* For HUB */
   #endif  /* USB_CFG_HUB == USB_CFG_ENABLE */
    rtos_create_mailbox(&g_rtos_usb_cls_mbx_id, &mbx_info);             /* For CLS */
   #if defined(USB_CFG_HMSC_USE)
    rtos_create_mailbox(&g_rtos_usb_hmsc_mbx_id, &mbx_info);            /* For HMSC Mailbox */
    rtos_create_mailbox(&g_rtos_usb_hmsc_req_mbx_id, &mbx_info);        /* For HMSC Req Mailbox */
    rtos_create_semaphore(&g_rtos_usb_hmsc_sem_id, (rtos_sem_info_t *)NULL);    /* HMSC Semaphore */
   #endif /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HHID_USE)
    rtos_create_mailbox(&g_rtos_usb_hhid_mbx_id, &mbx_info);            /* For HHID */
   #endif /* defined(USB_CFG_HHID_USE) */

    /* Task Creation */
    /** For HCD **/
    task_info.task_code     = (TaskFunction_t)usb_hstd_hcd_task;
    task_info.p_name        = "HCD_TSK";
    task_info.stack_depth   = STACK_SIZE;
    task_info.p_parameter     = (void *)NULL;
    task_info.priority      = HCD_TSK_PRI;
    rtos_create_task(&g_rtos_usb_hcd_task_id, &task_info);

    /** For MGR **/
    task_info.task_code     = (TaskFunction_t)usb_hstd_mgr_task;
    task_info.p_name        = "MGR_TSK";
    task_info.stack_depth   = STACK_SIZE;
    task_info.p_parameter     = (void *)NULL;
    task_info.priority      = MGR_TSK_PRI;
    rtos_create_task(&g_rtos_usb_mgr_task_id, &task_info);

   #if (USB_CFG_HUB == USB_CFG_ENABLE)
    /** For Hub **/
    task_info.task_code     = (TaskFunction_t)usb_hstd_hub_task;
    task_info.p_name        = "HUB_TSK";
    task_info.stack_depth   = STACK_SIZE;
    task_info.p_parameter     = (void *)NULL;
    task_info.priority      = HUB_TSK_PRI;
    rtos_create_task(&g_rtos_usb_hub_task_id, &task_info);
   #endif  /* USB_CFG_HUB == USB_CFG_ENABLE */
  #endif /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    /* Mailbox Creation */
    mbx_info.length         = QUEUE_SIZE;
    rtos_create_mailbox(&g_rtos_usb_pcd_mbx_id, &mbx_info);             /* For PCD */
    rtos_create_mailbox(&g_rtos_usb_pcd_sub_mbx_id, &mbx_info);         /* For PCD Sub */

   #if defined(USB_CFG_PMSC_USE)
    /* Mailbox Creation */
    mbx_info.length         = QUEUE_SIZE;
    rtos_create_mailbox(&g_rtos_usb_pmsc_mbx_id, &mbx_info);             /* For PMSC */
    task_info.task_code     = (TaskFunction_t)usb_pmsc_task;
    task_info.p_name        = "PMSC_TSK";
    task_info.stack_depth   = STACK_SIZE;
    task_info.p_parameter   = (void *)NULL;
    task_info.priority      = PMSC_TSK_PRI;
    rtos_create_task(&g_rtos_usb_pmsc_task_id, &task_info);

   #endif /* defined(USB_CFG_PMSC_USE) */

    /* Task Creation */
    /** For PCD **/
    task_info.task_code     = (TaskFunction_t)usb_pstd_pcd_task;
    task_info.p_name        = "PCD_TSK";
    task_info.stack_depth   = STACK_SIZE;
    task_info.p_parameter     = (void *)NULL;
    task_info.priority      = PCD_TSK_PRI;
    rtos_create_task(&g_rtos_usb_pcd_task_id, &task_info);
  #endif /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */

 #elif   BSP_CFG_RTOS_USED == 2                                          /* SEGGER embOS */
 #elif   BSP_CFG_RTOS_USED == 3                                          /* Micrium MicroC/OS */
 #elif   BSP_CFG_RTOS_USED == 4                                          /* Renesas RI600V4 & RI600PX */
    g_rtos_usb_mpf_id               = ID_USB_RTOS_DRIVER_MPF;

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    g_rtos_usb_hcd_mbx_id           = ID_USB_RTOS_HCD_MBX;
    g_rtos_usb_hcd_sub_mbx_id       = ID_USB_RTOS_HCD_SUB_MBX;
    g_rtos_usb_hcd_sub_addr_mbx_id  = ID_USB_RTOS_HCD_SUB_ADDR_MBX;
    g_rtos_usb_mgr_mbx_id           = ID_USB_RTOS_MGR_MBX;
    g_rtos_usb_cls_mbx_id           = ID_USB_RTOS_CLS_MBX;
   #if defined(USB_CFG_HMSC_USE)
    g_rtos_usb_hmsc_mbx_id          = ID_USB_RTOS_HMSC_MBX;
    g_rtos_usb_hmsc_req_mbx_id      = ID_USB_RTOS_HMSC_REQ_MBX;
    g_rtos_usb_hmsc_sem_id          = ID_USB_RTOS_HMSC_SEM;
   #endif /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HHID_USE)
    g_rtos_usb_hhid_mbx_id          = ID_USB_RTOS_HID_MBX;
   #endif /* defined(USB_CFG_HHID_USE) */

   #if USB_CFG_HUB == USB_CFG_ENABLE
    g_rtos_usb_hub_mbx_id           = ID_USB_RTOS_HUB_MBX;
   #endif /* USB_CFG_HUB == USB_CFG_ENABLE */

    g_rtos_usb_hcd_task_id           = ID_USB_RTOS_HCD_TSK;
    g_rtos_usb_mgr_task_id           = ID_USB_RTOS_MGR_TSK;
   #if (USB_CFG_HUB == USB_CFG_ENABLE)
    g_rtos_usb_hub_task_id           = ID_USB_RTOS_HUB_TSK;
   #endif  /* USB_CFG_HUB == USB_CFG_ENABLE */
  #endif  /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    g_rtos_usb_pcd_mbx_id           = ID_USB_RTOS_PCD_MBX;
    g_rtos_usb_pcd_sub_mbx_id       = ID_USB_RTOS_PCD_SUB_MBX;

   #if defined(USB_CFG_PMSC_USE)
    g_rtos_usb_pmsc_mbx_id          = ID_USB_RTOS_PMSC_MBX;
    g_rtos_usb_pmsc_task_id         = ID_USB_RTOS_PMSC_TSK;
   #endif /* defined(USB_CFG_PMSC_USE) */

    g_rtos_usb_pcd_task_id          = ID_USB_RTOS_PCD_TSK;

  #endif  /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    rtos_start_task (&g_rtos_usb_hcd_task_id);
    rtos_start_task (&g_rtos_usb_mgr_task_id);
   #if (USB_CFG_HUB == USB_CFG_ENABLE)
    rtos_start_task (&g_rtos_usb_hub_task_id);
   #endif  /* USB_CFG_HUB == USB_CFG_ENABLE */
  #endif /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    rtos_start_task (&g_rtos_usb_pcd_task_id);

   #if defined(USB_CFG_PMSC_USE)
    rtos_start_task (&g_rtos_usb_pmsc_task_id);
   #endif /* defined(USB_CFG_PMSC_USE) */

  #endif  /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

 #elif   BSP_CFG_RTOS_USED == 5                                          /* Azure RTOS */
    /* Fix Memory Pool Creation */
    mpf_info.p_name         = "USB_MEM_BLOCK";
    mpf_info.block_size     = sizeof(usb_utr_t);
    mpf_info.p_pool_start   = (VOID *)&g_usb_rtos_fixed_memblk;
    mpf_info.pool_size      = (uint32_t) ((sizeof(usb_utr_t) + sizeof(void *)) * NUM_OF_BLOCK);
    rtos_create_fixed_memory(&g_rtos_usb_mpf_id, &mpf_info);

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    mbx_info.p_name         = "USB_HCD_MBX";
    mbx_info.message_size   = TX_1_ULONG;
    mbx_info.p_queue_start  = (VOID *)&g_rtos_usb_hcd_mbx[0];
    mbx_info.queue_size     = (sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE));
    rtos_create_mailbox(&g_rtos_usb_hcd_mbx_id, &mbx_info);             /* For HCD */

    mbx_info.p_name         = "USB_HCD_SUB_MBX";
    mbx_info.message_size   = TX_1_ULONG;
    mbx_info.p_queue_start  = (VOID *)&g_rtos_usb_hcd_sub_mbx[0];
    mbx_info.queue_size     = (sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE));
    rtos_create_mailbox(&g_rtos_usb_hcd_sub_mbx_id, &mbx_info);         /* For HCD Sub */

    mbx_info.p_name         = "USB_HCD_SUB_ADDR_MBX";
    mbx_info.message_size   = TX_1_ULONG;
    mbx_info.p_queue_start  = (VOID *)&g_rtos_usb_hcd_sub_addr_mbx[0];
    mbx_info.queue_size     = (sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE));
    rtos_create_mailbox(&g_rtos_usb_hcd_sub_addr_mbx_id, &mbx_info);    /* For HCD Sub ADDR */

    mbx_info.p_name         = "USB_MGR_MBX";
    mbx_info.message_size   = TX_1_ULONG;
    mbx_info.p_queue_start  = (VOID *)&g_rtos_usb_mgr_mbx[0];
    mbx_info.queue_size     = (sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE));
    rtos_create_mailbox(&g_rtos_usb_mgr_mbx_id, &mbx_info);             /* For MGR */

    mbx_info.p_name         = "USB_CLS_MBX";
    mbx_info.message_size   = TX_1_ULONG;
    mbx_info.p_queue_start  = (VOID *)&g_rtos_usb_cls_mbx[0];
    mbx_info.queue_size     = (sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE));
    rtos_create_mailbox(&g_rtos_usb_cls_mbx_id, &mbx_info);             /* For CLS */

    task_info.p_name        = "HCD_TSK";
    task_info.p_entry_func  = usb_hstd_hcd_task;
    task_info.entry_input   = (ULONG) NULL;
    task_info.p_stack_start = (VOID *) &g_rtos_usb_hcd_stack[0];
    task_info.stack_size    = HCD_STACK_SIZE;
    task_info.priority      = HCD_TSK_PRI;
    task_info.preempt_threshold = HCD_TSK_PRI;
    task_info.time_slice    = TX_NO_TIME_SLICE;
    task_info.auto_start    = TX_AUTO_START;
    rtos_create_task(&g_rtos_usb_hcd_task_id, &task_info);

    task_info.p_name        = "MGR_TSK";
    task_info.p_entry_func  = usb_hstd_mgr_task;
    task_info.entry_input   = (ULONG) NULL;
    task_info.p_stack_start = (VOID *) &g_rtos_usb_mgr_stack[0];
    task_info.stack_size    = MGR_STACK_SIZE;
    task_info.priority      = MGR_TSK_PRI;
    task_info.preempt_threshold = MGR_TSK_PRI;
    task_info.time_slice    = TX_NO_TIME_SLICE;
    task_info.auto_start    = TX_AUTO_START;
    rtos_create_task(&g_rtos_usb_mgr_task_id, &task_info);
  #endif /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    mbx_info.p_name         = "USB_PCD_MBX";
    mbx_info.message_size   = TX_1_ULONG;
    mbx_info.p_queue_start  = (VOID *)&g_rtos_usb_pcd_mbx[0];
    mbx_info.queue_size     = (sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE));
    rtos_create_mailbox(&g_rtos_usb_pcd_mbx_id, &mbx_info);

    mbx_info.p_name         = "USB_PCD_SUB_MBX";
    mbx_info.message_size   = TX_1_ULONG;
    mbx_info.p_queue_start  = (VOID *)&g_rtos_usb_pcd_sub_mbx[0];
    mbx_info.queue_size     = (sizeof(ULONG) * (TX_1_ULONG) * (QUEUE_SIZE));
    rtos_create_mailbox(&g_rtos_usb_pcd_sub_mbx_id, &mbx_info);

    task_info.p_name        = "PCD_TSK";
    task_info.p_entry_func  = usb_pstd_pcd_task;
    task_info.entry_input   = (ULONG) NULL;
    task_info.p_stack_start = (VOID *) &g_rtos_usb_pcd_stack[0];
    task_info.stack_size    = PCD_STACK_SIZE;
    task_info.priority      = PCD_TSK_PRI;
    task_info.preempt_threshold = PCD_TSK_PRI;
    task_info.time_slice    = TX_NO_TIME_SLICE;
    task_info.auto_start    = TX_AUTO_START;
    rtos_create_task(&g_rtos_usb_pcd_task_id, &task_info);
  #endif /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */
 #endif  /* BSP_CFG_RTOS_USED == 1/2/3/4/5 */

    return ret;
} /* End of function usb_rtos_configuration() */

/******************************************************************************
* Function Name: usb_rtos_unconfiguration
* Description  : Create mailboxes, memory pool using for the created tasks
*                in usb system.
* Arguments    : None
* Return Value : USB_RTOS_SUCCESS -
*                   Successful.
*                UsbRtos_Err_Init_Mbx -
*                   Failed in mailbox allocation.
*                UsbRtos_Err_Init_Mpl -
*                   Failed in memory pool allocation.
******************************************************************************/
rtos_err_t usb_rtos_unconfiguration(void)
{
    rtos_err_t ret      = RTOS_SUCCESS;

 #if (BSP_CFG_RTOS_USED == 1)  /* FreeRTOS */
    /* Fix Memory Pool */
    rtos_delete_fixed_memory(&g_rtos_usb_mpf_id);

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    /* Terminate Task */
    rtos_terminate_task(&g_rtos_usb_hcd_task_id);           /* For HCD */
    rtos_terminate_task(&g_rtos_usb_mgr_task_id);           /* For MGR */
   #if (USB_CFG_HUB == USB_CFG_ENABLE)
    rtos_terminate_task(&g_rtos_usb_hub_task_id);           /* For Hub */
   #endif   /* USB_CFG_HUB == USB_CFG_ENABLE */

    /* Delete Task */
    rtos_delete_task(&g_rtos_usb_hcd_task_id);              /* For HCD */
    rtos_delete_task(&g_rtos_usb_mgr_task_id);              /* For MGR */
   #if (USB_CFG_HUB == USB_CFG_ENABLE)
    rtos_delete_task(&g_rtos_usb_hub_task_id);              /* For HUB */
   #endif   /* USB_CFG_HUB == USB_CFG_ENABLE */
   #if defined(USB_CFG_HHID_USE)
    rtos_delete_mailbox(&g_rtos_usb_hhid_mbx_id);            /* For HHID */
   #endif /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HMSC_USE)
    /* Delete Semaphore */
    rtos_delete_semaphore(&g_rtos_usb_hmsc_sem_id);         /* For HMSC Semaphore */

    /* Delete Mailbox */
    rtos_delete_mailbox(&g_rtos_usb_hmsc_mbx_id);           /* For HMSC Mailbox */
    rtos_delete_mailbox(&g_rtos_usb_hmsc_req_mbx_id);       /* For HMSC Req Mailbox */
   #endif /* defined(USB_CFG_HMSC_USE) */

    /* Delete Mailbox */
    rtos_delete_mailbox(&g_rtos_usb_hcd_mbx_id);            /* For HCD */
    rtos_delete_mailbox(&g_rtos_usb_hcd_sub_mbx_id);        /* For HCD Sub */
    rtos_delete_mailbox(&g_rtos_usb_hcd_sub_addr_mbx_id);   /* For HCD Sub ADDR */
    rtos_delete_mailbox(&g_rtos_usb_mgr_mbx_id);            /* For MGR */
   #if (USB_CFG_HUB == USB_CFG_ENABLE)
    rtos_delete_mailbox(&g_rtos_usb_hub_mbx_id);            /* For HUB */
   #endif   /* USB_CFG_HUB == USB_CFG_ENABLE */
    rtos_delete_mailbox(&g_rtos_usb_cls_mbx_id);            /* For CLS */

  #endif /* ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST ) */

  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)

    /* Terminate Task */
    rtos_terminate_task(&g_rtos_usb_pcd_task_id);           /* For PCD */

    /* Delete Task */
    rtos_delete_task(&g_rtos_usb_pcd_task_id);              /* For PCD */
   #if defined(USB_CFG_PMSC_USE)
    /* Delete Mailbox */
    rtos_delete_mailbox(&g_rtos_usb_pmsc_mbx_id);           /* For PMSC */

    /* Terminate Task */
    rtos_terminate_task(&g_rtos_usb_pmsc_task_id);          /* For PMSC */

    /* Delete Task */
    rtos_delete_task(&g_rtos_usb_pmsc_task_id);             /* For PMSC */
   #endif /* defined(USB_CFG_PMSC_USE) */

    /* Delete Mailbox */
    rtos_delete_mailbox(&g_rtos_usb_pcd_mbx_id);            /* For PCD */
    rtos_delete_mailbox(&g_rtos_usb_pcd_sub_mbx_id);        /* For PCD Sub */

  #endif /* ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI ) */

 #elif   BSP_CFG_RTOS_USED == 2                              /* SEGGER embOS */
 #elif   BSP_CFG_RTOS_USED == 3                              /* Micrium MicroC/OS */
 #elif   BSP_CFG_RTOS_USED == 4                              /* Renesas RI600V4 & RI600PX */
    g_rtos_usb_mpf_id               = USB_NULL;

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    /* Terminate Task */
    rtos_terminate_task(&g_rtos_usb_hcd_task_id);           /* For HCD */
    rtos_terminate_task(&g_rtos_usb_mgr_task_id);           /* For MGR */
   #if (USB_CFG_HUB == USB_CFG_ENABLE)
    rtos_terminate_task(&g_rtos_usb_hub_task_id);           /* For Hub */
   #endif   /* USB_CFG_HUB == USB_CFG_ENABLE */

    g_rtos_usb_hcd_mbx_id           = USB_NULL;
    g_rtos_usb_hcd_sub_mbx_id       = USB_NULL;
    g_rtos_usb_hcd_sub_addr_mbx_id  = USB_NULL;
    g_rtos_usb_mgr_mbx_id           = USB_NULL;
    g_rtos_usb_cls_mbx_id           = USB_NULL;
   #if defined(USB_CFG_HMSC_USE)
    g_rtos_usb_hmsc_mbx_id          = USB_NULL;
    g_rtos_usb_hmsc_req_mbx_id      = USB_NULL;
    g_rtos_usb_hmsc_sem_id          = USB_NULL;
   #endif /* defined(USB_CFG_HMSC_USE) */

   #if defined(USB_CFG_HHID_USE)
    g_rtos_usb_hhid_mbx_id          = USB_NULL;
   #endif /* defined(USB_CFG_HHID_USE) */

  #endif  /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    /* Terminate Task */
    rtos_terminate_task(&g_rtos_usb_pcd_task_id);           /* For PCD */

    g_rtos_usb_pcd_mbx_id           = USB_NULL;
    g_rtos_usb_pcd_sub_mbx_id       = USB_NULL;

   #if defined(USB_CFG_PMSC_USE)
    g_rtos_usb_pmsc_mbx_id          = USB_NULL;
   #endif /* defined(USB_CFG_PMSC_USE) */

  #endif  /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

 #elif   BSP_CFG_RTOS_USED == 5     /* Azure RTOS */
    rtos_task_priority_t current_task_pri;

    rtos_disable_dispatch(&current_task_pri);

  #if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
    /* Delete Mailbox */
    rtos_delete_mailbox(&g_rtos_usb_hcd_mbx_id);            /* For HCD */
    rtos_delete_mailbox(&g_rtos_usb_mgr_mbx_id);            /* For MGR */
    rtos_delete_mailbox(&g_rtos_usb_cls_mbx_id);            /* For CLS */

    /* Terminate Task */
    rtos_terminate_task(&g_rtos_usb_hcd_task_id);           /* For HCD */
    rtos_terminate_task(&g_rtos_usb_mgr_task_id);           /* For MGR */

    /* Delete Task */
    rtos_delete_task(&g_rtos_usb_hcd_task_id);              /* For HCD */
    rtos_delete_task(&g_rtos_usb_mgr_task_id);              /* For MGR */
  #endif /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

  #if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
    /* Delete Mailbox */
    rtos_delete_mailbox(&g_rtos_usb_pcd_mbx_id);            /* For PCD */
    rtos_delete_mailbox(&g_rtos_usb_pcd_sub_mbx_id);        /* For PCD Sub */

    /* Terminate Task */
    rtos_terminate_task(&g_rtos_usb_pcd_task_id);           /* For PCD */
    /* Delete Task */
    rtos_delete_task(&g_rtos_usb_pcd_task_id);              /* For PCD */
  #endif /* ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI) */

    rtos_enable_dispatch(current_task_pri);
 #endif  /* (BSP_CFG_RTOS_USED == 5) */

    return ret;
} /* End of function usb_rtos_unconfiguration() */
#endif /* (BSP_CFG_RTOS_USED != 0) */
/******************************************************************************
 End  Of File
 *****************************************************************************/

