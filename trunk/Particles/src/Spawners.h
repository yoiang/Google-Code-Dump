#ifndef __SPAWNERS_H__
#define __SPAWNERS_H__

#include "ParticleSource.h"
#include "math.h"

class Fountain : public Spawner
{
public:
	float fRadius ;
	Point ptInitialColor ;

	Fountain() ;
	void Spawn(int iNumSpawn, ParticleSource *pSource) ;
} ;

#endif