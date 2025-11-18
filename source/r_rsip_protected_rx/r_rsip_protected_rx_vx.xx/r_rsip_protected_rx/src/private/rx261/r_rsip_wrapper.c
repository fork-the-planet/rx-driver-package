/*
* Copyright (c) 2024 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : r_rsip_wrapper.c
* Description  : Interface definition for the RSIP wrapper.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.10.2024 1.00     First Release.
*         : 31.07.2025 2.00     Added support for ECDH KDF and HMAC Suspend, Resume
*         :                     Revised key management specification
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rsip_private.h"
#include "r_rsip_primitive.h"
#include "r_rsip_wrapper.h"
#include "r_rsip_public.h"
#include "r_rsip_protected_rx_config.h"
#include "r_rsip_util.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RSIP_INSTALL_KEY_RING_INDEX     (0)

/* For AES-CMAC. These commands do not require byte swapping */
#define RSIP_PRV_CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER    (0U)
#define RSIP_PRV_CMD_AES_CMAC_GENERATE_WITH_REMAINDER       (1U)
#define RSIP_PRV_CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER      (2U)
#define RSIP_PRV_CMD_AES_CMAC_VERIFY_WITH_REMAINDER         (3U)

/* For RFC3394 Key Wrap */
#define RSIP_PRV_WORD_SIZE_RFC3394_WRAPPED_KEY_AES_128      (6U)
#define RSIP_PRV_WORD_SIZE_RFC3394_WRAPPED_KEY_AES_256      (10U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

typedef enum e_cmd
{
    CMD_AES_KEY_WRAP_AES128 = 0,
    CMD_AES_KEY_WRAP_AES256 = 1,

    CMD_AES_MODE_ECB_ENCRYPT = 0,
    CMD_AES_MODE_ECB_DECRYPT = 1,
    CMD_AES_MODE_CBC_ENCRYPT = 2,
    CMD_AES_MODE_CBC_DECRYPT = 3,
    CMD_AES_MODE_CTR_CRYPT   = 4,

    CMD_AES_IV_TYPE_PLAIN   = 0,
    CMD_AES_IV_TYPE_WRAPPED = 1,

    CMD_ECC_TYPE_NIST      = 0,
    CMD_ECC_TYPE_BRAINPOOL = 1,

    CMD_ECDH_PUBKEY_TYPE_PLAIN   = 0,
    CMD_ECDH_PUBKEY_TYPE_WRAPPED = 1,

    CMD_PKI_KEY_TYPE_ECC_SECP256R1 = 3,

    CMD_KDF_HASH_TYPE_SHA256 = 0,

    CMD_KDF_OUTDATA_TYPE_AES128      = 0,
    CMD_KDF_OUTDATA_TYPE_AES256      = 1,
    CMD_KDF_OUTDATA_TYPE_IV_AES      = 2,
} cmd_t;

/* OEM Command */
typedef enum e_rsip_oem_cmd
{
    RSIP_OEM_CMD_INVALID                     = 0U,
    RSIP_OEM_CMD_AES128                      = 5U,
    RSIP_OEM_CMD_AES256                      = 7U,
    RSIP_OEM_CMD_ECC_SECP256R1_PUBLIC        = 22U,
    RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE       = 23U,
    RSIP_OEM_CMD_HMAC_SHA224                 = 26U,
    RSIP_OEM_CMD_HMAC_SHA256                 = 27U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PUBLIC  = 28U,
    RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PRIVATE = 29U,
    RSIP_OEM_CMD_ECC_SECP256K1_PUBLIC        = 34U,
    RSIP_OEM_CMD_ECC_SECP256K1_PRIVATE       = 35U,
    RSIP_OEM_CMD_KUK                         = 0xff,
} rsip_oem_cmd_t;

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

static const uint32_t gs_cmd[5] =
{
    BSWAP_32BIG_C(0U), BSWAP_32BIG_C(1U), BSWAP_32BIG_C(2U), BSWAP_32BIG_C(3U), BSWAP_32BIG_C(4U)
};

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

rsip_ret_t r_rsip_wrapper_pf0_secp256r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[])
{
    const uint32_t * InData_DomainParam = DomainParam_NIST_P256;
    uint32_t         cv_type            = bswap_32big(RSIP_ECC_CURVE_TYPE_NIST);

    return r_rsip_pf0(&cv_type, InData_KeyIndex, InData_MsgDgst, InData_DomainParam, OutData_Signature);
}

