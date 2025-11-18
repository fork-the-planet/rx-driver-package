/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_RSIP_CM_RX261_IODEFINE_HEADER_FILE
#define R_RSIP_CM_RX261_IODEFINE_HEADER_FILE

#include "r_bsp/platform.h"
#define SCE_BASE    0x0008ba00UL

R_BSP_PRAGMA_UNPACK

struct SCE_Type {
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0000H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0004H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0008H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_000CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0010H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0014H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0018H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_001CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0020H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0024H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0028H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_002CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0030H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0034H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0038H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_003CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0040H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0044H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0048H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_004CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0050H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0054H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0058H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_005CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0060H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0064H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0068H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_006CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0070H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0074H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0078H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_007CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0080H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0084H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0088H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_008CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0090H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0094H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0098H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_009CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00A0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00A4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00A8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00ACH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00B0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00B4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00B8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00BCH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00C0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00C4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00C8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00CCH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00D0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00D4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00D8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00DCH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00E0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00E4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00E8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00ECH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00F0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00F4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00F8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_00FCH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0100H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0104H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0108H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_010CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0110H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0114H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0118H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_011CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0120H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0124H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0128H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_012CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0130H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0134H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0138H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_013CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0140H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0144H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0148H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_014CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0150H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0154H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0158H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_015CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0160H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0164H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0168H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_016CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0170H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0174H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0178H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_017CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0180H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0184H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0188H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_018CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0190H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0194H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_0198H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_019CH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01A0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01A4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01A8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01ACH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01B0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01B4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01B8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01BCH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01C0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01C4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01C8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01CCH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01D0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01D4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01D8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01DCH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01E0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01E4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01E8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01ECH;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01F0H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01F4H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01F8H;
    union {
        unsigned long WORD;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_32(
            unsigned long B31:1,
            unsigned long B30:1,
            unsigned long B29:1,
            unsigned long B28:1,
            unsigned long B27:1,
            unsigned long B26:1,
            unsigned long B25:1,
            unsigned long B24:1,
            unsigned long B23:1,
            unsigned long B22:1,
            unsigned long B21:1,
            unsigned long B20:1,
            unsigned long B19:1,
            unsigned long B18:1,
            unsigned long B17:1,
            unsigned long B16:1,
            unsigned long B15:1,
            unsigned long B14:1,
            unsigned long B13:1,
            unsigned long B12:1,
            unsigned long B11:1,
            unsigned long B10:1,
            unsigned long B9:1,
            unsigned long B8:1,
            unsigned long B7:1,
            unsigned long B6:1,
            unsigned long B5:1,
            unsigned long B4:1,
            unsigned long B3:1,
            unsigned long B2:1,
            unsigned long B1:1,
            unsigned long B0:1
        ) BIT;
    } REG_01FCH;
} ;

#define MSTP_SECURITY   SYSTEM.MSTPCRD.BIT.MSTPD31

// for bit access

