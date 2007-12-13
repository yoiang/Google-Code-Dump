#include <conio.h>

#include "Environment.h"

//80 X 26
//http://www.math.com/students/wonders/life/life.html
//http://psoup.math.wisc.edu/mcell/ca_files_formats.html

int main ()
{
 int iCycle = 0 ;
 Environment Board(75, 24) ;
 int iKeyInput = 0 ;
 while (iKeyInput != 27)
 {
  Board.Output() ;
#ifdef _DEBUG
  printf("%i", iKeyInput) ;
#endif
  if (iCycle == 25)
  {
   Board.Update() ;
   iCycle = 0 ;
  }
  if (_kbhit())
  {
   iKeyInput = getch() ;
  }
  if (iKeyInput == 114)
  {
   Board.Clear(1) ;
   iKeyInput = 0 ;
  } else if (iKeyInput == 99)
  {
   Board.Clear(0) ;
   iKeyInput = 0 ;
  }
  iCycle ++ ;
 }
 return 0 ;
}