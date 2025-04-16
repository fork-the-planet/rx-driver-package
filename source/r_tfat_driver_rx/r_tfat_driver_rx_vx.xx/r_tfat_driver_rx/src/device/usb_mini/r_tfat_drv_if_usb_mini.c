/***********************************************************************************************************************
* Copyright (c) 2015 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_tfat_drv_if_usb_mini.c
* Description  : TFAT driver Interface for USB Mini Firmware.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 21.01.2015 1.00    First Release
*              : 22.06.2015 1.02    Added support MCU RX231.
*              : 01.04.2016 1.03    Updated the xml file.
*              : 08.08.2019 2.00    Added support for GNUC and ICCRX.
*              : 16.04.2020 2.10    Added support for FreeRTOS and 
*                                   Renesas uITRON (RI600V4).
*              : 10.09.2020 2.20    Added support for the format function.
*              : 15.12.2023 2.40    Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*              : 30.09.2024 2.60    Changed the comment of API functions to the Doxygen style.
*              : 15.03.2025 2.61    Updated disclaimer.
***********************************************************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_tfat_drv_if_dev.h"
#include "r_tfat_driver_rx_config.h"

#if (TFAT_USB_MINI_DRIVE_NUM > 0)

#include "ff.h"                  /* TFAT define */
#include "diskio.h"              /* TFAT define */

#include "r_usb_basic_mini_if.h"
#include "r_usb_hmsc_mini_if.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
*******************************************************************************/

#if (BSP_CFG_RTOS_USED == 0)
static void R_usb_mini_hmsc_WaitLoop(void);
#endif /* BSP_CFG_RTOS_USED == 0 */

static uint16_t usb_ghmsc_tfatSecSize = 512;


/**********************************************************************************************************************
* Function Name: usb_mini_disk_initialize
*******************************************************************************************************************//**
* @brief This function initializes the disk drive.
*
* @param[in] drive  Specifies the initialize drive number.
*
* @retval TFAT_RES_OK  Normal termination.
*
* @retval Others       DSTATUS status of the disk after function execution.
*
* @details This API does not call USB driver initialize function because of USB driver limitation
* (1 time call is only accepted). Please call USB driver initialize function in user program.
* @note None
*/
DSTATUS usb_mini_disk_initialize(uint8_t drive)
{
    return  RES_OK;
}


/**********************************************************************************************************************
* Function Name: usb_mini_disk_read
*******************************************************************************************************************//**
* @brief This function reads the data from disk.
*
* @param[in]  drive     Specifies the physical drive number.
*
* @param[out] buffer    Pointer to the read buffer to store the read data. A buffer of the size equal to the
* number of bytes to be read is required.
*
* @param[in]  sector_number  Specifies the start sector number in logical block address (LBA).
*
* @param[in]  sector_count   Specifies number of sectors to read. The value can be 1 to 255.
*
* @retval DRESULT  Result of the function execution.
*
* @details This function reads the data from disk drive. The position of read data is specified using
* this function argument.
* @note None
*/
DRESULT usb_mini_disk_read (
    uint8_t drive,              /* Physical drive number            */
    uint8_t* buffer,            /* Pointer to the read data buffer  */
    uint32_t sector_number,     /* Start sector number              */
    uint32_t sector_count       /* Number of sectors to read        */
)
{
#if (BSP_CFG_RTOS_USED == 0)
    usb_tskinfo_t   *mess;
    usb_tskinfo_t   *mes;
#endif /* BSP_CFG_RTOS_USED == 0 */
    uint16_t        err;
    uint32_t        tran_byte;
    usb_info_t      info;
    usb_err_t       ret;

    /* set transfer length */
    tran_byte = (uint32_t)sector_count * usb_ghmsc_tfatSecSize;

#if (BSP_CFG_RTOS_USED == 0)
    ret = R_USB_GetInformation (&info);
    if ((USB_STS_CONFIGURED != info.status) || (USB_SUCCESS != ret))
    {
        return RES_ERROR;
    }

    /* read function */
    err = R_usb_hmsc_StrgReadSector((uint16_t)drive, buffer, sector_number, (uint16_t)sector_count, tran_byte);
    if ( USB_HMSC_OK == err )
    {
        do  /* Wait for complete R_usb_hmsc_StrgReadSector() */
        {
            ret = R_USB_GetInformation (&info);                         /* Get device connect state */
            R_usb_mini_hmsc_WaitLoop();                                 /* Task Schedule */
            err = R_USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&mess);     /* Receive read complete msg */
        }
        while ((USB_E_OK != err) && ((USB_STS_CONFIGURED == info.status) && (USB_SUCCESS == ret))); /* WAIT_LOOP */

        if ( err == USB_E_OK )
        {   /* Complete R_usb_hmsc_StrgReadSector() */
            mes = (usb_tskinfo_t *)mess;
            err = mes->keyword;
            R_USB_REL_BLK(mess->flag);
        }
        else
        {   /* Device detach */
            R_usb_mini_hmsc_WaitLoop();                                 /* Task Schedule */
            err = R_USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&mess);     /* Receive read complete msg */
            if ( USB_E_OK == err )
            {
                R_USB_REL_BLK(mess->flag);
            }
            err = USB_ERROR;
        }
    }

    if ( err != USB_E_OK )
    {
        return RES_ERROR;
    }
