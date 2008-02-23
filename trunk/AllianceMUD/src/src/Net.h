/*

  Net.h
  Version 0.004.000

*/

#ifndef __NET_H__
#define __NET_H__

#define MW_CONNECTED 200 // Connection request
#define MW_DATAREADY 201 // Data ready from transmision

SOCKET BindSocket(int nAssignPort, int nNumConnect) ;
Entity* ConnectClient (SOCKET hSocket) ;
void DisconnectClient (Entity *pClient) ;


#endif //__NET_H__