/* --------------------------------  SCE.REG_xxxH  -------------------------------- */
#define SCE_REG_0_Pos     0                          /*!< SCE REG_xxxH: bit 0 Position       */
#define SCE_REG_0_Msk     (0x01UL << SCE_REG_0_Pos)  /*!< SCE REG_xxxH: bit 0 Mask           */
#define SCE_REG_1_Pos     1                          /*!< SCE REG_xxxH: bit 1 Position       */
#define SCE_REG_1_Msk     (0x01UL << SCE_REG_1_Pos)  /*!< SCE REG_xxxH: bit 1 Mask           */
#define SCE_REG_2_Pos     2                          /*!< SCE REG_xxxH: bit 2 Position       */
#define SCE_REG_2_Msk     (0x01UL << SCE_REG_2_Pos)  /*!< SCE REG_xxxH: bit 2 Mask           */
#define SCE_REG_3_Pos     3                          /*!< SCE REG_xxxH: bit 3 Position       */
#define SCE_REG_3_Msk     (0x01UL << SCE_REG_3_Pos)  /*!< SCE REG_xxxH: bit 3 Mask           */
#define SCE_REG_4_Pos     4                          /*!< SCE REG_xxxH: bit 4 Position       */
#define SCE_REG_4_Msk     (0x01UL << SCE_REG_4_Pos)  /*!< SCE REG_xxxH: bit 4 Mask           */
#define SCE_REG_5_Pos     5                          /*!< SCE REG_xxxH: bit 5 Position       */
#define SCE_REG_5_Msk     (0x01UL << SCE_REG_5_Pos)  /*!< SCE REG_xxxH: bit 5 Mask           */
#define SCE_REG_6_Pos     6                          /*!< SCE REG_xxxH: bit 6 Position       */
#define SCE_REG_6_Msk     (0x01UL << SCE_REG_6_Pos)  /*!< SCE REG_xxxH: bit 6 Mask           */
#define SCE_REG_7_Pos     7                          /*!< SCE REG_xxxH: bit 7 Position       */
#define SCE_REG_7_Msk     (0x01UL << SCE_REG_7_Pos)  /*!< SCE REG_xxxH: bit 7 Mask           */
#define SCE_REG_8_Pos     8                          /*!< SCE REG_xxxH: bit 8 Position       */
#define SCE_REG_8_Msk     (0x01UL << SCE_REG_8_Pos)  /*!< SCE REG_xxxH: bit 8 Mask           */
#define SCE_REG_9_Pos     9                          /*!< SCE REG_xxxH: bit 9 Position       */
#define SCE_REG_9_Msk     (0x01UL << SCE_REG_9_Pos)  /*!< SCE REG_xxxH: bit 9 Mask           */
#define SCE_REG_10_Pos    10                         /*!< SCE REG_xxxH: bit 10 Position       */
#define SCE_REG_10_Msk    (0x01UL << SCE_REG_10_Pos) /*!< SCE REG_xxxH: bit 10 Mask           */
#define SCE_REG_11_Pos    11                         /*!< SCE REG_xxxH: bit 11 Position       */
#define SCE_REG_11_Msk    (0x01UL << SCE_REG_11_Pos) /*!< SCE REG_xxxH: bit 11 Mask           */
#define SCE_REG_12_Pos    12                         /*!< SCE REG_xxxH: bit 12 Position       */
#define SCE_REG_12_Msk    (0x01UL << SCE_REG_12_Pos) /*!< SCE REG_xxxH: bit 12 Mask           */
#define SCE_REG_13_Pos    13                         /*!< SCE REG_xxxH: bit 13 Position       */
#define SCE_REG_13_Msk    (0x01UL << SCE_REG_13_Pos) /*!< SCE REG_xxxH: bit 13 Mask           */
#define SCE_REG_14_Pos    14                         /*!< SCE REG_xxxH: bit 14 Position       */
#define SCE_REG_14_Msk    (0x01UL << SCE_REG_14_Pos) /*!< SCE REG_xxxH: bit 14 Mask           */
#define SCE_REG_15_Pos    15                         /*!< SCE REG_xxxH: bit 15 Position       */
#define SCE_REG_15_Msk    (0x01UL << SCE_REG_15_Pos) /*!< SCE REG_xxxH: bit 15 Mask           */
#define SCE_REG_16_Pos    16                         /*!< SCE REG_xxxH: bit 16 Position       */
#define SCE_REG_16_Msk    (0x01UL << SCE_REG_16_Pos) /*!< SCE REG_xxxH: bit 16 Mask           */
#define SCE_REG_17_Pos    17                         /*!< SCE REG_xxxH: bit 17 Position       */
#define SCE_REG_17_Msk    (0x01UL << SCE_REG_17_Pos) /*!< SCE REG_xxxH: bit 17 Mask           */
#define SCE_REG_18_Pos    18                         /*!< SCE REG_xxxH: bit 18 Position       */
#define SCE_REG_18_Msk    (0x01UL << SCE_REG_18_Pos) /*!< SCE REG_xxxH: bit 18 Mask           */
#define SCE_REG_19_Pos    19                         /*!< SCE REG_xxxH: bit 19 Position       */
#define SCE_REG_19_Msk    (0x01UL << SCE_REG_19_Pos) /*!< SCE REG_xxxH: bit 19 Mask           */
#define SCE_REG_20_Pos    20                         /*!< SCE REG_xxxH: bit 20 Position       */
#define SCE_REG_20_Msk    (0x01UL << SCE_REG_20_Pos) /*!< SCE REG_xxxH: bit 20 Mask           */
#define SCE_REG_21_Pos    21                         /*!< SCE REG_xxxH: bit 21 Position       */
#define SCE_REG_21_Msk    (0x01UL << SCE_REG_21_Pos) /*!< SCE REG_xxxH: bit 21 Mask           */
#define SCE_REG_22_Pos    22                         /*!< SCE REG_xxxH: bit 22 Position       */
#define SCE_REG_22_Msk    (0x01UL << SCE_REG_22_Pos) /*!< SCE REG_xxxH: bit 22 Mask           */
#define SCE_REG_23_Pos    23                         /*!< SCE REG_xxxH: bit 23 Position       */
#define SCE_REG_23_Msk    (0x01UL << SCE_REG_23_Pos) /*!< SCE REG_xxxH: bit 23 Mask           */
#define SCE_REG_24_Pos    24                         /*!< SCE REG_xxxH: bit 24 Position       */
#define SCE_REG_24_Msk    (0x01UL << SCE_REG_24_Pos) /*!< SCE REG_xxxH: bit 24 Mask           */
#define SCE_REG_25_Pos    25                         /*!< SCE REG_xxxH: bit 25 Position       */
#define SCE_REG_25_Msk    (0x01UL << SCE_REG_25_Pos) /*!< SCE REG_xxxH: bit 25 Mask           */
#define SCE_REG_26_Pos    26                         /*!< SCE REG_xxxH: bit 26 Position       */
#define SCE_REG_26_Msk    (0x01UL << SCE_REG_26_Pos) /*!< SCE REG_xxxH: bit 26 Mask           */
#define SCE_REG_27_Pos    27                         /*!< SCE REG_xxxH: bit 27 Position       */
#define SCE_REG_27_Msk    (0x01UL << SCE_REG_27_Pos) /*!< SCE REG_xxxH: bit 27 Mask           */
#define SCE_REG_28_Pos    28                         /*!< SCE REG_xxxH: bit 28 Position       */
#define SCE_REG_28_Msk    (0x01UL << SCE_REG_28_Pos) /*!< SCE REG_xxxH: bit 28 Mask           */
#define SCE_REG_29_Pos    29                         /*!< SCE REG_xxxH: bit 29 Position       */
#define SCE_REG_29_Msk    (0x01UL << SCE_REG_29_Pos) /*!< SCE REG_xxxH: bit 29 Mask           */
#define SCE_REG_30_Pos    30                         /*!< SCE REG_xxxH: bit 30 Position       */
#define SCE_REG_30_Msk    (0x01UL << SCE_REG_30_Pos) /*!< SCE REG_xxxH: bit 30 Mask           */
#define SCE_REG_31_Pos    31                         /*!< SCE REG_xxxH: bit 31 Position       */
#define SCE_REG_31_Msk    (0x01UL << SCE_REG_31_Pos) /*!< SCE REG_xxxH: bit 31 Mask           */

