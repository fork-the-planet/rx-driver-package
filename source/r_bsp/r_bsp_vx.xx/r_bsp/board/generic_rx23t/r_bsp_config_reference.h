/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_bsp_config_reference.h
* Device(s)    : RX23T
* Description  : The file r_bsp_config.h is used to configure your BSP. r_bsp_config.h should be included
*                somewhere in your package so that the r_bsp code has access to it. This file (r_bsp_config_reference.h)
*                is just a reference file that the user can use to make their own r_bsp_config.h file.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.09.2015 1.00    First Release
*         : 30.09.2015 1.01    Changed Minor version to 3.01
*         : 13.04.2016 1.02    Added the setting of High Speed On-Chip Oscillator (HOCO).
*                              Added the following macro definition.
*                                - BSP_CFG_MAIN_CLOCK_SOURCE
*                                - BSP_CFG_MOSC_WAIT_TIME
*                                - BSP_CFG_HOCO_WAIT_TIME
*         : 15.05.2017 1.03    Added comments of the RAM capacity.
*         : 01.11.2017 2.00    Added the following macro definition.
*                                - BSP_CFG_STARTUP_DISABLE
*         : 01.07.2018 2.01    Deleted the following macro definition.
*                                - BSP_CFG_USER_BOOT_ENABLE
*         : 27.07.2018 2.02    Deleted the following macro definition.
*                                - BSP_CFG_MCU_PART_VERSION
*                              Added the following macro definition.
*                                - BSP_CFG_FIT_IPL_MAX
*         : 31.10.2018 2.03    Added the following macro definition.
*                                - BSP_CFG_CONFIGURATOR_SELECT
*         : 28.02.2019 3.00    Added the following macro definition.
*                                - BSP_CFG_RTOS_USED
*                              Added support for GNUC and ICCRX.
*                              Fixed coding style.
*                              Deleted the following macro definition.
*                                - BSP_CFG_ROM_CODE_PROTECT_VALUE
*         : 23.07.2019 3.01    Modified comments of the following macro definition.
*                               - BSP_CFG_RTOS_USED : The value '1'(FreeRTOS is used.) is available.
*                              Added the following macro definition.
*                               - BSP_CFG_RTOS_SYSTEM_TIMER
*         : 08.10.2019 3.02    Added the following macro definition.
*                               - BSP_CFG_SWINT_UNIT1_ENABLE
*                               - BSP_CFG_SWINT_TASK_BUFFER_NUMBER
*                               - BSP_CFG_SWINT_IPR_INITIAL_VALUE
*                              Modified comment for added support of Renesas RTOS (RI600V4 or RI600PX).
*                              Added the following macro definition.
*                               - BSP_CFG_RENESAS_RTOS_USED
*         : 29.01.2021 3.03    Added the following macro definition.
*                               - BSP_CFG_SCI_UART_TERMINAL_ENABLE
*                               - BSP_CFG_SCI_UART_TERMINAL_CHANNEL
*                               - BSP_CFG_SCI_UART_TERMINAL_BITRATE
*                               - BSP_CFG_SCI_UART_TERMINAL_INTERRUPT_PRIORITY
*         : 26.02.2021 3.04    Added a comment for Azure RTOS to BSP_CFG_RTOS_USED.
*         : 30.11.2021 4.00    Added the following macro definitions.
*                               - BSP_CFG_MAIN_CLOCK_OSCILLATE_ENABLE
*                               - BSP_CFG_HOCO_OSCILLATE_ENABLE
*                               - BSP_CFG_LOCO_OSCILLATE_ENABLE
*                               - BSP_CFG_IWDT_CLOCK_OSCILLATE_ENABLE
*                               - BSP_CFG_CONFIGURATOR_VERSION
*                               - BSP_CFG_CPLUSPLUS
*                              Changed initial value of the following macro definitions.
*                               - BSP_CFG_MCU_PART_GROUP
*                               - BSP_CFG_MCU_PART_SERIES
*         : 11.02.2022 4.01    Changed initial value of the following macro definitions.
*                               - BSP_CFG_SWINT_UNIT1_ENABLE
*         : 25.11.2022 4.02    Added the following macro definition.
*                               - BSP_CFG_EXPANSION_RAM_ENABLE
*         : 28.02.2023 4.03    Modified comment.
*         : 21.11.2023 4.04    Added the following macro definitions.
*                               - BSP_CFG_BUS_PRIORITY_INITIALIZE_ENABLE
*                               - BSP_CFG_MEMORY_BUS1_PRIORITY
*                               - BSP_CFG_MEMORY_BUS2_PRIORITY
*                               - BSP_CFG_INTERNAL_PERIPHERAL_BUS1_PRIORITY
*                               - BSP_CFG_INTERNAL_PERIPHERAL_BUS2_3_PRIORITY
*                               - BSP_CFG_INTERNAL_PERIPHERAL_BUS4_PRIORITY
*                               - BSP_CFG_INTERNAL_PERIPHERAL_BUS6_PRIORITY
*         : 26.02.2025 4.05    Changed the disclaimer.
***********************************************************************************************************************/

