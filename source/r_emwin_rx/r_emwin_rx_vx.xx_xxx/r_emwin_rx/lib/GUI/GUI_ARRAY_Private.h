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
File        : GUI_ARRAY_Private.h
Purpose     : Private array handling routines, should be used only
              from within GUI_ARRAY... routines!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_ARRAY_PRIVATE_H
#define GUI_ARRAY_PRIVATE_H

#include "GUI_Private.h"
#include "WM_Intern.h"
#include "GUI_ARRAY.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private types
*
**********************************************************************
*/
typedef struct {
  U16 NumItems;
  WM_HMEM haHandle;   /* Handle to buffer holding handles */
} GUI_ARRAY_OBJ;

/*********************************************************************
*
*       Private functions
*
**********************************************************************
*/
WM_HMEM GUI_ARRAY__GethItem      (const GUI_ARRAY_OBJ * pThis, unsigned int Index);
void  * GUI_ARRAY__GetpItem      (const GUI_ARRAY_OBJ * pThis, unsigned int Index);
void  * GUI_ARRAY__GetpItemLocked(const GUI_ARRAY_OBJ * pThis, unsigned int Index);
int     GUI_ARRAY__SethItem      (      GUI_ARRAY_OBJ * pThis, unsigned int Index, WM_HMEM hItem);

#endif /* GUI_WINSUPPORT */

#endif /* GUI_ARRAY_PRIVATE_H */

/*************************** End of file ****************************/
