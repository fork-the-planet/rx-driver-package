/*
* Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef RM_RAI_DATA_SHIPPER_R_CRC_API_COMPLEMENT_H
#define RM_RAI_DATA_SHIPPER_R_CRC_API_COMPLEMENT_H


/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Structure for CRC inputs */
typedef struct st_crc_input_t
{
    uint32_t num_bytes;                ///< Length of input buffer
    uint32_t crc_seed;                 ///< CRC seed value
    void   * p_input_buffer;           ///< Pointer to input buffer
} crc_input_t;

/* CRC APIs */
typedef struct st_crc_api
{
    void (* setCrc8)(void);                 ///< Set CRC8
    void (* inputData)(uint32_t p_dta);     ///< Input data
    void (* getResult)(uint32_t *p_result); ///< Get result
} crc_api_t;

#ifndef CRC_INSTANCE
#define CRC_INSTANCE
/* RX Driver Instance */
typedef struct st_crc_instance
{
    crc_api_t const   *  p_api;
} crc_instance_t;
#endif

#endif
