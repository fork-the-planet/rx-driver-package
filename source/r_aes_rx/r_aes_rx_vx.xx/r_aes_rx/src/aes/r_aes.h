/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         r_aes.h
 * @brief        AES Library header file.
 **********************************************************************************************************************/

#ifndef R_AES_H
    #define R_AES_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
    #include "r_stdint.h"
    #include "r_mw_version.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* Library compiling options (default) */
    #define __COMPILE_DEFAULT_EMPHASIS_SPEED__   (1) /* compile with emphasis on execution performance */
    #define __COMPILE_DEFAULT_EMPHASIS_SIZE__    (2) /* compile with emphasis on code size */

    #if defined (__RX) ||(__GNUC__) ||(__ICCRX__)
        #define __SUPPORT_AES128__
        #define __SUPPORT_AES256__
        #define __COMPILE_EMPHASIS_DEFAULT__   (__COMPILE_DEFAULT_EMPHASIS_SPEED__)
    #elif defined (__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)
        #define __SUPPORT_AES128__
        #define __SUPPORT_AES256__
        #define __COMPILE_EMPHASIS_DEFAULT__   (__COMPILE_DEFAULT_EMPHASIS_SIZE__)
    #endif

    #define AES_KEY128_LEN      (16)        /* 128 bits (16 bytes) */
    #define AES_KEY192_LEN      (24)        /* 192 bits (24 bytes) */
    #define AES_KEY256_LEN      (32)        /* 256 bits (32 bytes) */
    #define AES_EKEY128_LEN     (44)        /* 176 bytes (44*4(uint32_t)) */
    #define AES_EKEY192_LEN     (52)        /* 208 bytes (52*4(uint32_t)) */
    #define AES_EKEY256_LEN     (60)        /* 240 bytes (60*4(uint32_t)) */
    #define AES_BLOCK_SIZE      (16)        /* 128 bits (16 bytes) */
    #define AES_IVEC_SIZE       (16)        /* 128 bits (16 bytes) */

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/
extern const mw_version_t far R_aes_version;

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
/* Function Name: R_Aes_128_Keysch */
/******************************************************************************
 * Function Name: R_Aes_128_Keysch
 **************************************************************************//**
 * @brief AES 128-bit Key Schedule
 * @param[in] key Key data area (16 byte).
 * @param[out] ekey Expanded key area (176 byte).
 * @retval none.
 * @details The R_Aes_128_Keysch function executes the key schedule of AES.
 * The R_Aes_128_Keysch function expands the given key specified by the first
 * argument "key" and writes the expanded key to an "ekey". Because 176 bytes
 * memory area is required to store the expansion key, "ekey" has to point to
 * the memory area of at least 176 bytes.
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined.
 */
void R_Aes_128_Keysch (uint8_t near *key, uint32_t near *ekey);