/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

//#define SCE    ((SCE_Type *) SCE_BASE)
#define SCE    (*(volatile struct SCE_Type  R_BSP_EVENACCESS_SFR *)SCE_BASE)

// macro definishion

#define SCE_DELAY(delay)                                      \
    for (volatile uint32_t count = 0; count < delay; count++) \
    {                                                         \
        ;                                                     \
    }

// [R RD 1 B]
#define  RD1_PROG(regName) \
    (SCE.regName.WORD)

// [R WR 1 B]
#define  WR1_PROG(regName, value) \
    SCE.regName.WORD = value

// [R WR 2 B0 B1]
#define  WR2_PROG(regName, value0, value1) \
    WR1_PROG(regName, value0);             \
    WR1_PROG(regName, value1);

// [R WR 3 B0 B1 B2]
#define  WR3_PROG(regName, value0, value1, value2) \
    WR1_PROG(regName, value0);                     \
    WR1_PROG(regName, value1);                     \
    WR1_PROG(regName, value2)

// [R WR 4 B0 B1 B2 B3]
#define  WR4_PROG(regName, value0, value1, value2, value3) \
    WR1_PROG(regName, value0);                             \
    WR1_PROG(regName, value1);                             \
    WR1_PROG(regName, value2);                             \
    WR1_PROG(regName, value3)

// [R WR 16 B0 B1 B2 B3 B4 B5 B6 B7]
#define  WR8_PROG(regName,     \
                   value0,      \
                   value1,      \
                   value2,      \
                   value3,      \
                   value4,      \
                   value5,      \
                   value6,      \
                   value7)      \
    WR1_PROG(regName, value0);  \
    WR1_PROG(regName, value1);  \
    WR1_PROG(regName, value2);  \
    WR1_PROG(regName, value3);  \
    WR1_PROG(regName, value4);  \
    WR1_PROG(regName, value5);  \
    WR1_PROG(regName, value6);  \
    WR1_PROG(regName, value7)

// [R WR 16 B0 B1 B2 B3 B4 B5 B6 B7 B8 B9 B10 B11 B12 B13 B14 B15]
#define  WR16_PROG(regName,     \
                   value0,      \
                   value1,      \
                   value2,      \
                   value3,      \
                   value4,      \
                   value5,      \
                   value6,      \
                   value7,      \
                   value8,      \
                   value9,      \
                   value10,     \
                   value11,     \
                   value12,     \
                   value13,     \
                   value14,     \
                   value15)     \
    WR1_PROG(regName, value0);  \
    WR1_PROG(regName, value1);  \
    WR1_PROG(regName, value2);  \
    WR1_PROG(regName, value3);  \
    WR1_PROG(regName, value4);  \
    WR1_PROG(regName, value5);  \
    WR1_PROG(regName, value6);  \
    WR1_PROG(regName, value7);  \
    WR1_PROG(regName, value8);  \
    WR1_PROG(regName, value9);  \
    WR1_PROG(regName, value10); \
    WR1_PROG(regName, value11); \
    WR1_PROG(regName, value12); \
    WR1_PROG(regName, value13); \
    WR1_PROG(regName, value14); \
    WR1_PROG(regName, value15)

// [R RD 1 B]
#define  RD1_EVAL(regName, value) \
    if (SCE.regName != value)    \
        return FSP_ERR_CRYPTO_SCE_FAIL

// [R CHK_STATUS A B]
#define  CHCK_STS(regName, bitPos, value) \
    (((SCE.regName.WORD & (0x01UL << bitPos)) >> bitPos) == value)

// [R CHK_REG A (!= B)]
#define  RD1_MASK(regName, maskValue) \
    (SCE.regName.WORD & maskValue)

// [R WAIT_STATUS A B]
#define  WAIT_STS(regName, bitPos, value) \
    while (!CHCK_STS(regName, bitPos, value))

// [R WR 1 MEM[Ofs]]
#define  WR1_ADDR(regName, addr) \
    SCE.regName.WORD = *(addr)

// [R WR 2 MEM[Ofs]]
#define  WR2_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1);

// [R WR 3 MEM[Ofs]]
#define  WR3_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2);

// [R WR 4 MEM[Ofs]]
#define  WR4_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3)

// [R WR 5 MEM[Ofs]]
#define  WR5_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3); \
    WR1_ADDR(regName, (addr) + 4)

// [R WR 6 MEM[Ofs]]
#define  WR6_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3); \
    WR1_ADDR(regName, (addr) + 4); \
    WR1_ADDR(regName, (addr) + 5)

// [R WR 7 MEM[Ofs]]
#define  WR7_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3); \
    WR1_ADDR(regName, (addr) + 4); \
    WR1_ADDR(regName, (addr) + 5); \
    WR1_ADDR(regName, (addr) + 6)

// [R WR 8 MEM[Ofs]]
#define  WR8_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0); \
    WR1_ADDR(regName, (addr) + 1); \
    WR1_ADDR(regName, (addr) + 2); \
    WR1_ADDR(regName, (addr) + 3); \
    WR1_ADDR(regName, (addr) + 4); \
    WR1_ADDR(regName, (addr) + 5); \
    WR1_ADDR(regName, (addr) + 6); \
    WR1_ADDR(regName, (addr) + 7)