rsip_ret_t r_rsip_wrapper_pf0_brainpoolp256r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[])
{
    const uint32_t * InData_DomainParam = DomainParam_Brainpool_256r1;
    uint32_t         cv_type            = bswap_32big(RSIP_ECC_CURVE_TYPE_Brainpool);

    return r_rsip_pf0(&cv_type, InData_KeyIndex, InData_MsgDgst, InData_DomainParam, OutData_Signature);
}

rsip_ret_t r_rsip_wrapper_pf0_secp256k1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        uint32_t       OutData_Signature[])
{
    const uint32_t * InData_DomainParam = DomainParam_Koblitz_secp256k1;
    uint32_t         cv_type            = bswap_32big(RSIP_ECC_CURVE_TYPE_Koblitz);

    return r_rsip_pf0(&cv_type, InData_KeyIndex, InData_MsgDgst, InData_DomainParam, OutData_Signature);
}

rsip_ret_t r_rsip_wrapper_pf1_secp256r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[])
{
    const uint32_t * InData_DomainParam = DomainParam_NIST_P256;
    uint32_t         cv_type            = bswap_32big(RSIP_ECC_CURVE_TYPE_NIST);

    return r_rsip_pf1(&cv_type, InData_KeyIndex, InData_MsgDgst, InData_Signature, InData_DomainParam);
}

rsip_ret_t r_rsip_wrapper_pf1_brainpoolp256r1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[])
{
    const uint32_t * InData_DomainParam = DomainParam_Brainpool_256r1;
    uint32_t         cv_type            = bswap_32big(RSIP_ECC_CURVE_TYPE_Brainpool);

    return r_rsip_pf1(&cv_type, InData_KeyIndex, InData_MsgDgst, InData_Signature, InData_DomainParam);
}

rsip_ret_t r_rsip_wrapper_pf1_secp256k1(const uint32_t InData_KeyIndex[],
                                        const uint32_t InData_MsgDgst[],
                                        const uint32_t InData_Signature[])
{
    const uint32_t * InData_DomainParam = DomainParam_Koblitz_secp256k1;
    uint32_t         cv_type            = bswap_32big(RSIP_ECC_CURVE_TYPE_Koblitz);

    return r_rsip_pf1(&cv_type, InData_KeyIndex, InData_MsgDgst, InData_Signature, InData_DomainParam);
}

