#ifndef __CLIENT_H__
#define __CLIENT_H__

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

//#define WS_VERSION 0x101
#define WS_VERSION 0x202
#include <winsock2.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Log.h"

#define MAIN_SOCK 1
#define PASV_SOCK 2
#define PORT_SOCK 3

#define A_TYPE 1
#define I_TYPE 2

class Client
{
private:
	WSADATA WSAData ;

	SOCKET m_hMainSock ;
	sockaddr_in m_MainAddr ;

	SOCKET m_hPASVSock ;
	sockaddr_in m_PASVAddr ;

	SOCKET m_hPORTSock ;
	sockaddr_in m_PORTAddr ;

	SOCKET *m_phDTLSock ;

	int m_iType ;

	Log m_Log ;

	int Send(int iSocket, char *szMessage) ;
	int Send(int iSocket, char *szMessage, int iLength) ;
	int Recieve(int iSocket, char *szBuffer, int iLength) ;

	void CloseSocket(SOCKET &hSocket) ;

public:
	Client() ;
	~Client() ;

	int Connect(char *szConnectTo) ;
	void Disconnect() ;

	int GetType() { return m_iType ; }
	void SetType(int iType) { m_iType = iType ; }

	int SendMain(char *szMessage) ;
	int SendMain(char *szMessage, int iLength) ;
	int SendPASV(char *szMessage) ;
	int SendPASV(char *szMessage, int iLength) ;
	int SendPORT(char *szMessage) ;
	int SendPORT(char *szMessage, int iLength) ;

	int RecieveMain(char *szMessage, int iLength) ;
	int RecievePASV(char *szMessage, int iLength) ;
	int RecievePORT(char *szMessage, int iLength) ;

	void PORTRequest() ;
	int PORTAccept() ;
	SOCKET GetPORT() { return m_hPORTSock ; }
	void PORTClose() ;
} ;

#endif