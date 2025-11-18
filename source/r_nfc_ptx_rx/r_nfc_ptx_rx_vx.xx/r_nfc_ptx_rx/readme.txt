PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_nfc_ptx_rx
=======

Document Number
---------------
R01AN7890EU0100 (English version)

Version
-------
v1.00

Overview
--------------------------------------------------------------------------------
The r_nfc_ptx_rx module is a NFC driver.

This driver is tested and works with the following toolchain:
  Renesas Electronics C/C++ Compiler for RX Family V3.07.00
All API calls and their supporting interface definitions are located in r_nfc_ptx_if.h.

Features
--------
* Initializes the IOTRD (IoT Reader) API and NSC stack
* Initializes the PTX chip
* Discovers cards according to NFC Forum
* Selects a specific card in case multiple cards/protocols were discovered
* Retrieves card details like technical/activation parameters
* Exchanges RF data and bitstreams
* Stops RF communication
* Controls various GPIO pins of the PTX chip

Supported MCUs
--------------
* RX261 Group

Boards Tested On
----------------
* EK-RX261

Required Packages
-----------------
* r_bsp
* r_sci_rx
* r_byteq
* r_irq_rx
* r_gpio_rx
* r_cmt_rx

How to add to your project
--------------------------
Please refer to the Adding Firmware Integration Technology Modules to Projects.
"r01an1723eu0121_rx.pdf/r01an1826ej0110_rx.pdf/r20an0451es0100-e2studio-sc.pdf"(Only English version)
"r01an1723ju0121_rx.pdf/r01an1826jj0110_rx.pdf/r20an0451js0100-e2studio-sc.pdf"(Only Japanese version)

Toolchain(s) Used
-----------------
* Renesas Electronics C/C++ Compiler for RX Family V3.07.00

File Structure
--------------
r_nfc_ptx_rx
|   readme.txt
|   r_nfc_ptx_if.h
|
+---doc
|    \---en
|           r01an7890eu0100-rx-ptx-nfc.pdf
|
+---lib
|    \---nfc_reader_ptx_sdk
|
|
\---src
        r_nfc_ptx_common.c
        r_nfc_ptx_common.h
        r_nfc_ptx_reader.c

r_config
    r_nfc_ptx_rx_config.h
