/***********************************************************************************************************************
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_tfat_drv_if_flash.c
* Description  : TFAT driver Interface for FLASH memory.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 10.06.2020 1.00    First Release
*              : 10.09.2020 2.20    Revised the processing of the flash_spi_disk_ioctl function. The value of
*                                   GET_BLOCK_SIZE is fixed to 16.
*              : 15.12.2023 2.40    Added support FLASH SPI sector size selectable.
*                                   Fixed to comply with GSCE Coding Standards Rev.6.5.0.
*              : 30.09.2024 2.60    Changed the comment of API functions to the Doxygen style.
*              : 15.03.2025 2.61    Updated disclaimer.
***********************************************************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <string.h>
#include "r_tfat_drv_if_dev.h"
#include "r_tfat_driver_rx_config.h"

#if (TFAT_SERIAL_FLASH_DRIVE_NUM > 0)
#include "ff.h"              /* TFAT define */
#include "diskio.h"              /* TFAT define */

#include "r_flash_spi_if.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
#define FLASH_WRITE_PROTECT_OPEN        (1)
#define FLASH_WRITE_PROTECT_CLOSE       (0)
#define FLASH_WRITE_PROTECT_STATUS      (0x3c)

/* Sector Erase busy timeout 200*1ms = 0.2s  */
/** SET **/
#define FLASH_SE_BUSY_WAIT              (200)
/* Page Program time out 3*1ms = 3ms */
/** SET **/
#define FLASH_PP_BUSY_WAIT              (3)
/* Write Register time out 40*1ms = 40ms */
/** SET **/
#define FLASH_WR_BUSY_WAIT              (40)
#define FLASH_BUSY                      (0x01)
#define FLASH_NO_BUSY                   (0x00)

/*  Flash SPI default configuration for TFAT usage */
#define FLASH_PAGE_SIZE                 (256)
#define FLASH_ERASE_SECTOR_SIZE         (4096)
#define FAT_SECTOR_CNT_BY_ERASE_SECTOR  (FLASH_ERASE_SECTOR_SIZE/TFAT_FLASH_SECTOR_SIZE)
#define FLASH_PAGE_CNT_BY_FAT_SECTOR    (TFAT_FLASH_SECTOR_SIZE/FLASH_PAGE_SIZE)

#define BIT_PER_BYTE_SHIFT              (8)

#define TIMER_MAX_CH                    (8)
#define TIMER_CH_FLG                    (0)
#define TIMER_CH_COUNT                  (1)
#define TIMER_CH_MAX_COUNT              (2)

#define FLASH_OK                        (0)
#define FLASH_ERROR                     (-1)
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
*******************************************************************************/
static uint32_t    gs_timer_cnt_out[TIMER_MAX_CH][TIMER_CH_MAX_COUNT + 1];

static flash_spi_status_t flash_spi_busy_check (uint8_t driver,
                    flash_spi_poll_mode_t mode, uint32_t loop_cnt);
static int8_t flash_spi_wait_time (uint32_t channel, uint32_t time);
static int8_t flash_spi_start_timer (uint32_t channel, uint32_t msec);
static int8_t flash_spi_check_timer (uint32_t channel);
static int8_t flash_spi_end_timer (uint32_t channel);


/**********************************************************************************************************************
* Function Name: flash_spi_disk_initialize
*******************************************************************************************************************//**
* @brief This function initializes the disk drive.
*
* @param[in] drive  Specifies the initialize drive number.
*
* @retval TFAT_RES_OK  Normal termination.
*
* @retval Others       DSTATUS status of the disk after function execution.
*
* @details This function does not execute the Serial Flash memory driver initialize. Please implement Serial
* Flash memory initialize code in user code.
* @note None
*/
DSTATUS flash_spi_disk_initialize(uint8_t drive)
{
    uint8_t                 flash_status;       // Flash status

    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;

    /* Read flash status */
    ret = R_FLASH_SPI_Read_Status(drive, &flash_status);
    if (FLASH_SPI_SUCCESS > ret)
    {
        return STA_NOINIT;
    }

    if (0 != (flash_status & FLASH_BUSY))
    {
        return STA_NOINIT;                      // Flash is busy
    }

    return RES_OK;
} /* End of function flash_spi_disk_initialize() */


