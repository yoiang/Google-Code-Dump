#include "ParticleSource.h"


ParticleSource::ParticleSource()	// constructor, set default values
{
	bRespawn = false ;
	bLines = false ;
	bWind = false ;
	bGravity = false ;
	bTexture = false ;
	bFade = true ;
	bWrongAcceleration = true ;
	bDie = true ;

	iTextureName = -1 ;

	ptInitialLocation = Point(0, 0.5, 0) ;
	ptLocationDeviation = Point(2, 0, 2) ;

	ptInitialVelocity = Point(0, 4, 0) ;
	ptVelocityDeviation = Point(2, 1, 2) ;

	ptWindAcceleration = Point(4, 0, 0) ;
	ptGravityAcceleration = Point(0, -9.8, 0) ;

	ptInitialColor = Point(0.5, 0.5, 0.5) ;
	ptColorDeviation = Point(0.5, 0.5, 0.5) ;
	ptColorIncrimenter = Point(0.0, 0.0, 0.0) ;

	dInitialLife = 1.5 ;
	dLifeDeviation = 0.6 ;
	dLifeIncrimenter = -0.01 ;

	ptScale = 1.0 ;
}

ParticleSource::~ParticleSource()	// destructor, clear memory
{
	Particles.Clear(true) ;
}

void ParticleSource::SetTexture(char *szFilename)	// set texture for particles
{
	pTextureImage = auxDIBImageLoad(szFilename) ;
	glGenTextures(1, &iTextureName);

	glBindTexture(GL_TEXTURE_2D, iTextureName);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage->sizeX, pTextureImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
}

void ParticleSource::SpawnParticles(int iNumSpawn)	// spawn specified number of particles
{
	Particle *pNew ;
	for (int iTrav = 0 ; iTrav < iNumSpawn ; iTrav ++)
	{
		pNew = new Particle ;

		pNew->ptLocation = CalcInitial(ptInitialLocation, ptLocationDeviation);
		pNew->ptPreviousLocation = pNew->ptLocation ;
		pNew->ptVelocity = CalcInitial(ptInitialVelocity, ptVelocityDeviation) ;

		pNew->dLife = dInitialLife + dLifeDeviation * randp() - dLifeDeviation / 2.0 ;
		pNew->dLifeIncrimenter = dLifeIncrimenter ;

		pNew->ptColor = CalcInitial(ptInitialColor, ptColorDeviation) ;
		pNew->ptColorIncrimenter = ptColorIncrimenter ;

		Particles.AddBack(pNew) ;
	}
}

void BillboardSpherical(Point ptCam, Point ptWorldPos)	// billboard calculation
{
	float angleCosine;
	Point ptLookAt(0, 0, 1) ;
	Point ptObjToCamProj ;
	Point ptObjToCam ;
	Point ptUpAux ;

// objToCamProj is the vector in world coordinates from the local origin to the camera
// projected in the XZ plane
	ptObjToCamProj.dVal[0] = ptCam.dVal[0] - ptWorldPos.dVal[0] ;
	ptObjToCamProj.dVal[1] = 0;
	ptObjToCamProj.dVal[2] = ptCam.dVal[2] - ptWorldPos.dVal[2] ;

// normalize both vectors to get the cosine directly afterwards
	Normalize(ptObjToCamProj);

// easy fix to determine wether the angle is negative or positive
// for positive angles upAux will be a vector pointing in the 
// positive y direction, otherwise upAux will point downwards
// effectively reversing the rotation.

	CrossProduct(ptLookAt, ptObjToCamProj, ptUpAux);

// compute the angle
	angleCosine = InnerProduct(ptLookAt, ptObjToCamProj);

// perform the rotation. The if statement is used for stability reasons
// if the lookAt and v vectors are too close together then |aux| could
// be bigger than 1 due to lack of precision
	if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
		glRotatef(acos(angleCosine)*180/3.14, ptUpAux.dVal[0], ptUpAux.dVal[1], ptUpAux.dVal[2]);	


// The second part tilts the object so that it faces the camera

// objToCam is the vector in world coordinates from the local origin to the camera
	ptObjToCam.dVal[0] = ptCam.dVal[0] - ptWorldPos.dVal[0] ;
	ptObjToCam.dVal[1] = ptCam.dVal[1] - ptWorldPos.dVal[1] ;
	ptObjToCam.dVal[2] = ptCam.dVal[2] - ptWorldPos.dVal[2] ;

// Normalize to get the cosine afterwards
	Normalize(ptObjToCam);

// Compute the angle between v and v2, i.e. compute the
// required angle for the lookup vector
	angleCosine = InnerProduct(ptObjToCamProj,ptObjToCam);


// Tilt the object. The test is done to prevent instability when objToCam and objToCamProj have a very small
// angle between them
	if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
		if (ptObjToCam.dVal[1] < 0)
			glRotatef(acos(angleCosine)*180/3.14,1,0,0);	
		else
			glRotatef(acos(angleCosine)*180/3.14,-1,0,0);	

}

