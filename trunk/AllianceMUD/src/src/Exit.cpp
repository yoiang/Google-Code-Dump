/*

  Exit.cpp
  Version 0.004.000

*/
  
#include "Main.h"

/*
Exit::Exit()
{
 pOwner = NULL ;
} 

Exit::~Exit()
{
}
*/
/*
int Exit::Spawn ()
{
 return 1 ;
}

int Exit::Die ()
{
 return 1 ;
}
*/
PField ExitPField [] =
{
 {"szRoomTo", EXITFM(szRoomTo), F_STRING},
 {"pRoomTo", EXITFM(pRoomTo), F_POINT},

// {"Spawn", EXITFM(Spawn), F_FUNCTION},
// {"Die", EXITFM(Die), F_FUNCTION},

 {"", NULL, F_END}
} ;

PFField ExitPFField [] =
{
 {"Spawn", SP_Exit},
 {"Die", DIE_Exit},

 {"END", NULL}
} ;