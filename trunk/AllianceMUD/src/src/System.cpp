/*

  System.cpp
  Version 0.004.000

*/

#include "Main.h"

/*
System::System ()
{
 pOwner = NULL ;
// ppBodys = NULL ;
// hNumppBodys = 0 ;
}

System::~System ()
{
// if (ppBodys != NULL)
// {
//  for (handle hTemp = 0 ; hTemp < hNumppBodys ; hTemp ++)
//	if (ppBodys[hTemp] != NULL) delete ppBodys[hTemp] ;
//  delete ppBodys ;
// }
}
*/
/*
int System::Spawn ()
{
 return 1 ;
}

int System::Die ()
{
 return 1 ;
}
*/
PField SystemPField [] =
{
 {"", NULL, F_END}
} ;

PFField SystemPFField [] =
{
 {"Spawn", SP_System},
 {"Die", DIE_System},

 {"END", NULL}
} ;