/**********************************************************************************************************************
* Function Name: flash_spi_disk_read
*******************************************************************************************************************//**
* @brief This function reads the data from disk.
*
* @param[in]  drive  Specifies the physical drive number.
*
* @param[out] buffer Pointer to the read buffer to store the read data. A buffer of the size equal to the
* number of bytes to be read is required.
*
* @param[in]  sector_number  Specifies the start sector number in logical block address (LBA).
*
* @param[in]  sector_count   Specifies number of sectors to read. The value can be 1 to 255.
*
* @retval DRESULT  Result of the function execution.
*
* @details Read data from Serial Flash memory by block.
* @note None
*/
DRESULT flash_spi_disk_read (
    uint8_t drive,               /* Physical drive number            */
    uint8_t* buffer,             /* Pointer to the read data buffer  */
    uint32_t sector_number,      /* Start sector number              */
    uint32_t sector_count        /* Number of sectors to read        */
)
{
    flash_spi_info_t        Flash_Info_R;
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;

    /* Set flash read arguments */
    Flash_Info_R.addr       = (uint32_t)(sector_number * TFAT_FLASH_SECTOR_SIZE);
    Flash_Info_R.cnt        = (uint32_t)(sector_count * TFAT_FLASH_SECTOR_SIZE);
    Flash_Info_R.p_data     = buffer;
    Flash_Info_R.op_mode    = FLASH_SPI_SINGLE;

    /* Read flash data */
    ret = R_FLASH_SPI_Read_Data(drive, &Flash_Info_R);
    if (FLASH_SPI_SUCCESS > ret)
    {
        return RES_ERROR;
    }

    return RES_OK;
} /* End of function flash_spi_disk_read() */

/* FAT sector structure definition */
typedef struct
{
    uint32_t erase_fat_sector_start;
    uint32_t erase_fat_sector_cnt;
    uint32_t program_fat_sector_start;
    uint32_t program_fat_sector_cnt;
} fat_sector_written_info_t;

typedef struct
{
    fat_sector_written_info_t head_sector_info;
    fat_sector_written_info_t midl_sector_info;
    fat_sector_written_info_t tail_sector_info;
} fat_sector_written_map_t;

/* Write sector size */
DRESULT flash_spi_disk_write_fat_sector(
    uint8_t drive,                /* Physical drive number           */
    const uint8_t* buffer,        /* Pointer to the write data       */
    uint32_t fat_sector           /* Sector number to write          */
)
{
    uint8_t* p_buffer = (uint8_t*)buffer;
    flash_spi_status_t rst_flash = FLASH_SPI_SUCCESS;
    flash_spi_info_t flash_spi_info;
    uint32_t page;
    
    /* WAIT_LOOP */
    for (page = 0;
        page < FLASH_PAGE_CNT_BY_FAT_SECTOR;
        page++, p_buffer += FLASH_PAGE_SIZE)
    {
        /* Write page */
        flash_spi_info.addr = fat_sector * TFAT_FLASH_SECTOR_SIZE +
                                        page * FLASH_PAGE_SIZE;
        flash_spi_info.cnt = FLASH_PAGE_SIZE;
        flash_spi_info.p_data = p_buffer;
        flash_spi_info.op_mode = FLASH_SPI_SINGLE;
        rst_flash = R_FLASH_SPI_Write_Data_Page(drive, &flash_spi_info);
        if (FLASH_SPI_SUCCESS != rst_flash)
        {
            return RES_ERROR;
        }
        rst_flash = flash_spi_busy_check(drive, FLASH_SPI_MODE_PROG_POLL,
                                                        FLASH_PP_BUSY_WAIT);
        if (FLASH_SPI_SUCCESS != rst_flash)
        {
            return RES_ERROR;
        }
    }
    return RES_OK;
}

