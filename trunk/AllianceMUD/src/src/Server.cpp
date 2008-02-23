/*

  Server.cpp
  Version 0.004.000

*/

#include "Main.h"

/*
Server::Server ()
{
 pOwner = NULL ;
// InitVariables () ;
}

Server::~Server ()
{
// Shutdown () ;
}
*/

/*int Server::Spawn ()
{
 return Startup () ;
}

int Server::Die ()
{
 return Shutdown () ;
}
*/

int Server::Startup ()
{
// if (bOnline) return 1 ;

// Logs.AddLine ("**** Initializing server ****") ;

// Logs.AddLine ("Initializing server variables") ; 
// InitVariables () ;

// Logs.AddLine ("Reading server variables from config file ", "server.cfg") ; 
// ReadFields("server.cfg", pServerConfigVariables, NULL) ;

// Logs.AddLine ("Reading area files") ;
// hNumppPlanes = InitAreas("areas\\", "index.area", ppPlanes) ;

// Logs.AddLine ("Opening main server sockets") ;
// if (!InitSockets ()) return 0 ;

// if (szServerName != NULL)
// {
//  sprintf(szGBuffer, "**** %s", szServerName) ;
//  Logs.AddLine (szGBuffer, " going online ****") ; 

//  AddToTree(hEntitys, szServerName, TVI_ROOT) ;
// } else Logs.AddLine ("**** Going online ****") ; 

// bOnline = 1 ;

 return 1 ;
}

int Server::Shutdown ()
{
// if (!bOnline) return 1 ;
/*
 Logs.AddLine("**** Shutting down server ****") ; 

 Logs.AddLine("Deinitializing server variables") ;
 DeInitVariables () ; 

// DeleteFile("server.cfg") ;
// Logs.AddLine("Writing server variables to config file ", "server.cfg") ;
// WriteFields("server.cfg", pServerConfigVariables, NULL) ;

 Logs.AddLine("Closing main server sockets") ;
 if (!DeInitSockets ()) return 0 ; 

 Logs.AddLine ("**** Going offline ****") ; 
 bOnline = 0 ;
*/
 return 1 ;
}

PField ServerPField [] =
{
 {"nConnectPort", SERVERFM(nConnectPort), F_INT},
 {"hConnectSock", SERVERFM(hConnectSock), F_HANDLE},

 {"", NULL, F_END}
} ;


PFField ServerPFField [] =
{
 {"Spawn", SP_Server},
 {"Die", DIE_Server},

 {"END", NULL}
} ;
/*
void Server::InitVariables ()
{
// bOnline = 0 ;

// szServerName = NULL ;

// hNumppMobs = 0 ;
// hNumMobs = 0 ;
// ppMobs = NULL ;
// nNumppMobsInc = 5 ;

 pHeadClient = NULL ;
 pTailClient = NULL ;

// hNumppPlanes = 0 ;
// ppPlanes = NULL ;
}

int Server::InitSockets ()
{
// if (!(hMainSocket = InitSocket(nMainPort, 1))) return 0 ;
 return 1 ;
}

/*
void Server::DeInitVariables () 
{
 Logs.AddLine("Deallocating areas") ;
// for (int hTemp = 0 ; hTemp < hNumppPlanes ; hTemp ++)
// { if (ppPlanes[hTemp] != NULL) delete ppPlanes[hTemp] ; }
// if (ppPlanes != NULL) delete [] ppPlanes ;

 Logs.AddLine("Deallocating mobs and disconnecting clients") ;
// for (hTemp = 0 ; hTemp < hNumppMobs ; hTemp ++)
// { if (ppMobs[hTemp] != NULL) delete ppMobs[hTemp] ; }
// if (ppMobs != NULL) delete [] ppMobs ;

 if (szServerName != NULL) delete [] szServerName ;
}

int Server::DeInitSockets ()
{
 if (closesocket (hMainSocket) == SOCKET_ERROR) return 0 ;
 return 1 ;
}

/*void Server::RegisterMob (Entity *pEntity)
{
 if (hNumppMobs == hNumMobs)
 {
  ResizeppEntitys (ppMobs, hNumppMobs, hNumppMobs + nNumppMobsInc) ;
  ppMobs[hNumppMobs] = pEntity ;
  pEntity->pMob->hNumber = hNumppMobs ;

  hNumMobs ++ ;
  hNumppMobs += nNumppMobsInc ;
  return ;
 } else
 {
  for (int hTemp = 0 ; hTemp < hNumppMobs ; hTemp ++)
   if (ppMobs[hTemp] == NULL) 
  {
   ppMobs[hTemp] = pEntity ;
   pEntity->pMob->hNumber = hTemp ;
   return ;
  }
 }
}

Entity* Server::CreateMob()
{
 Entity *pEntity = CreateEntity () ;

 pEntity->fType = E_MOB ;
 pEntity->pMob = new Mob ;
 RegisterMob (pEntity) ;

 return pEntity ;
}

void Server::RegisterClient (Entity *pEntity)
{
 if (pHeadClient == NULL)
 {
  pHeadClient = pEntity ;
  pTailClient = pEntity ;
  return ;
 }

 pTailClient->pMob->pClient->pNext = pEntity ; 
 pEntity->pMob->pClient->pLast = pTailClient ;
 pTailClient = pEntity ;
 return ;
}

Entity* Server::CreateClient()
{
 Entity *pEntity = CreateMob () ;

 pEntity->pMob->pClient = new Client ;
 RegisterClient (pEntity) ;
 return pEntity ;
}

*/