/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2020 CRI Middleware Co., Ltd.
 *
 * Library  : Aeropoint Lite Runtime
 * Module   : Library System Header
 * File     : cri_sdc_sdmem_rx_pin.h
 *
 ***************************************************************************/

#ifndef CRI_SDC_SDMEM_RX_PIN_H
#define CRI_SDC_SDMEM_RX_PIN_H

#include "cri_sdc_sdmem_rx_pin_config.h"
#include "r_sdc_sd_rx_if.h"

typedef enum
{
    SDC_SD_DELAY_MICROSECS = 1000000,  
    SDC_SD_DELAY_MILLISECS = 1000,     
    SDC_SD_DELAY_SECS = 1              
} sdc_sd_delay_units_t;

sdc_sd_status_t r_sdc_sdmem_power_Initialize(uint32_t card_no);
sdc_sd_status_t r_sdc_sdmem_power_on(uint32_t card_no);
sdc_sd_status_t r_sdc_sdmem_power_off(uint32_t card_no);
bool            r_sdc_sdmem_softwaredelay(uint32_t delay, sdc_sd_delay_units_t units);

#endif

