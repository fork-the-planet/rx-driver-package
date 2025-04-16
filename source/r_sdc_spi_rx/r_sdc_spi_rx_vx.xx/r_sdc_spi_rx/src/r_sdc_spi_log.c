/**********************************************************************************************************************
* Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_sdc_spi_log.c
 * Version      : 1.11
 * Description  : Functions for module log.
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

#if (1 == SDC_SPI_CFG_ERROR_LOG_ACQUISITION)
#include "r_longq_if.h"
#endif

/**********************************************************************************************************************
 Exported global variables
 *********************************************************************************************************************/
#if (1 == SDC_SPI_CFG_ERROR_LOG_ACQUISITION)
static longq_hdl_t gs_sdc_spi_long_que;
#endif

/**********************************************************************************************************************
* Outline      : Set log handle address.
* Function Name: r_sdc_spi_setloghdladdress
* Description  : Set log handle address.
* Arguments    : uint32_t           user_long_que       ;   LONG FIT handle.
* Return Value : SDC_SPI_SUCCESS                        ;   Successful operation
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
sdc_spi_status_t r_sdc_spi_setloghdladdress(uint32_t user_long_que)
{
#if (1 == SDC_SPI_CFG_ERROR_LOG_ACQUISITION)
    gs_sdc_spi_long_que = (longq_hdl_t)user_long_que;
#endif
    return SDC_SPI_SUCCESS;

} /* End of function r_sdc_spi_setloghdladdress() */

/**********************************************************************************************************************
* Outline      : Log get or log set.
* Function Name: r_sdc_spi_log
* Description  : Log get or log set.
* Arguments    : uint32_t           flg                 ;   Error flag.
*              : uint32_t           fid                 ;   File id.
*              : uint32_t           line                ;   Line number
* Return Value : 0                                      ;   Successful operation
*              : 1                                      ;   Failed operation
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
int32_t r_sdc_spi_log(uint32_t flg, uint32_t fid, uint32_t line)
{
#if (1 == SDC_SPI_CFG_ERROR_LOG_ACQUISITION)
    longq_err_t err = LONGQ_SUCCESS;
    uint32_t ul_tmp = 0;

    /* Put data setting */
    ul_tmp = (ul_tmp | (line << SDC_SPI_BIT_SHIFT_8));
    ul_tmp = (ul_tmp | (fid << SDC_SPI_BIT_SHIFT_21));
    ul_tmp = (ul_tmp | (SDC_SPI_DRIVER_ID << SDC_SPI_BIT_SHIFT_27));
    ul_tmp = (ul_tmp | (flg << SDC_SPI_BIT_SHIFT_31));

    /* Data put */
    err = R_LONGQ_Put(gs_sdc_spi_long_que, ul_tmp);

    /* Error check */
    if (err != LONGQ_SUCCESS)
    {
        return 1;
    }
    else if (0x80000000 == (ul_tmp & 0x80000000))
    {
        return 1;
    }
    else
    {
        /* Do Nothing */
    }
#endif
    return 0;

} /* End of function r_sdc_spi_log() */

/* End of File */
