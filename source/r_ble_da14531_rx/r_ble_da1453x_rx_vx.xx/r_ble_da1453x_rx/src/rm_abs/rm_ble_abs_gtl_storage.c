/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "rm_ble_abs_gtl_storage.h"
#ifdef CRYPTO_ENABLED
#include "rm_ble_abs_gtl_sw_aes_api.h"
#endif

/***********************************************************************************************************************
 * NOTES
 * ----------------------------------------------------
 * Both variables described below are used in the VEE driver.
 * User needs to set appropriate names using the Configurator.
 * These are stored in hal_data.h
 * g_vee_ctrl is the control structure for the VEE driver
 * g_vee_cfg is the configuration structure for the VEE driver
 *
 * The name of the VEE driver instance must be set in the Configurator.
 * ra_gen\ble_thread.h
 * the name for the should be set to: extern const rm_vee_instance_t g_vee;
 **********************************************************************************************************************/
#ifdef ENABLE_STORAGE

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/* capture callback event.*/
static volatile bool g_write_flag = false;

 #ifdef CRYPTO_ENABLED
extern crypto_env_t rm_ble_abs_gtl_aes_env;
uint8_t             usr_key[16] =
{
    0x3d, 0xaf, 0xba, 0x42, 0x9d, 0x9e, 0xb4, 0x30, 0xb4, 0x22, 0xda, 0x80, 0x2c, 0x9f, 0xac, 0x41
};
 #endif

/*******************************************************************************************************************//**
 *  Wrappper for memory allocate function.
 *
 * @param[in]  size     Size of memory to be allocated (in bytes)
 * @retval NULL         Memory not allocated
 * @retval Address      Address of memory allocated
 **********************************************************************************************************************/
static void * rm_ble_gtl_malloc (uint32_t size)
{
 #if (BSP_CFG_RTOS == 2)               /* FreeRTOS */
    return pvPortMalloc(size);
 #elif (BSP_CFG_RTOS == 0)             /* Baremetal */
    void * p_mem = NULL;
    p_mem = malloc(size);
    memset(p_mem, 0, size);

    return p_mem;
 #else

    return NULL;                       // ThreadX is not supported, so this is a placeholder
 #endif
}

/*******************************************************************************************************************//**
 *  Wrapper for free memory allocation function.
 *
 * @param[in]  p_mem    Pointer to memory to be freed
 **********************************************************************************************************************/
static void rm_ble_gtl_free (void * p_mem)
{
 #if (BSP_CFG_RTOS == 2)               /* FreeRTOS */
    vPortFree(p_mem);
 #elif (BSP_CFG_RTOS == 0)             /* Baremetal */
    free(p_mem);
 #else

    return NULL;                       // ThreadX is not supported, so this is a placeholder
 #endif
}

/*******************************************************************************************************************//**
 *  Generate a blocking delay.
 *
 * @param[in]  ms       Length of delay in milliseconds
 **********************************************************************************************************************/
void rm_ble_gtl_delay (uint32_t ms)
{
 #if (BSP_CFG_RTOS == 2)               /* FreeRTOS */
    vTaskDelay(pdMS_TO_TICKS(ms));
 #elif (BSP_CFG_RTOS == 1)             /* ThreadX */
    tx_thread_sleep((ms * TX_TIMER_TICKS_PER_SECOND) / R_BLE_GTL_MS_PER_SECOND);
 #elif (BSP_CFG_RTOS == 0)             /* Baremetal */
    R_BSP_SoftwareDelay(ms, BSP_DELAY_MILLISECS);
 #endif
}

/*******************************************************************************************************************//**
 * Wait for the Virtual EEPROM callback to indicate that it has finished writing data
 * and vee flash is in ready state.
 * @retval     fsp_err_t   Status of the operation.
 * @note        This function waits for the Virtual EEPROM callback to indicate that it has finished writing data
 * and vee flash is in ready state. 
 * If the callback event does not occur within a certain time, it returns a timeout error.
 **********************************************************************************************************************/
