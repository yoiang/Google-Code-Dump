/*

  Commands.cpp
  Version 0.004.000

*/

#include "Main.h"

int DoCommand (Entity *pEntity, char *szCommand) 
{
 int nTrav = 0 ;
 while (szCommand[nTrav] != ' ' && szCommand[nTrav] != '\n' && szCommand[nTrav] != 13 && szCommand[nTrav] != '\0') nTrav ++ ;

 char *szDoCommand = new char [nTrav + 1] ;
 nTrav = 0 ;
 while (szCommand[nTrav] != ' ' && szCommand[nTrav] != '\n' && szCommand[nTrav] != 13 && szCommand[nTrav] != '\0') 
 {
  szDoCommand[nTrav] = szCommand[nTrav] ;
  nTrav ++ ;
 }
 szDoCommand[nTrav] = '\0' ;
 char *szParam = new char [strlen(szCommand) - nTrav + 1] ;
 int nParam = 0 ;
 nTrav ++ ;
 while (szCommand[nTrav] != '\0')
 {
  szParam[nParam] = szCommand[nTrav] ;
  nTrav ++ ;
  nParam ++ ;
 }
 szParam[nParam] = '\0' ;

 nTrav = 0 ;
 while (strcmp(PCommands[nTrav].szName, "END") != 0 && strcmp(PCommands[nTrav].szName, szDoCommand) != 0) nTrav ++ ;
 if (strcmp(PCommands[nTrav].szName, szDoCommand) == 0)
 {
  PCommands[nTrav].Command(pEntity, szParam) ;
  if (strcmp(PCommands[nTrav].szName, "quit") == 0)
  {
	   delete [] szDoCommand ;
		delete [] szParam ; 

		return 0 ;
  }
 } else
 {
  send(pEntity->uMob.pClient->hSocket, "Unknown command\n\r", strlen("Unknown command\n\r"), 0) ;
 }
 delete [] szDoCommand ;
 delete [] szParam ; 

 return 1 ;
}

void DoLook (Entity *pEntity, char *szParam)
{
 Entity *pLookAt ;
 if (strcmp(szParam, "") == 0)
 {
  pLookAt = pEntity->pOwner ;
 } else
 {
  pLookAt = pEntity->pOwner->pCItem ;
  while (pLookAt != NULL && strcmp(szParam, pLookAt->szName) != 0) pLookAt = pLookAt->pNext ;
  if (pLookAt == NULL)
  {
   pLookAt = pEntity->pOwner->pCMob ;
   while (pLookAt != NULL && (strcmp(szParam, pLookAt->szName) != 0 || pLookAt == pEntity )) pLookAt = pLookAt->pNext ;
   if (pLookAt == NULL)	
   {
	send(pEntity->uMob.pClient->hSocket, "look at what?\n\r", 15, 0) ;
	return ;
   }
  }
 }
 if(pLookAt->szName != NULL)
 {
  send(pEntity->uMob.pClient->hSocket, pLookAt->szName, strlen(pLookAt->szName), 0) ;
  send(pEntity->uMob.pClient->hSocket, "\n\r", 2, 0) ;
 }
/*
  if (pLookAt->szLongDescription != NULL) 
  {
   send(pEntity->uMob.pClient->hSocket, pLookAt->szLongDescription, strlen(pLookAt->szLongDescription), 0) ;
   send(pEntity->uMob.pClient->hSocket, "\n\r", 2, 0) ;
  }
*/
 if (pLookAt->szShortDescription != NULL) 
 {
  send(pEntity->uMob.pClient->hSocket, pLookAt->szShortDescription, strlen(pLookAt->szShortDescription), 0) ;
  send(pEntity->uMob.pClient->hSocket, "\n\r", 2, 0) ;
 }

 switch (pLookAt->nEntType)
 {
/* case E_SERVER:
 break ;
 case E_PLANE:
 break ;
 case E_SYSTEM:
 break ;
 case E_BODY:
 break ;
*/
 case E_ROOM:
  Entity *pTrav ;
  if (pLookAt->pCExit != NULL)
  {
   send(pEntity->uMob.pClient->hSocket, "Exits:\n\r", 8, 0) ;
   pTrav = pLookAt->pCExit ;
   while (pTrav != NULL)
   {
	if (pTrav->szName != NULL)
	{
     send(pEntity->uMob.pClient->hSocket, pTrav->szName, strlen(pTrav->szName), 0) ;
     send(pEntity->uMob.pClient->hSocket, "\n\r", 2, 0) ;
	}
	pTrav = pTrav->pNext ;
   }
   send(pEntity->uMob.pClient->hSocket, "\n\r", 2, 0) ;
  }

  if (pLookAt->pCMob != NULL)
  {
   pTrav = pLookAt->pCMob ;
   while (pTrav != NULL)
   {
	if (pTrav->szName != NULL && pTrav != pEntity)
	{
     send(pEntity->uMob.pClient->hSocket, pTrav->szName, strlen(pTrav->szName), 0) ;
     send(pEntity->uMob.pClient->hSocket, "\n\r", 2, 0) ;
	}
	pTrav = pTrav->pNext ;
   }
  }

  if (pLookAt->pCItem != NULL)
  {
   pTrav = pLookAt->pCItem ;
   while (pTrav != NULL)
   {
	if (pTrav->szName != NULL)
	{
     send(pEntity->uMob.pClient->hSocket, pTrav->szName, strlen(pTrav->szName), 0) ;
     send(pEntity->uMob.pClient->hSocket, "\n\r", 2, 0) ;
	}
	pTrav = pTrav->pNext ;
   }
  }
 break ;
/* case E_EXIT:
 break ;
*/
 case E_MOB:
  if (pLookAt->uMob.bClient)
  {
   char *szBuffer = new char [14 + strlen(pEntity->szName)] ;
   sprintf(szBuffer, "%s looks at you", pEntity->szName) ;
   send(pLookAt->uMob.pClient->hSocket, szBuffer, strlen(szBuffer), 0) ;
   delete [] szBuffer ;
  }
 break ;
/* case E_ITEM:
 break ;
*/ }
}

