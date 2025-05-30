/***********************************************************************************************************************
* Copyright (c) 2021 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_rspia_rx_if.h
* Description  : Functions for using RSPIA on RX devices.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 31.03.2021 1.00     First Release
*                               Supported for RX671.
*         : 13.09.2021 1.10     Added the demo for RX671.
*         : 29.07.2022 1.20     Updated demo projects.
*         : 15.08.2022 1.30     Added RX26T support.
*                               Fixed to comply GSCE coding standard revision 6.5.0.
*         : 30.06.2023 1.40     Added RX26T-256K support.
*                               Fixed to comply GSCE coding standard revision 6.5.0.
*         : 13.11.2023 1.41     Added WAIT_LOOP comments.
*         : 15.12.2023 1.50     Added support RSPIA with DMAC/DTC.
*         : 31.12.2024 1.60     Supported for Nested interrupt.
*         : 15.03.2025 1.61     Updated disclaimer.
***********************************************************************************************************************/

#ifndef RSPIA_API_HEADER_FILE
#define RSPIA_API_HEADER_FILE

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* User set table configuration options for the RSPIA code */
#include "r_rspia_rx_config.h"

/* Internal definitions. */
#include "r_rspia_rx_private.h"

/* Defines of default settings used by the RSPIA code */
#include "r_rspia_defaults.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#if ((R_BSP_VERSION_MAJOR == 6) && (R_BSP_VERSION_MINOR < 10) || (R_BSP_VERSION_MAJOR < 6))
    #error "This module must use BSP module of Rev.6.10 or higher. Please use the BSP module of Rev.6.10 or higher."
#endif

/* Version Number of API. */
#define RSPIA_RX_VERSION_MAJOR           (1)
#define RSPIA_RX_VERSION_MINOR           (61)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* The following enumeration lists the possible error codes that can be returned by the API functions. */
typedef enum e_rspia_ch       /* RSPIA channel numbers */
{
    RSPIA_CH0=0,
    RSPIA_NUM_CH
} rspia_ch_t;

typedef enum rspia_err_e      /* RSPIA API error codes */
{
    RSPIA_SUCCESS = 0,        /* Successful; channel initialized */
    RSPIA_ERR_BAD_CHAN,       /* Invalid channel number. */
    RSPIA_ERR_OMITTED_CHAN,   /* RSPIA_USE_CHx is 0 in config.h */
    RSPIA_ERR_CH_NOT_OPENED,  /* Channel not yet opened. */
    RSPIA_ERR_CH_NOT_CLOSED,  /* Channel still open from previous open. */
    RSPIA_ERR_UNKNOWN_CMD,    /* Control command is not recognized. */
    RSPIA_ERR_INVALID_ARG,    /* Argument is not valid for parameter. */
    RSPIA_ERR_ARG_RANGE,      /* Argument is out of range for parameter. */
    RSPIA_ERR_NULL_PTR,       /* Received null pointer; missing required argument. */
    RSPIA_ERR_LOCK,           /* The lock procedure failed. */
    RSPIA_ERR_UNDEF,          /* Undefined/unknown error */
} rspia_err_t;

typedef enum                      /* RSPIA API event codes */
{
    RSPIA_EVT_TRANSFER_COMPLETE,  /* The data transfer completed. */
    RSPIA_EVT_TRANSFER_ABORTED,   /* The data transfer was aborted. */
    RSPIA_EVT_ERR_MODE_FAULT,     /* Mode fault error. */
    RSPIA_EVT_ERR_READ_OVF,       /* Read overflow. */
    RSPIA_EVT_ERR_PARITY,         /* Parity error. */
    RSPIA_EVT_ERR_UNDER_RUN,      /* Under run error. */
    RSPIA_EVT_ERR_UNDEF           /* Undefined/unknown error event. */
} rspia_evt_t;

/************ Type defines used with the R_RSPIA_Open function. ***************/
/* Hardware interface mode configuration settings. */
typedef enum
{
    RSPIA_IF_MODE_3WIRE  =  RSPIA_SPCR_SPMS,    /* Use GPIO for slave select. */
    RSPIA_IF_MODE_4WIRE  = ~RSPIA_SPCR_SPMS     /* Use slave select signals controlled by RSPIA. */
} rspia_interface_mode_t;