/* Function Name: R_Aes_128_Cbcenc */
/******************************************************************************
 * Function Name: R_Aes_128_Cbcenc
 **************************************************************************//**
 * @brief The data encryption functions that use the AES encryption technology.
 * @param[in] pdat Plain text area (block * 16 byte).
 * @param[out] cdat Cipher text area (block * 16 byte).
 * @param[in,out] ivec Initialization vector area (16 byte).
 * @param[in] ekey Expanded key area (176 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_128_Cbcenc() function encrypts the plain text at a
 * specified address (the first argument "pdat") by using the expanded key (the
 * forth argument "ekey") with initialization vector (the third argument "ivec")
 * in CBC mode and outputs cipher text to a designated address (the second
 * argument "cdat"). The amount specified by the number of blocks (the fifth
 * argument "block" and each block is 16 byte in length) is encrypted. The
 * "ivec" is used as16-byte work area. When the block encryption has finished,
 * the last encrypted block data would be output to the "ivec".
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined. It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined). If store the data excluding
 * output from R_Aes_128_Keysch() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_128_Cbcenc (uint8_t near *pdat , uint8_t near *cdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);

/* Function Name: R_Aes_128_Cbcdec */
/******************************************************************************
 * Function Name: R_Aes_128_Cbcdec
 **************************************************************************//**
 * @brief The data decryption functions that use the AES encryption technology.
 * @param[in] cdat Cipher text area (block * 16 byte).
 * @param[out] pdat Plain text area (block * 16 byte).
 * @param[in,out] ivec Initialization vector area (16 byte).
 * @param[in] ekey Expanded key area (176 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_128_Cbcdec() function decrypts the cipher text at a
 * specified address (the first argument "cdat") by using the expanded key (the
 * forth argument "key") with initialization vector (the third argument "ivec")
 * in CBC mode and outputs plain text to a designated address (the second
 * argument "pdat"). The amount specified by the number of blocks (the fifth
 * argument "block" and each block is 16 byte in length) is encrypted. The"ivec"
 * is used as 16-byte work area. When the block encryption has finished, the
 * last decrypted block data would be output to the "ivec".
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined. It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined). If store the data excluding
 * output from R_Aes_128_Keysch() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_128_Cbcdec (uint8_t near *cdat , uint8_t near *pdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);

/* Function Name: R_Aes_128_Ecbenc */
/******************************************************************************
 * Function Name: R_Aes_128_Ecbenc
 **************************************************************************//**
 * @brief The data encryption functions that use the AES encryption technology.
 * @param[in] pdat Plain text area (block * 16 byte).
 * @param[out] cdat Cipher text area (block * 16 byte).
 * @param[in] ekey Expanded key area (176 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_128_Ecbenc() function encrypts the plain text at a
 * specifie daddress (the first argument "pdat") by using the expanded key (the
 * third argument "ekey") in ECB mode and outputs cipher text to a designated
 * address (the second argument "cdat"). The amount specified by the number of
 * blocks (the forth argument"block" and each block is 16 byte in length) is
 * encrypted.
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined. It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined.) If store the data excluding
 * output from R_Aes_128_Ecbenc() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_128_Ecbenc (uint8_t near *pdat, uint8_t near *cdat, uint32_t near *ekey, uint16_t block);

/* Function Name: R_Aes_128_Ecbdec */
/******************************************************************************
 * Function Name: R_Aes_128_Ecbdec
 **************************************************************************//**
 * @brief The data decryption functions that use the AES encryption technology.
 * @param[in] cdat Cipher text area (block * 16 byte).
 * @param[out] pdat Plain text area (block * 16 byte).
 * @param[in] ekey Expanded key area (176 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_128_Ecbdec() function decrypts the cipher text at a
 * specified address (the first argument "cpdat") by using the expanded key (the
 * third argument "ekey") in ECB mode and outputs plain text (the second
 * argument "pdat"). The amount specified by the number of blocks (the to a
 * designated address forth argument "block" and each block is 16 byte in 
 * length) is encrypted.
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined. It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined). If store the data excluding
 * output from R_Aes_128_Ecbdec() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_128_Ecbdec (uint8_t near *cdat, uint8_t near *pdat, uint32_t near *ekey, uint16_t block);

/* Function Name: R_Aes_192_Keysch */
/******************************************************************************
 * Function Name: R_Aes_192_Keysch
 **************************************************************************//**
 * @brief AES 192-bit Key Schedule
 * @param[in] key Key data area (24 byte).
 * @param[out] ekey Expanded key area (208 byte).
 * @retval none.
 * @details The R_Aes_192_Keysch() function executes the key schedule of AES.
 * The R_Aes_192_Keysch() function expands the given key specified by the first
 * argument "key" and writes the expanded key to an "ekey". Because 208 bytes
 * memory area is required to store the expansion key, "ekey" has to point to
 * the memory area of at least 208 bytes.
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined.
 */
void R_Aes_192_Keysch (uint8_t near *key, uint32_t near *ekey);

