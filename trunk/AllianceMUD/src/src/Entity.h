/*

  Entity.h
  Version 0.004.000

*/

#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity
{
public:
 int nEntType ;

//private:
// int fContain ;

// int nNumber ;
// int hEntityNumber ;

 union
 {
  Server uServer ;
  Plane uPlane ;
  System uSystem ;
  Body uBody ;
  Room uRoom ;
  Exit uExit ;
  Mob uMob ;
  Item uItem ;
 } ;

 char *szName ;
 char *szShortDescription ;
 char *szLongDescription ;

 Entity *pOwner ;

 Entity *pLast ;
 Entity *pNext ;

 Entity *pCServer ;
 Entity *pCPlane ;
 Entity *pCSystem ;
 Entity *pCBody ;
 Entity *pCRoom ;
 Entity *pCExit ;
 Entity *pCMob ;
 Entity *pCItem ;

 HTREEITEM hTreeItem ;

//private:
 Entity *pGLast ;
 Entity *pGNext ;

public:
 Entity () ;
 ~Entity () ;

 void (*Spawn)(Entity *pEntity) ;
 void (*Die)(Entity *pEntity) ;

 void Register () ;
 void Unregister () ;
} ;

#define ENTFM(x) (void *)&(((Entity *)0)->x)

extern PField EntPField [] ;
extern PField EntTypePField [][3] ;

// ***#define FOR ENTITY TYPES MUST BE CORRISPONDING WITH EntPField AND EntTypePField OR EVERYTHING WILL BE UTTER CHAOS***
#define E_SERVER 1
#define E_PLANE 2
#define E_SYSTEM 3
#define E_BODY 4
#define E_ROOM 5
#define E_EXIT 6
#define E_MOB 7
#define E_ITEM 8

#define EB_SERVER BIT01
#define EB_PLANE BIT02
#define EB_SYSTEM BIT03
#define EB_BODY BIT04
#define EB_ROOM BIT05
#define EB_EXIT BIT06
#define EB_MOB BIT07
#define EB_ITEM BIT08

Entity* CreateEntity (int nType) ;
void DeleteEntity (Entity *pDelete) ;
void MoveEntity (Entity *pEntity, Entity *pNewOwner) ;
void SendToAll (char *szMessage, Entity *pEntity, Entity *pExclude) ; 


#endif // __ENTITY_H_