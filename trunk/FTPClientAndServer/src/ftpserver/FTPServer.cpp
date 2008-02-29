#include "FTPServer.h"

Server FTPServer ;

void Start ()
{
	FTPServer.MainLoop() ;
}

void Stop ()
{
	FTPServer.Shutdown() ;
    ServiceStopped();
}