/* Function Name: R_Aes_192_Cbcenc */
/******************************************************************************
 * Function Name: R_Aes_192_Cbcenc
 **************************************************************************//**
 * @brief The data encryption functions that use the AES encryption technology.
 * @param[in] pdat Plain text area (block * 16 byte).
 * @param[out] cdat Cipher text area (block * 16 byte).
 * @param[in,out] ivec Initialization vector area (16 byte).
 * @param[in] ekey Expanded key area (208 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_192_Cbcenc() function encrypts the plain text at a
 * specified address (the first argument "pdat") by using the expanded key (the
 * forth argument "ekey") with initialization vector (the third argument "ivec")
 * in CBC mode and outputs cipher text to a designated address (the second
 * argument "cdat"). The amount specified by the number of blocks (the fifth
 * argument "block" and each block is 16 byte in length) is encrypted. The
 * "ivec" is used as16-byte work area. When the block encryption has finished,
 * the last encrypted block data would be output to the "ivec".
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined.It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined). If store the data excluding
 * output from R_Aes_192_Keysch() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_192_Cbcenc (uint8_t near *pdat , uint8_t near *cdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);

/* Function Name: R_Aes_192_Cbcdec */
/******************************************************************************
 * Function Name: R_Aes_192_Cbcdec
 **************************************************************************//**
 * @brief The data decryption functions that use the AES encryption technology.
 * @param[in] cdat Cipher text area (block * 16 byte).
 * @param[out] pdat Plain text area (block * 16 byte).
 * @param[in,out] ivec Initialization vector area (16 byte).
 * @param[in] ekey Expanded key area (208 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_192_Cbcdec() function decrypts the cipher text at a
 * specified address (the first argument "cdat") by using the expanded key (the
 * forth argument "key") with initialization vector (the third argument "ivec")
 * in CBC mode and outputs plain text to a designated address (the second
 * argument "pdat"). The amount specified by the number of blocks (the fifth
 * argument "block" and each block is 16 byte in length) is encrypted. The"ivec"
 * is used as 16-byte work area. When the block encryption has finished, the
 * last decrypted block data would be output to the "ivec".
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined. It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined). If store the data excluding
 * output from R_Aes_192_Keysch() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_192_Cbcdec (uint8_t near *cdat, uint8_t near *pdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);

/* Function Name: R_Aes_192_Ecbenc */
/******************************************************************************
 * Function Name: R_Aes_192_Ecbenc
 **************************************************************************//**
 * @brief The data encryption functions that use the AES encryption technology.
 * @param[in] pdat Plain text area (block * 16 byte).
 * @param[out] cdat Cipher text area (block * 16 byte).
 * @param[in] ekey Expanded key area (208 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_192_Ecbenc() function encrypts the plain text at a
 * specified address (the first argument "pdat") by using the expanded key (the
 * third argument "ekey") in ECB mode and outputs cipher text to a designated
 * address (the second argument "cdat"). The amount specified by the number of
 * blocks (the forth argument"block" and each block is 16 byte in length) is
 * encrypted.
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined. It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined.) If store the data excluding
 * output from R_Aes_192_Ecbenc() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_192_Ecbenc (uint8_t near *pdat, uint8_t near *cdat, uint32_t near *ekey, uint16_t block);

/* Function Name: R_Aes_192_Ecbdec */
/******************************************************************************
 * Function Name: R_Aes_192_Ecbdec
 **************************************************************************//**
 * @brief The data decryption functions that use the AES encryption technology.
 * @param[in] cdat Cipher text area (block * 16 byte).
 * @param[out] pdat Plain text area (block * 16 byte).
 * @param[in] ekey Expanded key area (208 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_192_Ecbdec() function decrypts the cipher text at a
 * specified address (the first argument "cpdat") by using the expanded key (the
 * third argument "ekey") in ECB mode and outputs plain text (the second
 * argument "pdat"). The amount specified by the number of blocks (the to a
 * designated address forth argument "block" and each block is 16 byte in 
 * length) is encrypted.
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined. It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined). If store the data excluding
 * output from R_Aes_192_Ecbdec() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_192_Ecbdec (uint8_t near *cdat, uint8_t near *pdat, uint32_t near *ekey, uint16_t block);

/* Function Name: R_Aes_256_Keysch */
/******************************************************************************
 * Function Name: R_Aes_256_Keysch
 **************************************************************************//**
 * @brief AES 256-bit Key Schedule
 * @param[in] key Key data area (32 byte).
 * @param[out] ekey Expanded key area (240 byte).
 * @retval none.
 * @details The R_Aes_256_Keysch() function executes the key schedule of AES.
 * The R_Aes_256_Keysch() function expands the given key specified by the first
 * argument "key" and writes the expanded key to an "ekey". Because 240 bytes
 * memory area is required to store the expansion key, "ekey" has to point to
 * the memory area of at least 240 bytes.
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined.
 */
void R_Aes_256_Keysch (uint8_t near *key, uint32_t near *ekey);

