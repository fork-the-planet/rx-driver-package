/***********************************************************************************************************************
* Copyright (c) 2016 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/**********************************************************************************************************************
* System Name  : SDSI Driver
* File Name    : r_sdsi_rx.c
* Version      : 2.06
* Device       : RX
* Abstract     : API & Sub module
* Tool-Chain   : -
* OS           : not use
* H/W Platform : RSK board for RX
* Description  : Interface file for SDSI API for RX
* Limitation   : None
**********************************************************************************************************************/
/**********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 30.09.2016 1.00    First Release
*              : 31.07.2017 2.00    Supported RX65N-2MB.
*              :                    Fixed to correspond to Renesas coding rule.
*              : 27.12.2022 2.03    Updated slash format of included header file paths for Linux compatibility.
*              : 13.12.2023 2.04    Added WAIT_LOOP comments.
*              : 15.03.2025 2.05    Updated disclaimer.
*              : 30.10.2025 2.06    Changed the comment of API functions to the doxygen style.
**********************************************************************************************************************/

/**********************************************************************************************************************
Includes <System Includes> , "Project Includes"
**********************************************************************************************************************/
#include "platform.h"
#include "r_sdsi_rx_if.h"
#include "./src/r_sdsi_rx_private.h"
#ifdef SDSI_CFG_LONGQ_ENABLE                                /* Uses FIT LONGQ module                */
#include "r_longq_if.h"
#endif /* SDSI_CFG_LONGQ_ENABLE */

/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/

/**********************************************************************************************************************
Typedef definitions
**********************************************************************************************************************/

/**********************************************************************************************************************
Private global variables and functions
**********************************************************************************************************************/
sdsi_hndl_t * g_sdsi_hndl[((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t))];
static sdsi_status_t r_sdsi_init_hndl(uint32_t channel);

#ifdef SDSI_CFG_LONGQ_ENABLE                                /* Uses FIT LONGQ module                */
static longq_hdl_t     p_sdsi_long_que = 0;             /* LONGQ module                         */
#endif /* SDSI_CFG_LONGQ_ENABLE */

/**********************************************************************************************************************
 * Function Name: R_SDSI_Open
 *****************************************************************************************************************/ /**
 * @brief      This function initializes the SDSI FIT module. This function should be run first before using
 *             other API functions.
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  *p_sdsi_workarea
 *              Working area pointer for 4-byte boundaries (working area size 28 bytes should be secured)
 * @retval     SDSI_SUCCESS              Successful operation
 * @retval     SDSI_ERR                  Common error
 * @retval     SDSI_ERR_ADDRESS_BOUNDARY 4-byte boundaries address error in *p_sdsi_workarea
 * @details    Gets SDSI channel resource specified by the argument channel, and initializes SDSI driver and
 *             SDSI channels. Also, this function monopolizes the SDSI channel resource. \n
 *             Hold the working area specified by *p_sdsi_workarea and do not change the contents until
 *             SDSI drivers R_SDSI_Close() is called.
 * @note       To end the function processing before SDIO command is issued from SD host, run this function immediately
 *             after the system power-up. \n
 *             It is recommended to enable \#define SDSI_CFG_DISABLE_SYSTEM_INTERRUPT. When running this function,
 *             the state becomes IOR0=1 (Function0 Enabled/ Ready state) during the period from cancellation of
 *             SDSI module stop state to SDSI software reset (SDSICR3.SRST). During this period, SD slave detects
 *             SDIO command and returns the response. If \#define SDSI_CFG_DISABLE_SYSTEM_INTERRUPT is enabled,
 *             all processors interrupt requests are disabled during the period from module stop state to software
 *             reset, therefore, ready state period can be minimized. \n
 *             The pin state does not change before/after running this function. \n
 *             APIs other than R_SDSI_GetVersion() function, R_SDSI_Log() function, and R_SDSI_Set_LogHdlAddress()
 *             function cannot be used unless the function is successfully completed.
 */
