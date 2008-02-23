#include "Background.h"

Entity *pPlanets, *pStars ;

void AddStar()
{
	Entity *pTemp = new Entity ;
	if (pStars == 0)
	{
		pStars = pTemp ;
		pTemp->pNext = 0 ;
		pTemp->pLast = 0 ;
	} else
	{
		pTemp->pNext = pStars->pNext ;
		if (pStars->pNext != 0) pStars->pNext->pLast = pTemp ;
		pTemp->pLast = pStars ;
		pStars->pNext = pTemp ;
	}
	float fColorChance = GLfloat(rand()) / GLfloat(RAND_MAX) ;
	if (fColorChance > 0.75)
	{
		fColorChance = GLfloat(rand()) / GLfloat(RAND_MAX) ;
		pTemp->ptAngle.dX = 1.0 - fColorChance * 0.1 ;
		pTemp->ptAngle.dY = 1.0 - fColorChance * 0.1 ;
		pTemp->ptAngle.dZ = 1.0 - fColorChance * 0.1 ;
	} else
	{
		pTemp->ptAngle.dX = 0.35 + fColorChance * 0.2 ;
		pTemp->ptAngle.dY = 0.43 + fColorChance * 0.2 ;
		pTemp->ptAngle.dZ = 0.40 + fColorChance * 0.2 ;
	}
	pTemp->ptLocation.dX = GLfloat(rand()) / GLfloat(RAND_MAX) * 50 ;
	if (GLfloat(rand()) / GLfloat(RAND_MAX) > 0.5) pTemp->ptLocation.dX *= -1 ;
	pTemp->ptLocation.dY = GLfloat(rand()) / GLfloat(RAND_MAX) * 50 ;
	if (GLfloat(rand()) / GLfloat(RAND_MAX) > 0.5) pTemp->ptLocation.dY *= -1 ;
//	pTemp->ptLocation.dY = -40 - (pTemp->ptAngle.dX + pTemp->ptAngle.dY + pTemp->ptAngle.dZ) ;
	pTemp->ptLocation.dZ = 100 ;
	pTemp->pModel = 0 ;
	pTemp->ptDirection.dZ = (pTemp->ptAngle.dX + pTemp->ptAngle.dY + pTemp->ptAngle.dZ) / 3 * -0.5 ;
}

void DisplayStars()
{
	Entity *pTrav = pStars ;
	Entity *pTemp ;
	glBegin(GL_POINTS) ;
	while (pTrav != 0)
	{
		if (!bPause) pTrav->ptLocation.dZ = pTrav->ptLocation.dZ + pTrav->ptDirection.dZ ;
		if (pTrav->ptLocation.dZ > -100)
		{
			glColor3f(pTrav->ptAngle.dX, pTrav->ptAngle.dY, pTrav->ptAngle.dZ) ; 

			glVertex3f(pTrav->ptLocation.dX, pTrav->ptLocation.dY, pTrav->ptLocation.dZ) ;

			pTrav = pTrav->pNext ;
		} else 
		{
			pTemp = pTrav ;
			pTrav = pTrav->pNext ;
			RemoveEntity(pStars, pTemp) ;
		}
	}
	glEnd() ;
}

void AddPlanet()
{
	Entity *pTemp = new Entity ;
	if (pPlanets == 0)
	{
		pPlanets = pTemp ;
		pTemp->pNext = 0 ;
		pTemp->pLast = 0 ;
	} else
	{
		pTemp->pNext = pPlanets->pNext ;
		if (pPlanets->pNext != 0) pPlanets->pNext->pLast = pTemp ;
		pTemp->pLast = pPlanets ;
		pPlanets->pNext = pTemp ;
	}
	float fColorChance = GLfloat(rand()) / GLfloat(RAND_MAX) ;
	if (fColorChance > 0.95)
	{
		pTemp->ptAngle.dX = 0 ;
		pTemp->ptAngle.dY = 0.8 + GLfloat(rand()) / GLfloat(RAND_MAX) * 0.1 ;
		pTemp->ptAngle.dZ = 0 ;
	} else if (fColorChance > 0.7)
	{
		pTemp->ptAngle.dX = 0.15 ;
		pTemp->ptAngle.dY = 0.07 ;
		pTemp->ptAngle.dZ = 0.91 + GLfloat(rand()) / GLfloat(RAND_MAX) * 0.1 ;
	} else if (fColorChance > 0.5)
	{
		pTemp->ptAngle.dX = 0.6 + GLfloat(rand()) / GLfloat(RAND_MAX) * 0.1 ;
		pTemp->ptAngle.dY = 0.27 ;
		pTemp->ptAngle.dZ = 0.09 ;
	} else
	{
		pTemp->ptAngle.dX = 0.38 + GLfloat(rand()) / GLfloat(RAND_MAX) * 0.1 ;
		pTemp->ptAngle.dY = 0.47 + GLfloat(rand()) / GLfloat(RAND_MAX) * 0.1 ;
		pTemp->ptAngle.dZ = 0.41 + GLfloat(rand()) / GLfloat(RAND_MAX) * 0.1 ;
	}
	pTemp->pModel = 0 ;
	pTemp->ptDirection.dX = GLfloat(rand()) / GLfloat(RAND_MAX) * 5.0 ;
	pTemp->ptDirection.dY = 0 ;
	pTemp->ptLocation.dX = GLfloat(rand()) / GLfloat(RAND_MAX) * 100 + 15 ;
	if (GLfloat(rand()) / GLfloat(RAND_MAX) > 0.5) pTemp->ptLocation.dX *= -1 ;
	pTemp->ptLocation.dY = GLfloat(rand()) / GLfloat(RAND_MAX) * 100 + 15 ;
	if (GLfloat(rand()) / GLfloat(RAND_MAX) > 0.5) pTemp->ptLocation.dY *= -1 ;
//	pTemp->ptLocation.dY = -30 - pTemp->ptDirection.dX * 2 ;
	pTemp->ptLocation.dZ = 200 ;
//	pTemp->ptDirection.dZ = GLfloat(rand()) / GLfloat(RAND_MAX) * -0.5 * (pTemp->ptDirection.dX / 5.0) ;
	pTemp->ptDirection.dZ = (pTemp->ptDirection.dX / 5.0) * -0.5 ;
}

void DisplayPlanets()
{
	Entity *pTrav = pPlanets ;
	Entity *pTemp ;
	while (pTrav != 0)
	{
		if (!bPause) pTrav->ptLocation.dZ = pTrav->ptLocation.dZ + pTrav->ptDirection.dZ ;
		if (pTrav->ptLocation.dZ > -100)
		{
			glPushMatrix() ;

			glTranslatef(pTrav->ptLocation.dX, pTrav->ptLocation.dY, pTrav->ptLocation.dZ) ;
			glScalef(pTrav->ptDirection.dX, pTrav->ptDirection.dX, pTrav->ptDirection.dX) ;
			glColor3f(pTrav->ptAngle.dX, pTrav->ptAngle.dY, pTrav->ptAngle.dZ) ; 

			if (bFilling) glutSolidSphere(1.0, 10, 10) ;
			else glutWireSphere(1.0, 10, 10) ;

			glPopMatrix() ;
			pTrav = pTrav->pNext ;
		} else 
		{
			pTemp = pTrav ;
			pTrav = pTrav->pNext ;
			RemoveEntity(pPlanets, pTemp) ;
		}
	}
}

