/***********************************************************************************************************************
* Copyright (c) 2013 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_sci_iic_rx_config.h
 * Description  : Configures the SCI IIC drivers
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 01.07.2013 1.00     First Release
 *         : 30.09.2013 1.10     Change symbol of return value and status
 *         : 01.07.2014 1.20     RX110 support added.
 *         : 22.09.2014 1.30     RX64M support added.
 *         : 01.12.2014 1.40     RX113 support added.
 *         : 15.12.2014 1.50     RX71M support added.
 *         : 27.02.2015 1.60     RX63N support added.
 *         : 29.05.2015 1.70     RX231 support added.
 *         : 31.10.2015 1.80     RX130, RX230, RX23T support added.
 *         : 04.03.2016 1.90     RX24T support added.Changed about the pin definisions.
 *         : 01.10.2016 2.00     RX65N support added.
 *         : 31.08.2017 2.20     Changed the default value of the following macro definition.
 *                                 - SCI_IIC_CFG_CH1_INCLUDED
 *                               RX24U,RX130-512 support added.
 *         : 29.01.2018 2.30     RX66T support added.
 *                               Change the comment for definition of priority level
 *         : 21.09.2018 2.40     RX72T support added.
 *         : 20.06.2019 2.42     RX23W support added.
 *         : 30.07.2019 2.43     RX72M support added.
 *         : 30.10.2019 2.44     RX13T support added.
 *         : 22.11.2019 2.45     RX66N, RX72N support added.
 *         : 10.03.2020 2.46     RX23E-A support added.
 *         : 30.06.2021 2.48     RX671 support added.
 *         : 31.07.2021 2.49     RX140 support added.
 *         : 31.12.2021 2.50     RX660 support added.
 *         : 15.06.2022 2.60     RX26T support added.
 *         : 29.05.2023 2.70     RX23E-B support added.
 *         : 28.06.2024 2.80     RX260, RX261 support added.
 *         : 15.03.2025 2.81     Updated disclaimer
 **********************************************************************************************************************/
/* Guards against multiple inclusion */
#ifndef SCI_IIC_CONFIG_H
    #define SCI_IIC_CONFIG_H
/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/
/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking */
/*            0 compiles out parameter checking */
    #define SCI_IIC_CFG_PARAM_CHECKING_ENABLE   (1)

/* SPECIFY CHANNELS TO INCLUDE SOFTWARE SUPPORT FOR 1=included, 0=not */
/* mcu supported channels */
/*  RX110    :    , ch1,    ,    ,    , ch5,    ,    ,    ,    ,    ,    ,ch12 */
/*  RX111    :    , ch1,    ,    ,    , ch5,    ,    ,    ,    ,    ,    ,ch12 */
/*  RX113    : ch0, ch1, ch2,    ,    , ch5, ch6,    , ch8, ch9,    ,    ,ch12 */
/*  RX130    : ch0, ch1,    ,    ,    , ch5, ch6,    , ch8, ch9,    ,    ,ch12 */
/*  RX13T    :    , ch1,    ,    ,    , ch5,    ,    ,    ,    ,    ,    ,ch12 */
/*  RX140    :    , ch1,    ,    ,    , ch5, ch6,    , ch8, ch9,    ,    ,ch12 */
/*  RX230    : ch0, ch1,    ,    ,    , ch5, ch6,    , ch8, ch9,    ,    ,ch12 */
/*  RX231    : ch0, ch1,    ,    ,    , ch5, ch6,    , ch8, ch9,    ,    ,ch12 */
/*  RX23E-A  :    , ch1,    ,    ,    , ch5, ch6,    ,    ,    ,    ,    ,ch12 */
/*  RX23E-B  : ch0, ch1,    ,    ,    , ch5, ch6,    , ch8, ch9,    ,    ,ch12 */
/*  RX23T    :    , ch1,    ,    ,    , ch5,    ,    ,    ,    ,    ,    ,     */
/*  RX23W    :    , ch1,    ,    ,    , ch5,    ,    , ch8,    ,    ,    ,ch12 */
/*  RX24T    :    , ch1,    ,    ,    , ch5, ch6,    ,    ,    ,    ,    ,     */
/*  RX24U    :    , ch1,    ,    ,    , ch5, ch6,    , ch8, ch9,    ,ch11,     */
/*  RX260    :    , ch1,    ,    ,    , ch5, ch6,    ,    ,    ,    ,    ,ch12 */
/*  RX261    :    , ch1,    ,    ,    , ch5, ch6,    ,    ,    ,    ,    ,ch12 */
/*  RX26T    :    , ch1,    ,    ,    , ch5, ch6,    ,    ,    ,    ,    ,ch12 */
/*  RX63N    : ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9,ch10,ch11,ch12 */
/*  RX64M    : ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7,    ,    ,    ,    ,ch12 */
/*  RX65N    : ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9,ch10,ch11,ch12 */
/*  RX660    : ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9,ch10,ch11,ch12 */
/*  RX66T    :    , ch1,    ,    ,    , ch5, ch6,    , ch8, ch9,    ,ch11,ch12 */
/*  RX66N    : ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9,ch10,ch11,ch12 */
/*  RX671    : ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9,ch10,ch11,ch12 */
/*  RX71M    : ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7,    ,    ,    ,    ,ch12 */
/*  RX72T    :    , ch1,    ,    ,    , ch5, ch6,    , ch8, ch9,    ,ch11,ch12 */
/*  RX72M    : ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9,ch10,ch11,ch12 */
/*  RX72N    : ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9,ch10,ch11,ch12 */
/* Please change the definition value of channel to be used to '1'. */
    #define SCI_IIC_CFG_CH0_INCLUDED    (0)
    #define SCI_IIC_CFG_CH1_INCLUDED    (0)
    #define SCI_IIC_CFG_CH2_INCLUDED    (0)
    #define SCI_IIC_CFG_CH3_INCLUDED    (0)
    #define SCI_IIC_CFG_CH4_INCLUDED    (0)
    #define SCI_IIC_CFG_CH5_INCLUDED    (0)
    #define SCI_IIC_CFG_CH6_INCLUDED    (0)
    #define SCI_IIC_CFG_CH7_INCLUDED    (0)
    #define SCI_IIC_CFG_CH8_INCLUDED    (0)
    #define SCI_IIC_CFG_CH9_INCLUDED    (0)
    #define SCI_IIC_CFG_CH10_INCLUDED   (0)
    #define SCI_IIC_CFG_CH11_INCLUDED   (0)
    #define SCI_IIC_CFG_CH12_INCLUDED   (0)

