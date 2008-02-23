/*

  Entity.cpp
  Version 0.004.000

*/

#include "Main.h"

// ***EntPField AND EntTypePField MUST BE CORRISPONDING WITH #define OF ENTITY TYPES IN Entity.h OR EVERYTHING WILL BE UTTER CHAOS***
PField EntPField [] =
{
 {"nEntType", ENTFM(nEntType), F_INT},

 {"pCServer", ENTFM(pCServer), F_CPOINT},
 {"pCPlane", ENTFM(pCPlane), F_CPOINT},
 {"pCSystem", ENTFM(pCSystem), F_CPOINT},
 {"pCBody", ENTFM(pCBody), F_CPOINT},
 {"pCRoom", ENTFM(pCRoom), F_CPOINT},
 {"pCExit", ENTFM(pCExit), F_CPOINT},
 {"pCMob", ENTFM(pCMob), F_CPOINT},
 {"pCItem", ENTFM(pCItem), F_CPOINT},

 {"szName", ENTFM(szName), F_STRING},
 {"szShortDescription", ENTFM(szShortDescription), F_STRING},
 {"szLongDescription", ENTFM(szLongDescription), F_STRING},

// {"Spawn", ENTFM(Spawn), F_FUNCTION},
// {"Die", ENTFM(Die), F_FUNCTION},

 {NULL, 0, F_END}
} ;

PField EntTypePField [][3] =
{
 { {NULL, 0, F_IGNORE}, {NULL, 0, F_IGNORE}, {NULL, 0, F_IGNORE} },

 { {"uServer", ENTFM(uServer), F_TPOINT}, {"ServerPF", GFM(ServerPField), F_PFIELD}, {"ServerPFF", GFM(ServerPFField), F_PFIELD} },
 { {"uPlane", ENTFM(uPlane), F_TPOINT},   {"PlanePF", GFM(PlanePField), F_PFIELD},   {"PlanePFF", GFM(PlanePFField), F_PFIELD}   },
 { {"uSystem", ENTFM(uSystem), F_TPOINT}, {"SystemPF", GFM(SystemPField), F_PFIELD}, {"SystemPFF", GFM(SystemPFField), F_PFIELD} },
 { {"uBody", ENTFM(uBody), F_TPOINT},     {"BodyPF", GFM(BodyPField), F_PFIELD},     {"BodyPFF", GFM(BodyPFField), F_PFIELD} },
 { {"uRoom", ENTFM(uRoom), F_TPOINT},     {"RoomPF", GFM(RoomPField), F_PFIELD},     {"RoomPFF", GFM(RoomPFField), F_PFIELD} },
 { {"uExit", ENTFM(uExit), F_TPOINT},     {"ExitPF", GFM(ExitPField), F_PFIELD},     {"ExitPFF", GFM(ExitPFField), F_PFIELD} },
 { {"uMob", ENTFM(uMob), F_TPOINT},       {"MobPF", GFM(MobPField), F_PFIELD},       {"MobPFF", GFM(MobPFField), F_PFIELD} },
 { {"uItem", ENTFM(uItem), F_TPOINT},     {"ItemPF", GFM(ItemPField), F_PFIELD},     {"ItemPFF", GFM(ItemPFField), F_PFIELD} },

 { {NULL, 0, F_END}, {NULL, 0, F_END}, {NULL, 0, F_END} }
} ;

Entity::Entity ()
{
 Spawn = NULL ;
 Die = NULL ;

// pServer = NULL ;

 pCServer = NULL ;
 pCPlane = NULL ;
 pCSystem = NULL ;
 pCBody = NULL ;
 pCRoom = NULL ;
 pCExit = NULL ;
 pCMob = NULL ;
 pCItem = NULL ;

 nEntType = 0 ;
// fType = 0 ;
// fType = E_MOB ;

// nNumber = 0 ;
// hEntityNumber = 0 ;

// fContain = 0 ;

// szName = NULL ;
// szShortDescription = NULL ;
// szLongDescription = NULL ;

// pMob = NULL ;

 pLast = NULL ;
 pNext = NULL ;

 pGLast = NULL ;
 pGNext = NULL ;

 hTreeItem = 0 ;

 szName = NULL ;
 szShortDescription = NULL ;
 szLongDescription = NULL ;

 pOwner = NULL ;
}

Entity::~Entity ()
{
// if (szName != NULL) delete [] szName ;
// if (szShortDescription != NULL) delete [] szShortDescription ;
// if (szLongDescription != NULL) delete [] szLongDescription ;

// switch (fType)
// {
// case E_MOB:
//  if (pMob != NULL) delete pMob ;
// break ;
// case E_ITEM:
//  if (pItem != NULL) delete pItem ;
// break ;
// case E_PLANE:
//  if (pPlane != NULL) delete pPlane ;
// break ;
// case E_SYSTEM:
//  if (pSystem != NULL) delete pSystem ;
// break ;
// case E_BODY:
//  if (pBody != NULL) delete pBody ;
// break ;
// case E_ROOM:
//  if (pRoom != NULL) delete pRoom ;
// break ;
// case E_EXIT:
//  if (pExit != NULL) delete pExit ;
// break ;
// case E_SERVER:
//  if (pServer != NULL) delete pServer ;
// break ;
// }
}

