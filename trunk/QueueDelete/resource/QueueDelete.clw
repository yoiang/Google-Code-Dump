; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=m_cbAlwaysRun
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "queuedelete.h"
LastPage=0

ClassCount=3
Class1=CQueueDeleteApp
Class2=CQueueDeleteDlg

ResourceCount=2
Resource1=IDD_QUEUEDELETE_DIALOG
Class3=m_cbAlwaysRun
Resource2=IDR_MAINMENU

[CLS:CQueueDeleteApp]
Type=0
BaseClass=CWinApp
HeaderFile=\Personal\QueueDelete\src\QueueDelete.h
ImplementationFile=\Personal\QueueDelete\src\QueueDelete.cpp
LastObject=ID_OPTIONS_TOGGLEAUTOSTART

[CLS:CQueueDeleteDlg]
Type=0
BaseClass=CDialog
HeaderFile=\Personal\QueueDelete\src\QueueDeleteDlg.h
ImplementationFile=\Personal\QueueDelete\src\QueueDeleteDlg.cpp
LastObject=ID_OPTIONS_ALWAYS_RUN

[DLG:IDD_QUEUEDELETE_DIALOG]
Type=1
Class=CQueueDeleteDlg
ControlCount=1
Control1=IDC_FILELIST,SysListView32,1350631431

[MNU:IDR_MAINMENU]
Type=1
Class=CQueueDeleteDlg
Command1=ID_OPTIONS_TOGGLEAUTOSTART
Command2=ID_OPTIONS_FORCEAUTOSTART
Command3=ID_OPTIONS_REMOVEREGISTERY
Command4=ID_OPTIONS_ALWAYS_RUN
Command5=ID_OPTIONS_DELETEFILESNOW
Command6=ID_OPTIONS_EXIT
CommandCount=6

