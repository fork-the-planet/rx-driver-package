/***********************************************************************************************************************
* Copyright (c) 2019 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_riic_rx72m.c
 * Description  : Functions for using RIIC on RX devices. 
 **********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 30.07.2019 2.43     First Release
 *         : 10.10.2019 2.44     Added support for atomic control.
 *         : 15.03.2025 3.01     Updated disclaimer.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
/* Defines for RIIC support */
#include "r_riic_rx_if.h"

/* Check MCU Group */
#if defined(BSP_MCU_RX72M)

    #include "r_riic_rx_private.h"

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
/* Array of bit rate for RIICn (n=0, 1 or 2) */
const uint16_t g_riic_bps[] =
{
    RIIC_CFG_CH0_kBPS,
    RIIC_CFG_CH1_kBPS,
    RIIC_CFG_CH2_kBPS
};

/* Array of data of Slave Address 0 Register (SARL0 and SARU0) for RIICn (n=0, 1 or 2) */
const uint16_t g_riic_slv_ad0_val[] =
{
    RIIC_CFG_CH0_SLV_ADDR0,
    RIIC_CFG_CH1_SLV_ADDR0,
    RIIC_CFG_CH2_SLV_ADDR0
};

/* Array of data of Slave Address 1 Register (SARL1 and SARU1) for RIICn (n=0, 1 or 2) */
const uint16_t g_riic_slv_ad1_val[] =
{
    RIIC_CFG_CH0_SLV_ADDR1,
    RIIC_CFG_CH1_SLV_ADDR1,
    RIIC_CFG_CH2_SLV_ADDR1
};

/* Array of data of Slave Address 2 Register (SARL2 and SARU2) for RIICn (n=0, 1 or 2) */
const uint16_t g_riic_slv_ad2_val[] =
{
    RIIC_CFG_CH0_SLV_ADDR2,
    RIIC_CFG_CH1_SLV_ADDR2,
    RIIC_CFG_CH2_SLV_ADDR2
};

/* Array of slave address 0 format for RIICn (n=0, 1 or 2) */
const uint8_t g_riic_slv_ad0_format[] =
{
    RIIC_CFG_CH0_SLV_ADDR0_FORMAT,
    RIIC_CFG_CH1_SLV_ADDR0_FORMAT,
    RIIC_CFG_CH2_SLV_ADDR0_FORMAT
};

/* Array of slave address 1 format for RIICn (n=0, 1 or 2) */
const uint8_t g_riic_slv_ad1_format[] =
{
    RIIC_CFG_CH0_SLV_ADDR1_FORMAT,
    RIIC_CFG_CH1_SLV_ADDR1_FORMAT,
    RIIC_CFG_CH2_SLV_ADDR1_FORMAT
};

/* Array of slave address 2 format for RIICn (n=0, 1 or 2) */
const uint8_t g_riic_slv_ad2_format[] =
{
    RIIC_CFG_CH0_SLV_ADDR2_FORMAT,
    RIIC_CFG_CH1_SLV_ADDR2_FORMAT,
    RIIC_CFG_CH2_SLV_ADDR2_FORMAT
};

/* Array of general call address enable for RIICn (n=0, 1 or 2) */
const uint8_t g_riic_gca_enable[] =
{
    RIIC_CFG_CH0_SLV_GCA_ENABLE,
    RIIC_CFG_CH1_SLV_GCA_ENABLE,
    RIIC_CFG_CH2_SLV_GCA_ENABLE
};

/* Array of initialize data of I2C-bus Mode Register 2 (ICMR2) for RIICn (n=0, 1 or 2) */
const uint8_t g_riic_icmr2_init[] =
{
    RIIC_CH0_ICMR2_INIT,
    RIIC_CH1_ICMR2_INIT,
    RIIC_CH2_ICMR2_INIT
};

