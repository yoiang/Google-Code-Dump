/*

  WinProcs.cpp
  Version 0.004.000

*/
  
#include "Main.h"

int SelectStartupServer (HMENU hMenu) ;
int SelectShutdownServer (HMENU hMenu) ;

LRESULT CALLBACK MainProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
 switch (uMsg)
 {
 case MW_CONNECTED:
  Logs.AddLine("Client connected, logging in") ;
  ConnectClient (wParam) ;
 return 0 ;
 case MW_DATAREADY:
  switch (LOWORD(lParam))
  {
  case FD_READ:
   Entity *pEntity ;
   pEntity = pGHeadEnt ;
   while (pEntity != NULL && (pEntity->nEntType != E_MOB || pEntity->uMob.bClient != 1 || pEntity->uMob.pClient->hSocket != wParam)) pEntity = pEntity->pGNext ;
   if (pEntity != NULL) 
   {
    char szBuffer[64] ;
    int nBufferLength ;
    if ((nBufferLength = recv(wParam, szBuffer, 255, 0)) == SOCKET_ERROR) Logs.AddLine("MainProc: MW_DATAREADY: FD_READ: SOCKET_ERROR") ;
    else
    {
 	 szBuffer[nBufferLength] = '\0' ;
 	 for (int nTrav = 0 ; (nTrav < nBufferLength && nTrav + pEntity->uMob.pClient->nBufferPos < 255 && szBuffer[nTrav] != '\0' && szBuffer[nTrav] != '\n') ; nTrav ++) pEntity->uMob.pClient->szBuffer[nTrav + pEntity->uMob.pClient->nBufferPos] = szBuffer[nTrav] ;
     pEntity->uMob.pClient->szBuffer[nTrav + pEntity->uMob.pClient->nBufferPos] = '\0' ;
	 pEntity->uMob.pClient->nBufferPos += nTrav ;
	 send(pEntity->uMob.pClient->hSocket, szBuffer, strlen(szBuffer), 0) ;
	 if (szBuffer[nTrav] == '\n' || nTrav + pEntity->uMob.pClient->nBufferPos == 255)
	 {
	  send(pEntity->uMob.pClient->hSocket, "\n\r", 2, 0) ;

	  if (nTrav + pEntity->uMob.pClient->nBufferPos == 255) pEntity->uMob.pClient->szBuffer[nTrav + pEntity->uMob.pClient->nBufferPos - 1] = '\0' ;
	  else pEntity->uMob.pClient->szBuffer[nTrav + pEntity->uMob.pClient->nBufferPos - 2] = '\0' ;
	  
	  if (DoCommand (pEntity, pEntity->uMob.pClient->szBuffer))
	  {
		  send(pEntity->uMob.pClient->hSocket, "\n\r: ", 6, 0) ;
      
		  pEntity->uMob.pClient->nBufferPos = 0 ;
	  }
	 }
	} 
   }
  return 0 ;
  case FD_CLOSE:
   Entity *pClosed ;
   pClosed = pGHeadEnt ;
   while (pClosed != NULL && (pClosed->nEntType != E_MOB || pClosed->uMob.bClient != 1 || pClosed->uMob.pClient->hSocket != wParam)) pClosed = pClosed->pGNext ;
   if (pClosed != NULL) 
   {
    char *szBuffer = new char [21 + strlen(pClosed->szName)] ;
    sprintf(szBuffer, "Client %s disconnected", pClosed->szName) ; 
    Logs.AddLine(szBuffer) ;
	delete [] szBuffer ;

	DisconnectClient (pClosed) ;
   } else Logs.AddLine("Unknown connection closed") ;
  return 0 ;
  default:
//   Logs.AddLine("MainProc - MW_DATAREADY: Unknown socket event") ;
  return 0 ;
  }
 return 0 ;
 case WM_CREATE:
 return 0 ;
 case WM_SIZE:
  if (hEntitys)
  {
   MoveWindow(hEntitys,
	          0,
			  0,
			  LOWORD(lParam) / 4,
			  HIWORD(lParam) / 2 - 20,
			  1) ;
  }
  if (hEntity)
  {
   MoveWindow(hEntity,
	          0,
			  HIWORD(lParam) / 2 - 20,
			  LOWORD(lParam) / 4,
			  HIWORD(lParam) - 20,
			  1) ;
  }
  if (hLog)
  {
   MoveWindow(hLog,
	          LOWORD(lParam) / 4,
			  0,
			  LOWORD(lParam),
			  HIWORD(lParam) - 20,
			  1) ;
  }
  if (hStatus)
  {
   MoveWindow(hStatus,
	          0,
			  HIWORD(lParam) - 20,
			  LOWORD(lParam),
			  HIWORD(lParam),
			  1) ;
  }
  PostMessage(hEntitys, WM_PAINT, 0, 0) ;
  PostMessage(hEntity, WM_PAINT, 0, 0) ;
  PostMessage(hLog, WM_PAINT, 0, 0) ;
  PostMessage(hStatus, WM_PAINT, 0, 0) ;
 return 0 ;
 case WM_ACTIVATE:
  if (LOWORD(wParam) != WA_ACTIVE && LOWORD(wParam) != WA_CLICKACTIVE) break ;
  PostMessage(hEntitys, WM_PAINT, 0, 0) ;
  PostMessage(hEntity, WM_PAINT, 0, 0) ;
  PostMessage(hLog, WM_PAINT, 0, 0) ;
  PostMessage(hStatus, WM_PAINT, 0, 0) ;
 return 0 ;
 case WM_NOTIFY:
  switch (((LPNMHDR) lParam)->code)
  {
   case LVN_GETDISPINFO: 
/*    NMLVDISPINFO *pnmv ;
    pnmv = (NMLVDISPINFO*) lParam; 
    if (pnmv->item.mask & LVIF_TEXT) 
	{ 
 	 PField* pItem ;
     pItem = (PField*) (pnmv->item.lParam); 
	 pnmv->item.pszText = new char [strlen(pItem[pnmv->item.iItem].szName) + 1] ;
	 strcpy(pnmv->item.pszText, pItem[pnmv->item.iItem].szName);
	 pnmv->item.cchTextMax = strlen(pItem[pnmv->item.iItem].szName) ;
	}*/
   break ;
   case TVN_SELCHANGED:
/*	NMTREEVIEW pNMTV ;
	pNMTV = (NMTREEVIEW) lParam ;
	Entity *pEntity = pGEntHead ;
	while (pEntity != NULL && pEntity->hTreeItem != pNMTV.itemNew) pEntity = pEntity->pGNext ;
	if (pEntity != NULL)
	{
	}
*/   return 0 ;
  }
 break ;
 case WM_COMMAND:
  if (HIWORD(wParam) == 0)
  {
   HMENU hMenu ;
   switch (LOWORD(wParam))
   {
//   case ID_FILE_SETTINGS:
//	DialogBox(hInstanceCurrent, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, (DLGPROC)SettingsDlgProc) ;
//   break ;
   case ID_FILE_EXIT:
	PostMessage (hWnd, WM_CLOSE, NULL, NULL);
   break ;
/*   case ID_STATUS_ONLINE:
    hMenu = GetMenu (MainWin.hWnd) ;
	SelectStartupServer (hMenu) ;
   break ;
   case ID_STATUS_RESTART:
    hMenu = GetMenu (MainWin.hWnd) ;
	SelectShutdownServer (hMenu) ;
	SelectStartupServer (hMenu) ;
   break ;
   case ID_STATUS_OFFLINE:
    hMenu = GetMenu (MainWin.hWnd) ;
	SelectShutdownServer (hMenu) ;
   break ;
   case ID_STATUS_SHUTDOWN:
    hMenu = GetMenu (MainWin.hWnd) ;
	SelectShutdownServer (hMenu) ;
   break ;
*/
   case ID_CONNECT_LOCALHOST:
   if (pGServers == NULL) break ;
	char szTemp [26] ;
	sprintf (szTemp, "telnet://localhost:%i", pGServers->uServer.nConnectPort) ;
	ShellExecute (hWnd, "open", szTemp, NULL, NULL, SW_SHOWNORMAL) ;
   break ;
/*   case ID_CONNECT_REMOTE:
//	ShellExecute (hWnd, "open", "telnet://", NULL, NULL, SW_SHOWNORMAL) ;
   break ;
   case ID_HELP_THEALLIANCEHOMEPAGE:
	ShellExecute (hWnd, "open", "http://thealliance.dhs.org", NULL, NULL, SW_SHOWNORMAL) ;
   break ;
   case ID_HELP_ALLIANCEMUDDEVELOPMENT:
	ShellExecute (hWnd, "open", "http://mudcode.dhs.org", NULL, NULL, SW_SHOWNORMAL) ;
   break ;
   case ID_HELP_ABOUT:
    DialogBox(hInstanceCurrent, MAKEINTRESOURCE(IDD_ABOUT), hWnd, (DLGPROC)AboutDlgProc) ;
   break ;*/
   }
  }
 return 0;
 case WM_ERASEBKGND:
 // No point erasing the window, it is obscured by child windows.
 return 1;
 case WM_CLOSE:
//  if (TheAlliance->IsOnline () && bDisplayCloseApp) DialogBox(hInstanceCurrent, MAKEINTRESOURCE(IDD_EXIT), hWnd, (DLGPROC)ExitDlgProc) ;
/*   else*/ DestroyWindow(hWnd) ;
 return 0 ;
 case WM_DESTROY:
//  TheAlliance->Shutdown () ;
//  if (!GetWindowRect(hWnd, &MainWin.Rect)) ExitWithError("MainProc: Cannot GetWindowRect for hWnd") ;
  PostQuitMessage(0) ;
 return 0/*(!DeInitWinSock())*/ ;
 }
 return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

