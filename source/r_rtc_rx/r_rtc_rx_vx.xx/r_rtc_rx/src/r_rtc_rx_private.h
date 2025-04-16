/***********************************************************************************************************************
* Copyright (c) 2013 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_rtc_rx_private.h
* Description  : Internal definitions for the Real Time Clock (RTC) peripheral driver on RX MCUs.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           09.09.2013 1.00    First release.
*           16.04.2014 2.00    Updated for new API.
*           03.09.2014 2.10    Added support for RX64M.
*           03.12.2014 2.20    Added support for RX113.
*           22.01.2015 2.30    Added support for RX71M.
*           20.07.2015 2.40    Added support for RX231.
*           01.03.2016 2.41    Added support for RX130.
*                              Added support for RX230.
*                              Added the option of RTC_CFG_DRIVE_CAPACITY_MD for sub-clock drive capacity.
*                              Added the definition of RTC_CAPTURE_EDGE_MASK to mask the capture register.
*                              Added the rtc_enable_ints function.
*           01.10.2016 2.50    Added support for RX65N
*                              The specification has been changed as follows:
*                              Added the RTC_INT_ENABLE definition as a setting of the RCR1 register.
*                              When the following conditions are met, a build error occurs to notify the user.
*                              - RX63N or RX631 is selected as the target MCU.
*                              - More than two sub-clock drive capacity values are selected.
*           31.07.2017 2.70    Added support for RX65N-2MB and RX130-512KB.
*                              Removed support for RX210 and RX63N/631.
*                              Added definition of RTC_DUMMY_READ for dummy read processing after register setting.
*                              Fixed the contents of RTC_DRIVE_CAPACITY definition (removed the shift process).
*                              Changed return type of rtc_bcd_to_dec function from uint8_t type to int type.
*           20.09.2017 2.71    Fixed issue that an incorrect time is read out when a carry of the RTC counter occurs
*                              while reading the current time.
*                              - Changed the value of RTC_INT_ENABLE definition from 0x05 to 0x07.
*                                By this way, the carry interrupt enable bit (RCR1.CIE) becomes enabled,
*                                it detects the carry during reading of the current time and reads again.
*           20.05.2019 2.75    Added support for GNUC and ICCRX.
*                              Fixed coding style.
*           20.06.2019 2.76    Added support for RX23W.
*           30.07.2019 2.77    Added support for RX72M.
*           22.11.2019 2.78    Added support for RX66N.
*                              Added support for RX72N.
*           30.06.2021 2.81    Added support for RX671.
*                              Added the following macro definitions.
*                              - RTC_CAPTURE_TAMPICR1_CH0EN
*                              - RTC_CAPTURE_TAMPICR1_CH1EN
*                              - RTC_CAPTURE_TAMPICR1_CH2EN
*           31.07.2021 2.82    Added support for RX140.
*           31.12.2021 2.83    Added support for RX660.
*           29.05.2023 2.90    Added support for RX23E-B.
*                              Updated according to GSCE Code Checker 6.50.
*           28.06.2024 3.00    Added support for RX260, RX261.
*                              Updated according to GSCE Code Checker 6.50.
*           15.03.2025 3.01    Updated disclaimer.
***********************************************************************************************************************/

#ifndef R_RTC_PRIVATE_H
#define R_RTC_PRIVATE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Need rtc_cb_func_t */
#include "r_rtc_rx_if.h"
#include "r_rtc_rx_config.h"


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define RTC_COUNTER_STOP        (0)
#define RTC_COUNTER_START       (1)

#define RTC_CAPTURE_ENABLE_MASK     (0x80)
#define RTC_CAPTURE_EVENT_MASK      (0x04)
#define RTC_CAPTURE_EDGE_MASK       (0x03)
#define RTC_CAPTURE_TAMPICR1_CH0EN  (0x01)
#define RTC_CAPTURE_TAMPICR1_CH1EN  (0x02)
#define RTC_CAPTURE_TAMPICR1_CH2EN  (0x04)