sdsi_status_t R_SDSI_Open(uint32_t channel, void * p_sdsi_workarea)
{
    sdsi_hndl_t * p_hndl = 0;
    uint32_t    * p_ptr = 0;
    int16_t       i = 0;
#ifdef SDSI_CFG_USE_FIT
    bool          chk = false;
#endif /* SDSI_CFG_USE_FIT */

#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

#ifdef SDSI_CFG_USE_FIT
    /* Get the SDSI hardware resource. */
    chk = r_sdsi_dev_hardware_lock(channel);
    if (false == chk)
    {
        /* Lock has already been acquired by another task. Needs to try again later. */
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_USE_FIT */

    /* Initialize the work memory. */
    if (0 == (uint32_t)p_sdsi_workarea)
    {
#ifdef SDSI_CFG_USE_FIT
        /* Release the SDSI hardware resource. */
        r_sdsi_dev_hardware_unlock(channel);
#endif /* SDSI_CFG_USE_FIT */
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        g_sdsi_hndl[channel] = 0;    /* Release the SDSI handle. */
        return SDSI_ERR;
    }

    /* Check the work memory boundary (4-byte unit) */
    if ((uint32_t)p_sdsi_workarea & SDSI_ADDR_BOUNDARY)
    {
#ifdef SDSI_CFG_USE_FIT
        /* Release the SDSI hardware resource. */
        r_sdsi_dev_hardware_unlock(channel);
#endif /* SDSI_CFG_USE_FIT */
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        g_sdsi_hndl[channel] = 0;    /* Release the SDSI handle. */
        return SDSI_ERR_ADDRESS_BOUNDARY;
    }

    p_hndl = (sdsi_hndl_t *)p_sdsi_workarea;
    g_sdsi_hndl[channel] = p_hndl;

    /* Clear the work memory to '0'. */
    p_ptr = (uint32_t *)p_hndl;

    /* WAIT_LOOP */
    for (i = (sizeof(sdsi_hndl_t) / sizeof(uint32_t)); i > 0; i--)
    {
        *p_ptr++ = 0;
    }

    /* Set the SDSI register base address. */
    p_hndl->reg_base = (uint32_t)g_sdsi_cfg_ip_base[channel];

    /* Set to disable all interrupts. */
    r_sdsi_dev_disable_system_int(channel);

    /* Enable the peripheral module. */
    r_sdsi_dev_module_enable(channel);

    /* Open setting of SDSI register. */
    r_sdsi_dev_open(channel);

    /* Clear to disable all interrupts. */
    r_sdsi_dev_enable_system_int(channel);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_Open() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_Close
 *****************************************************************************************************************/ /**
 * @brief      This function is used to release the resources of the SDSI FIT module currently in use.
 * @param[in]  channel
 *              SDSI channel number
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Ends all SDSI FIT module processing and releases SDSI channel resource specified by the argument
 *             channel. Sets the SDSI channel to the module stop state. \n
 *             Releases the working area specified by R_SDSI_Open() function.
 * @note       Open processing by R_SDSI_Open() function is also required before running the function. The pin state
 *             does not change before/after running this function.
 */
sdsi_status_t R_SDSI_Close(uint32_t channel)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == g_sdsi_hndl[channel])
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Disable all interrupts. */
    r_sdsi_dev_disable_int(channel);

    /* Close setting of SDSI register. */
    r_sdsi_dev_close(channel);

    /* Disable the peripheral module. */
    r_sdsi_dev_module_disable(channel);

    /* Destroy the SDSI Handle and SDSI driver trans status. */
    g_sdsi_hndl[channel] = 0;

#ifdef SDSI_CFG_USE_FIT
    /* Release the SDSI hardware resource. */
    r_sdsi_dev_hardware_unlock(channel);
#endif /* SDSI_CFG_USE_FIT */

    return SDSI_SUCCESS;

} /* End of function R_SDSI_Close() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_Initialize
 *****************************************************************************************************************/ /**
 * @brief      This function performs SDSI IP initial setting. After successful operation, the state changes to
 *             C flag polling state.
 * @param[in]  channel
 *              SDSI channel number
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Performs SDSI IP initial setting. After successful operation, the state changes to C flag polling
 *             state.
 * @note       Before running this function, pin setting is required. Refer to 4 Pin Setting  in application note.
 *             Open processing by R_SDSI_Open() function is also required before running the function. \n
 *             The following settings should be made : \n
 *             \li Enable CPU access to Function1 Register1-4. \n
 *             \li Enable SD host access on Function1 Register5. \n
 *             \li Set FBR, FBR.SPS, and CCCR.SMPC \n
 *             \li Enable SDSI interrupt. \n
 *             \li Set CCCR.IOR1 to 1 (Ready). \n
 *             \li Set I/O Function ready 0 bit (SDSICR3.IOR0) to 1. When the bit is 1 and CMD5 from the SD host
 *               is accepted, 1 is set to C flag on R4 response. C flag status can be confirmed with
 *               R_SDSI_CflagPolling() return value. Call R_SDSI_CflagPolling() until CMD5 is issued from SD host.
 */
sdsi_status_t R_SDSI_Initialize(uint32_t channel)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Initializes the SDSI handle. */
    r_sdsi_init_hndl(channel);

    /* Disable ICU interrupts. */
    r_sdsi_dev_disable_int(channel);

    /* Initialize setting of SDSI register. */
    r_sdsi_dev_initialize(channel);

    /* Enable SDSI interrupts. */
    r_sdsi_dev_enable_int(channel);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_Initialize() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_End
 *****************************************************************************************************************/ /**
 * @brief      This function changes the SDSI FIT module from idle state to initialization state.
 * @param[in]  channel
 *              SDSI channel number
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Performs SDSI end processing.
 * @note       Before running this function, open processing by R_SDSI_Open() function is required. The pin state
 *             does not change before/after running this function.
 */
