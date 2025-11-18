PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_rsip_protected_rx
=========

Document Number
---------------
R20AN0748JJ0200-RX-RSIP-SECURITY
R20AN0748EJ0200-RX-RSIP-SECURITY

Version
-------
v2.00

Overview
--------
The RSIP(Renesas Secure IP) functions for Renesas MCUs.
RSIP supports AES, GCM, CCM, CMAC, SHA, ECC, Random number generate, Key management.
Support secure boot and secure firmware update sequence APIs.

These configuration options can be found in "r_config\r_rsip_protected_rx_config.h". 


Features
--------
* Strongly Key Management.
* Hardware acceralator for AES, GCM, CCM, CMAC, SHA and ECC.
* Supports True Random Number Generating.
* Supports secure boot and secure firmware update.

Supported MCUs
--------------
* RX261 Group

Boards Tested On
----------------
* EnvisionKitRX261

Limitations
-----------
None

Peripherals Used Directly
-------------------------
* Renesas Secure IP (RSIP)

Required Packages
-----------------
* r_bsp      V7.51

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
* Renesas RXC 3.07.00
* GNU GNURX 8.03.00.202405
* IAR ICCRX 5.10.01

File Structure
--------------
r_rsip_protected_rx
|   readme.txt
|   r_rsip_protected_rx_if.h
|
+---doc
|   +---ja
|   |    r20an0748jj0200-rx-rsip-security.pdf
|   +---en
|        r20an0748ej0200-rx-rsip-security.pdf
|
+---src
    |
    +---inc
    |   |
    |   +---rx261
    |          r_rsip.h
    |          r_rsip_cfg.h
    |
    +---primitive
    |   |
    |   +---common
    |   |      r_rsip_err.h
    |   |      r_rsip_util.h
    |   |
    |   +---rx261
    |          r_rsip_rx261_iodefine.h
    |          r_rsip_primitive.h
    |          r_rsip_data.c
    |          s_flash.c
    |          r_rsip_rx_function001.c
    |          r_rsip_rx_function002.c
    |          r_rsip_rx_function003.c
    |          :
    |
    +---private
    |   |
    |   +---common
    |   |      r_rsip_private.c
    |   |      r_rsip_private.h
    |   |
    |   +---rx261
    |          r_rsip_hal.c
    |          r_rsip_wrapper.c
    |          r_rsip_wrapper.h
    |
    +---public
        |
        +---common
        |      r_rsip.c
        |      r_rsip_aes.c
        |      r_rsip_ecc.c
        |      r_rsip_kdf.c
        |      r_rsip_otf.c
        |      r_rsip_pki.c
        |      r_rsip_rsa.c
        |      r_rsip_sha.c
        |      r_rsip_public.h
        |
        +---rx261
               r_rsip_fwup.c
               r_rsip_key_injection.c
               r_rsip_rx.c

r_config
    r_rsip_protected_rx_config.h

