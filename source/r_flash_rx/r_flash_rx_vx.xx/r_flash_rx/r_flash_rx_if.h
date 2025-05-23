/*
* Copyright (C) 2014-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_flash_rx_if.h
* Description  : This module provides the interface file to be included by the user when using the FLASH API
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*           12.04.2014 1.00    First Release
*           24.11.2014 1.10    Enhanced non_fcu driver. Added timeout check, clearing of FLASH.FASR.BIT.EXS, and
*                              additional checking of .PRGERR
*           11.12.2014 1.11    Added RX64M to xml support file.
*           22.12.2014 1.20    Added RX71M support.
*           25.06.2015 1.30    Added RX231 support. Added RX64M/71M run-from-rom support.
*           03.09.2015 1.40    Added RX23T support.
*           11.11.2015 1.50    Added RX130 support.
*           11.11.2015 1.51    Added RX130 demo to web package.
*           11.11.2015 1.60    Added RX24T support. Added Cache support.
*           20.05.2016 1.61    Added BGO write/erase/blankcheck interrupt operation for RX64M/71M (Flash Type 3).
*                              Fixed FLASH_CMD_LOCKBIT_DISABLE/ENABLE operation.
*           25.05.2016 1.62    Added BGO lockbit read/write interrupt operation for RX64M/71M (Flash Type 3).
*           13.06.2016 1.63    Fixed timeouts on flash erase and write (too short and returned success when failed).
*           10.08.2016 1.64    Fixed Flash Type 3 R_FLASH_Control(FLASH_CMD_STATUS_GET, NULL).
*                               (always returned BUSY)
*                              Cleaned up flash_fcuram_codecopy() function.
*                              Added #if to exclude ISR code when not in BGO mode.
*           11.08.2016 1.70    Added RX651/65N support (Flash Type 4). Re-organized this file based on feature sets.
*                              Fixed blankcheck bug on Flash Type 2.
*           12.08.2016 2.00    Added configuration option for BSPless operation.
*                              Added support for RX230.
*           12.12.2016 2.10    Added support for RX24U and 512K RX24T.
*                              Added equate FLASH_HAS_DIFF_CF_BLOCK_SIZES.
*
*                              Type 1:
*                              Fixed flash_reset() so issues a flash_stop() before issuing a FLASH_CMD_RESET.
*                              Added DF and CF block boundary check to flash_api_erase().
*                              Added CF block boundary check to FLASH_CMD_ACCESSWINDOW_SET.
*                              Added non-NULL argument check for FLASH_CMD_SWAPSTATE_SET and FLASH_CMD_SWAPSTATE_GET.
*                              Added valid SAS value check for FLASH_CMD_SWAPSTATE_SET.
*                              Added check for BUSY in flash_api_control() when in BGO mode.
*                              Added check in Open() for another operation in progress when in BGO mode.
*
*                              Type 2:
*                              Fixed bug where erasing code flash block 0 would return FLASH_ERR_ADDRESS.
*                              Fixed bug where erase ran at both app and interrupt level in BGO mode causing failure.
*                              Fixed bug where erase always erased first block more than once in BGO mode.
*                              Fixed bug where erasing more than 1 block in BGO mode did not work.
*                              Fixed bug where flash error interrupts remained disabled in BGO mode.
*                              Fixed bug where interrupts disabled in BGO mode when blank checking BLANK_CHECK_SMALLEST.
*                              Fixed bug where #if not set properly for FLASH_CFG_CODE_FLASH_ENABLE set to 0.
*                              Fixed bug in RX21x where FLASH_CF_BLOCK_INVALID for 1M parts was incorrect.
*                              Added check to R_FLASH_Control() to detect missing argument.
*                              Added check that interrupt priority is 1-15 in BGO mode.
*                              Added check for DF erase on non-block boundary addresses.
*                              Added check for lockbit program/read on illegal DF addresses.
*                              Added check so Open() cannot be called while another operation is in progress in BGO mode.
*
*                              Type 3:
*                              Fixed flash_reset() so enters PE mode before issuing a flash_stop()
*                                when in idle state.
*                              Fixed bug where locking multiple blocks would exit in BGO before operation completed.
*                              Fixed bug where driver was not locked in flash_api_lockbit_set().
*                              Fixed bug where interrupt was not handled properly when an internal flash_stop()
*                                was issued.
*                              Fixed bug where rounding was not handled in flash_clock_config().
*                              Fixed bug where where Open() did not check if another operation was in progress
*                                when in BGO mode.
*                              Fixed bug where #if not set properly for FLASH_CFG_CODE_FLASH_ENABLE set to 0.
*                              Moved flash_api_control() and flash_api_lockbit_set() into FRAM so will work when
*                                FLASH_CFG_CODE_FLASH_ENABLE is 1.
*                              Added CF and DF block boundary check to flash_api_erase().
*                              Added DF minimum program size boundary check to flash_api_blankcheck().
*                              Added argument present check for FLASH_CMD_LOCKBIT_READ, FLASH_CMD_LOCKBIT_WRITE, and
*                                FLASH_CMD_CONFIG_CLOCK.
*                              Added CF block boundary check to flash_api_lockbit_read() and flash_api_lockbit_set().
*                              Added check that start address + number blocks does not exceed legal address range
*                                for flash_api_erase(), flash_api_lockbit_set().
*                              Added check that callback function is set in BGO mode for flash_api_blankcheck(),
*                                flash_api_erase(), flash_api_write() and flash_api_control() for FLASH_CMD_LOCKBIT_READ
*                                and FLASH_CMD_LOCKBIT_WRITE.
*
*                              Type 4:
*                              Fixed flash_reset() so enters PE mode before issuing a flash_stop()
*                                when in idle state.
*                              Fixed bug where interrupt was not handled properly when an internal flash_stop()
*                                was issued.
*                              Fixed bug where rounding was not handled in flash_clock_config().
*                              Added CF block boundary check to flash_api_erase().
*                              Added argument present check for FLASH_CMD_CONFIG_CLOCK.
*                              Added check that start address + number blocks does not exceed legal address range
*                                for flash_api_erase().
*                              Added check that callback function is set in BGO mode for flash_api_erase() and
*                                flash_api_write().
*                              Removed commented out code.
*
*           13.12.2016 3.00    Merged functions common to Flash Types 1, 3, and 4 into r_flash_group.c and
*                                 restructured high level.
*                              Merged functions common to Flash Types 3 and 4 into r_flash_fcu.c.
*                              Moved BLANK_CHECK_SMALLEST and BLANK_CHECK_ENTIRE_BLOCK from r_flash_rx.h to here.
*                               (Flash Type 2 R_FLASH_BlankCheck() 'size" argument).
*                              Combined #include paths for RX651 and RX65N in r_flash_rx.h
*
*           06.02.2017 3.10    Added support for RX65N-2M (bank/application swap).
*                              Removed bad return BUSY from R_DF/CF_Write_Check(), R_DF/CF_Erase_Check(), and
*                                 R_DF/CF_BlankCheck_Check() timeout loops in Flash Type 1 devices.
*                              Added code to clear ECC flag in flash_fcuram_codecopy() for Type 3 devices.
*                              Corrected DF_NUM_BLOCKS value in r_flash_rx220.h
*           11.08.2017 3.20    Added support for RX130-512.
*                              Updated equates for MCU_CFG_PART_MEMORY_SIZEs for RX130, RX231, RX63N/631, RX65N.
*                              Expanded qualification for FLASH_IN_DUAL_BANK_MODE.
*                              Repackaged include files so r_mcu_config.h not required for projects using BSP.
*                              Fixed bug in RX65N-2M dual mode operation where sometimes when running in bank 0,
*                                 performing a bank swap caused application execution to fail.
*           31.10.2017 3.30    Added error check FLASH_ERR_ALREADY_OPEN to R_FLASH_Open().
*                              Added function R_FLASH_Close().
*           06.09.2018 3.40    Added support for RX66T.
*                              Added support for 256K and 384K RX111 variants.
*                              Added support for 256K and 384K RX24T variants.
*           08.11.2018 3.41    Added NON_CACHED Control() commands.
*                              Added new <sampleapplicationnote> tag to driver associated xml file.
*           12.02.2019 3.42    Fixed typos in app note.
*           26.02.2019 3.50    Added support for RX72T.
*                              Fixed write failure bug in RX210 768K and 1M variants.
*                              Modified flash types 3 and 4 R_FLASH_BlankCheck() parameter checking to return error
*                                 when argument passed in is code flash address.
*           19.04.2019 4.00    Removed support for flash type 2.
*                               (BLANK_CHECK_SMALLEST, BLANK_CHECK_ENTIRE_BLOCK,
*                                FLASH_CMD_LOCKBIT_PROGRAM, FLASH_CMD_LOCKBIT_PROTECTION,
*                                FLASH_ERR_ALIGNED, FLASH_ERR_BOUNDARY, FLASH_ERR_OVERFLOW)
*           07.06.2019 4.10    Added support for RX23W.
*           19.07.2019 4.20    Added support for RX72M.
*           09.09.2019 4.30    Added support for RX13T.
*           27.09.2019 4.40    Added support for RX23E-A.
*           18.11.2019 4.50    Added support for RX66N, and RX72N.
*           26.06.2020 4.60    Modified some minor problem.
*           23.10.2020 4.70    Added support for RX671.
*           23.04.2021 4.80    Added support for RX140.
*           10.12.2021 4.81    Added support for Tool News R20TS0765, R20TS0772, and some minor updates.
*           13.05.2022 4.90    Added support for RX660.
*                              Added support for Tool News R20TS0818, and Technical Update TN-RX*-A0261A.
*           23.12.2022 4.91    Fixed typos in app note. 
*           24.01.2023 5.00    Added support for RX26T. Added Flash Type 5.
*                              Added support for Tool News R20TS0872.
*           28.02.2023 5.10    Added support for RX23E-B.
*           01.10.2023 5.11    Added support for Tool News R20TS0963.
*           17.01.2024 5.12    Modified the dual mode definition of RX671 code flash memory 1 Mbyte.
*           30.07.2024 5.20    Added support for RX260 and RX261.
*                              Added countermeasures as described in Technical Update TN-RX*-A0274A.
*                              Modified FISR register settings.
*                              Modified functions flash_InterruptRequestDisable(), flash_InterruptRequestEnable().
*                              (When using the GCC or IAR compiler in non-blocking mode,
*                               ROM access occurs during P/E mode.)
*           15.11.2024 5.21    Added WAIT_LOOP comment.
*           20.03.2025 5.22    Changed the disclaimer in program sources
***********************************************************************************************************************/