#ifndef R_BSP_CONFIG_REF_HEADER_FILE
#define R_BSP_CONFIG_REF_HEADER_FILE

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/

/* NOTE:
   The default settings are the same as when using RSKRX23T.
   Change to the settings for the user board.
*/

/* Start up select
   0 = Enable BSP startup program.
   1 = Disable BSP startup program. (e.g. Using user startup program.)
   NOTE: This setting is available only when using CCRX. */
#define BSP_CFG_STARTUP_DISABLE (0)

/* Enter the product part number for your MCU. This information will be used to obtain information about your MCU such 
   as package and memory size.
   To help parse this information, the part number will be defined using multiple macros.
   R 5 F 52 3T 5 A D FL
   | | | |  |  | | | |  Macro Name                      Description
   | | | |  |  | | | |__BSP_CFG_MCU_PART_PACKAGE      = Package type, number of pins, and pin pitch
   | | | |  |  | | |____not used                      = Products with wide temperature range (D:-40-85C G:-40-105C)
   | | | |  |  | |______not used                      = 5V
   | | | |  |  |________BSP_CFG_MCU_PART_MEMORY_SIZE  = ROM, RAM, and Data Flash Capacity
   | | | |  |___________BSP_CFG_MCU_PART_GROUP        = Group name
   | | | |______________BSP_CFG_MCU_PART_SERIES       = Series name
   | | |________________BSP_CFG_MCU_PART_MEMORY_TYPE  = Type of memory (Flash)
   | |__________________not used                      = Renesas MCU
   |____________________not used                      = Renesas semiconductor product.
*/

/* Package type. Set the macro definition based on values below:
   Character(s) = Value for macro = Package Type/Number of Pins/Pin Pitch
   FM           = 0x2             = LFQFP/64/0.50
   FD           = 0xB             = LQFP /52/0.65
   FL           = 0x6             = LFQFP/48/0.50
*/

#define BSP_CFG_MCU_PART_PACKAGE        (0x2)

/* ROM, RAM, and Data Flash Capacity.
   Character(s) = Value for macro = ROM Size/Ram Size
   5            = 0x5             = 128KB/12KB
   3            = 0x3             =  64KB/12KB
   NOTE: The RAM areas are not contiguous.
*/
#define BSP_CFG_MCU_PART_MEMORY_SIZE    (0x5)

/* Group name.
   Character(s) = Description
   3T           = RX23T Group
*/
#define BSP_CFG_MCU_PART_GROUP          "RX23T"

/* Series name.
   Character(s) = Description
   52           = RX200 Series
*/
#define BSP_CFG_MCU_PART_SERIES         "RX200"

/* Memory type.
   Character(s) = Value for macro = Description
   F            = 0x0             = Flash memory version
*/
#define BSP_CFG_MCU_PART_MEMORY_TYPE    (0x0)

