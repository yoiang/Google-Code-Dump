/*

  Mob.h
  Version 0.004.000

*/

#ifndef __MOB_H_
#define __MOB_H_

class Mob
{
private:
// Entity *pOwner ;
public:

 int bClient ;
 Client *pClient ;

// handle hLocationPlane ;      // handle of Plane of location
// handle hLocationStarSystem ; // handle of StarSystem of location
// handle hLocationPlanet ;     // handle of Planet of location
// handle hLocationRoom ;       // handle of Room of location
// handle hSpacecraft ;         // handle of Spacecraft of location

// int nHealth ;
// int nMaxHealth ;
// int nMoney ;
// int nMana ;
// int nMaxMana ;
// int nMoves ;
// int nMaxMoves ;
// int nMaxCarryWeight ;
// int nMaxCarryNumber ;

// handle hFighting ;
// Mob *pFighting ;

// Item *pInventory ;
// Item *pEquiped ;
} ;

#define MOBFM(x) (void *)&(((Mob *)0)->x)

extern PField MobPField [] ;
extern PFField MobPFField [] ;

#endif // _MOB_H