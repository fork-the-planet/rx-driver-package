/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
* File Name    : rm_mcuboot_port.c
* Description  : This module implements function for starting application image.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           21.04.2025 1.00    First Release
*           30.06.2025 1.01    Added support for RX66N, RX72M and RX671
***********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

#include <stdio.h>
#include "rm_mcuboot_if.h"
#include "bootutil/bootutil_log.h"
#include "flash_map_backend/flash_map_backend.h"
#include "sysflash/sysflash.h"
#include "r_flash_rx_if.h"
#include "r_flash_fcu.h"
#include "r_flash_group.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

#define MSG_SW_RESET            "software reset...\r\n"
#define MSG_BANK_SWAP           "bank swap ...\r\n"
#define MSG_ERROR_BANK_SWAP     "Bank swap failure.\r\n"

#if defined(MCUBOOT_USE_RSIP)
rsip_instance_ctrl_t g_rsip_ctrl;
rsip_cfg_t g_rsip_cfg;
#endif

static void start_app(uint32_t pc);

/**********************************************************************************************************************
* Function Name: start_app
* Description  : This function jumps to the application image.
* Arguments    : uint32_t pc -
*                    Address of the image to run
* Return Value : none
**********************************************************************************************************************/
static void start_app (uint32_t pc)
{
    /* This is a naked/stackless function.
     * Do not pass arguments to the inline assembly when the GCC compiler is
     * used. */

    R_BSP_InterruptsDisable();
#if BSP_CFG_BOOTLOADER_PROJECT
    R_BSP_ClockReset_Bootloader();
#else
#warning "MCU clock settings are not reset before application execution."
#endif

    ((void (*)(void)) pc)();
}
/**********************************************************************************************************************
* End of function start_app (uint32_t pc)
**********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name: RM_MCUBOOT_GetVersion
 * Description  : Get rm_mcuboot module version
 * Arguments    : none
 * Return Value : The version number is encoded where the top 2 bytes are the major version number
 *                and the bottom 2 bytes are the minor version number.
 *                For example, Version 4.25 would be returned as 0x00040019.
 *********************************************************************************************************************/
uint32_t RM_MCUBOOT_GetVersion(void){
    return (((((uint32_t)MCUBOOT_VERSION_MAJOR) << 16) | (uint32_t)MCUBOOT_VERSION_MINOR));
}
/**********************************************************************************************************************
* End of function RM_MCUBOOT_GetVersion(void)
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: RM_MCUBOOT_BootApp
* Description  : Cleans up resources used by bootloader port and
*                branches to application image.
* Arguments    : struct boot_rsp * rsp
* Return Value : none
**********************************************************************************************************************/
void RM_MCUBOOT_BootApp (struct boot_rsp * p_rsp)
{
    BOOT_LOG_DBG("Starting Application Image\n");
    BOOT_LOG_DBG("Image Offset: 0x%x\n",
                ((int32_t) p_rsp->br_image_off));

    /* The vector table is located after the header.
     * Only running from internal flash is supported now. */
    uint32_t vector_table = (p_rsp->br_image_off + p_rsp->br_hdr->ih_hdr_size
                            + p_rsp->br_hdr->ih_img_size) - (0x4U);

#if defined (MCUBOOT_DIRECT_XIP)
#if RM_MCUBOOT_DUAL_BANK_ENABLED
    if (vector_table <= (uint32_t)FLASH_CF_LO_BANK_HI_ADDR)
    {
        flash_err_t err;

        BOOT_LOG_DBG(MSG_BANK_SWAP);
        R_BSP_InterruptsDisable();
        err = R_FLASH_Control(FLASH_CMD_BANK_TOGGLE, NULL);
        R_BSP_InterruptsEnable();
        if(FLASH_SUCCESS != err)
        {
            BOOT_LOG_DBG(MSG_ERROR_BANK_SWAP);
        }

        /* Reset the MCU to swap to the other bank */
        BOOT_LOG_DBG(MSG_SW_RESET);
        R_BSP_SoftwareReset();
    }
#endif
#endif

    uint32_t * p_app_image = (uint32_t *) vector_table;
    uint32_t   app_pc    = p_app_image[0];

    rm_mcuboot_cleanup();

    BOOT_LOG_DBG("Vector Table: 0x%x. PC=0x%x\n",
                (uint32_t) vector_table, (uint32_t) app_pc);

    /* Jumps to the application image. */
    start_app(app_pc);
}
/**********************************************************************************************************************
* End of function RM_MCUBOOT_BootApp (struct boot_rsp * rsp)
**********************************************************************************************************************/
