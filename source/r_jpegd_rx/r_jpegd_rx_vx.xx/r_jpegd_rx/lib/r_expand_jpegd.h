/*
* Copyright (C) 2006-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*******************************************************************************
* File Name     : r_expand_jpegd.h
* Version       :
* Device(s)     :
* Tool-Chain    :
* H/W Platform  :
* Description   : The header file of JPEG File Expand Library
*******************************************************************************/
#ifndef __r_expand_jpegd_h__
#define __r_expand_jpegd_h__

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "r_stdint.h"
#include "r_mw_version.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/* Return Value for library */
#define EXPAND_JPEGD_OK					(0)
#define EXPAND_JPEGD_ERROR_HEADER		(-1)
#define EXPAND_JPEGD_ERROR_DECODE		(-2)
#define EXPAND_JPEGD_NOT_SUPPORT		(-3)
#define EXPAND_JPEGD_ERROR_RST			(-4)
#define EXPAND_JPEGD_ERROR_SOI			(-5)
#define EXPAND_JPEGD_ERROR_EOI			(-6)


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
extern const mw_version_t R_expand_jpegd_version;

void R_init_jpeg(void);
int16_t R_expand_jpeg(uint8_t *input, int32_t fsize, uint16_t *outptr, int32_t offset);
int16_t R_get_info_jpeg(uint8_t *input, int32_t fsize, uint16_t *w, uint16_t *h);

#endif /* __r_expand_jpegd_h__ */
