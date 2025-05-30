/***********************************************************************************************************************
* Copyright (c) 2020 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_s12ad_rx24u_if.h
* Description  : 12-bit A/D Converter driver interface file.
***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           10.06.2020 1.00    Initial Release.
*           20.03.2025 5.41    Changed the disclaimer in program sources.
***********************************************************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "platform.h"

#ifndef S12AD_PRV_RX24U_IF_H
#define S12AD_PRV_RX24U_IF_H

/******************************************************************************
Macro definitions
*******************************************************************************/

#define ADC_DDA_STATE_CNT_MIN       (2)
#define ADC_DDA_STATE_CNT_MAX       (15)

#define ADC_SST_CNT_MIN     (5)
#define ADC_SST_CNT_MAX     (255)
#define ADC_SST_CNT_DEFAULT (13)

/* for ADC_CMD_ENABLE_CHANS */

/* Bitwise OR these masks together for desired channels and sensors
   Used for all commands containing a "mask" or "flags" field */
#define ADC_MASK_CH0    (1<<0)
#define ADC_MASK_CH1    (1<<1)
#define ADC_MASK_CH2    (1<<2)
#define ADC_MASK_CH3    (1<<3)
#define ADC_MASK_CH4    (1<<4)
#define ADC_MASK_CH5    (1<<5)
#define ADC_MASK_CH6    (1<<6)
#define ADC_MASK_CH7    (1<<7)
#define ADC_MASK_CH8    (1<<8)
#define ADC_MASK_CH9    (1<<9)
#define ADC_MASK_CH10   (1<<10)
#define ADC_MASK_CH11   (1<<11)
#define ADC_MASK_VOLT   (1<<12)     /* internal reference voltage sensor */
#define ADC_MASK_CH16   (1<<16)

#define ADC_MASK_SENSORS            (ADC_MASK_VOLT)
#define ADC_MASK_GROUPB_OFF         (0)
#define ADC_MASK_GROUPC_OFF         (0)
#define ADC_MASK_ADD_OFF            (0)
#define ADC_MASK_SAMPLE_HOLD_OFF    (0)

#define ADC_SST_SH_CNT_MIN      (4)     /* minimum sample&hold states */
#define ADC_SST_SH_CNT_MAX      (255)   /* maximum sample&hold states */
#define ADC_SST_SH_CNT_DEFAULT  (26)    /* default sample&hold states */

#define ADC_PGA_CHANNEL_MAX   (3)  /* ch0-2 */

#define ADC_0_REG_ARRAY_MAX   (5)
#define ADC_1_REG_ARRAY_MAX   (5)
#define ADC_2_REG_ARRAY_MAX   (12)

/*****************************************************************************
Typedef definitions
******************************************************************************/

/***** ADC_OPEN() ARGUMENT DEFINITIONS *****/

typedef enum e_adc_mode
{
    ADC_MODE_SS_INT_REF_VOLT,       // single scan temperature sensor
    ADC_MODE_SS_ONE_CH,             // single scan one channel
    ADC_MODE_SS_MULTI_CH,           // 1 trigger source, scan multiple channels
    ADC_MODE_CONT_ONE_CH,           // continuous scan one channel
    ADC_MODE_CONT_MULTI_CH,         // continuous scan multiple channels
    ADC_MODE_SS_ONE_CH_DBLTRIG,     // on even triggers save to ADDBLDR & interrupt
    ADC_MODE_SS_MULTI_CH_GROUPED,   // 2 trigger sources, scan multiple channels
    ADC_MODE_SS_MULTI_CH_GROUPED_GROUPC, // 3 trigger sources, scan multiple channels
    ADC_MODE_SS_MULTI_CH_GROUPED_DBLTRIG_A,
    ADC_MODE_SS_MULTI_CH_GROUPED_DBLTRIG_A_GROUPC,
    ADC_MODE_MAX                    // This definition DO NOT USE for R_ADC_Open() argument.
} adc_mode_t;

typedef enum e_adc_align
{
    ADC_ALIGN_RIGHT = 0x0000,
    ADC_ALIGN_LEFT  = 0x8000
} adc_align_t;