/* erase sector size: 4KB */
static uint32_t g_buffer_flash_sector[FLASH_ERASE_SECTOR_SIZE / sizeof(uint32_t) * sizeof(uint8_t)] = {0};
DRESULT flash_spi_disk_write_erase_sectors(
    uint8_t drive,                /* Physical drive number           */
    const uint8_t* buffer,        /* Pointer to the write data       */
    fat_sector_written_info_t* p_written_info
)
{
    DRESULT ret = RES_OK;
    flash_spi_erase_info_t flash_spi_erase_info;
    uint32_t erase_sector;
    uint32_t sector;
    uint8_t *p_buff;
    if (0 != p_written_info->erase_fat_sector_cnt
        && 0 != p_written_info->program_fat_sector_cnt)
    {
        /* Whether write over data in g_buffer_flash_sector or not */
        if (p_written_info->erase_fat_sector_cnt
            == p_written_info->program_fat_sector_cnt)
        {
            /* p_written_info is middle part, therefore it doesn't need to
               write over g_buffer_flash_sector */
            p_buff = (uint8_t*)buffer;
        }
        else
        {
            /* p_written_info is fragment, head, or tail, therefore it needs to
               write over g_buffer_flash_sector */
            /* Read a flash erase sector to keep data */
            ret = flash_spi_disk_read(drive, (uint8_t*)g_buffer_flash_sector, 
                p_written_info->erase_fat_sector_start, 
                p_written_info->erase_fat_sector_cnt);
            if(RES_OK != ret)
            {
                return ret;
            }
            /* Write over data in g_buffer_flash_sector */
            memcpy((uint8_t*)g_buffer_flash_sector +
                (p_written_info->program_fat_sector_start - p_written_info->erase_fat_sector_start) * TFAT_FLASH_SECTOR_SIZE,
                (uint8_t*)buffer,
                p_written_info->program_fat_sector_cnt * TFAT_FLASH_SECTOR_SIZE);

                p_buff = (uint8_t*)g_buffer_flash_sector;
        }
        
        /* Erase a flash erase sector */
        /* WAIT_LOOP */
        for (erase_sector = 0; 
            erase_sector < p_written_info->erase_fat_sector_cnt; 
            erase_sector += FAT_SECTOR_CNT_BY_ERASE_SECTOR)
        {
            flash_spi_erase_info.addr = (p_written_info->erase_fat_sector_start + erase_sector) * TFAT_FLASH_SECTOR_SIZE;
            flash_spi_erase_info.mode = FLASH_SPI_MODE_S_ERASE;
            if (FLASH_SPI_SUCCESS !=
                R_FLASH_SPI_Erase(drive, &flash_spi_erase_info))
            {
                return RES_ERROR;
            }
            if (FLASH_SPI_SUCCESS != flash_spi_busy_check(drive, FLASH_SPI_MODE_ERASE_POLL, FLASH_SE_BUSY_WAIT))
            {
                return RES_ERROR;
            }
        }
        
        /* Program data which is written over as needed
           in flash erase sectors */
        /* WAIT_LOOP */
        for (sector = 0;
            sector < p_written_info->erase_fat_sector_cnt;
            sector++, p_buff += TFAT_FLASH_SECTOR_SIZE)
        {
            ret = flash_spi_disk_write_fat_sector(drive, p_buff,
                    p_written_info->erase_fat_sector_start + sector);
            if (RES_OK != ret)
            {
                return ret;
            }
        }
    }
    else if (0 == p_written_info->erase_fat_sector_cnt
            && 0 == p_written_info->program_fat_sector_cnt)
    {
        return RES_OK;
    }
    else
    {
        /* fat_sector_written_info_t member has error value */
        return RES_PARERR;
    }
    return ret;
}


DRESULT flash_spi_disk_write_map(uint8_t drive, const uint8_t* buffer,
                                        fat_sector_written_map_t* p_map)
{
    if (RES_OK != flash_spi_disk_write_erase_sectors(drive, buffer, &p_map->head_sector_info))
    {
        return RES_ERROR;
    }
    if (RES_OK != flash_spi_disk_write_erase_sectors(drive, 
            buffer + (p_map->head_sector_info.program_fat_sector_cnt * TFAT_FLASH_SECTOR_SIZE), 
            &p_map->midl_sector_info))
    {
        return RES_ERROR;
    }
    if (RES_OK != flash_spi_disk_write_erase_sectors(drive, 
            buffer + ((p_map->midl_sector_info.program_fat_sector_cnt + p_map->head_sector_info.program_fat_sector_cnt) * TFAT_FLASH_SECTOR_SIZE), 
            &p_map->tail_sector_info))
    {
        return RES_ERROR;
    }
    return RES_OK;
}

