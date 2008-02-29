#include "Client.h"

Client::Client(SOCKET &hConnectTo, Log *pLog)
{
	m_pLog = pLog ;

	m_bUserLoggedIn = false ;

	int iSize = sizeof(m_MainAddr) ;
	m_hMainSock = accept(hConnectTo, (sockaddr*)(&m_MainAddr), &iSize);
	if (m_hMainSock== INVALID_SOCKET)
	{
		m_pLog->Error("could not accept connection") ;
		CloseSocket(m_hMainSock) ;
		return ;
	}

	if (getpeername(m_hMainSock, (sockaddr*)&m_MainAddr, &iSize) == SOCKET_ERROR) 
		m_pLog->FatalError("could not get peer's name") ;
		
	m_szUserName = NULL ;
	m_szPassword = NULL ;
	m_szCurrentDir = NULL ;

	m_hPASVSock = -1 ;
	m_hPORTSock = -1 ;

	m_phDTLSock = NULL ;

	char szBuffer[256] ;
	sprintf(szBuffer, "Client connected from %s", inet_ntoa(m_MainAddr.sin_addr)) ;
	m_pLog->AddLine(szBuffer) ;

	m_iType = A_TYPE ;
}

Client::~Client()
{
	UserLogOut() ;

	CloseSocket(m_hMainSock) ;
	CloseSocket(m_hPASVSock) ;
	CloseSocket(m_hPORTSock) ;
	
	char szBuffer[256] ;
	sprintf(szBuffer, "Client from %s disconnected", inet_ntoa(m_MainAddr.sin_addr)) ;
	m_pLog->AddLine(szBuffer) ;

	m_pLog->Close() ;
	m_pLog->Open("log.txt") ;
}

void Client::CloseSocket(SOCKET &hSocket)
{
	if (hSocket == -1) return ;
	closesocket(hSocket) ;
	hSocket = -1 ;
}

void Client::UserLogIn() 
{
	m_bUserLoggedIn = true ;
}

void Client::UserLogOut()
{
	m_bUserLoggedIn = false ;
	if (m_szUserName != NULL)
	{
		delete [] m_szUserName ;
		m_szUserName = NULL ;
	}
	if (m_szPassword != NULL)
	{
		delete [] m_szPassword ;
		m_szPassword = NULL ;
	}
	if (m_szCurrentDir != NULL)
	{
		delete [] m_szCurrentDir ;
		m_szCurrentDir = NULL ;
	}
}

int Client::Send(int iSocket, char *szMessage) 
{
	return Send(iSocket, szMessage, strlen(szMessage)) ;
}

int Client::Send(int iSocket, char *szMessage, int iLength) 
{
	SOCKET hSocket ;
	switch (iSocket)
	{
	case MAIN_SOCK:
		hSocket = m_hMainSock ;
	break ;
	case PASV_SOCK:
		hSocket = m_hPASVSock ;
	break ;
	case PORT_SOCK:
		hSocket = m_hPORTSock ;
	break ;
	default: hSocket = m_hMainSock ;
	}

	char *szBuffer = new char [iLength + 4] ;
	sprintf(szBuffer, "%s\r\n", szMessage) ;
	m_pLog->AddLine(szBuffer) ;
	int iSent = send(hSocket, szBuffer, iLength+2, 0) ;
	delete [] szBuffer ;
	return iSent ;
}

int Client::Recieve(int iSocket, char *szBuffer, int iLength) 
{
	SOCKET hSocket ;
	switch (iSocket)
	{
	case MAIN_SOCK:
		hSocket = m_hMainSock ;
	break ;
	case PASV_SOCK:
		hSocket = m_hPASVSock ;
	break ;
	case PORT_SOCK:
		hSocket = m_hPORTSock ;
	break ;
	default: hSocket = m_hMainSock ;
	}

	int iRecieved = recv(hSocket, szBuffer, iLength, 0) ;
	int iLen = 0 ;
	while (iLen < iRecieved-1)
	{
		if (szBuffer[iLen] == '\r' && szBuffer[iLen+1] == '\n')
		{
			szBuffer[iLen] = '\0' ;
			szBuffer[iLen] = '\0' ;
			break ;
		}
		iLen ++ ;

	}
	return iRecieved ;
}

