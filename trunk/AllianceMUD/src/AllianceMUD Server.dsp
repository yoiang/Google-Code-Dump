# Microsoft Developer Studio Project File - Name="AllianceMUD Server" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AllianceMUD Server - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AllianceMUD Server.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AllianceMUD Server.mak" CFG="AllianceMUD Server - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AllianceMUD Server - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AllianceMUD Server - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AllianceMUD Server - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "src\Release"
# PROP Intermediate_Dir "src\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Comctl32.lib /nologo /subsystem:windows /machine:I386 /out:"AllianceMUD Server.exe"

!ELSEIF  "$(CFG)" == "AllianceMUD Server - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "src\Debug"
# PROP Intermediate_Dir "src\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"AllianceMUD Server Debug.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AllianceMUD Server - Win32 Release"
# Name "AllianceMUD Server - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\Body.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Client.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Commands.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Entity.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Exit.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Files.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Globals.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Item.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Log.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Main.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Main.rc
# End Source File
# Begin Source File

SOURCE=.\src\Mob.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Net.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Plane.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Queue.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Room.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Server.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\Spawn.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\System.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\src\WinProcs.cpp
# SUBTRACT CPP /YX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\Body.h
# End Source File
# Begin Source File

SOURCE=.\src\Client.h
# End Source File
# Begin Source File

SOURCE=.\src\Commands.h
# End Source File
# Begin Source File

SOURCE=.\src\Defs.h
# End Source File
# Begin Source File

SOURCE=.\src\Entity.h
# End Source File
# Begin Source File

SOURCE=.\src\Exit.h
# End Source File
# Begin Source File

SOURCE=.\src\Files.h
# End Source File
# Begin Source File

SOURCE=.\src\Globals.h
# End Source File
# Begin Source File

SOURCE=.\src\Item.h
# End Source File
# Begin Source File

SOURCE=.\src\Log.h
# End Source File
# Begin Source File

SOURCE=.\src\Main.h
# End Source File
# Begin Source File

SOURCE=.\src\Mob.h
# End Source File
# Begin Source File

SOURCE=.\src\Net.h
# End Source File
# Begin Source File

SOURCE=.\src\Plane.h
# End Source File
# Begin Source File

SOURCE=.\src\Queue.h
# End Source File
# Begin Source File

SOURCE=.\src\Room.h
# End Source File
# Begin Source File

SOURCE=.\src\Server.h
# End Source File
# Begin Source File

SOURCE=.\src\Spawn.h
# End Source File
# Begin Source File

SOURCE=.\src\System.h
# End Source File
# Begin Source File

SOURCE=.\src\WinProcs.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\src\main.ico
# End Source File
# Begin Source File

SOURCE=.\Todo.txt
# End Source File
# End Group
# End Target
# End Project
