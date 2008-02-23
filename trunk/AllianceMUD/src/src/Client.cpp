/*

  Client.cpp
  Version 0.004.000

*/

#include "Main.h"

/*
Client::Client ()
{
 pOwner = NULL ;
// ppRooms = NULL ;
// hNumppRooms = 0 ;
}

Client::~Client ()
{
// if (ppRooms != NULL)
// {
//  for (handle hTemp = 0 ; hTemp < hNumppRooms ; hTemp ++)
//	if (ppRooms[hTemp] != NULL) delete ppRooms[hTemp] ;
//  delete ppRooms ;
// }
}
*/
/*
void Client::Spawn (Entity *pEntity)
{
}

void Client::Die (Entity *pEntity)
{
}
*/
PField ClientPField [] =
{
 {"hSocket", CLIENTFM(hSocket), F_HANDLE}, 

 {"", NULL, F_END}
} ;