sdsi_status_t R_SDSI_End(uint32_t channel)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Disable ICU interrupts. */
    r_sdsi_dev_disable_int(channel);

    /* End setting of SDSI register. */
    r_sdsi_dev_end(channel);

    /* Initializes the SDSI handle. */
    r_sdsi_init_hndl(channel);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_End() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_CflagPolling
 *****************************************************************************************************************/ /**
 * @brief      This function gets C flag status of R4 response. After initialization processing by the
 *             R_SDSI_Initialize() function, call this function and check that SDSI_SUCCESS (C flag is
 *             1 (ready)) as return value.
 * @param[in]  channel
 *              SDSI channel number
 * @retval     SDSI_SUCCESS    C Flag is 1(Ready)
 * @retval     SDSI_ERR_BUSY   C Flag is 0(Busy)
 * @retval     SDSI_ERR        Common error
 * @details    Gets C flag status of R4 response.
 * @note       Before running this function, open processing by R_SDSI_Initialize() is required. \n
 *             When IOR0 is 1 and CMD5 from the SD host is accepted, 1 is set to C flag on R4 response.
 */
sdsi_status_t R_SDSI_CflagPolling(uint32_t channel)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)(sizeof(g_sdsi_cfg_ip_base) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Check the C Flag. */
    if (r_sdsi_dev_c_flag_polling(channel) != SDSI_SUCCESS)
    {
        return SDSI_ERR_BUSY;
    }
    return SDSI_SUCCESS;
} /* End of function R_SDSI_CflagPolling() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_WriteCisReg
 *****************************************************************************************************************/ /**
 * @brief      This function writes the value to CIS Data Register.
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  *p_sdsi_reg
 *              reg_no   Register No. (Setting is not required) \n
 *              offset   CIS Data Register offset (multiples of 4:0,4,8,12...100,104) \n
 *              *p_buff  Write buffer pointer (4 bytes)
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Writes the value to CIS Data Register, and accesses to CIS Data Register at 4 bytes. Can call only
 *             when the driver is in the initialization state.
 * @note       Before running this function, open processing by R_SDSI_Open() is required.
 */
sdsi_status_t R_SDSI_WriteCisReg(uint32_t channel,sdsi_cis_reg_t * p_sdsi_reg)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }

    if (SDSI_CIS_OFFSET_MAX < p_sdsi_reg->offset)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (SDSI_OFFSET_BOUNDARY & p_sdsi_reg->offset)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == p_sdsi_reg->p_buff)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Set SDSI CIS register. */
    r_sdsi_dev_write_cis_reg(channel, p_sdsi_reg);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_WriteCisReg() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_ReadCisReg
 *****************************************************************************************************************/ /**
 * @brief      This function reads the value from CIS Data Register.
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  *p_sdsi_reg
 *              reg_no   Register No. (Setting is not required) \n
 *              offset   CIS Data Register Offset (multiples of 4:0,4,8,12...100,104) \n
 *              *p_buff  Read buffer pointer (4 bytes)
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Reads the value from CIS Data Register, and accesses CIS Data Register at 4 bytes.
 * @note       Before running this function, open processing by R_SDSI_Open() is required.
 */
sdsi_status_t R_SDSI_ReadCisReg(uint32_t channel, sdsi_cis_reg_t * p_sdsi_reg)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }

    if (SDSI_CIS_OFFSET_MAX < p_sdsi_reg->offset)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (SDSI_OFFSET_BOUNDARY & p_sdsi_reg->offset)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == p_sdsi_reg->p_buff)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Get SDSI CIS register. */
    r_sdsi_dev_read_cis_reg(channel, p_sdsi_reg);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_ReadCisReg() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_WriteFuncReg
 *****************************************************************************************************************/ /**
 * @brief      This function writes the value to FN1 Data Register n (n=1,2,5). It performs processing to write
 *             data to the Function1 area.
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  *p_sdsi_reg
 *              reg_no   Register No. (1 or 2 or 5) \n
 *              offset   FN1 Data Register n (n=1 or 2 or 5) Offset \n
 *                       Allowable setting value: \n
 *                       FN1 Data Register 1 (Function1 Register1) : 0,1,2,3...255 \n
 *                       FN1 Data Register 2 (Function1 Register2) : 0,1,2,3...255 \n
 *                       FN1 Data Register 5 (Function1 Register5) : 0,1,2,3...1023 \n
 *              *p_buff  Write buffer pointer (1 bytes)
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Writes the value to FN1 Data Register n, and accesses FN1 Data Register n at 4 bytes.
 * @note       Before running this function, open processing by R_SDSI_Open() is required. \n
 *             FN1 Data Register 5 cannot be accessed simultaneously by the SD host and the CPU. Therefore,
 *             follow the steps below: \n
 *             \- Enable FN1 Data Register 5 to access from CPU (SDSICR2.REG5EN = 1) \n
 *                Access by SD host controller disabled. \n
 *             \- Access FN1 Data Register 5 \n
 *             \- Enable FN1 Data Register 5 to access from SD host controller (SDSICR2.REG5EN = 0) \n
 *                Access by SD host controller enabled. \n\n
 *             During the period of 2 mentioned above, when accessing from SD host controller to FN1 Data
 *             Register 5, the value wrote is ignored, and the read value is undefined. If writing or reading
 *             from both CPU and SD host controller to FN1 Data Register 5 occurs, exclusive access control
 *             in FN1 Data Register 5 is required.
 */
