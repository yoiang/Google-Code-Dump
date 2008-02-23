#include "Main.h"

bool bPause, bRotate, bAutofire, bExplode ;
Entity Player ;
Model ShotsModel ;
Model Enemy01Model, Enemy02Model, Enemy03Model ;
Model Enemy01ShotModel, Enemy02ShotModel, Enemy03ShotModel ;
Entity *pPlayerShots ;
Entity *pEnemys ;
Entity *pEnemyShots ;

int iScore ;

LinkedList<Particle> Particles ;

int iCount ;

float randp()
{
	return float(rand())/float(RAND_MAX) ;
}

void DisplayParticle(Particle *pDisplay)
{
	glBegin(GL_POINTS) ;
	glColor4f(pDisplay->ptColor.dX, pDisplay->ptColor.dY, pDisplay->ptColor.dZ, pDisplay->dAlpha) ;
	glVertex3f(pDisplay->ptLocation.dX, pDisplay->ptLocation.dY, pDisplay->ptLocation.dZ) ;
	glEnd() ;

}

void InitOptions()
{
	bPause = false ;
	bRotate = false ;
	bAutofire = false ;
	bExplode = false ;
	Player.ReadModel("Models\\Player.ml") ;
	ShotsModel.ReadFile("Models\\Shot01.ml") ;
	Enemy01Model.ReadFile("Models\\Enemy01.ml") ;
	Enemy01ShotModel.ReadFile("Models\\EnemyShot01.ml") ;

	pPlayerShots = 0 ;
	pPlanets = 0 ;
	pStars = 0 ;
	pEnemys = 0 ;
	pEnemyShots = 0 ;

	iScore = 0 ;

	Player.ptLocation.dX = 0 ;
	Player.ptLocation.dY = 0 ;
	Player.ptLocation.dZ = -5 ;
	Player.ptDirection.dX = 0 ;
	Player.ptDirection.dY = 0 ;
	Player.ptDirection.dZ = 1 ;
	Player.ptAngle.dX = 0 ;
	Player.ptAngle.dY = 0 ;
	Player.ptAngle.dZ = 0 ;
}

void FireShot(Entity *pShootFrom, Entity *&pAddTo)
{
	Entity *pTemp = new Entity ;
	if (pAddTo == 0)
	{
		pAddTo = pTemp ;
		pTemp->pNext = 0 ;
		pTemp->pLast = 0 ;
	} else
	{
		pTemp->pNext = pAddTo->pNext ;
		if (pAddTo->pNext != 0) pAddTo->pNext->pLast = pTemp ;
		pTemp->pLast = pAddTo ;
		pAddTo->pNext = pTemp ;
	}
	pTemp->ptLocation = pShootFrom->ptLocation ;
	pTemp->ptAngle = pShootFrom->ptAngle ;
	pTemp->ptDirection = pShootFrom->ptDirection / 0.5 ;
	if (pShootFrom != &Player) pTemp->pModel = &Enemy01ShotModel ;
	else pTemp->pModel = &ShotsModel ;
}


void DisplayShots(Entity *&pShots)
{
	Entity *pTrav = pShots ;
	Entity *pTemp ;
	Point ptPlayerUFL, ptPlayerLBR, ptShotUFL, ptShotLBR ;
	ptPlayerUFL = Player.ptLocation + Player.pModel->ptBBUpperFrontLeft ;
	ptPlayerLBR = Player.ptLocation + Player.pModel->ptBBLowerBackRight ;

	while (pTrav != 0)
	{
		ptShotUFL = pTrav->ptLocation + pTrav->pModel->ptBBLowerBackRight ;
		ptShotLBR = pTrav->ptLocation + pTrav->pModel->ptBBUpperFrontLeft ;
		if (pTrav->ptLocation.dX < 50 && pTrav->ptLocation.dX > -50 &&
			pTrav->ptLocation.dZ < 100 && pTrav->ptLocation.dZ > -100)
		{
			if (!bExplode && (
					(ptPlayerUFL < ptShotUFL && ptPlayerLBR > ptShotUFL) || 
					(ptPlayerUFL < ptShotLBR && ptPlayerLBR > ptShotLBR) ||
					(ptShotUFL < ptPlayerUFL && ptShotLBR > ptPlayerUFL) || 
					(ptShotUFL < ptPlayerLBR && ptShotLBR > ptPlayerLBR)))
			{
				bExplode = true ;
				iCount = 0 ;
			}
			pTrav->Display() ;
			if (!bPause) pTrav->ptLocation = pTrav->ptLocation + pTrav->ptDirection ;
			pTrav = pTrav->pNext ;
		} else 
		{
			pTemp = pTrav ;
			pTrav = pTrav->pNext ;
			pTemp->pModel = 0 ;
			RemoveEntity(pShots, pTemp) ;
		}
	}
}

