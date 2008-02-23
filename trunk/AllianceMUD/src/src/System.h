/*

  System.h
  Version 0.004.000

*/

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

class System
{
private:
// Entity *pOwner ;

public:
// System() ;
// ~System() ;

// int Spawn () ;
// int Die () ;
 
// Entity **ppBodys ;         // Dynamic array of pointers to Entitys of Bodys contained in this System
// handle hNumppBodys ;       // Number of nodes in ppBodys
} ;

#define SYSTEMFM(x) (void *)&(((System *)0)->x)

extern PField SystemPField [] ;
extern PFField SystemPFField [] ;

#endif // __SYSTEM_H_