#else  /* BSP_CFG_RTOS_USED == 0 */
    ret = R_USB_GetInformation (&info);
    if ((USB_STS_CONFIGURED != info.status) || (USB_SUCCESS != ret))
    {
        return RES_ERROR;
    }

    /* read function */
    err = R_usb_hmsc_StrgReadSector((uint16_t)drive, buffer, sector_number, (uint16_t) sector_count, tran_byte);
    if ( USB_OK != err)
    {
        return RES_ERROR;
    }
#endif /* BSP_CFG_RTOS_USED == 0 */

    return RES_OK;
}


/**********************************************************************************************************************
* Function Name: usb_mini_disk_write
*******************************************************************************************************************//**
* @brief This function writes the data to the disk.
*
* @param[in] drive    Specifies the physical drive number.
*
* @param[in] buffer   Pointer to the data to be written.
*
* @param[in] sector_number  Specifies the start sector number in logical block address (LBA).
*
* @param[in] sector_count   Specifies number of sectors to write. The value can be 1 to 255.
*
* @retval DRESULT  Result of the function execution.
*
* @details This function writes the data to the disk drive. The position of write data is specified using
* this function argument.
* @note None
*/
DRESULT usb_mini_disk_write (
    uint8_t drive,               /* Physical drive number           */
    const uint8_t* buffer,       /* Pointer to the write data       */
    uint32_t sector_number,      /* Sector number to write          */
    uint32_t sector_count        /* Number of sectors to write      */
)
{
#if (BSP_CFG_RTOS_USED == 0)
    usb_tskinfo_t   *mess;
    usb_tskinfo_t   *mes;
#endif /* BSP_CFG_RTOS_USED == 0 */
    uint16_t        err;
    uint32_t        tran_byte;
    usb_info_t      info;
    usb_err_t       ret;

    /* set transfer length */
    tran_byte = (uint32_t)sector_count * usb_ghmsc_tfatSecSize;

#if (BSP_CFG_RTOS_USED == 0)
    ret = R_USB_GetInformation (&info);
    if ((USB_STS_CONFIGURED != info.status) || (USB_SUCCESS != ret))
    {
        return RES_ERROR;
    }

    /* write function */
    err = R_USB_HmscStrgWriteSector((uint16_t)drive, (uint8_t *)buffer
                    , sector_number, (uint16_t)sector_count, tran_byte);
    if ( USB_HMSC_OK == err )
    {
        do  /* Wait for complete R_USB_HmscStrgWriteSector() */
        {
            ret = R_USB_GetInformation (&info);                         /* Get device connect state */
            R_usb_mini_hmsc_WaitLoop();                                 /* Task Schedule */
            err = R_USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&mess);     /* Receive write complete msg */
        }
        while ((USB_E_OK != err) && ((USB_STS_CONFIGURED == info.status) && (USB_SUCCESS == ret))); /* WAIT_LOOP */

        if ( err == USB_E_OK )
        {   /* Complete R_usb_hmsc_StrgReadSector() */
            mes = (usb_tskinfo_t *)mess;
            err = mes->keyword;
            R_USB_REL_BLK(mess->flag);
        }
        else
        {   /* Device detach */
            R_usb_mini_hmsc_WaitLoop();                                 /* Task Schedule */
            err = R_USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&mess);     /* Receive read complete msg */
            if ( USB_E_OK == err )
            {
                R_USB_REL_BLK(mess->flag);
            }
            err = USB_ERROR;
        }
    }

    if ( err != USB_E_OK )
    {
        return RES_ERROR;
    }
