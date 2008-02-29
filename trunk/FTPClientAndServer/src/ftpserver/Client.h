#ifndef __CLIENT_H__
#define __CLIENT_H__

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

//#define WS_VERSION 0x101
#define WS_VERSION 0x202
#include <winsock2.h>

#include <stdio.h>
#include <stdlib.h>

#include "Log.h"

// Sockets
#define MAIN_SOCK 1
#define PASV_SOCK 2
#define PORT_SOCK 3

// Transfer type
#define A_TYPE 1
#define I_TYPE 2

class Client // Client class
{
private:
	// Main connection
	SOCKET m_hMainSock ;
	sockaddr_in m_MainAddr ;

	// Passive connection
	SOCKET m_hPASVSock ;
	sockaddr_in m_PASVAddr ;

	// PORT connection
	SOCKET m_hPORTSock ;
	sockaddr_in m_PORTAddr ;

	SOCKET *m_phDTLSock ;

	// is user logged in or not
	bool m_bUserLoggedIn ;

	// user information
	char *m_szUserName ;
	char *m_szPassword ;
	char *m_szCurrentDir ;

	// tranfer type
	int m_iType ;

	Log *m_pLog ; // logger

	// base send and recieve functions
	int Send(int iSocket, char *szMessage) ;
	int Send(int iSocket, char *szMessage, int iLength) ;
	int Recieve(int iSocket, char *szBuffer, int iLength) ;

	void CloseSocket(SOCKET &hSocket) ; // close socket

public:
	Client(SOCKET &hConnectTo, Log *pLogger) ; 
	~Client() ;

	int RetrieveUserInfo (char *szUserName) ; // retrieve user info from file
	char *GetUserName() { return m_szUserName ; } // return username
	char *GetPassword() { return m_szPassword ; } // return password
	char *GetCurrentDir() { return m_szCurrentDir ; } // return user's current directory

	int GetType() { return m_iType ; } // get transfer type
	void SetType(int iType) { m_iType = iType ; } // set transfer type

	void ChangeCurrentDir(char *szNewDir) ; // change user's current directory

	void UserLogIn() ; // log user in
	void UserLogOut() ; // log user out

	bool UserLoggedIn() { return m_bUserLoggedIn ; } // is user logged in
	bool MainConnected() { return (m_hMainSock != -1) ; } // if the main connection established

	int SendMain(char *szMessage) ; // send over main port
	int SendMain(char *szMessage, int iLength) ;
	int SendPASV(char *szMessage) ; // send over passive port
	int SendPASV(char *szMessage, int iLength) ;
	int SendPORT(char *szMessage) ; // send over PORT port
	int SendPORT(char *szMessage, int iLength) ;

	int RecieveMain(char *szMessage, int iLength) ; // recieve over main port
	int RecievePASV(char *szMessage, int iLength) ; // recieve over passive port
	int RecievePORT(char *szMessage, int iLength) ; // recieve over PORT port

	int PORTTo(char *szConnect) ; // initialize PORT port for DTL
	int ConnectDTL() ; // connect DTL
	SOCKET *GetDTL() { return m_phDTLSock ; } // get current open DTL port
	
/*	
	void OpenPassivePort() ;
//	FILE *AcceptPassive() ;
	void ConnectTo(char *szConnect) ;
	SOCKET AcceptPassive() ;

	*/
} ;

#endif