
rm_mcuboot
=========

Document Number
---------------
r01an7374ej0101
r01an7374jj0101

Version
-------
v1.01

Overview
--------
Provides MCUboot function for RX.
MCUboot verifies the image being updated.
If validation completes successfully, replaces the existing image with the update image in the specified update mode.
Validation of the boot image is performed regardless of whether it has been updated or not.
Support encrypted images in some update modes.

Features
--------
* Image updates can be performed in three modes (Overwrite Only, Overwrite Only Fast, Swap, Direct XIP).
* Signature verification of images to be updated can be performed using two methods (ECDSA, RSA).
* Two cryptographic processes (TSIP, tinycrypto) allow image updates using encrypted images.

Supported MCUs
--------------
* RX65N Group
* RX66N Group
* RX671 Group
* RX72M Group
* RX72N Group
* RX261 Group

Boards Tested On
----------------
* RSKRX65N-2MB
* RSKRX671
* RSKRX72M
* RSKRX72N
* EKRX261

Limitations
-----------
None

Peripherals Used Directly
-------------------------
* RX MCUboot FIT

Required Packages
-----------------
* r_bsp       V7.52
* r_flash_rx  V5.21
* r_tsip_rx   V1.21
* r_rsip_rx   V1.00

How to add to your project
--------------------------
This module must be added to each project in which it is used.
Renesas recommends using "Smart Configurator" described in (1) or (3).
However, "Smart Configurator" only supports some RX devices.
Please use the methods of (2) or (4) for unsupported RX devices.

(1) Adding the FIT module to your project using "Smart Configurator" in e2 studio
By using the "Smart Configurator" in e2 studio, 
the FIT module is automatically added to your project.
Refer to "Renesas e2 studio Smart Configurator User Guide (R20AN0451)" for details.

(2) Adding the FIT module to your project using "FIT Configurator" in e2 studio
By using the "FIT Configurator" in e2 studio,
the FIT module is automatically added to your project.
Refer to "Adding Firmware Integration Technology Modules to Projects (R01AN1723)" for details.

(3) Adding the FIT module to your project using "Smart Configurator" on CS+
By using the "Smart Configurator Standalone version" in CS+,
the FIT module is automatically added to your project.
Refer to "Renesas e2 studio Smart Configurator User Guide (R20AN0451)" for details.

(4) Adding the FIT module to your project in CS+
In CS+, please manually add the FIT module to your project.
Refer to "Adding Firmware Integration Technology Modules to CS+ Projects (R01AN1826)" for details.

Toolchain(s) Used
-----------------
* C/C++ Compiler for RX Family V3.07.00
* GCC for RX Family 8.3.0.202411
* IAR Embedded Workbench for Renesas RX 5.10.1

File Structure
--------------
rm_mcuboot
|   readme.txt
|   rm_mcuboot_if.h
|
+---doc
|   +-- en
|   |       r01an7374ej0101-rx-mcuboot.pdf
|   +-- ja
|           r01an7374jj0101-rx-mcuboot.pdf
|
\---src
    +---mcu-tools
    |   \---MCUboot
    |
    \---rm_mcuboot_port
        |   flash_map.c
        |   rm_mcuboot_port.c
        |
        +---ccrx
        |       abort.c
        |
        +---config
        |   +---mcuboot_config
        |   |       mcuboot_config.h
        |   |       mcuboot_logging.h
        |   |
        |   \---sysflash
        |           sysflash.h
        |
        +---crypto
        |       rsip_aes_ctr.h
        |       rsip_aes_kw.h
        |       rsip_ecdsa_p256.h
        |       rsip_image_ec256.c
        |       rsip_keys.c
        |       rsip_keys.h
        |       rsip_sha256.h
        |       tsip_aes_ctr.h
        |       tsip_aes_kw.h
        |       tsip_ecdsa_p256.h
        |       tsip_image_ec256.c
        |       tsip_image_rsa.c
        |       tsip_keys.c
        |       tsip_keys.h
        |       tsip_sha256.h
        |
        +---flash_map_backend
        |       flash_map_backend.h
        |
        \---os
                os_malloc.h

r_config
    rm_mcuboot_config.h