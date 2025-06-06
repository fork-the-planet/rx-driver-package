/*
 * Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/***********************************************************************************************************************
 * File Name    : r_glcdc_rx66n.c
 * Version      : 1.61
 * Description  : Internal function program using in GLCDC API functions.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version   Description
 *         : 20.09.2019 1.30      First Release
 *         : 30.06.2020 1.40      Fixed preprocessor condition of BSP version.
 *         : 20.03.2025 1.61      Changed the disclaimer.
***********************************************************************************************************************/
/***********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "../../r_glcdc_private.h"

/* Check MCU Group */
#if defined(BSP_MCU_RX66N)
/***********************************************************************************************************************
 Imported global variables and functions (from other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/

/*******************************************************************************
 * Outline      : Interrupt setting.
 * Function Name: r_glcdc_interrupt_setting
 * Description  : Graphic 1 underflow, Graphic 2 underflow, Graphic 2 line detection
 *                interrupt setting.
 * Arguments    : p_interrupt -
 *                  Enable or disable of each interrupt.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_interrupt_setting(glcdc_interrupt_cfg_t const * const p_interrupt)
{
    bsp_int_ctrl_t grpal1;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
#endif

    grpal1.ipl = GLCDC_CFG_INTERRUPT_PRIORITY_LEVEL;

    if (true == p_interrupt->vpos_enable)
    {
        /* INTEN - Interrupt Request Enable Control Register
        b31:b3 Reserved   - These bits are read as 0. Writing to these bits have no effect.
        b2     GR2UFINTEN - GR2UF Interrupt Enable.
        b1     GR1UFINTEN - GR1UF Interrupt Enable.
        b0     VPOSINTEN  - VPOS Interrupt Enable. - Enable VPOS interrupt request. */
        GLCDC.INTEN.BIT.VPOSINTEN = 1;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b8 EN8 - Interrupt Request Enable 8 - Interrupt request is enabled. */
        EN(GLCDC,VPOS) = 1;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

    }
    else
    {
        /* INTEN - Interrupt Request Enable Control Register
        b0 VPOSINTEN  - VPOS Interrupt Enable. - Disable VPOS interrupt request. */
        GLCDC.INTEN.BIT.VPOSINTEN = 0;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif        

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b8 EN8 - Interrupt Request Enable 8 - Interrupt request is disabled. */
        EN(GLCDC,VPOS) = 0;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

        /* GRPAL1 - Group AL1 Interrupt Request Register
        b8 IS8 - Interrupt Status Flag 8. */

        /* WAIT_LOOP */
        while (0 != IS(GLCDC,VPOS))
        {
            R_BSP_NOP();
        }
    }

    if (true == p_interrupt->gr1uf_enable)
    {
        /* INTEN - Interrupt Request Enable Control Register
        b1 GR1UFINTEN - GR1UF Interrupt enable. */
        GLCDC.INTEN.BIT.GR1UFINTEN = 1;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif    

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b9 EN9 - Interrupt Request Enable 9 - Interrupt request is enabled. */
        EN(GLCDC,GR1UF) = 1;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif
    }
    else
    {
        /* INTEN - Interrupt Request Enable Control Register
        b1 GR1UFINTEN - GR1UF Interrupt disable. */
        GLCDC.INTEN.BIT.GR1UFINTEN = 0;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif  

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b9 EN9 - Interrupt Request Enable 9 - Interrupt request is disabled. */
        EN(GLCDC,GR1UF) = 0;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

        /* GRPAL1 - Group AL1 Interrupt Request Register
        b9 IS9 - Interrupt Status Flag 9. */

        /* WAIT_LOOP */
        while (0 != IS(GLCDC,GR1UF))
        {
            R_BSP_NOP();
        }
    }

    if (true == p_interrupt->gr2uf_enable)
    {
        /* INTEN - Interrupt Request Enable Control Register
        b2 GR2UFINTEN - GR2UF Interrupt enable. */
        GLCDC.INTEN.BIT.GR2UFINTEN = 1;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b10 EN10 - Interrupt Request Enable 10 - Interrupt request is enabled. */
        EN(GLCDC,GR2UF) = 1;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif
    }
    else
    {
        /* INTEN - Interrupt Request Enable Control Register
        b2 GR2UFINTEN - GR2UF Interrupt disable. */
        GLCDC.INTEN.BIT.GR2UFINTEN = 0;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b10 EN10 - Interrupt Request Enable 10 - Interrupt request is disabled. */
        EN(GLCDC,GR2UF) = 0;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
        R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

        /* GRPAL1 - Group AL1 Interrupt Request Register
        b10 IS10 - Interrupt Status Flag 10. */
        
        /* WAIT_LOOP */
        while (0 != IS(GLCDC,GR2UF))
        {
            R_BSP_NOP();
        }
    }

    /* Set GROUPAL1 interrupt request to enable, if GLCDC interrupt parameter is enabled
       Set GROUPAL1 interrupt request to disable, if GLCDC interrupt parameter is disabled */
    if ((true == p_interrupt->vpos_enable) || (true == p_interrupt->gr1uf_enable) || (true == p_interrupt->gr2uf_enable))
    {
        R_BSP_InterruptControl(BSP_INT_SRC_AL1_GLCDC_VPOS, BSP_INT_CMD_GROUP_INTERRUPT_ENABLE, (void *) &grpal1.ipl);
    }
    else
    {
        R_BSP_InterruptControl(BSP_INT_SRC_AL1_GLCDC_VPOS, BSP_INT_CMD_GROUP_INTERRUPT_DISABLE, NULL);
    }

} /* End of function r_glcdc_interrupt_setting() */
#endif  /* defined(BSP_MCU_RX66N) */
/* End of File */