/* Array of initialize data of I2C-bus Mode Register 3 (ICMR3) for RIICn (n=0, 1 or 2) */
const uint8_t g_riic_icmr3_init[] =
{
    RIIC_CH0_ICMR3_INIT,
    RIIC_CH1_ICMR3_INIT,
    RIIC_CH2_ICMR3_INIT
};

/* Array of initialize data of I2C-bus Function Enable Register (ICFER) for RIICn (n=0, 1 or 2) */
const uint8_t g_riic_icfer_init[] =
{
    RIIC_CH0_ICFER_INIT,
    RIIC_CH1_ICFER_INIT,
    RIIC_CH2_ICFER_INIT
};

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
    #if (1U == RIIC_CFG_PORT_SET_PROCESSING)
/***********************************************************************************************************************
 * Function Name: riic_mcu_io_open
 * Description  : Sets ports to input mode.
 *              : Ports input pull-up becomes "Off".
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_io_open (uint8_t channel)
{
    volatile uint8_t uctmp = 0x00;
    R_BSP_VOLATILE_EVENACCESS uint8_t * ppcr = NULL;
    R_BSP_VOLATILE_EVENACCESS uint8_t * ppdr = NULL;
    uint8_t port_gr = 0;
    uint8_t pin_num = 0;

    /* Channel number? */
    switch (channel)
    {
        #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */

            /* Sets the port register of SCL pin. */
            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SCL0 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SCL0 input mode */

            /* Sets the port register of SDA pin. */
            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SDA0 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SDA0 input mode */
            uctmp = (*ppdr); /* Reads PDR. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */

            /* Sets the port register of SCL pin. */
            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SCL1 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SCL1 input mode */

            /* Sets the port register of SDA pin. */
            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SDA1 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SDA1 input mode */
            uctmp = (*ppdr); /* Reads PDR. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */

            /* Sets the port register of SCL pin. */
            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SCL2 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SCL2 input mode */

            /* Sets the port register of SDA pin. */
            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SDA2 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SDA2 input mode */
            uctmp = (*ppdr); /* Reads PDR. */
        break;
        #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
} /* End of function riic_mcu_io_open() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_mpc_enable
 * Description  : Enables RIIC multi-function pin controller.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_mpc_enable (uint8_t channel)
{
    volatile uint8_t uctmp = 0x00;
    R_BSP_VOLATILE_EVENACCESS uint8_t * ppmr = NULL;
    R_BSP_VOLATILE_EVENACCESS uint8_t * ppfs = NULL;
    uint8_t port_gr = 0;
    uint8_t pin_num = 0;

    /* The upper layer software should call "riic_disable()." */
    /* The upper layer software should set SCL and SDA ports to input mode using PDR. */
    /* The upper layer software should perform RIIC reset or internal reset. */

    /* Channel number? */
    switch (channel)
    {
        #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */
            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            /* Specifies the assignments of input/output signals for peripheral functions to the desired pins.
             But SCL and SDA are already in a high-impedance state.
             Because the upper layer software called "riic_reset_set()". */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL0_ENABLE; /* Pin function select to RIIC SCL pin. */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA0_ENABLE; /* Pin function select to RIIC SDA pin. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */

            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SCL). */
            uctmp = (*ppmr); /* Reads PMR. */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SDA). */
            uctmp = (*ppmr); /* Reads PMR. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */
            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            /* Specifies the assignments of input/output signals for peripheral functions to the desired pins.
             But SCL and SDA are already in a high-impedance state.
             Because the upper layer software called "riic_reset_set()". */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL1_ENABLE; /* Pin function select to RIIC SCL pin. */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA1_ENABLE; /* Pin function select to RIIC SDA pin. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */

            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SCL). */
            uctmp = (*ppmr); /* Reads PMR. */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SDA). */
            uctmp = (*ppmr); /* Reads PMR. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */
            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            /* Specifies the assignments of input/output signals for peripheral functions to the desired pins.
             But SCL and SDA are already in a high-impedance state.
             Because the upper layer software called "riic_reset_set()". */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL2_ENABLE; /* Pin function select to RIIC SCL pin. */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA2_ENABLE; /* Pin function select to RIIC SDA pin. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */

            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SCL). */
            uctmp = (*ppmr); /* Reads PMR. */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SDA). */
            uctmp = (*ppmr); /* Reads PMR. */
        break;
        #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
} /* End of function riic_mcu_mpc_enable() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_mpc_disable
 * Description  : Disables RIIC multi-function pin controller.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_mpc_disable (uint8_t channel)
{
    volatile uint8_t uctmp = 0x00;
    R_BSP_VOLATILE_EVENACCESS uint8_t * ppmr = NULL;
    R_BSP_VOLATILE_EVENACCESS uint8_t * ppfs = NULL;
    uint8_t port_gr = 0;
    uint8_t pin_num = 0;

    /* The upper layer software should set SCL snd SDA ports to input mode using PDR. */

    /* Channel number? */
    switch (channel)
    {
        #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */
            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL0_INIT; /* Pin function select to Hi-Z. */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA0_INIT; /* Pin function select to Hi-Z. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */
            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL1_INIT; /* Pin function select to Hi-Z. */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA1_INIT; /* Pin function select to Hi-Z. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */
            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL2_INIT; /* Pin function select to Hi-Z. */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA2_INIT; /* Pin function select to Hi-Z. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */
        break;
        #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
    uctmp = RIIC_PWPR_BOWI; /* Reads PWPR. */
} /* End of function riic_mcu_mpc_disable() */
    #endif

