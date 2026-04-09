PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_src_api_rx
=======================

Document Number 
---------------
r01an2090jj0116
r01an2090ej0116


Version
-------
v1.16

Overview
--------
This is a FIT compliant module for RX's SRC peripheral.
It provides ways of sampling rate conversion using the SRC (Sampling Rate Converter) peripheral.

Features
--------
* PCM data sampling rate conversion with SRC peripheral.

Supported MCUs
--------------
* RX64M Group
* RX71M Group

Boards Tested On
----------------
* RSKRX64M
* RSKRX71M
 
Limitations
-----------
* None

Peripherals Used Directly
-------------------------
* SRC (Smapling Rate Converter)

Required Packages
-----------------
* r_bsp     v5.50

How to add to your project
--------------------------
* Add src\r_src_api_rx.c to your project.
* Add an include path to the 'r_src_api_rx' directory. 
* Add an include path to the 'r_src_api_rx\src' directory.
* Configure this API through r_src_api_rx_config.h.
* Add a #include for r_src_api_rx_if.h in any source file that needs to use this API.

Toolchain(s) Used
-----------------
* Renesas RX v3.07.00
* GCC for Renesas RX 14.2.0.202511
* IAR C/C++ Compiler for Renesas RX version 5.20.1

File Structure
--------------
r_src_api_rx
|  readme.txt
|  r_src_api_rx_if.h
|
+---doc
|   +---en
|   |   r01an2090ej0116-rx-src.pdf
|   |
|   +---ja
|       r01an2090jj0116-rx-src.pdf
|
|
\---src
   r_src_api_rx.c
   r_src_api_rx_coef_table.c
   r_src_api_rx_private.h

r_config
    r_sci_iic_rx_config.h

