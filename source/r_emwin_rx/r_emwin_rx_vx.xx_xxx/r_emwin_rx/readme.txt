PLEASE REFER TO THE APPLICATION NOTE FOR THIS MIDDLEWARE FOR MORE INFORMATION

r_emwin_rx
=========

Overview
--------
emWin is designed to provide an efficient, processor- and display controller-independent graphical user interface for 
any application that operates with a graphical display. It is compatible with single-task and multitask environments, 
with a proprietary operating system or with any commercial RTOS. emWin is shipped as C source code. It may be adapted 
to any size physical and virtual display with any display controller and CPU.

emWin FIT module provides above features as library files to be used in RX MCU. This module can be implemented with 
using Smart Configurator and QE for Display. Then the dependent modules can also be implemented simultaneously. In 
order to implement this module manually, the configuration options need to be modified which is found in 
"r_config\r_emwin_rx_config.h". 


Features
--------
* Provide emWin features.
* Display graphics to LCD.
* Enable touch panel functions.

File Structure
--------------
r_config
    r_emwin_rx_config.h

r_emwin_rx
|   readme.txt
|   r_emwin_rx_if.h
|
+---doc
|   +---emWin_doc
|   |       AN03002_Custom_Widget_Type.pdf
|   |       emWin_ExampleApplications.html
|   |       emWin_UserGuideAndReferenceManual.html
|   |       HowTo_RunSimulationUnderVS2015OrLater.txt
|   |       License_GUI-00678.txt
|   |       Release.html
|   |       UM03001_emWin.pdf
|   |
|   +---en
|   |       r01an7047ej0121-rx-emwin.pdf
|   |
|   +---ja
|   |       r01an7047jj0121-rx-emwin.pdf
|   |
|   +---Training
|       |   emWin_Training.pdf
|       |
|       +---AlphaBlending
|       |       MainTask_AlphaBlending.c
|       |
|       +---AnimatedSprites
|       |       MainTask_AnimatedCursor.c
|       |       MainTask_AnimatedSprites.c
|       |
|       +---AntiAliasing
|       |       MainTask_AA.c
|       |       MainTask_HiResAA.c
|       |
|       +---BitmapConverter
|       |       ArrowRight_40x40.bmp
|       |       Car_286x250.png
|       |       Car_320x240.bmp
|       |       ColorCircle_120x120_24bpp.bmp
|       |       ColorCircle_240x240_24bpp.bmp
|       |       Garden_100x100.bmp
|       |       Garden_100x100_DTA.c
|       |       Garden_100x100_DTA.dta
|       |       Gradient_32x32.gif
|       |       Printer_200x200_ARGB.png
|       |       Printer_50x50_ARGB.png
|       |       Sunset_150x100.jpg
|       |       Symbol_300x300.bmp
|       |       Toucan_162x150.png
|       |
|       +---Colors
|       |       MainTask_ColorManagement.c
|       |
|       +---Configuration
|       |       Device1_180x100_at_25_10.bmp
|       |       Device_180x100_at_25_10.bmp
|       |       GUIConf_SleepMode.c
|       |       LCDConf_CustomPaletteMode.c
|       |       LCDConf_Min.c
|       |       LCDConf_MultiLayer.c
|       |       MainTask_MultiLayer.c
|       |       SIMConf_CustomBitmapView.c
|       |       SIMConf_CustomBitmapViewMag.c
|       |       SIMConf_MultiLayer.c
|       |       SIMConf_WindowView.c
|       |
|       +---Core
|       |       MainTask_ArabicFont.c
|       |       MainTask_Basics.c
|       |       MainTask_QRCode.c
|       |       PatternFileForArabicFont.txt
|       |
|       +---FontConverter
|       |       Chinese_C.c
|       |       Chinese_Unicode.txt
|       |       Chinese_UTF8.txt
|       |       FontABC_16_EXT.c
|       |       FontABC_16_EXT_XBF.c
|       |       FontABC_16_EXT_XBF.xbf
|       |       FontASCII_16_EXT_SIF.sif
|       |       FontASCII_16_EXT_XBF.c
|       |       FontASCII_16_EXT_XBF.xbf
|       |       FontChinese_30_EXT.c
|       |       FontChinese_30_EXT_XBF.c
|       |       FontChinese_30_EXT_XBF.xbf
|       |       GetData_Bin2C.c
|       |       GetData_XBF.c
|       |
|       +---GUIBuilder
|       |       Application.zip
|       |       CatsMovie.gif
|       |       Circle_40x40_GIF.gif
|       |       CustomerDLG.c
|       |       FramewinDLG.c
|       |       GUIBuilderDLG.c
|       |       MainTask.c
|       |       SmileyMovie.gif
|       |       WindowDLG.c
|       |
|       +---ImageFiles
|       |       GetData_0.c
|       |       GetData_1.c
|       |       MainTask_DrawingImageFile.c
|       |
|       +---LanguageResources
|       |       GUI_LANG_CSV_Ger_Eng.csv
|       |       GUI_LANG_CSV_Ger_Eng.txt
|       |       MainTask_LanguageResource.c
|       |       MainTask_MultiLanguageDialog.c
|       |
|       +---MemoryDevices
|       |       MainTask_MemDevAnimation.c
|       |       MainTask_MemDevFading.c
|       |       MainTask_MemDevImageContainerPNG.c
|       |       MainTask_MemDevRotation.c
|       |       MainTask_MemDevTransparency.c
|       |       MainTask_NestedModal.c
|       |
|       +---Skinning
|       |       MainTask_ScrollBarSkin.c
|       |
|       +---VNC-Server
|       |       MainTask_VNC_Connection.c
|       |
|       +---WidgetLibrary
|       |       MainTask_CreatingWidgets.c
|       |       MainTask_Initialization.c
|       |       MainTask_OverwritingCallback.c
|       |       MainTask_OwnerDraw.c
|       |       MainTask_TransparentWidget.c
|       |
|       +---WM
|               MainTask_WM.c
|               MainTask_WM_Invalidating.c
|               MainTask_WM_MotionMoveContent.c
|               MainTask_WM_MotionMoveWindow.c
|               MainTask_WM_Tiling.c
|               MainTask_WM_Timer.c
|               MainTask_WM_UserData.c
|
+---lib
|   +---Config
|   |       APPW_X_NoFS.c
|   |       GUIConf.c
|   |       GUIConf.h
|   |       GUI_X_Ex.c
|   |       LCDConf.h
|   |       LCDConf_glcdc_if.c
|   |       LCDConf_spi_if.c
|   |       LCDConf_user_if.c
|   |       PIDConf.c
|   |       PIDConf.h
|   |
|   +---GUI
|           AppWizard.h
|           BUTTON.h
|           BUTTON_Private.h
|           CALENDAR.h
|           CHECKBOX.h
|           CHECKBOX_Private.h
|           CHOOSECOLOR.h
|           CHOOSEFILE.h
|           DIALOG.h
|           DIALOG_Type.h
|           DROPDOWN.h
|           DROPDOWN_Private.h
|           EDIT.h
|           EDIT_Private.h
|           emWinLib_RXv1_CCRX.lib
|           emWinLib_RXv1_IAR.a
|           emWinLib_RXv2_CCRX.lib
|           emWinLib_RXv2_IAR.a
|           emWinLib_RXv3_CCRX_d.lib
|           emWinLib_RXv3_CCRX_s.lib
|           emWinLib_RXv3_IAR_d.a
|           emWinLib_RXv3_IAR_s.a
|           FRAMEWIN.h
|           FRAMEWIN_Private.h
|           GAUGE.h
|           GAUGE_Private.h
|           Global.h
|           GRAPH.h
|           GRAPH_Private.h
|           GUI.h
|           GUIDRV_FlexColor.h
|           GUIDRV_FlexColor_Private.h
|           GUIDRV_Lin.h
|           GUIDRV_Null.h
|           GUIDRV_TemplateI.h
|           GUI_ARRAY.h
|           GUI_ARRAY_Private.h
|           GUI_BMP_Private.h
|           GUI_ConfDefaults.h
|           GUI_Debug.h
|           GUI_FontIntern.h
|           GUI_GCache_Private.h
|           GUI_GIF_Private.h
|           GUI_HOOK.h
|           GUI_JPEG_Private.h
|           GUI_Private.h
|           GUI_SetOrientation.h
|           GUI_SetOrientationCX.h
|           GUI_SPRITE_Private.h
|           GUI_SPY_Private.h
|           GUI_Type.h
|           GUI_Version.h
|           GUI_VNC.h
|           GUI__BiDi2_Brackets_800.h
|           GUI__BiDi2_Types_800.h
|           HEADER.h
|           HEADER_Private.h
|           ICONVIEW.h
|           ICONVIEW_Private.h
|           IMAGE.h
|           IMAGE_Private.h
|           IP_FS.h
|           KEYBOARD.h
|           KEYBOARD_Private.h
|           KNOB.h
|           KNOB_Private.h
|           LCD.h
|           LCD_ConfDefaults.h
|           LCD_Private.h
|           LCD_Protected.h
|           LCD_SIM.h
|           libemWinLib_RXv1_GCC.a
|           libemWinLib_RXv2_GCC.a
|           libemWinLib_RXv3_GCC.a
|           LISTBOX.h
|           LISTBOX_Private.h
|           LISTVIEW.h
|           LISTVIEW_Private.h
|           LISTWHEEL.h
|           LISTWHEEL_Private.h
|           MENU.h
|           MENU_Private.h
|           MESSAGEBOX.h
|           MOVIE.h
|           MOVIE_Private.h
|           MULTIEDIT.h
|           MULTIEDIT_Private.h
|           MULTIPAGE.h
|           MULTIPAGE_Private.h
|           PROGBAR.h
|           PROGBAR_Private.h
|           QRCODE.h
|           QRCODE_Private.h
|           RADIO.h
|           RADIO_Private.h
|           ROTARY.h
|           ROTARY_Private.h
|           SCROLLBAR.h
|           SCROLLBAR_Private.h
|           SCROLLER.h
|           SCROLLER_Private.h
|           SEGGER.h
|           SLIDER.h
|           SLIDER_Private.h
|           SPINBOX.h
|           SPINBOX_Private.h
|           SWIPELIST.h
|           SWIPELIST_Private.h
|           SWITCH.h
|           SWITCH_Private.h
|           TEXT.h
|           TEXT_Private.h
|           TICKER.h
|           TICKER_Private.h
|           TREEVIEW.h
|           TREEVIEW_Private.h
|           WHEEL.h
|           WHEEL_Private.h
|           WIDGET.h
|           WIDGET_ID.h
|           WINDOW_Private.h
|           WM.h
|           WM_GUI.h
|           WM_Intern.h
|
+---src
|       r_emwin_rx_if.c
|       r_emwin_rx_pid_iic_if.c
|       r_emwin_rx_pid_spi_if.c
|       r_emwin_rx_pid_user_if.c
|       r_emwin_rx_private.h
|
+---tool
        AppWizardRenesas_V140f_634g_Install.exe
        Bin2C.exe
        BmpCvtCL_V634_Install.exe
        BmpCvt_V634_Install.exe
        emVNC_V634_Install.exe
        emWinPlayer.exe
        emWinSPY.exe
        emWinSPY_V634_Install.exe
        emWinView_V634c_Install.exe
        GUIBuilder.exe
        JPEG2Movie.exe
        License.txt
        MakeMovie_V634_Install.exe
        SetupFontCvt_V634.exe
        U2C.exe
