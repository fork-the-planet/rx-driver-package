/***********************************************************************************************************************
* Copyright (c) 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_elc_rx260.c
 * Version      : 4.01
 * Description  : Functions for using Event Link Controller module
 ************************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           31.07.2024 1.0     Initial Release
 *           20.03.2025 4.01    Changed the disclaimer in program sources.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "platform.h"

#if defined (BSP_MCU_RX260) /* This pre-processer need for complie when module added by FIT-Plugin */
#include "r_elc_rx_private.h"

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
#define ELC_ELSR0_ADDRESS_OFFSET        ((uint8_t)0x01)

/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/
static void elc_set_port_link_module (elc_link_module_t *p_elc_module);
static void elc_set_port_event_signal (elc_event_signal_t *p_elc_event_signal);
static void elc_set_timer_operation (elc_link_module_t *p_elc_module);
static void elc_set_interrupt_operation (elc_link_module_t * const p_elc_module);

static elc_icu_t elc_icu1;
static elc_icu_t elc_icu2;
static elc_icu_t elc_icu_lpt;

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
extern elc_interrupt_set_t g_elc_callback_icu1;
extern elc_interrupt_set_t g_elc_callback_icu2;
extern elc_interrupt_set_t g_elc_callback_icu_lpt;

/***********************************************************************************************************************
 * Function Name: elc_module_control
 * Description  : Release from the module-stop state.
 * Arguments    : select
 *                  - The set value of the module stop state of ELC.
 * Return Value : none
 ***********************************************************************************************************************/
