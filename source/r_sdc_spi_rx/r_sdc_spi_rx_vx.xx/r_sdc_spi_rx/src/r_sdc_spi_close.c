/**********************************************************************************************************************
* Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_sdc_spi_close.c
 * Version      : 1.11
 * Description  : Functions for module close.
  *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 28.12.2023 1.00     First Release
 *         : 20.03.2025 1.11     Changed the disclaimer in program sources.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_sdc_spi_private.h"

/**********************************************************************************************************************
* Outline      : Close SPI mode SD card driver
* Function Name: r_sdc_spi_close
* Description  : Close the SD Driver work memory specified by channel.
* Arguments    : uint32_t           card_no              ;   SD Card No.
* Return Value : SDC_SPI_SUCCESS                         ;   Successful operation
*              : SDC_SPI_ERR_INTERNAL                    ;   Error in module used inside driver
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
sdc_spi_status_t r_sdc_spi_close(uint32_t card_no)
{
    sdc_spi_hndl_t * p_hndl = 0;

    /* Get handle address */
    p_hndl = r_sdc_spi_handle_get(card_no);

    /* I/O port initialize */
    if (SDC_SPI_ENABLE == p_hndl->use_cs_pin)
    {
        R_GPIO_PinDirectionSet(p_hndl->cs_pin, GPIO_DIRECTION_INPUT);
    }
    if (SDC_SPI_ENABLE == p_hndl->use_cd_pin)
    {
        R_GPIO_PinDirectionSet(p_hndl->cd_pin, GPIO_DIRECTION_INPUT);
    }
    if (SDC_SPI_ENABLE == p_hndl->use_wp_pin)
    {
        R_GPIO_PinDirectionSet(p_hndl->wp_pin, GPIO_DIRECTION_INPUT);
    }

    /* Handle parameter initialize */
    r_sdc_spi_mem_clear((uint8_t *)p_hndl, sizeof(sdc_spi_hndl_t));
    r_sdc_spi_handle_clear(card_no);

    return SDC_SPI_SUCCESS;
} /* End of function r_sdc_spi_close() */

/* End of File */
