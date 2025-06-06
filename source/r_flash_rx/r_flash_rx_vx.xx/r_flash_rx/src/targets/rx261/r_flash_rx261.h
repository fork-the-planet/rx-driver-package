/*
* Copyright (C) 2024-2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : r_flash_rx261.h
 * Description  : This is a private header file used internally by the FLASH FIT module. It should not be modified or
 *                included by the user in their application. 
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 30.07.2024 5.20     First Release
 *         : 20.03.2025 5.22     Changed the disclaimer in program sources
 *********************************************************************************************************************/

#ifndef R_FLASH_RX261_H
#define R_FLASH_RX261_H

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#define FLASH_NUM_BLOCKS_DF           (32)
#define FLASH_DF_MIN_PGM_SIZE         (1)
#define FLASH_CF_MIN_PGM_SIZE         (8)

#define FLASH_CF_BLOCK_SIZE           (2048)
#define FLASH_DF_BLOCK_SIZE           (256)
#define FLASH_DF_FULL_SIZE            (FLASH_NUM_BLOCKS_DF*FLASH_DF_BLOCK_SIZE)
#define FLASH_DF_FULL_PGM_SIZE        (FLASH_DF_FULL_SIZE-FLASH_DF_MIN_PGM_SIZE)
#define FLASH_DF_LAST_VALID_ADDR      (FLASH_DF_BLOCK_INVALID-1)
#define FLASH_DF_HIGHEST_VALID_BLOCK  (FLASH_DF_BLOCK_INVALID-FLASH_DF_BLOCK_SIZE)


#define FLASH_NUM_BLOCKS_CF           (MCU_ROM_SIZE_BYTES / FLASH_CF_BLOCK_SIZE)
#define FLASH_CF_FULL_SIZE            (FLASH_NUM_BLOCKS_CF*FLASH_CF_BLOCK_SIZE)
#define FLASH_CF_LOWEST_VALID_BLOCK   (FLASH_CF_BLOCK_INVALID + 1)
#define FLASH_CF_LAST_VALID_ADDR      (FLASH_CF_LOWEST_VALID_BLOCK)