void elc_module_control (elc_module_stop_t select)
{
#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
#endif

    /* Enable PRCR access */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
#endif

    MSTP_ELC = select;

#if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
#endif

    /* Disable PRCR access */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
}
/***********************************************************************************************************************
 End of function elc_module_control
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_open_init_register
 * Description  : Initialize ELC registers.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void elc_open_init_register (void)
{
    ELC.ELCR.BYTE   = 0x7F; /* Event Link Control Register initialize */
    ELC.ELSR7.BYTE  = 0x00; /* Event Link Setting Register 7 initialize */
    ELC.ELSR8.BYTE  = 0x00; /* Event Link Setting Register 8 initialize */
    ELC.ELSR10.BYTE = 0x00; /* Event Link Setting Register 10 initialize */
    ELC.ELSR12.BYTE = 0x00; /* Event Link Setting Register 12 initialize */
    ELC.ELSR14.BYTE = 0x00; /* Event Link Setting Register 14 initialize */
    ELC.ELSR15.BYTE = 0x00; /* Event Link Setting Register 15 initialize */
    ELC.ELSR16.BYTE = 0x00; /* Event Link Setting Register 16 initialize */
    ELC.ELSR18.BYTE = 0x00; /* Event Link Setting Register 18 initialize */
    ELC.ELSR19.BYTE = 0x00; /* Event Link Setting Register 19 initialize */
    ELC.ELSR20.BYTE = 0x00; /* Event Link Setting Register 20 initialize */
    ELC.ELSR21.BYTE = 0x00; /* Event Link Setting Register 21 initialize */
    ELC.ELSR22.BYTE = 0x00; /* Event Link Setting Register 22 initialize */
    ELC.ELSR23.BYTE = 0x00; /* Event Link Setting Register 23 initialize */
    ELC.ELSR24.BYTE = 0x00; /* Event Link Setting Register 24 initialize */
    ELC.ELSR25.BYTE = 0x00; /* Event Link Setting Register 25 initialize */
    ELC.ELSR26.BYTE = 0x00; /* Event Link Setting Register 26 initialize */
    ELC.ELSR27.BYTE = 0x00; /* Event Link Setting Register 27 initialize */
    ELC.ELSR28.BYTE = 0x00; /* Event Link Setting Register 28 initialize */
    ELC.ELSR48.BYTE = 0x00; /* Event Link Setting Register 48 initialize */
    ELC.ELSR49.BYTE = 0x00; /* Event Link Setting Register 49 initialize */
    ELC.ELSR50.BYTE = 0x00; /* Event Link Setting Register 50 initialize */
    ELC.ELSR51.BYTE = 0x00; /* Event Link Setting Register 51 initialize */
    ELC.ELSR52.BYTE = 0x00; /* Event Link Setting Register 52 initialize */
    ELC.ELSR53.BYTE = 0x00; /* Event Link Setting Register 53 initialize */
    ELC.ELSR54.BYTE = 0x00; /* Event Link Setting Register 54 initialize */
    ELC.ELSR55.BYTE = 0x00; /* Event Link Setting Register 55 initialize */
    ELC.ELSR56.BYTE = 0x00; /* Event Link Setting Register 56 initialize */
    ELC.ELOPC.BYTE  = 0xFF; /* Event Link Option Setting Register C initialize */
    ELC.ELOPD.BYTE  = 0xFF; /* Event Link Option Setting Register D initialize */
    ELC.PGR1.BYTE   = 0x00; /* Port Group Setting Register 1 initialize */
    ELC.PGR2.BYTE   = 0x00; /* Port Group Setting Register 2 initialize */
    ELC.PGC1.BYTE   = 0x88; /* Port Group Control Register 1 initialize */
    ELC.PGC2.BYTE   = 0x88; /* Port Group Control Register 2 initialize */
    ELC.PDBF1.BYTE  = 0x00; /* Port Buffer Register 1 initialize */
    ELC.PDBF2.BYTE  = 0x00; /* Port Buffer Register 2 initialize */
    ELC.PEL0.BYTE   = 0x80; /* Event Link Port Setting Register 0 initialize */
    ELC.PEL1.BYTE   = 0x80; /* Event Link Port Setting Register 1 initialize */
    ELC.PEL2.BYTE   = 0x80; /* Event Link Port Setting Register 2 initialize */
    ELC.PEL3.BYTE   = 0x80; /* Event Link Port Setting Register 3 initialize */
    ELC.ELSEGR.BYTE = 0x3E; /* Event Link Software Event Generation Register initialize */

    R_BSP_InterruptRequestDisable(VECT(ELC,ELSR18I)); /* Interrupt Request Enable Register initialize */
    IR(ELC,ELSR18I)= 0;     /* Interrupt Request Register initialize */
    ICU.IPR[VECT_ELC_ELSR18I].BYTE = 0;  /* Interrupt Source Priority Register initialize */

    R_BSP_InterruptRequestDisable(VECT(ELC,ELSR19I)); /* Interrupt Request Enable Register initialize */
    IR(ELC,ELSR19I) = 0;    /* Interrupt Request Register initialize */
    ICU.IPR[VECT_ELC_ELSR19I].BYTE = 0;   /* Interrupt Source Priority Register initialize */

    R_BSP_InterruptRequestDisable(VECT(ELC,ELSR8I));  /* Interrupt Request Enable Register initialize */
    IR(ELC,ELSR8I)= 0;      /* Interrupt Request Register initialize */
    ICU.IPR[VECT_ELC_ELSR8I].BYTE = 0;   /* Interrupt Source Priority Register initialize */

}
/***********************************************************************************************************************
 End of function elc_open_init_register
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_set_eventlink_setting
 * Description  : Set an event link.
 * Arguments    : p_elc_event_signal
 *                  - Struct index of information about an event input.
 *              : p_elc_module
 *                  - Struct index of information about an event generation.
 * Return Value : none
 ***********************************************************************************************************************/
void elc_set_eventlink_setting (elc_event_signal_t * const p_elc_event_signal, elc_link_module_t * const p_elc_module)
{
    volatile uint8_t R_BSP_EVENACCESS_SFR *pbase_register_address;
    volatile uint8_t R_BSP_EVENACCESS_SFR *poffset_address;
    volatile uint8_t R_BSP_EVENACCESS_SFR *pset_address;

    elc_set_port_link_module(p_elc_module);
    elc_set_port_event_signal(p_elc_event_signal);

    pbase_register_address = (volatile uint8_t R_BSP_EVENACCESS_SFR *) &ELC.ELCR;
    poffset_address = (volatile uint8_t R_BSP_EVENACCESS_SFR *) ((p_elc_module->link_module) + ELC_ELSR0_ADDRESS_OFFSET);
    pset_address = (volatile uint8_t R_BSP_EVENACCESS_SFR *) ((uint32_t) pbase_register_address + (uint32_t) poffset_address);
    *pset_address = (p_elc_event_signal->event_signal);

    elc_set_timer_operation(p_elc_module);
    elc_set_interrupt_operation(p_elc_module);

}
/***********************************************************************************************************************
 End of function elc_set_eventlink_setting
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_set_port_link_module
 * Description  : The setting when the module with which an event is connected is a port.
 * Arguments    : p_elc_module
 *                - Struct index of information about an event link connection module.
 * Return Value : none
 ***********************************************************************************************************************/
