#include "Server.h"

HANDLE m_hDiskMutex ;
char *m_szMainDir ;

Server::Server() // initialize member vars and open up main connection port
{
	DeleteFile("log.txt") ;

	m_Log.Open("log.txt") ;	
	m_Log.AddLine("Server starting up") ;

	if (WSAStartup(WS_VERSION, &WSAData) != 0/* && (Proto = getprotobyname ("tcp")) != NULL*/) 
		m_Log.FatalError("WSAStartup failed") ;
	m_Log.AddLine("WSAStartup successful") ;

	if ((m_pServent = getservbyname("ftp", "tcp")) == NULL)
		m_Log.FatalError("getserverbyname failed for ftp") ;

	m_hConnectSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_hConnectSock == INVALID_SOCKET)
		m_Log.FatalError("could not create main socket") ;

	sockaddr_in sockaddr ;
	sockaddr.sin_family = AF_INET ;
    sockaddr.sin_port = m_pServent->s_port ;
	sockaddr.sin_addr.s_addr = INADDR_ANY;

	int x = 1;
	if (setsockopt(m_hConnectSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&x, sizeof(int)) == SOCKET_ERROR)
		m_Log.Error("could not set socket options") ;

	if (bind(m_hConnectSock, (const struct sockaddr*)&sockaddr, sizeof(sockaddr)))
		m_Log.FatalError("could not bind port to stream") ;
	if (listen(m_hConnectSock, SOMAXCONN) == SOCKET_ERROR)
		m_Log.FatalError("could not set socket to listen") ;

	char szBuffer[256] ;
	GetCurrentDirectory(256, szBuffer) ;
	m_szMainDir = new char [strlen(szBuffer) + 1] ;
	strcpy(m_szMainDir, szBuffer) ;

	m_bKeepUp = true ;

    ServiceStarted();
}

Server::~Server() // shut down everything
{
	delete [] m_szMainDir ;

	m_Log.AddLine("Server shutting down") ;
	closesocket(m_hConnectSock) ;
	WSACleanup();

}

void Server::MainLoop () // main service loop
{
	while (m_bKeepUp)
	{
		if (ConnectClient()) HandleClient() ;
	}
}

void Server::Shutdown() // shut down service
{
	m_bKeepUp = false ;
}

int Server::ConnectClient() // create and accept next client
{
	Client *pClient = new Client(m_hConnectSock, &m_Log) ;
	if (!pClient->MainConnected()) 
	{
		delete pClient ;		
		return 0 ;
	}

	::WaitForSingleObject(m_hListMutex, INFINITE);
	m_pClientsList.push_back(pClient) ;
	::ReleaseMutex(m_hListMutex);
	return 1 ;
}

typedef unsigned (WINAPI *THREAD_FUNCTION)(LPVOID pParam);
typedef unsigned *THREAD_ID;

void Server::HandleClient() // start client thread
{
	DWORD dwThreadID;
	HANDLE hThread = (HANDLE)_beginthreadex(0, 0, (THREAD_FUNCTION)(ClientThread), 
											(LPVOID)this, 0, (THREAD_ID)&dwThreadID);

	if (hThread == INVALID_HANDLE_VALUE) 
		m_Log.FatalError("Cannot start client thread") ;
}

DWORD WINAPI Server::ClientThread(LPVOID pThis) // client handling thread, pass messages to message handler
{
	char szBuffer[256] ;
	int iReadIn ;
	Server *pServer = static_cast<Server*>(pThis);

	::WaitForSingleObject(pServer->m_hListMutex, INFINITE);
	std::list<Client*>::iterator LastAdded = --(pServer->m_pClientsList.end()) ;
	::ReleaseMutex(pServer->m_hListMutex);

	SendResponse((*LastAdded), 220, "ready.") ;
	szBuffer[0] = '\0' ;
	while (strcmp(szBuffer, "QUIT") != 0)
	{
		szBuffer[0] = '\0' ;
		iReadIn = (*LastAdded)->RecieveMain(szBuffer, 256) ;
		if (iReadIn == SOCKET_ERROR) break ;
		if (szBuffer[0] != '\0') pServer->m_Log.AddLine(szBuffer) ;
		HandleCommand(*LastAdded, szBuffer, iReadIn) ;
	}

	::WaitForSingleObject(pServer->m_hListMutex, INFINITE);
	delete (*LastAdded) ;
	pServer->m_pClientsList.erase(LastAdded) ;
	::ReleaseMutex(pServer->m_hListMutex);
	return 0 ;
}