int Client::RetrieveUserInfo(char *szUserName)
{
	char szBuffer[256] ;
	char *szFile = new char [12 + strlen(szUserName)] ;
	strcpy(szFile, "users\\") ;
	strcat(szFile, szUserName) ;
	strcat(szFile, ".usr") ;

	FILE *pUserFile = fopen(szFile, "r") ;
	if (pUserFile == NULL) return 0 ;
	delete [] szFile ;

	m_szUserName = new char [strlen(szUserName) + 1] ;
	strcpy(m_szUserName, szUserName) ;

	fscanf(pUserFile, "%255[^\n\t\0]\n", szBuffer) ;
	m_szPassword = new char [strlen(szBuffer) + 1] ;
	strcpy(m_szPassword, szBuffer) ;

	fscanf(pUserFile, "%255[^\n\t\0]\n", szBuffer) ;
	m_szCurrentDir = new char [strlen(szBuffer) + 1] ;
	strcpy(m_szCurrentDir, szBuffer) ;
	fclose(pUserFile) ;

	return 1 ;
}

void Client::ChangeCurrentDir(char *szNewDir)
{
	if (m_szCurrentDir != NULL) delete [] m_szCurrentDir ;
	m_szCurrentDir = new char [strlen(szNewDir) + 1] ;
	strcpy(m_szCurrentDir, szNewDir) ;
}

int Client::SendMain(char *szMessage)
{
	return Send(MAIN_SOCK, szMessage) ;
}

int Client::SendMain(char *szMessage, int iLength)
{
	return Send(MAIN_SOCK, szMessage, iLength) ;
}

int Client::SendPASV(char *szMessage)
{
	return Send(PASV_SOCK, szMessage) ;
}

int Client::SendPASV(char *szMessage, int iLength) 
{
	return Send(PASV_SOCK, szMessage, iLength) ;
}

int Client::SendPORT(char *szMessage) 
{
	return Send(PORT_SOCK, szMessage) ;
}

int Client::SendPORT(char *szMessage, int iLength) 
{
	return Send(PORT_SOCK, szMessage, iLength) ;
}


int Client::RecieveMain(char *szMessage, int iLength)
{
	return Recieve(MAIN_SOCK, szMessage, iLength) ;
}

int Client::RecievePASV(char *szMessage, int iLength) 
{
	return Recieve(PASV_SOCK, szMessage, iLength) ;
}

int Client::RecievePORT(char *szMessage, int iLength) 
{
	return Recieve(PORT_SOCK, szMessage, iLength) ;
}

int Client::PORTTo(char *szConnect)
{
	int iCount = 0 ;
	int iPort, iPort2 ;
	int iTrav = 0 ;
	while (szConnect[iTrav] != '\0')
	{
		if (szConnect[iTrav] == ',') 
		{
			szConnect[iTrav] = '.' ;
			iCount ++ ;
			if (iCount == 4) 
			{
				szConnect[iTrav] = '\0' ;
				iPort = iTrav+1 ;
			}
			if (iCount == 5)
			{
				szConnect[iTrav] = '\0' ;
				iPort2 = iTrav+1 ;
			}
		}
		iTrav ++ ;
	}
	szConnect[iTrav] = '\0' ;
	iPort = atoi(szConnect+iPort) ;
	iPort2 = atoi(szConnect+iPort2) ;
	
	m_PORTAddr.sin_family = AF_INET ;
	m_PORTAddr.sin_port = htons(256*iPort + iPort2) ;
	m_PORTAddr.sin_addr.s_addr=inet_addr(szConnect) ;

	m_hPORTSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_hPORTSock == INVALID_SOCKET)
	{
		m_pLog->Error("could not create PORT socket") ;
		CloseSocket(m_hPORTSock) ;
		return 0 ;
	}
	
	int x = 1;
	if (setsockopt(m_hPORTSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&x, sizeof(int)) == SOCKET_ERROR)
		m_pLog->Error("could not set PORT socket options") ;
	
	return 1 ;
}

int Client::ConnectDTL()
{
	if (m_hPORTSock != -1)
	{
		if (connect(m_hPORTSock, (const struct sockaddr*)&m_PORTAddr, sizeof(m_PORTAddr)) == SOCKET_ERROR)
		{
			CloseSocket(m_hPORTSock) ;
			m_pLog->Error("could not connect PORT") ;
		}
		else 
		{
			m_pLog->AddLine("PORT connected") ;
			m_phDTLSock = &m_hPORTSock ;
			return PORT_SOCK ;
		}
	}
	return 0 ;
}

