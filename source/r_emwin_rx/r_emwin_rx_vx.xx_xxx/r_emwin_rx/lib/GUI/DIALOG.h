/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2023  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V6.34 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only  be used  in accordance  with  a license  and should  not be  re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Software GmbH
Licensed to:              Renesas Electronics Europe GmbH, Arcadiastrasse 10, 40472 Duesseldorf, Germany
Licensed SEGGER software: emWin
License number:           GUI-00678
License model:            License and Service Agreement, signed December 16th, 2016, Amendment No. 1 signed May 16th, 2019 and Amendment No. 2, signed September 20th, 2021 by Carsten Jauch, Managing Director
License valid for:        RX (based on RX-V1, RX-V2 or RX-V3)
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2016-12-22 - 2023-12-31
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : Dialog.h
Purpose     : Dialog box include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef DIALOG_H
#define DIALOG_H

#include "WM.h"

#include "BUTTON.h"
#include "CALENDAR.h"
#include "CHECKBOX.h"
#include "CHOOSECOLOR.h"
#include "CHOOSEFILE.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "GAUGE.h"
#include "GRAPH.h"
#include "HEADER.h"
#include "ICONVIEW.h"
#include "IMAGE.h"
#include "KEYBOARD.h"
#include "KNOB.h"
#include "LISTBOX.h"
#include "LISTVIEW.h"
#include "LISTWHEEL.h"
#include "MENU.h"
#include "MOVIE.h"
#include "MULTIEDIT.h"
#include "MULTIPAGE.h"
#include "PROGBAR.h"
#include "QRCODE.h"
#include "RADIO.h"
#include "ROTARY.h"
#include "SCROLLBAR.h"
#include "SCROLLER.h"
#include "SLIDER.h"
#include "SPINBOX.h"
#include "SWIPELIST.h"
#include "SWITCH.h"
#include "TEXT.h"
#include "TICKER.h"
#include "TREEVIEW.h"
#include "WHEEL.h"

#if GUI_WINSUPPORT

#if defined(__cplusplus)
  extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       WINDOW API
*/
WM_HWIN   WINDOW_CreateEx         (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id, WM_CALLBACK * cb);
WM_HWIN   WINDOW_CreateUser       (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id, WM_CALLBACK * cb, int NumExtraBytes);
WM_HWIN   WINDOW_CreateIndirect   (const GUI_WIDGET_CREATE_INFO * pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK * cb);
GUI_COLOR WINDOW_GetBkColor       (WM_HWIN hObj);
GUI_COLOR WINDOW_GetDefaultBkColor(void);
int       WINDOW_GetUserData      (WM_HWIN hObj, void * pDest, int NumBytes);
void      WINDOW_SetBkColor       (WM_HWIN hObj, GUI_COLOR Color);
void      WINDOW_SetDefaultBkColor(GUI_COLOR Color);
int       WINDOW_SetUserData      (WM_HWIN hObj, const void * pSrc, int NumBytes);

void WINDOW_Callback(WM_MESSAGE * pMsg);

#if defined(__cplusplus)
  }
#endif

#endif  // GUI_WINSUPPORT
#endif  // DIALOG_H

/*************************** End of file ****************************/