fsp_err_t wr_timeout (uint8_t delay_ms)
{
    fsp_err_t err            = FSP_SUCCESS;
    int32_t   write_time_out = delay_ms;
    e_flash_dm_status_t ret;
    uint32_t status;

    /* Wait for the Virtual EEPROM callback to indicate that it has finished writing data
     * and vee flash is in ready state. */
    do
    {
        /* Delay 1ms each time */
        rm_ble_gtl_delay(1);

        /* Get the current status of the driver.*/
        ret = R_FLASH_DM_Control(FLASH_DM_GET_STATUS, &status);
        if (FLASH_DM_SUCCESS != ret)
        {
            return FSP_ERR_ASSERTION;
        }
    } while ((FLASH_DM_ACT_IDLE != status) && (ZERO_VALUE < --write_time_out));

    if (ZERO_VALUE == write_time_out)
    {
        return FSP_ERR_TIMEOUT;
    }

    /* Reset the flag.*/
    g_write_flag = false;

    return err;
}

/*******************************************************************************************************************//**
* Initialize the data flash management module.
 **********************************************************************************************************************/
e_flash_dm_status_t RM_DATFRX_Init()
{
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

#if(FLASH_TYPE == FLASH_TYPE_1)
    /* ==== INITIALIZE ==== */
    ret = R_FLASH_DM_Init();
    if(ret == FLASH_DM_SUCCESS)
    {
        g_proc_flag = DATFRX_SUCCESS_INIT;
    }
    else if(ret == FLASH_DM_SUCCESS_REQUEST_ERASE)
    {
        ret = R_FLASH_DM_Erase();
        if(ret != FLASH_DM_ACCEPT)
        {
            nop();
        }
    }
    else if(ret == FLASH_DM_ERR_BUSY)
    {
        /* === CONTINUE TO LOOP ===*/
        /* Do Nothing */
        nop();
    }
    else if(ret == FLASH_DM_ERR_REQUEST_FORMAT)
    {
        ret = R_FLASH_DM_Format();
        if(ret != FLASH_DM_ACCEPT)
        {
            nop();
        }
        else
        {
            g_proc_flag = DATFRX_RUN_FORMAT;
        }
    }
    else
    {
        nop();
    }
#else/* FLASH_TYPE */

    while(1)
    {
        /* ==== INITIALIZE ==== */
        ret = R_FLASH_DM_Init();
        if(ret == FLASH_DM_ADVANCE)
        {
            break;
        }
        else if(ret == FLASH_DM_ERR_BUSY)
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
        else
        {
            nop();
        }
    }

    while(1)
    {
        ret = R_FLASH_DM_InitAdvance();
        if(ret == FLASH_DM_SUCCESS)
        {
            g_proc_flag = DATFRX_SUCCESS_INIT;
            break;
        }
        else if(ret == FLASH_DM_ADVANCE)
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
        else if(ret == FLASH_DM_ERR_BUSY)
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
        else if(ret == FLASH_DM_ERR_REQUEST_FORMAT)
        {
            ret = R_FLASH_DM_Format();
            if(ret != FLASH_DM_ACCEPT)
            {
                nop();
            }
            else
            {
                g_proc_flag = DATFRX_RUN_FORMAT;
            }
            break;
        }
        else
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
    }
#endif /* FLASH_TYPE */

    return ret;
}


/*******************************************************************************************************************//**
 * @brief       This functions performs refresh on vee_flash.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful refresh
 * @retval      Any Other Error code apart from FSP_SUCCESS
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_refresh_operation (void)
{
    fsp_err_t err             = FSP_SUCCESS;
    int32_t   status_time_out = INT32_MAX;
    e_flash_dm_status_t ret;
    uint32_t status;

//    /* force refresh and wait to complete */
//    err = RM_VEE_FLASH_Refresh(&g_vee_ctrl);
//    if (FSP_SUCCESS != err)
//    {
//        return err;
//    }

    do
    {
        /* Get the current status of the driver.*/
        ret = R_FLASH_DM_Control(FLASH_DM_GET_STATUS, &status);
        if (FLASH_DM_SUCCESS != ret)
        {
            return FSP_ERR_ASSERTION;
        }
    } while ((FLASH_DM_ACT_IDLE != status) && (ZERO_VALUE < --status_time_out));

    if (ZERO_VALUE == status_time_out)
    {
        err = FSP_ERR_TIMEOUT;
    }
    else
    {
        /* Reset the flag.*/
        g_write_flag = false;
    }

    return err;
}