static void elc_set_port_link_module (elc_link_module_t * const p_elc_module)
{

    switch (p_elc_module->link_module)
    {
        case ELC_OUT_PGR1 :
            ELC.PGC1.BIT.PGCO = p_elc_module->link_module_output_port_level;
            ELC.PGR1.BYTE = p_elc_module->link_module_port_group_bit;
        break;
        case ELC_OUT_PGR2 :
            ELC.PGC2.BIT.PGCO = p_elc_module->link_module_output_port_level;
            ELC.PGR2.BYTE = p_elc_module->link_module_port_group_bit;
        break;
        case ELC_IN_PGR1 :
            ELC.PGC1.BIT.PGCOVE = p_elc_module->link_module_port_buffer;
            ELC.PGR1.BYTE = p_elc_module->link_module_port_group_bit;
        break;
        case ELC_IN_PGR2 :
            ELC.PGC2.BIT.PGCOVE = p_elc_module->link_module_port_buffer;
            ELC.PGR2.BYTE = p_elc_module->link_module_port_group_bit;
        break;
        case ELC_PSP0 :
            ELC.PEL0.BIT.PSB = ((p_elc_module->link_module_single_port) & 0x07);
            ELC.PEL0.BIT.PSP = ((p_elc_module->link_module_single_port) >> 3);
            ELC.PEL0.BIT.PSM = p_elc_module->link_module_output_port_level;
        break;
        case ELC_PSP1 :
            ELC.PEL1.BIT.PSB = ((p_elc_module->link_module_single_port) & 0x07);
            ELC.PEL1.BIT.PSP = ((p_elc_module->link_module_single_port) >> 3);
            ELC.PEL1.BIT.PSM = p_elc_module->link_module_output_port_level;
        break;
        case ELC_PSP2 :
            ELC.PEL2.BIT.PSB = ((p_elc_module->link_module_single_port) & 0x07);
            ELC.PEL2.BIT.PSP = ((p_elc_module->link_module_single_port) >> 3);
            ELC.PEL2.BIT.PSM = p_elc_module->link_module_output_port_level;
        break;
        case ELC_PSP3 :
            ELC.PEL3.BIT.PSB = ((p_elc_module->link_module_single_port) & 0x07);
            ELC.PEL3.BIT.PSP = ((p_elc_module->link_module_single_port) >> 3);
            ELC.PEL3.BIT.PSM = p_elc_module->link_module_output_port_level;
        break;
        default :
        break;
    }
}
/***********************************************************************************************************************
 End of function elc_set_port_link_module
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_set_port_event_signal
 * Description  : The setting when event output source is a port.
 * Arguments    : p_elc_event_signal
 *                  - Struct index of information on event link source.
 * Return Value : none
 ***********************************************************************************************************************/
