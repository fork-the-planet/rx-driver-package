/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_bsp_vbatt.c
* Description  : Contains battery backup function routines.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 26.07.2019 1.00     First Release
*         : 20.11.2020 1.01     Fixed the vbatt_voltage_stability_wait function for updated TN-RX*-A0214A.
*         : 26.02.2025 1.02     Changed the disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

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

/**********************************************************************************************************************
 * Function Name: R_BSP_VbattInitialSetting
 ******************************************************************************************************************//**
* @brief Initialize the battery backup function(VBATT).
 * @details Initialize the battery backup function(VBATT). This processing is needed for using the BSP and peripheral 
 * FIT modules. Call this function only if all the following conditions are satisfied.
 * - The BSP startup is disabled.
 * - Do not use the battery backup function.
 * - Access to the RTC related registers.
 * 
 * Call this function before accessing RTC related registers.
 * @note The R_BSP_VbattInitialSetting function performs a part of processing in the startup function. This function 
 * is enabled if BSP startup is disabled and the battery backup function is not used.
 * See Section 5.24 in the application note for more information.
 */
#if (BSP_CFG_STARTUP_DISABLE != 0) && (BSP_CFG_VBATT_ENABLE == 0)
void R_BSP_VbattInitialSetting(void)
{
    /* Wait for power voltage stabilization of VBATT function. */
    vbatt_voltage_stability_wait();
}
#endif

/***********************************************************************************************************************
* Function Name: vbatt_voltage_stability_wait
* Description  : Wait for power voltage stabilization of VBATT function.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void vbatt_voltage_stability_wait (void)
{
#if (BSP_CFG_VBATT_ENABLE == 0)
    /* Protect off. DO NOT USE R_BSP_RegisterProtectDisable()! (not initialized yet) */
    SYSTEM.PRCR.WORD = 0xA508;

    /* Disable vbatt function. */
    SYSTEM.VBATTCR.BIT.VBATTDIS = 1;

    /* Wait 5 ms. */
    R_BSP_SoftwareDelay((uint32_t)5, BSP_DELAY_MILLISECS);

    /* WAIT_LOOP */
    while (0 != SYSTEM.VBATTSR.BIT.VBATRLVDETF)
    {
        /* Reset Battery Backup Power Voltage Drop Detection Flag. */
        SYSTEM.VBATTSR.BIT.VBATRLVDETF = 0;
    }

    /* Protect on. */
    SYSTEM.PRCR.WORD = 0xA500;
#elif (BSP_CFG_VBATT_ENABLE == 1)
    /* Wait 30 us. */
    R_BSP_SoftwareDelay((uint32_t)30, BSP_DELAY_MICROSECS);
#endif /* (BSP_CFG_VBATT_ENABLE == 1) */

} /* End of function vbatt_voltage_stability_wait() */

