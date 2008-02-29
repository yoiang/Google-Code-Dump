#include "Log.h"

Log::Log()
{
	m_pLogFile = NULL ;
}

Log::Log(char *szFileName)
{
	m_pLogFile = NULL ;
	Open(szFileName) ;
}

Log::~Log()
{
	Close() ;
}

void Log::Open(char *szFileName)
{
    WaitForSingleObject(m_hLogMutex, INFINITE);
	Close() ;
	m_pLogFile = fopen(szFileName, "a") ;
	ReleaseMutex(m_hLogMutex);
}

void Log::AddLine(char *szLine)
{
    WaitForSingleObject(m_hLogMutex, INFINITE);
	fprintf(m_pLogFile, "%s\n", szLine) ;
	printf("%s\n", szLine) ;
	ReleaseMutex(m_hLogMutex);
}

void Log::Error(char *szError)
{
    WaitForSingleObject(m_hLogMutex, INFINITE);
	fprintf(m_pLogFile, "ERROR: %s\n", szError) ;
	printf("ERROR: %s\n", szError) ;
	ReleaseMutex(m_hLogMutex);
}

void Log::FatalError(char *szError)
{
    WaitForSingleObject(m_hLogMutex, INFINITE);
	fprintf(m_pLogFile, "FATALERROR: %s\n", szError) ;
	printf("FATALERROR: %s\n", szError) ;
	ReleaseMutex(m_hLogMutex);

	Close() ;

	ServiceStartAborted() ;
}

void Log::Close()
{
    WaitForSingleObject(m_hLogMutex, INFINITE);
	if (m_pLogFile != NULL) 
	{
		fclose(m_pLogFile) ;
		m_pLogFile = NULL ;
	}
	ReleaseMutex(m_hLogMutex);
}
