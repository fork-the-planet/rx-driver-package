
r_sha_rx
=======

Overview
--------------------------------------------------------------------------------
The r_sha_rx library is software library to calculate hash function of
SHA-1/SHA-256/SHA-384 with RX microcomputer.
FIPS PUB 180-4 SECURE HASH STANDARD is for reference on the specifications
and standards related to the r_sha_rx library.
The r_sha_rx library outputs the hash value (message digest) of SHA-1 (160bits),
SHA-256 (256bits), SHA-384 (384bits) with digital data as an input value.
There are two approaches to implementing a hash function: "priority in processing
performance" and "priority in size".
These configuration options can be found in "r_config\r_sha_rx_config.h".
An original copy of the configuration file is stored in "r_sha_rx\ref\r_sha_rx_config_reference.h".


Features
--------
* Supports:
        -SHA-1
        -SHA-256
        -SHA-384

File Structure
--------------
r_sha_rx
|   readme.txt
|   r_sha.h
|
+---doc
|	en
|           r20an0157ej0106-rx-sha.pdf
|           r20uw0101ej0200-sha.pdf
|	ja
|           r20an0157jj0106-rx-sha.pdf
|           r20uw0101jj0200-sha.pdf
|
+---ref
|       r_sha_config_reference.h
|
+---src
        r_mw_version.h
        r_sha_version.c
        r_stdint.h
        sha1.c
        sha1if.c
        sha256.c
        sha256if.c
        sha384if.c
        sha512.c
        shaif.h
   
r_config
    r_sha_config.h

