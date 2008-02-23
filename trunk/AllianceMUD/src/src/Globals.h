/*

  Globals.h
  Version 0.004.000

*/

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

extern char *szApplicationName ; // Application's name

extern HINSTANCE hCurrentInstance ; // handle of Application's current instance

extern SYSTEMTIME SystemTime ; // Current time

extern HWND hMain ;
extern HWND hLog ;
extern HWND hEntitys ;
extern HWND hEntity ;
extern HWND hStatus ;

extern char szGBuffer[256] ;

extern Entity *pGHeadEnt ;
extern Entity *pGTailEnt ;

extern Entity *pGServers ;


extern WSADATA WSAData ;  // WinSock DLL Info 

extern PROTOENT *Proto ;

extern Log Logs ;

//extern HBRUSH brushStatus ; // Status window brush
//extern TEXTMETRIC tmTextSize ; // Log text size
//extern int nAverageFontWidth ; // Average font width
extern HFONT hFont ; // Font handle
//extern int nStatusPad ; // Number of pixels padding to add to text in status window

extern int bDisplayNormals ; // Display normal messages
extern int bDisplayDebugs ; // Display debug messages
extern int bDisplayErrors ; // Display error messages

extern int bRestoreWindowPositions ; // Restore window positions

extern int bDisplayCloseApp ;
extern int bDisplayCloseServer ; 

extern UINT nSystemTimer ; // Update time
extern UINT nTimerID2 ; // Server's main loop

//extern COLORREF colors [] ; // Standard ascii colors

//extern FieldTypesStruct pApplicationVariables [] ; // Application config variables
#endif // __GLOBALS_H__