/* Whether to use 1 stack or 2. RX MCUs have the ability to use 2 stacks: an interrupt stack and a user stack.
 * When using 2 stacks the user stack will be used during normal user code. When an interrupt occurs the CPU
 * will automatically shift to using the interrupt stack. Having 2 stacks can make it easier to figure out how
 * much stack space to allocate since the user does not have to worry about always having enough room on the
 * user stack for if-and-when an interrupt occurs. Some users will not want 2 stacks though because it is not
 * needed in all applications and can lead to wasted RAM (i.e. space in between stacks that is not used).
 * If only 1 stack is used then the interrupt stack is the one that will be used. If 1 stack is chosen then
 * the user may want to remove the 'SU' section from the linker sections to remove any linker warnings.
 *
 * 0 = Use 1 stack. Disable user stack. User stack size set below will be ignored.
 * 1 = Use 2 stacks. User stack and interrupt stack will both be used.
 * NOTE: This setting is available only when using CCRX and GNUC.
 *       This is invalid when using Renesas RTOS with CCRX.
 */
#define BSP_CFG_USER_STACK_ENABLE       (1)

/* If only 1 stack is chosen using BSP_CFG_USER_STACK_ENABLE then no RAM will be allocated for the user stack. */
#if BSP_CFG_USER_STACK_ENABLE == 1
/* User Stack size in bytes. 
 * NOTE: This setting is available only when using CCRX and GNUC.
 *       This is invalid when using Renesas RTOS with CCRX. */
#define BSP_CFG_USTACK_BYTES            (0x400)
#endif

/* Interrupt Stack size in bytes.
   NOTE: This setting is available only when using CCRX and GNUC. */
#define BSP_CFG_ISTACK_BYTES            (0x200)

/* Heap size in bytes.
   To disable the heap you must follow these steps:
   1) Set this macro (BSP_CFG_HEAP_BYTES) to 0.
   2) Set the macro BSP_CFG_IO_LIB_ENABLE to 0.
   3) Disable stdio from being built into the project library. This is done by going into the Renesas RX Toolchain 
      settings and choosing the Standard Library section. After that choose 'Contents' in e2 studio.
      This will present a list of modules that can be included. Uncheck the box for stdio.h.
   NOTE: This setting is available only when using CCRX and GNUC. */
#define BSP_CFG_HEAP_BYTES              (0x400)

/* Initializes C input & output library functions.
   0 = Disable I/O library initialization in resetprg.c. If you are not using stdio then use this value.
   1 = Enable I/O library initialization in resetprg.c. This is default and needed if you are using stdio.
   NOTE: This setting is available only when using CCRX. */
#define BSP_CFG_IO_LIB_ENABLE           (1)

/* If desired the user may redirect the stdio charget() and/or charput() functions to their own respective functions
   by enabling below and providing and replacing the my_sw_... function names with the names of their own functions. */
#define BSP_CFG_USER_CHARGET_ENABLED    (0)
#define BSP_CFG_USER_CHARGET_FUNCTION     my_sw_charget_function

#define BSP_CFG_USER_CHARPUT_ENABLED    (0)
#define BSP_CFG_USER_CHARPUT_FUNCTION     my_sw_charput_function

/* After reset MCU will operate in Supervisor mode. To switch to User mode, set this macro to '1'. For more information
   on the differences between these 2 modes see the CPU >> Processor Mode section of your MCU's hardware manual.
   0 = Stay in Supervisor mode.
   1 = Switch to User mode.
   NOTE: This is invalid when using Renesas RTOS with CCRX.
*/
#define BSP_CFG_RUN_IN_USER_MODE        (0)

/* Set your desired ID code. NOTE, leave at the default (all 0xFF's) if you do not wish to use an ID code. If you set 
   this value and program it into the MCU then you will need to remember the ID code because the debugger will ask for 
   it when trying to connect. Note that the E1/E20 will ignore the ID code when programming the MCU during debugging.
   If you set this value and then forget it then you can clear the ID code by connecting up in serial boot mode using 
   FDT. The ID Code is 16 bytes long. The macro below define the ID Code in 4-byte sections. */