/***********************************************************************************************************************
 * Function Name: riic_mcu_check_channel
 * Description  : Checks channel is valid or not.
 * Arguments    : uint8_t channel
 * Return Value : true                   : RIIC channel is valid.
 *                false                  : RIIC channel is invalid.
 **********************************************************************************************************************/
bool riic_mcu_check_channel (uint8_t channel)
{
    bool ret = false;

    switch (channel)
    {

    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            ret = true;
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            ret = true;
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            ret = true;
        break;
    #endif

        default :

            /* The channel number is invalid. */
            ret = false;
        break;
    }

    return ret;
} /* End of function riic_mcu_check_channel() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_int_init
 * Description  : Registers a callback function for supported TEI and EEI group interrupts.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_int_init (uint8_t channel)
{
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC0_EEI0, (bsp_int_cb_t) riic0_eei_isr);
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC0_TEI0, (bsp_int_cb_t) riic0_tei_isr);
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC1_EEI1, (bsp_int_cb_t) riic1_eei_isr);
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC1_TEI1, (bsp_int_cb_t) riic1_tei_isr);
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC2_EEI2, (bsp_int_cb_t)riic2_eei_isr);
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC2_TEI2, (bsp_int_cb_t)riic2_tei_isr);
        break;
    #endif

        default :

            /* Do Nothing */
        break;
    }
} /* End of function riic_mcu_int_init() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_check_ir_txi
 * Description  : Check TXI interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : RIIC_IR_CLR         : TXI Interrupt request (IR) register is cleared.
 *              : RIIC_IR_SET         : TXI Interrupt request (IR) register is set.
 **********************************************************************************************************************/
uint8_t riic_mcu_check_ir_txi (uint8_t channel)
{
    uint8_t ret = RIIC_IR_CLR;

    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            ret = RIIC_IR_TXI0;
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            ret = RIIC_IR_TXI1;
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            ret = RIIC_IR_TXI2;
        break;
    #endif
        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }

    return ret;
} /* End of function riic_mcu_check_ir_txi() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_check_ir_rxi
 * Description  : Check RXI interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : RIIC_IR_CLR         : TXI Interrupt request (IR) register is cleared.
 *              : RIIC_IR_SET         : TXI Interrupt request (IR) register is set.
 **********************************************************************************************************************/