typedef enum e_adc_add
{
    ADC_ADD_OFF = 0,                // addition is turned off for chans/sensors
    ADC_ADD_TWO_SAMPLES = 1,
    ADC_ADD_THREE_SAMPLES = 2,
    ADC_ADD_FOUR_SAMPLES = 3,
    ADC_ADD_SIXTEEN_SAMPLES = 5,
    ADC_ADD_AVG_2_SAMPLES = 0x81,   // average 2 samples
    ADC_ADD_AVG_4_SAMPLES = 0x83,   // average 4 samples
} adc_add_t;

typedef enum e_adc_clear
{
    ADC_CLEAR_AFTER_READ_OFF = 0x0000,
    ADC_CLEAR_AFTER_READ_ON  = 0x0020
} adc_clear_t;


typedef enum e_adc_trig             // trigger sources (set to TRSA bit or TRSB bit)
{
    ADC_TRIG_ASYNC_ADTRG                 = 0,   /* ext asynchronous trigger; not for Group modes
                                                   nor double trigger modes */
    ADC_TRIG_SYNC_TRG0AN                 = 1,   // MTU0 TRGA
    ADC_TRIG_SYNC_TRG1AN                 = 2,   // MTU1 TRGA
    ADC_TRIG_SYNC_TRG2AN                 = 3,   // MTU2 TRGA
    ADC_TRIG_SYNC_TRG3AN                 = 4,   // MTU3 TRGA
    ADC_TRIG_SYNC_TRG4AN_OR_UDF4N        = 5,   // MTU4 TRGA or MTU4 underflow(complementary PWM mode)
    ADC_TRIG_SYNC_TRG6AN                 = 6,   // MTU6 TRGA
    ADC_TRIG_SYNC_TRG7AN_OR_UDF7N        = 7,   // MTU7 TRGA or MTU7 underflow(complementary PWM mode)
    ADC_TRIG_SYNC_TRG0EN                 = 8,   // MTU0 TRGE
    ADC_TRIG_SYNC_TRG4AN                 = 9,   // MTU4 TADCORA
    ADC_TRIG_SYNC_TRG4BN                 = 10,  // MTU4 TADCORB
    ADC_TRIG_SYNC_TRG4AN_OR_TRG4BN       = 11,  // MTU4 TADCORA or MTU4 TADCORB
    ADC_TRIG_SYNC_TRG4AN_AND_TRG4BN      = 12,  // MTU4 TADCORA and MTU4 TADCORB
    ADC_TRIG_SYNC_TRG7AN                 = 13,  // MTU7 TADCORA
    ADC_TRIG_SYNC_TRG7BN                 = 14,  // MTU7 TADCORB
    ADC_TRIG_SYNC_TRG7AN_OR_TRG7BN       = 15,  // MTU7 TADCORA or MTU7 TADCORB
    ADC_TRIG_SYNC_TRG7AN_AND_TRG7BN      = 16,  // MTU7 TADCORA and MTU7 TADCORB
    ADC_TRIG_SYNC_TRG9AN                 = 19,  // MTU9 TRGA
    ADC_TRIG_SYNC_TRG9EN                 = 20,  // MTU9 TRGE
    ADC_TRIG_SYNC_TRG0AN_OR_TRG0EN       = 25,  // MTU0 TRGA or MTU0 TRGE
    ADC_TRIG_SYNC_TRG9AN_OR_TRG9EN       = 26,  // MTU9 TRGA or MTU9 TRGE
    ADC_TRIG_SYNC_TRG0AN_OR_TRG9AN       = 27,  // MTU0 TRGA or MTU9 TRGA
    ADC_TRIG_SYNC_TRG0EN_OR_TRG9EN       = 28,  // MTU0 TRGE or MTU9 TRGE
    ADC_TRIG_SYNC_TMRTRG0AN              = 29,  // TMR0 TCORA
    ADC_TRIG_SYNC_TMRTRG2AN              = 30,  // TMR2 TCORA
    ADC_TRIG_SYNC_TMRTRG4AN              = 31,  // TMR4 TCORA
    ADC_TRIG_SYNC_TMRTRG6AN              = 32,  // TMR6 TCORA
    ADC_TRIG_SYNC_TRG9AN_AND_TRG9EN      = 33,  // MTU9 TRGA and MTU9 TRGE
    ADC_TRIG_SYNC_TRG0AN_AND_TRG0EN      = 34,  // MTU0 TRGA and MTU0 TRGE
    ADC_TRIG_SYNC_TRG0AN_AND_TRG9AN      = 35,  // MTU0 TRGA and MTU9 TRGA
    ADC_TRIG_SYNC_TRG0EN_AND_TRG9EN      = 36,  // MTU0 TRGE and MTU9 TRGE
    ADC_TRIG_SYNC_GTADTR0AN              = 50,  // GPT0 GTADTRA
    ADC_TRIG_SYNC_GTADTR0BN              = 51,  // GPT0 GTADTRB
    ADC_TRIG_SYNC_GTADTR1AN              = 52,  // GPT1 GTADTRA
    ADC_TRIG_SYNC_GTADTR1BN              = 53,  // GPT1 GTADTRB
    ADC_TRIG_SYNC_GTADTR2AN              = 54,  // GPT2 GTADTRA
    ADC_TRIG_SYNC_GTADTR2BN              = 55,  // GPT2 GTADTRB
    ADC_TRIG_SYNC_GTADTR3AN              = 56,  // GPT3 GTADTRA
    ADC_TRIG_SYNC_GTADTR3BN              = 57,  // GPT3 GTADTRB
    ADC_TRIG_SYNC_GTADTR0AN_OR_GTADTR0BN = 58,  // GPT0 GTADTRA or GPT0 GTADTRB
    ADC_TRIG_SYNC_GTADTR1AN_OR_GTADTR1BN = 59,  // GPT1 GTADTRA or GPT1 GTADTRB
    ADC_TRIG_SYNC_GTADTR2AN_OR_GTADTR2BN = 60,  // GPT2 GTADTRA or GPT2 GTADTRB
    ADC_TRIG_SYNC_GTADTR3AN_OR_GTADTR3BN = 61,  // GPT3 GTADTRA or GPT3 GTADTRB
    ADC_TRIG_SOFTWARE                    = 64,  /* software trigger; not for Group modes
                                                   nor double trigger modes
                                                   This is not set to TRSA or TRSB */
    ADC_TRIG_NONE                        = 0x3F
} adc_trig_t;

