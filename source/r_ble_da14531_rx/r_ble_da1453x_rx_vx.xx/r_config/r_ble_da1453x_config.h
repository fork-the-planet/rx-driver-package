/* Generated configuration header file - do not edit */
/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2025 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_ble_da1453x_config.h
 * Description  : DA1453x BLE driver Configuration.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/
#ifndef R_BLE_DA1453X_CONFIG_H_
#define R_BLE_DA1453X_CONFIG_H_

/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting */
/* Setting to 1 includes parameter checking; 0 compiles out parameter checking */
#define BLE_CFG_PARAM_CHECKING_ENABLE        (BSP_CFG_PARAM_CHECKING_ENABLE)

/* Interrupt Level for BLE_CFG_SCI_CHANNEL */
#define BLE_CFG_SCI_INTERRUPT_LEVEL                 (3)

/* SCI channel for DA1453x GTL command communication*/
#define BLE_CFG_SCI_CHANNEL                         (10)

/* Configure SCK */
#define BLE_CFG_SCK_PORT                            8
#define BLE_CFG_SCK_PIN                             0

/* Configure reset */
#define BLE_CFG_RESET_PORT                          4
#define BLE_CFG_RESET_PIN                           7

/* Board dependent settings; please use the value for each setting listed below depending on the board you use.

Preprocessors that define board dependent settings and the corresponding values to be set are as follows:
Confirmed board number    1      2      3      4      5      6      7      8      9       10       11      12      13      14      15      16      17      18
BLE_CFG_SCI_CHANNEL       0      2      6      1      6      0      6      2      10      11       5       5       5       1       5       9       5       9
BLE_CFG_SCK_PORT          2      5      0      F      0      3      0      5      8       7        C       C       A       3       C       B       C       B
BLE_CFG_SCK_PIN           2      1      2      1      2      4      2      1      0       5        1       1       1       1       1       5       1       5
BLE_CFG_RESET_PORT        D      5      F      2      5      A      5      A      4       C        B       B       B       B       D       5       D       5
BLE_CFG_RESET_PIN         0      5      5      0      5      1      5      1      7       0        1       1       3       2       7       1       7       1

where the confirmed board numbers listed in the first row above are as follows (*Note1):
1: RX65N Cloud Kit (PMOD)
2: RX65N Envision Kit (PMOD)
3: RX65N RSK (2MB) (PMOD1)
4: RX65N RSK (2MB) (PMOD2)
5: CK-RX65N v1 (PMOD1)
6: CK-RX65N v1 (PMOD2)
7: CK-RX65N v2 (PMOD1)
8: CK-RX65N v2 (PMOD2)
9: EK-RX671 v1 (PMOD1)
10: EK-RX671 v1 (PMOD2)
11: RX671 Target Board (PMOD)    (*Note2)
12: RX66N Target Board (PMOD)   (*Note3)
13: RX140 FPB (PMOD1)
14: RX140 FPB (PMOD2)
15: EK-RX261 v1 (PMOD1)
16: EK-RX261 v1 (PMOD2)
17: RX261 FPB v1 (PMOD1)        (*Note4)
18: RX261 FPB v1 (PMOD2)        (*Note4)
In the above preprocessor list, please use one of the values listed on the right side.
On the right side, each column corresponds to each confirmed board number.

Note1: List of board user's manual:
1: RX65N Cloud Kit:    https://www.renesas.com/us/en/document/mat/uses-manual-cloud-option-board
2: RX65N Envision Kit: https://www.renesas.com/us/en/document/mat/rx65n-envision-kit-users-manual-rev100
3: RX65N RSK (2MB):    https://www.renesas.com/us/en/document/mat/renesas-starter-kit-rx65n-2mb-users-manual
4: CK-RX65N v1:        https://www.renesas.com/kr/en/document/mat/ck-rx65n-v1-users-manual
5: CK-RX65N v1:        https://www.renesas.com/kr/en/document/mat/ck-rx65n-v2-users-manual
6: EK-RX671 v1:        https://www.renesas.com/en/document/mat/ek-rx671-v1-users-manual
7: RX671 Target Board: https://www.renesas.com/br/en/document/mat/target-board-rx671-users-manual-rev100
8: RX66N Target Board: https://www.renesas.com/us/en/document/mah/target-board-rx66n-users-manual-rev100
9: RX140 FPB:          https://www.renesas.com/en/document/mat/fpb-rx140-v1-users-manual
10: EK-RX261:           https://www.renesas.com/en/document/mat/ek-rx261-v1-users-manual
11: RX261 FPB          https://www.renesas.com/en/document/mat/fpb-rx261-v1-users-manual

Note2:
- When you use RX671 Target Board, you need pattern cut and so on to use SCI channel 5(TXD5/RXD5/CTS5) and GPIO(PC1).
Please refer to User's Manual: https://www.renesas.com/products/microcontrollers-microprocessors/rx-32-bit-performance-efficiency-mcus/rtk5rx6710c00000bj-target-board-rx671

Note3:
- When you use RX66N Target Board, you need remodeling of the board to use SCI channel 5(TXD5/RXD5/CTS5) and GPIO(PC1).
Please refer to User's Manual: https://www.renesas.com/products/microcontrollers-microprocessors/rx-32-bit-performance-efficiency-mcus/rtk5rx66n0c00000bj-target-board-rx66n
- RX66N Target Board not support AzureRTOS.

Note4:
- Only support Bare metal mode.
*/