// [R WR 12 MEM[Ofs]]
#define  WR12_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0);  \
    WR1_ADDR(regName, (addr) + 1);  \
    WR1_ADDR(regName, (addr) + 2);  \
    WR1_ADDR(regName, (addr) + 3);  \
    WR1_ADDR(regName, (addr) + 4);  \
    WR1_ADDR(regName, (addr) + 5);  \
    WR1_ADDR(regName, (addr) + 6);  \
    WR1_ADDR(regName, (addr) + 7);  \
    WR1_ADDR(regName, (addr) + 8);  \
    WR1_ADDR(regName, (addr) + 9);  \
    WR1_ADDR(regName, (addr) + 10); \
    WR1_ADDR(regName, (addr) + 11)

// [R WR 16 MEM[Ofs]]
#define  WR16_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0);  \
    WR1_ADDR(regName, (addr) + 1);  \
    WR1_ADDR(regName, (addr) + 2);  \
    WR1_ADDR(regName, (addr) + 3);  \
    WR1_ADDR(regName, (addr) + 4);  \
    WR1_ADDR(regName, (addr) + 5);  \
    WR1_ADDR(regName, (addr) + 6);  \
    WR1_ADDR(regName, (addr) + 7);  \
    WR1_ADDR(regName, (addr) + 8);  \
    WR1_ADDR(regName, (addr) + 9);  \
    WR1_ADDR(regName, (addr) + 10); \
    WR1_ADDR(regName, (addr) + 11); \
    WR1_ADDR(regName, (addr) + 12); \
    WR1_ADDR(regName, (addr) + 13); \
    WR1_ADDR(regName, (addr) + 14); \
    WR1_ADDR(regName, (addr) + 15)

// [R WR 32 MEM[Ofs]]
#define  WR32_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0);  \
    WR1_ADDR(regName, (addr) + 1);  \
    WR1_ADDR(regName, (addr) + 2);  \
    WR1_ADDR(regName, (addr) + 3);  \
    WR1_ADDR(regName, (addr) + 4);  \
    WR1_ADDR(regName, (addr) + 5);  \
    WR1_ADDR(regName, (addr) + 6);  \
    WR1_ADDR(regName, (addr) + 7);  \
    WR1_ADDR(regName, (addr) + 8);  \
    WR1_ADDR(regName, (addr) + 9);  \
    WR1_ADDR(regName, (addr) + 10); \
    WR1_ADDR(regName, (addr) + 11); \
    WR1_ADDR(regName, (addr) + 12); \
    WR1_ADDR(regName, (addr) + 13); \
    WR1_ADDR(regName, (addr) + 14); \
    WR1_ADDR(regName, (addr) + 15); \
    WR1_ADDR(regName, (addr) + 16); \
    WR1_ADDR(regName, (addr) + 17); \
    WR1_ADDR(regName, (addr) + 18); \
    WR1_ADDR(regName, (addr) + 19); \
    WR1_ADDR(regName, (addr) + 20); \
    WR1_ADDR(regName, (addr) + 21); \
    WR1_ADDR(regName, (addr) + 22); \
    WR1_ADDR(regName, (addr) + 23); \
    WR1_ADDR(regName, (addr) + 24); \
    WR1_ADDR(regName, (addr) + 25); \
    WR1_ADDR(regName, (addr) + 26); \
    WR1_ADDR(regName, (addr) + 27); \
    WR1_ADDR(regName, (addr) + 28); \
    WR1_ADDR(regName, (addr) + 29); \
    WR1_ADDR(regName, (addr) + 30); \
    WR1_ADDR(regName, (addr) + 31)

// [R WR 64 MEM[Ofs]]
#define  WR64_ADDR(regName, addr)   \
    WR1_ADDR(regName, (addr) + 0);  \
    WR1_ADDR(regName, (addr) + 1);  \
    WR1_ADDR(regName, (addr) + 2);  \
    WR1_ADDR(regName, (addr) + 3);  \
    WR1_ADDR(regName, (addr) + 4);  \
    WR1_ADDR(regName, (addr) + 5);  \
    WR1_ADDR(regName, (addr) + 6);  \
    WR1_ADDR(regName, (addr) + 7);  \
    WR1_ADDR(regName, (addr) + 8);  \
    WR1_ADDR(regName, (addr) + 9);  \
    WR1_ADDR(regName, (addr) + 10); \
    WR1_ADDR(regName, (addr) + 11); \
    WR1_ADDR(regName, (addr) + 12); \
    WR1_ADDR(regName, (addr) + 13); \
    WR1_ADDR(regName, (addr) + 14); \
    WR1_ADDR(regName, (addr) + 15); \
    WR1_ADDR(regName, (addr) + 16); \
    WR1_ADDR(regName, (addr) + 17); \
    WR1_ADDR(regName, (addr) + 18); \
    WR1_ADDR(regName, (addr) + 19); \
    WR1_ADDR(regName, (addr) + 20); \
    WR1_ADDR(regName, (addr) + 21); \
    WR1_ADDR(regName, (addr) + 22); \
    WR1_ADDR(regName, (addr) + 23); \
    WR1_ADDR(regName, (addr) + 24); \
    WR1_ADDR(regName, (addr) + 25); \
    WR1_ADDR(regName, (addr) + 26); \
    WR1_ADDR(regName, (addr) + 27); \
    WR1_ADDR(regName, (addr) + 28); \
    WR1_ADDR(regName, (addr) + 29); \
    WR1_ADDR(regName, (addr) + 30); \
    WR1_ADDR(regName, (addr) + 31); \
    WR1_ADDR(regName, (addr) + 32); \
    WR1_ADDR(regName, (addr) + 33); \
    WR1_ADDR(regName, (addr) + 34); \
    WR1_ADDR(regName, (addr) + 35); \
    WR1_ADDR(regName, (addr) + 36); \
    WR1_ADDR(regName, (addr) + 37); \
    WR1_ADDR(regName, (addr) + 38); \
    WR1_ADDR(regName, (addr) + 39); \
    WR1_ADDR(regName, (addr) + 40); \
    WR1_ADDR(regName, (addr) + 41); \
    WR1_ADDR(regName, (addr) + 42); \
    WR1_ADDR(regName, (addr) + 43); \
    WR1_ADDR(regName, (addr) + 44); \
    WR1_ADDR(regName, (addr) + 45); \
    WR1_ADDR(regName, (addr) + 46); \
    WR1_ADDR(regName, (addr) + 47); \
    WR1_ADDR(regName, (addr) + 48); \
    WR1_ADDR(regName, (addr) + 49); \
    WR1_ADDR(regName, (addr) + 50); \
    WR1_ADDR(regName, (addr) + 51); \
    WR1_ADDR(regName, (addr) + 52); \
    WR1_ADDR(regName, (addr) + 53); \
    WR1_ADDR(regName, (addr) + 54); \
    WR1_ADDR(regName, (addr) + 55); \
    WR1_ADDR(regName, (addr) + 56); \
    WR1_ADDR(regName, (addr) + 57); \
    WR1_ADDR(regName, (addr) + 58); \
    WR1_ADDR(regName, (addr) + 59); \
    WR1_ADDR(regName, (addr) + 60); \
    WR1_ADDR(regName, (addr) + 61); \
    WR1_ADDR(regName, (addr) + 62); \
    WR1_ADDR(regName, (addr) + 63)