sdsi_status_t R_SDSI_WriteFuncReg(uint32_t channel, sdsi_func_reg_t * p_sdsi_reg)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }

    if (0 == p_sdsi_reg->reg_no)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if ((SDSI_FUNC1_REG3 == p_sdsi_reg->reg_no) ||
        (SDSI_FUNC1_REG4 == p_sdsi_reg->reg_no))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (((SDSI_FUNC1_REG1 == p_sdsi_reg->reg_no) ||
         (SDSI_FUNC1_REG2 == p_sdsi_reg->reg_no)) &&
         (SDSI_OFFSET_256 <= p_sdsi_reg->offset))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if ((SDSI_FUNC1_REG5  == p_sdsi_reg->reg_no) &&
        (SDSI_OFFSET_1024 <= p_sdsi_reg->offset))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
/*
    if (SDSI_OFFSET_BOUNDARY & p_sdsi_reg->offset)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
*/
    if (0 == p_sdsi_reg->p_buff)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Set SDSI function 1 register N. */
    r_sdsi_dev_write_func_reg(channel, p_sdsi_reg);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_WriteFuncReg() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_ReadFuncReg
 *****************************************************************************************************************/ /**
 * @brief      This function reads the value from FN1 Data Register m (m=1,3,5). It performs processing to read
 *             data from the Function1 area.
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  *p_sdsi_reg
 *              reg_no   Register No. (1 or 3 or 5) \n
 *              offset   FN1 Data Register m (m=1 or 2 or 5) Offset \n
 *                       Allowable setting value: \n
 *                       FN1 Data Register 1 (Function1 Register1) : 0,1,2,3...255 \n
 *                       FN1 Data Register 3 (Function1 Register3) : 0,1,2,3...255 \n
 *                       FN1 Data Register 5 (Function1 Register5) : 0,1,2,3...1023 \n
 *              *p_buff  Read buffer pointer (1 bytes)
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Reads the value from FN1 Data Register m, and accesses FN1 Data Register m at 4 bytes.
 * @note       Before running this function, open processing by R_SDSI_Open() is required. \n
 *             FN1 Data Register 5 cannot be accessed simultaneously by the SD host and the CPU. Therefore,
 *             follow the steps below: \n
 *             \- Enable FN1 Data Register 5 to access from CPU (SDSICR2.REG5EN = 1) \n
 *                Access by SD host controller disabled. \n
 *             \- Access FN1 Data Register 5 \n
 *             \- Enable FN1 Data Register 5 to access from SD host controller (SDSICR2.REG5EN = 0) \n
 *                Access by SD host controller enabled. \n\n
 *             During the period of 2 mentioned above, when accessing from SD host controller to FN1 Data
 *             Register 5, the value wrote is ignored, and the read value is undefined. If writing or reading
 *             from both CPU and SD host controller to FN1 Data Register 5 occurs, exclusive access control
 *             in FN1 Data Register 5 is required.
 */
sdsi_status_t R_SDSI_ReadFuncReg(uint32_t channel, sdsi_func_reg_t * p_sdsi_reg)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }

    if (0 == p_sdsi_reg->reg_no)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if ((SDSI_FUNC1_REG2 == p_sdsi_reg->reg_no) ||
        (SDSI_FUNC1_REG4 == p_sdsi_reg->reg_no))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (((SDSI_FUNC1_REG1 == p_sdsi_reg->reg_no) ||
         (SDSI_FUNC1_REG3 == p_sdsi_reg->reg_no)) &&
         (SDSI_OFFSET_256 <= p_sdsi_reg->offset))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if ((SDSI_FUNC1_REG5  == p_sdsi_reg->reg_no) &&
        (SDSI_OFFSET_1024 <= p_sdsi_reg->offset))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