/*

void Client::OpenPassivePort()
{
	char szBuffer[256] ;
	if (m_hPassiveSock >= 0) closesocket(m_hPassiveSock) ;

	m_hPassiveSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_hPassiveSock == INVALID_SOCKET) 
	{
		Send(425, "Cannot open passive connection", 30) ;
		return ;
	}
	m_iPassivePort = rand() % 64511 + 1025 ;
	int iP1 = m_iPassivePort / 256 ;
	int iP2 = m_iPassivePort % 256 ;

	int iSize = sizeof(m_PassiveAddr) ;
	if (getsockname(m_hConnectedTo, (sockaddr*)(&m_PassiveAddr), &iSize) == SOCKET_ERROR)
		m_pLog->FatalError("could not get local name") ;

	m_PassiveAddr.sin_port = htons(m_iPassivePort) ;
	int x = 1;
	setsockopt(m_hPassiveSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&x, sizeof(int)) ;
	while (bind(m_hPassiveSock, (const struct sockaddr*)&m_PassiveAddr, sizeof(m_PassiveAddr)) != 0)
	{
		m_iPassivePort = rand() % 64511 + 1025 ;
		iP1 = m_iPassivePort / 256 ;
		iP2 = m_iPassivePort % 256 ;

		m_PassiveAddr.sin_port = htons(m_iPassivePort) ;
	}
	
	if (getsockname(m_hPassiveSock, (struct sockaddr *) &m_PassiveAddr, &iSize) == SOCKET_ERROR || 
		listen(m_hPassiveSock, 1) == SOCKET_ERROR)
	{
		closesocket(m_hPassiveSock) ;
		m_hPassiveSock = -1 ;
		Send(425, "Cannot open passive connection", 30) ;
		return ;
	}
	
	sprintf(szBuffer, "Entering Passive Mode (%i,%i,%i,%i,%i,%i).", 
		m_PassiveAddr.sin_addr.S_un.S_un_b.s_b1,
		m_PassiveAddr.sin_addr.S_un.S_un_b.s_b2,
		m_PassiveAddr.sin_addr.S_un.S_un_b.s_b3,
		m_PassiveAddr.sin_addr.S_un.S_un_b.s_b4,
		iP1,
		iP2) ;
	Send(227, szBuffer) ;
}

//FILE *Client::AcceptPassive()
SOCKET Client::AcceptPassive()
{
	SOCKET Accepted ;

	sockaddr_in From ;
	int iFrom = sizeof(From) ;

	if (m_hPassiveSock < 0)
	{
		Send(425, "Passive port not open", 28) ;
		return m_hConnectedTo ;
	}

	if ((Accepted = accept(m_hPassiveSock, (sockaddr*)(&From), &iFrom)) == INVALID_SOCKET)
	{
//		Send(425, "Cannot build data connection", 28) ;
		closesocket(m_hPassiveSock) ;
		closesocket(Accepted) ;
		m_hPassiveSock = -1 ;
		return m_hConnectedTo ;
	}
	closesocket(m_hPassiveSock) ;

/*		if (ntohs(From.sin_port) < IPPORT_RESERVED)
		{
			pClient->Send(425, "Cannot build data connection", 28) ;
			closesocket(Accepted) ;
			m_hPassiveSock = -1 ;
			return ;
		}
		if (From.sin_addr.s_addr != m_SockAddr.sin_addr.s_addr) 
		{
			pClient->Send(435, "Cannot build data connection", 28) ;
			closesocket(Accepted) ;
			m_hPassiveSock = -1 ;
			return ;
		}
*/
/*	m_hPassiveSock = Accepted ;

	Send(150, "Opening ASCII data connection", 28) ;
	return m_hPassiveSock ;
//	FILE *pFile = fdopen(m_hPassiveSock, "w") ;
//	if (pFile == NULL)
//	{
//		closesocket(m_hPassiveSock) ;
//		closesocket(Accepted) ;
//		m_hPassiveSock = -1 ;
//		Send(425, "Cannot build data connection", 28) ;
//		return NULL ;
//	}
//	return pFile ;
}

*/