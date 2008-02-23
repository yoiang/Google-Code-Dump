#include "Particle.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Apply(float fTime)
{
//	ptVelocity = ptVelocity + ptAcceleration 
	ptLocation = ptLocation + (ptVelocity * fTime) + ptAcceleration * (fTime * fTime) ;
}

void Particle::ApplyAcceleration(const Point &ptApply)
{
	ptAcceleration = ptAcceleration + ptApply ;
//	ptAcceleration.dX = ptAcceleration.dX + (ptForce.dX / dMass) ; 
//	ptAcceleration.dY = ptAcceleration.dY + (ptForce.dY / dMass) ; 
//	ptAcceleration.dZ = ptAcceleration.dZ + (ptForce.dZ / dMass) ; 
//	ptVelocity = ptVelocity + (ptForce * (fTime * fTime / dMass)) ;
}
