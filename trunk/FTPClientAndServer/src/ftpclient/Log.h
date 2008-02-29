#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <process.h>

class Log
{
private:
	FILE *m_pLogFile ;
	HANDLE m_hLogMutex ;
public:
	Log() ;
	Log(char *szFileName) ;
	~Log() ;
	
	void Open(char *szFileName) ;
	void Close() ;

	void AddLine(char *szLine) ;
	void Error(char *szError) ;
	void FatalError(char *szError) ;
} ;

#endif