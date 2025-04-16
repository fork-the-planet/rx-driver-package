
r_rsa_rx
=======

Overview
--------------------------------------------------------------------------------
The RSA library is a software library for performing RSA cryptographic processing
with RX microcomputer.
PKCS #1 v2.1 RSA CRYPTOGRAPHY STANDARD is for reference on the specifications
and standards related to this library.

RSA is a public key cryptographic algorithm.
This library can perform RSA signature generation (RSASSA-PKCS1 V1_5), 
RSA signature verification (RSASSA-PKCS1 V1_5).

There is User function that is called R_rsa_if_hash.
This function that defines HASH function can be used by incorporating the r_rsa_driver_rx
module at the same time.
Although the sample code of the user function body is provided, it can also be
implemented by the user.


Features
--------
* Supports:
        -SIGNATURE_GEN_PKCS
        -SIGNATURE_VERI_PKCS
        -MOD_EXP

File Structure
--------------
r_rsa_rx
|   readme.txt
|   r_rsa.h
|
+---doc
|	en
|           r20uw0115ej0200-rsa.pdf
|           r20an0292ej0105-rx-rsa.pdf
|	ja
|           r20uw0115jj0200-rsa.pdf
|           r20an0292jj0105-rx-rsa.pdf
|
+---ref
|       r_rsa_config_reference.h
|
+---src
        mc_lib.c
        mc_lib.h
        r_mw_version.h
        r_rsa_version.c
        r_sample_rsa_if.c
        r_stdint.h
        rsa_api.c
        rsa_internal_header.h
   
r_config
    r_rsa_config.h

