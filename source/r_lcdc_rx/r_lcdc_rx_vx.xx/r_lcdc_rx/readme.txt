PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_lcdc_rx
=========

Document Number
---------------
R01AN1980JJ0202
R01AN1980EJ0202

Version
-------
v2.02

Overview
--------
This document describes the LCD module using firmware integration technology (FIT). This module uses the LCD controller/driver (LCDC) to display data on an LCD. Hereinafter this module is referred to as LCDC FIT module.

Features
--------
- The internal voltage boosting method, the capacitor split method, or the external resistance division method can be
selected for the LCD driver voltage generator.
- The display bias method can be selected from the 1/2 bias method, 1/3 bias method, or 1/4 bias method.
- The time slice of display can be selected from static, 2-time slice, 3-time slice, 4-time slice, or 8-time slice.
- The display waveform can be selected from waveform A or waveform B.
- The display data area can be selected from A-pattern, B-pattern, or the blinking. The display data area can be
switched.
- The blinking display with A-pattern and B-pattern can be achieved using the RTC periodic interrupt (PRD).
- The reference voltage, which is generated when operating the voltage boost circuit, can be selected from 16 steps
(contrast adjustment).

Supported MCUs
--------------
* RX113 Group
* RX23E-B Grop

Boards Tested On
----------------
* RSKRX113
* RSSKRX23E-B

Limitations
-----------
None

Peripherals Used Directly
-------------------------
* LCDC

Required Packages
-----------------
* r_bsp     v7.40

Toolchain(s) Used
-----------------
* Renesas RX v3.07.00
* GCC for Renesas RX 14.02.00.202511
* IAR C/C++ Compiler for Renesas RX version 5.20.1


File Structure
--------------
r_lcdc_rx
|   readme.txt
|   r_lcdc_rx_if.h
|
+---doc
|   +---en
|   |   r01an1980ej{VERSION_NUMBER}-rx-lcdc.pdf
|   |
|   +---ja
|       r01an1980jj{VERSION_NUMBER}-rx-lcdc.pdf
|
+---src
      r_lcdc_rx.c
      r_lcdc_rx_private.h

r_config
    r_lcdc_rx_config.h
