/*

  Spawn.cpp
  Version 0.004.000

*/

#include "Main.h"

void SpawnContained (Entity *pEntity)
{
 int nType = 1 ;
 Entity *pTrace ;
 while (EntPField[nType].Type != F_END)
 {
  if (EntPField[nType].Type == F_CPOINT)
  {
	pTrace = *(Entity**)((byte*)pEntity + (int)EntPField[nType].pVar) ;
	while (pTrace != NULL)
	{
	 pTrace->Spawn(pTrace) ;
	 pTrace = pTrace->pNext ;
	}
  }
  nType ++ ;
 }
}

void SP_Server (Entity *pSelf)
{
 SpawnContained (pSelf) ;

 if (!(pSelf->uServer.hConnectSock = BindSocket(pSelf->uServer.nConnectPort, SOMAXCONN))) Logs.AddLine("SP_Server - BindSocket failed for server ", pSelf->szName) ;
}

void SP_Plane (Entity *pSelf)
{
 SpawnContained (pSelf) ;
}

void SP_System (Entity *pSelf)
{
 SpawnContained (pSelf) ;
}

void SP_Body (Entity *pSelf)
{
 SpawnContained (pSelf) ;
}

void SP_Room (Entity *pSelf)
{
 SpawnContained (pSelf) ;
}

void SP_Item (Entity *pSelf)
{
 SpawnContained (pSelf) ;
}

void SP_Mob (Entity *pSelf)
{
 if (pSelf->uMob.bClient) 
 {
  pSelf->uMob.pClient->nBufferPos = 0 ;
  
 }

 SpawnContained (pSelf) ;
}

void SP_Exit (Entity *pSelf)
{
 if (pSelf->uExit.szRoomTo != NULL)
 {
  int nType ;
  Entity *pTrace = NULL ;

  int nLength, nPosition = 0, nNumber, nRoomTo = strlen(pSelf->uExit.szRoomTo) ;
  if (nRoomTo > MAX_FILE_NUMBER)
  {
   Logs.AddLine ("SP_Exit - szRoomTo value exceeds MAX_FILE_NUMBER") ;
   SpawnContained (pSelf) ;
   return ;
  }
  while (nPosition < nRoomTo)
  {
   nLength = 0 ;
   while (pSelf->uExit.szRoomTo[nLength + nPosition] != ' ' && pSelf->uExit.szRoomTo[nLength + nPosition] != '\0')
   {
    szGBuffer[nLength] = pSelf->uExit.szRoomTo[nLength + nPosition] ;
    nLength ++ ;
   }
   szGBuffer[nLength] = '\0' ;
   nLength ++ ;
   nPosition += nLength ;

   nType = 1 ;
   while (EntPField[nType].Type != F_END && strcmp(EntPField[nType].szName, szGBuffer) != 0) nType ++ ;

   if (EntPField[nType].Type == F_CPOINT && strcmp(EntPField[nType].szName, szGBuffer) == 0)
   {
    nLength = 0 ;

    while (pSelf->uExit.szRoomTo[nLength + nPosition] != ' ' && pSelf->uExit.szRoomTo[nLength + nPosition] != '\0')
    {
     szGBuffer[nLength] = pSelf->uExit.szRoomTo[nLength + nPosition] ;
     nLength ++ ;
	}
    szGBuffer[nLength] = '\0' ;
    nLength ++ ;
    nPosition += nLength ;

    nNumber = atoi(szGBuffer) ;
    nLength = 0 ;

	if (pTrace != NULL) pTrace = *(Entity**)((byte*)pTrace + (int)EntPField[nType].pVar) ;
	else pTrace = pGServers ;
    while (nNumber != nLength && pTrace != NULL)
    {
     pTrace = pTrace->pNext ;
     nLength ++ ;
	}
	if (pTrace == NULL)
    {
     Logs.AddLine("SP_Exit - Could not link Exit ", pSelf->szName) ;
     SpawnContained (pSelf) ;
 	 return ;	
    }
   } else
   {
    Logs.AddLine("SP_Exit - Could not link Exit ", pSelf->szName) ;
    SpawnContained (pSelf) ;
	return ;	
   }
   nType ++ ;
  }

//  delete [] pSelf->uExit.szRoomTo ;
//  pSelf->uExit.szRoomTo = NULL ;
  pSelf->uExit.pRoomTo = pTrace ;
 }

 SpawnContained (pSelf) ;
}

void DIE_Server (Entity *pSelf)
{
}

void DIE_Plane (Entity *pSelf)
{
}

void DIE_System (Entity *pSelf)
{
}

void DIE_Body (Entity *pSelf)
{
}

void DIE_Room (Entity *pSelf)
{
}

void DIE_Item (Entity *pSelf)
{
}

void DIE_Mob (Entity *pSelf)
{
}

void DIE_Exit (Entity *pSelf)
{
}