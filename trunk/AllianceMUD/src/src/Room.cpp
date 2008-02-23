/*

  Room.cpp
  Version 0.004.000

*/

#include "Main.h"

/*
Room::Room()
{
}

Room::~Room()
{
}
*/
/*
int Room::Spawn ()
{
 return 1 ;
}

int Room::Die ()
{
 return 1 ;
}*/

PField RoomPField [] =
{
 {"", NULL, F_END}
} ;

PFField RoomPFField [] =
{
 {"Spawn", SP_Room},
 {"Die", DIE_Room},

 {"END", NULL}
} ;