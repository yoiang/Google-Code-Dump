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


LRESULT CALLBACK StatProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
void SetStatTitle () ;

void CALLBACK DisplayTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) ;
void DisplayBody (HDC hDC, Point ptLocation, Point ptNetForce, PointType dRadius, HBRUSH hBrush, HPEN hPen, char *szName, COLORREF dwTextColor) ;

void CALLBACK CalcTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) ;
/*
// Normals log window procedure
LRESULT CALLBACK LogWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ; 
// Status window procedure
LRESULT CALLBACK StatusWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ; 
*/
// About dialog procedure
LRESULT CALLBACK AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;

LRESULT CALLBACK OpenDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
/*// Exit dialog procedure
LRESULT CALLBACK ExitDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;

// Time updater
VOID CALLBACK UpdateSystemTime(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) ;*/
#endif // __WINPROCS_H__