VOID CALLBACK ServerMainLoop(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
 Logs.AddLine("Test") ;
}

VOID CALLBACK UpdateSystemTime(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
 // replace with self addition?
 GetLocalTime(&SystemTime) ;
}

LRESULT CALLBACK LogWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
 switch (uMsg) 
 {
 case WM_PAINT:
  RECT rectUpdate ;
  if (GetUpdateRect(hWnd, &rectUpdate, 1))
  {
   RECT Rect ;
   GetClientRect(hWnd, &Rect) ;
//SetScrollPos
   HDC hDC ;
   PAINTSTRUCT lpPaint ;

   if ((hDC = BeginPaint(hWnd, &lpPaint)) == NULL) FatalError ("StatusWinProc: Cannot BeginPaint with hWnd") ;
   SelectObject(hDC, hFont);
   SetBkColor(hDC, 0x00000000);
   SetTextColor(hDC, 0x00ffffff);
   SetTextAlign(hDC, TA_LEFT|TA_TOP|TA_NOUPDATECP) ;
 
   int nDisplayNum, nLogNum, nCurrentX, nNumLine, nCurrentY ;

   int nNumLines = int(float(Rect.bottom) / 16.0f) ;

   int nLogCurrentLine = Logs.CurrentLine () ;

   if (nNumLines < nLogCurrentLine) nNumLine = nLogCurrentLine - nNumLines ;
   else nNumLine = 0 ;
   nCurrentY = 1 ;

   SCROLLINFO ScrollInfo ;
   ScrollInfo.cbSize = sizeof(SCROLLINFO) ; 
   ScrollInfo.fMask = SIF_PAGE|SIF_POS|SIF_RANGE/*|SIF_DISABLENOSCROLL|SIF_TRACKPOS*/ ; 
   ScrollInfo.nMin = 1 ; 
   ScrollInfo.nMax = nLogCurrentLine ; 
   ScrollInfo.nPage = nNumLines ; 
   ScrollInfo.nPos = nLogCurrentLine ; 
   SetScrollInfo(hWnd, SB_VERT, &ScrollInfo, 1) ;
   for ( ; nNumLine < nLogCurrentLine ; nNumLine ++)
   {
	ExtTextOut(hDC, 1, nCurrentY, 0, NULL, Logs.Line(nNumLine), strlen(Logs.Line(nNumLine)), NULL) ;

	nCurrentY += 16 ;
   }
   EndPaint(hWnd, &lpPaint) ;
   return 0 ;
  }
 break ;
// case WM_SIZE:
// case WM_MOVE:
//  if (!GetWindowRect(hWnd, &LogWin.Rect)) ExitWithError("NormalsWinProc: Cannot GetWindowRect for hWnd") ;
// break ;
 case WM_DESTROY:
//  if (!GetWindowRect(hWnd, &LogWin.Rect)) ExitWithError("NormalsWinProc: Cannot GetWindowRect with hWnd") ;
 return 0 ;
 }
 return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

