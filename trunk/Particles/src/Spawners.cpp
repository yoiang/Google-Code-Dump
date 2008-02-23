#include "Spawners.h"


Fountain::Fountain()
{
	fRadius = 1 ;
	ptInitialColor = Point(0, 0, 0) ;
}

void Fountain::Spawn(int iNumSpawn, ParticleSource *pSource)
{
	Particle *pNew ;
	for (int iTrav = 0 ; iTrav < iNumSpawn ; iTrav ++)
	{
		pNew = new Particle ;
		
		Point ptPlace ;
		ptPlace.dVal[0] = fRadius * RandomPercent() ;
		ptPlace.dVal[2] = sqrt(fRadius * fRadius - ptPlace.dVal[0] * ptPlace.dVal[0]) ;

		pNew->ptVelocity = CalcInitial(pSource->ptInitialVelocity, pSource->ptVelocityDeviation) ;

		if (RandomPercent() > 0.5) 
		{
			ptPlace.dVal[0] *= -1 ;
			if (pNew->ptVelocity.dVal[0] > 0) pNew->ptVelocity.dVal[0] = -1.0 * pNew->ptVelocity.dVal[0] ;
		} else
		{
			if (pNew->ptVelocity.dVal[0] < 0) pNew->ptVelocity.dVal[0] = -1.0 * pNew->ptVelocity.dVal[0] ;
		}
		if (RandomPercent() > 0.5) 
		{
			ptPlace.dVal[2] *= -1 ;
			if (pNew->ptVelocity.dVal[2] > 0) pNew->ptVelocity.dVal[2] = -1.0 * pNew->ptVelocity.dVal[2] ;
		} else
		{
			if (pNew->ptVelocity.dVal[2] < 0) pNew->ptVelocity.dVal[2] = -1.0 * pNew->ptVelocity.dVal[2] ;
		}
		ptPlace.dVal[1] = 0 ;

		pNew->ptLocation = CalcInitial(pSource->ptInitialLocation + ptPlace, pSource->ptLocationDeviation);
		pNew->ptPreviousLocation = pNew->ptLocation ;
		
		pNew->dLife = pSource->dInitialLife + pSource->dLifeDeviation * RandomPercent() - pSource->dLifeDeviation / 2.0 ;
		pNew->dLifeIncrimenter = pSource->dLifeIncrimenter ;
		
		pNew->ptColor = CalcInitial(pSource->ptInitialColor, pSource->ptColorDeviation) ;
		pNew->ptColorIncrimenter = pSource->ptColorIncrimenter ;
		
		pSource->Particles.AddBack(pNew) ;
	}
/*
	ParticleShooter.ptInitialLocation = Point(0, 0.5, 0) ;
	ParticleShooter.ptLocationDeviation = Point(2, 0, 2) ;
	ParticleShooter.ptInitialVelocity = Point(0, 4, 0) ;
	ParticleShooter.ptVelocityDeviation = Point(2.5, 0.6, 2.5) ;

	ParticleShooter.ptInitialColor = Point(0.8, 0.8, 0.9) ;
	ParticleShooter.ptColorDeviation = Point(0.01, 0.01, 0.2) ;
	ParticleShooter.ptColorIncrimenter = Point(-0.005, -0.005, -0.0001) ;

	ParticleShooter.ptWindAcceleration = Point(4, 0, 0) ;

	ParticleShooter.dInitialLife = 0.8 ;
*/
}
