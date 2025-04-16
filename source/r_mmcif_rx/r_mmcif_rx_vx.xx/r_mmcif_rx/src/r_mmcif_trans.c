/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_mmcif_trans.c
* Description  : Interface file for MMC API for RX
**********************************************************************************************************************/
/**********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 03.09.2014 1.00    First Release
*              : 30.07.2019 1.06    Add WAIT_LOOP.
*              : 29.11.2024 1.20    Updated file description.
*              : 15.03.2025 1.21    Updated disclaimer.
**********************************************************************************************************************/

/**********************************************************************************************************************
Includes <System Includes> , "Project Includes"
**********************************************************************************************************************/
/* Public interface header file for this package. */
#include "r_mmcif_rx_if.h"
/* Private header file for this package. */
#include "./src/r_mmcif_rx_private.h"


/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/

/**********************************************************************************************************************
Typedef definitions
**********************************************************************************************************************/

/**********************************************************************************************************************
Private global variables and functions
**********************************************************************************************************************/


/**********************************************************************************************************************
* Outline      : Transfer Data using PIO Mode
* Function Name: r_mmcif_software_trans
* Description  : Transfers data to/from the MMC by PIO mode
* Arguments    : uint32_t           channel             ;   MMC Channel No.
*              : uint8_t            *p_buff             ;   Destination/Source data buffer
*              : int32_t            cnt                 ;   Number of transfer bytes
*              : int32_t            dir                 ;   Transfer direction
* Return Value : MMC_SUCCESS                            ;   Successful operation
*              : other                                  ;   Failed operation
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
mmc_status_t r_mmcif_software_trans(uint32_t channel, uint8_t *p_buff, int32_t cnt, int32_t dir)
{
    mmc_mmchndl_t       *p_hndl = 0;
    int32_t                   j = 0;
    mmc_status_t        (*func)(uint8_t *, uint32_t, int32_t);

    p_hndl = MMC_GET_HNDL(channel);

    if (MMC_TRANS_READ == dir)
    {
        func = r_mmcif_dev_read_data;
    }
    else
    {
        func = r_mmcif_dev_write_data;
    }

    /* WAIT_LOOP */
    for (j = cnt; j > 0; j--)
    {
        /* ---- Wait for the read enable or the wrte enable interrupt. ---- */
        if (r_mmcif_dev_int_wait(channel, MMC_TIMEOUT_MULTIPLE) != MMC_SUCCESS)
        {
            R_MMCIF_Log_Func(MMC_DEBUG_ERR_ID, (uint32_t)MMC_TRANS, __LINE__);
            r_mmcif_set_err(channel, MMC_ERR_HOST_TOE);
            break;
        }
        if (p_hndl->ceint2 & MMC_CEINT2_ALL_ERR)
        {
            R_MMCIF_Log_Func(MMC_DEBUG_ERR_ID, (uint32_t)MMC_TRANS, __LINE__);
            r_mmcif_check_info2_err(channel);
            break;
        }
        if (MMC_TRANS_READ == dir)
        {
            r_mmcif_clear_info(channel, MMC_CEINT1_BUFR_ENAB, 0x0000);        /* Clear the read enable bit. */
        }
        else
        {
            r_mmcif_clear_info(channel, MMC_CEINT1_BUFW_ENAB, 0x0000);        /* Clear the write enable bit. */
        }

        /* Write/Read to/from MMC_CEDATA by 1 sector. */
        if ((*func)(p_buff, ((uint32_t)p_hndl->reg_base + MMC_CEDATA), MMC_TRANS_BLOCK_SIZE) != MMC_SUCCESS)
        {
            R_MMCIF_Log_Func(MMC_DEBUG_ERR_ID, (uint32_t)MMC_TRANS, __LINE__);
            r_mmcif_set_err(channel, MMC_ERR_CPU_IF);
            break;
        }

        /* Update buffer. */
        p_buff += MMC_TRANS_BLOCK_SIZE;
        
        /* ---- Check the stop flag. ---- */
        if (p_hndl->stop)
        {
            p_hndl->stop = 0;
            R_MMCIF_Log_Func(MMC_DEBUG_ERR_ID, (uint32_t)MMC_TRANS, __LINE__);
            p_hndl->error = MMC_ERR_STOP;   /* Set an error code forcibly. */
            break;
        }
    }
    return p_hndl->error;
}


/* End of File */
