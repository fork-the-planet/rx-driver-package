/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : rm_mcoboot_if.h
 * Version      : 1.00
 * Description  : This is the interface header file.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 21.04.2025 1.00     First Release
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "bootutil/image.h"
#include "bootutil/bootutil.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef RM_MCUBOOT_IF_H
#define RM_MCUBOOT_IF_H

#define MCUBOOT_VERSION_MAJOR (1)
#define MCUBOOT_VERSION_MINOR (0)

uint32_t RM_MCUBOOT_GetVersion(void);
void RM_MCUBOOT_BootApp(struct boot_rsp * rsp);

#endif /* RM_MCUBOOT_IF_H */