#define RTC_INT_ENABLE          (0x07)  /* Enable the AIE bit, the CIE bit and the PIE bit. */
                                        /* The carry interrupt (CIE bit) is used to read the current time. */
#define RTC_DUMMY_READ          (3)     /* Three times of dummy read */

#if (((BSP_MCU_RX261 == 1) || (BSP_MCU_RX260 == 1)) && (BSP_PACKAGE_PINS == 48))
    #error  "ERROR - Product with 48 Pins not support RTC Module."
#endif

#if !defined(BSP_MCU_RX140) || !defined(BSP_MCU_RX660) || !defined(BSP_MCU_RX260) || !defined(BSP_MCU_RX261)
#if !defined(RTC_CFG_DRIVE_CAPACITY_LO) && \
    !defined(RTC_CFG_DRIVE_CAPACITY_MD) && \
    !defined(RTC_CFG_DRIVE_CAPACITY_HI) && \
    !defined(RTC_CFG_DRIVE_CAPACITY_STD)
    #error "ERROR - A drive capacity #define must be uncommented in r_rtc_rx_config.h"
#endif

#if defined(RTC_CFG_DRIVE_CAPACITY_LO) && defined(RTC_CFG_DRIVE_CAPACITY_STD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_LO) && defined(RTC_CFG_DRIVE_CAPACITY_HI)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_LO) && defined(RTC_CFG_DRIVE_CAPACITY_MD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_HI) && defined(RTC_CFG_DRIVE_CAPACITY_STD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_HI) && defined(RTC_CFG_DRIVE_CAPACITY_MD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_MD) && defined(RTC_CFG_DRIVE_CAPACITY_STD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif

#ifdef BSP_MCU_RX11_ALL
    #if defined(RTC_CFG_DRIVE_CAPACITY_LO)
        #define RTC_DRIVE_CAPACITY      (2)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_MD)
        #define RTC_DRIVE_CAPACITY      (0)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_HI)
        #define RTC_DRIVE_CAPACITY      (1)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_STD)
        #define RTC_DRIVE_CAPACITY      (4)
    #endif
#else /* RX130, RX230, RX231, RX23W, RX23E-B, RX64M, RX65N, RX671, RX71M, RX72M, RX66N, RX72N */
    #if defined(RTC_CFG_DRIVE_CAPACITY_LO)
        #define RTC_DRIVE_CAPACITY      (1)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_STD)
        #define RTC_DRIVE_CAPACITY      (6)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_MD)
        #error "ERROR - RTC_CFG_DRIVE_CAPACITY_MD in r_rtc_rx_config.h is invalid selection for MCU."
    #elif defined(RTC_CFG_DRIVE_CAPACITY_HI)
        #error "ERROR - RTC_CFG_DRIVE_CAPACITY_HI in r_rtc_rx_config.h is invalid selection for MCU."
    #endif
#endif
#endif /* !definedBSP_MCU_RX140 || !definedBSP_MCU_RX660 || !definedBSP_MCU_RX260 || !definedBSP_MCU_RX261*/


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct            /* RTC Control Block */
{
    bool            initialized;
    rtc_cb_func_t   p_callback;
} rtc_ctrl_t;

typedef struct  /* maps to portion of st_rtc in iodefine.h */
{
    uint8_t     rtccr;
    uint8_t     pad;
} rtc_cap_ctrl_t;

typedef struct  /* maps to portion of st_rtc in iodefine.h */
{
    uint8_t     rseccp;
    uint8_t     pad_a;
    uint8_t     rmincp;
    uint8_t     pad_b;
    uint8_t     rhrcp;
    uint8_t     pad_c[3];
    uint8_t     rdaycp;
    uint8_t     pad_d;
    uint8_t     rmoncp;
    uint8_t     pad_e[5];
} rtc_cap_time_t;


/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

#if !defined(BSP_MCU_RX11_ALL) && !defined(BSP_MCU_RX130) && !defined(BSP_MCU_RX140) && !defined(BSP_MCU_RX23E_B)
extern volatile rtc_cap_ctrl_t  * g_pcap_ctrl;
extern volatile rtc_cap_time_t  * g_pcap_time;


