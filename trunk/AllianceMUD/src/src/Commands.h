/*

  Commands.h
  Version 0.004.000

*/

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

extern PCommand PCommands [] ;

int DoCommand (Entity *pEntity, char *szCommand) ;

void DoLook (Entity *pEntity, char *szParam) ;
void DoGo (Entity *pEntity, char *szParam) ;
void DoSay (Entity *pEntity, char *szParam) ;
void DoEmote (Entity *pEntity, char *szParam) ;
void DoQuit (Entity *pEntity, char *szParam) ;

#endif // __COMMANDS_H__