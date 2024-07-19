PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_sdsi_rx (SD Mode SDSI Driver)
=======================

Document Number 
---------------
R01AN3238EJ0204
R01AN3238JJ0204

Version
-------
v2.04

Overview
--------
This driver is a device driver to control the SD mode SDIO using SD Slave Interface (SDSI).

Features
--------
* SD slave interface which is compliant with the SDIO Card Specification Version 2.00
* Supports high-speed mode and default speed mode
* Supports block transfer mode and byte transfer mode
* Selectable from wide bus mode (4bit) or default bus mode (1bit)
* Supports SD mode. SPI mode is not supported.
* Supports CCCR (Card Common Control Register)-based operation
* Supports FBR (Function Basic Register)-based operation
* Supports access to CIS (Card Information Structure) 108 bytes
* Supports access to Function1 register (Function Unique register space)
* Supports direct transfer to MCUfs internal RAM
* Can call callback function when detecting SDSI interrupt

Supported MCUs
--------------
* RX65N Group

Boards Tested On
----------------
* RSK for RX65N
* RSK for RX65N_2MB
 
Limitations
-----------
None

Peripherals Used Directly
-------------------------
* SD Slave Interface (SDSI)

Required Packages
-----------------
* r_bsp    v7.41

How to add to your project
--------------------------
This module must be added to each project in which it is used.
Renesas recommends using "Smart Configurator" described in (1) or (2).
However, "Smart Configurator" only supports some RX devices.
Please use the methods of (3) for unsupported RX devices.

(1)	Adding the FIT module to your project using "Smart Configurator" in e2 studio
By using the "Smart Configurator" in e2 studio, 
the FIT module is automatically added to your project.
Refer to "Renesas e2 studio Smart Configurator User Guide (R20AN0451)" for details.

(2)	Adding the FIT module to your project using "Smart Configurator" on CS+
By using the "Smart Configurator Standalone version" in CS+,
the FIT module is automatically added to your project.
Refer to "Renesas e2 studio Smart Configurator User Guide (R20AN0451)" for details.

(3)	Adding the FIT module to your project in CS+
In CS+, please manually add the FIT module to your project.
Refer to "Adding Firmware Integration Technology Modules to CS+ Projects (R01AN1826)" for details.

Toolchain(s) Used
-----------------
* Renesas RX v3.05
* GCC for Renesas RX v8.3.0.202305
* IAR C/C++ Compiler for Renesas RX v4.20.3

File Structure
--------------
r_sdsi_rx
|   r_sdsi_rx_if.h
|   readme.txt
|
+---doc
|   |
|   +---en
|   |       r01an3238ej0204-rx-communication.pdf
|   +---ja
|           r01an3238jj0204-rx-communication.pdf
|
+---src
    |   r_sdsi_rx.c
    |   r_sdsi_rx_private.h
    |
    +---targets
        |
        +---rx65n
                r_sdsi_dev.c
                r_sdsi_register.c
                r_sdsi_rx_target.h

r_config
    r_sdsi_rx_config.h

