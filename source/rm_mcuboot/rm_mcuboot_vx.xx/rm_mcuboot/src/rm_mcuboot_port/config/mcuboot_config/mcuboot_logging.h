/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : mcuboot_logging.h
 * Version      : 1.0
 * Description  : This is a header file used by the logging module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *           21.04.2025 1.00    First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "mcuboot_config/mcuboot_config.h"
#if defined(MCUBOOT_LOG_LEVEL)
#include <stdio.h>
#endif

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef MCUBOOT_LOGGING_H
#define MCUBOOT_LOGGING_H

#define MCUBOOT_LOG_LEVEL_OFF        (0)
#define MCUBOOT_LOG_LEVEL_ERROR      (1)
#define MCUBOOT_LOG_LEVEL_WARNING    (2)
#define MCUBOOT_LOG_LEVEL_INFO       (3)
#define MCUBOOT_LOG_LEVEL_DEBUG      (4)

/*
 * The compiled log level determines the maximum level that can be
 * printed.
 */

#define MCUBOOT_LOG_MODULE_DECLARE(domain)  /* ignore */
#define MCUBOOT_LOG_MODULE_REGISTER(domain) /* ignore */

#if defined(__CCRX__)
#if (MCUBOOT_LOG_LEVEL >= MCUBOOT_LOG_LEVEL_ERROR)
#define MCUBOOT_LOG_ERR(...)          CCRX_PRINT_LOG_ERR(__VA_ARGS__, "")
#define CCRX_PRINT_LOG_ERR(_fmt, ...) printf("[ERR] " _fmt "\r\n", __VA_ARGS__)
#else
#define MCUBOOT_LOG_ERR(...)          IGNORE(__VA_ARGS__)
#endif

#if (MCUBOOT_LOG_LEVEL >= MCUBOOT_LOG_LEVEL_WARNING)
#define MCUBOOT_LOG_WRN(...)          CCRX_PRINT_LOG_WRN(__VA_ARGS__, "")
#define CCRX_PRINT_LOG_WRN(_fmt, ...) printf("[WRN] " _fmt "\r\n", __VA_ARGS__)
#else
#define MCUBOOT_LOG_WRN(...)          IGNORE(__VA_ARGS__)
#endif

#if (MCUBOOT_LOG_LEVEL >= MCUBOOT_LOG_LEVEL_INFO)
#define MCUBOOT_LOG_INF(...)          CCRX_PRINT_LOG_INF(__VA_ARGS__, "")
#define CCRX_PRINT_LOG_INF(_fmt, ...) printf("[INF] " _fmt "\r\n", __VA_ARGS__)
#else
#define MCUBOOT_LOG_INF(...)          IGNORE(__VA_ARGS__)
#endif

#if (MCUBOOT_LOG_LEVEL >= MCUBOOT_LOG_LEVEL_DEBUG)
#define MCUBOOT_LOG_DBG(...)          CCRX_PRINT_LOG_DBG(__VA_ARGS__, "")
#define CCRX_PRINT_LOG_DBG(_fmt, ...) printf("[DBG] " _fmt "\r\n", __VA_ARGS__)
#else
#define MCUBOOT_LOG_DBG(...)          IGNORE(__VA_ARGS__)
#endif


#else

#if (MCUBOOT_LOG_LEVEL >= MCUBOOT_LOG_LEVEL_ERROR)
#define MCUBOOT_LOG_ERR(_fmt, ...)    printf("[ERR] " _fmt "\r\n", ## __VA_ARGS__)
#else
#define MCUBOOT_LOG_ERR(...)          IGNORE(__VA_ARGS__)
#endif

#if (MCUBOOT_LOG_LEVEL >= MCUBOOT_LOG_LEVEL_WARNING)
#define MCUBOOT_LOG_WRN(_fmt, ...)    printf("[WRN] " _fmt "\r\n", ## __VA_ARGS__)
#else
#define MCUBOOT_LOG_WRN(...)          IGNORE(__VA_ARGS__)
#endif

#if (MCUBOOT_LOG_LEVEL >= MCUBOOT_LOG_LEVEL_INFO)
#define MCUBOOT_LOG_INF(_fmt, ...)    printf("[INF] " _fmt "\r\n", ## __VA_ARGS__)
#else
#define MCUBOOT_LOG_INF(...)          IGNORE(__VA_ARGS__)
#endif

#if (MCUBOOT_LOG_LEVEL >= MCUBOOT_LOG_LEVEL_DEBUG)
#define MCUBOOT_LOG_DBG(_fmt, ...)    printf("[DBG] " _fmt "\r\n", ## __VA_ARGS__)
#else
#define MCUBOOT_LOG_DBG(...)          IGNORE(__VA_ARGS__)
#endif

#endif
#endif /* MCUBOOT_LOGGING_H */
