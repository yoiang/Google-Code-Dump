/*

  Main.cpp
  Version 0.004.000

*/
  
#include "Main.h"

int InitLogClass ()
{
 WNDCLASS wndClass ;

 wndClass.style = 0 ;
 wndClass.lpfnWndProc = LogWinProc ;
 wndClass.cbClsExtra = 0;
 wndClass.cbWndExtra = 0;
 wndClass.hInstance = hCurrentInstance ;
 wndClass.hIcon = NULL;
 wndClass.hCursor = LoadCursor(NULL, IDC_IBEAM);
 wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
 wndClass.lpszMenuName = NULL ;
 wndClass.lpszClassName = "AMUDLog" ;

 return RegisterClass(&wndClass);
}

int InitStatusClass ()
{
 WNDCLASS wndClass ;

 wndClass.style = 0 ;
 wndClass.lpfnWndProc = StatusWinProc ;
 wndClass.cbClsExtra = 0 ;
 wndClass.cbWndExtra = 0 ;
 wndClass.hInstance = hCurrentInstance ;
 wndClass.hIcon = NULL ;
 wndClass.hCursor = LoadCursor(NULL, IDC_ARROW) ;
 wndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1) ;
 wndClass.lpszMenuName = NULL ;
 wndClass.lpszClassName = "AMUDStatus" ;

 return RegisterClass(&wndClass) ;
}

int InitWC ()
{
 if (hCurrentInstance == 0) return 0 ;

 INITCOMMONCONTROLSEX InitComCntrlEX ;
 InitComCntrlEX.dwSize = sizeof(INITCOMMONCONTROLSEX) ;
 InitComCntrlEX.dwICC = ICC_TREEVIEW_CLASSES ; //| ICC_BAR_CLASSES | ICC_INTERNET_CLASSES ;
 if (!InitCommonControlsEx (&InitComCntrlEX)) FatalError("WinMain: InitCommonControlsEx failed") ;

 // ReadFields ("app.cfg", pApplicationVariables, NULL) ;

 if (!InitLogClass ()) return 0 ;
 if (!InitStatusClass ()) return 0 ;

 WNDCLASS wndClass ;

 wndClass.style = 0 ;
 wndClass.lpfnWndProc = MainProc ; 
 wndClass.cbClsExtra = 0 ;
 wndClass.cbWndExtra = 0 ;
 wndClass.hInstance = hCurrentInstance ;
 wndClass.hIcon = LoadIcon(hCurrentInstance, MAKEINTRESOURCE(IDI_MAIN)) ;
 wndClass.hCursor = LoadCursor(NULL, IDC_ARROW) ;
 wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH) ;
 wndClass.lpszMenuName = MAKEINTRESOURCE(IDM_MAIN) ;
 wndClass.lpszClassName = "AMUDMain" ;

 return RegisterClass(&wndClass) ;
}

void InitFonts ()
{
 HDC hDC ;			
 LOGFONT lpLogFont ;

 if (!(hDC = GetDC(hMain))) FatalError("InitFonts: Cannot GetDC with hMain") ;

 lpLogFont.lfHeight = -MulDiv(10, GetDeviceCaps(hDC, LOGPIXELSY), 72);
 lpLogFont.lfWidth = 0 ;
 lpLogFont.lfEscapement = 0 ;
 lpLogFont.lfOrientation = 0 ;
 lpLogFont.lfWeight = FW_NORMAL ;
 lpLogFont.lfItalic = 0 ;
 lpLogFont.lfUnderline = 0 ;
 lpLogFont.lfStrikeOut = 0 ;
 lpLogFont.lfCharSet = 0 ;
 lpLogFont.lfOutPrecision = 0 ;
 lpLogFont.lfClipPrecision = 0 ;
 lpLogFont.lfQuality = 0 ;
 lpLogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
 strcpy(lpLogFont.lfFaceName, "MS Sans Serif");
 
 hFont = CreateFontIndirect(&lpLogFont);

 ReleaseDC(hMain, hDC) ;
 return ;
}

void InitEntitysWin ()
{
 RECT Rect ;
 GetClientRect(hMain, &Rect);
 
 if (!(hEntitys = CreateWindowEx(0, 
                                 WC_TREEVIEW, 
								 "Entities",
                                 WS_VISIBLE|WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS,
								 0,
								 0,
								 Rect.right / 4,
								 Rect.bottom / 2 - 20,
								 hMain,
								 NULL,
								 hCurrentInstance,
								 NULL))) FatalError ("InitEntitysWin - CreateWindowEx failed") ;

 ShowWindow(hEntitys, SW_SHOW) ;
 if(!UpdateWindow(hEntitys))
 {
  FatalError ("InitEntitysWin - UpdateWindow failed") ;
  DestroyWindow(hEntitys) ;
 }

 if (!(hEntity = CreateWindowEx(0, 
                                WC_LISTVIEW, 
								"Entity",
                                WS_VISIBLE|WS_CHILD|LVS_REPORT,
								0,
								Rect.bottom / 2 - 20,
								Rect.right / 4,
								Rect.bottom - 20,
								hMain,
								NULL,
								hCurrentInstance,
								NULL))) FatalError ("InitEntitysWin - CreateWindowEx failed") ;
/*
 LVITEM LVItem ;
 LVItem.mask = LVIF_TEXT ;
 LVItem.iItem = 0 ;
 LVItem.iSubItem = 0 ;
 LVItem.state = 0 ;
 LVItem.stateMask = 0 ;
 LVItem.iImage = 0 ;
 LVItem.pszText = LPSTR_TEXTCALLBACK ;
 LVItem.lParam = (LPARAM)EntPField ;
 if (SendMessage(hEntity, LVM_INSERTITEM, 0, (LPARAM) (LPLVITEM) &LVItem) == -1) Logs.AddLine("InitEntitysWin - SendMessage failed") ;
*/
 ShowWindow(hEntity, SW_SHOW) ;
 if(!UpdateWindow(hEntity))
 {
  FatalError ("InitEntitysWin - UpdateWindow failed") ;
  DestroyWindow(hEntity) ;
 }

}


