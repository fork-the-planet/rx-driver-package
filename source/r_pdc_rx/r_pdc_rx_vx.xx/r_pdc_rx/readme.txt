PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_pdc_rx
========

Document Number
---------------
R01AN3167EJ0207-rx-pdc (English version)
R01AN3167JJ0207-rx-pdc (Japanese version)

Version
-------
v2.07

Overview
--------
The PDC fit module provides a method to capture the parallel data output from the device including image sensors.
The source was tested on the board RSKRX64M and RSKRX71M, RSKRX65N, RSKRX65N_2MB, RSKRX72M, RSKRX66N, RSKRX72N, IDE e2studio with RX compiler
The driver includes API functions to initialize PDC, Control of PDC module, registrasion of the callback function etc..
All configuration options can be found in "r_config\r_pdc_rx_config.h".
An original copy of the configuration file is stored in "r_pdc_rx\ref\r_pdc_rx_config_reference.h".

Features
--------
* Capturing parallel data of any vertical, horizontal directions.

Supported MCUs
--------------
* RX64M Group
* RX71M Group
* RX651 Group
* RX65N Group
* RX72M Group
* RX66N Group
* RX72N Group

Boards Tested On
----------------
* RSKRX64M
* RSKRX71M
* RSKRX65N
* RSKRX65N_2MB
* RSKRX72M
* RSKRX72N

Limitations
-----------
* None

Peripherals Used Directly
-------------------------
* Parallel Data Capture Unit (PDC)

Required Packages
-----------------
* r_bsp

How to add to your project
--------------------------
* Add source foler r_pdc_rx to your project.
* Add an include path to the 'r_pdc_rx' directory.
* Copy the reference configuration file 'r_pdc_rx_config_reference.h' to your
  project and rename it r_pdc_rx_config.h.
* Configure middleware for your system through just copied r_pdc_rx_config.h.
* Add a #include for r_pdc_rx_if.h(It is also r_pdc_<mcu>.h)
  to any source files that need to use the API
  functions.

NOTE : <mcu> is RX famiry Group name.  (For example, rx64m)


Toolchain(s) Used
-----------------
* Renesas RX v3.07.00
* GCC for Renesas RX 8.3.0.202411
* IAR C/C++ Compiler for Renesas RX 5.10.1

File Structure
--------------
r_pdc_rx
|       readme.txt
|       r_pdc_rx_if.h
|
+---doc
|   |
|   +---en
|   |   r01an3167ej0207-rx-pdc.pdf
|   |
|   \---ja
|       r01an3167jj0207-rx-pdc.pdf
|
\---src
        r_pdc_rx.c
        r_pdc_rx_private.h