void ucb_function(void* error_code)
{
   /* ==== SUCCESS ==== */
    /* cast from void* to e_flash_dm_status_t*/
    switch((e_flash_dm_status_t)error_code)
    {
        case FLASH_DM_FINISH_FORMAT:
        case FLASH_DM_FINISH_WRITE:
        case FLASH_DM_FINISH_ERASE:
    #if (FLASH_TYPE == FLASH_TYPE_1)
        case FLASH_DM_FINISH_RECLAIM:
    #endif
        case FLASH_DM_ERR_FORMAT:
        case FLASH_DM_ERR_WRITE:
        case FLASH_DM_ERR_ERASE:
        case FLASH_DM_ERR_RECLAIM:
            break;   /* TODO: handle status later */
    }
}
/* End of function ucb_function() */


/**********************************************************************************************************************
 *  Executed at start of the application.
 *  This function initializes the VEE driver and formats the flash if necessary.
 * @param[in]  none
 * @param[out] num_of_entries  Number of entries in the flash.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_init(uint8_t * num_of_entries)
{
    fsp_err_t           err = FSP_SUCCESS;
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;
    uint32_t            status;
    uint8_t                * p_ref_data_read = NULL;
    uint8_t             dummy_boot_data[sizeof(rm_ble_abs_gtl_strg_boot)] = {0};

    rm_ble_abs_gtl_strg_boot boot_data = {0};

    /* === OPEN ===*/
    if (FLASH_DM_SUCCESS != R_FLASH_DM_Open(gs_flash_dm_work, &ucb_function))
    {
        nop();
    }

    do
    {
        RM_DATFRX_Init();
        /* Do Nothing */
        while(g_proc_flag == DATFRX_RUN_FORMAT)
        {
            /* Do Nothing */
        }
    }
    while(g_proc_flag != DATFRX_SUCCESS_INIT);
    /* === END_OPEN ===*/


    /* Check flash status */
    ret = R_FLASH_DM_Control(FLASH_DM_GET_STATUS, &status);
    if (FLASH_DM_SUCCESS != ret)
    {
        return FSP_ERR_INVALID_STATE;
    }

#ifdef CRYPTO_ENABLED
    /* Initialize AES environment */
    rm_ble_abs_gtl_aes_init(NULL, NULL, NULL); // default IV and mode
    rm_ble_abs_gtl_aes_env.keyset_func(usr_key, NULL, AES_MODE_128_);
#endif

    /* Try reading existing boot data */
    st_flash_dm_info_t flash_info;
    flash_info.data_no = FLASH_DM_CFG_DF_DATA_NUM - 1;
    flash_info.p_data = (uint8_t *)&gs_test_r_buff[0];

    ret = R_FLASH_DM_Read(&flash_info);

    p_ref_data_read = flash_info.p_data;
    memcpy(&boot_data, p_ref_data_read, sizeof(rm_ble_abs_gtl_strg_boot));

    if ((FLASH_DM_SUCCESS != ret) ||
        (boot_data.sec_data_mng_info.magic_num != BLE_ABS_SECURE_DATA_MAGIC_NUMBER))
    {
        /* Flash not formatted or invalid magic number → format */
        ret = R_FLASH_DM_Format();
        if (FLASH_DM_SUCCESS != ret)
        {
            return FSP_ERR_ERASE_FAILED;
        }

        /* Initialize empty structure and write back to flash */
        memset(dummy_boot_data, ZERO_VALUE, sizeof(dummy_boot_data));

        flash_info.data_no = REF_DATA_IDX;
        flash_info.p_data  = dummy_boot_data;
        ret = R_FLASH_DM_Write(&flash_info);
        if(ret == FLASH_DM_ERR_REQUEST_ERASE)
        {
            ret = R_FLASH_DM_Erase();
            if(ret != FLASH_DM_ACCEPT)
            {
                nop();
            }
        }

        *num_of_entries = 0;
    }
    else
    {
        *num_of_entries = boot_data.sec_data_mng_info.bond_cnt;
    }

    return err;
}

