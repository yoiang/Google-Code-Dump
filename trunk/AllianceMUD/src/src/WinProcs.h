/*

  WinProcs.h
  Version 0.004.000

*/

#ifndef __WINPROCS_H__
#define __WINPROCS_H__

// Main window procedure
LRESULT CALLBACK MainProc(HWND hWnd,       // handle of window
                          UINT uMsg,     // message identifier
						  WPARAM wParam,   // first message parameter
						  LPARAM lParam) ; // second message parameter

// Normals log window procedure
LRESULT CALLBACK LogWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ; 
// Status window procedure
LRESULT CALLBACK StatusWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ; 

// About dialog procedure
LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
// Settings dialog procedure
LRESULT CALLBACK SettingsDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
// Exit dialog procedure
LRESULT CALLBACK ExitDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;

// Main server loop caller
VOID CALLBACK ServerMainLoop(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) ;
// Time updater
VOID CALLBACK UpdateSystemTime(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) ;
#endif // __WINPROCS_H__