LRESULT CALLBACK StatusWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
 switch (uMsg) 
 {
 case WM_PAINT:
  RECT rectUpdate ;
  if (GetUpdateRect(hWnd, &rectUpdate, 1))
  {
   HDC hDC ;
   PAINTSTRUCT lpPaint ;
   if ((hDC = BeginPaint(hWnd, &lpPaint)) == NULL) FatalError ("StatusWinProc: Cannot BeginPaint with hWnd") ;
   SetBkColor(hDC, GetSysColor(COLOR_BTNFACE));
   SetTextColor(hDC, GetSysColor(COLOR_BTNTEXT));
   SelectObject(hDC, hFont);
/*   if (TheAlliance->IsOnline()) ExtTextOut(hDC, 5, 2 * nStatusPad, ETO_CLIPPED|ETO_OPAQUE, &rectUpdate, "Online", 6, NULL) ;
    else */ExtTextOut(hDC, 5, 2, ETO_CLIPPED|ETO_OPAQUE, &rectUpdate, "Offline", 7, NULL) ;
   EndPaint(hWnd, &lpPaint) ;
   return 0 ;
  }
 break ;
 case WM_MOVE:
// case WM_SIZE:
//  if (!GetWindowRect(hWnd, &StatusWin.Rect)) ExitWithError("StatusWinProc: Cannot GetWindowRect with hWnd") ;
// return 0;
 case WM_DESTROY:
//  if (!GetClientRect(hWnd, &StatusWin.Rect)) ExitWithError("StatusWinProc: Cannot GetClientRect with hWnd") ;
//  StatusWin.hWnd = 0 ;
 return 0 ;
 }
 return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
 switch(uMsg ) 
 {
 case WM_INITDIALOG:

 return 1 ;

 case WM_COMMAND:
  switch (LOWORD(wParam)) 
  {
  case IDOK: 
   EndDialog(hWnd, 1);
  return 0 ;
  }
  break;
 }
 return 0 ;
}