/**********************************************************************************************************************
 * Read bonding information from flash.
 * @param[in]  num_of_entries   Number of entries to read (retrieved from the security data management information).
 * @param[out] addr             Address to store the read data.
 * @retval     fsp_err_t        Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_read_bond_data (uint8_t num_of_entries, uint8_t ** addr, uint16_t * data_size)
{
    fsp_err_t err              = FSP_SUCCESS;
    void    * p_record_data    = NULL;
    uint8_t * p_ref_data       = rm_ble_gtl_malloc(BOND_DATA_TL_SIZE);
    uint8_t * p_ref_data_start = NULL;
    uint32_t  out_len          = 0;
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    *data_size = 0;
 #ifdef CRYPTO_ENABLED
    uint8_t decrypted[BOND_DATA_SINGLE] = {0}; // Buffer to hold decrypted data
 #endif
    if (NULL == p_ref_data)
    {
        return FSP_ERR_OUT_OF_MEMORY;          // Memory allocation failed
    }

    p_ref_data_start = p_ref_data;             // Get starting address

    // Check if the number of entries exceeds the maximum allowed
    if (num_of_entries > BLE_ABS_CFG_NUMBER_BONDING)
    {
        rm_ble_gtl_free(p_ref_data);
        p_ref_data_start = NULL;

        return FSP_ERR_INVALID_ARGUMENT;
    }

    st_flash_dm_info_t flash_info;

    for (uint32_t rec_id = 1; rec_id <= num_of_entries; rec_id++)
    {
        ret = R_FLASH_DM_Read(&flash_info);
        if (FLASH_DM_SUCCESS == ret)
        {
            p_record_data = flash_info.p_data;
 #ifdef CRYPTO_ENABLED

            // The bond data len cannot exceed 254 bytes.
            err = rm_ble_abs_gtl_aes_env.decrypt_func(decrypted,
                                                      sizeof(decrypted),
                                                      (uint8_t *) p_record_data,
                                                      out_len,
                                                      usr_key);
            out_len -= AES_BLOCK_SIZE;
            memcpy(p_ref_data, decrypted, out_len);
 #else
            memcpy(p_ref_data, p_record_data, out_len);
 #endif
            p_ref_data += out_len;
            *data_size += (uint16_t) out_len; // Update the total length of data read
        }
        else
        {
            rm_ble_gtl_free(p_ref_data);
            p_ref_data_start = NULL;

            return FSP_ERR_ASSERTION;
        }
    }

    *addr = p_ref_data_start;          // Update address to point to the start of the data

    return err;
}

/***********************************************************************************************************************
 * This function releases the buffer allocated for bonding information.
 * @param[in]  p_sec_data   Pointer to the security data buffer to be released.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_rel_buf (uint8_t * p_sec_data)
{
    fsp_err_t err = FSP_SUCCESS;
    rm_ble_gtl_free(p_sec_data);

    return err;
}

/***********************************************************************************************************************
 /**********************************************************************************************************************
 * @brief   Write bonding data to Data Flash.
 * @param[in]  idx         Index of record to write.
 * @param[in]  data_addr   Pointer to data.
 * @param[in]  data_size   Size of data (must equal BOND_DATA_SINGLE).
 * @retval     FSP_SUCCESS             Operation successful.
 * @retval     FSP_ERR_INVALID_ARGUMENT Invalid data size.
 * @retval     FSP_ERR_WRITE_FAILED    Flash write failed.
 * @retval     FSP_ERR_TIMEOUT         Timeout waiting for write completion.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_write_bond_data(uint8_t idx, uint8_t *data_addr, uint16_t data_size)
{
    fsp_err_t err = FSP_SUCCESS;
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    do
    {
        RM_DATFRX_Init();
        /* Do Nothing */
        while(g_proc_flag == DATFRX_RUN_FORMAT)
        {
            /* Do Nothing */
        }
    }
    while(g_proc_flag != DATFRX_SUCCESS_INIT);

    if (data_size != BOND_DATA_SINGLE)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

#ifdef CRYPTO_ENABLED
    uint8_t *plain_data      = rm_ble_gtl_malloc(data_size);
    uint8_t *cipher_datatext = rm_ble_gtl_malloc(data_size + AES_BLOCK_SIZE);

    if ((plain_data == NULL) || (cipher_datatext == NULL))
    {
        return FSP_ERR_ASSERTION; // Allocation failed
    }

    memset(plain_data, ZERO_VALUE, data_size);
    memset(cipher_datatext, ZERO_VALUE, data_size + AES_BLOCK_SIZE);

    memcpy(plain_data, data_addr, data_size);

    err = rm_ble_abs_gtl_aes_env.encrypt_func(cipher_datatext,
                                              data_size + AES_BLOCK_SIZE,
                                              plain_data,
                                              data_size,
                                              usr_key,
                                              NULL); // NULL = use default IV
    st_flash_dm_info_t flash_info;
    flash_info.data_no = idx;
    flash_info.p_data  = cipher_datatext;

    ret = R_FLASH_DM_Write(&flash_info);

    rm_ble_gtl_free(plain_data);
    rm_ble_gtl_free(cipher_datatext);