/******************************************************************************
 * Function Name: rtc_config_capture
 * Description  : .
 * Argument     : p_capture
 * Return Value : .
 *****************************************************************************/
void            rtc_config_capture (rtc_capture_cfg_t * p_capture);

/******************************************************************************
 * Function Name: rtc_check_capture
 * Description  : .
 * Arguments    : pin
 *              : p_time
 * Return Value : .
 *****************************************************************************/
rtc_err_t       rtc_check_capture (rtc_pin_t pin, tm_t * p_time);

/******************************************************************************
 * Function Name: rtc_disable_capture
 * Description  : .
 * Argument     : pin
 * Return Value : .
 *****************************************************************************/
void            rtc_disable_capture (rtc_pin_t pin);
#endif

/******************************************************************************
 * Function Name: rtc_init
 * Description  : .
 * Arguments    : .
 * Return Value : .
 *****************************************************************************/
void     rtc_init (void);

/******************************************************************************
 * Function Name: rtc_set_output
 * Description  : .
 * Arguments    : output_freq
 * Return Value : .
 *****************************************************************************/
void     rtc_set_output (rtc_output_t output_freq);

/******************************************************************************
 * Function Name: rtc_set_periodic
 * Description  : .
 * Arguments    : freq
 *              : priority
 * Return Value : .
 *****************************************************************************/
void     rtc_set_periodic (rtc_periodic_t freq, uint8_t priority);

/******************************************************************************
 * Function Name: rtc_set_current_time
 * Description  : .
 * Arguments    : p_current
 * Return Value : .
 *****************************************************************************/
void     rtc_set_current_time (tm_t * p_current);

/******************************************************************************
 * Function Name: rtc_set_alarm_time
 * Description  : .
 * Arguments    : p_alarm
 * Return Value : .
 *****************************************************************************/
void     rtc_set_alarm_time (tm_t * p_alarm);

/******************************************************************************
 * Function Name: rtc_read_current
 * Description  : .
 * Arguments    : p_current
 * Return Value : .
 *****************************************************************************/
void     rtc_read_current (tm_t * p_current);

/******************************************************************************
 * Function Name: rtc_enable_alarms
 * Description  : .
 * Arguments    : p_alm_ctrl
 * Return Value : .
 *****************************************************************************/
void     rtc_enable_alarms (rtc_alarm_ctrl_t * p_alm_ctrl);

/******************************************************************************
 * Function Name: rtc_read_alarm
 * Description  : .
 * Arguments    : p_alarm
 * Return Value : .
 *****************************************************************************/
void     rtc_read_alarm (tm_t * p_alarm);

/******************************************************************************
 * Function Name: rtc_reset
 * Description  : .
 * Arguments    : .
 * Return Value : .
 *****************************************************************************/
void     rtc_reset (void);

/******************************************************************************
 * Function Name: rtc_counter_run
 * Description  : .
 * Arguments    : bit_value
 * Return Value : .
 *****************************************************************************/
void     rtc_counter_run (const uint8_t bit_value);

/******************************************************************************
 * Function Name: rtc_disable_ints
 * Description  : .
 * Arguments    : .
 * Return Value : .
 *****************************************************************************/
void     rtc_disable_ints (void);

/******************************************************************************
 * Function Name: rtc_enable_ints
 * Description  : .
 * Arguments    : .
 * Return Value : .
 *****************************************************************************/
void     rtc_enable_ints (void);

/******************************************************************************
 * Function Name: rtc_bcd_to_dec
 * Description  : .
 * Arguments    : to_convert
 * Return Value : .
 *****************************************************************************/
int  rtc_bcd_to_dec (uint8_t to_convert);

/******************************************************************************
 * Function Name: rtc_dec_to_bcd
 * Description  : .
 * Arguments    : to_convert
 * Return Value : .
 *****************************************************************************/
uint8_t  rtc_dec_to_bcd (uint8_t to_convert);


#endif /* R_RTC_PRIVATE_H */

