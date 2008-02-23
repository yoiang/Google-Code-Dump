#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"

class Particle	// particle class
{
public:
	Point ptPreviousLocation,	// previous location
		  ptLocation,			// current location
		  ptVelocity ;			// velocity

	double dLifeIncrimenter ;	// life incrimenter
	double dLife ;				// current life

	Point ptColorIncrimenter ;	// color incrimenter
	Point ptColor ;				// current color

	Particle() ;
	~Particle() ;
} ;

#endif