#else  /* BSP_CFG_RTOS_USED == 0 */
    ret = R_USB_GetInformation (&info);
    if ((USB_STS_CONFIGURED != info.status) || (USB_SUCCESS != ret))
    {
        return RES_ERROR;
    }

    /* write function */
    err = R_USB_HmscStrgWriteSector((uint16_t)drive, (uint8_t *)buffer, sector_number, (uint16_t) sector_count,
                                    tran_byte);
    if ( USB_OK != err)
    {
        return RES_ERROR;
    }

#endif /* BSP_CFG_RTOS_USED == 0 */
    return RES_OK;
}


/**********************************************************************************************************************
* Function Name: usb_mini_disk_ioctl
*******************************************************************************************************************//**
* @brief This function controls the drive.
*
* @param[in] drive   Specifies the physical drive number.
*
* @param[in] command Specifies the command code. The command code will always be 0.
*
* @param[in] buffer  Pointer should always be a NULL pointer.
*
* @retval DRESULT  Result of the function execution.
*
* @details The usb_mini_disk_ioctl function is used only by the f_sync function amongst all the TFAT FIT functions.
* Users who do not plan to use f_sync function in their applications can skip the implementation for this
* particular driver interface function.\n
* For users who wish to use f_sync function in their applications, the command CTRL_SYNC has to be implemented.\n
* For users who wish to use f_sync function in their applications, this particular driver interface function
* will have to be implemented. This driver function should consist of the code to finish off any pending write
* process. If the disk i/o module has a write back cache, the dirty sector must be flushed immediately.The f_sync
* function will perform a save operation to the unsaved data related to the file object passed as argument.
* @note None
*/
DRESULT usb_mini_disk_ioctl (
    uint8_t drive,               /* Drive number             */
    uint8_t command,             /* Control command code     */
    void* buffer                 /* Data transfer buffer     */
)
{
#if FF_USE_MKFS == 1
#if (BSP_CFG_RTOS_USED == 0)
    usb_tskinfo_t   *p_mess;
    usb_tskinfo_t   *p_mes;
#endif /* BSP_CFG_RTOS_USED == 0 */
    usb_info_t      info;
    usb_err_t       ret;
    uint32_t        num_blocks;
    uint32_t        block_length;
    uint16_t        err;
    uint8_t         buff[8];
#endif

    if ((NULL == buffer) && (CTRL_SYNC != command))
    {
        return RES_PARERR;
    }

    switch (command)
    {
        case CTRL_SYNC:

        break;

        case GET_SECTOR_COUNT:
        case GET_BLOCK_SIZE:
#if FF_USE_MKFS
            ret = R_USB_GetInformation (&info);
            if ((USB_STS_CONFIGURED != info.status) || (USB_SUCCESS != ret))
            {
                return RES_ERROR;
            }

#if (BSP_CFG_RTOS_USED == 0)
            /* Get format capacities */
            err = usb_hmsc_strg_user_command(USB_ATAPI_READ_CAPACITY, buff, (usb_hmsc_cb_t)usb_hstd_dummy_function);
            if (USB_OK != err)
            {
                return RES_ERROR;
            }

            do  /* Wait for complete usb_hmsc_strg_user_command() */
            {
                ret = R_USB_GetInformation (&info);                         /* Get device connect state */
                /*
                 * The completion judgment of usb_hmsc_strg_user_command() is the message sent by getting
                 * the memory block of the previous stage. R_usb_mini_hmsc_WaitLoop() and R_USB_RCV_MSG()
                 * were required to receive the message.
                 */
                R_usb_mini_hmsc_WaitLoop();                                 /* Task Schedule */
                err = R_USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&p_mess);   /* Receive capacities complete msg */
            }
            while ((USB_E_OK != err) && ((USB_STS_CONFIGURED == info.status) && (USB_SUCCESS == ret))); /* WAIT_LOOP */

            if (USB_E_OK == err)
            {   /* Complete usb_hmsc_strg_user_command() */
                p_mes = (usb_tskinfo_t *)p_mess;
                err = p_mes->keyword;
                R_USB_REL_BLK(p_mess->flag);
            }
            else
            {   /* Device detach */
                R_usb_mini_hmsc_WaitLoop();                                 /* Task Schedule */
                err = R_USB_RCV_MSG(USB_HSTRG_MBX, (usb_msg_t**)&p_mess);   /* Receive capacities complete msg */
                if (USB_E_OK == err)
                {
                    R_USB_REL_BLK(p_mess->flag);
                }
                err = USB_ERROR;
            }
#else /* (BSP_CFG_RTOS_USED == 0) */
            err = usb_hmsc_strg_user_command(USB_ATAPI_READ_CAPACITY, buff);
            if (USB_OK != err)
            {
                return RES_ERROR;
            }
#endif /* BSP_CFG_RTOS_USED == 0 */

            /* eight bytes of READ CAPACITY data */
            block_length = (uint32_t) buff[7];
            block_length |= ((uint32_t) buff[6] << 8);
            block_length |= ((uint32_t) buff[5] << 16);
            block_length |= ((uint32_t) buff[4] << 24);
            block_length = block_length / USB_HMSC_STRG_SECTSIZE;

            if (GET_SECTOR_COUNT == command)
            {
                num_blocks = (uint32_t) buff[3];
                num_blocks |= ((uint32_t) buff[2] << 8);
                num_blocks |= ((uint32_t) buff[1] << 16);
                num_blocks |= ((uint32_t) buff[0] << 24);
                num_blocks = (num_blocks + 1) * block_length;
                /* Get USB mini number of blocks */
                ((uint32_t *)buffer)[0] = num_blocks;
            }
            else if (GET_BLOCK_SIZE == command)
            {
                /* Get USB mini block length */
                ((uint32_t *)buffer)[0] = block_length;
            }
            else
            {
                return RES_ERROR;
            }
#else /* FF_USE_MKFS == 0 */
        return RES_PARERR;
#endif /* FF_USE_MKFS == 1 */
        break;

        case GET_SECTOR_SIZE:
#if FF_MAX_SS == FF_MIN_SS
            return RES_PARERR;
#else
            ((uint32_t *)buffer)[0] = (uint32_t)USB_HMSC_STRG_SECTSIZE;
#endif
        break;

        case CTRL_TRIM:

        break;

        default:
            return RES_PARERR;
        break;
    }
    return RES_OK;
}


