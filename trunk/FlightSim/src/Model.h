#ifndef __MODEL_H__
#define __MODEL_H__

#include "Point.h"
#include "LinkedList.h"
#include "UtilityFuncs.h"

#ifdef WIN32
#include <windows.h>
#include <GL\Gl.h>
#else 
#include <GL\Glut.h>
#endif

#include <stdio.h>

class ModelPolygon	// polygon class
{
public:
	int iNumSides ; // number of sides
	Point *pPoints ; // array of points
	Point ptColor ; // color of polygon
	PointType dAlpha ; // alpha of polygon
	GLuint iTextureName ; // texture name

	Point ptNormal ; // polygon normal
	Point ptBBNegatives, ptBBPositives ; // bounding box

	ModelPolygon() ; // contructor
	ModelPolygon(int iSetNumSides) ; // costructor
	~ModelPolygon() ; // destructor

	void SetSides(int iSetNumSides) ;	// set number of sides
} ;

class Model	// model class
{
private:

public:
	LinkedList<ModelPolygon> Polygons ; // polygons in the model

	Model() ;
	~Model() ;

	void Display(bool bBlackOut) ;	// display the model

	void ReadFile(char *szFilename) ;	// read in file
} ;

#endif