uint8_t riic_mcu_check_ir_rxi (uint8_t channel)
{
    uint8_t ret = RIIC_IR_CLR;

    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            ret = RIIC_IR_RXI0;
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            ret = RIIC_IR_RXI1;
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            ret = RIIC_IR_RXI2;
        break;
    #endif
        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }

    return ret;
} /* End of function riic_mcu_check_ir_rxi() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_clear_ir_txi
 * Description  : Clear TXI interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_clear_ir_txi (uint8_t channel)
{
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            RIIC_IR_TXI0 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if (RIIC_IR_CLR == RIIC_IR_TXI0)
            {
                /* Do Nothing */
            }
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            RIIC_IR_TXI1 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if (RIIC_IR_CLR == RIIC_IR_TXI1)
            {
                /* Do Nothing */
            }
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            RIIC_IR_TXI2 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if(RIIC_IR_CLR == RIIC_IR_TXI2)
            {
                /* Do Nothing */
            }
        break;
    #endif
        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }
} /* End of function riic_mcu_clear_ir_txi() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_clear_ir_rxi
 * Description  : Clear RXI interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_clear_ir_rxi (uint8_t channel)
{
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            RIIC_IR_RXI0 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if (RIIC_IR_CLR == RIIC_IR_RXI0)
            {
                /* Do Nothing */
            }
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            RIIC_IR_RXI1 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if (RIIC_IR_CLR == RIIC_IR_RXI1)
            {
                /* Do Nothing */
            }
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            RIIC_IR_RXI2 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if(RIIC_IR_CLR == RIIC_IR_RXI2)
            {
                /* Do Nothing */
            }
        break;
    #endif
        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }
} /* End of function riic_mcu_clear_ir_rxi() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_hardware_lock
 * Description  : Attempt to acquire the lock that has been sent in.
 * Arguments    : uint8_t channel
 * Return Value : true                   ; Successful operation
 *              : false                  ; error operation
 **********************************************************************************************************************/
