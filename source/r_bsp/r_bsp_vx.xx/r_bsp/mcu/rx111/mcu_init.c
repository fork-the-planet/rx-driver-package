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
* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : mcu_init.c
* Description  : Performs initialization common to all MCUs in this Group
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 07.05.2013 1.00     First Release
*         : 25.06.2013 1.10     Updated for v1.00 of HW manual. Ports H & J and 40-pin package were added.
*         : 15.05.2017 1.20     Deleted the following macro definition.
*                               - BSP_PRV_PORTH_NE_PIN_MASK
*                               Deleted PORTE.PDR.BYTE initialization processing.
*                               Changed port initialization of 64 pin.
*         : 28.02.2019 1.21     Fixed coding style.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Get specifics on this MCU. */
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* RX MCUs come in different packages and different pin counts. 'Non-existent' pins that are not bonded out
 * need to be initialized to save power. The macros below define the non-existent pins on each port. If a pin
 * is non-existent then its value is set to a 1. These values are then ORed into the
 * direction registers to set non-existent pins as outputs which can help save power.
 */
#if   BSP_PACKAGE_PINS == 64
    /* HW Manual Table 18.3 */
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0xD7)    /* Missing pins: P00 P01 P02 P04 P06 P07 */
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x0F)
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x3F)
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0xD8)
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0xA0)
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0xCF)
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0xA4)
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0x14)
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0x00)
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0x00)
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x3F)
#elif BSP_PACKAGE_PINS == 48
    /* HW Manual Table 18.4 */
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x0F)
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x3F)
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0xDF)
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0xB8)
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0xA5)
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0xD4)
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0x00)
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0x60)
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x3F)
#elif BSP_PACKAGE_PINS == 40
    /* HW Manual Table 18.5 */
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x0F)
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x3F)
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0xDB)
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0xB9)
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0xA5)
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0xF6)
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0xEF)
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0xE0)
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x3F)
#elif BSP_PACKAGE_PINS == 36
    /* HW Manual Table 18.6 */
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x0F)
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x7F)
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0xDF)
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0xF9)
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0xA7)
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0xF6)
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0xEF)
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0xE0)
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x3F)
#else
    #error "ERROR - This package is not defined in mcu_init.c"
#endif

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
* Function Name: bsp_non_existent_port_init
* Description  : For MCUs that do not have the maximum number of pins for their group (e.g. MCU with 100 pins when
*                maximum is 144 pins) these 'non-existent' pins that are not bonded out need to be initialized to save
*                power.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void bsp_non_existent_port_init (void)
{
    /* OR in missing pin masks from above. */

    /* Set PORT0.PDR */
    PORT0.PDR.BYTE |= BSP_PRV_PORT0_NE_PIN_MASK;

    /* Set PORT1.PDR */
    PORT1.PDR.BYTE |= BSP_PRV_PORT1_NE_PIN_MASK;

    /* Set PORT2.PDR */
    PORT2.PDR.BYTE |= BSP_PRV_PORT2_NE_PIN_MASK;

    /* Set PORT3.PDR */
    PORT3.PDR.BYTE |= BSP_PRV_PORT3_NE_PIN_MASK;

    /* Set PORT4.PDR */
    PORT4.PDR.BYTE |= BSP_PRV_PORT4_NE_PIN_MASK;

    /* Set PORT5.PDR */
    PORT5.PDR.BYTE |= BSP_PRV_PORT5_NE_PIN_MASK;

    /* Set PORTA.PDR */
    PORTA.PDR.BYTE |= BSP_PRV_PORTA_NE_PIN_MASK;

    /* Set PORTBB.PDR */
    PORTB.PDR.BYTE |= BSP_PRV_PORTB_NE_PIN_MASK;

    /* Set PORTC.PDR */
    PORTC.PDR.BYTE |= BSP_PRV_PORTC_NE_PIN_MASK;

    /* Set PORTE.PDR */
    PORTE.PDR.BYTE |= BSP_PRV_PORTE_NE_PIN_MASK;

    /* Set PORTJ.PDR */
    PORTJ.PDR.BYTE |= BSP_PRV_PORTJ_NE_PIN_MASK;
} /* End of function bsp_non_existent_port_init() */