void ParticleSource::DisplayParticleTextured(Particle *pParticle, Point ptCameraLocation)	// display particle textured
{
	if (bFade) glColor4f(pParticle->ptColor.dVal[0],
						 pParticle->ptColor.dVal[1],
						 pParticle->ptColor.dVal[2],
						 pParticle->dLife) ;
	else glColor4f(pParticle->ptColor.dVal[0],
				   pParticle->ptColor.dVal[1],
				   pParticle->ptColor.dVal[2],
				   1.0) ;

	glPushMatrix() ;
				
	glTranslatef(pParticle->ptLocation.dVal[0],
				 pParticle->ptLocation.dVal[1],
				 pParticle->ptLocation.dVal[2]) ;
	BillboardSpherical(ptCameraLocation, pParticle->ptLocation) ;
				
	if (ptScale.dVal[0] != 1.0 || ptScale.dVal[1] != 1.0 || ptScale.dVal[2] != 1.0) 
		glScalef(ptScale.dVal[0], ptScale.dVal[1], ptScale.dVal[2]) ;

	glBegin(GL_TRIANGLE_STRIP);					
	glTexCoord2d(1,1); glVertex3f(0.5f,0.5f,0); // Top Right
	glTexCoord2d(0,1); glVertex3f(-0.5f,0.5f,0); // Top Left
	glTexCoord2d(1,0); glVertex3f(0.5f,-0.5f,0); // Bottom Right
	glTexCoord2d(0,0); glVertex3f(-0.5f,-0.5f,0); // Bottom Left
	glEnd();

	glPopMatrix() ;
}

void ParticleSource::DisplayParticles(Point ptCameraLocation)	// display all particles
{
	LinkedListNode<Particle> *pTravParticles = Particles.pHead ;
	if (bLines)
	{
		glBegin(GL_POINTS) ;
		while (pTravParticles != 0)
		{
			glVertex3fv(pTravParticles->pValue->ptLocation.dVal) ;
			glEnd() ;

			if (bTexture && iTextureName != -1)
			{	
				glEnable(GL_BLEND) ;
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, iTextureName);

				DisplayParticleTextured(pTravParticles->pValue, ptCameraLocation) ;

				glDisable(GL_TEXTURE_2D) ;
				glDisable(GL_BLEND) ;
			} else
			{
				glColor3fv(pTravParticles->pValue->ptColor.dVal) ;
				glBegin(GL_POINTS) ;
				glVertex3fv(pTravParticles->pValue->ptLocation.dVal) ;
				glEnd() ;
			}

			glColor3fv(pTravParticles->pValue->ptColor.dVal) ;
			glBegin(GL_LINES) ;
			glVertex3fv(pTravParticles->pValue->ptLocation.dVal) ;

			pTravParticles = pTravParticles->pNext ;
		}
		glEnd() ;
	} else
	{
			if (bTexture && iTextureName != -1)
			{	
				glEnable(GL_BLEND) ;
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, iTextureName);
				while (pTravParticles != 0)
				{
					DisplayParticleTextured(pTravParticles->pValue, ptCameraLocation) ;
					pTravParticles = pTravParticles->pNext ;
				}
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND) ;
			} else
			{
				glBegin(GL_POINTS) ;
				while (pTravParticles != 0)
				{
					glColor3fv(pTravParticles->pValue->ptColor.dVal) ;
					glVertex3fv(pTravParticles->pValue->ptLocation.dVal) ;
					
					pTravParticles = pTravParticles->pNext ;
				}
				glEnd() ;
			}

	}
}