typedef struct st_adc_cfg
{

    adc_align_t     alignment;       // ignored if addition used
    adc_add_t       add_cnt;         // add or average samples
    adc_clear_t     clearing;        // clear after read
    adc_trig_t      trigger;         // default and Group A trigger source
    adc_trig_t      trigger_groupb;  // valid only for group modes
    adc_trig_t      trigger_groupc;  // valid only for group modes
    uint8_t         priority;        // for S12ADIO int; 1=lo 15=hi 0=off/polled
    uint8_t         priority_groupb; // S12GBADI interrupt priority; 0-15
    uint8_t         priority_groupc; // S12GCADI interrupt priority; 0-15
} adc_cfg_t;


/***** ADC_CONTROL() ARGUMENT DEFINITIONS *****/


typedef enum e_adc_cmd
{
    /* Commands for special hardware configurations */
    ADC_CMD_SET_DDA_STATE_CNT,      // for Disconnect Detection Assist
    ADC_CMD_SET_SAMPLE_STATE_CNT,

    /* Command to configure channels, sensors, and comparator */
    ADC_CMD_ENABLE_CHANS,           // configure channels and sensors to scan

    /* Commands to enable hardware triggers or cause software trigger */
    ADC_CMD_ENABLE_TRIG,            // ADCSR.TRGE=1 for sync/async triggers
    ADC_CMD_SCAN_NOW,               // software trigger start scan

    /* Commands to poll for scan completion and comparator results */
    ADC_CMD_CHECK_SCAN_DONE,        // for Normal or GroupA scan
    ADC_CMD_CHECK_SCAN_DONE_GROUPA,
    ADC_CMD_CHECK_SCAN_DONE_GROUPB,
    ADC_CMD_CHECK_SCAN_DONE_GROUPC,

    /* Advanced control commands */
    ADC_CMD_DISABLE_TRIG,           // ADCSR.TRGE=0 for sync/async trigs
    ADC_CMD_DISABLE_INT,            // interrupt disable; ADCSR.ADIE=0
    ADC_CMD_ENABLE_INT,             // interrupt enable;  ADCSR.ADIE=1
    ADC_CMD_DISABLE_INT_GROUPB,     // interrupt disable; ADCSR.GBADIE=0
    ADC_CMD_ENABLE_INT_GROUPB,      // interrupt enable;  ADCSR.GBADIE=1
    ADC_CMD_DISABLE_INT_GROUPC,     // interrupt disable; ADGCTRGR.GCADIE=0
    ADC_CMD_ENABLE_INT_GROUPC       // interrupt enable;  ADGCTRGR.GCADIE=1
} adc_cmd_t;


