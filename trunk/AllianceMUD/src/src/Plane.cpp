/*

  Plane.cpp
  Version 0.004.000

*/

#include "Main.h"

/*
Plane::Plane ()
{
 pOwner = NULL ;

// ppSystems = NULL ;
// hNumppSystems = 0 ;
}

Plane::~Plane ()
{
// if (ppSystems != NULL)
// {
//  for (handle hTemp = 0 ; hTemp < hNumppSystems ; hTemp ++)
//	if (ppSystems[hTemp] != NULL) delete ppSystems[hTemp] ;
//  delete [] ppSystems ;
// }
}
*/
/*
int Plane::Spawn ()
{
 return 1 ;
}

int Plane::Die ()
{
 return 1 ;
}
*/

PField PlanePField [] =
{
// {"pOwner",
 {"", NULL, F_END}
} ;

PFField PlanePFField [] =
{
 {"Spawn", SP_Plane},
 {"Die", DIE_Plane},

 {"END", NULL}
} ;