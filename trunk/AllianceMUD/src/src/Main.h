/*

  Main.h 
  Version 0.004.000

*/
  
#ifndef __MAIN_H__
#define __MAIN_H__

#define MEM_DEBUG

#define STRICT // strict Windows type checking
#include <windows.h> // WINAPI functions

//#define _WIN32_IE 0x0200
#define _WIN32_IE 0x0400
#include <commctrl.h> // common windows controls

//#define WS_VERSION 0x101
#define WS_VERSION 0x202
#include <winsock.h> // WinSock functions

//#include <stdlib.h>
//#include <stdarg.h>
//#include <conio.h>
//#include <ctype.h>
//#include <errno.h>
//#include <time.h>
#include <string.h> // null terminated string functions
						  // strlen
//#include <alloc.h> // malloc and free (NOOOOOOOOOOOOOOOOOOOO)
//#include <fcntl.h>
//#include <signal.h>
#include <math.h> // pow
#include <stdio.h> // stream I/O functions

/*
#include <sys/types.h>
#define NOCRYPT
#define index strchr
#define rindex strrchr
*/

//#pragma warning( disable: 4706)
//#ifndef _DEBUG
//#pragma intrinsic(strcat, strcmp, strcpy, strlen)
//#endif 

#include "resource.h"

#include "Defs.h"

#include "Queue.h"
#include "Log.h"
#include "Files.h"

#include "Net.h"

#include "Item.h"
#include "Client.h"
#include "Mob.h"
#include "Exit.h"
#include "Room.h"
#include "Body.h"
#include "System.h"
#include "Plane.h"
#include "Server.h"
#include "Spawn.h"
#include "Commands.h"
#include "Entity.h"

#include "Globals.h"
#include "WinProcs.h"

void FatalError (char *szError) ;

#endif // __MAIN_H__