void Server::HandleCommand(Client *pClient, char *szCommand, int iLength) // handle messages
{
	int iLen = 0 ;
	while (iLen < iLength)
	{
		if (szCommand[iLen] == ' ')
		{
			szCommand[iLen] = '\0' ;
			break ;
		}
		iLen ++ ;
	}
	if (stricmp(szCommand, "QUIT") == 0)
	{
		return ;
	}
	if ((pClient->GetUserName() == NULL && stricmp(szCommand, "USER") != 0)) // not logged in
	{
		SendResponse(pClient, 530, "Please login with USER and PASS.") ;
		return ;
	}
	if (stricmp(szCommand, "USER") == 0) // user command
	{
		HandleUSER(pClient, szCommand+5) ;	
		return ;
	} else if (stricmp(szCommand, "PASS") == 0) // pass command
	{
		HandlePASS(pClient, szCommand+5) ;
		return ;		
	}
	
	if (!pClient->UserLoggedIn()) // not logged in
	{
		SendResponse(pClient, 530, "Please login with USER and PASS.") ;
		return ;		
	}

	// Call corrisponding command handler
	if (stricmp(szCommand, "HELP") == 0) 
	{
		HandleHELP(pClient, szCommand+5) ;
		return ;		
	} if (stricmp(szCommand, "PWD") == 0) 
	{
		HandlePWD(pClient) ;
		return ;
	} if (stricmp(szCommand, "CWD") == 0) 
	{
		HandleCWD(pClient, szCommand+4) ;
		return ;
	}	else if (stricmp(szCommand, "MKD") == 0)
	{
		HandleMKD(pClient, szCommand+4) ;
		return ;
	}	else if (stricmp(szCommand, "RMD") == 0)
	{
		HandleRMD(pClient, szCommand+4) ;
		return ;
	}	else if (stricmp(szCommand, "CDUP") == 0)
	{
		HandleCDUP(pClient) ;
		return ;
	}	else if (stricmp(szCommand, "DELE") == 0)
	{
		HandleDELE(pClient, szCommand+5) ;
		return ;
	}	else if (stricmp(szCommand, "NOOP") == 0)
	{
		HandleNOOP(pClient) ;
		return ;
//	}	else if (stricmp(szCommand, "PASV") == 0)
//	{
//		HandlePASV(pClient) ;
//		return ;
	}	else if (stricmp(szCommand, "PORT") == 0)
	{
		HandlePORT(pClient, szCommand+5) ;
		return ;
	}	else if (stricmp(szCommand, "LIST") == 0)
	{
		HandleLIST(pClient, 0) ;
		return ;
	}	else if (stricmp(szCommand, "NLST") == 0)
	{
		HandleLIST(pClient, 1) ;
		return ;
	}	else if (stricmp(szCommand, "TYPE") == 0)
	{
		HandleTYPE(pClient, szCommand+5) ;
		return ;
	}	else if (stricmp(szCommand, "RETR") == 0)
	{
		HandleRETR(pClient, szCommand+5) ;
		return ;
	}	else if (stricmp(szCommand, "STOR") == 0)
	{
		HandleSTOR(pClient, szCommand+5) ;
		return ;
	}	else if (stricmp(szCommand, "RNFR") == 0)
	{
		HandleRNFR(pClient, szCommand+5) ;
		return ;
//	}	else if (stricmp(szCommand, "SYST") == 0)
//	{
//		SendResponse(pClient, 215, "UNKNOWN Type: L8") ;
//		return ;
	}	else
	{
		SendResponse(pClient, 500, "Command not understood.") ;
		return ;		
	}
}

