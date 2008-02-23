/*

  Exit.h
  Version 0.004.000

*/

#ifndef __EXIT_H_
#define __EXIT_H_

class Exit
{
private:
// Entity *pOwner ;
 
public:
 char *szRoomTo ;
 Entity *pRoomTo ;

// unsigned int uFlags ;

// Exit();          // Default contructor
// ~Exit();         // Destructor

// int Spawn () ;
// int Die () ;
} ;

#define EXITFM(x) (void *)&(((Exit *)0)->x)

extern PField ExitPField [] ;
extern PFField ExitPFField [] ;

#endif // __EXIT_H_
/*
struct	exit_data
{
	 EXIT_DATA *		prev;		// previous exit in linked list
	 EXIT_DATA *		next;		// next exit in linked list
	 EXIT_DATA *		rexit;		// Reverse exit pointer
	 ROOM_INDEX_DATA *	to_room;	// Pointer to destination room
	 char *		keyword;	// Keywords for exit or door
	 char *		description;	// Description of exit
	 int			vnum;		// Vnum of room exit leads to
    int			rvnum;		// Vnum of room in opposite dir	
    int			exit_info;	// door states & other flags	
    int			key;		// Key vnum			
    sh_int		vdir;		// Physical "direction"		
    sh_int		distance;	// how far to the next room	
    sh_int		pull;		// pull of direction (current)	
    sh_int		pulltype;	// type of pull (current, wind)	
};*/