/******************************************************************************
* Function Name : get_sector_written_map
* Description   : This function calculates distribution map of written sectors 
*               :    of fat because serial flash writing process must be 
*               :    considered erasing and programing sectors of fat.
* Arguments     : uint32_t fat_sector_number : Sector number of fat to write
*               : uint32_t fat_sector_count  : Number of sectors of fat to write
*               : fat_sector_written_map_t* p_map : Sector map to write (output)
* Return value  : None
******************************************************************************/
void get_sector_written_map(
    uint32_t fat_sector_number,         /* Sector number of fat to write    */
    uint32_t fat_sector_count,          /* Number of sectors of fat to write */
    fat_sector_written_map_t* p_map     /* Sector map to write (output)    */
)
{
    uint32_t outside_sector = fat_sector_number + fat_sector_count;
    uint32_t next_erase_sector;
    uint32_t current_sector;
        p_map->head_sector_info.erase_fat_sector_cnt = 0;
        p_map->head_sector_info.program_fat_sector_cnt = 0;
        p_map->midl_sector_info.erase_fat_sector_cnt = 0;
        p_map->midl_sector_info.program_fat_sector_cnt = 0;
        p_map->tail_sector_info.erase_fat_sector_cnt = 0;
        p_map->tail_sector_info.program_fat_sector_cnt = 0;
    /* Calculate head part */
    if(0 == fat_sector_number % FAT_SECTOR_CNT_BY_ERASE_SECTOR)
    {
        /* Invalid of head part */
        current_sector = fat_sector_number;
    }
    else
    {
        p_map->head_sector_info.erase_fat_sector_start = 
                    (fat_sector_number / FAT_SECTOR_CNT_BY_ERASE_SECTOR) * FAT_SECTOR_CNT_BY_ERASE_SECTOR;
        p_map->head_sector_info.erase_fat_sector_cnt = FAT_SECTOR_CNT_BY_ERASE_SECTOR;
        p_map->head_sector_info.program_fat_sector_start = fat_sector_number;
        next_erase_sector = p_map->head_sector_info.erase_fat_sector_start +
                            FAT_SECTOR_CNT_BY_ERASE_SECTOR;
        if (outside_sector < next_erase_sector)
        {
            /* Fragment part */
            p_map->head_sector_info.program_fat_sector_cnt = fat_sector_count;
            return;
        }
        else
        {
            /* Head part */
            p_map->head_sector_info.program_fat_sector_cnt = next_erase_sector - fat_sector_number;
        }
        current_sector = next_erase_sector;
    }
    /* Calculate middle part */
    if((outside_sector - current_sector) < FAT_SECTOR_CNT_BY_ERASE_SECTOR)
    {
        /* Invalid of middle part */
        /* Do Nothing */
        R_BSP_NOP();
    }
    else
    {
        /* Middle part */
        p_map->midl_sector_info.erase_fat_sector_start = current_sector;
        p_map->midl_sector_info.erase_fat_sector_cnt = 
            ((outside_sector - current_sector) / FAT_SECTOR_CNT_BY_ERASE_SECTOR) * FAT_SECTOR_CNT_BY_ERASE_SECTOR;
        p_map->midl_sector_info.program_fat_sector_start = current_sector;
        p_map->midl_sector_info.program_fat_sector_cnt = p_map->midl_sector_info.erase_fat_sector_cnt;
        current_sector = p_map->midl_sector_info.erase_fat_sector_start + p_map->midl_sector_info.erase_fat_sector_cnt;
    }
    /* Calculate tail part */
    p_map->tail_sector_info.program_fat_sector_cnt = outside_sector - current_sector;
    if(0 == p_map->tail_sector_info.program_fat_sector_cnt)
    {
        /* Invalid of tail part */
        /* Do Nothing */
        R_BSP_NOP();
    }
    else
    {
        /* Tail part */
        p_map->tail_sector_info.erase_fat_sector_start = current_sector;
        p_map->tail_sector_info.erase_fat_sector_cnt = FAT_SECTOR_CNT_BY_ERASE_SECTOR;
        p_map->tail_sector_info.program_fat_sector_start = current_sector;
    }
    return;
}


