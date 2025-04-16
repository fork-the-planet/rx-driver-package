/**********************************************************************************************************************
* Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_sdc_spi_getcarddetection.c
 * Version      : 1.11
 * Description  : Functions for module get card detection.
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
* Outline      : SD card get detect status
* Function Name: r_sdc_spi_getcarddetection
* Description  : Read CD pin and get detection status of SD card.
* Arguments    : uint32_t           card_no             ;   SD Card No.
* Return Value : SDC_SPI_SUCCESS                        ;   Card detection or do not use CD pin.
*              : SDC_SPI_ERR                            ;   CD pin not detected.
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
sdc_spi_status_t r_sdc_spi_getcarddetection(uint32_t card_no)
{
    sdc_spi_hndl_t * p_hndl = 0;

    /* Get handle address */
    p_hndl = r_sdc_spi_handle_get(card_no);

    /* If CD pin not use then return success */
    if (SDC_SPI_DISABLE == p_hndl->use_cd_pin)
    {
        return SDC_SPI_SUCCESS;
    }
    else
    {
        /* CD pin Read */
        if (GPIO_LEVEL_LOW == R_GPIO_PinRead(p_hndl->cd_pin))
        {
            return SDC_SPI_SUCCESS;
        }
        else
        {
            return SDC_SPI_ERR;
        }
    }

} /* End of function r_sdc_spi_getcarddetection() */

/* End of File */
