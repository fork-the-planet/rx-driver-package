/**********************************************************************************************************************
* Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_sdc_spi_get_status.c
 * Version      : 1.11
 * Description  : Functions for module get card status.
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
* Outline      : Get card status
* Function Name: r_sdc_spi_getcardstatus
* Description  : Get card status from handle.
* Arguments    : uint32_t           card_no                    ;   SD Card No.
*              : sdc_spi_card_status_t * p_sdc_spi_card_status ;   Card status struct pointer
* Return Value : SDC_SPI_SUCCESS                               ;   Successful operation
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
sdc_spi_status_t r_sdc_spi_getcardstatus(uint32_t card_no, sdc_spi_card_status_t * p_sdc_spi_card_status)
{
    sdc_spi_hndl_t * p_hndl = 0;

    /* Get handle address */
    p_hndl = r_sdc_spi_handle_get(card_no);

    /* Cast to uint8_t */
    p_sdc_spi_card_status->csd_structure = (uint8_t)(p_hndl->media & SDC_SPI_CSD_STRUCTER_MASK);
    p_sdc_spi_card_status->card_sector_size = p_hndl->csdinfo.memsize;
    p_sdc_spi_card_status->max_block_number = p_hndl->csdinfo.maxblkno; /* Total number of blocks */
    p_sdc_spi_card_status->write_protect = p_hndl->csdinfo.wp;

    return SDC_SPI_SUCCESS;
} /* End of function r_sdc_spi_getcardstatus() */

/* End of File */