void Server::HandleUSER(Client *pClient, char *szUserName) // handle user login
{
	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(m_szMainDir) ;
	int iResult = pClient->RetrieveUserInfo(szUserName) ;
	::ReleaseMutex(m_hDiskMutex);

	if (iResult) SendResponse(pClient, 331, "Password required for user.") ;
	else SendResponse(pClient, 530, "USER not found") ;
}

void Server::HandlePASS(Client *pClient, char *szPassword) // check for valid password
{
	if (strcmp(szPassword, pClient->GetPassword()) != 0)
	{
		pClient->UserLogOut() ;
		SendResponse(pClient, 530, "Login incorrect.") ;
		return ;
	}
	pClient->UserLogIn() ;
	SendResponse(pClient, 230, "User logged in.") ;
}

void Server::HandleHELP(Client *pClient, char *szHelp) // respond with help
{
//	if (szHelp[0] == '\0') 
		SendResponse(pClient, 214, "The following commands are implimented: CDUP CWD DELE HELP MKD NLST NOOP LIST PASS PORT PWD QUIT RETR RMD RNFR RNTO STOR SYST TYPE USER") ;
//	else if (stricmp(szHelp, "HELP") == 0)
//	{
//		SendResponse(pClient, 214, "Syntax: HELP <command>") ;
//	}
}


void Server::HandlePWD(Client *pClient) // respond with current directory
{
	char szBuffer[256] ;
	sprintf(szBuffer, "\"%s\" is current directory.", pClient->GetCurrentDir()) ;
	SendResponse(pClient, 257, szBuffer) ;
}
 
void Server::HandleCWD(Client *pClient, char *szDirectory) // change directory
{
	char szBuffer[256] ;
	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(pClient->GetCurrentDir()) ;
	if (SetCurrentDirectory(szDirectory))
	{
		GetCurrentDirectory(256, szBuffer) ;
		pClient->ChangeCurrentDir(szBuffer) ;
		SendResponse(pClient, 250, "CWD command successful.") ;
	} else
	{
		SendResponse(pClient, 550, "No such file or directory.") ;
	}
	SetCurrentDirectory(m_szMainDir) ;
	::ReleaseMutex(m_hDiskMutex);
}

void Server::HandleMKD(Client *pClient, char *szDirectory) // make directory
{
	char szBuffer[256] ;
	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(pClient->GetCurrentDir()) ;
	if (CreateDirectory(szDirectory, NULL))
	{
		sprintf(szBuffer, "\"%s\\%s\" new directory created.", pClient->GetCurrentDir(), szDirectory) ;
		SendResponse(pClient, 257, szBuffer) ;
	} else
	{
		SendResponse(pClient, 557, "Error creating directory.") ;
	}
	SetCurrentDirectory(m_szMainDir) ;
	::ReleaseMutex(m_hDiskMutex);
}

void Server::HandleRMD(Client *pClient, char *szDirectory) // remove directory
{
	char szBuffer[256] ;
	::WaitForSingleObject(m_hDiskMutex, INFINITE) ;
	SetCurrentDirectory(pClient->GetCurrentDir()) ;

	if (RemoveDirectory(szDirectory))
	{
		sprintf(szBuffer, "\"%s\\%s\" directory removed.", pClient->GetCurrentDir(), szDirectory) ;
		SendResponse(pClient, 257, szBuffer) ;
	} else
	{
		SendResponse(pClient, 557, "Cannot remove directory.") ;
	}
	SetCurrentDirectory(m_szMainDir) ;
	::ReleaseMutex(m_hDiskMutex);
}

void Server::HandleCDUP(Client *pClient) // go up a directory
{
	char szBuffer[256] ;
	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(pClient->GetCurrentDir()) ;
	if (SetCurrentDirectory(".."))
	{
		GetCurrentDirectory(256, szBuffer) ;
		pClient->ChangeCurrentDir(szBuffer) ;
		SendResponse(pClient, 250, "CDUP command successful.") ;
	} else
	{
		SendResponse(pClient, 550, "CDUP command failed.") ;
	}
	SetCurrentDirectory(m_szMainDir) ;
	::ReleaseMutex(m_hDiskMutex);
}