/* Lowest 4-byte section, address 0xFFFFFFA0. From MSB to LSB: Control Code, ID code 1, ID code 2, ID code 3. */
#define BSP_CFG_ID_CODE_LONG_1          (0xFFFFFFFF)
/* 2nd ID Code section, address 0xFFFFFFA4. From MSB to LSB: ID code 4, ID code 5, ID code 6, ID code 7. */
#define BSP_CFG_ID_CODE_LONG_2          (0xFFFFFFFF)
/* 3rd ID Code section, address 0xFFFFFFA8. From MSB to LSB: ID code 8, ID code 9, ID code 10, ID code 11. */
#define BSP_CFG_ID_CODE_LONG_3          (0xFFFFFFFF)
/* 4th ID Code section, address 0xFFFFFFAC. From MSB to LSB: ID code 12, ID code 13, ID code 14, ID code 15. */
#define BSP_CFG_ID_CODE_LONG_4          (0xFFFFFFFF)

/* Select whether to oscillate the Main Clock Oscillator.
   0 = Stop Oscillating the Main Clock.
   1 = Enable oscillating the Main Clock. (default)
*/
#define BSP_CFG_MAIN_CLOCK_OSCILLATE_ENABLE    (1)

/* Select whether to oscillate the High Speed On-Chip Oscillator (HOCO).
   0 = Stop Oscillating the HOCO. (default)
   1 = Enable Oscillating the HOCO.
*/
#define BSP_CFG_HOCO_OSCILLATE_ENABLE          (0)

/* Select whether to oscillate the Low Speed On-Chip Oscillator (LOCO).
   0 = Stop Oscillating the LOCO. (default)
   1 = Enable Oscillating the LOCO.
*/
#define BSP_CFG_LOCO_OSCILLATE_ENABLE          (0)

/* Select whether to oscillate the IWDT-Dedicated On-Chip Oscillator (IWDT).
   0 = Stop Oscillating the IWDT Clock. (default)
   1 = Enable Oscillating the IWDT Clock.
*/
#define BSP_CFG_IWDT_CLOCK_OSCILLATE_ENABLE    (0)

/* Clock source select (CKSEL).
   0 = Low Speed On-Chip Oscillator  (LOCO)
   1 = High Speed On-Chip Oscillator (HOCO)
   2 = Main Clock Oscillator
   3 = Sub-Clock Oscillator                   (N/A for RX23T)
   4 = PLL Circuit
*/
#define BSP_CFG_CLOCK_SOURCE            (4)

/* Main clock Oscillator Switching (MOSEL).
   0 = Resonator
   1 = External clock input
*/
#define BSP_CFG_MAIN_CLOCK_SOURCE       (0)

/* The input clock frequency is specified and then the system clocks are set by specifying the multipliers used. The
   multiplier settings are used to set the clock registers in resetprg.c. If a 20MHz clock is used and the 
   ICLK is 50MHz, PCLKB is 25MHz, FCLK is 50MHz, PCLKD is 50MHz, and BCLK is 25MHz then the 
   settings would be:

   BSP_CFG_XTAL_HZ  = 20000000
   BSP_CFG_PLL_DIV  = 2        (divide by 2)
   BSP_CFG_PLL_MUL  = 4        (10MHz x 4 = 40MHz)
   BSP_CFG_ICK_DIV  = 1      : System Clock (ICLK)        = 
                               (((BSP_CFG_XTAL_HZ/BSP_CFG_PLL_DIV) * BSP_CFG_PLL_MUL) / BSP_CFG_ICK_DIV)  = 40MHz
   BSP_CFG_PCKA_DIV = 1      : Peripheral Clock B (PCLKA) = 
                               (((BSP_CFG_XTAL_HZ/BSP_CFG_PLL_DIV) * BSP_CFG_PLL_MUL) / BSP_CFG_PCKA_DIV) = 40MHz
   BSP_CFG_PCKB_DIV = 1      : Peripheral Clock B (PCLKB) = 
                               (((BSP_CFG_XTAL_HZ/BSP_CFG_PLL_DIV) * BSP_CFG_PLL_MUL) / BSP_CFG_PCKB_DIV) = 40MHz
   BSP_CFG_PCKD_DIV = 1      : Peripheral Clock D (PCLKD) = 
                               (((BSP_CFG_XTAL_HZ/BSP_CFG_PLL_DIV) * BSP_CFG_PLL_MUL) / BSP_CFG_PCKB_DIV) = 40MHz
   BSP_CFG_FCK_DIV  = 2      : Flash IF Clock (FCLK)      = 
                               (((BSP_CFG_XTAL_HZ/BSP_CFG_PLL_DIV) * BSP_CFG_PLL_MUL) / BSP_CFG_FCK_DIV)  = 20MHz
*/
/* Input clock frequency in Hz (XTAL or EXTAL). */
#define BSP_CFG_XTAL_HZ                 (20000000)

