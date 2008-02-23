/*

  Globals.cpp
  Version 0.004.000

*/
  
#include "Main.h"

char *szApplicationName = "AllianceMUD" ;

HINSTANCE hCurrentInstance = 0 ;

SYSTEMTIME SystemTime = {0, 0, 0, 0, 0, 0, 0, 0} ;

Entity *pGHeadEnt = NULL ;
Entity *pGTailEnt = NULL ;

Entity *pGServers = NULL ;


char szGBuffer[256] ;

WSADATA WSAData ; // WinSock DLL Info 

PROTOENT *Proto ;

Log Logs(300) ;

HWND hMain = 0 ;
HWND hLog = 0 ;
HWND hEntitys = 0 ;
HWND hEntity = 0 ;
HWND hStatus = 0 ;

HFONT hFont = 0 ;
//HBRUSH brushStatus = 0 ;
//TEXTMETRIC tmTextSize = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; 
//int nAverageFontWidth = 0 ;
//int nStatusPad = 0 ;

int bDisplayNormals = 1 ;
int bDisplayDebugs = 1 ;
int bDisplayErrors = 1 ;

int bDisplayCloseApp = 1 ;
int bDisplayCloseServer = 1 ; 

int bRestoreWindowPositions = 0 ;

UINT nSystemTimer = 0 ;
UINT nTimerID2 = 0 ;
/*
FieldTypesStruct pApplicationVariables [] =
{
 {"bRestoreWindowPositions", GFM(bRestoreWindowPositions), F_BOOL},

 {"bDisplayNormals", GFM(bDisplayNormals), F_BOOL},
 {"bDisplayDebugs", GFM(bDisplayDebugs), F_BOOL},
 {"bDisplayErrors", GFM(bDisplayErrors), F_BOOL},

 {"bDisplayCloseApp", GFM(bDisplayCloseApp), F_BOOL},

 {"if", GFM(bRestoreWindowPositions), F_BOOL},
  {"MainWin.Rect.left", GFM(MainWin.Rect.left), F_LONG},
  {"MainWin.Rect.top", GFM(MainWin.Rect.top), F_LONG},
  {"MainWin.Rect.right", GFM(MainWin.Rect.right), F_LONG},
  {"MainWin.Rect.bottom", GFM(MainWin.Rect.bottom), F_LONG},

//  {"Variables.Rect.left", GFM(Variables.Rect.left), F_LONG},
//  {"Variables.Rect.top", GFM(Variables.Rect.top), F_LONG},
//  {"Variables.Rect.right", GFM(Variables.Rect.right), F_LONG},
//  {"Variables.Rect.bottom", GFM(Variables.Rect.bottom), F_LONG},
 {"endif", NULL, F_IGNORE},
 {NULL, 0, F_END}
} ;*/