# Microsoft Developer Studio Project File - Name="bender" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=bender - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bender.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bender.mak" CFG="bender - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bender - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "bender - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bender - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 hasp_windows_104780.lib libhasp_cpp_windows_mtd_msc6.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"mfc42.lib" /nodefaultlib:"mfcs42.lib" /nodefaultlib:"msvcrt.lib"
# SUBTRACT LINK32 /incremental:yes /debug /nodefaultlib

!ELSEIF  "$(CFG)" == "bender - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 hasp_windows_104780.lib libhasp_cpp_windows_mtd_msc6_d.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"mfc42.lib" /nodefaultlib:"mfcs42.lib" /nodefaultlib:"msvcrt.lib" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "bender - Win32 Release"
# Name "bender - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "NEST_CPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg_Nest.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_NestNum.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_NestSave.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_NestSize.cpp
# End Source File
# End Group
# Begin Group "OCX_CALSS_CPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\adodc.cpp
# End Source File
# Begin Source File

SOURCE=.\captioninfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ClrButton.cpp
# End Source File
# Begin Source File

SOURCE=.\displayctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Dmcwin.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDoubleClick.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\gridcad.cpp
# End Source File
# Begin Source File

SOURCE=.\lamp.cpp
# End Source File
# Begin Source File

SOURCE=.\planinfo.cpp
# End Source File
# End Group
# Begin Group "GRID_CPP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\grid\ComboGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\grid\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\grid\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\grid\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\grid\InPlaceList.cpp
# End Source File
# Begin Source File

SOURCE=.\grid\TitleTip.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\2DDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\AdjustDouble.cpp
# End Source File
# Begin Source File

SOURCE=.\bender.cpp
# End Source File
# Begin Source File

SOURCE=.\bender.rc
# End Source File
# Begin Source File

SOURCE=.\benderDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\btnctl.cpp
# End Source File
# Begin Source File

SOURCE=.\CTest.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_affirm.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_AfxMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_BackUp.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_bottero.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Calculator.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_config.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CuttingSize.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_DrawCad.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_galil.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_glass.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_hand.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Home.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_KeyChar.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_KeyNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_light.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Loading.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_machine.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_MachineCase.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_motion.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Oiling.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_pass.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_path2.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_save.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_scan.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SheetGlass.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_ShowExtra.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_sn.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_super.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_ustLimit.cpp
# End Source File
# Begin Source File

SOURCE=.\excel.cpp
# End Source File
# Begin Source File

SOURCE=.\IOExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\mscomm.cpp
# End Source File
# Begin Source File

SOURCE=.\OrangeListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintView.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadGcode.cpp
# End Source File
# Begin Source File

SOURCE=.\RectEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RectOptDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetXY.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UniButton.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "NEST"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dlg_Nest.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_NestNum.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_NestSave.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_NestSize.h
# End Source File
# End Group
# Begin Group "OCX_CLASS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\2DWnd.h
# End Source File
# Begin Source File

SOURCE=.\adodc.h
# End Source File
# Begin Source File

SOURCE=.\Alarm\AlarmDll.h
# End Source File
# Begin Source File

SOURCE=.\CadBase.h
# End Source File
# Begin Source File

SOURCE=.\ClrButton.h
# End Source File
# Begin Source File

SOURCE=.\CuttingPress.h
# End Source File
# Begin Source File

SOURCE=.\PLC\DataPlc.h
# End Source File
# Begin Source File

SOURCE=.\DataStruct.h
# End Source File
# Begin Source File

SOURCE=.\Dmccom.h
# End Source File
# Begin Source File

SOURCE=.\dmcdrc.h
# End Source File
# Begin Source File

SOURCE=.\dmcdrco.h
# End Source File
# Begin Source File

SOURCE=.\Dmcgc.h
# End Source File
# Begin Source File

SOURCE=.\Dmcwin.h
# End Source File
# Begin Source File

SOURCE=.\Dxf2G.h
# End Source File
# Begin Source File

SOURCE=.\EditDoubleClick.h
# End Source File
# Begin Source File

SOURCE=.\ewfapi.h
# End Source File
# Begin Source File

SOURCE=.\Expired\Expired.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\gridcad.h
# End Source File
# Begin Source File

SOURCE=.\HandDll.h
# End Source File
# Begin Source File

SOURCE=.\lamp.h
# End Source File
# Begin Source File

SOURCE=.\MachineDll.h
# End Source File
# Begin Source File

SOURCE=.\planinfo.h
# End Source File
# Begin Source File

