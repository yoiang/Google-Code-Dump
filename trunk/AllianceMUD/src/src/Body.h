/*

  Body.h
  Version 0.004.000

*/

#ifndef __BODY_H_
#define __BODY_H_

class Body                  // Body class
{
//private:
// Entity *pOwner ;

public:
// Body() ;
// ~Body() ;

// void Spawn (Entity *pEntity) ;
// void Die (Entity *pEntity) ;
// Entity **ppRooms ;         // Dynamic array of pointers to Entitys of Rooms contained in this Body
// handle hNumppRooms ;       // Number of nodes in ppRooms
} ;

#define BODYFM(x) (void *)&(((Body *)0)->x)

extern PField BodyPField [] ;
extern PFField BodyPFField [] ;

#endif // __BODY_H_