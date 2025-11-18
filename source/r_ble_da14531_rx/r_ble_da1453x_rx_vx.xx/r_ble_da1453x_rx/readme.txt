PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_ble_da1453x_rx
=======

Document Number
---------------
R01AN7174EU (English version)

Version
-------
v1.60

Overview
--------------------------------------------------------------------------------
The r_ble_da1453x_rx module provides BLE GAP functionality for DA1453x BLE module
which are compliant with Bluetooth version 5.0.
This driver is tested and works with the following toolchain:
  Renesas RX Toolchain v3.07.00
All API calls and their supporting interface definitions are located in r_ble_da1453x_if.h.

Features
--------
* UART support
* Dynamic loading of custom profile
* Integration with QE BLE plugin
* FreeRTOS, AzureRTOS, Bare metal Support
* GATT Client support
* Support SDK download from host MCU

* Common functionality for DA1453x:
  - Boot from host or DA14531/DA14535 flash
  - Use 1-wire (default) or 2-wire UART for booting
  - Open/Close the BLE protocol stack

*The following GAP Role support:
  - Peripheral: The device that accepts a connection request from Central and establishes a connection
  - Central: The device that initiates a connection with a peripheral
  - All roles: The device may act as a central and peripheral the same time

* GATT Common functionality:
  - Get MTU Size
  
* GAP functionality:
  - Initialize the Host stack
  - Setting address
  - Start/Stop Advertising
  - Connect/Disconnect a link
  - Scan
  
* GATT Server functionality:
  - Initialization of GATT Server
  - Loading of Profile definition
  - Notifications and Indications
  - Read/Write of GATT Profile from host
  - Optionally the application and not the device may handle the attributes (Read Indication)
  
* GATT Client functionality:
  - Discover Peripheral Services/Characteristics
  - Read/Write Peripheral Characteristics
  - Receive Notifications and Indications
  
*Security functionality (DA14531/DA14535 module acting as Peripheral):
  - Legacy Pairing supporting Just works functionality
  - Legacy Pairing supporting Passkey functionality
  - Initiate security request procedure from Peripheral as well
  - Secure connection with Numeric Comparison
  - Support security for both roles (Central - Peripheral)
  - Enable security configuration

Supported MCUs
--------------
* RX65N Group
* RX671 Group
* RX66N Group
* RX261 Group
* RX140 FPB

Boards Tested On
----------------
* CK-RX65N v1
* CK-RX65N v2
* EK-RX671
* RX671 Target Board
* RX66N Target Board
* EK-RX261
* RX261-FPB
* RX140-FPB

Limitations
-----------
* r_ble_da1453x_rx only supports QE BLE projects. To generate sample code using QE for BLE,
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
* Renesas RX v3.07.00

File Structure
--------------
r_ble_da1453x_rx
|   readme.txt
|   r_ble_da1453x_if.h
|
+---doc
|    \---en
|           r01an7174eu{VERSION_NUMBER}-rx-da1453x-ble.pdf
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
    r_ble_da1453x_config.h