// [R RD 1 MEM[Ofs]]
#define  RD1_ADDR(regName, addr) \
    *((addr) + 0) = SCE.regName.WORD;

// [R RD 2 MEM[Ofs]]
#define  RD2_ADDR(regName, addr)  \
    *((addr) + 0) = SCE.regName.WORD; \
    *((addr) + 1) = SCE.regName.WORD;

// [R RD 3 MEM[Ofs]]
#define  RD3_ADDR(regName, addr)  \
    *((addr) + 0) = SCE.regName.WORD; \
    *((addr) + 1) = SCE.regName.WORD; \
    *((addr) + 2) = SCE.regName.WORD;

// [R RD 4 MEM[Ofs]]
#define  RD4_ADDR(regName, addr)  \
    *((addr) + 0) = SCE.regName.WORD; \
    *((addr) + 1) = SCE.regName.WORD; \
    *((addr) + 2) = SCE.regName.WORD; \
    *((addr) + 3) = SCE.regName.WORD

// [R RD 5 MEM[Ofs]]
#define  RD5_ADDR(regName, addr)  \
    *((addr) + 0) = SCE.regName.WORD; \
    *((addr) + 1) = SCE.regName.WORD; \
    *((addr) + 2) = SCE.regName.WORD; \
    *((addr) + 3) = SCE.regName.WORD; \
    *((addr) + 4) = SCE.regName.WORD

// [R RD 6 MEM[Ofs]]
#define  RD6_ADDR(regName, addr)  \
    *((addr) + 0) = SCE.regName.WORD; \
    *((addr) + 1) = SCE.regName.WORD; \
    *((addr) + 2) = SCE.regName.WORD; \
    *((addr) + 3) = SCE.regName.WORD; \
    *((addr) + 4) = SCE.regName.WORD; \
    *((addr) + 5) = SCE.regName.WORD

// [R RD 7 MEM[Ofs]]
#define  RD7_ADDR(regName, addr)  \
    *((addr) + 0) = SCE.regName.WORD; \
    *((addr) + 1) = SCE.regName.WORD; \
    *((addr) + 2) = SCE.regName.WORD; \
    *((addr) + 3) = SCE.regName.WORD; \
    *((addr) + 4) = SCE.regName.WORD; \
    *((addr) + 5) = SCE.regName.WORD; \
    *((addr) + 6) = SCE.regName.WORD

// [R RD 8 MEM[Ofs]]
#define  RD8_ADDR(regName, addr)  \
    *((addr) + 0) = SCE.regName.WORD; \
    *((addr) + 1) = SCE.regName.WORD; \
    *((addr) + 2) = SCE.regName.WORD; \
    *((addr) + 3) = SCE.regName.WORD; \
    *((addr) + 4) = SCE.regName.WORD; \
    *((addr) + 5) = SCE.regName.WORD; \
    *((addr) + 6) = SCE.regName.WORD; \
    *((addr) + 7) = SCE.regName.WORD

// [R RD 12 MEM[Ofs]]
#define  RD12_ADDR(regName, addr)  \
    *((addr) + 0)  = SCE.regName.WORD; \
    *((addr) + 1)  = SCE.regName.WORD; \
    *((addr) + 2)  = SCE.regName.WORD; \
    *((addr) + 3)  = SCE.regName.WORD; \
    *((addr) + 4)  = SCE.regName.WORD; \
    *((addr) + 5)  = SCE.regName.WORD; \
    *((addr) + 6)  = SCE.regName.WORD; \
    *((addr) + 7)  = SCE.regName.WORD; \
    *((addr) + 8)  = SCE.regName.WORD; \
    *((addr) + 9)  = SCE.regName.WORD; \
    *((addr) + 10) = SCE.regName.WORD; \
    *((addr) + 11) = SCE.regName.WORD

