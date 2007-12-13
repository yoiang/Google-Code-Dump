#include "Environment.h"

HANDLE hConsole = 0 ;
void gotoxy(int x, int y)
{
 COORD cursor_pos;              //origin in upper left corner
 cursor_pos.X = x - 1;          //Windows starts at (0, 0)
 cursor_pos.Y = y - 1;          //we start at (1, 1)
 SetConsoleCursorPosition(hConsole, cursor_pos);
}

void Environment::Make(char **&ppMake, int iXSize, int iYSize)
{
 ppMake = new char*[iYSize] ;
 int iTrav2 ;
 for (int iTrav = 0 ; iTrav < iYSize ; iTrav ++)
 {
  ppMake[iTrav] = new char[iXSize + 1] ;
  for (iTrav2 = 0 ; iTrav2 < iXSize ; iTrav2 ++)
  {
   if ((float)(rand()) / (float)(RAND_MAX) < 0.20f)
	ppMake[iTrav][iTrav2] = '*' ;
   else ppMake[iTrav][iTrav2] = ' ' ;
  }
  ppMake[iTrav][iXSize] = '\0' ;
 }
}

void Environment::Remove(char **ppRemove)
{
 for (int iTrav = 0 ; iTrav < m_iYSize ; iTrav ++)
 {
  delete [] ppRemove[iTrav] ;
 }
 delete [] ppRemove ;
}

Environment::Environment(int iXSize, int iYSize)
{
 if (hConsole == 0)
 {
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  srand( (unsigned)time( NULL ) );
 }

 Rules("23/3") ;

 m_iXSize = iXSize ;
 m_iYSize = iYSize ;
 Make(m_ppCurrent, iXSize, iYSize) ;
 Make(m_ppUpdated, iXSize, iYSize) ;
}

Environment::~Environment()
{
}

void Environment::Clear(bool iRandomize)
{
 int iTrav2 ;
 for (int iTrav = 0 ; iTrav < m_iYSize ; iTrav ++)
 {
  for (iTrav2 = 0 ; iTrav2 < m_iXSize ; iTrav2 ++)
  {
   if (iRandomize && (float)(rand()) / (float)(RAND_MAX) < 0.20f)
	m_ppCurrent[iTrav][iTrav2] = '*' ;
   else m_ppCurrent[iTrav][iTrav2] = ' ' ;
  }
  m_ppCurrent[iTrav][m_iXSize] = '\0' ;
 }
}

void Environment::Rules(char *szRules)
{
 for (int iTrav = 0 ; iTrav < 9 ; iTrav ++)
 {
  m_iBirth[iTrav] = 0 ;
  m_iSurvival[iTrav] = 0 ;
 }
 iTrav = 0 ;
 int iNeighbors ;
 while(szRules[iTrav] != '/' && szRules[iTrav] != '\0')
 {
  iNeighbors = szRules[iTrav] - 48 ;
  if (iNeighbors > 0 && iNeighbors < 9)
   m_iSurvival[iNeighbors] = 1 ;
  iTrav ++ ;
 }
 while(szRules[iTrav] != '\0')
 {
  iNeighbors = szRules[iTrav] - 48 ;
  if (iNeighbors > 0 && iNeighbors < 9)
   m_iBirth[iNeighbors] = 1 ;
  iTrav ++ ;
 }
}

int Environment::CountNeighbors(int iX, int iY)
{
 int iTotal = 0 ;
 if (iY > 0)
 {
  if (iX > 0 && m_ppCurrent[iY-1][iX-1] == '*') iTotal ++ ;
  if (m_ppCurrent[iY-1][iX] == '*') iTotal ++ ;
  if (iX < m_iXSize && m_ppCurrent[iY-1][iX+1] == '*') iTotal ++ ;
 }

 if (iX > 0 && m_ppCurrent[iY][iX-1] == '*') iTotal ++ ;
 if (iX < m_iXSize && m_ppCurrent[iY][iX+1] == '*') iTotal ++ ;

 if (iY + 1 < m_iYSize)
 {
  if (iX > 0 && m_ppCurrent[iY+1][iX-1] == '*') iTotal ++ ;
  if (m_ppCurrent[iY+1][iX] == '*') iTotal ++ ;
  if (iX < m_iXSize && m_ppCurrent[iY+1][iX+1] == '*') iTotal ++ ;
 }
 return iTotal ;
}

void Environment::Update()
{
 int iTrav2, iNeighbors ;
 for (int iTrav = 0 ; iTrav < m_iYSize ; iTrav ++)
 {
  for (iTrav2 = 0 ; iTrav2 < m_iXSize ; iTrav2 ++)
  {
   iNeighbors = CountNeighbors(iTrav2, iTrav) ;
   if (m_ppCurrent[iTrav][iTrav2] == ' ' && m_iBirth[iNeighbors]) // birth
   {
	m_ppUpdated[iTrav][iTrav2] = '*' ;
   } else if (m_ppCurrent[iTrav][iTrav2] == '*' && m_iSurvival[iNeighbors]) // survival
   {
	m_ppUpdated[iTrav][iTrav2] = '*' ;
   } else m_ppUpdated[iTrav][iTrav2] = ' ' ; // overcrowding or loneliness
  }
 }
 char **ppTemp = m_ppCurrent ;
 m_ppCurrent = m_ppUpdated ;
 m_ppUpdated = ppTemp ;
}

void Environment::Output()
{
 gotoxy(1,1) ;
 for (int iTrav = 0 ; iTrav < m_iYSize ; iTrav ++)
 {
  printf("%s\n", m_ppCurrent[iTrav]) ;
 }
}