<#--
/***********************************************************************************************************************
* Copyright (c) 2017 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
-->
<#-- = DECLARE FUNCTION INFORMATION HERE =================== -->
<#assign Function_Base_Name = "R_CAN_PinSet">
<#assign Function_Description = "This function initializes pins for r_rscan_rx module">
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

    /* Set ${pin.pinName} pin */
    <#if pin.pinName?contains("CTXD")>
    PORT${pin.portNum}.PODR.BIT.B${pin.pinBitNum} = 1U;
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.PDR.BIT.B${pin.pinBitNum} = 1U;
    <#if headerInfo.device?contains("R5F5140")>
    <#else>
    PORT${pin.portNum}.DSCR.BIT.B${pin.pinBitNum} = 1U;
    </#if>
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
    <#elseif pin.pinName?contains("CRXD")>
    PORT${pin.portNum}.PODR.BIT.B${pin.pinBitNum} = 0U;
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    PORT${pin.portNum}.PDR.BIT.B${pin.pinBitNum} = 0U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
    </#if>
</#macro> 

<#macro channelpincode pin>
</#macro> 

<#macro endsection>

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}
</#macro> 

<#macro headerfilesection postfix>
void ${Function_Base_Name}${postfix}();
</#macro> 

<#-- = END OF FILE ========================================= -->