// [R RD 16 MEM[Ofs]]
#define  RD16_ADDR(regName, addr)  \
    *((addr) + 0)  = SCE.regName.WORD; \
    *((addr) + 1)  = SCE.regName.WORD; \
    *((addr) + 2)  = SCE.regName.WORD; \
    *((addr) + 3)  = SCE.regName.WORD; \
    *((addr) + 4)  = SCE.regName.WORD; \
    *((addr) + 5)  = SCE.regName.WORD; \
    *((addr) + 6)  = SCE.regName.WORD; \
    *((addr) + 7)  = SCE.regName.WORD; \
    *((addr) + 8)  = SCE.regName.WORD; \
    *((addr) + 9)  = SCE.regName.WORD; \
    *((addr) + 10) = SCE.regName.WORD; \
    *((addr) + 11) = SCE.regName.WORD; \
    *((addr) + 12) = SCE.regName.WORD; \
    *((addr) + 13) = SCE.regName.WORD; \
    *((addr) + 14) = SCE.regName.WORD; \
    *((addr) + 15) = SCE.regName.WORD

// [R RD 32 MEM[Ofs]]
#define  RD32_ADDR(regName, addr)  \
    *((addr) + 0)  = SCE.regName.WORD; \
    *((addr) + 1)  = SCE.regName.WORD; \
    *((addr) + 2)  = SCE.regName.WORD; \
    *((addr) + 3)  = SCE.regName.WORD; \
    *((addr) + 4)  = SCE.regName.WORD; \
    *((addr) + 5)  = SCE.regName.WORD; \
    *((addr) + 6)  = SCE.regName.WORD; \
    *((addr) + 7)  = SCE.regName.WORD; \
    *((addr) + 8)  = SCE.regName.WORD; \
    *((addr) + 9)  = SCE.regName.WORD; \
    *((addr) + 10) = SCE.regName.WORD; \
    *((addr) + 11) = SCE.regName.WORD; \
    *((addr) + 12) = SCE.regName.WORD; \
    *((addr) + 13) = SCE.regName.WORD; \
    *((addr) + 14) = SCE.regName.WORD; \
    *((addr) + 15) = SCE.regName.WORD; \
    *((addr) + 16) = SCE.regName.WORD; \
    *((addr) + 17) = SCE.regName.WORD; \
    *((addr) + 18) = SCE.regName.WORD; \
    *((addr) + 19) = SCE.regName.WORD; \
    *((addr) + 20) = SCE.regName.WORD; \
    *((addr) + 21) = SCE.regName.WORD; \
    *((addr) + 22) = SCE.regName.WORD; \
    *((addr) + 23) = SCE.regName.WORD; \
    *((addr) + 24) = SCE.regName.WORD; \
    *((addr) + 25) = SCE.regName.WORD; \
    *((addr) + 26) = SCE.regName.WORD; \
    *((addr) + 27) = SCE.regName.WORD; \
    *((addr) + 28) = SCE.regName.WORD; \
    *((addr) + 29) = SCE.regName.WORD; \
    *((addr) + 30) = SCE.regName.WORD; \
    *((addr) + 31) = SCE.regName.WORD

// [R RD 64 MEM[Ofs]]
#define  RD64_ADDR(regName, addr)  \
    *((addr) + 0)  = SCE.regName.WORD; \
    *((addr) + 1)  = SCE.regName.WORD; \
    *((addr) + 2)  = SCE.regName.WORD; \
    *((addr) + 3)  = SCE.regName.WORD; \
    *((addr) + 4)  = SCE.regName.WORD; \
    *((addr) + 5)  = SCE.regName.WORD; \
    *((addr) + 6)  = SCE.regName.WORD; \
    *((addr) + 7)  = SCE.regName.WORD; \
    *((addr) + 8)  = SCE.regName.WORD; \
    *((addr) + 9)  = SCE.regName.WORD; \
    *((addr) + 10) = SCE.regName.WORD; \
    *((addr) + 11) = SCE.regName.WORD; \
    *((addr) + 12) = SCE.regName.WORD; \
    *((addr) + 13) = SCE.regName.WORD; \
    *((addr) + 14) = SCE.regName.WORD; \
    *((addr) + 15) = SCE.regName.WORD; \
    *((addr) + 16) = SCE.regName.WORD; \
    *((addr) + 17) = SCE.regName.WORD; \
    *((addr) + 18) = SCE.regName.WORD; \
    *((addr) + 19) = SCE.regName.WORD; \
    *((addr) + 20) = SCE.regName.WORD; \
    *((addr) + 21) = SCE.regName.WORD; \
    *((addr) + 22) = SCE.regName.WORD; \
    *((addr) + 23) = SCE.regName.WORD; \
    *((addr) + 24) = SCE.regName.WORD; \
    *((addr) + 25) = SCE.regName.WORD; \
    *((addr) + 26) = SCE.regName.WORD; \
    *((addr) + 27) = SCE.regName.WORD; \
    *((addr) + 28) = SCE.regName.WORD; \
    *((addr) + 29) = SCE.regName.WORD; \
    *((addr) + 30) = SCE.regName.WORD; \
    *((addr) + 31) = SCE.regName.WORD; \
    *((addr) + 32) = SCE.regName.WORD; \
    *((addr) + 33) = SCE.regName.WORD; \
    *((addr) + 34) = SCE.regName.WORD; \
    *((addr) + 35) = SCE.regName.WORD; \
    *((addr) + 36) = SCE.regName.WORD; \
    *((addr) + 37) = SCE.regName.WORD; \
    *((addr) + 38) = SCE.regName.WORD; \
    *((addr) + 39) = SCE.regName.WORD; \
    *((addr) + 40) = SCE.regName.WORD; \
    *((addr) + 41) = SCE.regName.WORD; \
    *((addr) + 42) = SCE.regName.WORD; \
    *((addr) + 43) = SCE.regName.WORD; \
    *((addr) + 44) = SCE.regName.WORD; \
    *((addr) + 45) = SCE.regName.WORD; \
    *((addr) + 46) = SCE.regName.WORD; \
    *((addr) + 47) = SCE.regName.WORD; \
    *((addr) + 48) = SCE.regName.WORD; \
    *((addr) + 49) = SCE.regName.WORD; \
    *((addr) + 50) = SCE.regName.WORD; \
    *((addr) + 51) = SCE.regName.WORD; \
    *((addr) + 52) = SCE.regName.WORD; \
    *((addr) + 53) = SCE.regName.WORD; \
    *((addr) + 54) = SCE.regName.WORD; \
    *((addr) + 55) = SCE.regName.WORD; \
    *((addr) + 56) = SCE.regName.WORD; \
    *((addr) + 57) = SCE.regName.WORD; \
    *((addr) + 58) = SCE.regName.WORD; \
    *((addr) + 59) = SCE.regName.WORD; \
    *((addr) + 60) = SCE.regName.WORD; \
    *((addr) + 61) = SCE.regName.WORD; \
    *((addr) + 62) = SCE.regName.WORD; \
    *((addr) + 63) = SCE.regName.WORD