bool riic_mcu_hardware_lock (uint8_t channel)
{
    bool chk = false;

    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            chk = R_BSP_HardwareLock(BSP_LOCK_RIIC0);
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            chk = R_BSP_HardwareLock(BSP_LOCK_RIIC1);
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            chk = R_BSP_HardwareLock(BSP_LOCK_RIIC2);
        break;
    #endif

        default :

            /* Do Nothing */
        break;
    }
    return chk;
} /* End of function riic_mcu_hardware_lock() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_hardware_unlock
 * Description  : Release hold on lock.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_hardware_unlock (uint8_t channel)
{
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            R_BSP_HardwareUnlock(BSP_LOCK_RIIC0);
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            R_BSP_HardwareUnlock(BSP_LOCK_RIIC1);
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            R_BSP_HardwareUnlock(BSP_LOCK_RIIC2);
        break;
    #endif

        default :

            /* Do Nothing */
        break;
    }
} /* End of function riic_mcu_hardware_unlock() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_power_on
 * Description  : Turns on power to a RIIC channel.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_power_on (uint8_t channel)
{
    #if ((1U == RIIC_CFG_CH0_INCLUDED) || (1U == RIIC_CFG_CH1_INCLUDED) || (1U == RIIC_CFG_CH2_INCLUDED))
    #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
    #endif
    #endif
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

    /* Enable selected RIIC Channel. */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
        
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
        
            /* Bring module out of stop state. */
            MSTP(RIIC0) = 0U;
            
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :

        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            
            /* Bring module out of stop state. */
            MSTP(RIIC1) = 0U;
            
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
        
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            
            /* Bring module out of stop state. */
            MSTP(RIIC2) = 0U;
            
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
        break;
    #endif

        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }

    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
} /* End of function riic_mcu_power_on() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_power_off
 * Description  : Turns off power to a RIIC channel.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_power_off (uint8_t channel)
{
    #if ((1U == RIIC_CFG_CH0_INCLUDED) || (1U == RIIC_CFG_CH1_INCLUDED) || (1U == RIIC_CFG_CH2_INCLUDED))
    #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
    #endif
    #endif
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

    /* Disable selected CMT Channel. */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :

        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            
            /* Put module in stop state. */
            MSTP(RIIC0) = 1U;
            
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :

        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            
            /* Put module in stop state. */
            MSTP(RIIC1) = 1U;
            
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
        
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            
            /* Put module in stop state. */
            MSTP(RIIC2) = 1U;
            
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
        break;
    #endif

        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }

    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
} /* End of function riic_mcu_power_off() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_int_icier_setting
 * Description  : Time out interrupt enable bit setting.
 * Arguments    : uint8_t channel
 *              : uint8_t New_icier       ; New ICIER value
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_int_icier_setting (uint8_t channel, uint8_t New_icier)
{
    volatile uint8_t uctmp = 0x00;

    /* Channel number? */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */
        #if (1U == RIIC_CFG_CH0_TMO_ENABLE)
            RIIC0.ICIER.BYTE = (New_icier | RIIC_ICIER_TMO);
            uctmp = RIIC0.ICIER.BYTE; /* Reads ICIER. */
        #else
            RIIC0.ICIER.BYTE = New_icier;
            uctmp = RIIC0.ICIER.BYTE; /* Reads ICIER. */
        #endif
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */
        #if (1U == RIIC_CFG_CH1_TMO_ENABLE)
            RIIC1.ICIER.BYTE = (New_icier | RIIC_ICIER_TMO);
            uctmp = RIIC1.ICIER.BYTE; /* Reads ICIER. */
        #else
            RIIC1.ICIER.BYTE = New_icier;
            uctmp = RIIC1.ICIER.BYTE; /* Reads ICIER. */
        #endif
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */
        #if (1U == RIIC_CFG_CH2_TMO_ENABLE)
            RIIC2.ICIER.BYTE = (New_icier | RIIC_ICIER_TMO);
            uctmp = RIIC2.ICIER.BYTE; /* Reads ICIER. */
        #else
            RIIC2.ICIER.BYTE = New_icier;
            uctmp = RIIC2.ICIER.BYTE; /* Reads ICIER. */
        #endif
        break;
    #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
} /* End of function riic_mcu_int_icier_setting() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_int_enable
 * Description  : Clears interrupt request register.
 *              : Enables interrupt.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_int_enable (uint8_t channel)
{
    #if ((1U == RIIC_CFG_CH0_INCLUDED) || (1U == RIIC_CFG_CH1_INCLUDED) || (1U == RIIC_CFG_CH2_INCLUDED))
    volatile uint8_t uctmp = 0x00;
    volatile bsp_int_ctrl_t group_priority;
    #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
    #endif
    group_priority.ipl = 0x00000000;

        #if (1U == RIIC_CFG_CH0_INCLUDED)
    if (group_priority.ipl < RIIC_IPR_CH0_EEI_SET)
    {
        group_priority.ipl = (uint32_t) RIIC_IPR_CH0_EEI_SET;
    }
    if (group_priority.ipl < RIIC_IPR_CH0_TEI_SET)
    {
        group_priority.ipl = (uint32_t) RIIC_IPR_CH0_TEI_SET;
    }
        #endif

        #if (1U == RIIC_CFG_CH1_INCLUDED)
    if (group_priority.ipl < RIIC_IPR_CH1_EEI_SET)
    {
        group_priority.ipl = (uint32_t) RIIC_IPR_CH1_EEI_SET;
    }
    if (group_priority.ipl < RIIC_IPR_CH1_TEI_SET)
    {
        group_priority.ipl = (uint32_t) RIIC_IPR_CH1_TEI_SET;
    }
        #endif

        #if (1U == RIIC_CFG_CH2_INCLUDED)
    if(group_priority.ipl < RIIC_IPR_CH2_EEI_SET)
    {
        group_priority.ipl = (uint32_t)RIIC_IPR_CH2_EEI_SET;
    }
    if(group_priority.ipl < RIIC_IPR_CH2_TEI_SET)
    {
        group_priority.ipl = (uint32_t)RIIC_IPR_CH2_TEI_SET;
    }
        #endif

    R_BSP_InterruptControl(BSP_INT_SRC_BL1_RIIC0_TEI0, BSP_INT_CMD_GROUP_INTERRUPT_ENABLE, (void *) &group_priority);
    #endif

    /* Channel number? */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */

            /* Enables interrupt. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_EEI0_GPBL1 = RIIC_IER_ENABLE; /* Enables EEI0 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
            RIIC_IER_RXI0 = RIIC_IER_ENABLE; /* Enables RXI0 interrupt request enable register. */
            RIIC_IER_TXI0 = RIIC_IER_ENABLE; /* Enables TXI0 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_TEI0_GPBL1 = RIIC_IER_ENABLE; /* Enables TEI0 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif

            /* Sets interrupt source priority. */
            RIIC_IPR_RXI0 = RIIC_IPR_CH0_RXI_SET; /* Sets RXI0 interrupt source priority register. */
            RIIC_IPR_TXI0 = RIIC_IPR_CH0_TXI_SET; /* Sets TXI0 interrupt source priority register. */
            uctmp = RIIC_IPR_TXI0; /* Reads IPR. */
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */

            /* Enables interrupt. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_EEI1_GPBL1 = RIIC_IER_ENABLE; /* Enables EEI1 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
            RIIC_IER_RXI1 = RIIC_IER_ENABLE; /* Enables RXI1 interrupt request enable register. */
            RIIC_IER_TXI1 = RIIC_IER_ENABLE; /* Enables TXI1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_TEI1_GPBL1 = RIIC_IER_ENABLE; /* Enables TEI1 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif

            /* Sets interrupt source priority. */
            RIIC_IPR_RXI1 = RIIC_IPR_CH1_RXI_SET; /* Sets RXI1 interrupt source priority register. */
            RIIC_IPR_TXI1 = RIIC_IPR_CH1_TXI_SET; /* Sets TXI1 interrupt source priority register. */
            uctmp = RIIC_IPR_TXI1; /* Reads IPR. */
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */

            /* Enables interrupt. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_EEI2_GPBL1 = RIIC_IER_ENABLE; /* Enables EEI2 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
            RIIC_IER_RXI2 = RIIC_IER_ENABLE; /* Enables RXI2 interrupt request enable register. */
            RIIC_IER_TXI2 = RIIC_IER_ENABLE; /* Enables TXI2 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_TEI2_GPBL1 = RIIC_IER_ENABLE; /* Enables TEI2 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif

            /* Sets interrupt source priority. */
            RIIC_IPR_RXI2 = RIIC_IPR_CH2_RXI_SET; /* Sets RXI2 interrupt source priority register. */
            RIIC_IPR_TXI2 = RIIC_IPR_CH2_TXI_SET; /* Sets TXI2 interrupt source priority register. */
            uctmp = RIIC_IPR_TXI2; /* Reads IPR. */
        break;
    #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
} /* End of function riic_mcu_int_enable() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_int_disable
 * Description  : Disables interrupt.
 *              : Sets interrupt source priority.
 *              : Clears interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_int_disable (uint8_t channel)
{
    #if ((1U == RIIC_CFG_CH0_INCLUDED) || (1U == RIIC_CFG_CH1_INCLUDED) || (1U == RIIC_CFG_CH2_INCLUDED))
    volatile uint8_t uctmp = 0x00;
    volatile bsp_int_ctrl_t group_priority;
    #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
    bsp_int_ctrl_t int_ctrl;
    #endif
    #endif

    /* Channel number? */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */

            /* Disables interrupt. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_EEI0_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI0 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
            RIIC_IER_RXI0 = RIIC_IER_DISABLE; /* Disables RXI0 interrupt request enable register. */
            RIIC_IER_TXI0 = RIIC_IER_DISABLE; /* Disables TXI0 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_TEI0_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI0 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif

            /* Sets interrupt source priority. */
            RIIC_IPR_RXI0 = RIIC_IPR_CH0_RXI_INIT; /* Sets RXI0 interrupt source priority register. */
            RIIC_IPR_TXI0 = RIIC_IPR_CH0_TXI_INIT; /* Sets TXI0 interrupt source priority register. */
            uctmp = RIIC_IPR_TXI0; /* Reads IPR. */
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */

            /* Disables interrupt. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_EEI1_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI1 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
            RIIC_IER_RXI1 = RIIC_IER_DISABLE; /* Disables RXI1 interrupt request enable register. */
            RIIC_IER_TXI1 = RIIC_IER_DISABLE; /* Disables TXI1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_TEI1_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI1 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif

            /* Sets interrupt source priority. */
            RIIC_IPR_RXI1 = RIIC_IPR_CH1_RXI_INIT; /* Sets RXI1 interrupt source priority register. */
            RIIC_IPR_TXI1 = RIIC_IPR_CH1_TXI_INIT; /* Sets TXI1 interrupt source priority register. */
            uctmp = RIIC_IPR_TXI1; /* Reads IPR. */
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */

            /* Disables interrupt. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_EEI2_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI2 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif
            RIIC_IER_RXI2 = RIIC_IER_DISABLE; /* Disables RXI2 interrupt request enable register. */
            RIIC_IER_TXI2 = RIIC_IER_DISABLE; /* Disables TXI2 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_DISABLE, &int_ctrl);
        #endif
            RIIC_IER_TEI2_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI2 groupBL1 interrupt request enable register. */
        #if ((R_BSP_VERSION_MAJOR == 5) && (R_BSP_VERSION_MINOR >= 30)) || (R_BSP_VERSION_MAJOR >= 6)
            R_BSP_InterruptControl(BSP_INT_SRC_EMPTY, BSP_INT_CMD_FIT_INTERRUPT_ENABLE, &int_ctrl);
        #endif

            /* Sets interrupt source priority. */
            RIIC_IPR_RXI2 = RIIC_IPR_CH2_RXI_INIT; /* Sets RXI2 interrupt source priority register. */
            RIIC_IPR_TXI2 = RIIC_IPR_CH2_TXI_INIT; /* Sets TXI2 interrupt source priority register. */
            uctmp = RIIC_IPR_TXI2; /* Reads IPR. */
        break;
    #endif

        default :

            /* Please add a channel as needed. */
        break;
    }

    group_priority.ipl = 0x00000000;
    R_BSP_InterruptControl(BSP_INT_SRC_BL1_RIIC0_TEI0, BSP_INT_CMD_GROUP_INTERRUPT_DISABLE, (void *) &group_priority);
} /* End of function riic_mcu_int_disable() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_check_freq
 * Description  : check pclk frequency and return that value.
 * Arguments    : None
 * Return Value : PCLK frequency
 **********************************************************************************************************************/