/*
    if (SDSI_OFFSET_BOUNDARY & p_sdsi_reg->offset)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
*/
    if (0 == p_sdsi_reg->p_buff)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Get SDSI function 1 register N. */
    r_sdsi_dev_read_func_reg(channel, p_sdsi_reg);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_ReadFuncReg() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_WriteIntVectorReg
 *****************************************************************************************************************/ /**
 * @brief      This function writes the value to FN1 interrupt vector register (FN1INTVECR).
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  vector
 *              Value of FN1 Interrupt Vector Register (1 byte)
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Writes the value to FN1 interrupt vector register. If CCCR IEN1 is set to 1, SDIO interrupt
 *             using SDSI_D1 occurs.
 * @note       Before running this function, open processing by R_SDSI_Open() is required. If SDIO interrupt
 *             occurs, SDSI_D1 changes from H to L. \n
 *             The timing of issuance of SDIO interrupts differs depending on whether the SD bus width is
 *             1-bit or 4-bit. \n
 *             \li 1-bit bus (CCCR 0x07 bus width = 00b) \n
 *                 SDIO interrupts are generated with asynchronous timing; they are not synchronized with the SD clock.
 *             \li 4-bit bus (CCCR 0x07 bus width = 10b) \n
 *                 SDIO interrupts are generated in synchronization with the SD clock. If this API function is
 *                 called when the SD clock is halted, no SDIO interrupt is generated. SDIO interrupts are
 *                 generated when the SD clock is being supplied. \n
 *                 To generate SDIO interrupts with asynchronous timing, first set the bus width to 1-bit, then
 *                 call this API function.
 */
sdsi_status_t R_SDSI_WriteIntVectorReg(uint32_t channel, uint8_t vector)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)(sizeof(g_sdsi_cfg_ip_base) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Set SDIO interrupt vector. */
    r_sdsi_dev_write_int_vector_reg(channel, vector);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_WriteIntVectorReg() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_ReadIntVectorReg
 *****************************************************************************************************************/ /**
 * @brief      This function reads the value from FN1 interrupt vector register (FN1INTVECR).
 * @param[in]  channel
 *              SDSI channel number
 * @param[out] *p_vector
 *              Read buffer pointer (1 byte)
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Reads the value from FN1 interrupt vector register.
 * @note       Before running this function, open processing by R_SDSI_Open() is required.
 */
sdsi_status_t R_SDSI_ReadIntVectorReg(uint32_t channel, uint8_t * p_vector)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)(sizeof(g_sdsi_cfg_ip_base) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }

    if (0 == p_vector)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Get SDIO interrupt vector. */
    r_sdsi_dev_read_int_vector_reg(channel, p_vector);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_ReadIntVectorReg() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_ReadIntClearReg
 *****************************************************************************************************************/ /**
 * @brief      This function reads the value from FN1 interrupt clear register.
 * @param[in]  channel
 *              SDSI channel number
 * @param[out] p_vector
 *              Read buffer pointer (1 byte)
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Reads the value from FN1 interrupt clear register.
 * @note       Before running this function, open processing by R_SDSI_Open() is required.
 */
sdsi_status_t R_SDSI_ReadIntClearReg(uint32_t channel, uint8_t * p_vector)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)(sizeof(g_sdsi_cfg_ip_base) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }

    if (0 == p_vector)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    /* Get SDIO interrupt vector clear register. */
    r_sdsi_dev_read_int_clear_reg(channel, p_vector);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_ReadIntClearReg() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_EnableDirectTrans
 *****************************************************************************************************************/ /**
 * @brief      This function makes DMA transfer enable setting.
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  *p_sdsi_direct_trans
 *              adr : DMA transfer start address (allowable setting range: On-chip RAM address)
 *                      Use an address aligned with a 4-byte boundary. \n
 *              mode: DMA transfer mode \n
 *               Address setting: Specify one of the followings \n
 *                SDSI_MODE_DIRECT_ADDR_FIXED  : Fix the DMA transfer address \n
 *                SDSI_MODE_DIRECT_ADDR_INC    : Increment the DMA transfer address \n
 *               Specifies the next DMA transfer address when detecting DMA transfer end interrupt. \n\n
 *               Bus setting: Select one of the followings \n
 *                SDSI_MODE_DIRECT_BUS_LOCK    : Lock the bus used in the DMA transfer \n
 *                SDSI_MODE_DIRECT_BUS_UNLOCK  : Does not lock the bus used in the DMA transfer
 * @retval     SDSI_SUCCESS                Successful operation
 * @retval     SDSI_ERR                    Common error
 * @retval     SDSI_ERR_ADDRESS_BOUNDARY   adr 4-byte boundary address error
 * @details    Makes DMA transfer enable setting. After successful operation, when CMD53 (specified Function1) is
 *             issued from SD host controller, SDSI IP performs data transfer for On-chip RAM.
 * @note       Before running this function, open processing by R_SDSI_Open() is required. \n
 *             Do not call this function again if this function was operated successfully. If called, error is
 *             returned. To run this function again, run DMA transfer disable processing
 *             R_SDSI_DisableDirectTrans() in advance.\n
 *             SDSI performs DMA transfer using DMA bus. For RX65N/RX651 sharing the DMA bus used in SDSI and
 *             Ethernet controller (ETHERC), exclusive access control is required. The preconditions necessary for
 *             this function to operate properly are listed below. If these preconditions are not satisfied,
 *             the value SDSI_ERR is returned. \n
 *             \- The ETHER and EDMAC are in the module stop state. \n
 *             \- Initial settings have not been applied to the Ethernet FIT module. \n
 *                 (The ETHERC and EDMAC hardware resource is free) \n\n
 *             And ETHERC cannot release DMA bus dynamically due to its communication method. Therefore,
 *             if combining use of SDSI and ETHERC in the user system, do not perform SDSI DMA transfer.
 *             For the setting, follow the procedures below
 *            (assuming the use of Ethernet FIT module to control ETHERC) \n
 *             \- Make initialization setting for Ethernet FIT module
 *                 (ETHERC/EDMAC hardware resource lock and module stop cancellation) \n
 *             \- Make initialization setting for SDSI FIT module \n
 *             \- Disable R_SDSI_EnableDirectTrans() call after the above procedures \n\n
 *             When this function is called in the state mentioned in step 3 above, SDSI_ERR is returned.
 */
