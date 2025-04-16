/*
* Copyright (c) 2019-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef _MESH_DATAFLASH_
#define _MESH_DATAFLASH_

/*******************************************************************************
* Compilation Switches
*******************************************************************************/
#define DATAFLASH_EN    (1)

/*******************************************************************************
* Prototype declarations
*******************************************************************************/
#if DATAFLASH_EN
uint8_t mesh_dataflash_open(void);
void    mesh_dataflash_close(void);
uint8_t mesh_dataflash_read(uint32_t addr, uint8_t *buff, uint16_t len);
uint8_t mesh_dataflash_write(uint32_t addr, uint8_t *buff, uint16_t len);
uint8_t mesh_dataflash_erase_all(void);
#endif /* DATAFLASH_EN */

#endif /* _MESH_DATAFLASH_ */

