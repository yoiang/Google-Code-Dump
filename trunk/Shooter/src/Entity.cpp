#include "Entity.h"


Entity::Entity()
{
	pModel = 0 ;
}

Entity::~Entity()
{
	if (pModel != 0) delete pModel ;
}

void Entity::Display()
{
	glPushMatrix() ;
	glTranslatef(ptLocation.dX, ptLocation.dY, ptLocation.dZ) ;
	if (ptAngle.dX != 0) glRotatef(ptAngle.dX, 1.0, 0.0, 0.0) ;
	if (ptAngle.dY != 0) glRotatef(ptAngle.dY, 0.0, 1.0, 0.0) ;
	if (ptAngle.dZ != 0) glRotatef(ptAngle.dZ, 0.0, 0.0, 1.0) ;

	pModel->Display() ;
	glPopMatrix() ;
}

void Entity::ReadModel(char *szFilename)
{
	if (pModel != 0) delete pModel ;
	pModel = new Model ;
	pModel->ReadFile(szFilename) ;
}

void Entity::SetDirection(Point ptSetDirection)
{
	ptDirection = ptSetDirection ;
//	ptAngle.dX = 
}

void ClearEntitys(Entity *&pHead)
{
	Entity *pTemp = pHead ;
	while (pTemp != 0)
	{
		pHead = pHead->pNext ;
		pTemp->pModel = 0 ;
		delete pTemp ;
		pTemp = pHead ;
	}
}

void RemoveEntity(Entity *&pHead, Entity *pRemove)
{
	if (pRemove == pHead) 
	{
		pHead->pLast = 0 ;
		pHead = pHead->pNext ;
	} else
	{
		pRemove->pLast->pNext = pRemove->pNext ;
		if (pRemove->pNext != 0) pRemove->pNext->pLast = pRemove->pLast ;
	}
	delete pRemove ;
}