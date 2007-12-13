#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

class Environment
{
private:
 char **m_ppCurrent ;
 char **m_ppUpdated ;

 int m_iXSize ;
 int m_iYSize ;
 int m_iBirth[9] ;
 int m_iSurvival[9] ;

 int CountNeighbors(int iX, int iY) ;
 void Make(char **&ppMake, int iXSize, int iYSize) ;
 void Remove(char **ppRemove) ;
public:
 Environment(int iXSize, int iYSize) ;
 ~Environment() ;

 void Clear(bool iRandomize) ;
 void Rules(char *szRules) ;
 void Update() ;
 void Output() ;
} ;

#endif