#else
    st_flash_dm_info_t flash_info;
    flash_info.data_no = idx;
    flash_info.p_data  = data_addr;

    ret = R_FLASH_DM_Write(&flash_info);
#endif

    if (FLASH_DM_ACCEPT != ret)
    {
        return FSP_ERR_WRITE_FAILED;
    }

    // Wait until flash operation complete (depends on your driver’s busy check)
    err = wr_timeout(5); // e.g. wait 5 ms or 5s depending on your implementation

    if (FSP_SUCCESS != err)
    {
        return FSP_ERR_TIMEOUT;
    }

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 * Update the number of bonds in the reference data.
 * This function updates the bond count in the reference data and writes it back to flash.
 * @param[in]  act_num_bond   The actual number of bonds to update.
 * @retval     fsp_err_t      Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_update_bond_num (uint8_t act_num_bond)
{
    fsp_err_t                err            = FSP_SUCCESS;
    rm_ble_abs_gtl_strg_boot boot_data      = {0};
    uint8_t   ref_data_write[REF_DATA_SIZE] = {0};
    uint8_t * p_ref_data_read               = NULL;
    e_flash_dm_status_t                      ret;
    uint32_t                                  status;
    st_flash_dm_info_t                         flash_info;
    /* Get the reference data pointer */

    flash_info.data_no = act_num_bond;
    flash_info.p_data = (uint8_t *)&gs_test_r_buff[0];

    ret = R_FLASH_DM_Read(&flash_info);
    p_ref_data_read = flash_info.p_data;
    if (FLASH_DM_SUCCESS != ret)
    {
        return FSP_ERR_ASSERTION;
    }

    /* Read the existing boot data */
    memcpy(&boot_data, p_ref_data_read, sizeof(rm_ble_abs_gtl_strg_boot));

    /* Update the bond count */
    boot_data.sec_data_mng_info.bond_cnt = act_num_bond;

    if ((boot_data.sec_data_mng_info.magic_num != BLE_ABS_SECURE_DATA_MAGIC_NUMBER) && (act_num_bond == 1))
    {
        /* If the magic number is not valid, set it to the correct value */
        boot_data.sec_data_mng_info.magic_num = BLE_ABS_SECURE_DATA_MAGIC_NUMBER;
    }
    else
    {
        /* If the magic number is valid, do nothing */
    }

    /* Write the updated boot data back to flash */
    memcpy(&ref_data_write, &boot_data, REF_DATA_SIZE);
    ret = R_FLASH_DM_Control(FLASH_DM_GET_STATUS, &status);
    if (FLASH_DM_SUCCESS != ret)
    {
        return FSP_ERR_ASSERTION;
    }

    flash_info.p_data = ref_data_write;
    flash_info.data_no = REF_DATA_IDX;

    ret = R_FLASH_DM_Write(&flash_info);
    if (FLASH_DM_ACCEPT != ret)
    {
        return FSP_ERR_ASSERTION;
    }

    err = wr_timeout(5);

    return err;
}


/***********************************************************************************************************************
 *  @brief        This function formats the flash memory.
 *  @note         It opens the VEE driver, performs a manual format operation, and checks the status of the driver.
 *  @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_format_operation (void)
{
    fsp_err_t err                      = FSP_SUCCESS;
    e_flash_dm_status_t               ret;
    uint32_t                          status;

    /* === OPEN ===*/
    if (FLASH_DM_SUCCESS != R_FLASH_DM_Open(gs_flash_dm_work, &ucb_function))
    {
        nop();
    }


    /* === END_OPEN ===*/

    /* Start a manual format operation.*/
    ret = R_FLASH_DM_Format();
    if (FLASH_DM_ACCEPT != ret)
    {
        return FSP_ERR_ASSERTION;
    }

    /* Get the current status of the driver.*/
    ret = R_FLASH_DM_Control(FLASH_DM_GET_STATUS, &status);
    if (FLASH_DM_SUCCESS != ret)
    {
        return FSP_ERR_ASSERTION;
    }

    return err;
}