/* PLL Input Frequency Divider Select (PLIDIV).
   Available divisors = /1 (no division), /2, /4
*/
#define BSP_CFG_PLL_DIV                 (2)

/* PLL Frequency Multiplication Factor Select (STC).
   Available multipliers = x4, x4.5, x5, x5.5, x6, x6.5, x7, x7.5, x8, x8.5, x9, x9.5, x10
*/
#define BSP_CFG_PLL_MUL                 (4)

/* System Clock Divider (ICK).
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define BSP_CFG_ICK_DIV                 (1)

/* Peripheral Module Clock A Divider (PCKA).
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define BSP_CFG_PCKA_DIV                (1)

/* Peripheral Module Clock B Divider (PCKB).
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define BSP_CFG_PCKB_DIV                (1)

/* Peripheral Module Clock D Divider (PCKD).
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define BSP_CFG_PCKD_DIV                (1)

/* Flash IF Clock Divider (FCK).
   Available divisors = /1 (no division), /2, /4, /8, /16, /32, /64
*/
#define BSP_CFG_FCK_DIV                 (2)

/* Main Clock Oscillator Wait Time (MOSCWTCR).
   0x00 = Wait time = 2 cycles (0.5 us)
   0x01 = Wait time = 1024 cycles (256 us)
   0x02 = Wait time = 2048 cycles (512 us)
   0x03 = Wait time = 4096 cycles (1.024 ms)
   0x04 = Wait time = 8192 cycles (2.048 ms)
   0x05 = Wait time = 16384 cycles (4.096 ms)
   0x06 = Wait time = 32768 cycles (8.192 ms)
   0x07 = Wait time = 65536 cycles (16.384 ms)
   Settings other than above are prohibited.
   Wait time when LOCO = 4.0 MHz (0.25 us, TYP.)
   NOTE: When the main clock is externally input, set these bits to 00000b because the oscillation
         stabilization time is not required.
*/
#define BSP_CFG_MOSC_WAIT_TIME          (0x04)

/* High-Speed On-Chip Oscillator Wait Time (HOCOWTCR).
   0x04(100b) = Wait time = 78 cycles
   0x05(101b) = Wait time = 142 cycles
   Settings other than above are prohibited.
*/
#define BSP_CFG_HOCO_WAIT_TIME          (0x05)

/* Configure IWDT settings.
   OFS0 - Option Function Select Register 0
   b31:b15 Reserved (set to 1)
   b14     IWDTSLCSTP - IWDT Sleep Mode Count Stop Control - (0=can't stop count, 1=stop w/some low power modes)
   b13     Reserved (set to 1)
   b12     IWDTRSTIRQS - IWDT Reset Interrupt Request - What to do on underflow (0=take interrupt, 1=reset MCU)
   b11:b10 IWDTRPSS - IWDT Window Start Position Select - (0=25%, 1=50%, 2=75%, 3=100%,don't use)
   b9:b8   IWDTRPES - IWDT Window End Position Select - (0=75%, 1=50%, 2=25%, 3=0%,don't use)
   b7:b4   IWDTCKS - IWDT Clock Frequency Division Ratio - (0=none, 2=/16, 3 = /32, 4=/64, 0xF=/128, 5=/256)
   b3:b2   IWDTTOPS - IWDT Timeout Period Select - (0=128 cycles, 1=512, 2=1024, 3=2048)
   b1      IWDTSTRT - IWDT Start Mode Select - (0=auto-start after reset, halt after reset)
   Default value is 0xFFFFFFFF.
*/
#define BSP_CFG_OFS0_REG_VALUE  (0xFFFFFFFF)

