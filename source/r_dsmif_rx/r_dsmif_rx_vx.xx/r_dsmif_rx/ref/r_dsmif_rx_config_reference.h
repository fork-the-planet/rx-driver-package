/*
* Copyright (c) 2019 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/*******************************************************************************
* File Name     : r_dsmif_rx_config.h
* Description   : Configures the DSMIF module
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 06.08.2019 1.00     First Release
*              : 20.03.2025 1.02     Changed the disclaimer.
*******************************************************************************/

#ifndef R_DSMIF_CONFIG_HEADER
#define R_DSMIF_CONFIG_HEADER

/*******************************************************************************
Configuration Options
*******************************************************************************/

/* Error interrupt handler priority */
#define DSMIF_ERR_INTR_PRI_LVL  (0x0FU) /* Level 15 (highest) */

/* Wait count for filter setting */
#define DSMIF_SETTING_WAIT_CNT  (100000u)

/* Over current detection low threshold value */
#define DSMIF_OCLTR_VALUE       (1u)

/* Short-circuit detection high threshold value */
#define DSMIF_SHORT_CNT_1       (0x00001FFEu)

/* Short-circuit detection low threshold value */
#define DSMIF_SHORT_CNT_0       (0x00001FFEu)

#endif /* R_DSMIF_CONFIG_HEADER */

/* End of File */
