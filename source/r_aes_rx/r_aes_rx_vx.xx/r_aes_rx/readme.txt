
r_aes_rx
=======

Overview
--------------------------------------------------------------------------------
The r_aes_rx library is software library to operate AES cryptographic processing
with RX microcomputer.
FIPS PUB 197 ADVANCED ENCRYPTION STANDARD is for reference on the specifications
and standards related to the r_aes_rx library.

This library comes with a GCM library compatible with Galois/Counter Mode (GCM) 
that can be used in combination with the AES library.
AES library supports ECB and CBC modes as block cipher modes of operation.
GCM library supports GCM mode as block cipher modes of operation and provides
data authenticity and confidentiality.

There are two approaches to implementing the AES library: "processing performance
priority" and "size priority".
These configuration options can be found in "r_config\r_aes_rx_config.h".
An original copy of the configuration file is stored in "r_aes_rx\ref\r_aes_rx_config_reference.h".
User functions can be used by incorporating the r_gcm_driver_rx module at the same time.
Although the sample code of the user function body is provided, it can also be
implemented by user.


Features
--------
* Supports:
        -AES128-ECB
        -AES128-CBC
        -AES256-ECB
        -AES256-CBC
        -AES-GCM

File Structure
--------------
r_aes_rx
|   readme.txt
|   r_aes_rx_if.h
|
+---doc
|		en
|       	r20uw0068ej0200-aes.pdf
|       	r20an0044ej0108-rx-aes.pdf
|		ja
|       	r20uw0068jj0200-aes.pdf
|       	r20an0044jj0108-rx-aes.pdf
|
+---ref
|       r_aes_config_reference.h
|
+---src
		aes
			r_aes.h
			aes128.h
			aes128Cbc_big.c
			aes128Cbc_small.c
			aes128Ecb_big.c
			aes128Ecb_small.c
			aes256.h
			aes256Cbc_big.c
			aes256Cbc_small.c
			aes256Ecb_big.c
			aes256Ecb_small.c
			r_aes_development.h
			r_aes_version.c
			r_aesEcb.h
			r_aesSbox.h				
		gcm
			r_gcm.c
			r_gcm.h
			r_gcm_driver.c
			r_gcm_version.c
        r_mw_version.h
        r_stdint.h
   
r_config
    r_aes_config.h