void Server::HandleDELE(Client *pClient, char *szFile) // delete a file
{
	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(pClient->GetCurrentDir()) ;
	if (DeleteFile(szFile))
	{
		SendResponse(pClient, 250, "DELE command successful.") ;
	} else
	{
		SendResponse(pClient, 550, "DELE command failed.") ;
	}
	SetCurrentDirectory(m_szMainDir) ;
	::ReleaseMutex(m_hDiskMutex);
}

void Server::HandleNOOP(Client *pClient) // noop response, often used for keep-alive
{
	SendResponse(pClient, 200, "NOOP response ok.") ;
}
/*
void Server::HandlePASV(Client *pClient)
{
//	pClient->OpenPassivePort() ;
}
*/
void Server::HandlePORT(Client *pClient, char *szConnect) // connect to client requested port
{
	if (!pClient->PORTTo(szConnect))
	{
		SendResponse(pClient, 500, "Connect open PORT.") ;
	}
	SendResponse(pClient, 200, "PORT command successful.") ;
}

void Server::HandleLIST(Client *pClient, bool bBare) // send list over direct transmission line
{
	char szBuffer[256] ;
	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(pClient->GetCurrentDir()) ;

	if (!pClient->ConnectDTL())
	{
		SendResponse(pClient, 500, "Error opening ASCII data connection.") ;
		return ;
	}
	SendResponse(pClient, 150, "Opening ASCII data connection.") ;
	SOCKET *phSocket = pClient->GetDTL() ;

	WIN32_FIND_DATA FindData ;
	HANDLE hFindResult = FindFirstFile("*.*", &FindData) ;
	::ReleaseMutex(m_hDiskMutex);
	while (hFindResult != INVALID_HANDLE_VALUE)
	{
		char *pFileName ;
		if (FindData.cAlternateFileName[0] == '\0')
			pFileName = FindData.cFileName ;
		else pFileName = FindData.cAlternateFileName ;

		if (bBare)
		{
			sprintf(szBuffer, "%s\r\n", pFileName) ;
		}	else
		{
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
				sprintf(szBuffer, "d %i %s\r\n", (FindData.nFileSizeHigh * MAXDWORD) + FindData.nFileSizeLow, pFileName) ;
			else sprintf(szBuffer, "- %i %s\r\n", (FindData.nFileSizeHigh * MAXDWORD) + FindData.nFileSizeLow, pFileName) ;
		}

		printf(szBuffer) ;

		send((*phSocket), szBuffer, strlen(szBuffer), 0) ;
		if (!FindNextFile(hFindResult, &FindData)) break ;
	}
	closesocket((*phSocket));
	(*phSocket) = -1 ;

	SendResponse(pClient, 226, "Transfer complete.") ;

	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(m_szMainDir) ;
	::ReleaseMutex(m_hDiskMutex);
	return ;
}

void Server::HandleTYPE(Client *pClient, char *szType) // change transfer type
{
	if (szType[0] == 'A')
	{
		pClient->SetType(A_TYPE) ;
		SendResponse(pClient, 200, "Type set to A.") ;
	} else if (szType[0] == 'I')
	{
		pClient->SetType(I_TYPE) ;
		SendResponse(pClient, 200, "Type set to I.") ;
	} else
	{
		SendResponse(pClient, 500, "Unknown type.") ;
	}
}

