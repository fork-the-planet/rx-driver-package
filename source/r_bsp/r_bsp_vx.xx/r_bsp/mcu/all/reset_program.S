;;/*
;;* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
;;*
;;* SPDX-License-Identifier: BSD-3-Clause
;;*/
;;/***********************************************************************************************************************
;;* File Name    : reset_program.asm
;;* Description  : Defines post-reset routines that are used to configure the MCU prior to the main program starting. 
;;*                This is where the program counter starts on power-up or reset.
;;***********************************************************************************************************************/
;;/***********************************************************************************************************************
;;* History : DD.MM.YYYY Version   Description
;;*         : 28.02.2019 1.00      First Release
;;*         : 25.11.2022 1.01      Added initialization processing for expansion RAM area.
;;*         : 26.02.2025 1.02      Changed the disclaimer.
;;***********************************************************************************************************************/

#include "r_bsp_config.h"

    .if __GNUC__

;;reset_program.asm

    .list
    .section .text
    .global _PowerON_Reset_PC  ;;global Start routine
    .global _PowerON_Reset     ;;for backward compatibility

    .extern _PowerON_Reset_PC_Prg  ;;external Power ON Reset main function in RESETPRG.C
    .extern _data
    .extern _mdata
    .extern _ebss
    .extern _bss
    .extern _edata
    .extern _ustack
    .extern _istack
    .extern _exit
#if BSP_CFG_EXPANSION_RAM_ENABLE == 1
    .extern _data_exram
    .extern _mdata_exram
    .extern _ebss_exram
    .extern _bss_exram
    .extern _edata_exram
#endif

_PowerON_Reset_PC :
_PowerON_Reset :
;;initialise user stack pointer
    mvtc    #_ustack,USP

;;initialise interrupt stack pointer
    mvtc    #_istack,ISP

;;jump to Power ON Reset main function in RESETPRG.C
    bra     _PowerON_Reset_PC_Prg

;;init section
    .global __INITSCT
    .type   __INITSCT,@function
__INITSCT:

;;load data section from ROM to RAM
    pushm   r1-r3
    mov     #_mdata,r2      ;;src ROM address of data section in R2
    mov     #_data,r1       ;;dest start RAM address of data section in R1
    mov     #_edata,r3      ;;end RAM address of data section in R3
    sub     r1,r3           ;;size of data section in R3 (R3=R3-R1)
    smovf                   ;;block copy R3 bytes from R2 to R1

#if BSP_CFG_EXPANSION_RAM_ENABLE == 1
;;load data section from ROM to Extra RAM
    mov     #_mdata_exram,r2      ;;src ROM address of data_exram section in R2
    mov     #_data_exram,r1       ;;dest start RAM address of data_exram section in R1
    mov     #_edata_exram,r3      ;;end RAM address of data_exram section in R3
    sub     r1,r3           ;;size of data section in R3 (R3=R3-R1)
    smovf                   ;;block copy R3 bytes from R2 to R1
#endif

;;bss initialisation : zero out bss
    mov    #00h,r2          ;;load R2 reg with zero
    mov    #_ebss, r3       ;;store the end address of bss in R3
    mov    #_bss, r1        ;;store the start address of bss in R1
    sub    r1,r3            ;;size of bss section in R3 (R3=R3-R1)
    sstr.b

#if BSP_CFG_EXPANSION_RAM_ENABLE == 1
;;bss initialisation : zero out bss_exram
    mov    #00h,r2          ;;load R2 reg with zero
    mov    #_ebss_exram, r3       ;;store the end address of bss_exram in R3
    mov    #_bss_exram, r1        ;;store the start address of bss_exram in R1
    sub    r1,r3            ;;size of bss_exram section in R3 (R3=R3-R1)
    sstr.b
#endif

    popm    r1-r3
    rts

#ifdef CPPAPP

;;init global class object
    .global __CALL_INIT
    .type   __CALL_INIT,@function
__CALL_INIT:
    bra      __rx_init

    .global _rx_run_preinit_array
    .type   _rx_run_preinit_array,@function
_rx_run_preinit_array:
    mov     #__preinit_array_start,r1
    mov     #__preinit_array_end,r2
    bra.a   _rx_run_inilist

    .global _rx_run_init_array
    .type   _rx_run_init_array,@function
_rx_run_init_array:
    mov     #__init_array_start,r1
    mov     #__init_array_end,r2
    mov     #4, r3
    bra.a   _rx_run_inilist

    .global _rx_run_fini_array
    .type   _rx_run_fini_array,@function
_rx_run_fini_array:
    mov    #__fini_array_start,r2
    mov    #__fini_array_end,r1
    mov    #-4, r3
    ;;fall through

_rx_run_inilist:
next_inilist:
    cmp     r1,r2
    beq.b   done_inilist
    mov.l   [r1],r4
    cmp     #-1, r4
    beq.b   skip_inilist
    cmp     #0, r4
    beq.b   skip_inilist
    pushm   r1-r3
    jsr     r4
    popm    r1-r3
skip_inilist:
    add     r3,r1
    bra.b   next_inilist
done_inilist:
    rts

    .section    .init,"ax"
    .balign 4

    .global     __rx_init
__rx_init:

    .section    .fini,"ax"
    .balign 4

    .global     __rx_fini
__rx_fini:
    bsr.a   _rx_run_fini_array

    .section .sdata
    .balign 4
    .global __gp
    .weak   __gp
__gp:

    .section .data
    .global ___dso_handle
    .weak   ___dso_handle
___dso_handle:
    .long    0

     .section   .init,"ax"
     bsr.a      _rx_run_preinit_array
     bsr.a      _rx_run_init_array
     rts

    .global     __rx_init_end
__rx_init_end:

    .section    .fini,"ax"

    rts
    .global __rx_fini_end
__rx_fini_end:

#endif

;;call to exit
_exit:
    bra  _loop_here
_loop_here:
    bra _loop_here

    .text

    .endif

    .end

