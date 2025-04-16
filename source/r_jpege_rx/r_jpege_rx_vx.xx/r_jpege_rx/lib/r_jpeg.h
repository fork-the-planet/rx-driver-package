/*
* Copyright (C) 2013-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name	   : r_jpeg.h
* Version      : V.1.01
* Description  : The headre file of JPEG Decoder & JPEG Encoder.
***********************************************************************************************************************/

#ifndef __r_jpeg_h__
#define __r_jpeg_h__

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_stdint.h"
#include "r_mw_version.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Error Code */
#define _JPEG_OK						(0)
#define _JPEG_ERROR						(-1)

/* Constant */
#define _JPEG_DCTSIZE					8
#define _JPEG_DCTSIZE2					(_JPEG_DCTSIZE * _JPEG_DCTSIZE)
#define _JPEG_COMPONENT_NUM				3	/* YCbCr */

#define _JPEG_HUFFVAL_SIZE				256
#define _JPEG_BITS_SIZE					17

/* _jpeg_dec_FMB */
#define _jpeg_work(base)				((base)->_jpeg_work)
#define _jpeg_next_read_byte(base)		((base)->_jpeg_next_read_byte)
#define _jpeg_d_free_in_buffer(base)	((base)->_jpeg_d_free_in_buffer)
#define _jpeg_cur_read_buffer(base)		((base)->_jpeg_cur_read_buffer)
#define _jpeg_cur_bits_offset(base)		((base)->_jpeg_cur_bits_offset)
#define _jpeg_restart_interval(base)	((base)->_jpeg_restart_interval)

/* _jpeg_dec_SMB */
#define _jpeg_d_num_QTBL(base)			((base)->_jpeg_d_num_QTBL)
#define _jpeg_d_number_of_lines(base)	((base)->_jpeg_d_number_of_lines)
#define _jpeg_d_line_length(base)		((base)->_jpeg_d_line_length)
#define _jpeg_d_precision(base)			((base)->_jpeg_d_precision)
#define _jpeg_X_density(base)			((base)->_jpeg_X_density)
#define _jpeg_Y_density(base)			((base)->_jpeg_Y_density)
#define _jpeg_d_num_of_components(base)	((base)->_jpeg_d_num_of_components)
#define _jpeg_d_frame_num_of_components(base)	((base)->_jpeg_d_frame_num_of_components)
#define _jpeg_error_stat(base)			((base)->_jpeg_error_stat)
#define component_info(base)			((base)->component_info)
#define frame_component_info(base)		((base)->frame_component_info)

/* _jpeg_enc_FMB */
#define _jpeg_DCTqtbl(base)				((base)->_jpeg_DCTqtbl)
#define _jpeg_next_output_byte(base)	((base)->_jpeg_next_output_byte)
#define _jpeg_free_in_buffer(base)		((base)->_jpeg_free_in_buffer)
#define _jpeg_cur_put_buffer(base)		((base)->_jpeg_cur_put_buffer)
#define _jpeg_cur_put_bits(base)		((base)->_jpeg_cur_put_bits)
//#define _jpeg_restart_interval(base)	((base)->_jpeg_restart_interval)
#define _jpeg_dc_size(base)				((base)->_jpeg_dc_size)
#define _jpeg_ac_size(base)				((base)->_jpeg_ac_size)

/* _jpeg_enc_SMB */
#define _jpeg_num_QTBL(base)			((base)->_jpeg_num_QTBL)
#define _jpeg_QTBL(base)				((base)->_jpeg_QTBL)
#define _jpeg_precision_QTBL(base)		((base)->_jpeg_precision_QTBL)
#define _jpeg_number_of_lines(base)		((base)->_jpeg_number_of_lines)
#define _jpeg_line_length(base)			((base)->_jpeg_line_length)
//#define component_info(base)			((base)->component_info)
//#define frame_component_info(base)		((base)->frame_component_info)
#define _jpeg_frame_num_of_components(base)	((base)->_jpeg_frame_num_of_components)
#define _jpeg_write_DQT(base)			((base)->_jpeg_write_DQT)
#define _jpeg_write_DHT(base)			((base)->_jpeg_write_DHT)



