/***********************************************************************************************************************
* Copyright (c) 2014 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
* System Name  : FLASH SPI driver software
* File Name    : r_flash_spi_mx_type_sub.c
* Version      : 3.51
* Device       : -
* Abstract     : Sub module
* Tool-Chain   : -
* OS           : not use
* H/W Platform : -
* Description  : SPI FLASH Sub file
* Limitation   : None
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 23.07.2014 2.21     Created
*              : 29.05.2015 2.32     Revised functions of same as Ver.2.32 of EEPROM SPI FIT module.
*              : 31.12.2021 3.03     Added variable "read_after_write" "read_after_write_add" and
*                                    "read_after_write_data" for controlling SPI bus.
*              : 16.03.2023 3.20     Added support for QSPIX Memory Mapped Mode.
*              : 15.11.2023 3.40     Added support for reading across multiple banks in QSPIX Memory Mapped Mode.
*                                    Updated according to GSCE Code Checker 6.50.
*                                    Added support for MX25U6432F.
*                                    Added features Advanced sector protection supporting for MX66L1G45 and MX25U6432F.
*              : 15.03.2025 3.51     Updated disclaimer.
***********************************************************************************************************************/


/************************************************************************************************
Includes <System Includes> , "Project Includes"
*************************************************************************************************/
#include "r_flash_spi_if.h"                     /* FLASH driver I/F definitions                 */
#include "r_flash_spi_config.h"                 /* FLASH driver Configuration definitions       */
#include "../../r_flash_spi_private.h"          /* FLASH driver Private module definitions      */


/* Check flash memory types. */
#if (FLASH_SPI_CFG_DEV0_MX25L == 1) || (FLASH_SPI_CFG_DEV0_MX66L == 1) || (FLASH_SPI_CFG_DEV0_MX25R == 1) || (FLASH_SPI_CFG_DEV0_MX25U == 1) ||\
    (FLASH_SPI_CFG_DEV1_MX25L == 1) || (FLASH_SPI_CFG_DEV1_MX66L == 1) || (FLASH_SPI_CFG_DEV1_MX25R == 1) || (FLASH_SPI_CFG_DEV1_MX25U == 1)


/************************************************************************************************
Macro definitions
*************************************************************************************************/
/*---------- Definitions of FLASH command -----------*/
#define FLASH_SPI_MX_CMD_WREN       ((uint8_t)(0x06)) /* Write Enable                                 */
#define FLASH_SPI_MX_CMD_WRDI       ((uint8_t)(0x04)) /* Write Disable                                */
#define FLASH_SPI_MX_CMD_RDSR       ((uint8_t)(0x05)) /* Read Status Register                         */
#define FLASH_SPI_MX_CMD_WRSR       ((uint8_t)(0x01)) /* Write Status Register                        */
#define FLASH_SPI_MX_CMD_RDCR       ((uint8_t)(0x15)) /* Read Configuration Register                  */
#define FLASH_SPI_MX_CMD_RDSCUR     ((uint8_t)(0x2b)) /* Read Security Register                       */
#define FLASH_SPI_MX_CMD_FREAD      ((uint8_t)(0x0b)) /* Read Data at Higher Speed                    */
#define FLASH_SPI_MX_CMD_DREAD      ((uint8_t)(0x3b)) /* Dual Read (Single -> Dual Out)               */
#define FLASH_SPI_MX_CMD_QREAD      ((uint8_t)(0x6b)) /* Quad Read (Single -> Quad Out)               */
#define FLASH_SPI_MX_CMD_PP         ((uint8_t)(0x02)) /* Page Program (Single -> Single Input         */
#define FLASH_SPI_MX_CMD_4PP        ((uint8_t)(0x38)) /* Quad Page Program (Single -> Quad Input)     */
#define FLASH_SPI_MX_CMD_SE         ((uint8_t)(0x20)) /* Sector Erase (4KB)                           */
#define FLASH_SPI_MX_CMD_BE32K      ((uint8_t)(0x52)) /* Block Erase (32KB)                           */
#define FLASH_SPI_MX_CMD_BE64K      ((uint8_t)(0xd8)) /* Block Erase (64KB)                           */
#define FLASH_SPI_MX_CMD_CE         ((uint8_t)(0x60)) /* Chip Erase                                   */
#define FLASH_SPI_MX_CMD_RDID       ((uint8_t)(0x9f)) /* Read Identification                          */
#define FLASH_SPI_MX_CMD_EN4B       ((uint8_t)(0xb7)) /* Enter 4-byte Address Mode                    */
#define FLASH_SPI_MX_CMD_EX4B       ((uint8_t)(0xe9)) /* Exit 4-byte Address Mode                     */
#define FLASH_SPI_MX_CMD_WPSEL      ((uint8_t)(0x68)) /* Write Protect Selection                      */
#define FLASH_SPI_MX_CMD_WRLR       ((uint8_t)(0x2c)) /* Write Lock Register                          */
#define FLASH_SPI_MX_CMD_RDLR       ((uint8_t)(0x2d)) /* Read Lock Register                           */
#define FLASH_SPI_MX_CMD_SPBLK      ((uint8_t)(0xa6)) /* Set SPB Lock Bit                             */
#define FLASH_SPI_MX_CMD_RDSPBLK    ((uint8_t)(0xa7)) /* Read SPB Lock Register                       */
#define FLASH_SPI_MX_CMD_RDSPB      ((uint8_t)(0xe2)) /* Read SPB Status                              */
#define FLASH_SPI_MX_CMD_WRSPB      ((uint8_t)(0xe3)) /* SPB Program                                  */
#define FLASH_SPI_MX_CMD_ESSPB      ((uint8_t)(0xe4)) /* SPB Erase                                    */
#define FLASH_SPI_MX_CMD_GBULK      ((uint8_t)(0x98)) /* Gang Block Unlock                            */
#define FLASH_SPI_MX_CMD_GBLK       ((uint8_t)(0x7e)) /* Gang Block Lock                              */


/*--------- Command transmission processing ----------*/
#define R_FLASH_SPI_MX_CMD_WREN(devno, read_after_write)      (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_WREN,   (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_WRDI(devno, read_after_write)      (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_WRDI,   (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_RDSR(devno, read_after_write)      (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_RDSR,   (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_WRSR(devno, read_after_write)      (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_WRSR,   (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_RDCR(devno, read_after_write)      (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_RDCR,   (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_RDSCUR(devno, read_after_write)    (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_RDSCUR, (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_SE(devno, addr, addr_size, read_after_write)    (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_SE, \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE+addr_size, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_BE32K(devno, addr, addr_size, read_after_write) (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_BE32K, \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE+addr_size, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_BE64K(devno, addr, addr_size, read_after_write) (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_BE64K, \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE+addr_size, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_CE(devno, addr, read_after_write)  (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_CE,   (uint32_t)addr, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_RDID(devno, read_after_write)      (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_RDID,   (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_ENTER4(devno, read_after_write)    (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_EN4B,   (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_EXIT4(devno, read_after_write)     (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_EX4B,   (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
/* READ Command */
/* 1 Dummy cycle is indicated as "1". */
#define R_FLASH_SPI_MX_CMD_FREAD(devno, addr, addr_size, read_after_write) (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_FREAD, \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE+addr_size+1, read_after_write, TRUE))
#define R_FLASH_SPI_MX_CMD_DREAD(devno, addr, addr_size, read_after_write) (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_DREAD, \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE+addr_size+1, read_after_write, TRUE))
#define R_FLASH_SPI_MX_CMD_QREAD(devno, addr, addr_size, read_after_write) (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_QREAD, \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE+addr_size+1, read_after_write, TRUE))
/* Page Program Command */
#define R_FLASH_SPI_MX_CMD_PP(devno, addr, addr_size, read_after_write)   (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_PP,  \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_4PP(devno, addr, addr_size, read_after_write)  (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_4PP, \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))

/* Advanced Sector Protection Command */
#define R_FLASH_SPI_MX_CMD_WPSEL(devno, read_after_write)     (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_WPSEL, (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_RDLR(devno, read_after_write)      (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_RDLR,  (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_SPBLK(devno, read_after_write)     (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_SPBLK, (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_RDSPBLK(devno, read_after_write)   (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_RDSPBLK, (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_WRSPB(devno, addr, addr_size, read_after_write)     (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_WRSPB, \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE+addr_size, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_RDSPB(devno, addr, addr_size, read_after_write)     (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_RDSPB, \
                                                            (uint32_t)addr, FLASH_SPI_MX_CMD_SIZE+addr_size, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_ESSPB(devno, read_after_write)     (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_ESSPB, (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_GBULK(devno, read_after_write)     (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_GBULK, (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))
#define R_FLASH_SPI_MX_CMD_GBLK(devno, read_after_write)      (r_flash_spi_mx_send_cmd(devno, FLASH_SPI_MX_CMD_GBLK,  (uint32_t)0, \
                                                            FLASH_SPI_MX_CMD_SIZE, read_after_write, FALSE))

/************************************************************************************************
Typedef definitions
*************************************************************************************************/
/* uint32_t <-> uint8_t conversion */
typedef union
{
    uint32_t    ul;
    uint8_t     uc[4];
} flash_spi_mx_exchg_long_t;                            /* total 4 bytes                       */


/************************************************************************************************
Exported global variables (to be accessed by other files)
*************************************************************************************************/


/************************************************************************************************
Private global variables and functions
*************************************************************************************************/
static bool s_flash_mx_read_memory_mapped[FLASH_SPI_DEV_NUM] =
{
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
#if (MEMDRV_DRVR_RX_FIT_QSPIX_MMM == MEMDRV_CFG_DEV0_MODE_DRVR)
    true,
#else
    false,
#endif
#if (MEMDRV_DRVR_RX_FIT_QSPIX_MMM == MEMDRV_CFG_DEV1_MODE_DRVR)
    true
#else
    false
#endif
#elif (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
#if (MEMDRV_CFG_DEV0_MODE_DRVR == MEMDRV_DRVR_RX_FIT_QSPIX_MMM)
    true
#else
    false
#endif
#else
#endif
};

/* Transmission buffer */
static uint32_t s_flash_mx_cmdbuf[FLASH_SPI_DEV_NUM][8/sizeof(uint32_t)];

/* Command transmission */
static flash_spi_status_t r_flash_spi_mx_send_cmd (uint8_t devno, uint8_t cmd, uint32_t addr, uint8_t cmdsize,
                                                   bool read_after_write, bool read_in_memory_mapped);