/**********************************************************************************************************************
* Function Name: flash_spi_disk_write
*******************************************************************************************************************//**
* @brief This function writes the data to the disk.
*
* @param[in] drive  Specifies the physical drive number.
*
* @param[in] buffer Pointer to the data to be written.
*
* @param[in] sector_number  Specifies the start sector number in logical block address (LBA).
*
* @param[in] sector_count   Specifies number of sectors to write. The value can be 1 to 255.
*
* @retval DRESULT  Result of the function execution.
*
* @details Write the data to the Serial Flash memory by block.
* @note None
*/
DRESULT flash_spi_disk_write (
    uint8_t drive,                /* Physical drive number           */
    const uint8_t* buffer,        /* Pointer to the write data       */
    uint32_t sector_number,       /* Sector number to write          */
    uint32_t sector_count         /* Number of sectors to write      */
)
{
    uint8_t                 flash_status;       // flash status

    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;
    fat_sector_written_map_t fat_sector_written_map;

    /* Disable the write PROTECT */
    ret = R_FLASH_SPI_Set_Write_Protect(drive, FLASH_WRITE_PROTECT_CLOSE);
    if (FLASH_SPI_SUCCESS > ret)
    {
        return RES_ERROR;
    }

    /* Disable the write PROTECT completed */
    ret = flash_spi_busy_check(drive, FLASH_SPI_MODE_REG_WRITE_POLL, FLASH_WR_BUSY_WAIT);
    if (FLASH_SPI_SUCCESS != ret)
    {
        return RES_ERROR;
    }

    ret = R_FLASH_SPI_Read_Status(drive, &flash_status);
    if (FLASH_SPI_SUCCESS > ret)
    {
        return RES_ERROR;
    }

    if (0 != (flash_status & FLASH_WRITE_PROTECT_STATUS))   // Write protect is disable
    {
        return RES_WRPRT;
    }

    /* Calculate position of fat sectors which is erased and programed */
    get_sector_written_map(sector_number, sector_count, &fat_sector_written_map);
    /* Write data to serial flash */
    if (RES_OK != flash_spi_disk_write_map(drive, (uint8_t*)buffer, &fat_sector_written_map))
    {
        return RES_ERROR;
    }

    /* Enable write PROTECT */
    ret = R_FLASH_SPI_Set_Write_Protect(drive, FLASH_WRITE_PROTECT_OPEN);
    if (FLASH_SPI_SUCCESS > ret)
    {
        return RES_ERROR;
    }
    
    ret = flash_spi_busy_check(drive, FLASH_SPI_MODE_REG_WRITE_POLL, FLASH_WR_BUSY_WAIT);
    if (FLASH_SPI_SUCCESS != ret)
    {
        return RES_ERROR;
    }

    return RES_OK;
} /* End of function flash_spi_disk_write() */


