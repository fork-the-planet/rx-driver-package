/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* System Name  : FLASH SPI driver software
* File Name    : r_flash_spi.c
* Version      : 3.51
* Device       : -
* Abstract     : User I/F file
* Tool-Chain   : -
* OS           : not use
* H/W Platform : -
* Description  : SPI FLASH User I/F file
* Limitation   : None
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 23.07.2014 2.21     Created
*              : 29.05.2015 2.32     Revised functions of same as Ver.2.32 of EEPROM SPI FIT module.
*              : 10.12.2020 3.02     Modified comment of API function to Doxygen style.
*              : 16.03.2023 3.20     Added support for AT25QF641B-SHB with Indirect Access Mode of QSPIX
*              : 15.11.2023 3.40     Removed note for QSPIX Memory Mapped Mode in R_FLASH_SPI_Read_Data() function.
*                                    Updated according to GSCE Code Checker 6.50.
*                                    Added support for MX25U6432F.
*                                    Added features Advanced sector protection supporting for MX66L1G45 and MX25U6432F.
*              : 20.12.2024 3.50     Modified comment of API function to Doxygen style.
*              : 15.03.2025 3.51     Updated disclaimer.
***********************************************************************************************************************/


/************************************************************************************************
Includes <System Includes> , "Project Includes"
*************************************************************************************************/
#include "r_flash_spi_if.h"                      /* FLASH driver I/F definitions                 */
#include "r_flash_spi_config.h"                  /* FLASH driver Configuration definitions       */
#include "r_flash_spi_private.h"                 /* FLASH driver Private module definitions      */

/************************************************************************************************
Macro definitions
*************************************************************************************************/


/************************************************************************************************
Typedef definitions
*************************************************************************************************/


/************************************************************************************************
Exported global variables (to be accessed by other files)
*************************************************************************************************/
#if (FLASH_SPI_CFG_LONGQ_ENABLE == 1)
static longq_hdl_t       p_flash_long_que;             /* LONGQ handler                        */
#endif  /* (FLASH_SPI_CFG_LONGQ_ENABLE == 1) */


/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Open
 *****************************************************************************************************************/ /**
 * @brief This function is run first when using the APIs of the serial flash memory control software.
 * @param[in] devno
 *             Device number (0, 1)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @details   Initializes the slave device select pin of the device number specified by the argument devno.
 *            After initialization the pin is in the general output port high-output state.\n
 *            Do not call this function when communication is in progress.
 *            Communication cannot be guaranteed if the function is called when communication is in progress.
 * @note      After calling this user API function, it is recommended that R_FLASH_SPI_Polling() be used to confirm
 *            that the serial flash memory write cycle has completed. The next read or write processing will not be
 *            accepted while the serial flash memory write cycle is in progress.\n
 *            However, it is possible to access the serial flash memory during the write cycle by, for example,
 *            issuing a system reset while the serial flash memory write cycle is in progress and restarting
 *            serial flash memory control from the beginning.
 */
flash_spi_status_t R_FLASH_SPI_Open(uint8_t devno)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_init_port(devno);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Open
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Close
 *****************************************************************************************************************/ /**
 * @brief This function is used to close the serial flash memory control software when it is in use.
 * @param[in] devno
 *             Device number (0, 1)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_OTHER  Other error
 * @details   Sets the slave device select pin of the device number specified by the argument devno to function as
 *            a general I/O port. After the function runs, the pin is in the general output port high-output state.\n
 *            Do not call this function when communication is in progress.
 *            Communication cannot be guaranteed if the function is called when communication is in progress.
 * @note      The state of the slave device select pin after this function is called is different from its state after
 *            a reset (general input port state). Review the pin settings if necessary.\n
 *            Before calling this user API function, it is recommended that R_FLASH_SPI_Polling() be used to confirm
 *            that the serial flash memory write cycle has completed. This makes it possible to restart serial flash
 *            memory control because the serial flash memory has not transitioned to the write cycle.
 */