/* for ADC_CMD_SET_DDA_STATE_CNT */

typedef enum e_adc_charge           // Disconnection Detection Assist (DDA)
{
    ADC_DDA_DISCHARGE = 0x00,
    ADC_DDA_PRECHARGE = 0x01,
    ADC_DDA_OFF = 0x02
} adc_charge_t;

typedef struct st_adc_dda
{
    adc_charge_t    method;
    uint8_t         num_states;     // 2-15
} adc_dda_t;


/* for ADC_CMD_SET_SAMPLE_STATE_CNT */

typedef enum e_adc_sst_reg          // sample state registers
{
    ADC_SST_CH0 = 0,
    ADC_SST_CH1,
    ADC_SST_CH2,
    ADC_SST_CH3,
    ADC_SST_CH4,
    ADC_SST_CH5,
    ADC_SST_CH6,
    ADC_SST_CH7,
    ADC_SST_CH8,
    ADC_SST_CH9,
    ADC_SST_CH10,
    ADC_SST_CH11,
    ADC_SST_CH16,
    ADC_SST_VOLTAGE,
    ADC_SST_REG_MAX = ADC_SST_VOLTAGE
} adc_sst_reg_t;

typedef struct st_adc_time
{
    adc_sst_reg_t   reg_id;
    uint8_t         num_states;     // ch8-20 use the same value
} adc_sst_t;

typedef enum e_adc_grpa                 // action when groupa interrupts groupb scan
{
    ADC_GRPA_PRIORITY_OFF = 0,                           // groupa ignored and does not interrupt groupb and groupc
    ADC_GRPA_GRPB_GRPC_WAIT_TRIG = 1,                    // groupb and groupc restart at next trigger
    ADC_GRPA_GRPB_GRPC_TOP_RESTART_SCAN = 3,             /* groupb and groupc restart immediately
                                                            and scans from the head of the channel */
    ADC_GRPA_GRPB_GRPC_RESTART_TOP_CONT_SCAN = 0x8003,   /* groupb and groupc restart immediately
                                                            and scans continuously from the head of the channel */
    ADC_GRPA_GRPB_GRPC_RESTART_SCAN = 0x4003,            // groupb and groupc restart immediately and scans continuously
    ADC_GRPA_GRPB_GRPC_TOP_CONT_SCAN = 0x8001,           /* groupb and groupc restart and scans continuously
                                                            from the head of the channel */
    ADC_GRPA_GRPB_GRPC_RESTART_CONT_SCAN = 0xC003,       // groupb and groupc restart immediately and scans continuously
} adc_grpa_t;

typedef enum e_adc_diag                 // Self-Diagnosis Channel
{
    ADC_DIAG_OFF = 0x00,
    ADC_DIAG_0_VOLT = 0x01,
    ADC_DIAG_HALF_VREFH0 = 0x2,
    ADC_DIAG_VREFH0 = 0x3,
    ADC_DIAG_ROTATE_VOLTS = 0x4
} adc_diag_t;

typedef enum e_adc_pga_amp
{
    ADC_PGA_NOT_USE = 0x00,
    ADC_PGA_USE     = 0x06,
} adc_pga_amp_t;