/* Set SCI IIC bps */
/* 1K = 1000, 100K= 100000, Max:384k = 384000 */
    #define SCI_IIC_CFG_CH0_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH1_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH2_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH3_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH4_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH5_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH6_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH7_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH8_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH9_BITRATE_BPS   (384000)
    #define SCI_IIC_CFG_CH10_BITRATE_BPS  (384000)
    #define SCI_IIC_CFG_CH11_BITRATE_BPS  (384000)
    #define SCI_IIC_CFG_CH12_BITRATE_BPS  (384000)

/*
 This definition set for TXI and so on for SCI interrupt priority level for SCI IIC.
 When you use device which has GROUP12 interrupt(e.g RX65N) then
 this definition set for GROUP12 and TXI and so on for SCI interrupt priority level.
 When you use RX63N or device whcih does not have GROUP12 interrupt
 then this definition set for TXI and so on for SCI interrupt priority level.
 */
/* 1 lowest, 15 highest */
    #define SCI_IIC_CFG_CH0_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH1_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH2_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH3_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH4_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH5_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH6_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH7_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH8_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH9_INT_PRIORITY  (2)
    #define SCI_IIC_CFG_CH10_INT_PRIORITY (2)
    #define SCI_IIC_CFG_CH11_INT_PRIORITY (2)
    #define SCI_IIC_CFG_CH12_INT_PRIORITY (2)

/* Digital noise filter (NFEN bit).
 0 =  Noise cancellation function for the SSCLn and SSDAn input signals is disabled.
 1 =  Noise cancellation function for the SSCLn and SSDAn input signals is enable.
 */
    #define SCI_IIC_CFG_CH0_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH1_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH2_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH3_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH4_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH5_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH6_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH7_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH8_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH9_DIGITAL_FILTER  (1)
    #define SCI_IIC_CFG_CH10_DIGITAL_FILTER (1)
    #define SCI_IIC_CFG_CH11_DIGITAL_FILTER (1)
    #define SCI_IIC_CFG_CH12_DIGITAL_FILTER (1)

/* Noise Filter Setting Register (NFCS bit).
 001  =  1       =   The clock signal divided by 1 is used with the noise filter.
 010  =  2       =   The clock signal divided by 2 is used with the noise filter.
 011  =  3       =   The clock signal divided by 4 is used with the noise filter.
 100  =  4       =   The clock signal divided by 8 is used with the noise filter.
 */
    #define SCI_IIC_CFG_CH0_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH1_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH2_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH3_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH4_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH5_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH6_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH7_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH8_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH9_FILTER_CLOCK    (1)
    #define SCI_IIC_CFG_CH10_FILTER_CLOCK   (1)
    #define SCI_IIC_CFG_CH11_FILTER_CLOCK   (1)
    #define SCI_IIC_CFG_CH12_FILTER_CLOCK   (1)

/* I2C Mode Register 1 (IICDL bit).
 00001  =  1       =   0 to 1 cycle
 00010  =  2       =   1 to 2 cycles
 00011  =  3       =   2 to 3 cycles
 00100  =  4       =   3 to 4 cycles
 00101  =  5       =   4 to 5 cycles
 |
 11110  = 30       =  29 to 30 cycles
 11111  = 31       =  30 to 31 cycles
 */
    #define SCI_IIC_CFG_CH0_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH1_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH2_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH3_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH4_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH5_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH6_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH7_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH8_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH9_SSDA_DELAY_SELECT   (18)
    #define SCI_IIC_CFG_CH10_SSDA_DELAY_SELECT  (18)
    #define SCI_IIC_CFG_CH11_SSDA_DELAY_SELECT  (18)
    #define SCI_IIC_CFG_CH12_SSDA_DELAY_SELECT  (18)

/* Define software bus busy check counter. */
    #define SCI_IIC_CFG_BUS_CHECK_COUNTER   (1000)

/* Setting to port.
 1 =  includes sci (simple iic)port setting processing
 0 =  compiles out sci (simple iic)port setting processing
 */
    #define SCI_IIC_CFG_PORT_SETTING_PROCESSING   (1)

#endif /* SCI_IIC_CONFIG_H */