/* Writing enable */
static flash_spi_status_t r_flash_spi_mx_write_en (uint8_t devno);

/* Writing status register */
static flash_spi_status_t r_flash_spi_mx_write_stsreg (uint8_t devno, flash_spi_reg_info_t * p_reg, bool read_after_write);

/* Wait for ready after busy by program or erase operation */
static flash_spi_status_t r_flash_spi_mx_poll_prog_erase (uint8_t devno, flash_spi_poll_mode_t mode);

/* Wait for ready after register write operation */
static flash_spi_status_t r_flash_spi_mx_poll_reg_write (uint8_t devno);

/* Set command */
static void               r_flash_spi_mx_cmd_set (uint8_t devno, uint8_t cmd, uint32_t addr, uint8_t cmdsize);

/* Gang Block Unlock */
static flash_spi_status_t r_flash_spi_mx_gang_block_unlock (uint8_t devno);

/* Gang Block Lock */
static flash_spi_status_t r_flash_spi_mx_gang_block_lock (uint8_t devno);

/* Writing write protect selection */
static flash_spi_status_t r_flash_spi_mx_set_write_protect_selection (uint8_t devno);

/* Reading lock register */
static flash_spi_status_t r_flash_spi_mx_read_lkreg (uint8_t devno, uint8_t * p_lkreg);

/* Writing lock register */
static flash_spi_status_t r_flash_spi_mx_write_lkreg (uint8_t devno);

/* Reading SPB lock register */
static flash_spi_status_t r_flash_spi_mx_read_spblkreg (uint8_t devno, uint8_t * p_spblkreg);

/* Writing SPB lock register */
static flash_spi_status_t r_flash_spi_mx_write_spblkreg (uint8_t devno);

/* Erasing SPB register */
static flash_spi_status_t r_flash_spi_mx_erase_spbreg (uint8_t devno);

/* Reading SPB register */
static flash_spi_status_t r_flash_spi_mx_read_spbreg (uint8_t devno, uint32_t addr, uint8_t * p_spbreg);

/* Writing SPB register */
static flash_spi_status_t r_flash_spi_mx_write_spbreg (uint8_t devno, uint32_t addr);


