/*

  Log.h
  Version 0.004.000

*/

#ifndef __LOG_H__
#define __LOG_H__

class Log
{
private:
 char **pszLog ;
 int nNumLines ;
 int nCurrentLine ;

public:
 Log () ;
 Log (int nAssignNumLines) ;
 ~Log () ;

 void Make (int nAssignNumLines) ;
 void Delete () ;
 void Clear () ;
 void AddLine (char *szLine) ;
 void AddLine (char *szLine1, char *szLine2) ;
 const char* Line (int nIndex) ;
 int NumLines () ;
 int CurrentLine () ;
} ;

#endif // __LOG_H__