/* Delay function Setting */
#define WAIT_DIV_LOOP_CYCLE           (4000) /* 4 cycle of 1 loop * 1000(us) */
#define WAIT_OVERHEAD_COUNT           (5)    /* Overhead is reduced from a loop count.
                                                overhead loop count = 20 cycle / 4 cycle of 1 loop */

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/
typedef enum _flash_block_address
{
    FLASH_CF_BLOCK_END     = 0xFFFFFFFF,    /*   End of Code Flash Area       */
    FLASH_CF_BLOCK_0       = 0xFFFFF800,    /*   2KB: 0xFFFFF800 - 0xFFFFFFFF */
    FLASH_CF_BLOCK_1       = 0xFFFFF000,    /*   2KB: 0xFFFFF000 - 0xFFFFF7FF */
    FLASH_CF_BLOCK_2       = 0xFFFFE800,    /*   2KB: 0xFFFFE800 - 0xFFFFEFFF */
    FLASH_CF_BLOCK_3       = 0xFFFFE000,    /*   2KB: 0xFFFFE000 - 0xFFFFE7FF */
    FLASH_CF_BLOCK_4       = 0xFFFFD800,    /*   2KB: 0xFFFFD800 - 0xFFFFDFFF */
    FLASH_CF_BLOCK_5       = 0xFFFFD000,    /*   2KB: 0xFFFFD000 - 0xFFFFD7FF */
    FLASH_CF_BLOCK_6       = 0xFFFFC800,    /*   2KB: 0xFFFFC800 - 0xFFFFCFFF */
    FLASH_CF_BLOCK_7       = 0xFFFFC000,    /*   2KB: 0xFFFFC000 - 0xFFFFC7FF */
    FLASH_CF_BLOCK_8       = 0xFFFFB800,    /*   2KB: 0xFFFFB800 - 0xFFFFBFFF */
    FLASH_CF_BLOCK_9       = 0xFFFFB000,    /*   2KB: 0xFFFFB000 - 0xFFFFB7FF */
    FLASH_CF_BLOCK_10      = 0xFFFFA800,    /*   2KB: 0xFFFFA800 - 0xFFFFAFFF */
    FLASH_CF_BLOCK_11      = 0xFFFFA000,    /*   2KB: 0xFFFFA000 - 0xFFFFA7FF */
    FLASH_CF_BLOCK_12      = 0xFFFF9800,    /*   2KB: 0xFFFF9800 - 0xFFFF9FFF */
    FLASH_CF_BLOCK_13      = 0xFFFF9000,    /*   2KB: 0xFFFF9000 - 0xFFFF97FF */
    FLASH_CF_BLOCK_14      = 0xFFFF8800,    /*   2KB: 0xFFFF8800 - 0xFFFF8FFF */
    FLASH_CF_BLOCK_15      = 0xFFFF8000,    /*   2KB: 0xFFFF8000 - 0xFFFF87FF */
    FLASH_CF_BLOCK_16      = 0xFFFF7800,    /*   2KB: 0xFFFF7800 - 0xFFFF7FFF */
    FLASH_CF_BLOCK_17      = 0xFFFF7000,    /*   2KB: 0xFFFF7000 - 0xFFFF77FF */
    FLASH_CF_BLOCK_18      = 0xFFFF6800,    /*   2KB: 0xFFFF6800 - 0xFFFF6FFF */
    FLASH_CF_BLOCK_19      = 0xFFFF6000,    /*   2KB: 0xFFFF6000 - 0xFFFF67FF */
    FLASH_CF_BLOCK_20      = 0xFFFF5800,    /*   2KB: 0xFFFF5800 - 0xFFFF5FFF */
    FLASH_CF_BLOCK_21      = 0xFFFF5000,    /*   2KB: 0xFFFF5000 - 0xFFFF57FF */
    FLASH_CF_BLOCK_22      = 0xFFFF4800,    /*   2KB: 0xFFFF4800 - 0xFFFF4FFF */
    FLASH_CF_BLOCK_23      = 0xFFFF4000,    /*   2KB: 0xFFFF4000 - 0xFFFF47FF */
    FLASH_CF_BLOCK_24      = 0xFFFF3800,    /*   2KB: 0xFFFF3800 - 0xFFFF3FFF */
    FLASH_CF_BLOCK_25      = 0xFFFF3000,    /*   2KB: 0xFFFF3000 - 0xFFFF37FF */
    FLASH_CF_BLOCK_26      = 0xFFFF2800,    /*   2KB: 0xFFFF2800 - 0xFFFF2FFF */
    FLASH_CF_BLOCK_27      = 0xFFFF2000,    /*   2KB: 0xFFFF2000 - 0xFFFF27FF */
    FLASH_CF_BLOCK_28      = 0xFFFF1800,    /*   2KB: 0xFFFF1800 - 0xFFFF1FFF */
    FLASH_CF_BLOCK_29      = 0xFFFF1000,    /*   2KB: 0xFFFF1000 - 0xFFFF17FF */
    FLASH_CF_BLOCK_30      = 0xFFFF0800,    /*   2KB: 0xFFFF0800 - 0xFFFF0FFF */
    FLASH_CF_BLOCK_31      = 0xFFFF0000,    /*   2KB: 0xFFFF0000 - 0xFFFF07FF */
    FLASH_CF_BLOCK_32      = 0xFFFEF800,    /*   2KB: 0xFFFEF800 - 0xFFFEFFFF */
    FLASH_CF_BLOCK_33      = 0xFFFEF000,    /*   2KB: 0xFFFEF000 - 0xFFFEF7FF */
    FLASH_CF_BLOCK_34      = 0xFFFEE800,    /*   2KB: 0xFFFEE800 - 0xFFFEEFFF */
    FLASH_CF_BLOCK_35      = 0xFFFEE000,    /*   2KB: 0xFFFEE000 - 0xFFFEE7FF */
    FLASH_CF_BLOCK_36      = 0xFFFED800,    /*   2KB: 0xFFFED800 - 0xFFFEDFFF */
    FLASH_CF_BLOCK_37      = 0xFFFED000,    /*   2KB: 0xFFFED000 - 0xFFFED7FF */
    FLASH_CF_BLOCK_38      = 0xFFFEC800,    /*   2KB: 0xFFFEC800 - 0xFFFECFFF */
    FLASH_CF_BLOCK_39      = 0xFFFEC000,    /*   2KB: 0xFFFEC000 - 0xFFFEC7FF */
    FLASH_CF_BLOCK_40      = 0xFFFEB800,    /*   2KB: 0xFFFEB800 - 0xFFFEBFFF */
    FLASH_CF_BLOCK_41      = 0xFFFEB000,    /*   2KB: 0xFFFEB000 - 0xFFFEB7FF */
    FLASH_CF_BLOCK_42      = 0xFFFEA800,    /*   2KB: 0xFFFEA800 - 0xFFFEAFFF */
    FLASH_CF_BLOCK_43      = 0xFFFEA000,    /*   2KB: 0xFFFEA000 - 0xFFFEA7FF */
    FLASH_CF_BLOCK_44      = 0xFFFE9800,    /*   2KB: 0xFFFE9800 - 0xFFFE9FFF */
    FLASH_CF_BLOCK_45      = 0xFFFE9000,    /*   2KB: 0xFFFE9000 - 0xFFFE97FF */
    FLASH_CF_BLOCK_46      = 0xFFFE8800,    /*   2KB: 0xFFFE8800 - 0xFFFE8FFF */
    FLASH_CF_BLOCK_47      = 0xFFFE8000,    /*   2KB: 0xFFFE8000 - 0xFFFE87FF */
    FLASH_CF_BLOCK_48      = 0xFFFE7800,    /*   2KB: 0xFFFE7800 - 0xFFFE7FFF */
    FLASH_CF_BLOCK_49      = 0xFFFE7000,    /*   2KB: 0xFFFE7000 - 0xFFFE77FF */
    FLASH_CF_BLOCK_50      = 0xFFFE6800,    /*   2KB: 0xFFFE6800 - 0xFFFE6FFF */
    FLASH_CF_BLOCK_51      = 0xFFFE6000,    /*   2KB: 0xFFFE6000 - 0xFFFE67FF */
    FLASH_CF_BLOCK_52      = 0xFFFE5800,    /*   2KB: 0xFFFE5800 - 0xFFFE5FFF */
    FLASH_CF_BLOCK_53      = 0xFFFE5000,    /*   2KB: 0xFFFE5000 - 0xFFFE57FF */
    FLASH_CF_BLOCK_54      = 0xFFFE4800,    /*   2KB: 0xFFFE4800 - 0xFFFE4FFF */
    FLASH_CF_BLOCK_55      = 0xFFFE4000,    /*   2KB: 0xFFFE4000 - 0xFFFE47FF */
    FLASH_CF_BLOCK_56      = 0xFFFE3800,    /*   2KB: 0xFFFE3800 - 0xFFFE3FFF */
    FLASH_CF_BLOCK_57      = 0xFFFE3000,    /*   2KB: 0xFFFE3000 - 0xFFFE37FF */
    FLASH_CF_BLOCK_58      = 0xFFFE2800,    /*   2KB: 0xFFFE2800 - 0xFFFE2FFF */
    FLASH_CF_BLOCK_59      = 0xFFFE2000,    /*   2KB: 0xFFFE2000 - 0xFFFE27FF */
    FLASH_CF_BLOCK_60      = 0xFFFE1800,    /*   2KB: 0xFFFE1800 - 0xFFFE1FFF */
    FLASH_CF_BLOCK_61      = 0xFFFE1000,    /*   2KB: 0xFFFE1000 - 0xFFFE17FF */
    FLASH_CF_BLOCK_62      = 0xFFFE0800,    /*   2KB: 0xFFFE0800 - 0xFFFE0FFF */
    FLASH_CF_BLOCK_63      = 0xFFFE0000,    /*   2KB: 0xFFFE0000 - 0xFFFE07FF */
    FLASH_CF_BLOCK_64      = 0xFFFDF800,    /*   2KB: 0xFFFDF800 - 0xFFFDFFFF */
    FLASH_CF_BLOCK_65      = 0xFFFDF000,    /*   2KB: 0xFFFDF000 - 0xFFFDF7FF */
    FLASH_CF_BLOCK_66      = 0xFFFDE800,    /*   2KB: 0xFFFDE800 - 0xFFFDEFFF */
    FLASH_CF_BLOCK_67      = 0xFFFDE000,    /*   2KB: 0xFFFDE000 - 0xFFFDE7FF */
    FLASH_CF_BLOCK_68      = 0xFFFDD800,    /*   2KB: 0xFFFDD800 - 0xFFFDDFFF */
    FLASH_CF_BLOCK_69      = 0xFFFDD000,    /*   2KB: 0xFFFDD000 - 0xFFFDD7FF */
    FLASH_CF_BLOCK_70      = 0xFFFDC800,    /*   2KB: 0xFFFDC800 - 0xFFFDCFFF */
    FLASH_CF_BLOCK_71      = 0xFFFDC000,    /*   2KB: 0xFFFDC000 - 0xFFFDC7FF */
    FLASH_CF_BLOCK_72      = 0xFFFDB800,    /*   2KB: 0xFFFDB800 - 0xFFFDBFFF */
    FLASH_CF_BLOCK_73      = 0xFFFDB000,    /*   2KB: 0xFFFDB000 - 0xFFFDB7FF */
    FLASH_CF_BLOCK_74      = 0xFFFDA800,    /*   2KB: 0xFFFDA800 - 0xFFFDAFFF */
    FLASH_CF_BLOCK_75      = 0xFFFDA000,    /*   2KB: 0xFFFDA000 - 0xFFFDA7FF */
    FLASH_CF_BLOCK_76      = 0xFFFD9800,    /*   2KB: 0xFFFD9800 - 0xFFFD9FFF */
    FLASH_CF_BLOCK_77      = 0xFFFD9000,    /*   2KB: 0xFFFD9000 - 0xFFFD97FF */
    FLASH_CF_BLOCK_78      = 0xFFFD8800,    /*   2KB: 0xFFFD8800 - 0xFFFD8FFF */
    FLASH_CF_BLOCK_79      = 0xFFFD8000,    /*   2KB: 0xFFFD8000 - 0xFFFD87FF */
    FLASH_CF_BLOCK_80      = 0xFFFD7800,    /*   2KB: 0xFFFD7800 - 0xFFFD7FFF */
    FLASH_CF_BLOCK_81      = 0xFFFD7000,    /*   2KB: 0xFFFD7000 - 0xFFFD77FF */
    FLASH_CF_BLOCK_82      = 0xFFFD6800,    /*   2KB: 0xFFFD6800 - 0xFFFD6FFF */
    FLASH_CF_BLOCK_83      = 0xFFFD6000,    /*   2KB: 0xFFFD6000 - 0xFFFD67FF */
    FLASH_CF_BLOCK_84      = 0xFFFD5800,    /*   2KB: 0xFFFD5800 - 0xFFFD5FFF */
    FLASH_CF_BLOCK_85      = 0xFFFD5000,    /*   2KB: 0xFFFD5000 - 0xFFFD57FF */
    FLASH_CF_BLOCK_86      = 0xFFFD4800,    /*   2KB: 0xFFFD4800 - 0xFFFD4FFF */
    FLASH_CF_BLOCK_87      = 0xFFFD4000,    /*   2KB: 0xFFFD4000 - 0xFFFD47FF */
    FLASH_CF_BLOCK_88      = 0xFFFD3800,    /*   2KB: 0xFFFD3800 - 0xFFFD3FFF */
    FLASH_CF_BLOCK_89      = 0xFFFD3000,    /*   2KB: 0xFFFD3000 - 0xFFFD37FF */
    FLASH_CF_BLOCK_90      = 0xFFFD2800,    /*   2KB: 0xFFFD2800 - 0xFFFD2FFF */
    FLASH_CF_BLOCK_91      = 0xFFFD2000,    /*   2KB: 0xFFFD2000 - 0xFFFD27FF */
    FLASH_CF_BLOCK_92      = 0xFFFD1800,    /*   2KB: 0xFFFD1800 - 0xFFFD1FFF */
    FLASH_CF_BLOCK_93      = 0xFFFD1000,    /*   2KB: 0xFFFD1000 - 0xFFFD17FF */
    FLASH_CF_BLOCK_94      = 0xFFFD0800,    /*   2KB: 0xFFFD0800 - 0xFFFD0FFF */
    FLASH_CF_BLOCK_95      = 0xFFFD0000,    /*   2KB: 0xFFFD0000 - 0xFFFD07FF */
    FLASH_CF_BLOCK_96      = 0xFFFCF800,    /*   2KB: 0xFFFCF800 - 0xFFFCFFFF */
    FLASH_CF_BLOCK_97      = 0xFFFCF000,    /*   2KB: 0xFFFCF000 - 0xFFFCF7FF */
    FLASH_CF_BLOCK_98      = 0xFFFCE800,    /*   2KB: 0xFFFCE800 - 0xFFFCEFFF */
    FLASH_CF_BLOCK_99      = 0xFFFCE000,    /*   2KB: 0xFFFCE000 - 0xFFFCE7FF */
    FLASH_CF_BLOCK_100     = 0xFFFCD800,    /*   2KB: 0xFFFCD800 - 0xFFFCDFFF */
    FLASH_CF_BLOCK_101     = 0xFFFCD000,    /*   2KB: 0xFFFCD000 - 0xFFFCD7FF */
    FLASH_CF_BLOCK_102     = 0xFFFCC800,    /*   2KB: 0xFFFCC800 - 0xFFFCCFFF */
    FLASH_CF_BLOCK_103     = 0xFFFCC000,    /*   2KB: 0xFFFCC000 - 0xFFFCC7FF */
    FLASH_CF_BLOCK_104     = 0xFFFCB800,    /*   2KB: 0xFFFCB800 - 0xFFFCBFFF */
    FLASH_CF_BLOCK_105     = 0xFFFCB000,    /*   2KB: 0xFFFCB000 - 0xFFFCB7FF */
    FLASH_CF_BLOCK_106     = 0xFFFCA800,    /*   2KB: 0xFFFCA800 - 0xFFFCAFFF */
    FLASH_CF_BLOCK_107     = 0xFFFCA000,    /*   2KB: 0xFFFCA000 - 0xFFFCA7FF */
    FLASH_CF_BLOCK_108     = 0xFFFC9800,    /*   2KB: 0xFFFC9800 - 0xFFFC9FFF */
    FLASH_CF_BLOCK_109     = 0xFFFC9000,    /*   2KB: 0xFFFC9000 - 0xFFFC97FF */
    FLASH_CF_BLOCK_110     = 0xFFFC8800,    /*   2KB: 0xFFFC8800 - 0xFFFC8FFF */
    FLASH_CF_BLOCK_111     = 0xFFFC8000,    /*   2KB: 0xFFFC8000 - 0xFFFC87FF */
    FLASH_CF_BLOCK_112     = 0xFFFC7800,    /*   2KB: 0xFFFC7800 - 0xFFFC7FFF */
    FLASH_CF_BLOCK_113     = 0xFFFC7000,    /*   2KB: 0xFFFC7000 - 0xFFFC77FF */
    FLASH_CF_BLOCK_114     = 0xFFFC6800,    /*   2KB: 0xFFFC6800 - 0xFFFC6FFF */
    FLASH_CF_BLOCK_115     = 0xFFFC6000,    /*   2KB: 0xFFFC6000 - 0xFFFC67FF */
    FLASH_CF_BLOCK_116     = 0xFFFC5800,    /*   2KB: 0xFFFC5800 - 0xFFFC5FFF */
    FLASH_CF_BLOCK_117     = 0xFFFC5000,    /*   2KB: 0xFFFC5000 - 0xFFFC57FF */
    FLASH_CF_BLOCK_118     = 0xFFFC4800,    /*   2KB: 0xFFFC4800 - 0xFFFC4FFF */
    FLASH_CF_BLOCK_119     = 0xFFFC4000,    /*   2KB: 0xFFFC4000 - 0xFFFC47FF */
    FLASH_CF_BLOCK_120     = 0xFFFC3800,    /*   2KB: 0xFFFC3800 - 0xFFFC3FFF */
    FLASH_CF_BLOCK_121     = 0xFFFC3000,    /*   2KB: 0xFFFC3000 - 0xFFFC37FF */
    FLASH_CF_BLOCK_122     = 0xFFFC2800,    /*   2KB: 0xFFFC2800 - 0xFFFC2FFF */
    FLASH_CF_BLOCK_123     = 0xFFFC2000,    /*   2KB: 0xFFFC2000 - 0xFFFC27FF */
    FLASH_CF_BLOCK_124     = 0xFFFC1800,    /*   2KB: 0xFFFC1800 - 0xFFFC1FFF */
    FLASH_CF_BLOCK_125     = 0xFFFC1000,    /*   2KB: 0xFFFC1000 - 0xFFFC17FF */
    FLASH_CF_BLOCK_126     = 0xFFFC0800,    /*   2KB: 0xFFFC0800 - 0xFFFC0FFF */
    FLASH_CF_BLOCK_127     = 0xFFFC0000,    /*   2KB: 0xFFFC0000 - 0xFFFC07FF */
#if MCU_CFG_PART_MEMORY_SIZE >= 0x7         /*   '7' parts 384KB ROM          */
    FLASH_CF_BLOCK_128     = 0xFFFBF800,    /*   2KB: 0xFFFBF800 - 0xFFFBFFFF */
    FLASH_CF_BLOCK_129     = 0xFFFBF000,    /*   2KB: 0xFFFBF000 - 0xFFFBF7FF */
    FLASH_CF_BLOCK_130     = 0xFFFBE800,    /*   2KB: 0xFFFBE800 - 0xFFFBEFFF */
    FLASH_CF_BLOCK_131     = 0xFFFBE000,    /*   2KB: 0xFFFBE000 - 0xFFFBE7FF */
    FLASH_CF_BLOCK_132     = 0xFFFBD800,    /*   2KB: 0xFFFBD800 - 0xFFFBDFFF */
    FLASH_CF_BLOCK_133     = 0xFFFBD000,    /*   2KB: 0xFFFBD000 - 0xFFFBD7FF */
    FLASH_CF_BLOCK_134     = 0xFFFBC800,    /*   2KB: 0xFFFBC800 - 0xFFFBCFFF */
    FLASH_CF_BLOCK_135     = 0xFFFBC000,    /*   2KB: 0xFFFBC000 - 0xFFFBC7FF */
    FLASH_CF_BLOCK_136     = 0xFFFBB800,    /*   2KB: 0xFFFBB800 - 0xFFFBBFFF */
    FLASH_CF_BLOCK_137     = 0xFFFBB000,    /*   2KB: 0xFFFBB000 - 0xFFFBB7FF */
    FLASH_CF_BLOCK_138     = 0xFFFBA800,    /*   2KB: 0xFFFBA800 - 0xFFFBAFFF */
    FLASH_CF_BLOCK_139     = 0xFFFBA000,    /*   2KB: 0xFFFBA000 - 0xFFFBA7FF */
    FLASH_CF_BLOCK_140     = 0xFFFB9800,    /*   2KB: 0xFFFB9800 - 0xFFFB9FFF */
    FLASH_CF_BLOCK_141     = 0xFFFB9000,    /*   2KB: 0xFFFB9000 - 0xFFFB97FF */
    FLASH_CF_BLOCK_142     = 0xFFFB8800,    /*   2KB: 0xFFFB8800 - 0xFFFB8FFF */
    FLASH_CF_BLOCK_143     = 0xFFFB8000,    /*   2KB: 0xFFFB8000 - 0xFFFB87FF */
    FLASH_CF_BLOCK_144     = 0xFFFB7800,    /*   2KB: 0xFFFB7800 - 0xFFFB7FFF */
    FLASH_CF_BLOCK_145     = 0xFFFB7000,    /*   2KB: 0xFFFB7000 - 0xFFFB77FF */
    FLASH_CF_BLOCK_146     = 0xFFFB6800,    /*   2KB: 0xFFFB6800 - 0xFFFB6FFF */
    FLASH_CF_BLOCK_147     = 0xFFFB6000,    /*   2KB: 0xFFFB6000 - 0xFFFB67FF */
    FLASH_CF_BLOCK_148     = 0xFFFB5800,    /*   2KB: 0xFFFB5800 - 0xFFFB5FFF */
    FLASH_CF_BLOCK_149     = 0xFFFB5000,    /*   2KB: 0xFFFB5000 - 0xFFFB57FF */
    FLASH_CF_BLOCK_150     = 0xFFFB4800,    /*   2KB: 0xFFFB4800 - 0xFFFB4FFF */
    FLASH_CF_BLOCK_151     = 0xFFFB4000,    /*   2KB: 0xFFFB4000 - 0xFFFB47FF */
    FLASH_CF_BLOCK_152     = 0xFFFB3800,    /*   2KB: 0xFFFB3800 - 0xFFFB3FFF */
    FLASH_CF_BLOCK_153     = 0xFFFB3000,    /*   2KB: 0xFFFB3000 - 0xFFFB37FF */
    FLASH_CF_BLOCK_154     = 0xFFFB2800,    /*   2KB: 0xFFFB2800 - 0xFFFB2FFF */
    FLASH_CF_BLOCK_155     = 0xFFFB2000,    /*   2KB: 0xFFFB2000 - 0xFFFB27FF */
    FLASH_CF_BLOCK_156     = 0xFFFB1800,    /*   2KB: 0xFFFB1800 - 0xFFFB1FFF */
    FLASH_CF_BLOCK_157     = 0xFFFB1000,    /*   2KB: 0xFFFB1000 - 0xFFFB17FF */
    FLASH_CF_BLOCK_158     = 0xFFFB0800,    /*   2KB: 0xFFFB0800 - 0xFFFB0FFF */
    FLASH_CF_BLOCK_159     = 0xFFFB0000,    /*   2KB: 0xFFFB0000 - 0xFFFB07FF */
    FLASH_CF_BLOCK_160     = 0xFFFAF800,    /*   2KB: 0xFFFAF800 - 0xFFFAFFFF */
    FLASH_CF_BLOCK_161     = 0xFFFAF000,    /*   2KB: 0xFFFAF000 - 0xFFFAF7FF */
    FLASH_CF_BLOCK_162     = 0xFFFAE800,    /*   2KB: 0xFFFAE800 - 0xFFFAEFFF */
    FLASH_CF_BLOCK_163     = 0xFFFAE000,    /*   2KB: 0xFFFAE000 - 0xFFFAE7FF */
    FLASH_CF_BLOCK_164     = 0xFFFAD800,    /*   2KB: 0xFFFAD800 - 0xFFFADFFF */
    FLASH_CF_BLOCK_165     = 0xFFFAD000,    /*   2KB: 0xFFFAD000 - 0xFFFAD7FF */
    FLASH_CF_BLOCK_166     = 0xFFFAC800,    /*   2KB: 0xFFFAC800 - 0xFFFACFFF */
    FLASH_CF_BLOCK_167     = 0xFFFAC000,    /*   2KB: 0xFFFAC000 - 0xFFFAC7FF */
    FLASH_CF_BLOCK_168     = 0xFFFAB800,    /*   2KB: 0xFFFAB800 - 0xFFFABFFF */
    FLASH_CF_BLOCK_169     = 0xFFFAB000,    /*   2KB: 0xFFFAB000 - 0xFFFAB7FF */
    FLASH_CF_BLOCK_170     = 0xFFFAA800,    /*   2KB: 0xFFFAA800 - 0xFFFAAFFF */
    FLASH_CF_BLOCK_171     = 0xFFFAA000,    /*   2KB: 0xFFFAA000 - 0xFFFAA7FF */
    FLASH_CF_BLOCK_172     = 0xFFFA9800,    /*   2KB: 0xFFFA9800 - 0xFFFA9FFF */
    FLASH_CF_BLOCK_173     = 0xFFFA9000,    /*   2KB: 0xFFFA9000 - 0xFFFA97FF */
    FLASH_CF_BLOCK_174     = 0xFFFA8800,    /*   2KB: 0xFFFA8800 - 0xFFFA8FFF */
    FLASH_CF_BLOCK_175     = 0xFFFA8000,    /*   2KB: 0xFFFA8000 - 0xFFFA87FF */
    FLASH_CF_BLOCK_176     = 0xFFFA7800,    /*   2KB: 0xFFFA7800 - 0xFFFA7FFF */
    FLASH_CF_BLOCK_177     = 0xFFFA7000,    /*   2KB: 0xFFFA7000 - 0xFFFA77FF */
    FLASH_CF_BLOCK_178     = 0xFFFA6800,    /*   2KB: 0xFFFA6800 - 0xFFFA6FFF */
    FLASH_CF_BLOCK_179     = 0xFFFA6000,    /*   2KB: 0xFFFA6000 - 0xFFFA67FF */
    FLASH_CF_BLOCK_180     = 0xFFFA5800,    /*   2KB: 0xFFFA5800 - 0xFFFA5FFF */
    FLASH_CF_BLOCK_181     = 0xFFFA5000,    /*   2KB: 0xFFFA5000 - 0xFFFA57FF */
    FLASH_CF_BLOCK_182     = 0xFFFA4800,    /*   2KB: 0xFFFA4800 - 0xFFFA4FFF */
    FLASH_CF_BLOCK_183     = 0xFFFA4000,    /*   2KB: 0xFFFA4000 - 0xFFFA47FF */
    FLASH_CF_BLOCK_184     = 0xFFFA3800,    /*   2KB: 0xFFFA3800 - 0xFFFA3FFF */
    FLASH_CF_BLOCK_185     = 0xFFFA3000,    /*   2KB: 0xFFFA3000 - 0xFFFA37FF */
    FLASH_CF_BLOCK_186     = 0xFFFA2800,    /*   2KB: 0xFFFA2800 - 0xFFFA2FFF */
    FLASH_CF_BLOCK_187     = 0xFFFA2000,    /*   2KB: 0xFFFA2000 - 0xFFFA27FF */
    FLASH_CF_BLOCK_188     = 0xFFFA1800,    /*   2KB: 0xFFFA1800 - 0xFFFA1FFF */
    FLASH_CF_BLOCK_189     = 0xFFFA1000,    /*   2KB: 0xFFFA1000 - 0xFFFA17FF */
    FLASH_CF_BLOCK_190     = 0xFFFA0800,    /*   2KB: 0xFFFA0800 - 0xFFFA0FFF */
    FLASH_CF_BLOCK_191     = 0xFFFA0000,    /*   2KB: 0xFFFA0000 - 0xFFFA07FF */
#endif /* MCU_CFG_PART_MEMORY_SIZE >= 0x7 */
#if MCU_CFG_PART_MEMORY_SIZE >= 0x8         /*   '8' parts 512KB ROM          */
    FLASH_CF_BLOCK_192     = 0xFFF9F800,    /*   2KB: 0xFFF9F800 - 0xFFF9FFFF */
    FLASH_CF_BLOCK_193     = 0xFFF9F000,    /*   2KB: 0xFFF9F000 - 0xFFF9F7FF */
    FLASH_CF_BLOCK_194     = 0xFFF9E800,    /*   2KB: 0xFFF9E800 - 0xFFF9EFFF */
    FLASH_CF_BLOCK_195     = 0xFFF9E000,    /*   2KB: 0xFFF9E000 - 0xFFF9E7FF */
    FLASH_CF_BLOCK_196     = 0xFFF9D800,    /*   2KB: 0xFFF9D800 - 0xFFF9DFFF */
    FLASH_CF_BLOCK_197     = 0xFFF9DE00,    /*   2KB: 0xFFF9DE00 - 0xFFF9D7FF */
    FLASH_CF_BLOCK_198     = 0xFFF9C800,    /*   2KB: 0xFFF9C800 - 0xFFF9CFFF */
    FLASH_CF_BLOCK_199     = 0xFFF9C000,    /*   2KB: 0xFFF9C000 - 0xFFF9C7FF */
    FLASH_CF_BLOCK_200     = 0xFFF9B800,    /*   2KB: 0xFFF9B800 - 0xFFF9BFFF */
    FLASH_CF_BLOCK_201     = 0xFFF9B000,    /*   2KB: 0xFFF9B000 - 0xFFF9B7FF */
    FLASH_CF_BLOCK_202     = 0xFFF9A800,    /*   2KB: 0xFFF9A800 - 0xFFF9AFFF */
    FLASH_CF_BLOCK_203     = 0xFFF9A000,    /*   2KB: 0xFFF9A000 - 0xFFF9A7FF */
    FLASH_CF_BLOCK_204     = 0xFFF99800,    /*   2KB: 0xFFF99800 - 0xFFF99FFF */
    FLASH_CF_BLOCK_205     = 0xFFF99000,    /*   2KB: 0xFFF99000 - 0xFFF997FF */
    FLASH_CF_BLOCK_206     = 0xFFF98800,    /*   2KB: 0xFFF98800 - 0xFFF98FFF */
    FLASH_CF_BLOCK_207     = 0xFFF98000,    /*   2KB: 0xFFF98000 - 0xFFF987FF */
    FLASH_CF_BLOCK_208     = 0xFFF97800,    /*   2KB: 0xFFF97800 - 0xFFF97FFF */
    FLASH_CF_BLOCK_209     = 0xFFF97000,    /*   2KB: 0xFFF97000 - 0xFFF977FF */
    FLASH_CF_BLOCK_210     = 0xFFF96800,    /*   2KB: 0xFFF96800 - 0xFFF96FFF */
    FLASH_CF_BLOCK_211     = 0xFFF96000,    /*   2KB: 0xFFF96000 - 0xFFF967FF */
    FLASH_CF_BLOCK_212     = 0xFFF95800,    /*   2KB: 0xFFF95800 - 0xFFF95FFF */
    FLASH_CF_BLOCK_213     = 0xFFF95000,    /*   2KB: 0xFFF95000 - 0xFFF957FF */
    FLASH_CF_BLOCK_214     = 0xFFF94800,    /*   2KB: 0xFFF94800 - 0xFFF94FFF */
    FLASH_CF_BLOCK_215     = 0xFFF94000,    /*   2KB: 0xFFF94000 - 0xFFF947FF */
    FLASH_CF_BLOCK_216     = 0xFFF93800,    /*   2KB: 0xFFF93800 - 0xFFF93FFF */
    FLASH_CF_BLOCK_217     = 0xFFF93000,    /*   2KB: 0xFFF93000 - 0xFFF937FF */
    FLASH_CF_BLOCK_218     = 0xFFF92800,    /*   2KB: 0xFFF92800 - 0xFFF92FFF */
    FLASH_CF_BLOCK_219     = 0xFFF92000,    /*   2KB: 0xFFF92000 - 0xFFF927FF */
    FLASH_CF_BLOCK_220     = 0xFFF91800,    /*   2KB: 0xFFF91800 - 0xFFF91FFF */
    FLASH_CF_BLOCK_221     = 0xFFF91000,    /*   2KB: 0xFFF91000 - 0xFFF917FF */
    FLASH_CF_BLOCK_222     = 0xFFF90800,    /*   2KB: 0xFFF90800 - 0xFFF90FFF */
    FLASH_CF_BLOCK_223     = 0xFFF90000,    /*   2KB: 0xFFF90000 - 0xFFF907FF */
    FLASH_CF_BLOCK_224     = 0xFFF8F800,    /*   2KB: 0xFFF8F800 - 0xFFF8FFFF */
    FLASH_CF_BLOCK_225     = 0xFFF8F000,    /*   2KB: 0xFFF8F000 - 0xFFF8F7FF */
    FLASH_CF_BLOCK_226     = 0xFFF8E800,    /*   2KB: 0xFFF8E800 - 0xFFF8EFFF */
    FLASH_CF_BLOCK_227     = 0xFFF8E000,    /*   2KB: 0xFFF8E000 - 0xFFF8E7FF */
    FLASH_CF_BLOCK_228     = 0xFFF8D800,    /*   2KB: 0xFFF8D800 - 0xFFF8DFFF */
    FLASH_CF_BLOCK_229     = 0xFFF8D000,    /*   2KB: 0xFFF8D000 - 0xFFF8D7FF */
    FLASH_CF_BLOCK_230     = 0xFFF8C800,    /*   2KB: 0xFFF8C800 - 0xFFF8CFFF */
    FLASH_CF_BLOCK_231     = 0xFFF8C000,    /*   2KB: 0xFFF8C000 - 0xFFF8C7FF */
    FLASH_CF_BLOCK_232     = 0xFFF8B800,    /*   2KB: 0xFFF8B800 - 0xFFF8BFFF */
    FLASH_CF_BLOCK_233     = 0xFFF8B000,    /*   2KB: 0xFFF8B000 - 0xFFF8B7FF */
    FLASH_CF_BLOCK_234     = 0xFFF8A800,    /*   2KB: 0xFFF8A800 - 0xFFF8AFFF */
    FLASH_CF_BLOCK_235     = 0xFFF8A000,    /*   2KB: 0xFFF8A000 - 0xFFF8A7FF */
    FLASH_CF_BLOCK_236     = 0xFFF89800,    /*   2KB: 0xFFF89800 - 0xFFF89FFF */
    FLASH_CF_BLOCK_237     = 0xFFF89000,    /*   2KB: 0xFFF89000 - 0xFFF897FF */
    FLASH_CF_BLOCK_238     = 0xFFF88800,    /*   2KB: 0xFFF88800 - 0xFFF88FFF */
    FLASH_CF_BLOCK_239     = 0xFFF88000,    /*   2KB: 0xFFF88000 - 0xFFF887FF */
    FLASH_CF_BLOCK_240     = 0xFFF87800,    /*   2KB: 0xFFF87800 - 0xFFF87FFF */
    FLASH_CF_BLOCK_241     = 0xFFF87000,    /*   2KB: 0xFFF87000 - 0xFFF877FF */
    FLASH_CF_BLOCK_242     = 0xFFF86800,    /*   2KB: 0xFFF86800 - 0xFFF86FFF */
    FLASH_CF_BLOCK_243     = 0xFFF86000,    /*   2KB: 0xFFF86000 - 0xFFF867FF */
    FLASH_CF_BLOCK_244     = 0xFFF85800,    /*   2KB: 0xFFF85800 - 0xFFF85FFF */
    FLASH_CF_BLOCK_245     = 0xFFF85000,    /*   2KB: 0xFFF85000 - 0xFFF857FF */
    FLASH_CF_BLOCK_246     = 0xFFF84800,    /*   2KB: 0xFFF84800 - 0xFFF84FFF */
    FLASH_CF_BLOCK_247     = 0xFFF84000,    /*   2KB: 0xFFF84000 - 0xFFF847FF */
    FLASH_CF_BLOCK_248     = 0xFFF83800,    /*   2KB: 0xFFF83800 - 0xFFF83FFF */
    FLASH_CF_BLOCK_249     = 0xFFF83000,    /*   2KB: 0xFFF83000 - 0xFFF837FF */
    FLASH_CF_BLOCK_250     = 0xFFF82800,    /*   2KB: 0xFFF82800 - 0xFFF82FFF */
    FLASH_CF_BLOCK_251     = 0xFFF82000,    /*   2KB: 0xFFF82000 - 0xFFF827FF */
    FLASH_CF_BLOCK_252     = 0xFFF81800,    /*   2KB: 0xFFF81800 - 0xFFF81FFF */
    FLASH_CF_BLOCK_253     = 0xFFF81000,    /*   2KB: 0xFFF81000 - 0xFFF817FF */
    FLASH_CF_BLOCK_254     = 0xFFF80800,    /*   2KB: 0xFFF80800 - 0xFFF80FFF */
    FLASH_CF_BLOCK_255     = 0xFFF80000,    /*   2KB: 0xFFF80000 - 0xFFF807FF */
#endif /* MCU_CFG_PART_MEMORY_SIZE >= 0x8 */
    FLASH_CF_BLOCK_INVALID = FLASH_CF_BLOCK_END - (FLASH_CF_BLOCK_SIZE * FLASH_NUM_BLOCKS_CF),

    FLASH_DF_BLOCK_0       = 0x00100000,    /*  256B: 0x00100000 - 0x001000FF */
    FLASH_DF_BLOCK_1       = 0x00100100,    /*  256B: 0x00100100 - 0x001001FF */
    FLASH_DF_BLOCK_2       = 0x00100200,    /*  256B: 0x00100200 - 0x001002FF */
    FLASH_DF_BLOCK_3       = 0x00100300,    /*  256B: 0x00100300 - 0x001003FF */
    FLASH_DF_BLOCK_4       = 0x00100400,    /*  256B: 0x00100400 - 0x001004FF */
    FLASH_DF_BLOCK_5       = 0x00100500,    /*  256B: 0x00100500 - 0x001005FF */
    FLASH_DF_BLOCK_6       = 0x00100600,    /*  256B: 0x00100600 - 0x001006FF */
    FLASH_DF_BLOCK_7       = 0x00100700,    /*  256B: 0x00100700 - 0x001007FF */
    FLASH_DF_BLOCK_8       = 0x00100800,    /*  256B: 0x00100800 - 0x001008FF */
    FLASH_DF_BLOCK_9       = 0x00100900,    /*  256B: 0x00100900 - 0x001009FF */
    FLASH_DF_BLOCK_10      = 0x00100A00,    /*  256B: 0x00100A00 - 0x00100AFF */
    FLASH_DF_BLOCK_11      = 0x00100B00,    /*  256B: 0x00100B00 - 0x00100BFF */
    FLASH_DF_BLOCK_12      = 0x00100C00,    /*  256B: 0x00100C00 - 0x00100CFF */
    FLASH_DF_BLOCK_13      = 0x00100D00,    /*  256B: 0x00100D00 - 0x00100DFF */
    FLASH_DF_BLOCK_14      = 0x00100E00,    /*  256B: 0x00100E00 - 0x00100EFF */
    FLASH_DF_BLOCK_15      = 0x00100F00,    /*  256B: 0x00100F00 - 0x00100FFF */
    FLASH_DF_BLOCK_16      = 0x00101000,    /*  256B: 0x00101000 - 0x001010FF */
    FLASH_DF_BLOCK_17      = 0x00101100,    /*  256B: 0x00101100 - 0x001011FF */
    FLASH_DF_BLOCK_18      = 0x00101200,    /*  256B: 0x00101200 - 0x001012FF */
    FLASH_DF_BLOCK_19      = 0x00101300,    /*  256B: 0x00101300 - 0x001013FF */
    FLASH_DF_BLOCK_20      = 0x00101400,    /*  256B: 0x00101400 - 0x001014FF */
    FLASH_DF_BLOCK_21      = 0x00101500,    /*  256B: 0x00101500 - 0x001015FF */
    FLASH_DF_BLOCK_22      = 0x00101600,    /*  256B: 0x00101600 - 0x001016FF */
    FLASH_DF_BLOCK_23      = 0x00101700,    /*  256B: 0x00101700 - 0x001017FF */
    FLASH_DF_BLOCK_24      = 0x00101800,    /*  256B: 0x00101800 - 0x001018FF */
    FLASH_DF_BLOCK_25      = 0x00101900,    /*  256B: 0x00101900 - 0x001019FF */
    FLASH_DF_BLOCK_26      = 0x00101A00,    /*  256B: 0x00101A00 - 0x00101AFF */
    FLASH_DF_BLOCK_27      = 0x00101B00,    /*  256B: 0x00101B00 - 0x00101BFF */
    FLASH_DF_BLOCK_28      = 0x00101C00,    /*  256B: 0x00101B00 - 0x00101CFF */
    FLASH_DF_BLOCK_29      = 0x00101D00,    /*  256B: 0x00101B00 - 0x00101DFF */
    FLASH_DF_BLOCK_30      = 0x00101E00,    /*  256B: 0x00101B00 - 0x00101EFF */
    FLASH_DF_BLOCK_31      = 0x00101F00,    /*  256B: 0x00101C00 - 0x00101FFF */
    FLASH_DF_BLOCK_INVALID = FLASH_DF_BLOCK_0 + (FLASH_DF_BLOCK_SIZE * FLASH_NUM_BLOCKS_DF)
} flash_block_address_t;