SOURCE=.\SHLWAPI.H
# End Source File
# Begin Source File

SOURCE=.\SystemDll.h
# End Source File
# End Group
# Begin Group "GRID"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\grid\CellRange.h
# End Source File
# Begin Source File

SOURCE=.\grid\ComboGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\grid\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\grid\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\grid\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\grid\InPlaceList.h
# End Source File
# Begin Source File

SOURCE=.\grid\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\grid\TitleTip.h
# End Source File
# End Group
# Begin Group "SCAN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\scan\ScanAct.h
# End Source File
# Begin Source File

SOURCE=.\scan\ScanWork.h
# End Source File
# End Group
# Begin Group "PARAMETER"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\parameter\DataStruct.h
# End Source File
# End Group
# Begin Group "hasp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\errorprinter.h
# End Source File
# Begin Source File

SOURCE=.\hasp_api.h
# End Source File
# Begin Source File

SOURCE=.\hasp_api_cpp.h
# End Source File
# Begin Source File

SOURCE=.\vendor_code.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\2DDraw.h
# End Source File
# Begin Source File

SOURCE=.\AdjustDouble.h
# End Source File
# Begin Source File

SOURCE=.\bender.h
# End Source File
# Begin Source File

SOURCE=.\benderDlg.h
# End Source File
# Begin Source File

SOURCE=.\btnctl.h
# End Source File
# Begin Source File

SOURCE=.\captioninfo.h
# End Source File
# Begin Source File

SOURCE=.\CTest.h
# End Source File
# Begin Source File

SOURCE=.\displayctrl.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_affirm.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_AfxMessage.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_array.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_BackUp.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_bottero.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Calculator.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_config.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CuttingSize.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_DrawCad.h
# End Source File
# Begin Source File

SOURCE=.\dlg_galil.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_glass.h
# End Source File
# Begin Source File

SOURCE=.\dlg_hand.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Home.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_KeyChar.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_KeyNumber.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_light.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Loading.h
# End Source File
# Begin Source File

SOURCE=.\dlg_machine.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_MachineCase.h
# End Source File
# Begin Source File

SOURCE=.\dlg_manager.h
# End Source File
# Begin Source File

SOURCE=.\dlg_motion.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Oiling.h
# End Source File
# Begin Source File

SOURCE=.\dlg_pass.h
# End Source File
# Begin Source File

SOURCE=.\dlg_path2.h
# End Source File
# Begin Source File

SOURCE=.\dlg_save.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_scan.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SheetGlass.h
# End Source File
# Begin Source File

SOURCE=.\dlg_ShowExtra.h
# End Source File
# Begin Source File

SOURCE=.\dlg_sn.h
# End Source File
# Begin Source File

SOURCE=.\dlg_super.h
# End Source File
# Begin Source File

SOURCE=.\dlg_ustLimit.h
# End Source File
# Begin Source File

SOURCE=.\excel.h
# End Source File
# Begin Source File

SOURCE=.\IOExcel.h
# End Source File
# Begin Source File

SOURCE=.\mscomm.h
# End Source File
# Begin Source File

SOURCE=.\OrangeListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\PLGCDll.h
# End Source File
# Begin Source File

SOURCE=.\PrintFrame.h
# End Source File
# Begin Source File

SOURCE=.\PrintView.h
# End Source File
# Begin Source File

SOURCE=.\ReadGcode.h
# End Source File
# Begin Source File

SOURCE=.\RectEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\RectOptDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RtOpt.h
# End Source File
# Begin Source File

SOURCE=.\SetXY.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StructDef.h
# End Source File
# Begin Source File

SOURCE=.\TabDlg.h
# End Source File
# Begin Source File

SOURCE=.\UniButton.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BUTTON\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\3.bmp
# End Source File
# Begin Source File

SOURCE=".\res\alarm add.ico"
# End Source File
# Begin Source File

SOURCE=".\res\alarm remove.ico"
# End Source File
# Begin Source File

SOURCE=.\res\alarm.ico
# End Source File
# Begin Source File

SOURCE=.\res\bender.ico
# End Source File
# Begin Source File

