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
File        : GUI_GIF_Private.h
Purpose     : Private header file for GUI_GIF... functions
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_GIF_PRIVATE_H
#define GUI_GIF_PRIVATE_H

#include "GUI_Private.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define MAX_NUM_LWZ_BITS 12

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/* Context structure */
typedef struct {
  /* Required for getting input */
  unsigned            NumBytesInBuffer;     /* Remaining bytes in buffer */
  const U8          * pBuffer;              /* Pointer into buffer for reading data */
  GUI_GET_DATA_FUNC * pfGetData;            /* Function pointer */
  void              * pParam;               /* Parameter pointer passed to function */
  U32                 Off;                  /* Data pointer */
  /* Decompression data */
  U8    aBuffer[258];                       /* Input buffer for data block */
  short aCode  [(1 << MAX_NUM_LWZ_BITS)];   /* This array stores the LZW codes for the compressed strings */
  U8    aPrefix[(1 << MAX_NUM_LWZ_BITS)];   /* Prefix character of the LZW code. */
  U8    aDecompBuffer[3000];                /* Decompression buffer. The higher the compression, the more bytes are needed in the buffer. */
  U8 *  sp;                                 /* Pointer into the decompression buffer */
  int   CurBit;
  int   LastBit;
  int   GetDone;
  int   LastByte;
  int   ReturnClear;
  int   CodeSize;
  int   SetCodeSize;
  int   MaxCode;
  int   MaxCodeSize;
  int   ClearCode;
  int   EndCode;
  int   FirstCode;
  int   OldCode;
  /* Palette buffer */
  GUI_COLOR aColorTable[256];
} GUI_GIF_CONTEXT;

typedef struct {
  int XPos;
  int YPos;
  int XSize;
  int YSize;
  int Flags;
  int NumColors;
} IMAGE_DESCRIPTOR;

/* Default parameter structure for reading data from memory */
typedef struct {
  const U8 * pFileData;
  U32   FileSize;
} GUI_GIF_PARAM;

typedef int  DRAW_FROM_DATABLOCK(GUI_GIF_CONTEXT * pContext, IMAGE_DESCRIPTOR * pDescriptor, int x0, int y0, int Transparency, int Disposal, int Num, int Denom);
typedef void CLEAR_UNUSED_PIXELS(int x0, int y0, IMAGE_DESCRIPTOR * pDescriptor, GUI_GIF_IMAGE_INFO * pInfo, int Num, int Denom);

/*********************************************************************
*
*       Private data
*
**********************************************************************
*/
extern const int GUI_GIF__aInterlaceOffset[4];
extern const int GUI_GIF__aInterlaceYPos[4];

/*********************************************************************
*
*       Interface
*
**********************************************************************
*/
int  GUI_GIF__ReadData(GUI_GIF_CONTEXT * pContext, unsigned NumBytes, const U8 ** ppData, unsigned StartOfFile);
int  GUI_GIF__GetData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off);
int  GUI_GIF__DrawFromFilePointer(GUI_GIF_CONTEXT * pContext, int x0, int y0, int Index, int Num, int Denom, DRAW_FROM_DATABLOCK pfDrawFromDataBlock, CLEAR_UNUSED_PIXELS pfClearUnusedPixels);
void GUI_GIF__InitLZW(GUI_GIF_CONTEXT * pContext, int InputCodeSize);
int  GUI_GIF__GetNextByte(GUI_GIF_CONTEXT * pContext);

#endif /* GUI_GIF_PRIVATE_H */