typedef enum e_adc_pga_gain
{
    /* PGA_SINGLE_END */
    ADC_PGA_GAIN_2_000  = 0x00,    /* x  2.000 */
    ADC_PGA_GAIN_2_500  = 0x01,    /* x  2.500 */
    ADC_PGA_GAIN_3_077  = 0x04,    /* x  3.077 */
    ADC_PGA_GAIN_3_636  = 0x06,    /* x  3.636 */
    ADC_PGA_GAIN_4_000  = 0x07,    /* x  4.000 */
    ADC_PGA_GAIN_4_444  = 0x08,    /* x  4.444 */
    ADC_PGA_GAIN_5_000  = 0x09,    /* x  5.000 */
    ADC_PGA_GAIN_6_667  = 0x0B,    /* x  6.667 */
    ADC_PGA_GAIN_8_000  = 0x0C,    /* x  8.000 */
    ADC_PGA_GAIN_10_000  = 0x0D,   /* x  10.000 */
    ADC_PGA_GAIN_13_333  = 0x0E    /* x  13.333 */
} adc_pga_gain_t;

typedef struct st_adc_ch_cfg            // bit 0 is ch0; bit 11 is ch11
{
    uint32_t        chan_mask;          // channels/bits 0-11
    uint32_t        chan_mask_groupb;   // valid for group modes
    uint32_t        chan_mask_groupc;   // valid for group modes
    adc_grpa_t      priority_groupa;    // valid for group modes
    uint32_t        add_mask;           // valid if add enabled in Open()
    adc_diag_t      diag_method;        // self-diagnosis virtual channel
    uint8_t         sample_hold_mask;   // channels/bits 0-2
    uint8_t         sample_hold_states; // minimum .4us
    adc_pga_amp_t   pga_amp[ADC_PGA_CHANNEL_MAX];
    adc_pga_gain_t  pga_gain[ADC_PGA_CHANNEL_MAX];
} adc_ch_cfg_t;


/***** ADC_READ() ARGUMENT DEFINITIONS *****/

typedef enum e_adc_reg
{
    ADC_REG_CH0 = 0,
    ADC_REG_CH1 = 1,
    ADC_REG_CH2 = 2,
    ADC_REG_CH3 = 3,
    ADC_REG_CH4_CH16 = 4,
    ADC_REG_CH5 = 5,
    ADC_REG_CH6 = 6,
    ADC_REG_CH7 = 7,    // last channel unit0
    ADC_REG_CH8 = 8,
    ADC_REG_CH9 = 9,
    ADC_REG_CH10 = 10,
    ADC_REG_CH11 = 11,
    ADC_REG_VOLT,

    /* both units */
    ADC_REG_DBLTRIG,
    ADC_REG_DBLTRIGA,   // loaded when first multi-source trigger was A
    ADC_REG_DBLTRIGB,   // loaded when first multi-source trigger was B
    ADC_REG_SELF_DIAG,
    ADC_REG_MAX = ADC_REG_SELF_DIAG
} adc_reg_t;

/* ADC_READALL() ARGUMENT DEFINITIONS */

typedef struct st_adc_unit0_data
{
    uint16_t    chan[ADC_0_REG_ARRAY_MAX];
    uint16_t    dbltrig;
    uint16_t    dbltrigA;
    uint16_t    dbltrigB;
    uint16_t    self_diag;
} adc_unit0_data_t;

typedef struct st_adc_unit1_data
{
    uint16_t    chan[ADC_1_REG_ARRAY_MAX];
    uint16_t    dbltrig;
    uint16_t    dbltrigA;
    uint16_t    dbltrigB;
    uint16_t    self_diag;
} adc_unit1_data_t;

typedef struct st_adc_unit2_data
{
    uint16_t    chan[ADC_2_REG_ARRAY_MAX];
    uint16_t    volt;
    uint16_t    dbltrig;
    uint16_t    dbltrigA;
    uint16_t    dbltrigB;
    uint16_t    self_diag;
} adc_unit2_data_t;

typedef struct st_adc_data
{
    adc_unit0_data_t   unit0;
    adc_unit1_data_t   unit1;
    adc_unit2_data_t   unit2;
} adc_data_t;


/*****************************************************************************
Public Functions
******************************************************************************/

#endif /* S12AD_PRV_RX24U_IF_H */

