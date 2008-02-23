/*

  Body.cpp
  Version 0.004.000

*/

#include "Main.h"

/*
Body::Body ()
{
 pOwner = NULL ;
// ppRooms = NULL ;
// hNumppRooms = 0 ;
}

Body::~Body ()
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
void Body::Spawn (Entity *pEntity)
{
}

void Body::Die (Entity *pEntity)
{
}
*/
PField BodyPField [] =
{
 {"", NULL, F_END}
} ;

PFField BodyPFField [] =
{
 {"Spawn", SP_Body},
 {"Die", DIE_Body},

 {"END", NULL}
} ;
