PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_s2_rx
=========

Document Number
---------------
R20AN0037JJ0306_RX_S2
R20AN0037EJ0306_RX_S2

Version
-------
v3.06

Overview
--------
The original ADPCM codec for encode/decode (S2).
S2 provides encode/decode function for the sound playback and sound record method. 
The sound playback needs D/A or PWM,  the sound record needs A/D. Please refer to 
the "R20AN0291JJxxxx_RX_S2/R20AN0291EJxxxx_RX_S2" too.

These configuration options can be found in "r_config\r_s2_rx_config.h". 


Features
--------
* S2 codec can compress raw-audio data to 1/4.
* S2 is optimized using RX assembler for performance.
* S2 provides the tools that convert wave format to original ADPCM format.

Supported MCUs
--------------
* RX family

Boards Tested On
----------------
* RSKRX71M
* RSKRX64M
* RSKRX63N
* RSKRX62N
* RSKRX610
* RSKRX231
* RSKRX210
* RSKRX113
* RSKRX111
* RSKRX65N

Limitations
-----------
None

Peripherals Used Directly
-------------------------
None

Required Packages
-----------------
None

How to add to your project
--------------------------
Please refer to the Adding Firmware Integration Technology Modules to Projects.
"r01an1723ju0111_rx.pdf/r01an1826jj0102_rx.pdf(R20AN0037JJ0306_RX_S2)"
"r01an1723eu0111_rx.pdf/r01an1826eu0102_rx.pdf(R20AN0037EJ0306_RX_S2)".

Toolchain(s) Used
-----------------
* Renesas RXC 3.07.00

File Structure
--------------
r_s2_rx
|   readme.txt
|   r_adpcm.h
|
+---doc
|   |
|   +---ja
|   |     r20an0037jj0306_rx_s2.pdf
|   |     r20uw0079jj0100_s2.pdf
|   |     r21an0002jj0100_adpcm_tool.pdf
|   +---en
|         r20an0037ej0306_rx_s2.pdf
|         r20uw0079ej0100_s2.pdf
|         r21an0002ej0100_adpcm_tool.pdf
|
+---lib
|       r_mw_version.h
|       r_stdint.h
|       s2_rx200_big_rtune.lib
|       s2_rx200_little_rtune.lib
|       s2_rx600_big_rtune.lib
|       s2_rx600_little_rtune.lib
|
+---make_lib
|       make_lib.zip
|
|
+---tool
    |
    +---adpcm_tool
            ADPCM.exe

r_config
    r_s2_rx_config.h
