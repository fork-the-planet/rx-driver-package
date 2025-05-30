/***********************************************************************************************************************
* Copyright (c) 2023 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* File Name    : r_dtc_rx_target.c
* Description  : Functions for using DTC on RX26T devices.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 31.03.2023 1.00    First Release
*         : 15.03.2025 4.51    Updated disclaimer.
*******************************************************************************/

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
/* Defines for DTC support */
#include "r_dtc_rx_if.h"
#include "./src/r_dtc_rx_private.h"

/* Check MCU Group */
#if defined(BSP_MCU_RX26T)

/*******************************************************************************
Exported global variables (to be accessed by other files)
*******************************************************************************/
/* The array of all interrupt source */
const dtc_activation_source_t g_source_array[DTC_NUM_INTERRUPT_SRC] =
{
    DTCE_ICU_SWINT2,DTCE_ICU_SWINT,
    DTCE_CMT0_CMI0,
    DTCE_CMT1_CMI1,
    DTCE_CMT2_CMI2,
    DTCE_CMT3_CMI3,
    DTCE_RSPI0_SPRI0,DTCE_RSPI0_SPTI0,
    DTCE_RI3C0_RESPI,DTCE_RI3C0_CMDI,DTCE_RI3C0_IBII,DTCE_RI3C0_RCVI,
    DTCE_RSPIA0_SPRI,DTCE_RSPIA0_SPTI,
    DTCE_RIIC0_RXI0,DTCE_RIIC0_TXI0,
    DTCE_SCI1_RXI1,DTCE_SCI1_TXI1,
    DTCE_ICU_IRQ0,DTCE_ICU_IRQ1,DTCE_ICU_IRQ2,DTCE_ICU_IRQ3,DTCE_ICU_IRQ4,DTCE_ICU_IRQ5,DTCE_ICU_IRQ6,DTCE_ICU_IRQ7,
    DTCE_ICU_IRQ8,DTCE_ICU_IRQ9,DTCE_ICU_IRQ10,DTCE_ICU_IRQ11,DTCE_ICU_IRQ12,DTCE_ICU_IRQ13,DTCE_ICU_IRQ14,DTCE_ICU_IRQ15,
    DTCE_SCI5_RXI5,DTCE_SCI5_TXI5,
    DTCE_SCI6_RXI6,DTCE_SCI6_TXI6,
    DTCE_RSCI8_RXI,DTCE_RSCI8_TXI,
    DTCE_RSCI9_RXI,DTCE_RSCI9_TXI,
    DTCE_RSCI11_RXI,DTCE_RSCI11_TXI,
    DTCE_SCI12_RXI12,DTCE_SCI12_TXI12,
    DTCE_RI3C0_RXI,DTCE_RI3C0_TXI,
    DTCE_DMAC_DMAC0I,DTCE_DMAC_DMAC1I,DTCE_DMAC_DMAC2I,DTCE_DMAC_DMAC3I,
    DTCE_S12AD_S12ADI,DTCE_S12AD_S12GBADI,DTCE_S12AD_S12GCADI,
    DTCE_S12AD1_S12ADI1,DTCE_S12AD1_S12GBADI1,DTCE_S12AD1_S12GCADI1,
    DTCE_S12AD2_S12ADI2,DTCE_S12AD2_S12GBADI2,DTCE_S12AD2_S12GCADI2,
    DTCE_CANFD_RFDREQ0,DTCE_CANFD_RFDREQ1,
    DTCE_CANFD0_CFDREQ0,
    DTCE_TMR0_CMIA0,DTCE_TMR0_CMIB0,
    DTCE_TMR1_CMIA1,DTCE_TMR1_CMIB1,
    DTCE_TMR2_CMIA2,DTCE_TMR2_CMIB2,
    DTCE_TMR3_CMIA3,DTCE_TMR3_CMIB3,
    DTCE_TMR4_CMIA4,DTCE_TMR4_CMIB4,
    DTCE_TMR5_CMIA5,DTCE_TMR5_CMIB5,
    DTCE_TMR6_CMIA6,DTCE_TMR6_CMIB6,
    DTCE_TMR7_CMIA7,DTCE_TMR7_CMIB7,
    DTCE_ELC_ELSR18I,DTCE_ELC_ELSR19I,
    DTCE_TSIP_RD,DTCE_TSIP_WR,
    DTCE_CMPC0_CMPC0,
    DTCE_CMPC1_CMPC1,
    DTCE_CMPC2_CMPC2,
    DTCE_CMPC3_CMPC3,
    DTCE_CMPC4_CMPC4,
    DTCE_CMPC5_CMPC5,
    DTCE_CMTW0_CMWI0,DTCE_CMTW0_IC0I0,DTCE_CMTW0_IC1I0,DTCE_CMTW0_OC0I0,DTCE_CMTW0_OC1I0,
    DTCE_CMTW1_CMWI1,DTCE_CMTW1_IC0I1,DTCE_CMTW1_IC1I1,DTCE_CMTW1_OC0I1,DTCE_CMTW1_OC1I1,
    DTCE_RSCI9_AED,
    DTCE_PERIA_INTA208,DTCE_PERIA_INTA209,DTCE_PERIA_INTA210,DTCE_PERIA_INTA211,DTCE_PERIA_INTA212,DTCE_PERIA_INTA213,
    DTCE_PERIA_INTA214,DTCE_PERIA_INTA215,DTCE_PERIA_INTA216,DTCE_PERIA_INTA217,DTCE_PERIA_INTA218,DTCE_PERIA_INTA219,
    DTCE_PERIA_INTA220,DTCE_PERIA_INTA221,DTCE_PERIA_INTA222,DTCE_PERIA_INTA223,DTCE_PERIA_INTA224,DTCE_PERIA_INTA225,
    DTCE_PERIA_INTA226,DTCE_PERIA_INTA227,DTCE_PERIA_INTA228,DTCE_PERIA_INTA229,DTCE_PERIA_INTA230,DTCE_PERIA_INTA231,
    DTCE_PERIA_INTA232,DTCE_PERIA_INTA233,DTCE_PERIA_INTA234,DTCE_PERIA_INTA235,DTCE_PERIA_INTA236,DTCE_PERIA_INTA237,
    DTCE_PERIA_INTA238,DTCE_PERIA_INTA239,DTCE_PERIA_INTA240,DTCE_PERIA_INTA241,DTCE_PERIA_INTA242,DTCE_PERIA_INTA243,
    DTCE_PERIA_INTA244,DTCE_PERIA_INTA245,DTCE_PERIA_INTA246,DTCE_PERIA_INTA247,DTCE_PERIA_INTA248,DTCE_PERIA_INTA249,
    DTCE_PERIA_INTA250,DTCE_PERIA_INTA251,DTCE_PERIA_INTA252,DTCE_PERIA_INTA253,DTCE_PERIA_INTA254,DTCE_PERIA_INTA255
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


#endif /* defined(BSP_MCU_RX26T) */

/* End of File */