SOURCE=.\res\bender.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bitDn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitLf.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_l.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitRt.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitUp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmpIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmpOut.bmp
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\CAD-WAY1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\CAD-WAY2.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\chaoyang.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chaoyang1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chaoyang2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\C轴下刀1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\C轴下刀2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\C轴下刀3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\Edit-WAY1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\Edit-WAY2.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\eelyecw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\filetype.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\GCode1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\GCode2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\Gid1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\Gid2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HENDA.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico000032.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico000042.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico000052.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico000062.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00012.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00013.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00014.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00015.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00016.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00017.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00018.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00019.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00020.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico12924.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico12926.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico12930.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico12932.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico204.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico205.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico226.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico227.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico231.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico234.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico246.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico257.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico374.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico375.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico421.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico422.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico435.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico440.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico441.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico444.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico449.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico711.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico712.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico766.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico767.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico832.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico833.ico
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_alm.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_aod.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_aou.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_com.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_def.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_dn.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_g2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_g3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_gra.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_han.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_io_.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_lin.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_lt.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_pgd.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_pgu.ico
# End Source File
# Begin Source File

SOURCE=.\icon_qui.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_rat.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon_too.ico
# End Source File
# Begin Source File

SOURCE=.\res\jingling.bmp
# End Source File
# Begin Source File

SOURCE=.\res\led_alm.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_gree.ico
# End Source File
# Begin Source File

SOURCE=.\res\led_red.ico
# End Source File
# Begin Source File

SOURCE=.\res\LedGreen.ico
# End Source File
# Begin Source File

SOURCE=.\res\LedNone.ico
# End Source File
# Begin Source File

SOURCE=.\res\LedRed.ico
# End Source File
# Begin Source File

SOURCE=.\res\LightBulbBroken.ico
# End Source File
# Begin Source File

SOURCE=.\res\LightBulbOff.ico
# End Source File
# Begin Source File

SOURCE=.\res\LightBulbOn.ico
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\MDI1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\MDI2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newjs1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newjs2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PIDN.ico
# End Source File
# Begin Source File

SOURCE=.\res\PIUP.ico
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\PLC1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\PLC2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\PNT1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\PNT2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Powerland.bmp
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\p上一页1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\p上一页2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\p下一页1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\p下一页2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\p优化1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\p优化2.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\smallico.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\speeddw1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\speeddw2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\speedup1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BUTTON\speedup2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\yirui.bmp
# End Source File
# Begin Source File

SOURCE=.\res\yirui1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\yirui2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存CXF1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存CXF2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存G1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存G2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存参数1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\保存参数2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\报警1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\报警2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\报警复位1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\报警复位2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\背景.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\背景.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\背景1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\编辑1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\编辑2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\编辑设置1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\编辑设置2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\参数1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\参数2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\参数备份1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\参数备份2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\测厚1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\测厚2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\测试1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\测试2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\查询1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\查询2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\程序零点1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\程序零点2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\程序零点3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\打开1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\打开2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\打印机1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\打印机2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\刀压设置1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\刀压设置2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\第一页1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\第一页2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\定位柱1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\定位柱2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\定位柱3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\反向1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\反向2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\反向3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\返回1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\返回2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\放大.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\放大1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\放大2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\放大使能1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\放大使能2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\分支界面.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\分支界面.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\风机换向1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\风机换向2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\风机启动1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\风机启动2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\风机启动3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\复位1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\复位2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\关闭系统1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\关闭系统2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\关机1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\关机2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\光电定位1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\光电定位2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\黑.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\还原1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\还原2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\回零1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\回零2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\回零3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\回零x1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\回零x2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\绘图1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\绘图2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\机械参数1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\机械参数2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\机械零点1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\机械零点2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\机械零点3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\计数清除1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\计数清除2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\计算器1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\计算器2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\精菱.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\精菱.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\空按钮1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\空按钮2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\空运行1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\空运行2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\空运行3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\控制器1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\控制器2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\历史报警1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\历史报警2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\流水切割1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\流水切割2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\螺补1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\螺补2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\启动1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\启动2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\气缸上1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\气缸上2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\前一页1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\前一页2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\删除1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\删除2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\上1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\上2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\设置1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\设置2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\升降1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\升降2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\升降3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\手动1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\手动2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\手动3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\手动小1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\手动小2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\输出点1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\输出点2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\输入点1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\输入点2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度11.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度12.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度13.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度21.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度22.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度23.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度降1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度降11.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度降12.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度降2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度升1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度升11.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度升12.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\速度升2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\缩小1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\缩小2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\套料1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\套料2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\套料删除1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\套料删除2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\添加1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\添加2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\停止1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\停止2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\bitmap\文件1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\文件1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\bitmap\文件2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\文件2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\文件管理1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\文件管理2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\文件类型1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\文件类型2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\物理位置1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\物理位置2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\系统配置1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\系统配置2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\下1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\下2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\下一页1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\下一页2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\新建1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\新建2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\旋转1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\旋转2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\压力降1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\压力降2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\压力升1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\压力升2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\移动1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\移动2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\异形扫描1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\异形扫描2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\优化1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\优化2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\右1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\右2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\原片统计1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\原片统计2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\圆弧1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\圆弧2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\运动1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\运动2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\暂停1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\暂停2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\诊断1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\诊断2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\正向1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\正向2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\正向3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\置位1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\置位2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\注油1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\注油2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\注油H1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\注油H2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\注油H3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\自动1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\自动2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\自动3.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\最后一页1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\最后一页2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\左1.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\BUTTON\左2.bmp"
# End Source File
# End Group
# Begin Group "Graph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GraphDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphDlg.h
# End Source File
# Begin Source File

