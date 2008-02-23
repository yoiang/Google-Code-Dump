/*

  Server.h
  Version 0.004.000

*/

#ifndef __SERVER_H__
#define __SERVER_H__

class Server
{
private:
// int bOnline ;

// char *szServerName ;

// int nMainPort ;

// int hNumppMobs ;
// int hNumMobs ;
// Entity **ppMobs ;
// int nNumppMobsInc ;

// int hNumppPlanes ;
// Entity **ppPlanes ;

// void InitVariables () ;
// int InitSockets () ;

// void DeInitVariables () ;
// int DeInitSockets () ;

// Entity *pOwner ;

public:

 int nConnectPort ;
 SOCKET hConnectSock ;
 
// Server () ;
// ~Server () ;

// int Spawn () ;
// int Die () ;

 int Startup () ;
 int Shutdown () ;

// int IsOnline () { return bOnline ; }
// int MainPort () { return nMainPort ; }

// Entity* CreateMob () ;
// void RegisterMob (Entity *pEntity) ;
// Entity* CreateClient () ;
// void RegisterClient (Entity *pEntity) ;
} ;

#define SERVERFM(x) (void *)&(((Server *)0)->x)

extern PField ServerPField [] ;
extern PFField ServerPFField [] ;

#endif // __SERVER_H__