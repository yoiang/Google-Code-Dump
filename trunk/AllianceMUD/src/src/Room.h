/*

  Room.h
  Version 0.004.000

*/

#ifndef __ROOM_H_
#define __ROOM_H_

class Room
{
private:
// Entity *pOwner ;
 
public:
// Room() ;
// ~Room() ;

// int Spawn () ;
// int Die () ;

// Item *pItems ; // hash table
// handle hNumpItems ;

// handle hNumpMobs ;
// Mob *pMobs ; // hash table

// Exit *pExits ; // hash table
// handle hNumpExits ;
} ;

#define ROOMFM(x) (void *)&(((Room *)0)->x)

extern PField RoomPField [] ;
extern PFField RoomPFField [] ;

#endif // __ROOM_H_

/*
struct	room_index_data
{
	 ROOM_INDEX_DATA *	next;
	 ROOM_INDEX_DATA *	next_sort;
	 CHAR_DATA *		first_person;	    // people in the room
	 CHAR_DATA *		last_person;	    //		..
	 OBJ_DATA *		first_content;	    // objects on floor
	 OBJ_DATA *		last_content;	    //		..
	 EXTRA_DESCR_DATA *	first_extradesc;    // extra descriptions
    EXTRA_DESCR_DATA *	last_extradesc;	    //		..		
    AREA_DATA *		area;
    EXIT_DATA *		first_exit;	    // exits from the room	
    EXIT_DATA *		last_exit;	    //		..		
    AFFECT_DATA *	first_affect;	    // effects on the room	
    AFFECT_DATA *	last_affect;	    //		..		
    MAP_DATA *		map;		    // maps 
    PLANE_DATA *	plane;		    // do it by room rather than area 
    MPROG_ACT_LIST *	mpact;		    // mudprogs 
	 int			mpactnum;	    // mudprogs
    MPROG_DATA *	mudprogs;	    // mudprogs 
    sh_int		mpscriptpos;
    char *		name;
    char *		description;
    int			vnum;
    int			room_flags;
    EXT_BV		progtypes;           // mudprogs 
    sh_int		light;		     // amount of light in the room 
    sh_int		sector_type;
    int			tele_vnum;
    sh_int		tele_delay;
    sh_int		tunnel;		     // max people that will fit 
};
*/

