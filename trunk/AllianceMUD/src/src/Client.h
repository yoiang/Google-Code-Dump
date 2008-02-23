/*

  Client.h
  Version 0.004.000

*/

#ifndef __CLIENT_H_
#define __CLIENT_H_

#define CLIENT_BUFFER_SIZE 256
class Client                  // Client class
{
//private:
// Entity *pOwner ;

public:
 SOCKET hSocket ;

 char szBuffer[CLIENT_BUFFER_SIZE] ;
 int nBufferPos ;
// Client() ;
// ~Client() ;

// void Spawn (Entity *pEntity) ;
// void Die (Entity *pEntity) ;
} ;

#define CLIENTFM(x) (void *)&(((Client *)0)->x)

extern PField ClientPField [] ;

#endif // __CLIENT_H_