sdsi_status_t R_SDSI_EnableDirectTrans(uint32_t channel, sdsi_direct_trans_t * p_sdsi_direct_trans)
{
    sdsi_hndl_t * p_hndl = 0;
    
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    sdsi_status_t ret = SDSI_SUCCESS;

    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }

    /* Check direct transfer address. */
    ret = r_sdsi_dev_chk_direct_trans_adr(channel, p_sdsi_direct_trans->adr);
    if (SDSI_SUCCESS != ret)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return ret;
    }

    /* Check direct transfer mode. */
    if (0 == (p_sdsi_direct_trans->mode & SDSI_MODE_DIRECT_ADDR_MASK))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == (p_sdsi_direct_trans->mode & SDSI_MODE_DIRECT_BUS_MASK))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    p_hndl = SDSI_GET_HNDL(channel);

    /* Enable direct transfer. */
    if (r_sdsi_dev_enable_direct_trans(channel, p_sdsi_direct_trans) != SDSI_SUCCESS)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    /* Set address mode. */
    p_hndl->direct_trans_mode = p_sdsi_direct_trans->mode;

    return SDSI_SUCCESS;
} /* End of function R_SDSI_EnableDirectTrans() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_DisableDirectTrans
 *****************************************************************************************************************/ /**
 * @brief      Makes DMA transfer disable setting.
 * @param[in]  channel
 *              SDSI channel number
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Makes DMA transfer disable setting. After successful operation, when CMD53 (specified Function1) is
 *             issued from SD host controller, SDSI IP performs data transfer for Function1 area.
 * @note       Before running this function, open processing by R_SDSI_Open() is required.
 */
sdsi_status_t R_SDSI_DisableDirectTrans(uint32_t channel)
{
    sdsi_hndl_t * p_hndl = 0;
    
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    p_hndl = SDSI_GET_HNDL(channel);

    /* Disable direct transfer. */
    r_sdsi_dev_disable_direct_trans(channel);

    /* Clear address mode. */
    p_hndl->direct_trans_mode = SDSI_MODE_DIRECT_NONE;

    return SDSI_SUCCESS;
} /* End of function R_SDSI_DisableDirectTrans() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_SetDirectTransAdr
 *****************************************************************************************************************/ /**
 * @brief      This function specifies the DMA transfer address.
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  adr
 *              DMA transfer start address (allowable setting range : On-chip RAM address)
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Specifies the DMA transfer address.
 * @note       Before running this function, open processing by R_SDSI_Open() is required. Call this function before
 *              the DMA transfer starts.
 */
sdsi_status_t R_SDSI_SetDirectTransAdr(uint32_t channel, uint32_t adr)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    sdsi_status_t ret = SDSI_SUCCESS;

    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }

    /* Check direct transfer address. */
    ret = r_sdsi_dev_chk_direct_trans_adr(channel, adr);
    if (SDSI_SUCCESS != ret)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return ret;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    r_sdsi_dev_set_direct_trans_adr(channel, adr);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_SetDirectTransAdr() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_GetDirectTransAdr
 *****************************************************************************************************************/ /**
 * @brief      This function gets DMA transfer address.
 * @param[in]  channel
 *              SDSI channel number
 * @param[out] *p_adr
 *              DMA transfer start address buffer (4 bytes)
 * @retval     SDSI_SUCCESS   Successful operation
 * @retval     SDSI_ERR       Common error
 * @details    Gets DMA transfer address.
 * @note       Before running this function, open processing by R_SDSI_Open() is required. Call this function before
 *             the DMA transfer starts.
 */
sdsi_status_t R_SDSI_GetDirectTransAdr(uint32_t channel, uint32_t * p_adr)
{
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }

    if (0 == p_adr)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    r_sdsi_dev_get_direct_trans_adr(channel, p_adr);

    return SDSI_SUCCESS;
} /* End of function R_SDSI_GetDirectTransAdr() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_RegistIntCallback
 *****************************************************************************************************************/ /**
 * @brief      This function registers SDSI command interrupt callback function.
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  (\*callback)(sdsi_cmd_t\*)
 *              Callback function to be registered \n
 *              Callback function is not registered when null pointer is set.
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Registers SDSI command interrupt callback function. Call this function before running
 *             R_SDSI_Initialize().
 * @note       Before running this function, open processing by R_SDSI_Open() is required.\n
 *             The information stored in the callback function argument (sdsi_cmd_t\*) is shown in
 *             Table 3.1 in application note, this information is overwritten by the command issued from
 *             SD host controller.\n
 *             Read this information before SD host issues the next command.
 */
