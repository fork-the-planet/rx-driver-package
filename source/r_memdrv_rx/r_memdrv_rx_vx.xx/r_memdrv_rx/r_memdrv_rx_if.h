/***********************************************************************************************************************
* Copyright (c) 2018 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_memdrv_rx_if.h
* Version      : 1.31
* Description  : Memory driver header file
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 15.12.2018 1.00    Initial Release
*              : 04.04.2019 1.01    Added support for GNUC and ICCRX.
*                                   Fixed coding style.
*              : 22.11.2019 1.02    Modify the parameter type of structure Memory Driver I/F information.
*              : 10.09.2020 1.03    Changed version to 1.03.
*              : 30.10.2021 1.04    Add the definition of QSPIX.
*              : 16.03.2023 1.05    Added support for RSCI and QSPIX Memory Mapped Mode.
*              : 07.06.2023 1.10    Fixed issue that software lock was not released when RSPI communication timeout 
*                                   occurs, when MEMDRV FIT, RSPI FIT and DMAC/DTC FIT are used together.
*              : 29.08.2023 1.20    Updated demo projects.
*              : 20.12.2024 1.30    Updated the data count formulas for RSPI mode and QSPI mode.
*                                   Added dependency modules to the options in MDF file.
*                                   Updated demo projects.
*              : 15.03.2025 1.31    Updated disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

#ifndef MEMDRV_IF_H
#define MEMDRV_IF_H
/* Version Number of API. */
#define MEMDRV_VERSION_MAJOR                 (1)
#define MEMDRV_VERSION_MINOR                 (31)

/* Define device no. */
#define MEMDRV_DEV0                          (0)
#define MEMDRV_DEV1                          (1)

/* Definitions of device driver channel no. */
#define MEMDRV_DRVR_CH0                      (0x00000000ul)
#define MEMDRV_DRVR_CH1                      (0x00000001ul)
#define MEMDRV_DRVR_CH2                      (0x00000002ul)
#define MEMDRV_DRVR_CH3                      (0x00000003ul)
#define MEMDRV_DRVR_CH4                      (0x00000004ul)
#define MEMDRV_DRVR_CH5                      (0x00000005ul)
#define MEMDRV_DRVR_CH6                      (0x00000006ul)
#define MEMDRV_DRVR_CH7                      (0x00000007ul)
#define MEMDRV_DRVR_CH8                      (0x00000008ul)
#define MEMDRV_DRVR_CH9                      (0x00000009ul)
#define MEMDRV_DRVR_CH10                     (0x0000000aul)
#define MEMDRV_DRVR_CH11                     (0x0000000bul)
#define MEMDRV_DRVR_CH12                     (0x0000000cul)
#define MEMDRV_DRVR_CH13                     (0x0000000dul)
#define MEMDRV_DRVR_CH14                     (0x0000000eul)
#define MEMDRV_DRVR_CH15                     (0x0000000ful)

/* Definitions of device driver */
#define MEMDRV_DRVR_RX_FIT_RSPI              (0x00000100ul)
#define MEMDRV_DRVR_RX_FIT_QSPI_SMSTR        (0x00000200ul)
#define MEMDRV_DRVR_RX_FIT_SCI_SPI           (0x00000400ul)
#define MEMDRV_DRVR_RX_FIT_QSPIX_IAM         (0x00000800ul)
#define MEMDRV_DRVR_RX_FIT_QSPIX_MMM         (0x00001000ul)
#define MEMDRV_DRVR_RX_FIT_RSCI_SPI          (0x00002000ul)

/* Definitions of data transfer method */
#define MEMDRV_TRNS_CPU                      (0x00001000ul)
#define MEMDRV_TRNS_DMAC                     (0x00002000ul)
#define MEMDRV_TRNS_DTC                      (0x00004000ul)

/* Definitions of input/output mode */
#define MEMDRV_MODE_SINGLE                   ((uint8_t)(0x01))
#define MEMDRV_MODE_DUAL                     ((uint8_t)(0x02))
#define MEMDRV_MODE_QUAD                     ((uint8_t)(0x03))

/* Definitions of input/output mode */
#define MEMDRV_ADDR_4BYTES                   ((uint8_t)(4))
#define MEMDRV_ADDR_3BYTES                   ((uint8_t)(3))

#define MEMDRV_TRNS_CMD                      (0x0703)       /* data length is 8 bits, CPOL is 1, CHPA is 1 */
#define MEMDRV_TRNS_DATA_CMD                 (0x0203)       /* data length is 32 bits, CPOL is 1, CHPA is 1 */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Enumeration for return values */
typedef enum e_memdrv_err
{
    MEMDRV_BUSY         = 1,  /* Successful operation (device is busy) */
    MEMDRV_SUCCESS      = 0,  /* Successful operation */
    MEMDRV_ERR_PARAM    = -1, /* Parameter error */
    MEMDRV_ERR_HARD     = -2, /* Hardware error */
    MEMDRV_ERR_WP       = -4, /* Write-protection error */
    MEMDRV_ERR_TIMEOUT  = -6, /* Time out error */
    MEMDRV_ERR_OTHER    = -7  /* Other error */
} memdrv_err_t;

/* Memory Driver I/F information */
typedef struct
{
    uint32_t    cnt;
    uint32_t    p_addr;
    uint8_t   * p_data;
    uint8_t     io_mode;
    uint8_t     addr_size;
    bool        read_after_write;
    bool        read_in_memory_mapped;
    uint8_t     rsv[3];
} st_memdrv_info_t;
/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Public Functions
***********************************************************************************************************************/
memdrv_err_t    R_MEMDRV_Open(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_Close(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_Disable(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_DisableTxData(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_DisableRxData(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_Enable(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_EnableTxData(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_EnableRxData(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_Tx(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_TxData(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_Rx(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
memdrv_err_t    R_MEMDRV_RxData(uint8_t devno, st_memdrv_info_t * p_memdrv_info);
void            R_MEMDRV_ClearDMACFlagTx(uint8_t devno);
void            R_MEMDRV_ClearDMACFlagRx(uint8_t devno);
void            R_MEMDRV_1msInterval(void);
memdrv_err_t    R_MEMDRV_SetLogHdlAddress(uint32_t user_long_que);
uint32_t        R_MEMDRV_Log(uint32_t flg, uint32_t fid, uint32_t line);
uint32_t        R_MEMDRV_GetVersion(void);

#endif /* MEMDRV_IF_H */