// [TEST_BUSY WAIT A]
#define  WAI_BUSY(value) \
    WAIT_STS(SCE->REG_00H, 31, value)

//void SC32_function001(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
//void SC32_function002(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
//void SC32_function003(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
//
//void SC327_function001(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
//void SC327_function002(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);
//void SC327_function003(uint32_t ARG1, uint32_t ARG2, uint32_t ARG3, uint32_t ARG4);

// [R WR 32 B0 B1 B2 B3 B4 .... B31]
#define  WR32_PROG(regName,                                                                                  \
                   value0, value1, value2, value3, value4, value5, value6, value7, value8, value9,           \
                   value10, value11, value12, value13, value14, value15, value16, value17, value18, value19, \
                   value20, value21, value22, value23, value24, value25, value26, value27, value28, value29, \
                   value30, value31                                                                          \
                   )                                                                                         \
    WR1_PROG(regName, value0);                                                                               \
    WR1_PROG(regName, value1);                                                                               \
    WR1_PROG(regName, value2);                                                                               \
    WR1_PROG(regName, value3);                                                                               \
    WR1_PROG(regName, value4);                                                                               \
    WR1_PROG(regName, value5);                                                                               \
    WR1_PROG(regName, value6);                                                                               \
    WR1_PROG(regName, value7);                                                                               \
    WR1_PROG(regName, value8);                                                                               \
    WR1_PROG(regName, value9);                                                                               \
    WR1_PROG(regName, value10);                                                                              \
    WR1_PROG(regName, value11);                                                                              \
    WR1_PROG(regName, value12);                                                                              \
    WR1_PROG(regName, value13);                                                                              \
    WR1_PROG(regName, value14);                                                                              \
    WR1_PROG(regName, value15);                                                                              \
    WR1_PROG(regName, value16);                                                                              \
    WR1_PROG(regName, value17);                                                                              \
    WR1_PROG(regName, value18);                                                                              \
    WR1_PROG(regName, value19);                                                                              \
    WR1_PROG(regName, value20);                                                                              \
    WR1_PROG(regName, value21);                                                                              \
    WR1_PROG(regName, value22);                                                                              \
    WR1_PROG(regName, value23);                                                                              \
    WR1_PROG(regName, value24);                                                                              \
    WR1_PROG(regName, value25);                                                                              \
    WR1_PROG(regName, value26);                                                                              \
    WR1_PROG(regName, value27);                                                                              \
    WR1_PROG(regName, value28);                                                                              \
    WR1_PROG(regName, value29);                                                                              \
    WR1_PROG(regName, value30);                                                                              \
    WR1_PROG(regName, value31)

// [R WR 48 B0 B1 B2 B3 B4 .... B47]
#define  WR48_PROG(regName,                                                                                  \
                   value0, value1, value2, value3, value4, value5, value6, value7, value8, value9,           \
                   value10, value11, value12, value13, value14, value15, value16, value17, value18, value19, \
                   value20, value21, value22, value23, value24, value25, value26, value27, value28, value29, \
                   value30, value31, value32, value33, value34, value35, value36, value37, value38, value39, \
                   value40, value41, value42, value43, value44, value45, value46, value47                    \
                   )                                                                                         \
    WR1_PROG(regName, value0);                                                                               \
    WR1_PROG(regName, value1);                                                                               \
    WR1_PROG(regName, value2);                                                                               \
    WR1_PROG(regName, value3);                                                                               \
    WR1_PROG(regName, value4);                                                                               \
    WR1_PROG(regName, value5);                                                                               \
    WR1_PROG(regName, value6);                                                                               \
    WR1_PROG(regName, value7);                                                                               \
    WR1_PROG(regName, value8);                                                                               \
    WR1_PROG(regName, value9);                                                                               \
    WR1_PROG(regName, value10);                                                                              \
    WR1_PROG(regName, value11);                                                                              \
    WR1_PROG(regName, value12);                                                                              \
    WR1_PROG(regName, value13);                                                                              \
    WR1_PROG(regName, value14);                                                                              \
    WR1_PROG(regName, value15);                                                                              \
    WR1_PROG(regName, value16);                                                                              \
    WR1_PROG(regName, value17);                                                                              \
    WR1_PROG(regName, value18);                                                                              \
    WR1_PROG(regName, value19);                                                                              \
    WR1_PROG(regName, value20);                                                                              \
    WR1_PROG(regName, value21);                                                                              \
    WR1_PROG(regName, value22);                                                                              \
    WR1_PROG(regName, value23);                                                                              \
    WR1_PROG(regName, value24);                                                                              \
    WR1_PROG(regName, value25);                                                                              \
    WR1_PROG(regName, value26);                                                                              \
    WR1_PROG(regName, value27);                                                                              \
    WR1_PROG(regName, value28);                                                                              \
    WR1_PROG(regName, value29);                                                                              \
    WR1_PROG(regName, value30);                                                                              \
    WR1_PROG(regName, value31);                                                                              \
    WR1_PROG(regName, value32);                                                                              \
    WR1_PROG(regName, value33);                                                                              \
    WR1_PROG(regName, value34);                                                                              \
    WR1_PROG(regName, value35);                                                                              \
    WR1_PROG(regName, value36);                                                                              \
    WR1_PROG(regName, value37);                                                                              \
    WR1_PROG(regName, value38);                                                                              \
    WR1_PROG(regName, value39);                                                                              \
    WR1_PROG(regName, value40);                                                                              \
    WR1_PROG(regName, value41);                                                                              \
    WR1_PROG(regName, value42);                                                                              \
    WR1_PROG(regName, value43);                                                                              \
    WR1_PROG(regName, value44);                                                                              \
    WR1_PROG(regName, value45);                                                                              \
    WR1_PROG(regName, value46);                                                                              \
    WR1_PROG(regName, value47)

