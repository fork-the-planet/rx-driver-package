/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "hw_sce_rx_private.h"
#include "hw_sce_sub_func.h"

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

void HW_SCE_p_func073_sub001(uint32_t arg1, uint32_t arg2, uint32_t arg3)
{
   WR1_PROG(REG_00B4H, arg1);
   WR1_PROG(REG_00B8H, arg2);

   WR1_PROG(REG_00A4H, arg3);
   WR1_PROG(REG_00A0H, 0x20010001U);
   WAIT_STS(REG_00A8H, 0, 1);
   WR1_PROG(REG_00ACH, 0x00000001U);
}

void HW_SCE_p_func073_sub002(uint32_t arg1)
{
   WR1_PROG(REG_00B0H, arg1);
   WR1_PROG(REG_009CH, 0x80820005U);
   WR1_PROG(REG_0000H, 0x03430009U);
   WAIT_STS(REG_0004H, 30, 0);
   WR1_PROG(REG_0040H, 0x00001800U);
}

void HW_SCE_p_func073_sub003(uint32_t arg1, uint32_t arg2)
{
	WR1_PROG(REG_00B0H, arg1);
	WR1_PROG(REG_0000H, arg2);
	WAIT_STS(REG_0004H, 30, 0);
	WR1_PROG(REG_0040H, 0x00001800U);
}