sdsi_status_t R_SDSI_RegistIntCallback(uint32_t channel, sdsi_status_t (* callback)(sdsi_cmd_t *))
{
    sdsi_hndl_t * p_hndl = 0;
    
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    p_hndl = SDSI_GET_HNDL(channel);
    p_hndl->int_callback = callback;

    return SDSI_SUCCESS;
} /* End of function R_SDSI_RegistIntCallback() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_RegistCdIntCallback
 *****************************************************************************************************************/ /**
 * @brief      This function registers SDSI card detection disable (Rise/Fall) interrupt callback function.
 * @param[in]  channel
 *              SDSI channel number
 * @param[in]  (\*callback)(uint32_t)
 *              Callback function to be registered \n
 *              Callback function is not registered when null pointer is set.
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Registers SDSI card detection disable (Rise/Fall) interrupt callback function. Call this function before
 *             running R_SDSI_Initialize().
 * @note       Before running this function, open processing by R_SDSI_Open() is required. \n
 *             The information stored in the callback function argument (uint32_t) is as follows: \n
 *             \li SDSI_CD_RISE : when Card detection disable (Rise) interrupt is detected \n
 *             \li SDSI_CD_FALL : when Card detection disable (Fall) interrupt is detected
 */
sdsi_status_t R_SDSI_RegistCdIntCallback(uint32_t channel, sdsi_status_t (* callback)(uint32_t))
{
    sdsi_hndl_t * p_hndl = 0;
    
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    p_hndl = SDSI_GET_HNDL(channel);
    p_hndl->int_cd_callback = callback;

    return SDSI_SUCCESS;
} /* End of function R_SDSI_RegistCdIntCallback() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_RegistDtIntCallback
 *****************************************************************************************************************/ /**
 * @brief      This function registers SDSI DMA transfer end interrupt callback function.
 * @param[in]  channel
 *              SDSI channel
 * @param[in]  (\*callback)(sdsi_cmd_t\*)
 *              Callback function to be registered \n
 *              Callback function is not registered when null pointer is set.\n
 * @retval     SDSI_SUCCESS  Successful operation
 * @retval     SDSI_ERR      Common error
 * @details    Registers SDSI DMA transfer end interrupt callback function. Call this function before running
 *             R_SDSI_Initialize().
 * @note       Before running this function, open processing by R_SDSI_Open() is required.\n
 *             The information stored in the callback function argument (sdsi_cmd_t\*) is the same as SDSI command
 *             interrupt. Refer to Table 3.1 in application note for the detail. This information is overwritten
 *             by the command issued from SD host controller. Read this information before SD host issues
 *             the next command.\n
 */
sdsi_status_t R_SDSI_RegistDtIntCallback(uint32_t channel, sdsi_status_t (* callback)(sdsi_cmd_t *))
{
    sdsi_hndl_t * p_hndl = 0;
    
#if (SDSI_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((uint32_t)((sizeof(g_sdsi_cfg_ip_base)) / sizeof(uint32_t)) <= channel)
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;
    }

    if (0 == SDSI_GET_HNDL(channel))
    {
        SDSI_LOG_FUNC(SDSI_DEBUG_ERR_ID, (uint32_t)SDSI_RX, __LINE__);
        return SDSI_ERR;  /* Not initialized */
    }
#endif /* SDSI_CFG_PARAM_CHECKING_ENABLE == 1 */

    p_hndl = SDSI_GET_HNDL(channel);
    p_hndl->int_dt_callback = callback;

    return SDSI_SUCCESS;
} /* End of function R_SDSI_RegistDtIntCallback() */

/**********************************************************************************************************************
 * Function Name: R_SDSI_GetVersion
 *****************************************************************************************************************/ /**
 * @brief     This function is used to get the SDSI FIT module version information.
 * @retval    Upper 2 bytes: Major version (in decimal). \n
 *            Lower 2 bytes: Minor version (in decimal).
 * @details   Returns the drivers version information.
 * @note      None.
 */
uint32_t R_SDSI_GetVersion(void)
{
    uint32_t const version = ((RX_SDSI_VERSION_MAJOR << SDSI_BIT_SHIFT_16) | RX_SDSI_VERSION_MINOR);

    return version;
} /* End of function R_SDSI_GetVersion() */

