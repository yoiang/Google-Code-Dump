#ifndef __SERVER_H__
#define __SERVER_H__

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

//#define WS_VERSION 0x101
#define WS_VERSION 0x202
#include <winsock2.h>

#include <process.h>

#include <list>

#include <stdlib.h>

#include "Service.h"

#include "Log.h"
#include "Client.h"
#include "FTPServer.h"

class Server
{
private:	
	WSADATA WSAData ;

	SOCKET m_hConnectSock ;

	Log m_Log ;

	HANDLE m_hListMutex ;
	std::list<Client*> m_pClientsList ;

	SERVENT *m_pServent ;

	bool m_bKeepUp ;
public:
	Server() ;
	~Server() ;

	int ConnectClient() ;
	void HandleClient() ;

	void MainLoop() ;
	void Shutdown() ;

	static DWORD WINAPI ClientThread(LPVOID pThis) ;

	static void HandleCommand(Client *pClient, char *szMessage, int iLength) ;

	static void HandleUSER(Client *pClient, char *szUserName) ;
	static void HandlePASS(Client *pClient, char *szPassword) ;
	static void HandleHELP(Client *pClient, char *szHelp) ;
	static void HandlePWD(Client *pClient) ;
	static void HandleCWD(Client *pClient, char *szDirectory) ;
	static void HandleMKD(Client *pClient, char *szDirectory) ;
	static void HandleRMD(Client *pClient, char *szDirectory) ;
	static void HandleCDUP(Client *pClient) ;
	static void HandleDELE(Client *pClient, char *szFile) ;
	static void HandleNOOP(Client *pClient) ;
//	static void HandlePASV(Client *pClient) ;
	static void HandlePORT(Client *pClient, char *szConnect) ;
	static void HandleLIST(Client *pClient, bool bBare) ;
	static void HandleTYPE(Client *pClient, char *szType) ;
	static void HandleRETR(Client *pClient, char *szFileName) ;
	static void HandleSTOR(Client *pClient, char *szFileName) ;
	static void HandleRNFR(Client *pClient, char *szFileName) ;

	static void SendResponse(Client *pClient, int iMessageCode, char *szMessage) ;
} ;										  

#endif