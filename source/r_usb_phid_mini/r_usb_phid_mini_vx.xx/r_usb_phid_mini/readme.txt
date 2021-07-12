PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_usb_phid_mini
=======================

Document Number 
---------------
R01AN2171EJ
R01AN2171JJ

Version
-------
v1.20

Overview
--------
USB Peripheral Human Interface Device Class Driver (PHID)

Features
--------
USB peripheral HID class driver conforms to the USB HID class specification 
and implements communication with HID devices.


Supported MCUs
--------------
* RX111 Group
* RX113 Group
* RX231 Group
* RX23W Group

Boards Tested On
----------------
* RSKRX111
* RSKRX113
* RSKRX231
* RSSKRX23W
 
Limitations
-----------

Peripherals Used Directly
-------------------------


Required Packages
-----------------
* r_bsp
* r_usb_basic_mini

How to add to your project
--------------------------

Toolchain(s) Used
-----------------
* Renesas RX v.3.02.00
* GCC for Renesas RX 8.3.0.201904
* IAR C/C++ Compiler for Renesas version 4.14.1

File Structure
--------------
r_usb_phid_mini
|   readme.txt
|   r_usb_phid_mini_if.h
|
+---doc
|     \en
|     |   r01an2171ej0120_usb.pdf
|     \jp
|         r01an2171jj0120_usb.pdf
|
+---ref
|       r_usb_phid_mini_config_reference.h
|
\---src
     |  r_usb_phid_driver.c
     |
     \---inc
             r_usb_phid.h