SOURCE=.\GrArc.cpp
# End Source File
# Begin Source File

SOURCE=.\GrArc.h
# End Source File
# Begin Source File

SOURCE=.\GrEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\GrEditor.h
# End Source File
# Begin Source File

SOURCE=.\GrEllipse.cpp
# End Source File
# Begin Source File

SOURCE=.\GrEllipse.h
# End Source File
# Begin Source File

SOURCE=.\grMath.cpp
# End Source File
# Begin Source File

SOURCE=.\grMath.h
# End Source File
# Begin Source File

SOURCE=.\GrPath.cpp
# End Source File
# Begin Source File

SOURCE=.\GrPath.h
# End Source File
# Begin Source File

SOURCE=.\MyFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MyFrame.h
# End Source File
# Begin Source File

SOURCE=.\PicListWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\PicListWnd.h
# End Source File
# Begin Source File

SOURCE=.\PicWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\PicWnd.h
# End Source File
# Begin Source File

SOURCE=.\RoundAngle.cpp
# End Source File
# Begin Source File

SOURCE=.\RoundAngle.h
# End Source File
# Begin Source File

SOURCE=.\UISetting.cpp
# End Source File
# Begin Source File

SOURCE=.\UISetting.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\DMC32.lib
# End Source File
# Begin Source File

SOURCE=.\SHLWAPI.LIB
# End Source File
# Begin Source File

SOURCE=.\Dmcgc32.lib
# End Source File
# Begin Source File

SOURCE=.\HandDll.lib
# End Source File
# Begin Source File

SOURCE=.\MachineDll.lib
# End Source File
# Begin Source File

SOURCE=.\SystemDll.lib
# End Source File
# Begin Source File

SOURCE=.\Dxf2GCode.lib
# End Source File
# Begin Source File

SOURCE="c:\Program Files\Microsoft Visual Studio\VC98\Lib\ODBCCP32.LIB"
# End Source File
# Begin Source File

SOURCE=.\ewfapi.lib
# End Source File
# Begin Source File

SOURCE=.\CuttingPressure.lib
# End Source File
# Begin Source File

SOURCE=.\Alarm\AlarmRecord.lib
# End Source File
# Begin Source File

SOURCE=.\scan\ScanGlass.lib
# End Source File
# Begin Source File