#ifndef FLASH_INTERFACE_HEADER_FILE
#define FLASH_INTERFACE_HEADER_FILE

#include "r_flash_rx_config.h"
#include "r_flash_targets.h"

#if R_BSP_VERSION_MAJOR < 5
    #error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Driver Version Number. */
#define FLASH_RX_VERSION_MAJOR           (5)
#define FLASH_RX_VERSION_MINOR           (22)


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/* DRIVER INTERNAL PROGRAMMING GROUPINGS */

#define FLASH_TYPE_1    1
#define FLASH_TYPE_3    3
#define FLASH_TYPE_4    4
#define FLASH_TYPE_5    5

#if (defined(MCU_RX110) || defined(MCU_RX111) || defined(MCU_RX113) || \
     defined(MCU_RX130) || defined(MCU_RX231) || defined(MCU_RX23T) || \
     defined(MCU_RX24T) || defined(MCU_RX24U) || defined(MCU_RX230) || \
     defined(MCU_RX23W) || defined(MCU_RX13T) || defined(MCU_RX23E_A) || \
     defined(MCU_RX140) || defined(MCU_RX23E_B) || defined(MCU_RX260) || \
     defined(MCU_RX261))
#define FLASH_TYPE              FLASH_TYPE_1

#elif (defined(MCU_RX64M) || defined(MCU_RX66T) || defined(MCU_RX71M) || \
       defined(MCU_RX72T) || defined(MCU_RX660))
