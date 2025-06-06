/***********************************************************************************************************************
* Copyright (c) 2019 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 30.06.2019 1.00     First Release
*              : 15.03.2025 2.31     Updated disclaimer.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_vbatt_rx23w_private.h
* Description  : Functions for using Battery Backup Function on RX devices. 
*******************************************************************************/
#ifndef R_VBATT_RX23W_PRIVATE_H
#define R_VBATT_RX23W_PRIVATE_H

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
/* Access to peripherals and board defines. */
#include "platform.h"
#ifdef BSP_MCU_RX23W


/*******************************************************************************
Macro definitions
*******************************************************************************/
/*----------------------------------------------------------------------------*/
/*  Parameter check of Configuration Options                                  */
/*----------------------------------------------------------------------------*/
#if ((0 > VBATT_CFG_DETECT_LEVEL) || ( 1 < VBATT_CFG_DETECT_LEVEL))
    #error "ERROR - VBATT_CFG_DETECT_LEVEL - Parameter error in configures file."
#endif

/*----------------------------------------------------------------------------*/
/*   Define                                                                   */
/*----------------------------------------------------------------------------*/
/* lvd0 of ofs1 setting judgment */
#define VBATT_OFS1_ADDRESS              ((uint32_t *)(0xFFFFFF88))  /* ofs1 address                 */
#define VBATT_OFS1_LVD0_BIT_MASK        ((uint32_t)(0x00000007))    /* mask for lvd0 bit of ofs1    */
#define VBATT_OFS1_LVD0_2_51_V_ENABLE   ((uint32_t)(0x00000002))    /* lvd0 enable, lvd0 level is 2.51 V */


/* information struct initial */
#define VBATT_RSV_INIT                  ((uint8_t)(0x00))           /* reserved bit                 */

/* Interrupt register setting */
#define VBATT_LVDBT_IEN_ENABLE          ((uint8_t)(0x01))           /* VBATT maskable interrupt is enable  */
#define VBATT_LVDBT_IEN_DISABLE         ((uint8_t)(0x00))           /* VBATT maskable interrupt is disable */

#define VBATT_NMIER_VBATEN_ENABLE       ((uint8_t)(0x01))           /* VBATT non-maskable interrupt is enable  */
#define VBATT_NMIER_VBATEN_DISABLE      ((uint8_t)(0x00))           /* VBATT non-maskable interrupt is disable */

/* VBATTCR register setting */
#define VBATT_VBATTCR_VBATTDIS_ENABLE   ((uint8_t)(0x00))           /* Battery Backup Function is enable  */
#define VBATT_VBATTCR_VBATTDIS_DISABLE  ((uint8_t)(0x01))           /* Battery Backup Function is disable */

#define VBATT_VBATTCR_VBTLVDEN_ENABLE   ((uint8_t)(0x01))           /* VBATT detection is enable    */
#define VBATT_VBATTCR_VBTLVDEN_DISABLE  ((uint8_t)(0x00))           /* VBATT detection is disable   */

#define VBATT_VBATTCR_VBTLVDLVL_2_20V   ((uint8_t)(0x02))           /* VBATT detection level is 2.20V */
#define VBATT_VBATTCR_VBTLVDLVL_2_00V   ((uint8_t)(0x03))           /* VBATT detection level is 2.00V */

/* VBTLVDICR register setting */
#define VBATT_VBTLVDICR_VBTLVDIE_ENABLE         ((uint8_t)(0x01))   /* VBATT interrupt is enable    */
#define VBATT_VBTLVDICR_VBTLVDIE_DISABLE        ((uint8_t)(0x00))   /* VBATT interrupt is disable   */

#define VBATT_VBTLVDICR_VBTLVDISEL_NON_MASKABLE ((uint8_t)(0x00))   /* VBATT interrupt is non-maskable interrupt */
#define VBATT_VBTLVDICR_VBTLVDISEL_MASKABLE     ((uint8_t)(0x01))   /* VBATT interrupt is maskable interrupt */



/*******************************************************************************
Private global variables and functions
*******************************************************************************/
/*----------------------------------------------------------------------------*/
/*   Function For Target MCU                                                  */
/*----------------------------------------------------------------------------*/
extern vbatt_return_t r_vbatt_check_parameter(void * p_arg, vbatt_api_mode_t called_api);
extern vbatt_return_t r_vbatt_open_set_target_mcu(void);
extern uint8_t r_vbatt_open_check_target_mcu(void);
extern void r_vbatt_open_f_clear_target_mcu(void);
extern vbatt_return_t r_vbatt_control_target_mcu(vbatt_ctrl_info_t * p_vbatt_ctrl_info);
extern vbatt_return_t r_vbatt_getstatus_target_mcu(vbatt_status_t * p_vbatt_status);


#endif /* BSP_MCU_RX23W */
#endif /* R_VBATT_RX23W_PRIVATE_H */

/* End of File */

