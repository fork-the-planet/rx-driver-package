/*
* Copyright (C) 2013-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name	   : r_compress_jpege.h
* Description  : Header file of JPEG File Compress Library.
***********************************************************************************************************************/
#include "r_stdint.h"
#include "r_mw_version.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define COMPRESS_JPEGE_OK				0
#define COMPRESS_JPEGE_ERROR_ARG		-1
#define COMPRESS_JPEGE_ERROR_WRITE		-2

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
enum r_jpege_in_format_t
{
	JPEGE_IN_RGB565,
	JPEGE_IN_RGB888,
	JPEGE_IN_YCC422,
};

enum r_jpege_out_format_t
{
	JPEGE_OUT_YCC422,
	JPEGE_OUT_YCC420,
};

struct r_jpeg_encode_t
{
	/* JPEG setting */
	uint16_t width;						/* original image's width */
	uint16_t height;					/* original image's height */
	int16_t quality;					/* image quality when encoding an image (default: 64) */
	int16_t restart_interval;			/* RST marker value; when don't use RST marker, set 0 */

	/* input */
	const uint8_t *input_addr;
	uint16_t input_line_byte;
	enum r_jpege_in_format_t input_format;

	/* output */
	uint8_t *outbuff;
	int32_t outbuff_size;
	enum r_jpege_out_format_t output_format;
};

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/
extern const mw_version_t R_compress_jpege_version;

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
/* API */
int32_t R_compress_jpeg(struct r_jpeg_encode_t *);

/* user defined function */
uint8_t * R_jpeg_write_out_buffer(int32_t *rest);