// [R WR 48 B0 B1 B2 B3 B4 .... B47]
#define  WR64_PROG(regName,                                                                                  \
                   value0, value1, value2, value3, value4, value5, value6, value7, value8, value9,           \
                   value10, value11, value12, value13, value14, value15, value16, value17, value18, value19, \
                   value20, value21, value22, value23, value24, value25, value26, value27, value28, value29, \
                   value30, value31, value32, value33, value34, value35, value36, value37, value38, value39, \
                   value40, value41, value42, value43, value44, value45, value46, value47, value48, value49, \
                   value50, value51, value52, value53, value54, value55, value56, value57, value58, value59, \
                   value60, value61, value62, value63                                                        \
                   )                                                                                         \
    WR1_PROG(regName, value0);                                                                               \
    WR1_PROG(regName, value1);                                                                               \
    WR1_PROG(regName, value2);                                                                               \
    WR1_PROG(regName, value3);                                                                               \
    WR1_PROG(regName, value4);                                                                               \
    WR1_PROG(regName, value5);                                                                               \
    WR1_PROG(regName, value6);                                                                               \
    WR1_PROG(regName, value7);                                                                               \
    WR1_PROG(regName, value8);                                                                               \
    WR1_PROG(regName, value9);                                                                               \
    WR1_PROG(regName, value10);                                                                              \
    WR1_PROG(regName, value11);                                                                              \
    WR1_PROG(regName, value12);                                                                              \
    WR1_PROG(regName, value13);                                                                              \
    WR1_PROG(regName, value14);                                                                              \
    WR1_PROG(regName, value15);                                                                              \
    WR1_PROG(regName, value16);                                                                              \
    WR1_PROG(regName, value17);                                                                              \
    WR1_PROG(regName, value18);                                                                              \
    WR1_PROG(regName, value19);                                                                              \
    WR1_PROG(regName, value20);                                                                              \
    WR1_PROG(regName, value21);                                                                              \
    WR1_PROG(regName, value22);                                                                              \
    WR1_PROG(regName, value23);                                                                              \
    WR1_PROG(regName, value24);                                                                              \
    WR1_PROG(regName, value25);                                                                              \
    WR1_PROG(regName, value26);                                                                              \
    WR1_PROG(regName, value27);                                                                              \
    WR1_PROG(regName, value28);                                                                              \
    WR1_PROG(regName, value29);                                                                              \
    WR1_PROG(regName, value30);                                                                              \
    WR1_PROG(regName, value31);                                                                              \
    WR1_PROG(regName, value32);                                                                              \
    WR1_PROG(regName, value33);                                                                              \
    WR1_PROG(regName, value34);                                                                              \
    WR1_PROG(regName, value35);                                                                              \
    WR1_PROG(regName, value36);                                                                              \
    WR1_PROG(regName, value37);                                                                              \
    WR1_PROG(regName, value38);                                                                              \
    WR1_PROG(regName, value39);                                                                              \
    WR1_PROG(regName, value40);                                                                              \
    WR1_PROG(regName, value41);                                                                              \
    WR1_PROG(regName, value42);                                                                              \
    WR1_PROG(regName, value43);                                                                              \
    WR1_PROG(regName, value44);                                                                              \
    WR1_PROG(regName, value45);                                                                              \
    WR1_PROG(regName, value46);                                                                              \
    WR1_PROG(regName, value47);                                                                              \
    WR1_PROG(regName, value48);                                                                              \
    WR1_PROG(regName, value49);                                                                              \
    WR1_PROG(regName, value50);                                                                              \
    WR1_PROG(regName, value51);                                                                              \
    WR1_PROG(regName, value52);                                                                              \
    WR1_PROG(regName, value53);                                                                              \
    WR1_PROG(regName, value54);                                                                              \
    WR1_PROG(regName, value55);                                                                              \
    WR1_PROG(regName, value56);                                                                              \
    WR1_PROG(regName, value57);                                                                              \
    WR1_PROG(regName, value58);                                                                              \
    WR1_PROG(regName, value59);                                                                              \
    WR1_PROG(regName, value60);                                                                              \
    WR1_PROG(regName, value61);                                                                              \
    WR1_PROG(regName, value62);                                                                              \
    WR1_PROG(regName, value63)

R_BSP_PRAGMA_PACKOPTION
#endif /* R_RSIP_CM_RX261_IODEFINE_HEADER_FILE */