flash_spi_status_t R_FLASH_SPI_Close(uint8_t devno)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_reset_port(devno);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Close
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Status
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the status register.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in,out] p_status
 *             Status register storage buffer (size: 1 byte)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Reads the status register and stores the contents in p_status. See section R_FLASH_SPI_Read_Status()
 *            in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Read_Status(uint8_t devno, uint8_t * p_status)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_read_status(devno, p_status);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Read_Status
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Status2
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the status register 2. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in,out] p_status
 *             Status register 2 storage buffer (size: 1 byte)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Reads the status register and stores the contents in p_status. See section R_FLASH_SPI_Read_Status2()
 *            in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Read_Status2(uint8_t devno, uint8_t * p_status)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_read_status2(devno, p_status);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Read_Status2
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Status3
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the status register 3. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in,out] p_status
 *             Status register 3 storage buffer (size: 1 byte)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Reads the status register and stores the contents in p_status. See section R_FLASH_SPI_Read_Status3()
 *            in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Read_Status3(uint8_t devno, uint8_t * p_status)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_read_status3(devno, p_status);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Read_Status3
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Set_Write_Protect
 *****************************************************************************************************************/ /**
 * @brief This function is used to make write protect settings.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] wpsts
 *             Write protect setting data
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_WP     Write-protection error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Make write protect settings. SRWD is cleared to 0. See section R_FLASH_SPI_Set_Write_Protect() in the
 *            application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Set_Write_Protect(uint8_t devno, uint8_t wpsts)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_set_write_protect(devno, wpsts);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Set_Write_Protect
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Di
 *****************************************************************************************************************/ /**
 * @brief This function is used to disable write operation.
 * @param[in] devno
 *             Device number (0, 1)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Transmits the WRDI command and clears the WEL bit in the status register.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Write_Di(uint8_t devno)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_write_di(devno);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Write_Di
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Data
 *****************************************************************************************************************/ /**
 * @brief This function is used to read data from the serial flash memory.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in,out] p_flash_spi_info
 *             Serial flash memory information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_FLASH_SPI_Read_Data() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Reads the specified number of bytes of data from the specified address in the serial flash memory and
 *            stores the data in p_data.\n
 *            The maximum read address is the serial flash memory capacity - 1.\n
 *            Rollover read operations are not supported. After the end address is read, processing ends.
 *            It is then necessary to reset the address and call this API function again.\n
 *            FLASH_SPI_ERR_PARAM is returned if the total value of the read byte count, cnt, and specified address,
 *            addr, exceeds the maximum read address.\n
 *            DMAC transfer or DTC transfer occurs when the transfer size conditions of the clock synchronous single
 *            master control software are matched. Otherwise, operation switches to software transfer.
 * @note      To speed up data transfers, align the start address with a 4-byte boundary when specifying data storage
 *            buffer pointers.\n
 *            The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Read_Data(uint8_t devno, flash_spi_info_t * p_flash_spi_info)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_read_data(devno, p_flash_spi_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Read_Data
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Data_Page
 *****************************************************************************************************************/ /**
 * @brief This function is used to write data to the serial flash memory in single-page units.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] p_flash_spi_info
 *             Serial flash memory information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_FLASH_SPI_Write_Data_Page() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Writes the specified number of bytes of data (up to a maximum size of 1 page) in p_data to the serial
 *            flash memory, starting from the specified address.\n
 *            When writing a large volume of data, communication is divided into page units. This prevents a situation
 *            in which other processing is not possible while communication is in progress. \n
 *            Writing to the serial flash memory is only possible when write protect has been canceled.\n
 *            It is not possible to write to a protected page. Attempting to do so returns the error FLASH_SPI_ERR_WP.\n
 *            The maximum write address is the serial flash memory capacity - 1.\n
 *            The maximum write byte count (cnt) setting value is the capacity of the serial flash memory.\n
 *            FLASH_SPI_ERR_PARAM is returned if the total value of the write byte count, cnt, and specified address,
 *            addr, exceeds the maximum write address.\n
 *            DMAC transfer or DTC transfer occurs when the transfer size conditions of the clock synchronous single
 *            master control software are matched. Otherwise, operation switches to software transfer.\n
 *            When a byte count exceeding 1 page is specified, the remaining byte count and next address information
 *            remain in the serial flash memory information structure (p_flash_info) after processing of a single page
 *            write finishes. It is possible to write the remaining bytes by specifying p_flash_info unmodified in
 *            this API function again.\n
 *            After this user API function finishes successfully, the serial flash memory transitions to the write
 *            cycle. Do not fail to confirm that the write has finished with R_FLASH_SPI_Polling(). If an attempt
 *            is made to perform the next read or write processing while a write cycle is in progress, the serial
 *            flash memory will not accept that processing. \n
 *            R_FLASH_SPI_Polling() can be called at any time specified by the user. This makes it possible for the
 *            user application to perform other processing while a write cycle is in progress.\n
 *            See section R_FLASH_SPI_Write_Data_Page() in the application note for details.
 * @note      To speed up data transfers, align the start address with a 4-byte boundary when specifying data storage
 *            buffer pointers.\n
 *            The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Write_Data_Page(uint8_t devno, flash_spi_info_t * p_flash_spi_info)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_write_data_page(devno, p_flash_spi_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Write_Data_Page
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Erase
 *****************************************************************************************************************/ /**
 * @brief Based on the mode setting, this function erases all the data in the specified sector (sector erase),
          all the data in the specified block (block erase: 32 KB block or 64 KB block), or all the data on
          the specified chip (chip erase).
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] p_flash_spi_erase_info
 *             Serial flash memory erase information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_FLASH_SPI_Erase() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   For sector erase, specify the start address of the sector in addr.\n
 *            For block erase, specify the start address of the block in addr.\n
 *            For security erase, specify the start address of the security register pages in addr.\n
 *            For chip erase, set addr to 0x00000000.\n
 *            Erasing data in serial flash memory is only possible when write protect has been canceled. \n
 *            It is not possible to erase data in a protected area. Attempting to do so returns the error
 *            FLASH_SPI_ERR_OTHER.\n
 *            When this user API function completes successfully, the serial flash memory transitions to an erase
 *            cycle. Do not fail to confirm erase completion with R_FLASH_SPI_Polling(). If the next read or write
 *            processing starts when a previous erase cycle is in progress, the serial flash memory will not accept
 *            the new processing. \n
 *            R_FLASH_SPI_Polling() can be called at any time specified by the user. This allows a user application
 *            to perform other processing while an erase cycle is in progress. \n
 *            See section R_FLASH_SPI_Erase() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Erase(uint8_t devno, flash_spi_erase_info_t * p_flash_spi_erase_info)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_erase(devno, p_flash_spi_erase_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Erase
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Polling
 *****************************************************************************************************************/ /**
 * @brief This function is used to perform polling to determine if a write or erase operation has finished.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] mode
 *             Completion wait processing setting. See section R_FLASH_SPI_Polling() in the application note for
 *             details.
 * @retval    FLASH_SPI_SUCCESS         Normal end, and write finished
 * @retval    FLASH_SPI_SUCCESS_BUSY    Normal end, and write in progress
 * @retval    FLASH_SPI_ERR_PARAM       Parameter error
 * @retval    FLASH_SPI_ERR_HARD        Hardware error
 * @retval    FLASH_SPI_ERR_OTHER       Other task has acquired clock synchronous single master control software
 *                                      resources, or other error
 * @details   Determines whether or not a write or erase operation has finished.
 * @note      R_FLASH_SPI_Polling() can be called at any time specified by the user. This makes it possible for the
 *            user application to perform other processing while a write cycle is in progress.\n
 *            The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Polling(uint8_t devno, flash_spi_poll_mode_t mode)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_polling(devno, mode);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Polling
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_ID
 *****************************************************************************************************************/ /**
 * @brief This function is used to read ID information.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in,out] p_data
 *             ID information storage buffer. The size differs depending on the serial flash memory product used.
 *             See section R_FLASH_SPI_Read_ID() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Stores ID information for the serial flash memory in p_data.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Read_ID(uint8_t devno, uint8_t * p_data)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_read_id(devno, p_data);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Read_ID
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_GetMemoryInfo
 *****************************************************************************************************************/ /**
 * @brief This function is used to fetch the serial flash memory size information.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in,out] p_flash_spi_mem_info
 *             Serial flash memory size information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_FLASH_SPI_GetMemoryInfo() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @details   Fetches serial flash memory size information for the device number specified by the argument devno.
 * @note      None.
 */
