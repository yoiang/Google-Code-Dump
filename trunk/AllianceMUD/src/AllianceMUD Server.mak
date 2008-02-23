# Microsoft Developer Studio Generated NMAKE File, Based on AllianceMUD Server.dsp
!IF "$(CFG)" == ""
CFG=AllianceMUD Server - Win32 Debug
!MESSAGE No configuration specified. Defaulting to AllianceMUD Server - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "AllianceMUD Server - Win32 Release" && "$(CFG)" != "AllianceMUD Server - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "AllianceMUD Server - Win32 Release"

OUTDIR=.\src\Release
INTDIR=.\src\Release

ALL : ".\AllianceMUD Server.exe"


CLEAN :
	-@erase "$(INTDIR)\Entity.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Main.res"
	-@erase "$(INTDIR)\Queue.obj"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinProcs.obj"
	-@erase ".\AllianceMUD Server.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\AllianceMUD Server.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Main.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AllianceMUD Server.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Comctl32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\AllianceMUD Server.pdb" /machine:I386 /out:"AllianceMUD Server.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Entity.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\Queue.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\WinProcs.obj" \
	"$(INTDIR)\Main.res"

".\AllianceMUD Server.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AllianceMUD Server - Win32 Debug"

OUTDIR=.\src\Debug
INTDIR=.\src\Debug

ALL : ".\AllianceMUD Server Debug.exe"


CLEAN :
	-@erase "$(INTDIR)\Entity.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Log.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Main.res"
	-@erase "$(INTDIR)\Queue.obj"
	-@erase "$(INTDIR)\Server.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WinProcs.obj"
	-@erase "$(OUTDIR)\AllianceMUD Server Debug.pdb"
	-@erase ".\AllianceMUD Server Debug.exe"
	-@erase ".\AllianceMUD Server Debug.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\AllianceMUD Server.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Main.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\AllianceMUD Server.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Comctl32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\AllianceMUD Server Debug.pdb" /debug /machine:I386 /out:"AllianceMUD Server Debug.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Entity.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\Log.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\Queue.obj" \
	"$(INTDIR)\Server.obj" \
	"$(INTDIR)\WinProcs.obj" \
	"$(INTDIR)\Main.res"

".\AllianceMUD Server Debug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("AllianceMUD Server.dep")
!INCLUDE "AllianceMUD Server.dep"
!ELSE 
!MESSAGE Warning: cannot find "AllianceMUD Server.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "AllianceMUD Server - Win32 Release" || "$(CFG)" == "AllianceMUD Server - Win32 Debug"
SOURCE=.\src\Entity.cpp

"$(INTDIR)\Entity.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Globals.cpp

"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Log.cpp

"$(INTDIR)\Log.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Main.cpp

"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Main.rc

!IF  "$(CFG)" == "AllianceMUD Server - Win32 Release"


"$(INTDIR)\Main.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Main.res" /i "src" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "AllianceMUD Server - Win32 Debug"


"$(INTDIR)\Main.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Main.res" /i "src" /d "_DEBUG" $(SOURCE)


!ENDIF 

SOURCE=.\src\Queue.cpp

"$(INTDIR)\Queue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\Server.cpp

"$(INTDIR)\Server.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\WinProcs.cpp

"$(INTDIR)\WinProcs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

