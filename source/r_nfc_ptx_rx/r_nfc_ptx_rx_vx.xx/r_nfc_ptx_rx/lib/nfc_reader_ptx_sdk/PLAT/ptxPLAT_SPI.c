/*
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*
 * ####################################################################################################################
 * INCLUDES
 * ####################################################################################################################
 */
#include "ptxPLAT_SPI.h"
#include <string.h>

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */

static  ptxPLAT_SpiInstance_t   g_ptx_plat_sci_handle;

/*
 * ####################################################################################################################
 * STATIC VARIABLES
 * ####################################################################################################################
 */

/**
 * Instance of available (predefined) spi port driver.
 */
static ptxPLAT_SpiPort_t available_spi_port;

/**
 * Instance of SPI context.
 */
ptxPLAT_Spi_t spi_ctx;

/*
 * ####################################################################################################################
 * INTERNAL FUNCTIONS
 * ####################################################################################################################
 */

static ptxStatus_t ptxPLAT_SPI_PortOpen(ptxPLAT_SpiPort_t **spiPort, ptxPLAT_SpiConfigPars_t *spiPars);
static ptxStatus_t ptxPLAT_SPI_PortClose(ptxPLAT_SpiPort_t *spiPort);
static ptxStatus_t ptxPLAT_SPI_TxAux(ptxPLAT_Spi_t *spi, uint8_t *txBuff, size_t *len);
static ptxStatus_t ptxPLAT_SPI_RxAux(ptxPLAT_Spi_t *spi, uint8_t *rxBuff, size_t *len);
static ptxStatus_t ptxPLAT_SPI_TRx_Helper(ptxPLAT_Spi_t * spi,
                                          uint8_t       * txBuf[],
                                          size_t          txLen[],
                                          size_t          numTxBuffers,
                                          uint8_t       * rxBuf[],
                                          size_t        * rxLen[],
                                          size_t          numRxBuffers);
static ptxStatus_t ptxPLAT_SPI_SetTRxState(ptxPLAT_Spi_t *spi, uint8_t state);
static ptxStatus_t ptxPLAT_SPI_SetChipSelect(ptxPLAT_SpiPort_t *spiPort, uint8_t newState);

/*
 * ####################################################################################################################
 * EXTERNAL FUNCTIONS
 * ####################################################################################################################
 */

extern const st_gpio_conf_t s_spi_ss_cfg;

extern st_sci_conf_t *get_port_config(void);


/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */

ptxStatus_t ptxPLAT_SPI_GetInitialized(ptxPLAT_Spi_t **spi, ptxPLAT_SpiConfigPars_t *spiPars)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != spi) && (NULL != spiPars))
    {
        /**
         * Initialization of the SPI Context
         */

        ptxPLAT_SpiPort_t *spi_port = NULL;
        memset(&spi_ctx, 0, sizeof(ptxPLAT_Spi_t));

        status = ptxPLAT_SPI_PortOpen(&spi_port, spiPars);

        if (ptxStatus_Success == status)
        {
            ptxPlatGpio_Config_t gpio_pars;
            gpio_pars.Type = GPIO_Type_PTXExtIRQPin;

            status = ptxPLAT_GPIO_GetInitialized(&spi_ctx.Gpio, &gpio_pars);

            if((ptxStatus_Success == status) && (NULL != spi_port))
            {
                spi_ctx.SpiPortUsed = spi_port;
                *spi                = &spi_ctx;
            }
            else
            {
                /**
                 *  Clean up here: close SPI port instance since it has been successfully opened.
                 */
                ptxPLAT_SPI_PortClose(spi_port);

                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
            }
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_SPI_Deinit(ptxPLAT_Spi_t *spi)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != spi)
    {
        /**
         * De Init tasks shall be performed here:
         *  close spi port - power down the peripheral
         *  de-init external irq gpio module
         */
        ptxPLAT_SPI_PortClose(spi->SpiPortUsed);

        ptxPLAT_GPIO_Deinit(spi->Gpio);

        /** Clean spi context structure. */
        memset(&spi_ctx, 0, sizeof(ptxPLAT_Spi_t));
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_SPI_TRx (ptxPLAT_Spi_t * spi,
                             uint8_t       * txBuf[],
                             size_t          txLen[],
                             size_t          numTxBuffers,
                             uint8_t       * rxBuf[],
                             size_t        * rxLen[],
                             size_t          numRxBuffers,
                             uint8_t         flags)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != spi) && (NULL != txBuf) && (NULL != txLen))
    {
        /**
         * For any transmission operation over any interface the interrupt from GPIO-IRQ shall be disabled
         * to avoid potential mutual use of SPI driver.
         */
        uint32_t int_enable_status = PTX_PLAT_SPI_INT_ENABLE;

        /** If function call is successful, returned value will be 0 or 1. */
        ptxPLAT_GPIO_GetIntEnableStatus(spi->Gpio, &int_enable_status);

        ptxPLAT_GPIO_DisableInterrupt(spi->Gpio);
        status = ptxPLAT_SPI_TRx_Helper(spi, txBuf, txLen, numTxBuffers, rxBuf, rxLen, numRxBuffers);

        if (1U == int_enable_status)
        {
            /** Restore interrupt state. */
            ptxPLAT_GPIO_EnableInterrupt(spi->Gpio);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    (void)flags;

    return status;
}

ptxStatus_t ptxPLAT_SPI_StartWaitForRx(ptxPLAT_Spi_t *spi, pptxPlat_RxCallBack_t irqCb, void *ctxIrqCb)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != spi) && (NULL != irqCb) && (NULL != ctxIrqCb))
    {
        /** This function shall ensure that IRQ is not high before starting the wait for the event. */

        /** First register the callback function and the context, for future use */
        spi->RxCb    = irqCb;
        spi->CtxRxCb = ctxIrqCb;

        /** Read IRQ first to check if it is already HIGH.*/
        uint8_t value_IRQ = 0;
        ptxPLAT_GPIO_ReadLevel(spi->Gpio, &value_IRQ);

        if (1U == value_IRQ)
        {
            /** IRQ is already high, so let's trigger the asynchronous event now to prevent than race condition has happened. */
            spi->RxCb(spi->CtxRxCb);
        }

        /** Enable waiting for the trigger on IRQ (Not blocking). ISR on rising edge. */
        status = ptxPLAT_GPIO_StartWaitForTrigger(spi->Gpio, (pptxPlat_IRQCallBack_t)irqCb, ctxIrqCb);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_SPI_StopWaitForRx(ptxPLAT_Spi_t *spi)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != spi)
    {
        /** Stop the wait for the trigger on IRQ (Not blocking) */
        status = ptxPLAT_GPIO_StopWaitForTrigger(spi->Gpio);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

void ptxPLAT_SPI_TransferCallback(void *p_args)
{
	sci_cb_args_t *args = (sci_cb_args_t *)p_args;
    if((NULL != args) && (g_ptx_plat_sci_handle == args->hdl))
    {
        switch(args->event)
        {
            case SCI_EVT_XFER_DONE:
                ptxPLAT_SPI_SetTRxState(&spi_ctx, 1u);
                break;

            default:
                /** Transfer error. */
                ptxPLAT_SPI_SetTRxState(&spi_ctx, 0xFFu);
                break;
        }
    }
	else
    {
        /** Transfer error. */
        ptxPLAT_SPI_SetTRxState(&spi_ctx, 0xFFu);
    }
}

/*
 * ####################################################################################################################
 * LOCAL FUNCTIONS
 * ####################################################################################################################
 */
static ptxStatus_t ptxPLAT_SPI_SetTRxState(ptxPLAT_Spi_t *spi, uint8_t state)
{
    ptxStatus_t status = ptxStatus_Success;

    if(NULL != spi)
    {
        spi->TransferState = state;
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

static ptxStatus_t ptxPLAT_SPI_PortClose(ptxPLAT_SpiPort_t *spiPort)
{
    ptxStatus_t status = ptxStatus_Success;

    if(NULL != spiPort)
    {
        /**
         * Close spi port: power down the peripheral.
         */
    	ptxPLAT_SpiInstance_t spi_instance = *( (ptxPLAT_SpiInstance_t *) spiPort->SpiInstance );
        sci_err_t r_status = port_close(spi_instance);
        if(SCI_SUCCESS != r_status)
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

static ptxStatus_t  ptxPLAT_SPI_PortOpen(ptxPLAT_SpiPort_t **spiPort, ptxPLAT_SpiConfigPars_t *spiPars)
{
    ptxStatus_t status = ptxStatus_Success;
    FSP_PARAMETER_NOT_USED(spiPars);

    if((NULL != spiPars) && (NULL != spiPort))
    {
        if (PTX_PLAT_HOST_SPEED_SPI_MAX >= spiPars->IntfSpeed)
        {
        	available_spi_port.SpiInstance = &g_ptx_plat_sci_handle;
        	available_spi_port.Nss = s_spi_ss_cfg.pin;
        	ptxPLAT_SpiInstance_t *spi_instance = (ptxPLAT_SpiInstance_t *)available_spi_port.SpiInstance;
            sci_err_t r_status = port_open(spi_instance, ptxPLAT_SPI_TransferCallback);

            if (SCI_SUCCESS == r_status)
            {
            	/* Configure the NSS pin as output for further use */
                set_pin_direct((gpio_port_pin_t *)&available_spi_port.Nss, GPIO_DIRECTION_OUTPUT);

            	*spiPort = (ptxPLAT_SpiPort_t *)&available_spi_port;
            }
            else
            {
                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
            }

        } else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
        }
    } else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

static ptxStatus_t ptxPLAT_SPI_TxAux (ptxPLAT_Spi_t * spi, uint8_t * txBuff, size_t * len)
{
    /**
     * All input arguments shall be checked by the caller. Here, it is expected all are valid i.e. not NULL and
     * allocated enough memory for Rx operation.
     *
     * What about setting a safeguard timer before the wait-for-transfer-end loop?
     */
    ptxStatus_t status = ptxStatus_Success;

    ptxPLAT_SpiInstance_t spi_instance = *((ptxPLAT_SpiInstance_t *)spi->SpiPortUsed->SpiInstance);
    uint32_t length 				   = (uint32_t)*len;

    ptxPLAT_SPI_SetTRxState(spi, 0);

    sci_err_t _st = port_send(spi_instance, txBuff, length);
    if(SCI_SUCCESS != _st)
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InterfaceError);
    }

    if(ptxStatus_Success == status)
    {
        /** Wait until transfer notification is received via callback. */
        while (0 == spi->TransferState)
        {
            /* Do nothing */
            R_BSP_NOP();
        }

        if (1U != spi->TransferState)
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InterfaceError);
        }
    }

    return status;
}

static ptxStatus_t ptxPLAT_SPI_RxAux(ptxPLAT_Spi_t *spi, uint8_t *rxBuff, size_t *len)
{
    /**
     * All input arguments shall be checked by the caller. Here, it is expected all are valid i.e. not NULL and
     * allocated enough memory for Rx operation.
     *
     * What about setting a safeguard timer before the wait-for-transfer-end loop?
     */
    ptxStatus_t status = ptxStatus_Success;

    ptxPLAT_SpiInstance_t spi_instance = *((ptxPLAT_SpiInstance_t *)spi->SpiPortUsed->SpiInstance);
    uint32_t                length     = (uint32_t) *len;

    ptxPLAT_SPI_SetTRxState(spi, 0);

    sci_err_t r_status = port_receive(spi_instance, rxBuff, length);

    if(SCI_SUCCESS != r_status)
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InterfaceError);
    }

    if(ptxStatus_Success == status)
    {
        /** Wait until transfer notification is received via callback. */
        while (0 == spi->TransferState)
        {
            /* Do nothing */
            R_BSP_NOP();
        }

        if (1U != spi->TransferState)
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InterfaceError);
        }
    }

    return status;
}