/* input-buffer */
#define CHECK_BUFF(env, fmb) \
	if (_jpeg_d_free_in_buffer(fmb) == 0) { \
		(*(env->dec_read_input))(env); \
		if (_jpeg_d_free_in_buffer(fmb) == 0) { \
			return _JPEG_ERROR;			/* Caution! use "return" */ \
		} \
	}

#define CHECK_BYTES(n, env)				/* dummy */

#define INPUT_BYTE(var, env, fmb) \
	CHECK_BUFF(env, fmb); \
	var = *_jpeg_next_read_byte(fmb)++; \
	--_jpeg_d_free_in_buffer(fmb);

#define INPUT_2BYTES(var, env, fmb) \
	CHECK_BUFF(env, fmb); \
	var = ((uint16_t)*_jpeg_next_read_byte(fmb)++) << 8; \
	--_jpeg_d_free_in_buffer(fmb); \
	CHECK_BUFF(env, fmb); \
	var += (uint16_t)*_jpeg_next_read_byte(fmb)++; \
	--_jpeg_d_free_in_buffer(fmb);

#define READ_NBYTE(p, n, env, fmb) \
	{ \
		int16_t _tmp_i = n; \
		uint8_t *_tmp_p; \
		_tmp_p = p; \
		while (_tmp_i--) { \
			CHECK_BUFF(env, fmb); \
			*_tmp_p++ = *_jpeg_next_read_byte(fmb)++; \
			--_jpeg_d_free_in_buffer(fmb); \
		} \
	}

#define SKIP_BYTES(n, env, fmb) \
	{ \
		int16_t _tmp_i = n; \
		while (_tmp_i--) { \
			CHECK_BUFF(env, fmb); \
			++_jpeg_next_read_byte(fmb); \
			--_jpeg_d_free_in_buffer(fmb); \
		} \
	}

#define READ_LENGTH(len, env, fmb) \
		CHECK_BYTES(2, env); \
		INPUT_2BYTES(len, env, fmb); \
		(len) -= 2; \
		CHECK_BYTES(len, env);

#define WRITE_BYTE(c, env) \
	*_jpeg_next_output_byte(env->encFMB) = (c); \
	++_jpeg_next_output_byte(env->encFMB); \
	--_jpeg_free_in_buffer(env->encFMB); \
	if (_jpeg_free_in_buffer(env->encFMB) == 0) { \
		(*(env->enc_dump_func))(env); \
		if (_jpeg_free_in_buffer(env->encFMB) == 0) { \
			return _JPEG_ERROR;			/* Caution! use "return" */ \
		} \
	}


/* Stream Check */
#define STREAM_HEADER_FLAG_CLEAR(env)	\
    (env)->flagStreamHeader[0] = 0;		\
    (env)->flagStreamHeader[1] = 0;		\
    (env)->flagStreamHeader[2] = 0;

#define STREAM_HEADER_FLAG_SET(env, n)	\
    if ((n) >= 32)						\
    {									\
        (env)->flagStreamHeader[1] |= (1<<((n)-32));	\
    }									\
    else								\
    {									\
        (env)->flagStreamHeader[0] |= (1<<(n));	\
    }
/*
	flagStreamHeader[2]
	    *--------+--------+----+----+----+----*
	    |        |        |    |    |    |    |
	    *--------+--------+----+----+----+----*
	                           | AC   DC |    |
	                           |   DHT   | DQT|
 */
#define STREAM_HEADER_DQT_SET(env, n)	(env)->flagStreamHeader[2] |= (1<<(n));
/* Tc=0 -> DC table, Tc=1 -> AC table, Th shall be 0 or 1 */
#define DQT_BITS						(4)
#define DHT_INDEX2N(n)					(DQT_BITS+(((n)&0x10)>>2)+((n)&0x0f))
#define STREAM_HEADER_DHT_SET(env, n)	(env)->flagStreamHeader[2] |= (1<<(n));
#define STREAM_HEADER_CHECK_QUNAT_TABLE(env, n)	(((env)->flagStreamHeader[2])&(1u<<(n)))
#define STREAM_HEADER_CHECK_DC_TABLE(env, n)	(((env)->flagStreamHeader[2])&(1u<<(n+DQT_BITS)))
#define STREAM_HEADER_CHECK_AC_TABLE(env, n)	(((env)->flagStreamHeader[2])&(1u<<(n+DQT_BITS+4)))