void Server::HandleRETR(Client *pClient, char *szFileName) // retrieve file from server
{
	FILE *pFile ;
	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(pClient->GetCurrentDir()) ;

	if (pClient->GetType() == I_TYPE) pFile = fopen(szFileName, "rb") ;
	else pFile = fopen(szFileName, "rb") ;

	::ReleaseMutex(m_hDiskMutex);

	if (pFile == NULL) 
	{
		SendResponse(pClient, 550, "No such file or directory.") ;
		return ;
	}

	if (!pClient->ConnectDTL())
	{
		SendResponse(pClient, 500, "Error opening connection.") ;
		return ;
	}
	SendResponse(pClient, 150, "Opening data connection.") ;
	SOCKET *phSocket = pClient->GetDTL() ;

	char szBuffer[256] ;
	int iRead ;
	while (!feof(pFile) || iRead == 256)
	{
		iRead = fread(szBuffer, sizeof(char), 256, pFile) ; 
		send((*phSocket), szBuffer, iRead, 0) ;
	}
	closesocket((*phSocket));
	(*phSocket) = -1 ;
	fclose(pFile) ;

	SendResponse(pClient, 226, "Transfer complete.") ;

	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(m_szMainDir) ;
	::ReleaseMutex(m_hDiskMutex);
}

void Server::HandleSTOR(Client *pClient, char *szFileName) // store file on server
{
	FILE *pFile ;
	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(pClient->GetCurrentDir()) ;

	if (pClient->GetType() == I_TYPE) pFile = fopen(szFileName, "wb") ;
	else pFile = fopen(szFileName, "wb") ;

	::ReleaseMutex(m_hDiskMutex);

	if (pFile == NULL) 
	{
		SendResponse(pClient, 550, "No such file or directory.") ;
		return ;
	}

	if (!pClient->ConnectDTL())
	{
		SendResponse(pClient, 500, "Error opening connection.") ;
		return ;
	}
	SendResponse(pClient, 150, "Opening data connection.") ;
	SOCKET *phSocket = pClient->GetDTL() ;
	char cTemp ;
	if (pClient->GetType() == I_TYPE)
		while (cTemp != '\n' && cTemp != 255)
		{
			if (recv((*phSocket), &cTemp, 1, 0) == SOCKET_ERROR) break ;
			if (cTemp != 255) putc(cTemp, pFile) ;
		}
	else
		while (cTemp != 255)
		{
			if (recv((*phSocket), &cTemp, 1, 0) == SOCKET_ERROR) break ;
			if (cTemp != 255) putc(cTemp, pFile) ;
		}
	closesocket((*phSocket));
	(*phSocket) = -1 ;
	fclose(pFile) ;

	SendResponse(pClient, 226, "Transfer complete.") ;

	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(m_szMainDir) ;
	::ReleaseMutex(m_hDiskMutex);
}


void Server::HandleRNFR(Client *pClient, char *szFileName) // rename file command
{
	char szBuffer[256] ;
	::WaitForSingleObject(m_hDiskMutex, INFINITE);
	SetCurrentDirectory(pClient->GetCurrentDir()) ;
	if (GetFileAttributes(szFileName) != 0xFFFFFFFF)
	{
		SendResponse(pClient, 350, "File exists, ready for destination name.") ;
		pClient->RecieveMain(szBuffer, 256) ;
		szBuffer[4] = '\0' ;
		if (stricmp(szBuffer, "RNTO") == 0)
		{
			if (MoveFile(szFileName, szBuffer+5))
			{
				SendResponse(pClient, 250, "RNTO command successful.") ;
			}	else
			{
				SendResponse(pClient, 450, "RNTO command failed.") ;
			}
		}	else
		{
			SendResponse(pClient, 550, "Invalid RNTO command") ;
		}
	}	else
	{
		SendResponse(pClient, 550, "File does not exist.") ;
	}
	SetCurrentDirectory(m_szMainDir) ;
	::ReleaseMutex(m_hDiskMutex);
}
/*
	char szBuffer[256] ;
	int iRecieved ;
	while (iRecieved == 256)
	{
		iRecieved = recv((*phSocket), szBuffer, 256, 0) ;
		fwrite(szBuffer, sizeof(char), iRecieved, pFile
	}
*/

void Server::SendResponse(Client *pClient, int iMessageCode, char *szMessage) // send response with code through main port
{
	char szBuffer[256] ;
	sprintf(szBuffer, "%i %s", iMessageCode, szMessage) ;
	pClient->SendMain(szBuffer) ;
}
