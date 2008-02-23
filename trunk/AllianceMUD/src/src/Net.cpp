/*

  Net.cpp
  Version 0.004.000

*/

#include "Main.h"

SOCKET BindSocket(int nAssignPort, int nNumConnect)
{
// char szHostName[64];
 sockaddr_in SocketAddress ;
 int x = 1;
 SOCKET hSocket;

// gethostname(szHostName, sizeof(szHostName));

 if ((hSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
 {
  closesocket(hSocket) ;
  return 0 ;
 }

 if (setsockopt(hSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&x, sizeof(int)) < 0)
 {
  closesocket(hSocket) ;
  return 0 ;
 }

 SocketAddress.sin_family = AF_INET ;
 SocketAddress.sin_port = htons(nAssignPort) ;
 SocketAddress.sin_addr.S_un.S_addr = '\0' ;
 SocketAddress.sin_zero[0] = '\0' ;

 if (bind(hSocket, (const struct sockaddr*)&SocketAddress, sizeof(SocketAddress)) == SOCKET_ERROR)
 {
  closesocket(hSocket) ;
  return 0 ;
 }
 if (listen(hSocket, nNumConnect) == SOCKET_ERROR)
 {
//  int nError = WSAGetLastError() ;
  closesocket(hSocket) ;
  return 0 ;
 }

 // Set up window message to indicate connection 
 if (WSAAsyncSelect(hSocket, hMain, MW_CONNECTED, FD_ACCEPT) == SOCKET_ERROR)
 {
  closesocket(hSocket);
  return 0 ;
 }
 
 return hSocket ;
}

Entity* ConnectClient (SOCKET hSocket)
{
// WSAAccept
 SOCKET hAccepted ;
 if ((hAccepted = accept(hSocket, NULL, NULL)) == INVALID_SOCKET) return NULL ;

 Entity *pClient = CreateEntity(E_MOB) ;
 pClient->uMob.bClient = 1 ;
 pClient->uMob.pClient = new Client ;
#ifdef MEM_DEBUG
 if (pClient->uMob.pClient == NULL) FatalError("ConnectClient - Heap overflow") ;
#endif // MEM_DEBUG
 pClient->uMob.pClient->hSocket = hAccepted ;

 if(WSAAsyncSelect(hAccepted, hMain, MW_DATAREADY, FD_READ|FD_WRITE|FD_CLOSE) == SOCKET_ERROR)
 {
  closesocket(hAccepted);
  delete pClient->uMob.pClient ;
  DeleteEntity(pClient) ;
  return NULL;
 }

 pClient->pOwner = pGServers->pCPlane->pCSystem->pCBody->pNext->pNext->pCRoom->pNext ;

 if (pClient->pOwner->pCMob != NULL)
 {
  pClient->pOwner->pCMob->pLast = pClient ;
  pClient->pNext = pClient->pOwner->pCMob ;
 }
 pClient->pOwner->pCMob = pClient ;

 pClient->szName = new char [strlen("Bob") + 1] ;
 sprintf(pClient->szName, "%s", "Bob") ;

 TVITEM hTVI ;
 TVINSERTSTRUCT hTVIns ;

 hTVI.mask = TVIF_TEXT | TVIF_PARAM ; //| TVIF_IMAGE | TVIF_SELECTEDIMAGE ;

 hTVI.pszText = new char [strlen (pClient->szName) + 6] ;
#ifdef MEM_DEBUG
 if (hTVI.pszText == NULL) FatalError("ReadScript - Heap overflow") ;
#endif // MEM_DEBUG
 sprintf (hTVI.pszText, "%s", pClient->szName) ;
 hTVI.cchTextMax = strlen (pClient->szName) ;

// hTVI.iImage = NULL ;
// hTVI.iSelectedImage = NULL ;
 hTVIns.item = hTVI ;
 if (pClient->pOwner == NULL)
 {
  hTVIns.hInsertAfter = TVI_LAST ;
  hTVIns.hParent = TVI_ROOT ;
 } else
 {
  hTVIns.hInsertAfter = TVI_LAST ;
  hTVIns.hParent = pClient->pOwner->hTreeItem ;
 }

 pClient->hTreeItem = (HTREEITEM) SendMessage(hEntitys, TVM_INSERTITEM, 0, (LPARAM)(LPTVINSERTSTRUCT) &hTVIns) ;
#ifdef MEM_DEBUG
 if (pClient->hTreeItem == 0) Logs.AddLine("ReadNumScripts - SendMessage(TVM_INSERTITEM) failed") ;
#endif // MEM_DEBUG

 pClient->Spawn (pClient) ;

 Entity *pTrav = pClient->pOwner->pCMob ;
 while (pTrav != NULL)
 {
  if (pTrav->uMob.bClient && pTrav != pClient)
  {
   send(pTrav->uMob.pClient->hSocket, "\n\r", 2, 0) ;
   send(pTrav->uMob.pClient->hSocket, pClient->szName, strlen(pClient->szName), 0) ;
   send(pTrav->uMob.pClient->hSocket, " has connected\n\r: ", 18, 0) ;
  }
  pTrav = pTrav->pNext ;
 }
 DoLook(pClient, "") ;
 send(pClient->uMob.pClient->hSocket, ": ", 2, 0) ;

 return pClient ;
}

void DisconnectClient (Entity *pClient)
{
 Entity *pTrav = pClient->pOwner->pCMob ;
 while (pTrav != NULL)
 {
  if (pTrav->uMob.bClient == 1 && pTrav != pClient)
  {
   send(pTrav->uMob.pClient->hSocket, "\n\r", 2, 0) ;
   send(pTrav->uMob.pClient->hSocket, pClient->szName, strlen(pClient->szName), 0) ;
   send(pTrav->uMob.pClient->hSocket, " has disconnected\n\r: ", 21, 0) ;
  }
  pTrav = pTrav->pNext ;
 }
 TreeView_DeleteItem(hEntitys, pClient->hTreeItem) ;
// SendMessage(hEntitys, TVM_DELETEITEM, 0, (LPARAM)&pClient->hTreeItem) ;
 closesocket(pClient->uMob.pClient->hSocket) ;
 delete pClient->uMob.pClient ;
 DeleteEntity (pClient) ;
}