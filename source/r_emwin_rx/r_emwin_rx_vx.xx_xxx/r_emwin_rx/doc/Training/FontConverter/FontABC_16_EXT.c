/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Font converter for emWin version 3.18                       *
*        Compiled Mar 31 2011, 11:33:06                              *
*        (C) 1998 - 2010 Segger Microcontroller GmbH                 *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: 16.c                                                  *
* Font:        Arial                                                 *
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
SUA period:               2016-12-22 - 2022-12-31
Contact to extend SUA:    sales@segger.com
* Height:      16                                                    *
*                                                                    *
**********************************************************************
*                                                                    *
* Initial font height: 16                                            *
* Range disabled: 0000 - FFFF                                        *
* Character enabled:   0x41 (65)                                     *
* Character enabled:   0x42 (66)                                     *
* Character enabled:   0x43 (67)                                     *
*                                                                    *
**********************************************************************
*/

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

/* The following line needs to be included in any file selecting the
   font. A good place would be GUIConf.H
*/
extern GUI_CONST_STORAGE GUI_FONT GUI_Font16;

/* Start of unicode area <Basic Latin> */
GUI_CONST_STORAGE unsigned char acGUI_Font16_0041[ 20] = { /* code 0041, LATIN CAPITAL LETTER A */
  ____X___,________,
  ___X_X__,________,
  ___X_X__,________,
  ___X_X__,________,
  __X___X_,________,
  __X___X_,________,
  _XXXXXXX,________,
  _X_____X,________,
  X_______,X_______,
  X_______,X_______};

GUI_CONST_STORAGE unsigned char acGUI_Font16_0042[ 10] = { /* code 0042, LATIN CAPITAL LETTER B */
  XXXXXX__,
  X_____X_,
  X_____X_,
  X_____X_,
  XXXXXX__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acGUI_Font16_0043[ 10] = { /* code 0043, LATIN CAPITAL LETTER C */
  __XXX___,
  _X___X__,
  X_____X_,
  X_______,
  X_______,
  X_______,
  X_______,
  X_____X_,
  _X___X__,
  __XXX___};

GUI_CONST_STORAGE GUI_CHARINFO_EXT GUI_Font16_CharInfo[3] = {
   {   9,  10,   0,   3,   9, acGUI_Font16_0041 } /* code 0041, LATIN CAPITAL LETTER A */
  ,{   7,  10,   1,   3,   9, acGUI_Font16_0042 } /* code 0042, LATIN CAPITAL LETTER B */
  ,{   7,  10,   1,   3,   9, acGUI_Font16_0043 } /* code 0043, LATIN CAPITAL LETTER C */
};

GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_Font16_Prop1 = {
   0x0041 /* first character */
  ,0x0043 /* last character  */
  ,&GUI_Font16_CharInfo[  0] /* address of first character */
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0 /* pointer to next GUI_FONT_PROP_EXT */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font16 = {
   GUI_FONTTYPE_PROP_EXT /* type of font    */
  ,16 /* height of font  */
  ,16 /* space of font y */
  ,1 /* magnification x */
  ,1 /* magnification y */
  ,{&GUI_Font16_Prop1}
  ,13 /* Baseline */
  ,7 /* Height of lowercase characters */
  ,10 /* Height of capital characters */
};

