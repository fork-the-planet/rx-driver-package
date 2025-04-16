/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_hstorage_driver_api.c
 * Description  : USB Host Storage Driver API
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 01.09.2014 1.00    First Release
 *         : 01.06.2015 1.01    Added RX231.
 *         : 30.11.2018 1.10    Supporting Smart Configurator
 *         : 30.06.2020 1.20    Added support for RTOS.
 *         : 20.03.2025 1.31    Changed the disclaimer.
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

#include "r_usb_hmsc_mini_if.h"

#if defined(USB_CFG_HMSC_USE)

/***********************************************************************************************************************
Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/


/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_usb_hmsc_StrgReadSector
 * Description  : Releases drive
 * Arguments    : uint16_t side        : Side(no use)
                : uint8_t  *p_buff     : Buffer address
                : uint32_t secno       : Sector number
                : uint16_t seccnt      : Sector count
                : uint32_t trans_byte  : Trans byte
 * Return Value : uint16_t             : [DONE/ERROR]
 ***********************************************************************************************************************/
uint16_t R_usb_hmsc_StrgReadSector (uint16_t side, uint8_t *p_buff, uint32_t secno, uint16_t seccnt,
        uint32_t trans_byte)
{
    uint16_t result;

    /* Device Status */
    if (USB_HMSC_DEV_ATT != usb_hmsc_get_device_status())
    {
        return (USB_ERROR);
    }

    result = usb_hmsc_read10(p_buff, secno, seccnt, trans_byte);
#if (BSP_CFG_RTOS_USED != 0)    /* Use RTOS */
    if (USB_HMSC_OK == result)
    {
        result = USB_OK;
    }
    else
    {
        usb_hmsc_error_process(result);

        result = USB_ERROR;
    }
#endif /* (BSP_CFG_RTOS_USED != 0) */

    return (result);
}
/***********************************************************************************************************************
 End of function R_usb_hmsc_StrgReadSector
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_USB_HmscStrgWriteSector
 * Description  : Writes sector information
 * Arguments    : uint16_t side        : Side(no use)
                : uint8_t  *p_buff     : Buffer address
                : uint32_t secno       : Sector number
                : uint16_t seccnt      : Sector count
                : uint32_t trans_byte  : Trans byte
 * Return Value : uint16_t             : [DONE/ERROR]
 ***********************************************************************************************************************/
uint16_t R_USB_HmscStrgWriteSector (uint16_t side, uint8_t *p_buff, uint32_t secno, uint16_t seccnt,
        uint32_t trans_byte)
{
    uint16_t result;

    /* Device Status */
    if (USB_HMSC_DEV_ATT != usb_hmsc_get_device_status())
    {
        return (USB_ERROR);
    }

    result = usb_hmsc_write10(p_buff, secno, seccnt, trans_byte);
#if (BSP_CFG_RTOS_USED != 0)    /* Use RTOS */
    if (USB_HMSC_OK == result)
    {
        result = USB_OK;
    }
    else
    {
        usb_hmsc_error_process(result);

        result = USB_ERROR;
    }
#endif /* (BSP_CFG_RTOS_USED != 0) */

    return (result);
}
/***********************************************************************************************************************
 End of function R_USB_HmscStrgWriteSector
 ***********************************************************************************************************************/

#endif /* defined(USB_CFG_HMSC_USE) */
/***********************************************************************************************************************
 End  Of File
 ***********************************************************************************************************************/
