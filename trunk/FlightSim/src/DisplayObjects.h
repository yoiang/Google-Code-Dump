#ifndef __DISPLAY_OBJECTS_H__
#define __DISPLAY_OBJECTS_H__

#include "Terrain.h"
#include "Model.h"
#include "GLUTStuff.h"
#include <stdlib.h>
#include <time.h>

extern 
bool bTime ;	// whether time goes by
extern
int iMountMaxDepth ;	// maximum background midpoint subdivision depth

extern
GLfloat fSunAngle ;	// angle of sun

void InitGround() ;	// initialize the ground
void DisplayGround() ;	// display the ground
void CleanObjects() ;	// clean the ground objects

#endif