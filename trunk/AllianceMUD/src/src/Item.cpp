/*

  Item.cpp
  Version 0.004.000

*/

#include "Main.h"

/*
Item::Item ()
{
 pOwner = NULL ;
}

Item::~Item ()
{
}
*/
/*
int Item::Spawn ()
{
 return 1 ;
}

int Item::Die ()
{
 return 1 ;
}
*/
PField ItemPField [] =
{
 {"", NULL, F_END}
} ;

PFField ItemPFField [] =
{
 {"Spawn", SP_Item},
 {"Die", DIE_Item},

 {"END", NULL}
} ;