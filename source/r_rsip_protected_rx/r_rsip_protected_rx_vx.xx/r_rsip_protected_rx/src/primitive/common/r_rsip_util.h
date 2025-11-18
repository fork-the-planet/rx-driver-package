/*
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_rsip_util.h
* Description  : RSIP function utility header file.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.10.2024 1.00     First Release.
*         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
*         :                     Revised key management specification
***********************************************************************************************************************/

#ifndef R_RSIP_UTIL_H
#define R_RSIP_UTIL_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>

#if defined(__ICCARM__)
 #include <iccarm_builtin.h>
#elif defined(__ICCRX__)
 #include <machine.h>
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Byte swapping macro */
#define RSIP_PRV_BSWAP_32_C(data)    ((((data) & 0xff000000U) >> 24) | (((data) & 0x00ff0000U) >> 8) | \
                                      (((data) & 0x0000ff00U) << 8) | (((data) & 0x000000ffU) << 24))

/* Endianness */
#if defined(__GNUC__)
 #define RSIP_PRV_LITTLE_ENDIAN    (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#elif defined(__IAR_SYSTEMS_ICC__)
 #define RSIP_PRV_LITTLE_ENDIAN    (__LITTLE_ENDIAN__)
#elif defined(__CCRX__)
 #define RSIP_PRV_LITTLE_ENDIAN    defined(__LIT)
#else
 #error Unsupported compiler.
#endif

/* Changes data endianness to big-endian. */
#if RSIP_PRV_LITTLE_ENDIAN
 #define BSWAP_32BIG_C(data)        RSIP_PRV_BSWAP_32_C(data)
#else
 #define BSWAP_32BIG_C(data)        (data)
#endif

/* Built-in byte swapping function */
#if defined(__GNUC__)
 #define RSIP_PRV_BSWAP_32(data)    __builtin_bswap32(data)
#elif defined(__ICCARM__)
 #define RSIP_PRV_BSWAP_32(data)    __iar_builtin_REV(data)
#elif defined(__CCRX__)
 #define RSIP_PRV_BSWAP_32(data)    _builtin_revl(data)
#elif defined(__ICCRX__)
 #define RSIP_PRV_BSWAP_32(data)    _builtin_revl(data)
#else
 #define RSIP_PRV_BSWAP_32(data)    RSIP_PRV_BSWAP_32_C(data)
#endif

/* Static inline */
#if defined(__GNUC__)
 #if (__RX__)
  #define RSIP_PRV_STATIC_INLINE(func)   inline static __attribute__((always_inline))
 #else
  #define RSIP_PRV_STATIC_INLINE         __attribute__((always_inline)) static inline
 #endif
#elif defined(__IAR_SYSTEMS_ICC__)
 #if (__ICCRX__)
  #define RSIP_PRV_STATIC_INLINE(func)  _Pragma("inline=forced")\
                                        static inline
 #else
   #define RSIP_PRV_STATIC_INLINE       _Pragma("inline=forced") static inline
 #endif
#elif defined(__CCRX__)
 #if !(defined(__cplusplus))
  #define RSIP_PRV_PRAGMA(...)          _Pragma(#__VA_ARGS__)
 #else
  #define RSIP_PRV_PRAGMA(x)
 #endif
  #define RSIP_PRV_STATIC_INLINE(func)  RSIP_PRV_PRAGMA(inline func)\
                                        static
#else
 #define RSIP_PRV_STATIC_INLINE         static inline
#endif

/*
 * Set compiler optimization option for primitive functions.
 * GNU Toolchain: "Os"
 * IAR Embedded Workbench: "size" (enabled only if default optimization level is "high")
 * Other toolchains: no change
 */
#if defined(__GNUC__) && !defined(__CC_ARM) && !defined(__llvm__) // ARM Compiler and Clang do not support
 #define RSIP_PRV_PRIMITIVE_OPTIMIZE    __attribute__((optimize("Os")))
#elif defined(__IAR_SYSTEMS_ICC__)
 #define RSIP_PRV_PRIMITIVE_OPTIMIZE    _Pragma("optimize = size")
#else
 #define RSIP_PRV_PRIMITIVE_OPTIMIZE
#endif

/* Optional attribute */
#if !defined RSIP_PRIMITIVE_ATTR
 #define RSIP_PRIMITIVE_ATTR
#endif

/* Primitive function attributes */
#define RSIP_PRV_PRIMITIVE_FUNC    RSIP_PRV_PRIMITIVE_OPTIMIZE RSIP_PRIMITIVE_ATTR

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Changes data endianness to big-endian.
 *
 * bswap_32big(): For other than const variable. This inline function directly uses ISA.
 *
 * BSWAP_32BIG_C(): For const variable. This macro uses bit shift operation.
 *
 * @param[in] data 32-bit data
 *
 * @return big-endian data
 **********************************************************************************************************************/
RSIP_PRV_STATIC_INLINE(bswap_32big)
uint32_t bswap_32big (uint32_t data)
{
#if RSIP_PRV_LITTLE_ENDIAN
    return RSIP_PRV_BSWAP_32(data);
#else
    return data;
#endif
}

#endif                                 /* R_RSIP_UTIL_H */
