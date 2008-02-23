#ifndef __MODEL_H__
#define __MODEL_H__

#include "Point.h"

#include <windows.h>
#include <GL\Gl.h>
#include <stdio.h>

class ModelPolygon
{
public:
	int iNumSides ;
	Point *pPoints ;
	Point ptColor ;
	PointType dAlpha ;

	ModelPolygon *pNext, *pLast ;
	
	ModelPolygon() ;
	ModelPolygon(int iSetNumSides) ;
	~ModelPolygon() ;

	void SetSides(int iSetNumSides) ;
} ;

class Model
{
private:

public:
	ModelPolygon *pPolysHead, *pPolysTail ;
	Point ptBBUpperFrontLeft, ptBBLowerBackRight ;

	Model() ;
	~Model() ;

	void Display() ;

	void AddPolygon(ModelPolygon *pAdd) ;
	void ClearPolygons() ;

	void ReadFile(char *szFilename) ;
} ;

#endif