/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_nfc_ptx_common.h
 * Description  : Common definition for PTX.
 *********************************************************************************************************************/

#ifndef R_NFC_PTX_COMMON_H
#define R_NFC_PTX_COMMON_H

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#include "r_sci_rx_if.h"
#include "r_sci_rx_pinset.h"
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL)
#include "r_sci_rl_if.h"
#endif
#include "r_byteq_if.h"
#include "r_gpio_rx_if.h"
#include "r_cmt_rx_if.h"
#include "r_irq_rx_if.h"
#include "r_sci_rx_if.h"
#include "r_nfc_ptx_if.h"


/**********************************************************************************************************************
 Local Typedef definitions
 *********************************************************************************************************************/
/* SCI port configuration */
typedef struct
{
    sci_ch_t    ch;           /**< SCI channel */
    void (*func)(void);    /**< Function name of SCI Port configuration */
    uint16_t    tx_size;      /**< TX buffer size */
    uint16_t    rx_size;      /**< RX buffer size */
} st_sci_conf_t;

 /* SCI table information */
typedef struct
{
    sci_hdl_t           sci_hdl;            /**< Handle for the SCI port. */
    sci_cfg_t           sci_config;         /**< Configuration for the SCI port. */
    volatile uint8_t    tx_end_flag;       /**< Flag indicating if the transmission has ended. */
} st_sci_tbl_t;

/* Pin configuration */
typedef struct
{
    gpio_port_pin_t pin;  /**< GPIO pin used for SPI SS functionality. */
    gpio_level_t    level; /**< GPIO level used for SPI SS functionality. */
    gpio_dir_t      dir;
} st_gpio_conf_t;

/* External interrupt configuration */
typedef struct
{
    gpio_port_pin_t pin;  /**< GPIO pin used for external interrupt. */
    irq_number_t    irq_num;    /**< IRQ number associated with the pin. */
    irq_trigger_t   trigger; /**< Trigger type for the external interrupt. */
    uint8_t         priority;      /**< Priority level for the external interrupt. */
    irq_handle_t    *handle; /**< Handle for the external interrupt. */
} st_irq_conf_t;


/* Timer configuration */
typedef struct
{
    uint32_t              channel; /**< CMT channel used for the timer. */
    const cmt_priority_t  priority;       /**< Timer priority level. */
} st_timer_cfg_t;



/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

#if !defined(NFC_CFG_SCI_CHANNEL)
	#error "Error! Need to define NFC_CFG_SCI_CHANNEL in r_nfc_ptx_rx_config.h"
#endif

#if (NFC_CFG_SCI_MODE == 0)
	#define PTX_INTF_SPI
#else
    #error "Other communication intefaces are not supported in this version"
#endif

#if SCI_CFG_TEI_INCLUDED != 1
#error "Error! Need to set SCI_CFG_TEI_INCLUDED is '1' in r_sci_rx_config.h"
#endif

#if (NFC_CFG_POLL_TYPE_A == 0) && (NFC_CFG_POLL_TYPE_B == 0) && (NFC_CFG_POLL_TYPE_F == 0) && (NFC_CFG_POLL_TYPE_A == 0)
    #error "Error! At least one NFC poll type must be enabled
#endif

/* GPIO pin macro */
#define NFC_SET_GPIO_PREPROC(x, y)	GPIO_PORT_ ## x ## _PIN_ ## y

/* GPIO pin number */
#define NFC_SET_GPIO(x, y)          NFC_SET_GPIO_PREPROC(x, y)

/* IRQ number macro */
#define NFC_SET_IRQ_NUM_PREPROC(x)  IRQ_NUM_ ## x

/* IRQ number */
#define NFC_SET_IRQ_NUM(x)	        NFC_SET_IRQ_NUM_PREPROC(x)

/* Configuration */

/* GPIO external interrupt pin macro */
#define NFC_EXT_IRQ_PIN			    NFC_SET_GPIO(NFC_CFG_EXT_IRQ_PORT, NFC_CFG_EXT_IRQ_PIN)

/* NSS pin macro */
#define NFC_SCI_SPI_SS_PIN			NFC_SET_GPIO(NFC_CFG_SCI_SSPI_SS_PORT, NFC_CFG_SCI_SSPI_SS_PIN)


/* IRQ source number according to IRQ pin */
#define NFC_IRQ_NUM	                NFC_SET_IRQ_NUM(NFC_CFG_IRQ_NUM)

/* IRQ enable bit according to IRQ pin */
#if defined(BSP_MCU_RX261)
#define NFC_IER_REG_NUM				8
#if (NFC_CFG_IRQ_NUM == 5)
#define NFC_IRQ_ENABLE_BIT	    	ICU.IER[NFC_IER_REG_NUM].BIT.IEN5
#elif (NFC_CFG_IRQ_NUM == 6)
#define NFC_IRQ_ENABLE_BIT	    	ICU.IER[NFC_IER_REG_NUM].BIT.IEN6
#endif
#endif

/* CMT interrupt priority level */
#define NFC_CMT_IPR_LEVEL			CMT_RX_CFG_IPR

/* Get SCI port configuration */
static st_sci_conf_t *get_port_config(void);

/* Open comm port */
sci_err_t port_open(sci_hdl_t *p_handle, void (* const p_cb)(void *p_args));

/* Send data via comm port */
sci_err_t port_send(sci_hdl_t const hdl, uint8_t *p_src, uint32_t length);

/* Receive data via comm port */
sci_err_t port_receive(sci_hdl_t const hdl, uint8_t *p_dst, uint32_t length);

/* Close comm port */
sci_err_t port_close(sci_hdl_t const hdl);

/* Open IRQ source */
irq_err_t ext_irq_open(irq_handle_t *phandle, void (* const p_callback)(void *p_args));

/* Enable external IRQ source */
irq_err_t ext_irq_enable(irq_handle_t hdl, bool enable);

/* Read IRQ interrupt status */
uint8_t read_interrupt_status(void);

/* Read input current of IRQ pin */
irq_err_t ext_irq_read_input(irq_handle_t hdl, uint32_t *state);

/* Close IRQ source */
irq_err_t ext_irq_close(irq_handle_t hdl);

/* Write current level to pin */
void write_pin(gpio_port_pin_t pin, gpio_level_t level);

/* Read current level from a pin */
gpio_err_t read_pin(gpio_port_pin_t pin);

/* Configure pin direction */
int set_pin_direct(gpio_port_pin_t *pin, gpio_dir_t dir);

/* Initialize timer */
bool timer_init(uint32_t freq, void(* p_callback)(void * pdata), uint32_t channel, cmt_priority_t priority);

/* Get timer status */
bool timer_status(uint32_t channel, bool *p_status);

/* Stop timer */
bool timer_stop(uint32_t channel);

#endif /* R_NFC_PTX_COMMON_H */