static ptxStatus_t ptxPLAT_SPI_SetChipSelect(ptxPLAT_SpiPort_t *spiPort, uint8_t newState)
{
    ptxStatus_t status = ptxStatus_Success;

    if((NULL != spiPort) && ((PTX_PLAT_SPI_CS_LOW == newState) || (PTX_PLAT_SPI_CS_HIGH == newState)))
    {
        write_pin((gpio_port_pin_t)spiPort->Nss, (gpio_level_t)newState);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

static ptxStatus_t ptxPLAT_SPI_TRx_Helper (ptxPLAT_Spi_t * spi,
                                           uint8_t       * txBuf[],
                                           size_t          txLen[],
                                           size_t          numTxBuffers,
                                           uint8_t       * rxBuf[],
                                           size_t        * rxLen[],
                                           size_t          numRxBuffers)
{
    ptxStatus_t status = ptxStatus_Success;

    /**
     * Tx operation is required always: to send and to receive anything on SPI. So, tx buffers have to be provided always.
     */

    if ((NULL != spi) && (NULL != spi->SpiPortUsed) && (NULL != txBuf) && (NULL != txLen))
    {
        uint8_t i = 0;

        /** At this point the SPI transfer operation is triggered */
        ptxPLAT_SPI_SetChipSelect(spi->SpiPortUsed, PTX_PLAT_SPI_CS_LOW);

        /** Tx part of the overall transaction. */
        i = 0;
        while ((ptxStatus_Success == status) && (i < numTxBuffers))
        {
            if ((txBuf[i] != NULL) && (txLen[i] > 0))
            {
                size_t trx_len = txLen[i];
                status = ptxPLAT_SPI_TxAux(spi, txBuf[i], &trx_len);
            }
            else
            {
                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
            }

            i++;
        }

        if (ptxStatus_Success == status)
        {
            /** Let's see if there is something to read. */
            if ((NULL != rxBuf) && (NULL != rxLen))
            {
                i = 0;
                while ((ptxStatus_Success == status) && (i < numRxBuffers))
                {
                    if ((rxBuf[i] != NULL) && (rxLen[i] != NULL) && (*rxLen[i] > 0))
                    {
                        status = ptxPLAT_SPI_RxAux(spi, rxBuf[i], rxLen[i]);
                    }
                    else
                    {
                        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
                    }

                    i++;
                }
            }
        }

        /** In any case, at this point the SPI transfer operation is finished */
        ptxPLAT_SPI_SetChipSelect(spi->SpiPortUsed, PTX_PLAT_SPI_CS_HIGH);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}