/* Function Name: R_Aes_256_Cbcenc */
/******************************************************************************
 * Function Name: R_Aes_256_Cbcenc
 **************************************************************************//**
 * @brief The data encryption functions that use the AES encryption technology.
 * @param[in] pdat Plain text area (block * 16 byte).
 * @param[out] cdat Cipher text area (block * 16 byte).
 * @param[in,out] ivec Initialization vector area (16 byte).
 * @param[in] ekey Expanded key area (240 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_256_Cbcenc() function encrypts the plain text at a
 * specified address (the first argument "pdat") by using the expanded key (the
 * forth argument "ekey") with initialization vector (the third argument "ivec")
 * in CBC mode and outputs cipher text to a designated address (the second
 * argument "cdat"). The amount specified by the number of blocks (the fifth
 * argument "block" and each block is 16 byte in length) is encrypted. The
 * "ivec" is used as16-byte work area. When the block encryption has finished,
 * the last encrypted block data would be output to the "ivec".
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter, the
 * functions behavior is undefined. It is possible to allocate plain text area
 * and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined). If store the data excluding
 * output from R_Aes_256_Keysch() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_256_Cbcenc (uint8_t near *pdat , uint8_t near *cdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);

/* Function Name: R_Aes_256_Cbcdec */
/******************************************************************************
 * Function Name: R_Aes_256_Cbcdec
 **************************************************************************//**
 * @brief The data decryption functions that use the AES encryption technology.
 * @param[in] cdat Cipher text area (block * 16 byte).
 * @param[out] pdat Plain text area (block * 16 byte).
 * @param[in, out] ivec Initialization vector area (16 byte).
 * @param[in] ekey Expanded key area (240 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_256_Cbcdec() function decrypts the cipher text at a
 * specified address (the first argument "cdat") by using the expanded key (the
 * forth argument "key") with initialization vector (the third argument "ivec")
 * in CBC mode and outputs plain text to a designated address (the second
 * argument "pdat"). The amount specified by the number of blocks (the fifth
 * argument "block" and each block is 16 byte in length) is encrypted. The"ivec"
 * is used as 16-byte work area. When the block encryption has finished, the
 * last decrypted block data would be output to the "ivec".
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter, the
 * functions behavior is undefined. It is possible to allocate plain text area
 * and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined). If store the data excluding
 * output from R_Aes_256_Keysch() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_256_Cbcdec (uint8_t near *cdat, uint8_t near *pdat, uint8_t near *ivec, uint32_t near *ekey,
    uint16_t block);

/* Function Name: R_Aes_256_Ecbenc */
/******************************************************************************
 * Function Name: R_Aes_256_Ecbenc
 **************************************************************************//**
 * @brief The data encryption functions that use the AES encryption technology.
 * @param[in] pdat Plain text area (block * 16 byte).
 * @param[out] cdat Cipher text area (block * 16 byte).
 * @param[in] ekey Expanded key area (240 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_256_Ecbenc() function encrypts the plain text at a specified
 * address (the first argument "pdat") by using the expanded key (the third
 * argument "ekey") in ECB mode and outputs cipher text to a designated address
 * (the second argument "cdat"). The amount specified by the number of blocks
 * (the forth argument"block" and each block is 16 byte in length) is encrypted.
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined. It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined.) If store the data excluding
 * output from R_Aes_256_Ecbenc() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_256_Ecbenc (uint8_t near *pdat, uint8_t near *cdat, uint32_t near *ekey, uint16_t block);

/* Function Name: R_Aes_256_Ecbdec */
/******************************************************************************
 * Function Name: R_Aes_256_Ecbdec
 **************************************************************************//**
 * @brief The data decryption functions that use the AES encryption technology.
 * @param[in] cdat Cipher text area (block * 16 byte).
 * @param[out] pdat Plain text area (block * 16 byte).
 * @param[in] ekey Expanded key area (240 byte).
 * @param[in] block Number of encryption block (1 - any block).
 * @retval none.
 * @details The R_Aes_256_Ecbdec() function decrypts the cipher text at a
 * specified address (the first argument "cpdat") by using the expanded key (the
 * third argument "ekey") in ECB mode and outputs plain text (the second
 * argument "pdat"). The amount specified by the number of blocks (the to a
 * designated address forth argument "block" and each block is 16 byte in 
 * length) is encrypted.
 * @note When an invalid pointer (ex. Null Pointer) is passed as a parameter,
 * the functions behavior is undefined. It is possible to allocate plain text
 * area and cipher text area in same address. (If these areas are not completely
 * overlap, the function behavior is not defined). If store the data excluding
 * output from R_Aes_256_Ecbdec() to the ekey, the function behavior is not
 * defined.
 */
void R_Aes_256_Ecbdec (uint8_t near *cdat, uint8_t near *pdat, uint32_t near *ekey, uint16_t block);

/* Function Name: R_Aes_Table_Init */
/******************************************************************************************************************//**
 * @brief         AES Table Data Transmission Function (M16C only).
 * @warning       none.
 * @retval        none.
 *********************************************************************************************************************/
void R_Aes_Table_Init (void);

