/*

  Mob.cpp
  Version 0.004.000

*/

#include "Main.h"

PField MobPField [] =
{
 {"bClient", MOBFM(bClient), F_INT}, 

 {"", NULL, F_END}
} ;

PFField MobPFField [] =
{
 {"Spawn", SP_Mob},
 {"Die", DIE_Mob},

 {"END", NULL}
} ;