#define IS_SOF0_MAKER	0x00000001
#define IS_DHT_MAKER	0x00000010
#define IS_SOI_MAKER	0x01000000
#define IS_EOI_MAKER	0x02000000
#define IS_SOS_MAKER	0x04000000
#define IS_DQT_MAKER	0x08000000
#define IS_DRI_MAKER	0x20000000
#define IS_APP0_MAKER	0x00000001
#define IS_APP1_MAKER	0x00000002
#define IS_APP14_MAKER	0x00004000
#define IS_COM_MAKER	0x40000000

#define STREAM_HEADER_MUST_SET0			(IS_SOF0_MAKER | IS_DHT_MAKER | IS_SOI_MAKER | IS_SOS_MAKER | IS_DQT_MAKER)	// 0x0D000011
#define STREAM_HEADER_MUST_SET1			(0)		// 0x00000000

#define STREAM_HEADER_CHECK(f,v)		((f) != (v))
#define STREAM_HEADER_CHECK_SOF0(flag)	STREAM_HEADER_CHECK((flag)&IS_SOI_MAKER,IS_SOI_MAKER)
#define STREAM_HEADER_CHECK_SOS(flag)	STREAM_HEADER_CHECK((flag)&(IS_SOI_MAKER|IS_SOF0_MAKER),(IS_SOI_MAKER|IS_SOF0_MAKER))
#define STREAM_HEADER_FLAG_CHECK(env)	((((env)->flagStreamHeader[0]) & (STREAM_HEADER_MUST_SET0)) == (STREAM_HEADER_MUST_SET0)) && ((((env)->flagStreamHeader[1]) & (STREAM_HEADER_MUST_SET1)) == (STREAM_HEADER_MUST_SET1))



/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
struct component_info
{
	uint8_t component_id[_JPEG_COMPONENT_NUM + 1];		/* +1 for alignment */
	uint8_t hsample_ratio[_JPEG_COMPONENT_NUM + 1];		/* +1 for alignment */
	uint8_t vsample_ratio[_JPEG_COMPONENT_NUM + 1];		/* +1 for alignment */
	uint8_t quant_tbl_no[_JPEG_COMPONENT_NUM + 1];		/* +1 for alignment */
};

struct frame_component_info
{
	uint8_t component_id[_JPEG_COMPONENT_NUM + 1];		/* +1 for alignment */
	uint8_t dc_tbl_no[_JPEG_COMPONENT_NUM + 1];			/* +1 for alignment */
	uint8_t ac_tbl_no[_JPEG_COMPONENT_NUM + 1];			/* +1 for alignment */
};

struct _jpeg_dec_FMB
{
	uint8_t fmb1[512];					/* reserved */

	uint16_t _jpeg_work[_JPEG_HUFFVAL_SIZE + 1];		/* reserved */
	int16_t _jpeg_restart_interval;
	uint8_t *_jpeg_next_read_byte;
	int32_t _jpeg_d_free_in_buffer;
	uint32_t _jpeg_cur_read_buffer;
	uint32_t _jpeg_cur_bits_offset;

	uint8_t fmb2[3632];					/* reserved */
};

struct _jpeg_dec_FMC
{
	uint8_t fmc[1284];					/* reserved */
};

struct _jpeg_dec_SMB
{
	int32_t _jpeg_d_num_QTBL;
	int32_t _jpeg_thinning_mode;
	uint16_t _jpeg_d_number_of_lines;
	uint16_t _jpeg_d_line_length;