/**********************************************************************************************************************
* Function Name: flash_spi_disk_ioctl
*******************************************************************************************************************//**
* @brief This function controls the drive.
*
* @param[in] drive   Specifies the physical drive number.
*
* @param[in] command Specifies the command code. The command code will always be 0.
*
* @param[in] buffer  Pointer should always be a NULL pointer.
*
* @retval DRESULT  Result of the function execution.
*
* @details The flash_spi_disk_ioctl function is used only by the f_sync or f_mkfs function amongst all the TFAT
* FIT functions. Users who do not plan to use f_sync function in their applications can skip the implementation
* for this particular driver interface function.\n
* For users who wish to use f_sync function in their applications, the command CTRL_SYNC has to be implemented.\n
* The command CTRL_SYNC should consist of the code to finish off any pending write process. If the disk i/o module
* has a write back cache, the dirty sector must be flushed immediately. The f_sync function will perform a save
* operation to the unsaved data related to the file object passed as argument.\n
* For other commands, see Section 4.6.4 in the application note for details.
* @note None
*/
DRESULT flash_spi_disk_ioctl (
    uint8_t drive,                /* Drive number             */
    uint8_t command,              /* Control command code     */
    void* buffer                  /* Data transfer buffer     */
)
{
    uint8_t             cmd = command;
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;
#if FF_FS_READONLY == 0
    uint8_t                 flash_status;       // flash status
#endif
#if FF_USE_MKFS == 1
    uint32_t                flash_size;
    flash_spi_mem_info_t Flash_MemInfo;
#endif

    if ((NULL == buffer) && (CTRL_SYNC != cmd))
    {
        return RES_PARERR;
    }

    switch (cmd)
    {
        case CTRL_SYNC:
#if FF_FS_READONLY == 0
            /* Read FLASH status */
            ret = R_FLASH_SPI_Read_Status(drive, &flash_status);
            if (FLASH_SPI_SUCCESS > ret)
            {
                return RES_ERROR;
            }
            
            if (0 != (flash_status & FLASH_BUSY))
            {
                return RES_NOTRDY;             // Flash is busy
            }
            else
            {
                R_BSP_NOP();          // Flash isn't busy
            }
#endif
        break;
        
        case GET_SECTOR_COUNT:
#if FF_USE_MKFS == 1
            /* Get Flash memory information */
            ret = R_FLASH_SPI_GetMemoryInfo(drive, &Flash_MemInfo);
            if (FLASH_SPI_SUCCESS != ret)
            {
                return RES_ERROR;
            }
            
            flash_size = (Flash_MemInfo.mem_size / TFAT_FLASH_SECTOR_SIZE);
            ((uint32_t *)buffer)[0] = flash_size;       // Return the total number of sectors
#endif
        break;
        
        case GET_SECTOR_SIZE:
#if FF_MAX_SS != FF_MIN_SS
            flash_size = TFAT_FLASH_SECTOR_SIZE;
            ((uint32_t *)buffer)[0] = flash_size;       // Return the sector size of flash
#endif
        break;
        
        case GET_BLOCK_SIZE:
#if FF_USE_MKFS == 1
            ((uint32_t *)buffer)[0] = FAT_SECTOR_CNT_BY_ERASE_SECTOR;               // Sector count per erasable block
#endif
        break;
        
        case CTRL_TRIM:
            
        break;
        
        default:
            return RES_PARERR;
        break;
    }

    return RES_OK;
} /* End of function flash_spi_disk_ioctl() */


/**********************************************************************************************************************
* Function Name: flash_spi_disk_status
*******************************************************************************************************************//**
* @brief This function gets the disk drive status.
*
* @param[in] drive  Specifies the physical drive number.
*
* @retval TFAT_RES_OK  Normal termination.
*
* @retval Others       DSTATUS status of the disk after function execution.
*
* @details This function should consist of the code that checks the disk and returns the current disk status.
* The disk status can have any of the three values, see Section 2.10 in the application note for details.
* The disk status can be returned by updating the return value with the macros related to disk status.
* @note None
*/
DSTATUS flash_spi_disk_status (
    uint8_t drive                  /* Physical drive number    */
)
{
    uint8_t                 flash_status;           // flash status
    flash_spi_status_t      ret = FLASH_SPI_SUCCESS;

    ret = R_FLASH_SPI_Read_Status(drive, &flash_status);
    if (FLASH_SPI_SUCCESS != ret)
    {
        return STA_NODISK;
    }

    if (0 != (flash_status & FLASH_BUSY))
    {
        return STA_NOINIT;                          //Flash is busy
    }
    else
    {
        R_BSP_NOP();
    }

    return RES_OK;
} /* End of function flash_spi_disk_status() */


/**********************************************************************************************************************
* Function Name: flash_spi_1ms_interval
*******************************************************************************************************************//**
* @brief This function updates the internal timer per 1 ms.
*
* @details This function updates the internal timer of the TFAT driver FIT per 1 ms. This timer is used to check
* the busy status of the serial flash memory.
* @note None
*/
void flash_spi_1ms_interval (void)
{
    uint32_t channel = 0;

    /* WAIT_LOOP */
    for (channel = 0; channel < TIMER_MAX_CH; channel++)
    {
        if (0 != gs_timer_cnt_out[channel][TIMER_CH_FLG])
        {
            gs_timer_cnt_out[channel][TIMER_CH_COUNT]++;
        }
    }

    return;
} /* End of function flash_spi_1ms_interval() */