/* Frame format select configuration settings. */
typedef enum
{
    RSPIA_IF_FRAME_TI_SSP        =  RSPIA_SPCR_FRFS,  /* Use TI SSP Frame format.  */
    RSPIA_IF_FRAME_MOTOROLA_SPI  = ~RSPIA_SPCR_FRFS   /* Use Motorola SPI Frame format. */
} rspia_frame_select_t;

/* Master or slave operating mode configuration settings. */
typedef enum
{
    RSPIA_MS_MODE_MASTER =  RSPIA_SPCR_MSTR,    /* Channel operates as SPI master */
    RSPIA_MS_MODE_SLAVE  = ~RSPIA_SPCR_MSTR,    /* Channel operates as SPI slave */
} rspia_master_slave_mode_t;

/* Define for data transfer mode */
typedef enum e_rspia_str_tranmode
{
    RSPIA_TRANS_MODE_SW         = 0,   /* Data transfer mode is software. */
    RSPIA_TRANS_MODE_DMAC,             /* Data transfer mode is DMAC. */
    RSPIA_TRANS_MODE_DTC               /* Data transfer mode is DTC. */
} rspia_str_tranmode_t;

/* Abstraction of channel handle data structure.
 * User application will use this as a reference to an opened channel. */
typedef struct rspia_cfg_block_s * rspia_hdl_t;

typedef struct rspia_callback_data_s
{
    rspia_hdl_t  hdl;
    rspia_evt_t  event;
} rspia_callback_data_t;

typedef struct rspia_chnl_settings_s
{
    rspia_interface_mode_t     gpio_ssl;         /* RSPIA_IF_MODE_4WIRE: RSPIA slave selects,
                                                  * RSPIA_IF_MODE_3WIRE: GPIO slave selects. */
    rspia_master_slave_mode_t  master_slave_mode;/* RSPIA_MS_MODE_MASTER or RSPIA_MS_MODE_SLAVE. */
    rspia_frame_select_t       frame_mode;       /* RSPIA_IF_FRAME_TI_SSP or RSPIA_IF_FRAME_MOTOROLA_SPI. */
    uint32_t                   bps_target;       /* The target bits per second setting value for the channel. */
    rspia_str_tranmode_t       tran_mode;        /* Data transfer mode. */
} rspia_chan_settings_t;

/************ Type defines used with the R_RSPIA_Control function. ***************/
/* Control function command codes. */
typedef enum rspia_cmd_e
{
    RSPIA_CMD_SET_BAUD = 1,             /* Change the base bit rate */
    RSPIA_CMD_ABORT,                    /* Stop the current read or write operation immediately. */
    RSPIA_CMD_SET_REGS,                 /* Set all supported RSPIA registers in one operation. Expert use only! */
    RSPIA_CMD_CHANGE_TX_FIFO_THRESH,    /* change TX FIFO threshold */
    RSPIA_CMD_CHANGE_RX_FIFO_THRESH,    /* change TX FIFO threshold */
    RSPIA_CMD_SET_TRANS_MODE,           /* Set the data transfer mode */
    RSPIA_CMD_UNKNOWN                   /* Not a valid command. */
} rspia_cmd_t;

/* Data structure for the Set Baud command. */
typedef struct rspia_cmd_baud_s
{
    uint32_t    bps_target;     /* The target bits per second setting value for the channel. */
} rspia_cmd_baud_t;

/* Advanced use! Entries for use in setting RSPIA registers that control operation.
 * To be used with the R_RSPIA_Control()-RSPIA_CMD_SETREGS command.
 * Values will be copied directly into the associated register when used.
 * To use this with the RSPIA_CMD_SETREGS command, user creates an instance of this with
 * settings as required, and passes a pointer to it as an argument in the call to R_RSPIA_Control(). */
typedef struct rspia_cmd_setregs_s
{
    uint16_t spdcr_val;      /* RSPIA Data Control Register (SPDCR) */
    uint8_t  sslp_val;       /* RSPIA Slave Select Polarity Register (SSLP) */
    uint8_t  sppcr_val;      /* RSPIA Pin Control Register (SPPCR) */
    uint8_t  spckd_val;      /* RSPIA Clock Delay Register (SPCKD) */
    uint8_t  sslnd_val;      /* RSPIA Slave Select Negation Delay Register (SSLND) */
    uint8_t  spnd_val;       /* RSPIA Next-Access Delay Register (SPND) */
} rspia_cmd_setregs_t;