#define FLASH_TYPE              FLASH_TYPE_3

#elif (defined(MCU_RX651) || defined(MCU_RX65N) || defined(MCU_RX72M) || \
       defined(MCU_RX66N) || defined(MCU_RX72N) || defined(MCU_RX671))
#define FLASH_TYPE              FLASH_TYPE_4

#elif (defined(MCU_RX26T))
#define FLASH_TYPE              FLASH_TYPE_5
#endif

#define FLASH_TYPE_VARIETY_A    (1)

#if (defined(MCU_RX140) || defined(MCU_RX260) || defined(MCU_RX261))
#define FLASH_TYPE_VARIETY      (FLASH_TYPE_VARIETY_A)
#endif

/* FEATURE GROUPINGS */

#define FLASH_HAS_ISR_CALLBACK_CMD  1

#if ((FLASH_TYPE == 4) && (MCU_DATA_FLASH_SIZE_BYTES == 0))
#define FLASH_NO_BLANK_CHECK        1
#endif

#if (FLASH_TYPE == 1)
#define FLASH_HAS_CF_BLANK_CHECK    1
#endif

#if (defined(MCU_RX110) || defined(MCU_RX23T) || ((FLASH_TYPE == 4) && (MCU_DATA_FLASH_SIZE_BYTES == 0)))
#define FLASH_NO_DATA_FLASH         1
#if (FLASH_CFG_CODE_FLASH_ENABLE == 0)
#error "No data flash on this MCU. Set FLASH_CFG_CODE_FLASH_ENABLE to 1 in r_flash_rx_config.h."
#endif
#endif

