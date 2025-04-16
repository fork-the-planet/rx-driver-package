/*​
* Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates​
*​
* SPDX-License-Identifier: BSD-3-Clause​
*/
/***********************************************************************************************************************
 * @file         r_sha.h
 * @brief        SHA Library header file.
 **********************************************************************************************************************/
#ifndef R_SHA_H
    #define R_SHA_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
    #include "r_stdint.h"
    #include "r_mw_version.h"
    #include "platform.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* Library compiling options (default) */
    #define __COMPILE_DEFAULT_EMPHASIS_SPEED__   (1) /* compile with emphasis on execution performance */
    #define __COMPILE_DEFAULT_EMPHASIS_SIZE__    (2) /* compile with emphasis on code size */

    #if defined (__RX) || (__GNUC__) || (__ICCRX__)
        #define __SUPPORT_SHA1__
        #define __SUPPORT_SHA256__
        #define __SUPPORT_SHA384__
        #define __COMPILE_EMPHASIS_DEFAULT__   __COMPILE_DEFAULT_EMPHASIS_SPEED__
    #elif defined (__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)
        #define __SUPPORT_SHA1__
        #define __SUPPORT_SHA256__
        #define __COMPILE_EMPHASIS_DEFAULT__   __COMPILE_DEFAULT_EMPHASIS_SIZE__
    #endif

    #define R_SHA_ADD                       (0)
    #define R_SHA_INIT                      (1)
    #define R_SHA_FINISH                    (2)
    #define R_SHA_NOPADDING                 (4)
    #define R_SHA_FINISH_WITHOUT_PADDING    (R_SHA_FINISH | R_SHA_NOPADDING)

    #define R_PROCESS_COMPLETE              (0)
    #define R_SHA_ERROR_POINTER             (-1)
    #define R_SHA_ERROR_FLAG                (-2)
    #define R_SHA_ERROR_LENGTH              (-3)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
    #if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)
typedef struct
{
    uint32_t work[51 + 24];
}R_sha_handle;
    #else
typedef struct
{
    uint32_t work[51 + (2 * 88)];
} R_sha_handle;
    #endif /* defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__) */

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
/* Variable Name: R_sha_version */
extern const mw_version_t far R_sha_version;

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
    #if defined(__RL78__) || defined(__ICCRL78__) || defined(__CCRL__)
/* Function Name: R_Sha1_HashDigest */
/************************************************************************
 * Function Name: R_Sha1_HashDigest
 ********************************************************************//**
 * @brief Calculates the hash value of SHA-1.
 * @param[in] madat Address of a input message.
 * @param[out] hdat Address of message digest.
 * @param[in] len Length of message (unit : byte).
 * @param[in] flag Control flag.
 * @param[in, out] work Address of work area.
 * @retval R_PROCESS_COMPLETE Normal end.
 * @retval R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 * @retval R_SHA_ERROR_FLAG Incorrect flag is specified.
 * @retval R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 * @details This function computes message digest defined in the SHA-1
 * algorithm.The application specifies address of data making a message
 * digest to the 1st argument "mdat". And the application specifies address to
 * store a message digest to the 2nd argument "hash". And the application
 * specifies the data length of message to the 3rd argument "len". And the
 * application specifies the Control flag to the 4th argument "flag".
 * And the application specifies address of Work area to the 5th argument
 * "work". It is necessary to keep a work until the operation of a hash value
 * finishes.A message digest is stored when "R_SHA_FINISH" is specified as flag.
 * @note none.
 */
int8_t R_Sha1_HashDigest (uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work);

/* Function Name: R_Sha256_HashDigest */
/************************************************************************
 * Function Name: R_Sha256_HashDigest
 ********************************************************************//**
 * @brief Calculates the hash value of SHA-256.
 * @param[in] madat Address of a input message.
 * @param[out] hdat Address of message digest.
 * @param[in] len Length of message (unit : byte).
 * @param[in] flag Control flag.
 * @param[in, out] work Address of work area.
 * @retval R_PROCESS_COMPLETE Normal end.
 * @retval R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 * @retval R_SHA_ERROR_FLAG Incorrect flag is specified.
 * @retval R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 * @details This function computes message digest defined in the SHA-256
 * algorithm.The application specifies address of data making a message
 * digest to the 1st argument "mdat". And the application specifies address to
 * store a message digest to the 2nd argument "hash". And the application
 * specifies the data length of message to the 3rd argument "len". And the
 * application specifies the Control flag to the 4th argument "flag".
 * And the application specifies address of Work area to the 5th argument
 * "work". It is necessary to keep a work until the operation of a hash value
 * finishes.A message digest is stored when "R_SHA_FINISH" is specified as flag.
 * @note none.
 */
int8_t R_Sha256_HashDigest (uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work);

/* Function Name: R_Sha384_HashDigest */
/************************************************************************
 * Function Name: R_Sha384_HashDigest
 ********************************************************************//**
 * @brief Calculates the hash value of SHA-384.
 * @param[in] madat Address of a input message.
 * @param[out] hdat Address of message digest.
 * @param[in] len Length of message (unit : byte)
 * @param[in] flag Control flag.
 * @param[in, out] work Address of work area.
 * @retval R_PROCESS_COMPLETE Normal end.
 * @retval R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 * @retval R_SHA_ERROR_FLAG Incorrect flag is specified.
 * @retval R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 * @details This function computes message digest defined in the SHA-384
 * algorithm.The application specifies address of data making a message
 * digest to the 1st argument "mdat". And the application specifies address to
 * store a message digest to the 2nd argument "hash". And the application
 * specifies the data length of message to the 3rd argument "len". And the
 * application specifies the Control flag to the 4th argument "flag".
 * And the application specifies address of Work area to the 5th argument
 * "work". It is necessary to keep a work until the operation of a hash value
 * finishes.A message digest is stored when "R_SHA_FINISH" is specified as flag.
 * @note none.
 */