bool ParticleSource::MoveParticle(Particle *pParticle, float fTime)	// update and move particle with collision testing
{
	Point ptAcceleration ;
	pParticle->dLife += pParticle->dLifeIncrimenter ;
	if (pParticle->dLife <= 0 && bDie)
	{
		return 1 ;
	} else
	{
		pParticle->ptPreviousLocation = pParticle->ptLocation ; 
		
		if (bWind) ptAcceleration = ptWindAcceleration ;
		else ptAcceleration = 0.0 ;

		if (bGravity) ptAcceleration = ptAcceleration + ptGravityAcceleration ;	

		if (bWrongAcceleration) pParticle->ptVelocity = pParticle->ptVelocity + ptAcceleration * fTime * fTime ;
		else pParticle->ptVelocity = pParticle->ptVelocity + ptAcceleration * fTime ;

		pParticle->ptLocation = pParticle->ptLocation + pParticle->ptVelocity * fTime ;
		
		pParticle->ptColor = pParticle->ptColor + pParticle->ptColorIncrimenter ;

		if (pParticle->ptColor.dVal[0] > 1.0) pParticle->ptColor.dVal[0] = 1.0 ;
		else if (pParticle->ptColor.dVal[0] < 0.0) pParticle->ptColor.dVal[0] = 0.0 ;
		if (pParticle->ptColor.dVal[1] > 1.0) pParticle->ptColor.dVal[1] = 1.0 ;
		else if (pParticle->ptColor.dVal[1] < 0.0) pParticle->ptColor.dVal[1] = 0.0 ;
		if (pParticle->ptColor.dVal[2] > 1.0) pParticle->ptColor.dVal[2] = 1.0 ;
		else if (pParticle->ptColor.dVal[2] < 0.0) pParticle->ptColor.dVal[2] = 0.0 ;
	}
	return 0 ;
}

void ParticleSource::MoveParticles(float fTime)
{
	LinkedListNode<Particle> *pTravParticles = Particles.pHead ;
	LinkedListNode<Particle> *pTempParticle ;
	int iNumRespawn = 0 ;
	while (pTravParticles != 0)
	{
		if (MoveParticle(pTravParticles->pValue, fTime))
		{
			pTempParticle = pTravParticles ;
			pTravParticles = pTravParticles->pNext ;
			Particles.Remove(pTempParticle, true) ;
			
			if (bRespawn) iNumRespawn ++ ;
		} else
		{
			pTravParticles = pTravParticles->pNext ;
		}
	}
	SpawnParticles(iNumRespawn) ;
}

void ParticleSource::MoveDisplayParticles(float fTime, Point ptCameraLocation)	// move and display particles
{
	LinkedListNode<Particle> *pTravParticles = Particles.pHead ;
	LinkedListNode<Particle> *pTempParticle ;
	int iNumRespawn = 0 ;

	if (bLines)
	{
		glBegin(GL_POINTS) ;
		while (pTravParticles != 0)
		{
			if (MoveParticle(pTravParticles->pValue, fTime))
			{
				pTempParticle = pTravParticles ;
				pTravParticles = pTravParticles->pNext ;
				Particles.Remove(pTempParticle, true) ;
				
				if (bRespawn) iNumRespawn ++ ;
			} else
			{
				glVertex3fv(pTravParticles->pValue->ptLocation.dVal) ;
				glEnd() ;
				
				if (bTexture && iTextureName != -1)
				{	
					glEnable(GL_BLEND) ;
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, iTextureName);
					
					DisplayParticleTextured(pTravParticles->pValue, ptCameraLocation) ;
					
					glDisable(GL_TEXTURE_2D) ;
					glDisable(GL_BLEND) ;
				} else
				{
					glColor3fv(pTravParticles->pValue->ptColor.dVal) ;
					glBegin(GL_POINTS) ;
					glVertex3fv(pTravParticles->pValue->ptLocation.dVal) ;
					glEnd() ;
				}
				
				glColor3fv(pTravParticles->pValue->ptColor.dVal) ;
				glBegin(GL_LINES) ;
				glVertex3fv(pTravParticles->pValue->ptLocation.dVal) ;
				
				pTravParticles = pTravParticles->pNext ;
			}
		}
		glEnd() ;
	} else
	{
			if (bTexture && iTextureName != -1)
			{	
				glEnable(GL_BLEND) ;
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, iTextureName);
				while (pTravParticles != 0)
				{
					if (MoveParticle(pTravParticles->pValue, fTime))
					{
						pTempParticle = pTravParticles ;
						pTravParticles = pTravParticles->pNext ;
						Particles.Remove(pTempParticle, true) ;
						
						if (bRespawn) iNumRespawn ++ ;
					} else
					{
						DisplayParticleTextured(pTravParticles->pValue, ptCameraLocation) ;
						pTravParticles = pTravParticles->pNext ;
					}
				}
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND) ;
			} else
			{
				glBegin(GL_POINTS) ;
				while (pTravParticles != 0)
				{
					if (MoveParticle(pTravParticles->pValue, fTime))
					{
						pTempParticle = pTravParticles ;
						pTravParticles = pTravParticles->pNext ;
						Particles.Remove(pTempParticle, true) ;
						
						if (bRespawn) iNumRespawn ++ ;
					} else
					{
						glColor3fv(pTravParticles->pValue->ptColor.dVal) ;
						glVertex3fv(pTravParticles->pValue->ptLocation.dVal) ;
						
						pTravParticles = pTravParticles->pNext ;
					}
				}
				glEnd() ;
			}

	}

	SpawnParticles(iNumRespawn) ;
}

	/*

//			glBegin(GL_POINTS) ;
			glColor4f(pTravParticles->pValue->ptColor.dVal[0],
					pTravParticles->pValue->ptColor.dVal[1],
					pTravParticles->pValue->ptColor.dVal[2],
					pTravParticles->pValue->dLife / (dLife + dLifeDev)) ;
//			glVertex3fv(pTravParticles->pValue->ptLocation.dVal) ;
//			glEnd() ;
			GLfloat x, y, z ;
			x = pTravParticles->pValue->ptLocation.dVal[0] ;
			y = pTravParticles->pValue->ptLocation.dVal[1] ;
			z = pTravParticles->pValue->ptLocation.dVal[2] ;
    glBegin(GL_TRIANGLE_STRIP); // Build Quad From A Triangle Strip
    glTexCoord2f(1,1); glVertex3f(x+0.2f,y+0.2f,z); // Top Right
    glTexCoord2f(0,1); glVertex3f(x-0.2f,y+0.2f,z); // Bottom Right
    glTexCoord2f(1,0); glVertex3f(x+0.2f,y-0.2f,z); // Top Left
    glTexCoord2f(0,0); glVertex3f(x-0.2f,y-0.2f,z); // Bottom Left
    glEnd(); // Done Building Triangle Strip
glColor4f(1, 1, 1, 1) ;


	if (bLines) glEnd() ;*/