void InitLogWin ()
{
 RECT Rect ;		

 GetClientRect(hMain, &Rect);

 if (!(hLog = CreateWindow("AMUDLog", 
                           "Log", 
						   WS_CHILD|WS_VSCROLL|WS_VISIBLE,
						   Rect.right / 4,
						   0,
						   Rect.right,
						   Rect.bottom - 20,
						   hMain,
						   NULL,
						   hCurrentInstance,
  						   NULL))) FatalError ("InitLogWin - CreateWindow failed") ;

 ShowWindow(hLog, SW_SHOW) ;
 if(!UpdateWindow(hLog))
 {
  FatalError ("InitLogWin - UpdateWindow failed") ;
  DestroyWindow(hLog) ;
 }
}

void InitStatusWin ()
{
 RECT Rect ;		

 GetClientRect(hMain, &Rect);

 if (!(hStatus = CreateWindow ("AMUDStatus",
                               "Status",
							   WS_CHILD,
							   0, 
						       Rect.bottom - 20, 
						       Rect.right, 
						       20,
                               hMain, 
						       NULL, 
							   hCurrentInstance,
							   NULL))) FatalError ("InitStatusWin - CreateWindow failed") ;

 ShowWindow(hStatus, SW_SHOW) ;
 if(!UpdateWindow(hStatus))
 {
  FatalError ("InitStatusWin - UpdateWindow failed") ;
  DestroyWindow(hStatus) ;
 }
}

void InitInst (int nCmdShow)
{
 if (!(hMain = CreateWindow("AMUDMain",
			                szApplicationName,
			                WS_OVERLAPPEDWINDOW,
			                CW_USEDEFAULT, 
							CW_USEDEFAULT,
			                CW_USEDEFAULT, 
							CW_USEDEFAULT,
			                NULL, 
							NULL, 
							hCurrentInstance, 
							NULL))) FatalError ("InitStatusWin - CreateWindow failed") ;

 if (!(nSystemTimer = SetTimer (hMain, 0, 1, UpdateSystemTime))) FatalError("InitInstance: Cannot SetTimer for MainWin.hWnd with UpdateSystemTime") ;

// if (!(nTimerID2 = SetTimer (hMain, 1, 1, ServerMainLoop)))
//  FatalError("InitInstance: Cannot SetTimer for MainWin.hWnd with ServerMainLoop") ;

 InitFonts() ;
 InitEntitysWin() ;
 InitLogWin() ;
 InitStatusWin() ;

 ShowWindow(hMain, nCmdShow) ;
 if(!UpdateWindow(hMain)) FatalError ("InitInst - UpdateWindow failed") ;

 Logs.AddLine("Initializing winsocks") ;
 if (WSAStartup(WS_VERSION, &WSAData) != 0/* && (Proto = getprotobyname ("tcp")) != NULL*/) FatalError("InitInst - WSAStartup failed") ;

 Logs.AddLine("Reading Entitys") ;
 ReadNumScripts ("pCServer", pGServers, E_SERVER, NULL) ;

 Logs.AddLine("Spawning Entitys") ;
 Entity *pEntity = pGServers ;
 while (pEntity != NULL) 
 {
  pEntity->Spawn (pEntity) ;
  pEntity = pEntity->pNext ;
 }

 Logs.AddLine("Starting server") ;
}

void DeInitAppVars ()
{
 if (nSystemTimer != 0) KillTimer(hMain, nSystemTimer) ;
 if (nTimerID2 != 0) KillTimer(hMain, nTimerID2) ;
 if (hFont != 0) DeleteObject(hFont);

 Entity *pEntity = pGServers ;
 while (pEntity != NULL) 
 {
  pEntity->Die (pEntity) ;
  pEntity = pEntity->pNext ;
 }

 if (pGHeadEnt != NULL)
 {
  while (pGTailEnt->pLast != NULL) 
  {
   pGTailEnt = pGTailEnt->pLast ;
   delete pGTailEnt->pNext ;
  }
  delete pGTailEnt ;
 }
}

void ShutDownApplication ()
{
 if (hCurrentInstance == 0) return ;
 hCurrentInstance = 0 ;
// DeleteFile ("app.cfg") ;
 DeInitAppVars () ; 
// WriteFields ("app.cfg", pApplicationVariables, NULL) ;

 fcloseall () ;
 return ;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
 MSG uMsg ;

 hCurrentInstance = hInstance ;

 Logs.AddLine("Initializing windows classes") ;
 if (!hPrevInstance) if (!InitWC()) return 1 ;

 Logs.AddLine("Initializing application") ;
 InitInst(nCmdShow) ;

 while (GetMessage(&uMsg, NULL, 0,0))
 {
  TranslateMessage(&uMsg) ;
  DispatchMessage(&uMsg) ;
 }

 Logs.AddLine("Shutting down application") ;
 ShutDownApplication() ;

 Logs.AddLine("Shutting down winsocks") ;
 WSACleanup();

 return uMsg.wParam ;
}

void FatalError (char *szError)
{
 MessageBox (NULL, szError, "Fatal Error!", MB_OK | MB_ICONERROR) ;

 ShutDownApplication () ;

 exit(-1) ;
}