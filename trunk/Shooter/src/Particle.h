#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"

class Particle
{
public:
	Point ptLocation,
		  ptVelocity,
		  ptAcceleration ;

	PointType dMass ;

	double dLife ;

	Point ptColor ;
	PointType dAlpha ;

	Particle() ;
	~Particle() ;
	void Apply(float fTime) ;
	void ApplyAcceleration(const Point &ptApply) ;
} ;

#endif