#if (FLASH_TYPE == 1)
#define FLASH_ERASE_CF_ASCENDING_ADDRESSES     1
#else
#define FLASH_ERASE_CF_ASCENDING_BLOCK_NUMS    1
#endif

#if (defined(MCU_RX24T) || defined(MCU_RX24U) || defined(MCU_RX66T) || \
     defined(MCU_RX72T) || (FLASH_TYPE == 4))
#define FLASH_HAS_ROM_CACHE     1
#endif

#if (defined(MCU_RX66T) || defined(MCU_RX72T) || defined(MCU_RX72M) || \
     defined(MCU_RX66N) || defined(MCU_RX72N) || defined(MCU_RX671))
#define FLASH_HAS_NON_CACHED_RANGES     1
#endif

#if (defined(MCU_RX64_ALL) || defined(MCU_RX65_ALL) || defined(MCU_RX66_ALL) || \
     defined(MCU_RX71_ALL) || defined(MCU_RX72_ALL) || defined(MCU_RX67_ALL) || \
     defined(MCU_RX26T))
#define FLASH_HAS_DIFF_CF_BLOCK_SIZES   1
#endif

#if ((FLASH_TYPE == 1) || (FLASH_TYPE == 4) || (FLASH_TYPE == 5))
#define FLASH_HAS_BOOT_SWAP     1
#endif

#if (((FLASH_TYPE == 4) && (MCU_ROM_SIZE_BYTES >= 1572864)) || defined(MCU_RX67_ALL) || (FLASH_TYPE == 5))
#define FLASH_HAS_APP_SWAP      1
#endif

#if ((FLASH_TYPE == 1) || (FLASH_TYPE == 4) || (FLASH_TYPE == 5))
#define FLASH_HAS_CF_ACCESS_WINDOW  1
#endif

#if (FLASH_TYPE == 3)
#define FLASH_HAS_SEQUENTIAL_CF_BLOCKS_LOCK     1
#endif

#if (FLASH_TYPE != 1)
#define FLASH_HAS_ERR_ISR           (1)
#endif

#if ((FLASH_TYPE == 3) || (FLASH_TYPE == 4) || (FLASH_TYPE == 5))
#define FLASH_HAS_FCU               (1)
#endif

#if (defined(MCU_RX64M) || defined(MCU_RX71M))
#define FLASH_HAS_FCU_RAM_ENABLE    (1)
#endif

#if (((FLASH_TYPE == 4) || (FLASH_TYPE == 5)) && (FLASH_HAS_APP_SWAP == 1) && (BSP_CFG_CODE_FLASH_BANK_MODE == 0) && (FLASH_CFG_CODE_FLASH_ENABLE == 1))
#define FLASH_IN_DUAL_BANK_MODE     (1)
#endif

#if FLASH_IN_DUAL_BANK_MODE
#define MCU_ROM_REGION_SIZE_BYTES    (MCU_ROM_SIZE_BYTES / 2)
#else
#define MCU_ROM_REGION_SIZE_BYTES    MCU_ROM_SIZE_BYTES
#endif



