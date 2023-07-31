PLEASE REFER TO THE APPLICATION NOTE FOR THIS DRIVER FOR MORE INFORMATION

r_lpt_rx
========

Overview
--------------------------------------------------------------------------------
The r_lpt_rx module generates an exit signal from software standby mode using the low power timer (LPT).
This driver initializes the LPT module, starts and stops the timer, and disables the LPT module.
To change the period, disable the LPT module once, and initialize the LPT module with the new period. 
The code size can be reduced by removing code for parameter checking. 
These configuration options can be found in "r_config\r_lpt_rx_config.h". 

Features
--------
* The LPT fit module provides a method to generate a periodic exit signal from software standby mode.

File Structure
--------------
r_lpt_rx
|   readme.txt
|   r_lpt_rx_if.h
|
+---doc
|    +---en
|    |    |
|    |    +---r01an2571ej{VERSION_NUMBER}-rx-timer.pdf
|    |
|    +---ja
|         |
|         +---r01an2571jj{VERSION_NUMBER}-rx-timer.pdf
|
+---src
    |   r_lpt_rx.c
    |   r_lpt_rx_private.h
    |   r_lpt_rx_platform.h
    |
    +---targets
        |
        +---rx113
        |      r_lpt_rx113.c
        |      r_lpt_rx113_private.h
        |
        +---rx130
        |      r_lpt_rx130.c
        |      r_lpt_rx130_private.h
        |
        +---rx140
        |      r_lpt_rx140.c
        |      r_lpt_rx140_private.h
        |
        +---rx230
        |      r_lpt_rx230.c
        |      r_lpt_rx230_private.h
        |
        +---rx231
        |      r_lpt_rx231.c
        |      r_lpt_rx231_private.h
        |
        +---rx23w
        |      r_lpt_rx23w.c
        |      r_lpt_rx23w_private.h
        |
        +---rx23e-b
               r_lpt_rx23e-b.c
               r_lpt_rx23e-b_private.h

r_config
    r_lpt_rx_config.h

