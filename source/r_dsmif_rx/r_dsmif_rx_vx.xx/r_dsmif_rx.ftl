<#--
/*
* Copyright (c) 2019 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
-->
<#-- = DECLARE FUNCTION INFORMATION HERE =================== -->
<#assign Function_Base_Name = "R_DSMIF_PinSet">
<#assign Function_Description = "This function initializes pins for r_dsmif_rx module">
<#assign Function_Arg = "none">
<#assign Function_Ret = "none">
<#assign Version = 1.00>

<#-- = DECLARE FUNCTION CONTENT HERE ======================= -->
<#macro initialsection postfix>
<#assign Function_Name = "${Function_Base_Name}${postfix}">
<#include "lib/functionheader.ftl">
void ${Function_Name}()
{
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);
</#macro> 

<#macro peripheralpincode pin>
</#macro> 

<#macro channelpincode pin>

<#if pin.pinName?contains("DSMCLK1")>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#elseif pin.pinName?contains("DSMDAT1")>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#elseif pin.pinName?contains("DSMCLK2")>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#elseif pin.pinName?contains("DSMDAT2")>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#elseif pin.pinName?contains("DSMDAT3")>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#elseif pin.pinName?contains("DSMCLK4")>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#elseif pin.pinName?contains("DSMDAT4")>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#elseif pin.pinName?contains("DSMCLK5")>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#elseif pin.pinName?contains("DSMDAT5")>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#else>
    /* Set ${pin.pinName} pin */
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
</#if>

</#macro> 

<#macro endsection>

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}
</#macro> 

<#macro headerfilesection postfix>
void ${Function_Base_Name}${postfix}();
</#macro> 

<#-- = END OF FILE ========================================= -->