/******************************************************************************
* Function Name : flash_spi_busy_check
* Description   : This function is used to check flash memory status
*               :    of the disk
* Arguments     : flash_spi_poll_mode_t mode          Mode of error check
*                 uint32_t loop_cnt                   loop counter(ms)
* Return value  : Result of function execution
******************************************************************************/
static flash_spi_status_t flash_spi_busy_check (
    uint8_t driver,                     /* channel number */
    flash_spi_poll_mode_t mode,         /* Poll mode */
    uint32_t loop_cnt                   /* loop count for 1ms */
)
{
    flash_spi_status_t ret = FLASH_SPI_SUCCESS_BUSY;

    do
    {
        /* FLASH is busy.
           User application can perform other processing while flash is busy. */

        ret = R_FLASH_SPI_Polling(driver, mode);
        if (FLASH_SPI_SUCCESS_BUSY != ret)
        {
            /* FLASH is ready or error. */
            break;
        }
        loop_cnt--;
        flash_spi_wait_time(driver, 1);     // 1 ms
    }
    while (0 != loop_cnt); /* WAIT_LOOP */

    return ret;
} /* End of function flash_spi_busy_check() */

/******************************************************************************
* Function Name : flash_spi_wait_time
* Description   : This function is used to wait for specified time
*               :    of the disk
* Arguments     : uint32_t channel       timer channel number
*                 uint32_t time          timeout(ms)
* Return value  : Result of function execution
******************************************************************************/
static int8_t flash_spi_wait_time (
    uint32_t channel,                    /* timer channel No. */
    uint32_t time                        /* timeout value */
)
{
    if (flash_spi_start_timer(channel, time) == FLASH_ERROR)
    {
        return FLASH_ERROR;
    }

    /* WAIT_LOOP */
    while (1)
    {
        /* Timeout? */
        if (FLASH_ERROR == flash_spi_check_timer(channel))
        {
            break;
        }
    }

    flash_spi_end_timer(channel);

    return FLASH_OK;
} /* End of function flash_spi_wait_time() */

/******************************************************************************
* Function Name : flash_spi_start_timer
* Description   : This function is used to start timer
*               :    of the disk
* Arguments     : uint32_t channel       timer channel number
*                 uint32_t msec          timeout(ms)
* Return value  : Result of function execution
******************************************************************************/
static int8_t flash_spi_start_timer (
    uint32_t channel,                    /* timer channel No. */
    uint32_t msec                        /* timeout value */
)
{
    if (TIMER_MAX_CH <= channel)
    {
        return FLASH_ERROR;
    }

    /* ---- Check argument ---- */
    if ((0 >= msec) || (msec > 0x0fffffff))
    {
        return FLASH_ERROR;
    }
    gs_timer_cnt_out[channel][TIMER_CH_FLG] = 1;
    gs_timer_cnt_out[channel][TIMER_CH_COUNT] = 0;
    gs_timer_cnt_out[channel][TIMER_CH_MAX_COUNT] = msec;

    return FLASH_OK;
} /* End of function flash_spi_start_timer() */

/******************************************************************************
* Function Name : flash_spi_check_timer
* Description   : This function is used to check timeout
*               :    of the disk
* Arguments     : uint32_t channel       timer channel number
* Return value  : Result of function execution
******************************************************************************/
static int8_t flash_spi_check_timer (
    uint32_t channel                   /* timer channel No. */
)
{
    int8_t ret = 0;

    /* ---- Check compare ---- */
    if (gs_timer_cnt_out[channel][TIMER_CH_COUNT] >= gs_timer_cnt_out[channel][TIMER_CH_MAX_COUNT])
    {
        ret = FLASH_ERROR;
    }
    else
    {
        ret = FLASH_OK;
    }

    return ret;
} /* End of function flash_spi_check_timer() */

/******************************************************************************
* Function Name : flash_spi_end_timer
* Description   : This function is used to end the timer
* Arguments     : uint32_t channel       timer channel number
* Return value  : Result of function execution
******************************************************************************/
static int8_t flash_spi_end_timer (
    uint32_t channel                   /* timer channel No. */
)
{
    gs_timer_cnt_out[channel][TIMER_CH_FLG] = 0;

    return FLASH_OK;
} /* End of function flash_spi_end_timer() */

#endif /* (TFAT_SERIAL_FLASH_DRIVE_NUM > 0) */
/******************************************************************************
End  Of File
******************************************************************************/