/* Return error codes */
typedef enum _flash_err
{
    FLASH_SUCCESS = 0,
    FLASH_ERR_BUSY,         // Peripheral Busy
    FLASH_ERR_ACCESSW,      // Access window error
    FLASH_ERR_FAILURE,      // Operation failure, programming or erasing error due to something other than lock bit
    FLASH_ERR_CMD_LOCKED,   // Peripheral in command locked state
    FLASH_ERR_LOCKBIT_SET,  // Pgm/Erase error due to lock bit.
    FLASH_ERR_FREQUENCY,    // Illegal frequency value attempted
    FLASH_ERR_BYTES,        // Invalid number of bytes passed
    FLASH_ERR_ADDRESS,      // Invalid address or address not on a programming boundary
    FLASH_ERR_BLOCKS,       // The 'number of blocks' argument is invalid
    FLASH_ERR_PARAM,        // Illegal parameter
    FLASH_ERR_NULL_PTR,     // Received null ptr; missing required argument
    FLASH_ERR_UNSUPPORTED,  // Command not supported for this flash type
    FLASH_ERR_SECURITY,     // Pgm/Erase error due to part locked (FAW.FSPR)
    FLASH_ERR_TIMEOUT,      // Timeout Condition
    FLASH_ERR_ALREADY_OPEN, // Open() called twice without intermediate Close()
    FLASH_ERR_HOCO          // The HOCO is not running.
} flash_err_t;


/* R_FLASH_Control() commands */
typedef enum _flash_cmd
{
    FLASH_CMD_RESET,                // Kill any ongoing operation and reset the flash controller
    FLASH_CMD_STATUS_GET,           // Get flash status; returns FLASH_ERR_BUSY or FLASH_SUCCESS (idle)
    FLASH_CMD_SET_BGO_CALLBACK,     // Specify callback function for Flash ISR
                                    // Arg: flash_interrupt_config_t*
    FLASH_CMD_SWAPFLAG_GET,         // Get current selection for the start-up area used at reset
                                    // Arg: uint8_t* (FLASH_STARTUP_SETTING_xxx)
    FLASH_CMD_SWAPFLAG_TOGGLE,      // Swap the start-up area used at reset

    FLASH_CMD_SWAPSTATE_GET,        // Get the temporarily active start-up area (FLASH_SAS_xxx)
                                    // Arg: uint8_t*
    FLASH_CMD_SWAPSTATE_SET,        // Set the start-up area for temporary use (FLASH_SAS_xxx)
                                    // Arg: uint8_t*
    FLASH_CMD_ACCESSWINDOW_SET,     // Set the Access Window boundaries for DF or CF
                                    // Arg: flash_access_window_config_t*
    FLASH_CMD_ACCESSWINDOW_GET,     // Get the Access Window boundaries for CF
                                    // Arg: flash_access_window_config_t*
    FLASH_CMD_LOCKBIT_READ,         // (Flash Type 3) Arg: flash_lockbit_config_t*
    FLASH_CMD_LOCKBIT_WRITE,        // (Flash Type 3) Arg: flash_lockbit_config_t*
    FLASH_CMD_LOCKBIT_ENABLE,       // (Flash Type 3) Enabled by default
    FLASH_CMD_LOCKBIT_DISABLE,      // (Flash Type 3) Override lockbits; erase block to clear lockbit

    FLASH_CMD_CONFIG_CLOCK,         // (Flash Types 3,4) Arg: uint32_t* (FCLK speed)

    FLASH_CMD_ROM_CACHE_ENABLE,     // Enable caching of ROM
    FLASH_CMD_ROM_CACHE_DISABLE,    // Disable caching (before rewriting ROM)
    FLASH_CMD_ROM_CACHE_STATUS,     // Arg: uint8_t*  (1 if cache is enabled; 0 otherwise)

    FLASH_CMD_SET_NON_CACHED_RANGE0, // do not cache this address range when caching enabled
    FLASH_CMD_SET_NON_CACHED_RANGE1, // do not cache this address range when caching enabled
    FLASH_CMD_GET_NON_CACHED_RANGE0, // get non-cached address range 0
    FLASH_CMD_GET_NON_CACHED_RANGE1, // get non-cached address range 1

    FLASH_CMD_BANK_TOGGLE,          // Swap the application bank (dual mode) used at startup
    FLASH_CMD_BANK_GET,             // Get bank address at next reset. Arg: flash_bank_t*
    FLASH_CMD_END_ENUM
} flash_cmd_t;