void SpawnEnemy()
{
	Entity *pTemp = new Entity ;
	if (pEnemys == 0)
	{
		pEnemys = pTemp ;
		pTemp->pNext = 0 ;
		pTemp->pLast = 0 ;
	} else
	{
		pTemp->pNext = pEnemys->pNext ;
		if (pEnemys->pNext != 0) pEnemys->pNext->pLast = pTemp ;
		pTemp->pLast = pEnemys ;
		pEnemys->pNext = pTemp ;
	}
	pTemp->ptDirection.dX = 0.0 ;
	pTemp->ptDirection.dY = 0.0 ;
	pTemp->ptDirection.dZ = randp() * -0.8 ;

	pTemp->ptAngle.dX = 180.0 ;
	pTemp->ptAngle.dY = 0.0 ;

	pTemp->ptLocation.dX = randp() * 20 - 10  ;
	pTemp->ptLocation.dY = 0 ;
	pTemp->ptLocation.dZ = 100 ;

	pTemp->ptAngle.dZ = 0.0 ;

	pTemp->pModel = &Enemy01Model ;
}


void MakeExplosion(Point ptLocation, int iNumParticles)
{
	for (int iTrav = 0 ; iTrav < iNumParticles ; iTrav ++)
	{
		Particle *pNew = new Particle ;
		pNew->ptLocation.dX = ptLocation.dX ;
		pNew->ptLocation.dY = ptLocation.dY ;
		pNew->ptLocation.dZ = ptLocation.dZ ;
		pNew->ptVelocity.dX = 2 * randp() - 1 ;
		pNew->ptVelocity.dY = 2 * randp() - 1 ;
		pNew->ptVelocity.dZ = 2 * randp() - 1 ;
		pNew->ptColor.dX = 0.98 ;
		pNew->ptColor.dY = 0.59 + 0.3 * randp() - 0.15 ;
		pNew->ptColor.dZ = 0.01 ;
		pNew->dAlpha = 0.7 ;
		pNew->dMass = 1 ;
		pNew->dLife = 4 * randp() + 3 ;
		pNew->ptAcceleration = 0 ;
		Particles.AddBack(pNew) ;
	}
}

void DisplayEnemies()
{
	Entity *pTrav = pEnemys ;
	Entity *pTravShots ;
	Entity *pTemp ;
	bool bShot ;
	Point ptBBModelUFL, ptBBModelLBR, ptBBShotUFL, ptBBShotLBR ;
	while (pTrav != 0)
	{
		if (pTrav->ptLocation.dZ > -100)
		{
			ptBBModelUFL = pTrav->ptLocation + pTrav->pModel->ptBBUpperFrontLeft ;
			ptBBModelLBR = pTrav->ptLocation + pTrav->pModel->ptBBLowerBackRight ;

			bShot = false ;
			pTravShots = pPlayerShots ;
			while (pTravShots != 0)
			{
				ptBBShotUFL = pTravShots->ptLocation + pTravShots->pModel->ptBBUpperFrontLeft ;
				ptBBShotLBR = pTravShots->ptLocation + pTravShots->pModel->ptBBLowerBackRight ;

				if ((ptBBModelUFL < ptBBShotUFL && ptBBModelLBR > ptBBShotUFL) || 
					(ptBBModelUFL < ptBBShotLBR && ptBBModelLBR > ptBBShotLBR))
				{
					bShot = true ;

					MakeExplosion(pTrav->ptLocation, 500) ;

					if (!bExplode)
					{
						iScore += 100 ;
						printf ("Score: %i\n", iScore) ;
					}

					pTemp = pTrav ;
					pTrav = pTrav->pNext ;
					pTemp->pModel = 0 ;
					RemoveEntity(pEnemys, pTemp) ;
					pTravShots->pModel = 0 ;
					RemoveEntity(pPlayerShots, pTravShots) ;
					break ;
				}
				pTravShots = pTravShots->pNext ;
			}

			if (!bShot)
			{
				ptBBShotUFL = Player.ptLocation + Player.pModel->ptBBUpperFrontLeft ;
				ptBBShotLBR = Player.ptLocation + Player.pModel->ptBBLowerBackRight ;

				if (!bExplode && ((ptBBModelUFL < ptBBShotUFL && ptBBModelLBR > ptBBShotUFL) || 
									(ptBBModelUFL < ptBBShotLBR && ptBBModelLBR > ptBBShotLBR)))
				{
					bExplode = true ;
					iCount = 0 ; 

					MakeExplosion(pTrav->ptLocation, 500) ;
					pTemp = pTrav ;
					pTrav = pTrav->pNext ;
					pTemp->pModel = 0 ;
					RemoveEntity(pEnemys, pTemp) ;
				} else
				{
//					if (randp() > 0.99)
					if (!bExplode && randp() > 0.99)
						FireShot(pTrav, pEnemyShots) ;
					pTrav->Display() ;
					if (!bPause) pTrav->ptLocation = pTrav->ptLocation + pTrav->ptDirection ;
					pTrav = pTrav->pNext ;
				}
			}
		} else 
		{
			pTemp = pTrav ;
			pTrav = pTrav->pNext ;
			pTemp->pModel = 0 ;
			RemoveEntity(pEnemys, pTemp) ;
		}
	}
}