double riic_mcu_check_freq (void)
{
    return BSP_PCLKB_HZ;
} /* End of function riic_mcu_check_freq() */

    #if (1U == RIIC_CFG_CH0_INCLUDED)
/***********************************************************************************************************************
 * Function Name: riic0_eei_isr
 * Description  : Interrupt EEI handler for channel 0.
 *                Types of interrupt requests transfer error or event generation.
 *                The event generations are arbitration-lost, NACK detection, timeout detection, 
 *                start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic0_eei_isr (void * vect)
{
    riic0_eei_sub();
} /* End of function riic0_eei_isr() */

/***********************************************************************************************************************
 * Function Name: riic0_txi_isr
 * Description  : Interrupt TXI handler for channel 0.
 *                Types of interrupt requests transmission data empty.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT(riic0_txi_isr, VECT(RIIC0, TXI0))
R_BSP_ATTRIB_STATIC_INTERRUPT void riic0_txi_isr (void)
{
    riic0_txi_sub();
} /* End of function riic0_txi_isr() */

/***********************************************************************************************************************
 * Function Name: riic0_rxi_isr
 * Description  : Interrupt RXI handler for channel 0.
 *                Types of interrupt requests reception end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT(riic0_rxi_isr, VECT(RIIC0, RXI0))
R_BSP_ATTRIB_STATIC_INTERRUPT void riic0_rxi_isr (void)
{
    riic0_rxi_sub();
} /* End of function riic0_rxi_isr() */

