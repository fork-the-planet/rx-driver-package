/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : vecttbl.c
* Device(s)    : RX261
* Description  : Definition of the exception vector table, reset vector, and user boot options.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version   Description
*         : 31.05.2024 1.00      First Release
*         : 26.02.2025 1.01      Changed the disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* BSP configuration. */
#include "platform.h"

/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_DISABLE == 0

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
R_BSP_POR_FUNCTION(R_BSP_POWER_ON_RESET_FUNCTION);

/***********************************************************************************************************************
* The following array fills in the endian and option function select registers and the ID code protection bytes.
***********************************************************************************************************************/
#ifdef __BIG
    #define BSP_PRV_MDE_VALUE (0xfffffff8)    /* big */
#else
    #define BSP_PRV_MDE_VALUE (0xffffffff)    /* little */
#endif

#if defined(__ICCRX__)

#pragma public_equ = "__MDE", BSP_PRV_MDE_VALUE
#pragma public_equ = "__OFS1", BSP_CFG_OFS1_REG_VALUE
#pragma public_equ = "__OFS0", BSP_CFG_OFS0_REG_VALUE
#pragma public_equ = "__OSIS_1", BSP_CFG_ID_CODE_LONG_1
#pragma public_equ = "__OSIS_2", BSP_CFG_ID_CODE_LONG_2
#pragma public_equ = "__OSIS_3", BSP_CFG_ID_CODE_LONG_3
#pragma public_equ = "__OSIS_4", BSP_CFG_ID_CODE_LONG_4

#endif /* defined(__ICCRX__) */

/***********************************************************************************************************************
* The following array fills in the exception vector table.
***********************************************************************************************************************/
#if BSP_CFG_RTOS_USED == 4  /* Renesas RI600V4 & RI600PX */
    /* System configurator generates the ritble.src as interrupt & exception vector tables. */
#else /* BSP_CFG_RTOS_USED!=4 */

#if defined(__CCRX__) || defined(__GNUC__)
R_BSP_ATTRIB_SECTION_CHANGE_EXCEPTVECT void * const Except_Vectors[] =
{
    /* The Endian select register (MDE), Option function select register 1 (OFS1), and Option function select
       register 0 (OFS0) are located in User ROM. */
    (void *)BSP_PRV_MDE_VALUE,      /* 0xffffff80 - Endian */
    (void *)0xFFFFFFFF,             /* 0xffffff84 - Reserved */
    (void *)BSP_CFG_OFS1_REG_VALUE, /* 0xffffff88 - OFS1 register defined in r_bsp_config.h */
    (void *)BSP_CFG_OFS0_REG_VALUE, /* 0xffffff8c - OFS0 register defined in r_bsp_config.h */
    (void *)0xFFFFFFFF,             /* 0xffffff90 - Reserved */
    (void *)0xFFFFFFFF,             /* 0xffffff94 - Reserved */
    (void *)0xFFFFFFFF,             /* 0xffffff98 - Reserved */
    (void *)0xFFFFFFFF,             /* 0xffffff9c - Reserved */

    /* The memory are immediately below (0xffffffa0 through 0xffffffaf) is a special area that allows the on-chip 
       firmware to be protected. See the section "ID Code Protection" in the HW manual for details on how to enable 
       protection. Setting the four long words below to non-0xFF values will enable protection.  Do this only after 
       carefully review the HW manual */

    /* 0xffffffa0 through 0xffffffaf: ID Code Protection. The ID code is specified using macros in r_bsp_config.h. */
    (void *) BSP_CFG_ID_CODE_LONG_1,  /* 0xffffffa0 - Control code and ID code */
    (void *) BSP_CFG_ID_CODE_LONG_2,  /* 0xffffffa4 - ID code (cont.) */
    (void *) BSP_CFG_ID_CODE_LONG_3,  /* 0xffffffa8 - ID code (cont.) */
    (void *) BSP_CFG_ID_CODE_LONG_4,  /* 0xffffffac - ID code (cont.) */

    /* 0xffffffb0 through 0xffffffcf: Reserved area */
    (void *) 0xFFFFFFFF,  /* 0xffffffb0 - Reserved */
    (void *) 0xFFFFFFFF,  /* 0xffffffb4 - Reserved */
    (void *) 0xFFFFFFFF,  /* 0xffffffb8 - Reserved */
    (void *) 0xFFFFFFFF,  /* 0xffffffbc - Reserved */
    (void *) 0xFFFFFFFF,  /* 0xffffffc0 - Reserved */
    (void *) 0xFFFFFFFF,  /* 0xffffffc4 - Reserved */
    (void *) 0xFFFFFFFF,  /* 0xffffffc8 - Reserved */
    (void *) 0xFFFFFFFF,  /* 0xffffffcc - Reserved */

    /* Exception vector table */
    (void *) excep_supervisor_inst_isr,         /* 0xffffffd0  Exception(Supervisor Instruction) */
    (void *) excep_access_isr,                  /* 0xffffffd4  Exception(Access exception) */
    (void *) undefined_interrupt_source_isr,    /* 0xffffffd8  Reserved */
    (void *) excep_undefined_inst_isr,          /* 0xffffffdc  Exception(Undefined Instruction) */
    (void *) undefined_interrupt_source_isr,    /* 0xffffffe0  Reserved */
    (void *) excep_floating_point_isr,          /* 0xffffffe4  Exception(Floating Point) */
    (void *) undefined_interrupt_source_isr,    /* 0xffffffe8  Reserved */
    (void *) undefined_interrupt_source_isr,    /* 0xffffffec  Reserved */
    (void *) undefined_interrupt_source_isr,    /* 0xfffffff0  Reserved */
    (void *) undefined_interrupt_source_isr,    /* 0xfffffff4  Reserved */
    (void *) non_maskable_isr                   /* 0xfffffff8  (0x80 + 0x78) NMI */
};
R_BSP_ATTRIB_SECTION_CHANGE_END
#endif /* defined__CCRX__ || defined__GNUC__ */

/***********************************************************************************************************************
* The following array fills in the reset vector.
***********************************************************************************************************************/
#if defined(__CCRX__) || defined(__GNUC__)
R_BSP_ATTRIB_SECTION_CHANGE_RESETVECT void (* const Reset_Vector[])(void) =
{
    R_BSP_POWER_ON_RESET_FUNCTION                   /* 0xfffffffc  RESET */
};
R_BSP_ATTRIB_SECTION_CHANGE_END
#endif /* defined(__CCRX__), defined(__GNUC__) */

#endif/* BSP_CFG_RTOS_USED == 4 */

#endif /* BSP_CFG_STARTUP_DISABLE == 0 */

