/*
* Copyright (C) 2016 Renesas Electronics Corporation and/or its affiliates  
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_ether_setting_rx64m.c
* Version      : 1.24
* Device       : RX64M
* Description  : Ethernet module device driver
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 22.07.2014 1.00     First Release
*         : 16.12.2014 1.01     Deleted header file include. Renamed file.
*         : 31.03.2016 1.02     Added changes for RX63N.
*         : 01.10.2016 1.10     Removed pin setting functions.
*         : 01.10.2017 1.13     Removed ether_clear_icu_source function.
*         : 22.11.2019 1.20     Added support for atomic control. 
*         : 20.03.2025 1.24     Changed the disclaimer in program sources
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

#include "r_ether_rx_if.h"
#include "src/r_ether_rx_private.h"

#if defined(BSP_MCU_RX64M)
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/* Check the setting values is valid. Please review the setting values
 * in r_ether_rx_config.h if error message is output */
    #if !((ETHER_CFG_AL1_INT_PRIORTY >= 1) && (ETHER_CFG_AL1_INT_PRIORTY <= 15))
        #error "ERROR- ETHER_CFG_AL1_INT_PRIORTY - Interrupt priority level is out of range defined in r_ether_rx_config.h."
    #endif

/***********************************************************************************************************************
* Function Name: ether_enable_icu
* Description  :
* Arguments    : channel -
*                    Ethernet channel number
* Return Value : none
***********************************************************************************************************************/
void ether_enable_icu(uint32_t channel)
{
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t    int_ctrl;
#endif
    ICU.IPR[IPR_ICU_GROUPAL1].BIT.IPR = ETHER_CFG_AL1_INT_PRIORTY;
    
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif
    if (ETHER_CHANNEL_0 == channel)
    {
        ICU.GENAL1.BIT.EN4 = 1;
    }
    else
    {
        ICU.GENAL1.BIT.EN5 = 1;
    }
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif
    ICU.IER[IER_ICU_GROUPAL1].BIT.IEN1 = 1;
    
} /* End of function ether_enable_icu() */

/***********************************************************************************************************************
* Function Name: ether_disable_icu
* Description  :
* Arguments    : channel -
*                    Ethernet channel number
* Return Value : none
***********************************************************************************************************************/
void ether_disable_icu(uint32_t channel)
{
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t    int_ctrl;
#endif
    ICU.IER[IER_ICU_GROUPAL1].BIT.IEN1 = 0;
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif
    if (ETHER_CHANNEL_0 == channel)
    {
        ICU.GENAL1.BIT.EN4 = 0;
    }
    else
    {
        ICU.GENAL1.BIT.EN5 = 0;
    }
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif
} /* End of function ether_disable_icu() */

/***********************************************************************************************************************
* Function Name: ether_set_phy_mode
* Description  :
* Arguments    : connect -
*                    Ethernet channel number
* Return Value : none
***********************************************************************************************************************/
void ether_set_phy_mode(uint8_t connect)
{
    if (PORT_CONNECT_ET0 == (connect & PORT_CONNECT_ET0))
    {
    #if (ETHER_CFG_MODE_SEL == 0)
        /* CH0 MII */
        MPC.PFENET.BIT.PHYMODE0 = 1;
    #elif (ETHER_CFG_MODE_SEL == 1)
        /* CH0 RMII */
        MPC.PFENET.BIT.PHYMODE0 = 0;
    #endif
    }

    if (PORT_CONNECT_ET1 == (connect & PORT_CONNECT_ET1))
    {
    #if (ETHER_CFG_MODE_SEL == 0)
        /* CH1 MII */
        MPC.PFENET.BIT.PHYMODE1 = 1;
    #elif (ETHER_CFG_MODE_SEL == 1)
        /* CH1 RMII */
        MPC.PFENET.BIT.PHYMODE1 = 0;
    #endif
    }
    
} /* End of function ether_set_phy_mode() */

#endif  /* defined(BSP_MCU_RX64M) */

/* End of File */
