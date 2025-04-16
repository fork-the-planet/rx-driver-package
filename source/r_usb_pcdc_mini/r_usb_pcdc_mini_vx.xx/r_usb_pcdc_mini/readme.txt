PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_usb_pcdc_mini
=======================

Document Number 
---------------
R01AN2170EJ
R01AN2170JJ

Version
-------
v1.31


Overview
--------
USB Peripheral Communications Device Class Driver (PCDC)

Features
--------
The PCDC conforms to the abstract control model of the communication
device class specification (CDC) and enables communication with a USB Host.


Supported MCUs
--------------
* RX111 Group
* RX113 Group
* RX231 Group
* RX23W Group
* RX261 Group

Boards Tested On
----------------
* RSKRX111
* RSKRX113
* RSKRX231
* RSSKRX23W
* EK-RX261
 
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
* Renesas RX v.3.07.00
* GCC for Renesas RX 8.3.0.202411
* IAR C/C++ Compiler for Renesas version 5.10.1

File Structure
--------------
r_usb_pcdc_mini
|   readme.txt
|   r_usb_pcdc_mini_if.h
|
+---doc
|     \en
|     |   r01an2170ej0131_usb.pdf
|     \jp
|         r01an2170jj0131_usb.pdf
|
+---ref
|       r_usb_pcdc_mini_config_reference.h
|
+---utilities
|       CDC_Demo.inf
|
\---src
     |  r_usb_pcdc_driver.c
     |
     \---inc
             r_usb_pcdc.h