/* Data structure for the Set Transfer mode command. */
typedef struct rspia_cmd_trans_mode_s
{
    rspia_str_tranmode_t    transfer_mode;    /* The transfer mode setting value for the channel. */
} rspia_cmd_trans_mode_t;

/**********************************************************************************************************************
 * Type defines used with the R_RSPIA_Write, R_RSPIA_Read, and R_RSPIA_WriteRead functions.
 * Enumerates are provided for each field of the command word for write and read operations.
 * A command word must be formed by complete initialization of a structure of these.
 * This word is passed as an argument to the R_RSPIA_Write, R_RSPIA_Read, and R_RSPIA_WriteRead functions
 * and will get copied to the SPCMD register with each call.
***********************************************************************************************************************/

/* Clock phase and polarity */
typedef enum
{
    RSPIA_SPCMD_CPHA_SAMPLE_ODD = (0x0),    /* 0: Data sampling on odd edge, data variation on even edge. */
    RSPIA_SPCMD_CPHA_SAMPLE_EVEN  = (0x1)   /* 1: Data variation on odd edge, data sampling on even edge. */
} rspia_spcmd_cpha_t;

typedef enum
{
    RSPIA_SPCMD_CPOL_IDLE_LO = (0x0),      /* 0: RSPCK is low when idle. */
    RSPIA_SPCMD_CPOL_IDLE_HI = (0x1)       /* 1: RSPCK is high when idle. */
} rspia_spcmd_cpol_t;

/* Clock base rate division */
typedef enum
{
    RSPIA_SPCMD_BR_DIV_1 = (0x0),    /* Select the base bit rate */
    RSPIA_SPCMD_BR_DIV_2 = (0x1),    /* Select the base bit rate divided by 2 */
    RSPIA_SPCMD_BR_DIV_4 = (0x2),    /* Select the base bit rate divided by 4 */
    RSPIA_SPCMD_BR_DIV_8 = (0x3)     /* Select the base bit rate divided by 8 */
} rspia_spcmd_br_div_t;

/* Slave select to be asserted during transfer operation. */
typedef enum
{
    RSPIA_SPCMD_ASSERT_SSL0 = (0x0),     /* Select SSL0 */
    RSPIA_SPCMD_ASSERT_SSL1 = (0x1),     /* Select SSL1 */
    RSPIA_SPCMD_ASSERT_SSL2 = (0x2),     /* Select SSL2 */
    RSPIA_SPCMD_ASSERT_SSL3 = (0x3)      /* Select SSL3 */
} rspia_spcmd_ssl_assert_t;

/* Slave select negation. */
typedef enum
{
    RSPIA_SPCMD_SSL_NEGATE = (0x0),   /* 0: Negates all SSL signals upon completion of transfer */
    RSPIA_SPCMD_SSL_KEEP  =  (0x1)    /* 1: Keep SSL signal level from end of transfer until start of next. */
} rspia_spcmd_ssl_negation_t;

/* Frame data length */
typedef enum
{
    RSPIA_SPCMD_BIT_LENGTH_4  = (0x03),    /* 00011 =  4 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_5  = (0x04),    /* 00100 =  5 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_6  = (0x05),    /* 00101 =  6 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_7  = (0x06),    /* 00110 =  7 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_8  = (0x07),    /* 00111 =  8 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_9  = (0x08),    /* 01000 =  9 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_10 = (0x09),    /* 01001 = 10 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_11 = (0x0A),    /* 01010 = 11 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_12 = (0x0B),    /* 01011 = 12 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_13 = (0x0C),    /* 01100 = 13 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_14 = (0x0D),    /* 01101 = 14 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_15 = (0x0E),    /* 01110 = 15 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_16 = (0x0F),    /* 01111 = 16 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_17 = (0x10),    /* 10000 = 17 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_18 = (0x11),    /* 10001 = 17 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_19 = (0x12),    /* 10010 = 19 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_20 = (0x13),    /* 10011 = 20 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_21 = (0x14),    /* 10100 = 21 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_22 = (0x15),    /* 10101 = 22 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_23 = (0x16),    /* 10110 = 23 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_24 = (0x17),    /* 10111 = 24 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_25 = (0x18),    /* 11000 = 25 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_26 = (0x19),    /* 11001 = 26 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_27 = (0x1A),    /* 11010 = 27 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_28 = (0x1B),    /* 11011 = 28 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_29 = (0x1C),    /* 11100 = 29 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_30 = (0x1D),    /* 11101 = 30 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_31 = (0x1E),    /* 11110 = 31 bits data length */
    RSPIA_SPCMD_BIT_LENGTH_32 = (0x1F)     /* 11111 = 32 bits data length */
} rspia_spcmd_bit_length_t;