SOURCE=.\RtOptDll.lib
# End Source File
# End Target
# End Project
# Section bender : {7BCB4920-648B-46C2-829B-75D1510A832F}
# 	2:5:Class:CGalilRPOcx
# 	2:10:HeaderFile:galilrpocx1.h
# 	2:8:ImplFile:galilrpocx1.cpp
# End Section
# Section bender : {C0FAECCF-F1D4-4756-9DED-8B36F792E607}
# 	2:5:Class:CDemo10
# 	2:10:HeaderFile:demo11.h
# 	2:8:ImplFile:demo11.cpp
# End Section
# Section bender : {E6E17E90-DF38-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CMSComm
# 	2:10:HeaderFile:mscomm.h
# 	2:8:ImplFile:mscomm.cpp
# End Section
# Section bender : {DFAC5876-68AD-4858-9F59-C37422F10248}
# 	2:5:Class:CCSpan
# 	2:10:HeaderFile:cspan.h
# 	2:8:ImplFile:cspan.cpp
# End Section
# Section bender : {648A5600-2C6E-101B-82B6-000000000014}
# 	2:21:DefaultSinkHeaderFile:mscomm.h
# 	2:16:DefaultSinkClass:CMSComm
# End Section
# Section bender : {1432BAEF-59DB-432A-992A-1A5F6C12375E}
# 	2:21:DefaultSinkHeaderFile:galilallocx.h
# 	2:16:DefaultSinkClass:CGalilAllOcx
# End Section
# Section bender : {2E56328F-52AE-45C4-8C11-CBEE5C5B501C}
# 	2:21:DefaultSinkHeaderFile:galilioocx.h
# 	2:16:DefaultSinkClass:CGalilIOOcx
# End Section
# Section bender : {71A5E095-40DA-4A4D-83D3-21D29C89C7B5}
# 	2:21:DefaultSinkHeaderFile:cspan.h
# 	2:16:DefaultSinkClass:CCSpan
# End Section
# Section bender : {0A8EF673-AFDE-4FFB-9FA8-344168F61424}
# 	2:21:DefaultSinkHeaderFile:gridcad.h
# 	2:16:DefaultSinkClass:CGridCAD
# End Section
# Section bender : {D21D9466-82BF-42A1-8EDC-2ED1C85AB130}
# 	2:5:Class:CCaptionInfo
# 	2:10:HeaderFile:captioninfo.h
# 	2:8:ImplFile:captioninfo.cpp
# End Section
# Section bender : {0E09638C-3CFA-4F05-9BF0-4BA46E72ABF5}
# 	2:5:Class:CLed
# 	2:10:HeaderFile:led.h
# 	2:8:ImplFile:led.cpp
# End Section
# Section bender : {7C5CE390-4368-4CAB-B0E2-FF8D7D6F0631}
# 	2:5:Class:CBtnCtl
# 	2:10:HeaderFile:btnctl.h
# 	2:8:ImplFile:btnctl.cpp
# End Section
# Section bender : {81B9117E-72B5-4DE3-963B-0A3F5B06F66B}
# 	2:21:DefaultSinkHeaderFile:displayctrl.h
# 	2:16:DefaultSinkClass:CDisplayCtrl
# End Section
# Section bender : {96003DAD-D82D-4617-805D-2653ADF1947D}
# 	2:21:DefaultSinkHeaderFile:led.h
# 	2:16:DefaultSinkClass:CLed
# End Section
# Section bender : {B78587E6-F90F-40A3-89FE-4FFE0DD19D43}
# 	2:5:Class:CGalilAxisStateOcx
# 	2:10:HeaderFile:galilaxisstateocx.h
# 	2:8:ImplFile:galilaxisstateocx.cpp
# End Section
# Section bender : {978C9E23-D4B0-11CE-BF2D-00AA003F40D0}
# 	2:21:DefaultSinkHeaderFile:labelcontrol.h
# 	2:16:DefaultSinkClass:CLabelControl
# End Section
# Section bender : {F3E43F52-2A42-402E-8B64-823F50148CB4}
# 	2:21:DefaultSinkHeaderFile:manometer.h
# 	2:16:DefaultSinkClass:CManometer
# End Section
# Section bender : {36A58C54-2836-42DF-B0C2-B1BCB69006AA}
# 	2:5:Class:CDisplayCtrl
# 	2:10:HeaderFile:displayctrl.h
# 	2:8:ImplFile:displayctrl.cpp
# End Section
# Section bender : {5AB0622F-638F-4520-8591-A2B63E58ED4B}
# 	2:5:Class:CPlanInfo
# 	2:10:HeaderFile:planinfo1.h
# 	2:8:ImplFile:planinfo1.cpp
# End Section
# Section bender : {3B813CE7-7C10-4F84-AD06-9DF76D97A9AA}
# 	2:5:Class:CAcroAXDocShim
# 	2:10:HeaderFile:acroaxdocshim.h
# 	2:8:ImplFile:acroaxdocshim.cpp
# End Section
# Section bender : {B00AC9EB-4ED1-4734-B67F-1BEF4016AC1F}
# 	2:21:DefaultSinkHeaderFile:galilaxisstateocx.h
# 	2:16:DefaultSinkClass:CGalilAxisStateOcx
# End Section
# Section bender : {1013922F-98F9-426D-B5D5-5D0104CA792F}
# 	2:21:DefaultSinkHeaderFile:plan.h
# 	2:16:DefaultSinkClass:CPlan
# End Section
# Section bender : {C06EA015-E48A-4FF2-8862-28925C248B46}
# 	2:21:DefaultSinkHeaderFile:btnctl.h
# 	2:16:DefaultSinkClass:CBtnCtl
# End Section
# Section bender : {E65D638B-F1B3-45A7-B7E1-BCC480496CA8}
# 	2:21:DefaultSinkHeaderFile:posmonit.h
# 	2:16:DefaultSinkClass:CPosMonit
# End Section
# Section bender : {9DA7072B-A6DB-4819-8FDC-C818CC82A02D}
# 	2:21:DefaultSinkHeaderFile:lamp.h
# 	2:16:DefaultSinkClass:CLamp
# End Section
# Section bender : {47A738F1-7FAF-11D0-B148-00A0C922E820}
# 	2:5:Class:CAdodc
# 	2:10:HeaderFile:adodc.h
# 	2:8:ImplFile:adodc.cpp
# End Section
# Section bender : {769D5AAE-0342-424F-9ABD-386E44BA4123}
# 	2:21:DefaultSinkHeaderFile:planinfo.h
# 	2:16:DefaultSinkClass:CPlanInfo
# End Section
# Section bender : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section bender : {ADD08276-69DF-49AA-BD16-ED7BA0FDEA23}
# 	2:21:DefaultSinkHeaderFile:buttonw.h
# 	2:16:DefaultSinkClass:CButtonW
# End Section
# Section bender : {A192EC58-118D-4A7B-9652-EFB9594CBCC9}
# 	2:5:Class:CPlan
# 	2:10:HeaderFile:plan.h
# 	2:8:ImplFile:plan.cpp
# End Section
# Section bender : {5F979E5C-A269-4DC4-9A53-10C42B873DA7}
# 	2:21:DefaultSinkHeaderFile:demo10.h
# 	2:16:DefaultSinkClass:CDemo10
# End Section
# Section bender : {F214CDF5-5CB1-40CA-ABAD-00A30B5D272C}
# 	2:21:DefaultSinkHeaderFile:galilrpocx.h
# 	2:16:DefaultSinkClass:CGalilRPOcx
# End Section
# Section bender : {4813FDFE-79AF-4020-AA0F-6A6569E0A5C6}
# 	2:5:Class:CGridCAD
# 	2:10:HeaderFile:gridcad.h
# 	2:8:ImplFile:gridcad.cpp
# End Section
# Section bender : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section bender : {67397AA3-7FB1-11D0-B148-00A0C922E820}
# 	2:21:DefaultSinkHeaderFile:adodc.h
# 	2:16:DefaultSinkClass:CAdodc
# End Section
# Section bender : {8C236C62-832C-441E-BA96-9FDB080C059E}
# 	2:21:DefaultSinkHeaderFile:captioninfo.h
# 	2:16:DefaultSinkClass:CCaptionInfo
# End Section
# Section bender : {C5744A1D-8A2C-488A-8B58-DA5EAFA19733}
# 	2:5:Class:CGalilAllOcx
# 	2:10:HeaderFile:galilallocx.h
# 	2:8:ImplFile:galilallocx.cpp
# End Section
# Section bender : {CA8A9780-280D-11CF-A24D-444553540000}
# 	2:21:DefaultSinkHeaderFile:acroaxdocshim.h
# 	2:16:DefaultSinkClass:CAcroAXDocShim
# End Section
# Section bender : {DC0F364D-6B19-42D2-BF8F-317CEDAB5170}
# 	2:5:Class:CManometer
# 	2:10:HeaderFile:manometer.h
# 	2:8:ImplFile:manometer.cpp
# End Section
# Section bender : {04598FC1-866C-11CF-AB7C-00AA00C08FCF}
# 	2:5:Class:CLabelControl
# 	2:10:HeaderFile:labelcontrol.h
# 	2:8:ImplFile:labelcontrol.cpp
# End Section
# Section bender : {BC2D0E22-32A6-409E-B711-3D0B36B3FD1C}
# 	2:5:Class:CGalilIOOcx
# 	2:10:HeaderFile:galilioocx.h
# 	2:8:ImplFile:galilioocx.cpp
# End Section
# Section bender : {1F1A4D94-9EE9-460D-A23B-2710BE388DDA}
# 	2:5:Class:CLamp
# 	2:10:HeaderFile:lamp.h
# 	2:8:ImplFile:lamp.cpp
# End Section
# Section bender : {2AA1FD1B-EB55-47A6-91B5-11407B5666F2}
# 	2:5:Class:CPosMonit
# 	2:10:HeaderFile:posmonit.h
# 	2:8:ImplFile:posmonit.cpp
# End Section
# Section bender : {97D3FD94-8B6C-49E1-81EA-81D929B775C7}
# 	2:5:Class:CButtonW
# 	2:10:HeaderFile:buttonw2.h
# 	2:8:ImplFile:buttonw2.cpp
# End Section
