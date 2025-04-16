/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/**********************************************************************************************************************
 * @file         mc_lib.h
 * @brief        Arbitrary Length Integer Calculation Library Header File.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "r_stdint.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#ifndef MC_LIB_H
    #define MC_LIB_H


/* **** Section 1: System Parameters **** */

/*
 * (1) Define ONE of the following.
 *       If you use al_lib38.asm, define AL_BASE as 32.
 *       If you use al_libp.c and,
 *         if _INT64_SUPPORT is defined (see inttype.h),
 *     AL_BASE can be 16 or 32. Otherwise, must be 16.
 */

    #if defined (__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)
        #define MC_BASE (16)
    #else
        #define MC_BASE (32)
    #endif /* defined __RL78__ || defined__ICCRL78__ || defined__CCRL__ */

    #if ((MC_BASE != 32) && (MC_BASE != 16))
        #error "Please define MC_BASE 32 or 16 !"
    #endif

/*
 * (2) To declare linkage rules, define the following:
 *     AL_KWD for a special calling rule definition,
 *     AL_EXP and AL_IMP for export/import declaration.
 *
 *     For example, if you use al_lib38.asm with Watcom
 *     C compiler, you must define AL_KWD as __cdecl.
 *     When you create a Microsoft dinamic link library
 *     with Miscrosoft Visual C, define AL_EXT and AL_IMP
 *     as __declspec(dllexport) and __declspec(dllimport).
 */

    #if 1

        #define MC_KWD
        #define MC_EXP
        #define MC_IMP

/*
 * (3) If you want to erase memory when it is freed
 *     for security reasons, define AL_SAFE.
 */

        #define MC_SAFE

/*
 * (4) AL_prnt() / al_prnt() internally call "printf()".
 *     Define AL_PRNT if you need these functions.
 *     Note that implementation of "printf()" is out of
 *     the scope of al library (so you need C library).
 */

        #define MC_PRNT

/*
 * (5) Define AL_RAND if you need al_rndl().
 *     Note that this function uses static variables.
 */
/*
 #define AL_RAND
 */
/*
 * (6) If you cannot use malloc()/free(), define AL_MEMX.
 *     Internal memory routines are automatically called.
 *     To activate these routines, you must additionally
 *     define AL_MEMX_MAXBYTES and AL_MEMX_MAXCALLS.
 *
 *     AL_MEMX_MAXBYTES denotes maximal number of bytes
 *     that one memory allocation function requests.
 *     AL_MEMX_MAXCALLS denotes maximal number of calls
 *     that are allowed to be allocated at a time.
 */

/*
 #define AL_MEMX
 #define AL_MEMX_MAXBYTES 1000
 #define AL_MEMX_MAXCALLS 1000

 #define AL_MEMX_DEBUG
 */

/* **** Do not change the following **** */

/* **** Section 2: Type definition **** */

        #if MC_BASE==16
typedef uint16_t MC;
typedef int16_t mc;
typedef uint32_t MCMC;
        #else
typedef uint32_t MC;
typedef int32_t mc;
/* #ifdef _INT64_SUPPORT */
typedef uint64_t MCMC;
/* #endif */
        #endif /* MC_BASE==16 */

        #if MC_BASE==16
            #define MC_MASK ((uint16_t)0xffffU)
        #else
            #define MC_MASK ((uint32_t)0xffffffffU)
        #endif /* MC_BASE==16 */

/* Structure of the multiple-precision */
typedef struct
{
    uint16_t deg;
    MC       *val;
    uint16_t len;
} MC_int;

/* BIT length of data to be input and output */
        #if !defined(IO_DATA_BIT_LENGTH)
            #define IO_DATA_BIT_LENGTH (2048) /* default value for RX & RL78 */
        #endif

/* BYTE length of data to be input and output */
        #define IO_DATA_BYTE_LENGTH (IO_DATA_BIT_LENGTH/8)

        #define MC_MEMORY_NUM    (2)

        #if MC_BASE==16
            #define MC_MEMORY_SIZE      ((IO_DATA_BYTE_LENGTH*2)+2) /* 514 Bytes */
            #define MC_INT_ARRAY_LENGTH (MC_MEMORY_SIZE/2) /* Length of array of val member of MC_int */
        #else
            #define MC_MEMORY_SIZE      ((IO_DATA_BYTE_LENGTH*2)+4) /* 516 Bytes */
            #define MC_INT_ARRAY_LENGTH (MC_MEMORY_SIZE/4) /* Length of array of val member of MC_int */
        #endif /* MC_BASE==16 */

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
/* **** Section 3 : AL Library Prototype **** */

