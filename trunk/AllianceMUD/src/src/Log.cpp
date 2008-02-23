/*

  Log.cpp
  Version 0.004.000

*/

#include "Main.h"

Log::Log ()
{
 pszLog = NULL ;
 nNumLines = 0 ;
 nCurrentLine = 0 ;
}

Log::Log (int nAssignNumLines)
{
 pszLog = new char* [nAssignNumLines] ;
#ifdef MEM_DEBUG
 if (pszLog == NULL) FatalError("Log::Make - Heap overflow") ;
#endif // MEM_DEBUG
 nNumLines = nAssignNumLines ;
 for (nCurrentLine = 0 ; nCurrentLine < nNumLines ; nCurrentLine ++)
  pszLog[nCurrentLine] = NULL ;
 nCurrentLine = 0 ;
}

Log::~Log ()
{
 for (nCurrentLine = 0 ; (nCurrentLine < nNumLines && pszLog[nCurrentLine] != NULL) ; nCurrentLine ++)
  delete [] pszLog [nCurrentLine] ;
 delete [] pszLog ;
}

void Log::Make (int nAssignNumLines)
{
 if (pszLog != NULL) 
 {
  for (nCurrentLine = 0 ; (nCurrentLine < nNumLines && pszLog[nCurrentLine] != NULL) ; nCurrentLine ++)
   delete [] pszLog [nCurrentLine] ;
  delete [] pszLog ;
 }
 pszLog = new char* [nAssignNumLines] ;
#ifdef MEM_DEBUG
 if (pszLog == NULL) FatalError("Log::Make - Heap overflow") ;
#endif // MEM_DEBUG
 nNumLines = nAssignNumLines ;
 for (nCurrentLine = 0 ; nCurrentLine < nNumLines ; nCurrentLine ++)
  pszLog[nCurrentLine] = NULL ;
 nCurrentLine = 0 ;
}

void Log::Delete ()
{
 if (pszLog == NULL) return ;
 for (nCurrentLine = 0 ; (nCurrentLine < nNumLines && pszLog[nCurrentLine] != NULL) ; nCurrentLine ++)
  delete [] pszLog [nCurrentLine] ;
 delete [] pszLog ;
 pszLog = NULL ;
 nNumLines = 0 ;
}

void Log::Clear ()
{
 for (nCurrentLine = 0 ; (nCurrentLine < nNumLines && pszLog[nCurrentLine] != NULL) ; nCurrentLine ++)
 {
  delete [] pszLog[nCurrentLine] ;
  pszLog[nCurrentLine] = NULL ;
 }
 nCurrentLine = 0 ;
}

void Log::AddLine (char *szLine)
{
 if (nCurrentLine == nNumLines) Clear () ;

 pszLog[nCurrentLine] = new char [strlen(szLine) + 29] ;
#ifdef MEM_DEBUG
 if (pszLog[nCurrentLine] == NULL) FatalError("Log::Addline - Heap overflow") ;
#endif // MEM_DEBUG
 sprintf (pszLog[nCurrentLine], 
          "[%u/%u/%u %u:%u:%u:%u] %s", 
		  SystemTime.wMonth, 
		  SystemTime.wDay,
		  SystemTime.wYear,
		  SystemTime.wHour,
		  SystemTime.wMinute,
		  SystemTime.wSecond,
		  SystemTime.wMilliseconds, 
		  szLine) ;

 nCurrentLine ++ ;

 RECT Rect ;
 GetClientRect (hLog, &Rect) ;
 InvalidateRect(hLog, &Rect, 1) ;
}

void Log::AddLine (char *szLine1, char *szLine2)
{
 if (nCurrentLine == nNumLines) Clear () ;

 pszLog[nCurrentLine] = new char [strlen(szLine1) + strlen(szLine2) + 29] ;
#ifdef MEM_DEBUG
 if (pszLog[nCurrentLine] == NULL) FatalError("Log::Addline - Heap overflow") ;
#endif // MEM_DEBUG
 sprintf (pszLog[nCurrentLine], 
          "[%u/%u/%u %u:%u:%u:%u] %s%s", 
		  SystemTime.wMonth, 
		  SystemTime.wDay,
		  SystemTime.wYear,
		  SystemTime.wHour,
		  SystemTime.wMinute,
		  SystemTime.wSecond,
		  SystemTime.wMilliseconds, 
		  szLine1, 
		  szLine2) ;

 nCurrentLine ++ ;

 RECT Rect ;
 GetClientRect (hLog, &Rect) ;
 InvalidateRect(hLog, &Rect, 1) ;
}

const char* Log::Line(int nIndex)
{ return pszLog[nIndex] ; }

int Log::NumLines ()
{ return nNumLines ; }

int Log::CurrentLine ()
{ return nCurrentLine ; }