void DisplayHandler () // display callback function
{
	if (bRotate) 
	{
		fCameraAngle[0] += 1.0 ;
		fCameraAngle[2] += 1.0 ;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	glLoadIdentity() ;

	SetCamera() ;

	if (!bPause)
	{
		GLfloat fTempX = GLfloat(iLastMouseX) / GLfloat(iWinWidth) ;
		GLfloat fTempY = GLfloat(iLastMouseY) / GLfloat(iWinHeight) ;
		GLfloat fFixedX = (Player.ptLocation.dX - 8.65) / -17.3 ;
		GLfloat fFixedZ = (Player.ptLocation.dZ - 8.65) / -17.3 ;
		if (bRightMouseDown)
		{
			if (!(fFixedX + 0.02 > fTempX && fFixedX - 0.02 < fTempX))
			{
				if (fFixedX > fTempX)
				{
					Player.ptLocation.dX += 0.1 ;
					if (Player.ptAngle.dZ > -20) 
						Player.ptAngle.dZ -= 5.0 ;
				} else
				{
					Player.ptLocation.dX -= 0.1 ;
					if (Player.ptAngle.dZ < 20) 
						Player.ptAngle.dZ += 5.0 ;
				}
			} else
			{
				if (Player.ptAngle.dZ < 0) Player.ptAngle.dZ += 5.0 ;
				else if (Player.ptAngle.dZ > 0)	Player.ptAngle.dZ -= 5.0 ;
			}
			if (!(fFixedZ + 0.1 > fTempY && fFixedZ - 0.02 < fTempY))
			{
				if (fFixedZ > fTempY)
				{
					Player.ptLocation.dZ += 0.1 ;
				} else 
				{
					Player.ptLocation.dZ -= 0.1 ;
				}
			}
		} else Player.ptAngle.dZ = 0 ;

		if (randp() > 0.98) AddPlanet() ;
		AddStar() ;
		AddStar() ;
		AddStar() ;
		AddStar() ;
		AddStar() ;
		AddStar() ;

		if (/*!bExplode && */iCount % 15 == 0) SpawnEnemy() ;

		if (!bExplode && bAutofire && iCount % 4 == 0) FireShot(&Player, pPlayerShots) ;

		iCount ++ ;

	}
	
	DisplayStars() ;
	DisplayPlanets() ;
	DisplayEnemies() ;

	DisplayShots(pPlayerShots) ;
	DisplayShots(pEnemyShots) ;

	if (bExplode && !bPause)
	{
		if (iCount == 0) 
		{
			printf("Game over\n") ;
			MakeExplosion(Player.ptLocation, 1000) ;
		}
	} else 
	{
		if (iCount % 4)
		{
			Particle *pNew = new Particle ;
			pNew->ptLocation.dX = Player.ptLocation.dX + randp() * 0.5 - 0.25;
			pNew->ptLocation.dY = Player.ptLocation.dY + 0.3 * randp() ;
			pNew->ptLocation.dZ = Player.ptLocation.dZ - 1.5 + 0.2 * randp() ;
			pNew->ptVelocity.dX = 0 ;
			pNew->ptVelocity.dY = 0 ;
			pNew->ptVelocity.dZ = -0.2 ;
			pNew->ptColor.dX = 0.98 ;
			pNew->ptColor.dY = 0.59 + 0.3 * randp() - 0.15 ;
			pNew->ptColor.dZ = 0.01 ;
			pNew->dAlpha = 0.7 ;
			pNew->dMass = 1 ;
			pNew->dLife = 7 * randp() + 3 ;
			pNew->ptAcceleration = 0 ;
			Particles.AddBack(pNew) ;
		}

		Player.Display() ;
	}

	LinkedListNode<Particle> *pTravParticles = Particles.pHead ;
	LinkedListNode<Particle> *pTempParticle ;
	
	while (pTravParticles != 0)
	{
		pTravParticles->pValue->dLife -- ;
		if (pTravParticles->pValue->dLife <= 0)
		{
			pTempParticle = pTravParticles ;
			pTravParticles = pTravParticles->pNext ;
			Particles.Remove(pTempParticle, true) ;
		} else
		{
			pTravParticles->pValue->Apply(0.9) ;
			
			DisplayParticle(pTravParticles->pValue) ;
			
			pTravParticles = pTravParticles->pNext ;
		}
	}
	
		
	glFinish() ;
	glutSwapBuffers() ;
	glutPostRedisplay() ;
}

void MouseButtonHandler (int iButton, int iState, int iX, int iY) // mouse button handler
{
	iLastMouseY = iY ;
	iLastMouseX = iX ;
	if (iButton == GLUT_RIGHT_BUTTON)
	{

		if (iState == GLUT_DOWN) 
		{
			bRightMouseDown = true ;
		}
		else 
		{
			bRightMouseDown = false ;
		}
	} else if (iButton == GLUT_LEFT_BUTTON)
	{
		if (iState == GLUT_DOWN) 
		{
			bLeftMouseDown = true ;
			if (!bExplode && !bPause) FireShot(&Player, pPlayerShots) ;
		}
		else 
		{
			bLeftMouseDown = false ;	
		}
	}
}

void MotionHandler(int iX, int iY)
{
	iLastMouseY = iY ;
	iLastMouseX = iX ;
}

void KeyboardHandler (unsigned char cKey, int iX, int iY) // keyboard input handling function
{
	switch (cKey)
	{
	case 'p' :
	case 'P' :
		bPause = !bPause ;
	break ;
#ifdef _DEBUG
	case 'm' : // toggle filling
	case 'M' :
		ToggleFilling(!bFilling) ;
	break ;

	case 'n' : // toggle lighting
	case 'N' :
		ToggleLighting(!bLighting) ;
	break ;
#endif

	case 'i' : 
	case 'I' :
		InitCamera(10) ;
	break ;

	case 'a' :
	case 'A' :
		bAutofire = !bAutofire ;
	break ;

	case ' ' :
		if (!bExplode && !bPause) FireShot(&Player, pPlayerShots) ;
	break ;
	case 'w' :
	case 'W' :
		fCameraAngle[0] += 10 ;
	break ;
	case 'x' :
	case 'X' :
		fCameraAngle[0] -= 10 ;
	break ;
	case 's' :
    case 'S' :
		fCameraAngle[2] += 10 ;
	break ;
	case 'd' :
	case 'D' :
		fCameraAngle[2] -= 10 ;
	break ;

	case 'r' :
	case 'R' :
		iScore = 0 ;
		bExplode = !bExplode ;
		iCount = 0 ;
	break ;

	case 'c' :
	case 'C' :
		bRotate = !bRotate ;
	break ;

	case 'q' : // quit program
	case 'Q' :
		ClearEntitys(pPlayerShots) ;
		ClearEntitys(pEnemyShots) ;
		ClearEntitys(pStars) ;
		ClearEntitys(pPlanets) ;

		Particles.Clear(true) ;
		exit(0) ;
	break ;
	}
}

int main(int argc, char **argv)
{ 
	srand( (unsigned)time( NULL ) );
	
	InitGLUT(argc, argv, "Shooter", 500, 500) ;
	InitDisplay(true, true, false) ; 
	InitCamera(10) ;
	InitMouse() ;

	glutDisplayFunc(DisplayHandler) ;
 	glutKeyboardFunc(KeyboardHandler) ;
	glutMouseFunc(MouseButtonHandler) ;
	glutMotionFunc(MotionHandler) ;

	InitOptions() ;

 	glutMainLoop() ;
 
	return 0 ;
}