/*  According to HW Manual the Max Programming Time for 8 bytes (ROM)
    is 843.5 us.  This is with a FCLK of 1MHz. The calculation below
    calculates the number of ICLK ticks needed for the timeout delay.
    The 843.5 us number is adjusted linearly depending on the FCLK frequency.
*/
#define WAIT_MAX_ROM_WRITE \
        ((int32_t)(844 * (MCU_CFG_ICLK_HZ/1000000)))

/*  According to HW Manual the Max Programming Time for 1 bytes
    (Data Flash) is 729.5 us.  This is with a FCLK of 1MHz. The calculation
    below calculates the number of ICLK ticks needed for the timeout delay.
    The 729.5 us number is adjusted linearly depending on the FCLK frequency.
*/
#define WAIT_MAX_DF_WRITE \
        ((int32_t)(730 * (MCU_CFG_ICLK_HZ/1000000)))

/*  According to HW Manual the Max Blank Check time for 1 bytes
    (Data Flash) is 44.6 usec.  This is with a FCLK of 1MHz. The calculation
    below calculates the number of ICLK ticks needed for the timeout delay.
    The 44.6 usec number is adjusted linearly depending on the FCLK frequency.
*/
#define WAIT_MAX_BLANK_CHECK \
        ((int32_t)(45 * (MCU_CFG_ICLK_HZ/1000000)))


