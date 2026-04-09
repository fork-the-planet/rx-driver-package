/*
 * Copyright (C) 2024 - 2025 Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef RM_COMMS_LOCK_H
#define RM_COMMS_LOCK_H

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #include "platform.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL78__)
 #include <stddef.h>
 #include <stdbool.h>
 #include "r_cg_macrodriver.h"
 #include "r_fsp_error.h"
#else
 #include "bsp_api.h"
#endif


#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
 #if BSP_CFG_RTOS_USED == 1            // FreeRTOS
  #define BSP_CFG_RTOS    2
 #elif BSP_CFG_RTOS_USED == 5          // ThreadX
  #define BSP_CFG_RTOS    1
 #else
  #define BSP_CFG_RTOS    0
 #endif
#elif defined(__CCRL__) || defined(__ICCRL__) || defined(__RL78__)
  #define BSP_CFG_RTOS    0
#endif


#if BSP_CFG_RTOS

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

 #if BSP_CFG_RTOS == 1                 // ThreadX
  #include    "tx_api.h"
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
  #include    "FreeRTOS.h"
  #include    "task.h"
  #include    "queue.h"
  #include    "semphr.h"
 #else
 #endif

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Mutex structure */
typedef struct st_rm_comms_mutex
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    TX_MUTEX handle;
    CHAR   * p_name;
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    SemaphoreHandle_t handle;
    StaticSemaphore_t buffer;
 #else
 #endif
} rm_comms_mutex_t;

/* Semaphore Structure */
typedef struct st_rm_comms_semaphore
{
 #if BSP_CFG_RTOS == 1                 // ThreadX
    TX_SEMAPHORE handle;
    CHAR       * p_name;
 #elif BSP_CFG_RTOS == 2               // FreeRTOS
    SemaphoreHandle_t handle;
    StaticSemaphore_t buffer;
 #else
 #endif
} rm_comms_semaphore_t;

/**********************************************************************************************************************
 * @brief rm_comms_lock API
 *
 * @retval FSP_SUCCESS              Funciton call succeeds.
 * @retval FSP_ERR_INTERNAL         RTOS internal error.
 * @retval FSP_ERR_UNSUPPORTED      RTOS not supported.
 *********************************************************************************************************************/
fsp_err_t rm_comms_recursive_mutex_initialize(rm_comms_mutex_t * p_mutex);
fsp_err_t rm_comms_recursive_mutex_destroy(rm_comms_mutex_t * p_mutex);
fsp_err_t rm_comms_recursive_mutex_acquire(rm_comms_mutex_t * p_mutex, uint32_t const timeout);
fsp_err_t rm_comms_recursive_mutex_release(rm_comms_mutex_t * p_mutex);

fsp_err_t rm_comms_semaphore_initialize(rm_comms_semaphore_t * p_semaphore);
fsp_err_t rm_comms_semaphore_destroy(rm_comms_semaphore_t * p_semaphore);
fsp_err_t rm_comms_semaphore_acquire(rm_comms_semaphore_t * p_semaphore, uint32_t const timeout);
fsp_err_t rm_comms_semaphore_release(rm_comms_semaphore_t * p_semaphore);

#endif /* BSP_CFG_RTOS */

#endif /* RM_COMMS_LOCK_H */