static void elc_set_port_event_signal (elc_event_signal_t * const p_elc_event_signal)
{

    switch (p_elc_event_signal->event_signal)
    {
        case ELC_PORT_PGR1 :
            ELC.PGC1.BIT.PGCI = p_elc_event_signal->event_signal_input_port_edge;
            ELC.PGR1.BYTE = p_elc_event_signal->event_signal_port_group_bit;
        break;
        case ELC_PORT_PGR2 :
            ELC.PGC2.BIT.PGCI = p_elc_event_signal->event_signal_input_port_edge;
            ELC.PGR2.BYTE = p_elc_event_signal->event_signal_port_group_bit;
        break;
        case ELC_PORT_PSP0 :
            ELC.PEL0.BIT.PSB = (p_elc_event_signal->event_signal_single_port & 0x07);
            ELC.PEL0.BIT.PSP = ((p_elc_event_signal->event_signal_single_port) >> 3);
            ELC.PEL0.BIT.PSM = p_elc_event_signal->event_signal_input_port_edge;
        break;
        case ELC_PORT_PSP1 :
            ELC.PEL1.BIT.PSB = (p_elc_event_signal->event_signal_single_port & 0x07);
            ELC.PEL1.BIT.PSP = ((p_elc_event_signal->event_signal_single_port) >> 3);
            ELC.PEL1.BIT.PSM = p_elc_event_signal->event_signal_input_port_edge;
        break;
        case ELC_PORT_PSP2 :
            ELC.PEL2.BIT.PSB = (p_elc_event_signal->event_signal_single_port & 0x07);
            ELC.PEL2.BIT.PSP = ((p_elc_event_signal->event_signal_single_port) >> 3);
            ELC.PEL2.BIT.PSM = p_elc_event_signal->event_signal_input_port_edge;
        break;
        case ELC_PORT_PSP3 :
            ELC.PEL3.BIT.PSB = (p_elc_event_signal->event_signal_single_port & 0x07);
            ELC.PEL3.BIT.PSP = ((p_elc_event_signal->event_signal_single_port) >> 3);
            ELC.PEL3.BIT.PSM = p_elc_event_signal->event_signal_input_port_edge;
        break;
        default :
        break;
    }
}
/***********************************************************************************************************************
 End of function elc_set_port_event_signal
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_set_timer_operation
 * Description  : The setting when the module with which an event is connected is a timer.
 * Arguments    : p_elc_module
 *                  - Struct index of information about an event link connection module.
 * Return Value : none
 ***********************************************************************************************************************/
static void elc_set_timer_operation (elc_link_module_t * const p_elc_module)
{

    switch (p_elc_module->link_module)
    {
        case ELC_CMT1 :
            ELC.ELOPC.BIT.CMT1MD = p_elc_module->link_module_timer_operation;
        break;

        case ELC_TMR0 :
            ELC.ELOPD.BIT.TMR0MD = p_elc_module->link_module_timer_operation;
        break;

        case ELC_TMR2 :
            ELC.ELOPD.BIT.TMR2MD = p_elc_module->link_module_timer_operation;
        break;

        default :
        break;
    }
}
/***********************************************************************************************************************
 End of function elc_set_timer_operation
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_set_interrupt_operation
 * Description  : The setting when the module with which an event is connected is a interrupt.
 * Arguments    : p_elc_module
 *                  - Struct index of information about an event link connection module.
 * Return Value : none
 ***********************************************************************************************************************/
static void elc_set_interrupt_operation (elc_link_module_t * const p_elc_module)
{

    switch (p_elc_module->link_module)
    {
        case ELC_ICU1:
            ICU.IPR[VECT_ELC_ELSR18I].BYTE = p_elc_module->link_module_interrupt_level;
            IR(ELC,ELSR18I)= 0;
            R_BSP_InterruptRequestEnable(VECT(ELC,ELSR18I));
        break;

        case ELC_ICU2:
            ICU.IPR[VECT_ELC_ELSR19I].BYTE = p_elc_module->link_module_interrupt_level;
            IR(ELC,ELSR19I) = 0;
            R_BSP_InterruptRequestEnable(VECT(ELC,ELSR19I));
        break;

        case ELC_ICU_LPT:
            ELC.ELOPC.BIT.LPTMD = 0;
            ICU.IPR[VECT_ELC_ELSR8I].BYTE = p_elc_module->link_module_interrupt_level;
            IR(ELC,ELSR8I)= 0;
            R_BSP_InterruptRequestEnable(VECT(ELC,ELSR8I));
        break;
        default :
        break;
    }
}
/***********************************************************************************************************************
 End of function elc_set_interrupt_operation
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_control_cmd_event_clear
 * Description  : Setting of an event link is cleared.
 * Arguments    : clear_select
 *                  - Choice of a release event link.
 * Return Value : none
 ***********************************************************************************************************************/
