#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <gl\Glut.h>
#include "Model.h"

#ifdef WIN32
#include <windows.h>
#else
#include <time.h>
#endif

#include <stdlib.h>

class Terrain	// terrain class
{
public:
	GLfloat fLength, fWidth, fHeight ;	// size of terrain
	Model TerrainModel ;	// model of terrain

	// color of mountain
	Point ptColor ;
	PointType dAlpha ;

	int iMaxDepth ;	// depth of mountain

	Terrain() ;
	~Terrain() ;

	void AddPolygon(ModelPolygon *pAdd) ;	// add polygon to terrain
	int Midpoint(ModelPolygon *pSplit, int iDepth) ;	// midpoint recursive function
	void GenMidpoint() ;	// generate midpoint
	void Display() ;	// display
} ;

#endif