/*  According to HW Manual the Max Erasure Time for a 512KB block is
    around 17356 ms.  This is with a FCLK of 1MHz. The calculation below
    calculates the number of ICLK ticks needed for the timeout delay.
    The 17356 ms number is adjusted linearly depending on the FCLK frequency.
*/
#define WAIT_MAX_ERASE_CF_1K \
        ((int32_t)((17356000) * (MCU_CFG_ICLK_HZ/1000000)))

/*  According to HW Manual the Max Erasure Time for a 8KB Data Flash block is
    around 2331.4 ms.  This is with a FCLK of 1MHz. The calculation below
    calculates the number of ICLK ticks needed for the timeout delay.
    The 2331.4 ms number is adjusted linearly depending on the FCLK frequency.
*/
#define WAIT_MAX_ERASE_DF_1K \
        ((int32_t)((2331400) * (MCU_CFG_ICLK_HZ/1000000)))

#define WAIT_MAX_ERASE_CF   WAIT_MAX_ERASE_CF_1K
#define WAIT_MAX_ERASE_DF   WAIT_MAX_ERASE_DF_1K

/*  According to HW Manual the Max Setting Time for Start-up area switching and Access window is around 503.3ms.
    This is with a FCLK of 1MHz. 
    The calculation below calculates the number of ICLK ticks needed for the timeout delay.
    The 503.3ms number is adjusted linearly depending on the FCLK frequency.
*/
#define WAIT_MAX_EXRDY_CMD_TIMEOUT \
        ((int32_t)(503300 *(MCU_CFG_ICLK_HZ/1000000)))

#endif /* R_FLASH_RX261_H */
