#ifndef __PATH_H__
#define __PATH_H__

#include "LinkedList.h"
#include "Point.h"

class PathNode 
{
public:
	Point ptVertex ;
	int iNumSteps ;
	PathNode() ;
} ;

class Path
{
public:
	LinkedList<PathNode> PathList ;
	LinkedListNode<PathNode> *pPlace ;
	int iIterationCount ;
	Point ptIterater ;
	bool bConnectEnd, bLoop ;

	Path() ;
	~Path() ;

	void Add(Point ptSetVertex, int iSetNumSteps) ;
	void Add(PointType dSetX, PointType dSetY, PointType dSetZ, int iSetNumSteps) ;
	Point StartingPoint() ;
	Point StepForward() ;
} ;

#endif