/* Function Name: MC_init */
/******************************************************************************************************************//**
 * @brief         Initialize Multiple length variables.
 * @warning       none.
 * @retval        none.
 *********************************************************************************************************************/
MC_IMP void MC_init (MC_int *x);

/* Function Name: MC_mall */
/******************************************************************************************************************//**
 * @brief         Allocate memory for multiple-precision variables.
 * @warning       none.
 * @retval        none.
 *********************************************************************************************************************/
MC_IMP MC *MC_mall (uint16_t i, MC_int *x);

/* Function Name: MC_free */
/******************************************************************************************************************//**
 * @brief         Release memory of multiple-precision variables.
 * @warning       none.
 * @retval        none.
 *********************************************************************************************************************/
MC_IMP void MC_free (MC_int *x);

        #ifdef MC_PRNT
/* Function Name: MC_prnt */
/******************************************************************************************************************//**
 * @brief         Display multiple-precision variables.
 * @warning       none.
 * @retval        none.
 *********************************************************************************************************************/
MC_IMP void MC_prnt (int8_t *c, MC_int *x);

        #endif

/* Function Name: MC_byte2mc */
/******************************************************************************************************************//**
 * @brief         Convert from 1-byte array data to MC_int type.
 * @warning       none.
 * @retval        0 Normal end.
 * @retval        -1 Error end.
 *********************************************************************************************************************/
int16_t MC_byte2mc (uint8_t *c, uint16_t len, MC_int *x);

/* Function Name: MC_mc2byte */
/******************************************************************************************************************//**
 * @brief         Convert from MC_int type to 1-byte array data.
 * @warning       none.
 * @retval        0 Normal end.
 * @retval        -1 Error end.
 *********************************************************************************************************************/
int16_t MC_mc2byte (MC_int *x, uint8_t *c, uint16_t *len);

/* Function Name: MC_cmpl */
/******************************************************************************************************************//**
 * @brief         Compare multiple length variables.
 * @warning       none.
 * @retval        1 The comparison destination is large
 * @retval        0 Equivalence
 * @retval        -1 The comparison destination is small
 *********************************************************************************************************************/
int16_t MC_cmpl (MC_int *x, MC_int *y);

/* Function Name: MC_mull */
/******************************************************************************************************************//**
 * @brief         Multiplication of multiple length variables.
 * @warning       none.
 * @retval        none.
 *********************************************************************************************************************/
void MC_mull (MC_int *x, MC_int *y, MC_int *z);

/* Function Name: MC_sqrl */
/******************************************************************************************************************//**
 * @brief         Square of multiple length variables.
 * @warning       none.
 * @retval        none.
 *********************************************************************************************************************/
void MC_sqrl (MC_int *x, MC_int *z);

/* Function Name: MC_reml */
/******************************************************************************************************************//**
 * @brief         Surplus calculation of multiple length variables.
 * @warning       none.
 * @retval        none.
 *********************************************************************************************************************/
void MC_reml (MC_int *x, MC_int *y, MC_int *r);

/* Function Name: MC_rems */
/******************************************************************************************************************//**
 * @brief         Surplus calculation of multiple length variables (When the variable x falls within the range of MC).
 * @warning       none.
 * @retval        MC Remainder operation result.
 *********************************************************************************************************************/
MC MC_rems (MC x, MC_int *y);

/* Function Name: MC_mulm */
/******************************************************************************************************************//**
 * @brief         Multi-precision variable multiplication remainder operation (z = x * y mod m).
 * @warning       none.
 * @retval        -3 Input value is incorrect.
 * @retval        -1 Memory allocation failure.
 * @retval        0 Normal end.
 *********************************************************************************************************************/
int16_t MC_mulm (MC_int *x, MC_int *y, MC_int *z, MC_int *m);

/* Function Name: MC_powm */
/******************************************************************************************************************//**
 * @brief         Modular exponentiation (z = x^y mod m)
 * @warning       none.
 * @retval        -3 Input value is incorrect
 * @retval        -1 Memory allocation failure.
 * @retval        0 Normal end.
 *********************************************************************************************************************/
int16_t MC_powm (MC_int *x, MC_int *y, MC_int *z, MC_int *m, uint8_t *MC_memory0, uint8_t *MC_memory1);

/* **** Section 5 : Miscellaneous Functions **** */

    #endif  /* if 0/1 */

#endif /* MC_LIB_H */

