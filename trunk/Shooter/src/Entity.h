#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <math.h>

#include "Point.h"
#include "Model.h"

class Entity
{
private:
public:
	Model *pModel ;
	Point ptLocation ;
	Point ptDirection ;
	Point ptAngle ;

	Entity *pNext ;
	Entity *pLast ;

public:
	Entity() ;
	~Entity() ;

	void Display() ;
	void ReadModel(char *szFilename) ;
//	void Move() ;
	void SetDirection (Point ptSetDirection) ;
} ;

void ClearEntitys(Entity *&pHead) ;
void RemoveEntity(Entity *&pHead, Entity *pRemove) ;

#endif