LRESULT CALLBACK SettingsDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
 switch(uMsg) 
 {
 case WM_INITDIALOG:
 return 1 ;

 case WM_COMMAND:
  switch (LOWORD(wParam)) 
  {
  case IDCANCEL: 
   EndDialog(hWnd, 1);
  return 0 ;
  case IDOK: 
   EndDialog(hWnd, 1);
  return 0 ;
  }
  break;
 }
 return 0 ;
}

LRESULT CALLBACK ExitDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
/* switch(uMsg) 
 {
 case WM_INITDIALOG:
 return 1 ;

 case WM_COMMAND:
  switch (LOWORD(wParam)) 
  {
  case IDC_EXIT_NEVER_ASK:
   if (bDisplayCloseApp == 0) bDisplayCloseApp = 1 ;
   else bDisplayCloseApp = 0 ;
  return 0 ;
  case IDCANCEL:
   bDisplayCloseApp = 1 ;
   EndDialog(hWnd, 1);
  return 0 ;
  case IDOK: 
   DestroyWindow(MainWin.hWnd);
   EndDialog(hWnd, 1);
  return 0 ;
  }
  break;
 }*/
 return 0 ;
}


/*
 case WM_LBUTTONDOWN:
  termLeftButtonDown(wparam, LOWORD(lparam), HIWORD(lparam));
 return 0;
 case WM_LBUTTONUP:
  termLeftButtonUp(wparam, LOWORD(lparam), HIWORD(lparam));
 return 0;
 case WM_LBUTTONDBLCLK:
  termLeftButtonDouble(wparam, LOWORD(lparam), HIWORD(lparam));
 return 0;
 case WM_MBUTTONDOWN:
  termMiddleButtonDown(wparam, LOWORD(lparam), HIWORD(lparam));
 return 0;
 case WM_MBUTTONDBLCLK:
  termMiddleButtonDouble(wparam, LOWORD(lparam), HIWORD(lparam));
 return 0;
 case WM_RBUTTONDOWN:
  termRightButtonDown(wparam, LOWORD(lparam), HIWORD(lparam));
 return 0;
 case WM_RBUTTONUP:
  termRightButtonUp(wparam, LOWORD(lparam), HIWORD(lparam));
 return 0;
 case WM_RBUTTONDBLCLK:
  termRightButtonDouble(wparam, LOWORD(lparam), HIWORD(lparam));
 return 0;
 case WM_MOUSEMOVE:
  termMouseMove(wparam, LOWORD(lparam), HIWORD(lparam));
 return 0;
 case WM_TIMER:
  termTimer();
 return 0;

 case WM_VSCROLL:
  termUseScrollbar(LOWORD(wparam), HIWORD(wparam));
 return 0;

 case WM_PALETTECHANGED:
  if ((HWND)wparam == termGetWnd())
 return 0;
 case WM_QUERYNEWPALETTE:
 	// About to receive window focus - realise our palette
 return termPaletteChanged();
*/
// case WM_CREATE:
		  //  WM_TERM_WHEEL = RegisterWindowMessage("MSWHEEL_ROLLMSG");
