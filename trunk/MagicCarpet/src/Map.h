#ifndef __MAP_H__
#define __MAP_H__

#include <stdio.h>
#include "GLUTStuff.h"
#include "Point.h"
#include "UtilityFuncs.h"

class Map
{
public:
	double *pHeightMap ;
	long lHoriLen, lVertLen ;
	double dHoriSize, dVertSize, dMapScale ;
	int bTexture, bEdging ;
	GLuint iLowTexName, iMidTexName, iHighTexName ;
	double dLowHeight, dMidHeight, dHighHeight ;

	Map() ;
	~Map() ;

	void CreateMap(long lHori, long lVert) ;
	void Clear() ;

	void GenerateFlatMap(double dScale, double dHeight, long lHori, long lVert) ;
	int ReadRaw(char *szFilename, long lHori, long lVert, double dScale, double dScaleHeight) ;
	int ReadMap(char *szFilename) ;

	int SetLowHeight(double dHeight, char *szTexFilename) ;
	int SetMidHeight(double dHeight, char *szTexFilename) ;
	int SetHighHeight(double dHeight, char *szTexFilename) ;

	double CheckCollision(Point ptCameraPosition) ;

	double Height(long lHori, long lVert) ;
	double Height(long lHori, long lVert, double dHeight) ;
	void Display(Point ptCameraPosition, Point ptCameraOrientation, double dScale) ;
} ;

#endif