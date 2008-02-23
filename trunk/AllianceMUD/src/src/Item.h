/*

  Item.h
  Version 0.004.000

*/

#ifndef __ITEM_H_
#define __ITEM_H_

class Item
{
private:
// Entity *pOwner ;

public:
// Item () ;
// ~Item () ;

// int Spawn () ;
// int Die () ;
};

#define ITEMFM(x) (void *)&(((Item *)0)->x)

extern PField ItemPField [] ;
extern PFField ItemPFField [] ;

#endif // __ITEM_H_

/*
struct	obj_data
{
	 OBJ_DATA *		next;
	 OBJ_DATA *		prev;
	 OBJ_DATA *		next_content;
	 OBJ_DATA *		prev_content;
	 OBJ_DATA *		first_content;
    OBJ_DATA *		last_content;
    OBJ_DATA *		in_obj;
    CHAR_DATA *		carried_by;
    EXTRA_DESCR_DATA *	first_extradesc;
    EXTRA_DESCR_DATA *	last_extradesc;
    AFFECT_DATA *	first_affect;
    AFFECT_DATA *	last_affect;
    OBJ_INDEX_DATA *	pIndexData;
    ROOM_INDEX_DATA *	in_room;
    char *		name;
    char *		short_descr;
    char *		description;
    char *		action_desc;
	 sh_int		item_type;
    sh_int		mpscriptpos;
    EXT_BV		extra_flags;
    int			magic_flags; //Need more bitvectors for spells - Scryn
    int			wear_flags; 
    MPROG_ACT_LIST *	mpact;		// mudprogs 
    int			mpactnum;	// mudprogs 
    sh_int		wear_loc;
    sh_int		weight;
    int			cost;
    sh_int		level;
	 sh_int		timer;
	 int			value	[6];
	 sh_int		count;		// support for object grouping
	 int			serial;		// serial number
};

{
    OBJ_INDEX_DATA *	next;
    OBJ_INDEX_DATA *	next_sort;
    EXTRA_DESCR_DATA *	first_extradesc;
    EXTRA_DESCR_DATA *	last_extradesc;
    AFFECT_DATA *	first_affect;
    AFFECT_DATA *	last_affect;
    MPROG_DATA *	mudprogs;               // objprogs 
    EXT_BV		progtypes;              // objprogs 
    char *		name;
	 char *		short_descr;
	 char *		description;
    char *		action_desc;
    int			vnum;
    sh_int              level;
    sh_int		item_type;
    EXT_BV		extra_flags;
    int			magic_flags; // Need more bitvectors for spells - Scryn
    int			wear_flags;
    sh_int		count;
    sh_int		weight;
    int			cost;
    int			value	[6];
    int			serial;
    sh_int		layers;
    int			rent;			// Unused 
*/
