/*

  Plane.h
  Version 0.004.000

*/

#ifndef __PLANE_H_
#define __PLANE_H_

class Plane
{
private:
// Entity *pOwner ;

public:
// Plane () ;
// ~Plane () ;

// int Spawn () ;
// int Die () ;

// Entity **ppSystems ;     // Dynamic array of pointers to Entitys of StarSystems contained in this Plane
// handle hNumppSystems ;   // Number of nodes in ppStarSystems
} ;

#define PLANEFM(x) (void *)&(((Plane *)0)->x)

extern PField PlanePField [] ;
extern PFField PlanePFField [] ;

#endif // __PLANE_H_