flash_spi_status_t R_FLASH_SPI_GetMemoryInfo(uint8_t devno, flash_spi_mem_info_t * p_flash_spi_mem_info)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_get_memory_info(devno, p_flash_spi_mem_info);
    
    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_GetMemoryInfo
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Configuration
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the configuration register(s). It is a dedicated API function for MX25L,
 *        MX66L, MX25R, or MX25U family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in,out] p_config
 *             Configuration register storage buffer. The size differs depending on the serial NOR flash memory
 *             product used. See section R_FLASH_SPI_Read_Configuration() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *            or other error
 * @details   Reads the configuration register(s) of the serial NOR Flash memory and stores the contents in p_config.
 *            See section R_FLASH_SPI_Read_Configuration() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Read_Configuration(uint8_t devno, uint8_t * p_config)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_read_configuration(devno, p_config);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Read_Configuration
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Configuration
 *****************************************************************************************************************/ /**
 * @brief This function is used to write the configuration register(s). It is a dedicated API function for MX25L,
 *        MX66L, MX25R, or MX25U family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] p_reg
 *             Register information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_FLASH_SPI_Write_Configuration() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *            or other error
 * @details   The values set in p_reg->config1 and p_reg->config2 are written to the configuration register.
 *            See section R_FLASH_SPI_Write_Configuration() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Write_Configuration(uint8_t devno, flash_spi_reg_info_t * p_reg)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_write_configuration(devno, p_reg);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Write_Configuration
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Status
 *****************************************************************************************************************/ /**
 * @brief This function is used to write the status register 1. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] p_reg
 *             Status register 1 setting data buffer
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *            or other error
 * @details   The values set in p_reg is written to the status register 1.
 *            See section R_FLASH_SPI_Write_Status() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Write_Status(uint8_t devno, uint8_t * p_reg)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_write_status(devno, p_reg);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Write_Status
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Status2
 *****************************************************************************************************************/ /**
 * @brief This function is used to write the status register 2. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] p_reg
 *             Status register 2 setting data buffer
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *            or other error
 * @details   The values set in p_reg is written to the status register 2.
 *            See section R_FLASH_SPI_Write_Status2() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Write_Status2(uint8_t devno, uint8_t * p_reg)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_write_status2(devno, p_reg);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Write_Status2
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Status3
 *****************************************************************************************************************/ /**
 * @brief This function is used to write the status register 3. It is a dedicated API function for AT25QF family
 *        serial NOR flash memory of Renesas Electronics.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] p_reg
 *             Status register 3 setting data buffer
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *            or other error
 * @details   The values set in p_reg is written to the status register 3.
 *            See section R_FLASH_SPI_Write_Status3() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Write_Status3(uint8_t devno, uint8_t * p_reg)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_write_status3(devno, p_reg);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Write_Status3
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Set_4byte_Address_Mode
 *****************************************************************************************************************/ /**
 * @brief This function is used to set the address mode to 4-byte address mode. It is a dedicated API function for
 *        MX25L, MX66L, or MX25R family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[in] devno
 *             Device number (0, 1)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *            or other error
 * @details   See section R_FLASH_SPI_Set_4byte_Address_Mode() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Set_4byte_Address_Mode(uint8_t devno)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_set_4byte_address_mode(devno);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Set_4byte_Address_Mode
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Security
 *****************************************************************************************************************/ /**
 * @brief This function is used to read the security register. It is a dedicated API function for MX25L, MX66L,
 *        MX25R, or MX25U family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in,out] p_scur
 *             Security register  storage buffer (size: 1 byte)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *            or other error
 * @details   Reads the security register and stores the contents in p_scur.
 *            See section R_FLASH_SPI_Read_Security() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Read_Security(uint8_t devno, uint8_t * p_scur)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_read_security(devno, p_scur);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Read_Security
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Read_Data_Security_Page
 *****************************************************************************************************************/ /**
 * @brief This function is used to read data from the security register. It is a dedicated API function for AT25QF
 *        family serial NOR flash memory of Renesas Electronics.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in,out] p_flash_spi_info
 *             Serial flash memory information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_FLASH_SPI_Read_Data_Security_Page() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Reads the specified number of bytes of data from the specified address in the security register and
 *            stores the data in p_data.\n
 *            The maximum read address is the page size - 1.\n
 *            Rollover read operations are not supported. After the end address is read, processing ends.
 *            It is then necessary to reset the address and call this API function again.\n
 *            FLASH_SPI_ERR_PARAM is returned if the total value of the read byte count, cnt, and specified address,
 *            addr, exceeds the maximum read address.\n
 *            DMAC transfer or DTC transfer occurs when the transfer size conditions of the clock synchronous single
 *            master control software are matched. Otherwise, operation switches to software transfer.
 * @note      To speed up data transfers, align the start address with a 4-byte boundary when specifying data storage
 *            buffer pointers.\n
 *            The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.\n
 *            This API function is omitted in QSPIX Memory Mapped Mode.
 */