void elc_control_cmd_event_clear (const elc_module_t clear_select)
{
    volatile uint8_t R_BSP_EVENACCESS_SFR *pbase_register_address;
    volatile uint8_t R_BSP_EVENACCESS_SFR *poffset_address;
    static volatile uint8_t R_BSP_EVENACCESS_SFR *pset_address;

    switch (clear_select)
    {
        case ELC_ICU_LPT :
            ELC.ELOPC.BIT.LPTMD = 3;
            R_BSP_InterruptRequestDisable(VECT(ELC,ELSR8I));
            IR(ELC,ELSR8I) = 0;
            ICU.IPR[VECT_ELC_ELSR8I].BYTE = 0;
        break;
        case ELC_ICU1 :
            R_BSP_InterruptRequestDisable(VECT(ELC,ELSR18I));
            IR(ELC,ELSR18I) = 0;
            ICU.IPR[VECT_ELC_ELSR18I].BYTE = 0;
        break;
        case ELC_ICU2 :
            R_BSP_InterruptRequestDisable(VECT(ELC,ELSR19I));
            IR(ELC,ELSR19I) = 0;
            ICU.IPR[VECT_ELC_ELSR19I].BYTE = 0;
        break;
        default:
        break;
    }

    pbase_register_address = (volatile uint8_t R_BSP_EVENACCESS_SFR *) &ELC.ELCR;
    poffset_address = (volatile uint8_t R_BSP_EVENACCESS_SFR *) (clear_select + ELC_ELSR0_ADDRESS_OFFSET);
    pset_address = (volatile uint8_t R_BSP_EVENACCESS_SFR *) ((uint32_t) pbase_register_address + (uint32_t) poffset_address);
    *pset_address = 0x00;

}
/***********************************************************************************************************************
 End of function elc_control_cmd_event_clear
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_control_cmd_soft_trigger
 * Description  : Software event is generated.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void elc_control_cmd_soft_trigger (void)
{
    ELC.ELSEGR.BYTE = 0x7E;
    ELC.ELSEGR.BYTE = 0x7F;
    ELC.ELSEGR.BYTE = 0x3E;
}
/***********************************************************************************************************************
 End of function elc_control_cmd_soft_trigger
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_start_all_eventlink
 * Description  : This function starts all events link.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void elc_start_all_eventlink (void)
{
    ELC.ELCR.BIT.ELCON = 1;

}
/***********************************************************************************************************************
 End of function elc_start_all_eventlink
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_stop_all_eventlink
 * Description  : This function stops all events link.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void elc_stop_all_eventlink (void)
{
    ELC.ELCR.BIT.ELCON = 0;

}
/***********************************************************************************************************************
 End of function elc_stop_all_eventlink
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_control_cmd_write_pdbf
 * Description  : This function writes the value to the port buffer.
 * Arguments    : portbuffer_select
 *                   - Port buffer choice.
 *              : value
 *                   - The set value to the port buffer.
 * Return Value : none
 ***********************************************************************************************************************/
void elc_control_cmd_write_pdbf (const elc_portbuffer_t portbuffer_select, const uint8_t value)
{
    switch (portbuffer_select)
    {
        case ELC_PORT_GROUP1 :
            ELC.PDBF1.BYTE = value;
        break;
        case ELC_PORT_GROUP2 :
            ELC.PDBF2.BYTE = value;
        break;
        default :
        break;
    }
}
/***********************************************************************************************************************
 End of function elc_control_cmd_write_pdbf
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_control_cmd_read_pdbf
 * Description  : This function returns the specified port buffer value.
 * Arguments    : portbuffer_select
 *                   - Port buffer choice.
 * Return Value : Read value of the portbuffer.
 ***********************************************************************************************************************/
uint8_t elc_control_cmd_read_pdbf (const elc_portbuffer_t portbuffer_select)
{
    uint8_t read_value = 0;

    switch (portbuffer_select)
    {
        case ELC_PORT_GROUP1 :
            read_value = ELC.PDBF1.BYTE;
        break;
        case ELC_PORT_GROUP2 :
            read_value = ELC.PDBF2.BYTE;
        break;
        default :
        break;
    }

    return read_value;
}
/***********************************************************************************************************************
 End of function elc_control_cmd_read_pdbf
 ***********************************************************************************************************************/

#if (ELC_CFG_PARAM_CHECKING_ENABLE == 1)
/***********************************************************************************************************************
 * Function Name: elc_check_validate_module
 * Description  : Selected module is confirmed valid.
 * Arguments    : link_module
 *                  - Selected module.
 * Return Value : ELC_SUCCESS
 *                  - Selected module is valid.
 *              : ELC_ERR_INVALID_ARG
 *                  - Selected module is invalid.
 ***********************************************************************************************************************/