int8_t R_Sha384_HashDigest (uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work);

/* Function Name: R_Sha512_HashDigest */
int8_t R_Sha512_HashDigest (uint8_t near *mdat, uint8_t near *hdat, uint16_t len, uint8_t flag, void near *work);
    #else /* defined__RL78__ || defined__ICCRL78__ || defined__CCRL__ */

/* Function Name: R_Sha1_HashDigest */
/************************************************************************
 * Function Name: R_Sha1_HashDigest
 ********************************************************************//**
 * @brief Calculates the hash value of SHA-1.
 * @param[in] madat Address of a input message.
 * @param[out] hdat Address of message digest.
 * @param[in] len Length of message (unit : byte).
 * @param[in] flag Control flag.
 * @param[in, out] work Address of work area.
 * @retval R_PROCESS_COMPLETE Normal end.
 * @retval R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 * @retval R_SHA_ERROR_FLAG Incorrect flag is specified.
 * @retval R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 * @details This function computes message digest defined in the SHA-1
 * algorithm.The application specifies address of data making a message
 * digest to the 1st argument "mdat". And the application specifies address to
 * store a message digest to the 2nd argument "hash". And the application
 * specifies the data length of message to the 3rd argument "len". And the
 * application specifies the Control flag to the 4th argument "flag".
 * And the application specifies address of Work area to the 5th argument
 * "work". It is necessary to keep a work until the operation of a hash value
 * finishes.A message digest is stored when "R_SHA_FINISH" is specified as flag.
 * @note none.
 */
int8_t R_Sha1_HashDigest (uint8_t *mdat, uint8_t *hdat, uint16_t len, uint8_t flag, void *work);

/* Function Name: R_Sha256_HashDigest */
/************************************************************************
 * Function Name: R_Sha256_HashDigest
 ********************************************************************//**
 * @brief Calculates the hash value of SHA-256.
 * @param[in] madat Address of a input message.
 * @param[out] hdat Address of message digest.
 * @param[in] len Length of message (unit : byte).
 * @param[in] flag Control flag.
 * @param[in, out] work Address of work area.
 * @retval R_PROCESS_COMPLETE Normal end.
 * @retval R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 * @retval R_SHA_ERROR_FLAG Incorrect flag is specified.
 * @retval R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 * @details This function computes message digest defined in the SHA-256
 * algorithm.The application specifies address of data making a message
 * digest to the 1st argument "mdat". And the application specifies address to
 * store a message digest to the 2nd argument "hash". And the application
 * specifies the data length of message to the 3rd argument "len". And the
 * application specifies the Control flag to the 4th argument "flag".
 * And the application specifies address of Work area to the 5th argument
 * "work". It is necessary to keep a work until the operation of a hash value
 * finishes.A message digest is stored when "R_SHA_FINISH" is specified as flag.
 * @note none.
 */
int8_t R_Sha256_HashDigest (uint8_t *mdat, uint8_t *hdat, uint16_t len, uint8_t flag, void *work);

/* Function Name: R_Sha384_HashDigest */
/************************************************************************
 * Function Name: R_Sha384_HashDigest
 ********************************************************************//**
 * @brief Calculates the hash value of SHA-384.
 * @param[in] madat Address of a input message.
 * @param[out] hdat Address of message digest.
 * @param[in] len Length of message (unit : byte)
 * @param[in] flag Control flag.
 * @param[in, out] work Address of work area.
 * @retval R_PROCESS_COMPLETE Normal end.
 * @retval R_SHA_ERROR_POINTER Pointer "hdat" or "work" is NULL.
 * @retval R_SHA_ERROR_FLAG Incorrect flag is specified.
 * @retval R_SHA_ERROR_LENGTH Pointer "mdat" is NULL, and len > 0.
 * @details This function computes message digest defined in the SHA-384
 * algorithm.The application specifies address of data making a message
 * digest to the 1st argument "mdat". And the application specifies address to
 * store a message digest to the 2nd argument "hash". And the application
 * specifies the data length of message to the 3rd argument "len". And the
 * application specifies the Control flag to the 4th argument "flag".
 * And the application specifies address of Work area to the 5th argument
 * "work". It is necessary to keep a work until the operation of a hash value
 * finishes.A message digest is stored when "R_SHA_FINISH" is specified as flag.
 * @note none.
 */
int8_t R_Sha384_HashDigest (uint8_t *mdat, uint8_t *hdat, uint16_t len, uint8_t flag, void *work);

/* Function Name: R_Sha512_HashDigest */
int8_t R_Sha512_HashDigest (uint8_t *mdat, uint8_t *hdat, uint16_t len, uint8_t flag, void *work);
    #endif /* defined__RL78__ || defined__ICCRL78__ || defined__CCRL__ */

#endif /* define R_SHA_H */
