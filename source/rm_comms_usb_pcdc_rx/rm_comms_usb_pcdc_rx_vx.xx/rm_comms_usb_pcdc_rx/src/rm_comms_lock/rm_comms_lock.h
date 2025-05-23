/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

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
