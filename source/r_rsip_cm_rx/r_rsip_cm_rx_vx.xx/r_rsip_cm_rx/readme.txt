PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_rsip_cm_rx
=========

Document Number
---------------
R01AN7445JJ0100-RX-RSIP-CM-SECURITY
R01AN7445EJ0100-RX-RSIP-CM-SECURITY

Version
-------
v1.00

Overview
--------
The RSIP CM(Compatibility Mode) functions for Renesas MCUs.
RSIP CM supports AES, GCM, CCM, CMAC, SHA, ECC, Random number generate, Key management.

These configuration options can be found in "r_config\r_rsip_cm_rx_config.h". 


Features
--------
* Strongly Key Management.
* Hardware acceralator for AES, GCM, CCM, CMAC, SHA and ECC.
* Supports True Random Number Generating.

Supported MCUs
--------------
* RX261 Group

Boards Tested On
----------------
* RSKRX261

Limitations
-----------
None

Peripherals Used Directly
-------------------------
* Renesas Secure IP Compatibility Mode (RSIP CM)

Required Packages
-----------------
* r_bsp      V7.52

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
* GNU GNURX 8.03.00.202411
* IAR ICCRX 5.10.01

File Structure
--------------
r_rsip_cm_rx
|   readme.txt
|   r_rsip_cm_rx_if.h
|
+---doc
|   +---ja
|   |    r01an7445jj0100-rx-rsip-rx-security.pdf
|   +---en
|        r01an7445ej0100-rx-rsip-rx-security.pdf
|
+---src
    |
	+---mbedtls
	+---r_rsip_cm
        |   
        +---common
		|	+---hw_sce_common.h	
        +---src
		|	+---adaptors
		|	|	        r_sce_adapt.c
		|	+---primitive
		|	|	+---rx261
        |   |            hw_sce_p_func000.c
        |   |            hw_sce_p_func001.c
        |   |            hw_sce_p_func002.c
        |   |                   :				
		|	+---private
		|	|	+---inc
		|	|		   hw_sce_rx_private.h
		|	|		   r_rsip_rx261_iodefine.h	
        |   |		
		|	+---public
		|	|	+---inc
		|	|		   r_sce_if.h
		|   |
        +---hw_sce_aes_private.h
        +---hw_sce_ecc_private.h
        +---hw_sce_hash_private.h
        +---hw_sce_private.h
        +---hw_sce_rsa_private.h
        +---hw_sce_trng_private.h		
	+---r_rsip_cm_key_injection
        |   
        +---r_rsip_cm_key_injection.c	
            r_rsip_cm_key_injection.h			
	+---rm_psa_crypto
        |   
        +---inc	
        |      aes_alt.h	
        |      aes_vendor.h	
        |      asymmetric_vendor.h
        |      :
        +---aes_alt.c
        +---aes_alt_process.c		
        +---aes_vendor.c		
        +---   :		


r_config
    r_rsip_cm_rx_config.h