/**********************************************************************************************************************
* Function Name: usb_mini_disk_status
*******************************************************************************************************************//**
* @brief This function gets the information about disk drive.
*
* @param[in] drive  Specifies the physical drive number.
*
* @retval TFAT_RES_OK  Normal termination.
*
* @retval Others       DSTATUS status of the disk after function execution.
*
* @details This function should consist of the code that checks the disk and returns the current disk status.
* The disk status can have any of the three values, see Section 2.10 in the application note for details.
* The disk status can be returned by updating the return value with the macros related to disk status.
* @note None
*/
DSTATUS usb_mini_disk_status (
    uint8_t drive                 /* Physical drive number    */
)
{

    /*  Please put the code for disk_status driver interface
         function over here.  */
    /*  Please refer the application note for details.  */
    return RES_OK;
}

#if (BSP_CFG_RTOS_USED == 0)
/**********************************************************************************************************************
* Function Name: R_usb_mini_hmsc_WaitLoop
*******************************************************************************************************************//**
* @brief This function waits for the data read/write.
*
* @details Please refer to the USB driver document for details.
*
* @note None
*/
void R_usb_mini_hmsc_WaitLoop(void)
{
    if ( R_usb_cstd_Scheduler() == USB_FLGSET )
    {
        R_usb_hstd_HcdTask();
        R_usb_hstd_MgrTask();
        R_usb_hmsc_Task();
    }
}
#endif /* BSP_CFG_RTOS_USED == 0 */

#endif /* (TFAT_USB_MINI_DRIVE_NUM > 0) */
/******************************************************************************
End  of file
******************************************************************************/