/* Configure whether voltage detection 0 circuit.
   OFS1 - Option Function Select Register 1
   b31:b9 Reserved (set to 1)
   b8     HOCOEN - Choose to enable/disable HOCO Oscillation Enable after a reset (0=enable, 1=disable)
   b7:b3  Reserved (set to 1)
   b2     LVDAS - Choose to enable/disable Voltage Detection 0 Circuit after a reset (0=enable, 1=disable)
   b1:b0  VDSEL - Voltage Detection 0 Level Select (0=3.84V, 1=2.82V, 2=2.51V, 3=1.90V)
   Default value is 0xFFFFFFFF.
*/
#define BSP_CFG_OFS1_REG_VALUE  (0xFFFFFFFF)

/* This macro lets other modules no if a RTOS is being used.
   0 = RTOS is not used.
   1 = FreeRTOS is used.
   2 = embOS is used.(This is not available.)
   3 = MicroC_OS is used.(This is not available.)
   4 = Renesas ITRON OS (RI600V4 or RI600PX) is used.
   5 = Azure RTOS is used.
*/
#define BSP_CFG_RTOS_USED               (0)

/* This macro is used to select which Renesas ITRON OS.
   0 = RI600V4 is used.
   1 = RI600PX is used.
*/
#define BSP_CFG_RENESAS_RTOS_USED       (0)

/* This macro is used to select which CMT channel used for system timer of RTOS.
 * The setting of this macro is only valid if the macro BSP_CFG_RTOS_USED is set to a value other than 0. */
#if BSP_CFG_RTOS_USED != 0
/* Setting value.
 * 0      = CMT channel 0 used for system timer of RTOS (recommended to be used for RTOS).
 * 1      = CMT channel 1 used for system timer of RTOS.
 * 2      = CMT channel 2 used for system timer of RTOS.
 * 3      = CMT channel 3 used for system timer of RTOS.
 * Others = Invalid.
 * NOTE: This is invalid when using Renesas RTOS with CCRX.
 */
#define BSP_CFG_RTOS_SYSTEM_TIMER       (0)
#endif

/* By default modules will use global locks found in mcu_locks.c. If the user is using a RTOS and would rather use its
   locking mechanisms then they can change this macro.
   NOTE: If '1' is chosen for this macro then the user must also change the next macro 'BSP_CFG_USER_LOCKING_TYPE'.
   0 = Use default locking (non-RTOS)
   1 = Use user defined locking mechanism.
*/
#define BSP_CFG_USER_LOCKING_ENABLED    (0)

/* If the user decides to use their own locking mechanism with FIT modules then they will need to redefine the typedef
   that is used for the locks. If the user is using a RTOS then they would likely redefine the typedef to be 
   a semaphore/mutex type of their RTOS. Use the macro below to set the type that will be used for the locks.
   NOTE: If BSP_CFG_USER_LOCKING_ENABLED == 0 then this typedef is ignored.
   NOTE: Do not surround the type with parentheses '(' ')'.
*/
#define BSP_CFG_USER_LOCKING_TYPE       bsp_lock_t