/*Result type for certain operations*/
typedef enum _flash_res
{
    FLASH_RES_LOCKBIT_STATE_PROTECTED,      // (Flash Type 3) Result for FLASH_CMD_LOCKBIT_READ
    FLASH_RES_LOCKBIT_STATE_NON_PROTECTED,  // (Flash Type 3) Result for FLASH_CMD_LOCKBIT_READ
    FLASH_RES_BLANK,                        // Result for Blank Check Function
    FLASH_RES_NOT_BLANK                     // Result for Blank Check Function
} flash_res_t;


typedef enum _flash_type
{
    FLASH_TYPE_CODE_FLASH = 0,
    FLASH_TYPE_DATA_FLASH,
    FLASH_TYPE_INVALID
} flash_type_t;


/* Event type for the flash interrupt callback function (where available) */
typedef enum _flash_interrupt_event
{
    FLASH_INT_EVENT_INITIALIZED,
    FLASH_INT_EVENT_ERASE_COMPLETE,
    FLASH_INT_EVENT_WRITE_COMPLETE,
    FLASH_INT_EVENT_BLANK,
    FLASH_INT_EVENT_NOT_BLANK,
    FLASH_INT_EVENT_TOGGLE_STARTUPAREA,
    FLASH_INT_EVENT_SET_ACCESSWINDOW,
    FLASH_INT_EVENT_LOCKBIT_WRITTEN,
    FLASH_INT_EVENT_LOCKBIT_PROTECTED,
    FLASH_INT_EVENT_LOCKBIT_NON_PROTECTED,
    FLASH_INT_EVENT_ERR_DF_ACCESS,
    FLASH_INT_EVENT_ERR_CF_ACCESS,
    FLASH_INT_EVENT_ERR_SECURITY,
    FLASH_INT_EVENT_ERR_CMD_LOCKED,
    FLASH_INT_EVENT_ERR_LOCKBIT_SET,
    FLASH_INT_EVENT_ERR_FAILURE,
    FLASH_INT_EVENT_TOGGLE_BANK,
    FLASH_INT_EVENT_END_ENUM
} flash_interrupt_event_t;


#ifdef FLASH_HAS_ISR_CALLBACK_CMD
/* Control() FLASH_CMD_SET_BGO_CALLBACK */
typedef struct _flash_interrupt_config
{
    void    (*pcallback)(void *);
    uint8_t int_priority;
} flash_interrupt_config_t;

/*Event type for ISR callback*/
typedef struct
{
    flash_interrupt_event_t event;      /* Which Flash event caused this interrupt */
} flash_int_cb_args_t;

#endif


#ifdef FLASH_HAS_BOOT_SWAP
/* Control() FLASH_CMD_SWAPFLAG_GET
 * Startup area select for reset
 * FSCMR.SASMF, FAW/FAWMON.BTFLG
  */
#define FLASH_STARTUP_SETTING_ALTERNATE     (0)
#define FLASH_STARTUP_SETTING_DEFAULT       (1)

/* Control() FLASH_CMD_SWAPSTATE_GET/SET
 * Startup area select for temporary read/write
 * FISR.SAS, FSUACR.SAS
 */
#define FLASH_SAS_SWAPFLG       (0)     // The start-up area temporarily set according to the swap flag
#define FLASH_SAS_EXTRA         (0)     // (same as above; here for backwards compatibility)
#define FLASH_SAS_DEFAULT       (2)     // The start-up area temporarily set to the default area
#define FLASH_SAS_ALTERNATE     (3)     // The start-up area temporarily set to the alternate area
#define FLASH_SAS_SWITCH_AREA   (4)     // Command to temporarily switch to the other startup area

#endif


#ifdef FLASH_HAS_APP_SWAP
/* Control() FLASH_CMD_BANK_GET: Gets bank address at next reset. Running app is at FFF00000. */
typedef enum _flash_bank
{
    FLASH_BANK1          = 0,           // BANKSEL.BANKSWP is 000
    FLASH_BANK0          = 1,           // BANKSEL.BANKSWP is 111
    FLASH_BANK0_FFE00000 = 0,           // BANKSEL.BANKSWP is 000
    FLASH_BANK1_FFF00000 = 0,           // BANKSEL.BANKSWP is 000
    FLASH_BANK0_FFF00000 = 1,           // BANKSEL.BANKSWP is 111
    FLASH_BANK1_FFE00000 = 1            // BANKSEL.BANKSWP is 111
} flash_bank_t;

#endif