/* Specify module reset polarity */
/* 1=Activa High, 0=Active Low */
#define BLE_CFG_RESET_POLARITY                      (0)

/* Boot SDK download from host MCU
0 = Disabled boot mode
1 = Boot SDK download from host MCU via 1-Wire UART
2 = Boot SDK download from host MCU via 2-Wire UART (*Note7)
Note7: Only be used with the DA14535 device
*/
#define BLE_CFG_HOST_BOOT_MODE                      (0)

/* Option BLE DA1453x
DA14531 = DA14531 device is selected
DA14535 = DA14535 device is selected
*/
#define BLE_CFG_DA1453X_DEVICE (DA14531_DEVICE)

#define BLE_CFG_DEVICE_ROLE                (R_BLE_GTL_PERIPHERAL_ROLE)

/* Pairing Configuration */

/* Specifies the I/O capabilities of the device for pairing:
BLE_GAP_DISPLAY_ONLY 		= Show passkey only.
BLE_GAP_DISPLAY_YESNO 		= Show passkey + Yes/No input.
BLE_GAP_KEYBOARD_ONLY 		= Input passkey only.
BLE_GAP_NOINPUT_NOOUTPUT 	= No I/O (Just Works).
BLE_GAP_KEYBOARD_DISPLAY 	= Both display and input passkey.
*/
#define BLE_CFG_IO_CAPABILITY				(BLE_GAP_IOCAP_NOINPUT_NOOUTPUT)

/* Defines which keys the local device distributes:
BLE_GAP_KEY_DIST_ENCKEY		= Encryption key (LTK).
BLE_GAP_KEY_DIST_IDKEY		= Identity key (IRK).
BLE_GAP_KEY_DIST_SIGNKEY	= Signing key (CSRK).
*/
#define BLE_CFG_SECURITY_KEY_DIST			(BLE_GAP_KEY_DIST_ENCKEY)

/* Defines which keys the device expects from peer:
BLE_GAP_KEY_DIST_ENCKEY		= Request LTK.
BLE_GAP_KEY_DIST_IDKEY		= Request IRK.
BLE_GAP_KEY_DIST_SIGNKEY	= Request CSRK.
*/
#define BLE_CFG_SECURITY_KEY_DIST_PEER		(BLE_GAP_KEY_DIST_IDKEY)

/* Specifies MITM protection policy:
BLE_GAP_SEC_MITM_BEST_EFFORT = Attempts to use MITM protection if supported by the peer, still accepts connections without MITM.
BLE_GAP_SEC_MITM_STRICT		 = Requires MITM protection. Connection is allowed only if pairing includes authentication.
*/
#define BLE_CFG_MITM_PROTECTION				(BLE_GAP_SEC_MITM_BEST_EFFORT)

/* Controls Secure Connections mode:
BLE_GAP_SC_STRICT		= Only accept Secure Connections
BLE_GAP_SC_BEST_EFFORT	= Prefer Secure Connections, allow legacy.
*/
#define BLE_CFG_SECURE_CONNECTIONS			(BLE_GAP_SC_BEST_EFFORT)

/* Sets the maximum size (in bytes) of the Long Term Key (LTK)*/
#define BLE_CFG_MAX_LTK_SIZE				(16)

/* Secure bonding configuration*/

/* Enables or disables the secure data storage feature for bonding information.
0 = Disable secure data storage
1 = Enable secure data storage.
*/
#define BLE_ABS_CFG_ENABLE_SECURE_DATA              (0)

/* Specifies the data flash block number to be used for secure bonding data storage*/
#define BLE_ABS_CFG_SECURE_DATA_DATAFLASH_BLOCK     (0)

/*Defines the maximum number of devices that can be bonded.*/
#define BLE_ABS_CFG_NUMBER_BONDING                  (7)

/* Sleep mode configuration*/

/* Sleep flow control 
- 0 = Sleep flow control is disabled.
- 1 = Sleep flow control is enabled.
*/
#define BLE_DA1453x_SLEEP_FLOW_CONTROL     (0)

/**********************************************************************************************************************
 Global Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 External global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global functions
 *********************************************************************************************************************/

#endif /* R_BLE_DA1453X_CONFIG_H_ */