/* If the user decides to use their own locking mechanism with FIT modules then they will need to define the functions
   that will handle the locking and unlocking. These functions should be defined below.
   If BSP_CFG_USER_LOCKING_ENABLED is != 0:
   R_BSP_HardwareLock(mcu_lock_t hw_index) will call BSP_CFG_USER_LOCKING_HW_LOCK_FUNCTION(mcu_lock_t hw_index)
   R_BSP_HardwareUnlock(mcu_lock_t hw_index) will call BSP_CFG_USER_LOCKING_HW_UNLOCK_FUNCTION(mcu_lock_t hw_index)
       NOTE:With these functions the index into the array holding the global hardware locks is passed as the parameter.
   R_BSP_SoftwareLock(BSP_CFG_USER_LOCKING_TYPE * plock) will call 
   BSP_CFG_USER_LOCKING_SW_LOCK_FUNCTION(BSP_CFG_USER_LOCKING_TYPE * plock)
   R_BSP_SoftwareUnlock(BSP_CFG_USER_LOCKING_TYPE * plock) will call 
   BSP_CFG_USER_LOCKING_SW_UNLOCK_FUNCTION(BSP_CFG_USER_LOCKING_TYPE * plock)
       NOTE:With these functions the actual address of the lock to use is passed as the parameter.
   NOTE: These functions must return a boolean. If lock was obtained or released successfully then return true. Else, 
         return false.
   NOTE: If BSP_CFG_USER_LOCKING_ENABLED == 0 then this typedef is ignored.
   NOTE: Do not surround the type with parentheses '(' ')'.
*/
#define BSP_CFG_USER_LOCKING_HW_LOCK_FUNCTION      my_hw_locking_function
#define BSP_CFG_USER_LOCKING_HW_UNLOCK_FUNCTION    my_hw_unlocking_function
#define BSP_CFG_USER_LOCKING_SW_LOCK_FUNCTION      my_sw_locking_function
#define BSP_CFG_USER_LOCKING_SW_UNLOCK_FUNCTION    my_sw_unlocking_function

/* If the user would like to determine if a warm start reset has occurred, then they may enable one or more of the
   following callback definitions AND provide a call back function name for the respective callback
   function (to be defined by the user). Setting BSP_CFG_USER_WARM_START_CALLBACK_PRE_INITC_ENABLED = 1 will result
   in a callback to the user defined my_sw_warmstart_prec_function just prior to the initialization of the C
   runtime environment by resetprg.
   Setting BSP_CFG_USER_WARM_START_CALLBACK_POST_INITC_ENABLED = 1 will result in a callback to the user defined
   my_sw_warmstart_postc_function just after the initialization of the C runtime environment by resetprg.
*/
#define BSP_CFG_USER_WARM_START_CALLBACK_PRE_INITC_ENABLED    (0)
#define BSP_CFG_USER_WARM_START_PRE_C_FUNCTION     my_sw_warmstart_prec_function

#define BSP_CFG_USER_WARM_START_CALLBACK_POST_INITC_ENABLED    (0)
#define BSP_CFG_USER_WARM_START_POST_C_FUNCTION    my_sw_warmstart_postc_function

/* By default FIT modules will check input parameters to be valid. This is helpful during development but some users
   will want to disable this for production code. The reason for this would be to save execution time and code space.
   This macro is a global setting for enabling or disabling parameter checking. Each FIT module will also have its
   own local macro for this same purpose. By default the local macros will take the global value from here though
   they can be overridden. Therefore, the local setting has priority over this global setting. Disabling parameter
   checking should only used when inputs are known to be good and the increase in speed or decrease in code space is 
   needed.
   0 = Global setting for parameter checking is disabled.
   1 = Global setting for parameter checking is enabled (Default).
*/
#define BSP_CFG_PARAM_CHECKING_ENABLE               (1)

/* This macro is used to define the voltage that is supplied to the MCU (Vcc). This macro is defined in millivolts. This
   macro does not actually change anything on the MCU. Some FIT modules need this information so it is defined here. */
#define BSP_CFG_MCU_VCC_MV                          (3300)

/* For some BSP functions, it is necessary to ensure that, while these functions are executing, interrupts from other 
   FIT modules do not occur. By controlling the IPL, these functions disable interrupts that are at or below the 
   specified interrupt priority level.
   This macro sets the IPL. Range is 0x0 - 0xF.
   Please set this macro more than IPR for other FIT module interrupts.
   The default value is 0xF (maximum value).
   Don't change if there is no special processing with higher priority than all fit modules.
*/
#define BSP_CFG_FIT_IPL_MAX                         (0xF)

/* Allow initialization of auto-generated peripheral initialization code by Smart Configurator tool.
   When not using the Smart Configurator,  set the value of BSP_CFG_CONFIGURATOR_SELECT to 0.
   0 = Disabled (default)
   1 = Smart Configurator initialization code used
*/
#define BSP_CFG_CONFIGURATOR_SELECT                 (0)

/* Version number of Smart Configurator.
   This macro definition is updated by Smart Configurator.
*/
#define BSP_CFG_CONFIGURATOR_VERSION                (100)