#ifdef FLASH_HAS_CF_ACCESS_WINDOW

/* Control() FLASH_CMD_ACCESSWINDOW_SET/GET */
typedef struct _flash_access_window_config
{
    uint32_t start_addr;                /* start address of code flash Access Window */
    uint32_t end_addr;                  /* end address of code flash Access Window */
} flash_access_window_config_t;

#endif


#ifdef FLASH_HAS_SEQUENTIAL_CF_BLOCKS_LOCK
#include "r_flash_type3_if.h"
/* Control() FLASH_CMD_LOCKBIT_READ, FLASH_CMD_LOCKBIT_WRITE */
typedef struct _flash_lockbit_config
{
    flash_block_address_t block_start_address;
    flash_res_t           result;       /* Returned by API when using FLASH_CMD_LOCKBIT_READ */
    uint32_t              num_blocks;   /* Set by user for FLASH_CMD_LOCKBIT_WRITE */
} flash_lockbit_config_t;

#endif


#if FLASH_HAS_NON_CACHED_RANGES

#define FLASH_NON_CACHED_MASK_IF    (0x02)      // do not cache fast instruction fetching by the CPU
#define FLASH_NON_CACHED_MASK_OA    (0x04)      // do not cache fast operand access by the CPU
#define FLASH_NON_CACHED_MASK_DM    (0x08)      // do not cache fast access to data by bus masters other than CPU

typedef enum _flash_no_cache_size
{
    FLASH_NON_CACHED_16_BYTES   = 0x10,
    FLASH_NON_CACHED_32_BYTES   = 0x20,
    FLASH_NON_CACHED_64_BYTES   = 0x40,
    FLASH_NON_CACHED_128_BYTES  = 0x80,
    FLASH_NON_CACHED_256_BYTES  = 0x100,
    FLASH_NON_CACHED_512_BYTES  = 0x200,
    FLASH_NON_CACHED_1_KBYTE    = 0x400,
    FLASH_NON_CACHED_2_KBYTES   = 0x800,
    FLASH_NON_CACHED_4_KBYTES   = 0x1000,
    FLASH_NON_CACHED_8_KBYTES   = 0x2000,
    FLASH_NON_CACHED_16_KBYTES  = 0x4000,
    FLASH_NON_CACHED_32_KBYTES  = 0x8000,
    FLASH_NON_CACHED_64_KBYTES  = 0x10000,
    FLASH_NON_CACHED_128_KBYTES = 0x20000,
    FLASH_NON_CACHED_256_KBYTES = 0x40000,
    FLASH_NON_CACHED_512_KBYTES = 0x80000,
    FLASH_NON_CACHED_1_MBYTE    = 0x100000,
    FLASH_NON_CACHED_2_MBYTE    = 0x200000
} flash_non_cached_size_t;

typedef struct _flash_non_cached
{
    uint32_t                type_mask;
    uint32_t                start_addr;     // must be on 16-byte boundary
    flash_non_cached_size_t size;           // number bytes to not cache
} flash_non_cached_t;

#endif


#if (FLASH_TYPE == FLASH_TYPE_1)
#include "r_flash_type1_if.h"

#elif (FLASH_TYPE == FLASH_TYPE_3)
#include "r_flash_type3_if.h"

typedef union _flash_control_arg
{
    flash_lockbit_config_t      lockbit_cmd;
    flash_interrupt_config_t    bgo_cmd;
} flash_control_arg_t;

#elif (FLASH_TYPE == FLASH_TYPE_4)
#include "r_flash_type4_if.h"

#elif (FLASH_TYPE == FLASH_TYPE_5)
#include "r_flash_type5_if.h"
#endif


/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
flash_err_t R_FLASH_Open(void);
flash_err_t R_FLASH_Close(void);
flash_err_t R_FLASH_Write(uint32_t src_address, uint32_t dest_address, uint32_t num_bytes);
flash_err_t R_FLASH_Erase(flash_block_address_t block_start_address, uint32_t num_blocks);
flash_err_t R_FLASH_BlankCheck(uint32_t address, uint32_t num_bytes, flash_res_t *blank_check_result);
flash_err_t R_FLASH_Control(flash_cmd_t cmd, void *pcfg);
uint32_t R_FLASH_GetVersion (void);

#endif /* FLASH_INTERFACE_HEADER_FILE */