//}
/*
void ParticleSource::CheckCollision(Particle *pCheck, LinkedList<Model> *pModels)
{
	LinkedListNode<Model> *pTrav = pModels->pHead ;
	LinkedListNode<ModelPolygon> *pTravPolygons ;
	while (pTrav != 0)
	{
		pTravPolygons = pTrav->pValue->Polygons.pHead ;

		while (pTravPolygons != 0)
		{
			if (pCheck->ptLocation.dVal[0] >= pTravPolygons->pValue->ptBBNegatives.dVal[0] - 0.5 && pCheck->ptLocation.dVal[0] <= pTravPolygons->pValue->ptBBPositives.dVal[0] &&
				pCheck->ptLocation.dVal[1] >= pTravPolygons->pValue->ptBBNegatives.dVal[1] - 0.5 && pCheck->ptLocation.dVal[1] <= pTravPolygons->pValue->ptBBPositives.dVal[1] &&
				pCheck->ptLocation.dVal[2] >= pTravPolygons->pValue->ptBBNegatives.dVal[2] - 0.5 && pCheck->ptLocation.dVal[2] <= pTravPolygons->pValue->ptBBPositives.dVal[2])
			{
				Point ptMagnitude = pCheck->ptVelocity * pTravPolygons->pValue->ptNormal ;
				if (ptMagnitude.dVal[0] < 0) ptMagnitude.dVal[0] *= -1.0 ;
				if (ptMagnitude.dVal[1] < 0) ptMagnitude.dVal[1] *= -1.0 ;
				if (ptMagnitude.dVal[2] < 0) ptMagnitude.dVal[2] *= -1.0 ;
				pCheck->ptVelocity = pCheck->ptVelocity + (ptMagnitude * (pTravPolygons->pValue->ptNormal * 1.2)) ;
				return ;
//				pCheck->ptAcceleration = pCheck->ptAcceleration + pCheck->ptAcceleration * (pTravPolygons->pValue->ptNormal * -0.2) ;

				//			pCheck->ptAcceleration = pCheck->ptAcceleration + pCheck->ptAcceleration * (pTrav->pValue->pPolysHead->ptNormal * -1.5) ;
				
				//			pCheck->ptVelocity = pCheck->ptVelocity + pCheck->ptVelocity * World.pPolysHead->ptNormal * 0.03 ;
				//			pCheck->ptVelocity = pCheck->ptVelocity + World.pPolysHead->ptNormal * (World.ptBBUpperFrontLeft - pCheck->ptLocation) * (World.ptBBUpperFrontLeft - pCheck->ptLocation);
			}
			pTravPolygons = pTravPolygons->pNext ;
		}
		pTrav = pTrav->pNext ;
	}
	return ;
}

*/