#include "Client.h"

Client::Client()
{
	if (WSAStartup(WS_VERSION, &WSAData) != 0/* && (Proto = getprotobyname ("tcp")) != NULL*/) 
		m_Log.FatalError("WSAStartup failed") ;
	m_Log.Open("log.txt") ;
	m_hMainSock = -1 ;
	m_hPASVSock = -1 ;
	m_hPORTSock = -1 ;

	m_phDTLSock = NULL ;

	m_iType = A_TYPE ;

	srand( (unsigned)time( NULL ) );
}

Client::~Client()
{
	Disconnect() ;
	WSACleanup() ;
}

void Client::CloseSocket(SOCKET &hSocket)
{
	if (hSocket == -1) return ;
	closesocket(hSocket) ;
	hSocket = -1 ;
}

int Client::Connect(char *szConnectTo)
{
	m_hMainSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_hMainSock == INVALID_SOCKET)
	{
		m_Log.Error("could not create connect socket") ;
		CloseSocket(m_hMainSock) ;
		return 0 ;
	}
	
	int iPort = -1 ;
	int iTrav = 0 ;
	while (szConnectTo[iTrav] != '\0')
	{
		if (szConnectTo[iTrav] == ' ') 
		{
			szConnectTo[iTrav] = '\0' ;
			iPort = iTrav + 1 ;
		}

		iTrav ++ ;
	}
	szConnectTo[iTrav] = '\0' ;
	if (iPort == -1) iPort = 21 ;
	else iPort = atoi(szConnectTo+iPort) ;

	hostent *pHostEntry ;
	if((pHostEntry = gethostbyname(szConnectTo)))
		memcpy((char *)&m_MainAddr.sin_addr,pHostEntry->h_addr, pHostEntry->h_length);
	else if((m_MainAddr.sin_addr.s_addr=inet_addr(szConnectTo))==INADDR_NONE) 
	{
		m_Log.Error("invalid address") ;
		return 0 ;
	}

	m_MainAddr.sin_family = AF_INET ;
	m_MainAddr.sin_port = htons(iPort) ;

	int x = 1;
	if (setsockopt(m_hMainSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&x, sizeof(int)) == SOCKET_ERROR)
		m_Log.Error("could not set connect socket options") ;

	if (connect(m_hMainSock, (const struct sockaddr*)&m_MainAddr, sizeof(m_MainAddr)) == SOCKET_ERROR)
	{
		CloseSocket(m_hMainSock) ;
		m_Log.Error("could not connect") ;
		return 0 ;
	}
	m_Log.AddLine("connected successfully") ;
	return 1 ;	
}

void Client::Disconnect()
{
	if (m_hMainSock != -1)
	{
		Send(MAIN_SOCK, "QUIT", 4) ;
		m_Log.AddLine("disconnected") ;
		CloseSocket(m_hMainSock) ;
	}
	CloseSocket(m_hPASVSock) ;
	CloseSocket(m_hPORTSock) ;
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
	m_Log.AddLine(szBuffer) ;
	int iSent = send(hSocket, szBuffer, iLength+2, 0) ;
//	delete [] szBuffer ;
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
	m_Log.AddLine(szBuffer) ;
	return iRecieved ;
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

void Client::PORTRequest()
{
	int iSize = sizeof(m_PORTAddr) ;
	getsockname(m_hMainSock, (sockaddr*)&m_PORTAddr, &iSize) ;

	if (m_hPORTSock != -1) CloseSocket(m_hPORTSock) ;

	m_hPORTSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_hPORTSock == INVALID_SOCKET)
		m_Log.FatalError("could not create PORT socket") ;

	int x = 1;
	if (setsockopt(m_hPORTSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&x, sizeof(int)) == SOCKET_ERROR)
		m_Log.Error("could not set socket options") ;

	int iPort = rand() % 64000 + 1025 ;
	m_PORTAddr.sin_port = htons(iPort) ;
	if (bind(m_hPORTSock, (const struct sockaddr*)&m_PORTAddr, sizeof(m_PORTAddr)))
		m_Log.FatalError("could not bind port to stream") ;

	char szBuffer[256] ;
	sprintf(szBuffer, "PORT %s,%i,%i", inet_ntoa(m_PORTAddr.sin_addr), iPort/256, iPort%256) ;
	for (int iTrav = 0 ; szBuffer[iTrav] != '\0' ; iTrav++) 
		if (szBuffer[iTrav] == '.') szBuffer[iTrav] = ',' ;
	SendMain(szBuffer) ;
	if (listen(m_hPORTSock, 1) == SOCKET_ERROR)
		m_Log.FatalError("could not set socket to listen") ;

}

int Client::PORTAccept()
{
	int iSize = sizeof(m_PORTAddr) ;
	SOCKET hTemp = accept(m_hPORTSock, (sockaddr*)(&m_PORTAddr), &iSize);
	if (hTemp == INVALID_SOCKET) return 0 ;
	m_hPORTSock = hTemp ;
	return 1 ;
}

void Client::PORTClose()
{
	CloseSocket(m_hPORTSock) ;
}