/* Data transfer bit order. */
typedef enum
{
    RSPIA_SPCMD_ORDER_MSB_FIRST = (0x0),    /* 0: MSB first. */
    RSPIA_SPCMD_ORDER_LSB_FIRST = (0x1)     /* 1: LSB first. */
} rspia_spcmd_bit_order_t;

/* RSPIA signal delays */
typedef enum
{
    RSPIA_SPCMD_NEXT_DLY_1     = (0x0),  /* 0: A next-access delay of 1 RSPCK +2 PCLK. */
    RSPIA_SPCMD_NEXT_DLY_SSLND = (0x1),  /* 1: Next-access delay = RSPI nextaccess delay register (SPND) */
} rspia_spcmd_spnden_t;

typedef enum
{
    RSPIA_SPCMD_SSL_NEG_DLY_1     = (0x0),  /* 0: An SSL negation delay of 1 RSPCK. */
    RSPIA_SPCMD_SSL_NEG_DLY_SSLND = (0x1),  /* 1: Delay = slave select negation delay register (SSLND) */
} rspia_spcmd_slnden_t;

typedef enum
{
    RSPIA_SPCMD_CLK_DLY_1         = (0x0),  /* 0: An RSPCK delay of 1 RSPCK. */
    RSPIA_SPCMD_CLK_DLY_SPCKD     = (0x1)   /* 1: Delay = setting of RSPI clock delay register (SPCKD). */
} rspia_spcmd_sckden_t;

typedef enum
{
    RSPIA_SPCMD_RESERVE_BIT = (0x0)
} rspia_spcmd_reserve_bit_t;

/* The complete command word data structure. This contains one from each of the
 * above fields in the correct order to set all the bits of the SPCMD register. */
typedef union rspia_command_word_s
{
    R_BSP_ATTRIB_STRUCT_BIT_ORDER_RIGHT_14(
        rspia_spcmd_cpha_t         cpha          :1,
        rspia_spcmd_cpol_t         cpol          :1,
        rspia_spcmd_br_div_t       br_div        :2,
        rspia_spcmd_reserve_bit_t  rs0           :3,    /* reserved */
        rspia_spcmd_ssl_negation_t ssl_negate    :1,
        rspia_spcmd_reserve_bit_t  rs1           :4,    /* reserved */
        rspia_spcmd_bit_order_t    bit_order     :1,
        rspia_spcmd_spnden_t       next_delay    :1,
        rspia_spcmd_slnden_t       ssl_neg_delay :1,
        rspia_spcmd_sckden_t       clock_delay   :1,
        rspia_spcmd_bit_length_t   bit_length    :5,
        rspia_spcmd_reserve_bit_t  rs2           :3,    /* reserved */
        rspia_spcmd_ssl_assert_t   ssl_assert    :3,
        rspia_spcmd_reserve_bit_t  rs3           :5     /* reserved */
);
    uint32_t word[1];
} rspia_command_word_t;