/* Function Name: R_Aes_128_OtfCbcenc */
/******************************************************************************************************************//**
 * @brief         AES 128-bit on-the-fly Encryption Function (CBC Mode).
 * @warning       When an invalid pointer (ex. Null Pointer) is passed as a parameter, the functions behavior is
 *                undefined.It is possible to allocate plain text area and cipher text area in same address. (If these
 *                areas are not completely overlap, the function behavior is not defined). When encrypting continuation
 *                data and this function needs to be called two or more times, the right plain text result can be output
 *                by this function, without changing ivec.
 * @retval        none.
 *********************************************************************************************************************/
void R_Aes_128_OtfCbcenc (uint8_t near *, uint8_t near *, uint8_t near *, uint16_t near *, uint16_t);

/* Function Name: R_Aes_128_OtfCbcdec */
/******************************************************************************************************************//**
 * @brief         AES 128-bit on-the-fly Decryption Function (CBC Mode).
 * @warning       When an invalid pointer (ex. Null Pointer) is passed as a parameter, the functions behavior is
 *                undefined. It is possible to allocate plain text area and cipher text area in same address. (If these
 *                areas are not completely overlap, the function behavior is not defined).
 * @retval        none.
 *********************************************************************************************************************/
void R_Aes_128_OtfCbcdec (uint8_t near *, uint8_t near *, uint8_t near *, uint16_t near *, uint16_t);

/* Function Name: R_Aes_128_OtfEcbenc */
/******************************************************************************************************************//**
 * @brief         AES 128-bit on-the-fly Encryption Function (ECB Mode).
 * @warning       When an invalid pointer (ex. Null Pointer) is passed as a parameter, the functions behavior is
 *                undefined. It is possible to allocate plain text area and cipher text area in same address. (If these
 *                areas are not completely overlap, the function behavior is not defined).
 * @retval        none.
 *********************************************************************************************************************/
void R_Aes_128_OtfEcbenc (uint8_t near *, uint8_t near *, uint16_t near *, uint16_t);

/* Function Name: R_Aes_128_OtfEcbdec */
/******************************************************************************************************************//**
 * @brief         AES 128-bit on-the-fly Decryption Function (ECB Mode).
 * @warning       When an invalid pointer (ex. Null Pointer) is passed as a parameter, the functions behavior is
 *                undefined. It is possible to allocate plain text area and cipher text area in same address. (If these
 *                areas are not completely overlap, the function behavior is not defined).
 * @retval        none.
 *********************************************************************************************************************/
void R_Aes_128_OtfEcbdec (uint8_t near *, uint8_t near *, uint16_t near *, uint16_t);

/* Function Name: R_Aes_256_OtfEcbenc */
/******************************************************************************************************************//**
 * @brief         AES 256-bit on-the-fly Encryption Function (ECB Mode).
 * @warning       When an invalid pointer (ex. Null Pointer) is passed as a parameter, the functions behavior is
 *                undefined. It is possible to allocate plain text area and cipher text area in same address. (If these
 *                areas are not completely overlap, the function behavior is not defined).
 * @retval        none.
 *********************************************************************************************************************/
void R_Aes_256_OtfEcbenc (uint8_t near *, uint8_t near *, uint16_t near *, uint16_t);

/* Function Name: R_Aes_256_OtfEcbdec */
/******************************************************************************************************************//**
 * @brief         AES 256-bit on-the-fly Decryption Function (ECB Mode).
 * @warning       When an invalid pointer (ex. Null Pointer) is passed as a parameter, the functions behavior is
 *                undefined. It is possible to allocate plain text area and cipher text area in same address. (If these
 *                areas are not completely overlap, the function behavior is not defined).
 * @retval        none.
 *********************************************************************************************************************/
void R_Aes_256_OtfEcbdec (uint8_t near *, uint8_t near *, uint16_t near *, uint16_t);

    #if defined(R8C) || defined(M16C) || defined(M32C)
        #pragma PARAMETER R_Aes_128_OtfEcbenc(a0, a1, r2, r3)
        #pragma PARAMETER R_Aes_128_OtfEcbdec(a1, a0, r2, r3)
        #pragma PARAMETER R_Aes_128_OtfCbcenc(a0, a1, r1, r2, r3)
        #pragma PARAMETER R_Aes_128_OtfCbcdec(a1, a0, r1, r2, r3)
        #pragma PARAMETER R_Aes_256_OtfEcbenc(a0, a1, r2, r3)
        #pragma PARAMETER R_Aes_256_OtfEcbdec(a1, a0, r2, r3)
        #pragma PARAMETER R_Aes_256_OtfCbcenc(a0, a1, r1, r2, r3)
        #pragma PARAMETER R_Aes_256_OtfCbcdec(a1, a0, r1, r2, r3)
    #endif

#endif /* R_AES_H */
