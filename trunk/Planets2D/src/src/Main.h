#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#include <commdlg.h>
#include <dlgs.h> 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "resource.h"

#include "Defs.h"

#include "Polygoon.h"
#include "Body.h"
#include "Camera.h"

#include "Math.h"
//#include "Matrix.h"

#include "Files.h"

#include "WinProcs.h"

#include "Globals.h"

// Main.cpp prototypes
void CloseInst () ;
void DeallAll () ;
int InitData (char *szFileName) ;
void UnFatalError (char *szError) ;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow) ;
void FatalError (char *szError) ;

#endif // __MAIN_H__