/**********************************************************************************************************************
* Function Name: r_sdsi_init_hndl
* Description  : Initializes the SDSI handle.
* Arguments    : uint32_t       channel                  ;   SDSI Channel No.
* Return Value : SDSI_SUCCESS                            ;   Successful operation
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
static sdsi_status_t r_sdsi_init_hndl(uint32_t channel)
{
    sdsi_hndl_t * p_hndl = 0;

    p_hndl = SDSI_GET_HNDL(channel);

    p_hndl->intsr1 = 0;
    p_hndl->intsr2 = 0;
    p_hndl->direct_trans_mode = 0;

    return SDSI_SUCCESS;
} /* End of function r_sdsi_init_hndl() */

#ifdef SDSI_CFG_LONGQ_ENABLE                                /* Uses FIT LONGQ module                */
/**********************************************************************************************************************
 * Function Name: R_SDSI_SetLogHdlAddress
 *****************************************************************************************************************/ /**
 * @brief      This function specifies the handler address for the LONGQ FIT module.
 * @param[in]  user_long_que
 *              LONGQ FIT module handler address
 * @retval     SDSI_SUCCESS  Successful operation
 * @details    Specifies the handler address of the LONGQ FIT module.
 * @note       Uses the LONGQ FIT module and performs preparatory processing to get the error log. Run this processing
 *             before calling R_SDSI_Open(). \n
 *             Incorporate the LONGQ FIT module separately.
 */
sdsi_status_t R_SDSI_SetLogHdlAddress(uint32_t user_long_que)
{
    p_sdsi_long_que = (longq_hdl_t)user_long_que;

    return SDSI_SUCCESS;
} /* End of function R_SDSI_SetLogHdlAddress() */


/**********************************************************************************************************************
* Function Name: r_sdsi_log
* Description  : Stores the debugging information.
* Arguments    : uint32_t           flg                  ;   Breakpoint processing
*              : uint32_t           fid                  ;   SDSI driver file No.
*              : uint32_t           line                 ;   SDSI driver line No.
* Return Value : 0      ; Successful
*              : 1      ; Error
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
uint32_t r_sdsi_log(uint32_t flg, uint32_t fid, uint32_t line)
{
    longq_err_t err = LONGQ_SUCCESS;
    uint32_t    ul_tmp = 0;

    /* Long to Byte */
    ul_tmp = 0;                                                        /* sdsi_log   Reserved               */
    ul_tmp = (ul_tmp | (line << SDSI_BIT_SHIFT_8));                    /* sdsi_log   LINE                   */
    ul_tmp = (ul_tmp | (fid  << SDSI_BIT_SHIFT_21));                   /* sdsi_log   FID FILE No.           */
    ul_tmp = (ul_tmp | (SDSI_DRIVER_ID << SDSI_BIT_SHIFT_27));         /* sdsi_log   FID DRIVER No.         */
    ul_tmp = (ul_tmp | (flg  << SDSI_BIT_SHIFT_31));                   /* sdsi_log   Breakpoint processing  */

    /* error log white */
    err = R_LONGQ_Put(p_sdsi_long_que, ul_tmp);

    if (err != LONGQ_SUCCESS)
    {
        return 1;
    }

    /* Breakpoint processing */
    if (0x80000000 == (ul_tmp & 0x80000000))
    {
        return 1;
    }

    return 0;
} /* End of function r_sdsi_log() */
#else

/**********************************************************************************************************************
 * Function Name: R_SDSI_SetLogHdlAddress
 *****************************************************************************************************************/ /**
 * @brief      This function specifies the handler address for the LONGQ FIT module.
 * @param[in]  user_long_que
 *              LONGQ FIT module handler address
 * @retval     SDSI_SUCCESS  Successful operation
 * @details    Specifies the handler address of the LONGQ FIT module.
 * @note       Uses the LONGQ FIT module and performs preparatory processing to get the error log. Run this processing
 *             before calling R_SDSI_Open(). \n
 *             Incorporate the LONGQ FIT module separately.
 */
sdsi_status_t R_SDSI_SetLogHdlAddress(uint32_t user_long_que)
{
    return SDSI_SUCCESS;
} /* End of function R_SDSI_SetLogHdlAddress() */
#endif /* SDSI_CFG_LONGQ_ENABLE */

/**********************************************************************************************************************
 * Function Name: R_SDSI_Log
 *****************************************************************************************************************/ /**
 * @brief      This function gets the error log.
 * @param[in]  flg
 *              0x00000001 (fixed value)
 * @param[in]  fid
 *              0x0000003f (fixed value)
 * @param[in]  line
 *              0x00001fff (fixed value)
 * @retval     0  Successful operation
 * @details    This function gets the error log. \n
 *             To end the error log acquisition, call this function.
 * @note       Incorporate the LONGQ FIT module separately.
 */
uint32_t R_SDSI_Log(uint32_t flg, uint32_t fid, uint32_t line)
{
    SDSI_LOG_FUNC(flg, fid, line);
    return 0;
} /* End of function R_SDSI_Log() */


/* End of File */