/***********************************************************************************************************************
 *  @brief        This function removes all bond data from the flash memory.
 *  @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_rem_all_bond_data (void)
{
    fsp_err_t                err            = FSP_SUCCESS;
    rm_ble_abs_gtl_strg_boot boot_data      = {0};
    uint8_t   ref_data_write[REF_DATA_SIZE] = {0};
    uint8_t * p_ref_data_read               = NULL;
    st_flash_dm_info_t                         flash_info;
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    flash_info.data_no = FLASH_DM_CFG_DF_DATA_NUM - 1;
    flash_info.p_data = (uint8_t *)&gs_test_r_buff[0];

    /* Get the reference data pointer */
    ret = R_FLASH_DM_Read(&flash_info);
    if (FLASH_DM_SUCCESS != ret)
    {
        return FSP_ERR_ASSERTION;
    }
    p_ref_data_read = flash_info.p_data;
    /* Read the existing boot data */
    memcpy(&boot_data, p_ref_data_read, sizeof(rm_ble_abs_gtl_strg_boot));

    /* Update the bond count */
    boot_data.sec_data_mng_info.bond_cnt = ZERO_VALUE;

    /* Format the flash */
    rm_ble_abs_gtl_storage_format_operation();

    /* Write the updated boot data back to flash */
    memcpy(&ref_data_write, &boot_data, REF_DATA_SIZE);

    flash_info.p_data = ref_data_write;
    flash_info.data_no = REF_DATA_IDX;
    ret = R_FLASH_DM_Write(&flash_info);

    if (FLASH_DM_ACCEPT != ret)
    {
        return FSP_ERR_ASSERTION;
    }
    err = wr_timeout(5);

    return err;
}

/***********************************************************************************************************************
 *  @brief        This function removes specific bond data from the flash memory.
 *  @param[in]    idx         Index of the bond data to remove.
 *  @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_rem_specific_bond_data (uint8_t idx)
{
    // Copy new DB from RAM
    // Update the bond count in the reference data
    FSP_PARAMETER_NOT_USED(idx);

    return FSP_SUCCESS;
}

/***********************************************************************************************************************
 *  @brief        This function retrieves the Bluetooth device address from the flash memory.
 *  @param[out]   bd_address  Pointer to store the Bluetooth device address.
 *  @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_get_addr (st_ble_dev_addr_t * bd_address)
{
    fsp_err_t                err             = FSP_SUCCESS;
    rm_ble_abs_gtl_strg_boot boot_data       = {0};
    uint8_t                * p_ref_data_read = NULL;
    e_flash_dm_status_t                      ret;
    st_flash_dm_info_t                         flash_info;

    /* === OPEN ===*/
    if (FLASH_DM_SUCCESS != R_FLASH_DM_Open(gs_flash_dm_work, &ucb_function))
    {
        nop();
    }

    do
    {
        RM_DATFRX_Init();
        /* Do Nothing */
        while(g_proc_flag == DATFRX_RUN_FORMAT)
        {
            /* Do Nothing */
        }
    }
    while(g_proc_flag != DATFRX_SUCCESS_INIT);
    /* === END_OPEN ===*/


    flash_info.data_no = FLASH_DM_CFG_DF_DATA_NUM - 1;
    flash_info.p_data = (uint8_t *)&gs_test_r_buff[0];

    /* Get the reference data pointer */
    ret = R_FLASH_DM_Read(&flash_info);
    if (FLASH_DM_SUCCESS != ret)
    {
        return FSP_ERR_ASSERTION;
    }

    /* Read the existing boot data */
    p_ref_data_read = flash_info.p_data;
    memcpy(&boot_data, p_ref_data_read, sizeof(rm_ble_abs_gtl_strg_boot));
    if (boot_data.sec_data_mng_info.magic_num != BLE_ABS_SECURE_DATA_MAGIC_NUMBER)
    {
        err = FSP_ERR_NOT_FOUND;
        memset(bd_address, 0x00, BLE_BD_ADDR_LEN); // Clear the address
        return err;
    }

    /* Copy the address */
    memcpy(bd_address->addr, &boot_data.loc_dev_sec_data.loc_ident_addr.addr, BLE_BD_ADDR_LEN);
    bd_address->type = boot_data.loc_dev_sec_data.loc_ident_addr.type;

    return err;
}