/* Software Interrupt (SWINT).
   0 = Software interrupt is not used.
   1 = Software interrupt is used.
   NOTE: When this macro is set to 1, the software interrupt is initialized in bsp startup routine. 
*/
#define BSP_CFG_SWINT_UNIT1_ENABLE    (0)

/* Software Interrupt Task Buffer Number.
   For software interrupt, this value is number of buffering user tasks.
   So user can increase this value if user system would have many software interrupt tasks
   and user system has enough buffer. This value requires 9 byte per task.
   NOTE: This setting is common to all units. It can not be set individually. 
         The maximum value is 254.
*/
#define BSP_CFG_SWINT_TASK_BUFFER_NUMBER     (8)

/* Initial value of the software interrupt priority.
   For software interrupt, this value is interrupt priority. Range is 0x0 - 0xF.
   NOTE: This setting is common to all units. It can not be set individually. 
         Please be careful that this setting is the initial value of the interrupt priority register(IPR).
         It is possible to dynamically change the IPR.
*/
#define BSP_CFG_SWINT_IPR_INITIAL_VALUE     (0x1)

/* This macro is used for serial terminal on the board selected by smart configurator.
   0 = SCI UART Terminal is disabled.
   1 = SCI UART Terminal is enabled.
*/
#define BSP_CFG_SCI_UART_TERMINAL_ENABLE         (0)

/* This macro is channel number for serial terminal.
*/
#define BSP_CFG_SCI_UART_TERMINAL_CHANNEL        (1)

/* This macro is bit-rate for serial terminal.
*/
#define BSP_CFG_SCI_UART_TERMINAL_BITRATE        (115200)

/* This macro is interrupt priority for serial terminal.
   0(low) - 15(high)
*/
#define BSP_CFG_SCI_UART_TERMINAL_INTERRUPT_PRIORITY   (15)

/* This macro is used for C++ project and updated by Smart Configurator.
   0 = This project is a C project.(Not a C++ project).
   1 = This project is a C++ project.
*/
#define BSP_CFG_CPLUSPLUS             (0)

/* Select whether to enable sections of the expansion RAM area.
   0 = Sections of the expansion RAM area is disabled. (default)
   1 = Sections of the expansion RAM area is enabled.
*/
#define BSP_CFG_EXPANSION_RAM_ENABLE  (0)

/* Select whether to enable bus priority initialization.
   0 = Bus priority initialization is disabled.
   1 = Bus priority initialization is enabled.
*/
#define BSP_CFG_BUS_PRIORITY_INITIALIZE_ENABLE      (0)

/* Select the priority order for memory bus 1 (RAM).
   0 = The order of priority is fixed.
   1 = The order of priority is toggled.
*/
#define BSP_CFG_MEMORY_BUS1_PRIORITY                (0)

/* Select the priority order for memory bus 2 (ROM).
   0 = The order of priority is fixed.
   1 = The order of priority is toggled.
*/
#define BSP_CFG_MEMORY_BUS2_PRIORITY                (0)

/* Select the priority order for internal peripheral bus 1.
   0 = The order of priority is fixed.
   1 = The order of priority is toggled.
*/
#define BSP_CFG_INTERNAL_PERIPHERAL_BUS1_PRIORITY   (0)

/* Select the priority order for internal peripheral buses 2 and 3.
   0 = The order of priority is fixed.
   1 = The order of priority is toggled.
*/
#define BSP_CFG_INTERNAL_PERIPHERAL_BUS2_3_PRIORITY (0)

/* Select the priority order for internal peripheral bus 4.
   0 = The order of priority is fixed.
   1 = The order of priority is toggled.
*/
#define BSP_CFG_INTERNAL_PERIPHERAL_BUS4_PRIORITY   (0)

/* Select the priority order for internal peripheral bus 6.
   0 = The order of priority is fixed.
   1 = The order of priority is toggled.
*/
#define BSP_CFG_INTERNAL_PERIPHERAL_BUS6_PRIORITY   (0)

#endif /* R_BSP_CONFIG_REF_HEADER_FILE */