void Entity::Register ()
{
 if (pGHeadEnt == NULL)
 {
  pGHeadEnt = this ;
  pGTailEnt = this ;
  return ;
 }
 pGTailEnt->pGNext = this ;
 pGLast = pGTailEnt ;
 pGTailEnt = this ;
}

void Entity::Unregister ()
{
 if (pGNext != NULL) pGNext->pGLast = pGLast ;
 if (pGLast != NULL) pGLast->pGNext = pGNext ;
 if (pGHeadEnt == this) pGHeadEnt = pGNext ;
 if (pGTailEnt == this) pGTailEnt = pGLast ;
}

Entity* CreateEntity (int nType)
{
 Entity *pNew = new Entity ;
#ifdef MEM_DEBUG
 if (pNew == NULL) FatalError("CreateEntity - Heap overflow") ;
#endif // MEM_DEBUG
 if (nType)
 {
  pNew->nEntType = nType ;
  
  int nFunc = 0 ;
  while (strcmp(((PFField*)(EntTypePField[nType][2].pVar))[nFunc].szName, "END") != 0 && strcmp(((PFField*)(EntTypePField[nType][2].pVar))[nFunc].szName, "Spawn") != 0) nFunc ++ ;
  if (strcmp(((PFField*)(EntTypePField[nType][2].pVar))[nFunc].szName, "END") != 0)
  {
   pNew->Spawn = (((PFField*)(EntTypePField[nType][2].pVar))[nFunc].pVar) ;
  }
  nFunc = 0 ;
  while (strcmp(((PFField*)(EntTypePField[nType][2].pVar))[nFunc].szName, "END") != 0 && strcmp(((PFField*)(EntTypePField[nType][2].pVar))[nFunc].szName, "Die") != 0) nFunc ++ ;
  if (strcmp(((PFField*)(EntTypePField[nType][2].pVar))[nFunc].szName, "END") != 0)
  {
   pNew->Die = (((PFField*)(EntTypePField[nType][2].pVar))[nFunc].pVar) ;
  }
 }
 pNew->Register () ;
 return pNew ;
}

void DeleteEntity (Entity *pDelete)
{
 pDelete->Unregister () ;

 if (pDelete->pNext != NULL) pDelete->pNext->pLast = pDelete->pLast ;
 if (pDelete->pLast != NULL) pDelete->pLast->pNext = pDelete->pNext ; 
 if (pDelete->pOwner != NULL)
 {
  if (pDelete == *(Entity**)((byte*)pDelete->pOwner + (int)EntPField[pDelete->nEntType].pVar)) 
   *(Entity**)((byte*)pDelete->pOwner + (int)EntPField[pDelete->nEntType].pVar) = pDelete->pNext ;
 } else if (pGServers == pDelete)
 {
  pGServers = pGServers->pNext ;
  if (pGServers != NULL) pGServers->pLast = NULL ;
 }
 delete pDelete ;
}

void MoveEntity (Entity *pEntity, Entity *pNewOwner)
{
 if (pEntity->pNext != NULL) pEntity->pNext->pLast = pEntity->pLast ;
 if (pEntity->pLast != NULL) pEntity->pLast->pNext = pEntity->pNext ; 
 if (pEntity->pOwner != NULL)
 {
  if (pEntity == *(Entity**)((byte*)pEntity->pOwner + (int)EntPField[pEntity->nEntType].pVar)) 
  *(Entity**)((byte*)pEntity->pOwner + (int)EntPField[pEntity->nEntType].pVar) = pEntity->pNext ;
 } else if (pGServers == pEntity)
 {
  pGServers = pGServers->pNext ;
  if (pGServers != NULL) pGServers->pLast = NULL ;
 }

 pEntity->pOwner = pNewOwner ;

 if (*(Entity**)((byte*)pNewOwner + (int)EntPField[pEntity->nEntType].pVar) != NULL)
 {
  (*(Entity**)((byte*)pNewOwner + (int)EntPField[pEntity->nEntType].pVar))->pLast = pEntity ;
  pEntity->pNext = *(Entity**)((byte*)pNewOwner + (int)EntPField[pEntity->nEntType].pVar) ;
 }
 *(Entity**)((byte*)pNewOwner + (int)EntPField[pEntity->nEntType].pVar) = pEntity ;
}

void SendToAll (char *szMessage, Entity *pEntity, Entity *pExclude) 
{
 int nMessage = strlen (szMessage) ;
 while (pEntity != NULL)
 {
  if (/*pEntity->nEntType == E_MOB &&*/ pEntity->uMob.bClient && pEntity != pExclude)
  {
   send(pEntity->uMob.pClient->hSocket, szMessage, nMessage, 0) ;
  }
  pEntity = pEntity->pNext ;
 }
}