/*
* Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @file
 * @defgroup timer Timer Library
 * @{
 * @ingroup app_lib
 * @brief This library provides APIs for Software Timer.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 23.08.2019 1.00    First Release
***********************************************************************************************************************/

#include "r_ble_rx23w_if.h"

#ifndef R_BLE_TIMER_H
#define R_BLE_TIMER_H


/** @defgroup timer_macro Macros 
 *  @{
 *  @brief Macro definition
 */
/** The maximum number of timer slot. */
#define BLE_TIMER_NUM_OF_SLOT (10)

/** The invalid timer handle. */
#if (BSP_CFG_RTOS_USED == 0)
#define BLE_TIMER_INVALID_HDL (0xFF)
#else /* (BSP_CFG_RTOS_USED == 0) */
#define BLE_TIMER_INVALID_HDL ((uint32_t)NULL)
#define BLE_TIMER_INVALID_INDEX (0xFFFFFFFF)
#endif /* (BSP_CFG_RTOS_USED == 0) */

/** The timer type. */
typedef enum {
    BLE_TIMER_ONE_SHOT, /**< One shot timer type  */
    BLE_TIMER_PERIODIC  /**< Periodic timer type */
} e_ble_timer_type_t;
/*@}*/

/** @defgroup timer_callback Callbacks
 *  @{
 *  @brief Callback definition
 */
/** The timer callback invoked when the timer expired. */
typedef void (*ble_timer_cb_t)(uint32_t timer_hdl);
/*@}*/

/** @defgroup timer_func Functions
 *  @{
 *  @brief Function definition
 */
/******************************************************************************************************************//**
 * @brief Initialize the timer library.
 * @details This function should be called before calling any other timer library function.
 * @note Because abstraction API uses software timer, call R_BLE_TIMER_Init() before R_BLE_ABS_Init(). 
 **********************************************************************************************************************/
void R_BLE_TIMER_Init(void);

/******************************************************************************************************************//**
 * @brief Terminate the timer library.
 * @details This function should be called after deleting all the created timers.
 **********************************************************************************************************************/
void R_BLE_TIMER_Terminate(void);

/******************************************************************************************************************//**
 * @brief     Create a timer.
 * @details   The timer created is in inactive (stopped), to start the timer, call @ref R_BLE_TIMER_Start.
 *            After this function return SUCCESS, one timer slot is occupied.
 *            The maximum number of timer slot is specified with BLE_TIMER_NUM_OF_SLOT.
 * @param[out] p_timer_hdl output location for the timer handle.
 * @param[in]  timeout_ms The timer timeout in milli seconds.
 * @param[in]  type The timer type (@ref e_ble_timer_type_t).
 * @param[in]  cb The callback invoked when the timer is expired.
 * @retval    BLE_SUCCESS Success 
 * @retval    BLE_ERR_INVALID_ARG Some of arguments are invalid.
 * @retval    BLE_ERR_LIMIT_EXCEEDED No timer slot is available.
 **********************************************************************************************************************/
ble_status_t R_BLE_TIMER_Create(uint32_t *p_timer_hdl, uint32_t timeout_ms, uint8_t type, ble_timer_cb_t cb);

/******************************************************************************************************************//**
 * @brief Delete the timer.
 * @details If the timer is active, the timer is stopped and deleted.
 *          After this function returns SUCCESS, the timer slot is freed.
 * @param[in,out] timer_hdl Timer handle identifying the timer to be deleted and initialize with BLE_TIMER_INVALID_HDL.
 * @retval BLE_SUCCESS Success
 * @retval BLE_ERR_INVALID_HDL The timer handle is invalid.
 **********************************************************************************************************************/
ble_status_t R_BLE_TIMER_Delete(uint32_t *p_timer_hdl);

/******************************************************************************************************************//**
 * @brief Start the timer.
 * @details After starting, the timer will be expired at the timeout specified in
 *          @ref R_BLE_TIMER_Create or @ref R_BLE_TIMER_UpdateTimeout
 * @param[in] timer_hdl Timer handle identifying the timer to be started.
 * @retval BLE_SUCCESS Success
 * @retval BLE_ERR_INVALID_HDL The timer handle is invalid.
 **********************************************************************************************************************/
ble_status_t R_BLE_TIMER_Start(uint32_t timer_hdl);

/******************************************************************************************************************//**
 * @brief   Stop the timer.
 * @details When the timer is stopped, the remaining time is discarded.
 *          The timer can be started by calling @ref R_BLE_TIMER_Start.
 * @param[in] timer_hdl Timer handle identifying the timer to be stoped.
 * @retval BLE_SUCCESS Success
 * @retval  BLE_ERR_INVALID_HDL The timer handle is invalid.
 **********************************************************************************************************************/
ble_status_t R_BLE_TIMER_Stop(uint32_t timer_hdl);

/******************************************************************************************************************//**
 * @brief Update timeout of the timer.
 * @details If the timer is active, the timer stop and started with new timeout.
 * @param[in] timer_hdl Timer handle identifying the timer to be updated.
 * @param[in] timeout_ms The timeout to update in milli seconds.
 * @retval BLE_SUCCESS Success
 * @retval BLE_ERR_INVALID_HDL The timer handle is invalid.
 **********************************************************************************************************************/
ble_status_t R_BLE_TIMER_UpdateTimeout(uint32_t timer_hdl, uint32_t timeout_ms);

/*@}*/

#endif /* R_BLE_TIMER_H */

/** @} */
