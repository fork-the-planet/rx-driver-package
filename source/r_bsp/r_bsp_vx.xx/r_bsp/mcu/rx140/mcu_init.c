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
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : mcu_init.c
* Description  : Performs initialization common to all MCUs in this Group
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 30.06.2021 1.00     First Release
*         : 20.08.2021 1.01     Fixed the initial value of PDR register of PORTH for 80 and 64 pins.
*         : 11.02.2022 1.02     Fixed the initial value of PDR register of PORTH for 80 and 64 pins.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Get specifics on this MCU. */
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* RX MCUs come in different packages and different pin counts. For MCUs that do not have the maximum number of pins
 * for their group (e.g. MCU with 100 pins when maximum is 144 pins) these 'non-existent' pins that are not bonded out
 * need to be initialized to save power. The macros below define the non-existent pins on each port for smaller
 * pin count MCUs. If a pin is non-existent then its value is set to a 1. These values are then ORed into the
 * direction registers to set non-existent pins as outputs which can help save power.
 */
#if   BSP_PACKAGE_PINS == 80
    /* Refer User's Manual: Hardware Table 18.3. */
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0x07)
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x03)
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x3C)
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0x08)
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0x00)
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0xCF)
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0x80)
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0x00)
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0x03)
    #define BSP_PRV_PORTD_NE_PIN_MASK     (0xF8)
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0xC0)
    #define BSP_PRV_PORTG_NE_PIN_MASK     (0x7F)
    #define BSP_PRV_PORTH_NE_PIN_MASK     (0x30)
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x3D)
#elif BSP_PACKAGE_PINS == 64
    /* Refer User's Manual: Hardware Table 18.4. */
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0xD7)
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x0F)
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x3F)
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0x18)
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0x00)
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0xCF)
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0xA4)
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0x14)
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0x03)
    #define BSP_PRV_PORTD_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0xC0)
    #define BSP_PRV_PORTG_NE_PIN_MASK     (0x7F)
  #if BSP_CFG_MCU_PART_MEMORY_SIZE == 0x3
    #define BSP_PRV_PORTH_NE_PIN_MASK     (0xF0)
  #else
    #define BSP_PRV_PORTH_NE_PIN_MASK     (0x30)
  #endif
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x3F)
#elif BSP_PACKAGE_PINS == 48
    /* Refer User's Manual: Hardware Table 18.5. */
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x0F)
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x3F)
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0x1C)
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0x18)
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0xA5)
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0xD4)
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0x0F)
    #define BSP_PRV_PORTD_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0xE1)
    #define BSP_PRV_PORTG_NE_PIN_MASK     (0x7F)
    #define BSP_PRV_PORTH_NE_PIN_MASK     (0xF0)
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x3F)
#elif BSP_PACKAGE_PINS == 32
    /* Refer User's Manual: Hardware Table 18.6. */
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x3F)
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x3F)
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0x9C)
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0xF8)
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0xE5)
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0xFE)
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0x0F)
    #define BSP_PRV_PORTD_NE_PIN_MASK     (0xFF)
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0xE1)
    #define BSP_PRV_PORTG_NE_PIN_MASK     (0x7F)
    #define BSP_PRV_PORTH_NE_PIN_MASK     (0xFF)
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
* Description  : For MCUs that do not have the 'non-existent' pins for their group (e.g. MCU with 100 pins when
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

    /* Set PORTB.PDR */
    PORTB.PDR.BYTE |= BSP_PRV_PORTB_NE_PIN_MASK;

    /* Set PORTC.PDR */
    PORTC.PDR.BYTE |= BSP_PRV_PORTC_NE_PIN_MASK;

    /* Set PORTD.PDR */
    PORTD.PDR.BYTE |= BSP_PRV_PORTD_NE_PIN_MASK;

    /* Set PORTE.PDR */
    PORTE.PDR.BYTE |= BSP_PRV_PORTE_NE_PIN_MASK;

    /* Set PORTG.PDR */
    PORTG.PDR.BYTE |= BSP_PRV_PORTG_NE_PIN_MASK;

    /* Set PORTH.PDR */
    PORTH.PDR.BYTE |= BSP_PRV_PORTH_NE_PIN_MASK;

    /* Set PORTJ.PDR */
    PORTJ.PDR.BYTE |= BSP_PRV_PORTJ_NE_PIN_MASK;
} /* End of function bsp_non_existent_port_init() */