rsip_ret_t r_rsip_wrapper_pf4_secp256r1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    uint32_t         InData_CurveType    = bswap_32big(RSIP_ECC_CURVE_TYPE_NIST);
    uint32_t const * p_domain_param      = DomainParam_NIST_P256;

    return r_rsip_pf4(&InData_CurveType, p_domain_param, OutData_PubKeyIndex, OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_wrapper_pf4_brainpoolp256r1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    uint32_t         InData_CurveType    = bswap_32big(RSIP_ECC_CURVE_TYPE_Brainpool);
    uint32_t const * p_domain_param      = DomainParam_Brainpool_256r1;

    return r_rsip_pf4(&InData_CurveType, p_domain_param, OutData_PubKeyIndex, OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_wrapper_pf4_secp256k1(uint32_t OutData_PubKeyIndex[], uint32_t OutData_PrivKeyIndex[])
{
    uint32_t         InData_CurveType    = bswap_32big(RSIP_ECC_CURVE_TYPE_Koblitz);
    uint32_t const * p_domain_param      = DomainParam_Koblitz_secp256k1;

    return r_rsip_pf4(&InData_CurveType, p_domain_param, OutData_PubKeyIndex, OutData_PrivKeyIndex);
}

rsip_ret_t r_rsip_p6e_aes128(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_AES128;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_AES128_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_aes256(const uint32_t InData_SessionKey[],
                            const uint32_t InData_IV[],
                            const uint32_t InData_InstData[],
                            uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_AES256;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_AES256_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_secp256r1_pub(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_SECP256R1_PUBLIC;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_secp256r1_priv(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_brainpool256r1_pub(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PUBLIC;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_brainpool256r1_priv(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PRIVATE;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_eccsecp256k1_public(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_SECP256K1_PUBLIC;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_secp256k1_priv(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_SECP256K1_PRIVATE;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_hmacsha224(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_HMAC_SHA224;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_HMAC_SHA256_KEY_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_hmacsha256(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_HMAC_SHA256;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_HMAC_SHA256_KEY_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_p6e_aes256_KUK(const uint32_t InData_SessionKey[],
                                const uint32_t InData_IV[],
                                const uint32_t InData_InstData[],
                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_KUK;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_AES256_INST_DATA_WORD;
    uint32_t InData_SharedKeyIndex = RSIP_INSTALL_KEY_RING_INDEX;

    return r_rsip_p6e(&LC, &CMD, &InData_SharedKeyIndex, InData_SessionKey, InData_IV,
                        InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_aes128(const uint32_t InData_IV[],
                                    const uint32_t InData_InstData[],
                                    uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_AES128;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_AES128_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}


rsip_ret_t r_rsip_wrapper_p6f_aes256(const uint32_t InData_IV[],
                                    const uint32_t InData_InstData[],
                                    uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_AES256;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_AES256_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_secp256r1_pub(const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_SECP256R1_PUBLIC;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_secp256r1_priv(const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_SECP256R1_PRIVATE;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_hmacsha224(const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_HMAC_SHA224;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_HMAC_SHA256_KEY_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_hmacsha256(const uint32_t InData_IV[],
                                        const uint32_t InData_InstData[],
                                        uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_HMAC_SHA256;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_HMAC_SHA256_KEY_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_brainpoolp256r1_pub(const uint32_t InData_IV[],
                                                const uint32_t InData_InstData[],
                                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PUBLIC;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_brainpoolp256r1_priv(const uint32_t InData_IV[],
                                                const uint32_t InData_InstData[],
                                                uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_BRAINPOOLP256R1_PRIVATE;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_secp256k1_pub(const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_SECP256K1_PUBLIC;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PUBLIC_KEY_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p6f_secp256k1_priv(const uint32_t InData_IV[],
                                            const uint32_t InData_InstData[],
                                            uint32_t       OutData_KeyIndex[])
{
    uint32_t CMD = RSIP_OEM_CMD_ECC_SECP256K1_PRIVATE;
    uint32_t LC  = RSIP_DUMMY_LC;
    INST_DATA_SIZE = RSIP_OEM_KEY_SIZE_ECC_SECP256R1_PRIVATE_KEY_INST_DATA_WORD;

    return r_rsip_p6f(&LC, &CMD, InData_IV, InData_InstData, INST_DATA_SIZE, OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p8f_aes128 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_WrappedKeyIndex[],
                                      uint32_t       OutData_Text[],
                                      uint32_t       KEY_INDEX_SIZE,
                                      uint32_t       WRAPPED_KEY_SIZE)
{
    return r_rsip_p8f(&gs_cmd[CMD_AES_KEY_WRAP_AES128],
                      InData_KeyIndex,
                      InData_WrappedKeyType,
                      InData_WrappedKeyIndex,
                      KEY_INDEX_SIZE,
                      OutData_Text,
                      WRAPPED_KEY_SIZE);
}

rsip_ret_t r_rsip_wrapper_p8f_aes256 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_WrappedKeyIndex[],
                                      uint32_t       OutData_Text[],
                                      uint32_t       KEY_INDEX_SIZE,
                                      uint32_t       WRAPPED_KEY_SIZE)
{
    return r_rsip_p8f(&gs_cmd[CMD_AES_KEY_WRAP_AES256],
                      InData_KeyIndex,
                      InData_WrappedKeyType,
                      InData_WrappedKeyIndex,
                      KEY_INDEX_SIZE,
                      OutData_Text,
                      WRAPPED_KEY_SIZE);
}

rsip_ret_t r_rsip_wrapper_p90_aes128 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_Text[],
                                      uint32_t       OutData_KeyIndex[],
                                      uint32_t       WRAPPED_KEY_SIZE,
                                      uint32_t       KEY_INDEX_SIZE)
{
    return r_rsip_p90(&gs_cmd[CMD_AES_KEY_WRAP_AES128],
                      InData_KeyIndex,
                      InData_WrappedKeyType,
                      InData_Text,
                      KEY_INDEX_SIZE,
                      OutData_KeyIndex,
                      WRAPPED_KEY_SIZE);
}

rsip_ret_t r_rsip_wrapper_p90_aes256 (const uint32_t InData_KeyIndex[],
                                      const uint32_t InData_WrappedKeyType[],
                                      const uint32_t InData_Text[],
                                      uint32_t       OutData_KeyIndex[],
                                      uint32_t       WRAPPED_KEY_SIZE,
                                      uint32_t       KEY_INDEX_SIZE)
{
    return r_rsip_p90(&gs_cmd[CMD_AES_KEY_WRAP_AES256],
                      InData_KeyIndex,
                      InData_WrappedKeyType,
                      InData_Text,
                      KEY_INDEX_SIZE,
                      OutData_KeyIndex,
                      WRAPPED_KEY_SIZE);
}

rsip_ret_t r_rsip_wrapper_p47i_aes128ecb_encrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_ECB_ENCRYPT];

    return r_rsip_p47i(&cmd, InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_aes128ecb_decrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_ECB_DECRYPT];

    return r_rsip_p47i(&cmd, InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_encrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CBC_ENCRYPT];
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_PLAIN];

    return r_rsip_p47i(&cmd, InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_encrypt_wrapped_iv(const uint32_t InData_KeyIndex[],
                                                            const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CBC_ENCRYPT];
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_WRAPPED];

    return r_rsip_p47i(&cmd, InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_decrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CBC_DECRYPT];
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_PLAIN];

    return r_rsip_p47i(&cmd, InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_aes128cbc_decrypt_wrapped_iv(const uint32_t InData_KeyIndex[],
                                                            const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CBC_DECRYPT];
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_WRAPPED];

    return r_rsip_p47i(&cmd, InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p47i_aes128ctr_crypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CTR_CRYPT];

    return r_rsip_p47i(&cmd, InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_aes256ecb_encrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{;
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_ECB_ENCRYPT];

    return r_rsip_p50i(&cmd, InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_aes256ecb_decrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_ECB_DECRYPT];

    return r_rsip_p50i(&cmd, InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_encrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CBC_ENCRYPT];
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_PLAIN];

    return r_rsip_p50i(&cmd, InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_encrypt_wrapped_iv(const uint32_t InData_KeyIndex[],
                                                            const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CBC_ENCRYPT];
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_WRAPPED];

    return r_rsip_p50i(&cmd, InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_decrypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CBC_DECRYPT];
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_PLAIN];

    return r_rsip_p50i(&cmd, InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_aes256cbc_decrypt_wrapped_iv(const uint32_t InData_KeyIndex[],
                                                            const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CBC_DECRYPT];
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_WRAPPED];

    return r_rsip_p50i(&cmd, InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p50i_aes256ctr_crypt(const uint32_t InData_KeyIndex[], const uint32_t InData_IV[])
{
    uint32_t cmd      = gs_cmd[CMD_AES_MODE_CTR_CRYPT];

    return r_rsip_p50i(&cmd, InData_KeyIndex, NULL, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p29i_aes128gcm_encrypt(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_PLAIN];

    return r_rsip_p29i(InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p29i_aes128gcm_encrypt_wrapped_iv(const uint32_t * InData_KeyIndex,
                                                            const uint32_t * InData_IV)
{
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_WRAPPED];

    return r_rsip_p29i(InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p32i_aes128gcm_decrypt(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_PLAIN];

    return r_rsip_p32i(InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p32i_aes128gcm_decrypt_wrapped_iv(const uint32_t * InData_KeyIndex,
                                                            const uint32_t * InData_IV)
{
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_WRAPPED];

    return r_rsip_p32i(InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p34i_aes256gcm_encrypt(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_PLAIN];

    return r_rsip_p34i(InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p34i_aes256gcm_encrypt_wrapped_iv(const uint32_t * InData_KeyIndex,
                                                            const uint32_t * InData_IV)
{
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_WRAPPED];

    return r_rsip_p34i(InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p36i_aes256gcm_decrypt(const uint32_t * InData_KeyIndex, const uint32_t * InData_IV)
{
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_PLAIN];

    return r_rsip_p36i(InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p36i_aes256gcm_decrypt_wrapped_iv(const uint32_t * InData_KeyIndex,
                                                            const uint32_t * InData_IV)
{
    uint32_t iv_type  = gs_cmd[CMD_AES_IV_TYPE_WRAPPED];

    return r_rsip_p36i(InData_KeyIndex, &iv_type, InData_IV);
}

rsip_ret_t r_rsip_wrapper_p95i_aes128ccm_encrypt(const uint32_t * InData_KeyIndex,
                                                const uint32_t * InData_TextLen,
                                                const uint32_t * InData_IV,
                                                const uint32_t * InData_Header,
                                                uint32_t         Header_Len)
{
    (void) InData_TextLen;
    return r_rsip_p95i(InData_KeyIndex,
                        InData_IV,
                        InData_Header,
                        Header_Len);
}

rsip_ret_t r_rsip_wrapper_p95f_aes128ccm_encrypt(const uint32_t    * InData_Text,
                                                    const uint32_t * InData_TextLen,
                                                    uint32_t       * OutData_Text,
                                                    uint32_t       * OutData_MAC)
{


    return r_rsip_p95f(InData_Text, InData_TextLen, OutData_Text, OutData_MAC);
}

rsip_ret_t r_rsip_wrapper_p98i_aes128ccm_decrypt(const uint32_t    * InData_KeyIndex,
                                                    const uint32_t * InData_TextLen,
                                                    const uint32_t * InData_MACLength,
                                                    const uint32_t * InData_IV,
                                                    const uint32_t * InData_Header,
                                                    uint32_t         Header_Len)
{
    (void) InData_TextLen;
    (void) InData_MACLength;
    return r_rsip_p98i(InData_KeyIndex,
                        InData_IV,
                        InData_Header,
                        Header_Len);
}

rsip_ret_t r_rsip_wrapper_p98f_aes128ccm_decrypt(const uint32_t    * InData_Text,
                                                    const uint32_t * InData_TextLen,
                                                    const uint32_t * InData_MAC,
                                                    const uint32_t * InData_MACLength,
                                                    uint32_t       * OutData_Text)
{
    return r_rsip_p98f(InData_Text, InData_TextLen, InData_MAC, InData_MACLength, OutData_Text);
}

rsip_ret_t r_rsip_wrapper_pa1i_aes256ccm_encrypt(const uint32_t    * InData_KeyIndex,
                                                    const uint32_t * InData_TextLen,
                                                    const uint32_t * InData_IV,
                                                    const uint32_t * InData_Header,
                                                    uint32_t         Header_Len)
{
    (void) InData_TextLen;

    return r_rsip_pa1i(InData_KeyIndex, InData_IV, InData_Header, Header_Len);
}

rsip_ret_t r_rsip_wrapper_pa4i_aes256ccm_decrypt(const uint32_t   * InData_KeyIndex,
                                                    const uint32_t * InData_TextLen,
                                                    const uint32_t * InData_MACLength,
                                                    const uint32_t * InData_IV,
                                                    const uint32_t * InData_Header,
                                                    uint32_t         Header_Len)
{
    (void) InData_TextLen;
    (void) InData_MACLength;

    return r_rsip_pa4i(InData_KeyIndex, InData_IV, InData_Header, Header_Len);
}


rsip_ret_t r_rsip_wrapper_p41i_aes128mac(const uint32_t * InData_KeyIndex)
{
    return r_rsip_p41i(InData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p41f_aes128mac_generate(const uint32_t   * InData_Text,
                                                    uint32_t       * OutData_DataT,
                                                    const uint32_t   all_msg_len)
{
    uint32_t InData_Cmd[1] =
    {
        ((0 == (all_msg_len % 16)) &&
        (0 !=
        all_msg_len)) ? RSIP_PRV_CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER :
        RSIP_PRV_CMD_AES_CMAC_GENERATE_WITH_REMAINDER
    };
    uint32_t InData_DataT = 0;

    return r_rsip_p41f(InData_Cmd, InData_Text, &InData_DataT, (uint32_t *) &all_msg_len, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_p41f_aes128mac_verify(const uint32_t * InData_Text,
                                                const uint32_t * InData_DataT,
                                                const uint32_t * InData_DataTLen,
                                                const uint32_t   all_msg_len)
{
    uint32_t InData_Cmd[1] =
    {
        ((0 == (all_msg_len % 16)) &&
        (0 !=
        all_msg_len)) ? RSIP_PRV_CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER :
        RSIP_PRV_CMD_AES_CMAC_VERIFY_WITH_REMAINDER
    };
    uint32_t OutData_DataT[4] = {0};
    (void) all_msg_len;

    return r_rsip_p41f(InData_Cmd, InData_Text, InData_DataT, InData_DataTLen, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_p44i_aes256mac(const uint32_t * InData_KeyIndex)
{
    return r_rsip_p44i(InData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_p44f_aes256mac_generate(const uint32_t   * InData_Text,
                                                    uint32_t       * OutData_DataT,
                                                    const uint32_t   all_msg_len)
{
    uint32_t InData_Cmd[1] =
    {
        ((0 == (all_msg_len % 16)) &&
        (0 !=
        all_msg_len)) ? RSIP_PRV_CMD_AES_CMAC_GENERATE_WITHOUT_REMAINDER :
        RSIP_PRV_CMD_AES_CMAC_GENERATE_WITH_REMAINDER
    };
    uint32_t InData_DataT = 0;

    return r_rsip_p44f(InData_Cmd, InData_Text, &InData_DataT, (uint32_t *) &all_msg_len, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_p44f_aes256mac_verify(const uint32_t * InData_Text,
                                                const uint32_t * InData_DataT,
                                                const uint32_t * InData_DataTLen,
                                                const uint32_t   all_msg_len)
{
    uint32_t InData_Cmd[1] =
    {
        ((0 == (all_msg_len % 16)) &&
        (0 !=
        all_msg_len)) ? RSIP_PRV_CMD_AES_CMAC_VERIFY_WITHOUT_REMAINDER :
        RSIP_PRV_CMD_AES_CMAC_VERIFY_WITH_REMAINDER
    };
    uint32_t OutData_DataT[4] = {0};
    (void) all_msg_len;

    return r_rsip_p44f(InData_Cmd, InData_Text, InData_DataT, InData_DataTLen, OutData_DataT);
}

rsip_ret_t r_rsip_wrapper_pe2_wrapped (const uint32_t InData_PubKey[],
                                       const uint32_t InData_KeyIndex[],
                                       uint32_t       OutData_EncSecret[])
{
    return r_rsip_pe2(&gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECDH_PUBKEY_TYPE_WRAPPED],
                      InData_PubKey,
                      InData_KeyIndex,
                      DomainParam_NIST_P256,
                      OutData_EncSecret);
}

rsip_ret_t r_rsip_wrapper_pe2_plain (const uint32_t InData_PubKey[],
                                     const uint32_t InData_KeyIndex[],
                                     uint32_t       OutData_EncSecret[])
{
    return r_rsip_pe2(&gs_cmd[CMD_ECC_TYPE_NIST],
                      &gs_cmd[CMD_ECDH_PUBKEY_TYPE_PLAIN],
                      InData_PubKey,
                      InData_KeyIndex,
                      DomainParam_NIST_P256,
                      OutData_EncSecret);
}

rsip_ret_t r_rsip_wrapper_peei (const uint32_t InData_KeyIndex[],
                                const uint32_t InData_MsgDgst[],
                                const uint32_t InData_Signature[])
{
    return r_rsip_peei(&gs_cmd[CMD_ECC_TYPE_NIST],
                       InData_KeyIndex,
                       InData_MsgDgst,
                       InData_Signature,
                       DomainParam_NIST_P256);
}

rsip_ret_t r_rsip_wrapper_pe1_secp256r1 (const uint32_t InData_HashType[],
                                         const uint32_t InData_Certificate[],
                                         const uint32_t InData_CertificateLength[],
                                         const uint32_t InData_CertificatePubKey[],
                                         const uint32_t InData_EncCertificateInfo[],
                                         uint32_t       OutData_KeyIndex[])
{
    FSP_PARAMETER_NOT_USED(InData_HashType);

    return r_rsip_pe1(&gs_cmd[CMD_PKI_KEY_TYPE_ECC_SECP256R1],
                      InData_Certificate,
                      InData_CertificateLength,
                      InData_CertificatePubKey,
                      InData_EncCertificateInfo,
                      OutData_KeyIndex);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_aes128 (const uint32_t InData_KDFInfo[],
                                             const uint32_t InData_KDFInfo_Count[],
                                             const uint32_t InData_OutDataLocation[],
                                             uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe7(InData_KDFInfo, InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_AES128], InData_OutDataLocation, OutData_KeyIndex, NULL);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_aes256 (const uint32_t InData_KDFInfo[],
                                             const uint32_t InData_KDFInfo_Count[],
                                             const uint32_t InData_OutDataLocation[],
                                             uint32_t       OutData_KeyIndex[])
{
    return r_rsip_pe7(InData_KDFInfo, InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_AES256], InData_OutDataLocation, OutData_KeyIndex, NULL);
}

rsip_ret_t r_rsip_wrapper_pe7_sha256_iv_aes (const uint32_t InData_KDFInfo[],
                                             const uint32_t InData_KDFInfo_Count[],
                                             const uint32_t InData_OutDataLocation[],
                                             const uint32_t InData_SeqNum[],
                                             uint32_t       OutData_EncIV[])
{
    return r_rsip_pe7(InData_KDFInfo,
                      InData_KDFInfo_Count,
                      &gs_cmd[CMD_KDF_OUTDATA_TYPE_IV_AES],
                      InData_OutDataLocation,
                      NULL,
                      OutData_EncIV);
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/
