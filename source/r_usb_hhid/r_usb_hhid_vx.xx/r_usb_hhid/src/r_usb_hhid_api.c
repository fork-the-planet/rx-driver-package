/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2014(2023) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_hhid_api.c
 * Description  : Host HID class driver code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 "R_USB_HhidDriverRelease","R_USB_HhidTransferEnd","R_USB_HhidChangeDeviceState"
 *                           "R_USB_HhidGetReportLength","R_USB_HhidClassRequest","R_USB_HhidPipeTransfer" is deleted.
 *         : 31.03.2018 1.23 Supporting Smart Configurator.
 *         : 01.03.2020 1.30 RX72N/RX66N is added and uITRON is supported.
 *         : 30.04.2021 1.31 RX671 is added.
 *         : 30.09.2023 1.42 USBX HCDC is supported.
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
************************************************************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_reg_access.h"

#include "r_usb_hhid_if.h"
#include "r_usb_hhid.h"

#if defined(USB_CFG_HHID_USE)
  #if (BSP_CFG_RTOS_USED != 5)    /* !Azure RTOS */

/***********************************************************************************************************************
 Renesas Abstracted USB Driver functions
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
usb_err_t R_USB_HhidGetType(usb_ctrl_t *p_ctrl, uint8_t *p_type)
{
    usb_err_t   err;
    usb_info_t  info;

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_NULL == p_ctrl)
    {
        return USB_ERR_PARA;
    }

    if (USB_NULL == p_type)
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if( (USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) )
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)
    if( USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T) */
#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    err = R_USB_GetInformation(p_ctrl, &info);
    if ((USB_SUCCESS != err) || (USB_STS_CONFIGURED != info.status))
    {
        return USB_ERR_NG;
    }
    *p_type = usb_hhid_get_hid_protocol( p_ctrl->module, p_ctrl->address );
    return USB_SUCCESS;

}
/***********************************************************************************************************************
 End of function R_USB_HhidGetType
************************************************************************************************************************/


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
usb_err_t R_USB_HhidGetMxps(usb_ctrl_t *p_ctrl, uint16_t *p_mxps, uint8_t dir)
{
    usb_err_t   err;
    usb_info_t  info;
    usb_utr_t   utr;
    uint16_t    pipe;
    uint16_t    pipe_bit_map;

#if USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE
    if (USB_NULL == p_ctrl)
    {
        return USB_ERR_PARA;
    }

    if (USB_NULL == p_mxps)
    {
        return USB_ERR_PARA;
    }

    /* Argument Checking */
    if( (USB_IP0 != p_ctrl->module) && (USB_IP1 != p_ctrl->module) )
    {
        return USB_ERR_PARA;
    }

#if defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T)
    if( USB_IP1 == p_ctrl->module)
    {
        return USB_ERR_PARA;
    }
#endif /* defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX63T) || defined(BSP_MCU_RX72T) */

    if ((USB_IN != dir) && (USB_OUT != dir))
    {
        return USB_ERR_PARA;
    }

#endif /* USB_CFG_PARAM_CHECKING == USB_CFG_ENABLE */

    err = R_USB_GetInformation(p_ctrl, &info);
    if ((USB_SUCCESS != err) || (USB_STS_CONFIGURED != info.status))
    {
        return USB_ERR_NG;
    }

    if (USB_IN == dir)
    {
        pipe = usb_hstd_get_pipe_no (p_ctrl->module, p_ctrl->address, USB_HHID, USB_EP_INT, USB_PIPE_DIR_IN);

    }
    else if (USB_OUT == dir)
    {
        pipe = usb_hstd_get_pipe_no (p_ctrl->module, p_ctrl->address, USB_HHID, USB_EP_INT, USB_PIPE_DIR_OUT);

    }
    else
    {
        return USB_ERR_NG;
    }

    err = R_USB_GetUsePipe (p_ctrl, &pipe_bit_map);
    if (USB_SUCCESS != err)
    {
        return USB_ERR_NG;
    }

    if (0 == ((1 << pipe) & pipe_bit_map))
    {
        return USB_ERR_NG;
    }

    utr.ip = p_ctrl->module;
    utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip);

    *p_mxps = usb_cstd_get_maxpacket_size(&utr, pipe);
    return USB_SUCCESS;

}
/***********************************************************************************************************************
 End of function R_USB_HhidGetMxps
************************************************************************************************************************/

  #endif /* BSP_CFG_RTOS_USED != 5 !Azure RTOS */
#endif /* defined(USB_CFG_HHID_USE) */
/***********************************************************************************************************************
 End  Of File
************************************************************************************************************************/