elc_err_t elc_check_validate_module (const elc_module_t link_module)
{
    elc_err_t err = ELC_SUCCESS;

    /* Check module */
    if ((link_module < ELC_MODULE_MIN)||(link_module > ELC_MODULE_MAX))
    {
        err = ELC_ERR_INVALID_ARG;
    }

    return err;
}
/***********************************************************************************************************************
 End of function elc_check_validate_module
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_set_err_check_um_note
 * Description  : Usage Notes are checked.
 * Arguments    : p_elc_event_signal
 *                  - Struct index of information about an event input.
 *              : p_elc_module
 *                  - Struct index of information about an event generation.
 * Return Value : ELC_SUCCESS
 *                  - A process is success.
 *              : ELC_ERR_INVALID_ARG
 *                  - A process is failure.
 ***********************************************************************************************************************/
elc_err_t elc_set_err_check_um_note (elc_event_signal_t * const p_elc_event_signal, elc_link_module_t * const p_elc_module)
{
    elc_err_t err = ELC_SUCCESS;


    /* ELSR8 */
    if (ELC_ICU_LPT == (p_elc_module->link_module))
    {
        switch (p_elc_event_signal->event_signal)
        {
            case ELC_LPT_CMP0 :
            break;
            default :
                err = ELC_ERR_INVALID_ARG;
            break;
        }
    }


    /* ELSR18,ELSR19 */
    if ((ELC_ICU1 == (p_elc_module->link_module)) || (ELC_ICU2 == (p_elc_module->link_module)))
    {
        switch (p_elc_event_signal->event_signal)
        {
            /* These 8 case are intentionally combined */
            case ELC_PORT_PGR1 :
            case ELC_PORT_PGR2 :
            case ELC_PORT_PSP0 :
            case ELC_PORT_PSP1 :
            case ELC_PORT_PSP2 :
            case ELC_PORT_PSP3 :
            case ELC_ELC_SEG :
            case ELC_DOC_DOPCF :
            break;
            default :
                err = ELC_ERR_INVALID_ARG;
            break;
        }
    }

    return err;
}
/***********************************************************************************************************************
 End of function elc_set_err_check_um_note
 ***********************************************************************************************************************/
#endif

/***********************************************************************************************************************
 * Function Name: elc_intelc_icu_lpt_isr
 * Description  : ELSR8I interrupt Processing.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT(elc_intelc_icu_lpt_isr, VECT_ELC_ELSR8I)
R_BSP_ATTRIB_STATIC_INTERRUPT void elc_intelc_icu_lpt_isr (void)
{
    if ((NULL != g_elc_callback_icu_lpt) &&  (FIT_NO_FUNC != g_elc_callback_icu_lpt))
    {
       elc_icu_lpt = ELC_EVT_ICU_LPT;
       g_elc_callback_icu_lpt(&elc_icu_lpt);
    }
}
/***********************************************************************************************************************
 End of function elc_intelc_icu_lpt_isr
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_intelc_icu1_isr
 * Description  : ELSR18I interrupt Processing.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT(elc_intelc_icu1_isr, VECT_ELC_ELSR18I)
R_BSP_ATTRIB_STATIC_INTERRUPT void elc_intelc_icu1_isr (void)
{
    if ((NULL != g_elc_callback_icu1) &&  (FIT_NO_FUNC != g_elc_callback_icu1))
    {
       elc_icu1 = ELC_EVT_ICU1;
       g_elc_callback_icu1(&elc_icu1);
    }
}
/***********************************************************************************************************************
 End of function elc_intelc_icu1_isr
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: elc_intelc_icu2_isr
 * Description  : ELSR19I interrupt Processing.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT(elc_intelc_icu2_isr, VECT_ELC_ELSR19I)
R_BSP_ATTRIB_STATIC_INTERRUPT void elc_intelc_icu2_isr (void)
{
    if ((NULL != g_elc_callback_icu2) &&  (FIT_NO_FUNC != g_elc_callback_icu2))
    {
       elc_icu2 = ELC_EVT_ICU2;
       g_elc_callback_icu2(&elc_icu2);
    }
}
/***********************************************************************************************************************
 End of function elc_intelc_icu2_isr
 ***********************************************************************************************************************/
#endif /* #if defined (BSP_MCU_RX260) */

/***********************************************************************************************************************
 * End of File
 ***********************************************************************************************************************/
