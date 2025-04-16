PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_usb_pmsc
=======================

Document Number 
---------------
R01AN2029EJ
R01AN2029JJ

Version
-------
v1.44

Overview
--------
USB Peripheral Mass Storage Class Driver (PMSC)

Features
--------
The USB Peripheral Mass Storage lass driver comprises a USB Mass Storage class 
bulk-only transport (BOT) protocol. When combined with a USB peripheral control
driver and storage device driver, it enables communication with a USB host as 
a BOT-compatible storage device.


Supported MCUs
--------------
* RX64M Group
* RX71M Group
* RX65N Group
* RX66T Group
* RX72T Group
* RX72M Group
* RX72N Group
* RX66N Group
* RX671 Group


Boards Tested On
----------------
* RSKRX64M
* RSKRX71M
* RSKRX65N
* RSKRX65N_2MB
* RSKRX72T
* RSKRX72M
* RSKRX72N
* RSKRX671

 
Limitations
-----------

Peripherals Used Directly
-------------------------


Required Packages
-----------------
* r_bsp
* r_usb_basic

How to add to your project
--------------------------

Toolchain(s) Used
-----------------
* Renesas RX v.3.07.00
* GCC for Renesas RX 8.3.0.202411
* IAR C/C++ Compiler for Renesas version 5.10.1

File Structure
--------------
r_usb_pmsc
|   readme.txt
|   r_usb_pmsc_if.h
|   r_media_driver_if.h
|
+---doc
|     \en
|     |   r01an2029ej0144_usb.pdf
|     \jp
|         r01an2029jj0144_usb.pdf
|
+---ref
|       r_usb_pmsc_config_reference.h
|
\---src
     |  r_media_driver_api.c
     |  r_usb_atapi_driver.c
     |  r_usb_pmsc_driver.c
     |
     \---inc
             r_usb_patapi.h
             r_usb_pmsc.h