/************************************************************************************************
* Function Name: r_flash_spi_mx_init_port
* Description  : Initializes the ports related to the specified device.
* Arguments    : uint8_t           devno                ;   Device No. (FLASH_SPI_DEVn)
* Return Value : None
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
void r_flash_spi_mx_init_port(uint8_t devno)
{
    r_flash_spi_cs_init(devno);                         /* SS# "H"                              */
}
/******************************************************************************
 End of function r_flash_spi_mx_init_port
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_reset_port
* Description  : Resets the ports related to the specified device.
* Arguments    : uint8_t           devno                ;   Device No. (FLASH_SPI_DEVn)
* Return Value : None
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
void r_flash_spi_mx_reset_port(uint8_t devno)
{
    r_flash_spi_cs_reset(devno);                        /* SS# "H"                              */
}
/******************************************************************************
 End of function r_flash_spi_mx_reset_port
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_send_cmd
* Description  : Sends a FLASH command.
* Arguments    : uint8_t            cmd                   ;   Command data
*              : uint32_t           addr                  ;   Address data
*              : uint8_t            cmdsize               ;   Command size
*              : bool               read_after_write      ;   Control SPI bus
*              : bool               read_in_memory_mapped ;   Read access in memory-mapped mode
* Return Value : FLASH_SPI_SUCCESS                        ;   Successful operation
*              : FLASH_SPI_ERR_HARD                       ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                      ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_send_cmd(uint8_t devno, uint8_t cmd, uint32_t addr, uint8_t cmdsize, bool read_after_write, bool read_in_memory_mapped)
{
    flash_spi_status_t        ret = FLASH_SPI_SUCCESS;

    r_flash_spi_mx_cmd_set(devno, cmd, addr, cmdsize);
    
    /* The upper layer software should set to the single mode. */
    /* Send a command using the single mode. */
    /* Cast from 8-bit data to 32-bit data. */
    ret = r_flash_spi_drvif_tx(devno, (uint32_t)cmdsize, (uint8_t *)&s_flash_mx_cmdbuf[devno][0], read_after_write, read_in_memory_mapped);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_send_cmd
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_write_en
* Description  : Executes a Write Enable operation.
*              : Issues the WREN command and sets the WEL bit.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_write_en(uint8_t devno)
{
    flash_spi_status_t        ret = FLASH_SPI_SUCCESS;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Write Enable (WREN) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_WREN(devno, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_write_en
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_write_di
* Description  : Executes a Write Disable operation.
*              : Issues the WRDI command and clears the WEL bit.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_write_di(uint8_t devno)
{
    flash_spi_status_t        ret = FLASH_SPI_SUCCESS;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Write Disable (WRDI) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_WRDI(devno, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_write_di
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_read_stsreg
* Description  : Reads status from the status register and stores to the read status storage buffer(p_status).
*              :
*              :        Bit 7: Status register write enable/disable (SRWD)
*              :                  1: Disable writing to the status register.
*              :                  0: Enable writing to the status register.
*              :        Bit 6: Quad Enable (QE)
*              :                  1: Quad Enable (Performs Quad I/O mode and WP#, RESET# are disabled.)
*              :                  0: Not Quad Enable (Performs non-Quad I/O mode and WP#, RESET# are enabled.)
*              :        Bits 5 to 2: Block protect 3 - 0 (BP3 - BP0)
*              :                  Set to 1, a designated memory area is protected from PROGRAM and ERASE operations.
*              :        Bit 1: Write enable latch (WEL)
*              :                  1: Internal Write Enable Latch is set.
*              :                  0: Internal Write Enable Latch is reset.
*              :        Bit 0: Write in progress (WIP)
*              :                  1: Program or Erase cycle is in progress.
*              :                  0: No Program or Erase cycle is in progress.
*              :
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : uint8_t          * p_status            ;   Read status storage buffer (1 byte)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_read_stsreg(uint8_t devno, uint8_t * p_status)
{
    flash_spi_status_t        ret = FLASH_SPI_SUCCESS;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Status Register (RDSR) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_RDSR(devno, TRUE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_R_ACCESS);

    /* Receive data from the status register using the single mode. */
    ret = r_flash_spi_drvif_rx(devno, FLASH_SPI_MX_STSREG_SIZE, p_status);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_read_stsreg
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_read_configreg
* Description  : Reads status from the configuration register and stores to
*              : the configuration storage buffer (p_config).
*              :
*              :      <config1>
*              :    Configuration Register - 1 (For MX25L, MX66L, MX25R and MX25U)
*              :        Bits 7 to 6: DC1-DC0 (Dummy cycle)
*              :                  See the specification of the Flash memory.
*              :        Bit 5: 4 BYTE (4BYTE Indicator)
*              :                  1: 4-byte address mode
*              :                  0: 3-byte address mode
*              :        Bit 4: PBE (Preamble bit Enable)
*              :                  1: Bottom area protect
*              :                  0: Top area protect
*              :        Bit 3: TB (Top/Bottom)
*              :                  1: Bottom area protect
*              :                  0: Top area protect
*              :        Bits 2 to 0: ODS2-ODS0 (Output driver strength)
*              :                  See the specification of the Flash memory.
*              :
*              :      <config2>
*              :    Configuration Register - 2 (For MX25R)
*              :        Bits 7 to 2: Reserved
*              :        Bit 1: L/H Switch
*              :                  1: Low power mode (default)
*              :                  0: High performance mode
*              :        Bit 0: Reserved
*              :
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
*              : uint8_t          * p_config            ;   MX25L/MX66L/MX25U : Read configuration storage buffer (1 byte)
*              :                                        ;   MX25R             : Read configuration storage buffer (2 bytes)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_read_configreg(uint8_t devno, uint8_t * p_config)
{
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Configuration Register (RDCR) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_RDCR(devno, TRUE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_R_ACCESS);

    /* Receive data from the configuration status register using the single mode. */
    ret = r_flash_spi_drvif_rx(devno, FLASH_SPI_MX_CFGREG_SIZE, p_config);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_read_configreg
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_read_scurreg
* Description  : Reads status from the security register and stores to the security storage buffer (p_scur).
*              :
*              :        Bit 7: WPSEL
*              :                  1: Inidividual mode
*              :                  0: Normal WP mode
*              :        Bit 6: E_FAIL
*              :                  1: Erase failed
*              :                  0: Erase succeed
*              :        Bit 5: P_FAIL
*              :                  1: Program failed
*              :                  0: Program succeed
*              :        Bit 4: Reserved
*              :                  
*              :        Bit 3: ESB (Erase Suspend Bit)
*              :                  1: Erase Suspended
*              :                  0: Erase is not suspended.
*              :        Bit 2: PSB (Program Suspend Bit)
*              :                  1: Program Suspended
*              :                  0: Program is not suspended.
*              :        Bit 1: LDSO (Indicate if lock-down)
*              :                  1: Lock-down (Cannot program/erase OTP)
*              :                  0: Not lock-down
*              :        Bit 0: Secured OTP indicator
*              :                  1: Factory lock
*              :                  0: Non-factory lock
*              :
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
*              : uint8_t          * p_scur              ;   Read security storage buffer (1 byte)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_read_scurreg(uint8_t devno, uint8_t * p_scur)
{
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Security Register (RDSCUR) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_RDSCUR(devno, TRUE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_R_ACCESS);

    /* Receive the Manufacture Identification, Identification and Memory capacity using the single mode. */
    ret = r_flash_spi_drvif_rx(devno, FLASH_SPI_MX_SCURREG_SIZE, p_scur);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_read_scurreg
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_set_write_protect
* Description  : Makes a write-protection setting using Block Lock (BP) protection mode.
*              : The BP3, BP2, BP1 and BP0 bit of status register are set as follows by 
*              : write-protection setting data (wpsts).
*              :
*              :    wpsts=0x00  :   BP3=0, BP2=0, BP1=0, BP0=0
*              :    wpsts=0x01  :   BP3=0, BP2=0, BP1=0, BP0=1
*              :    wpsts=0x02  :   BP3=0, BP2=0, BP1=1, BP0=0
*              :    wpsts=0x03  :   BP3=0, BP2=0, BP1=1, BP0=1
*              :    wpsts=0x04  :   BP3=0, BP2=1, BP1=0, BP0=0
*              :    wpsts=0x05  :   BP3=0, BP2=1, BP1=0, BP0=1
*              :    wpsts=0x06  :   BP3=0, BP2=1, BP1=1, BP0=0
*              :    wpsts=0x07  :   BP3=0, BP2=1, BP1=1, BP0=1
*              :    wpsts=0x08  :   BP3=1, BP2=0, BP1=0, BP0=0
*              :    wpsts=0x09  :   BP3=1, BP2=0, BP1=0, BP0=1
*              :    wpsts=0x0a  :   BP3=1, BP2=0, BP1=1, BP0=0
*              :    wpsts=0x0b  :   BP3=1, BP2=0, BP1=1, BP0=1
*              :    wpsts=0x0c  :   BP3=1, BP2=1, BP1=0, BP0=0
*              :    wpsts=0x0d  :   BP3=1, BP2=1, BP1=0, BP0=1
*              :    wpsts=0x0e  :   BP3=1, BP2=1, BP1=1, BP0=0
*              :    wpsts=0x0f  :   BP3=1, BP2=1, BP1=1, BP0=1
*              :
*              : The TB bit of configuration register is set.
*              :    TB (Top/Bottom)
*              :        1: Bottom area protect
*              :        0: Top area protect
*              :
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : uint8_t            wpsts               ;   Write-protection setting data
*              : bool               read_after_write    ;   Control SPI bus
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_PARAM                    ;   Parameter error
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_WP                       ;   Write-protection error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : A SRWD bit is fixed to 0.
*              : Please confirm the status register.
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_set_write_protect(uint8_t devno, uint8_t wpsts, bool read_after_write)
{
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;
    flash_spi_reg_info_t    reg;
    uint8_t                 stsreg = 0;
    uint8_t                 p_scur = 0;
#if   (FLASH_SPI_CFG_DEV0_MX25L == 1) || (FLASH_SPI_CFG_DEV1_MX25L == 1) || \
      (FLASH_SPI_CFG_DEV0_MX66L == 1) || (FLASH_SPI_CFG_DEV1_MX66L == 1) || \
      (FLASH_SPI_CFG_DEV0_MX25U == 1) || (FLASH_SPI_CFG_DEV1_MX25U == 1)
    uint8_t                 cfgreg[1] = { 0 };
#elif (FLASH_SPI_CFG_DEV0_MX25R == 1) || (FLASH_SPI_CFG_DEV1_MX25R == 1)
    uint8_t                 cfgreg[2] = { 0, 0 };
#endif

    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        if (wpsts > FLASH_SPI_MX_DEV0_WP_WHOLE_MEM)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return FLASH_SPI_ERR_PARAM;
        }
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        if (wpsts > FLASH_SPI_MX_DEV1_WP_WHOLE_MEM)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return FLASH_SPI_ERR_PARAM;
        }
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    /* Execute the Read Security Register (RDSCUR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_scurreg(devno, &p_scur);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* WPSEL bit = 1: Advanced Sector Protection mode  */
    /* The WPSEL bit is an OTP bit. Once WPSEL is set to 1, it cannot be programmed back to 0. */
    /* Can't use the Block Protection (BP) mode as the write protection. */
    if (FLASH_SPI_MX_SCUR_WPSEL == (p_scur & FLASH_SPI_MX_SCUR_WPSEL))
    {
        return FLASH_SPI_ERR_WP;
    }

    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Execute the Read Configuration Register (RDCR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_configreg(devno, &cfgreg[0]);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Store the write-protection information. */
    reg.status  = ((stsreg & ((uint8_t)(~(FLASH_SPI_MX_REG_BPMASK | FLASH_SPI_MX_REG_SRWD)))) | (wpsts << 2));
    reg.config1 = cfgreg[0];
#if (FLASH_SPI_CFG_DEV0_MX25R == 1) || (FLASH_SPI_CFG_DEV1_MX25R == 1)
    reg.config2 = cfgreg[1];
#endif

    /* Use the Block lock (BP) protection mode as the write protection. */
    /* Therefore set Write Protection Selection (WPSEL) to 0 (default). */
    /* Execute the Write Status Register (WRSR) command operation using the single mode. */
    /* Execute the Read Status Register (RDSR) command operation using the single mode 
       in r_flash_spi_mx_write_stsreg(). */
    ret = r_flash_spi_mx_write_stsreg(devno, &reg, read_after_write);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    
    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_set_write_protect
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_write_configuration
* Description  : Writes from the write configuration storage buffer(config1, config2) 
*              : to the configuration register.
*              :
*              :      <config1>
*              :    Configuration Register - 1 (For MX25L, MX66L, RX25R and MX25U)
*              :        Bits 7 to 6: DC1-DC0 (Dummy cycle)
*              :                  See the specification of the Flash memory.
*              :        Bit 5: 4 BYTE (4BYTE Indicator)
*              :                  1: 4-byte address mode
*              :                  0: 3-byte address mode
*              :        Bit 4: PBE (Preamble bit Enable)
*              :                  1: Bottom area protect
*              :                  0: Top area protect
*              :        Bit 3: TB (Top/Bottom)
*              :                  1: Bottom area protect
*              :                  0: Top area protect
*              :        Bits 2 to 0: ODS2-ODS0 (Output driver strength)
*              :                  See the specification of the Flash memory.
*              :
*              :      <config2>
*              :    Configuration Register - 2 (For MX25R)
*              :        Bits 7 to 2: Reserved
*              :        Bit 1: L/H Switch
*              :                  1: Low power mode (default)
*              :                  0: High performance mode
*              :        Bit 0: Reserved
*              :
* Arguments    : uint8_t         devno            ;   Device No. (FLASH_DEVn)
*              : flash_spi_reg_info_t * p_reg     ;   Flash memory register information
*              :     uint8_t     status           ;   Status register setting data
*              :     uint8_t     config1          ;   Configuration or Configuration-1 register setting data
*              :     uint8_t     config2          ;   Configuration-2 register setting data
*              :     bool        read_after_write ;   Control SPI bus
* Return Value : FLASH_SPI_SUCCESS                ;   Successful operation
*              : FLASH_SPI_ERR_PARAM              ;   Parameter error
*              : FLASH_SPI_ERR_HARD               ;   Hardware error
*              : FLASH_SPI_ERR_OTHER              ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_write_configuration(uint8_t devno, flash_spi_reg_info_t * p_reg, bool read_after_write)
{
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;

    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &p_reg->status);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Use the Block lock (BP) protection mode as the write protection. */
    /* Therefore set Write Protection Selection (WPSEL) to 0 (default). */
    /* Execute the Write Status Register (WRSR) command operation using the single mode. */
    /* Execute the Read Status Register (RDSR) command operation using the single mode 
       in r_flash_spi_mx_write_stsreg(). */
    ret = r_flash_spi_mx_write_stsreg(devno, p_reg, read_after_write);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    
    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_write_configuration
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_quad_enable
* Description  : Makes a setting using Quad Enable (QE Bit) mode.
* Arguments    : uint8_t         devno                  ;   Device No. (FLASH_SPI_DEVn)
*              : bool            read_after_write       ;   Control SPI bus
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_PARAM                    ;   Parameter error
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : A SRWD bit is fixed to 0.
*              : Please confirm the status register and configuration register after this processing.
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_quad_enable(uint8_t devno, bool read_after_write)
{
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;
    flash_spi_reg_info_t    reg;
    uint8_t                 stsreg = 0;
#if   (FLASH_SPI_CFG_DEV0_MX25L == 1) || (FLASH_SPI_CFG_DEV1_MX25L == 1) || \
      (FLASH_SPI_CFG_DEV0_MX66L == 1) || (FLASH_SPI_CFG_DEV1_MX66L == 1) || \
      (FLASH_SPI_CFG_DEV0_MX25U == 1) || (FLASH_SPI_CFG_DEV1_MX25U == 1)
    uint8_t                 cfgreg[1] = { 0 };
#elif (FLASH_SPI_CFG_DEV0_MX25R == 1) || (FLASH_SPI_CFG_DEV1_MX25R == 1)
    uint8_t                 cfgreg[2] = { 0, 0 };
#endif

    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Execute the Read Configuration Register (RDCR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_configreg(devno, &cfgreg[0]);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Store the write-protection information. */
    reg.status  = (stsreg | FLASH_SPI_MX_REG_QE);
    reg.config1 = cfgreg[0];
#if (FLASH_SPI_CFG_DEV0_MX25R == 1) || (FLASH_SPI_CFG_DEV1_MX25R == 1)
    reg.config2 = cfgreg[1];
#endif

    /* Use the Block lock (BP) protection mode as the write protection. */
    /* Therefore set Write Protection Selection (WPSEL) to 0 (default). */
    /* Execute the Write Status Register (WRSR) command operation using the single mode. */
    /* Execute the Read Status Register (RDSR) command operation using the single mode 
       in r_flash_spi_mx_write_stsreg(). */
    ret = r_flash_spi_mx_write_stsreg(devno, &reg, read_after_write);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    
    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_quad_enable
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_quad_disable
* Description  : Makes a setting using Quad Disable (QE Bit) mode.
* Arguments    : uint8_t         devno                  ;   Device No. (FLASH_SPI_DEVn)
*              : bool            read_after_write       ;   Control SPI bus
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_PARAM                    ;   Parameter error
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : A SRWD bit is fixed to 0.
*              : Please confirm the status register and configuration register after this processing.
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_quad_disable(uint8_t devno, bool read_after_write)
{
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;
    flash_spi_reg_info_t    reg;
    uint8_t                 stsreg = 0;
#if   (FLASH_SPI_CFG_DEV0_MX25L == 1) || (FLASH_SPI_CFG_DEV1_MX25L == 1) || \
      (FLASH_SPI_CFG_DEV0_MX66L == 1) || (FLASH_SPI_CFG_DEV1_MX66L == 1) || \
      (FLASH_SPI_CFG_DEV0_MX25U == 1) || (FLASH_SPI_CFG_DEV1_MX25U == 1)
    uint8_t                 cfgreg[1] = { 0 };
#elif (FLASH_SPI_CFG_DEV0_MX25R == 1) || (FLASH_SPI_CFG_DEV1_MX25R == 1)
    uint8_t                 cfgreg[2] = { 0, 0 };
#endif

    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Execute the Read Configuration Register (RDCR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_configreg(devno, &cfgreg[0]);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Store the write-protection information. */
    reg.status = (uint8_t)(stsreg & (uint8_t)~FLASH_SPI_MX_REG_QE);
    reg.config1 = cfgreg[0];
#if (FLASH_SPI_CFG_DEV0_MX25R == 1) || (FLASH_SPI_CFG_DEV1_MX25R == 1)
    reg.config2 = cfgreg[1];
#endif

    /* Use the Block lock (BP) protection mode as the write protection. */
    /* Therefore set Write Protection Selection (WPSEL) to 0 (default). */
    /* Execute the Write Status Register (WRSR) command operation using the single mode. */
    /* Execute the Read Status Register (RDSR) command operation using the single mode 
       in r_flash_spi_mx_write_stsreg(). */
    ret = r_flash_spi_mx_write_stsreg(devno, &reg, read_after_write);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    
    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_quad_disable
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_write_stsreg
* Description  : Writes status from the write status storage buffer to the status register.
*              : 
*              :      <stsreg>
*              :    Status Register
*              :        Bit 7:Status register write enable/disable (SRWD)
*              :                  1: Disable writing to the status register.
*              :                  0: Enable writing to the status register.
*              :        Bit 6: Quad Enable (QE)
*              :                  1: Quad Enable (Performs Quad I/O mode and WP#, RESET# are disabled.)
*              :                  0: Not Quad Enable (Performs non-Quad I/O mode and WP#, RESET# are enabled.)
*              :        Bits 5 to 2: Block protect 3 - 0 (BP3 - BP0)
*              :                  Set to 1, a designated memory area is protected from PROGRAM and ERASE operations.
*              :        Bit 1:Write enable latch (WEL)
*              :                  1: Internal Write Enable Latch is set.
*              :                  0: Internal Write Enable Latch is reset.
*              :        Bit 0:Write in progress (WIP)
*              :                  1: Program or Erase cycle is in progress.
*              :                  0: No Program or Erase cycle is in progress.
*              :
*              :      <config1>
*              :    Configuration Register - 1 (For MX25L, MX66L, MX25R and MX25U)
*              :        Bits 7 to 6: DC1-DC0 (Dummy cycle)
*              :                  See the specification of the Flash memory.
*              :        Bit 5: 4 BYTE (4BYTE Indicator)
*              :                  1: 4-byte address mode
*              :                  0: 3-byte address mode
*              :        Bit 4: PBE (Preamble bit Enable)
*              :                  1: Bottom area protect
*              :                  0: Top area protect
*              :        Bit 3: TB (Top/Bottom)
*              :                  1: Bottom area protect
*              :                  0: Top area protect
*              :        Bits 2 to 0: ODS2-ODS0 (Output driver strength)
*              :                  See the specification of the Flash memory.
*              :
*              :      <config2>
*              :    Configuration Register - 2 (For MX25R)
*              :        Bits 7 to 2: Reserved
*              :        Bit 1: L/H Switch
*              :                  1: Low power mode (default)
*              :                  0: High performance mode
*              :        Bit 0: Reserved
*              :
* Arguments    : uint8_t            devno         ;   Device No. (FLASH_SPI_DEVn)
*              : flash_spi_reg_info_t * p_reg     ;   Flash memory register information
*              :     uint8_t     status           ;   Status register setting data
*              :     uint8_t     config1          ;   Configuration or Configuration-1 register setting data
*              :     uint8_t     config2          ;   Configuration-2 register setting data
*              :     bool        read_after_write ;   Control SPI bus
* Return Value : FLASH_SPI_SUCCESS                ;   Successful operation
*              : FLASH_SPI_ERR_HARD               ;   Hardware error
*              : FLASH_SPI_ERR_OTHER              ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_write_stsreg(uint8_t devno, flash_spi_reg_info_t * p_reg, bool read_after_write)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t             stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t  ret = FLASH_SPI_SUCCESS;
    uint8_t             data_size = 0;
    uint8_t             data_buff[4];

    data_buff[0] = 0;
    data_buff[1] = 0;
    data_buff[2] = 0;
    data_buff[3] = 0;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* Sets configuration fixed data for writing. */
    data_buff[0] = FLASH_SPI_MX_CMD_WRSR;
    data_buff[1] = p_reg->status | FLASH_SPI_MX_REG_WEL;
    data_buff[2] = p_reg->config1;
#if (FLASH_SPI_CFG_DEV0_MX25R == 1) || (FLASH_SPI_CFG_DEV1_MX25R == 1)
    data_buff[3] = p_reg->config2;
#endif
    data_size    = FLASH_SPI_MX_CMD_SIZE + FLASH_SPI_MX_WSTSREG_SIZE;

    /* Transmit data to the status register using the single mode. */
    ret = r_flash_spi_drvif_tx(devno, data_size, &data_buff[0], read_after_write, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_mx_write_stsreg
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_read
* Description  : Reads data from the specified address (addr) for the specified number (cnt) of bytes
*              : and stores to the specified buffer (pData).
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : flash_spi_info_t * p_flash_spi_info    ;   Flash memory information
*              :    uint32_t        addr                ;   Read start address
*              :    uint32_t        cnt                 ;   Number of bytes to be read
*              :    uint32_t        data_cnt            ;   Temporary Number of bytes to be read
*              :    uint8_t       * pData               ;   Read data storage buffer pointer
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_read(uint8_t devno, flash_spi_info_t * p_flash_spi_info)
{
    flash_spi_status_t        ret = FLASH_SPI_SUCCESS;
    uint32_t    tmpcnt    = 0;
    uint8_t     addr_size = 0;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the READ command using the single mode. */
    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        addr_size = FLASH_SPI_MX_DEV0_ADDR_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        addr_size = FLASH_SPI_MX_DEV1_ADDR_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    if (FLASH_SPI_SINGLE == p_flash_spi_info->op_mode)
    {
        ret = R_FLASH_SPI_MX_CMD_FREAD(devno, p_flash_spi_info->addr, addr_size, TRUE);
    }
    else if (FLASH_SPI_DUAL == p_flash_spi_info->op_mode)
    {
        ret = R_FLASH_SPI_MX_CMD_DREAD(devno, p_flash_spi_info->addr, addr_size, TRUE);
    }
    else
    {
        ret = R_FLASH_SPI_MX_CMD_QREAD(devno, p_flash_spi_info->addr, addr_size, TRUE);
    }

    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    ret = r_flash_spi_drvif_disable(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_R_ACCESS);

    /* Set SPI mode to mode N and bit rate for Data. */
    ret = r_flash_spi_drvif_enable_rx_data(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    do
    {
        if (true == s_flash_mx_read_memory_mapped[devno])
        {
            /* Calculates the writable bytes from the start address to the bank boundary */
            tmpcnt = ((p_flash_spi_info->addr + FLASH_SPI_R_DATA_QSPIX_BANK_SIZE) / FLASH_SPI_R_DATA_QSPIX_BANK_SIZE)
                     * FLASH_SPI_R_DATA_QSPIX_BANK_SIZE - p_flash_spi_info->addr;

            /* Set data size to receive. */
            /* The data size is 64 Mbytes or less when using a read memory map in the QSPI area. */
            if (tmpcnt >= p_flash_spi_info->cnt)
            {
                p_flash_spi_info->data_cnt = p_flash_spi_info->cnt;
            }
            else
            {
                p_flash_spi_info->data_cnt = tmpcnt;
            }
        }
        else
        {
            /* Set data size to receive. */
            /* The data size is (4G - 1) bytes or less when using Firmware Integration Technology (FIT). */
            /* The data size is 32K bytes or less when not using Firmware Integration Technology (FIT). */
            if (FLASH_SPI_R_DATA_SIZE <= p_flash_spi_info->cnt)
            {
                p_flash_spi_info->data_cnt = FLASH_SPI_R_DATA_SIZE;
            }
            else
            {
                p_flash_spi_info->data_cnt = p_flash_spi_info->cnt;
            }
        }

        /* Receive data from memory array. */
        /* The lower layer software should use the data_cnt as receiving counter. */
        ret = r_flash_spi_drvif_rx_data(devno, p_flash_spi_info->data_cnt, p_flash_spi_info->p_data,
                                         p_flash_spi_info->addr, addr_size, p_flash_spi_info->op_mode);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
            r_flash_spi_set_cs(devno, FLASH_SPI_HI);    /* SS# "H"                              */
            return ret;
        }

        if (true == s_flash_mx_read_memory_mapped[devno])
        {
            r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
            r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */
        }

        p_flash_spi_info->cnt    -= p_flash_spi_info->data_cnt;     /* Updates the cnt.         */
        p_flash_spi_info->p_data += p_flash_spi_info->data_cnt;
        p_flash_spi_info->addr   += p_flash_spi_info->data_cnt;

        if ((true == s_flash_mx_read_memory_mapped[devno]) && (0 != p_flash_spi_info->cnt))
        {
            r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
            r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        }
    }
    while(0 != p_flash_spi_info->cnt); /* WAIT_LOOP */

    if (true != s_flash_mx_read_memory_mapped[devno])
    {
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */
    }

    ret = r_flash_spi_drvif_disable(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Set SPI mode to mode 3 and bit rate for Command and Data as default. */
    ret = r_flash_spi_drvif_enable(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_read
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_write_page
* Description  : Writes data from the specified buffer (pData)
*              : to the specified address (addr) for the specified number (data_cnt) of bytes.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : flash_spi_info_t * p_flash_spi_info    ;   Flash memory information
*              :    uint32_t        addr                ;   Write start address
*              :    uint32_t        cnt                 ;   Number of bytes to be written
*              :    uint32_t        data_cnt            ;   Number of bytes to be written in a page
*              :    uint8_t       * p_data              ;   Write data storage buffer pointer
*              :    bool            read_after_write_add;   Whether or not to close SPI bus cycle
*              :    bool            read_after_write_data;  Whether or not to close SPI bus cycle
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_PARAM                    ;   Parameter error
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : A write exceeding the write page isn't allowed.
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_write_page(uint8_t devno, flash_spi_info_t * p_flash_spi_info, bool read_after_write_add, bool read_after_write_data)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t             stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t  ret = FLASH_SPI_SUCCESS;
    uint8_t             addr_size = 0;
    uint8_t           * p_cmdbuf = (uint8_t *)&s_flash_mx_cmdbuf[devno][0];

#if (BSP_CFG_PARAM_CHECKING_ENABLE)
    if (FLASH_SPI_DUAL == p_flash_spi_info->op_mode)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_PARAM;
    }
#endif /* BSP_CFG_PARAM_CHECKING_ENABLE */

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, (uint8_t *)&stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* Issue the WRITE command using the single mode. */
    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        addr_size = FLASH_SPI_MX_DEV0_ADDR_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        addr_size = FLASH_SPI_MX_DEV1_ADDR_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    if (FLASH_SPI_SINGLE == p_flash_spi_info->op_mode)
    {
        ret = R_FLASH_SPI_MX_CMD_PP(devno, p_flash_spi_info->addr, addr_size, TRUE);
    }
    else
    {
        ret = R_FLASH_SPI_MX_CMD_4PP(devno, p_flash_spi_info->addr, addr_size, TRUE);
    }

    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    /* CMD Dummy. */
    r_flash_spi_mx_cmd_set(devno, 0, p_flash_spi_info->addr, FLASH_SPI_MX_CMD_SIZE+addr_size);
    if (FLASH_SPI_SINGLE == p_flash_spi_info->op_mode)
    {
        ret = r_flash_spi_drvif_tx_add(devno, addr_size, ++p_cmdbuf, FLASH_SPI_SINGLE, read_after_write_add);
    }
    else
    {
        ret = r_flash_spi_drvif_tx_add(devno, addr_size, ++p_cmdbuf, FLASH_SPI_QUAD, read_after_write_add);
    }

    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    ret = r_flash_spi_drvif_disable(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    /* Set SPI mode to mode N and bit rate for Data. */
    ret = r_flash_spi_drvif_enable_tx_data(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    /* Transmit data to memory. */
    ret = r_flash_spi_drvif_tx_data(devno, p_flash_spi_info->data_cnt, p_flash_spi_info->p_data,
                                    p_flash_spi_info->op_mode, read_after_write_data);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    ret = r_flash_spi_drvif_disable(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Set SPI mode to mode 3 and bit rate for Command and Data as default. */
    ret = r_flash_spi_drvif_enable(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_write_page
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_flash_erase
* Description  : FLASH_MODE_S_ERASE (4KB)         ;   Erases the data of specified sector (Addr).
*              : FLASH_MODE_B32K_ERASE (32KB)     ;   Erases the data of specified block (Addr).
*              : FLASH_MODE_B64K_ERASE (64KB)     ;   Erases the data of specified block (Addr).
*              : FLASH_MODE_C_ERASE               ;   Erases the all data of specified chip (Addr).
* Arguments    : uint8_t            devno         ;   Device No. (FLASH_DEVn)
*              : flash_spi_erase_info_t * p_flash_spi_erase_info    ; Flash memory erase information
*              :    uint32_t        addr          ;   First address of specified sector
*              :    uint8_t         mode          ;   Type of erase command
*              :                                  ;   FLASH_SPI_MODE_S_ERASE     ; Sector Erase (4KB)
*              :                                  ;   FLASH_SPI_MODE_B32K_ERASE  ; Block Erase (32KB)
*              :                                  ;   FLASH_SPI_MODE_B64K_ERASE  ; Block Erase (64KB)
*              :                                  ;   FLASH_SPI_MODE_C_ERASE     ; Chip Erase
* Return Value : FLASH_SPI_SUCCESS                ;   Successful operation
*              : FLASH_SPI_ERR_PARAM              ;   Parameter error
*              : FLASH_SPI_ERR_HARD               ;   Hardware error
*              : FLASH_SPI_ERR_OTHER              ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : Flash memory can be erased to only when write-protection has been canceled.
*              : (1) Sector Erase
*              :   Data of the specified sector in the protected block (64KB) can't be erased and
*              :   error result is returned.
*              : (2) Block Erase
*              :   Data of the specified block in the protected block (64KB) can't be erased and
*              :   error result is returned.
*              : (3) Chip Erase
*              :   Data of the protected chip in the proteted block (64KB) can't be erased and
*              :   error result is returned.
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_erase(uint8_t devno, flash_spi_erase_info_t * p_flash_spi_erase_info)
{
    flash_spi_status_t     ret = FLASH_SPI_SUCCESS;
    uint32_t    mem_size = 0;
    uint8_t     addr_size = 0;
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t     stsreg = 0;                             /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        mem_size  = FLASH_SPI_MX_DEV0_MEM_SIZE;
        addr_size = FLASH_SPI_MX_DEV0_ADDR_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        mem_size  = FLASH_SPI_MX_DEV1_MEM_SIZE;
        addr_size = FLASH_SPI_MX_DEV1_ADDR_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    if (mem_size <= p_flash_spi_erase_info->addr)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_PARAM;
    }

#if (BSP_CFG_PARAM_CHECKING_ENABLE)
    if ((FLASH_SPI_MODE_S_ERASE    != p_flash_spi_erase_info->mode) &&
        (FLASH_SPI_MODE_B32K_ERASE != p_flash_spi_erase_info->mode) &&
        (FLASH_SPI_MODE_B64K_ERASE != p_flash_spi_erase_info->mode) &&
        (FLASH_SPI_MODE_C_ERASE    != p_flash_spi_erase_info->mode))
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_PARAM;
    }
#endif /* BSP_CFG_PARAM_CHECKING_ENABLE */

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, (uint8_t *)&stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* Issue the Erase command using the single mode. */
    /* The upper layer software should check and set the mode correctly to "p_flash_spi_erase_info->mode". */ 
    if (FLASH_SPI_MODE_S_ERASE == p_flash_spi_erase_info->mode)
    {
        if (FLASH_SPI_DEV0 == devno)
        {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
            p_flash_spi_erase_info->addr &= FLASH_SPI_MX_DEV0_SECT_ADDR;
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
        }
        else
        {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
            p_flash_spi_erase_info->addr &= FLASH_SPI_MX_DEV1_SECT_ADDR;
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
        }
        ret = R_FLASH_SPI_MX_CMD_SE(devno, p_flash_spi_erase_info->addr, addr_size, FALSE);
    }
    else if (FLASH_SPI_MODE_B32K_ERASE == p_flash_spi_erase_info->mode)
    {
        if (FLASH_SPI_DEV0 == devno)
        {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
            p_flash_spi_erase_info->addr &= FLASH_SPI_MX_DEV0_B32K_ADDR;
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
        }
        else
        {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
            p_flash_spi_erase_info->addr &= FLASH_SPI_MX_DEV1_B32K_ADDR;
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
        }
        ret = R_FLASH_SPI_MX_CMD_BE32K(devno, p_flash_spi_erase_info->addr, addr_size, FALSE);
    }
    else if (FLASH_SPI_MODE_B64K_ERASE == p_flash_spi_erase_info->mode)
    {
        if (FLASH_SPI_DEV0 == devno)
        {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
            p_flash_spi_erase_info->addr &= FLASH_SPI_MX_DEV0_B64K_ADDR;
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
        }
        else
        {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
            p_flash_spi_erase_info->addr &= FLASH_SPI_MX_DEV1_B64K_ADDR;
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
        }
        ret = R_FLASH_SPI_MX_CMD_BE64K(devno, p_flash_spi_erase_info->addr, addr_size, FALSE);
    }
    else
    {
        p_flash_spi_erase_info->addr &= 0x00000000;
        ret = R_FLASH_SPI_MX_CMD_CE(devno, p_flash_spi_erase_info->addr, FALSE);
    }

    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_erase
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_rdid
* Description  : Reads Manufacture ID, Device ID.
*              : ID data of 3 bytes are stored in the following order.
*              :        (1) Manufacturer ID - 1 byte
*              :        (2) Device ID - 2 bytes
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
*              : uint8_t          * p_data              ;   ID data storage buffer pointer (3 bytes)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_rdid(uint8_t devno, uint8_t * p_data)
{
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Configuration Register (RDCR) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_RDID(devno, TRUE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_R_ACCESS);

    /* Receive the Manufacture Identification, Identification and Memory capacity using the single mode. */
    ret = r_flash_spi_drvif_rx(devno, FLASH_SPI_MX_IDDATA_SIZE, p_data);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_rdid
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_polling
* Description  : Checks busy for the Page Program, Erase and Write Status Register command operation.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : flash_spi_poll_mode_t  mode            ;   Mode of error check
*              :                                        ;   FLASH_SPI_MODE_REG_WRITE_POLL
*              :                                        ;   FLASH_SPI_MODE_PROG_POLL
*              :                                        ;   FLASH_SPI_MODE_ERASE_POLL
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation (FLASH is ready)
*              : FLASH_SPI_SUCCESS_BUSY                 ;   Successful operation (FLASH is busy)
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_polling(uint8_t devno, flash_spi_poll_mode_t mode)
{
    flash_spi_status_t  ret = FLASH_SPI_SUCCESS;

    /* Checks mode of wait operation. */
    if ((FLASH_SPI_MODE_PROG_POLL == mode) || (FLASH_SPI_MODE_ERASE_POLL == mode))
    {
        /* Wait until the ready using single mode for the Page Program or Erase command operation. */
        ret = r_flash_spi_mx_poll_prog_erase(devno, mode);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            r_flash_spi_drvif_disable(devno);
            return ret;
        }
    }
    else
    {
        /* Wait until the ready using single mode for the Write Status Register (WRSR) command operation. */
        ret = r_flash_spi_mx_poll_reg_write(devno);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            r_flash_spi_drvif_disable(devno);
            return ret;
        }
    }

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_polling
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_poll_prog_erase
* Description  : Waits for the ready after busy.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
*              : flash_spi_poll_mode_t  mode            ;   Mode of error check
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation (FLASH is ready)
*              : FLASH_SPI_SUCCESS_BUSY                 ;   Successful operation (FLASH is busy)
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : If uses "Delay Task", minimum uint is 1ms.
*              : This is for the Write Status Register (WRSR) command.
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_poll_prog_erase(uint8_t devno, flash_spi_poll_mode_t mode)
{
    flash_spi_status_t  ret = FLASH_SPI_SUCCESS;
    uint8_t             rxbuf     = 0;          /* Receive temp buffer for Status Register      */
    uint8_t             rxbuf_scur = 0;         /* Receive temp buffer for Security Register    */

    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, (uint8_t *)&rxbuf);
    if (FLASH_SPI_SUCCESS == ret)
    {
        /* Ready/Busy check */
        if (0x00 == (rxbuf & FLASH_SPI_MX_REG_WIP))
        {
            ret = r_flash_spi_mx_read_scurreg(devno, &rxbuf_scur);
            if (FLASH_SPI_SUCCESS == ret)
            {
                if (FLASH_SPI_MODE_PROG_POLL == mode)
                {
                    /* Other error check */
                    if (0x00 != (rxbuf_scur & FLASH_SPI_MX_SCUR_P_FAIL))
                    {
                        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                        return FLASH_SPI_ERR_OTHER;
                    }
                }
                else
                {
                    /* Other error check */
                    if (0x00 != (rxbuf_scur & FLASH_SPI_MX_SCUR_E_FAIL))
                    {
                        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                        return FLASH_SPI_ERR_OTHER;
                    }
                }
                ret = FLASH_SPI_SUCCESS;                /* Ready                               */
            }
        }
        else
        {
            ret = FLASH_SPI_SUCCESS_BUSY;               /* Busy                                */
        }
    }
    else
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_poll_prog_erase
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_poll_reg_write
* Description  : Waits for the ready after busy.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation (Flash memory is ready)
*              : FLASH_SPI_SUCCESS_BUSY                 ;   Successful operation (Flash memory is busy)
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : If uses "Delay Task", minimum uint is 1ms.
*              : This is for the Write Status Register (WRSR) command.
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_poll_reg_write(uint8_t devno)
{
    flash_spi_status_t  ret = FLASH_SPI_SUCCESS;
    uint8_t             rxbuf = 0;              /* Receive temp buffer for Status Register      */

    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, (uint8_t *)&rxbuf);
    if (FLASH_SPI_SUCCESS == ret)
    {
        /* Ready/Busy check */
        if (0x00 == (rxbuf & FLASH_SPI_MX_REG_WIP))
        {
            ret = FLASH_SPI_SUCCESS;                   /* Ready                                */
        }
        else
        {
            ret = FLASH_SPI_SUCCESS_BUSY;              /* Busy                                 */
        }
    }
    else
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_poll_reg_write
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_cmd_set
* Description  : Command and address setting.
*              : Converts little endian data or big endian data.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : uint8_t            cmd                 ;   Command data
*              : uint32_t           addr                ;   Address data
*              : uint8_t            cmdsize             ;   Command size
* Return Value : None
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static void r_flash_spi_mx_cmd_set(uint8_t devno, uint8_t cmd, uint32_t addr, uint8_t cmdsize)
{
    flash_spi_mx_exchg_long_t     tmp;
    uint8_t     * p_cmdbuf = (uint8_t *)&s_flash_mx_cmdbuf[devno][0];
    uint8_t     addr_size = 0;

    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        addr_size = FLASH_SPI_MX_DEV0_ADDR_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        addr_size = FLASH_SPI_MX_DEV1_ADDR_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    tmp.ul = addr;

    if (FLASH_SPI_MX_CMD_SIZE == cmdsize)
    {
        *p_cmdbuf = cmd;
    }
    else if (4 == cmdsize)
    {
#if (FLASH_SPI_LITTLE_ENDIAN)
        *p_cmdbuf++ = cmd;
        *p_cmdbuf++ = tmp.uc[2];
        *p_cmdbuf++ = tmp.uc[1];
        *p_cmdbuf   = tmp.uc[0];
#else
        *p_cmdbuf++ = cmd;
        *p_cmdbuf++ = tmp.uc[1];
        *p_cmdbuf++ = tmp.uc[2];
        *p_cmdbuf   = tmp.uc[3];
#endif  /* #if (FLASH_SPI_LITTLE_ENDIAN) */
    }
    else if (5 == cmdsize)
    {
#if (FLASH_SPI_LITTLE_ENDIAN)
        if (3 == addr_size)
        {
            if ((FLASH_SPI_MX_CMD_RDSPB == cmd) || (FLASH_SPI_MX_CMD_WRSPB == cmd))
            {
                *p_cmdbuf++ = cmd;
                *p_cmdbuf++ = 0xFF;
                *p_cmdbuf++ = tmp.uc[2];
                *p_cmdbuf++ = tmp.uc[1];
                *p_cmdbuf   = tmp.uc[0];
            }
            else
            {
                *p_cmdbuf++ = cmd;
                *p_cmdbuf++ = tmp.uc[2];
                *p_cmdbuf++ = tmp.uc[1];
                *p_cmdbuf++ = tmp.uc[0];
                *p_cmdbuf   = 0xFF;
            }
        }
        else
        {
            *p_cmdbuf++ = cmd;
            *p_cmdbuf++ = tmp.uc[3];
            *p_cmdbuf++ = tmp.uc[2];
            *p_cmdbuf++ = tmp.uc[1];
            *p_cmdbuf   = tmp.uc[0];
        }
#else
        if (3 == addr_size)
        {
            if ((FLASH_SPI_MX_CMD_RDSPB == cmd) || (FLASH_SPI_MX_CMD_WRSPB == cmd))
            {
                *p_cmdbuf++ = cmd;
                *p_cmdbuf++ = 0xFF;
                *p_cmdbuf++ = tmp.uc[1];
                *p_cmdbuf++ = tmp.uc[2];
                *p_cmdbuf   = tmp.uc[3];
            }
            else
            {
                *p_cmdbuf++ = cmd;
                *p_cmdbuf++ = tmp.uc[1];
                *p_cmdbuf++ = tmp.uc[2];
                *p_cmdbuf++ = tmp.uc[3];
                *p_cmdbuf   = 0xFF;
            }

        }
        else
        {
            *p_cmdbuf++ = cmd;
            *p_cmdbuf++ = tmp.uc[0];
            *p_cmdbuf++ = tmp.uc[1];
            *p_cmdbuf++ = tmp.uc[2];
            *p_cmdbuf   = tmp.uc[3];
        }
#endif  /* #if (FLASH_SPI_LITTLE_ENDIAN) */
    }   
    else
    {
#if (FLASH_SPI_LITTLE_ENDIAN)
        *p_cmdbuf++ = cmd;
        *p_cmdbuf++ = tmp.uc[3];
        *p_cmdbuf++ = tmp.uc[2];
        *p_cmdbuf++ = tmp.uc[1];
        *p_cmdbuf++ = tmp.uc[0];
        *p_cmdbuf   = 0xFF;
#else
        *p_cmdbuf++ = cmd;
        *p_cmdbuf++ = tmp.uc[0];
        *p_cmdbuf++ = tmp.uc[1];
        *p_cmdbuf++ = tmp.uc[2];
        *p_cmdbuf++ = tmp.uc[3];
        *p_cmdbuf   = 0xFF;
#endif  /* #if (FLASH_SPI_LITTLE_ENDIAN) */
    }
}
/******************************************************************************
 End of function r_flash_spi_mx_cmd_set
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_enter_4addr
* Description  : Sets current addressing mode in 4-byte address mode.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_enter_4addr(uint8_t devno)
{
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;


#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
    if (FLASH_SPI_MODE_4BYTE == FLASH_SPI_MX_DEV0_ADDR_MODE)
#endif /* (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
    if (FLASH_SPI_MODE_4BYTE == FLASH_SPI_MX_DEV1_ADDR_MODE)
#endif /* (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    {
        r_flash_spi_set_cs(devno, FLASH_SPI_LOW);       /* SS# "L"                              */
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

        /* Issue the Enter 4-byte Address Mode command using the single mode. */
        ret = R_FLASH_SPI_MX_CMD_ENTER4(devno, FALSE);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
            r_flash_spi_set_cs(devno, FLASH_SPI_HI);    /* SS# "H"                              */
            return ret;
        }
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
    }

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_enter_4addr
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_get_memory_info
* Description  : Gets the memory size and page size.
* Arguments    : uint8_t               devno                ;   Device No. (FLASH_SPI_DEVn)
*              : flash_spi_mem_info_t * p_flash_spi_mem_info;   Flash memory size information
*              :    uint32_t            mem_size            ;   Max memory size
*              :    uint32_t            wpag_size           ;   Write page size
* Return Value : FLASH_SPI_SUCCESS                          ;   Successful operation
*              : FLASH_SPI_ERR_PARAM                        ;   Parameter error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_get_memory_info(uint8_t devno, flash_spi_mem_info_t * p_flash_spi_mem_info)
{
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;

    /* Get memory information. */
    switch (devno)
    {
        case FLASH_SPI_DEV0:
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
            p_flash_spi_mem_info->mem_size  = FLASH_SPI_MX_DEV0_MEM_SIZE;
            p_flash_spi_mem_info->wpag_size = FLASH_SPI_MX_DEV0_PAGE_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
            break;
        case FLASH_SPI_DEV1:
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
            p_flash_spi_mem_info->mem_size  = FLASH_SPI_MX_DEV1_MEM_SIZE;
            p_flash_spi_mem_info->wpag_size = FLASH_SPI_MX_DEV1_PAGE_SIZE;
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
            break;
        default:

            /* Do nothing. */
            break;
    }
    
    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_get_memory_info
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_check_cnt
* Description  : Checks counter.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : flash_spi_info_t * p_flash_spi_info    ;   Flash memory information
*              :    uint32_t        addr                ;   Read start address
*              :    uint32_t        cnt                 ;   Number of bytes to be read
*              :    uint32_t        data_cnt            ;   Not used
*              :    uint8_t       * p_data              ;   Read data storage buffer pointer
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_PARAM                    ;   Parameter error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_check_cnt(uint8_t devno, flash_spi_info_t * p_flash_spi_info)
{
    switch (devno)
    {
        case FLASH_SPI_DEV0:
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
            if ((0 == p_flash_spi_info->cnt) || (FLASH_SPI_MX_DEV0_MEM_SIZE < p_flash_spi_info->cnt) ||
                ((FLASH_SPI_MX_DEV0_MEM_SIZE - p_flash_spi_info->cnt) < p_flash_spi_info->addr))
            {
                R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                return FLASH_SPI_ERR_PARAM;
            }
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
            break;
        case FLASH_SPI_DEV1:
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
            if ((0 == p_flash_spi_info->cnt) || (FLASH_SPI_MX_DEV1_MEM_SIZE < p_flash_spi_info->cnt) ||
                ((FLASH_SPI_MX_DEV1_MEM_SIZE - p_flash_spi_info->cnt) < p_flash_spi_info->addr))
            {
                R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                return FLASH_SPI_ERR_PARAM;
            }
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
            break;
        default:
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return FLASH_SPI_ERR_PARAM;
            break;
    }
    return FLASH_SPI_SUCCESS;
}
/******************************************************************************
 End of function r_flash_spi_mx_check_cnt
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_page_calc
* Description  : Calculates the writable bytes from the start address to the page boundary.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : flash_spi_info_t * p_flash_spi_info    ;   Flash memory information
*              :    uint32_t        addr                ;   Read start address
*              :    uint32_t        cnt                 ;   Number of bytes to be read
*              :    uint32_t        data_cnt            ;   Not used
*              :    uint8_t       * p_data              ;   Read data storage buffer pointer
* Return Value : Writable size (bytes)
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
uint32_t r_flash_spi_mx_page_calc(uint8_t devno, flash_spi_info_t   * p_flash_spi_info)
{
    uint32_t    tmpcnt = 0;

    switch (devno)
    {
        case FLASH_SPI_DEV0:
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
            tmpcnt = ((p_flash_spi_info->addr + FLASH_SPI_MX_DEV0_PAGE_SIZE) / FLASH_SPI_MX_DEV0_PAGE_SIZE)
                     * FLASH_SPI_MX_DEV0_PAGE_SIZE - p_flash_spi_info->addr;
#endif  /* #if (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
            break;
        case FLASH_SPI_DEV1:
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
            tmpcnt = ((p_flash_spi_info->addr + FLASH_SPI_MX_DEV1_PAGE_SIZE) / FLASH_SPI_MX_DEV1_PAGE_SIZE)
                     * FLASH_SPI_MX_DEV1_PAGE_SIZE - p_flash_spi_info->addr;
#endif  /* #if (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
            break;
        default:

            /* Do nothing. */
            break;
    }
    return tmpcnt;
}
/******************************************************************************
 End of function r_flash_spi_mx_page_calc
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_set_write_protect_advanced_sector
* Description  : Makes a write-protection setting using Advanced sector protection mode.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_PARAM                    ;   Parameter error
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*              : FLASH_SPI_ERR_WP_ADVANCED              ;   Advanced write-protection error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_set_write_protect_advanced_sector(uint8_t devno, flash_spi_protect_sector_info_t * flash_spi_protect_sector_info)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t            stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;
    uint32_t           flash_type = 0;
    uint8_t            p_spblkreg = 0;
    uint8_t            p_lkreg[2] = { 0, 0 };
    uint8_t            p_spbreg = 0;
    uint8_t            p_scur = 0;

    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV0_TYPE;
#endif /* (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV1_TYPE;
#endif /* (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    /* Execute the Read Security Register (RDSCUR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_scurreg(devno, &p_scur);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Set WPSEL bit = 1: Advanced Sector Protection mode  */
    /* The WPSEL bit is an OTP bit. Once WPSEL is set to 1, it cannot be programmed back to 0. */
    if (FLASH_SPI_MX_SCUR_WPSEL != (p_scur & FLASH_SPI_MX_SCUR_WPSEL))
    {
        /* Execute the Write Protect Selection (WPSEL) command operation using the single mode. */
        ret = r_flash_spi_mx_set_write_protect_selection(devno);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return ret;
        }

        /* Execute the Gang Block Unlock (GBULK) command operation using the single mode. */
        ret = r_flash_spi_mx_gang_block_unlock(devno);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return ret;
        }
    }

    /* Individual protect */
    if (FLASH_SPI_MODE_INDIVIDUAL_PROTECT == flash_spi_protect_sector_info->protect_mode)
    {
        if (FLASH_SPI_TYPE_MX66L == flash_type)
        {
            /* Execute the Read Lock Register (RDLR) command operation using the single mode. */
            ret = r_flash_spi_mx_read_lkreg(devno, &p_lkreg[0]);
            if (FLASH_SPI_SUCCESS > ret)
            {
                R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                return ret;
            }

            /* Solid Protection Mode Not Enable */
            /* Solid Protection Mode Lock Bit = 1 */
            if (FLASH_SPI_MX_LKR_SPBE != p_lkreg[0])
            {
                /* Enable Solid Protection Mode */
                /* Set Solid Protection Mode Lock Bit = 0 */
                /* Execute the Write Lock Register (WRLR) command operation using the single mode. */
                ret = r_flash_spi_mx_write_lkreg(devno);
                if (FLASH_SPI_SUCCESS > ret)
                {
                    R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                    return ret;
                }
            }
        }

        /* Execute the Read SPB Register (RDSPB) command operation using the single mode. */
        ret = r_flash_spi_mx_read_spbreg(devno, flash_spi_protect_sector_info->addr, &p_spbreg);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return ret;
        }

        /* SPB = FFh: Protect Sector/Block  */
        if (0xFF == p_spbreg)
        {
            return FLASH_SPI_SUCCESS;
        }

        if (FLASH_SPI_TYPE_MX66L == flash_type)
        {
            /* Execute the Read SPB Lock Register (RDSPBLK) command operation using the single mode. */
            ret = r_flash_spi_mx_read_spblkreg(devno, &p_spblkreg);
            if (FLASH_SPI_SUCCESS > ret)
            {
                R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                return ret;
            }

            /* SPBLK bit = 0: SPBs protected  */
            /* Protect failed, need to manual reset flash chip */
            if (FLASH_SPI_MX_SPBLKR_SPBLK == p_spblkreg)
            {
                R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                return FLASH_SPI_ERR_WP_ADVANCED;
            }
        }
        else
        {
            /* Execute the Read Lock Register (RDLR) command operation using the single mode. */
            ret = r_flash_spi_mx_read_lkreg(devno, &p_lkreg[0]);
            if (FLASH_SPI_SUCCESS > ret)
            {
                R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                return ret;
            }

            /* SPBLKDN bit = 0: SPBs protected */
            /* Protect failed, need to manual reset flash chip */
            if (FLASH_SPI_MX_LKR_SPBLKDN == p_lkreg[0])
            {
                R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                return FLASH_SPI_ERR_WP_ADVANCED;
            }
        }

        /* Set Protect Sector/Block */
        /* Set Solid Protection Bit = 0xFF */
        /* Execute the Write SPB Register (WRSPB) command operation using the single mode. */
        ret = r_flash_spi_mx_write_spbreg(devno, flash_spi_protect_sector_info->addr);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return ret;
        }

        if (true == flash_spi_protect_sector_info->lock_protect_enable)
        {
            if (FLASH_SPI_TYPE_MX66L == flash_type)
            {
                /* Execute the Write SPB Lock Register (SPBLK) command operation using the single mode. */
                ret = r_flash_spi_mx_write_spblkreg(devno);
                if (FLASH_SPI_SUCCESS > ret)
                {
                    R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                    return ret;
                }
            }
            else
            {
                /* Execute the Write Lock Register (WRLR) command operation using the single mode. */
                ret = r_flash_spi_mx_write_lkreg(devno);
                if (FLASH_SPI_SUCCESS > ret)
                {
                    R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
                    return ret;
                }
            }
        }
    }
    else if (FLASH_SPI_MODE_ALL_PROTECT == flash_spi_protect_sector_info->protect_mode) /* All protect */
    {
        /* Execute the Gang Block Lock (GBLK) command operation using the single mode. */
        ret = r_flash_spi_mx_gang_block_lock(devno);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return ret;
        }
    }

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_set_write_protect_advanced_sector
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_erase_write_protect_advanced_sector
* Description  : Makes erase advanced write-protection setting.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*              : FLASH_SPI_ERR_WP_ADVANCED              ;   Advanced write-protection error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
flash_spi_status_t r_flash_spi_mx_erase_write_protect_advanced_sector(uint8_t devno)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t            stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;
    uint32_t           flash_type = 0;
    uint8_t            p_spblkreg = 0;
    uint8_t            p_lkreg[2] = { 0, 0 };
    uint8_t            p_scur = 0;

    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV0_TYPE;
#endif /* (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV1_TYPE;
#endif /* (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    /* Execute the Read Security Register (RDSCUR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_scurreg(devno, &p_scur);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Set WPSEL bit = 1: Advanced Sector Protection mode  */
    /* The WPSEL bit is an OTP bit. Once WPSEL is set to 1, it cannot be programmed back to 0. */
    if (FLASH_SPI_MX_SCUR_WPSEL != (p_scur & FLASH_SPI_MX_SCUR_WPSEL))
    {
        /* Execute the Write Protect Selection (WPSEL) command operation using the single mode. */
        ret = r_flash_spi_mx_set_write_protect_selection(devno);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return ret;
        }
    }

    if (FLASH_SPI_TYPE_MX66L == flash_type)
    {
        /* Execute the Read SPB Lock Register (RDSPBLK) command operation using the single mode. */
        ret = r_flash_spi_mx_read_spblkreg(devno, &p_spblkreg);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return ret;
        }

        /* SPBLK bit = 0: SPBs protected  */
        /* Protect failed, need to manual reset flash chip */
        if (FLASH_SPI_MX_SPBLKR_SPBLK == p_spblkreg)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return FLASH_SPI_ERR_WP_ADVANCED;
        }
    }
    else
    {
        /* Execute the Read Lock Register (RDLR) command operation using the single mode. */
        ret = r_flash_spi_mx_read_lkreg(devno, &p_lkreg[0]);
        if (FLASH_SPI_SUCCESS > ret)
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return ret;
        }

        /* SPBLKDN bit = 0: SPBs protected */
        /* Protect failed, need to manual reset flash chip */
        if (FLASH_SPI_MX_LKR_SPBLKDN == p_lkreg[0])
        {
            R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
            return FLASH_SPI_ERR_WP_ADVANCED;
        }
    }

    /* Execute the Gang Block Unlock (GBULK) command operation using the single mode. */
    ret = r_flash_spi_mx_gang_block_unlock(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    /* Execute the Erase SPB Register (ESSPB) command operation using the single mode. */
    ret = r_flash_spi_mx_erase_spbreg(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_erase_write_protect_advanced_sector
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_gang_block_unlock
* Description  : Executes clear all DPB bits at once.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_gang_block_unlock(uint8_t devno)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t             stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t        ret = FLASH_SPI_SUCCESS;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Gang Block Unlock (GBULK) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_GBULK(devno, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_gang_block_unlock
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_gang_block_lock
* Description  : Executes set all DPB bits at once.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_gang_block_lock(uint8_t devno)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t             stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t        ret = FLASH_SPI_SUCCESS;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Gang Block Lock (GBLK) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_GBLK(devno, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_gang_block_lock
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_set_write_protect_selection
* Description  : The WPSEL command is used to set WPSEL = 1.
*              : Advanced Sector Protection mode is enabled and BP mode is disabled.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_PARAM                    ;   Parameter error
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : The WPSEL bit is an OTP bit. Once WPSEL is set to 1, it cannot be programmed back to 0.
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_set_write_protect_selection(uint8_t devno)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t             stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t  ret = FLASH_SPI_SUCCESS;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Write Protect Selection (WPSEL) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_WPSEL(devno, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_set_write_protect_selection
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_read_lkreg
* Description  : Reads status from the lock register and stores to the lock register storage buffer (p_lkreg).
*              :
*              :    Lock Register (For MX66L)
*              :        Bits 15 to 3: Reserved
*              :        Bit 2: Password Protection Mode Lock Bit (Default = 1)
*              :                  1: Password Protection Mode not enable
*              :                  0: Password Protection Mode Enable
*              :        Bit 1: Solid Protection Mode Lock Bit (Default = 1)
*              :                  1: Solid Protection Mode not enable
*              :                  0: Solid Protection Mode Enable
*              :        Bit 0: Reserved
*              :
*              :    Lock Register (For MX25U)
*              :        Bits 15 to 7: Reserved
*              :        Bit 6: SPB Lock Down (Default = 1)
*              :                  1: SPB changeable
*              :                  0: freeze SPB
*              :        Bits 5 to 0: Reserved
*              :
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
*              : uint8_t          * p_lkreg             ;   Lock register storage buffer
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_read_lkreg (uint8_t devno, uint8_t * p_lkreg)
{
    flash_spi_status_t        ret = FLASH_SPI_SUCCESS;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Lock Register (RDLR) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_RDLR(devno, TRUE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_R_ACCESS);

    /* Receive data from the status register using the single mode. */
    ret = r_flash_spi_drvif_rx(devno, FLASH_SPI_MX_LKREG_SIZE, p_lkreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_read_lkreg
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_write_lkreg
* Description  : Executes a Write Lock Register operation (for MX66L and MX25U).
*              : Issues the WRLR command and sets the Lock Register.
*              :
*              :    Lock Register (For MX66L)
*              :        Bits 15 to 3: Reserved
*              :        Bit 2: Password Protection Mode Lock Bit (Default = 1)
*              :                  1: Password Protection Mode not enable
*              :                  0: Password Protection Mode Enable
*              :        Bit 1: Solid Protection Mode Lock Bit (Default = 1)
*              :                  1: Solid Protection Mode not enable
*              :                  0: Solid Protection Mode Enable
*              :        Bit 0: Reserved
*              :
*              :    Lock Register (For MX25U)
*              :        Bits 15 to 7: Reserved
*              :        Bit 6: SPB Lock Down (Default = 1)
*              :                  1: SPB changeable
*              :                  0: freeze SPB
*              :        Bits 5 to 0: Reserved
*              :
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_write_lkreg(uint8_t devno)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t             stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t  ret = FLASH_SPI_SUCCESS;
    uint32_t            flash_type = 0;
    uint8_t             data_size = 0;
    uint8_t             data_buff[3];

    data_buff[0] = 0;
    data_buff[1] = 0;
    data_buff[2] = 0;

    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV0_TYPE;
#endif /* (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV1_TYPE;
#endif /* (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* Sets configuration fixed data for writing. */
    data_buff[0] = FLASH_SPI_MX_CMD_WRLR;

    if (FLASH_SPI_TYPE_MX66L == flash_type)
    {
        /* Solid Protection Mode Enable */
        data_buff[1] = FLASH_SPI_MX_LKR_SPBE;
        data_buff[2] = 0xff;
    }
    else
    {
        /* SPB Lock Down */
        data_buff[1] = FLASH_SPI_MX_LKR_SPBLKDN;
        data_buff[2] = 0xff;
    }

    data_size    = FLASH_SPI_MX_CMD_SIZE + FLASH_SPI_MX_LKREG_SIZE;
    /* Transmit data to the lock register using the single mode. */
    ret = r_flash_spi_drvif_tx(devno, data_size, &data_buff[0], FALSE, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_write_lkreg
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_read_spblkreg
* Description  : Reads status from the spb lock register and stores to the spb lock register storage buffer (p_spblkreg).
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_read_spblkreg(uint8_t devno, uint8_t * p_spblkreg)
{
    flash_spi_status_t  ret = FLASH_SPI_SUCCESS;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Read SPB Lock Register (RDSPBLK) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_RDSPBLK(devno, TRUE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_R_ACCESS);

    /* Receive data from the status register using the single mode. */
    ret = r_flash_spi_drvif_rx(devno, FLASH_SPI_MX_SPBLKREG_SIZE, p_spblkreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_read_spb_lock_bit
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_write_spblkreg
* Description  : Set SPB Lock Register (for MX66L) operation.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_write_spblkreg(uint8_t devno)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t             stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t  ret = FLASH_SPI_SUCCESS;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the SPB Lock Bit Set (SPBLK) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_SPBLK(devno, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_write_spblkreg
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_erase_spbreg
* Description  : Executes clear all SPB bits at once.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_erase_spbreg(uint8_t devno)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t             stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t        ret = FLASH_SPI_SUCCESS;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    /* The upper layer software should set to the single mode. */
    /* Issue the Erase SPB Register (ESSPB) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_ESSPB(devno, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_erase_spbreg
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_read_spbreg
* Description  : Reads status from the spb register at address setting and stores to the spb register storage buffer (p_spbreg).
*              :
*              :        Bits 7 to 0: SPB (Solid Protection Bit)
*              :                00h = Unprotect Sector / Block
*              :                FFh = Protect Sector / Block
*              :
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : uint8_t            addr                ;   Address to issue a command
*              : uint8_t            p_spbreg            ;   SPB register storage buffer
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_read_spbreg(uint8_t devno, uint32_t addr, uint8_t * p_spbreg)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;
    uint32_t           flash_type = 0;
    uint8_t            addr_size = 0;

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV0_TYPE;
#endif /* (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV1_TYPE;
#endif /* (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    if (FLASH_SPI_TYPE_MX66L == flash_type)
    {
        addr_size = FLASH_SPI_MX_DEV0_ADDR_SIZE;
    }
    else
    {
        addr_size = FLASH_SPI_MX_DEV0_ADDR_SIZE + 1;
    }

    /* The upper layer software should set to the single mode. */
    /* Issue the Read Lock Register (RDSPB) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_RDSPB(devno, addr, addr_size, TRUE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_R_ACCESS);

    /* Receive data from the status register using the single mode. */
    ret = r_flash_spi_drvif_rx(devno, FLASH_SPI_MX_SPBREG_SIZE, p_spbreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_read_spbreg
 *****************************************************************************/

/************************************************************************************************
* Function Name: r_flash_spi_mx_write_spbreg
* Description  : Executes a Write SPB Register operation.
* Arguments    : uint8_t            devno               ;   Device No. (FLASH_SPI_DEVn)
*              : uint8_t            addr                ;   Address to issue a command
* Return Value : FLASH_SPI_SUCCESS                      ;   Successful operation
*              : FLASH_SPI_ERR_HARD                     ;   Hardware error
*              : FLASH_SPI_ERR_OTHER                    ;   Other error
*------------------------------------------------------------------------------------------------
* Notes        : None
*************************************************************************************************/
static flash_spi_status_t r_flash_spi_mx_write_spbreg(uint8_t devno, uint32_t addr)
{
#if (FLASH_SPI_CFG_WEL_CHK == 1)
    uint8_t            stsreg = 0;                     /* Status buffer                        */
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */
    flash_spi_status_t ret = FLASH_SPI_SUCCESS;
    uint32_t           flash_type = 0;
    uint8_t            addr_size = 0;

    /* The upper layer software should set to the single mode. */
    /* Execute the Write Enable (WREN) command operation using the single mode. */
    ret = r_flash_spi_mx_write_en(devno);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }

#if (FLASH_SPI_CFG_WEL_CHK == 1)
    /* Execute the Read Status Register (RDSR) command operation using the single mode. */
    ret = r_flash_spi_mx_read_stsreg(devno, &stsreg);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return ret;
    }
    if (0x00 == (stsreg & FLASH_SPI_MX_REG_WEL))        /* WEL bit =0 : In Write Disable State  */
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        return FLASH_SPI_ERR_OTHER;
    }
#endif  /* #if (FLASH_SPI_CFG_WEL_CHK == 1) */

    r_flash_spi_set_cs(devno, FLASH_SPI_LOW);           /* SS# "L"                              */
    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);

    if (FLASH_SPI_DEV0 == devno)
    {
#if (FLASH_SPI_CFG_DEV0_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV0_TYPE;
#endif /* (FLASH_SPI_CFG_DEV0_INCLUDED == 1) */
    }
    else
    {
#if (FLASH_SPI_CFG_DEV1_INCLUDED == 1)
        flash_type = FLASH_SPI_DEV1_TYPE;
#endif /* (FLASH_SPI_CFG_DEV1_INCLUDED == 1) */
    }

    if (FLASH_SPI_TYPE_MX66L == flash_type)
    {
        addr_size = FLASH_SPI_MX_DEV0_ADDR_SIZE;
    }
    else
    {
        addr_size = FLASH_SPI_MX_DEV0_ADDR_SIZE + 1;
    }

    /* The upper layer software should set to the single mode. */
    /* Issue the Write SPB Register (WRSPB) command using the single mode. */
    ret = R_FLASH_SPI_MX_CMD_WRSPB(devno, addr, addr_size, FALSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        R_FLASH_SPI_Log_Func(FLASH_SPI_DEBUG_ERR_ID, (uint32_t)FLASH_SPI_TYPE_SUB, __LINE__);
        r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
        r_flash_spi_set_cs(devno, FLASH_SPI_HI);        /* SS# "H"                              */
        return ret;
    }

    r_flash_spi_wait_lp(FLASH_SPI_T_CS_HOLD);
    r_flash_spi_set_cs(devno, FLASH_SPI_HI);            /* SS# "H"                              */

    return ret;
}
/******************************************************************************
 End of function r_flash_spi_mx_write_spbreg
 *****************************************************************************/

#endif /* FLASH_SPI_CFG_DEV0_MX25L == 1 || FLASH_SPI_CFG_DEV0_MX66L == 1 || FLASH_SPI_CFG_DEV0_MX25R == 1 || FLASH_SPI_CFG_DEV0_MX25U == 1 || \
    FLASH_SPI_CFG_DEV1_MX25L == 1 || FLASH_SPI_CFG_DEV1_MX66L == 1 || FLASH_SPI_CFG_DEV1_MX25R == 1 || FLASH_SPI_CFG_DEV1_MX25U == 1 */

/* End of File */
