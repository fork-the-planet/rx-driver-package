/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_hhid_api.c
 * Description  : USB host HID class driver API function code.
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 01.09.2014 1.00    First Release
 *         : 01.06.2015 1.01    Added RX231.
 *         : 29.12.2015 1.02    Minor Update.
 *         : 30.11.2018 1.10    Supporting Smart Configurator
 *         : 30.06.2020 1.20    Added support for RTOS.
 *         : 30.04.2024 1.30    Added support for RX261.
 *         : 20.03.2025 1.31    Changed the disclaimer.
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
************************************************************************************************************************/

#include "r_usb_hhid.h"

#if defined(USB_CFG_HHID_USE)
/***********************************************************************************************************************
 Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
***********************************************************************************************************************/


/***********************************************************************************************************************
 * Function Name   : R_USB_HhidGetMxps
 *******************************************************************************************************************//**
 * @brief  Obtains the max packet size for the HID device.
 * @param[in]  p_ctrl          Pointer to usb_ctrl_t structure area
 * @param[out] p_mxps          Pointer to the area to store the max packe size
 * @param[in]  dir             Transfer direction
 * @retval     USB_SUCCESS     Successfully completed
 * @retval     USB_ERR_PARA    Parameter error
 * @retval     USB_ERR_NG      Other error
 * @details Based on the information assigned to the usb_crtl_t structure (the member module and address), 
 * obtains max packet size for the connected HID device. The max packet size is set to the area indicated 
 * by the second argument (p_mxps). 
 * Set the direction (USB_IN / USB_OUT) of the max packet size which the user want to obtain  to the third argument (3rd)
 * @note The argument (p_ctrl) is not supported when using RX100/RX200 series MCU.
 */
usb_err_t R_USB_HhidGetMxps(uint16_t *p_mxps, uint8_t dir)
{
    usb_err_t   err;
    usb_info_t  info;
    uint16_t    pipe;
    uint16_t    pipe_bit_map;

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if  (USB_NULL == p_mxps)
    {
        return USB_ERR_PARA;
    }
#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    err = R_USB_GetInformation(&info);
    if ((USB_SUCCESS != err) || (USB_STS_CONFIGURED != info.status))
    {
        return USB_ERR_NG;
    }

    if (USB_IN == dir)
    {
        pipe = USB_CFG_HHID_INT_IN;
    }
    else if (USB_OUT == dir)
    {
        pipe = USB_CFG_HHID_INT_OUT;
    }
    else
    {
#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
        return USB_ERR_PARA;
#else  /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */
        return USB_ERR_NG;
#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */
    }

    err = R_USB_GetUsePipe (&pipe_bit_map);
    if (USB_SUCCESS != err)
    {
        return USB_ERR_NG;
    }

    if (0 == ((1 << pipe) & pipe_bit_map))
    {
        return USB_ERR_NG;
    }

    *p_mxps = usb_cstd_get_maxpacket_size(pipe);
    return USB_SUCCESS;
}
/***********************************************************************************************************************
 End of function R_USB_HhidGetMxps
************************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name   : R_USB_HhidGetType
 *******************************************************************************************************************//**
 * @brief  Obtains type information for the HID device.
 * @param[in]  p_ctrl          Pointer to usb_ctrl_t structure area
 * @param[out] p_type          Pointer to the area to store the type information
 * @retval     USB_SUCCESS     Successfully completed
 * @retval     USB_ERR_PARA    Parameter error
 * @retval     USB_ERR_NG      Other error
 * @details Based on the information assigned to the usb_crtl_t structure (the member module and address), 
 * obtains type information (mouse, keyboard, etc.) for the connected HID device. 
 * The type information is set to the area indicated by the second argument (p_type).
 * @note The argument (p_ctrl) is not supported when using RX100/RX200 series MCU.
 */
usb_err_t R_USB_HhidGetType(uint8_t *p_type)
{
    usb_info_t  info;

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_NULL == p_type)
    {
        return USB_ERR_PARA;
    }

#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    R_USB_GetInformation(&info);
    if (USB_STS_CONFIGURED != info.status)
    {
        return USB_ERR_NG;
    }

    *p_type = usb_hhid_get_hid_protocol();
    return USB_SUCCESS;
}
/***********************************************************************************************************************
 End of function R_USB_HhidGetType
************************************************************************************************************************/

#endif /* defined(USB_CFG_HHID_USE) */

/***********************************************************************************************************************
 End  Of File
************************************************************************************************************************/