// break;
/*
 case WM_DESTROY:
	// Window is being destroyed, clean up
	 
  if (useIniGeometry) 
  {
   termFormatSize(str);
   WritePrivateProfileString("Window", "Size", str, telnetIniFile());
  }
  sprintf(str, "%d", bottomOnOutput);
  WritePrivateProfileString("Terminal", "Bottom On Output", str, telnetIniFile());
  sprintf(str, "%d", autoCopy);
  WritePrivateProfileString("Terminal", "Auto Copy", str, telnetIniFile());
  if (term.font != NULL) DeleteObject(term.font);
  if (termHasPalette) DeleteObject(termPalette);
  if (term.lineList != NULL) 
  {
   for (idx = 0; idx < term.numLinesUsed; idx++) free(term.lineList[idx]);
   free(term.lineList);
  }
  if (term.caretBitmap != NULL) DeleteObject(term.caretBitmap);
  if (termTimerId != 0) KillTimer(termWnd, ID_TERM_TIMER);
 return 0;
 default:
  // Handle WM_TERM_WHEEL here.  Can't do it in a case because it's 
  // not a constant.
        
  if (WM_TERM_WHEEL == message) 
  {
   if ((signed)HIWORD(wparam) < 0) 
    PostMessage(wnd, WM_VSCROLL, MAKEWORD(SB_LINEUP, 0), 0);
    else PostMessage(wnd, WM_VSCROLL, MAKEWORD(SB_LINEDOWN, 0), 0);
  }
  break ;
*/


int SelectStartupServer (HMENU hMenu)
{
// if (!TheAlliance.IsOnline ())
/* {
  if (!TheAlliance->Startup ()) return 0 ;

  CheckMenuItem (hMenu, ID_STATUS_ONLINE, MF_BYCOMMAND|MF_CHECKED) ;
  CheckMenuItem (hMenu, ID_STATUS_OFFLINE, MF_BYCOMMAND|MF_UNCHECKED) ;
  EnableMenuItem(hMenu, ID_STATUS_SHUTDOWN, MF_BYCOMMAND|MF_ENABLED);
  GetClientRect(StatusWin.hWnd, &StatusWin.Rect) ;
  InvalidateRect(StatusWin.hWnd, &StatusWin.Rect, 0) ;
  UpdateWindow(StatusWin.hWnd) ;
 }*/
 return 1 ;
}

int SelectShutdownServer (HMENU hMenu)
{/*
// if (TheAlliance.IsOnline ())
 {
  // dialog box "are you sure" with never ask option
  if (!TheAlliance->Shutdown ()) return 0 ;

  CheckMenuItem (hMenu, ID_STATUS_ONLINE, MF_BYCOMMAND|MF_UNCHECKED) ;
  CheckMenuItem (hMenu, ID_STATUS_OFFLINE, MF_BYCOMMAND|MF_CHECKED) ;
  EnableMenuItem(hMenu, ID_STATUS_SHUTDOWN, MF_BYCOMMAND|MF_GRAYED);
  GetClientRect(StatusWin.hWnd, &StatusWin.Rect) ;
  InvalidateRect(StatusWin.hWnd, &StatusWin.Rect, 0) ;
  UpdateWindow(StatusWin.hWnd) ;
 }*/
 return 1 ;
}