void DoGo (Entity *pEntity, char *szParam)
{
 if (strcmp(szParam, "") == 0) send(pEntity->uMob.pClient->hSocket, "go where?\n\r", 11, 0) ;
 else
 {
  Entity *pTrav = pEntity->pOwner->pCExit ;
  while (pTrav != NULL)
  {
   if (strcmp (pTrav->szName, szParam) == 0)
   { 
	MoveEntity (pEntity, pTrav->uExit.pRoomTo) ;
	DoLook (pEntity, "") ;
	return ;
   }
   pTrav = pTrav->pNext ;
  }
  send(pEntity->uMob.pClient->hSocket, "not an exit\n\r", 15, 0) ;
 }
}

void DoSay (Entity *pEntity, char *szParam)
{
 if (strcmp(szParam, "") == 0) send(pEntity->uMob.pClient->hSocket, "say what?\n\r", 11, 0) ;
 else
 {
  char *szBuffer = new char [21 + strlen(pEntity->szName) + strlen(szParam)] ;
  sprintf(szBuffer, "\n\r\n\r%s says \"%s\"\n\r\n\r: ", pEntity->szName, szParam) ;
  SendToAll(szBuffer, pEntity->pOwner->pCMob, pEntity) ;
  delete [] szBuffer ;

  send(pEntity->uMob.pClient->hSocket, "You say \"", 9, 0) ;
  send(pEntity->uMob.pClient->hSocket, szParam, strlen(szParam), 0) ;
  send(pEntity->uMob.pClient->hSocket, "\"\n\r", 3, 0) ;
 }
}

void DoEmote (Entity *pEntity, char *szParam)
{
 if (strcmp(szParam, "") == 0) send(pEntity->uMob.pClient->hSocket, "emote what?\n\r", 11, 0) ;
 else
 {
  char *szBuffer = new char [12 + strlen(pEntity->szName) + strlen(szParam)] ;
  sprintf(szBuffer, "\n\r\n\r%s %s\n\r\n\r:", pEntity->szName, szParam) ;
  SendToAll(szBuffer, pEntity->pOwner->pCMob, pEntity) ;
  delete [] szBuffer ;

  send(pEntity->uMob.pClient->hSocket, pEntity->szName, strlen(pEntity->szName), 0) ;
  send(pEntity->uMob.pClient->hSocket, " ", 1, 0) ;
  send(pEntity->uMob.pClient->hSocket, szParam, strlen(szParam), 0) ;
  send(pEntity->uMob.pClient->hSocket, "\n\r", 2, 0) ;
 }
}

void DoQuit (Entity *pEntity, char *szParam)
{
 //send disconnect data
 SendMessage(hMain, MW_DATAREADY, pEntity->uMob.pClient->hSocket, FD_CLOSE) ;
}


PCommand PCommands [] =
{
 {"look", DoLook},
 {"l", DoLook},

 {"go", DoGo},
 {"g", DoGo},

 {"say", DoSay},

 {"emote", DoEmote},
 {"e", DoEmote},
 {":", DoEmote},

 {"quit", DoQuit},

 {"END", NULL}
} ;