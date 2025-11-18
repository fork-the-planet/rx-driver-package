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

#include "ptxPLAT_GPIO.h"
#include <string.h>
#include <stdbool.h>

/*
 * ####################################################################################################################
 * DEFINES / TYPES
 * ####################################################################################################################
 */
static irq_handle_t ptx_plat_irq_handle;
static void ptxPLAT_GPIO_IsrCallback(void *p_args);

/*
 * Instance of GPIO-IRQ context.
 */
ptxPlatGpio_t gpio_irq_ctx;



#ifdef SEN_PIN_CONNECTION_AVAILABLE
    /*
     * Instance of PTX100x SEN-pin context.
     */
#endif

/*
 * ####################################################################################################################
 * API FUNCTIONS
 * ####################################################################################################################
 */
    ptxStatus_t ptxPLAT_GPIO_GetInitialized(ptxPlatGpio_t **gpio, ptxPlatGpio_Config_t *gpioPars)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != gpio) && (NULL != gpioPars))
    {
    	irq_err_t   r_status = IRQ_SUCCESS;

        switch (gpioPars->Type)
        {
            case GPIO_Type_PTXExtIRQPin:
                /* Initialization of the GPIO Context */
                memset(&gpio_irq_ctx, 0, sizeof(ptxPlatGpio_t));

                /* GPIO used for IRQ purpose is the following one. */
                gpio_irq_ctx.PortPin = s_ext_irq_cfg.pin;
                gpio_irq_ctx.ExtIrqInstance = &ptx_plat_irq_handle;

                /* Open and enable IRQ */
                r_status = ext_irq_open(gpio_irq_ctx.ExtIrqInstance, ptxPLAT_GPIO_IsrCallback);
                if (IRQ_SUCCESS == r_status)
                {
                    *gpio = &gpio_irq_ctx;
				}
                else
                {
                    status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
                }

                break;

            case GPIO_Type_SENOutPin:
#ifdef SEN_PIN_CONNECTION_AVAILABLE
                /* Initialization of the SEN-pin Context */
#else
                *gpio = NULL;
#endif
                break;

            default:
                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
                break;
        }

    } else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }
    return status;
}

ptxStatus_t ptxPLAT_GPIO_Deinit(ptxPlatGpio_t *gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        /* De-init IRQ. */
        if (NULL != gpio->ExtIrqInstance)
        {
        	irq_err_t r_status = IRQ_SUCCESS;

            r_status = ext_irq_close(*(gpio->ExtIrqInstance));

			if (IRQ_SUCCESS != r_status)
			{
				status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
			}
			else
			{
				/* Clear Platform Context. */
				(void)memset(gpio, 0, sizeof(ptxPlatGpio_t));
			}
        }
        else
        {
        		status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
        }
    } else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }
    return status;
}

ptxStatus_t ptxPLAT_GPIO_EnableInterrupt(ptxPlatGpio_t *gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        if (NULL != gpio->ExtIrqInstance)
        {
            irq_err_t r_status = ext_irq_enable(*(gpio->ExtIrqInstance), true);

            if (IRQ_SUCCESS != r_status)
            {
                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
            }
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_DisableInterrupt(ptxPlatGpio_t *gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        if (NULL != gpio->ExtIrqInstance)
        {
            irq_err_t r_status = ext_irq_enable(*(gpio->ExtIrqInstance), false);

            if (IRQ_SUCCESS != r_status)
            {
                status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InternalError);
            }
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_GetIntEnableStatus(ptxPlatGpio_t *gpio, uint32_t *state)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != gpio) && (NULL != gpio->ExtIrqInstance))
    {
    	/* Read Interrupt enable status */
		*state = (uint32_t)read_interrupt_status();
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_StartWaitForTrigger (ptxPlatGpio_t        * gpio,
                                              pptxPlat_IRQCallBack_t irqCallBack,
                                              void                 * irqCallBackCtx)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        gpio->IrqCallBack    = irqCallBack;
        gpio->IrqCallBackCtx = irqCallBackCtx;
        status               = ptxPLAT_GPIO_EnableInterrupt(gpio);
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_StopWaitForTrigger(ptxPlatGpio_t *gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        status               = ptxPLAT_GPIO_DisableInterrupt(gpio);
        gpio->IrqCallBack    = NULL;
        gpio->IrqCallBackCtx = NULL;
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_ReadLevel(ptxPlatGpio_t *gpio, uint8_t *value)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != gpio) && (NULL != value))
    {
    	gpio_level_t p_pin_value = (gpio_level_t)read_pin(gpio->PortPin);
		*value = (uint8_t)p_pin_value;
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }
	
    return status;
}

ptxStatus_t ptxPLAT_GPIO_TriggerRx(ptxPlatGpio_t *gpio)
{
    ptxStatus_t status = ptxStatus_Success;

    if (NULL != gpio)
    {
        uint8_t value;
        status =  ptxPLAT_GPIO_ReadLevel(gpio, &value);

        if ((ptxStatus_Success == status) && (1U == value))
        {
            if ((gpio_irq_ctx.IrqCallBack != NULL) && (gpio_irq_ctx.IrqCallBackCtx != NULL))
            {
                (void)gpio_irq_ctx.IrqCallBack(gpio_irq_ctx.IrqCallBackCtx);
            }
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

ptxStatus_t ptxPLAT_GPIO_WriteLevel(ptxPlatGpio_t *gpio, uint8_t value)
{
    ptxStatus_t status = ptxStatus_Success;

    if ((NULL != gpio))
    {
        if (NULL == gpio->ExtIrqInstance)
        {
            write_pin(gpio->PortPin, (gpio_level_t)value);
        }
        else
        {
            status = PTX_STATUS(ptxStatus_Comp_PERIPH, ptxStatus_InvalidParameter);
        }
    }
    else
    {
        status = PTX_STATUS(ptxStatus_Comp_PLAT, ptxStatus_InvalidParameter);
    }

    return status;
}

/*
 * ####################################################################################################################
 * INTERRUPT HANDLERS
 * ####################################################################################################################
 */
void ptxPLAT_GPIO_IsrCallback(void *p_args)
{
    /* NFC_TODO: Add functionality to GPIO interrupt */
    (void) p_args;
}

