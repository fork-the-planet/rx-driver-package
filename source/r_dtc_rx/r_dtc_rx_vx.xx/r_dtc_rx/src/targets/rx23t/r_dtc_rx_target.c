/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target.c
* Device       : RX23T
* Tool-Chain   : Renesas RXC Toolchain v2.03.00
* OS           : not use
* H/W Platform : not use
* Description  : Functions for using DTC on RX23T devices.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 17.03.2014 1.00    Initial revision
*         : 17.07.2014 2.00    Second  revision
*         : 12.11.2014 2.01    Added RX113.
*         : 30.01.2015 2.02    Added RX71M.
*         : 24.12.2015 2.04    Added RX130, RX23T and RX24T.
*         : 31.07.2017 2.08    Fixed to correspond to Renesas coding rule.
*         : 25.11.2019 3.30    Added support for atomic control.
*         : 27.12.2022 4.21    Updated slash format of included header file paths for Linux compatibility.
*         : 15.03.2025 4.51    Updated disclaimer.
*******************************************************************************/

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
/* Defines for DTC support */
#include "r_dtc_rx_if.h"
#include "./src/r_dtc_rx_private.h"

/* Check MCU Group */
#if defined(BSP_MCU_RX23T)

/*******************************************************************************
Exported global variables (to be accessed by other files)
*******************************************************************************/
/* The array of all interrupt source */
const dtc_activation_source_t g_source_array[DTC_NUM_INTERRUPT_SRC] =
{
    DTCE_ICU_SWINT, DTCE_CMT0_CMI0,DTCE_CMT1_CMI1, DTCE_CMT2_CMI2,DTCE_CMT3_CMI3,
    DTCE_RSPI0_SPRI0, DTCE_RSPI0_SPTI0, DTCE_ICU_IRQ0, DTCE_ICU_IRQ1, DTCE_ICU_IRQ2,
    DTCE_ICU_IRQ3, DTCE_ICU_IRQ4, DTCE_ICU_IRQ5, DTCE_S12AD_S12ADI, DTCE_S12AD_GBADI,
    DTCE_CMPC0_CMPC0, DTCE_CMPC1_CMPC1, DTCE_CMPC2_CMPC2, DTCE_MTU0_TGIA0, 
    DTCE_MTU0_TGIB0, DTCE_MTU0_TGIC0, DTCE_MTU0_TGID0, DTCE_MTU1_TGIA1, DTCE_MTU1_TGIB1,
    DTCE_MTU2_TGIA2, DTCE_MTU2_TGIB2, DTCE_MTU3_TGIA3, DTCE_MTU3_TGIB3, DTCE_MTU3_TGIC3,
    DTCE_MTU3_TGID3, DTCE_MTU4_TGIA4, DTCE_MTU4_TGIB4, DTCE_MTU4_TGIC4, DTCE_MTU4_TGID4,
    DTCE_MTU4_TCIV4, DTCE_MTU5_TGIU5, DTCE_MTU5_TGIV5, DTCE_MTU5_TGIW5, DTCE_TMR0_CMIA0,
    DTCE_TMR0_CMIB0, DTCE_TMR1_CMIA1, DTCE_TMR1_CMIB1, DTCE_TMR2_CMIA2, DTCE_TMR2_CMIB2,
    DTCE_TMR3_CMIA3, DTCE_TMR3_CMIB3, DTCE_SCI1_RXI1, DTCE_SCI1_TXI1, DTCE_SCI5_RXI5,
    DTCE_SCI5_TXI5, DTCE_RIIC0_RXI0, DTCE_RIIC0_TXI0
};


#if ((0 != BSP_CFG_USER_LOCKING_ENABLED) || (bsp_lock_t != BSP_CFG_USER_LOCKING_TYPE) \
      || (DTC_ENABLE != DTC_CFG_USE_DMAC_FIT_MODULE))
/*******************************************************************************
* Function Name: r_dtc_check_DMAC_locking_byUSER
* Description  : Checks all DMAC channel locking.
* Arguments    : none -
* Return Value : true -
*                    All DMAC channels are unlocked. 
*                false -
*                    One or some DMAC channels are locked.
*
*******************************************************************************/
bool r_dtc_check_DMAC_locking_byUSER(void)
{
    bool ret = true;

    /* User has to check the locking of DMAC by themselves. */
    /* do something */

    return ret;
}
#endif


/*******************************************************************************
* Function Name: r_dtc_module_enable
* Description  : Releases module stop state.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void r_dtc_module_enable(void)
{
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
bsp_int_ctrl_t int_ctrl;
#endif
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif
    /* Release from module stop state. */
    MSTP(DTC) = 0;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif
    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

    return;
}
/******************************************************************************
 End of function r_dtc_module_enable
 *****************************************************************************/

/*******************************************************************************
* Function Name: r_dtc_module_disable
* Description  : Sets to module stop state.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void r_dtc_module_disable(void)
{
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
bsp_int_ctrl_t int_ctrl;
#endif
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif
    /* Set to module stop state. */
    MSTP(DTC) = 1;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif
    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);

    return;
}
/******************************************************************************
 End of function r_dtc_module_disable
 *****************************************************************************/


#endif /* defined(BSP_MCU_RX23T) */

/* End of File */