flash_spi_status_t R_FLASH_SPI_Read_Data_Security_Page(uint8_t devno,  flash_spi_info_t * p_flash_spi_info)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_read_data_security_page(devno, p_flash_spi_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Read_Data_Security_Page
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Write_Data_Security_Page
 *****************************************************************************************************************/ /**
 * @brief This function is used to write data to the security register page in single-page units. It is a dedicated
 *        API function for AT25QF family serial NOR flash memory of Renesas Electronics.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] p_flash_spi_info
 *             Serial flash memory information structure. Use a structure address aligned with a 4-byte boundary.
 *             See section R_FLASH_SPI_Write_Data_Security_Page() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *                                 or other error
 * @details   Writes the specified number of bytes of data (up to a maximum size of 1 page) in p_data to the security
 *            register pages, starting from the specified address.\n
 *            When writing a large volume of data, communication is divided into page units. This prevents a situation
 *            in which other processing is not possible while communication is in progress. \n
 *            Writing to the security register pages is only possible when they are not locked.\n
 *            It is not possible to write to a locked page. Attempting to do so returns the error FLASH_SPI_ERR_WP.\n
 *            The maximum write byte count (cnt) setting value is the capacity of the security register page size.\n
 *            FLASH_SPI_ERR_PARAM is returned if the total value of the write byte count, cnt, and specified address,
 *            addr, exceeds the maximum write address.\n
 *            DMAC transfer or DTC transfer occurs when the transfer size conditions of the clock synchronous single
 *            master control software are matched. Otherwise, operation switches to software transfer.\n
 * @note      To speed up data transfers, align the start address with a 4-byte boundary when specifying data storage
 *            buffer pointers.\n
 *            The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Write_Data_Security_Page(uint8_t devno, flash_spi_info_t * p_flash_spi_info)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_write_data_security_page(devno, p_flash_spi_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Write_Data_Security_Page
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Quad_Enable
 *****************************************************************************************************************/ /**
 * @brief This function is used to enable quad mode. It is a dedicated API function for MX25L, MX66L, MX25R,
 *        or MX25U family serial NOR flash memory of Macronix International Co., Ltd and AT25QF family serial NOR
 *        flash memory of Renesas Electronics.
 * @param[in] devno
 *             Device number (0, 1)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *            or other error
 * @details   Sets the quad enable (QE) bit in the status register to 1 to enable quad mode.\n
 *            To use quad mode, first call this function.\n
 *            After processing finishes, read the status register to confirm that the value of the QE bit is 1.\n
 *            The quad enable (QE) bit is a non-volatile bit. Once quad mode has been enabled, it is necessary to
 *            run R_FLASH_SPI_Quad_Disable() to disable quad mode.\n
 *            When this user API function completes successfully, the serial flash memory transitions to a write
 *            cycle. Do not fail to confirm write completion with R_FLASH_SPI_Polling(). If the next read or write
 *            processing starts when a previous write cycle is in progress, the serial flash memory will not accept
 *            the new processing. \n
 *            R_FLASH_SPI_Polling() can be called at any time specified by the user. This allows a user application
 *            to perform other processing while a write cycle is in progress. \n
 *            See section R_FLASH_SPI_Quad_Enable() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Quad_Enable(uint8_t devno)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_quad_enable(devno);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Quad_Enable
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Quad_Disable
 *****************************************************************************************************************/ /**
 * @brief This function is used to disable quad mode. It is a dedicated API function for MX25L, MX66L, MX25R,
 *        or MX25U family serial NOR flash memory of Macronix International Co., Ltd.and AT25QF family serial NOR
 *        flash memory of Renesas Electronics.
 * @param[in] devno
 *             Device number (0, 1)
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @retval    FLASH_SPI_ERR_PARAM  Parameter error
 * @retval    FLASH_SPI_ERR_HARD   Hardware error
 * @retval    FLASH_SPI_ERR_OTHER  Other task has acquired clock synchronous single master control software resources,
 *            or other error
 * @details   Clears the quad enable (QE) bit in the status register to 0 to cancel quad mode.\n
 *            After processing finishes, read the status register to confirm that the value of the QE bit is 0.\n
 *            The quad enable (QE) bit is a non-volatile bit. Once quad mode has been enabled, it is necessary to
 *            run this user API function to disable quad mode.\n
 *            When this user API function completes successfully, the serial flash memory transitions to a write
 *            cycle. Do not fail to confirm write completion with R_FLASH_SPI_Polling(). If the next read or write
 *            processing starts when a previous write cycle is in progress, the serial flash memory will not accept
 *            the new processing. \n
 *            R_FLASH_SPI_Polling() can be called at any time specified by the user. This allows a user application
 *            to perform other processing while a write cycle is in progress. \n
 *            See section R_FLASH_SPI_Quad_Disable() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Quad_Disable(uint8_t devno)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_quad_disable(devno);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Quad_Disable
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_GetVersion
 *****************************************************************************************************************/ /**
 * @brief This function is used to fetch the serial flash memory version information.
 * @return    Version number.   Upper 2 bytes: major version, lower 2 bytes: minor version.
 * @details   Returns the version information.
 * @note      None
 */
uint32_t R_FLASH_SPI_GetVersion(void)
{
    uint32_t const version = (FLASH_SPI_VERSION_MAJOR << 16) | FLASH_SPI_VERSION_MINOR;
    
    return version;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_GetVersion
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_1ms_Interval
 *****************************************************************************************************************/ /**
 * @brief This function calls the interval timer counter function of the clock synchronous single master control
 *        software. When using the DMAC or DTC, use a timer to call this function at 1 ms intervals.
 * @details   Increments the internal timer counter of the clock synchronous single master control software while
 *            waiting for the DMAC transfer or DTC transfer to finish.
 * @note      User a timer or the like to call this function at 1 ms intervals.
 */
void R_FLASH_SPI_1ms_Interval(void)
{
    r_flash_spi_drvif_1ms_interval();
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_1ms_Interval
 *********************************************************************************************************************/


#if (FLASH_SPI_CFG_LONGQ_ENABLE == 1)
/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Set_LogHdlAddress
 *****************************************************************************************************************/ /**
 * @brief This function specifies the handler address for the LONGQ FIT module. Call this function when using error
 *        log acquisition processing.
 * @param[in] user_long_que
 *             Specify the handler address of the LONGQ FIT module.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @details   Sets the handler address of the LONGQ FIT module in the serial flash memory control software and the
 *            clock synchronous single master control software used by the specified device.\n
 *            This is preparatory processing to enable fetching of error logs using the LONGQ FIT module.
 *            Run this function before calling R_FLASH_SPI_Open().
 * @note      Add the LONGQ FIT module, which is available separately, to your project.\n
 *            Enable the macro FLASH_SPI_CFG_LONGQ_ENABLE in r_flash_spi_config.h. Also, enable
 *            macro xxx_LONGQ_ENABLE in the clock synchronous single master control software used by the
 *            specified device.\n
 *            In the LONGQ FIT module, set the ignore_overflow argument of R_LONGQ_Open() to 1.
 *            This allows the error log buffer to be used as a ring buffer.
 */
flash_spi_status_t R_FLASH_SPI_Set_LogHdlAddress(uint32_t user_long_que)
{
    p_flash_long_que = (longq_hdl_t)user_long_que;
    r_flash_spi_drvif_set_loghdladdress(user_long_que);
    return FLASH_SPI_SUCCESS;
}


/************************************************************************************************
* Function Name: r_flash_spi_log
* Description  : Stores error information to LONGQ buffer.
* Arguments    : uint32_t           flg                 ;   Breakpoint processing
*              : uint32_t           fid                 ;   Flash middleware file No.
*              : uint32_t           line                ;   Flash middleware line No.
* Return Value : 0                                      ;   Successful operation
*              : 1                                      ;   Error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
uint32_t r_flash_spi_log(uint32_t flg, uint32_t fid, uint32_t line)
{
    longq_err_t err = LONGQ_SUCCESS;
    uint32_t    ul_tmp = 0;

    /* Long to Byte */
    ul_tmp = 0;                                         /* Reserved               */
    ul_tmp = (ul_tmp | (line << 8));                    /* LINE                   */
    ul_tmp = (ul_tmp | (fid  << 21));                   /* FID FILE No.           */
    ul_tmp = (ul_tmp | (FLASH_SPI_DRIVER_ID << 27));    /* FID DRIVER No.         */
    ul_tmp = (ul_tmp | (flg  << 31));                   /* Breakpoint processing  */

    err = R_LONGQ_Put(p_flash_long_que, ul_tmp);
    if (err != LONGQ_SUCCESS)
    {
        return 1;
    }

    /* Breakpoint processing */
    if (0x80000000 == (ul_tmp & 0x80000000))
    {
        return 1;
    }
    return 0;
}
#else  /* (FLASH_SPI_CFG_LONGQ_ENABLE == 1) */
/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Set_LogHdlAddress
 *****************************************************************************************************************/ /**
 * @brief This function specifies the handler address for the LONGQ FIT module. Call this function when using error
 *        log acquisition processing.
 * @param[in] user_long_que
 *             Specify the handler address of the LONGQ FIT module.
 * @retval    FLASH_SPI_SUCCESS    Successful operation
 * @details   Sets the handler address of the LONGQ FIT module in the serial flash memory control software and the
 *            clock synchronous single master control software used by the specified device.\n
 *            This is preparatory processing to enable fetching of error logs using the LONGQ FIT module.
 *            Run this function before calling R_FLASH_SPI_Open().
 * @note      Add the LONGQ FIT module, which is available separately, to your project.\n
 *            Enable the macro FLASH_SPI_CFG_LONGQ_ENABLE in r_flash_spi_config.h. Also, enable
 *            macro xxx_LONGQ_ENABLE in the clock synchronous single master control software used by the
 *            specified device.\n
 *            In the LONGQ FIT module, set the ignore_overflow argument of R_LONGQ_Open() to 1.
 *            This allows the error log buffer to be used as a ring buffer.
 */
flash_spi_status_t R_FLASH_SPI_Set_LogHdlAddress(uint32_t user_long_que)
{
    return FLASH_SPI_SUCCESS;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Set_LogHdlAddress
 *********************************************************************************************************************/
#endif  /* (FLASH_SPI_CFG_LONGQ_ENABLE == 1) */


/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Log
 *****************************************************************************************************************/ /**
 * @brief This function fetches the error log. When an error occurs, call this function immediately before user
 *        processing ends.
 * @param[in] flg
 *             Set this to 0x00000001 (fixed value).
 * @param[in] fid
 *             Set this to 0x0000003f (fixed value).
 * @param[in] line
 *             Set this to 0x0001ffff (fixed value).
 * @retval    0    Successful operation
 * @retval    1    Error
 * @details   This function fetches the error log. When an error occurs, call this function immediately before user
 *            processing ends.
 * @note      Incorporate the LONGQ FIT module separately.\n
 *            Enable the macro FLASH_SPI_CFG_LONGQ_ENABLE in r_flash_spi_config.h. Also, enable
 *            macro xxx_LONGQ_ENABLE in the clock synchronous single master control software used by the
 *            specified device.
 */
uint32_t R_FLASH_SPI_Log(uint32_t flg, uint32_t fid, uint32_t line)
{
    R_FLASH_SPI_Log_Func(flg, fid, line);
    return 0;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Log
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Set_Write_Protect_Advanced_Sector
 *****************************************************************************************************************/ /**
 * @brief This function is used to make advanced write-protect settings. It is a dedicated API function for MX66L, 
 *        or MX25U family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[in] devno
 *             Device number (0, 1)
 * @param[in] flash_spi_protect_sector_info
 *             Flash memory advanced sector protection information structure. Use a structure address aligned with
 *             a 4-byte boundary.
 *             See section R_FLASH_SPI_Set_Write_Protect_Advanced_Sector() in the application note for details.
 * @retval    FLASH_SPI_SUCCESS         Successful operation
 * @retval    FLASH_SPI_ERR_PARAM       Parameter error
 * @retval    FLASH_SPI_ERR_HARD        Hardware error
 * @retval    FLASH_SPI_ERR_OTHER       Other task has acquired clock synchronous single master control software resources,
 *                                      or other error
 * @retval    FLASH_SPI_ERR_WP_ADVANCED Advanced write-protection error
 * @details   Make advanced write-protect settings.
 *            See section R_FLASH_SPI_Set_Write_Protect_Advanced_Sector() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Set_Write_Protect_Advanced_Sector(uint8_t devno, flash_spi_protect_sector_info_t * flash_spi_protect_sector_info)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_set_write_protect_advanced_sector(devno, flash_spi_protect_sector_info);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Set_Write_Protect_Advanced_Sector
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: R_FLASH_SPI_Erase_Write_Protect_Advanced_Sector
 *****************************************************************************************************************/ /**
 * @brief This function is used to erase all advanced write-protect settings. It is a dedicated API function for MX66L, 
 *        or MX25U family serial NOR flash memory of Macronix International Co., Ltd.
 * @param[in] devno
 *             Device number (0, 1)
 * @retval    FLASH_SPI_SUCCESS         Successful operation
 * @retval    FLASH_SPI_ERR_PARAM       Parameter error
 * @retval    FLASH_SPI_ERR_HARD        Hardware error
 * @retval    FLASH_SPI_ERR_OTHER       Other task has acquired clock synchronous single master control software resources,
 *                                      or other error
 * @retval    FLASH_SPI_ERR_WP_ADVANCED Advanced write-protection error
 * @details   Erase all advanced write-protect settings.
 *            See section R_FLASH_SPI_Erase_Write_Protect_Advanced_Sector() in the application note for details.
 * @note      The clock synchronous single master control software resources are acquired at the start of the
 *            processing, and the resources are released and the end of the processing.
 */
flash_spi_status_t R_FLASH_SPI_Erase_Write_Protect_Advanced_Sector(uint8_t devno)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;

    ret = r_flash_spi_erase_write_protect_advanced_sector(devno);

    return ret;
}
/**********************************************************************************************************************
 End of function R_FLASH_SPI_Erase_Write_Protect_Advanced_Sector
 *********************************************************************************************************************/


/* End of File */