/***********************************************************************************************************************
 * @brief        This function sets the Bluetooth device address in the flash memory.
 * @param[in]    bd_address  Pointer to the Bluetooth device address to set.
 * @retval       fsp_err_t   Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_set_addr (st_ble_dev_addr_t * bd_address)
{
    fsp_err_t                err            = FSP_SUCCESS;
    rm_ble_abs_gtl_strg_boot boot_data      = {0};
    uint8_t   ref_data_write[REF_DATA_SIZE] = {0};
    uint8_t * p_ref_data_read               = NULL;
    st_flash_dm_info_t                         flash_info;
    e_flash_dm_status_t                      ret;

    /* === OPEN ===*/
    if (FLASH_DM_SUCCESS != R_FLASH_DM_Open(gs_flash_dm_work, &ucb_function))
    {
        nop();
    }

    do
    {
        RM_DATFRX_Init();
        /* Do Nothing */
        while(g_proc_flag == DATFRX_RUN_FORMAT)
        {
            /* Do Nothing */
        }
    }
    while(g_proc_flag != DATFRX_SUCCESS_INIT);
    /* === END_OPEN ===*/

    flash_info.data_no = FLASH_DM_CFG_DF_DATA_NUM - 1;
    flash_info.p_data = (uint8_t *)&gs_test_r_buff[0];

    /* Get the reference data pointer */
    ret = R_FLASH_DM_Read(&flash_info);
    if (FLASH_DM_SUCCESS != ret)
    {
        return FSP_ERR_ASSERTION;
    }

    /* Read the existing boot data */
    p_ref_data_read = flash_info.p_data;
    memcpy(&boot_data, p_ref_data_read, sizeof(rm_ble_abs_gtl_strg_boot));
    if (boot_data.sec_data_mng_info.magic_num != BLE_ABS_SECURE_DATA_MAGIC_NUMBER)
    {
        /* If the magic number is not valid, set it to the correct value */
        /*Set the magic number to indicate valid data*/ 
        boot_data.sec_data_mng_info.magic_num          = BLE_ABS_SECURE_DATA_MAGIC_NUMBER; 
        boot_data.sec_data_mng_info.bond_cnt           = 0;                                // Reset the bond count
        boot_data.loc_dev_sec_data.loc_ident_addr.type = BLE_GAP_ADDR_PUBLIC;              // Set default address type
        memset(boot_data.loc_dev_sec_data.loc_ident_addr.addr, 0x00, BLE_BD_ADDR_LEN);     // Clear the address
    }

    /* Update the Bluetooth device address */
    memcpy(&boot_data.loc_dev_sec_data.loc_ident_addr.addr, bd_address->addr, BLE_BD_ADDR_LEN);
    boot_data.loc_dev_sec_data.loc_ident_addr.type = bd_address->type;

    /* Write the updated boot data back to flash */
    memcpy(&ref_data_write, &boot_data, REF_DATA_SIZE);

    flash_info.p_data = ref_data_write;
    flash_info.data_no = REF_DATA_IDX;
    ret = R_FLASH_DM_Write(&flash_info);
    if (FLASH_DM_ACCEPT != ret)
    {
        return FSP_ERR_ASSERTION;
    }

    err = wr_timeout(5);

    return err;
}

/***********************************************************************************************************************
 * @brief        This function updates the crypto key value
 * @param[in]    key        Pointer to the new crypto key.
 * @param[in]    key_size   Size of the crypto key.
 * @retval       fsp_err_t  Status of the operation.
 **********************************************************************************************************************/
fsp_err_t rm_ble_abs_gtl_storage_upd_crypto_key (uint8_t * key, uint8_t key_size)
{
    fsp_err_t err = FSP_SUCCESS;

 #ifdef CRYPTO_ENABLED
    memcpy(usr_key, key, key_size);
 #else
    FSP_PARAMETER_NOT_USED(key);
    FSP_PARAMETER_NOT_USED(key_size);
 #endif

    return err;
}

#endif                                 // ENABLE_STORAGE