/***********************************************************************************************************************
 * Function Name: riic0_tei_isr
 * Description  : Interrupt TEI handler for channel 0.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic0_tei_isr (void * vect)
{
    riic0_tei_sub();
} /* End of function riic0_tei_isr() */
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
/***********************************************************************************************************************
 * Function Name: riic1_eei_isr
 * Description  : Interrupt EEI handler for channel 1.
 *                Types of interrupt requests transfer error or event generation.
 *                The event generations are arbitration-lost, NACK detection, timeout detection, 
 *                start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic1_eei_isr (void * vect)
{
    riic1_eei_sub();
} /* End of function riic1_eei_isr() */

/***********************************************************************************************************************
 * Function Name: riic1_txi_isr
 * Description  : Interrupt TXI handler for channel 1.
 *                Types of interrupt requests transmission data empty.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT(riic1_txi_isr, VECT(RIIC1,TXI1))
R_BSP_ATTRIB_STATIC_INTERRUPT void riic1_txi_isr (void)
{
    riic1_txi_sub();
} /* End of function riic1_txi_isr() */

/***********************************************************************************************************************
 * Function Name: riic1_rxi_isr
 * Description  : Interrupt RXI handler for channel 1.
 *                Types of interrupt requests reception end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT(riic1_rxi_isr, VECT(RIIC1,RXI1))
R_BSP_ATTRIB_STATIC_INTERRUPT void riic1_rxi_isr (void)
{
    riic1_rxi_sub();
} /* End of function riic1_rxi_isr() */

