PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_ble_da14531_rx
=======

Document Number
---------------
R01AN7174EU (English version)

Version
-------
v1.40

Overview
--------------------------------------------------------------------------------
The r_ble_da14531_rx module provides BLE GAP functionality for DA14531 BLE module
which are compliant with Bluetooth version 5.0.
This driver is tested and works with the following toolchain:
  Renesas RX Toolchain v3.06.00
All API calls and their supporting interface definitions are located in r_ble_da14531_if.h.

Features
--------
* Peripheral support only
* Legacy Advertising, connection (No Security)
* UART support
* Dynamic loading of custom profile
* Integration with QE BLE plugin
* GAP, GATT Server
* FreeRTOS Support
* AzureRTOS Support
* Bare metal support
* L2CAP, GATT Client support
* Support SDK download from host MCU
* Sleep mode support
* Common functionality for DA1453x
  - Boot from host or DA14531/DA14535 flash
  - Use 1-wire (default) or 2-wire UART for booting
  - Open/Close the BLE protocol stack
* GATT Server functionality: 
  - Notification of characteristics modification
  - Read/Write of GATT Profile from host
  - Loading of Profile definition
*Security functionality (DA14531/DA14535 module acting as Peripheral)
  - Legacy Pairing supporting Just works functionality
  - Legacy Pairing supporting Passkey functionality
  - Initiate security request procedure from Peripheral as well

Supported MCUs
--------------
* RX65N Group

Boards Tested On
----------------
* CK-RX65N

Limitations
-----------
* r_ble_da14531_rx only supports QE BLE projects. To generate sample code using QE for BLE,
  please refer to the Application Note (5. Sample Code Generation Using QE for BLE).
* The boot from host feature currently supports:
  - 1-wire UART operation
  - 2-wire UART operation. (*Note1)
Note1: Only be used with DA14535 device

Peripherals Used Directly
-------------------------
* BLE (Bluetooth Low Energy)

Required Packages
-----------------
* r_bsp
* r_sci_rx
* r_byteq

How to add to your project
--------------------------
Please refer to the Adding Firmware Integration Technology Modules to Projects.
"r01an1723eu0130_rx.pdf/r01an1826ej0110_rx.pdf/r20an0451es0100-e2studio-sc.pdf"(Only English version)
"r01an1723ju0130_rx.pdf/r01an1826jj0110_rx.pdf/r20an0451js0100-e2studio-sc.pdf"(Only Japanese version)

Toolchain(s) Used
-----------------
* Renesas RX v3.06.00

File Structure
--------------
r_ble_da14531_rx
|   readme.txt
|   r_ble_da14531_if.h
|
+---doc
|    \---en
|           r01an7174eu{VERSION_NUMBER}-rx-da14531-ble.pdf
|
\---src
    |   hal_data.c
    |   hal_data.h
    |   r_ble_api.h
    |   r_ble_gtl_api.c
    |
    |
    +---rm_abs
    |       rm_ble_abs.h
    |       rm_ble_abs_api.h
    |       rm_ble_abs_gtl.c
    |
    |
    \---r_ble_gtl
            r_ble_gtl.c
            r_ble_gtl.h
            r_ble_gtl_image.c
            r_ble_gtl_image.h
            r_ble_gtl_security.c
            r_ble_gtl_security.h
            r_ble_gtl_typedef.h
r_config
    r_ble_da14531_config.h