/***********************************************************************************************************************
Public Functions
***********************************************************************************************************************/
/**********************************************************************************************************************
 * Function Name: R_RSPIA_Open
 * Description  : This function initializes the associated registers.
 * Arguments    : chan - Number of the RSPIA channel to be initialized.
 *                *p_cfg - Pointer to RSPIA channel configuration data structure.
 *                p_cmd - SPCMD command data structure.
 *                (*p_callback)(void*p_cbdat) - Pointer to user defined function called from interrupt.
 *                *p_hdl - Pointer to a handle for channel. Handle value will be set by this function.
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
***********************************************************************************************************************/
rspia_err_t   R_RSPIA_Open (uint8_t                 chan,
                            rspia_chan_settings_t * p_cfg,
                            rspia_command_word_t    p_cmd,
                            void (*p_callback)(void * p_cbdat),
                            rspia_hdl_t           * p_hdl);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_Control
 * Description  : The Control function is responsible for handling special hardware or software operations for the RSPI
 *                channel.
 * Arguments    : hdl - Handle for the channel.
 *                cmd -  Enumerated command code.
 *                pcmd_data - Pointer to the required data structure, which is needed for operation completion.
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t R_RSPIA_Control (rspia_hdl_t    hdl,
                            rspia_cmd_t    cmd,
                            void         * pcmd_data);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_Read
 * Description  : The Read function receives data from the selected SPI device.
 * Arguments    : hdl - Handle for the channel.
 *                p_cmd - Bit field contains all the RSPIA command register settings for SPCMD for this operation.
 *                p_dst - Void type pointer to a destination buffer.
 *                length - The number of data frames to be transferred.
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t  R_RSPIA_Read  (rspia_hdl_t           hdl,
                            rspia_command_word_t  p_cmd,
                            void                * p_dst,
                            uint16_t              length);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_Write
 * Description  : The Write function transmits data to the selected SPIA device.
 * Arguments    : hdl - Handle for the channel.
 *                p_cmd - Bit field contains all the RSPIA command register settings for SPCMD for this operation.
 *                p_src - Void type pointer to a source data buffer.
 *                length - The number of data frames to be transferred.
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t  R_RSPIA_Write (rspia_hdl_t          hdl,
                            rspia_command_word_t p_cmd,
                            void               * p_src,
                            uint16_t             length);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_WriteRead
 * Description  : Simultaneously transmits data to a SPI device while receiving data from a SPI device.
 * Arguments    : hdl - Handle for the channel
 *                p_cmd - Bit field contains all the RSPIA command register settings for SPCMD for this operation.
 *                p_src - Void type pointer to a source data buffer.
 *                p_dst - Void type pointer to a destination data buffer.
 *                length - Length - The number of data frames to be transferred.
 * Return Value : [rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t  R_RSPIA_WriteRead (rspia_hdl_t         hdl,
                                rspia_command_word_t p_cmd,
                                void               * p_src,
                                void               * p_dst,
                                uint16_t             length);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_Close
 * Description  : Fully disables the RSPIA channel designated by the handle.
 * Argument     : hdl - RSPIA handle number
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t  R_RSPIA_Close (rspia_hdl_t hdl);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_GetVersion
 * Description  : This function returns the driver version number at runtime.
 * Return Value : uint32_t - Version number of current RSPIA driver.
 *********************************************************************************************************************/
uint32_t  R_RSPIA_GetVersion (void);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_IntSptiIerClear
 * Description  : This function is used to clear the ICU.IERm.IENj bit of the transmit buffer-empty interrupt (SPTI).
 * Argument     : hdl - RSPIA handle number
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t  R_RSPIA_IntSptiIerClear (rspia_hdl_t hdl);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_IntSpriIerClear
 * Description  : This function is used to clear the ICU.IERm.IENj bit of the receive buffer-full interrupt (SPRI).
 * Argument     : hdl - RSPIA handle number
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t  R_RSPIA_IntSpriIerClear (rspia_hdl_t hdl);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_DisableSpti
 * Description  : This function disables the generation of transmit buffer empty interrupt request.
 * Argument     : hdl - RSPIA handle number
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t  R_RSPIA_DisableSpti (rspia_hdl_t hdl);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_DisableRSPI
 * Description  : This function is set to disable the RSPI function.
 * Argument     : hdl - RSPIA handle number
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t  R_RSPIA_DisableRSPI (rspia_hdl_t hdl);

/**********************************************************************************************************************
 * Function Name: R_RSPIA_GetBuffRegAddress
 * Description  : This function is used to fetch the address of the RSPIA data register (SPDR).
 * Argument     : hdl - RSPIA handle number
 *                p_spdr_addr - The pointer for storing the address of SPDR. Set this to the address of the
 *                storage destination.
 * Return Value : rspia_err_t - RSPIA enumerated error codes.
 *********************************************************************************************************************/
rspia_err_t  R_RSPIA_GetBuffRegAddress (rspia_hdl_t hdl, uint32_t *p_spdr_addr);

#endif /* RSPIA_API_HEADER_FILE */