/***********************************************************************************************************************
 * Function Name: riic1_tei_isr
 * Description  : Interrupt TEI handler for channel 1.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic1_tei_isr (void * vect)
{
    riic1_tei_sub();
} /* End of function riic1_tei_isr() */
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
/***********************************************************************************************************************
 * Function Name: riic2_eei_isr
 * Description  : Interrupt EEI handler for channel 2.
 *                Types of interrupt requests transfer error or event generation.
 *                The event generations are arbitration-lost, NACK detection, timeout detection, 
 *                start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic2_eei_isr(void * vect)
{
    riic2_eei_sub();
} /* End of function riic2_eei_isr() */

/***********************************************************************************************************************
 * Function Name: riic2_txi_isr
 * Description  : Interrupt TXI handler for channel 2.
 *                Types of interrupt requests transmission data empty.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT(riic2_txi_isr, VECT(RIIC2,TXI2))
R_BSP_ATTRIB_STATIC_INTERRUPT void riic2_txi_isr (void)
{
    riic2_txi_sub();
} /* End of function riic2_txi_isr() */

/***********************************************************************************************************************
 * Function Name: riic2_rxi_isr
 * Description  : Interrupt RXI handler for channel 2.
 *                Types of interrupt requests reception end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
R_BSP_PRAGMA_STATIC_INTERRUPT(riic2_rxi_isr, VECT(RIIC2,RXI2))
R_BSP_ATTRIB_STATIC_INTERRUPT void riic2_rxi_isr (void)
{
    riic2_rxi_sub();
} /* End of function riic2_rxi_isr() */

/***********************************************************************************************************************
 * Function Name: riic2_tei_isr
 * Description  : Interrupt TEI handler for channel 2.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic2_tei_isr(void * vect)
{
    riic2_tei_sub();
} /* End of function riic2_tei_isr() */
    #endif

#endif /* defined(BSP_MCU_RX72M) */