	int16_t _jpeg_X_density;
	int16_t _jpeg_Y_density;
	int32_t _jpeg_d_frame_num_of_components;
	struct frame_component_info frame_component_info;
	int32_t _jpeg_error_stat;
	uint8_t _jpeg_d_precision;
	int32_t _jpeg_d_num_of_components;
	struct component_info component_info;
	int32_t flagStreamHeader[3];
};

struct _jpeg_enc_FMB
{
	int32_t _jpeg_work[_JPEG_DCTSIZE2];
	int16_t _jpeg_DCTqtbl[_JPEG_DCTSIZE2*3];
	uint8_t *_jpeg_next_output_byte;
	int32_t _jpeg_free_in_buffer;
	uint32_t _jpeg_cur_put_buffer;
	uint32_t _jpeg_cur_put_bits;
	int32_t _jpeg_restart_interval;
	int32_t _jpeg_thinning_mode;
	int32_t _jpeg_dc_size[_JPEG_COMPONENT_NUM + 1];
	int32_t _jpeg_ac_size[_JPEG_COMPONENT_NUM + 1];
};

struct _jpeg_enc_FMC
{
	uint32_t _jpeg_fmcData[634];
};

struct _jpeg_enc_SMB
{
	int32_t _jpeg_num_QTBL;
	uint16_t _jpeg_QTBL[_JPEG_DCTSIZE2*_JPEG_COMPONENT_NUM];
	uint8_t _jpeg_precision_QTBL[_JPEG_COMPONENT_NUM + 1];		/* +1 for alignment */
	uint16_t _jpeg_number_of_lines;
	uint16_t _jpeg_line_length;
	struct component_info component_info;
	struct frame_component_info frame_component_info;
	int32_t _jpeg_frame_num_of_components;
	uint8_t _jpeg_write_DQT;
	uint8_t _jpeg_write_DHT;
	uint8_t dummy1;
	uint8_t dummy2;
};

struct _jpeg_enc_SMC
{
	uint32_t _jpeg_smcData[174];
};

struct _jpeg_working
{
	/* encode */
	struct _jpeg_enc_FMB *encFMB;
	struct _jpeg_enc_FMC *encFMC;
	struct _jpeg_enc_SMB *encSMB;
	struct _jpeg_enc_SMC *encSMC;
	void (*enc_dump_func)(struct _jpeg_working *);

	/* decode */
	struct _jpeg_dec_FMB *decFMB;
	struct _jpeg_dec_FMC *decFMC;
	struct _jpeg_dec_SMB *decSMB;
	void (*dec_read_input)(struct _jpeg_working *);
};

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
/* decode */
extern const mw_version_t R_jpegd_version;
extern const struct _jpeg_dec_FMC * const _top_of_jpeg_dec_FMC;

int16_t R_jpeg_make_huff_table(uint8_t, uint8_t *, uint8_t *, int16_t, struct _jpeg_working *);
int16_t R_jpeg_add_iquant_table(int16_t, uint16_t *, struct _jpeg_working *);
int16_t R_jpeg_readRST(struct _jpeg_working *);
int16_t R_jpeg_decode_one_block(int16_t, int16_t, int16_t, int16_t *, struct _jpeg_working *);
void R_jpeg_IDCT(int16_t *, uint8_t **, int16_t, int16_t, struct _jpeg_working *);

/* encode */
extern const mw_version_t R_jpege_version;
extern const struct _jpeg_enc_FMC _jpeg_enc_fmcData;
extern const struct _jpeg_enc_SMC _jpeg_enc_smcData;

void R_jpeg_add_quant_table(int32_t, uint16_t *, int32_t, struct _jpeg_working *);
void R_jpeg_DCT(uint8_t **, int32_t, int32_t, int16_t *, struct _jpeg_working *);
int32_t R_jpeg_encode_one_block(int16_t *, int32_t, int32_t, int32_t, struct _jpeg_working *);
int32_t R_jpeg_writeDRI(int32_t, struct _jpeg_working *);
int32_t R_jpeg_writeRST(int32_t, struct _jpeg_working *);
int32_t R_jpeg_writeEOI(struct _jpeg_working *);
int32_t R_jpeg_flush_bits(struct _jpeg_working *);

#endif /* __r_jpeg_h__ */
