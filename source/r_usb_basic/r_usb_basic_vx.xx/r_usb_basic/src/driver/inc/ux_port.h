/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** USBX Component                                                        */
/**                                                                       */
/**   Port Specific                                                       */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  PORT SPECIFIC C INFORMATION                            RELEASE        */
/*                                                                        */
/*    ux_port.h                                          Cortex-M4/GNU    */
/*                                                           6.0          */
/*                                                                        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file contains data type definitions that make USBX function    */
/*    identically on a variety of different processor architectures.      */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/

#ifndef UX_PORT_H
 #define UX_PORT_H

/* Determine if the optional USBX user define file should be used.  */

 #ifdef UX_INCLUDE_USER_DEFINE_FILE

/* Yes, include the user defines in ux_user.h. The defines in this file may
 * alternately be defined on the command line.  */

  #include "ux_user.h"
 #endif

/* Include library header files.  */

 #include <stdio.h>
 #include <string.h>
 #include <stdint.h>
 #include "r_usb_basic_define.h"
 #include "r_usb_basic_config.h"

 #ifdef __cplusplus
extern "C" {
 #endif

 #if !defined(UX_STANDALONE)
  #include "tx_api.h"
 #else

/* VAR types used in UX,
 * if TX still used, expects tx_api.h included before include this.  */
  #if !defined(TX_API_H) && !defined(TX_PORT_H)

typedef void           VOID;
typedef char           CHAR;
typedef unsigned char  UCHAR;
typedef int            INT;
typedef unsigned int   UINT;
typedef long           LONG;
typedef unsigned long  ULONG;
typedef short          SHORT;
typedef unsigned short USHORT;
typedef uint64_t       ULONG64;

   #ifndef ALIGN_TYPE_DEFINED
    #define ALIGN_TYPE    ULONG
   #endif

  #endif
 #endif

/* CPU definition for X86 systems without preemptive timer function.
 * This will make USBX uses the controller for the timer. */

 #undef THREADX_X86_NO_PTIMER

/* For X86 systems, the define #define UX_USE_IO_INSTRUCTIONS should be used.  */

/* Define additional generic USBX types.  */

typedef long SLONG;

/*  Generic USBX Project constants follow.  */

 #ifndef UX_PERIODIC_RATE
  #define UX_PERIODIC_RATE                       1000
 #endif

 #ifndef UX_MAX_CLASS_DRIVER
  #define UX_MAX_CLASS_DRIVER                    2
 #endif

 #ifndef UX_MAX_SLAVE_CLASS_DRIVER
  #define UX_MAX_SLAVE_CLASS_DRIVER              2
 #endif

 #ifndef UX_MAX_HCD
  #define UX_MAX_HCD                             2
 #endif

 #ifndef UX_MAX_DEVICES
  #define UX_MAX_DEVICES                         8
 #endif

 #ifndef UX_MAX_ED
  #define UX_MAX_ED                              80
 #endif

 #ifndef UX_MAX_TD
  #define UX_MAX_TD                              32
 #endif

 #ifndef UX_MAX_ISO_TD
  #define UX_MAX_ISO_TD                          8
 #endif

 #ifndef UX_HOST_ENUM_THREAD_STACK_SIZE
  #define UX_HOST_ENUM_THREAD_STACK_SIZE         (2 * 1024)
 #endif

 #ifndef UX_THREAD_STACK_SIZE
  #define UX_THREAD_STACK_SIZE                   (1 * 1024)
 #endif

 #ifndef UX_THREAD_PRIORITY_ENUM
  #define UX_THREAD_PRIORITY_ENUM                20
 #endif

 #ifndef UX_THREAD_PRIORITY_CLASS
  #define UX_THREAD_PRIORITY_CLASS               20
 #endif

 #ifndef UX_THREAD_PRIORITY_KEYBOARD
  #define UX_THREAD_PRIORITY_KEYBOARD            20
 #endif

 #ifndef UX_THREAD_PRIORITY_HCD
  #define UX_THREAD_PRIORITY_HCD                 2
 #endif

 #ifndef UX_THREAD_PRIORITY_DCD
  #define UX_THREAD_PRIORITY_DCD                 2
 #endif

 #ifndef UX_NO_TIME_SLICE
  #define UX_NO_TIME_SLICE                       0
 #endif

 #ifndef UX_MAX_SLAVE_LUN
  #define UX_MAX_SLAVE_LUN                       2
 #endif

 #ifndef UX_MAX_HOST_LUN
  #define UX_MAX_HOST_LUN                        2
 #endif

 #ifndef UX_HOST_CLASS_STORAGE_MAX_MEDIA
  #define UX_HOST_CLASS_STORAGE_MAX_MEDIA        2
 #endif

 #ifndef UX_SLAVE_REQUEST_CONTROL_MAX_LENGTH
  #define UX_SLAVE_REQUEST_CONTROL_MAX_LENGTH    256
 #endif

 #ifndef UX_SLAVE_REQUEST_DATA_MAX_LENGTH
  #define UX_SLAVE_REQUEST_DATA_MAX_LENGTH       2048
 #endif

 #ifndef UX_USE_IO_INSTRUCTIONS

/* Don't use IO instructions if this define is not set.  Default to memory mapped.  */

  #define inpb(a)        *((uint8_t *) (a))
  #define inpw(a)        *((uint16_t *) (a))
  #define inpl(a)        *((uint32_t *) (a))
  #define outpb(a, b)    *((uint8_t *) (a))  = ((uint8_t) (b))
  #define outpw(a, b)    *((uint16_t *) (a)) = ((uint16_t) (b))
  #define outpl(a, b)    *((uint32_t *) (a)) = ((uint32_t) (b))
 #else

/* Define simple prototypes for non-memory mapped hardware access.  */

uint8_t  inpb(uint32_t);
uint16_t inpw(uint32_t);
uint32_t inpl(uint32_t);

void outpb(uint32_t, uint8_t);
void outpw(uint32_t, uint16_t);
void outpl(uint32_t, uint32_t);

 #endif

/* Define interrupt lockout constructs to protect the memory allocation/release which could happen
 * under ISR in the device stack.  */

 #define UX_INT_SAVE_AREA    unsigned int old_interrupt_posture;
 #define UX_DISABLE_INTS     old_interrupt_posture = tx_interrupt_control(TX_INT_DISABLE);
 #define UX_RESTORE_INTS     tx_interrupt_control(old_interrupt_posture);

/* Define the version ID of USBX.  This may be utilized by the application.  */

 #ifdef  UX_SYSTEM_INIT
CHAR _ux_version_id[] =
    "Copyright (c) Microsoft Corporation. All rights reserved. * USBX Cortex-M4/GNU Version 6.0 *";
 #else
extern CHAR _ux_version_id[];
 #endif

 #ifdef __cplusplus
}
 #endif

 #if (USB_CFG_MODE == USB_CFG_PERI)
  #define UX_DEVICE_SIDE_ONLY
 #endif

 #if (USB_CFG_MODE == USB_CFG_HOST)
  #define UX_HOST_SIDE_ONLY
 #endif

 #define UX_HOST_CLASS_HID_INTERRUPT_OUT_SUPPORT
 #define UX_DEVICE_CLASS_HID_INTERRUPT_OUT_SUPPORT
#endif
